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

<<<<<<< HEAD
#include "base/memory/stack_allocated.h"
#ifdef UNSAFE_BUFFERS_BUILD
// TODO(crbug.com/351564777): Remove this and convert code to safer constructs.
#pragma allow_unsafe_buffers
#endif

=======
>>>>>>> chromium
#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_RULE_SET_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_RULE_SET_H_

#include "base/types/pass_key.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/css/css_keyframes_rule.h"
#include "third_party/blink/renderer/core/css/media_query_evaluator.h"
#include "third_party/blink/renderer/core/css/resolver/media_query_result.h"
#include "third_party/blink/renderer/core/css/rule_feature_set.h"
#include "third_party/blink/renderer/core/css/style_rule.h"
#include "third_party/blink/renderer/core/css/style_rule_counter_style.h"
#include "third_party/blink/renderer/platform/heap/collection_support/heap_linked_stack.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/forward.h"
#include "third_party/blink/renderer/platform/wtf/hash_map.h"
#include "third_party/blink/renderer/platform/wtf/size_assertions.h"

namespace blink {

using AddRuleFlags = unsigned;

enum AddRuleFlag {
  kRuleHasNoSpecialState = 0,
  kRuleHasDocumentSecurityOrigin = 1 << 0,
  kRuleIsVisitedDependent = 1 << 1,
};

// Some CSS properties do not apply to certain pseudo-elements, and need to be
// ignored when resolving styles.
enum class ValidPropertyFilter : unsigned {
  // All properties are valid. This is the common case.
  kNoFilter,
  // Defined in a ::cue pseudo-element scope. Only properties listed
  // in https://w3c.github.io/webvtt/#the-cue-pseudo-element are valid.
  kCue,
  // Defined in a ::first-letter pseudo-element scope. Only properties listed in
  // https://drafts.csswg.org/css-pseudo-4/#first-letter-styling are valid.
  kFirstLetter,
  // Defined in a ::first-line pseudo-element scope. Only properties listed in
  // https://drafts.csswg.org/css-pseudo-4/#first-line-styling are valid.
  kFirstLine,
  // Defined in a ::marker pseudo-element scope. Only properties listed in
  // https://drafts.csswg.org/css-pseudo-4/#marker-pseudo are valid.
  kMarker,
  // Defined in a highlight pseudo-element scope like ::selection and
  // ::target-text. Only properties listed in
  // https://drafts.csswg.org/css-pseudo-4/#highlight-styling are valid.
  kHighlight,
};

class CSSSelector;
class MediaQueryEvaluator;
class StyleSheetContents;

class MinimalRuleData {
  DISALLOW_NEW();

 public:
  MinimalRuleData(StyleRule* rule, unsigned selector_index, AddRuleFlags flags)
      : rule_(rule), selector_index_(selector_index), flags_(flags) {}

  void Trace(Visitor*) const;

  Member<StyleRule> rule_;
  unsigned selector_index_;
  AddRuleFlags flags_;
};

}  // namespace blink

WTF_ALLOW_MOVE_AND_INIT_WITH_MEM_FUNCTIONS(blink::MinimalRuleData)

namespace blink {

// This is a wrapper around a StyleRule, pointing to one of the N complex
// selectors in the StyleRule. This allows us to treat each selector
// independently but still tie them back to the original StyleRule. If multiple
// selectors from a single rule match the same element we can see that as one
// match for the rule. It computes some information about the wrapped selector
// and makes it accessible cheaply.
class CORE_EXPORT RuleData : public GarbageCollected<RuleData> {
 public:
  enum class Type {
    kNormal = 0,
    kExtended = 1,
    // Note that the above values are stored in a 1-bit field.
    // See RuleData::type_.
  };

  static RuleData* MaybeCreate(StyleRule*,
                               unsigned selector_index,
                               unsigned position,
                               AddRuleFlags,
                               const ContainerQuery*);

  RuleData(StyleRule*,
           unsigned selector_index,
           unsigned position,
<<<<<<< HEAD
           const StyleScope*,
           AddRuleFlags,
           Vector<uint16_t>& bloom_hash_backing);
=======
           AddRuleFlags);
>>>>>>> chromium

