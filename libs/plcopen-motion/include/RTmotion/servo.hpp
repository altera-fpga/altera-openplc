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

#pragma once

#include <RTmotion/global.hpp>

namespace RTmotion
{
class Servo
{
public:
  Servo();
  virtual ~Servo();
  virtual MC_SERVO_ERROR_CODE setPower(mcBOOL powerStatus, mcBOOL& isDone);
  virtual MC_SERVO_ERROR_CODE setPos(mcDINT pos);
  virtual MC_SERVO_ERROR_CODE setVel(mcDINT vel);
  virtual MC_SERVO_ERROR_CODE setTorque(mcLREAL torque);
  virtual MC_SERVO_ERROR_CODE setMaxProfileVel(mcDWORD vel);
  virtual MC_SERVO_ERROR_CODE setMode(mcSINT mode);
  virtual MC_SERVO_ERROR_CODE setHomeEnable(mcBOOL enable);
  virtual mcDINT pos();
  virtual mcDINT vel();
  virtual mcDINT acc();
  virtual mcLREAL torque();
  virtual mcSINT mode();
  virtual mcBOOL getHomeState();
  virtual mcBOOL readVal(mcDINT index, mcLREAL& value);
  virtual mcBOOL writeVal(mcDINT index, mcLREAL value);
  virtual mcBOOL readVal(mcUINT index, mcUSINT sub_index, mcUSINT data_length,
                         mcUDINT& value);
  virtual mcBOOL writeVal(mcUINT index, mcUSINT sub_index, mcUSINT data_length,
                          mcUDINT value);
  virtual MC_SERVO_ERROR_CODE resetError(mcBOOL& isDone);
  virtual void runCycle(mcLREAL freq);
  virtual void emergStop();

private:
  class ServoImpl
  {
  public:
    mcDINT mSubmitPos     = 0;
    mcDINT mPos           = 0;
    mcLREAL mVel          = 0;
    mcLREAL mAcc          = 0;
    mcLREAL mTorque       = 0;
    mcLREAL maxProfileVel = 0;
    mcSINT mode           = 0;
    mcBOOL mHomeEnable    = mcFALSE;
    mcBOOL mHomeState     = mcFALSE;
  };
  ServoImpl mImpl_;
};
}  // namespace RTmotion
