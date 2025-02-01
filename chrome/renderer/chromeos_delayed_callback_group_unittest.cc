// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/renderer/chromeos_delayed_callback_group.h"

<<<<<<< HEAD
#include "base/task/sequenced_task_runner.h"
=======
#include "base/run_loop.h"
#include "base/task/post_task.h"
>>>>>>> chromium
#include "base/task/task_traits.h"
#include "base/test/bind.h"
#include "base/test/task_environment.h"
#include "base/test/test_future.h"
#include "base/threading/platform_thread.h"
#include "base/threading/sequenced_task_runner_handle.h"
#include "base/time/time.h"
#include "testing/gtest/include/gtest/gtest.h"

using base::TimeDelta;

TEST(DelayedCallbackGroup, RunEmpty) {
  base::test::TaskEnvironment task_environment;
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      TimeDelta::FromSeconds(1), base::SequencedTaskRunnerHandle::Get());
  callback_group->RunAll();
}

TEST(DelayedCallbackGroup, RunSimple) {
<<<<<<< HEAD
  const base::TimeDelta kTimeout = base::Seconds(1);
  base::test::TaskEnvironment task_environment;
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      kTimeout, base::SequencedTaskRunner::GetCurrentDefault());
=======
  const TimeDelta kTimeout = TimeDelta::FromMilliseconds(500);
  base::test::TaskEnvironment task_environment;
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      TimeDelta::FromSeconds(1), base::SequencedTaskRunnerHandle::Get());
>>>>>>> chromium

  base::Time time_before_add = base::Time::Now();
  base::test::TestFuture<DelayedCallbackGroup::RunReason> future;
  callback_group->Add(future.GetCallback());
  callback_group->RunAll();
  DelayedCallbackGroup::RunReason reason = future.Get();

<<<<<<< HEAD
  base::TimeDelta delta = base::Time::Now() - time_before_add;
=======
  TimeDelta delta = callback_time - time_before_add;
>>>>>>> chromium
  EXPECT_LT(delta, kTimeout);
  EXPECT_EQ(DelayedCallbackGroup::RunReason::NORMAL, reason);
}

TEST(DelayedCallbackGroup, TimeoutSimple) {
<<<<<<< HEAD
  const base::TimeDelta kTimeout = base::Seconds(1);
  base::test::TaskEnvironment task_environment{
      base::test::TaskEnvironment::TimeSource::MOCK_TIME};
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      kTimeout, base::SequencedTaskRunner::GetCurrentDefault());
=======
  const TimeDelta kTimeout = TimeDelta::FromMilliseconds(500);
  base::test::TaskEnvironment task_environment;
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      TimeDelta::FromSeconds(1), base::SequencedTaskRunnerHandle::Get());
>>>>>>> chromium

  base::test::TestFuture<DelayedCallbackGroup::RunReason> future;
  callback_group->Add(future.GetCallback());
  task_environment.FastForwardBy(kTimeout);

<<<<<<< HEAD
  EXPECT_TRUE(future.IsReady());
  DelayedCallbackGroup::RunReason reason = future.Get();
  EXPECT_EQ(DelayedCallbackGroup::RunReason::TIMEOUT, reason);
}

#if BUILDFLAG(IS_CHROMEOS)
// Failing on CrOS ASAN: crbug.com/1290874
#define MAYBE_TimeoutAndRun DISABLED_TimeoutAndRun
#else
#define MAYBE_TimeoutAndRun TimeoutAndRun
#endif

TEST(DelayedCallbackGroup, MAYBE_TimeoutAndRun) {
  const base::TimeDelta kTimeout = base::Seconds(1);
  base::test::TaskEnvironment task_environment{
      base::test::TaskEnvironment::TimeSource::MOCK_TIME};
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      kTimeout, base::SequencedTaskRunner::GetCurrentDefault());

  base::test::TestFuture<DelayedCallbackGroup::RunReason> future1;
  callback_group->Add(future1.GetCallback());
  task_environment.FastForwardBy(kTimeout + base::Milliseconds(100));
  EXPECT_TRUE(future1.IsReady());

  base::test::TestFuture<DelayedCallbackGroup::RunReason> future2;
  callback_group->Add(future2.GetCallback());
  DelayedCallbackGroup::RunReason reason1 = future1.Get();

  EXPECT_EQ(DelayedCallbackGroup::RunReason::TIMEOUT, reason1);
  EXPECT_FALSE(future2.IsReady());

  callback_group->RunAll();
  DelayedCallbackGroup::RunReason reason2 = future2.Get();

  EXPECT_EQ(DelayedCallbackGroup::RunReason::NORMAL, reason2);
}

