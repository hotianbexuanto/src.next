// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "base/auto_reset.h"
#include "base/base_switches.h"
#include "base/bind.h"
#include "base/callback.h"
#include "base/callback_helpers.h"
#include "base/check.h"
#include "base/command_line.h"
#include "base/location.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/stringprintf.h"
#include "base/test/scoped_feature_list.h"
#include "base/test/test_mock_time_task_runner.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/time/time.h"
#include "build/build_config.h"
#include "chrome/browser/apps/platform_apps/shortcut_manager.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/extensions/api/identity/web_auth_flow.h"
#include "chrome/browser/policy/cloud/user_policy_signin_service.h"
#include "chrome/browser/policy/cloud/user_policy_signin_service_internal.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/signin/account_consistency_mode_manager.h"
#include "chrome/browser/signin/account_reconcilor_factory.h"
#include "chrome/browser/signin/chrome_device_id_helper.h"
#include "chrome/browser/signin/chrome_signin_client.h"
#include "chrome/browser/signin/chrome_signin_client_factory.h"
#include "chrome/browser/signin/chrome_signin_helper.h"
#include "chrome/browser/signin/dice_response_handler.h"
#include "chrome/browser/signin/identity_manager_factory.h"
#include "chrome/browser/signin/signin_util.h"
#include "chrome/browser/sync/user_event_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/profile_chooser_constants.h"
#include "chrome/browser/ui/simple_message_box_internal.h"
#include "chrome/browser/ui/webui/signin/login_ui_service.h"
#include "chrome/browser/ui/webui/signin/login_ui_service_factory.h"
#include "chrome/browser/ui/webui/signin/login_ui_test_utils.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/url_constants.h"
#include "chrome/common/webui_url_constants.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
<<<<<<< HEAD
#include "chrome/test/user_education/interactive_feature_promo_test.h"
#include "components/autofill/core/browser/data_manager/personal_data_manager.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/embedder_support/user_agent_utils.h"
#include "components/feature_engagement/public/feature_list.h"
=======
#include "components/policy/core/common/management/management_service.h"
#include "components/policy/core/common/management/scoped_management_service_override_for_testing.h"
>>>>>>> chromium
#include "components/prefs/pref_service.h"
#include "components/search/ntp_features.h"
#include "components/signin/core/browser/account_reconcilor.h"
#include "components/signin/core/browser/dice_header_helper.h"
#include "components/signin/core/browser/signin_header_helper.h"
#include "components/signin/public/base/account_consistency_method.h"
#include "components/signin/public/base/signin_client.h"
#include "components/signin/public/base/signin_metrics.h"
#include "components/signin/public/base/signin_pref_names.h"
#include "components/signin/public/identity_manager/identity_manager.h"
#include "components/signin/public/identity_manager/identity_test_utils.h"
#include "components/signin/public/identity_manager/primary_account_mutator.h"
<<<<<<< HEAD
#include "components/signin/public/identity_manager/signin_constants.h"
#include "components/sync/base/features.h"
#include "components/sync/base/user_selectable_type.h"
#include "components/sync/service/sync_prefs.h"
#include "components/sync/service/sync_service.h"
#include "components/sync/service/sync_user_settings.h"
=======
#include "components/sync/base/sync_prefs.h"
>>>>>>> chromium
#include "components/sync_user_events/user_event_service.h"
#include "components/variations/variations_switches.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/load_notification_details.h"
#include "content/public/browser/notification_service.h"
#include "content/public/browser/notification_types.h"
#include "content/public/common/content_switches.h"
#include "content/public/test/browser_test.h"
<<<<<<< HEAD
#include "content/public/test/browser_test_utils.h"
#include "content/public/test/test_launcher.h"
#include "content/public/test/test_navigation_observer.h"
#include "google_apis/gaia/gaia_constants.h"
#include "google_apis/gaia/gaia_id.h"
=======
>>>>>>> chromium
#include "google_apis/gaia/gaia_switches.h"
#include "google_apis/gaia/gaia_urls.h"
#include "net/test/embedded_test_server/embedded_test_server.h"
#include "net/test/embedded_test_server/http_request.h"
#include "net/test/embedded_test_server/http_response.h"
#include "net/test/embedded_test_server/request_handler_util.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using net::test_server::BasicHttpResponse;
using net::test_server::HttpRequest;
using net::test_server::HttpResponse;
using signin::AccountConsistencyMethod;
using signin::constants::kNoHostedDomainFound;

namespace {

constexpr int kAccountReconcilorDelayMs = 10;

enum SignoutType {
  kSignoutTypeFirst = 0,

  kAllAccounts = 0,       // Sign out from all accounts.
  kMainAccount = 1,       // Sign out from main account only.
  kSecondaryAccount = 2,  // Sign out from secondary account only.

  kSignoutTypeLast
};

const char kAuthorizationCode[] = "authorization_code";
const char kDiceResponseHeader[] = "X-Chrome-ID-Consistency-Response";
const char kChromeSyncEndpointURL[] = "/signin/chrome/sync";
const char kEnableSyncURL[] = "/enable_sync";
const char kGoogleSignoutResponseHeader[] = "Google-Accounts-SignOut";
const char kMainGmailEmail[] = "main_email@gmail.com";
const char kMainManagedEmail[] = "main_email@managed.com";
const char kNoDiceRequestHeader[] = "NoDiceHeader";
const char kOAuth2TokenExchangeURL[] = "/oauth2/v4/token";
const char kOAuth2TokenRevokeURL[] = "/o/oauth2/revoke";
const char kSecondaryEmail[] = "secondary_email@example.com";
const char kSigninURL[] = "/signin";
const char kSigninWithOutageInDiceURL[] = "/signin/outage";
const char kSignoutURL[] = "/signout";

// Test response that does not complete synchronously. It must be unblocked by
// calling the completion closure.
class BlockedHttpResponse : public net::test_server::BasicHttpResponse {
 public:
  explicit BlockedHttpResponse(
      base::OnceCallback<void(base::OnceClosure)> callback)
      : callback_(std::move(callback)) {}

  void SendResponse(const net::test_server::SendBytesCallback& send,
                    net::test_server::SendCompleteCallback done) override {
    // Called on the IO thread to unblock the response.
    base::OnceClosure unblock_io_thread =
        base::BindOnce(send, ToResponseString(), std::move(done));
    // Unblock the response from any thread by posting a task to the IO thread.
    base::OnceClosure unblock_any_thread =
        base::BindOnce(base::IgnoreResult(&base::TaskRunner::PostTask),
                       base::ThreadTaskRunnerHandle::Get(), FROM_HERE,
                       std::move(unblock_io_thread));
    // Pass |unblock_any_thread| to the caller on the UI thread.
    content::GetUIThreadTaskRunner({})->PostTask(
        FROM_HERE,
        base::BindOnce(std::move(callback_), std::move(unblock_any_thread)));
  }

 private:
  base::OnceCallback<void(base::OnceClosure)> callback_;
};

}  // namespace

