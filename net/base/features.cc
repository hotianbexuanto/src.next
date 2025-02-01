// Copyright (c) 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/base/features.h"

#include <vector>

#include "build/build_config.h"

namespace net {
namespace features {

const base::Feature kAcceptLanguageHeader{"AcceptLanguageHeader",
                                          base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kAlpsForHttp2{"AlpsForHttp2",
                                  base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kAvoidH2Reprioritization{"AvoidH2Reprioritization",
                                             base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kCapReferrerToOriginOnCrossOrigin{
    "CapReferrerToOriginOnCrossOrigin", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kDnsTransactionDynamicTimeouts{
    "DnsTransactionDynamicTimeouts", base::FEATURE_DISABLED_BY_DEFAULT};

const base::FeatureParam<double> kDnsTransactionTimeoutMultiplier{
    &kDnsTransactionDynamicTimeouts, "DnsTransactionTimeoutMultiplier", 7.5};

const base::FeatureParam<base::TimeDelta> kDnsMinTransactionTimeout{
    &kDnsTransactionDynamicTimeouts, "DnsMinTransactionTimeout",
    base::TimeDelta::FromSeconds(12)};

const base::Feature kDnsHttpssvc{"DnsHttpssvc",
                                 base::FEATURE_DISABLED_BY_DEFAULT};

const base::FeatureParam<bool> kDnsHttpssvcUseHttpssvc{
    &kDnsHttpssvc, "DnsHttpssvcUseHttpssvc", false};

const base::FeatureParam<bool> kDnsHttpssvcUseIntegrity{
    &kDnsHttpssvc, "DnsHttpssvcUseIntegrity", false};

const base::FeatureParam<bool> kDnsHttpssvcEnableQueryOverInsecure{
    &kDnsHttpssvc, "DnsHttpssvcEnableQueryOverInsecure", false};

const base::FeatureParam<int> kDnsHttpssvcExtraTimeMs{
    &kDnsHttpssvc, "DnsHttpssvcExtraTimeMs", 10};

const base::FeatureParam<int> kDnsHttpssvcExtraTimePercent{
    &kDnsHttpssvc, "DnsHttpssvcExtraTimePercent", 5};

const base::FeatureParam<std::string> kDnsHttpssvcExperimentDomains{
    &kDnsHttpssvc, "DnsHttpssvcExperimentDomains", ""};

const base::FeatureParam<std::string> kDnsHttpssvcControlDomains{
    &kDnsHttpssvc, "DnsHttpssvcControlDomains", ""};

const base::FeatureParam<bool> kDnsHttpssvcControlDomainWildcard{
    &kDnsHttpssvc, "DnsHttpssvcControlDomainWildcard", false};

namespace dns_httpssvc_experiment {
base::TimeDelta GetExtraTimeAbsolute() {
  DCHECK(base::FeatureList::IsEnabled(features::kDnsHttpssvc));
  return base::TimeDelta::FromMilliseconds(kDnsHttpssvcExtraTimeMs.Get());
}
}  // namespace dns_httpssvc_experiment

const base::Feature kUseDnsHttpsSvcb{"UseDnsHttpsSvcb",
                                     base::FEATURE_DISABLED_BY_DEFAULT};

const base::FeatureParam<bool> kUseDnsHttpsSvcbHttpUpgrade{
    &kUseDnsHttpsSvcb, "UseDnsHttpsSvcbHttpUpgrade", false};

const base::FeatureParam<bool> kUseDnsHttpsSvcbEnforceSecureResponse{
    &kUseDnsHttpsSvcb, "UseDnsHttpsSvcbEnforceSecureResponse", false};

const base::FeatureParam<bool> kUseDnsHttpsSvcbEnableInsecure{
    &kUseDnsHttpsSvcb, "UseDnsHttpsSvcbEnableInsecure", false};

const base::FeatureParam<base::TimeDelta> kUseDnsHttpsSvcbExtraTimeAbsolute{
    &kUseDnsHttpsSvcb, "UseDnsHttpsSvcbExtraTimeAbsolute", base::TimeDelta()};

const base::FeatureParam<int> kUseDnsHttpsSvcbExtraTimePercent{
    &kUseDnsHttpsSvcb, "UseDnsHttpsSvcbExtraTimePercent", 0};

const base::Feature kEnableTLS13EarlyData{"EnableTLS13EarlyData",
                                          base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kNetworkQualityEstimator{"NetworkQualityEstimator",
                                             base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kSplitCacheByNetworkIsolationKey{
    "SplitCacheByNetworkIsolationKey", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kSplitHostCacheByNetworkIsolationKey{
    "SplitHostCacheByNetworkIsolationKey", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kPartitionConnectionsByNetworkIsolationKey{
    "PartitionConnectionsByNetworkIsolationKey",
    base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kPartitionHttpServerPropertiesByNetworkIsolationKey{
    "PartitionHttpServerPropertiesByNetworkIsolationKey",
    base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kPartitionSSLSessionsByNetworkIsolationKey{
    "PartitionSSLSessionsByNetworkIsolationKey",
    base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kPartitionExpectCTStateByNetworkIsolationKey{
    "PartitionExpectCTStateByNetworkIsolationKey",
    base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kPartitionNelAndReportingByNetworkIsolationKey{
    "PartitionNelAndReportingByNetworkIsolationKey",
    base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kExpectCTPruning{"ExpectCTPruning",
                                     base::FEATURE_ENABLED_BY_DEFAULT};

NET_EXPORT extern const base::FeatureParam<int>
    kExpectCTPruneMax(&kExpectCTPruning, "ExpectCTPruneMax", 2000);
NET_EXPORT extern const base::FeatureParam<int>
    kExpectCTPruneMin(&kExpectCTPruning, "ExpectCTPruneMin", 1800);
NET_EXPORT extern const base::FeatureParam<int> kExpectCTSafeFromPruneDays(
    &kExpectCTPruning,
    "ExpectCTSafeFromPruneDays",
    40);
NET_EXPORT extern const base::FeatureParam<int> kExpectCTMaxEntriesPerNik(
    &kExpectCTPruning,
    "ExpectCTMaxEntriesPerNik",
    20);
NET_EXPORT extern const base::FeatureParam<int>
    kExpectCTPruneDelaySecs(&kExpectCTPruning, "ExpectCTPruneDelaySecs", 60);

const base::Feature kTLS13KeyUpdate{"TLS13KeyUpdate",
                                    base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kPostQuantumCECPQ2{"PostQuantumCECPQ2",
                                       base::FEATURE_DISABLED_BY_DEFAULT};
const base::Feature kPostQuantumCECPQ2SomeDomains{
    "PostQuantumCECPQ2SomeDomains", base::FEATURE_ENABLED_BY_DEFAULT};
const base::FeatureParam<std::string> kPostQuantumCECPQ2InitialLetters(
    &kPostQuantumCECPQ2SomeDomains,
    "InitialLetters",
    "ag");

const base::Feature kNetUnusedIdleSocketTimeout{
    "NetUnusedIdleSocketTimeout", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kSameSiteByDefaultCookies{"SameSiteByDefaultCookies",
                                              base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kCookiesWithoutSameSiteMustBeSecure{
    "CookiesWithoutSameSiteMustBeSecure", base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kShortLaxAllowUnsafeThreshold{
    "ShortLaxAllowUnsafeThreshold", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kSameSiteDefaultChecksMethodRigorously{
    "SameSiteDefaultChecksMethodRigorously", base::FEATURE_DISABLED_BY_DEFAULT};

<<<<<<< HEAD
BASE_FEATURE(kSplitCodeCacheByNetworkIsolationKey,
             "SplitCodeCacheByNetworkIsolationKey",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kPartitionConnectionsByNetworkIsolationKey,
             "PartitionConnectionsByNetworkIsolationKey",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kPostQuantumKyber,
             "PostQuantumKyber",
             base::FEATURE_ENABLED_BY_DEFAULT);
=======
#if BUILDFLAG(BUILTIN_CERT_VERIFIER_FEATURE_SUPPORTED)
const base::Feature kCertVerifierBuiltinFeature{
    "CertVerifierBuiltin", base::FEATURE_DISABLED_BY_DEFAULT};
#if defined(OS_MAC)
const base::FeatureParam<int> kCertVerifierBuiltinImpl{
    &kCertVerifierBuiltinFeature, "impl", 0};
const base::FeatureParam<int> kCertVerifierBuiltinCacheSize{
    &kCertVerifierBuiltinFeature, "cachesize", 0};
#endif /* defined(OS_MAC) */
#endif
>>>>>>> chromium

#if BUILDFLAG(TRIAL_COMPARISON_CERT_VERIFIER_SUPPORTED)
// Enables the dual certificate verification trial feature.
// https://crbug.com/649026
const base::Feature kCertDualVerificationTrialFeature{
    "CertDualVerificationTrial", base::FEATURE_DISABLED_BY_DEFAULT};
#if defined(OS_MAC)
const base::FeatureParam<int> kCertDualVerificationTrialImpl{
    &kCertDualVerificationTrialFeature, "impl", 0};
const base::FeatureParam<int> kCertDualVerificationTrialCacheSize{
    &kCertDualVerificationTrialFeature, "cachesize", 0};
#endif /* defined(OS_MAC) */
#endif

<<<<<<< HEAD
BASE_FEATURE(kSearchEnginePreconnectInterval,
             "SearchEnginePreconnectInterval",
             base::FEATURE_DISABLED_BY_DEFAULT);
=======
const base::Feature kTurnOffStreamingMediaCachingOnBattery{
    "TurnOffStreamingMediaCachingOnBattery", base::FEATURE_DISABLED_BY_DEFAULT};
>>>>>>> chromium

const base::Feature kTurnOffStreamingMediaCachingAlways{
    "TurnOffStreamingMediaCachingAlways", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kLegacyTLSEnforced{"LegacyTLSEnforced",
                                       base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kSchemefulSameSite{"SchemefulSameSite",
                                       base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kTLSLegacyCryptoFallbackForMetrics{
    "TLSLegacyCryptoFallbackForMetrics", base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kUseLookalikesForNavigationSuggestions{
    "UseLookalikesForNavigationSuggestions", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kReportPoorConnectivity{"ReportPoorConnectivity",
                                            base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kPreemptiveMobileNetworkActivation{
    "PreemptiveMobileNetworkActivation", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kLimitOpenUDPSockets{"LimitOpenUDPSockets",
                                         base::FEATURE_ENABLED_BY_DEFAULT};

extern const base::FeatureParam<int> kLimitOpenUDPSocketsMax(
    &kLimitOpenUDPSockets,
    "LimitOpenUDPSocketsMax",
    6000);

const base::Feature kTimeoutTcpConnectAttempt{
    "TimeoutTcpConnectAttempt", base::FEATURE_DISABLED_BY_DEFAULT};

extern const base::FeatureParam<double> kTimeoutTcpConnectAttemptRTTMultiplier(
    &kTimeoutTcpConnectAttempt,
    "TimeoutTcpConnectAttemptRTTMultiplier",
    5.0);

extern const base::FeatureParam<base::TimeDelta> kTimeoutTcpConnectAttemptMin(
    &kTimeoutTcpConnectAttempt,
    "TimeoutTcpConnectAttemptMin",
    base::TimeDelta::FromSeconds(8));

extern const base::FeatureParam<base::TimeDelta> kTimeoutTcpConnectAttemptMax(
    &kTimeoutTcpConnectAttempt,
    "TimeoutTcpConnectAttemptMax",
    base::TimeDelta::FromSeconds(30));

constexpr base::Feature kFirstPartySets{"FirstPartySets",
                                        base::FEATURE_DISABLED_BY_DEFAULT};

const base::FeatureParam<bool> kFirstPartySetsIsDogfooder{
    &kFirstPartySets, "FirstPartySetsIsDogfooder", false};

const base::Feature kSameSiteCookiesBugfix1166211{
    "SameSiteCookiesBugfix1166211", base::FEATURE_ENABLED_BY_DEFAULT};

const base::Feature kNoCookieChangeNotificationOnLoad{
    "NoCookieChangeNotificationOnLoad", base::FEATURE_ENABLED_BY_DEFAULT};

<<<<<<< HEAD
BASE_FEATURE(kCookieSameSiteConsidersRedirectChain,
             "CookieSameSiteConsidersRedirectChain",
             base::FEATURE_DISABLED_BY_DEFAULT);
=======
#if BUILDFLAG(ENABLE_REPORTING)
const base::Feature kDocumentReporting{"DocumentReporting",
                                       base::FEATURE_DISABLED_BY_DEFAULT};
#endif  // BUILDFLAG(ENABLE_REPORTING)

#if defined(OS_POSIX) || defined(OS_FUCHSIA)
const base::Feature kUdpSocketPosixAlwaysUpdateBytesReceived{
    "UdpSocketPosixAlwaysUpdateBytesReceived",
    base::FEATURE_DISABLED_BY_DEFAULT};
#endif  // defined(OS_POSIX) || defined(OS_FUCHSIA)
>>>>>>> chromium

const base::Feature kCookieSameSiteConsidersRedirectChain{
    "CookieSameSiteConsidersRedirectChain", base::FEATURE_DISABLED_BY_DEFAULT};

const base::Feature kSamePartyCookiesConsideredFirstParty{
    "SamePartyCookiesConsideredFirstParty", base::FEATURE_DISABLED_BY_DEFAULT};

<<<<<<< HEAD
// Controls the maximum time duration an outermost frame navigation should be
// deferred by RWS initialization.
extern const base::FeatureParam<base::TimeDelta>
    kWaitForFirstPartySetsInitNavigationThrottleTimeout{
        &kWaitForFirstPartySetsInit,
        "kWaitForFirstPartySetsInitNavigationThrottleTimeout",
        base::Seconds(0)};

BASE_FEATURE(kAncestorChainBitEnabledInPartitionedCookies,
             "AncestorChainBitEnabledInPartitionedCookies",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kRequestStorageAccessNoCorsRequired,
             "RequestStorageAccessNoCorsRequired",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kStorageAccessApiFollowsSameOriginPolicy,
             "StorageAccessApiFollowsSameOriginPolicy",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kStaticKeyPinningEnforcement,
             "StaticKeyPinningEnforcement",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kCookieDomainRejectNonASCII,
             "CookieDomainRejectNonASCII",
             base::FEATURE_DISABLED_BY_DEFAULT);

// Enables partitioning of third party storage (IndexedDB, CacheStorage, etc.)
// by the top level site to reduce fingerprinting.
BASE_FEATURE(kThirdPartyStoragePartitioning,
             "ThirdPartyStoragePartitioning",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kTopLevelTpcdOriginTrial,
             "TopLevelTpcdOriginTrial",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kTpcdTrialSettings,
             "TpcdSupportSettings",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kTopLevelTpcdTrialSettings,
             "TopLevelTpcdSupportSettings",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kTpcdMetadataGrants,
             "TpcdMetadataGrants",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kTpcdMetadataStageControl,
             "TpcdMetadataStageControl",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kAlpsParsing, "AlpsParsing", base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kAlpsClientHintParsing,
             "AlpsClientHintParsing",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kShouldKillSessionOnAcceptChMalformed,
             "ShouldKillSessionOnAcceptChMalformed",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kEnableWebsocketsOverHttp3,
             "EnableWebsocketsOverHttp3",
             base::FEATURE_DISABLED_BY_DEFAULT);

#if BUILDFLAG(IS_WIN)
// Disabled because of https://crbug.com/1489696.
BASE_FEATURE(kEnableGetNetworkConnectivityHintAPI,
             "EnableGetNetworkConnectivityHintAPI",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kEnableTcpPortRandomization,
             "EnableTcpPortRandomization",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kTcpSocketIoCompletionPortWin,
             "TcpSocketIoCompletionPortWin",
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif

BASE_FEATURE(kAvoidEntryCreationForNoStore,
             "AvoidEntryCreationForNoStore",
             base::FEATURE_DISABLED_BY_DEFAULT);
const base::FeatureParam<int> kAvoidEntryCreationForNoStoreCacheSize{
    &kAvoidEntryCreationForNoStore, "AvoidEntryCreationForNoStoreCacheSize",
    1000};

// Prefetch to follow normal semantics instead of 5-minute rule
// https://crbug.com/1345207
BASE_FEATURE(kPrefetchFollowsNormalCacheSemantics,
             "PrefetchFollowsNormalCacheSemantics",
             base::FEATURE_ENABLED_BY_DEFAULT);

// A flag for new Kerberos feature, that suggests new UI
// when Kerberos authentication in browser fails on ChromeOS.
// b/260522530
#if BUILDFLAG(IS_CHROMEOS)
BASE_FEATURE(kKerberosInBrowserRedirect,
             "KerberosInBrowserRedirect",
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif

// A flag to use asynchronous session creation for new QUIC sessions.
BASE_FEATURE(kAsyncQuicSession,
             "AsyncQuicSession",
#if BUILDFLAG(IS_WIN)
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif

// A flag to make multiport context creation asynchronous.
BASE_FEATURE(kAsyncMultiPortPath,
             "AsyncMultiPortPath",
#if !BUILDFLAG(CRONET_BUILD) && (BUILDFLAG(IS_WIN) || BUILDFLAG(IS_ANDROID))
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif

// IP protection experiment configuration settings
BASE_FEATURE(kEnableIpProtectionProxy,
             "EnableIpPrivacyProxy",
             base::FEATURE_DISABLED_BY_DEFAULT);

const base::FeatureParam<std::string> kIpPrivacyTokenServer{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyTokenServer",
    /*default_value=*/"https://prod.ipprotectionauth.goog"};

const base::FeatureParam<std::string> kIpPrivacyIssuerTokenServer{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyIssuerTokenServer",
    /*default_value=*/"https://prod.issuertoken.goog"};

const base::FeatureParam<std::string> kIpPrivacyTokenServerGetInitialDataPath{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyTokenServerGetInitialDataPath",
    /*default_value=*/"/v1/ipblinding/getInitialData"};

const base::FeatureParam<std::string> kIpPrivacyIssuerTokenServerPath{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyIssuerTokenServerPath",
    /*default_value=*/"/v1/ipblinding/getIssuerToken"};

const base::FeatureParam<std::string> kIpPrivacyTokenServerGetTokensPath{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyTokenServerGetTokensPath",
    /*default_value=*/"/v1/ipblinding/auth"};

const base::FeatureParam<std::string> kIpPrivacyTokenServerGetProxyConfigPath{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyTokenServerGetProxyConfigPath",
    /*default_value=*/"/v1/ipblinding/getProxyConfig"};

const base::FeatureParam<int> kIpPrivacyAuthTokenCacheBatchSize{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyAuthTokenCacheBatchSize",
    /*default_value=*/64};

const base::FeatureParam<int> kIpPrivacyAuthTokenCacheLowWaterMark{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyAuthTokenCacheLowWaterMark",
    /*default_value=*/16};

const base::FeatureParam<base::TimeDelta> kIpPrivacyProxyListFetchInterval{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyProxyListFetchInterval",
    /*default_value=*/base::Hours(1)};

const base::FeatureParam<base::TimeDelta> kIpPrivacyProxyListMinFetchInterval{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyProxyMinListFetchInterval",
    /*default_value=*/base::Minutes(1)};

const base::FeatureParam<base::TimeDelta> kIpPrivacyProxyListFetchIntervalFuzz{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyProxyListFetchIntervalFuzz",
    /*default_value=*/base::Minutes(30)};

const base::FeatureParam<bool> kIpPrivacyDirectOnly{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyDirectOnly",
    /*default_value=*/false};

const base::FeatureParam<bool> kIpPrivacyIncludeOAuthTokenInGetProxyConfig{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyIncludeOAuthTokenInGetProxyConfig",
    /*default_value=*/false};

const base::FeatureParam<std::string> kIpPrivacyProxyAHostnameOverride{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyProxyAHostnameOverride",
    /*default_value=*/""};

const base::FeatureParam<std::string> kIpPrivacyProxyBHostnameOverride{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyProxyBHostnameOverride",
    /*default_value=*/""};

const base::FeatureParam<bool> kIpPrivacyAddHeaderToProxiedRequests{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyAddHeaderToProxiedRequests",
    /*default_value=*/false};

const base::FeatureParam<base::TimeDelta> kIpPrivacyExpirationFuzz{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyExpirationFuzz",
    /*default_value=*/base::Minutes(15)};

const base::FeatureParam<base::TimeDelta>
    kIpPrivacyTryGetAuthTokensNotEligibleBackoff{
        &kEnableIpProtectionProxy,
        /*name=*/"IpPrivacyTryGetAuthTokensNotEligibleBackoff",
        /*default_value=*/base::Hours(1)};

const base::FeatureParam<base::TimeDelta>
    kIpPrivacyTryGetAuthTokensTransientBackoff{
        &kEnableIpProtectionProxy,
        /*name=*/"IpPrivacyTryGetAuthTokensTransientBackoff",
        /*default_value=*/base::Seconds(5)};

const base::FeatureParam<base::TimeDelta> kIpPrivacyTryGetAuthTokensBugBackoff{
    &kEnableIpProtectionProxy, /*name=*/"IpPrivacyTryGetAuthTokensBugBackoff",
    /*default_value=*/base::Minutes(10)};

const base::FeatureParam<bool> kIpPrivacyRestrictTopLevelSiteSchemes{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyRestrictTopLevelSiteSchemes",
    /*default_value=*/true};

const base::FeatureParam<bool> kIpPrivacyUseQuicProxies{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyUseQuicProxies",
    /*default_value=*/false};

const base::FeatureParam<bool> kIpPrivacyUseQuicProxiesOnly{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyUseQuicProxiesOnly",
    /*default_value=*/false};

const base::FeatureParam<bool> kIpPrivacyUseSingleProxy{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyUseSingleProxy",
    /*default_value=*/false};

const base::FeatureParam<std::string> kIpPrivacyAlwaysProxy{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyAlwaysProxy",
    /*default_value=*/""};

const base::FeatureParam<bool> kIpPrivacyFallbackToDirect{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyFallbackToDirect",
    /*default_value=*/true};

const base::FeatureParam<int> kIpPrivacyDebugExperimentArm{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyDebugExperimentArm",
    /*default_value=*/0};

const base::FeatureParam<bool> kIpPrivacyCacheTokensByGeo{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyCacheTokensByGeo",
    /*default_value=*/false};

const base::FeatureParam<bool> kIpPrivacyAlwaysCreateCore{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyAlwaysCreateCore",
    /*default_value=*/false};

const base::FeatureParam<bool> kIpPrivacyOnlyInIncognito{
    &kEnableIpProtectionProxy,
    /*name=*/"IpPrivacyOnlyInIncognito",
    /*default_value=*/false};

// Network-change migration requires NetworkHandle support, which are currently
// only supported on Android (see
// NetworkChangeNotifier::AreNetworkHandlesSupported).
#if BUILDFLAG(IS_ANDROID)
inline constexpr auto kMigrateSessionsOnNetworkChangeV2Default =
    base::FEATURE_ENABLED_BY_DEFAULT;
#else   // !BUILDFLAG(IS_ANDROID)
inline constexpr auto kMigrateSessionsOnNetworkChangeV2Default =
    base::FEATURE_DISABLED_BY_DEFAULT;
#endif  // BUILDFLAG(IS_ANDROID)
BASE_FEATURE(kMigrateSessionsOnNetworkChangeV2,
             "MigrateSessionsOnNetworkChangeV2",
             kMigrateSessionsOnNetworkChangeV2Default);

BASE_FEATURE(kDisableBlackholeOnNoNewNetwork,
             "DisableBlackHoleOnNoNewNetwork",
             base::FEATURE_DISABLED_BY_DEFAULT);

#if BUILDFLAG(IS_LINUX)
BASE_FEATURE(kAddressTrackerLinuxIsProxied,
             "AddressTrackerLinuxIsProxied",
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif  // BUILDFLAG(IS_LINUX)

// Enables binding of cookies to the port that originally set them by default.
BASE_FEATURE(kEnablePortBoundCookies,
             "EnablePortBoundCookies",
             base::FEATURE_DISABLED_BY_DEFAULT);

// Enables binding of cookies to the scheme that originally set them.
NET_EXPORT BASE_DECLARE_FEATURE(kEnableSchemeBoundCookies);
BASE_FEATURE(kEnableSchemeBoundCookies,
             "EnableSchemeBoundCookies",
             base::FEATURE_DISABLED_BY_DEFAULT);

// Disallows cookies to have non ascii values in their name or value.
NET_EXPORT BASE_DECLARE_FEATURE(kDisallowNonAsciiCookies);
BASE_FEATURE(kDisallowNonAsciiCookies,
             "kDisallowNonAsciiCookies",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kTimeLimitedInsecureCookies,
             "TimeLimitedInsecureCookies",
             base::FEATURE_DISABLED_BY_DEFAULT);

// Enable third-party cookie blocking from the command line.
BASE_FEATURE(kForceThirdPartyCookieBlocking,
             "ForceThirdPartyCookieBlockingEnabled",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kEnableEarlyHintsOnHttp11,
             "EnableEarlyHintsOnHttp11",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kEnableWebTransportDraft07,
             "EnableWebTransportDraft07",
             base::FEATURE_DISABLED_BY_DEFAULT);

// When enabled, partitioned storage will be allowed even if third-party cookies
// are disabled by default. Partitioned storage will not be allowed if
// third-party cookies are disabled due to a specific rule.
BASE_FEATURE(kThirdPartyPartitionedStorageAllowedByDefault,
             "ThirdPartyPartitionedStorageAllowedByDefault",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kSpdyHeadersToHttpResponseUseBuilder,
             "SpdyHeadersToHttpResponseUseBuilder",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kReportEcn, "ReportEcn", base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kUseNewAlpsCodepointHttp2,
             "UseNewAlpsCodepointHttp2",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kUseNewAlpsCodepointQUIC,
             "UseNewAlpsCodepointQUIC",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kTreatHTTPExpiresHeaderValueZeroAsExpired,
             "TreatHTTPExpiresHeaderValueZeroAsExpired",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kTruncateBodyToContentLength,
             "TruncateBodyToContentLength",
             base::FEATURE_ENABLED_BY_DEFAULT);

#if BUILDFLAG(IS_MAC)
BASE_FEATURE(kReduceIPAddressChangeNotification,
             "ReduceIPAddressChangeNotification",
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif  // BUILDFLAG(IS_MAC)

BASE_FEATURE(kDeviceBoundSessions,
             "DeviceBoundSessions",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kPersistDeviceBoundSessions,
             "PersistDeviceBoundSessions",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kPartitionProxyChains,
             "PartitionProxyChains",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kSpdySessionForProxyAdditionalChecks,
             "SpdySessionForProxyAdditionalChecks",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kCompressionDictionaryTransportOverHttp1,
             "CompressionDictionaryTransportOverHttp1",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kCompressionDictionaryTransportOverHttp2,
             "CompressionDictionaryTransportOverHttp2",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kCompressionDictionaryTransportRequireKnownRootCert,
             "CompressionDictionaryTransportRequireKnownRootCert",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kReportingApiEnableEnterpriseCookieIssues,
             "ReportingApiEnableEnterpriseCookieIssues",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kOptimizeParsingDataUrls,
             "OptimizeParsingDataUrls",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kSimdutfBase64Support,
             "SimdutfBase64Support",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kFurtherOptimizeParsingDataUrls,
             "FurtherOptimizeParsingDataUrls",
             base::FEATURE_ENABLED_BY_DEFAULT);

// TODO(crbug.com/347047841): Remove this flag when we branch for M131 or later,
// if we haven't had to turn this off.
BASE_FEATURE(kLegacyPKCS1ForTLS13,
             "LegacyPKCS1ForTLS13",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kKeepWhitespaceForDataUrls,
             "KeepWhitespaceForDataUrls",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kNoVarySearchIgnoreUnrecognizedKeys,
             "NoVarySearchIgnoreUnrecognizedKeys",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kEncryptedAndPlaintextValuesAreInvalid,
             "EncryptedAndPlaintextValuesAreInvalid",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kEnableStaticCTAPIEnforcement,
             "EnableStaticCTAPIEnforcement",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kDiskCacheBackendExperiment,
             "DiskCacheBackendExperiment",
             base::FEATURE_DISABLED_BY_DEFAULT);
constexpr base::FeatureParam<DiskCacheBackend>::Option
    kDiskCacheBackendOptions[] = {
        {DiskCacheBackend::kSimple, "simple"},
        {DiskCacheBackend::kBlockfile, "blockfile"},
};
const base::FeatureParam<DiskCacheBackend> kDiskCacheBackendParam{
    &kDiskCacheBackendExperiment, "backend", DiskCacheBackend::kBlockfile,
    &kDiskCacheBackendOptions};

BASE_FEATURE(kIgnoreHSTSForLocalhost,
             "IgnoreHSTSForLocalhost",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kSimpleCachePrioritizedCaching,
             "SimpleCachePrioritizedCaching",
             base::FEATURE_DISABLED_BY_DEFAULT);

const base::FeatureParam<int>
    kSimpleCachePrioritizedCachingPrioritizationFactor{
        &kSimpleCachePrioritizedCaching,
        /*name=*/"SimpleCachePrioritizedCachingPrioritizationFactor",
        /*default_value=*/10};

const base::FeatureParam<base::TimeDelta>
    kSimpleCachePrioritizedCachingPrioritizationPeriod{
        &kSimpleCachePrioritizedCaching,
        /*name=*/"SimpleCachePrioritizedCachingPrioritizationPeriod",
        /*default_value=*/base::Days(1)};

#if BUILDFLAG(USE_NSS_CERTS)
// TODO(crbug.com/40928765): Remove this flag after a few milestones.
BASE_FEATURE(kNewClientCertPathBuilding,
             "NewClientCertPathBuilding",
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif  // BUILDFLAG(USE_NSS_CERTS)

BASE_FEATURE(kHstsTopLevelNavigationsOnly,
             "HstsTopLevelNavigationsOnly",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kHttpCacheNoVarySearch,
             "HttpCacheNoVarySearch",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE_PARAM(size_t,
                   kHttpCacheNoVarySearchCacheMaxEntries,
                   &kHttpCacheNoVarySearch,
                   "max_entries",
                   1000);

BASE_FEATURE(kReportingApiCorsOriginHeader,
             "ReportingApiCorsOriginHeader",
             base::FEATURE_ENABLED_BY_DEFAULT);

#if BUILDFLAG(IS_ANDROID)
BASE_FEATURE(kUseCertTransparencyAwareApiForOsCertVerify,
             "UseCertTransparencyAwareApiForOsCertVerify",
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif  // BUILDFLAG(IS_ANDROID)

}  // namespace net::features
=======
}  // namespace features
}  // namespace net
>>>>>>> chromium
