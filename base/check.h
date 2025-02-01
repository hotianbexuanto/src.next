// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_CHECK_H_
#define BASE_CHECK_H_

#include <iosfwd>

#include "base/base_export.h"
#include "base/compiler_specific.h"
#include "base/dcheck_is_on.h"
#include "base/immediate_crash.h"

// This header defines the CHECK, DCHECK, and DPCHECK macros.
//
// CHECK dies with a fatal error if its condition is not true. It is not
// controlled by NDEBUG, so the check will be executed regardless of compilation
// mode.
//
// DCHECK, the "debug mode" check, is enabled depending on NDEBUG and
// DCHECK_ALWAYS_ON, and its severity depends on DCHECK_IS_CONFIGURABLE.
//
// (D)PCHECK is like (D)CHECK, but includes the system error code (c.f.
// perror(3)).
//
// Additional information can be streamed to these macros and will be included
// in the log output if the condition doesn't hold (you may need to include
// <ostream>):
//
//   CHECK(condition) << "Additional info.";
//
// The condition is evaluated exactly once. Even in build modes where e.g.
// DCHECK is disabled, the condition and any stream arguments are still
// referenced to avoid warnings about unused variables and functions.
//
// For the (D)CHECK_EQ, etc. macros, see base/check_op.h. However, that header
// is *significantly* larger than check.h, so try to avoid including it in
// header files.

namespace logging {

// Class used to explicitly ignore an ostream, and optionally a boolean value.
class VoidifyStream {
 public:
  VoidifyStream() = default;
  explicit VoidifyStream(bool ignored) {}

  // This operator has lower precedence than << but higher than ?:
  void operator&(std::ostream&) {}
};

// Helper macro which avoids evaluating the arguents to a stream if the
// condition is false.
#define LAZY_CHECK_STREAM(stream, condition) \
  !(condition) ? (void)0 : ::logging::VoidifyStream() & (stream)

// Macro which uses but does not evaluate expr and any stream parameters.
#define EAT_CHECK_STREAM_PARAMS(expr) \
  true ? (void)0                      \
       : ::logging::VoidifyStream(expr) & (*::logging::g_swallow_stream)
BASE_EXPORT extern std::ostream* g_swallow_stream;

class CheckOpResult;
class LogMessage;

// Class used for raising a check error upon destruction.
class BASE_EXPORT CheckError {
 public:
<<<<<<< HEAD
  // All instances that take a base::Location should use
  // base::Location::CurrentWithoutFunctionName() by default since we
  // immediately pass file_name() and line_number() to LogMessage's constructor
  // and discard the function_name() anyways. This saves ~23k on the Android
  // size bots (as of 2024-12-17) but that's the official build that barely uses
  // these for CHECKs. The size gains are believed to be significantly larger on
  // developer builds and official+DCHECK where all CHECK failures generate
  // logs.

  static CheckError Check(const char* condition,
                          base::NotFatalUntil fatal_milestone,
                          const base::Location& location =
                              base::Location::CurrentWithoutFunctionName());
  // Takes ownership over (free()s after using) `log_message_str`, for use with
  // CHECK_op macros.
  static CheckError CheckOp(char* log_message_str,
                            base::NotFatalUntil fatal_milestone,
                            const base::Location& location =
                                base::Location::CurrentWithoutFunctionName());

  static CheckError DCheck(const char* condition,
                           const base::Location& location =
                               base::Location::CurrentWithoutFunctionName());
  // Takes ownership over (free()s after using) `log_message_str`, for use with
  // DCHECK_op macros.
  static CheckError DCheckOp(char* log_message_str,
                             const base::Location& location =
                                 base::Location::CurrentWithoutFunctionName());

  static CheckError DumpWillBeCheck(
      const char* condition,
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());
  // Takes ownership over (free()s after using) `log_message_str`, for use with
  // DUMP_WILL_BE_CHECK_op macros.
  static CheckError DumpWillBeCheckOp(
      char* log_message_str,
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());

  static CheckError DPCheck(const char* condition,
                            const base::Location& location =
                                base::Location::CurrentWithoutFunctionName());

  static CheckError NotImplemented(
      const char* function,
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());
=======
  static CheckError Check(const char* file, int line, const char* condition);
  static CheckError CheckOp(const char* file, int line, CheckOpResult* result);

