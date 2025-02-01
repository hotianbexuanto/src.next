// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/signin/chrome_signin_client.h"
#include <memory>
#include <utility>

#include "base/bind.h"
#include "base/cxx17_backports.h"
#include "base/notreached.h"
#include "base/run_loop.h"
#include "build/build_config.h"
#include "build/chromeos_buildflags.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/signin/chrome_signin_client_factory.h"
#include "chrome/browser/signin/signin_util.h"
#include "chrome/common/pref_names.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
<<<<<<< HEAD
#include "chrome/test/base/testing_profile_manager.h"
#include "components/prefs/pref_service.h"
#include "components/signin/public/base/consent_level.h"
#include "components/signin/public/base/signin_metrics.h"
#include "components/signin/public/base/signin_pref_names.h"
#include "components/signin/public/identity_manager/account_info.h"
#include "components/signin/public/identity_manager/identity_manager.h"
#include "components/signin/public/identity_manager/identity_test_environment.h"
#include "google_apis/gaia/gaia_id.h"
=======
#include "content/public/browser/network_service_instance.h"
#include "content/public/test/browser_task_environment.h"
#include "services/network/test/test_network_connection_tracker.h"
>>>>>>> chromium
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

#if !defined(OS_ANDROID)
#include "chrome/test/base/browser_with_test_window_test.h"
#endif

// ChromeOS has its own network delay logic.
#if !BUILDFLAG(IS_CHROMEOS_ASH)

namespace {

class CallbackTester {
 public:
  CallbackTester() : called_(0) {}

  void Increment();
  void IncrementAndUnblock(base::RunLoop* run_loop);
  bool WasCalledExactlyOnce();

 private:
  int called_;
};

void CallbackTester::Increment() {
  called_++;
}

void CallbackTester::IncrementAndUnblock(base::RunLoop* run_loop) {
  Increment();
  run_loop->QuitWhenIdle();
}

bool CallbackTester::WasCalledExactlyOnce() {
  return called_ == 1;
}

}  // namespace

class ChromeSigninClientTest : public testing::Test {
 public:
  ChromeSigninClientTest() {
    // Create a signed-in profile.
    TestingProfile::Builder builder;
    profile_ = builder.Build();

    signin_client_ = ChromeSigninClientFactory::GetForProfile(profile());
  }

 protected:
  void SetUpNetworkConnection(bool respond_synchronously,
                              network::mojom::ConnectionType connection_type) {
    auto* tracker = network::TestNetworkConnectionTracker::GetInstance();
    tracker->SetRespondSynchronously(respond_synchronously);
    tracker->SetConnectionType(connection_type);
  }

  void SetConnectionType(network::mojom::ConnectionType connection_type) {
    network::TestNetworkConnectionTracker::GetInstance()->SetConnectionType(
        connection_type);
  }

  Profile* profile() { return profile_.get(); }
  SigninClient* signin_client() { return signin_client_; }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<Profile> profile_;
  SigninClient* signin_client_;
};

TEST_F(ChromeSigninClientTest, DelayNetworkCallRunsImmediatelyWithNetwork) {
  SetUpNetworkConnection(true, network::mojom::ConnectionType::CONNECTION_3G);
  CallbackTester tester;
  signin_client()->DelayNetworkCall(
      base::BindOnce(&CallbackTester::Increment, base::Unretained(&tester)));
  ASSERT_TRUE(tester.WasCalledExactlyOnce());
}

TEST_F(ChromeSigninClientTest, DelayNetworkCallRunsAfterGetConnectionType) {
  SetUpNetworkConnection(false, network::mojom::ConnectionType::CONNECTION_3G);

  base::RunLoop run_loop;
  CallbackTester tester;
  signin_client()->DelayNetworkCall(
      base::BindOnce(&CallbackTester::IncrementAndUnblock,
                     base::Unretained(&tester), &run_loop));
  ASSERT_FALSE(tester.WasCalledExactlyOnce());
  run_loop.Run();  // Wait for IncrementAndUnblock().
  ASSERT_TRUE(tester.WasCalledExactlyOnce());
}

TEST_F(ChromeSigninClientTest, DelayNetworkCallRunsAfterNetworkChange) {
  SetUpNetworkConnection(true, network::mojom::ConnectionType::CONNECTION_NONE);

  base::RunLoop run_loop;
  CallbackTester tester;
  signin_client()->DelayNetworkCall(
      base::BindOnce(&CallbackTester::IncrementAndUnblock,
                     base::Unretained(&tester), &run_loop));

  ASSERT_FALSE(tester.WasCalledExactlyOnce());
  SetConnectionType(network::mojom::ConnectionType::CONNECTION_3G);
  run_loop.Run();  // Wait for IncrementAndUnblock().
  ASSERT_TRUE(tester.WasCalledExactlyOnce());
}

#if !defined(OS_ANDROID)

