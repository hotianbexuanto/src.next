// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/browser_ui_prefs.h"

#include <memory>

#include "base/numerics/safe_conversions.h"
#include "build/build_config.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/upgrade_detector/upgrade_detector.h"
#include "chrome/common/buildflags.h"
#include "chrome/common/pref_names.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/scoped_user_pref_update.h"
#include "components/translate/core/browser/translate_pref_names.h"
#include "media/media_buildflags.h"
#include "third_party/blink/public/common/peerconnection/webrtc_ip_handling_policy.h"

#if !BUILDFLAG(IS_CHROMEOS)
#include "ui/accessibility/accessibility_features.h"
#endif

#if defined(OS_WIN)
#include "base/win/windows_version.h"
#endif

namespace {

uint32_t GetHomeButtonAndHomePageIsNewTabPageFlags() {
#if defined(OS_ANDROID)
  return PrefRegistry::NO_REGISTRATION_FLAGS;
#else
  return user_prefs::PrefRegistrySyncable::SYNCABLE_PREF;
#endif
}

}  // namespace

void RegisterBrowserPrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(prefs::kAllowFileSelectionDialogs, true);

#if !defined(OS_ANDROID)
  registry->RegisterIntegerPref(prefs::kRelaunchNotification, 0);
  registry->RegisterIntegerPref(
      prefs::kRelaunchNotificationPeriod,
      base::saturated_cast<int>(
          UpgradeDetector::GetDefaultHighAnnoyanceThreshold()
              .InMilliseconds()));
  registry->RegisterDictionaryPref(prefs::kRelaunchWindow);
#endif  // !defined(OS_ANDROID)

#if defined(OS_MAC)
  registry->RegisterIntegerPref(
      prefs::kMacRestoreLocationPermissionsExperimentCount, 0);
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_MAC)

  registry->RegisterBooleanPref(prefs::kHoverCardImagesEnabled, true);

  registry->RegisterBooleanPref(prefs::kHoverCardMemoryUsageEnabled, true);

#if defined(USE_AURA)
  registry->RegisterBooleanPref(prefs::kOverscrollHistoryNavigationEnabled,
                                true);
#endif
  registry->RegisterTimePref(prefs::kDefaultBrowserLastDeclinedTime,
                             base::Time());
  registry->RegisterIntegerPref(prefs::kDefaultBrowserDeclinedCount, 0);
  registry->RegisterTimePref(prefs::kDefaultBrowserFirstShownTime,
                             base::Time());
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
  registry->RegisterStringPref(prefs::kEnterpriseCustomLabelForBrowser,
                               std::string());
  registry->RegisterStringPref(prefs::kEnterpriseLogoUrlForBrowser,
                               std::string());
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
=======
#endif  // defined(OS_MAC)
>>>>>>> chromium
}

