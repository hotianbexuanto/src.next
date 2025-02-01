// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SERVICES_METRICS_PUBLIC_CPP_UKM_RECORDER_H_
#define SERVICES_METRICS_PUBLIC_CPP_UKM_RECORDER_H_

#include "base/callback.h"
#include "base/feature_list.h"
#include "base/macros.h"
#include "base/threading/thread_checker.h"
#include "services/metrics/public/cpp/metrics_export.h"
#include "services/metrics/public/cpp/ukm_source.h"
#include "services/metrics/public/cpp/ukm_source_id.h"
#include "services/metrics/public/mojom/ukm_interface.mojom-forward.h"
#include "url/gurl.h"

<<<<<<< HEAD
class ChromePermissionsClient;
=======
>>>>>>> chromium
class PermissionUmaUtil;
class WebApkUkmRecorder;

namespace metrics {
class UkmRecorderInterface;
}  // namespace metrics

namespace content {
<<<<<<< HEAD
class BtmNavigationHandle;
class BtmServiceImpl;
class FedCmMetrics;
=======
>>>>>>> chromium
class PaymentAppProviderUtil;
class RenderFrameHostImpl;
}  // namespace content

namespace web_app {
class DesktopWebAppUkmRecorder;
}

namespace weblayer {
class BackgroundSyncDelegateImpl;
}

namespace ukm {

class DelegatingUkmRecorder;
class TestRecordingHelper;
class UkmBackgroundRecorderService;

enum class AppType {
  kArc,
  kPWA,
  kExtension,
  kChromeApp,
};

namespace internal {
class SourceUrlRecorderWebContentsObserver;
}  // namespace internal

// This feature controls whether UkmService should be created.
METRICS_EXPORT extern const base::Feature kUkmFeature;

// Interface for recording UKM
class METRICS_EXPORT UkmRecorder {
 public:
  UkmRecorder();
  virtual ~UkmRecorder();

  // Provides access to a global UkmRecorder instance for recording metrics.
  // This is typically passed to the Record() method of a entry object from
  // ukm_builders.h.
  // Use TestAutoSetUkmRecorder for capturing data written this way in tests.
  static UkmRecorder* Get();

  // Get the new source ID, which is unique for the duration of a browser
  // session.
  static SourceId GetNewSourceID();

<<<<<<< HEAD
  // Gets new source Id for PAYMENT_APP_ID type and updates the source URL to
  // the scope of the app. This method should only be called by
  // PaymentAppProviderUtil class when the payment app window is opened.
  static SourceId GetSourceIdForPaymentAppFromScope(
      base::PassKey<content::PaymentAppProviderUtil>,
      const GURL& payment_app_from_scope_url);

  // Gets a new SourceId for WEB_IDENTITY_ID type and updates the source URL
  // from the identity provider. This method should only be called in the
  // FedCmMetrics class.
  static SourceId GetSourceIdForWebIdentityFromScope(
      base::PassKey<content::FedCmMetrics>,
      const GURL& provider_url);

  // Gets a new SourceId of REDIRECT_ID type and updates the source URL
  // from the redirect chain. This method should only be called in the
  // BtmNavigationHandle class.
  static SourceId GetSourceIdForRedirectUrl(
      base::PassKey<content::BtmNavigationHandle>,
      const GURL& redirect_url);

  // Gets a new SourceId of EXTENSION_ID type and updates the source URL
  // from the extension message port. This method should only be called by
  // approved cases, indicated by the PassKeys.
  static SourceId GetSourceIdForExtensionUrl(
      base::PassKey<extensions::ExtensionMessagePort>,
      const GURL& extension_url);
  static SourceId GetSourceIdForExtensionUrl(
      base::PassKey<extensions::ManifestV2ExperimentManager>,
      const GURL& extension_url);

  // Gets a new SourceId of REDIRECT_ID type and updates the source URL to the
  // given domain. This method should only be called in the BtmServiceImpl
  // class for sites in the DIPS database. `site` must be a registrable domain.
  static SourceId GetSourceIdForDipsSite(base::PassKey<content::BtmServiceImpl>,
                                         const std::string& site);

  // Gets a new SourceId of CHROMEOS_WEBSITE_ID type. This should be only
  // used for recording ChromeOS website stats.
  static SourceId GetSourceIdForChromeOSWebsiteURL(
      base::PassKey<apps::WebsiteMetrics>,
      const GURL& chromeos_website_url);

