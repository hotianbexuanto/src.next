/*
 * Copyright (C) 2013 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CSS_TO_LENGTH_CONVERSION_DATA_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CSS_TO_LENGTH_CONVERSION_DATA_H_

#include <limits>
#include "third_party/abseil-cpp/absl/types/optional.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/css/css_primitive_value.h"
#include "third_party/blink/renderer/core/layout/geometry/axis.h"
#include "third_party/blink/renderer/platform/geometry/double_size.h"
#include "third_party/blink/renderer/platform/text/writing_mode.h"
#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"
#include "third_party/blink/renderer/platform/wtf/gc_plugin.h"
#include "third_party/blink/renderer/platform/wtf/math_extras.h"

namespace blink {

class ComputedStyle;
class LayoutView;
class Font;
class Element;

class CORE_EXPORT CSSToLengthConversionData {
  STACK_ALLOCATED();

 public:
  class CORE_EXPORT FontSizes {
    DISALLOW_NEW();

   public:
    FontSizes() : em_(0), rem_(0), font_(nullptr), zoom_(1) {}
    FontSizes(float em, float rem, const Font*, float zoom);
    FontSizes(const ComputedStyle*, const ComputedStyle* root_style);

    float Em() const { return em_; }
    float Rem() const { return rem_; }
    float Zoom() const;
    float Ex() const;
    float Ch() const;

   private:
<<<<<<< HEAD
    float em_ = 0;
    float rem_ = 0;
    GC_PLUGIN_IGNORE("GC API violation: https://crbug.com/389707046")
    const Font* font_ = nullptr;
    GC_PLUGIN_IGNORE("GC API violation: https://crbug.com/389707046")
    const Font* root_font_ = nullptr;
    // Font-metrics-based units (ex, ch, ic) are pre-zoomed by a factor of
    // `font_zoom_`.
    float font_zoom_ = 1;
    float root_font_zoom_ = 1;
  };

  class CORE_EXPORT LineHeightSize {
    DISALLOW_NEW();

   public:
    LineHeightSize() = default;
    LineHeightSize(const Length& line_height, const Font* font, float font_zoom)
        : line_height_(line_height), font_(font), font_zoom_(font_zoom) {}
    LineHeightSize(const Length& line_height,
                   const Length& root_line_height,
                   const Font* font,
                   const Font* root_font,
                   float font_zoom,
                   float root_font_zoom)
        : line_height_(line_height),
          root_line_height_(root_line_height),
          font_(font),
          root_font_(root_font),
          font_zoom_(font_zoom),
          root_font_zoom_(root_font_zoom) {}
    LineHeightSize(const FontSizeStyle& style, const ComputedStyle* root_style);

    float Lh(float zoom) const;
    float Rlh(float zoom) const;

   private:
    Length line_height_;
    Length root_line_height_;
    // Note that this Font may be different from the instance held
    // by FontSizes (for the same CSSToLengthConversionData object).
    GC_PLUGIN_IGNORE("GC API violation: https://crbug.com/389707046")
    const Font* font_ = nullptr;
    GC_PLUGIN_IGNORE("GC API violation: https://crbug.com/389707046")
    const Font* root_font_ = nullptr;
    // Like ex/ch/ic, lh is also based on font-metrics and is pre-zoomed by
    // a factor of `font_zoom_`.
    float font_zoom_ = 1;
    float root_font_zoom_ = 1;
=======
    float em_;
    float rem_;
    const Font* font_;
    float zoom_;
>>>>>>> chromium
  };

  class CORE_EXPORT ViewportSize {
    DISALLOW_NEW();

   public:
    ViewportSize() = default;
    ViewportSize(double width, double height) : size_(width, height) {}
    explicit ViewportSize(const LayoutView*);

    double Width() const { return size_.Width(); }
    double Height() const { return size_.Height(); }

   private:
    DoubleSize size_;
  };

  class CORE_EXPORT ContainerSizes {
    STACK_ALLOCATED();

   public:
    ContainerSizes() = default;
    explicit ContainerSizes(Element* nearest_container)
        : nearest_container_(nearest_container) {}

    absl::optional<double> Width() const;
    absl::optional<double> Height() const;
    absl::optional<double> InlineSize() const;
    absl::optional<double> BlockSize() const;

   private:
    void CacheSizeIfNeeded(LogicalAxes, absl::optional<double>& cache) const;
    void CacheSizeIfNeeded(PhysicalAxes, absl::optional<double>& cache) const;

    Element* nearest_container_{nullptr};
    mutable PhysicalAxes cached_physical_axes_{kPhysicalAxisNone};
    mutable LogicalAxes cached_logical_axes_{kLogicalAxisNone};
    mutable absl::optional<double> cached_width_;
    mutable absl::optional<double> cached_height_;
    mutable absl::optional<double> cached_inline_size_;
    mutable absl::optional<double> cached_block_size_;
  };

<<<<<<< HEAD
  using Flags = uint32_t;

  // Flags represent the units seen in a conversion. They are used for targeted
  // invalidation, e.g. when root font-size changes, only elements dependent on
  // rem units are recalculated.
  enum class Flag : Flags {
    // em
    kEm = 1u << 0,
    // rem
    kRootFontRelative = 1u << 1,
    // ex, ch, ic, lh, cap, rcap
    kGlyphRelative = 1u << 2,
    // rex, rch, ric have both kRootFontRelative and kGlyphRelative
    // v*
    kViewport = 1u << 3,
    // sv*, lv*
    kSmallLargeViewport = 1u << 4,
    // dv*
    kDynamicViewport = 1u << 5,
    // cq*
    kContainerRelative = 1u << 6,
    // https://drafts.csswg.org/css-scoping-1/#css-tree-scoped-reference
    kTreeScopedReference = 1u << 7,
    // vi, vb, cqi, cqb, etc
    kLogicalDirectionRelative = 1u << 8,
    // anchor(), anchor-size()
    // https://drafts.csswg.org/css-anchor-position-1
    kAnchorRelative = 1u << 9,
    // cap
    kCapRelative = 1u << 10,
    // rcap
    kRcapRelative = 1u << 11,
    // ic
    kIcRelative = 1u << 12,
    // ric
    kRicRelative = 1u << 13,
    // lh
    kLhRelative = 1u << 14,
    // rlh
    kRlhRelative = 1u << 15,
    // ch
    kChRelative = 1u << 16,
    // rch
    kRchRelative = 1u << 17,
    // rex
    kRexRelative = 1u << 18,
    // sibling-index(), sibling-count()
    kSiblingRelative = 1u << 19,
    // Adjust the Flags type above if adding more bits below.
  };

  explicit CSSToLengthConversionData(const Element* element)
      : CSSLengthResolver(1 /* zoom */), element_(element) {}
  CSSToLengthConversionData(WritingMode,
=======
  CSSToLengthConversionData() : style_(nullptr), zoom_(1) {}
  CSSToLengthConversionData(const ComputedStyle*,
>>>>>>> chromium
                            const FontSizes&,
                            const ViewportSize&,
                            const ContainerSizes&,
<<<<<<< HEAD
                            const AnchorData&,
                            float zoom,
                            Flags&,
                            const Element*);
  template <typename ComputedStyleOrBuilder>
  CSSToLengthConversionData(const ComputedStyleOrBuilder& element_style,
                            const ComputedStyle* parent_style,
                            const ComputedStyle* root_style,
                            const ViewportSize& viewport_size,
                            const ContainerSizes& container_sizes,
                            const AnchorData& anchor_data,
                            float zoom,
                            Flags& flags,
                            const Element* element)
      : CSSToLengthConversionData(
            element_style.GetWritingMode(),
            FontSizes(element_style.GetFontSizeStyle(), root_style),
            LineHeightSize(parent_style ? parent_style->GetFontSizeStyle()
                                        : element_style.GetFontSizeStyle(),
                           root_style),
            viewport_size,
            container_sizes,
            anchor_data,
            zoom,
            flags,
            element) {}
=======
                            float zoom);
  CSSToLengthConversionData(const ComputedStyle* curr_style,
                            const ComputedStyle* root_style,
                            const LayoutView*,
                            Element* nearest_container,
                            float zoom);
