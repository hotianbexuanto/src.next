// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/host_zoom_map_impl.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <utility>

#include "base/containers/contains.h"
#include "base/strings/string_piece.h"
#include "base/strings/utf_string_conversions.h"
#include "base/time/default_clock.h"
#include "base/values.h"
#include "content/browser/renderer_host/navigation_entry_impl.h"
#include "content/browser/renderer_host/render_process_host_impl.h"
#include "content/browser/renderer_host/render_view_host_impl.h"
#include "content/browser/web_contents/web_contents_impl.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/resource_context.h"
#include "content/public/browser/site_instance.h"
#include "content/public/browser/storage_partition.h"
#include "content/public/common/url_constants.h"
#include "net/base/url_util.h"
#include "third_party/blink/public/common/page/page_zoom.h"

namespace content {

namespace {

std::string GetHostFromProcessView(int render_process_id, int render_view_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  RenderViewHost* render_view_host =
      RenderViewHost::FromID(render_process_id, render_view_id);
  if (!render_view_host)
    return std::string();

<<<<<<< HEAD
  NavigationEntry* entry = rfh->GetController().GetLastCommittedEntry();
=======
  WebContents* web_contents = WebContents::FromRenderViewHost(render_view_host);

  NavigationEntry* entry =
      web_contents->GetController().GetLastCommittedEntry();
>>>>>>> chromium
  if (!entry)
    return std::string();

  return net::GetHostOrSpecFromURL(HostZoomMap::GetURLFromEntry(entry));
}

}  // namespace

GURL HostZoomMap::GetURLFromEntry(NavigationEntry* entry) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  switch (entry->GetPageType()) {
    case PAGE_TYPE_ERROR:
      return GURL(kUnreachableWebDataURL);
    // TODO(wjmaclean): In future, give interstitial pages special treatment as
    // well.
    default:
      return entry->GetURL();
  }
}

HostZoomMap* HostZoomMap::GetDefaultForBrowserContext(BrowserContext* context) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  StoragePartition* partition = context->GetDefaultStoragePartition();
  DCHECK(partition);
  return partition->GetHostZoomMap();
}

HostZoomMap* HostZoomMap::Get(SiteInstance* instance) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  StoragePartition* partition =
      instance->GetBrowserContext()->GetStoragePartition(instance);
  DCHECK(partition);
  return partition->GetHostZoomMap();
}

HostZoomMap* HostZoomMap::GetForWebContents(WebContents* contents) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  // TODO(wjmaclean): Update this behaviour to work with OOPIF.
  // See crbug.com/528407.
  StoragePartition* partition =
      contents->GetBrowserContext()->GetStoragePartition(
          contents->GetSiteInstance());
  DCHECK(partition);
  return partition->GetHostZoomMap();
}

// Helper function for setting/getting zoom levels for WebContents without
// having to import HostZoomMapImpl everywhere.

// static
double HostZoomMap::GetZoomLevel(WebContents* web_contents) {
  return GetZoomLevel(web_contents,
                      web_contents->GetPrimaryMainFrame()->GetGlobalId());
}

<<<<<<< HEAD
// static
double HostZoomMap::GetZoomLevel(WebContents* web_contents,
                                 GlobalRenderFrameHostId rfh_id) {
=======
bool HostZoomMap::PageScaleFactorIsOne(WebContents* web_contents) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  HostZoomMapImpl* host_zoom_map = static_cast<HostZoomMapImpl*>(
      HostZoomMap::GetForWebContents(web_contents));
  return host_zoom_map->PageScaleFactorIsOneForWebContents(
      static_cast<WebContentsImpl*>(web_contents));
}

void HostZoomMap::SetZoomLevel(WebContents* web_contents, double level) {
>>>>>>> chromium
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  HostZoomMapImpl* host_zoom_map = static_cast<HostZoomMapImpl*>(
      HostZoomMap::Get(RenderFrameHost::FromID(rfh_id)->GetSiteInstance()));
  return host_zoom_map->GetZoomLevelForWebContents(
      static_cast<WebContentsImpl*>(web_contents), rfh_id);
}