namespace FakeGaia {

// Handler for the signin page on the embedded test server.
// The response has the content of the Dice request header in its body, and has
// the Dice response header.
// Handles both the "Chrome Sync" endpoint and the old endpoint.
std::unique_ptr<HttpResponse> HandleSigninURL(
    const std::string& main_email,
    const base::RepeatingCallback<void(const std::string&)>& callback,
    const HttpRequest& request) {
  if (!net::test_server::ShouldHandle(request, kSigninURL) &&
      !net::test_server::ShouldHandle(request, kChromeSyncEndpointURL) &&
      !net::test_server::ShouldHandle(request, kSigninWithOutageInDiceURL))
    return nullptr;

  // Extract Dice request header.
  std::string header_value = kNoDiceRequestHeader;
  auto it = request.headers.find(signin::kDiceRequestHeader);
  if (it != request.headers.end())
    header_value = it->second;

  content::GetUIThreadTaskRunner({})->PostTask(
      FROM_HERE, base::BindOnce(callback, header_value));

  // Add the SIGNIN dice header.
  std::unique_ptr<BasicHttpResponse> http_response(new BasicHttpResponse);
  if (header_value != kNoDiceRequestHeader) {
    if (net::test_server::ShouldHandle(request, kSigninWithOutageInDiceURL)) {
      http_response->AddCustomHeader(
          kDiceResponseHeader,
          base::StringPrintf(
              "action=SIGNIN,authuser=1,id=%s,email=%s,"
              "no_authorization_code=true",
              signin::GetTestGaiaIdForEmail(main_email).ToString().c_str(),
              main_email.c_str()));
    } else {
      http_response->AddCustomHeader(
          kDiceResponseHeader,
          base::StringPrintf(
<<<<<<< HEAD
              "action=SIGNIN,authuser=1,id=%s,email=%s,authorization_code=%s,"
              "eligible_for_token_binding=ES256 RS256",
              signin::GetTestGaiaIdForEmail(main_email).ToString().c_str(),
=======
              "action=SIGNIN,authuser=1,id=%s,email=%s,authorization_code=%s",
              signin::GetTestGaiaIdForEmail(main_email).c_str(),
>>>>>>> chromium
              main_email.c_str(), kAuthorizationCode));
    }
  }

  // When hitting the Chrome Sync endpoint, redirect to kEnableSyncURL, which
  // adds the ENABLE_SYNC dice header.
  if (net::test_server::ShouldHandle(request, kChromeSyncEndpointURL)) {
    http_response->set_code(net::HTTP_FOUND);  // 302 redirect.
    http_response->AddCustomHeader("location", kEnableSyncURL);
  }

  http_response->AddCustomHeader("Cache-Control", "no-store");
  return std::move(http_response);
}

// Handler for the Gaia endpoint adding the ENABLE_SYNC dice header.
std::unique_ptr<HttpResponse> HandleEnableSyncURL(
    const std::string& main_email,
    const base::RepeatingCallback<void(base::OnceClosure)>& callback,
    const HttpRequest& request) {
  if (!net::test_server::ShouldHandle(request, kEnableSyncURL))
    return nullptr;

  std::unique_ptr<BlockedHttpResponse> http_response =
      std::make_unique<BlockedHttpResponse>(callback);
  http_response->AddCustomHeader(
      kDiceResponseHeader,
      base::StringPrintf(
          "action=ENABLE_SYNC,authuser=1,id=%s,email=%s",
          signin::GetTestGaiaIdForEmail(main_email).ToString().c_str(),
          main_email.c_str()));
  http_response->AddCustomHeader("Cache-Control", "no-store");
  return std::move(http_response);
}

// Handler for the signout page on the embedded test server.
// Responds with a Google-Accounts-SignOut header for the main account, the
// secondary account, or both (depending on the SignoutType, which is encoded in
// the query string).
std::unique_ptr<HttpResponse> HandleSignoutURL(const std::string& main_email,
                                               const HttpRequest& request) {
  if (!net::test_server::ShouldHandle(request, kSignoutURL))
    return nullptr;

  // Build signout header.
  int query_value;
  EXPECT_TRUE(base::StringToInt(request.GetURL().query(), &query_value));
  SignoutType signout_type = static_cast<SignoutType>(query_value);
  EXPECT_GE(signout_type, kSignoutTypeFirst);
  EXPECT_LT(signout_type, kSignoutTypeLast);
  std::string signout_header_value;
  if (signout_type == kAllAccounts || signout_type == kMainAccount) {
    GaiaId main_gaia_id = signin::GetTestGaiaIdForEmail(main_email);
    signout_header_value =
        base::StringPrintf("email=\"%s\", obfuscatedid=\"%s\", sessionindex=1",
                           main_email.c_str(), main_gaia_id.ToString().c_str());
  }
  if (signout_type == kAllAccounts || signout_type == kSecondaryAccount) {
    if (!signout_header_value.empty())
      signout_header_value += ", ";
<<<<<<< HEAD
    }
    GaiaId secondary_gaia_id = signin::GetTestGaiaIdForEmail(kSecondaryEmail);
    signout_header_value += base::StringPrintf(
        "email=\"%s\", obfuscatedid=\"%s\", sessionindex=2", kSecondaryEmail,
        secondary_gaia_id.ToString().c_str());
=======
    std::string secondary_gaia_id =
        signin::GetTestGaiaIdForEmail(kSecondaryEmail);
    signout_header_value +=
        base::StringPrintf("email=\"%s\", obfuscatedid=\"%s\", sessionindex=2",
                           kSecondaryEmail, secondary_gaia_id.c_str());
>>>>>>> chromium
  }

  std::unique_ptr<BasicHttpResponse> http_response(new BasicHttpResponse);
  http_response->AddCustomHeader(kGoogleSignoutResponseHeader,
                                 signout_header_value);
  http_response->AddCustomHeader("Cache-Control", "no-store");
  return std::move(http_response);
}

// Handler for OAuth2 token exchange.
// Checks that the request is well formatted and returns a refresh token in a
// JSON dictionary.
std::unique_ptr<HttpResponse> HandleOAuth2TokenExchangeURL(
    const base::RepeatingCallback<void(base::OnceClosure)>& callback,
    const HttpRequest& request) {
  if (!net::test_server::ShouldHandle(request, kOAuth2TokenExchangeURL))
    return nullptr;

  // Check that the authorization code is somewhere in the request body.
  if (!request.has_content)
    return nullptr;
  if (request.content.find(kAuthorizationCode) == std::string::npos)
    return nullptr;

  std::unique_ptr<BlockedHttpResponse> http_response =
      std::make_unique<BlockedHttpResponse>(callback);

  std::string content =
      "{"
      "  \"access_token\":\"access_token\","
      "  \"refresh_token\":\"new_refresh_token\","
      "  \"expires_in\":9999"
      "}";

  http_response->set_content(content);
  http_response->set_content_type("text/plain");
  http_response->AddCustomHeader("Cache-Control", "no-store");
  return std::move(http_response);
}

// Handler for OAuth2 token revocation.
std::unique_ptr<HttpResponse> HandleOAuth2TokenRevokeURL(
    const base::RepeatingClosure& callback,
    const HttpRequest& request) {
  if (!net::test_server::ShouldHandle(request, kOAuth2TokenRevokeURL))
    return nullptr;

  content::GetUIThreadTaskRunner({})->PostTask(FROM_HERE, callback);

  std::unique_ptr<BasicHttpResponse> http_response(new BasicHttpResponse);
  http_response->AddCustomHeader("Cache-Control", "no-store");
  return std::move(http_response);
}

// Handler for ServiceLogin on the embedded test server.
// Calls the callback with the dice request header, or kNoDiceRequestHeader if
// there is no Dice header.
std::unique_ptr<HttpResponse> HandleChromeSigninEmbeddedURL(
    const base::RepeatingCallback<void(const std::string&)>& callback,
    const HttpRequest& request) {
  if (!net::test_server::ShouldHandle(request,
                                      "/embedded/setup/chrome/usermenu"))
    return nullptr;

  std::string dice_request_header(kNoDiceRequestHeader);
  auto it = request.headers.find(signin::kDiceRequestHeader);
  if (it != request.headers.end())
    dice_request_header = it->second;
  content::GetUIThreadTaskRunner({})->PostTask(
      FROM_HERE, base::BindOnce(callback, dice_request_header));

  std::unique_ptr<BasicHttpResponse> http_response(new BasicHttpResponse);
  http_response->AddCustomHeader("Cache-Control", "no-store");
  return std::move(http_response);
}

}  // namespace FakeGaia

