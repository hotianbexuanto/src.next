// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/android/radio_utils.h"

#include "base/base_jni_headers/RadioUtils_jni.h"
#include "third_party/abseil-cpp/absl/types/optional.h"

namespace base {
namespace android {

namespace {
bool InitializeIsSupported() {
  JNIEnv* env = AttachCurrentThread();
  return Java_RadioUtils_isSupported(env);
}
}  // namespace

bool RadioUtils::IsSupported() {
  static const bool kIsSupported = InitializeIsSupported();
  return kIsSupported;
}

RadioConnectionType RadioUtils::GetConnectionType() {
<<<<<<< HEAD
  if (g_overrider_for_tests) {
    // If GetConnectionType is being used in tests
    return g_overrider_for_tests->GetConnectionType();
  }
  if (!IsSupported()) {
=======
  if (!IsSupported())
>>>>>>> chromium
    return RadioConnectionType::kUnknown;
  }

  JNIEnv* env = AttachCurrentThread();
  if (Java_RadioUtils_isWifiConnected(env)) {
    return RadioConnectionType::kWifi;
  } else {
    return RadioConnectionType::kCell;
  }
}

<<<<<<< HEAD
std::optional<RadioSignalLevel> RadioUtils::GetCellSignalLevel() {
  if (!IsSupported()) {
    return std::nullopt;
  }
=======
absl::optional<RadioSignalLevel> RadioUtils::GetCellSignalLevel() {
  if (!IsSupported())
    return absl::nullopt;
>>>>>>> chromium

  JNIEnv* env = AttachCurrentThread();
  int signal_level = Java_RadioUtils_getCellSignalLevel(env);
  if (signal_level < 0) {
    return absl::nullopt;
  } else {
    return static_cast<RadioSignalLevel>(signal_level);
  }
}

<<<<<<< HEAD
std::optional<RadioDataActivity> RadioUtils::GetCellDataActivity() {
  if (!IsSupported()) {
    return std::nullopt;
  }
=======
absl::optional<RadioDataActivity> RadioUtils::GetCellDataActivity() {
  if (!IsSupported())
    return absl::nullopt;
>>>>>>> chromium

  JNIEnv* env = AttachCurrentThread();
  return static_cast<RadioDataActivity>(
      Java_RadioUtils_getCellDataActivity(env));
}

}  // namespace android
}  // namespace base
