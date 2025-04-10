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
 
/************************************************************************
 *                DECLARATION OF MOTION CONTROL BLOCKS                  *
************************************************************************/

#include <RTmotion/axis.hpp>
#include "motion.h"

// FUNCTION_BLOCK MC_POWER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,ENABLE)
  __DECLARE_VAR(BOOL,ENABLEPOSITIVE)
  __DECLARE_VAR(BOOL,ENABLENEGATIVE)

  __DECLARE_VAR(BOOL,STATUS)
  __DECLARE_VAR(BOOL,VALID)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_POWER frame;
} MC_POWER;


// FUNCTION_BLOCK STOP
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,EXECUTE)
  __DECLARE_VAR(REAL,DECELERATION)
  __DECLARE_VAR(REAL,JERK)

  __DECLARE_VAR(BOOL,DONE)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,COMMANDABORTED)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_STOP frame;
} MC_STOP;


// FUNCTION_BLOCK HALT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,EXECUTE)
  __DECLARE_VAR(REAL,DECELERATION)
  __DECLARE_VAR(REAL,JERK)
  __DECLARE_VAR(INT,BUFFERMODE)

  __DECLARE_VAR(BOOL,DONE)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ACTIVE)
  __DECLARE_VAR(BOOL,COMMANDABORTED)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_HALT frame;
} MC_HALT;


// FUNCTION_BLOCK RESET
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,EXECUTE)

  __DECLARE_VAR(BOOL,DONE)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_RESET frame;
} MC_RESET;


// FUNCTION_BLOCK MOVEVELOCITY
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,EXECUTE)
  __DECLARE_VAR(BOOL,CONTINUOUSUPDATE)
  __DECLARE_VAR(REAL,VELOCITY)
  __DECLARE_VAR(REAL,ACCELERATION)
  __DECLARE_VAR(REAL,DECELERATION)
  __DECLARE_VAR(REAL,JERK)
  __DECLARE_VAR(INT,DIRECTION)
  __DECLARE_VAR(INT,BUFFERMODE)

  __DECLARE_VAR(BOOL,INVELOCITY)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ACTIVE)
  __DECLARE_VAR(BOOL,COMMANDABORTED)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_MOVEVELOCITY frame;
} MC_MOVEVELOCITY;


// FUNCTION_BLOCK MOVERELATIVE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,EXECUTE)
  __DECLARE_VAR(BOOL,CONTINUOUSUPDATE)
  __DECLARE_VAR(REAL,DISTANCE)
  __DECLARE_VAR(REAL,VELOCITY)
  __DECLARE_VAR(REAL,ACCELERATION)
  __DECLARE_VAR(REAL,DECELERATION)
  __DECLARE_VAR(REAL,JERK)
  __DECLARE_VAR(INT,BUFFERMODE)

  __DECLARE_VAR(BOOL,DONE)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ACTIVE)
  __DECLARE_VAR(BOOL,COMMANDABORTED)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_MOVERELATIVE frame;
} MC_MOVERELATIVE;


// FUNCTION_BLOCK MOVEABSOLUTE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,EXECUTE)
  __DECLARE_VAR(BOOL,CONTINUOUSUPDATE)
  __DECLARE_VAR(REAL,POSITION)
  __DECLARE_VAR(REAL,VELOCITY)
  __DECLARE_VAR(REAL,ACCELERATION)
  __DECLARE_VAR(REAL,DECELERATION)
  __DECLARE_VAR(REAL,JERK)
  __DECLARE_VAR(INT,DIRECTION)
  __DECLARE_VAR(INT,BUFFERMODE)

  __DECLARE_VAR(BOOL,DONE)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ACTIVE)
  __DECLARE_VAR(BOOL,COMMANDABORTED)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_MOVEABSOLUTE frame;
} MC_MOVEABSOLUTE;