  bool IsExtended() const {
    return static_cast<Type>(type_) == Type::kExtended;
  }
  unsigned GetPosition() const { return position_; }
  StyleRule* Rule() const { return rule_; }
  const ContainerQuery* GetContainerQuery() const;
  const CSSSelector& Selector() const {
    return rule_->SelectorList().SelectorAt(selector_index_);
  }
  unsigned SelectorIndex() const { return selector_index_; }

  unsigned Specificity() const { return specificity_; }
  unsigned LinkMatchType() const { return link_match_type_; }
<<<<<<< HEAD
  ValidPropertyFilter GetValidPropertyFilter() const {
    return static_cast<ValidPropertyFilter>(valid_property_filter_);
  }

  // Member functions related to the descendant Bloom filter.
  const base::span<const uint16_t> DescendantSelectorIdentifierHashes(
      const Vector<uint16_t>& backing) const {
    return {backing.data() + bloom_hash_pos_, bloom_hash_size_};
  }
  void ComputeBloomFilterHashes(const StyleScope* style_scope,
                                Vector<uint16_t>& backing);
  void MovedToDifferentRuleSet(const Vector<uint16_t>& old_backing,
                               Vector<uint16_t>& new_backing,
                               unsigned new_position);
=======
  bool HasDocumentSecurityOrigin() const {
    return has_document_security_origin_;
  }
  ValidPropertyFilter GetValidPropertyFilter(
      bool is_matching_ua_rules = false) const {
    return is_matching_ua_rules
               ? ValidPropertyFilter::kNoFilter
               : static_cast<ValidPropertyFilter>(valid_property_filter_);
  }
  // Try to balance between memory usage (there can be lots of RuleData objects)
  // and good filtering performance.
  static const unsigned kMaximumIdentifierCount = 4;
  const unsigned* DescendantSelectorIdentifierHashes() const {
    return descendant_selector_identifier_hashes_;
  }
>>>>>>> chromium

  void Trace(Visitor*) const;
  void TraceAfterDispatch(blink::Visitor* visitor) const;

  // This number is picked fairly arbitrary. If lowered, be aware that there
  // might be sites and extensions using style rules with selector lists
  // exceeding the number of simple selectors to fit in this bitfield.
  // See https://crbug.com/312913 and https://crbug.com/704562
  static constexpr size_t kSelectorIndexBits = 13;

  // This number was picked fairly arbitrarily. We can probably lower it if we
  // need to. Some simple testing showed <100,000 RuleData's on large sites.
  static constexpr size_t kPositionBits = 18;

 protected:
  RuleData(Type type,
           StyleRule*,
           unsigned selector_index,
           unsigned position,
           AddRuleFlags);

 private:
  Member<StyleRule> rule_;
  unsigned selector_index_ : kSelectorIndexBits;
  unsigned position_ : kPositionBits;
  unsigned unused_bit_ : 1;
  // 31 bits above (1 free bit).
  unsigned specificity_ : 24;
  unsigned link_match_type_ : 2;
  unsigned has_document_security_origin_ : 1;
  unsigned valid_property_filter_ : 3;
  unsigned type_ : 1;  // RuleData::Type
  // 31 bits above
  // Use plain array instead of a Vector to minimize memory overhead.
  unsigned descendant_selector_identifier_hashes_[kMaximumIdentifierCount];
};

// Big websites can have a large number of RuleData objects (30k+). This class
// exists to avoid allocating unnecessary memory for "rare" fields.
class CORE_EXPORT ExtendedRuleData : public RuleData {
 public:
  // Do not create ExtendedRuleData objects directly; RuleData::MaybeCreate
  // will decide if ExtendedRuleData is needed or not.
  ExtendedRuleData(base::PassKey<RuleData>,
                   StyleRule*,
                   unsigned selector_index,
                   unsigned position,
                   AddRuleFlags,
                   const ContainerQuery*);
  void TraceAfterDispatch(Visitor*) const;

 private:
  friend class RuleData;

  Member<const ContainerQuery> container_query_;
};

template <>
struct DowncastTraits<ExtendedRuleData> {
  static bool AllowFrom(const RuleData& data) { return data.IsExtended(); }
};

}  // namespace blink

WTF_ALLOW_MOVE_AND_INIT_WITH_MEM_FUNCTIONS(blink::RuleData)

