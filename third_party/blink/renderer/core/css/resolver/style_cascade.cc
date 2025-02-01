// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/css/resolver/style_cascade.h"

#include "third_party/blink/renderer/core/animation/css/css_animations.h"
#include "third_party/blink/renderer/core/animation/css_interpolation_environment.h"
#include "third_party/blink/renderer/core/animation/css_interpolation_types_map.h"
#include "third_party/blink/renderer/core/animation/invalidatable_interpolation.h"
#include "third_party/blink/renderer/core/animation/property_handle.h"
#include "third_party/blink/renderer/core/animation/transition_interpolation.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/css/css_attr_type.h"
=======
#include "third_party/blink/renderer/core/css/css_custom_property_declaration.h"
>>>>>>> chromium
#include "third_party/blink/renderer/core/css/css_cyclic_variable_value.h"
#include "third_party/blink/renderer/core/css/css_font_selector.h"
#include "third_party/blink/renderer/core/css/css_invalid_variable_value.h"
#include "third_party/blink/renderer/core/css/css_pending_substitution_value.h"
#include "third_party/blink/renderer/core/css/css_unset_value.h"
#include "third_party/blink/renderer/core/css/css_variable_data.h"
#include "third_party/blink/renderer/core/css/css_variable_reference_value.h"
#include "third_party/blink/renderer/core/css/document_style_environment_variables.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_fast_paths.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_local_context.h"
#include "third_party/blink/renderer/core/css/parser/css_property_parser.h"
#include "third_party/blink/renderer/core/css/properties/css_property.h"
#include "third_party/blink/renderer/core/css/properties/css_property_ref.h"
#include "third_party/blink/renderer/core/css/property_registry.h"
#include "third_party/blink/renderer/core/css/resolver/cascade_expansion.h"
#include "third_party/blink/renderer/core/css/resolver/cascade_interpolations.h"
#include "third_party/blink/renderer/core/css/resolver/cascade_resolver.h"
#include "third_party/blink/renderer/core/css/resolver/style_builder.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver_state.h"
#include "third_party/blink/renderer/core/css/scoped_css_value.h"
#include "third_party/blink/renderer/core/css/style_engine.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/css/style_rule_function_declarations.h"
#include "third_party/blink/renderer/core/css/try_value_flips.h"
#include "third_party/blink/renderer/core/css_value_keywords.h"
=======
>>>>>>> chromium
#include "third_party/blink/renderer/core/dom/shadow_root.h"
#include "third_party/blink/renderer/core/frame/web_feature.h"
#include "third_party/blink/renderer/core/html/html_element.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style_property_shorthand.h"
#include "third_party/blink/renderer/platform/instrumentation/use_counter.h"
#include "third_party/blink/renderer/platform/wtf/math_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

