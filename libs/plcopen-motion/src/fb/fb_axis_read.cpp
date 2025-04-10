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

#include <RTmotion/fb/fb_axis_read.hpp>

namespace RTmotion
{
FbAxisRead::FbAxisRead() : value_(0)
{
}

mcLREAL FbAxisRead::getFloatValue()
{
  return value_;
}

mcLREAL FbAxisRead::getAxisValue()
{
  return value_;
}

MC_ERROR_CODE FbAxisRead::onExecution()
{
  if (axis_->getAxisState() == mcErrorStop)
  {
    value_    = 0;
    error_    = mcTRUE;
    valid_    = mcFALSE;
    error_id_ = axis_->getAxisError();
    return mcErrorCodeAxisErrorStop;
  }

  error_ = mcFALSE;
  valid_ = mcTRUE;
  value_ = getAxisValue();
  return mcErrorCodeGood;
}

MC_ERROR_CODE FbAxisRead::onFallingEdgeExecution()
{
  value_ = 0;
  return mcErrorCodeGood;
}

}  // namespace RTmotion