class MockChromeSigninClient : public ChromeSigninClient {
 public:
  explicit MockChromeSigninClient(Profile* profile)
      : ChromeSigninClient(profile) {}

  MOCK_METHOD1(ShowUserManager, void(const base::FilePath&));
  MOCK_METHOD1(LockForceSigninProfile, void(const base::FilePath&));

  MOCK_METHOD3(SignOutCallback,
               void(signin_metrics::ProfileSignout,
                    signin_metrics::SignoutDelete,
                    SigninClient::SignoutDecision signout_decision));
};

class ChromeSigninClientSignoutTest : public BrowserWithTestWindowTest {
 public:
  ChromeSigninClientSignoutTest() : forced_signin_setter_(true) {}
  void SetUp() override {
    BrowserWithTestWindowTest::SetUp();
    CreateClient(browser()->profile());
  }

  void TearDown() override {
    BrowserWithTestWindowTest::TearDown();
    TestingBrowserProcess::GetGlobal()->SetLocalState(nullptr);
  }

  void CreateClient(Profile* profile) {
    client_ = std::make_unique<MockChromeSigninClient>(profile);
  }

  void PreSignOut(signin_metrics::ProfileSignout source_metric,
                  signin_metrics::SignoutDelete delete_metric) {
    client_->PreSignOut(base::BindOnce(&MockChromeSigninClient::SignOutCallback,
                                       base::Unretained(client_.get()),
                                       source_metric, delete_metric),
                        source_metric);
  }

  signin_util::ScopedForceSigninSetterForTesting forced_signin_setter_;
  std::unique_ptr<MockChromeSigninClient> client_;
};

TEST_F(ChromeSigninClientSignoutTest, SignOut) {
  signin_metrics::ProfileSignout source_metric =
      signin_metrics::ProfileSignout::USER_CLICKED_SIGNOUT_SETTINGS;
  signin_metrics::SignoutDelete delete_metric =
      signin_metrics::SignoutDelete::kIgnoreMetric;

  EXPECT_CALL(*client_, ShowUserManager(browser()->profile()->GetPath()))
      .Times(1);
  EXPECT_CALL(*client_, LockForceSigninProfile(browser()->profile()->GetPath()))
      .Times(1);
  EXPECT_CALL(
      *client_,
      SignOutCallback(source_metric, delete_metric,
                      SigninClient::SignoutDecision::ALLOW_SIGNOUT))
      .Times(1);

  PreSignOut(source_metric, delete_metric);
}

TEST_F(ChromeSigninClientSignoutTest, SignOutWithoutForceSignin) {
  signin_util::ScopedForceSigninSetterForTesting signin_setter(false);
  CreateClient(browser()->profile());

  signin_metrics::ProfileSignout source_metric =
      signin_metrics::ProfileSignout::USER_CLICKED_SIGNOUT_SETTINGS;
  signin_metrics::SignoutDelete delete_metric =
      signin_metrics::SignoutDelete::kIgnoreMetric;

  EXPECT_CALL(*client_, ShowUserManager(browser()->profile()->GetPath()))
      .Times(0);
  EXPECT_CALL(*client_, LockForceSigninProfile(browser()->profile()->GetPath()))
      .Times(0);
  EXPECT_CALL(
      *client_,
      SignOutCallback(source_metric, delete_metric,
                      SigninClient::SignoutDecision::ALLOW_SIGNOUT))
      .Times(1);
  PreSignOut(source_metric, delete_metric);
}

class ChromeSigninClientSignoutSourceTest
    : public ::testing::WithParamInterface<signin_metrics::ProfileSignout>,
      public ChromeSigninClientSignoutTest {};