class DiceBrowserTest : public InProcessBrowserTest,
                        public AccountReconcilor::Observer,
                        public signin::IdentityManager::Observer {
 protected:
  ~DiceBrowserTest() override = default;

  explicit DiceBrowserTest(const std::string& main_email = kMainGmailEmail)
      : main_email_(main_email),
        https_server_(net::EmbeddedTestServer::TYPE_HTTPS),
        enable_sync_requested_(false),
        token_requested_(false),
        refresh_token_available_(false),
        token_revoked_notification_count_(0),
        token_revoked_count_(0),
        reconcilor_blocked_count_(0),
        reconcilor_unblocked_count_(0),
        reconcilor_started_count_(0) {
    feature_list_.InitAndEnableFeature(kSupportOAuthOutageInDice);
    https_server_.RegisterDefaultHandler(base::BindRepeating(
        &FakeGaia::HandleSigninURL, main_email_,
        base::BindRepeating(&DiceBrowserTest::OnSigninRequest,
                            base::Unretained(this))));
    https_server_.RegisterDefaultHandler(base::BindRepeating(
        &FakeGaia::HandleEnableSyncURL, main_email_,
        base::BindRepeating(&DiceBrowserTest::OnEnableSyncRequest,
                            base::Unretained(this))));
    https_server_.RegisterDefaultHandler(
        base::BindRepeating(&FakeGaia::HandleSignoutURL, main_email_));
    https_server_.RegisterDefaultHandler(base::BindRepeating(
        &FakeGaia::HandleOAuth2TokenExchangeURL,
        base::BindRepeating(&DiceBrowserTest::OnTokenExchangeRequest,
                            base::Unretained(this))));
    https_server_.RegisterDefaultHandler(base::BindRepeating(
        &FakeGaia::HandleOAuth2TokenRevokeURL,
        base::BindRepeating(&DiceBrowserTest::OnTokenRevocationRequest,
                            base::Unretained(this))));
    https_server_.RegisterDefaultHandler(base::BindRepeating(
        &FakeGaia::HandleChromeSigninEmbeddedURL,
        base::BindRepeating(&DiceBrowserTest::OnChromeSigninEmbeddedRequest,
                            base::Unretained(this))));
    signin::SetDiceAccountReconcilorBlockDelayForTesting(
        kAccountReconcilorDelayMs);
  }

  // Navigates to the given path on the test server.
  void NavigateToURL(const std::string& path) {
    ui_test_utils::NavigateToURL(browser(), https_server_.GetURL(path));
  }

  // Returns the identity manager.
  signin::IdentityManager* GetIdentityManager() {
    return IdentityManagerFactory::GetForProfile(browser()->profile());
  }

  // Returns the account ID associated with |main_email_| and its associated
  // gaia ID.
  CoreAccountId GetMainAccountID() {
    return GetIdentityManager()->PickAccountIdForAccount(
        signin::GetTestGaiaIdForEmail(main_email_), main_email_);
  }

  // Returns the account ID associated with kSecondaryEmail and its associated
  // gaia ID.
  CoreAccountId GetSecondaryAccountID() {
    return GetIdentityManager()->PickAccountIdForAccount(
        signin::GetTestGaiaIdForEmail(kSecondaryEmail), kSecondaryEmail);
  }

  std::string GetDeviceId() {
    return GetSigninScopedDeviceIdForProfile(browser()->profile());
  }

  // Signin with a main account and add token for a secondary account.
  void SetupSignedInAccounts() {
    // Signin main account.
    AccountInfo primary_account_info = signin::MakePrimaryAccountAvailable(
        GetIdentityManager(), main_email_, signin::ConsentLevel::kSync);
    ASSERT_TRUE(
        GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
    ASSERT_FALSE(
        GetIdentityManager()->HasAccountWithRefreshTokenInPersistentErrorState(
            GetMainAccountID()));
    ASSERT_EQ(GetMainAccountID(), GetIdentityManager()->GetPrimaryAccountId(
                                      signin::ConsentLevel::kSync));

    // Add a token for a secondary account.
    AccountInfo secondary_account_info =
        signin::MakeAccountAvailable(GetIdentityManager(), kSecondaryEmail);
    ASSERT_TRUE(GetIdentityManager()->HasAccountWithRefreshToken(
        secondary_account_info.account_id));
    ASSERT_FALSE(
        GetIdentityManager()->HasAccountWithRefreshTokenInPersistentErrorState(
            secondary_account_info.account_id));
  }

  // Navigate to a Gaia URL setting the Google-Accounts-SignOut header.
  void SignOutWithDice(SignoutType signout_type) {
    NavigateToURL(base::StringPrintf("%s?%i", kSignoutURL, signout_type));
    EXPECT_EQ(1, reconcilor_blocked_count_);
    WaitForReconcilorUnblockedCount(1);

    base::RunLoop().RunUntilIdle();
  }

  // InProcessBrowserTest:
  void SetUp() override {
    ASSERT_TRUE(https_server_.InitializeAndListen());
    InProcessBrowserTest::SetUp();
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    const GURL& base_url = https_server_.base_url();
    command_line->AppendSwitchASCII(switches::kGaiaUrl, base_url.spec());
    command_line->AppendSwitchASCII(switches::kGoogleApisUrl, base_url.spec());
    command_line->AppendSwitchASCII(switches::kLsoUrl, base_url.spec());
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    https_server_.StartAcceptingConnections();

    GetIdentityManager()->AddObserver(this);
    // Wait for the token service to be ready.
    if (!GetIdentityManager()->AreRefreshTokensLoaded()) {
      WaitForClosure(&tokens_loaded_quit_closure_);
    }
    ASSERT_TRUE(GetIdentityManager()->AreRefreshTokensLoaded());

    AccountReconcilor* reconcilor =
        AccountReconcilorFactory::GetForProfile(browser()->profile());

    // Reconcilor starts as soon as the token service finishes loading its
    // credentials. Abort the reconcilor here to make sure tests start in a
    // stable state.
    reconcilor->AbortReconcile();
    reconcilor->SetState(
        signin_metrics::AccountReconcilorState::ACCOUNT_RECONCILOR_OK);
    reconcilor->AddObserver(this);
  }

  void TearDownOnMainThread() override {
    GetIdentityManager()->RemoveObserver(this);
    AccountReconcilorFactory::GetForProfile(browser()->profile())
        ->RemoveObserver(this);
  }

  // Calls |closure| if it is not null and resets it after.
  void RunClosureIfValid(base::OnceClosure closure) {
    if (closure)
      std::move(closure).Run();
  }

  // Creates and runs a RunLoop until |closure| is called.
  void WaitForClosure(base::OnceClosure* closure) {
    base::RunLoop run_loop;
    *closure = run_loop.QuitClosure();
    run_loop.Run();
  }

  // FakeGaia callbacks:
  void OnSigninRequest(const std::string& dice_request_header) {
    EXPECT_EQ(dice_request_header != kNoDiceRequestHeader,
              IsReconcilorBlocked());
    dice_request_header_ = dice_request_header;
    RunClosureIfValid(std::move(signin_requested_quit_closure_));
  }

  void OnChromeSigninEmbeddedRequest(const std::string& dice_request_header) {
    dice_request_header_ = dice_request_header;
    RunClosureIfValid(std::move(chrome_signin_embedded_quit_closure_));
  }

  void OnEnableSyncRequest(base::OnceClosure unblock_response_closure) {
    EXPECT_TRUE(IsReconcilorBlocked());
    enable_sync_requested_ = true;
    RunClosureIfValid(std::move(enable_sync_requested_quit_closure_));
    unblock_enable_sync_response_closure_ = std::move(unblock_response_closure);
  }

  void OnTokenExchangeRequest(base::OnceClosure unblock_response_closure) {
    // The token must be exchanged only once.
    EXPECT_FALSE(token_requested_);
    EXPECT_TRUE(IsReconcilorBlocked());
    token_requested_ = true;
    RunClosureIfValid(std::move(token_requested_quit_closure_));
    unblock_token_exchange_response_closure_ =
        std::move(unblock_response_closure);
  }

  void OnTokenRevocationRequest() {
    ++token_revoked_count_;
    RunClosureIfValid(std::move(token_revoked_quit_closure_));
  }

  // AccountReconcilor::Observer:
  void OnBlockReconcile() override { ++reconcilor_blocked_count_; }
  void OnUnblockReconcile() override {
    ++reconcilor_unblocked_count_;
    RunClosureIfValid(std::move(unblock_count_quit_closure_));
  }
  void OnStateChanged(signin_metrics::AccountReconcilorState state) override {
    if (state ==
        signin_metrics::AccountReconcilorState::ACCOUNT_RECONCILOR_RUNNING) {
      ++reconcilor_started_count_;
    }
  }

  // signin::IdentityManager::Observer
  void OnPrimaryAccountChanged(
      const signin::PrimaryAccountChangeEvent& event) override {
    if (event.GetEventTypeFor(signin::ConsentLevel::kSync) ==
        signin::PrimaryAccountChangeEvent::Type::kSet) {
      RunClosureIfValid(std::move(on_primary_account_set_quit_closure_));
    }
  }

  void OnRefreshTokenUpdatedForAccount(
      const CoreAccountInfo& account_info) override {
    if (account_info.account_id == GetMainAccountID()) {
      refresh_token_available_ = true;
      RunClosureIfValid(std::move(refresh_token_available_quit_closure_));
    }
  }

  void OnRefreshTokenRemovedForAccount(
      const CoreAccountId& account_id) override {
    ++token_revoked_notification_count_;
  }

  void OnRefreshTokensLoaded() override {
    RunClosureIfValid(std::move(tokens_loaded_quit_closure_));
  }

  // Returns true if the account reconcilor is currently blocked.
  bool IsReconcilorBlocked() {
    EXPECT_GE(reconcilor_blocked_count_, reconcilor_unblocked_count_);
    EXPECT_LE(reconcilor_blocked_count_, reconcilor_unblocked_count_ + 1);
    return (reconcilor_unblocked_count_ + 1) == reconcilor_blocked_count_;
  }

  // Waits until |reconcilor_unblocked_count_| reaches |count|.
  void WaitForReconcilorUnblockedCount(int count) {
    if (reconcilor_unblocked_count_ == count)
      return;

    ASSERT_EQ(count - 1, reconcilor_unblocked_count_);
    // Wait for the timeout after the request is complete.
    WaitForClosure(&unblock_count_quit_closure_);
    EXPECT_EQ(count, reconcilor_unblocked_count_);
  }

  // Waits until the user consented for sync.
  void WaitForSigninSucceeded() {
    if (GetIdentityManager()
            ->GetPrimaryAccountId(signin::ConsentLevel::kSync)
            .empty()) {
      WaitForClosure(&on_primary_account_set_quit_closure_);
    }
  }

  // Waits for the ENABLE_SYNC request to hit the server, and unblocks the
  // response. If this is not called, ENABLE_SYNC will not be sent by the
  // server.
  // Note: this does not wait for the response to reach Chrome.
  void SendEnableSyncResponse() {
    if (!enable_sync_requested_)
      WaitForClosure(&enable_sync_requested_quit_closure_);
    DCHECK(unblock_enable_sync_response_closure_);
    std::move(unblock_enable_sync_response_closure_).Run();
  }

  // Waits until the token request is sent to the server, the response is
  // received and the refresh token is available. If this is not called, the
  // refresh token will not be sent by the server.
  void SendRefreshTokenResponse() {
    // Wait for the request hitting the server.
    if (!token_requested_)
      WaitForClosure(&token_requested_quit_closure_);
    EXPECT_TRUE(token_requested_);
    // Unblock the server response.
    DCHECK(unblock_token_exchange_response_closure_);
    std::move(unblock_token_exchange_response_closure_).Run();
    // Wait for the response coming back.
    if (!refresh_token_available_)
      WaitForClosure(&refresh_token_available_quit_closure_);
    EXPECT_TRUE(refresh_token_available_);
  }

  void WaitForTokenRevokedCount(int count) {
    EXPECT_LE(token_revoked_count_, count);
    while (token_revoked_count_ < count)
      WaitForClosure(&token_revoked_quit_closure_);
    EXPECT_EQ(count, token_revoked_count_);
  }

  DiceResponseHandler* GetDiceResponseHandler() {
    return DiceResponseHandler::GetForProfile(browser()->profile());
  }

  const std::string main_email_;
  net::EmbeddedTestServer https_server_;
  bool enable_sync_requested_;
  bool token_requested_;
  bool refresh_token_available_;
  int token_revoked_notification_count_;
  int token_revoked_count_;
  int reconcilor_blocked_count_;
  int reconcilor_unblocked_count_;
  int reconcilor_started_count_;
  std::string dice_request_header_;
  base::test::ScopedFeatureList feature_list_;

  // Unblocks the server responses.
  base::OnceClosure unblock_token_exchange_response_closure_;
  base::OnceClosure unblock_enable_sync_response_closure_;

  // Used for waiting asynchronous events.
  base::OnceClosure enable_sync_requested_quit_closure_;
  base::OnceClosure token_requested_quit_closure_;
  base::OnceClosure token_revoked_quit_closure_;
  base::OnceClosure refresh_token_available_quit_closure_;
  base::OnceClosure chrome_signin_embedded_quit_closure_;
  base::OnceClosure unblock_count_quit_closure_;
  base::OnceClosure tokens_loaded_quit_closure_;
  base::OnceClosure on_primary_account_set_quit_closure_;
  base::OnceClosure signin_requested_quit_closure_;

  // The sync service and waits for policies to load before starting for
  // enterprise users, managed devices and browsers. This means that services
  // depending on it might have to wait too. By setting the management
  // authorities to none by default, we assume that the default test is on an
  // unmanaged device and browser thus we avoid unnecessarily waiting for
  // policies to load. Tests expecting either an enterprise user, a managed
  // device or browser should add the appropriate management authorities.
  policy::ScopedManagementServiceOverrideForTesting browser_management_ =
      policy::ScopedManagementServiceOverrideForTesting(
          policy::ManagementTarget::BROWSER,
          base::flat_set<policy::EnterpriseManagementAuthority>());
  policy::ScopedManagementServiceOverrideForTesting platform_management_ =
      policy::ScopedManagementServiceOverrideForTesting(
          policy::ManagementTarget::PLATFORM,
          base::flat_set<policy::EnterpriseManagementAuthority>());

  DISALLOW_COPY_AND_ASSIGN(DiceBrowserTest);
};

// Checks that signin on Gaia triggers the fetch for a refresh token.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, Signin) {
  EXPECT_EQ(0, reconcilor_started_count_);

  // Navigate to Gaia and sign in.
  NavigateToURL(kSigninURL);

  // Check that the Dice request header was sent.
  std::string client_id = GaiaUrls::GetInstance()->oauth2_chrome_client_id();
  EXPECT_EQ(base::StringPrintf("version=%s,client_id=%s,device_id=%s,"
                               "signin_mode=all_accounts,"
                               "signout_mode=show_confirmation",
                               signin::kDiceProtocolVersion, client_id.c_str(),
                               GetDeviceId().c_str()),
            dice_request_header_);

  // Check that the token was requested and added to the token service.
  SendRefreshTokenResponse();
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  // Sync should not be enabled.
  EXPECT_TRUE(GetIdentityManager()
                  ->GetPrimaryAccountId(signin::ConsentLevel::kSync)
                  .empty());

  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
  EXPECT_EQ(1, reconcilor_started_count_);
}