namespace blink {

namespace {

AtomicString ConsumeVariableName(CSSParserTokenRange& range) {
  range.ConsumeWhitespace();
  CSSParserToken ident_token = range.ConsumeIncludingWhitespace();
  DCHECK_EQ(ident_token.GetType(), kIdentToken);
  return ident_token.Value().ToAtomicString();
}

bool ConsumeComma(CSSParserTokenRange& range) {
  if (range.Peek().GetType() == kCommaToken) {
    range.Consume();
    return true;
  }
  return false;
}

// TODO(crbug.com/1105782): It is currently unclear how to handle 'revert'
// at computed-value-time. For now we treat it as 'unset'.
const CSSValue* TreatRevertAsUnset(const CSSValue* value) {
  if (value && value->IsRevertValue())
    return cssvalue::CSSUnsetValue::Create();
  return value;
}

const CSSValue* Parse(const CSSProperty& property,
                      CSSParserTokenRange range,
                      const CSSParserContext* context) {
  return CSSPropertyParser::ParseSingleValue(property.PropertyID(), range,
                                             context);
}

const CSSValue* ValueAt(const MatchResult& result, uint32_t position) {
  size_t matched_properties_index = DecodeMatchedPropertiesIndex(position);
  size_t declaration_index = DecodeDeclarationIndex(position);
  const MatchedPropertiesVector& vector = result.GetMatchedProperties();
  const CSSPropertyValueSet* set = vector[matched_properties_index].properties;
  return &set->PropertyAt(declaration_index).Value();
}

const TreeScope& TreeScopeAt(const MatchResult& result, uint32_t position) {
  size_t matched_properties_index = DecodeMatchedPropertiesIndex(position);
  const MatchedProperties& properties =
      result.GetMatchedProperties()[matched_properties_index];
  DCHECK_EQ(properties.types_.origin, CascadeOrigin::kAuthor);
  return result.ScopeFromTreeOrder(properties.types_.tree_order);
}

PropertyHandle ToPropertyHandle(const CSSProperty& property,
                                CascadePriority priority) {
  uint32_t position = priority.GetPosition();
  CSSPropertyID id = DecodeInterpolationPropertyID(position);
  if (id == CSSPropertyID::kVariable) {
    DCHECK(IsA<CustomProperty>(property));
    return PropertyHandle(property.GetPropertyNameAtomicString());
  }
  return PropertyHandle(CSSProperty::Get(id),
                        DecodeIsPresentationAttribute(position));
}

// https://drafts.csswg.org/css-cascade-4/#default
CascadeOrigin TargetOriginForRevert(CascadeOrigin origin) {
  switch (origin) {
    case CascadeOrigin::kNone:
    case CascadeOrigin::kTransition:
      NOTREACHED();
      return CascadeOrigin::kNone;
    case CascadeOrigin::kUserAgent:
      return CascadeOrigin::kNone;
    case CascadeOrigin::kUser:
      return CascadeOrigin::kUserAgent;
    case CascadeOrigin::kAuthor:
    case CascadeOrigin::kAnimation:
      return CascadeOrigin::kUser;
  }
}

CSSPropertyID UnvisitedID(CSSPropertyID id) {
  if (id == CSSPropertyID::kVariable)
    return id;
  const CSSProperty& property = CSSProperty::Get(id);
  if (!property.IsVisited())
    return id;
  return property.GetUnvisitedProperty()->PropertyID();
}

bool IsRevert(const CSSValue& value) {
  // TODO(andruud): Don't transport CSS-wide keywords in
  // CustomPropertyDeclaration.
  return value.IsRevertValue() ||
         (value.IsCustomPropertyDeclaration() &&
          To<CSSCustomPropertyDeclaration>(value).IsRevert());
}

bool IsInterpolation(CascadePriority priority) {
  switch (priority.GetOrigin()) {
    case CascadeOrigin::kAnimation:
    case CascadeOrigin::kTransition:
      return true;
    case CascadeOrigin::kNone:
    case CascadeOrigin::kUserAgent:
    case CascadeOrigin::kUser:
    case CascadeOrigin::kAuthor:
      return false;
  }
}

<<<<<<< HEAD
const CSSValue* FindOrNull(
    const HeapHashMap<String, Member<const CSSValue>>& map,
    const String& key) {
  auto it = map.find(key);
  if (it == map.end()) {
    return nullptr;
  }
  return it->value.Get();
}

=======
>>>>>>> chromium
}  // namespace

MatchResult& StyleCascade::MutableMatchResult() {
  DCHECK(!generation_) << "Apply has already been called";
  needs_match_result_analyze_ = true;
  return match_result_;
}

void StyleCascade::AddInterpolations(const ActiveInterpolationsMap* map,
                                     CascadeOrigin origin) {
  DCHECK(map);
  needs_interpolations_analyze_ = true;
  interpolations_.Add(map, origin);
}

void StyleCascade::Apply(CascadeFilter filter) {
  AnalyzeIfNeeded();

  CascadeResolver resolver(filter, ++generation_);

  ApplyCascadeAffecting(resolver);

  // Affects the computed value of 'color', hence needs to happen before
  // high-priority properties.
  LookupAndApply(GetCSSPropertyColorScheme(), resolver);

  // Affects the computed value of 'font-size', hence needs to happen before
  // high-priority properties.
  LookupAndApply(GetCSSPropertyMathDepth(), resolver);

  ApplyWebkitBorderImage(resolver);

  // -webkit-mask-image needs to be applied before -webkit-mask-composite,
  // otherwise -webkit-mask-composite has no effect.
  LookupAndApply(GetCSSPropertyWebkitMaskImage(), resolver);

  ApplyHighPriority(resolver);

  ApplyMatchResult(resolver);
  ApplyInterpolations(resolver);

<<<<<<< HEAD
  // These three flags are only used if HasAppearance() is set
  // (they are used for knowing whether appearance: auto is to be overridden),
  // but we compute them nevertheless, to avoid suddenly having to compute them
  // after-the-fact if inline style is updated incrementally.
  if (resolver.AuthorFlags() & CSSProperty::kBackground) {
    state_.StyleBuilder().SetHasAuthorBackground();
  }
  if (resolver.AuthorFlags() & CSSProperty::kBorder) {
    state_.StyleBuilder().SetHasAuthorBorder();
  }
  if (resolver.AuthorFlags() & CSSProperty::kBorderRadius) {
    state_.StyleBuilder().SetHasAuthorBorderRadius();
  }

  if ((state_.InsideLink() != EInsideLink::kInsideVisitedLink &&
       (resolver.AuthorFlags() & CSSProperty::kHighlightColors)) ||
      (state_.InsideLink() == EInsideLink::kInsideVisitedLink &&
       (resolver.AuthorFlags() & CSSProperty::kVisitedHighlightColors))) {
    state_.StyleBuilder().SetHasAuthorHighlightColors();
  }

  if (resolver.Flags() & CSSProperty::kAnimation) {
    state_.StyleBuilder().SetCanAffectAnimations();
  }
  if (resolver.RejectedFlags() & CSSProperty::kLegacyOverlapping) {
    state_.SetRejectedLegacyOverlapping();
  }

  // TOOD(crbug.com/1334570):
  //
  // Count applied H1 font-size from html.css UA stylesheet where H1 is inside
  // a sectioning element matching selectors like:
  //
  // :-webkit-any(article,aside,nav,section) h1 { ... }
  //
  if (state_.GetElement().HasTagName(html_names::kH1Tag)) {
    if (CascadePriority* priority =
            map_.Find(GetCSSPropertyFontSize().GetCSSPropertyName())) {
      if (priority->GetOrigin() != CascadeOrigin::kUserAgent) {
        return;
      }
      const CSSValue* value = ValueAt(match_result_, priority->GetPosition());
      if (const auto* numeric = DynamicTo<CSSNumericLiteralValue>(value)) {
        DCHECK(numeric->GetType() == CSSNumericLiteralValue::UnitType::kEms);
        if (numeric->DoubleValue() != 2.0) {
          CountUse(WebFeature::kH1UserAgentFontSizeInSectionApplied);
        }
      }
    }
=======
  if (state_.Style()->HasAppearance()) {
    if (resolver.AuthorFlags() & CSSProperty::kBackground)
      state_.Style()->SetHasAuthorBackground();
    if (resolver.AuthorFlags() & CSSProperty::kBorder)
      state_.Style()->SetHasAuthorBorder();
>>>>>>> chromium
  }

  ApplyUnresolvedEnv();
}

std::unique_ptr<CSSBitset> StyleCascade::GetImportantSet() {
  AnalyzeIfNeeded();
  if (!map_.HasImportant())
    return nullptr;
  auto set = std::make_unique<CSSBitset>();
  for (CSSPropertyID id : map_.NativeBitset()) {
    // We use the unvisited ID because visited/unvisited colors are currently
    // interpolated together.
    // TODO(crbug.com/1062217): Interpolate visited colors separately
    set->Or(UnvisitedID(id), map_.At(CSSPropertyName(id)).IsImportant());
  }
  return set;
}

void StyleCascade::Reset() {
  map_.Reset();
  match_result_.Reset();
  interpolations_.Reset();
  generation_ = 0;
  depends_on_cascade_affecting_property_ = false;
}

const CSSValue* StyleCascade::Resolve(const CSSPropertyName& name,
                                      const CSSValue& value,
                                      CascadeOrigin origin,
                                      CascadeResolver& resolver) {
  CSSPropertyRef ref(name, state_.GetDocument());

  const CSSValue* resolved =
      Resolve(ResolveSurrogate(ref.GetProperty()), value, origin, resolver);

  DCHECK(resolved);

  // TODO(crbug.com/1185745): Cycles in animations get special handling by our
  // implementation. This is not per spec, but the correct behavior is not
  // defined at the moment.
  if (resolved->IsCyclicVariableValue())
    return nullptr;

  // TODO(crbug.com/1185745): We should probably not return 'unset' for
  // properties where CustomProperty::SupportsGuaranteedInvalid return true.
  if (resolved->IsInvalidVariableValue())
    return cssvalue::CSSUnsetValue::Create();

  return resolved;
}

HeapHashMap<CSSPropertyName, Member<const CSSValue>>
StyleCascade::GetCascadedValues() const {
  DCHECK(!needs_match_result_analyze_);
  DCHECK(!needs_interpolations_analyze_);
  DCHECK_GE(generation_, 0);

  HeapHashMap<CSSPropertyName, Member<const CSSValue>> result;

  for (CSSPropertyID id : map_.NativeBitset()) {
    CSSPropertyName name(id);
    CascadePriority priority = map_.At(name);
    DCHECK(priority.HasOrigin());
    if (IsInterpolation(priority))
      continue;
    const CSSValue* cascaded = ValueAt(match_result_, priority.GetPosition());
    DCHECK(cascaded);
    result.Set(name, cascaded);
  }

  for (const auto& entry : map_.GetCustomMap()) {
    CascadePriority priority = entry.value;
    DCHECK(priority.HasOrigin());
    if (IsInterpolation(priority))
      continue;
    const CSSValue* cascaded = ValueAt(match_result_, priority.GetPosition());
    DCHECK(cascaded);
    result.Set(entry.key, cascaded);
  }

  return result;
}

void StyleCascade::AnalyzeIfNeeded() {
  if (needs_match_result_analyze_) {
    AnalyzeMatchResult();
    needs_match_result_analyze_ = false;
  }
  if (needs_interpolations_analyze_) {
    AnalyzeInterpolations();
    needs_interpolations_analyze_ = false;
  }
}

void StyleCascade::AnalyzeMatchResult() {
  for (auto e : match_result_.Expansions(GetDocument(), CascadeFilter())) {
    for (; !e.AtEnd(); e.Next()) {
      const CSSProperty& property = ResolveSurrogate(e.Property());
      map_.Add(property.GetCSSPropertyName(), e.Priority());
    }
  }
}

void StyleCascade::AnalyzeInterpolations() {
  const auto& entries = interpolations_.GetEntries();
  for (size_t i = 0; i < entries.size(); ++i) {
    for (const auto& active_interpolation : *entries[i].map) {
      auto name = active_interpolation.key.GetCSSPropertyName();
      uint32_t position = EncodeInterpolationPosition(
          name.Id(), i, active_interpolation.key.IsPresentationAttribute());
      CascadePriority priority(entries[i].origin, false, 0, position);

      CSSPropertyRef ref(name, GetDocument());
      DCHECK(ref.IsValid());
      const CSSProperty& property = ResolveSurrogate(ref.GetProperty());

      map_.Add(property.GetCSSPropertyName(), priority);

      // Since an interpolation for an unvisited property also causes an
      // interpolation of the visited property, add the visited property to
      // the map as well.
      // TODO(crbug.com/1062217): Interpolate visited colors separately
      if (const CSSProperty* visited = property.GetVisitedProperty())
        map_.Add(visited->GetCSSPropertyName(), priority);
    }
  }
}

void StyleCascade::Reanalyze() {
  map_.Reset();
  generation_ = 0;
  depends_on_cascade_affecting_property_ = false;

  needs_match_result_analyze_ = true;
  needs_interpolations_analyze_ = true;
  AnalyzeIfNeeded();
}

void StyleCascade::ApplyCascadeAffecting(CascadeResolver& resolver) {
  // During the initial call to Analyze, we speculatively assume that the
  // direction/writing-mode inherited from the parent will be the final
  // direction/writing-mode. If either property ends up with another value,
  // our assumption was incorrect, and we have to Reanalyze with the correct
  // values on ComputedStyle.
  auto direction = state_.Style()->Direction();
  auto writing_mode = state_.Style()->GetWritingMode();

  LookupAndApply(GetCSSPropertyDirection(), resolver);
  LookupAndApply(GetCSSPropertyWritingMode(), resolver);

  if (depends_on_cascade_affecting_property_) {
    if (direction != state_.Style()->Direction() ||
        writing_mode != state_.Style()->GetWritingMode()) {
      Reanalyze();
    }
  }
}

void StyleCascade::ApplyHighPriority(CascadeResolver& resolver) {
  uint64_t bits = map_.HighPriorityBits();

  if (bits) {
    int first = static_cast<int>(kFirstHighPriorityCSSProperty);
    int last = static_cast<int>(kLastHighPriorityCSSProperty);
    for (int i = first; i <= last; ++i) {
      if (bits & (static_cast<uint64_t>(1) << i))
        LookupAndApply(CSSProperty::Get(ConvertToCSSPropertyID(i)), resolver);
    }
  }

  state_.GetFontBuilder().CreateFont(state_.StyleRef(), state_.ParentStyle());
  state_.SetConversionFontSizes(CSSToLengthConversionData::FontSizes(
      state_.Style(), state_.RootElementStyle()));
  state_.SetConversionZoom(state_.Style()->EffectiveZoom());
}

void StyleCascade::ApplyWebkitBorderImage(CascadeResolver& resolver) {
  const CascadePriority* priority =
      map_.Find(CSSPropertyName(CSSPropertyID::kWebkitBorderImage));
  if (!priority)
    return;

  // -webkit-border-image is a surrogate for the border-image (shorthand).
  // By applying -webkit-border-image first, we avoid having to "partially"
  // apply -webkit-border-image depending on the border-image-* longhands that
  // have already been applied.
  // See also crbug.com/1056600
  LookupAndApply(GetCSSPropertyWebkitBorderImage(), resolver);

  const auto& shorthand = borderImageShorthand();
  const CSSProperty** longhands = shorthand.properties();
  for (unsigned i = 0; i < shorthand.length(); ++i) {
    const CSSProperty& longhand = *longhands[i];
    if (CascadePriority* p = map_.Find(longhand.GetCSSPropertyName())) {
      // If -webkit-border-image has higher priority than a border-image
      // longhand, we skip applying that longhand.
      if (*p < *priority)
        *p = CascadePriority(*p, resolver.generation_);
    }
  }
}

void StyleCascade::ApplyMatchResult(CascadeResolver& resolver) {
  for (auto e : match_result_.Expansions(GetDocument(), resolver.filter_)) {
    for (; !e.AtEnd(); e.Next()) {
      auto priority = CascadePriority(e.Priority(), resolver.generation_);
      const CSSProperty& property = ResolveSurrogate(e.Property());
      CascadePriority* p = map_.Find(property.GetCSSPropertyName());
      if (!p || *p >= priority)
        continue;
      *p = priority;
      CascadeOrigin origin = priority.GetOrigin();
      const CSSValue* value = Resolve(property, e.Value(), origin, resolver);
      // TODO(futhark): Use a user scope TreeScope to support tree-scoped names
      // for animations in user stylesheets.
      const TreeScope* tree_scope =
          origin == CascadeOrigin::kAuthor
              ? &match_result_.ScopeFromTreeOrder(e.TreeOrder())
              : nullptr;
      StyleBuilder::ApplyProperty(property, state_,
                                  ScopedCSSValue(*value, tree_scope));
    }
  }
}

void StyleCascade::ApplyInterpolations(CascadeResolver& resolver) {
  const auto& entries = interpolations_.GetEntries();
  for (size_t i = 0; i < entries.size(); ++i) {
    const auto& entry = entries[i];
    ApplyInterpolationMap(*entry.map, entry.origin, i, resolver);
  }
}

void StyleCascade::ApplyInterpolationMap(const ActiveInterpolationsMap& map,
                                         CascadeOrigin origin,
                                         size_t index,
                                         CascadeResolver& resolver) {
  for (const auto& entry : map) {
    auto name = entry.key.GetCSSPropertyName();
    uint32_t position = EncodeInterpolationPosition(
        name.Id(), index, entry.key.IsPresentationAttribute());
    CascadePriority priority(origin, false, 0, position);
    priority = CascadePriority(priority, resolver.generation_);

    CSSPropertyRef ref(name, GetDocument());
    if (resolver.filter_.Rejects(ref.GetProperty()))
      continue;

    const CSSProperty& property = ResolveSurrogate(ref.GetProperty());

    CascadePriority* p = map_.Find(property.GetCSSPropertyName());
    if (!p || *p >= priority) {
      continue;
    }
    *p = priority;

    ApplyInterpolation(property, priority, *entry.value, resolver);
  }
}

void StyleCascade::ApplyInterpolation(
    const CSSProperty& property,
    CascadePriority priority,
    const ActiveInterpolations& interpolations,
    CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());

  const Interpolation& interpolation = *interpolations.front();
  if (IsA<InvalidatableInterpolation>(interpolation)) {
    CSSInterpolationTypesMap map(state_.GetDocument().GetPropertyRegistry(),
                                 state_.GetDocument());
    CSSInterpolationEnvironment environment(map, state_, this, &resolver);
    InvalidatableInterpolation::ApplyStack(interpolations, environment);
  } else {
    To<TransitionInterpolation>(interpolation).Apply(state_);
  }

  // Applying a color property interpolation will also unconditionally apply
  // the -internal-visited- counterpart (see CSSColorInterpolationType::
  // ApplyStandardPropertyValue). To make sure !important rules in :visited
  // selectors win over animations, we re-apply the -internal-visited property
  // if its priority is higher.
  //
  // TODO(crbug.com/1062217): Interpolate visited colors separately
  if (const CSSProperty* visited = property.GetVisitedProperty()) {
    CascadePriority* visited_priority =
        map_.Find(visited->GetCSSPropertyName());
    if (visited_priority && priority < *visited_priority) {
      DCHECK(visited_priority->IsImportant());
      // Resetting generation to zero makes it possible to apply the
      // visited property again.
      *visited_priority = CascadePriority(*visited_priority, 0);
      LookupAndApply(*visited, resolver);
    }
  }
}

void StyleCascade::LookupAndApply(const CSSPropertyName& name,
                                  CascadeResolver& resolver) {
  CSSPropertyRef ref(name, state_.GetDocument());
  DCHECK(ref.IsValid());
  LookupAndApply(ref.GetProperty(), resolver);
}

void StyleCascade::LookupAndApply(const CSSProperty& property,
                                  CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());

