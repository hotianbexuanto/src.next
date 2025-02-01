// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_COMPOSITING_REASONS_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_COMPOSITING_REASONS_H_

#include <stdint.h>
#include <vector>
#include "third_party/blink/renderer/platform/platform_export.h"
#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

using CompositingReasons = uint64_t;

<<<<<<< HEAD
#define FOR_EACH_COMPOSITING_REASON(V)                                         \
  /* Intrinsic reasons that can be known right away by the layer.           */ \
  V(3DTransform)                                                               \
  V(3DScale)                                                                   \
  V(3DRotate)                                                                  \
  V(3DTranslate)                                                               \
  V(Trivial3DTransform)                                                        \
  V(IFrame)                                                                    \
  V(ActiveTransformAnimation)                                                  \
  V(ActiveScaleAnimation)                                                      \
  V(ActiveRotateAnimation)                                                     \
  V(ActiveTranslateAnimation)                                                  \
  V(ActiveOpacityAnimation)                                                    \
  V(ActiveFilterAnimation)                                                     \
  V(ActiveBackdropFilterAnimation)                                             \
  V(AffectedByOuterViewportBoundsDelta)                                        \
  V(AffectedBySafeAreaBottom)                                                  \
  V(FixedPosition)                                                             \
  V(UndoOverscroll)                                                            \
  V(StickyPosition)                                                            \
  V(AnchorPosition)                                                            \
  V(BackdropFilter)                                                            \
  V(BackdropFilterMask)                                                        \
  V(RootScroller)                                                              \
  V(Viewport)                                                                  \
  V(WillChangeTransform)                                                       \
  V(WillChangeScale)                                                           \
  V(WillChangeRotate)                                                          \
  V(WillChangeTranslate)                                                       \
  V(WillChangeOpacity)                                                         \
  V(WillChangeFilter)                                                          \
  V(WillChangeBackdropFilter)                                                  \
  /* This flag is needed only when none of the explicit kWillChange* reasons   \
     are set. */                                                               \
  V(WillChangeOther)                                                           \
                                                                               \
  /* Reasons that depend on ancestor properties */                             \
  V(BackfaceInvisibility3DAncestor)                                            \
  /* TODO(crbug.com/1256990): Transform3DSceneLeaf today depends only on the   \
     element and its properties, but in the future it could be optimized       \
     to consider descendants and moved to the subtree group below. */          \
  V(Transform3DSceneLeaf)                                                      \
                                                                               \
  /* Subtree reasons that require knowing what the status of your subtree is   \
     before knowing the answer. */                                             \
  V(PerspectiveWith3DDescendants)                                              \
  V(Preserve3DWith3DDescendants)                                               \
                                                                               \
  /* ViewTransition element.                                                   \
     See third_party/blink/renderer/core/view_transition/README.md. */         \
  V(ViewTransitionElement)                                                     \
  V(ViewTransitionPseudoElement)                                               \
  V(ViewTransitionElementDescendantWithClipPath)                               \
                                                                               \
  /* For composited scrolling, determined after paint. */                      \
  V(OverflowScrolling)                                                         \
                                                                               \
  /* Element is participating in element capture. */                           \
  V(ElementCapture)                                                            \
                                                                               \
  /* The following reasons are not used in paint properties, but are           \
     determined after paint, for debugging. See PaintArtifactCompositor. */    \
  /* This is based on overlapping relationship among pending layers. */        \
  V(Overlap)                                                                   \
  /* These are based on the type of paint chunks and display items. */         \
  V(BackfaceVisibilityHidden)                                                  \
  V(FixedAttachmentBackground)                                                 \
  V(Caret)                                                                     \
  V(Video)                                                                     \
  V(Canvas)                                                                    \
  V(Plugin)                                                                    \
  V(Scrollbar)                                                                 \
  V(LinkHighlight)                                                             \
  V(DevToolsOverlay)                                                           \
  V(ViewTransitionContent)