// Returns true if signout can be disallowed by policy for the given source.
bool IsSignoutDisallowedByPolicy(
    signin_metrics::ProfileSignout signout_source) {
  switch (signout_source) {
    // NOTE: SIGNOUT_TEST == SIGNOUT_PREF_CHANGED.
    case signin_metrics::ProfileSignout::SIGNOUT_PREF_CHANGED:
    case signin_metrics::ProfileSignout::GOOGLE_SERVICE_NAME_PATTERN_CHANGED:
    case signin_metrics::ProfileSignout::SIGNIN_PREF_CHANGED_DURING_SIGNIN:
    case signin_metrics::ProfileSignout::USER_CLICKED_SIGNOUT_SETTINGS:
    case signin_metrics::ProfileSignout::SERVER_FORCED_DISABLE:
    case signin_metrics::ProfileSignout::TRANSFER_CREDENTIALS:
    case signin_metrics::ProfileSignout::
        AUTHENTICATION_FAILED_WITH_FORCE_SIGNIN:
    case signin_metrics::ProfileSignout::SIGNIN_NOT_ALLOWED_ON_PROFILE_INIT:
    case signin_metrics::ProfileSignout::USER_TUNED_OFF_SYNC_FROM_DICE_UI:
      return true;
    case signin_metrics::ProfileSignout::ACCOUNT_REMOVED_FROM_DEVICE:
      // TODO(msarda): Add more of the above cases to this "false" branch.
      // For now only ACCOUNT_REMOVED_FROM_DEVICE is here to preserve the status
      // quo. Additional internal sources of sign-out will be moved here in a
      // follow up CL.
      return false;
    case signin_metrics::ProfileSignout::ABORT_SIGNIN:
      // Allow signout because data has not been synced yet.
      return false;
    case signin_metrics::ProfileSignout::FORCE_SIGNOUT_ALWAYS_ALLOWED_FOR_TEST:
      // Allow signout for tests that want to force it.
      return false;
    case signin_metrics::ProfileSignout::ACCOUNT_ID_MIGRATION:
      // Allowed to force finish the account id migration.
      return false;
    case signin_metrics::ProfileSignout::USER_DELETED_ACCOUNT_COOKIES:
    case signin_metrics::ProfileSignout::MOBILE_IDENTITY_CONSISTENCY_ROLLBACK:
      // There's no special-casing for these in ChromeSigninClient, as they only
      // happen when there's no sync account and policies aren't enforced.
      // PrimaryAccountManager won't actually invoke PreSignOut in this case,
      // thus it is fine for ChromeSigninClient to not have any special-casing.
      return true;
    case signin_metrics::ProfileSignout::NUM_PROFILE_SIGNOUT_METRICS:
      NOTREACHED();
      return false;
  }
}

TEST_P(ChromeSigninClientSignoutSourceTest, UserSignoutAllowed) {
  signin_metrics::ProfileSignout signout_source = GetParam();

  TestingProfile::Builder builder;
  builder.SetGuestSession();
  std::unique_ptr<TestingProfile> profile = builder.Build();

  CreateClient(profile.get());
  ASSERT_TRUE(signin_util::IsUserSignoutAllowedForProfile(profile.get()));

  // Verify IdentityManager gets callback indicating sign-out is always allowed.
  signin_metrics::SignoutDelete delete_metric =
      signin_metrics::SignoutDelete::kIgnoreMetric;
  EXPECT_CALL(
      *client_,
      SignOutCallback(signout_source, delete_metric,
                      SigninClient::SignoutDecision::ALLOW_SIGNOUT))
      .Times(1);

  PreSignOut(signout_source, delete_metric);
}

#if defined(OS_WIN) || defined(OS_LINUX) || defined(OS_CHROMEOS) || \
    defined(OS_MAC)
TEST_P(ChromeSigninClientSignoutSourceTest, UserSignoutDisallowed) {
  signin_metrics::ProfileSignout signout_source = GetParam();

  TestingProfile::Builder builder;
  builder.SetGuestSession();
  std::unique_ptr<TestingProfile> profile = builder.Build();

  CreateClient(profile.get());

  ASSERT_TRUE(signin_util::IsUserSignoutAllowedForProfile(profile.get()));
  signin_util::SetUserSignoutAllowedForProfile(profile.get(), false);
  ASSERT_FALSE(signin_util::IsUserSignoutAllowedForProfile(profile.get()));

  // Verify IdentityManager gets callback indicating sign-out is disallowed iff
  // the source of the sign-out is a user-action.
  SigninClient::SignoutDecision signout_decision =
      IsSignoutDisallowedByPolicy(signout_source)
          ? SigninClient::SignoutDecision::DISALLOW_SIGNOUT
          : SigninClient::SignoutDecision::ALLOW_SIGNOUT;
  signin_metrics::SignoutDelete delete_metric =
      signin_metrics::SignoutDelete::kIgnoreMetric;
  EXPECT_CALL(*client_,
              SignOutCallback(signout_source, delete_metric, signout_decision))
      .Times(1);

  PreSignOut(signout_source, delete_metric);
}
#endif

const signin_metrics::ProfileSignout kSignoutSources[] = {
    signin_metrics::ProfileSignout::SIGNOUT_PREF_CHANGED,
    signin_metrics::ProfileSignout::GOOGLE_SERVICE_NAME_PATTERN_CHANGED,
    signin_metrics::ProfileSignout::SIGNIN_PREF_CHANGED_DURING_SIGNIN,
    signin_metrics::ProfileSignout::USER_CLICKED_SIGNOUT_SETTINGS,
    signin_metrics::ProfileSignout::ABORT_SIGNIN,
    signin_metrics::ProfileSignout::SERVER_FORCED_DISABLE,
    signin_metrics::ProfileSignout::TRANSFER_CREDENTIALS,
    signin_metrics::ProfileSignout::AUTHENTICATION_FAILED_WITH_FORCE_SIGNIN,
    signin_metrics::ProfileSignout::USER_TUNED_OFF_SYNC_FROM_DICE_UI,
    signin_metrics::ProfileSignout::ACCOUNT_REMOVED_FROM_DEVICE,
    signin_metrics::ProfileSignout::SIGNIN_NOT_ALLOWED_ON_PROFILE_INIT,
    signin_metrics::ProfileSignout::FORCE_SIGNOUT_ALWAYS_ALLOWED_FOR_TEST,
    signin_metrics::ProfileSignout::USER_DELETED_ACCOUNT_COOKIES,
    signin_metrics::ProfileSignout::MOBILE_IDENTITY_CONSISTENCY_ROLLBACK,
    signin_metrics::ProfileSignout::ACCOUNT_ID_MIGRATION,
};
static_assert(base::size(kSignoutSources) ==
                  signin_metrics::ProfileSignout::NUM_PROFILE_SIGNOUT_METRICS,
              "kSignoutSources should enumerate all ProfileSignout values");

