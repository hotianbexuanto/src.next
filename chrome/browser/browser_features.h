// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file defines the browser-specific base::FeatureList features that are
// not shared with other process types.

#ifndef CHROME_BROWSER_BROWSER_FEATURES_H_
#define CHROME_BROWSER_BROWSER_FEATURES_H_

#include "base/feature_list.h"
#include "build/build_config.h"
#include "build/chromeos_buildflags.h"

namespace features {

// All features in alphabetical order. The features should be documented
// alongside the definition of their values in the .cc file.

extern const base::Feature kClosedTabCache;

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kContentUsesBrowserThemeColorMode);

#if BUILDFLAG(IS_LINUX)
BASE_DECLARE_FEATURE(kDbusSecretPortal);
BASE_DECLARE_FEATURE(kUseFreedesktopSecretKeyProvider);
#endif

BASE_DECLARE_FEATURE(kDestroyProfileOnBrowserClose);
BASE_DECLARE_FEATURE(kDestroySystemProfiles);

#if BUILDFLAG(IS_CHROMEOS)
BASE_DECLARE_FEATURE(kDoubleTapToZoomInTabletMode);
#endif

BASE_DECLARE_FEATURE(kFlexOrgManagementDisclosure);
BASE_DECLARE_FEATURE(kIncomingCallNotifications);

#if !BUILDFLAG(IS_ANDROID)
BASE_DECLARE_FEATURE(kMuteNotificationSnoozeAction);
#endif

BASE_DECLARE_FEATURE(kNetworkAnnotationMonitoring);
BASE_DECLARE_FEATURE(kNewTabPageTriggerForPrerender2);
// This parameter is used to set a time threshold for triggering onMouseHover
// prerender. For example, if the value is 300, the New Tab Page prerender
// will start after 300ms after mouseHover duration is over 300ms.
const base::FeatureParam<int>
    kNewTabPagePrerenderStartDelayOnMouseHoverByMiliSeconds{
        &features::kNewTabPageTriggerForPrerender2,
        "prerender_start_delay_on_mouse_hover_ms", 300};
const base::FeatureParam<int>
    kNewTabPagePreconnectStartDelayOnMouseHoverByMiliSeconds{
        &features::kNewTabPageTriggerForPrerender2,
        "preconnect_start_delay_on_mouse_hover_ms", 100};
const base::FeatureParam<bool> kPrerenderNewTabPageOnMousePressedTrigger{
    &features::kNewTabPageTriggerForPrerender2,
    "prerender_new_tab_page_on_mouse_pressed_trigger", true};
// The hover trigger is not enabled as we're aware that this negatively
// affects other navigations like Omnibox search.
const base::FeatureParam<bool> kPrerenderNewTabPageOnMouseHoverTrigger{
    &features::kNewTabPageTriggerForPrerender2,
    "prerender_new_tab_page_on_mouse_hover_trigger", false};

#if BUILDFLAG(IS_ANDROID)
BASE_DECLARE_FEATURE(kNotificationOneTapUnsubscribe);
extern base::FeatureParam<bool>
    kNotificationOneTapUnsubscribeUseServiceIntentParam;
#endif

BASE_DECLARE_FEATURE(kPromoBrowserCommands);
extern const char kBrowserCommandIdParam[];

#if !BUILDFLAG(IS_ANDROID)
BASE_DECLARE_FEATURE(kReadAnythingPermanentAccessibility);
=======
extern const base::Feature kDestroyProfileOnBrowserClose;

extern const base::Feature kPromoBrowserCommands;
extern const char kPromoBrowserCommandIdParam[];

#if BUILDFLAG(IS_CHROMEOS_ASH)
extern const base::Feature kDoubleTapToZoomInTabletMode;
extern const base::Feature kQuickSettingsPWANotifications;
#endif

#if !defined(OS_ANDROID)
extern const base::Feature kCopyLinkToText;
extern const base::Feature kMuteNotificationSnoozeAction;
>>>>>>> chromium
#endif

extern const base::Feature kPwaUpdateDialogForNameAndIcon;

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kRestartNetworkServiceUnsandboxedForFailedLaunch);
BASE_DECLARE_FEATURE(kSandboxExternalProtocolBlocked);
BASE_DECLARE_FEATURE(kSandboxExternalProtocolBlockedWarning);

#if BUILDFLAG(IS_LINUX)
BASE_DECLARE_FEATURE(kSecretPortalKeyProviderUseForEncryption);
BASE_DECLARE_FEATURE(kUseFreedesktopSecretKeyProviderForEncryption);
=======
#if !defined(OS_ANDROID) && !BUILDFLAG(IS_CHROMEOS_ASH)
extern const base::Feature kUserDataSnapshot;
>>>>>>> chromium
#endif

}  // namespace features

#endif  // CHROME_BROWSER_BROWSER_FEATURES_H_
