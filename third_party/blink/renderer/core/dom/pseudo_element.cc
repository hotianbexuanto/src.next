/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
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

#include "third_party/blink/renderer/core/dom/pseudo_element.h"

#include <utility>

<<<<<<< HEAD
#include "third_party/blink/renderer/core/css/post_style_update_scope.h"
#include "third_party/blink/renderer/core/css/resolver/style_adjuster.h"
=======
>>>>>>> chromium
#include "third_party/blink/renderer/core/css/resolver/style_resolver.h"
#include "third_party/blink/renderer/core/dom/element_rare_data.h"
#include "third_party/blink/renderer/core/dom/first_letter_pseudo_element.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/dom/scroll_button_pseudo_element.h"
#include "third_party/blink/renderer/core/dom/scroll_marker_group_pseudo_element.h"
#include "third_party/blink/renderer/core/dom/scroll_marker_pseudo_element.h"
=======
#include "third_party/blink/renderer/core/dom/node_computed_style.h"
>>>>>>> chromium
#include "third_party/blink/renderer/core/frame/web_feature.h"
#include "third_party/blink/renderer/core/layout/generated_children.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"
#include "third_party/blink/renderer/core/layout/layout_quote.h"
#include "third_party/blink/renderer/core/layout/list_marker.h"
#include "third_party/blink/renderer/core/probe/core_probes.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/content_data.h"
#include "third_party/blink/renderer/platform/instrumentation/use_counter.h"