// static
void HostZoomMap::SetZoomLevel(WebContents* web_contents, double level) {
  HostZoomMap::SetZoomLevel(
      web_contents, web_contents->GetPrimaryMainFrame()->GetGlobalId(), level);
}

// static
void HostZoomMap::SetZoomLevel(WebContents* web_contents,
                               GlobalRenderFrameHostId rfh_id,
                               double level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  HostZoomMapImpl* host_zoom_map = static_cast<HostZoomMapImpl*>(
      HostZoomMap::Get(RenderFrameHost::FromID(rfh_id)->GetSiteInstance()));
  host_zoom_map->SetZoomLevelForWebContents(
      static_cast<WebContentsImpl*>(web_contents), rfh_id, level);
}

void HostZoomMap::SendErrorPageZoomLevelRefresh(WebContents* web_contents) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  HostZoomMapImpl* host_zoom_map =
      static_cast<HostZoomMapImpl*>(HostZoomMap::GetDefaultForBrowserContext(
          web_contents->GetBrowserContext()));
  host_zoom_map->SendErrorPageZoomLevelRefresh();
}

HostZoomMapImpl::HostZoomMapImpl()
    : default_zoom_level_(0.0),
      clock_(base::DefaultClock::GetInstance()) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
}

void HostZoomMapImpl::CopyFrom(HostZoomMap* copy_interface) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  HostZoomMapImpl* copy = static_cast<HostZoomMapImpl*>(copy_interface);
  host_zoom_levels_.insert(copy->host_zoom_levels_.begin(),
                           copy->host_zoom_levels_.end());
  for (const auto& it : copy->scheme_host_zoom_levels_) {
    const std::string& host = it.first;
    scheme_host_zoom_levels_[host] = HostZoomLevels();
    scheme_host_zoom_levels_[host].insert(it.second.begin(), it.second.end());
  }
  default_zoom_level_ = copy->default_zoom_level_;
}

double HostZoomMapImpl::GetZoomLevelForHost(const std::string& host) const {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  const auto it = host_zoom_levels_.find(host);
  return it != host_zoom_levels_.end() ? it->second.level : default_zoom_level_;
}

bool HostZoomMapImpl::HasZoomLevel(const std::string& scheme,
                                   const std::string& host) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto scheme_iterator(scheme_host_zoom_levels_.find(scheme));

  const HostZoomLevels& zoom_levels =
      (scheme_iterator != scheme_host_zoom_levels_.end())
          ? scheme_iterator->second
          : host_zoom_levels_;

  return base::Contains(zoom_levels, host);
}

double HostZoomMapImpl::GetZoomLevelForHostAndScheme(const std::string& scheme,
                                                     const std::string& host) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto scheme_iterator(scheme_host_zoom_levels_.find(scheme));
  if (scheme_iterator != scheme_host_zoom_levels_.end()) {
    auto i(scheme_iterator->second.find(host));
    if (i != scheme_iterator->second.end())
      return i->second.level;
  }

  return GetZoomLevelForHost(host);
}

HostZoomMap::ZoomLevelVector HostZoomMapImpl::GetAllZoomLevels() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  HostZoomMap::ZoomLevelVector result;
  result.reserve(host_zoom_levels_.size() + scheme_host_zoom_levels_.size());
  for (const auto& entry : host_zoom_levels_) {
    ZoomLevelChange change = {
        HostZoomMap::ZOOM_CHANGED_FOR_HOST,
        entry.first,                // host
        std::string(),              // scheme
        entry.second.level,         // zoom level
        entry.second.last_modified  // last modified
    };
    result.push_back(change);
  }
  for (const auto& scheme_entry : scheme_host_zoom_levels_) {
    const std::string& scheme = scheme_entry.first;
    const HostZoomLevels& host_zoom_levels = scheme_entry.second;
    for (const auto& entry : host_zoom_levels) {
      ZoomLevelChange change = {
          HostZoomMap::ZOOM_CHANGED_FOR_SCHEME_AND_HOST,
          entry.first,                // host
          scheme,                     // scheme
          entry.second.level,         // zoom level
          entry.second.last_modified  // last modified
      };
      result.push_back(change);
    }
  }
  return result;
}

