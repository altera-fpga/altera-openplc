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

namespace RTmotion
{
/**
 * @brief Function block base for single axis motion
 */
class FbAxisNode
{
public:
  FbAxisNode();
  virtual ~FbAxisNode() = default;

  // Functions for addressing outputs
  virtual void syncStatus(mcBOOL done, mcBOOL busy, mcBOOL active,
                          mcBOOL cmd_aborted, mcBOOL error,
                          MC_ERROR_CODE error_id);

  mcBOOL isEnabled();
  mcBOOL isDone();
  mcBOOL isBusy();
  mcBOOL isActive();
  mcBOOL isAborted();
  virtual mcBOOL isError();
  virtual MC_ERROR_CODE getErrorID();

  virtual mcLREAL getPosition()           = 0;
  virtual mcLREAL getVelocity()           = 0;
  virtual mcLREAL getTorque()             = 0;
  virtual mcLREAL getMaxProfileVel()      = 0;
  virtual mcLREAL getAcceleration()       = 0;
  virtual mcLREAL getDeceleration()       = 0;
  virtual mcLREAL getJerk()               = 0;
  virtual mcLREAL getDuration()           = 0;
  virtual MC_DIRECTION getDirection()     = 0;
  virtual MC_BUFFER_MODE getBufferMode()  = 0;
  virtual mcLREAL getTargetPosition()     = 0;
  virtual mcLREAL getTargetVelocity()     = 0;
  virtual mcLREAL getTargetAcceleration() = 0;
  virtual mcLREAL getStartPosition()      = 0;
  virtual mcLREAL getStartVelocity()      = 0;
  virtual mcLREAL getStartAcceleration()  = 0;
  virtual PLANNER_TYPE getPlannerType()   = 0;

protected:
  VAR_INPUT mcBOOL execute_;

  /// Outputs
  VAR_OUTPUT mcBOOL done_;
  VAR_OUTPUT mcBOOL busy_;
  VAR_OUTPUT mcBOOL active_;
  VAR_OUTPUT mcBOOL command_aborted_;
  VAR_OUTPUT mcBOOL error_;
  VAR_OUTPUT MC_ERROR_CODE error_id_;
  VAR_OUTPUT MC_BUFFER_MODE buffer_mode_;

  mcBOOL output_flag_;  /// Hold the output for another cycle
};
}  // namespace RTmotion
