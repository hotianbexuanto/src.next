// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/intent_picker_tab_helper.h"

#include <utility>

#include "base/bind.h"
#include "chrome/browser/apps/app_service/app_service_proxy.h"
#include "chrome/browser/apps/app_service/app_service_proxy_factory.h"
#include "chrome/browser/apps/intent_helper/intent_picker_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_window.h"
<<<<<<< HEAD
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/page_action/page_action_icon_type.h"
#include "chrome/browser/ui/web_applications/web_app_launch_utils.h"
#include "chrome/browser/web_applications/proto/web_app_install_state.pb.h"
#include "chrome/browser/web_applications/web_app_provider.h"
#include "chrome/browser/web_applications/web_app_utils.h"
#include "components/password_manager/content/common/web_ui_constants.h"
#include "components/services/app_service/public/cpp/app_types.h"
#include "components/services/app_service/public/cpp/icon_types.h"
=======
#include "chrome/common/chrome_features.h"
>>>>>>> chromium
#include "content/public/browser/navigation_handle.h"
#include "ui/base/models/image_model.h"
#include "ui/gfx/favicon_size.h"
#include "ui/gfx/image/image.h"

namespace {

apps::mojom::AppType GetAppType(apps::PickerEntryType picker_entry_type) {
  apps::mojom::AppType app_type = apps::mojom::AppType::kUnknown;
  switch (picker_entry_type) {
    case apps::PickerEntryType::kUnknown:
    case apps::PickerEntryType::kDevice:
      break;
    case apps::PickerEntryType::kArc:
      app_type = apps::mojom::AppType::kArc;
      break;
    case apps::PickerEntryType::kWeb:
      app_type = apps::mojom::AppType::kWeb;
      break;
    case apps::PickerEntryType::kMacOs:
      app_type = apps::mojom::AppType::kMacOs;
      break;
  }
<<<<<<< HEAD

  Browser* browser = chrome::FindBrowserWithTab(web_contents);
  if (browser && (browser->is_type_app() || browser->is_type_app_popup())) {
    return false;
  }
  return true;
}

bool IsValidIntentPickerUrl(const GURL& url, bool is_error_page) {
  if (url.SchemeIsHTTPOrHTTPS() && !is_error_page) {
    return true;
  }

  // chrome://password-manager is a valid PWA, so it should be considered when
  // evaluating whether to show the intent picker.
  if (url.SchemeIs(content::kChromeUIScheme) &&
      url.host() == password_manager::kChromeUIPasswordManagerHost) {
    return true;
  }

  return false;
}

void ShowIntentPickerBubbleForApps(
    content::WebContents* web_contents,
    bool show_stay_in_chrome,
    bool show_remember_selection,
    IntentPickerResponse callback,
    std::vector<apps::IntentPickerAppInfo> apps) {
  if (apps.empty()) {
    return;
  }

  Browser* browser = chrome::FindBrowserWithTab(web_contents);
  if (!browser) {
    return;
  }

  browser->window()->ShowIntentPickerBubble(
      std::move(apps), show_stay_in_chrome, show_remember_selection,
      apps::IntentPickerBubbleType::kLinkCapturing, std::nullopt,
      std::move(callback));
}

bool IsShuttingDown(content::WebContents* web_contents) {
  return !web_contents || web_contents->IsBeingDestroyed() ||
         web_contents->GetBrowserContext()->ShutdownStarted();
=======
  return app_type;
>>>>>>> chromium
}

}  // namespace

IntentPickerTabHelper::~IntentPickerTabHelper() = default;

<<<<<<< HEAD
void IntentPickerTabHelper::MaybeShowIntentPickerIcon() {
  // Setting icon_resolved_ to false ensures testing callbacks can accurately
  // wait for the entire async process to finish.
  icon_resolved_ = false;
  CHECK(web_contents());
  if (!intent_picker_delegate_->ShouldShowIntentPickerWithApps() ||
      !IsValidWebContentsForIntentPicker(web_contents())) {
    MaybeShowIconForApps({});
    return;
  }

  intent_picker_delegate_->FindAllAppsForUrl(
      web_contents()->GetLastCommittedURL(), GetIntentPickerBubbleIconSize(),
      base::BindOnce(&IntentPickerTabHelper::MaybeShowIconForApps,
                     per_navigation_weak_factory_.GetWeakPtr()));
}

