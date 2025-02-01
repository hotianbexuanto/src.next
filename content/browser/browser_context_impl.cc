// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/browser_context_impl.h"

#include <utility>

<<<<<<< HEAD
#include "base/check_is_test.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/location.h"
=======
#include "base/debug/dump_without_crashing.h"
>>>>>>> chromium
#include "base/memory/ref_counted.h"
#include "base/trace_event/trace_event.h"
#include "build/build_config.h"
#include "components/content_settings/core/common/features.h"
#include "content/browser/background_sync/background_sync_scheduler.h"
#include "content/browser/browsing_data/browsing_data_remover_impl.h"
#include "content/browser/dips/dips_service_impl.h"
#include "content/browser/download/download_manager_impl.h"
#include "content/browser/permissions/permission_controller_impl.h"
#include "content/browser/speech/tts_controller_impl.h"
#include "content/browser/storage_partition_impl_map.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
<<<<<<< HEAD
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/shared_worker_service.h"
#include "content/public/common/content_client.h"
#include "media/capabilities/webrtc_video_stats_db_impl.h"
=======
>>>>>>> chromium
#include "media/learning/common/media_learning_tasks.h"
#include "media/learning/impl/learning_session_impl.h"
#include "media/mojo/services/video_decode_perf_history.h"

#if BUILDFLAG(IS_CHROMEOS)
#include "storage/browser/file_system/external_mount_points.h"
#endif

