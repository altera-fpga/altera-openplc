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

/* ---------------------------------------------------
    Headers of firmware functions and function blocks
            invoked from the PLC project
   --------------------------------------------------- */

#ifndef INCLUDING_RTMOTION_HEADERS

// ENUM: MC_DIRECTION 
typedef enum _MC_DIRECTION
{
    mcPositiveDirection = 1,
    mcShortestWay = 2,
    mcNegativeDirection = 3,
    mcCurrentDirection = 4
}
MC_DIRECTION;

// ENUM: MC_SERVO_CONTROL_MODE 
typedef enum _MC_SERVO_CONTROL_MODE
{
    mcServoControlModePosition = 0,
    mcServoControlModeVelocity = 1,
    mcServoControlModeTorque = 2
}
MC_SERVO_CONTROL_MODE;


// ENUM: MC_AXIS_STATES 
typedef enum _MC_AXIS_STATES
{
    mcDisabled = 0,
    mcStandstill = 1,
    mcHoming = 2,
    mcDiscreteMotion = 3,
    mcContinuousMotion = 4,
    mcSynchronizedMotion = 5,
    mcStopping = 6,
    mcErrorStop = 7
}
MC_AXIS_STATES;

// ENUM: MC_BUFFER_MODE 
typedef enum _MC_BUFFER_MODE
{
    mcAborting = 0,
    mcBuffered = 1,
    mcBlendingLow = 2,    // The velocity is blended with the lowest velocity of both FBs 
    mcBlendingPrevious = 3,    // The velocity is blended with the velocity of the first FB 
    mcBlendingNext = 4,    // The velocity is blended with velocity of the second FB 
    mcBlendingHigh = 5    // The velocity is blended with highest velocity of both FBs 
}
MC_BUFFER_MODE;

// MC_SetPosition mode 
typedef enum _MC_SET_POSITION_MODE
{
  mcSetPositionModeRelative  = 0,
  mcSetPositionModeAbsolute  = 1
}
MC_SET_POSITION_MODE;

#endif //INCLUDING_RTMOTION_HEADERS

#pragma pack(1)
/* STRUCT: MOTOR_CONFIG */
typedef struct _MOTOR_CONFIG
{
    char *EniFile;
    unsigned long int PerCycleEncoder;
}
MOTOR_CONFIG;
#pragma pack ()

#pragma pack(1)
/* STRUCT: AXIS_REF */
typedef struct _STRU_AXIS_REF
{
    unsigned short AxisId;
    char AxisName[33];
}
STRU_AXIS_REF;
#pragma pack ()

#pragma pack(1)
/* FUNCTION BLOCK: MC_Halt */
typedef struct _FB_MC_HALT
{
    /* VAR */
    unsigned char * _FbInst;
    unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
    STRU_AXIS_REF Axis;
    unsigned char Execute;
    double Deceleration;
    double Jerk;
    MC_BUFFER_MODE BufferMode;
    /* END_VAR */

    /* VAR_OUTPUT */
    unsigned char Done;
    unsigned char Busy;
    unsigned char Active;
    unsigned char CommandAborted;
    unsigned char Error;
    unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_HALT;
#pragma pack ()

extern void MC_Halt( FB_MC_HALT * frame );

/* FUNCTION BLOCK: MC_MoveAbsolute */
#pragma pack(1)
typedef struct _FB_MC_MOVEABSOLUTE
{
    /* VAR */
    unsigned char * _FbInst;
    unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
    STRU_AXIS_REF Axis;
    unsigned char Execute;
    unsigned char ContinuousUpdate;
    double Position;
    double Velocity;
    double Acceleration;
    double Deceleration;
    double Jerk;
    MC_DIRECTION Direction;
    MC_BUFFER_MODE BufferMode;
    /* END_VAR */

    /* VAR_OUTPUT */
    unsigned char Done;
    unsigned char Busy;
    unsigned char Active;
    unsigned char CommandAborted;
    unsigned char Error;
    unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_MOVEABSOLUTE;
#pragma pack ()

extern void MC_MoveAbsolute( FB_MC_MOVEABSOLUTE * frame );

/* FUNCTION BLOCK: MC_MoveAdditive */
#pragma pack(1)
typedef struct _FB_MC_MOVEADDITIVE
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Execute;
        unsigned char ContinuousUpdate;
        double Distance;
        double Velocity;
        double Acceleration;
        double Deceleration;
        double Jerk;
        MC_BUFFER_MODE BufferMode;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char Done;
        unsigned char Busy;
        unsigned char Active;
        unsigned char CommandAborted;
        unsigned char Error;
        unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_MOVEADDITIVE;
#pragma pack ()

extern void MC_MoveAdditive( FB_MC_MOVEADDITIVE * frame );

/* FUNCTION BLOCK: MC_MoveRelative */
#pragma pack(1)
typedef struct _FB_MC_MOVERELATIVE
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Execute;
        unsigned char ContinuousUpdate;
        double Distance;
        double Velocity;
        double Acceleration;
        double Deceleration;
        double Jerk;
        MC_BUFFER_MODE BufferMode;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char Done;
        unsigned char Busy;
        unsigned char Active;
        unsigned char CommandAborted;
        unsigned char Error;
        unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_MOVERELATIVE;
#pragma pack ()

extern void MC_MoveRelative( FB_MC_MOVERELATIVE * frame );

/* FUNCTION BLOCK: MC_MoveVelocity */
#pragma pack(1)
typedef struct _FB_MC_MOVEVELOCITY
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Execute;
        unsigned char ContinuousUpdate;
        double Velocity;
        double Acceleration;
        double Deceleration;
        double Jerk;
        MC_DIRECTION Direction;
        MC_BUFFER_MODE BufferMode;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char InVelocity;
        unsigned char Busy;
        unsigned char Active;
        unsigned char CommandAborted;
        unsigned char Error;
        unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_MOVEVELOCITY;
#pragma pack ()

extern void MC_MoveVelocity( FB_MC_MOVEVELOCITY * frame );

/* FUNCTION BLOCK: MC_Power */
#pragma pack(1)
typedef struct _FB_MC_POWER
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Enable;
        unsigned char EnablePositive;
        unsigned char EnableNegative;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char Status;
        unsigned char Valid;
        unsigned char Error;
        unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_POWER;
#pragma pack ()

extern void MC_Power( FB_MC_POWER * frame );

/* FUNCTION BLOCK: MC_ReadActualPosition */
#pragma pack(1)
typedef struct _FB_MC_READACTUALPOSITION
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Enable;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char Valid;
        unsigned char Busy;
        unsigned char Error;
        unsigned short ErrorID;
        double Position;
    /* END_VAR */

}
FB_MC_READACTUALPOSITION;
#pragma pack ()

extern void MC_ReadActualPosition( FB_MC_READACTUALPOSITION * frame );

/* FUNCTION BLOCK: MC_ReadActualVelocity */
#pragma pack(1)
typedef struct _FB_MC_READACTUALVELOCITY
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Enable;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char Valid;
        unsigned char Busy;
        unsigned char Error;
        unsigned short ErrorID;
        double Velocity;
    /* END_VAR */

}
FB_MC_READACTUALVELOCITY;
#pragma pack ()