void RegisterBrowserUserPrefs(user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(prefs::kHomePageIsNewTabPage, true,
                                GetHomeButtonAndHomePageIsNewTabPageFlags());
  registry->RegisterBooleanPref(prefs::kShowHomeButton, false,
                                GetHomeButtonAndHomePageIsNewTabPageFlags());

  registry->RegisterInt64Pref(prefs::kDefaultBrowserLastDeclined, 0);
  bool reset_check_default = false;
#if defined(OS_WIN)
  reset_check_default = base::win::GetVersion() >= base::win::Version::WIN10;
#endif
  registry->RegisterBooleanPref(prefs::kResetCheckDefaultBrowser,
                                reset_check_default);
  registry->RegisterBooleanPref(prefs::kWebAppCreateOnDesktop, true);
  registry->RegisterBooleanPref(prefs::kWebAppCreateInAppsMenu, true);
  registry->RegisterBooleanPref(prefs::kWebAppCreateInQuickLaunchBar, true);
  registry->RegisterBooleanPref(
      prefs::kOfferTranslateEnabled, true,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
  registry->RegisterStringPref(prefs::kCloudPrintEmail, std::string());
  registry->RegisterBooleanPref(prefs::kCloudPrintProxyEnabled, true);
  registry->RegisterBooleanPref(prefs::kCloudPrintSubmitEnabled, true);
  registry->RegisterDictionaryPref(prefs::kBrowserWindowPlacement);
  registry->RegisterDictionaryPref(prefs::kBrowserWindowPlacementPopup);
  registry->RegisterDictionaryPref(prefs::kAppWindowPlacement);
<<<<<<< HEAD
#if !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_ANDROID)
=======
  registry->RegisterBooleanPref(
      prefs::kEnableDoNotTrack, false,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
#if !BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OS_ANDROID)
>>>>>>> chromium
  registry->RegisterBooleanPref(prefs::kPrintPreviewUseSystemDefaultPrinter,
                                false);
#endif
  registry->RegisterStringPref(prefs::kWebRTCIPHandlingPolicy,
                               blink::kWebRTCIPHandlingDefault);
  registry->RegisterListPref(prefs::kWebRTCIPHandlingUrl, base::Value::List());
  registry->RegisterStringPref(prefs::kWebRTCUDPPortRange, std::string());
  registry->RegisterBooleanPref(prefs::kWebRtcEventLogCollectionAllowed, false);
  registry->RegisterListPref(prefs::kWebRtcLocalIpsAllowedUrls);
  registry->RegisterBooleanPref(prefs::kWebRTCAllowLegacyTLSProtocols, false);

  // Dictionaries to keep track of default tasks in the file browser.
  registry->RegisterDictionaryPref(
      prefs::kDefaultTasksByMimeType,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
  registry->RegisterDictionaryPref(
      prefs::kDefaultTasksBySuffix,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);

  // We need to register the type of these preferences in order to query
  // them even though they're only typically controlled via policy.
  registry->RegisterBooleanPref(prefs::kClearPluginLSODataEnabled, true);
  registry->RegisterBooleanPref(prefs::kHideWebStoreIcon, false);
  registry->RegisterBooleanPref(prefs::kSharedClipboardEnabled, true);

#if BUILDFLAG(ENABLE_CLICK_TO_CALL)
  registry->RegisterBooleanPref(prefs::kClickToCallEnabled, true);
#endif  // BUILDFLAG(ENABLE_CLICK_TO_CALL)

#if defined(OS_MAC)
  // This really belongs in platform code, but there's no good place to
  // initialize it between the time when the AppController is created
  // (where there's no profile) and the time the controller gets another
  // crack at the start of the main event loop. By that time,
  // StartupBrowserCreator has already created the browser window, and it's too
  // late: we need the pref to be already initialized. Doing it here also saves
  // us from having to hard-code pref registration in the several unit tests
  // that use this preference.
  registry->RegisterBooleanPref(prefs::kShowUpdatePromotionInfoBar, true);
  registry->RegisterBooleanPref(
      prefs::kShowFullscreenToolbar, true,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
  registry->RegisterBooleanPref(
      prefs::kAllowJavascriptAppleEvents, false,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
#else
  registry->RegisterBooleanPref(prefs::kFullscreenAllowed, true);
#endif

  registry->RegisterBooleanPref(prefs::kEnterpriseHardwarePlatformAPIEnabled,
                                false);
  registry->RegisterBooleanPref(prefs::kUserFeedbackAllowed, true);
  registry->RegisterBooleanPref(prefs::kAllowSyncXHRInPageDismissal, false);
  registry->RegisterBooleanPref(
      prefs::kExternalProtocolDialogShowAlwaysOpenCheckbox, true);
  registry->RegisterBooleanPref(prefs::kScreenCaptureAllowed, true);

#if !defined(OS_ANDROID)
  registry->RegisterBooleanPref(prefs::kCaretBrowsingEnabled, false);
  registry->RegisterBooleanPref(prefs::kCloudPrintDeprecationWarningsSuppressed,
                                false);
  registry->RegisterBooleanPref(prefs::kShowCaretBrowsingDialog, true);
#endif

#if !BUILDFLAG(IS_CHROMEOS)
  registry->RegisterBooleanPref(prefs::kAccessibilityFocusHighlightEnabled,
                                false);
#endif

  registry->RegisterBooleanPref(
      prefs::kHttpsOnlyModeEnabled, false,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
<<<<<<< HEAD
  registry->RegisterBooleanPref(
      prefs::kHttpsFirstBalancedMode, false,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
  registry->RegisterBooleanPref(
      prefs::kHttpsFirstModeIncognito, true,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
  registry->RegisterListPref(prefs::kHttpAllowlist);
  registry->RegisterBooleanPref(prefs::kHttpsUpgradesEnabled, true);

  registry->RegisterDictionaryPref(prefs::kHttpsUpgradeFallbacks);
  registry->RegisterDictionaryPref(prefs::kHttpsUpgradeNavigations);
  registry->RegisterBooleanPref(prefs::kHttpsOnlyModeAutoEnabled, false);
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
  registry->RegisterStringPref(prefs::kEnterpriseLogoUrlForProfile,
                               std::string());
  registry->RegisterStringPref(prefs::kEnterpriseCustomLabelForProfile,
                               std::string());
  registry->RegisterIntegerPref(prefs::kEnterpriseProfileBadgeToolbarSettings,
                                0);
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
=======
>>>>>>> chromium
}