namespace content {

namespace {

void ShutdownServiceWorkerContext(StoragePartition* partition) {
  ServiceWorkerContextWrapper* wrapper =
      static_cast<ServiceWorkerContextWrapper*>(
          partition->GetServiceWorkerContext());
  wrapper->process_manager()->Shutdown();
}

void ShutdownSharedWorkerContext(StoragePartition* partition) {
  partition->GetSharedWorkerService()->Shutdown();
}

void RegisterMediaLearningTask(
    media::learning::LearningSessionImpl* learning_session,
    const media::learning::LearningTask& task) {
  // The RegisterTask method cannot be directly used in base::Bind, because it
  // provides a default argument value for the 2nd parameter
  // (`feature_provider`).
  learning_session->RegisterTask(task);
}

}  // namespace

<<<<<<< HEAD
// static
BrowserContextImpl* BrowserContextImpl::From(BrowserContext* self) {
  return self->impl();
}

void BrowserContextImpl::MaybeCleanupDips() {
  base::ScopedClosureRunner quit_runner(dips_cleanup_loop_.QuitClosure());
  // Don't attempt to delete the database if the DIPS feature is enabled; we
  // need it.
  if (base::FeatureList::IsEnabled(features::kBtm)) {
    return;
  }

  // Don't attempt to delete the database if this browser context should never
  // have DIPS enabled. (This is important for embedders like ChromeOS, which
  // have internal non-user-facing browser contexts. We don't want to touch
  // them.)
  if (!GetContentClient()->browser()->ShouldEnableDips(self_)) {
    return;
  }

  // Don't attempt to delete the database if this browser context doesn't write
  // to disk. (This is important for embedders like Chrome, which can make OTR
  // browser contexts share the same data directory as a non-OTR context.)
  if (self_->IsOffTheRecord()) {
    return;
  }

  BtmStorage::DeleteDatabaseFiles(GetBtmFilePath(self_), quit_runner.Release());
}

void BrowserContextImpl::WaitForDipsCleanupForTesting() {
  dips_cleanup_loop_.Run();
}

BrowserContextImpl::BrowserContextImpl(BrowserContext* self) : self_(self) {
=======
BrowserContext::Impl::Impl(BrowserContext* self) : self_(self) {
>>>>>>> chromium
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  background_sync_scheduler_ = base::MakeRefCounted<BackgroundSyncScheduler>();

  // Run MaybeCleanupDips() very soon. We can't call it right now because it
  // calls a virtual function (BrowserContext::IsOffTheRecord()), which causes
  // undefined behavior since we're called by the BrowserContext constructor
  // and the method is not implemented by that class.
  base::SequencedTaskRunner::GetCurrentDefault()->PostTask(
      FROM_HERE, base::BindOnce(&BrowserContextImpl::MaybeCleanupDips,
                                weak_factory_.GetWeakPtr()));
}

BrowserContext::Impl::~Impl() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  DCHECK(!storage_partition_map_)
      << "StoragePartitionMap is not shut down properly";

  if (!will_be_destroyed_soon_) {
    NOTREACHED();
    base::debug::DumpWithoutCrashing();
  }

  // Verify that there are no outstanding RenderProcessHosts that reference
  // this context. Trigger a crash report if there are still references so
  // we can detect/diagnose potential UAFs.
  std::string rph_crash_key_value;
  ChildProcessSecurityPolicyImpl* policy =
      ChildProcessSecurityPolicyImpl::GetInstance();
  for (RenderProcessHost::iterator host_iterator =
           RenderProcessHost::AllHostsIterator();
       !host_iterator.IsAtEnd(); host_iterator.Advance()) {
    RenderProcessHost* host = host_iterator.GetCurrentValue();
    if (host->GetBrowserContext() == self_) {
      rph_crash_key_value +=
          "{ " + host->GetInfoForBrowserContextDestructionCrashReporting() +
          " }";
    }
  }
  if (!rph_crash_key_value.empty()) {
    NOTREACHED() << "rph_with_bc_reference : " << rph_crash_key_value;

    SCOPED_CRASH_KEY_STRING256("BrowserContext", "dangling_rph",
                               rph_crash_key_value);
    base::debug::DumpWithoutCrashing();
  }

  // Clean up any isolated origins and other security state associated with this
  // BrowserContext.
  policy->RemoveStateForBrowserContext(*self_);

  if (download_manager_)
    download_manager_->Shutdown();

  TtsControllerImpl::GetInstance()->OnBrowserContextDestroyed(self_);

  TRACE_EVENT_NESTABLE_ASYNC_END1(
      "shutdown", "BrowserContext::Impl::NotifyWillBeDestroyed() called.", this,
      "browser_context_impl", static_cast<void*>(this));
}

bool BrowserContext::Impl::ShutdownStarted() {
  return will_be_destroyed_soon_;
}

void BrowserContext::Impl::NotifyWillBeDestroyed() {
  TRACE_EVENT1("shutdown", "BrowserContext::Impl::NotifyWillBeDestroyed",
               "browser_context_impl", static_cast<void*>(this));
  TRACE_EVENT_NESTABLE_ASYNC_BEGIN1(
      "shutdown", "BrowserContext::Impl::NotifyWillBeDestroyed() called.", this,
      "browser_context_impl", static_cast<void*>(this));
  // Make sure NotifyWillBeDestroyed is idempotent.  This helps facilitate the
  // pattern where NotifyWillBeDestroyed is called from *both*
  // ShellBrowserContext and its derived classes (e.g. WebTestBrowserContext).
  if (will_be_destroyed_soon_)
    return;
  will_be_destroyed_soon_ = true;

  // Shut down service worker and shared worker machinery because these can keep
  // RenderProcessHosts and SiteInstances alive, and the codebase assumes these
  // are destroyed before the BrowserContext is destroyed.
  self_->ForEachStoragePartition(
      base::BindRepeating(ShutdownServiceWorkerContext));
  self_->ForEachStoragePartition(
      base::BindRepeating(ShutdownSharedWorkerContext));

  // Also forcibly release keep alive refcounts on RenderProcessHosts, to ensure
  // they destruct before the BrowserContext does.
  for (RenderProcessHost::iterator host_iterator =
           RenderProcessHost::AllHostsIterator();
       !host_iterator.IsAtEnd(); host_iterator.Advance()) {
    RenderProcessHost* host = host_iterator.GetCurrentValue();
    if (host->GetBrowserContext() == self_) {
      // This will also clean up spare RPH references.
      host->DisableKeepAliveRefCount();
    }
  }
}

StoragePartitionImplMap*
BrowserContext::Impl::GetOrCreateStoragePartitionMap() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (!storage_partition_map_)
    storage_partition_map_ = std::make_unique<StoragePartitionImplMap>(self_);

