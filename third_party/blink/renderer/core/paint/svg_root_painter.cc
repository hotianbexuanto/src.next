// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/paint/svg_root_painter.h"

#include "third_party/abseil-cpp/absl/types/optional.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_root.h"
#include "third_party/blink/renderer/core/layout/svg/svg_layout_support.h"
#include "third_party/blink/renderer/core/paint/box_painter.h"
#include "third_party/blink/renderer/core/paint/object_paint_properties.h"
#include "third_party/blink/renderer/core/paint/paint_info.h"
#include "third_party/blink/renderer/core/paint/scoped_svg_paint_state.h"
#include "third_party/blink/renderer/core/svg/svg_svg_element.h"

namespace blink {

IntRect SVGRootPainter::PixelSnappedSize(
    const PhysicalOffset& paint_offset) const {
  return PixelSnappedIntRect(
      PhysicalRect(paint_offset, layout_svg_root_.Size()));
}

AffineTransform SVGRootPainter::TransformToPixelSnappedBorderBox(
    const PhysicalOffset& paint_offset) const {
  const IntRect snapped_size = PixelSnappedSize(paint_offset);
  AffineTransform paint_offset_to_border_box =
      AffineTransform::Translation(snapped_size.X(), snapped_size.Y());
  LayoutSize size = layout_svg_root_.Size();
  if (!size.IsEmpty()) {
<<<<<<< HEAD
    if (ShouldApplySnappingScaleAdjustment(layout_svg_root_)) {
      paint_offset_to_border_box.Scale(
          snapped_size.width() / size.width.ToFloat(),
          snapped_size.height() / size.height.ToFloat());
    } else if (RuntimeEnabledFeatures::
                   SvgInlineRootPixelSnappingScaleAdjustmentEnabled()) {
      // If snapping shrunk the box, scale it to avoid overflowing and getting
      // clipped.
      if (size.width > snapped_size.width() ||
          size.height > snapped_size.height()) {
        // Scale uniformly to fit in the snapped box.
        const float scale_x = snapped_size.width() / size.width.ToFloat();
        const float scale_y = snapped_size.height() / size.height.ToFloat();
        const float uniform_scale = std::min(scale_x, scale_y);
        PhysicalSize scaled_size = size;
        scaled_size.Scale(uniform_scale);
        // If scaling uniformly introduces too large of an error, then scale
        // non-uniformly.
        if (snapped_size.width() - scaled_size.width > 1 ||
            snapped_size.height() - scaled_size.height > 1) {
          paint_offset_to_border_box.Scale(scale_x, scale_y);
        } else {
          paint_offset_to_border_box.Scale(uniform_scale);
        }
      }
    }
=======
    paint_offset_to_border_box.Scale(
        snapped_size.Width() / size.Width().ToFloat(),
        snapped_size.Height() / size.Height().ToFloat());
>>>>>>> chromium
  }
  paint_offset_to_border_box.Multiply(
      layout_svg_root_.LocalToBorderBoxTransform());
  return paint_offset_to_border_box;
}

void SVGRootPainter::PaintReplaced(const PaintInfo& paint_info,
                                   const PhysicalOffset& paint_offset) {
  // An empty viewport disables rendering.
  if (PixelSnappedSize(paint_offset).IsEmpty())
    return;

  // An empty viewBox also disables rendering.
  // (http://www.w3.org/TR/SVG/coords.html#ViewBoxAttribute)
  auto* svg = To<SVGSVGElement>(layout_svg_root_.GetNode());
  DCHECK(svg);
  if (svg->HasEmptyViewBox())
    return;

  ScopedSVGPaintState paint_state(layout_svg_root_, paint_info);
  BoxPainter(layout_svg_root_).PaintChildren(paint_info);
}

}  // namespace blink
