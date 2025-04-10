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

#include <RTmotion/fb/fb_axis_node.hpp>
#include <RTmotion/logging.hpp>

namespace RTmotion
{
FbAxisNode::FbAxisNode()
  : execute_(mcFALSE)
  , done_(mcFALSE)
  , busy_(mcFALSE)
  , active_(mcFALSE)
  , command_aborted_(mcFALSE)
  , error_(mcFALSE)
  , error_id_(mcErrorCodeGood)
  , buffer_mode_(mcBuffered)
  , output_flag_(mcFALSE)
{
}

void FbAxisNode::syncStatus(mcBOOL done, mcBOOL busy, mcBOOL active,
                            mcBOOL cmd_aborted, mcBOOL error,
                            MC_ERROR_CODE error_id)
{
  done_            = done;
  busy_            = busy;
  active_          = active;
  command_aborted_ = cmd_aborted;
  error_           = error;
  error_id_        = error_id;

  output_flag_ = execute_ == mcTRUE ? mcFALSE : mcTRUE;
  DEBUG_PRINT("FbAxisNode::syncStatus %s\n",
              done_ == mcTRUE ? "mcTRUE" : "mcFALSE");
}

mcBOOL FbAxisNode::isEnabled()
{
  return execute_;
}

mcBOOL FbAxisNode::isDone()
{
  return done_;
}

mcBOOL FbAxisNode::isBusy()
{
  return busy_;
}

mcBOOL FbAxisNode::isActive()
{
  return active_;
}

mcBOOL FbAxisNode::isAborted()
{
  return command_aborted_;
}

mcBOOL FbAxisNode::isError()
{
  DEBUG_PRINT("FbAxisNode::isError %s\n",
              error_ == mcTRUE ? "mcTRUE" : "mcFALSE");
  return error_;
}

MC_ERROR_CODE FbAxisNode::getErrorID()
{
  return error_id_;
}

}  // namespace RTmotion
