/*
 * Copyright (c) 2020 Intel Corporation
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

/**
 * @file function_block_test.cpp
 *
 * Maintainer: Yu Yan <yu.yan@intel.com>
 *
 */

#include <thread>
#include "gtest/gtest.h"
#include <RTmotion/axis.hpp>
#include <RTmotion/global.hpp>
#include <RTmotion/fb/fb_move_relative.hpp>
#include <RTmotion/fb/fb_move_velocity.hpp>
#include <RTmotion/fb/fb_move_absolute.hpp>
#include <RTmotion/fb/fb_move_additive.hpp>
#include <RTmotion/fb/fb_halt.hpp>
#include <RTmotion/fb/fb_stop.hpp>
#include <RTmotion/fb/fb_homing.hpp>
#include <RTmotion/fb/fb_power.hpp>
#include <RTmotion/fb/fb_read_actual_position.hpp>

using namespace RTmotion;

class FunctionBlockTest : public ::testing::Test
{
protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  FunctionBlockTest()
  {
    // You can do set-up work for each test here.
  }

  ~FunctionBlockTest() override
  {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override
  {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override
  {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
};

// Test MC_MoveRelative
TEST_F(FunctionBlockTest, DemoRelative)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveRelative fb_move_rel;
  fb_move_rel.setAxis(axis);
  fb_move_rel.setExecute(mcFALSE);
  fb_move_rel.setContinuousUpdate(mcFALSE);
  fb_move_rel.setDistance(3.14);
  fb_move_rel.setVelocity(1.57);
  fb_move_rel.setAcceleration(3.14);
  fb_move_rel.setDeceleration(3.14);
  fb_move_rel.setJerk(50);
  printf("Function block initialized.\n");

  double timeout = 0;
  while (fb_move_rel.isDone() == mcFALSE && timeout < 5)
  {
    axis->runCycle();
    fb_power.runCycle();
    fb_move_rel.runCycle();
    timeout += 0.001;

    if (fb_move_rel.isEnabled() == mcFALSE &&
        fb_power.getPowerStatus() == mcTRUE)
    {
      fb_move_rel.setExecute(mcTRUE);
      // printf("Axis powered on %d\n", fb_power.getPowerStatus() == mcTRUE);
    }

    // printf("Run time: %f, pos: %lf, vel: %lf\n", timeout, axis->toUserPos(),
    //        axis->toUserVel());
  }
  ASSERT_TRUE(fb_move_rel.isDone() == mcTRUE);
  ASSERT_LT(fabs(axis->toUserPos() - 3.14), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_MoveVelocity
TEST_F(FunctionBlockTest, DemoVelocity)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveVelocity fb_move_vel;
  fb_move_vel.setAxis(axis);
  fb_move_vel.setExecute(mcFALSE);
  fb_move_vel.setContinuousUpdate(mcFALSE);
  fb_move_vel.setVelocity(1.57);
  fb_move_vel.setAcceleration(3.14);
  fb_move_vel.setDeceleration(3.14);
  fb_move_vel.setJerk(50);
  printf("Function block initialized.\n");

  double timeout = 0;
  while (fb_move_vel.isInVelocity() == mcFALSE && timeout < 5.0)
  {
    axis->runCycle();
    fb_power.runCycle();
    fb_move_vel.runCycle();
    timeout += 0.001;

    if (fb_move_vel.isEnabled() == mcFALSE &&
        fb_power.getPowerStatus() == mcTRUE)
    {
      fb_move_vel.setExecute(mcTRUE);
      // printf("Axis powered on %d\n", fb_power.getPowerStatus() == mcTRUE);
    }

    // printf("Run time: %f, pos: %lf, vel: %lf\n", timeout, axis->toUserPos(),
    //         axis->toUserVel());
  }
  ASSERT_TRUE(fb_move_vel.isInVelocity() == mcTRUE);
  ASSERT_LT(fabs(axis->toUserVel() - 1.57), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_Stop
TEST_F(FunctionBlockTest, MC_Stop)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveVelocity move_vel;
  move_vel.setAxis(axis);
  move_vel.setVelocity(50);
  move_vel.setAcceleration(10);
  move_vel.setDeceleration(10);
  move_vel.setJerk(5000);
  move_vel.setBufferMode(mcAborting);

  FbStop stop;
  stop.setAxis(axis);
  stop.setAcceleration(20);
  stop.setDeceleration(20);
  stop.setJerk(5000);

  double time_out = 25;
  double t        = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    move_vel.runCycle();
    stop.runCycle();

    if (move_vel.isEnabled() == mcFALSE && t < 7.5)
    {  //使能成功后move1开始移动
      std::cout << "axis poweron, mov_vel start" << std::endl;
      move_vel.setExecute(mcTRUE);
    }

    if (6 < t && t < 12.5 && stop.isEnabled() == mcFALSE)
      stop.setExecute(mcTRUE);

    if (12.5 < t && stop.isEnabled() == mcTRUE)
      stop.setExecute(mcFALSE);

    if (7.5 < t && t < 10 && move_vel.isEnabled() == mcTRUE)
      move_vel.setExecute(mcFALSE);

    if (10 < t && t < 15 && move_vel.isEnabled() == mcFALSE)
      move_vel.setExecute(mcTRUE);

    if (15 < t && t < 20 && move_vel.isEnabled() == mcTRUE)
      move_vel.setExecute(mcFALSE);

    if (17.5 < t && move_vel.isEnabled() == mcFALSE)
      move_vel.setExecute(mcTRUE);

    // printf("Run time: %f, pos: %f, vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
    t += 0.001;
  }

  ASSERT_TRUE(move_vel.isInVelocity() == mcTRUE);
  ASSERT_LT(fabs(axis->toUserVel() - 50), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_Halt
TEST_F(FunctionBlockTest, MC_Halt)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveVelocity move_vel;
  move_vel.setAxis(axis);
  move_vel.setVelocity(50);
  move_vel.setAcceleration(10);
  move_vel.setDeceleration(10);
  move_vel.setJerk(50);
  move_vel.setBufferMode(mcAborting);

  FbHalt halt;
  halt.setAxis(axis);
  halt.setAcceleration(5);
  halt.setJerk(50);
  halt.setBufferMode(mcAborting);

  double time_out = 40;
  double t        = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    move_vel.runCycle();
    halt.runCycle();

    if (move_vel.isEnabled() == mcFALSE && t < 7.5)
    {  //使能成功后move1开始移动
      std::cout << "axis poweron, mov_vel start" << std::endl;
      move_vel.setExecute(mcTRUE);
    }

    if (8.5 < t && t < 19 && move_vel.isEnabled() == mcTRUE)
      move_vel.setExecute(mcFALSE);

    if (19 < t && t < 21.5 && move_vel.isEnabled() == mcFALSE)
      move_vel.setExecute(mcTRUE);

    if (21.5 < t && t < 32.5 && move_vel.isEnabled() == mcTRUE)
      move_vel.setExecute(mcFALSE);

    if (32.5 < t && move_vel.isEnabled() == mcFALSE)
      move_vel.setExecute(mcTRUE);

    if (7 < t && t < 17.5 && halt.isEnabled() == mcFALSE)
      halt.setExecute(mcTRUE);

    if (17.5 < t && t < 27.5 && halt.isEnabled() == mcTRUE)
      halt.setExecute(mcFALSE);

    if (27.5 < t && t < 37.5 && halt.isEnabled() == mcFALSE)
      halt.setExecute(mcTRUE);

    if (37.5 < t && halt.isEnabled() == mcTRUE)
      halt.setExecute(mcFALSE);

    // printf("Run time: %f, pos: %f, vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
    t += 0.001;
  }

  ASSERT_TRUE(move_vel.isInVelocity() == mcTRUE);
  ASSERT_LT(fabs(axis->toUserVel() - 50), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_MoveAbsolute
TEST_F(FunctionBlockTest, MC_MoveAbsolute)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveAbsolute move_abs1;
  move_abs1.setAxis(axis);
  move_abs1.setPosition(600);
  move_abs1.setVelocity(300);
  move_abs1.setAcceleration(500);
  move_abs1.setDeceleration(500);
  move_abs1.setJerk(5000);

  FbMoveAbsolute move_abs2;
  move_abs2.setAxis(axis);
  move_abs2.setPosition(1000);
  move_abs2.setVelocity(200);
  move_abs2.setAcceleration(500);
  move_abs2.setDeceleration(500);
  move_abs2.setJerk(5000);
  move_abs2.setBufferMode(mcAborting);

  double time_out = 7;
  double t        = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    move_abs1.runCycle();
    move_abs2.runCycle();

    if (2 < t && move_abs1.isEnabled() == mcTRUE)
      move_abs1.setExecute(mcFALSE);

    if (1 < t && t < 6 && move_abs2.isEnabled() == mcFALSE)
      move_abs2.setExecute(mcTRUE);

    if (6 < t && move_abs2.isEnabled() == mcTRUE)
      move_abs2.setExecute(mcFALSE);

    // printf("Run time: %f, pos: %f, vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
    t += 0.001;
  }
  ASSERT_LT(fabs(axis->toUserVel() - 0.0), 0.01);
  ASSERT_LT(fabs(axis->toUserPos() - 1000), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_MoveRelative
TEST_F(FunctionBlockTest, MC_MoveRelative)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveRelative fb_move_rel_1, fb_move_rel_2;
  fb_move_rel_1.setAxis(axis);
  fb_move_rel_1.setContinuousUpdate(mcFALSE);
  fb_move_rel_1.setDistance(600);
  fb_move_rel_1.setVelocity(300);
  fb_move_rel_1.setAcceleration(500);
  fb_move_rel_1.setDeceleration(500);
  fb_move_rel_1.setJerk(5000);

  fb_move_rel_2.setAxis(axis);
  fb_move_rel_2.setContinuousUpdate(mcFALSE);
  fb_move_rel_2.setDistance(400);
  fb_move_rel_2.setVelocity(200);
  fb_move_rel_2.setAcceleration(500);
  fb_move_rel_2.setDeceleration(500);
  fb_move_rel_2.setJerk(5000);
  fb_move_rel_2.setBufferMode(mcAborting);

  double time_out = 4;
  double t        = 0;
  double pos_tmp  = 0;
  mcBOOL trigger  = mcFALSE;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    fb_move_rel_1.runCycle();
    fb_move_rel_2.runCycle();
    if (trigger == mcTRUE)
    {
      pos_tmp = axis->toUserPos();
      trigger = mcFALSE;
    }

    if (fb_move_rel_1.isEnabled() == mcFALSE && t < 2)
    {
      // After enabled, move_relative_1 start to move
      fb_move_rel_1.setExecute(mcTRUE);
      std::cout << "axis poweron, fb_move_rel_1 start" << std::endl;
    }

    if (2 < t && fb_move_rel_1.isEnabled() == mcTRUE)
      fb_move_rel_1.setExecute(mcFALSE);

    if (1 < t && t < 3.8 && fb_move_rel_2.isEnabled() == mcFALSE)
    {
      fb_move_rel_2.setExecute(mcTRUE);
      trigger = mcTRUE;
    }

    if (3.8 < t && fb_move_rel_2.isEnabled() == mcTRUE)
      fb_move_rel_2.setExecute(mcFALSE);

    t += 0.001;
    // printf("Run time: %f, pos: %f, vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
  }

  ASSERT_LT(fabs(axis->toUserVel() - 0.0), 0.01);
  ASSERT_LT(fabs(axis->toUserPos() - (pos_tmp + 400)), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_MoveAdditive
TEST_F(FunctionBlockTest, MC_MoveAdditive)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveAbsolute move_abs1;
  move_abs1.setAxis(axis);
  move_abs1.setPosition(600);
  move_abs1.setVelocity(300);
  move_abs1.setAcceleration(500);
  move_abs1.setDeceleration(500);
  move_abs1.setJerk(5000);
  move_abs1.setDirection(mcPositiveDirection);

  FbMoveAdditive move_add2;
  move_add2.setAxis(axis);
  move_add2.setDistance(400);
  move_add2.setVelocity(200);
  move_add2.setAcceleration(500);
  move_add2.setDeceleration(500);
  move_add2.setJerk(5000);
  move_add2.setBufferMode(mcAborting);

  double time_out = 7;
  double t        = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    move_abs1.runCycle();
    move_add2.runCycle();

    if (2 < t && move_abs1.isEnabled() == mcTRUE)
      move_abs1.setExecute(mcFALSE);

    if (1 < t && t < 6 && move_add2.isEnabled() == mcFALSE)
    {
      move_add2.setExecute(mcTRUE);
    }

    if (6 < t && move_add2.isEnabled() == mcTRUE)
      move_add2.setExecute(mcFALSE);

    t += 0.001;
    // printf("Run time: %f, pos: %f, vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
  }

  ASSERT_LT(fabs(axis->toUserVel() - 0.0), 0.01);
  ASSERT_LT(fabs(axis->toUserPos() - (600 + 400)), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_MoveVelocity
TEST_F(FunctionBlockTest, MC_MoveVelocity)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveVelocity mov_vel1;
  mov_vel1.setAxis(axis);
  mov_vel1.setVelocity(500);
  mov_vel1.setAcceleration(500);
  mov_vel1.setDeceleration(500);
  mov_vel1.setJerk(5000);
  mov_vel1.setBufferMode(mcAborting);

  FbMoveVelocity mov_vel2;
  mov_vel2.setAxis(axis);
  mov_vel2.setVelocity(200);
  mov_vel2.setAcceleration(500);
  mov_vel2.setDeceleration(500);
  mov_vel2.setJerk(5000);
  mov_vel2.setBufferMode(mcAborting);

  double time_out = 9;
  double t        = 0;
  mcBOOL next = mcFALSE, test = mcFALSE;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    mov_vel1.runCycle();
    mov_vel2.runCycle();

    if (mov_vel1.isEnabled() == mcFALSE && t < 5)
    {
      std::cout << "axis poweron, mov_vel1 start" << std::endl;
      mov_vel1.setExecute(mcTRUE);
    }

    if (5 < t && t < 6 && mov_vel1.isEnabled() == mcTRUE)
      mov_vel1.setExecute(mcFALSE);

    if (6 < t && t < 8 && mov_vel1.isEnabled() == mcFALSE)
      mov_vel1.setExecute(mcTRUE);

    if (8 < t && mov_vel1.isEnabled() == mcTRUE)
      mov_vel1.setExecute(mcFALSE);

    if (2 < t && t < 4 && next == mcFALSE)
    {
      next = mcTRUE;
      mov_vel2.setExecute(next);
    }

    if (4 < t && next == mcTRUE)
    {
      next = mcFALSE;
      mov_vel2.setExecute(mcFALSE);
    }

    if (6.5 < t && t < 8.5 && test == mcFALSE)
    {
      test = mcTRUE;
      mov_vel2.setExecute(test);
    }

    if (8.5 < t && test == mcTRUE)
    {
      test = mcFALSE;
      mov_vel2.setExecute(test);
    }

    t += 0.001;
    // printf("Run time: %f, pos: %f, vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
  }

  ASSERT_LT(fabs(axis->toUserVel() - 200), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_Homing
TEST_F(FunctionBlockTest, MC_Homing1)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);
  axis->setNodeQueueSize(3);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbHoming move_homing;
  move_homing.setAxis(axis);
  move_homing.setDirection(mcNegativeDirection);
  move_homing.setVelocity(300);
  move_homing.setAcceleration(500);
  move_homing.setDeceleration(500);
  move_homing.setJerk(5000);

  FbReadActualPosition read_actual_pos;
  read_actual_pos.setAxis(axis);
  read_actual_pos.setEnable(mcTRUE);
  double time_out = 3.5;
  double t        = 0;
  int64_t count   = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    move_homing.runCycle();
    read_actual_pos.runCycle();

    if (move_homing.isEnabled() == mcFALSE &&
        fb_power.getPowerStatus() == mcTRUE)
    {
      std::cout << "axis poweron, moveHome start" << std::endl;
      move_homing.setExecute(mcTRUE);
      move_homing.setRefSignal(mcTRUE);
    }

    if (count == 100)
    {
      move_homing.setRefSignal(mcFALSE);
    }

    if (move_homing.isDone() == mcTRUE)
    {
      std::cout << "moveHome done" << std::endl;
      break;
    }

    // printf("Run time: %ld, usr pos: %f, act vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
    count++;
    t += 0.001;
  }

  ASSERT_LT(fabs(axis->toUserVel() - 0.0), 0.01);
  ASSERT_LT(fabs(axis->toUserPos() - 0.0), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_Homing
TEST_F(FunctionBlockTest, MC_Homing2)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);
  axis->setNodeQueueSize(3);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveRelative move_rel;
  move_rel.setAxis(axis);
  move_rel.setPosition(100);
  move_rel.setVelocity(300);
  move_rel.setAcceleration(500);
  move_rel.setDeceleration(500);
  move_rel.setJerk(5000);

  FbHoming move_homing;
  move_homing.setAxis(axis);
  move_homing.setDirection(mcNegativeDirection);
  move_homing.setVelocity(300);
  move_homing.setAcceleration(500);
  move_homing.setDeceleration(500);
  move_homing.setJerk(5000);

  FbReadActualPosition read_actual_pos;
  read_actual_pos.setAxis(axis);
  read_actual_pos.setEnable(mcTRUE);
  double time_out = 3.5;
  double t        = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    move_rel.runCycle();
    move_homing.runCycle();
    read_actual_pos.runCycle();

    if (move_rel.isEnabled() == mcFALSE && fb_power.getPowerStatus() == mcTRUE)
    {
      std::cout << "axis poweron, moveRel start" << std::endl;
      move_rel.setExecute(mcTRUE);
    }

    if (move_rel.isDone() == mcTRUE && move_homing.isEnabled() == mcFALSE)
    {
      std::cout << "moveRel done, moveHome start" << std::endl;
      move_homing.setExecute(mcTRUE);
    }

    if (move_homing.isEnabled() == mcTRUE &&
        read_actual_pos.getFloatValue() <= 0.0)
      move_homing.setRefSignal(mcTRUE);

    if (move_homing.isDone() == mcTRUE)
    {
      std::cout << "moveHome done" << std::endl;
      break;
    }

    // printf("Run time: %ld, usr pos: %f, act vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
    t += 0.001;
  }

  ASSERT_LT(fabs(axis->toUserVel() - 0.0), 0.01);
  ASSERT_LT(fabs(axis->toUserPos() - 0.0), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_Homing
TEST_F(FunctionBlockTest, MC_Homing3)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);
  axis->setNodeQueueSize(3);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbHoming move_homing;
  move_homing.setAxis(axis);
  move_homing.setDirection(mcNegativeDirection);
  move_homing.setVelocity(300);
  move_homing.setAcceleration(500);
  move_homing.setDeceleration(500);
  move_homing.setJerk(5000);

  FbReadActualPosition read_actual_pos;
  read_actual_pos.setAxis(axis);
  read_actual_pos.setEnable(mcTRUE);

  double time_out = 3.5;
  double t        = 0;
  int64_t count   = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    move_homing.runCycle();
    read_actual_pos.runCycle();

    if (move_homing.isEnabled() == mcFALSE &&
        fb_power.getPowerStatus() == mcTRUE)
    {
      std::cout << "axis poweron, moveRel start" << std::endl;
      move_homing.setExecute(mcTRUE);
    }

    if (count == 500)
    {
      move_homing.setLimitNegSignal(mcTRUE);
    }

    if (count == 1500)
    {
      move_homing.setRefSignal(mcTRUE);
    }

    if (count == 1600)
    {
      move_homing.setRefSignal(mcFALSE);
    }

    if (move_homing.isDone() == mcTRUE)
    {
      std::cout << "moveHome done" << std::endl;
      break;
    }

    // printf("Run time: %ld, usr pos: %f, act vel: %f\n", t, axis->toUserPos(),
    // axis->toUserVel());
    count++;
    t += 0.001;
  }

