// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_FLAG_DESCRIPTIONS_H_
#define CHROME_BROWSER_FLAG_DESCRIPTIONS_H_

// Includes needed for macros allowing conditional compilation of some strings.
#include "base/check_op.h"
#include "build/branding_buildflags.h"
#include "build/build_config.h"
#include "build/buildflag.h"
#include "chrome/common/buildflags.h"
#include "components/nacl/common/buildflags.h"
#include "components/paint_preview/buildflags/buildflags.h"
#include "components/signin/public/base/signin_buildflags.h"
#include "components/spellcheck/spellcheck_buildflags.h"
#include "device/vr/buildflags/buildflags.h"
#include "media/media_buildflags.h"
#include "ppapi/buildflags/buildflags.h"
#include "printing/buildflags/buildflags.h"
#include "third_party/blink/public/common/buildflags.h"

#if defined(OS_LINUX) || defined(OS_CHROMEOS)
#include "base/allocator/buildflags.h"
#endif  // defined(OS_LINUX) || defined(OS_CHROMEOS)

// This file declares strings used in chrome://flags. These messages are not
// translated, because instead of end-users they target Chromium developers and
// testers. See https://crbug.com/587272 and https://crbug.com/703134 for more
// details.
//
// Comments are not necessary. The contents of the strings (which appear in the
// UI) should be good enough documentation for what flags do and when they
// apply. If they aren't, fix them.
//
// Sort flags in each section alphabetically by the k...Name constant. Follow
// that by the k...Description constant and any special values associated with
// that.
//
// Put #ifdefed flags in the appropriate section toward the bottom, don't
// intersperse the file with ifdefs.

namespace flag_descriptions {

// Cross-platform -------------------------------------------------------------

extern const char kAccelerated2dCanvasName[];
extern const char kAccelerated2dCanvasDescription[];

extern const char kAcceleratedVideoDecodeName[];
extern const char kAcceleratedVideoDecodeDescription[];

extern const char kAcceleratedVideoEncodeName[];
extern const char kAcceleratedVideoEncodeDescription[];

extern const char kEnableMediaInternalsName[];
extern const char kEnableMediaInternalsDescription[];

<<<<<<< HEAD
extern const char kAiSettingsPageEnterpriseDisabledName[];
extern const char kAiSettingsPageEnterpriseDisabledDescription[];

extern const char kAlignSurfaceLayerImplToPixelGridName[];
extern const char kAlignSurfaceLayerImplToPixelGridDescription[];
=======
#if BUILDFLAG(ENABLE_PLUGINS)
extern const char kAccessiblePDFFormName[];
extern const char kAccessiblePDFFormDescription[];
#endif  // BUILDFLAG(ENABLE_PLUGINS)
>>>>>>> chromium

extern const char kAccountIdMigrationName[];
extern const char kAccountIdMigrationDescription[];

extern const char kAlignFontDisplayAutoTimeoutWithLCPGoalName[];
extern const char kAlignFontDisplayAutoTimeoutWithLCPGoalDescription[];

extern const char kAllowInsecureLocalhostName[];
extern const char kAllowInsecureLocalhostDescription[];

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_EXTENSIONS)
extern const char kAllowLegacyMV2ExtensionsName[];
extern const char kAllowLegacyMV2ExtensionsDescription[];
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)

extern const char kAndroidAppIntegrationName[];
extern const char kAndroidAppIntegrationDescription[];

extern const char kAndroidAppIntegrationModuleName[];
extern const char kAndroidAppIntegrationModuleDescription[];

extern const char kAndroidAppIntegrationV2Name[];
extern const char kAndroidAppIntegrationV2Description[];

extern const char kAndroidAppIntegrationWithFaviconName[];
extern const char kAndroidAppIntegrationWithFaviconDescription[];

extern const char kAndroidBcivBottomControlsName[];
extern const char kAndroidBcivBottomControlsDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kAndroidBookmarkBarName[];
extern const char kAndroidBookmarkBarDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

extern const char kAndroidBottomToolbarName[];
extern const char kAndroidBottomToolbarDescription[];

extern const char kAndroidExtendedKeyboardShortcutsName[];
extern const char kAndroidExtendedKeyboardShortcutsDescription[];

extern const char kAndroidBrowserControlsInVizName[];
extern const char kAndroidBrowserControlsInVizDescription[];
=======
extern const char kAllowSyncXHRInPageDismissalName[];
extern const char kAllowSyncXHRInPageDismissalDescription[];
>>>>>>> chromium

#if BUILDFLAG(IS_CHROMEOS)
extern const char kVpnAppsOnFlexName[];
extern const char kVpnAppsOnFlexDescription[];

<<<<<<< HEAD
extern const char kAnnotatorModeName[];
extern const char kAnnotatorModeDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS)

extern const char kAriaElementReflectionName[];
extern const char kAriaElementReflectionDescription[];

extern const char kAutomaticUsbDetachName[];
extern const char kAutomaticUsbDetachDescription[];

extern const char kAutomotiveFullscreenToolbarImprovementsName[];
extern const char kAutomotiveFullscreenToolbarImprovementsDescription[];

extern const char kAuxiliarySearchDonationName[];
extern const char kAuxiliarySearchDonationDescription[];

extern const char kBackgroundResourceFetchName[];
extern const char kBackgroundResourceFetchDescription[];

extern const char
    kBlinkSchedulerDiscreteInputMatchesResponsivenessMetricsName[];
extern const char
    kBlinkSchedulerDiscreteInputMatchesResponsivenessMetricsDescription[];

#if !BUILDFLAG(IS_ANDROID)
extern const char kBookmarksTreeViewName[];
extern const char kBookmarksTreeViewDescription[];
#endif

#if BUILDFLAG(IS_CHROMEOS)
extern const char kBirchWeatherName[];
extern const char kBirchWeatherDescription[];

extern const char kCampaignsComponentUpdaterTestTagName[];
extern const char kCampaignsComponentUpdaterTestTagDescription[];
extern const char kCampaignsOverrideName[];
extern const char kCampaignsOverrideDescription[];
#endif  // IS_CHROMEOS

=======
extern const char kAriaElementReflectionName[];
extern const char kAriaElementReflectionDescription[];

extern const char kCOLRV1FontsName[];
>>>>>>> chromium
extern const char kCOLRV1FontsDescription[];

extern const char kCSSContainerQueriesName[];
extern const char kCSSContainerQueriesDescription[];

extern const char kContentLanguagesInLanguagePickerName[];
extern const char kContentLanguagesInLanguagePickerDescription[];

extern const char kConversionMeasurementApiName[];
extern const char kConversionMeasurementApiDescription[];

extern const char kConversionMeasurementDebugModeName[];
extern const char kConversionMeasurementDebugModeDescription[];

extern const char kDebugHistoryInterventionNoUserActivationName[];
extern const char kDebugHistoryInterventionNoUserActivationDescription[];

<<<<<<< HEAD
extern const char kClientSideDetectionBrandAndIntentForScamDetectionName[];
extern const char
    kClientSideDetectionBrandAndIntentForScamDetectionDescription[];

extern const char kClipboardMaximumAgeName[];
extern const char kClipboardMaximumAgeDescription[];

extern const char kComputePressureRateObfuscationMitigationName[];
extern const char kComputePressureRateObfuscationMitigationDescription[];

extern const char kComputePressureBreakCalibrationMitigationName[];
extern const char kComputePressureBreakCalibrationMitigationDescription[];

extern const char kContainerTypeNoLayoutContainmentName[];
extern const char kContainerTypeNoLayoutContainmentDescription[];

extern const char kContentSettingsPartitioningName[];
extern const char kContentSettingsPartitioningDescription[];

extern const char kCopyImageFilenameToClipboardName[];
extern const char kCopyImageFilenameToClipboardDescription[];

#if BUILDFLAG(IS_CHROMEOS)
extern const char kCoralFeatureKeyName[];
extern const char kCoralFeatureKeyDescription[];

extern const char kCrosSwitcherName[];
extern const char kCrosSwitcherDescription[];
#endif  // IS_CHROMEOS

extern const char kCssGamutMappingName[];
extern const char kCssGamutMappingDescription[];

extern const char kCssTextBoxTrimName[];
extern const char kCssTextBoxTrimDescription[];

extern const char kCustomizeChromeSidePanelExtensionsCardName[];
extern const char kCustomizeChromeSidePanelExtensionsCardDescription[];

extern const char kCustomizeChromeWallpaperSearchName[];
extern const char kCustomizeChromeWallpaperSearchDescription[];

extern const char kCustomizeChromeWallpaperSearchButtonName[];
extern const char kCustomizeChromeWallpaperSearchButtonDescription[];

extern const char kCustomizeChromeWallpaperSearchInspirationCardName[];
extern const char kCustomizeChromeWallpaperSearchInspirationCardDescription[];

extern const char kDataSharingName[];
extern const char kDataSharingDescription[];

extern const char kDataSharingJoinOnlyName[];
extern const char kDataSharingJoinOnlyDescription[];

extern const char kHistorySyncAlternativeIllustrationName[];
extern const char kHistorySyncAlternativeIllustrationDescription[];

extern const char kDeprecateUnloadName[];
extern const char kDeprecateUnloadDescription[];

extern const char kDeferRendererTasksAfterInputName[];
extern const char kDeferRendererTasksAfterInputDescription[];

#if BUILDFLAG(IS_CHROMEOS)
extern const char kDemoModeComponentUpdaterTestTagName[];
extern const char kDemoModeComponentUpdaterTestTagDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS)

extern const char kDevToolsPrivacyUIName[];
extern const char kDevToolsPrivacyUIDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kDisableInstanceLimitName[];
extern const char kDisableInstanceLimitDescription[];
#endif

extern const char kDownloadWarningImprovementsName[];
extern const char kDownloadWarningImprovementsDescription[];

extern const char kEnableBenchmarkingName[];
extern const char kEnableBenchmarkingDescription[];
extern const char kEnableBenchmarkingChoiceDisabled[];
extern const char kEnableBenchmarkingChoiceDefaultFeatureStates[];
extern const char kEnableBenchmarkingChoiceMatchFieldTrialTestingConfig[];

extern const char kEnableBookmarksSelectedTypeOnSigninForTestingName[];
extern const char kEnableBookmarksSelectedTypeOnSigninForTestingDescription[];

extern const char kEnableLazyLoadImageForInvisiblePageName[];
extern const char kEnableLazyLoadImageForInvisiblePageDescription[];

extern const char kFontationsFontBackendName[];
extern const char kFontationsFontBackendDescription[];
=======
extern const char kDeprecateMenagerieAPIName[];
extern const char kDeprecateMenagerieAPIDescription[];
>>>>>>> chromium

extern const char kForceStartupSigninPromoName[];
extern const char kForceStartupSigninPromoDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
extern const char kForestFeatureName[];
extern const char kForestFeatureDescription[];
#endif
=======
extern const char kDetectedSourceLanguageOptionName[];
extern const char kDetectedSourceLanguageOptionDescription[];
>>>>>>> chromium

extern const char kLauncherAppSortName[];
extern const char kLauncherAppSortDescription[];

<<<<<<< HEAD
extern const char kTangibleSyncName[];
extern const char kTangibleSyncDescription[];

extern const char kMediaSessionEnterPictureInPictureName[];
extern const char kMediaSessionEnterPictureInPictureDescription[];
=======
extern const char kDetectFormSubmissionOnFormClearName[];
extern const char kDetectFormSubmissionOnFormClearDescription[];

extern const char kEditPasswordsInSettingsName[];
extern const char kEditPasswordsInSettingsDescription[];

extern const char kEnableBluetoothSerialPortProfileInSerialApiName[];
extern const char kEnableBluetoothSerialPortProfileInSerialApiDescription[];

extern const char kEnableFtpName[];
extern const char kEnableFtpDescription[];
>>>>>>> chromium

extern const char kEnablePolicyBlocklistThrottleRequiresPoliciesLoadedName[];
extern const char
    kEnablePolicyBlocklistThrottleRequiresPoliciesLoadedDescription[];

<<<<<<< HEAD
extern const char kEnableSnackbarInSettingsName[];
extern const char kEnableSnackbarInSettingsDescription[];

extern const char kUseAndroidStagingSmdsName[];
extern const char kUseAndroidStagingSmdsDescription[];
=======
extern const char kEnableSignedExchangeSubresourcePrefetchName[];
extern const char kEnableSignedExchangeSubresourcePrefetchDescription[];
>>>>>>> chromium

extern const char kEnableSignedExchangePrefetchCacheForNavigationsName[];
extern const char kEnableSignedExchangePrefetchCacheForNavigationsDescription[];

extern const char kUpdatedCellularActivationUiName[];
extern const char kUpdatedCellularActivationUiDescription[];

extern const char kUseLookalikesForNavigationSuggestionsName[];
extern const char kUseLookalikesForNavigationSuggestionsDescription[];

extern const char kUseStorkSmdsServerAddressName[];
extern const char kUseStorkSmdsServerAddressDescription[];

extern const char kUseWallpaperStagingUrlName[];
extern const char kUseWallpaperStagingUrlDescription[];

extern const char kSemanticColorsDebugOverrideName[];
extern const char kSemanticColorsDebugOverrideDescription[];

extern const char kUseMessagesStagingUrlName[];
extern const char kUseMessagesStagingUrlDescription[];

extern const char kUseCustomMessagesDomainName[];
extern const char kUseCustomMessagesDomainDescription[];

extern const char kAndroidPictureInPictureAPIName[];
extern const char kAndroidPictureInPictureAPIDescription[];

extern const char kAppCacheName[];
extern const char kAppCacheDescription[];

extern const char kAssistantExplicitVoiceConsentName[];
extern const char kAssistantExplicitVoiceConsentDescription[];

<<<<<<< HEAD
extern const char kImprovedSettingsUIOnDesktopName[];
extern const char kImprovedSettingsUIOnDesktopDescription[];

extern const char kIsSecurePaymentConfirmationAvailableAPIName[];
extern const char kIsSecurePaymentConfirmationAvailableAPIDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kAutofillDeprecateAccessibilityApiName[];
extern const char kAutofillDeprecateAccessibilityApiDescription[];
#endif  // BUILDFLAG(IS_ANDROID)
=======
extern const char kAssistantVoiceConstentTapsCounterName[];
extern const char kAssistantVoiceConstentTapsCounterDescription[];
>>>>>>> chromium

extern const char kAutofillAlwaysReturnCloudTokenizedCardName[];
extern const char kAutofillAlwaysReturnCloudTokenizedCardDescription[];

<<<<<<< HEAD
extern const char kAutofillEnableAllowlistForBmoCardCategoryBenefitsName[];
extern const char
    kAutofillEnableAllowlistForBmoCardCategoryBenefitsDescription[];

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
extern const char kAutofillEnableAmountExtractionDesktopName[];
extern const char kAutofillEnableAmountExtractionDesktopDescription[];
#endif
=======
extern const char kAutofillAssistantChromeEntryName[];
extern const char kAutofillAssistantChromeEntryDescription[];
>>>>>>> chromium

extern const char kAutofillAutoTriggerManualFallbackForCardsName[];
extern const char kAutofillAutoTriggerManualFallbackForCardsDescription[];

extern const char kAutofillEnableGoogleIssuedCardName[];
extern const char kAutofillEnableGoogleIssuedCardDescription[];

extern const char kAutofillEnableMerchantBoundVirtualCardsName[];
extern const char kAutofillEnableMerchantBoundVirtualCardsDescription[];

extern const char kAutofillEnableOfferNotificationName[];
extern const char kAutofillEnableOfferNotificationDescription[];

<<<<<<< HEAD
extern const char kAutofillEnableCvcStorageAndFillingEnhancementName[];
extern const char kAutofillEnableCvcStorageAndFillingEnhancementDescription[];

extern const char
    kAutofillEnableCvcStorageAndFillingStandaloneFormEnhancementName[];
extern const char
    kAutofillEnableCvcStorageAndFillingStandaloneFormEnhancementDescription[];

extern const char kAutofillEnableFpanRiskBasedAuthenticationName[];
extern const char kAutofillEnableFpanRiskBasedAuthenticationDescription[];

extern const char kAutofillEnableCardBenefitsForAmericanExpressName[];
extern const char kAutofillEnableCardBenefitsForAmericanExpressDescription[];

extern const char kAutofillEnableCardBenefitsForBmoName[];
extern const char kAutofillEnableCardBenefitsForBmoDescription[];

extern const char kAutofillEnableCardBenefitsIphName[];
extern const char kAutofillEnableCardBenefitsIphDescription[];

extern const char kAutofillEnableCardBenefitsSyncName[];
extern const char kAutofillEnableCardBenefitsSyncDescription[];

extern const char kAutofillEnableCardInfoRuntimeRetrievalName[];
extern const char kAutofillEnableCardInfoRuntimeRetrievalDescription[];

extern const char kAutofillEnableCardProductNameName[];
extern const char kAutofillEnableCardProductNameDescription[];

extern const char kAutofillEnableLogFormEventsToAllParsedFormTypesName[];
extern const char kAutofillEnableLogFormEventsToAllParsedFormTypesDescription[];

extern const char kAutofillEnableNewCardArtAndNetworkImagesName[];
extern const char kAutofillEnableNewCardArtAndNetworkImagesDescription[];
=======
extern const char kAutofillEnableOfferNotificationCrossTabTrackingName[];
extern const char kAutofillEnableOfferNotificationCrossTabTrackingDescription[];
>>>>>>> chromium

extern const char kAutofillEnableOffersInClankKeyboardAccessoryName[];
extern const char kAutofillEnableOffersInClankKeyboardAccessoryDescription[];

extern const char kAutofillEnableOffersInDownstreamName[];
extern const char kAutofillEnableOffersInDownstreamDescription[];

extern const char kAutofillEnableStickyManualFallbackForCardsName[];
extern const char kAutofillEnableStickyManualFallbackForCardsDescription[];

extern const char kAutofillEnableToolbarStatusChipName[];
extern const char kAutofillEnableToolbarStatusChipDescription[];

extern const char kAutofillEnableVirtualCardName[];
extern const char kAutofillEnableVirtualCardDescription[];

extern const char kAutofillFixOfferInIncognitoName[];
extern const char kAutofillFixOfferInIncognitoDescription[];

<<<<<<< HEAD
extern const char kAutofillEnableSaveAndFillName[];
extern const char kAutofillEnableSaveAndFillDescription[];

extern const char kAutofillEnableSaveCardLoadingAndConfirmationName[];
extern const char kAutofillEnableSaveCardLoadingAndConfirmationDescription[];
=======
extern const char kAutofillParseMerchantPromoCodeFieldsName[];
extern const char kAutofillParseMerchantPromoCodeFieldsDescription[];
>>>>>>> chromium

extern const char kAutofillProfileClientValidationName[];
extern const char kAutofillProfileClientValidationDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
extern const char kAutofillEnableSyncingOfPixBankAccountsName[];
extern const char kAutofillEnableSyncingOfPixBankAccountsDescription[];
#endif  // BUILDFLAG(IS_ANDROID)
=======
extern const char kAutofillProfileServerValidationName[];
extern const char kAutofillProfileServerValidationDescription[];

extern const char kAutofillPruneSuggestionsName[];
extern const char kAutofillPruneSuggestionsDescription[];
>>>>>>> chromium

extern const char kAutofillSaveAndFillVPAName[];
extern const char kAutofillSaveAndFillVPADescription[];

extern const char kAutofillSuggestVirtualCardsOnIncompleteFormName[];
extern const char kAutofillSuggestVirtualCardsOnIncompleteFormDescription[];

extern const char kAutofillUseImprovedLabelDisambiguationName[];
extern const char kAutofillUseImprovedLabelDisambiguationDescription[];

extern const char kAutoScreenBrightnessName[];
extern const char kAutoScreenBrightnessDescription[];

<<<<<<< HEAD
extern const char kAutofillEnableVirtualCardMetadataName[];
extern const char kAutofillEnableVirtualCardMetadataDescription[];

extern const char kAutofillImprovedLabelsName[];
extern const char kAutofillImprovedLabelsDescription[];

extern const char kAutofillParseVcnCardOnFileStandaloneCvcFieldsName[];
extern const char kAutofillParseVcnCardOnFileStandaloneCvcFieldsDescription[];

extern const char kAutofillRemovePaymentsButterDropdownName[];
extern const char kAutofillRemovePaymentsButterDropdownDescription[];

extern const char kAutofillSharedStorageServerCardDataName[];
extern const char kAutofillSharedStorageServerCardDataDescription[];

extern const char kAutofillMoreProminentPopupName[];
extern const char kAutofillMoreProminentPopupDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kAutofillSyncEwalletAccountsName[];
extern const char kAutofillSyncEwalletAccountsDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

extern const char kAutofillUnmaskCardRequestTimeoutName[];
extern const char kAutofillUnmaskCardRequestTimeoutDescription[];

extern const char kAutofillUploadCardRequestTimeoutName[];
extern const char kAutofillUploadCardRequestTimeoutDescription[];

extern const char kAutofillVcnEnrollRequestTimeoutName[];
extern const char kAutofillVcnEnrollRequestTimeoutDescription[];

extern const char kAutofillVirtualViewStructureAndroidName[];
extern const char kAutofillVirtualViewStructureAndroidDescription[];

extern const char kAutoPictureInPictureForVideoPlaybackName[];
extern const char kAutoPictureInPictureForVideoPlaybackDescription[];

extern const char kAutoPictureInPictureVideoHeuristicsName[];
extern const char kAutoPictureInPictureVideoHeuristicsDescription[];
=======
extern const char kAvatarToolbarButtonName[];
extern const char kAvatarToolbarButtonDescription[];
>>>>>>> chromium

extern const char kBackForwardCacheName[];
extern const char kBackForwardCacheDescription[];

extern const char kBentoBarName[];
extern const char kBentoBarDescription[];

extern const char kBiometricReauthForPasswordFillingName[];
extern const char kBiometricReauthForPasswordFillingDescription[];

<<<<<<< HEAD
extern const char kBindCookiesToPortName[];
extern const char kBindCookiesToPortDescription[];

extern const char kBindCookiesToSchemeName[];
extern const char kBindCookiesToSchemeDescription[];

extern const char kBorealisBigGlName[];
extern const char kBorealisBigGlDescription[];

extern const char kBorealisDGPUName[];
extern const char kBorealisDGPUDescription[];

extern const char kBorealisEnableUnsupportedHardwareName[];
extern const char kBorealisEnableUnsupportedHardwareDescription[];

extern const char kBorealisForceBetaClientName[];
extern const char kBorealisForceBetaClientDescription[];

extern const char kBorealisForceDoubleScaleName[];
extern const char kBorealisForceDoubleScaleDescription[];

extern const char kBorealisLinuxModeName[];
extern const char kBorealisLinuxModeDescription[];

extern const char kBorealisPermittedName[];
extern const char kBorealisPermittedDescription[];

extern const char kBorealisProvisionName[];
extern const char kBorealisProvisionDescription[];

extern const char kBorealisScaleClientByDPIName[];
extern const char kBorealisScaleClientByDPIDescription[];

extern const char kBorealisZinkGlDriverName[];
extern const char kBorealisZinkGlDriverDescription[];
=======
extern const char kBorealisDiskManagementName[];
extern const char kBorealisDiskManagementDescription[];
>>>>>>> chromium

extern const char kBypassAppBannerEngagementChecksName[];
extern const char kBypassAppBannerEngagementChecksDescription[];

extern const char kChangePasswordAffiliationInfoName[];
extern const char kChangePasswordAffiliationInfoDescription[];

extern const char kCheckOfflineCapabilityName[];
extern const char kCheckOfflineCapabilityDescription[];

extern const char kChromeLabsName[];
extern const char kChromeLabsDescription[];

extern const char kCompositeAfterPaintName[];
extern const char kCompositeAfterPaintDescription[];

extern const char kContextMenuGoogleLensChipName[];
extern const char kContextMenuGoogleLensChipDescription[];

extern const char kContextMenuSearchWithGoogleLensName[];
extern const char kContextMenuSearchWithGoogleLensDescription[];

extern const char kContextMenuShopWithGoogleLensName[];
extern const char kContextMenuShopWithGoogleLensDescription[];

extern const char kContextMenuSearchAndShopWithGoogleLensName[];
extern const char kContextMenuSearchAndShopWithGoogleLensDescription[];

extern const char kContextMenuTranslateWithGoogleLensName[];
extern const char kContextMenuTranslateWithGoogleLensDescription[];

extern const char kClipboardCustomFormatsName[];
extern const char kClipboardCustomFormatsDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
extern const char kContextualCueingName[];
extern const char kContextualCueingDescription[];
#endif  // #if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
=======
extern const char kClickToOpenPDFName[];
extern const char kClickToOpenPDFDescription[];

extern const char kClientStorageAccessContextAuditingName[];
extern const char kClientStorageAccessContextAuditingDescription[];

extern const char kConditionalTabStripAndroidName[];
extern const char kConditionalTabStripAndroidDescription[];
>>>>>>> chromium

extern const char kClearCrossSiteCrossBrowsingContextGroupWindowNameName[];
extern const char
    kClearCrossSiteCrossBrowsingContextGroupWindowNameDescription[];

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
extern const char kChromeTipsInMainMenuName[];
extern const char kChromeTipsInMainMenuDescription[];

extern const char kChromeTipsInMainMenuNewBadgeName[];
extern const char kChromeTipsInMainMenuNewBadgeDescription[];
#endif

extern const char kChromeWhatsNewUIName[];
extern const char kChromeWhatsNewUIDescription[];

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
extern const char kChromeWhatsNewInMainMenuNewBadgeName[];
extern const char kChromeWhatsNewInMainMenuNewBadgeDescription[];
#endif

extern const char kCompositingBasedThrottling[];
extern const char kCompositingBasedThrottlingDescription[];

extern const char kDarkLightTestName[];
extern const char kDarkLightTestDescription[];

extern const char kDecodeJpeg420ImagesToYUVName[];
extern const char kDecodeJpeg420ImagesToYUVDescription[];

extern const char kDecodeLossyWebPImagesToYUVName[];
extern const char kDecodeLossyWebPImagesToYUVDescription[];

extern const char kDetectTargetEmbeddingLookalikesName[];
extern const char kDetectTargetEmbeddingLookalikesDescription[];

extern const char kDisableProcessReuse[];
extern const char kDisableProcessReuseDescription[];

<<<<<<< HEAD
extern const char kDiscountConsentV2Name[];
extern const char kDiscountConsentV2Description[];

=======
>>>>>>> chromium
extern const char kDoubleBufferCompositingName[];
extern const char kDoubleBufferCompositingDescription[];

extern const char kDnsOverHttpsName[];
extern const char kDnsOverHttpsDescription[];

<<<<<<< HEAD
extern const char kCollaborationMessagingName[];
extern const char kCollaborationMessagingDescription[];

extern const char kCompressionDictionaryTransportName[];
extern const char kCompressionDictionaryTransportDescription[];
=======
extern const char kDnsHttpssvcName[];
extern const char kDnsHttpssvcDescription[];
>>>>>>> chromium

extern const char kEnableFirstPartySetsName[];
extern const char kEnableFirstPartySetsDescription[];

extern const char kEnablePasswordsAccountStorageName[];
extern const char kEnablePasswordsAccountStorageDescription[];

<<<<<<< HEAD
extern const char kCompressionDictionaryTransportOverHttp2Name[];
extern const char kCompressionDictionaryTransportOverHttp2Description[];

extern const char kCompressionDictionaryTransportRequireKnownRootCertName[];
extern const char
    kCompressionDictionaryTransportRequireKnownRootCertDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kContextualSearchWithCredentialsForDebugName[];
extern const char kContextualSearchWithCredentialsForDebugDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

extern const char kUseDMSAAForTilesName[];
extern const char kUseDMSAAForTilesDescription[];

extern const char kUseDnsHttpsSvcbAlpnName[];
extern const char kUseDnsHttpsSvcbAlpnDescription[];

extern const char kIsolatedSandboxedIframesName[];
extern const char kIsolatedSandboxedIframesDescription[];
=======
extern const char kEnablePasswordsAccountStorageIPHName[];
extern const char kEnablePasswordsAccountStorageIPHDescription[];
>>>>>>> chromium

extern const char kExperimentalAccessibilityLanguageDetectionName[];
extern const char kExperimentalAccessibilityLanguageDetectionDescription[];

extern const char kExperimentalAccessibilityLanguageDetectionDynamicName[];
extern const char
    kExperimentalAccessibilityLanguageDetectionDynamicDescription[];

extern const char kFontAccessAPIName[];
extern const char kFontAccessAPIDescription[];

extern const char kFontAccessPersistentName[];
extern const char kFontAccessPersistentDescription[];

extern const char kForceColorProfileSRGB[];
extern const char kForceColorProfileP3[];
extern const char kForceColorProfileColorSpin[];
extern const char kForceColorProfileSCRGBLinear[];
extern const char kForceColorProfileHDR10[];

extern const char kForceColorProfileName[];
extern const char kForceColorProfileDescription[];