=======
#define FOR_EACH_COMPOSITING_REASON(V)                                        \
  /* Intrinsic reasons that can be known right away by the layer. */          \
  V(3DTransform)                                                              \
  V(Trivial3DTransform)                                                       \
  V(Video)                                                                    \
  V(Canvas)                                                                   \
  V(Plugin)                                                                   \
  V(IFrame)                                                                   \
  /* This is used for pre-CompositAfterPaint + CompositeSVG only. */          \
  V(SVGRoot)                                                                  \
  V(BackfaceVisibilityHidden)                                                 \
  V(ActiveTransformAnimation)                                                 \
  V(ActiveOpacityAnimation)                                                   \
  V(ActiveFilterAnimation)                                                    \
  V(ActiveBackdropFilterAnimation)                                            \
  V(AffectedByOuterViewportBoundsDelta)                                       \
  V(FixedPosition)                                                            \
  V(StickyPosition)                                                           \
  V(OverflowScrolling)                                                        \
  V(OverflowScrollingParent)                                                  \
  V(OutOfFlowClipping)                                                        \
  V(VideoOverlay)                                                             \
  V(WillChangeTransform)                                                      \
  V(WillChangeOpacity)                                                        \
  V(WillChangeFilter)                                                         \
  V(WillChangeBackdropFilter)                                                 \
  /* Reasons that depend on ancestor properties */                            \
  V(BackfaceInvisibility3DAncestor)                                           \
  /* This flag is needed only when none of the explicit kWillChange* reasons  \
     are set. */                                                              \
  V(WillChangeOther)                                                          \
  V(BackdropFilter)                                                           \
  V(BackdropFilterMask)                                                       \
  V(RootScroller)                                                             \
  V(XrOverlay)                                                                \
  V(Viewport)                                                                 \
                                                                              \
  /* Overlap reasons that require knowing what's behind you in paint-order    \
     before knowing the answer. */                                            \
  V(AssumedOverlap)                                                           \
  V(Overlap)                                                                  \
  V(NegativeZIndexChildren)                                                   \
  V(SquashingDisallowed)                                                      \
                                                                              \
  /* Subtree reasons that require knowing what the status of your subtree is  \
     before knowing the answer. */                                            \
  V(OpacityWithCompositedDescendants)                                         \
  V(MaskWithCompositedDescendants)                                            \
  V(ReflectionWithCompositedDescendants)                                      \
  V(FilterWithCompositedDescendants)                                          \
  V(BlendingWithCompositedDescendants)                                        \
  V(PerspectiveWith3DDescendants)                                             \
  V(Preserve3DWith3DDescendants)                                              \
  V(IsolateCompositedDescendants)                                             \
  V(FullscreenVideoWithCompositedDescendants)                                 \
                                                                              \
  /* The root layer is a special case. It may be forced to be a layer, but it \
  also needs to be a layer if anything else in the subtree is composited. */  \
  V(Root)                                                                     \
                                                                              \
  /* CompositedLayerMapping internal hierarchy reasons. Some of them are also \
  used in CompositeAfterPaint. */                                             \
  V(LayerForHorizontalScrollbar)                                              \
  V(LayerForVerticalScrollbar)                                                \
  V(LayerForScrollCorner)                                                     \
  V(LayerForScrollingContents)                                                \
  V(LayerForSquashingContents)                                                \
  V(LayerForForeground)                                                       \
  V(LayerForMask)                                                             \
  /* Composited layer painted on top of all other layers as decoration. */    \
  V(LayerForDecoration)                                                       \
  /* Used in CompositeAfterPaint for link highlight, frame overlay, etc. */   \
  V(LayerForOther)                                                            \
  /* DocumentTransition shared element.                                       \
  See third_party/blink/renderer/core/document_transition/README.md. */       \
  V(DocumentTransitionSharedElement)
>>>>>>> chromium

class PLATFORM_EXPORT CompositingReason {
  DISALLOW_NEW();

 private:
  // This contains ordinal values for compositing reasons and will be used to
  // generate the compositing reason bits.
  enum {
#define V(name) kE##name,
    FOR_EACH_COMPOSITING_REASON(V)
#undef V
  };

#define V(name) static_assert(kE##name < 64, "Should fit in 64 bits");
  FOR_EACH_COMPOSITING_REASON(V)
#undef V

 public:
  static std::vector<const char*> ShortNames(CompositingReasons);
  static std::vector<const char*> Descriptions(CompositingReasons);
  static String ToString(CompositingReasons);

  enum : CompositingReasons {
    kNone = 0,
    kAll = ~static_cast<CompositingReasons>(0),
#define V(name) k##name = UINT64_C(1) << kE##name,
    FOR_EACH_COMPOSITING_REASON(V)
#undef V

    // Various combinations of compositing reasons are defined here also, for
    // more intuitive and faster bitwise logic.
    kComboActiveAnimation =
        kActiveTransformAnimation | kActiveOpacityAnimation |
        kActiveFilterAnimation | kActiveBackdropFilterAnimation,

