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

#include <RTmotion/fb/fb_read_status.hpp>

namespace RTmotion
{
FbReadStatus::FbReadStatus()
  : error_stop_(mcFALSE)
  , disabled_(mcFALSE)
  , stopping_(mcFALSE)
  , homing_(mcFALSE)
  , standstill_(mcFALSE)
  , discrete_motion_(mcFALSE)
  , continuous_motion_(mcFALSE)
  , synchronized_motion_(mcFALSE)
{
}

mcBOOL FbReadStatus::isErrorStop()
{
  return error_stop_;
}
mcBOOL FbReadStatus::isDisabled()
{
  return disabled_;
}
mcBOOL FbReadStatus::isStopping()
{
  return stopping_;
}
mcBOOL FbReadStatus::isHoming()
{
  return homing_;
}
mcBOOL FbReadStatus::isStandStill()
{
  return standstill_;
}
mcBOOL FbReadStatus::isDiscretMotion()
{
  return discrete_motion_;
}
mcBOOL FbReadStatus::isContinuousMotion()
{
  return continuous_motion_;
}
mcBOOL FbReadStatus::isSynchronizedMotion()
{
  return synchronized_motion_;
}

MC_ERROR_CODE FbReadStatus::onExecution()
{
  switch (axis_->getAxisState())
  {
    case mcErrorStop: {
      error_stop_ = mcTRUE;
      disabled_ = stopping_ = homing_ = standstill_ = discrete_motion_ =
          continuous_motion_ = synchronized_motion_ = mcFALSE;
    }
    break;
    case mcDisabled: {
      disabled_   = mcTRUE;
      error_stop_ = stopping_ = homing_ = standstill_ = discrete_motion_ =
          continuous_motion_ = synchronized_motion_ = mcFALSE;
    }
    break;
    case mcStopping: {
      stopping_   = mcTRUE;
      error_stop_ = disabled_ = homing_ = standstill_ = discrete_motion_ =
          continuous_motion_ = synchronized_motion_ = mcFALSE;
    }
    break;
    case mcHoming: {
      homing_     = mcTRUE;
      error_stop_ = disabled_ = stopping_ = standstill_ = discrete_motion_ =
          continuous_motion_ = synchronized_motion_ = mcFALSE;
    }
    break;
    case mcStandstill: {
      standstill_ = mcTRUE;
      error_stop_ = disabled_ = stopping_ = homing_ = discrete_motion_ =
          continuous_motion_ = synchronized_motion_ = mcFALSE;
    }
    break;
    case mcDiscreteMotion: {
      discrete_motion_ = mcTRUE;
      error_stop_ = disabled_ = stopping_ = homing_ = standstill_ =
          continuous_motion_ = synchronized_motion_ = mcFALSE;
    }
    break;
    case mcContinuousMotion: {
      continuous_motion_ = mcTRUE;
      error_stop_ = disabled_ = stopping_ = homing_ = standstill_ =
          discrete_motion_ = synchronized_motion_ = mcFALSE;
    }
    break;
    case mcSynchronizedMotion: {
      synchronized_motion_ = mcTRUE;
      error_stop_ = disabled_ = stopping_ = homing_ = standstill_ =
          discrete_motion_ = continuous_motion_ = mcFALSE;
    }
    break;
    default:
      break;
  }

  return mcErrorCodeGood;
}

}  // namespace RTmotion
