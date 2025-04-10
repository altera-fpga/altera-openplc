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

#include <RTmotion/algorithm/scurve_planner.hpp>
#include <ruckig/ruckig.hpp>

#define RUCKIG_DEFAULT_FREQUENCY 0.001
#define RUCKIG_AXIS_NUM 1

namespace trajectory_processing
{
class RuckigPlanner : public ScurvePlanner
{
public:
  RuckigPlanner()  = default;
  ~RuckigPlanner() = default;

  RTmotion::MC_ERROR_CODE plan() override;
  double* getWaypoint(double t) override;
  void setFrequency(double f) override;

  ruckig::Ruckig<RUCKIG_AXIS_NUM> otg_ =
      ruckig::Ruckig<RUCKIG_AXIS_NUM>(RUCKIG_DEFAULT_FREQUENCY);
  ruckig::InputParameter<RUCKIG_AXIS_NUM> input_;
  ruckig::OutputParameter<RUCKIG_AXIS_NUM> output_;
};

}  // namespace trajectory_processing
