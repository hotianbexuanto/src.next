// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/android/jni_android.h"

#include <stddef.h>
#include <sys/prctl.h>

#include <map>

#include "base/android/java_exception_reporter.h"
#include "base/android/jni_string.h"
#include "base/android/jni_utils.h"
#include "base/containers/flat_map.h"
#include "base/debug/debugging_buildflags.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/no_destructor.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_local.h"

namespace base {
namespace android {
namespace {

JavaVM* g_jvm = NULL;
base::LazyInstance<ScopedJavaGlobalRef<jobject>>::Leaky g_class_loader =
    LAZY_INSTANCE_INITIALIZER;
jmethodID g_class_loader_load_class_method_id = 0;

#if BUILDFLAG(CAN_UNWIND_WITH_FRAME_POINTERS)
base::LazyInstance<base::ThreadLocalPointer<void>>::Leaky
    g_stack_frame_pointer = LAZY_INSTANCE_INITIALIZER;
#endif

bool g_fatal_exception_occurred = false;

// Returns a ClassLoader instance which will be able to load classes from the
// specified split.
jobject GetCachedClassLoader(JNIEnv* env, const std::string& split_name) {
  DCHECK(!split_name.empty());
  static base::NoDestructor<base::Lock> lock;
  static base::NoDestructor<
      base::flat_map<std::string, ScopedJavaGlobalRef<jobject>>>
      split_class_loader_map;

  base::AutoLock guard(*lock);
  auto it = split_class_loader_map->find(split_name);
  if (it != split_class_loader_map->end()) {
    return it->second.obj();
  }

  ScopedJavaGlobalRef<jobject> class_loader(
      GetSplitClassLoader(env, split_name));
  jobject class_loader_obj = class_loader.obj();
  split_class_loader_map->insert({split_name, std::move(class_loader)});
  return class_loader_obj;
}

ScopedJavaLocalRef<jclass> GetClassInternal(JNIEnv* env,
                                            const char* class_name,
                                            jobject class_loader) {
  jclass clazz;
  if (class_loader != nullptr) {
    // ClassLoader.loadClass expects a classname with components separated by
    // dots instead of the slashes that JNIEnv::FindClass expects. The JNI
    // generator generates names with slashes, so we have to replace them here.
    // TODO(torne): move to an approach where we always use ClassLoader except
    // for the special case of base::android::GetClassLoader(), and change the
    // JNI generator to generate dot-separated names. http://crbug.com/461773
    size_t bufsize = strlen(class_name) + 1;
    char dotted_name[bufsize];
    memmove(dotted_name, class_name, bufsize);
    for (size_t i = 0; i < bufsize; ++i) {
      if (dotted_name[i] == '/') {
        dotted_name[i] = '.';
      }
    }

    clazz = static_cast<jclass>(
        env->CallObjectMethod(class_loader, g_class_loader_load_class_method_id,
                              ConvertUTF8ToJavaString(env, dotted_name).obj()));
  } else {
    clazz = env->FindClass(class_name);
  }
  if (ClearException(env) || !clazz) {
    LOG(FATAL) << "Failed to find class " << class_name;
  }
  return ScopedJavaLocalRef<jclass>(env, clazz);
}

}  // namespace

JNIEnv* AttachCurrentThread() {
  DCHECK(g_jvm);
  JNIEnv* env = nullptr;
  jint ret = g_jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_2);
  if (ret == JNI_EDETACHED || !env) {
    JavaVMAttachArgs args;
    args.version = JNI_VERSION_1_2;
    args.group = nullptr;

    // 16 is the maximum size for thread names on Android.
    char thread_name[16];
    int err = prctl(PR_GET_NAME, thread_name);
    if (err < 0) {
      DPLOG(ERROR) << "prctl(PR_GET_NAME)";
      args.name = nullptr;
    } else {
      args.name = thread_name;
    }

    ret = g_jvm->AttachCurrentThread(&env, &args);
    CHECK_EQ(JNI_OK, ret);
  }
  return env;
}

JNIEnv* AttachCurrentThreadWithName(const std::string& thread_name) {
  DCHECK(g_jvm);
  JavaVMAttachArgs args;
  args.version = JNI_VERSION_1_2;
  args.name = thread_name.c_str();
  args.group = NULL;
  JNIEnv* env = NULL;
  jint ret = g_jvm->AttachCurrentThread(&env, &args);
  CHECK_EQ(JNI_OK, ret);
  return env;
}

void DetachFromVM() {
  // Ignore the return value, if the thread is not attached, DetachCurrentThread
  // will fail. But it is ok as the native thread may never be attached.
  if (g_jvm)
    g_jvm->DetachCurrentThread();
}

void InitVM(JavaVM* vm) {
  DCHECK(!g_jvm || g_jvm == vm);
  g_jvm = vm;
}

<<<<<<< HEAD
=======
bool IsVMInitialized() {
  return g_jvm != NULL;
}

void InitReplacementClassLoader(JNIEnv* env,
                                const JavaRef<jobject>& class_loader) {
  DCHECK(g_class_loader.Get().is_null());
  DCHECK(!class_loader.is_null());

  ScopedJavaLocalRef<jclass> class_loader_clazz =
      GetClass(env, "java/lang/ClassLoader");
  CHECK(!ClearException(env));
  g_class_loader_load_class_method_id =
      env->GetMethodID(class_loader_clazz.obj(),
                       "loadClass",
                       "(Ljava/lang/String;)Ljava/lang/Class;");
  CHECK(!ClearException(env));

  DCHECK(env->IsInstanceOf(class_loader.obj(), class_loader_clazz.obj()));
  g_class_loader.Get().Reset(class_loader);
}

ScopedJavaLocalRef<jclass> GetClass(JNIEnv* env,
                                    const char* class_name,
                                    const std::string& split_name) {
  return GetClassInternal(env, class_name,
                          GetCachedClassLoader(env, split_name));
}

ScopedJavaLocalRef<jclass> GetClass(JNIEnv* env, const char* class_name) {
  return GetClassInternal(env, class_name, g_class_loader.Get().obj());
}

// This is duplicated with LazyGetClass below because these are performance
// sensitive.
jclass LazyGetClass(JNIEnv* env,
                    const char* class_name,
                    const std::string& split_name,
                    std::atomic<jclass>* atomic_class_id) {
  const jclass value = atomic_class_id->load(std::memory_order_acquire);
  if (value)
    return value;
  ScopedJavaGlobalRef<jclass> clazz;
  clazz.Reset(GetClass(env, class_name, split_name));
  jclass cas_result = nullptr;
  if (atomic_class_id->compare_exchange_strong(cas_result, clazz.obj(),
                                               std::memory_order_acq_rel)) {
    // We intentionally leak the global ref since we now storing it as a raw
    // pointer in |atomic_class_id|.
    return clazz.Release();
  } else {
    return cas_result;
  }
}

// This is duplicated with LazyGetClass above because these are performance
// sensitive.
jclass LazyGetClass(JNIEnv* env,
                    const char* class_name,
                    std::atomic<jclass>* atomic_class_id) {
  const jclass value = atomic_class_id->load(std::memory_order_acquire);
  if (value)
    return value;
  ScopedJavaGlobalRef<jclass> clazz;
  clazz.Reset(GetClass(env, class_name));
  jclass cas_result = nullptr;
  if (atomic_class_id->compare_exchange_strong(cas_result, clazz.obj(),
                                               std::memory_order_acq_rel)) {
    // We intentionally leak the global ref since we now storing it as a raw
    // pointer in |atomic_class_id|.
    return clazz.Release();
  } else {
    return cas_result;
  }
}

template<MethodID::Type type>
jmethodID MethodID::Get(JNIEnv* env,
                        jclass clazz,
                        const char* method_name,
                        const char* jni_signature) {
  auto get_method_ptr = type == MethodID::TYPE_STATIC ?
      &JNIEnv::GetStaticMethodID :
      &JNIEnv::GetMethodID;
  jmethodID id = (env->*get_method_ptr)(clazz, method_name, jni_signature);
  if (base::android::ClearException(env) || !id) {
    LOG(FATAL) << "Failed to find " <<
        (type == TYPE_STATIC ? "static " : "") <<
        "method " << method_name << " " << jni_signature;
  }
  return id;
}

// If |atomic_method_id| set, it'll return immediately. Otherwise, it'll call
// into ::Get() above. If there's a race, it's ok since the values are the same
// (and the duplicated effort will happen only once).
template <MethodID::Type type>
jmethodID MethodID::LazyGet(JNIEnv* env,
                            jclass clazz,
                            const char* method_name,
                            const char* jni_signature,
                            std::atomic<jmethodID>* atomic_method_id) {
  const jmethodID value = atomic_method_id->load(std::memory_order_acquire);
  if (value)
    return value;
  jmethodID id = MethodID::Get<type>(env, clazz, method_name, jni_signature);
  atomic_method_id->store(id, std::memory_order_release);
  return id;
}

// Various template instantiations.
template jmethodID MethodID::Get<MethodID::TYPE_STATIC>(
    JNIEnv* env, jclass clazz, const char* method_name,
    const char* jni_signature);

template jmethodID MethodID::Get<MethodID::TYPE_INSTANCE>(
    JNIEnv* env, jclass clazz, const char* method_name,
    const char* jni_signature);

template jmethodID MethodID::LazyGet<MethodID::TYPE_STATIC>(
    JNIEnv* env, jclass clazz, const char* method_name,
    const char* jni_signature, std::atomic<jmethodID>* atomic_method_id);

template jmethodID MethodID::LazyGet<MethodID::TYPE_INSTANCE>(
    JNIEnv* env, jclass clazz, const char* method_name,
    const char* jni_signature, std::atomic<jmethodID>* atomic_method_id);

bool HasException(JNIEnv* env) {
  return env->ExceptionCheck() != JNI_FALSE;
}

bool ClearException(JNIEnv* env) {
  if (!HasException(env))
    return false;
  env->ExceptionDescribe();
  env->ExceptionClear();
  return true;
}

>>>>>>> chromium
void CheckException(JNIEnv* env) {
  if (!HasException(env))
    return;

  jthrowable java_throwable = env->ExceptionOccurred();
  if (java_throwable) {
    // Clear the pending exception, since a local reference is now held.
    env->ExceptionDescribe();
    env->ExceptionClear();

    if (g_fatal_exception_occurred) {
      // Another exception (probably OOM) occurred during GetJavaExceptionInfo.
      base::android::SetJavaException(
          "Java OOM'ed in exception handling, check logcat");
    } else {
      g_fatal_exception_occurred = true;
      // RVO should avoid any extra copies of the exception string.
      base::android::SetJavaException(
          GetJavaExceptionInfo(env, java_throwable).c_str());
    }
  }

<<<<<<< HEAD
  // We cannot use `ScopedJavaLocalRef` directly because that ends up calling
  // env->GetObjectRefType() when DCHECK is on, and that call is not allowed
  // with a pending exception according to the JNI spec.
  jthrowable raw_throwable = env->ExceptionOccurred();
  // Now that we saved the reference to the throwable, clear the exception.
  //
  // We need to do this as early as possible to remove the risk that code below
  // might accidentally call back into Java, which is not allowed when `env`
  // has an exception set, per the JNI spec. (For example, LOG(FATAL) doesn't
  // work with a JNI exception set, because it calls
  // GetJavaStackTraceIfPresent()).
  env->ExceptionClear();
  // The reference returned by `ExceptionOccurred()` is a local reference.
  // `ExceptionClear()` merely removes the exception information from `env`;
  // it doesn't delete the reference, which is why this call is valid.
  auto throwable = ScopedJavaLocalRef<jthrowable>::Adopt(env, raw_throwable);

  if (!handle_exception_in_java) {
    base::android::SetJavaException(
        GetJavaExceptionInfo(env, throwable).c_str());
    if (g_log_fatal_callback_for_testing) {
      g_log_fatal_callback_for_testing(kUncaughtExceptionMessage);
    } else {
      LOG(FATAL) << kUncaughtExceptionMessage;
    }
    // Needed for tests, which do not terminate from LOG(FATAL).
    g_reentering = false;
    return;
  }

  // We don't need to call SetJavaException() in this branch because we
  // expect handleException() to eventually call JavaExceptionReporter through
  // the global uncaught exception handler.

  const std::string native_stack_trace = base::debug::StackTrace().ToString();
  LOG(ERROR) << "Native stack trace:" << std::endl << native_stack_trace;

  ScopedJavaLocalRef<jthrowable> secondary_exception =
      Java_JniAndroid_handleException(env, throwable, native_stack_trace);

  // Ideally handleException() should have terminated the process and we should
  // not get here. This can happen in the case of OutOfMemoryError or if the
  // app that embedded WebView installed an exception handler that does not
  // terminate, or itself threw an exception. We cannot be confident that
  // JavaExceptionReporter ran, so set the java exception explicitly.
  base::android::SetJavaException(
      GetJavaExceptionInfo(
          env, secondary_exception ? secondary_exception : throwable)
          .c_str());
  if (g_log_fatal_callback_for_testing) {
    g_log_fatal_callback_for_testing(kUncaughtExceptionHandlerFailedMessage);
  } else {
    LOG(FATAL) << kUncaughtExceptionHandlerFailedMessage;
  }
  // Needed for tests, which do not terminate from LOG(FATAL).
  g_reentering = false;
}

std::string GetJavaExceptionInfo(JNIEnv* env,
                                 const JavaRef<jthrowable>& throwable) {
  std::string sanitized_exception_string =
      Java_JniAndroid_sanitizedStacktraceForUnhandledException(env, throwable);
  // Returns null when PiiElider results in an OutOfMemoryError.
  return !sanitized_exception_string.empty()
             ? sanitized_exception_string
             : kOomInGetJavaExceptionInfoMessage;
=======
  // Now, feel good about it and die.
  LOG(FATAL) << "Please include Java exception stack in crash report";
}

std::string GetJavaExceptionInfo(JNIEnv* env, jthrowable java_throwable) {
  ScopedJavaLocalRef<jclass> log_clazz = GetClass(env, "android/util/Log");
  jmethodID log_getstacktracestring = MethodID::Get<MethodID::TYPE_STATIC>(
      env, log_clazz.obj(), "getStackTraceString",
      "(Ljava/lang/Throwable;)Ljava/lang/String;");

  // Call Log.getStackTraceString()
  ScopedJavaLocalRef<jstring> exception_string(
      env, static_cast<jstring>(env->CallStaticObjectMethod(
               log_clazz.obj(), log_getstacktracestring, java_throwable)));
  CheckException(env);

  ScopedJavaLocalRef<jclass> piielider_clazz =
      GetClass(env, "org/chromium/base/PiiElider");
  jmethodID piielider_sanitize_stacktrace =
      MethodID::Get<MethodID::TYPE_STATIC>(
          env, piielider_clazz.obj(), "sanitizeStacktrace",
          "(Ljava/lang/String;)Ljava/lang/String;");
  ScopedJavaLocalRef<jstring> sanitized_exception_string(
      env, static_cast<jstring>(env->CallStaticObjectMethod(
               piielider_clazz.obj(), piielider_sanitize_stacktrace,
               exception_string.obj())));
  CheckException(env);

  return ConvertJavaStringToUTF8(sanitized_exception_string);
>>>>>>> chromium
}

#if BUILDFLAG(CAN_UNWIND_WITH_FRAME_POINTERS)

JNIStackFrameSaver::JNIStackFrameSaver(void* current_fp) {
  previous_fp_ = g_stack_frame_pointer.Pointer()->Get();
  g_stack_frame_pointer.Pointer()->Set(current_fp);
}

JNIStackFrameSaver::~JNIStackFrameSaver() {
  g_stack_frame_pointer.Pointer()->Set(previous_fp_);
}

void* JNIStackFrameSaver::SavedFrame() {
  return g_stack_frame_pointer.Pointer()->Get();
}

#endif  // BUILDFLAG(CAN_UNWIND_WITH_FRAME_POINTERS)

}  // namespace android
}  // namespace base