  static CheckError DCheck(const char* file, int line, const char* condition);
  static CheckError DCheckOp(const char* file, int line, CheckOpResult* result);

  static CheckError PCheck(const char* file, int line, const char* condition);
  static CheckError PCheck(const char* file, int line);

  static CheckError DPCheck(const char* file, int line, const char* condition);

  static CheckError NotImplemented(const char* file,
                                   int line,
                                   const char* function);
>>>>>>> chromium

  // Stream for adding optional details to the error message.
  std::ostream& stream();

  NOMERGE ~CheckError();

<<<<<<< HEAD
  CheckError(const CheckError&) = delete;
  CheckError& operator=(const CheckError&) = delete;

  template <typename T>
  std::ostream& operator<<(T&& streamed_type) {
    return stream() << streamed_type;
  }

 protected:
  // Takes ownership of `log_message`.
  explicit CheckError(LogMessage* log_message);

  std::unique_ptr<LogMessage> log_message_;
};

// Used for NOTREACHED(), its destructor is importantly [[noreturn]].
class BASE_EXPORT CheckNoreturnError : public CheckError {
 public:
  [[noreturn]] NOMERGE NOINLINE NOT_TAIL_CALLED ~CheckNoreturnError();

  static CheckNoreturnError Check(
      const char* condition,
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());
  // Takes ownership over (free()s after using) `log_message_str`, for use with
  // CHECK_op macros.
  static CheckNoreturnError CheckOp(
      char* log_message_str,
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());

  static CheckNoreturnError PCheck(
      const char* condition,
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());
  static CheckNoreturnError PCheck(
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());

 private:
  using CheckError::CheckError;
};

// Used for NOTREACHED(base::NotFatalUntil) and DUMP_WILL_BE_NOTREACHED().
class BASE_EXPORT NotReachedError : public CheckError {
 public:
  static NotReachedError NotReached(
      base::NotFatalUntil fatal_milestone,
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());

  static NotReachedError DumpWillBeNotReached(
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());

  NOMERGE NOINLINE NOT_TAIL_CALLED ~NotReachedError();
=======
  CheckError(const CheckError& other) = delete;
  CheckError& operator=(const CheckError& other) = delete;
  CheckError(CheckError&& other) = default;
  CheckError& operator=(CheckError&& other) = default;
>>>>>>> chromium

 private:
  explicit CheckError(LogMessage* log_message);

  LogMessage* log_message_;
};

<<<<<<< HEAD
// Used for NOTREACHED(), its destructor is importantly [[noreturn]].
class BASE_EXPORT NotReachedNoreturnError : public CheckError {
 public:
  explicit NotReachedNoreturnError(
      const base::Location& location =
          base::Location::CurrentWithoutFunctionName());

