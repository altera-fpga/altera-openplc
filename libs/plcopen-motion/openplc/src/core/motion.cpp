/*
 * Copyright (c) 2024 Intel Corporation
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include <string.h>
#include <vector>

#include <RTmotion/global.hpp>
#include <RTmotion/axis.hpp>
#include <RTmotion/fb/fb_power.hpp>
#include <RTmotion/fb/fb_move_absolute.hpp>
#include <RTmotion/fb/fb_move_additive.hpp>
#include <RTmotion/fb/fb_move_relative.hpp>
#include <RTmotion/fb/fb_move_velocity.hpp>
#include <RTmotion/fb/fb_read_actual_position.hpp>
#include <RTmotion/fb/fb_read_actual_velocity.hpp>
#include <RTmotion/fb/fb_read_command_position.hpp>
#include <RTmotion/fb/fb_read_command_velocity.hpp>
#include <RTmotion/fb/fb_read_axis_error.hpp>
#include <RTmotion/fb/fb_read_status.hpp>
#include <RTmotion/fb/fb_reset.hpp>
#include <RTmotion/fb/fb_stop.hpp>
#include <RTmotion/fb/fb_halt.hpp>

using namespace RTmotion;

#define INCLUDING_RTMOTION_HEADERS
#include "motion.h"
#include "ladder.h"


void MC_Power( FB_MC_POWER * frame )
{
    RTmotion::FbPower * fb_power = (RTmotion::FbPower *)frame->_FbInst;
    if (fb_power == NULL)
    {
        //Init FB
        fb_power = new (frame->_FbMem)RTmotion::FbPower();
        frame->_FbInst = (unsigned char *)fb_power;
    }

    if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
        fb_power->setAxis(rtmotion_axis[frame->Axis.AxisId]);
    else
        return;

    fb_power->setEnable(frame->Enable ? mcTRUE : mcFALSE);
    fb_power->setEnablePositive(frame->EnablePositive ? mcTRUE : mcFALSE);
    fb_power->setEnableNegative(frame->EnableNegative ? mcTRUE : mcFALSE);

    fb_power->runCycle();

    frame->Valid = fb_power->isValid() == mcTRUE ? true : false;
    frame->Status = fb_power->getPowerStatus() == mcTRUE ? true : false;
    frame->Error = fb_power->isError() == mcTRUE ? true : false;
    frame->ErrorID = fb_power->getErrorID();
}

void MC_Halt( FB_MC_HALT * frame )
{
    RTmotion::FbHalt * fb_halt = (RTmotion::FbHalt *)frame->_FbInst;
    if (fb_halt == NULL)
    {
        //Init FB
        fb_halt = new (frame->_FbMem)RTmotion::FbHalt();
        frame->_FbInst = (unsigned char *)fb_halt;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_halt->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_halt->setExecute(frame->Execute ? mcTRUE : mcFALSE);
        fb_halt->setDeceleration(frame->Deceleration);
        fb_halt->setJerk(frame->Jerk);
        fb_halt->setBufferMode((RTmotion::MC_BUFFER_MODE)frame->BufferMode);

        frame->Done = fb_halt->isDone() == mcTRUE ? true : false;
        frame->Busy = fb_halt->isBusy() == mcTRUE ? true : false;
        frame->Active = fb_halt->isActive() == mcTRUE ? true : false;
        frame->CommandAborted = fb_halt->isAborted() == mcTRUE ? true : false;
        frame->Error = fb_halt->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_halt->getErrorID();

        fb_halt->runCycle();
    }
}

void MC_Stop( FB_MC_STOP * frame )
{
    RTmotion::FbStop * fb_stop = (RTmotion::FbStop *)frame->_FbInst;
    if (fb_stop == NULL)
    {
        //Init FB
        fb_stop = new (frame->_FbMem)RTmotion::FbStop();
        frame->_FbInst = (unsigned char *)fb_stop;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_stop->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_stop->setExecute(frame->Execute ? mcTRUE : mcFALSE);
        fb_stop->setDeceleration(frame->Deceleration);
        fb_stop->setJerk(frame->Jerk);
        frame->Done = fb_stop->isDone() == mcTRUE ? true : false;
        frame->Busy = fb_stop->isBusy() == mcTRUE ? true : false;
        frame->CommandAborted = fb_stop->isAborted() == mcTRUE ? true : false;
        frame->Error = fb_stop->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_stop->getErrorID();

        fb_stop->runCycle();
    }
}

void MC_Reset( FB_MC_RESET * frame )
{
    RTmotion::FbReset * fb_reset = (RTmotion::FbReset *)frame->_FbInst;
    if (fb_reset == NULL)
    {
        //Init FB
        fb_reset = new (frame->_FbMem)RTmotion::FbReset();
        frame->_FbInst = (unsigned char *)fb_reset;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_reset->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_reset->setEnable(frame->Execute ? mcTRUE : mcFALSE);
        frame->Done = fb_reset->isDone() == mcTRUE ? true : false;
        frame->Busy = fb_reset->isBusy() == mcTRUE ? true : false;
        frame->Error = fb_reset->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_reset->getErrorID();

        fb_reset->runCycle();
    }
}

void MC_MoveVelocity( FB_MC_MOVEVELOCITY * frame )
{
    RTmotion::FbMoveVelocity * fb_move_velocity = (RTmotion::FbMoveVelocity *)frame->_FbInst;
    if (fb_move_velocity == NULL)
    {
        //Init FB
        fb_move_velocity = new (frame->_FbMem)RTmotion::FbMoveVelocity();
        frame->_FbInst = (unsigned char *)fb_move_velocity;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_move_velocity->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_move_velocity->setExecute(frame->Execute ? mcTRUE : mcFALSE);
        fb_move_velocity->setContinuousUpdate(frame->ContinuousUpdate ? mcTRUE : mcFALSE);
        fb_move_velocity->setVelocity(frame->Velocity);
        fb_move_velocity->setAcceleration(frame->Acceleration);
        fb_move_velocity->setDeceleration(frame->Deceleration);
        fb_move_velocity->setJerk(frame->Jerk);
        fb_move_velocity->setDirection((RTmotion::MC_DIRECTION)frame->Direction);
        fb_move_velocity->setBufferMode((RTmotion::MC_BUFFER_MODE)frame->BufferMode);


        frame->InVelocity = fb_move_velocity->isInVelocity() == mcTRUE ? true : false;
        frame->Busy = fb_move_velocity->isBusy() == mcTRUE ? true : false;
        frame->Active = fb_move_velocity->isActive() == mcTRUE ? true : false;
        frame->CommandAborted = fb_move_velocity->isAborted() == mcTRUE ? true : false;
        frame->Error = fb_move_velocity->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_move_velocity->getErrorID();

        fb_move_velocity->runCycle();
    }
}

void MC_MoveRelative( FB_MC_MOVERELATIVE * frame )
{
    RTmotion::FbMoveRelative * fb_move_relative = (RTmotion::FbMoveRelative *)frame->_FbInst;
    if (fb_move_relative == NULL)
    {
        //Init FB
        fb_move_relative = new (frame->_FbMem)RTmotion::FbMoveRelative();
        frame->_FbInst = (unsigned char *)fb_move_relative;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_move_relative->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_move_relative->setExecute(frame->Execute ? mcTRUE : mcFALSE);
        fb_move_relative->setContinuousUpdate(frame->ContinuousUpdate ? mcTRUE : mcFALSE);
        fb_move_relative->setDistance(frame->Distance);
        fb_move_relative->setVelocity(frame->Velocity);
        fb_move_relative->setAcceleration(frame->Acceleration);
        fb_move_relative->setDeceleration(frame->Deceleration);
        fb_move_relative->setJerk(frame->Jerk);
        fb_move_relative->setBufferMode((RTmotion::MC_BUFFER_MODE)frame->BufferMode);


        frame->Done = fb_move_relative->isDone() == mcTRUE ? true : false;
        frame->Busy = fb_move_relative->isBusy() == mcTRUE ? true : false;
        frame->Active = fb_move_relative->isActive() == mcTRUE ? true : false;
        frame->CommandAborted = fb_move_relative->isAborted() == mcTRUE ? true : false;
        frame->Error = fb_move_relative->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_move_relative->getErrorID();

        fb_move_relative->runCycle();
    }
}

void MC_MoveAbsolute( FB_MC_MOVEABSOLUTE * frame )
{
    RTmotion::FbMoveAbsolute * fb_move_absolute = (RTmotion::FbMoveAbsolute *)frame->_FbInst;
    if (fb_move_absolute == NULL)
    {
        //Init FB
        fb_move_absolute = new (frame->_FbMem)RTmotion::FbMoveAbsolute();
        frame->_FbInst = (unsigned char *)fb_move_absolute;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_move_absolute->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_move_absolute->setExecute(frame->Execute ? mcTRUE : mcFALSE);
        fb_move_absolute->setContinuousUpdate(frame->ContinuousUpdate ? mcTRUE : mcFALSE);
        fb_move_absolute->setPosition(frame->Position);
        fb_move_absolute->setVelocity(frame->Velocity);
        fb_move_absolute->setAcceleration(frame->Acceleration);
        fb_move_absolute->setDeceleration(frame->Deceleration);
        fb_move_absolute->setJerk(frame->Jerk);
        fb_move_absolute->setDirection((RTmotion::MC_DIRECTION)frame->Direction);
        fb_move_absolute->setBufferMode((RTmotion::MC_BUFFER_MODE)frame->BufferMode);


        frame->Done = fb_move_absolute->isDone() == mcTRUE ? true : false;
        frame->Busy = fb_move_absolute->isBusy() == mcTRUE ? true : false;
        frame->Active = fb_move_absolute->isActive() == mcTRUE ? true : false;
        frame->CommandAborted = fb_move_absolute->isAborted() == mcTRUE ? true : false;
        frame->Error = fb_move_absolute->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_move_absolute->getErrorID();

        fb_move_absolute->runCycle();
    }
}

void MC_MoveAdditive( FB_MC_MOVEADDITIVE * frame )
{
    RTmotion::FbMoveAdditive * fb_move_additive = (RTmotion::FbMoveAdditive *)frame->_FbInst;
    if (fb_move_additive == NULL)
    {
        //Init FB
        fb_move_additive = new (frame->_FbMem)RTmotion::FbMoveAdditive();
        frame->_FbInst = (unsigned char *)fb_move_additive;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_move_additive->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_move_additive->setExecute(frame->Execute ? mcTRUE : mcFALSE);
        fb_move_additive->setContinuousUpdate(frame->ContinuousUpdate ? mcTRUE : mcFALSE);
        fb_move_additive->setDistance(frame->Distance);
        fb_move_additive->setVelocity(frame->Velocity);
        fb_move_additive->setAcceleration(frame->Acceleration);
        fb_move_additive->setDeceleration(frame->Deceleration);
        fb_move_additive->setJerk(frame->Jerk);
        fb_move_additive->setBufferMode((RTmotion::MC_BUFFER_MODE)frame->BufferMode);

        frame->Done = fb_move_additive->isDone() == mcTRUE ? true : false;
        frame->Busy = fb_move_additive->isBusy() == mcTRUE ? true : false;
        frame->Active = fb_move_additive->isActive() == mcTRUE ? true : false;
        frame->CommandAborted = fb_move_additive->isAborted() == mcTRUE ? true : false;
        frame->Error = fb_move_additive->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_move_additive->getErrorID();

        fb_move_additive->runCycle();
    }
}

void MC_ReadActualVelocity( FB_MC_READACTUALVELOCITY * frame )
{
    RTmotion::FbReadActualVelocity * fb_read_actual_velocity = (RTmotion::FbReadActualVelocity *)frame->_FbInst;
    if (fb_read_actual_velocity == NULL)
    {
        //Init FB
        fb_read_actual_velocity = new (frame->_FbMem)RTmotion::FbReadActualVelocity();
        frame->_FbInst = (unsigned char *)fb_read_actual_velocity;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_read_actual_velocity->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_read_actual_velocity->setEnable(frame->Enable ? mcTRUE : mcFALSE);
        frame->Valid = fb_read_actual_velocity->isValid() == mcTRUE ? true : false;
        frame->Busy = fb_read_actual_velocity->isBusy() == mcTRUE ? true : false;
        frame->Error = fb_read_actual_velocity->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_read_actual_velocity->getErrorID();
        frame->Velocity = fb_read_actual_velocity->getFloatValue();

        fb_read_actual_velocity->runCycle();
    }
}

void MC_ReadActualPosition( FB_MC_READACTUALPOSITION * frame )
{
    RTmotion::FbReadActualPosition * fb_read_actual_position = (RTmotion::FbReadActualPosition *)frame->_FbInst;
    if (fb_read_actual_position == NULL)
    {
        //Init FB
        fb_read_actual_position = new (frame->_FbMem)RTmotion::FbReadActualPosition();
        frame->_FbInst = (unsigned char *)fb_read_actual_position;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_read_actual_position->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_read_actual_position->setEnable(frame->Enable ? mcTRUE : mcFALSE);
        frame->Valid = fb_read_actual_position->isValid() == mcTRUE ? true : false;
        frame->Busy = fb_read_actual_position->isBusy() == mcTRUE ? true : false;
        frame->Error = fb_read_actual_position->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_read_actual_position->getErrorID();
        frame->Position = fb_read_actual_position->getFloatValue();

        fb_read_actual_position->runCycle();
    }
}

void MC_ReadAxisError( FB_MC_READAXISERROR * frame )
{
    RTmotion::FbReadAxisError * fb_read_axis_error = (RTmotion::FbReadAxisError *)frame->_FbInst;
    if (fb_read_axis_error == NULL)
    {
        //Init FB
        fb_read_axis_error = new (frame->_FbMem)RTmotion::FbReadAxisError();
        frame->_FbInst = (unsigned char *)fb_read_axis_error;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_read_axis_error->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_read_axis_error->setEnable(frame->Enable ? mcTRUE : mcFALSE);
        frame->Valid = fb_read_axis_error->isValid() == mcTRUE ? true : false;
        frame->Busy = fb_read_axis_error->isBusy() == mcTRUE ? true : false;
        frame->Error = fb_read_axis_error->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_read_axis_error->getErrorID();
        frame->AxisErrorID = fb_read_axis_error->getAxisErrorId();

        fb_read_axis_error->runCycle();
    }
}

void MC_ReadStatus( FB_MC_READSTATUS * frame )
{
    RTmotion::FbReadStatus * fb_read_status = (RTmotion::FbReadStatus *)frame->_FbInst;
    if (fb_read_status == NULL)
    {
        //Init FB
        fb_read_status = new (frame->_FbMem)RTmotion::FbReadStatus();
        frame->_FbInst = (unsigned char *)fb_read_status;
    }
    else
    {
        if (frame->Axis.AxisId >= 0 && frame->Axis.AxisId < sizeof(rtmotion_axis))
            fb_read_status->setAxis(rtmotion_axis[frame->Axis.AxisId]);
        else
            return;

        fb_read_status->setEnable(frame->Enable ? mcTRUE : mcFALSE);
        frame->Valid = fb_read_status->isValid() == mcTRUE ? true : false;
        frame->Busy = fb_read_status->isBusy() == mcTRUE ? true : false;
        frame->Error = fb_read_status->isError() == mcTRUE ? true : false;
        frame->ErrorID = fb_read_status->getErrorID();
        frame->ErrorStop = fb_read_status->isErrorStop() == mcTRUE ? true : false;;
        frame->Disabled = fb_read_status->isDisabled() == mcTRUE ? true : false;;
        frame->Stopping = fb_read_status->isStopping() == mcTRUE ? true : false;;
        frame->Homing = fb_read_status->isHoming() == mcTRUE ? true : false;;
        frame->Standstill = fb_read_status->isStandStill() == mcTRUE ? true : false;;
        frame->DiscreteMotion = fb_read_status->isDiscretMotion() == mcTRUE ? true : false;;
        frame->ContinuousMotion = fb_read_status->isContinuousMotion() == mcTRUE ? true : false;;
        frame->SynchronizedMotion = fb_read_status->isSynchronizedMotion() == mcTRUE ? true : false;;

        fb_read_status->runCycle();
    }
}

