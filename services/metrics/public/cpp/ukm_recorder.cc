// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "services/metrics/public/cpp/ukm_recorder.h"

#include "base/bind.h"
#include "base/feature_list.h"
#include "build/build_config.h"
#include "services/metrics/public/cpp/delegating_ukm_recorder.h"
#include "services/metrics/public/cpp/ukm_entry_builder.h"
#include "services/metrics/public/cpp/ukm_source_id.h"

namespace ukm {

const base::Feature kUkmFeature = {"Ukm", base::FEATURE_ENABLED_BY_DEFAULT};

UkmRecorder::UkmRecorder() = default;

UkmRecorder::~UkmRecorder() = default;

// static
UkmRecorder* UkmRecorder::Get() {
  // Note that SourceUrlRecorderWebContentsObserver assumes that
  // DelegatingUkmRecorder::Get() is the canonical UkmRecorder instance. If this
  // changes, SourceUrlRecorderWebContentsObserver should be updated to match.
  return DelegatingUkmRecorder::Get();
}

// static
ukm::SourceId UkmRecorder::GetNewSourceID() {
  return AssignNewSourceId();
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForPaymentAppFromScope(
    base::PassKey<content::PaymentAppProviderUtil>,
    const GURL& service_worker_scope) {
  return UkmRecorder::GetSourceIdFromScopeImpl(service_worker_scope,
                                               SourceIdType::PAYMENT_APP_ID);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForWebApkManifestUrl(
    base::PassKey<WebApkUkmRecorder>,
    const GURL& manifest_url) {
  return UkmRecorder::GetSourceIdFromScopeImpl(manifest_url,
                                               SourceIdType::WEBAPK_ID);
}

// static
<<<<<<< HEAD
ukm::SourceId UkmRecorder::GetSourceIdForRedirectUrl(
    base::PassKey<content::BtmNavigationHandle>,
    const GURL& redirect_url) {
  return UkmRecorder::GetSourceIdFromScopeImpl(redirect_url,
                                               SourceIdType::REDIRECT_ID);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForDipsSite(
    base::PassKey<content::BtmServiceImpl>,
    const std::string& site) {
  // Use REDIRECT_ID because DIPS sites are bounce trackers that redirected the
  // user (see go/dips). This method is used for background reporting of such
  // sites, so there's no RenderFrameHost to get a SourceId from, or even a full
  // URL to report on -- only the eTLD+1 stored by the DIPS Service.
  DCHECK(net::IsCanonicalizedHostCompliant(site)) << "Invalid site: " << site;
  return UkmRecorder::GetSourceIdFromScopeImpl(GURL("http://" + site),
                                               SourceIdType::REDIRECT_ID);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForChromeOSWebsiteURL(
    base::PassKey<apps::WebsiteMetrics>,
    const GURL& redirect_url) {
  return UkmRecorder::GetSourceIdFromScopeImpl(
      redirect_url, SourceIdType::CHROMEOS_WEBSITE_ID);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForExtensionUrl(
    base::PassKey<extensions::ExtensionMessagePort>,
    const GURL& extension_url) {
  // UkmRecorderImpl will verify the extension URL (and the corresponding
  // extension) prior to emitting the record.
  return UkmRecorder::GetSourceIdFromScopeImpl(extension_url,
                                               SourceIdType::EXTENSION_ID);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForExtensionUrl(
    base::PassKey<extensions::ManifestV2ExperimentManager>,
    const GURL& extension_url) {
  // UkmRecorderImpl will verify the extension URL (and the corresponding
  // extension) prior to emitting the record.
  return UkmRecorder::GetSourceIdFromScopeImpl(extension_url,
                                               SourceIdType::EXTENSION_ID);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForNotificationPermission(
    base::PassKey<ChromePermissionsClient>,
    const GURL& origin) {
  return UkmRecorder::GetSourceIdFromScopeImpl(origin,
                                               SourceIdType::NOTIFICATION_ID);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdForNotificationEvent(
    base::PassKey<PlatformNotificationServiceImpl>,
    const GURL& origin) {
  return UkmRecorder::GetSourceIdFromScopeImpl(origin,
                                               SourceIdType::NOTIFICATION_ID);
=======
ukm::SourceId UkmRecorder::GetSourceIdForDesktopWebAppStartUrl(
    base::PassKey<web_app::DesktopWebAppUkmRecorder>,
    const GURL& start_url) {
  ukm::SourceId source_id =
      ukm::SourceIdObj::FromOtherId(GetNewSourceID(),
                                    SourceIdType::DESKTOP_WEB_APP_ID)
          .ToInt64();
  ukm::UkmRecorder* ukm_recorder = ukm::UkmRecorder::Get();
  ukm_recorder->UpdateSourceURL(source_id, start_url);
  return source_id;
>>>>>>> chromium
}

void UkmRecorder::RecordOtherURL(ukm::SourceIdObj source_id, const GURL& url) {
  UpdateSourceURL(source_id.ToInt64(), url);
}

void UkmRecorder::RecordAppURL(ukm::SourceIdObj source_id,
                               const GURL& url,
                               const AppType app_type) {
  UpdateAppURL(source_id.ToInt64(), url, app_type);
}

// static
ukm::SourceId UkmRecorder::GetSourceIdFromScopeImpl(const GURL& scope_url,
                                                    SourceIdType type) {
  SourceId source_id =
      SourceIdObj::FromOtherId(GetNewSourceID(), type).ToInt64();
  UkmRecorder::Get()->UpdateSourceURL(source_id, scope_url);
  return source_id;
}

}  // namespace ukm