INSTANTIATE_TEST_SUITE_P(AllSignoutSources,
                         ChromeSigninClientSignoutSourceTest,
                         testing::ValuesIn(kSignoutSources));

<<<<<<< HEAD
struct MetricsAccessPointHistogramNamesParam {
  signin_metrics::AccessPoint access_point;

  std::string extensions_signin_histogram_name;
  std::string extensions_sync_histogram_name;

  std::string all_bookmarks_signin_histogram_name;
  std::string bar_bookmarks_signin_histogram_name;
  std::string all_bookmarks_sync_histogram_name;
  std::string bar_bookmarks_sync_histogram_name;

  std::string suffix_test_name;
};

// Expected values for each access point group.
const MetricsAccessPointHistogramNamesParam params_per_access_point_group[] = {
    // Expecting 'PreUnoWebSignin'.
    {.access_point = signin_metrics::AccessPoint::kWebSignin,
     .extensions_signin_histogram_name =
         "Signin.Extensions.OnSignin.PreUnoWebSignin",
     .extensions_sync_histogram_name =
         "Signin.Extensions.OnSync.PreUnoWebSignin",
     .all_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.AllBookmarks.PreUnoWebSignin",
     .bar_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.BookmarksBar.PreUnoWebSignin",
     .all_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.AllBookmarks.PreUnoWebSignin",
     .bar_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.BookmarksBar.PreUnoWebSignin",
     .suffix_test_name = "AccessPointGroup_PreUnoWebSignin"},

    // Expecting 'UnoSigninBubble'.
    {.access_point = signin_metrics::AccessPoint::kChromeSigninInterceptBubble,
     .extensions_signin_histogram_name =
         "Signin.Extensions.OnSignin.UnoSigninBubble",
     .extensions_sync_histogram_name =
         "Signin.Extensions.OnSync.UnoSigninBubble",
     .all_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.AllBookmarks.UnoSigninBubble",
     .bar_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.BookmarksBar.UnoSigninBubble",
     .all_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.AllBookmarks.UnoSigninBubble",
     .bar_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.BookmarksBar.UnoSigninBubble",
     .suffix_test_name = "AccessPointGroup_UnoSigninBubble"},

    // Expecting 'ProfileCreation'.
    {.access_point = signin_metrics::AccessPoint::kUserManager,
     .extensions_signin_histogram_name =
         "Signin.Extensions.OnSignin.ProfileCreation",
     .extensions_sync_histogram_name =
         "Signin.Extensions.OnSync.ProfileCreation",
     .all_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.AllBookmarks.ProfileCreation",
     .bar_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.BookmarksBar.ProfileCreation",
     .all_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.AllBookmarks.ProfileCreation",
     .bar_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.BookmarksBar.ProfileCreation",
     .suffix_test_name = "AccessPointGroup_ProfileCreation"},

    // Expecting 'ProfileMenu'.
    {.access_point = signin_metrics::AccessPoint::kAvatarBubbleSignIn,
     .extensions_signin_histogram_name =
         "Signin.Extensions.OnSignin.ProfileMenu",
     .extensions_sync_histogram_name = "Signin.Extensions.OnSync.ProfileMenu",
     .all_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.AllBookmarks.ProfileMenu",
     .bar_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.BookmarksBar.ProfileMenu",
     .all_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.AllBookmarks.ProfileMenu",
     .bar_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.BookmarksBar.ProfileMenu",
     .suffix_test_name = "AccessPointGroup_ProfileMenu"},

    // Expecting 'Other'.
    {.access_point = signin_metrics::AccessPoint::kExtensions,
     .extensions_signin_histogram_name = "Signin.Extensions.OnSignin.Other",
     .extensions_sync_histogram_name = "Signin.Extensions.OnSync.Other",
     .all_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.AllBookmarks.Other",
     .bar_bookmarks_signin_histogram_name =
         "Signin.Bookmarks.OnSignin.BookmarksBar.Other",
     .all_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.AllBookmarks.Other",
     .bar_bookmarks_sync_histogram_name =
         "Signin.Bookmarks.OnSync.BookmarksBar.Other",
     .suffix_test_name = "AccessPointGroup_Other"},
};

