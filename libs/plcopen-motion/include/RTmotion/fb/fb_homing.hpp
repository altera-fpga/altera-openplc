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

#include <RTmotion/global.hpp>
#include <RTmotion/fb/fb_axis_motion.hpp>

namespace RTmotion
{
/**
 * @brief Function block MC_Homing
 */
class FbHoming : public FbAxisMotion
{
public:
  FbHoming();
  ~FbHoming() override = default;

  typedef enum
  {
    mcHomingStill,
    mcHomingSearch,
    mcHomingSearchBack,
    mcHomingFinish,
    mcHomingHalt
  } MC_HOMING_STATE;

  virtual void setRefSignal(mcBOOL signal);
  virtual void setLimitNegSignal(mcBOOL signal);
  virtual void setLimitPosSignal(mcBOOL signal);
  virtual void setLimitOffset(mcLREAL offset);

  void syncStatus(mcBOOL done, mcBOOL busy, mcBOOL active, mcBOOL cmd_aborted,
                  mcBOOL error, MC_ERROR_CODE error_id) override;

  MC_ERROR_CODE onRisingEdgeExecution() override;
  MC_ERROR_CODE onExecution() override;
  MC_ERROR_CODE onFallingEdgeExecution() override;

protected:
  VAR_INPUT mcBOOL abs_switch_signal_;
  VAR_INPUT mcBOOL limit_switch_neg_signal_;
  VAR_INPUT mcBOOL limit_switch_pos_signal_;
  VAR_INPUT mcLREAL limit_offset_;

  mcBOOL homing_reset_;
  mcBOOL reach_neg_limit_;
  mcBOOL reach_pos_limit_;
  mcLREAL neg_limit_;
  mcLREAL pos_limit_;

  MC_HOMING_STATE homing_state_;
};
}  // namespace RTmotion
