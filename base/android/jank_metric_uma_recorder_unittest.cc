// Copyright (c) 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/android/jank_metric_uma_recorder.h"

#include <jni.h>

#include <cstddef>
#include <cstdint>

#include "base/android/jni_android.h"
#include "base/android/jni_array.h"
#include "base/android/jni_string.h"
#include "base/metrics/histogram.h"
#include "base/test/metrics/histogram_tester.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using ::testing::ElementsAre;

namespace base {
namespace android {
namespace {

jlongArray GenerateJavaLongArray(JNIEnv* env,
                                 const int64_t long_array[],
                                 const size_t array_length) {
  ScopedJavaLocalRef<jlongArray> java_long_array =
      ToJavaLongArray(env, long_array, array_length);

  return java_long_array.Release();
}

// Durations are received in nanoseconds, but are recorded to UMA in
// milliseconds.
const int64_t kDurations[] = {
    1'000'000,   // 1ms
    2'000'000,   // 2ms
    30'000'000,  // 30ms
    10'000'000,  // 10ms
    60'000'000,  // 60ms
    1'000'000,   // 1ms
    1'000'000,   // 1ms
    20'000'000,  // 20ms
};
const size_t kDurationsLen = base::size(kDurations);

// Jank bursts are calculated based on durations.
const int64_t kJankBursts[] = {
    100'000'000,  // 100ms
    20'000'000,   // 20ms
};
const size_t kJankBurstsLen = base::size(kJankBursts);

}  // namespace

TEST(JankMetricUMARecorder, TestUMARecording) {
<<<<<<< HEAD
  JNIEnv* env = AttachCurrentThread();

  jlongArray java_durations = GenerateJavaLongArray(env, kDurations);

  jintArray java_missed_vsyncs = GenerateJavaIntArray(env, kMissedVsyncs);

  const int kMinScenario = static_cast<int>(JankScenario::PERIODIC_REPORTING);
  const int kMaxScenario = static_cast<int>(JankScenario::MAX_VALUE);
  // keep one histogram tester outside to ensure that each histogram is a
  // different one rather than just the same string over and over.
  HistogramTester complete_histogram_tester;
  size_t total_histograms = 0;
  for (int i = kMinScenario; i < kMaxScenario; ++i) {
    if ((i == static_cast<int>(JankScenario::WEBVIEW_SCROLLING)) ||
        (i == static_cast<int>(JankScenario::FEED_SCROLLING))) {
      continue;
    }
    // HistogramTester takes a snapshot of currently incremented counters so
    // everything is scoped to just this iteration of the for loop.
    HistogramTester histogram_tester;

    RecordJankMetrics(
        env,
        /* java_durations_ns= */
        base::android::JavaParamRef<jlongArray>(env, java_durations),
        /* java_missed_vsyncs = */
        base::android::JavaParamRef<jintArray>(env, java_missed_vsyncs),
        /* java_reporting_interval_start_time = */ 0,
        /* java_reporting_interval_duration = */ 1000,
        /* java_scenario_enum = */ i);

    const std::string kDurationName =
        GetAndroidFrameTimelineDurationHistogramName(
            static_cast<JankScenario>(i));
    const std::string kJankyName =
        GetAndroidFrameTimelineJankHistogramName(static_cast<JankScenario>(i));

    // Only one Duration and one Jank scenario should be incremented.
    base::HistogramTester::CountsMap count_map =
        histogram_tester.GetTotalCountsForPrefix("Android.FrameTimelineJank.");
    EXPECT_EQ(count_map.size(), 2ul);
    EXPECT_EQ(count_map[kDurationName], 8) << kDurationName;
    EXPECT_EQ(count_map[kJankyName], 8) << kJankyName;
    // And we should be two more then last iteration, but don't do any other
    // verification because each iteration will do their own.
    base::HistogramTester::CountsMap total_count_map =
        complete_histogram_tester.GetTotalCountsForPrefix(
            "Android.FrameTimelineJank.");
    EXPECT_EQ(total_count_map.size(), total_histograms + 2);
    total_histograms += 2;

    EXPECT_THAT(histogram_tester.GetAllSamples(kDurationName),
                ElementsAre(Bucket(1, 3), Bucket(2, 1), Bucket(10, 1),
                            Bucket(20, 1), Bucket(29, 1), Bucket(57, 1)))
        << kDurationName;
    EXPECT_THAT(histogram_tester.GetAllSamples(kJankyName),
                ElementsAre(Bucket(FrameJankStatus::kJanky, 2),
                            Bucket(FrameJankStatus::kNonJanky, 6)))
        << kJankyName;
  }
}

TEST(JankMetricUMARecorder, TestWebviewScrollingScenario) {
  JNIEnv* env = AttachCurrentThread();

  jlongArray java_durations = GenerateJavaLongArray(env, kDurations);
  jintArray java_missed_vsyncs = GenerateJavaIntArray(env, kMissedVsyncs);

  const int scenario = static_cast<int>(JankScenario::WEBVIEW_SCROLLING);
=======
>>>>>>> chromium
  HistogramTester histogram_tester;

  JNIEnv* env = AttachCurrentThread();

  jstring java_scenario_name =
      ConvertUTF8ToJavaString(env, "PeriodicReporting").Release();
  jlongArray java_durations =
      GenerateJavaLongArray(env, kDurations, kDurationsLen);
  jlongArray java_jank_bursts =
      GenerateJavaLongArray(env, kJankBursts, kJankBurstsLen);

  RecordJankMetrics(
      env,
      /* java_scenario_name= */
      base::android::JavaParamRef<jstring>(env, java_scenario_name),
      /* java_durations_ns= */
      base::android::JavaParamRef<jlongArray>(env, java_durations),
      /* java_jank_bursts_ns=*/
      base::android::JavaParamRef<jlongArray>(env, java_jank_bursts),
      /* java_missed_frames = */ 2);

  EXPECT_THAT(histogram_tester.GetAllSamples(
                  "Android.Jank.FrameDuration.PeriodicReporting"),
              ElementsAre(Bucket(1, 3), Bucket(2, 1), Bucket(10, 1),
                          Bucket(20, 1), Bucket(29, 1), Bucket(57, 1)));

  EXPECT_THAT(histogram_tester.GetAllSamples(
                  "Android.Jank.JankBursts.PeriodicReporting"),
              ElementsAre(Bucket(20, 1), Bucket(96, 1)));

  histogram_tester.ExpectUniqueSample(
      "Android.Jank.MissedFrames.PeriodicReporting", 2, 1);
}

}  // namespace android
}  // namespace base