// Helper to have a better parametrized test.
std::string ParamToTestSuffix(
    const ::testing::TestParamInfo<
        std::tuple<signin::ConsentLevel,
                   MetricsAccessPointHistogramNamesParam>>& info) {
  std::string consent_level_string =
      std::get<0>(info.param) == signin::ConsentLevel::kSignin ? "Signin"
                                                               : "Sync";
  return consent_level_string + "_" + std::get<1>(info.param).suffix_test_name;
}

class ChromeSigninClientMetricsTest
    : public ::testing::TestWithParam<
          std::tuple<signin::ConsentLevel,
                     MetricsAccessPointHistogramNamesParam>> {
 public:
  TestingProfile* profile() { return testing_profile_.get(); }

  const base::HistogramTester& histogram_tester() { return histogram_tester_; }

  // Checks both AllBookmarks and BookmarksBar histograms with no access point.
  void ExpectSigninExtensionsAndBookmarksHistogramValues(
      size_t expected_extensions_count,
      size_t expected_all_bookmark_count,
      size_t expected_bar_bookmarks_count,
      size_t signin_expected_bucket_count,
      size_t sync_expected_bucket_count) {
    // Extensions checks.
    histogram_tester_.ExpectUniqueSample("Signin.Extensions.OnSignin",
                                         expected_extensions_count,
                                         signin_expected_bucket_count);
    histogram_tester_.ExpectUniqueSample("Signin.Extensions.OnSync",
                                         expected_extensions_count,
                                         sync_expected_bucket_count);

    // Bookmarks checks.
    histogram_tester_.ExpectUniqueSample(
        "Signin.Bookmarks.OnSignin.AllBookmarks", expected_all_bookmark_count,
        signin_expected_bucket_count);
    histogram_tester_.ExpectUniqueSample(
        "Signin.Bookmarks.OnSignin.BookmarksBar", expected_bar_bookmarks_count,
        signin_expected_bucket_count);

    histogram_tester_.ExpectUniqueSample("Signin.Bookmarks.OnSync.AllBookmarks",
                                         expected_all_bookmark_count,
                                         sync_expected_bucket_count);
    histogram_tester_.ExpectUniqueSample("Signin.Bookmarks.OnSync.BookmarksBar",
                                         expected_bar_bookmarks_count,
                                         sync_expected_bucket_count);
  }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> testing_profile_ =
      TestingProfile::Builder().Build();
  base::HistogramTester histogram_tester_;
};

