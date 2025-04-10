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

#include <RTmotion/servo.hpp>

namespace RTmotion
{
Servo::Servo()
{
  // mImpl_ = new ServoImpl();
}

Servo::~Servo()
{
  // delete mImpl_;
}

MC_SERVO_ERROR_CODE Servo::setPower(mcBOOL /*powerStatus*/, mcBOOL& isDone)
{
  isDone = mcTRUE;
  return mcServoNoError;
}

MC_SERVO_ERROR_CODE Servo::setPos(mcDINT pos)
{
  mImpl_.mSubmitPos = pos;
  return mcServoNoError;
}

MC_SERVO_ERROR_CODE Servo::setVel(mcDINT vel)
{
  mImpl_.mVel = vel;
  return mcServoNoError;
}

MC_SERVO_ERROR_CODE Servo::setTorque(mcLREAL torque)
{
  mImpl_.mTorque = torque;
  return mcServoNoError;
}

MC_SERVO_ERROR_CODE Servo::setMaxProfileVel(mcDWORD vel)
{
  mImpl_.maxProfileVel = vel;
  return mcServoNoError;
}

MC_SERVO_ERROR_CODE Servo::setMode(mcSINT mode)
{
  mImpl_.mode = mode;
  return mcServoNoError;
}

MC_SERVO_ERROR_CODE Servo::setHomeEnable(mcBOOL enable)
{
  mImpl_.mHomeEnable = enable;
  return mcServoNoError;
}

mcDINT Servo::pos()
{
  return mImpl_.mPos;
}

mcDINT Servo::vel()
{
  return mImpl_.mVel;
}

mcDINT Servo::acc()
{
  return mImpl_.mAcc;
}

mcLREAL Servo::torque()
{
  return mImpl_.mTorque;
}

mcSINT Servo::mode()
{
  return mImpl_.mode;
}

mcBOOL Servo::getHomeState()
{
  return mImpl_.mHomeState;
}

mcBOOL Servo::readVal(mcDINT /*index*/, mcLREAL& /*value*/)
{
  return mcFALSE;
}

mcBOOL Servo::writeVal(mcDINT /*index*/, mcLREAL /*value*/)
{
  return mcFALSE;
}

mcBOOL Servo::readVal(mcUINT /*index*/, mcUSINT /*sub_index*/,
                      mcUSINT /*data_length*/, mcUDINT& /*value*/)
{
  return mcTRUE;
}

mcBOOL Servo::writeVal(mcUINT /*index*/, mcUSINT /*sub_index*/,
                       mcUSINT /*data_length*/, mcUDINT /*value*/)
{
  return mcTRUE;
}

MC_SERVO_ERROR_CODE Servo::resetError(mcBOOL& isDone)
{
  isDone = mcTRUE;
  return mcServoNoError;
}

void Servo::runCycle(mcLREAL freq)
{
  mcDINT pos_diff = mImpl_.mSubmitPos - mImpl_.mPos;
  mcLREAL cur_vel = pos_diff * freq;
  mImpl_.mAcc     = (cur_vel - mImpl_.mVel) * freq;
  mImpl_.mVel     = cur_vel;
  mImpl_.mPos     = mImpl_.mSubmitPos;
  //printf("mImpl_.mSubmitPos: %d, mImpl_.mVel: %f, \n", mImpl_.mSubmitPos, mImpl_.mVel);
}

void Servo::emergStop()
{
  mImpl_.mPos = mImpl_.mSubmitPos;
  mImpl_.mVel = mImpl_.mAcc = mImpl_.mTorque = 0;
}
}  // namespace RTmotion