extern const char kDynamicColorGamutName[];
extern const char kDynamicColorGamutDescription[];

<<<<<<< HEAD
=======
extern const char kCooperativeSchedulingName[];
extern const char kCooperativeSchedulingDescription[];

extern const char kCreditCardAssistName[];
extern const char kCreditCardAssistDescription[];

>>>>>>> chromium
extern const char kDarkenWebsitesCheckboxInThemesSettingName[];
extern const char kDarkenWebsitesCheckboxInThemesSettingDescription[];

extern const char kDebugPackedAppName[];
extern const char kDebugPackedAppDescription[];

extern const char kDebugShortcutsName[];
extern const char kDebugShortcutsDescription[];

extern const char kDeviceDiscoveryNotificationsName[];
extern const char kDeviceDiscoveryNotificationsDescription[];

extern const char kDisallowDocWrittenScriptsUiName[];
extern const char kDisallowDocWrittenScriptsUiDescription[];

<<<<<<< HEAD
extern const char kViewTransitionLayeredCaptureName[];
extern const char kViewTransitionLayeredCaptureDescription[];
=======
extern const char kDocumentTransitionName[];
extern const char kDocumentTransitionDescription[];

extern const char kEnableAudioFocusEnforcementName[];
extern const char kEnableAudioFocusEnforcementDescription[];
>>>>>>> chromium

extern const char kEnableAutofillAccountWalletStorageName[];
extern const char kEnableAutofillAccountWalletStorageDescription[];

extern const char kEnableAutofillAddressSavePromptName[];
extern const char kEnableAutofillAddressSavePromptDescription[];

extern const char kEnableAutofillCreditCardAblationExperimentDisplayName[];
extern const char kEnableAutofillCreditCardAblationExperimentDescription[];

extern const char kEnableAutofillCreditCardAuthenticationName[];
extern const char kEnableAutofillCreditCardAuthenticationDescription[];

extern const char kEnableAutofillCreditCardUploadFeedbackName[];
extern const char kEnableAutofillCreditCardUploadFeedbackDescription[];

extern const char
    kEnableAutofillInfoBarAccountIndicationFooterForSingleAccountUsersName[];
extern const char
    kEnableAutofillInfoBarAccountIndicationFooterForSingleAccountUsersDescription
        [];

extern const char
    kEnableAutofillInfoBarAccountIndicationFooterForSyncUsersName[];
extern const char
    kEnableAutofillInfoBarAccountIndicationFooterForSyncUsersDescription[];

extern const char kEnableAutofillPasswordInfoBarAccountIndicationFooterName[];
extern const char
    kEnableAutofillPasswordInfoBarAccountIndicationFooterDescription[];

extern const char kEnableAutofillSaveCardInfoBarAccountIndicationFooterName[];
extern const char
    kEnableAutofillSaveCardInfoBarAccountIndicationFooterDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kEnterpriseRealTimeUrlCheckOnAndroidName[];
extern const char kEnterpriseRealTimeUrlCheckOnAndroidDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

extern const char kEnableExperimentalCookieFeaturesName[];
extern const char kEnableExperimentalCookieFeaturesDescription[];

extern const char kEnableSaveDataName[];
extern const char kEnableSaveDataDescription[];

extern const char kEnableNavigationPredictorName[];
extern const char kEnableNavigationPredictorDescription[];

extern const char kEnablePreconnectToSearchName[];
extern const char kEnablePreconnectToSearchDescription[];

extern const char kEnableRemovingAllThirdPartyCookiesName[];
extern const char kEnableRemovingAllThirdPartyCookiesDescription[];

extern const char kEnableBrowsingDataLifetimeManagerName[];
extern const char kEnableBrowsingDataLifetimeManagerDescription[];

extern const char kColorProviderRedirectionName[];
extern const char kColorProviderRedirectionDescription[];

extern const char kDesktopPWAsAppIconShortcutsMenuName[];
extern const char kDesktopPWAsAppIconShortcutsMenuDescription[];

extern const char kDesktopPWAsAppIconShortcutsMenuUIName[];
extern const char kDesktopPWAsAppIconShortcutsMenuUIDescription[];

extern const char kDesktopPWAsAttentionBadgingCrOSName[];
extern const char kDesktopPWAsAttentionBadgingCrOSDescription[];
extern const char kDesktopPWAsAttentionBadgingCrOSApiAndNotifications[];
extern const char kDesktopPWAsAttentionBadgingCrOSApiOverridesNotifications[];
extern const char kDesktopPWAsAttentionBadgingCrOSApiOnly[];
extern const char kDesktopPWAsAttentionBadgingCrOSNotificationsOnly[];

extern const char kDesktopPWAsPrefixAppNameInWindowTitleName[];
extern const char kDesktopPWAsPrefixAppNameInWindowTitleDescription[];

extern const char kDesktopPWAsRemoveStatusBarName[];
extern const char kDesktopPWAsRemoveStatusBarDescription[];

extern const char kDesktopPWAsElidedExtensionsMenuName[];
extern const char kDesktopPWAsElidedExtensionsMenuDescription[];

extern const char kDesktopPWAsFlashAppNameInsteadOfOriginName[];
extern const char kDesktopPWAsFlashAppNameInsteadOfOriginDescription[];

extern const char kDesktopPWAsNotificationIconAndTitleName[];
extern const char kDesktopPWAsNotificationIconAndTitleDescription[];

extern const char kDesktopPWAsLinkCapturingName[];
extern const char kDesktopPWAsLinkCapturingDescription[];

extern const char kDesktopPWAsManifestIdName[];
extern const char kDesktopPWAsManifestIdDescription[];

extern const char kDesktopPWAsTabStripName[];
extern const char kDesktopPWAsTabStripDescription[];

extern const char kDesktopPWAsTabStripLinkCapturingName[];
extern const char kDesktopPWAsTabStripLinkCapturingDescription[];

extern const char kDesktopPWAsTabStripSettingsName[];
extern const char kDesktopPWAsTabStripSettingsDescription[];

extern const char kDesktopPWAsRunOnOsLoginName[];
extern const char kDesktopPWAsRunOnOsLoginDescription[];

extern const char kDesktopPWAsSubAppsName[];
extern const char kDesktopPWAsSubAppsDescription[];

extern const char kDesktopPWAsProtocolHandlingName[];
extern const char kDesktopPWAsProtocolHandlingDescription[];

extern const char kDesktopPWAsUrlHandlingName[];
extern const char kDesktopPWAsUrlHandlingDescription[];

extern const char kDesktopPWAsWebBundlesName[];
extern const char kDesktopPWAsWebBundlesDescription[];

extern const char kDesktopPWAsWindowControlsOverlayName[];
extern const char kDesktopPWAsWindowControlsOverlayDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || \
    BUILDFLAG(IS_CHROMEOS)
extern const char kDocumentPictureInPictureAnimateResizeName[];
extern const char kDocumentPictureInPictureAnimateResizeDescription[];

extern const char kAudioDuckingName[];
extern const char kAudioDuckingDescription[];
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) ||
        // BUILDFLAG(IS_CHROMEOS)
=======
extern const char kEnableMigrateDefaultChromeAppToWebAppsGSuiteName[];
extern const char kEnableMigrateDefaultChromeAppToWebAppsGSuiteDescription[];

extern const char kEnableMigrateDefaultChromeAppToWebAppsNonGSuiteName[];
extern const char kEnableMigrateDefaultChromeAppToWebAppsNonGSuiteDescription[];

extern const char kEnableSyncRequiresPoliciesLoadedName[];
extern const char kEnableSyncRequiresPoliciesLoadedDescription[];
>>>>>>> chromium

extern const char kEnableTLS13EarlyDataName[];
extern const char kEnableTLS13EarlyDataDescription[];

extern const char kEnhancedNetworkVoicesName[];
extern const char kEnhancedNetworkVoicesDescription[];

extern const char kPostQuantumCECPQ2Name[];
extern const char kPostQuantumCECPQ2Description[];

extern const char kMacCoreLocationImplementationName[];
extern const char kMacCoreLocationImplementationDescription[];

<<<<<<< HEAD
extern const char kAccessibilityDisableTouchpadName[];
extern const char kAccessibilityDisableTouchpadDescription[];

extern const char kAccessibilityFlashScreenFeatureName[];
extern const char kAccessibilityFlashScreenFeatureDescription[];

extern const char kAccessibilityServiceName[];
extern const char kAccessibilityServiceDescription[];

extern const char kAccessibilityShakeToLocateName[];
extern const char kAccessibilityShakeToLocateDescription[];

extern const char kExperimentalAccessibilityColorEnhancementSettingsName[];
extern const char
    kExperimentalAccessibilityColorEnhancementSettingsDescription[];

extern const char kAccessibilityChromeVoxPageMigrationName[];
extern const char kAccessibilityChromeVoxPageMigrationDescription[];

extern const char kAccessibilityReducedAnimationsName[];
extern const char kAccessibilityReducedAnimationsDescription[];

extern const char kAccessibilityReducedAnimationsInKioskName[];
extern const char kAccessibilityReducedAnimationsInKioskDescription[];

extern const char kAccessibilityFaceGazeName[];
extern const char kAccessibilityFaceGazeDescription[];

extern const char kAccessibilityMagnifierFollowsChromeVoxName[];
extern const char kAccessibilityMagnifierFollowsChromeVoxDescription[];

extern const char kAccessibilityMouseKeysName[];
extern const char kAccessibilityMouseKeysDescription[];

extern const char kAccessibilitySelectToSpeakPrefsMigrationName[];
extern const char kAccessibilitySelectToSpeakPrefsMigrationDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kBiometricAuthIdentityCheckName[];
extern const char kBiometricAuthIdentityCheckDescription[];
#endif  // BUILDFLAG(IS_ANDROID)
=======
extern const char kMacCoreLocationBackendName[];
extern const char kMacCoreLocationBackendDescription[];
>>>>>>> chromium

extern const char kNewMacNotificationAPIName[];
extern const char kNewMacNotificationAPIDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
extern const char kNewTabPageCustomizationName[];
extern const char kNewTabPageCustomizationDescription[];
#endif  // BUILDFLAG(IS_ANDROID)
=======
extern const char kNotificationsViaHelperAppName[];
extern const char kNotificationsViaHelperAppDescription[];

extern const char kWinrtGeolocationImplementationName[];
extern const char kWinrtGeolocationImplementationDescription[];
>>>>>>> chromium

extern const char kEnableGenericSensorExtraClassesName[];
extern const char kEnableGenericSensorExtraClassesDescription[];

extern const char kEnableGpuServiceLoggingName[];
extern const char kEnableGpuServiceLoggingDescription[];

extern const char kEnableLayoutNGName[];
extern const char kEnableLayoutNGDescription[];

extern const char kEnableLayoutNGTableName[];
extern const char kEnableLayoutNGTableDescription[];

extern const char kEnableLazyFrameLoadingName[];
extern const char kEnableLazyFrameLoadingDescription[];

extern const char kEnableLazyImageLoadingName[];
extern const char kEnableLazyImageLoadingDescription[];

extern const char kEnableMediaSessionServiceName[];
extern const char kEnableMediaSessionServiceDescription[];

extern const char kEnableNetworkLoggingToFileName[];
extern const char kEnableNetworkLoggingToFileDescription[];

<<<<<<< HEAD
=======
extern const char kEnableNetworkServiceInProcessName[];
extern const char kEnableNetworkServiceInProcessDescription[];

extern const char kEnableTranslateSubFramesName[];
extern const char kEnableTranslateSubFramesDescription[];

>>>>>>> chromium
extern const char kEnableWindowsGamingInputDataFetcherName[];
extern const char kEnableWindowsGamingInputDataFetcherDescription[];

extern const char kBlockInsecurePrivateNetworkRequestsName[];
extern const char kBlockInsecurePrivateNetworkRequestsDescription[];

<<<<<<< HEAD
extern const char kPipDoubleTapToResizeName[];
extern const char kPipDoubleTapToResizeDescription[];

extern const char kPipTuckName[];
extern const char kPipTuckDescription[];

extern const char kPrivacyGuideAiSettingsName[];
extern const char kPrivacyGuideAiSettingsDescription[];

extern const char kPrivateNetworkAccessSendPreflightsName[];
extern const char kPrivateNetworkAccessSendPreflightsDescription[];

extern const char kPrivateNetworkAccessRespectPreflightResultsName[];
extern const char kPrivateNetworkAccessRespectPreflightResultsDescription[];

extern const char kPrivateNetworkAccessPreflightShortTimeoutName[];
extern const char kPrivateNetworkAccessPreflightShortTimeoutDescription[];

extern const char kPrivateNetworkAccessPermissionPromptName[];
extern const char kPrivateNetworkAccessPermissionPromptDescription[];

extern const char kPrivateNetworkAccessIgnoreWorkerErrorsName[];
extern const char kPrivateNetworkAccessIgnoreWorkerErrorsDescription[];

extern const char kPrivateNetworkAccessIgnoreNavigationErrorsName[];
extern const char kPrivateNetworkAccessIgnoreNavigationErrorsDescription[];
=======
extern const char kCrossOriginEmbedderPolicyCredentiallessName[];
extern const char kCrossOriginEmbedderPolicyCredentiallessDescription[];
>>>>>>> chromium

extern const char kDeprecateAltClickName[];
extern const char kDeprecateAltClickDescription[];

extern const char kDeprecateAltBasedSixPackName[];
extern const char kDeprecateAltBasedSixPackDescription[];

extern const char kDiagnosticsAppName[];
extern const char kDiagnosticsAppDescription[];

extern const char kDiagnosticsAppNavigationName[];
extern const char kDiagnosticsAppNavigationDescription[];

extern const char kDisableKeepaliveFetchName[];
extern const char kDisableKeepaliveFetchDescription[];

extern const char kMemlogName[];
extern const char kMemlogDescription[];
extern const char kMemlogModeMinimal[];
extern const char kMemlogModeAll[];
extern const char kMemlogModeAllRenderers[];
extern const char kMemlogModeBrowser[];
extern const char kMemlogModeGpu[];
extern const char kMemlogModeRendererSampling[];

extern const char kMemlogSamplingRateName[];
extern const char kMemlogSamplingRateDescription[];
extern const char kMemlogSamplingRate10KB[];
extern const char kMemlogSamplingRate50KB[];
extern const char kMemlogSamplingRate100KB[];
extern const char kMemlogSamplingRate500KB[];
extern const char kMemlogSamplingRate1MB[];
extern const char kMemlogSamplingRate5MB[];

extern const char kMemlogStackModeName[];
extern const char kMemlogStackModeDescription[];
extern const char kMemlogStackModeMixed[];
extern const char kMemlogStackModeNative[];
extern const char kMemlogStackModeNativeWithThreadNames[];
extern const char kMemlogStackModePseudo[];

extern const char kDownloadAutoResumptionNativeName[];
extern const char kDownloadAutoResumptionNativeDescription[];

extern const char kDownloadLaterName[];
extern const char kDownloadLaterDescription[];

extern const char kDownloadLaterDebugOnWifiName[];
extern const char kDownloadLaterDebugOnWifiNameDescription[];

extern const char kEnableExtendedSyncPromosCapabilityName[];
extern const char kEnableExtendedSyncPromosCapabilityDescription[];

extern const char kEnableFencedFramesName[];
extern const char kEnableFencedFramesDescription[];

extern const char kEnableGamepadButtonAxisEventsName[];
extern const char kEnableGamepadButtonAxisEventsDescription[];

extern const char kEnableLensRegionSearchFlagId[];
extern const char kEnableLensRegionSearchName[];
extern const char kEnableLensRegionSearchDescription[];

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
extern const char kEnableIsolatedWebAppsName[];
extern const char kEnableIsolatedWebAppsDescription[];

#if BUILDFLAG(IS_CHROMEOS)
extern const char kEnableIsolatedWebAppUnmanagedInstallName[];
extern const char kEnableIsolatedWebAppUnmanagedInstallDescription[];

extern const char kEnableIsolatedWebAppManagedGuestSessionInstallName[];
extern const char kEnableIsolatedWebAppManagedGuestSessionInstallDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS)

extern const char kEnableIsolatedWebAppDevModeName[];
extern const char kEnableIsolatedWebAppDevModeDescription[];

extern const char kEnableIwaKeyDistributionComponentName[];
extern const char kEnableIwaKeyDistributionComponentDescription[];

extern const char kIwaKeyDistributionComponentExpCohortName[];
extern const char kIwaKeyDistributionComponentExpCohortDescription[];
#endif  // !BUILDFLAG(IS_ANDROID)

extern const char kEnableControlledFrameName[];
extern const char kEnableControlledFrameDescription[];

extern const char kEnableFingerprintingProtectionBlocklistName[];
extern const char kEnableFingerprintingProtectionBlocklistDescription[];

extern const char kEnableFingerprintingProtectionBlocklistInIncognitoName[];
extern const char
    kEnableFingerprintingProtectionBlocklistInIncognitoDescription[];

extern const char kEnableLensStandaloneFlagId[];
extern const char kEnableLensStandaloneName[];
extern const char kEnableLensStandaloneDescription[];
=======
extern const char kEnableLoginDetectionName[];
extern const char kEnableLoginDetectionDescription[];
>>>>>>> chromium

extern const char kEnableManagedConfigurationWebApiName[];
extern const char kEnableManagedConfigurationWebApiDescription[];

extern const char kEnableNewDownloadBackendName[];
extern const char kEnableNewDownloadBackendDescription[];

<<<<<<< HEAD
extern const char kEnablePerfettoSystemTracingName[];
extern const char kEnablePerfettoSystemTracingDescription[];
=======
extern const char kEnablePciguardUiName[];
extern const char kEnablePciguardUiDescription[];

extern const char kEnablePenetratingImageSelectionName[];
extern const char kEnablePenetratingImageSelectionDescription[];
>>>>>>> chromium

extern const char kEnablePortalsName[];
extern const char kEnablePortalsDescription[];

extern const char kEnablePortalsCrossOriginName[];
extern const char kEnablePortalsCrossOriginDescription[];

extern const char kEnablePixelCanvasRecordingName[];
extern const char kEnablePixelCanvasRecordingDescription[];

extern const char kEnableShortcutCustomizationAppName[];
extern const char kEnableShortcutCustomizationAppDescription[];

<<<<<<< HEAD
extern const char kEnableSearchCustomizableShortcutsInLauncherName[];
extern const char kEnableSearchCustomizableShortcutsInLauncherDescription[];
=======
extern const char kEnableSRPIsolatedPrerendersName[];
extern const char kEnableSRPIsolatedPrerendersDescription[];

extern const char kEnableSRPIsolatedPrerenderProbingName[];
extern const char kEnableSRPIsolatedPrerenderProbingDescription[];
>>>>>>> chromium

extern const char kEnableSRPIsolatedPrerendersNSPName[];
extern const char kEnableSRPIsolatedPrerendersNSPDescription[];

extern const char kReduceHorizontalFlingVelocityName[];
extern const char kReduceHorizontalFlingVelocityDescription[];

extern const char kEnableResamplingInputEventsName[];
extern const char kEnableResamplingInputEventsDescription[];
extern const char kEnableResamplingScrollEventsName[];
extern const char kEnableResamplingScrollEventsDescription[];
extern const char kEnableResamplingScrollEventsExperimentalPredictionName[];
extern const char
    kEnableResamplingScrollEventsExperimentalPredictionDescription[];

extern const char kEnableRestrictedWebApisName[];
extern const char kEnableRestrictedWebApisDescription[];

extern const char kEnableSubresourceRedirectName[];
extern const char kEnableSubresourceRedirectDescription[];

extern const char kEnableUseZoomForDsfName[];
extern const char kEnableUseZoomForDsfDescription[];
extern const char kEnableUseZoomForDsfChoiceDefault[];
extern const char kEnableUseZoomForDsfChoiceEnabled[];
extern const char kEnableUseZoomForDsfChoiceDisabled[];

extern const char kEnableWebAuthenticationCableV2SupportName[];
extern const char kEnableWebAuthenticationCableV2SupportDescription[];

extern const char kEnableWebAuthenticationChromeOSAuthenticatorName[];
extern const char kEnableWebAuthenticationChromeOSAuthenticatorDescription[];

extern const char kExperimentalWebAssemblyFeaturesName[];
extern const char kExperimentalWebAssemblyFeaturesDescription[];

extern const char kEnableWasmBaselineName[];
extern const char kEnableWasmBaselineDescription[];

extern const char kEnableWasmLazyCompilationName[];
extern const char kEnableWasmLazyCompilationDescription[];

extern const char kEnableWasmSimdName[];
extern const char kEnableWasmSimdDescription[];

extern const char kEnableWasmTieringName[];
extern const char kEnableWasmTieringDescription[];

<<<<<<< HEAD
extern const char kExperimentalWebPlatformFeaturesName[];
extern const char kExperimentalWebPlatformFeaturesDescription[];

extern const char kSafeBrowsingLocalListsUseSBv5Name[];
extern const char kSafeBrowsingLocalListsUseSBv5Description[];

#if BUILDFLAG(ENABLE_EXTENSIONS)
extern const char kEnableWebHidInWebViewName[];
extern const char kEnableWebHidInWebViewDescription[];

extern const char kExperimentalOmniboxLabsName[];
extern const char kExperimentalOmniboxLabsDescription[];
extern const char kExtensionAiDataCollectionName[];
extern const char kExtensionAiDataCollectionDescription[];
extern const char kExtensionsMenuAccessControlName[];
extern const char kExtensionsMenuAccessControlDescription[];
extern const char kIPHExtensionsMenuFeatureName[];
extern const char kIPHExtensionsMenuFeatureDescription[];
extern const char kIPHExtensionsRequestAccessButtonFeatureName[];
extern const char kIPHExtensionsRequestAccessButtonFeatureDescription[];
extern const char kExtensionManifestV2DeprecationWarningName[];
extern const char kExtensionManifestV2DeprecationWarningDescription[];
extern const char kExtensionManifestV2DeprecationDisabledName[];
extern const char kExtensionManifestV2DeprecationDisabledDescription[];
extern const char kExtensionManifestV2DeprecationUnsupportedName[];
extern const char kExtensionManifestV2DeprecationUnsupportedDescription[];

extern const char kExtensionsToolbarZeroStateName[];
extern const char kExtensionsToolbarZeroStateDescription[];
extern const char kExtensionsToolbarZeroStateChoicesDisabled[];
extern const char kExtensionsToolbarZeroStateVistWebStore[];
extern const char kExtensionsToolbarZeroStateExploreExtensionsByCategory[];

extern const char kWebAuthFlowInBrowserTabName[];
extern const char kWebAuthFlowInBrowserTabDescription[];

extern const char kCWSInfoFastCheckName[];
extern const char kCWSInfoFastCheckDescription[];

extern const char kExtensionDisableUnsupportedDeveloperName[];
extern const char kExtensionDisableUnsupportedDeveloperDescription[];

extern const char kExtensionTelemetryForEnterpriseName[];
extern const char kExtensionTelemetryForEnterpriseDescription[];

#if BUILDFLAG(IS_CHROMEOS)
extern const char kExtensionWebFileHandlersName[];
extern const char kExtensionWebFileHandlersDescription[];
#endif  // IS_CHROMEOS
#endif  // ENABLE_EXTENSIONS
=======
extern const char kEvDetailsInPageInfoName[];
extern const char kEvDetailsInPageInfoDescription[];

extern const char kExpensiveBackgroundTimerThrottlingName[];
extern const char kExpensiveBackgroundTimerThrottlingDescription[];

extern const char kExperimentalAccessibilityLabelsName[];
extern const char kExperimentalAccessibilityLabelsDescription[];

extern const char kExperimentalWebPlatformFeaturesName[];
extern const char kExperimentalWebPlatformFeaturesDescription[];

extern const char kExtensionContentVerificationName[];
extern const char kExtensionContentVerificationDescription[];
extern const char kExtensionContentVerificationBootstrap[];
extern const char kExtensionContentVerificationEnforce[];
extern const char kExtensionContentVerificationEnforceStrict[];
>>>>>>> chromium

extern const char kExtensionsOnChromeUrlsName[];
extern const char kExtensionsOnChromeUrlsDescription[];

extern const char kFilteringScrollPredictionName[];
extern const char kFilteringScrollPredictionDescription[];

extern const char kFractionalScrollOffsetsName[];
extern const char kFractionalScrollOffsetsDescription[];

extern const char kForceEffectiveConnectionTypeName[];
extern const char kForceEffectiveConnectionTypeDescription[];
extern const char kEffectiveConnectionTypeUnknownDescription[];
extern const char kEffectiveConnectionTypeOfflineDescription[];
extern const char kEffectiveConnectionTypeSlow2GDescription[];
extern const char kEffectiveConnectionTypeSlow2GOnCellularDescription[];
extern const char kEffectiveConnectionType2GDescription[];
extern const char kEffectiveConnectionType3GDescription[];
extern const char kEffectiveConnectionType4GDescription[];

<<<<<<< HEAD
extern const char kFedCmButtonModeName[];
extern const char kFedCmButtonModeDescription[];

extern const char kFedCmDelegationName[];
extern const char kFedCmDelegationDescription[];

extern const char kFedCmIdPRegistrationName[];
extern const char kFedCmIdPRegistrationDescription[];

extern const char kFedCmLightweightModeName[];
extern const char kFedCmLightweightModeDescription[];

extern const char kFedCmMetricsEndpointName[];
extern const char kFedCmMetricsEndpointDescription[];

extern const char kFedCmMultiIdpName[];
extern const char kFedCmMultiIdpDescription[];

extern const char kFedCmSelectiveDisclosureName[];
extern const char kFedCmSelectiveDisclosureDescription[];

extern const char kFedCmShowFilteredAccountsName[];
extern const char kFedCmShowFilteredAccountsDescription[];

extern const char kFedCmUseOtherAccountName[];
extern const char kFedCmUseOtherAccountDescription[];

extern const char kFedCmWithStorageAccessAPIName[];
extern const char kFedCmWithStorageAccessAPIDescription[];

extern const char kFedCmWithoutWellKnownEnforcementName[];
extern const char kFedCmWithoutWellKnownEnforcementDescription[];

extern const char kWebIdentityDigitalCredentialsName[];
extern const char kWebIdentityDigitalCredentialsDescription[];
=======
extern const char kFileHandlingAPIName[];
extern const char kFileHandlingAPIDescription[];
>>>>>>> chromium

extern const char kWebIdentityDigitalCredentialsCreationName[];
extern const char kWebIdentityDigitalCredentialsCreationDescription[];

extern const char kFileHandlingIconsName[];
extern const char kFileHandlingIconsDescription[];

extern const char kFillingAcrossAffiliatedWebsitesName[];
extern const char kFillingAcrossAffiliatedWebsitesDescription[];

extern const char kFillOnAccountSelectName[];
extern const char kFillOnAccountSelectDescription[];

extern const char kForceTextDirectionName[];
extern const char kForceTextDirectionDescription[];
extern const char kForceDirectionLtr[];
extern const char kForceDirectionRtl[];

extern const char kForceUiDirectionName[];
extern const char kForceUiDirectionDescription[];

extern const char kGlobalMediaControlsName[];
extern const char kGlobalMediaControlsDescription[];

extern const char kGlobalMediaControlsForCastName[];
extern const char kGlobalMediaControlsForCastDescription[];

extern const char kGlobalMediaControlsForChromeOSName[];
extern const char kGlobalMediaControlsForChromeOSDescription[];

extern const char kGlobalMediaControlsPictureInPictureName[];
extern const char kGlobalMediaControlsPictureInPictureDescription[];

extern const char kGlobalMediaControlsSeamlessTransferName[];
extern const char kGlobalMediaControlsSeamlessTransferDescription[];

extern const char kGlobalMediaControlsModernUIName[];
extern const char kGlobalMediaControlsModernUIDescription[];

extern const char kGlobalMediaControlsOverlayControlsName[];
extern const char kGlobalMediaControlsOverlayControlsDescription[];

<<<<<<< HEAD
extern const char kCastMessageLoggingName[];
extern const char kCastMessageLoggingDescription[];

extern const char kCastStreamingAv1Name[];
extern const char kCastStreamingAv1Description[];

extern const char kCastStreamingHardwareH264Name[];
extern const char kCastStreamingHardwareH264Description[];

extern const char kCastStreamingHardwareVp8Name[];
extern const char kCastStreamingHardwareVp8Description[];

extern const char kCastStreamingHardwareVp9Name[];
extern const char kCastStreamingHardwareVp9Description[];

extern const char kCastStreamingMediaVideoEncoderName[];
extern const char kCastStreamingMediaVideoEncoderDescription[];

extern const char kCastStreamingPerformanceOverlayName[];
extern const char kCastStreamingPerformanceOverlayDescription[];

extern const char kCastStreamingVp8Name[];
extern const char kCastStreamingVp8Description[];

extern const char kCastStreamingVp9Name[];
extern const char kCastStreamingVp9Description[];

