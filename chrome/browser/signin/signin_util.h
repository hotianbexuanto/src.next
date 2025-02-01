// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SIGNIN_UTIL_H_
#define CHROME_BROWSER_SIGNIN_SIGNIN_UTIL_H_

<<<<<<< HEAD
#include <optional>
#include <string>

#include "base/containers/enum_set.h"
#include "base/files/file_path.h"
#include "base/functional/callback.h"
#include "base/supports_user_data.h"
#include "build/build_config.h"
#include "build/chromeos_buildflags.h"
#include "components/policy/core/browser/signin/profile_separation_policies.h"
#include "components/signin/public/base/signin_metrics.h"
#include "components/signin/public/identity_manager/primary_account_mutator.h"
#include "components/signin/public/identity_manager/tribool.h"
#include "net/cookies/canonical_cookie.h"

class GaiaId;
=======
>>>>>>> chromium
class Profile;

namespace signin_util {

// This class calls ResetForceSigninForTesting when destroyed, so that
// ForcedSigning doesn't leak across tests.
class ScopedForceSigninSetterForTesting {
 public:
  explicit ScopedForceSigninSetterForTesting(bool enable);
  ~ScopedForceSigninSetterForTesting();
};

// Return whether the force sign in policy is enabled or not.
// The state of this policy will not be changed without relaunch Chrome.
bool IsForceSigninEnabled();

// Enable or disable force sign in for testing. Please use
// ScopedForceSigninSetterForTesting instead, if possible. If not, make sure
// ResetForceSigninForTesting is called before the test finishes.
void SetForceSigninForTesting(bool enable);

// Reset force sign in to uninitialized state for testing.
void ResetForceSigninForTesting();

// Returns true if clearing the primary profile is allowed.
bool IsUserSignoutAllowedForProfile(Profile* profile);

// Sign-out is allowed by default, but some Chrome profiles (e.g. for cloud-
// managed enterprise accounts) may wish to disallow user-initiated sign-out.
// Note that this exempts sign-outs that are not user-initiated (e.g. sign-out
// triggered when cloud policy no longer allows current email pattern). See
// ChromeSigninClient::PreSignOut().
void SetUserSignoutAllowedForProfile(Profile* profile, bool is_allowed);

// Updates the user sign-out state to |true| if is was never initialized.
// This should be called at the end of the flow to initialize a profile to
// ensure that the signout allowed flag is updated.
void EnsureUserSignoutAllowedIsInitializedForProfile(Profile* profile);

<<<<<<< HEAD
// Returns true if profile separation is enforced by
// `intercepted_account_separation_policies`.
bool IsProfileSeparationEnforcedByPolicies(
    const policy::ProfileSeparationPolicies&
        intercepted_profile_separation_policies);

bool ProfileSeparationAllowsKeepingUnmanagedBrowsingDataInManagedProfile(
    Profile* profile,
    const policy::ProfileSeparationPolicies&
        intercepted_profile_separation_policies);

bool IsAccountExemptedFromEnterpriseProfileSeparation(Profile* profile,
                                                      const std::string& email);
#endif  // !BUILDFLAG(IS_CHROMEOS)
// Records a UMA metric if the user accepts or not to create an enterprise
// profile.
void RecordEnterpriseProfileCreationUserChoice(bool enforced_by_policy,
                                               bool created);
#endif  // !BUILDFLAG(IS_ANDROID)

// TODO(b/339214136): Add a standalone unit for this function.
// Add an account with `user_email` and `gaia_id` to `profile`, and then set it
// as the primary account. A invalid refresh token will be set to mimic the
// behavior of a signed-out user. It is expected that the user is not tracked
// yet.
PrimaryAccountError SetPrimaryAccountWithInvalidToken(
    Profile* profile,
    const std::string& user_email,
    const GaiaId& gaia_id,
    bool is_under_advanced_protection,
    signin_metrics::AccessPoint access_point,
    signin_metrics::SourceForRefreshTokenOperation source);

// Returns true if the Chrome is signed into with an account that is in
// persistent error state. Always return false for Syncing users, even if in
// error state.
bool IsSigninPending(signin::IdentityManager* identity_manager);

// Returns the current state of the primary account that is used in Chrome.
SignedInState GetSignedInState(const signin::IdentityManager* identity_manager);
=======
// Ensures that the primary account for |profile| is allowed:
// * If profile does not have any primary account, then this is a no-op.
// * If |IsUserSignoutAllowedForProfile| is allowed and the primary account
//   is no longer allowed, then this clears the primary account.
// * If |IsUserSignoutAllowedForProfile| is not allowed and the primary account
//   is not longer allowed, then this removes the profile.
void EnsurePrimaryAccountAllowedForProfile(Profile* profile);
>>>>>>> chromium

}  // namespace signin_util

#endif  // CHROME_BROWSER_SIGNIN_SIGNIN_UTIL_H_
