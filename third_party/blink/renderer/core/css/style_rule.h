/*
 * (C) 1999-2003 Lars Knoll (knoll@kde.org)
 * (C) 2002-2003 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2002, 2006, 2008, 2012, 2013 Apple Inc. All rights reserved.
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

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_STYLE_RULE_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_STYLE_RULE_H_

#include "base/memory/scoped_refptr.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/css/container_query.h"
#include "third_party/blink/renderer/core/css/css_property_value_set.h"
#include "third_party/blink/renderer/core/css/css_selector_list.h"
#include "third_party/blink/renderer/core/css/media_list.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/css/parser/css_at_rule_id.h"
#include "third_party/blink/renderer/core/css/parser/css_lazy_property_parser.h"
#include "third_party/blink/renderer/core/css/parser/css_nesting_type.h"
#include "third_party/blink/renderer/core/css/style_scope.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
=======
#include "third_party/blink/renderer/platform/heap/handle.h"
>>>>>>> chromium
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace blink {

class CSSRule;
class CSSStyleSheet;
<<<<<<< HEAD
class ExecutionContext;
=======
>>>>>>> chromium

class CORE_EXPORT StyleRuleBase : public GarbageCollected<StyleRuleBase> {
 public:
  enum RuleType {
    kCharset,
    kStyle,
    kImport,
    kMedia,
    kFontFace,
    kPage,
    kProperty,
    kKeyframes,
    kKeyframe,
<<<<<<< HEAD
    kLayerBlock,
    kLayerStatement,
    kNestedDeclarations,
    kFunctionDeclarations,
=======
>>>>>>> chromium
    kNamespace,
    kContainer,
    kCounterStyle,
    kScrollTimeline,
    kSupports,
    kViewport,
  };

  RuleType GetType() const { return static_cast<RuleType>(type_); }

  bool IsCharsetRule() const { return GetType() == kCharset; }
  bool IsContainerRule() const { return GetType() == kContainer; }
  bool IsCounterStyleRule() const { return GetType() == kCounterStyle; }
  bool IsFontFaceRule() const { return GetType() == kFontFace; }
  bool IsKeyframesRule() const { return GetType() == kKeyframes; }
  bool IsKeyframeRule() const { return GetType() == kKeyframe; }
<<<<<<< HEAD
  bool IsLayerBlockRule() const { return GetType() == kLayerBlock; }
  bool IsLayerStatementRule() const { return GetType() == kLayerStatement; }
  bool IsFunctionDeclarationsRule() const {
    return GetType() == kFunctionDeclarations;
  }
  bool IsNestedDeclarationsRule() const {
    return GetType() == kNestedDeclarations;
  }
=======
>>>>>>> chromium
  bool IsNamespaceRule() const { return GetType() == kNamespace; }
  bool IsMediaRule() const { return GetType() == kMedia; }
  bool IsPageRule() const { return GetType() == kPage; }
  bool IsPropertyRule() const { return GetType() == kProperty; }
  bool IsStyleRule() const { return GetType() == kStyle; }
  bool IsScrollTimelineRule() const { return GetType() == kScrollTimeline; }
  bool IsSupportsRule() const { return GetType() == kSupports; }
  bool IsViewportRule() const { return GetType() == kViewport; }
  bool IsImportRule() const { return GetType() == kImport; }

  StyleRuleBase* Copy() const;

  // FIXME: There shouldn't be any need for the null parent version.
<<<<<<< HEAD
  CSSRule* CreateCSSOMWrapper(
      wtf_size_t position_hint = std::numeric_limits<wtf_size_t>::max(),
      CSSStyleSheet* parent_sheet = nullptr,
      bool trigger_use_counters = false) const;
  CSSRule* CreateCSSOMWrapper(wtf_size_t position_hint,
                              CSSRule* parent_rule,
                              bool trigger_use_counters = false) const;

  // See CSSSelector::Renest.
  StyleRuleBase* Renest(StyleRule* new_parent);
=======
  CSSRule* CreateCSSOMWrapper(CSSStyleSheet* parent_sheet = nullptr) const;
  CSSRule* CreateCSSOMWrapper(CSSRule* parent_rule) const;
>>>>>>> chromium

  void Trace(Visitor*) const;
  void TraceAfterDispatch(blink::Visitor* visitor) const {}
  void FinalizeGarbageCollectedObject();

  // ~StyleRuleBase should be public, because non-public ~StyleRuleBase
  // causes C2248 error : 'blink::StyleRuleBase::~StyleRuleBase' : cannot
  // access protected member declared in class 'blink::StyleRuleBase' when
  // compiling 'source\wtf\refcounted.h' by using msvc.
  ~StyleRuleBase() = default;

 protected:
  StyleRuleBase(RuleType type) : type_(type) {}
  StyleRuleBase(const StyleRuleBase& rule) : type_(rule.type_) {}

 private:
  CSSRule* CreateCSSOMWrapper(CSSStyleSheet* parent_sheet,
                              CSSRule* parent_rule) const;

  const uint8_t type_;
};

// A single rule from a stylesheet. Contains a selector list (one or more
// complex selectors) and a collection of style properties to be applied where
// those selectors match. These are output by CSSParserImpl.
class CORE_EXPORT StyleRule : public StyleRuleBase {
 public:
  // Adopts the selector list
  StyleRule(CSSSelectorList, CSSPropertyValueSet*);
  StyleRule(CSSSelectorList, CSSLazyPropertyParser*);
  StyleRule(const StyleRule&);
  ~StyleRule();

  const CSSSelectorList& SelectorList() const { return selector_list_; }
  const CSSPropertyValueSet& Properties() const;
  MutableCSSPropertyValueSet& MutableProperties();

  void WrapperAdoptSelectorList(CSSSelectorList selectors) {
    selector_list_ = std::move(selectors);
  }

  StyleRule* Copy() const { return MakeGarbageCollected<StyleRule>(*this); }

  static unsigned AverageSizeInBytes();

  // Helper methods to avoid parsing lazy properties when not needed.
  bool PropertiesHaveFailedOrCanceledSubresources() const;
  bool ShouldConsiderForMatchingRules(bool include_empty_rules) const;

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  friend class CSSLazyParsingTest;
  bool HasParsedProperties() const;

  // Whether or not we should consider this for matching rules. Usually we try
  // to avoid considering empty property sets, as an optimization. This is
  // not possible for lazy properties, which always need to be considered. The
  // lazy parser does its best to avoid lazy parsing for properties that look
  // empty due to lack of tokens.
  enum ConsiderForMatching {
    kAlwaysConsider,
    kConsiderIfNonEmpty,
  };
  mutable ConsiderForMatching should_consider_for_matching_rules_;

  CSSSelectorList selector_list_;
  mutable Member<CSSPropertyValueSet> properties_;
  mutable Member<CSSLazyPropertyParser> lazy_property_parser_;
};

class CORE_EXPORT StyleRuleFontFace : public StyleRuleBase {
 public:
  StyleRuleFontFace(CSSPropertyValueSet*);
  StyleRuleFontFace(const StyleRuleFontFace&);

  const CSSPropertyValueSet& Properties() const { return *properties_; }
  MutableCSSPropertyValueSet& MutableProperties();

  StyleRuleFontFace* Copy() const {
    return MakeGarbageCollected<StyleRuleFontFace>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  Member<CSSPropertyValueSet> properties_;  // Cannot be null.
};

class StyleRulePage : public StyleRuleBase {
 public:
  StyleRulePage(CSSSelectorList, CSSPropertyValueSet*);
  StyleRulePage(const StyleRulePage&);
  ~StyleRulePage();

  const CSSSelector* Selector() const { return selector_list_.First(); }
  const CSSPropertyValueSet& Properties() const { return *properties_; }
  MutableCSSPropertyValueSet& MutableProperties();

  void WrapperAdoptSelectorList(CSSSelectorList selectors) {
    selector_list_ = std::move(selectors);
  }

  StyleRulePage* Copy() const {
    return MakeGarbageCollected<StyleRulePage>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  Member<CSSPropertyValueSet> properties_;  // Cannot be null.
  CSSSelectorList selector_list_;
};

class CORE_EXPORT StyleRuleProperty : public StyleRuleBase {
 public:
  StyleRuleProperty(const String& name, CSSPropertyValueSet*);
  StyleRuleProperty(const StyleRuleProperty&);
  ~StyleRuleProperty();

  const CSSPropertyValueSet& Properties() const { return *properties_; }
  MutableCSSPropertyValueSet& MutableProperties();
  const String& GetName() const { return name_; }
  const CSSValue* GetSyntax() const;
  const CSSValue* Inherits() const;
  const CSSValue* GetInitialValue() const;

  StyleRuleProperty* Copy() const {
    return MakeGarbageCollected<StyleRuleProperty>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  String name_;
  Member<CSSPropertyValueSet> properties_;
};

class CORE_EXPORT StyleRuleScrollTimeline : public StyleRuleBase {
 public:
  StyleRuleScrollTimeline(const String& name, const CSSPropertyValueSet*);
  StyleRuleScrollTimeline(const StyleRuleScrollTimeline&) = default;
  ~StyleRuleScrollTimeline();

  StyleRuleScrollTimeline* Copy() const {
    return MakeGarbageCollected<StyleRuleScrollTimeline>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

  const AtomicString& GetName() const { return name_; }
  const CSSValue* GetSource() const { return source_; }
  const CSSValue* GetOrientation() const { return orientation_; }
  const CSSValue* GetStart() const { return start_; }
  const CSSValue* GetEnd() const { return end_; }
  const CSSValue* GetTimeRange() const { return time_range_; }

 private:
  AtomicString name_;
  Member<const CSSValue> source_;
  Member<const CSSValue> orientation_;
  Member<const CSSValue> start_;
  Member<const CSSValue> end_;
  Member<const CSSValue> time_range_;
};

class CORE_EXPORT StyleRuleGroup : public StyleRuleBase {
 public:
  const HeapVector<Member<StyleRuleBase>>& ChildRules() const {
    return child_rules_;
  }

  void WrapperInsertRule(unsigned, StyleRuleBase*);
  void WrapperRemoveRule(unsigned);

  void TraceAfterDispatch(blink::Visitor*) const;

 protected:
  StyleRuleGroup(RuleType, HeapVector<Member<StyleRuleBase>>& adopt_rule);
  StyleRuleGroup(const StyleRuleGroup&);

 private:
  HeapVector<Member<StyleRuleBase>> child_rules_;
};

<<<<<<< HEAD
class CORE_EXPORT StyleRuleScope : public StyleRuleGroup {
 public:
  StyleRuleScope(const StyleScope&, HeapVector<Member<StyleRuleBase>> rules);
  StyleRuleScope(const StyleRuleScope&);

  StyleRuleScope* Copy() const {
    return MakeGarbageCollected<StyleRuleScope>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

  const StyleScope& GetStyleScope() const { return *style_scope_; }

 private:
  Member<const StyleScope> style_scope_;
};

// https://www.w3.org/TR/css-cascade-5/#layer-block
class CORE_EXPORT StyleRuleLayerBlock : public StyleRuleGroup {
 public:
  StyleRuleLayerBlock(LayerName name, HeapVector<Member<StyleRuleBase>> rules);
  StyleRuleLayerBlock(const StyleRuleLayerBlock&);
  StyleRuleLayerBlock(const StyleRuleLayerBlock&,
                      HeapVector<Member<StyleRuleBase>> rules);

  const LayerName& GetName() const { return name_; }
  String GetNameAsString() const;

  StyleRuleLayerBlock* Copy() const {
    return MakeGarbageCollected<StyleRuleLayerBlock>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  LayerName name_;
};

// https://www.w3.org/TR/css-cascade-5/#layer-empty
class CORE_EXPORT StyleRuleLayerStatement : public StyleRuleBase {
 public:
  explicit StyleRuleLayerStatement(Vector<LayerName>&& names);
  StyleRuleLayerStatement(const StyleRuleLayerStatement& other);

  const Vector<LayerName>& GetNames() const { return names_; }
  Vector<String> GetNamesAsStrings() const;

  StyleRuleLayerStatement* Copy() const {
    return MakeGarbageCollected<StyleRuleLayerStatement>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  Vector<LayerName> names_;
};

class StyleRulePage : public StyleRuleGroup {
 public:
  StyleRulePage(CSSSelectorList* selector_list,
                CSSPropertyValueSet* properties,
                HeapVector<Member<StyleRuleBase>> child_rules);
  StyleRulePage(const StyleRulePage&);

  const CSSSelector* Selector() const { return selector_list_->First(); }
  const CSSPropertyValueSet& Properties() const { return *properties_; }
  MutableCSSPropertyValueSet& MutableProperties();

  void WrapperAdoptSelectorList(CSSSelectorList* selectors) {
    selector_list_ = selectors;
  }

  StyleRulePage* Copy() const {
    return MakeGarbageCollected<StyleRulePage>(*this);
  }

  void SetCascadeLayer(const CascadeLayer* layer) { layer_ = layer; }
  const CascadeLayer* GetCascadeLayer() const { return layer_.Get(); }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  Member<CSSPropertyValueSet> properties_;  // Cannot be null.
  Member<const CascadeLayer> layer_;
  Member<CSSSelectorList> selector_list_;
};

class StyleRulePageMargin : public StyleRuleBase {
 public:
  StyleRulePageMargin(CSSAtRuleID id, CSSPropertyValueSet* properties);
  StyleRulePageMargin(const StyleRulePageMargin&);

  const CSSPropertyValueSet& Properties() const { return *properties_; }
  MutableCSSPropertyValueSet& MutableProperties();
  CSSAtRuleID ID() const { return id_; }

  StyleRulePageMargin* Copy() const {
    return MakeGarbageCollected<StyleRulePageMargin>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  CSSAtRuleID id_;                          // What margin, e.g. @top-right.
  Member<CSSPropertyValueSet> properties_;  // Cannot be null.
};

// If you add new children of this class, remember to update IsConditionRule()
// above.
=======
>>>>>>> chromium
class CORE_EXPORT StyleRuleCondition : public StyleRuleGroup {
 public:
  String ConditionText() const { return condition_text_; }

  void TraceAfterDispatch(blink::Visitor* visitor) const {
    StyleRuleGroup::TraceAfterDispatch(visitor);
  }

 protected:
  StyleRuleCondition(RuleType, HeapVector<Member<StyleRuleBase>>& adopt_rule);
  StyleRuleCondition(RuleType,
                     const String& condition_text,
                     HeapVector<Member<StyleRuleBase>>& adopt_rule);
  StyleRuleCondition(const StyleRuleCondition&);
  String condition_text_;
};

class CORE_EXPORT StyleRuleMedia : public StyleRuleCondition {
 public:
<<<<<<< HEAD
  StyleRuleMedia(const MediaQuerySet*, HeapVector<Member<StyleRuleBase>> rules);
  StyleRuleMedia(const StyleRuleMedia&) = default;
  StyleRuleMedia(const StyleRuleMedia&,
                 HeapVector<Member<StyleRuleBase>> rules);
=======
  StyleRuleMedia(scoped_refptr<MediaQuerySet>,
                 HeapVector<Member<StyleRuleBase>>& adopt_rules);
  StyleRuleMedia(const StyleRuleMedia&);
>>>>>>> chromium

  MediaQuerySet* MediaQueries() const { return media_queries_.get(); }

  StyleRuleMedia* Copy() const {
    return MakeGarbageCollected<StyleRuleMedia>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  scoped_refptr<MediaQuerySet> media_queries_;
};

class StyleRuleSupports : public StyleRuleCondition {
 public:
  StyleRuleSupports(const String& condition_text,
                    bool condition_is_supported,
                    HeapVector<Member<StyleRuleBase>>& adopt_rules);
  StyleRuleSupports(const StyleRuleSupports&);
  StyleRuleSupports(const StyleRuleSupports&,
                    HeapVector<Member<StyleRuleBase>> rules);

  bool ConditionIsSupported() const { return condition_is_supported_; }
  StyleRuleSupports* Copy() const {
    return MakeGarbageCollected<StyleRuleSupports>(*this);
  }

  void TraceAfterDispatch(blink::Visitor* visitor) const {
    StyleRuleCondition::TraceAfterDispatch(visitor);
  }

 private:
  String condition_text_;
  bool condition_is_supported_;
};

class CORE_EXPORT StyleRuleContainer : public StyleRuleCondition {
 public:
  StyleRuleContainer(ContainerQuery&,
                     HeapVector<Member<StyleRuleBase>>& adopt_rules);
  StyleRuleContainer(const StyleRuleContainer&);
  StyleRuleContainer(const StyleRuleContainer&,
                     HeapVector<Member<StyleRuleBase>> rules);

  ContainerQuery& GetContainerQuery() const { return *container_query_; }

  StyleRuleContainer* Copy() const {
    return MakeGarbageCollected<StyleRuleContainer>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  Member<ContainerQuery> container_query_;
};

class StyleRuleViewport : public StyleRuleBase {
 public:
  explicit StyleRuleViewport(CSSPropertyValueSet*);
  explicit StyleRuleViewport(const StyleRuleViewport&);

  const CSSPropertyValueSet& Properties() const { return *properties_; }
  MutableCSSPropertyValueSet& MutableProperties();

  StyleRuleViewport* Copy() const {
    return MakeGarbageCollected<StyleRuleViewport>(*this);
  }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  Member<CSSPropertyValueSet> properties_;  // Cannot be null
};

// This should only be used within the CSS Parser
class StyleRuleCharset : public StyleRuleBase {
 public:
  StyleRuleCharset() : StyleRuleBase(kCharset) {}
  void TraceAfterDispatch(blink::Visitor* visitor) const {
    StyleRuleBase::TraceAfterDispatch(visitor);
  }

 private:
};

<<<<<<< HEAD
// An @function rule, representing a CSS function.
class CORE_EXPORT StyleRuleFunction : public StyleRuleGroup {
 public:
  struct Parameter {
    DISALLOW_NEW();

   public:
    void Trace(blink::Visitor*) const;

    String name;
    CSSSyntaxDefinition type;
    Member<CSSVariableData> default_value;
  };

  // The body of the function is represented by `child_rules`.
  // Each child rule is either a CSSNestedDeclarations rule (holding
  // descriptors, like 'result' and local variables), or a conditional rule,
  // such as @media.
  //
  // The example below has three child rules: a CSSNestedDeclarations rule
  // holding `--x`, an @media rule, and another CSSNestedDeclarations rule
  // holding `results`.
  //
  //   @function --foo() {
  //     --x: 10px;
  //     @media (width > 100px) {
  //       --x: 20x;
  //     }
  //     result: var(--x);
  //   }
  //
  // Note: Although StyleRuleFunction itself can accommodate conditional rules,
  // it's not yet supported by parsing/evaluation.
  //
  // TODO(crbug.com/325504770): Support parsing/evaluation of conditionals.
  StyleRuleFunction(AtomicString name,
                    HeapVector<Parameter> parameters,
                    HeapVector<Member<StyleRuleBase>> child_rules,
                    CSSSyntaxDefinition return_type);
  StyleRuleFunction(const StyleRuleFunction&) = delete;

  const AtomicString& GetName() const { return name_; }
  const HeapVector<Parameter>& GetParameters() const { return parameters_; }
  const CSSSyntaxDefinition& GetReturnType() const { return return_type_; }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  AtomicString name_;
  HeapVector<Parameter> parameters_;
  CSSSyntaxDefinition return_type_;
};

// An @mixin rule, representing a CSS mixin. We store all of the rules
// and declarations under a dummy rule that serves as the parent;
// when @apply comes, we clone all the children below that rule and
// reparent them into the point of @apply.
class CORE_EXPORT StyleRuleMixin : public StyleRuleBase {
 public:
  StyleRuleMixin(AtomicString name, StyleRule* fake_parent_rule);
  StyleRuleMixin(const StyleRuleMixin&) = delete;

  const AtomicString& GetName() const { return name_; }
  StyleRule& FakeParentRule() const { return *fake_parent_rule_; }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  AtomicString name_;
  Member<StyleRule> fake_parent_rule_;
};

// An @apply rule, representing applying a mixin.
class CORE_EXPORT StyleRuleApplyMixin : public StyleRuleBase {
 public:
  explicit StyleRuleApplyMixin(AtomicString name);
  StyleRuleApplyMixin(const StyleRuleMixin&) = delete;

  const AtomicString& GetName() const { return name_; }

  void TraceAfterDispatch(blink::Visitor*) const;

 private:
  AtomicString name_;
};

=======
>>>>>>> chromium
template <>
struct DowncastTraits<StyleRule> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsStyleRule();
  }
};

template <>
struct DowncastTraits<StyleRuleFontFace> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsFontFaceRule();
  }
};

template <>
struct DowncastTraits<StyleRulePage> {
  static bool AllowFrom(const StyleRuleBase& rule) { return rule.IsPageRule(); }
};

template <>
struct DowncastTraits<StyleRuleProperty> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsPropertyRule();
  }
};

template <>
struct DowncastTraits<StyleRuleScrollTimeline> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsScrollTimelineRule();
  }
};

template <>
struct DowncastTraits<StyleRuleGroup> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsMediaRule() || rule.IsSupportsRule() ||
           rule.IsContainerRule();
  }
};

template <>
struct DowncastTraits<StyleRuleMedia> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsMediaRule();
  }
};

template <>
struct DowncastTraits<StyleRuleSupports> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsSupportsRule();
  }
};

template <>
struct DowncastTraits<StyleRuleContainer> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsContainerRule();
  }
};

template <>
struct DowncastTraits<StyleRuleViewport> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsViewportRule();
  }
};

template <>
struct DowncastTraits<StyleRuleCharset> {
  static bool AllowFrom(const StyleRuleBase& rule) {
    return rule.IsCharsetRule();
  }
};

}  // namespace blink

WTF_ALLOW_CLEAR_UNUSED_SLOTS_WITH_MEM_FUNCTIONS(
    blink::StyleRuleFunction::Parameter)

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_STYLE_RULE_H_