TEST_P(ChromeSigninClientMetricsTest, ExentsionsAndBookmarkCount) {
  MockChromeSigninClient client(profile());
  size_t all_bookmarks_count = 5;
  size_t bar_bookmarks_count = 3;
  size_t extensions_count = 4;

  EXPECT_CALL(client, GetAllBookmarksCount())
      .WillOnce(testing::Return(all_bookmarks_count));
  EXPECT_CALL(client, GetBookmarkBarBookmarksCount())
      .WillOnce(testing::Return(bar_bookmarks_count));
  EXPECT_CALL(client, GetExtensionsCount())
      .WillOnce(testing::Return(extensions_count));

  CoreAccountInfo account;
  account.email = "example@example.com";
  account.gaia = GaiaId("gaia_example");
  ASSERT_FALSE(account.IsEmpty());

  signin::ConsentLevel consent_level = std::get<0>(GetParam());
  signin::PrimaryAccountChangeEvent::State previous_state;
  // When testing for `kSync`, simulate a previous state with the same account
  // having `kSignin`.
  // A separate test is done for a direct change to `kSync`:
  // `BookmarkCountWithAccountInSyncDirectly`.
  if (consent_level == signin::ConsentLevel::kSync) {
    previous_state.primary_account = account;
    previous_state.consent_level = signin::ConsentLevel::kSignin;
  }
  MetricsAccessPointHistogramNamesParam test_params = std::get<1>(GetParam());
  signin::PrimaryAccountChangeEvent event_details{
      previous_state,
      /*current_state=*/
      signin::PrimaryAccountChangeEvent::State(account, consent_level),
      test_params.access_point};
  // Ensure the events types are correct for both consent levels.
  if (consent_level == signin::ConsentLevel::kSync) {
    ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSignin),
              signin::PrimaryAccountChangeEvent::Type::kNone);
    ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSync),
              signin::PrimaryAccountChangeEvent::Type::kSet);
  } else {
    ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSignin),
              signin::PrimaryAccountChangeEvent::Type::kSet);
    ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSync),
              signin::PrimaryAccountChangeEvent::Type::kNone);
  }

  // Simulate primary account changed.
  client.OnPrimaryAccountChanged(event_details);

  // Check for expected histograms values below.
  const size_t signin_expected_bucket_count =
      consent_level == signin::ConsentLevel::kSignin ? 1 : 0;
  const size_t sync_expected_bucket_count =
      consent_level == signin::ConsentLevel::kSync ? 1 : 0;

  // Checks histogram values without access point group names.
  ExpectSigninExtensionsAndBookmarksHistogramValues(
      extensions_count, all_bookmarks_count, bar_bookmarks_count,
      signin_expected_bucket_count, sync_expected_bucket_count);

  // For Extensions with access point group name.
  histogram_tester().ExpectUniqueSample(
      test_params.extensions_signin_histogram_name, extensions_count,
      signin_expected_bucket_count);
  histogram_tester().ExpectUniqueSample(
      test_params.extensions_sync_histogram_name, extensions_count,
      sync_expected_bucket_count);

  // For AllBookmarks with access point group name.
  histogram_tester().ExpectUniqueSample(
      test_params.all_bookmarks_signin_histogram_name, all_bookmarks_count,
      signin_expected_bucket_count);
  histogram_tester().ExpectUniqueSample(
      test_params.all_bookmarks_sync_histogram_name, all_bookmarks_count,
      sync_expected_bucket_count);

  // For BookmarksBar with access point group name.
  histogram_tester().ExpectUniqueSample(
      test_params.bar_bookmarks_signin_histogram_name, bar_bookmarks_count,
      signin_expected_bucket_count);
  histogram_tester().ExpectUniqueSample(
      test_params.bar_bookmarks_sync_histogram_name, bar_bookmarks_count,
      sync_expected_bucket_count);

  // The exact counts makes sure that no other histograms within this family
  // records unwanted values. For example not recording Sync histograms with a
  // Signin event and vice versa, or histogram for different access points than
  // the one being tested.
  // Exact sample counts histograms are done above.
  base::HistogramTester::CountsMap expected_bkmark_counts;
  base::HistogramTester::CountsMap expected_extensions_count;
  if (consent_level == signin::ConsentLevel::kSignin) {
    expected_extensions_count["Signin.Extensions.OnSignin"] = 1;
    expected_extensions_count[test_params.extensions_signin_histogram_name] = 1;
    expected_bkmark_counts["Signin.Bookmarks.OnSignin.AllBookmarks"] = 1;
    expected_bkmark_counts["Signin.Bookmarks.OnSignin.BookmarksBar"] = 1;
    expected_bkmark_counts[test_params.all_bookmarks_signin_histogram_name] = 1;
    expected_bkmark_counts[test_params.bar_bookmarks_signin_histogram_name] = 1;
  } else if (consent_level == signin::ConsentLevel::kSync) {
    expected_extensions_count["Signin.Extensions.OnSync"] = 1;
    expected_extensions_count[test_params.extensions_sync_histogram_name] = 1;
    expected_bkmark_counts["Signin.Bookmarks.OnSync.AllBookmarks"] = 1;
    expected_bkmark_counts["Signin.Bookmarks.OnSync.BookmarksBar"] = 1;
    expected_bkmark_counts[test_params.all_bookmarks_sync_histogram_name] = 1;
    expected_bkmark_counts[test_params.bar_bookmarks_sync_histogram_name] = 1;
  }
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Bookmarks."),
              testing::ContainerEq(expected_bkmark_counts));
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Extensions."),
              testing::ContainerEq(expected_extensions_count));
}

INSTANTIATE_TEST_SUITE_P(
    ,
    ChromeSigninClientMetricsTest,
    testing::Combine(testing::ValuesIn({signin::ConsentLevel::kSignin,
                                        signin::ConsentLevel::kSync}),
                     testing::ValuesIn(params_per_access_point_group)),
    &ParamToTestSuffix);

