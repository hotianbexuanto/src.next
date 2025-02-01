/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 2004-2005 Allan Sandfeld Jensen (kde@carewolf.com)
 * Copyright (C) 2006, 2007 Nicholas Shanks (webkit@nickshanks.com)
 * Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013 Apple Inc.
 * All rights reserved.
 * Copyright (C) 2007 Alexey Proskuryakov <ap@webkit.org>
 * Copyright (C) 2007, 2008 Eric Seidel <eric@webkit.org>
 * Copyright (C) 2008, 2009 Torch Mobile Inc. All rights reserved.
 * (http://www.torchmobile.com/)
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 * Copyright (C) Research In Motion Limited 2011. All rights reserved.
 * Copyright (C) 2012 Google Inc. All rights reserved.
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
 */

#include "third_party/blink/renderer/core/css/resolver/style_resolver.h"

#include "third_party/blink/public/mojom/web_feature/web_feature.mojom-blink.h"
#include "third_party/blink/renderer/core/animation/css/compositor_keyframe_value_factory.h"
#include "third_party/blink/renderer/core/animation/css/css_animations.h"
#include "third_party/blink/renderer/core/animation/document_animations.h"
#include "third_party/blink/renderer/core/animation/element_animations.h"
#include "third_party/blink/renderer/core/animation/invalidatable_interpolation.h"
#include "third_party/blink/renderer/core/css/container_query_evaluator.h"
#include "third_party/blink/renderer/core/css/css_default_style_sheets.h"
#include "third_party/blink/renderer/core/css/css_font_selector.h"
#include "third_party/blink/renderer/core/css/css_identifier_value.h"
#include "third_party/blink/renderer/core/css/css_initial_color_value.h"
#include "third_party/blink/renderer/core/css/css_keyframe_rule.h"
#include "third_party/blink/renderer/core/css/css_keyframes_rule.h"
#include "third_party/blink/renderer/core/css/css_property_names.h"
#include "third_party/blink/renderer/core/css/css_rule_list.h"
#include "third_party/blink/renderer/core/css/css_selector.h"
#include "third_party/blink/renderer/core/css/css_selector_watch.h"
#include "third_party/blink/renderer/core/css/css_style_declaration.h"
#include "third_party/blink/renderer/core/css/css_style_rule.h"
#include "third_party/blink/renderer/core/css/element_rule_collector.h"
#include "third_party/blink/renderer/core/css/font_face.h"
#include "third_party/blink/renderer/core/css/page_rule_collector.h"
#include "third_party/blink/renderer/core/css/part_names.h"
#include "third_party/blink/renderer/core/css/properties/computed_style_utils.h"
#include "third_party/blink/renderer/core/css/properties/css_property.h"
#include "third_party/blink/renderer/core/css/properties/css_property_ref.h"
#include "third_party/blink/renderer/core/css/resolver/match_result.h"
#include "third_party/blink/renderer/core/css/resolver/scoped_style_resolver.h"
#include "third_party/blink/renderer/core/css/resolver/selector_filter_parent_scope.h"
#include "third_party/blink/renderer/core/css/resolver/style_adjuster.h"
#include "third_party/blink/renderer/core/css/resolver/style_builder_converter.h"
#include "third_party/blink/renderer/core/css/resolver/style_cascade.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver_state.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver_stats.h"
#include "third_party/blink/renderer/core/css/resolver/style_rule_usage_tracker.h"
#include "third_party/blink/renderer/core/css/scoped_css_value.h"
#include "third_party/blink/renderer/core/css/style_engine.h"
#include "third_party/blink/renderer/core/css/style_rule_import.h"
#include "third_party/blink/renderer/core/css/style_sheet_contents.h"
#include "third_party/blink/renderer/core/dom/first_letter_pseudo_element.h"
#include "third_party/blink/renderer/core/dom/flat_tree_traversal.h"
#include "third_party/blink/renderer/core/dom/layout_tree_builder_traversal.h"
#include "third_party/blink/renderer/core/dom/shadow_root.h"
#include "third_party/blink/renderer/core/dom/space_split_string.h"
#include "third_party/blink/renderer/core/dom/text.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/frame/web_feature.h"
#include "third_party/blink/renderer/core/html/custom/custom_element_definition.h"
#include "third_party/blink/renderer/core/html/html_body_element.h"
#include "third_party/blink/renderer/core/html/html_iframe_element.h"
#include "third_party/blink/renderer/core/html/html_slot_element.h"
#include "third_party/blink/renderer/core/html/shadow/shadow_element_names.h"
#include "third_party/blink/renderer/core/html/track/text_track.h"
#include "third_party/blink/renderer/core/html/track/vtt/vtt_cue.h"
#include "third_party/blink/renderer/core/html/track/vtt/vtt_element.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/inspector/identifiers_factory.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/mathml/mathml_fraction_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_operator_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_padded_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_space_element.h"
#include "third_party/blink/renderer/core/mathml_names.h"
#include "third_party/blink/renderer/core/media_type_names.h"
#include "third_party/blink/renderer/core/page/page.h"
#include "third_party/blink/renderer/core/page/scrolling/snap_coordinator.h"
#include "third_party/blink/renderer/core/probe/core_probes.h"
#include "third_party/blink/renderer/core/style/style_initial_data.h"
#include "third_party/blink/renderer/core/style_property_shorthand.h"
#include "third_party/blink/renderer/core/svg/svg_element.h"
#include "third_party/blink/renderer/platform/heap/heap.h"
#include "third_party/blink/renderer/platform/instrumentation/use_counter.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/hash_set.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string_hash.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

namespace blink {

namespace {

<<<<<<< HEAD
bool IsPseudoElementWithUAStyle(PseudoId pseudo_id) {
  switch (pseudo_id) {
    case kPseudoIdMarker:
    case kPseudoIdScrollButtonBlockStart:
    case kPseudoIdScrollButtonInlineStart:
    case kPseudoIdScrollButtonInlineEnd:
    case kPseudoIdScrollButtonBlockEnd:
      return true;
    default:
      return false;
  }
}

bool ShouldStoreOldStyle(const StyleRecalcContext& style_recalc_context,
                         StyleResolverState& state) {
  // Storing the old style is only relevant if we risk computing the style
  // more than once for the same element. This can happen if we are currently
  // inside a size query container, or doing multiple style resolutions for
  // position-try-fallbacks.
  //
  // For anchored elements that generate pseudo elements, we also need to store
  // the old style for animating pseudo elements because style recalc for the
  // originating anchored elements will always update its pseudo elements,
  // causing the pseudo element styling to also have multiple passes.
  //
  // If we are not inside a size query container or an element with
  // position-try-fallbacks, we can fall back to the default behavior (in
  // CSSAnimations) of using the current style on Element as the old style.
  //
  // TODO(crbug.com/40943044): We also need to check whether we are a descendant
  // of an element with position-try-fallbacks to cover the case where the
  // descendant explicitly inherits insets or other valid @position-try
  // properties from the element with position-try-fallbacks. This applies to
  // descendants of elements with anchor queries as well.
  return (style_recalc_context.container ||
          state.StyleBuilder().HasAnchorFunctions() ||
          state.StyleBuilder().PositionAnchor() ||
          ((state.GetElement().IsPseudoElement() ||
            state.IsForPseudoElement()) &&
           (state.ParentStyle()->HasAnchorFunctions() ||
            state.ParentStyle()->PositionAnchor())) ||
          state.StyleBuilder().GetPositionTryFallbacks() != nullptr) &&
         state.CanAffectAnimations();
}

bool ShouldSetPendingUpdate(StyleResolverState& state, Element& element) {
  if (!state.AnimationUpdate().IsEmpty()) {
    return true;
  }
  // Even when the animation update is empty, we must still set the pending
  // update in order to clear PreviousActiveInterpolationsForAnimations.
  //
  // See CSSAnimations::MaybeApplyPendingUpdate
  if (const ElementAnimations* element_animations =
          element.GetElementAnimations()) {
    return element_animations->CssAnimations()
        .HasPreviousActiveInterpolationsForAnimations();
  }
  return false;
}

void SetAnimationUpdateIfNeeded(const StyleRecalcContext& style_recalc_context,
                                StyleResolverState& state,
                                Element& element) {
  if (auto* data = PostStyleUpdateScope::CurrentAnimationData()) {
    if (ShouldStoreOldStyle(style_recalc_context, state)) {
      data->StoreOldStyleIfNeeded(element);
    }
  }

=======
void SetAnimationUpdateIfNeeded(StyleResolverState& state, Element& element) {
>>>>>>> chromium
  // If any changes to CSS Animations were detected, stash the update away for
  // application after the layout object is updated if we're in the appropriate
  // scope.
  if (state.AnimationUpdate().IsEmpty())
    return;

  auto& element_animations = element.EnsureElementAnimations();
  auto& document_animations = state.GetDocument().GetDocumentAnimations();

  element_animations.CssAnimations().SetPendingUpdate(state.AnimationUpdate());

  if (RuntimeEnabledFeatures::CSSIsolatedAnimationUpdatesEnabled()) {
    if (document_animations.AnimationUpdatesAllowed()) {
      state.GetDocument()
          .GetDocumentAnimations()
          .AddElementWithPendingAnimationUpdate(element);
    }
  }
}

bool HasAnimationsOrTransitions(const StyleResolverState& state) {
  return state.Style()->Animations() || state.Style()->Transitions() ||
         (state.GetAnimatingElement() &&
          state.GetAnimatingElement()->HasAnimations());
}

bool ShouldComputeBaseComputedStyle(const ComputedStyle* base_computed_style) {
#if DCHECK_IS_ON()
  // The invariant in the base computed style optimization is that as long as
  // |IsAnimationStyleChange| is true, the computed style that would be
  // generated by the style resolver is equivalent to the one we hold
  // internally. To ensure this, we always compute a new style here disregarding
  // the fact that we have a base computed style when DCHECKs are enabled, and
  // call ComputeBaseComputedStyleDiff() to check that the optimization was
  // sound.
  return true;
#else
  return !base_computed_style;
#endif  // !DCHECK_IS_ON()
}

// Compare the base computed style with the one we compute to validate that the
// optimization is sound. A return value of g_null_atom means the diff was
// empty (which is what we want).
String ComputeBaseComputedStyleDiff(const ComputedStyle* base_computed_style,
                                    const ComputedStyle& computed_style) {
#if DCHECK_IS_ON()
  if (!base_computed_style)
    return g_null_atom;
  // Under certain conditions ComputedStyle::operator==() may return false for
  // differences that are permitted during an animation.
  // The FontFaceCache version number may be increased without forcing a style
  // recalc (see crbug.com/471079).
  if (!base_computed_style->GetFont().IsFallbackValid())
    return g_null_atom;
  // Images use instance equality rather than value equality (see
  // crbug.com/781461).
  for (CSSPropertyID id :
       {CSSPropertyID::kBackgroundImage, CSSPropertyID::kWebkitMaskImage}) {
    if (!CSSPropertyEquality::PropertiesEqual(
            PropertyHandle(CSSProperty::Get(id)), *base_computed_style,
            computed_style)) {
      return g_null_atom;
    }
  }

  if (*base_computed_style == computed_style)
    return g_null_atom;

  StringBuilder builder;
  builder.Append("Field diff: ");

  Vector<String> diff = base_computed_style->DebugDiffFields(computed_style);

  for (const String& s : diff) {
    builder.Append(s);
    builder.Append(" ");
  }

  return builder.ToString();
#else
  return g_null_atom;
#endif  // DCHECK_IS_ON()
}

// When force-computing the base computed style for validation purposes,
// we need to reset the StyleCascade when the base computed style optimization
// is used. This is because we don't want the computation of the base to
// populate the cascade, as they are supposed to be empty when the optimization
// is in use. This is to match the behavior of non-DCHECK builds.
void MaybeResetCascade(StyleCascade& cascade) {
#if DCHECK_IS_ON()
  cascade.Reset();
#endif  // DCHECK_IS_ON()
}

<<<<<<< HEAD
bool TextAutosizingMultiplierChanged(const StyleResolverState& state,
                                     const ComputedStyle& base_computed_style) {
  // Note that |old_style| can be a style replaced by
  // TextAutosizer::ApplyMultiplier.
  const ComputedStyle* old_style = state.GetElement().GetComputedStyle();
  return old_style && (old_style->TextAutosizingMultiplier() !=
                       base_computed_style.TextAutosizingMultiplier());
}

PseudoId GetPseudoId(const Element& element, ElementRuleCollector* collector) {
  if (element.IsPseudoElement()) {
    return element.GetPseudoIdForStyling();
  }

  return collector ? collector->GetPseudoId() : kPseudoIdNone;
}

void UseCountLegacyOverlapping(Document& document,
                               const ComputedStyle& a,
                               const ComputedStyleBuilder& b) {
  if (a.PerspectiveOrigin() != b.PerspectiveOrigin()) {
    document.CountUse(WebFeature::kCSSLegacyPerspectiveOrigin);
  }
  if (a.GetTransformOrigin() != b.GetTransformOrigin()) {
    document.CountUse(WebFeature::kCSSLegacyTransformOrigin);
  }
  if (a.BorderImage() != b.BorderImage()) {
    document.CountUse(WebFeature::kCSSLegacyBorderImage);
  }
  if ((a.BorderTopWidth() != b.BorderTopWidth()) ||
      (a.BorderRightWidth() != b.BorderRightWidth()) ||
      (a.BorderBottomWidth() != b.BorderBottomWidth()) ||
      (a.BorderLeftWidth() != b.BorderLeftWidth())) {
    document.CountUse(WebFeature::kCSSLegacyBorderImageWidth);
  }
}

void ApplyLengthConversionFlags(StyleResolverState& state) {
  using Flags = CSSToLengthConversionData::Flags;
  using Flag = CSSToLengthConversionData::Flag;

  Flags flags = state.TakeLengthConversionFlags();
  if (!flags) {
    return;
  }

  ComputedStyleBuilder& builder = state.StyleBuilder();

  if (flags & static_cast<Flags>(Flag::kEm)) {
    builder.SetHasEmUnits();
  }
  if (flags & static_cast<Flags>(Flag::kRootFontRelative)) {
    builder.SetHasRootFontRelativeUnits();
  }
  if (flags & static_cast<Flags>(Flag::kGlyphRelative)) {
    builder.SetHasGlyphRelativeUnits();
  }
  if (flags & (static_cast<Flags>(Flag::kViewport) |
               static_cast<Flags>(Flag::kSmallLargeViewport))) {
    builder.SetHasStaticViewportUnits();
  }
  if (flags & static_cast<Flags>(Flag::kDynamicViewport)) {
    builder.SetHasDynamicViewportUnits();
  }
  if (flags & (static_cast<Flags>(Flag::kDynamicViewport) |
               static_cast<Flags>(Flag::kSmallLargeViewport))) {
    UseCounter::CountWebDXFeature(state.GetDocument(),
                                  WebDXFeature::kViewportUnitVariants);
  }
  if (flags & static_cast<Flags>(Flag::kContainerRelative)) {
    builder.SetDependsOnSizeContainerQueries(true);
    builder.SetHasContainerRelativeUnits();
  }
  if (flags & static_cast<Flags>(Flag::kTreeScopedReference)) {
    state.SetHasTreeScopedReference();
  }
  if (flags & static_cast<Flags>(Flag::kAnchorRelative)) {
    builder.SetHasAnchorFunctions();
  }
  if (flags & static_cast<Flags>(Flag::kLogicalDirectionRelative)) {
    builder.SetHasLogicalDirectionRelativeUnits();
  }
  if (flags & static_cast<Flags>(Flag::kCapRelative)) {
    UseCounter::Count(state.GetDocument(), WebFeature::kHasCapUnits);
  }
  if (flags & static_cast<Flags>(Flag::kRcapRelative)) {
    UseCounter::Count(state.GetDocument(), WebFeature::kHasRcapUnits);
  }
  if (flags & static_cast<Flags>(Flag::kIcRelative)) {
    UseCounter::Count(state.GetDocument(), WebFeature::kHasIcUnits);
  }
  if (flags & static_cast<Flags>(Flag::kRicRelative)) {
    UseCounter::Count(state.GetDocument(), WebFeature::kHasRicUnits);
  }
  if (flags & static_cast<Flags>(Flag::kLhRelative)) {
    builder.SetHasLineHeightRelativeUnits();
    UseCounter::Count(state.GetDocument(), WebFeature::kHasLhUnits);
  }
  if (flags & static_cast<Flags>(Flag::kRlhRelative)) {
    builder.SetHasLineHeightRelativeUnits();
    UseCounter::Count(state.GetDocument(), WebFeature::kHasRlhUnits);
  }
  if (flags & static_cast<Flags>(Flag::kChRelative)) {
    UseCounter::Count(state.GetDocument(), WebFeature::kHasChUnits);
  }
  if (flags & static_cast<Flags>(Flag::kRchRelative)) {
    UseCounter::Count(state.GetDocument(), WebFeature::kHasRchUnits);
  }
  if (flags & static_cast<Flags>(Flag::kSiblingRelative)) {
    builder.SetHasSiblingFunctions();
  }
}

=======
>>>>>>> chromium
}  // namespace

static CSSPropertyValueSet* LeftToRightDeclaration() {
  DEFINE_STATIC_LOCAL(
      Persistent<MutableCSSPropertyValueSet>, left_to_right_decl,
      (MakeGarbageCollected<MutableCSSPropertyValueSet>(kHTMLQuirksMode)));
  if (left_to_right_decl->IsEmpty()) {
    left_to_right_decl->SetProperty(CSSPropertyID::kDirection,
                                    CSSValueID::kLtr);
  }
  return left_to_right_decl;
}

static CSSPropertyValueSet* RightToLeftDeclaration() {
  DEFINE_STATIC_LOCAL(
      Persistent<MutableCSSPropertyValueSet>, right_to_left_decl,
      (MakeGarbageCollected<MutableCSSPropertyValueSet>(kHTMLQuirksMode)));
  if (right_to_left_decl->IsEmpty()) {
    right_to_left_decl->SetProperty(CSSPropertyID::kDirection,
                                    CSSValueID::kRtl);
  }
  return right_to_left_decl;
}

static CSSPropertyValueSet* DocumentElementUserAgentDeclarations() {
  DEFINE_STATIC_LOCAL(
      Persistent<MutableCSSPropertyValueSet>, document_element_ua_decl,
      (MakeGarbageCollected<MutableCSSPropertyValueSet>(kHTMLStandardMode)));
  if (document_element_ua_decl->IsEmpty()) {
    document_element_ua_decl->SetProperty(CSSPropertyID::kColor,
                                          *CSSInitialColorValue::Create());
  }
  return document_element_ua_decl;
}

<<<<<<< HEAD
// The 'color' property conditionally inherits from the *used* value of its
// parent, and we rely on an explicit value in the cascade to implement this.
// https://drafts.csswg.org/css-color-adjust-1/#propdef-forced-color-adjust
static CSSPropertyValueSet* ForcedColorsUserAgentDeclarations() {
  DEFINE_STATIC_LOCAL(
      Persistent<MutableCSSPropertyValueSet>, decl,
      (MakeGarbageCollected<MutableCSSPropertyValueSet>(kHTMLStandardMode)));
  if (decl->IsEmpty()) {
    decl->SetProperty(CSSPropertyID::kColor, *CSSInheritedValue::Create());
  }
  return decl;
}

// UA rule: * { overlay: none !important }
static CSSPropertyValueSet* UniversalOverlayUserAgentDeclaration() {
  DEFINE_STATIC_LOCAL(
      Persistent<MutableCSSPropertyValueSet>, decl,
      (MakeGarbageCollected<MutableCSSPropertyValueSet>(kHTMLStandardMode)));

  if (decl->IsEmpty()) {
    decl->SetProperty(CSSPropertyID::kOverlay,
                      *CSSIdentifierValue::Create(CSSValueID::kNone),
                      true /* important */);
  }
  return decl;
}

=======
>>>>>>> chromium
static void CollectScopedResolversForHostedShadowTrees(
    const Element& element,
    HeapVector<Member<ScopedStyleResolver>, 8>& resolvers) {
  ShadowRoot* root = element.GetShadowRoot();
  if (!root)
    return;

  // Adding scoped resolver for active shadow roots for shadow host styling.
  if (ScopedStyleResolver* resolver = root->GetScopedStyleResolver())
    resolvers.push_back(resolver);
}

StyleResolver::StyleResolver(Document& document)
    : document_(document),
      initial_style_(ComputedStyle::CreateInitialStyleSingleton()) {
  UpdateMediaType();
}

StyleResolver::~StyleResolver() = default;

void StyleResolver::Dispose() {
  initial_style_.reset();
  matched_properties_cache_.Clear();
}

void StyleResolver::SetRuleUsageTracker(StyleRuleUsageTracker* tracker) {
  tracker_ = tracker;
}

static inline ScopedStyleResolver* ScopedResolverFor(const Element& element) {
  // For normal elements, returning element->treeScope().scopedStyleResolver()
  // is enough. Rules for ::cue and custom pseudo elements like
  // ::-webkit-meter-bar pierce through a single shadow dom boundary and apply
  // to elements in sub-scopes.
  //
  // An assumption here is that these elements belong to scopes without a
  // ScopedStyleResolver due to the fact that VTT scopes and UA shadow trees
  // don't have <style> or <link> elements. This is backed up by the DCHECKs
  // below. The one exception to this assumption are the media controls which
  // use a <style> element for CSS animations in the shadow DOM. If a <style>
  // element is present in the shadow DOM then this will also block any
  // author styling.

  TreeScope* tree_scope = &element.GetTreeScope();
  if (ScopedStyleResolver* resolver = tree_scope->GetScopedStyleResolver()) {
#if DCHECK_IS_ON()
    if (!element.HasMediaControlAncestor())
      DCHECK(element.ShadowPseudoId().IsEmpty());
#endif
    DCHECK(!element.IsVTTElement());
    return resolver;
  }

<<<<<<< HEAD
  return nullptr;
}

struct UAShadowPseudoResult {
  bool use_parent_resolver;
  bool cascade_style_attribute_in_parent_scope;
};

inline UAShadowPseudoResult UAShadowPseudoCascading(const Element& element) {
  // Rules for ::cue and custom pseudo elements like
  // ::-webkit-meter-bar pierce through a single shadow dom boundary and apply
  // to elements in sub-scopes.
  TreeScope* tree_scope = element.GetTreeScope().ParentTreeScope();
  if (!tree_scope) {
    return {false, false};
  }
  const AtomicString& shadow_pseudo_id = element.ShadowPseudoId();
  bool is_vtt = element.IsVTTElement();
  if (shadow_pseudo_id.empty() && !is_vtt) {
    return {false, false};
  }
  ScopedStyleResolver* parent_resolver = tree_scope->GetScopedStyleResolver();
  if (!parent_resolver) {
    return {true, false};
  }
  // Going forward, for shadow pseudo IDs that we standardize as
  // pseudo-elements, we expect styles specified by the author using the
  // pseudo-element to override styles specified in style attributes in
  // the user agent shadow DOM.  However, since we have a substantial
  // number of existing uses with :-webkit-* and :-internal-* pseudo
  // elements that do not override the style attribute, we do not apply
  // this (developer-expected) behavior to those existing
  // pseudo-elements.  (It's possible that we could, but it would
  // require a good bit of compatibility analysis.)
  DCHECK(shadow_pseudo_id.empty() || !shadow_pseudo_id.StartsWith("-") ||
         shadow_pseudo_id.StartsWith("-webkit-") ||
         shadow_pseudo_id.StartsWith("-internal-"))
      << "shadow pseudo IDs should either begin with -webkit- or -internal- "
         "or not begin with a -";
  return {true, shadow_pseudo_id.StartsWith("-")};
=======
  tree_scope = tree_scope->ParentTreeScope();
  if (!tree_scope)
    return nullptr;
  if (element.ShadowPseudoId().IsEmpty() && !element.IsVTTElement())
    return nullptr;
  return tree_scope->GetScopedStyleResolver();
>>>>>>> chromium
}

// Matches :host and :host-context rules if the element is a shadow host.
// It matches rules from the ShadowHostRules of the ScopedStyleResolver
// of the attached shadow root.
static void MatchHostRules(const Element& element,
                           ElementRuleCollector& collector) {
  ShadowRoot* shadow_root = element.GetShadowRoot();
  if (!shadow_root)
    return;
  if (ScopedStyleResolver* resolver = shadow_root->GetScopedStyleResolver())
    resolver->CollectMatchingShadowHostRules(collector);
}

// Matches custom element rules from Custom Element Default Style.
static void MatchCustomElementRules(const Element& element,
                                    ElementRuleCollector& collector) {
  if (!RuntimeEnabledFeatures::CustomElementDefaultStyleEnabled())
    return;
  if (CustomElementDefinition* definition =
          element.GetCustomElementDefinition()) {
    if (definition->HasDefaultStyleSheets()) {
      for (CSSStyleSheet* style : definition->DefaultStyleSheets()) {
        if (!style)
          continue;
        RuleSet* rule_set =
            element.GetDocument().GetStyleEngine().RuleSetForSheet(*style);
        if (rule_set)
          collector.CollectMatchingRules(MatchRequest(rule_set));
      }
    }
  }
}

// Matches :host and :host-context rules
// and custom element rules from Custom Element Default Style.
static void MatchHostAndCustomElementRules(const Element& element,
                                           ElementRuleCollector& collector) {
  ShadowRoot* shadow_root = element.GetShadowRoot();
  ScopedStyleResolver* resolver =
      shadow_root ? shadow_root->GetScopedStyleResolver() : nullptr;
  if (!resolver && !RuntimeEnabledFeatures::CustomElementDefaultStyleEnabled())
    return;
  collector.ClearMatchedRules();
  MatchCustomElementRules(element, collector);
  MatchHostRules(element, collector);
  collector.SortAndTransferMatchedRules();
  // TODO(futhark): If the resolver is null here, it means we are matching rules
  // for custom element default styles. Since we don't have a
  // ScopedStyleResolver if the custom element does not have a shadow root,
  // there is no way to collect @-rules for @font-face, @keyframes, etc. We
  // currently pass the element's TreeScope, which might not be what we want. It
  // means that if you have:
  //
  //   <style>@keyframes anim { ... }</style>
  //   <custom-element></custom-element>
  //
  // and the custom-element is defined with:
  //
  //   @keyframes anim { ... }
  //   custom-element { animation-name: anim }
  //
  // it means that the custom element will pick up the @keyframes definition
  // from the element's scope.
  collector.FinishAddingAuthorRulesForTreeScope(
      resolver ? resolver->GetTreeScope() : element.GetTreeScope());
}

static void MatchSlottedRules(const Element&, ElementRuleCollector&);
static void MatchSlottedRulesForUAHost(const Element& element,
                                       ElementRuleCollector& collector) {
  if (element.ShadowPseudoId() != shadow_element_names::kPseudoInputPlaceholder)
    return;

  // We allow ::placeholder pseudo element after ::slotted(). Since we are
  // matching such pseudo elements starting from inside the UA shadow DOM of
  // the element having the placeholder, we need to match ::slotted rules from
  // the scopes to which the placeholder's host element may be slotted.
  //
  // Example:
  //
  // <div id=host>
  //   <:shadow-root>
  //     <style>::slotted(input)::placeholder { color: green }</style>
  //     <slot />
  //   </:shadow-root>
  //   <input placeholder="PLACEHOLDER-TEXT">
  //     <:ua-shadow-root>
  //       ... <placeholder>PLACEHOLDER-TEXT</placeholder> ...
  //     </:ua-shadow-root>
  //   </input>
  // </div>
  //
  // Here we need to match the ::slotted rule from the #host shadow tree where
  // the input is slotted on the placeholder element.
  DCHECK(element.OwnerShadowHost());
  MatchSlottedRules(*element.OwnerShadowHost(), collector);
}

// Matches `::slotted` selectors. It matches rules in the element's slot's
// scope. If that slot is itself slotted it will match rules in the slot's
// slot's scope and so on. The result is that it considers a chain of scopes
// descending from the element's own scope.
static void MatchSlottedRules(const Element& element,
                              ElementRuleCollector& collector) {
  MatchSlottedRulesForUAHost(element, collector);
  HTMLSlotElement* slot = element.AssignedSlot();
  if (!slot)
    return;

  HeapVector<Member<ScopedStyleResolver>> resolvers;
  for (; slot; slot = slot->AssignedSlot()) {
    if (ScopedStyleResolver* resolver =
            slot->GetTreeScope().GetScopedStyleResolver())
      resolvers.push_back(resolver);
  }
<<<<<<< HEAD

  for (const auto& [slot, resolver] : base::Reversed(resolvers)) {
=======
  for (auto it = resolvers.rbegin(); it != resolvers.rend(); ++it) {
>>>>>>> chromium
    collector.ClearMatchedRules();
    (*it)->CollectMatchingSlottedRules(collector);
    collector.SortAndTransferMatchedRules();
    collector.FinishAddingAuthorRulesForTreeScope((*it)->GetTreeScope());
  }
}

const static TextTrack* GetTextTrackFromElement(const Element& element) {
  if (auto* vtt_element = DynamicTo<VTTElement>(element))
    return vtt_element->GetTrack();
  if (auto* vtt_cue_background_box = DynamicTo<VTTCueBackgroundBox>(element))
    return vtt_cue_background_box->GetTrack();
  return nullptr;
}

static void MatchVTTRules(const Element& element,
                          ElementRuleCollector& collector) {
  const TextTrack* text_track = GetTextTrackFromElement(element);
  if (!text_track)
    return;
  const HeapVector<Member<CSSStyleSheet>>& styles =
      text_track->GetCSSStyleSheets();
<<<<<<< HEAD
  if (!styles.empty()) {
=======
  if (!styles.IsEmpty()) {
    int style_sheet_index = 0;
>>>>>>> chromium
    collector.ClearMatchedRules();

    StyleEngine& style_engine = element.GetDocument().GetStyleEngine();
    Element* vtt_originating_element =
        style_engine.EnsureVTTOriginatingElement();

    // We could cache the MatchRequests here, but this happens rarely enough
    // that it's not worth it. We just take the performance hit and construct
    // them anew every time.
    unsigned rule_set_group_index = 0;
    RuleSetGroup rule_set_group{rule_set_group_index++};

    for (CSSStyleSheet* style : styles) {
      RuleSet* rule_set = style_engine.RuleSetForSheet(*style);
<<<<<<< HEAD
      if (!rule_set) {
        continue;
      }
      rule_set_group.AddRuleSet(rule_set);
      if (rule_set_group.IsFull()) {
        MatchRequest match_request(rule_set_group, /*scope=*/nullptr,
                                   vtt_originating_element);
        collector.CollectMatchingRules(match_request,
                                       /*part_names*/ nullptr);
        rule_set_group = RuleSetGroup{rule_set_group_index++};
      }
    }
    if (!rule_set_group.IsEmpty()) {
      MatchRequest match_request(rule_set_group, /*scope=*/nullptr,
                                 vtt_originating_element);
      collector.CollectMatchingRules(match_request,
                                     /*part_names*/ nullptr);
    }

    collector.SortAndTransferMatchedRules(
        CascadeOrigin::kAuthor, true /* is_vtt_embedded_style */, tracker);
  }
}

void MatchHostPartRules(const Element& element,
                        ElementRuleCollector& collector,
                        StyleRuleUsageTracker* tracker) {
  DOMTokenList* part = element.GetPart();
  if (!part || !part->length() || !element.IsInShadowTree()) {
    return;
  }

  PartNames current_names(part->TokenSet());

  // Consider ::part rules in this element’s tree scope, which only match if
  // preceded by a :host or :host() that matches one of its containing shadow
  // hosts (see MatchForRelation).
  TreeScope& tree_scope = element.GetTreeScope();
  if (ScopedStyleResolver* resolver = tree_scope.GetScopedStyleResolver()) {
    resolver->CollectMatchingPartPseudoRules(collector, &current_names);
  }
}

void MatchStyleAttribute(const Element& element,
                         ElementRuleCollector& collector,
                         StyleRuleUsageTracker* tracker) {
  if (element.IsStyledElement() && element.InlineStyle() &&
      collector.GetPseudoId() == kPseudoIdNone) {
    // Do not add styles depending on style attributes to the
    // MatchedPropertiesCache (MPC) if they have been modified after parsing.
    // The reason is that these are typically used for animations by modifying
    // the style attribute every frame, and making the style cacheable would
    // effectively just fill up the MPC with unnecessary ComputedStyles.
    //
    // Note that we have a special fast path for modifying certain independent
    // attributes on inline style, which also bypasses the MPC.
    bool is_inline_style_cacheable = !element.InlineStyle()->IsMutable();
    collector.AddElementStyleProperties(
        element.InlineStyle(), CascadeOrigin::kAuthor,
        is_inline_style_cacheable, true /* is_inline_style */);
=======
      if (rule_set) {
        collector.CollectMatchingRules(MatchRequest(
            rule_set, nullptr /* scope */, style, style_sheet_index,
            style_engine.EnsureVTTOriginatingElement()));
        style_sheet_index++;
      }
    }
    collector.SortAndTransferMatchedRules();
>>>>>>> chromium
  }
}

// Matches rules from the element's scope. The selectors may cross shadow
// boundaries during matching, like for :host-context.
<<<<<<< HEAD
void MatchElementScopeRules(const Element& element,
                            ElementRuleCollector& collector,
                            StyleRuleUsageTracker* tracker) {
  ScopedStyleResolver* element_scope_resolver = ScopedResolverFor(element);
  UAShadowPseudoResult spr = UAShadowPseudoCascading(element);
  collector.BeginAddingAuthorRulesForTreeScope(element.GetTreeScope());
  if (element_scope_resolver) {
    collector.ClearMatchedRules();
    DCHECK_EQ(&element_scope_resolver->GetTreeScope(), &element.GetTreeScope());
    element_scope_resolver->CollectMatchingElementScopeRules(
        collector, /*part_shadow_host*/ nullptr);
    MatchHostPartRules(element, collector, tracker);
    collector.SortAndTransferMatchedRules(
        CascadeOrigin::kAuthor, /*is_vtt_embedded_style=*/false, tracker);
  }

  if (!spr.cascade_style_attribute_in_parent_scope) {
    MatchStyleAttribute(element, collector, tracker);
  }
}

void MatchOuterScopeRules(const Element& matching_element,
                          ElementRuleCollector& collector,
                          StyleRuleUsageTracker* tracker) {
  // Because ::part() is never allowed after ::part(), or after another
  // pseudo-element, and because elements (generally those in UA shadow trees,
  // but this is also used for VTT) that are exposed as pseudos ("shadow
  // pseudos") are never exposed as parts, the rules from a particular scope
  // can only be used for one of the states below.
  enum class MatchingState {
    kDone,
    kShadowPseudo,
    kPart,
    kPartAboveShadowPseudo,
  };

  MatchingState state = MatchingState::kDone;

  // Given an element that we're trying to match, and a scope containing
  // style rules, there is only a single set of part names that can
  // match the element in that scope.  (It doesn't depend on the
  // selector.  It only depends on what parts are exported from each
  // scope to the scope outside it, via either part= or exportparts=.)
  //
  // This does depend on the idea (see above) that the same element can't be
  // exposed as both a UA shadow pseudo and as a part.
  //
  // Present when state is kMatchingPart or kMatchingPartAboveShadowPseudo.
  std::optional<PartNames> current_part_names;

  auto set_part_names = [&current_part_names](const Element* element) -> bool {
    if (DOMTokenList* part = element->GetPart()) {
      if (part->length() && element->IsInShadowTree()) {
        current_part_names.emplace(part->TokenSet());
        return true;
      }
    }
    current_part_names.reset();
    return false;
  };

  bool style_attribute_cascaded_in_parent_scope = false;
  if (set_part_names(&matching_element)) {
    state = MatchingState::kPart;
  } else {
    UAShadowPseudoResult spr = UAShadowPseudoCascading(matching_element);
    if (spr.use_parent_resolver) {
      state = MatchingState::kShadowPseudo;
      style_attribute_cascaded_in_parent_scope =
          spr.cascade_style_attribute_in_parent_scope;
    }
  }

  // Consider rules for ::part() and for UA shadow pseudo-elements from scopes
  // outside this tree scope.  Note that :host::part() rules in the element's
  // own scope are considered in MatchElementScopeRules.
  for (const Element* element = matching_element.OwnerShadowHost();
       element && state != MatchingState::kDone;
       element = element->OwnerShadowHost()) {
    // Consider the ::part rules and pseudo-element rules for the given scope.
    TreeScope& tree_scope = element->GetTreeScope();
    if (ScopedStyleResolver* resolver = tree_scope.GetScopedStyleResolver()) {
      collector.ClearMatchedRules();
      collector.BeginAddingAuthorRulesForTreeScope(resolver->GetTreeScope());
      if (state == MatchingState::kPart) {
        resolver->CollectMatchingPartPseudoRules(collector,
                                                 &*current_part_names);
      } else {
        resolver->CollectMatchingElementScopeRules(
            collector, base::OptionalToPtr(current_part_names));
      }

      collector.SortAndTransferMatchedRules(
          CascadeOrigin::kAuthor, /*is_vtt_embedded_style=*/false, tracker);

      if (style_attribute_cascaded_in_parent_scope) {
        MatchStyleAttribute(matching_element, collector, tracker);
      }
    }

    if (state == MatchingState::kShadowPseudo) {
      CHECK(!current_part_names);
      // The style attribute only goes in the parent scope (in some legacy
      // cases), never higher.
      style_attribute_cascaded_in_parent_scope = false;

      if (set_part_names(element)) {
        state = MatchingState::kPartAboveShadowPseudo;
      } else {
        // For now we only handle shadow pseudos in the parent scope.
        //
        // TODO(https://crbug.com/356158098): In theory this should be an
        // "else if (element->ShadowPseudoId().empty())", since there could be
        // a chain of pseudo-elements in the next scope outside, and we should
        // continue looping when there are more shadow pseudos to match.
        // However, we don't currently parse any such selectors as valid
        // right now, so it seems wasteful to gather rules from the second
        // outer scope (for example, on an element that's conceptually
        // ::-webkit-media-controls-timeline::-webkit-slider-container) when
        // we know none of them will match.
        state = MatchingState::kDone;
      }
    } else {
      CHECK(current_part_names);
      // Subsequent containing tree scopes require mapping part names through
      // @exportparts before considering ::part rules. If no parts are
      // forwarded, the element is now unreachable and we can stop handling
      // ::part() rules.
      if (element->HasPartNamesMap()) {
        current_part_names->PushMap(*element->PartNamesMap());
      } else {
        state = MatchingState::kDone;
      }
    }
  }
}

}  // namespace

void StyleResolver::MatchPositionTryRules(ElementRuleCollector& collector) {
  collector.AddTryStyleProperties();
  collector.AddTryTacticsStyleProperties();
}

void StyleResolver::MatchAuthorRules(const Element& element,
                                     ElementRuleCollector& collector) {
  const Element& originating_element =
      UltimateOriginatingElementOrSelf(element);
  MatchHostRules(originating_element, collector, tracker_);
  MatchSlottedRules(originating_element, collector, tracker_);
  MatchElementScopeRules(element, collector, tracker_);
  MatchOuterScopeRules(originating_element, collector, tracker_);
  MatchVTTRules(element, collector, tracker_);
  MatchPositionTryRules(collector);
=======
static void MatchElementScopeRules(const Element& element,
                                   ScopedStyleResolver* element_scope_resolver,
                                   ElementRuleCollector& collector) {
  if (element_scope_resolver) {
    collector.ClearMatchedRules();
    element_scope_resolver->CollectMatchingElementScopeRules(collector);
    collector.SortAndTransferMatchedRules();
  }

  MatchVTTRules(element, collector);
  if (element.IsStyledElement() && element.InlineStyle() &&
      !collector.IsCollectingForPseudoElement()) {
    // Inline style is immutable as long as there is no CSSOM wrapper.
    bool is_inline_style_cacheable = !element.InlineStyle()->IsMutable();
    collector.AddElementStyleProperties(element.InlineStyle(),
                                        is_inline_style_cacheable);
  }

  collector.FinishAddingAuthorRulesForTreeScope(
      element_scope_resolver ? element_scope_resolver->GetTreeScope()
                             : element.GetTreeScope());
}

void StyleResolver::MatchPseudoPartRulesForUAHost(
    const Element& element,
    ElementRuleCollector& collector) {
  const AtomicString& pseudo_id = element.ShadowPseudoId();
  if (pseudo_id != shadow_element_names::kPseudoInputPlaceholder &&
      pseudo_id != shadow_element_names::kPseudoFileUploadButton) {
    return;
  }

  // We allow ::placeholder pseudo element after ::part(). See
  // MatchSlottedRulesForUAHost for a more detailed explanation.
  DCHECK(element.OwnerShadowHost());
  MatchPseudoPartRules(*element.OwnerShadowHost(), collector,
                       /* for_shadow_pseudo */ true);
}

void StyleResolver::MatchPseudoPartRules(const Element& element,
                                         ElementRuleCollector& collector,
                                         bool for_shadow_pseudo) {
  if (!for_shadow_pseudo)
    MatchPseudoPartRulesForUAHost(element, collector);
  DOMTokenList* part = element.GetPart();
  if (!part)
    return;

  PartNames current_names(part->TokenSet());

  // ::part selectors in the shadow host's scope and above can match this
  // element.
  Element* host = element.OwnerShadowHost();
  if (!host)
    return;

  while (current_names.size()) {
    TreeScope& tree_scope = host->GetTreeScope();
    if (ScopedStyleResolver* resolver = tree_scope.GetScopedStyleResolver()) {
      collector.ClearMatchedRules();
      resolver->CollectMatchingPartPseudoRules(collector, current_names,
                                               for_shadow_pseudo);
      collector.SortAndTransferMatchedRules();
      collector.FinishAddingAuthorRulesForTreeScope(resolver->GetTreeScope());
    }

    // If the host doesn't forward any parts using partmap= then the element is
    // unreachable from any scope further above and we can stop.
    const NamesMap* part_map = host->PartNamesMap();
    if (!part_map)
      return;

    // We have reached the top-level document.
    if (!(host = host->OwnerShadowHost()))
      return;

    current_names.PushMap(*part_map);
  }
}

void StyleResolver::MatchAuthorRules(
    const Element& element,
    ScopedStyleResolver* element_scope_resolver,
    ElementRuleCollector& collector) {
  MatchHostAndCustomElementRules(element, collector);
  MatchSlottedRules(element, collector);
  MatchElementScopeRules(element, element_scope_resolver, collector);
  MatchPseudoPartRules(element, collector);
>>>>>>> chromium
}

void StyleResolver::MatchUserRules(ElementRuleCollector& collector) {
  collector.ClearMatchedRules();
  GetDocument().GetStyleEngine().CollectMatchingUserRules(collector);
  collector.SortAndTransferMatchedRules();
  collector.FinishAddingUserRules();
}

namespace {

bool IsInMediaUAShadow(const Element& element) {
  ShadowRoot* root = element.ContainingShadowRoot();
  if (!root || !root->IsUserAgent())
    return false;
  ShadowRoot* outer_root;
  do {
    outer_root = root;
    root = root->host().ContainingShadowRoot();
  } while (root && root->IsUserAgent());
  return outer_root->host().IsMediaElement();
}

}  // namespace

<<<<<<< HEAD
template <typename Functor>
void StyleResolver::ForEachUARulesForElement(const Element& element,
                                             ElementRuleCollector* collector,
                                             Functor& func) const {
  CSSDefaultStyleSheets& default_style_sheets =
      CSSDefaultStyleSheets::Instance();
  if (!print_media_type_) {
    if (element.IsHTMLElement() || element.IsPseudoElement() ||
        element.IsVTTElement()) [[likely]] {
      func(default_style_sheets.DefaultHtmlStyle(), kHTMLUASheet);
    } else if (element.IsSVGElement()) {
      func(default_style_sheets.DefaultSVGStyle(), kSVGUASheet);
    } else if (element.namespaceURI() == mathml_names::kNamespaceURI) {
      func(default_style_sheets.DefaultMathMLStyle(), kMathMLUASheet);
    }
    if (Fullscreen::HasFullscreenElements()) {
      func(default_style_sheets.DefaultFullscreenStyle(), kFullscreenUASheet);
    }
  } else {
    func(default_style_sheets.DefaultPrintStyle(), kPrintUASheet);
  }

  // In quirks mode, we match rules from the quirks user agent sheet.
  if (GetDocument().InQuirksMode()) {
    func(default_style_sheets.DefaultHtmlQuirksStyle(), kQuirksUASheet);
  }

  // If document uses view source styles (in view source mode or in xml
  // viewer mode), then we match rules from the view source style sheet.
  if (GetDocument().IsViewSource()) {
    func(default_style_sheets.DefaultViewSourceStyle(), kViewSourceUASheet);
  }

  // If the system is in forced colors mode, match rules from the forced colors
  // style sheet.
  if (IsForcedColorsModeEnabled()) {
    func(default_style_sheets.DefaultForcedColorStyle(), kForcedColorsUASheet);
  }

  if (GetDocument().IsJSONDocument()) {
    func(default_style_sheets.DefaultJSONDocumentStyle(), kJSONUASheet);
  }

  const auto pseudo_id = GetPseudoId(element, collector);
  if (pseudo_id == kPseudoIdNone) {
    return;
  }

  if (IsPseudoElementWithUAStyle(pseudo_id) &&
      default_style_sheets.DefaultPseudoElementStyleOrNull()) {
    func(default_style_sheets.DefaultPseudoElementStyleOrNull(),
         kPseudoElementUASheet);
  } else if (IsTransitionPseudoElement(pseudo_id) &&
             GetDocument().GetStyleEngine().DefaultViewTransitionStyle()) {
    func(GetDocument().GetStyleEngine().DefaultViewTransitionStyle(),
         kViewTransitionUASheet);
  }
}

=======
>>>>>>> chromium
void StyleResolver::MatchUARules(const Element& element,
                                 ElementRuleCollector& collector) {
  collector.SetMatchingUARules(true);

<<<<<<< HEAD
  // Figure out which UA RuleSets are active for this element right now.
  // We use that to build up a bitmap, which we use as a cache key to avoid
  // recomputing the MatchRequest. If we actually need to make one, we'll
  // do another call to ForEachUARulesForElement() below where we actually
  // care about the RuleSet pointers. (If the RuleSet pointers for a given
  // key change, CSSDefaultStyleSheets will clear the cache for us.)
  unsigned cache_key = 0;
  auto func = [&cache_key](RuleSet* rules, unsigned rule_set_index) {
    cache_key |= 1 << rule_set_index;
  };
  ForEachUARulesForElement(element, &collector, func);

  // View transitions can come and go without much notice for us.
  // Instead of trying to figure out when to invalidate the cache,
  // we just disable it entirely when view transitions are in use.
  const bool can_use_cache = (cache_key & (1 << kViewTransitionUASheet)) == 0;

  RuleSetGroup* rule_set_group = nullptr;
  HeapVector<std::pair<unsigned, RuleSetGroup>>& rule_set_group_cache =
      CSSDefaultStyleSheets::Instance().RuleSetGroupCache();
  for (auto& [key, value] : rule_set_group_cache) {
    if (key == cache_key) {
      rule_set_group = &value;
      break;
    }
  }
  if (rule_set_group == nullptr || !can_use_cache) {
    // We need to create a new RuleSetGroup.
    if (rule_set_group == nullptr) {
      rule_set_group_cache.emplace_back(
          cache_key, RuleSetGroup(/*rule_set_group_index=*/0u));
      rule_set_group = &rule_set_group_cache.back().second;
    } else {
      // Reuse the memory from the previous one, but discard its contents.
      *rule_set_group = RuleSetGroup(/*rule_set_group_index=*/0u);
    }
    auto func2 = [rule_set_group](RuleSet* rules, unsigned rule_set_index) {
      rule_set_group->AddRuleSet(rules);
    };
    ForEachUARulesForElement(element, &collector, func2);
  }

#if DCHECK_IS_ON()
  {
    // Verify that we get the same result as without the cache.
    RuleSetGroup ref(/*rule_set_group_index=*/0u);
    auto func2 = [&ref](RuleSet* rules, unsigned rule_set_index) {
      ref.AddRuleSet(rules);
    };
    ForEachUARulesForElement(element, &collector, func2);
    rule_set_group->AssertEqualTo(ref);
  }
#endif

  if (!rule_set_group->IsEmpty()) {
    collector.ClearMatchedRules();
    MatchRequest match_request(*rule_set_group, /*scope=*/nullptr);
    collector.CollectMatchingRules(match_request, /*part_names*/ nullptr);
    collector.SortAndTransferMatchedRules(
        CascadeOrigin::kUserAgent, /*is_vtt_embedded_style=*/false, tracker_);
  }

  if (IsInMediaUAShadow(element)) {
    RuleSet* rule_set =
        IsForcedColorsModeEnabled()
            ? CSSDefaultStyleSheets::Instance()
                  .DefaultForcedColorsMediaControlsStyle()
            : CSSDefaultStyleSheets::Instance().DefaultMediaControlsStyle();
    // Match media controls UA shadow rules in separate UA origin, as they
    // should override UA styles regardless of specificity.
    if (media_controls_cache_key_ != rule_set) {
      media_controls_cached_rule_set_group_ =
          RuleSetGroup(/*rule_set_group_index=*/0u);
      media_controls_cached_rule_set_group_.AddRuleSet(rule_set);
      media_controls_cache_key_ = rule_set;
    }
    MatchRequest match_request(media_controls_cached_rule_set_group_,
                               /*scope=*/nullptr);
    collector.ClearMatchedRules();
    collector.CollectMatchingRules(match_request,
                                   /*part_names*/ nullptr);
    collector.SortAndTransferMatchedRules(
        CascadeOrigin::kUserAgent, /*is_vtt_embedded_style=*/false, tracker_);
=======
  CSSDefaultStyleSheets& default_style_sheets =
      CSSDefaultStyleSheets::Instance();
  if (!print_media_type_) {
    if (LIKELY(element.IsHTMLElement() || element.IsVTTElement())) {
      MatchRuleSet(collector, default_style_sheets.DefaultHtmlStyle());
      if (UNLIKELY(IsInMediaUAShadow(element))) {
        MatchRuleSet(collector,
                     default_style_sheets.DefaultMediaControlsStyle());
      }
    } else if (element.IsSVGElement()) {
      MatchRuleSet(collector, default_style_sheets.DefaultSVGStyle());
    } else if (element.namespaceURI() == mathml_names::kNamespaceURI) {
      MatchRuleSet(collector, default_style_sheets.DefaultMathMLStyle());
    }
  } else {
    MatchRuleSet(collector, default_style_sheets.DefaultPrintStyle());
  }

  // In quirks mode, we match rules from the quirks user agent sheet.
  if (GetDocument().InQuirksMode())
    MatchRuleSet(collector, default_style_sheets.DefaultHtmlQuirksStyle());

  // If document uses view source styles (in view source mode or in xml viewer
  // mode), then we match rules from the view source style sheet.
  if (GetDocument().IsViewSource())
    MatchRuleSet(collector, default_style_sheets.DefaultViewSourceStyle());

  // If the system is in forced colors mode, match rules from the forced colors
  // style sheet.
  if (IsForcedColorsModeEnabled())
    MatchRuleSet(collector, default_style_sheets.DefaultForcedColorStyle());

  if (collector.IsCollectingForPseudoElement()) {
    if (RuleSet* default_pseudo_style =
            default_style_sheets.DefaultPseudoElementStyleOrNull())
      MatchRuleSet(collector, default_pseudo_style);
>>>>>>> chromium
  }

  collector.FinishAddingUARules();
  collector.SetMatchingUARules(false);
}

void StyleResolver::MatchRuleSet(ElementRuleCollector& collector,
                                 RuleSet* rules) {
  collector.ClearMatchedRules();
  collector.CollectMatchingRules(MatchRequest(rules));
  collector.SortAndTransferMatchedRules();
}

DISABLE_CFI_PERF
void StyleResolver::MatchAllRules(StyleResolverState& state,
                                  ElementRuleCollector& collector,
                                  bool include_smil_properties) {
  Element& element = state.GetElement();
  MatchUARules(element, collector);
  MatchUserRules(collector);

  // Now check author rules, beginning first with presentational attributes
  // mapped from HTML.
  if (element.IsStyledElement() && !state.IsForPseudoElement()) {
    collector.AddElementStyleProperties(element.PresentationAttributeStyle());

    // Now we check additional mapped declarations.
    // Tables and table cells share an additional mapped rule that must be
    // applied after all attributes, since their mapped style depends on the
    // values of multiple attributes.
    collector.AddElementStyleProperties(
        element.AdditionalPresentationAttributeStyle());

    if (auto* html_element = DynamicTo<HTMLElement>(element)) {
      if (html_element->HasDirectionAuto()) {
        collector.AddElementStyleProperties(
            html_element->CachedDirectionality() == TextDirection::kLtr
                ? LeftToRightDeclaration()
                : RightToLeftDeclaration());
      }
    }
  }

  ScopedStyleResolver* element_scope_resolver = ScopedResolverFor(element);
  MatchAuthorRules(element, element_scope_resolver, collector);

  if (element.IsStyledElement() && !state.IsForPseudoElement()) {
    // Now check SMIL animation override style.
    auto* svg_element = DynamicTo<SVGElement>(element);
    if (include_smil_properties && svg_element) {
      collector.AddElementStyleProperties(
          svg_element->AnimatedSMILStyleProperties(), false /* isCacheable */);
    }
  }

  collector.FinishAddingAuthorRulesForTreeScope(
      element_scope_resolver ? element_scope_resolver->GetTreeScope()
                             : element.GetTreeScope());
}

scoped_refptr<ComputedStyle> StyleResolver::StyleForViewport() {
  scoped_refptr<ComputedStyle> viewport_style = InitialStyleForElement();

  viewport_style->SetZIndex(0);
  viewport_style->SetIsStackingContextWithoutContainment(true);
  viewport_style->SetDisplay(EDisplay::kBlock);
  viewport_style->SetPosition(EPosition::kAbsolute);

  // Document::InheritHtmlAndBodyElementStyles will set the final overflow
  // style values, but they should initially be auto to avoid premature
  // scrollbar removal in PaintLayerScrollableArea::UpdateAfterStyleChange.
  viewport_style->SetOverflowX(EOverflow::kAuto);
  viewport_style->SetOverflowY(EOverflow::kAuto);

  GetDocument().GetStyleEngine().ApplyVisionDeficiencyStyle(viewport_style);

  return viewport_style;
}

static ElementAnimations* GetElementAnimations(
    const StyleResolverState& state) {
  if (!state.GetAnimatingElement())
    return nullptr;
  return state.GetAnimatingElement()->GetElementAnimations();
}

static const ComputedStyle* CachedAnimationBaseComputedStyle(
    StyleResolverState& state) {
  ElementAnimations* element_animations = GetElementAnimations(state);
  if (!element_animations)
    return nullptr;

  return element_animations->BaseComputedStyle();
}

static void UpdateAnimationBaseComputedStyle(StyleResolverState& state,
                                             StyleCascade& cascade,
                                             bool forced_update) {
  if (!state.GetAnimatingElement())
    return;

  if (!state.CanCacheBaseStyle())
    return;

  if (forced_update)
    state.GetAnimatingElement()->EnsureElementAnimations();

  ElementAnimations* element_animations =
      state.GetAnimatingElement()->GetElementAnimations();
  if (!element_animations)
    return;

  if (element_animations->IsAnimationStyleChange() &&
      element_animations->BaseComputedStyle()) {
    return;
  }

  std::unique_ptr<CSSBitset> important_set = cascade.GetImportantSet();
  element_animations->UpdateBaseComputedStyle(state.Style(),
                                              std::move(important_set));
}

static void IncrementResolvedStyleCounters(const StyleRequest& style_request,
                                           Document& document) {
  document.GetStyleEngine().IncStyleForElementCount();

  if (style_request.IsPseudoStyleRequest()) {
    INCREMENT_STYLE_STATS_COUNTER(document.GetStyleEngine(),
                                  pseudo_elements_styled, 1);
  } else {
    INCREMENT_STYLE_STATS_COUNTER(document.GetStyleEngine(), elements_styled,
                                  1);
  }
}

scoped_refptr<ComputedStyle> StyleResolver::ResolveStyle(
    Element* element,
    const StyleRecalcContext& style_recalc_context,
    const StyleRequest& style_request) {
  if (!element) {
    DCHECK(style_request.IsPseudoStyleRequest());
    return nullptr;
  }

<<<<<<< HEAD
  if (InvalidationTracingFlag::IsEnabled()) [[unlikely]] {
    TRACE_EVENT_INSTANT1(
        TRACE_DISABLED_BY_DEFAULT("devtools.timeline.invalidationTracking"),
        "StyleResolver::ResolveStyle", TRACE_EVENT_SCOPE_THREAD, "elementId",
        IdentifiersFactory::IntIdForNode(element));
  }

  DCHECK(GetDocument().GetFrame());
  DCHECK(GetDocument().GetSettings());

  // The StyleResolverState is where we actually end up accumulating the
  // computed style. It's just a convenient way of not having to send
  // a lot of input/output variables around between the different functions.
  StyleResolverState state(GetDocument(), *element, &style_recalc_context,
=======
  DCHECK(!style_request.IsPseudoStyleRequest() ||
         style_request.parent_override);
  DCHECK(GetDocument().GetFrame());
  DCHECK(GetDocument().GetSettings());

  SelectorFilterParentScope::EnsureParentStackIsPushed();

  StyleResolverState state(GetDocument(), *element, style_recalc_context,
>>>>>>> chromium
                           style_request);

  STACK_UNINITIALIZED StyleCascade cascade(state);

  ApplyBaseStyle(element, style_recalc_context, style_request, state, cascade);

  if (style_request.IsPseudoStyleRequest() && state.HadNoMatchedProperties())
    return state.TakeStyle();

  if (ApplyAnimatedStyle(state, cascade, style_recalc_context)) {
    INCREMENT_STYLE_STATS_COUNTER(GetDocument().GetStyleEngine(),
                                  styles_animated, 1);
    StyleAdjuster::AdjustComputedStyle(
        state, style_request.IsPseudoStyleRequest() ? nullptr : element);
  }

  IncrementResolvedStyleCounters(style_request, GetDocument());

  if (!style_request.IsPseudoStyleRequest()) {
    if (IsA<HTMLBodyElement>(*element)) {
      GetDocument().GetTextLinkColors().SetTextColor(
          state.Style()->GetCurrentColor());
    }

    if (element->IsMathMLElement())
      ApplyMathMLCustomStyleProperties(element, state);
  } else if (IsHighlightPseudoElement(style_request.pseudo_id)) {
    if (element->GetComputedStyle() &&
        element->GetComputedStyle()->TextShadow() !=
            state.Style()->TextShadow()) {
      // This counts the usage of text-shadow in CSS highlight pseudos.
      UseCounter::Count(GetDocument(),
                        WebFeature::kTextShadowInHighlightPseudo);
      if (state.Style()->TextShadow()) {
        // This counts the cases in which text-shadow is not "none" in CSS
        // highlight pseudos, as the most common use case is using it to disable
        // text-shadow, and that won't be need once some painting issues related
        // to highlight pseudos are fixed.
        UseCounter::Count(GetDocument(),
                          WebFeature::kTextShadowNotNoneInHighlightPseudo);
      }
    }
  }

  if (Element* animating_element = state.GetAnimatingElement())
    SetAnimationUpdateIfNeeded(state, *animating_element);

  if (state.Style()->HasViewportUnits())
    GetDocument().SetHasViewportUnits();

  if (state.Style()->HasContainerRelativeUnits()) {
    state.Style()->SetDependsOnContainerQueries(true);
    GetDocument().GetStyleEngine().SetUsesContainerRelativeUnits();
  }

  if (state.Style()->HasRemUnits())
    GetDocument().GetStyleEngine().SetUsesRemUnit(true);

  if (state.Style()->HasGlyphRelativeUnits())
    UseCounter::Count(GetDocument(), WebFeature::kHasGlyphRelativeUnits);

  state.LoadPendingResources();

  // Now return the style.
  return state.TakeStyle();
}

<<<<<<< HEAD
const ComputedStyle& StyleResolver::ResolveBaseStyle(
    Element& element,
    const ComputedStyle* parent_base_style,
    const ComputedStyle* layout_parent_base_style,
    const StyleRecalcContext& style_recalc_context) {
  StyleRequest style_request;
  style_request.parent_override = parent_base_style;
  style_request.layout_parent_override = layout_parent_base_style;
  StyleResolverState state(GetDocument(), element, &style_recalc_context,
                           style_request);
  STACK_UNINITIALIZED StyleCascade cascade(state);
  ApplyBaseStyleNoCache(&element, style_recalc_context, style_request, state,
                        cascade);
  return *state.TakeStyle();
}

void StyleResolver::InitStyle(Element& element,
                              const StyleRequest& style_request,
                              const ComputedStyle& source_for_noninherited,
                              const ComputedStyle* parent_style,
                              StyleResolverState& state) {
  if (state.UsesHighlightPseudoInheritance()) {
    // When resolving highlight styles for children, we need to default all
    // properties (whether or not defined as inherited) to parent values.

    // Sadly, ComputedStyle creation is unavoidable until ElementRuleCollector
    // and friends stop relying on ComputedStyle mutation. The good news is that
    // if the element has no rules for this highlight pseudo, we skip resolution
    // entirely (leaving the optional unset). The bad news is that if
    // the element has rules but no matched properties, we currently clone.
    state.SetStyle(*parent_style);

    // Highlight Pseudos may use var() references but those must be resolved
    // against the originating element. Share the variables from the originating
    // style and remove any from the highlight chain.
    state.StyleBuilder().SetInheritedVariablesFrom(
        state.OriginatingElementStyle());
    state.StyleBuilder().SetNonInheritedVariablesFrom(
        state.OriginatingElementStyle());
  } else {
    state.CreateNewStyle(
        source_for_noninherited, *parent_style,
        (!style_request.IsPseudoStyleRequest() && IsAtShadowBoundary(&element))
            ? ComputedStyleBuilder::kAtShadowBoundary
            : ComputedStyleBuilder::kNotAtShadowBoundary);
  }
  if (element.IsPseudoElement()) {
    state.StyleBuilder().SetStyleType(element.GetPseudoIdForStyling());
=======
static bool AllowsInheritance(const StyleRequest& style_request,
                              const ComputedStyle* parent_style) {
  // The spec disallows inheritance for ::backdrop.
  return parent_style && style_request.pseudo_id != kPseudoIdBackdrop;
}

void StyleResolver::InitStyleAndApplyInheritance(
    Element& element,
    const StyleRequest& style_request,
    StyleResolverState& state) {
  if (AllowsInheritance(style_request, state.ParentStyle())) {
    scoped_refptr<ComputedStyle> style = CreateComputedStyle();
    style->InheritFrom(
        *state.ParentStyle(),
        (!style_request.IsPseudoStyleRequest() && IsAtShadowBoundary(&element))
            ? ComputedStyle::kAtShadowBoundary
            : ComputedStyle::kNotAtShadowBoundary);
    state.SetStyle(std::move(style));

    // contenteditable attribute (implemented by -webkit-user-modify) should
    // be propagated from shadow host to distributed node.
    if (!style_request.IsPseudoStyleRequest() && element.AssignedSlot()) {
      if (Element* parent = element.parentElement()) {
        if (const ComputedStyle* shadow_host_style = parent->GetComputedStyle())
          state.Style()->SetUserModify(shadow_host_style->UserModify());
      }
    }
>>>>>>> chromium
  } else {
    state.SetStyle(InitialStyleForElement());
    state.SetParentStyle(ComputedStyle::Clone(*state.Style()));
    state.SetLayoutParentStyle(state.ParentStyle());
    if (!style_request.IsPseudoStyleRequest() &&
        element != GetDocument().documentElement()) {
      // Strictly, we should only allow the root element to inherit from
      // initial styles, but we allow getComputedStyle() for connected
      // elements outside the flat tree rooted at an unassigned shadow host
      // child or a slot fallback element.
      DCHECK((IsShadowHost(element.parentNode()) ||
              IsA<HTMLSlotElement>(element.parentNode())) &&
             !LayoutTreeBuilderTraversal::ParentElement(element));
      state.Style()->SetIsEnsuredOutsideFlatTree();
    }
  }
  state.Style()->SetStyleType(style_request.pseudo_id);
  state.Style()->SetPseudoArgument(style_request.pseudo_argument);

  if (!style_request.IsPseudoStyleRequest() && element.IsLink()) {
    state.Style()->SetIsLink();
    EInsideLink link_state = state.ElementLinkState();
    if (link_state != EInsideLink::kNotInsideLink) {
      bool force_visited = false;
      probe::ForcePseudoState(&element, CSSSelector::kPseudoVisited,
                              &force_visited);
      if (force_visited)
        link_state = EInsideLink::kInsideVisitedLink;
    }
    state.Style()->SetInsideLink(link_state);
  }
}

void StyleResolver::ApplyMathMLCustomStyleProperties(
    Element* element,
    StyleResolverState& state) {
  DCHECK(element && element->IsMathMLElement());
  ComputedStyle& style = state.StyleRef();
  if (auto* space = DynamicTo<MathMLSpaceElement>(*element)) {
    space->AddMathBaselineIfNeeded(style, state.CssToLengthConversionData());
  } else if (auto* padded = DynamicTo<MathMLPaddedElement>(*element)) {
    padded->AddMathBaselineIfNeeded(style, state.CssToLengthConversionData());
    padded->AddMathPaddedDepthIfNeeded(style,
                                       state.CssToLengthConversionData());
    padded->AddMathPaddedLSpaceIfNeeded(style,
                                        state.CssToLengthConversionData());
    padded->AddMathPaddedVOffsetIfNeeded(style,
                                         state.CssToLengthConversionData());
  } else if (auto* fraction = DynamicTo<MathMLFractionElement>(*element)) {
    fraction->AddMathFractionBarThicknessIfNeeded(
        style, state.CssToLengthConversionData());
  } else if (auto* operator_element =
                 DynamicTo<MathMLOperatorElement>(*element)) {
    operator_element->AddMathLSpaceIfNeeded(style,
                                            state.CssToLengthConversionData());
    operator_element->AddMathRSpaceIfNeeded(style,
                                            state.CssToLengthConversionData());
    operator_element->AddMathMinSizeIfNeeded(style,
                                             state.CssToLengthConversionData());
    operator_element->AddMathMaxSizeIfNeeded(style,
                                             state.CssToLengthConversionData());
  }
}

<<<<<<< HEAD
bool CanApplyInlineStyleIncrementally(Element* element,
                                      const StyleResolverState& state,
                                      const StyleRequest& style_request) {
  // If non-independent properties are modified, we need to do a full
  // recomputation; otherwise, the properties we're setting could affect
  // the interpretation of other properties (e.g. if a script is setting
  // el.style.fontSize = "24px", that could affect the interpretation
  // of "border-width: 0.2em", but our incremental style recalculation
  // won't update border width).
  //
  // This also covers the case where the inline style got new or removed
  // existing property declarations. We cannot say easily how that would
  // affect the cascade, so we do a full recalculation in that case.
  if (element->GetStyleChangeType() != kInlineIndependentStyleChange) {
    return false;
  }

  // We must, obviously, have an existing style to do incremental calculation.
  if (!element->GetComputedStyle()) {
    return false;
  }

  // Pseudo-elements can't have inline styles. We also don't have the old
  // style in this situation (|element| is the originating element in in
  // this case, so using that style would be wrong).
  if (style_request.IsPseudoStyleRequest()) {
    return false;
  }

  // Links have special handling of visited/not-visited colors (they are
  // represented using special -internal-* properties), which happens
  // during expansion of the CSS cascade. Since incremental style doesn't
  // replicate this behavior, we don't try to compute incremental style
  // for anything that is a link or inside a link.
  if (element->GetComputedStyle()->InsideLink() !=
      EInsideLink::kNotInsideLink) {
    return false;
  }

  // If in the existing style, any inline property _lost_ the cascade
  // (e.g. to an !important class declaration), modifying the ComputedStyle
  // directly may be wrong. This is rare, so we can just skip those cases.
  if (element->GetComputedStyle()->InlineStyleLostCascade()) {
    return false;
  }

  // Custom style callbacks can do style adjustment after style resolution.
  if (element->HasCustomStyleCallbacks()) {
    return false;
  }

  // We don't bother with the root element; it's a special case.
  if (!state.ParentStyle()) {
    return false;
  }

  // We don't currently support combining incremental style and the
  // base computed style animation; we'd have to apply the incremental
  // style onto the base as opposed to the computed style itself,
  // and we don't support that. It should be rare to animate elements
  // _both_ with animations and mutating inline style anyway.
  if (GetElementAnimations(state) || element->GetComputedStyle()->BaseData()) {
    return false;
  }

  // ComputedStyles produced by OOF-interleaving (StyleEngine::
  // UpdateStyleForOutOfFlow) have this flag set. We can not apply the style
  // incrementally on top of this, because ComputedStyles produced by normal
  // style recalcs should not have this flag.
  if (element->GetComputedStyle()->HasAnchorEvaluator()) {
    return false;
  }

  const CSSPropertyValueSet* inline_style = element->InlineStyle();
  if (inline_style) {
    for (const CSSPropertyValue& property : inline_style->Properties()) {
      // If a script mutated inline style properties that are not idempotent,
      // we would not normally even reach this path (we wouldn't get a changed
      // signal saying “inline incremental style modified”, just “style
      // modified”). However, we could have such properties set on inline style
      // _before_ this calculation, and their continued existence blocks us from
      // reusing the style (because e.g. the StyleAdjuster is not necessarily
      // idempotent in such cases).
      if (!CSSProperty::Get(property.PropertyID()).IsIdempotent()) {
        return false;
      }

      // Variables and reverts are resolved in StyleCascade, which we don't run
      // in this path; thus, we cannot support them.
      if (property.Value().IsUnparsedDeclaration() ||
          property.Value().IsPendingSubstitutionValue() ||
          property.Value().IsRevertValue() ||
          property.Value().IsRevertLayerValue()) {
        return false;
      }
    }
  }

  return true;
}

// This is the core of computing base style for a given element, ie., the style
// that does not depend on animations. For our purposes, style consists of three
// parts:
//
//  A. Properties inherited from the parent (parent style).
//  B. Properties that come from the defaults (initial style).
//  C. Properties from CSS rules that apply from this element
//     (matched properties).
//
// The typical flow (barring special rules for pseudo-elements and similar) is:
//
//   1. Collect all CSS rules that apply to this element
//      (MatchAllRules(), into ElementRuleCollector).
//   2. Figure out where we should get parent style (A) from, and where we
//      should get initial style (B) from; typically the parent element and
//      the global initial style, respectively.
//   3. Construct a new ComputedStyle, merging the two sources (InitStyle()).
//   4. Apply all the found properties (C) in the correct order
//      (ApplyPropertiesFromCascade(), using StyleCascade).
//
// However, the MatchedPropertiesCache can often give us A with the correct
// parts of C pre-applied, or similar for B+C, or simply A+B+C (a full MPC hit).
// Thus, after step 1, we look up the set of properties we've collected in the
// MPC, and if we have a full MPC hit, we stop after step 1. (This is the reason
// why step 1 needs to be first.) If we have a partial hit (we can use A+C
// but not B+C, or the other way around), we use that as one of our sources
// in step 3, and can skip the relevant properties in step 4.
//
// The base style is cached by the caller if possible (see ResolveStyle() on
// the “base computed style optimization”).
void StyleResolver::ApplyBaseStyleNoCache(
    Element* element,
    const StyleRecalcContext& style_recalc_context,
    const StyleRequest& style_request,
    StyleResolverState& state,
    StyleCascade& cascade) {
  // For some very special elements (e.g. <video>): Ensure internal UA style
  // rules that are relevant for the element exist in the stylesheet.
  GetDocument().GetStyleEngine().EnsureUAStyleForElement(*element);

  if (!style_request.IsPseudoStyleRequest()) {
    if (IsForcedColorsModeEnabled()) {
      cascade.MutableMatchResult().AddMatchedProperties(
          ForcedColorsUserAgentDeclarations(),
          {.origin = CascadeOrigin::kUserAgent});
    }

    // UA rule: * { overlay: none !important }
    // and
    // UA rule: ::scroll-marker-group { contain: size !important; }
    // Implemented here because DCHECKs ensures we don't add universal rules to
    // the UA sheets. Note that this is a universal rule in any namespace.
    // Adding this to the html.css would only do the override in the HTML
    // namespace since the sheet has a default namespace.
    cascade.MutableMatchResult().AddMatchedProperties(
        UniversalOverlayUserAgentDeclaration(),
        {.origin = CascadeOrigin::kUserAgent});

    // This adds a CSSInitialColorValue to the cascade for the document
    // element. The CSSInitialColorValue will resolve to a color-scheme
    // sensitive color in Color::ApplyValue. It is added at the start of the
    // MatchResult such that subsequent declarations (even from the UA sheet)
    // get a higher priority.
    //
    // TODO(crbug.com/1046753): Remove this when canvastext is supported.
    if (element == state.GetDocument().documentElement()) {
      cascade.MutableMatchResult().AddMatchedProperties(
          DocumentElementUserAgentDeclarations(),
          {.origin = CascadeOrigin::kUserAgent});
    }
  }

  ElementRuleCollector collector(state.ElementContext(), style_recalc_context,
                                 selector_filter_, cascade.MutableMatchResult(),
                                 state.InsideLink());

  if (element->IsPseudoElement() || style_request.IsPseudoStyleRequest()) {
    collector.SetPseudoElementStyleRequest(style_request);
    if (element->IsPseudoElement()) {
      GetDocument().GetStyleEngine().EnsureUAStyleForPseudoElement(
          element->GetPseudoIdForStyling());
    } else {
      GetDocument().GetStyleEngine().EnsureUAStyleForPseudoElement(
          style_request.pseudo_id);
    }
  }

  if (!state.ParentStyle()) {
    // We have no parent so use the initial style as the parent. Note that we
    // need to do this before MPC lookup, so that the parent comparison (to
    // determine if we have a hit on inherited properties) is correctly
    // determined.
    state.SetParentStyle(InitialStyleForElement());
    state.SetLayoutParentStyle(state.ParentStyle());

    if (!style_request.IsPseudoStyleRequest() &&
        *element != GetDocument().documentElement()) {
      // Strictly, we should only allow the root element to inherit from
      // initial styles, but we allow getComputedStyle() for connected
      // elements outside the flat tree rooted at an unassigned shadow host
      // child or a slot fallback element.
      DCHECK((IsShadowHost(element->parentNode()) ||
              IsA<HTMLSlotElement>(element->parentNode())) &&
             !LayoutTreeBuilderTraversal::ParentElement(*element));
    }
  }

  if (style_request.rules_to_include == StyleRequest::kUAOnly) {
    MatchUARules(*element, collector);
  } else {
    MatchAllRules(
        state, collector,
        style_request.matching_behavior != kMatchAllRulesExcludingSMIL);
  }

  const MatchResult& match_result = collector.MatchedResult();

  if (element->IsPseudoElement() || style_request.IsPseudoStyleRequest()) {
    if (!match_result.HasMatchedProperties()) {
      InitStyle(*element, style_request, *initial_style_, state.ParentStyle(),
                state);
      StyleAdjuster::AdjustComputedStyle(state, nullptr /* element */);
      state.SetHadNoMatchedProperties();
      return;
    }
  }

  const MatchResult& result = cascade.GetMatchResult();
  CacheSuccess cache_success = ApplyMatchedCache(state, style_request, result);
  ComputedStyleBuilder& builder = state.StyleBuilder();

  if (style_recalc_context.is_ensuring_style &&
      style_recalc_context.is_outside_flat_tree) {
    builder.SetIsEnsuredOutsideFlatTree();
  }

  if (!cache_success.IsHit()) {
    ApplyPropertiesFromCascade(state, cascade);
    MaybeAddToMatchedPropertiesCache(state, cache_success.key);
  }

  // TODO(crbug.com/1024156): do this for CustomHighlightNames too, so we
  // can remove the cache-busting for ::highlight() in IsStyleCacheable
  builder.SetHasNonUniversalHighlightPseudoStyles(
      match_result.HasNonUniversalHighlightPseudoStyles());
  builder.SetHasNonUaHighlightPseudoStyles(
      match_result.HasNonUaHighlightPseudoStyles());
  builder.SetHighlightsDependOnSizeContainerQueries(
      match_result.HighlightsDependOnSizeContainerQueries());

  if (match_result.HasFlag(MatchFlag::kAffectedByDrag)) {
    builder.SetAffectedByDrag();
  }
  if (match_result.HasFlag(MatchFlag::kAffectedByFocusWithin)) {
    builder.SetAffectedByFocusWithin();
  }
  if (match_result.HasFlag(MatchFlag::kAffectedByHover)) {
    builder.SetAffectedByHover();
  }
  if (match_result.HasFlag(MatchFlag::kAffectedByActive)) {
    builder.SetAffectedByActive();
  }
  if (match_result.HasFlag(MatchFlag::kAffectedByStartingStyle)) {
    builder.SetIsStartingStyle();
  }
  if (match_result.DependsOnSizeContainerQueries()) {
    builder.SetDependsOnSizeContainerQueries(true);
  }
  if (match_result.DependsOnStyleContainerQueries()) {
    builder.SetDependsOnStyleContainerQueries(true);
  }
  if (match_result.DependsOnScrollStateContainerQueries()) {
    builder.SetDependsOnScrollStateContainerQueries(true);
  }
  if (match_result.FirstLineDependsOnSizeContainerQueries()) {
    builder.SetFirstLineDependsOnSizeContainerQueries(true);
  }
  if (match_result.DependsOnStaticViewportUnits()) {
    builder.SetHasStaticViewportUnits();
  }
  if (match_result.DependsOnDynamicViewportUnits()) {
    builder.SetHasDynamicViewportUnits();
  }
  if (match_result.DependsOnRootFontContainerQueries()) {
    builder.SetHasRootFontRelativeUnits();
  }
  if (match_result.ConditionallyAffectsAnimations()) {
    state.SetConditionallyAffectsAnimations();
  }
  if (!match_result.CustomHighlightNames().empty()) {
    builder.SetCustomHighlightNames(match_result.CustomHighlightNames());
  }
  builder.SetPseudoElementStyles(match_result.PseudoElementStyles());

  if (element->IsPseudoElement()) {
    state.StyleBuilder().SetStyleType(element->GetPseudoIdForStyling());
  }

  // Now we're done with all operations that may overwrite InsideLink,
  // so we can set it once and for all.
  builder.SetInsideLink(state.InsideLink());

  ApplyCallbackSelectors(state);
  if (element->IsLink() && (element->HasTagName(html_names::kATag) ||
                            element->HasTagName(html_names::kAreaTag))) {
    ApplyDocumentRulesSelectors(state, To<ContainerNode>(&element->TreeRoot()));
  }

  // Cache our if our original display is inline.
  builder.SetIsOriginalDisplayInlineType(
      ComputedStyle::IsDisplayInlineType(builder.Display()));

  StyleAdjuster::AdjustComputedStyle(
      state, style_request.IsPseudoStyleRequest() ? nullptr : element);

  ApplyAnchorData(state);
}

// In the normal case, just a forwarder to ApplyBaseStyleNoCache(); see that
// function for the meat of the computation. However, this is where the
// “computed base style optimization” is applied if possible, and also
// incremental inline style updates:
//
// If we have an existing computed style, and the only changes have been
// mutations of independent properties on the element's inline style
// (see CanApplyInlineStyleIncrementally() for the precise conditions),
// we may reuse the old computed style and just reapply the element's
// inline style on top of it. This allows us to skip collecting elements
// and computing the full cascade, which can be a significant win when
// animating elements via inline style from JavaScript.
=======
>>>>>>> chromium
void StyleResolver::ApplyBaseStyle(
    Element* element,
    const StyleRecalcContext& style_recalc_context,
    const StyleRequest& style_request,
    StyleResolverState& state,
    StyleCascade& cascade) {
  DCHECK(style_request.pseudo_id != kPseudoIdFirstLineInherited);

  bool base_is_usable =
      state.CanCacheBaseStyle() && CanReuseBaseComputedStyle(state);
  const ComputedStyle* animation_base_computed_style =
      base_is_usable ? CachedAnimationBaseComputedStyle(state) : nullptr;
  if (ShouldComputeBaseComputedStyle(animation_base_computed_style)) {
    InitStyleAndApplyInheritance(*element, style_request, state);

    GetDocument().GetStyleEngine().EnsureUAStyleForElement(*element);

    // This adds a CSSInitialColorValue to the cascade for the document
    // element. The CSSInitialColorValue will resolve to a color-scheme
    // sensitive color in Color::ApplyValue. It is added at the start of the
    // MatchResult such that subsequent declarations (even from the UA sheet)
    // get a higher priority.
    //
    // TODO(crbug.com/1046753): Remove this when canvastext is supported.
    if (!style_request.IsPseudoStyleRequest() &&
        element == state.GetDocument().documentElement()) {
      cascade.MutableMatchResult().AddMatchedProperties(
          DocumentElementUserAgentDeclarations());
    }

    ElementRuleCollector collector(state.ElementContext(), style_recalc_context,
                                   selector_filter_,
                                   cascade.MutableMatchResult(), state.Style(),
                                   state.Style()->InsideLink());

    if (style_request.IsPseudoStyleRequest()) {
      collector.SetPseudoElementStyleRequest(style_request);
      GetDocument().GetStyleEngine().EnsureUAStyleForPseudoElement(
          style_request.pseudo_id);
    }

    // TODO(obrufau): support styling nested pseudo-elements
    if (style_request.IsPseudoStyleRequest() && element->IsPseudoElement()) {
      MatchUARules(*element, collector);
    } else {
      MatchAllRules(
          state, collector,
          style_request.matching_behavior != kMatchAllRulesExcludingSMIL);
    }

    if (tracker_)
      AddMatchedRulesToTracker(collector);

    if (style_request.IsPseudoStyleRequest() &&
        !collector.MatchedResult().HasMatchedProperties()) {
      StyleAdjuster::AdjustComputedStyle(state, nullptr /* element */);
      state.SetHadNoMatchedProperties();
      return;
    }

    if (!style_request.IsPseudoStyleRequest() && element->GetComputedStyle() &&
        element->GetComputedStyle()->TextAutosizingMultiplier() !=
            state.Style()->TextAutosizingMultiplier()) {
      // Preserve the text autosizing multiplier on style recalc. Autosizer will
      // update it during layout if needed.
      // NOTE: this must occur before ApplyMatchedProperties for correct
      // computation of font-relative lengths.
      state.Style()->SetTextAutosizingMultiplier(
          element->GetComputedStyle()->TextAutosizingMultiplier());
    }

    CascadeAndApplyMatchedProperties(state, cascade);

    if (collector.MatchedResult().DependsOnContainerQueries())
      state.Style()->SetDependsOnContainerQueries(true);

    ApplyCallbackSelectors(state);

    // Cache our original display.
    state.Style()->SetOriginalDisplay(state.Style()->Display());

    StyleAdjuster::AdjustComputedStyle(
        state, style_request.IsPseudoStyleRequest() ? nullptr : element);

    DCHECK_EQ(g_null_atom, ComputeBaseComputedStyleDiff(
                               animation_base_computed_style, *state.Style()));
  }

  if (base_is_usable) {
    DCHECK(animation_base_computed_style);
    state.SetStyle(ComputedStyle::Clone(*animation_base_computed_style));
    state.Style()->SetStyleType(style_request.pseudo_id);
    if (!state.ParentStyle()) {
      state.SetParentStyle(InitialStyleForElement());
      state.SetLayoutParentStyle(state.ParentStyle());
    }
    MaybeResetCascade(cascade);
    INCREMENT_STYLE_STATS_COUNTER(GetDocument().GetStyleEngine(),
                                  base_styles_used, 1);
  }
<<<<<<< HEAD

  if (style_recalc_context.can_use_incremental_style &&
      CanApplyInlineStyleIncrementally(element, state, style_request)) {
    // We are in a situation where we can reuse the old style
    // and just apply the element's inline style on top of it
    // (see the function comment).
    state.SetStyle(*element->GetComputedStyle());

    // This is always false when creating a new style, but is not reset
    // when copying the style, so it needs to happen here. After us,
    // Element::StyleForLayoutObject() will call AdjustElementStyle(),
    // which sets it to true if applicable.
    state.StyleBuilder().ResetSkipsContents();

    const CSSPropertyValueSet* inline_style = element->InlineStyle();
    if (inline_style) {
      for (const CSSPropertyValue& property : inline_style->Properties()) {
        StyleBuilder::ApplyProperty(
            property.Name(), state,
            property.Value().EnsureScopedValue(&GetDocument()));
      }
    }

    // Sets flags related to length unit conversions which may have taken
    // place during StyleBuilder::ApplyProperty.
    ApplyLengthConversionFlags(state);

    StyleAdjuster::AdjustComputedStyle(
        state, style_request.IsPseudoStyleRequest() ? nullptr : element);

    // Normally done by StyleResolver::MaybeAddToMatchedPropertiesCache(),
    // when applying the cascade. Note that this is probably redundant
    // (we'll be loading pending resources later), but not doing so would
    // currently create diffs below.
    state.LoadPendingResources();

    ApplyAnchorData(state);

#if DCHECK_IS_ON()
    // Verify that we got the right answer.
    const ComputedStyle* incremental_style = state.TakeStyle();
    ApplyBaseStyleNoCache(element, style_recalc_context, style_request, state,
                          cascade);

    // Having false positives here is OK (and can happen if an inline style
    // element used to be “inherit” but no longer is); it is only used to see
    // whether parent elements need to propagate inherited properties down to
    // children or not. We'd be doing too much work in such cases, but still
    // maintain correctness.
    if (incremental_style->HasExplicitInheritance()) {
      state.StyleBuilder().SetHasExplicitInheritance();
    }

    // Similarly, if a style went from using viewport units to not,
    // the flags can stick around in the incremental version. This can cause
    // invalidations when none are needed, but is otherwise harmless.
    state.StyleBuilder().SetViewportUnitFlags(
        state.StyleBuilder().ViewportUnitFlags() |
        incremental_style->ViewportUnitFlags());

    const ComputedStyle* style_snapshot = state.StyleBuilder().CloneStyle();
    DCHECK_EQ(g_null_atom,
              ComputeBaseComputedStyleDiff(incremental_style, *style_snapshot));
    // The incremental style must not contain BaseData, otherwise we'd risk
    // creating an infinite chain of BaseData/ComputedStyle in
    // ApplyAnimatedStyle.
    DCHECK(!incremental_style->BaseData());
#endif
    return;
  }

  // None of the caches applied, so we need a full recalculation.
  ApplyBaseStyleNoCache(element, style_recalc_context, style_request, state,
                        cascade);
=======
>>>>>>> chromium
}

CompositorKeyframeValue* StyleResolver::CreateCompositorKeyframeValueSnapshot(
    Element& element,
    const ComputedStyle& base_style,
    const ComputedStyle* parent_style,
    const PropertyHandle& property,
    const CSSValue* value,
    double offset) {
  // TODO(alancutter): Avoid creating a StyleResolverState just to apply a
  // single value on a ComputedStyle.
  // TOOD(crbug.com/1223030): Propagate a real StyleRecalcContext to handle
  // container relative units.
  StyleResolverState state(element.GetDocument(), element, StyleRecalcContext(),
                           StyleRequest(parent_style));
  state.SetStyle(ComputedStyle::Clone(base_style));
  if (value) {
    STACK_UNINITIALIZED StyleCascade cascade(state);
    auto* set =
        MakeGarbageCollected<MutableCSSPropertyValueSet>(state.GetParserMode());
    set->SetProperty(property.GetCSSProperty().PropertyID(), *value);
    cascade.MutableMatchResult().FinishAddingUARules();
    cascade.MutableMatchResult().FinishAddingUserRules();
    cascade.MutableMatchResult().AddMatchedProperties(set);
    cascade.MutableMatchResult().FinishAddingAuthorRulesForTreeScope(
        element.GetTreeScope());
    cascade.Apply();
  }
  return CompositorKeyframeValueFactory::Create(property, *state.Style(),
                                                offset);
}

scoped_refptr<const ComputedStyle> StyleResolver::StyleForPage(
    uint32_t page_index,
    const AtomicString& page_name) {
  scoped_refptr<const ComputedStyle> initial_style = InitialStyleForElement();
  if (!GetDocument().documentElement())
    return initial_style;

  StyleResolverState state(GetDocument(), *GetDocument().documentElement(),
                           StyleRecalcContext(),
                           StyleRequest(initial_style.get()));

<<<<<<< HEAD
    LayoutView* layout_view = document_->GetLayoutView();
    document_icb_size_ = layout_view->InitialContainingBlockSizeForPrinting();

    const LocalFrame* frame = document_->GetFrame();
    auto page_context_viewport_size = PhysicalSize::FromSizeFRound(
        frame->GetPrintParams().default_page_description.size);
    layout_view->SetInitialContainingBlockSizeForPrinting(
        page_context_viewport_size);
    document->GetStyleEngine().UpdateViewportSize();
  }
  ~ViewportSizeChangeScopeForPrinting() {
    if (!document_icb_size_) {
      return;
    }
    document_->GetLayoutView()->SetInitialContainingBlockSizeForPrinting(
        *document_icb_size_);
    document_->GetStyleEngine().UpdateViewportSize();
  }

 private:
  Document* document_;
  std::optional<PhysicalSize> document_icb_size_;
};

const ComputedStyle* StyleResolver::StyleForPage(uint32_t page_index,
                                                 const AtomicString& page_name,
                                                 float page_fitting_scale,
                                                 bool ignore_author_style) {
  // The page context inherits from the root element.
  Element* root_element = GetDocument().documentElement();
  if (!root_element) {
    return InitialStyleForElement();
  }
  DCHECK(!GetDocument().NeedsLayoutTreeUpdateForNode(*root_element));
  const ComputedStyle* parent_style =
      ComputedStyle::NullifyEnsured(root_element->GetComputedStyle());
  if (!parent_style) {
    // The root is display:none. One page box will still be created, but no
    // properties should apply.
    return InitialStyleForElement();
  }
  StyleResolverState state(GetDocument(), *root_element,
                           nullptr /* StyleRecalcContext */,
                           StyleRequest(parent_style));
  state.CreateNewStyle(*InitialStyleForElement(), *parent_style);

  auto& builder = state.StyleBuilder();
  // Page boxes are blocks.
  builder.SetDisplay(EDisplay::kBlock);

  // Temporarily set the viewport size to the size of the default page box
  // specified in the print parameters.
  ViewportSizeChangeScopeForPrinting use_default_page_box_size(&GetDocument());
=======
  scoped_refptr<ComputedStyle> style = CreateComputedStyle();
  const ComputedStyle* root_element_style =
      state.RootElementStyle() ? state.RootElementStyle()
                               : GetDocument().GetComputedStyle();
  DCHECK(root_element_style);
  style->InheritFrom(*root_element_style);
  state.SetStyle(std::move(style));
>>>>>>> chromium

  STACK_UNINITIALIZED StyleCascade cascade(state);

  PageRuleCollector collector(root_element_style, page_index, page_name,
                              cascade.MutableMatchResult());

  collector.MatchPageRules(
      CSSDefaultStyleSheets::Instance().DefaultPrintStyle());

  if (ScopedStyleResolver* scoped_resolver =
          GetDocument().GetScopedStyleResolver())
    scoped_resolver->MatchPageRules(collector);

  cascade.Apply();

  // Now return the style.
  return state.TakeStyle();
}

const ComputedStyle& StyleResolver::InitialStyle() const {
  return *initial_style_;
}

scoped_refptr<ComputedStyle> StyleResolver::CreateComputedStyle() const {
  return ComputedStyle::Clone(*initial_style_);
}

scoped_refptr<ComputedStyle> StyleResolver::InitialStyleForElement() const {
  const LocalFrame* frame = GetDocument().GetFrame();

  scoped_refptr<ComputedStyle> initial_style = CreateComputedStyle();

  initial_style->SetRtlOrdering(
      GetDocument().VisuallyOrdered() ? EOrder::kVisual : EOrder::kLogical);
  initial_style->SetZoom(
      frame && !GetDocument().Printing() ? frame->PageZoomFactor() : 1);
  initial_style->SetEffectiveZoom(initial_style->Zoom());
  initial_style->SetInForcedColorsMode(GetDocument().InForcedColorsMode());
  initial_style->SetTapHighlightColor(
      ComputedStyleInitialValues::InitialTapHighlightColor());

  FontDescription document_font_description =
      initial_style->GetFontDescription();
  document_font_description.SetLocale(
      LayoutLocale::Get(GetDocument().ContentLanguage()));

  initial_style->SetFontDescription(document_font_description);
  initial_style->SetUserModify(GetDocument().InDesignMode()
                                   ? EUserModify::kReadWrite
                                   : EUserModify::kReadOnly);
  FontBuilder(&GetDocument()).CreateInitialFont(*initial_style);

  scoped_refptr<StyleInitialData> initial_data =
      GetDocument().GetStyleEngine().MaybeCreateAndGetInitialData();
  if (initial_data)
    initial_style->SetInitialData(std::move(initial_data));

  return initial_style;
}

scoped_refptr<const ComputedStyle> StyleResolver::StyleForText(
    Text* text_node) {
  DCHECK(text_node);
  if (Node* parent_node = LayoutTreeBuilderTraversal::Parent(*text_node)) {
    const ComputedStyle* style = parent_node->GetComputedStyle();
    if (style && !style->IsEnsuredInDisplayNone())
      return style;
  }
  return nullptr;
}

void StyleResolver::UpdateFont(StyleResolverState& state) {
  state.GetFontBuilder().CreateFont(state.StyleRef(), state.ParentStyle());
  state.SetConversionFontSizes(CSSToLengthConversionData::FontSizes(
      state.Style(), state.RootElementStyle()));
  state.SetConversionZoom(state.Style()->EffectiveZoom());
}

void StyleResolver::AddMatchedRulesToTracker(
    const ElementRuleCollector& collector) {
  collector.AddMatchedRulesToTracker(tracker_);
}

StyleRuleList* StyleResolver::StyleRulesForElement(Element* element,
                                                   unsigned rules_to_include) {
  DCHECK(element);
  StyleResolverState state(GetDocument(), *element);
  MatchResult match_result;
  // TODO(crbug.com/1145970): Use actual StyleRecalcContext.
  StyleRecalcContext style_recalc_context;
  ElementRuleCollector collector(state.ElementContext(), style_recalc_context,
                                 selector_filter_, match_result, state.Style(),
                                 EInsideLink::kNotInsideLink);
  collector.SetMode(SelectorChecker::kCollectingStyleRules);
  CollectPseudoRulesForElement(*element, collector, kPseudoIdNone,
                               rules_to_include);
  return collector.MatchedStyleRuleList();
}

HeapHashMap<CSSPropertyName, Member<const CSSValue>>
StyleResolver::CascadedValuesForElement(Element* element, PseudoId pseudo_id) {
  StyleResolverState state(GetDocument(), *element);
  state.SetStyle(CreateComputedStyle());

  STACK_UNINITIALIZED StyleCascade cascade(state);
  // TODO(crbug.com/1145970): Use actual StyleRecalcContext.
  StyleRecalcContext style_recalc_context;
  ElementRuleCollector collector(state.ElementContext(), style_recalc_context,
                                 selector_filter_, cascade.MutableMatchResult(),
                                 state.Style(), EInsideLink::kNotInsideLink);
  collector.SetPseudoElementStyleRequest(StyleRequest(pseudo_id, nullptr));
  MatchAllRules(state, collector, false /* include_smil_properties */);

  cascade.Apply();
  return cascade.GetCascadedValues();
}

Element* StyleResolver::FindContainerForElement(
    Element* element,
<<<<<<< HEAD
    const ContainerSelector& container_selector,
    const TreeScope* selector_tree_scope) {
  DCHECK(element);
  return ContainerQueryEvaluator::FindContainer(
      FlatTreeTraversal::ParentElement(*element), container_selector,
      selector_tree_scope);
=======
    const AtomicString& container_name) {
  auto context = StyleRecalcContext::FromAncestors(*element);
  return ContainerQueryEvaluator::FindContainer(context, container_name);
>>>>>>> chromium
}

RuleIndexList* StyleResolver::PseudoCSSRulesForElement(
    Element* element,
    PseudoId pseudo_id,
    unsigned rules_to_include) {
  DCHECK(element);
  StyleResolverState state(GetDocument(), *element);
  MatchResult match_result;
  StyleRecalcContext style_recalc_context =
      StyleRecalcContext::FromAncestors(*element);
  ElementRuleCollector collector(state.ElementContext(), style_recalc_context,
                                 selector_filter_, match_result, state.Style(),
                                 EInsideLink::kNotInsideLink);
  collector.SetMode(SelectorChecker::kCollectingCSSRules);
  // TODO(obrufau): support collecting rules for nested ::marker
  if (!element->IsPseudoElement()) {
    CollectPseudoRulesForElement(*element, collector, pseudo_id,
                                 rules_to_include);
  }

  if (tracker_)
    AddMatchedRulesToTracker(collector);
  return collector.MatchedCSSRuleList();
}

RuleIndexList* StyleResolver::CssRulesForElement(Element* element,
                                                 unsigned rules_to_include) {
  return PseudoCSSRulesForElement(element, kPseudoIdNone, rules_to_include);
}

void StyleResolver::CollectPseudoRulesForElement(
    const Element& element,
    ElementRuleCollector& collector,
    PseudoId pseudo_id,
    unsigned rules_to_include) {
  collector.SetPseudoElementStyleRequest(StyleRequest(pseudo_id, nullptr));

  if (rules_to_include & kUACSSRules)
    MatchUARules(element, collector);
  else
    collector.FinishAddingUARules();

  if (rules_to_include & kUserCSSRules)
    MatchUserRules(collector);
  else
    collector.FinishAddingUserRules();

  if (rules_to_include & kAuthorCSSRules) {
    collector.SetSameOriginOnly(!(rules_to_include & kCrossOriginCSSRules));
    collector.SetIncludeEmptyRules(rules_to_include & kEmptyCSSRules);
    MatchAuthorRules(element, ScopedResolverFor(element), collector);
  }
}

<<<<<<< HEAD
bool StyleResolver::ApplyAnimatedStyle(
    StyleResolverState& state,
    StyleCascade& cascade,
    const StyleRecalcContext& style_recalc_context) {
  Element& element = state.GetUltimateOriginatingElementOrSelf();
=======
bool StyleResolver::ApplyAnimatedStyle(StyleResolverState& state,
                                       StyleCascade& cascade) {
  Element& element = state.GetElement();
>>>>>>> chromium

  // The animating element may be this element, the pseudo element we are
  // resolving style for, or null if we are resolving style for a pseudo
  // element which is not represented by a PseudoElement like scrollbar pseudo
  // elements.
  Element* animating_element = state.GetAnimatingElement();

  if (!animating_element)
    return false;

  DCHECK(animating_element == &element ||
         animating_element->ParentOrShadowHostElement() == element);

  if (!HasAnimationsOrTransitions(state)) {
    // Ensure that the base computed style is not stale even if not currently
    // running an animation or transition. This ensures that any new transitions
    // use the correct starting point based on the "before change" style.
    UpdateAnimationBaseComputedStyle(state, cascade, false);
    return false;
  }

  CSSAnimations::CalculateAnimationUpdate(
<<<<<<< HEAD
      state.AnimationUpdate(), *animating_element, element,
      state.StyleBuilder(), state.ParentStyle(), this,
      state.CanTriggerAnimations());
  CSSAnimations::CalculateTransitionUpdate(
      state.AnimationUpdate(), *animating_element, state.StyleBuilder(),
      state.OldStyle(), style_recalc_context, state.CanTriggerAnimations());

  bool apply = !state.AnimationUpdate().IsEmpty();
  if (apply) {
    const ActiveInterpolationsMap& animations =
        state.AnimationUpdate().ActiveInterpolationsForAnimations();
    const ActiveInterpolationsMap& transitions =
        state.AnimationUpdate().ActiveInterpolationsForTransitions();

    cascade.AddInterpolations(&animations, CascadeOrigin::kAnimation);
    cascade.AddInterpolations(&transitions, CascadeOrigin::kTransition);

    // Note: this applies the same filter to pseudo elements as its originating
    // element since state.GetElement() returns the originating element when
    // resolving style for pseudo elements.
    CascadeFilter filter =
        UltimateOriginatingElementOrSelf(state.GetElement()).GetCascadeFilter();
    if (state.StyleBuilder().StyleType() == kPseudoIdMarker) {
      filter = filter.Add(CSSProperty::kValidForMarker, false);
    }
    if (IsHighlightPseudoElement(state.StyleBuilder().StyleType())) {
      if (UsesHighlightPseudoInheritance(state.StyleBuilder().StyleType())) {
        filter = filter.Add(CSSProperty::kValidForHighlight, false);
      } else {
        filter = filter.Add(CSSProperty::kValidForHighlightLegacy, false);
      }
    }
    filter = filter.Add(CSSProperty::kAnimation, true);

    cascade.Apply(filter);

    // Start loading resources used by animations.
    state.LoadPendingResources();

    // Apply any length conversion flags produced by CSS/Web animations (e.g.
    // animations involving viewport units would set such flags).
    ApplyLengthConversionFlags(state);

    DCHECK(!state.GetFontBuilder().FontDirty());
  }

=======
      state.AnimationUpdate(), *animating_element, state.GetElement(),
      *state.Style(), state.ParentStyle(), this);
>>>>>>> chromium
  CSSAnimations::CalculateCompositorAnimationUpdate(
      state.AnimationUpdate(), *animating_element, element, *state.Style(),
      state.ParentStyle(), WasViewportResized());
  CSSAnimations::CalculateTransitionUpdate(state.AnimationUpdate(),
                                           *animating_element, *state.Style());

  CSSAnimations::SnapshotCompositorKeyframes(
      element, state.AnimationUpdate(), *state.Style(), state.ParentStyle());

  bool has_update = !state.AnimationUpdate().IsEmpty();
  UpdateAnimationBaseComputedStyle(state, cascade, has_update);

  if (!has_update)
    return false;

  const ActiveInterpolationsMap& animations =
      state.AnimationUpdate().ActiveInterpolationsForAnimations();
  const ActiveInterpolationsMap& transitions =
      state.AnimationUpdate().ActiveInterpolationsForTransitions();

  cascade.AddInterpolations(&animations, CascadeOrigin::kAnimation);
  cascade.AddInterpolations(&transitions, CascadeOrigin::kTransition);

  CascadeFilter filter;
  if (state.Style()->StyleType() == kPseudoIdMarker)
    filter = filter.Add(CSSProperty::kValidForMarker, false);
  if (IsHighlightPseudoElement(state.Style()->StyleType()))
    filter = filter.Add(CSSProperty::kValidForHighlight, false);
  filter = filter.Add(CSSProperty::kAnimation, true);

  cascade.Apply(filter);

  // Start loading resources used by animations.
  state.LoadPendingResources();

  DCHECK(!state.GetFontBuilder().FontDirty());

  return true;
}

StyleRuleKeyframes* StyleResolver::FindKeyframesRule(
    const Element* element,
    const AtomicString& animation_name) {
  HeapVector<Member<ScopedStyleResolver>, 8> resolvers;
  CollectScopedResolversForHostedShadowTrees(*element, resolvers);
  if (ScopedStyleResolver* scoped_resolver =
          element->GetTreeScope().GetScopedStyleResolver())
    resolvers.push_back(scoped_resolver);

  for (auto& resolver : resolvers) {
    if (StyleRuleKeyframes* keyframes_rule =
            resolver->KeyframeStylesForAnimation(animation_name))
      return keyframes_rule;
  }

  if (StyleRuleKeyframes* keyframes_rule =
          GetDocument().GetStyleEngine().KeyframeStylesForAnimation(
              animation_name))
    return keyframes_rule;

<<<<<<< HEAD
  // Match UA keyframe rules after user and author rules.
  StyleRuleKeyframes* matched_keyframes_rule = nullptr;
  auto func = [&matched_keyframes_rule, &animation_name](
                  RuleSet* rules, unsigned rule_set_index) {
    auto keyframes_rules = rules->KeyframesRules();
    for (auto& keyframes_rule : keyframes_rules) {
      if (keyframes_rule->GetName() == animation_name) {
        matched_keyframes_rule = keyframes_rule;
      }
    }
  };
  ForEachUARulesForElement(*animating_element, nullptr, func);
  if (matched_keyframes_rule) {
    return FindKeyframesRuleResult{matched_keyframes_rule, nullptr};
  }

  for (auto& resolver : resolvers) {
=======
  for (auto& resolver : resolvers)
>>>>>>> chromium
    resolver->SetHasUnresolvedKeyframesRule();
  return nullptr;
}

void StyleResolver::InvalidateMatchedPropertiesCache() {
  matched_properties_cache_.Clear();
}

void StyleResolver::SetResizedForViewportUnits() {
  was_viewport_resized_ = true;
  GetDocument().GetStyleEngine().UpdateActiveStyle();
  matched_properties_cache_.ClearViewportDependent();
}

void StyleResolver::ClearResizedForViewportUnits() {
  was_viewport_resized_ = false;
}

bool StyleResolver::CacheSuccess::EffectiveZoomChanged(
    const ComputedStyle& style) const {
  if (!cached_matched_properties)
    return false;
  return cached_matched_properties->computed_style->EffectiveZoom() !=
         style.EffectiveZoom();
}

bool StyleResolver::CacheSuccess::FontChanged(
    const ComputedStyle& style) const {
  if (!cached_matched_properties)
    return false;
  return cached_matched_properties->computed_style->GetFontDescription() !=
         style.GetFontDescription();
}

bool StyleResolver::CacheSuccess::InheritedVariablesChanged(
    const ComputedStyle& style) const {
  if (!cached_matched_properties)
    return false;
  return cached_matched_properties->computed_style->InheritedVariables() !=
         style.InheritedVariables();
}

bool StyleResolver::CacheSuccess::IsUsableAfterApplyInheritedOnly(
    const ComputedStyle& style) const {
  return !EffectiveZoomChanged(style) && !FontChanged(style) &&
         !InheritedVariablesChanged(style);
}

StyleResolver::CacheSuccess StyleResolver::ApplyMatchedCache(
    StyleResolverState& state,
    const MatchResult& match_result) {
  const Element& element = state.GetElement();

  MatchedPropertiesCache::Key key(match_result);

  bool is_inherited_cache_hit = false;
  bool is_non_inherited_cache_hit = false;
  const CachedMatchedProperties* cached_matched_properties =
      key.IsValid() ? matched_properties_cache_.Find(key, state) : nullptr;

  if (cached_matched_properties && MatchedPropertiesCache::IsCacheable(state)) {
    INCREMENT_STYLE_STATS_COUNTER(GetDocument().GetStyleEngine(),
                                  matched_property_cache_hit, 1);
    // We can build up the style by copying non-inherited properties from an
    // earlier style object built using the same exact style declarations. We
    // then only need to apply the inherited properties, if any, as their values
    // can depend on the element context. This is fast and saves memory by
    // reusing the style data structures. Note that we cannot do this if the
    // direct parent is a ShadowRoot.
    if (state.ParentStyle()->InheritedDataShared(
            *cached_matched_properties->parent_computed_style) &&
        !IsAtShadowBoundary(&element)) {
      INCREMENT_STYLE_STATS_COUNTER(GetDocument().GetStyleEngine(),
                                    matched_property_cache_inherited_hit, 1);

      EInsideLink link_status = state.Style()->InsideLink();
      // If the cache item parent style has identical inherited properties to
      // the current parent style then the resulting style will be identical
      // too. We copy the inherited properties over from the cache and are done.
      state.Style()->InheritFrom(*cached_matched_properties->computed_style);

      // Unfortunately the link status is treated like an inherited property. We
      // need to explicitly restore it.
      state.Style()->SetInsideLink(link_status);

      is_inherited_cache_hit = true;
    }
    if (!IsForcedColorsModeEnabled() || is_inherited_cache_hit) {
      state.Style()->CopyNonInheritedFromCached(
          *cached_matched_properties->computed_style);
      // If the child style is a cache hit, we'll never reach StyleBuilder::
      // ApplyProperty, hence we'll never set the flag on the parent.
      if (state.Style()->HasExplicitInheritance())
        state.ParentStyle()->SetChildHasExplicitInheritance();
      is_non_inherited_cache_hit = true;
    }
<<<<<<< HEAD
    state.UpdateFont();
  } else {
    // Initialize a new, plain ComputedStyle with only initial
    // style and inheritance accounted for. We'll return a cache
    // miss, which will cause the caller to apply all the matched
    // properties on top of it.
    //
    // We use a different initial_style for <img> elements to match the
    // overrides in html.css. This avoids allocation overhead from copy-on-write
    // when these properties are set only via UA styles. The overhead shows up
    // on MotionMark, which stress-tests this code. See crbug.com/1369454 for
    // details.
    const ComputedStyle& initial_style = IsA<HTMLImageElement>(element)
                                             ? *initial_style_for_img_
                                             : *initial_style_;
    InitStyle(element, style_request, initial_style, state.ParentStyle(),
              state);

    // contenteditable attribute (implemented by -webkit-user-modify) should
    // be propagated from shadow host to distributed node.
    //
    // This can be overridden by matched properties, so we don't want to do it
    // when we have a cache hit; both this fixup and any overriding of it have
    // already been applied in the cached data.
    if (!element.IsPseudoElement() && !style_request.IsPseudoStyleRequest() &&
        element.AssignedSlot()) {
      if (Element* parent = element.parentElement()) {
        if (!RuntimeEnabledFeatures::
                InheritUserModifyWithoutContenteditableEnabled() ||
            !element.FastHasAttribute(html_names::kContenteditableAttr)) {
          if (const ComputedStyle* shadow_host_style =
                  parent->GetComputedStyle()) {
            state.StyleBuilder().SetUserModify(shadow_host_style->UserModify());
          }
        }
      }
    }
=======
    UpdateFont(state);
>>>>>>> chromium
  }

  return CacheSuccess(is_inherited_cache_hit, is_non_inherited_cache_hit, key,
                      cached_matched_properties);
}

void StyleResolver::MaybeAddToMatchedPropertiesCache(
    StyleResolverState& state,
    const CacheSuccess& cache_success,
    const MatchResult& match_result) {
  state.LoadPendingResources();
  if (!cache_success.cached_matched_properties && cache_success.key.IsValid() &&
      MatchedPropertiesCache::IsCacheable(state)) {
    INCREMENT_STYLE_STATS_COUNTER(GetDocument().GetStyleEngine(),
                                  matched_property_cache_added, 1);
    matched_properties_cache_.Add(cache_success.key, *state.Style(),
                                  *state.ParentStyle());
  }
}

bool StyleResolver::CanReuseBaseComputedStyle(const StyleResolverState& state) {
  // TODO(crbug.com/1180159): @container and transitions properly.
  if (RuntimeEnabledFeatures::CSSContainerQueriesEnabled())
    return false;

  ElementAnimations* element_animations = GetElementAnimations(state);
  if (!element_animations || !element_animations->BaseComputedStyle())
    return false;

  if (!element_animations->IsAnimationStyleChange())
    return false;

  // Animating a custom property can have side effects on other properties
  // via variable references. Disallow base computed style optimization in such
  // cases.
  if (CSSAnimations::IsAnimatingCustomProperties(element_animations))
    return false;

  // We need to build the cascade to know what to revert to.
  if (CSSAnimations::IsAnimatingRevert(element_animations))
    return false;

  // When applying an animation or transition for a font affecting property,
  // font-relative units (e.g. em, ex) in the base style must respond to the
  // animation. We cannot use the base computed style optimization in such
  // cases.
  if (CSSAnimations::IsAnimatingFontAffectingProperties(element_animations)) {
    if (element_animations->BaseComputedStyle() &&
        element_animations->BaseComputedStyle()->HasFontRelativeUnits()) {
      return false;
    }
  }

  // Normally, we apply all active animation effects on top of the style created
  // by regular CSS declarations. However, !important declarations have a
  // higher priority than animation effects [1]. If we're currently animating
  // (not transitioning) a property which was declared !important in the base
  // style, we disable the base computed style optimization.
  // [1] https://drafts.csswg.org/css-cascade-4/#cascade-origin
  if (CSSAnimations::IsAnimatingStandardProperties(
          element_animations, element_animations->BaseImportantSet(),
          KeyframeEffect::kDefaultPriority)) {
    return false;
  }

  return true;
}

const CSSValue* StyleResolver::ComputeValue(
    Element* element,
    const CSSPropertyName& property_name,
    const CSSValue& value) {
  const ComputedStyle* base_style = element->GetComputedStyle();
  StyleResolverState state(element->GetDocument(), *element);
  STACK_UNINITIALIZED StyleCascade cascade(state);
  state.SetStyle(ComputedStyle::Clone(*base_style));
  auto* set =
      MakeGarbageCollected<MutableCSSPropertyValueSet>(state.GetParserMode());
  if (property_name.IsCustomProperty()) {
    set->SetProperty(CSSPropertyValue(property_name, value));
  } else {
    set->SetProperty(property_name.Id(), value);
  }
  cascade.MutableMatchResult().FinishAddingUARules();
  cascade.MutableMatchResult().FinishAddingUserRules();
  cascade.MutableMatchResult().AddMatchedProperties(set);
  cascade.MutableMatchResult().FinishAddingAuthorRulesForTreeScope(
      element->GetTreeScope());
  cascade.Apply();

  CSSPropertyRef property_ref(property_name, element->GetDocument());
  return ComputedStyleUtils::ComputedPropertyValue(property_ref.GetProperty(),
                                                   *state.Style());
}

FilterOperations StyleResolver::ComputeFilterOperations(
    Element* element,
    const Font& font,
    const CSSValue& filter_value) {
  scoped_refptr<ComputedStyle> parent = CreateComputedStyle();
  parent->SetFont(font);

  // TODO(crbug.com/1145970): Use actual StyleRecalcContext.
  StyleResolverState state(GetDocument(), *element, StyleRecalcContext(),
                           StyleRequest(parent.get()));

  state.SetStyle(ComputedStyle::Clone(*parent));

  StyleBuilder::ApplyProperty(GetCSSPropertyFilter(), state,
                              ScopedCSSValue(filter_value, &GetDocument()));

  state.LoadPendingResources();

  return state.Style()->Filter();
}

scoped_refptr<ComputedStyle> StyleResolver::StyleForInterpolations(
    Element& element,
    ActiveInterpolationsMap& interpolations) {
  // TODO(crbug.com/1145970): Use actual StyleRecalcContext.
  StyleRecalcContext style_recalc_context;
  StyleRequest style_request;
  StyleResolverState state(GetDocument(), element, style_recalc_context,
                           style_request);
  STACK_UNINITIALIZED StyleCascade cascade(state);

  ApplyBaseStyle(&element, style_recalc_context, style_request, state, cascade);
  ApplyInterpolations(state, cascade, interpolations);

  return state.TakeStyle();
}

void StyleResolver::ApplyInterpolations(
    StyleResolverState& state,
    StyleCascade& cascade,
    ActiveInterpolationsMap& interpolations) {
  cascade.AddInterpolations(&interpolations, CascadeOrigin::kAnimation);
  cascade.Apply();
}

scoped_refptr<ComputedStyle>
StyleResolver::BeforeChangeStyleForTransitionUpdate(
    Element& element,
    const ComputedStyle& base_style,
    ActiveInterpolationsMap& transition_interpolations) {
  StyleResolverState state(GetDocument(), element);
  STACK_UNINITIALIZED StyleCascade cascade(state);
  state.SetStyle(ComputedStyle::Clone(base_style));

  // Various property values may depend on the parent style. A valid parent
  // style is required, even if animating the root element, in order to
  // handle these dependencies. The root element inherits from initial
  // styles.
  if (!state.ParentStyle()) {
    if (element != GetDocument().documentElement()) {
      // Do not apply interpolations to a detached element.
      return state.TakeStyle();
    }
    state.SetParentStyle(InitialStyleForElement());
    state.SetLayoutParentStyle(state.ParentStyle());
  }

  // TODO(crbug.com/1098937): Include active CSS animations in a separate
  // interpolations map and add each map at the appropriate CascadeOrigin.
  ApplyInterpolations(state, cascade, transition_interpolations);
  return state.TakeStyle();
}

void StyleResolver::CascadeAndApplyMatchedProperties(StyleResolverState& state,
                                                     StyleCascade& cascade) {
  const MatchResult& result = cascade.GetMatchResult();

  CacheSuccess cache_success = ApplyMatchedCache(state, result);

  if (cache_success.IsFullCacheHit())
    return;

  if (cache_success.ShouldApplyInheritedOnly()) {
    cascade.Apply(CascadeFilter(CSSProperty::kInherited, false));
    if (!cache_success.IsUsableAfterApplyInheritedOnly(state.StyleRef()))
      cascade.Apply(CascadeFilter(CSSProperty::kInherited, true));
  } else {
    cascade.Apply();
  }

  MaybeAddToMatchedPropertiesCache(state, cache_success, result);

  DCHECK(!state.GetFontBuilder().FontDirty());
}

void StyleResolver::ApplyCallbackSelectors(StyleResolverState& state) {
  RuleSet* watched_selectors_rule_set =
      GetDocument().GetStyleEngine().WatchedSelectorsRuleSet();
  if (!watched_selectors_rule_set)
    return;

  // TODO(crbug.com/1145970): Use actual StyleRecalcContext.
  StyleRecalcContext style_recalc_context;
  MatchResult match_result;
  ElementRuleCollector collector(state.ElementContext(), style_recalc_context,
                                 selector_filter_, match_result, state.Style(),
                                 state.Style()->InsideLink());
  collector.SetMode(SelectorChecker::kCollectingStyleRules);
<<<<<<< HEAD
  rule_set->CompactRulesIfNeeded();
  RuleSetGroup rule_set_group(/*rule_set_group_index=*/0u);
  rule_set_group.AddRuleSet(rule_set);
  collector.CollectMatchingRules(MatchRequest(rule_set_group, scope),
                                 /*part_names=*/nullptr);
  collector.SortAndTransferMatchedRules(
      CascadeOrigin::kAuthor, /*is_vtt_embedded_style=*/false, tracker_);
  collector.SetMatchingRulesFromNoStyleSheet(false);
=======
  collector.SetIncludeEmptyRules(true);
>>>>>>> chromium

  MatchRequest match_request(watched_selectors_rule_set);
  collector.CollectMatchingRules(match_request);
  collector.SortAndTransferMatchedRules();

  if (tracker_)
    AddMatchedRulesToTracker(collector);

  StyleRuleList* rules = collector.MatchedStyleRuleList();
  if (!rules)
    return;
  for (auto rule : *rules)
    state.Style()->AddCallbackSelector(rule->SelectorList().SelectorsText());
}

// Font properties are also handled by FontStyleResolver outside the main
// thread. If you add/remove properties here, make sure they are also properly
// handled by FontStyleResolver.
void StyleResolver::ComputeFont(Element& element,
                                ComputedStyle* style,
                                const CSSPropertyValueSet& property_set) {
  static const CSSProperty* properties[7] = {
      &GetCSSPropertyFontSize(),        &GetCSSPropertyFontFamily(),
      &GetCSSPropertyFontStretch(),     &GetCSSPropertyFontStyle(),
      &GetCSSPropertyFontVariantCaps(), &GetCSSPropertyFontWeight(),
      &GetCSSPropertyLineHeight(),
  };

  // TODO(timloh): This is weird, the style is being used as its own parent
  StyleResolverState state(GetDocument(), element, StyleRecalcContext(),
                           StyleRequest(style));
  state.SetStyle(style);

  for (const CSSProperty* property : properties) {
    if (property->IDEquals(CSSPropertyID::kLineHeight))
      UpdateFont(state);
    // TODO(futhark): If we start supporting fonts on ShadowRoot.fonts in
    // addition to Document.fonts, we need to pass the correct TreeScope instead
    // of GetDocument() in the ScopedCSSValue below.
    StyleBuilder::ApplyProperty(
        *property, state,
        ScopedCSSValue(
            *property_set.GetPropertyCSSValue(property->PropertyID()),
            &GetDocument()));
  }
}

void StyleResolver::UpdateMediaType() {
  if (LocalFrameView* view = GetDocument().View()) {
    bool was_print = print_media_type_;
    print_media_type_ =
        EqualIgnoringASCIICase(view->MediaType(), media_type_names::kPrint);
    if (was_print != print_media_type_)
      matched_properties_cache_.ClearViewportDependent();
  }
}

void StyleResolver::Trace(Visitor* visitor) const {
  visitor->Trace(matched_properties_cache_);
  visitor->Trace(selector_filter_);
  visitor->Trace(document_);
  visitor->Trace(tracker_);
  visitor->Trace(media_controls_cache_key_);
  visitor->Trace(media_controls_cached_rule_set_group_);
}

bool StyleResolver::IsForcedColorsModeEnabled() const {
  return GetDocument().InForcedColorsMode();
}

bool StyleResolver::IsForcedColorsModeEnabled(
    const StyleResolverState& state) const {
  return IsForcedColorsModeEnabled() &&
         state.Style()->ForcedColorAdjust() != EForcedColorAdjust::kNone;
}

scoped_refptr<ComputedStyle> StyleResolver::CreateAnonymousStyleWithDisplay(
    const ComputedStyle& parent_style,
    EDisplay display) {
  scoped_refptr<ComputedStyle> new_style = CreateComputedStyle();
  new_style->InheritFrom(parent_style);
  new_style->SetUnicodeBidi(parent_style.GetUnicodeBidi());
  new_style->SetDisplay(display);
  return new_style;
}

scoped_refptr<ComputedStyle>
StyleResolver::CreateInheritedDisplayContentsStyleIfNeeded(
    const ComputedStyle& parent_style,
    const ComputedStyle& layout_parent_style) {
  if (parent_style.InheritedEqual(layout_parent_style))
    return nullptr;
  return CreateAnonymousStyleWithDisplay(parent_style, EDisplay::kInline);
}

#define PROPAGATE_FROM(source, getter, setter, initial) \
  PROPAGATE_VALUE(source ? source->getter() : initial, getter, setter);

#define PROPAGATE_VALUE(value, getter, setter)     \
  if ((new_viewport_style->getter()) != (value)) { \
    new_viewport_style->setter(value);             \
    changed = true;                                \
  }

namespace {

bool PropagateScrollSnapStyleToViewport(
    Document& document,
    const ComputedStyle* document_element_style,
    ComputedStyle* new_viewport_style) {
  bool changed = false;
  // We only propagate the properties related to snap container since viewport
  // defining element cannot be a snap area.
  PROPAGATE_FROM(document_element_style, GetScrollSnapType, SetScrollSnapType,
                 cc::ScrollSnapType());
  PROPAGATE_FROM(document_element_style, ScrollPaddingTop, SetScrollPaddingTop,
                 Length());
  PROPAGATE_FROM(document_element_style, ScrollPaddingRight,
                 SetScrollPaddingRight, Length());
  PROPAGATE_FROM(document_element_style, ScrollPaddingBottom,
                 SetScrollPaddingBottom, Length());
  PROPAGATE_FROM(document_element_style, ScrollPaddingLeft,
                 SetScrollPaddingLeft, Length());

  if (changed) {
    document.GetSnapCoordinator().SnapContainerDidChange(
        *document.GetLayoutView());
  }

  return changed;
}

}  // namespace

bool StyleResolver::ShouldStopBodyPropagation(const Element& body_or_html) {
  DCHECK(!body_or_html.NeedsReattachLayoutTree())
      << "This method relies on LayoutObject to be attached and up-to-date";
  DCHECK(IsA<HTMLBodyElement>(body_or_html) ||
         IsA<HTMLHtmlElement>(body_or_html));
  LayoutObject* layout_object = body_or_html.GetLayoutObject();
  if (!layout_object)
    return true;
  bool contained = layout_object->ShouldApplyAnyContainment();
  if (contained) {
    UseCounter::Count(GetDocument(), IsA<HTMLHtmlElement>(body_or_html)
                                         ? WebFeature::kHTMLRootContained
                                         : WebFeature::kHTMLBodyContained);
  }
  if (!RuntimeEnabledFeatures::CSSContainedBodyPropagationEnabled())
    return false;
  DCHECK_EQ(contained,
            layout_object->StyleRef().ShouldApplyAnyContainment(body_or_html))
      << "Applied containment must give the same result from LayoutObject and "
         "ComputedStyle";
  return contained;
}

void StyleResolver::PropagateStyleToViewport() {
  DCHECK(GetDocument().InStyleRecalc());
  Element* document_element = GetDocument().documentElement();
  const ComputedStyle* document_element_style =
      document_element && document_element->GetLayoutObject()
          ? document_element->GetComputedStyle()
          : nullptr;
  const ComputedStyle* body_style = nullptr;
  if (HTMLBodyElement* body = GetDocument().FirstBodyElement()) {
    if (!ShouldStopBodyPropagation(*document_element) &&
        !ShouldStopBodyPropagation(*body)) {
      body_style = body->GetComputedStyle();
    }
  }

  const ComputedStyle& viewport_style =
      GetDocument().GetLayoutView()->StyleRef();
  scoped_refptr<ComputedStyle> new_viewport_style =
      ComputedStyle::Clone(viewport_style);
  bool changed = false;
  bool update_scrollbar_style = false;

  // Writing mode and direction
  {
    const ComputedStyle* direction_style =
        body_style ? body_style : document_element_style;
    PROPAGATE_FROM(direction_style, GetWritingMode, SetWritingMode,
                   WritingMode::kHorizontalTb);
    PROPAGATE_FROM(direction_style, Direction, SetDirection,
                   TextDirection::kLtr);
  }

  // Background
  {
    const ComputedStyle* background_style = document_element_style;
    // http://www.w3.org/TR/css3-background/#body-background
    // <html> root element with no background steals background from its first
    // <body> child.
    // Also see LayoutBoxModelObject::BackgroundTransfersToView()
    if (body_style && !background_style->HasBackground())
      background_style = body_style;

    Color background_color = Color::kTransparent;
    FillLayer background_layers(EFillLayerType::kBackground, true);
    EImageRendering image_rendering = EImageRendering::kAuto;

    if (background_style) {
      background_color = background_style->VisitedDependentColor(
          GetCSSPropertyBackgroundColor());
      background_layers = background_style->BackgroundLayers();
      for (auto* current_layer = &background_layers; current_layer;
           current_layer = current_layer->Next()) {
        // http://www.w3.org/TR/css3-background/#root-background
        // The root element background always have painting area of the whole
        // canvas.
        current_layer->SetClip(EFillBox::kBorder);

        // The root element doesn't scroll. It always propagates its layout
        // overflow to the viewport. Positioning background against either box
        // is equivalent to positioning against the scrolled box of the
        // viewport.
        if (current_layer->Attachment() == EFillAttachment::kScroll)
          current_layer->SetAttachment(EFillAttachment::kLocal);
      }
      image_rendering = background_style->ImageRendering();
    }

    if (viewport_style.VisitedDependentColor(GetCSSPropertyBackgroundColor()) !=
            background_color ||
        viewport_style.BackgroundLayers() != background_layers ||
        viewport_style.ImageRendering() != image_rendering) {
      changed = true;
      new_viewport_style->SetBackgroundColor(StyleColor(background_color));
      new_viewport_style->AccessBackgroundLayers() = background_layers;
      new_viewport_style->SetImageRendering(image_rendering);
    }
  }

  // Overflow
  {
    const ComputedStyle* overflow_style = document_element_style;
    if (body_style &&
        document_element_style->IsOverflowVisibleAlongBothAxes()) {
      overflow_style = body_style;

      // The body element has its own scrolling box, independent from the
      // viewport.  This is a bit of a weird edge case in the CSS spec that we
      // might want to try to eliminate some day (eg. for ScrollTopLeftInterop
      // - see http://crbug.com/157855).
      if (body_style && body_style->IsScrollContainer()) {
        UseCounter::Count(GetDocument(),
                          WebFeature::kBodyScrollsInAdditionToViewport);
      }
    }

    // TODO(954423): overscroll-behavior (and most likely overflow-anchor)
    // should be propagated from the document element and not the viewport
    // defining element.
    PROPAGATE_FROM(overflow_style, OverscrollBehaviorX, SetOverscrollBehaviorX,
                   EOverscrollBehavior::kAuto);
    PROPAGATE_FROM(overflow_style, OverscrollBehaviorY, SetOverscrollBehaviorY,
                   EOverscrollBehavior::kAuto);

    // Counts any time overscroll behavior break if we change its viewport
    // propagation logic. Overscroll behavior only breaks if the body style
    // (i.e. non-document style) was propagated to the viewport and the
    // body style has a different overscroll behavior from the document one.
    // TODO(954423): Remove once propagation logic change is complete.
    if (document_element_style && overflow_style &&
        overflow_style != document_element_style) {
      EOverscrollBehavior document_x =
          document_element_style->OverscrollBehaviorX();
      EOverscrollBehavior document_y =
          document_element_style->OverscrollBehaviorY();
      EOverscrollBehavior body_x = overflow_style->OverscrollBehaviorX();
      EOverscrollBehavior body_y = overflow_style->OverscrollBehaviorY();
      // Document style is auto but body is not: fixing crbug.com/954423 might
      // break the page.
      if ((document_x == EOverscrollBehavior::kAuto && document_x != body_x) ||
          (document_y == EOverscrollBehavior::kAuto && document_y != body_y)) {
        UseCounter::Count(GetDocument(),
                          WebFeature::kOversrollBehaviorOnViewportBreaks);
      }
      // Body style is auto but document is not: currently we are showing the
      // wrong behavior, and fixing crbug.com/954423 gives the correct behavior.
      if ((body_x == EOverscrollBehavior::kAuto && document_x != body_x) ||
          (body_y == EOverscrollBehavior::kAuto && document_y != body_y)) {
        UseCounter::Count(GetDocument(),
                          WebFeature::kOverscrollBehaviorWillBeFixed);
      }
    }

    EOverflow overflow_x = EOverflow::kAuto;
    EOverflow overflow_y = EOverflow::kAuto;
    EOverflowAnchor overflow_anchor = EOverflowAnchor::kAuto;

    if (overflow_style) {
      overflow_x = overflow_style->OverflowX();
      overflow_y = overflow_style->OverflowY();
      overflow_anchor = overflow_style->OverflowAnchor();
      // Visible overflow on the viewport is meaningless, and the spec says to
      // treat it as 'auto'. The spec also says to treat 'clip' as 'hidden'.
      if (overflow_x == EOverflow::kVisible)
        overflow_x = EOverflow::kAuto;
      else if (overflow_x == EOverflow::kClip)
        overflow_x = EOverflow::kHidden;
      if (overflow_y == EOverflow::kVisible)
        overflow_y = EOverflow::kAuto;
      else if (overflow_y == EOverflow::kClip)
        overflow_y = EOverflow::kHidden;
      if (overflow_anchor == EOverflowAnchor::kVisible)
        overflow_anchor = EOverflowAnchor::kAuto;

      if (GetDocument().IsInMainFrame()) {
        using OverscrollBehaviorType = cc::OverscrollBehavior::Type;
        GetDocument().GetPage()->GetChromeClient().SetOverscrollBehavior(
            *GetDocument().GetFrame(),
            cc::OverscrollBehavior(static_cast<OverscrollBehaviorType>(
                                       overflow_style->OverscrollBehaviorX()),
                                   static_cast<OverscrollBehaviorType>(
                                       overflow_style->OverscrollBehaviorY())));
      }

      if (overflow_style->HasCustomScrollbarStyle())
        update_scrollbar_style = true;
    }

    PROPAGATE_VALUE(overflow_x, OverflowX, SetOverflowX)
    PROPAGATE_VALUE(overflow_y, OverflowY, SetOverflowY)
    PROPAGATE_VALUE(overflow_anchor, OverflowAnchor, SetOverflowAnchor);
  }

  // Misc
  {
    PROPAGATE_FROM(document_element_style, GetEffectiveTouchAction,
                   SetEffectiveTouchAction, TouchAction::kAuto);
    PROPAGATE_FROM(document_element_style, GetScrollBehavior, SetScrollBehavior,
                   mojom::blink::ScrollBehavior::kAuto);
    PROPAGATE_FROM(document_element_style, DarkColorScheme, SetDarkColorScheme,
                   false);
    PROPAGATE_FROM(document_element_style, ScrollbarGutter, SetScrollbarGutter,
                   kScrollbarGutterAuto);
    PROPAGATE_FROM(document_element_style, ForcedColorAdjust,
                   SetForcedColorAdjust, EForcedColorAdjust::kAuto);
  }

  changed |= PropagateScrollSnapStyleToViewport(
      GetDocument(), document_element_style, new_viewport_style.get());

  if (changed) {
    new_viewport_style->UpdateFontOrientation();
    FontBuilder(&GetDocument()).CreateInitialFont(*new_viewport_style);
  }
  if (changed || update_scrollbar_style)
    GetDocument().GetLayoutView()->SetStyle(new_viewport_style);
}
#undef PROPAGATE_VALUE
#undef PROPAGATE_FROM

}  // namespace blink
