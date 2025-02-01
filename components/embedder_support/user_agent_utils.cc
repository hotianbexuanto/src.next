// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/embedder_support/user_agent_utils.h"

#include "base/command_line.h"
#include "base/no_destructor.h"
#include "base/strings/strcat.h"
#include "base/strings/stringprintf.h"
#include "base/system/sys_info.h"
#include "build/branding_buildflags.h"
#include "components/embedder_support/switches.h"
#include "components/version_info/version_info.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/content_features.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/user_agent.h"
#include "net/http/http_util.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/common/user_agent/user_agent_metadata.h"

namespace embedder_support {

<<<<<<< HEAD
namespace {

#if BUILDFLAG(IS_WIN)

// The registry key where the UniversalApiContract version value can be read
// from.
constexpr wchar_t kWindowsRuntimeWellKnownContractsRegKeyName[] =
    L"SOFTWARE\\Microsoft\\WindowsRuntime\\WellKnownContracts";

// Name of the UniversalApiContract registry.
constexpr wchar_t kUniversalApiContractName[] =
    L"Windows.Foundation.UniversalApiContract";

// There's a chance that access to the registry key that contains the
// UniversalApiContract Version will not be available in the future. After we
// confirm that our Windows version is RS5 or greater, it is best to have the
// default return value be the highest known version number at the time this
// code is submitted. If the UniversalApiContract registry key is no longer
// available, there will either be a new API introduced, or we will need
// to rely on querying the IsApiContractPresentByMajor function used by
// user_agent_utils_unittest.cc.
const int kHighestKnownUniversalApiContractVersion = 19;

int GetPreRS5UniversalApiContractVersion() {
  // This calls Kernel32Version() to get the real non-spoofable version (as
  // opposed to base::win::GetVersion() which as of writing this seems to return
  // different results depending on compatibility mode, and is spoofable).
  // See crbug.com/1404448.
  const base::win::Version version = base::win::OSInfo::Kernel32Version();
  if (version == base::win::Version::WIN10) {
    return 1;
  }
  if (version == base::win::Version::WIN10_TH2) {
    return 2;
  }
  if (version == base::win::Version::WIN10_RS1) {
    return 3;
  }
  if (version == base::win::Version::WIN10_RS2) {
    return 4;
  }
  if (version == base::win::Version::WIN10_RS3) {
    return 5;
  }
  if (version == base::win::Version::WIN10_RS4) {
    return 6;
  }
  // The list above should account for all Windows versions prior to
  // RS5.
  NOTREACHED();
}

// Returns the UniversalApiContract version number, which is available for
// Windows versions greater than RS5. Otherwise, returns 0.
const std::string& GetUniversalApiContractVersion() {
  // Do not use this for runtime environment detection logic. This method should
  // only be used to help populate the Sec-CH-UA-Platform client hint. If
  // authoring code that depends on a minimum API contract version being
  // available, you should instead leverage the OS's IsApiContractPresentByMajor
  // method.
  static const base::NoDestructor<std::string> universal_api_contract_version(
      [] {
        int major_version = 0;
        int minor_version = 0;
        if (base::win::OSInfo::Kernel32Version() <=
            base::win::Version::WIN10_RS4) {
          major_version = GetPreRS5UniversalApiContractVersion();
        } else {
          base::win::RegKey version_key(
              HKEY_LOCAL_MACHINE, kWindowsRuntimeWellKnownContractsRegKeyName,
              KEY_QUERY_VALUE | KEY_WOW64_64KEY);
          if (version_key.Valid()) {
            DWORD universal_api_contract_version = 0;
            LONG result = version_key.ReadValueDW(
                kUniversalApiContractName, &universal_api_contract_version);
            if (result == ERROR_SUCCESS) {
              major_version = HIWORD(universal_api_contract_version);
              minor_version = LOWORD(universal_api_contract_version);
            } else {
              major_version = kHighestKnownUniversalApiContractVersion;
            }
          } else {
            major_version = kHighestKnownUniversalApiContractVersion;
          }
        }
        // The major version of the contract is stored in the HIWORD, while the
        // minor version is stored in the LOWORD.
        return base::StrCat({base::NumberToString(major_version), ".",
                             base::NumberToString(minor_version), ".0"});
      }());
  return *universal_api_contract_version;
}

const std::string& GetWindowsPlatformVersion() {
  return GetUniversalApiContractVersion();
}
#endif  // BUILDFLAG(IS_WIN)

// Returns true if the user agent reduction should be forced (or prevented).
// TODO(crbug.com/1330890): Remove this method along with policy.
bool ShouldReduceUserAgentMinorVersion(
    UserAgentReductionEnterprisePolicyState user_agent_reduction) {
  return ((user_agent_reduction !=
               UserAgentReductionEnterprisePolicyState::kForceDisabled &&
           base::FeatureList::IsEnabled(
               blink::features::kReduceUserAgentMinorVersion)) ||
          user_agent_reduction ==
              UserAgentReductionEnterprisePolicyState::kForceEnabled);
}

// For desktop:
// Returns true if both kReduceUserAgentMinorVersionName and
// kReduceUserAgentPlatformOsCpu are enabled. It makes
// kReduceUserAgentPlatformOsCpu depend on kReduceUserAgentMinorVersionName.
//
// For android:
// Returns true if both kReduceUserAgentMinorVersionName and
// kReduceUserAgentAndroidVersionDeviceModel are enabled. It makes
// kReduceUserAgentAndroidVersionDeviceModel depend on
// kReduceUserAgentMinorVersionName.
//
// It helps us avoid introducing individual enterprise policy controls for
// sending unified platform for the user agent string.
bool ShouldSendUserAgentUnifiedPlatform(
    UserAgentReductionEnterprisePolicyState user_agent_reduction) {
#if BUILDFLAG(IS_ANDROID)
  return ShouldReduceUserAgentMinorVersion(user_agent_reduction) &&
         base::FeatureList::IsEnabled(
             blink::features::kReduceUserAgentAndroidVersionDeviceModel);
#else
  return ShouldReduceUserAgentMinorVersion(user_agent_reduction) &&
         base::FeatureList::IsEnabled(
             blink::features::kReduceUserAgentPlatformOsCpu);
#endif
}

const blink::UserAgentBrandList GetUserAgentBrandList(
    const std::string& major_version,
    bool enable_updated_grease_by_policy,
    const std::string& full_version,
    blink::UserAgentBrandVersionType output_version_type,
    std::optional<blink::UserAgentBrandVersion> additional_brand_version) {
  int major_version_number;
  bool parse_result = base::StringToInt(major_version, &major_version_number);
  DCHECK(parse_result);
  std::optional<std::string> brand;
#if !BUILDFLAG(CHROMIUM_BRANDING)
  brand = version_info::GetProductName();
#endif

  std::string brand_version =
      output_version_type == blink::UserAgentBrandVersionType::kFullVersion
          ? full_version
          : major_version;

  return GenerateBrandVersionList(major_version_number, brand, brand_version,
                                  enable_updated_grease_by_policy,
                                  output_version_type,
                                  additional_brand_version);
}

// Return UserAgentBrandList with the major version populated in the brand
// `version` value.
// TODO(crbug.com/1291612): Consolidate *MajorVersionList() methods by using
// GetVersionNumber()
const blink::UserAgentBrandList GetUserAgentBrandMajorVersionListInternal(
    bool enable_updated_grease_by_policy,
    std::optional<blink::UserAgentBrandVersion> additional_brand_version) {
  return GetUserAgentBrandList(version_info::GetMajorVersionNumber(),
                               enable_updated_grease_by_policy,
                               std::string(version_info::GetVersionNumber()),
                               blink::UserAgentBrandVersionType::kMajorVersion,
                               additional_brand_version);
}

// Return UserAgentBrandList with the full version populated in the brand
// `version` value.
// TODO(crbug.com/1291612): Consolidate *FullVersionList() methods by using
// GetVersionNumber()
const blink::UserAgentBrandList GetUserAgentBrandFullVersionListInternal(
    bool enable_updated_grease_by_policy,
    std::optional<blink::UserAgentBrandVersion> additional_brand_version) {
  return GetUserAgentBrandList(
      version_info::GetMajorVersionNumber(), enable_updated_grease_by_policy,
      std::string(version_info::GetVersionNumber()),
      blink::UserAgentBrandVersionType::kFullVersion, additional_brand_version);
}

std::vector<std::string> GetFormFactorsClientHint(
    const blink::UserAgentMetadata& metadata,
    bool is_mobile) {
  // By default, use "Mobile" or "Desktop" depending on the `mobile` bit.
  std::vector<std::string> form_factors = {
      is_mobile ? blink::kMobileFormFactor : blink::kDesktopFormFactor};

  if (base::FeatureList::IsEnabled(blink::features::kClientHintsXRFormFactor)) {
    form_factors.push_back(blink::kXRFormFactor);
  }
  return form_factors;
}

// Internal function to handle return the full or "reduced" user agent string,
// depending on the UserAgentReduction enterprise policy.
std::string GetUserAgentInternal(
    UserAgentReductionEnterprisePolicyState user_agent_reduction) {
  std::string product = GetProductAndVersion(user_agent_reduction);
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(kHeadless)) {
    product.insert(0, "Headless");
  }

#if BUILDFLAG(IS_ANDROID)
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kUseMobileUserAgent))
    product += " Mobile";
