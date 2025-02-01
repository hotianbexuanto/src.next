// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef UNSAFE_BUFFERS_BUILD
// TODO(crbug.com/390223051): Remove C-library calls to fix the errors.
#pragma allow_unsafe_libc_calls
#endif

#include "base/check.h"

// check.h is a widely included header and its size has significant impact on
// build time. Try not to raise this limit unless absolutely necessary. See
// https://chromium.googlesource.com/chromium/src/+/HEAD/docs/wmax_tokens.md
#ifndef NACL_TC_REV
#pragma clang max_tokens_here 17000
#endif

#include "base/check_op.h"
#include "base/logging.h"
#include "build/build_config.h"

namespace logging {

CheckError CheckError::Check(const char* file,
                             int line,
                             const char* condition) {
  CheckError check_error(new LogMessage(file, line, LOGGING_FATAL));
  check_error.stream() << "Check failed: " << condition << ". ";
  return check_error;
}

CheckError CheckError::CheckOp(const char* file,
                               int line,
                               CheckOpResult* check_op_result) {
  CheckError check_error(new LogMessage(file, line, LOGGING_FATAL));
  check_error.stream() << "Check failed: " << check_op_result->message_;
  free(check_op_result->message_);
  check_op_result->message_ = nullptr;
  return check_error;
}

CheckError CheckError::DCheck(const char* file,
                              int line,
                              const char* condition) {
  CheckError check_error(new LogMessage(file, line, LOGGING_DCHECK));
  check_error.stream() << "Check failed: " << condition << ". ";
  return check_error;
}

CheckError CheckError::DCheckOp(const char* file,
                                int line,
                                CheckOpResult* check_op_result) {
  CheckError check_error(new LogMessage(file, line, LOGGING_DCHECK));
  check_error.stream() << "Check failed: " << check_op_result->message_;
  free(check_op_result->message_);
  check_op_result->message_ = nullptr;
  return check_error;
}

<<<<<<< HEAD
base::debug::CrashKeyString* GetDCheckCrashKey() {
#if BUILDFLAG(IS_NACL)
  return nullptr;
#else
  static auto* const key = ::base::debug::AllocateCrashKeyString(
      "Logging-DCHECK_MESSAGE", base::debug::CrashKeySize::Size1024);
  return key;
#endif  // BUILDFLAG(IS_NACL)
}

base::debug::CrashKeyString* GetDumpWillBeCheckCrashKey() {
#if BUILDFLAG(IS_NACL)
  return nullptr;
#else
  static auto* const key = ::base::debug::AllocateCrashKeyString(
      "Logging-DUMP_WILL_BE_CHECK_MESSAGE",
      base::debug::CrashKeySize::Size1024);
  return key;
#endif  // BUILDFLAG(IS_NACL)
}

#if !BUILDFLAG(IS_NACL)
base::debug::CrashKeyString* GetFatalMilestoneCrashKey() {
  static auto* const key = ::base::debug::AllocateCrashKeyString(
      "Logging-FATAL_MILESTONE", base::debug::CrashKeySize::Size32);
  return key;
}
#endif  // BUILDFLAG(IS_NACL)

void MaybeSetFatalMilestoneCrashKey(base::NotFatalUntil fatal_milestone) {
#if !BUILDFLAG(IS_NACL)
  if (fatal_milestone == base::NotFatalUntil::NoSpecifiedMilestoneInternal) {
    return;
  }
  base::debug::SetCrashKeyString(
      GetFatalMilestoneCrashKey(),
      base::NumberToString(base::to_underlying(fatal_milestone)));
#endif  // BUILDFLAG(IS_NACL)
}

void DumpWithoutCrashing(base::debug::CrashKeyString* message_key,
                         const logging::LogMessage* log_message,
                         const base::Location& location,
                         base::NotFatalUntil fatal_milestone) {
  const std::string crash_string = log_message->BuildCrashString();
#if !BUILDFLAG(IS_NACL)
  base::debug::ScopedCrashKeyString scoped_message_key(message_key,
                                                       crash_string);

  MaybeSetFatalMilestoneCrashKey(fatal_milestone);
#endif  // !BUILDFLAG(IS_NACL)
  // Copy the crash message to stack memory to make sure it can be recovered in
  // crash dumps. This is easier to recover in minidumps than crash keys during
  // local debugging.
  DEBUG_ALIAS_FOR_CSTR(log_message_str, crash_string.c_str(), 1024);

  // Report from the same location at most once every 30 days (unless the
  // process has died). This attempts to prevent us from flooding ourselves with
  // repeat reports for the same bug.
  base::debug::DumpWithoutCrashing(location, base::Days(30));

#if !BUILDFLAG(IS_NACL)
  base::debug::ClearCrashKeyString(GetFatalMilestoneCrashKey());
#endif  // !BUILDFLAG(IS_NACL)
}

void HandleCheckErrorLogMessage(base::debug::CrashKeyString* message_key,
                                const logging::LogMessage* log_message,
                                const base::Location& location,
                                base::NotFatalUntil fatal_milestone) {
  if (log_message->severity() == logging::LOGGING_FATAL) {
    // Set NotFatalUntil key if applicable for when we die in ~LogMessage.
    MaybeSetFatalMilestoneCrashKey(fatal_milestone);
  } else {
    DumpWithoutCrashing(message_key, log_message, location, fatal_milestone);
  }
}

class NotReachedLogMessage : public LogMessage {
 public:
  NotReachedLogMessage(const base::Location& location,
                       LogSeverity severity,
                       base::NotFatalUntil fatal_milestone)
      : LogMessage(location.file_name(), location.line_number(), severity),
        location_(location),
        fatal_milestone_(fatal_milestone) {}
  ~NotReachedLogMessage() override {
    HandleCheckErrorLogMessage(GetNotReachedCrashKey(), this, location_,
                               fatal_milestone_);
  }