// Checks that the account reconcilor is blocked when where was OAuth
// outage in Dice, and unblocked after the timeout.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, SupportOAuthOutageInDice) {
  DiceResponseHandler* dice_response_handler = GetDiceResponseHandler();
  scoped_refptr<base::TestMockTimeTaskRunner> task_runner =
      new base::TestMockTimeTaskRunner();
  dice_response_handler->SetTaskRunner(task_runner);
  NavigateToURL(kSigninWithOutageInDiceURL);
  // Check that the Dice request header was sent.
  std::string client_id = GaiaUrls::GetInstance()->oauth2_chrome_client_id();
  EXPECT_EQ(base::StringPrintf("version=%s,client_id=%s,device_id=%s,"
                               "signin_mode=all_accounts,"
                               "signout_mode=show_confirmation",
                               signin::kDiceProtocolVersion, client_id.c_str(),
                               GetDeviceId().c_str()),
            dice_request_header_);
  // Check that the reconcilor was blocked and not unblocked before timeout.
  EXPECT_EQ(1, reconcilor_blocked_count_);
  EXPECT_EQ(0, reconcilor_unblocked_count_);
  task_runner->FastForwardBy(
      base::TimeDelta::FromHours(kLockAccountReconcilorTimeoutHours / 2));
  EXPECT_EQ(0, reconcilor_unblocked_count_);
  task_runner->FastForwardBy(
      base::TimeDelta::FromHours((kLockAccountReconcilorTimeoutHours + 1) / 2));
  // Wait until reconcilor is unblocked.
  WaitForReconcilorUnblockedCount(1);
}

// Checks that re-auth on Gaia triggers the fetch for a refresh token.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, Reauth) {
  EXPECT_EQ(0, reconcilor_started_count_);

  // Start from a signed-in state.
  SetupSignedInAccounts();
  EXPECT_EQ(1, reconcilor_started_count_);

  // Navigate to Gaia and sign in again with the main account.
  NavigateToURL(kSigninURL);

  // Check that the Dice request header was sent.
  std::string client_id = GaiaUrls::GetInstance()->oauth2_chrome_client_id();
  EXPECT_EQ(base::StringPrintf("version=%s,client_id=%s,device_id=%s,"
                               "signin_mode=all_accounts,"
                               "signout_mode=show_confirmation",
                               signin::kDiceProtocolVersion, client_id.c_str(),
                               GetDeviceId().c_str()),
            dice_request_header_);

  // Check that the token was requested and added to the token service.
  SendRefreshTokenResponse();
  EXPECT_EQ(GetMainAccountID(), GetIdentityManager()->GetPrimaryAccountId(
                                    signin::ConsentLevel::kSync));

  // Old token must not be revoked (see http://crbug.com/865189).
  EXPECT_EQ(0, token_revoked_notification_count_);

  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
  EXPECT_EQ(2, reconcilor_started_count_);
}

// Checks that the Dice signout flow works and deletes all tokens.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, SignoutMainAccount) {
  // Start from a signed-in state.
  SetupSignedInAccounts();

  // Signout from main account.
  SignOutWithDice(kMainAccount);

  // Check that the user is in error state.
  EXPECT_EQ(GetMainAccountID(), GetIdentityManager()->GetPrimaryAccountId(
                                    signin::ConsentLevel::kSync));
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshTokenInPersistentErrorState(
          GetMainAccountID()));
  EXPECT_TRUE(GetIdentityManager()->HasAccountWithRefreshToken(
      GetSecondaryAccountID()));

  // Token for main account is revoked on server but not notified in the client.
  EXPECT_EQ(0, token_revoked_notification_count_);
  WaitForTokenRevokedCount(1);

  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
}

// Checks that signing out from a secondary account does not delete the main
// token.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, SignoutSecondaryAccount) {
  // Start from a signed-in state.
  SetupSignedInAccounts();

  // Signout from secondary account.
  SignOutWithDice(kSecondaryAccount);

  // Check that the user is still signed in from main account, but secondary
  // token is deleted.
  EXPECT_EQ(GetMainAccountID(), GetIdentityManager()->GetPrimaryAccountId(
                                    signin::ConsentLevel::kSync));
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  EXPECT_FALSE(GetIdentityManager()->HasAccountWithRefreshToken(
      GetSecondaryAccountID()));
  EXPECT_EQ(1, token_revoked_notification_count_);
  WaitForTokenRevokedCount(1);
  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
}

// Checks that the Dice signout flow works and deletes all tokens.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, SignoutAllAccounts) {
  // Start from a signed-in state.
  SetupSignedInAccounts();

  // Signout from all accounts.
  SignOutWithDice(kAllAccounts);

  // Check that the user is in error state.
  EXPECT_EQ(GetMainAccountID(), GetIdentityManager()->GetPrimaryAccountId(
                                    signin::ConsentLevel::kSync));
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshTokenInPersistentErrorState(
          GetMainAccountID()));
  EXPECT_FALSE(GetIdentityManager()->HasAccountWithRefreshToken(
      GetSecondaryAccountID()));

  // Token for main account is revoked on server but not notified in the client.
  EXPECT_EQ(1, token_revoked_notification_count_);
  WaitForTokenRevokedCount(2);

  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
}

// Checks that Dice request header is not set from request from WebUI.
// See https://crbug.com/428396
#if defined(OS_WIN)
#define MAYBE_NoDiceFromWebUI DISABLED_NoDiceFromWebUI
#else
#define MAYBE_NoDiceFromWebUI NoDiceFromWebUI
#endif
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, MAYBE_NoDiceFromWebUI) {
  // Navigate to Gaia and from the native tab, which uses an extension.
  ui_test_utils::NavigateToURL(browser(),
                               GURL("chrome:chrome-signin?reason=5"));

  // Check that the request had no Dice request header.
  if (dice_request_header_.empty())
    WaitForClosure(&chrome_signin_embedded_quit_closure_);
  EXPECT_EQ(kNoDiceRequestHeader, dice_request_header_);
  EXPECT_EQ(0, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(0);
}

IN_PROC_BROWSER_TEST_F(DiceBrowserTest,
                       NoDiceExtensionConsent_LaunchWebAuthFlow) {
  auto web_auth_flow = std::make_unique<extensions::WebAuthFlow>(
      nullptr, browser()->profile(), https_server_.GetURL(kSigninURL),
      extensions::WebAuthFlow::INTERACTIVE,
      extensions::WebAuthFlow::LAUNCH_WEB_AUTH_FLOW);
  web_auth_flow->Start();

  if (dice_request_header_.empty())
    WaitForClosure(&signin_requested_quit_closure_);

  EXPECT_EQ(kNoDiceRequestHeader, dice_request_header_);
  EXPECT_EQ(0, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(0);

  // Delete the web auth flow (uses DeleteSoon).
  web_auth_flow.release()->DetachDelegateAndDelete();
  base::RunLoop().RunUntilIdle();
}

IN_PROC_BROWSER_TEST_F(DiceBrowserTest, DiceExtensionConsent_GetAuthToken) {
  // Signin from extension consent flow.
  class DummyDelegate : public extensions::WebAuthFlow::Delegate {
   public:
    void OnAuthFlowFailure(extensions::WebAuthFlow::Failure failure) override {}
    ~DummyDelegate() override = default;
  };

  DummyDelegate delegate;
  auto web_auth_flow = std::make_unique<extensions::WebAuthFlow>(
      &delegate, browser()->profile(), https_server_.GetURL(kSigninURL),
      extensions::WebAuthFlow::INTERACTIVE,
      extensions::WebAuthFlow::GET_AUTH_TOKEN);
  web_auth_flow->Start();

  // Check that the token was requested and added to the token service.
  SendRefreshTokenResponse();
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));

  // Check that the Dice request header was sent.
  std::string client_id = GaiaUrls::GetInstance()->oauth2_chrome_client_id();
  EXPECT_EQ(base::StringPrintf("version=%s,client_id=%s,device_id=%s,"
                               "signin_mode=all_accounts,"
                               "signout_mode=show_confirmation",
                               signin::kDiceProtocolVersion, client_id.c_str(),
                               GetDeviceId().c_str()),
            dice_request_header_);

  // Sync should not be enabled.
  EXPECT_TRUE(GetIdentityManager()
                  ->GetPrimaryAccountId(signin::ConsentLevel::kSync)
                  .empty());

  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
  EXPECT_EQ(1, reconcilor_started_count_);

  // Delete the web auth flow (uses DeleteSoon).
  web_auth_flow.release()->DetachDelegateAndDelete();
  base::RunLoop().RunUntilIdle();
}

