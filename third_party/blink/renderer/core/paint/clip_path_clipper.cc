// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/paint/clip_path_clipper.h"

#include "third_party/blink/renderer/core/css/clip_path_paint_image_generator.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/layout/layout_box.h"
#include "third_party/blink/renderer/core/layout/layout_inline.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_resource_clipper.h"
#include "third_party/blink/renderer/core/layout/svg/svg_resources.h"
#include "third_party/blink/renderer/core/paint/paint_info.h"
#include "third_party/blink/renderer/core/paint/paint_layer.h"
#include "third_party/blink/renderer/core/style/clip_path_operation.h"
#include "third_party/blink/renderer/core/style/reference_clip_path_operation.h"
#include "third_party/blink/renderer/core/style/shape_clip_path_operation.h"
#include "third_party/blink/renderer/platform/graphics/image.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_display_item.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_recorder.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_controller.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_record_builder.h"
#include "third_party/blink/renderer/platform/graphics/paint/scoped_paint_chunk_properties.h"

namespace blink {

namespace {

SVGResourceClient* GetResourceClient(const LayoutObject& object) {
  if (object.IsSVGChild())
    return SVGResources::GetClient(object);
  CHECK(object.IsBoxModelObject());
  return To<LayoutBoxModelObject>(object).Layer()->ResourceInfo();
}

LayoutSVGResourceClipper* ResolveElementReference(
    const LayoutObject& object,
    const ReferenceClipPathOperation& reference_clip_path_operation) {
  SVGResourceClient* client = GetResourceClient(object);
  // We may not have a resource client for some non-rendered elements (like
  // filter primitives) that we visit during paint property tree construction.
  if (!client)
    return nullptr;
  LayoutSVGResourceClipper* resource_clipper =
      GetSVGResourceAsType(*client, reference_clip_path_operation);
  if (resource_clipper) {
    SECURITY_DCHECK(!resource_clipper->NeedsLayout());
    resource_clipper->ClearInvalidationMask();
  }
  return resource_clipper;
}

<<<<<<< HEAD
PhysicalRect BorderBoxRect(const LayoutBoxModelObject& object) {
  // It is complex to map from an SVG border box to a reference box (for
  // example, `GeometryBox::kViewBox` is independent of the border box) so we
  // use `SVGResources::ReferenceBoxForEffects` for SVG reference boxes.
  CHECK(!object.IsSVGChild());

  if (auto* box = DynamicTo<LayoutBox>(object)) {
    // If the box is fragment-less return an empty box.
    if (box->PhysicalFragmentCount() == 0u) {
      return PhysicalRect();
    }
    return box->PhysicalBorderBoxRect();
  }

  // The spec doesn't say what to do if there are multiple lines. Gecko uses the
  // first fragment in that case. We'll do the same here.
  // See: https://crbug.com/641907
  const LayoutInline& layout_inline = To<LayoutInline>(object);
  if (layout_inline.IsInLayoutNGInlineFormattingContext()) {
    InlineCursor cursor;
    cursor.MoveTo(layout_inline);
    if (cursor) {
      return cursor.Current().RectInContainerFragment();
    }
  }
  return PhysicalRect();
}

// TODO(crbug.com/1473440): Convert this to take a PhysicalBoxFragment
// instead of a LayoutBoxModelObject.
PhysicalBoxStrut ReferenceBoxBorderBoxOutsets(
    GeometryBox geometry_box,
    const LayoutBoxModelObject& object) {
  // It is complex to map from an SVG border box to a reference box (for
  // example, `GeometryBox::kViewBox` is independent of the border box) so we
  // use `SVGResources::ReferenceBoxForEffects` for SVG reference boxes.
  CHECK(!object.IsSVGChild());

  switch (geometry_box) {
    case GeometryBox::kPaddingBox:
      return -object.BorderOutsets();
    case GeometryBox::kContentBox:
    case GeometryBox::kFillBox:
      return -(object.BorderOutsets() + object.PaddingOutsets());
    case GeometryBox::kMarginBox:
      return object.MarginOutsets();
    case GeometryBox::kBorderBox:
    case GeometryBox::kStrokeBox:
    case GeometryBox::kViewBox:
      return PhysicalBoxStrut();
  }
}

FloatRoundedRect RoundedReferenceBox(GeometryBox geometry_box,
                                     const LayoutObject& object) {
  if (object.IsSVGChild()) {
    return FloatRoundedRect(ClipPathClipper::LocalReferenceBox(object));
  }

  const auto& box = To<LayoutBoxModelObject>(object);
  PhysicalRect border_box_rect = BorderBoxRect(box);
  FloatRoundedRect rounded_border_box_rect =
      RoundedBorderGeometry::RoundedBorder(box.StyleRef(), border_box_rect);
  if (geometry_box == GeometryBox::kMarginBox) {
    rounded_border_box_rect.OutsetForMarginOrShadow(
        gfx::OutsetsF(ReferenceBoxBorderBoxOutsets(geometry_box, box)));
  } else {
    rounded_border_box_rect.Outset(
        gfx::OutsetsF(ReferenceBoxBorderBoxOutsets(geometry_box, box)));
  }
  return rounded_border_box_rect;
}

// Should the paint offset be applied to clip-path geometry for
// `clip_path_owner`?
bool UsesPaintOffset(const LayoutObject& clip_path_owner) {
  return !clip_path_owner.IsSVGChild();
}

// Is the reference box (as returned by LocalReferenceBox) for |clip_path_owner|
// zoomed with EffectiveZoom()?
bool UsesZoomedReferenceBox(const LayoutObject& clip_path_owner) {
  return !clip_path_owner.IsSVGChild() || clip_path_owner.IsSVGForeignObject();
}

CompositedPaintStatus CompositeClipPathStatus(Node* node) {
  Element* element = DynamicTo<Element>(node);
  if (!element) {
    return CompositedPaintStatus::kNoAnimation;
  }

  ElementAnimations* element_animations = element->GetElementAnimations();
  if (!element_animations) {
    return CompositedPaintStatus::kNoAnimation;
  }
  return element_animations->CompositedClipPathStatus();
}

void SetCompositeClipPathStatus(Node* node, bool is_compositable) {
  Element* element = DynamicTo<Element>(node);
  if (!element)
    return;

  ElementAnimations* element_animations = element->GetElementAnimations();
  DCHECK(element_animations || !is_compositable);
  if (element_animations) {
    element_animations->SetCompositedClipPathStatus(
        is_compositable ? CompositedPaintStatus::kComposited
                        : CompositedPaintStatus::kNotComposited);
  }
}

void PaintWorkletBasedClip(GraphicsContext& context,
                           const LayoutObject& clip_path_owner,
                           const gfx::RectF& reference_box,
                           const LayoutObject& reference_box_object) {
  DCHECK(ClipPathClipper::HasCompositeClipPathAnimation(clip_path_owner));

  ClipPathPaintImageGenerator* generator =
      clip_path_owner.GetFrame()->GetClipPathPaintImageGenerator();

  // The bounding rect of the clip-path animation, relative to the layout
  // object.
  std::optional<gfx::RectF> bounding_box =
      ClipPathClipper::LocalClipPathBoundingBox(clip_path_owner);
  DCHECK(bounding_box);

  // Pixel snap bounding rect to allow for the proper painting of partially
  // opaque pixels
  *bounding_box = gfx::RectF(gfx::ToEnclosingRect(*bounding_box));

  // The mask image should be the same size as the bounding rect, but will have
  // an origin of 0,0 as it has its own coordinate space.
  gfx::RectF src_rect = gfx::RectF(bounding_box.value().size());
  gfx::RectF dst_rect = bounding_box.value();

  float zoom = UsesZoomedReferenceBox(reference_box_object)
                   ? reference_box_object.StyleRef().EffectiveZoom()
                   : 1;

  scoped_refptr<Image> paint_worklet_image = generator->Paint(
      zoom,
      /* Translate the reference box such that it is relative to the origin of
         the mask image, and not the origin of the layout object. This ensures
         the clip path remains within the bounds of the mask image and has the
         correct translation. */
      gfx::RectF(reference_box.origin() - dst_rect.origin().OffsetFromOrigin(),
                 reference_box.size()),

      dst_rect.size(), *clip_path_owner.GetNode());
  // Dark mode should always be disabled for clip mask.
  context.DrawImage(*paint_worklet_image, Image::kSyncDecode,
                    ImageAutoDarkMode::Disabled(), ImagePaintTimingInfo(),
                    dst_rect, &src_rect, SkBlendMode::kSrcOver,
                    kRespectImageOrientation);
}

gfx::RectF CalcLocalReferenceBox(
    const LayoutObject& object,
    const ClipPathOperation::OperationType clip_path_operation,
    GeometryBox geometry_box) {
  if (object.IsSVGChild()) {
    // Use the object bounding box for url() references.
    if (clip_path_operation == ClipPathOperation::kReference) {
      geometry_box = GeometryBox::kFillBox;
    }
    gfx::RectF unzoomed_reference_box = SVGResources::ReferenceBoxForEffects(
        object, geometry_box, SVGResources::ForeignObjectQuirk::kDisabled);
    if (UsesZoomedReferenceBox(object)) {
      return gfx::ScaleRect(unzoomed_reference_box,
                            object.StyleRef().EffectiveZoom());
    }
    return unzoomed_reference_box;
  }

  const auto& box = To<LayoutBoxModelObject>(object);
  PhysicalRect reference_box = BorderBoxRect(box);
  reference_box.Expand(ReferenceBoxBorderBoxOutsets(geometry_box, box));
  return gfx::RectF(reference_box);
}

}  // namespace

Animation* ClipPathClipper::GetCompositableClipPathAnimation(
    const LayoutObject& layout_object) {
  ClipPathPaintImageGenerator* generator =
      layout_object.GetFrame()->GetClipPathPaintImageGenerator();
  CHECK(generator);

  const Element* element = To<Element>(layout_object.GetNode());
  Animation* animation = generator->GetAnimationIfCompositable(element);

  if (!animation) {
    return nullptr;
  }

  if (animation->CheckCanStartAnimationOnCompositor(nullptr) !=
      CompositorAnimations::kNoFailure) {
    return nullptr;
  }

  return animation;
}

bool ClipPathClipper::HasCompositeClipPathAnimation(
    const LayoutObject& layout_object) {
  if (!RuntimeEnabledFeatures::CompositeClipPathAnimationEnabled()) {
    return false;
  }

  if (layout_object.GetDocument().Lifecycle().GetState() <
      DocumentLifecycle::kInPrePaint) {
    DCHECK(false) << "HasCompositeClipPathAnimation result not defined before"
                  << " pre-paint.";
    base::debug::DumpWithoutCrashing();
  }

  CompositedPaintStatus status =
      CompositeClipPathStatus(layout_object.GetNode());
  switch (status) {
    case CompositedPaintStatus::kComposited:
      DCHECK(GetCompositableClipPathAnimation(layout_object));
      return true;
    case CompositedPaintStatus::kNoAnimation:
    case CompositedPaintStatus::kNotComposited:
      return false;
    case CompositedPaintStatus::kNeedsRepaint:
      // TODO(crbug.com/374656290): Remove this and replace with NOTREACHED.
      // The compositing decision must be resolved by the time this check is
      // called. See FragmentPaintPropertyTreeBuilder::UpdateClipPathClip.

      // For now, dump without crashing as this is likely caused by
      // crbug.com/374656290. In this case, the status is set to kNeedsRepaint
      // in an update caused by a transform animation after the status and paint
      // property has already been configured correctly, and is not re-resolved
      // only because the animation has not had an update that requires a
      // repaint (See the early return in PrePaintTreeWalk::Walk). Because
      // nothing meaningful has changed in this case, we can safely return true.

      // Confirm this is the case be re-resolving status. Doing so here is
      // improper because it's unaware of fragmentation, so produce a crash dump
      ClipPathClipper::ResolveClipPathStatus(layout_object, false);
      CHECK(CompositeClipPathStatus(layout_object.GetNode()) ==
            CompositedPaintStatus::kComposited);

      base::debug::DumpWithoutCrashing();
      return true;
  }
=======
}  // namespace

// Is the reference box (as returned by LocalReferenceBox) for |clip_path_owner|
// zoomed with EffectiveZoom()?
static bool UsesZoomedReferenceBox(const LayoutObject& clip_path_owner) {
  return !clip_path_owner.IsSVGChild() || clip_path_owner.IsSVGForeignObject();
>>>>>>> chromium
}

static void PaintWorkletBasedClip(GraphicsContext& context,
                                  const LayoutObject& clip_path_owner,
                                  const FloatRect& reference_box,
                                  bool uses_zoomed_reference_box) {
  DCHECK(RuntimeEnabledFeatures::CompositeClipPathAnimationEnabled());
  DCHECK_EQ(clip_path_owner.StyleRef().ClipPath()->GetType(),
            ClipPathOperation::SHAPE);

  float zoom = uses_zoomed_reference_box
                   ? clip_path_owner.StyleRef().EffectiveZoom()
                   : 1;
  ClipPathPaintImageGenerator* generator =
      clip_path_owner.GetFrame()->GetClipPathPaintImageGenerator();

  scoped_refptr<Image> paint_worklet_image =
      generator->Paint(zoom, reference_box, *clip_path_owner.GetNode());

  absl::optional<FloatRect> bounding_box =
      ClipPathClipper::LocalClipPathBoundingBox(clip_path_owner);
  DCHECK(bounding_box);
  FloatRect src_rect(bounding_box.value());
  context.DrawImage(paint_worklet_image.get(), Image::kSyncDecode, src_rect,
                    &src_rect, clip_path_owner.StyleRef().DisableForceDark(),
                    SkBlendMode::kSrcOver, kRespectImageOrientation);
}

FloatRect ClipPathClipper::LocalReferenceBox(const LayoutObject& object) {
  if (object.IsSVGChild())
    return SVGResources::ReferenceBoxForEffects(object);

<<<<<<< HEAD
  // TODO(crbug.com/374656290): Replace this with CHECK_LE when this bug is
  // known to be resolved.
  if (layout_object.GetDocument().Lifecycle().GetState() >=
      DocumentLifecycle::kInPaint) {
    DCHECK(false) << "Clip-path status must not be resolved after pre-paint";
    base::debug::DumpWithoutCrashing();
  }

  // If not all the fragments of this layout object have been populated yet, it
  // will be impossible to tell if a composited clip path animation is possible
  // or not based only on the layout object. Exclude the possibility if we're
  // fragmented. We also shouldn't composite in the case of will-change:
  // contents.
  if (is_in_block_fragmentation ||
      layout_object.StyleRef().SubtreeWillChangeContents()) {
    SetCompositeClipPathStatus(layout_object.GetNode(), false);
    return;
  }

  if (CompositeClipPathStatus(layout_object.GetNode()) !=
      CompositedPaintStatus::kNeedsRepaint) {
    return;
  }

  Animation* animation = GetCompositableClipPathAnimation(layout_object);
  SetCompositeClipPathStatus(layout_object.GetNode(), animation);
}

gfx::RectF ClipPathClipper::LocalReferenceBox(const LayoutObject& object) {
  ClipPathOperation* clip_path = object.StyleRef().ClipPath();
  GeometryBox geometry_box = GeometryBox::kBorderBox;

  if (const auto* shape = DynamicTo<ShapeClipPathOperation>(clip_path)) {
    geometry_box = shape->GetGeometryBox();
  } else if (const auto* box =
                 DynamicTo<GeometryBoxClipPathOperation>(clip_path)) {
    geometry_box = box->GetGeometryBox();
  }

  return CalcLocalReferenceBox(object, clip_path->GetType(), geometry_box);
}

std::optional<gfx::RectF> ClipPathClipper::LocalClipPathBoundingBox(
=======
  if (object.IsBox())
    return FloatRect(To<LayoutBox>(object).BorderBoxRect());

  return FloatRect(To<LayoutInline>(object).ReferenceBoxForClipPath());
}

absl::optional<FloatRect> ClipPathClipper::LocalClipPathBoundingBox(
>>>>>>> chromium
    const LayoutObject& object) {
  if (object.IsText() || !object.StyleRef().HasClipPath())
    return absl::nullopt;

  FloatRect reference_box = LocalReferenceBox(object);
  ClipPathOperation& clip_path = *object.StyleRef().ClipPath();
  if (clip_path.GetType() == ClipPathOperation::SHAPE) {
    auto zoom =
        UsesZoomedReferenceBox(object) ? object.StyleRef().EffectiveZoom() : 1;
    auto& shape = To<ShapeClipPathOperation>(clip_path);
    FloatRect bounding_box = shape.GetPath(reference_box, zoom).BoundingRect();
    bounding_box.Intersect(LayoutRect::InfiniteIntRect());
    return bounding_box;
  }

  DCHECK_EQ(clip_path.GetType(), ClipPathOperation::REFERENCE);
  LayoutSVGResourceClipper* clipper = ResolveElementReference(
      object, To<ReferenceClipPathOperation>(clip_path));
  if (!clipper)
    return absl::nullopt;

  FloatRect bounding_box = clipper->ResourceBoundingBox(reference_box);
  if (UsesZoomedReferenceBox(object) &&
      clipper->ClipPathUnits() == SVGUnitTypes::kSvgUnitTypeUserspaceonuse) {
    bounding_box.Scale(clipper->StyleRef().EffectiveZoom());
    // With kSvgUnitTypeUserspaceonuse, the clip path layout is relative to
    // the current transform space, and the reference box is unused.
    // While SVG object has no concept of paint offset, HTML object's
    // local space is shifted by paint offset.
    bounding_box.MoveBy(reference_box.Location());
  }
  bounding_box.Intersect(LayoutRect::InfiniteIntRect());
  return bounding_box;
}

static AffineTransform MaskToContentTransform(
    const LayoutSVGResourceClipper& resource_clipper,
    bool uses_zoomed_reference_box,
    const FloatRect& reference_box) {
  AffineTransform mask_to_content;
  if (resource_clipper.ClipPathUnits() ==
      SVGUnitTypes::kSvgUnitTypeUserspaceonuse) {
    if (uses_zoomed_reference_box) {
      mask_to_content.Translate(reference_box.X(), reference_box.Y());
      mask_to_content.Scale(resource_clipper.StyleRef().EffectiveZoom());
    }
  }

  mask_to_content.Multiply(
      resource_clipper.CalculateClipTransform(reference_box));
  return mask_to_content;
}

static absl::optional<Path> PathBasedClipInternal(
    const LayoutObject& clip_path_owner,
    bool uses_zoomed_reference_box,
    const FloatRect& reference_box) {
  const ClipPathOperation& clip_path = *clip_path_owner.StyleRef().ClipPath();
  if (const auto* reference_clip =
          DynamicTo<ReferenceClipPathOperation>(clip_path)) {
    LayoutSVGResourceClipper* resource_clipper =
        ResolveElementReference(clip_path_owner, *reference_clip);
    if (!resource_clipper)
      return absl::nullopt;
    absl::optional<Path> path = resource_clipper->AsPath();
    if (!path)
      return path;
    path->Transform(MaskToContentTransform(
        *resource_clipper, uses_zoomed_reference_box, reference_box));
    return path;
  }

  DCHECK_EQ(clip_path.GetType(), ClipPathOperation::SHAPE);
  auto& shape = To<ShapeClipPathOperation>(clip_path);
  float zoom = uses_zoomed_reference_box
                   ? clip_path_owner.StyleRef().EffectiveZoom()
                   : 1;
  return shape.GetPath(reference_box, zoom);
}

void ClipPathClipper::PaintClipPathAsMaskImage(
    GraphicsContext& context,
    const LayoutObject& layout_object,
    const DisplayItemClient& display_item_client,
    const PhysicalOffset& paint_offset) {
  const auto* properties = layout_object.FirstFragment().PaintProperties();
  DCHECK(properties);
  DCHECK(properties->MaskClip());
  DCHECK(properties->ClipPathMask());
  PropertyTreeStateOrAlias property_tree_state(
      properties->MaskClip()->LocalTransformSpace(), *properties->MaskClip(),
      *properties->ClipPathMask());
  ScopedPaintChunkProperties scoped_properties(
      context.GetPaintController(), property_tree_state, display_item_client,
      DisplayItem::kSVGClip);

  if (DrawingRecorder::UseCachedDrawingIfPossible(context, display_item_client,
                                                  DisplayItem::kSVGClip))
    return;

  DrawingRecorder recorder(
      context, display_item_client, DisplayItem::kSVGClip,
      EnclosingIntRect(properties->MaskClip()->UnsnappedClipRect().Rect()));
  context.Save();
  context.Translate(paint_offset.left, paint_offset.top);

<<<<<<< HEAD
  if (ClipPathClipper::HasCompositeClipPathAnimation(layout_object)) {
    if (!layout_object.GetFrame()) {
      return;
    }

    // clip_path can potentially be a nullptr instead of being none in certain
    // cases, like if there is a clip-path animation with a delay on an element
    // that is absolutely positioned.
    gfx::RectF reference_box;
    if (layout_object.StyleRef().ClipPath()) {
      reference_box = ClipPathClipper::LocalReferenceBox(layout_object);
    } else {
      // TODO(crbug.com/379052285): these assumptions are currently valid
      // because of value filters. Eventually, these should be removed when
      // proper geometry-box support is added.
      reference_box = CalcLocalReferenceBox(
          layout_object, ClipPathOperation::OperationType::kShape,
          GeometryBox::kBorderBox);
    }

    PaintWorkletBasedClip(context, layout_object, reference_box, layout_object);

    // TODO(crbug.com/393260698): Use cached animation value rather than
    // re-running checks
    Animation* animation = GetCompositableClipPathAnimation(layout_object);
    CHECK(animation) << "Unable to find composited clip path animation";
    animation->OnPaintWorkletImageCreated();
=======
  bool uses_zoomed_reference_box = UsesZoomedReferenceBox(layout_object);
  FloatRect reference_box = LocalReferenceBox(layout_object);
  if (RuntimeEnabledFeatures::CompositeClipPathAnimationEnabled() &&
      layout_object.StyleRef().ClipPath()->GetType() ==
          ClipPathOperation::SHAPE) {
    if (!layout_object.GetFrame())
      return;
    PaintWorkletBasedClip(context, layout_object, reference_box,
                          uses_zoomed_reference_box);
>>>>>>> chromium
  } else {
    gfx::RectF reference_box = LocalReferenceBox(layout_object);
    bool is_first = true;
    bool rest_of_the_chain_already_appled = false;
    const LayoutObject* current_object = &layout_object;
    while (!rest_of_the_chain_already_appled && current_object) {
      const ClipPathOperation* clip_path =
          current_object->StyleRef().ClipPath();
      if (!clip_path)
        break;
      // We wouldn't have reached here if the current clip-path is a shape,
      // because it would have been applied as a path-based clip already.
      LayoutSVGResourceClipper* resource_clipper = ResolveElementReference(
          *current_object, To<ReferenceClipPathOperation>(*clip_path));
      if (!resource_clipper)
        break;

      if (is_first)
        context.Save();
      else
        context.BeginLayer(1.f, SkBlendMode::kDstIn);

      if (resource_clipper->StyleRef().HasClipPath()) {
        // Try to apply nested clip-path as path-based clip.
        if (const absl::optional<Path>& path = PathBasedClipInternal(
                *resource_clipper, uses_zoomed_reference_box, reference_box)) {
          context.ClipPath(path->GetSkPath(), kAntiAliased);
          rest_of_the_chain_already_appled = true;
        }
      }
      context.ConcatCTM(MaskToContentTransform(
          *resource_clipper, uses_zoomed_reference_box, reference_box));
      context.DrawRecord(resource_clipper->CreatePaintRecord());

      if (is_first)
        context.Restore();
      else
        context.EndLayer();

      is_first = false;
      current_object = resource_clipper;
    }
  }
  context.Restore();
}

bool ClipPathClipper::ShouldUseMaskBasedClip(const LayoutObject& object) {
  if (object.IsText() || !object.StyleRef().HasClipPath())
    return false;
  if (RuntimeEnabledFeatures::CompositeClipPathAnimationEnabled() &&
      object.StyleRef().ClipPath()->GetType() == ClipPathOperation::SHAPE)
    return true;
  const auto* reference_clip =
      DynamicTo<ReferenceClipPathOperation>(object.StyleRef().ClipPath());
  if (!reference_clip)
    return false;
  LayoutSVGResourceClipper* resource_clipper =
      ResolveElementReference(object, *reference_clip);
  if (!resource_clipper)
    return false;
  return !resource_clipper->AsPath();
}

absl::optional<Path> ClipPathClipper::PathBasedClip(
    const LayoutObject& clip_path_owner) {
  if (RuntimeEnabledFeatures::CompositeClipPathAnimationEnabled()) {
    const ClipPathOperation& clip_path = *clip_path_owner.StyleRef().ClipPath();
    if (clip_path.GetType() == ClipPathOperation::SHAPE)
      return absl::nullopt;
  }
  return PathBasedClipInternal(clip_path_owner,
                               UsesZoomedReferenceBox(clip_path_owner),
                               LocalReferenceBox(clip_path_owner));
}

}  // namespace blink