void HostZoomMapImpl::SetZoomLevelForHost(const std::string& host,
                                          double level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  base::Time last_modified = clock_->Now();
  SetZoomLevelForHostInternal(host, level, last_modified);
}

void HostZoomMapImpl::InitializeZoomLevelForHost(const std::string& host,
                                                 double level,
                                                 base::Time last_modified) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  SetZoomLevelForHostInternal(host, level, last_modified);
}

void HostZoomMapImpl::SetZoomLevelForHostInternal(const std::string& host,
                                                  double level,
                                                  base::Time last_modified) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (blink::PageZoomValuesEqual(level, default_zoom_level_)) {
    host_zoom_levels_.erase(host);
  } else {
    ZoomLevel& zoomLevel = host_zoom_levels_[host];
    zoomLevel.level = level;
    zoomLevel.last_modified = last_modified;
  }

  // TODO(wjmaclean) Should we use a GURL here? crbug.com/384486
  SendZoomLevelChange(std::string(), host);

  HostZoomMap::ZoomLevelChange change;
  change.mode = HostZoomMap::ZOOM_CHANGED_FOR_HOST;
  change.host = host;
  change.zoom_level = level;
  change.last_modified = last_modified;

  zoom_level_changed_callbacks_.Notify(change);
}

void HostZoomMapImpl::SetZoomLevelForHostAndScheme(const std::string& scheme,
                                                   const std::string& host,
                                                   double level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  // No last_modified timestamp for scheme and host because they are
  // not persistet and are used for special cases only.
  scheme_host_zoom_levels_[scheme][host].level = level;

  SendZoomLevelChange(scheme, host);

  HostZoomMap::ZoomLevelChange change;
  change.mode = HostZoomMap::ZOOM_CHANGED_FOR_SCHEME_AND_HOST;
  change.host = host;
  change.scheme = scheme;
  change.zoom_level = level;
  change.last_modified = base::Time();

  zoom_level_changed_callbacks_.Notify(change);
}

double HostZoomMapImpl::GetDefaultZoomLevel() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  return default_zoom_level_;
}

void HostZoomMapImpl::SetDefaultZoomLevelInternal(double level,
                                                  WebContentsImpl* web_contents,
                                                  RenderFrameHostImpl* rfh) {
  // Get the url from the navigation controller directly, as calling
  // WebContentsImpl::GetLastCommittedURL() may give us a virtual url that
  // is different than the one stored in the map.
  GURL url;
  std::string host;
  std::string scheme;

  NavigationEntry* entry = rfh->GetController().GetLastCommittedEntry();
  // It is possible for a WebContent's zoom level to be queried before
  // a navigation has occurred.
  if (entry) {
    url = GetURLFromEntry(entry);
    scheme = url.scheme();
    host = net::GetHostOrSpecFromURL(url);
  }

  bool uses_default_zoom = !HasZoomLevel(scheme, host) &&
                           !UsesTemporaryZoomLevel(rfh->GetGlobalId());

  if (uses_default_zoom) {
    web_contents->UpdateZoom(rfh->GetGlobalId());

    HostZoomMap::ZoomLevelChange change;
    change.mode = HostZoomMap::ZOOM_CHANGED_FOR_HOST;
    change.host = host;
    change.zoom_level = level;

    zoom_level_changed_callbacks_.Notify(change);
  }
}