void IntentPickerTabHelper::ShowIntentPickerBubbleOrLaunchApp(const GURL& url) {
  CHECK(web_contents());
  if (!intent_picker_delegate_->ShouldShowIntentPickerWithApps() ||
      !IsValidWebContentsForIntentPicker(web_contents())) {
    return;
  }

  intent_picker_delegate_->FindAllAppsForUrl(
      url, GetIntentPickerBubbleIconSize(),
      base::BindOnce(&IntentPickerTabHelper::ShowIntentPickerOrLaunchAppImpl,
                     per_navigation_weak_factory_.GetWeakPtr(), url));
}

=======
>>>>>>> chromium
// static
void IntentPickerTabHelper::SetShouldShowIcon(
    content::WebContents* web_contents,
    bool should_show_icon) {
  IntentPickerTabHelper* tab_helper = FromWebContents(web_contents);
  if (!tab_helper) {
    return;
<<<<<<< HEAD
  }

  if (apps::features::ShouldShowLinkCapturingUX()) {
    tab_helper->current_app_icon_ = ui::ImageModel();
    tab_helper->show_expanded_chip_from_usage_ = false;
    tab_helper->current_app_id_ = std::string();
    tab_helper->current_app_is_preferred_ = false;
    tab_helper->last_shown_origin_ = url::Origin();
  }

  tab_helper->ShowOrHideIconInternal(should_show_icon);
}

// static
int IntentPickerTabHelper::GetIntentPickerBubbleIconSize() {
  const int kIntentPickerUiUpdateIconSize = 40;
  return apps::features::ShouldShowLinkCapturingUX()
             ? kIntentPickerUiUpdateIconSize
             : gfx::kFaviconSize;
}

void IntentPickerTabHelper::MaybeShowIconForApps(
    std::vector<apps::IntentPickerAppInfo> apps) {
  // We enter this block when we have apps available and there weren't any
  // previously.
  if (!should_show_icon_ && !apps.empty()) {
    // This point doesn't exactly match when the icon is shown in the UI (e.g.
    // if the tab is not active), but recording here corresponds more closely to
    // navigations which cause the icon to appear.
    intent_picker_delegate_->RecordIntentPickerIconEvent(
        apps::IntentPickerIconEvent::kIconShown);

#if BUILDFLAG(IS_CHROMEOS)
    apps::IntentHandlingMetrics::RecordLinkCapturingEntryPointShown(apps);
#endif  // BUILDFLAG(IS_CHROMEOS)
  }

  if (apps::features::ShouldShowLinkCapturingUX()) {
    if (apps.size() == 1 && apps[0].launch_name != current_app_id_) {
      current_app_id_ = apps[0].launch_name;

      // If this app is the preferred app to handle this URL, the icon will
      // always be shown as expanded, regardless of the usage-based decision
      // calculated in UpdateExpandedState().
      current_app_is_preferred_ =
          intent_picker_delegate_->IsPreferredAppForSupportedLinks(
              current_app_id_);

      intent_picker_delegate_->LoadSingleAppIcon(
          apps[0].type, current_app_id_,
          GetLayoutConstant(LOCATION_BAR_ICON_SIZE),
          base::BindOnce(&IntentPickerTabHelper::OnAppIconLoadedForChip,
                         per_navigation_weak_factory_.GetWeakPtr(),
                         current_app_id_));
      return;
    } else if (apps.size() != 1) {
      current_app_icon_ = ui::ImageModel();
      current_app_id_ = std::string();
      current_app_is_preferred_ = false;
    }
  }

  ShowIconForLinkIntent(!apps.empty());
=======
  tab_helper->should_show_icon_ = should_show_icon;
  Browser* browser = chrome::FindBrowserWithWebContents(web_contents);
  if (!browser)
    return;
  browser->window()->UpdatePageActionIcon(PageActionIconType::kIntentPicker);
>>>>>>> chromium
}

IntentPickerTabHelper::IntentPickerTabHelper(content::WebContents* web_contents)
    : content::WebContentsObserver(web_contents) {}

// static
void IntentPickerTabHelper::LoadAppIcons(
    content::WebContents* web_contents,
    std::vector<apps::IntentPickerAppInfo> apps,
    IntentPickerIconLoaderCallback callback) {
  IntentPickerTabHelper* tab_helper = FromWebContents(web_contents);
  if (!tab_helper) {
    std::move(callback).Run(std::move(apps));
    return;
  }
  tab_helper->LoadAppIcon(std::move(apps), std::move(callback), 0);
}