// In this test, the account changes is directly set to `kSync`, without a prior
// state where `kSignin` is set, this will trigger both changes for `kSignin`
// and `kSync`, only testing a single access point.
TEST_F(ChromeSigninClientMetricsTest,
       ExentsionsAndBookmarksCountWithAccountInSyncDirectly) {
  MockChromeSigninClient client(profile());
  size_t all_bookmarks_count = 7;
  size_t bar_bookmarks_count = 5;
  size_t extensions_count = 3;

  // `Times(2)` for both Signin then Sync.
  EXPECT_CALL(client, GetAllBookmarksCount())
      .Times(2)
      .WillRepeatedly(testing::Return(all_bookmarks_count));
  EXPECT_CALL(client, GetBookmarkBarBookmarksCount())
      .Times(2)
      .WillRepeatedly(testing::Return(bar_bookmarks_count));
  EXPECT_CALL(client, GetExtensionsCount())
      .Times(2)
      .WillRepeatedly(testing::Return(extensions_count));

  CoreAccountInfo account;
  account.email = "example@example.com";
  account.gaia = GaiaId("gaia_example");
  ASSERT_FALSE(account.IsEmpty());

  // State goes from no account to an account with `kSync` set.
  // It will trigger both events to `kSignin` and `kSync`.
  signin::PrimaryAccountChangeEvent event_details{
      /*previous_state=*/signin::PrimaryAccountChangeEvent::State(),
      /*current_state=*/
      signin::PrimaryAccountChangeEvent::State(account,
                                               signin::ConsentLevel::kSync),
      signin_metrics::AccessPoint::kWebSignin};
  // Both Signin and Sync event are being set.
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSignin),
            signin::PrimaryAccountChangeEvent::Type::kSet);
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSync),
            signin::PrimaryAccountChangeEvent::Type::kSet);

  // Simulate primary account changed.
  client.OnPrimaryAccountChanged(event_details);

  // Check for expected histograms values below.

  // Checks histogram values without access point group names.
  histogram_tester().ExpectUniqueSample("Signin.Extensions.OnSignin",
                                        extensions_count, 1);
  histogram_tester().ExpectUniqueSample("Signin.Extensions.OnSync",
                                        extensions_count, 1);
  histogram_tester().ExpectUniqueSample(
      "Signin.Bookmarks.OnSignin.AllBookmarks", all_bookmarks_count, 1);
  histogram_tester().ExpectUniqueSample("Signin.Bookmarks.OnSync.AllBookmarks",
                                        all_bookmarks_count, 1);
  histogram_tester().ExpectUniqueSample(
      "Signin.Bookmarks.OnSignin.BookmarksBar", bar_bookmarks_count, 1);
  histogram_tester().ExpectUniqueSample("Signin.Bookmarks.OnSync.BookmarksBar",
                                        bar_bookmarks_count, 1);

  // For Extensions with access point group name.
  histogram_tester().ExpectUniqueSample(
      "Signin.Extensions.OnSignin.PreUnoWebSignin", extensions_count, 1);
  histogram_tester().ExpectUniqueSample(
      "Signin.Extensions.OnSync.PreUnoWebSignin", extensions_count, 1);

  // For AllBookmarks with access point group name.
  histogram_tester().ExpectUniqueSample(
      "Signin.Bookmarks.OnSignin.AllBookmarks.PreUnoWebSignin",
      all_bookmarks_count, 1);
  histogram_tester().ExpectUniqueSample(
      "Signin.Bookmarks.OnSync.AllBookmarks.PreUnoWebSignin",
      all_bookmarks_count, 1);

  // For BookmarksBar with access point group name.
  histogram_tester().ExpectUniqueSample(
      "Signin.Bookmarks.OnSignin.BookmarksBar.PreUnoWebSignin",
      bar_bookmarks_count, 1);
  histogram_tester().ExpectUniqueSample(
      "Signin.Bookmarks.OnSync.BookmarksBar.PreUnoWebSignin",
      bar_bookmarks_count, 1);

  // Makes sure that no other unwanted histograms are recorded (Mainly for
  // other access point groups). Exact sample counts are checked above.
  base::HistogramTester::CountsMap expected_counts;
  expected_counts["Signin.Bookmarks.OnSignin.AllBookmarks"] = 1;
  expected_counts["Signin.Bookmarks.OnSignin.BookmarksBar"] = 1;
  expected_counts["Signin.Bookmarks.OnSync.AllBookmarks"] = 1;
  expected_counts["Signin.Bookmarks.OnSync.BookmarksBar"] = 1;
  expected_counts["Signin.Bookmarks.OnSignin.AllBookmarks.PreUnoWebSignin"] = 1;
  expected_counts["Signin.Bookmarks.OnSignin.BookmarksBar.PreUnoWebSignin"] = 1;
  expected_counts["Signin.Bookmarks.OnSync.AllBookmarks.PreUnoWebSignin"] = 1;
  expected_counts["Signin.Bookmarks.OnSync.BookmarksBar.PreUnoWebSignin"] = 1;
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Bookmarks."),
              testing::ContainerEq(expected_counts));

  // Makes sure that no other unwanted histograms are recorded (Mainly for
  // other access point groups). Exact sample counts are checked above.
  base::HistogramTester::CountsMap extensions_expected_counts;
  extensions_expected_counts["Signin.Extensions.OnSignin"] = 1;
  extensions_expected_counts["Signin.Extensions.OnSignin.PreUnoWebSignin"] = 1;
  extensions_expected_counts["Signin.Extensions.OnSync"] = 1;
  extensions_expected_counts["Signin.Extensions.OnSync.PreUnoWebSignin"] = 1;
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Extensions."),
              testing::ContainerEq(extensions_expected_counts));
}