void HostZoomMapImpl::SetDefaultZoomLevel(double level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (blink::PageZoomValuesEqual(level, default_zoom_level_))
    return;

  default_zoom_level_ = level;

  // First, remove all entries that match the new default zoom level.
  for (auto it = host_zoom_levels_.begin(); it != host_zoom_levels_.end();) {
    if (blink::PageZoomValuesEqual(it->second.level, default_zoom_level_))
      it = host_zoom_levels_.erase(it);
    else
      it++;
  }

  // Second, update zoom levels for all pages that do not have an overriding
  // entry.
  for (auto* web_contents : WebContentsImpl::GetAllWebContents()) {
    // Only change zoom for WebContents tied to the StoragePartition this
    // HostZoomMap serves.
    if (GetForWebContents(web_contents) != this)
      continue;

<<<<<<< HEAD
    SetDefaultZoomLevelInternal(level, web_contents,
                                web_contents->GetPrimaryMainFrame());
  }

  // If kGuestViewMPArch is enabled, then update zoom levels for subframes that
  // do not have an overriding entry.
  if (!base::FeatureList::IsEnabled(features::kGuestViewMPArch)) {
    return;
  }
  for (auto ftn_id : independent_zoom_frame_tree_nodes_) {
    auto* rfh = FrameTreeNode::GloballyFindByID(ftn_id)->current_frame_host();
    // `rfh` should be non-null here since, if it was deleted, then
    // WebContentsObserver::FrameDeleted will have notified any ZoomControllers,
    // and `independent_zoom_frame_tree_nodes_` will have been updated
    // accordingly.
    if (!UsesTemporaryZoomLevel(rfh->GetGlobalId())) {
      auto* web_contents = WebContentsImpl::FromRenderFrameHostImpl(rfh);
      if (web_contents && (rfh != web_contents->GetPrimaryMainFrame())) {
        SetDefaultZoomLevelInternal(level, web_contents, rfh);
      }
=======
    int render_process_id =
        web_contents->GetRenderViewHost()->GetProcess()->GetID();
    int render_view_id = web_contents->GetRenderViewHost()->GetRoutingID();

    // Get the url from the navigation controller directly, as calling
    // WebContentsImpl::GetLastCommittedURL() may give us a virtual url that
    // is different than the one stored in the map.
    GURL url;
    std::string host;
    std::string scheme;

    NavigationEntry* entry =
        web_contents->GetController().GetLastCommittedEntry();
    // It is possible for a WebContent's zoom level to be queried before
    // a navigation has occurred.
    if (entry) {
      url = GetURLFromEntry(entry);
      scheme = url.scheme();
      host = net::GetHostOrSpecFromURL(url);
    }

    bool uses_default_zoom =
        !HasZoomLevel(scheme, host) &&
        !UsesTemporaryZoomLevel(render_process_id, render_view_id);

    if (uses_default_zoom) {
      web_contents->UpdateZoom();

      HostZoomMap::ZoomLevelChange change;
      change.mode = HostZoomMap::ZOOM_CHANGED_FOR_HOST;
      change.host = host;
      change.zoom_level = level;

      zoom_level_changed_callbacks_.Notify(change);
>>>>>>> chromium
    }
  }
}

base::CallbackListSubscription HostZoomMapImpl::AddZoomLevelChangedCallback(
    ZoomLevelChangedCallback callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  return zoom_level_changed_callbacks_.Add(std::move(callback));
}

double HostZoomMapImpl::GetZoomLevelForWebContents(
    WebContentsImpl* web_contents_impl) {
  return GetZoomLevelForWebContents(
      web_contents_impl,
      web_contents_impl->GetPrimaryMainFrame()->GetGlobalId());
}

double HostZoomMapImpl::GetZoomLevelForWebContents(
    WebContentsImpl* web_contents_impl,
    GlobalRenderFrameHostId rfh_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  int render_process_id =
      web_contents_impl->GetRenderViewHost()->GetProcess()->GetID();
  int routing_id = web_contents_impl->GetRenderViewHost()->GetRoutingID();

<<<<<<< HEAD
  if (UsesTemporaryZoomLevel(rfh_id))
    return GetTemporaryZoomLevel(rfh_id);
=======
  if (UsesTemporaryZoomLevel(render_process_id, routing_id))
    return GetTemporaryZoomLevel(render_process_id, routing_id);
>>>>>>> chromium

  // Get the url from the navigation controller directly, as calling
  // WebContentsImpl::GetLastCommittedURL() may give us a virtual url that
  // is different than is stored in the map.
  GURL url;
  RenderFrameHostImpl* rfh = RenderFrameHostImpl::FromID(rfh_id);
  NavigationEntry* entry =
      base::FeatureList::IsEnabled(features::kGuestViewMPArch)
          ? rfh->GetController().GetLastCommittedEntry()
          : web_contents_impl->GetController().GetLastCommittedEntry();
  // It is possible for a WebContent's zoom level to be queried before
  // a navigation has occurred.
  if (entry) {
    url = GetURLFromEntry(entry);
<<<<<<< HEAD
  }

#if BUILDFLAG(IS_ANDROID)
  return GetZoomLevelForHostAndSchemeAndroid(url.scheme(),
                                             net::GetHostOrSpecFromURL(url));
#else
=======
>>>>>>> chromium
  return GetZoomLevelForHostAndScheme(url.scheme(),
                                      net::GetHostOrSpecFromURL(url));
}

void HostZoomMapImpl::SetZoomLevelForWebContents(
    WebContentsImpl* web_contents_impl,
    GlobalRenderFrameHostId rfh_id,
    double level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
<<<<<<< HEAD

  if (UsesTemporaryZoomLevel(rfh_id)) {
    SetTemporaryZoomLevel(rfh_id, level);
=======
  int render_process_id =
      web_contents_impl->GetRenderViewHost()->GetProcess()->GetID();
  int render_view_id = web_contents_impl->GetRenderViewHost()->GetRoutingID();
  if (UsesTemporaryZoomLevel(render_process_id, render_view_id)) {
    SetTemporaryZoomLevel(render_process_id, render_view_id, level);
>>>>>>> chromium
  } else {
    RenderFrameHostImpl* rfh = RenderFrameHostImpl::FromID(rfh_id);
    NavigationEntry* entry =
        base::FeatureList::IsEnabled(features::kGuestViewMPArch)
            ? rfh->GetController().GetLastCommittedEntry()
            : web_contents_impl->GetController().GetLastCommittedEntry();
    // Get the url from the navigation controller directly, as calling
    // WebContentsImpl::GetLastCommittedURL() may give us a virtual url that
<<<<<<< HEAD
    // is different than what the render frame is using. If the two don't
    // match, the attempt to set the zoom will fail.
=======
    // is different than what the render view is using. If the two don't match,
    // the attempt to set the zoom will fail.
    NavigationEntry* entry =
        web_contents_impl->GetController().GetLastCommittedEntry();
>>>>>>> chromium
    // Tests may invoke this function with a null entry, but we don't
    // want to save zoom levels in this case.
    if (!entry) {
      return;
    }

    GURL url = GetURLFromEntry(entry);
    SetZoomLevelForHost(net::GetHostOrSpecFromURL(url), level);
  }
}

void HostZoomMapImpl::SetPageScaleFactorIsOneForView(int render_process_id,
                                                     int render_view_id,
                                                     bool is_one) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  view_page_scale_factors_are_one_[RenderViewKey(render_process_id,
                                                 render_view_id)] = is_one;
  HostZoomMap::ZoomLevelChange change;
  change.mode = HostZoomMap::PAGE_SCALE_IS_ONE_CHANGED;
  zoom_level_changed_callbacks_.Notify(change);
}

bool HostZoomMapImpl::PageScaleFactorIsOneForWebContents(
    WebContentsImpl* web_contents_impl) const {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  if (!web_contents_impl->GetRenderViewHost()->GetProcess())
    return true;

  const auto it = view_page_scale_factors_are_one_.find(RenderViewKey(
      web_contents_impl->GetRenderViewHost()->GetProcess()->GetID(),
      web_contents_impl->GetRenderViewHost()->GetRoutingID()));
  return it != view_page_scale_factors_are_one_.end() ? it->second : true;
}

void HostZoomMapImpl::ClearPageScaleFactorIsOneForView(int render_process_id,
                                                       int render_view_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  view_page_scale_factors_are_one_.erase(
      RenderViewKey(render_process_id, render_view_id));
}

bool HostZoomMapImpl::UsesTemporaryZoomLevel(int render_process_id,
                                             int render_view_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  RenderViewKey key(render_process_id, render_view_id);
  return base::Contains(temporary_zoom_levels_, key);
}

double HostZoomMapImpl::GetTemporaryZoomLevel(int render_process_id,
                                              int render_view_id) const {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  RenderViewKey key(render_process_id, render_view_id);
  const auto it = temporary_zoom_levels_.find(key);
  return it != temporary_zoom_levels_.end() ? it->second : 0;
}

void HostZoomMapImpl::SetTemporaryZoomLevel(int render_process_id,
                                            int render_view_id,
                                            double level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

<<<<<<< HEAD
  RenderFrameHostImpl* rfh = RenderFrameHostImpl::FromID(rfh_id);
  if (base::FeatureList::IsEnabled(features::kGuestViewMPArch)) {
    CHECK(rfh->is_local_root());
  } else {
    DCHECK(rfh == rfh->GetOutermostMainFrame());
  }

  temporary_zoom_levels_[rfh_id] = level;

  WebContentsImpl* web_contents = WebContentsImpl::FromRenderFrameHostImpl(rfh);
  web_contents->UpdateZoom(rfh_id);
=======
  RenderViewKey key(render_process_id, render_view_id);
  temporary_zoom_levels_[key] = level;

  WebContentsImpl* web_contents =
      static_cast<WebContentsImpl*>(WebContents::FromRenderViewHost(
          RenderViewHost::FromID(render_process_id, render_view_id)));
  web_contents->UpdateZoom();
>>>>>>> chromium

  HostZoomMap::ZoomLevelChange change;
  change.mode = HostZoomMap::ZOOM_CHANGED_TEMPORARY_ZOOM;
  change.host = GetHostFromProcessView(render_process_id, render_view_id);
  change.zoom_level = level;

  zoom_level_changed_callbacks_.Notify(change);
}

void HostZoomMapImpl::ClearZoomLevels(base::Time delete_begin,
                                      base::Time delete_end) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  double default_zoom_level = GetDefaultZoomLevel();
  for (const auto& zoom_level : GetAllZoomLevels()) {
    if (zoom_level.scheme.empty() && delete_begin <= zoom_level.last_modified &&
        (delete_end.is_null() || zoom_level.last_modified < delete_end)) {
      SetZoomLevelForHost(zoom_level.host, default_zoom_level);
    }
  }
}