// FUNCTION_BLOCK MOVEADDITIVE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,EXECUTE)
  __DECLARE_VAR(BOOL,CONTINUOUSUPDATE)
  __DECLARE_VAR(REAL,DISTANCE)
  __DECLARE_VAR(REAL,VELOCITY)
  __DECLARE_VAR(REAL,ACCELERATION)
  __DECLARE_VAR(REAL,DECELERATION)
  __DECLARE_VAR(REAL,JERK)
  __DECLARE_VAR(INT,BUFFERMODE)

  __DECLARE_VAR(BOOL,DONE)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ACTIVE)
  __DECLARE_VAR(BOOL,COMMANDABORTED)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_MOVEADDITIVE frame;
} MC_MOVEADDITIVE;


// FUNCTION_BLOCK READACTUALVELOCITY
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,ENABLE)

  __DECLARE_VAR(BOOL,VALID)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)
  __DECLARE_VAR(REAL,VELOCITY)

  // FB private variables - TEMP, private and located variables
  FB_MC_READACTUALVELOCITY frame;
} MC_READACTUALVELOCITY;

// FUNCTION_BLOCK READACTUALPOSITION
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,ENABLE)

  __DECLARE_VAR(BOOL,VALID)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)
  __DECLARE_VAR(REAL,POSITION)

  // FB private variables - TEMP, private and located variables
  FB_MC_READACTUALPOSITION frame;
} MC_READACTUALPOSITION;

// FUNCTION_BLOCK READAXISERROR
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,ENABLE)

  __DECLARE_VAR(BOOL,VALID)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)
  __DECLARE_VAR(WORD,AXISERRORID)

  // FB private variables - TEMP, private and located variables
  FB_MC_READAXISERROR frame;
} MC_READAXISERROR;

// FUNCTION_BLOCK READSTATUS
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,AXIS)
  __DECLARE_VAR(BOOL,ENABLE)

  __DECLARE_VAR(BOOL,VALID)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(BOOL,ERROR)
  __DECLARE_VAR(WORD,ERRORID)
  __DECLARE_VAR(BOOL,ERRORSTOP)
  __DECLARE_VAR(BOOL,DISABLED)
  __DECLARE_VAR(BOOL,STOPPING)
  __DECLARE_VAR(BOOL,HOMING)
  __DECLARE_VAR(BOOL,STANDSTILL)
  __DECLARE_VAR(BOOL,DISCRETEMOTION)
  __DECLARE_VAR(BOOL,CONTINUOUSMOTION)
  __DECLARE_VAR(BOOL,SYNCHRONIZEDMOTION)

  // FB private variables - TEMP, private and located variables
  FB_MC_READSTATUS frame;
} MC_READSTATUS;

