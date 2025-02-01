/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 2004-2005 Allan Sandfeld Jensen (kde@carewolf.com)
 * Copyright (C) 2006, 2007 Nicholas Shanks (webkit@nickshanks.com)
 * Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012 Apple Inc. All
 * rights reserved.
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

#include "third_party/blink/renderer/core/css/rule_set.h"

#include <type_traits>

#include "third_party/blink/renderer/core/css/css_font_selector.h"
#include "third_party/blink/renderer/core/css/css_selector.h"
#include "third_party/blink/renderer/core/css/css_selector_list.h"
#include "third_party/blink/renderer/core/css/selector_filter.h"
#include "third_party/blink/renderer/core/css/style_rule_import.h"
#include "third_party/blink/renderer/core/css/style_sheet_contents.h"
#include "third_party/blink/renderer/core/html/shadow/shadow_element_names.h"
#include "third_party/blink/renderer/core/html/track/text_track_cue.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/trace_event.h"
#include "third_party/blink/renderer/platform/weborigin/security_origin.h"

namespace blink {

static inline ValidPropertyFilter DetermineValidPropertyFilter(
    const AddRuleFlags add_rule_flags,
    const CSSSelector& selector) {
  for (const CSSSelector* component = &selector; component;
       component = component->TagHistory()) {
    if (component->Match() == CSSSelector::kPseudoElement &&
        component->Value() == TextTrackCue::CueShadowPseudoId()) {
      return ValidPropertyFilter::kCue;
    }
    switch (component->GetPseudoType()) {
      case CSSSelector::kPseudoCue:
        return ValidPropertyFilter::kCue;
      case CSSSelector::kPseudoFirstLetter:
        return ValidPropertyFilter::kFirstLetter;
      case CSSSelector::kPseudoFirstLine:
        return ValidPropertyFilter::kFirstLine;
      case CSSSelector::kPseudoMarker:
        return ValidPropertyFilter::kMarker;
      case CSSSelector::kPseudoSelection:
      case CSSSelector::kPseudoTargetText:
        return ValidPropertyFilter::kHighlight;
      default:
        break;
    }
  }
  return ValidPropertyFilter::kNoFilter;
}

static unsigned DetermineLinkMatchType(const AddRuleFlags add_rule_flags,
                                       const CSSSelector& selector) {
  if (selector.HasLinkOrVisited()) {
    return (add_rule_flags & kRuleIsVisitedDependent)
               ? CSSSelector::kMatchVisited
               : CSSSelector::kMatchLink;
  }
  return CSSSelector::kMatchAll;
}

RuleData* RuleData::MaybeCreate(StyleRule* rule,
                                unsigned selector_index,
                                unsigned position,
                                AddRuleFlags add_rule_flags,
                                const ContainerQuery* container_query) {
  // The selector index field in RuleData is only 13 bits so we can't support
  // selectors at index 8192 or beyond.
  // See https://crbug.com/804179
  if (selector_index >= (1 << RuleData::kSelectorIndexBits))
    return nullptr;
  if (position >= (1 << RuleData::kPositionBits))
    return nullptr;
  if (container_query) {
    return MakeGarbageCollected<ExtendedRuleData>(
        base::PassKey<RuleData>(), rule, selector_index, position,
        add_rule_flags, container_query);
  }
  return MakeGarbageCollected<RuleData>(rule, selector_index, position,
                                        add_rule_flags);
}

RuleData::RuleData(StyleRule* rule,
                   unsigned selector_index,
                   unsigned position,
<<<<<<< HEAD
                   const StyleScope* style_scope,
                   AddRuleFlags add_rule_flags,
                   Vector<uint16_t>& bloom_hash_backing)
=======
                   AddRuleFlags add_rule_flags)
    : RuleData(Type::kNormal, rule, selector_index, position, add_rule_flags) {}

RuleData::RuleData(Type type,
                   StyleRule* rule,
                   unsigned selector_index,
                   unsigned position,
                   AddRuleFlags add_rule_flags)
>>>>>>> chromium
    : rule_(rule),
      selector_index_(selector_index),
      position_(position),
      specificity_(Selector().Specificity()),
      link_match_type_(DetermineLinkMatchType(add_rule_flags, Selector())),
      has_document_security_origin_(add_rule_flags &
                                    kRuleHasDocumentSecurityOrigin),
      valid_property_filter_(
          static_cast<std::underlying_type_t<ValidPropertyFilter>>(
              DetermineValidPropertyFilter(add_rule_flags, Selector()))),
<<<<<<< HEAD
      is_entirely_covered_by_bucketing_(
          false),  // Will be computed in ComputeEntirelyCoveredByBucketing().
      is_easy_(false),  // Ditto.
      is_starting_style_((add_rule_flags & kRuleIsStartingStyle) != 0),
      bloom_hash_size_(0),
      bloom_hash_pos_(0) {
  ComputeBloomFilterHashes(style_scope, bloom_hash_backing);
}

void RuleData::ComputeEntirelyCoveredByBucketing() {
  is_easy_ = EasySelectorChecker::IsEasy(&Selector());
  is_entirely_covered_by_bucketing_ = true;
  for (const CSSSelector* selector = &Selector(); selector;
       selector = selector->NextSimpleSelector()) {
    if (!selector->IsCoveredByBucketing()) {
      is_entirely_covered_by_bucketing_ = false;
      break;
    }
  }
}

void RuleData::ResetEntirelyCoveredByBucketing() {
  for (CSSSelector* selector = &MutableSelector(); selector;
       selector = selector->NextSimpleSelector()) {
    selector->SetCoveredByBucketing(false);
    if (selector->Relation() != CSSSelector::kSubSelector) {
      break;
    }
  }
  is_entirely_covered_by_bucketing_ = false;
}

void RuleData::ComputeBloomFilterHashes(const StyleScope* style_scope,
                                        Vector<uint16_t>& bloom_hash_backing) {
  if (bloom_hash_backing.size() >= 16777216) {
    // This won't fit into bloom_hash_pos_, so don't collect any hashes.
    return;
  }
  bloom_hash_pos_ = bloom_hash_backing.size();
  SelectorFilter::CollectIdentifierHashes(Selector(), style_scope,
                                          bloom_hash_backing);

  // The clamp here is purely for safety; a real rule would never have
  // as many as 255 descendant selectors.
  bloom_hash_size_ =
      std::min<uint32_t>(bloom_hash_backing.size() - bloom_hash_pos_, 255);

  // If we've already got the exact same set of hashes in the vector,
  // we can simply reuse those, saving a bit of memory and cache space.
  // We only check the trivial case of a tail match; we could go with
  // something like a full suffix tree solution, but this is simple and
  // captures most of the benefits. (It is fairly common, especially with
  // nesting, to have the same sets of parents in consecutive rules.)
  if (bloom_hash_size_ > 0 && bloom_hash_pos_ >= bloom_hash_size_ &&
      std::equal(
          bloom_hash_backing.begin() + bloom_hash_pos_ - bloom_hash_size_,
          bloom_hash_backing.begin() + bloom_hash_pos_,
          bloom_hash_backing.begin() + bloom_hash_pos_)) {
    bloom_hash_backing.resize(bloom_hash_pos_);
    bloom_hash_pos_ -= bloom_hash_size_;
  }
}