namespace blink {

struct SameSizeAsRuleData {
  DISALLOW_NEW();
  Member<void*> a;
  unsigned b;
  unsigned c;
  unsigned d[4];
};

ASSERT_SIZE(RuleData, SameSizeAsRuleData);

<<<<<<< HEAD
// A memory-efficient and (fairly) cache-efficient mapping from bucket key
// (e.g. CSS class, tag name, attribute key, etc.) to a collection of rules
// (RuleData objects). It uses a vector as backing storage, and generally works
// in two phases:
//
//  - During RuleSet setup (before compaction), we simply add rules to the
//    back of the vector, ie., the elements will be in a random order.
//  - Before rule matching, we need to _compact_ the rule map. This is done
//    by grouping/sorting the vector by bucket, so that everything that belongs
//    to the same vector lives together and can easily be picked out.
//
// The normal flow is that you first add all rules, call Compact(), then call
// Find() as many times as you need. (Compact() is a moderately expensive
// operation, which is why we don't want to be doing it too much.) However, in
// certain cases related to UA stylesheets, we may need to insert new rules
// on-the-fly (e.g., when seeing a <video> element for the first time, we
// insert additional rules related to it); if so, you need to call Uncompact()
// before adding them, then Compact() again.
class RuleMap {
  DISALLOW_NEW();

 private:
  // A collection of rules that are in the same bucket. Before compaction,
  // they are scattered around in the bucket vector; after compaction,
  // each bucket will be contiguous.
  struct Extent {
    Extent() : bucket_number(0) {}
    union {
      // [0..num_buckets). Valid before compaction.
      unsigned bucket_number;

      // Into the backing vector. Valid after compaction.
      unsigned start_index;
    };

    // How many rules are in this bucket. Will naturally not change
    // by compaction.
    wtf_size_t length = 0;
  };

 public:
  // Returns false on failure (which should be very rare).
  bool Add(const AtomicString& key, const RuleData& rule_data);
  void AddFilteredRulesFromOtherSet(
      const RuleMap& other,
      const HeapHashSet<Member<StyleRule>>& only_include,
      const RuleSet& old_rule_set,
      RuleSet& new_rule_set);
  base::span<const RuleData> Find(const AtomicString& key) const {
    // Go through all the buckets and check for equality, brute force.
    // Note that we don't check for IsNull() to get an early abort
    // on empty buckets; the comparison of AtomicString is so cheap
    // that it actually benchmarks negatively. This loop typically
    // gets unrolled and inlined, resulting in a very tight lookup.
    const RobinHoodMap<AtomicString, Extent>::Bucket* bucket =
        buckets.Find(key);
    if (bucket == nullptr) {
      return {};
    } else {
      return {backing.begin() + bucket->value.start_index,
              bucket->value.length};
    }
  }
  bool IsEmpty() const { return backing.empty(); }
  bool IsCompacted() const { return compacted; }

  void Compact();
  void Uncompact();

  void Trace(Visitor* visitor) const { visitor->Trace(backing); }

  struct ConstIterator {
    STACK_ALLOCATED();

   public:
    RobinHoodMap<AtomicString, Extent>::const_iterator sub_it;
    const RuleMap* rule_map;

    WTF::KeyValuePair<AtomicString, base::span<const RuleData>> operator*()
        const {
      return {sub_it->key, rule_map->GetRulesFromExtent(sub_it->value)};
    }
    bool operator==(const ConstIterator& other) const {
      DCHECK_EQ(rule_map, other.rule_map);
      return sub_it == other.sub_it;
    }
    bool operator!=(const ConstIterator& other) const {
      DCHECK_EQ(rule_map, other.rule_map);
      return sub_it != other.sub_it;
    }
    ConstIterator& operator++() {
      ++sub_it;
      return *this;
    }
  };
  ConstIterator begin() const { return {buckets.begin(), this}; }
  ConstIterator end() const { return {buckets.end(), this}; }

 private:
  base::span<RuleData> GetRulesFromExtent(Extent extent) {
    return {backing.begin() + extent.start_index, extent.length};
  }
  base::span<const RuleData> GetRulesFromExtent(Extent extent) const {
    return {backing.begin() + extent.start_index, extent.length};
  }
  base::span<unsigned> GetBucketNumberFromExtent(Extent extent) {
    return {bucket_number_.begin() + extent.start_index, extent.length};
  }
  base::span<const unsigned> GetBucketNumberFromExtent(Extent extent) const {
    return {bucket_number_.begin() + extent.start_index, extent.length};
  }

