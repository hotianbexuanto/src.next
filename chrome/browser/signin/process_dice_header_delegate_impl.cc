// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/signin/process_dice_header_delegate_impl.h"

#include <utility>

#include "base/callback.h"
#include "base/logging.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/signin/dice_tab_helper.h"
#include "chrome/browser/signin/dice_web_signin_interceptor.h"
#include "chrome/browser/signin/dice_web_signin_interceptor_factory.h"
#include "chrome/browser/signin/identity_manager_factory.h"
#include "chrome/browser/ui/webui/signin/signin_ui_error.h"
#include "chrome/common/url_constants.h"
#include "components/signin/public/identity_manager/identity_manager.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/web_contents.h"
#include "url/gurl.h"

namespace {

void RedirectToNtp(content::WebContents* contents) {
  VLOG(1) << "RedirectToNtp";
  contents->GetController().LoadURL(
      GURL(chrome::kChromeUINewTabURL), content::Referrer(),
      ui::PAGE_TRANSITION_AUTO_TOPLEVEL, std::string());
}

// Helper function similar to DiceTabHelper::FromWebContents(), but also handles
// the case where |contents| is nullptr.
DiceTabHelper* GetDiceTabHelperFromWebContents(content::WebContents* contents) {
  if (!contents)
    return nullptr;
  return DiceTabHelper::FromWebContents(contents);
}

<<<<<<< HEAD
// Should Sign in to Chrome for all access points when Uno is enabled. Except
// for Web Signin where we first check the user choice first on whether to
// automatically sign in or not.
void AttemptChromeSignin(CoreAccountId account_id,
                         Profile& profile,
                         signin_metrics::AccessPoint access_point) {
  CHECK(!account_id.empty());

  // For the non-ExplicitBrowserSignin equivalent counterpart, the code takes
  // care of in `SigninManager::UpdateUnconsentedPrimaryAccount()`.
  if (!switches::IsExplicitBrowserSigninUIOnDesktopEnabled()) {
    return;
  }

  // Do not sign in if the access point is unknown.
  if (access_point == signin_metrics::AccessPoint::kUnknown) {
    return;
  }

  signin::IdentityManager* identity_manager =
      IdentityManagerFactory::GetForProfile(&profile);
  if (access_point == signin_metrics::AccessPoint::kWebSignin) {
    if (switches::IsExplicitBrowserSigninUIOnDesktopEnabled()) {
      AccountInfo account_info =
          identity_manager->FindExtendedAccountInfoByAccountId(account_id);
      // If the user did not choose the signin choice, do not proceed with a
      // sign in from a Web Signin.
      if (SigninPrefs(*profile.GetPrefs())
              .GetChromeSigninInterceptionUserChoice(account_info.gaia) !=
          ChromeSigninUserChoice::kSignin) {
        return;
      }

      // Proceed with the access point as the choice remembered.
      access_point = signin_metrics::AccessPoint::kSigninChoiceRemembered;
    }
  }

  // This access point should only be used as a result of a non Uno flow.
  CHECK_NE(signin_metrics::AccessPoint::kDesktopSigninManager, access_point);

  if (!identity_manager->HasPrimaryAccount(signin::ConsentLevel::kSignin)) {
    base::UmaHistogramEnumeration("Signin.SigninManager.SigninAccessPoint",
                                  access_point);
    identity_manager->GetPrimaryAccountMutator()->SetPrimaryAccount(
        account_id, signin::ConsentLevel::kSignin, access_point);
  }
}

}  // namespace