// Tests that Sync is enabled if the ENABLE_SYNC response is received after the
// refresh token.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, EnableSyncAfterToken) {
  EXPECT_EQ(0, reconcilor_started_count_);

  // Signin using the Chrome Sync endpoint.
<<<<<<< HEAD
  signin_metrics::AccessPoint access_point =
      signin_metrics::AccessPoint::kSettings;
  browser()->signin_view_controller()->ShowDiceEnableSyncTab(
      access_point,
      signin_metrics::PromoAction::PROMO_ACTION_NEW_ACCOUNT_NO_EXISTING_ACCOUNT,
      /*email_hint=*/std::string());
=======
  browser()->signin_view_controller()->ShowSignin(
      profiles::BUBBLE_VIEW_MODE_GAIA_SIGNIN,
      signin_metrics::AccessPoint::ACCESS_POINT_SETTINGS);
>>>>>>> chromium

  // Receive token.
  EXPECT_FALSE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  SendRefreshTokenResponse();
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));

  // Receive ENABLE_SYNC.
  SendEnableSyncResponse();

  // Check that the Dice request header was sent, with signout confirmation.
  std::string client_id = GaiaUrls::GetInstance()->oauth2_chrome_client_id();
  EXPECT_EQ(base::StringPrintf("version=%s,client_id=%s,device_id=%s,"
                               "signin_mode=all_accounts,"
                               "signout_mode=show_confirmation",
                               signin::kDiceProtocolVersion, client_id.c_str(),
                               GetDeviceId().c_str()),
            dice_request_header_);

  content::WindowedNotificationObserver ntp_url_observer(
      content::NOTIFICATION_LOAD_STOP,
      base::BindRepeating([](const content::NotificationSource&,
                             const content::NotificationDetails& details) {
        auto url =
            content::Details<content::LoadNotificationDetails>(details)->url;
        // Some test flags (e.g. ForceWebRequestProxyForTest) can change whether
        // the reported NTP URL is chrome://newtab or chrome://new-tab-page.
        return url == GURL(chrome::kChromeUINewTabPageURL) ||
               url == GURL(chrome::kChromeUINewTabURL);
      }));

  WaitForSigninSucceeded();
  EXPECT_EQ(GetMainAccountID(), GetIdentityManager()->GetPrimaryAccountId(
                                    signin::ConsentLevel::kSync));

  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
  EXPECT_EQ(1, reconcilor_started_count_);

  // Check that the tab was navigated to the NTP.
  ntp_url_observer.Wait();

  // Dismiss the Sync confirmation UI.
  EXPECT_TRUE(login_ui_test_utils::ConfirmSyncConfirmationDialog(browser()));
}

// Tests that Sync is enabled if the ENABLE_SYNC response is received before the
// refresh token.

// https://crbug.com/1082858
#if (defined(OS_LINUX) || defined(OS_CHROMEOS)) && !defined(NDEBUG)
#define MAYBE_EnableSyncBeforeToken DISABLED_EnableSyncBeforeToken
#else
#define MAYBE_EnableSyncBeforeToken EnableSyncBeforeToken
#endif
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, MAYBE_EnableSyncBeforeToken) {
  EXPECT_EQ(0, reconcilor_started_count_);

  ui_test_utils::UrlLoadObserver enable_sync_url_observer(
      https_server_.GetURL(kEnableSyncURL),
      content::NotificationService::AllSources());

  // Signin using the Chrome Sync endpoint.
  browser()->signin_view_controller()->ShowSignin(
<<<<<<< HEAD
      signin_metrics::AccessPoint::kSettings);
=======
      profiles::BUBBLE_VIEW_MODE_GAIA_SIGNIN,
      signin_metrics::AccessPoint::ACCESS_POINT_SETTINGS);
>>>>>>> chromium

  // Receive ENABLE_SYNC.
  SendEnableSyncResponse();
  // Wait for the page to be fully loaded.
  enable_sync_url_observer.Wait();

  // Receive token.
  EXPECT_FALSE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  SendRefreshTokenResponse();
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));

  // Check that the Dice request header was sent, with signout confirmation.
  std::string client_id = GaiaUrls::GetInstance()->oauth2_chrome_client_id();
  EXPECT_EQ(base::StringPrintf("version=%s,client_id=%s,device_id=%s,"
                               "signin_mode=all_accounts,"
                               "signout_mode=show_confirmation",
                               signin::kDiceProtocolVersion, client_id.c_str(),
                               GetDeviceId().c_str()),
            dice_request_header_);

<<<<<<< HEAD
  // Wait for the Sync confirmation UI and click through.
  EXPECT_TRUE(login_ui_test_utils::ConfirmSyncConfirmationDialog(browser()));

  EXPECT_EQ(signin::ConsentLevel::kSync,
            signin::GetPrimaryAccountConsentLevel(GetIdentityManager()));
}

// Verifies that Chrome doesn't crash on browser window close when the sync
// confirmation dialog is waiting for its size.
// Regression test for https://crbug.com/1304055.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest,
                       CloseBrowserWhileInitializingSyncConfirmation) {
  // Signin using the Chrome Sync endpoint.
  browser()->signin_view_controller()->ShowSignin(
      signin_metrics::AccessPoint::kSettings);

  content::TestNavigationObserver sync_confirmation_url_observer(
      GURL("chrome://sync-confirmation?style=0"));
  sync_confirmation_url_observer.StartWatchingNewWebContents();

  // Receive token.
  SendRefreshTokenResponse();
  // Receive ENABLE_SYNC.
  SendEnableSyncResponse();
=======
  ui_test_utils::UrlLoadObserver ntp_url_observer(
      GURL(chrome::kChromeUINewTabURL),
      content::NotificationService::AllSources());
>>>>>>> chromium

  WaitForSigninSucceeded();
  EXPECT_EQ(GetMainAccountID(), GetIdentityManager()->GetPrimaryAccountId(
                                    signin::ConsentLevel::kSync));

  EXPECT_EQ(1, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(1);
  EXPECT_EQ(1, reconcilor_started_count_);

  // Check that the tab was navigated to the NTP.
  ntp_url_observer.Wait();

  // Dismiss the Sync confirmation UI.
  EXPECT_TRUE(login_ui_test_utils::ConfirmSyncConfirmationDialog(browser()));
}

// Tests that turning off Dice via preferences works.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, PRE_TurnOffDice) {
  // Sign the profile in.
  SetupSignedInAccounts();
  syncer::SyncPrefs(browser()->profile()->GetPrefs()).SetFirstSetupComplete();

  EXPECT_TRUE(AccountConsistencyModeManager::IsDiceEnabledForProfile(
      browser()->profile()));

  EXPECT_FALSE(GetIdentityManager()
                   ->GetPrimaryAccountId(signin::ConsentLevel::kSync)
                   .empty());
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  EXPECT_FALSE(GetIdentityManager()->GetAccountsWithRefreshTokens().empty());

  // Turn off Dice for this profile.
  browser()->profile()->GetPrefs()->SetBoolean(
      prefs::kSigninAllowedOnNextStartup, false);
}

IN_PROC_BROWSER_TEST_F(DiceBrowserTest, TurnOffDice) {
  // Check that Dice is disabled.
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(prefs::kSigninAllowed));
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kSigninAllowedOnNextStartup));
  EXPECT_FALSE(AccountConsistencyModeManager::IsDiceEnabledForProfile(
      browser()->profile()));

  EXPECT_TRUE(GetIdentityManager()
                  ->GetPrimaryAccountId(signin::ConsentLevel::kSync)
                  .empty());
  EXPECT_FALSE(
      GetIdentityManager()->HasAccountWithRefreshToken(GetMainAccountID()));
  EXPECT_TRUE(GetIdentityManager()->GetAccountsWithRefreshTokens().empty());

  // Navigate to Gaia and sign in.
  NavigateToURL(kSigninURL);
  // Check that the Dice request header was not sent.
  EXPECT_EQ(kNoDiceRequestHeader, dice_request_header_);
  EXPECT_EQ(0, reconcilor_blocked_count_);
  WaitForReconcilorUnblockedCount(0);
}

// Checks that Dice is disabled in incognito mode.
IN_PROC_BROWSER_TEST_F(DiceBrowserTest, Incognito) {
  Browser* incognito_browser = Browser::Create(Browser::CreateParams(
      browser()->profile()->GetPrimaryOTRProfile(/*create_if_needed=*/true),
      true));

  // Check that Dice is disabled.
  EXPECT_FALSE(AccountConsistencyModeManager::IsDiceEnabledForProfile(
      incognito_browser->profile()));
}