#if BUILDFLAG(IS_MAC)
extern const char kCastStreamingMacHardwareH264Name[];
extern const char kCastStreamingMacHardwareH264Description[];
extern const char kUseNetworkFrameworkForLocalDiscoveryName[];
extern const char kUseNetworkFrameworkForLocalDiscoveryDescription[];
#endif

#if BUILDFLAG(IS_WIN)
extern const char kCastStreamingWinHardwareH264Name[];
extern const char kCastStreamingWinHardwareH264Description[];
#endif

extern const char kCastEnableStreamingWithHiDPIName[];
extern const char kCastEnableStreamingWithHiDPIDescription[];

extern const char kContextualPageActionsName[];
extern const char kContextualPageActionsDescription[];

extern const char kContextualPageActionsPriceTrackingName[];
extern const char kContextualPageActionsPriceTrackingDescription[];

extern const char kContextualPageActionsReaderModeName[];
extern const char kContextualPageActionsReaderModeDescription[];

extern const char kContextualPageActionsShareModelName[];
extern const char kContextualPageActionsShareModelDescription[];

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
extern const char kEnableSearchAggregatorPolicyName[];
extern const char kEnableSearchAggregatorPolicyDescription[];
#endif

#if BUILDFLAG(IS_CHROMEOS)
extern const char kFlexFirmwareUpdateName[];
extern const char kFlexFirmwareUpdateDescription[];
#endif
=======
extern const char kGoogleLensSdkIntentName[];
extern const char kGoogleLensSdkIntentDescription[];
>>>>>>> chromium

extern const char kGpuRasterizationName[];
extern const char kGpuRasterizationDescription[];

<<<<<<< HEAD
extern const char kHappyEyeballsV3Name[];
extern const char kHappyEyeballsV3Description[];
=======
extern const char kHandwritingGestureEditingName[];
extern const char kHandwritingGestureEditingDescription[];
>>>>>>> chromium

extern const char kHardwareMediaKeyHandling[];
extern const char kHardwareMediaKeyHandlingDescription[];

extern const char kHeavyAdPrivacyMitigationsName[];
extern const char kHeavyAdPrivacyMitigationsDescription[];

extern const char kHeavyAdInterventionName[];
extern const char kHeavyAdInterventionDescription[];

<<<<<<< HEAD
extern const char kCrasProcessorWavDumpName[];
extern const char kCrasProcessorWavDumpDescription[];
=======
extern const char kTabSwitcherOnReturnName[];
extern const char kTabSwitcherOnReturnDescription[];

extern const char kHideShelfControlsInTabletModeName[];
extern const char kHideShelfControlsInTabletModeDescription[];
>>>>>>> chromium

extern const char kHostedAppShimCreationName[];
extern const char kHostedAppShimCreationDescription[];

extern const char kHttpsOnlyModeName[];
extern const char kHttpsOnlyModeDescription[];

extern const char kIgnoreGpuBlocklistName[];
extern const char kIgnoreGpuBlocklistDescription[];

<<<<<<< HEAD
extern const char kIncrementLocalSurfaceIdForMainframeSameDocNavigationName[];
extern const char
    kIncrementLocalSurfaceIdForMainframeSameDocNavigationDescription[];
=======
extern const char kImprovedCookieControlsName[];
extern const char kImprovedCookieControlsDescription[];

extern const char kImprovedCookieControlsForThirdPartyCookieBlockingName[];
extern const char
    kImprovedCookieControlsForThirdPartyCookieBlockingDescription[];

extern const char kImprovedKeyboardShortcutsName[];
extern const char kImprovedKeyboardShortcutsDescription[];

extern const char kCompositorThreadedScrollbarScrollingName[];
extern const char kCompositorThreadedScrollbarScrollingDescription[];

extern const char kImpulseScrollAnimationsName[];
extern const char kImpulseScrollAnimationsDescription[];

extern const char kIncognitoBrandConsistencyForAndroidName[];
extern const char kIncognitoBrandConsistencyForAndroidDescription[];

extern const char kIncognitoBrandConsistencyForDesktopName[];
extern const char kIncognitoBrandConsistencyForDesktopDescription[];

extern const char kIncognitoClearBrowsingDataDialogForDesktopName[];
extern const char kIncognitoClearBrowsingDataDialogForDesktopDescription[];

extern const char kUpdateHistoryEntryPointsInIncognitoName[];
extern const char kUpdateHistoryEntryPointsInIncognitoDescription[];
>>>>>>> chromium

extern const char kIncognitoScreenshotName[];
extern const char kIncognitoScreenshotDescription[];

extern const char kInheritNativeThemeFromParentWidgetName[];
extern const char kInheritNativeThemeFromParentWidgetDescription[];

extern const char kInProductHelpDemoModeChoiceName[];
extern const char kInProductHelpDemoModeChoiceDescription[];

extern const char kInstalledAppsInCbdName[];
extern const char kInstalledAppsInCbdDescription[];

extern const char kJavascriptHarmonyName[];
extern const char kJavascriptHarmonyDescription[];

extern const char kJavascriptHarmonyShippingName[];
extern const char kJavascriptHarmonyShippingDescription[];

extern const char kLegacyTLSEnforcedName[];
extern const char kLegacyTLSEnforcedDescription[];

<<<<<<< HEAD
extern const char kJumpStartOmniboxName[];
extern const char kJumpStartOmniboxDescription[];
=======
extern const char kLensCameraAssistedSearchName[];
extern const char kLensCameraAssistedSearchDescription[];

extern const char kLinkDoctorDeprecationAndroidName[];
extern const char kLinkDoctorDeprecationAndroidDescription[];

extern const char kLiteVideoName[];
extern const char kLiteVideoDescription[];
>>>>>>> chromium

extern const char kLiteVideoDownlinkBandwidthKbpsName[];
extern const char kLiteVideoDownlinkBandwidthKbpsDescription[];

<<<<<<< HEAD
extern const char kLanguageDetectionAPIName[];
extern const char kLanguageDetectionAPIDescription[];

extern const char kLegacyTechReportTopLevelUrlName[];
extern const char kLegacyTechReportTopLevelUrlDescription[];

extern const char kLensOverlayName[];
extern const char kLensOverlayDescription[];

extern const char kLensOverlayContextualSearchboxName[];
extern const char kLensOverlayContextualSearchboxDescription[];

extern const char kLensOverlayImageContextMenuActionsName[];
extern const char kLensOverlayImageContextMenuActionsDescription[];

extern const char kLensOverlaySidePanelOpenInNewTabName[];
extern const char kLensOverlaySidePanelOpenInNewTabDescription[];

extern const char kLensOverlayTranslateButtonName[];
extern const char kLensOverlayTranslateButtonDescription[];

extern const char kLensOverlayTranslateLanguagesName[];
extern const char kLensOverlayTranslateLanguagesDescription[];

extern const char kLensOverlayLatencyOptimizationsName[];
extern const char kLensOverlayLatencyOptimizationsDescription[];

extern const char kLensImageFormatOptimizationsName[];
extern const char kLensImageFormatOptimizationsDescription[];

extern const char kLinkedServicesSettingName[];
extern const char kLinkedServicesSettingDescription[];

extern const char kLensOnQuickActionSearchWidgetName[];
extern const char kLensOnQuickActionSearchWidgetDescription[];

extern const char kLocationBarModelOptimizationsName[];
extern const char kLocationBarModelOptimizationsDescription[];
=======
extern const char kLiteVideoForceOverrideDecisionName[];
extern const char kLiteVideoForceOverrideDecisionDescription[];
>>>>>>> chromium

extern const char kLogJsConsoleMessagesName[];
extern const char kLogJsConsoleMessagesDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
extern const char kLoginDbDeprecationAndroidName[];
extern const char kLoginDbDeprecationAndroidDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
extern const char kMantisFeatureKeyName[];
extern const char kMantisFeatureKeyDescription[];
#endif  // IS_CHROMEOS
=======
extern const char kMediaHistoryName[];
extern const char kMediaHistoryDescription[];
>>>>>>> chromium

extern const char kMediaRouterCastAllowAllIPsName[];
extern const char kMediaRouterCastAllowAllIPsDescription[];

extern const char kMediaSessionWebRTCName[];
extern const char kMediaSessionWebRTCDescription[];

extern const char kMemoriesName[];
extern const char kMemoriesDescription[];

extern const char kMemoriesDebugName[];
extern const char kMemoriesDebugDescription[];

extern const char kMetricsSettingsAndroidName[];
extern const char kMetricsSettingsAndroidDescription[];

extern const char kMixedFormsDisableAutofillName[];
extern const char kMixedFormsDisableAutofillDescription[];

extern const char kMixedFormsInterstitialName[];
extern const char kMixedFormsInterstitialDescription[];

extern const char kMobileIdentityConsistencyName[];
extern const char kMobileIdentityConsistencyDescription[];

extern const char kMobileIdentityConsistencyFREName[];
extern const char kMobileIdentityConsistencyFREDescription[];

extern const char kWipeDataOnChildAccountSigninName[];
extern const char kWipeDataOnChildAccountSigninDescription[];

extern const char kMobileIdentityConsistencyVarName[];
extern const char kMobileIdentityConsistencyVarDescription[];

extern const char kMobilePwaInstallUseBottomSheetName[];
extern const char kMobilePwaInstallUseBottomSheetDescription[];

extern const char kMojoLinuxChannelSharedMemName[];
extern const char kMojoLinuxChannelSharedMemDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
extern const char kMostVisitedTilesCustomizationName[];
extern const char kMostVisitedTilesCustomizationDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

extern const char kMostVisitedTilesNewScoringName[];
extern const char kMostVisitedTilesNewScoringDescription[];
=======
extern const char kMouseSubframeNoImplicitCaptureName[];
extern const char kMouseSubframeNoImplicitCaptureDescription[];
>>>>>>> chromium

extern const char kMutingCompromisedCredentialsName[];
extern const char kMutingCompromisedCredentialsDescription[];

<<<<<<< HEAD
extern const char kUsernameFirstFlowWithIntermediateValuesPredictionsName[];
extern const char
    kUsernameFirstFlowWithIntermediateValuesPredictionsDescription[];

extern const char kUsernameFirstFlowWithIntermediateValuesVotingName[];
extern const char kUsernameFirstFlowWithIntermediateValuesVotingDescription[];
=======
extern const char kUsernameFirstFlowName[];
extern const char kUsernameFirstFlowDescription[];

extern const char kUsernameFirstFlowFillingName[];
extern const char kUsernameFirstFlowFillingDescription[];
>>>>>>> chromium

extern const char kCanvas2DLayersName[];
extern const char kCanvas2DLayersDescription[];

extern const char kNewCanvas2DAPIName[];
extern const char kNewCanvas2DAPIDescription[];

extern const char kSignInProfileCreationName[];
extern const char kSignInProfileCreationDescription[];

extern const char kSignInProfileCreationEnterpriseName[];
extern const char kSignInProfileCreationEnterpriseDescription[];

extern const char kSyncingCompromisedCredentialsName[];
extern const char kSyncingCompromisedCredentialsDescription[];

extern const char kDestroyProfileOnBrowserCloseName[];
extern const char kDestroyProfileOnBrowserCloseDescription[];

extern const char kNewUsbBackendName[];
extern const char kNewUsbBackendDescription[];

extern const char kNewTabstripAnimationName[];
extern const char kNewTabstripAnimationDescription[];

extern const char kNotificationIndicatorName[];
extern const char kNotificationIndicatorDescription[];

extern const char kNotificationSchedulerName[];
extern const char kNotificationSchedulerDescription[];

extern const char kNotificationSchedulerDebugOptionName[];
extern const char kNotificationSchedulerDebugOptionDescription[];
extern const char kNotificationSchedulerImmediateBackgroundTaskDescription[];

extern const char kNotificationsSystemFlagName[];
extern const char kNotificationsSystemFlagDescription[];

<<<<<<< HEAD
extern const char kOrganicRepeatableQueriesName[];
extern const char kOrganicRepeatableQueriesDescription[];

extern const char kOriginAgentClusterDefaultName[];
extern const char kOriginAgentClusterDefaultDescription[];

extern const char kOriginKeyedProcessesByDefaultName[];
extern const char kOriginKeyedProcessesByDefaultDescription[];

extern const char kOmitCorsClientCertName[];
extern const char kOmitCorsClientCertDescription[];
=======
extern const char kOmniboxActiveSearchEnginesName[];
extern const char kOmniboxActiveSearchEnginesDescription[];
>>>>>>> chromium

extern const char kOmniboxAdaptiveSuggestionsCountName[];
extern const char kOmniboxAdaptiveSuggestionsCountDescription[];

extern const char kOmniboxAssistantVoiceSearchName[];
extern const char kOmniboxAssistantVoiceSearchDescription[];

extern const char kOmniboxBookmarkPathsName[];
extern const char kOmniboxBookmarkPathsDescription[];

extern const char kOmniboxClobberTriggersContextualWebZeroSuggestName[];
extern const char kOmniboxClobberTriggersContextualWebZeroSuggestDescription[];

extern const char kOmniboxCompactSuggestionsName[];
extern const char kOmniboxCompactSuggestionsDescription[];

extern const char kOmniboxDisableCGIParamMatchingName[];
extern const char kOmniboxDisableCGIParamMatchingDescription[];

extern const char kOmniboxDefaultTypedNavigationsToHttpsName[];
extern const char kOmniboxDefaultTypedNavigationsToHttpsDescription[];

extern const char kOmniboxKeywordSpaceTriggeringSettingName[];
extern const char kOmniboxKeywordSpaceTriggeringSettingDescription[];

extern const char kOmniboxExperimentalSuggestScoringName[];
extern const char kOmniboxExperimentalSuggestScoringDescription[];

<<<<<<< HEAD
extern const char kOmniboxMlUrlPiecewiseMappedSearchBlendingName[];
extern const char kOmniboxMlUrlPiecewiseMappedSearchBlendingDescription[];

extern const char kOmniboxMlUrlScoreCachingName[];
extern const char kOmniboxMlUrlScoreCachingDescription[];

extern const char kOmniboxMlUrlScoringName[];
extern const char kOmniboxMlUrlScoringDescription[];

extern const char kOmniboxMlUrlScoringModelName[];
extern const char kOmniboxMlUrlScoringModelDescription[];

extern const char kOmniboxMlUrlSearchBlendingName[];
extern const char kOmniboxMlUrlSearchBlendingDescription[];

extern const char kOmniboxMostVisitedTilesHorizontalRenderGroupName[];
extern const char kOmniboxMostVisitedTilesHorizontalRenderGroupDescription[];

extern const char kOmniboxMostVisitedTilesTitleWrapAroundName[];
extern const char kOmniboxMostVisitedTilesTitleWrapAroundDescription[];

extern const char kOmniboxOnDeviceHeadSuggestionsName[];
extern const char kOmniboxOnDeviceHeadSuggestionsDescription[];

extern const char kOmniboxOnDeviceHeadSuggestionsIncognitoName[];
extern const char kOmniboxOnDeviceHeadSuggestionsIncognitoDescription[];

extern const char kOmniboxOnDeviceTailSuggestionsName[];
extern const char kOmniboxOnDeviceTailSuggestionsDescription[];

extern const char kOmniboxSuppressClipboardSuggestionAfterFirstUsedName[];
extern const char
    kOmniboxSuppressClipboardSuggestionAfterFirstUsedDescription[];
=======
extern const char kOmniboxMostVisitedTilesName[];
extern const char kOmniboxMostVisitedTilesDescription[];
>>>>>>> chromium

extern const char kOmniboxRichAutocompletionName[];
extern const char kOmniboxRichAutocompletionDescription[];
extern const char kOmniboxRichAutocompletionMinCharName[];
extern const char kOmniboxRichAutocompletionMinCharDescription[];
extern const char kOmniboxRichAutocompletionShowAdditionalTextName[];
extern const char kOmniboxRichAutocompletionShowAdditionalTextDescription[];
extern const char kOmniboxRichAutocompletionSplitName[];
extern const char kOmniboxRichAutocompletionSplitDescription[];
extern const char kOmniboxRichAutocompletionPreferUrlsOverPrefixesName[];
extern const char kOmniboxRichAutocompletionPreferUrlsOverPrefixesDescription[];
extern const char kOmniboxRichAutocompletionPromisingName[];
extern const char kOmniboxRichAutocompletionPromisingDescription[];

extern const char kOmniboxRichEntitiesInLauncherName[];
extern const char kOmniboxRichEntitiesInLauncherDescription[];

extern const char kOmniboxOnFocusSuggestionsContextualWebAllowSRPName[];
extern const char kOmniboxOnFocusSuggestionsContextualWebAllowSRPDescription[];

extern const char kOmniboxOnFocusSuggestionsContextualWebName[];
extern const char kOmniboxOnFocusSuggestionsContextualWebDescription[];

extern const char kOmniboxShortBookmarkSuggestionsName[];
extern const char kOmniboxShortBookmarkSuggestionsDescription[];

extern const char kOmniboxSpareRendererName[];
extern const char kOmniboxSpareRendererDescription[];

extern const char kOmniboxTabSwitchSuggestionsName[];
extern const char kOmniboxTabSwitchSuggestionsDescription[];

<<<<<<< HEAD
extern const char kOmniboxFocusTriggersWebAndSRPZeroSuggestName[];
extern const char kOmniboxFocusTriggersWebAndSRPZeroSuggestDescription[];

extern const char kOmniboxZeroSuggestPrefetchDebouncingName[];
extern const char kOmniboxZeroSuggestPrefetchDebouncingDescription[];
=======
extern const char kOmniboxTrendingZeroPrefixSuggestionsOnNTPName[];
extern const char kOmniboxTrendingZeroPrefixSuggestionsOnNTPDescription[];
>>>>>>> chromium

extern const char kOmniboxUIHideSteadyStateUrlSchemeName[];
extern const char kOmniboxUIHideSteadyStateUrlSchemeDescription[];

extern const char kOmniboxUIHideSteadyStateUrlTrivialSubdomainsName[];
extern const char kOmniboxUIHideSteadyStateUrlTrivialSubdomainsDescription[];

extern const char kOmniboxUIRevealSteadyStateUrlPathQueryAndRefOnHoverName[];
extern const char
    kOmniboxUIRevealSteadyStateUrlPathQueryAndRefOnHoverDescription[];

extern const char
    kOmniboxUIHideSteadyStateUrlPathQueryAndRefOnInteractionName[];
extern const char
    kOmniboxUIHideSteadyStateUrlPathQueryAndRefOnInteractionDescription[];

extern const char kOmniboxUIMaybeElideToRegistrableDomainName[];
extern const char kOmniboxUIMaybeElideToRegistrableDomainDescription[];

extern const char kOmniboxMaxZeroSuggestMatchesName[];
extern const char kOmniboxMaxZeroSuggestMatchesDescription[];

extern const char kOmniboxUIMaxAutocompleteMatchesName[];
extern const char kOmniboxUIMaxAutocompleteMatchesDescription[];

extern const char kOmniboxUpdatedConnectionSecurityIndicatorsName[];
extern const char kOmniboxUpdatedConnectionSecurityIndicatorsDescription[];

extern const char kOmniboxMaxURLMatchesName[];
extern const char kOmniboxMaxURLMatchesDescription[];

extern const char kOmniboxDynamicMaxAutocompleteName[];
extern const char kOmniboxDynamicMaxAutocompleteDescription[];

extern const char kOmniboxOnDeviceHeadSuggestionsIncognitoName[];
extern const char kOmniboxOnDeviceHeadSuggestionsIncognitoDescription[];

extern const char kOmniboxOnDeviceHeadSuggestionsNonIncognitoName[];
extern const char kOmniboxOnDeviceHeadSuggestionsNonIncognitoDescription[];

extern const char kOmniboxWebUIOmniboxPopupName[];
extern const char kOmniboxWebUIOmniboxPopupDescription[];

extern const char kEnableSearchPrefetchName[];
extern const char kEnableSearchPrefetchDescription[];

extern const char kOopRasterizationName[];
extern const char kOopRasterizationDescription[];

extern const char kOopRasterizationDDLName[];
extern const char kOopRasterizationDDLDescription[];

extern const char kOptimizationGuideModelDownloadingName[];
extern const char kOptimizationGuideModelDownloadingDescription[];

extern const char kOptimizationGuideModelPushNotificationName[];
extern const char kOptimizationGuideModelPushNotificationDescription[];

extern const char kOsSettingsAppNotificationsPageName[];
extern const char kOsSettingsAppNotificationsPageDescription[];

extern const char kOsSettingsDeepLinkingName[];
extern const char kOsSettingsDeepLinkingDescription[];

<<<<<<< HEAD
=======
extern const char kOverviewButtonName[];
extern const char kOverviewButtonDescription[];

extern const char kEnableDeJellyName[];
extern const char kEnableDeJellyDescription[];

>>>>>>> chromium
extern const char kOverlayScrollbarsName[];
extern const char kOverlayScrollbarsDescription[];

extern const char kOverlayStrategiesName[];
extern const char kOverlayStrategiesDescription[];
extern const char kOverlayStrategiesDefault[];
extern const char kOverlayStrategiesNone[];
extern const char kOverlayStrategiesUnoccludedFullscreen[];
extern const char kOverlayStrategiesUnoccluded[];
extern const char kOverlayStrategiesOccludedAndUnoccluded[];

extern const char kOverrideLanguagePrefsForHrefTranslateName[];
extern const char kOverrideLanguagePrefsForHrefTranslateDescription[];
extern const char kOverrideSitePrefsForHrefTranslateName[];
extern const char kOverrideSitePrefsForHrefTranslateDescription[];
extern const char kOverrideUnsupportedPageLanguageForHrefTranslateName[];
extern const char kOverrideUnsupportedPageLanguageForHrefTranslateDescription[];
extern const char kOverrideSimilarLanguagesForHrefTranslateName[];
extern const char kOverrideSimilarLanguagesForHrefTranslateDescription[];

extern const char kUpdateHoverAtBeginFrameName[];
extern const char kUpdateHoverAtBeginFrameDescription[];

extern const char kOverscrollHistoryNavigationName[];
extern const char kOverscrollHistoryNavigationDescription[];

<<<<<<< HEAD
extern const char kPageContentAnnotationsName[];
extern const char kPageContentAnnotationsDescription[];

extern const char kPageEmbeddedPermissionControlName[];
extern const char kPageEmbeddedPermissionControlDescription[];

extern const char kPageContentAnnotationsPersistSalientImageMetadataName[];
extern const char
    kPageContentAnnotationsPersistSalientImageMetadataDescription[];

extern const char kPageContentAnnotationsRemotePageMetadataName[];
extern const char kPageContentAnnotationsRemotePageMetadataDescription[];

extern const char kPageImageServiceOptimizationGuideSalientImagesName[];
extern const char kPageImageServiceOptimizationGuideSalientImagesDescription[];

extern const char kPageImageServiceSuggestPoweredImagesName[];
extern const char kPageImageServiceSuggestPoweredImagesDescription[];

extern const char kPageInfoAboutThisPagePersistentEntryName[];
extern const char kPageInfoAboutThisPagePersistentEntryDescription[];

extern const char kPageInfoCookiesSubpageName[];
extern const char kPageInfoCookiesSubpageDescription[];

extern const char kPageInfoHideSiteSettingsName[];
extern const char kPageInfoHideSiteSettingsDescription[];

extern const char kPageInfoHistoryDesktopName[];
extern const char kPageInfoHistoryDesktopDescription[];

extern const char kPageVisibilityPageContentAnnotationsName[];
extern const char kPageVisibilityPageContentAnnotationsDescription[];
=======
extern const char kPageInfoV2DesktopName[];
extern const char kPageInfoV2DesktopDescription[];
>>>>>>> chromium

extern const char kParallelDownloadingName[];
extern const char kParallelDownloadingDescription[];

extern const char kPasswordChangeInSettingsName[];
extern const char kPasswordChangeInSettingsDescription[];

extern const char kPasswordChangeName[];
extern const char kPasswordChangeDescription[];

extern const char kPassiveEventListenersDueToFlingName[];
extern const char kPassiveEventListenersDueToFlingDescription[];

extern const char kPassiveDocumentEventListenersName[];
extern const char kPassiveDocumentEventListenersDescription[];

extern const char kPassiveDocumentWheelEventListenersName[];
extern const char kPassiveDocumentWheelEventListenersDescription[];

extern const char kPasswordImportName[];
extern const char kPasswordImportDescription[];

extern const char kPasswordScriptsFetchingName[];
extern const char kPasswordScriptsFetchingDescription[];

extern const char kPdfUnseasonedName[];
extern const char kPdfUnseasonedDescription[];

extern const char kPdfXfaFormsName[];
extern const char kPdfXfaFormsDescription[];

extern const char kForceWebContentsDarkModeName[];
extern const char kForceWebContentsDarkModeDescription[];

extern const char kForcedColorsName[];
extern const char kForcedColorsDescription[];

<<<<<<< HEAD
extern const char kImprovedSemanticsActivityIndicatorsName[];
extern const char kImprovedSemanticsActivityIndicatorsDescription[];
=======
extern const char kPercentBasedScrollingName[];
extern const char kPercentBasedScrollingDescription[];

extern const char kPermissionChipName[];
extern const char kPermissionChipDescription[];
>>>>>>> chromium

extern const char kPermissionChipGestureSensitiveName[];
extern const char kPermissionChipGestureSensitiveDescription[];

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
extern const char kMerchantTrustName[];
extern const char kMerchantTrustDescription[];
extern const char kPrivacyPolicyInsightsName[];
extern const char kPrivacyPolicyInsightsDescription[];
#endif

#if BUILDFLAG(IS_CHROMEOS)
extern const char kCrosSystemLevelPermissionBlockedWarningsName[];
extern const char kCrosSystemLevelPermissionBlockedWarningsDescription[];
#endif

extern const char kPerformanceInterventionUiName[];
extern const char kPerformanceInterventionUiDescription[];

extern const char kPerformanceInterventionDemoModeName[];
extern const char kPerformanceInterventionDemoModeDescription[];
=======
extern const char kPermissionChipRequestTypeSensitiveName[];
extern const char kPermissionChipRequestTypeSensitiveDescription[];
>>>>>>> chromium

extern const char kPermissionsAIv1Name[];
extern const char kPermissionsAIv1Description[];

<<<<<<< HEAD
extern const char kPermissionSiteSettingsRadioButtonName[];
extern const char kPermissionSiteSettingsRadioButtonDescription[];
=======
extern const char kPermissionQuietChipName[];
extern const char kPermissionQuietChipDescription[];
>>>>>>> chromium

extern const char kPlaybackSpeedButtonName[];
extern const char kPlaybackSpeedButtonDescription[];

<<<<<<< HEAD
extern const char kShowWarningsForSuspiciousNotificationsName[];
extern const char kShowWarningsForSuspiciousNotificationsDescription[];

extern const char kPowerBookmarkBackendName[];
extern const char kPowerBookmarkBackendDescription[];

extern const char kSpeculationRulesPrerenderingTargetHintName[];
extern const char kSpeculationRulesPrerenderingTargetHintDescription[];

extern const char kSubframeProcessReuseThresholds[];
extern const char kSubframeProcessReuseThresholdsDescription[];

extern const char kSupportSearchSuggestionForPrerender2Name[];
extern const char kSupportSearchSuggestionForPrerender2Description[];

extern const char kPrerender2EarlyDocumentLifecycleUpdateName[];
extern const char kPrerender2EarlyDocumentLifecycleUpdateDescription[];

extern const char kWarmUpCompositorName[];
extern const char kWarmUpCompositorDescription[];

extern const char kPrerender2WarmUpCompositorName[];
extern const char kPrerender2WarmUpCompositorDescription[];

extern const char kPrerender2ForNewTabPageAndroidName[];
extern const char kPrerender2ForNewTabPageAndroidDescription[];

extern const char kEnableOmniboxSearchPrefetchName[];
extern const char kEnableOmniboxSearchPrefetchDescription[];

extern const char kEnableOmniboxClientSearchPrefetchName[];
extern const char kEnableOmniboxClientSearchPrefetchDescription[];

extern const char kPreloadingOnPerformancePageName[];
extern const char kPreloadingOnPerformancePageDescription[];
=======
extern const char kPointerLockOptionsName[];
extern const char kPointerLockOptionsDescription[];
>>>>>>> chromium

extern const char kPrerender2Name[];
extern const char kPrerender2Description[];

<<<<<<< HEAD
extern const char kPriceChangeModuleName[];
extern const char kPriceChangeModuleDescription[];
=======
extern const char kPrivacyAdvisorName[];
extern const char kPrivacyAdvisorDescription[];

extern const char kPrivacyReviewName[];
extern const char kPrivacyReviewDescription[];
>>>>>>> chromium

extern const char kPrivacySandboxSettingsName[];
extern const char kPrivacySandboxSettingsDescription[];

<<<<<<< HEAD
extern const char kPrivacySandboxAdsApiUxEnhancementsName[];
extern const char kPrivacySandboxAdsApiUxEnhancementsDescription[];

extern const char kPrivacySandboxEnrollmentOverridesName[];
extern const char kPrivacySandboxEnrollmentOverridesDescription[];