  RobinHoodMap<AtomicString, Extent> buckets;

  // Contains all the rules from all the buckets; after compaction,
  // they will be contiguous in memory and you can do easily lookups
  // on them through Find(); before, they are identified
  // by having the group number in bucket_data_.
  //
  // The inline size is, perhaps surprisingly, to reduce GC pressure
  // for _large_ vectors. Setting an inline size (other than zero)
  // causes Vector, and by extension HeapVector, to grow more
  // aggressively on push_back(), leading to fewer memory allocations
  // that need freeing. We call ShrinkToFit() on compaction, so the
  // excess increase (which would normally be the downside of this
  // strategy) is not a big problem for us.
  //
  // Of course, we also save a few allocations for the rule sets
  // that are tiny. Most RuleMaps are either ~1–2 entries or in
  // the hundreds/thousands.
  HeapVector<RuleData, 4> backing;

  // Used by RuleMap before compaction, to hold what bucket the corresponding
  // RuleData (by index) is to be sorted into (this member is 1:1 with backing).
  // After compaction, the vector is emptied to save memory.
  Vector<unsigned> bucket_number_;

  wtf_size_t num_buckets = 0;
  bool compacted = false;
};

=======
>>>>>>> chromium
// Holds RuleData objects. It partitions them into various indexed groups,
// e.g. it stores separately rules that match against id, class, tag, shadow
// host, etc. It indexes these by some key where possible, e.g. rules that match
// against tag name are indexed by that tag. Rules that don't fall into a
// specific group are appended to the "universal" rules. The grouping is done to
// optimize finding what rules apply to an element under consideration by
// ElementRuleCollector::CollectMatchingRules.
class CORE_EXPORT RuleSet final : public GarbageCollected<RuleSet> {
 public:
  RuleSet() : rule_count_(0) {}
  RuleSet(const RuleSet&) = delete;
  RuleSet& operator=(const RuleSet&) = delete;

  void AddRulesFromSheet(const StyleSheetContents*,
                         const MediaQueryEvaluator&,
<<<<<<< HEAD
                         CascadeLayer* = nullptr,
                         const StyleScope* = nullptr);

  // “within_mixin” means that we are currently adding this rule
  // as part of @apply in a mixin, and all rules we add must be
  // duplicated and reparented. This is also propagated through
  // AddChildRules().
  void AddStyleRule(StyleRule* style_rule,
                    StyleRule* parent_rule,
                    const MediaQueryEvaluator& medium,
                    AddRuleFlags add_rule_flags,
                    bool within_mixin,
                    const ContainerQuery* container_query = nullptr,
                    CascadeLayer* cascade_layer = nullptr,
                    const StyleScope* style_scope = nullptr);

  // Adds RuleDatas (and only RuleDatas) from the other set, but only if they
  // correspond to rules in “only_include”. This is used when creating diff
  // rulesets for invalidation, and the resulting RuleSets are not usable
  // for anything else. In particular, cascade layers are not copied
  // and RuleData offsets are not adjusted (so CascadePriority would be wrong
  // if merging RuleDatas from different RuleSets). This means that the only
  // thing you can really do with this RuleSet afterwards is
  // ElementRuleCollector's CheckIfAnyRuleMatches(); the regular
  // Collect*Rules() functions are bound to give you trouble.
  void AddFilteredRulesFromOtherSet(
      const RuleSet& other,
      const HeapHashSet<Member<StyleRule>>& only_include);

  void AddFilteredRulesFromOtherBucket(
      const RuleSet& other,
      const HeapVector<RuleData>& src,
      const HeapHashSet<Member<StyleRule>>& only_include,
      HeapVector<RuleData>* dst);
=======
                         AddRuleFlags = kRuleHasNoSpecialState);
  void AddStyleRule(StyleRule*, AddRuleFlags);
  void AddRule(StyleRule*,
               unsigned selector_index,
               AddRuleFlags,
               const ContainerQuery*);
>>>>>>> chromium

  const RuleFeatureSet& Features() const { return features_; }

