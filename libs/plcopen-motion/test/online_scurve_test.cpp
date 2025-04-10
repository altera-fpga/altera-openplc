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
 * @file online_scurve_test.cpp
 *
 * Maintainer: Yu Yan <yu.yan@intel.com>
 *
 */

#include <RTmotion/algorithm/online_scurve_planner.hpp>
#include <thread>
#include <RTmotion/logging.hpp>
#include "gtest/gtest.h"

namespace traj_pro = trajectory_processing;

// The fixture for testing class Foo.
class ScurveTest : public ::testing::Test
{
protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  ScurveTest()
  {
    // You can do set-up work for each test here.
  }

  ~ScurveTest() override
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

  traj_pro::ScurvePlannerOnLine planner_;
};

// Test 1
TEST_F(ScurveTest, Test1)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 50;
  planner_.condition_.v0    = 0;
  planner_.condition_.v1    = 0;
  planner_.condition_.a0    = 0;
  planner_.condition_.a1    = 0;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 8;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 50, planner_.vk_ - 0, planner_.ak_ - 0);
  ASSERT_LT(abs(planner_.sk_ - 50), 0.01);
  ASSERT_LT(abs(planner_.vk_ - 0), 0.05);
  ASSERT_LT(abs(planner_.ak_ - 0), 0.05);
}

// Test 2
TEST_F(ScurveTest, Test2)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 5;
  planner_.condition_.v0    = 0;
  planner_.condition_.v1    = 0;
  planner_.condition_.a0    = 0;
  planner_.condition_.a1    = 0;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 2;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 5, planner_.vk_ - 0, planner_.ak_ - 0);
  ASSERT_LT(abs(planner_.sk_ - 5), 0.02);
  ASSERT_LT(abs(planner_.vk_ - 0), 0.05);
  ASSERT_LT(abs(planner_.ak_ - 0), 0.05);
}

// Test 3
TEST_F(ScurveTest, Test3)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 5;
  planner_.condition_.v0    = 5;
  planner_.condition_.v1    = 3;
  planner_.condition_.a0    = 3;
  planner_.condition_.a1    = 5;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 1.5;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 5, planner_.vk_ - 3, planner_.ak_ - 5);
  ASSERT_LT(abs(planner_.sk_ - 5), 0.02);
  ASSERT_LT(abs(planner_.vk_ - 3), 0.05);
  ASSERT_LT(abs(planner_.ak_ - 5), 0.05);
}

// Test 4
TEST_F(ScurveTest, Test4)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 5;
  planner_.condition_.v0    = 5;
  planner_.condition_.v1    = 3;
  planner_.condition_.a0    = -4;
  planner_.condition_.a1    = 2;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 1.5;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 5, planner_.vk_ - 3, planner_.ak_ - 2);
  ASSERT_LT(abs(planner_.sk_ - 5), 0.01);
  ASSERT_LT(abs(planner_.vk_ - 3), 0.05);
  ASSERT_LT(abs(planner_.ak_ - 2), 4);
}

// Test 5
TEST_F(ScurveTest, Test5)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 50;
  planner_.condition_.v0    = 15;
  planner_.condition_.v1    = 3;
  planner_.condition_.a0    = -4;
  planner_.condition_.a1    = 2;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 6;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 50, planner_.vk_ - 3, planner_.ak_ - 2);
  ASSERT_LT(abs(planner_.sk_ - 50), 0.01);
  ASSERT_LT(abs(planner_.vk_ - 3), 0.05);
  ASSERT_LT(abs(planner_.ak_ - 2), 0.05);
}

// Test 6
TEST_F(ScurveTest, Test6)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 50;
  planner_.condition_.v0    = 15;
  planner_.condition_.v1    = 20;
  planner_.condition_.a0    = -4;
  planner_.condition_.a1    = 2;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 6;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 50, planner_.vk_ - 20, planner_.ak_ - 2);
  ASSERT_LT(abs(planner_.sk_ - 50), 0.025);
  ASSERT_LT(abs(planner_.vk_ - 20), 0.05);
  ASSERT_LT(abs(planner_.ak_ - 2), 0.05);
}

// Test 7
TEST_F(ScurveTest, Test7)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 20;
  planner_.condition_.v0    = 15;
  planner_.condition_.v1    = 20;
  planner_.condition_.a0    = -4;
  planner_.condition_.a1    = 2;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 2;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 20, planner_.vk_ - 20, planner_.ak_ - 2);
  ASSERT_LT(abs(planner_.sk_ - 20), 0.05);
  ASSERT_LT(abs(planner_.vk_ - 20), 0.05);
  ASSERT_LT(abs(planner_.ak_ - 2), 0.05);
}

// Test 8
TEST_F(ScurveTest, Test8)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 3.14;
  planner_.condition_.v0    = 0;
  planner_.condition_.v1    = 0;
  planner_.condition_.a0    = 0;
  planner_.condition_.a1    = 0;
  planner_.condition_.v_max = 1.57;
  planner_.condition_.a_max = 3.14;
  planner_.condition_.j_max = 500;

  planner_.plan();

  double iter_t = 0, t = 3;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 3.14, planner_.vk_ - 0, planner_.ak_ - 0);
  ASSERT_LT(abs(planner_.sk_ - 3.14), 0.02);
  ASSERT_LT(abs(planner_.vk_ - 0), 0.1);
  ASSERT_LT(abs(planner_.ak_ - 0), 1);
}

// Test 9
TEST_F(ScurveTest, Test9)
{
  planner_.reset();
  planner_.condition_.q0    = 0;
  planner_.condition_.q1    = 10;
  planner_.condition_.v0    = 1;
  planner_.condition_.v1    = 0;
  planner_.condition_.a0    = 0;
  planner_.condition_.a1    = 0;
  planner_.condition_.v_max = 10;
  planner_.condition_.a_max = 10;
  planner_.condition_.j_max = 30;

  planner_.plan();

  double iter_t = 0, t = 3;
  while (iter_t < t)
  {
    planner_.getWaypoint(iter_t);
    iter_t += 0.001;
  }

  INFO_PRINT("Scurve profile: Tj2a %f, Tj2b %f, Td %f\n",
             planner_.profile_.Tj2a, planner_.profile_.Tj2b,
             planner_.profile_.Td);
  INFO_PRINT("Scurve termination: sk_e %f, vk_e %f, ak_e %f\n",
             planner_.sk_ - 10, planner_.vk_ - 0, planner_.ak_ - 0);
  ASSERT_LT(abs(planner_.sk_ - 10), 0.03);
  ASSERT_LT(abs(planner_.vk_ - 0), 0.1);
  ASSERT_LT(abs(planner_.ak_ - 0), 1);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
