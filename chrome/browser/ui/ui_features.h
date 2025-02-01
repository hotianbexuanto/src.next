// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file defines the browser-specific base::FeatureList features that are
// limited to top chrome UI.

#ifndef CHROME_BROWSER_UI_UI_FEATURES_H_
#define CHROME_BROWSER_UI_UI_FEATURES_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "build/branding_buildflags.h"
#include "build/build_config.h"
#include "chrome/common/buildflags.h"

namespace features {

// All features in alphabetical order. The features should be documented
// alongside the definition of their values in the .cc file.

extern const base::Feature kChromeLabs;

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
extern const base::Feature kChromeTipsInMainMenu;

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kCloseOmniboxPopupOnInactiveAreaClick);

BASE_DECLARE_FEATURE(kDefaultBrowserPromptRefresh);
BASE_DECLARE_FEATURE(kDefaultBrowserPromptRefreshTrial);

// String representation of the study group for running a synthetic trial.
extern const base::FeatureParam<std::string>
    kDefaultBrowserPromptRefreshStudyGroup;

// Whether to show the default browser info bar prompt.
extern const base::FeatureParam<bool> kShowDefaultBrowserInfoBar;

// Whether to show the default browser app menu item anytime the browser isn't
// default, even if the app menu chip prompt isn't enabled.
extern const base::FeatureParam<bool> kShowDefaultBrowserAppMenuItem;

// Base duration after which the user may be remprompted.
extern const base::FeatureParam<base::TimeDelta> kRepromptDuration;

// Maximum number of times a user will be prompted. When set to a negative
// value, the user will be prompted indefinitely.
extern const base::FeatureParam<int> kMaxPromptCount;

BASE_DECLARE_FEATURE(kExtensionsMenuInAppMenu);
bool IsExtensionMenuInRootAppMenu();

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
BASE_DECLARE_FEATURE(kFewerUpdateConfirmations);
#endif

#if !BUILDFLAG(IS_ANDROID)
BASE_DECLARE_FEATURE(kIOSPromoRefreshedPasswordBubble);
BASE_DECLARE_FEATURE(kIOSPromoAddressBubble);
BASE_DECLARE_FEATURE(kIOSPromoPaymentBubble);

// String params for the Desktop to iOS promos' QR code URLs.
extern const base::FeatureParam<std::string> kIOSPromoPasswordBubbleQRCodeURL;
extern const base::FeatureParam<std::string> kIOSPromoAddressBubbleQRCodeURL;
extern const base::FeatureParam<std::string> kIOSPromoPaymentBubbleQRCodeURL;
#endif  // !BUILDFLAG(IS_ANDROID)
=======
extern const base::Feature kChromeTipsInMainMenuNewBadge;
#endif

extern const base::Feature kChromeWhatsNewUI;

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
extern const base::Feature kChromeWhatsNewInMainMenuNewBadge;
#endif

extern const base::Feature kCommander;

#if BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS)
extern const base::Feature kEnterpriseCastingUI;
#endif
>>>>>>> chromium

extern const base::Feature kEvDetailsInPageInfo;

extern const base::Feature kExtensionsSidePanel;

// The extension id of the extension hosted in the left aligned side panel.
extern const base::FeatureParam<std::string> kExtensionsSidePanelId;

extern const base::Feature kForceSignInReauth;

extern const base::Feature kNewTabstripAnimation;

extern const base::Feature kProminentDarkModeActiveTabTitle;

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kScrimForBrowserWindowModal);

BASE_DECLARE_FEATURE(KScrimForTabModal);

BASE_DECLARE_FEATURE(kSideBySide);
=======
extern const base::Feature kReadLaterNewBadgePromo;
>>>>>>> chromium

extern const base::Feature kReadLaterAddFromDialog;

extern const base::Feature kScrollableTabStrip;
extern const char kMinimumTabWidthFeatureParameterName[];

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kSidePanelResizing);
BASE_DECLARE_FEATURE(kSidePanelSearchCompanion);

