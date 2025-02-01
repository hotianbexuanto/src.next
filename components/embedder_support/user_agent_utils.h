// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_EMBEDDER_SUPPORT_USER_AGENT_UTILS_H_
#define COMPONENTS_EMBEDDER_SUPPORT_USER_AGENT_UTILS_H_

#include <string>

#include "build/build_config.h"
#include "third_party/blink/public/common/user_agent/user_agent_metadata.h"

namespace blink {
struct UserAgentMetadata;
}

namespace content {
class WebContents;
}

namespace embedder_support {

// Returns the product used in building the user-agent.
std::string GetProduct();

// Returns the user agent string for Chrome.
std::string GetUserAgent();

<<<<<<< HEAD
// Returns a user agent string passed via the kUserAgent command-line argument
// when it is valid, or std::nullopt if it is not valid.
std::optional<std::string> GetUserAgentFromCommandLine();

// Returns the full or "reduced" user agent string, depending on the following:
// 1) UserAgentReduction enterprise policy.
// 2) Reduce User-Agent reduction phase features.
// TODO(crbug.com/40212812): modify to accept an optional PrefService*.
std::string GetUserAgent(
    UserAgentReductionEnterprisePolicyState user_agent_reduction =
        UserAgentReductionEnterprisePolicyState::kDefault);
=======
blink::UserAgentMetadata GetUserAgentMetadata();
>>>>>>> chromium

blink::UserAgentBrandList GenerateBrandVersionList(
    int seed,
<<<<<<< HEAD
    std::optional<std::string> brand,
    const std::string& version,
    bool enable_updated_grease_by_policy,
    blink::UserAgentBrandVersionType output_version_type,
    std::optional<blink::UserAgentBrandVersion> additional_brand_version =
        std::nullopt);

// Return UserAgentBrandList with full versions based on the additional brand
// version list if provided. It generates a pseudo-random permutation of the
// following brand/full_version pairs:
//   1. The base project (i.e. Chromium)
//   2. The browser brand, if available
//   3. A randomized string containing GREASE characters to ensure proper
//      header parsing, along with an arbitrarily low version to ensure proper
//      version checking.
//   4. Additional brand/full_version pairs.
const blink::UserAgentBrandList GetUserAgentBrandFullVersionList(
    std::optional<blink::UserAgentBrandVersion> additional_brand_version =
        std::nullopt);

// Return UserAgentBrandList with major versions based on the additional brand
// version list if provided. It generates a pseudo-random permutation of the
// following brand/major_version pairs:
//   1. The base project (i.e. Chromium)
//   2. The browser brand, if available
//   3. A randomized string containing GREASE characters to ensure proper
//      header parsing, along with an arbitrarily low version to ensure proper
//      version checking.
//   4. Additional brand/major_version pairs.
const blink::UserAgentBrandList GetUserAgentBrandMajorVersionList(
    std::optional<blink::UserAgentBrandVersion> additional_brand_version =
        std::nullopt);

// Return greased UserAgentBrandVersion to prevent assumptions about the
// current values being baked into implementations. See
// https://wicg.github.io/ua-client-hints/#create-arbitrary-brands-section.
blink::UserAgentBrandVersion GetGreasedUserAgentBrandVersion(
    int seed,
    bool enable_updated_grease_by_policy,
    blink::UserAgentBrandVersionType output_version_type);

#if BUILDFLAG(IS_ANDROID)
=======
    absl::optional<std::string> brand,
    std::string major_version,
    absl::optional<std::string> maybe_greasey_brand);

#if defined(OS_ANDROID)
>>>>>>> chromium
// This sets a user agent string to simulate a desktop user agent on mobile.
// If |override_in_new_tabs| is true, and the first navigation in the tab is
// renderer initiated, then is-overriding-user-agent is set to true for the
// NavigationEntry.
void SetDesktopUserAgentOverride(content::WebContents* web_contents,
                                 const blink::UserAgentMetadata& metadata,
                                 bool override_in_new_tabs);
#endif

}  // namespace embedder_support

#endif  // COMPONENTS_EMBEDDER_SUPPORT_USER_AGENT_UTILS_H_
