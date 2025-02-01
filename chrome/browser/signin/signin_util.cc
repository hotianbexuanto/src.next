// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/signin/signin_util.h"

#include <memory>

#include "base/bind.h"
#include "base/macros.h"
#include "base/strings/utf_string_conversions.h"
#include "base/supports_user_data.h"
#include "base/task/post_task.h"
#include "base/threading/thread_task_runner_handle.h"
#include "build/build_config.h"
#include "build/chromeos_buildflags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/policy/cloud/user_policy_signin_service_internal.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profiles_state.h"
#include "chrome/browser/signin/identity_manager_factory.h"
#include "chrome/browser/ui/simple_message_box.h"
#include "chrome/browser/ui/startup/startup_types.h"
#include "chrome/browser/ui/webui/profile_helper.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/url_constants.h"
#include "chrome/grit/generated_resources.h"
#include "components/google/core/common/google_util.h"
#include "components/prefs/pref_service.h"
#include "components/signin/public/base/signin_metrics.h"
#include "components/signin/public/base/signin_pref_names.h"
#include "components/signin/public/identity_manager/identity_manager.h"
#include "components/signin/public/identity_manager/identity_utils.h"
#include "components/signin/public/identity_manager/primary_account_mutator.h"
#include "google_apis/gaia/gaia_auth_util.h"
<<<<<<< HEAD
#include "google_apis/gaia/gaia_constants.h"
#include "google_apis/gaia/gaia_id.h"
#include "net/cookies/canonical_cookie.h"
#include "services/network/public/mojom/cookie_manager.mojom.h"
=======
>>>>>>> chromium
#include "ui/base/l10n/l10n_util.h"

#if defined(OS_WIN) || defined(OS_LINUX) || defined(OS_CHROMEOS) || \
    defined(OS_MAC)
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/browser_list_observer.h"
#include "chrome/browser/ui/browser_window.h"
#define CAN_DELETE_PROFILE
#endif

namespace signin_util {
namespace {

constexpr char kSignoutSettingKey[] = "signout_setting";

#if defined(CAN_DELETE_PROFILE)
// Manager that presents the profile will be deleted dialog on the first active
// browser window.
class DeleteProfileDialogManager : public BrowserListObserver {
 public:
  class Delegate {
   public:
    // Called when the profile was marked for deletion. It is safe for the
    // delegate to delete |manager| when this is called.
    virtual void OnProfileDeleted(DeleteProfileDialogManager* manager) = 0;
  };

  DeleteProfileDialogManager(Profile* profile,
                             std::string primary_account_email,
                             Delegate* delegate)
      : profile_(profile),
        primary_account_email_(primary_account_email),
        delegate_(delegate) {}

  ~DeleteProfileDialogManager() override { BrowserList::RemoveObserver(this); }

  void PresentDialogOnAllBrowserWindows() {
    BrowserList::AddObserver(this);
    Browser* active_browser = chrome::FindLastActiveWithProfile(profile_);
    if (active_browser)
      OnBrowserSetLastActive(active_browser);
  }

  void OnBrowserSetLastActive(Browser* browser) override {
    DCHECK(profile_);
    if (browser->profile() != profile_)
      return;

    DCHECK(browser->window()->GetNativeWindow());
    chrome::ShowWarningMessageBox(
        browser->window()->GetNativeWindow(),
        l10n_util::GetStringUTF16(IDS_PROFILE_WILL_BE_DELETED_DIALOG_TITLE),
        l10n_util::GetStringFUTF16(
            IDS_PROFILE_WILL_BE_DELETED_DIALOG_DESCRIPTION,
            base::ASCIIToUTF16(primary_account_email_),
            base::ASCIIToUTF16(
                gaia::ExtractDomainName(primary_account_email_))));

    webui::DeleteProfileAtPath(
        profile_->GetPath(),
        ProfileMetrics::DELETE_PROFILE_PRIMARY_ACCOUNT_NOT_ALLOWED);
    delegate_->OnProfileDeleted(this);
  }

