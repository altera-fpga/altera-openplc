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

#include <RTmotion/fb/fb_axis_read.hpp>

namespace RTmotion
{
/**
 * @brief Function block base for single axis motion
 */
class FbReadStatus : public FbAxisRead
{
public:
  FbReadStatus();
  ~FbReadStatus() override = default;

  mcBOOL isErrorStop();
  mcBOOL isDisabled();
  mcBOOL isStopping();
  mcBOOL isHoming();
  mcBOOL isStandStill();
  mcBOOL isDiscretMotion();
  mcBOOL isContinuousMotion();
  mcBOOL isSynchronizedMotion();

  MC_ERROR_CODE onExecution() override;

protected:
  VAR_OUTPUT mcBOOL error_stop_;
  VAR_OUTPUT mcBOOL disabled_;
  VAR_OUTPUT mcBOOL stopping_;
  VAR_OUTPUT mcBOOL homing_;
  VAR_OUTPUT mcBOOL standstill_;
  VAR_OUTPUT mcBOOL discrete_motion_;
  VAR_OUTPUT mcBOOL continuous_motion_;
  VAR_OUTPUT mcBOOL synchronized_motion_;
};
}  // namespace RTmotion
