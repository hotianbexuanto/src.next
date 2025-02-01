// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/common/extension_features.h"

#include "base/feature_list.h"

namespace extensions_features {

// Controls whether we disable extensions for malware.
const base::Feature kDisableMalwareExtensionsRemotely{
    "DisableMalwareExtensionsRemotely", base::FEATURE_ENABLED_BY_DEFAULT};

// Controls whether we disable extensions that are marked as policy violation
// by the Omaha attribute.
const base::Feature kDisablePolicyViolationExtensionsRemotely{
    "DisablePolicyViolationExtensionsRemotely",
    base::FEATURE_DISABLED_BY_DEFAULT};

// Controls whether we disable extensions that are marked as potentially
// unwanted by the Omaha attribute.
const base::Feature kDisablePotentiallyUwsExtensionsRemotely{
    "DisablePotentiallyUwsExtensionsRemotely",
    base::FEATURE_DISABLED_BY_DEFAULT};

// Controls whether we show an install friction dialog when an Enhanced Safe
// Browsing user tries to install an extension that is not included in the
// Safe Browsing CRX allowlist. This feature also controls if we show a warning
// in 'chrome://extensions' for extensions not included in the allowlist.
const base::Feature kSafeBrowsingCrxAllowlistShowWarnings{
    "SafeBrowsingCrxAllowlistShowWarnings", base::FEATURE_DISABLED_BY_DEFAULT};

<<<<<<< HEAD
BASE_FEATURE(kApiRuntimeActionData,
             "ApiRuntimeActionData",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kApiPermissionsHostAccessRequests,
             "ApiPermissionsHostAccessRequests",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kApiUserScriptsExecute,
             "ApiUserScriptsExecute",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kApiUserScriptsMultipleWorlds,
             "ApiUserScriptsMultipleWorlds",
             base::FEATURE_ENABLED_BY_DEFAULT);
=======
// Automatically disable extensions not included in the Safe Browsing CRX
// allowlist if the user has turned on Enhanced Safe Browsing (ESB). The
// extensions can be disabled at ESB opt-in time or when an extension is moved
// out of the allowlist.
const base::Feature kSafeBrowsingCrxAllowlistAutoDisable{
    "SafeBrowsingCrxAllowlistAutoDisable", base::FEATURE_DISABLED_BY_DEFAULT};

// Forces requests to go through WebRequestProxyingURLLoaderFactory.
const base::Feature kForceWebRequestProxyForTest{
    "ForceWebRequestProxyForTest", base::FEATURE_DISABLED_BY_DEFAULT};
>>>>>>> chromium

// Enables the UI in the install prompt which lets a user choose to withhold
// requested host permissions by default.
const base::Feature kAllowWithholdingExtensionPermissionsOnInstall{
    "AllowWithholdingExtensionPermissionsOnInstall",
    base::FEATURE_DISABLED_BY_DEFAULT};

// Enables support for the "match_origin_as_fallback" property in content
// scripts.
const base::Feature kContentScriptsMatchOriginAsFallback{
    "ContentScriptsMatchOriginAsFallback", base::FEATURE_DISABLED_BY_DEFAULT};

// Whether Manifest Version 3-based extensions are supported.
const base::Feature kMv3ExtensionsSupported{"Mv3ExtensionsSupported",
                                            base::FEATURE_ENABLED_BY_DEFAULT};

// Reports Extensions.WebRequest.KeepaliveRequestFinished when enabled.
const base::Feature kReportKeepaliveUkm{"ReportKeepaliveUkm",
                                        base::FEATURE_ENABLED_BY_DEFAULT};

<<<<<<< HEAD
BASE_FEATURE(kAllowWithholdingExtensionPermissionsOnInstall,
             "AllowWithholdingExtensionPermissionsOnInstall",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kCheckingNoExtensionIdInExtensionIpcs,
             "EMF_NO_EXTENSION_ID_FOR_EXTENSION_SOURCE",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kEnableWebHidInWebView,
             "EnableWebHidInWebView",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionDisableUnsupportedDeveloper,
             "ExtensionDisableUnsupportedDeveloper",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionDynamicURLRedirection,
             "ExtensionDynamicURLRedirection",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionIconVariants,
             "ExtensionIconVariants",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionManifestV2DeprecationWarning,
             "ExtensionManifestV2DeprecationWarning",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionManifestV2Unsupported,
             "ExtensionManifestV2Unsupported",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionManifestV2ExceptionList,
             "ExtensionManifestV2ExceptionList",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionManifestV2Disabled,
             "ExtensionManifestV2Disabled",
             base::FEATURE_DISABLED_BY_DEFAULT);

const base::FeatureParam<std::string> kExtensionManifestV2ExceptionListParam(
    &kExtensionManifestV2ExceptionList,
    /*name=*/"mv2_exception_list",
    /*default_value=*/"");

BASE_FEATURE(kAllowLegacyMV2Extensions,
             "AllowLegacyMV2Extensions",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionSourceUrlEnforcement,
             "ExtensionSourceUrlEnforcement",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionWebFileHandlers,
             "ExtensionWebFileHandlers",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionsManifestV3Only,
             "ExtensionsManifestV3Only",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionsMenuAccessControl,
             "ExtensionsMenuAccessControl",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionsMenuAccessControlWithPermittedSites,
             "ExtensionsMenuAccessControlWithPermittedSitesName",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kExtensionsToolbarZeroState,
             "ExtensionsToolbarZeroState",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kForceWebRequestProxyForTest,
             "ForceWebRequestProxyForTest",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kLaunchWindowsNativeHostsDirectly,
             "LaunchWindowsNativeHostsDirectly",
             base::FEATURE_DISABLED_BY_DEFAULT);

// To investigate signal beacon loss in crrev.com/c/2262402.
BASE_FEATURE(kReportKeepaliveUkm,
             "ReportKeepaliveUkm",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kSafeBrowsingCrxAllowlistAutoDisable,
             "SafeBrowsingCrxAllowlistAutoDisable",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kSafeBrowsingCrxAllowlistShowWarnings,
             "SafeBrowsingCrxAllowlistShowWarnings",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kStructuredCloningForMV3Messaging,
             "StructuredCloningForMV3Messaging",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kTelemetryExtensionPendingApprovalApi,
             "TelemetryExtensionPendingApprovalApi",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kNewWebstoreURL,
             "NewWebstoreURL",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kDeclarativeNetRequestSafeRuleLimits,
             "DeclarativeNetRequestSafeDynamicRules",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kExperimentalOmniboxLabs,
             "ExperimentalOmniboxLabs",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kDeclarativeNetRequestResponseHeaderMatching,
             "DeclarativeNetRequestResponseHeaderMatching",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kIncludeJSCallStackInExtensionApiRequest,
             "IncludeJSCallStackInExtensionApiRequest",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kUseItemSnippetsAPI,
             "UseItemSnippetsAPI",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kUseNewServiceWorkerTaskQueue,
             "UseNewServiceWorkerTaskQueue",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kDeclarativeNetRequestHeaderSubstitution,
             "DeclarativeNetRequestHeaderSubstitution",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kSilentDebuggerExtensionAPI,
             "SilentDebuggerExtensionAPI",
             base::FEATURE_DISABLED_BY_DEFAULT);
=======
// Controls whether every extension will require a locked process, preventing
// process sharing between extensions. See https://crbug.com/1209417.
const base::Feature kStrictExtensionIsolation{
    "StrictExtensionIsolation", base::FEATURE_DISABLED_BY_DEFAULT};
>>>>>>> chromium

BASE_FEATURE(kRemoveCoreSiteInstance,
             "RemoveCoreSiteInstance",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kUserScriptUserExtensionToggle,
             "UserScriptUserExtensionToggle",
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace extensions_features