 private:
  Profile* profile_;
  std::string primary_account_email_;
  Delegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(DeleteProfileDialogManager);
};
#endif  // defined(CAN_DELETE_PROFILE)

// Per-profile manager for the signout allowed setting.
#if defined(CAN_DELETE_PROFILE)
class UserSignoutSetting : public base::SupportsUserData::Data,
                           public DeleteProfileDialogManager::Delegate {
#else
class UserSignoutSetting : public base::SupportsUserData::Data {
#endif  // defined(CAN_DELETE_PROFILE)
 public:
  enum class State { kUndefined, kAllowed, kDisallowed };

  // Fetch from Profile. Make and store if not already present.
  static UserSignoutSetting* GetForProfile(Profile* profile) {
    UserSignoutSetting* signout_setting = static_cast<UserSignoutSetting*>(
        profile->GetUserData(kSignoutSettingKey));

    if (!signout_setting) {
      profile->SetUserData(kSignoutSettingKey,
                           std::make_unique<UserSignoutSetting>());
      signout_setting = static_cast<UserSignoutSetting*>(
          profile->GetUserData(kSignoutSettingKey));
    }

    return signout_setting;
  }

  State state() const { return state_; }
  void set_state(State state) { state_ = state; }

#if defined(CAN_DELETE_PROFILE)
  // Shows the delete profile dialog on the first browser active window.
  void ShowDeleteProfileDialog(Profile* profile, const std::string& email) {
    if (delete_profile_dialog_manager_)
      return;
    delete_profile_dialog_manager_ =
        std::make_unique<DeleteProfileDialogManager>(profile, email, this);
    delete_profile_dialog_manager_->PresentDialogOnAllBrowserWindows();
  }

  void OnProfileDeleted(DeleteProfileDialogManager* dialog_manager) override {
    DCHECK_EQ(delete_profile_dialog_manager_.get(), dialog_manager);
    delete_profile_dialog_manager_.reset();
  }
#endif

 private:
  State state_ = State::kUndefined;

#if defined(CAN_DELETE_PROFILE)
  std::unique_ptr<DeleteProfileDialogManager> delete_profile_dialog_manager_;
#endif
};

enum ForceSigninPolicyCache {
  NOT_CACHED = 0,
  ENABLE,
  DISABLE
} g_is_force_signin_enabled_cache = NOT_CACHED;

void SetForceSigninPolicy(bool enable) {
  g_is_force_signin_enabled_cache = enable ? ENABLE : DISABLE;
}

}  // namespace

ScopedForceSigninSetterForTesting::ScopedForceSigninSetterForTesting(
    bool enable) {
  SetForceSigninForTesting(enable);  // IN-TEST
}

ScopedForceSigninSetterForTesting::~ScopedForceSigninSetterForTesting() {
  ResetForceSigninForTesting();  // IN-TEST
}

bool IsForceSigninEnabled() {
  if (g_is_force_signin_enabled_cache == NOT_CACHED) {
    PrefService* prefs = g_browser_process->local_state();
    if (prefs)
      SetForceSigninPolicy(prefs->GetBoolean(prefs::kForceBrowserSignin));
    else
      return false;
  }
  return (g_is_force_signin_enabled_cache == ENABLE);
}

void SetForceSigninForTesting(bool enable) {
  SetForceSigninPolicy(enable);
}

void ResetForceSigninForTesting() {
  g_is_force_signin_enabled_cache = NOT_CACHED;
}

<<<<<<< HEAD
bool IsProfileDeletionAllowed(Profile* profile) {
#if BUILDFLAG(IS_ANDROID)
  return false;
#else
  return true;
#endif
=======
bool IsUserSignoutAllowedForProfile(Profile* profile) {
  return UserSignoutSetting::GetForProfile(profile)->state() ==
         UserSignoutSetting::State::kAllowed;
>>>>>>> chromium
}

void EnsureUserSignoutAllowedIsInitializedForProfile(Profile* profile) {
  if (UserSignoutSetting::GetForProfile(profile)->state() ==
      UserSignoutSetting::State::kUndefined) {
    SetUserSignoutAllowedForProfile(profile, true);
  }
}

void SetUserSignoutAllowedForProfile(Profile* profile, bool is_allowed) {
  UserSignoutSetting::State new_state =
      is_allowed ? UserSignoutSetting::State::kAllowed
                 : UserSignoutSetting::State::kDisallowed;
  UserSignoutSetting::GetForProfile(profile)->set_state(new_state);
}

<<<<<<< HEAD
bool ProfileSeparationAllowsKeepingUnmanagedBrowsingDataInManagedProfile(
    Profile* profile,
    const policy::ProfileSeparationPolicies&
        intercepted_account_separation_policies) {
  // We should not move managed data.
  if (enterprise_util::UserAcceptedAccountManagement(profile)) {
    return false;
  }

  std::string legacy_policy_for_intercepted_profile =
      intercepted_account_separation_policies
          .managed_accounts_signin_restrictions()
          .value_or(std::string());
  std::string legacy_policy_for_current_profile =
      profile->GetPrefs()->GetString(prefs::kManagedAccountsSigninRestriction);
  bool allowed_by_existing_profile =
      legacy_policy_for_current_profile.empty() ||
      legacy_policy_for_current_profile == "none" ||
      base::EndsWith(legacy_policy_for_current_profile, "keep_existing_data");
  bool allowed_by_intercepted_account =
      intercepted_account_separation_policies
              .profile_separation_data_migration_settings()
              .value_or(policy::ProfileSeparationDataMigrationSettings::
                            USER_OPT_IN) !=
          policy::ProfileSeparationDataMigrationSettings::ALWAYS_SEPARATE &&
      (legacy_policy_for_intercepted_profile.empty() ||
       legacy_policy_for_intercepted_profile == "none" ||
       base::EndsWith(legacy_policy_for_intercepted_profile,
                      "keep_existing_data"));
  return allowed_by_existing_profile && allowed_by_intercepted_account;
}

bool IsAccountExemptedFromEnterpriseProfileSeparation(
    Profile* profile,
    const std::string& email) {
  if (profile->GetPrefs()
          ->FindPreference(prefs::kProfileSeparationDomainExceptionList)
          ->IsDefaultValue()) {
    return true;
  }

  const std::string domain = gaia::ExtractDomainName(email);
  const auto& allowed_domains = profile->GetPrefs()->GetList(
      prefs::kProfileSeparationDomainExceptionList);
  return base::Contains(allowed_domains, base::Value(domain));
}
#endif  // !BUILDFLAG(IS_CHROMEOS)

void RecordEnterpriseProfileCreationUserChoice(bool enforced_by_policy,
                                               bool created) {
  base::UmaHistogramBoolean(
      enforced_by_policy
          ? "Signin.Enterprise.WorkProfile.ProfileCreatedWithPolicySet"
          : "Signin.Enterprise.WorkProfile.ProfileCreatedwithPolicyUnset",
      created);
}

#endif  // !BUILDFLAG(IS_ANDROID)

PrimaryAccountError SetPrimaryAccountWithInvalidToken(
    Profile* profile,
    const std::string& user_email,
    const GaiaId& gaia_id,
    bool is_under_advanced_protection,
    signin_metrics::AccessPoint access_point,
    signin_metrics::SourceForRefreshTokenOperation source) {
=======
void EnsurePrimaryAccountAllowedForProfile(Profile* profile) {
// All primary accounts are allowed on ChromeOS, so this method is a no-op on
// ChromeOS.
#if !BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
  auto* identity_manager = IdentityManagerFactory::GetForProfile(profile);
  if (!identity_manager->HasPrimaryAccount(signin::ConsentLevel::kSync))
    return;

  CoreAccountInfo primary_account =
      identity_manager->GetPrimaryAccountInfo(signin::ConsentLevel::kSync);
  if (profile->GetPrefs()->GetBoolean(prefs::kSigninAllowed) &&
      signin::IsUsernameAllowedByPatternFromPrefs(
          g_browser_process->local_state(), primary_account.email)) {
    return;
  }

<<<<<<< HEAD
  DVLOG(1) << "Adding user with gaia id <" << gaia_id << "> and email <"
           << user_email << "> with invalid refresh token.";

  // Lock AccountReconcilor temporarily to prevent AddOrUpdateAccount failure
  // since we have an invalid refresh token.
  AccountReconcilor::Lock account_reconcilor_lock(
      AccountReconcilorFactory::GetForProfile(profile));

  CoreAccountId account_id =
      identity_manager->GetAccountsMutator()->AddOrUpdateAccount(
          gaia_id, user_email, GaiaConstants::kInvalidRefreshToken,
          is_under_advanced_protection, access_point, source);

  DVLOG(1) << "Account id <" << account_id.ToString()
           << "> has been added to the profile with invalid token.";

  auto set_primary_account_result =
      identity_manager->GetPrimaryAccountMutator()->SetPrimaryAccount(
          account_id, signin::ConsentLevel::kSignin);
  DVLOG(1) << "Operation of setting account id <" << account_id.ToString()
           << "> received the following result: "
           << static_cast<int>(set_primary_account_result);

  return set_primary_account_result;
}

bool IsSigninPending(signin::IdentityManager* identity_manager) {
  return !identity_manager->HasPrimaryAccount(signin::ConsentLevel::kSync) &&
         identity_manager->HasPrimaryAccount(signin::ConsentLevel::kSignin) &&
         identity_manager->HasAccountWithRefreshTokenInPersistentErrorState(
             identity_manager->GetPrimaryAccountId(
                 signin::ConsentLevel::kSignin));
}

SignedInState GetSignedInState(
    const signin::IdentityManager* identity_manager) {
  if (!identity_manager) {
    return SignedInState::kSignedOut;
  }

  if (identity_manager->HasPrimaryAccount(signin::ConsentLevel::kSync)) {
    if (identity_manager->HasAccountWithRefreshTokenInPersistentErrorState(
            identity_manager->GetPrimaryAccountId(
                signin::ConsentLevel::kSync))) {
      return SignedInState::kSyncPaused;
=======
  UserSignoutSetting* signout_setting =
      UserSignoutSetting::GetForProfile(profile);
  switch (signout_setting->state()) {
    case UserSignoutSetting::State::kUndefined:
      NOTREACHED();
      break;
    case UserSignoutSetting::State::kAllowed: {
      // Force clear the primary account if it is no longer allowed and if sign
      // out is allowed.
      auto* primary_account_mutator =
          identity_manager->GetPrimaryAccountMutator();
      primary_account_mutator->ClearPrimaryAccount(
          signin_metrics::SIGNIN_NOT_ALLOWED_ON_PROFILE_INIT,
          signin_metrics::SignoutDelete::kIgnoreMetric);
      break;
>>>>>>> chromium
    }
    case UserSignoutSetting::State::kDisallowed:
#if defined(CAN_DELETE_PROFILE)
      // Force remove the profile if sign out is not allowed and if the
      // primary account is no longer allowed.
      // This may be called while the profile is initializing, so it must be
      // scheduled for later to allow the profile initialization to complete.
      CHECK(profiles::IsMultipleProfilesEnabled());
      base::ThreadTaskRunnerHandle::Get()->PostTask(
          FROM_HERE,
          base::BindOnce(&UserSignoutSetting::ShowDeleteProfileDialog,
                         base::Unretained(signout_setting), profile,
                         primary_account.email));
#else
      CHECK(false) << "Deleting profiles is not supported.";
#endif  // defined(CAN_DELETE_PROFILE)
      break;
  }
#endif  // !BUILDFLAG(IS_CHROMEOS_ASH)
}

}  // namespace signin_util