<<<<<<< HEAD
class DiceExplicitSigninRollbackBrowserTest : public InProcessBrowserTest {
 public:
  struct AccountStorageStatus {
    bool autofill_sync_toggle_available = false;
    syncer::UserSelectableTypeSet user_selectable_type_set;
  };

  // InProcessBrowserTest:
  void SetUpInProcessBrowserTestFixture() override {
    InProcessBrowserTest::SetUpInProcessBrowserTestFixture();
    client_helper_.SetUp();
  }

  DiceExplicitSigninRollbackBrowserTest() {
    std::vector<base::test::FeatureRef> features = {
        switches::kExplicitBrowserSigninUIOnDesktop};
    std::vector<base::test::FeatureRef> enabled_features;
    std::vector<base::test::FeatureRef> disabled_features;

    if (content::IsPreTest()) {
      // PRE_ test has explicit signin.
      enabled_features = std::move(features);
    } else {
      // Non-PRE_ test has implicit signin.
      disabled_features = std::move(features);
    }
    feature_list_.InitWithFeatures(enabled_features, disabled_features);
  }

  signin::IdentityManager* GetIdentityManager() {
    return IdentityManagerFactory::GetForProfile(browser()->profile());
  }

  AccountStorageStatus GetAccountStorageStatus() {
    syncer::SyncUserSettings* settings =
        SyncServiceFactory::GetForProfile(browser()->profile())
            ->GetUserSettings();
    return {.autofill_sync_toggle_available =
                autofill::PersonalDataManagerFactory::GetForBrowserContext(
                    browser()->profile())
                    ->address_data_manager()
                    .IsAutofillSyncToggleAvailable(),
            .user_selectable_type_set = settings->GetSelectedTypes()};
  }

  network::TestURLLoaderFactory* test_url_loader_factory() {
    return client_helper_.test_url_loader_factory();
  }

 private:
  ChromeSigninClientWithURLLoaderHelper client_helper_;
  base::test::ScopedFeatureList feature_list_;
};

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninRollbackBrowserTest, PRE_Rollback) {
  signin::AccountAvailabilityOptionsBuilder builder;
  signin::MakeAccountAvailable(
      GetIdentityManager(),
      builder.AsPrimary(signin::ConsentLevel::kSignin)
          .WithAccessPoint(
              signin_metrics::AccessPoint::kChromeSigninInterceptBubble)
          .Build(kMainGmailEmail));
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSignin);

  ASSERT_TRUE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kExplicitBrowserSignin));

  // Butter for autofill is enabled.
  AccountStorageStatus account_storage_status = GetAccountStorageStatus();
  EXPECT_TRUE(account_storage_status.autofill_sync_toggle_available);
  EXPECT_TRUE(account_storage_status.user_selectable_type_set.HasAll(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));
  // Cookie migration is complete.
  EXPECT_TRUE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kCookieClearOnExitMigrationNoticeComplete));
}

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninRollbackBrowserTest, Rollback) {
  Profile* profile = browser()->profile();
  // The user is now signed in implicitly.
  signin::WaitForRefreshTokensLoaded(GetIdentityManager());
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSignin);
  ASSERT_TRUE(gaia::AreEmailsSame(
      GetIdentityManager()
          ->GetPrimaryAccountInfo(signin::ConsentLevel::kSignin)
          .email,
      kMainGmailEmail));
  ASSERT_FALSE(profile->GetPrefs()->GetBoolean(prefs::kExplicitBrowserSignin));
  // Account storage is disabled.
  AccountStorageStatus account_storage_status = GetAccountStorageStatus();
  EXPECT_FALSE(account_storage_status.user_selectable_type_set.HasAny(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));
  // Cookie migration is required.
  EXPECT_FALSE(profile->GetPrefs()->GetBoolean(
      prefs::kCookieClearOnExitMigrationNoticeComplete));
  // And cannot be completed by changing cookie settings.
  content_settings::CookieSettings* settings =
      CookieSettingsFactory::GetForProfile(profile).get();
  settings->SetDefaultCookieSetting(CONTENT_SETTING_ALLOW);
  EXPECT_FALSE(profile->GetPrefs()->GetBoolean(
      prefs::kCookieClearOnExitMigrationNoticeComplete));
}

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninRollbackBrowserTest,
                       PRE_RollbackSigninPending) {
  signin::MakeAccountAvailable(
      GetIdentityManager(),
      signin::AccountAvailabilityOptionsBuilder()
          .AsPrimary(signin::ConsentLevel::kSignin)
          .WithAccessPoint(
              signin_metrics::AccessPoint::kChromeSigninInterceptBubble)
          .Build(kMainGmailEmail));
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSignin);
  ASSERT_TRUE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kExplicitBrowserSignin));

  // Induce SigninPending
  signin::SetInvalidRefreshTokenForPrimaryAccount(GetIdentityManager());

  // Still signed in.
  EXPECT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSignin);
  // But account is in error.
  EXPECT_TRUE(
      GetIdentityManager()->HasAccountWithRefreshTokenInPersistentErrorState(
          GetIdentityManager()->GetPrimaryAccountId(
              signin::ConsentLevel::kSignin)));
}

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninRollbackBrowserTest,
                       RollbackSigninPending) {
  // The account is signed out after tokens are loaded.
  signin::WaitForRefreshTokensLoaded(GetIdentityManager());
  // After rollback, a signin pending state should transition to signed out.
  EXPECT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            std::nullopt);
}

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninRollbackBrowserTest,
                       PRE_RollbackWebSigninOnly) {
  // Signin on the web only.
  AccountInfo account_info = signin::MakeAccountAvailable(
      GetIdentityManager(),
      signin::AccountAvailabilityOptionsBuilder(test_url_loader_factory())
          .WithAccessPoint(signin_metrics::AccessPoint::kWebSignin)
          .WithCookie()
          .Build(kMainGmailEmail));
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            std::nullopt);
  ASSERT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kExplicitBrowserSignin));

  // Signed in on the web.
  EXPECT_TRUE(GetIdentityManager()->HasAccountWithRefreshToken(
      account_info.account_id));
  signin::AccountsInCookieJarInfo cookie_jar =
      GetIdentityManager()->GetAccountsInCookieJar();
  ASSERT_TRUE(cookie_jar.AreAccountsFresh());
  ASSERT_EQ(cookie_jar.GetSignedInAccounts().size(), 1u);
  EXPECT_TRUE(gaia::AreEmailsSame(cookie_jar.GetSignedInAccounts()[0].email,
                                  kMainGmailEmail));
}

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninRollbackBrowserTest,
                       RollbackWebSigninOnly) {
  signin::WaitForRefreshTokensLoaded(GetIdentityManager());
  signin::TriggerListAccount(GetIdentityManager(), test_url_loader_factory());
  // After rollback, Chrome would be implicitly signed in.
  EXPECT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSignin);
  CoreAccountInfo primary_account = GetIdentityManager()->GetPrimaryAccountInfo(
      signin::ConsentLevel::kSignin);
  EXPECT_TRUE(gaia::AreEmailsSame(primary_account.email, kMainGmailEmail));
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kExplicitBrowserSignin));

  // Signed in on the web as well.
  EXPECT_TRUE(GetIdentityManager()->HasAccountWithRefreshToken(
      primary_account.account_id));
  signin::AccountsInCookieJarInfo cookie_jar =
      GetIdentityManager()->GetAccountsInCookieJar();
  ASSERT_TRUE(cookie_jar.AreAccountsFresh());
  ASSERT_EQ(cookie_jar.GetSignedInAccounts().size(), 1u);
  EXPECT_TRUE(gaia::AreEmailsSame(cookie_jar.GetSignedInAccounts()[0].email,
                                  kMainGmailEmail));
}

class DiceExplicitSigninBrowserTest : public InProcessBrowserTest {
 public:
  struct AccountStorageStatus {
    bool autofill_sync_toggle_available = false;
    syncer::UserSelectableTypeSet user_selectable_type_set;
  };

  DiceExplicitSigninBrowserTest() {
    std::vector<base::test::FeatureRef> enabled_features;
    std::vector<base::test::FeatureRef> disabled_features;

    if (content::IsPreTest()) {
      disabled_features.push_back(switches::kExplicitBrowserSigninUIOnDesktop);
    } else {
      enabled_features.push_back(switches::kExplicitBrowserSigninUIOnDesktop);
    }
    feature_list_.InitWithFeatures(enabled_features, disabled_features);
  }

  signin::IdentityManager* GetIdentityManager() {
    return IdentityManagerFactory::GetForProfile(browser()->profile());
  }

  AccountStorageStatus GetAccountStorageStatus() {
    syncer::SyncUserSettings* settings =
        SyncServiceFactory::GetForProfile(browser()->profile())
            ->GetUserSettings();
    return {.autofill_sync_toggle_available =
                autofill::PersonalDataManagerFactory::GetForBrowserContext(
                    browser()->profile())
                    ->address_data_manager()
                    .IsAutofillSyncToggleAvailable(),
            .user_selectable_type_set = settings->GetSelectedTypes()};
  }

 private:
  base::test::ScopedFeatureList feature_list_;
};

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninBrowserTest, PRE_Migration) {
  signin::AccountAvailabilityOptionsBuilder builder;
  signin::MakeAccountAvailable(
      GetIdentityManager(),
      builder
          .AsPrimary(signin::ConsentLevel::kSignin)
          // `kWebSignin` is not explicit before the migration.
          .WithAccessPoint(signin_metrics::AccessPoint::kWebSignin)
          .Build(kMainGmailEmail));
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSignin);

  ASSERT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kExplicitBrowserSignin));

  AccountStorageStatus account_storage_status = GetAccountStorageStatus();
  EXPECT_FALSE(account_storage_status.autofill_sync_toggle_available);
  EXPECT_FALSE(account_storage_status.user_selectable_type_set.HasAny(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));
}

