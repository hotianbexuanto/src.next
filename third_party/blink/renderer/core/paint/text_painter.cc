// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/paint/text_painter.h"

#include "third_party/blink/renderer/core/css/css_property_names.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/layout/api/line_layout_api_shim.h"
#include "third_party/blink/renderer/core/layout/api/line_layout_item.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"
#include "third_party/blink/renderer/core/layout/layout_text_combine.h"
#include "third_party/blink/renderer/core/layout/text_decoration_offset_base.h"
#include "third_party/blink/renderer/core/paint/applied_decoration_painter.h"
#include "third_party/blink/renderer/core/paint/box_painter.h"
#include "third_party/blink/renderer/core/paint/highlight_painting_utils.h"
#include "third_party/blink/renderer/core/paint/paint_info.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/paint/svg_object_painter.h"
#include "third_party/blink/renderer/core/paint/text_paint_style.h"
#include "third_party/blink/renderer/core/paint/text_shadow_painter.h"
#include "third_party/blink/renderer/core/paint/timing/paint_timing_detector.h"
=======
>>>>>>> chromium
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/shadow_list.h"
#include "third_party/blink/renderer/platform/fonts/font.h"
#include "third_party/blink/renderer/platform/fonts/text_run_paint_info.h"
#include "third_party/blink/renderer/platform/graphics/graphics_context.h"
#include "third_party/blink/renderer/platform/graphics/graphics_context_state_saver.h"
#include "third_party/blink/renderer/platform/text/text_run.h"
#include "third_party/blink/renderer/platform/wtf/text/character_names.h"

namespace blink {

<<<<<<< HEAD
namespace {

// We usually use the text decoration thickness to determine how far
// ink-skipped text decorations should be away from the glyph
// contours. Cap this at 5 CSS px in each direction when thickness
// growths larger than that. A value of 13 closely matches FireFox'
// implementation.
constexpr float kDecorationClipMaxDilation = 13;

class SelectionStyleScope {
  STACK_ALLOCATED();

 public:
  SelectionStyleScope(const LayoutObject&,
                      const ComputedStyle& style,
                      const ComputedStyle& selection_style);
  SelectionStyleScope(const SelectionStyleScope&) = delete;
  SelectionStyleScope& operator=(const SelectionStyleScope) = delete;
  ~SelectionStyleScope();

