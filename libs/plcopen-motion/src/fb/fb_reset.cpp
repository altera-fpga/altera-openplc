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

#include <RTmotion/fb/fb_reset.hpp>

namespace RTmotion
{
MC_ERROR_CODE FbReset::onExecution()
{
  if (!axis_->getAxisError())
  {
    done_ = mcTRUE;
  }
  else
  {
    DEBUG_PRINT("FbReset::onExecution, reset error\n");
    axis_->resetError(enable_);

    if (axis_->powerTriggered() == mcTRUE && axis_->powerOn() == mcTRUE)
      if (axis_->getAxisState() == mcStandstill)
        done_ = mcTRUE;

    if (axis_->powerOn() == mcFALSE)
      if (axis_->getAxisState() == mcDisabled)
        done_ = mcTRUE;
  }

  return mcErrorCodeGood;
  ;
}

}  // namespace RTmotion
