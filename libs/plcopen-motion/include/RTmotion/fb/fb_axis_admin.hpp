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

#include <RTmotion/fb/fb_base.hpp>

namespace RTmotion
{
/**
 * @brief Function block base for single axis motion
 */
class FbAxisAdmin : public FunctionBlock
{
public:
  FbAxisAdmin();
  ~FbAxisAdmin() override = default;

  // Functions for addressing inputs
  virtual void setEnable(mcBOOL enable);

  virtual mcBOOL isEnabled();
  virtual mcBOOL isDone();
  virtual mcBOOL isValid();
  virtual mcBOOL isBusy();
  virtual mcBOOL isError();
  virtual MC_ERROR_CODE getErrorID();

  void runCycle() override;
  void onError(MC_ERROR_CODE error_code) override;

protected:
  // Inputs
  VAR_INPUT mcBOOL enable_;

  // Outputs
  VAR_OUTPUT mcBOOL done_;
  VAR_OUTPUT mcBOOL valid_;
  VAR_OUTPUT mcBOOL busy_;
  VAR_OUTPUT mcBOOL error_;
  VAR_OUTPUT MC_ERROR_CODE error_id_;

  mcBOOL enabled_;
};
}  // namespace RTmotion
