// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/test/scoped_feature_list.h"
#include "testing/gtest/include/gtest/gtest.h"
<<<<<<< HEAD
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/renderer/core/dom/shadow_root.h"
=======
#include "third_party/blink/renderer/core/dom/node_computed_style.h"
>>>>>>> chromium
#include "third_party/blink/renderer/core/frame/event_handler_registry.h"
#include "third_party/blink/renderer/core/testing/core_unit_test_helper.h"
#include "third_party/blink/renderer/platform/testing/runtime_enabled_features_test_helpers.h"
#include "ui/base/ui_base_features.h"

namespace blink {

class StyleAdjusterTest : public RenderingTest {
 public:
  StyleAdjusterTest()
      : RenderingTest(MakeGarbageCollected<SingleChildLocalFrameClient>()) {}
};

TEST_F(StyleAdjusterTest, TouchActionPropagatedAcrossIframes) {
  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <style>body { margin: 0; } iframe { display: block; } </style>
    <iframe id='owner' src='http://test.com' width='500' height='500'
    style='touch-action: none'>
    </iframe>
  )HTML");
  SetChildFrameHTML(R"HTML(
    <style>body { margin: 0; } #target { width: 200px; height: 200px; }
    </style>
    <div id='target' style='touch-action: pinch-zoom'></div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();

  Element* target = ChildDocument().getElementById("target");
  EXPECT_EQ(TouchAction::kNone,
            target->GetComputedStyle()->GetEffectiveTouchAction());

  Element* owner = GetDocument().getElementById("owner");
  owner->setAttribute(html_names::kStyleAttr, "touch-action: auto");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_EQ(TouchAction::kPinchZoom,
            target->GetComputedStyle()->GetEffectiveTouchAction());
}

TEST_F(StyleAdjusterTest, TouchActionPanningReEnabledByScrollers) {
  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <style>#ancestor { margin: 0; touch-action: pinch-zoom; }
    #scroller { overflow: scroll; width: 100px; height: 100px; }
    #target { width: 200px; height: 200px; } </style>
    <div id='ancestor'><div id='scroller'><div id='target'>
    </div></div></div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();

<<<<<<< HEAD
  Element* target = GetDocument().getElementById(AtomicString("target"));
  EXPECT_EQ((TouchAction::kManipulation & ~TouchAction::kInternalHandwriting) |
                TouchAction::kInternalPanXScrolls |
                TouchAction::kInternalNotWritable,
            target->GetComputedStyle()->EffectiveTouchAction());
=======
  Element* target = GetDocument().getElementById("target");
  EXPECT_EQ(TouchAction::kManipulation | TouchAction::kInternalPanXScrolls,
            target->GetComputedStyle()->GetEffectiveTouchAction());
>>>>>>> chromium
}

TEST_F(StyleAdjusterTest, TouchActionPropagatedWhenAncestorStyleChanges) {
  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <style>#ancestor { margin: 0; touch-action: pan-x; }
    #potential-scroller { width: 100px; height: 100px; overflow: hidden; }
    #target { width: 200px; height: 200px; }</style>
    <div id='ancestor'><div id='potential-scroller'><div id='target'>
    </div></div></div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();

  Element* target = GetDocument().getElementById("target");
  EXPECT_EQ(TouchAction::kPanX | TouchAction::kInternalPanXScrolls,
            target->GetComputedStyle()->GetEffectiveTouchAction());

  Element* ancestor = GetDocument().getElementById("ancestor");
  ancestor->setAttribute(html_names::kStyleAttr, "touch-action: pan-y");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_EQ(TouchAction::kPanY,
            target->GetComputedStyle()->GetEffectiveTouchAction());

  Element* potential_scroller =
      GetDocument().getElementById("potential-scroller");
  potential_scroller->setAttribute(html_names::kStyleAttr, "overflow: scroll");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_EQ(TouchAction::kPan | TouchAction::kInternalPanXScrolls,
            target->GetComputedStyle()->GetEffectiveTouchAction());
}

TEST_F(StyleAdjusterTest, TouchActionRestrictedByLowerAncestor) {
  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <div id='ancestor' style='touch-action: pan'>
    <div id='parent' style='touch-action: pan-right pan-y'>
    <div id='target' style='touch-action: pan-x'>
    </div></div></div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();

  Element* target = GetDocument().getElementById("target");
  EXPECT_EQ(TouchAction::kPanRight | TouchAction::kInternalPanXScrolls,
            target->GetComputedStyle()->GetEffectiveTouchAction());

  Element* parent = GetDocument().getElementById("parent");
  parent->setAttribute(html_names::kStyleAttr, "touch-action: auto");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_EQ(TouchAction::kPanX | TouchAction::kInternalPanXScrolls,
            target->GetComputedStyle()->GetEffectiveTouchAction());
}

TEST_F(StyleAdjusterTest, AdjustOverflow) {
  ScopedOverflowClipForTest overflow_clip_feature_enabler(true);
  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <div id='clipauto' style='overflow-x: clip; overflow-y: auto;
         overflow-clip-margin: 1px;'>
    <div id='autoclip' style='overflow-x: auto; overflow-y: clip;
         overflow-clip-margin: 1px;'>
    <div id='clipclip' style='overflow-x: clip; overflow-y: clip;
         overflow-clip-margin: 1px;'>
    <div id='visclip' style='overflow-x: visible; overflow-y: clip;
         overflow-clip-margin: 1px;'>
    <div id='clipvis' style='overflow-x: clip; overflow-y: visible;
         overflow-clip-margin: 1px;'>
    <div id='hiddenvis' style='overflow-x: hidden; overflow-y: visible;
         overflow-clip-margin: 1px;'>
    <div id='vishidden' style='overflow-x: visible; overflow-y: hidden;
         overflow-clip-margin: 1px;'>
    <div id='containpaint' style='contain: paint; overflow-clip-margin: 1px;'>
    </div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();

  Element* target = GetDocument().getElementById("clipauto");
  ASSERT_TRUE(target);
  EXPECT_EQ(EOverflow::kHidden, target->GetComputedStyle()->OverflowX());
  EXPECT_EQ(EOverflow::kAuto, target->GetComputedStyle()->OverflowY());
  EXPECT_EQ(LayoutUnit(), target->GetComputedStyle()->OverflowClipMargin());

  target = GetDocument().getElementById("autoclip");
  ASSERT_TRUE(target);
  EXPECT_EQ(EOverflow::kAuto, target->GetComputedStyle()->OverflowX());
  EXPECT_EQ(EOverflow::kHidden, target->GetComputedStyle()->OverflowY());
  EXPECT_EQ(LayoutUnit(), target->GetComputedStyle()->OverflowClipMargin());

  target = GetDocument().getElementById("clipclip");
  ASSERT_TRUE(target);
  EXPECT_EQ(EOverflow::kClip, target->GetComputedStyle()->OverflowX());
  EXPECT_EQ(EOverflow::kClip, target->GetComputedStyle()->OverflowY());
  EXPECT_EQ(LayoutUnit(1), target->GetComputedStyle()->OverflowClipMargin());

  target = GetDocument().getElementById("visclip");
  ASSERT_TRUE(target);
  EXPECT_EQ(EOverflow::kVisible, target->GetComputedStyle()->OverflowX());
  EXPECT_EQ(EOverflow::kClip, target->GetComputedStyle()->OverflowY());
  EXPECT_EQ(LayoutUnit(), target->GetComputedStyle()->OverflowClipMargin());

  target = GetDocument().getElementById("clipvis");
  ASSERT_TRUE(target);
  EXPECT_EQ(EOverflow::kClip, target->GetComputedStyle()->OverflowX());
  EXPECT_EQ(EOverflow::kVisible, target->GetComputedStyle()->OverflowY());
  EXPECT_EQ(LayoutUnit(), target->GetComputedStyle()->OverflowClipMargin());

  target = GetDocument().getElementById("vishidden");
  ASSERT_TRUE(target);
  EXPECT_EQ(EOverflow::kAuto, target->GetComputedStyle()->OverflowX());
  EXPECT_EQ(EOverflow::kHidden, target->GetComputedStyle()->OverflowY());
  EXPECT_EQ(LayoutUnit(), target->GetComputedStyle()->OverflowClipMargin());

  target = GetDocument().getElementById("hiddenvis");
  ASSERT_TRUE(target);
  EXPECT_EQ(EOverflow::kHidden, target->GetComputedStyle()->OverflowX());
  EXPECT_EQ(EOverflow::kAuto, target->GetComputedStyle()->OverflowY());
  EXPECT_EQ(LayoutUnit(), target->GetComputedStyle()->OverflowClipMargin());

  target = GetDocument().getElementById("containpaint");
  ASSERT_TRUE(target);
  EXPECT_TRUE(target->GetComputedStyle()->ContainsPaint());
  EXPECT_EQ(LayoutUnit(1), target->GetComputedStyle()->OverflowClipMargin());
}

TEST_F(StyleAdjusterTest, TouchActionContentEditableArea) {
  base::test::ScopedFeatureList feature_list;
  feature_list.InitWithFeatures({::features::kSwipeToMoveCursor}, {});
  if (!::features::IsSwipeToMoveCursorEnabled())
    return;

  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <div id='editable1' contenteditable='false'></div>
    <input type="text" id='input1' disabled>
    <textarea id="textarea1" readonly></textarea>
    <div id='editable2' contenteditable='true'></div>
    <input type="text" id='input2'>
    <textarea id="textarea2"></textarea>
  )HTML");
  UpdateAllLifecyclePhasesForTest();

