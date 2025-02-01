// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_PAINT_TEXT_PAINTER_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_PAINT_TEXT_PAINTER_H_

#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/paint/text_painter_base.h"
#include "third_party/blink/renderer/platform/graphics/dom_node_id.h"

namespace blink {

class TextDecorationOffsetBase;
class TextRun;
struct TextRunPaintInfo;
class LayoutTextCombine;

// Text painter for legacy layout. Operates on TextRuns.
class CORE_EXPORT TextPainter : public TextPainterBase {
  STACK_ALLOCATED();

 public:
  TextPainter(GraphicsContext& context,
              const Font& font,
<<<<<<< HEAD
              std::optional<AffineTransform> rotation,
              const gfx::Rect& visual_rect,
              const LineRelativeOffset& text_origin,
              bool horizontal)
      : graphics_context_(context),
        svg_context_paints_(svg_context_paints),
        font_(font),
        rotation_(rotation),
        visual_rect_(visual_rect),
        text_origin_(text_origin),
        horizontal_(horizontal) {}
=======
              const TextRun& run,
              const PhysicalOffset& text_origin,
              const PhysicalRect& text_frame_rect,
              bool horizontal)
      : TextPainterBase(context,
                        font,
                        text_origin,
                        text_frame_rect,
                        horizontal),
        run_(run) {}
>>>>>>> chromium
  ~TextPainter() = default;

  void SetCombinedText(LayoutTextCombine* combined_text) {
    combined_text_ = combined_text;
  }

  void ClipDecorationsStripe(float upper,
                             float stripe_width,
                             float dilation) override;
  void Paint(unsigned start_offset,
             unsigned end_offset,
             unsigned length,
             const TextPaintStyle&,
             DOMNodeId node_id);

<<<<<<< HEAD
  void PaintSelectedText(const TextFragmentPaintInfo& fragment_paint_info,
                         unsigned selection_start,
                         unsigned selection_end,
                         const TextPaintStyle& text_style,
                         const TextPaintStyle& selection_style,
                         const LineRelativeRect& selection_rect,
                         DOMNodeId node_id,
                         const AutoDarkMode& auto_dark_mode);

  void PaintDecorationLine(const TextDecorationInfo& decoration_info,
                           const Color& line_color,
                           const TextFragmentPaintInfo* fragment_paint_info);

  SvgTextPaintState& SetSvgState(const LayoutSVGInlineText&,
                                 const ComputedStyle&,
                                 StyleVariant style_variant,
                                 PaintFlags paint_flags);
  SvgTextPaintState& SetSvgState(const LayoutSVGInlineText& svg_inline_text,
                                 const ComputedStyle& style,
                                 Color text_match_color);
  SvgTextPaintState* GetSvgState();

  static Color TextColorForWhiteBackground(Color);

  static TextPaintStyle TextPaintingStyle(const Document&,
                                          const ComputedStyle&,
                                          const PaintInfo&);

  void SetEmphasisMark(const AtomicString&, TextEmphasisPosition);

  gfx::RectF VisualRectInLocalSpace() const;

 protected:
  const Font& font() const { return font_; }
  const LineRelativeOffset& text_origin() const { return text_origin_; }
  const AtomicString& emphasis_mark() const { return emphasis_mark_; }
  int emphasis_mark_offset() const { return emphasis_mark_offset_; }
  GraphicsContext& graphics_context() const { return graphics_context_; }
=======
  void PaintDecorationsExceptLineThrough(const TextDecorationOffsetBase&,
                                         TextDecorationInfo&,
                                         const PaintInfo&,
                                         const Vector<AppliedTextDecoration>&,
                                         const TextPaintStyle& text_style,
                                         bool* has_line_through_decoration);
  void PaintDecorationsOnlyLineThrough(TextDecorationInfo&,
                                       const PaintInfo&,
                                       const Vector<AppliedTextDecoration>&,
                                       const TextPaintStyle&);
>>>>>>> chromium

 private:
  template <PaintInternalStep step>
  void PaintInternalRun(TextRunPaintInfo&,
                        unsigned from,
                        unsigned to,
                        DOMNodeId node_id);

  template <PaintInternalStep step>
  void PaintInternal(unsigned start_offset,
                     unsigned end_offset,
                     unsigned truncation_point,
                     DOMNodeId node_id);

<<<<<<< HEAD
  GraphicsContext& graphics_context_;
  const SvgContextPaints* svg_context_paints_;
  const Font& font_;
  std::optional<AffineTransform> rotation_;
  const gfx::Rect visual_rect_;
  const LineRelativeOffset text_origin_;
  const bool horizontal_;
  std::optional<SvgTextPaintState> svg_text_paint_state_;
  AtomicString emphasis_mark_;
  int emphasis_mark_offset_ = 0;
=======
  const TextRun& run_;
  LayoutTextCombine* combined_text_ = nullptr;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_PAINT_TEXT_PAINTER_H_