TEST(DelayedCallbackGroup, DoubleExpiration) {
  const base::TimeDelta kTimeout = base::Seconds(1);
  const base::TimeDelta kTimeDiff = base::Milliseconds(100);
  base::test::TaskEnvironment task_environment{
      base::test::TaskEnvironment::TimeSource::MOCK_TIME};
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      kTimeout, base::SequencedTaskRunner::GetCurrentDefault());

  base::test::TestFuture<DelayedCallbackGroup::RunReason> future1;
  callback_group->Add(future1.GetCallback());
  task_environment.FastForwardBy(kTimeDiff);
  base::test::TestFuture<DelayedCallbackGroup::RunReason> future2;
  callback_group->Add(future2.GetCallback());
  task_environment.FastForwardBy(kTimeout - kTimeDiff);

  EXPECT_TRUE(future1.IsReady());
  EXPECT_FALSE(future2.IsReady());
  DelayedCallbackGroup::RunReason reason1 = future1.Get();
  EXPECT_EQ(DelayedCallbackGroup::RunReason::TIMEOUT, reason1);

  task_environment.FastForwardBy(kTimeDiff);

  EXPECT_TRUE(future2.IsReady());
  DelayedCallbackGroup::RunReason reason2 = future2.Get();
  EXPECT_EQ(DelayedCallbackGroup::RunReason::TIMEOUT, reason2);
=======
  TimeDelta delta = callback_time - time_before_add;
  EXPECT_GE(delta, kTimeout);
}

TEST(DelayedCallbackGroup, TimeoutAndRun) {
  const TimeDelta kTimeout = TimeDelta::FromMilliseconds(500);
  base::test::TaskEnvironment task_environment;
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      TimeDelta::FromSeconds(1), base::SequencedTaskRunnerHandle::Get());

  base::Time start_time = base::Time::Now();
  base::Time callback_time_1;
  base::Time callback_time_2;
  base::RunLoop run_loop_1;
  bool callback_1_called = false;
  callback_group->Add(
      base::BindLambdaForTesting([&](DelayedCallbackGroup::RunReason reason) {
        EXPECT_FALSE(callback_1_called);
        callback_1_called = true;
        callback_time_1 = base::Time::Now();
        EXPECT_EQ(DelayedCallbackGroup::RunReason::TIMEOUT, reason);
        run_loop_1.Quit();
      }));
  base::PlatformThread::Sleep(kTimeout + TimeDelta::FromMilliseconds(100));
  base::RunLoop run_loop_2;
  bool callback_2_called = false;
  callback_group->Add(
      base::BindLambdaForTesting([&](DelayedCallbackGroup::RunReason reason) {
        EXPECT_FALSE(callback_2_called);
        callback_2_called = true;
        callback_time_2 = base::Time::Now();
        EXPECT_EQ(DelayedCallbackGroup::RunReason::NORMAL, reason);
        run_loop_2.Quit();
      }));
  run_loop_1.Run();

  TimeDelta delta = callback_time_1 - start_time;
  EXPECT_GE(delta, kTimeout);
  // Only the first callback should have timed out.
  EXPECT_TRUE(callback_time_2.is_null());
  callback_group->RunAll();
  run_loop_2.Run();
  delta = callback_time_2 - start_time;
  EXPECT_GE(delta, kTimeout + TimeDelta::FromMilliseconds(100));
}

TEST(DelayedCallbackGroup, DoubleExpiration) {
  const TimeDelta kTimeout = TimeDelta::FromMilliseconds(500);
  base::test::TaskEnvironment task_environment;
  auto callback_group = base::MakeRefCounted<DelayedCallbackGroup>(
      TimeDelta::FromSeconds(1), base::SequencedTaskRunnerHandle::Get());

  base::Time start_time = base::Time::Now();
  base::Time callback_time_1;
  base::Time callback_time_2;
  base::RunLoop run_loop_1;
  bool callback_1_called = false;
  callback_group->Add(
      base::BindLambdaForTesting([&](DelayedCallbackGroup::RunReason reason) {
        EXPECT_FALSE(callback_1_called);
        callback_1_called = true;
        callback_time_1 = base::Time::Now();
        EXPECT_EQ(DelayedCallbackGroup::RunReason::TIMEOUT, reason);
        run_loop_1.Quit();
      }));
  base::PlatformThread::Sleep(TimeDelta::FromMilliseconds(100));
  base::RunLoop run_loop_2;
  bool callback_2_called = false;
  callback_group->Add(
      base::BindLambdaForTesting([&](DelayedCallbackGroup::RunReason reason) {
        EXPECT_FALSE(callback_2_called);
        callback_2_called = true;
        callback_time_2 = base::Time::Now();
        EXPECT_EQ(DelayedCallbackGroup::RunReason::TIMEOUT, reason);
        run_loop_2.Quit();
      }));
  run_loop_1.Run();

  TimeDelta delta = callback_time_1 - start_time;
  EXPECT_GE(delta, kTimeout);
  // Only the first callback should have timed out.
  EXPECT_TRUE(callback_time_2.is_null());
  run_loop_2.Run();
  delta = callback_time_2 - start_time;
  EXPECT_GE(delta, kTimeout + TimeDelta::FromMilliseconds(100));
>>>>>>> chromium
}