  const HeapVector<Member<const RuleData>>* IdRules(
      const AtomicString& key) const {
    DCHECK(!pending_rules_);
    return id_rules_.at(key);
  }
  const HeapVector<Member<const RuleData>>* ClassRules(
      const AtomicString& key) const {
    DCHECK(!pending_rules_);
    return class_rules_.at(key);
  }
  const HeapVector<Member<const RuleData>>* TagRules(
      const AtomicString& key) const {
    DCHECK(!pending_rules_);
    return tag_rules_.at(key);
  }
  const HeapVector<Member<const RuleData>>* UAShadowPseudoElementRules(
      const AtomicString& key) const {
    DCHECK(!pending_rules_);
    return ua_shadow_pseudo_element_rules_.at(key);
  }
  const HeapVector<Member<const RuleData>>* LinkPseudoClassRules() const {
    DCHECK(!pending_rules_);
    return &link_pseudo_class_rules_;
  }
  const HeapVector<Member<const RuleData>>* CuePseudoRules() const {
    DCHECK(!pending_rules_);
    return &cue_pseudo_rules_;
  }
  const HeapVector<Member<const RuleData>>* FocusPseudoClassRules() const {
    DCHECK(!pending_rules_);
    return &focus_pseudo_class_rules_;
  }
  const HeapVector<Member<const RuleData>>* FocusVisiblePseudoClassRules()
      const {
    DCHECK(!pending_rules_);
    return &focus_visible_pseudo_class_rules_;
  }
  const HeapVector<Member<const RuleData>>*
  SpatialNavigationInterestPseudoClassRules() const {
    DCHECK(!pending_rules_);
    return &spatial_navigation_interest_class_rules_;
  }
  const HeapVector<Member<const RuleData>>* UniversalRules() const {
    DCHECK(!pending_rules_);
    return &universal_rules_;
  }
  const HeapVector<Member<const RuleData>>* ShadowHostRules() const {
    DCHECK(!pending_rules_);
    return &shadow_host_rules_;
  }
  const HeapVector<Member<const RuleData>>* PartPseudoRules() const {
    DCHECK(!pending_rules_);
    return &part_pseudo_rules_;
  }
  const HeapVector<Member<const RuleData>>* VisitedDependentRules() const {
    DCHECK(!pending_rules_);
    return &visited_dependent_rules_;
  }
  const HeapVector<Member<StyleRulePage>>& PageRules() const {
    DCHECK(!pending_rules_);
    return page_rules_;
  }
  const HeapVector<Member<StyleRuleFontFace>>& FontFaceRules() const {
    return font_face_rules_;
  }
  const HeapVector<Member<StyleRuleKeyframes>>& KeyframesRules() const {
    return keyframes_rules_;
  }
  const HeapVector<Member<StyleRuleProperty>>& PropertyRules() const {
    return property_rules_;
  }
  const HeapVector<Member<StyleRuleCounterStyle>>& CounterStyleRules() const {
    return counter_style_rules_;
  }
  const HeapVector<Member<StyleRuleScrollTimeline>>& ScrollTimelineRules()
      const {
    return scroll_timeline_rules_;
  }
  const HeapVector<MinimalRuleData>& SlottedPseudoElementRules() const {
    return slotted_pseudo_element_rules_;
  }

  unsigned RuleCount() const { return rule_count_; }

  void CompactRulesIfNeeded() {
    if (!pending_rules_)
      return;
    CompactRules();
  }

  void AssertCompacted() const { DCHECK(!need_compaction_); }

  bool HasSlottedRules() const {
    return !slotted_pseudo_element_rules_.IsEmpty();
  }

  bool NeedsFullRecalcForRuleSetInvalidation() const {
    return features_.NeedsFullRecalcForRuleSetInvalidation();
  }

  bool DidMediaQueryResultsChange(const MediaQueryEvaluator& evaluator) const;

<<<<<<< HEAD
  // We use a vector of Interval<T> to represent that rules with positions
  // between start_position (inclusive) and the next Interval<T>'s
  // start_position (exclusive) share some property:
  //
  //   - If T = CascadeLayer, belong to the given layer.
  //   - If T = ContainerQuery, are predicated on the given container query.
  //   - If T = StyleScope, are declared in the given @style scope.
  //
  // We do this instead of putting the data directly onto the RuleData,
  // because most rules don't need these fields and websites can have a large
  // number of RuleData objects (30k+). Since neighboring rules tend to have the
  // same values for these (often nullptr), we save memory and cache space at
  // the cost of a some extra seeking through these lists when matching rules.
  template <class T>
  class Interval {
    DISALLOW_NEW();