 private:
  const base::Location location_;
  const base::NotFatalUntil fatal_milestone_;
};

class DCheckLogMessage : public LogMessage {
 public:
  explicit DCheckLogMessage(const base::Location& location)
      : LogMessage(location.file_name(),
                   location.line_number(),
                   LOGGING_DCHECK),
        location_(location) {}
  ~DCheckLogMessage() override {
    HandleCheckErrorLogMessage(
        GetDCheckCrashKey(), this, location_,
        base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  }

 private:
  const base::Location location_;
};

class CheckLogMessage : public LogMessage {
 public:
  CheckLogMessage(const base::Location& location,
                  LogSeverity severity,
                  base::NotFatalUntil fatal_milestone)
      : LogMessage(location.file_name(), location.line_number(), severity),
        location_(location),
        fatal_milestone_(fatal_milestone) {}
  ~CheckLogMessage() override {
    HandleCheckErrorLogMessage(GetDumpWillBeCheckCrashKey(), this, location_,
                               fatal_milestone_);
  }

 private:
  const base::Location location_;
  const base::NotFatalUntil fatal_milestone_;
};

#if BUILDFLAG(IS_WIN)
class DCheckWin32ErrorLogMessage : public Win32ErrorLogMessage {
 public:
  DCheckWin32ErrorLogMessage(const base::Location& location,
                             SystemErrorCode err)
      : Win32ErrorLogMessage(location.file_name(),
                             location.line_number(),
                             LOGGING_DCHECK,
                             err),
        location_(location) {}
  ~DCheckWin32ErrorLogMessage() override {
    HandleCheckErrorLogMessage(
        GetDCheckCrashKey(), this, location_,
        base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  }

 private:
  const base::Location location_;
};
#elif BUILDFLAG(IS_POSIX) || BUILDFLAG(IS_FUCHSIA)
class DCheckErrnoLogMessage : public ErrnoLogMessage {
 public:
  DCheckErrnoLogMessage(const base::Location& location, SystemErrorCode err)
      : ErrnoLogMessage(location.file_name(),
                        location.line_number(),
                        LOGGING_DCHECK,
                        err),
        location_(location) {}
  ~DCheckErrnoLogMessage() override {
    HandleCheckErrorLogMessage(
        GetDCheckCrashKey(), this, location_,
        base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  }

 private:
  const base::Location location_;
};
#endif  // BUILDFLAG(IS_WIN)

}  // namespace

CheckError CheckError::Check(const char* condition,
                             base::NotFatalUntil fatal_milestone,
                             const base::Location& location) {
  auto* const log_message = new CheckLogMessage(
      location, GetCheckSeverity(fatal_milestone), fatal_milestone);
  log_message->stream() << "Check failed: " << condition << ". ";
  return CheckError(log_message);
}

CheckError CheckError::CheckOp(char* log_message_str,
                               base::NotFatalUntil fatal_milestone,
                               const base::Location& location) {
  auto* const log_message = new CheckLogMessage(
      location, GetCheckSeverity(fatal_milestone), fatal_milestone);
  log_message->stream() << log_message_str;
  free(log_message_str);
  return CheckError(log_message);
}

CheckError CheckError::DCheck(const char* condition,
                              const base::Location& location) {
  auto* const log_message = new DCheckLogMessage(location);
  log_message->stream() << "Check failed: " << condition << ". ";
  return CheckError(log_message);
}

CheckError CheckError::DCheckOp(char* log_message_str,
                                const base::Location& location) {
  auto* const log_message = new DCheckLogMessage(location);
  log_message->stream() << log_message_str;
  free(log_message_str);
  return CheckError(log_message);
}

CheckError CheckError::DumpWillBeCheck(const char* condition,
                                       const base::Location& location) {
  auto* const log_message =
      new CheckLogMessage(location, GetDumpSeverity(),
                          base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  log_message->stream() << "Check failed: " << condition << ". ";
  return CheckError(log_message);
}

CheckError CheckError::DumpWillBeCheckOp(char* log_message_str,
                                         const base::Location& location) {
  auto* const log_message =
      new CheckLogMessage(location, GetDumpSeverity(),
                          base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  log_message->stream() << log_message_str;
  free(log_message_str);
  return CheckError(log_message);
}

CheckError CheckError::DPCheck(const char* condition,
                               const base::Location& location) {
=======
CheckError CheckError::PCheck(const char* file,
                              int line,
                              const char* condition) {
  SystemErrorCode err_code = logging::GetLastSystemErrorCode();
#if defined(OS_WIN)
  CheckError check_error(
      new Win32ErrorLogMessage(file, line, LOGGING_FATAL, err_code));
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
  CheckError check_error(
      new ErrnoLogMessage(file, line, LOGGING_FATAL, err_code));
#endif
  check_error.stream() << "Check failed: " << condition << ". ";
  return check_error;
}

CheckError CheckError::PCheck(const char* file, int line) {
  return PCheck(file, line, "");
}

CheckError CheckError::DPCheck(const char* file,
                               int line,
                               const char* condition) {
>>>>>>> chromium
  SystemErrorCode err_code = logging::GetLastSystemErrorCode();
#if defined(OS_WIN)
  CheckError check_error(
      new Win32ErrorLogMessage(file, line, LOGGING_DCHECK, err_code));
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
  CheckError check_error(
      new ErrnoLogMessage(file, line, LOGGING_DCHECK, err_code));
#endif
  check_error.stream() << "Check failed: " << condition << ". ";
  return check_error;
}

<<<<<<< HEAD
CheckError CheckError::NotImplemented(const char* function,
                                      const base::Location& location) {
  auto* const log_message = new LogMessage(
      location.file_name(), location.line_number(), LOGGING_ERROR);
  log_message->stream() << "Not implemented reached in " << function;
  return CheckError(log_message);
=======
CheckError CheckError::NotImplemented(const char* file,
                                      int line,
                                      const char* function) {
  CheckError check_error(new LogMessage(file, line, LOGGING_ERROR));
  check_error.stream() << "Not implemented reached in " << function;
  return check_error;
>>>>>>> chromium
}

std::ostream& CheckError::stream() {
  return log_message_->stream();
}

CheckError::~CheckError() {
  // Note: This function ends up in crash stack traces. If its full name
  // changes, the crash server's magic signature logic needs to be updated.
  // See cl/306632920.
  delete log_message_;
}

CheckError::CheckError(LogMessage* log_message) : log_message_(log_message) {}

<<<<<<< HEAD
// Note: This function ends up in crash stack traces. If its full name changes,
// the crash server's magic signature logic needs to be updated. See
// cl/306632920.
CheckNoreturnError::~CheckNoreturnError() {
  // Reset before `ImmediateCrash()` to ensure the message is flushed.
  log_message_.reset();

  // Make sure we die if we haven't.
  // TODO(crbug.com/40254046): Replace this with NOTREACHED() once LOG(FATAL) is
  // [[noreturn]].
  base::ImmediateCrash();
}

CheckNoreturnError CheckNoreturnError::Check(const char* condition,
                                             const base::Location& location) {
  auto* const log_message =
      new CheckLogMessage(location, LOGGING_FATAL,
                          base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  log_message->stream() << "Check failed: " << condition << ". ";
  return CheckNoreturnError(log_message);
}

CheckNoreturnError CheckNoreturnError::CheckOp(char* log_message_str,
                                               const base::Location& location) {
  auto* const log_message =
      new CheckLogMessage(location, LOGGING_FATAL,
                          base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  log_message->stream() << log_message_str;
  free(log_message_str);
  return CheckNoreturnError(log_message);
}

CheckNoreturnError CheckNoreturnError::PCheck(const char* condition,
                                              const base::Location& location) {
  SystemErrorCode err_code = logging::GetLastSystemErrorCode();
#if BUILDFLAG(IS_WIN)
  auto* const log_message = new Win32ErrorLogMessage(
      location.file_name(), location.line_number(), LOGGING_FATAL, err_code);
#elif BUILDFLAG(IS_POSIX) || BUILDFLAG(IS_FUCHSIA)
  auto* const log_message = new ErrnoLogMessage(
      location.file_name(), location.line_number(), LOGGING_FATAL, err_code);
#endif
  log_message->stream() << "Check failed: " << condition << ". ";
  return CheckNoreturnError(log_message);
}

CheckNoreturnError CheckNoreturnError::PCheck(const base::Location& location) {
  return PCheck("", location);
}

NotReachedError NotReachedError::NotReached(base::NotFatalUntil fatal_milestone,
                                            const base::Location& location) {
  auto* const log_message = new NotReachedLogMessage(
      location, GetCheckSeverity(fatal_milestone), fatal_milestone);

  // TODO(pbos): Consider a better message for NotReached(), this is here to
  // match existing behavior + test expectations.
  log_message->stream() << "Check failed: false. ";
  return NotReachedError(log_message);
}

NotReachedError NotReachedError::DumpWillBeNotReached(
    const base::Location& location) {
  auto* const log_message = new NotReachedLogMessage(
      location, GetDumpSeverity(),
      base::NotFatalUntil::NoSpecifiedMilestoneInternal);
  log_message->stream() << "NOTREACHED hit. ";
  return NotReachedError(log_message);
}

NotReachedError::~NotReachedError() = default;

NotReachedNoreturnError::NotReachedNoreturnError(const base::Location& location)
    : CheckError([location] {
        auto* const log_message = new NotReachedLogMessage(
            location, LOGGING_FATAL,
            base::NotFatalUntil::NoSpecifiedMilestoneInternal);
        log_message->stream() << "NOTREACHED hit. ";
        return log_message;
      }()) {}

// Note: This function ends up in crash stack traces. If its full name changes,
// the crash server's magic signature logic needs to be updated. See
// cl/306632920.
NotReachedNoreturnError::~NotReachedNoreturnError() {
  // Reset before `ImmediateCrash()` to ensure the message is flushed.
  log_message_.reset();

  // Make sure we die if we haven't.
  // TODO(crbug.com/40254046): Replace this with NOTREACHED() once LOG(FATAL) is
  // [[noreturn]].
  base::ImmediateCrash();
}

void RawCheckFailure(const char* message) {
=======
void RawCheck(const char* message) {
>>>>>>> chromium
  RawLog(LOGGING_FATAL, message);
}

}  // namespace logging
