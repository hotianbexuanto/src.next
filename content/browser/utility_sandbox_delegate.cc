// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/utility_sandbox_delegate.h"

#include "base/check.h"
#include "build/build_config.h"
<<<<<<< HEAD
#include "content/common/features.h"
#include "content/public/common/sandboxed_process_launcher_delegate.h"
#include "content/public/common/zygote/zygote_buildflags.h"
#include "ppapi/buildflags/buildflags.h"
#include "sandbox/policy/mojom/sandbox.mojom.h"

#if BUILDFLAG(IS_WIN)
#include "content/public/browser/content_browser_client.h"
#include "content/public/common/content_client.h"
#endif  // BUILDFLAG(IS_WIN)

#if BUILDFLAG(USE_ZYGOTE)
#include "content/common/zygote/zygote_handle_impl_linux.h"
=======
#include "build/chromeos_buildflags.h"
#include "content/public/common/sandboxed_process_launcher_delegate.h"
#include "content/public/common/zygote/zygote_buildflags.h"
#include "printing/buildflags/buildflags.h"
>>>>>>> chromium
#include "sandbox/policy/sandbox_type.h"

#if BUILDFLAG(USE_ZYGOTE_HANDLE)
#include "content/common/zygote/zygote_handle_impl_linux.h"
#endif

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
#include "chromeos/ash/components/assistant/buildflags.h"
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
#include "chromeos/assistant/buildflags.h"
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