#endif

  // In User-Agent reduction phase 5, only apply the <unifiedPlatform> to
  // desktop UA strings.
  // In User-Agent reduction phase 6, only apply the <unifiedPlatform> to
  // android UA strings.
  return ShouldSendUserAgentUnifiedPlatform(user_agent_reduction)
             ? content::BuildUnifiedPlatformUserAgentFromProduct(product)
             : content::BuildUserAgentFromProduct(product);
}

// Generate random order list based on the input size and seed.
// Manually implement a stable permutation shuffle since STL random number
// engines and generators are banned and helpers in base/rand_util.h not
// supported seed shuffle.
std::vector<size_t> GetRandomOrder(int seed, size_t size) {
  CHECK_GE(size, 2u);
  CHECK_LE(size, 4u);

  if (size == 2u) {
    return {seed % size, (seed + 1) % size};
  } else if (size == 3u) {
    // Pick a stable permutation seeded by major version number. any values here
    // and in order should be under three.
    static constexpr std::array<std::array<size_t, 3>, 6> orders{
        {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}}};
    const std::array<size_t, 3> order = orders[seed % orders.size()];
    return std::vector<size_t>(order.begin(), order.end());
  } else {
    // Pick a stable permutation seeded by major version number. any values
    // here and in order should be under four.
    static constexpr std::array<std::array<size_t, 4>, 24> orders{
        {{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 1, 2},
         {0, 3, 2, 1}, {1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0},
         {1, 3, 0, 2}, {1, 3, 2, 0}, {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3},
         {2, 1, 3, 0}, {2, 3, 0, 1}, {2, 3, 1, 0}, {3, 0, 1, 2}, {3, 0, 2, 1},
         {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}}};
    const std::array<size_t, 4> order = orders[seed % orders.size()];
    return std::vector<size_t>(order.begin(), order.end());
  }
}