extern const char kPrivacySandboxEqualizedPromptButtonsName[];
extern const char kPrivacySandboxEqualizedPromptButtonsDescription[];

extern const char kPrivacySandboxInternalsName[];
extern const char kPrivacySandboxInternalsDescription[];
=======
extern const char kPrivacySandboxSettings2Name[];
extern const char kPrivacySandboxSettings2Description[];

extern const char kSafetyCheckWeakPasswordsName[];
extern const char kSafetyCheckWeakPasswordsDescription[];
>>>>>>> chromium

extern const char kProminentDarkModeActiveTabTitleName[];
extern const char kProminentDarkModeActiveTabTitleDescription[];

extern const char kPromoBrowserCommandsName[];
extern const char kPromoBrowserCommandsDescription[];

extern const char kPullToRefreshName[];
extern const char kPullToRefreshDescription[];
extern const char kPullToRefreshEnabledTouchscreen[];

extern const char kPwaUpdateDialogForNameAndIconName[];
extern const char kPwaUpdateDialogForNameAndIconDescription[];

extern const char kQuicName[];
extern const char kQuicDescription[];

extern const char kQuickActionSearchWidgetAndroidName[];
extern const char kQuickActionSearchWidgetAndroidDescription[];

<<<<<<< HEAD
extern const char kQuickDimName[];
extern const char kQuickDimDescription[];

extern const char kQuickDeleteAndroidSurveyName[];
extern const char kQuickDeleteAndroidSurveyDescription[];

extern const char kQuickShareV2Name[];
extern const char kQuickShareV2Description[];

extern const char kSendTabToSelfIOSPushNotificationsName[];
extern const char kSendTabToSelfIOSPushNotificationsDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kSensitiveContentName[];
extern const char kSensitiveContentDescription[];

extern const char kSensitiveContentWhileSwitchingTabsName[];
extern const char kSensitiveContentWhileSwitchingTabsDescription[];
#endif  // BUILDFLAG(IS_ANDROID)
=======
extern const char kQuietNotificationPromptsName[];
extern const char kQuietNotificationPromptsDescription[];
>>>>>>> chromium

extern const char kSettingsAppNotificationSettingsName[];
extern const char kSettingsAppNotificationSettingsDescription[];

extern const char kAbusiveNotificationPermissionRevocationName[];
extern const char kAbusiveNotificationPermissionRevocationDescription[];

extern const char kContentSettingsRedesignName[];
extern const char kContentSettingsRedesignDescription[];

extern const char kRawClipboardName[];
extern const char kRawClipboardDescription[];

extern const char kReadLaterFlagId[];
extern const char kReadLaterName[];
extern const char kReadLaterDescription[];

extern const char kReadLaterNewBadgePromoName[];
extern const char kReadLaterNewBadgePromoDescription[];

extern const char kRecordWebAppDebugInfoName[];
extern const char kRecordWebAppDebugInfoDescription[];

<<<<<<< HEAD
#if BUILDFLAG(IS_MAC)
extern const char kReduceIPAddressChangeNotificationName[];
extern const char kReduceIPAddressChangeNotificationDescription[];
#endif  // BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_ANDROID)
extern const char kReplaceSyncPromosWithSignInPromosName[];
extern const char kReplaceSyncPromosWithSignInPromosDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
extern const char kRetainOmniboxOnFocusName[];
extern const char kRetainOmniboxOnFocusDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

extern const char kRoundedWindows[];
extern const char kRoundedWindowsDescription[];

extern const char kRubyShortHeuristicsName[];
extern const char kRubyShortHeuristicsDescription[];
=======
extern const char kReduceUserAgentName[];
extern const char kReduceUserAgentDescription[];

extern const char kRestrictGamepadAccessName[];
extern const char kRestrictGamepadAccessDescription[];
>>>>>>> chromium

extern const char kMBIModeName[];
extern const char kMBIModeDescription[];

extern const char kIntensiveWakeUpThrottlingName[];
extern const char kIntensiveWakeUpThrottlingDescription[];

extern const char kSafetyTipName[];
extern const char kSafetyTipDescription[];

extern const char kSamePartyCookiesConsideredFirstPartyName[];
extern const char kSamePartyCookiesConsideredFirstPartyDescription[];

extern const char kSchemefulSameSiteName[];
extern const char kSchemefulSameSiteDescription[];

<<<<<<< HEAD
extern const char kSafetyHubFollowupName[];
extern const char kSafetyHubFollowupDescription[];

extern const char kSafetyHubAndroidSurveyName[];
extern const char kSafetyHubAndroidSurveyDescription[];

extern const char kSafetyHubAndroidSurveyV2Name[];
extern const char kSafetyHubAndroidSurveyV2Description[];

extern const char kSafetyHubWeakAndReusedPasswordsName[];
extern const char kSafetyHubWeakAndReusedPasswordsDescription[];
#else
extern const char kSafetyHubHaTSOneOffSurveyName[];
extern const char kSafetyHubHaTSOneOffSurveyDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

extern const char kSafetyHubAbusiveNotificationRevocationName[];
extern const char kSafetyHubAbusiveNotificationRevocationDescription[];

#if !BUILDFLAG(IS_ANDROID)
extern const char kSafetyHubServicesOnStartUpName[];
extern const char kSafetyHubServicesOnStartUpDescription[];
#endif  // !BUILDFLAG(IS_ANDROID)

extern const char kSameAppWindowCycleName[];
extern const char kSameAppWindowCycleDescription[];

extern const char kTestThirdPartyCookiePhaseoutName[];
extern const char kTestThirdPartyCookiePhaseoutDescription[];
=======
extern const char kScreenCaptureTestName[];
extern const char kScreenCaptureTestDescription[];
>>>>>>> chromium

extern const char kScrollableTabStripFlagId[];
extern const char kScrollableTabStripName[];
extern const char kScrollableTabStripDescription[];

<<<<<<< HEAD
extern const char kTabstripComboButtonFlagId[];
extern const char kTabstripComboButtonName[];
extern const char kTabstripComboButtonDescription[];
=======
extern const char kScrollableTabStripButtonsName[];
extern const char kScrollableTabStripButtonsDescription[];

extern const char kScrollUnificationName[];
extern const char kScrollUnificationDescription[];
>>>>>>> chromium

extern const char kSearchHistoryLinkName[];
extern const char kSearchHistoryLinkDescription[];

extern const char kSecurePaymentConfirmationBrowserBoundKeysName[];
extern const char kSecurePaymentConfirmationBrowserBoundKeysDescription[];

extern const char kSecurePaymentConfirmationDebugName[];
extern const char kSecurePaymentConfirmationDebugDescription[];

extern const char kSendTabToSelfWhenSignedInName[];
extern const char kSendTabToSelfWhenSignedInDescription[];

extern const char kSendTabToSelfV2Name[];
extern const char kSendTabToSelfV2Description[];

extern const char kSidePanelFlagId[];
extern const char kSidePanelName[];
extern const char kSidePanelDescription[];

extern const char kServiceWorkerSubresourceFilterName[];
extern const char kServiceWorkerSubresourceFilterDescription[];

extern const char kSharedClipboardUIName[];
extern const char kSharedClipboardUIDescription[];

extern const char kSharingHubDesktopAppMenuName[];
extern const char kSharingHubDesktopAppMenuDescription[];

extern const char kSharingHubDesktopOmniboxName[];
extern const char kSharingHubDesktopOmniboxDescription[];

extern const char kSharingPeerConnectionReceiverName[];
extern const char kSharingPeerConnectionReceiverDescription[];

extern const char kSharingPeerConnectionSenderName[];
extern const char kSharingPeerConnectionSenderDescription[];

extern const char kSharingPreferVapidName[];
extern const char kSharingPreferVapidDescription[];

extern const char kSharingSendViaSyncName[];
extern const char kSharingSendViaSyncDescription[];

extern const char kShelfDragToPinName[];
extern const char kShelfDragToPinDescription[];

extern const char kShelfHoverPreviewsName[];
extern const char kShelfHoverPreviewsDescription[];

extern const char kShowAutofillSignaturesName[];
extern const char kShowAutofillSignaturesDescription[];

extern const char kShowAutofillTypePredictionsName[];
extern const char kShowAutofillTypePredictionsDescription[];

extern const char kShowPerformanceMetricsHudName[];
extern const char kShowPerformanceMetricsHudDescription[];

extern const char kShowOverdrawFeedbackName[];
extern const char kShowOverdrawFeedbackDescription[];

<<<<<<< HEAD
#if !BUILDFLAG(IS_CHROMEOS)
extern const char kFeedbackIncludeVariationsName[];
extern const char kFeedbackIncludeVariationsDescription[];
#endif

extern const char kSidePanelResizingFlagId[];
extern const char kSidePanelResizingName[];
extern const char kSidePanelResizingDescription[];

extern const char kSiteInstanceGroupsForDataUrlsName[];
extern const char kSiteInstanceGroupsForDataUrlsDescription[];

extern const char kDefaultSiteInstanceGroupsName[];
extern const char kDefaultSiteInstanceGroupsDescription[];

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
extern const char kPwaNavigationCapturingName[];
extern const char kPwaNavigationCapturingDescription[];
#endif

=======
>>>>>>> chromium
extern const char kSkiaRendererName[];
extern const char kSkiaRendererDescription[];

extern const char kStorageAccessAPIName[];
extern const char kStorageAccessAPIDescription[];

extern const char kIsolateOriginsName[];
extern const char kIsolateOriginsDescription[];

extern const char kIsolationByDefaultName[];
extern const char kIsolationByDefaultDescription[];

extern const char kSignatureBasedSriName[];
extern const char kSignatureBasedSriDescription[];

extern const char kSiteIsolationOptOutName[];
extern const char kSiteIsolationOptOutDescription[];
extern const char kSiteIsolationOptOutChoiceDefault[];
extern const char kSiteIsolationOptOutChoiceOptOut[];

extern const char kSmoothScrollingName[];
extern const char kSmoothScrollingDescription[];

<<<<<<< HEAD
extern const char kStorageAccessApiFollowsSameOriginPolicyName[];
extern const char kStorageAccessApiFollowsSameOriginPolicyDescription[];

extern const char kStorageAccessHeadersName[];
extern const char kStorageAccessHeadersDescription[];
=======
extern const char kWebOTPCrossDeviceName[];
extern const char kWebOTPCrossDeviceDescription[];

extern const char kSplitCacheByNetworkIsolationKeyName[];
extern const char kSplitCacheByNetworkIsolationKeyDescription[];

extern const char kStoragePressureEventName[];
extern const char kStoragePressureEventDescription[];

extern const char kStoreHoursAndroidName[];
extern const char kStoreHoursAndroidDescription[];

extern const char kStrictExtensionIsolationName[];
extern const char kStrictExtensionIsolationDescription[];
>>>>>>> chromium

extern const char kStrictOriginIsolationName[];
extern const char kStrictOriginIsolationDescription[];

<<<<<<< HEAD
extern const char kSupportToolScreenshot[];
extern const char kSupportToolScreenshotDescription[];

extern const char kSuppressToolbarCapturesName[];
extern const char kSuppressToolbarCapturesDescription[];
=======
extern const char kStylusBatteryStatusName[];
extern const char kStylusBatteryStatusDescription[];

extern const char kSubframeShutdownDelayName[];
extern const char kSubframeShutdownDelayDescription[];
>>>>>>> chromium

extern const char kSystemKeyboardLockName[];
extern const char kSystemKeyboardLockDescription[];

extern const char kSuggestionsWithSubStringMatchName[];
extern const char kSuggestionsWithSubStringMatchDescription[];

extern const char kSyncAutofillWalletOfferDataName[];
extern const char kSyncAutofillWalletOfferDataDescription[];

extern const char kSyncSandboxName[];
extern const char kSyncSandboxDescription[];

extern const char kSyncTrustedVaultPassphrasePromoName[];
extern const char kSyncTrustedVaultPassphrasePromoDescription[];

extern const char kSyncTrustedVaultPassphraseRecoveryName[];
extern const char kSyncTrustedVaultPassphraseRecoveryDescription[];

extern const char kSystemProxyForSystemServicesName[];
extern const char kSystemProxyForSystemServicesDescription[];

extern const char kTabEngagementReportingName[];
extern const char kTabEngagementReportingDescription[];

extern const char kTabGridLayoutAndroidName[];
extern const char kTabGridLayoutAndroidDescription[];

extern const char kCommerceMerchantViewerAndroidName[];
extern const char kCommerceMerchantViewerAndroidDescription[];

extern const char kCommercePriceTrackingAndroidName[];
extern const char kCommercePriceTrackingAndroidDescription[];

<<<<<<< HEAD
extern const char kTabGroupsDeferRemoteNavigationsId[];
extern const char kTabGroupsDeferRemoteNavigationsName[];
extern const char kTabGroupsDeferRemoteNavigationsDescription[];

extern const char kTabGroupsSaveV2Id[];
extern const char kTabGroupsSaveV2Name[];
extern const char kTabGroupsSaveV2Description[];

extern const char kTabGroupSyncServiceDesktopMigrationId[];
extern const char kTabGroupSyncServiceDesktopMigrationName[];
extern const char kTabGroupSyncServiceDesktopMigrationDescription[];
=======
extern const char kTabGroupsAndroidName[];
extern const char kTabGroupsAndroidDescription[];

extern const char kTabGroupsContinuationAndroidName[];
extern const char kTabGroupsContinuationAndroidDescription[];

extern const char kTabGroupsUiImprovementsAndroidName[];
extern const char kTabGroupsUiImprovementsAndroidDescription[];

extern const char kTabToGTSAnimationAndroidName[];
extern const char kTabToGTSAnimationAndroidDescription[];

extern const char kTabGroupsAutoCreateName[];
extern const char kTabGroupsAutoCreateDescription[];

extern const char kTabGroupsCollapseName[];
extern const char kTabGroupsCollapseDescription[];

extern const char kTabGroupsCollapseFreezingName[];
extern const char kTabGroupsCollapseFreezingDescription[];

extern const char kTabGroupsFeedbackName[];
extern const char kTabGroupsFeedbackDescription[];

extern const char kTabGroupsNewBadgePromoName[];
extern const char kTabGroupsNewBadgePromoDescription[];

extern const char kTabGroupsSaveName[];
extern const char kTabGroupsSaveDescription[];
>>>>>>> chromium

extern const char kTabHoverCardImagesName[];
extern const char kTabHoverCardImagesDescription[];

extern const char kTabOutlinesInLowContrastThemesName[];
extern const char kTabOutlinesInLowContrastThemesDescription[];

extern const char kTabRestoreSubMenusName[];
extern const char kTabRestoreSubMenusDescription[];

extern const char kTextFragmentColorChangeName[];
extern const char kTextFragmentColorChangeDescription[];

<<<<<<< HEAD
extern const char kTabResumptionModuleAndroidName[];
extern const char kTabResumptionModuleAndroidDescription[];

extern const char kTextBasedAudioDescriptionName[];
extern const char kTextBasedAudioDescriptionDescription[];

extern const char kTextInShelfName[];
extern const char kTextInShelfDescription[];

extern const char kTextSafetyClassifierName[];
extern const char kTextSafetyClassifierDescription[];

#if BUILDFLAG(IS_ANDROID)
extern const char kAutofillThirdPartyModeContentProviderName[];
extern const char kAutofillThirdPartyModeContentProviderDescription[];
#endif

extern const char kThreadedScrollPreventRenderingStarvationName[];
extern const char kThreadedScrollPreventRenderingStarvationDescription[];
=======
extern const char kTFLiteLanguageDetectionName[];
extern const char kTFLiteLanguageDetectionDescription[];
>>>>>>> chromium

extern const char kThrottleMainTo60HzName[];
extern const char kThrottleMainTo60HzDescription[];

extern const char kTintCompositedContentName[];
extern const char kTintCompositedContentDescription[];

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
extern const char kToolbarPinningFlagId[];
extern const char kToolbarPinningName[];
extern const char kToolbarPinningDescription[];
#endif

#if !BUILDFLAG(IS_ANDROID)
extern const char kTopChromeToastsName[];
extern const char kTopChromeToastsDescription[];

extern const char kTopChromeToastRefinementsName[];
extern const char kTopChromeToastRefinementsDescription[];
#endif

=======
>>>>>>> chromium
extern const char kTopChromeTouchUiName[];
extern const char kTopChromeTouchUiDescription[];

extern const char kThreadedScrollingName[];
extern const char kThreadedScrollingDescription[];

extern const char
    kThrottleDisplayNoneAndVisibilityHiddenCrossOriginIframesName[];
extern const char
    kThrottleDisplayNoneAndVisibilityHiddenCrossOriginIframesDescription[];

extern const char kTouchDragDropName[];
extern const char kTouchDragDropDescription[];

extern const char kTouchSelectionStrategyName[];
extern const char kTouchSelectionStrategyDescription[];
extern const char kTouchSelectionStrategyCharacter[];
extern const char kTouchSelectionStrategyDirection[];

extern const char kTraceUploadUrlName[];
extern const char kTraceUploadUrlDescription[];
extern const char kTraceUploadUrlChoiceOther[];
extern const char kTraceUploadUrlChoiceEmloading[];
extern const char kTraceUploadUrlChoiceQa[];
extern const char kTraceUploadUrlChoiceTesting[];

extern const char kTranslateAssistContentName[];
extern const char kTranslateAssistContentDescription[];

extern const char kTranslateBubbleUIName[];
extern const char kTranslateBubbleUIDescription[];

extern const char kTranslateForceTriggerOnEnglishName[];
extern const char kTranslateForceTriggerOnEnglishDescription[];

extern const char kTranslateIntentName[];
extern const char kTranslateIntentDescription[];

extern const char kTreatInsecureOriginAsSecureName[];
extern const char kTreatInsecureOriginAsSecureDescription[];

extern const char kTreatUnsafeDownloadsAsActiveName[];
extern const char kTreatUnsafeDownloadsAsActiveDescription[];

extern const char kTrustTokensName[];
extern const char kTrustTokensDescription[];

extern const char kTurnOffStreamingMediaCachingOnBatteryName[];
extern const char kTurnOffStreamingMediaCachingOnBatteryDescription[];

extern const char kTurnOffStreamingMediaCachingAlwaysName[];
extern const char kTurnOffStreamingMediaCachingAlwaysDescription[];

extern const char kUnifiedPasswordManagerAndroidName[];
extern const char kUnifiedPasswordManagerAndroidDescription[];

extern const char kUnsafeWebGPUName[];
extern const char kUnsafeWebGPUDescription[];

extern const char kUnsafeWebGPUServiceName[];
extern const char kUnsafeWebGPUServiceDescription[];

extern const char kUnsafeFastJSCallsName[];
extern const char kUnsafeFastJSCallsDescription[];

extern const char kUiPartialSwapName[];
extern const char kUiPartialSwapDescription[];

<<<<<<< HEAD
extern const char kUIEnableSharedImageCacheForGpuName[];
extern const char kUIEnableSharedImageCacheForGpuDescription[];
=======
extern const char kUseFirstPartySetName[];
extern const char kUseFirstPartySetDescription[];
>>>>>>> chromium

extern const char kUseSearchClickForRightClickName[];
extern const char kUseSearchClickForRightClickDescription[];

<<<<<<< HEAD
extern const char kVcBackgroundReplaceName[];
extern const char kVcBackgroundReplaceDescription[];

extern const char kVcRelightingInferenceBackendName[];
extern const char kVcRelightingInferenceBackendDescription[];

extern const char kVcRetouchInferenceBackendName[];
extern const char kVcRetouchInferenceBackendDescription[];

extern const char kVcSegmentationInferenceBackendName[];
extern const char kVcSegmentationInferenceBackendDescription[];

extern const char kVcSegmentationModelName[];
extern const char kVcSegmentationModelDescription[];

extern const char kVcStudioLookName[];
extern const char kVcStudioLookDescription[];

extern const char kVcTrayMicIndicatorName[];
extern const char kVcTrayMicIndicatorDescription[];

extern const char kVcTrayTitleHeaderName[];
extern const char kVcTrayTitleHeaderDescription[];

extern const char kVcLightIntensityName[];
extern const char kVcLightIntensityDescription[];

extern const char kVcWebApiName[];
extern const char kVcWebApiDescription[];

extern const char kVideoPictureInPictureControlsUpdate2024Name[];
extern const char kVideoPictureInPictureControlsUpdate2024Description[];

extern const char kViewportSegmentsName[];
extern const char kViewportSegmentsDescription[];

extern const char kVisitedURLRankingServiceDeduplicationName[];
extern const char kVisitedURLRankingServiceDeduplicationDescription[];

extern const char kVisitedURLRankingServiceHistoryVisibilityScoreFilterName[];
extern const char
    kVisitedURLRankingServiceHistoryVisibilityScoreFilterDescription[];

=======
>>>>>>> chromium
extern const char kV8VmFutureName[];
extern const char kV8VmFutureDescription[];

extern const char kWalletServiceUseSandboxName[];
extern const char kWalletServiceUseSandboxDescription[];

<<<<<<< HEAD
extern const char kWallpaperFastRefreshName[];
extern const char kWallpaperFastRefreshDescription[];

extern const char kWallpaperGooglePhotosSharedAlbumsName[];
extern const char kWallpaperGooglePhotosSharedAlbumsDescription[];

extern const char kWallpaperSearchSettingsVisibilityName[];
extern const char kWallpaperSearchSettingsVisibilityDescription[];

#if !BUILDFLAG(IS_ANDROID)
extern const char kWebAuthnUsePasskeyFromAnotherDeviceInContextMenuName[];
extern const char
    kWebAuthnUsePasskeyFromAnotherDeviceInContextMenuDescription[];
extern const char kWebAuthnEnclaveAuthenticatorName[];
extern const char kWebAuthnEnclaveAuthenticatorDescription[];
extern const char kWebAuthnPasskeyUpgradeName[];
extern const char kWebAuthnPasskeyUpgradeDescription[];
#endif

extern const char kWebBluetoothName[];
extern const char kWebBluetoothDescription[];
=======
extern const char kWallpaperWebUIName[];
extern const char kWallpaperWebUIDescription[];
>>>>>>> chromium

extern const char kWebBluetoothNewPermissionsBackendName[];
extern const char kWebBluetoothNewPermissionsBackendDescription[];

extern const char kWebBundlesName[];
extern const char kWebBundlesDescription[];

extern const char kWebIdName[];
extern const char kWebIdDescription[];

extern const char kWebOtpBackendName[];
extern const char kWebOtpBackendDescription[];
extern const char kWebOtpBackendSmsVerification[];
extern const char kWebOtpBackendUserConsent[];
extern const char kWebOtpBackendAuto[];

extern const char kWebglDeveloperExtensionsName[];
extern const char kWebglDeveloperExtensionsDescription[];

extern const char kWebglDraftExtensionsName[];
extern const char kWebglDraftExtensionsDescription[];

extern const char kWebPaymentsExperimentalFeaturesName[];
extern const char kWebPaymentsExperimentalFeaturesDescription[];

extern const char kWebPaymentsMinimalUIName[];
extern const char kWebPaymentsMinimalUIDescription[];

extern const char kAppStoreBillingDebugName[];
extern const char kAppStoreBillingDebugDescription[];

extern const char kWebrtcCaptureMultiChannelApmName[];
extern const char kWebrtcCaptureMultiChannelApmDescription[];

extern const char kWebrtcHideLocalIpsWithMdnsName[];
extern const char kWebrtcHideLocalIpsWithMdnsDecription[];

extern const char kWebrtcHybridAgcName[];
extern const char kWebrtcHybridAgcDescription[];

extern const char kWebrtcAnalogAgcClippingControlName[];
extern const char kWebrtcAnalogAgcClippingControlDescription[];

extern const char kWebrtcHwDecodingName[];
extern const char kWebrtcHwDecodingDescription[];

extern const char kWebrtcHwEncodingName[];
extern const char kWebrtcHwEncodingDescription[];

<<<<<<< HEAD
=======
extern const char kWebRtcRemoteEventLogName[];
extern const char kWebRtcRemoteEventLogDescription[];

extern const char kWebrtcSrtpAesGcmName[];
extern const char kWebrtcSrtpAesGcmDescription[];

>>>>>>> chromium
extern const char kWebrtcUseMinMaxVEADimensionsName[];
extern const char kWebrtcUseMinMaxVEADimensionsDescription[];

extern const char kWebXrForceRuntimeName[];
extern const char kWebXrForceRuntimeDescription[];

extern const char kWebXrRuntimeChoiceNone[];
extern const char kWebXrRuntimeChoiceOpenXR[];
<<<<<<< HEAD
extern const char kWebXrRuntimeChoiceOrientationSensors[];

extern const char kWebXrHandAnonymizationStrategyName[];
extern const char kWebXrHandAnonymizationStrategyDescription[];

extern const char kWebXrHandAnonymizationChoiceNone[];
extern const char kWebXrHandAnonymizationChoiceRuntime[];
extern const char kWebXrHandAnonymizationChoiceFallback[];

extern const char kWebXrHandInputName[];
extern const char kWebXrHandInputDescription[];
=======
>>>>>>> chromium

extern const char kWebXrWebGpuBindingName[];
extern const char kWebXrWebGpuBindingDescription[];

extern const char kWebXrIncubationsName[];
extern const char kWebXrIncubationsDescription[];

extern const char kWindowsFollowCursorName[];
extern const char kWindowsFollowCursorDescription[];

extern const char kWindowNamingName[];
extern const char kWindowNamingDescription[];

extern const char kZeroCopyName[];
extern const char kZeroCopyDescription[];

extern const char kEnableVulkanName[];
extern const char kEnableVulkanDescription[];

extern const char kSharedHighlightingUseBlocklistName[];
extern const char kSharedHighlightingUseBlocklistDescription[];

extern const char kSharedHighlightingV2Name[];
extern const char kSharedHighlightingV2Description[];

<<<<<<< HEAD
extern const char kSharedHighlightingManagerName[];
extern const char kSharedHighlightingManagerDescription[];
=======
extern const char kSharedHighlightingAmpName[];
extern const char kSharedHighlightingAmpDescription[];

extern const char kPreemptiveLinkToTextGenerationName[];
extern const char kPreemptiveLinkToTextGenerationDescription[];

extern const char kDraw1PredictedPoint12Ms[];
extern const char kDraw2PredictedPoints6Ms[];
extern const char kDraw1PredictedPoint6Ms[];
extern const char kDraw2PredictedPoints3Ms[];
extern const char kDrawPredictedPointsDefault[];
extern const char kDrawPredictedPointsDescription[];
extern const char kDrawPredictedPointsName[];
>>>>>>> chromium

extern const char kSanitizerApiName[];
extern const char kSanitizerApiDescription[];

extern const char kUsePassthroughCommandDecoderName[];
extern const char kUsePassthroughCommandDecoderDescription[];

<<<<<<< HEAD
extern const char kReduceAcceptLanguageName[];
extern const char kReduceAcceptLanguageDescription[];

extern const char kReduceTransferSizeUpdatedIPCName[];
extern const char kReduceTransferSizeUpdatedIPCDescription[];

extern const char kResetAudioSelectionImprovementPrefName[];
extern const char kResetAudioSelectionImprovementPrefDescription[];

extern const char kResetShortcutCustomizationsName[];
extern const char kResetShortcutCustomizationsDescription[];

extern const char kWebSQLAccessName[];
extern const char kWebSQLAccessDescription[];

extern const char kUseIDNA2008NonTransitionalName[];
extern const char kUseIDNA2008NonTransitionalDescription[];

extern const char kEnablePasswordSharingName[];
extern const char kEnablePasswordSharingDescription[];

extern const char kEnableMantaServiceName[];
extern const char kEnableMantaServiceDescription[];

extern const char kPredictableReportedQuotaName[];
extern const char kPredictableReportedQuotaDescription[];

extern const char kPromptAPIForGeminiNanoName[];
extern const char kPromptAPIForGeminiNanoDescription[];
extern const char* const kAIAPIsForGeminiNanoLinks[2];

extern const char kPromptAPIForGeminiNanoMultimodalInputName[];
extern const char kPromptAPIForGeminiNanoMultimodalInputDescription[];

extern const char kSummarizationAPIForGeminiNanoName[];
extern const char kSummarizationAPIForGeminiNanoDescription[];

extern const char kWriterAPIForGeminiNanoName[];
extern const char kWriterAPIForGeminiNanoDescription[];

extern const char kRewriterAPIForGeminiNanoName[];
extern const char kRewriterAPIForGeminiNanoDescription[];
=======
extern const char kExtensionWorkflowJustificationName[];
extern const char kExtensionWorkflowJustificationDescription[];
>>>>>>> chromium

// Android --------------------------------------------------------------------

#if defined(OS_ANDROID)