// Not expecting any histogram to be recorded when no account update happens.
TEST_F(ChromeSigninClientMetricsTest,
       ExentsionsAndBookmarksCountWithAccountUpdate_kNone) {
  MockChromeSigninClient client(profile());

  EXPECT_CALL(client, GetAllBookmarksCount()).Times(0);
  EXPECT_CALL(client, GetBookmarkBarBookmarksCount()).Times(0);
  EXPECT_CALL(client, GetExtensionsCount()).Times(0);

  // Event details to simulate no update. Either empty or same value set.
  signin::PrimaryAccountChangeEvent event_details{
      /*previous_state=*/signin::PrimaryAccountChangeEvent::State(),
      /*current_state=*/signin::PrimaryAccountChangeEvent::State(),
      signin_metrics::AccessPoint::kWebSignin};
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSignin),
            signin::PrimaryAccountChangeEvent::Type::kNone);
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSync),
            signin::PrimaryAccountChangeEvent::Type::kNone);

  // Simulate primary account changed.
  client.OnPrimaryAccountChanged(event_details);

  // `expected_counts` is empty as we expect no histograms related to
  // `Signin.Bookmarks` or `Signin.Extensions to be recorded.
  base::HistogramTester::CountsMap expected_counts;
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Bookmarks."),
              testing::ContainerEq(expected_counts));
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Extensions."),
              testing::ContainerEq(expected_counts));
}

// Not expecting any histogram to be recorded when revoking account consent.
TEST_F(ChromeSigninClientMetricsTest,
       ExentsionsAndBookmarksCountWithAccountUpdate_kCleared) {
  MockChromeSigninClient client(profile());

  EXPECT_CALL(client, GetAllBookmarksCount()).Times(0);
  EXPECT_CALL(client, GetBookmarkBarBookmarksCount()).Times(0);
  EXPECT_CALL(client, GetExtensionsCount()).Times(0);

  CoreAccountInfo account;
  account.email = "example@example.com";
  account.gaia = GaiaId("gaia_example");
  ASSERT_FALSE(account.IsEmpty());

  // Simulating revoking Signin consent.
  signin::PrimaryAccountChangeEvent event_details{
      /*previous_state=*/signin::PrimaryAccountChangeEvent::State(
          account, signin::ConsentLevel::kSignin),
      /*current_state=*/signin::PrimaryAccountChangeEvent::State(),
      signin_metrics::ProfileSignout::kTest};
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSignin),
            signin::PrimaryAccountChangeEvent::Type::kCleared);
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSync),
            signin::PrimaryAccountChangeEvent::Type::kNone);

  // Simulate primary account changed.
  client.OnPrimaryAccountChanged(event_details);

  // `expected_counts` is empty as we expect no histograms related to
  // `Signin.Bookmarks` or `Signin.Extensions to be recorded.
  base::HistogramTester::CountsMap expected_counts;
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Bookmarks."),
              testing::ContainerEq(expected_counts));
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Extensions."),
              testing::ContainerEq(expected_counts));
}

// Not expecting any histogram to be recorded when the bookmark service is null.
TEST_F(ChromeSigninClientMetricsTest,
       ExentsionsAndBookmarksCountWithAccountSigningin_ServiceNull) {
  MockChromeSigninClient client(profile());

  // Returning `std::nullopt` to simulate the service being nullptr.
  EXPECT_CALL(client, GetAllBookmarksCount())
      .WillOnce(testing::Return(std::nullopt));
  EXPECT_CALL(client, GetBookmarkBarBookmarksCount())
      .WillOnce(testing::Return(std::nullopt));
  EXPECT_CALL(client, GetExtensionsCount())
      .WillOnce(testing::Return(std::nullopt));

  CoreAccountInfo account;
  account.email = "example@example.com";
  account.gaia = GaiaId("gaia_example");
  ASSERT_FALSE(account.IsEmpty());

  // Simulating signing in update.
  signin::PrimaryAccountChangeEvent event_details{
      /*previous_state=*/signin::PrimaryAccountChangeEvent::State(),
      /*current_state=*/
      signin::PrimaryAccountChangeEvent::State(account,
                                               signin::ConsentLevel::kSignin),
      signin_metrics::AccessPoint::kWebSignin};
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSignin),
            signin::PrimaryAccountChangeEvent::Type::kSet);
  ASSERT_EQ(event_details.GetEventTypeFor(signin::ConsentLevel::kSync),
            signin::PrimaryAccountChangeEvent::Type::kNone);

  // Simulate primary account changed.
  client.OnPrimaryAccountChanged(event_details);

  // `expected_counts` is empty as we expect no histograms related to
  // `Signin.Bookmarks` or `Signin.Extensions to be recorded.
  base::HistogramTester::CountsMap expected_counts;
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Bookmarks."),
              testing::ContainerEq(expected_counts));
  EXPECT_THAT(histogram_tester().GetTotalCountsForPrefix("Signin.Extensions."),
              testing::ContainerEq(expected_counts));
}

#endif  // !BUILDFLAG(IS_CHROMEOS_ASH) && !BUILDFLAG(IS_ANDROID)
=======
#endif  // !defined(OS_ANDROID)
#endif  // !BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
