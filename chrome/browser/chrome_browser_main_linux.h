// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Contains functions used by BrowserMain() that are linux-specific.

#ifndef CHROME_BROWSER_CHROME_BROWSER_MAIN_LINUX_H_
#define CHROME_BROWSER_CHROME_BROWSER_MAIN_LINUX_H_

<<<<<<< HEAD
#include "base/memory/scoped_refptr.h"
#include "build/build_config.h"
#include "build/config/linux/dbus/buildflags.h"
#include "chrome/browser/chrome_browser_main_posix.h"

#if BUILDFLAG(IS_CHROMEOS)
namespace metrics {
class StackSamplingRecorder;
}
#endif

=======
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/chrome_browser_main_posix.h"

>>>>>>> chromium
class ChromeBrowserMainPartsLinux : public ChromeBrowserMainPartsPosix {
 public:
  ChromeBrowserMainPartsLinux(const content::MainFunctionParams& parameters,
                              StartupData* startup_data);
  ~ChromeBrowserMainPartsLinux() override;

  // ChromeBrowserMainParts overrides.
  void PreProfileInit() override;
<<<<<<< HEAD
#if BUILDFLAG(USE_DBUS) && !BUILDFLAG(IS_CHROMEOS)
  // Only needed for native Linux, to set up the low-memory-monitor-based memory
  // monitoring (which depends on D-Bus).
  void PostBrowserStart() override;
#endif
  void PostDestroyThreads() override;

 private:
#if BUILDFLAG(IS_CHROMEOS)
  // Used by ChromeOS tast tests. This is used by both Lacros and Ash, which
  // is why it's in ChromeBrowserMainPartsLinux, even though it's not used in
  // Linux. ChromeBrowserMainPartsLinux is the base class of both
  // ChromeBrowserMainPartsAsh and ChromeBrowserMainPartsLacros.
  scoped_refptr<metrics::StackSamplingRecorder> stack_sampling_recorder_;
#endif
=======
  void PostCreateMainMessageLoop() override;
  void PostDestroyThreads() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeBrowserMainPartsLinux);
>>>>>>> chromium
};

#endif  // CHROME_BROWSER_CHROME_BROWSER_MAIN_LINUX_H_