<<<<<<< HEAD
extern const char kAccessibilityDeprecateTypeAnnounceName[];
extern const char kAccessibilityDeprecateTypeAnnounceDescription[];
extern const char kAccessibilityIncludeLongClickActionName[];
extern const char kAccessibilityIncludeLongClickActionDescription[];
extern const char kAccessibilityPageZoomEnhancementsName[];
extern const char kAccessibilityPageZoomEnhancementsDescription[];
extern const char kAccessibilityUnifiedSnapshotsName[];
extern const char kAccessibilityUnifiedSnapshotsDescription[];
extern const char kAccessibilityManageBroadcastReceiverOnBackgroundName[];
extern const char
    kAccessibilityManageBroadcastReceiverOnBackgroundDescription[];
=======
extern const char kAddToHomescreenIPHName[];
extern const char kAddToHomescreenIPHDescription[];
>>>>>>> chromium

extern const char kAImageReaderName[];
extern const char kAImageReaderDescription[];

extern const char kAndroidDetailedLanguageSettingsName[];
extern const char kAndroidDetailedLanguageSettingsDescription[];

extern const char kAndroidForceAppLanguagePromptName[];
extern const char kAndroidForceAppLanguagePromptDescription[];

extern const char kAndroidLayoutChangeTabReparentingName[];
extern const char kAndroidLayoutChangeTabReparentingDescription[];

extern const char kAndroidPartnerCustomizationPhenotypeName[];
extern const char kAndroidPartnerCustomizationPhenotypeDescription[];

extern const char kAndroidSurfaceControlName[];
extern const char kAndroidSurfaceControlDescription[];

extern const char kAssistantIntentPageUrlName[];
extern const char kAssistantIntentPageUrlDescription[];

extern const char kAssistantIntentTranslateInfoName[];
extern const char kAssistantIntentTranslateInfoDescription[];

extern const char kAsyncDnsName[];
extern const char kAsyncDnsDescription[];

extern const char kAutofillAccessoryViewName[];
extern const char kAutofillAccessoryViewDescription[];

extern const char kAutofillAssistantDirectActionsName[];
extern const char kAutofillAssistantDirectActionsDescription[];

extern const char kAutofillUseMobileLabelDisambiguationName[];
extern const char kAutofillUseMobileLabelDisambiguationDescription[];

<<<<<<< HEAD
extern const char kAndroidPdfAssistContentName[];
extern const char kAndroidPdfAssistContentDescription[];

extern const char kChromePageInfoSharingName[];
extern const char kChromePageInfoSharingDescription[];
=======
extern const char kAppMenuMobileSiteOptionName[];
extern const char kAppMenuMobileSiteOptionDescription[];
>>>>>>> chromium

extern const char kBentoOfflineName[];
extern const char kBentoOfflineDescription[];

extern const char kBookmarkBottomSheetName[];
extern const char kBookmarkBottomSheetDescription[];

<<<<<<< HEAD
extern const char kAndroidTabDeclutterArchiveDuplicateTabsName[];
extern const char kAndroidTabDeclutterArchiveDuplicateTabsDescription[];

extern const char kAppSpecificHistoryName[];
extern const char kAppSpecificHistoryDescription[];

extern const char kBoardingPassDetectorName[];
extern const char kBoardingPassDetectorDescription[];

extern const char kBookmarkPaneAndroidName[];
extern const char kBookmarkPaneAndroidDescription[];

extern const char kCCTAuthTabName[];
extern const char kCCTAuthTabDescription[];

extern const char kCCTAuthTabDisableAllExternalIntentsName[];
extern const char kCCTAuthTabDisableAllExternalIntentsDescription[];

extern const char kCCTAuthTabEnableHttpsRedirectsName[];
extern const char kCCTAuthTabEnableHttpsRedirectsDescription[];

extern const char kCCTBeforeUnloadName[];
extern const char kCCTBeforeUnloadDescription[];

extern const char kCCTEphemeralMediaViewerExperimentName[];
extern const char kCCTEphemeralMediaViewerExperimentDescription[];

extern const char kCCTEphemeralModeName[];
extern const char kCCTEphemeralModeDescription[];
=======
extern const char kCCTIncognitoName[];
extern const char kCCTIncognitoDescription[];
>>>>>>> chromium

extern const char kCCTIncognitoAvailableToThirdPartyName[];
extern const char kCCTIncognitoAvailableToThirdPartyDescription[];

<<<<<<< HEAD
extern const char kCCTMinimizedName[];
extern const char kCCTMinimizedDescription[];

extern const char kCCTNestedSecurityIconName[];
extern const char kCCTNestedSecurityIconDescription[];

extern const char kCCTGoogleBottomBarName[];
extern const char kCCTGoogleBottomBarDescription[];

extern const char kCCTGoogleBottomBarVariantLayoutsName[];
extern const char kCCTGoogleBottomBarVariantLayoutsDescription[];

extern const char kCCTOpenInBrowserButtonIfAllowedByEmbedderName[];
extern const char kCCTOpenInBrowserButtonIfAllowedByEmbedderDescription[];

extern const char kCCTOpenInBrowserButtonIfEnabledByEmbedderName[];
extern const char kCCTOpenInBrowserButtonIfEnabledByEmbedderDescription[];

extern const char kCCTResizableForThirdPartiesName[];
extern const char kCCTResizableForThirdPartiesDescription[];

extern const char kCCTRevampedBrandingName[];
extern const char kCCTRevampedBrandingDescription[];

extern const char kCCTSignInPromptName[];
extern const char kCCTSignInPromptDescription[];

extern const char kBottomBrowserControlsRefactorName[];
extern const char kBottomBrowserControlsRefactorDescription[];

extern const char kBrowsingDataModelName[];
extern const char kBrowsingDataModelDescription[];
=======
extern const char kCCTTargetTranslateLanguageName[];
extern const char kCCTTargetTranslateLanguageDescription[];
>>>>>>> chromium

extern const char kChimeAlwaysShowNotificationDescription[];
extern const char kChimeAlwaysShowNotificationName[];

extern const char kChimeAndroidSdkDescription[];
extern const char kChimeAndroidSdkName[];

extern const char kContinuousSearchName[];
extern const char kContinuousSearchDescription[];

extern const char kChromeShareHighlightsAndroidName[];
extern const char kChromeShareHighlightsAndroidDescription[];

<<<<<<< HEAD
extern const char kTabStateFlatBufferName[];
extern const char kTabStateFlatBufferDescription[];
=======
extern const char kChromeShareLongScreenshotName[];
extern const char kChromeShareLongScreenshotDescription[];

extern const char kChromeShareScreenshotName[];
extern const char kChromeShareScreenshotDescription[];
>>>>>>> chromium

extern const char kChromeSharingHubName[];
extern const char kChromeSharingHubDescription[];

extern const char kClipboardSuggestionContentHiddenName[];
extern const char kClipboardSuggestionContentHiddenDescription[];

extern const char kCloseTabSuggestionsName[];
extern const char kCloseTabSuggestionsDescription[];

<<<<<<< HEAD
extern const char kDrawCutoutEdgeToEdgeName[];
extern const char kDrawCutoutEdgeToEdgeDescription[];
=======
extern const char kCriticalPersistedTabDataName[];
extern const char kCriticalPersistedTabDataDescription[];

extern const char kContextMenuPerformanceInfoAndRemoteHintFetchingName[];
extern const char kContextMenuPerformanceInfoAndRemoteHintFetchingDescription[];

extern const char kContextualSearchDebugName[];
extern const char kContextualSearchDebugDescription[];

extern const char kContextualSearchForceCaptionName[];
extern const char kContextualSearchForceCaptionDescription[];
>>>>>>> chromium

extern const char kContextualSearchLiteralSearchTapName[];
extern const char kContextualSearchLiteralSearchTapDescription[];

<<<<<<< HEAD
extern const char kDynamicSafeAreaInsetsName[];
extern const char kDynamicSafeAreaInsetsDescription[];
=======
extern const char kContextualSearchLongpressResolveName[];
extern const char kContextualSearchLongpressResolveDescription[];

extern const char kContextualSearchMlTapSuppressionName[];
extern const char kContextualSearchMlTapSuppressionDescription[];
>>>>>>> chromium

extern const char kContextualSearchRankerQueryName[];
extern const char kContextualSearchRankerQueryDescription[];

<<<<<<< HEAD
extern const char kDynamicSafeAreaInsetsSupportedByCCName[];
extern const char kDynamicSafeAreaInsetsSupportedByCCDescription[];

extern const char kEdgeToEdgeBottomChinName[];
extern const char kEdgeToEdgeBottomChinDescription[];
=======
extern const char kContextualSearchSecondTapName[];
extern const char kContextualSearchSecondTapDescription[];
>>>>>>> chromium

extern const char kContextualSearchThinWebViewImplementationName[];
extern const char kContextualSearchThinWebViewImplementationDescription[];

<<<<<<< HEAD
extern const char kEdgeToEdgeSafeAreaConstraintName[];
extern const char kEdgeToEdgeSafeAreaConstraintDescription[];

extern const char kEdgeToEdgeWebOptInName[];
extern const char kEdgeToEdgeWebOptInDescription[];
=======
extern const char kContextualSearchTranslationsName[];
extern const char kContextualSearchTranslationsDescription[];
>>>>>>> chromium

extern const char kCpuAffinityRestrictToLittleCoresName[];
extern const char kCpuAffinityRestrictToLittleCoresDescription[];

extern const char kDecoupleSyncFromAndroidAutoSyncName[];
extern const char kDecoupleSyncFromAndroidAutoSyncDescription[];

extern const char kDirectActionsName[];
extern const char kDirectActionsDescription[];

extern const char kDynamicColorAndroidName[];
extern const char kDynamicColorAndroidDescription[];

extern const char kAutofillManualFallbackAndroidName[];
extern const char kAutofillManualFallbackAndroidDescription[];

extern const char kEnableAutofillRefreshStyleName[];
extern const char kEnableAutofillRefreshStyleDescription[];

extern const char kEnableAndroidSpellcheckerDescription[];

extern const char kEnableCommandLineOnNonRootedName[];
extern const char kEnableCommandLineOnNoRootedDescription[];

<<<<<<< HEAD
extern const char kTabClosureMethodRefactorName[];
extern const char kTabClosureMethodRefactorDescription[];

extern const char kEnableClipboardDataControlsAndroidName[];
extern const char kEnableClipboardDataControlsAndroidDescription[];
=======
extern const char kEnableUseAaudioDriverName[];
extern const char kEnableUseAaudioDriverDescription[];

extern const char kExploreSitesName[];
extern const char kExploreSitesDescription[];
>>>>>>> chromium

extern const char kFeedInteractiveRefreshName[];
extern const char kFeedInteractiveRefreshDescription[];

extern const char kFillingPasswordsFromAnyOriginName[];
extern const char kFillingPasswordsFromAnyOriginDescription[];

extern const char kHomepagePromoCardName[];
extern const char kHomepagePromoCardDescription[];

extern const char kInstanceSwitcherName[];
extern const char kInstanceSwitcherDescription[];

extern const char kInstantStartName[];
extern const char kInstantStartDescription[];

extern const char kIntentBlockExternalFormRedirectsNoGestureName[];
extern const char kIntentBlockExternalFormRedirectsNoGestureDescription[];

<<<<<<< HEAD
extern const char kFeedCloseRefreshName[];
extern const char kFeedCloseRefreshDescription[];

extern const char kFeedContainmentName[];
extern const char kFeedContainmentDescription[];

extern const char kFeedDynamicColorsName[];
extern const char kFeedDynamicColorsDescription[];

extern const char kFeedDiscoFeedEndpointName[];
extern const char kFeedDiscoFeedEndpointDescription[];

extern const char kFetchGaiaHashOnSignInName[];
extern const char kFetchGaiaHashOnSignInDescription[];

extern const char kFloatingSnackbarName[];
extern const char kFloatingSnackbarDescription[];

extern const char kForceListTabSwitcherName[];
extern const char kForceListTabSwitcherDescription[];

extern const char kFullscreenInsetsApiMigrationName[];
extern const char kFullscreenInsetsApiMigrationDescription[];

extern const char kFullscreenInsetsApiMigrationOnAutomotiveName[];
extern const char kFullscreenInsetsApiMigrationOnAutomotiveDescription[];

extern const char kGtsCloseTabAnimationName[];
extern const char kGtsCloseTabAnimationDescription[];

extern const char kRefreshFeedOnRestartName[];
extern const char kRefreshFeedOnRestartDescription[];
=======
extern const char kInterestFeedContentSuggestionsName[];
extern const char kInterestFeedContentSuggestionsDescription[];
>>>>>>> chromium

extern const char kInterestFeedV2Name[];
extern const char kInterestFeedV2Description[];

<<<<<<< HEAD
extern const char kLogoPolishName[];
extern const char kLogoPolishDescription[];
=======
extern const char kInterestFeedV2HeartsName[];
extern const char kInterestFeedV2HeartsDescription[];

extern const char kInterestFeedV2AutoplayName[];
extern const char kInterestFeedV2AutoplayDescription[];
>>>>>>> chromium

extern const char kInterestFeedV1ClickAndViewActionsConditionalUploadName[];
extern const char
    kInterestFeedV1ClickAndViewActionsConditionalUploadDescription[];

extern const char kInterestFeedV2ClickAndViewActionsConditionalUploadName[];
extern const char
    kInterestFeedV2ClickAndViewActionsConditionalUploadDescription[];

extern const char kMessagesForAndroidInfrastructureName[];
extern const char kMessagesForAndroidInfrastructureDescription[];

extern const char kMessagesForAndroidPasswordsName[];
extern const char kMessagesForAndroidPasswordsDescription[];

extern const char kMessagesForAndroidPopupBlockedName[];
extern const char kMessagesForAndroidPopupBlockedDescription[];

extern const char kMessagesForAndroidReaderModeName[];
extern const char kMessagesForAndroidReaderModeDescription[];

<<<<<<< HEAD
extern const char kNavBarColorAnimationName[];
extern const char kNavBarColorAnimationDescription[];
=======
extern const char kMessagesForAndroidSafetyTipName[];
extern const char kMessagesForAndroidSafetyTipDescription[];

extern const char kMessagesForAndroidSaveCardName[];
extern const char kMessagesForAndroidSaveCardDescription[];
>>>>>>> chromium

extern const char kMessagesForAndroidUpdatePasswordName[];
extern const char kMessagesForAndroidUpdatePasswordDescription[];

extern const char kNewWindowAppMenuName[];
extern const char kNewWindowAppMenuDescription[];

extern const char kOfflineIndicatorV2Name[];
extern const char kOfflineIndicatorV2Description[];

extern const char kOfflinePagesLivePageSharingName[];
extern const char kOfflinePagesLivePageSharingDescription[];

extern const char kPageInfoDiscoverabilityName[];
extern const char kPageInfoDiscoverabilityDescription[];

<<<<<<< HEAD
extern const char kOmahaMinSdkVersionAndroidName[];
extern const char kOmahaMinSdkVersionAndroidDescription[];
extern const char kOmahaMinSdkVersionAndroidMinSdk1Description[];
extern const char kOmahaMinSdkVersionAndroidMinSdk1000Description[];
=======
extern const char kPageInfoHistoryName[];
extern const char kPageInfoHistoryDescription[];

extern const char kPhotoPickerVideoSupportName[];
extern const char kPhotoPickerVideoSupportDescription[];
>>>>>>> chromium

extern const char kProcessSharingWithDefaultSiteInstancesName[];
extern const char kProcessSharingWithDefaultSiteInstancesDescription[];

extern const char kProcessSharingWithStrictSiteInstancesName[];
extern const char kProcessSharingWithStrictSiteInstancesDescription[];

extern const char kQueryTilesName[];
extern const char kQueryTilesDescription[];
extern const char kQueryTilesNTPName[];
extern const char kQueryTilesNTPDescription[];
extern const char kQueryTilesOmniboxName[];
extern const char kQueryTilesOmniboxDescription[];
extern const char kQueryTilesSingleTierName[];
extern const char kQueryTilesSingleTierDescription[];
extern const char kQueryTilesEnableQueryEditingName[];
extern const char kQueryTilesEnableQueryEditingDescription[];
extern const char kQueryTilesEnableTrendingName[];
extern const char kQueryTilesEnableTrendingDescription[];
extern const char kQueryTilesCountryCode[];
extern const char kQueryTilesCountryCodeDescription[];
extern const char kQueryTilesCountryCodeUS[];
extern const char kQueryTilesCountryCodeIndia[];
extern const char kQueryTilesCountryCodeBrazil[];
extern const char kQueryTilesCountryCodeNigeria[];
extern const char kQueryTilesCountryCodeIndonesia[];
extern const char kQueryTilesLocalOrderingName[];
extern const char kQueryTilesLocalOrderingDescription[];
extern const char kQueryTilesInstantFetchName[];
extern const char kQueryTilesInstantFetchDescription[];
extern const char kQueryTilesMoreTrendingName[];
extern const char kQueryTilesMoreTrendingDescription[];
extern const char kQueryTilesRankTilesName[];
extern const char kQueryTilesRankTilesDescription[];
extern const char kQueryTilesSwapTrendingName[];
extern const char kQueryTilesSwapTrendingDescription[];

extern const char kReaderModeHeuristicsName[];
extern const char kReaderModeHeuristicsDescription[];
extern const char kReaderModeHeuristicsMarkup[];
extern const char kReaderModeHeuristicsAdaboost[];
extern const char kReaderModeHeuristicsAllArticles[];
extern const char kReaderModeHeuristicsAlwaysOff[];
extern const char kReaderModeHeuristicsAlwaysOn[];

<<<<<<< HEAD
=======
extern const char kReaderModeInCCTName[];
extern const char kReaderModeInCCTDescription[];

extern const char kReadLaterReminderNotificationName[];
extern const char kReadLaterReminderNotificationDescription[];

extern const char kRecoverFromNeverSaveAndroidName[];
extern const char kRecoverFromNeverSaveAndroidDescription[];

>>>>>>> chromium
extern const char kReengagementNotificationName[];
extern const char kReengagementNotificationDescription[];

extern const char kRelatedSearchesName[];
extern const char kRelatedSearchesDescription[];

extern const char kRelatedSearchesAlternateUxName[];
extern const char kRelatedSearchesAlternateUxDescription[];

extern const char kRelatedSearchesInBarName[];
extern const char kRelatedSearchesInBarDescription[];

<<<<<<< HEAD
extern const char kRightEdgeGoesForwardGestureNavName[];
extern const char kRightEdgeGoesForwardGestureNavDescription[];

extern const char kSafeBrowsingSyncCheckerCheckAllowlistName[];
extern const char kSafeBrowsingSyncCheckerCheckAllowlistDescription[];
=======
extern const char kRelatedSearchesSimplifiedUxName[];
extern const char kRelatedSearchesSimplifiedUxDescription[];
>>>>>>> chromium

extern const char kRelatedSearchesUiName[];
extern const char kRelatedSearchesUiDescription[];

extern const char kShareUsageRankingName[];
extern const char kShareUsageRankingDescription[];

<<<<<<< HEAD
extern const char kShowNewTabAnimationsName[];
extern const char kShowNewTabAnimationsDescription[];

extern const char kShowReadyToPayDebugInfoName[];
extern const char kShowReadyToPayDebugInfoDescription[];
=======
extern const char kSingleTouchSelectName[];
extern const char kSingleTouchSelectDescription[];
>>>>>>> chromium

extern const char kRequestDesktopSiteForTabletsName[];
extern const char kRequestDesktopSiteForTabletsDescription[];

extern const char kSafeBrowsingClientSideDetectionAndroidName[];
extern const char kSafeBrowsingClientSideDetectionAndroidDescription[];

extern const char
    kSafeBrowsingPasswordCheckIntegrationForSavedPasswordsAndroidName[];
extern const char
    kSafeBrowsingPasswordCheckIntegrationForSavedPasswordsAndroidDescription[];

extern const char kEnhancedProtectionPromoAndroidName[];
extern const char kEnhancedProtectionPromoAndroidDescription[];

extern const char kSafeBrowsingUseLocalBlacklistsV2Name[];
extern const char kSafeBrowsingUseLocalBlacklistsV2Description[];

extern const char kSetMarketUrlForTestingName[];
extern const char kSetMarketUrlForTestingDescription[];

extern const char kSiteIsolationForPasswordSitesName[];
extern const char kSiteIsolationForPasswordSitesDescription[];

extern const char kSmartSuggestionForLargeDownloadsName[];
extern const char kSmartSuggestionForLargeDownloadsDescription[];

extern const char kStartSurfaceAndroidName[];
extern const char kStartSurfaceAndroidDescription[];

extern const char kSharingHubLinkToggleName[];
extern const char kSharingHubLinkToggleDescription[];

extern const char kStrictSiteIsolationName[];
extern const char kStrictSiteIsolationDescription[];

extern const char kActionableContentSettingsName[];
extern const char kActionableContentSettingsDescription[];

extern const char kThemeRefactorAndroidName[];
extern const char kThemeRefactorAndroidDescription[];

<<<<<<< HEAD
extern const char kHistoryPaneAndroidName[];
extern const char kHistoryPaneAndroidDescription[];

extern const char kTabGroupCreationDialogAndroidName[];
extern const char kTabGroupCreationDialogAndroidDescription[];

extern const char kTabGroupPaneAndroidName[];
extern const char kTabGroupPaneAndroidDescription[];

extern const char kTabGroupsForTabletsName[];
extern const char kTabGroupsForTabletsDescription[];

extern const char kTabGroupSyncAndroidName[];
extern const char kTabGroupSyncAndroidDescription[];

extern const char kTabGroupSyncDisableNetworkLayerName[];
extern const char kTabGroupSyncDisableNetworkLayerDescription[];

extern const char kTabStripGroupCollapseAndroidName[];
extern const char kTabStripGroupCollapseAndroidDescription[];

extern const char kTabStripGroupDragDropAndroidName[];
extern const char kTabStripGroupDragDropAndroidDescription[];

extern const char kTabStripGroupReorderAndroidName[];
extern const char kTabStripGroupReorderAndroidDescription[];

extern const char kTabStripIncognitoMigrationName[];
extern const char kTabStripIncognitoMigrationDescription[];

extern const char kTabStripLayoutOptimizationName[];
extern const char kTabStripLayoutOptimizationDescription[];

extern const char kTabStripTransitionInDesktopWindowName[];
extern const char kTabStripTransitionInDesktopWindowDescription[];

extern const char kTabSwitcherColorBlendAnimateName[];
extern const char kTabSwitcherColorBlendAnimateDescription[];

extern const char kTabSwitcherFullNewTabButtonName[];
extern const char kTabSwitcherFullNewTabButtonDescription[];

extern const char kHideTabletToolbarDownloadButtonName[];
extern const char kHideTabletToolbarDownloadButtonDescription[];

extern const char
    kUnifiedPasswordManagerLocalPasswordsAndroidAccessLossWarningName[];
extern const char
    kUnifiedPasswordManagerLocalPasswordsAndroidAccessLossWarningDescription[];
=======
extern const char kToolbarIphAndroidName[];
extern const char kToolbarIphAndroidDescription[];

extern const char kToolbarMicIphAndroidName[];
extern const char kToolbarMicIphAndroidDescription[];
>>>>>>> chromium

extern const char kUpdateMenuBadgeName[];
extern const char kUpdateMenuBadgeDescription[];

extern const char kUpdateMenuItemCustomSummaryDescription[];
extern const char kUpdateMenuItemCustomSummaryName[];

extern const char kUpdateMenuTypeName[];
extern const char kUpdateMenuTypeDescription[];
extern const char kUpdateMenuTypeNone[];
extern const char kUpdateMenuTypeUpdateAvailable[];
extern const char kUpdateMenuTypeUnsupportedOSVersion[];
extern const char kUpdateMenuTypeInlineUpdateSuccess[];
extern const char kUpdateMenuTypeInlineUpdateDialogCanceled[];
extern const char kUpdateMenuTypeInlineUpdateDialogFailed[];
extern const char kUpdateMenuTypeInlineUpdateDownloadFailed[];
extern const char kUpdateMenuTypeInlineUpdateDownloadCanceled[];
extern const char kUpdateMenuTypeInlineUpdateInstallFailed[];

extern const char kUseNotificationCompatBuilderName[];
extern const char kUseNotificationCompatBuilderDescription[];

extern const char kUserMediaScreenCapturingName[];
extern const char kUserMediaScreenCapturingDescription[];

extern const char kVideoTutorialsName[];
extern const char kVideoTutorialsDescription[];
extern const char kVideoTutorialsInstantFetchName[];
extern const char kVideoTutorialsInstantFetchDescription[];

extern const char kAdaptiveButtonInTopToolbarName[];
extern const char kAdaptiveButtonInTopToolbarDescription[];
extern const char kAdaptiveButtonInTopToolbarCustomizationName[];
extern const char kAdaptiveButtonInTopToolbarCustomizationDescription[];
extern const char kShareButtonInTopToolbarName[];
extern const char kShareButtonInTopToolbarDescription[];
extern const char kVoiceButtonInTopToolbarName[];
extern const char kVoiceButtonInTopToolbarDescription[];

extern const char kInlineUpdateFlowName[];
extern const char kInlineUpdateFlowDescription[];

extern const char kSwipeToMoveCursorName[];
extern const char kSwipeToMoveCursorDescription[];

extern const char kWalletRequiresFirstSyncSetupCompleteName[];
extern const char kWalletRequiresFirstSyncSetupCompleteDescription[];

extern const char kWebFeedName[];
extern const char kWebFeedDescription[];

extern const char kWebNotesStylizeName[];
extern const char kWebNotesStylizeDescription[];

extern const char kXsurfaceMetricsReportingName[];
extern const char kXsurfaceMetricsReportingDescription[];

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_VR) && BUILDFLAG(ENABLE_OPENXR)
extern const char kOpenXRExtendedFeaturesName[];
extern const char kOpenXRExtendedFeaturesDescription[];

extern const char kOpenXRName[];
extern const char kOpenXRDescription[];

extern const char kOpenXRAndroidSmoothDepthName[];
extern const char kOpenXRAndroidSmoothDepthDescription[];
#endif

=======
>>>>>>> chromium
// Non-Android ----------------------------------------------------------------

#else  // !defined(OS_ANDROID)

extern const char kAllowAllSitesToInitiateMirroringName[];
extern const char kAllowAllSitesToInitiateMirroringDescription[];

extern const char kAppManagementIntentSettingsName[];
extern const char kAppManagementIntentSettingsDescription[];

extern const char kEnableAccessibilityLiveCaptionName[];
extern const char kEnableAccessibilityLiveCaptionDescription[];

extern const char kEnableAccessibilityLiveCaptionSodaName[];
extern const char kEnableAccessibilityLiveCaptionSodaDescription[];

extern const char kCastMediaRouteProviderName[];
extern const char kCastMediaRouteProviderDescription[];

extern const char kCopyLinkToTextName[];
extern const char kCopyLinkToTextDescription[];

<<<<<<< HEAD
extern const char kEnableCrOSSodaLanguagesName[];
extern const char kEnableCrOSSodaLanguagesDescription[];

extern const char kEnableCrOSSodaConchLanguagesName[];
extern const char kEnableCrOSSodaConchLanguagesDescription[];

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
extern const char kEsbDownloadRowPromoFeatureName[];
extern const char kEsbDownloadRowPromoFeatureDescription[];
#endif

extern const char kFreezingOnEnergySaverName[];
extern const char kFreezingOnEnergySaverDescription[];

extern const char kFreezingOnEnergySaverTestingName[];
extern const char kFreezingOnEnergySaverTestingDescription[];

extern const char kKeyboardLockPromptName[];
extern const char kKeyboardLockPromptDescription[];

extern const char kPressAndHoldEscToExitBrowserFullscreenName[];
extern const char kPressAndHoldEscToExitBrowserFullscreenDescription[];

extern const char kReadAnythingImagesViaAlgorithmName[];
extern const char kReadAnythingImagesViaAlgorithmDescription[];

extern const char kReadAnythingReadAloudName[];
extern const char kReadAnythingReadAloudDescription[];

extern const char kReadAnythingReadAloudPhraseHighlightingName[];
extern const char kReadAnythingReadAloudPhraseHighlightingDescription[];

extern const char kReadAnythingDocsIntegrationName[];
extern const char kReadAnythingDocsIntegrationDescription[];

extern const char kReadAnythingDocsLoadMoreButtonName[];
extern const char kReadAnythingDocsLoadMoreButtonDescription[];

extern const char kLinkPreviewName[];
extern const char kLinkPreviewDescription[];

extern const char kMoveThemePrefsToSpecificsName[];
extern const char kMoveThemePrefsToSpecificsDescription[];
=======
extern const char kEnterpriseRealtimeExtensionRequestName[];
extern const char kEnterpriseRealtimeExtensionRequestDescription[];

extern const char kGlobalMediaControlsCastStartStopName[];
extern const char kGlobalMediaControlsCastStartStopDescription[];
>>>>>>> chromium

extern const char kMuteNotificationSnoozeActionName[];
extern const char kMuteNotificationSnoozeActionDescription[];

extern const char kNtpCacheOneGoogleBarName[];
extern const char kNtpCacheOneGoogleBarDescription[];

extern const char kNtpRepeatableQueriesName[];
extern const char kNtpRepeatableQueriesDescription[];

extern const char kNtpModulesName[];
extern const char kNtpModulesDescription[];