  CSSPropertyName name = property.GetCSSPropertyName();
  DCHECK(!resolver.IsLocked(property));

  CascadePriority* p = map_.Find(name);
  if (!p)
    return;
  CascadePriority priority(*p, resolver.generation_);
  if (*p >= priority)
    return;
  *p = priority;

  if (resolver.filter_.Rejects(property))
    return;

  LookupAndApplyValue(property, priority, resolver);
}

void StyleCascade::LookupAndApplyValue(const CSSProperty& property,
                                       CascadePriority priority,
                                       CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());

  if (priority.GetOrigin() < CascadeOrigin::kAnimation)
    LookupAndApplyDeclaration(property, priority, resolver);
  else if (priority.GetOrigin() >= CascadeOrigin::kAnimation)
    LookupAndApplyInterpolation(property, priority, resolver);
}

void StyleCascade::LookupAndApplyDeclaration(const CSSProperty& property,
                                             CascadePriority priority,
                                             CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());
  DCHECK(priority.GetOrigin() < CascadeOrigin::kAnimation);
  const CSSValue* value = ValueAt(match_result_, priority.GetPosition());
  DCHECK(value);
  CascadeOrigin origin = priority.GetOrigin();
  value = Resolve(property, *value, origin, resolver);
  DCHECK(!value->IsVariableReferenceValue());
  DCHECK(!value->IsPendingSubstitutionValue());
  const TreeScope* tree_scope{nullptr};
  if (origin == CascadeOrigin::kAuthor)
    tree_scope = &TreeScopeAt(match_result_, priority.GetPosition());
  StyleBuilder::ApplyProperty(property, state_,
                              ScopedCSSValue(*value, tree_scope));
}

void StyleCascade::LookupAndApplyInterpolation(const CSSProperty& property,
                                               CascadePriority priority,
                                               CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());

  // Interpolations for -internal-visited properties are applied via the
  // interpolation for the main (unvisited) property, so we don't need to
  // apply it twice.
  // TODO(crbug.com/1062217): Interpolate visited colors separately
  if (property.IsVisited())
    return;
  DCHECK(priority.GetOrigin() >= CascadeOrigin::kAnimation);
  size_t index = DecodeInterpolationIndex(priority.GetPosition());
  DCHECK_LE(index, interpolations_.GetEntries().size());
  const ActiveInterpolationsMap& map = *interpolations_.GetEntries()[index].map;
  PropertyHandle handle = ToPropertyHandle(property, priority);
  const auto& entry = map.find(handle);
  DCHECK_NE(entry, map.end());
  ApplyInterpolation(property, priority, *entry->value, resolver);
}