// Checks that a user who signed in with Dice before
// `switches::kExplicitBrowserSigninUIOnDesktop` was enabled does not get the
// account storage enabled silently. Account storage is enabled after the user
// signs out and signs in again through an explicit flow.
IN_PROC_BROWSER_TEST_F(DiceExplicitSigninBrowserTest, Migration) {
  Profile* profile = browser()->profile();
  // The user is still signed in implicitly.
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSignin);
  ASSERT_TRUE(gaia::AreEmailsSame(
      GetIdentityManager()
          ->GetPrimaryAccountInfo(signin::ConsentLevel::kSignin)
          .email,
      kMainGmailEmail));
  ASSERT_FALSE(profile->GetPrefs()->GetBoolean(prefs::kExplicitBrowserSignin));
  // Account storage was not enabled yet.
  AccountStorageStatus account_storage_status = GetAccountStorageStatus();
  EXPECT_FALSE(account_storage_status.user_selectable_type_set.HasAny(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));

  // Signout, and then signin again explicitly.
  signin::ClearPrimaryAccount(GetIdentityManager());
  AccountInfo primary_account_info = signin::MakePrimaryAccountAvailable(
      GetIdentityManager(), kMainGmailEmail, signin::ConsentLevel::kSignin);
  EXPECT_TRUE(profile->GetPrefs()->GetBoolean(prefs::kExplicitBrowserSignin));

  // Account storage is now enabled.
  account_storage_status = GetAccountStorageStatus();
  EXPECT_TRUE(account_storage_status.user_selectable_type_set.HasAll(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));

  // Cookie migration is done.
  EXPECT_TRUE(profile->GetPrefs()->GetBoolean(
      prefs::kCookieClearOnExitMigrationNoticeComplete));
}

// Checks that migration handles Cookie clear on exit and sync toggles.
IN_PROC_BROWSER_TEST_F(DiceExplicitSigninBrowserTest,
                       PRE_MigrationWithSettings) {
  Profile* profile = browser()->profile();
  signin::AccountAvailabilityOptionsBuilder builder;
  signin::MakeAccountAvailable(
      GetIdentityManager(),
      builder.AsPrimary(signin::ConsentLevel::kSync).Build(kMainGmailEmail));
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSync);

  ASSERT_FALSE(profile->GetPrefs()->GetBoolean(prefs::kExplicitBrowserSignin));

  // Set cookie clear on exit, and set addresses and password sync to OFF.
  content_settings::CookieSettings* settings =
      CookieSettingsFactory::GetForProfile(profile).get();
  settings->SetDefaultCookieSetting(CONTENT_SETTING_SESSION_ONLY);
  syncer::SyncPrefs(profile->GetPrefs())
      .SetSelectedTypesForSyncingUser(
          /*keep_everything_synced=*/false,
          /*registered_types=*/syncer::UserSelectableTypeSet::All(),
          /*selected_types=*/{});

  AccountStorageStatus account_storage_status = GetAccountStorageStatus();
  EXPECT_FALSE(account_storage_status.autofill_sync_toggle_available);
  EXPECT_FALSE(account_storage_status.user_selectable_type_set.HasAny(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));
}

IN_PROC_BROWSER_TEST_F(DiceExplicitSigninBrowserTest, MigrationWithSettings) {
  Profile* profile = browser()->profile();
  // The user is still signed in implicitly.
  ASSERT_EQ(signin::GetPrimaryAccountConsentLevel(GetIdentityManager()),
            signin::ConsentLevel::kSync);
  ASSERT_TRUE(gaia::AreEmailsSame(
      GetIdentityManager()
          ->GetPrimaryAccountInfo(signin::ConsentLevel::kSync)
          .email,
      kMainGmailEmail));
  ASSERT_FALSE(profile->GetPrefs()->GetBoolean(prefs::kExplicitBrowserSignin));

  // Account storage was not enabled yet.
  AccountStorageStatus account_storage_status = GetAccountStorageStatus();
  EXPECT_FALSE(account_storage_status.user_selectable_type_set.HasAny(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));

  // Signout, and then signin again explicitly.
  signin::ClearPrimaryAccount(GetIdentityManager());
  AccountInfo primary_account_info = signin::MakePrimaryAccountAvailable(
      GetIdentityManager(), kMainGmailEmail, signin::ConsentLevel::kSignin);
  EXPECT_TRUE(profile->GetPrefs()->GetBoolean(prefs::kExplicitBrowserSignin));

  // Account storage is not enabled, because Sync settings were carried over.
  account_storage_status = GetAccountStorageStatus();
  EXPECT_FALSE(account_storage_status.user_selectable_type_set.HasAny(
      {syncer::UserSelectableType::kAutofill,
       syncer::UserSelectableType::kPasswords}));

  // Cookie migration is not done, because there is clear on exit.
  content_settings::CookieSettings* settings =
      CookieSettingsFactory::GetForProfile(profile).get();
  EXPECT_EQ(CONTENT_SETTING_SESSION_ONLY, settings->GetDefaultCookieSetting());
  EXPECT_FALSE(profile->GetPrefs()->GetBoolean(
      prefs::kCookieClearOnExitMigrationNoticeComplete));

  // Allow cookies to trigger the migration.
  settings->SetDefaultCookieSetting(CONTENT_SETTING_ALLOW);
  EXPECT_TRUE(profile->GetPrefs()->GetBoolean(
      prefs::kCookieClearOnExitMigrationNoticeComplete));
}

// Signin implicitlty, Dice Signin.
IN_PROC_BROWSER_TEST_F(DiceExplicitSigninBrowserTest,
                       PRE_DiceUserMigratedClearsCookie) {
  signin::MakeAccountAvailable(
      GetIdentityManager(),
      signin::AccountAvailabilityOptionsBuilder()
          .AsPrimary(signin::ConsentLevel::kSignin)
          // `kWebSignin` is not explicit before the migration.
          .WithAccessPoint(signin_metrics::AccessPoint::kWebSignin)
          .Build(kMainGmailEmail));
  // Set the SAPISID cookie so that its deletion can be detected later.
  // Set a max-age so that it's persisted on disk.
  std::string gaia_cookie = base::StrCat(
      {GaiaConstants::kGaiaSigninCookieName, "=foo; secure; max-age=1000"});
  ASSERT_TRUE(content::SetCookie(browser()->profile(),
                                 GURL("https://google.com/"), gaia_cookie));
  ASSERT_TRUE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  ASSERT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kExplicitBrowserSignin));
}

// Dice Signin with `switches::kExplicitBrowserSigninUIOnDesktop` enabled.
IN_PROC_BROWSER_TEST_F(DiceExplicitSigninBrowserTest,
                       DiceUserMigratedClearsCookie) {
  Profile* profile = browser()->profile();
  // The user is still signed in implicitly.
  ASSERT_TRUE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  ASSERT_TRUE(gaia::AreEmailsSame(
      GetIdentityManager()
          ->GetPrimaryAccountInfo(signin::ConsentLevel::kSignin)
          .email,
      kMainGmailEmail));
  ASSERT_FALSE(profile->GetPrefs()->GetBoolean(prefs::kExplicitBrowserSignin));

  content::DeleteCookies(profile, network::mojom::CookieDeletionFilter());

  // User should be signed out.
  EXPECT_FALSE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
}

class DiceBrowserTestWithExplicitSignin : public DiceBrowserTest {
 public:
  // Sets the user choice for Chrome Signin on `main_email_`.
  void SetChromeSigninChoice(ChromeSigninUserChoice choice) {
    SigninPrefs(*browser()->profile()->GetPrefs())
        .SetChromeSigninInterceptionUserChoice(
            signin::GetTestGaiaIdForEmail(main_email_), choice);
  }

  // Signs in `main_email_`.
  void SimulateWebSigninMainAccount() {
    NavigateToURL(kSigninURL);
    SendRefreshTokenResponse();
    WaitForReconcilorUnblockedCount(1);
  }

 private:
  base::test::ScopedFeatureList scoped_feature_list_{
      switches::kExplicitBrowserSigninUIOnDesktop};
};

IN_PROC_BROWSER_TEST_F(DiceBrowserTestWithExplicitSignin,
                       SigninWithChoiceRemembered_NoChoiceDefault) {
  // Sign in with no prior user action -- same as
  // `ChromeSigninUserChoice::kNoChoice`.
  SimulateWebSigninMainAccount();

  EXPECT_FALSE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  ASSERT_EQ(GetIdentityManager()->GetAccountsWithRefreshTokens().size(), 1u);
  EXPECT_TRUE(gaia::AreEmailsSame(
      GetIdentityManager()->GetAccountsWithRefreshTokens()[0].email,
      main_email_));
}

IN_PROC_BROWSER_TEST_F(DiceBrowserTestWithExplicitSignin,
                       SigninWithChoiceRemembered_NoChoice) {
  // Simulates no previous choice yet.
  SetChromeSigninChoice(ChromeSigninUserChoice::kNoChoice);

  SimulateWebSigninMainAccount();

  EXPECT_FALSE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  ASSERT_EQ(GetIdentityManager()->GetAccountsWithRefreshTokens().size(), 1u);
  EXPECT_TRUE(gaia::AreEmailsSame(
      GetIdentityManager()->GetAccountsWithRefreshTokens()[0].email,
      main_email_));
}

