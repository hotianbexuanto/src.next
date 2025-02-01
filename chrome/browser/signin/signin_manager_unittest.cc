// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include "chrome/browser/signin/signin_manager.h"

#include "components/signin/public/identity_manager/accounts_in_cookie_jar_info.h"
#include "components/signin/public/identity_manager/identity_manager.h"
#include "components/signin/public/identity_manager/identity_test_environment.h"
#include "components/signin/public/identity_manager/identity_test_utils.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using ::testing::_;
using ::testing::Mock;

namespace signin {
namespace {
const char kTestEmail[] = "me@gmail.com";
const char kTestEmail2[] = "me2@gmail.com";

class FakeIdentityManagerObserver : public IdentityManager::Observer {
 public:
  explicit FakeIdentityManagerObserver(IdentityManager* identity_manager)
      : identity_manager_(identity_manager) {}
  ~FakeIdentityManagerObserver() override = default;

  void OnPrimaryAccountChanged(
      const PrimaryAccountChangeEvent& event) override {
    auto current_state = event.GetCurrentState();
    EXPECT_EQ(
        current_state.primary_account,
        identity_manager_->GetPrimaryAccountInfo(current_state.consent_level));
    events_.push_back(event);
  }

  const std::vector<PrimaryAccountChangeEvent>& events() const {
    return events_;
  }

  void Reset() { events_.clear(); }

 private:
  IdentityManager* identity_manager_;
  std::vector<PrimaryAccountChangeEvent> events_;
};
}  // namespace

class SigninManagerTest : public testing::Test {
 public:
  SigninManagerTest()
      : identity_test_env_(/*test_url_loader_factory=*/nullptr,
                           /*pref_service=*/nullptr,
                           signin::AccountConsistencyMethod::kDice,
                           /*test_signin_client=*/nullptr),
        observer_(identity_test_env_.identity_manager()) {}

  void SetUp() override {
    testing::Test::SetUp();
    RecreateSigninManager();
    identity_manager()->AddObserver(&observer_);
  }

  void TearDown() override { identity_manager()->RemoveObserver(&observer_); }

  void RecreateSigninManager() {
    signin_manger_ = std::make_unique<SigninManager>(identity_manager());
  }

<<<<<<< HEAD
  void InitializeSignoutDecision() {
    if (!is_signout_allowed()) {
      client_.set_is_clear_primary_account_allowed_for_testing(
          SigninClient::SignoutDecision::CLEAR_PRIMARY_ACCOUNT_DISALLOWED);
    }
  }

  bool is_signout_allowed() const { return GetParam().is_signout_allowed; }

  bool explicit_browser_signin() {
    // The `SigninManager` will not automatically set the primary account.
    // The account will be updated only if it was implicitly sign in.
    // In practice, this can only happen if the user was signed in prior to the
    // feature being enabled.
    return GetParam().explicit_browser_signin;
  }

  void Signin(const std::string& email,
              signin_metrics::AccessPoint access_point,
              ConsentLevel consent_level) {
    identity_test_env()->MakeAccountAvailable(
        identity_test_env()
            ->CreateAccountAvailabilityOptionsBuilder()
            .WithAccessPoint(access_point)
            .AsPrimary(consent_level)
            .Build(email));
    CHECK(identity_manager()->HasPrimaryAccount(consent_level));
  }

  void SigninImplicitlyWithAccount(
      const std::string& email,
      ConsentLevel consent_level = ConsentLevel::kSignin) {
    Signin(email, signin_metrics::AccessPoint::kWebSignin, consent_level);
  }