extern const char kNtpDriveModuleName[];
extern const char kNtpDriveModuleDescription[];

extern const char kNtpRecipeTasksModuleName[];
extern const char kNtpRecipeTasksModuleDescription[];

extern const char kNtpShoppingTasksModuleName[];
extern const char kNtpShoppingTasksModuleDescription[];

extern const char kNtpChromeCartModuleName[];
extern const char kNtpChromeCartModuleDescription[];

extern const char kNtpModulesDragAndDropName[];
extern const char kNtpModulesDragAndDropDescription[];

extern const char kNtpModulesRedesignedName[];
extern const char kNtpModulesRedesignedDescription[];

<<<<<<< HEAD
extern const char kNtpOneGoogleBarAsyncBarPartsName[];
extern const char kNtpOneGoogleBarAsyncBarPartsDescription[];

extern const char kNtpOutlookCalendarModuleName[];
extern const char kNtpOutlookCalendarModuleDescription[];

extern const char kNtpPhotosModuleOptInTitleName[];
extern const char kNtpPhotosModuleOptInTitleDescription[];

extern const char kNtpPhotosModuleOptInArtWorkName[];
extern const char kNtpPhotosModuleOptInArtWorkDescription[];

extern const char kNtpPhotosModuleName[];
extern const char kNtpPhotosModuleDescription[];

extern const char kNtpPhotosModuleSoftOptOutName[];
extern const char kNtpPhotosModuleSoftOptOutDescription[];

extern const char kNtpRealboxContextualAndTrendingSuggestionsName[];
extern const char kNtpRealboxContextualAndTrendingSuggestionsDescription[];

extern const char kNtpRealboxCr23ThemingName[];
extern const char kNtpRealboxCr23ThemingDescription[];

extern const char kNtpRealboxMatchSearchboxThemeName[];
extern const char kNtpRealboxMatchSearchboxThemeDescription[];

extern const char kNtpRealboxUseGoogleGIconName[];
extern const char kNtpRealboxUseGoogleGIconDescription[];

extern const char kNtpSafeBrowsingModuleName[];
extern const char kNtpSafeBrowsingModuleDescription[];

extern const char kNtpSharepointModuleName[];
extern const char kNtpSharepointModuleDescription[];

extern const char kNtpWallpaperSearchButtonName[];
extern const char kNtpWallpaperSearchButtonDescription[];

extern const char kNtpWallpaperSearchButtonAnimationName[];
extern const char kNtpWallpaperSearchButtonAnimationDescription[];

extern const char kNtpWideModulesName[];
extern const char kNtpWideModulesDescription[];
=======
extern const char kNtpRealboxSuggestionAnswersName[];
extern const char kNtpRealboxSuggestionAnswersDescription[];

extern const char kEnableReaderModeName[];
extern const char kEnableReaderModeDescription[];
>>>>>>> chromium

extern const char kHappinessTrackingSurveysForDesktopDemoName[];
extern const char kHappinessTrackingSurveysForDesktopDemoDescription[];

<<<<<<< HEAD
extern const char kMainNodeAnnotationsName[];
extern const char kMainNodeAnnotationsDescription[];
=======
extern const char kHappinessTrackingSurveysForDesktopPrivacySandboxName[];
extern const char
    kHappinessTrackingSurveysForDesktopPrivacySandboxDescription[];

extern const char kHappinessTrackingSurveysForDesktopSettingsName[];
extern const char kHappinessTrackingSurveysForDesktopSettingsDescription[];

extern const char kHappinessTrackingSurveysForDesktopSettingsPrivacyName[];
extern const char
    kHappinessTrackingSurveysForDesktopSettingsPrivacyDescription[];

extern const char kKernelnextVMsName[];
extern const char kKernelnextVMsDescription[];
>>>>>>> chromium

extern const char kOmniboxDriveSuggestionsName[];
extern const char kOmniboxDriveSuggestionsDescriptions[];

extern const char kOmniboxExperimentalKeywordModeName[];
extern const char kOmniboxExperimentalKeywordModeDescription[];

extern const char kOmniboxSuggestionButtonRowName[];
extern const char kOmniboxSuggestionButtonRowDescription[];

extern const char kOmniboxPedalSuggestionsName[];
extern const char kOmniboxPedalSuggestionsDescription[];

extern const char kOmniboxPedalsBatch2Name[];
extern const char kOmniboxPedalsBatch2Description[];

extern const char kOmniboxPedalsBatch2NonEnglishName[];
extern const char kOmniboxPedalsBatch2NonEnglishDescription[];

extern const char kOmniboxPedalsBatch3Name[];
extern const char kOmniboxPedalsBatch3Description[];

extern const char kOmniboxPedalsDefaultIconColoredName[];
extern const char kOmniboxPedalsDefaultIconColoredDescription[];

extern const char kOmniboxKeywordSearchButtonName[];
extern const char kOmniboxKeywordSearchButtonDescription[];

extern const char kOmniboxRefinedFocusStateName[];
extern const char kOmniboxRefinedFocusStateDescription[];

extern const char kSCTAuditingName[];
extern const char kSCTAuditingDescription[];

extern const char kShutdownSupportForKeepaliveName[];
extern const char kShutdownSupportForKeepaliveDescription[];

extern const char kTabFreezeName[];
extern const char kTabFreezeDescription[];

<<<<<<< HEAD
extern const char kTabOrganizationSettingsVisibilityName[];
extern const char kTabOrganizationSettingsVisibilityDescription[];

extern const char kTabstripDeclutterName[];
extern const char kTabstripDeclutterDescription[];

extern const char kTabstripDedupeName[];
extern const char kTabstripDedupeDescription[];

extern const char kIOSPromoRefreshedPasswordBubbleName[];
extern const char kIOSPromoRefreshedPasswordBubbleDescription[];

extern const char kIOSPromoAddressBubbleName[];
extern const char kIOSPromoAddressBubbleDescription[];

extern const char kIOSPromoPaymentBubbleName[];
extern const char kIOSPromoPaymentBubbleDescription[];

extern const char kWebAppSyncGeneratedIconBackgroundFixName[];
extern const char kWebAppSyncGeneratedIconBackgroundFixDescription[];

extern const char kWebAppSyncGeneratedIconRetroactiveFixName[];
extern const char kWebAppSyncGeneratedIconRetroactiveFixDescription[];

extern const char kWebAppSyncGeneratedIconUpdateFixName[];
extern const char kWebAppSyncGeneratedIconUpdateFixDescription[];

#if !BUILDFLAG(IS_ANDROID)
extern const char kTranslateOpenSettingsName[];
extern const char kTranslateOpenSettingsDescription[];
#endif

extern const char kUserDisplayModeSyncBrowserMitigationName[];
extern const char kUserDisplayModeSyncBrowserMitigationDescription[];

extern const char kUserDisplayModeSyncStandaloneMitigationName[];
extern const char kUserDisplayModeSyncStandaloneMitigationDescription[];

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
extern const char kWasmTtsComponentUpdaterEnabledName[];
extern const char kWasmTtsComponentUpdaterEnabledDescription[];
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)
extern const char kWebAppSystemMediaControlsName[];
extern const char kWebAppSystemMediaControlsDescription[];
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)

extern const char kWebAuthenticationPermitEnterpriseAttestationName[];
extern const char kWebAuthenticationPermitEnterpriseAttestationDescription[];

#endif  // BUILDFLAG(IS_ANDROID)
=======
#endif  // defined(OS_ANDROID)
>>>>>>> chromium

// Windows --------------------------------------------------------------------

#if defined(OS_WIN)

extern const char kCalculateNativeWinOcclusionName[];
extern const char kCalculateNativeWinOcclusionDescription[];

extern const char kChromeCleanupScanCompletedNotificationName[];
extern const char kChromeCleanupScanCompletedNotificationDescription[];

extern const char kCloudPrintXpsName[];
extern const char kCloudPrintXpsDescription[];

extern const char kD3D11VideoDecoderName[];
extern const char kD3D11VideoDecoderDescription[];

extern const char kEnableIncognitoShortcutOnDesktopName[];
extern const char kEnableIncognitoShortcutOnDesktopDescription[];

extern const char kEnableMediaFoundationVideoCaptureName[];
extern const char kEnableMediaFoundationVideoCaptureDescription[];

extern const char kRawAudioCaptureName[];
extern const char kRawAudioCaptureDescription[];

extern const char kRunVideoCaptureServiceInBrowserProcessName[];
extern const char kRunVideoCaptureServiceInBrowserProcessDescription[];

extern const char kSafetyCheckChromeCleanerChildName[];
extern const char kSafetyCheckChromeCleanerChildDescription[];

extern const char kUseAngleName[];
extern const char kUseAngleDescription[];

extern const char kUseAngleDefault[];
extern const char kUseAngleGL[];
extern const char kUseAngleD3D11[];
extern const char kUseAngleD3D9[];
extern const char kUseAngleD3D11on12[];

extern const char kUseWinrtMidiApiName[];
extern const char kUseWinrtMidiApiDescription[];

<<<<<<< HEAD
extern const char kWebRtcAllowWgcScreenCapturerName[];
extern const char kWebRtcAllowWgcScreenCapturerDescription[];

extern const char kWebRtcAllowWgcWindowCapturerName[];
extern const char kWebRtcAllowWgcWindowCapturerDescription[];

extern const char kWindows11MicaTitlebarName[];
extern const char kWindows11MicaTitlebarDescription[];

inline constexpr char kWindowsSystemTracingName[] = "System tracing";
inline constexpr char kWindowsSystemTracingDescription[] =
    "When enabled, the system tracing service is started along with Chrome's "
    "tracing service (if the system tracing service is registered).";

#if BUILDFLAG(ENABLE_EXTENSIONS)
extern const char kLaunchWindowsNativeHostsDirectlyName[];
extern const char kLaunchWindowsNativeHostsDirectlyDescription[];
#endif  // ENABLE_EXTENSIONS

=======
>>>>>>> chromium
#if BUILDFLAG(ENABLE_PRINTING)
extern const char kGdiTextPrinting[];
extern const char kGdiTextPrintingDescription[];

extern const char kPrintWithReducedRasterizationName[];
extern const char kPrintWithReducedRasterizationDescription[];

extern const char kUseXpsForPrintingName[];
extern const char kUseXpsForPrintingDescription[];

extern const char kUseXpsForPrintingFromPdfName[];
extern const char kUseXpsForPrintingFromPdfDescription[];
#endif  // BUILDFLAG(ENABLE_PRINTING)

extern const char kWin10TabSearchCaptionButtonName[];
extern const char kWin10TabSearchCaptionButtonDescription[];

#endif  // defined(OS_WIN)

// Mac ------------------------------------------------------------------------

#if defined(OS_MAC)

#if BUILDFLAG(ENABLE_PRINTING)
extern const char kCupsIppPrintingBackendName[];
extern const char kCupsIppPrintingBackendDescription[];
#endif  // BUILDFLAG(ENABLE_PRINTING)

extern const char kEnterpriseReportingApiKeychainRecreationName[];
extern const char kEnterpriseReportingApiKeychainRecreationDescription[];

extern const char kImmersiveFullscreenName[];
extern const char kImmersiveFullscreenDescription[];

<<<<<<< HEAD
extern const char kMacAccessibilityAPIMigrationName[];
extern const char kMacAccessibilityAPIMigrationDescription[];

extern const char kMacImeLiveConversionFixName[];
extern const char kMacImeLiveConversionFixDescription[];

extern const char kMacLoopbackAudioForScreenShareName[];
extern const char kMacLoopbackAudioForScreenShareDescription[];

extern const char kMacPWAsNotificationAttributionName[];
extern const char kMacPWAsNotificationAttributionDescription[];

=======
>>>>>>> chromium
extern const char kMacSyscallSandboxName[];
extern const char kMacSyscallSandboxDescription[];

extern const char kMetalName[];
extern const char kMetalDescription[];

extern const char kScreenTimeName[];
extern const char kScreenTimeDescription[];

#endif  // defined(OS_MAC)

<<<<<<< HEAD
extern const char kUseAdHocSigningForWebAppShimsName[];
extern const char kUseAdHocSigningForWebAppShimsDescription[];

extern const char kUseSCContentSharingPickerName[];
extern const char kUseSCContentSharingPickerDescription[];

extern const char kBlockRootWindowAccessibleNameChangeEventName[];
extern const char kBlockRootWindowAccessibleNameChangeEventDescription[];

#endif  // BUILDFLAG(IS_MAC)

// Windows and Mac ------------------------------------------------------------

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)

extern const char kLocationProviderManagerName[];
extern const char kLocationProviderManagerDescription[];

extern const char kUseAngleGL[];

#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)

//  Android  --------------------------------------------------

#if BUILDFLAG(IS_ANDROID)

extern const char kUseAngleDescriptionAndroid[];

extern const char kUseAngleGLES[];
extern const char kUseAngleVulkan[];

#endif  // BUILDFLAG(IS_ANDROID)

// Windows, Mac and Android  --------------------------------------------------

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_ANDROID)

extern const char kUseAngleName[];

extern const char kUseAngleDefault[];

#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_ANDROID)

// ChromeOS -------------------------------------------------------------------
=======
// Chrome OS ------------------------------------------------------------------
>>>>>>> chromium

#if BUILDFLAG(IS_CHROMEOS)

extern const char kAccountManagementFlowsV2Name[];
extern const char kAccountManagementFlowsV2Description[];

extern const char kAcceleratedMjpegDecodeName[];
extern const char kAcceleratedMjpegDecodeDescription[];

<<<<<<< HEAD
extern const char kAccessibilityBounceKeysName[];
extern const char kAccessibilityBounceKeysDescription[];

extern const char kAccessibilitySlowKeysName[];
extern const char kAccessibilitySlowKeysDescription[];

extern const char kAllowApnModificationPolicyName[];
extern const char kAllowApnModificationPolicyDescription[];

extern const char kAllowCrossDeviceFeatureSuiteName[];
extern const char kAllowCrossDeviceFeatureSuiteDescription[];

extern const char kLinkCrossDeviceInternalsName[];
extern const char kLinkCrossDeviceInternalsDescription[];
=======
extern const char kAllowDisableMouseAccelerationName[];
extern const char kAllowDisableMouseAccelerationDescription[];

extern const char kAllowRepeatedUpdatesName[];
extern const char kAllowRepeatedUpdatesDescription[];
>>>>>>> chromium

extern const char kAllowScrollSettingsName[];
extern const char kAllowScrollSettingsDescription[];

extern const char kAppListBubbleName[];
extern const char kAppListBubbleDescription[];

extern const char kAppServiceAdaptiveIconName[];
extern const char kAppServiceAdaptiveIconDescription[];

extern const char kAppServiceExternalProtocolName[];
extern const char kAppServiceExternalProtocolDescription[];

extern const char kArcCustomTabsExperimentName[];
extern const char kArcCustomTabsExperimentDescription[];

<<<<<<< HEAD
extern const char kArcEnableAttestationName[];
extern const char kArcEnableAttestationDescription[];

extern const char kArcExtendInputAnrTimeoutName[];
extern const char kArcExtendInputAnrTimeoutDescription[];

extern const char kArcExtendIntentAnrTimeoutName[];
extern const char kArcExtendIntentAnrTimeoutDescription[];

extern const char kArcExtendServiceAnrTimeoutName[];
extern const char kArcExtendServiceAnrTimeoutDescription[];

extern const char kArcFriendlierErrorDialogName[];
extern const char kArcFriendlierErrorDialogDescription[];

extern const char kArcIdleManagerName[];
extern const char kArcIdleManagerDescription[];

extern const char kArcInstantResponseWindowOpenName[];
extern const char kArcInstantResponseWindowOpenDescription[];
=======
extern const char kArcDocumentsProviderUnknownSizeName[];
extern const char kArcDocumentsProviderUnknownSizeDescription[];

extern const char kArcFilePickerExperimentName[];
extern const char kArcFilePickerExperimentDescription[];

extern const char kArcImageCopyPasteCompatName[];
extern const char kArcImageCopyPasteCompatDescription[];

extern const char kArcKeyboardShortcutHelperIntegrationName[];
extern const char kArcKeyboardShortcutHelperIntegrationDescription[];
>>>>>>> chromium

extern const char kArcNativeBridgeToggleName[];
extern const char kArcNativeBridgeToggleDescription[];

extern const char kArcNativeBridge64BitSupportExperimentName[];
extern const char kArcNativeBridge64BitSupportExperimentDescription[];

extern const char kArcRtVcpuDualCoreName[];
extern const char kArcRtVcpuDualCoreDesc[];

extern const char kArcRtVcpuQuadCoreName[];
extern const char kArcRtVcpuQuadCoreDesc[];

extern const char kArcUseHighMemoryDalvikProfileName[];
extern const char kArcUseHighMemoryDalvikProfileDesc[];

extern const char kArcWebAppShareName[];
extern const char kArcWebAppShareDescription[];

extern const char kArcEnableUsapName[];
extern const char kArcEnableUsapDesc[];

extern const char kAshEnablePipRoundedCornersName[];
extern const char kAshEnablePipRoundedCornersDescription[];

extern const char kAshEnableUnifiedDesktopName[];
extern const char kAshEnableUnifiedDesktopDescription[];

extern const char kAshSwipingFromLeftEdgeToGoBackName[];
extern const char kAshSwipingFromLeftEdgeToGoBackDescription[];

extern const char kBluetoothAdvertisementMonitoringName[];
extern const char kBluetoothAdvertisementMonitoringDescription[];

extern const char kBluetoothAggressiveAppearanceFilterName[];
extern const char kBluetoothAggressiveAppearanceFilterDescription[];

extern const char kBluetoothFixA2dpPacketSizeName[];
extern const char kBluetoothFixA2dpPacketSizeDescription[];

extern const char kBluetoothRevampName[];
extern const char kBluetoothRevampDescription[];

extern const char kBluetoothWbsDogfoodName[];
extern const char kBluetoothWbsDogfoodDescription[];

<<<<<<< HEAD
extern const char kAshSplitKeyboardRefactorName[];
extern const char kAshSplitKeyboardRefactorDescription[];

extern const char kAshNullTopRowFixName[];
extern const char kAshNullTopRowFixDescription[];

extern const char kAssistantIphName[];
extern const char kAssistantIphDescription[];

extern const char kAudioA2DPAdvancedCodecsName[];
extern const char kAudioA2DPAdvancedCodecsDescription[];

extern const char kAudioSelectionImprovementName[];
extern const char kAudioSelectionImprovementDescription[];

extern const char kAutoFramingOverrideName[];
extern const char kAutoFramingOverrideDescription[];

extern const char kAutocorrectByDefaultName[];
extern const char kAutocorrectByDefaultDescription[];

extern const char kAutocorrectParamsTuningName[];
extern const char kAutocorrectParamsTuningDescription[];

extern const char kBatteryBadgeIconName[];
extern const char kBatteryBadgeIconDescription[];

extern const char kBlockTelephonyDevicePhoneMuteName[];
extern const char kBlockTelephonyDevicePhoneMuteDescription[];

extern const char kBluetoothAudioLEAudioOnlyName[];
extern const char kBluetoothAudioLEAudioOnlyDescription[];

extern const char kBluetoothBtsnoopInternalsName[];
extern const char kBluetoothBtsnoopInternalsDescription[];

extern const char kBluetoothFlossTelephonyName[];
extern const char kBluetoothFlossTelephonyDescription[];

extern const char kBluetoothUseFlossName[];
extern const char kBluetoothUseFlossDescription[];

extern const char kBluetoothWifiQSPodRefreshName[];
extern const char kBluetoothWifiQSPodRefreshDescription[];

extern const char kBluetoothUseLLPrivacyName[];
extern const char kBluetoothUseLLPrivacyDescription[];

extern const char kCampbellGlyphName[];
extern const char kCampbellGlyphDescription[];

extern const char kCampbellKeyName[];
extern const char kCampbellKeyDescription[];

extern const char kCaptureModeEducationName[];
extern const char kCaptureModeEducationDescription[];

extern const char kCaptureModeEducationBypassLimitsName[];
extern const char kCaptureModeEducationBypassLimitsDescription[];

extern const char kCrosContentAdjustedRefreshRateName[];
extern const char kCrosContentAdjustedRefreshRateDescription[];

extern const char kCrosSoulName[];
extern const char kCrosSoulDescription[];

extern const char kCrosSoulGravediggerName[];
extern const char kCrosSoulGravediggerDescription[];

extern const char kDeskButtonName[];
extern const char kDeskButtonDescription[];

extern const char kDesksTemplatesName[];
extern const char kDesksTemplatesDescription[];
=======
extern const char kButtonARCNetworkDiagnosticsName[];
extern const char kButtonARCNetworkDiagnosticsDescription[];
>>>>>>> chromium

extern const char kForceControlFaceAeName[];
extern const char kForceControlFaceAeDescription[];

extern const char kCategoricalSearchName[];
extern const char kCategoricalSearchDescription[];

extern const char kCdmFactoryDaemonName[];
extern const char kCdmFactoryDaemonDescription[];

extern const char kCellularAllowPerNetworkRoamingName[];
extern const char kCellularAllowPerNetworkRoamingDescription[];

<<<<<<< HEAD
extern const char kClipboardHistoryUrlTitlesName[];
extern const char kClipboardHistoryUrlTitlesDescription[];
=======
extern const char kCellularForbidAttachApnName[];
extern const char kCellularForbidAttachApnDescription[];

extern const char kCellularUseAttachApnName[];
extern const char kCellularUseAttachApnDescription[];
>>>>>>> chromium

extern const char kCellularUseExternalEuiccName[];
extern const char kCellularUseExternalEuiccDescription[];

extern const char kContextualNudgesName[];
extern const char kContextualNudgesDescription[];

extern const char kCroshSWAName[];
extern const char kCroshSWADescription[];

extern const char kCrosLanguageSettingsUpdate2Name[];
extern const char kCrosLanguageSettingsUpdate2Description[];

extern const char kCrosOnDeviceGrammarCheckName[];
extern const char kCrosOnDeviceGrammarCheckDescription[];

extern const char kCrosRegionsModeName[];
extern const char kCrosRegionsModeDescription[];
extern const char kCrosRegionsModeDefault[];
extern const char kCrosRegionsModeOverride[];
extern const char kCrosRegionsModeHide[];

extern const char kCrostiniDiskResizingName[];
extern const char kCrostiniDiskResizingDescription[];

<<<<<<< HEAD
extern const char kDisableBruschettaInstallChecksName[];
extern const char kDisableBruschettaInstallChecksDescription[];

extern const char kCrostiniContainerInstallName[];
extern const char kCrostiniContainerInstallDescription[];
=======
extern const char kCrostiniUseBusterImageName[];
extern const char kCrostiniUseBusterImageDescription[];
>>>>>>> chromium

extern const char kCrostiniGpuSupportName[];
extern const char kCrostiniGpuSupportDescription[];

extern const char kCrostiniUseDlcName[];
extern const char kCrostiniUseDlcDescription[];

extern const char kCrostiniResetLxdDbName[];
extern const char kCrostiniResetLxdDbDescription[];

extern const char kCryptAuthV2DeviceActivityStatusName[];
extern const char kCryptAuthV2DeviceActivityStatusDescription[];

extern const char kCryptAuthV2DeviceActivityStatusUseConnectivityName[];
extern const char kCryptAuthV2DeviceActivityStatusUseConnectivityDescription[];

extern const char kCryptAuthV2DeviceSyncName[];
extern const char kCryptAuthV2DeviceSyncDescription[];

extern const char kCryptAuthV2EnrollmentName[];
extern const char kCryptAuthV2EnrollmentDescription[];

extern const char kDisableBufferBWCompressionName[];
extern const char kDisableBufferBWCompressionDescription[];

<<<<<<< HEAD
=======
extern const char kDisableCameraFrameRotationAtSourceName[];
extern const char kDisableCameraFrameRotationAtSourceDescription[];

extern const char kForceSpectreVariant2MitigationName[];
extern const char kForceSpectreVariant2MitigationDescription[];

>>>>>>> chromium
extern const char kDisableCancelAllTouchesName[];
extern const char kDisableCancelAllTouchesDescription[];

extern const char kDisableCryptAuthV1DeviceSyncName[];
extern const char kDisableCryptAuthV1DeviceSyncDescription[];

extern const char kDisableIdleSocketsCloseOnMemoryPressureName[];
extern const char kDisableIdleSocketsCloseOnMemoryPressureDescription[];

extern const char kDisableExplicitDmaFencesName[];
extern const char kDisableExplicitDmaFencesDescription[];

extern const char kDisplayAlignmentAssistanceName[];
extern const char kDisplayAlignmentAssistanceDescription[];

<<<<<<< HEAD
extern const char kFaceRetouchOverrideName[];
extern const char kFaceRetouchOverrideDescription[];

extern const char kFastPairDebugMetadataName[];
extern const char kFastPairDebugMetadataDescription[];

extern const char kFastPairHandshakeLongTermRefactorName[];
extern const char kFastPairHandshakeLongTermRefactorDescription[];

extern const char kFastPairKeyboardsName[];
extern const char kFastPairKeyboardsDescription[];

extern const char kFastPairPwaCompanionName[];
extern const char kFastPairPwaCompanionDescription[];

extern const char kFastPairDevicesBluetoothSettingsName[];
extern const char kFastPairDevicesBluetoothSettingsDescription[];

extern const char kFrameSinkDesktopCapturerInCrdName[];
extern const char kFrameSinkDesktopCapturerInCrdDescription[];
=======
extern const char kDisplayIdentificationName[];
extern const char kDisplayIdentificationDescription[];
>>>>>>> chromium

extern const char kUseHDRTransferFunctionName[];
extern const char kUseHDRTransferFunctionDescription[];

extern const char kDisableOfficeEditingComponentAppName[];
extern const char kDisableOfficeEditingComponentAppDescription[];

extern const char kDoubleTapToZoomInTabletModeName[];
extern const char kDoubleTapToZoomInTabletModeDescription[];

extern const char kQuickSettingsPWANotificationsDescription[];

extern const char kDriveFsBidirectionalNativeMessagingName[];
extern const char kDriveFsBidirectionalNativeMessagingDescription[];

extern const char kEnableAppDataSearchName[];
extern const char kEnableAppDataSearchDescription[];

<<<<<<< HEAD
extern const char kEnableAssistantRoutinesName[];
extern const char kEnableAssistantRoutinesDescription[];

extern const char kEnableBackgroundBlurName[];
extern const char kEnableBackgroundBlurDescription[];

extern const char kEnableBrightnessControlInSettingsName[];
extern const char kEnableBrightnessControlInSettingsDescription[];

extern const char kEnableDisplayPerformanceModeName[];
extern const char kEnableDisplayPerformanceModeDescription[];

extern const char kDisableDnsProxyName[];
extern const char kDisableDnsProxyDescription[];

extern const char kDisconnectWiFiOnEthernetConnectedName[];
extern const char kDisconnectWiFiOnEthernetConnectedDescription[];

extern const char kEnableRFC8925Name[];
extern const char kEnableRFC8925Description[];

extern const char kEnableRootNsDnsProxyName[];
extern const char kEnableRootNsDnsProxyDescription[];

extern const char kEnableEdidBasedDisplayIdsName[];
extern const char kEnableEdidBasedDisplayIdsDescription[];

extern const char kTiledDisplaySupportName[];
extern const char kTiledDisplaySupportDescription[];

extern const char kEnableDozeModePowerSchedulerName[];
extern const char kEnableDozeModePowerSchedulerDescription[];

extern const char kEnableExternalKeyboardsInDiagnosticsAppName[];
extern const char kEnableExternalKeyboardsInDiagnosticsAppDescription[];

extern const char kEnableFastInkForSoftwareCursorName[];
extern const char kEnableFastInkForSoftwareCursorDescription[];

extern const char kEnableGetDebugdLogsInParallelName[];
extern const char kEnableGetDebugdLogsInParallelDescription[];

extern const char kEnableHostnameSettingName[];
extern const char kEnableHostnameSettingDescription[];

extern const char kEnableGesturePropertiesDBusServiceName[];
extern const char kEnableGesturePropertiesDBusServiceDescription[];

extern const char kEnableGoogleAssistantDspName[];
extern const char kEnableGoogleAssistantDspDescription[];

extern const char kEnableGoogleAssistantStereoInputName[];
extern const char kEnableGoogleAssistantStereoInputDescription[];

extern const char kEnableGoogleAssistantAecName[];
extern const char kEnableGoogleAssistantAecDescription[];

extern const char kEnableInputEventLoggingName[];
extern const char kEnableInputEventLoggingDescription[];

extern const char kEnableKeyboardBacklightControlInSettingsName[];
extern const char kEnableKeyboardBacklightControlInSettingsDescription[];

extern const char kEnableKeyboardRewriterFixName[];
extern const char kEnableKeyboardRewriterFixDescription[];

extern const char kEnableLibinputToHandleTouchpadName[];
extern const char kEnableLibinputToHandleTouchpadDescription[];