  return storage_partition_map_.get();
}

BrowsingDataRemover* BrowserContext::Impl::GetBrowsingDataRemover() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (!browsing_data_remover_) {
    browsing_data_remover_ = std::make_unique<BrowsingDataRemoverImpl>(self_);
    browsing_data_remover_->SetEmbedderDelegate(
        self_->GetBrowsingDataRemoverDelegate());
  }

  return browsing_data_remover_.get();
}

media::learning::LearningSession* BrowserContext::Impl::GetLearningSession() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (!learning_session_) {
    learning_session_ = std::make_unique<media::learning::LearningSessionImpl>(
        base::SequencedTaskRunnerHandle::Get());

    // Using base::Unretained is safe below, because the callback here will not
    // be called or retained after the Register method below returns.
    media::learning::MediaLearningTasks::Register(base::BindRepeating(
        &RegisterMediaLearningTask, base::Unretained(learning_session_.get())));
  }

  return learning_session_.get();
}

media::VideoDecodePerfHistory*
BrowserContext::Impl::GetVideoDecodePerfHistory() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (!video_decode_perf_history_)
    video_decode_perf_history_ = self_->CreateVideoDecodePerfHistory();

  return video_decode_perf_history_.get();
}

void BrowserContext::Impl::ShutdownStoragePartitions() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  // The BackgroundSyncScheduler keeps raw pointers to partitions; clear it
  // first.
  DCHECK(background_sync_scheduler_->HasOneRef());
  background_sync_scheduler_.reset();

  storage_partition_map_.reset();

  // Delete the BtmService, causing its SQLite database file to be closed. This
  // is necessary for TestBrowserContext to be able to delete its temporary
  // directory.
  dips_service_.reset();
}

DownloadManager* BrowserContext::Impl::GetDownloadManager() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  // Lazily populate `download_manager_`.  This is important to
  // 1) Avoid constructing DownloadManagerImpl when a test might have provided
  //    an alternative object via SetDownloadManagerForTesting.
  // 2) Avoiding calling into DownloadManagerImpl's constructor with a partially
  //    constructed BrowserContext.
  if (!download_manager_) {
    download_manager_ = std::make_unique<DownloadManagerImpl>(self_);

    // Note that GetDownloadManagerDelegate might call into GetDownloadManager,
    // leading to re-entrancy concerns.  We avoid re-entrancy by making sure
    // `download_manager_` is set earlier, above.
    download_manager_->SetDelegate(self_->GetDownloadManagerDelegate());
  }

  return download_manager_.get();
}

void BrowserContext::Impl::SetDownloadManagerForTesting(
    std::unique_ptr<DownloadManager> download_manager) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  download_manager_ = std::move(download_manager);
}

PermissionController* BrowserContext::Impl::GetPermissionController() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (!permission_controller_)
    permission_controller_ = std::make_unique<PermissionControllerImpl>(self_);

  return permission_controller_.get();
}

void BrowserContext::Impl::SetPermissionControllerForTesting(
    std::unique_ptr<PermissionController> permission_controller) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  permission_controller_ = std::move(permission_controller);
}

storage::ExternalMountPoints* BrowserContext::Impl::GetMountPoints() {
  // Ensure that these methods are called on the UI thread, except for
  // unittests where a UI thread might not have been created.
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI) ||
         !BrowserThread::IsThreadInitialized(BrowserThread::UI));

#if BUILDFLAG(IS_CHROMEOS)
  if (!external_mount_points_)
    external_mount_points_ = storage::ExternalMountPoints::CreateRefCounted();
  return external_mount_points_.get();
#else
  return nullptr;
#endif
}

<<<<<<< HEAD
PrefetchService* BrowserContextImpl::GetPrefetchService() {
  if (!prefetch_service_) {
    prefetch_service_ = std::make_unique<PrefetchService>(self_);
  }

  return prefetch_service_.get();
}

InMemoryFederatedPermissionContext*
BrowserContextImpl::GetFederatedPermissionContext() {
  if (!federated_permission_context_) {
    federated_permission_context_ =
        std::make_unique<InMemoryFederatedPermissionContext>();
  }
  return federated_permission_context_.get();
}