extern void MC_ReadActualVelocity( FB_MC_READACTUALVELOCITY * frame );

/* FUNCTION BLOCK: MC_ReadAxisError */
#pragma pack(1)
typedef struct _FB_MC_READAXISERROR
{
/* VAR */
    unsigned char * _FbInst;
    unsigned char _FbMem[1024];
/* END_VAR */

/* VAR_INPUT */
    STRU_AXIS_REF Axis;
    unsigned char Enable;
/* END_VAR */

/* VAR_OUTPUT */
    unsigned char Valid;
    unsigned char Busy;
    unsigned char Error;
    unsigned short ErrorID;
    unsigned short AxisErrorID;
/* END_VAR */

}
FB_MC_READAXISERROR;

#pragma pack ()
extern void MC_ReadAxisError( FB_MC_READAXISERROR * frame );

/* FUNCTION BLOCK: MC_ReadStatus */
#pragma pack(1)
typedef struct _FB_MC_READSTATUS
{
/* VAR */
    unsigned char * _FbInst;
    unsigned char _FbMem[1024];
/* END_VAR */

/* VAR_INPUT */
    STRU_AXIS_REF Axis;
    unsigned char Enable;
/* END_VAR */

/* VAR_OUTPUT */
    unsigned char Valid;
    unsigned char Busy;
    unsigned char Error;
    unsigned short ErrorID;
    unsigned char ErrorStop;
    unsigned char Disabled;
    unsigned char Stopping;
    unsigned char Homing;
    unsigned char Standstill;
    unsigned char DiscreteMotion;
    unsigned char ContinuousMotion;
    unsigned char SynchronizedMotion;
/* END_VAR */

}
FB_MC_READSTATUS;
#pragma pack ()

extern void MC_ReadStatus( FB_MC_READSTATUS * frame );

/* FUNCTION BLOCK: MC_Reset */
#pragma pack(1)
typedef struct _FB_MC_RESET
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Execute;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char Done;
        unsigned char Busy;
        unsigned char Error;
        unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_RESET;
#pragma pack ()

extern void MC_Reset( FB_MC_RESET * frame );

/* FUNCTION BLOCK: MC_Stop */
#pragma pack(1)
typedef struct _FB_MC_STOP
{
    /* VAR */
        unsigned char * _FbInst;
        unsigned char _FbMem[1024];
    /* END_VAR */

    /* VAR_INPUT */
        STRU_AXIS_REF Axis;
        unsigned char Execute;
        double Deceleration;
        double Jerk;
    /* END_VAR */

    /* VAR_OUTPUT */
        unsigned char Done;
        unsigned char Busy;
        unsigned char CommandAborted;
        unsigned char Error;
        unsigned short ErrorID;
    /* END_VAR */

}
FB_MC_STOP;
#pragma pack ()

extern void MC_Stop( FB_MC_STOP * frame );

