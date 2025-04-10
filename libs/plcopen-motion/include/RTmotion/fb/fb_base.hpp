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

#include <RTmotion/axis.hpp>
#include <RTmotion/logging.hpp>
#include <map>

namespace RTmotion
{
class Axis;

class FunctionBlock
{
public:
  FunctionBlock();

  FunctionBlock(const FunctionBlock& fb);

  FunctionBlock& operator=(const FunctionBlock& fb);

  virtual ~FunctionBlock();

  virtual void setAxis(AXIS_REF axis);

  virtual void runCycle();

  // Functions for working on different status
  virtual MC_ERROR_CODE onRisingEdgeExecution();

  virtual MC_ERROR_CODE onFallingEdgeExecution();

  virtual MC_ERROR_CODE onExecution();

  virtual MC_ERROR_CODE afterFallingEdgeExecution();

  virtual void onError(MC_ERROR_CODE error_code);

protected:
  /// AXIS_REF
  VAR_IN_OUT AXIS_REF axis_;
};

}  // namespace RTmotion
