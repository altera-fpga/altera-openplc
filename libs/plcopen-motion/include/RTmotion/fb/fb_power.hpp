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

#include <RTmotion/fb/fb_axis_admin.hpp>

namespace RTmotion
{
/**
 * @brief Function block base for single axis motion
 */
class FbPower : public FbAxisAdmin
{
public:
  FbPower();
  ~FbPower() override = default;

  // Functions for addressing inputs
  void setEnablePositive(mcBOOL enable_positive);
  void setEnableNegative(mcBOOL enable_negative);

  mcBOOL getPowerStatus();

  MC_ERROR_CODE onExecution() override;
  MC_ERROR_CODE onFallingEdgeExecution() override;

protected:
  /// Inputs
  VAR_INPUT mcBOOL enable_positive_;
  VAR_INPUT mcBOOL enable_negative_;
};
}  // namespace RTmotion
