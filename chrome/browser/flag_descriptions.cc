// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/flag_descriptions.h"

<<<<<<< HEAD
#include "build/build_config.h"
#include "flag_descriptions.h"
#include "media/gpu/buildflags.h"
#include "pdf/buildflags.h"
#include "skia/buildflags.h"
=======
#include "build/chromeos_buildflags.h"
>>>>>>> chromium

// Keep in identical order as the header file, see the comment at the top
// for formatting rules.

namespace flag_descriptions {

const char kAccelerated2dCanvasName[] = "Accelerated 2D canvas";
const char kAccelerated2dCanvasDescription[] =
    "Enables the use of the GPU to perform 2d canvas rendering instead of "
    "using software rendering.";

<<<<<<< HEAD
const char kAiSettingsPageRefreshName[] = "AI settings page refresh";
const char kAiSettingsPageRefreshDescription[] =
    "Enables a revamp of the existing AI settings page.";

const char kAiSettingsPageEnterpriseDisabledName[] =
    "AI settings page enterprise disabled UI";
const char kAiSettingsPageEnterpriseDisabledDescription[] =
    "Enables settings UI for AI features that are disabled by enterprise "
    "policy.";

const char kCanvasHibernationName[] = "Hibernation for 2D canvas";
const char kCanvasHibernationDescription[] =
    "Enables canvas hibernation for 2D canvas.";

const char kCanvasOopRasterizationName[] =
    "Out-of-process 2D canvas rasterization.";
const char kCanvasOopRasterizationDescription[] =
    "The rasterization of 2d canvas contents is performed in the GPU process. "
    "Requires that out-of-process rasterization be enabled.";

const char kCapturedSurfaceControlName[] = "Captured Surface Control";
const char kCapturedSurfaceControlDescription[] =
    "Enables an API that allows an application to control scroll and zoom on "
    "the tab which it is capturing.";

=======
>>>>>>> chromium
const char kAcceleratedVideoDecodeName[] = "Hardware-accelerated video decode";
const char kAcceleratedVideoDecodeDescription[] =
    "Hardware-accelerated video decode where available.";

const char kAcceleratedVideoEncodeName[] = "Hardware-accelerated video encode";
const char kAcceleratedVideoEncodeDescription[] =
    "Hardware-accelerated video encode where available.";

const char kEnableMediaInternalsName[] = "Media-internals page";
const char kEnableMediaInternalsDescription[] =
    "Enables the chrome://media-internals debug page.";

#if BUILDFLAG(ENABLE_PLUGINS)
const char kAccessiblePDFFormName[] = "Accessible PDF Forms";
const char kAccessiblePDFFormDescription[] =
    "Enables accessibility support for PDF forms.";
#endif  // BUILDFLAG(ENABLE_PLUGINS)

const char kAccountIdMigrationName[] = "Account ID migration";
const char kAccountIdMigrationDescription[] =
    "Migrate to use Gaia ID instead of the email as the account identifer for "
    "the Identity Manager.";

const char kLauncherAppSortName[] = "Productivity experiment: Reorder Apps";
const char kLauncherAppSortDescription[] =
    "To evaluate an enhanced Launcher experience that enables users to reorder "
    "their apps in order to find them more easily.";

const char kAlignFontDisplayAutoTimeoutWithLCPGoalName[] =
    "Align 'font-display: auto' timeout with LCP goal";
const char kAlignFontDisplayAutoTimeoutWithLCPGoalDescription[] =
    "Make pending 'display: auto' web fonts enter the swap or failure period "
    "immediately before reaching the LCP time limit (~2500ms), so that web "
    "fonts do not become a source of bad LCP (Largest Contentful Paint).";

const char kAllowInsecureLocalhostName[] =
    "Allow invalid certificates for resources loaded from localhost.";
const char kAllowInsecureLocalhostDescription[] =
    "Allows requests to localhost over HTTPS even when an invalid certificate "
    "is presented.";

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_EXTENSIONS)
const char kAllowLegacyMV2ExtensionsName[] =
    "Allow legacy extension manifest versions";
const char kAllowLegacyMV2ExtensionsDescription[] =
    "Allows extensions with legacy (unsupported) manifest versions to be loaded"
    " as unpacked extensions. This should only be used for maintaining legacy "
    "extensions and will be removed in the future.";
#endif

const char kAndroidAppIntegrationName[] = "Integrate with Android App Search";
const char kAndroidAppIntegrationDescription[] =
    "If enabled, allows Chrome to integrate with the Android App Search.";

const char kAndroidAppIntegrationModuleName[] =
    "Integrate with Android App Search and shows a notice card";
const char kAndroidAppIntegrationModuleDescription[] =
    "If enabled, allows Chrome to show a notice card on the magic stack for "
    "Android App Search integration";

const char kAndroidAppIntegrationV2Name[] =
    "Integrate with Android App Search V2";
const char kAndroidAppIntegrationV2Description[] =
    "If enabled, allows Chrome to integrate with the Android App Search "
    "directly without using internal library.";

#if BUILDFLAG(IS_ANDROID)
const char kNewTabPageCustomizationName[] = "Customize the new tab page";
const char kNewTabPageCustomizationDescription[] =
    "If enabled, allows users to customize the new tab page";
#endif  // BUILDFLAG(IS_ANDROID)

const char kAndroidAppIntegrationWithFaviconName[] =
    "Integrate with Android App Search with favicons";
const char kAndroidAppIntegrationWithFaviconDescription[] =
    "If enabled, allows Chrome to integrate with the Android App Search with "
    "favicons.";

const char kAndroidBcivBottomControlsName[] =
    "Browser controls in viz for bottom controls";
const char kAndroidBcivBottomControlsDescription[] =
    "Let viz move bottom browser controls when scrolling. If this flag is "
    "enabled, AndroidBrowserControlsInViz must also be enabled.";

#if BUILDFLAG(IS_ANDROID)
const char kAndroidBookmarkBarName[] = "Bookmark Bar";
const char kAndroidBookmarkBarDescription[] =
    "Enables the bookmark bar which provides users with bookmark access from "
    "top chrome. Note that device form factor restrictions also apply.";
#endif  // BUILDFLAG(IS_ANDROID)

const char kAndroidBottomToolbarName[] = "Bottom Toolbar";
const char kAndroidBottomToolbarDescription[] =
    "If enabled, displays the toolbar at the bottom.";

const char kAndroidExtendedKeyboardShortcutsName[] =
    "Android Extended Keyboard Shortcuts";
const char kAndroidExtendedKeyboardShortcutsDescription[] =
    "If enabled, allows for extended keyboard shortcuts (i.e. Alt + Backspace "
    "to delete line).";

const char kAndroidBrowserControlsInVizName[] =
    "Android Browser Controls in Viz";
const char kAndroidBrowserControlsInVizDescription[] =
    "Let viz move browser controls when scrolling. For now, this applies only "
    "to top controls.";
=======
const char kAllowSyncXHRInPageDismissalName[] =
    "Allows synchronous XHR requests in page dismissal";
const char kAllowSyncXHRInPageDismissalDescription[] =
    "Allows synchronous XHR requests during page dismissal when the page is "
    "being navigated away or closed by the user.";

const char kWindowsFollowCursorName[] =
    "Windows open on the display with the cursor";
const char kWindowsFollowCursorDescription[] =
    "When there are multiple displays, windows open on the display where "
    "cursor is located.";
>>>>>>> chromium

#if BUILDFLAG(IS_CHROMEOS)
const char kVpnAppsOnFlexName[] = "Enable VPN Apps on Flex";
const char kVpnAppsOnFlexDescription[] =
    "Enables support for VPN Apps on Flex devices.";

<<<<<<< HEAD
const char kAnnotatorModeName[] = "Enable annotator tool";
const char kAnnotatorModeDescription[] =
    "Enables the tool for annotating across the OS.";
#endif  // BUILDFLAG(IS_CHROMEOS)

=======
>>>>>>> chromium
const char kAriaElementReflectionName[] = "Enable ARIA element reflection";
const char kAriaElementReflectionDescription[] =
    "Enable setting ARIA relationship attributes that reference other elements "
    "directly without an IDREF";

<<<<<<< HEAD
const char kAutomaticUsbDetachName[] =
    "Automatically detach USB kernel drivers";
const char kAutomaticUsbDetachDescription[] =
    "Automatically detach kernel drivers when a USB interface is busy.";

const char kAutomotiveFullscreenToolbarImprovementsName[] =
    "Enable automotive fullscreen toolbar improvements.";
const char kAutomotiveFullscreenToolbarImprovementsDescription[] =
    "In automotive, hides the toolbar when entering fullscreen mode. Swipe on"
    "edge to reshow the toolbar.";
=======
const char kCOLRV1FontsName[] = "COLR v1 Fonts";
const char kCOLRV1FontsDescription[] =
    "Display COLR v1 color gradient vector fonts.";
>>>>>>> chromium

extern const char kCSSContainerQueriesName[] = "Enable CSS Container Queries";
extern const char kCSSContainerQueriesDescription[] =
    "Enables support for @container, inline-size and block-size values for the "
    "contain property, and the LayoutNG Grid implementation.";

const char kConditionalTabStripAndroidName[] = "Conditional Tab Strip";
const char kConditionalTabStripAndroidDescription[] =
    "Allows users to access conditional tab strip.";

const char kContentLanguagesInLanguagePickerName[] =
    "Content languages in language picker";
const char kContentLanguagesInLanguagePickerDescription[] =
    "Enables bringing user's content languages that are translatable to the "
    "top of the list with all languages shown in the translate menu";

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
const char kBirchWeatherName[] = "Birch weather";
const char kBirchWeatherDescription[] =
    "Shows the weather suggestion chip in the birch suggestions UI. Note that "
    "the chip only shows certain times of day, so it may not immediately "
    "appear after enabling this feature.";
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
const char kConversionMeasurementApiName[] = "Conversion Measurement API";
const char kConversionMeasurementApiDescription[] =
    "Enables usage of the Conversion Measurement API. Requires "
    "#enable-experimental-web-platform-features to be enabled.";
>>>>>>> chromium

const char kConversionMeasurementDebugModeName[] =
    "Conversion Measurement Debug Mode";
const char kConversionMeasurementDebugModeDescription[] =
    "Enables debug mode for the Conversion Measurement API. This removes all "
    "reporting delays and noise. Only works if the Conversion Measurement API "
    "is already enabled.";

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
const char kBookmarksTreeViewName[] = "Top Chrome Bookmarks Tree View";
const char kBookmarksTreeViewDescription[] =
    "Show the bookmarks side panel in a tree view while in compact mode.";
#endif

const char kCertVerificationNetworkTimeName[] =
    "Network Time for Certificate Verification";
const char kCertVerificationNetworkTimeDescription[] =
    "Use time fetched from the network for certificate verification decisions. "
    "If certificate verification fails with the network time, it will fall back"
    " to system time.";

#if BUILDFLAG(IS_ANDROID)
const char kChangeUnfocusedPriorityName[] = "Change Unfocused Priority";
const char kChangeUnfocusedPriorityDescription[] =
    "Lower process priority for processes with only unfocused windows, "
    "allowing them to be discarded sooner.";
#endif

const char kClassifyUrlOnProcessResponseEventName[] =
    "Classify Url on process response event";
const char kClassifyUrlOnProcessResponseEventDescription[] =
    "Alters the behavior of a supervised user navigation throttle so that the"
    "decision whether to proceed or cancel is made when the response is ready"
    "to be rendered, rather than before the request (or any redirect)"
    "is issued.";

const char kClearUndecryptablePasswordsName[] =
    "Removes passwords that can no longer be decrypted";
const char kClearUndecryptablePasswordsDescription[] =
    "If enabled local passwords that current encryption key cannot decrypt, "
    "will be deleted to restore the full functionality of password manager.";

const char kClickToCallName[] = "Click-To-Call";
const char kClickToCallDescription[] = "Enable the click-to-call feature.";

const char kClipboardMaximumAgeName[] = "Clipboard maximum age";
const char kClipboardMaximumAgeDescription[] =
    "Limit the maximum age for recent clipboard content";

const char kComputePressureRateObfuscationMitigationName[] =
    "Enable mitigation algorithm for rate obfuscation in compute pressure";
const char kComputePressureRateObfuscationMitigationDescription[] =
    "Rate Obfuscation Mitigation is used to avoid fingerprinting attacks. Its "
    "usage introduces some timing penalties to the compute pressure results."
    "This mitigation might introduce slight precision errors."
    "When disabled this helps to test how predictable and accurate compute "
    "pressure is, but the Compute Pressure API can be susceptible to "
    "fingerprinting attacks.";

const char kComputePressureBreakCalibrationMitigationName[] =
    "Enable mitigation algorithm to break calibration attempt in compute "
    "pressure";
const char kComputePressureBreakCalibrationMitigationDescription[] =
    "In a calibration process an attacker tries to manipulate the CPU so that "
    "Compute Pressure API would report a transition into a certain pressure "
    "state with the highest probability in response to the pressure exerted "
    "by the fabricated workload."
    "Break Calibration Mitigation is used to avoid calibration attempts by "
    "introducing some randomness in the result of the platform collector."
    "This mitigation might introduce slight precision errors."
    "When disabled this helps to test how predictable and accurate compute "
    "pressure is, but the Compute Pressure API can be susceptible to "
    "calibration attempts.";

const char kContainerTypeNoLayoutContainmentName[] =
    "Enables the container-type property to have no layout containment";
const char kContainerTypeNoLayoutContainmentDescription[] =
    "The container-type property was recently changed to not add layout "
    "containment, this allows users to temporarily disable this change.";

const char kContentSettingsPartitioningName[] = "Content Settings Partitioning";
const char kContentSettingsPartitioningDescription[] =
    "Partition content settings by StoragePartitions";

const char kCopyImageFilenameToClipboardName[] =
    "Copy image filename to clipboard.";
const char kCopyImageFilenameToClipboardDescription[] =
    "Whether to write filename to the clipboard when copying image downloads.";

#if BUILDFLAG(IS_CHROMEOS)
const char kCoralFeatureKeyName[] = "Secret key for Coral feature.";
const char kCoralFeatureKeyDescription[] =
    "Secret key for Coral feature. Incorrect values will cause chrome crashes.";

const char kCrosSwitcherName[] = "ChromeOS Switcher feature.";
const char kCrosSwitcherDescription[] =
    "Enable/Disable ChromeOS Switcher feature.";
#endif  // IS_CHROMEOS

const char kCssGamutMappingName[] = "CSS Gamut Mapping";
const char kCssGamutMappingDescription[] =
    "Enable experimental CSS gamut mapping implementation.";

const char kCssTextBoxTrimName[] = "CSS text-box-trim";
const char kCssTextBoxTrimDescription[] =
    "Enable experimental CSS text-box-trim property.";

const char kCustomizeChromeSidePanelExtensionsCardName[] =
    "Customize Chrome Side Panel Extension Card";
const char kCustomizeChromeSidePanelExtensionsCardDescription[] =
    "If enabled, shows an extension card within the Customize Chrome Side "
    "Panel for access to the Chrome Web Store extensions.";

const char kCustomizeChromeWallpaperSearchName[] =
    "Customize Chrome Wallpaper Search";
const char kCustomizeChromeWallpaperSearchDescription[] =
    "Enables wallpaper search in Customize Chrome Side Panel.";

const char kCustomizeChromeWallpaperSearchButtonName[] =
    "Customize Chrome Wallpaper Search Button";
const char kCustomizeChromeWallpaperSearchButtonDescription[] =
    "Enables entry point on Customize Chrome Side Panel's Appearance page for "
    "Wallpaper Search.";

const char kCustomizeChromeWallpaperSearchInspirationCardName[] =
    "Customize Chrome Wallpaper Search Inspiration Card";
const char kCustomizeChromeWallpaperSearchInspirationCardDescription[] =
    "Shows inspiration card in Customize Chrome Side Panel Wallpaper Search. "
    "Requires #customize-chrome-wallpaper-search to be enabled too.";

const char kDataSharingName[] = "Data Sharing";
const char kDataSharingDescription[] =
    "Enabled all Data Sharing related UI and features.";

const char kDataSharingJoinOnlyName[] = "Data Sharing Join Only";
const char kDataSharingJoinOnlyDescription[] =
    "Enabled Data Sharing Joining flow related UI and features.";

const char kHistorySyncAlternativeIllustrationName[] =
    "History Sync Alternative Illustration";
const char kHistorySyncAlternativeIllustrationDescription[] =
    "Enables history sync alternative illustration.";

const char kDeprecateUnloadName[] = "Deprecate the unload event";
const char kDeprecateUnloadDescription[] =
    "Controls the default for Permissions-Policy unload. If enabled, unload "
    "handlers are deprecated and will not receive the unload event unless a "
    "Permissions-Policy to enable them has been explicitly set. If  disabled, "
    "unload handlers will continue to receive the unload event unless "
    "explicitly disabled by Permissions-Policy, even during the gradual "
    "rollout of their deprecation.";

const char kDeferRendererTasksAfterInputName[] =
    "Defer Renderer Tasks After Input";
const char kDeferRendererTasksAfterInputDescription[] =
    "If enabled, tasks in the renderer will be deferred after discrete input "
    "events, e.g. keypress, until after the subsequent frame. The associated "
    "policy controls which tasks types can be deferred.";

const char kDevToolsPrivacyUIName[] = "DevTools Privacy UI";
const char kDevToolsPrivacyUIDescription[] =
    "Enables the Privacy UI in the current 'Security' panel in DevTools.";
=======
const char kDeprecateMenagerieAPIName[] = "Deprecate Menagerie API on Android";
const char kDeprecateMenagerieAPIDescription[] =
    "If enabled, the legacy Menagerie API for profile data will be replaced by "
    "the new profile data source";
>>>>>>> chromium

const char kForceStartupSigninPromoName[] = "Force Start-up Signin Promo";
const char kForceStartupSigninPromoDescription[] =
    "If enabled, the full screen signin promo will be forced to show up at "
    "Chrome start-up.";

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
const char kForestFeatureName[] = "Forest";
const char kForestFeatureDescription[] = "Enable Forest experiment.";
#endif
=======
const char kDebugHistoryInterventionNoUserActivationName[] =
    "Debug flag for history intervention on no user activation";
const char kDebugHistoryInterventionNoUserActivationDescription[] =
    "This flag when enabled, will be used to debug an issue where a page that "
    "did not get user activation "
    "is able to work around the history intervention which is not the expected "
    "behavior";
>>>>>>> chromium

const char kDetectedSourceLanguageOptionName[] =
    "Use Detected Language string on Desktop and Android";
const char kDetectedSourceLanguageOptionDescription[] =
    "Renames the 'Unknown' source language option to 'Detected Language' and "
    "enables translation of unknown source language pages on Android.";

const char kDetectFormSubmissionOnFormClearName[] =
    "Detect form submission when the form is cleared.";
const char kDetectFormSubmissionOnFormClearDescription[] =
    "Detect form submissions for change password forms that are cleared and "
    "not removed from the page.";

<<<<<<< HEAD
const char kTangibleSyncName[] = "Tangible Sync";
const char kTangibleSyncDescription[] =
    "Enables the tangible sync when a user starts the sync consent flow";
=======
const char kEditPasswordsInSettingsName[] = "Edit passwords in settings";
const char kEditPasswordsInSettingsDescription[] =
    "Enables password editing in settings.";

const char kEnableBluetoothSerialPortProfileInSerialApiName[] =
    "Enable Bluetooth Serial Port Profile in Serial API";
const char kEnableBluetoothSerialPortProfileInSerialApiDescription[] =
    "When enabled, Bluetooth Serial Port Profile devices will be enumerated "
    "for use with the Serial API.";
>>>>>>> chromium

const char kEnableFtpName[] = "Enable support for FTP URLs";
const char kEnableFtpDescription[] =
    "When enabled, the browser will handle navigations to ftp:// URLs by "
    "either showing a directory listing or downloading the resource over FTP. "
    "When disabled, the browser has no special handling for ftp:// URLs and "
    "by default defer handling of the URL to the underlying platform.";

const char kEnablePolicyBlocklistThrottleRequiresPoliciesLoadedName[] =
    "Url blocklist throttle wait for policies to be loaded";
const char kEnablePolicyBlocklistThrottleRequiresPoliciesLoadedDescription[] =
    "Enables behaviour for Url blocklist throttle to wait for all policies to "
    "load";

const char kEnableSignedExchangeSubresourcePrefetchName[] =
    "Enable Signed Exchange subresource prefetching";
const char kEnableSignedExchangeSubresourcePrefetchDescription[] =
    "When enabled, the distributors of signed exchanges can let Chrome know "
    "alternative signed exchange subresources by setting \"alternate\" link "
    "header. Chrome will prefetch the alternate signed exchange subresources "
    "and will load them if the publisher of the main signed exchange has set "
    "\"allowed-alt-sxg\" link header in the signed inner response of the "
    "main signed exchange.";

const char kEnableSignedExchangePrefetchCacheForNavigationsName[] =
    "Enable Signed Exchange prefetch cache for navigations";
const char kEnableSignedExchangePrefetchCacheForNavigationsDescription[] =
    "When enabled, the prefetched signed exchanges is stored to a prefetch "
    "cache attached to the frame. The body of the inner response is stored as "
    "a blob and the verification process of the signed exchange is skipped for "
    "the succeeding navigation.";

const char kUpdatedCellularActivationUiName[] =
    "Updated Cellular Activation UI";
const char kUpdatedCellularActivationUiDescription[] =
    "Enables the updated cellular activation UI.";

<<<<<<< HEAD
const char kPrerender2Name[] = "Prerendering";
const char kPrerender2Description[] =
    "If enabled, browser features and the speculation rules API can trigger "
    "prerendering. If disabled, all prerendering APIs still exist, but a "
    "prerender will never successfully take place.";

const char kEnableDrDcName[] =
    "Enables Display Compositor to use a new gpu thread.";
const char kEnableDrDcDescription[] =
    "When enabled, chrome uses 2 gpu threads instead of 1. "
    " Display compositor uses new dr-dc gpu thread and all other clients "
    "(raster, webgl, video) "
    " continues using the gpu main thread.";

const char kEnableSnackbarInSettingsName[] = "Snackbar for settings ";
const char kEnableSnackbarInSettingsDescription[] =
    "Enables a snack bar that is shown to users after they save the "
    "setting that controls whether a user gets signed in to Chrome when "
    "signing in to Google Services.";

const char kTextBasedAudioDescriptionName[] = "Enable audio descriptions.";
const char kTextBasedAudioDescriptionDescription[] =
    "When enabled, HTML5 video elements with a 'descriptions' WebVTT track "
    "will speak the audio descriptions aloud as the video plays.";

const char kUseAndroidStagingSmdsName[] = "Use Android staging SM-DS";
const char kUseAndroidStagingSmdsDescription[] =
    "Use the Android staging address when fetching pending eSIM profiles.";

const char kUseFrameIntervalDeciderName[] =
    "Use rewritten display FrameIntervalDecider";
const char kUseFrameIntervalDeciderDescription[] =
    "Rewrite is meant to preserve existing behavior and enable new features.";

const char kUseSharedImagesForPepperVideoName[] =
    "Use SharedImages for PPAPI Video";
const char kUseSharedImagesForPepperVideoDescription[] =
    "Enables use of SharedImages for textures that are used by PPAPI "
    "VideoDecoder";
=======
const char kUseLookalikesForNavigationSuggestionsName[] =
    "Use lookalike URL suggestions for navigation suggestions";
const char kUseLookalikesForNavigationSuggestionsDescription[] =
    "Use lookalike URL suggestions to suggest navigations to users who "
    "face domain not found error.";
>>>>>>> chromium

const char kUseStorkSmdsServerAddressName[] = "Use Stork SM-DS address";
const char kUseStorkSmdsServerAddressDescription[] =
    "Use the Stork SM-DS address to fetch pending eSIM profiles managed by the "
    "Stork prod server. Note that Stork profiles can be created with an EID at "
    "go/stork-profile, and managed at go/stork-batch > View Profiles. Also "
<<<<<<< HEAD
    "note that an test eUICC card is required to use this feature, usually "
    "that requires the kCellularUseSecond flag to be enabled. Go to "
=======
    "note that an external EUICC card is required to use this feature, and "
    "that the kCellularUseExternal flag must be enabled. Go to "
>>>>>>> chromium
    "go/cros-connectivity > Dev Tips for more instructions.";

const char kUseWallpaperStagingUrlName[] = "Use Wallpaper staging URL";
const char kUseWallpaperStagingUrlDescription[] =
    "Use the staging server as part of the Wallpaper App to verify "
    "additions/removals of wallpapers.";

const char kSemanticColorsDebugOverrideName[] =
    "Use semantic color debug override";
const char kSemanticColorsDebugOverrideDescription[] =
    "Use debug override colors to find system components that are not using "
    "semantic colors.";

const char kUseMessagesStagingUrlName[] = "Use Messages staging URL";
const char kUseMessagesStagingUrlDescription[] =
    "Use the staging server as part of the \"Messages\" feature under "
    "\"Connected Devices\" settings.";

const char kUseCustomMessagesDomainName[] = "Use custom Messages domain";
const char kUseCustomMessagesDomainDescription[] =
    "Use a custom URL as part of the \"Messages\" feature under "
    "\"Connected Devices\" settings.";

const char kAndroidPictureInPictureAPIName[] =
    "Picture-in-Picture Web API for Android";
const char kAndroidPictureInPictureAPIDescription[] =
    "Enable Picture-in-Picture Web API for Android";

<<<<<<< HEAD
const char kUseDnsHttpsSvcbAlpnName[] = "Use DNS https alpn";
const char kUseDnsHttpsSvcbAlpnDescription[] =
    "When enabled, Chrome may try QUIC on the first connection using the ALPN"
    " information in the DNS HTTPS record.";
=======
const char kAppCacheName[] = "AppCache web API and browser backend";
const char kAppCacheDescription[] =
    "When disabled, turns off all AppCache code so that developers "
    "can test that their code works properly in the future when AppCache "
    "has been removed.  If disabled, this will also delete any AppCache data "
    "from profile directories.";

const char kDnsHttpssvcName[] = "Support for HTTPSSVC records in DNS.";
const char kDnsHttpssvcDescription[] =
    "When enabled, Chrome may query a configured DoH server for HTTPSSVC "
    "records. If any HTTPSSVC records are returned, Chrome may upgrade the URL "
    "to HTTPS. If the records indicate support for QUIC, Chrome may attempt "
    "QUIC on the first connection.";
>>>>>>> chromium

const char kEnableFirstPartySetsName[] = "Enable First-Party Sets";
const char kEnableFirstPartySetsDescription[] =
    "When enabled, Chrome will apply First-Party Sets to features such as the "
    "SameParty cookie attribute.";

const char kDnsOverHttpsName[] = "Secure DNS lookups";
const char kDnsOverHttpsDescription[] =
    "Enables DNS over HTTPS. When this feature is enabled, your browser may "
    "try to use a secure HTTPS connection to look up the addresses of websites "
    "and other web resources.";

extern const char kAssistantExplicitVoiceConsentName[] =
    "AssistantExplicitVoiceConsent";
extern const char kAssistantExplicitVoiceConsentDescription[] =
    "When enabled, backing off from the consent screen by tapping outside of "
    "it or pressing the back button are not treated as rejection";

<<<<<<< HEAD
const char kAutofillEnableAllowlistForBmoCardCategoryBenefitsName[] =
    "Enable allowlist for showing category benefits for BMO cards";
const char kAutofillEnableAllowlistForBmoCardCategoryBenefitsDescription[] =
    "When enabled, card category benefits offered by BMO will be shown in "
    "Autofill suggestions on the allowlisted merchant websites.";

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
const char kAutofillEnableAmountExtractionDesktopName[] =
    "Enable checkout amount extraction on Chrome desktop";
const char kAutofillEnableAmountExtractionDesktopDescription[] =
    "When enabled, Chrome will extract the checkout amount from the checkout "
    "page of the allowlisted merchant websites.";
#endif
=======
extern const char kAssistantVoiceConstentTapsCounterName[] =
    "AssistantVoiceConsentTapsCounter";
extern const char kAssistantVoiceConstentTapsCounterDescription[] =
    "When enabled, a specified (by a feature param) number of taps outside of "
    "the consent screen or back button presses will be ignored, but the next "
    "one will be treated as rejection";
>>>>>>> chromium

const char kAutofillAlwaysReturnCloudTokenizedCardName[] =
    "Return cloud token details for server credit cards when possible";
const char kAutofillAlwaysReturnCloudTokenizedCardDescription[] =
    "When enabled and where available, forms filled using Google Payments "
    "server cards are populated with cloud token details, including CPAN "
    "(cloud tokenized version of the Primary Account Number) and dCVV (dynamic "
    "CVV).";

const char kAutofillAssistantChromeEntryName[] = "AutofillAssistantChromeEntry";
const char kAutofillAssistantChromeEntryDescription[] =
    "Initiate autofill assistant from within Chrome.";

const char kAutofillAutoTriggerManualFallbackForCardsName[] =
    "Auto trigger manual fallback for credit card form-filling failure cases";
const char kAutofillAutoTriggerManualFallbackForCardsDescription[] =
    "When enabled, manual fallback will be auto-triggered on form interaction "
    "in the case where autofill failed to fill a credit card form accurately.";

const char kAutofillEnableGoogleIssuedCardName[] =
    "Enable Autofill Google-issued card";
const char kAutofillEnableGoogleIssuedCardDescription[] =
    "When enabled, Google-issued cards will be available in the autofill "
    "suggestions.";

const char kAutofillEnableMerchantBoundVirtualCardsName[] =
    "Offer merchant bound virtual cards in Autofill";
const char kAutofillEnableMerchantBoundVirtualCardsDescription[] =
    "When enabled, Autofill will offer to use merchant bound virtual cards in "
    "payment forms.";

const char kAutofillEnableOfferNotificationName[] =
    "Enable Autofill offers and rewards notification";
const char kAutofillEnableOfferNotificationDescription[] =
    "When enabled, a notification will be displayed on page navigation if the "
    "domain has an eligible credit card linked offer or reward.";

<<<<<<< HEAD
const char kAutofillEnableFpanRiskBasedAuthenticationName[] =
    "Enable risk-based authentication for FPAN retrieval";
const char kAutofillEnableFpanRiskBasedAuthenticationDescription[] =
    "When enabled, server card retrieval will begin with a risk-based check "
    "instead of jumping straight to CVC or biometric auth.";

const char kAutofillEnableCardBenefitsForAmericanExpressName[] =
    "Enable showing card benefits for American Express cards";
const char kAutofillEnableCardBenefitsForAmericanExpressDescription[] =
    "When enabled, card benefits offered by American Express will be shown in "
    "Autofill suggestions.";

const char kAutofillEnableCardBenefitsForBmoName[] =
    "Enable showing card benefits for BMO cards";
const char kAutofillEnableCardBenefitsForBmoDescription[] =
    "When enabled, card benefits offered by BMO will be shown in Autofill "
    "suggestions.";

const char kAutofillEnableCardBenefitsIphName[] =
    "Enable showing in-process help UI for card benefits";
const char kAutofillEnableCardBenefitsIphDescription[] =
    "When enabled, in-process help UI will be shown for Autofill card "
    "suggestions with benefits.";

const char kAutofillEnableCardBenefitsSyncName[] =
    "Enable syncing card benefits";
const char kAutofillEnableCardBenefitsSyncDescription[] =
    "When enabled, card benefits offered by issuers will be synced from the "
    "Payments server.";

const char kAutofillEnableCardInfoRuntimeRetrievalName[] =
    "Enable retrieval of card info(with CVC) from issuer for enrolled cards";
const char kAutofillEnableCardInfoRuntimeRetrievalDescription[] =
    "When enabled, runtime retrieval of CVC along with card number and expiry "
    "from issuer for enrolled cards will be enabled during form fill.";

const char kAutofillEnableCardProductNameName[] =
    "Enable showing card product name";
const char kAutofillEnableCardProductNameDescription[] =
    "When enabled, card product name (instead of issuer network) will be shown "
    "in Payments Autofill UI.";

const char kAutofillEnableLogFormEventsToAllParsedFormTypesName[] =
    "Enable logging form events to all parsed form on a web page.";
const char kAutofillEnableLogFormEventsToAllParsedFormTypesDescription[] =
    "When enabled, a form event will log to all of the parsed forms of the "
    "same type on a webpage. This means credit card form events will log to "
    "all credit card form types and address form events will log to all "
    "address form types.";

const char kAutofillEnableNewCardArtAndNetworkImagesName[] =
    "Enable showing new card art and network images";
const char kAutofillEnableNewCardArtAndNetworkImagesDescription[] =
    "When enabled, new and larger card art and network icons will be shown.";
=======
const char kAutofillEnableOfferNotificationCrossTabTrackingName[] =
    "Enable cross tab status tracking for Autofill offer notification";
const char kAutofillEnableOfferNotificationCrossTabTrackingDescription[] =
    "When enabled, the offer notification showing will be tracked cross-tab, "
    "and on one merchant, the notification will only be shown once.";
>>>>>>> chromium

const char kAutofillEnableOffersInClankKeyboardAccessoryName[] =
    "Enable Autofill offers in keyboard accessory";
const char kAutofillEnableOffersInClankKeyboardAccessoryDescription[] =
    "When enabled, offers will be displayed in the keyboard accessory when "
    "available.";

const char kAutofillEnableOffersInDownstreamName[] =
    "Enable Autofill offers in downstream";
const char kAutofillEnableOffersInDownstreamDescription[] =
    "When enabled, offer data will be retrieved during downstream and shown in "
    "the dropdown list.";

const char kAutofillEnableStickyManualFallbackForCardsName[] =
    "Make manual fallback sticky for credit cards";
const char kAutofillEnableStickyManualFallbackForCardsDescription[] =
    "When enabled, if the user interacts with the manual fallback bottom "
    "sheet, it'll remain sticky until the user dismisses it.";

const char kAutofillEnableToolbarStatusChipName[] =
    "Move Autofill omnibox icons next to the profile avatar icon";
const char kAutofillEnableToolbarStatusChipDescription[] =
    "When enabled, Autofill data related icon will be shown in the status "
    "chip next to the profile avatar icon in the toolbar.";

const char kAutofillEnableVirtualCardName[] =
    "Offer to use cloud token virtual card in Autofill";
const char kAutofillEnableVirtualCardDescription[] =
    "When enabled, if all requirements are met, Autofill will offer to use "
    "virtual credit cards in form filling.";

const char kAutofillFixOfferInIncognitoName[] =
    "Enable the fix for Autofill offer in Incognito mode";
const char kAutofillFixOfferInIncognitoDescription[] =
    "When enabled, the fix will be enabled and offers should work correctly in "
    "Incognito mode.";

<<<<<<< HEAD
const char kAutofillEnableSaveAndFillName[] = "Enable Save and Fill";
const char kAutofillEnableSaveAndFillDescription[] =
    "When enabled, show an option to offer saving and filling a credit card "
    "with a single click when users don't have any cards saved in Autofill.";

const char kAutofillEnableSaveCardLoadingAndConfirmationName[] =
    "Enable save card loading and confirmation UX";
const char kAutofillEnableSaveCardLoadingAndConfirmationDescription[] =
    "When enabled, a loading spinner will be shown when uploading a card to "
    "the server and a confirmation screen will be will be shown based on the "
    "result of the upload. If the upload is unsuccessful in being uploaded to "
    "the server, it will be saved locally.";
=======
const char kAutofillParseMerchantPromoCodeFieldsName[] =
    "Parse promo code fields in forms";
const char kAutofillParseMerchantPromoCodeFieldsDescription[] =
    "When enabled, Autofill will attempt to find merchant promo/coupon/gift "
    "code fields when parsing forms.";
>>>>>>> chromium

const char kAutofillProfileClientValidationName[] =
    "Autofill Validates Profiles By Client";
const char kAutofillProfileClientValidationDescription[] =
    "Allows autofill to validate profiles on the client side";

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
const char kAutofillEnableSyncingOfPixBankAccountsName[] =
    "Sync Pix bank accounts from Google Payments";
const char kAutofillEnableSyncingOfPixBankAccountsDescription[] =
    "When enabled, Pix bank accounts are synced from Google Payments backend. "
    "These bank account will show up in Chrome settings.";
#endif  // BUILDFLAG(IS_ANDROID)
=======
const char kAutofillProfileServerValidationName[] =
    "Autofill Uses Server Validation";
const char kAutofillProfileServerValidationDescription[] =
    "Allows autofill to use server side validation";

const char kAutofillPruneSuggestionsName[] = "Autofill Prune Suggestions";
const char kAutofillPruneSuggestionsDescription[] =
    "Further limits the number of suggestions in the Autofill dropdown.";
>>>>>>> chromium

const char kAutofillSaveAndFillVPAName[] =
    "Offer save and autofill of UPI/VPA values";
const char kAutofillSaveAndFillVPADescription[] =
    "If enabled, when autofill recognizes a UPI/VPA value in a payment form, "
    "it will offer to save it. If saved, it will be offered for filling in "
    "fields which expect a VPA.";

const char kAutofillSuggestVirtualCardsOnIncompleteFormName[] =
    "Autofill suggests virtual cards on incomplete forms";
const char kAutofillSuggestVirtualCardsOnIncompleteFormDescription[] =
    "When enabled, merchant bound virtual cards will be suggested even if not "
    "all "
    "of the card number, exp date and CVC fields are detected in a payment "
    "form.";

const char kAutofillUseImprovedLabelDisambiguationName[] =
    "Autofill Uses Improved Label Disambiguation";
const char kAutofillUseImprovedLabelDisambiguationDescription[] =
    "When enabled, the Autofill dropdown's suggestions' labels are displayed "
    "using the improved disambiguation format.";

const char kAutoScreenBrightnessName[] = "Auto Screen Brightness model";
const char kAutoScreenBrightnessDescription[] =
    "Uses Auto Screen Brightness ML model (if it exists) to adjust screen "
    "brightness based on ambient light. If disabled, screen brightness "
    "will be controlled by the heuristic model provided by powerd (and only "
    "on devices that have ambient light sensors).";

<<<<<<< HEAD
const char kAutofillEnableVirtualCardMetadataName[] =
    "Enable showing metadata for virtual cards";
const char kAutofillEnableVirtualCardMetadataDescription[] =
    "When enabled, Chrome will show metadata together with other card "
    "information when the virtual card is presented to users.";

const char kAutofillImprovedLabelsName[] =
    "Autofill suggestions with improved labels";
const char kAutofillImprovedLabelsDescription[] =
    "When enabled, the autofill suggestion labels are more more descriptive "
    "and relevant.";

const char kAutofillParseVcnCardOnFileStandaloneCvcFieldsName[] =
    "Parse standalone CVC fields for VCN card on file in forms";
const char kAutofillParseVcnCardOnFileStandaloneCvcFieldsDescription[] =
    "When enabled, Autofill will attempt to find standalone CVC fields for VCN "
    "card on file when parsing forms.";

const char kAutofillMoreProminentPopupName[] = "More prominent Autofill popup";
const char kAutofillMoreProminentPopupDescription[] =
    "If enabled Autofill's popup becomes more prominent, i.e. its shadow "
    "becomes more emphasized, position is also updated";

const char kAutofillRemovePaymentsButterDropdownName[] =
    "Remove \"Show cards from your Google Account\" dropdown";
const char kAutofillRemovePaymentsButterDropdownDescription[] =
    "When enabled, the \"Show cards from your Google Account\" Autofill "
    "suggestion will not be displayed, and Autofill will work as if it had "
    "been selected.";

const char kAutofillSharedStorageServerCardDataName[] =
    "Enable storing autofill server card data in the shared storage database";
const char kAutofillSharedStorageServerCardDataDescription[] =
    "When enabled, the cached server credit card data from autofill will be "
    "pushed into the shared storage database for the payments origin.";

#if BUILDFLAG(IS_ANDROID)
const char kAutofillSyncEwalletAccountsName[] =
    "Sync eWallet accounts from Google Payments";
const char kAutofillSyncEwalletAccountsDescription[] =
    "When enabled, eWallet accounts are synced from the Google Payments "
    "servers and displayed on the payment methods settings page.";
#endif  // BUILDFLAG(IS_ANDROID)

const char kAutofillUnmaskCardRequestTimeoutName[] =
    "Timeout for the credit card unmask request";
const char kAutofillUnmaskCardRequestTimeoutDescription[] =
    "When enabled, sets a client-side timeout on the Autofill credit card "
    "unmask request. Upon timeout, the client will terminate the current "
    "unmask server call, which may or may not terminate the ongoing unmask UI.";

const char kAutofillUploadCardRequestTimeoutName[] =
    "Timeout for the credit card upload request";
const char kAutofillUploadCardRequestTimeoutDescription[] =
    "When enabled, sets a client-side timeout on the Autofill credit card "
    "upload request. Upon timeout, the client will terminate the upload UI, "
    "but the request may still succeed server-side.";

const char kAutofillVcnEnrollRequestTimeoutName[] =
    "Timeout for the credit card VCN enrollment request";
const char kAutofillVcnEnrollRequestTimeoutDescription[] =
    "When enabled, sets a client-side timeout on the Autofill credit card "
    "VCN enrollment request. Upon timeout, the client will terminate the VCN "
    "enrollment UI, but the request may still succeed server-side.";

const char kAutofillVirtualViewStructureAndroidName[] =
    "Enable the setting to provide a virtual view structure for Autofill";
const char kAutofillVirtualViewStructureAndroidDescription[] =
    "When enabled, a setting allows to switch to using Android Autofill. Chrome"
    " then provides a virtual view structure but no own suggestions.";

const char kAutoPictureInPictureForVideoPlaybackName[] =
    "Auto picture in picture for video playback";
const char kAutoPictureInPictureForVideoPlaybackDescription[] =
    "Enables auto picture in picture for video playback. Requires "
    "chrome://flags/#auto-picture-in-picture-video-heuristics to be enabled.";

const char kAutoPictureInPictureVideoHeuristicsName[] =
    "Auto picture in picture video heuristics";
const char kAutoPictureInPictureVideoHeuristicsDescription[] =
    "Enables the use of video heuristics for tracking HTMLVideoElement "
    "visibility.";
=======
const char kAvatarToolbarButtonName[] = "Avatar Toolbar Button";
const char kAvatarToolbarButtonDescription[] =
    "Enables the avatar toolbar button and the associated menu";
>>>>>>> chromium

const char kBackForwardCacheName[] = "Back-forward cache";
const char kBackForwardCacheDescription[] =
    "If enabled, caches eligible pages after cross-site navigations."
    "To enable caching pages on same-site navigations too, choose 'enabled "
    "same-site support'.";

const char kBentoBarName[] = "Persistent desks bar";
const char kBentoBarDescription[] =
    "Showing a persistent desks bar at the top of the screen in clamshell mode "
    "when there are more than one desk.";

const char kBiometricReauthForPasswordFillingName[] =
    "Biometric reauth for password filling";
const char kBiometricReauthForPasswordFillingDescription[] =
    "Enables biometric"
    "re-authentication before password filling";

<<<<<<< HEAD
const char kBindCookiesToPortName[] =
    "Bind cookies to their setting origin's port";
const char kBindCookiesToPortDescription[] =
    "If enabled, cookies will only be accessible by origins with the same port "
    "as the one that originally set the cookie.";

const char kBindCookiesToSchemeName[] =
    "Bind cookies to their setting origin's scheme";
const char kBindCookiesToSchemeDescription[] =
    "If enabled, cookies will only be accessible by origins with the same "
    "scheme as the one that originally set the cookie";

const char kBackgroundListeningName[] = "BackgroundListening";
const char kBackgroundListeningDescription[] =
    "Enables the new media player features optimized for background listening.";

const char kBorealisBigGlName[] = "Borealis Big GL";
const char kBorealisBigGlDescription[] = "Enable Big GL when running Borealis.";

const char kBorealisDGPUName[] = "Borealis dGPU";
const char kBorealisDGPUDescription[] = "Enable dGPU when running Borealis.";

const char kBorealisEnableUnsupportedHardwareName[] =
    "Borealis Enable Unsupported Hardware";
const char kBorealisEnableUnsupportedHardwareDescription[] =
    "Allow Borealis to run on hardware that does not meet the minimum spec "
    "requirements. Be aware: Games may crash, or perform below expectations.";

const char kBorealisForceBetaClientName[] = "Borealis Force Beta Client";
const char kBorealisForceBetaClientDescription[] =
    "Force the client to run its beta version.";

const char kBorealisForceDoubleScaleName[] = "Borealis Force Double Scale";
const char kBorealisForceDoubleScaleDescription[] =
    "Force the client to run in 2x visual zoom. the scale client by DPI flag "
    "needs to be off for this to take effect.";

const char kBorealisLinuxModeName[] = "Borealis Linux Mode";
const char kBorealisLinuxModeDescription[] =
    "Do not run ChromeOS-specific code in the client.";

// For UX reasons we prefer "enabled", but that is used internally to refer to
// whether borealis is installed or not, so the name of the variable is a bit
// different to the user-facing name.
const char kBorealisPermittedName[] = "Borealis Enabled";
const char kBorealisPermittedDescription[] =
    "Allows Borealis to run on your device. Borealis may still be blocked for "
    "other reasons, including: administrator settings, device hardware "
    "capabilities, or other security measures.";

const char kBorealisProvisionName[] = "Borealis Provision";
const char kBorealisProvisionDescription[] =
    "Uses the experimental 'provision' option when mounting borealis stateful. "
    "The feature causes allocations on thinly provisioned storage, such as "
    "sparse vm images, to be passed to the underlying storage layers. "
    "Resulting in allocations in the Borealis being backed by physical "
    "storage.";

const char kBorealisScaleClientByDPIName[] = "Borealis Scale Client By DPI";
const char kBorealisScaleClientByDPIDescription[] =
    "Enable scaling the Steam client according to device DPI. "
    "If enabled this will override the force double scale flag.";

const char kBorealisZinkGlDriverName[] = "Borealis Zink GL Driver";
const char kBorealisZinkGlDriverDescription[] =
    "Enables zink driver for GL rendering in Borealis. Can be enabled for "
    "recommended GL apps only or for all GL apps. Defaults to recommended.";
=======
const char kBorealisDiskManagementName[] = "Borealis Disk management";
const char kBorealisDiskManagementDescription[] =
    "Enable experimental disk management settings.";
>>>>>>> chromium

const char kBypassAppBannerEngagementChecksName[] =
    "Bypass user engagement checks";
const char kBypassAppBannerEngagementChecksDescription[] =
    "Bypasses user engagement checks for displaying app banners, such as "
    "requiring that users have visited the site before and that the banner "
    "hasn't been shown recently. This allows developers to test that other "
    "eligibility requirements for showing app banners, such as having a "
    "manifest, are met.";

const char kChangePasswordAffiliationInfoName[] =
    "Using Affiliation Service for Change Password URLs";
const char kChangePasswordAffiliationInfoDescription[] =
    "In case site doesn't support /.well-known/change-password Chrome will try "
    "to obtain it using Affiliation Service.";

<<<<<<< HEAD
const char kSeparateWebAppShortcutBadgeIconName[] =
    "Separate Web App Shortcut Badge Icon";
const char kSeparateWebAppShortcutBadgeIconDescription[] =
    "The shortcut app badge is painted in the UI instead of being part of the "
    "shortcut app icon, and more effects are added for the icon.";
=======
const char kCheckOfflineCapabilityName[] = "Check offline capability for PWAs";
const char kCheckOfflineCapabilityDescription[] =
    "Use advanced offline capability check to decide whether the browser "
    "displays install prompts for PWAs.";
>>>>>>> chromium

const char kChromeLabsName[] = "Chrome Labs";
const char kChromeLabsDescription[] =
    "Access Chrome Labs through the toolbar menu to see featured user-facing "
    "experimental features.";

const char kCompositeAfterPaintName[] = "Composite after paint";
const char kCompositeAfterPaintDescription[] =
    "A new algorithm to create compositing layers. "
    "See http://bit.ly/composite-after-paint.";

const char kContextMenuGoogleLensChipName[] =
    "Google Lens powered image search for surfaced as a chip below the context "
    "menu.";
const char kContextMenuGoogleLensChipDescription[] =
    "Enable a chip for a Shopping intent into Google Lens when supported. ";

<<<<<<< HEAD
const char kClientSideDetectionBrandAndIntentForScamDetectionName[] =
    "Client Side Detection Brand and  Intent for Scam Detection";
const char kClientSideDetectionBrandAndIntentForScamDetectionDescription[] =
    "Enables on device LLM output on pages to inquire for brand and intent of "
    "the page.";
=======
const char kContextMenuSearchWithGoogleLensName[] =
    "Google Lens powered image search in the context menu.";
const char kContextMenuSearchWithGoogleLensDescription[] =
    "Replaces default image search with an intent to Google Lens when "
    "supported.";

const char kContextMenuShopWithGoogleLensName[] =
    "Google Lens powered image search for shoppable images in the context "
    "menu.";
const char kContextMenuShopWithGoogleLensDescription[] =
    "Enable a menu item for a Shopping intent into Google Lens when supported. "
    "By default replaces the Search with Google Lens option.";

const char kContextMenuSearchAndShopWithGoogleLensName[] =
    "Additional menu item for Google Lens image search for shoppable images in "
    "the context menu.";
const char kContextMenuSearchAndShopWithGoogleLensDescription[] =
    "Display an additional menu item for a Shopping intent to Google Lens "
    "below Search with Google Lens when Lens shopping feature is enabled";

const char kContextMenuTranslateWithGoogleLensName[] =
    "Google Lens powered image search for translatable images surfaced as a "
    "chip under the context menu.";
const char kContextMenuTranslateWithGoogleLensDescription[] =
    "Enable a chip for a Translate intent into Google Lens when supported.";

const char kClipboardCustomFormatsName[] = "Clipboard Custom Formats";
const char kClipboardCustomFormatsDescription[] =
    "Allows read/write of custom formats with unsanitized clipboard content. "
    "See crbug.com/106449";

const char kClickToOpenPDFName[] = "Click to open embedded PDFs";
const char kClickToOpenPDFDescription[] =
    "When the PDF plugin is unavailable, show a click-to-open placeholder for "
    "embedded PDFs.";

const char kClientStorageAccessContextAuditingName[] =
    "Access contexts for client-side storage";
const char kClientStorageAccessContextAuditingDescription[] =
    "Record the first-party contexts in which client-side storage was accessed";
>>>>>>> chromium

const char kClearCrossSiteCrossBrowsingContextGroupWindowNameName[] =
    "Clear window name in top-level cross-site cross-browsing-context-group "
    "navigation";
const char kClearCrossSiteCrossBrowsingContextGroupWindowNameDescription[] =
    "Clear the preserved window.name property when it's a top-level cross-site "
    "navigation that swaps BrowsingContextGroup.";

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
const char kChromeTipsInMainMenuName[] =
    "Show 'Tips for Chrome' in Help portion of main menu.";
const char kChromeTipsInMainMenuDescription[] =
    "Enables 'Tips for Chrome' in main menu; the menu item will take users to "
    "an official Google site with information about the latest and most "
    "popular Chrome features.";

<<<<<<< HEAD
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || \
    BUILDFLAG(IS_CHROMEOS)
const char kDocumentPictureInPictureAnimateResizeName[] =
    "Document Picture-in-Picture Animate Resize";
const char kDocumentPictureInPictureAnimateResizeDescription[] =
    "Use an animation when programmatically resizing a document"
    "picture-in-picture window";

const char kAudioDuckingName[] = "Audio Ducking";
const char kAudioDuckingDescription[] =
    "Allows Chrome to duck (attenuate) "
    "audio from other tabs.";
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) ||
        // BUILDFLAG(IS_CHROMEOS)
=======
const char kChromeTipsInMainMenuNewBadgeName[] =
    "Show 'New' promo badge on 'Tips for Chrome' in Help portion of main menu.";
const char kChromeTipsInMainMenuNewBadgeDescription[] =
    "Enables 'New' promo badge on 'Tips for Chrome' in main menu; experiment to"
    " test the value of this user education feature.";
#endif
>>>>>>> chromium

const char kChromeWhatsNewUIName[] =
    "Show Chrome What's New page at chrome://whats-new";
const char kChromeWhatsNewUIDescription[] =
    "Enables Chrome What's New page at chrome://whats-new.";

<<<<<<< HEAD
const char kVisitedURLRankingServiceDeduplicationName[] =
    "Visited URL ranking deduplication strategy";
const char kVisitedURLRankingServiceDeduplicationDescription[] =
    "Enables visited url ranking service to use one of various deduplication "
    "strategies.";

const char kVisitedURLRankingServiceHistoryVisibilityScoreFilterName[] =
    "Enable visited URL aggregates visibility score based filtering";
const char kVisitedURLRankingServiceHistoryVisibilityScoreFilterDescription[] =
    "Enables filtering of visited URL aggregates based on history URL "
    "visibility scores.";
=======
#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
const char kChromeWhatsNewInMainMenuNewBadgeName[] =
    "Show 'New' badge on 'What's New' menu item.";
const char kChromeWhatsNewInMainMenuNewBadgeDescription[] =
    "Enables 'New' promo badge on 'What's New' in the Help portion of the main "
    "menu.";
#endif
>>>>>>> chromium

const char kCompositingBasedThrottling[] = "Compositing-based Throttling";
const char kCompositingBasedThrottlingDescription[] =
    "Enables compositing-based throttling to throttle appropriate frame sinks "
    "that do not need to be refreshed at high fps.";

<<<<<<< HEAD
=======
const char kDarkLightTestName[] = "Dark/light mode of system UI";
const char kDarkLightTestDescription[] =
    "Enables the dark/light mode of system UI, which includes shelf, launcher, "
    "system tray etc.";

const char kDecodeJpeg420ImagesToYUVName[] = "YUV decoding for JPEG";
const char kDecodeJpeg420ImagesToYUVDescription[] =
    "Decode and render 4:2:0 formatted jpeg images from YUV instead of RGB."
    "This feature requires GPU or OOP rasterization to also be enabled.";

const char kDecodeLossyWebPImagesToYUVName[] = "YUV Decoding for WebP";
const char kDecodeLossyWebPImagesToYUVDescription[] =
    "Decode and render lossy WebP images from YUV instead of RGB. "
    "You must also have GPU rasterization or OOP rasterization.";

>>>>>>> chromium
const char kDoubleBufferCompositingName[] = "Double buffered compositing";
const char kDoubleBufferCompositingDescription[] =
    "Use double buffer for compositing (instead of triple-buffering). "
    "Latency should be reduced in some cases. On the other hand, more skipped "
    "frames are expected.";

<<<<<<< HEAD
const char kMediaSessionEnterPictureInPictureName[] =
    "Media Session enterpictureinpicture action";
const char kMediaSessionEnterPictureInPictureDescription[] =
    "Enables the 'enterpictureinpicture' MediaSessionAction to allow websites "
    "to register an action handler for entering picture-in-picture.";
=======
const char kEnablePasswordsAccountStorageName[] =
    "Enable the account data storage for passwords";
const char kEnablePasswordsAccountStorageDescription[] =
    "Enables storing passwords in a second, Gaia-account-scoped storage for "
    "signed-in but not syncing users";

const char kEnablePasswordsAccountStorageIPHName[] =
    "Enable IPH for the account data storage for passwords";
const char kEnablePasswordsAccountStorageIPHDescription[] =
    "Enables in-product help bubbles about storing passwords in a second, "
    "Gaia-account-scoped storage for signed-in but not syncing users";
>>>>>>> chromium

const char kFontAccessAPIName[] = "Font Access APIs";
const char kFontAccessAPIDescription[] =
    "Enables the experimental Font Access APIs, giving websites access "
    "to enumerate local fonts and access their table data.";

<<<<<<< HEAD
const char kCollaborationMessagingName[] = "Collaboration Messaging";
const char kCollaborationMessagingDescription[] =
    "Enables the messaging framework within the collaboration feature, "
    "including features such as recent activity, dirty dots, and description "
    "action chips.";

const char kCompressionDictionaryTransportName[] =
    "Compression dictionary transport";
const char kCompressionDictionaryTransportDescription[] =
    "Enables compression dictionary transport features. Requires "
    "chrome://flags/#enable-compression-dictionary-transport-backend to be "
    "enabled.";

const char kCompressionDictionaryTransportBackendName[] =
    "Compression dictionary transport backend";
const char kCompressionDictionaryTransportBackendDescription[] =
    "Enables the backend of compression dictionary transport features. "
    "Requires chrome://flags/#enable-compression-dictionary-transport to be "
    "enabled for testing the feature.";

const char kCompressionDictionaryTransportOverHttp1Name[] =
    "Compression dictionary transport over HTTP/1";
const char kCompressionDictionaryTransportOverHttp1Description[] =
    "When this is enabled, Chromium can use stored shared dictionaries even "
    "when the connection is using HTTP/1 for non-localhost requests.";

const char kCompressionDictionaryTransportOverHttp2Name[] =
    "Compression dictionary transport over HTTP/2";
const char kCompressionDictionaryTransportOverHttp2Description[] =
    "When this is enabled, Chromium can use stored shared dictionaries even "
    "when the connection is using HTTP/2 for non-localhost requests.";

const char kCompressionDictionaryTransportRequireKnownRootCertName[] =
    "Compression dictionary transport require known root cert";
const char kCompressionDictionaryTransportRequireKnownRootCertDescription[] =
    "When this is enabled, Chromium can use stored shared dictionaries only "
    "when the connection is using a well known root cert or when the server is "
    "a localhost.";

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
const char kContextualCueingName[] = "Contextual cueing";
const char kContextualCueingDescription[] =
    "Enables the contextual cueing system to support showing actions";

#endif  // #if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)

#if BUILDFLAG(IS_ANDROID)
const char kContextualSearchWithCredentialsForDebugName[] =
    "Contextual Search within credentials for debug";
const char kContextualSearchWithCredentialsForDebugDescription[] =
    "When this is enabled, if a user do the contextual search, the credentials "
    "mode will be include.";
#endif  // BUILDFLAG(IS_ANDROID)
=======
const char kFontAccessPersistentName[] =
    "Enable persistent access to the Font Access API";
const char kFontAccessPersistentDescription[] =
    "Enables persistent access to the Font Access API, giving websites access "
    "to enumerate local fonts after being granted a permission.";
>>>>>>> chromium

const char kForceColorProfileSRGB[] = "sRGB";
const char kForceColorProfileP3[] = "Display P3 D65";
const char kForceColorProfileColorSpin[] = "Color spin with gamma 2.4";
const char kForceColorProfileSCRGBLinear[] =
    "scRGB linear (HDR where available)";
const char kForceColorProfileHDR10[] = "HDR10 (HDR where available)";

const char kForceColorProfileName[] = "Force color profile";
const char kForceColorProfileDescription[] =
    "Forces Chrome to use a specific color profile instead of the color "
    "of the window's current monitor, as specified by the operating system.";

const char kDynamicColorGamutName[] = "Dynamic color gamut";
const char kDynamicColorGamutDescription[] =
    "Displays in wide color when the content is wide. When the content is "
    "not wide, displays sRGB";

<<<<<<< HEAD
=======
const char kCooperativeSchedulingName[] = "Cooperative Scheduling";
const char kCooperativeSchedulingDescription[] =
    "Enables cooperative scheduling in Blink.";

const char kCreditCardAssistName[] = "Credit Card Assisted Filling";
const char kCreditCardAssistDescription[] =
    "Enable assisted credit card filling on certain sites.";

>>>>>>> chromium
const char kDarkenWebsitesCheckboxInThemesSettingName[] =
    "Darken websites checkbox in themes setting";
const char kDarkenWebsitesCheckboxInThemesSettingDescription[] =
    "Show a darken websites checkbox in themes settings when system default or "
    "dark is selected. The checkbox can toggle the auto-darkening web contents "
    "feature";

const char kDebugPackedAppName[] = "Debugging for packed apps";
const char kDebugPackedAppDescription[] =
    "Enables debugging context menu options such as Inspect Element for packed "
    "applications.";

const char kDebugShortcutsName[] = "Debugging keyboard shortcuts";
const char kDebugShortcutsDescription[] =
    "Enables additional keyboard shortcuts that are useful for debugging Ash.";

const char kDetectTargetEmbeddingLookalikesName[] =
    "Detect target embedding domains as lookalikes.";
const char kDetectTargetEmbeddingLookalikesDescription[] =
    "Shows a lookalike interstitial when navigating to target embedding domains"
    "(e.g. google.com.example.com).";

const char kDeviceDiscoveryNotificationsName[] =
    "Device Discovery Notifications";
const char kDeviceDiscoveryNotificationsDescription[] =
    "Device discovery notifications on local network.";

const char kDisableProcessReuse[] = "Disable subframe process reuse";
const char kDisableProcessReuseDescription[] =
    "Prevents out-of-process iframes from reusing compatible processes from "
    "unrelated tabs. This is an experimental mode that will result in more "
    "processes being created.";

const char kDisallowDocWrittenScriptsUiName[] =
    "Block scripts loaded via document.write";
const char kDisallowDocWrittenScriptsUiDescription[] =
    "Disallows fetches for third-party parser-blocking scripts inserted into "
    "the main frame via document.write.";

<<<<<<< HEAD
const char kViewTransitionLayeredCaptureName[] =
    "CSS view transition layered capture";
const char kViewTransitionLayeredCaptureDescription[] =
    "Controls the way view transition elements are captured. "
    "When enabled, view transition borders, backgrounds, effects etc. "
    "are captured as style instead of being baked into the image.";

const char kViewTransitionOnNavigationName[] =
    "viewTransition API for navigations";
const char kViewTransitionOnNavigationDescription[] =
    "Controls the availability of the viewTransition API on document "
    "navigations.";

const char kViewTransitionOnNavigationIframeName[] =
    "viewTransition API for sub-frame navigations";
const char kViewTransitionOnNavigationIframeDescription[] =
    "Controls the availability of the viewTransition API on document "
    "navigations in a subframe. Must be used with "
    "view-transition-on-navigation";

const char kViewTransitionOverflowRectFromSurfaceName[] =
    "CSS view transitions: compute visual overflow from surfaces";
const char kViewTransitionOverflowRectFromSurfaceDescription[] =
    "Changes the underlying mechanism to compute the view transition live "
    "element geometry. "
    "This shouldn't have web-observable effects, but exposing as a flag for "
    "easy triage.";

const char kEnableAutoDisableAccessibilityName[] = "Auto-disable Accessibility";
const char kEnableAutoDisableAccessibilityDescription[] =
    "When accessibility APIs are no longer being requested, automatically "
    "disables accessibility. This might happen if an assistive technology is "
    "turned off or if an extension which uses accessibility APIs no longer "
    "needs them.";

const char kImageDescriptionsAlternateRoutingName[] =
    "Use alternative route for image descriptions.";
const char kImageDescriptionsAlternateRoutingDescription[] =
    "When adding automatic captions to images, use a different route to "
    "acquire descriptions.";

const char kImprovedSigninUIOnDesktopName[] = "Improved signin UI";
const char kImprovedSigninUIOnDesktopDescription[] =
    "Enables redesign of profile menu and signin settings ; new signin promos "
    "and better signin errors.";
=======
const char kDocumentTransitionName[] = "documentTransition API";
const char kDocumentTransitionDescription[] =
    "Controls the availability of the documentTransition JavaScript API.";

const char kEnableAudioFocusEnforcementName[] = "Audio Focus Enforcement";
const char kEnableAudioFocusEnforcementDescription[] =
    "Enables enforcement of a single media session having audio focus at "
    "any one time. Requires #enable-media-session-service to be enabled too.";

const char kEnableAutofillAccountWalletStorageName[] =
    "Enable the account data storage for autofill";
const char kEnableAutofillAccountWalletStorageDescription[] =
    "Enable the ephemeral storage for account data for autofill.";
>>>>>>> chromium

const char kImprovedSettingsUIOnDesktopName[] = "Improved settings UI";
const char kImprovedSettingsUIOnDesktopDescription[] =
    "Enables redesign of signin settings and better signin errors in "
    "chrome://settings.";

const char kIsSecurePaymentConfirmationAvailableAPIName[] =
    "isSecurePaymentConfirmationAvailable API";
const char kIsSecurePaymentConfirmationAvailableAPIDescription[] =
    "Enables the PaymentRequest.isSecurePaymentConfirmationAvailable web API, "
    "which allows for more ergonomic feature detection of Secure Payment "
    "Confirmation";

const char kEnableAutofillAddressSavePromptName[] =
    "Autofill Address Save Prompts";
const char kEnableAutofillAddressSavePromptDescription[] =
    "Enable the Autofill address save prompts.";

const char kEnableAutofillCreditCardAuthenticationName[] =
    "Allow using platform authenticators to retrieve server cards";
const char kEnableAutofillCreditCardAuthenticationDescription[] =
    "When enabled, users will be given the option to use a platform "
    "authenticator (if available) to verify card ownership when retrieving "
    "credit cards from Google Payments.";

const char
    kEnableAutofillInfoBarAccountIndicationFooterForSingleAccountUsersName[] =
        "Display InfoBar footers with account indication information for "
        "single account users";
const char
    kEnableAutofillInfoBarAccountIndicationFooterForSingleAccountUsersDescription
        [] = "When enabled and user has single account, a footer indicating "
             "user's e-mail address  will appear at the bottom of InfoBars "
             "which has corresponding account indication footer flags on.";

const char kEnableAutofillInfoBarAccountIndicationFooterForSyncUsersName[] =
    "Display InfoBar footers with account indication information for "
    "sync users";
const char
    kEnableAutofillInfoBarAccountIndicationFooterForSyncUsersDescription[] =
        "When enabled and user is signed in, a footer indicating user's e-mail "
        "address  will appear at the bottom of InfoBars which has "
        "corresponding account indication footer flags on.";

const char kEnableAutofillPasswordInfoBarAccountIndicationFooterName[] =
    "Display password InfoBar footers with account indication information";
const char kEnableAutofillPasswordInfoBarAccountIndicationFooterDescription[] =
    "When enabled, a footer indicating user's e-mail address will appear at "
    "the bottom of corresponding password InfoBars.";

const char kEnableAutofillSaveCardInfoBarAccountIndicationFooterName[] =
    "Display SaveCardInfoBar footer with account indication information";
const char kEnableAutofillSaveCardInfoBarAccountIndicationFooterDescription[] =
    "When enabled, a footer indicating user's e-mail address will appear at "
    "the bottom of SaveCardInfoBar.";

const char kEnableAutofillCreditCardUploadFeedbackName[] =
    "Enable feedback for credit card upload flow";
const char kEnableAutofillCreditCardUploadFeedbackDescription[] =
    "When enabled, if credit card upload succeeds, the avatar button will "
    "show a highlight, otherwise the icon will be updated and if it is "
    "clicked, the save card failure bubble will be shown.";

#if BUILDFLAG(IS_ANDROID)
const char kEnterpriseRealTimeUrlCheckOnAndroidName[] =
    "Allow the enterprise real-time URL check";
const char kEnterpriseRealTimeUrlCheckOnAndroidDescription[] =
    "Enables enterprise real-time URL checks if the "
    "EnterpriseRealTimeUrlCheckMode policy is set.";
#endif

const char kEnableExperimentalCookieFeaturesName[] =
    "Enable experimental cookie features";
const char kEnableExperimentalCookieFeaturesDescription[] =
    "Enable new features that affect setting, sending, and managing cookies. "
    "The enabled features are subject to change at any time.";

const char kEnableSaveDataName[] = "Enables save data feature";
const char kEnableSaveDataDescription[] =
    "Enables save data feature. May cause user's traffic to be proxied via "
    "Google's data reduction proxy.";

const char kEnableNavigationPredictorName[] = "Enables navigation predictor";
const char kEnableNavigationPredictorDescription[] =
    "Enables navigation predictor feature that predicts the next likely "
    "navigation using a set of heuristics.";

const char kEnablePreconnectToSearchName[] =
    "Enables preconnections to default search engine";
const char kEnablePreconnectToSearchDescription[] =
    "Enables the feature that preconnects to the user's default search engine.";

const char kEnableRemovingAllThirdPartyCookiesName[] =
    "Enable removing SameSite=None cookies";
const char kEnableRemovingAllThirdPartyCookiesDescription[] =
    "Enables UI on chrome://settings/siteData to remove all third-party "
    "cookies and site data.";

const char kEnableBrowsingDataLifetimeManagerName[] =
    "Enables the BrowsingDataLifetimeManager service to run.";
const char kEnableBrowsingDataLifetimeManagerDescription[] =
    "Enables the BrowsingDataLifetimeManager service to run and periodically "
    "delete browsing data as specified by the BrowsingDataLifetime policy.";

<<<<<<< HEAD
const char kDesktopPWAsAppTitleName[] = "Desktop PWA Application Title";
const char kDesktopPWAsAppTitleDescription[] =
    "Enable PWAs to set a custom title for their windows.";
=======
const char kColorProviderRedirectionName[] = "Color Provider Redirection";
const char kColorProviderRedirectionDescription[] =
    "Redirects color requests to the color provider where possible.";

const char kDesktopPWAsPrefixAppNameInWindowTitleName[] =
    "Desktop PWAs prefix window title with app name.";
const char kDesktopPWAsPrefixAppNameInWindowTitleDescription[] =
    "Prefix the window title of installed PWAs with the name of the PWA. On "
    "ChromeOS this is visible only in the window/activity switcher.";

const char kDesktopPWAsAppIconShortcutsMenuName[] =
    "Desktop PWAs app icon shortcuts menu";
const char kDesktopPWAsAppIconShortcutsMenuDescription[] =
    "Enable installed PWAs to include a menu of shortcuts associated with the "
    "app icon in the taskbar on Windows, or the dock on macOS or Linux.";

const char kDesktopPWAsAppIconShortcutsMenuUIName[] =
    "Desktop PWAs app icon shortcuts menu UI";
const char kDesktopPWAsAppIconShortcutsMenuUIDescription[] =
    "Show web app shortcuts in the shelf context menu";

const char kDesktopPWAsAttentionBadgingCrOSName[] =
    "Desktop PWAs Attention Badging";
const char kDesktopPWAsAttentionBadgingCrOSDescription[] =
    "Enable attention badging for PWA icons in the shelf and launcher.";
const char kDesktopPWAsAttentionBadgingCrOSApiAndNotifications[] =
    "for Badging API and notifications";
const char kDesktopPWAsAttentionBadgingCrOSApiOverridesNotifications[] =
    "for Badging API, or notifications for apps not using Badging API";
const char kDesktopPWAsAttentionBadgingCrOSApiOnly[] = "for Badging API only";
const char kDesktopPWAsAttentionBadgingCrOSNotificationsOnly[] =
    "for notifications only";

const char kDesktopPWAsRemoveStatusBarName[] = "Desktop PWAs remove status bar";
const char kDesktopPWAsRemoveStatusBarDescription[] =
    "Hides the status bar popup in Desktop PWA app windows.";
>>>>>>> chromium

const char kDesktopPWAsElidedExtensionsMenuName[] =
    "Desktop PWAs elided extensions menu";
const char kDesktopPWAsElidedExtensionsMenuDescription[] =
    "Moves the Extensions \"puzzle piece\" icon from the title bar into the "
    "app menu for web app windows.";

const char kDesktopPWAsFlashAppNameInsteadOfOriginName[] =
    "Desktop PWAs flash app name instead of origin";
const char kDesktopPWAsFlashAppNameInsteadOfOriginDescription[] =
    "Replaces the origin flash with an app name flash when launching a web app "
    "window.";

const char kDesktopPWAsNotificationIconAndTitleName[] =
    "Desktop PWAs improvements in notification icon and title";
const char kDesktopPWAsNotificationIconAndTitleDescription[] =
    "Replaces the websites origin and the Chrome icon with the web app's name "
    "and app icon in notifications.";

const char kDesktopPWAsLinkCapturingName[] =
    "Desktop PWA declarative link capturing";
const char kDesktopPWAsLinkCapturingDescription[] =
    "Enable web app manifests to declare link capturing behavior. Prototype "
    "implementation of: "
    "https://github.com/WICG/sw-launch/blob/master/"
    "declarative_link_capturing.md";

const char kDesktopPWAsManifestIdName[] = "Desktop PWA manifest id";
const char kDesktopPWAsManifestIdDescription[] =
    "Enable web app manifests to declare id. Prototype "
    "implementation of: "
    "https://github.com/philloooo/pwa-unique-id/blob/main/explainer.md";

const char kDesktopPWAsTabStripName[] = "Desktop PWA tab strips";
const char kDesktopPWAsTabStripDescription[] =
    "Experimental UI for exploring what PWA windows would look like with a tab "
    "strip.";

const char kDesktopPWAsTabStripLinkCapturingName[] =
    "Desktop PWA tab strip link capturing";
const char kDesktopPWAsTabStripLinkCapturingDescription[] =
    "Experimental behaviour for \"Desktop PWA tab strips\" to capture link "
    "navigations within the app scope and bring them into the app's tabbed "
    "window.";

const char kDesktopPWAsTabStripSettingsName[] =
    "Desktop PWA tab strips settings";
const char kDesktopPWAsTabStripSettingsDescription[] =
    "Experimental UI for selecting whether a PWA should open in tabbed mode.";

const char kDesktopPWAsRunOnOsLoginName[] = "Desktop PWAs run on OS login";
const char kDesktopPWAsRunOnOsLoginDescription[] =
    "Enable installed PWAs to be configured to automatically start when the OS "
    "user logs in.";

const char kDesktopPWAsSubAppsName[] = "Desktop PWA Sub Apps";
const char kDesktopPWAsSubAppsDescription[] =
    "Enable installed PWAs to create shortcuts by installing their sub apps. "
    "Prototype implementation of: "
    "https://github.com/ivansandrk/multi-apps/blob/main/explainer.md";

const char kDesktopPWAsProtocolHandlingName[] = "Desktop PWA Protocol handling";
const char kDesktopPWAsProtocolHandlingDescription[] =
    "Enable web app manifests to declare protocol handling behavior."
    "See: https://crbug.com/1019239.";

const char kDesktopPWAsUrlHandlingName[] = "Desktop PWA URL handling";
const char kDesktopPWAsUrlHandlingDescription[] =
    "Enable web app manifests to declare URL handling behavior. Prototype "
    "implementation of: "
    "https://github.com/WICG/pwa-url-handler/blob/master/explainer.md";

const char kDesktopPWAsWindowControlsOverlayName[] =
    "Desktop PWA Window Controls Overlay";
const char kDesktopPWAsWindowControlsOverlayDescription[] =
    "Enable web app manifests to declare Window Controls Overlay as a display "
    "override. Prototype implementation of: "
    "https://github.com/WICG/window-controls-overlay/blob/main/explainer.md";

const char kDesktopPWAsWebBundlesName[] = "Desktop PWAs Web Bundles";
const char kDesktopPWAsWebBundlesDescription[] =
    "Adds support for web bundles, making web apps able to be launched "
    "offline.";

const char kEnableMigrateDefaultChromeAppToWebAppsGSuiteName[] =
    "Migrate default G Suite Chrome apps to web apps";
const char kEnableMigrateDefaultChromeAppToWebAppsGSuiteDescription[] =
    "Enable the migration of default installed G Suite Chrome apps over to "
    "their corresponding web apps.";

const char kEnableMigrateDefaultChromeAppToWebAppsNonGSuiteName[] =
    "Migrate default non-G Suite Chrome apps to web apps";
const char kEnableMigrateDefaultChromeAppToWebAppsNonGSuiteDescription[] =
    "Enable the migration of default installed non-G Suite Chrome apps over to "
    "their corresponding web apps.";

const char kEnableSyncRequiresPoliciesLoadedName[] =
    "Sync waits for all policies to load before starting";
const char kEnableSyncRequiresPoliciesLoadedDescription[] =
    "Enables behaviour for Sync to wait for all policies to load before "
    "starting";

const char kEnableTLS13EarlyDataName[] = "TLS 1.3 Early Data";
const char kEnableTLS13EarlyDataDescription[] =
    "This option enables TLS 1.3 Early Data, allowing GET requests to be sent "
    "during the handshake when resuming a connection to a compatible TLS 1.3 "
    "server.";

const char kEnhancedNetworkVoicesName[] = "Enhanced network voices";
const char kEnhancedNetworkVoicesDescription[] =
    "This option enables high-quality, network-based voices in "
    "Select-to-speak.";

const char kPostQuantumCECPQ2Name[] = "TLS Post-Quantum Confidentiality";
const char kPostQuantumCECPQ2Description[] =
    "This option enables a post-quantum (i.e. resistent to quantum computers) "
    "key exchange algorithm in TLS (CECPQ2).";

const char kMacCoreLocationImplementationName[] =
    "Core Location Implementation";
const char kMacCoreLocationImplementationDescription[] =
    "Enables usage of the Core Location APIs to get location permission on "
    "macOS";

<<<<<<< HEAD
const char kAccessibilityDisableTouchpadName[] =
    "Accessibility disable trackpad";
const char kAccessibilityDisableTouchpadDescription[] =
    "Adds a setting that allows the user to disable the built-in trackpad.";

const char kAccessibilityFlashScreenFeatureName[] =
    "Accessibility feature to flash the screen for each notification";
const char kAccessibilityFlashScreenFeatureDescription[] =
    "Allows the user to use a feature which flashes the screen for each "
    "notification.";

const char kAccessibilityServiceName[] = "Experimental Accessibility Service";
const char kAccessibilityServiceDescription[] =
    "This option enables the experimental Accessibility Service and runs some "
    "accessibility features in the service.";

const char kAccessibilityShakeToLocateName[] =
    "Adds shake cursor to locate feature";
const char kAccessibilityShakeToLocateDescription[] =
    "This option enables the experimental Accessibility feature to make the "
    "mouse cursor more visible when a shake is detected.";

const char kExperimentalAccessibilityColorEnhancementSettingsName[] =
    "Experimental Accessibility color enhancement settings";
const char kExperimentalAccessibilityColorEnhancementSettingsDescription[] =
    "This option enables the experimental Accessibility color enhancement "
    "settings found in the OS Accessibility settings.";

const char kAccessibilityChromeVoxPageMigrationName[] =
    "ChromeVox Page Migration";
const char kAccessibilityChromeVoxPageMigrationDescription[] =
    "This option enables ChromeVox page migration from extension options page "
    "to a Chrome OS settings page.";

const char kAccessibilityReducedAnimationsName[] =
    "Experimental Reduced Animations";
const char kAccessibilityReducedAnimationsDescription[] =
    "This option enables the setting to limit movement on the screen.";

const char kAccessibilityReducedAnimationsInKioskName[] =
    "Reduced Animations feature toggle available in Kiosk quick settings";
const char kAccessibilityReducedAnimationsInKioskDescription[] =
    "This option enables the quick settings option to toggle reduced "
    "animations.";

const char kAccessibilityFaceGazeName[] = "Experimental FaceGaze integration";
const char kAccessibilityFaceGazeDescription[] =
    "This option enables the experimental FaceGaze ChromeOS integration";

const char kAccessibilityMagnifierFollowsChromeVoxName[] =
    "Magnifier follows ChromeVox focus";
const char kAccessibilityMagnifierFollowsChromeVoxDescription[] =
    "This option enables the fullscreen magnifier to follow ChromeVox's focus.";

const char kAccessibilityMouseKeysName[] = "Mouse Keys";
const char kAccessibilityMouseKeysDescription[] =
    "This option enables you to control the mouse with the keyboard.";
=======
const char kMacCoreLocationBackendName[] = "Core Location Backend";
const char kMacCoreLocationBackendDescription[] =
    "Enables usage of the Core Location APIs as the backend for Geolocation "
    "API";
>>>>>>> chromium

const char kNewMacNotificationAPIName[] =
    "Determines which notification API to use on macOS devices";
const char kNewMacNotificationAPIDescription[] =
    "Enables the usage of Apple's new notification API which will run on macOS "
    "10.14+";

const char kNotificationsViaHelperAppName[] = "Notifications via helper app";
const char kNotificationsViaHelperAppDescription[] =
    "Enables the notification helper app to display alerts on macOS instead of "
    "the XPC service";

const char kWinrtGeolocationImplementationName[] =
    "WinRT Geolocation Implementation";
const char kWinrtGeolocationImplementationDescription[] =
    "Enables usage of the Windows.Devices.Geolocation WinRT APIs on Windows "
    "for geolocation";

extern const char kEnableExtendedSyncPromosCapabilityName[] =
    "Enables reading the extended sync promo account capability";
extern const char kEnableExtendedSyncPromosCapabilityDescription[] =
    "When enabled, starts reading the account capability to decide whether "
    "or not Chrome should display an extended sync promo";

const char kEnableFencedFramesName[] = "Enable the <fencedframe> element.";
const char kEnableFencedFramesDescription[] =
    "Fenced frames are an experimental web platform feature that allows "
    "embedding an isolated top-level page. See "
    "https://github.com/shivanigithub/fenced-frame";

const char kEnableGamepadButtonAxisEventsName[] =
    "Gamepad Button and Axis Events";
const char kEnableGamepadButtonAxisEventsDescription[] =
    "Enables the ability to subscribe to changes in buttons and/or axes "
    "on the gamepad object.";

const char kEnableGenericSensorExtraClassesName[] =
    "Generic Sensor Extra Classes";
const char kEnableGenericSensorExtraClassesDescription[] =
    "Enables an extra set of sensor classes based on Generic Sensor API, which "
    "expose previously unavailable platform features, i.e. AmbientLightSensor "
    "and Magnetometer interfaces.";

const char kEnableGpuServiceLoggingName[] = "Enable gpu service logging";
const char kEnableGpuServiceLoggingDescription[] =
    "Enable printing the actual GL driver calls.";

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
const char kEnableIsolatedWebAppsName[] = "Enable Isolated Web Apps";
const char kEnableIsolatedWebAppsDescription[] =
    "Enables experimental support for Isolated Web Apps. "
    "See https://github.com/reillyeon/isolated-web-apps for more information.";

#if BUILDFLAG(IS_CHROMEOS)
const char kEnableIsolatedWebAppUnmanagedInstallName[] =
    "Enable Isolated Web App unmanaged installation";
const char kEnableIsolatedWebAppUnmanagedInstallDescription[] =
    "Enables the installation of Isolated Web Apps on devices that are not "
    "managed by an enterprise.";

const char kEnableIsolatedWebAppManagedGuestSessionInstallName[] =
    "Enable Isolated Web App installation in managed guest sessions";
const char kEnableIsolatedWebAppManagedGuestSessionInstallDescription[] =
    "Enables the installation of Isolated Web Apps for users that are logged "
    "into a managed guest session.";
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
const char kEnableShortcutCustomizationAppName[] =
    "Enable shortcut customization app";
const char kEnableShortcutCustomizationAppDescription[] =
    "Enable the shortcut customization SWA, allowing users to customize system "
    "shortcuts.";

const char kEnableSRPIsolatedPrerendersName[] =
    "Enable Navigation Predictor Isolated Prerenders";
const char kEnableSRPIsolatedPrerendersDescription[] =
    "Enable Navigation Predictions on the Google SRP to be fully isolated.";

const char kEnableSRPIsolatedPrerenderProbingName[] =
    "Enable Probing on Navigation Predictor Isolated Prerenders";
const char kEnableSRPIsolatedPrerenderProbingDescription[] =
    "Enable probing checks for Isolated Prerenders which will block commit.";

const char kEnableSRPIsolatedPrerendersNSPName[] =
    "Enable NoStatePrefetch on Navigation Predictor Isolated Prerenders";
const char kEnableSRPIsolatedPrerendersNSPDescription[] =
    "Enables NoStatePrefetch on Isolated Prerenders.";
>>>>>>> chromium

const char kDownloadAutoResumptionNativeName[] =
    "Enable download auto-resumption in native";
const char kDownloadAutoResumptionNativeDescription[] =
    "Enables download auto-resumption in native";

<<<<<<< HEAD
const char kEnableIwaKeyDistributionComponentName[] =
    "Enable the Iwa Key Distribution component";
const char kEnableIwaKeyDistributionComponentDescription[] =
    "Enables the Iwa Key Distribution component that supplies key rotation "
    "data for Isolated Web Apps.";

const char kIwaKeyDistributionComponentExpCohortName[] =
    "Experimental cohort for the Iwa Key Distribution component";
const char kIwaKeyDistributionComponentExpCohortDescription[] =
    "Specifies the experimental cohort for the Iwa Key Distribution component.";
#endif  // !BUILDFLAG(IS_ANDROID)

const char kEnableControlledFrameName[] = "Enable Controlled Frame";
const char kEnableControlledFrameDescription[] =
    "Enables experimental support for Controlled Frame. See "
    "https://github.com/WICG/controlled-frame/blob/main/EXPLAINER.md "
    "for more information.";

const char kEnableFingerprintingProtectionBlocklistName[] =
    "Enable Fingerprinting Protection Blocklist In Regular Browsing";
const char kEnableFingerprintingProtectionBlocklistDescription[] =
    "Enable Fingerprinting Protection which may block fingerprinting "
    "resources from loading in a 3p context. This flag applies only outside of "
    "Incognito mode.";

const char kEnableFingerprintingProtectionBlocklistInIncognitoName[] =
    "Enable Fingerprinting Protection Blocklist In Incognito";
const char kEnableFingerprintingProtectionBlocklistInIncognitoDescription[] =
    "Enable Fingerprinting Protection which may block fingerprinting "
    "resources from loading in a 3p context. This flag applies only in "
    "Incognito mode.";
=======
const char kDownloadLaterName[] = "Enable download later";
const char kDownloadLaterDescription[] = "Enables download later feature.";

const char kDownloadLaterDebugOnWifiName[] =
    "Show download later dialog on WIFI.";
const char kDownloadLaterDebugOnWifiNameDescription[] =
    "Show download later dialog on WIFI.";

const char kEnableLayoutNGName[] = "Enable LayoutNG";
const char kEnableLayoutNGDescription[] =
    "Enable Blink's next generation layout engine.";
>>>>>>> chromium

const char kEnableLayoutNGTableName[] = "Enable TableNG";
const char kEnableLayoutNGTableDescription[] =
    "Enable Blink's next generation table layout.";

const char kEnableLazyFrameLoadingName[] = "Enable lazy frame loading";
const char kEnableLazyFrameLoadingDescription[] =
    "Defers the loading of iframes marked with the attribute 'loading=lazy' "
    "until the page is scrolled down near them.";

const char kEnableLazyImageLoadingName[] = "Enable lazy image loading";
const char kEnableLazyImageLoadingDescription[] =
    "Defers the loading of images marked with the attribute 'loading=lazy' "
    "until the page is scrolled down near them.";

<<<<<<< HEAD
const char kEnablePeripheralCustomizationName[] =
    "Enable peripheral customization";
const char kEnablePeripheralCustomizationDescription[] =
    "Enable peripheral customization to allow users to customize buttons on "
    "their peripherals.";

const char kEnablePeripheralNotificationName[] =
    "Enable peripheral notification";
const char kEnablePeripheralNotificationDescription[] =
    "Enable peripheral notification to notify users when a input device is "
    "connected to the user's Chromebook for the first time.";

const char kEnablePeripheralsLoggingName[] = "Enable peripherals logging";
const char kEnablePeripheralsLoggingDescription[] =
    "Enable peripherals logging to get detailed logs of peripherals";

const char kExperimentalRgbKeyboardPatternsName[] =
    "Enable experimental RGB Keyboard patterns support";
const char kExperimentalRgbKeyboardPatternsDescription[] =
    "Enable experimental RGB Keyboard patterns support on supported devices.";

const char kClayBlockingDialogName[] = "Clay blocking dialog";
const char kClayBlockingDialogDescription[] =
    "Enables the blocking dialog that directs users to complete their choice "
    "of default apps (for Browser & Search) in Android.";

const char kTemplateUrlReconciliationName[] = "Merge TemplateUrl definitions";
const char kTemplateUrlReconciliationDialogDescription[] =
    "Allows Chrome to reconcile TemplateUrl definitions coming from external "
    "sources with its internal database.";
=======
const char kEnableMediaSessionServiceName[] = "Media Session Service";
const char kEnableMediaSessionServiceDescription[] =
    "Enables the media session mojo service and internal media session "
    "support.";
>>>>>>> chromium

const char kEnableNetworkLoggingToFileName[] = "Enable network logging to file";
const char kEnableNetworkLoggingToFileDescription[] =
    "Enables network logging to a file named netlog.json in the user data "
    "directory. The file can be imported into chrome://net-internals.";

const char kEnableNetworkServiceInProcessName[] =
    "Runs network service in-process";
const char kEnableNetworkServiceInProcessDescription[] =
    "Runs the network service in the browser process.";

<<<<<<< HEAD
const char kEnablePerfettoSystemTracingName[] =
    "Enable Perfetto system tracing";
const char kEnablePerfettoSystemTracingDescription[] =
    "When enabled, Chrome will attempt to connect to the system tracing "
    "service";
=======
const char kEnableNewDownloadBackendName[] = "Enable new download backend";
const char kEnableNewDownloadBackendDescription[] =
    "Enables the new download backend that uses offline content provider";

const char kEnablePortalsName[] = "Enable Portals.";
const char kEnablePortalsDescription[] =
    "Portals are an experimental web platform feature that allows embedding"
    " and seamless transitions between pages."
    " See https://github.com/WICG/portals and https://wicg.github.io/portals/";

const char kEnablePortalsCrossOriginName[] = "Enable cross-origin Portals.";
const char kEnablePortalsCrossOriginDescription[] =
    "Allows portals to load cross-origin URLs in addition to same-origin ones."
    " Has no effect if Portals are not enabled.";

const char kEnableTranslateSubFramesName[] = "Translate sub frames";
const char kEnableTranslateSubFramesDescription[] =
    "Enable the translation of sub frames (as well as the main frame)";

const char kEnableWindowsGamingInputDataFetcherName[] =
    "Enable Windows.Gaming.Input";
const char kEnableWindowsGamingInputDataFetcherDescription[] =
    "Enable Windows.Gaming.Input by default to provide game controller "
    "support on Windows 10 desktop.";
>>>>>>> chromium

const char kEnableWindowsGamingInputDataFetcherName[] =
    "Enable Windows.Gaming.Input";
const char kEnableWindowsGamingInputDataFetcherDescription[] =
    "Enable Windows.Gaming.Input by default to provide game controller "
    "support on Windows 10 desktop.";

const char kBlockInsecurePrivateNetworkRequestsName[] =
    "Block insecure private network requests.";
const char kBlockInsecurePrivateNetworkRequestsDescription[] =
    "Prevents non-secure contexts from making sub-resource requests to "
    "more-private IP addresses. An IP address IP1 is more private than IP2 if "
    "1) IP1 is localhost and IP2 is not, or 2) IP1 is private and IP2 is "
    "public. This is a first step towards full enforcement of CORS-RFC1918: "
    "https://wicg.github.io/cors-rfc1918";

<<<<<<< HEAD
const char kPipDoubleTapToResizeName[] =
    "Enable double-tap to resize PiP windows";
const char kPipDoubleTapToResizeDescription[] =
    "Enables double-tapping on existing PiP windows to resize "
    "them depending on its current state, such as minimizing or maximizing.";

const char kPipTuckName[] = "Enable tuck for PiP windows";
const char kPipTuckDescription[] = "Enables window tucking for PiP windows. ";

const char kPrivacyGuideAiSettingsName[] = "AI settings in Privacy Guide";
const char kPrivacyGuideAiSettingsDescription[] =
    "Enables the AI settings linkout in the Privacy Guide completion card.";

const char kPrivateNetworkAccessRespectPreflightResultsName[] =
    "Respect the result of Private Network Access preflights";
const char kPrivateNetworkAccessRespectPreflightResultsDescription[] =
    "Enables sending Private Network Access preflights ahead of requests to "
    "more-private IP addresses. These preflight requests must succeed in order "
    "for the request to proceed. See also: "
    "https://developer.chrome.com/blog/private-network-access-preflight/";

const char kPrivateNetworkAccessPreflightShortTimeoutName[] =
    "Reduce waiting time for Private Network Access preflights response";
const char kPrivateNetworkAccessPreflightShortTimeoutDescription[] =
    "Reduce the waiting time for Private Network Access preflights to 200 "
    "milliseconds. The default timeout period for requests is 5 minutes. "
    "See also: "
    "https://developer.chrome.com/blog/private-network-access-preflight/";

const char kPrivateNetworkAccessPermissionPromptName[] =
    "Enable Permission Prompt for Private Network Access";
const char kPrivateNetworkAccessPermissionPromptDescription[] =
    "Enable Permission Prompt for HTTPS public websites accessing HTTP "
    "more-private devices. Require to set a fetch option `targetAddressSpace` "
    "on the request to relax mixed content check. "
    "See also: "
    "https://developer.chrome.com/blog/"
    "private-network-access-update-2023-02-02/";

const char kPrivateNetworkAccessIgnoreWorkerErrorsName[] =
    "Ignore Private Network Access errors for worker-related requests";
const char kPrivateNetworkAccessIgnoreWorkerErrorsDescription[] =
    "Ignore Private Network Access errors for worker-related requests, "
    "including worker script fetches, and fetches initiated in a worker. "
    "Instead of blocking the requests, the errors will be shown as an issue in "
    "DevTools. See "
    "also: https://developer.chrome.com/blog/private-network-access-update/ "
    "and https://developer.chrome.com/blog/private-network-access-preflight/";

const char kPrivateNetworkAccessIgnoreNavigationErrorsName[] =
    "Ignore Private Network Access errors for navigation-related requests";
const char kPrivateNetworkAccessIgnoreNavigationErrorsDescription[] =
    "Ignore Private Network Access errors for navigation-related requests, "
    "including iframes and popups. Instead of blocking the requests, the errors"
    "will be shown as an issue in DevTools. See also: "
    "https://developer.chrome.com/blog/private-network-access-update/ "
    "and https://developer.chrome.com/blog/private-network-access-preflight/";
=======
const char kCrossOriginEmbedderPolicyCredentiallessName[] =
    "Enable Cross-Origin-Embedder-Policy: credentialless";
const char kCrossOriginEmbedderPolicyCredentiallessDescription[] =
    "Credentialless is a Cross-Origin-Embedder-Policy (COEP) variant. "
    "COEP:credentialless causes no-cors cross-origin requests not to include "
    "credentials (cookies, client certificates, etc...). Similarly to "
    "require-corp, it can be used to enable cross-origin-isolation.";
>>>>>>> chromium

const char kDeprecateAltClickName[] =
    "Enable Alt+Click deprecation notifications";
const char kDeprecateAltClickDescription[] =
    "Start providing notifications about Alt+Click deprecation and enable "
    "Search+Click as an alternative.";

const char kDeprecateAltBasedSixPackName[] =
    "Deprecate Alt based six-pack (PgUp, PgDn, Home, End, Delete, Insert)";
const char kDeprecateAltBasedSixPackDescription[] =
    "Show deprecation notifications and disable functionality for Alt based "
    "six pack deprecations. The Search based versions continue to work.";

const char kDiagnosticsAppName[] = "Diagnostics app";
const char kDiagnosticsAppDescription[] =
    "Enables the Diagnostics app that allows Chrome OS users to be able to "
    "view their system telemetric information and run diagnostic tests for "
    "their device.";

const char kDiagnosticsAppNavigationName[] = "Diagnostics app navigation";
const char kDiagnosticsAppNavigationDescription[] =
    "Enables the navigation panel in the Diagnostics app.";

const char kDisableKeepaliveFetchName[] = "Disable fetch with keepalive set";
const char kDisableKeepaliveFetchDescription[] =
    "Disable fetch with keepalive set "
    "(https://fetch.spec.whatwg.org/#request-keepalive-flag).";

const char kExperimentalAccessibilityLanguageDetectionName[] =
    "Experimental accessibility language detection";
const char kExperimentalAccessibilityLanguageDetectionDescription[] =
    "Enable language detection for in-page content which is then exposed to "
    "assistive technologies such as screen readers.";

const char kExperimentalAccessibilityLanguageDetectionDynamicName[] =
    "Experimental accessibility language detection for dynamic content";
const char kExperimentalAccessibilityLanguageDetectionDynamicDescription[] =
    "Enable language detection for dynamic content which is then exposed to "
    "assistive technologies such as screen readers.";

const char kCompositorThreadedScrollbarScrollingName[] =
    "Compositor threaded scrollbar scrolling";
const char kCompositorThreadedScrollbarScrollingDescription[] =
    "Enables pointer-based scrollbar scrolling on the compositor thread "
    "instead of the main thread";

const char kMemlogName[] = "Chrome heap profiler start mode.";
const char kMemlogDescription[] =
    "Starts heap profiling service that records sampled memory allocation "
    "profile having each sample attributed with a callstack. "
    "The sampling resolution is controlled with --memlog-sampling-rate flag. "
    "Recorded heap dumps can be obtained at chrome://tracing "
    "[category:memory-infra] and chrome://memory-internals. This setting "
    "controls which processes will be profiled since their start. To profile "
    "any given process at a later time use chrome://memory-internals page.";
const char kMemlogModeMinimal[] = "Browser and GPU";
const char kMemlogModeAll[] = "All processes";
const char kMemlogModeAllRenderers[] = "All renderers";
const char kMemlogModeRendererSampling[] = "Single renderer";
const char kMemlogModeBrowser[] = "Browser only";
const char kMemlogModeGpu[] = "GPU only";

const char kMemlogSamplingRateName[] =
    "Heap profiling sampling interval (in bytes).";
const char kMemlogSamplingRateDescription[] =
    "Heap profiling service uses Poisson process to sample allocations. "
    "Default value for the interval between samples is 100000 (100KB). "
    "This results in low noise for large and/or frequent allocations "
    "[size * frequency >> 100KB]. This means that aggregate numbers [e.g. "
    "total size of malloc-ed objects] and large and/or frequent allocations "
    "can be trusted with high fidelity. "
    "Lower intervals produce higher samples resolution, but come at a cost of "
    "higher performance overhead.";
const char kMemlogSamplingRate10KB[] = "10KB";
const char kMemlogSamplingRate50KB[] = "50KB";
const char kMemlogSamplingRate100KB[] = "100KB";
const char kMemlogSamplingRate500KB[] = "500KB";
const char kMemlogSamplingRate1MB[] = "1MB";
const char kMemlogSamplingRate5MB[] = "5MB";

const char kMemlogStackModeName[] = "Heap profiling stack traces type.";
const char kMemlogStackModeDescription[] =
    "By default heap profiling service records native stacks. "
    "A post-processing step is required to symbolize the stacks. "
    "'Native with thread names' adds the thread name as the first frame of "
    "each native stack. It's also possible to record a pseudo stack using "
    "trace events as identifiers. It's also possible to do a mix of both.";
const char kMemlogStackModeMixed[] = "Mixed";
const char kMemlogStackModeNative[] = "Native";
const char kMemlogStackModeNativeWithThreadNames[] = "Native with thread names";
const char kMemlogStackModePseudo[] = "Trace events";

const char kEnableLensRegionSearchFlagId[] = "enable-lens-region-search";
const char kEnableLensRegionSearchName[] =
    "Search your screen with Google Lens";
const char kEnableLensRegionSearchDescription[] =
    "Right click and select \"Search part of the page with Google Lens\" to "
    "search any region of the site to learn more about the visual content you "
    "see while you browse and shop on the web.";

<<<<<<< HEAD
const char kEnableLazyLoadImageForInvisiblePageName[] =
    "Enable lazy load image for invisible page";
const char kEnableLazyLoadImageForInvisiblePageDescription[] =
    "Respect the loading = lazy attribute for images even on invisible pages.";

const char kEnableLensStandaloneFlagId[] = "enable-lens-standalone";
const char kEnableLensStandaloneName[] = "Enable Lens features in Chrome.";
const char kEnableLensStandaloneDescription[] =
    "Enables Lens image and region search to learn about the visual content "
    "you see while you browse and shop on the web.";
=======
const char kEnableLoginDetectionName[] = "Enable login detection";
const char kEnableLoginDetectionDescription[] =
    "Allow user sign-in to be detected based on heuristics.";
>>>>>>> chromium

const char kEnableManagedConfigurationWebApiName[] =
    "Enable Managed Configuration Web API";
const char kEnableManagedConfigurationWebApiDescription[] =
    "Allows website to access a managed configuration provided by the device "
    "administrator for the origin.";

const char kEnablePciguardUiName[] =
    "Enable Pciguard (Thunderbolt + USB4 tunneling) UI for settings";
const char kEnablePciguardUiDescription[] =
    "Enable toggling Pciguard settings through the Settings App. By default, "
    "this flag is enabled.";

const char kEnablePenetratingImageSelectionName[] =
    "Penetrating Image Selection";
const char kEnablePenetratingImageSelectionDescription[] =
    "Enables image options to be surfaced in the context menu for nodes "
    "covered by transparent overlays.";

const char kEnablePixelCanvasRecordingName[] = "Enable pixel canvas recording";
const char kEnablePixelCanvasRecordingDescription[] =
    "Pixel canvas recording allows the compositor to raster contents aligned "
    "with the pixel and improves text rendering. This should be enabled when a "
    "device is using fractional scale factor.";

const char kReduceHorizontalFlingVelocityName[] =
    "Reduce horizontal fling velocity";
const char kReduceHorizontalFlingVelocityDescription[] =
    "Reduces the velocity of horizontal flings to 20\% of their original"
    "velocity.";

const char kEnableResamplingInputEventsName[] =
    "Enable resampling input events";
const char kEnableResamplingInputEventsDescription[] =
    "Predicts mouse and touch inputs position at rAF time based on previous "
    "input";
const char kEnableResamplingScrollEventsName[] =
    "Enable resampling scroll events";
const char kEnableResamplingScrollEventsDescription[] =
    "Predicts the scroll amount at vsync time based on previous input";
const char kEnableResamplingScrollEventsExperimentalPredictionName[] =
    "Enable experimental prediction for scroll events";
const char kEnableResamplingScrollEventsExperimentalPredictionDescription[] =
    "Predicts the scroll amount after the vsync time to more closely match "
    "when the frame is visible.";

<<<<<<< HEAD
const char kEnableSystemEntropyOnPerformanceNavigationTimingName[] =
    "Enable the systemEntropy property on PerformanceNavigationTiming";
const char kEnableSystemEntropyOnPerformanceNavigationTimingDescription[] =
    "Allows developers to discern if the top level navigation occurred "
    "while the user agent was under load. See "
    "https://chromestatus.com/feature/5186950448283648 for more information.";
=======
const char kEnableRestrictedWebApisName[] =
    "Enable the restriced web APIs for high-trusted apps.";
const char kEnableRestrictedWebApisDescription[] =
    "Enable the restricted web APIs for dev trial. This will be replaced with "
    "permission policies to control the capabilities afterwards.";
>>>>>>> chromium

const char kEnableUseZoomForDsfName[] =
    "Use Blink's zoom for device scale factor.";
const char kEnableUseZoomForDsfDescription[] =
    "If enabled, Blink uses its zooming mechanism to scale content for device "
    "scale factor.";
const char kEnableUseZoomForDsfChoiceDefault[] = "Default";
const char kEnableUseZoomForDsfChoiceEnabled[] = "Enabled";
const char kEnableUseZoomForDsfChoiceDisabled[] = "Disabled";

const char kEnableSubresourceRedirectName[] =
    "Enable Subresource Redirect Compression";
const char kEnableSubresourceRedirectDescription[] =
    "Allow subresource compression for data savings";

const char kEnableWebAuthenticationCableV2SupportName[] =
    "Web Authentication caBLE v2 support";
const char kEnableWebAuthenticationCableV2SupportDescription[] =
    "Enable use of phones that are signed into the same account, with Sync "
    "enabled, to be used as 2nd-factor security keys.";

const char kEnableWebAuthenticationChromeOSAuthenticatorName[] =
    "ChromeOS platform Web Authentication support";
const char kEnableWebAuthenticationChromeOSAuthenticatorDescription[] =
    "Enable the ChromeOS platform authenticator for the Web Authentication "
    "API.";

const char kExperimentalWebAssemblyFeaturesName[] = "Experimental WebAssembly";
const char kExperimentalWebAssemblyFeaturesDescription[] =
    "Enable web pages to use experimental WebAssembly features.";

const char kEnableWasmBaselineName[] = "WebAssembly baseline compiler";
const char kEnableWasmBaselineDescription[] =
    "Enables WebAssembly baseline compilation and tier up.";

const char kEnableWasmLazyCompilationName[] = "WebAssembly lazy compilation";
const char kEnableWasmLazyCompilationDescription[] =
    "Enables lazy (JIT on first call) compilation of WebAssembly modules.";

const char kEnableWasmSimdName[] = "WebAssembly SIMD support.";
const char kEnableWasmSimdDescription[] =
    "Enables support for the WebAssembly SIMD proposal.";

const char kEnableWasmTieringName[] = "WebAssembly tiering";
const char kEnableWasmTieringDescription[] =
    "Enables tiered compilation of WebAssembly (will tier up to TurboFan if "
    "#enable-webassembly-baseline is enabled).";

<<<<<<< HEAD
=======
const char kEvDetailsInPageInfoName[] = "EV certificate details in Page Info.";
const char kEvDetailsInPageInfoDescription[] =
    "Shows the EV certificate details in the Page Info bubble.";

const char kExpensiveBackgroundTimerThrottlingName[] =
    "Throttle expensive background timers";
const char kExpensiveBackgroundTimerThrottlingDescription[] =
    "Enables intervention to limit CPU usage of background timers to 1%.";

const char kExperimentalAccessibilityLabelsName[] =
    "Experimental Accessibility Labels";
const char kExperimentalAccessibilityLabelsDescription[] =
    "Enables experimental accessibility labels feature. Note that this only "
    "enables the feature, and enabling the service is a profile preference.";

>>>>>>> chromium
const char kExperimentalWebPlatformFeaturesName[] =
    "Experimental Web Platform features";
const char kExperimentalWebPlatformFeaturesDescription[] =
    "Enables experimental Web Platform features that are in development.";

<<<<<<< HEAD
const char kSafeBrowsingLocalListsUseSBv5Name[] =
    "Safe Browsing Local Lists use v5 API";
const char kSafeBrowsingLocalListsUseSBv5Description[] =
    "Fetch and check local lists using the Safe Browsing v5 API instead of the "
    "v4 Update API.";

#if BUILDFLAG(ENABLE_EXTENSIONS)
const char kEnableWebHidInWebViewName[] = "Web HID in WebView";
const char kEnableWebHidInWebViewDescription[] =
    "Enable WebViews to access Web HID upon embedder's permission.";

const char kExperimentalOmniboxLabsName[] =
    "Enable extension permission omnibox.directInput";
const char kExperimentalOmniboxLabsDescription[] =
    "Allows extensions to request permission omnibox.directInput, which "
    "enables unscoped mode in the Omnibox";
const char kExtensionAiDataCollectionName[] =
    "Enables AI Data collection via extension";
const char kExtensionAiDataCollectionDescription[] =
    "Enables an extension API to allow specific extensions to collect data "
    "from browser process. This data may contain profile specific information "
    " and may be otherwise unavailable to an extension.";
const char kExtensionsMenuAccessControlName[] =
    "Extensions Menu Access Control";
const char kExtensionsMenuAccessControlDescription[] =
    "Enables a redesigned extensions menu that allows the user to control "
    "extensions site access.";
const char kIPHExtensionsMenuFeatureName[] = "IPH Extensions Menu";
const char kIPHExtensionsMenuFeatureDescription[] =
    "Enables In-Product-Help that appears when at least one extension has "
    "access to the current page. This feature is gated by "
    "extensions-menu-access-control.";
const char kIPHExtensionsRequestAccessButtonFeatureName[] =
    "IPH Extensions Request Access Button Feature";
const char kIPHExtensionsRequestAccessButtonFeatureDescription[] =
    "Enables In-Product-Help that appears when at least one extension is "
    "requesting access to the current page. This feature is gated by "
    "extensions-menu-access-control.";
const char kExtensionManifestV2DeprecationWarningName[] =
    "Extension Manifest V2 Deprecation Warning Stage";
const char kExtensionManifestV2DeprecationWarningDescription[] =
    "Displays a warning that affected MV2 extensions may no longer be "
    "supported due to the Manifest V2 deprecation.";
const char kExtensionManifestV2DeprecationDisabledName[] =
    "Extension Manifest V2 Deprecation Disabled Stage";
const char kExtensionManifestV2DeprecationDisabledDescription[] =
    "Displays a warning that affected MV2 extensions were turned off due to "
    "the Manifest V2 deprecation.";
const char kExtensionManifestV2DeprecationUnsupportedName[] =
    "Extension Manifest V2 Deprecation Unsupported Stage";
const char kExtensionManifestV2DeprecationUnsupportedDescription[] =
    "Displays a warning that affected MV2 extensions were turned off due to "
    "the Manifest V2 deprecation and cannot be re-enabled.";

const char kWebAuthFlowInBrowserTabName[] =
    "Web Authentication Flow in Browser Tab";
const char kWebAuthFlowInBrowserTabDescription[] =
    "Web authentication flows to be displayed in a Browser Tab instead of an "
    "App Window. The flows are used via the Chrome Extension API, using "
    "`chrome.identity` functions. Browser Tab can be displayed either in a New "
    "Tab or a Popup Window via the feature parameters.";

const char kCWSInfoFastCheckName[] = "CWS Info Fast Check";
const char kCWSInfoFastCheckDescription[] =
    "When enabled, Chrome checks and fetches metadata for installed extensions "
    "more frequently.";

const char kExtensionDisableUnsupportedDeveloperName[] =
    "Extension Disable Unsupported Developer";
const char kExtensionDisableUnsupportedDeveloperDescription[] =
    "When enabled, disable unpacked extensions if developer mode is off.";

const char kExtensionTelemetryForEnterpriseName[] =
    "Extension Telemetry for Enterprise";
const char kExtensionTelemetryForEnterpriseDescription[] =
    "When enabled, the extension telemetry service collects signals and "
    "generates reports to send for enterprise.";

const char kExtensionsToolbarZeroStateName[] = "Extensions Toolbar Zero State";
const char kExtensionsToolbarZeroStateDescription[] =
    "When enabled, show an IPH to prompt users with zero extensions installed "
    "to interact with the Extensions Toolbar Button. Upon the user clicking "
    "the toolbar button, display a submenu that suggests exploring the Chrome "
    "Web Store.";
const char kExtensionsToolbarZeroStateChoicesDisabled[] = "Disabled";
const char kExtensionsToolbarZeroStateVistWebStore[] = "Visit Chrome Web Store";
const char kExtensionsToolbarZeroStateExploreExtensionsByCategory[] =
    "Explore CWS extensions by category";

#if BUILDFLAG(IS_CHROMEOS)
const char kExtensionWebFileHandlersName[] = "Extensions Web File Handlers";
const char kExtensionWebFileHandlersDescription[] =
    "Enable Extension Web File Handlers, which allows extensions to operate on "
    "the native file system. An extension can register to read and edit files, "
    "specified in the manifest, by their file extension or mime type.";
#endif  // BUILDFLAG(IS_CHROMEOS)
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)
=======
const char kExtensionContentVerificationName[] =
    "Extension Content Verification";
const char kExtensionContentVerificationDescription[] =
    "This flag can be used to turn on verification that the contents of the "
    "files on disk for extensions from the webstore match what they're "
    "expected to be. This can be used to turn on this feature if it would not "
    "otherwise have been turned on, but cannot be used to turn it off (because "
    "this setting can be tampered with by malware).";
const char kExtensionContentVerificationBootstrap[] =
    "Bootstrap (get expected hashes, but do not enforce them)";
const char kExtensionContentVerificationEnforce[] =
    "Enforce (try to get hashes, and enforce them if successful)";
const char kExtensionContentVerificationEnforceStrict[] =
    "Enforce strict (hard fail if we can't get hashes)";
>>>>>>> chromium

const char kExtensionsOnChromeUrlsName[] = "Extensions on chrome:// URLs";
const char kExtensionsOnChromeUrlsDescription[] =
    "Enables running extensions on chrome:// URLs, where extensions explicitly "
    "request this permission.";

const char kFilteringScrollPredictionName[] = "Filtering scroll prediction";
const char kFilteringScrollPredictionDescription[] =
    "Enable filtering of predicted scroll events";

const char kFractionalScrollOffsetsName[] = "Fractional Scroll Offsets";
const char kFractionalScrollOffsetsDescription[] =
    "Enables fractional scroll offsets inside Blink, exposing non-integer "
    "offsets to web APIs.";

const char kForceEffectiveConnectionTypeName[] =
    "Override effective connection type";
const char kForceEffectiveConnectionTypeDescription[] =
    "Overrides the effective connection type of the current connection "
    "returned by the network quality estimator. Slow 2G on Cellular returns "
    "Slow 2G when connected to a cellular network, and the actual estimate "
    "effective connection type when not on a cellular network.";
const char kEffectiveConnectionTypeUnknownDescription[] = "Unknown";
const char kEffectiveConnectionTypeOfflineDescription[] = "Offline";
const char kEffectiveConnectionTypeSlow2GDescription[] = "Slow 2G";
const char kEffectiveConnectionTypeSlow2GOnCellularDescription[] =
    "Slow 2G On Cellular";
const char kEffectiveConnectionType2GDescription[] = "2G";
const char kEffectiveConnectionType3GDescription[] = "3G";
const char kEffectiveConnectionType4GDescription[] = "4G";

<<<<<<< HEAD
const char kFedCmButtonModeName[] = "FedCmButtonMode";
const char kFedCmButtonModeDescription[] =
    "Enables RPs specify whether they want to trigger the FedCM widget flow or "
    "the button flow.";

const char kFedCmDelegationName[] = "FedCM with delegation support";
const char kFedCmDelegationDescription[] =
    "Enables IdPs to delegate presentation to the browser.";

const char kFedCmIdPRegistrationName[] = "FedCM with IdP Registration support";
const char kFedCmIdPRegistrationDescription[] =
    "Enables RPs to get identity credentials from registered IdPs.";

const char kFedCmMetricsEndpointName[] = "FedCmMetricsEndpoint";
const char kFedCmMetricsEndpointDescription[] =
    "Allows the FedCM API to send performance measurement to the metrics "
    "endpoint on the identity provider side. Requires FedCM to be enabled.";

const char kFedCmLightweightModeName[] = "FedCmLightweightMode";
const char kFedCmLightweightModeDescription[] =
    "Enables IdPs to store user profile information using the login status "
    "API.";

const char kFedCmMultiIdpName[] = "FedCmMultiIdp";
const char kFedCmMultiIdpDescription[] =
    "Allows the FedCM API to request multiple identity providers "
    "simultaneously. Requires FedCM to be enabled as well.";

const char kFedCmSelectiveDisclosureName[] = "FedCmSelectiveDisclosure";
const char kFedCmSelectiveDisclosureDescription[] =
    "Allows a relying party to selectively request a set of identity "
    "attributes to be disclosed.";

const char kFedCmShowFilteredAccountsName[] = "FedCmShowFilteredAccounts";
const char kFedCmShowFilteredAccountsDescription[] =
    "Allows the FedCM API to show filtered accounts greyed out.";

const char kFedCmWithStorageAccessAPIName[] = "FedCmWithStorageAccessAPI";
const char kFedCmWithStorageAccessAPIDescription[] =
    "Allows Storage Access API to auto-resolve if the user has allowed a FedCM "
    "connection.";

const char kFedCmWithoutWellKnownEnforcementName[] =
    "FedCmWithoutWellKnownEnforcement";
const char kFedCmWithoutWellKnownEnforcementDescription[] =
    "Supports configURL that's not in the IdP's .well-known file.";

const char kFedCmUseOtherAccountName[] = "FedCmUseOtherAccount";
const char kFedCmUseOtherAccountDescription[] =
    "Enables the \"Use a different account\" button on the FedCM account "
    "chooser to log in to another IdP account, for IdPs who have opted in.";

const char kWebIdentityDigitalCredentialsName[] = "DigitalCredentials";
const char kWebIdentityDigitalCredentialsDescription[] =
    "Enables the three-party verifier/holder/issuer identity model.";
=======
const char kFileHandlingAPIName[] = "File Handling API";
const char kFileHandlingAPIDescription[] =
    "Enables the file handling API, allowing websites to register as file "
    "handlers.";
>>>>>>> chromium

const char kWebIdentityDigitalCredentialsCreationName[] =
    "DigitalCredentialsCreation";
const char kWebIdentityDigitalCredentialsCreationDescription[] =
    "Enables the Digital Credentials Creation API.";

const char kFileHandlingIconsName[] = "File Handling Icons";
const char kFileHandlingIconsDescription[] =
    "Allows websites using the file handling API to also register file type "
    "icons. See https://github.com/WICG/file-handling/blob/main/explainer.md "
    "for more information.";

const char kFillingAcrossAffiliatedWebsitesName[] =
    "Fill passwords across affiliated websites.";
const char kFillingAcrossAffiliatedWebsitesDescription[] =
    "Enables filling password on a website when there is saved "
    "password on affiliated website.";

const char kFillOnAccountSelectName[] = "Fill passwords on account selection";
const char kFillOnAccountSelectDescription[] =
    "Filling of passwords when an account is explicitly selected by the user "
    "rather than autofilling credentials on page load.";

const char kForceTextDirectionName[] = "Force text direction";
const char kForceTextDirectionDescription[] =
    "Explicitly force the per-character directionality of UI text to "
    "left-to-right (LTR) or right-to-left (RTL) mode, overriding the default "
    "direction of the character language.";
const char kForceDirectionLtr[] = "Left-to-right";
const char kForceDirectionRtl[] = "Right-to-left";

const char kForceUiDirectionName[] = "Force UI direction";
const char kForceUiDirectionDescription[] =
    "Explicitly force the UI to left-to-right (LTR) or right-to-left (RTL) "
    "mode, overriding the default direction of the UI language.";

const char kGlobalMediaControlsName[] = "Global Media Controls";
const char kGlobalMediaControlsDescription[] =
    "Enables the Global Media Controls UI in the toolbar.";

const char kGlobalMediaControlsForCastName[] = "Global Media Controls for Cast";
const char kGlobalMediaControlsForCastDescription[] =
    "Shows Cast sessions in the Global Media Controls UI. Requires "
    "#global-media-controls and #cast-media-route-provider to also be enabled.";

const char kGlobalMediaControlsForChromeOSName[] =
    "Global Media Controls for ChromeOS";
const char kGlobalMediaControlsForChromeOSDescription[] =
    "Enable Global Media Controls UI in shelf and quick settings.";

const char kGlobalMediaControlsPictureInPictureName[] =
    "Global Media Controls Picture-in-Picture";
const char kGlobalMediaControlsPictureInPictureDescription[] =
    "Enables Picture-in-Picture controls in the Global Media Controls UI. "
    "Requires "
    "#global-media-controls to also be enabled.";

const char kGlobalMediaControlsSeamlessTransferName[] =
    "Global Media Controls Seamless Transfer";
const char kGlobalMediaControlsSeamlessTransferDescription[] =
    "Enables selection of audio output device to play media through in "
    "the Global Media Controls UI. Requires #global-media-controls to "
    "also be enabled.";

const char kGlobalMediaControlsModernUIName[] =
    "Global Media Controls Modern UI";

const char kGlobalMediaControlsModernUIDescription[] =
    "Use a redesigned version of the Global Media Controls UI. Requires "
    "#global-media-controls to also be enabled.";

const char kGlobalMediaControlsOverlayControlsName[] =
    "Enable overlay controls for Global Media Controls";
const char kGlobalMediaControlsOverlayControlsDescription[] =
    "Allowing controls to be dragged out from Global Media Controls dialog. "
    "Requires #global-media-controls to also be enabled.";

<<<<<<< HEAD
const char kCastStreamingAv1Name[] =
    "Enable AV1 video encoding for Cast Streaming";
const char kCastStreamingAv1Description[] =
    "Offers the AV1 video codec when negotiating Cast Streaming, and uses AV1 "
    "if selected for the session.";

const char kCastStreamingHardwareH264Name[] =
    "Toggle hardware accelerated H.264 video encoding for Cast Streaming";
const char kCastStreamingHardwareH264Description[] =
    "The default is to allow hardware H.264 encoding when recommended for the "
    "platform. If enabled, hardware H.264 encoding will always be allowed when "
    "supported by the platform. If disabled, hardware H.264 encoding will "
    "never be used.";

const char kCastStreamingHardwareVp8Name[] =
    "Toggle hardware accelerated VP8 video encoding for Cast Streaming";
const char kCastStreamingHardwareVp8Description[] =
    "The default is to allow hardware VP8 encoding when recommended for the "
    "platform. If enabled, hardware VP8 encoding will always be allowed when "
    "supported by the platform (regardless of recommendation). If disabled, "
    "hardware VP8 encoding will never be used.";

const char kCastStreamingHardwareVp9Name[] =
    "Toggle hardware accelerated VP9 video encoding for Cast Streaming";
const char kCastStreamingHardwareVp9Description[] =
    "The default is to allow hardware VP9 encoding when recommended for the "
    "platform. If enabled, hardware VP9 encoding will always be allowed when "
    "supported by the platform (regardless of recommendation). If disabled, "
    "hardware VP9 encoding will never be used.";

const char kCastStreamingMediaVideoEncoderName[] =
    "Toggles using the media::VideoEncoder implementation for Cast Streaming";
const char kCastStreamingMediaVideoEncoderDescription[] =
    "When enabled, the media base VideoEncoder implementation is used instead "
    "of the media cast implementation.";

const char kCastStreamingPerformanceOverlayName[] =
    "Toggle a performance metrics overlay while Cast Streaming";
const char kCastStreamingPerformanceOverlayDescription[] =
    "When enabled, a text overlay is rendered on top of each frame sent while "
    "Cast Streaming that includes frame duration, resolution, timestamp, "
    "low latency mode, capture duration, target playout delay, target bitrate, "
    "and encoder utilization.";

const char kCastStreamingVp8Name[] =
    "Enable VP8 video encoding for Cast Streaming";
const char kCastStreamingVp8Description[] =
    "Offers the VP8 video codec when negotiating Cast Streaming, and uses VP8 "
    "if selected for the session. If true, software VP8 encoding will be "
    "offered and hardware VP8 encoding may be offered if enabled and available "
    "on this platform. If false, software VP8 will not be offered and hardware "
    "VP8 will only be offered if #cast-streaming-hardware-vp8 is explicitly "
    "set to true.";

const char kCastStreamingVp9Name[] =
    "Enable VP9 video encoding for Cast Streaming";
const char kCastStreamingVp9Description[] =
    "Offers the VP9 video codec when negotiating Cast Streaming, and uses VP9 "
    "if selected for the session.";

#if BUILDFLAG(IS_MAC)
const char kCastStreamingMacHardwareH264Name[] =
    "Enable hardware H264 video encoding on for Cast Streaming on macOS";
const char kCastStreamingMacHardwareH264Description[] =
    "Offers the H264 video codec when negotiating Cast Streaming, and uses "
    "hardware-accelerated H264 encoding if selected for the session";
const char kUseNetworkFrameworkForLocalDiscoveryName[] =
    "Use the Network Framework for local device discovery on Mac";
const char kUseNetworkFrameworkForLocalDiscoveryDescription[] =
    "Use the Network Framework to replace the Bonjour API for local device "
    "discovery on Mac.";
#endif

#if BUILDFLAG(IS_WIN)
const char kCastStreamingWinHardwareH264Name[] =
    "Enable hardware H264 video encoding on for Cast Streaming on Windows";
const char kCastStreamingWinHardwareH264Description[] =
    "Offers the H264 video codec when negotiating Cast Streaming, and uses "
    "hardware-accelerated H264 encoding if selected for the session";
#endif

const char kCastEnableStreamingWithHiDPIName[] =
    "HiDPI tab capture support for Cast Streaming";
const char kCastEnableStreamingWithHiDPIDescription[] =
    "Enables HiDPI tab capture during Cast Streaming mirroring sessions. May "
    "reduce performance on some platforms and also improve quality of video "
    "frames.";

#if BUILDFLAG(IS_CHROMEOS)
const char kFlexFirmwareUpdateName[] = "ChromeOS Flex Firmware Updates";
const char kFlexFirmwareUpdateDescription[] =
    "Allow firmware updates from LVFS to be installed on ChromeOS Flex.";
#endif
=======
const char kGoogleLensSdkIntentName[] =
    "Enable the use of the Lens SDK when starting intent into Lens.";
const char kGoogleLensSdkIntentDescription[] =
    "Starts Lens using the Lens SDK if supported.";
>>>>>>> chromium

const char kGpuRasterizationName[] = "GPU rasterization";
const char kGpuRasterizationDescription[] = "Use GPU to rasterize web content.";

const char kHandwritingGestureEditingName[] = "Handwriting Gestures Editing";
const char kHandwritingGestureEditingDescription[] =
    "Enables editing with handwriting gestures within the virtual keyboard.";

const char kHappyEyeballsV3Name[] = "Happy Eyeballs Version 3";
const char kHappyEyeballsV3Description[] =
    "Enables the Happy Eyeballs Version 3 algorithm. See "
    "https://datatracker.ietf.org/doc/draft-pauly-v6ops-happy-eyeballs-v3/";

const char kHardwareMediaKeyHandling[] = "Hardware Media Key Handling";
const char kHardwareMediaKeyHandlingDescription[] =
    "Enables using media keys to control the active media session. This "
    "requires MediaSessionService to be enabled too";

const char kHeavyAdPrivacyMitigationsName[] = "Heavy ad privacy mitigations";
const char kHeavyAdPrivacyMitigationsDescription[] =
    "Enables privacy mitigations for the heavy ad intervention. Disabling "
    "this makes the intervention deterministic. Defaults to enabled.";

const char kHeavyAdInterventionName[] = "Heavy Ad Intervention";
const char kHeavyAdInterventionDescription[] =
    "Unloads ads that use too many device resources.";

const char kHideShelfControlsInTabletModeName[] =
    "Hide shelf control buttons in tablet mode.";

const char kHideShelfControlsInTabletModeDescription[] =
    "Hides home, back, and overview button from the shelf while the device is "
    "in tablet mode. Predicated on shelf-hotseat feature being enabled.";

<<<<<<< HEAD
const char kCrasProcessorWavDumpName[] = "Enable CrasProcessor WAVE file dumps";
const char kCrasProcessorWavDumpDescription[] =
    "Make CrasProcessor produce WAVE file dumps for the audio processing "
    "pipeline";
=======
const char kTabSwitcherOnReturnName[] = "Tab switcher on return";
const char kTabSwitcherOnReturnDescription[] =
    "Enable tab switcher on return after specified time has elapsed";

const char kHostedAppShimCreationName[] =
    "Creation of app shims for hosted apps on Mac";
const char kHostedAppShimCreationDescription[] =
    "Create app shims on Mac when creating a hosted app.";
>>>>>>> chromium

const char kHttpsOnlyModeName[] = "HTTPS-Only Mode Setting";
const char kHttpsOnlyModeDescription[] =
    "Adds a setting under chrome://settings/security to opt-in to HTTPS-Only "
    "Mode.";

const char kIgnoreGpuBlocklistName[] = "Override software rendering list";
const char kIgnoreGpuBlocklistDescription[] =
    "Overrides the built-in software rendering list and enables "
    "GPU-acceleration on unsupported system configurations.";

<<<<<<< HEAD
const char kIncrementLocalSurfaceIdForMainframeSameDocNavigationName[] =
    "Increments LocalSurfaceId for main-frame same-doc navigations";
const char kIncrementLocalSurfaceIdForMainframeSameDocNavigationDescription[] =
    "If enabled, every same-document navigations in the main-frame will also "
    "increment the LocalSurfaceId.";
=======
const char kImprovedCookieControlsName[] =
    "Enable improved cookie controls UI in incognito mode";
const char kImprovedCookieControlsDescription[] =
    "Improved UI in Incognito mode for third-party cookie blocking.";

const char kImprovedCookieControlsForThirdPartyCookieBlockingName[] =
    "Enable improved UI for third-party cookie blocking";
const char kImprovedCookieControlsForThirdPartyCookieBlockingDescription[] =
    "Enables an improved UI for existing third-party cookie blocking users.";

const char kImprovedKeyboardShortcutsName[] =
    "Enable improved keyboard shortcuts";
const char kImprovedKeyboardShortcutsDescription[] =
    "Ensure keyboard shortcuts work consistently with international keyboard "
    "layouts and deprecate legacy shortcuts.";

const char kImpulseScrollAnimationsName[] = "Impulse-style scroll animations";
const char kImpulseScrollAnimationsDescription[] =
    "Replaces the default scroll animation with Impulse-style scroll "
    "animations.";

const char kIncognitoBrandConsistencyForAndroidName[] =
    "Enable Incognito brand consistency in Android.";
const char kIncognitoBrandConsistencyForAndroidDescription[] =
    "When enabled, keeps Incognito UI consistent regardless of any selected "
    "theme.";

const char kIncognitoBrandConsistencyForDesktopName[] =
    "Enable Incognito brand consistency in desktop.";
const char kIncognitoBrandConsistencyForDesktopDescription[] =
    "When enabled, removes any theme or background customization done by the "
    "user on the Incognito UI.";

const char kIncognitoClearBrowsingDataDialogForDesktopName[] =
    "Enable clear browsing data dialog in Incognito.";
const char kIncognitoClearBrowsingDataDialogForDesktopDescription[] =
    "When enabled, clear browsing data option would be enabled in Incognito "
    "which upon clicking would show a dialog to close all Incognito windows.";

const char kUpdateHistoryEntryPointsInIncognitoName[] =
    "Update history entry points in Incognito.";
const char kUpdateHistoryEntryPointsInIncognitoDescription[] =
    "When enabled, the entry points to history UI from Incognito mode will be "
    "removed for iOS and Desktop. An educative placeholder will be shown for "
    "Android history page.";
>>>>>>> chromium

const char kIncognitoScreenshotName[] = "Incognito Screenshot";
const char kIncognitoScreenshotDescription[] =
    "Enables Incognito screenshots on Android. It will also make Incognito "
    "thumbnails visible.";

const char kInheritNativeThemeFromParentWidgetName[] =
    "Allow widgets to inherit native theme from its parent widget.";
const char kInheritNativeThemeFromParentWidgetDescription[] =
    "When enabled, secondary UI like menu, dialog etc would be in dark mode "
    "when Incognito mode is open.";

const char kInProductHelpDemoModeChoiceName[] = "In-Product Help Demo Mode";
const char kInProductHelpDemoModeChoiceDescription[] =
    "Selects the In-Product Help demo mode.";

const char kInstalledAppsInCbdName[] = "Installed Apps in Clear Browsing Data";
const char kInstalledAppsInCbdDescription[] =
    "Adds the installed apps warning dialog to the clear browsing data flow "
    "which allows users to protect installed apps' data from being deleted.";

const char kJavascriptHarmonyName[] = "Experimental JavaScript";
const char kJavascriptHarmonyDescription[] =
    "Enable web pages to use experimental JavaScript features.";

const char kJavascriptHarmonyShippingName[] =
    "Latest stable JavaScript features";
const char kJavascriptHarmonyShippingDescription[] =
    "Some web pages use legacy or non-standard JavaScript extensions that may "
    "conflict with the latest JavaScript features. This flag allows disabling "
    "support of those features for compatibility with such pages.";

const char kLegacyTLSEnforcedName[] =
    "Enforce deprecation of legacy TLS versions";
const char kLegacyTLSEnforcedDescription[] =
    "Enable connection errors and interstitials for sites that use legacy TLS "
    "versions (TLS 1.0 and TLS 1.1), which are deprecated and will be removed "
    " in the future.";

<<<<<<< HEAD
const char kJumpStartOmniboxName[] = "Jump-start Omnibox";
const char kJumpStartOmniboxDescription[] =
    "Modifies cold- and warm start-up "
    "process on low-end devices to reduce the time to active Omnibox, while "
    "completing core systems initialization in the background.";
=======
const char kLensCameraAssistedSearchName[] =
    "Google Lens in Omnibox and New Tab Page";
const char kLensCameraAssistedSearchDescription[] =
    "Enable an entry point to Google Lens to allow users to search what they "
    "see using their mobile camera.";

const char kLinkDoctorDeprecationAndroidName[] =
    "Link Doctor Deprecation on Android";
const char kLinkDoctorDeprecationAndroidDescription[] =
    "Removes the setting for retrieving suggestions on navigation errors since "
    "this feature is deprecated.";

const char kLiteVideoName[] = "Enable LiteVideos";
const char kLiteVideoDescription[] =
    "Enable the LiteVideo optimization to throttle media requests to "
    "reduce data usage";
>>>>>>> chromium

const char kLiteVideoDownlinkBandwidthKbpsName[] =
    "Lite Video: Adjust throttling downlink (in Kbps).";
const char kLiteVideoDownlinkBandwidthKbpsDescription[] =
    "Specify the throttling bandwidth to be used";

<<<<<<< HEAD
const char kLanguageDetectionAPIName[] = "Language detection web platform API";
const char kLanguageDetectionAPIDescription[] =
    "When enabled, JS can use the web platform's language detection API";

const char kLegacyTechReportTopLevelUrlName[] =
    "Using top level navigation URL for legacy technology report";
const char kLegacyTechReportTopLevelUrlDescription[] =
    "When a legacy technology report is triggered and uploaded for enterprise "
    "users. By default, the URL of the report won't be same as the one in the "
    "Omnibox if the event is detected in a sub-frame. Enable this flag will "
    "allow browser trace back to the top level URL instead and populate the "
    "Frame URL in the `frame_url` field on the API.";

const char kLensOverlayName[] = "Lens overlay";
const char kLensOverlayDescription[] =
    "Enables Lens search via an overlay on any page.";

const char kLensOverlayContextualSearchboxName[] =
    "Lens overlay contextual search box";
const char kLensOverlayContextualSearchboxDescription[] =
    "Enables contextual search box in the Lens overlay.";

const char kLensOverlayImageContextMenuActionsName[] =
    "Lens overlay image context menu actions";
const char kLensOverlayImageContextMenuActionsDescription[] =
    "Enables image context menu actions in the Lens overlay.";

const char kLensOverlaySidePanelOpenInNewTabName[] =
    "Lens overlay side panel open in new tab";
const char kLensOverlaySidePanelOpenInNewTabDescription[] =
    "Enables open in new tab in the Lens overlay side panel.";

const char kLensOverlayTranslateButtonName[] = "Lens overlay translate button";
const char kLensOverlayTranslateButtonDescription[] =
    "Enables translate button via the Lens overlay.";

const char kLensOverlayTranslateLanguagesName[] =
    "More Lens overlay translate languages";
const char kLensOverlayTranslateLanguagesDescription[] =
    "Enables more translate languages in the Lens Overlay.";

const char kLensOverlayLatencyOptimizationsName[] =
    "Lens overlay latency optimizations";
const char kLensOverlayLatencyOptimizationsDescription[] =
    "Enables latency optimizations for the Lens overlay.";

const char kLinkedServicesSettingName[] = "Linked Services Setting";
const char kLinkedServicesSettingDescription[] =
    "Add Linked Services Setting to the Sync Settings page.";
=======
const char kLiteVideoForceOverrideDecisionName[] = "Force LiteVideos decision";
const char kLiteVideoForceOverrideDecisionDescription[] =
    "Force the LiteVideo decision to be allowed on every navigation.";
>>>>>>> chromium

const char kLogJsConsoleMessagesName[] =
    "Log JS console messages in system logs";
const char kLogJsConsoleMessagesDescription[] =
    "Enable logging JS console messages in system logs, please note that they "
    "may contain PII.";

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
const char kLoginDbDeprecationAndroidName[] =
    "Deprecate the LoginDB on Android";
const char kLoginDbDeprecationAndroidDescription[] =
    "When enabled, Chrome on Android stops using the LoginDB. This applies "
    "only to users who haven't been migrated to the new Android backend."
    "Existing passwords in the LoginDB can be accessed in an exported CSV when "
    "the user chooses to do so.";
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
const char kMantisFeatureKeyName[] = "Secret key for Mantis feature.";
const char kMantisFeatureKeyDescription[] =
    "Feature key to use the Mantis feature on ChromeOS.";
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
const char kMediaHistoryName[] = "Enable Media History";
const char kMediaHistoryDescription[] =
    "Enables Media History which records data around media playbacks on "
    "websites.";
>>>>>>> chromium

const char kMediaRouterCastAllowAllIPsName[] =
    "Connect to Cast devices on all IP addresses";
const char kMediaRouterCastAllowAllIPsDescription[] =
    "Have the Media Router connect to Cast devices on all IP addresses, not "
    "just RFC1918/RFC4193 private addresses.";

const char kMediaSessionWebRTCName[] = "Enable WebRTC actions in Media Session";
const char kMediaSessionWebRTCDescription[] =
    "Adds new actions into Media Session for video conferencing.";

const char kMemoriesName[] = "Memories";
const char kMemoriesDescription[] = "Enables chrome://memories.";

const char kMemoriesDebugName[] = "Memories Debug";
const char kMemoriesDebugDescription[] =
    "Show debug information for chrome://memories.";

const char kMetricsSettingsAndroidName[] = "Metrics Settings on Android";
const char kMetricsSettingsAndroidDescription[] =
    "Enables the new design of metrics settings.";

const char kMixedFormsDisableAutofillName[] =
    "Disable autofill for mixed forms";
const char kMixedFormsDisableAutofillDescription[] =
    "If enabled, autofill is not allowed for mixed forms (forms on HTTPS sites "
    "that submit over HTTP), and a warning bubble will be shown instead. "
    "Autofill for passwords is not affected by this setting.";

const char kMixedFormsInterstitialName[] = "Mixed forms interstitial";
const char kMixedFormsInterstitialDescription[] =
    "When enabled, a full-page interstitial warning is shown when a mixed "
    "content form (a form on an HTTPS site that submits over HTTP) is "
    "submitted.";

const char kMobileIdentityConsistencyName[] = "Mobile identity consistency";
const char kMobileIdentityConsistencyDescription[] =
    "Enables stronger identity consistency on mobile";

const char kMobileIdentityConsistencyVarName[] =
    "Mobile identity consistency variations";
const char kMobileIdentityConsistencyVarDescription[] =
    "Enables stronger identity consistency on mobile with different UI "
    "variations";

const char kWipeDataOnChildAccountSigninName[] =
    "Wipe Data On Child account signin";
const char kWipeDataOnChildAccountSigninDescription[] =
    "Wipe Data from previous account when signing in a child account";

const char kMobileIdentityConsistencyFREName[] =
    "Mobile identity consistency FRE";
const char kMobileIdentityConsistencyFREDescription[] =
    "Enables stronger identity consistency on mobile with different UIs for "
    "the First Run Experience.";

const char kMobilePwaInstallUseBottomSheetName[] =
    "Mobile PWA Installation bottom sheet";
const char kMobilePwaInstallUseBottomSheetDescription[] =
    "Enables use of a rich bottom sheet when offering mobile PWA installation.";

const char kMojoLinuxChannelSharedMemName[] =
    "Enable Mojo Shared Memory Channel";
const char kMojoLinuxChannelSharedMemDescription[] =
    "If enabled Mojo on Linux based platforms can use shared memory as an "
    "alternate channel for most messages.";

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
const char kMostVisitedTilesCustomizationName[] =
    "Customize Most Visiteid Tiles";
const char kMostVisitedTilesCustomizationDescription[] =
    "Adds long-click menu to fix the title and URL of a Most Visited Tile; "
    "enables MVT reordering.";
#endif  // BUILDFLAG(IS_ANDROID)

const char kMostVisitedTilesReselectName[] = "Most Visited Tiles Reselect";
const char kMostVisitedTilesReselectDescription[] =
    "When MV tiles is clicked, scans for a tab with a matching URL. "
    "If found, selects the tab and closes the NTP. Else opens into NTP.";
=======
const char kMouseSubframeNoImplicitCaptureName[] =
    "Disable mouse implicit capture for iframe";
const char kMouseSubframeNoImplicitCaptureDescription[] =
    "When enable, mouse down does not implicit capture for iframe.";
>>>>>>> chromium

const char kMutingCompromisedCredentialsName[] =
    "Enables muting of compromised credentials";
const char kMutingCompromisedCredentialsDescription[] =
    "When enable, insecure credential muting state is respected.";

const char kCanvas2DLayersName[] =
    "Enables canvas 2D methods BeginLayer and EndLayer";
const char kCanvas2DLayersDescription[] =
    "Enables the canvas 2D methods BeginLayer and EndLayer.";

const char kNewCanvas2DAPIName[] = "Experimental canvas 2D API features";
const char kNewCanvas2DAPIDescription[] =
    "Enables in-progress features for the canvas 2D API. See "
    "https://github.com/fserb/canvas2d.";

const char kSignInProfileCreationName[] = "Profile creation flow with sign-in";
const char kSignInProfileCreationDescription[] =
    "Enables a new sign-in flow in profile creation";

const char kSignInProfileCreationEnterpriseName[] =
    "Profile creation flow support for enterprise sign-in";
const char kSignInProfileCreationEnterpriseDescription[] =
    "Enables smoother enterprise experience in signed-in profile creation flow";

const char kSyncingCompromisedCredentialsName[] = "Syncing of Security Issues";
const char kSyncingCompromisedCredentialsDescription[] =
    "Enables syncing of Security issues which includes compromised and phished "
    "passwords.";

const char kSystemProxyForSystemServicesName[] =
    "Enable system-proxy for selected system services";
const char kSystemProxyForSystemServicesDescription[] =
    "Enabling this flag will allow Chrome OS system service which require "
    "network connectivity to use the system-proxy daemon for authentication to "
    "remote HTTP web proxies.";

const char kDestroyProfileOnBrowserCloseName[] =
    "Destroy Profile on browser close";
const char kDestroyProfileOnBrowserCloseDescription[] =
    "Release memory and other resources when a Profile's last browser window "
    "is closed, rather than when Chrome closes completely.";

const char kNewUsbBackendName[] = "Enable new USB backend";
const char kNewUsbBackendDescription[] =
    "Enables the new experimental USB backend for macOS";

const char kNewTabstripAnimationName[] = "New tabstrip animations";
const char kNewTabstripAnimationDescription[] =
    "New implementation of tabstrip animations.";

const char kNotificationIndicatorName[] = "Notification Indicators";
const char kNotificationIndicatorDescription[] =
    "Enable notification indicators, which appear on shelf app icons and "
    "launcher apps when a notification is active.";

const char kNotificationSchedulerName[] = "Notification scheduler";
const char kNotificationSchedulerDescription[] =
    "Enable notification scheduler feature.";

const char kNotificationSchedulerDebugOptionName[] =
    "Notification scheduler debug options";
const char kNotificationSchedulerDebugOptionDescription[] =
    "Enable debugging mode to override certain behavior of notification "
    "scheduler system for easier manual testing.";
const char kNotificationSchedulerImmediateBackgroundTaskDescription[] =
    "Show scheduled notification right away.";

const char kNotificationsSystemFlagName[] = "Enable system notifications.";
const char kNotificationsSystemFlagDescription[] =
    "Enable support for using the system notification toasts and notification "
    "center on platforms where these are available.";

const char kUpdateHoverAtBeginFrameName[] = "Update hover at the begin frame";
const char kUpdateHoverAtBeginFrameDescription[] =
    "Recompute hover state at BeginFrame for layout and scroll based mouse "
    "moves, rather than old timing-based mechanism.";

<<<<<<< HEAD
=======
const char kOmniboxActiveSearchEnginesName[] =
    "Active Search Engines section on settings page";
const char kOmniboxActiveSearchEnginesDescription[] =
    "Enables a 'Your Search Engines' section on "
    "chrome://settings/searchEngines.";

>>>>>>> chromium
const char kOmniboxAdaptiveSuggestionsCountName[] =
    "Adaptive Omnibox Suggestions count";
const char kOmniboxAdaptiveSuggestionsCountDescription[] =
    "Dynamically adjust number of presented Omnibox suggestions depending on "
    "available space. When enabled, this feature will increase (or decrease) "
    "amount of offered Omnibox suggestions to fill in the space between the "
    "Omnibox and soft keyboard (if any). See also Max Autocomplete Matches "
    "flag to adjust the limit of offered suggestions. The number of shown "
    "suggestions will be no less than the platform default limit.";

const char kOmniboxAssistantVoiceSearchName[] =
    "Omnibox Assistant Voice Search";
const char kOmniboxAssistantVoiceSearchDescription[] =
    "When enabled, use Assistant for omnibox voice query recognition instead of"
    " Android's built-in voice recognition service. Only works on Android.";

const char kOmniboxBookmarkPathsName[] = "Omnibox Bookmark Paths";
const char kOmniboxBookmarkPathsDescription[] =
    "Allows inputs to match with bookmark paths. E.g. 'planets jupiter' can "
    "suggest a bookmark titled 'Jupiter' with URL "
    "'en.wikipedia.org/wiki/Jupiter' located in a path containing 'planet.'";

const char kOmniboxClobberTriggersContextualWebZeroSuggestName[] =
    "Omnibox Clobber Triggers Contextual Web ZeroSuggest";
const char kOmniboxClobberTriggersContextualWebZeroSuggestDescription[] =
    "If enabled, when the user clears the whole omnibox text (i.e. via "
    "Backspace), Chrome will request ZeroSuggest suggestions for the OTHER "
    "page classification (contextual web).";

const char kOmniboxCompactSuggestionsName[] = "Omnibox: Compact suggestions";
const char kOmniboxCompactSuggestionsDescription[] =
    "Conserve the space for Omnibox Suggestions by slightly reducing their "
    "size.";

const char kOmniboxDisableCGIParamMatchingName[] =
    "Disable CGI Param Name Matching";
const char kOmniboxDisableCGIParamMatchingDescription[] =
    "Disables using matches in CGI parameter names while scoring suggestions.";

const char kOmniboxDefaultTypedNavigationsToHttpsName[] =
    "Omnibox - Use HTTPS as the default protocol for navigations";
const char kOmniboxDefaultTypedNavigationsToHttpsDescription[] =
    "Use HTTPS as the default protocol when the user types a URL without "
    "a protocol in the omnibox such as 'example.com'. Presently, such an entry "
    "navigates to http://example.com. When this feature is enabled, it will "
    "navigate to https://example.com if the HTTPS URL is available. If Chrome "
    "can't determine the availability of the HTTPS URL within the timeout, it "
    "will fall back to the HTTP URL.";

const char kOmniboxExperimentalSuggestScoringName[] =
    "Omnibox Experimental Suggest Scoring";
const char kOmniboxExperimentalSuggestScoringDescription[] =
    "Enables an experimental scoring mode for suggestions when Google is the "
    "default search engine.";

const char kOmniboxKeywordSpaceTriggeringSettingName[] =
    "Omnibox Keyword Space Triggering Setting";
const char kOmniboxKeywordSpaceTriggeringSettingDescription[] =
    "Adds a setting to the search engines setting page to control whether "
    "spacebar activates keyword mode.";

const char kOmniboxMostVisitedTilesName[] = "Omnibox Most Visited Tiles";
const char kOmniboxMostVisitedTilesDescription[] =
    "Display a list of frquently visited pages from history as a single row "
    "with a carousel instead of one URL per line.";

<<<<<<< HEAD
const char kOmniboxZeroSuggestPrefetchingOnSRPName[] =
    "Omnibox Zero Prefix Suggestion Prefetching on SRP";
const char kOmniboxZeroSuggestPrefetchingOnSRPDescription[] =
    "Enables prefetching of the zero prefix suggestions for eligible users "
    "on the Search Results page.";

const char kOmniboxZeroSuggestPrefetchingOnWebName[] =
    "Omnibox Zero Prefix Suggestion Prefetching on the Web";
const char kOmniboxZeroSuggestPrefetchingOnWebDescription[] =
    "Enables prefetching of the zero prefix suggestions for eligible users "
    "on the Web (i.e. non-NTP and non-SRP URLs).";

const char kOmniboxZeroSuggestInMemoryCachingName[] =
    "Omnibox Zero Prefix Suggestion in-memory caching";
const char kOmniboxZeroSuggestInMemoryCachingDescription[] =
    "Enables in-memory caching of zero prefix suggestions.";

const char kOmniboxOnDeviceHeadSuggestionsName[] =
    "Omnibox on device head suggestions (non-incognito only)";
const char kOmniboxOnDeviceHeadSuggestionsDescription[] =
    "Google head non personalized search suggestions provided by a compact on "
    "device model for non-incognito. Turn off this feature if you have other "
    "apps running which affects local file access (e.g. anti-virus software) "
    "and are experiencing searchbox typing lag.";
const char kOmniboxOnDeviceHeadSuggestionsIncognitoName[] =
    "Omnibox on device head suggestions (incognito only)";
const char kOmniboxOnDeviceHeadSuggestionsIncognitoDescription[] =
    "Google head non personalized search suggestions provided by a compact on "
    "device model for incognito. Turn off this feature if you have other "
    "apps running which affects local file access (e.g. anti-virus software) "
    "and are experiencing searchbox typing lag.";
const char kOmniboxOnDeviceTailSuggestionsName[] =
    "Omnibox on device tail suggestions";
const char kOmniboxOnDeviceTailSuggestionsDescription[] =
    "Google tail non personalized search suggestions provided by a compact on "
    "device model.";

=======
const char kOmniboxTrendingZeroPrefixSuggestionsOnNTPName[] =
    "Omnibox Trending Zero Prefix Suggestions";
const char kOmniboxTrendingZeroPrefixSuggestionsOnNTPDescription[] =
    "Enables trending zero prefix suggestions for signed-in users with no or "
    "insufficient search history.";

const char kOmniboxRichAutocompletionName[] = "Omnibox Rich Autocompletion";
const char kOmniboxRichAutocompletionDescription[] =
    "Allow autocompletion for titles and non-prefixes. I.e. suggestions whose "
    "titles or URLs contain the user input as a continuous chunk, but not "
    "necessarily a prefix, can be the default suggestion. Typically, only "
    "suggestions whose URLs are prefixed by the user input can be. The "
    "potential variations toggle 4 params: 1) 'Title UI' displays titles, 2) "
    "'2-Line UI' includes titles (and URLs when autocompleting titles) on a "
    "2nd line, 3) 'Title AC' autocompletes titles, and 4) 'Non-Prefix AC' "
    "autocompletes non-prefixes.";
const char kOmniboxRichAutocompletionMinCharName[] =
    "Omnibox Rich Autocompletion Min Characters";
const char kOmniboxRichAutocompletionMinCharDescription[] =
    "Specifies min input character length to trigger rich autocompletion.";
const char kOmniboxRichAutocompletionShowAdditionalTextName[] =
    "Omnibox Rich Autocompletion Show Additional Text";
const char kOmniboxRichAutocompletionShowAdditionalTextDescription[] =
    "Show the suggestion title or URL additional text when the input matches "
    "the URL or title respectively. Defaults to true.";
const char kOmniboxRichAutocompletionSplitName[] =
    "Omnibox Rich Autocompletion Split";
const char kOmniboxRichAutocompletionSplitDescription[] =
    "Allow splitting the user input to intermix with autocompletions; e.g., "
    "the user input 'x z' could be autocompleted as 'x [y ]z'.";
const char kOmniboxRichAutocompletionPreferUrlsOverPrefixesName[] =
    "Omnibox Rich Autocompletion Prefer URLs over prefixes";
const char kOmniboxRichAutocompletionPreferUrlsOverPrefixesDescription[] =
    "When the input matches both a suggestion's title's prefix and its URL's "
    "non-prefix, autocomplete the URL.";
>>>>>>> chromium
const char kOmniboxRichAutocompletionPromisingName[] =
    "Omnibox Rich Autocompletion Promising Combinations";
const char kOmniboxRichAutocompletionPromisingDescription[] =
    "Allow autocompletion for titles and non-prefixes; see Omnibox Rich "
    "Autocompletion.";

const char kOmniboxRichEntitiesInLauncherName[] =
    "Omnibox rich entities in the launcher";
const char kOmniboxRichEntitiesInLauncherDescription[] =
    "Enable rich entity formatting for Omnibox results in the launcher.";

const char kOmniboxOnFocusSuggestionsContextualWebAllowSRPName[] =
    "Allow Omnibox contextual web on-focus suggestions on the SRP";
const char kOmniboxOnFocusSuggestionsContextualWebAllowSRPDescription[] =
    "Enables on-focus suggestions on the Search Results page. "
    "Requires on-focus suggestions for the contextual web to be enabled. "
    "Will only work if user is signed-in and syncing.";

const char kOmniboxOnFocusSuggestionsContextualWebName[] =
    "Omnibox on-focus suggestions for the contextual Web";
const char kOmniboxOnFocusSuggestionsContextualWebDescription[] =
    "Enables on-focus suggestions on the Open Web, that are contextual to the "
    "current URL. Will only work if user is signed-in and syncing, or is "
    "otherwise eligible to send the current page URL to the suggest server.";

const char kOmniboxSpareRendererName[] =
    "Start spare renderer on omnibox focus";
const char kOmniboxSpareRendererDescription[] =
    "When the omnibox is focused, start an empty spare renderer. This can "
    "speed up the load of the navigation from the omnibox.";

const char kOmniboxTabSwitchSuggestionsName[] =
    "Omnibox switch to tab suggestions";
const char kOmniboxTabSwitchSuggestionsDescription[] =
    "Enable URL suggestions to optionally take the user to a tab where a "
    "website is already opened.";

<<<<<<< HEAD
const char kOmniboxMlUrlScoringModelName[] = "Omnibox URL Scoring Model";
const char kOmniboxMlUrlScoringModelDescription[] =
    "Enables ML scoring model for Omnibox URL suggestions.";
=======
const char kOmniboxUIHideSteadyStateUrlSchemeName[] =
    "Omnibox UI Hide Steady-State URL Scheme";
const char kOmniboxUIHideSteadyStateUrlSchemeDescription[] =
    "In the omnibox, hide the scheme from steady state displayed URLs. It is "
    "restored during editing.";
>>>>>>> chromium

const char kOmniboxUIHideSteadyStateUrlTrivialSubdomainsName[] =
    "Omnibox UI Hide Steady-State URL Trivial Subdomains";
const char kOmniboxUIHideSteadyStateUrlTrivialSubdomainsDescription[] =
    "In the omnibox, hide trivial subdomains from steady state displayed URLs. "
    "Hidden portions are restored during editing.";

const char kOmniboxUIRevealSteadyStateUrlPathQueryAndRefOnHoverName[] =
    "Omnibox UI Reveal Steady-State URL Path, Query, and Ref On Hover";
const char kOmniboxUIRevealSteadyStateUrlPathQueryAndRefOnHoverDescription[] =
    "In the omnibox, reveal the path, query and ref from steady state "
    "displayed URLs on hover.";

const char kOmniboxUIHideSteadyStateUrlPathQueryAndRefOnInteractionName[] =
    "Omnibox UI Hide Steady-State URL Path, Query, and Ref On Interaction";
const char
    kOmniboxUIHideSteadyStateUrlPathQueryAndRefOnInteractionDescription[] =
        "In the omnibox, hide the path, query and ref from steady state "
        "displayed URLs when the user interacts with the page.";

const char kOmniboxUIMaybeElideToRegistrableDomainName[] =
    "Omnibox UI Sometimes Hide Steady-State URL Subdomains Beyond Registrable "
    "Domain";
const char kOmniboxUIMaybeElideToRegistrableDomainDescription[] =
    "In the omnibox, occasionally hide subdomains as well as path, query and "
    "ref from steady state displayed URLs, depending on heuristics. Has no "
    "effect unless at least one of "
    "#omnibox-ui-reveal-steady-state-url-path-query-and-ref-on-hover or "
    "#omnibox-ui-hide-steady-state-url-path-query-and-ref-on-interaction is "
    "enabled.";

const char kOmniboxMaxZeroSuggestMatchesName[] =
    "Omnibox Max Zero Suggest Matches";
const char kOmniboxMaxZeroSuggestMatchesDescription[] =
    "Changes the maximum number of autocomplete matches displayed when zero "
    "suggest is active (i.e. displaying suggestions without input).";

const char kOmniboxUIMaxAutocompleteMatchesName[] =
    "Omnibox UI Max Autocomplete Matches";
const char kOmniboxUIMaxAutocompleteMatchesDescription[] =
    "Changes the maximum number of autocomplete matches displayed in the "
    "Omnibox UI.";

<<<<<<< HEAD
const char kOmniboxStarterPackExpansionName[] =
    "Expansion pack for the Site search starter pack";
const char kOmniboxStarterPackExpansionDescription[] =
    "Enables additional providers for the Site search starter pack feature";

const char kOmniboxStarterPackIPHName[] =
    "IPH message for the Site search starter pack";
const char kOmniboxStarterPackIPHDescription[] =
    "Enables an informational IPH message for the  Site search starter pack "
    "feature";

const char kOmniboxFocusTriggersWebAndSRPZeroSuggestName[] =
    "Omnibox on-focus suggestions on web and SRP";
const char kOmniboxFocusTriggersWebAndSRPZeroSuggestDescription[] =
    "Enables zero-prefix suggestions on web and SRP when the omnibox is "
    "focused, subject to the same conditions and restrictions as on-clobber "
    "suggestions.";

const char kWebUIOmniboxPopupName[] = "WebUI Omnibox Popup";
const char kWebUIOmniboxPopupDescription[] =
    "If enabled, shows the omnibox suggestions popup in WebUI.";
=======
const char kOmniboxUpdatedConnectionSecurityIndicatorsName[] =
    "Omnibox Updated connection security indicators";
const char kOmniboxUpdatedConnectionSecurityIndicatorsDescription[] =
    "Use new connection security indicators for https pages in the omnibox.";
>>>>>>> chromium

const char kOmniboxMaxURLMatchesName[] = "Omnibox Max URL Matches";
const char kOmniboxMaxURLMatchesDescription[] =
    "The maximum number of URL matches to show, unless there are no "
    "replacements.";

const char kOmniboxDynamicMaxAutocompleteName[] =
    "Omnibox Dynamic Max Autocomplete";
const char kOmniboxDynamicMaxAutocompleteDescription[] =
    "Configures the maximum number of autocomplete matches displayed in the "
    "Omnibox UI dynamically based on the number of URL matches.";

const char kOmniboxOnDeviceHeadSuggestionsIncognitoName[] =
    "Omnibox on device head suggestions (incognito only)";
const char kOmniboxOnDeviceHeadSuggestionsIncognitoDescription[] =
    "Google head non personalized search suggestions provided by a compact on "
    "device model for incognito";

const char kOmniboxOnDeviceHeadSuggestionsNonIncognitoName[] =
    "Omnibox on device head suggestions (non-incognito only)";
const char kOmniboxOnDeviceHeadSuggestionsNonIncognitoDescription[] =
    "Google head non personalized search suggestions provided by a compact on "
    "device model for non-incognito";

const char kOmniboxWebUIOmniboxPopupName[] = "WebUI Omnibox Popup";
const char kOmniboxWebUIOmniboxPopupDescription[] =
    "If enabled, uses WebUI to render the omnibox suggestions popup, similar "
    "to how the NTP \"realbox\" is implemented.";

const char kEnableSearchPrefetchName[] = "Search Prefetch";
const char kEnableSearchPrefetchDescription[] =
    "Allow the default search engine to specify prefetch behavior for "
    "suggestions to search results pages.";

const char kOopRasterizationName[] = "Out of process rasterization";
const char kOopRasterizationDescription[] =
    "Perform Ganesh raster in the GPU Process instead of the renderer.  "
    "Must also enable GPU rasterization";

const char kOopRasterizationDDLName[] =
    "Out of process rasterization using DDLs";
const char kOopRasterizationDDLDescription[] =
    "Use Skia Deferred Display Lists when performing rasterization in the GPU "
    "process  "
    "Must also enable OOP rasterization";

const char kOptimizationGuideModelDownloadingName[] =
    "Allow optimization guide model downloads";
const char kOptimizationGuideModelDownloadingDescription[] =
    "Enables the optimization guide to download prediction models.";

const char kOptimizationGuideModelPushNotificationName[] =
    "Enable optimization guide push notifications";
const char kOptimizationGuideModelPushNotificationDescription[] =
    "Enables the optimization guide to receive push notifications.";

const char kEnableDeJellyName[] = "Experimental de-jelly effect";
const char kEnableDeJellyDescription[] =
    "Enables an experimental effect which attempts to mitigate "
    "\"jelly-scrolling\". This is an experimental implementation with known "
    "bugs, visual artifacts, and performance cost. This implementation may be "
    "removed at any time.";

const char kOsSettingsAppNotificationsPageName[] =
    "CrOS Settings App Notifications Page";
const char kOsSettingsAppNotificationsPageDescription[] =
    "If enabled, a new App Notifications subpage will appear in the "
    "CrOS Settings Apps section.";

const char kOsSettingsDeepLinkingName[] = "CrOS Settings Deep Linking";
const char kOsSettingsDeepLinkingDescription[] =
    "Enables a unique URL for each path in CrOS settings. "
    "This allows deep linking to individual settings, i.e. in settings search.";

const char kOverlayScrollbarsName[] = "Overlay Scrollbars";
const char kOverlayScrollbarsDescription[] =
    "Enable the experimental overlay scrollbars implementation. You must also "
    "enable threaded compositing to have the scrollbars animate.";

const char kOverlayStrategiesName[] = "Select HW overlay strategies";
const char kOverlayStrategiesDescription[] =
    "Select strategies used to promote quads to HW overlays.";
const char kOverlayStrategiesDefault[] = "Default";
const char kOverlayStrategiesNone[] = "None";
const char kOverlayStrategiesUnoccludedFullscreen[] =
    "Unoccluded fullscreen buffers (single-fullscreen)";
const char kOverlayStrategiesUnoccluded[] =
    "Unoccluded buffers (single-fullscreen,single-on-top)";
const char kOverlayStrategiesOccludedAndUnoccluded[] =
    "Occluded and unoccluded buffers "
    "(single-fullscreen,single-on-top,underlay)";

const char kOverrideLanguagePrefsForHrefTranslateName[] =
    "Override user-blocklisted languages for hrefTranslate";
const char kOverrideLanguagePrefsForHrefTranslateDescription[] =
    "When using hrefTranslate, ignore the user's blocklist of languages that "
    "shouldn't be translated.";
const char kOverrideSitePrefsForHrefTranslateName[] =
    "Override user-blocklisted sites for hrefTranslate";
const char kOverrideSitePrefsForHrefTranslateDescription[] =
    "When using hrefTranslate, ignore the user's blocklist of websites that "
    "shouldn't be translated.";
const char kOverrideUnsupportedPageLanguageForHrefTranslateName[] =
    "Force translation on pages with unsupported languages for hrefTranslate";
const char kOverrideUnsupportedPageLanguageForHrefTranslateDescription[] =
    "When using hrefTranslate, force translation on pages where the page's "
    "language cannot be determined or is unsupported.";
const char kOverrideSimilarLanguagesForHrefTranslateName[] =
    "Force translation on pages with a similar page language for hrefTranslate";
const char kOverrideSimilarLanguagesForHrefTranslateDescription[] =
    "When using hrefTranslate, force translation on pages where the page's "
    "language is similar to the target language specified via hrefTranslate.";

const char kOverscrollHistoryNavigationName[] = "Overscroll history navigation";
const char kOverscrollHistoryNavigationDescription[] =
    "History navigation in response to horizontal overscroll.";

<<<<<<< HEAD
const char kPageContentAnnotationsName[] = "Page content annotations";
const char kPageContentAnnotationsDescription[] =
    "Enables page content to be annotated on-device.";

const char kPageContentAnnotationsPersistSalientImageMetadataName[] =
    "Page content annotations - Persist salient image metadata";
const char kPageContentAnnotationsPersistSalientImageMetadataDescription[] =
    "Enables salient image metadata per page load to be persisted on-device.";

const char kPageContentAnnotationsRemotePageMetadataName[] =
    "Page content annotations - Remote page metadata";
const char kPageContentAnnotationsRemotePageMetadataDescription[] =
    "Enables fetching of page load metadata to be persisted on-device.";

const char kPageEmbeddedPermissionControlName[] =
    "Page embedded permission control (permission element)";
const char kPageEmbeddedPermissionControlDescription[] =
    "Enables the Page Embedded Permission Control feature, which allows the "
    "use of the HTML 'permission' element.";

const char kPageImageServiceOptimizationGuideSalientImagesName[] =
    "Page Image Service - Optimization Guide Salient Images";
const char kPageImageServiceOptimizationGuideSalientImagesDescription[] =
    "Enables the PageImageService fetching images from the Optimization Guide "
    "Salient Images source.";

const char kPageImageServiceSuggestPoweredImagesName[] =
    "Page Image Service - Suggest Powered Images";
const char kPageImageServiceSuggestPoweredImagesDescription[] =
    "Enables the PageImageService fetching images from the Suggest source.";

const char kPageInfoAboutThisPagePersistentEntryName[] =
    "AboutThisPage persistent SidePanel entry";
const char kPageInfoAboutThisPagePersistentEntryDescription[] =
    "Registers a SidePanel entry on pageload if 'AboutThisPage' info is "
    "available";

const char kPageInfoCookiesSubpageName[] = "Cookies subpage in page info";
const char kPageInfoCookiesSubpageDescription[] =
    "Enable the Cookies subpage in page info for managing cookies and site "
    "data.";

const char kPageInfoHideSiteSettingsName[] = "Page info hide site settings";
const char kPageInfoHideSiteSettingsDescription[] =
    "Hides site settings row in the page info menu.";

const char kPageInfoHistoryDesktopName[] = "Page info history";
const char kPageInfoHistoryDesktopDescription[] =
    "Enable a history section in the page info.";

const char kPageVisibilityPageContentAnnotationsName[] =
    "Page visibility content annotations";
const char kPageVisibilityPageContentAnnotationsDescription[] =
    "Enables annotating the page visibility model for each page load "
    "on-device.";
=======
const char kOverviewButtonName[] = "Overview button at the status area";
const char kOverviewButtonDescription[] =
    "If enabled, always show the overview button at the status area.";

const char kPageInfoV2DesktopName[] = "Page info version two desktop";
const char kPageInfoV2DesktopDescription[] =
    "Enable the second version of the page info menu on desktop.";
>>>>>>> chromium

const char kParallelDownloadingName[] = "Parallel downloading";
const char kParallelDownloadingDescription[] =
    "Enable parallel downloading to accelerate download speed.";

const char kPassiveEventListenersDueToFlingName[] =
    "Touch Event Listeners Passive Default During Fling";
const char kPassiveEventListenersDueToFlingDescription[] =
    "Forces touchstart, and first touchmove per scroll event listeners during "
    "fling to be treated as passive.";

const char kPassiveDocumentEventListenersName[] =
    "Document Level Event Listeners Passive Default";
const char kPassiveDocumentEventListenersDescription[] =
    "Forces touchstart, and touchmove event listeners on document level "
    "targets (which haven't requested otherwise) to be treated as passive.";

const char kPassiveDocumentWheelEventListenersName[] =
    "Document Level Wheel Event Listeners Passive Default";
const char kPassiveDocumentWheelEventListenersDescription[] =
    "Forces wheel, and mousewheel event listeners on document level targets "
    "(which haven't requested otherwise) to be treated as passive.";

const char kPasswordChangeInSettingsName[] =
    "Rework password change flow from settings";
const char kPasswordChangeInSettingsDescription[] =
    "Change password when bulk leak check detected an issue.";

const char kPasswordChangeName[] = "Rework password change flow";
const char kPasswordChangeDescription[] =
    "Change password when password leak is detected.";

const char kPasswordImportName[] = "Password import";
const char kPasswordImportDescription[] =
    "Import functionality in password settings.";

const char kPasswordScriptsFetchingName[] = "Fetch password scripts";
const char kPasswordScriptsFetchingDescription[] =
    "Fetches scripts for password change flows.";

const char kPdfUnseasonedName[] = "Pepper-free PDF viewer";
const char kPdfUnseasonedDescription[] = "Enables the Pepper-free PDF viewer.";

const char kPdfXfaFormsName[] = "PDF XFA support";
const char kPdfXfaFormsDescription[] =
    "Enables support for XFA forms in PDFs. "
    "Has no effect if Chrome was not built with XFA support.";

const char kForceWebContentsDarkModeName[] = "Force Dark Mode for Web Contents";
const char kForceWebContentsDarkModeDescription[] =
    "Automatically render all web contents using a dark theme.";

const char kForcedColorsName[] = "Forced Colors";
const char kForcedColorsDescription[] =
    "Enables forced colors mode for web content.";

<<<<<<< HEAD
const char kLeftHandSideActivityIndicatorsName[] =
    "Left-hand side activity indicators";
const char kLeftHandSideActivityIndicatorsDescription[] =
    "Moves activity indicators to the left-hand side of location bar.";

#if !BUILDFLAG(IS_ANDROID)
const char kMerchantTrustName[] = "Merchant Trust";
const char kMerchantTrustDescription[] =
    "Enables the merchant trust UI in page info.";
#endif

#if !BUILDFLAG(IS_ANDROID)
const char kPrivacyPolicyInsightsName[] = "Privacy Policy Insights";
const char kPrivacyPolicyInsightsDescription[] =
    "Enables the privacy policy insights UI in page info.";
#endif

#if BUILDFLAG(IS_CHROMEOS)
const char kCrosSystemLevelPermissionBlockedWarningsName[] =
    "Chrome OS block warnings";
const char kCrosSystemLevelPermissionBlockedWarningsDescription[] =
    "Displays warnings in browser if camera, microphone or geolocation is "
    "disabled in the OS.";
#endif

const char kPermissionsAIv1Name[] = "PermissionsAI";
const char kPermissionsAIv1Description[] =
    "Use the Permission Predictions Service and Gemini Nano v2 to surface "
    "permission requests using a quieter UI when the likelihood of the user "
    "granting the permission is predicted to be low. Requires `Make Searches "
    "and Browsing Better` to be enabled.";

const char kPermissionSiteSettingsRadioButtonName[] =
    "Permission radio buttons in Site Settings";
const char kPermissionSiteSettingsRadioButtonDescription[] =
    "Enables radio buttons for permissions in SiteSettings";
=======
const char kPercentBasedScrollingName[] = "Percent-based Scrolling";
const char kPercentBasedScrollingDescription[] =
    "If enabled, mousewheel and keyboard scrolls will scroll by a percentage "
    "of the scroller size.";

const char kPermissionChipName[] = "Permissions Chip Experiment";
const char kPermissionChipDescription[] =
    "Enables an experimental permission prompt that uses a chip in the location"
    " bar.";

const char kPermissionChipGestureSensitiveName[] =
    "Gesture-sensitive Permissions Chip";
const char kPermissionChipGestureSensitiveDescription[] =
    "If the Permissions Chip Experiment is enabled, controls whether or not "
    "the chip should be more prominent when the request is associated with a "
    "gesture.";

const char kPermissionChipRequestTypeSensitiveName[] =
    "Request-type-sensitive Permissions Chip";
const char kPermissionChipRequestTypeSensitiveDescription[] =
    "If the Permissions Chip Experiment is enabled, controls whether or not "
    "the chip should be more or less prominent depending on the request type.";

const char kPermissionPredictionsName[] = "Permission Predictions";
const char kPermissionPredictionsDescription[] =
    "Use the Permission Predictions Service to surface permission requests "
    "using a quieter UI when the likelihood of the user granting the "
    "permission is predicted to be low. Requires "
    "chrome://flags/#quiet-notification-prompts and `Safe Browsing Enhanced "
    "Protection` to be enabled.";

const char kPermissionQuietChipName[] = "Quiet Permission Chip Experiment";
const char kPermissionQuietChipDescription[] =
    "Enables an experimental permission prompt that uses the quiet chip "
    "instead of the right-hand side address bar icon for quiet permission "
    "prompts. Requires chrome://flags/#quiet-notification-prompts to be "
    "enabled.";
>>>>>>> chromium

const char kPlaybackSpeedButtonName[] = "Playback Speed Button";
const char kPlaybackSpeedButtonDescription[] =
    "Enable the playback speed button on the media controls.";

<<<<<<< HEAD
const char kShowWarningsForSuspiciousNotificationsName[] =
    "Show Warnings for Suspicious Notifications";
const char kShowWarningsForSuspiciousNotificationsDescription[] =
    "Enables replacing notification contents with a warning when the on-device "
    "notification content detection model returns a suspicious verdict.";

const char kPowerBookmarkBackendName[] = "Power bookmark backend";
const char kPowerBookmarkBackendDescription[] =
    "Enables storing additional metadata to support power bookmark features.";
=======
const char kPointerLockOptionsName[] = "Enables pointer lock options";
const char kPointerLockOptionsDescription[] =
    "Enables pointer lock unadjustedMovement. When unadjustedMovement is set "
    "to true, pointer movements wil not be affected by the underlying platform "
    "modications such as mouse accelaration.";
>>>>>>> chromium

const char kPrerender2Name[] = "Prerender2";
const char kPrerender2Description[] =
    "Enables the new prerenderer implementation for "
    "<script type=speculationrules> that specifies prerender candidates.";

const char kPrivacyAdvisorName[] = "Privacy Advisor";
const char kPrivacyAdvisorDescription[] =
    "Provides contextual entry points for adjusting privacy settings";

const char kPrivacyReviewName[] = "Privacy Review";
const char kPrivacyReviewDescription[] =
    "Shows a new subpage in Settings that helps the user to review various "
    "privacy settings.";

const char kPrivacySandboxSettingsName[] = "Privacy Sandbox Settings";
const char kPrivacySandboxSettingsDescription[] =
    "Enables privacy sandbox settings. Requires at least one of the Privacy "
    "Sandbox APIs to be enabled.";

const char kPrivacySandboxSettings2Name[] = "Privacy Sandbox Settings 2";
const char kPrivacySandboxSettings2Description[] =
    "Enables the second set of privacy sandbox settings. Requires "
    "#privacy-sandbox-settings to also be enabled";

<<<<<<< HEAD
const char kPrerender2WarmUpCompositorName[] =
    "Warm up compositor on prerendering";
const char kPrerender2WarmUpCompositorDescription[] =
    "Enables compositor warming up on particular loading events of prerender "
    "initial navigation. Requires chrome://flags/#compositor-warm-up to be "
    "enabled";
=======
const char kSafetyCheckWeakPasswordsName[] = "Safety check for weak passwords";
const char kSafetyCheckWeakPasswordsDescription[] =
    "If weak passwords were found, show them in safety check.";
>>>>>>> chromium

const char kProminentDarkModeActiveTabTitleName[] =
    "Prominent Dark Mode Active Tab Titles";
const char kProminentDarkModeActiveTabTitleDescription[] =
    "Makes the active tab title in dark mode bolder so the active tab is "
    "easier "
    "to identify.";

<<<<<<< HEAD
const char kEnableOmniboxSearchPrefetchName[] = "Omnibox prefetch Search";
const char kEnableOmniboxSearchPrefetchDescription[] =
    "Allows omnibox to prefetch likely search suggestions provided by the "
    "Default Search Engine";

const char kEnableOmniboxClientSearchPrefetchName[] =
    "Omnibox client prefetch Search";
const char kEnableOmniboxClientSearchPrefetchDescription[] =
    "Allows omnibox to prefetch search suggestions provided by the Default "
    "Search Engine that the client thinks are likely to be navigated. Requires "
    "chrome://flags/#omnibox-search-prefetch";

const char kPriceChangeModuleName[] = "Price Change Module";
const char kPriceChangeModuleDescription[] =
    "Show a module with price drops of open tabs on new tab page.";

const char kPrivacySandboxAdsAPIsOverrideName[] = "Privacy Sandbox Ads APIs";
const char kPrivacySandboxAdsAPIsOverrideDescription[] =
    "Enables Privacy Sandbox APIs: Attribution Reporting, Fledge, Topics, "
    "Fenced Frames, Shared Storage, Private Aggregation, and their associated "
    "features.";

const char kPrivacySandboxAdsApiUxEnhancementsName[] =
    "Privacy Sandbox Ads API UX Enhancements";
const char kPrivacySandboxAdsApiUxEnhancementsDescription[] =
    "Enables UI and text updates to the Privacy Sandbox Ads APIs Notice and "
    "Consent UX, and settings pages to improve user comprehension";

const char kPrivacySandboxEnrollmentOverridesName[] =
    "Privacy Sandbox Enrollment Overrides";
const char kPrivacySandboxEnrollmentOverridesDescription[] =
    "Allows a list of sites to use Privacy Sandbox features without them being "
    "enrolled and attested into the Privacy Sandbox experiment. See: "
    "https://developer.chrome.com/en/docs/privacy-sandbox/enroll/";

const char kPrivacySandboxEqualizedPromptButtonsName[] =
    "Privacy Sandbox Equalized Prompt Buttons";
const char kPrivacySandboxEqualizedPromptButtonsDescription[] =
    "Enables equalized styling for the dismissal buttons on the Privacy "
    "Sandbox Prompt.";

const char kPrivacySandboxInternalsName[] = "Privacy Sandbox Internals Page";
const char kPrivacySandboxInternalsDescription[] =
    "Enables the chrome://privacy-sandbox-internals debugging page.";

const char kPrivateStateTokensDevUIName[] = "Private State Tokens Dev UI";
const char kPrivateStateTokensDevUIDescription[] =
    "Enables the chrome://privacy-sandbox-internals/private-state-tokens page."
    "Relies on privacy-sandbox-internals also being enabled";

const char kPrivacySandboxPrivacyGuideAdTopicsName[] =
    "Privacy Sandbox Privacy Guide Ad Topics";
const char kPrivacySandboxPrivacyGuideAdTopicsDescription[] =
    "Enables the Ad Topics card in the Privacy Guide to be displayed, subject "
    "to regional availability.";

const char kPrivacySandboxPrivacyPolicyName[] =
    "Privacy Sandbox Privacy Policy";
const char kPrivacySandboxPrivacyPolicyDescription[] =
    "Enables the Privacy Policy link to be displayed on the Privacy Sandbox "
    "Consent dialog, subject to regional availability.";

const char kProtectedAudiencesConsentedDebugTokenName[] =
    "Protected Audiences Consented Debug Token";
const char kProtectedAudiencesConsentedDebugTokenDescription[] =
    "Enables Protected Audience Consented Debugging with the provided token. "
    "Protected Audience auctions running on a Bidding and Auction API trusted "
    "server with a matching token will be able to log information about the "
    "auction to enable debugging. Note that this logging may include "
    "information about the user's browsing history normally kept private.";
=======
const char kPromoBrowserCommandsName[] = "NTP Promo Browser Commands";
const char kPromoBrowserCommandsDescription[] =
    "Enables executing the browser commands sent by the NTP promos";
>>>>>>> chromium

const char kPullToRefreshName[] = "Pull-to-refresh gesture";
const char kPullToRefreshDescription[] =
    "Pull-to-refresh gesture in response to vertical overscroll.";
const char kPullToRefreshEnabledTouchscreen[] = "Enabled for touchscreen only";

const char kPwaUpdateDialogForNameAndIconName[] =
    "Enable PWA install update dialog for name/icon changes";
const char kPwaUpdateDialogForNameAndIconDescription[] =
    "Enable a confirmation dialog that shows up when a PWA changes its "
    "icon/name";

const char kQuicName[] = "Experimental QUIC protocol";
const char kQuicDescription[] = "Enable experimental QUIC protocol support.";

const char kQuickActionSearchWidgetAndroidName[] = "Quick Action Search Widget";
const char kQuickActionSearchWidgetAndroidDescription[] =
    "When enabled, the quick action search widget will be available to add to "
    "the homescreen.";

<<<<<<< HEAD
const char kQuickDeleteAndroidSurveyName[] = "HaTS for Quick Delete on Android";
const char kQuickDeleteAndroidSurveyDescription[] =
    "Enables HaTS survey for Quick Delete on Android.";

const char kQuickShareV2Name[] = "Quick Share v2";
const char kQuickShareV2Description[] =
    "Enables Quick Share v2, which defaults Quick Share to 'Your Devices' "
    "visibility, removes the 'Selected Contacts' visibility, removes the Quick "
    "Share On/Off toggle.";

const char kSendTabToSelfIOSPushNotificationsName[] =
    "Send tab to self iOS push notifications";
const char kSendTabToSelfIOSPushNotificationsDescription[] =
    "Feature to allow users to send tabs to their iOS device through a system "
    "push notification.";

#if BUILDFLAG(IS_ANDROID)
const char kSensitiveContentName[] =
    "Redact sensitive content during screen sharing, screen recording, "
    "and similar actions";

const char kSensitiveContentDescription[] =
    "When enabled, if sensitive form fields (such as credit cards, passwords) "
    "are present on the page, the entire content area is redacted during "
    "screen sharing, screen recording, and similar actions. This feature "
    "works only on Android V or above.";

const char kSensitiveContentWhileSwitchingTabsName[] =
    "Redact sensitive content while switching tabs during screen sharing, "
    "screen recording, and similar actions";

const char kSensitiveContentWhileSwitchingTabsDescription[] =
    "When enabled, if a tab switching surface provides a preview of a tab that "
    "contains sensitive content, the screen is redacted during screen sharing, "
    "screen recording, and similar actions. This feature works only on Android "
    "V or above, and if #sensitive-content is also enabled.";
#endif  // BUILDFLAG(IS_ANDROID)
=======
const char kQuietNotificationPromptsName[] =
    "Quieter notification permission prompts";
const char kQuietNotificationPromptsDescription[] =
    "Enables quieter permission prompts for notification permission requests. "
    "When a site wishes to show notifications, the usual modal dialog is "
    "replaced with a quieter version.";
>>>>>>> chromium

const char kSettingsAppNotificationSettingsName[] =
    "Split notification permission settings";
const char kSettingsAppNotificationSettingsDescription[] =
    "Remove per-app notification permissions settings from the quick settings "
    "menu. Notification permission settings will be split between the "
    "lacros-chrome browser's notification permission page "
    "and the ChromeOS settings app.";

const char kAbusiveNotificationPermissionRevocationName[] =
    "Abusive notification permission revocation";
const char kAbusiveNotificationPermissionRevocationDescription[] =
    "Enables notification permission revocation for abusive origins. "
    "Prior to dispatching a push message to the service worker, the origin is "
    "verified through Safe Browsing. Origins with abusive notification "
    "permission requests or content will have the notification permission "
    "revoked.";

const char kContentSettingsRedesignName[] = "Content settings page redesign";
const char kContentSettingsRedesignDescription[] =
    "Enables a new content settings page UI.";

const char kRawClipboardName[] = "Raw Clipboard";
const char kRawClipboardDescription[] =
    "Allows raw / unsanitized clipboard content to be read and written. "
    "See https://github.com/WICG/raw-clipboard-access.";

const char kReadLaterNewBadgePromoName[] = "Reading list 'New' badge promo";
const char kReadLaterNewBadgePromoDescription[] =
    "Causes a 'New' badge to appear on the entry point for adding to the "
    "reading list in the tab context menu.";

const char kRecordWebAppDebugInfoName[] = "Record web app debug info";
const char kRecordWebAppDebugInfoDescription[] =
    "Enables recording additional web app related debugging data to be "
    "displayed in: chrome://web-app-internals";

<<<<<<< HEAD
#if BUILDFLAG(IS_MAC)
const char kReduceIPAddressChangeNotificationName[] =
    "Reduce IP address change notification";
const char kReduceIPAddressChangeNotificationDescription[] =
    "Reduce the frequency of IP address change notifications that result in "
    "TCP and QUIC connection resets.";
#endif  // BUILDFLAG(IS_MAC)

const char kReduceAcceptLanguageName[] =
    "Reduce Accept-Language request header";
const char kReduceAcceptLanguageDescription[] =
    "Reduce the amount of information available in the Accept-Language request "
    "header. See https://github.com/Tanych/accept-language for more info.";

const char kReduceTransferSizeUpdatedIPCName[] =
    "Reduce TransferSizeUpdated IPC";
const char kReduceTransferSizeUpdatedIPCDescription[] =
    "When enabled, the network service will send TransferSizeUpdatedIPC IPC "
    "only when DevTools is attached or the request is for an ad request.";

#if BUILDFLAG(IS_ANDROID)
const char kReplaceSyncPromosWithSignInPromosName[] =
    "Replace all sync-related UI with sign-in ones";
const char kReplaceSyncPromosWithSignInPromosDescription[] =
    "Follow-ups to the project that replaced sync-related UIs with sign-in "
    "ones.";
#endif  // BUILDFLAG(IS_ANDROID)

const char kResetShortcutCustomizationsName[] =
    "Reset all shortcut customizations";
const char kResetShortcutCustomizationsDescription[] =
    "Resets all shortcut customizations on startup.";

#if BUILDFLAG(IS_ANDROID)
const char kRetainOmniboxOnFocusName[] = "Retain omnibox on focus";
const char kRetainOmniboxOnFocusDescription[] =
    "Whether the contents of the omnibox should be retained on focus as "
    "opposed to being cleared. When this feature flag is enabled and the "
    "omnibox contents are retained, focus events will also result in the "
    "omnibox contents being fully selected so as to allow for easy replacement "
    "by the user. Note that even with this feature flag enabled, only large "
    "screen devices with an attached keyboard and precision pointer will "
    "exhibit a change in behavior.";
#endif  // BUILDFLAG(IS_ANDROID)

const char kRoundedWindows[] = "Use rounded windows";
const char kRoundedWindowsDescription[] =
    "Specifies the radius of rounded windows in DIPs (Device Independent "
    "Pixels)";

const char kRubyShortHeuristicsName[] = "Short ruby heuristics";
const char kRubyShortHeuristicsDescription[] =
    "When enabled, line breaking doesn't happen inside <ruby>s with shorter "
    "contents even if `text-wrap: nowrap` is not specified.";
=======
const char kReduceUserAgentName[] = "Reduce User-Agent request header";
const char kReduceUserAgentDescription[] =
    "Reduce (formerly, \"freeze\") the amount of information available in "
    "the User-Agent request header. "
    "See https://www.chromium.org/updates/ua-reduction for more info.";

const char kRestrictGamepadAccessName[] = "Restrict gamepad access";
const char kRestrictGamepadAccessDescription[] =
    "Enables Permissions Policy and Secure Context restrictions on the Gamepad "
    "API";
>>>>>>> chromium

const char kMBIModeName[] = "MBI Scheduling Mode";
const char kMBIModeDescription[] =
    "Enables independent agent cluster scheduling, via the "
    "AgentSchedulingGroup infrastructure.";

const char kIntensiveWakeUpThrottlingName[] =
    "Throttle Javascript timers in background.";
const char kIntensiveWakeUpThrottlingDescription[] =
    "When enabled, wake ups from DOM Timers are limited to 1 per minute in a "
    "page that has been hidden for 5 minutes. For additional details, see "
    "https://www.chromestatus.com/feature/4718288976216064.";

const char kSafetyTipName[] =
    "Show Safety Tip UI when visiting low-reputation websites";
const char kSafetyTipDescription[] =
    "If enabled, a Safety Tip UI may be displayed when visiting or interacting "
    "with a site Chrome believes may be suspicious.";

const char kSamePartyCookiesConsideredFirstPartyName[] =
    "Consider SameParty cookies to be first-party.";
const char kSamePartyCookiesConsideredFirstPartyDescription[] =
    "If enabled, SameParty cookies will not be blocked even if third-party "
    "cookies are blocked.";

const char kSchemefulSameSiteName[] = "Schemeful Same-Site";
const char kSchemefulSameSiteDescription[] =
    "Modify the same-site computation such that origins with the same "
    "registrable domain but different schemes are considered cross-site. This "
    "change only applies to cookies with the 'SameSite' attribute.";

<<<<<<< HEAD
const char kSafetyHubFollowupName[] = "Followup for Safety Check v2";
const char kSafetyHubFollowupDescription[] =
    "Enables some follow up work for Safety Check v2 if, this includes some "
    "enhancements to the passwords module on the Safety Check page and "
    "enabling the password card on magic stack.";

const char kSafetyHubAndroidSurveyName[] =
    "HaTS for Safety Check v2 on Android";
const char kSafetyHubAndroidSurveyDescription[] =
    "Enables control & proactive HaTS surveys for Safety Check v2 on Android.";

const char kSafetyHubAndroidSurveyV2Name[] =
    "New triggers for HaTS for Safety Check v2 on Android";
const char kSafetyHubAndroidSurveyV2Description[] =
    "Enables new triggers for the HaTS surveys for Safety Check v2 on Android.";

const char kSafetyHubWeakAndReusedPasswordsName[] =
    "Enables Weak and Reused passwords in Safety Hub";
const char kSafetyHubWeakAndReusedPasswordsDescription[] =
    "Enables showing weak and reused passwords in the password module of "
    "Safety Hub.";
#else
const char kSafetyHubHaTSOneOffSurveyName[] =
    "HaTS for Safety Check v2 on Desktop";
const char kSafetyHubHaTSOneOffSurveyDescription[] =
    "Enables one-off HaTS surveys for Safety Check v2 on Desktop.";
#endif  // BUILDFLAG(IS_ANDROID)

const char kSafetyHubAbusiveNotificationRevocationName[] =
    "Include abusive notification sites in the Permissions Module of Safety "
    "Hub";
const char kSafetyHubAbusiveNotificationRevocationDescription[] =
    "When enabled, includes abusive notification permission revocation in the "
    "site permission module of Safety Hub on desktop.";

#if !BUILDFLAG(IS_ANDROID)
const char kSafetyHubServicesOnStartUpName[] =
    "Create Safety Hub services on start up";
const char kSafetyHubServicesOnStartUpDescription[] =
    "When enabled, Safety Hub services are created on start up enabling its "
    "checks to start right away.";
#endif  // !BUILDFLAG(IS_ANDROID)

const char kSameAppWindowCycleName[] = "Cros Labs: Same App Window Cycling";
const char kSameAppWindowCycleDescription[] =
    "Use Alt+` to cycle through the windows of the active application.";

const char kTestThirdPartyCookiePhaseoutName[] =
    "Test Third Party Cookie Phaseout";
const char kTestThirdPartyCookiePhaseoutDescription[] =
    "Enable to test third-party cookie phaseout. "
    "Learn more: https://goo.gle/3pcd-flags";
=======
const char kScreenCaptureTestName[] = "Screen capture test";
const char kScreenCaptureTestDescription[] =
    "Enables an improved screen capture experience which aims to increase "
    "productivity by making screen capture discoverable, intuitive, and "
    "powerful. When enabled, access a new screen capture entry point from "
    "quick settings. Select the capture type and selection default from the "
    "capture mode UI bar. Try out new screen recording functionality.";
>>>>>>> chromium

const char kScrollableTabStripFlagId[] = "scrollable-tabstrip";
const char kScrollableTabStripName[] = "Tab Scrolling";
const char kScrollableTabStripDescription[] =
    "Enables tab strip to scroll left and right when full.";

<<<<<<< HEAD
const char kTabstripComboButtonFlagId[] = "tabstrip-combo-button";
const char kTabstripComboButtonName[] = "Tabstrip Combo Button";
const char kTabstripComboButtonDescription[] =
    "Combines tab search and the new tab button into a single combo button.";
=======
const char kScrollableTabStripButtonsName[] = "Tab Scrolling Buttons";
const char kScrollableTabStripButtonsDescription[] =
    "When the scrollable-tabstrip flag is enabled, this enables buttons to "
    "permanently appear on the tabstrip.";

const char kScrollUnificationName[] = "Scroll Unification";
const char kScrollUnificationDescription[] =
    "Refactoring project that eliminates scroll handling code from Blink. "
    "Does not affect behavior or performance.";
>>>>>>> chromium

const char kSearchHistoryLinkName[] = "Search History Link";
const char kSearchHistoryLinkDescription[] =
    "Changes the Clear Browsing Data UI to display a link to clear search "
    "history on My Google Activity.";

const char kSecurePaymentConfirmationBrowserBoundKeysName[] =
    "Secure Payment Confirmation Browser Bound Key";
const char kSecurePaymentConfirmationBrowserBoundKeysDescription[] =
    "This flag enables an additional browser-bound signature in secure payment "
    "confirmation in PaymentRequest and for WebAuthn payment credentials.";

const char kSecurePaymentConfirmationDebugName[] =
    "Secure Payment Confirmation Debug Mode";
const char kSecurePaymentConfirmationDebugDescription[] =
    "This flag removes the restriction that PaymentCredential in WebAuthn and "
    "secure payment confirmation in PaymentRequest API must use user verifying "
    "platform authenticators.";

const char kSendTabToSelfWhenSignedInName[] = "Send tab to self when signed-in";
const char kSendTabToSelfWhenSignedInDescription[] =
    "Makes the tab sharing feature also available for users who have \"only\" "
    "signed-in to their Google Account (as opposed to having enabled Sync).";

extern const char kSendTabToSelfV2Name[] = "Send tab to self 2.0";
extern const char kSendTabToSelfV2Description[] =
    "Enables new received tab "
    "UI shown next to the profile icon instead of using system notifications.";

const char kSidePanelFlagId[] = "side-panel";
const char kSidePanelName[] = "Side panel";
const char kSidePanelDescription[] =
    "Enables a browser-level side panel for a useful and persistent way to "
    "access your Reading List and Bookmarks.";

const char kServiceWorkerSubresourceFilterName[] =
    "ServiceWorker subresource filter";
const char kServiceWorkerSubresourceFilterDescription[] =
    "Enables an experimental API to specify subresource URLs that bypass "
    "service workers";

const char kSharedClipboardUIName[] =
    "Enable shared clipboard feature signals to be handled";
const char kSharedClipboardUIDescription[] =
    "Enables shared clipboard feature signals to be handled by showing "
    "a list of user's available devices to share the clipboard.";

const char kSharingHubDesktopAppMenuName[] = "Desktop Sharing Hub in App Menu";
const char kSharingHubDesktopAppMenuDescription[] =
    "Enables the Chrome Sharing Hub in the 3-dot menu for desktop.";

const char kSharingHubDesktopOmniboxName[] = "Desktop Sharing Hub in Omnibox";
const char kSharingHubDesktopOmniboxDescription[] =
    "Enables the Chrome Sharing Hub in the omnibox for desktop.";

const char kSharingPeerConnectionReceiverName[] =
    "Enable receiver device to handle peer connection requests.";
const char kSharingPeerConnectionReceiverDescription[] =
    "Enables receiver device to connect and share data using a peer to peer "
    "connection.";

const char kSharingPeerConnectionSenderName[] =
    "Enable sender device to initiate peer connection requests.";
const char kSharingPeerConnectionSenderDescription[] =
    "Enables the sender devices to connect with chosen device using a peer to "
    "peer connection for transferring data.";

const char kSharingPreferVapidName[] =
    "Prefer sending Sharing message via VAPID";
const char kSharingPreferVapidDescription[] =
    "Prefer sending Sharing message via FCM WebPush authenticated using VAPID.";

const char kSharingSendViaSyncName[] =
    "Enable sending Sharing message via Sync";
const char kSharingSendViaSyncDescription[] =
    "Enables sending Sharing message via commiting to Chrome Sync's "
    "SHARING_MESSAGE data type";

const char kShelfDragToPinName[] = "Pin apps in shelf using drag";

const char kShelfDragToPinDescription[] =
    "Enables pinning unpinned items in shelf by dragging them to the part of "
    "the shelf that contains pinned apps.";

const char kShelfHoverPreviewsName[] =
    "Show previews of running apps when hovering over the shelf.";
const char kShelfHoverPreviewsDescription[] =
    "Shows previews of the open windows for a given running app when hovering "
    "over the shelf.";

const char kShowAutofillSignaturesName[] = "Show autofill signatures.";
const char kShowAutofillSignaturesDescription[] =
    "Annotates web forms with Autofill signatures as HTML attributes. Also "
    "marks password fields suitable for password generation.";

const char kShowAutofillTypePredictionsName[] = "Show Autofill predictions";
const char kShowAutofillTypePredictionsDescription[] =
    "Annotates web forms with Autofill field type predictions as placeholder "
    "text.";

const char kShowPerformanceMetricsHudName[] = "Show performance metrics in HUD";
const char kShowPerformanceMetricsHudDescription[] =
    "Display the performance metrics of current page in a heads up display on "
    "the page.";

const char kShowOverdrawFeedbackName[] = "Show overdraw feedback";
const char kShowOverdrawFeedbackDescription[] =
    "Visualize overdraw by color-coding elements based on if they have other "
    "elements drawn underneath.";

<<<<<<< HEAD
#if !BUILDFLAG(IS_CHROMEOS)
const char kFeedbackIncludeVariationsName[] = "Feedback include variations";
const char kFeedbackIncludeVariationsDescription[] =
    "In Chrome feedback report, include commandline variations.";
#endif

const char kSidePanelResizingFlagId[] = "side-panel-resizing";
const char kSidePanelResizingName[] = "Side Panel Resizing";
const char kSidePanelResizingDescription[] =
    "Allows users to resize the side panel and persist the width across "
    "browser sessions.";

const char kSiteInstanceGroupsForDataUrlsName[] =
    "SiteInstanceGroups for data: URLs";
const char kSiteInstanceGroupsForDataUrlsDescription[] =
    "Put data: URL subframes in a separate SiteInstance from the initiator, "
    "but in the same SiteInstanceGroup, and thus the same process.";

const char kDefaultSiteInstanceGroupsName[] = "Default SiteInstanceGroups";
const char kDefaultSiteInstanceGroupsDescription[] =
    "Put sites that don't need isolation in their own SiteInstance in a default"
    "SiteInstanceGroup (per BrowsingContextGroup) instead of in a default "
    "SiteInstance.";

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
const char kPwaNavigationCapturingName[] = "Desktop PWA Link Capturing";
const char kPwaNavigationCapturingDescription[] =
    "Enables opening links from Chrome in an installed PWA. Currently under "
    "reimplementation.";
#endif
=======
const char kSkiaRendererName[] = "Skia API for compositing";
const char kSkiaRendererDescription[] =
    "If enabled, the display compositor will use Skia as the graphics API "
    "instead of OpenGL ES.";
>>>>>>> chromium

const char kIsolateOriginsName[] = "Isolate additional origins";
const char kIsolateOriginsDescription[] =
    "Requires dedicated processes for an additional set of origins, "
    "specified as a comma-separated list.";

const char kIsolationByDefaultName[] =
    "Change web-facing behaviors that prevent origin-level isolation";
const char kIsolationByDefaultDescription[] =
    "Change several web APIs that make it difficult to isolate origins into "
    "distinct processes. While these changes will ideally become new default "
    "behaviors for the web, this flag is likely to break your experience on "
    "sites you visit today.";

const char kSignatureBasedSriName[] = "Signature-based Integrity Checks";
const char kSignatureBasedSriDescription[] =
    "Enables signature-based "
    "integrity checks, as proposed in "
    "https://wicg.github.io/signature-based-sri/.";

const char kSiteIsolationOptOutName[] = "Disable site isolation";
const char kSiteIsolationOptOutDescription[] =
    "Disables site isolation "
    "(SitePerProcess, IsolateOrigins, etc). Intended for diagnosing bugs that "
    "may be due to out-of-process iframes. Opt-out has no effect if site "
    "isolation is force-enabled using a command line switch or using an "
    "enterprise policy. "
    "Caution: this disables important mitigations for the Spectre CPU "
    "vulnerability affecting most computers.";
const char kSiteIsolationOptOutChoiceDefault[] = "Default";
const char kSiteIsolationOptOutChoiceOptOut[] = "Disabled (not recommended)";

const char kSmoothScrollingName[] = "Smooth Scrolling";
const char kSmoothScrollingDescription[] =
    "Animate smoothly when scrolling page content.";

<<<<<<< HEAD
const char kStorageAccessApiFollowsSameOriginPolicyName[] =
    "Storage Access API follows Same Origin Policy";
const char kStorageAccessApiFollowsSameOriginPolicyDescription[] =
    "Modifies the Storage Access API to follow the Same Origin Policy with "
    "respect to security.";

const char kStorageAccessHeadersName[] = "Storage Access Headers";
const char kStorageAccessHeadersDescription[] =
    "Enables HTTP headers related to the Storage Access API.";
=======
const char kWebOTPCrossDeviceName[] = "WebOTP Cross Device";
const char kWebOTPCrossDeviceDescription[] =
    "Enable the WebOTP API to work across devices";

const char kSplitCacheByNetworkIsolationKeyName[] = "HTTP Cache Partitioning";
const char kSplitCacheByNetworkIsolationKeyDescription[] =
    "Partitions the HTTP Cache by (top-level site, current-frame site) to "
    "disallow cross-site tracking.";

const char kStrictExtensionIsolationName[] = "Strict Extension Isolation";
const char kStrictExtensionIsolationDescription[] =
    "Experimental security mode that prevents extensions from sharing a "
    "process with each other.";
>>>>>>> chromium

const char kStrictOriginIsolationName[] = "Strict-Origin-Isolation";
const char kStrictOriginIsolationDescription[] =
    "Experimental security mode that strengthens the site isolation policy. "
    "Controls whether site isolation should use origins instead of scheme and "
    "eTLD+1.";

<<<<<<< HEAD
const char kSupportToolScreenshot[] = "Support Tool Screenshot";
const char kSupportToolScreenshotDescription[] =
    "Enables the Support Tool to capture and include a screenshot in the "
    "exported packet.";
=======
const char kStorageAccessAPIName[] = "Storage Access API";
const char kStorageAccessAPIDescription[] =
    "Enables the Storage Access API, allowing websites to request storage "
    "access when it would otherwise be restricted.";

const char kStoragePressureEventName[] = "Enable storage pressure Event";
const char kStoragePressureEventDescription[] =
    "If enabled, Chrome will dispatch a DOM event, informing applications "
    "about storage pressure (low disk space)";
>>>>>>> chromium

const char kStoreHoursAndroidName[] = "Store Hours";
const char kStoreHoursAndroidDescription[] =
    "When enabled, shows store hours for stores in tab grid view.";

const char kSuggestionsWithSubStringMatchName[] =
    "Substring matching for Autofill suggestions";
const char kSuggestionsWithSubStringMatchDescription[] =
    "Match Autofill suggestions based on substrings (token prefixes) rather "
    "than just prefixes.";

const char kSyncAutofillWalletOfferDataName[] =
    "Enable syncing autofill offer data";
const char kSyncAutofillWalletOfferDataDescription[] =
    "When enabled, allows syncing autofill wallet offer data type.";

const char kSyncSandboxName[] = "Use Chrome Sync sandbox";
const char kSyncSandboxDescription[] =
    "Connects to the testing server for Chrome Sync.";

const char kSyncTrustedVaultPassphrasePromoName[] =
    "Enable promos for sync trusted vault passphrase.";
const char kSyncTrustedVaultPassphrasePromoDescription[] =
    "Enables promos for an experimental sync passphrase type, referred to as "
    "trusted vault.";

const char kSyncTrustedVaultPassphraseRecoveryName[] =
    "Enable sync trusted vault passphrase with improved recovery.";
const char kSyncTrustedVaultPassphraseRecoveryDescription[] =
    "Enables support for an experimental sync passphrase type, referred to as "
    "trusted vault, including logic and APIs for improved account recovery "
    "flows.";

const char kSystemKeyboardLockName[] = "Experimental system keyboard lock";
const char kSystemKeyboardLockDescription[] =
    "Enables websites to use the keyboard.lock() API to intercept system "
    "keyboard shortcuts and have the events routed directly to the website "
    "when in fullscreen mode.";

const char kStylusBatteryStatusName[] =
    "Show stylus battery stylus in the stylus tools menu";
const char kStylusBatteryStatusDescription[] =
    "Enables viewing the current stylus battery level in the stylus tools "
    "menu.";

const char kSubframeShutdownDelayName[] =
    "Add delay to subframe renderer process shutdown";
const char kSubframeShutdownDelayDescription[] =
    "Delays shutdown of subframe renderer processes by a few seconds to allow "
    "them to be potentially reused. This aims to reduce process churn in "
    "navigations where the source and destination share subframes.";

const char kTabEngagementReportingName[] = "Tab Engagement Metrics";
const char kTabEngagementReportingDescription[] =
    "Tracks tab engagement and lifetime metrics.";

<<<<<<< HEAD
const char kTabGroupsDeferRemoteNavigationsId[] =
    "tab-groups-defer-remote-navigations";
const char kTabGroupsDeferRemoteNavigationsName[] =
    "Tab Groups Defer Remote Navigations";
const char kTabGroupsDeferRemoteNavigationsDescription[] =
    "Prevents remote navigations from being performed when a tab is "
    "backgrounded in a group";

const char kTabGroupsSaveV2Id[] = "tab-groups-save-v2";
const char kTabGroupsSaveV2Name[] = "Tab Groups Save and Sync V2";
const char kTabGroupsSaveV2Description[] =
    "Enables saving and recalling of tab groups but enhanced. Highly "
    "experimental.";

const char kTabGroupSyncServiceDesktopMigrationId[] =
    "tab-group-sync-service-desktop-migration";
const char kTabGroupSyncServiceDesktopMigrationName[] =
    "Tab Group Sync Service Desktop Migration";
const char kTabGroupSyncServiceDesktopMigrationDescription[] =
    "Enables use of the TabGroupSyncService. This is a backend only change.";
=======
const char kTabGridLayoutAndroidName[] = "Tab Grid Layout";
const char kTabGridLayoutAndroidDescription[] =
    "Allows users to see their tabs in a grid layout in the tab switcher on "
    "phones.";

const char kCommerceMerchantViewerAndroidName[] = "Merchant Viewer";
const char kCommerceMerchantViewerAndroidDescription[] =
    "Allows users to view merchant trust signals on eligible pages.";

const char kCommercePriceTrackingAndroidName[] = "Price Tracking";
const char kCommercePriceTrackingAndroidDescription[] =
    "Allows users to track product prices through Chrome.";

const char kTabGroupsAndroidName[] = "Tab Groups";
const char kTabGroupsAndroidDescription[] =
    "Allows users to create groups to better organize their tabs on phones.";

const char kTabGroupsContinuationAndroidName[] = "Tab Groups Continuation";
const char kTabGroupsContinuationAndroidDescription[] =
    "Allows users to access continuation features in Tab Group on phones.";

const char kTabGroupsUiImprovementsAndroidName[] = "Tab Groups UI Improvements";
const char kTabGroupsUiImprovementsAndroidDescription[] =
    "Allows users to access new features in Tab Group UI on phones.";

const char kTabToGTSAnimationAndroidName[] = "Enable Tab-to-GTS Animation";
const char kTabToGTSAnimationAndroidDescription[] =
    "Allows users to see an animation when entering or leaving the "
    "Grid Tab Switcher on phones.";

const char kTabGroupsAutoCreateName[] = "Tab Groups Auto Create";
const char kTabGroupsAutoCreateDescription[] =
    "Automatically creates groups for users, if tab groups are enabled.";

const char kTabGroupsCollapseName[] = "Tab Groups Collapse";
const char kTabGroupsCollapseDescription[] =
    "Allows a tab group to be collapsible and expandable, if tab groups are "
    "enabled.";

const char kTabGroupsCollapseFreezingName[] = "Tab Groups Collapse Freezing";
const char kTabGroupsCollapseFreezingDescription[] =
    "Experimental tab freezing upon collapsing a tab group.";

const char kTabGroupsFeedbackName[] = "Tab Groups Feedback";
const char kTabGroupsFeedbackDescription[] =
    "Enables the feedback app to appear in the tab group editor bubble, if tab "
    "groups are enabled.";

const char kTabGroupsNewBadgePromoName[] = "Tab Groups 'New' Badge Promo";
const char kTabGroupsNewBadgePromoDescription[] =
    "Causes a 'New' badge to appear on the entry point for creating a tab "
    "group in the tab context menu.";

const char kTabGroupsSaveName[] = "Tab Groups Save";
const char kTabGroupsSaveDescription[] =
    "Enables users to explicitly save and recall tab groups.";
>>>>>>> chromium

const char kTabHoverCardImagesName[] = "Tab Hover Card Images";
const char kTabHoverCardImagesDescription[] =
    "Shows a preview image in tab hover cards, if tab hover cards are enabled.";

const char kTabOutlinesInLowContrastThemesName[] =
    "Tab Outlines in Low Contrast Themes";
const char kTabOutlinesInLowContrastThemesDescription[] =
    "Expands the range of situations in which tab outline strokes are "
    "displayed, improving accessiblity in dark and incognito mode.";

const char kTabRestoreSubMenusName[] = "Show app menu history sub menus";
const char kTabRestoreSubMenusDescription[] =
    "Show app menu history sub menus for the contents of recently closed tab "
    "groups and windows.";

const char kTextFragmentColorChangeName[] = "Text Fragment color change";
const char kTextFragmentColorChangeDescription[] =
    "Changes the Text Fragment background color"
    "away from the default yellow.";

<<<<<<< HEAD
const char kTextSafetyClassifierName[] = "Text Safety Classifier";
const char kTextSafetyClassifierDescription[] =
    "Enables text safety classifier for on-device models";

#if BUILDFLAG(IS_ANDROID)
const char kAutofillThirdPartyModeContentProviderName[] =
    "Autofill Third Party Mode Content Provider";
const char kAutofillThirdPartyModeContentProviderDescription[] =
    "Enables querying the third party autofill mode state from the Chrome app.";
#endif

const char kThreadedScrollPreventRenderingStarvationName[] =
    "threaded-scroll-prevent-rendering-starvation";
const char kThreadedScrollPreventRenderingStarvationDescription[] =
    "Prevents main thread rendering starvation during threaded scrolling based "
    "on a given threshold.";
=======
const char kTFLiteLanguageDetectionName[] = "TFLite-based Language Detection";
const char kTFLiteLanguageDetectionDescription[] =
    "Uses TFLite for language detection in place of CLD3";
>>>>>>> chromium

const char kThrottleMainTo60HzName[] = "throttle-main-thread-to-60hz";
const char kThrottleMainTo60HzDescription[] =
    "Throttle main thread updates to 60fps, even when VSync rate is higher.";

const char kTintCompositedContentName[] = "Tint composited content";
const char kTintCompositedContentDescription[] =
    "Tint contents composited using Viz with a shade of red to help debug and "
    "study overlay support.";

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
const char kToolbarPinningFlagId[] = "toolbar-pinning";
const char kToolbarPinningName[] = "Toolbar pinning";
const char kToolbarPinningDescription[] =
    "Enables the ability to pin features to the toolbar via the Customize "
    "Chrome side panel.";
#endif

#if !BUILDFLAG(IS_ANDROID)
const char kTopChromeToastsName[] = "Top Chrome Toasts";
const char kTopChromeToastsDescription[] =
    "Enables the use of toasts to present confirmation of user actions.";

const char kTopChromeToastRefinementsName[] = "Top Chrome Toast Refinements";
const char kTopChromeToastRefinementsDescription[] =
    "Enables the use of options to control which toasts appear.";
#endif

=======
>>>>>>> chromium
const char kTopChromeTouchUiName[] = "Touch UI Layout";
const char kTopChromeTouchUiDescription[] =
    "Enables touch UI layout in the browser's top chrome.";

const char kThreadedScrollingName[] = "Threaded scrolling";
const char kThreadedScrollingDescription[] =
    "Threaded handling of scroll-related input events. Disabling this will "
    "force all such scroll events to be handled on the main thread. Note that "
    "this can dramatically hurt scrolling performance of most websites and is "
    "intended for testing purposes only.";

const char kThrottleDisplayNoneAndVisibilityHiddenCrossOriginIframesName[] =
    "Throttle non-visible cross-origin iframes";
const char
    kThrottleDisplayNoneAndVisibilityHiddenCrossOriginIframesDescription[] =
        "When enabled, all cross-origin iframes with zero visibility (either "
        "display:none or zero area) will be throttled, regardless of whether "
        "they are same-process or cross-process. When disabled, only cross-"
        "process iframes will be throttled.";

const char kTouchDragDropName[] = "Touch initiated drag and drop";
const char kTouchDragDropDescription[] =
    "Touch drag and drop can be initiated through long press on a draggable "
    "element.";

const char kTouchSelectionStrategyName[] = "Touch text selection strategy";
const char kTouchSelectionStrategyDescription[] =
    "Controls how text selection granularity changes when touch text selection "
    "handles are dragged. Non-default behavior is experimental.";
const char kTouchSelectionStrategyCharacter[] = "Character";
const char kTouchSelectionStrategyDirection[] = "Direction";

const char kTraceUploadUrlName[] = "Trace label for navigation tracing";
const char kTraceUploadUrlDescription[] =
    "This is to be used in conjunction with the enable-navigation-tracing "
    "flag. Please select the label that best describes the recorded traces. "
    "This will choose the destination the traces are uploaded to. If you are "
    "not sure, select other. If left empty, no traces will be uploaded.";
const char kTraceUploadUrlChoiceOther[] = "Other";
const char kTraceUploadUrlChoiceEmloading[] = "emloading";
const char kTraceUploadUrlChoiceQa[] = "QA";
const char kTraceUploadUrlChoiceTesting[] = "Testing";

const char kTranslateAssistContentName[] = "Translate AssistContent";
const char kTranslateAssistContentDescription[] =
    "Enables populating translate details for the current page in "
    "AssistContent.";

const char kTranslateBubbleUIName[] =
    "Select which UI to use for translate bubble";
const char kTranslateBubbleUIDescription[] =
    "Three bubble options to choose. Existing UI is selected by default";

const char kTranslateForceTriggerOnEnglishName[] =
    "Select which language model to use to trigger translate on English "
    "content";
const char kTranslateForceTriggerOnEnglishDescription[] =
    "Force the Translate Triggering on English pages experiment to be enabled "
    "with the selected language model active.";

const char kTranslateIntentName[] = "Translate intent";
const char kTranslateIntentDescription[] =
    "Enables an intent that allows Assistant to initiate a translation of the "
    "foreground tab.";

const char kTreatInsecureOriginAsSecureName[] =
    "Insecure origins treated as secure";
const char kTreatInsecureOriginAsSecureDescription[] =
    "Treat given (insecure) origins as secure origins. Multiple origins can be "
    "supplied as a comma-separated list. Origins must have their protocol "
    "specified e.g. \"http://example.com\". For the definition of secure "
    "contexts, see https://w3c.github.io/webappsec-secure-contexts/";

<<<<<<< HEAD
const char kUnifiedPasswordManagerAndroidReenrollmentName[] =
    "Automatic reenrollment of users who were evicted from using Google "
    "Mobile Services after experiencing errors.";
const char kUnifiedPasswordManagerAndroidReenrollmentDescription[] =
    "Requires UnifiedPasswordManagerAndroid flag enabled. Allows automatic "
    "reenrollment into Google Mobile Services if sync and backend "
    "communication work.";
=======
const char kTreatUnsafeDownloadsAsActiveName[] =
    "Treat risky downloads over insecure connections as active mixed content";
const char kTreatUnsafeDownloadsAsActiveDescription[] =
    "Disallows downloads of unsafe files (files that can potentially execute "
    "code), where the final download origin or any origin in the redirect "
    "chain is insecure if the originating page is secure.";
>>>>>>> chromium

const char kTrustTokensName[] = "Enable Trust Tokens";
const char kTrustTokensDescription[] =
    "Enables the prototype Trust Token API "
    "(https://github.com/wicg/trust-token-api).";

const char kTurnOffStreamingMediaCachingOnBatteryName[] =
    "Turn off caching of streaming media to disk while on battery power.";
const char kTurnOffStreamingMediaCachingOnBatteryDescription[] =
    "Reduces disk activity during media playback, which can result in "
    "power savings.";

const char kTurnOffStreamingMediaCachingAlwaysName[] =
    "Turn off caching of streaming media to disk.";
const char kTurnOffStreamingMediaCachingAlwaysDescription[] =
    "Reduces disk activity during media playback, which can result in "
    "power savings.";

const char kUnifiedPasswordManagerAndroidName[] =
    "Google Mobile Services for passwords";
const char kUnifiedPasswordManagerAndroidDescription[] =
    "Uses Google Mobile Services to store and retrieve passwords."
    "Warning: Highly experimental. May lead to loss of passwords and "
    "impact performance.";

const char kUnsafeWebGPUName[] = "Unsafe WebGPU";
const char kUnsafeWebGPUDescription[] =
    "Enables access to the experimental WebGPU API. Warning: As GPU sandboxing "
    "isn't implemented yet for the WebGPU API, it is possible to read GPU data "
    "for other processes.";
const char kUnsafeWebGPUServiceName[] = "Unsafe WebGPU Service";
const char kUnsafeWebGPUServiceDescription[] =
    "Enables access to the experimental WebGPU API on service side but not "
    "blink side."
    "This is used to test origin trial code integrations before WebGPU is "
    "enabled globally.";

const char kUnsafeFastJSCallsName[] = "Unsafe fast JS calls";
const char kUnsafeFastJSCallsDescription[] =
    "Enables experimental fast API between Blink and V8."
    "Warning: type checking, few POD types and array types "
    "are not supported yet, so crashes are possible.";

const char kUiPartialSwapName[] = "Partial swap";
const char kUiPartialSwapDescription[] = "Sets partial swap behavior.";

const char kUseFirstPartySetName[] = "First-Party Set";
const char kUseFirstPartySetDescription[] =
    "Use the provided list of origins as a First-Party Set, with the first "
    "valid origin as the owner of the set.";

<<<<<<< HEAD
const char kTPCPhaseOutFacilitatedTestingName[] =
    "Third-party Cookie Phase Out Facilitated Testing";
const char kTPCPhaseOutFacilitatedTestingDescription[] =
    "Enables third-party cookie phase out for facilitated testing described in "
    "https://developer.chrome.com/en/docs/privacy-sandbox/chrome-testing/";

const char kTpcdHeuristicsGrantsName[] =
    "Third-party Cookie Grants Heuristics Testing";
const char kTpcdHeuristicsGrantsDescription[] =
    "Enables temporary storage access grants for certain user behavior "
    "heuristics. See "
    "https://github.com/amaliev/3pcd-exemption-heuristics/blob/main/"
    "explainer.md for more details.";

const char kTpcdMetadataGrantsName[] =
    "Third-Party Cookie Deprecation Metadata Grants for Testing";
const char kTpcdMetadataGrantsDescription[] =
    "Provides a control for enabling/disabling Third-Party Cookie Deprecation "
    "Metadata Grants (WRT its default state) for testing.";

const char kTrackingProtection3pcdName[] = "Tracking Protection for 3PCD";
const char kTrackingProtection3pcdDescription[] =
    "Enables the tracking protection UI + prefs that will be used for the 3PCD "
    "1%.";

const char kUsernameFirstFlowWithIntermediateValuesPredictionsName[] =
    "Predictions on Username first flow with intermediate values";
const char kUsernameFirstFlowWithIntermediateValuesPredictionsDescription[] =
    "New single username predictions based on voting from Username First Flow "
    "with intermediate values.";

const char kUsernameFirstFlowWithIntermediateValuesVotingName[] =
    "Username first flow with intermediate values voting";
const char kUsernameFirstFlowWithIntermediateValuesVotingDescription[] =
    "Support voting on username first flow with intermediate values. Username "
    "first flow is login/sign-up flow where a user has to type username first "
    "on one page and then password on another page. Intermediate fields are "
    "usually an OTP field or CAPTCHA.";
=======
const char kUsernameFirstFlowName[] = "Username first flow voting";
const char kUsernameFirstFlowDescription[] =
    "Support of sending votes on username first flow i.e. login "
    "flows where a user has to type username first on one page and then "
    "password on another page";

const char kUsernameFirstFlowFillingName[] = "Username first flow filling";
const char kUsernameFirstFlowFillingDescription[] =
    "Support of username saving and filling on username first flow i.e. login "
    "flows where a user has to type username first on one page and then "
    "password on another page";
>>>>>>> chromium

const char kUseSearchClickForRightClickName[] =
    "Use Search+Click for right click";
const char kUseSearchClickForRightClickDescription[] =
    "When enabled search+click will be remapped to right click, allowing "
    "webpages and apps to consume alt+click. When disabled the legacy "
    "behavior of remapping alt+click to right click will remain unchanged.";

<<<<<<< HEAD
const char kVcBackgroundReplaceName[] = "Enable vc background replacement";
const char kVcBackgroundReplaceDescription[] =
    "Enables background replacement feature for video conferencing on "
    "Chromebooks. THIS WILL OVERRIDE BACKGROUND BLUR.";

const char kVcRelightingInferenceBackendName[] =
    "Select relighting backend for video conferencing";
const char kVcRelightingInferenceBackendDescription[] =
    "Select relighting backend to be used for running model inference during "
    "video conferencing, which may offload work from GPU.";

const char kVcRetouchInferenceBackendName[] =
    "Select retouch backend for video conferencing";
const char kVcRetouchInferenceBackendDescription[] =
    "Select retouch backend to be used for running model inference during "
    "video conferencing, which may offload work from GPU.";

const char kVcSegmentationInferenceBackendName[] =
    "Select segmentation backend for video conferencing";
const char kVcSegmentationInferenceBackendDescription[] =
    "Select segmentation backend to be used for running model inference "
    "during video conferencing, which may offload work from GPU.";

const char kVcStudioLookName[] = "Enables Studio Look for video conferencing";
const char kVcStudioLookDescription[] =
    "Enables Studio Look and VC settings UI, which contains settings for Studio"
    "Look.";

const char kVcSegmentationModelName[] = "Use a different segmentation model";
const char kVcSegmentationModelDescription[] =
    "Allows a different segmentation model to be used for blur and relighting, "
    "which may reduce the workload on the GPU.";

const char kVcTrayMicIndicatorName[] = "Adds a mic indicator in VC tray";
const char kVcTrayMicIndicatorDescription[] =
    "Displays a pulsing mic indicator that indicates how loud the audio is "
    "captured by the microphone, after some effects like noise cancellation "
    "is applied.";

const char kVcTrayTitleHeaderName[] = "Adds a sidetone toggle in VC tray";
const char kVcTrayTitleHeaderDescription[] =
    "Displays a sidetone toggle in VC Tray Title header";

const char kVcLightIntensityName[] = "VC relighting intensity";
const char kVcLightIntensityDescription[] =
    "Allows different light intensity to be used for relighting.";

const char kVcWebApiName[] = "VC web API";
const char kVcWebApiDescription[] =
    "Allows web API support for video conferencing on Chromebooks.";

const char kVideoPictureInPictureControlsUpdate2024Name[] =
    "Video picture-in-picture controls update 2024";
const char kVideoPictureInPictureControlsUpdate2024Description[] =
    "Displays an updated UI for video picture-in-picture controls from its 2024"
    "UI update";

=======
>>>>>>> chromium
const char kV8VmFutureName[] = "Future V8 VM features";
const char kV8VmFutureDescription[] =
    "This enables upcoming and experimental V8 VM features. "
    "This flag does not enable experimental JavaScript features.";

const char kWalletServiceUseSandboxName[] =
    "Use Google Payments sandbox servers";
const char kWalletServiceUseSandboxDescription[] =
    "For developers: use the sandbox service for Google Payments API calls.";

<<<<<<< HEAD
const char kWallpaperFastRefreshName[] =
    "Enable shortened wallpaper daily refresh interval for manual testing";
const char kWallpaperFastRefreshDescription[] =
    "Allows developers to see a new wallpaper once every ten seconds rather "
    "than once per day when using the daily refresh feature.";

const char kWallpaperGooglePhotosSharedAlbumsName[] =
    "Enable Google Photos shared albums for wallpaper";
const char kWallpaperGooglePhotosSharedAlbumsDescription[] =
    "Allow users to set shared Google Photos albums as the source for their "
    "wallpaper.";

const char kWallpaperSearchSettingsVisibilityName[] =
    "Wallpaper Search Settings Visibility";
const char kWallpaperSearchSettingsVisibilityDescription[] =
    "Shows wallpaper search settings in settings UI.";

#if !BUILDFLAG(IS_ANDROID)
const char kWebAuthnUsePasskeyFromAnotherDeviceInContextMenuName[] =
    "Use passkey from another device in the context menu";
const char kWebAuthnUsePasskeyFromAnotherDeviceInContextMenuDescription[] =
    "Hides the \"Use a passkey\" entry from the autofill popup for conditional "
    "WebAuthn requests. Moves the entry point to the context menu.";
const char kWebAuthnEnclaveAuthenticatorName[] =
    "Enable the cloud enclave authenticator for GPM passkeys";
const char kWebAuthnEnclaveAuthenticatorDescription[] =
    "Allow users to create and use Google Password Manager passkeys using a "
    "cloud-based authenticator service.";
const char kWebAuthnPasskeyUpgradeName[] =
    "Enable automatic passkey upgrades in Google Password Manager";
const char kWebAuthnPasskeyUpgradeDescription[] =
    "Enable the WebAuthn Conditional Create feature and let websites "
    "automatically create passkeys in GPM if there is a matching password "
    "credential for the same user.";
#endif

const char kWebBluetoothName[] = "Web Bluetooth";
const char kWebBluetoothDescription[] =
    "Enables the Web Bluetooth API on platforms without official support";
=======
const char kWallpaperWebUIName[] = "Enable new wallpaper experience";
const char kWallpaperWebUIDescription[] =
    "Enables the wallpaper picker "
    "in ChromeOS Settings";
>>>>>>> chromium

const char kWebBluetoothNewPermissionsBackendName[] =
    "Use the new permissions backend for Web Bluetooth";
const char kWebBluetoothNewPermissionsBackendDescription[] =
    "Enables the new permissions backend for Web Bluetooth. This will enable "
    "persistent storage of device permissions.";

const char kWebBundlesName[] = "Web Bundles";
const char kWebBundlesDescription[] =
    "Enables experimental supports for Web Bundles (Bundled HTTP Exchanges) "
    "navigation.";

const char kWebIdName[] = "WebID";
const char kWebIdDescription[] =
    "Enables WebID HTTP filtering and JavaScript "
    "API to intermediate federated identity requests.";

const char kWebOtpBackendName[] = "Web OTP";
const char kWebOtpBackendDescription[] =
    "Enables Web OTP API that uses the specified backend.";
const char kWebOtpBackendSmsVerification[] = "Code Browser API";
const char kWebOtpBackendUserConsent[] = "User Consent API";
const char kWebOtpBackendAuto[] = "Automatically select the backend";

const char kWebglDeveloperExtensionsName[] = "WebGL Developer Extensions";
const char kWebglDeveloperExtensionsDescription[] =
    "Enabling this option allows web applications to access WebGL extensions "
    "intended only for use during development time.";

const char kWebglDraftExtensionsName[] = "WebGL Draft Extensions";
const char kWebglDraftExtensionsDescription[] =
    "Enabling this option allows web applications to access the WebGL "
    "extensions that are still in draft status.";

const char kWebPaymentsExperimentalFeaturesName[] =
    "Experimental Web Payments API features";
const char kWebPaymentsExperimentalFeaturesDescription[] =
    "Enable experimental Web Payments API features";

const char kWebPaymentsMinimalUIName[] = "Web Payments Minimal UI";
const char kWebPaymentsMinimalUIDescription[] =
    "Allow Payment Request API to open a minimal UI to replace the Payment "
    "Request UI when appropriate.";

const char kAppStoreBillingDebugName[] =
    "Web Payments App Store Billing Debug Mode";
const char kAppStoreBillingDebugDescription[] =
    "App-store purchases (e.g., Google Play Store) within a TWA can be "
    "requested using the Payment Request API. This flag removes the "
    "restriction that the TWA has to be installed from the app-store.";

const char kWebrtcCaptureMultiChannelApmName[] =
    "WebRTC multi-channel capture audio processing.";
const char kWebrtcCaptureMultiChannelApmDescription[] =
    "Support in WebRTC for processing capture audio in multi channel without "
    "downmixing when running APM in the render process.";

const char kWebrtcHideLocalIpsWithMdnsName[] =
    "Anonymize local IPs exposed by WebRTC.";
const char kWebrtcHideLocalIpsWithMdnsDecription[] =
    "Conceal local IP addresses with mDNS hostnames.";

const char kWebrtcHybridAgcName[] = "WebRTC hybrid Agc2/Agc1.";
const char kWebrtcHybridAgcDescription[] =
    "WebRTC Agc2 digital adaptation with Agc1 analog adaptation.";

const char kWebrtcAnalogAgcClippingControlName[] =
    "WebRTC Agc1 analog clipping control.";
const char kWebrtcAnalogAgcClippingControlDescription[] =
    "WebRTC Agc1 analog clipping controller to reduce saturation.";

const char kWebrtcHwDecodingName[] = "WebRTC hardware video decoding";
const char kWebrtcHwDecodingDescription[] =
    "Support in WebRTC for decoding video streams using platform hardware.";

const char kWebrtcHwEncodingName[] = "WebRTC hardware video encoding";
const char kWebrtcHwEncodingDescription[] =
    "Support in WebRTC for encoding video streams using platform hardware.";

<<<<<<< HEAD
=======
const char kWebRtcRemoteEventLogName[] = "WebRTC remote-bound event logging";
const char kWebRtcRemoteEventLogDescription[] =
    "Allow collecting WebRTC event logs and uploading them to Crash. "
    "Please note that, even if enabled, this will still require "
    "a policy to be set, for it to have an effect.";

const char kWebrtcSrtpAesGcmName[] =
    "Negotiation with GCM cipher suites for SRTP in WebRTC";
const char kWebrtcSrtpAesGcmDescription[] =
    "When enabled, WebRTC will try to negotiate GCM cipher suites for SRTP.";

>>>>>>> chromium
const char kWebrtcUseMinMaxVEADimensionsName[] =
    "WebRTC Min/Max Video Encode Accelerator dimensions";
const char kWebrtcUseMinMaxVEADimensionsDescription[] =
    "When enabled, WebRTC will only use the Video Encode Accelerator for "
    "video resolutions inside those published as supported.";

const char kWebXrForceRuntimeName[] = "Force WebXr Runtime";
const char kWebXrForceRuntimeDescription[] =
    "Force the browser to use a particular runtime, even if it would not "
    "usually be enabled or would otherwise not be selected based on the "
    "attached hardware.";

const char kWebXrRuntimeChoiceNone[] = "No Runtime";
const char kWebXrRuntimeChoiceOpenXR[] = "OpenXR";

const char kWebXrHandAnonymizationStrategyName[] =
    "WebXr Hand Anonymization Strategy";
const char kWebXrHandAnonymizationStrategyDescription[] =
    "Force the browser to use a particular strategy for anonymizing hand data, "
    "the default order has a hierarchy of strategies to try and if all of them "
    "fail, then no data will be returned, while this choice does allow the "
    "(not recommended) alternative of bypassing these algorithms all together.";

const char kWebXrHandAnonymizationChoiceNone[] = "None (Not Recommended)";
const char kWebXrHandAnonymizationChoiceRuntime[] = "Runtime Provided";
const char kWebXrHandAnonymizationChoiceFallback[] = "Chrome Fallback";

const char kWebXrIncubationsName[] = "WebXR Incubations";
const char kWebXrIncubationsDescription[] =
    "Enables experimental features for WebXR.";

const char kWindowNamingName[] = "Window Naming";
const char kWindowNamingDescription[] =
    "Whether the window naming UI is enabled.";

const char kZeroCopyName[] = "Zero-copy rasterizer";
const char kZeroCopyDescription[] =
    "Raster threads write directly to GPU memory associated with tiles.";

const char kEnableVulkanName[] = "Vulkan";
const char kEnableVulkanDescription[] = "Use vulkan as the graphics backend.";

const char kSharedHighlightingUseBlocklistName[] =
    "Shared Highlighting blocklist";
const char kSharedHighlightingUseBlocklistDescription[] =
    "Uses a blocklist to disable Shared Highlighting link generation on "
    "certain sites where personalized or dynamic content or other technical "
    "restrictions make it unlikely that a URL can be generated and actually "
    "work when shared.";

const char kSharedHighlightingV2Name[] = "Shared Highlighting 2.0";
const char kSharedHighlightingV2Description[] =
    "Improvements to Shared Highlighting. Including ability to reshare or "
    "remove a highlight.";

<<<<<<< HEAD
const char kSharedHighlightingManagerName[] = "Refactoring Shared Highlighting";
const char kSharedHighlightingManagerDescription[] =
    "Refactors Shared Highlighting by centralizing the IPC calls in a Manager.";
=======
const char kSharedHighlightingAmpName[] = "Shared Highlighting for AMP Viewers";
const char kSharedHighlightingAmpDescription[] =
    "Enables Shared Highlighting for AMP Viwers.";

const char kPreemptiveLinkToTextGenerationName[] =
    "Preemptive generation of link to text";
const char kPreemptiveLinkToTextGenerationDescription[] =
    "Enables link to text to be generated in advance.";

const char kDraw1PredictedPoint12Ms[] = "1 point 12ms ahead.";
const char kDraw2PredictedPoints6Ms[] = "2 points, each 6ms ahead.";
const char kDraw1PredictedPoint6Ms[] = "1 point 6ms ahead.";
const char kDraw2PredictedPoints3Ms[] = "2 points, each 3ms ahead.";
const char kDrawPredictedPointsDefault[] = "Disabled";
const char kDrawPredictedPointsDescription[] =
    "Draw predicted points when using the delegated ink trails API. Requires "
    "experimental web platform features to be enabled.";
const char kDrawPredictedPointsName[] = "Draw predicted delegated ink points";
>>>>>>> chromium

const char kSanitizerApiName[] = "Sanitizer API";
const char kSanitizerApiDescription[] =
    "Enable the Sanitizer API. See: https://github.com/WICG/sanitizer-api";

const char kUsePassthroughCommandDecoderName[] =
    "Use passthrough command decoder";
const char kUsePassthroughCommandDecoderDescription[] =
    "Use chrome passthrough command decoder instead of validating command "
    "decoder.";

<<<<<<< HEAD
const char kUseIDNA2008NonTransitionalName[] =
    "Enable IDNA 2008 Non-Transitional Mode";
const char kUseIDNA2008NonTransitionalDescription[] =
    "Enables IDNA 2008 in Non-Transitional Mode in URL processing, allowing "
    "deviation characters in domain names.";

const char kEnablePasswordSharingName[] = "Enables password sharing";
const char kEnablePasswordSharingDescription[] =
    "Enables sharing of password between members of the same family.";

const char kEnableMantaServiceName[] = "Enable Manta Service";
const char kEnableMantaServiceDescription[] =
    "Enables the profile keyed Manta service at startup.";

const char kPredictableReportedQuotaName[] = "Predictable Reported Quota";
const char kPredictableReportedQuotaDescription[] =
    "Enables reporting of a predictable quota from the StorageManager's "
    "estimate API. This flag is intended only for validating if this change "
    "caused an unforeseen bug.";

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_CHROMEOS)
const char kRunVideoCaptureServiceInBrowserProcessName[] =
    "Run video capture service in browser";
const char kRunVideoCaptureServiceInBrowserProcessDescription[] =
    "Run the video capture service in the browser process.";
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_CHROMEOS)

const char kPromptAPIForGeminiNanoName[] = "Prompt API for Gemini Nano";
const char kPromptAPIForGeminiNanoDescription[] =
    "Enables the exploratory Prompt API, allowing you to send natural language "
    "instructions to a built-in large language model (Gemini Nano in Chrome). "
    "Exploratory APIs are designed for local prototyping to help discover "
    "potential use cases, and may never launch. These explorations will inform "
    "the built-in AI roadmap [1]. "
    "This API is primarily intended for natural language processing tasks such "
    "as summarizing, classifying, or rephrasing text. It is NOT suitable for "
    "use cases that require factual accuracy (e.g. answering knowledge "
    "questions). "
    "You must comply with our Prohibited Use Policy [2] which provides "
    "additional details about appropriate use of Generative AI.";
const char* const kAIAPIsForGeminiNanoLinks[2] = {
    "https://goo.gle/chrome-ai-dev-preview",
    "https://policies.google.com/terms/generative-ai/use-policy"};

const char kPromptAPIForGeminiNanoMultimodalInputName[] =
    "Prompt API for Gemini Nano with Multimodal Input";
const char kPromptAPIForGeminiNanoMultimodalInputDescription[] =
    "Extends the exploratory Prompt API with image and audio input types. "
    "Allows you to supplement natural language instructions for a built-in "
    "large language model (Gemini Nano in Chrome) with image and audio inputs. "
    "Exploratory APIs are designed for local prototyping to help discover "
    "potential use cases, and may never launch. These explorations will inform "
    "the built-in AI roadmap [1]. "
    "This API enhancement is primarily intended for natural language "
    "processing tasks associated with visual and auditory data, such as "
    "generating rough descriptions of pictures and sounds. It is NOT suitable "
    "for use cases that require factual accuracy (e.g. answering knowledge "
    "questions). "
    "You must comply with our Prohibited Use Policy [2] which provides "
    "additional details about appropriate use of Generative AI.";

const char kSummarizationAPIForGeminiNanoName[] =
    "Summarization API for Gemini Nano";
const char kSummarizationAPIForGeminiNanoDescription[] =
    "Enables the Summarization API, allowing you to summarize a piece "
    "of text with a built-in large language model (Gemini Nano in Chrome)."
    "The API may be subject to changes including the supported options."
    "Please refer to the built-in AI article [1] for details. "
    "This API It is NOT suitable for use cases that require factual accuracy "
    "(e.g. answering knowledge questions). "
    "You must comply with our Prohibited Use Policy [2] which provides "
    "additional details about appropriate use of Generative AI.";

const char kWriterAPIForGeminiNanoName[] = "Writer API for Gemini Nano";
const char kWriterAPIForGeminiNanoDescription[] =
    "Enables the Writer API, allowing you to write a piece "
    "of text with a built-in large language model (Gemini Nano in Chrome)."
    "The API may be subject to changes including the supported options."
    "Please refer to the built-in AI article [1] for details. "
    "You must comply with our Prohibited Use Policy [2] which provides "
    "additional details about appropriate use of Generative AI.";

const char kRewriterAPIForGeminiNanoName[] = "Rewriter API for Gemini Nano";
const char kRewriterAPIForGeminiNanoDescription[] =
    "Enables the Rewriter API, allowing you to rewrite a piece "
    "of text with a built-in large language model (Gemini Nano in Chrome)."
    "The API may be subject to changes including the supported options."
    "Please refer to the built-in AI article [1] for details. "
    "You must comply with our Prohibited Use Policy [2] which provides "
    "additional details about appropriate use of Generative AI.";
=======
const char kExtensionWorkflowJustificationName[] =
    "Extension request justification";
const char kExtensionWorkflowJustificationDescription[] =
    "Enables users to justify their extension requests by causing a text field "
    "to appear on the extension request dialog.";
>>>>>>> chromium

// Android ---------------------------------------------------------------------

#if defined(OS_ANDROID)

<<<<<<< HEAD
const char kAccessibilityDeprecateTypeAnnounceName[] =
    "Accessibility Deprecate TYPE_ANNOUNCE";
const char kAccessibilityDeprecateTypeAnnounceDescription[] =
    "When enabled, TYPE_ANNOUNCE events will no longer be sent for live "
    "regions in the web contents.";

const char kAccessibilityIncludeLongClickActionName[] =
    "Accessibility Include Long Click Action";
const char kAccessibilityIncludeLongClickActionDescription[] =
    "When enabled, the accessibility tree for the web contents will include "
    "the ACTION_LONG_CLICK action on all relevant nodes.";
=======
const char kAddToHomescreenIPHName[] = "Add to homescreen IPH";
const char kAddToHomescreenIPHDescription[] =
    " Shows in-product-help messages educating users about add to homescreen "
    "option in chrome.";
>>>>>>> chromium

const char kAImageReaderName[] = "Android ImageReader";
const char kAImageReaderDescription[] =
    " Enables MediaPlayer and MediaCodec to use AImageReader on Android. "
    " This feature is only available for android P+ devices. Disabling it also "
    " disables SurfaceControl.";

<<<<<<< HEAD
const char kAccessibilityUnifiedSnapshotsName[] =
    "Accessibility Unified Snapshots";
const char kAccessibilityUnifiedSnapshotsDescription[] =
    "When enabled, use the experimental unified code path for AXTree "
    "snapshots.";
=======
const char kAndroidDetailedLanguageSettingsName[] =
    "Detailed Language Settings";
const char kAndroidDetailedLanguageSettingsDescription[] =
    "Enable the new detailed language settings page";

const char kAndroidForceAppLanguagePromptName[] =
    "Force second run app language prompt";
const char kAndroidForceAppLanguagePromptDescription[] =
    "When enabled the app language prompt to change the UI language will"
    "always be shown.";
>>>>>>> chromium

const char kAndroidLayoutChangeTabReparentingName[] =
    "Android Chrome UI phone/tablet layout change tab reparenting";
const char kAndroidLayoutChangeTabReparentingDescription[] =
    "If enabled, when the screen size switches between phone and tablet size, "
    "the UI layout updates to the proper one and the current tabs are "
    "reparented instead of reloaded.";

const char kAndroidSurfaceControlName[] = "Android SurfaceControl";
const char kAndroidSurfaceControlDescription[] =
    " Enables SurfaceControl to manage the buffer queue for the "
    " DisplayCompositor on Android. This feature is only available on "
    " android Q+ devices";

const char kAssistantIntentPageUrlName[] =
    "Include page URL in Assistant intent";
const char kAssistantIntentPageUrlDescription[] =
    "Include the current page's URL in the Assistant voice transcription "
    "intent.";

const char kAssistantIntentTranslateInfoName[] =
    "Translate info in Assistant intent";
const char kAssistantIntentTranslateInfoDescription[] =
    "Include page translation details in the Assistant voice transcription "
    "intent. This includes the page's URL and its original, current, and "
    "default target language.";

const char kAsyncDnsName[] = "Async DNS resolver";
const char kAsyncDnsDescription[] = "Enables the built-in DNS resolver.";

const char kAutofillAccessoryViewName[] =
    "Autofill suggestions as keyboard accessory view";
const char kAutofillAccessoryViewDescription[] =
    "Shows Autofill suggestions on top of the keyboard rather than in a "
    "dropdown.";

<<<<<<< HEAD
const char kAndroidPdfAssistContentName[] = "Provide assist content for PDF";
const char kAndroidPdfAssistContentDescription[] =
    "Provide assist content for PDF on Android.";

const char kChromePageInfoSharingName[] = "Page Info Sharing";
const char kChromePageInfoSharingDescription[] =
    "Enable Page Info Sharing on Android.";
=======
const char kAutofillAssistantDirectActionsName[] =
    "Autofill Assistant direct actions";
const char kAutofillAssistantDirectActionsDescription[] =
    "When enabled, expose direct actions from the Autofill Assistant.";
>>>>>>> chromium

const char kAutofillUseMobileLabelDisambiguationName[] =
    "Autofill Uses Mobile Label Disambiguation";
const char kAutofillUseMobileLabelDisambiguationDescription[] =
    "When enabled, Autofill suggestions' labels are displayed using a "
    "mobile-friendly format.";

const char kAppMenuMobileSiteOptionName[] =
    "Show Mobile Site option in app menu";
const char kAppMenuMobileSiteOptionDescription[] =
    "When enabled, app menu should show 'Mobile site' when showing desktop "
    "site, instead of showing 'Desktop Site' with checkbox";

<<<<<<< HEAD
const char kAndroidTabDeclutterArchiveDuplicateTabsName[] =
    "Archive all duplicate tabs.";
const char kAndroidTabDeclutterArchiveDuplicateTabsDescription[] =
    "Enables auto-archival of all duplicate tabs except the most recently used "
    "copy.";

const char kAnimatedImageDragShadowName[] =
    "Enable animated image drag shadow on Android.";
const char kAnimatedImageDragShadowDescription[] =
    "Animate the shadow image from its original bound to the touch point. ";
=======
const char kBentoOfflineName[] =
    "Enables an experiment for Offline Bento content on Android";
const char kBentoOfflineDescription[] =
    "Enables displaying Bento content on the offline page for Android.";
>>>>>>> chromium

const char kBookmarkBottomSheetName[] = "Enables bookmark bottom sheet";
const char kBookmarkBottomSheetDescription[] =
    "Enables showing a bookmark bottom sheet when adding a bookmark.";

<<<<<<< HEAD
const char kAppSpecificHistoryName[] = "Allow app specific history";
const char kAppSpecificHistoryDescription[] =
    "If enabled, history results will also be categorized by application.";

const char kBoardingPassDetectorName[] = "Boarding Pass Detector";
const char kBoardingPassDetectorDescription[] = "Enable Boarding Pass Detector";

const char kBookmarkPaneAndroidName[] = "Bookmark hub pane";
const char kBookmarkPaneAndroidDescription[] = "Enables a bookmark hub pane.";

const char kCCTAuthTabName[] = "CCT Auth Tab";
const char kCCTAuthTabDescription[] = "Enable AuthTab used for authentication";

const char kCCTAuthTabDisableAllExternalIntentsName[] =
    "Disable all external intents in Auth Tab";
const char kCCTAuthTabDisableAllExternalIntentsDescription[] =
    "Disables all external intents in Auth Tab";

const char kCCTAuthTabEnableHttpsRedirectsName[] =
    "Enable HTTPS redirect scheme in Auth Tab";
const char kCCTAuthTabEnableHttpsRedirectsDescription[] =
    "Enables HTTPS redirect scheme in Auth Tab";

const char kCCTBeforeUnloadName[] = "CCT before unload";
const char kCCTBeforeUnloadDescription[] =
    "Kill switch for new CCT before unload behavior during back press";

const char kCCTEphemeralMediaViewerExperimentName[] =
    "Ephemeral CCT for Media Viewer";
const char kCCTEphemeralMediaViewerExperimentDescription[] =
    "Enables Media Viewer launched from Downloads to open in Ephemeral "
    "mode.";

const char kCCTEphemeralModeName[] =
    "Allow CCT embedders to open CCTs in ephemeral mode";
const char kCCTEphemeralModeDescription[] =
    "Enabling it would allow apps to open ephemeral mode for "
    "Chrome Custom Tabs, on Android.";
=======
const char kCCTIncognitoName[] = "Chrome Custom Tabs Incognito mode";
const char kCCTIncognitoDescription[] =
    "Enables incognito mode for Chrome Custom Tabs, on Android.";
>>>>>>> chromium

const char kCCTIncognitoAvailableToThirdPartyName[] =
    "Allow third party to open Custom Tabs Incognito mode";
const char kCCTIncognitoAvailableToThirdPartyDescription[] =
    "Enabling it would allow third party apps to open incognito mode for "
    "Chrome Custom Tabs, on Android.";

<<<<<<< HEAD
const char kCCTMinimizedName[] = "Allow Custom Tabs to be minimized";
const char kCCTMinimizedDescription[] =
    "When enabled, CCTs can be minimized into picture-in-picture (PiP) mode.";

const char kCCTNestedSecurityIconName[] =
    "Nest the CCT security icon under the title.";
const char kCCTNestedSecurityIconDescription[] =
    "When enabled, the CCT toolbar security icon will be nested under the "
    "title.";

const char kCCTGoogleBottomBarName[] = "Google Bottom Bar";
const char kCCTGoogleBottomBarDescription[] =
    "Show bottom bar on Custom Tabs opened by the Android Google App.";

const char kCCTGoogleBottomBarVariantLayoutsName[] =
    "Google Bottom Bar Variant Layouts";
const char kCCTGoogleBottomBarVariantLayoutsDescription[] =
    "Show different layouts on Google Bottom Bar.";

const char kCCTOpenInBrowserButtonIfAllowedByEmbedderName[] =
    "Open in Browser Button in CCT if allowed by Embedder";
const char kCCTOpenInBrowserButtonIfAllowedByEmbedderDescription[] =
    "Open in Browser Button in CCT if allowed by Embedder";

const char kCCTOpenInBrowserButtonIfEnabledByEmbedderName[] =
    "Open in Browser Button in CCT if enabled by Embedder";
const char kCCTOpenInBrowserButtonIfEnabledByEmbedderDescription[] =
    "Open in Browser Button in CCT if enabled by Embedder";

const char kCCTResizableForThirdPartiesName[] =
    "Bottom sheet Custom Tabs (third party)";
const char kCCTResizableForThirdPartiesDescription[] =
    "Enable bottom sheet Custom Tabs for third party apps.";

const char kCCTRevampedBrandingName[] = "Revamped CCT toolbar branding.";
const char kCCTRevampedBrandingDescription[] =
    "Enables a revamped branding animation on the CCT toolbar.";

const char kCCTSignInPromptName[] = "Sign-in prompt in CCT.";
const char kCCTSignInPromptDescription[] =
    "Displays a sign-in prompt message in CCT opened by 1P apps when the user "
    "is signed out of Chrome but signed in to the 1P app.";

const char kBottomBrowserControlsRefactorName[] =
    "BottomBrowserControlsRefactor";
const char kBottomBrowserControlsRefactorDescription[] =
    "Use BottomControlsStacker to position bottom controls layers.";

const char kBrowsingDataModelName[] = "Browsing Data Model";
const char kBrowsingDataModelDescription[] = "Enables BDM on Android.";
=======
const char kCCTTargetTranslateLanguageName[] =
    "Chrome Custom Tabs Target Translate Language";
const char kCCTTargetTranslateLanguageDescription[] =
    "Enables specify target language the page should be translated to "
    "in Chrome Custom Tabs.";
>>>>>>> chromium

const char kChimeAlwaysShowNotificationDescription[] =
    "A debug flag to always show Chime notification after receiving a payload.";
const char kChimeAlwaysShowNotificationName[] =
    "Always show Chime notification";

const char kChimeAndroidSdkDescription[] =
    "Enable Chime SDK to receive push notification.";
const char kChimeAndroidSdkName[] = "Use Chime SDK";

<<<<<<< HEAD
const char kClankDefaultBrowserPromoName[] = "Clank default browser promo 2";
const char kClankDefaultBrowserPromoDescription[] =
    "When enabled, show additional non-intrusive entry points to allow users "
    "to set Chrome as their default browser, if the trigger conditions are "
    "met.";

const char kClankDefaultBrowserPromoRoleManagerName[] =
    "Clank default browser Promo Role Manager ";
const char kClankDefaultBrowserPromoRoleManagerDescription[] =
    "Sets the Role Manager Default Browser Promo for testing the new "
    "Default Browser Promo Feature";

const char kTabStateFlatBufferName[] = "Enable TabState FlatBuffer";
const char kTabStateFlatBufferDescription[] =
    "Migrates TabState from a pickle based schema to a FlatBuffer based "
    "schema.";

const char kContextualSearchSuppressShortViewName[] =
    "Contextual Search suppress short view";
const char kContextualSearchSuppressShortViewDescription[] =
    "Contextual Search suppress when the base page view is too short";

const char kConvertTrackpadEventsToMouseName[] =
    "Convert trackpad events to mouse events";
const char kConvertTrackpadEventsToMouseDescription[] =
    "Convert trackpad events to mouse events to improve gesture support";

const char kDeprecatedExternalPickerFunctionName[] =
    "Use deprecated External Picker method";
const char kDeprecatedExternalPickerFunctionDescription[] =
    "Use the old-style opening of an External Picker when uploading files";

const char kDrawCutoutEdgeToEdgeName[] = "DrawCutoutEdgeToEdge";
const char kDrawCutoutEdgeToEdgeDescription[] =
    "Enables the Android feature Edge-to-Edge Feature to coordinate with the "
    "Display Cutout for the notch when drawing below the Nav Bar.";

const char kDrawKeyNativeEdgeToEdgeName[] = "DrawKeyNativeEdgeToEdge";
const char kDrawKeyNativeEdgeToEdgeDescription[] =
    "Enables the Android feature Edge-to-Edge and forces a draw ToEdge on "
    "select native pages. No effect when EdgeToEdgeBottomChin is disabled";

const char kEdgeToEdgeBottomChinName[] = "EdgeToEdgeBottomChin";
const char kEdgeToEdgeBottomChinDescription[] =
    "Enables the scrollable bottom chin for an intermediate Edge-to-Edge "
=======
const char kContinuousSearchName[] = "Continuous Search Navigation";
const char kContinuousSearchDescription[] =
    "Enables caching of search results to permit a more seamless search "
>>>>>>> chromium
    "experience.";

const char kChromeShareHighlightsAndroidName[] =
    "Chrome Share text highlights on Android";
const char kChromeShareHighlightsAndroidDescription[] =
    "Enables UI to generate and share link to text highlights on Android";

<<<<<<< HEAD
const char kEdgeToEdgeSafeAreaConstraintName[] = "EdgeToEdgeSafeAreaConstraint";
const char kEdgeToEdgeSafeAreaConstraintDescription[] =
    "Ensure web content is constrained to within the safe area if safe area "
    "constraint is presents on a given web page.";

const char kEdgeToEdgeWebOptInName[] = "EdgeToEdgeWebOptIn";
const char kEdgeToEdgeWebOptInDescription[] =
    "Enables Chrome to draw below the Nav Bar on websites that have explicitly "
    "opted into Edge-to-Edge. Requires DrawCutoutEdgeToEdge to also be "
    "enabled. No effect when EdgeToEdgeBottomChin is disabled";

const char kTabClosureMethodRefactorName[] = "Tab closure method refactor";
const char kTabClosureMethodRefactorDescription[] =
    "Enables the refactored changes for tab closure methods where existing "
    "methods usages are switched off and newly introduced are made active.";
=======
const char kChromeShareLongScreenshotName[] = "Chrome Share Long Screenshots";
const char kChromeShareLongScreenshotDescription[] =
    "Enables UI to edit and share long screenshots on Android";
>>>>>>> chromium

const char kChromeShareScreenshotName[] = "Chrome Share Screenshots";
const char kChromeShareScreenshotDescription[] =
    "Enables UI to edit and share screenshots";

<<<<<<< HEAD
const char kDynamicSafeAreaInsetsOnScrollName[] =
    "DynamicSafeAreaInsetsOnScroll";
const char kDynamicSafeAreaInsetsOnScrollDescription[] =
    "Dynamically change the safe area insets on the main thread as browser "
    "controls scrolls. "
    "Requires DynamicSafeAreaInsets to also be enabled.";

const char kDynamicSafeAreaInsetsSupportedByCCName[] =
    "DynamicSafeAreaInsetsSupportedByCC";
const char kDynamicSafeAreaInsetsSupportedByCCDescription[] =
    "Dynamically change the safe area insets on the compositor thread as "
    "browser controls are shown or hidden during scroll. "
    "Requires DynamicSafeAreaInsets to also be enabled.";
=======
const char kChromeSharingHubName[] = "Chrome Sharing Hub";
const char kChromeSharingHubDescription[] =
    "Enables the Chrome Sharing Hub/custom share sheet for Android.";
>>>>>>> chromium

const char kClipboardSuggestionContentHiddenName[] =
    "Clipboard suggestion content hidden";
const char kClipboardSuggestionContentHiddenDescription[] =
    "Prevents the Clipboard suggestion from proactively retrieving the "
    "clipboard content.";

const char kCloseTabSuggestionsName[] = "Suggest to close Tabs";
const char kCloseTabSuggestionsDescription[] =
    "Suggests to the user to close Tabs that haven't been used beyond a "
    "configurable threshold or where duplicates of Tabs exist. "
    "The threshold is configurable.";

const char kCriticalPersistedTabDataName[] = "Enable CriticalPersistedTabData";
const char kCriticalPersistedTabDataDescription[] =
    "A new method of persisting Tab data across restarts has been devised "
    "and implemented. This actives the new approach.";

const char kContextMenuPerformanceInfoAndRemoteHintFetchingName[] =
    "Context menu performance info and remote hint fetching";
const char kContextMenuPerformanceInfoAndRemoteHintFetchingDescription[] =
    "Enables showing link performance information in the context menu and "
    "allows communicating with Google servers to fetch performance information "
    "for the main frame URL.";

const char kContextualSearchDebugName[] = "Contextual Search debug";
const char kContextualSearchDebugDescription[] =
    "Enables internal debugging of Contextual Search behavior on the client "
    "and server.";

const char kContextualSearchForceCaptionName[] =
    "Contextual Search force a caption";
const char kContextualSearchForceCaptionDescription[] =
    "Forces a caption to always be shown in the Touch to Search Bar.";

const char kContextualSearchLiteralSearchTapName[] =
    "Contextual Search literal search with tap";
const char kContextualSearchLiteralSearchTapDescription[] =
    "Enables Contextual Search to be activated with a single tap and produce "
    "a literal search. This is intended to be used in conjunction with the "
    "long-press resolve feature to allow both gestures to trigger a form of "
    "Touch to Search.";

const char kContextualSearchLongpressResolveName[] =
    "Contextual Search long-press Resolves";
const char kContextualSearchLongpressResolveDescription[] =
    "Enables communicating with Google servers when a long-press gesture is "
    "recognized under some privacy-limited conditions, including having Touch "
    "to Search enabled in preferences. The page context data sent to Google is "
    "potentially privacy sensitive!  This disables the tap gesture from "
    "triggering Touch to Search unless that experiment arm is enabled.";

const char kContextualSearchMlTapSuppressionName[] =
    "Contextual Search ML tap suppression";
const char kContextualSearchMlTapSuppressionDescription[] =
    "Enables tap gestures to be suppressed to improve CTR by applying machine "
    "learning.  The \"Contextual Search Ranker prediction\" flag must also be "
    "enabled!";

const char kContextualSearchRankerQueryName[] =
    "Contextual Search Ranker prediction";
const char kContextualSearchRankerQueryDescription[] =
    "Enables prediction of tap gestures using Assist-Ranker machine learning.";

const char kContextualSearchSecondTapName[] =
    "Contextual Search second tap triggering";
const char kContextualSearchSecondTapDescription[] =
    "Enables triggering on a second tap gesture even when Ranker would "
    "normally suppress that tap.";

const char kContextualSearchThinWebViewImplementationName[] =
    "Use Contextual Search ThinWebView implementation";
const char kContextualSearchThinWebViewImplementationDescription[] =
    "Use ThinWebView and BottomSheet based implementation for Contextual"
    "Search.";

const char kContextualSearchTranslationsName[] =
    "Contextual Search translations";
const char kContextualSearchTranslationsDescription[] =
    "Enables automatic translations of words on a page to be presented in the "
    "caption of the bottom bar.";

const char kCpuAffinityRestrictToLittleCoresName[] = "Restrict to LITTLE cores";
const char kCpuAffinityRestrictToLittleCoresDescription[] =
    "Restricts Chrome threads to LITTLE cores on devices with big.LITTLE or "
    "similar CPU architectures.";

const char kDecoupleSyncFromAndroidAutoSyncName[] =
    "Enable Chrome Sync decoupling from Android auto-sync";
const char kDecoupleSyncFromAndroidAutoSyncDescription[] =
    "Causes Chrome to disappear from the list of auto-sync apps in Android "
    "settings. Sync will no longer be disabled when master sync is disabled, "
    "provided that Chrome is run at least once with master sync enabled.";

const char kDirectActionsName[] = "Direct actions";
const char kDirectActionsDescription[] =
    "Enables direct actions (Android Q and more).";

const char kDynamicColorAndroidName[] = "Dynamic colors on Android";
const char kDynamicColorAndroidDescription[] =
    "Enabled dynamic colors on supported devices, such as Pixel devices "
    "running Android 12.";

const char kAutofillManualFallbackAndroidName[] =
    "Enable Autofill manual fallback for Addresses and Payments (Android)";
const char kAutofillManualFallbackAndroidDescription[] =
    "If enabled, adds toggle for addresses and payments bottom sheet to the "
    "keyboard accessory.";

const char kEnableAutofillRefreshStyleName[] =
    "Enable Autofill refresh style (Android)";
const char kEnableAutofillRefreshStyleDescription[] =
    "Enable modernized style for Autofill on Android";

const char kEnableAndroidSpellcheckerDescription[] =
    "Enables use of the Android spellchecker.";

const char kEnableCommandLineOnNonRootedName[] =
    "Enable command line on non-rooted devices";
const char kEnableCommandLineOnNoRootedDescription[] =
    "Enable reading command line file on non-rooted devices (DANGEROUS).";

<<<<<<< HEAD
const char kEnableClipboardDataControlsAndroidName[] =
    "Enable enterprise data controls.";
const char kEnableClipboardDataControlsAndroidDescription[] =
    "Enables the enterprise data controls on Android for restricting copy and "
    "paste actions for the clipboard.";
=======
const char kEnableUseAaudioDriverName[] = "Use AAudio Driver";
const char kEnableUseAaudioDriverDescription[] =
    "Enable the use of AAudio, if supported by the current Android version.";

const char kExploreSitesName[] = "Explore websites";
const char kExploreSitesDescription[] =
    "Enables portal from new tab page to explore websites.";
>>>>>>> chromium

const char kFeedInteractiveRefreshName[] = "Refresh feeds";
const char kFeedInteractiveRefreshDescription[] =
    "Enables refreshing feeds triggered by the users.";

const char kFillingPasswordsFromAnyOriginName[] =
    "Filling passwords from any origin";
const char kFillingPasswordsFromAnyOriginDescription[] =
    "Enabling this flag adds a button to the password fallback sheet. The "
    "button opens a different sheet that allows filling a password from any "
    "origin.";

const char kHomepagePromoCardName[] =
    "Enable homepage promo card on the New Tab Page";
const char kHomepagePromoCardDescription[] =
    "Enable homepage promo card that will be shown to users with partner "
    "configured homepage.";

const char kInstanceSwitcherName[] = "Enable instance switcher";
const char kInstanceSwitcherDescription[] =
    "Enable instance switcher dialog UI that helps users manage multiple "
    "instances of Chrome.";

const char kInstantStartName[] = "Instant start";
const char kInstantStartDescription[] =
    "Show start surface before native library is loaded.";

const char kIntentBlockExternalFormRedirectsNoGestureName[] =
    "Block intents from form submissions without user gesture";
const char kIntentBlockExternalFormRedirectsNoGestureDescription[] =
    "Require a user gesture that triggered a form submission in order to "
    "allow for redirecting to an external intent.";

<<<<<<< HEAD
const char kFeedCloseRefreshName[] = "Feed-close refresh";
const char kFeedCloseRefreshDescription[] =
    "Enables scheduling a background refresh of the feed following feed use.";

const char kFeedContainmentName[] = "Feed containment";
const char kFeedContainmentDescription[] =
    "Enables putting the feed in a container.";

const char kFeedDiscoFeedEndpointName[] =
    "Feed using the DiscoFeed backend endpoint";
const char kFeedDiscoFeedEndpointDescription[] =
    "Uses the DiscoFeed endpoint for serving the feed instead of GWS.";

const char kFeedDynamicColorsName[] = "Enable dynamic colors in the feed";
const char kFeedDynamicColorsDescription[] =
    "Allows feed to fully respect dynamic colors if supported by the client.";

const char kFetchGaiaHashOnSignInName[] =
    "Enable Fetching Gaia credentials from SharedPreferences.";
const char kFetchGaiaHashOnSignInDescription[] =
    "Enable retrieving email, salt, and hashed password from SharedPreferences "
    "for password reuse detection when a user signs in.";

const char kFloatingSnackbarName[] = "FloatingSnackbar";
const char kFloatingSnackbarDescription[] =
    "Enables the snackbar to float on top of the web content.";

const char kForceListTabSwitcherName[] =
    "Force list tab switcher for low-end devices";
const char kForceListTabSwitcherDescription[] =
    "Forces the list mode of the tab switcher intended for low-end devices. "
    "This flag is intended for debugging only.";

const char kFullscreenInsetsApiMigrationName[] =
    "Migrate to the new fullscreen insets APIs";
const char kFullscreenInsetsApiMigrationDescription[] =
    "Migration from View#setSystemUiVisibility to WindowInsetsController.";

const char kFullscreenInsetsApiMigrationOnAutomotiveName[] =
    "Migrate to the new fullscreen insets APIs on automotive";
const char kFullscreenInsetsApiMigrationOnAutomotiveDescription[] =
    "Migration from View#setSystemUiVisibility to WindowInsetsController on "
    "automotive.";

const char kGtsCloseTabAnimationName[] =
    "Grid tab switcher close tab animation";
const char kGtsCloseTabAnimationDescription[] =
    "New grid tab switcher close tab animation.";

const char kRefreshFeedOnRestartName[] = "Enable refreshing feed on restart";
const char kRefreshFeedOnRestartDescription[] =
    "Refresh feed when Chrome restarts.";
=======
const char kInterestFeedContentSuggestionsDescription[] =
    "Use the interest feed to render content suggestions. Currently "
    "content "
    "suggestions are shown on the New Tab Page.";
const char kInterestFeedContentSuggestionsName[] =
    "Interest Feed Content Suggestions";
>>>>>>> chromium

const char kInterestFeedV2Name[] = "Interest Feed v2";
const char kInterestFeedV2Description[] =
    "Show content suggestions on the New Tab Page and Start Surface using the "
    "new Feed Component.";

<<<<<<< HEAD
const char kLogoPolishName[] = "Logo Polish";
const char kLogoPolishDescription[] = "Enable bigger doodle size for NTP.";
=======
const char kInterestFeedV2HeartsName[] = "Interest Feed v2 Hearts";
const char kInterestFeedV2HeartsDescription[] = "Enable hearts on Feedv2.";

const char kInterestFeedV2AutoplayName[] = "Interest Feed v2 Autoplay";
const char kInterestFeedV2AutoplayDescription[] = "Enable autoplay on Feedv2.";
>>>>>>> chromium

const char kInterestFeedV1ClickAndViewActionsConditionalUploadName[] =
    "Interest Feed V1 clicks/views conditional upload";
const char kInterestFeedV1ClickAndViewActionsConditionalUploadDescription[] =
    "Only enable the upload of clicks/views in Feed V1 after reaching "
    "conditions.";

const char kInterestFeedV2ClickAndViewActionsConditionalUploadName[] =
    "Interest Feed V2 clicks/views conditional upload";
const char kInterestFeedV2ClickAndViewActionsConditionalUploadDescription[] =
    "Only enable the upload of clicks/views in Feed V2 after reaching "
    "conditions.";

const char kMessagesForAndroidInfrastructureName[] = "Messages infrastructure";
const char kMessagesForAndroidInfrastructureDescription[] =
    "When enabled, will initialize Messages UI infrastructure";

const char kMessagesForAndroidPasswordsName[] = "Passwords Messages UI";
const char kMessagesForAndroidPasswordsDescription[] =
    "When enabled, password prompt will use the new Messages UI.";

<<<<<<< HEAD
const char kSegmentationPlatformEphemeralCardRankerName[] =
    "Segmentation platform ephemeral card ranker";
const char kSegmentationPlatformEphemeralCardRankerDescription[] =
    "Enable the Ephemeral Card ranker for the segmentation platform service "
    "to rank home modules on Android.";
=======
const char kMessagesForAndroidPopupBlockedName[] = "Popup Blocked Messages UI";
const char kMessagesForAndroidPopupBlockedDescription[] =
    "When enabled, popup blocked prompt will use the new Messages UI.";
>>>>>>> chromium

const char kMessagesForAndroidReaderModeName[] = "Reader Mode Messages UI";
const char kMessagesForAndroidReaderModeDescription[] =
    "When enabled, reader mode prompt will use the new Messages UI.";

<<<<<<< HEAD
const char kNavBarColorAnimationName[] = "NavBarColorAnimation";
const char kNavBarColorAnimationDescription[] =
    "Enables animations for color changes to the OS navigation bar.";
=======
const char kMessagesForAndroidSafetyTipName[] = "Safety Tip Messages UI";
const char kMessagesForAndroidSafetyTipDescription[] =
    "When enabled, safety tip prompt will use the new Messages UI.";

extern const char kMessagesForAndroidSaveCardName[] = "Save Card Messages UI";
extern const char kMessagesForAndroidSaveCardDescription[] =
    "When enabled, save card prompt will use the new Messages UI.";
>>>>>>> chromium

const char kMessagesForAndroidUpdatePasswordName[] =
    "Update password Messages UI";
const char kMessagesForAndroidUpdatePasswordDescription[] =
    "When enabled, update password prompt will use the new Messages UI.";

const char kNewWindowAppMenuName[] = "Show a menu item 'New Window'";
const char kNewWindowAppMenuDescription[] =
    "Show a new menu item 'New Window' on tablet-sized screen when Chrome "
    "can open a new window and create a new instance in it.";

const char kOfflineIndicatorV2Name[] = "Offline indicator V2";
const char kOfflineIndicatorV2Description[] =
    "Show a persistent offline indicator when offline.";

const char kOfflinePagesLivePageSharingName[] =
    "Enables live page sharing of offline pages";
const char kOfflinePagesLivePageSharingDescription[] =
    "Enables to share current loaded page as offline page by saving as MHTML "
    "first.";

const char kAndroidPartnerCustomizationPhenotypeName[] =
    "Use homepage and bookmarks from partner customization";
const char kAndroidPartnerCustomizationPhenotypeDescription[] =
    "This flag loads a new configuration source of the default homepage and "
    "bookmarks.";

<<<<<<< HEAD
const char kOmniboxShortcutsAndroidName[] = "Omnibox shortcuts on Android";
const char kOmniboxShortcutsAndroidDescription[] =
    "Enables storing successful query/match in the omnibox shortcut database "
    "on Android";
=======
const char kPageInfoDiscoverabilityName[] = "Page info discoverability";
const char kPageInfoDiscoverabilityDescription[] =
    "Improve discoverability of permission controls in the page info bubble. "
    "After a permission decision is made, the page info icon in the address "
    "bar will show a brief animation.";

const char kPageInfoHistoryName[] = "Page info history";
const char kPageInfoHistoryDescription[] =
    "Enable a history sub page to the page info menu, and a button to forget "
    "a site, removing all preferences and history.";
>>>>>>> chromium

extern const char kPageInfoV2DesktopName[];
extern const char kPageInfoV2DesktopDescription[];

const char kPhotoPickerVideoSupportName[] = "Photo Picker Video Support";
const char kPhotoPickerVideoSupportDescription[] =
    "Enables video files to be shown in the Photo Picker dialog";

const char kProcessSharingWithDefaultSiteInstancesName[] =
    "Process sharing with default site instances";
const char kProcessSharingWithDefaultSiteInstancesDescription[] =
    "When site isolation is disabled, this mode changes how sites are lumped "
    "in to shared processes. For sites that do not require isolation, this "
    "feature groups them into a single 'default' site instance (per browsing "
    "instance) instead of creating unique site instances for each one. This "
    "enables resource savings by creating fewer processes for sites that do "
    "not need isolation.";

const char kProcessSharingWithStrictSiteInstancesName[] =
    "Process sharing with strict site instances";
const char kProcessSharingWithStrictSiteInstancesDescription[] =
    "When site isolation is disabled, this mode changes how sites are lumped "
    "in to a shared process. Process selection is usually controlled with "
    "site instances. With strict site isolation, each site on a page gets its "
    "own site instance and process. With site isolation disabled and without "
    "this mode, all sites that share a process are put into the same site "
    "instance. This mode adds a third way: site instances are strictly "
    "separated like strict site isolation, but process selection puts multiple "
    "site instances in a single process.";

const char kActionableContentSettingsName[] = "Improvements to site settings";
const char kActionableContentSettingsDescription[] =
    "Changes the site settings to use a switch instead of a dialog. "
    " Additionally improves icons to show current blocked status.";

const char kQueryTilesName[] = "Show query tiles";
const char kQueryTilesDescription[] = "Shows query tiles in Chrome";
const char kQueryTilesNTPName[] = "Show query tiles in NTP";
const char kQueryTilesNTPDescription[] = "Shows query tiles in NTP";
const char kQueryTilesOmniboxName[] = "Show query tiles in omnibox";
const char kQueryTilesOmniboxDescription[] = "Shows query tiles in omnibox";
const char kQueryTilesSingleTierName[] = "Show only one level of query tiles";
const char kQueryTilesSingleTierDescription[] =
    "Show only one level of query tiles";
const char kQueryTilesEnableQueryEditingName[] =
    "Query Tiles - Enable query edit mode";
const char kQueryTilesEnableQueryEditingDescription[] =
    "When a query tile is tapped, the query text will be shown in the omnibox "
    "and user will have a chance to edit the text before submitting";
const char kQueryTilesEnableTrendingName[] =
    "Query Tiles - Enable trending queries";
const char kQueryTilesEnableTrendingDescription[] =
    "Allow tiles of trending queries to show up in front of curated tiles";
const char kQueryTilesCountryCode[] = "Country code for getting tiles";
const char kQueryTilesCountryCodeDescription[] =
    "When query tiles are enabled, this value determines tiles for which "
    "country should be displayed.";
const char kQueryTilesCountryCodeUS[] = "US";
const char kQueryTilesCountryCodeIndia[] = "IN";
const char kQueryTilesCountryCodeBrazil[] = "BR";
const char kQueryTilesCountryCodeNigeria[] = "NG";
const char kQueryTilesCountryCodeIndonesia[] = "ID";
const char kQueryTilesLocalOrderingName[] =
    "Query Tiles - Enable local ordering";
const char kQueryTilesLocalOrderingDescription[] =
    "Enables ordering query tiles locally based on user interactions.";
const char kQueryTilesInstantFetchName[] = "Query tile instant fetch";
const char kQueryTilesInstantFetchDescription[] =
    "Immediately schedule background task to fetch query tiles";
const char kQueryTilesMoreTrendingName[] =
    "Query Tiles - more trending queries";
const char kQueryTilesMoreTrendingDescription[] =
    "Request more trending queries from the server";
const char kQueryTilesRankTilesName[] = "Query Tiles - rank tiles on server";
const char kQueryTilesRankTilesDescription[] =
    "Rank tiles on server based on client context";
const char kQueryTilesSwapTrendingName[] =
    "Query Tiles - Swap trending queries";
const char kQueryTilesSwapTrendingDescription[] =
    "Swap trending queries if user didn't click on them after several "
    "impressions";

const char kReadLaterFlagId[] = "read-later";
const char kReadLaterName[] = "Reading List";
const char kReadLaterDescription[] =
    "Allow users to save tabs for later. Enables a new button and menu for "
    "accessing tabs saved for later.";

const char kReaderModeHeuristicsName[] = "Reader Mode triggering";
const char kReaderModeHeuristicsDescription[] =
    "Determines what pages the Reader Mode infobar is shown on.";
const char kReaderModeHeuristicsMarkup[] = "With article structured markup";
const char kReaderModeHeuristicsAdaboost[] = "Non-mobile-friendly articles";
const char kReaderModeHeuristicsAllArticles[] = "All articles";
const char kReaderModeHeuristicsAlwaysOff[] = "Never";
const char kReaderModeHeuristicsAlwaysOn[] = "Always";

<<<<<<< HEAD
=======
const char kReaderModeInCCTName[] = "Reader Mode in CCT";
const char kReaderModeInCCTDescription[] =
    "Open Reader Mode in Chrome Custom Tabs.";

const char kReadLaterReminderNotificationName[] =
    "Read later reminder notification";
const char kReadLaterReminderNotificationDescription[] =
    "Enables read later weekly reminder notification.";

const char kRecoverFromNeverSaveAndroidName[] =
    "UI to recover from never save passwords on Android";
const char kRecoverFromNeverSaveAndroidDescription[] =
    "Enables showing UI which allows for easy reverting of the decision to "
    "never save passwords on a certain webiste";

>>>>>>> chromium
const char kReengagementNotificationName[] =
    "Enable re-engagement notifications";
const char kReengagementNotificationDescription[] =
    "Enables Chrome to use the in-product help system to decide when "
    "to show re-engagement notifications.";

const char kRelatedSearchesName[] =
    "Enables an experiment for Related Searches on Android";
const char kRelatedSearchesDescription[] =
    "Enables requesting related searches suggestions. These will be requested "
    "but not shown unless the UI flag is also enabled.";

const char kRelatedSearchesAlternateUxName[] =
    "Enables showing Related Searches in an alternate user experience.";
const char kRelatedSearchesAlternateUxDescription[] =
    "Enables showing related searches with an alternative from the normal "
    "user experience treatment.";

<<<<<<< HEAD
const char kRightEdgeGoesForwardGestureNavName[] =
    "RightEdgeGoesForwardGestureNav";
const char kRightEdgeGoesForwardGestureNavDescription[] =
    "Enables the right edge to navigate forward in OS gesture navigation mode.";

const char kSafeBrowsingSyncCheckerCheckAllowlistName[] =
    "Safe Browsing Sync Checker Check Allowlist";
const char kSafeBrowsingSyncCheckerCheckAllowlistDescription[] =
    "Enables Safe Browsing sync checker to check the allowlist before checking "
    "the blocklist.";
=======
const char kRelatedSearchesInBarName[] =
    "Enables showing Related Searches in the peeking bar.";
const char kRelatedSearchesInBarDescription[] =
    "Enables showing related searches suggestions in a carousel in the "
    "peeking bar of the bottom sheet on Android.";
>>>>>>> chromium

const char kRelatedSearchesSimplifiedUxName[] =
    "Enables showing Related Searches in a simplified user experience.";
const char kRelatedSearchesSimplifiedUxDescription[] =
    "Enables showing related searches with a simplified form of the normal "
    "user experience treatment.";

const char kRelatedSearchesUiName[] =
    "Forces showing of the Related Searches UI on Android";
const char kRelatedSearchesUiDescription[] =
    "Forces the Related Searches UI and underlying requests to be enabled "
    "regardless of whether they are safe or useful. This requires the Related "
    "Searches feature flag to also be enabled.";

const char kShareUsageRankingName[] =
    "Incorporate usage history into share target ranking.";
const char kShareUsageRankingDescription[] =
    "Incorporate the history of which apps were shared to when producing the "
    "ordered list of 3P share targets in the share hub.";

const char kRequestDesktopSiteForTabletsName[] =
    "Request desktop site for tablets on Android";
const char kRequestDesktopSiteForTabletsDescription[] =
    "Requests a desktop site, if the screen size is large enough on Android."
    " On tablets with small screens a mobile site will be requested by "
    "default.";

const char kSafeBrowsingClientSideDetectionAndroidName[] =
    "Safe Browsing Client Side Detection on Android";
const char kSafeBrowsingClientSideDetectionAndroidDescription[] =
    "Enable DOM feature collection on Safe Browsing pings on Android";

const char kSafeBrowsingPasswordCheckIntegrationForSavedPasswordsAndroidName[] =
    "Safe Browsing PasswordCheck Integration for Saved Passwords Android";
const char
    kSafeBrowsingPasswordCheckIntegrationForSavedPasswordsAndroidDescription[] =
        "Allows Android Chrome users to change their saved passwords through "
        "password reuse warning on phishing or low reputation sites.";

const char kEnhancedProtectionPromoAndroidName[] =
    "Enable enhanced protection promo card on Android on the New Tab Page";
const char kEnhancedProtectionPromoAndroidDescription[] =
    "Enable enhanced protection promo card for users that have not signed up "
    "for enhanced protection.";

const char kSafeBrowsingUseLocalBlacklistsV2Name[] =
    "Use local Safe Browsing blacklists";
const char kSafeBrowsingUseLocalBlacklistsV2Description[] =
    "If enabled, maintain a copy of Safe Browsing blacklists in the browser "
    "process to check the Safe Browsing reputation of URLs without calling "
    "into GmsCore for every URL.";

const char kSetMarketUrlForTestingName[] = "Set market URL for testing";
const char kSetMarketUrlForTestingDescription[] =
    "When enabled, sets the market URL for use in testing the update menu "
    "item.";

const char kSingleTouchSelectName[] =
    "Enables selecting plain text with a single touch.";
const char kSingleTouchSelectDescription[] =
    "Enables selecting plain text with a single touch on Android.";

const char kSiteIsolationForPasswordSitesName[] =
    "Site Isolation For Password Sites";
const char kSiteIsolationForPasswordSitesDescription[] =
    "Security mode that enables site isolation for sites based on "
    "password-oriented heuristics, such as a user typing in a password.";

const char kSmartSuggestionForLargeDownloadsName[] =
    "Smart suggestion for large downloads";
const char kSmartSuggestionForLargeDownloadsDescription[] =
    "Smart suggestion that offers download locations for large files.";

const char kStartSurfaceAndroidName[] = "Start Surface";
const char kStartSurfaceAndroidDescription[] =
    "Enable showing the start surface when launching Chrome via the "
    "launcher.";

const char kSharingHubLinkToggleName[] = "Sharing Hub Link Toggle";
const char kSharingHubLinkToggleDescription[] =
    "Enable the link toggle in the Sharing Hub.";

const char kStrictSiteIsolationName[] = "Strict site isolation";
const char kStrictSiteIsolationDescription[] =
    "Security mode that enables site isolation for all sites (SitePerProcess). "
    "In this mode, each renderer process will contain pages from at most one "
    "site, using out-of-process iframes when needed. "
    "Check chrome://process-internals to see the current isolation mode. "
    "Setting this flag to 'Enabled' turns on site isolation regardless of the "
    "default. Here, 'Disabled' is a legacy value that actually means "
    "'Default,' in which case site isolation may be already enabled based on "
    "platform, enterprise policy, or field trial. See also "
    "#site-isolation-trial-opt-out for how to disable site isolation for "
    "testing.";

const char kThemeRefactorAndroidName[] = "Theme refactor on Android";
const char kThemeRefactorAndroidDescription[] =
    "Enables the theme refactoring on Android.";

<<<<<<< HEAD
const char kCrossDeviceTabPaneAndroidName[] = "Cross Device Tab Pane Android";
const char kCrossDeviceTabPaneAndroidDescription[] =
    "Enables showing a new pane in the hub that displays the pre-existing "
    "cross device tabs feature originally located in Recent Tabs.";

const char kHistoryPaneAndroidName[] = "History Pane Android";
const char kHistoryPaneAndroidDescription[] =
    "Enables showing a new pane in the hub that displays History.";

const char kTabGroupCreationDialogAndroidName[] =
    "Tab Group Creation Dialog Android";
const char kTabGroupCreationDialogAndroidDescription[] =
    "Enables showing a dialog for adjusting tab group settings on new tab "
    "group creations. The dialog will only show for groups created through "
    "drag and drop or bulk selection merge.";

const char kTabGroupPaneAndroidName[] = "Tab Group Pane Android";
const char kTabGroupPaneAndroidDescription[] =
    "Enables showing a new pane in the hub that displays and allows "
    "interactions with tab groups. These groups may be currently opened in the "
    "tab mode or currently hidden.";

const char kTabGroupSyncAndroidName[] = "Tab Group Sync on Android";
const char kTabGroupSyncAndroidDescription[] =
    "Enables syncing of tab groups on Android with other devices.";

const char kTabGroupSyncDisableNetworkLayerName[] =
    "Tab Group Sync Disable Network Layer";
const char kTabGroupSyncDisableNetworkLayerDescription[] =
    "Disables network layer of tab group sync.";

const char kTabResumptionModuleAndroidName[] = "Tab Resumption Module";
const char kTabResumptionModuleAndroidDescription[] =
    "Enable showing tab suggestions on Android";

const char kTabStripGroupCollapseAndroidName[] =
    "Tab Strip Group Collapse Android";
const char kTabStripGroupCollapseAndroidDescription[] =
    "Enables tab strip group indicators to be clicked to collapse, temporarily "
    "hiding the colored outline, the group title, and the grouped tabs. "
    "Collapsed groups can be clicked again to expand. Synced tab groups will "
    "immediately be collapsed.";

const char kTabStripGroupDragDropAndroidName[] =
    "Tab Strip Group Drag Drop Android";
const char kTabStripGroupDragDropAndroidDescription[] =
    "Enables long-pressing on tab strip tab group indicators to start "
    "drag-and-drop. Users can drag the tab group off the tab strip and drop it "
    "into another window in split-screen mode or create a new window by "
    "dropping it on the edge of Chrome.";

const char kTabStripGroupReorderAndroidName[] = "Tab Strip Group Reorder";
const char kTabStripGroupReorderAndroidDescription[] =
    "Enables long-pressing on tab strip tab group indicators to enter reorder "
    "mode. Users will then be able to drag the tab group to reorder it.";

const char kTabStripIncognitoMigrationName[] =
    "Tab Strip Incognito switcher migration to toolbar";
const char kTabStripIncognitoMigrationDescription[] =
    "Migrates tab strip incognito switcher to toolbar and adds options to tab "
    "switcher context menu.";

const char kTabStripLayoutOptimizationName[] = "Tab Strip Layout Optimization";
const char kTabStripLayoutOptimizationDescription[] =
    "Allows adding horizontal and vertical margin to the tab strip.";

const char kTabStripTransitionInDesktopWindowName[] =
    "Tab Strip Transition in Desktop Window";
const char kTabStripTransitionInDesktopWindowDescription[] =
    "Allows hiding / showing the tab strip with varying desktop window widths "
    "by initiating a fade transition.";

const char kTabSwitcherFullNewTabButtonName[] = "Tab Switcher New Tab Button";
const char kTabSwitcherFullNewTabButtonDescription[] =
    "Modifies the visual behavior of the new tab button in the tab switcher.";

const char kUseHardwareBufferUsageFlagsFromVulkanName[] =
    "Use recommended AHardwareBuffer usage flags from Vulkan";
const char kUseHardwareBufferUsageFlagsFromVulkanDescription[] =
    "Allows querying recommended AHardwareBuffer usage flags from Vulkan API";

const char kUnifiedPasswordManagerLocalPasswordsAndroidAccessLossWarningName[] =
    "Access loss warning for unmigrated password manager users";
const char
    kUnifiedPasswordManagerLocalPasswordsAndroidAccessLossWarningDescription[] =
        "Chrome password manager users who are not enrolled into the new "
        "experience of storing local passwords in GMSCore will be warned via "
        "various communication channels about data/feature access loss unless "
        "they upgrade GMSCore.";
=======
const char kToolbarIphAndroidName[] = "Enable Toolbar IPH on Android";
const char kToolbarIphAndroidDescription[] =
    "Enables in product help bubbles on the toolbar. In particular, the home "
    "button and the tab switcher button.";

const char kToolbarMicIphAndroidName[] =
    "Enable IPH on Android on the mic in the toolbar";
const char kToolbarMicIphAndroidDescription[] =
    "Enables in product help bubble on the mic button in the toolbar.";
>>>>>>> chromium

const char kUpdateMenuBadgeName[] = "Force show update menu badge";
const char kUpdateMenuBadgeDescription[] =
    "When enabled, a badge will be shown on the app menu button if the update "
    "type is Update Available or Unsupported OS Version.";

const char kUpdateMenuItemCustomSummaryDescription[] =
    "When this flag and the force show update menu item flag are enabled, a "
    "custom summary string will be displayed below the update menu item.";
const char kUpdateMenuItemCustomSummaryName[] =
    "Update menu item custom summary";

const char kUpdateMenuTypeName[] =
    "Forces the update menu type to a specific type";
const char kUpdateMenuTypeDescription[] =
    "When set, forces the update type to be a specific one, which impacts "
    "the app menu badge and menu item for updates. For Inline Update, the "
    "update available flag is implied. The 'Inline Update: Success' selection "
    "goes through the whole inline update flow to the end with a successful "
    "outcome. The other 'Inline Update' options go through the same flow, but "
    "stop at various stages, see their error type for details.";
const char kUpdateMenuTypeNone[] = "None";
const char kUpdateMenuTypeUpdateAvailable[] = "Update Available";
const char kUpdateMenuTypeUnsupportedOSVersion[] = "Unsupported OS Version";
const char kUpdateMenuTypeInlineUpdateSuccess[] = "Inline Update: Success";
const char kUpdateMenuTypeInlineUpdateDialogCanceled[] =
    "Inline Update Error: Dialog Canceled";
const char kUpdateMenuTypeInlineUpdateDialogFailed[] =
    "Inline Update Error: Dialog Failed";
const char kUpdateMenuTypeInlineUpdateDownloadFailed[] =
    "Inline Update Error: Download Failed";
const char kUpdateMenuTypeInlineUpdateDownloadCanceled[] =
    "Inline Update Error: Download Canceled";
const char kUpdateMenuTypeInlineUpdateInstallFailed[] =
    "Inline Update Error: Install Failed";

<<<<<<< HEAD
const char kOmahaMinSdkVersionAndroidName[] =
    "Forces the minimum Android SDK version to a particular value.";
const char kOmahaMinSdkVersionAndroidDescription[] =
    "When set, the minimum Android minimum SDK version is set to a particular "
    "value which impact the app menu badge, menu items, and settings about "
    "screen regarding whether Chrome can be updated.";
const char kOmahaMinSdkVersionAndroidMinSdk1Description[] = "Minimum SDK = 1";
const char kOmahaMinSdkVersionAndroidMinSdk1000Description[] =
    "Minimum SDK = 1000";
=======
const char kUseNotificationCompatBuilderName[] =
    "Use NotificationCompat.Builder for Web Notifications";
const char kUseNotificationCompatBuilderDescription[] =
    "This enables using NotificationCompat.Builder instead of "
    "Notification.Builder to create Web Notifications.";

const char kUserMediaScreenCapturingName[] = "Screen Capture API";
const char kUserMediaScreenCapturingDescription[] =
    "Allows sites to request a video stream of your screen.";
>>>>>>> chromium

const char kVideoTutorialsName[] = "Enable video tutorials";
const char kVideoTutorialsDescription[] = "Show video tutorials in Chrome";
const char kVideoTutorialsInstantFetchName[] =
    "Video tutorials fetch on startup";
const char kVideoTutorialsInstantFetchDescription[] =
    "Fetch video tutorials on startup";

const char kAdaptiveButtonInTopToolbarName[] = "Adaptive button in top toolbar";
const char kAdaptiveButtonInTopToolbarDescription[] =
    "Enables showing an adaptive action button in the top toolbar";
const char kAdaptiveButtonInTopToolbarCustomizationName[] =
    "Adaptive button in top toolbar customization";
const char kAdaptiveButtonInTopToolbarCustomizationDescription[] =
    "Enables UI for customizing the adaptive action button in the top toolbar";
const char kShareButtonInTopToolbarName[] = "Share button in top toolbar";
const char kShareButtonInTopToolbarDescription[] =
    "Enables UI to initiate sharing from the top toolbar. Enabling Adaptive "
    "Button overrides this.";
const char kVoiceButtonInTopToolbarName[] = "Voice button in top toolbar";
const char kVoiceButtonInTopToolbarDescription[] =
    "Enables showing the voice search button in the top toolbar. Enabling "
    "Adaptive Button overrides this.";

const char kInlineUpdateFlowName[] = "Enable Google Play inline update flow";
const char kInlineUpdateFlowDescription[] =
    "When this flag is set, instead of taking the user to the Google Play "
    "Store when an update is available, the user is presented with an inline "
    "flow where they do not have to leave Chrome until the update is ready "
    "to install.";

const char kSwipeToMoveCursorName[] = "Swipe to move cursor";
const char kSwipeToMoveCursorDescription[] =
    "Allows user to use touch gestures to move the text cursor around. This "
    "flag will only take effect on Android 11 and above.";

const char kWalletRequiresFirstSyncSetupCompleteName[] =
    "Controls whether Wallet (GPay) integration on Android requires "
    "first-sync-setup to be complete";
const char kWalletRequiresFirstSyncSetupCompleteDescription[] =
    "Controls whether the Wallet (GPay) integration on Android requires "
    "first-sync-setup to be complete. Only has an effect if "
    "enable-autofill-account-wallet-storage is also enabled.";

const char kWebFeedName[] = "Web Feed";
const char kWebFeedDescription[] =
    "Allows users to keep up with and consume web content.";

const char kWebNotesStylizeName[] = "WebNotes Stylize";
const char kWebNotesStylizeDescription[] =
    "Allows users to create and share stylized webnotes.";

const char kXsurfaceMetricsReportingName[] = "Xsurface Metrics Reporting";
const char kXsurfaceMetricsReportingDescription[] =
    "Allows metrics reporting state to be passed to Xsurface";

<<<<<<< HEAD
const char kPasswordSuggestionBottomSheetV2Name[] =
    "Refactored password suggestions bottom sheet";
const char kPasswordSuggestionBottomSheetV2Description[] =
    "Enables the refactored version of the password suggestions bottom sheet. "
    "All the user facing functionality should stay the same.";

#if BUILDFLAG(ENABLE_VR) && BUILDFLAG(ENABLE_OPENXR)
const char kOpenXRExtendedFeaturesName[] =
    "WebXR OpenXR Runtime Extended Features";
const char kOpenXRExtendedFeaturesDescription[] =
    "Enables the use of the OpenXR runtime to create WebXR sessions with a "
    "broader feature set (e.g. features not currently supported on Desktop).";

const char kOpenXRName[] = "Enable OpenXR WebXR Runtime";
const char kOpenXRDescription[] =
    "Enables the use of the OpenXR runtime to create WebXR sessions.";

const char kOpenXRAndroidSmoothDepthName[] = "Enable OpenXR Smooth Depth";
const char kOpenXRAndroidSmoothDepthDescription[] =
    "Forces the OpenXR Android runtime to use the Smooth depth image. When "
    "Disabled, the raw depth image will be used instead.";
#endif

=======
>>>>>>> chromium
// Non-Android -----------------------------------------------------------------

#else  // !defined(OS_ANDROID)

const char kAllowAllSitesToInitiateMirroringName[] =
    "Allow all sites to initiate mirroring";
const char kAllowAllSitesToInitiateMirroringDescription[] =
    "When enabled, allows all websites to request to initiate tab mirroring "
    "via Presentation API. Requires #cast-media-route-provider to also be "
    "enabled";

const char kAppManagementIntentSettingsName[] =
    "App Management intent settings";
const char kAppManagementIntentSettingsDescription[] =
    "Enables and displays the intent settings link handling setting for App "
    "Management.";

const char kEnableAccessibilityLiveCaptionName[] = "Live Caption";
const char kEnableAccessibilityLiveCaptionDescription[] =
    "Enables the live caption feature which generates captions for "
    "media playing in Chrome. Turn the feature on in "
    "chrome://settings/accessibility.";

const char kEnableAccessibilityLiveCaptionSodaName[] = "SODA for Live Caption";
const char kEnableAccessibilityLiveCaptionSodaDescription[] =
    "If Live Caption (chrome://flags/#enable-accessibility-live-captions) is "
    "enabled, whether or not to use SODA for live captions instead of the web "
    "api. Turn on the feature in chrome://settings/accessibility.";

const char kCastMediaRouteProviderName[] = "Cast Media Route Provider";
const char kCastMediaRouteProviderDescription[] =
    "Enables the native Cast Media Route Provider implementation to be used "
    "instead of the implementation in the Media Router component extension.";

const char kCopyLinkToTextName[] = "Copy Link To Text";
const char kCopyLinkToTextDescription[] =
    "Adds an item to the context menu to allow a user to copy a link to the "
    "page with the selected text highlighted.";

<<<<<<< HEAD
const char kEnableCrOSLiveTranslateName[] = "Live Translate CrOS";
const char kEnableCrOSLiveTranslateDescription[] =
    "Enables the live translate feature on ChromeOS which allows for live "
    "translation of captions into a target language.";

const char kEnableCrOSSodaLanguagesName[] = "SODA language expansion";
const char kEnableCrOSSodaLanguagesDescription[] =
    "Enable language expansion for SODA on device to "
    "impact dictation and Live Captions.";

const char kEnableCrOSSodaConchLanguagesName[] = "SODA Conch Languages.";
const char kEnableCrOSSodaConchLanguagesDescription[] =
    "Enable Conch specific SODA language models.";

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
const char kEsbDownloadRowPromoFeatureName[] =
    "Enable ESB Download Row promotion";
const char kEsbDownloadRowPromoFeatureDescription[] =
    "Promotes Enhanced Safe Browsing (ESB) on a user's most recent "
    "dangerous/suspicious download by adding an extra row under the download "
    "that links to the chrome://settings/security page.";
#endif

const char kFreezingOnEnergySaverName[] =
    "Freeze CPU intensive background tabs on Energy Saver";
const char kFreezingOnEnergySaverDescription[] =
    "When Energy Saver is active, freeze eligible background tabs that use a "
    "lot of CPU. A tab is eligible if it's silent, doesn't provide audio- or "
    "video- conference functionality and doesn't use WebUSB or Web Bluetooth.";

const char kFreezingOnEnergySaverTestingName[] =
    "Freeze CPU intensive background tabs on Energy Saver - Testing Mode";
const char kFreezingOnEnergySaverTestingDescription[] =
    "Similar to #freezing-on-energy-saver, with changes to facilitate testing: "
    "1) pretend that Energy Saver is active even when it's not and 2) pretend "
    "that all tabs use a lot of CPU.";

const char kKeyboardLockPromptName[] = "Keyboard Lock prompt";
const char kKeyboardLockPromptDescription[] =
    "Requesting to use the keyboard lock API causes a permission prompt to be "
    "shown.";

const char kPressAndHoldEscToExitBrowserFullscreenName[] =
    "Holding Esc to exit browser fullscreen";
const char kPressAndHoldEscToExitBrowserFullscreenDescription[] =
    "Allows users to press and hold Esc key to exit browser fullscreen.";

const char kReadAnythingImagesViaAlgorithmName[] =
    "Reading Mode with images added via algorithm";
const char kReadAnythingImagesViaAlgorithmDescription[] =
    "Have Reading Mode use a local rules based algorithm to include images "
    "from webpages.";

const char kReadAnythingReadAloudName[] = "Reading Mode Read Aloud";
const char kReadAnythingReadAloudDescription[] =
    "Enables the experimental Read Aloud feature in Reading Mode.";

const char kReadAnythingReadAloudPhraseHighlightingName[] =
    "Reading Mode Read Aloud Phrase Highlighting";
const char kReadAnythingReadAloudPhraseHighlightingDescription[] =
    "Enables the experimental Reading Mode feature that highlights by phrases "
    "when reading aloud, when the phrase option is selected from the highlight "
    "menu.";

const char kReadAnythingDocsIntegrationName[] =
    "Reading Mode Google Docs Integration";
const char kReadAnythingDocsIntegrationDescription[] =
    "Allows Reading Mode to work on Google Docs.";

const char kReadAnythingDocsLoadMoreButtonName[] =
    "Reading Mode Google Docs Load More Button";
const char kReadAnythingDocsLoadMoreButtonDescription[] =
    "Adds a button to the end of the Reading Mode UI. When clicked, "
    "the main page scrolls to show the next page's content.";

const char kLinkPreviewName[] = "Link Preview";
const char kLinkPreviewDescription[] =
    "When enabled, Link Preview feature gets to be available to preview a "
    "linked page in a dedicated small window before navigating to the linked "
    "page. The feature can be triggered from a context menu item, or users' "
    "actions. We are evaluating multiple actions in our experiment to "
    "understand what's to be the best for users from the viewpoint of "
    "security, privacy, and usability. The feature might be unstable and "
    "unusable on some platforms, e.g. macOS or touch devices.";

const char kMoveThemePrefsToSpecificsName[] =
    "Move theme prefs to ThemeSpecifics";
const char kMoveThemePrefsToSpecificsDescription[] =
    "Uses new fields in ThemeSpecifics for theme attributes which were "
    "previously synced using preferences, thereby putting syncing of all the "
    "theme attributes behind the Themes sync toggle.";
=======
const char kEnterpriseRealtimeExtensionRequestName[] =
    "Enterprise real-time extension request report";
const char kEnterpriseRealtimeExtensionRequestDescription[] =
    "Enable the real-time extension request uploading. The feature requires "
    "the enterprise reporting and extension request being enabled.";

const char kGlobalMediaControlsCastStartStopName[] =
    "Global media controls control Cast start/stop";
const char kGlobalMediaControlsCastStartStopDescription[] =
    "Allows global media controls to control when a Cast session is started "
    "or stopped instead of relying on the Cast dialog.";
>>>>>>> chromium

const char kMuteNotificationSnoozeActionName[] =
    "Snooze action for mute notifications";
const char kMuteNotificationSnoozeActionDescription[] =
    "Adds a Snooze action to mute notifications shown while sharing a screen.";

const char kNtpCacheOneGoogleBarName[] = "Cache OneGoogleBar";
const char kNtpCacheOneGoogleBarDescription[] =
    "Enables using the OneGoogleBar cached response in chrome://new-tab-page, "
    "when available.";

const char kNtpRepeatableQueriesName[] =
    "Repeatable queries on the New Tab Page";
const char kNtpRepeatableQueriesDescription[] =
    "Enables surfacing repeatable queries as most visited tiles on the "
    "New Tab Page.";

const char kNtpModulesName[] = "NTP Modules";
const char kNtpModulesDescription[] = "Shows modules on the New Tab Page.";

const char kNtpDriveModuleName[] = "NTP Drive Module";
const char kNtpDriveModuleDescription[] =
    "Shows the Google Drive module on the New Tab Page";

const char kNtpRecipeTasksModuleName[] = "NTP Recipe Tasks Module";
const char kNtpRecipeTasksModuleDescription[] =
    "Shows the recipe tasks module on the New Tab Page.";

const char kNtpShoppingTasksModuleName[] = "NTP Shopping Tasks Module";
const char kNtpShoppingTasksModuleDescription[] =
    "Shows the shopping tasks module on the New Tab Page.";

const char kNtpChromeCartModuleName[] = "NTP Chrome Cart Module";
const char kNtpChromeCartModuleDescription[] =
    "Shows the chrome cart module on the New Tab Page.";

const char kNtpModulesDragAndDropName[] = "NTP Modules Drag and Drop";
const char kNtpModulesDragAndDropDescription[] =
    "Enables modules to be reordered via dragging and dropping on the "
    "New Tab Page.";

const char kNtpModulesRedesignedName[] = "NTP Modules Redesigned";
const char kNtpModulesRedesignedDescription[] =
    "Shows the redesigned modules on the New Tab Page.";

const char kNtpRealboxSuggestionAnswersName[] =
    "NTP Realbox Suggestion Answers";
const char kNtpRealboxSuggestionAnswersDescription[] =
    "Shows suggestion answers in the NTP Realbox when enabled.";

<<<<<<< HEAD
const char kNtpPhotosModuleOptInArtWorkName[] =
    "NTP Photos Module Opt In ArtWork";
const char kNtpPhotosModuleOptInArtWorkDescription[] =
    "Determines the art work in the NTP Photos Opt-In card";

const char kNtpPhotosModuleOptInTitleName[] = "NTP Photos Module Opt In Title";
const char kNtpPhotosModuleOptInTitleDescription[] =
    "Determines the title of the NTP Photos Opt-In card";

const char kNtpPhotosModuleSoftOptOutName[] = "NTP Photos Module Soft Opt-Out";
const char kNtpPhotosModuleSoftOptOutDescription[] =
    "Enables soft opt-out option in Photos opt-in card";

const char kNtpOneGoogleBarAsyncBarPartsName[] =
    "NTP OneGoogleBar Async Bar Parts";
const char kNtpOneGoogleBarAsyncBarPartsDescription[] =
    "Enables the OneGoogleBar async bar parts API on the New Tab Page.";

const char kNtpOutlookCalendarModuleName[] = "NTP Outlook Calendar Module";
const char kNtpOutlookCalendarModuleDescription[] =
    "Shows the Outlook Calendar module on the New Tab Page.";

const char kNtpRealboxContextualAndTrendingSuggestionsName[] =
    "NTP Realbox Contextual and Trending Suggestions";
const char kNtpRealboxContextualAndTrendingSuggestionsDescription[] =
    "Allows NTP Realbox's second column to display contextual and trending "
    "text suggestions.";

const char kNtpRealboxCr23ThemingName[] = "Chrome Refresh Themed Realbox";
const char kNtpRealboxCr23ThemingDescription[] =
    "CR23 theming will be applied in Realbox when enabled.";

const char kNtpRealboxMatchSearchboxThemeName[] =
    "NTP Realbox Matches Searchbox Theme";
const char kNtpRealboxMatchSearchboxThemeDescription[] =
    "Makes NTP Realbox drop shadow match that of the Searchbox when enabled.";

const char kNtpRealboxUseGoogleGIconName[] = "NTP Realbox Google G Icon";
const char kNtpRealboxUseGoogleGIconDescription[] =
    "Shows Google G icon "
    "instead of Search Loupe in realbox when enabled";

const char kNtpSafeBrowsingModuleName[] = "NTP Safe Browsing Module";
const char kNtpSafeBrowsingModuleDescription[] =
    "Shows the safe browsing module on the New Tab Page.";

const char kNtpSharepointModuleName[] = "NTP Sharepoint Module";
const char kNtpSharepointModuleDescription[] =
    "Shows the Sharepoint module on the New Tab Page.";

const char kNtpWallpaperSearchButtonName[] = "NTP Wallpaper Search Button";
const char kNtpWallpaperSearchButtonDescription[] =
    "Enables entry point on New Tab Page for Customize Chrome Side Panel "
    "Wallpaper Search.";

const char kNtpWallpaperSearchButtonAnimationName[] =
    "NTP Wallpaper Search Button Animation";
const char kNtpWallpaperSearchButtonAnimationDescription[] =
    "Enables animation for New Tab Page's Wallpaper Search button. Requires "
    "#ntp-wallpaper-search-button to be enabled too.";

const char kNtpWideModulesName[] = "NTP Wide Modules";
const char kNtpWideModulesDescription[] =
    "Shows wide NTP modules if NTP provides enough space.";
=======
const char kEnableReaderModeName[] = "Enable Reader Mode";
const char kEnableReaderModeDescription[] =
    "Allows viewing of simplified web pages by selecting 'Customize and "
    "control Chrome'>'Distill page'";
>>>>>>> chromium

const char kHappinessTrackingSurveysForDesktopDemoName[] =
    "Happiness Tracking Surveys Demo";
const char kHappinessTrackingSurveysForDesktopDemoDescription[] =
    "Enable showing Happiness Tracking Surveys Demo to users on Desktop";

<<<<<<< HEAD
const char kMainNodeAnnotationsName[] = "Main Node Annotations";
const char kMainNodeAnnotationsDescription[] =
    "Uses Screen2x main content extractor to annotate the accessibility tree "
    "with the main landmark on the node identified as main.";
=======
const char kHappinessTrackingSurveysForDesktopPrivacySandboxName[] =
    "Happiness Tracking Surveys for the Privacy Sandbox";
const char kHappinessTrackingSurveysForDesktopPrivacySandboxDescription[] =
    "Enable showing Happiness Tracking Surveys for the Privacy Sandbox to "
    "users on Desktop";

const char kHappinessTrackingSurveysForDesktopSettingsName[] =
    "Happiness Tracking Surveys for Settings";
const char kHappinessTrackingSurveysForDesktopSettingsDescription[] =
    "Enable showing Happiness Tracking Surveys for Settings to users on "
    "Desktop";

const char kHappinessTrackingSurveysForDesktopSettingsPrivacyName[] =
    "Happiness Tracking Surveys for Privacy Settings";
const char kHappinessTrackingSurveysForDesktopSettingsPrivacyDescription[] =
    "Enable showing Happiness Tracking Surveys for Privacy Settings to users "
    "on Desktop";

const char kKernelnextVMsName[] = "Enable VMs on experimental kernels.";
const char kKernelnextVMsDescription[] =
    "Enables VM support on devices running experimental kernel versions.";
>>>>>>> chromium

const char kOmniboxDriveSuggestionsName[] =
    "Omnibox Google Drive Document suggestions";
const char kOmniboxDriveSuggestionsDescriptions[] =
    "Display suggestions for Google Drive documents in the omnibox when Google "
    "is the default search engine.";

const char kOmniboxExperimentalKeywordModeName[] =
    "Omnibox Experimental Keyword Mode";
const char kOmniboxExperimentalKeywordModeDescription[] =
    "Enables various experimental features related to keyword mode, its "
    "suggestions and layout.";

const char kOmniboxPedalsBatch2Name[] = "Omnibox Pedals batch 2";
const char kOmniboxPedalsBatch2Description[] =
    "Enable the second batch of Omnibox Pedals (Safety Check, etc.).";

const char kOmniboxPedalsBatch2NonEnglishName[] =
    "Omnibox Pedals batch 2 for non-English locales";
const char kOmniboxPedalsBatch2NonEnglishDescription[] =
    "Enable the second batch of Omnibox Pedals (Safety Check, etc.) for "
    "locales other than 'en' and 'en-GB'. This flag has no effect unless "
    "\"Omnibox Pedals batch 2\" is also enabled.";

const char kOmniboxPedalsBatch3Name[] = "Omnibox Pedals batch 3";
const char kOmniboxPedalsBatch3Description[] =
    "Enable the third batch of Omnibox Pedals.";

const char kOmniboxPedalsDefaultIconColoredName[] =
    "Omnibox Pedals Default Icon Colored";
const char kOmniboxPedalsDefaultIconColoredDescription[] =
    "Enable a color version of the default icon shown on the button for most "
    "omnibox Pedals (aka Chrome Actions).";

const char kOmniboxKeywordSearchButtonName[] = "Omnibox keyword search button";
const char kOmniboxKeywordSearchButtonDescription[] =
    "Enable the omnibox keyword search button which offers a way to search "
    "on specific sites from the omnibox.";

const char kOmniboxRefinedFocusStateName[] = "Omnibox refined focus state UI";
const char kOmniboxRefinedFocusStateDescription[] =
    "Enables new changes to the UI indicating focus and hover states.";

const char kOmniboxShortBookmarkSuggestionsName[] =
    "Omnibox short bookmark suggestions";
const char kOmniboxShortBookmarkSuggestionsDescription[] =
    "Match very short input words to beginning of words in bookmark "
    "suggestions.";

const char kReadLaterFlagId[] = "read-later";
const char kReadLaterName[] = "Reading List";
const char kReadLaterDescription[] =
    "Click on the Bookmark icon or right click on a tab to add tabs to a "
    "reading list.";

const char kSCTAuditingName[] = "SCT auditing";
const char kSCTAuditingDescription[] =
    "Enables SCT auditing for users who have opted in to Safe Browsing "
    "Extended Reporting.";

const char kShutdownSupportForKeepaliveName[] =
    "Shutdown support for keepalive requests";
const char kShutdownSupportForKeepaliveDescription[] =
    "When enabled, keepalive requests "
    "(https://fetch.spec.whatwg.org/#request-keepalive-flag) blocks the "
    "browser shutdown sequence for a short period of time.";

const char kTabFreezeName[] = "Tab Freeze";
const char kTabFreezeDescription[] =
    "Enables freezing eligible tabs when they have been backgrounded for 5 "
    "minutes.";

<<<<<<< HEAD
const char kTabOrganizationSettingsVisibilityName[] =
    "Tab Organization Settings Visibility";
const char kTabOrganizationSettingsVisibilityDescription[] =
    "Shows Tab Organization in the settings UI";

const char kTabstripDeclutterName[] = "Tab Declutter";
const char kTabstripDeclutterDescription[] =
    "Enables the Tab Declutter feature, which can be found within the Tab "
    "Search bubble.";

const char kTabstripDedupeName[] = "Tab Deduplication";
const char kTabstripDedupeDescription[] =
    "Enables the Tab Deduplication feature, which can be found within the Tab "
    "Search bubble.";

const char kIOSPromoRefreshedPasswordBubbleName[] =
    "Chrome for iOS promo : passwords";
const char kIOSPromoRefreshedPasswordBubbleDescription[] =
    "When enabled, the new Contextual Chrome for iOS promo will be shown to"
    "the eligible users when they save/update their passwords.";

const char kIOSPromoAddressBubbleName[] = "Chrome for iOS promo : addresses";
const char kIOSPromoAddressBubbleDescription[] =
    "When enabled, the Contextual Chrome for iOS promo will be shown to"
    "the eligible users when they save/update their address.";

const char kIOSPromoPaymentBubbleName[] = "Chrome for iOS promo : payments";
const char kIOSPromoPaymentBubbleDescription[] =
    "When enabled, the Contextual Chrome for iOS promo will be shown to"
    "the eligible users when they save/update their payments.";

const char kWebAppSyncGeneratedIconBackgroundFixName[] =
    "Web App Sync Generated Icon Background Fix";
const char kWebAppSyncGeneratedIconBackgroundFixDescription[] =
    "Schedules attempts to fix generated icons for sync installed web apps in "
    "the background with exponential backoff within their permitted fix time "
    "window.";

const char kWebAppSyncGeneratedIconRetroactiveFixName[] =
    "Web App Sync Generated Icon Retroactive Fix";
const char kWebAppSyncGeneratedIconRetroactiveFixDescription[] =
    "Starts a time window for existing sync installed web apps with generated "
    "icons for background/update events to attempt fixes.";

const char kWebAppSyncGeneratedIconUpdateFixName[] =
    "Web App Sync Generated Icon Update Fix";
const char kWebAppSyncGeneratedIconUpdateFixDescription[] =
    "Allows web apps installed via sync to update their icons without prompting"
    "during a manifest update if the icons were generated, indicative of"
    "network errors during the sync install.";

#if !BUILDFLAG(IS_ANDROID)
const char kTranslateOpenSettingsName[] = "Translate Open Settings";
const char kTranslateOpenSettingsDescription[] =
    "Add an option to the translate bubble menu to open language settings.";
#endif

const char kUserDisplayModeSyncBrowserMitigationName[] =
    "Web App User Display Mode Sync Browser Mitigation";
const char kUserDisplayModeSyncBrowserMitigationDescription[] =
    "Enables a mitigation during web app install on CrOS for syncing "
    "user_display_mode: kBrowser to non-CrOS devices.";

const char kUserDisplayModeSyncStandaloneMitigationName[] =
    "Web App User Display Mode Sync Standalone Mitigation";
const char kUserDisplayModeSyncStandaloneMitigationDescription[] =
    "Enables a mitigation during web app install on CrOS for syncing "
    "user_display_mode: kStandalone to non-CrOS devices.";

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
const char kWasmTtsComponentUpdaterEnabledName[] =
    "Enable Wasm TTS Extension Component";
const char kWasmTtsComponentUpdaterEnabledDescription[] =
    "Enable updating the wasm TTS extension resource files through the "
    "Component Updater.";
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)
const char kWebAppSystemMediaControlsName[] = "Web App System Media Controls";
const char kWebAppSystemMediaControlsDescription[] =
    "Enable instanced system media controls for web apps";
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)

const char kWebAuthenticationPermitEnterpriseAttestationName[] =
    "Web Authentication Enterprise Attestation";
const char kWebAuthenticationPermitEnterpriseAttestationDescription[] =
    "Permit a set of origins to request a uniquely identifying enterprise "
    "attestation statement from a security key when creating a Web "
    "Authentication credential.";

#endif  // BUILDFLAG(IS_ANDROID)
=======
#endif  // !defined(OS_ANDROID)
>>>>>>> chromium

// Windows ---------------------------------------------------------------------

#if defined(OS_WIN)

const char kCalculateNativeWinOcclusionName[] =
    "Calculate window occlusion on Windows";
const char kCalculateNativeWinOcclusionDescription[] =
    "Calculate window occlusion on Windows will be used in the future "
    "to throttle and potentially unload foreground tabs in occluded windows";

const char kChromeCleanupScanCompletedNotificationName[] =
    "Chrome cleanup scan completion notification";
const char kChromeCleanupScanCompletedNotificationDescription[] =
    "Allows you to be notified when a Chrome cleaner scan you started "
    "completes.";

const char kCloudPrintXpsName[] = "XPS in Google Cloud Print";
const char kCloudPrintXpsDescription[] =
    "XPS enables advanced options for classic printers connected to the Cloud "
    "Print with Chrome. Printers must be re-connected after changing this "
    "flag.";

const char kD3D11VideoDecoderName[] = "D3D11 Video Decoder";
const char kD3D11VideoDecoderDescription[] =
    "Enables D3D11VideoDecoder for hardware accelerated video decoding.";

const char kEnableIncognitoShortcutOnDesktopName[] =
    "Enable Incognito Desktop Shortcut";
const char kEnableIncognitoShortcutOnDesktopDescription[] =
    "Enables users to create a desktop shortcut for incognito mode.";

const char kEnableMediaFoundationVideoCaptureName[] =
    "MediaFoundation Video Capture";
const char kEnableMediaFoundationVideoCaptureDescription[] =
    "Enable/Disable the usage of MediaFoundation for video capture. Fall back "
    "to DirectShow if disabled.";

const char kRawAudioCaptureName[] = "Raw audio capture";
const char kRawAudioCaptureDescription[] =
    "Enable/Disable the usage of WASAPI raw audio capture. When enabled, the "
    "audio stream is a 'raw' stream that bypasses all signal processing except "
    "for endpoint specific, always-on processing in the Audio Processing Object"
    " (APO), driver, and hardware.";

const char kRunVideoCaptureServiceInBrowserProcessName[] =
    "Run video capture service in browser";
const char kRunVideoCaptureServiceInBrowserProcessDescription[] =
    "Run the video capture service in the browser process.";

const char kSafetyCheckChromeCleanerChildName[] =
    "Chrome Cleanup Tool in safety check";
const char kSafetyCheckChromeCleanerChildDescription[] =
    "Enables the Chrome Cleanup Tool child in safety check.";

const char kUseAngleName[] = "Choose ANGLE graphics backend";
const char kUseAngleDescription[] =
    "Choose the graphics backend for ANGLE. D3D11 is used on most Windows "
    "computers by default. Using the OpenGL backend is not supported and will "
    "likely exhibit rendering artifacts.";

const char kUseAngleDefault[] = "Default";
const char kUseAngleGL[] = "OpenGL";
const char kUseAngleD3D11[] = "D3D11";
const char kUseAngleD3D9[] = "D3D9";
const char kUseAngleD3D11on12[] = "D3D11on12";

const char kUseWinrtMidiApiName[] = "Use Windows Runtime MIDI API";
const char kUseWinrtMidiApiDescription[] =
    "Use Windows Runtime MIDI API for WebMIDI (effective only on Windows 10 or "
    "later).";

#if BUILDFLAG(ENABLE_PRINTING)
const char kGdiTextPrinting[] = "GDI Text Printing";
const char kGdiTextPrintingDescription[] =
    "Use GDI to print text as simply text";

const char kPrintWithReducedRasterizationName[] =
    "Print with reduced rasterization";
const char kPrintWithReducedRasterizationDescription[] =
    "When using GDI printing, avoid rasterization if possible.";

const char kUseXpsForPrintingName[] = "Use XPS for printing";
const char kUseXpsForPrintingDescription[] =
    "When enabled, use XPS printing API instead of the GDI print API.";

const char kUseXpsForPrintingFromPdfName[] = "Use XPS for printing from PDF";
const char kUseXpsForPrintingFromPdfDescription[] =
    "When enabled, use XPS printing API instead of the GDI print API when "
    "printing PDF documents.";
#endif  // BUILDFLAG(ENABLE_PRINTING)

const char kWin10TabSearchCaptionButtonName[] =
    "Windows 10 Tab Search Caption Button";
const char kWin10TabSearchCaptionButtonDescription[] =
    "Move the Tab Search entrypoint besides the window caption buttons on "
    "Windows 10 platforms.";

#endif  // defined(OS_WIN)

// Mac -------------------------------------------------------------------------

#if defined(OS_MAC)

#if BUILDFLAG(ENABLE_PRINTING)
const char kCupsIppPrintingBackendName[] = "CUPS IPP Printing Backend";
const char kCupsIppPrintingBackendDescription[] =
    "Use the CUPS IPP printing backend instead of the original CUPS backend "
    "that calls the PPD API.";
#endif  // BUILDFLAG(ENABLE_PRINTING)

const char kEnterpriseReportingApiKeychainRecreationName[] =
    "Enterprise reporting API keychain item recreation.";
const char kEnterpriseReportingApiKeychainRecreationDescription[] =
    "Allow enterprise reporting private API to recreate keychain item on Mac. "
    "The recreated item can be accessed by other binaries.";

const char kImmersiveFullscreenName[] = "Immersive Fullscreen Toolbar";
const char kImmersiveFullscreenDescription[] =
    "Automatically hide and show the toolbar in fullscreen.";

<<<<<<< HEAD
const char kMacAccessibilityAPIMigrationName[] = "Mac A11y API Migration";
const char kMacAccessibilityAPIMigrationDescription[] =
    "Enables the migration to the new Cocoa accessibility API.";

const char kMacImeLiveConversionFixName[] = "Mac IME Live Conversion";
const char kMacImeLiveConversionFixDescription[] =
    "A fix for the Live Conversion feature of Japanese IME.";

const char kMacLoopbackAudioForScreenShareName[] =
    "Mac System Audio Loopback for Screen Sharing";
const char kMacLoopbackAudioForScreenShareDescription[] =
    "Enable system audio sharing when screen sharing on macOS 13.0+.";

const char kMacPWAsNotificationAttributionName[] =
    "Mac PWA notification attribution";
const char kMacPWAsNotificationAttributionDescription[] =
    "Route notifications for PWAs on Mac through the app shim, attributing "
    "notifications to the correct apps.";

=======
>>>>>>> chromium
const char kMacSyscallSandboxName[] = "Mac Syscall Filtering Sandbox";
const char kMacSyscallSandboxDescription[] =
    "Controls whether the macOS sandbox filters syscalls.";

const char kMetalName[] = "Metal";
const char kMetalDescription[] =
    "Use Metal instead of OpenGL for rasterization (if out-of-process "
    "rasterization is enabled) and display (if the Skia renderer is enabled)";

<<<<<<< HEAD
const char kSonomaAccessibilityActivationRefinementsName[] =
    "Sonoma Accessibility Activation Refinements";
const char kSonomaAccessibilityActivationRefinementsDescription[] =
    "Refines how Chrome responds to accessibility activation signals on macOS "
    "Sonoma.";

const char kUseAngleDescriptionMac[] =
    "Choose the graphics backend for ANGLE. Metal is the default on all Macs "
    "which can support it. The OpenGL backend is soon to be "
    "deprecated and may contain driver bugs that are not planned to be fixed.";

const char kUseAngleMetal[] = "Metal";

const char kUseAdHocSigningForWebAppShimsName[] =
    "Use Ad-hoc Signing for Web App Shims";
const char kUseAdHocSigningForWebAppShimsDescription[] =
    "Ad-hoc code signing ensures that each PWA app shim has a unique identity. "
    "This allows macOS subsystems to correctly distinguish between multiple "
    "PWAs. Only enabled on macOS 11.7 and later.";

const char kUseSCContentSharingPickerName[] =
    "Use ScreenCaptureKit picker for stream selection";
const char kUseSCContentSharingPickerDescription[] =
    "This feature opens a native picker in macOS 15+ to allow the selection "
    "of a window or screen that will be captured.";
=======
const char kScreenTimeName[] = "Screen Time";
const char kScreenTimeDescription[] =
    "Integrate with the macOS Screen Time system.";
>>>>>>> chromium

const char kBlockRootWindowAccessibleNameChangeEventName[] =
    "Block Root Window Accessible Name Change Event";
const char kBlockRootWindowAccessibleNameChangeEventDescription[] =
    "This feature prevents the firing of accessible name change events on the "
    "Root Window of MacOS applications. By blocking these events, it ensures "
    "that changes to the accessible name of Root Window do not trigger "
    "notifications to assistive technologies. This can be useful in scenarios "
    "where frequent or unnecessary name change events could lead to "
    "performance issues or unwanted behavior in assistive applications.";

#endif

<<<<<<< HEAD
// Windows and Mac -------------------------------------------------------------

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)

const char kLocationProviderManagerName[] =
    "Enable location provider manager for Geolocation API";
const char kLocationProviderManagerDescription[] =
    "Enables usage of the location provider manager to select between "
    "the operating system's location API or the network-based provider "
    "as the data source for Geolocation API.";

const char kUseAngleGL[] = "OpenGL";

#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)

//  Android  --------------------------------------------------

#if BUILDFLAG(IS_ANDROID)

const char kUseAngleDescriptionAndroid[] =
    "Choose the graphics backend for ANGLE. The Vulkan backend is still "
    "experimental, and may contain bugs that "
    "are still being worked on.";

const char kUseAngleGLES[] = "OpenGL ES";
const char kUseAngleVulkan[] = "Vulkan";

#endif  // BUILDFLAG(IS_ANDROID)

// Windows, Mac and Android  --------------------------------------------------

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_ANDROID)

const char kUseAngleName[] = "Choose ANGLE graphics backend";

const char kUseAngleDefault[] = "Default";

#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_ANDROID)

// ChromeOS -------------------------------------------------------------------
=======
// Chrome OS -------------------------------------------------------------------
>>>>>>> chromium

#if BUILDFLAG(IS_CHROMEOS)

const char kAccountManagementFlowsV2Name[] =
    "Enable redesign of account management flows";
const char kAccountManagementFlowsV2Description[] =
    "Enables redesign of account management flows and Account Manager page in "
    "Settings. "
    "See go/betterAM";

const char kAcceleratedMjpegDecodeName[] =
    "Hardware-accelerated mjpeg decode for captured frame";
const char kAcceleratedMjpegDecodeDescription[] =
    "Enable hardware-accelerated MJPEG decode for captured frame where "
    "available.";

<<<<<<< HEAD
const char kAccessibilityBounceKeysName[] = "Bounce keys";
const char kAccessibilityBounceKeysDescription[] =
    "Enables accessibility settings for bounce keys, which ignores quickly "
    "repeated presses of the same keyboard key.";

const char kAccessibilitySlowKeysName[] = "Slow keys";
const char kAccessibilitySlowKeysDescription[] =
    "Enables accessibility settings for slow key, which adds a delay between "
    "when you press a key and when it activates.";

const char kAllowApnModificationPolicyName[] =
    "Allow APN Modification by Policy";
const char kAllowApnModificationPolicyDescription[] =
    "Enables the ChromeOS APN Allow APN Modification policy, which gives "
    "admins the ability to allow or prohibit managed users from modifying "
    "APNs.";

const char kAllowCrossDeviceFeatureSuiteName[] =
    "Allow the use of Cross-Device features";
const char kAllowCrossDeviceFeatureSuiteDescription[] =
    "Allow features such as Nearby Share, PhoneHub, Fast Pair, and Smart Lock, "
    "that require communication with a nearby device. This should be enabled "
    "by default on most platforms, and only disabled in cases where we cannot "
    "guarantee a good experience with the stock Bluetooth hardware (e.g. "
    "ChromeOS Flex). If disabled, this removes all Cross-Device features and "
    "their entries in the Settings app.";

const char kLinkCrossDeviceInternalsName[] =
    "Link Cross-Device internals logging to Feedback reports.";
const char kLinkCrossDeviceInternalsDescription[] =
    "Improves debugging of Cross-Device features by recording more verbose "
    "logs and attaching these logs to filed Feedback reports.";
=======
const char kAllowDisableMouseAccelerationName[] =
    "Allow disabling mouse acceleration";
const char kAllowDisableMouseAccelerationDescription[] =
    "Shows a setting to disable mouse acceleration.";

const char kAllowRepeatedUpdatesName[] =
    "Continue checking for updates before reboot and after initial update.";
const char kAllowRepeatedUpdatesDescription[] =
    "Continues checking to see if there is a more recent update, even if user"
    "has not rebooted to apply the previous update.";
>>>>>>> chromium

const char kAllowScrollSettingsName[] =
    "Allow changes to scroll acceleration/sensitivity for mice/touchpads.";
const char kAllowScrollSettingsDescription[] =
    "Shows settings to enable/disable scroll acceleration and to adjust the "
    "sensitivity for scrolling.";

extern const char kAppListBubbleName[] =
    "Productivity experiment: App Launcher";
extern const char kAppListBubbleDescription[] =
    "To evaluate an enhanced Launcher experience that aims to improve app "
    "workflows by optimizing access to apps, app content, and app actions.";

const char kAppServiceExternalProtocolName[] = "App Service External Protocol";
const char kAppServiceExternalProtocolDescription[] =
    "Use the App Service to provide data for external protocol dialog.";

const char kAppServiceAdaptiveIconName[] = "App Service Adaptive Icons";
const char kAppServiceAdaptiveIconDescription[] =
    "Provide adaptive icons through the App Service";

const char kArcCustomTabsExperimentName[] =
    "Enable Custom Tabs experiment for ARC";
const char kArcCustomTabsExperimentDescription[] =
    "Allow Android apps to use Custom Tabs."
    "This feature only works on the Canary and Dev channels.";

<<<<<<< HEAD
const char kArcEnableAttestationName[] = "Enable ARC attestation";
const char kArcEnableAttestationDescription[] =
    "Allow key and ID attestation to run for keymint";

const char kArcExtendInputAnrTimeoutName[] =
    "Extend input event ANR timeout time";
const char kArcExtendInputAnrTimeoutDescription[] =
    "When enabled, the default input event ANR timeout time will be extended"
    " from 5 seconds to 8 seconds.";

const char kArcExtendIntentAnrTimeoutName[] =
    "Extend broadcast of intent ANR timeout time";
const char kArcExtendIntentAnrTimeoutDescription[] =
    "When enabled, the default broadcast of intent ANR timeout time will be"
    " extended from 10 seconds to 15 seconds for foreground broadcasts, 60"
    " seconds to 90 seconds for background broadcasts.";

const char kArcExtendServiceAnrTimeoutName[] =
    "Extend executing service ANR timeout time";
const char kArcExtendServiceAnrTimeoutDescription[] =
    "When enabled, the default executing service ANR timeout time will be"
    " extended from 20 seconds to 30 seconds for foreground services, 200"
    " seconds to 300 seconds for background services.";

const char kArcFriendlierErrorDialogName[] =
    "Enable friendlier error dialog for ARC";
const char kArcFriendlierErrorDialogDescription[] =
    "Replaces disruptive error dialogs with Chrome notifications for some ANR "
    "and crash events.";

const char kArcIdleManagerName[] = "Enable ARC Idle Manager";
const char kArcIdleManagerDescription[] =
    "ARC will turn on Android's doze mode when idle.";

const char kArcInstantResponseWindowOpenName[] =
    "Enable Instance Response for ARC app window open";
const char kArcInstantResponseWindowOpenDescription[] =
    "In some devices the placeholder window will popup immediately after the "
    "user attempts to launch apps.";
=======
const char kArcDocumentsProviderUnknownSizeName[] =
    "Enable ARC DocumentsProvider unknown file size handling";
const char kArcDocumentsProviderUnknownSizeDescription[] =
    "Allow opening DocumentsProvider files where size is not reported.";

const char kArcFilePickerExperimentName[] =
    "Enable file picker experiment for ARC";
const char kArcFilePickerExperimentDescription[] =
    "Enables using Chrome OS file picker in ARC.";

const char kArcImageCopyPasteCompatName[] =
    "Enable image copy & paste compatibility mode for ARC";
const char kArcImageCopyPasteCompatDescription[] =
    "Allows pasting of images to Android apps through commitContent API and "
    "share intent.";

const char kArcKeyboardShortcutHelperIntegrationName[] =
    "Enable keyboard shortcut helper integration for ARC";
const char kArcKeyboardShortcutHelperIntegrationDescription[] =
    "Shows keyboard shortcuts from Android apps in Chrome OS Shortcut Viewer";
>>>>>>> chromium

const char kArcNativeBridgeToggleName[] =
    "Toggle between native bridge implementations for ARC";
const char kArcNativeBridgeToggleDescription[] =
    "Toggle between native bridge implementations for ARC.";

const char kArcNativeBridge64BitSupportExperimentName[] =
    "Enable experimental 64-bit native bridge support for ARC";
const char kArcNativeBridge64BitSupportExperimentDescription[] =
    "Enable experimental 64-bit native bridge support for ARC where available.";

const char kArcRtVcpuDualCoreName[] =
    "Enable ARC real time vCPU on a device with 2 logical cores online.";
const char kArcRtVcpuDualCoreDesc[] =
    "Enable ARC real time vCPU on a device with 2 logical cores online to "
    "reduce media playback glitch.";

const char kArcRtVcpuQuadCoreName[] =
    "Enable ARC real time vCPU on a device with 3+ logical cores online.";
const char kArcRtVcpuQuadCoreDesc[] =
    "Enable ARC real time vCPU on a device with 3+ logical cores online to "
    "reduce media playback glitch.";

const char kArcUseHighMemoryDalvikProfileName[] =
    "Enable ARC high-memory dalvik profile";
const char kArcUseHighMemoryDalvikProfileDesc[] =
    "Allow Android to use high-memory dalvik profile when applicable for "
    "high-memory devices.";

const char kArcWebAppShareName[] = "Enable sharing to Web Apps from ARC";
const char kArcWebAppShareDescription[] =
    "Allow Android apps to send shared text and files to web apps. When "
    "disabled, web apps may still appear in share sheets, but will not "
    "receive any shared content.";

const char kArcEnableUsapName[] =
    "Enable ARC Unspecialized Application Processes";
const char kArcEnableUsapDesc[] =
    "Enable ARC Unspecialized Application Processes when applicable for "
    "high-memory devices.";

const char kAshEnablePipRoundedCornersName[] =
    "Enable Picture-in-Picture rounded corners.";
const char kAshEnablePipRoundedCornersDescription[] =
    "Enable rounded corners on the Picture-in-Picture window.";

const char kAshEnableUnifiedDesktopName[] = "Unified desktop mode";
const char kAshEnableUnifiedDesktopDescription[] =
    "Enable unified desktop mode which allows a window to span multiple "
    "displays.";

const char kAshSwipingFromLeftEdgeToGoBackName[] =
    "Swping from the left edge of the display to go back to the previous page.";
const char kAshSwipingFromLeftEdgeToGoBackDescription[] =
    "Swiping from the restricted left area of the display with enough drag "
    "distance or fling velocity could go back to the previous page while in "
    "tablet mode.";

<<<<<<< HEAD
const char kAshPickerGifsName[] = "Picker GIFs search";
const char kAshPickerGifsDescription[] = "Enable GIf search for Picker.";

const char kAshSplitKeyboardRefactorName[] = "Split keyboard refactor";
const char kAshSplitKeyboardRefactorDescription[] =
    "Enable split keyboard refactor on ChromeOS.";

const char kAshNullTopRowFixName[] = "Null top row fix";
const char kAshNullTopRowFixDescription[] =
    "Enable the bugfix for keyboards with a null top row descriptor.";

const char kAssistantIphName[] = "Assistant IPH";
const char kAssistantIphDescription[] =
    "Enables showing Assistant IPH on ChromeOS.";

const char kAudioA2DPAdvancedCodecsName[] = "BT A2DP advanced codecs support";
const char kAudioA2DPAdvancedCodecsDescription[] =
    "Enable BT A2DP advanced codecs support";

const char kAudioSelectionImprovementName[] =
    "Enable audio selection improvement algorithm";
const char kAudioSelectionImprovementDescription[] =
    "Enable set-based audio selection improvement algorithm.";

const char kResetAudioSelectionImprovementPrefName[] =
    "Reset audio selection improvement user preference";
const char kResetAudioSelectionImprovementPrefDescription[] =
    "Reset audio selection improvement user preference for testing purpose.";

const char kAutoFramingOverrideName[] = "Auto-framing control override";
const char kAutoFramingOverrideDescription[] =
    "Overrides the default to forcibly enable or disable the auto-framing "
    "feature";

const char kAutocorrectByDefaultName[] = "CrOS autocorrect by default";
const char kAutocorrectByDefaultDescription[] =
    "Enables autocorrect by default experiment on ChromeOS";

const char kAutocorrectParamsTuningName[] = "CrOS autocorrect params tuning";
const char kAutocorrectParamsTuningDescription[] =
    "Enables params tuning experiment for autocorrect on ChromeOS.";

const char kBatteryBadgeIconName[] = "Enables smaller battery badge icon";
const char kBatteryBadgeIconDescription[] =
    "Enables smaller battery badge icons for increased legibility of the "
    "battery percentage.";

const char kBlockTelephonyDevicePhoneMuteName[] =
    "Block Telephony Device Phone Mute";
const char kBlockTelephonyDevicePhoneMuteDescription[] =
    "Block telephony device phone mute HID code so it does not toggle ChromeOS "
    "system microphone mute.";

const char kBluetoothAudioLEAudioOnlyName[] = "Bluetooth Audio LE Audio Only";
const char kBluetoothAudioLEAudioOnlyDescription[] =
    "Enable Bluetooth LE audio and disable classic profiles "
    "(A2DP, HFP, AVRCP). This is used for prototyping and demonstration "
    "purposes.";

const char kBluetoothBtsnoopInternalsName[] =
    "Enables btsnoop collection in chrome://bluetooth-internals";
const char kBluetoothBtsnoopInternalsDescription[] =
    "Enables bluetooth traffic (btsnoop) collection via the page "
    "chrome://bluetooth-internals. Btsnoop logs are essential for debugging "
    "bluetooth issues.";

const char kBluetoothFlossTelephonyName[] = "Bluetooth Floss Telephony";
const char kBluetoothFlossTelephonyDescription[] =
    "Enable Floss to create a Bluetooth HID device that allows applications to "
    "access Bluetooth telephony functions through WebHID.";

const char kBluetoothUseFlossName[] = "Use Floss instead of BlueZ";
const char kBluetoothUseFlossDescription[] =
    "Enables using Floss (also known as Fluoride, Android's Bluetooth stack) "
    "instead of BlueZ. This is meant to be used by developers and is not "
    "guaranteed to be stable";

const char kBluetoothWifiQSPodRefreshName[] =
    "Enable better bluetooth and wifi UI";
const char kBluetoothWifiQSPodRefreshDescription[] =
    "Enables better quick settings UI for bluetooth and wifi error states";

const char kBluetoothUseLLPrivacyName[] = "Enable LL Privacy in Floss";
const char kBluetoothUseLLPrivacyDescription[] =
    "Enable address resolution offloading to Bluetooth Controller if "
    "supported. Modifying this flag will cause Bluetooth Controller to reset.";

const char kCampbellGlyphName[] = "Enable glyph for Campbell";
const char kCampbellGlyphDescription[] = "Enables a Campbell glyph.";

const char kCampbellKeyName[] = "Key to enable glyph for Campbell";
const char kCampbellKeyDescription[] =
    "Secret key to enable glyph for Campbell";

const char kCaptureModeEducationName[] = "Enable Capture Mode Education";
const char kCaptureModeEducationDescription[] =
    "Enables the Capture Mode Education nudges and tutorials that inform users "
    "of the screenshot keyboard shortcut and the screen capture tool in the "
    "quick settings menu.";

const char kCaptureModeEducationBypassLimitsName[] =
    "Enable Capture Mode Education bypass limits";
const char kCaptureModeEducationBypassLimitsDescription[] =
    "Enables bypassing the 3 times / 24 hours show limit for Capture Mode "
    "Education nudges and tutorials, so they can be viewed repeatedly for "
    "testing purposes.";

const char kDeskButtonName[] = "Desk button in shelf";
const char kDeskButtonDescription[] =
    "Show a desk button that provides quick access to the desk menu in the "
    "shelf in clamshell mode when there is more than one desk.";

const char kCrosContentAdjustedRefreshRateName[] =
    "Content Adjusted Refresh Rate";
const char kCrosContentAdjustedRefreshRateDescription[] =
    "Allows the display to adjust the refresh rate in order to match content.";

const char kCrosSoulName[] = "CrOS SOUL";
const char kCrosSoulDescription[] = "Enable the CrOS SOUL feature.";

const char kCrosSoulGravediggerName[] = "CrOS SOUL Gravedigger";
const char kCrosSoulGravediggerDescription[] = "Use Gravedigger.";

const char kDesksTemplatesName[] = "Desk Templates";
const char kDesksTemplatesDescription[] =
    "Streamline workflows by saving a group of applications and windows as a "
    "launchable template in a new desk";
=======
const char kBluetoothAdvertisementMonitoringName[] =
    "Bluetooth Advertisement Monitoring";
const char kBluetoothAdvertisementMonitoringDescription[] =
    "Advertisement monitoring allows applications to register low energy "
    "scanners that filter low energy advertisements in a power-efficient "
    "manner.";

const char kBluetoothAggressiveAppearanceFilterName[] =
    "Aggressive Bluetooth device filtering";
const char kBluetoothAggressiveAppearanceFilterDescription[] =
    "Enables a more aggressive Bluetooth filter in the UI to hide devices that "
    "likely cannot be connected to.";

const char kBluetoothFixA2dpPacketSizeName[] = "Bluetooth fix A2DP packet size";
const char kBluetoothFixA2dpPacketSizeDescription[] =
    "Fixes Bluetooth A2DP packet size to a smaller default value to improve "
    "audio quality and may fix audio stutter.";

const char kBluetoothRevampName[] = "Bluetooth Revamp";
const char kBluetoothRevampDescription[] =
    "Enables the Chrome OS Bluetooth Revamp, which updates Bluetooth system UI "
    "and related infrastructure.";

const char kBluetoothWbsDogfoodName[] = "Bluetooth WBS dogfood";
const char kBluetoothWbsDogfoodDescription[] =
    "Enables Bluetooth wideband speech mic as default audio option. "
    "Note that flipping this flag makes no difference on most of the "
    "Chrome OS models, because Bluetooth WBS is either unsupported "
    "or fully launched. Only on the few models that Bluetooth WBS is "
    "still stablizing this flag will take effect.";

const char kButtonARCNetworkDiagnosticsName[] = "ARC Network Tests Button";
const char kButtonARCNetworkDiagnosticsDescription[] =
    "Enables the display of a button on the ARC Provisioning failure dialog "
    "that opens the connectivity section of the diagnostics app.";
>>>>>>> chromium

const char kForceControlFaceAeName[] = "Force control face AE";
const char kForceControlFaceAeDescription[] =
    "Control this flag to force enable or disable face AE for camera";

const char kCategoricalSearchName[] = "Launcher Categorical Search";
const char kCategoricalSearchDescription[] =
    "Launcher search results grouped by categories";

<<<<<<< HEAD
const char kCellularUseSecondEuiccName[] = "Use second Euicc";
const char kCellularUseSecondEuiccDescription[] =
    "When enabled Cellular Setup and Settings UI will use the second available "
    "eUICC that's exposed by Hermes.";
=======
const char kCdmFactoryDaemonName[] = "CDM Factory Daemon";
const char kCdmFactoryDaemonDescription[] =
    "Use the CDM daemon instead of the library CDM";
>>>>>>> chromium

const char kCellularAllowPerNetworkRoamingName[] =
    "Allow per-networking roaming";
const char kCellularAllowPerNetworkRoamingDescription[] =
    "Allows per-network cellular roaming configuration when cellular roaming "
    "is not disabled for the device through enterprise policy.";

<<<<<<< HEAD
const char kClipboardHistoryUrlTitlesName[] =
    "Show page titles for copied URLs in the clipboard history menu";
const char kClipboardHistoryUrlTitlesDescription[] =
    "When clipboard-history-refresh is also enabled, this flag enables an "
    "annotation for copied URLs in the clipboard history menu: If the URL has "
    "been visited, its page title will appear as part of the URL's menu item.";
=======
const char kCellularForbidAttachApnName[] = "Forbid Use Attach APN";
const char kCellularForbidAttachApnDescription[] =
    "If enabled, the value of |kCellularUseAttachApn| should have no effect "
    "and the LTE attach APN configuration will not be sent to the modem. This "
    "flag exists because the |kCellularUseAttachApn| flag can be enabled "
    "by command-line arguments via board overlays which takes precedence over "
    "finch configs, which may be needed to turn off the Attach APN feature.";

const char kCellularUseAttachApnName[] = "Cellular use Attach APN";
const char kCellularUseAttachApnDescription[] =
    "Use the mobile operator database to set explicitly an Attach APN "
    "for the LTE connections rather than letting the modem decide which "
    "attach APN to use or retrieve it from the network";
>>>>>>> chromium

const char kCellularUseExternalEuiccName[] = "Use external Euicc";
const char kCellularUseExternalEuiccDescription[] =
    "When enabled Cellular Setup and Settings UI will use the first available "
    "external Euicc.";

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
const char kCampaignsComponentUpdaterTestTagName[] = "Campaigns test tag";
const char kCampaignsComponentUpdaterTestTagDescription[] =
    "Tags used for component updater to select Omaha cohort for Growth "
    "Campaigns.";
const char kCampaignsOverrideName[] = "Campaigns override";
const char kCampaignsOverrideDescription[] =
    "Base64 encoded Growth campaigns used for testing.";
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
const char kContextualNudgesName[] =
    "Contextual nudges for user gesture education";
const char kContextualNudgesDescription[] =
    "Enables contextual nudges, periodically showing the user a label "
    "explaining how to interact with a particular UI element using gestures.";
>>>>>>> chromium

const char kCroshSWAName[] = "Crosh System Web App";
const char kCroshSWADescription[] =
    "When enabled, crosh (Chrome OS Shell) will run as a tabbed System Web App "
    "rather than a normal browser tab.";

const char kCrosLanguageSettingsUpdate2Name[] = "Language Settings Update 2";
const char kCrosLanguageSettingsUpdate2Description[] =
    "Enables the second language settings update. Requires "
    "#enable-cros-language-settings-update to be enabled.";

const char kCrosOnDeviceGrammarCheckName[] = "On-device Grammar Check";
const char kCrosOnDeviceGrammarCheckDescription[] =
    "Enable new on-device grammar check component.";

const char kCrosRegionsModeName[] = "Cros-regions load mode";
const char kCrosRegionsModeDescription[] =
    "This flag controls cros-regions load mode";
const char kCrosRegionsModeDefault[] = "Default";
const char kCrosRegionsModeOverride[] = "Override VPD values.";
const char kCrosRegionsModeHide[] = "Hide VPD values.";

const char kCrostiniDiskResizingName[] = "Allow resizing Crostini disks";
const char kCrostiniDiskResizingDescription[] =
    "Use preallocated user-resizeable disks for Crostini instead of sparse "
    "automatically sized disks.";

<<<<<<< HEAD
const char kChromeboxUsbPassthroughRestrictionsName[] =
    "Limit primary mice/keyboards from USB passthrough on chromeboxes";
const char kChromeboxUsbPassthroughRestrictionsDescription[] =
    "When enabled, attempts to prevent primary mice/keyboard from being passed "
    "through to guest environments on chromebox-style devices.  If you have "
    "issues with passing through a USB peripheral on a chromebox, you can "
    "try disabling this feature.";

const char kDisableBruschettaInstallChecksName[] =
    "Disable Bruschetta Installer Checks";
const char kDisableBruschettaInstallChecksDescription[] =
    "Disables the built-in checks the Bruschetta installer performs before "
    "running the install process.";

const char kCrostiniContainerInstallName[] =
    "Debian version for new Crostini containers";
const char kCrostiniContainerInstallDescription[] =
    "New Crostini containers will use this Debian version";
=======
const char kCrostiniUseBusterImageName[] = "New Crostini containers use Buster";
const char kCrostiniUseBusterImageDescription[] =
    "New Crostini containers use Debian Buster images instead of Debian "
    "Stretch.";
>>>>>>> chromium

const char kCrostiniGpuSupportName[] = "Crostini GPU Support";
const char kCrostiniGpuSupportDescription[] = "Enable Crostini GPU support.";

const char kCrostiniUseDlcName[] = "Crostini Use DLC";
const char kCrostiniUseDlcDescription[] =
    "Download the termina VM using the new DLC service instead of the old "
    "component updater.";

const char kCrostiniResetLxdDbName[] = "Crostini Reset LXD DB on launch";
const char kCrostiniResetLxdDbDescription[] =
    "Recreates the LXD database every time we launch it";

const char kCryptAuthV2DeviceActivityStatusName[] =
    "CryptAuth Device Activity Status";
const char kCryptAuthV2DeviceActivityStatusDescription[] =
    "Use the CryptAuth GetDevicesActivityStatus API to sort devices.";

const char kCryptAuthV2DeviceActivityStatusUseConnectivityName[] =
    "CryptAuth Device Activity Status: Use connectivity status";
const char kCryptAuthV2DeviceActivityStatusUseConnectivityDescription[] =
    "Utilize the connectivity status from the CryptAuth "
    "GetDevicesActivityStatus API to sort devices.";

const char kCryptAuthV2DeviceSyncName[] = "CryptAuth v2 DeviceSync";
const char kCryptAuthV2DeviceSyncDescription[] =
    "Use the CryptAuth v2 DeviceSync protocol. Note: v1 DeviceSync will "
    "continue to run until the deprecation flag is flipped.";

const char kCryptAuthV2EnrollmentName[] = "CryptAuth v2 Enrollment";
const char kCryptAuthV2EnrollmentDescription[] =
    "Use the CryptAuth v2 Enrollment protocol.";

<<<<<<< HEAD
const char kCameraAppPdfOcrName[] = "Camera App PDF OCR";
const char kCameraAppPdfOcrDescription[] =
    "Enable this flag to make text on PDFs saved from Camera app accessible.";

const char kCameraAppPreviewOcrName[] = "Camera App Preview OCR";
const char kCameraAppPreviewOcrDescription[] =
    "Enable this flag to use OCR features on preview in Camera app.";

const char kConchName[] = "Conch feature";
const char kConchDescription[] = "Enable Conch on ChromeOS.";

const char kConchExpandTranscriptionLanguageName[] =
    "Transcription language options for Conch";
const char kConchExpandTranscriptionLanguageDescription[] =
    "Expand transcription language options for Conch on ChromeOS.";

const char kConchGenAiName[] = "GenAI features for Conch";
const char kConchGenAiDescription[] =
    "Enable this flag to use GenAI for Conch on ChromeOS.";

const char kConchLargeModelName[] = "GenAI models for Conch";
const char kConchLargeModelDescription[] =
    "Enable this flag to use large model for Conch on ChromeOS. Note that "
    "GenAI features may become unusable if models are unavailable on this "
    "device";

const char kConchSystemAudioFromMicName[] = "System audio capture for Conch";
const char kConchSystemAudioFromMicDescription[] =
    "Capture system audio from microphone for Conch on ChromeOS.";

#if BUILDFLAG(IS_CHROMEOS)
const char kDemoModeComponentUpdaterTestTagName[] = "Demo Mode test tag";
const char kDemoModeComponentUpdaterTestTagDescription[] =
    "Tags used for component updater to select Omaha cohort for Demo Mode.";
#endif  // BUILDFLAG(IS_CHROMEOS)

const char kDeskProfilesName[] = "Desk profiles";
const char kDeskProfilesDescription[] =
    "Enable association of lacros profiles with desks.";
=======
const char kDisableBufferBWCompressionName[] =
    "Disable buffer bandwidth compression";
const char kDisableBufferBWCompressionDescription[] =
    "Disable bandwidth compression when allocating buffers";
>>>>>>> chromium

const char kDisableCancelAllTouchesName[] = "Disable CancelAllTouches()";
const char kDisableCancelAllTouchesDescription[] =
    "If enabled, a canceled touch will not force all other touches to be "
    "canceled.";

const char kDisableCryptAuthV1DeviceSyncName[] =
    "Disable CryptAuth v1 DeviceSync";
const char kDisableCryptAuthV1DeviceSyncDescription[] =
    "Disable the CryptAuth v1 DeviceSync protocol. The v2 DeviceSync flag "
    "should be enabled before this flag is flipped.";

const char kDisableIdleSocketsCloseOnMemoryPressureName[] =
    "Disable closing idle sockets on memory pressure";
const char kDisableIdleSocketsCloseOnMemoryPressureDescription[] =
    "If enabled, idle sockets will not be closed when chrome detects memory "
    "pressure. This applies to web pages only and not to internal requests.";

const char kDisableExplicitDmaFencesName[] = "Disable explicit dma-fences";
const char kDisableExplicitDmaFencesDescription[] =
    "Always rely on implicit synchronization between GPU and display "
    "controller instead of using dma-fences explicitly when available.";

const char kDisplayAlignmentAssistanceName[] =
    "Enable Display Alignment Assistance";
const char kDisplayAlignmentAssistanceDescription[] =
    "Show indicators on shared edges of the displays when user is "
    "attempting to move their mouse over to another display. Show preview "
    "indicators when the user is moving a display in display layouts.";

<<<<<<< HEAD
const char kEnableLibinputToHandleTouchpadName[] =
    "Enable libinput to handle touchpad.";
const char kEnableLibinputToHandleTouchpadDescription[] =
    "Use libinput instead of the gestures library to handle touchpad."
    "Libgesures works very well on modern devices but fails on legacy"
    "devices. Use libinput if an input device doesn't work or is not working"
    "well.";

const char kEnableFakeKeyboardHeuristicName[] =
    "Enable Fake Keyboard Heuristic";
const char kEnableFakeKeyboardHeuristicDescription[] =
    "Enable heuristic to prevent non-keyboard devices from pretending "
    "to be keyboards. Primarily assists in preventing the virtual keyboard "
    "from being disabled unintentionally.";

const char kEnableFakeMouseHeuristicName[] = "Enable Fake Mouse Heuristic";
const char kEnableFakeMouseHeuristicDescription[] =
    "Enable heuristic to prevent non-mouse devices from pretending "
    "to be mice. Primarily assists in preventing fake entries "
    "appearing in the input settings menu.";

const char kFastPairDebugMetadataName[] = "Enable Fast Pair Debug Metadata";
const char kFastPairDebugMetadataDescription[] =
    "Enables Fast Pair to use Debug metadata when checking device "
    "advertisements, allowing notifications to pop up for debug-mode only "
    "devices.";

const char kFaceRetouchOverrideName[] =
    "Enable face retouch using the relighting button in the VC panel";
const char kFaceRetouchOverrideDescription[] =
    "Enables or disables the face retouch feature using the relighting button "
    "in the VC panel.";

const char kFastPairHandshakeLongTermRefactorName[] =
    "Enable Fast Pair Handshake Long Term Refactor";
const char kFastPairHandshakeLongTermRefactorDescription[] =
    "Enables long term refactored handshake logic for Google Fast Pair "
    "service.";

const char kFastPairKeyboardsName[] = "Enable Fast Pair Keyboards";
const char kFastPairKeyboardsDescription[] =
    "Enables prototype support for Fast Pair for keyboards.";

const char kFastPairPwaCompanionName[] = "Enable Fast Pair Web Companion";
const char kFastPairPwaCompanionDescription[] =
    "Enables Fast Pair Web Companion link after device pairing.";

const char kFastPairDevicesBluetoothSettingsName[] =
    "Enable Fast Pair Devices in Bluetooth Settings";
const char kFastPairDevicesBluetoothSettingsDescription[] =
    "Enables the Fast Pair Bluetooth Settings page to display a list of the "
    "user's devices available for Subsequent Pairing.";

const char kFrameSinkDesktopCapturerInCrdName[] =
    "Enable FrameSinkDesktopCapturer in CRD";
const char kFrameSinkDesktopCapturerInCrdDescription[] =
    "Enables the use of FrameSinkDesktopCapturer in the video streaming for "
    "CRD, "
    "replacing the use of AuraDesktopCapturer";
=======
const char kDisplayIdentificationName[] =
    "Enable display identification highlight";
const char kDisplayIdentificationDescription[] =
    "Shows a blue highlight around the edges of the display that is selected "
    "in the Displays Settings page. Only shown when the Displays Settings page "
    "is open.";
>>>>>>> chromium

const char kUseHDRTransferFunctionName[] =
    "Monitor/Display HDR transfer function";
const char kUseHDRTransferFunctionDescription[] =
    "Allows using the HDR transfer functions of any connected monitor that "
    "supports it";

const char kDisableOfficeEditingComponentAppName[] =
    "Disable Office Editing for Docs, Sheets & Slides";
const char kDisableOfficeEditingComponentAppDescription[] =
    "Disables Office Editing for Docs, Sheets & Slides component app so "
    "handlers won't be registered, making it possible to install another "
    "version for testing.";

const char kDoubleTapToZoomInTabletModeName[] =
    "Double-tap to zoom in tablet mode";
const char kDoubleTapToZoomInTabletModeDescription[] =
    "If Enabled, double tapping in webpages while in tablet mode will zoom the "
    "page.";

<<<<<<< HEAD
const char kDriveFsMirroringName[] = "Enable local to Drive mirror sync";
const char kDriveFsMirroringDescription[] =
    "Enable mirror sync between local files and Google Drive";
=======
const char kQuickSettingsPWANotificationsName[] =
    "Enable setting of PWA notification permissions in quick settings ";
const char kQuickSettingsPWANotificationsDescription[] =
    "Replace website notification permissions with PWA notification "
    "permissions in the quick settings menu. Website notification permissions "
    "settings will be migrated to the lacros - chrome browser.";

const char kDriveFsBidirectionalNativeMessagingName[] =
    "Enable bidirectional native messaging for DriveFS";
const char kDriveFsBidirectionalNativeMessagingDescription[] =
    "Enable enhanced native messaging host to communicate with DriveFS.";
>>>>>>> chromium

const char kEnableAppDataSearchName[] = "Enable app data search in launcher";
const char kEnableAppDataSearchDescription[] =
    "Allow launcher search to access data available through Firebase App "
    "Indexing";

const char kCrOSEnforceSystemAecName[] = "Enforce using the system AEC in CrAS";
const char kCrOSEnforceSystemAecDescription[] =
    "Enforces using the system variant in CrAS of the AEC";

const char kCrOSEnforceSystemAecAgcName[] =
    "Enforce using the system AEC and AGC in CrAS";
const char kCrOSEnforceSystemAecAgcDescription[] =
    "Enforces using the system variants in CrAS of the AEC and AGC.";

const char kCrOSEnforceSystemAecNsName[] =
    "Enforce using the system AEC and NS in CrAS";
const char kCrOSEnforceSystemAecNsDescription[] =
    "Enforces using the system variants in CrAS of the AEC and NS.";

const char kCrOSEnforceSystemAecNsAgcName[] =
    "Enforce using the system AEC, NS and AGC in CrAS";
const char kCrOSEnforceSystemAecNsAgcDescription[] =
    "Enforces using the system variants in CrAS of the AEC, NS and AGC.";

const char kEnableAppReinstallZeroStateName[] =
    "Enable Zero State App Reinstall Suggestions.";
const char kEnableAppReinstallZeroStateDescription[] =
    "Enable Zero State App Reinstall Suggestions feature in launcher, which "
    "will show app reinstall recommendations at end of zero state list.";

const char kEnableAppGridGhostName[] = "App Grid Ghosting";
const char kEnableAppGridGhostDescription[] =
    "Enables ghosting during an item drag in launcher.";

const char kEnableArcUnifiedAudioFocusName[] =
    "Enable unified audio focus on ARC";
const char kEnableArcUnifiedAudioFocusDescription[] =
    "If audio focus is enabled in Chrome then this will delegate audio focus "
    "control in Android apps to Chrome.";

const char kEnableAssistantAppSupportName[] = "Enable Assistant App Support";
const char kEnableAssistantAppSupportDescription[] =
    "Enable the Assistant App Support feature";

const char kEnableAssistantBetterOnboardingName[] =
    "Enable Assistant Better Onboarding";
const char kEnableAssistantBetterOnboardingDescription[] =
    "Enables the Assistant better onboarding experience.";

const char kEnableAssistantLauncherIntegrationName[] =
    "Assistant & Launcher integration";
const char kEnableAssistantLauncherIntegrationDescription[] =
    "Combine Launcher search with the power of Assistant to provide the most "
    "useful answer for each query. Requires Assistant to be enabled.";

const char kEnableAssistantLauncherUIName[] = "Assistant Launcher UI";
const char kEnableAssistantLauncherUIDescription[] =
    "Enables the embedded Assistant UI in the app list. Requires Assistant to "
    "be enabled.";

const char kEnableAssistantRoutinesName[] = "Assistant Routines";
const char kEnableAssistantRoutinesDescription[] = "Enable Assistant Routines.";

const char kEnableAutoSelectName[] = "Auto Select";
const char kEnableAutoSelectDescription[] =
    "Automatically select the word under cursor on contextual menu click.";

const char kEnableBackgroundBlurName[] = "Enable background blur.";
const char kEnableBackgroundBlurDescription[] =
    "Enables background blur for the Launcher, Shelf, Unified System Tray etc.";

const char kEnhancedClipboardName[] =
    "Productivity Experiment: Enable Enhanced Clipboard";
const char kEnhancedClipboardDescription[] =
    "Enables an experimental clipboard history which aims to reduce context "
    "switching. After copying to the clipboard, press search + v to show the "
    "history. Selecting something from the menu will result in a paste to the "
    "active window.";

const char kEnhancedClipboardNudgeSessionResetName[] =
    "Enable resetting enhanced clipboard nudge data";
const char kEnhancedClipboardNudgeSessionResetDescription[] =
    "When enabled, this will reset the clipboard nudge shown data on every new "
    "user session, allowing the nudge to be shown again.";

const char kEnhancedClipboardScreenshotNudgeName[] =
    "Enable clipboard history screenshot nudge";
const char kEnhancedClipboardScreenshotNudgeDescription[] =
    "When enabled, the keyboard shortcut for clipboard history will show in "
    "the screenshot notification banner in clamshell mode.";

const char kEnableCrOSActionRecorderName[] = "Enable CrOS action recorder";
const char kEnableCrOSActionRecorderDescription[] =
    "When enabled, each app launching, file opening, setting change, and url "
    "visiting will be logged locally into an encrypted file. Should not be "
    "enabled. Be aware that hash option only provides a thin layer of privacy.";

const char kEnableDnsProxyName[] = "Enable DNS proxy service";
const char kEnableDnsProxyDescription[] =
    "When enabled, standard DNS queries will be proxied through the system "
    "service";

<<<<<<< HEAD
const char kEnableRootNsDnsProxyName[] =
    "Enable DNS proxy service running on the root network namespace for "
    "ChromeOS";
const char kEnableRootNsDnsProxyDescription[] =
    "When enabled, DNS proxy service runs on the root network namespace "
    "instead of inside a specified network namespace";

const char kEnableEdidBasedDisplayIdsName[] = "Enable EDID-based display IDs";
const char kEnableEdidBasedDisplayIdsDescription[] =
    "When enabled, a display's ID will be produced by hashing certain values "
    "in the display's EDID blob. EDID-based display IDs allow ChromeOS to "
    "consistently identify previously connected displays, regardless of the "
    "physical port they were connected to, and load user display layouts more "
    "accurately.";

const char kTiledDisplaySupportName[] = "Enable tile display support";
const char kTiledDisplaySupportDescription[] =
    "When enabled, tiled displays will be represented by a single display in "
    "ChromeOS, rather than each tile being a separate display.";

const char kEnableDozeModePowerSchedulerName[] =
    "Enable doze mode power scheduler";
const char kEnableDozeModePowerSchedulerDescription[] =
    "Enable doze mode power scheduler.";

const char kEnableExternalKeyboardsInDiagnosticsAppName[] =
    "Enable external keyboards in the Diagnostics App";
const char kEnableExternalKeyboardsInDiagnosticsAppDescription[] =
    "Shows external keyboards in the Diagnostics App's input section. Requires "
    "#enable-input-in-diagnostics-app to be enabled.";

const char kEnableFastInkForSoftwareCursorName[] =
    "Enable fast ink for software cursor";
const char kEnableFastInkForSoftwareCursorDescription[] =
    "When enabled, software cursor will use fast ink to display cursor with "
    "minimal latency. "
    "However, it might also cause tearing artifacts.";
=======
const char kDnsProxyEnableDOHName[] =
    "Enable DNS-over-HTTPS in the DNS proxy service";
const char kDnsProxyEnableDOHDescription[] =
    "When enabled, the DNS proxy will perform DNS-over-HTTPS in accordance "
    "with the Chrome OS SecureDNS settings.";
>>>>>>> chromium

const char kEnableHostnameSettingName[] = "Enable setting the device hostname";
const char kEnableHostnameSettingDescription[] =
    "Enables the ability to set the Chrome OS hostname, the name of the device "
    "that is exposed to the local network";

const char kEnableGeneratedWebApksName[] = "Generated WebAPKs";
const char kEnableGeneratedWebApksDescription[] =
    "When enabled, generates and installs a WebAPK inside ARC for each "
    "installed and eligible PWA.";

const char kEnableGesturePropertiesDBusServiceName[] =
    "Enable gesture properties D-Bus service";
const char kEnableGesturePropertiesDBusServiceDescription[] =
    "Enable a D-Bus service for accessing gesture properties, which are used "
    "to configure input devices.";

const char kEnableGoogleAssistantDspName[] =
    "Enable Google Assistant with hardware-based hotword";
const char kEnableGoogleAssistantDspDescription[] =
    "Enable an experimental feature that uses hardware-based hotword detection "
    "for Assistant. Only a limited number of devices have this type of "
    "hardware support.";

const char kEnableGoogleAssistantStereoInputName[] =
    "Enable Google Assistant with stereo audio input";
const char kEnableGoogleAssistantStereoInputDescription[] =
    "Enable an experimental feature that uses stereo audio input for hotword "
    "and voice to text detection in Google Assistant.";

const char kEnableGoogleAssistantAecName[] = "Enable Google Assistant AEC";
const char kEnableGoogleAssistantAecDescription[] =
    "Enable an experimental feature that removes local feedback from audio "
    "input to help hotword and ASR when background audio is playing.";

const char kEnableHeuristicStylusPalmRejectionName[] =
    "Enable Heuristic for Stylus/Palm Rejection.";
const char kEnableHeuristicStylusPalmRejectionDescription[] =
    "Enable additional heuristic palm rejection logic when interacting with "
    "stylus usage. Not intended for all devices.";

const char kEnableInputEventLoggingName[] = "Enable input event logging";
const char kEnableInputEventLoggingDescription[] =
    "Enable detailed logging of input events from touchscreens, touchpads, and "
    "mice. These events include the locations of all touches as well as "
    "relative pointer movements, and so may disclose sensitive data. They "
    "will be included in feedback reports and system logs, so DO NOT ENTER "
    "SENSITIVE INFORMATION with this flag enabled.";

const char kEnableInputInDiagnosticsAppName[] =
    "Enable input device cards in the Diagnostics App";
const char kEnableInputInDiagnosticsAppDescription[] =
    "Enable input device cards in the Diagnostics App";

const char kEnableInputNoiseCancellationUiName[] =
    "Enable Input Noise Cancellation UI.";
const char kEnableInputNoiseCancellationUiDescription[] =
    "Enable toggling input noise cancellation through the Quick Settings. By "
    "default, this flag is disabled.";

<<<<<<< HEAD
const char kEnableKeyboardUsedPalmSuppressionName[] =
    "Use keyboard based palm suppression.";
const char kEnableKeyboardUsedPalmSuppressionDescription[] =
    "Enable keyboard usage based palm suppression.";

const char kEnableNeuralPalmAdaptiveHoldName[] = "Palm Rejection Adaptive Hold";
const char kEnableNeuralPalmAdaptiveHoldDescription[] =
    "Enable adaptive hold in palm rejection.  Not compatible with all devices.";
=======
const char kEnableLauncherSearchNormalizationName[] =
    "Enable normalization of launcher search results";
const char kEnableLauncherSearchNormalizationDescription[] =
    "Enable normalization of scores from different providers to the "
    "launcher.";
>>>>>>> chromium

const char kNewDragSpecInLauncherName[] = "Enable Launcher App Paging";
const char kNewDragSpecInLauncherDescription[] =
    "Show visual affordance of launcher app pages and enable page previews "
    "when dragging apps.";

const char kEnableNeuralStylusPalmRejectionName[] =
    "Enable Neural Palm Detection";
const char kEnableNeuralStylusPalmRejectionDescription[] =
    "Experimental: Enable Neural Palm detection. Not compatible with all "
    "devices.";

const char kEnableOsFeedbackName[] = "Enable updated Feedback Tool App";
const char kEnableOsFeedbackDescription[] =
    "Enable the feedback tool with new UX design that helps users mitigate "
    "the issues while writing feedback and makes the UI easier to use.";

const char kEnableNewShortcutMappingName[] = "Enable New Shortcut Mapping";
const char kEnableNewShortcutMappingDescription[] =
    "Enables experimental new shortcut mapping";

const char kEnablePalmOnMaxTouchMajorName[] =
    "Enable Palm when Touch is Maximum";
const char kEnablePalmOnMaxTouchMajorDescription[] =
    "Experimental: Enable Palm detection when the touchscreen reports max "
    "size. Not compatible with all devices.";

const char kEnablePalmOnToolTypePalmName[] =
    "Enable Palm when Tool Type is Palm";
const char kEnablePalmOnToolTypePalmDescription[] =
    "Experimental: Enable palm detection when touchscreen reports "
    "TOOL_TYPE_PALM. Not compatible with all devices.";

const char kEnablePalmSuppressionName[] =
    "Enable Palm Suppression with Stylus.";
const char kEnablePalmSuppressionDescription[] =
    "If enabled, suppresses touch when a stylus is on a touchscreen.";

const char kEnablePlayStoreSearchName[] = "Enable Play Store search";
const char kEnablePlayStoreSearchDescription[] =
    "Enable Play Store search in launcher.";

const char kEnableQuickAnswersName[] = "Enable Quick Answers";
const char kEnableQuickAnswersDescription[] =
    "Enable the Quick Answers feature";

const char kEnableQuickAnswersOnEditableTextName[] =
    "Enable Quick Answers on editable text";
const char kEnableQuickAnswersOnEditableTextDescription[] =
    "Enable Quick Answers on editable text.";

const char kEnableQuickAnswersRichUiName[] = "Enable Quick Answers Rich UI";
const char kEnableQuickAnswersRichUiDescription[] =
    "Enable the Quick Answers rich UI.";

<<<<<<< HEAD
const char kEnableToggleCameraShortcutName[] =
    "Enable shortcut to toggle camera access";
const char kEnableToggleCameraShortcutDescription[] =
    "Adds a shortcut to toggle the value of the top level 'Camera access' "
    "setting in the privacy controls section of the Settings app.";

const char kEnableTouchpadsInDiagnosticsAppName[] =
    "Enable touchpad cards in the Diagnostics App";
const char kEnableTouchpadsInDiagnosticsAppDescription[] =
    "Shows touchpad cards in the Diagnostics App's input section. Requires "
    "#enable-input-in-diagnostics-app to be enabled.";
=======
const char kEnableQuickAnswersTextAnnotatorName[] =
    "Enable Quick Answers text annotator";
const char kEnableQuickAnswersTextAnnotatorDescription[] =
    "Enable Quick Answers text annotator.";
>>>>>>> chromium

const char kEnableQuickAnswersTranslationName[] =
    "Enable Quick Answers translation";
const char kEnableQuickAnswersTranslationDescription[] =
    "Enable Quick Answers translation.";

const char kEnableQuickAnswersTranslationCloudAPIName[] =
    "Enable Quick Answers translation using the Cloud API";
const char kEnableQuickAnswersTranslationCloudAPIDescription[] =
    "Enable Quick Answers translation using the Cloud API.";

const char kEnableQuickAnswersV2Name[] = "Enable Quick Answers V2 features";
const char kEnableQuickAnswersV2Description[] =
    "Enable Quick Answers V2 features.";

const char kTrimOnFreezeName[] = "Trim Working Set on freeze";
const char kTrimOnFreezeDescription[] = "Trim Working Set on all frames frozen";

const char kTrimOnMemoryPressureName[] = "Trim Working Set on memory pressure";
const char kTrimOnMemoryPressureDescription[] =
    "Trim Working Set periodically on memory pressure";

const char kEcheSWAName[] = "Enable Eche App SWA.";
const char kEcheSWADescription[] = "Enable the SWA version of the Eche.";

const char kEcheSWAResizingName[] = "Allow resizing Eche App.";
const char kEcheSWAResizingDescription[] =
    "Enable a naive resize for the Eche window";

<<<<<<< HEAD
const char kEcheLauncherName[] = "Enable the Eche launcher";
const char kEcheLauncherDescription[] =
    "Enables the launcher for all apps for Eche.";

const char kEcheLauncherListViewName[] = "Enable Eche launcher list view";
const char kEcheLauncherListViewDescription[] =
    "Convert Eche launcher from grid view to list view";

const char kEcheLauncherIconsInMoreAppsButtonName[] =
    "Enable app icons in the Eche launcher more apps button";
const char kEcheLauncherIconsInMoreAppsButtonDescription[] =
    "Show app icons in the Eche launcher more apps button";

const char kEcheSWADebugModeName[] = "Enable Eche Debug Mode";
const char kEcheSWADebugModeDescription[] =
    "Save console logs of Eche in the system log";

const char kEcheSWAMeasureLatencyName[] = "Measure Eche E2E Latency";
const char kEcheSWAMeasureLatencyDescription[] =
    "Measure Eche E2E Latency and print all E2E latency logs of Eche in "
    "Console";

const char kEcheSWASendStartSignalingName[] =
    "Enable Eche Send Start Signaling";
const char kEcheSWASendStartSignalingDescription[] =
    "Allows sending start signaling action to establish Eche's WebRTC "
    "connection";

const char kEcheSWADisableStunServerName[] = "Disable Eche STUN server";
const char kEcheSWADisableStunServerDescription[] =
    "Allows disabling the stun servers when establishing a WebRTC connection "
    "to Eche";

const char kEcheSWACheckAndroidNetworkInfoName[] = "Check Android network info";
const char kEcheSWACheckAndroidNetworkInfoDescription[] =
    "Allows CrOS to analyze Android network information to provide more "
    "context on connection errors";

const char kEcheSWAProcessAndroidAccessibilityTreeName[] =
    "Process Android Application Accessibility Tree";
const char kEcheSWAProcessAndroidAccessibilityTreeDescription[] =
    "Allows CrOS to process the Android accessibility tree information of the "
    "currently streaming app.";
=======
const char kEnableNetworkingInDiagnosticsAppName[] =
    "Enable networking cards in the Diagnostics App";
const char kEnableNetworkingInDiagnosticsAppDescription[] =
    "Enable networking cards in the Diagnostics App";
>>>>>>> chromium

const char kEnableOAuthIppName[] =
    "Enable OAuth when printing via the IPP protocol";
const char kEnableOAuthIppDescription[] =
    "Enable OAuth when printing via the IPP protocol";

<<<<<<< HEAD
const char kEnableOngoingProcessesName[] = "Enable Ongoing Processes";
const char kEnableOngoingProcessesDescription[] =
    "Enables use of the new PinnedNotificationView for all ash pinned "
    "notifications, which are now referred to as Ongoing Processes";

const char kEnterOverviewFromWallpaperName[] =
    "Enable entering overview from wallpaper";
const char kEnterOverviewFromWallpaperDescription[] =
    "Experimental feature. Enable entering overview by clicking wallpaper with "
    "mouse click";

const char kEolResetDismissedPrefsName[] =
    "Reset end of life notification prefs";
const char kEolResetDismissedPrefsDescription[] =
    "Reset the end of life notification prefs to their default value, at the "
    "start of the user session. This is meant to make manual testing easier.";

const char kEolIncentiveName[] = "Enable end of life incentives";
const char kEolIncentiveDescription[] =
    "Allows end of life incentives to be shown within the system UI.";

const char kEventBasedLogUpload[] = "Enable event based log uploads";
const char kEventBasedLogUploadDescription[] =
    "Uploads relevant logs to device management server when unexpected events "
    "(e.g. crashes) occur on the device. The feature is guarded by "
    "LogUploadEnabled policy.";

const char kExcludeDisplayInMirrorModeName[] =
    "Enable feature to exclude a display in mirror mode.";
const char kExcludeDisplayInMirrorModeDescription[] =
    "Show toggles in Display Settings to exclude a display in mirror mode.";
=======
const char kEnableSuggestedFilesName[] = "Enable Suggested Files";
const char kEnableSuggestedFilesDescription[] =
    "Enable Suggested Files feature in Launcher, which will show file "
    "suggestions in the suggestion chips when the launcher is opened";
>>>>>>> chromium

const char kExoGamepadVibrationName[] = "Gamepad Vibration for Exo Clients";
const char kExoGamepadVibrationDescription[] =
    "Allow Exo clients like Android to request vibration events for gamepads "
    "that support it.";

const char kExoOrdinalMotionName[] =
    "Raw (unaccelerated) motion for Linux applications";
const char kExoOrdinalMotionDescription[] =
    "Send unaccelerated values as raw motion events to Linux applications.";

const char kExoPointerLockName[] = "Pointer lock for Linux applications";
const char kExoPointerLockDescription[] =
    "Allow Linux applications to request a pointer lock, i.e. exclusive use of "
    "the mouse pointer.";

const char kExoLockNotificationName[] = "Notification bubble for UI lock";
const char kExoLockNotificationDescription[] =
    "Show a notification bubble once an application has switched to "
    "non-immersive fullscreen mode or obtained pointer lock.";

const char kExperimentalAccessibilityDictationExtensionName[] =
    "Experimental accessibility dictation extension.";
const char kExperimentalAccessibilityDictationExtensionDescription[] =
    "Enables the JavaScript dictation extension.";

const char kExperimentalAccessibilityDictationListeningName[] =
    "Experimental accessibility dictation listening duration and behavior.";
const char kExperimentalAccessibilityDictationListeningDescription[] =
    "Enables longer listening with network recognition and listening after "
    "finalized speech for the accessibility dictation feature.";

const char kExperimentalAccessibilityDictationOfflineName[] =
    "Experimental accessibility dictation offline.";
const char kExperimentalAccessibilityDictationOfflineDescription[] =
    "Enables offline speech recognition for the accessibility dictation "
    "feature.";

const char kAccessibilityManifestV3BrailleImeName[] =
    "Changes accessibility extension Braille IME manifest v2 to v3.";
const char kAccessibilityManifestV3BrailleImeDescription[] =
    "Experimental migration of Braille IME from extension manifest v2 to v3.";

const char kAccessibilityManifestV3EnhancedNetworkTtsName[] =
    "Changes accessibility extension Enhanced Network TTS manifest v2 to v3.";
const char kAccessibilityManifestV3EnhancedNetworkTtsDescription[] =
    "Experimental migration of Enhanced Network TTS from extension manifest "
    "v2 to v3.";

const char kExperimentalAccessibilitySwitchAccessTextName[] =
    "Enable enhanced Switch Access text input.";
const char kExperimentalAccessibilitySwitchAccessTextDescription[] =
    "Enable experimental or in-progress Switch Access features for improved "
    "text input";

const char kSwitchAccessPointScanningName[] =
    "Enable point scanning with Switch Access.";
const char kSwitchAccessPointScanningDescription[] =
    "Enable an in-process feature to select points onscreen with Switch "
    "Access.";

<<<<<<< HEAD
const char kFastDrmMasterDropName[] =
    "Drop DRM master tokens without disabling all the displays.";
const char kFastDrmMasterDropDescription[] =
    "Drop DRM master tokens after detaching all the planes off of pipes,"
    "rather than disabling all the displays. Will not work on AMD devices as "
    "they are unable to accept commits without a primary plane.";

const char kFileTransferEnterpriseConnectorName[] =
    "Enable Files Transfer Enterprise Connector.";
const char kFileTransferEnterpriseConnectorDescription[] =
    "Enable the File Transfer Enterprise Connector.";
=======
const char kExperimentalAccessibilitySwitchAccessSetupGuideName[] =
    "Enable setup guide for Switch Access.";
const char kExperimentalAccessibilitySwitchAccessSetupGuideDescription[] =
    "Enable a setup guide to walk through the steps of initially configuring "
    "Switch Access.";
>>>>>>> chromium

const char kMagnifierPanningImprovementsName[] =
    "Enable panning improvements in magnifier";
const char kMagnifierPanningImprovementsDescription[] =
    "Enable feature which adds additional mouse and keyboard panning "
    "functionality in Magnifier.";

const char kMagnifierContinuousMouseFollowingModeSettingName[] =
    "Enable ability to choose continuous mouse following mode in Magnifier "
    "settings";
const char kMagnifierContinuousMouseFollowingModeSettingDescription[] =
    "Enable feature which adds ability to choose new continuous mouse "
    "following mode in Magnifier settings.";

const char kFilesArchivemountName[] = "Archivemount in Files App";
const char kFilesArchivemountDescription[] =
    "Enable mounting various archive formats in File Manager.";

const char kFilesBannerFrameworkName[] =
    "Updated Banner framework in Files app";
const char kFilesBannerFrameworkDescription[] =
    "Enable the updated branner framework in Files app";

const char kFilesSinglePartitionFormatName[] =
    "Enable Partitioning of Removable Disks.";
const char kFilesSinglePartitionFormatDescription[] =
    "Enable partitioning of removable disks into single partition.";

const char kFilesSWAName[] = "Enable Files App SWA.";
const char kFilesSWADescription[] =
    "Enable the SWA version of the file manager.";

const char kFilesTrashName[] = "Enable Files Trash.";
const char kFilesTrashDescription[] =
    "Enable trash for My files volume in Files App.";

const char kFilesZipMountName[] = "New ZIP mounting in Files App";
const char kFilesZipMountDescription[] =
    "Enable new ZIP archive mounting system in File Manager.";

const char kFilesZipPackName[] = "New ZIP packing in Files App";
const char kFilesZipPackDescription[] =
    "Enable new ZIP archive creation system in File Manager.";

const char kFilesZipUnpackName[] = "New ZIP unpacking in Files App";
const char kFilesZipUnpackDescription[] =
    "Enable new ZIP archive extraction system in File Manager.";

const char kForceSpectreVariant2MitigationName[] =
    "Force Spectre variant 2 mitigagtion";
const char kForceSpectreVariant2MitigationDescription[] =
    "Forces Spectre variant 2 mitigation. Setting this to enabled will "
    "override #spectre-variant2-mitigation and any system-level setting that "
    "disables Spectre variant 2 mitigation.";

const char kFiltersInRecentsName[] = "Enable filters in Recents";
const char kFiltersInRecentsDescription[] =
    "Enable file-type filters (Audio, Images, Videos) in Files App Recents "
    "view.";

const char kFocusFollowsCursorName[] = "Focus follows cursor";
const char kFocusFollowsCursorDescription[] =
    "Enable window focusing by moving the cursor.";

const char kFrameThrottleFpsName[] = "Set frame throttling fps.";
const char kFrameThrottleFpsDescription[] =
    "Set the throttle fps for compositor frame submission.";
const char kFrameThrottleFpsDefault[] = "Default";
const char kFrameThrottleFps5[] = "5 fps";
const char kFrameThrottleFps10[] = "10 fps";
const char kFrameThrottleFps15[] = "15 fps";
const char kFrameThrottleFps20[] = "20 fps";
const char kFrameThrottleFps25[] = "25 fps";
const char kFrameThrottleFps30[] = "30 fps";

const char kFullRestoreName[] = "Full restore";
const char kFullRestoreDescription[] = "Chrome OS full restore";

const char kHelpAppBackgroundPageName[] = "Help App Background Page";
const char kHelpAppBackgroundPageDescription[] =
    "Enables the Background page in the help app. The background page is used "
    "to initialize the Help App Launcher search index and show the Discover "
    "tab notification.";

const char kHelpAppDiscoverTabName[] = "Help App Discover Tab";
const char kHelpAppDiscoverTabDescription[] =
    "Enables the Discover tab in the help app. Even if the feature is enabled, "
    "internal app logic might decide not to show the tab.";

const char kHelpAppLauncherSearchName[] = "Help App launcher search";
const char kHelpAppLauncherSearchDescription[] =
    "Enables showing search results from the help app in the launcher.";

const char kHelpAppSearchServiceIntegrationName[] =
    "Help App search service integration";
const char kHelpAppSearchServiceIntegrationDescription[] =
    "Enables the integration between the help app and the local search"
    " service. Includes using the search service for in app search.";

const char kHideArcMediaNotificationsName[] = "Hide ARC media notifications";
const char kHideArcMediaNotificationsDescription[] =
    "Hides media notifications for ARC apps. Requires "
    "#enable-media-session-notifications to be enabled.";

<<<<<<< HEAD
const char kHoldingSpaceSuggestionsName[] = "Enable holding space suggestions";
const char kHoldingSpaceSuggestionsDescription[] =
    "Enables pinned file suggestions in holding space to help the user "
    "understand and discover the ability to pin.";
=======
const char kHoldingSpaceInProgressDownloadsIntegrationName[] =
    "Enable showing in-progress downloads in Tote.";
const char kHoldingSpaceInProgressDownloadsIntegrationDescription[] =
    "Show in-progress download functionality in Tote to increase productivity "
    "by giving users one place to go to monitor and access their downloads.";

const char kImeAssistAutocorrectName[] = "Enable assistive autocorrect";
const char kImeAssistAutocorrectDescription[] =
    "Enable assistive auto-correct features for native IME";
>>>>>>> chromium

const char kImeAssistEmojiEnhancedName[] = "Enable enhanced assistive emojis";
const char kImeAssistEmojiEnhancedDescription[] =
    "Enable enhanced assistive emoji suggestion features for native IME";

const char kImeAssistMultiWordName[] =
    "Enable assistive multi word suggestions";
const char kImeAssistMultiWordDescription[] =
    "Enable assistive multi word suggestions for native IME";

const char kImeAssistMultiWordExpandedName[] =
    "Enable expanded assistive multi word suggestions";
const char kImeAssistMultiWordExpandedDescription[] =
    "Enable expanded assistive multi word suggestions for native IME";

<<<<<<< HEAD
const char kImeKoreanOnlyModeSwitchOnRightAltName[] =
    "Only internal-mode switch on right-Alt in Korean input method";
const char kImeKoreanOnlyModeSwitchOnRightAltDescription[] =
    "When enabled and in Korean input method, right-Alt key location solely "
    "toggles internal Korean/English mode, without Alt modifier functionality";

const char kImeSwitchCheckConnectionStatusName[] =
    "Enable IME switching using global boolean";
const char kImeSwitchCheckConnectionStatusDescription[] =
    "When enabled and swapping between input methods, this prevents a race "
    "condition.";
=======
const char kImeAssistPersonalInfoName[] = "Enable assistive personal info";
const char kImeAssistPersonalInfoDescription[] =
    "Enable auto-complete suggestions on personal infomation for native IME.";

const char kImeEmojiSuggestAdditionName[] =
    "Enable emoji suggestion (addition)";
const char kImeEmojiSuggestAdditionDescription[] =
    "Enable emoji suggestion as addition to the text written for native IME.";

const char kImeMozcProtoName[] = "Enable protobuf on Japanese IME";
const char kImeMozcProtoDescription[] =
    "Enable Japanese IME to use protobuf as interactive message format to "
    "replace JSON";
>>>>>>> chromium

const char kImeServiceDecoderName[] = "ChromeOS IME Service Decoder";
const char kImeServiceDecoderDescription[] =
    "Controls whether ChromeOS system IME works with the NaCl decoders or "
    "the decoders loaded in the IME service.";

const char kImeSystemEmojiPickerName[] = "System emoji picker";
const char kImeSystemEmojiPickerDescription[] =
    "Controls whether a System emoji picker, or the virtual keyboard is used "
    "for inserting emoji.";

<<<<<<< HEAD
const char kImeSystemEmojiPickerJellySupportName[] =
    "Enable jelly colors for the System Emoji Picker";
const char kImeSystemEmojiPickerJellySupportDescription[] =
    "Enable jelly colors for the System Emoji Picker.";
=======
const char kImeSystemEmojiPickerClipboardName[] =
    "System emoji picker clipboard";
const char kImeSystemEmojiPickerClipboardDescription[] =
    "Emoji picker will insert emoji into clipboard if they can't be inserted "
    "into a text field";
>>>>>>> chromium

const char kCrosLanguageSettingsImeOptionsInSettingsName[] =
    "Ime settings in settings";
const char kCrosLanguageSettingsImeOptionsInSettingsDescription[] =
    "Adds IME settings to the settings menu";

const char kIntentHandlingSharingName[] = "Intent handling for sharing";
const char kIntentHandlingSharingDescription[] =
    "Support sharing in Chrome OS intent handling.";

const char kIntentPickerPWAPersistenceName[] = "Intent picker PWA Persistence";
const char kIntentPickerPWAPersistenceDescription[] =
    "Allow user to always open with PWA in intent picker.";

<<<<<<< HEAD
const char kCrosComponentsName[] = "Cros Components";
const char kCrosComponentsDescription[] =
    "Enable cros-component UI elements, replacing other elements.";

const char kLanguagePacksInSettingsName[] = "Language Packs in Settings";
const char kLanguagePacksInSettingsDescription[] =
    "Enables the UI and logic to manage Language Packs in Settings. This is "
    "used for languages and input methods.";

const char kUseMlServiceForNonLongformHandwritingOnAllBoardsName[] =
    "Use ML Service for non-Longform handwriting on all boards";
const char kUseMlServiceForNonLongformHandwritingOnAllBoardsDescription[] =
    "Use ML Service (and DLC Language Packs) for non-Longform handwriting in "
    "Chrome OS 1P Virtual Keyboard on all boards. When this flag is OFF, such "
    "usage exists on certain boards only.";

const char kLauncherContinueSectionWithRecentsName[] =
    "Launcher continue section with recent drive files";
const char kLauncherContinueSectionWithRecentsDescription[] =
    "Adds Google Drive file suggestions based on users' recent activity to "
    "\"Continue where you left off\" section in Launcher.";

const char kLauncherItemSuggestName[] = "Launcher ItemSuggest";
const char kLauncherItemSuggestDescription[] =
    "Allows configuration of experiment parameters for ItemSuggest in the "
    "launcher.";
=======
const char kKeyboardBasedDisplayArrangementInSettingsName[] =
    "Keyboard-based Display Arrangement in Settings";
const char kKeyboardBasedDisplayArrangementInSettingsDescription[] =
    "Enables using arrow keys to rearrange displays on Settings > Device > "
    "Displays page.";

const char kLacrosAvailabilityIgnoreName[] =
    "Ignore lacros-availability policy";
const char kLacrosAvailabilityIgnoreDescription[] =
    "Makes the lacros-availability policy have no effect. Instead Lacros "
    "availability will be controlled by experiment and/or user flags.";

const char kLacrosPrimaryName[] = "Lacros as the primary browser";
const char kLacrosPrimaryDescription[] =
    "Use Lacros-chrome as the primary web browser on Chrome OS. "
    "This flag is ignored if Lacros support is disabled.";

const char kLacrosStabilityName[] = "Lacros stability";
const char kLacrosStabilityDescription[] = "Frequency of Lacros updates.";

const char kLacrosStabilityLeastStableDescription[] = "Daily updates";
const char kLacrosStabilityLessStableDescription[] = "Weekly updates";
const char kLacrosStabilityMoreStableDescription[] = "Monthly updates";

const char kLacrosSelectionName[] = "Lacros selection";
const char kLacrosSelectionDescription[] =
    "Choosing between rootfs or stateful Lacros.";

const char kLacrosSelectionRootfsDescription[] = "Rootfs";
const char kLacrosSelectionStatefulDescription[] = "Stateful";

const char kLacrosSupportName[] = "Lacros support";
const char kLacrosSupportDescription[] =
    "Support for the experimental lacros-chrome browser. Please note that the "
    "first restart can take some time to setup lacros-chrome. Please DO NOT "
    "attempt to turn off the device during the restart.";

const char kLauncherQueryHighlightingName[] = "Launcher query highlighting";
const char kLauncherQueryHighlightingDescription[] =
    "Enables highlighting occurrences of the search query in launcher search "
    "result titles.";

const char kLimitAltTabToActiveDeskName[] =
    "Limit Alt-Tab windows to active desk";
const char kLimitAltTabToActiveDeskDescription[] =
    "Limits the windows listed in Alt-Tab to the ones in the currently active "
    "virtual desk";
>>>>>>> chromium

const char kLimitShelfItemsToActiveDeskName[] =
    "Limit Shelf items to active desk";
const char kLimitShelfItemsToActiveDeskDescription[] =
    "Limits items on the shelf to the ones associated with windows on the "
    "active desk";

const char kListAllDisplayModesName[] = "List all display modes";
const char kListAllDisplayModesDescription[] =
    "Enables listing all external displays' modes in the display settings.";

const char kEnableHardwareMirrorModeName[] = "Enable Hardware Mirror Mode";
const char kEnableHardwareMirrorModeDescription[] =
    "Enables hardware support when multiple displays are set to mirror mode.";

const char kLockScreenMediaControlsName[] = "Lock screen media controls";
const char kLockScreenMediaControlsDescription[] =
    "Enable media controls on the lock screen.";

const char kLockScreenNotificationName[] = "Lock screen notification";
const char kLockScreenNotificationDescription[] =
    "Enable notifications on the lock screen.";

const char kMediaAppAnnotationName[] = "Media App Annotation";
const char kMediaAppAnnotationDescription[] =
    "Enables image annotation in chrome://media-app";

const char kMediaAppDisplayExifName[] = "Media App Display Exif";
const char kMediaAppDisplayExifDescription[] =
    "Enables displaying EXIF metadata in chrome://media-app";

<<<<<<< HEAD
const char kMahiPanelResizableName[] = "Mahi panel resizing";
const char kMahiPanelResizableDescription[] =
    "Enable Mahi panel resizing on ChromeOS.";

const char kMahiSummarizeSelectedName[] = "Mahi summarize selected text";
const char kMahiSummarizeSelectedDescription[] =
    "Enable Mahi to summarize the selected text";

const char kMediaAppPdfMahiName[] = "Mahi feature on Media App PDF";
const char kMediaAppPdfMahiDescription[] =
    "Enable Mahi feature on PDF files in Gallery app.";
=======
const char kMediaAppHandlesPdfName[] = "Media App Handles PDF";
const char kMediaAppHandlesPdfDescription[] =
    "Enables opening PDF files by default in chrome://media-app";

const char kMediaAppVideoName[] = "Media App Handles Video";
const char kMediaAppVideoDescription[] =
    "Use chrome://media-app as the default handler for video. Hides the "
    "deprecated VideoPlayer chrome app as a file handler.";

const char kMeteredShowToggleName[] = "Show Metered Toggle";
const char kMeteredShowToggleDescription[] =
    "Shows a Metered toggle in the Network settings UI for WiFI and Cellular. "
    "The toggle allows users to set whether a network should be considered "
    "metered for purposes of bandwith usage (e.g. for automatic updates).";

const char kMicrophoneMuteNotificationsName[] = "Microphone Mute Notifications";
const char kMicrophoneMuteNotificationsDescription[] =
    "Enables notifications that are shown when an app tries to use microphone "
    "while audio input is muted.";
>>>>>>> chromium

const char kMicrophoneMuteSwitchDeviceName[] = "Microphone Mute Switch Device";
const char kMicrophoneMuteSwitchDeviceDescription[] =
    "Support for detecting the state of hardware microphone mute toggle. Only "
    "effective on devices that have a microphone mute toggle. Enabling the "
    "flag does not affect the toggle functionality, it only affects how the "
    "System UI handles the mute toggle state.";

const char kMultilingualTypingName[] = "Multilingual typing on CrOS";
const char kMultilingualTypingDescription[] =
    "Enables support for multilingual assistive typing on Chrome OS.";

const char kNearbyKeepAliveFixName[] = "Nearby Keep Alive Fix";
const char kNearbyKeepAliveFixDescription[] =
    "Enables custom KeepAlive interval and timeout for Nearby Connections and "
    "makes Nearby Connections WebRTC KeepAlive less chatty to help with "
    "battery life.";

const char kNearbySharingName[] = "Nearby Sharing";
const char kNearbySharingDescription[] =
    "Enables Nearby Sharing for sharing content between devices.";

const char kNearbySharingBackgroundScanningName[] =
    "Nearby Sharing Background Scanning";
const char kNearbySharingBackgroundScanningDescription[] =
    "Enables background scanning for Nearby Share, allowing devices to "
    "persistently scan and present a notification when a nearby device is "
    "attempting to share.";

const char kNearbySharingDeviceContactsName[] =
    "Nearby Sharing Device Contacts";
const char kNearbySharingDeviceContactsDescription[] =
    "Enables use of device contacts in Nearby Share.";

<<<<<<< HEAD
const char kEnableNearbyBleV2GattServerName[] = "Nearby BLE v2 GATT Server";
const char kEnableNearbyBleV2GattServerDescription[] =
    "Enables GATT server functionality over BLE when using Nearby BLE "
    "v2.";

const char kEnableNearbyBluetoothClassicAdvertisingName[] =
    "Nearby Bluetooth Classic Advertising";
const char kEnableNearbyBluetoothClassicAdvertisingDescription[] =
    "Enables Nearby advertising over Bluetooth Classic.";

const char kEnableNearbyMdnsName[] = "Nearby mDNS Discovery";
const char kEnableNearbyMdnsDescription[] =
    "Enables Nearby discovery over mDNS.";

const char kEnableNearbyWebRtcName[] = "Nearby WebRTC";
const char kEnableNearbyWebRtcDescription[] =
    "Enables Nearby transfers over WebRTC.";

const char kEnableNearbyWifiDirectName[] = "Nearby WiFi Direct";
const char kEnableNearbyWifiDirectDescription[] =
    "Enables Nearby transfers over WiFi Direct.";

const char kEnableNearbyWifiLanName[] = "Nearby WiFi LAN";
const char kEnableNearbyWifiLanDescription[] =
    "Enables Nearby transfers over WiFi LAN.";

const char kNearbyPresenceName[] = "Nearby Presence";
const char kNearbyPresenceDescription[] =
    "Enables Nearby Presence for scanning and discovery of nearby devices.";

const char kNotificationsIgnoreRequireInteractionName[] =
    "Notifications always timeout";
const char kNotificationsIgnoreRequireInteractionDescription[] =
    "Always timeout notifications, even if they are set with "
    "requireInteraction.";

const char kOnDeviceAppControlsName[] = "On-device controls for apps";
const char kOnDeviceAppControlsDescription[] =
    "Enables the on-device controls UI for blocking apps.";

const char kOrcaKeyName[] = "Secret key for Orca feature";
const char kOrcaKeyDescription[] =
    "Secret key for Orca feature. Incorrect values will cause chrome crashes.";

const char kOsFeedbackDialogName[] =
    "OS Feedback dialog on OOBE and login screen";
const char kOsFeedbackDialogDescription[] =
    "Enable the OS Feedback dialog on OOBE and login screen.";

const char kPcieBillboardNotificationName[] = "PCIe billboard notification";
const char kPcieBillboardNotificationDescription[] =
    "Enable PCIe peripheral billboard notification.";
=======
const char kNearbySharingWebRtcName[] = "Nearby Sharing WebRTC";
const char kNearbySharingWebRtcDescription[] =
    "Enables use of WebRTC in Nearby Share.";
>>>>>>> chromium

const char kPerformantSplitViewResizing[] = "Performant Split View Resizing";
const char kPerformantSplitViewResizingDescription[] =
    "If enabled, windows may be moved instead of scaled when resizing split "
    "view in tablet mode.";

const char kPhoneHubCameraRollName[] = "Camera Roll in Phone Hub";
const char kPhoneHubCameraRollDescription[] =
    "Enables the Camera Roll feature in Phone Hub, which allows users to "
    "access recent photos and videos taken on a connected Android device.";

const char kPhoneHubRecentAppsName[] = "Recent Apps in Phone Hub";
const char kPhoneHubRecentAppsDescription[] =
    "Enables the Recent Apps feature in Phone Hub, which allows users to "
    "relaunch a recently streamed app.";

<<<<<<< HEAD
const char kPrintingPpdChannelName[] = "Printing PPD channel";
const char kPrintingPpdChannelDescription[] =
    "The channel from which PPD index "
    "is loaded when matching PPD files during printer setup.";

const char kPrintPreviewCrosAppName[] = "Enable ChromeOS print preview";
const char kPrintPreviewCrosAppDescription[] =
    "Enables ChromeOS print preview app.";

const char kProductivityLauncherImageSearchName[] =
    "Productivity Launcher experiment: Launcher Image Search";
const char kProductivityLauncherImageSearchDescription[] =
    "To evaluate the viability of image search as part of Productivity "
    "Launcher Search.";

const char kProjectorAppDebugName[] = "Enable Projector app debug";
const char kProjectorAppDebugDescription[] =
    "Adds more informative error messages to the Projector app for debugging";

const char kProjectorGm3Name[] = "Enable Screencast GM3";
const char kProjectorGm3Description[] =
    "Adds updated styles and dynamic colors to the Screencast app.";

const char kProjectorServerSideSpeechRecognitionName[] =
    "Enable server side speech recognition for Projector";
const char kProjectorServerSideSpeechRecognitionDescription[] =
    "Adds server side speech recognition capability to Projector.";

const char kProjectorServerSideUsmName[] =
    "Enable USM for Projector server side speech recognition";
const char kProjectorServerSideUsmDescription[] =
    "Allows Screencast to use the latest model for server side speech "
    "recognition.";
=======
const char kReduceDisplayNotificationsName[] = "Reduce display notifications";
const char kReduceDisplayNotificationsDescription[] =
    "If enabled, notifications for display rotation, display removed, display "
    "mirroring, and display extending will be suppressed.";

const char kReleaseNotesNotificationName[] = "Release Notes Notification";
const char kReleaseNotesNotificationDescription[] =
    "Enables the release notes notification and suggestion chip";
>>>>>>> chromium

const char kProjectorUseDVSPlaybackEndpointName[] =
    "Use DVS endpoint in the Screencast app";
const char kProjectorUseDVSPlaybackEndpointDescription[] =
    "Use the latest endpoint for retrieving playback urls in the Screencast "
    "app.";

const char kReleaseNotesNotificationAllChannelsName[] =
    "Release Notes Notification All Channels";
const char kReleaseNotesNotificationAllChannelsDescription[] =
    "Enables the release notes notification for all Chrome OS channels";

const char kArcGhostWindowName[] = "Enable ARC ghost window";
const char kArcGhostWindowDescription[] =
    "Enables the pre-load app window for "
    "ARC++ app during ARCVM booting stage on full restore process";

const char kArcResizeLockName[] = "Resize Lock for Android apps";
const char kArcResizeLockDescription[] =
    "Enable compatibility mode for Android apps that are not optimized for "
    "large screens, and impose restrictions on resizing the apps";

const char kScanAppMediaLinkName[] = "Show Media app link in Scan app";
const char kScanAppMediaLinkDescription[] =
    "Enables showing a link in the Scan app to open scanned images in the Media"
    " app.";

const char kScanAppMultiPageScanName[] =
    "Enable multi-page scanning in Scan app";
const char kScanAppMultiPageScanDescription[] =
    "Enables creating a single PDF file from multiple flatbed scans";

extern const char kScanAppSearchablePdfName[] =
    "Enable saving scans as a searchable PDF.";
extern const char kScanAppSearchablePdfDescription[] =
    "Allow selecting Searchable PDF file type in Scan app"
    " with incorporation of OCR service.";

<<<<<<< HEAD
const char kSealKeyName[] = "Secret key for Seal feature";
const char kSealKeyDescription[] = "Secret key for Seal feature.";

const char kShelfAutoHideSeparationName[] =
    "Enable separate shelf auto-hide preferences.";
const char kShelfAutoHideSeparationDescription[] =
    "Allows for the shelf's auto-hide preference to be specified separately "
    "for clamshell and tablet mode.";

const char kShimlessRMAAproUpdateRootfsName[] =
    "Enable APRO update from RootFS in Shimless RMA";
const char kShimlessRMAAproUpdateRootfsDescription[] =
    "Updates APRO from RootFS first in the Shimless RMA flow and fallbacks to "
    "USB drive when it fails.";

const char kShimlessRMAOsUpdateName[] = "Enable OS updates in shimless RMA";
const char kShimlessRMAOsUpdateDescription[] =
    "Turns on OS updating in Shimless RMA";
=======
const char kScanAppStickySettingsName[] = "Enable sticky settings in Scan app";
const char kScanAppStickySettingsDescription[] =
    "Enables sticky settings in Scan app for automatically saving scan"
    " settings in Chrome OS.";

const char kShimlessRMAFlowName[] = "Enable shimless RMA flow";
const char kShimlessRMAFlowDescription[] = "Enable shimless RMA flow";
>>>>>>> chromium

const char kSchedulerConfigurationName[] = "Scheduler Configuration";
const char kSchedulerConfigurationDescription[] =
    "Instructs the OS to use a specific scheduler configuration setting.";
const char kSchedulerConfigurationConservative[] =
    "Disables Hyper-Threading on relevant CPUs.";
const char kSchedulerConfigurationPerformance[] =
    "Enables Hyper-Threading on relevant CPUs.";

const char kSelectToSpeakNavigationControlName[] =
    "Select-to-speak navigation control";
const char kSelectToSpeakNavigationControlDescription[] =
    "Enables enhanced Select-to-speak navigation features.";

const char kSharesheetContentPreviewsName[] = "Sharesheet Content Previews";
const char kSharesheetContentPreviewsDescription[] =
    "Chrome OS content previews for sharesheet.";

const char kSharesheetName[] = "Sharesheet";
const char kSharesheetDescription[] = "Chrome OS sharesheet.";

const char kChromeOSSharingHubName[] = "Chrome OS Sharing Hub";
const char kChromeOSSharingHubDescription[] =
    "Enables the Sharing Hub (share sheet) on ChromeOS via the Omnibox.";

const char kShowBluetoothDebugLogToggleName[] =
    "Show Bluetooth debug log toggle";
const char kShowBluetoothDebugLogToggleDescription[] =
    "Enables a toggle which can enable debug (i.e., verbose) logs for "
    "Bluetooth";

const char kBluetoothSessionizedMetricsName[] =
    "Enable Bluetooth sessionized metrics";
const char kBluetoothSessionizedMetricsDescription[] =
    "Enables collecting and processing Bluetooth sessionized metrics.";

const char kShowDateInTrayName[] = "Enable Show Date In Tray";
const char kShowDateInTrayDescription[] =
    "Showing date in status area when the screen is sufficiently large.";

const char kShowTapsName[] = "Show taps";
const char kShowTapsDescription[] =
    "Draws a circle at each touch point, which makes touch points more obvious "
    "when projecting or mirroring the display. Similar to the Android OS "
    "developer option.";

const char kShowTouchHudName[] = "Show HUD for touch points";
const char kShowTouchHudDescription[] =
    "Shows a trail of colored dots for the last few touch points. Pressing "
    "Ctrl-Alt-I shows a heads-up display view in the top-left corner. Helps "
    "debug hardware issues that generate spurious touch events.";

<<<<<<< HEAD
const char kContinuousOverviewScrollAnimationName[] =
    "Makes the gesture for Overview continuous";
const char kContinuousOverviewScrollAnimationDescription[] =
    "When a user does the Overview gesture (3 finger swipe), smoothly animates "
    "the transition into Overview as the gesture is done. Allows for the user "
    "to scrub (move forward and backward) through Overview.";
=======
const char kSmartLockUIRevampName[] = "Enable Smart Lock UI Revamp";
const char kSmartLockUIRevampDescription[] =
    "Replaces the existing Smart Lock UI on the lock screen with a new design "
    "and adds Smart Lock to the 'Lock screen and sign-in' section of settings.";
>>>>>>> chromium

const char kSpectreVariant2MitigationName[] = "Spectre variant 2 mitigation";
const char kSpectreVariant2MitigationDescription[] =
    "Controls whether Spectre variant 2 mitigation is enabled when "
    "bootstrapping the Seccomp BPF sandbox. Can be overridden by "
    "#force-spectre-variant2-mitigation.";

<<<<<<< HEAD
const char kSystemJapanesePhysicalTypingName[] =
    "Use system IME for Japanese typing";
const char kSystemJapanesePhysicalTypingDescription[] =
=======
const char kSplitSettingsSyncName[] = "Split OS and browser sync";
const char kSplitSettingsSyncDescription[] =
    "Allows OS sync to be configured separately from browser sync. Changes the "
    "OS settings UI to provide controls for OS data types. Requires "
    "#split-settings to be enabled.";

const char kSystemLatinPhysicalTypingName[] =
    "Use system IME for latin-script typing";
const char kSystemLatinPhysicalTypingDescription[] =
>>>>>>> chromium
    "Use the system input engine instead of the Chrome extension for physical "
    "typing in languages based on latin script.";

const char kPluginVmFullscreenName[] = "Plugin VM Fullscreen";
const char kPluginVmFullscreenDescription[] =
    "Hides shelf in immersive mode and allows esc hold to exit.";

const char kTetherName[] = "Instant Tethering";
const char kTetherDescription[] =
    "Enables Instant Tethering. Instant Tethering allows your nearby Google "
    "phone to share its Internet connection with this device.";

const char kTouchscreenCalibrationName[] =
    "Enable/disable touchscreen calibration option in material design settings";
const char kTouchscreenCalibrationDescription[] =
    "If enabled, the user can calibrate the touch screen displays in "
    "chrome://settings/display.";

<<<<<<< HEAD
const char kTouchscreenMappingName[] =
    "Enable/disable touchscreen mapping option in material design settings";
const char kTouchscreenMappingDescription[] =
    "If enabled, the user can map the touch screen display to the correct "
    "input device in chrome://settings/display.";

const char kTrafficCountersEnabledName[] = "Traffic counters enabled";
const char kTrafficCountersEnabledDescription[] =
    "If enabled, data usage will be visible in the Cellular Settings UI and "
    "traffic counters will be automatically reset if that setting is enabled.";

const char kTrafficCountersForWiFiTestingName[] =
    "Traffic counters enabled for WiFi networks";
const char kTrafficCountersForWiFiTestingDescription[] =
    "If enabled, data usage will be visible in the Settings UI for WiFi "
    "networks";

const char kUploadOfficeToCloudName[] = "Enable Office files upload workflow.";
const char kUploadOfficeToCloudDescription[] =
    "Some file handlers for Microsoft Office files are only available on the "
    "the cloud. Enables the cloud upload workflow for Office file handling.";

const char kUseAnnotatedAccountIdName[] =
    "Use AccountId based mapping between User and BrowserContext";
const char kUseAnnotatedAccountIdDescription[] =
    "Uses AccountId annotated for BrowserContext to look up between ChromeOS "
    "User and BrowserContext, a.k.a. Profile.";

=======
>>>>>>> chromium
const char kUseFakeDeviceForMediaStreamName[] = "Use fake video capture device";
const char kUseFakeDeviceForMediaStreamDescription[] =
    "Forces Chrome to use a fake video capture device (a rolling pacman with a "
    "timestamp) instead of the system audio/video devices, for debugging "
    "purposes.";

<<<<<<< HEAD
const char kUseLegacyDHCPCDName[] = "Use legacy dhcpcd7 for IPv4";
const char kUseLegacyDHCPCDDescription[] =
    "Use legacy dhcpcd7 for IPv4 provisioning, otherwise the latest dhcpcd "
    "will be used. Note that IPv6 (DHCPv6-PD) will always use the latest "
    "dhcpcd.";

const char kUseManagedPrintJobOptionsInPrintPreviewName[] =
    "Use managed print job options in print preview";
const char kUseManagedPrintJobOptionsInPrintPreviewDescription[] =
    "Use managed print job options set via "
    "DevicePrinters/PrinterBulkConfiguration policy in print preview.";

=======
>>>>>>> chromium
const char kUiDevToolsName[] = "Enable native UI inspection";
const char kUiDevToolsDescription[] =
    "Enables inspection of native UI elements. For local inspection use "
    "chrome://inspect#other";

const char kUiSlowAnimationsName[] = "Slow UI animations";
const char kUiSlowAnimationsDescription[] = "Makes all UI animations slow.";

const char kVaapiJpegImageDecodeAccelerationName[] =
    "VA-API JPEG decode acceleration for images";
const char kVaapiJpegImageDecodeAccelerationDescription[] =
    "Enable or disable decode acceleration of JPEG images (as opposed to camera"
    " captures) using the VA-API.";

const char kVaapiWebPImageDecodeAccelerationName[] =
    "VA-API WebP decode acceleration for images";
const char kVaapiWebPImageDecodeAccelerationDescription[] =
    "Enable or disable decode acceleration of WebP images using the VA-API.";

const char kVirtualKeyboardName[] = "Virtual Keyboard";
const char kVirtualKeyboardDescription[] =
    "Always show virtual keyboard regardless of having a physical keyboard "
    "present";

const char kVirtualKeyboardBorderedKeyName[] = "Virtual Keyboard Bordered Key";
const char kVirtualKeyboardBorderedKeyDescription[] =
    "Show virtual keyboard with bordered key";

const char kVirtualKeyboardDisabledName[] = "Disable Virtual Keyboard";
const char kVirtualKeyboardDisabledDescription[] =
    "Always disable virtual keyboard regardless of device mode. Workaround for "
    "virtual keyboard showing with some external keyboards.";

const char kVirtualKeyboardMultipasteName[] = "Virtual Keyboard MultiPaste";
const char kVirtualKeyboardMultipasteDescription[] =
    "Show virtual keyboard with multipaste UI";

const char kVmStatusPageName[] = "VM status page";
const char kVmStatusPageDescription[] = "Enable VM status page";

const char kWakeOnWifiAllowedName[] = "Allow enabling wake on WiFi features";
const char kWakeOnWifiAllowedDescription[] =
    "Allows wake on WiFi features in shill to be enabled.";

const char kWebAppsCrosapiName[] = "Web Apps Crosapi";
const char kWebAppsCrosapiDescription[] =
    "Support web apps publishing from Lacros browser.";

const char kWebuiDarkModeName[] = "WebUI dark mode";
const char kWebuiDarkModeDescription[] =
    "Allows dark mode usage in WebUI. Note that this does not necessary enable "
    "dark mode, which is enabled via the #enable-force-dark flag.";

const char kWifiSyncAllowDeletesName[] =
    "Sync removal of Wi-Fi network configurations";
const char kWifiSyncAllowDeletesDescription[] =
    "Enables the option to sync deletions of Wi-Fi networks to other Chrome OS "
    "devices when Wi-Fi Sync is enabled.";

<<<<<<< HEAD
const char kWelcomeTourForceUserEligibilityName[] =
    "Force Welcome Tour user eligibility";
const char kWelcomeTourForceUserEligibilityDescription[] =
    "Forces user eligibility for the Welcome Tour that walks new users through "
    "ChromeOS System UI. Enabling this flag has no effect unless the Welcome "
    "Tour is also enabled.";

const char kWifiConnectMacAddressRandomizationName[] =
    "MAC address randomization";
const char kWifiConnectMacAddressRandomizationDescription[] =
    "Randomize MAC address when connecting to unmanaged (non-enterprise) "
    "WiFi networks.";

const char kWifiConcurrencyName[] = "WiFi Concurrency";
const char kWifiConcurrencyDescription[] =
    "When enabled, it uses new WiFi concurrency Shill APIs to start station "
    "WiFi and tethering.";

const char kWifiDirectName[] = "Wifi Direct";
const char kWifiDirectDescription[] =
    "Enables the WiFi direct functionalities in ChromeOS";

const char kWindowSplittingName[] = "CrOS Labs - Window splitting";
const char kWindowSplittingDescription[] =
    "Enables splitting windows by dragging one over another.";

const char kLauncherKeyShortcutInBestMatchName[] =
    "Enable keyshortcut results in best match";
const char kLauncherKeyShortcutInBestMatchDescription[] =
    "When enabled, it allows key shortcut results to appear in best match and "
    "answer card in launcher.";

const char kLauncherKeywordExtractionScoring[] =
    "Query keyword extraction and scoring in launcher";
const char kLauncherKeywordExtractionScoringDescription[] =
    "Enables extraction of keywords from query then calculate score from "
    "extracted keyword in the launcher.";

const char kLauncherLocalImageSearchName[] =
    "Enable launcher local image search";
const char kLauncherLocalImageSearchDescription[] =
    "Enables on-device local image search in the launcher.";

const char kLauncherLocalImageSearchConfidenceName[] =
    "Launcher Local Image Search Confidence";
const char kLauncherLocalImageSearchConfidenceDescription[] =
    "Allows configurations of the experiment parameters for local image search "
    "confidence threshold in the launcher.";

const char kLauncherLocalImageSearchRelevanceName[] =
    "Launcher Local Image Search Relevance";
const char kLauncherLocalImageSearchRelevanceDescription[] =
    "Allows configurations of the experiment parameters for local image search "
    "Relevance threshold in the launcher.";

const char kLauncherLocalImageSearchOcrName[] =
    "Enable OCR for local image search";
const char kLauncherLocalImageSearchOcrDescription[] =
    "Enables on-device Optical Character Recognition for local image search in "
    "the launcher.";

const char kLauncherLocalImageSearchIcaName[] =
    "Enable ICA for local image search";
const char kLauncherLocalImageSearchIcaDescription[] =
    "Enables on-device Image Content-based Annotation for local image search "
    "in the launcher.";

const char kLauncherSearchControlName[] = "Enable launcher search control";
const char kLauncherSearchControlDescription[] =
    "Enable search control in launcher so that users can customize the result "
    "results provided.";

const char kLauncherNudgeSessionResetName[] =
    "Enable resetting launcher nudge data";
const char kLauncherNudgeSessionResetDescription[] =
    "When enabled, this will reset the launcher nudge shown data on every new "
    "user session, allowing the nudge to be shown again.";

const char kLauncherSystemInfoAnswerCardsName[] =
    "System Info Answer Cards in launcher";
const char kLauncherSystemInfoAnswerCardsDescription[] =
    "Enables System info answer cards in the launcher to provide system "
    "performance metrics";

const char kMacAddressRandomizationName[] = "MAC address randomization";
const char kMacAddressRandomizationDescription[] =
    "Feature to allow MAC address randomization to be enabled for WiFi "
    "networks.";

const char kSysUiShouldHoldbackDriveIntegrationName[] =
    "Holdback for Drive Integration on chromeOS";
const char kSysUiShouldHoldbackDriveIntegrationDescription[] =
    "Enables holdback for Drive Integration.";

const char kSysUiShouldHoldbackFocusModeName[] =
    "Holdback for Focus Mode on chromeOS";
const char kSysUiShouldHoldbackFocusModeDescription[] =
    "Enables holdback for Focus Mode.";

const char kSysUiShouldHoldbackForestName[] = "Holdback for Forest on chromeOS";
const char kSysUiShouldHoldbackForestDescription[] =
    "Enables holdback for Forest.";

const char kSysUiShouldHoldbackTaskManagementName[] =
    "Holdback for Task Management on chromeOS";
const char kSysUiShouldHoldbackTaskManagementDescription[] =
    "Enables holdback for Task Management.";

const char kTetheringExperimentalFunctionalityName[] =
    "Tethering Allow Experimental Functionality";
const char kTetheringExperimentalFunctionalityDescription[] =
    "Feature to enable Chromebook hotspot functionality for experimental "
    "carriers, modem and modem FW.";

// Prefer keeping this section sorted to adding new definitions down here.

#endif  // BUILDFLAG(IS_CHROMEOS)
=======
const char kWifiSyncAndroidName[] =
    "Sync Wi-Fi network configurations with Android";
const char kWifiSyncAndroidDescription[] =
    "Enables the option to sync Wi-Fi network configurations between Chrome OS "
    "devices and a connected Android phone";

// Prefer keeping this section sorted to adding new definitions down here.

#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS)
const char kAllowDefaultWebAppMigrationForChromeOsManagedUsersName[] =
    "Allow default web app migration for Chrome OS managed users";
const char kAllowDefaultWebAppMigrationForChromeOsManagedUsersDescription[] =
    "The web app migration flags "
    "(chrome://flags/#enable-migrate-default-chrome-app-to-web-apps-gsuite and "
    "chrome://flags/#enable-migrate-default-chrome-app-to-web-apps-non-gsuite) "
    "are ignored for managed Chrome OS users unless this feature is enabled.";

const char kDefaultChatWebAppName[] = "Default Chat web app";
const char kDefaultChatWebAppDescription[] =
    "Enables the Chat web app to be installed by default.";

const char kDefaultMeetWebAppName[] = "Default Meet web app";
const char kDefaultMeetWebAppDescription[] =
    "Enables the Meet web app to be installed by default.";
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS)
>>>>>>> chromium

#if defined(OS_CHROMEOS)
const char kDeprecateLowUsageCodecsName[] = "Deprecates low usage media codecs";
const char kDeprecateLowUsageCodecsDescription[] =
    "Deprecates low usage codecs. Disable this feature to allow playback of "
    "AMR and GSM.";

const char kVaapiAV1DecoderName[] = "VA-API decode acceleration for AV1";
const char kVaapiAV1DecoderDescription[] =
    "Enable or disable decode acceleration of AV1 videos using the VA-API.";
#endif  // defined(OS_CHROMEOS)

#if defined(ARCH_CPU_X86_FAMILY) && BUILDFLAG(IS_CHROMEOS_ASH)
const char kVaapiVP9kSVCEncoderName[] =
    "VA-API encode acceleration for k-SVC VP9";
const char kVaapiVP9kSVCEncoderDescription[] =
    "Enable or disable k-SVC VP9 encode acceleration using VA-API.";
#endif  // defined(ARCH_CPU_X86_FAMILY) && BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_CHROMEOS) && BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)
const char kChromeOSDirectVideoDecoderName[] = "ChromeOS Direct Video Decoder";
const char kChromeOSDirectVideoDecoderDescription[] =
    "Enables the hardware-accelerated ChromeOS direct media::VideoDecoder "
    "implementation. Note that this might be entirely disallowed by the "
    "--platform-disallows-chromeos-direct-video-decoder command line switch "
    "which is added for platforms where said direct VideoDecoder does not work "
    "or is not well tested (see the disable_cros_video_decoder USE flag in "
    "Chrome OS)";
#endif  // defined(OS_CHROMEOS) && BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)

<<<<<<< HEAD
const char kRunOnOsLoginName[] = "Run on OS login";
const char kRunOnOsLoginDescription[] =
    "When enabled, allows PWAs to be automatically run on OS login.";

const char kPreventCloseName[] = "Prevent close";
const char kPreventCloseDescription[] =
    "When enabled, allow-listed PWAs cannot be closed manually.";

const char kFileSystemAccessGetCloudIdentifiersName[] =
    "Cloud identifiers for FileSystemAccess API";
const char kFileSystemAccessGetCloudIdentifiersDescription[] =
    "Enables the FileSystemHandle.getCloudIdentifiers() method. See"
    "https://github.com/WICG/file-system-access/blob/main/proposals/"
    "CloudIdentifier.md"
    "for more information.";

const char kCrOSDspBasedAecAllowedName[] =
    "Allow CRAS to use a DSP-based AEC if available";
const char kCrOSDspBasedAecAllowedDescription[] =
    "Allows the system variant of the AEC in CRAS to be run on DSP ";

const char kCrOSDspBasedNsAllowedName[] =
    "Allow CRAS to use a DSP-based NS if available";
const char kCrOSDspBasedNsAllowedDescription[] =
    "Allows the system variant of the NS in CRAS to be run on DSP ";

const char kCrOSDspBasedAgcAllowedName[] =
    "Allow CRAS to use a DSP-based AGC if available";
const char kCrOSDspBasedAgcAllowedDescription[] =
    "Allows the system variant of the AGC in CRAS to be run on DSP ";

const char kCrOSEnforceSystemAecName[] = "Enforce using the system AEC in CrAS";
const char kCrOSEnforceSystemAecDescription[] =
    "Enforces using the system variant in CrAS of the AEC";

const char kCrOSEnforceSystemAecAgcName[] =
    "Enforce using the system AEC and AGC in CrAS";
const char kCrOSEnforceSystemAecAgcDescription[] =
    "Enforces using the system variants in CrAS of the AEC and AGC.";

const char kCrOSEnforceSystemAecNsName[] =
    "Enforce using the system AEC and NS in CrAS";
const char kCrOSEnforceSystemAecNsDescription[] =
    "Enforces using the system variants in CrAS of the AEC and NS.";

const char kCrOSEnforceSystemAecNsAgcName[] =
    "Enforce using the system AEC, NS and AGC in CrAS";
const char kCrOSEnforceSystemAecNsAgcDescription[] =
    "Enforces using the system variants in CrAS of the AEC, NS and AGC.";

const char kIgnoreUiGainsName[] = "Ignore UI Gains in system mic gain setting";
const char kIgnoreUiGainsDescription[] =
    "Ignore UI Gains in system mic gain setting";

const char kShowForceRespectUiGainsToggleName[] =
    "Enable a setting toggle to force respect UI gains";
const char kShowForceRespectUiGainsToggleDescription[] =
    "Enable a setting toggle to force respect UI gains.";

const char kCrOSSystemVoiceIsolationOptionName[] =
    "Enable the options of setting system voice isolation per stream";
const char kCrOSSystemVoiceIsolationOptionDescription[] =
    "Enable the options of setting system voice isolation per stream.";

const char kShowSpatialAudioToggleName[] =
    "Enable a setting toggle for spatial audio";
const char kShowSpatialAudioToggleDescription[] =
    "Enable a setting toggle for spatial audio.";

const char kSingleCaCertVerificationPhase0Name[] =
    "Use single CA cert for EAP networks if provided phase 0";
const char kSingleCaCertVerificationPhase0Description[] =
    "Only collect data for server certificate verification failure.";

const char kSingleCaCertVerificationPhase1Name[] =
    "Use single CA cert for EAP networks if provided phase 1";
const char kSingleCaCertVerificationPhase1Description[] =
    "Use a single CA cert for server's cert verification with fallback to"
    "the old config.";

const char kSingleCaCertVerificationPhase2Name[] =
    "Use single CA cert for EAP networks if provided phase 2";
const char kSingleCaCertVerificationPhase2Description[] =
    "Use a single CA cert for server's cert verification, no fallback.";

const char kCrosMallName[] = "ChromeOS App Mall";
const char kCrosMallDescription[] =
    "Enables an app to discover and install other apps.";

const char kCrosMallManagedName[] = "ChromeOS App Mall for managed users";
const char kCrosMallManagedDescription[] =
    "Enables the Mall app for managed users. Only has an effect when the "
    "#cros-mall flag is enabled.";

const char kCrosMallUrlName[] = "ChromeOS App Mall URL";
const char kCrosMallUrlDescription[] =
    "Customize the URL used for the ChromeOS App Mall.";

const char kCrosPrivacyHubName[] = "Enable ChromeOS Privacy Hub";
const char kCrosPrivacyHubDescription[] = "Enables ChromeOS Privacy Hub.";

const char kCrosPrivacyHubAppPermissionsV2Name[] =
    "Add privacy controls to app specific subpages";
const char kCrosPrivacyHubAppPermissionsV2Description[] =
    "When enabled, the user will be able to manage system access of sensors "
    "from the app specific subpages under the OS Apps section.";

const char kDisableIdleSocketsCloseOnMemoryPressureName[] =
    "Disable closing idle sockets on memory pressure";
const char kDisableIdleSocketsCloseOnMemoryPressureDescription[] =
    "If enabled, idle sockets will not be closed when chrome detects memory "
    "pressure. This applies to web pages only and not to internal requests.";

const char kDisableOfficeEditingComponentAppName[] =
    "Disable Office Editing for Docs, Sheets & Slides";
const char kDisableOfficeEditingComponentAppDescription[] =
    "Disables Office Editing for Docs, Sheets & Slides component app so "
    "handlers won't be registered, making it possible to install another "
    "version for testing.";

const char kLockedModeName[] = "Enable the Locked Mode API.";
const char kLockedModeDescription[] =
    "Enabled the Locked Mode Web API which allows admin-allowlisted sites "
    "to enter a locked down fullscreen mode.";

const char kOneGroupPerRendererName[] =
    "Use one cgroup for each foreground renderer";
const char kOneGroupPerRendererDescription[] =
    "Places each Chrome foreground renderer into its own cgroup";

const char kPlatformKeysChangesWave1Name[] = "Platform Keys Changes Wave 1";
const char kPlatformKeysChangesWave1Description[] =
    "Enables the first wave of new features for the "
    "chrome.enterprise.platformKeys API. That includes supporting the "
    "\"RSA-OAEP\" key type with the \"unwrapKey\" key usage and adding the "
    "setKeyTag() API method to mark keys for future lookup.";

const char kPrintPreviewCrosPrimaryName[] =
    "Enables the ChromeOS print preview to be the primary print preview.";
const char kPrintPreviewCrosPrimaryDescription[] =
    "Allows the ChromeOS print preview to be opened instead of the browser "
    " print preview.";

const char kDisableQuickAnswersV2TranslationName[] =
    "Disable Quick Answers Translation";
const char kDisableQuickAnswersV2TranslationDescription[] =
    "Disable translation services of the Quick Answers.";

const char kQuickAnswersRichCardName[] = "Enable Quick Answers Rich Card";
const char kQuickAnswersRichCardDescription[] =
    "Enable rich card views of the Quick Answers feature.";

const char kQuickAnswersMaterialNextUIName[] =
    "Enable Quick Answers Material Next UI";
const char kQuickAnswersMaterialNextUIDescription[] =
    "Enable Material Next UI for the Quick Answers feature. This is effective "
    "only if Magic Boost flag is off. Note that this will be changed as this "
    "is effective only if a device is eligible to Magic Boost when the Magic "
    "Boost flag gets flipped.";

const char kQuickOfficeForceFileDownloadName[] =
    "Basic Office Editor File Download";
const char kQuickOfficeForceFileDownloadDescription[] =
    "Forces the Basic Office Editor to download files instead of intercepting "
    "navigations to document types it can handle.";

const char kWebPrintingApiName[] = "Web Printing API";
const char kWebPrintingApiDescription[] =
    "Enable access to the Web Printing API. See "
    "https://github.com/WICG/web-printing for details.";
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_CHROMEOS) && BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)
const char kChromeOSHWVBREncodingName[] =
    "ChromeOS Hardware Variable Bitrate Encoding";
const char kChromeOSHWVBREncodingDescription[] =
    "Enables the hardware-accelerated variable bitrate (VBR) encoding on "
    "ChromeOS. If the hardware encoder supports VBR for a specified codec, a "
    "video is recorded in VBR encoding in MediaRecoder API automatically and "
    "WebCodecs API if configured so.";
#if defined(ARCH_CPU_ARM_FAMILY)
const char kUseGLForScalingName[] = "Use GL image processor for scaling";
const char kUseGLForScalingDescription[] =
    "Use the GL image processor for scaling over libYUV implementations.";
const char kPreferGLImageProcessorName[] = "Prefer GL image processor";
const char kPreferGLImageProcessorDescription[] =
    "Prefers the GL image processor for format conversion of video frames over"
    " both the libYUV and hardware implementations";
const char kPreferSoftwareMT21Name[] = "Prefer software MT21 conversion";
const char kPreferSoftwareMT21Description[] =
    "Prefer using the software MT21 conversion instead of the MDP hardware "
    "conversion on MT8173 devices.";
const char kEnableProtectedVulkanDetilingName[] =
    "Enable Protected Vulkan Detiling";
const char kEnableProtectedVulkanDetilingDescription[] =
    "Use a Vulkan shader for protected Vulkan detiling.";
const char kEnableArmHwdrm10bitOverlaysName[] =
    "Enable ARM HW DRM 10-bit Overlays";
const char kEnableArmHwdrm10bitOverlaysDescription[] =
    "Enable 10-bit overlays for ARM HW DRM content. If disabled, 10-bit "
    "HW DRM content will be subsampled to 8-bit before scanout. This flag "
    "has no effect on 8-bit content.";
#if BUILDFLAG(USE_CHROMEOS_PROTECTED_MEDIA)
const char kEnableArmHwdrmName[] = "Enable ARM HW DRM";
const char kEnableArmHwdrmDescription[] = "Enable HW backed Widevine L1 DRM";
#endif  // BUILDFLAG(USE_CHROMEOS_PROTECTED_MEDIA)
#endif  // defined(ARCH_CPU_ARM_FAMILY)
#endif  // BUILDFLAG(IS_CHROMEOS) && BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)

// Linux -----------------------------------------------------------------------

#if BUILDFLAG(IS_LINUX)
const char kOzonePlatformHintChoiceDefault[] = "Default";
const char kOzonePlatformHintChoiceAuto[] = "Auto";
const char kOzonePlatformHintChoiceX11[] = "X11";
const char kOzonePlatformHintChoiceWayland[] = "Wayland";

const char kOzonePlatformHintName[] = "Preferred Ozone platform";
const char kOzonePlatformHintDescription[] =
    "Selects the preferred platform backend used on Linux. \"Auto\" selects "
    "Wayland if possible, X11 otherwise. ";

const char kPulseaudioLoopbackForCastName[] =
    "Linux System Audio Loopback for Cast (pulseaudio)";
const char kPulseaudioLoopbackForCastDescription[] =
    "Enable system audio mirroring when casting a screen on Linux with "
    "pulseaudio.";

const char kPulseaudioLoopbackForScreenShareName[] =
    "Linux System Audio Loopback for Screen Sharing (pulseaudio)";
const char kPulseaudioLoopbackForScreenShareDescription[] =
    "Enable system audio sharing when screen sharing on Linux with pulseaudio.";

const char kSimplifiedTabDragUIName[] = "Simplified tab dragging UI mode";
const char kSimplifiedTabDragUIDescription[] =
    "Enable simplified tab dragging UI mode as a fallback if the graphical "
    "environment does not support the classic UI.";

const char kWaylandLinuxDrmSyncobjName[] =
    "Wayland linux-drm-syncobj explicit sync";
const char kWaylandLinuxDrmSyncobjDescription[] =
    "Enable Wayland's explicit sync support using linux-drm-syncobj."
    "Requires minimum kernel version v6.11.";

const char kWaylandPerWindowScalingName[] = "Wayland per-window scaling";
const char kWaylandPerWindowScalingDescription[] =
    "Enable Wayland's per-window scaling experimental support.";

const char kWaylandTextInputV3Name[] = "Wayland text-input-v3";
const char kWaylandTextInputV3Description[] =
    "Enable Wayland's text-input-v3 experimental support.";

const char kWaylandUiScalingName[] = "Wayland UI scaling";
const char kWaylandUiScalingDescription[] =
    "Enable experimental support for text scaling in the Wayland backend "
    "backed by full UI scaling. Requires #wayland-per-window-scaling to be "
    "enabled too.";
#endif  // BUILDFLAG(IS_LINUX)

// Random platform combinations -----------------------------------------------

#if BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC) || defined(OS_WIN)
>>>>>>> chromium
const char kZeroCopyVideoCaptureName[] = "Enable Zero-Copy Video Capture";
const char kZeroCopyVideoCaptureDescription[] =
    "Camera produces a gpu friendly buffer on capture and, if there is, "
    "hardware accelerated video encoder consumes the buffer";
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC) || defined(OS_WIN)
>>>>>>> chromium

// All views-based platforms --------------------------------------------------

#if defined(TOOLKIT_VIEWS)

<<<<<<< HEAD
const char kHideTabletToolbarDownloadButtonName[] =
    "Hide Tablet Toolbar Download Button";
const char kHideTabletToolbarDownloadButtonDescription[] =
    "Hides the Omnibox download button and shows it as a menu item for "
    "tablets.";

const char kShowNewTabAnimationsName[] = "Show New Tab Animations";
const char kShowNewTabAnimationsDescription[] =
    "Shows new animations for creating tabs.";

const char kTabSwitcherColorBlendAnimateName[] =
    "Tab Switcher Color Blend Animation";
const char kTabSwitcherColorBlendAnimateDescription[] =
    "Animates the color transition between incognito and regular tab switcher "
    "panes in the Hub.";
#else
const char kTaskManagerDesktopRefreshName[] = "Task Manager Desktop Refresh";
const char kTaskManagerDesktopRefreshDescription[] =
    "Enables a refreshed design for the Task Manager on Desktop platforms.";
#endif  // BUILDFLAG(IS_ANDROID)
=======
const char kDesktopInProductHelpSnoozeName[] =
    "Allow snooze on supported in-product help promos";
const char kDesktopInProductHelpSnoozeDescription[] =
    "Snoozing an in-product help promo closes it and schedules it to be shown "
    "later. When enabled, this functionality is allowed on supported promos.";
>>>>>>> chromium

const char kDownloadShelfWebUI[] = "Download Shelf WebUI";
const char kDownloadShelfWebUIDescription[] =
    "Replaces the Views download shelf with a WebUI download shelf.";

const char kEnableMDRoundedCornersOnDialogsName[] =
    "MD corners on secondary UI";
const char kEnableMDRoundedCornersOnDialogsDescription[] =
    "Increases corner radius on secondary UI.";

const char kInstallableInkDropName[] = "Use InstallableInkDrop where supported";
const char kInstallableInkDropDescription[] =
    "InstallableInkDrop is part of an InkDrop refactoring effort. This enables "
    "the pilot implementation where available.";

#endif  // defined(TOOLKIT_VIEWS)

// Random platform combinations -----------------------------------------------

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) || \
    defined(OS_CHROMEOS)

const char kEnableOopPrintDriversName[] =
    "Enables Out-of-Process Printer Drivers";
const char kEnableOopPrintDriversDescription[] =
    "Enables printing interactions with the operating system to be performed "
    "out-of-process.";

const char kWebUIBrandingUpdateName[] = "WebUI Branding Update";
const char kWebUIBrandingUpdateDescription[] =
    "Changes various UI components in WebUI pages to have a more modern look.";

const char kWebuiFeedbackName[] = "WebUI Feedback";
const char kWebuiFeedbackDescription[] =
    "If enabled, Chrome will show the Feedback WebUI, as opposed to Chrome "
    "App Feedback UI, when clicking on \"Report an issue...\"";

const char kSettingsLandingPageRedesignName[] =
    "Settings Landing Page Redesign";
const char kSettingsLandingPageRedesignDescription[] =
    "Changes the layout of the chrome://settings page to only show one section "
    "at a time.";

#endif  // defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) ||
        // defined(OS_CHROMEOS)

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)

const char kCommanderName[] = "Commander";
const char kCommanderDescription[] =
    "Enable a text interface to browser features. Invoke with Ctrl-Space.";

const char kDesktopRestructuredLanguageSettingsName[] =
    "Restructured Language Settings (Desktop)";
const char kDesktopRestructuredLanguageSettingsDescription[] =
    "Enable the new restructured language settings page";

const char kDesktopDetailedLanguageSettingsName[] =
    "Detailed Language Settings (Desktop)";
const char kDesktopDetailedLanguageSettingsDescription[] =
    "Enable the new detailed language settings page";

#endif  // defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)

#if defined(OS_CHROMEOS) || defined(OS_LINUX)
#if BUILDFLAG(USE_TCMALLOC)
const char kDynamicTcmallocName[] = "Dynamic Tcmalloc Tuning";
const char kDynamicTcmallocDescription[] =
    "Allows tcmalloc to dynamically adjust tunables based on system resource "
    "utilization.";
#endif  // BUILDFLAG(USE_TCMALLOC)
#endif  // #if defined(OS_CHROMEOS) || defined(OS_LINUX)

#if !defined(OS_ANDROID) && !BUILDFLAG(IS_CHROMEOS_ASH)
const char kUserDataSnapshotName[] = "Enable user data snapshots";
const char kUserDataSnapshotDescription[] =
    "Enables taking snapshots of the user data directory after a Chrome "
    "update and restoring them after a version rollback.";
#endif  // !defined(OS_ANDROID) && !BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_WIN) || BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC)
const char kWebShareName[] = "Web Share";
const char kWebShareDescription[] =
    "Enables the Web Share (navigator.share) APIs on experimentally supported "
    "platforms.";
#endif  // defined(OS_WIN) || BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC)

#if defined(OS_LINUX) && defined(USE_OZONE)
const char kUseOzonePlatformName[] = "Use ozone.";
const char kUseOzonePlatformDescription[] =
    "Use the Ozone/X11 platform implementation on X11.";
#endif  // defined(OS_LINUX) && defined(USE_OZONE)

// Feature flags --------------------------------------------------------------

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_PRINTING)
const char kCupsIppPrintingBackendName[] = "CUPS IPP Printing Backend";
const char kCupsIppPrintingBackendDescription[] =
    "Use the CUPS IPP printing backend instead of the original CUPS backend "
    "that calls the PPD API.";
#endif  // BUILDFLAG(ENABLE_PRINTING)
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_CHROMEOS)
const char kScreenlockReauthCardName[] =
    "Show screenlock reauth before filling password setting in password "
    "manager";
const char kScreenlockReauthCardDescription[] =
    "Enables setting for requiring reauth before filling passwords "
    "in password manager settings. The default for setting is turned off.";
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(CHROME_WIDE_ECHO_CANCELLATION)
const char kChromeWideEchoCancellationName[] = "Chrome-wide echo cancellation";
const char kChromeWideEchoCancellationDescription[] =
    "Run WebRTC capture audio processing in the audio process instead of the "
    "renderer processes, thereby cancelling echoes from more audio sources.";
#endif  // BUILDFLAG(CHROME_WIDE_ECHO_CANCELLATION)

#if BUILDFLAG(DCHECK_IS_CONFIGURABLE)
=======
#if defined(DCHECK_IS_CONFIGURABLE)
>>>>>>> chromium
const char kDcheckIsFatalName[] = "DCHECKs are fatal";
const char kDcheckIsFatalDescription[] =
    "By default Chrome will evaluate in this build, but only log failures, "
    "rather than crashing. If enabled, DCHECKs will crash the calling process.";
#endif  // defined(DCHECK_IS_CONFIGURABLE)

#if BUILDFLAG(ENABLE_JXL_DECODER)
const char kEnableJXLName[] = "Enable JXL image format";
const char kEnableJXLDescription[] =
    "Adds image decoding support for the JPEG XL image format.";
#endif  // BUILDFLAG(ENABLE_JXL_DECODER)

#if BUILDFLAG(ENABLE_NACL)
const char kNaclName[] = "Native Client";
const char kNaclDescription[] =
    "Support Native Client for all web applications, even those that were not "
    "installed from the Chrome Web Store.";
#endif  // ENABLE_NACL

#if BUILDFLAG(ENABLE_PAINT_PREVIEW) && defined(OS_ANDROID)
const char kPaintPreviewDemoName[] = "Paint Preview Demo";
const char kPaintPreviewDemoDescription[] =
    "If enabled a menu item is added to the Android main menu to demo paint "
    "previews.";
<<<<<<< HEAD
#endif  // ENABLE_PAINT_PREVIEW && BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_PDF)
const char kAccessiblePDFFormName[] = "Accessible PDF Forms";
const char kAccessiblePDFFormDescription[] =
    "Enables accessibility support for PDF forms.";

const char kPdfCr23Name[] = "PDF Chrome Refresh 2023";
const char kPdfCr23Description[] =
    "Use new CR23 icons and colors for the PDF Viewer.";

#if BUILDFLAG(ENABLE_PDF_INK2)
const char kPdfInk2Name[] = "PDF Ink Signatures";
const char kPdfInk2Description[] =
    "Enables the ability to annotate PDFs using a new ink library.";
#endif  // BUILDFLAG(ENABLE_PDF_INK2)

const char kPdfOopifName[] = "OOPIF for PDF Viewer";
const char kPdfOopifDescription[] =
    "Use an OOPIF for the PDF Viewer, instead of a GuestView.";

const char kPdfPortfolioName[] = "PDF portfolio";
const char kPdfPortfolioDescription[] = "Enable PDF portfolio feature.";

const char kPdfUseSkiaRendererName[] = "Use Skia Renderer";
const char kPdfUseSkiaRendererDescription[] =
    "Use Skia as the PDF renderer. This flag will have no effect if the "
    "renderer choice is controlled by an enterprise policy.";
#endif  // BUILDFLAG(ENABLE_PDF)

#if BUILDFLAG(ENABLE_VR)
const char kWebXrHandInputName[] = "WebXR Hand Input";
const char kWebXrHandInputDescription[] =
    "Enables access to articulated hand tracking sensor input in WebXR.";
const char kWebXrWebGpuBindingName[] = "WebXR/WebGPU Binding";
const char kWebXrWebGpuBindingDescription[] =
    "Enables rendering with WebGPU for WebXR sessions.";
const char kWebXrInternalsName[] = "WebXR Internals Debugging Page";
const char kWebXrInternalsDescription[] =
    "Enables the webxr-internals developer page which can be used to help "
    "debug issues with the WebXR Device API.";
#endif  // #if defined(ENABLE_VR)
=======
const char kPaintPreviewStartupName[] = "Paint Preview Startup";
const char kPaintPreviewStartupDescription[] =
    "If enabled, paint previews for each tab are captured when a tab is hidden "
    "and are deleted when a tab is closed. If a paint preview was captured for "
    "the tab to be restored on startup, the paint preview will be shown "
    "instead.";
#endif  // ENABLE_PAINT_PREVIEW && defined(OS_ANDROID)
>>>>>>> chromium

#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)
const char kWebUITabStripName[] = "WebUI tab strip";
const char kWebUITabStripDescription[] =
    "When enabled makes use of a WebUI-based tab strip.";

const char kWebUITabStripNTBInTabStripName[] =
    "WebUI tab strip NTB in tab strip";
const char kWebUITabStripNTBInTabStripDescription[] =
    "Whether the new tab button is in the WebUI tab strip or in the toolbar.";
#endif  // BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)

#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP) && BUILDFLAG(IS_CHROMEOS_ASH)
const char kWebUITabStripTabDragIntegrationName[] =
    "ChromeOS drag-drop extensions for WebUI tab strip";
const char kWebUITabStripTabDragIntegrationDescription[] =
    "Enables special handling in ash for WebUI tab strip tab drags. Allows "
    "dragging tabs out to new windows.";
#endif  // BUILDFLAG(ENABLE_WEBUI_TAB_STRIP) && BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(TOOLKIT_VIEWS) || defined(OS_ANDROID)

const char kAutofillCreditCardUploadName[] =
    "Enable offering upload of Autofilled credit cards";
const char kAutofillCreditCardUploadDescription[] =
    "Enables a new option to upload credit cards to Google Payments for sync "
    "to all Chrome devices.";

#endif  // defined(TOOLKIT_VIEWS) || defined(OS_ANDROID)

#if !defined(OS_WIN) && !defined(OS_FUCHSIA)
const char kSendWebUIJavaScriptErrorReportsName[] =
    "Send WebUI JavaScript Error Reports";
const char kSendWebUIJavaScriptErrorReportsDescription[] =
    "If enabled, and if the user has consented to sending metrics to Google, "
    "then when the JavaScript has an error on a WebUI page, an error report "
    "will be sent to Google.";
#endif

#if defined(OS_WIN) || defined(OS_ANDROID)
const char kElasticOverscrollName[] = "Elastic Overscroll";
const char kElasticOverscrollDescription[] =
    "Enables Elastic Overscrolling on touchscreens and precision touchpads.";
#endif  // defined(OS_WIN) || defined(OS_ANDROID)

#if defined(OS_WIN) || (defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)) || \
    defined(OS_MAC)
const char kUIDebugToolsName[] = "Debugging tools for UI";
const char kUIDebugToolsDescription[] =
    "Enables additional keyboard shortcuts to help debugging.";
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
const char kAuraWindowSubtreeCaptureName[] = "ChromeOS Window Subtree Capture";
const char kAuraWindowSubtreeCaptureDescription[] =
    "Enables capture of ChromeOS Aura windows using subtree capture. When "
    "disabled, the legacy slow capturer will be used.";
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(WEBRTC_USE_PIPEWIRE)
const char kWebrtcPipeWireCapturerName[] = "WebRTC PipeWire support";
const char kWebrtcPipeWireCapturerDescription[] =
    "When enabled the WebRTC will use the PipeWire multimedia server for "
    "capturing the desktop content on the Wayland display server.";
#endif  // #if defined(WEBRTC_USE_PIPEWIRE)

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
const char kPromiseIconsName[] = "Promise Icons";
const char kPromiseIconsDescription[] =
    "Enables promise icons in the Launcher and Shelf (if the app is pinned) "
    "for app installations.";

const char kEnableAudioFocusEnforcementName[] = "Audio Focus Enforcement";
const char kEnableAudioFocusEnforcementDescription[] =
    "Enables enforcement of a single media session having audio focus at "
    "any one time. Requires #enable-media-session-service to be enabled too.";
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(ENABLE_COMPOSE)
const char kComposeId[] = "CCO";
const char kComposeName[] = "CCO Edits";
const char kComposeDescription[] = "Enables CCO editing feature";

const char kComposeNudgeAtCursorName[] = "Compose Nudge At Cursor";
const char kComposeNudgeAtCursorDescription[] =
    "Shows the Compose proactive nudge at the cursor location";

const char kComposeProactiveNudgeName[] = "Compose Proactive Nudge";
const char kComposeProactiveNudgeDescription[] =
    "Enables proactive nudging for Compose";

const char kComposePoliteNudgeName[] = "Compose Polite a11y announcement";
const char kComposePoliteNudgeDescription[] =
    "Uses polite announcements to alert the user that a compose popup is "
    "available to interact with.";

const char kComposeSegmentationPromotionName[] =
    "Compose Segmentation Promotion";
const char kComposeSegmentationPromotionDescription[] =
    "Enables the segmentation platform for the Compose proactive nudge";

const char kComposeSelectionNudgeName[] = "Compose Selection Nudge";
const char kComposeSelectionNudgeDescription[] =
    "Enables nudge on selection for Compose";

const char kComposeUpfrontInputModesName[] = "Compose Upfront Input Modes";
const char kComposeUpfrontInputModesDescription[] =
    "Enables upfront input modes in the Compose dialog";
#endif  // BUILDFLAG(ENABLE_COMPOSE)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
const char kThirdPartyProfileManagementName[] =
    "Third party profile management";
const char kThirdPartyProfileManagementDescription[] =
    "Enables profile management triggered by third-party sign-ins.";

const char kOidcAuthProfileManagementName[] = "OIDC profile management";
const char kOidcAuthProfileManagementDescription[] =
    "Enables profile management triggered by OIDC authentications.";

const char kUnoDesktopName[] = "UNO Desktop";
const char kUnoDesktopDescription[] =
    "Enables the UNO model on Desktop. This is currently an experiment in a "
    "prototype stage in order to validate the model.";

const char kExplicitBrowserSigninUIOnDesktopName[] =
    "Explicit Browser Signin UI On Desktop";
const char kExplicitBrowserSigninUIOnDesktopDescription[] =
    "Enables the UNO model on Desktop. Used for the launch of the UNO model on "
    "Desktop, as well as for the later phases of the experiment.";

const char kGlicName[] = "Glic";
const char kGlicDescription[] = "Enables glic";

const char kDesktopPWAsUserLinkCapturingScopeExtensionsName[] =
    "Desktop PWA Link Capturing with Scope Extensions";
const char kDesktopPWAsUserLinkCapturingScopeExtensionsDescription[] =
    "Allows the 'Desktop PWA Scope Extensions' feature to be used with the "
    "'Desktop PWA Link Capturing' feature. Both of those features are required "
    "to be turned on for this flag to have an effect.";

const char kSyncEnableBookmarksInTransportModeName[] =
    "Enable bookmarks in transport mode";
const char kSyncEnableBookmarksInTransportModeDescription[] =
    "Enables account bookmarks for signed-in non-syncing users";

const char kEnableGenericOidcAuthProfileManagementName[] =
    "Enable generic OIDC profile management";
const char kEnableGenericOidcAuthProfileManagementDescription[] =
    "Enables profile management triggered by generic OIDC authentications.";
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)

#if BUILDFLAG(ENABLE_HLS_DEMUXER)
const char kEnableBuiltinHlsName[] = "Builtin HLS player";
const char kEnableBuiltinHlsDescription[] =
    "Enables chrome's builtin HLS player instead of Android's MediaPlayer";
#endif  // BUILDFLAG(ENABLE_HLS_DEMUXER)

#if !BUILDFLAG(IS_CHROMEOS)
const char kProfilesReorderingName[] = "Profiles Reordering";
const char kProfilesReorderingDescription[] =
    "Enables profiles reordering in the Profile Picker main view by drag and "
    "dropping the Profile Tiles. The order is saved when changed and "
    "persisted.";
#endif

const char kProfilePickerGlicTesting[] = "Profile Picker Glic Testing";
const char kProfilePickerGlicTestingDescription[] =
    "Allows testing the Glic version of the Profile Picker.";

#if BUILDFLAG(ENABLE_DICE_SUPPORT)
const char kBatchUploadDesktopName[] = "Batch Upload Desktop";
const char kBatchUploadDesktopDescription[] =
    "Enables the Batch Upload feature for Desktop. This allows to upload local "
    "data to the account data when signed in. Currently only supports "
    "Passwords and Addresses";
#endif

#if BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)
const char kEnableBoundSessionCredentialsName[] =
    "Device Bound Session Credentials";
const char kEnableBoundSessionCredentialsDescription[] =
    "Enables Google session credentials binding to cryptographic keys.";

const char kEnableBoundSessionCredentialsSoftwareKeysForManualTestingName[] =
    "Device Bound Session Credentials with software keys";
const char
    kEnableBoundSessionCredentialsSoftwareKeysForManualTestingDescription[] =
        "Enables mock software-backed cryptographic keys for Google session "
        "credentials binding and Chrome refresh tokens binding (not secure). "
        "This is intended to be used for manual testing only.";

const char kEnableChromeRefreshTokenBindingName[] =
    "Chrome Refresh Token Binding";
const char kEnableChromeRefreshTokenBindingDescription[] =
    "Enables binding of Chrome refresh tokens to cryptographic keys.";
#endif  // BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)

const char kEnableStandardBoundSessionCredentialsName[] =
    "Device Bound Session Credentials (Standard)";
const char kEnableStandardBoundSessionCredentialsDescription[] =
    "Enables the official version of Device Bound Session Credentials. For "
    "more information see https://github.com/WICG/dbsc.";
const char kEnableStandardBoundSessionPersistenceName[] =
    "Device Bound Session Credentials (Standard) Persistence";
const char kEnableStandardBoundSessionPersistenceDescription[] =
    "Enables session persistence for the official version of "
    "Device Bound Session Credentials.";

#if BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)
const char kEnableCertManagementV2UIName[] = "Cert Management V2 UI";
const char kEnableCertManagementV2UIDescription[] =
    "Enables the Cert Management V2 UI; accessible at "
    "chrome://certificate-manager";
const char kEnableCertManagementV2UIWriteName[] =
    "Cert Management V2 UI Write features";
const char kEnableCertManagementV2UIWriteDescription[] =
    "Enables the Cert Management V2 UI write features, using a chrome managed "
    "DB "
    "to store user added certs. This is new functionality for Windows and Mac. "
    "For Linux and ChromeOS, this is a change as previously user-added certs "
    "would be written to the platform cert store. The UI is accessible at "
    "chrome://certificate-manager";
const char kEnableCertManagementV2UIEditCertsName[] =
    "Cert Management V2 UI Edit Certs";
const char kEnableCertManagementV2UIEditCertsDescription[] =
    "Enables the ability to edit trust and constraints on the cert viewer "
    "for user-added certs that are added via chrome://certificate-manager";
#endif  // BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)

#if !BUILDFLAG(IS_ANDROID)
const char kEnablePolicyPromotionBannerName[] =
    "Enable Policy Promotion Banner";
const char kEnablePolicyPromotionBannerDescription[] =
    "Enables showing the policy promotion banner on chrome://policy page.";
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
const char kOverlayScrollbarsOSSettingsName[] = "Overlay Scrollbar OS Settings";
const char kOverlayScrollbarsOSSettingsDescription[] =
    "Enable the OS settings for overlay scrollbars on ChromeOS.";
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
const char kSupervisedProfileHideGuestName[] = "Supervised Profile Hide Guest";
const char kSupervisedProfileHideGuestDescription[] =
    "Hides Guest Profile entry points for supervised users";

const char kSupervisedProfileSafeSearchName[] = "Supervised Profile SafeSearch";
const char kSupervisedProfileSafeSearchDescription[] =
    "Enables SafeSearch in Google Search for supervised users in the pending "
    "state.";

const char kSupervisedProfileReauthForYouTubeName[] =
    "Supervised Profile YouTube reauth";
const char kSupervisedProfileReauthForYouTubeDescription[] =
    "Ask supervised users to re-authenticate when attempting to access YouTube "
    "in the pending state.";

const char kSupervisedProfileReauthForBlockedSiteName[] =
    "Supervised Profile blocked site reauth";
const char kSupervisedProfileReauthForBlockedSiteDescription[] =
    "Ask supervised users to re-authenticate when attempting to navigate to a "
    "site blocked by parental controls.";

const char kSupervisedProfileSubframeReauthName[] =
    "Supervised Profile reauth in subframes";
const char kSupervisedProfileSubframeReauthDescription[] =
    "If \"Supervised Profile YouTube reauth\" or \"Supervised Profile blocked "
    "site reauth\" is enabled, require supervised users to re-authenticate "
    "before accessing embedded YouTube videos or blocked sites in subframes, "
    "respectively.";

const char kSupervisedProfileFilteringFallbackName[] =
    "Supervised Profile filtering fallback";
const char kSupervisedProfileFilteringFallbackDescription[] =
    "Applies website filters for supervised users in the pending state, if the "
    "Family Link website filtering setting is set to block explicit sites. "
    "If the Family Link website filtering setting is set to another value, it "
    "is applied in the pending regardless of this flag.";

const char kSupervisedProfileCustomStringsName[] =
    "Supervised Profile custom strings";
const char kSupervisedProfileCustomStringsDescription[] =
    "Displays modified strings on both the sign-in intercept UI and the "
    "pre-UNO sync opt out screen";

const char kSupervisedProfileSignInIphName[] = "Supervised Profile sign-in IPH";
const char kSupervisedProfileSignInIphDescription[] =
    "Displays an in-product help message when a Profile becomes owned by a "
    "supervised user (either on creation of the new profile, or after sign "
    "in).";

const char kSupervisedProfileShowKiteBadgeName[] =
    "Supervised Profile show kite badge";
const char kSupervisedProfileShowKiteBadgeDescription[] =
    "Shows a kite badge on the profile avatar for supervised users.";

const char kSupervisedUserLocalWebApprovalsName[] =
    "Enable local web approvals feature";
const char kSupervisedUserLocalWebApprovalsDescription[] =
    "Enables parents to approve blocked websites on a child's device.";

#endif  // #if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)

#if BUILDFLAG(IS_ANDROID)
const char kHistoryOptInEntryPointsName[] = "History opt-in entry points";
const char kHistoryOptInEntryPointsDescription[] =
    "Add some history opt-in entry points.";

const char kSupervisedUserForceSigninWithCapabilitiesName[] =
    "Use capabilities for supervised user forced sign-in";
const char kSupervisedUserForceSigninWithCapabilitiesDescription[] =
    "Migrate the usage of USM flags to force supervised user accounts to be "
    "signed in to Chrome to instead use account capabilities.";
#endif  // BUILDFLAG(IS_ANDROID)

=======
>>>>>>> chromium
// ============================================================================
// Don't just add flags to the end, put them in the right section in
// alphabetical order just like the header file.
// ============================================================================

}  // namespace flag_descriptions