extern const char kEnableNeuralPalmAdaptiveHoldName[];
extern const char kEnableNeuralPalmAdaptiveHoldDescription[];

extern const char kEnableFakeKeyboardHeuristicName[];
extern const char kEnableFakeKeyboardHeuristicDescription[];

extern const char kEnableFakeMouseHeuristicName[];
extern const char kEnableFakeMouseHeuristicDescription[];

extern const char kEnableHeatmapPalmDetectionName[];
extern const char kEnableHeatmapPalmDetectionDescription[];

extern const char kEnableKeyboardUsedPalmSuppressionName[];
extern const char kEnableKeyboardUsedPalmSuppressionDescription[];

extern const char kEnableNeuralStylusPalmRejectionName[];
extern const char kEnableNeuralStylusPalmRejectionDescription[];

extern const char kEnableEdgeDetectionName[];
extern const char kEnableEdgeDetectionDescription[];

extern const char kEnableFastTouchpadClickName[];
extern const char kEnableFastTouchpadClickDescription[];

extern const char kEnablePalmSuppressionName[];
extern const char kEnablePalmSuppressionDescription[];

extern const char kEnableRemoveStalePolicyPinnedAppsFromShelfName[];
extern const char kEnableRemoveStalePolicyPinnedAppsFromShelfDescription[];

extern const char kEnableSeamlessRefreshRateSwitchingName[];
extern const char kEnableSeamlessRefreshRateSwitchingDescription[];

extern const char kEnableToggleCameraShortcutName[];
extern const char kEnableToggleCameraShortcutDescription[];

extern const char kEnableTouchpadsInDiagnosticsAppName[];
extern const char kEnableTouchpadsInDiagnosticsAppDescription[];

extern const char kEnableTouchscreensInDiagnosticsAppName[];
extern const char kEnableTouchscreensInDiagnosticsAppDescription[];

extern const char kEnableWifiQosName[];
extern const char kEnableWifiQosDescription[];

extern const char kEnableWifiQosEnterpriseName[];
extern const char kEnableWifiQosEnterpriseDescription[];

extern const char kEapGtcWifiAuthenticationName[];
extern const char kEapGtcWifiAuthenticationDescription[];

extern const char kEcheSWAName[];
extern const char kEcheSWADescription[];

extern const char kEcheLauncherName[];
extern const char kEcheLauncherDescription[];

extern const char kEcheLauncherListViewName[];
extern const char kEcheLauncherListViewDescription[];

extern const char kEcheLauncherIconsInMoreAppsButtonName[];
extern const char kEcheLauncherIconsInMoreAppsButtonDescription[];

extern const char kEcheSWADebugModeName[];
extern const char kEcheSWADebugModeDescription[];

extern const char kEcheSWAMeasureLatencyName[];
extern const char kEcheSWAMeasureLatencyDescription[];

extern const char kEcheSWASendStartSignalingName[];
extern const char kEcheSWASendStartSignalingDescription[];

extern const char kEcheSWADisableStunServerName[];
extern const char kEcheSWADisableStunServerDescription[];

extern const char kEcheSWACheckAndroidNetworkInfoName[];
extern const char kEcheSWACheckAndroidNetworkInfoDescription[];

extern const char kEcheSWAProcessAndroidAccessibilityTreeName[];
extern const char kEcheSWAProcessAndroidAccessibilityTreeDescription[];

extern const char kEnableOAuthIppName[];
extern const char kEnableOAuthIppDescription[];

extern const char kEnableOngoingProcessesName[];
extern const char kEnableOngoingProcessesDescription[];

extern const char kPanelSelfRefresh2Name[];
extern const char kPanelSelfRefresh2Description[];

extern const char kEnableVariableRefreshRateName[];
extern const char kEnableVariableRefreshRateDescription[];

extern const char kEnterOverviewFromWallpaperName[];
extern const char kEnterOverviewFromWallpaperDescription[];

extern const char kEolIncentiveName[];
extern const char kEolIncentiveDescription[];

extern const char kEolResetDismissedPrefsName[];
extern const char kEolResetDismissedPrefsDescription[];

extern const char kEventBasedLogUpload[];
extern const char kEventBasedLogUploadDescription[];

extern const char kExcludeDisplayInMirrorModeName[];
extern const char kExcludeDisplayInMirrorModeDescription[];

extern const char kExoGamepadVibrationName[];
extern const char kExoGamepadVibrationDescription[];

extern const char kExoOrdinalMotionName[];
extern const char kExoOrdinalMotionDescription[];

extern const char kExperimentalAccessibilityDictationContextCheckingName[];
extern const char
    kExperimentalAccessibilityDictationContextCheckingDescription[];

extern const char kExperimentalAccessibilityGoogleTtsHighQualityVoicesName[];
extern const char
    kExperimentalAccessibilityGoogleTtsHighQualityVoicesDescription[];

extern const char kExperimentalAccessibilityManifestV3Name[];
extern const char kExperimentalAccessibilityManifestV3Description[];

extern const char kAccessibilityManifestV3BrailleImeName[];
extern const char kAccessibilityManifestV3BrailleImeDescription[];

extern const char kAccessibilityManifestV3EnhancedNetworkTtsName[];
extern const char kAccessibilityManifestV3EnhancedNetworkTtsDescription[];

extern const char kExperimentalAccessibilitySwitchAccessTextName[];
extern const char kExperimentalAccessibilitySwitchAccessTextDescription[];

extern const char kExposeOutOfProcessVideoDecodingToLacrosName[];
extern const char kExposeOutOfProcessVideoDecodingToLacrosDescription[];

extern const char kFastDrmMasterDropName[];
extern const char kFastDrmMasterDropDescription[];

extern const char kFileTransferEnterpriseConnectorName[];
extern const char kFileTransferEnterpriseConnectorDescription[];

extern const char kFileTransferEnterpriseConnectorUIName[];
extern const char kFileTransferEnterpriseConnectorUIDescription[];

extern const char kFilesConflictDialogName[];
extern const char kFilesConflictDialogDescription[];

extern const char kFilesKernelDriversName[];
extern const char kFilesKernelDriversDescription[];

extern const char kFilesExtractArchiveName[];
extern const char kFilesExtractArchiveDescription[];

extern const char kFilesLocalImageSearchName[];
extern const char kFilesLocalImageSearchDescription[];

extern const char kFilesMaterializedViewsName[];
extern const char kFilesMaterializedViewsDescription[];

extern const char kFilesSinglePartitionFormatName[];
extern const char kFilesSinglePartitionFormatDescription[];

extern const char kFilesTrashAutoCleanupName[];
extern const char kFilesTrashAutoCleanupDescription[];

extern const char kFilesTrashDriveName[];
extern const char kFilesTrashDriveDescription[];

extern const char kFileSystemProviderCloudFileSystemName[];
extern const char kFileSystemProviderCloudFileSystemDescription[];

extern const char kFileSystemProviderContentCacheName[];
extern const char kFileSystemProviderContentCacheDescription[];

extern const char kFirmwareUpdateUIV2Name[];
extern const char kFirmwareUpdateUIV2Description[];

extern const char kFirstPartyVietnameseInputName[];
extern const char kFirstPartyVietnameseInputDescription[];

extern const char kFocusFollowsCursorName[];
extern const char kFocusFollowsCursorDescription[];

extern const char kFocusModeName[];
extern const char kFocusModeDescription[];

extern const char kFocusModeYTMName[];
extern const char kFocusModeYTMDescription[];

extern const char kFuseBoxDebugName[];
extern const char kFuseBoxDebugDescription[];

extern const char kGameDashboardGamepadSupport[];
extern const char kGameDashboardGamepadSupportDescription[];

extern const char kGameDashboardGamePWAs[];
extern const char kGameDashboardGamePWAsDescription[];

extern const char kGameDashboardGamesInTest[];
extern const char kGameDashboardGamesInTestDescription[];

extern const char kGameDashboardUtilities[];
extern const char kGameDashboardUtilitiesDescription[];

extern const char kAppLaunchShortcut[];
extern const char kAppLaunchShortcutDescription[];

extern const char kGlanceablesTimeManagementClassroomStudentViewName[];
extern const char kGlanceablesTimeManagementClassroomStudentViewDescription[];

extern const char kGlanceablesTimeManagementTasksViewName[];
extern const char kGlanceablesTimeManagementTasksViewDescription[];

extern const char kHelpAppAppDetailPageName[];
extern const char kHelpAppAppDetailPageDescription[];

extern const char kHelpAppAppsListName[];
extern const char kHelpAppAppsListDescription[];

extern const char kHelpAppAutoTriggerInstallDialogName[];
extern const char kHelpAppAutoTriggerInstallDialogDescription[];

extern const char kHelpAppHomePageAppArticlesName[];
extern const char kHelpAppHomePageAppArticlesDescription[];

extern const char kHelpAppLauncherSearchName[];
extern const char kHelpAppLauncherSearchDescription[];

extern const char kHelpAppOnboardingRevampName[];
extern const char kHelpAppOnboardingRevampDescription[];

extern const char kHelpAppOpensInsteadOfReleaseNotesNotificationName[];
extern const char kHelpAppOpensInsteadOfReleaseNotesNotificationDescription[];

extern const char kHoldingSpaceSuggestionsName[];
extern const char kHoldingSpaceSuggestionsDescription[];

extern const char kHotspotName[];
extern const char kHotspotDescription[];

extern const char kImeAssistMultiWordName[];
extern const char kImeAssistMultiWordDescription[];

extern const char kImeFstDecoderParamsUpdateName[];
extern const char kImeFstDecoderParamsUpdateDescription[];

extern const char kImeKoreanOnlyModeSwitchOnRightAltName[];
extern const char kImeKoreanOnlyModeSwitchOnRightAltDescription[];

extern const char kImeSwitchCheckConnectionStatusName[];
extern const char kImeSwitchCheckConnectionStatusDescription[];

extern const char kIppFirstSetupForUsbPrintersName[];
extern const char kIppFirstSetupForUsbPrintersDescription[];

extern const char kHindiInscriptLayoutName[];
extern const char kHindiInscriptLayoutDescription[];

extern const char kImeSystemEmojiPickerGIFSupportName[];
extern const char kImeSystemEmojiPickerGIFSupportDescription[];

extern const char kImeSystemEmojiPickerJellySupportName[];
extern const char kImeSystemEmojiPickerJellySupportDescription[];

extern const char kImeSystemEmojiPickerMojoSearchName[];
extern const char kImeSystemEmojiPickerMojoSearchDescription[];

extern const char kImeSystemEmojiPickerVariantGroupingName[];
extern const char kImeSystemEmojiPickerVariantGroupingDescription[];

extern const char kImeUsEnglishModelUpdateName[];
extern const char kImeUsEnglishModelUpdateDescription[];

extern const char kCrosComponentsName[];
extern const char kCrosComponentsDescription[];

extern const char kLanguagePacksInSettingsName[];
extern const char kLanguagePacksInSettingsDescription[];

extern const char kUseMlServiceForNonLongformHandwritingOnAllBoardsName[];
extern const char
    kUseMlServiceForNonLongformHandwritingOnAllBoardsDescription[];

extern const char kLauncherContinueSectionWithRecentsName[];
extern const char kLauncherContinueSectionWithRecentsDescription[];

extern const char kLauncherItemSuggestName[];
extern const char kLauncherItemSuggestDescription[];

extern const char kLimitShelfItemsToActiveDeskName[];
extern const char kLimitShelfItemsToActiveDeskDescription[];

extern const char kListAllDisplayModesName[];
extern const char kListAllDisplayModesDescription[];

extern const char kEnableHardwareMirrorModeName[];
extern const char kEnableHardwareMirrorModeDescription[];

extern const char kLockScreenNotificationName[];
extern const char kLockScreenNotificationDescription[];

extern const char kMahiName[];
extern const char kMahiDescription[];

extern const char kMahiPanelResizableName[];
extern const char kMahiPanelResizableDescription[];

extern const char kMahiSummarizeSelectedName[];
extern const char kMahiSummarizeSelectedDescription[];

extern const char kMahiDebuggingName[];
extern const char kMahiDebuggingDescription[];

extern const char kMediaAppPdfMahiName[];
extern const char kMediaAppPdfMahiDescription[];

extern const char kMicrophoneMuteSwitchDeviceName[];
extern const char kMicrophoneMuteSwitchDeviceDescription[];

extern const char kMultiCalendarSupportName[];
extern const char kMultiCalendarSupportDescription[];

extern const char kMultiZoneRgbKeyboardName[];
extern const char kMultiZoneRgbKeyboardDescription[];

extern const char kNotificationWidthIncreaseName[];
extern const char kNotificationWidthIncreaseDescription[];

extern const char kEnableNearbyBleV2Name[];
extern const char kEnableNearbyBleV2Description[];

extern const char kEnableNearbyBleV2ExtendedAdvertisingName[];
extern const char kEnableNearbyBleV2ExtendedAdvertisingDescription[];

extern const char kEnableNearbyBleV2GattServerName[];
extern const char kEnableNearbyBleV2GattServerDescription[];

extern const char kEnableNearbyBluetoothClassicAdvertisingName[];
extern const char kEnableNearbyBluetoothClassicAdvertisingDescription[];

extern const char kEnableNearbyMdnsName[];
extern const char kEnableNearbyMdnsDescription[];

extern const char kEnableNearbyWebRtcName[];
extern const char kEnableNearbyWebRtcDescription[];

extern const char kEnableNearbyWifiDirectName[];
extern const char kEnableNearbyWifiDirectDescription[];

extern const char kEnableNearbyWifiLanName[];
extern const char kEnableNearbyWifiLanDescription[];

extern const char kNearbyPresenceName[];
extern const char kNearbyPresenceDescription[];

extern const char kNotificationsIgnoreRequireInteractionName[];
extern const char kNotificationsIgnoreRequireInteractionDescription[];

extern const char kOnDeviceAppControlsName[];
extern const char kOnDeviceAppControlsDescription[];

extern const char kPcieBillboardNotificationName[];
extern const char kPcieBillboardNotificationDescription[];

extern const char kPerformantSplitViewResizing[];
extern const char kPerformantSplitViewResizingDescription[];

extern const char kPhoneHubCallNotificationName[];
extern const char kPhoneHubCallNotificationDescription[];

extern const char kPompanoName[];
extern const char kPompanoDescritpion[];

extern const char kPrintingPpdChannelName[];
extern const char kPrintingPpdChannelDescription[];

extern const char kPrintPreviewCrosAppName[];
extern const char kPrintPreviewCrosAppDescription[];

extern const char kProductivityLauncherImageSearchName[];
extern const char kProductivityLauncherImageSearchDescription[];

extern const char kProjectorAppDebugName[];
extern const char kProjectorAppDebugDescription[];

extern const char kProjectorGm3Name[];
extern const char kProjectorGm3Description[];

extern const char kProjectorServerSideSpeechRecognitionName[];
extern const char kProjectorServerSideSpeechRecognitionDescription[];

extern const char kProjectorServerSideUsmName[];
extern const char kProjectorServerSideUsmDescription[];

extern const char kProjectorUseDVSPlaybackEndpointName[];
extern const char kProjectorUseDVSPlaybackEndpointDescription[];

extern const char kReleaseNotesNotificationAllChannelsName[];
extern const char kReleaseNotesNotificationAllChannelsDescription[];

extern const char kReleaseNotesNotificationAlwaysEligibleName[];
extern const char kReleaseNotesNotificationAlwaysEligibleDescription[];

extern const char kRenderArcNotificationsByChromeName[];
extern const char kRenderArcNotificationsByChromeDescription[];

extern const char kRunVideoCaptureServiceInBrowserProcessName[];
extern const char kRunVideoCaptureServiceInBrowserProcessDescription[];

extern const char kArcWindowPredictorName[];
extern const char kArcWindowPredictorDescription[];

extern const char kScalableIphDebugName[];
extern const char kScalableIphDebugDescription[];

extern const char kSealKeyName[];
extern const char kSealKeyDescription[];

extern const char kSeaPenName[];
extern const char kSeaPenDescription[];

extern const char kShelfAutoHideSeparationName[];
extern const char kShelfAutoHideSeparationDescription[];

extern const char kShimlessRMAAproUpdateRootfsName[];
extern const char kShimlessRMAAproUpdateRootfsDescription[];

extern const char kShimlessRMAOsUpdateName[];
extern const char kShimlessRMAOsUpdateDescription[];

extern const char kSchedulerConfigurationName[];
extern const char kSchedulerConfigurationDescription[];

extern const char kSchedulerConfigurationConservative[];
extern const char kSchedulerConfigurationPerformance[];

extern const char kSnapGroupsName[];
extern const char kSnapGroupsDescription[];

extern const char kMediaDynamicCgroupName[];
extern const char kMediaDynamicCgroupDescription[];

extern const char kMissiveStorageName[];
extern const char kMissiveStorageDescription[];

extern const char kShowBluetoothDebugLogToggleName[];
extern const char kShowBluetoothDebugLogToggleDescription[];

extern const char kShowTapsName[];
extern const char kShowTapsDescription[];

extern const char kShowTouchHudName[];
extern const char kShowTouchHudDescription[];

extern const char kSnoopingProtectionName[];
extern const char kSnoopingProtectionDescription[];

extern const char kContinuousOverviewScrollAnimationName[];
extern const char kContinuousOverviewScrollAnimationDescription[];

extern const char kSpectreVariant2MitigationName[];
extern const char kSpectreVariant2MitigationDescription[];

extern const char kSystemJapanesePhysicalTypingName[];
extern const char kSystemJapanesePhysicalTypingDescription[];

extern const char kSupportF11AndF12ShortcutsName[];
extern const char kSupportF11AndF12ShortcutsDescription[];

extern const char kTerminalDevName[];
extern const char kTerminalDevDescription[];

extern const char kTetherName[];
extern const char kTetherDescription[];

extern const char kTilingWindowResizeName[];
extern const char kTilingWindowResizeDescription[];

extern const char kTouchscreenCalibrationName[];
extern const char kTouchscreenCalibrationDescription[];

extern const char kTouchscreenMappingName[];
extern const char kTouchscreenMappingDescription[];

extern const char kTrafficCountersEnabledName[];
extern const char kTrafficCountersEnabledDescription[];

extern const char kTrafficCountersForWiFiTestingName[];
extern const char kTrafficCountersForWiFiTestingDescription[];

extern const char kUiDevToolsName[];
extern const char kUiDevToolsDescription[];

extern const char kUiSlowAnimationsName[];
extern const char kUiSlowAnimationsDescription[];

extern const char kUploadOfficeToCloudName[];
extern const char kUploadOfficeToCloudDescription[];

extern const char kUseAnnotatedAccountIdName[];
extern const char kUseAnnotatedAccountIdDescription[];

extern const char kUseFakeDeviceForMediaStreamName[];
extern const char kUseFakeDeviceForMediaStreamDescription[];

extern const char kUseLegacyDHCPCDName[];
extern const char kUseLegacyDHCPCDDescription[];

extern const char kUseManagedPrintJobOptionsInPrintPreviewName[];
extern const char kUseManagedPrintJobOptionsInPrintPreviewDescription[];

extern const char kVcDlcUiName[];
extern const char kVcDlcUiDescription[];

extern const char kVirtualKeyboardName[];
extern const char kVirtualKeyboardDescription[];

extern const char kVirtualKeyboardDisabledName[];
extern const char kVirtualKeyboardDisabledDescription[];

extern const char kVirtualKeyboardGlobalEmojiPreferencesName[];
extern const char kVirtualKeyboardGlobalEmojiPreferencesDescription[];

extern const char kWakeOnWifiAllowedName[];
extern const char kWakeOnWifiAllowedDescription[];

extern const char kWelcomeExperienceName[];
extern const char kWelcomeExperienceDescription[];

extern const char kWelcomeExperienceTestUnsupportedDevicesName[];
extern const char kWelcomeExperienceTestUnsupportedDevicesDescription[];

extern const char kWelcomeTourName[];
extern const char kWelcomeTourDescription[];

extern const char kWelcomeTourForceUserEligibilityName[];
extern const char kWelcomeTourForceUserEligibilityDescription[];

extern const char kWifiConnectMacAddressRandomizationName[];
extern const char kWifiConnectMacAddressRandomizationDescription[];

extern const char kWifiConcurrencyName[];
extern const char kWifiConcurrencyDescription[];

extern const char kWifiDirectName[];
extern const char kWifiDirectDescription[];

extern const char kWindowSplittingName[];
extern const char kWindowSplittingDescription[];

extern const char kLauncherKeyShortcutInBestMatchName[];
extern const char kLauncherKeyShortcutInBestMatchDescription[];

extern const char kLauncherKeywordExtractionScoring[];
extern const char kLauncherKeywordExtractionScoringDescription[];

extern const char kLauncherLocalImageSearchName[];
extern const char kLauncherLocalImageSearchDescription[];

extern const char kLauncherLocalImageSearchConfidenceName[];
extern const char kLauncherLocalImageSearchConfidenceDescription[];

extern const char kLauncherLocalImageSearchRelevanceName[];
extern const char kLauncherLocalImageSearchRelevanceDescription[];

extern const char kLauncherLocalImageSearchOcrName[];
extern const char kLauncherLocalImageSearchOcrDescription[];

extern const char kLauncherLocalImageSearchIcaName[];
extern const char kLauncherLocalImageSearchIcaDescription[];

extern const char kLauncherSearchControlName[];
extern const char kLauncherSearchControlDescription[];

extern const char kLauncherNudgeSessionResetName[];
extern const char kLauncherNudgeSessionResetDescription[];

extern const char kLauncherSystemInfoAnswerCardsName[];
extern const char kLauncherSystemInfoAnswerCardsDescription[];

extern const char kMacAddressRandomizationName[];
extern const char kMacAddressRandomizationDescription[];

extern const char kSysUiShouldHoldbackDriveIntegrationName[];
extern const char kSysUiShouldHoldbackDriveIntegrationDescription[];

extern const char kSysUiShouldHoldbackFocusModeName[];
extern const char kSysUiShouldHoldbackFocusModeDescription[];

extern const char kSysUiShouldHoldbackForestName[];
extern const char kSysUiShouldHoldbackForestDescription[];

extern const char kSysUiShouldHoldbackTaskManagementName[];
extern const char kSysUiShouldHoldbackTaskManagementDescription[];

extern const char kTetheringExperimentalFunctionalityName[];
extern const char kTetheringExperimentalFunctionalityDescription[];

// Prefer keeping this section sorted to adding new declarations down here.

#endif  // #if BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_LINUX)
extern const char kGetAllScreensMediaName[];
extern const char kGetAllScreensMediaDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_LINUX)

#if BUILDFLAG(IS_CHROMEOS)
extern const char kAddPrinterViaPrintscanmgrName[];
extern const char kAddPrinterViaPrintscanmgrDescription[];

extern const char kCrosAppsBackgroundEventHandlingName[];
extern const char kCrosAppsBackgroundEventHandlingDescription[];

extern const char kRunOnOsLoginName[];
extern const char kRunOnOsLoginDescription[];

extern const char kPreventCloseName[];
extern const char kPreventCloseDescription[];

extern const char kFileSystemAccessGetCloudIdentifiersName[];
extern const char kFileSystemAccessGetCloudIdentifiersDescription[];

extern const char kCrOSDspBasedAecAllowedName[];
extern const char kCrOSDspBasedAecAllowedDescription[];

extern const char kCrOSDspBasedNsAllowedName[];
extern const char kCrOSDspBasedNsAllowedDescription[];

extern const char kCrOSDspBasedAgcAllowedName[];
extern const char kCrOSDspBasedAgcAllowedDescription[];

extern const char kCrosMallName[];
extern const char kCrosMallDescription[];

extern const char kCrosMallManagedName[];
extern const char kCrosMallManagedDescription[];

extern const char kCrosMallUrlName[];
extern const char kCrosMallUrlDescription[];

extern const char kCrosPrivacyHubName[];
extern const char kCrosPrivacyHubDescription[];

extern const char kCrosPrivacyHubAppPermissionsV2Name[];
extern const char kCrosPrivacyHubAppPermissionsV2Description[];
=======
extern const char kEnableAppGridGhostName[];
extern const char kEnableAppGridGhostDescription[];
>>>>>>> chromium

extern const char kCrOSEnforceSystemAecName[];
extern const char kCrOSEnforceSystemAecDescription[];

extern const char kCrOSEnforceSystemAecAgcName[];
extern const char kCrOSEnforceSystemAecAgcDescription[];

extern const char kCrOSEnforceSystemAecNsName[];
extern const char kCrOSEnforceSystemAecNsDescription[];

extern const char kCrOSEnforceSystemAecNsAgcName[];
extern const char kCrOSEnforceSystemAecNsAgcDescription[];

extern const char kEnableAppReinstallZeroStateName[];
extern const char kEnableAppReinstallZeroStateDescription[];

extern const char kEnableArcUnifiedAudioFocusName[];
extern const char kEnableArcUnifiedAudioFocusDescription[];

extern const char kEnableAssistantAppSupportName[];
extern const char kEnableAssistantAppSupportDescription[];

extern const char kEnableAssistantBetterOnboardingName[];
extern const char kEnableAssistantBetterOnboardingDescription[];

<<<<<<< HEAD
extern const char kPlatformKeysChangesWave1Name[];
extern const char kPlatformKeysChangesWave1Description[];
=======
extern const char kEnableAssistantLauncherIntegrationName[];
extern const char kEnableAssistantLauncherIntegrationDescription[];
>>>>>>> chromium

extern const char kEnableAssistantLauncherUIName[];
extern const char kEnableAssistantLauncherUIDescription[];

extern const char kEnableAssistantRoutinesName[];
extern const char kEnableAssistantRoutinesDescription[];

extern const char kEnableAutoSelectName[];
extern const char kEnableAutoSelectDescription[];

extern const char kEnableBackgroundBlurName[];
extern const char kEnableBackgroundBlurDescription[];

extern const char kEnhancedClipboardName[];
extern const char kEnhancedClipboardDescription[];

extern const char kEnhancedClipboardNudgeSessionResetName[];
extern const char kEnhancedClipboardNudgeSessionResetDescription[];

extern const char kEnhancedClipboardScreenshotNudgeName[];
extern const char kEnhancedClipboardScreenshotNudgeDescription[];

extern const char kEnableCrOSActionRecorderName[];
extern const char kEnableCrOSActionRecorderDescription[];

extern const char kEnableDnsProxyName[];
extern const char kEnableDnsProxyDescription[];

<<<<<<< HEAD
extern const char kShowSpatialAudioToggleName[];
extern const char kShowSpatialAudioToggleDescription[];

extern const char kSingleCaCertVerificationPhase0Name[];
extern const char kSingleCaCertVerificationPhase0Description[];

extern const char kSingleCaCertVerificationPhase1Name[];
extern const char kSingleCaCertVerificationPhase1Description[];

extern const char kSingleCaCertVerificationPhase2Name[];
extern const char kSingleCaCertVerificationPhase2Description[];
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
extern const char kDnsProxyEnableDOHName[];
extern const char kDnsProxyEnableDOHDescription[];

extern const char kEnableHostnameSettingName[];
extern const char kEnableHostnameSettingDescription[];
>>>>>>> chromium

extern const char kEnableGeneratedWebApksName[];
extern const char kEnableGeneratedWebApksDescription[];

extern const char kEnableGesturePropertiesDBusServiceName[];
extern const char kEnableGesturePropertiesDBusServiceDescription[];

extern const char kEnableGoogleAssistantDspName[];
extern const char kEnableGoogleAssistantDspDescription[];

extern const char kEnableGoogleAssistantStereoInputName[];
extern const char kEnableGoogleAssistantStereoInputDescription[];

extern const char kEnableGoogleAssistantAecName[];
extern const char kEnableGoogleAssistantAecDescription[];

extern const char kEnableHeuristicStylusPalmRejectionName[];
extern const char kEnableHeuristicStylusPalmRejectionDescription[];

extern const char kEnableInputEventLoggingName[];
extern const char kEnableInputEventLoggingDescription[];

extern const char kEnableInputInDiagnosticsAppName[];
extern const char kEnableInputInDiagnosticsAppDescription[];

extern const char kEnableInputNoiseCancellationUiName[];
extern const char kEnableInputNoiseCancellationUiDescription[];

extern const char kEnableLauncherSearchNormalizationName[];
extern const char kEnableLauncherSearchNormalizationDescription[];

extern const char kNewDragSpecInLauncherName[];
extern const char kNewDragSpecInLauncherDescription[];

extern const char kEnableNeuralStylusPalmRejectionName[];
extern const char kEnableNeuralStylusPalmRejectionDescription[];

extern const char kEnableOsFeedbackName[];
extern const char kEnableOsFeedbackDescription[];

extern const char kEnableNewShortcutMappingName[];
extern const char kEnableNewShortcutMappingDescription[];

extern const char kEnablePalmOnMaxTouchMajorName[];
extern const char kEnablePalmOnMaxTouchMajorDescription[];

extern const char kEnablePalmOnToolTypePalmName[];
extern const char kEnablePalmOnToolTypePalmDescription[];

