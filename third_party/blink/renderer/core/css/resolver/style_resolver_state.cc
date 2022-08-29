/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011 Apple Inc.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "third_party/blink/renderer/core/css/resolver/style_resolver_state.h"

#include "third_party/blink/public/mojom/use_counter/metrics/web_feature.mojom-blink.h"
#include "third_party/blink/renderer/core/animation/css/css_animations.h"
#include "third_party/blink/renderer/core/css/css_light_dark_value_pair.h"
#include "third_party/blink/renderer/core/css/css_property_value_set.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver.h"
#include "third_party/blink/renderer/core/dom/flat_tree_traversal.h"
#include "third_party/blink/renderer/core/dom/node.h"
#include "third_party/blink/renderer/core/dom/pseudo_element.h"
#include "third_party/blink/renderer/core/style/computed_style.h"

namespace blink {

namespace {

bool CanCacheBaseStyle(const StyleRequest& style_request) {
  return style_request.IsPseudoStyleRequest() ||
         (!style_request.parent_override &&
          !style_request.layout_parent_override &&
          style_request.matching_behavior == kMatchAllRules);
}

}  // namespace

StyleResolverState::StyleResolverState(
    Document& document,
    Element& element,
    const StyleRecalcContext* style_recalc_context,
    const StyleRequest& style_request)
    : element_context_(element),
      document_(&document),
      css_to_length_conversion_data_(&element),
      parent_style_(style_request.parent_override),
      layout_parent_style_(style_request.layout_parent_override),
      pseudo_request_type_(style_request.type),
      font_builder_(&document),
      pseudo_element_(
          element.GetNestedPseudoElement(style_request.pseudo_id,
                                         style_request.pseudo_argument)),
      element_style_resources_(GetElement(),
                               document.DevicePixelRatio(),
                               pseudo_element_),
      element_type_(style_request.IsPseudoStyleRequest()
                        ? ElementType::kPseudoElement
                        : ElementType::kElement),
<<<<<<< HEAD
      container_unit_context_(style_recalc_context
                                  ? style_recalc_context->container
                                  : FlatTreeTraversal::ParentElement(element)),
      anchor_evaluator_(style_recalc_context
                            ? style_recalc_context->anchor_evaluator
                            : nullptr),
      originating_element_style_(style_request.originating_element_style),
      is_for_highlight_(IsHighlightPseudoElement(style_request.pseudo_id)),
      uses_highlight_pseudo_inheritance_(
          ::blink::UsesHighlightPseudoInheritance(style_request.pseudo_id)),
      is_outside_flat_tree_(style_recalc_context
                                ? style_recalc_context->is_outside_flat_tree
                                : false),
      can_trigger_animations_(style_request.can_trigger_animations) {
=======
      nearest_container_(style_recalc_context.container),
      can_cache_base_style_(blink::CanCacheBaseStyle(style_request)) {
>>>>>>> chromium
  DCHECK(!!parent_style_ == !!layout_parent_style_);

  if (!parent_style_) {
    parent_style_ = element_context_.ParentStyle();
  }

  if (!layout_parent_style_)
    layout_parent_style_ = element_context_.LayoutParentStyle();

  if (!layout_parent_style_)
    layout_parent_style_ = parent_style_;

  DCHECK(document.IsActive());

  if (UsesHighlightPseudoInheritance())
    DCHECK(originating_element_style_);
}

StyleResolverState::~StyleResolverState() {
  // For performance reasons, explicitly clear HeapVectors and
  // HeapHashMaps to avoid giving a pressure on Oilpan's GC.
  animation_update_.Clear();
}

void StyleResolverState::SetStyle(scoped_refptr<ComputedStyle> style) {
  // FIXME: Improve RAII of StyleResolverState to remove this function.
  style_ = std::move(style);
  UpdateLengthConversionData();
}

scoped_refptr<ComputedStyle> StyleResolverState::TakeStyle() {
  if (had_no_matched_properties_ &&
      pseudo_request_type_ == StyleRequest::kForRenderer) {
    return nullptr;
  }
<<<<<<< HEAD
  return style_builder_->TakeStyle();
}

void StyleResolverState::UpdateLengthConversionData() {
  css_to_length_conversion_data_ = CSSToLengthConversionData(
      *style_builder_, ParentStyle(), RootElementStyle(),
      GetDocument().GetStyleEngine().GetViewportSize(),
      CSSToLengthConversionData::ContainerSizes(container_unit_context_),
      CSSToLengthConversionData::AnchorData(
          anchor_evaluator_, StyleBuilder().PositionAnchor(),
          StyleBuilder().PositionAreaOffsets()),
      StyleBuilder().EffectiveZoom(), length_conversion_flags_, &GetElement());
  element_style_resources_.UpdateLengthConversionData(
      &css_to_length_conversion_data_);
=======
  return std::move(style_);
>>>>>>> chromium
}

void StyleResolverState::UpdateLengthConversionData() {
  css_to_length_conversion_data_ = CSSToLengthConversionData(
      Style(), RootElementStyle(), GetDocument().GetLayoutView(),
      CSSToLengthConversionData::ContainerSizes(container_unit_context_),
      Style()->EffectiveZoom());
  element_style_resources_.UpdateLengthConversionData(
      &css_to_length_conversion_data_);
}

CSSToLengthConversionData StyleResolverState::UnzoomedLengthConversionData(
    const ComputedStyle* font_style) const {
  float em = font_style->SpecifiedFontSize();
  float rem = RootElementStyle() ? RootElementStyle()->SpecifiedFontSize() : 1;
  CSSToLengthConversionData::FontSizes font_sizes(
      em, rem, &font_style->GetFont(), font_style->EffectiveZoom());
  CSSToLengthConversionData::ViewportSize viewport_size(
      GetDocument().GetLayoutView());
<<<<<<< HEAD
  CSSToLengthConversionData::ContainerSizes container_sizes(
      container_unit_context_);
  CSSToLengthConversionData::AnchorData anchor_data(
      anchor_evaluator_, StyleBuilder().PositionAnchor(),
      StyleBuilder().PositionAreaOffsets());
  return CSSToLengthConversionData(StyleBuilder().GetWritingMode(), font_sizes,
                                   line_height_size, viewport_size,
                                   container_sizes, anchor_data, 1,
                                   length_conversion_flags_, &GetElement());
=======
  CSSToLengthConversionData::ContainerSizes container_sizes(nearest_container_);

  return CSSToLengthConversionData(Style(), font_sizes, viewport_size,
                                   container_sizes, 1);
>>>>>>> chromium
}

CSSToLengthConversionData StyleResolverState::FontSizeConversionData() const {
  return UnzoomedLengthConversionData(ParentStyle());
}

CSSToLengthConversionData StyleResolverState::UnzoomedLengthConversionData()
    const {
  return UnzoomedLengthConversionData(Style());
}

void StyleResolverState::SetParentStyle(
    scoped_refptr<const ComputedStyle> parent_style) {
  parent_style_ = std::move(parent_style);
}

void StyleResolverState::EnsureParentStyle() {
  if (!ParentStyle()) {
    SetParentStyle(StyleResolver(GetDocument()).InitialStyleForElement());
    SetLayoutParentStyle(ParentStyle());
  }
}

void StyleResolverState::SetLayoutParentStyle(
    scoped_refptr<const ComputedStyle> parent_style) {
  layout_parent_style_ = std::move(parent_style);
}

void StyleResolverState::LoadPendingResources() {
  if (pseudo_request_type_ == StyleRequest::kForComputedStyle ||
      (ParentStyle() && ParentStyle()->IsEnsuredInDisplayNone()) ||
      (StyleRef().Display() == EDisplay::kNone &&
       !GetElement().LayoutObjectIsNeeded(StyleRef())) ||
      StyleRef().IsEnsuredOutsideFlatTree()) {
    return;
  }
<<<<<<< HEAD
  if (StyleBuilder().Display() == EDisplay::kNone && GetStyledElement() &&
      !GetStyledElement()->LayoutObjectIsNeeded(
          style_builder_->GetDisplayStyle())) {
    // Don't load resources for display:none elements unless we are animating
    // display. If we are animating display, we might otherwise have ended up
    // caching a base style with pending images.
    Element* animating_element = GetAnimatingElement();
    if (!animating_element || !CSSAnimations::IsAnimatingDisplayProperty(
                                  animating_element->GetElementAnimations())) {
      return;
    }
  }
=======
>>>>>>> chromium

  if (StyleRef().StyleType() == kPseudoIdTargetText) {
    // Do not load any resources for ::target-text since that could leak text
    // content to external stylesheets.
    return;
  }

<<<<<<< HEAD
  element_style_resources_.LoadPendingResources(StyleBuilder(),
                                                css_to_length_conversion_data_);
=======
  element_style_resources_.LoadPendingResources(StyleRef());
>>>>>>> chromium
}

const FontDescription& StyleResolverState::ParentFontDescription() const {
  return parent_style_->GetFontDescription();
}

void StyleResolverState::SetZoom(float f) {
  float parent_effective_zoom = ParentStyle()
                                    ? ParentStyle()->EffectiveZoom()
                                    : ComputedStyleInitialValues::InitialZoom();

  style_->SetZoom(f);

  if (f != 1.f)
    GetDocument().CountUse(WebFeature::kCascadedCSSZoomNotEqualToOne);

  if (style_->SetEffectiveZoom(parent_effective_zoom * f))
    font_builder_.DidChangeEffectiveZoom();
}

void StyleResolverState::SetEffectiveZoom(float f) {
  if (style_->SetEffectiveZoom(f))
    font_builder_.DidChangeEffectiveZoom();
}

void StyleResolverState::SetWritingMode(WritingMode new_writing_mode) {
  if (style_->GetWritingMode() == new_writing_mode) {
    return;
  }
  style_->SetWritingMode(new_writing_mode);
  UpdateLengthConversionData();
  font_builder_.DidChangeWritingMode();
}

void StyleResolverState::SetTextOrientation(ETextOrientation text_orientation) {
  if (style_->GetTextOrientation() != text_orientation) {
    style_->SetTextOrientation(text_orientation);
    font_builder_.DidChangeTextOrientation();
  }
}

CSSParserMode StyleResolverState::GetParserMode() const {
  return GetDocument().InQuirksMode() ? kHTMLQuirksMode : kHTMLStandardMode;
}

Element* StyleResolverState::GetAnimatingElement() const {
  if (element_type_ == ElementType::kElement)
    return &GetElement();
  DCHECK_EQ(ElementType::kPseudoElement, element_type_);
  return pseudo_element_;
}

PseudoElement* StyleResolverState::GetPseudoElement() const {
  return element_type_ == ElementType::kPseudoElement ? pseudo_element_
                                                      : nullptr;
}

const CSSValue& StyleResolverState::ResolveLightDarkPair(
    const CSSProperty& property,
    const CSSValue& value) {
  if (const auto* pair = DynamicTo<CSSLightDarkValuePair>(value)) {
    if (!property.IsInherited())
      Style()->SetHasNonInheritedLightDarkValue();
    if (Style()->UsedColorScheme() == mojom::blink::ColorScheme::kLight)
      return pair->First();
    return pair->Second();
  }
  return value;
}

}  // namespace blink
