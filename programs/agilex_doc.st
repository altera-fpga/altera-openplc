(* ##################################################################################*)
(* Copyright (C) 2025 Altera Corporation                                             *)
(* SPDX-License-Identifier: GPL-3.0-or-later                                         *)
(* ##################################################################################*)

FUNCTION_BLOCK OnOffIntervalTimer
  VAR_INPUT
    ON_TIME : TIME;
    OFF_TIME : TIME;
  END_VAR
  VAR_OUTPUT
    ACTIVE  : BOOL;
  END_VAR
  VAR
    LATCH : RS;
    ON_INTERVAL : TP;
    OFF_INTERVAL : TOF;
  END_VAR

  LATCH(S := NOT OFF_INTERVAL.Q, R1 := ON_INTERVAL.Q);
  ON_INTERVAL(IN := LATCH.Q1, PT := ON_TIME);
  OFF_INTERVAL(IN := ON_INTERVAL.Q, PT := OFF_TIME);
  ACTIVE := ON_INTERVAL.Q;
END_FUNCTION_BLOCK

PROGRAM prog0
  VAR
     MOTOR_PULSE0 : OnOffIntervalTimer;
  END_VAR
  VAR
     AXIS_0_HALT : MC_HALT;
     AXIS_1_HALT : MC_HALT;
     AXIS_0_SET_VEL : MC_MOVEVELOCITY;
     AXIS_1_SET_VEL : MC_MOVEVELOCITY;
     AXIS_0_READ_VEL : MC_READACTUALVELOCITY;
     AXIS_1_READ_VEL : MC_READACTUALVELOCITY;
     AXIS_0_POWER : MC_POWER;
     AXIS_1_POWER : MC_POWER;
  END_VAR
  VAR
     AXIS_0_VELOCITY AT %MD0 : REAL := 0.0;
     AXIS_1_VELOCITY AT %MD1 : REAL := 0.0;
  END_VAR

  AXIS_0_POWER(Axis := 0,
               Enable := TRUE,
               EnablePositive := TRUE,
               EnableNegative := TRUE);

  AXIS_1_POWER(Axis := 1,
               Enable := TRUE,
               EnablePositive := TRUE,
               EnableNegative := TRUE);

  MOTOR_PULSE0(ON_TIME := T#20S, OFF_TIME := T#5S);

  AXIS_0_SET_VEL(Axis := 0,
                 Execute := AXIS_0_POWER.Status AND AXIS_0_POWER.Valid AND MOTOR_PULSE0.ACTIVE,
                 Velocity := 50.0,
                 Acceleration := 20000.0,
                 Deceleration := 20000.0,
                 Jerk := 100000.0);

  AXIS_1_SET_VEL(Axis := 1,
                 Execute := AXIS_1_POWER.Status AND AXIS_1_POWER.Valid AND MOTOR_PULSE0.ACTIVE,
                 Velocity := 80.0,
                 Acceleration := 20000.0,
                 Deceleration := 20000.0,
                 Jerk := 100000.0);

  AXIS_0_HALT(Axis := 0,
              Execute := AXIS_0_POWER.Status AND AXIS_0_POWER.Valid AND NOT MOTOR_PULSE0.ACTIVE,
              Deceleration := 20000.0,
              Jerk := 100000.0);

  AXIS_1_HALT(Axis := 1,
              Execute := AXIS_1_POWER.Status AND AXIS_1_POWER.Valid AND NOT MOTOR_PULSE0.ACTIVE,
              Deceleration := 20000.0,
              Jerk := 100000.0);

  AXIS_0_READ_VEL(Axis := 0,
             Enable := AXIS_0_POWER.Status AND AXIS_0_POWER.Valid);

  AXIS_1_READ_VEL(Axis := 1,
             Enable := AXIS_1_POWER.Status AND AXIS_1_POWER.Valid);

  AXIS_0_VELOCITY := AXIS_0_READ_VEL.Velocity;
  AXIS_1_VELOCITY := AXIS_1_READ_VEL.Velocity;

END_PROGRAM

CONFIGURATION Config0
  RESOURCE Res0 ON PLC
    TASK Main(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH Main : prog0;      
  END_RESOURCE
END_CONFIGURATION
