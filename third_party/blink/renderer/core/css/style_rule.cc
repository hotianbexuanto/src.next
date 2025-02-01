/*
 * (C) 1999-2003 Lars Knoll (knoll@kde.org)
 * (C) 2002-2003 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2002, 2005, 2006, 2008, 2012 Apple Inc. All rights reserved.
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

#include "third_party/blink/renderer/core/css/style_rule.h"

#include "third_party/blink/renderer/core/css/css_container_rule.h"
#include "third_party/blink/renderer/core/css/css_counter_style_rule.h"
#include "third_party/blink/renderer/core/css/css_font_face_rule.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/css/css_font_feature_values_rule.h"
#include "third_party/blink/renderer/core/css/css_font_palette_values_rule.h"
#include "third_party/blink/renderer/core/css/css_function_declarations_rule.h"
#include "third_party/blink/renderer/core/css/css_function_rule.h"
=======
>>>>>>> chromium
#include "third_party/blink/renderer/core/css/css_identifier_value.h"
#include "third_party/blink/renderer/core/css/css_import_rule.h"
#include "third_party/blink/renderer/core/css/css_keyframes_rule.h"
#include "third_party/blink/renderer/core/css/css_media_rule.h"
#include "third_party/blink/renderer/core/css/css_namespace_rule.h"
#include "third_party/blink/renderer/core/css/css_page_rule.h"
#include "third_party/blink/renderer/core/css/css_property_rule.h"
#include "third_party/blink/renderer/core/css/css_scroll_timeline_rule.h"
#include "third_party/blink/renderer/core/css/css_style_rule.h"
#include "third_party/blink/renderer/core/css/css_supports_rule.h"
#include "third_party/blink/renderer/core/css/style_rule_counter_style.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/css/style_rule_font_feature_values.h"
#include "third_party/blink/renderer/core/css/style_rule_font_palette_values.h"
#include "third_party/blink/renderer/core/css/style_rule_function_declarations.h"
=======
>>>>>>> chromium
#include "third_party/blink/renderer/core/css/style_rule_import.h"
#include "third_party/blink/renderer/core/css/style_rule_keyframe.h"
#include "third_party/blink/renderer/core/css/style_rule_namespace.h"
#include "third_party/blink/renderer/platform/wtf/size_assertions.h"

namespace blink {

struct SameSizeAsStyleRuleBase final
    : public GarbageCollected<SameSizeAsStyleRuleBase> {
  uint8_t field;
};

ASSERT_SIZE(StyleRuleBase, SameSizeAsStyleRuleBase);

CSSRule* StyleRuleBase::CreateCSSOMWrapper(CSSStyleSheet* parent_sheet) const {
  return CreateCSSOMWrapper(parent_sheet, nullptr);
}

CSSRule* StyleRuleBase::CreateCSSOMWrapper(CSSRule* parent_rule) const {
  return CreateCSSOMWrapper(nullptr, parent_rule);
}

void StyleRuleBase::Trace(Visitor* visitor) const {
  switch (GetType()) {
    case kCharset:
      To<StyleRuleCharset>(this)->TraceAfterDispatch(visitor);
      return;
    case kStyle:
      To<StyleRule>(this)->TraceAfterDispatch(visitor);
      return;
    case kPage:
      To<StyleRulePage>(this)->TraceAfterDispatch(visitor);
      return;
    case kProperty:
      To<StyleRuleProperty>(this)->TraceAfterDispatch(visitor);
      return;
    case kFontFace:
      To<StyleRuleFontFace>(this)->TraceAfterDispatch(visitor);
      return;
    case kMedia:
      To<StyleRuleMedia>(this)->TraceAfterDispatch(visitor);
      return;
<<<<<<< HEAD
    case kNestedDeclarations:
      To<StyleRuleNestedDeclarations>(this)->TraceAfterDispatch(visitor);
      return;
    case kFunctionDeclarations:
      To<StyleRuleFunctionDeclarations>(this)->TraceAfterDispatch(visitor);
      return;
    case kScope:
      To<StyleRuleScope>(this)->TraceAfterDispatch(visitor);
=======
    case kScrollTimeline:
      To<StyleRuleScrollTimeline>(this)->TraceAfterDispatch(visitor);
>>>>>>> chromium
      return;
    case kSupports:
      To<StyleRuleSupports>(this)->TraceAfterDispatch(visitor);
      return;
    case kImport:
      To<StyleRuleImport>(this)->TraceAfterDispatch(visitor);
      return;
    case kKeyframes:
      To<StyleRuleKeyframes>(this)->TraceAfterDispatch(visitor);
      return;
    case kKeyframe:
      To<StyleRuleKeyframe>(this)->TraceAfterDispatch(visitor);
      return;
    case kNamespace:
      To<StyleRuleNamespace>(this)->TraceAfterDispatch(visitor);
      return;
    case kViewport:
      To<StyleRuleViewport>(this)->TraceAfterDispatch(visitor);
      return;
    case kContainer:
      To<StyleRuleContainer>(this)->TraceAfterDispatch(visitor);
      return;
    case kCounterStyle:
      To<StyleRuleCounterStyle>(this)->TraceAfterDispatch(visitor);
      return;
  }
  NOTREACHED();
}

void StyleRuleBase::FinalizeGarbageCollectedObject() {
  switch (GetType()) {
    case kCharset:
      To<StyleRuleCharset>(this)->~StyleRuleCharset();
      return;
    case kStyle:
      To<StyleRule>(this)->~StyleRule();
      return;
    case kPage:
      To<StyleRulePage>(this)->~StyleRulePage();
      return;
    case kProperty:
      To<StyleRuleProperty>(this)->~StyleRuleProperty();
      return;
    case kFontFace:
      To<StyleRuleFontFace>(this)->~StyleRuleFontFace();
      return;
    case kMedia:
      To<StyleRuleMedia>(this)->~StyleRuleMedia();
      return;
<<<<<<< HEAD
    case kNestedDeclarations:
      To<StyleRuleNestedDeclarations>(this)->~StyleRuleNestedDeclarations();
      return;
    case kFunctionDeclarations:
      To<StyleRuleFunctionDeclarations>(this)->~StyleRuleFunctionDeclarations();
      return;
    case kScope:
      To<StyleRuleScope>(this)->~StyleRuleScope();
=======
    case kScrollTimeline:
      To<StyleRuleScrollTimeline>(this)->~StyleRuleScrollTimeline();
>>>>>>> chromium
      return;
    case kSupports:
      To<StyleRuleSupports>(this)->~StyleRuleSupports();
      return;
    case kImport:
      To<StyleRuleImport>(this)->~StyleRuleImport();
      return;
    case kKeyframes:
      To<StyleRuleKeyframes>(this)->~StyleRuleKeyframes();
      return;
    case kKeyframe:
      To<StyleRuleKeyframe>(this)->~StyleRuleKeyframe();
      return;
    case kNamespace:
      To<StyleRuleNamespace>(this)->~StyleRuleNamespace();
      return;
    case kViewport:
      To<StyleRuleViewport>(this)->~StyleRuleViewport();
      return;
    case kContainer:
      To<StyleRuleContainer>(this)->~StyleRuleContainer();
      return;
    case kCounterStyle:
      To<StyleRuleCounterStyle>(this)->~StyleRuleCounterStyle();
      return;
  }
  NOTREACHED();
}

StyleRuleBase* StyleRuleBase::Copy() const {
  switch (GetType()) {
    case kStyle:
      return To<StyleRule>(this)->Copy();
    case kPage:
      return To<StyleRulePage>(this)->Copy();
    case kProperty:
      return To<StyleRuleProperty>(this)->Copy();
    case kFontFace:
      return To<StyleRuleFontFace>(this)->Copy();
    case kMedia:
      return To<StyleRuleMedia>(this)->Copy();
<<<<<<< HEAD
    case kNestedDeclarations:
      return To<StyleRuleNestedDeclarations>(this)->Copy();
    case kFunctionDeclarations:
      return To<StyleRuleFunctionDeclarations>(this)->Copy();
    case kScope:
      return To<StyleRuleScope>(this)->Copy();
=======
    case kScrollTimeline:
      return To<StyleRuleScrollTimeline>(this)->Copy();
>>>>>>> chromium
    case kSupports:
      return To<StyleRuleSupports>(this)->Copy();
    case kImport:
      // FIXME: Copy import rules.
      NOTREACHED();
      return nullptr;
    case kKeyframes:
      return To<StyleRuleKeyframes>(this)->Copy();
    case kViewport:
      return To<StyleRuleViewport>(this)->Copy();
    case kNamespace:
      return To<StyleRuleNamespace>(this)->Copy();
    case kCharset:
    case kKeyframe:
      NOTREACHED();
      return nullptr;
    case kContainer:
      return To<StyleRuleContainer>(this)->Copy();
    case kCounterStyle:
      return To<StyleRuleCounterStyle>(this)->Copy();
  }
  NOTREACHED();
  return nullptr;
}

CSSRule* StyleRuleBase::CreateCSSOMWrapper(CSSStyleSheet* parent_sheet,
                                           CSSRule* parent_rule) const {
  CSSRule* rule = nullptr;
  StyleRuleBase* self = const_cast<StyleRuleBase*>(this);
  switch (GetType()) {
    case kStyle:
      rule =
          MakeGarbageCollected<CSSStyleRule>(To<StyleRule>(self), parent_sheet);
      break;
    case kPage:
      rule = MakeGarbageCollected<CSSPageRule>(To<StyleRulePage>(self),
                                               parent_sheet);
      break;
    case kProperty:
      rule = MakeGarbageCollected<CSSPropertyRule>(To<StyleRuleProperty>(self),
                                                   parent_sheet);
      break;
    case kFontFace:
      rule = MakeGarbageCollected<CSSFontFaceRule>(To<StyleRuleFontFace>(self),
                                                   parent_sheet);
      break;
    case kMedia:
      rule = MakeGarbageCollected<CSSMediaRule>(To<StyleRuleMedia>(self),
                                                parent_sheet);
      break;
<<<<<<< HEAD
    case kNestedDeclarations:
      rule = MakeGarbageCollected<CSSNestedDeclarationsRule>(
          To<StyleRuleNestedDeclarations>(self), parent_sheet);
      break;
    case kFunctionDeclarations:
      rule = MakeGarbageCollected<CSSFunctionDeclarationsRule>(
          To<StyleRuleFunctionDeclarations>(self), parent_sheet);
      break;
    case kFunction:
      rule = MakeGarbageCollected<CSSFunctionRule>(To<StyleRuleFunction>(self),
                                                   parent_sheet);
      break;
    case kScope:
      rule = MakeGarbageCollected<CSSScopeRule>(To<StyleRuleScope>(self),
                                                parent_sheet);
=======
    case kScrollTimeline:
      rule = MakeGarbageCollected<CSSScrollTimelineRule>(
          To<StyleRuleScrollTimeline>(self), parent_sheet);
>>>>>>> chromium
      break;
    case kSupports:
      rule = MakeGarbageCollected<CSSSupportsRule>(To<StyleRuleSupports>(self),
                                                   parent_sheet);
      break;
    case kImport:
      rule = MakeGarbageCollected<CSSImportRule>(To<StyleRuleImport>(self),
                                                 parent_sheet);
      break;
    case kKeyframes:
      rule = MakeGarbageCollected<CSSKeyframesRule>(
          To<StyleRuleKeyframes>(self), parent_sheet);
      break;
    case kNamespace:
      rule = MakeGarbageCollected<CSSNamespaceRule>(
          To<StyleRuleNamespace>(self), parent_sheet);
      break;
    case kContainer:
      rule = MakeGarbageCollected<CSSContainerRule>(
          To<StyleRuleContainer>(self), parent_sheet);
      break;
    case kCounterStyle:
      rule = MakeGarbageCollected<CSSCounterStyleRule>(
          To<StyleRuleCounterStyle>(self), parent_sheet);
      break;
    case kKeyframe:
    case kCharset:
<<<<<<< HEAD
    case kMixin:
    case kApplyMixin:
=======
    case kViewport:
>>>>>>> chromium
      NOTREACHED();
      return nullptr;
  }
  if (parent_rule)
    rule->SetParentRule(parent_rule);
  return rule;
}

unsigned StyleRule::AverageSizeInBytes() {
  return sizeof(StyleRule) + sizeof(CSSSelector) +
         CSSPropertyValueSet::AverageSizeInBytes();
}

StyleRule::StyleRule(CSSSelectorList selector_list,
                     CSSPropertyValueSet* properties)
    : StyleRuleBase(kStyle),
      should_consider_for_matching_rules_(kConsiderIfNonEmpty),
      selector_list_(std::move(selector_list)),
      properties_(properties) {}

StyleRule::StyleRule(CSSSelectorList selector_list,
                     CSSLazyPropertyParser* lazy_property_parser)
    : StyleRuleBase(kStyle),
      should_consider_for_matching_rules_(kAlwaysConsider),
      selector_list_(std::move(selector_list)),
      lazy_property_parser_(lazy_property_parser) {}

const CSSPropertyValueSet& StyleRule::Properties() const {
  if (!properties_) {
    properties_ = lazy_property_parser_->ParseProperties();
    lazy_property_parser_.Clear();
  }
  return *properties_;
}

StyleRule::StyleRule(const StyleRule& o)
    : StyleRuleBase(o),
      should_consider_for_matching_rules_(kConsiderIfNonEmpty),
      selector_list_(o.selector_list_.Copy()),
      properties_(o.Properties().MutableCopy()) {}

StyleRule::~StyleRule() = default;

MutableCSSPropertyValueSet& StyleRule::MutableProperties() {
  // Ensure properties_ is initialized.
  if (!Properties().IsMutable())
    properties_ = properties_->MutableCopy();
  return *To<MutableCSSPropertyValueSet>(properties_.Get());
}

bool StyleRule::PropertiesHaveFailedOrCanceledSubresources() const {
  return properties_ && properties_->HasFailedOrCanceledSubresources();
}

bool StyleRule::ShouldConsiderForMatchingRules(bool include_empty_rules) const {
  DCHECK(should_consider_for_matching_rules_ == kAlwaysConsider || properties_);
  return include_empty_rules ||
         should_consider_for_matching_rules_ == kAlwaysConsider ||
         !properties_->IsEmpty();
}

bool StyleRule::HasParsedProperties() const {
  // StyleRule should only have one of {lazy_property_parser_, properties_} set.
  DCHECK(lazy_property_parser_ || properties_);
  DCHECK(!lazy_property_parser_ || !properties_);
  return !lazy_property_parser_;
}

void StyleRule::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(properties_);
  visitor->Trace(lazy_property_parser_);
  StyleRuleBase::TraceAfterDispatch(visitor);
}

<<<<<<< HEAD
namespace {

bool RenestRules(const HeapVector<Member<StyleRuleBase>>& old_rules,
                 StyleRule* new_parent,
                 HeapVector<Member<StyleRuleBase>>& result) {
  bool renested_any = false;
  for (StyleRuleBase* old_rule : old_rules) {
    StyleRuleBase* renested = old_rule->Renest(new_parent);
    renested_any |= (old_rule != renested);
    result.push_back(renested);
  }
  return renested_any;
}

template <typename T>
StyleRuleBase* RenestGroupRule(T* group_rule, StyleRule* new_parent) {
  HeapVector<Member<StyleRuleBase>> new_child_rules;
  if (!RenestRules(group_rule->ChildRules(), new_parent, new_child_rules)) {
    return group_rule;
  }
  return MakeGarbageCollected<T>(*group_rule, std::move(new_child_rules));
}

}  // namespace

StyleRuleBase* StyleRuleBase::Renest(StyleRule* new_parent) {
  switch (GetType()) {
    case kStyle: {
      HeapVector<CSSSelector> selectors;
      if (!CSSSelectorList::Renest(To<StyleRule>(this)->FirstSelector(),
                                   new_parent, selectors)) {
        return this;
      }
      auto* new_rule = StyleRule::Create(
          selectors, To<StyleRule>(this)->Properties().ImmutableCopyIfNeeded());
      if (HeapVector<Member<StyleRuleBase>>* child_rules =
              To<StyleRule>(this)->ChildRules()) {
        for (StyleRuleBase* child_rule : *child_rules) {
          new_rule->AddChildRule(child_rule->Renest(new_rule));
        }
      }
      return new_rule;
    }
    case kScope: {
      const StyleScope* old_style_scope =
          &To<StyleRuleScope>(this)->GetStyleScope();
      const StyleScope* new_style_scope = old_style_scope->Renest(new_parent);
      if (old_style_scope == new_style_scope) {
        return this;
      }
      CHECK(new_style_scope);
      HeapVector<Member<StyleRuleBase>> new_child_rules;
      RenestRules(To<StyleRuleScope>(this)->ChildRules(),
                  new_style_scope->RuleForNesting(), new_child_rules);
      // Note that `new_child_rules` is usable here even if `RenestRules`
      // returned false.
      return MakeGarbageCollected<StyleRuleScope>(*new_style_scope,
                                                  std::move(new_child_rules));
    }
    case kLayerBlock:
      return RenestGroupRule(To<StyleRuleLayerBlock>(this), new_parent);
    case kContainer:
      return RenestGroupRule(To<StyleRuleContainer>(this), new_parent);
    case kMedia:
      return RenestGroupRule(To<StyleRuleMedia>(this), new_parent);
    case kSupports:
      return RenestGroupRule(To<StyleRuleSupports>(this), new_parent);
    case kStartingStyle: {
      HeapVector<Member<StyleRuleBase>> result;
      if (!RenestRules(To<StyleRuleStartingStyle>(this)->ChildRules(),
                       new_parent, result)) {
        return this;
      }
      return MakeGarbageCollected<StyleRuleStartingStyle>(std::move(result));
    }
    case kPage:
      // Can not contain style rules.
      return this;
    case kMixin:
    case kApplyMixin:
      // The parent pointers in mixins don't really matter;
      // they are always replaced during application anyway.
      return this;
    case kNestedDeclarations: {
      auto* nested_declarations_rule = To<StyleRuleNestedDeclarations>(this);
      // Nested declaration rules are different from regular nested style rules,
      // since they don't refer to their parent rule with any '&' selector.
      // Instead the outer selector list is *copied* parse-time. Now that we're
      // being re-nested, we need to create a new StyleRuleNestedDeclarations
      // rule, again with a copy of the new parent rule's selector list.
      //
      // The copying behavior does not apply to nested declaration rules held
      // by @scope rules, however, since they always just behave like
      // :where(:scope).
      if (nested_declarations_rule->NestingType() == CSSNestingType::kScope) {
        return this;
      }
      StyleRule* old_inner_rule = nested_declarations_rule->InnerStyleRule();
      HeapVector<CSSSelector> selectors =
          CSSSelectorList::Copy(new_parent->FirstSelector());
      auto* new_inner_rule = StyleRule::Create(
          selectors, old_inner_rule->Properties().ImmutableCopyIfNeeded());
      return MakeGarbageCollected<StyleRuleNestedDeclarations>(
          nested_declarations_rule->NestingType(), new_inner_rule);
    }
    case kFunctionDeclarations:
    case kFunction:
      // Can not contain style rules.
      return this;
    case kPageMargin:
    case kProperty:
    case kFontFace:
    case kFontPaletteValues:
    case kFontFeatureValues:
    case kFontFeature:
    case kImport:
    case kKeyframes:
    case kLayerStatement:
    case kNamespace:
    case kCounterStyle:
    case kKeyframe:
    case kCharset:
    case kViewTransition:
    case kPositionTry:
      // Cannot have any child rules.
      return this;
  }
=======
StyleRulePage::StyleRulePage(CSSSelectorList selector_list,
                             CSSPropertyValueSet* properties)
    : StyleRuleBase(kPage),
      properties_(properties),
      selector_list_(std::move(selector_list)) {}

StyleRulePage::StyleRulePage(const StyleRulePage& page_rule)
    : StyleRuleBase(page_rule),
      properties_(page_rule.properties_->MutableCopy()),
      selector_list_(page_rule.selector_list_.Copy()) {}

StyleRulePage::~StyleRulePage() = default;

MutableCSSPropertyValueSet& StyleRulePage::MutableProperties() {
  if (!properties_->IsMutable())
    properties_ = properties_->MutableCopy();
  return *To<MutableCSSPropertyValueSet>(properties_.Get());
}

void StyleRulePage::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(properties_);
  StyleRuleBase::TraceAfterDispatch(visitor);
>>>>>>> chromium
}

StyleRuleProperty::StyleRuleProperty(const String& name,
                                     CSSPropertyValueSet* properties)
    : StyleRuleBase(kProperty), name_(name), properties_(properties) {}

StyleRuleProperty::StyleRuleProperty(const StyleRuleProperty& property_rule)
    : StyleRuleBase(property_rule),
      name_(property_rule.name_),
      properties_(property_rule.properties_->MutableCopy()) {}

StyleRuleProperty::~StyleRuleProperty() = default;

MutableCSSPropertyValueSet& StyleRuleProperty::MutableProperties() {
  if (!properties_->IsMutable())
    properties_ = properties_->MutableCopy();
  return *To<MutableCSSPropertyValueSet>(properties_.Get());
}

const CSSValue* StyleRuleProperty::GetSyntax() const {
  return properties_->GetPropertyCSSValue(CSSPropertyID::kSyntax);
}

const CSSValue* StyleRuleProperty::Inherits() const {
  return properties_->GetPropertyCSSValue(CSSPropertyID::kInherits);
}

const CSSValue* StyleRuleProperty::GetInitialValue() const {
  return properties_->GetPropertyCSSValue(CSSPropertyID::kInitialValue);
}

void StyleRuleProperty::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(properties_);
  StyleRuleBase::TraceAfterDispatch(visitor);
}

StyleRuleFontFace::StyleRuleFontFace(CSSPropertyValueSet* properties)
    : StyleRuleBase(kFontFace), properties_(properties) {}

StyleRuleFontFace::StyleRuleFontFace(const StyleRuleFontFace& font_face_rule)
    : StyleRuleBase(font_face_rule),
      properties_(font_face_rule.properties_->MutableCopy()) {}

MutableCSSPropertyValueSet& StyleRuleFontFace::MutableProperties() {
  if (!properties_->IsMutable())
    properties_ = properties_->MutableCopy();
  return *To<MutableCSSPropertyValueSet>(properties_.Get());
}

void StyleRuleFontFace::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(properties_);
  StyleRuleBase::TraceAfterDispatch(visitor);
}

StyleRuleScrollTimeline::StyleRuleScrollTimeline(
    const String& name,
    const CSSPropertyValueSet* properties)
    : StyleRuleBase(kScrollTimeline),
      name_(name),
      source_(properties->GetPropertyCSSValue(CSSPropertyID::kSource)),
      orientation_(
          properties->GetPropertyCSSValue(CSSPropertyID::kOrientation)),
      start_(properties->GetPropertyCSSValue(CSSPropertyID::kStart)),
      end_(properties->GetPropertyCSSValue(CSSPropertyID::kEnd)),
      time_range_(properties->GetPropertyCSSValue(CSSPropertyID::kTimeRange)) {}

StyleRuleScrollTimeline::~StyleRuleScrollTimeline() = default;

void StyleRuleScrollTimeline::TraceAfterDispatch(
    blink::Visitor* visitor) const {
  visitor->Trace(source_);
  visitor->Trace(orientation_);
  visitor->Trace(start_);
  visitor->Trace(end_);
  visitor->Trace(time_range_);

<<<<<<< HEAD
=======
  StyleRuleBase::TraceAfterDispatch(visitor);
}

>>>>>>> chromium
StyleRuleGroup::StyleRuleGroup(RuleType type,
                               HeapVector<Member<StyleRuleBase>>& adopt_rule)
    : StyleRuleBase(type) {
  child_rules_.swap(adopt_rule);
}

StyleRuleGroup::StyleRuleGroup(const StyleRuleGroup& group_rule)
    : StyleRuleBase(group_rule), child_rules_(group_rule.child_rules_.size()) {
  for (unsigned i = 0; i < child_rules_.size(); ++i)
    child_rules_[i] = group_rule.child_rules_[i]->Copy();
}

void StyleRuleGroup::WrapperInsertRule(unsigned index, StyleRuleBase* rule) {
  child_rules_.insert(index, rule);
}

void StyleRuleGroup::WrapperRemoveRule(unsigned index) {
  child_rules_.EraseAt(index);
}

void StyleRuleGroup::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(child_rules_);
  StyleRuleBase::TraceAfterDispatch(visitor);
}

StyleRuleCondition::StyleRuleCondition(
    RuleType type,
    HeapVector<Member<StyleRuleBase>>& adopt_rules)
    : StyleRuleGroup(type, adopt_rules) {}

<<<<<<< HEAD
StyleRuleLayerBlock::StyleRuleLayerBlock(
    LayerName name,
    HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleGroup(kLayerBlock, std::move(rules)), name_(std::move(name)) {}

StyleRuleLayerBlock::StyleRuleLayerBlock(const StyleRuleLayerBlock& other) =
    default;

StyleRuleLayerBlock::StyleRuleLayerBlock(
    const StyleRuleLayerBlock& other,
    HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleLayerBlock(other.name_, std::move(rules)) {}

void StyleRuleLayerBlock::TraceAfterDispatch(blink::Visitor* visitor) const {
  StyleRuleGroup::TraceAfterDispatch(visitor);
}

String StyleRuleLayerBlock::GetNameAsString() const {
  return LayerNameAsString(name_);
}

StyleRuleLayerStatement::StyleRuleLayerStatement(Vector<LayerName>&& names)
    : StyleRuleBase(kLayerStatement), names_(std::move(names)) {}

StyleRuleLayerStatement::StyleRuleLayerStatement(
    const StyleRuleLayerStatement& other) = default;

void StyleRuleLayerStatement::TraceAfterDispatch(
    blink::Visitor* visitor) const {
  StyleRuleBase::TraceAfterDispatch(visitor);
}

Vector<String> StyleRuleLayerStatement::GetNamesAsStrings() const {
  Vector<String> result;
  for (const auto& name : names_) {
    result.push_back(LayerNameAsString(name));
  }
  return result;
}

StyleRulePage::StyleRulePage(CSSSelectorList* selector_list,
                             CSSPropertyValueSet* properties,
                             HeapVector<Member<StyleRuleBase>> child_rules)
    : StyleRuleGroup(kPage, std::move(child_rules)),
      properties_(properties),
      selector_list_(selector_list) {}

StyleRulePage::StyleRulePage(const StyleRulePage& page_rule)
    : StyleRuleGroup(page_rule),
      properties_(page_rule.properties_->MutableCopy()),
      selector_list_(page_rule.selector_list_->Copy()) {}

MutableCSSPropertyValueSet& StyleRulePage::MutableProperties() {
  if (!properties_->IsMutable()) {
    properties_ = properties_->MutableCopy();
  }
  return *To<MutableCSSPropertyValueSet>(properties_.Get());
}

void StyleRulePage::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(properties_);
  visitor->Trace(layer_);
  visitor->Trace(selector_list_);
  StyleRuleGroup::TraceAfterDispatch(visitor);
}

StyleRulePageMargin::StyleRulePageMargin(CSSAtRuleID id,
                                         CSSPropertyValueSet* properties)
    : StyleRuleBase(kPageMargin), id_(id), properties_(properties) {}

StyleRulePageMargin::StyleRulePageMargin(
    const StyleRulePageMargin& page_margin_rule)
    : StyleRuleBase(page_margin_rule),
      properties_(page_margin_rule.properties_->MutableCopy()) {}

MutableCSSPropertyValueSet& StyleRulePageMargin::MutableProperties() {
  if (!properties_->IsMutable()) {
    properties_ = properties_->MutableCopy();
  }
  return *To<MutableCSSPropertyValueSet>(properties_.Get());
}

void StyleRulePageMargin::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(properties_);
  StyleRuleBase::TraceAfterDispatch(visitor);
}

StyleRuleCondition::StyleRuleCondition(RuleType type,
                                       HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleGroup(type, std::move(rules)) {}

StyleRuleCondition::StyleRuleCondition(RuleType type,
                                       const String& condition_text,
                                       HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleGroup(type, std::move(rules)), condition_text_(condition_text) {}
=======
StyleRuleCondition::StyleRuleCondition(
    RuleType type,
    const String& condition_text,
    HeapVector<Member<StyleRuleBase>>& adopt_rules)
    : StyleRuleGroup(type, adopt_rules), condition_text_(condition_text) {}
>>>>>>> chromium

StyleRuleCondition::StyleRuleCondition(
    const StyleRuleCondition& condition_rule) = default;

StyleRuleMedia::StyleRuleMedia(scoped_refptr<MediaQuerySet> media,
                               HeapVector<Member<StyleRuleBase>>& adopt_rules)
    : StyleRuleCondition(kMedia, adopt_rules), media_queries_(media) {}

StyleRuleMedia::StyleRuleMedia(const StyleRuleMedia& media_rule)
    : StyleRuleCondition(media_rule) {
  if (media_rule.media_queries_)
    media_queries_ = media_rule.media_queries_->Copy();
}

StyleRuleSupports::StyleRuleSupports(
    const String& condition_text,
    bool condition_is_supported,
    HeapVector<Member<StyleRuleBase>>& adopt_rules)
    : StyleRuleCondition(kSupports, condition_text, adopt_rules),
      condition_is_supported_(condition_is_supported) {}

StyleRuleMedia::StyleRuleMedia(const StyleRuleMedia& other,
                               HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleMedia(other.media_queries_, std::move(rules)) {}

void StyleRuleMedia::TraceAfterDispatch(blink::Visitor* visitor) const {
  StyleRuleCondition::TraceAfterDispatch(visitor);
}

StyleRuleSupports::StyleRuleSupports(const StyleRuleSupports& supports_rule)
    : StyleRuleCondition(supports_rule),
      condition_is_supported_(supports_rule.condition_is_supported_) {}

<<<<<<< HEAD
StyleRuleSupports::StyleRuleSupports(const StyleRuleSupports& other,
                                     HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleSupports(other.condition_text_,
                        other.condition_is_supported_,
                        std::move(rules)) {}

void StyleRuleSupports::SetConditionText(
    const ExecutionContext* execution_context,
    String value) {
  CSSParserTokenStream stream(value);
  auto* context = MakeGarbageCollected<CSSParserContext>(*execution_context);
  CSSParserImpl parser(context);

  CSSSupportsParser::Result result =
      CSSSupportsParser::ConsumeSupportsCondition(stream, parser);
  condition_text_ = value;
  condition_is_supported_ = result == CSSSupportsParser::Result::kSupported;
}

StyleRuleContainer::StyleRuleContainer(ContainerQuery& container_query,
                                       HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleCondition(kContainer,
                         container_query.ToString(),
                         std::move(rules)),
=======
StyleRuleContainer::StyleRuleContainer(
    ContainerQuery& container_query,
    HeapVector<Member<StyleRuleBase>>& adopt_rules)
    : StyleRuleCondition(kContainer, adopt_rules),
>>>>>>> chromium
      container_query_(&container_query) {}

StyleRuleContainer::StyleRuleContainer(const StyleRuleContainer& container_rule)
    : StyleRuleCondition(container_rule) {
  DCHECK(container_rule.container_query_);
  container_query_ =
      MakeGarbageCollected<ContainerQuery>(*container_rule.container_query_);
}

<<<<<<< HEAD
StyleRuleContainer::StyleRuleContainer(const StyleRuleContainer& other,
                                       HeapVector<Member<StyleRuleBase>> rules)
    : StyleRuleContainer(*other.container_query_, std::move(rules)) {}

void StyleRuleContainer::SetConditionText(
    const ExecutionContext* execution_context,
    String value) {
  auto* context = MakeGarbageCollected<CSSParserContext>(*execution_context);
  ContainerQueryParser parser(*context);

  if (const MediaQueryExpNode* exp_node = parser.ParseCondition(value)) {
    condition_text_ = exp_node->Serialize();

    ContainerSelector selector(container_query_->Selector().Name(), *exp_node);
    container_query_ =
        MakeGarbageCollected<ContainerQuery>(std::move(selector), exp_node);
  }
}

=======
>>>>>>> chromium
void StyleRuleContainer::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(container_query_);
  StyleRuleCondition::TraceAfterDispatch(visitor);
}

StyleRuleViewport::StyleRuleViewport(CSSPropertyValueSet* properties)
    : StyleRuleBase(kViewport), properties_(properties) {}

<<<<<<< HEAD
void StyleRuleFunction::Parameter::Trace(blink::Visitor* visitor) const {
  visitor->Trace(default_value);
}

StyleRuleFunction::StyleRuleFunction(
    AtomicString name,
    HeapVector<StyleRuleFunction::Parameter> parameters,
    HeapVector<Member<StyleRuleBase>> child_rules,
    CSSSyntaxDefinition return_type)
    : StyleRuleGroup(kFunction, std::move(child_rules)),
      name_(std::move(name)),
      parameters_(std::move(parameters)),
      return_type_(return_type) {}

void StyleRuleFunction::TraceAfterDispatch(blink::Visitor* visitor) const {
  StyleRuleGroup::TraceAfterDispatch(visitor);
  visitor->Trace(parameters_);
=======
StyleRuleViewport::StyleRuleViewport(const StyleRuleViewport& viewport_rule)
    : StyleRuleBase(viewport_rule),
      properties_(viewport_rule.properties_->MutableCopy()) {}

MutableCSSPropertyValueSet& StyleRuleViewport::MutableProperties() {
  if (!properties_->IsMutable())
    properties_ = properties_->MutableCopy();
  return *To<MutableCSSPropertyValueSet>(properties_.Get());
>>>>>>> chromium
}

void StyleRuleViewport::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(properties_);
  StyleRuleBase::TraceAfterDispatch(visitor);
}

}  // namespace blink