void HostZoomMapImpl::ClearTemporaryZoomLevel(int render_process_id,
                                              int render_view_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  RenderViewKey key(render_process_id, render_view_id);
  auto it = temporary_zoom_levels_.find(key);
  if (it == temporary_zoom_levels_.end())
    return;

  temporary_zoom_levels_.erase(it);
<<<<<<< HEAD
  WebContentsImpl* web_contents = WebContentsImpl::FromRenderFrameHostImpl(
      RenderFrameHostImpl::FromID(rfh_id));
  web_contents->UpdateZoom(rfh_id);
=======
  WebContentsImpl* web_contents =
      static_cast<WebContentsImpl*>(WebContents::FromRenderViewHost(
          RenderViewHost::FromID(render_process_id, render_view_id)));
  web_contents->UpdateZoom();
>>>>>>> chromium
}

void HostZoomMapImpl::SendZoomLevelChange(const std::string& scheme,
                                          const std::string& host) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  // We'll only send to WebContents not using temporary zoom levels. The one
  // other case of interest is where the renderer is hosting a plugin document;
  // that should be reflected in our temporary zoom level map, but we will
  // double check on the renderer side to avoid the possibility of any races.
  for (auto* web_contents : WebContentsImpl::GetAllWebContents()) {
    // Only send zoom level changes to WebContents that are using this
    // HostZoomMap.
    if (GetForWebContents(web_contents) != this)
      continue;

    int render_process_id =
        web_contents->GetRenderViewHost()->GetProcess()->GetID();
    int render_view_id = web_contents->GetRenderViewHost()->GetRoutingID();

    if (!UsesTemporaryZoomLevel(render_process_id, render_view_id))
      web_contents->UpdateZoomIfNecessary(scheme, host);
  }

  // Also loop over the independently-zoomed FTNs that aren't primary
  // mainframes. If kGuestViewMPArch isn't enabled, then there will be no
  // such frames, so early-out in that case.
  if (!base::FeatureList::IsEnabled(features::kGuestViewMPArch)) {
    return;
  }
  for (auto ftn_id : independent_zoom_frame_tree_nodes_) {
    auto* rfh = FrameTreeNode::GloballyFindByID(ftn_id)->current_frame_host();
    if (!UsesTemporaryZoomLevel(rfh->GetGlobalId())) {
      auto* web_contents = WebContentsImpl::FromRenderFrameHostImpl(rfh);
      if (web_contents && (rfh != web_contents->GetPrimaryMainFrame())) {
        web_contents->UpdateZoomIfNecessary(scheme, host, rfh);
      }
    }
  }
}