  ASSERT_LT(fabs(axis->toUserVel() - 0.0), 0.0001);
  ASSERT_LT(fabs(axis->toUserPos() - 0.0), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

// Test MC_MoveVelocity -> MC_Halt/MC_Stop -> MC_MoveRelative
TEST_F(FunctionBlockTest, MC_Sequence1)
{
  AxisConfig config;
  AXIS_REF axis;
  axis = new Axis();
  axis->setAxisId(1);

  axis->setAxisConfig(&config);
  printf("Axis initialized.\n");

  Servo* servo;
  servo = new Servo();
  axis->setServo(servo);

  FbPower fb_power;
  fb_power.setAxis(axis);
  fb_power.setEnable(mcTRUE);
  fb_power.setEnablePositive(mcTRUE);
  fb_power.setEnableNegative(mcTRUE);

  FbMoveVelocity fb_move_vel;
  fb_move_vel.setAxis(axis);
  fb_move_vel.setVelocity(50);
  fb_move_vel.setAcceleration(10);
  fb_move_vel.setDeceleration(10);
  fb_move_vel.setJerk(50);
  fb_move_vel.setBufferMode(mcAborting);

  FbHalt fb_halt;
  fb_halt.setAxis(axis);
  fb_halt.setAcceleration(5);
  fb_halt.setJerk(50);
  fb_halt.setBufferMode(mcAborting);

  FbMoveAbsolute fb_move_abs;
  fb_move_abs.setAxis(axis);
  fb_move_abs.setPosition(600);
  fb_move_abs.setVelocity(300);
  fb_move_abs.setAcceleration(500);
  fb_move_abs.setDeceleration(500);
  fb_move_abs.setJerk(5000);

  double time_out = 17;
  double t        = 0;
  while (t < time_out)
  {
    axis->runCycle();
    fb_power.runCycle();
    fb_move_vel.runCycle();
    fb_halt.runCycle();
    fb_move_abs.runCycle();

    if (fb_move_vel.isInVelocity() == mcTRUE && fb_halt.isEnabled() == mcFALSE)
    {
      std::cout << "axis in velocity, halt start" << std::endl;
      fb_halt.setExecute(mcTRUE);
    }

    if (fb_halt.isDone() == mcTRUE && fb_move_abs.isEnabled() == mcFALSE)
    {
      std::cout << "axis halt, fb_move_abs start" << std::endl;
      fb_move_abs.setExecute(mcTRUE);
    }

    // printf("Run time: %ld, pos: %f, vel: %f\n", t, axis->toUserPos(),
    //        axis->toUserVel());
    t += 0.001;
  }

  ASSERT_LT(fabs(axis->toUserPos() - 600), 0.01);
  delete servo;
  delete axis;
  servo = nullptr;
  axis  = nullptr;
  printf("FB test end. Delete axis and servo.\n");
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