extern const char kEnablePalmSuppressionName[];
extern const char kEnablePalmSuppressionDescription[];

extern const char kEnablePlayStoreSearchName[];
extern const char kEnablePlayStoreSearchDescription[];

extern const char kEnableQuickAnswersName[];
extern const char kEnableQuickAnswersDescription[];

extern const char kEnableQuickAnswersOnEditableTextName[];
extern const char kEnableQuickAnswersOnEditableTextDescription[];

extern const char kEnableQuickAnswersRichUiName[];
extern const char kEnableQuickAnswersRichUiDescription[];

extern const char kEnableQuickAnswersTextAnnotatorName[];
extern const char kEnableQuickAnswersTextAnnotatorDescription[];

extern const char kEnableQuickAnswersTranslationName[];
extern const char kEnableQuickAnswersTranslationDescription[];

extern const char kEnableQuickAnswersTranslationCloudAPIName[];
extern const char kEnableQuickAnswersTranslationCloudAPIDescription[];

extern const char kEnableQuickAnswersV2Name[];
extern const char kEnableQuickAnswersV2Description[];

extern const char kPluginVmFullscreenName[];
extern const char kPluginVmFullscreenDescription[];

extern const char kTrimOnFreezeName[];
extern const char kTrimOnFreezeDescription[];

extern const char kTrimOnMemoryPressureName[];
extern const char kTrimOnMemoryPressureDescription[];

extern const char kEcheSWAName[];
extern const char kEcheSWADescription[];

extern const char kEcheSWAResizingName[];
extern const char kEcheSWAResizingDescription[];

extern const char kEnableNetworkingInDiagnosticsAppName[];
extern const char kEnableNetworkingInDiagnosticsAppDescription[];

extern const char kEnableOAuthIppName[];
extern const char kEnableOAuthIppDescription[];

extern const char kEnableSuggestedFilesName[];
extern const char kEnableSuggestedFilesDescription[];

extern const char kExoGamepadVibrationName[];
extern const char kExoGamepadVibrationDescription[];

extern const char kExoOrdinalMotionName[];
extern const char kExoOrdinalMotionDescription[];

extern const char kExoPointerLockName[];
extern const char kExoPointerLockDescription[];

extern const char kExoLockNotificationName[];
extern const char kExoLockNotificationDescription[];

extern const char kExperimentalAccessibilityDictationExtensionName[];
extern const char kExperimentalAccessibilityDictationExtensionDescription[];

extern const char kExperimentalAccessibilityDictationListeningName[];
extern const char kExperimentalAccessibilityDictationListeningDescription[];

extern const char kExperimentalAccessibilityDictationOfflineName[];
extern const char kExperimentalAccessibilityDictationOfflineDescription[];

extern const char kExperimentalAccessibilitySwitchAccessTextName[];
extern const char kExperimentalAccessibilitySwitchAccessTextDescription[];

extern const char kSwitchAccessPointScanningName[];
extern const char kSwitchAccessPointScanningDescription[];

extern const char kExperimentalAccessibilitySwitchAccessSetupGuideName[];
extern const char kExperimentalAccessibilitySwitchAccessSetupGuideDescription[];

extern const char kMagnifierPanningImprovementsName[];
extern const char kMagnifierPanningImprovementsDescription[];

extern const char kMagnifierContinuousMouseFollowingModeSettingName[];
extern const char kMagnifierContinuousMouseFollowingModeSettingDescription[];

extern const char kFilesArchivemountName[];
extern const char kFilesArchivemountDescription[];

extern const char kFilesBannerFrameworkName[];
extern const char kFilesBannerFrameworkDescription[];

extern const char kFilesSinglePartitionFormatName[];
extern const char kFilesSinglePartitionFormatDescription[];

extern const char kFilesSWAName[];
extern const char kFilesSWADescription[];

extern const char kFilesTrashName[];
extern const char kFilesTrashDescription[];

extern const char kFilesZipMountName[];
extern const char kFilesZipMountDescription[];

extern const char kFilesZipPackName[];
extern const char kFilesZipPackDescription[];

extern const char kFilesZipUnpackName[];
extern const char kFilesZipUnpackDescription[];

extern const char kFiltersInRecentsName[];
extern const char kFiltersInRecentsDescription[];

extern const char kFocusFollowsCursorName[];
extern const char kFocusFollowsCursorDescription[];

extern const char kFrameThrottleFpsName[];
extern const char kFrameThrottleFpsDescription[];
extern const char kFrameThrottleFpsDefault[];
extern const char kFrameThrottleFps5[];
extern const char kFrameThrottleFps10[];
extern const char kFrameThrottleFps15[];
extern const char kFrameThrottleFps20[];
extern const char kFrameThrottleFps25[];
extern const char kFrameThrottleFps30[];

extern const char kFullRestoreName[];
extern const char kFullRestoreDescription[];

extern const char kHelpAppBackgroundPageName[];
extern const char kHelpAppBackgroundPageDescription[];

extern const char kHelpAppDiscoverTabName[];
extern const char kHelpAppDiscoverTabDescription[];

extern const char kHelpAppLauncherSearchName[];
extern const char kHelpAppLauncherSearchDescription[];

extern const char kHelpAppSearchServiceIntegrationName[];
extern const char kHelpAppSearchServiceIntegrationDescription[];

extern const char kHideArcMediaNotificationsName[];
extern const char kHideArcMediaNotificationsDescription[];

extern const char kHoldingSpaceInProgressDownloadsIntegrationName[];
extern const char kHoldingSpaceInProgressDownloadsIntegrationDescription[];

extern const char kImeAssistAutocorrectName[];
extern const char kImeAssistAutocorrectDescription[];

extern const char kImeAssistEmojiEnhancedName[];
extern const char kImeAssistEmojiEnhancedDescription[];

extern const char kImeAssistMultiWordName[];
extern const char kImeAssistMultiWordDescription[];

extern const char kImeAssistMultiWordExpandedName[];
extern const char kImeAssistMultiWordExpandedDescription[];

extern const char kImeAssistPersonalInfoName[];
extern const char kImeAssistPersonalInfoDescription[];

extern const char kImeEmojiSuggestAdditionName[];
extern const char kImeEmojiSuggestAdditionDescription[];

extern const char kImeMozcProtoName[];
extern const char kImeMozcProtoDescription[];

extern const char kImeServiceDecoderName[];
extern const char kImeServiceDecoderDescription[];

extern const char kCrosLanguageSettingsImeOptionsInSettingsName[];
extern const char kCrosLanguageSettingsImeOptionsInSettingsDescription[];

extern const char kImeSystemEmojiPickerName[];
extern const char kImeSystemEmojiPickerDescription[];

extern const char kImeSystemEmojiPickerClipboardName[];
extern const char kImeSystemEmojiPickerClipboardDescription[];

extern const char kIntentHandlingSharingName[];
extern const char kIntentHandlingSharingDescription[];

extern const char kIntentPickerPWAPersistenceName[];
extern const char kIntentPickerPWAPersistenceDescription[];

extern const char kKeyboardBasedDisplayArrangementInSettingsName[];
extern const char kKeyboardBasedDisplayArrangementInSettingsDescription[];

extern const char kLacrosAvailabilityIgnoreName[];
extern const char kLacrosAvailabilityIgnoreDescription[];

extern const char kLacrosPrimaryName[];
extern const char kLacrosPrimaryDescription[];

extern const char kLacrosStabilityName[];
extern const char kLacrosStabilityDescription[];
extern const char kLacrosStabilityLeastStableDescription[];
extern const char kLacrosStabilityLessStableDescription[];
extern const char kLacrosStabilityMoreStableDescription[];

extern const char kLacrosSelectionName[];
extern const char kLacrosSelectionDescription[];
extern const char kLacrosSelectionRootfsDescription[];
extern const char kLacrosSelectionStatefulDescription[];

extern const char kLacrosSupportName[];
extern const char kLacrosSupportDescription[];

extern const char kLauncherQueryHighlightingName[];
extern const char kLauncherQueryHighlightingDescription[];

extern const char kLimitAltTabToActiveDeskName[];
extern const char kLimitAltTabToActiveDeskDescription[];

extern const char kLimitShelfItemsToActiveDeskName[];
extern const char kLimitShelfItemsToActiveDeskDescription[];

extern const char kListAllDisplayModesName[];
extern const char kListAllDisplayModesDescription[];

extern const char kEnableHardwareMirrorModeName[];
extern const char kEnableHardwareMirrorModeDescription[];

extern const char kLockScreenMediaControlsName[];
extern const char kLockScreenMediaControlsDescription[];

extern const char kLockScreenNotificationName[];
extern const char kLockScreenNotificationDescription[];

extern const char kMediaAppAnnotationName[];
extern const char kMediaAppAnnotationDescription[];

extern const char kMediaAppDisplayExifName[];
extern const char kMediaAppDisplayExifDescription[];

extern const char kMediaAppHandlesPdfName[];
extern const char kMediaAppHandlesPdfDescription[];

extern const char kMediaAppVideoName[];
extern const char kMediaAppVideoDescription[];

extern const char kMeteredShowToggleName[];
extern const char kMeteredShowToggleDescription[];

extern const char kMicrophoneMuteNotificationsName[];
extern const char kMicrophoneMuteNotificationsDescription[];

extern const char kMicrophoneMuteSwitchDeviceName[];
extern const char kMicrophoneMuteSwitchDeviceDescription[];

extern const char kMultilingualTypingName[];
extern const char kMultilingualTypingDescription[];

extern const char kNearbyKeepAliveFixName[];
extern const char kNearbyKeepAliveFixDescription[];

extern const char kNearbySharingName[];
extern const char kNearbySharingDescription[];

extern const char kNearbySharingBackgroundScanningName[];
extern const char kNearbySharingBackgroundScanningDescription[];

extern const char kNearbySharingDeviceContactsName[];
extern const char kNearbySharingDeviceContactsDescription[];

extern const char kNearbySharingWebRtcName[];
extern const char kNearbySharingWebRtcDescription[];

extern const char kPerformantSplitViewResizing[];
extern const char kPerformantSplitViewResizingDescription[];

extern const char kPhoneHubCameraRollName[];
extern const char kPhoneHubCameraRollDescription[];

extern const char kPhoneHubRecentAppsName[];
extern const char kPhoneHubRecentAppsDescription[];

extern const char kReduceDisplayNotificationsName[];
extern const char kReduceDisplayNotificationsDescription[];

extern const char kReleaseNotesNotificationName[];
extern const char kReleaseNotesNotificationDescription[];

extern const char kReleaseNotesNotificationAllChannelsName[];
extern const char kReleaseNotesNotificationAllChannelsDescription[];

extern const char kArcGhostWindowName[];
extern const char kArcGhostWindowDescription[];

extern const char kArcResizeLockName[];
extern const char kArcResizeLockDescription[];

extern const char kScanAppMediaLinkName[];
extern const char kScanAppMediaLinkDescription[];

extern const char kScanAppMultiPageScanName[];
extern const char kScanAppMultiPageScanDescription[];

extern const char kScanAppSearchablePdfName[];
extern const char kScanAppSearchablePdfDescription[];

extern const char kScanAppStickySettingsName[];
extern const char kScanAppStickySettingsDescription[];

extern const char kShimlessRMAFlowName[];
extern const char kShimlessRMAFlowDescription[];

extern const char kSchedulerConfigurationName[];
extern const char kSchedulerConfigurationDescription[];
extern const char kSchedulerConfigurationConservative[];
extern const char kSchedulerConfigurationPerformance[];

extern const char kSelectToSpeakNavigationControlName[];
extern const char kSelectToSpeakNavigationControlDescription[];

extern const char kSharesheetContentPreviewsName[];
extern const char kSharesheetContentPreviewsDescription[];

extern const char kSharesheetName[];
extern const char kSharesheetDescription[];

extern const char kChromeOSSharingHubName[];
extern const char kChromeOSSharingHubDescription[];

extern const char kShowBluetoothDebugLogToggleName[];
extern const char kShowBluetoothDebugLogToggleDescription[];

extern const char kBluetoothSessionizedMetricsName[];
extern const char kBluetoothSessionizedMetricsDescription[];

extern const char kShowDateInTrayName[];
extern const char kShowDateInTrayDescription[];

extern const char kShowTapsName[];
extern const char kShowTapsDescription[];

extern const char kShowTouchHudName[];
extern const char kShowTouchHudDescription[];

extern const char kSmartLockUIRevampName[];
extern const char kSmartLockUIRevampDescription[];

extern const char kSpectreVariant2MitigationName[];
extern const char kSpectreVariant2MitigationDescription[];

extern const char kSplitSettingsSyncName[];
extern const char kSplitSettingsSyncDescription[];

extern const char kSystemLatinPhysicalTypingName[];
extern const char kSystemLatinPhysicalTypingDescription[];

extern const char kTetherName[];
extern const char kTetherDescription[];

extern const char kTouchscreenCalibrationName[];
extern const char kTouchscreenCalibrationDescription[];

extern const char kUiDevToolsName[];
extern const char kUiDevToolsDescription[];

extern const char kUiSlowAnimationsName[];
extern const char kUiSlowAnimationsDescription[];

extern const char kUseFakeDeviceForMediaStreamName[];
extern const char kUseFakeDeviceForMediaStreamDescription[];

extern const char kVaapiJpegImageDecodeAccelerationName[];
extern const char kVaapiJpegImageDecodeAccelerationDescription[];

extern const char kVaapiWebPImageDecodeAccelerationName[];
extern const char kVaapiWebPImageDecodeAccelerationDescription[];

extern const char kVirtualKeyboardName[];
extern const char kVirtualKeyboardDescription[];

extern const char kVirtualKeyboardBorderedKeyName[];
extern const char kVirtualKeyboardBorderedKeyDescription[];

extern const char kVirtualKeyboardDisabledName[];
extern const char kVirtualKeyboardDisabledDescription[];

extern const char kVirtualKeyboardMultipasteName[];
extern const char kVirtualKeyboardMultipasteDescription[];

extern const char kVmStatusPageName[];
extern const char kVmStatusPageDescription[];

extern const char kWakeOnWifiAllowedName[];
extern const char kWakeOnWifiAllowedDescription[];

extern const char kWebAppsCrosapiName[];
extern const char kWebAppsCrosapiDescription[];

extern const char kWebuiDarkModeName[];
extern const char kWebuiDarkModeDescription[];

extern const char kWifiSyncAllowDeletesName[];
extern const char kWifiSyncAllowDeletesDescription[];

extern const char kWifiSyncAndroidName[];
extern const char kWifiSyncAndroidDescription[];

// Prefer keeping this section sorted to adding new declarations down here.

#endif  // #if BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS)
extern const char kAllowDefaultWebAppMigrationForChromeOsManagedUsersName[];
extern const char
    kAllowDefaultWebAppMigrationForChromeOsManagedUsersDescription[];

extern const char kDefaultChatWebAppName[];
extern const char kDefaultChatWebAppDescription[];

extern const char kDefaultMeetWebAppName[];
extern const char kDefaultMeetWebAppDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS)

#if defined(OS_CHROMEOS)
extern const char kDeprecateLowUsageCodecsName[];
extern const char kDeprecateLowUsageCodecsDescription[];

extern const char kVaapiAV1DecoderName[];
extern const char kVaapiAV1DecoderDescription[];
#endif  // defined(OS_CHROMEOS)

#if defined(ARCH_CPU_X86_FAMILY) && BUILDFLAG(IS_CHROMEOS_ASH)
extern const char kVaapiVP9kSVCEncoderName[];
extern const char kVaapiVP9kSVCEncoderDescription[];
#endif  // defined(ARCH_CPU_X86_FAMILY) && BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_CHROMEOS) && BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)
extern const char kChromeOSDirectVideoDecoderName[];
extern const char kChromeOSDirectVideoDecoderDescription[];
#endif  // defined(OS_CHROMEOS) && BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)

#if BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC) || defined(OS_WIN)
extern const char kZeroCopyVideoCaptureName[];
extern const char kZeroCopyVideoCaptureDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC) || defined(OS_WIN)

// All views-based platforms --------------------------------------------------

#if defined(TOOLKIT_VIEWS)

extern const char kDesktopInProductHelpSnoozeName[];
extern const char kDesktopInProductHelpSnoozeDescription[];

extern const char kDownloadShelfWebUI[];
extern const char kDownloadShelfWebUIDescription[];

extern const char kEnableMDRoundedCornersOnDialogsName[];
extern const char kEnableMDRoundedCornersOnDialogsDescription[];

extern const char kInstallableInkDropName[];
extern const char kInstallableInkDropDescription[];
#endif  // defined(TOOLKIT_VIEWS)

// Random platform combinations -----------------------------------------------

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
extern const char kZeroCopyVideoCaptureName[];
extern const char kZeroCopyVideoCaptureDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
=======
#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) || \
    defined(OS_CHROMEOS)
>>>>>>> chromium

extern const char kEnableOopPrintDriversName[];
extern const char kEnableOopPrintDriversDescription[];

extern const char kWebUIBrandingUpdateName[];
extern const char kWebUIBrandingUpdateDescription[];

extern const char kWebuiFeedbackName[];
extern const char kWebuiFeedbackDescription[];

extern const char kSettingsLandingPageRedesignName[];
extern const char kSettingsLandingPageRedesignDescription[];

#endif  // defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) ||
        // defined(OS_CHROMEOS)

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)

extern const char kCommanderName[];
extern const char kCommanderDescription[];

extern const char kDesktopRestructuredLanguageSettingsName[];
extern const char kDesktopRestructuredLanguageSettingsDescription[];

extern const char kDesktopDetailedLanguageSettingsName[];
extern const char kDesktopDetailedLanguageSettingsDescription[];

#endif  // defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)

#if defined(OS_CHROMEOS) || defined(OS_LINUX)
#if BUILDFLAG(USE_TCMALLOC)
extern const char kDynamicTcmallocName[];
extern const char kDynamicTcmallocDescription[];
#endif  // BUILDFLAG(USE_TCMALLOC)
#endif  // #if defined(OS_CHROMEOS) || defined(OS_LINUX)

#if !defined(OS_ANDROID) && !BUILDFLAG(IS_CHROMEOS_ASH)
extern const char kUserDataSnapshotName[];
extern const char kUserDataSnapshotDescription[];
#endif  // !defined(OS_ANDROID) && !BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_WIN) || BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC)
extern const char kWebShareName[];
extern const char kWebShareDescription[];
#endif  // defined(OS_WIN) || BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC)

#if defined(OS_LINUX) && defined(USE_OZONE)
extern const char kUseOzonePlatformName[];
extern const char kUseOzonePlatformDescription[];
#endif  // defined(OS_LINUX) && defined(USE_OZONE)

// Feature flags --------------------------------------------------------------

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_PRINTING)
extern const char kCupsIppPrintingBackendName[];
extern const char kCupsIppPrintingBackendDescription[];
#endif  // BUILDFLAG(ENABLE_PRINTING)
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_CHROMEOS)
extern const char kScreenlockReauthCardName[];
extern const char kScreenlockReauthCardDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
extern const char kFollowingFeedSidepanelName[];
extern const char kFollowingFeedSidepanelDescription[];
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) ||
        //  BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
extern const char kTaskManagerClankName[];
extern const char kTaskManagerClankDescription[];
#else
extern const char kTaskManagerDesktopRefreshName[];
extern const char kTaskManagerDesktopRefreshDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
extern const char kEnableNetworkServiceSandboxName[];
extern const char kEnableNetworkServiceSandboxDescription[];

extern const char kUseOutOfProcessVideoDecodingName[];
extern const char kUseOutOfProcessVideoDecodingDescription[];
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(CHROME_WIDE_ECHO_CANCELLATION)
extern const char kChromeWideEchoCancellationName[];
extern const char kChromeWideEchoCancellationDescription[];
#endif  // BUILDFLAG(CHROME_WIDE_ECHO_CANCELLATION)

#if BUILDFLAG(DCHECK_IS_CONFIGURABLE)
=======
#if defined(DCHECK_IS_CONFIGURABLE)
>>>>>>> chromium
extern const char kDcheckIsFatalName[];
extern const char kDcheckIsFatalDescription[];
#endif  // defined(DCHECK_IS_CONFIGURABLE)

#if BUILDFLAG(ENABLE_JXL_DECODER)
extern const char kEnableJXLName[];
extern const char kEnableJXLDescription[];
#endif  // BUILDFLAG(ENABLE_JXL_DECODER)

#if BUILDFLAG(ENABLE_NACL)
extern const char kNaclName[];
extern const char kNaclDescription[];
#endif  // ENABLE_NACL

#if BUILDFLAG(ENABLE_PAINT_PREVIEW) && defined(OS_ANDROID)
extern const char kPaintPreviewDemoName[];
extern const char kPaintPreviewDemoDescription[];
extern const char kPaintPreviewStartupName[];
extern const char kPaintPreviewStartupDescription[];
#endif  // ENABLE_PAINT_PREVIEW && defined(OS_ANDROID)

#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)
extern const char kWebUITabStripName[];
extern const char kWebUITabStripDescription[];
extern const char kWebUITabStripNTBInTabStripName[];
extern const char kWebUITabStripNTBInTabStripDescription[];
#endif  // BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)

#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP) && BUILDFLAG(IS_CHROMEOS_ASH)
extern const char kWebUITabStripTabDragIntegrationName[];
extern const char kWebUITabStripTabDragIntegrationDescription[];
#endif  // BUILDFLAG(ENABLE_WEBUI_TAB_STRIP) && BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(TOOLKIT_VIEWS) || defined(OS_ANDROID)

extern const char kAutofillCreditCardUploadName[];
extern const char kAutofillCreditCardUploadDescription[];

#endif  // defined(TOOLKIT_VIEWS) || defined(OS_ANDROID)

#if !defined(OS_WIN) && !defined(OS_FUCHSIA)
extern const char kSendWebUIJavaScriptErrorReportsName[];
extern const char kSendWebUIJavaScriptErrorReportsDescription[];
#endif

#if defined(OS_WIN) || defined(OS_ANDROID)
extern const char kElasticOverscrollName[];
extern const char kElasticOverscrollDescription[];
#endif  // defined(OS_WIN) || defined(OS_ANDROID)

#if defined(OS_WIN) || (defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)) || \
    defined(OS_MAC)
extern const char kUIDebugToolsName[];
extern const char kUIDebugToolsDescription[];
#endif

<<<<<<< HEAD
#if defined(WEBRTC_USE_PIPEWIRE)
extern const char kWebrtcPipeWireCameraName[];
extern const char kWebrtcPipeWireCameraDescription[];
#endif  // #if defined(WEBRTC_USE_PIPEWIRE)

#if BUILDFLAG(IS_CHROMEOS)
extern const char kPromiseIconsName[];
extern const char kPromiseIconsDescription[];

extern const char kEnableAudioFocusEnforcementName[];
extern const char kEnableAudioFocusEnforcementDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(ENABLE_COMPOSE)
extern const char kComposeId[];
extern const char kComposeName[];
extern const char kComposeDescription[];

extern const char kComposeNudgeAtCursorName[];
extern const char kComposeNudgeAtCursorDescription[];

extern const char kComposeProactiveNudgeName[];
extern const char kComposeProactiveNudgeDescription[];

extern const char kComposePoliteNudgeName[];
extern const char kComposePoliteNudgeDescription[];

extern const char kComposeSegmentationPromotionName[];
extern const char kComposeSegmentationPromotionDescription[];

extern const char kComposeSelectionNudgeName[];
extern const char kComposeSelectionNudgeDescription[];

extern const char kComposeUpfrontInputModesName[];
extern const char kComposeUpfrontInputModesDescription[];
#endif  // BUILDFLAG(ENABLE_COMPOSE)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
extern const char kThirdPartyProfileManagementName[];
extern const char kThirdPartyProfileManagementDescription[];

extern const char kOidcAuthProfileManagementName[];
extern const char kOidcAuthProfileManagementDescription[];

extern const char kUnoDesktopName[];
extern const char kUnoDesktopDescription[];

extern const char kExplicitBrowserSigninUIOnDesktopName[];
extern const char kExplicitBrowserSigninUIOnDesktopDescription[];

extern const char kGlicName[];
extern const char kGlicDescription[];

extern const char kDesktopPWAsUserLinkCapturingScopeExtensionsName[];
extern const char kDesktopPWAsUserLinkCapturingScopeExtensionsDescription[];

extern const char kSyncEnableBookmarksInTransportModeName[];
extern const char kSyncEnableBookmarksInTransportModeDescription[];

extern const char kEnableGenericOidcAuthProfileManagementName[];
extern const char kEnableGenericOidcAuthProfileManagementDescription[];
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)

#if BUILDFLAG(ENABLE_HLS_DEMUXER)
extern const char kEnableBuiltinHlsName[];
extern const char kEnableBuiltinHlsDescription[];
#endif  // BUILDFLAG(ENABLE_HLS_DEMUXER)

#if !BUILDFLAG(IS_CHROMEOS)
extern const char kProfilesReorderingName[];
extern const char kProfilesReorderingDescription[];
#endif

extern const char kProfilePickerGlicTesting[];
extern const char kProfilePickerGlicTestingDescription[];

#if BUILDFLAG(ENABLE_DICE_SUPPORT)
extern const char kBatchUploadDesktopName[];
extern const char kBatchUploadDesktopDescription[];
#endif

#if BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)
extern const char kEnableBoundSessionCredentialsName[];
extern const char kEnableBoundSessionCredentialsDescription[];

extern const char
    kEnableBoundSessionCredentialsSoftwareKeysForManualTestingName[];
extern const char
    kEnableBoundSessionCredentialsSoftwareKeysForManualTestingDescription[];

extern const char kEnableChromeRefreshTokenBindingName[];
extern const char kEnableChromeRefreshTokenBindingDescription[];
#endif  // BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)

extern const char kEnableStandardBoundSessionCredentialsName[];
extern const char kEnableStandardBoundSessionCredentialsDescription[];
extern const char kEnableStandardBoundSessionPersistenceName[];
extern const char kEnableStandardBoundSessionPersistenceDescription[];

#if BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)
extern const char kEnableCertManagementV2UIName[];
extern const char kEnableCertManagementV2UIDescription[];
extern const char kEnableCertManagementV2UIWriteName[];
extern const char kEnableCertManagementV2UIWriteDescription[];
extern const char kEnableCertManagementV2UIEditCertsName[];
extern const char kEnableCertManagementV2UIEditCertsDescription[];
#endif  // BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)

#if BUILDFLAG(IS_CHROMEOS)
extern const char kOverlayScrollbarsOSSettingsName[];
extern const char kOverlayScrollbarsOSSettingsDescription[];
#endif

#if !BUILDFLAG(IS_ANDROID)
extern const char kEnablePolicyPromotionBannerName[];
extern const char kEnablePolicyPromotionBannerDescription[];
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
extern const char kSupervisedProfileHideGuestName[];
extern const char kSupervisedProfileHideGuestDescription[];

extern const char kSupervisedProfileSafeSearchName[];
extern const char kSupervisedProfileSafeSearchDescription[];

extern const char kSupervisedProfileReauthForYouTubeName[];
extern const char kSupervisedProfileReauthForYouTubeDescription[];

extern const char kSupervisedProfileReauthForBlockedSiteName[];
extern const char kSupervisedProfileReauthForBlockedSiteDescription[];

extern const char kSupervisedProfileSubframeReauthName[];
extern const char kSupervisedProfileSubframeReauthDescription[];

extern const char kSupervisedProfileFilteringFallbackName[];
extern const char kSupervisedProfileFilteringFallbackDescription[];

extern const char kSupervisedProfileCustomStringsName[];
extern const char kSupervisedProfileCustomStringsDescription[];

extern const char kSupervisedProfileSignInIphName[];
extern const char kSupervisedProfileSignInIphDescription[];

extern const char kSupervisedProfileShowKiteBadgeName[];
extern const char kSupervisedProfileShowKiteBadgeDescription[];

extern const char kSupervisedUserLocalWebApprovalsName[];
extern const char kSupervisedUserLocalWebApprovalsDescription[];

#endif  // #if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
extern const char kAuraWindowSubtreeCaptureName[];
extern const char kAuraWindowSubtreeCaptureDescription[];
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(WEBRTC_USE_PIPEWIRE)
extern const char kWebrtcPipeWireCapturerName[];
extern const char kWebrtcPipeWireCapturerDescription[];
#endif  // #if defined(WEBRTC_USE_PIPEWIRE)
>>>>>>> chromium

#if BUILDFLAG(IS_ANDROID)
extern const char kHistoryOptInEntryPointsName[];
extern const char kHistoryOptInEntryPointsDescription[];

extern const char kSupervisedUserForceSigninWithCapabilitiesName[];
extern const char kSupervisedUserForceSigninWithCapabilitiesDescription[];
#endif  // BUILDFLAG(IS_ANDROID)

// ============================================================================
// Don't just add flags to the end, put them in the right section in
// alphabetical order. See top instructions for more.
// ============================================================================

}  // namespace flag_descriptions

#endif  // CHROME_BROWSER_FLAG_DESCRIPTIONS_H_
