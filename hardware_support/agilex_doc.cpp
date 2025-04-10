/* ##################################################################################
* Copyright (C) 2025 Altera Corporation
* SPDX-License-Identifier: GPL-3.0-or-later
* ##################################################################################
*/

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <exception>
#include <fstream>
#include <cstdint>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <RTmotion/axis.hpp>
#include <RTmotion/global.hpp>
#include <RTmotion/servo.hpp>

#include "ladder.h"

#define RTMOTION

#define DRIVE_AXIS_PER_DEVICE   2
#define MAX_AXIS_NUM            2

using namespace RTmotion;

namespace DoC
{
    enum WaveDemoMode {
        WAVE_DEMO_MODE_SPEED    = 0,
        WAVE_DEMO_MODE_POSITION = 1,
        WAVE_DEMO_MODE_CLOCK    = 2,
    };

    enum WaveDemoWaveform {
        SINE        = 0,
        TRIANGLE    = 1,
        SQUARE      = 2,
        SAW         = 3,
        CONSTANT    = 4,
    };

    enum DebugRegister {
        // For full set of Drive-On-Chip registers
        //refer to AN1000 or AN994 
        SPEED               = 10,
        POSITION            = 12,
        SPEED_SETP0         = 22,
        AXIS_SELECT         = 23,
        POS_SETP0           = 25,
        WAVE_DEMO_MODE      = 29,
        POS_SPEED_LIMIT     = 30,
        WAVE_DEMO_PERIOD    = 33,
        WAVE_DEMO_OFFSET    = 34,
        WAVE_DEMO_WAVEFORM  = 35,
        WAVE_DEMO_AMP_F     = 36,
        WAVE_DEMO_UPDATE    = 61,
        REG_LENGTH          = 66
    };
} // DoC

class UIODevice
{
public:
    UIODevice(uint32_t device = 0, uint32_t axis = 0)
      : m_device(device),
        m_axis(axis),
        m_mmap(NULL),
        m_offset(0),
        m_size(0)
    {
      // Check for DoC device
      std::string device_name("uio" + std::to_string(m_device));
      std::string device_path = GetDevicePath(device_name);

      if (device_path.size() == 0) {
          throw std::runtime_error("DoC device not found");
      }

      // Check for axis mapping
      if (!IsAxisMapped(m_device, m_axis)) {
          throw std::runtime_error("Requested axis is not available");
      }

      // Get axis memory mapping information
      std::string sys_offset_path("/sys/class/uio/" + device_name + "/maps/map" + std::to_string(m_axis) + "/offset");
      std::string sys_size_path("/sys/class/uio/" + device_name + "/maps/map" + std::to_string(m_axis) + "/size");

      m_offset = ReadSysHexVal(sys_offset_path);
      m_size = ReadSysHexVal(sys_size_path);

      int fd = open(device_path.c_str(), O_RDWR);
      if (fd > 0) {
          m_mmap = (uint32_t*)mmap(0, m_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
          close(fd);
          if ((void *)m_mmap == MAP_FAILED) {
              throw std::runtime_error("Failed to map debugregisters");
          }
      }
    }
    ~UIODevice(void)
    {
        if (m_mmap) {
            munmap((void*)m_mmap, m_size);
        }
    }

    uint32_t UIODevice::Read(uint32_t reg)
    {
        if (reg < DoC::DebugRegister::REG_LENGTH) {
            return *(m_mmap + reg + (m_offset/sizeof(uint32_t)));
        }
        return 0;
    }

    void UIODevice::Write(uint32_t reg, uint32_t value)
    {
        if (reg < DoC::DebugRegister::REG_LENGTH) {
            *(m_mmap + reg + (m_offset/sizeof(uint32_t))) = value;
        }
    }

    std::string UIODevice::GetDevicePath(const std::string& device_name)
    {
           // Check if /dev/<device> exists
        std::string device_path = "/dev/" + device_name;
        struct stat sp;
        if (stat(device_path.c_str(), &sp) == 0) {
            // Get sysfs path
            std::string sys_name_path = "/sys/class/uio/" + device_name + "/name";
            std::ifstream sysfile(sys_name_path.c_str(), std::ifstream::in);
            std::string ip;
            if (std::getline(sysfile, ip)) {
                // Is uio device a DoC device? 
                if (ip.substr(0,3) == std::string("doc")) {
                    return device_path;
                }
            }
        }
        return std::string();
    }
    
    static bool UIODevice::IsAxisMapped(uint32_t device, uint32_t axis)
    {
        std::string sys_path = "/sys/class/uio/uio" + std::to_string(device) + "/maps/map" + std::to_string(axis);
        struct stat sp;
        if (stat(sys_path.c_str(), &sp) == 0) {
            return true;
        }
        return false;
    }

private:

    uint64_t UIODevice::ReadSysHexVal(const std::string& filepath)
    {
        std::ifstream sysfile(filepath.c_str(), std::ifstream::in);
        std::string ip;
        if (std::getline(sysfile, ip)) {
            return std::stoull(ip,nullptr,16);
        }
        return 0;
    }

private:
    uint32_t        m_device;
    uint32_t        m_axis;
    uint32_t*       m_mmap;
    off_t           m_offset;
    size_t          m_size;
};

class DoCServo : public RTmotion::Servo
{
public:
    DoCServo::DoCServo(uint32_t axis)
        : mTargetVelocity{0}
    {
        uint32_t device = axis / DRIVE_AXIS_PER_DEVICE;
        uint32_t subAxis = axis % DRIVE_AXIS_PER_DEVICE;

        if (UIODevice::IsAxisMapped(device, subAxis)) {
            mDevice = std::make_shared<UIODevice>(device, axis);
        }
    }

