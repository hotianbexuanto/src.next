// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/android/jni_utils.h"

#include "base/android/jni_string.h"
#include "base/android/scoped_java_ref.h"

#include "base/base_jni_headers/JNIUtils_jni.h"

namespace base {
namespace android {

ScopedJavaLocalRef<jobject> GetClassLoader(JNIEnv* env) {
  return Java_JNIUtils_getSplitClassLoader(env,
                                           ConvertUTF8ToJavaString(env, ""));
}

ScopedJavaLocalRef<jobject> GetSplitClassLoader(JNIEnv* env,
                                                const std::string& split_name) {
  return Java_JNIUtils_getSplitClassLoader(
      env, ConvertUTF8ToJavaString(env, split_name));
}

<<<<<<< HEAD
  ScopedJavaGlobalRef<jobject> class_loader(
      Java_JNIUtils_getSplitClassLoader(env, split_name));
  jobject class_loader_obj = class_loader.obj();
  lock_and_map->map.insert({split_name, std::move(class_loader)});
  return class_loader_obj;
=======
bool IsSelectiveJniRegistrationEnabled(JNIEnv* env) {
  return Java_JNIUtils_isSelectiveJniRegistrationEnabled(env);
>>>>>>> chromium
}

}  // namespace android
}  // namespace base