  EXPECT_EQ(TouchAction::kAuto, GetDocument()
                                    .getElementById("editable1")
                                    ->GetComputedStyle()
                                    ->GetEffectiveTouchAction());
  EXPECT_EQ(TouchAction::kAuto, GetDocument()
                                    .getElementById("input1")
                                    ->GetComputedStyle()
                                    ->GetEffectiveTouchAction());
  EXPECT_EQ(TouchAction::kAuto, GetDocument()
                                    .getElementById("textarea1")
                                    ->GetComputedStyle()
                                    ->GetEffectiveTouchAction());
  EXPECT_EQ(TouchAction::kAuto & ~TouchAction::kInternalPanXScrolls,
            GetDocument()
                .getElementById("editable2")
                ->GetComputedStyle()
                ->GetEffectiveTouchAction());
  EXPECT_EQ(TouchAction::kAuto & ~TouchAction::kInternalPanXScrolls,
            GetDocument()
                .getElementById("input2")
                ->GetComputedStyle()
                ->GetEffectiveTouchAction());
  EXPECT_EQ(TouchAction::kAuto & ~TouchAction::kInternalPanXScrolls,
            GetDocument()
                .getElementById("textarea2")
                ->GetComputedStyle()
                ->GetEffectiveTouchAction());

  Element* target = GetDocument().getElementById("editable1");
  target->setAttribute(html_names::kContenteditableAttr, "true");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_EQ(TouchAction::kAuto & ~TouchAction::kInternalPanXScrolls,
            target->GetComputedStyle()->GetEffectiveTouchAction());
}