void HostZoomMapImpl::SendErrorPageZoomLevelRefresh() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  GURL error_url(kUnreachableWebDataURL);
  std::string host = net::GetHostOrSpecFromURL(error_url);

  SendZoomLevelChange(std::string(), host);
}

void HostZoomMapImpl::WillCloseRenderView(int render_process_id,
                                          int render_view_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  ClearTemporaryZoomLevel(render_process_id, render_view_id);
  ClearPageScaleFactorIsOneForView(render_process_id, render_view_id);
}

HostZoomMapImpl::~HostZoomMapImpl() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
}

void HostZoomMapImpl::SetClockForTesting(base::Clock* clock) {
  clock_ = clock;
}

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
void HostZoomMapImpl::SetSystemFontScaleForTesting(float scale) {
  JNIEnv* env = jni_zero::AttachCurrentThread();
  Java_HostZoomMapImpl_setSystemFontScaleForTesting(env, scale);  // IN-TEST
}

void HostZoomMapImpl::SetShouldAdjustForOSLevelForTesting(
    bool shouldAdjustForOSLevel) {
  JNIEnv* env = jni_zero::AttachCurrentThread();
  Java_HostZoomMapImpl_setShouldAdjustForOSLevelForTesting(
      env, shouldAdjustForOSLevel);  // IN-TEST
}

