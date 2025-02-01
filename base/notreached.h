// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_NOTREACHED_H_
#define BASE_NOTREACHED_H_

#include "base/check.h"
#include "base/logging_buildflags.h"

namespace logging {

<<<<<<< HEAD
#if CHECK_WILL_STREAM()
#define NOTREACHED_INTERNAL_IMPL() ::logging::NotReachedNoreturnError()
#else
// This function is used to be able to detect NOTREACHED() failures in stack
// traces where this symbol is preserved (even if inlined). Its implementation
// matches logging::CheckFailure() but intentionally uses a different signature.
[[noreturn]] NOMERGE IMMEDIATE_CRASH_ALWAYS_INLINE void NotReachedFailure() {
  base::ImmediateCrash();
}

#define NOTREACHED_INTERNAL_IMPL() \
  DISCARDING_CHECK_FUNCTION_IMPL(::logging::NotReachedFailure(), false)
#endif

// NOTREACHED() annotates should-be unreachable code. When a base::NotFatalUntil
// milestone is provided the instance is non-fatal (dumps without crashing)
// until that milestone is hit. That is: `NOTREACHED(base::NotFatalUntil::M120)`
// starts crashing in M120. See base/check.h.
#define NOTREACHED(...)                                           \
  BASE_IF(BASE_IS_EMPTY(__VA_ARGS__), NOTREACHED_INTERNAL_IMPL(), \
          LOGGING_CHECK_FUNCTION_IMPL(                            \
              ::logging::NotReachedError::NotReached(__VA_ARGS__), false))

// The DUMP_WILL_BE_NOTREACHED() macro provides a convenient way to
// non-fatally dump in official builds if ever hit. See DUMP_WILL_BE_CHECK for
// suggested usage.
#define DUMP_WILL_BE_NOTREACHED() \
  ::logging::NotReachedError::DumpWillBeNotReached()
=======
#if BUILDFLAG(ENABLE_LOG_ERROR_NOT_REACHED)
void BASE_EXPORT LogErrorNotReached(const char* file, int line);
#define NOTREACHED()                                       \
  true ? ::logging::LogErrorNotReached(__FILE__, __LINE__) \
       : EAT_CHECK_STREAM_PARAMS()
#else
#define NOTREACHED() DCHECK(false)
#endif

// The NOTIMPLEMENTED() macro annotates codepaths which have not been
// implemented yet. If output spam is a serious concern,
// NOTIMPLEMENTED_LOG_ONCE can be used.
#if DCHECK_IS_ON()
#define NOTIMPLEMENTED()                                     \
  ::logging::CheckError::NotImplemented(__FILE__, __LINE__,  \
                                        __PRETTY_FUNCTION__) \
      .stream()
#else
#define NOTIMPLEMENTED() EAT_CHECK_STREAM_PARAMS()
#endif

#define NOTIMPLEMENTED_LOG_ONCE()    \
  {                                  \
    static bool logged_once = false; \
    if (!logged_once) {              \
      NOTIMPLEMENTED();              \
      logged_once = true;            \
    }                                \
  }                                  \
  EAT_CHECK_STREAM_PARAMS()
>>>>>>> chromium

}  // namespace logging

#endif  // BASE_NOTREACHED_H_