TEST_F(StyleAdjusterTest, TouchActionNoPanXScrollsWhenNoPanX) {
  base::test::ScopedFeatureList feature_list;
  feature_list.InitWithFeatures({::features::kSwipeToMoveCursor}, {});
  if (!::features::IsSwipeToMoveCursorEnabled())
    return;

  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <div id='target' contenteditable='false' style='touch-action: pan-y'></div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();

  Element* target = GetDocument().getElementById("target");
  EXPECT_EQ(TouchAction::kPanY,
            target->GetComputedStyle()->GetEffectiveTouchAction());

  target->setAttribute(html_names::kContenteditableAttr, "true");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_EQ(TouchAction::kPanY,
            target->GetComputedStyle()->GetEffectiveTouchAction());
}

// Non-writable elements shouldn't signal that they would lose handwriting
// capabilities.
TEST_F(StyleAdjusterTest, TouchActionHandwriting_NotWritable) {
  SetBodyInnerHTML(R"HTML(
    <div style="width: 100px; height: 100px;"/>
  )HTML");
  EXPECT_FALSE(GetDocument().IsUseCounted(
      WebFeature::kNonNoneTouchActionWouldLoseEditableHandwriting));
}

// Non-writable elements shouldn't signal that they would lose handwriting
// capabilities even if `touch-action` is specified.
TEST_F(StyleAdjusterTest, TouchActionHandwriting_NotWritableTouchAction) {
  SetBodyInnerHTML(R"HTML(
    <div style="touch-action: pan-x; width: 100px; height: 100px;"/>
  )HTML");
  EXPECT_FALSE(GetDocument().IsUseCounted(
      WebFeature::kNonNoneTouchActionWouldLoseEditableHandwriting));
}

