// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CONTAINER_QUERY_EVALUATOR_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CONTAINER_QUERY_EVALUATOR_H_

#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/css/media_query_evaluator.h"
#include "third_party/blink/renderer/core/layout/geometry/axis.h"
#include "third_party/blink/renderer/core/layout/geometry/physical_size.h"
#include "third_party/blink/renderer/platform/heap/handle.h"

namespace blink {

class ContainerQuery;
class Element;
class StyleRecalcContext;

class CORE_EXPORT ContainerQueryEvaluator final
    : public GarbageCollected<ContainerQueryEvaluator> {
 public:
  static Element* FindContainer(const StyleRecalcContext& context,
                                const AtomicString& container_name);

  // Creates an evaluator with no containment, hence all queries evaluated
  // against it will fail.
  ContainerQueryEvaluator() = default;

<<<<<<< HEAD
  // Width/Height are used by container relative units (qi, qb, etc).
  //
  // A return value of std::nullopt normally means that the relevant axis
  // doesn't have effective containment (e.g. elements with display:table).
  //
  // https://drafts.csswg.org/css-contain-2/#containment-size
  std::optional<double> Width() const;
  std::optional<double> Height() const;
  void SetReferencedByUnit() { referenced_by_unit_ = true; }
  bool DependsOnStyle() const { return depends_on_style_; }
  bool DependsOnStuck() const { return depends_on_stuck_; }
  bool DependsOnSnapped() const { return depends_on_snapped_; }
  bool DependsOnScrollable() const { return depends_on_scrollable_; }
  bool DependsOnSize() const { return depends_on_size_; }
  bool MayDependOnWritingDirection() const {
    return DependsOnSize() || DependsOnStuck() || DependsOnSnapped() ||
           DependsOnScrollable();
=======
  // Used by container relative units (qi, qb, etc).
  double Width() const;
  double Height() const;
  void SetReferencedByUnit() { referenced_by_unit_ = true; }

  bool Eval(const ContainerQuery&) const;

  // Add a dependent query to this evaluator. During calls to ContainerChanged,
  // all dependent queries are checked to see if the new size/axis information
  // causes a change in the evaluation result.
  void Add(const ContainerQuery&, bool result);

  bool EvalAndAdd(const ContainerQuery& query) {
    bool result = Eval(query);
    Add(query, result);
    return result;
>>>>>>> chromium
  }

  enum class Change {
    // The update has no effect on the evaluation of queries associated with
    // this evaluator, and therefore we do not need to perform style recalc of
    // any elements which depend on this evaluator.
    kNone,
    // The update can only affect elements for which this container is the
    // nearest container. In other words, we do not need to recalculate style
    // for elements in nested containers.
    kNearestContainer,
    // The update can affect elements within this container, and also in
    // descendant containers.
    kDescendantContainers,
  };

  // Update the size/axis information of the evaluator.
  //
  // Dependent queries are cleared when kUnnamed/kNamed is returned (and left
  // unchanged otherwise).
  Change ContainerChanged(PhysicalSize, PhysicalAxes contained_axes);

  void Trace(Visitor*) const;

 private:
<<<<<<< HEAD
  friend class ContainerQueryEvaluatorTest;

  // Reconstruct CSSContainerValues based on the current ComputedStyle stored on
  // the container element, but otherwise keep other values the same.
  void UpdateContainerValues();

  // Re-evaluate the cached results and clear any results which are affected.
  Change StyleContainerChanged();

  // Update the ContainerValues for the evaluator if necessary based on the
  // latest snapshots for stuck and snapped states.
  Change ApplyScrollState();

  // Re-evaluate results of size queries which may have changed for computed
  // style changes like font and writing direction.
  Change StyleAffectingSizeChanged();

  // Re-evaluate results of scroll-state() queries which may have changed for
  // computed style changes like writing direction.
  Change StyleAffectingScrollStateChanged();

  // Update the CSSContainerValues with the new size and contained axes to be
  // used for queries.
  void UpdateContainerSize(PhysicalSize, PhysicalAxes contained_axes);

  // Update the CSSContainerValues with the new stuck state.
  void UpdateContainerStuck(ContainerStuckPhysical stuck_horizontal,
                            ContainerStuckPhysical stuck_vertical);

  // Update the CSSContainerValues with the new stuck state.
  void UpdateContainerSnapped(ContainerSnappedFlags snapped);

  // Update the CSSContainerValues with the new overflowing state.
  void UpdateContainerScrollable(ContainerScrollableFlags scrollable_horizontal,
                                 ContainerScrollableFlags scrollable_vertical);

  // Re-evaluate the cached results and clear any results which are affected by
  // the ContainerStuckPhysical changes.
  Change StickyContainerChanged(ContainerStuckPhysical stuck_horizontal,
                                ContainerStuckPhysical stuck_vertical);

  // Re-evaluate the cached results and clear any results which are affected by
  // the snapped target changes.
  Change SnapContainerChanged(ContainerSnappedFlags snapped);

  // Re-evaluate the cached results and clear any results which are affected by
  // the snapped target changes.
  Change ScrollableContainerChanged(
      ContainerScrollableFlags scrollable_horizontal,
      ContainerScrollableFlags scrollable_vertical);

  enum ContainerType {
    kSizeContainer,
    kStyleContainer,
    kStickyContainer,
    kSnapContainer,
    kScrollableContainer,
  };
  void ClearResults(Change change, ContainerType container_type);

  // Re-evaluate cached query results after a size change and return which
  // elements need to be invalidated if necessary.
  Change ComputeSizeChange() const;

  // Re-evaluate cached query results after a style change and return which
  // elements need to be invalidated if necessary.
  Change ComputeStyleChange() const;

  // Re-evaluate cached query results after a stuck state change and return
  // which elements need to be invalidated if necessary.
  Change ComputeStickyChange() const;

  // Re-evaluate cached query results after a snapped state change and return
  // which elements need to be invalidated if necessary.
  Change ComputeSnapChange() const;

  // Re-evaluate cached query results after a overflowing state change and
  // return which elements need to be invalidated if necessary.
  Change ComputeOverflowChange() const;

  struct Result {
    // Main evaluation result.
    bool value = false;
    // The units that were relevant for the result.
    // See `MediaQueryExpValue::UnitFlags`.
    unsigned unit_flags : MediaQueryExpValue::kUnitFlagsBits;
    // Indicates what we need to invalidate if the result value changes.
    Change change = Change::kNone;
  };

  Result Eval(const ContainerQuery&) const;

  // Evaluate and add a dependent query to this evaluator. During calls to
  // SizeContainerChanged/StyleChanged, all dependent queries are checked to see
  // if the new size/axis or computed style information causes a change in the
  // evaluation result.
  bool EvalAndAdd(const ContainerQuery& query,
                  Change change,
                  MatchResult& match_result);
=======
  void SetData(PhysicalSize, PhysicalAxes contained_axes);
  void ClearResults();
  Change ComputeChange() const;
>>>>>>> chromium

  // TODO(crbug.com/1145970): Don't lean on MediaQueryEvaluator.
  Member<MediaQueryEvaluator> media_query_evaluator_;
  PhysicalSize size_;
  PhysicalAxes contained_axes_;
<<<<<<< HEAD
  ContainerStuckPhysical stuck_horizontal_ = ContainerStuckPhysical::kNo;
  ContainerStuckPhysical stuck_vertical_ = ContainerStuckPhysical::kNo;
  ContainerSnappedFlags snapped_ =
      static_cast<ContainerSnappedFlags>(ContainerSnapped::kNone);
  ContainerSnappedFlags pending_snapped_ =
      static_cast<ContainerSnappedFlags>(ContainerSnapped::kNone);
  ContainerScrollableFlags scrollable_horizontal_ =
      static_cast<ContainerScrollableFlags>(ContainerScrollable::kNone);
  ContainerScrollableFlags scrollable_vertical_ =
      static_cast<ContainerScrollableFlags>(ContainerScrollable::kNone);
  HeapHashMap<Member<const ContainerQuery>, Result> results_;
  Member<ScrollStateQuerySnapshot> scroll_state_snapshot_;
  // The MediaQueryExpValue::UnitFlags of all queries evaluated against this
  // ContainerQueryEvaluator.
  unsigned unit_flags_ = 0;
  bool referenced_by_unit_ = false;
  bool depends_on_style_ = false;
  bool depends_on_stuck_ = false;
  bool depends_on_snapped_ = false;
  bool depends_on_scrollable_ = false;
  bool depends_on_size_ = false;
=======
  HeapHashMap<Member<const ContainerQuery>, bool> results_;
  bool referenced_by_unit_ = false;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CONTAINER_QUERY_EVALUATOR_H_
