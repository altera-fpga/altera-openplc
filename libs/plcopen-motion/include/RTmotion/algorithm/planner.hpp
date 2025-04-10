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
#include <RTmotion/algorithm/offline_scurve_planner.hpp>
#include <RTmotion/algorithm/online_scurve_planner.hpp>
#include <RTmotion/algorithm/ruckig_planner.hpp>
#include <chrono>

using RTmotion::MC_ERROR_CODE;

namespace trajectory_processing
{
class AxisPlanner
{
public:
  AxisPlanner();

  AxisPlanner(const AxisPlanner& planner);

  AxisPlanner& operator=(const AxisPlanner& planner);

  virtual ~AxisPlanner();

  void setCondition(const ScurveCondition& condition,
                    const RTmotion::PLANNER_TYPE type);
  void setCondition(double start_pos, double end_pos, double start_vel,
                    double end_vel, double start_acc, double end_acc,
                    double duration, double vel_max, double acc_max,
                    double jerk_max, RTmotion::PLANNER_TYPE type);

  MC_ERROR_CODE planTrajectory();

  double* getTrajectoryPoint(double t);

  MC_ERROR_CODE onReplan();

  MC_ERROR_CODE onExecution(double t, double* pos_cmd, double* vel_cmd,
                            double* acc_cmd);

  const ScurveCondition& getScurveCondition() const;

  ScurveProfile& getScurveProfile();

  void setStartTime(double t);

  void setFrequency(double f);

  RTmotion::PLANNER_TYPE getType() const;

private:
  ScurvePlanner* scurve_planner_;
  ScurvePlannerOnLine online_planner_;
  ScurvePlannerOffLine offline_planner_;
  RuckigPlanner ruckig_planner_;
  double start_time_;
  RTmotion::PLANNER_TYPE type_;
};

}  // namespace trajectory_processing