// Writable elements shouldn't signal that they would lose handwriting
// capabilities if `touch-action` is not specified.
TEST_F(StyleAdjusterTest, TouchActionHandwriting_NoTouchAction) {
  SetBodyInnerHTML(R"HTML(
    <input type="text" style="width: 100px; height: 100px;"></input>
  )HTML");
  EXPECT_FALSE(GetDocument().IsUseCounted(
      WebFeature::kNonNoneTouchActionWouldLoseEditableHandwriting));
}

// Writable elements shouldn't signal that they would lose handwriting
// capabilities if `touch-action: auto` is specified.
TEST_F(StyleAdjusterTest, TouchActionHandwriting_Auto) {
  SetBodyInnerHTML(R"HTML(
    <input style="touch-action:auto; height:100px; width:100px" type="text"/>
  )HTML");
  EXPECT_FALSE(GetDocument().IsUseCounted(
      WebFeature::kNonNoneTouchActionWouldLoseEditableHandwriting));
}

// Writable elements shouldn't signal that they would lose handwriting
// capabilities if `touch-action: manipulation` is specified.
TEST_F(StyleAdjusterTest, TouchActionHandwriting_Manipulation) {
  SetBodyInnerHTML(R"HTML(
    <input style="touch-action:manipulation; height:100px; width:100px"
      type="text"/>
  )HTML");
  EXPECT_FALSE(GetDocument().IsUseCounted(
      WebFeature::kNonNoneTouchActionWouldLoseEditableHandwriting));
}

// Writable elements shouldn't signal that they would lose handwriting
// capabilities if `touch-action: none` is specified, as handwriting would be
// intentionally disabled.
TEST_F(StyleAdjusterTest, TouchActionHandwriting_TouchActionNone) {
  SetBodyInnerHTML(R"HTML(
    <input style="touch-action:none; height:100px; width:100px"
      type="text"/>
  )HTML");
  EXPECT_FALSE(GetDocument().IsUseCounted(
      WebFeature::kNonNoneTouchActionWouldLoseEditableHandwriting));
}

// Writable elements should signal that they would lose handwriting
// capabilities if `touch-action` is specified with a value other than
// `manipulation` or `auto`.
TEST_F(StyleAdjusterTest, TouchActionHandwriting_TouchActionDeclared) {
  SetBodyInnerHTML(R"HTML(
    <input style="touch-action:pan-x pan-y pinch-zoom; height:100px; width:100px"
      type="text"/>
  )HTML");
  EXPECT_TRUE(GetDocument().IsUseCounted(
      WebFeature::kNonNoneTouchActionWouldLoseEditableHandwriting));
}

TEST_F(StyleAdjusterTest, OverflowClipUseCount) {
  GetDocument().SetBaseURLOverride(KURL("http://test.com"));
  SetBodyInnerHTML(R"HTML(
    <div></div>
    <div style='overflow: hidden'></div>
    <div style='overflow: scroll'></div>
    <div></div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_FALSE(
      GetDocument().IsUseCounted(WebFeature::kOverflowClipAlongEitherAxis));

  SetBodyInnerHTML(R"HTML(
    <div style='overflow: clip'></div>
  )HTML");
  UpdateAllLifecyclePhasesForTest();
  EXPECT_TRUE(
      GetDocument().IsUseCounted(WebFeature::kOverflowClipAlongEitherAxis));
}

// crbug.com/392643253
TEST_F(StyleAdjusterTest, AdjustForDisplayInlinify) {
  SetBodyInnerHTML(R"HTML(<ruby><video></video><audio></audio></ruby>)HTML");
  UpdateAllLifecyclePhasesForTest();
  // Pass if no crashes.
}

// crbug.com/1216721
TEST_F(StyleAdjusterTest, AdjustForSVGCrash) {
  SetBodyInnerHTML(R"HTML(
<style>
.class1 { dominant-baseline: hanging; }
</style>
<svg>
<tref>
<text id="text5" style="dominant-baseline: no-change;"/>
</svg>
<svg>
<use id="use1" xlink:href="#text5" class="class1" />
  )HTML");
  UpdateAllLifecyclePhasesForTest();
  Element* text =
      GetDocument().getElementById("use1")->GetShadowRoot()->getElementById(
          "text5");
  EXPECT_EQ(EDominantBaseline::kHanging,
            text->GetComputedStyle()->CssDominantBaseline());
}

}  // namespace blink