namespace blink {

<<<<<<< HEAD
using mojom::blink::FormControlType;

namespace {

// ::scroll-marker-group is represented internally as
// kPseudoIdScrollMarkerGroupBefore or kPseudoIdScrollMarkerGroupAfter,
// depending on scroll-marker property of originating element.
// But the have to resolve to kPseudoIdScrollMarkerGroup to
// correctly match CSS rules to the ::scroll-marker-group element.
PseudoId ResolvePseudoIdAlias(PseudoId pseudo_id) {
  switch (pseudo_id) {
    case kPseudoIdScrollMarkerGroupBefore:
    case kPseudoIdScrollMarkerGroupAfter:
      return kPseudoIdScrollMarkerGroup;
    default:
      return pseudo_id;
  }
}

}  // namespace

PseudoElement* PseudoElement::Create(Element* parent,
                                     PseudoId pseudo_id,
                                     const AtomicString& view_transition_name) {
  if (pseudo_id == kPseudoIdCheckMark) {
    CHECK(RuntimeEnabledFeatures::CustomizableSelectEnabled());

    if (!IsA<HTMLOptionElement>(parent)) {
      // The `::checkmark` pseudo element should only be created for option
      // elements.
      return nullptr;
    }
  }

  if (pseudo_id == kPseudoIdPickerIcon) {
    CHECK(RuntimeEnabledFeatures::CustomizableSelectEnabled());

    if (!IsA<HTMLSelectElement>(parent)) {
      // The `::picker-icon` pseudo element should only be created for select
      // elements.
      return nullptr;
    }
  }

  if (pseudo_id == kPseudoIdFirstLetter) {
    return MakeGarbageCollected<FirstLetterPseudoElement>(parent);
  } else if (IsTransitionPseudoElement(pseudo_id)) {
    auto* transition =
        ViewTransitionUtils::GetTransition(parent->GetDocument());
    DCHECK(transition);
    return transition->CreatePseudoElement(parent, pseudo_id,
                                           view_transition_name);
  } else if (ResolvePseudoIdAlias(pseudo_id) == kPseudoIdScrollMarkerGroup) {
    return MakeGarbageCollected<ScrollMarkerGroupPseudoElement>(parent,
                                                                pseudo_id);
  } else if (pseudo_id == kPseudoIdScrollMarker) {
    return MakeGarbageCollected<ScrollMarkerPseudoElement>(parent);
  } else if (pseudo_id == kPseudoIdScrollButtonBlockStart ||
             pseudo_id == kPseudoIdScrollButtonInlineStart ||
             pseudo_id == kPseudoIdScrollButtonInlineEnd ||
             pseudo_id == kPseudoIdScrollButtonBlockEnd) {
    return MakeGarbageCollected<ScrollButtonPseudoElement>(parent, pseudo_id);
  }
  DCHECK(pseudo_id == kPseudoIdAfter || pseudo_id == kPseudoIdBefore ||
         pseudo_id == kPseudoIdCheckMark || pseudo_id == kPseudoIdPickerIcon ||
         pseudo_id == kPseudoIdBackdrop || pseudo_id == kPseudoIdMarker ||
         pseudo_id == kPseudoIdColumn);
  return MakeGarbageCollected<PseudoElement>(parent, pseudo_id,
                                             view_transition_name);
=======
PseudoElement* PseudoElement::Create(Element* parent, PseudoId pseudo_id) {
  if (pseudo_id == kPseudoIdFirstLetter)
    return MakeGarbageCollected<FirstLetterPseudoElement>(parent);
  DCHECK(pseudo_id == kPseudoIdAfter || pseudo_id == kPseudoIdBefore ||
         pseudo_id == kPseudoIdBackdrop || pseudo_id == kPseudoIdMarker);
  return MakeGarbageCollected<PseudoElement>(parent, pseudo_id);
>>>>>>> chromium
}

const QualifiedName& PseudoElementTagName(PseudoId pseudo_id) {
  switch (pseudo_id) {
    case kPseudoIdAfter: {
      DEFINE_STATIC_LOCAL(QualifiedName, after,
                          (g_null_atom, "::after", g_null_atom));
      return after;
    }
    case kPseudoIdBefore: {
      DEFINE_STATIC_LOCAL(QualifiedName, before,
                          (g_null_atom, "::before", g_null_atom));
      return before;
    }
<<<<<<< HEAD
    case kPseudoIdCheckMark: {
      DEFINE_STATIC_LOCAL(QualifiedName, check, (AtomicString("::checkmark")));
      return check;
    }
    case kPseudoIdPickerIcon: {
      DEFINE_STATIC_LOCAL(QualifiedName, picker_icon,
                          (AtomicString("::picker-icon")));
      return picker_icon;
    }
=======
>>>>>>> chromium
    case kPseudoIdBackdrop: {
      DEFINE_STATIC_LOCAL(QualifiedName, backdrop,
                          (g_null_atom, "::backdrop", g_null_atom));
      return backdrop;
    }
    case kPseudoIdFirstLetter: {
      DEFINE_STATIC_LOCAL(QualifiedName, first_letter,
                          (g_null_atom, "::first-letter", g_null_atom));
      return first_letter;
    }
    case kPseudoIdMarker: {
      DEFINE_STATIC_LOCAL(QualifiedName, marker,
                          (g_null_atom, "::marker", g_null_atom));
      return marker;
    }
<<<<<<< HEAD
    case kPseudoIdScrollMarkerGroup: {
      DEFINE_STATIC_LOCAL(QualifiedName, scroll_marker_group,
                          (AtomicString("::scroll-marker-group")));
      return scroll_marker_group;
    }
    case kPseudoIdScrollButtonBlockStart: {
      DEFINE_STATIC_LOCAL(QualifiedName, scroll_button_block_start,
                          (AtomicString("::scroll-button(block-start)")));
      return scroll_button_block_start;
    }
    case kPseudoIdScrollButtonInlineStart: {
      DEFINE_STATIC_LOCAL(QualifiedName, scroll_button_inline_start,
                          (AtomicString("::scroll-button(inline-start)")));
      return scroll_button_inline_start;
    }
    case kPseudoIdScrollButtonInlineEnd: {
      DEFINE_STATIC_LOCAL(QualifiedName, scroll_button_inline_end,
                          (AtomicString("::scroll-button(inline-end)")));
      return scroll_button_inline_end;
    }
    case kPseudoIdScrollButtonBlockEnd: {
      DEFINE_STATIC_LOCAL(QualifiedName, scroll_button_block_end,
                          (AtomicString("::scroll-button(block-end)")));
      return scroll_button_block_end;
    }
    case kPseudoIdScrollMarker: {
      DEFINE_STATIC_LOCAL(QualifiedName, scroll_marker,
                          (AtomicString("::scroll-marker")));
      return scroll_marker;
    }
    case kPseudoIdViewTransition: {
      DEFINE_STATIC_LOCAL(QualifiedName, transition,
                          (AtomicString("::view-transition")));
      return transition;
    }
    case kPseudoIdViewTransitionGroup: {
      // TODO(khushalsagar) : Update these tag names to include the additional
      // ID.
      DEFINE_STATIC_LOCAL(QualifiedName, transition_container,
                          (AtomicString("::view-transition-group")));
      return transition_container;
    }
    case kPseudoIdViewTransitionImagePair: {
      DEFINE_STATIC_LOCAL(QualifiedName, transition_image_wrapper,
                          (AtomicString("::view-transition-image-pair")));
      return transition_image_wrapper;
    }
    case kPseudoIdViewTransitionNew: {
      DEFINE_STATIC_LOCAL(QualifiedName, transition_incoming_image,
                          (AtomicString("::view-transition-new")));
      return transition_incoming_image;
    }
    case kPseudoIdViewTransitionOld: {
      DEFINE_STATIC_LOCAL(QualifiedName, transition_outgoing_image,
                          (AtomicString("::view-transition-old")));
      return transition_outgoing_image;
    }
=======
>>>>>>> chromium
    default:
      NOTREACHED();
  }
  DEFINE_STATIC_LOCAL(QualifiedName, name,
                      (g_null_atom, "::unknown", g_null_atom));
  return name;
}

<<<<<<< HEAD
AtomicString PseudoElement::PseudoElementNameForEvents(Element* element) {
  DCHECK(element);
  auto pseudo_id = element->GetPseudoIdForStyling();

  switch (pseudo_id) {
    case kPseudoIdNone:
      return g_null_atom;
    case kPseudoIdViewTransitionGroup:
    case kPseudoIdViewTransitionImagePair:
    case kPseudoIdViewTransitionNew:
    case kPseudoIdViewTransitionOld: {
      auto* pseudo = To<PseudoElement>(element);
      DCHECK(pseudo);
      StringBuilder builder;
      builder.Append(PseudoElementTagName(pseudo_id).LocalName());
      builder.Append("(");
      if (pseudo->is_generated_name_) {
        builder.Append("match-element");
      } else {
        builder.Append(pseudo->view_transition_name());
      }
      builder.Append(")");
      return AtomicString(builder.ReleaseString());
    }
    default:
      break;
  }
  return PseudoElementTagName(pseudo_id).LocalName();
}

PseudoId PseudoElement::GetPseudoIdForStyling() const {
  return ResolvePseudoIdAlias(pseudo_id_);
=======
const AtomicString& PseudoElement::PseudoElementNameForEvents(
    PseudoId pseudo_id) {
  if (pseudo_id == kPseudoIdNone)
    return g_null_atom;
  else
    return PseudoElementTagName(pseudo_id).LocalName();
>>>>>>> chromium
}

bool PseudoElement::IsWebExposed(PseudoId pseudo_id, const Node* parent) {
  switch (pseudo_id) {
    case kPseudoIdMarker:
      if (parent && parent->IsPseudoElement())
        return RuntimeEnabledFeatures::CSSMarkerNestedPseudoElementEnabled();
      return true;
    default:
      return true;
  }
}

PseudoElement::PseudoElement(Element* parent, PseudoId pseudo_id)
    : Element(PseudoElementTagName(pseudo_id),
              &parent->GetDocument(),
              kCreateElement),
      pseudo_id_(pseudo_id) {
  DCHECK_NE(pseudo_id, kPseudoIdNone);
  parent->GetTreeScope().AdoptIfNeeded(*this);
  SetParentOrShadowHostNode(parent);
  SetHasCustomStyleCallbacks();
  if ((pseudo_id == kPseudoIdBefore || pseudo_id == kPseudoIdAfter) &&
      parent->HasTagName(html_names::kInputTag)) {
    UseCounter::Count(parent->GetDocument(),
                      WebFeature::kPseudoBeforeAfterForInputElement);
  }
}

scoped_refptr<ComputedStyle> PseudoElement::CustomStyleForLayoutObject(
    const StyleRecalcContext& style_recalc_context) {
  Element* parent = ParentOrShadowHostElement();
<<<<<<< HEAD
  // second condition is to temporary fix nested ::marker
  // on ::before and ::after when they are declared as display: list-item,
  // so that we don't lose e.g. list-style-type property.
  // TODO(373478544): remove second condition, once the flag is
  // flipped.
  if (RuntimeEnabledFeatures::CSSNestedPseudoElementsEnabled() ||
      (IsMarkerPseudoElement() && parentElement()->IsPseudoElement())) {
    return StyleForPseudoElement(
        style_recalc_context,
        StyleRequest(kPseudoIdNone, parent->GetComputedStyle(),
                     /* originating_element_style */ nullptr,
                     view_transition_name_));
  }
  return parent->StyleForPseudoElement(
      style_recalc_context,
      StyleRequest(GetPseudoIdForStyling(), parent->GetComputedStyle(),
                   /* originating_element_style */ nullptr,
                   view_transition_name_));
}

// static
bool PseudoElement::IsLayoutSiblingOfOriginatingElement(PseudoId pseudo_id) {
  return pseudo_id == kPseudoIdScrollButtonBlockStart ||
         pseudo_id == kPseudoIdScrollButtonInlineStart ||
         pseudo_id == kPseudoIdScrollButtonBlockEnd ||
         pseudo_id == kPseudoIdScrollButtonInlineEnd ||
         pseudo_id == kPseudoIdScrollButton ||
         pseudo_id == kPseudoIdScrollMarkerGroup ||
         pseudo_id == kPseudoIdScrollMarkerGroupAfter ||
         pseudo_id == kPseudoIdScrollMarkerGroupBefore;
}

const ComputedStyle* PseudoElement::AdjustedLayoutStyle(
    const ComputedStyle& style,
    const ComputedStyle& layout_parent_style) {
  if (style.Display() == EDisplay::kContents) {
    // For display:contents we should not generate a box, but we generate a non-
    // observable inline box for pseudo elements to be able to locate the
    // anonymous layout objects for generated content during DetachLayoutTree().
    ComputedStyleBuilder builder =
        GetDocument()
            .GetStyleResolver()
            .CreateComputedStyleBuilderInheritingFrom(style);
    builder.SetContent(style.GetContentData());
    builder.SetDisplay(EDisplay::kInline);
    builder.SetStyleType(GetPseudoIdForStyling());
    return builder.TakeStyle();
  }

  if (IsScrollMarkerPseudoElement()) {
    ComputedStyleBuilder builder(style);
    // The layout parent of a scroll marker is the scroll marker group, not
    // the originating element of the scroll marker.
    StyleAdjuster::AdjustStyleForDisplay(builder, layout_parent_style, this,
                                         &GetDocument());
    return builder.TakeStyle();
  }

  return nullptr;
=======
  return parent->StyleForPseudoElement(
      style_recalc_context,
      StyleRequest(pseudo_id_, parent->GetComputedStyle()));
}

scoped_refptr<ComputedStyle> PseudoElement::LayoutStyleForDisplayContents(
    const ComputedStyle& style) {
  // For display:contents we should not generate a box, but we generate a non-
  // observable inline box for pseudo elements to be able to locate the
  // anonymous layout objects for generated content during DetachLayoutTree().
  scoped_refptr<ComputedStyle> layout_style =
      GetDocument().GetStyleResolver().CreateComputedStyle();
  layout_style->InheritFrom(style);
  layout_style->SetContent(style.GetContentData());
  layout_style->SetDisplay(EDisplay::kInline);
  layout_style->SetStyleType(pseudo_id_);
  return layout_style;
>>>>>>> chromium
}

void PseudoElement::Dispose() {
  DCHECK(ParentOrShadowHostElement());

  probe::PseudoElementDestroyed(this);

  DCHECK(!nextSibling());
  DCHECK(!previousSibling());

  DetachLayoutTree();
  Element* parent = ParentOrShadowHostElement();
  GetDocument().AdoptIfNeeded(*this);
  SetParentOrShadowHostNode(nullptr);
  RemovedFrom(*parent);
}

PseudoElement::AttachLayoutTreeScope::AttachLayoutTreeScope(
    PseudoElement* element,
    const AttachContext& attach_context)
    : element_(element) {
  const ComputedStyle* style = element->GetComputedStyle();
  const LayoutObject* parent = attach_context.parent;
  if (!style || !parent) {
    return;
  }
  if (const ComputedStyle* adjusted_style =
          element->AdjustedLayoutStyle(*style, parent->StyleRef())) {
    original_style_ = style;
    element->SetComputedStyle(adjusted_style);
  }
}

PseudoElement::AttachLayoutTreeScope::~AttachLayoutTreeScope() {
  if (original_style_)
    element_->SetComputedStyle(std::move(original_style_));
}

void PseudoElement::AttachLayoutTree(AttachContext& context) {
  DCHECK(!GetLayoutObject());

  // Some elements may have 'display: list-item' but not be list items.
  // Do not create a layout object for the ::marker in that case.
  if (pseudo_id_ == kPseudoIdMarker) {
    LayoutObject* originating_layout = parentNode()->GetLayoutObject();
    if (!originating_layout || !originating_layout->IsListItemIncludingNG()) {
      Node::AttachLayoutTree(context);
      return;
    }
  }

  {
    AttachLayoutTreeScope scope(this, context);
    Element::AttachLayoutTree(context);
  }
  LayoutObject* layout_object = GetLayoutObject();
  if (!layout_object)
    return;

  // This is to ensure that bypassing the CanHaveGeneratedChildren() check in
  // LayoutTreeBuilderForElement::CreateLayoutObject() does not result in
  // the backdrop pseudo element's layout object becoming the child of a layout
  // object that doesn't allow children.
  DCHECK(layout_object->Parent());
  DCHECK(CanHaveGeneratedChildren(*layout_object->Parent()));

  const ComputedStyle& style = layout_object->StyleRef();
  switch (pseudo_id_) {
    case kPseudoIdMarker: {
      if (ListMarker* marker = ListMarker::Get(layout_object))
        marker->UpdateMarkerContentIfNeeded(*layout_object);
      if (style.ContentBehavesAsNormal())
        return;
      break;
    }
<<<<<<< HEAD
    case kPseudoIdScrollButtonBlockStart:
    case kPseudoIdScrollButtonInlineStart:
    case kPseudoIdScrollButtonInlineEnd:
    case kPseudoIdScrollButtonBlockEnd:
      if (style.ContentBehavesAsNormal()) {
        context.counters_context.LeaveObject(*layout_object);
        return;
      }
      break;
    case kPseudoIdCheckMark:
    case kPseudoIdBefore:
    case kPseudoIdAfter:
    case kPseudoIdPickerIcon:
    case kPseudoIdScrollMarker:
      break;
    default: {
      context.counters_context.LeaveObject(*layout_object);
=======
    case kPseudoIdBefore:
    case kPseudoIdAfter:
      break;
    default:
>>>>>>> chromium
      return;
  }

  DCHECK(!style.ContentBehavesAsNormal());
  DCHECK(!style.ContentPreventsBoxGeneration());
  for (const ContentData* content = style.GetContentData(); content;
       content = content->Next()) {
    LegacyLayout legacy = context.force_legacy_layout ? LegacyLayout::kForce
                                                      : LegacyLayout::kAuto;
    if (!content->IsAltText()) {
      LayoutObject* child = content->CreateLayoutObject(*this, style, legacy);
      if (layout_object->IsChildAllowed(child, style)) {
        layout_object->AddChild(child);
        if (child->IsQuote())
          To<LayoutQuote>(child)->AttachQuote();
      } else {
        child->Destroy();
      }
    }
  }
}

<<<<<<< HEAD
bool PseudoElement::CanGenerateContent() const {
  switch (GetPseudoIdForStyling()) {
    case kPseudoIdMarker:
    case kPseudoIdCheckMark:
    case kPseudoIdBefore:
    case kPseudoIdAfter:
    case kPseudoIdPickerIcon:
    case kPseudoIdScrollMarker:
    case kPseudoIdScrollMarkerGroup:
    case kPseudoIdScrollButtonBlockStart:
    case kPseudoIdScrollButtonInlineStart:
    case kPseudoIdScrollButtonInlineEnd:
    case kPseudoIdScrollButtonBlockEnd:
      return true;
    default:
      return false;
  }
}

bool PseudoElement::LayoutObjectIsNeeded(const DisplayStyle& style) const {
  return PseudoElementLayoutObjectIsNeeded(GetPseudoId(), style,
                                           parentElement());
}

// Keep in sync with CanGeneratePseudoElement.
bool PseudoElement::CanHaveNestedPseudoElement() const {
  switch (GetPseudoId()) {
    case kPseudoIdBefore:
    case kPseudoIdAfter:
    case kPseudoIdColumn:
      return true;
    default:
      return false;
  }
}

// Keep in sync with CanHaveNestedPseudoElement.
bool PseudoElement::CanGeneratePseudoElement(PseudoId pseudo_id) const {
  switch (GetPseudoId()) {
=======
bool PseudoElement::LayoutObjectIsNeeded(const ComputedStyle& style) const {
  return PseudoElementLayoutObjectIsNeeded(&style, parentElement());
}

bool PseudoElement::CanGeneratePseudoElement(PseudoId pseudo_id) const {
  switch (pseudo_id_) {
>>>>>>> chromium
    case kPseudoIdBefore:
    case kPseudoIdAfter:
      if (pseudo_id != kPseudoIdMarker)
        return false;
      break;
    default:
      return false;
  }
  return Element::CanGeneratePseudoElement(pseudo_id);
}

Node* PseudoElement::InnerNodeForHitTesting() const {
  Node* parent = ParentOrShadowHostNode();
  if (parent && parent->IsPseudoElement())
    return To<PseudoElement>(parent)->InnerNodeForHitTesting();
  return parent;
}

bool PseudoElementLayoutObjectIsNeeded(const ComputedStyle* pseudo_style,
                                       const Element* originating_element) {
  if (!pseudo_style)
    return false;
  if (pseudo_style->Display() == EDisplay::kNone)
    return false;
  switch (pseudo_style->StyleType()) {
    case kPseudoIdFirstLetter:
    case kPseudoIdBackdrop:
      return true;
<<<<<<< HEAD
    case kPseudoIdCheckMark:
    case kPseudoIdBefore:
    case kPseudoIdAfter:
    case kPseudoIdPickerIcon:
      return !pseudo_style.ContentPreventsBoxGeneration();
    case kPseudoIdScrollMarker:
    case kPseudoIdScrollButtonBlockStart:
    case kPseudoIdScrollButtonInlineStart:
    case kPseudoIdScrollButtonInlineEnd:
    case kPseudoIdScrollButtonBlockEnd:
      return !pseudo_style.ContentBehavesAsNormal();
=======
    case kPseudoIdBefore:
    case kPseudoIdAfter:
      return !pseudo_style->ContentPreventsBoxGeneration();
>>>>>>> chromium
    case kPseudoIdMarker: {
      if (!pseudo_style->ContentBehavesAsNormal())
        return !pseudo_style->ContentPreventsBoxGeneration();
      const ComputedStyle* parent_style =
          originating_element->GetComputedStyle();
      return parent_style && (parent_style->ListStyleType() ||
                              parent_style->GeneratesMarkerImage());
    }
    default:
      NOTREACHED();
      return false;
  }
}

}  // namespace blink