// Shuffle the generated brand version list based on the seed.
blink::UserAgentBrandList ShuffleBrandList(
    blink::UserAgentBrandList brand_version_list,
    int seed) {
  const std::vector<size_t> order =
      GetRandomOrder(seed, brand_version_list.size());
  CHECK_EQ(brand_version_list.size(), order.size());

  blink::UserAgentBrandList shuffled_brand_version_list(
      brand_version_list.size());
  for (size_t i = 0; i < order.size(); i++) {
    shuffled_brand_version_list[order[i]] = brand_version_list[i];
  }

  return shuffled_brand_version_list;
}

}  // namespace

std::string GetProductAndVersion(
    UserAgentReductionEnterprisePolicyState user_agent_reduction) {
  return ShouldReduceUserAgentMinorVersion(user_agent_reduction)
             ? version_info::GetProductNameAndVersionForReducedUserAgent(
                   blink::features::kUserAgentFrozenBuildVersion.Get())
             : std::string(
                   version_info::GetProductNameAndVersionForUserAgent());
}

std::optional<std::string> GetUserAgentFromCommandLine() {
=======
std::string GetProduct() {
  return version_info::GetProductNameAndVersionForUserAgent();
}

std::string GetUserAgent() {
>>>>>>> chromium
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kUserAgent)) {
    std::string ua = command_line->GetSwitchValueASCII(kUserAgent);
    if (net::HttpUtil::IsValidHeaderValue(ua))
      return ua;
    LOG(WARNING) << "Ignored invalid value for flag --" << kUserAgent;
  }

  if (base::FeatureList::IsEnabled(blink::features::kReduceUserAgent)) {
    return content::GetReducedUserAgent(
        command_line->HasSwitch(switches::kUseMobileUserAgent),
        version_info::GetMajorVersionNumber());
  }