  void SigninExplicitlyWithAccount(const std::string& email) {
    CHECK(base::FeatureList::IsEnabled(
        switches::kExplicitBrowserSigninUIOnDesktop));
    Signin(email, signin_metrics::AccessPoint::kAvatarBubbleSignIn,
           ConsentLevel::kSignin);
=======
  AccountInfo GetAccountInfo(const std::string& email) {
    AccountInfo account_info;
    account_info.gaia = GetTestGaiaIdForEmail(email);
    account_info.account_id =
        identity_manager()->PickAccountIdForAccount(account_info.gaia, email);
    account_info.email = email;
    return account_info;
>>>>>>> chromium
  }

  void ExpectUnconsentedPrimaryAccountSetEvent(
      const CoreAccountInfo& expected_primary_account) {
    EXPECT_EQ(1U, observer().events().size());
    auto event = observer().events()[0];
    EXPECT_EQ(PrimaryAccountChangeEvent::Type::kSet,
              event.GetEventTypeFor(ConsentLevel::kSignin));
    EXPECT_TRUE(event.GetPreviousState().primary_account.IsEmpty());
    EXPECT_EQ(expected_primary_account,
              event.GetCurrentState().primary_account);
    observer().Reset();
  }

  void ExpectUnconsentedPrimaryAccountClearedEvent(
      const CoreAccountInfo& expected_cleared_account) {
    EXPECT_EQ(1U, observer().events().size());
    auto event = observer().events()[0];
    EXPECT_EQ(PrimaryAccountChangeEvent::Type::kCleared,
              event.GetEventTypeFor(ConsentLevel::kSignin));
    EXPECT_EQ(expected_cleared_account,
              event.GetPreviousState().primary_account);
    EXPECT_TRUE(event.GetCurrentState().primary_account.IsEmpty());
    observer().Reset();
  }

  void ExpectSyncPrimaryAccountSetEvent(
      const CoreAccountInfo& expected_primary_account) {
    EXPECT_EQ(1U, observer().events().size());
    auto event = observer().events()[0];
    EXPECT_EQ(PrimaryAccountChangeEvent::Type::kSet,
              event.GetEventTypeFor(ConsentLevel::kSignin));
    EXPECT_EQ(PrimaryAccountChangeEvent::Type::kSet,
              event.GetEventTypeFor(ConsentLevel::kSync));
    EXPECT_TRUE(event.GetPreviousState().primary_account.IsEmpty());
    EXPECT_EQ(expected_primary_account,
              event.GetCurrentState().primary_account);
    observer().Reset();
  }

  IdentityManager* identity_manager() {
    return identity_test_env_.identity_manager();
  }

  IdentityTestEnvironment* identity_test_env() { return &identity_test_env_; }

<<<<<<< HEAD
  AccountInfo MakeAccountAvailableWithCookies(
      const std::string& email,
      signin_metrics::AccessPoint access_point =
          signin_metrics::AccessPoint::kUnknown) {
    AccountAvailabilityOptionsBuilder builder =
        identity_test_env()
            ->CreateAccountAvailabilityOptionsBuilder()
            .WithAccessPoint(access_point);

    AccountInfo account =
        identity_test_env_.MakeAccountAvailable(builder.Build(email));
    signin::CookieParamsForTest cookie_params = {account.email, account.gaia};
    identity_test_env_.SetCookieAccounts({cookie_params});
=======
  AccountInfo MakeAccountAvailableWithCookies(const std::string& email) {
    AccountInfo account = GetAccountInfo(kTestEmail);
    identity_test_env_.MakeAccountAvailableWithCookies(account.email,
                                                       account.gaia);
    EXPECT_FALSE(account.IsEmpty());
    EXPECT_TRUE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
    EXPECT_EQ(account,
              identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
    EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSync));
>>>>>>> chromium
    return account;
  }

  AccountInfo MakeSyncAccountAvailableWithCookies(const std::string& email) {
    AccountInfo account = identity_test_env_.MakePrimaryAccountAvailable(
        email, signin::ConsentLevel::kSync);
    identity_test_env_.SetCookieAccounts({{account.email, account.gaia}});
    EXPECT_EQ(account,
              identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
    EXPECT_EQ(account,
              identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSync));
    EXPECT_TRUE(identity_manager()->HasPrimaryAccountWithRefreshToken(
        signin::ConsentLevel::kSync));
    return account;
  }

  FakeIdentityManagerObserver& observer() { return observer_; }

  content::BrowserTaskEnvironment task_environment_;
  IdentityTestEnvironment identity_test_env_;
  std::unique_ptr<SigninManager> signin_manger_;
  FakeIdentityManagerObserver observer_;

  DISALLOW_COPY_AND_ASSIGN(SigninManagerTest);
};

TEST_F(
    SigninManagerTest,
    UnconsentedPrimaryAccountUpdatedOnItsAccountRefreshTokenUpdateWithValidTokenWhenNoSyncConsent) {
  // Add an unconsented primary account, incl. proper cookies.
  AccountInfo account = MakeAccountAvailableWithCookies(kTestEmail);
  ExpectUnconsentedPrimaryAccountSetEvent(account);
  EXPECT_EQ(account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
}

TEST_F(
    SigninManagerTest,
    UnconsentedPrimaryAccountUpdatedOnItsAccountRefreshTokenUpdateWithInvalidTokenWhenNoSyncConsent) {
  // Prerequisite: add an unconsented primary account, incl. proper cookies.
  AccountInfo account = MakeAccountAvailableWithCookies(kTestEmail);
  ExpectUnconsentedPrimaryAccountSetEvent(account);

  // Invalid token.
  SetInvalidRefreshTokenForAccount(identity_manager(), account.account_id);
  ExpectUnconsentedPrimaryAccountClearedEvent(account);
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));