 private:
  const LayoutObject& layout_object_;
  const ComputedStyle& selection_style_;
  const bool styles_are_equal_;
};

SelectionStyleScope::SelectionStyleScope(const LayoutObject& layout_object,
                                         const ComputedStyle& style,
                                         const ComputedStyle& selection_style)
    : layout_object_(layout_object),
      selection_style_(selection_style),
      styles_are_equal_(style == selection_style) {
  if (styles_are_equal_) {
    return;
  }
  DCHECK(!layout_object.IsSVGInlineText());
  SVGResources::UpdatePaints(layout_object_, nullptr, selection_style_);
}

SelectionStyleScope::~SelectionStyleScope() {
  if (styles_are_equal_) {
    return;
  }
  SVGResources::ClearPaints(layout_object_, &selection_style_);
}

void UpdateGraphicsContext(GraphicsContext& context,
                           const TextPaintStyle& text_style,
                           GraphicsContextStateSaver& state_saver,
                           const TextShadowPaintPhase& phase) {
  if (phase == TextShadowPaintPhase::kShadow) {
    context.SetTextDrawingMode(kTextModeFill);
    context.SetFillColor(Color::kBlack);
  } else {
    TextDrawingModeFlags mode = context.TextDrawingMode();
    if (text_style.stroke_width > 0) {
      TextDrawingModeFlags new_mode = mode | kTextModeStroke;
      if (mode != new_mode) {
        state_saver.SaveIfNeeded();
        context.SetTextDrawingMode(new_mode);
        mode = new_mode;
      }
    }

    if (mode & kTextModeFill && text_style.fill_color != context.FillColor()) {
      context.SetFillColor(text_style.fill_color);
    }

    if (mode & kTextModeStroke) {
      if (text_style.stroke_color != context.StrokeColor()) {
        context.SetStrokeColor(text_style.stroke_color);
      }
      if (text_style.stroke_width != context.StrokeThickness()) {
        context.SetStrokeThickness(text_style.stroke_width);
      }
    }
  }

  switch (text_style.paint_order) {
    case kPaintOrderNormal:
    case kPaintOrderFillStrokeMarkers:
    case kPaintOrderFillMarkersStroke:
    case kPaintOrderMarkersFillStroke:
      context.SetTextPaintOrder(kFillStroke);
      break;
    case kPaintOrderStrokeFillMarkers:
    case kPaintOrderStrokeMarkersFill:
    case kPaintOrderMarkersStrokeFill:
      context.SetTextPaintOrder(kStrokeFill);
      break;
  }
}

enum class SvgPaintMode { kText, kTextDecoration };

void PrepareStrokeGeometry(const TextPainter::SvgTextPaintState& state,
                           const ComputedStyle& style,
                           const LayoutObject& layout_parent,
                           SvgPaintMode svg_paint_mode,
                           cc::PaintFlags& flags) {
  float stroke_scale_factor = 1;
  // The stroke geometry needs be generated based on the scaled font.
  if (style.VectorEffect() != EVectorEffect::kNonScalingStroke) {
    switch (svg_paint_mode) {
      case SvgPaintMode::kText:
        stroke_scale_factor = state.InlineText().ScalingFactor();
        break;
      case SvgPaintMode::kTextDecoration: {
        Font scaled_font;
        LayoutSVGInlineText::ComputeNewScaledFontForStyle(
            layout_parent, stroke_scale_factor, scaled_font);
        DCHECK(stroke_scale_factor);
        break;
      }
    }
  }

  StrokeData stroke_data;
  SVGLayoutSupport::ApplyStrokeStyleToStrokeData(
      stroke_data, style, layout_parent, stroke_scale_factor);
  if (stroke_scale_factor != 1) {
    stroke_data.SetThickness(stroke_data.Thickness() * stroke_scale_factor);
  }
  stroke_data.SetupPaint(&flags);
}

struct SvgPaints {
  std::optional<cc::PaintFlags> fill;
  std::optional<cc::PaintFlags> stroke;
};

void PrepareSvgPaints(const TextPainter::SvgTextPaintState& state,
                      const SvgContextPaints* context_paints,
                      SvgPaintMode paint_mode,
                      SvgPaints& paints) {
  if (state.IsRenderingClipPathAsMaskImage()) [[unlikely]] {
    cc::PaintFlags& flags = paints.fill.emplace();
    flags.setColor(SK_ColorBLACK);
    flags.setAntiAlias(true);
    return;
  }

  // https://svgwg.org/svg2-draft/text.html#TextDecorationProperties
  // The fill and stroke of the text decoration are given by the fill and stroke
  // of the text at the point where the text decoration is declared.
  const LayoutObject& layout_parent = paint_mode == SvgPaintMode::kText
                                          ? *state.InlineText().Parent()
                                          : state.TextDecorationObject();
  SVGObjectPainter object_painter(layout_parent, context_paints);
  if (state.IsPaintingTextMatch()) [[unlikely]] {
    const ComputedStyle& style = state.Style();

    cc::PaintFlags& fill_flags = paints.fill.emplace();
    fill_flags.setColor(state.TextMatchColor().Rgb());
    fill_flags.setAntiAlias(true);

    cc::PaintFlags unused_flags;
    if (SVGObjectPainter::HasVisibleStroke(style, context_paints)) {
      if (!object_painter.PreparePaint(state.GetPaintFlags(), style,
                                       kApplyToStrokeMode, unused_flags)) {
        return;
      }
      cc::PaintFlags& stroke_flags = paints.stroke.emplace(fill_flags);
      PrepareStrokeGeometry(state, style, layout_parent, paint_mode,
                            stroke_flags);
    }
    return;
  }

  const ComputedStyle& style = [&layout_parent,
                                &state]() -> const ComputedStyle& {
    if (state.IsPaintingSelection()) {
      if (const ComputedStyle* pseudo_selection_style =
              layout_parent.GetSelectionStyle()) {
        return *pseudo_selection_style;
      }
    }
    return layout_parent.StyleRef();
  }();

  std::optional<SelectionStyleScope> paint_resource_scope;
  if (&style != layout_parent.Style()) {
    paint_resource_scope.emplace(layout_parent, *layout_parent.Style(), style);
  }

  const AffineTransform* shader_transform = state.GetShaderTransform();
  if (SVGObjectPainter::HasFill(style, context_paints)) {
    if (object_painter.PreparePaint(state.GetPaintFlags(), style,
                                    kApplyToFillMode, paints.fill.emplace(),
                                    shader_transform)) {
      paints.fill->setAntiAlias(true);
    } else {
      paints.fill.reset();
    }
  }
  if (SVGObjectPainter::HasVisibleStroke(style, context_paints)) {
    if (object_painter.PreparePaint(state.GetPaintFlags(), style,
                                    kApplyToStrokeMode, paints.stroke.emplace(),
                                    shader_transform)) {
      paints.stroke->setAntiAlias(true);

      PrepareStrokeGeometry(state, style, layout_parent, paint_mode,
                            *paints.stroke);
    } else {
      paints.stroke.reset();
    }
  }
}

using OrderedPaints = std::array<const cc::PaintFlags*, 2>;

OrderedPaints OrderPaints(const SvgPaints& paints, EPaintOrder paint_order) {
  OrderedPaints ordered_paints = {
      base::OptionalToPtr(paints.fill),
      base::OptionalToPtr(paints.stroke),
  };
  const PaintOrderArray paint_order_array(paint_order,
                                          PaintOrderArray::Type::kNoMarkers);
  if (paint_order_array[0] == PT_STROKE) {
    std::swap(ordered_paints[0], ordered_paints[1]);
  }
  return ordered_paints;
}

template <typename PassFunction>
void DrawPaintOrderPasses(const OrderedPaints& ordered_paints,
                          PassFunction pass) {
  for (const auto* paint : ordered_paints) {
    if (!paint) {
      continue;
    }
    pass(*paint);
  }
}

}  // namespace

gfx::RectF TextPainter::VisualRectInLocalSpace() const {
  gfx::RectF float_visual_rect(visual_rect_);
  if (rotation_) {
    float_visual_rect = rotation_->Inverse().MapRect(float_visual_rect);
  }
  return float_visual_rect;
}

void TextPainter::Paint(const TextFragmentPaintInfo& fragment_paint_info,
                        const TextPaintStyle& text_style,
                        DOMNodeId node_id,
                        const AutoDarkMode& auto_dark_mode,
                        ShadowMode shadow_mode) {
  // TODO(layout-dev): We shouldn't be creating text fragments without text.
  if (!fragment_paint_info.shape_result) {
    return;
  }
  // Do not try to paint kShadowsOnly without a ShadowList, because we will
  // create an empty DrawLooper that effectively paints kTextProperOnly.
  if (shadow_mode == ShadowMode::kShadowsOnly && !text_style.shadow) {
    return;
  }
  DCHECK_LE(fragment_paint_info.from, fragment_paint_info.text.length());
  DCHECK_LE(fragment_paint_info.to, fragment_paint_info.text.length());

  // TODO(layout-dev): Handle combine text here or elsewhere.
  PaintWithTextShadow(
      [&](TextShadowPaintPhase phase) {
        GraphicsContextStateSaver state_saver(graphics_context_, false);
        UpdateGraphicsContext(graphics_context_, text_style, state_saver,
                              phase);

        if (svg_text_paint_state_.has_value()) {
          // clipPath works on raw geometry even with shadow.
          if (phase == TextShadowPaintPhase::kForeground ||
              !svg_text_paint_state_->IsRenderingClipPathAsMaskImage()) {
            const AutoDarkMode svg_text_auto_dark_mode(
                DarkModeFilter::ElementRole::kSVG,
                auto_dark_mode.enabled &&
                    !svg_text_paint_state_->IsRenderingClipPathAsMaskImage());
            PaintSvgTextFragment(fragment_paint_info, node_id,
                                 svg_text_auto_dark_mode);
          }
        } else {
          graphics_context_.DrawText(font_, fragment_paint_info,
                                     gfx::PointF(text_origin_), node_id,
                                     auto_dark_mode);
        }

        if (!emphasis_mark_.empty()) {
          if (phase == TextShadowPaintPhase::kForeground &&
              text_style.emphasis_mark_color != text_style.fill_color) {
            graphics_context_.SetFillColor(text_style.emphasis_mark_color);
          }
          graphics_context_.DrawEmphasisMarks(
              font_, fragment_paint_info, emphasis_mark_,
              gfx::PointF(text_origin_) +
                  gfx::Vector2dF(0, emphasis_mark_offset_),
              auto_dark_mode);
        }
      },
      graphics_context_, text_style, VisualRectInLocalSpace(), horizontal_,
      shadow_mode);

  // TODO(sohom): SubstringContainsOnlyWhitespaceOrEmpty() does not check
  // for all whitespace characters as defined in the spec definition of
  // whitespace. See https://w3c.github.io/paint-timing/#non-empty
  // In particular 0xb and 0xc are not checked.
  if (!fragment_paint_info.text.SubstringContainsOnlyWhitespaceOrEmpty(
          fragment_paint_info.from, fragment_paint_info.to)) {
    graphics_context_.GetPaintController().SetTextPainted();
  }

  if (!font_.ShouldSkipDrawing()) {
    PaintTimingDetector::NotifyTextPaint(visual_rect_);
=======
void TextPainter::Paint(unsigned start_offset,
                        unsigned end_offset,
                        unsigned length,
                        const TextPaintStyle& text_style,
                        DOMNodeId node_id) {
  GraphicsContextStateSaver state_saver(graphics_context_, false);
  UpdateGraphicsContext(text_style, state_saver);
  if (combined_text_) {
    graphics_context_.Save();
    combined_text_->TransformToInlineCoordinates(graphics_context_,
                                                 text_frame_rect_);
    PaintInternal<kPaintText>(start_offset, end_offset, length, node_id);
    graphics_context_.Restore();
  } else {
    PaintInternal<kPaintText>(start_offset, end_offset, length, node_id);
  }

  if (!emphasis_mark_.IsEmpty()) {
    if (combined_text_) {
      graphics_context_.ConcatCTM(Rotation(text_frame_rect_, kClockwise));
      PaintEmphasisMarkForCombinedText(text_style,
                                       combined_text_->OriginalFont());
      graphics_context_.ConcatCTM(
          Rotation(text_frame_rect_, kCounterclockwise));
    } else {
      if (text_style.emphasis_mark_color != text_style.fill_color)
        graphics_context_.SetFillColor(text_style.emphasis_mark_color);
      PaintInternal<kPaintEmphasisMark>(start_offset, end_offset, length,
                                        node_id);
    }
>>>>>>> chromium
  }
}

void TextPainter::PaintDecorationsExceptLineThrough(
    const TextDecorationOffsetBase& decoration_offset,
    TextDecorationInfo& decoration_info,
    const PaintInfo& paint_info,
    const Vector<AppliedTextDecoration>& decorations,
    const TextPaintStyle& text_style,
<<<<<<< HEAD
    const TextPaintStyle& selection_style,
    const LineRelativeRect& selection_rect,
    DOMNodeId node_id,
    const AutoDarkMode& auto_dark_mode) {
  if (!fragment_paint_info.shape_result) {
    return;
  }
=======
    bool* has_line_through_decoration) {
  GraphicsContext& context = paint_info.context;
  GraphicsContextStateSaver state_saver(context);
  UpdateGraphicsContext(context, text_style, horizontal_, state_saver);
>>>>>>> chromium

  if (combined_text_)
    context.ConcatCTM(Rotation(text_frame_rect_, kClockwise));

  // text-underline-position may flip underline and overline.
  ResolvedUnderlinePosition underline_position =
      decoration_info.UnderlinePosition();
  bool flip_underline_and_overline = false;
  if (underline_position == ResolvedUnderlinePosition::kOver) {
    flip_underline_and_overline = true;
    underline_position = ResolvedUnderlinePosition::kUnder;
  }

  for (size_t applied_decoration_index = 0;
       applied_decoration_index < decorations.size();
       ++applied_decoration_index) {
    const AppliedTextDecoration& decoration =
        decorations[applied_decoration_index];
    TextDecoration lines = decoration.Lines();
    bool has_underline = EnumHasFlags(lines, TextDecoration::kUnderline);
    bool has_overline = EnumHasFlags(lines, TextDecoration::kOverline);
    if (flip_underline_and_overline)
      std::swap(has_underline, has_overline);

    decoration_info.SetDecorationIndex(applied_decoration_index);

    float resolved_thickness = decoration_info.ResolvedThickness();
    context.SetStrokeThickness(resolved_thickness);

    if (has_underline && decoration_info.FontData()) {
      // Don't apply text-underline-offset to overline.
      Length line_offset =
          flip_underline_and_overline ? Length() : decoration.UnderlineOffset();

      const int paint_underline_offset =
          decoration_offset.ComputeUnderlineOffset(
              underline_position, decoration_info.Style().ComputedFontSize(),
              decoration_info.FontData()->GetFontMetrics(), line_offset,
              resolved_thickness);
      decoration_info.SetPerLineData(
          TextDecoration::kUnderline, paint_underline_offset,
          TextDecorationInfo::DoubleOffsetFromThickness(resolved_thickness), 1);
      PaintDecorationUnderOrOverLine(context, decoration_info,
                                     TextDecoration::kUnderline);
    }

    if (has_overline && decoration_info.FontData()) {
      // Don't apply text-underline-offset to overline.
      Length line_offset =
          flip_underline_and_overline ? decoration.UnderlineOffset() : Length();

      FontVerticalPositionType position =
          flip_underline_and_overline ? FontVerticalPositionType::TopOfEmHeight
                                      : FontVerticalPositionType::TextTop;
      const int paint_overline_offset =
          decoration_offset.ComputeUnderlineOffsetForUnder(
              line_offset, decoration_info.Style().ComputedFontSize(),
              resolved_thickness, position);
      decoration_info.SetPerLineData(
          TextDecoration::kOverline, paint_overline_offset,
          -TextDecorationInfo::DoubleOffsetFromThickness(resolved_thickness),
          1);
      PaintDecorationUnderOrOverLine(context, decoration_info,
                                     TextDecoration::kOverline);
    }

    // We could instead build a vector of the TextDecoration instances needing
    // line-through but this is a rare case so better to avoid vector overhead.
    *has_line_through_decoration |=
        EnumHasFlags(lines, TextDecoration::kLineThrough);
  }

  // Restore rotation as needed.
  if (combined_text_)
    context.ConcatCTM(Rotation(text_frame_rect_, kCounterclockwise));
}

void TextPainter::PaintDecorationsOnlyLineThrough(
    TextDecorationInfo& decoration_info,
    const PaintInfo& paint_info,
    const Vector<AppliedTextDecoration>& decorations,
    const TextPaintStyle& text_style) {
  GraphicsContext& context = paint_info.context;
  GraphicsContextStateSaver state_saver(context);
  UpdateGraphicsContext(context, text_style, horizontal_, state_saver);

  if (combined_text_)
    context.ConcatCTM(Rotation(text_frame_rect_, kClockwise));

  for (size_t applied_decoration_index = 0;
       applied_decoration_index < decorations.size();
       ++applied_decoration_index) {
    const AppliedTextDecoration& decoration =
        decorations[applied_decoration_index];
    TextDecoration lines = decoration.Lines();
    if (EnumHasFlags(lines, TextDecoration::kLineThrough)) {
      decoration_info.SetDecorationIndex(applied_decoration_index);

      float resolved_thickness = decoration_info.ResolvedThickness();
      context.SetStrokeThickness(resolved_thickness);

      // For increased line thickness, the line-through decoration needs to grow
      // in both directions from its origin, subtract half the thickness to keep
      // it centered at the same origin.
      const float line_through_offset =
          2 * decoration_info.Baseline() / 3 - resolved_thickness / 2;
      // Floor double_offset in order to avoid double-line gap to appear
      // of different size depending on position where the double line
      // is drawn because of rounding downstream in
      // GraphicsContext::DrawLineForText.
      decoration_info.SetPerLineData(
          TextDecoration::kLineThrough, line_through_offset,
          floorf(TextDecorationInfo::DoubleOffsetFromThickness(
              resolved_thickness)),
          0);
      AppliedDecorationPainter decoration_painter(context, decoration_info,
                                                  TextDecoration::kLineThrough);
      // No skip: ink for line-through,
      // compare https://github.com/w3c/csswg-drafts/issues/711
      decoration_painter.Paint();
    }
  }

  // Restore rotation as needed.
  if (combined_text_)
    context.ConcatCTM(Rotation(text_frame_rect_, kCounterclockwise));
}

template <TextPainter::PaintInternalStep step>
void TextPainter::PaintInternalRun(TextRunPaintInfo& text_run_paint_info,
                                   unsigned from,
                                   unsigned to,
                                   DOMNodeId node_id) {
  DCHECK(from <= text_run_paint_info.run.length());
  DCHECK(to <= text_run_paint_info.run.length());

  text_run_paint_info.from = from;
  text_run_paint_info.to = to;

  if (step == kPaintEmphasisMark) {
    graphics_context_.DrawEmphasisMarks(
        font_, text_run_paint_info, emphasis_mark_,
        FloatPoint(text_origin_) + IntSize(0, emphasis_mark_offset_));
  } else {
    DCHECK(step == kPaintText);
    graphics_context_.DrawText(font_, text_run_paint_info,
                               FloatPoint(text_origin_), node_id);
  }
}

template <TextPainter::PaintInternalStep Step>
void TextPainter::PaintInternal(unsigned start_offset,
                                unsigned end_offset,
                                unsigned truncation_point,
                                DOMNodeId node_id) {
  TextRunPaintInfo text_run_paint_info(run_);
  if (start_offset <= end_offset) {
    PaintInternalRun<Step>(text_run_paint_info, start_offset, end_offset,
                           node_id);
  } else {
    if (end_offset > 0) {
      PaintInternalRun<Step>(text_run_paint_info, ellipsis_offset_, end_offset,
                             node_id);
    }
    if (start_offset < truncation_point) {
      PaintInternalRun<Step>(text_run_paint_info, start_offset,
                             truncation_point, node_id);
    }
  }
}

<<<<<<< HEAD
void TextPainter::ClipDecorationsStripe(
    const TextFragmentPaintInfo& fragment_paint_info,
    float upper,
    float stripe_width,
    float dilation) {
  if (fragment_paint_info.from >= fragment_paint_info.to ||
      !fragment_paint_info.shape_result) {
=======
void TextPainter::ClipDecorationsStripe(float upper,
                                        float stripe_width,
                                        float dilation) {
  TextRunPaintInfo text_run_paint_info(run_);
  if (!run_.length())
>>>>>>> chromium
    return;
  }

  Vector<Font::TextIntercept> text_intercepts;
  font_.GetTextIntercepts(
      text_run_paint_info, graphics_context_.DeviceScaleFactor(),
      graphics_context_.FillFlags(),
      std::make_tuple(upper, upper + stripe_width), text_intercepts);

<<<<<<< HEAD
  for (auto intercept : text_intercepts) {
    gfx::PointF clip_origin(text_origin_);
    gfx::RectF clip_rect(
        clip_origin + gfx::Vector2dF(intercept.begin_, upper),
        gfx::SizeF(intercept.end_ - intercept.begin_, stripe_width));
    // We need to ensure the clip rectangle is covering the full underline
    // extent. For horizontal drawing, using enclosingIntRect would be
    // sufficient, since we can clamp to full device pixels that way. However,
    // for vertical drawing, we have a transformation applied, which breaks the
    // integers-equal-device pixels assumption, so vertically inflating by 1
    // pixel makes sure we're always covering. This should only be done on the
    // clipping rectangle, not when computing the glyph intersects.
    clip_rect.Outset(gfx::OutsetsF::VH(1.0, dilation));

    if (!gfx::RectFToSkRect(clip_rect).isFinite()) {
      continue;
    }
    graphics_context_.ClipOut(clip_rect);
  }
}

void TextPainter::PaintSvgTextFragment(
    const TextFragmentPaintInfo& fragment_paint_info,
    DOMNodeId node_id,
    const AutoDarkMode& auto_dark_mode) {
  SvgPaints paints;
  const SvgTextPaintState& state = svg_text_paint_state_.value();
  PrepareSvgPaints(state, svg_context_paints_, SvgPaintMode::kText, paints);

  const OrderedPaints ordered_paints =
      OrderPaints(paints, state.Style().PaintOrder());
  DrawPaintOrderPasses(ordered_paints, [&](const cc::PaintFlags& flags) {
    graphics_context_.DrawText(font_, fragment_paint_info,
                               gfx::PointF(text_origin_), flags, node_id,
                               auto_dark_mode);
  });
}

TextPainter::SvgTextPaintState& TextPainter::SetSvgState(
    const LayoutSVGInlineText& svg_inline_text,
    const ComputedStyle& style,
    StyleVariant style_variant,
    PaintFlags paint_flags) {
  return svg_text_paint_state_.emplace(svg_inline_text, style, style_variant,
                                       paint_flags);
}

TextPainter::SvgTextPaintState& TextPainter::SetSvgState(
    const LayoutSVGInlineText& svg_inline_text,
    const ComputedStyle& style,
    Color text_match_color) {
  return svg_text_paint_state_.emplace(svg_inline_text, style,
                                       text_match_color);
}

TextPainter::SvgTextPaintState* TextPainter::GetSvgState() {
  return base::OptionalToPtr(svg_text_paint_state_);
}

// static
Color TextPainter::TextColorForWhiteBackground(Color text_color) {
  int distance_from_white = DifferenceSquared(text_color, Color::kWhite);
  // semi-arbitrarily chose 65025 (255^2) value here after a few tests;
  return distance_from_white > 65025 ? text_color : text_color.Dark();
}

// static
TextPaintStyle TextPainter::TextPaintingStyle(const Document& document,
                                              const ComputedStyle& style,
                                              const PaintInfo& paint_info) {
  TextPaintStyle text_style;
  text_style.stroke_width = style.TextStrokeWidth();
  text_style.color_scheme = style.UsedColorScheme();

  if (paint_info.phase == PaintPhase::kTextClip) {
    // When we use the text as a clip, we only care about the alpha, thus we
    // make all the colors black.
    text_style.current_color = Color::kBlack;
    text_style.fill_color = Color::kBlack;
    text_style.stroke_color = Color::kBlack;
    text_style.emphasis_mark_color = Color::kBlack;
    text_style.shadow = nullptr;
    text_style.paint_order = kPaintOrderNormal;
  } else {
    text_style.current_color =
        style.VisitedDependentColorFast(GetCSSPropertyColor());
    text_style.fill_color =
        style.VisitedDependentColorFast(GetCSSPropertyWebkitTextFillColor());
    text_style.stroke_color =
        style.VisitedDependentColorFast(GetCSSPropertyWebkitTextStrokeColor());
    text_style.emphasis_mark_color =
        style.VisitedDependentColorFast(GetCSSPropertyTextEmphasisColor());
    text_style.shadow = style.TextShadow();
    text_style.paint_order = style.PaintOrder();

    // Adjust text color when printing with a white background.
    bool force_background_to_white =
        BoxPainterBase::ShouldForceWhiteBackgroundForPrintEconomy(document,
                                                                  style);
    if (force_background_to_white) {
      text_style.fill_color =
          TextColorForWhiteBackground(text_style.fill_color);
      text_style.stroke_color =
          TextColorForWhiteBackground(text_style.stroke_color);
      text_style.emphasis_mark_color =
          TextColorForWhiteBackground(text_style.emphasis_mark_color);
    }
  }

  return text_style;
}

TextPainter::SvgTextPaintState::SvgTextPaintState(
    const LayoutSVGInlineText& layout_svg_inline_text,
    const ComputedStyle& style,
    StyleVariant style_variant,
    PaintFlags paint_flags)
    : layout_svg_inline_text_(layout_svg_inline_text),
      style_(style),
      style_variant_(style_variant),
      paint_flags_(paint_flags) {}

TextPainter::SvgTextPaintState::SvgTextPaintState(
    const LayoutSVGInlineText& layout_svg_inline_text,
    const ComputedStyle& style,
    Color text_match_color)
    : layout_svg_inline_text_(layout_svg_inline_text),
      style_(style),
      text_match_color_(text_match_color) {}

const LayoutSVGInlineText& TextPainter::SvgTextPaintState::InlineText() const {
  return layout_svg_inline_text_;
}

const LayoutObject& TextPainter::SvgTextPaintState::TextDecorationObject()
    const {
  // Lookup the first LayoutObject in parent hierarchy which has text-decoration
  // set.
  const LayoutObject* result = InlineText().Parent();
  while (result) {
    if (style_variant_ == StyleVariant::kFirstLine) {
      if (const ComputedStyle* style = result->FirstLineStyle()) {
        if (style->GetTextDecorationLine() != TextDecorationLine::kNone) {
          break;
        }
      }
    }
    if (const ComputedStyle* style = result->Style()) {
      if (style->GetTextDecorationLine() != TextDecorationLine::kNone) {
        break;
      }
    }

    result = result->Parent();
  }

  DCHECK(result);
  return *result;
}

const ComputedStyle& TextPainter::SvgTextPaintState::Style() const {
  return style_;
}

bool TextPainter::SvgTextPaintState::IsPaintingSelection() const {
  return is_painting_selection_;
}

PaintFlags TextPainter::SvgTextPaintState::GetPaintFlags() const {
  return paint_flags_;
}

bool TextPainter::SvgTextPaintState::IsRenderingClipPathAsMaskImage() const {
  return paint_flags_ & PaintFlag::kPaintingClipPathAsMask;
}

bool TextPainter::SvgTextPaintState::IsPaintingTextMatch() const {
  return text_match_color_.has_value();
}

Color TextPainter::SvgTextPaintState::TextMatchColor() const {
  return *text_match_color_;
}

AffineTransform& TextPainter::SvgTextPaintState::EnsureShaderTransform() {
  return shader_transform_ ? shader_transform_.value()
                           : shader_transform_.emplace();
}

const AffineTransform* TextPainter::SvgTextPaintState::GetShaderTransform()
    const {
  return base::OptionalToPtr(shader_transform_);
=======
  DecorationsStripeIntercepts(upper, stripe_width, dilation, text_intercepts);
>>>>>>> chromium
}

}  // namespace blink