void HostZoomMapImpl::SetDefaultZoomLevelPrefCallback(
    HostZoomMap::DefaultZoomChangedCallback callback) {
  default_zoom_level_pref_callback_ = std::move(callback);
}

HostZoomMap::DefaultZoomChangedCallback*
HostZoomMapImpl::GetDefaultZoomLevelPrefCallback() {
  return &default_zoom_level_pref_callback_;
}

void JNI_HostZoomMapImpl_SetZoomLevel(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_web_contents,
    jdouble new_zoom_level,
    jdouble adjusted_zoom_level) {
  WebContents* web_contents = WebContents::FromJavaWebContents(j_web_contents);
  DCHECK(web_contents);

  GlobalRenderFrameHostId rfh_id =
      web_contents->GetPrimaryMainFrame()->GetGlobalId();

  // We want to set and save the new zoom level, but we want to actually render
  // the adjusted level.
  HostZoomMap::SetZoomLevel(web_contents, new_zoom_level);

  HostZoomMapImpl* host_zoom_map = static_cast<HostZoomMapImpl*>(
      HostZoomMap::GetForWebContents(web_contents));
  host_zoom_map->SetTemporaryZoomLevel(rfh_id, adjusted_zoom_level);

  // We must now remove this webcontents from the list of temporary zoom levels,
  // this is so that any future request will continue to update the underlying
  // host/scheme save, and will not be perceived as "temporary".
  // i.e. once temporary is set for a web_contents, the call to
  // SetZoomLevelForWebContents will keep updating what is rendered, but will no
  // longer call SetZoomLevelForHost, which saves the choice for that host.
  host_zoom_map->SetNoLongerUsesTemporaryZoomLevel(rfh_id);
}

void JNI_HostZoomMapImpl_SetZoomLevelForHost(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_context,
    const base::android::JavaParamRef<jstring>& j_host,
    jdouble level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  BrowserContext* context = BrowserContextFromJavaHandle(j_context);
  if (!context) {
    return;
  }

  HostZoomMap* host_zoom_map =
      HostZoomMap::GetDefaultForBrowserContext(context);

  std::string host(base::android::ConvertJavaStringToUTF8(env, j_host));
  host_zoom_map->SetZoomLevelForHost(host, level);
}

jdouble JNI_HostZoomMapImpl_GetZoomLevel(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_web_contents) {
  WebContents* web_contents = WebContents::FromJavaWebContents(j_web_contents);
  DCHECK(web_contents);

  return HostZoomMap::GetZoomLevel(web_contents);
}