bool StyleCascade::IsRootElement() const {
  return &state_.GetElement() == state_.GetDocument().documentElement();
}

StyleCascade::TokenSequence::TokenSequence(const CSSVariableData* data)
    : backing_strings_(data->BackingStrings()),
      is_animation_tainted_(data->IsAnimationTainted()),
      has_font_units_(data->HasFontUnits()),
      has_root_font_units_(data->HasRootFontUnits()),
<<<<<<< HEAD
      has_line_height_units_(data->HasLineHeightUnits()) {}

bool StyleCascade::TokenSequence::AppendFallback(const TokenSequence& sequence,
                                                 bool is_attr_tainted,
                                                 wtf_size_t byte_limit) {
  // https://drafts.csswg.org/css-variables/#long-variables
  if (original_text_.length() + sequence.original_text_.length() > byte_limit) {
    return false;
  }
  size_t start = original_text_.length();

  StringView other_text = sequence.original_text_;
  other_text =
      CSSVariableParser::StripTrailingWhitespaceAndComments(other_text);

  CSSTokenizer tokenizer(other_text);
  CSSParserToken first_token = tokenizer.TokenizeSingleWithComments();

  if (NeedsInsertedComment(last_token_, first_token)) {
    original_text_.Append("/**/");
  }
  original_text_.Append(other_text);
  last_token_ = last_non_whitespace_token_ =
      sequence.last_non_whitespace_token_;
=======
      base_url_(data->BaseURL()),
      charset_(data->Charset()) {}
>>>>>>> chromium

void StyleCascade::TokenSequence::Append(const TokenSequence& sequence) {
  tokens_.AppendVector(sequence.tokens_);
  backing_strings_.AppendVector(sequence.backing_strings_);
  is_animation_tainted_ |= sequence.is_animation_tainted_;
  has_font_units_ |= sequence.has_font_units_;
  has_root_font_units_ |= sequence.has_root_font_units_;
<<<<<<< HEAD
  has_line_height_units_ |= sequence.has_line_height_units_;

  size_t end = original_text_.length();
  if (is_attr_tainted) {
    attr_taint_ranges_.emplace_back(std::make_pair(start, end));
  }
  return true;
}

static bool IsNonWhitespaceToken(const CSSParserToken& token) {
  return token.GetType() != kWhitespaceToken &&
         token.GetType() != kCommentToken;
}

bool StyleCascade::TokenSequence::Append(StringView str,
                                         bool is_attr_tainted,
                                         wtf_size_t byte_limit) {
  // https://drafts.csswg.org/css-variables/#long-variables
  if (original_text_.length() + str.length() > byte_limit) {
    return false;
  }
  size_t start = original_text_.length();
  CSSTokenizer tokenizer(str);
  const CSSParserToken first_token = tokenizer.TokenizeSingleWithComments();
  if (first_token.GetType() != kEOFToken) {
    CSSVariableData::ExtractFeatures(first_token, has_font_units_,
                                     has_root_font_units_,
                                     has_line_height_units_);
    if (NeedsInsertedComment(last_token_, first_token)) {
      original_text_.Append("/**/");
    }
    last_token_ = first_token.CopyWithoutValue();
    if (IsNonWhitespaceToken(first_token)) {
      last_non_whitespace_token_ = first_token;
    }
    while (true) {
      const CSSParserToken token = tokenizer.TokenizeSingleWithComments();
      if (token.GetType() == kEOFToken) {
        break;
      } else {
        CSSVariableData::ExtractFeatures(token, has_font_units_,
                                         has_root_font_units_,
                                         has_line_height_units_);
        last_token_ = token.CopyWithoutValue();
        if (IsNonWhitespaceToken(token)) {
          last_non_whitespace_token_ = token;
        }
      }
    }
  }
  original_text_.Append(str);

  size_t end = original_text_.length();
  if (is_attr_tainted) {
    attr_taint_ranges_.emplace_back(std::make_pair(start, end));
  }
  return true;
}

bool StyleCascade::TokenSequence::Append(const CSSValue* value,
                                         bool is_attr_tainted,
                                         wtf_size_t byte_limit) {
  return Append(value->CssText(), is_attr_tainted, byte_limit);
}

bool StyleCascade::TokenSequence::Append(CSSVariableData* data,
                                         bool is_attr_tainted,
                                         wtf_size_t byte_limit) {
  if (!Append(data->OriginalText(), is_attr_tainted, byte_limit)) {
    return false;
  }
=======
}

void StyleCascade::TokenSequence::Append(const CSSVariableData* data) {
  tokens_.AppendVector(data->Tokens());
  backing_strings_.AppendVector(data->BackingStrings());
>>>>>>> chromium
  is_animation_tainted_ |= data->IsAnimationTainted();
  has_font_units_ |= data->HasFontUnits();
  has_root_font_units_ |= data->HasRootFontUnits();
}

<<<<<<< HEAD
void StyleCascade::TokenSequence::Append(const CSSParserToken& token,
                                         bool is_attr_tainted,
                                         StringView original_text) {
  CSSVariableData::ExtractFeatures(token, has_font_units_, has_root_font_units_,
                                   has_line_height_units_);
  size_t start = original_text_.length();
  if (NeedsInsertedComment(last_token_, token)) {
    original_text_.Append("/**/");
  }
  last_token_ = token.CopyWithoutValue();
  if (IsNonWhitespaceToken(token)) {
    last_non_whitespace_token_ = token;
  }
  original_text_.Append(original_text);
  size_t end = original_text_.length();
  if (is_attr_tainted) {
    attr_taint_ranges_.emplace_back(std::make_pair(start, end));
  }
}

CSSVariableData* StyleCascade::TokenSequence::BuildVariableData() {
  return CSSVariableData::Create(
      original_text_, is_animation_tainted_, !attr_taint_ranges_.empty(),
      /*needs_variable_resolution=*/false, has_font_units_,
      has_root_font_units_, has_line_height_units_);
=======
void StyleCascade::TokenSequence::Append(const CSSParserToken& token) {
  tokens_.push_back(token);
}

scoped_refptr<CSSVariableData>
StyleCascade::TokenSequence::BuildVariableData() {
  return CSSVariableData::CreateResolved(
      std::move(tokens_), std::move(backing_strings_), is_animation_tainted_,
      has_font_units_, has_root_font_units_, base_url_, charset_);
>>>>>>> chromium
}

const CSSValue* StyleCascade::Resolve(const CSSProperty& property,
                                      const CSSValue& value,
                                      CascadeOrigin& origin,
                                      CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());
  if (IsRevert(value))
    return ResolveRevert(property, value, origin, resolver);
  resolver.CollectAuthorFlags(property, origin);
  if (const auto* v = DynamicTo<CSSCustomPropertyDeclaration>(value))
    return ResolveCustomProperty(property, *v, resolver);
  if (const auto* v = DynamicTo<CSSVariableReferenceValue>(value))
    return ResolveVariableReference(property, *v, resolver);
  if (const auto* v = DynamicTo<cssvalue::CSSPendingSubstitutionValue>(value))
    return ResolvePendingSubstitution(property, *v, resolver);
  return &value;
}

const CSSValue* StyleCascade::ResolveCustomProperty(
    const CSSProperty& property,
    const CSSCustomPropertyDeclaration& decl,
    CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());

  // TODO(andruud): Don't transport css-wide keywords in this value.
  if (!decl.Value())
    return &decl;

  DCHECK(!resolver.IsLocked(property));
  CascadeResolver::AutoLock lock(property, resolver);

  scoped_refptr<CSSVariableData> data = decl.Value();

  if (data->NeedsVariableResolution())
    data = ResolveVariableData(data.get(), resolver);

  if (HasFontSizeDependency(To<CustomProperty>(property), data.get()))
    resolver.DetectCycle(GetCSSPropertyFontSize());

  state_.Style()->SetHasVariableDeclaration();

  if (resolver.InCycle())
    return CSSCyclicVariableValue::Create();

  if (!data)
    return CSSInvalidVariableValue::Create();

  if (data == decl.Value())
    return &decl;

  return MakeGarbageCollected<CSSCustomPropertyDeclaration>(decl.GetName(),
                                                            data);
}