void BrowserContextImpl::ResetFederatedPermissionContext() {
  federated_permission_context_.reset();
}

void BrowserContextImpl::SetPrefetchServiceForTesting(
    std::unique_ptr<PrefetchService> prefetch_service) {
  prefetch_service_ = std::move(prefetch_service);
}

NavigationEntryScreenshotManager*
BrowserContextImpl::GetNavigationEntryScreenshotManager() {
  if (!nav_entry_screenshot_manager_ &&
      NavigationTransitionConfig::AreBackForwardTransitionsEnabled()) {
    nav_entry_screenshot_manager_ =
        std::make_unique<NavigationEntryScreenshotManager>();
  }
  return nav_entry_screenshot_manager_.get();
}

void BrowserContextImpl::WriteIntoTrace(
    perfetto::TracedProto<TraceProto> proto) const {
  proto->set_id(UniqueId());
}

namespace {
bool ShouldEnableDips(BrowserContext* browser_context) {
  if (!base::FeatureList::IsEnabled(features::kBtm)) {
    return false;
  }

  if (!GetContentClient()->browser()->ShouldEnableDips(browser_context)) {
    return false;
  }

  return true;
}
}  // namespace

BtmServiceImpl* BrowserContextImpl::GetDipsService() {
  if (!dips_service_) {
    if (!ShouldEnableDips(self_)) {
      return nullptr;
    }
    dips_service_ = std::make_unique<BtmServiceImpl>(
        base::PassKey<BrowserContextImpl>(), self_);
    GetContentClient()->browser()->OnDipsServiceCreated(self_,
                                                        dips_service_.get());
  }

  return dips_service_.get();
}

namespace {
void CreatePopupHeuristicGrants(base::WeakPtr<BrowserContext> browser_context,
                                base::OnceCallback<void(bool)> callback,
                                std::vector<PopupWithTime> recent_popups) {
  if (!browser_context) {
    std::move(callback).Run(false);
    return;
  }

  for (const PopupWithTime& popup : recent_popups) {
    base::TimeDelta grant_duration =
        content_settings::features::kTpcdBackfillPopupHeuristicsGrants.Get() -
        (base::Time::Now() - popup.last_popup_time);
    if (!grant_duration.is_positive()) {
      continue;
    }

    // `popup_site` and `opener_site` were read from the DIPS database,
    // and were originally computed by calling GetSiteForBtm().
    // GrantCookieAccessDueToHeuristic() takes SchemefulSites, so we create some
    // here, but since we pass ignore_schemes=true the scheme doesn't matter
    // (and port never matters for SchemefulSites), so we hardcode http and 80.
    net::SchemefulSite popup_site(
        url::Origin::CreateFromNormalizedTuple("http", popup.popup_site, 80));
    net::SchemefulSite opener_site(
        url::Origin::CreateFromNormalizedTuple("http", popup.opener_site, 80));

    GetContentClient()->browser()->GrantCookieAccessDueToHeuristic(
        browser_context.get(), opener_site, popup_site, grant_duration,
        /*ignore_schemes=*/true);
  }
  std::move(callback).Run(true);
}
}  // namespace

void BrowserContextImpl::BackfillPopupHeuristicGrants(
    base::OnceCallback<void(bool)> callback) {
  if (!base::FeatureList::IsEnabled(
          content_settings::features::kTpcdHeuristicsGrants) ||
      !content_settings::features::kTpcdBackfillPopupHeuristicsGrants.Get()
           .is_positive()) {
    std::move(callback).Run(false);
    return;
  }

  // TODO: crbug.com/1502264 - ensure backfill is completed if Chrome is
  // shutdown or crashes.
  GetDipsService()
      ->storage()
      ->AsyncCall(&BtmStorage::ReadRecentPopupsWithInteraction)
      .WithArgs(
          content_settings::features::kTpcdBackfillPopupHeuristicsGrants.Get())
      .Then(base::BindOnce(&CreatePopupHeuristicGrants, self_->GetWeakPtr(),
                           std::move(callback)));
}
=======
>>>>>>> chromium
}  // namespace content
