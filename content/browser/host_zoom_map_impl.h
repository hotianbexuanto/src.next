// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_HOST_ZOOM_MAP_IMPL_H_
#define CONTENT_BROWSER_HOST_ZOOM_MAP_IMPL_H_

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/sequenced_task_runner_helpers.h"
#include "content/public/browser/host_zoom_map.h"

namespace content {

class RenderFrameHostImpl;
class WebContentsImpl;

// HostZoomMap lives on the UI thread.
class CONTENT_EXPORT HostZoomMapImpl : public HostZoomMap {
 public:
  HostZoomMapImpl();
  ~HostZoomMapImpl() override;

  // HostZoomMap implementation:
  void SetPageScaleFactorIsOneForView(
      int render_process_id, int render_view_id, bool is_one) override;
  void ClearPageScaleFactorIsOneForView(
      int render_process_id, int render_view_id) override;
  void CopyFrom(HostZoomMap* copy) override;
  double GetZoomLevelForHostAndScheme(const std::string& scheme,
                                      const std::string& host) override;
  // TODO(wjmaclean) Should we use a GURL here? crbug.com/384486
  bool HasZoomLevel(const std::string& scheme,
                    const std::string& host) override;
  ZoomLevelVector GetAllZoomLevels() override;
  void SetZoomLevelForHost(const std::string& host, double level) override;
  void InitializeZoomLevelForHost(const std::string& host,
                                  double level,
                                  base::Time last_modified) override;
  void SetZoomLevelForHostAndScheme(const std::string& scheme,
                                    const std::string& host,
                                    double level) override;
  bool UsesTemporaryZoomLevel(int render_process_id,
                              int render_view_id) override;
  void SetTemporaryZoomLevel(int render_process_id,
                             int render_view_id,
                             double level) override;
  void ClearZoomLevels(base::Time delete_begin, base::Time delete_end) override;
  void ClearTemporaryZoomLevel(int render_process_id,
                               int render_view_id) override;
  double GetDefaultZoomLevel() override;
  void SetDefaultZoomLevel(double level) override;
  base::CallbackListSubscription AddZoomLevelChangedCallback(
      ZoomLevelChangedCallback callback) override;

  // Returns the current zoom level for the specified WebContents. This may
  // be a temporary zoom level, depending on UsesTemporaryZoomLevel().
  double GetZoomLevelForWebContents(WebContentsImpl* web_contents_impl);
  double GetZoomLevelForWebContents(WebContentsImpl* web_contents_impl,
                                    GlobalRenderFrameHostId rfh_id);

  bool PageScaleFactorIsOneForWebContents(
      WebContentsImpl* web_contents_impl) const;

  // Sets the zoom level for this WebContents. If this WebContents is using
  // a temporary zoom level, then level is only applied to this WebContents.
  // Otherwise, the level will be applied on a host level.
  void SetZoomLevelForWebContents(WebContentsImpl* web_contents_impl,
                                  double level);
  void SetZoomLevelForWebContents(WebContentsImpl* web_contents_impl,
                                  GlobalRenderFrameHostId rfh_id,
                                  double level);

  // Returns the temporary zoom level that's only valid for the lifetime of
  // the given WebContents (i.e. isn't saved and doesn't affect other
  // WebContentses) if it exists, the default zoom level otherwise.
  double GetTemporaryZoomLevel(int render_process_id,
                               int render_view_id) const;

  void SendErrorPageZoomLevelRefresh();

  void WillCloseRenderView(int render_process_id, int render_view_id);

  void SetClockForTesting(base::Clock* clock) override;

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
  void SetDefaultZoomLevelPrefCallback(
      HostZoomMap::DefaultZoomChangedCallback callback) override;
  HostZoomMap::DefaultZoomChangedCallback* GetDefaultZoomLevelPrefCallback();
  double GetZoomLevelForHostAndSchemeAndroid(const std::string& scheme,
                                             const std::string& host) override;
  void SetSystemFontScaleForTesting(float scale);
  void SetShouldAdjustForOSLevelForTesting(bool shouldAdjustForOSLevel);
#endif

  double GetZoomLevelForPreviewAndHost(const std::string& host) override;
  void SetZoomLevelForPreviewAndHost(const std::string& host,
                                     double level) override;

  void SetIndependentZoomForFrameTreeNode(WebContents* web_contents,
                                          FrameTreeNodeId ftn_id) override;
  void ClearIndependentZoomForFrameTreeNode(FrameTreeNodeId ftn_id) override;

=======
>>>>>>> chromium
 private:
  struct ZoomLevel {
    double level;
    base::Time last_modified;
  };
  typedef std::map<std::string, ZoomLevel> HostZoomLevels;
  typedef std::map<std::string, HostZoomLevels> SchemeHostZoomLevels;

<<<<<<< HEAD
  typedef std::map<GlobalRenderFrameHostId, double> TemporaryZoomLevels;
  typedef std::set<FrameTreeNodeId> IndependentZoomFrameTreeNodes;
=======
  struct RenderViewKey {
    int render_process_id;
    int render_view_id;
    RenderViewKey(int render_process_id, int render_view_id)
        : render_process_id(render_process_id),
          render_view_id(render_view_id) {}
    bool operator<(const RenderViewKey& other) const {
      return std::tie(render_process_id, render_view_id) <
             std::tie(other.render_process_id, other.render_view_id);
    }
  };

  typedef std::map<RenderViewKey, double> TemporaryZoomLevels;
  typedef std::map<RenderViewKey, bool> ViewPageScaleFactorsAreOne;
>>>>>>> chromium

  double GetZoomLevelForHost(const std::string& host) const;

  // Set a zoom level for |host| and store the |last_modified| timestamp.
  // Use only to explicitly set a timestamp.
  void SetZoomLevelForHostInternal(const std::string& host,
                                   double level,
                                   base::Time last_modified);

  // Internal helper for SetDefaultZoomLevel().
  void SetDefaultZoomLevelInternal(double level,
                                   WebContentsImpl* web_contents,
                                   RenderFrameHostImpl* rfh);

  // Notifies the renderers from this browser context to change the zoom level
  // for the specified host and scheme.
  // |zoom level| will be extracted from |host_zoom_levels_| when needed, so no
  // need to pass them in.
  // TODO(wjmaclean) Should we use a GURL here? crbug.com/384486
  void SendZoomLevelChange(const std::string& scheme, const std::string& host);

  // Callbacks called when zoom level changes.
  base::RepeatingCallbackList<void(const ZoomLevelChange&)>
      zoom_level_changed_callbacks_;

  // Copy of the pref data.
  HostZoomLevels host_zoom_levels_;
  SchemeHostZoomLevels scheme_host_zoom_levels_;
  double default_zoom_level_;

  // Page scale factor data for each renderer.
  ViewPageScaleFactorsAreOne view_page_scale_factors_are_one_;

  TemporaryZoomLevels temporary_zoom_levels_;
  // Used to track which FrameTreeNodes have independent zoom. A FrameTreeNode
  // can have a zoom level that is independent from the main frame when it is
  // displaying content in a GuestView (or possibly a PDF in a OOPIF without a
  // GuestView), and features::kGuestViewMPArch is enabled. When this feature is
  // not enabled it means that GuestViews will have their own WebContents, and
  // so the use of a single zoom level for an entire WebContents suffices.
  IndependentZoomFrameTreeNodes independent_zoom_frame_tree_nodes_;

  base::Clock* clock_;

  DISALLOW_COPY_AND_ASSIGN(HostZoomMapImpl);
};

}  // namespace content

#endif  // CONTENT_BROWSER_HOST_ZOOM_MAP_IMPL_H_