    kComboAllDirectStyleDeterminedReasons =
        k3DTransform | kTrivial3DTransform | kBackfaceVisibilityHidden |
        kComboActiveAnimation | kWillChangeTransform | kWillChangeOpacity |
        kWillChangeFilter | kWillChangeOther | kBackdropFilter |
        kWillChangeBackdropFilter,

    kComboScrollDependentPosition = kFixedPosition | kStickyPosition,

    kComboAllDirectNonStyleDeterminedReasons =
        kVideo | kCanvas | kPlugin | kIFrame | kSVGRoot |
        kOverflowScrollingParent | kOutOfFlowClipping | kVideoOverlay |
        kXrOverlay | kRoot | kRootScroller | kComboScrollDependentPosition |
        kAffectedByOuterViewportBoundsDelta | kBackfaceInvisibility3DAncestor |
        kDocumentTransitionSharedElement,

    kComboAllDirectReasons = kComboAllDirectStyleDeterminedReasons |
                             kComboAllDirectNonStyleDeterminedReasons,

    kComboAllCompositedScrollingDeterminedReasons =
        kComboScrollDependentPosition | kAffectedByOuterViewportBoundsDelta |
        kOverflowScrolling,

    kComboCompositedDescendants =
        kIsolateCompositedDescendants | kOpacityWithCompositedDescendants |
        kMaskWithCompositedDescendants | kFilterWithCompositedDescendants |
        kBlendingWithCompositedDescendants |
        kReflectionWithCompositedDescendants,

    kCombo3DDescendants =
        kPreserve3DWith3DDescendants | kPerspectiveWith3DDescendants,

    kComboAllStyleDeterminedReasons = kComboAllDirectStyleDeterminedReasons |
                                      kComboCompositedDescendants |
                                      kCombo3DDescendants,

    kComboSquashableReasons =
        kOverlap | kAssumedOverlap | kOverflowScrollingParent,

    kPreventingSubpixelAccumulationReasons = kWillChangeTransform,

    kDirectReasonsForPaintOffsetTranslationProperty =
<<<<<<< HEAD
        kFixedPosition | kAffectedByOuterViewportBoundsDelta | kUndoOverscroll |
        kVideo | kCanvas | kPlugin | kIFrame | kAffectedBySafeAreaBottom,
    // TODO(dbaron): kWillChangeOther probably shouldn't be in this list.
    // TODO(vmpstr): kViewTransitionElement is needed to make sure that the
    // capture escapes clips when view transition has a descendant that
    // naturally escapes clips. See crbug.com/348590918 for details.
=======
        kComboScrollDependentPosition | kAffectedByOuterViewportBoundsDelta |
        kVideo | kCanvas | kPlugin | kIFrame | kSVGRoot,
>>>>>>> chromium
    kDirectReasonsForTransformProperty =
        k3DTransform | kTrivial3DTransform | kWillChangeTransform |
        kWillChangeOther | kPerspectiveWith3DDescendants |
        kPreserve3DWith3DDescendants | kActiveTransformAnimation,
    kDirectReasonsForScrollTranslationProperty =
        kRootScroller | kOverflowScrolling,
    kDirectReasonsForEffectProperty =
        kActiveOpacityAnimation | kWillChangeOpacity | kBackdropFilter |
        kWillChangeBackdropFilter | kActiveBackdropFilterAnimation |
        kDocumentTransitionSharedElement,
    kDirectReasonsForFilterProperty =
        kActiveFilterAnimation | kWillChangeFilter,
    kDirectReasonsForBackdropFilter = kBackdropFilter |
                                      kActiveBackdropFilterAnimation |
                                      kWillChangeBackdropFilter,
  };
};

// Any reasons other than overlap or assumed overlap will require the layer to
// be separately compositing.
inline bool RequiresCompositing(CompositingReasons reasons) {
  return reasons & ~CompositingReason::kComboSquashableReasons;
}

// If the layer has overlap or assumed overlap, but no other reasons, then it
// should be squashed.
inline bool RequiresSquashing(CompositingReasons reasons) {
  return !RequiresCompositing(reasons) &&
         (reasons & CompositingReason::kComboSquashableReasons);
}

struct CompositingReasonsStats {
  size_t overlap_layers = 0;
  size_t active_animation_layers = 0;
  size_t assumed_overlap_layers = 0;
  size_t indirect_composited_layers = 0;
  size_t total_composited_layers = 0;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_COMPOSITING_REASONS_H_