   public:
    Interval(const T* passed_value, unsigned passed_position)
        : value(passed_value), start_position(passed_position) {}
    const Member<const T> value;
    const unsigned start_position = 0;

    void Trace(Visitor*) const;
  };

  const HeapVector<Interval<CascadeLayer>>& LayerIntervals() const {
    return layer_intervals_;
  }
  const HeapVector<Interval<ContainerQuery>>& ContainerQueryIntervals() const {
    return container_query_intervals_;
  }
  const HeapVector<Interval<StyleScope>>& ScopeIntervals() const {
    return scope_intervals_;
  }
  const Vector<uint16_t>& BloomHashBacking() const {
    return bloom_hash_backing_;
  }

#if DCHECK_IS_ON()
=======
#ifndef NDEBUG
>>>>>>> chromium
  void Show() const;
#endif

  void Trace(Visitor*) const;

 private:
  using PendingRuleMap =
      HeapHashMap<AtomicString,
                  Member<HeapLinkedStack<Member<const RuleData>>>>;
  using CompactRuleMap =
      HeapHashMap<AtomicString, Member<HeapVector<Member<const RuleData>>>>;

  void AddToRuleSet(const AtomicString& key, PendingRuleMap&, const RuleData*);
  void AddPageRule(StyleRulePage*);
  void AddViewportRule(StyleRuleViewport*);
  void AddFontFaceRule(StyleRuleFontFace*);
  void AddKeyframesRule(StyleRuleKeyframes*);
  void AddPropertyRule(StyleRuleProperty*);
  void AddScrollTimelineRule(StyleRuleScrollTimeline*);
  void AddCounterStyleRule(StyleRuleCounterStyle*);

  bool MatchMediaForAddRules(const MediaQueryEvaluator& evaluator,
                             const MediaQuerySet* media_queries);
  void AddChildRules(const HeapVector<Member<StyleRuleBase>>&,
                     const MediaQueryEvaluator& medium,
                     AddRuleFlags,
<<<<<<< HEAD
                     const ContainerQuery*,
                     CascadeLayer*,
                     const StyleScope*,
                     bool within_mixin);

  // Determines whether or not CSSSelector::is_covered_by_bucketing_ should
  // be computed during calls to FindBestRuleSetAndAdd.
  enum class BucketCoverage {
    kIgnore,
    kCompute,
  };

  template <BucketCoverage bucket_coverage>
  void FindBestRuleSetAndAdd(CSSSelector&, const RuleData&, const StyleScope*);

  void AddRule(StyleRule*,
               unsigned selector_index,
               AddRuleFlags,
               const ContainerQuery*,
               const CascadeLayer*,
               const StyleScope*);

  // Must be called when a RuleData has been added to this RuleSet
  // through some form that does not go through AddRule();
  // used during creation of diff rulesets (AddFilteredRulesFromOtherSet()).
  // In particular, it will adjust the position of new_rule_data,
  // add it to the necessary intervals for diff rulesets, and adjust
  // rule_count_.
  //
  // Used only by RuleSet itself, and RuleMap (through a friend declaration).
  void NewlyAddedFromDifferentRuleSet(const RuleData& old_rule_data,
                                      const StyleScope* style_scope,
                                      const RuleSet& old_rule_set,
                                      RuleData& new_rule_data);
=======
                     const ContainerQuery*);
  bool FindBestRuleSetAndAdd(const CSSSelector&, RuleData*);
>>>>>>> chromium

  void SortKeyframesRulesIfNeeded();

  void CompactRules();
<<<<<<< HEAD
  static void CreateSubstringMatchers(
      RuleMap& attr_map,
      const HeapVector<Interval<StyleScope>>& scope_intervals,
      SubstringMatcherMap& substring_matcher_map);
=======
  static void CompactPendingRules(PendingRuleMap&, CompactRuleMap&);