void IntentPickerTabHelper::OnAppIconLoaded(
    std::vector<apps::IntentPickerAppInfo> apps,
    IntentPickerIconLoaderCallback callback,
    size_t index,
    apps::mojom::IconValuePtr icon_value) {
  apps[index].icon_model =
      ui::ImageModel::FromImage(gfx::Image(icon_value->uncompressed));

  if (index == apps.size() - 1) {
    std::move(callback).Run(std::move(apps));
<<<<<<< HEAD
  } else {
    LoadAppIcon(std::move(apps), index + 1, std::move(callback));
  }
=======
  else
    LoadAppIcon(std::move(apps), std::move(callback), index + 1);
>>>>>>> chromium
}

void IntentPickerTabHelper::LoadAppIcon(
    std::vector<apps::IntentPickerAppInfo> apps,
    IntentPickerIconLoaderCallback callback,
    size_t index) {
  if (index >= apps.size()) {
    std::move(callback).Run(std::move(apps));
    return;
  }

  const std::string& app_id = apps[index].launch_name;
  auto app_type = GetAppType(apps[index].type);

  Profile* profile =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext());

  constexpr bool allow_placeholder_icon = false;
  auto icon_type =
      (base::FeatureList::IsEnabled(features::kAppServiceAdaptiveIcon))
          ? apps::mojom::IconType::kStandard
          : apps::mojom::IconType::kUncompressed;
  apps::AppServiceProxyFactory::GetForProfile(profile)->LoadIcon(
      app_type, app_id, icon_type, gfx::kFaviconSize, allow_placeholder_icon,
      base::BindOnce(&IntentPickerTabHelper::OnAppIconLoaded,
                     weak_factory_.GetWeakPtr(), std::move(apps),
                     std::move(callback), index));
}

void IntentPickerTabHelper::DidFinishNavigation(
    content::NavigationHandle* navigation_handle) {
  // For a http/https scheme URL navigation, we will check if the
  // url can be handled by some apps, and show intent picker icon
  // or bubble if there are some apps available. We only want to check this if
<<<<<<< HEAD
  // the navigation happens in the primary main frame, and the navigation is not
  // the same document with same URL.
  if (!web_contents()) {
    return;
  }

  if (IsNavigatingToNewSite(navigation_handle)) {
    per_navigation_weak_factory_.InvalidateWeakPtrs();

    if (IsValidIntentPickerUrl(navigation_handle->GetURL(),
                               navigation_handle->IsErrorPage())) {
      MaybeShowIntentPickerIcon();
    } else {
      ShowOrHideIcon(web_contents(), /*should_show_icon=*/false);
    }
  }
}

void IntentPickerTabHelper::OnWebAppWillBeUninstalled(
    const webapps::AppId& app_id) {
  // WebAppTabHelper has an app_id but it is reset during
  // OnWebAppWillBeUninstalled so using FindAppWithUrlInScope.
  std::optional<webapps::AppId> local_app_id =
      registrar_->FindBestAppWithUrlInScope(
          web_contents()->GetLastCommittedURL(),
          web_app::WebAppFilter::InstalledInChrome());
  if (app_id == local_app_id) {
    ShowOrHideIcon(web_contents(), /*should_show_icon=*/false);
  }
}

void IntentPickerTabHelper::OnWebAppInstallManagerDestroyed() {
  install_manager_observation_.Reset();
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(IntentPickerTabHelper);
=======
  // the navigation happens in the main frame, and the navigation is not the
  // same document with same URL.
  // TODO(crbug.com/826982): Check is not error page here. Adding this check
  // will break the browser test, given this is a refactor CL, will add check in
  // follow up CL.
  // TODO(https://crbug.com/1218946): With MPArch there may be multiple main
  // frames. This caller was converted automatically to the primary main frame
  // to preserve its semantics. Follow up to confirm correctness.
  if (navigation_handle->IsInPrimaryMainFrame() &&
      navigation_handle->HasCommitted() &&
      (!navigation_handle->IsSameDocument() ||
       navigation_handle->GetURL() !=
           navigation_handle->GetPreviousMainFrameURL()) &&
      navigation_handle->GetURL().SchemeIsHTTPOrHTTPS()) {
    apps::MaybeShowIntentPicker(navigation_handle);
  }
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(IntentPickerTabHelper)
>>>>>>> chromium