  // Update with a valid token.
  SetRefreshTokenForAccount(identity_manager(), account.account_id, "");
  ExpectUnconsentedPrimaryAccountSetEvent(account);
  EXPECT_EQ(identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin),
            account);
}

TEST_F(
    SigninManagerTest,
    UnconsentedPrimaryAccountRemovedOnItsAccountRefreshTokenRemovalWhenNoSyncConsent) {
  // Prerequisite: Add an unconsented primary account, incl. proper cookies.
  AccountInfo account = MakeAccountAvailableWithCookies(kTestEmail);
  ExpectUnconsentedPrimaryAccountSetEvent(account);

  // With no refresh token, there is no unconsented primary account any more.
  identity_test_env()->RemoveRefreshTokenForAccount(account.account_id);
  ExpectUnconsentedPrimaryAccountClearedEvent(account);
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
}

TEST_F(SigninManagerTest, UnconsentedPrimaryAccountNotChangedOnSignout) {
  // Set a primary account at sync consent level.
  AccountInfo account = MakeSyncAccountAvailableWithCookies(kTestEmail);
  EXPECT_EQ(account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  EXPECT_EQ(account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSync));
  EXPECT_TRUE(identity_manager()->HasPrimaryAccountWithRefreshToken(
      signin::ConsentLevel::kSync));

  // Verify the primary account changed event.
  ExpectSyncPrimaryAccountSetEvent(account);

  // Tests that sync primary account is cleared, but unconsented account is not.
  identity_test_env()->RevokeSyncConsent();
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ(account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSync));

  EXPECT_EQ(1U, observer().events().size());
  auto event = observer().events()[0];
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kNone,
            event.GetEventTypeFor(ConsentLevel::kSignin));
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kCleared,
            event.GetEventTypeFor(ConsentLevel::kSync));
  EXPECT_EQ(account, event.GetPreviousState().primary_account);
  EXPECT_EQ(account, event.GetCurrentState().primary_account);
}

TEST_F(SigninManagerTest,
       UnconsentedPrimaryAccountTokenRevokedWithStaleCookies) {
  // Prerequisite: add an unconsented primary account, incl. proper cookies.
  AccountInfo account = MakeAccountAvailableWithCookies(kTestEmail);
  ExpectUnconsentedPrimaryAccountSetEvent(account);

  // Make the cookies stale and remove the account.
  // Removing the refresh token for the unconsented primary account is
  // sufficient to clear it.
  identity_test_env()->SetFreshnessOfAccountsInGaiaCookie(false);
  identity_test_env()->RemoveRefreshTokenForAccount(account.account_id);
  ASSERT_FALSE(identity_manager()->GetAccountsInCookieJar().accounts_are_fresh);

  // Unconsented account was removed.
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
  ExpectUnconsentedPrimaryAccountClearedEvent(account);
}

TEST_F(SigninManagerTest,
       UnconsentedPrimaryAccountTokenRevokedWithStaleCookiesMultipleAccounts) {
  // Add two accounts with cookies.
  AccountInfo main_account =
      identity_test_env()->MakeAccountAvailable(kTestEmail);
  AccountInfo secondary_account =
      identity_test_env()->MakeAccountAvailable(kTestEmail2);
  identity_test_env()->SetCookieAccounts(
      {{main_account.email, main_account.gaia},
       {secondary_account.email, secondary_account.gaia}});

  EXPECT_TRUE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSync));
  EXPECT_EQ(main_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  ExpectUnconsentedPrimaryAccountSetEvent(main_account);

  // Make the cookies stale and remove the main account.
  identity_test_env()->SetFreshnessOfAccountsInGaiaCookie(false);
  identity_test_env()->RemoveRefreshTokenForAccount(main_account.account_id);
  ASSERT_FALSE(identity_manager()->GetAccountsInCookieJar().accounts_are_fresh);

  // Unconsented account was removed.
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
  ExpectUnconsentedPrimaryAccountClearedEvent(main_account);
}