  // Gets a new SourceId of NOTIFICATION_ID type. This should only be
  // used for recording Permission UKM events related to persistent and
  // nonpersistent notifications. `origin` is the domain that uses the Push API.
  static SourceId GetSourceIdForNotificationPermission(
      base::PassKey<ChromePermissionsClient>,
      const GURL& origin);

  // Gets a new SourceId of NOTIFICATION_ID type. This should only be used
  // for recording persistent and nonpersistent notification UKM events.
  static SourceId GetSourceIdForNotificationEvent(
      base::PassKey<PlatformNotificationServiceImpl>,
      const GURL& origin);

  // This method should be called when the system is about to shutdown, but
  // `UkmRecorder` is still available to record metrics.
  // Calls `OnStartingShutdown` on each observer from `observers_`.
  void NotifyStartShutdown();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

=======
>>>>>>> chromium
  // Add an entry to the UkmEntry list.
  virtual void AddEntry(mojom::UkmEntryPtr entry) = 0;

  // Disables sampling for testing purposes.
  virtual void DisableSamplingForTesting() {}

 protected:
  // Type-safe wrappers for Update<X> functions.
  void RecordOtherURL(ukm::SourceIdObj source_id, const GURL& url);
  void RecordAppURL(ukm::SourceIdObj source_id,
                    const GURL& url,
                    const AppType app_type);

  // Gets new source Id for WEBAPK_ID type and updates the manifest url. This
  // method should only be called by WebApkUkmRecorder class.
  static SourceId GetSourceIdForWebApkManifestUrl(const GURL& manifest_url);

  // Gets new source ID for a desktop web app, using the start_url from the web
  // app manifest. This method should only be called by DailyMetricsHelper.
  static SourceId GetSourceIdForDesktopWebAppStartUrl(const GURL& start_url);

  // Gets new source Id for PAYMENT_APP_ID type and updates the source url to
  // the scope of the app. This method should only be called by
  // PaymentAppProviderUtil class when the payment app window is opened.
  static SourceId GetSourceIdForPaymentAppFromScope(
      const GURL& service_worker_scope);

 private:
  friend weblayer::BackgroundSyncDelegateImpl;
  friend DelegatingUkmRecorder;
  friend TestRecordingHelper;
  friend UkmBackgroundRecorderService;
  friend metrics::UkmRecorderInterface;
  friend PermissionUmaUtil;
  friend content::PaymentAppProviderUtil;
  friend content::RenderFrameHostImpl;

  // WebApkUkmRecorder and DesktopWebAppUkmRecorder record metrics about
  // installed web apps. Instead of using
  // the current main frame URL, we want to record the URL which identifies the
  // current app: the web app manifest url or start url, respectively.
  // Therefore, they need to be friends so that they can access the private
  // GetSourceIdForWebApkManifestUrl() method.
  friend WebApkUkmRecorder;
  friend web_app::DesktopWebAppUkmRecorder;

  // Associates the SourceId with a URL. Most UKM recording code should prefer
  // to use a shared SourceId that is already associated with a URL, rather
  // than using this API directly. New uses of this API must be audited to
  // maintain privacy constraints.
  virtual void UpdateSourceURL(SourceId source_id, const GURL& url) = 0;

  // Associates the SourceId with an app URL for APP_ID sources. This method
  // should only be called by AppSourceUrlRecorder and DelegatingUkmRecorder.
  virtual void UpdateAppURL(SourceId source_id,
                            const GURL& url,
                            const AppType app_type) = 0;

  // Associates navigation data with the UkmSource keyed by |source_id|. This
  // should only be called by SourceUrlRecorderWebContentsObserver, for
  // navigation sources.
  virtual void RecordNavigation(
      SourceId source_id,
      const UkmSource::NavigationData& navigation_data) = 0;

  // Marks a source as no longer needed to kept alive in memory. Called by
  // SourceUrlRecorderWebContentsObserver when a browser tab or its WebContents
  // are no longer alive. Not to be used through mojo interface.
  virtual void MarkSourceForDeletion(ukm::SourceId source_id) = 0;

  DISALLOW_COPY_AND_ASSIGN(UkmRecorder);
};

}  // namespace ukm

#endif  // SERVICES_METRICS_PUBLIC_CPP_UKM_RECORDER_H_