<<<<<<< HEAD
  return GetUserAgentInternal(user_agent_reduction);
}

const blink::UserAgentBrandList GetUserAgentBrandMajorVersionList(
    std::optional<blink::UserAgentBrandVersion> additional_brand_version) {
  return GetUserAgentBrandMajorVersionListInternal(
      /*enable_updated_grease_by_policy=*/true, additional_brand_version);
}

const blink::UserAgentBrandList GetUserAgentBrandFullVersionList(
    std::optional<blink::UserAgentBrandVersion> additional_brand_version) {
  return GetUserAgentBrandFullVersionListInternal(
      /*enable_updated_grease_by_policy=*/true, additional_brand_version);
=======
  std::string product = GetProduct();
#if defined(OS_ANDROID)
  if (command_line->HasSwitch(switches::kUseMobileUserAgent))
    product += " Mobile";
#endif
  return content::BuildUserAgentFromProduct(product);
>>>>>>> chromium
}

// Generate a pseudo-random permutation of the following brand/version pairs:
//   1. The base project (i.e. Chromium)
//   2. The browser brand, if available
//   3. A randomized string containing escaped characters to ensure proper
//      header parsing, along with an arbitrarily low version to ensure proper
//      version checking.
blink::UserAgentBrandList GenerateBrandVersionList(
    int seed,
<<<<<<< HEAD
    std::optional<std::string> brand,
    const std::string& version,
    bool enable_updated_grease_by_policy,
    blink::UserAgentBrandVersionType output_version_type,
    std::optional<blink::UserAgentBrandVersion> additional_brand_version) {
=======
    absl::optional<std::string> brand,
    std::string major_version,
    absl::optional<std::string> maybe_greasey_brand) {
>>>>>>> chromium
  DCHECK_GE(seed, 0);
  const int npermutations = 6;  // 3!
  int permutation = seed % npermutations;

<<<<<<< HEAD
  blink::UserAgentBrandVersion greasey_bv = GetGreasedUserAgentBrandVersion(
      seed, enable_updated_grease_by_policy, output_version_type);
  blink::UserAgentBrandVersion chromium_bv = {"Chromium", version};
=======
  // Pick a stable permutation seeded by major version number. any values here
  // and in order should be under three.
  const std::vector<std::vector<int>> orders{{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
                                             {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
  const std::vector<int> order = orders[permutation];
  DCHECK_EQ(6u, orders.size());
  DCHECK_EQ(3u, order.size());

  // Previous values for indexes 0 and 1 were '\' and '"', temporarily removed
  // because of compat issues
  const std::vector<std::string> escaped_chars = {" ", " ", ";"};
  std::string greasey_brand =
      base::StrCat({escaped_chars[order[0]], "Not", escaped_chars[order[1]],
                    "A", escaped_chars[order[2]], "Brand"});

  blink::UserAgentBrandVersion greasey_bv = {
      maybe_greasey_brand.value_or(greasey_brand), "99"};
  blink::UserAgentBrandVersion chromium_bv = {"Chromium", major_version};

  blink::UserAgentBrandList greased_brand_version_list(3);
>>>>>>> chromium

  if (brand) {
    blink::UserAgentBrandVersion brand_bv = {brand.value(), major_version};

    greased_brand_version_list[order[0]] = greasey_bv;
    greased_brand_version_list[order[1]] = chromium_bv;
    greased_brand_version_list[order[2]] = brand_bv;
  } else {
    greased_brand_version_list[seed % 2] = greasey_bv;
    greased_brand_version_list[(seed + 1) % 2] = chromium_bv;

    // If left, the last element would make a blank "" at the end of the header.
    greased_brand_version_list.pop_back();
  }

  return greased_brand_version_list;
}

<<<<<<< HEAD
blink::UserAgentBrandVersion GetGreasedUserAgentBrandVersion(
    int seed,
    bool enable_updated_grease_by_policy,
    blink::UserAgentBrandVersionType output_version_type) {
  std::string greasey_brand;
  std::string greasey_version;
  // The updated algorithm is enabled by default, but we maintain the ability
  // to opt out of it either via Finch (setting updated_algorithm to false) or
  // via an enterprise policy escape hatch.
  if (enable_updated_grease_by_policy) {
    const std::vector<std::string> greasey_chars = {
        " ", "(", ":", "-", ".", "/", ")", ";", "=", "?", "_"};
    const std::vector<std::string> greased_versions = {"8", "99", "24"};
    // See the spec:
    // https://wicg.github.io/ua-client-hints/#create-arbitrary-brands-section
    greasey_brand = base::StrCat(
        {"Not", greasey_chars[(seed) % greasey_chars.size()], "A",
         greasey_chars[(seed + 1) % greasey_chars.size()], "Brand"});
    greasey_version = greased_versions[seed % greased_versions.size()];

    return GetProcessedGreasedBrandVersion(greasey_brand, greasey_version,
                                           output_version_type);
  } else {
    const std::vector<std::string> greasey_chars = {" ", " ", ";"};
    const std::vector<size_t> permuted_order =
        GetRandomOrder(seed, greasey_chars.size());
    CHECK_EQ(greasey_chars.size(), permuted_order.size());
    greasey_brand = base::StrCat({greasey_chars[permuted_order[0]], "Not",
                                  greasey_chars[permuted_order[1]], "A",
                                  greasey_chars[permuted_order[2]], "Brand"});
    greasey_version = "99";

    // The old algorithm is held constant; it does not respond to experiment
    // overrides.
    return GetProcessedGreasedBrandVersion(greasey_brand, greasey_version,
                                           output_version_type);
  }
=======
const blink::UserAgentBrandList& GetBrandVersionList() {
  static const base::NoDestructor<blink::UserAgentBrandList>
      greased_brand_version_list([] {
        int major_version_number;
        std::string major_version = version_info::GetMajorVersionNumber();
        base::StringToInt(major_version, &major_version_number);
        absl::optional<std::string> brand;
#if !BUILDFLAG(CHROMIUM_BRANDING)
        brand = version_info::GetProductName();
#endif
        absl::optional<std::string> maybe_param_override =
            base::GetFieldTrialParamValueByFeature(features::kGreaseUACH,
                                                   "brand_override");
        if (maybe_param_override->empty())
          maybe_param_override = absl::nullopt;

        return GenerateBrandVersionList(major_version_number, brand,
                                        major_version, maybe_param_override);
      }());
  return *greased_brand_version_list;
>>>>>>> chromium
}

// TODO(crbug.com/1103047): This can be removed/re-refactored once we use
// "macOS" by default
std::string GetPlatformForUAMetadata() {
#if defined(OS_MAC)
  return "macOS";
#else
  return version_info::GetOSType();
#endif
}

blink::UserAgentMetadata GetUserAgentMetadata() {
  blink::UserAgentMetadata metadata;

  metadata.brand_version_list = GetBrandVersionList();
  metadata.full_version = version_info::GetVersionNumber();
  metadata.platform = GetPlatformForUAMetadata();
  metadata.architecture = content::GetLowEntropyCpuArchitecture();
  metadata.model = content::BuildModelInfo();
  metadata.mobile = false;
#if defined(OS_ANDROID)
  metadata.mobile = base::CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kUseMobileUserAgent);
#endif

<<<<<<< HEAD
  // For users providing a valid user-agent override via the command line:
  // If kUACHOverrideBlank is enabled, set user-agent metadata with the
  // default blank values, otherwise return the default UserAgentMetadata values
  // to populate and send only the low entropy client hints.
  // Notes: Sending low entropy hints with empty values may cause requests being
  // blocked by web application firewall software, etc.
  std::optional<std::string> custom_ua = GetUserAgentFromCommandLine();
  if (custom_ua.has_value()) {
    return base::FeatureList::IsEnabled(blink::features::kUACHOverrideBlank)
               ? blink::UserAgentMetadata()
               : metadata;
  }

  if (only_low_entropy_ch) {
    return metadata;
  }

  // High entropy client hints.
  metadata.brand_full_version_list = GetUserAgentBrandFullVersionListInternal(
      enable_updated_grease_by_policy, std::nullopt);
  metadata.full_version = std::string(version_info::GetVersionNumber());
  metadata.architecture = content::GetCpuArchitecture();
  metadata.model = content::BuildModelInfo();
  metadata.form_factors = GetFormFactorsClientHint(metadata, metadata.mobile);
  metadata.bitness = content::GetCpuBitness();
  metadata.wow64 = content::IsWoW64();

#if BUILDFLAG(IS_WIN)
  metadata.platform_version = GetWindowsPlatformVersion();
#else
=======
>>>>>>> chromium
  int32_t major, minor, bugfix = 0;
  base::SysInfo::OperatingSystemVersionNumbers(&major, &minor, &bugfix);
  metadata.platform_version =
      base::StringPrintf("%d.%d.%d", major, minor, bugfix);
<<<<<<< HEAD
#endif
=======
  // These methods use the same information as the User-Agent string, but are
  // "low entropy" in that they reduce the number of options for output to a
  // set number. For more information, see the respective headers.
  metadata.architecture = content::GetLowEntropyCpuArchitecture();
  metadata.bitness = content::GetLowEntropyCpuBitness();
>>>>>>> chromium

  return metadata;
}

#if defined(OS_ANDROID)
void SetDesktopUserAgentOverride(content::WebContents* web_contents,
                                 const blink::UserAgentMetadata& metadata,
                                 bool override_in_new_tabs) {
  const char kLinuxInfoStr[] = "X11; Linux x86_64";
  std::string product = version_info::GetProductNameAndVersionForUserAgent();

  blink::UserAgentOverride spoofed_ua;
  spoofed_ua.ua_string_override =
      content::BuildUserAgentFromOSAndProduct(kLinuxInfoStr, product);
  spoofed_ua.ua_metadata_override = metadata;
  spoofed_ua.ua_metadata_override->platform = "Linux";
  spoofed_ua.ua_metadata_override->platform_version =
      std::string();  // match content::GetOSVersion(false) on Linux
  spoofed_ua.ua_metadata_override->model = std::string();
  spoofed_ua.ua_metadata_override->mobile = false;
  // Match the above "CpuInfo" string, which is also the most common Linux
  // CPU architecture and bitness.`
  spoofed_ua.ua_metadata_override->architecture = "x86";
  spoofed_ua.ua_metadata_override->bitness = "64";

  web_contents->SetUserAgentOverride(spoofed_ua, override_in_new_tabs);
}
#endif  // OS_ANDROID

}  // namespace embedder_support