TEST_F(SigninManagerTest, UnconsentedPrimaryAccountDuringLoad) {
  // Pre-requisite: Add two accounts with cookies.
  AccountInfo main_account =
      identity_test_env()->MakeAccountAvailable(kTestEmail);
  AccountInfo secondary_account =
      identity_test_env()->MakeAccountAvailable(kTestEmail2);
  identity_test_env()->SetCookieAccounts(
      {{main_account.email, main_account.gaia},
       {secondary_account.email, secondary_account.gaia}});
  ASSERT_EQ(main_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  ASSERT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSync));
  ExpectUnconsentedPrimaryAccountSetEvent(main_account);

  // Set the token service in "loading" mode.
  identity_test_env()->ResetToAccountsNotYetLoadedFromDiskState();
  RecreateSigninManager();

  // Unconsented primary account is available while tokens are not loaded.
  EXPECT_EQ(main_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  EXPECT_TRUE(observer().events().empty());

  // Revoking an unrelated token doesn't change the unconsented primary account.
  identity_test_env()->RemoveRefreshTokenForAccount(
      secondary_account.account_id);
  EXPECT_EQ(main_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  EXPECT_TRUE(observer().events().empty());

  // Revoking the token of the unconsented primary account while the tokens
  // are still loading does not change the unconsented primary account.
  identity_test_env()->RemoveRefreshTokenForAccount(main_account.account_id);
  EXPECT_EQ(main_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  EXPECT_TRUE(observer().events().empty());

  // Finish the token load should clear the primary account as the token of the
  // primary account was revoked.
  identity_test_env()->ReloadAccountsFromDisk();
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
  ExpectUnconsentedPrimaryAccountClearedEvent(main_account);
}

TEST_F(SigninManagerTest,
       UnconsentedPrimaryAccountUpdatedOnSyncConsentRevoked) {
  AccountInfo first_account =
      identity_test_env()->MakeAccountAvailable(kTestEmail);
  AccountInfo second_account =
      identity_test_env()->MakeAccountAvailable(kTestEmail2);
  identity_test_env()->SetCookieAccounts(
      {{first_account.email, first_account.gaia},
       {second_account.email, second_account.gaia}});
  ASSERT_EQ(first_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  ExpectUnconsentedPrimaryAccountSetEvent(first_account);

  // Set the sync primary account to the second account in cookies.
  // The unconsented primary account should be updated.
  identity_test_env()->SetPrimaryAccount(second_account.email,
                                         signin::ConsentLevel::kSync);
  EXPECT_EQ(second_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSync));
  EXPECT_EQ(1U, observer().events().size());
  auto event = observer().events()[0];
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kSet,
            event.GetEventTypeFor(ConsentLevel::kSync));
  EXPECT_EQ(first_account, event.GetPreviousState().primary_account);
  EXPECT_EQ(second_account, event.GetCurrentState().primary_account);
  observer().Reset();

  // Clear primary account but do not delete the account. The unconsented
  // primary account should be updated to be the first account in cookies.
  identity_test_env()->RevokeSyncConsent();
  base::RunLoop().RunUntilIdle();

  // Primary account is cleared, but unconsented account is not.
  EXPECT_FALSE(
      identity_manager()->HasPrimaryAccount(signin::ConsentLevel::kSync));
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSync));
  EXPECT_TRUE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
  EXPECT_EQ(first_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));

  EXPECT_EQ(2U, observer().events().size());
  event = observer().events()[0];
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kCleared,
            event.GetEventTypeFor(ConsentLevel::kSync));
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kNone,
            event.GetEventTypeFor(ConsentLevel::kSignin));
  EXPECT_EQ(second_account, event.GetPreviousState().primary_account);
  EXPECT_EQ(second_account, event.GetCurrentState().primary_account);

  event = observer().events()[1];
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kNone,
            event.GetEventTypeFor(ConsentLevel::kSync));
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kSet,
            event.GetEventTypeFor(ConsentLevel::kSignin));
  EXPECT_EQ(second_account, event.GetPreviousState().primary_account);
  EXPECT_EQ(first_account, event.GetCurrentState().primary_account);
}