BASE_DECLARE_FEATURE(kTabGroupsCollapseFreezing);
=======
extern const base::Feature kScrollableTabStripButtons;

#if !defined(ANDROID)
extern const base::Feature kSettingsLandingPageRedesign;
#endif

// TODO(pbos): Once kReadLater is cleaned up on Desktop, move definition into
// ui_features.cc. This is currently temporarily in reading_list_switches.h.
extern const base::Feature kSidePanel;

extern const base::Feature kSyncConfirmationUpdatedText;

extern const base::Feature kSignInProfileCreation;
>>>>>>> chromium

extern const base::Feature kSignInProfileCreationEnterprise;

extern const base::Feature kTabGroupsAutoCreate;

extern const base::Feature kTabGroupsCollapseFreezing;

extern const base::Feature kTabGroupsFeedback;

extern const base::Feature kTabGroupsNewBadgePromo;

extern const base::Feature kTabGroupsSave;

extern const base::Feature kTabHoverCardImages;
extern const char kTabHoverCardImagesNotReadyDelayParameterName[];
extern const char kTabHoverCardImagesLoadingDelayParameterName[];
extern const char kTabHoverCardImagesLoadedDelayParameterName[];
extern const char kTabHoverCardImagesCrossfadePreviewAtParameterName[];

extern const base::Feature kTabOutlinesInLowContrastThemes;

extern const base::Feature kTabRestoreSubMenus;

extern const base::Feature kTabSearchChevronIcon;

extern const base::Feature kTabSearchFuzzySearch;

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kTabOrganizationAppMenuItem);

BASE_DECLARE_FEATURE(kTabOrganizationModelStrategy);
=======
extern const base::Feature kTabSearchFeedback;

extern const base::Feature kTabSearchRecentlyClosed;

// Setting this to true will ignore the distance parameter when finding matches.
// This means that it will not matter where in the string the pattern occurs.
extern const base::FeatureParam<bool> kTabSearchSearchIgnoreLocation;

// Determines how close the match must be to the beginning of the string. Eg a
// distance of 100 and threshold of 0.8 would require a perfect match to be
// within 80 characters of the beginning of the string.
extern const base::FeatureParam<int> kTabSearchSearchDistance;

// This determines how strong the match should be for the item to be included in
// the result set. Eg a threshold of 0.0 requires a perfect match, 1.0 would
// match anything. Permissible values are [0.0, 1.0].
extern const base::FeatureParam<double> kTabSearchSearchThreshold;
>>>>>>> chromium

// These are the hardcoded minimum and maximum search threshold values for
// |kTabSearchSearchThreshold|.
constexpr double kTabSearchSearchThresholdMin = 0.0;
constexpr double kTabSearchSearchThresholdMax = 1.0;

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kTabOrganizationUserInstruction);

// Duration of inactivity after which a tab is considered stale for declutter.
extern const base::FeatureParam<base::TimeDelta>
    kTabstripDeclutterStaleThresholdDuration;
// Interval between a recomputation of stale tabs for declutter.
extern const base::FeatureParam<base::TimeDelta>
    kTabstripDeclutterTimerInterval;
// Default interval after showing a nudge to prevent another nudge from being
// shown for declutter.
extern const base::FeatureParam<base::TimeDelta>
    kTabstripDeclutterNudgeTimerInterval;
=======
// Controls the weight associated with a tab's title for filtering and ordering
// list items.
extern const base::FeatureParam<double> kTabSearchTitleWeight;
>>>>>>> chromium

// Controls the weight associated with a tab's hostname when filering and
// odering list items.
extern const base::FeatureParam<double> kTabSearchHostnameWeight;

// Controls the weight associated with a tab's group title filering and
// odering list items
extern const base::FeatureParam<double> kTabSearchGroupTitleWeight;

<<<<<<< HEAD
// The minimum score threshold for proactive nudge triggering to occur.
extern const base::FeatureParam<double> kTabOrganizationTriggerThreshold;

