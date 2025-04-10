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

#include <RTmotion/fb/fb_power.hpp>

namespace RTmotion
{
FbPower::FbPower() : enable_positive_(mcFALSE), enable_negative_(mcFALSE)
{
}

void FbPower::setEnablePositive(mcBOOL enable_positive)
{
  enable_positive_ = enable_positive;
}

void FbPower::setEnableNegative(mcBOOL enable_negative)
{
  enable_negative_ = enable_negative;
}

mcBOOL FbPower::getPowerStatus()
{
  return axis_->powerOn();
}

MC_ERROR_CODE FbPower::onExecution()
{
  axis_->setPower(enable_, enable_positive_, enable_negative_);
  valid_ = axis_->powerTriggered();

  return axis_->getAxisError();
}

MC_ERROR_CODE FbPower::onFallingEdgeExecution()
{
  axis_->setPower(enable_, enable_positive_, enable_negative_);
  return axis_->getAxisError();
}

}  // namespace RTmotion