IN_PROC_BROWSER_TEST_F(DiceBrowserTestWithExplicitSignin,
                       SigninWithChoiceRemembered_DoNotSignin) {
  // Simulates a previous choice done with do not sign in.
  SetChromeSigninChoice(ChromeSigninUserChoice::kDoNotSignin);

  SimulateWebSigninMainAccount();

  EXPECT_FALSE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  ASSERT_EQ(GetIdentityManager()->GetAccountsWithRefreshTokens().size(), 1u);
  EXPECT_TRUE(gaia::AreEmailsSame(
      GetIdentityManager()->GetAccountsWithRefreshTokens()[0].email,
      main_email_));
}

IN_PROC_BROWSER_TEST_F(DiceBrowserTestWithExplicitSignin,
                       SigninWithChoiceRemembered_AlwaysAsk) {
  // Simulates a previous choice done with always ask, expecting the Chrome
  // Signin bubble to show.
  SetChromeSigninChoice(ChromeSigninUserChoice::kAlwaysAsk);

  SimulateWebSigninMainAccount();

  EXPECT_FALSE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
}

IN_PROC_BROWSER_TEST_F(DiceBrowserTestWithExplicitSignin,
                       SigninWithChoiceRemembered_Signin) {
  base::HistogramTester histogram_tester;

  PrefService* prefs = browser()->profile()->GetPrefs();
  ASSERT_FALSE(prefs->GetBoolean(prefs::kExplicitBrowserSignin));

  // Simulates a previous choice done with Always sign in.
  SetChromeSigninChoice(ChromeSigninUserChoice::kSignin);

  SimulateWebSigninMainAccount();

  EXPECT_TRUE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  histogram_tester.ExpectUniqueSample(
      "Signin.SignIn.Completed",
      signin_metrics::AccessPoint::kSigninChoiceRemembered, 1);
  // Should still count as an explicit sign in since the choice was explicit
  // set.
  EXPECT_TRUE(prefs->GetBoolean(prefs::kExplicitBrowserSignin));
}

class DiceBrowserTestWithChromeSigninIPH
    : public InteractiveFeaturePromoTestT<DiceBrowserTestWithExplicitSignin> {
 public:
  DiceBrowserTestWithChromeSigninIPH()
      : InteractiveFeaturePromoTestT(UseDefaultTrackerAllowingPromos(
            {feature_engagement::
                 kIPHExplicitBrowserSigninPreferenceRememberedFeature})) {}

  void SimulateExtendedAccountInfoFetched() {
    CoreAccountInfo core_account_info =
        GetIdentityManager()->GetPrimaryAccountInfo(
            signin::ConsentLevel::kSignin);
    AccountInfo account_info =
        GetIdentityManager()->FindExtendedAccountInfo(core_account_info);
    account_info.full_name = "First Last";
    account_info.given_name = "First";
    account_info.hosted_domain = kNoHostedDomainFound;
    account_info.picture_url = "https://example.com";
    signin::UpdateAccountInfoForAccount(GetIdentityManager(), account_info);
  }

  void CloseIPH() {
    RunTestSequence(
        PressButton(user_education::HelpBubbleView::kCloseButtonIdForTesting),
        WaitForHide(
            user_education::HelpBubbleView::kHelpBubbleElementIdForTesting),
        CheckResult(
            [this]() {
              return browser()->window()->IsFeaturePromoActive(
                  feature_engagement::
                      kIPHExplicitBrowserSigninPreferenceRememberedFeature);
            },
            false));
  }

  void SignoutAndResetState() {
    signin::ClearPrimaryAccount(GetIdentityManager());

    // Reset internal state to sign in again.
    token_requested_ = false;
    refresh_token_available_ = false;
    reconcilor_unblocked_count_ = 0;
    reconcilor_blocked_count_ = 0;

    EXPECT_FALSE(
        GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  }
};

IN_PROC_BROWSER_TEST_F(DiceBrowserTestWithChromeSigninIPH,
                       SigninRememberedIPH) {
  // The IPH can be shown after 14 days. Use 15 in the test to avoid any
  // precision problem.
  base::TimeDelta kIPHReshowDelay = base::Days(15);
  // Simulates a previous choice done with Always sign in.
  SetChromeSigninChoice(ChromeSigninUserChoice::kSignin);

  base::HistogramTester histogram_tester;
  SimulateWebSigninMainAccount();

  EXPECT_TRUE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  histogram_tester.ExpectUniqueSample(
      "Signin.SignIn.Completed",
      signin_metrics::AccessPoint::kSigninChoiceRemembered, 1);

  CoreAccountInfo core_account_info =
      GetIdentityManager()->GetPrimaryAccountInfo(
          signin::ConsentLevel::kSignin);
  AccountInfo account_info =
      GetIdentityManager()->FindExtendedAccountInfo(core_account_info);

  // IPH not showing yet, waiting for the name.
  ASSERT_TRUE(account_info.given_name.empty());
  EXPECT_FALSE(browser()->window()->IsFeaturePromoActive(
      feature_engagement::
          kIPHExplicitBrowserSigninPreferenceRememberedFeature));

  // IPH shown after receiving the name.
  SimulateExtendedAccountInfoFetched();
  EXPECT_TRUE(browser()->window()->IsFeaturePromoActive(
      feature_engagement::
          kIPHExplicitBrowserSigninPreferenceRememberedFeature));

  // Sign-in once more, the IPH is not shown again.
  CloseIPH();
  SignoutAndResetState();
  SimulateWebSigninMainAccount();
  EXPECT_TRUE(
      GetIdentityManager()->HasPrimaryAccount(signin::ConsentLevel::kSignin));
  histogram_tester.ExpectUniqueSample(
      "Signin.SignIn.Completed",
      signin_metrics::AccessPoint::kSigninChoiceRemembered, 2);
  SimulateExtendedAccountInfoFetched();
  EXPECT_FALSE(browser()->window()->IsFeaturePromoActive(
      feature_engagement::
          kIPHExplicitBrowserSigninPreferenceRememberedFeature));

  // The IPH can be reshown two weeks after the signout.
  RunTestSequence(AdvanceTime(kIPHReshowDelay));
  SignoutAndResetState();
  SimulateWebSigninMainAccount();
  SimulateExtendedAccountInfoFetched();
  // IPH does not reshow yet, because the delay was before the signout event.
  EXPECT_FALSE(browser()->window()->IsFeaturePromoActive(
      feature_engagement::
          kIPHExplicitBrowserSigninPreferenceRememberedFeature));
  SignoutAndResetState();
  // Wait 2 weeks after the signout event (by overriding the last signout date).
  SigninPrefs(*browser()->profile()->GetPrefs())
      .SetChromeLastSignoutTime(core_account_info.gaia,
                                base::Time::Now() - kIPHReshowDelay);
  SimulateWebSigninMainAccount();
  SimulateExtendedAccountInfoFetched();
  // IPH can now show again.
  EXPECT_TRUE(browser()->window()->IsFeaturePromoActive(
      feature_engagement::
          kIPHExplicitBrowserSigninPreferenceRememberedFeature));
}

=======
>>>>>>> chromium
// This test is not specifically related to DICE, but it extends
// |DiceBrowserTest| for convenience.
class DiceManageAccountBrowserTest : public DiceBrowserTest {
 public:
  DiceManageAccountBrowserTest()
      : DiceBrowserTest(kMainManagedEmail),
        // Skip showing the error message box to avoid freezing the main thread.
        skip_message_box_auto_reset_(
            &chrome::internal::g_should_skip_message_box_for_test,
            true),
        // Force the policy component to prohibit clearing the primary account
        // even when the policy core component is not initialized.
        prohibit_sigout_auto_reset_(
            &policy::internal::g_force_prohibit_signout_for_tests,
            true) {}

  void SetUp() override {
#if defined(OS_WIN)
    // Shortcut deletion delays tests shutdown on Win-7 and results in time out.
    // See crbug.com/1073451.
    AppShortcutManager::SuppressShortcutsForTesting();
#endif
    DiceBrowserTest::SetUp();
  }

 protected:
  base::AutoReset<bool> skip_message_box_auto_reset_;
  base::AutoReset<bool> prohibit_sigout_auto_reset_;
  unsigned int number_of_profiles_added_ = 0;
};

// Tests that prohiting sign-in on startup for a managed profile clears the
// profile directory on next start-up.
IN_PROC_BROWSER_TEST_F(DiceManageAccountBrowserTest,
                       PRE_ClearManagedProfileOnStartup) {
  // Ensure that there are not deleted profiles before running this test.
  PrefService* local_state = g_browser_process->local_state();
  DCHECK(local_state);
  const base::ListValue* deleted_profiles =
      local_state->GetList(prefs::kProfilesDeleted);
  ASSERT_TRUE(deleted_profiles);
  ASSERT_TRUE(deleted_profiles->GetList().empty());

  // Sign the profile in.
  SetupSignedInAccounts();

  // Prohibit sign-in on next start-up.
  browser()->profile()->GetPrefs()->SetBoolean(
      prefs::kSigninAllowedOnNextStartup, false);
}

IN_PROC_BROWSER_TEST_F(DiceManageAccountBrowserTest,
                       ClearManagedProfileOnStartup) {
  // Initial profile should have been deleted as sign-in and sign out were no
  // longer allowed.
  PrefService* local_state = g_browser_process->local_state();
  DCHECK(local_state);
  const base::ListValue* deleted_profiles =
      local_state->GetList(prefs::kProfilesDeleted);
  EXPECT_TRUE(deleted_profiles);
  EXPECT_EQ(1U, deleted_profiles->GetList().size());

  content::RunAllTasksUntilIdle();

  // Verify that there is an active profile.
  Profile* initial_profile = browser()->profile();
  EXPECT_EQ(1U, g_browser_process->profile_manager()->GetNumberOfProfiles());
  EXPECT_EQ(g_browser_process->profile_manager()->GetLastUsedProfile(),
            initial_profile);
}