>>>>>>> chromium

  class PendingRuleMaps : public GarbageCollected<PendingRuleMaps> {
   public:
    PendingRuleMaps() = default;

    PendingRuleMap id_rules;
    PendingRuleMap class_rules;
    PendingRuleMap tag_rules;
    PendingRuleMap ua_shadow_pseudo_element_rules;

    void Trace(Visitor*) const;
  };

  PendingRuleMaps* EnsurePendingRules() {
    if (!pending_rules_)
      pending_rules_ = MakeGarbageCollected<PendingRuleMaps>();
    return pending_rules_.Get();
  }

  CompactRuleMap id_rules_;
  CompactRuleMap class_rules_;
  CompactRuleMap tag_rules_;
  CompactRuleMap ua_shadow_pseudo_element_rules_;
  HeapVector<Member<const RuleData>> link_pseudo_class_rules_;
  HeapVector<Member<const RuleData>> cue_pseudo_rules_;
  HeapVector<Member<const RuleData>> focus_pseudo_class_rules_;
  HeapVector<Member<const RuleData>> focus_visible_pseudo_class_rules_;
  HeapVector<Member<const RuleData>> spatial_navigation_interest_class_rules_;
  HeapVector<Member<const RuleData>> universal_rules_;
  HeapVector<Member<const RuleData>> shadow_host_rules_;
  HeapVector<Member<const RuleData>> part_pseudo_rules_;
  HeapVector<Member<const RuleData>> visited_dependent_rules_;
  RuleFeatureSet features_;
  HeapVector<Member<StyleRulePage>> page_rules_;
  HeapVector<Member<StyleRuleFontFace>> font_face_rules_;
  HeapVector<Member<StyleRuleKeyframes>> keyframes_rules_;
  HeapVector<Member<StyleRuleProperty>> property_rules_;
  HeapVector<Member<StyleRuleCounterStyle>> counter_style_rules_;
  HeapVector<Member<StyleRuleScrollTimeline>> scroll_timeline_rules_;
  HeapVector<MinimalRuleData> slotted_pseudo_element_rules_;
  Vector<MediaQuerySetResult> media_query_set_results_;

  unsigned rule_count_;
  Member<PendingRuleMaps> pending_rules_;

<<<<<<< HEAD
  // Whether we need to check the universal bucket for rules when calculating
  // style for the shadow host. There are two reasons why this may need to
  // be checked:
  //
  // 1. Since the :scope pseudo-class can match a shadow host when that host
  //    is the scoping root,
  //    ElementRuleCollector::CollectMatchingShadowHostRules also needs to
  //    collect rules from the universal bucket, but this is only required when
  //    :scope is actually present.
  //
  // 2. Combination rules such as :is(:host, .foo) will be bucketed into the
  //    universal bucket and not into the bucket for :host. If this happens,
  //    we will need to check the universal bucket, too.
  //
  // Nothing else in the universal bucket can match the host from inside
  // the shadow tree.
  bool must_check_universal_bucket_for_shadow_host_ = false;

  unsigned rule_count_ = 0;
  bool need_compaction_ = false;

  // nullptr if the stylesheet doesn't explicitly declare any layer.
  Member<CascadeLayer> implicit_outer_layer_;
  // Empty vector if the stylesheet doesn't explicitly declare any layer.
  HeapVector<Interval<CascadeLayer>> layer_intervals_;
  // Empty vector if the stylesheet doesn't use any container queries.
  HeapVector<Interval<ContainerQuery>> container_query_intervals_;
  // Empty vector if the stylesheet doesn't use any @scopes.
  HeapVector<Interval<StyleScope>> scope_intervals_;

  // Backing store for the Bloom filter hashes for each RuleData.
  // It is stored here so that we can have a variable number of them
  // (without the overhead of a Vector in each RuleData).
  Vector<uint16_t> bloom_hash_backing_;

#if DCHECK_IS_ON()
  HeapVector<RuleData> all_rules_;

  // If true, we don't DCHECK that these are unsorted, since they
  // came from merged+filtered rulesets, which only happens when
  // making diff rulesets for invalidation. Those do not care
  // about the ordering, since they do not use the CascadeLayerSeeker.
  bool allow_unsorted_ = false;
#endif  // DCHECK_IS_ON()
=======
#ifndef NDEBUG
  HeapVector<Member<const RuleData>> all_rules_;
#endif
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_RULE_SET_H_