// static
std::unique_ptr<ProcessDiceHeaderDelegateImpl>
ProcessDiceHeaderDelegateImpl::Create(content::WebContents* web_contents) {
  bool is_sync_signin_tab = false;
  signin_metrics::AccessPoint access_point =
      signin_metrics::AccessPoint::kUnknown;
  signin_metrics::PromoAction promo_action =
      signin_metrics::PromoAction::PROMO_ACTION_NO_SIGNIN_PROMO;
  GURL redirect_url;
  EnableSyncCallback enable_sync_callback;
  OnSigninHeaderReceived on_signin_header_received;
  ShowSigninErrorCallback show_signin_error_callback;

  DiceTabHelper* tab_helper = DiceTabHelper::FromWebContents(web_contents);
  if (tab_helper) {
    is_sync_signin_tab = tab_helper->IsSyncSigninInProgress();
    redirect_url = tab_helper->redirect_url();
    access_point = tab_helper->signin_access_point();
    promo_action = tab_helper->signin_promo_action();
    // `show_signin_error_callback` may be null if the `DiceTabHelper` was reset
    // after completion of a signin flow.
    show_signin_error_callback =
        std::move(tab_helper->GetShowSigninErrorCallback());
    if (is_sync_signin_tab) {
      enable_sync_callback = tab_helper->GetEnableSyncCallback();
    }

    on_signin_header_received = tab_helper->GetOnSigninHeaderReceived();

  } else {
    access_point = signin_metrics::AccessPoint::kWebSignin;
=======
}  // namespace

ProcessDiceHeaderDelegateImpl::ProcessDiceHeaderDelegateImpl(
    content::WebContents* web_contents,
    EnableSyncCallback enable_sync_callback,
    ShowSigninErrorCallback show_signin_error_callback)
    : content::WebContentsObserver(web_contents),
      profile_(Profile::FromBrowserContext(web_contents->GetBrowserContext())),
      enable_sync_callback_(std::move(enable_sync_callback)),
      show_signin_error_callback_(std::move(show_signin_error_callback)) {
  DCHECK(web_contents);
  DCHECK(profile_);

  DiceTabHelper* tab_helper = DiceTabHelper::FromWebContents(web_contents);
  if (tab_helper) {
    is_sync_signin_tab_ = tab_helper->IsSyncSigninInProgress();
    redirect_url_ = tab_helper->redirect_url();
    access_point_ = tab_helper->signin_access_point();
    promo_action_ = tab_helper->signin_promo_action();
    reason_ = tab_helper->signin_reason();
>>>>>>> chromium
  }
}

ProcessDiceHeaderDelegateImpl::~ProcessDiceHeaderDelegateImpl() = default;

bool ProcessDiceHeaderDelegateImpl::ShouldEnableSync() {
  if (IdentityManagerFactory::GetForProfile(profile_)->HasPrimaryAccount(
          signin::ConsentLevel::kSync)) {
    VLOG(1) << "Do not start sync after web sign-in [already authenticated].";
    return false;
  }

  if (!is_sync_signin_tab_) {
    VLOG(1)
        << "Do not start sync after web sign-in [not a Chrome sign-in tab].";
    return false;
  }

  return true;
}

void ProcessDiceHeaderDelegateImpl::HandleTokenExchangeSuccess(
    CoreAccountId account_id,
    bool is_new_account) {
  // is_sync_signin_tab_ tells whether the current signin is happening in a tab
  // that was opened from a "Enable Sync" Chrome UI. Usually this is indeed a
  // sync signin, but it is not always the case: the user may abandon the sync
  // signin and do a simple web signin in the same tab instead.
  DiceWebSigninInterceptorFactory::GetForProfile(profile_)
      ->MaybeInterceptWebSignin(web_contents(), account_id, is_new_account,
                                is_sync_signin_tab_);
}

void ProcessDiceHeaderDelegateImpl::EnableSync(
    const CoreAccountId& account_id) {
  DiceTabHelper* tab_helper = GetDiceTabHelperFromWebContents(web_contents());
  if (tab_helper)
    tab_helper->OnSyncSigninFlowComplete();

  if (!ShouldEnableSync()) {
    // No special treatment is needed if the user is not enabling sync.
    return;
  }

  content::WebContents* web_contents = this->web_contents();
  VLOG(1) << "Start sync after web sign-in.";
  std::move(enable_sync_callback_)
      .Run(profile_, access_point_, promo_action_, reason_, web_contents,
           account_id);

  if (!web_contents)
    return;

  // After signing in to Chrome, the user should be redirected to the NTP,
  // unless specified otherwise.
  if (redirect_url_.is_empty()) {
    RedirectToNtp(web_contents);
    return;
  }

  DCHECK(redirect_url_.is_valid());
  web_contents->GetController().LoadURL(redirect_url_, content::Referrer(),
                                        ui::PAGE_TRANSITION_AUTO_TOPLEVEL,
                                        std::string());
}

void ProcessDiceHeaderDelegateImpl::HandleTokenExchangeFailure(
    const std::string& email,
    const GoogleServiceAuthError& error) {
  DCHECK_NE(GoogleServiceAuthError::NONE, error.state());
  DiceTabHelper* tab_helper = GetDiceTabHelperFromWebContents(web_contents());
  if (tab_helper)
    tab_helper->OnSyncSigninFlowComplete();

  bool should_enable_sync = ShouldEnableSync();

  content::WebContents* web_contents = this->web_contents();
  if (should_enable_sync && web_contents)
    RedirectToNtp(web_contents);

  // Show the error even if the WebContents was closed, because the user may be
  // signed out of the web.
  std::move(show_signin_error_callback_)
      .Run(profile_, web_contents,
           SigninUIError::FromGoogleServiceAuthError(email, error));
}
