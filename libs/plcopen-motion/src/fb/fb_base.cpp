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

#include <RTmotion/fb/fb_base.hpp>

namespace RTmotion
{
FunctionBlock::FunctionBlock() : axis_(nullptr)
{
}

FunctionBlock::FunctionBlock(const FunctionBlock& fb)
{
  axis_ = fb.axis_;
}

FunctionBlock& FunctionBlock::operator=(const FunctionBlock& fb)
{
  if (this != &fb)
  {
    axis_ = fb.axis_;
  }
  return *this;
}

FunctionBlock::~FunctionBlock()
{
  axis_ = nullptr;
}

void FunctionBlock::setAxis(AXIS_REF axis)
{
  axis_ = axis;
}

void FunctionBlock::runCycle()
{
}

// Functions for working on different status
MC_ERROR_CODE FunctionBlock::onRisingEdgeExecution()
{
  return mcErrorCodeGood;
}

MC_ERROR_CODE FunctionBlock::onFallingEdgeExecution()
{
  return mcErrorCodeGood;
}

MC_ERROR_CODE FunctionBlock::onExecution()
{
  return mcErrorCodeGood;
}

MC_ERROR_CODE FunctionBlock::afterFallingEdgeExecution()
{
  return mcErrorCodeGood;
}

void FunctionBlock::onError(MC_ERROR_CODE /*error_code*/)
{
}

}  // namespace RTmotion