const CSSValue* StyleCascade::ResolveVariableReference(
    const CSSProperty& property,
    const CSSVariableReferenceValue& value,
    CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());
  DCHECK(!resolver.IsLocked(property));
  CascadeResolver::AutoLock lock(property, resolver);

  const CSSVariableData* data = value.VariableDataValue();
  const CSSParserContext* context = GetParserContext(value);

  MarkHasVariableReference(property);

  DCHECK(data);
  DCHECK(context);

  TokenSequence sequence;

<<<<<<< HEAD
  CSSParserTokenStream stream(data->OriginalText());
  if (ResolveTokensInto(stream, resolver, *context,
                        /* function_context */ nullptr,
                        /* stop_type */ kEOFToken, sequence)) {
    // TODO(sesse): It would be nice if we had some way of combining
    // ResolveTokensInto() and the re-tokenization. This is basically
    // what we pay by using the streaming parser everywhere; we tokenize
    // everything involving variable references twice.
    CSSParserTokenStream stream2(sequence.OriginalText(),
                                 sequence.GetAttrTaintedRanges());
    if (const auto* parsed = Parse(property, stream2, context)) {
      return parsed;
    }
=======
  if (ResolveTokensInto(data->Tokens(), resolver, sequence)) {
    if (const auto* parsed = Parse(property, sequence.TokenRange(), context))
      return TreatRevertAsUnset(parsed);
>>>>>>> chromium
  }

  return cssvalue::CSSUnsetValue::Create();
}

