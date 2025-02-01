// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/signin/dice_tab_helper.h"

#include "base/check_op.h"
#include "base/metrics/user_metrics.h"
#include "chrome/browser/signin/dice_tab_helper.h"
#include "chrome/browser/signin/signin_util.h"
#include "chrome/browser/ui/browser_finder.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/browser/navigation_handle.h"
<<<<<<< HEAD
#include "google_apis/gaia/gaia_auth_util.h"

// static
DiceTabHelper::EnableSyncCallback
DiceTabHelper::GetEnableSyncCallbackForBrowser() {
  return base::BindRepeating([](Profile* profile,
                                signin_metrics::AccessPoint access_point,
                                signin_metrics::PromoAction promo_action,
                                content::WebContents* web_contents,
                                const CoreAccountInfo& account_info) {
    DCHECK(profile);
    Browser* browser = web_contents ? chrome::FindBrowserWithTab(web_contents)
                                    : chrome::FindBrowserWithProfile(profile);
    if (!browser) {
      return;
    }

    bool is_sync_promo =
        access_point ==
        signin_metrics::AccessPoint::kAvatarBubbleSignInWithSyncPromo;
    if (switches::IsImprovedSettingsUIOnDesktopEnabled()) {
      is_sync_promo = is_sync_promo ||
                      access_point == signin_metrics::AccessPoint::kSettings;
    }
    TurnSyncOnHelper::SigninAbortedMode abort_mode =
        is_sync_promo ? TurnSyncOnHelper::SigninAbortedMode::KEEP_ACCOUNT
                      : TurnSyncOnHelper::SigninAbortedMode::REMOVE_ACCOUNT;

    // TurnSyncOnHelper is suicidal (it will kill itself once it
    // finishes enabling sync).
    new TurnSyncOnHelper(profile, browser, access_point, promo_action,
                         account_info.account_id, abort_mode, is_sync_promo);
  });
}

// static
DiceTabHelper::ShowSigninErrorCallback
DiceTabHelper::GetShowSigninErrorCallbackForBrowser() {
  return base::BindRepeating([](Profile* profile,
                                content::WebContents* web_contents,
                                const SigninUIError& error) {
    if (!profile) {
      return;
    }
    Browser* browser = web_contents ? chrome::FindBrowserWithTab(web_contents)
                                    : chrome::FindBrowserWithProfile(profile);
    if (!browser) {
      return;
    }
    LoginUIServiceFactory::GetForProfile(profile)->DisplayLoginResult(
        browser, error, /*from_profile_picker=*/false);
  });
}

DiceTabHelper::ResetableState::ResetableState() = default;
DiceTabHelper::ResetableState::~ResetableState() = default;
DiceTabHelper::ResetableState::ResetableState(ResetableState&& other) = default;
DiceTabHelper::ResetableState& DiceTabHelper::ResetableState::operator=(
    ResetableState&& other) = default;
=======
#include "google_apis/gaia/gaia_urls.h"
>>>>>>> chromium

DiceTabHelper::DiceTabHelper(content::WebContents* web_contents)
    : content::WebContentsObserver(web_contents) {}

DiceTabHelper::~DiceTabHelper() = default;

void DiceTabHelper::InitializeSigninFlow(
    const GURL& signin_url,
    signin_metrics::AccessPoint access_point,
    signin_metrics::Reason reason,
    signin_metrics::PromoAction promo_action,
    const GURL& redirect_url) {
  DCHECK(signin_url.is_valid());
  DCHECK(signin_url_.is_empty() || signin_url_ == signin_url);

  signin_url_ = signin_url;
  signin_access_point_ = access_point;
  signin_reason_ = reason;
  signin_promo_action_ = promo_action;
  is_chrome_signin_page_ = true;
  signin_page_load_recorded_ = false;
  redirect_url_ = redirect_url;
  sync_signin_flow_status_ = SyncSigninFlowStatus::kNotStarted;

  if (reason == signin_metrics::Reason::kSigninPrimaryAccount) {
    sync_signin_flow_status_ = SyncSigninFlowStatus::kStarted;
    signin_metrics::LogSigninAccessPointStarted(access_point, promo_action);
    signin_metrics::RecordSigninUserActionForAccessPoint(access_point,
                                                         promo_action);
    base::RecordAction(base::UserMetricsAction("Signin_SigninPage_Loading"));
  }
<<<<<<< HEAD

  if (signin_util::IsSigninPending(identity_manager)) {
    base::UmaHistogramEnumeration(
        "Signin.SigninPending.ResolutionSourceStarted", access_point);
  }
=======
>>>>>>> chromium
}

bool DiceTabHelper::IsChromeSigninPage() const {
  return is_chrome_signin_page_;
}

bool DiceTabHelper::IsSyncSigninInProgress() const {
  return sync_signin_flow_status_ == SyncSigninFlowStatus::kStarted;
}

void DiceTabHelper::OnSyncSigninFlowComplete() {
  // The flow is complete, reset to initial state.
  sync_signin_flow_status_ = SyncSigninFlowStatus::kNotStarted;
}

void DiceTabHelper::DidStartNavigation(
    content::NavigationHandle* navigation_handle) {
  if (!is_chrome_signin_page_)
    return;

  // Ignore internal navigations.
  // TODO(https://crbug.com/1218946): With MPArch there may be multiple main
  // frames. This caller was converted automatically to the primary main frame
  // to preserve its semantics. Follow up to confirm correctness.
  if (!navigation_handle->IsInPrimaryMainFrame() ||
      navigation_handle->IsSameDocument()) {
    return;
  }

  if (!IsSigninPageNavigation(navigation_handle)) {
    // Navigating away from the signin page.
    is_chrome_signin_page_ = false;
  }
}

void DiceTabHelper::DidFinishNavigation(
    content::NavigationHandle* navigation_handle) {
  if (!is_chrome_signin_page_)
    return;

  // Ignore internal navigations.
  // TODO(https://crbug.com/1218946): With MPArch there may be multiple main
  // frames. This caller was converted automatically to the primary main frame
  // to preserve its semantics. Follow up to confirm correctness.
  if (!navigation_handle->IsInPrimaryMainFrame() ||
      navigation_handle->IsSameDocument()) {
    return;
  }

  if (!IsSigninPageNavigation(navigation_handle)) {
    // Navigating away from the signin page.
    is_chrome_signin_page_ = false;
    return;
  }

  if (!signin_page_load_recorded_) {
    signin_page_load_recorded_ = true;
    base::RecordAction(base::UserMetricsAction("Signin_SigninPage_Shown"));
  }
}

bool DiceTabHelper::IsSigninPageNavigation(
    content::NavigationHandle* navigation_handle) const {
  return !navigation_handle->IsErrorPage() &&
         navigation_handle->GetRedirectChain()[0] == signin_url_ &&
         navigation_handle->GetURL().GetOrigin() ==
             GaiaUrls::GetInstance()->gaia_url();
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(DiceTabHelper)