  [[noreturn]] NOMERGE NOINLINE NOT_TAIL_CALLED ~NotReachedNoreturnError();
};

// A helper macro for checks that log to streams that makes it easier for the
// compiler to identify and warn about dead code, e.g.:
//
//   return 2;
//   NOTREACHED_IN_MIGRATION();
//
// The 'switch' is used to prevent the 'else' from being ambiguous when the
// macro is used in an 'if' clause such as:
// if (a == 1)
//   CHECK(Foo());
//
// The weird ternary is to still generate an "is not contextually convertible to
// 'bool' when provided weird parameters (regardless of ANALYZER_ASSUME_TRUE's
// implementation). See base/check_nocompile.nc.
#define LOGGING_CHECK_FUNCTION_IMPL(check_stream, condition) \
  switch (0)                                                 \
  case 0:                                                    \
  default:                                                   \
    if (ANALYZER_ASSUME_TRUE((condition) ? true : false))    \
      [[likely]];                                            \
    else                                                     \
      (check_stream)

// A helper macro like LOGGING_CHECK_FUNCTION_IMPL above but discarding any
// log-stream parameters rather than evaluate them on failure.
#define DISCARDING_CHECK_FUNCTION_IMPL(check_failure, condition) \
  switch (0)                                                     \
  case 0:                                                        \
  default:                                                       \
    if (!ANALYZER_ASSUME_TRUE((condition) ? true : false))       \
      check_failure;                                             \
    else [[likely]]                                              \
      EAT_CHECK_STREAM_PARAMS()

#if defined(OFFICIAL_BUILD) && !defined(NDEBUG)
#error "Debug builds are not expected to be optimized as official builds."
#endif  // defined(OFFICIAL_BUILD) && !defined(NDEBUG)

#if defined(OFFICIAL_BUILD) && !DCHECK_IS_ON()

// Official non-DCHECK builds do not preserve CHECK() logging (including
// evaluation of logging arguments). This generates more compact code which is
// good for both speed and binary size.
#define CHECK_WILL_STREAM() false

// Note that this uses IMMEDIATE_CRASH_ALWAYS_INLINE to force-inline in debug
// mode as well. See LoggingTest.CheckCausesDistinctBreakpoints.
[[noreturn]] NOMERGE IMMEDIATE_CRASH_ALWAYS_INLINE void CheckFailure() {
  base::ImmediateCrash();
}

// Discard log strings to reduce code bloat when there is no NotFatalUntil
// argument (which temporarily preserves logging both locally and in crash
// reports).
#define CHECK_INTERNAL_IMPL(cond) \
  DISCARDING_CHECK_FUNCTION_IMPL(::logging::CheckFailure(), cond)

#else

// Generate logging versions of CHECKs to help diagnosing failures.
#define CHECK_WILL_STREAM() true

#define CHECK_INTERNAL_IMPL(cond) \
  LOGGING_CHECK_FUNCTION_IMPL(::logging::CheckNoreturnError::Check(#cond), cond)
=======
#if defined(OFFICIAL_BUILD) && defined(NDEBUG)

// Discard log strings to reduce code bloat.
//
// This is not calling BreakDebugger since this is called frequently, and
// calling an out-of-line function instead of a noreturn inline macro prevents
// compiler optimizations.
#define CHECK(condition) \
  UNLIKELY(!(condition)) ? IMMEDIATE_CRASH() : EAT_CHECK_STREAM_PARAMS()

#define PCHECK(condition)                                         \
  LAZY_CHECK_STREAM(                                              \
      ::logging::CheckError::PCheck(__FILE__, __LINE__).stream(), \
      UNLIKELY(!(condition)))

#else

#define CHECK(condition)                                                     \
  LAZY_CHECK_STREAM(                                                         \
      ::logging::CheckError::Check(__FILE__, __LINE__, #condition).stream(), \
      !ANALYZER_ASSUME_TRUE(condition))

#define PCHECK(condition)                                                     \
  LAZY_CHECK_STREAM(                                                          \
      ::logging::CheckError::PCheck(__FILE__, __LINE__, #condition).stream(), \
      !ANALYZER_ASSUME_TRUE(condition))
>>>>>>> chromium

#endif

#define CHECK(cond, ...)                                         \
  BASE_IF(BASE_IS_EMPTY(__VA_ARGS__), CHECK_INTERNAL_IMPL(cond), \
          LOGGING_CHECK_FUNCTION_IMPL(                           \
              logging::CheckError::Check(#cond, __VA_ARGS__), cond))

// Strip the conditional string based on CHECK_WILL_STREAM()
#define PCHECK(cond)                                        \
  LOGGING_CHECK_FUNCTION_IMPL(                              \
      BASE_IF(CHECK_WILL_STREAM(),                          \
              ::logging::CheckNoreturnError::PCheck(#cond), \
              ::logging::CheckNoreturnError::PCheck()),     \
      cond)

#if DCHECK_IS_ON()

#define DCHECK(condition)                                                     \
  LAZY_CHECK_STREAM(                                                          \
      ::logging::CheckError::DCheck(__FILE__, __LINE__, #condition).stream(), \
      !ANALYZER_ASSUME_TRUE(condition))

#define DPCHECK(condition)                                                     \
  LAZY_CHECK_STREAM(                                                           \
      ::logging::CheckError::DPCheck(__FILE__, __LINE__, #condition).stream(), \
      !ANALYZER_ASSUME_TRUE(condition))

#else

#define DCHECK(condition) EAT_CHECK_STREAM_PARAMS(!(condition))
#define DPCHECK(condition) EAT_CHECK_STREAM_PARAMS(!(condition))

#endif

// Async signal safe checking mechanism.
BASE_EXPORT void RawCheck(const char* message);
#define RAW_CHECK(condition)                                 \
  do {                                                       \
    if (!(condition))                                        \
      ::logging::RawCheck("Check failed: " #condition "\n"); \
  } while (0)

}  // namespace logging

#endif  // BASE_CHECK_H_