<<<<<<< HEAD
TEST_P(SigninManagerTest, UnconsentedPrimaryAccountUpdatedOnHandleDestroyed) {
  base::HistogramTester histogram_tester;
  AccountAvailabilityOptionsBuilder builder =
      identity_test_env()
          ->CreateAccountAvailabilityOptionsBuilder()
          .WithAccessPoint(signin_metrics::AccessPoint::kUnknown);
  AccountInfo first_account =
      identity_test_env()->MakeAccountAvailable(builder.Build(kTestEmail));
  AccountInfo second_account =
      identity_test_env()->MakeAccountAvailable(builder.Build(kTestEmail2));
  identity_test_env()->SetCookieAccounts(
      {{first_account.email, first_account.gaia},
       {second_account.email, second_account.gaia}});
  signin_metrics::AccessPoint access_point =
      signin_metrics::AccessPoint::kDesktopSigninManager;
  if (explicit_browser_signin()) {
    SigninImplicitlyWithAccount(first_account.email);
    access_point = signin_metrics::AccessPoint::kWebSignin;
  }
  ASSERT_EQ(first_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  ExpectUnconsentedPrimaryAccountSetEvent(first_account);
  if (!explicit_browser_signin()) {
    histogram_tester.ExpectUniqueSample("Signin.SignIn.Completed", access_point,
                                        1);
    histogram_tester.ExpectUniqueSample(
        "Signin.SigninManager.SigninAccessPoint", access_point, 1);
  }
  std::unique_ptr<AccountSelectionInProgressHandle> handle =
      signin_manager_->CreateAccountSelectionInProgressHandle();
  ASSERT_TRUE(handle);

  // Set the primary account to the second account in cookies. This simulates
  // that the user chose the second account as the to-be-synced account.
  // The unconsented primary account should be updated.
  SigninImplicitlyWithAccount(second_account.email);
  InitializeSignoutDecision();
  EXPECT_EQ(second_account,
            identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));
  EXPECT_FALSE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSync));
  if (!explicit_browser_signin()) {
    // TODO(crbug.com/40202341): The change should be logged in some way.
    histogram_tester.ExpectUniqueSample(
        "Signin.SignIn.Completed",
        signin_metrics::AccessPoint::kDesktopSigninManager, 1);
    histogram_tester.ExpectTotalCount("Signin.SignOut.Completed", 0);
  }
  observer().Reset();

  // Release the handle. The unconsented primary account should be updated to be
  // the first account in cookies.
  handle.reset();
  ASSERT_FALSE(handle);
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ(
#if BUILDFLAG(IS_CHROMEOS_LACROS)
      // On Lacros, the UPA is not computed based on cookies, so it won't be
      // automatically reset to the "first" account.
      second_account,
#else
      is_signout_allowed() ? first_account : second_account,
#endif
      identity_manager()->GetPrimaryAccountInfo(ConsentLevel::kSignin));

#if BUILDFLAG(IS_CHROMEOS_LACROS)
  EXPECT_EQ(0U, observer().events().size());
#else
  if (is_signout_allowed()) {
    ExpectUnconsentedPrimaryAccountChangedEvent(second_account, first_account);
  } else {
    EXPECT_EQ(0U, observer().events().size());
  }
#endif
  // TODO(crbug.com/40202341): The change should be logged in some way.
  if (!explicit_browser_signin()) {
    histogram_tester.ExpectUniqueSample(
        "Signin.SignIn.Completed",
        signin_metrics::AccessPoint::kDesktopSigninManager, 1);
    histogram_tester.ExpectTotalCount("Signin.SignOut.Completed", 0);
  }
}

TEST_P(SigninManagerTest, ClearPrimaryAccountAndSignOut) {
=======
TEST_F(SigninManagerTest, ClearPrimaryAccountAndSignOut) {
>>>>>>> chromium
  AccountInfo account = MakeSyncAccountAvailableWithCookies(kTestEmail);
  ExpectSyncPrimaryAccountSetEvent(account);

  identity_test_env()->ClearPrimaryAccount();
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ(1U, observer().events().size());
  auto event = observer().events()[0];
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kCleared,
            event.GetEventTypeFor(ConsentLevel::kSignin));
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kCleared,
            event.GetEventTypeFor(ConsentLevel::kSync));
  EXPECT_EQ(account, event.GetPreviousState().primary_account);
  EXPECT_TRUE(event.GetCurrentState().primary_account.IsEmpty());
}

