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
#include <queue>
#include <RTmotion/fb/execution_node.hpp>

namespace RTmotion
{
class ExecutionNode;

class MotionKernel
{
public:
  MotionKernel();

  virtual ~MotionKernel();

  virtual void runCycle(const mcLREAL master_ref_pos,
                        const mcLREAL master_ref_vel, const mcLREAL pos,
                        const mcLREAL vel, MC_AXIS_STATES* state);

  void addFBToQueue(ExecutionNode* fb, mcLREAL current_pos, mcLREAL current_vel,
                    mcLREAL current_acc, mcLREAL end_acc);

  std::deque<ExecutionNode*>& getQueuedMotions();

  void getCommands(mcLREAL* pos_cmd, mcLREAL* vel_cmd, mcLREAL* acc_cmd);

  void setAllFBsAborted();

  void offsetAllFBs(mcLREAL home_pos);

private:
  std::deque<ExecutionNode*> fb_queue_;
  ExecutionNode* fb_hold_ = nullptr;
};

}  // namespace RTmotion