>>>>>>> chromium

  float Zoom() const { return zoom_; }

  float EmFontSize() const;
  float RemFontSize() const;
  float ExFontSize() const;
  float ChFontSize() const;
  float FontSizeZoom() const { return font_sizes_.Zoom(); }

  // Accessing these marks the style as having viewport units
  double ViewportWidthPercent() const;
  double ViewportHeightPercent() const;
  double ViewportMinPercent() const;
  double ViewportMaxPercent() const;

  // Accessing these marks the style as having container relative units.
  double ContainerWidthPercent() const;
  double ContainerHeightPercent() const;
  double ContainerInlineSizePercent() const;
  double ContainerBlockSizePercent() const;
  double ContainerMinPercent() const;
  double ContainerMaxPercent() const;

  void SetFontSizes(const FontSizes& font_sizes) { font_sizes_ = font_sizes; }
  void SetZoom(float zoom) {
    DCHECK(std::isfinite(zoom));
    DCHECK_GT(zoom, 0);
    zoom_ = zoom;
  }
  void SetContainerSizes(const ContainerSizes& container_sizes) {
    container_sizes_ = container_sizes;
  }

<<<<<<< HEAD
  void ReferenceAnchor() const override;
  void ReferenceSibling() const override;

  AnchorEvaluator* GetAnchorEvaluator() const override {
    return anchor_data_.GetEvaluator();
  }
  const ScopedCSSName* GetPositionAnchor() const override {
    return anchor_data_.GetPositionAnchor();
  }
  std::optional<PositionAreaOffsets> GetPositionAreaOffsets() const override {
    return anchor_data_.GetPositionAreaOffsets();
  }

  const Element* GetElement() const override { return element_; }

  // See ContainerSizes::PreCachedCopy.
  //
  // Calling this function will mark the associated ComputedStyle as
  // dependent on container-relative units.
  ContainerSizes PreCachedContainerSizesCopy() const;

  CSSToLengthConversionData CopyWithAdjustedZoom(float new_zoom) const {
    DCHECK(flags_);
    return CSSToLengthConversionData(
        writing_mode_, font_sizes_, line_height_size_, viewport_size_,
        container_sizes_, anchor_data_, new_zoom, *flags_, element_);
  }
  CSSToLengthConversionData Unzoomed() const {
    return CopyWithAdjustedZoom(1.0f);
=======
  CSSToLengthConversionData CopyWithAdjustedZoom(float new_zoom) const {
    return CSSToLengthConversionData(style_, font_sizes_, viewport_size_,
                                     container_sizes_, new_zoom);
>>>>>>> chromium
  }

  double ZoomedComputedPixels(double value, CSSPrimitiveValue::UnitType) const;

 private:
  const ComputedStyle* style_;
  FontSizes font_sizes_;
  ViewportSize viewport_size_;
  ContainerSizes container_sizes_;
<<<<<<< HEAD
  AnchorData anchor_data_;
  mutable Flags* flags_ = nullptr;
  const Element* element_;
=======
  float zoom_;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CSS_TO_LENGTH_CONVERSION_DATA_H_