<<<<<<< HEAD
// Disabling `kSigninAllowed` is not supported on Lacros.
#if !BUILDFLAG(IS_CHROMEOS_LACROS)
TEST_P(SigninManagerTest,
       UnconsentedPrimaryAccountClearedWhenSigninDisallowed) {
  // Prerequisite: add an unconsented primary account.
  AccountInfo account = MakeAccountAvailableWithCookies(kTestEmail);
  if (explicit_browser_signin()) {
    // Set the primary account and mark it to be implicitly signed in.
    SigninImplicitlyWithAccount(account.email);
  }
  ExpectUnconsentedPrimaryAccountSetEvent(account);

  prefs_.SetBoolean(prefs::kSigninAllowed, false);
  base::RunLoop().RunUntilIdle();

  EXPECT_FALSE(
      identity_manager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));

  EXPECT_EQ(1U, observer().events().size());
  auto event = observer().events()[0];
  EXPECT_EQ(PrimaryAccountChangeEvent::Type::kCleared,
            event.GetEventTypeFor(ConsentLevel::kSignin));
  EXPECT_EQ(account, event.GetPreviousState().primary_account);
  EXPECT_TRUE(event.GetCurrentState().primary_account.IsEmpty());
}
#endif  // !BUILDFLAG(IS_CHROMEOS_LACROS)

TEST_P(SigninManagerTest, SigninCompletedMetric) {
  if (explicit_browser_signin()) {
    GTEST_SKIP();
  }
  base::HistogramTester histogram_tester;

  signin_metrics::AccessPoint access_point =
      signin_metrics::AccessPoint::kSettings;
  AccountInfo account =
      MakeAccountAvailableWithCookies(kTestEmail, access_point);
  ExpectUnconsentedPrimaryAccountSetEvent(account);
  histogram_tester.ExpectUniqueSample("Signin.SignIn.Completed", access_point,
                                      1);
  histogram_tester.ExpectUniqueSample("Signin.SigninManager.SigninAccessPoint",
                                      access_point, 1);
}

INSTANTIATE_TEST_SUITE_P(
    ,
    SigninManagerTest,
    ::testing::ConvertGenerator<SigninManagerTestParams::TupleType>(
        ::testing::Combine(::testing::Bool(), ::testing::Bool())),
    [](const ::testing::TestParamInfo<SigninManagerTestParams>& info) {
      std::string name = base::StrCat(
          {info.param.explicit_browser_signin ? "Explicit" : "Implicit", "And",
           info.param.is_signout_allowed ? "SignoutAllowed"
                                         : "SignoutRestricted"});
      return name;
    });

#if BUILDFLAG(ENABLE_DICE_SUPPORT)
class SigninManagerSupervisedUserTest : public SigninManagerTest {
 public:
  SigninManagerSupervisedUserTest() = default;
  ~SigninManagerSupervisedUserTest() override = default;

  void AddSupervisedAccount(ConsentLevel level) {
    AccountInfo account;
    if (level == ConsentLevel::kSignin) {
      account = MakeAccountAvailableWithCookies(kTestEmail);
    } else {
      account = MakeSyncAccountAvailableWithCookies(kTestEmail);
    }
    AccountCapabilitiesTestMutator mutator(&account.capabilities);
    mutator.set_is_subject_to_parental_controls(true);
    signin::UpdateAccountInfoForAccount(identity_manager(), account);
  }

 private:
  base::test::ScopedFeatureList feature_list_;
};

TEST_P(SigninManagerSupervisedUserTest, SignoutOnCookiesDeletedNotAllowed) {
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitWithFeatures({}, {kPreventSignoutIfAccountValid});
  AddSupervisedAccount(ConsentLevel::kSignin);
  ASSERT_TRUE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
  ASSERT_EQ(1U, observer().events().size());
  observer().Reset();

  // Remove the cookie, the account shouldn't be cleared when flag is disabled.
  identity_test_env()->SetCookieAccounts({});
  EXPECT_EQ(0U, observer().events().size());
  EXPECT_TRUE(identity_manager()->HasPrimaryAccount(ConsentLevel::kSignin));
}

INSTANTIATE_TEST_SUITE_P(,
                         SigninManagerSupervisedUserTest,
                         ::testing::Values(SigninManagerTestParams(
                             {/*explicit_browser_signin=*/false,
                              /*is_signout_allowed=*/true})));
#endif  // BUILDFLAG(ENABLE_DICE_SUPPORT)

=======
>>>>>>> chromium
}  // namespace signin