static void MC_POWER_init__(MC_POWER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ENABLEPOSITIVE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ENABLENEGATIVE,__BOOL_LITERAL(FALSE),retain)

  __INIT_VAR(data__->STATUS,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->VALID,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_POWER_body__(MC_POWER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Enable = __GET_VAR(data__->ENABLE);
  data__->frame.EnablePositive = __GET_VAR(data__->ENABLEPOSITIVE);
  data__->frame.EnableNegative = __GET_VAR(data__->ENABLENEGATIVE);

  MC_Power(&data__->frame);

  __SET_VAR(,data__->STATUS,,data__->frame.Status);
  __SET_VAR(,data__->VALID,,data__->frame.Valid);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_POWER_body__()


static void MC_STOP_init__(MC_STOP *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->EXECUTE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DECELERATION,0,retain)
  __INIT_VAR(data__->JERK,0,retain)

  __INIT_VAR(data__->DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->COMMANDABORTED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_STOP_body__(MC_STOP *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Execute = __GET_VAR(data__->EXECUTE);
  data__->frame.Deceleration = __GET_VAR(data__->DECELERATION);
  data__->frame.Jerk = __GET_VAR(data__->JERK);

  MC_Stop(&data__->frame);

  __SET_VAR(,data__->DONE,,data__->frame.Done);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->COMMANDABORTED,,data__->frame.CommandAborted);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_STOP_body__()


static void MC_HALT_init__(MC_HALT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->EXECUTE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DECELERATION,0,retain)
  __INIT_VAR(data__->JERK,0,retain)
  __INIT_VAR(data__->BUFFERMODE,0,retain)

  __INIT_VAR(data__->DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ACTIVE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->COMMANDABORTED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_HALT_body__(MC_HALT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Execute = __GET_VAR(data__->EXECUTE);
  data__->frame.Deceleration = __GET_VAR(data__->DECELERATION);
  data__->frame.Jerk = __GET_VAR(data__->JERK);
  data__->frame.BufferMode = (_MC_BUFFER_MODE)(__GET_VAR(data__->BUFFERMODE));

  MC_Halt(&data__->frame);

  __SET_VAR(,data__->DONE,,data__->frame.Done);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ACTIVE,,data__->frame.Active);
  __SET_VAR(,data__->COMMANDABORTED,,data__->frame.CommandAborted);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_HALT_body__()


static void MC_RESET_init__(MC_RESET *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->EXECUTE,__BOOL_LITERAL(FALSE),retain)

  __INIT_VAR(data__->DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_RESET_body__(MC_RESET *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Execute = __GET_VAR(data__->EXECUTE);

  MC_Reset(&data__->frame);

  __SET_VAR(,data__->DONE,,data__->frame.Done);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_RESET_body__()


static void MC_MOVEVELOCITY_init__(MC_MOVEVELOCITY *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->EXECUTE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CONTINUOUSUPDATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->VELOCITY,0,retain)
  __INIT_VAR(data__->ACCELERATION,0,retain)
  __INIT_VAR(data__->DECELERATION,0,retain)
  __INIT_VAR(data__->JERK,0,retain)
  __INIT_VAR(data__->DIRECTION,1,retain)
  __INIT_VAR(data__->BUFFERMODE,0,retain)

  __INIT_VAR(data__->INVELOCITY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ACTIVE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->COMMANDABORTED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_MOVEVELOCITY_body__(MC_MOVEVELOCITY *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Execute = __GET_VAR(data__->EXECUTE);
  data__->frame.ContinuousUpdate = __GET_VAR(data__->CONTINUOUSUPDATE);
  data__->frame.Velocity = __GET_VAR(data__->VELOCITY);
  data__->frame.Acceleration = __GET_VAR(data__->ACCELERATION);
  data__->frame.Deceleration = __GET_VAR(data__->DECELERATION);
  data__->frame.Jerk = __GET_VAR(data__->JERK);
  data__->frame.Direction = (MC_DIRECTION)(__GET_VAR(data__->DIRECTION));
  data__->frame.BufferMode = (MC_BUFFER_MODE)(__GET_VAR(data__->BUFFERMODE));

  MC_MoveVelocity(&data__->frame);

  __SET_VAR(,data__->INVELOCITY,,data__->frame.InVelocity);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ACTIVE,,data__->frame.Active);
  __SET_VAR(,data__->COMMANDABORTED,,data__->frame.CommandAborted);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_MOVEVELOCITY_body__()


static void MC_MOVERELATIVE_init__(MC_MOVERELATIVE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->EXECUTE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CONTINUOUSUPDATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DISTANCE,0,retain)
  __INIT_VAR(data__->VELOCITY,0,retain)
  __INIT_VAR(data__->ACCELERATION,0,retain)
  __INIT_VAR(data__->DECELERATION,0,retain)
  __INIT_VAR(data__->JERK,0,retain)
  __INIT_VAR(data__->BUFFERMODE,0,retain)

  __INIT_VAR(data__->DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ACTIVE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->COMMANDABORTED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_MOVERELATIVE_body__(MC_MOVERELATIVE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Execute = __GET_VAR(data__->EXECUTE);
  data__->frame.ContinuousUpdate = __GET_VAR(data__->CONTINUOUSUPDATE);
  data__->frame.Distance = __GET_VAR(data__->DISTANCE);
  data__->frame.Velocity = __GET_VAR(data__->VELOCITY);
  data__->frame.Acceleration = __GET_VAR(data__->ACCELERATION);
  data__->frame.Deceleration = __GET_VAR(data__->DECELERATION);
  data__->frame.Jerk = __GET_VAR(data__->JERK);
  data__->frame.BufferMode = (MC_BUFFER_MODE)(__GET_VAR(data__->BUFFERMODE));

  MC_MoveRelative(&data__->frame);

  __SET_VAR(,data__->DONE,,data__->frame.Done);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ACTIVE,,data__->frame.Active);
  __SET_VAR(,data__->COMMANDABORTED,,data__->frame.CommandAborted);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_MOVERELATIVE_body__()


static void MC_MOVEABSOLUTE_init__(MC_MOVEABSOLUTE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->EXECUTE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CONTINUOUSUPDATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->POSITION,0,retain)
  __INIT_VAR(data__->VELOCITY,0,retain)
  __INIT_VAR(data__->ACCELERATION,0,retain)
  __INIT_VAR(data__->DECELERATION,0,retain)
  __INIT_VAR(data__->JERK,0,retain)
  __INIT_VAR(data__->DIRECTION,1,retain)
  __INIT_VAR(data__->BUFFERMODE,0,retain)

  __INIT_VAR(data__->DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ACTIVE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->COMMANDABORTED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_MOVEABSOLUTE_body__(MC_MOVEABSOLUTE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Execute = __GET_VAR(data__->EXECUTE);
  data__->frame.ContinuousUpdate = __GET_VAR(data__->CONTINUOUSUPDATE);
  data__->frame.Position = __GET_VAR(data__->POSITION);
  data__->frame.Velocity = __GET_VAR(data__->VELOCITY);
  data__->frame.Acceleration = __GET_VAR(data__->ACCELERATION);
  data__->frame.Deceleration = __GET_VAR(data__->DECELERATION);
  data__->frame.Jerk = __GET_VAR(data__->JERK);
  data__->frame.Direction = (MC_DIRECTION)(__GET_VAR(data__->DIRECTION));
  data__->frame.BufferMode = (MC_BUFFER_MODE)(__GET_VAR(data__->BUFFERMODE));

  MC_MoveAbsolute(&data__->frame);

  __SET_VAR(,data__->DONE,,data__->frame.Done);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ACTIVE,,data__->frame.Active);
  __SET_VAR(,data__->COMMANDABORTED,,data__->frame.CommandAborted);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_MOVEABSOLUTE_body__()

static void MC_MOVEADDITIVE_init__(MC_MOVEADDITIVE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->EXECUTE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CONTINUOUSUPDATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DISTANCE,0,retain)
  __INIT_VAR(data__->VELOCITY,0,retain)
  __INIT_VAR(data__->ACCELERATION,0,retain)
  __INIT_VAR(data__->DECELERATION,0,retain)
  __INIT_VAR(data__->JERK,0,retain)
  __INIT_VAR(data__->BUFFERMODE,0,retain)

  __INIT_VAR(data__->DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ACTIVE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->COMMANDABORTED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_MOVEADDITIVE_body__(MC_MOVEADDITIVE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Execute = __GET_VAR(data__->EXECUTE);
  data__->frame.ContinuousUpdate = __GET_VAR(data__->CONTINUOUSUPDATE);
  data__->frame.Distance = __GET_VAR(data__->DISTANCE);
  data__->frame.Velocity = __GET_VAR(data__->VELOCITY);
  data__->frame.Acceleration = __GET_VAR(data__->ACCELERATION);
  data__->frame.Deceleration = __GET_VAR(data__->DECELERATION);
  data__->frame.Jerk = __GET_VAR(data__->JERK);
  data__->frame.BufferMode = (MC_BUFFER_MODE)(__GET_VAR(data__->BUFFERMODE));

  MC_MoveAdditive(&data__->frame);

  __SET_VAR(,data__->DONE,,data__->frame.Done);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ACTIVE,,data__->frame.Active);
  __SET_VAR(,data__->COMMANDABORTED,,data__->frame.CommandAborted);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
} // MC_MOVEABSOLUTE_body__()


static void MC_READACTUALVELOCITY_init__(MC_READACTUALVELOCITY *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->ENABLE,__BOOL_LITERAL(FALSE),retain)

  __INIT_VAR(data__->VALID,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
  __INIT_VAR(data__->VELOCITY,0,retain)
}

// Code part
static void MC_READACTUALVELOCITY_body__(MC_READACTUALVELOCITY *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Enable = __GET_VAR(data__->ENABLE);

  MC_ReadActualVelocity(&data__->frame);

  __SET_VAR(,data__->VALID,,data__->frame.Valid);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
  __SET_VAR(,data__->VELOCITY,,data__->frame.Velocity);
} // MC_READACTUALVELOCITY_body__()

static void MC_READACTUALPOSITION_init__(MC_READACTUALPOSITION *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->ENABLE,__BOOL_LITERAL(FALSE),retain)

  __INIT_VAR(data__->VALID,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
  __INIT_VAR(data__->POSITION,0,retain)
}

// Code part
static void MC_READACTUALPOSITION_body__(MC_READACTUALPOSITION *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Enable = __GET_VAR(data__->ENABLE);

  MC_ReadActualPosition(&data__->frame);

  __SET_VAR(,data__->VALID,,data__->frame.Valid);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
  __SET_VAR(,data__->POSITION,,data__->frame.Position);
} // MC_READACTUALPOSITION_body__()

static void MC_READAXISERROR_init__(MC_READAXISERROR *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->ENABLE,__BOOL_LITERAL(FALSE),retain)

  __INIT_VAR(data__->VALID,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
  __INIT_VAR(data__->AXISERRORID,__WORD_LITERAL(0),retain)
}

// Code part
static void MC_READAXISERROR_body__(MC_READAXISERROR *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Enable = __GET_VAR(data__->ENABLE);

  MC_ReadAxisError(&data__->frame);

  __SET_VAR(,data__->VALID,,data__->frame.Valid);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
  __SET_VAR(,data__->AXISERRORID,,data__->frame.AxisErrorID);
} // MC_READAXISERROR_body__()

static void MC_READSTATUS_init__(MC_READSTATUS *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)

  __INIT_VAR(data__->AXIS,-1,retain)
  __INIT_VAR(data__->ENABLE,__BOOL_LITERAL(FALSE),retain)

  __INIT_VAR(data__->VALID,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERROR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORID,__WORD_LITERAL(0),retain)
  __INIT_VAR(data__->ERRORSTOP,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DISABLED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STOPPING,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HOMING,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STANDSTILL,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DISCRETEMOTION,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CONTINUOUSMOTION,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SYNCHRONIZEDMOTION,__BOOL_LITERAL(FALSE),retain)
}

// Code part
static void MC_READSTATUS_body__(MC_READSTATUS *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }

  data__->frame.Axis.AxisId = __GET_VAR(data__->AXIS,);
  data__->frame.Enable = __GET_VAR(data__->ENABLE);

  MC_ReadStatus(&data__->frame);

  __SET_VAR(,data__->VALID,,data__->frame.Valid);
  __SET_VAR(,data__->BUSY,,data__->frame.Busy);
  __SET_VAR(,data__->ERROR,,data__->frame.Error);
  __SET_VAR(,data__->ERRORID,,data__->frame.ErrorID);
  __SET_VAR(,data__->ERRORSTOP,,data__->frame.ErrorStop);
  __SET_VAR(,data__->DISABLED,,data__->frame.Disabled);
  __SET_VAR(,data__->STOPPING,,data__->frame.Stopping);
  __SET_VAR(,data__->HOMING,,data__->frame.Homing);
  __SET_VAR(,data__->STANDSTILL,,data__->frame.Standstill);
  __SET_VAR(,data__->DISCRETEMOTION,,data__->frame.DiscreteMotion);
  __SET_VAR(,data__->CONTINUOUSMOTION,,data__->frame.ContinuousMotion);
  __SET_VAR(,data__->SYNCHRONIZEDMOTION,,data__->frame.SynchronizedMotion);
} // MC_READSTATUS_body__()