const CSSValue* StyleCascade::ResolvePendingSubstitution(
    const CSSProperty& property,
    const cssvalue::CSSPendingSubstitutionValue& value,
    CascadeResolver& resolver) {
  DCHECK(!property.IsSurrogate());
  DCHECK(!resolver.IsLocked(property));
  CascadeResolver::AutoLock lock(property, resolver);

  CascadePriority priority = map_.At(property.GetCSSPropertyName());
  DCHECK_NE(property.PropertyID(), CSSPropertyID::kVariable);
  DCHECK_NE(priority.GetOrigin(), CascadeOrigin::kNone);

  MarkHasVariableReference(property);

  // If the previous call to ResolvePendingSubstitution parsed 'value', then
  // we don't need to do it again.
  bool is_cached = resolver.shorthand_cache_.value == &value;

  if (!is_cached) {
    CSSVariableReferenceValue* shorthand_value = value.ShorthandValue();
    const auto* shorthand_data = shorthand_value->VariableDataValue();
    CSSPropertyID shorthand_property_id = value.ShorthandPropertyId();

    TokenSequence sequence;

<<<<<<< HEAD
    CSSParserTokenStream stream(shorthand_data->OriginalText());
    if (!ResolveTokensInto(stream, resolver,
                           *GetParserContext(*shorthand_value),
                           /* function_context */ nullptr,
                           /* stop_type */ kEOFToken, sequence)) {
=======
    if (!ResolveTokensInto(shorthand_data->Tokens(), resolver, sequence))
>>>>>>> chromium
      return cssvalue::CSSUnsetValue::Create();

    HeapVector<CSSPropertyValue, 256> parsed_properties;
    const bool important = false;

    if (!CSSPropertyParser::ParseValue(
            shorthand_property_id, important, sequence.TokenRange(),
            shorthand_value->ParserContext(), parsed_properties,
            StyleRule::RuleType::kStyle)) {
      return cssvalue::CSSUnsetValue::Create();
    }

    resolver.shorthand_cache_.value = &value;
    resolver.shorthand_cache_.parsed_properties = std::move(parsed_properties);
  }

  const auto& parsed_properties = resolver.shorthand_cache_.parsed_properties;

  // For -internal-visited-properties with CSSPendingSubstitutionValues,
  // the inner 'shorthand_property_id' will expand to a set of longhands
  // containing the unvisited equivalent. Hence, when parsing the
  // CSSPendingSubstitutionValue, we look for the unvisited property in
  // parsed_properties.
  const CSSProperty* unvisited_property =
      property.IsVisited() ? property.GetUnvisitedProperty() : &property;

  unsigned parsed_properties_count = parsed_properties.size();
  for (unsigned i = 0; i < parsed_properties_count; ++i) {
    const CSSProperty& longhand =
        CSSProperty::Get(parsed_properties[i].PropertyID());

    // When using var() in a css-logical shorthand (e.g. margin-inline),
    // the longhands here will also be logical.
<<<<<<< HEAD
    if (unvisited_property == &ResolveSurrogate(longhand)) {
      return &parsed_properties[i].Value();
    }
=======
    if (unvisited_property == &ResolveSurrogate(longhand))
      return TreatRevertAsUnset(parsed);
>>>>>>> chromium
  }

  NOTREACHED();
  return cssvalue::CSSUnsetValue::Create();
}

const CSSValue* StyleCascade::ResolveRevert(const CSSProperty& property,
                                            const CSSValue& value,
                                            CascadeOrigin& origin,
                                            CascadeResolver& resolver) {
  MaybeUseCountRevert(value);

  CascadeOrigin target_origin = TargetOriginForRevert(origin);

  switch (target_origin) {
    case CascadeOrigin::kTransition:
    case CascadeOrigin::kNone:
      return cssvalue::CSSUnsetValue::Create();
    case CascadeOrigin::kUserAgent:
    case CascadeOrigin::kUser:
    case CascadeOrigin::kAuthor:
    case CascadeOrigin::kAnimation: {
      CascadePriority* p =
          map_.Find(property.GetCSSPropertyName(), target_origin);
      if (!p) {
        origin = CascadeOrigin::kNone;
        return cssvalue::CSSUnsetValue::Create();
      }
      origin = p->GetOrigin();
      return Resolve(property, *ValueAt(match_result_, p->GetPosition()),
                     origin, resolver);
    }
  }
}

scoped_refptr<CSSVariableData> StyleCascade::ResolveVariableData(
    CSSVariableData* data,
    CascadeResolver& resolver) {
  DCHECK(data && data->NeedsVariableResolution());

  TokenSequence sequence(data);

<<<<<<< HEAD
  CSSParserTokenStream stream(data->OriginalText());
  if (!ResolveTokensInto(stream, resolver, context,
                         /* function_context */ nullptr,
                         /* stop_type */ kEOFToken, sequence)) {
=======
  if (!ResolveTokensInto(data->Tokens(), resolver, sequence))
>>>>>>> chromium
    return nullptr;

  return sequence.BuildVariableData();
}

bool StyleCascade::ResolveTokensInto(CSSParserTokenRange range,
                                     CascadeResolver& resolver,
<<<<<<< HEAD
                                     const CSSParserContext& context,
                                     const FunctionContext* function_context,
                                     CSSParserTokenType stop_type,
                                     TokenSequence& out) {
  bool success = true;
  int nesting_level = 0;
  while (true) {
    const CSSParserToken& token = stream.Peek();
    if (token.IsEOF()) {
      break;
    } else if (token.GetType() == stop_type && nesting_level == 0) {
      break;
    } else if (token.FunctionId() == CSSValueID::kVar) {
      CSSParserTokenStream::BlockGuard guard(stream);
      success &=
          ResolveVarInto(stream, resolver, context, function_context, out);
    } else if (token.FunctionId() == CSSValueID::kEnv) {
      CSSParserTokenStream::BlockGuard guard(stream);
      success &= ResolveEnvInto(stream, resolver, context, out);
    } else if (token.FunctionId() == CSSValueID::kAttr &&
               RuntimeEnabledFeatures::CSSAdvancedAttrFunctionEnabled()) {
      CSSParserTokenStream::BlockGuard guard(stream);
      state_.StyleBuilder().SetHasAttrFunction();
      success &= ResolveAttrInto(stream, resolver, context, out);
    } else if (token.FunctionId() ==
               CSSValueID::kInternalAutoBase) {
      CSSParserTokenStream::BlockGuard guard(stream);
      success &=
          ResolveAutoBaseInto(stream, resolver, context, out);
    } else if (token.GetType() == kFunctionToken &&
               CSSVariableParser::IsValidVariableName(token.Value()) &&
               RuntimeEnabledFeatures::CSSFunctionsEnabled()) {
      // User-defined CSS function.
      CSSParserTokenStream::BlockGuard guard(stream);
      success &= ResolveFunctionInto(token.Value(), stream, resolver, context,
                                     function_context, out);
    } else {
      if (token.GetBlockType() == CSSParserToken::kBlockStart) {
        ++nesting_level;
      } else if (token.GetBlockType() == CSSParserToken::kBlockEnd) {
        if (nesting_level == 0) {
          // Attempting to go outside our block.
          break;
        }
        --nesting_level;
      }
      wtf_size_t start = stream.Offset();
      stream.ConsumeRaw();
      wtf_size_t end = stream.Offset();

      // NOTE: This will include any comment tokens that ConsumeRaw()
      // skipped over; i.e., any comment will be attributed to the
      // token after it and any trailing comments will be skipped.
      // This is fine, because trailing comments (sans whitespace)
      // should be skipped anyway.
      out.Append(token, stream.IsAttrTainted(start, end),
                 stream.StringRangeAt(start, end - start));
    }
=======
                                     TokenSequence& out) {
  bool success = true;
  while (!range.AtEnd()) {
    const CSSParserToken& token = range.Peek();
    if (token.FunctionId() == CSSValueID::kVar)
      success &= ResolveVarInto(range.ConsumeBlock(), resolver, out);
    else if (token.FunctionId() == CSSValueID::kEnv)
      success &= ResolveEnvInto(range.ConsumeBlock(), resolver, out);
    else
      out.Append(range.Consume());
>>>>>>> chromium
  }
  return success;
}

bool StyleCascade::ResolveVarInto(CSSParserTokenRange range,
                                  CascadeResolver& resolver,
<<<<<<< HEAD
                                  const CSSParserContext& context,
                                  const FunctionContext* function_context,
                                  TokenSequence& out) {
  AtomicString var_name = ConsumeVariableName(stream);
  DCHECK(stream.AtEnd() || (stream.Peek().GetType() == kCommaToken));
=======
                                  TokenSequence& out) {
  AtomicString variable_name = ConsumeVariableName(range);
  DCHECK(range.AtEnd() || (range.Peek().GetType() == kCommaToken));

  CustomProperty property(variable_name, state_.GetDocument());
>>>>>>> chromium

  // If we have a fallback, we must process it to look for cycles,
  // even if we are not going to use the fallback.
  //
  // https://drafts.csswg.org/css-variables/#cycles
  TokenSequence fallback;
  bool has_fallback = false;
  // Note: has_comma may be `true` even for fallbacks which contain
  // invalid var(). This is needed for syntax validation of fallbacks for
  // registered custom properties.
  // TODO(crbug.com/372475301): Remove this, if possible.
  bool has_comma = false;
  if (ConsumeComma(stream)) {
    has_comma = true;
    stream.ConsumeWhitespace();
    has_fallback =
        ResolveTokensInto(stream, resolver, context, function_context,
                          /* stop_type */ kEOFToken, fallback);
    // Even if the above call to ResolveTokensInto caused a cycle
    // (resolver.InCycle()==true), we must proceed to look for cycles in the
    // non-fallback branch. For example, suppose we are currently resolving
    // the ', var(--z)' part of the following:
    //
    //  --x: var(--y, var(--z));
    //  --y: var(--x);
    //  --z: var(--x);
    //
    // The properties --x and --z would be detected as cyclic as a result,
    // but we also need to discover the cycle between --x and --y.
  }

  // Within a function context (i.e. when resolving values within the body of
  // an @function rule), var() must first look for local variables
  // and arguments.
  //
  // https://drafts.csswg.org/css-mixins-1/#locally-substitute-a-var
  if (function_context) {
    // TODO(crbug.com/325504770): Handle cycles.

    // Locals shadow arguments, which shadow custom properties
    // from the element.
    //
    // Note that for arguments, there's nothing to actually resolve within
    // the value; substitution functions were already eliminated at the
    // call site by ResolveFunctionInto. We're still using ResolveTokensInto,
    // since it's the most convenient way to "paste" the value into `out`.
    //
    // TODO(crbug.com/325504770): Avoid tokenization/ResolveTokensInto
    // for arguments.
    //
    // For locals, we do need to resolve var() (etc) here, but we should
    // probably find a way to not repeat work for multiple references to
    // the same substitution. E.g. for --c:var(--a);--b:var(--a)--a:<stuff>,
    // we should resolve <stuff> only once.
    //
    // TODO(crbug.com/325504770): Cache local resolves, as described above.
    if (const CSSValue* local_variable =
            FindOrNull(function_context->locals, var_name)) {
      return ResolveArgumentOrLocalInto(
          *local_variable, stream, resolver, context, function_context,
          (has_fallback ? &fallback : nullptr), out);
    }
    if (const CSSValue* argument =
            FindOrNull(function_context->arguments, var_name)) {
      return ResolveArgumentOrLocalInto(
          *argument, stream, resolver, context, function_context,
          (has_fallback ? &fallback : nullptr), out);
    }
  }

  CustomProperty property(var_name, state_.GetDocument());

  // Any custom property referenced (by anything, even just once) in the
  // document can currently not be animated on the compositor. Hence we mark
  // properties that have been referenced.
  DCHECK(resolver.CurrentProperty());
  MarkIsReferenced(*resolver.CurrentProperty(), property);

  if (!resolver.DetectCycle(property)) {
    // We are about to substitute var(property). In order to do that, we must
    // know the computed value of 'property', hence we Apply it.
    //
    // We can however not do this if we're in a cycle. If a cycle is detected
    // here, it means we are already resolving 'property', and have discovered
    // a reference to 'property' during that resolution.
    LookupAndApply(property, resolver);
  }
  // Note that this check catches cycles detected by the DetectCycle call
  // immediately above, but also any cycles detected during processing of the
  // fallback near the start of this function.
  if (resolver.InCycle()) {
    return false;
  }

  scoped_refptr<CSSVariableData> data = GetVariableData(property);

  // If substitution is not allowed, treat the value as
  // invalid-at-computed-value-time.
  //
  // https://drafts.csswg.org/css-variables/#animation-tainted
  if (!resolver.AllowSubstitution(data.get()))
    data = nullptr;

  // The fallback must match the syntax of the referenced custom
  // property, even if the fallback isn't used.
  //
<<<<<<< HEAD
  // TODO(crbug.com/372475301): Remove this, if possible.
  //
  // https://drafts.css-houdini.org/css-properties-values-api-1/#fallbacks-in-var-references
  if (has_comma && !ValidateFallback(property, fallback.OriginalText())) {
    CountUse(WebFeature::kVarFallbackValidation);
=======
  // https://drafts.csswg.org/css-variables/#cycles
  if (ConsumeComma(range)) {
    TokenSequence fallback;
    bool success = ResolveTokensInto(range, resolver, fallback);
    // The fallback must match the syntax of the referenced custom property.
    // https://drafts.css-houdini.org/css-properties-values-api-1/#fallbacks-in-var-references
    if (!ValidateFallback(property, fallback.TokenRange()))
      return false;
    if (!data && success)
      data = fallback.BuildVariableData();
  }

  if (!data || resolver.InCycle())
>>>>>>> chromium
    return false;

<<<<<<< HEAD
  if (!data) {
    // No substitution value found; attempt fallback.
    if (has_fallback) {
      return out.AppendFallback(fallback,
                                !fallback.GetAttrTaintedRanges()->empty(),
                                CSSVariableData::kMaxVariableBytes);
    }
    return false;
  }

  return out.Append(data, data->IsAttrTainted(),
                    CSSVariableData::kMaxVariableBytes);
}

bool StyleCascade::ResolveFunctionInto(StringView function_name,
                                       CSSParserTokenStream& stream,
                                       CascadeResolver& resolver,
                                       const CSSParserContext& context,
                                       const FunctionContext* function_context,
                                       TokenSequence& out) {
  state_.StyleBuilder().SetAffectedByCSSFunction();

  // TODO(sesse): Deal with tree-scoped references.
  StyleRuleFunction* function = nullptr;
  if (GetDocument().GetScopedStyleResolver()) {
    function =
        GetDocument().GetScopedStyleResolver()->FunctionForName(function_name);
  }
  if (!function) {
    return false;
  }

  // Parse and resolve function arguments.
  HeapHashMap<String, Member<const CSSValue>> function_arguments;

  bool first_parameter = true;
  for (const StyleRuleFunction::Parameter& parameter :
       function->GetParameters()) {
    stream.ConsumeWhitespace();

    StringView argument_string;

    if (!stream.AtEnd() &&
        (first_parameter || stream.Peek().GetType() == kCommaToken)) {
      first_parameter = false;
      if (stream.Peek().GetType() == kCommaToken) {
        stream.ConsumeIncludingWhitespace();
      }
      wtf_size_t value_start_offset = stream.LookAheadOffset();
      stream.SkipUntilPeekedTypeIs<kCommaToken>();
      wtf_size_t value_end_offset = stream.LookAheadOffset();
      argument_string = stream.StringRangeAt(
          value_start_offset, value_end_offset - value_start_offset);
      // Explicitly empty values, e.g. --foo(1,,3), are not allowed.
      if (argument_string.empty()) {
        return false;
      }
    } else if (parameter.default_value) {
      argument_string = parameter.default_value->OriginalText();
    } else {
      // Argument was missing, with no default.
      return false;
    }

    DCHECK(!argument_string.empty());

    // We need to resolve the argument in the context of this function,
    // so that we can do type coercion on the resolved value before the call.
    // In particular, we want any var() within the argument to be resolved
    // in our context; e.g., --foo(var(--a)) should be our a, not foo's a
    // (if that even exists).
    //
    // Note that if this expression comes from directly a function call,
    // as in the example above (and if the return and argument types are the
    // same), we will effectively do type parsing of exactly the same data
    // twice. This is wasteful, and it's possible that we should do something
    // about it if it proves to be a common case.
    const CSSValue* argument_value = ResolveFunctionExpression(
        argument_string, parameter.type, resolver, context, function_context);
    if (argument_value == nullptr) {
      return false;
    }

    function_arguments.insert(parameter.name, argument_value);
  }

  if (!stream.AtEnd()) {
    // This could mean that we have more arguments than we have parameters,
    // which isn't allowed.
    return false;
  }

  // For now, we only support @function rules that contain a single
  // CSSNestedDeclarations rule with a single 'result' descriptor.
  //
  // TODO(crbug.com/325504770): Support conditional rules.
  HeapVector<Member<StyleRuleBase>>& child_rules = function->ChildRules();
  if (child_rules.size() != 1u) {
    return false;
  }
  const auto* function_declarations =
      DynamicTo<StyleRuleFunctionDeclarations>(child_rules.front().Get());
  if (!function_declarations) {
    return false;
  }
  const CSSPropertyValueSet& propety_value_set =
      function_declarations->Properties();

  // Collect local variables. Any substitution functions found within relevant
  // locals will be substituted during the call to ResolveFunctionExpression
  // for the 'result' descriptor; they are not substituted here.
  HeapHashMap<String, Member<const CSSValue>> locals;
  for (const CSSPropertyValue& property_value :
       propety_value_set.Properties()) {
    if (property_value.PropertyID() == CSSPropertyID::kVariable) {
      const auto& unresolved_local =
          To<CSSUnparsedDeclarationValue>(property_value.Value());
      locals.insert(property_value.CustomPropertyName(), &unresolved_local);
    }
  }

  const auto* unresolved_result = DynamicTo<CSSUnparsedDeclarationValue>(
      propety_value_set.GetPropertyCSSValue(CSSPropertyID::kResult));
  if (!unresolved_result) {
    return false;
  }

  FunctionContext local_function_context{function_arguments, locals};
  const CSSValue* ret_value = ResolveFunctionExpression(
      unresolved_result->VariableDataValue()->OriginalText(),
      function->GetReturnType(), resolver, context, &local_function_context);
  if (ret_value == nullptr) {
    return false;
  }
  // TODO(crbug.com/325504770): Urggg
  String ret_string = ret_value->CssText();
  CSSParserTokenStream ret_value_stream(ret_string);
  return ResolveTokensInto(ret_value_stream, resolver, context,
                           /* function_context */ nullptr,
                           /* stop_type */ kEOFToken, out);
}

bool StyleCascade::ResolveArgumentOrLocalInto(
    const CSSValue& value,
    CSSParserTokenStream& stream,
    CascadeResolver& resolver,
    const CSSParserContext& context,
    const FunctionContext* function_context,
    const TokenSequence* fallback,
    TokenSequence& out) {
  String value_str = value.CssText();
  CSSParserTokenStream value_stream(value_str);
  bool success =
      ResolveTokensInto(value_stream, resolver, context, function_context,
                        /* stop_type */ kEOFToken, out);
  if (!success && fallback) {
    success = out.AppendFallback(*fallback,
                                 !fallback->GetAttrTaintedRanges()->empty(),
                                 CSSVariableData::kMaxVariableBytes);
  }
  return success;
}

// Resolves an expression within a function; in practice, either a function
// argument or its return value. In practice, this is about taking a string
// and coercing it into the given type -- and then the caller will convert it
// right back to a string again. This is pretty suboptimal, but it's the way
// registered properties also work, and crucially, without such a resolve step
// (which needs a type), we would not be able to collapse calc() expressions
// and similar, which could cause massive blowup as the values are passed
// through a large tree of function calls.
const CSSValue* StyleCascade::ResolveFunctionExpression(
    StringView expr,
    const CSSSyntaxDefinition& type,
    CascadeResolver& resolver,
    const CSSParserContext& context,
    const FunctionContext* function_context) {
  TokenSequence resolved_expr;

  CSSParserTokenStream argument_stream(expr);
  if (!ResolveTokensInto(argument_stream, resolver, context, function_context,
                         /* stop_type */ kEOFToken, resolved_expr)) {
    return nullptr;
  }

  const CSSValue* value = type.Parse(resolved_expr.OriginalText(), context,
                                     /*is_animation_tainted=*/false);
  if (!value) {
    return nullptr;
  }

  // TODO(crbug.com/325504770): We need to return a CSSUnparsedDeclarationValue
  // (or CSSVariableData) from this function. We're currently losing
  // tainting information held by TokenSequence.

  // Resolve the value as if it were a registered property, to get rid of
  // extraneous calc(), resolve lengths and so on.
  return &StyleBuilderConverter::ConvertRegisteredPropertyValue(state_, *value,
                                                                &context);
}

bool StyleCascade::ResolveEnvInto(CSSParserTokenStream& stream,
=======
  // https://drafts.csswg.org/css-variables/#long-variables
  if (data->Tokens().size() > kMaxSubstitutionTokens)
    return false;

  out.Append(data.get());

  return true;
}

bool StyleCascade::ResolveEnvInto(CSSParserTokenRange range,
>>>>>>> chromium
                                  CascadeResolver& resolver,
                                  TokenSequence& out) {
<<<<<<< HEAD
  state_.StyleBuilder().SetHasEnv();
  AtomicString variable_name = ConsumeVariableName(stream);

  if (variable_name == "safe-area-inset-bottom") {
    state_.StyleBuilder().SetHasEnvSafeAreaInsetBottom();
    state_.GetDocument()
        .GetStyleEngine()
        .SetNeedsToUpdateComplexSafeAreaConstraints();
  }

  DCHECK(stream.AtEnd() || (stream.Peek().GetType() == kCommaToken) ||
         (stream.Peek().GetType() == kNumberToken));
=======
  AtomicString variable_name = ConsumeVariableName(range);
  DCHECK(range.AtEnd() || (range.Peek().GetType() == kCommaToken));
>>>>>>> chromium

  CSSVariableData* data = GetEnvironmentVariable(variable_name);

  if (!data) {
<<<<<<< HEAD
    if (ConsumeComma(stream)) {
      return ResolveTokensInto(stream, resolver, context,
                               /* function_context */ nullptr,
                               /* stop_type */ kEOFToken, out);
    }
    return false;
  }

  return out.Append(data, data->IsAttrTainted());
}

bool StyleCascade::ResolveAttrInto(CSSParserTokenStream& stream,
                                   CascadeResolver& resolver,
                                   const CSSParserContext& context,
                                   TokenSequence& out) {
  AtomicString local_name = ConsumeVariableName(stream);
  if (resolver.DetectCycle(local_name)) {
    return false;
  }
  CascadeResolver::AutoLock lock(local_name, resolver);
  std::optional<CSSAttrType> attr_type = CSSAttrType::Consume(stream);
  if (!attr_type.has_value()) {
    attr_type = CSSAttrType::GetDefaultValue();
  }
  DCHECK(stream.AtEnd() || stream.Peek().GetType() == kCommaToken);

  Element& element = state_.GetUltimateOriginatingElementOrSelf();

  // TODO(crbug.com/387281256): Support namespaces.
  const String& attribute_value = element.getAttributeNS(
      /*namespace_uri=*/g_null_atom, element.LowercaseIfNecessary(local_name));

  String substituted_attribute_value = attribute_value;
  if (!attribute_value.IsNull() && !attr_type->IsString()) {
    TokenSequence substituted_attribute_token_sequence;
    CSSParserTokenStream attribute_value_stream(attribute_value);
    if (!ResolveTokensInto(attribute_value_stream, resolver, context,
                           /* function_context */ nullptr,
                           /* stop_type */ kEOFToken,
                           substituted_attribute_token_sequence)) {
      return false;
    }
    substituted_attribute_value =
        substituted_attribute_token_sequence.OriginalText();
  }

  const CSSValue* substitution_value =
      (!attribute_value || !substituted_attribute_value)
          ? nullptr
          : attr_type->Parse(substituted_attribute_value, context);

  if (ConsumeComma(stream)) {
    stream.ConsumeWhitespace();

    TokenSequence fallback;
    if (!ResolveTokensInto(stream, resolver, context,
                           /* function_context */ nullptr,
                           /* stop_type */ kEOFToken, fallback)) {
      return false;
    }
    if (!substitution_value) {
      return out.AppendFallback(fallback, /* is_attr_tainted */ true,
                                CSSVariableData::kMaxVariableBytes);
    }
  }

  if (attr_type->IsString() && !substitution_value) {
    // If the <attr-type> argument is omitted, the fallback defaults to the
    // empty string if omitted.
    // https://drafts.csswg.org/css-values-5/#attr-notation
    out.Append(CSSParserToken(kStringToken, g_empty_atom),
               /* is_attr_tainted */ true, g_empty_atom);
    return true;
  }

  if (substitution_value) {
    out.Append(substitution_value, /* is_attr_tainted */ true,
               CSSVariableData::kMaxVariableBytes);
    return true;
  }

  return false;
}

bool StyleCascade::ResolveAutoBaseInto(
    CSSParserTokenStream& stream,
    CascadeResolver& resolver,
    const CSSParserContext& context,
    TokenSequence& out) {
  const CSSProperty& appearance = GetCSSPropertyAppearance();
  if (resolver.DetectCycle(appearance)) {
    return false;
  }
  LookupAndApply(appearance, resolver);

  // Note that the InBaseSelectAppearance() flag is set by StyleAdjuster,
  // which hasn't happened yet. Therefore we also need to check
  // HasBaseSelectAppearance() here.
  bool has_base_appearance = state_.StyleBuilder().HasBaseSelectAppearance() ||
                             state_.StyleBuilder().InBaseSelectAppearance();

  if (has_base_appearance) {
    // We want to the second argument.
    stream.SkipUntilPeekedTypeIs<kCommaToken>();
    CHECK(!stream.AtEnd());
    stream.ConsumeIncludingWhitespace();  // kCommaToken
  }

  return ResolveTokensInto(stream, resolver, context,
                           /* function_context */ nullptr,
                           /* stop_type */ kCommaToken, out);
=======
    if (ConsumeComma(range))
      return ResolveTokensInto(range, resolver, out);
    return false;
  }

  out.Append(data);

  return true;
>>>>>>> chromium
}

CSSVariableData* StyleCascade::GetVariableData(
    const CustomProperty& property) const {
  const AtomicString& name = property.GetPropertyNameAtomicString();
  const bool is_inherited = property.IsInherited();
  return state_.StyleRef().GetVariableData(name, is_inherited);
}

CSSVariableData* StyleCascade::GetEnvironmentVariable(
    const AtomicString& name) const {
  // If we are in a User Agent Shadow DOM then we should not record metrics.
  ContainerNode& scope_root = state_.GetElement().GetTreeScope().RootNode();
  auto* shadow_root = DynamicTo<ShadowRoot>(&scope_root);
  bool is_ua_scope = shadow_root && shadow_root->IsUserAgent();

  return state_.GetDocument()
      .GetStyleEngine()
      .EnsureEnvironmentVariables()
      .ResolveVariable(name, !is_ua_scope);
}

const CSSParserContext* StyleCascade::GetParserContext(
    const CSSVariableReferenceValue& value) {
  // TODO(crbug.com/985028): CSSVariableReferenceValue should always have a
  // CSSParserContext. (CSSUnparsedValue violates this).
  if (value.ParserContext())
    return value.ParserContext();
  return StrictCSSParserContext(
      state_.GetDocument().GetExecutionContext()->GetSecureContextMode());
}

bool StyleCascade::HasFontSizeDependency(const CustomProperty& property,
                                         CSSVariableData* data) const {
  if (!property.IsRegistered() || !data)
    return false;
  if (data->HasFontUnits())
    return true;
  if (data->HasRootFontUnits() && IsRootElement())
    return true;
  return false;
}

bool StyleCascade::ValidateFallback(const CustomProperty& property,
                                    CSSParserTokenRange range) const {
  if (!property.IsRegistered())
    return true;
  auto context_mode =
      state_.GetDocument().GetExecutionContext()->GetSecureContextMode();
  auto var_mode = CSSParserLocalContext::VariableMode::kTyped;
  auto* context = StrictCSSParserContext(context_mode);
  auto local_context = CSSParserLocalContext().WithVariableMode(var_mode);
  return property.ParseSingleValue(range, *context, local_context);
}

void StyleCascade::MarkIsReferenced(const CSSProperty& referencer,
                                    const CustomProperty& referenced) {
  if (!referenced.IsRegistered())
    return;
  const AtomicString& name = referenced.GetPropertyNameAtomicString();
  state_.GetDocument().EnsurePropertyRegistry().MarkReferenced(name);
}

void StyleCascade::MarkHasVariableReference(const CSSProperty& property) {
<<<<<<< HEAD
  state_.StyleBuilder().SetHasVariableReference();
}

void StyleCascade::ApplyUnresolvedEnv() {
  // Currently the only field that depends on parsing unresolved env().
  ApplyIsBottomRelativeToSafeAreaInset();
}

void StyleCascade::ApplyIsBottomRelativeToSafeAreaInset() {
  if (!state_.StyleBuilder().HasEnvSafeAreaInsetBottom() ||
      !map_.NativeBitset().Has(CSSPropertyID::kBottom)) {
    return;
  }

  const CascadePriority* p = map_.FindKnownToExist(CSSPropertyID::kBottom);
  if (p->GetOrigin() >= CascadeOrigin::kAnimation) {
    // Effect values from animations/transition do not contain env().
    return;
  }

  const CSSValue* value = ValueAt(match_result_, p->GetPosition());
  const auto* unparsed = DynamicTo<CSSUnparsedDeclarationValue>(value);
  if (!unparsed) {
    return;  // Does not contain env().
  }

  // IsSafeAreaInsetBottom assumes the fallback is not taken.
  DCHECK(GetEnvironmentVariable(AtomicString("safe-area-inset-bottom"),
                                /*indices=*/WTF::Vector<unsigned>()));

  if (CSSParserFastPaths::IsSafeAreaInsetBottom(
          unparsed->VariableDataValue()->OriginalText())) {
    state_.StyleBuilder().SetIsBottomRelativeToSafeAreaInset(true);

    UseCounter::Count(
        state_.GetDocument(),
        WebFeature::kCSSEnvironmentVariable_SafeAreaInsetBottom_FastPath);
  }
}

bool StyleCascade::TreatAsRevertLayer(CascadePriority priority) const {
  return priority.IsTryStyle() && !ComputedStyle::HasOutOfFlowPosition(
                                      state_.StyleBuilder().GetPosition());
=======
  if (!property.IsInherited())
    state_.Style()->SetHasVariableReferenceFromNonInheritedProperty();
  state_.Style()->SetHasVariableReference();
>>>>>>> chromium
}

const Document& StyleCascade::GetDocument() const {
  return state_.GetDocument();
}

const CSSProperty& StyleCascade::ResolveSurrogate(const CSSProperty& property) {
  if (!property.IsSurrogate())
    return property;
  // This marks the cascade as dependent on cascade-affecting properties
  // even for simple surrogates like -webkit-writing-mode, but there isn't
  // currently a flag to distinguish such surrogates from e.g. css-logical
  // properties.
  depends_on_cascade_affecting_property_ = true;
  const CSSProperty* original = property.SurrogateFor(
      state_.Style()->Direction(), state_.Style()->GetWritingMode());
  DCHECK(original);
  return *original;
}

void StyleCascade::CountUse(WebFeature feature) {
  GetDocument().CountUse(feature);
}

void StyleCascade::MaybeUseCountRevert(const CSSValue& value) {
  if (IsRevert(value))
    CountUse(WebFeature::kCSSKeywordRevert);
}

}  // namespace blink