// The maximum sensitivity score for a tab to contribute to trigger scoring.
extern const base::FeatureParam<double>
    kTabOrganizationTriggerSensitivityThreshold;

// Enable 'demo mode' for Tab Organization triggering, which triggers much more
// predictably and frequently.
extern const base::FeatureParam<bool> KTabOrganizationTriggerDemoMode;

BASE_DECLARE_FEATURE(kTearOffWebAppTabOpensWebAppWindow);
=======
// Whether to move the active tab to the bottom of the list.
extern const base::FeatureParam<bool> kTabSearchMoveActiveTabToBottom;

// Default number of recently closed entries to display by default when no
// search text is provided.
extern const base::FeatureParam<int>
    kTabSearchRecentlyClosedDefaultItemDisplayCount;

// A threshold of recently closed tabs after which to stop adding recently
// closed item data to the profile data payload should the minimum display
// count have been met.
extern const base::FeatureParam<int> kTabSearchRecentlyClosedTabCountThreshold;

// Determines how screenshots of the toolbar uses Software or Hardware drawing.
// Works on Android 10+.
extern const base::Feature kToolbarUseHardwareBitmapDraw;
>>>>>>> chromium

// Whether to label the update menu item as "Relaunch to update Chrome", rather
// than "Update Google Chrome".
extern const base::Feature kUseRelaunchToUpdateString;

extern const base::Feature kWebUIBubblePerProfilePersistence;

<<<<<<< HEAD
BASE_DECLARE_FEATURE(kPinnedCastButton);
BASE_DECLARE_FEATURE(kPinnableDownloadsButton);
=======
#if !defined(ANDROID)
extern const base::Feature kWebUIBrandingUpdate;
#endif
>>>>>>> chromium

extern const base::Feature kWebUIDownloadShelf;

extern const base::Feature kWebUITabStrip;

extern const base::Feature kWebUITabStripNewTabButtonInTabStrip;

extern const base::Feature kWebUIFeedback;

// Cocoa to views migration.
#if defined(OS_MAC)
extern const base::Feature kLocationPermissionsExperiment;

extern const base::Feature kViewsFirstRunDialog;
extern const base::Feature kViewsTaskManager;
extern const base::Feature kViewsJSAppModalDialog;

int GetLocationPermissionsExperimentBubblePromptLimit();
int GetLocationPermissionsExperimentLabelPromptLimit();
#endif

<<<<<<< HEAD
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
BASE_DECLARE_FEATURE(kUsePortalAccentColor);
#endif

// Controls whether the site-specific data dialog shows a related installed
// applications section.
BASE_DECLARE_FEATURE(kPageSpecificDataDialogRelatedInstalledAppsSection);

// Feature for the promotion banner on the top of chrome://management page
BASE_DECLARE_FEATURE(kEnableManagementPromotionBanner);

// Enable display for the Chrome Enterprise Core promotion banner on
// the chrome://policy page.
BASE_DECLARE_FEATURE(kEnablePolicyPromotionBanner);

// Controls whether a performance improvement in browser feature support
// checking is enabled.
BASE_DECLARE_FEATURE(kInlineFullscreenPerfExperiment);

// Controls whether the new page actions framework should be displaying page
// actions.
BASE_DECLARE_FEATURE(kPageActionsMigration);

// Controls whether browser tab loading animations are driven by the compositor
// vs. a repeating timer.
BASE_DECLARE_FEATURE(kCompositorLoadingAnimations);

// If enabled, when no given_name is provided, the FedCM Continue button will
// say "Continue" instead of "Continue as Firstname Lastname".
BASE_DECLARE_FEATURE(kFedCmContinueWithoutName);

=======
#if defined(OS_WIN)
extern const base::Feature kWin10TabSearchCaptionButton;
#endif

>>>>>>> chromium
}  // namespace features

#endif  // CHROME_BROWSER_UI_UI_FEATURES_H_
