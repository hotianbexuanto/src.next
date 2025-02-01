// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_OFFSCREEN_CANVAS_PLACEHOLDER_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_OFFSCREEN_CANVAS_PLACEHOLDER_H_

#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "base/single_thread_task_runner.h"
#include "components/viz/common/resources/resource_id.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/platform/graphics/canvas_resource_dispatcher.h"
=======
#include "third_party/abseil-cpp/absl/types/optional.h"
>>>>>>> chromium
#include "third_party/blink/renderer/platform/platform_export.h"
#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"
#include "third_party/skia/include/core/SkFilterQuality.h"

namespace blink {

class CanvasResource;

class PLATFORM_EXPORT OffscreenCanvasPlaceholder {
  DISALLOW_NEW();

 public:
  ~OffscreenCanvasPlaceholder();

  virtual void SetOffscreenCanvasResource(scoped_refptr<CanvasResource>,
                                          viz::ResourceId resource_id);
  void SetOffscreenCanvasDispatcher(
      base::WeakPtr<CanvasResourceDispatcher>,
      scoped_refptr<base::SingleThreadTaskRunner>);

<<<<<<< HEAD
  void SetSuspendOffscreenCanvasAnimation(
      CanvasResourceDispatcher::AnimationState requested_state);
=======
  void ReleaseOffscreenCanvasFrame();

  void SetSuspendOffscreenCanvasAnimation(bool);
>>>>>>> chromium

  static OffscreenCanvasPlaceholder* GetPlaceholderCanvasById(
      unsigned placeholder_id);

  void RegisterPlaceholderCanvas(unsigned placeholder_id);
  void UnregisterPlaceholderCanvas();
  const scoped_refptr<CanvasResource>& OffscreenCanvasFrame() const {
    return placeholder_frame_;
  }

  bool IsOffscreenCanvasRegistered() const {
    return placeholder_id_ != kNoPlaceholderId;
  }

<<<<<<< HEAD
=======
  void UpdateOffscreenCanvasFilterQuality(SkFilterQuality filter_quality);

>>>>>>> chromium
  virtual bool HasCanvasCapture() const { return false; }

  CanvasResourceDispatcher::AnimationState GetAnimationStateForTesting() const {
    return current_animation_state_;
  }

 private:
  bool PostSetAnimationStateToOffscreenCanvasThread(
      CanvasResourceDispatcher::AnimationState animation_state);

  // Information about the Offscreen Canvas:
  scoped_refptr<CanvasResource> placeholder_frame_;
  base::WeakPtr<CanvasResourceDispatcher> frame_dispatcher_;
  scoped_refptr<base::SingleThreadTaskRunner> frame_dispatcher_task_runner_;
  viz::ResourceId placeholder_frame_resource_id_ = viz::kInvalidResourceId;

  enum {
    kNoPlaceholderId = -1,
  };
  int placeholder_id_ = kNoPlaceholderId;

<<<<<<< HEAD
  // If an animation state change was requested, but we couldn't update it
  // immediately, then this holds the most recent request.
  std::optional<CanvasResourceDispatcher::AnimationState>
      deferred_animation_state_;

  // Most recent animation state sent to the dispatcher.
  CanvasResourceDispatcher::AnimationState current_animation_state_ =
      CanvasResourceDispatcher::AnimationState::kActive;

  std::optional<cc::PaintFlags::FilterQuality> filter_quality_ = std::nullopt;
=======
  enum AnimationState {
    kActiveAnimation,
    kSuspendedAnimation,
    kShouldSuspendAnimation,
    kShouldActivateAnimation,
  };
  AnimationState animation_state_ = kActiveAnimation;
  absl::optional<SkFilterQuality> filter_quality_ = absl::nullopt;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_OFFSCREEN_CANVAS_PLACEHOLDER_H_