void JNI_HostZoomMapImpl_SetDefaultZoomLevel(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_context,
    jdouble new_default_zoom_level) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  BrowserContext* context = BrowserContextFromJavaHandle(j_context);
  if (!context)
    return;

  HostZoomMapImpl* host_zoom_map = static_cast<HostZoomMapImpl*>(
      HostZoomMap::GetDefaultForBrowserContext(context));

  // If a callback has been set (e.g. by chrome_zoom_level_prefs to store an
  // updated value in Prefs), call this now with the chosen zoom level.
  if (host_zoom_map->GetDefaultZoomLevelPrefCallback()) {
    host_zoom_map->GetDefaultZoomLevelPrefCallback()->Run(
        new_default_zoom_level);
  }

  // Update the default zoom level for existing tabs. This must be done after
  // the Pref is updated due to guard clause in chrome_zoom_level_prefs.
  host_zoom_map->SetDefaultZoomLevel(new_default_zoom_level);
}

jdouble JNI_HostZoomMapImpl_GetDefaultZoomLevel(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_context) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  BrowserContext* context = BrowserContextFromJavaHandle(j_context);
  if (!context)
    return 0.0;

  HostZoomMapImpl* host_zoom_map = static_cast<HostZoomMapImpl*>(
      HostZoomMap::GetDefaultForBrowserContext(context));
  return host_zoom_map->GetDefaultZoomLevel();
}

std::vector<jni_zero::ScopedJavaLocalRef<jobject>>
JNI_HostZoomMapImpl_GetAllHostZoomLevels(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_context) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  std::vector<jni_zero::ScopedJavaLocalRef<jobject>> ret;

  // Get instance of HostZoomMap.
  BrowserContext* context = BrowserContextFromJavaHandle(j_context);
  if (!context) {
    return ret;
  }

  HostZoomMap* host_zoom_map =
      HostZoomMap::GetDefaultForBrowserContext(context);

  // Convert C++ vector of structs to vector of objects.
  for (const auto& entry : host_zoom_map->GetAllZoomLevels()) {
    switch (entry.mode) {
      case HostZoomMap::ZOOM_CHANGED_FOR_HOST: {
        ret.push_back(Java_HostZoomMapImpl_buildSiteZoomInfo(env, entry.host,
                                                             entry.zoom_level));
        break;
      }
      case HostZoomMap::ZOOM_CHANGED_FOR_SCHEME_AND_HOST:
        NOTREACHED();
      case HostZoomMap::ZOOM_CHANGED_TEMPORARY_ZOOM:
        NOTREACHED();
    }
  }

  return ret;
}
#endif

double HostZoomMapImpl::GetZoomLevelForPreviewAndHost(const std::string& host) {
  const auto it = host_zoom_levels_for_preview_.find(host);
  return it != host_zoom_levels_for_preview_.end() ? it->second.level
                                                   : default_zoom_level_;
}

void HostZoomMapImpl::SetZoomLevelForPreviewAndHost(const std::string& host,
                                                    double level) {
  if (blink::ZoomValuesEqual(level, default_zoom_level_)) {
    host_zoom_levels_for_preview_.erase(host);
  } else {
    ZoomLevel& zoomLevel = host_zoom_levels_for_preview_[host];
    zoomLevel.level = level;
    zoomLevel.last_modified = clock_->Now();
  }
}

void HostZoomMapImpl::SetIndependentZoomForFrameTreeNode(
    WebContents* web_contents,
    FrameTreeNodeId ftn_id) {
  CHECK(web_contents);
  CHECK(static_cast<RenderFrameHostImpl*>(
            web_contents->UnsafeFindFrameByFrameTreeNodeId(ftn_id))
            ->is_local_root());
  independent_zoom_frame_tree_nodes_.insert(ftn_id);
}

void HostZoomMapImpl::ClearIndependentZoomForFrameTreeNode(
    FrameTreeNodeId ftn_id) {
  independent_zoom_frame_tree_nodes_.erase(ftn_id);
}

=======
>>>>>>> chromium
}  // namespace content