namespace content {

UtilitySandboxedProcessLauncherDelegate::
    UtilitySandboxedProcessLauncherDelegate(
        sandbox::policy::SandboxType sandbox_type,
        const base::EnvironmentMap& env,
        const base::CommandLine& cmd_line)
    :
#if defined(OS_POSIX)
      env_(env),
#endif
      sandbox_type_(sandbox_type),
      cmd_line_(cmd_line) {
#if DCHECK_IS_ON()
  bool supported_sandbox_type =
      sandbox_type_ == sandbox::policy::SandboxType::kNoSandbox ||
#if defined(OS_WIN)
      sandbox_type_ ==
          sandbox::policy::SandboxType::kNoSandboxAndElevatedPrivileges ||
      sandbox_type_ == sandbox::policy::SandboxType::kXrCompositing ||
      sandbox_type_ == sandbox::policy::SandboxType::kProxyResolver ||
      sandbox_type_ == sandbox::policy::SandboxType::kPdfConversion ||
      sandbox_type_ == sandbox::policy::SandboxType::kIconReader ||
      sandbox_type_ == sandbox::policy::SandboxType::kMediaFoundationCdm ||
#endif
#if defined(OS_MAC)
      sandbox_type_ == sandbox::policy::SandboxType::kMirroring ||
#endif
<<<<<<< HEAD
      sandbox_type_ == sandbox::mojom::Sandbox::kUtility ||
      sandbox_type_ == sandbox::mojom::Sandbox::kService ||
      sandbox_type_ == sandbox::mojom::Sandbox::kServiceWithJit ||
      sandbox_type_ == sandbox::mojom::Sandbox::kNetwork ||
      sandbox_type_ == sandbox::mojom::Sandbox::kOnDeviceModelExecution ||
      sandbox_type_ == sandbox::mojom::Sandbox::kCdm ||
      sandbox_type_ == sandbox::mojom::Sandbox::kPrintCompositor ||
#if BUILDFLAG(ENABLE_PPAPI) && !BUILDFLAG(IS_WIN)
      sandbox_type_ == sandbox::mojom::Sandbox::kPpapi ||
#endif
#if BUILDFLAG(IS_FUCHSIA)
      sandbox_type_ == sandbox::mojom::Sandbox::kVideoCapture ||
#endif
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
      sandbox_type_ == sandbox::mojom::Sandbox::kHardwareVideoDecoding ||
      sandbox_type_ == sandbox::mojom::Sandbox::kHardwareVideoEncoding ||
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(IS_CHROMEOS)
      sandbox_type_ == sandbox::mojom::Sandbox::kIme ||
      sandbox_type_ == sandbox::mojom::Sandbox::kTts ||
      sandbox_type_ == sandbox::mojom::Sandbox::kNearby ||
=======
      sandbox_type_ == sandbox::policy::SandboxType::kUtility ||
      sandbox_type_ == sandbox::policy::SandboxType::kNetwork ||
      sandbox_type_ == sandbox::policy::SandboxType::kCdm ||
#if BUILDFLAG(ENABLE_PRINTING)
      sandbox_type_ == sandbox::policy::SandboxType::kPrintBackend ||
#endif
      sandbox_type_ == sandbox::policy::SandboxType::kPrintCompositor ||
      sandbox_type_ == sandbox::policy::SandboxType::kPpapi ||
      sandbox_type_ == sandbox::policy::SandboxType::kVideoCapture ||
#if BUILDFLAG(IS_CHROMEOS_ASH)
      sandbox_type_ == sandbox::policy::SandboxType::kIme ||
      sandbox_type_ == sandbox::policy::SandboxType::kTts ||
>>>>>>> chromium
#if BUILDFLAG(ENABLE_CROS_LIBASSISTANT)
      sandbox_type_ == sandbox::policy::SandboxType::kLibassistant ||
#endif  // BUILDFLAG(ENABLE_CROS_LIBASSISTANT)
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || \
    BUILDFLAG(IS_WIN)
      sandbox_type_ == sandbox::mojom::Sandbox::kScreenAI ||
      sandbox_type_ == sandbox::mojom::Sandbox::kPrintBackend ||
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
      sandbox_type_ == sandbox::policy::SandboxType::kAudio ||
#if !defined(OS_MAC)
      sandbox_type_ == sandbox::policy::SandboxType::kService ||
>>>>>>> chromium
#endif
      sandbox_type_ == sandbox::policy::SandboxType::kSpeechRecognition;
  DCHECK(supported_sandbox_type);
#endif  // DCHECK_IS_ON()
}

UtilitySandboxedProcessLauncherDelegate::
    ~UtilitySandboxedProcessLauncherDelegate() {}

sandbox::policy::SandboxType
UtilitySandboxedProcessLauncherDelegate::GetSandboxType() {
  return sandbox_type_;
}

#if defined(OS_POSIX)
base::EnvironmentMap UtilitySandboxedProcessLauncherDelegate::GetEnvironment() {
  return env_;
}
#endif  // OS_POSIX

#if BUILDFLAG(USE_ZYGOTE_HANDLE)
ZygoteHandle UtilitySandboxedProcessLauncherDelegate::GetZygote() {
  // If the sandbox has been disabled for a given type, don't use a zygote.
  if (sandbox::policy::IsUnsandboxedSandboxType(sandbox_type_))
    return nullptr;

  // Utility processes which need specialized sandboxes fork from the
  // unsandboxed zygote and then apply their actual sandboxes in the forked
  // process upon startup.
<<<<<<< HEAD
  if (sandbox_type_ == sandbox::mojom::Sandbox::kNetwork ||
      sandbox_type_ == sandbox::mojom::Sandbox::kOnDeviceModelExecution ||
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
      sandbox_type_ == sandbox::mojom::Sandbox::kHardwareVideoDecoding ||
      sandbox_type_ == sandbox::mojom::Sandbox::kHardwareVideoEncoding ||
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(IS_CHROMEOS)
      sandbox_type_ == sandbox::mojom::Sandbox::kIme ||
      sandbox_type_ == sandbox::mojom::Sandbox::kTts ||
      sandbox_type_ == sandbox::mojom::Sandbox::kNearby ||
=======
  if (sandbox_type_ == sandbox::policy::SandboxType::kNetwork ||
#if BUILDFLAG(IS_CHROMEOS_ASH)
      sandbox_type_ == sandbox::policy::SandboxType::kIme ||
      sandbox_type_ == sandbox::policy::SandboxType::kTts ||
>>>>>>> chromium
#if BUILDFLAG(ENABLE_CROS_LIBASSISTANT)
      sandbox_type_ == sandbox::policy::SandboxType::kLibassistant ||
#endif  // BUILDFLAG(ENABLE_CROS_LIBASSISTANT)
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_CHROMEOS)
      sandbox_type_ == sandbox::mojom::Sandbox::kAudio ||
#if BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || \
    BUILDFLAG(IS_WIN)
      sandbox_type_ == sandbox::mojom::Sandbox::kPrintBackend ||
      sandbox_type_ == sandbox::mojom::Sandbox::kScreenAI ||
#endif
#if BUILDFLAG(IS_LINUX)
      sandbox_type_ == sandbox::mojom::Sandbox::kVideoEffects ||
      sandbox_type_ == sandbox::mojom::Sandbox::kOnDeviceTranslation ||
#endif  // BUILDFLAG(IS_LINUX)
      sandbox_type_ == sandbox::mojom::Sandbox::kSpeechRecognition) {
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
      sandbox_type_ == sandbox::policy::SandboxType::kAudio ||
#if BUILDFLAG(ENABLE_PRINTING)
      sandbox_type_ == sandbox::policy::SandboxType::kPrintBackend ||
#endif
      sandbox_type_ == sandbox::policy::SandboxType::kSpeechRecognition) {
>>>>>>> chromium
    return GetUnsandboxedZygote();
  }

  // All other types use the pre-sandboxed zygote.
  return GetGenericZygote();
}
#endif  // BUILDFLAG(USE_ZYGOTE_HANDLE)

}  // namespace content