    DoCServo::~DoCServo() {}

    MC_SERVO_ERROR_CODE DoCServo::setVel(mcDINT vel) override
    {
        mTargetVelocity = vel;
        return mcServoNoError;
    }

    mcDINT DoCServo::vel()
    {
        mcDINT vel = 0;
        if (mDevice) {
            vel = static_cast<mcDINT>(mDevice->Read(DoC::DebugRegister::SPEED));
        }
        return vel;
    }

    void DoCServo::runCycle(mcLREAL freq) override
    {
        if (mDevice && mSetVelocity != mTargetVelocity) {
            mSetVelocity = mTargetVelocity;

            mDevice->Write(DoC::DebugRegister::WAVE_DEMO_MODE, DoC::WaveDemoMode::WAVE_DEMO_MODE_SPEED);
            mDevice->Write(DoC::DebugRegister::SPEED_SETP0, static_cast<uint32_t>(mSetVelocity));

            mDevice->Write(DoC::DebugRegister::WAVE_DEMO_PERIOD, 200);
            mDevice->Write(DoC::DebugRegister::WAVE_DEMO_AMP_F, 0);

            mDevice->Write(DoC::DebugRegister::WAVE_DEMO_OFFSET, 0);
            mDevice->Write(DoC::DebugRegister::WAVE_DEMO_WAVEFORM, DoC::WaveDemoWaveform::CONSTANT);
            mDevice->Write(DoC::DebugRegister::WAVE_DEMO_UPDATE, 1);
        }
    }

private:
    mcDINT mTargetVelocity;
    mcDINT mSetVelocity;
    std::shared_ptr<UIODevice> mDevice;
};

static AxisConfig config[MAX_AXIS_NUM];
static DoCServo* servo[MAX_AXIS_NUM];
static uint32_t active_drives_num;

void initializeHardware()
{
    for (uint32_t i = 0; i < MAX_AXIS_NUM; i++) {
        rtmotion_axis[i] = nullptr;
        servo[i] = nullptr;
    }

    active_drives_num = 0;

    for (uint32_t i = 0; i < MAX_AXIS_NUM; i++) {
        config[i].encoder_count_per_unit_ = 1;
        rtmotion_axis[i] = new RTmotion::Axis();
        rtmotion_axis[i]->setAxisConfig(&config[i]);
        rtmotion_axis[i]->setAxisId(i);
        rtmotion_axis[i]->setNodeQueueSize(5);

        try {
            servo[i] = new DoCServo(i);
            rtmotion_axis[i]->setServo(servo[i]);
            active_drives_num++;
        }
        catch(const std::exception& e) {
            printf("ERROR: Cannot initialize axis: %ul => %s\n",i,e.what());
            break;
        }
        rtmotion_axis[i]->setControllerMode(RTmotion::mcServoControlModeVelocity);
    }
}

void finalizeHardware()
{
    for (uint32_t i = 0; i < MAX_AXIS_NUM; i++) {
        if(rtmotion_axis[i] != nullptr) {
            delete rtmotion_axis[i];
            rtmotion_axis[i] = nullptr;
        }
        if(servo[i] != nullptr) {
            delete servo[i];
            servo[i] = nullptr;
        }
    }
}

void updateBuffersIn()
{
    pthread_mutex_lock(&bufferLock);    //lock mutex

    for (uint32_t i = 0; i < active_drives_num; i++)
    {
        rtmotion_axis[i]->runCycle();
    }
    
    pthread_mutex_unlock(&bufferLock);  //unlock mutex
}

void updateBuffersOut()
{
    pthread_mutex_lock(&bufferLock);    //lock mutex

    pthread_mutex_unlock(&bufferLock);  //unlock mutex
}