void RuleData::MovedToDifferentRuleSet(const Vector<uint16_t>& old_backing,
                                       Vector<uint16_t>& new_backing,
                                       unsigned new_position) {
  unsigned new_pos = new_backing.size();
  new_backing.insert(new_backing.size(), old_backing.data() + bloom_hash_pos_,
                     bloom_hash_size_);
  bloom_hash_pos_ = new_pos;
  position_ = new_position;
=======
      type_(static_cast<unsigned>(type)),
      descendant_selector_identifier_hashes_() {
  SelectorFilter::CollectIdentifierHashes(
      Selector(), descendant_selector_identifier_hashes_,
      kMaximumIdentifierCount);
>>>>>>> chromium
}

void RuleSet::AddToRuleSet(const AtomicString& key,
                           PendingRuleMap& map,
                           const RuleData* rule_data) {
  Member<HeapLinkedStack<Member<const RuleData>>>& rules =
      map.insert(key, nullptr).stored_value->value;
  if (!rules)
    rules = MakeGarbageCollected<HeapLinkedStack<Member<const RuleData>>>();
  rules->Push(rule_data);
}

static void ExtractSelectorValues(const CSSSelector* selector,
                                  const StyleScope* style_scope,
                                  AtomicString& id,
                                  AtomicString& class_name,
                                  AtomicString& custom_pseudo_element_name,
                                  AtomicString& tag_name,
                                  AtomicString& part_name,
                                  CSSSelector::PseudoType& pseudo_type) {
  switch (selector->Match()) {
    case CSSSelector::kId:
      id = selector->Value();
      break;
    case CSSSelector::kClass:
      class_name = selector->Value();
      break;
    case CSSSelector::kTag:
<<<<<<< HEAD
      tag_name = selector->TagQName().LocalName();
=======
      if (selector->TagQName().LocalName() !=
          CSSSelector::UniversalSelectorAtom())
        tag_name = selector->TagQName().LocalName();
>>>>>>> chromium
      break;
    case CSSSelector::kPseudoClass:
    case CSSSelector::kPseudoElement:
    case CSSSelector::kPagePseudoClass:
      // Must match the cases in RuleSet::FindBestRuleSetAndAdd.
      switch (selector->GetPseudoType()) {
<<<<<<< HEAD
        case CSSSelector::kPseudoFocus:
          if (pseudo_type == CSSSelector::kPseudoScrollMarker ||
              pseudo_type == CSSSelector::kPseudoScrollButton) {
            break;
          }
          [[fallthrough]];
=======
>>>>>>> chromium
        case CSSSelector::kPseudoCue:
        case CSSSelector::kPseudoLink:
        case CSSSelector::kPseudoVisited:
        case CSSSelector::kPseudoWebkitAnyLink:
        case CSSSelector::kPseudoAnyLink:
        case CSSSelector::kPseudoFocus:
        case CSSSelector::kPseudoFocusVisible:
        case CSSSelector::kPseudoPlaceholder:
        case CSSSelector::kPseudoFileSelectorButton:
        case CSSSelector::kPseudoHost:
        case CSSSelector::kPseudoHostContext:
<<<<<<< HEAD
        case CSSSelector::kPseudoSlotted:
        case CSSSelector::kPseudoSelectorFragmentAnchor:
        case CSSSelector::kPseudoRoot:
        case CSSSelector::kPseudoScrollMarker:
        case CSSSelector::kPseudoScrollButton:
=======
        case CSSSelector::kPseudoSpatialNavigationInterest:
>>>>>>> chromium
          pseudo_type = selector->GetPseudoType();
          break;
        case CSSSelector::kPseudoWebKitCustomElement:
        case CSSSelector::kPseudoBlinkInternalElement:
          custom_pseudo_element_name = selector->Value();
          break;
        case CSSSelector::kPseudoPart:
          part_name = selector->Value();
          break;
<<<<<<< HEAD
        case CSSSelector::kPseudoPicker:
          picker_name = selector->Argument();
          break;
        case CSSSelector::kPseudoIs:
        case CSSSelector::kPseudoWhere:
        case CSSSelector::kPseudoParent: {
          const CSSSelector* selector_list = selector->SelectorListOrParent();
          // If the :is/:where has only a single argument, it effectively acts
          // like a normal selector (save for specificity), and we can put it
          // into a bucket based on that selector.
          //
          // Note that `selector_list` may be nullptr for top-level '&'
          // selectors.
          //
          // Note also that FindBestRuleSetAndAdd assumes that you cannot
          // reach a pseudo-element via a '&' selector (crbug.com/380107557).
          // We ensure that this cannot happen by never adding rules
          // like '::before { & {} }' to the RuleSet in the first place,
          // see CollectMetadataFromSelector. Rules with mixed
          // allowed/disallowed selectors, e.g. '::before, .foo { & {} }',
          // *are* added to the RuleSet, but fail the IsSingleComplexSelector
          // check below, satisfying the assumptions of FindBestRuleSetAndAdd.
          if (selector_list &&
              CSSSelectorList::IsSingleComplexSelector(*selector_list)) {
            ExtractSelectorValues(selector_list, style_scope, id, class_name,
                                  attr_name, attr_value, is_exact_attr,
                                  custom_pseudo_element_name, tag_name,
                                  part_name, picker_name, pseudo_type);
          }
          break;
        }
        case CSSSelector::kPseudoScope: {
          // Just like :is() and :where(), we can bucket :scope as the
          // <scope-start> it refers to, as long as the <scope-start>
          // contains a single selector.
          //
          // Note that the <scope-start> selector is optional, therefore
          // From() may return nullptr below.
          const CSSSelector* selector_list =
              style_scope ? style_scope->From() : nullptr;
          if (selector_list &&
              CSSSelectorList::IsSingleComplexSelector(*selector_list)) {
            ExtractSelectorValues(selector_list, style_scope, id, class_name,
                                  attr_name, attr_value, is_exact_attr,
                                  custom_pseudo_element_name, tag_name,
                                  part_name, picker_name, pseudo_type);
          }
          break;
        }
=======
>>>>>>> chromium
        default:
          break;
      }
      break;
    default:
      break;
  }
}

<<<<<<< HEAD
// For a (possibly compound) selector, extract the values used for determining
// its buckets (e.g. for “.foo[baz]”, will return foo for class_name and
// baz for attr_name). Returns the last subselector in the group, which is also
// the one given the highest priority.
static const CSSSelector* ExtractBestSelectorValues(
    const CSSSelector& component,
    const StyleScope* style_scope,
    AtomicString& id,
    AtomicString& class_name,
    AtomicString& attr_name,
    AtomicString& attr_value,
    bool& is_exact_attr,
    AtomicString& custom_pseudo_element_name,
    AtomicString& tag_name,
    AtomicString& part_name,
    AtomicString& picker_name,
    CSSSelector::PseudoType& pseudo_type) {
  const CSSSelector* it = &component;
  for (; it && it->Relation() == CSSSelector::kSubSelector;
       it = it->NextSimpleSelector()) {
    ExtractSelectorValues(it, style_scope, id, class_name, attr_name,
                          attr_value, is_exact_attr, custom_pseudo_element_name,
                          tag_name, part_name, picker_name, pseudo_type);
  }
  if (it) {
    ExtractSelectorValues(it, style_scope, id, class_name, attr_name,
                          attr_value, is_exact_attr, custom_pseudo_element_name,
                          tag_name, part_name, picker_name, pseudo_type);
  }
  return it;
}

template <class Func>
static void MarkAsCoveredByBucketing(CSSSelector& selector,
                                     Func&& should_mark_func) {
  for (CSSSelector* s = &selector;;
       ++s) {  // Termination condition within loop.
    if (should_mark_func(*s)) {
      s->SetCoveredByBucketing(true);
    }

    // NOTE: We could also have tested single-element :is() and :where()
    // if the inside matches, but it's very rare, so we save the runtime
    // here instead. (& in nesting selectors could perhaps be somewhat
    // more common, but we currently don't bucket on & at all.)
    //
    // We could also have taken universal selectors no matter what
    // should_mark_func() says, but again, we consider that not worth it
    // (though if the selector is being put in the universal bucket,
    // there will be an explicit check).

    if (s->IsLastInComplexSelector() ||
        s->Relation() != CSSSelector::kSubSelector) {
      break;
    }
  }
}

static void UnmarkAsCoveredByBucketing(CSSSelector& selector) {
  for (CSSSelector* s = &selector;;
       ++s) {  // Termination condition within loop.
    s->SetCoveredByBucketing(false);
    if (s->IsLastInComplexSelector() ||
        s->Relation() != CSSSelector::kSubSelector) {
      break;
    }
  }
}

template <RuleSet::BucketCoverage bucket_coverage>
void RuleSet::FindBestRuleSetAndAdd(CSSSelector& component,
                                    const RuleData& rule_data,
                                    const StyleScope* style_scope) {
=======
bool RuleSet::FindBestRuleSetAndAdd(const CSSSelector& component,
                                    RuleData* rule_data) {
>>>>>>> chromium
  AtomicString id;
  AtomicString class_name;
  AtomicString custom_pseudo_element_name;
  AtomicString tag_name;
  AtomicString part_name;
  CSSSelector::PseudoType pseudo_type = CSSSelector::kPseudoUnknown;

#ifndef NDEBUG
  all_rules_.push_back(rule_data);
#endif

<<<<<<< HEAD
  bool is_exact_attr;
  const CSSSelector* it = ExtractBestSelectorValues(
      component, style_scope, id, class_name, attr_name, attr_value,
      is_exact_attr, custom_pseudo_element_name, tag_name, part_name,
      picker_name, pseudo_type);
=======
  const CSSSelector* it = &component;
  for (; it && it->Relation() == CSSSelector::kSubSelector;
       it = it->TagHistory()) {
    ExtractSelectorValues(it, id, class_name, custom_pseudo_element_name,
                          tag_name, part_name, pseudo_type);
  }
  if (it) {
    ExtractSelectorValues(it, id, class_name, custom_pseudo_element_name,
                          tag_name, part_name, pseudo_type);
  }
>>>>>>> chromium

  // Prefer rule sets in order of most likely to apply infrequently.
  if (!id.IsEmpty()) {
    AddToRuleSet(id, EnsurePendingRules()->id_rules, rule_data);
    return true;
  }

  if (!class_name.IsEmpty()) {
    AddToRuleSet(class_name, EnsurePendingRules()->class_rules, rule_data);
    return true;
  }

<<<<<<< HEAD
  if (!attr_name.empty()) {
    AddToRuleSet(attr_name, attr_rules_, rule_data);
    if (attr_name == html_names::kStyleAttr) {
      has_bucket_for_style_attr_ = true;
    }
    // NOTE: Cannot mark anything as covered by bucketing, since the bucketing
    // does not verify namespaces. (We could consider doing so if the namespace
    // is *, but we'd need to be careful about case sensitivity wrt. legacy
    // attributes.)
    return;
  }

  auto get_ua_shadow_pseudo = [&]() -> const AtomicString& {
    if (picker_name == "select") {
      return shadow_element_names::kPickerSelect;
    } else if (pseudo_type != CSSSelector::kPseudoUnknown) {
      return shadow_element_utils::StringForUAShadowPseudoId(
          CSSSelector::GetPseudoId(pseudo_type));
    }
    return g_null_atom;
  };

  AtomicString ua_shadow_pseudo = get_ua_shadow_pseudo();

  // Any selector with or following ::part() or a UA shadow pseudo-element
  // must go in the bucket for the *innermost* such pseudo-element.

  // TODO(dbaron): Should this eventually check kShadowSlot as well?
  if (part_name.empty() && ua_shadow_pseudo == g_null_atom && it &&
      (it->Relation() == CSSSelector::RelationType::kUAShadow ||
       it->Relation() == CSSSelector::RelationType::kShadowPart)) {
    const CSSSelector* previous = it->NextSimpleSelector();
    if (previous->Match() == CSSSelector::kPseudoElement) {
      ExtractSelectorValues(previous, style_scope, id, class_name, attr_name,
                            attr_value, is_exact_attr,
                            custom_pseudo_element_name, tag_name, part_name,
                            picker_name, pseudo_type);
      ua_shadow_pseudo = get_ua_shadow_pseudo();
    }
  }

  // Any selector with or following ::part() must go in the part bucket,
  // because we look in that bucket in higher scopes to find rules that need
  // to match inside the shadow tree.
  if (!part_name.empty()) {
    // TODO: Mark as covered by bucketing?
    AddToRuleSet(part_pseudo_rules_, rule_data);
    return;
  }

  if (!custom_pseudo_element_name.empty()) {
    // Custom pseudos come before ids and classes in the order of
    // NextSimpleSelector(), and have a relation of ShadowPseudo between them.
    // Therefore we should never be a situation where ExtractSelectorValues
    // finds id and className in addition to custom pseudo.
    DCHECK(id.empty());
    DCHECK(class_name.empty());
    AddToRuleSet(custom_pseudo_element_name, ua_shadow_pseudo_element_rules_,
=======
  if (!custom_pseudo_element_name.IsEmpty()) {
    // Custom pseudos come before ids and classes in the order of tagHistory,
    // and have a relation of ShadowPseudo between them. Therefore we should
    // never be a situation where ExtractSelectorValues finds id and
    // className in addition to custom pseudo.
    DCHECK(id.IsEmpty());
    DCHECK(class_name.IsEmpty());
    AddToRuleSet(custom_pseudo_element_name,
                 EnsurePendingRules()->ua_shadow_pseudo_element_rules,
>>>>>>> chromium
                 rule_data);
    return true;
  }

<<<<<<< HEAD
  if (ua_shadow_pseudo != g_null_atom) {
    // TODO(dbaron): This needs further work to support multiple
    // pseudo-elements after ::slotted().  This likely requires reorganization
    // of how MatchSlottedRules interacts with MatchOuterScopeRules.
    CHECK(it);
    if (it->FollowsSlotted()) {
      AddToRuleSet(slotted_pseudo_element_rules_, rule_data);
    } else {
      AddToRuleSet(ua_shadow_pseudo, ua_shadow_pseudo_element_rules_,
                   rule_data);
    }
    return;
=======
  if (!part_name.IsEmpty()) {
    part_pseudo_rules_.push_back(rule_data);
    return true;
>>>>>>> chromium
  }

  switch (pseudo_type) {
    case CSSSelector::kPseudoCue:
      cue_pseudo_rules_.push_back(rule_data);
      return true;
    case CSSSelector::kPseudoLink:
    case CSSSelector::kPseudoVisited:
    case CSSSelector::kPseudoAnyLink:
    case CSSSelector::kPseudoWebkitAnyLink:
      link_pseudo_class_rules_.push_back(rule_data);
      return true;
    case CSSSelector::kPseudoSpatialNavigationInterest:
      spatial_navigation_interest_class_rules_.push_back(rule_data);
      return true;
    case CSSSelector::kPseudoFocus:
      focus_pseudo_class_rules_.push_back(rule_data);
      return true;
    case CSSSelector::kPseudoFocusVisible:
      focus_visible_pseudo_class_rules_.push_back(rule_data);
      return true;
    case CSSSelector::kPseudoPlaceholder:
    case CSSSelector::kPseudoFileSelectorButton:
      if (it->FollowsPart()) {
        part_pseudo_rules_.push_back(rule_data);
      } else {
        const auto& name = pseudo_type == CSSSelector::kPseudoFileSelectorButton
                               ? shadow_element_names::kPseudoFileUploadButton
                               : shadow_element_names::kPseudoInputPlaceholder;
        AddToRuleSet(name, EnsurePendingRules()->ua_shadow_pseudo_element_rules,
                     rule_data);
      }
      return true;
    case CSSSelector::kPseudoHost:
    case CSSSelector::kPseudoHostContext:
      shadow_host_rules_.push_back(rule_data);
      return true;
    default:
      break;
  }

  if (!tag_name.IsEmpty()) {
    AddToRuleSet(tag_name, EnsurePendingRules()->tag_rules, rule_data);
    return true;
  }

<<<<<<< HEAD
  // The ':scope' pseudo-class (bucketed as universal) may match the host
  // when the selector is scoped (e.g. using '@scope') to that host.
  if (component.IsScopeContaining()) {
    must_check_universal_bucket_for_shadow_host_ = true;
  }

  // Normally, rules involving :host would be stuck in their own bucket
  // above; if we came here, it is because we have something like :is(:host,
  // .foo). Mark that we have this case.
  if (component.IsOrContainsHostPseudoClass()) {
    must_check_universal_bucket_for_shadow_host_ = true;
  }

  // If we didn't find a specialized map to stick it in, file under universal
  // rules.
  MarkAsCoveredByBucketing(component, [](const CSSSelector& selector) {
    return selector.Match() == CSSSelector::kUniversalTag &&
           selector.TagQName() == AnyQName();
  });
  AddToRuleSet(universal_rules_, rule_data);
=======
  return false;
>>>>>>> chromium
}

void RuleSet::AddRule(StyleRule* rule,
                      unsigned selector_index,
                      AddRuleFlags add_rule_flags,
                      const ContainerQuery* container_query) {
  RuleData* rule_data = RuleData::MaybeCreate(rule, selector_index, rule_count_,
                                              add_rule_flags, container_query);
  if (!rule_data) {
    // This can happen if selector_index or position is out of range.
    return;
  }
  ++rule_count_;
  if (features_.CollectFeaturesFromRuleData(rule_data) ==
      RuleFeatureSet::kSelectorNeverMatches)
    return;

<<<<<<< HEAD
  FindBestRuleSetAndAdd<BucketCoverage::kCompute>(rule_data.MutableSelector(),
                                                  rule_data, style_scope);
=======
  if (!FindBestRuleSetAndAdd(rule_data->Selector(), rule_data)) {
    // If we didn't find a specialized map to stick it in, file under universal
    // rules.
    universal_rules_.push_back(rule_data);
  }
>>>>>>> chromium

  // If the rule has CSSSelector::kMatchLink, it means that there is a :visited
  // or :link pseudo-class somewhere in the selector. In those cases, we
  // effectively split the rule into two: one which covers the situation
  // where we are in an unvisited link (kMatchLink), and another which covers
  // the visited link case (kMatchVisited).
<<<<<<< HEAD
  if (rule_data.LinkMatchType() == CSSSelector::kMatchLink) {
    // Now the selector will be in two buckets.
    rule_data.ResetEntirelyCoveredByBucketing();

    RuleData visited_dependent(
        rule, rule_data.SelectorIndex(), rule_data.GetPosition(), style_scope,
        add_rule_flags | kRuleIsVisitedDependent, bloom_hash_backing_);
    // Since the selector now is in two buckets, we use BucketCoverage::kIgnore
    // to prevent CSSSelector::is_covered_by_bucketing_ from being set.
    FindBestRuleSetAndAdd<BucketCoverage::kIgnore>(
        visited_dependent.MutableSelector(), visited_dependent, style_scope);
=======
  if (rule_data->LinkMatchType() == CSSSelector::kMatchLink) {
    RuleData* visited_dependent = RuleData::MaybeCreate(
        rule, rule_data->SelectorIndex(), rule_data->GetPosition(),
        add_rule_flags | kRuleIsVisitedDependent, container_query);
    DCHECK(visited_dependent);
    visited_dependent_rules_.push_back(visited_dependent);
>>>>>>> chromium
  }
}

void RuleSet::AddPageRule(StyleRulePage* rule) {
  EnsurePendingRules();  // So that page_rules_.ShrinkToFit() gets called.
  page_rules_.push_back(rule);
}

void RuleSet::AddFontFaceRule(StyleRuleFontFace* rule) {
  EnsurePendingRules();  // So that font_face_rules_.ShrinkToFit() gets called.
  font_face_rules_.push_back(rule);
}

void RuleSet::AddKeyframesRule(StyleRuleKeyframes* rule) {
  EnsurePendingRules();  // So that keyframes_rules_.ShrinkToFit() gets called.
  keyframes_rules_.push_back(rule);
}

void RuleSet::AddPropertyRule(StyleRuleProperty* rule) {
  EnsurePendingRules();  // So that property_rules_.ShrinkToFit() gets called.
  property_rules_.push_back(rule);
}

void RuleSet::AddCounterStyleRule(StyleRuleCounterStyle* rule) {
  EnsurePendingRules();  // So that counter_style_rules_.ShrinkToFit() gets
                         // called.
  counter_style_rules_.push_back(rule);
}

void RuleSet::AddScrollTimelineRule(StyleRuleScrollTimeline* rule) {
  EnsurePendingRules();  // So that property_rules_.ShrinkToFit() gets called.
  scroll_timeline_rules_.push_back(rule);
}

void RuleSet::AddChildRules(const HeapVector<Member<StyleRuleBase>>& rules,
                            const MediaQueryEvaluator& medium,
                            AddRuleFlags add_rule_flags,
                            const ContainerQuery* container_query) {
  for (unsigned i = 0; i < rules.size(); ++i) {
    StyleRuleBase* rule = rules[i].Get();

    if (auto* style_rule = DynamicTo<StyleRule>(rule)) {
      const CSSSelectorList& selector_list = style_rule->SelectorList();
      for (const CSSSelector* selector = selector_list.First(); selector;
           selector = selector_list.Next(*selector)) {
        wtf_size_t selector_index = selector_list.SelectorIndex(*selector);
        if (selector->HasSlottedPseudo()) {
          slotted_pseudo_element_rules_.push_back(
              MinimalRuleData(style_rule, selector_index, add_rule_flags));
        } else {
          AddRule(style_rule, selector_index, add_rule_flags, container_query);
        }
      }
    } else if (auto* page_rule = DynamicTo<StyleRulePage>(rule)) {
      AddPageRule(page_rule);
    } else if (auto* media_rule = DynamicTo<StyleRuleMedia>(rule)) {
      if (MatchMediaForAddRules(medium, media_rule->MediaQueries())) {
        AddChildRules(media_rule->ChildRules(), medium, add_rule_flags,
                      container_query);
      }
    } else if (auto* font_face_rule = DynamicTo<StyleRuleFontFace>(rule)) {
      AddFontFaceRule(font_face_rule);
    } else if (auto* keyframes_rule = DynamicTo<StyleRuleKeyframes>(rule)) {
      AddKeyframesRule(keyframes_rule);
    } else if (auto* property_rule = DynamicTo<StyleRuleProperty>(rule)) {
      AddPropertyRule(property_rule);
    } else if (auto* counter_style_rule =
                   DynamicTo<StyleRuleCounterStyle>(rule)) {
      AddCounterStyleRule(counter_style_rule);
    } else if (auto* scroll_timeline_rule =
                   DynamicTo<StyleRuleScrollTimeline>(rule)) {
      AddScrollTimelineRule(scroll_timeline_rule);
    } else if (auto* supports_rule = DynamicTo<StyleRuleSupports>(rule)) {
      if (supports_rule->ConditionIsSupported()) {
        AddChildRules(supports_rule->ChildRules(), medium, add_rule_flags,
                      container_query);
      }
    } else if (auto* container_rule = DynamicTo<StyleRuleContainer>(rule)) {
      // TODO(crbug.com/1145970): Handle nested container queries.
      // For now only the innermost applies.
      AddChildRules(container_rule->ChildRules(), medium, add_rule_flags,
                    &container_rule->GetContainerQuery());
    }
  }
}

bool RuleSet::MatchMediaForAddRules(const MediaQueryEvaluator& evaluator,
                                    const MediaQuerySet* media_queries) {
  if (!media_queries)
    return true;
  bool match_media = evaluator.Eval(
      *media_queries, &features_.ViewportDependentMediaQueryResults(),
      &features_.DeviceDependentMediaQueryResults());
  media_query_set_results_.push_back(
      MediaQuerySetResult(*media_queries, match_media));
  return match_media;
}

void RuleSet::AddRulesFromSheet(const StyleSheetContents* sheet,
                                const MediaQueryEvaluator& medium,
<<<<<<< HEAD
                                CascadeLayer* cascade_layer,
                                const StyleScope* style_scope) {
=======
                                AddRuleFlags add_rule_flags) {
>>>>>>> chromium
  TRACE_EVENT0("blink", "RuleSet::addRulesFromSheet");

  DCHECK(sheet);

  const HeapVector<Member<StyleRuleImport>>& import_rules =
      sheet->ImportRules();
  for (unsigned i = 0; i < import_rules.size(); ++i) {
    StyleRuleImport* import_rule = import_rules[i].Get();
<<<<<<< HEAD
    if (!import_rule->IsSupported()) {
      continue;
    }
    if (!MatchMediaForAddRules(medium, import_rule->MediaQueries())) {
      continue;
    }
    CascadeLayer* import_layer = cascade_layer;
    if (import_rule->IsLayered()) {
      import_layer =
          GetOrAddSubLayer(cascade_layer, import_rule->GetLayerName());
    }
    if (import_rule->GetStyleSheet()) {
      AddRulesFromSheet(import_rule->GetStyleSheet(), medium, import_layer,
                        import_rule->GetScope());
    }
  }

  AddChildRules(/*parent_rule=*/nullptr, sheet->ChildRules(), medium,
                kRuleHasNoSpecialState, nullptr /* container_query */,
                cascade_layer, style_scope, /*within_mixin=*/false);
=======
    if (import_rule->GetStyleSheet() &&
        MatchMediaForAddRules(medium, import_rule->MediaQueries())) {
      AddRulesFromSheet(import_rule->GetStyleSheet(), medium, add_rule_flags);
    }
  }

  AddChildRules(sheet->ChildRules(), medium, add_rule_flags,
                nullptr /* container_query */);
>>>>>>> chromium
}

void RuleSet::AddStyleRule(StyleRule* rule, AddRuleFlags add_rule_flags) {
  for (wtf_size_t selector_index =
           rule->SelectorList().SelectorIndex(*rule->SelectorList().First());
       selector_index != kNotFound;
       selector_index =
           rule->SelectorList().IndexOfNextSelectorAfter(selector_index)) {
    AddRule(rule, selector_index, add_rule_flags,
            nullptr /* container_query */);
  }
}

<<<<<<< HEAD
void RuleSet::NewlyAddedFromDifferentRuleSet(const RuleData& old_rule_data,
                                             const StyleScope* style_scope,
                                             const RuleSet& old_rule_set,
                                             RuleData& new_rule_data) {
  new_rule_data.MovedToDifferentRuleSet(old_rule_set.bloom_hash_backing_,
                                        bloom_hash_backing_, rule_count_);
  // We don't bother with container_query_intervals_ and
  // AddRuleToLayerIntervals() here, since they are not checked in diff
  // rulesets.
  AddRuleToIntervals(style_scope, rule_count_, scope_intervals_);
  ++rule_count_;
}

void RuleSet::AddFilteredRulesFromOtherBucket(
    const RuleSet& other,
    const HeapVector<RuleData>& src,
    const HeapHashSet<Member<StyleRule>>& only_include,
    HeapVector<RuleData>* dst) {
  Seeker<StyleScope> scope_seeker(other.scope_intervals_);
  for (const RuleData& rule_data : src) {
    if (IncludeRule(rule_data.Rule(), only_include)) {
      dst->push_back(rule_data);
      NewlyAddedFromDifferentRuleSet(rule_data,
                                     scope_seeker.Seek(rule_data.GetPosition()),
                                     other, dst->back());
    }
  }
}

void RuleSet::AddFilteredRulesFromOtherSet(
    const RuleSet& other,
    const HeapHashSet<Member<StyleRule>>& only_include) {
  if (other.rule_count_ > 0) {
    id_rules_.AddFilteredRulesFromOtherSet(other.id_rules_, only_include, other,
                                           *this);
    class_rules_.AddFilteredRulesFromOtherSet(other.class_rules_, only_include,
                                              other, *this);
    attr_rules_.AddFilteredRulesFromOtherSet(other.attr_rules_, only_include,
                                             other, *this);
    // NOTE: attr_substring_matchers_ will be rebuilt in CompactRules().
    tag_rules_.AddFilteredRulesFromOtherSet(other.tag_rules_, only_include,
                                            other, *this);
    ua_shadow_pseudo_element_rules_.AddFilteredRulesFromOtherSet(
        other.ua_shadow_pseudo_element_rules_, only_include, other, *this);
    AddFilteredRulesFromOtherBucket(other, other.link_pseudo_class_rules_,
                                    only_include, &link_pseudo_class_rules_);
    AddFilteredRulesFromOtherBucket(other, other.cue_pseudo_rules_,
                                    only_include, &cue_pseudo_rules_);
    AddFilteredRulesFromOtherBucket(other, other.focus_pseudo_class_rules_,
                                    only_include, &focus_pseudo_class_rules_);
    AddFilteredRulesFromOtherBucket(
        other, other.focus_visible_pseudo_class_rules_, only_include,
        &focus_visible_pseudo_class_rules_);
    AddFilteredRulesFromOtherBucket(other, other.universal_rules_, only_include,
                                    &universal_rules_);
    AddFilteredRulesFromOtherBucket(other, other.shadow_host_rules_,
                                    only_include, &shadow_host_rules_);
    AddFilteredRulesFromOtherBucket(other, other.part_pseudo_rules_,
                                    only_include, &part_pseudo_rules_);
    AddFilteredRulesFromOtherBucket(other, other.slotted_pseudo_element_rules_,
                                    only_include,
                                    &slotted_pseudo_element_rules_);
    AddFilteredRulesFromOtherBucket(
        other, other.selector_fragment_anchor_rules_, only_include,
        &selector_fragment_anchor_rules_);
    AddFilteredRulesFromOtherBucket(other, other.root_element_rules_,
                                    only_include, &root_element_rules_);

    // We don't care about page_rules_ etc., since having those in a RuleSetDiff
    // would mark it as unrepresentable anyway.

    need_compaction_ = true;
  }

#if EXPENSIVE_DCHECKS_ARE_ON()
  allow_unsorted_ = true;
#endif
}

void RuleSet::AddStyleRule(StyleRule* style_rule,
                           StyleRule* parent_rule,
                           const MediaQueryEvaluator& medium,
                           AddRuleFlags add_rule_flags,
                           bool within_mixin,
                           const ContainerQuery* container_query,
                           CascadeLayer* cascade_layer,
                           const StyleScope* style_scope) {
  if (within_mixin) {
    style_rule = To<StyleRule>(style_rule->Renest(parent_rule));
  }
  for (const CSSSelector* selector = style_rule->FirstSelector(); selector;
       selector = CSSSelectorList::Next(*selector)) {
    wtf_size_t selector_index = style_rule->SelectorIndex(*selector);
    AddRule(style_rule, selector_index, add_rule_flags, container_query,
            cascade_layer, style_scope);
  }

  // Nested rules are taken to be added immediately after their parent rule.
  if (style_rule->ChildRules() != nullptr) {
    AddChildRules(style_rule, *style_rule->ChildRules(), medium, add_rule_flags,
                  container_query, cascade_layer, style_scope, within_mixin);
  }
}

CascadeLayer* RuleSet::GetOrAddSubLayer(CascadeLayer* cascade_layer,
                                        const StyleRuleBase::LayerName& name) {
  if (!cascade_layer) {
    cascade_layer = EnsureImplicitOuterLayer();
  }
  return cascade_layer->GetOrAddSubLayer(name);
}

bool RuleMap::Add(const AtomicString& key, const RuleData& rule_data) {
  RuleMap::Extent* rules = nullptr;
  if (buckets.IsNull()) {
    // First insert.
    buckets = RobinHoodMap<AtomicString, Extent>(8);
  } else {
    // See if we can find an existing entry for this key.
    RobinHoodMap<AtomicString, Extent>::Bucket* bucket = buckets.Find(key);
    if (bucket != nullptr) {
      rules = &bucket->value;
    }
  }
  if (rules == nullptr) {
    RobinHoodMap<AtomicString, Extent>::Bucket* bucket = buckets.Insert(key);
    if (bucket == nullptr) {
      return false;
    }
    rules = &bucket->value;
    rules->bucket_number = num_buckets++;
  }

  RuleData rule_data_copy = rule_data;
  rule_data_copy.ComputeEntirelyCoveredByBucketing();
  bucket_number_.push_back(rules->bucket_number);
  ++rules->length;
  backing.push_back(std::move(rule_data_copy));
  return true;
}

void RuleMap::Compact() {
  if (compacted) {
    return;
  }
  if (backing.empty()) {
    DCHECK(bucket_number_.empty());
    // Nothing to do.
    compacted = true;
    return;
  }

  backing.shrink_to_fit();

  // Order by (bucket_number, order_in_bucket) by way of a simple
  // in-place counting sort (which is O(n), because our highest bucket
  // number is always less than or equal to the number of elements).
  // First, we make an array that contains the number of elements in each
  // bucket, indexed by the bucket number. We also find each element's
  // position within that bucket.
  auto counts =
      base::HeapArray<unsigned>::WithSize(num_buckets);  // Zero-initialized.
  auto order_in_bucket = base::HeapArray<unsigned>::Uninit(backing.size());
  for (wtf_size_t i = 0; i < bucket_number_.size(); ++i) {
    order_in_bucket[i] = counts[bucket_number_[i]]++;
  }

  // Do the prefix sum. After this, counts[i] is the desired start index
  // for the i-th bucket.
  unsigned sum = 0;
  for (wtf_size_t i = 0; i < num_buckets; ++i) {
    DCHECK_GT(counts[i], 0U);
    unsigned new_sum = sum + counts[i];
    counts[i] = sum;
    sum = new_sum;
  }

  // Store that information into each bucket.
  for (auto& [key, value] : buckets) {
    value.start_index = counts[value.bucket_number];
  }

  // Now put each element into its right place. Every iteration, we will
  // either swap an element into its final destination, or, when we
  // encounter one that is already in its correct place (possibly
  // because we put it there earlier), skip to the next array slot.
  // These will happen exactly n times each, giving us our O(n) runtime.
  for (wtf_size_t i = 0; i < backing.size();) {
    wtf_size_t correct_pos = counts[bucket_number_[i]] + order_in_bucket[i];
    if (i == correct_pos) {
      ++i;
=======
void RuleSet::CompactPendingRules(PendingRuleMap& pending_map,
                                  CompactRuleMap& compact_map) {
  for (auto& item : pending_map) {
    HeapLinkedStack<Member<const RuleData>>* pending_rules =
        item.value.Release();
    Member<HeapVector<Member<const RuleData>>>& rules =
        compact_map.insert(item.key, nullptr).stored_value->value;
    if (!rules) {
      rules = MakeGarbageCollected<HeapVector<Member<const RuleData>>>();
      rules->ReserveInitialCapacity(pending_rules->size());
>>>>>>> chromium
    } else {
      rules->ReserveCapacity(pending_rules->size());
    }
<<<<<<< HEAD
  }

  // We're done with the bucket numbers, so we can release the memory.
  // If we need the bucket numbers again, they will be reconstructed by
  // RuleMap::Uncompact.
  bucket_number_.clear();

  compacted = true;
}

void RuleMap::Uncompact() {
  bucket_number_.resize(backing.size());

  num_buckets = 0;
  for (auto& [key, value] : buckets) {
    for (unsigned& bucket_number : GetBucketNumberFromExtent(value)) {
      bucket_number = num_buckets;
    }
    value.bucket_number = num_buckets++;
    value.length =
        static_cast<unsigned>(GetBucketNumberFromExtent(value).size());
  }
  compacted = false;
}

// See RuleSet::AddFilteredRulesFromOtherSet().
void RuleMap::AddFilteredRulesFromOtherSet(
    const RuleMap& other,
    const HeapHashSet<Member<StyleRule>>& only_include,
    const RuleSet& old_rule_set,
    RuleSet& new_rule_set) {
  if (compacted) {
    Uncompact();
  }
  if (other.compacted) {
    for (const auto& [key, extent] : other.buckets) {
      Seeker<StyleScope> scope_seeker(old_rule_set.scope_intervals_);
      for (const RuleData& rule_data : other.GetRulesFromExtent(extent)) {
        if (IncludeRule(rule_data.Rule(), only_include)) {
          Add(key, rule_data);
          new_rule_set.NewlyAddedFromDifferentRuleSet(
              rule_data, scope_seeker.Seek(rule_data.GetPosition()),
              old_rule_set, backing.back());
        }
      }
    }
  } else {
    // First make a mapping of bucket number to key.
    auto keys = base::HeapArray<const AtomicString*>::Uninit(other.num_buckets);
    for (const auto& [key, src_extent] : other.buckets) {
      keys[src_extent.bucket_number] = &key;
    }

    // Now that we have the mapping, we can just copy over all the relevant
    // RuleDatas.
    Seeker<StyleScope> scope_seeker(old_rule_set.scope_intervals_);
    for (wtf_size_t i = 0; i < other.backing.size(); ++i) {
      const unsigned bucket_number = other.bucket_number_[i];
      const RuleData& rule_data = other.backing[i];
      if (IncludeRule(rule_data.Rule(), only_include)) {
        Add(*keys[bucket_number], rule_data);
        new_rule_set.NewlyAddedFromDifferentRuleSet(
            rule_data, scope_seeker.Seek(rule_data.GetPosition()), old_rule_set,
            backing.back());
      }
    }
  }
}

static wtf_size_t GetMinimumRulesetSizeForSubstringMatcher() {
  // It's not worth going through the Aho-Corasick matcher unless we can
  // reject a reasonable number of rules in one go. Practical ad-hoc testing
  // suggests the break-even point between using the tree and just testing
  // all of the rules individually lies somewhere around 20–40 rules
  // (depending a bit on e.g. how hot the tree is in the cache, the length
  // of the value that we match against, and of course whether we actually
  // have a match). We add a little bit of margin to compensate for the fact
  // that we also need to spend time building the tree, and the extra memory
  // in use.
  return 50;
}

bool RuleSet::CanIgnoreEntireList(base::span<const RuleData> list,
                                  const AtomicString& key,
                                  const AtomicString& value) const {
  DCHECK_EQ(attr_rules_.Find(key).size(), list.size());
  if (!list.empty()) {
    DCHECK_EQ(attr_rules_.Find(key).data(), list.data());
  }
  if (list.size() < GetMinimumRulesetSizeForSubstringMatcher()) {
    // Too small to build up a tree, so always check.
    DCHECK(!base::Contains(attr_substring_matchers_, key));
    return false;
  }

  // See CreateSubstringMatchers().
  if (value.empty()) {
    return false;
  }

  auto it = attr_substring_matchers_.find(key);
  if (it == attr_substring_matchers_.end()) {
    // Building the tree failed, so always check.
    return false;
  }
  return !it->value->AnyMatch(value.LowerASCII().Utf8());
}

void RuleSet::CreateSubstringMatchers(
    RuleMap& attr_map,
    const HeapVector<Interval<StyleScope>>& scope_intervals,
    RuleSet::SubstringMatcherMap& substring_matcher_map) {
  for (const auto& [/*AtomicString*/ attr,
                    /*base::span<const RuleData>*/ ruleset] : attr_map) {
    if (ruleset.size() < GetMinimumRulesetSizeForSubstringMatcher()) {
      continue;
    }
    std::vector<MatcherStringPattern> patterns;
    int rule_index = 0;
    Seeker<StyleScope> scope_seeker(scope_intervals);
    for (const RuleData& rule : ruleset) {
      AtomicString id;
      AtomicString class_name;
      AtomicString attr_name;
      AtomicString attr_value;
      AtomicString custom_pseudo_element_name;
      AtomicString tag_name;
      AtomicString part_name;
      AtomicString picker_name;
      bool is_exact_attr;
      CSSSelector::PseudoType pseudo_type = CSSSelector::kPseudoUnknown;
      const StyleScope* style_scope = scope_seeker.Seek(rule.GetPosition());
      ExtractBestSelectorValues(rule.Selector(), style_scope, id, class_name,
                                attr_name, attr_value, is_exact_attr,
                                custom_pseudo_element_name, tag_name, part_name,
                                picker_name, pseudo_type);
      DCHECK(!attr_name.empty());

      if (attr_value.empty()) {
        if (is_exact_attr) {
          // The empty string would make the entire tree useless
          // (it is a substring of every possible value),
          // so as a special case, we ignore it, and have a separate
          // check in CanIgnoreEntireList().
          continue;
        } else {
          // This rule would indeed match every element containing the
          // given attribute (e.g. [foo] or [foo^=""]), so building a tree
          // would be wrong.
          patterns.clear();
          break;
        }
      }

      std::string pattern = attr_value.LowerASCII().Utf8();

      // SubstringSetMatcher doesn't like duplicates, and since we only
      // use the tree for true/false information anyway, we can remove them.
      bool already_exists =
          any_of(patterns.begin(), patterns.end(),
                 [&pattern](const MatcherStringPattern& existing_pattern) {
                   return existing_pattern.pattern() == pattern;
                 });
      if (!already_exists) {
        patterns.emplace_back(pattern, rule_index);
      }
      ++rule_index;
    }

    if (patterns.empty()) {
      continue;
    }

    auto substring_matcher = std::make_unique<SubstringSetMatcher>();
    if (!substring_matcher->Build(patterns)) {
      // Should never really happen unless there are megabytes and megabytes
      // of such classes, so we just drop out to the slow path.
    } else {
      substring_matcher_map.insert(attr, std::move(substring_matcher));
=======
    while (!pending_rules->IsEmpty()) {
      rules->push_back(pending_rules->Peek());
      pending_rules->Pop();
>>>>>>> chromium
    }
  }
}

void RuleSet::CompactRules() {
<<<<<<< HEAD
  DCHECK(need_compaction_);
  id_rules_.Compact();
  class_rules_.Compact();
  attr_rules_.Compact();
  CreateSubstringMatchers(attr_rules_, scope_intervals_,
                          attr_substring_matchers_);
  tag_rules_.Compact();
  ua_shadow_pseudo_element_rules_.Compact();
  link_pseudo_class_rules_.shrink_to_fit();
  cue_pseudo_rules_.shrink_to_fit();
  focus_pseudo_class_rules_.shrink_to_fit();
  selector_fragment_anchor_rules_.shrink_to_fit();
  focus_visible_pseudo_class_rules_.shrink_to_fit();
  universal_rules_.shrink_to_fit();
  shadow_host_rules_.shrink_to_fit();
  part_pseudo_rules_.shrink_to_fit();
  slotted_pseudo_element_rules_.shrink_to_fit();
  page_rules_.shrink_to_fit();
  font_face_rules_.shrink_to_fit();
  font_palette_values_rules_.shrink_to_fit();
  keyframes_rules_.shrink_to_fit();
  property_rules_.shrink_to_fit();
  counter_style_rules_.shrink_to_fit();
  position_try_rules_.shrink_to_fit();
  layer_intervals_.shrink_to_fit();
  view_transition_rules_.shrink_to_fit();
  bloom_hash_backing_.shrink_to_fit();

#if EXPENSIVE_DCHECKS_ARE_ON()
  if (!allow_unsorted_) {
    AssertRuleListsSorted();
  }
#endif
  need_compaction_ = false;
=======
  DCHECK(pending_rules_);
  PendingRuleMaps* pending_rules = pending_rules_.Release();
  CompactPendingRules(pending_rules->id_rules, id_rules_);
  CompactPendingRules(pending_rules->class_rules, class_rules_);
  CompactPendingRules(pending_rules->tag_rules, tag_rules_);
  CompactPendingRules(pending_rules->ua_shadow_pseudo_element_rules,
                      ua_shadow_pseudo_element_rules_);
  link_pseudo_class_rules_.ShrinkToFit();
  cue_pseudo_rules_.ShrinkToFit();
  focus_pseudo_class_rules_.ShrinkToFit();
  focus_visible_pseudo_class_rules_.ShrinkToFit();
  spatial_navigation_interest_class_rules_.ShrinkToFit();
  universal_rules_.ShrinkToFit();
  shadow_host_rules_.ShrinkToFit();
  part_pseudo_rules_.ShrinkToFit();
  visited_dependent_rules_.ShrinkToFit();
  page_rules_.ShrinkToFit();
  font_face_rules_.ShrinkToFit();
  keyframes_rules_.ShrinkToFit();
  property_rules_.ShrinkToFit();
  counter_style_rules_.ShrinkToFit();
  scroll_timeline_rules_.ShrinkToFit();
  slotted_pseudo_element_rules_.ShrinkToFit();
>>>>>>> chromium
}

bool RuleSet::DidMediaQueryResultsChange(
    const MediaQueryEvaluator& evaluator) const {
  return evaluator.DidResultsChange(media_query_set_results_);
}

void MinimalRuleData::Trace(Visitor* visitor) const {
  visitor->Trace(rule_);
}

const ContainerQuery* RuleData::GetContainerQuery() const {
  if (auto* extended = DynamicTo<ExtendedRuleData>(this))
    return extended->container_query_;
  return nullptr;
}

void RuleData::Trace(Visitor* visitor) const {
  switch (static_cast<Type>(type_)) {
    case Type::kNormal:
      TraceAfterDispatch(visitor);
      break;
    case Type::kExtended:
      To<ExtendedRuleData>(*this).TraceAfterDispatch(visitor);
      break;
  }
}

void RuleData::TraceAfterDispatch(blink::Visitor* visitor) const {
  visitor->Trace(rule_);
}

ExtendedRuleData::ExtendedRuleData(base::PassKey<RuleData>,
                                   StyleRule* rule,
                                   unsigned selector_index,
                                   unsigned position,
                                   AddRuleFlags flags,
                                   const ContainerQuery* container_query)
    : RuleData(Type::kExtended, rule, selector_index, position, flags),
      container_query_(container_query) {}

void ExtendedRuleData::TraceAfterDispatch(Visitor* visitor) const {
  RuleData::TraceAfterDispatch(visitor);
  visitor->Trace(container_query_);
}

void RuleSet::PendingRuleMaps::Trace(Visitor* visitor) const {
  visitor->Trace(id_rules);
  visitor->Trace(class_rules);
  visitor->Trace(tag_rules);
  visitor->Trace(ua_shadow_pseudo_element_rules);
}

void RuleSet::Trace(Visitor* visitor) const {
  visitor->Trace(id_rules_);
  visitor->Trace(class_rules_);
  visitor->Trace(tag_rules_);
  visitor->Trace(ua_shadow_pseudo_element_rules_);
  visitor->Trace(link_pseudo_class_rules_);
  visitor->Trace(cue_pseudo_rules_);
  visitor->Trace(focus_pseudo_class_rules_);
  visitor->Trace(focus_visible_pseudo_class_rules_);
  visitor->Trace(spatial_navigation_interest_class_rules_);
  visitor->Trace(universal_rules_);
  visitor->Trace(shadow_host_rules_);
  visitor->Trace(part_pseudo_rules_);
  visitor->Trace(visited_dependent_rules_);
  visitor->Trace(page_rules_);
  visitor->Trace(font_face_rules_);
  visitor->Trace(keyframes_rules_);
  visitor->Trace(property_rules_);
  visitor->Trace(counter_style_rules_);
  visitor->Trace(scroll_timeline_rules_);
  visitor->Trace(slotted_pseudo_element_rules_);
  visitor->Trace(pending_rules_);
#ifndef NDEBUG
  visitor->Trace(all_rules_);
#endif
}

#ifndef NDEBUG
void RuleSet::Show() const {
  for (const auto& rule : all_rules_)
    rule->Selector().Show();
}
#endif

}  // namespace blink
