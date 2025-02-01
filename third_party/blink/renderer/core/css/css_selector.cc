/*
 * Copyright (C) 1999-2003 Lars Knoll (knoll@kde.org)
 *               1999 Waldo Bastian (bastian@kde.org)
 *               2001 Andreas Schlapbach (schlpbch@iam.unibe.ch)
 *               2001-2003 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2002, 2006, 2007, 2008, 2009, 2010 Apple Inc. All rights
 * reserved.
 * Copyright (C) 2008 David Smith (catfish.man@gmail.com)
 * Copyright (C) 2010 Google Inc. All rights reserved.
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

#include "third_party/blink/renderer/core/css/css_selector.h"

#include <algorithm>
#include <memory>

#include "base/cxx17_backports.h"
#include "third_party/blink/renderer/core/css/css_markup.h"
#include "third_party/blink/renderer/core/css/css_selector_list.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_context.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_token_range.h"
#include "third_party/blink/renderer/core/css/parser/css_selector_parser.h"
#include "third_party/blink/renderer/core/css/parser/css_tokenizer.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/pseudo_element.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/origin_trials/origin_trials.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/hash_map.h"
#include "third_party/blink/renderer/platform/wtf/size_assertions.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

namespace blink {

namespace {

<<<<<<< HEAD
constexpr bool kExpandPseudoReferences = true;

=======
>>>>>>> chromium
unsigned MaximumSpecificity(const CSSSelectorList* list) {
  if (!list)
    return 0;

  unsigned result = 0;
  const CSSSelector* selector;
  for (selector = list->First(); selector;
       selector = CSSSelectorList::Next(*selector)) {
    unsigned specificity = selector->Specificity();
    if (result < specificity)
      result = specificity;
  }
  return result;
}

}  // namespace

struct SameSizeAsCSSSelector {
  unsigned bitfields;
  void* pointers[1];
};

ASSERT_SIZE(CSSSelector, SameSizeAsCSSSelector);

<<<<<<< HEAD
CSSSelector::CSSSelector(MatchType match_type,
                         const QualifiedName& attribute,
                         AttributeMatchType case_sensitivity)
    : bits_(
          RelationField::encode(kSubSelector) | MatchField::encode(match_type) |
          PseudoTypeField::encode(kPseudoUnknown) |
          IsLastInSelectorListField::encode(false) |
          IsLastInComplexSelectorField::encode(false) |
          HasRareDataField::encode(false) | IsForPageField::encode(false) |
          IsImplicitlyAddedField::encode(false) |
          IsCoveredByBucketingField::encode(false) |
          AttributeMatchField::encode(static_cast<unsigned>(case_sensitivity)) |
          LegacyCaseInsensitiveMatchField::encode(
              !HTMLDocument::IsCaseSensitiveAttribute(attribute) &&
              case_sensitivity != AttributeMatchType::kCaseSensitiveAlways) |
          IsScopeContainingField::encode(false)),
      data_(attribute) {
  DCHECK_EQ(match_type, kAttributeSet);
}

CSSSelector::CSSSelector(MatchType match_type,
                         const QualifiedName& attribute,
                         AttributeMatchType case_sensitivity,
                         const AtomicString& value)
    : bits_(
          RelationField::encode(kSubSelector) |
          MatchField::encode(static_cast<unsigned>(match_type)) |
          PseudoTypeField::encode(kPseudoUnknown) |
          IsLastInSelectorListField::encode(false) |
          IsLastInComplexSelectorField::encode(false) |
          HasRareDataField::encode(true) | IsForPageField::encode(false) |
          IsImplicitlyAddedField::encode(false) |
          IsCoveredByBucketingField::encode(false) |
          AttributeMatchField::encode(static_cast<unsigned>(case_sensitivity)) |
          LegacyCaseInsensitiveMatchField::encode(
              !HTMLDocument::IsCaseSensitiveAttribute(attribute) &&
              case_sensitivity != AttributeMatchType::kCaseSensitiveAlways) |
          IsScopeContainingField::encode(false)),
      data_(MakeGarbageCollected<RareData>(value)) {
  DCHECK(IsAttributeSelector());
  data_.rare_data_->attribute_ = attribute;
}

void CSSSelector::CreateRareData() {
  DCHECK_NE(Match(), kTag);
  DCHECK_NE(Match(), kUniversalTag);
  if (HasRareData()) {
=======
void CSSSelector::CreateRareData() {
  DCHECK_NE(Match(), kTag);
  if (has_rare_data_)
>>>>>>> chromium
    return;
  // This transitions the DataUnion from |value_| to |rare_data_| and thus needs to be careful to
  // correctly manage explicitly destruction of |value_| followed by placement new of |rare_data_|.
  // A straight-assignment will compile and may kinda work, but will be undefined behavior.
  auto rare_data = RareData::Create(data_.value_);
  data_.value_.~AtomicString();
  new (&data_.rare_data_) scoped_refptr<RareData>(std::move(rare_data));
  has_rare_data_ = true;
}

unsigned CSSSelector::Specificity() const {
  // make sure the result doesn't overflow
  static const unsigned kMaxValueMask = 0xffffff;
  static const unsigned kIdMask = 0xff0000;
  static const unsigned kClassMask = 0x00ff00;
  static const unsigned kElementMask = 0x0000ff;

  if (IsForPage())
    return SpecificityForPage() & kMaxValueMask;

  unsigned total = 0;
  unsigned temp = 0;

  for (const CSSSelector* selector = this; selector;
       selector = selector->TagHistory()) {
    temp = total + selector->SpecificityForOneSelector();
    // Clamp each component to its max in the case of overflow.
    if ((temp & kIdMask) < (total & kIdMask))
      total |= kIdMask;
    else if ((temp & kClassMask) < (total & kClassMask))
      total |= kClassMask;
    else if ((temp & kElementMask) < (total & kElementMask))
      total |= kElementMask;
    else
      total = temp;
  }
  return total;
}

inline unsigned CSSSelector::SpecificityForOneSelector() const {
  // FIXME: Pseudo-elements and pseudo-classes do not have the same specificity.
  // This function isn't quite correct.
  // http://www.w3.org/TR/selectors/#specificity
  switch (match_) {
    case kId:
      return kIdSpecificity;
    case kPseudoClass:
      switch (GetPseudoType()) {
        case kPseudoWhere:
          return 0;
        case kPseudoHost:
          if (!SelectorList())
            return kClassLikeSpecificity;
          FALLTHROUGH;
        case kPseudoHostContext:
          DCHECK(SelectorList()->IsSingleComplexSelector());
          return kClassLikeSpecificity + SelectorList()->First()->Specificity();
        case kPseudoNot:
          DCHECK(SelectorList());
          FALLTHROUGH;
        case kPseudoIs:
          return MaximumSpecificity(SelectorList());
<<<<<<< HEAD
        case kPseudoHas:
          return MaximumSpecificity(SelectorList());
        case kPseudoParent:
          if (data_.parent_rule_ == nullptr) {
            // & in a non-nesting context matches nothing.
            return 0;
          }
          return MaximumSpecificity(
              data_.parent_rule_->FirstSelector(),
              [](const CSSSelector* selector) {
                return selector->IsAllowedInParentPseudo();
              });
        case kPseudoNthChild:
        case kPseudoNthLastChild:
          if (SelectorList()) {
            return kClassLikeSpecificity + MaximumSpecificity(SelectorList());
          } else {
            return kClassLikeSpecificity;
          }
        case kPseudoRelativeAnchor:
          return 0;
        case kPseudoScope:
          if (IsImplicit()) {
            // Implicit :scope pseudo-classes are added to selectors
            // within @scope. Such pseudo-classes must not have any effect
            // on the specificity of the scoped selector.
            //
            // https://drafts.csswg.org/css-cascade-6/#scope-effects
            return 0;
          }
          break;
=======
>>>>>>> chromium
        // FIXME: PseudoAny should base the specificity on the sub-selectors.
        // See http://lists.w3.org/Archives/Public/www-style/2010Sep/0530.html
        case kPseudoAny:
        default:
          break;
      }
      return kClassLikeSpecificity;
    case kPseudoElement:
      switch (GetPseudoType()) {
        case kPseudoSlotted:
<<<<<<< HEAD
          DCHECK(SelectorList()->IsSingleComplexSelector());
          return kTagSpecificity + SelectorList()->First()->Specificity();
        case kPseudoViewTransitionGroup:
        case kPseudoViewTransitionImagePair:
        case kPseudoViewTransitionOld:
        case kPseudoViewTransitionNew: {
          CHECK(!IdentList().empty());
          return (IdentList().size() == 1u && IdentList()[0].IsNull())
                     ? 0
                     : kTagSpecificity;
        }
=======
          DCHECK(SelectorList()->HasOneSelector());
          return kClassLikeSpecificity + SelectorList()->First()->Specificity();
>>>>>>> chromium
        default:
          break;
      }
      return kClassLikeSpecificity;
    case kClass:
    case kAttributeExact:
    case kAttributeSet:
    case kAttributeList:
    case kAttributeHyphen:
    case kAttributeContain:
    case kAttributeBegin:
    case kAttributeEnd:
      return kClassLikeSpecificity;
    case kTag:
<<<<<<< HEAD
      return kTagSpecificity;
    case kUniversalTag:
      return 0;
    case kInvalidList:
    case kPagePseudoClass:
      NOTREACHED();
=======
      if (TagQName().LocalName() == UniversalSelectorAtom())
        return 0;
      return kTagSpecificity;
>>>>>>> chromium
    case kUnknown:
      return 0;
  }
  NOTREACHED();
  return 0;
}

unsigned CSSSelector::SpecificityForPage() const {
  // See https://drafts.csswg.org/css-page/#cascading-and-page-context
  unsigned s = 0;

  for (const CSSSelector* component = this; component;
       component = component->TagHistory()) {
    switch (component->match_) {
      case kTag:
        s += 4;
        break;
      case kPagePseudoClass:
        switch (component->GetPseudoType()) {
          case kPseudoFirstPage:
            s += 2;
            break;
          case kPseudoLeftPage:
          case kPseudoRightPage:
            s += 1;
            break;
          default:
            NOTREACHED();
        }
        break;
      default:
        break;
    }
  }
  return s;
}

PseudoId CSSSelector::GetPseudoId(PseudoType type) {
  switch (type) {
    case kPseudoFirstLine:
      return kPseudoIdFirstLine;
    case kPseudoFirstLetter:
      return kPseudoIdFirstLetter;
    case kPseudoSelection:
      return kPseudoIdSelection;
<<<<<<< HEAD
    case kPseudoCheckMark:
      return kPseudoIdCheckMark;
=======
>>>>>>> chromium
    case kPseudoBefore:
      return kPseudoIdBefore;
    case kPseudoAfter:
      return kPseudoIdAfter;
<<<<<<< HEAD
    case kPseudoPickerIcon:
      return kPseudoIdPickerIcon;
=======
>>>>>>> chromium
    case kPseudoMarker:
      return kPseudoIdMarker;
    case kPseudoBackdrop:
      return kPseudoIdBackdrop;
    case kPseudoScrollbar:
      return kPseudoIdScrollbar;
<<<<<<< HEAD
    case kPseudoScrollMarker:
      return kPseudoIdScrollMarker;
    case kPseudoScrollMarkerGroup:
      return kPseudoIdScrollMarkerGroup;
    case kPseudoScrollButton:
      return kPseudoIdScrollButton;
    case kPseudoColumn:
      return kPseudoIdColumn;
=======
>>>>>>> chromium
    case kPseudoScrollbarButton:
      return kPseudoIdScrollbarButton;
    case kPseudoScrollbarCorner:
      return kPseudoIdScrollbarCorner;
    case kPseudoScrollbarThumb:
      return kPseudoIdScrollbarThumb;
    case kPseudoScrollbarTrack:
      return kPseudoIdScrollbarTrack;
    case kPseudoScrollbarTrackPiece:
      return kPseudoIdScrollbarTrackPiece;
    case kPseudoResizer:
      return kPseudoIdResizer;
    case kPseudoTargetText:
      return kPseudoIdTargetText;
    case kPseudoHighlight:
      return kPseudoIdHighlight;
    case kPseudoSpellingError:
      return kPseudoIdSpellingError;
    case kPseudoGrammarError:
      return kPseudoIdGrammarError;
    case kPseudoUnknown:
    case kPseudoEmpty:
    case kPseudoFirstChild:
    case kPseudoFirstOfType:
    case kPseudoLastChild:
    case kPseudoLastOfType:
    case kPseudoOnlyChild:
    case kPseudoOnlyOfType:
    case kPseudoNthChild:
    case kPseudoNthOfType:
    case kPseudoNthLastChild:
    case kPseudoNthLastOfType:
    case kPseudoLink:
    case kPseudoVisited:
    case kPseudoAny:
    case kPseudoIs:
    case kPseudoWhere:
    case kPseudoAnyLink:
    case kPseudoWebkitAnyLink:
    case kPseudoAutofill:
    case kPseudoAutofillPreviewed:
    case kPseudoAutofillSelected:
<<<<<<< HEAD
    case kPseudoBlinkInternalElement:
    case kPseudoChecked:
    case kPseudoCornerPresent:
    case kPseudoCue:
    case kPseudoCurrent:
    case kPseudoDecrement:
    case kPseudoDefault:
    case kPseudoDefined:
    case kPseudoDialogInTopLayer:
    case kPseudoDir:
    case kPseudoDisabled:
    case kPseudoDoubleButton:
=======
    case kPseudoHover:
>>>>>>> chromium
    case kPseudoDrag:
    case kPseudoFocus:
    case kPseudoFocusVisible:
    case kPseudoFocusWithin:
    case kPseudoActive:
    case kPseudoChecked:
    case kPseudoEnabled:
    case kPseudoFullPageMedia:
    case kPseudoDefault:
    case kPseudoDisabled:
    case kPseudoOptional:
    case kPseudoPlaceholder:
    case kPseudoPlaceholderShown:
    case kPseudoFileSelectorButton:
    case kPseudoRequired:
    case kPseudoReadOnly:
    case kPseudoReadWrite:
    case kPseudoValid:
    case kPseudoInvalid:
    case kPseudoIndeterminate:
    case kPseudoTarget:
    case kPseudoLang:
    case kPseudoDir:
    case kPseudoNot:
    case kPseudoRoot:
    case kPseudoScope:
    case kPseudoWindowInactive:
    case kPseudoCornerPresent:
    case kPseudoDecrement:
    case kPseudoIncrement:
    case kPseudoHorizontal:
    case kPseudoVertical:
    case kPseudoStart:
    case kPseudoEnd:
    case kPseudoDoubleButton:
    case kPseudoSingleButton:
    case kPseudoNoButton:
    case kPseudoFirstPage:
    case kPseudoLeftPage:
    case kPseudoRightPage:
    case kPseudoInRange:
    case kPseudoOutOfRange:
    case kPseudoWebKitCustomElement:
    case kPseudoBlinkInternalElement:
    case kPseudoCue:
    case kPseudoFutureCue:
    case kPseudoPastCue:
    case kPseudoDefined:
    case kPseudoHost:
    case kPseudoHostContext:
    case kPseudoPart:
    case kPseudoState:
    case kPseudoFullScreen:
    case kPseudoFullScreenAncestor:
    case kPseudoFullscreen:
<<<<<<< HEAD
    case kPseudoFutureCue:
    case kPseudoHas:
    case kPseudoHasInterest:
    case kPseudoHasSlotted:
    case kPseudoHasDatalist:
    case kPseudoHorizontal:
    case kPseudoHost:
    case kPseudoHostContext:
    case kPseudoHostHasNonAutoAppearance:
    case kPseudoHover:
    case kPseudoInRange:
    case kPseudoIncrement:
    case kPseudoIndeterminate:
    case kPseudoInvalid:
    case kPseudoIs:
    case kPseudoIsHtml:
    case kPseudoLang:
    case kPseudoLastChild:
    case kPseudoLastOfType:
    case kPseudoLeftPage:
    case kPseudoLink:
    case kPseudoListBox:
    case kPseudoModal:
    case kPseudoMultiSelectFocus:
    case kPseudoNoButton:
    case kPseudoNot:
    case kPseudoNthChild:
    case kPseudoNthLastChild:
    case kPseudoNthLastOfType:
    case kPseudoNthOfType:
    case kPseudoOnlyChild:
    case kPseudoOnlyOfType:
    case kPseudoOpen:
    case kPseudoOptional:
    case kPseudoOutOfRange:
    case kPseudoParent:
    case kPseudoPart:
    case kPseudoPastCue:
=======
>>>>>>> chromium
    case kPseudoPaused:
    case kPseudoPictureInPicture:
    case kPseudoPlaying:
<<<<<<< HEAD
    case kPseudoPopoverInTopLayer:
    case kPseudoPopoverOpen:
    case kPseudoReadOnly:
    case kPseudoReadWrite:
    case kPseudoRelativeAnchor:
    case kPseudoRequired:
    case kPseudoRightPage:
    case kPseudoRoot:
    case kPseudoScope:
    case kPseudoSelectorFragmentAnchor:
    case kPseudoSingleButton:
    case kPseudoSlotted:
    case kPseudoSpatialNavigationFocus:
    case kPseudoStart:
    case kPseudoState:
    case kPseudoTarget:
    case kPseudoTargetCurrent:
    case kPseudoUnknown:
    case kPseudoUnparsed:
    case kPseudoUserInvalid:
    case kPseudoUserValid:
    case kPseudoValid:
    case kPseudoVertical:
=======
    case kPseudoSpatialNavigationFocus:
    case kPseudoSpatialNavigationInterest:
    case kPseudoHasDatalist:
    case kPseudoIsHtml:
    case kPseudoListBox:
    case kPseudoMultiSelectFocus:
    case kPseudoHostHasAppearance:
    case kPseudoPopupOpen:
    case kPseudoSlotted:
>>>>>>> chromium
    case kPseudoVideoPersistent:
    case kPseudoVideoPersistentAncestor:
    case kPseudoXrOverlay:
    case kPseudoModal:
    case kPseudoHas:
      return kPseudoIdNone;
  }

  NOTREACHED();
<<<<<<< HEAD
}

std::optional<CSSSelector> CSSSelector::Renest(StyleRule* new_parent) const {
  if (GetPseudoType() == CSSSelector::kPseudoParent &&
      data_.parent_rule_ != new_parent) {
    CSSSelector selector(*this);
    selector.data_.parent_rule_ = new_parent;
    return selector;
  } else if (HasRareData()) {
    // Handles cases where simple selectors hold an inner selector list,
    // e.g. :is(), :where(), :not().
    RareData* old_rare_data = data_.rare_data_;
    RareData* new_rare_data = old_rare_data->Renest(new_parent);
    if (old_rare_data != new_rare_data) {
      CSSSelector selector(*this);
      selector.data_.rare_data_ = new_rare_data;
      return selector;
    }
  }
  // Note that :scope (which isn't handled by any of the branches above)
  // does not need re-nesting, because it does not contain any reference
  // to a parent rule. The relationship between :scope, and the elements
  // matched by it, are instead handled dynamically at selector-matching time.

  return std::nullopt;
=======
  return kPseudoIdNone;
>>>>>>> chromium
}

// Could be made smaller and faster by replacing pointer with an
// offset into a string buffer and making the bit fields smaller but
// that could not be maintained by hand.
struct NameToPseudoStruct {
  const char* string;
  unsigned type : 8;
};

// These tables should be kept sorted.
const static NameToPseudoStruct kPseudoTypeWithoutArgumentsMap[] = {
    {"-internal-autofill-previewed", CSSSelector::kPseudoAutofillPreviewed},
    {"-internal-autofill-selected", CSSSelector::kPseudoAutofillSelected},
    {"-internal-has-datalist", CSSSelector::kPseudoHasDatalist},
    {"-internal-is-html", CSSSelector::kPseudoIsHtml},
    {"-internal-list-box", CSSSelector::kPseudoListBox},
    {"-internal-media-controls-overlay-cast-button",
     CSSSelector::kPseudoWebKitCustomElement},
    {"-internal-modal", CSSSelector::kPseudoModal},
    {"-internal-multi-select-focus", CSSSelector::kPseudoMultiSelectFocus},
<<<<<<< HEAD
    {"-internal-popover-in-top-layer", CSSSelector::kPseudoPopoverInTopLayer},
    {"-internal-relative-anchor", CSSSelector::kPseudoRelativeAnchor},
    {"-internal-selector-fragment-anchor",
     CSSSelector::kPseudoSelectorFragmentAnchor},
    {"-internal-shadow-host-has-non-auto-appearance",
     CSSSelector::kPseudoHostHasNonAutoAppearance},
=======
    {"-internal-popup-open", CSSSelector::kPseudoPopupOpen},
    {"-internal-shadow-host-has-appearance",
     CSSSelector::kPseudoHostHasAppearance},
>>>>>>> chromium
    {"-internal-spatial-navigation-focus",
     CSSSelector::kPseudoSpatialNavigationFocus},
    {"-internal-spatial-navigation-interest",
     CSSSelector::kPseudoSpatialNavigationInterest},
    {"-internal-video-persistent", CSSSelector::kPseudoVideoPersistent},
    {"-internal-video-persistent-ancestor",
     CSSSelector::kPseudoVideoPersistentAncestor},
    {"-webkit-any-link", CSSSelector::kPseudoWebkitAnyLink},
    {"-webkit-autofill", CSSSelector::kPseudoAutofill},
    {"-webkit-drag", CSSSelector::kPseudoDrag},
    {"-webkit-full-page-media", CSSSelector::kPseudoFullPageMedia},
    {"-webkit-full-screen", CSSSelector::kPseudoFullScreen},
    {"-webkit-full-screen-ancestor", CSSSelector::kPseudoFullScreenAncestor},
    {"-webkit-resizer", CSSSelector::kPseudoResizer},
    {"-webkit-scrollbar", CSSSelector::kPseudoScrollbar},
    {"-webkit-scrollbar-button", CSSSelector::kPseudoScrollbarButton},
    {"-webkit-scrollbar-corner", CSSSelector::kPseudoScrollbarCorner},
    {"-webkit-scrollbar-thumb", CSSSelector::kPseudoScrollbarThumb},
    {"-webkit-scrollbar-track", CSSSelector::kPseudoScrollbarTrack},
    {"-webkit-scrollbar-track-piece", CSSSelector::kPseudoScrollbarTrackPiece},
    {"active", CSSSelector::kPseudoActive},
    {"after", CSSSelector::kPseudoAfter},
    {"any-link", CSSSelector::kPseudoAnyLink},
    {"backdrop", CSSSelector::kPseudoBackdrop},
    {"before", CSSSelector::kPseudoBefore},
    {"checked", CSSSelector::kPseudoChecked},
<<<<<<< HEAD
    {"checkmark", CSSSelector::kPseudoCheckMark},
    {"column", CSSSelector::kPseudoColumn},
=======
>>>>>>> chromium
    {"corner-present", CSSSelector::kPseudoCornerPresent},
    {"cue", CSSSelector::kPseudoWebKitCustomElement},
    {"decrement", CSSSelector::kPseudoDecrement},
    {"default", CSSSelector::kPseudoDefault},
    {"defined", CSSSelector::kPseudoDefined},
    {"disabled", CSSSelector::kPseudoDisabled},
    {"double-button", CSSSelector::kPseudoDoubleButton},
    {"empty", CSSSelector::kPseudoEmpty},
    {"enabled", CSSSelector::kPseudoEnabled},
    {"end", CSSSelector::kPseudoEnd},
    {"file-selector-button", CSSSelector::kPseudoFileSelectorButton},
    {"first", CSSSelector::kPseudoFirstPage},
    {"first-child", CSSSelector::kPseudoFirstChild},
    {"first-letter", CSSSelector::kPseudoFirstLetter},
    {"first-line", CSSSelector::kPseudoFirstLine},
    {"first-of-type", CSSSelector::kPseudoFirstOfType},
    {"focus", CSSSelector::kPseudoFocus},
    {"focus-visible", CSSSelector::kPseudoFocusVisible},
    {"focus-within", CSSSelector::kPseudoFocusWithin},
    {"fullscreen", CSSSelector::kPseudoFullscreen},
    {"future", CSSSelector::kPseudoFutureCue},
    {"grammar-error", CSSSelector::kPseudoGrammarError},
<<<<<<< HEAD
    {"granted", CSSSelector::kPseudoPermissionGranted},
    {"has-interest", CSSSelector::kPseudoHasInterest},
    {"has-slotted", CSSSelector::kPseudoHasSlotted},
=======
>>>>>>> chromium
    {"horizontal", CSSSelector::kPseudoHorizontal},
    {"host", CSSSelector::kPseudoHost},
    {"hover", CSSSelector::kPseudoHover},
    {"in-range", CSSSelector::kPseudoInRange},
    {"increment", CSSSelector::kPseudoIncrement},
    {"indeterminate", CSSSelector::kPseudoIndeterminate},
    {"invalid", CSSSelector::kPseudoInvalid},
    {"last-child", CSSSelector::kPseudoLastChild},
    {"last-of-type", CSSSelector::kPseudoLastOfType},
    {"left", CSSSelector::kPseudoLeftPage},
    {"link", CSSSelector::kPseudoLink},
    {"marker", CSSSelector::kPseudoMarker},
    {"no-button", CSSSelector::kPseudoNoButton},
    {"only-child", CSSSelector::kPseudoOnlyChild},
    {"only-of-type", CSSSelector::kPseudoOnlyOfType},
    {"optional", CSSSelector::kPseudoOptional},
    {"out-of-range", CSSSelector::kPseudoOutOfRange},
    {"past", CSSSelector::kPseudoPastCue},
    {"paused", CSSSelector::kPseudoPaused},
    {"picker-icon", CSSSelector::kPseudoPickerIcon},
    {"picture-in-picture", CSSSelector::kPseudoPictureInPicture},
    {"placeholder", CSSSelector::kPseudoPlaceholder},
    {"placeholder-shown", CSSSelector::kPseudoPlaceholderShown},
    {"playing", CSSSelector::kPseudoPlaying},
    {"read-only", CSSSelector::kPseudoReadOnly},
    {"read-write", CSSSelector::kPseudoReadWrite},
    {"required", CSSSelector::kPseudoRequired},
    {"right", CSSSelector::kPseudoRightPage},
    {"root", CSSSelector::kPseudoRoot},
    {"scope", CSSSelector::kPseudoScope},
<<<<<<< HEAD
    {"scroll-marker", CSSSelector::kPseudoScrollMarker},
    {"scroll-marker-group", CSSSelector::kPseudoScrollMarkerGroup},
    {"search-text", CSSSelector::kPseudoSearchText},
=======
>>>>>>> chromium
    {"selection", CSSSelector::kPseudoSelection},
    {"single-button", CSSSelector::kPseudoSingleButton},
    {"spelling-error", CSSSelector::kPseudoSpellingError},
    {"start", CSSSelector::kPseudoStart},
    {"target", CSSSelector::kPseudoTarget},
    {"target-current", CSSSelector::kPseudoTargetCurrent},
    {"target-text", CSSSelector::kPseudoTargetText},
    {"valid", CSSSelector::kPseudoValid},
    {"vertical", CSSSelector::kPseudoVertical},
    {"visited", CSSSelector::kPseudoVisited},
    {"window-inactive", CSSSelector::kPseudoWindowInactive},
    {"xr-overlay", CSSSelector::kPseudoXrOverlay},
};

const static NameToPseudoStruct kPseudoTypeWithArgumentsMap[] = {
    {"-webkit-any", CSSSelector::kPseudoAny},
    {"cue", CSSSelector::kPseudoCue},
    {"dir", CSSSelector::kPseudoDir},
    {"has", CSSSelector::kPseudoHas},
    {"highlight", CSSSelector::kPseudoHighlight},
    {"host", CSSSelector::kPseudoHost},
    {"host-context", CSSSelector::kPseudoHostContext},
    {"is", CSSSelector::kPseudoIs},
    {"lang", CSSSelector::kPseudoLang},
    {"not", CSSSelector::kPseudoNot},
    {"nth-child", CSSSelector::kPseudoNthChild},
    {"nth-last-child", CSSSelector::kPseudoNthLastChild},
    {"nth-last-of-type", CSSSelector::kPseudoNthLastOfType},
    {"nth-of-type", CSSSelector::kPseudoNthOfType},
    {"part", CSSSelector::kPseudoPart},
<<<<<<< HEAD
    {"picker", CSSSelector::kPseudoPicker},
    {"scroll-button", CSSSelector::kPseudoScrollButton},
=======
>>>>>>> chromium
    {"slotted", CSSSelector::kPseudoSlotted},
    {"where", CSSSelector::kPseudoWhere},
};

CSSSelector::PseudoType CSSSelector::NameToPseudoType(const AtomicString& name,
                                                      bool has_arguments) {
  if (name.IsNull() || !name.Is8Bit())
    return CSSSelector::kPseudoUnknown;

  const NameToPseudoStruct* pseudo_type_map;
  const NameToPseudoStruct* pseudo_type_map_end;
  if (has_arguments) {
    pseudo_type_map = kPseudoTypeWithArgumentsMap;
    pseudo_type_map_end =
        kPseudoTypeWithArgumentsMap + base::size(kPseudoTypeWithArgumentsMap);
  } else {
    pseudo_type_map = kPseudoTypeWithoutArgumentsMap;
    pseudo_type_map_end = kPseudoTypeWithoutArgumentsMap +
                          base::size(kPseudoTypeWithoutArgumentsMap);
  }
  const NameToPseudoStruct* match = std::lower_bound(
      pseudo_type_map, pseudo_type_map_end, name,
      [](const NameToPseudoStruct& entry, const AtomicString& name) -> bool {
        DCHECK(name.Is8Bit());
        DCHECK(entry.string);
        // If strncmp returns 0, then either the keys are equal, or |name| sorts
        // before |entry|.
        return strncmp(entry.string,
                       reinterpret_cast<const char*>(name.Characters8()),
                       name.length()) < 0;
      });
  if (match == pseudo_type_map_end || match->string != name.GetString())
    return CSSSelector::kPseudoUnknown;

  if (match->type == CSSSelector::kPseudoDir &&
      !RuntimeEnabledFeatures::CSSPseudoDirEnabled())
    return CSSSelector::kPseudoUnknown;

  if (match->type == CSSSelector::kPseudoFocusVisible &&
      !RuntimeEnabledFeatures::CSSFocusVisibleEnabled())
    return CSSSelector::kPseudoUnknown;

  if (match->type == CSSSelector::kPseudoPaused &&
      !RuntimeEnabledFeatures::CSSPseudoPlayingPausedEnabled())
    return CSSSelector::kPseudoUnknown;

  if (match->type == CSSSelector::kPseudoPictureInPicture &&
      !RuntimeEnabledFeatures::CSSPictureInPictureEnabled())
    return CSSSelector::kPseudoUnknown;

  if (match->type == CSSSelector::kPseudoPlaying &&
      !RuntimeEnabledFeatures::CSSPseudoPlayingPausedEnabled())
    return CSSSelector::kPseudoUnknown;

  if (match->type == CSSSelector::kPseudoTargetText &&
      !RuntimeEnabledFeatures::CSSTargetTextPseudoElementEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

<<<<<<< HEAD
  if (match->type == CSSSelector::kPseudoPermissionElementInvalidStyle &&
      !RuntimeEnabledFeatures::PermissionElementEnabled(
          document ? document->GetExecutionContext() : nullptr)) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoPermissionElementOccluded &&
      !RuntimeEnabledFeatures::PermissionElementEnabled(
          document ? document->GetExecutionContext() : nullptr)) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoPermissionGranted &&
      !RuntimeEnabledFeatures::PermissionElementEnabled(
          document ? document->GetExecutionContext() : nullptr)) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoTargetCurrent &&
      !RuntimeEnabledFeatures::CSSPseudoScrollMarkersEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if ((match->type == CSSSelector::kPseudoScrollMarker ||
       match->type == CSSSelector::kPseudoScrollMarkerGroup) &&
      !RuntimeEnabledFeatures::CSSPseudoScrollMarkersEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoScrollButton &&
      !RuntimeEnabledFeatures::CSSPseudoScrollButtonsEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoColumn &&
      !RuntimeEnabledFeatures::CSSPseudoColumnEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoOpen &&
      !RuntimeEnabledFeatures::CSSPseudoOpenEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoPicker &&
      !RuntimeEnabledFeatures::CustomizableSelectEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if ((match->type == CSSSelector::kPseudoSearchText ||
       match->type == CSSSelector::kPseudoCurrent) &&
      !RuntimeEnabledFeatures::SearchTextHighlightPseudoEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoHasInterest &&
      !RuntimeEnabledFeatures::HTMLInterestTargetAttributeEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoHasSlotted &&
      !RuntimeEnabledFeatures::CSSPseudoHasSlottedEnabled()) {
=======
  if (match->type == CSSSelector::kPseudoHighlight &&
      !RuntimeEnabledFeatures::HighlightAPIEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if ((match->type == CSSSelector::kPseudoSpellingError ||
       match->type == CSSSelector::kPseudoGrammarError) &&
      !RuntimeEnabledFeatures::CSSSpellingGrammarErrorsEnabled()) {
    return CSSSelector::kPseudoUnknown;
  }

  if (match->type == CSSSelector::kPseudoHas &&
      !RuntimeEnabledFeatures::CSSPseudoHasEnabled()) {
>>>>>>> chromium
    return CSSSelector::kPseudoUnknown;
  }

  return static_cast<CSSSelector::PseudoType>(match->type);
}

#ifndef NDEBUG
void CSSSelector::Show(int indent) const {
  printf("%*sSelectorText(): %s\n", indent, "", SelectorText().Ascii().c_str());
<<<<<<< HEAD
  printf("%*smatch_: %d\n", indent, "", Match());
  if (Match() != kTag && Match() != kUniversalTag) {
=======
  printf("%*smatch_: %d\n", indent, "", match_);
  if (match_ != kTag)
>>>>>>> chromium
    printf("%*sValue(): %s\n", indent, "", Value().Ascii().c_str());
  printf("%*sGetPseudoType(): %d\n", indent, "", GetPseudoType());
<<<<<<< HEAD
  if (Match() == kTag && Match() != kUniversalTag) {
=======
  if (match_ == kTag) {
>>>>>>> chromium
    printf("%*sTagQName().LocalName(): %s\n", indent, "",
           TagQName().LocalName().Ascii().c_str());
  }
  printf("%*sIsAttributeSelector(): %d\n", indent, "", IsAttributeSelector());
  if (IsAttributeSelector()) {
    printf("%*sAttribute(): %s\n", indent, "",
           Attribute().LocalName().Ascii().c_str());
  }
  printf("%*sArgument(): %s\n", indent, "", Argument().Ascii().c_str());
  printf("%*sSpecificity(): %u\n", indent, "", Specificity());
  if (TagHistory()) {
    printf("\n%*s--> (Relation() == %d)\n", indent, "", Relation());
    TagHistory()->Show(indent + 2);
  } else {
    printf("\n%*s--> (Relation() == %d)\n", indent, "", Relation());
  }
}

void CSSSelector::Show() const {
  printf("\n******* CSSSelector::Show(\"%s\") *******\n",
         SelectorText().Ascii().c_str());
  Show(2);
  printf("******* end *******\n");
}
#endif

void CSSSelector::UpdatePseudoPage(const AtomicString& value) {
  DCHECK_EQ(Match(), kPagePseudoClass);
  SetValue(value);
  PseudoType type = CSSSelectorParser::ParsePseudoType(value, false);
  if (type != kPseudoFirstPage && type != kPseudoLeftPage &&
      type != kPseudoRightPage) {
    type = kPseudoUnknown;
  }
  pseudo_type_ = type;
}

void CSSSelector::UpdatePseudoType(const AtomicString& value,
                                   const CSSParserContext& context,
                                   bool has_arguments,
                                   CSSParserMode mode) {
  DCHECK(match_ == kPseudoClass || match_ == kPseudoElement);
  AtomicString lower_value = value.LowerASCII();
  PseudoType pseudo_type =
      CSSSelectorParser::ParsePseudoType(lower_value, has_arguments);
  SetPseudoType(pseudo_type);
<<<<<<< HEAD
  SetValue(lower_value);
=======
  SetValue(pseudo_type == kPseudoState ? value : lower_value);
>>>>>>> chromium

  switch (GetPseudoType()) {
    case kPseudoAfter:
    case kPseudoBefore:
    case kPseudoFirstLetter:
    case kPseudoFirstLine:
      // The spec says some pseudos allow both single and double colons like
      // :before for backwards compatability. Single colon becomes PseudoClass,
      // but should be PseudoElement like double colon.
      if (match_ == kPseudoClass)
        match_ = kPseudoElement;
      FALLTHROUGH;
    // For pseudo elements
<<<<<<< HEAD
    case kPseudoPickerIcon:
    case kPseudoCheckMark:
=======
>>>>>>> chromium
    case kPseudoBackdrop:
    case kPseudoCue:
    case kPseudoMarker:
    case kPseudoPart:
    case kPseudoPlaceholder:
    case kPseudoFileSelectorButton:
    case kPseudoResizer:
    case kPseudoScrollbar:
    case kPseudoScrollbarCorner:
    case kPseudoScrollbarButton:
    case kPseudoScrollbarThumb:
    case kPseudoScrollbarTrack:
    case kPseudoScrollbarTrackPiece:
<<<<<<< HEAD
    case kPseudoScrollMarker:
    case kPseudoScrollMarkerGroup:
    case kPseudoScrollButton:
    case kPseudoColumn:
    case kPseudoPicker:
=======
>>>>>>> chromium
    case kPseudoSelection:
    case kPseudoWebKitCustomElement:
    case kPseudoSlotted:
    case kPseudoTargetText:
    case kPseudoHighlight:
    case kPseudoSpellingError:
    case kPseudoGrammarError:
      if (match_ != kPseudoElement)
        pseudo_type_ = kPseudoUnknown;
      break;
    case kPseudoBlinkInternalElement:
      if (match_ != kPseudoElement || mode != kUASheetMode)
        pseudo_type_ = kPseudoUnknown;
      break;
    case kPseudoHasDatalist:
    case kPseudoHostHasAppearance:
    case kPseudoIsHtml:
    case kPseudoListBox:
<<<<<<< HEAD
=======
    case kPseudoModal:
>>>>>>> chromium
    case kPseudoMultiSelectFocus:
    case kPseudoPopupOpen:
    case kPseudoSpatialNavigationFocus:
    case kPseudoSpatialNavigationInterest:
    case kPseudoVideoPersistent:
    case kPseudoVideoPersistentAncestor:
      if (mode != kUASheetMode) {
        pseudo_type_ = kPseudoUnknown;
        break;
      }
      FALLTHROUGH;
    // For pseudo classes
    case kPseudoActive:
    case kPseudoAny:
    case kPseudoAnyLink:
    case kPseudoAutofill:
    case kPseudoAutofillPreviewed:
    case kPseudoAutofillSelected:
    case kPseudoChecked:
    case kPseudoCornerPresent:
    case kPseudoDecrement:
    case kPseudoDefault:
    case kPseudoDefined:
    case kPseudoDisabled:
    case kPseudoDir:
    case kPseudoDoubleButton:
    case kPseudoDrag:
    case kPseudoEmpty:
    case kPseudoEnabled:
    case kPseudoEnd:
    case kPseudoFirstChild:
    case kPseudoFirstOfType:
    case kPseudoFocus:
    case kPseudoFocusVisible:
    case kPseudoFocusWithin:
    case kPseudoFullPageMedia:
    case kPseudoFullScreen:
    case kPseudoFullScreenAncestor:
    case kPseudoFullscreen:
    case kPseudoFutureCue:
    case kPseudoHas:
<<<<<<< HEAD
    case kPseudoHasInterest:
    case kPseudoHasSlotted:
=======
>>>>>>> chromium
    case kPseudoHorizontal:
    case kPseudoHost:
    case kPseudoHostContext:
    case kPseudoHover:
    case kPseudoInRange:
    case kPseudoIncrement:
    case kPseudoIndeterminate:
    case kPseudoInvalid:
    case kPseudoWhere:
    case kPseudoLang:
    case kPseudoLastChild:
    case kPseudoLastOfType:
    case kPseudoLink:
    case kPseudoIs:
    case kPseudoNoButton:
    case kPseudoNot:
    case kPseudoNthChild:
    case kPseudoNthLastChild:
    case kPseudoNthLastOfType:
    case kPseudoNthOfType:
    case kPseudoOnlyChild:
    case kPseudoOnlyOfType:
    case kPseudoOptional:
    case kPseudoPaused:
    case kPseudoPictureInPicture:
    case kPseudoPlaying:
    case kPseudoPlaceholderShown:
    case kPseudoOutOfRange:
    case kPseudoPastCue:
    case kPseudoReadOnly:
    case kPseudoReadWrite:
    case kPseudoRequired:
    case kPseudoRoot:
    case kPseudoScope:
    case kPseudoSingleButton:
    case kPseudoStart:
    case kPseudoState:
    case kPseudoTarget:
<<<<<<< HEAD
    case kPseudoTargetCurrent:
=======
>>>>>>> chromium
    case kPseudoUnknown:
    case kPseudoValid:
    case kPseudoVertical:
    case kPseudoVisited:
    case kPseudoWebkitAnyLink:
    case kPseudoWindowInactive:
    case kPseudoXrOverlay:
      if (match_ != kPseudoClass)
        pseudo_type_ = kPseudoUnknown;
      break;
    case kPseudoFirstPage:
    case kPseudoLeftPage:
    case kPseudoRightPage:
      pseudo_type_ = kPseudoUnknown;
      break;
  }
}

bool CSSSelector::operator==(const CSSSelector& other) const {
  const CSSSelector* sel1 = this;
  const CSSSelector* sel2 = &other;

  while (sel1 && sel2) {
    if (sel1->Attribute() != sel2->Attribute() ||
        sel1->Relation() != sel2->Relation() || sel1->match_ != sel2->match_ ||
        sel1->Value() != sel2->Value() ||
        sel1->GetPseudoType() != sel2->GetPseudoType() ||
        sel1->Argument() != sel2->Argument()) {
      return false;
    }
    if (sel1->match_ == kTag) {
      if (sel1->TagQName() != sel2->TagQName())
        return false;
    }
    sel1 = sel1->TagHistory();
    sel2 = sel2->TagHistory();
  }

<<<<<<< HEAD
void CSSSelector::SetWhere(CSSSelectorList* selector_list) {
  SetMatch(kPseudoClass);
  SetPseudoType(kPseudoWhere);
  SetSelectorList(selector_list);
=======
  if (sel1 || sel2)
    return false;

  return true;
>>>>>>> chromium
}

static void SerializeIdentifierOrAny(const AtomicString& identifier,
                                     const AtomicString& any,
                                     StringBuilder& builder) {
  if (identifier != any)
    SerializeIdentifier(identifier, builder);
  else
    builder.Append(g_star_atom);
}

static void SerializeNamespacePrefixIfNeeded(const AtomicString& prefix,
                                             const AtomicString& any,
                                             StringBuilder& builder,
                                             bool is_attribute_selector) {
  if (prefix.IsNull() || (prefix.IsEmpty() && is_attribute_selector))
    return;
  SerializeIdentifierOrAny(prefix, any, builder);
  builder.Append('|');
}

<<<<<<< HEAD
// static
template <bool expand_pseudo_references>
void CSSSelector::SerializeSelectorList(const CSSSelectorList* selector_list,
                                        StringBuilder& builder,
                                        uintptr_t scope_id) {
  const CSSSelector* first_sub_selector = selector_list->First();
  for (const CSSSelector* sub_selector = first_sub_selector; sub_selector;
       sub_selector = CSSSelectorList::Next(*sub_selector)) {
    if (sub_selector != first_sub_selector) {
      builder.Append(", ");
    }
    builder.Append(
        sub_selector->SelectorTextInternal<expand_pseudo_references>(scope_id));
  }
}

String CSSSelector::SelectorText() const {
  // The value of `scope_id` does not matter when
  // `expand_pseudo_references` is `false`.
  return SelectorTextInternal<!kExpandPseudoReferences>(/*scope_id=*/0);
}

String CSSSelector::SelectorTextExpandingPseudoReferences(
    uintptr_t scope_id) const {
  return SelectorTextInternal<kExpandPseudoReferences>(scope_id);
}

template <bool expand_pseudo_references>
bool CSSSelector::SerializeSimpleSelector(StringBuilder& builder,
                                          uintptr_t scope_id) const {
  bool suppress_selector_list = false;
  if (Match() == kId) {
    builder.Append('#');
    SerializeIdentifier(SerializingValue(), builder);
  } else if (Match() == kClass) {
    builder.Append('.');
    SerializeIdentifier(SerializingValue(), builder);
  } else if (Match() == kPseudoClass || Match() == kPagePseudoClass) {
    if (GetPseudoType() == kPseudoUnparsed) {
      builder.Append(Value());
    } else if (GetPseudoType() != kPseudoParent &&
               GetPseudoType() != kPseudoScope) {
      builder.Append(':');
      builder.Append(SerializingValue());
    }

    switch (GetPseudoType()) {
      case kPseudoNthChild:
      case kPseudoNthLastChild:
      case kPseudoNthOfType:
      case kPseudoNthLastOfType: {
        builder.Append('(');

        // https://drafts.csswg.org/css-syntax/#serializing-anb
        int a = data_.rare_data_->NthAValue();
        int b = data_.rare_data_->NthBValue();
        if (a == 0) {
          builder.Append(String::Number(b));
        } else {
          if (a == 1) {
            builder.Append('n');
          } else if (a == -1) {
            builder.Append("-n");
          } else {
            builder.AppendFormat("%dn", a);
          }

          if (b < 0) {
            builder.Append(String::Number(b));
          } else if (b > 0) {
            builder.AppendFormat("+%d", b);
          }
        }

        // Only relevant for :nth-child, not :nth-of-type.
        if (data_.rare_data_->selector_list_ != nullptr) {
          builder.Append(" of ");
          SerializeSelectorList<expand_pseudo_references>(
              data_.rare_data_->selector_list_, builder, scope_id);
          suppress_selector_list = true;
        }

        builder.Append(')');
        break;
      }
      case kPseudoDir:
      case kPseudoLang:
      case kPseudoState:
        builder.Append('(');
        SerializeIdentifier(Argument(), builder);
        builder.Append(')');
        break;
      case kPseudoHas:
      case kPseudoNot:
        DCHECK(SelectorList());
        break;
      case kPseudoHost:
      case kPseudoHostContext:
      case kPseudoAny:
      case kPseudoIs:
      case kPseudoWhere:
        break;
      case kPseudoParent:
        if constexpr (expand_pseudo_references) {
          // Replace parent pseudo with equivalent :is() pseudo.
          builder.Append(":is");
          if (auto* parent = SelectorListOrParent()) {
            builder.Append('(');
            builder.Append(
                parent->SelectorTextExpandingPseudoReferences(scope_id));
            builder.Append(')');
          }
        } else {
          builder.Append('&');
        }
        break;
      case kPseudoScope:
        if constexpr (expand_pseudo_references) {
          builder.Append(":-internal-scope-");
          builder.AppendNumber(scope_id);
        } else {
          builder.Append(':');
          builder.Append(SerializingValue());
        }
        break;
      case kPseudoRelativeAnchor:
        NOTREACHED();
      case kPseudoActiveViewTransitionType: {
        CHECK(!IdentList().empty());
        String separator = "(";
        for (AtomicString type : IdentList()) {
          builder.Append(separator);
          if (separator == "(") {
            separator = ", ";
          }
          SerializeIdentifier(type, builder);
        }
        builder.Append(')');
        break;
      }
      default:
        break;
    }
  } else if (Match() == kPseudoElement) {
    builder.Append("::");
    SerializeIdentifier(SerializingValue(), builder);
    switch (GetPseudoType()) {
      case kPseudoPart: {
        char separator = '(';
        for (AtomicString part : IdentList()) {
          builder.Append(separator);
          if (separator == '(') {
            separator = ' ';
          }
          SerializeIdentifier(part, builder);
        }
        builder.Append(')');
        break;
      }
      case kPseudoHighlight: {
        builder.Append('(');
        builder.Append(Argument());
        builder.Append(')');
        break;
      }
      case kPseudoScrollButton: {
        builder.Append('(');
        builder.Append(Argument());
        builder.Append(')');
        break;
      }
      case kPseudoViewTransitionGroup:
      case kPseudoViewTransitionImagePair:
      case kPseudoViewTransitionNew:
      case kPseudoViewTransitionOld: {
        builder.Append('(');
        bool first = true;
        for (const AtomicString& name_or_class : IdentList()) {
          if (!first) {
            builder.Append('.');
          }

          first = false;
          if (name_or_class == UniversalSelectorAtom()) {
            builder.Append(g_star_atom);
          } else {
            SerializeIdentifier(name_or_class, builder);
          }
        }
        builder.Append(')');
        break;
      }
      default:
        break;
    }
  } else if (IsAttributeSelector()) {
    builder.Append('[');
    SerializeNamespacePrefixIfNeeded(Attribute().Prefix(), g_star_atom, builder,
                                     IsAttributeSelector());
    SerializeIdentifier(Attribute().LocalName(), builder);
    switch (Match()) {
      case kAttributeExact:
        builder.Append('=');
        break;
      case kAttributeSet:
        // set has no operator or value, just the attrName
        builder.Append(']');
        break;
      case kAttributeList:
        builder.Append("~=");
        break;
      case kAttributeHyphen:
        builder.Append("|=");
        break;
      case kAttributeBegin:
        builder.Append("^=");
        break;
      case kAttributeEnd:
        builder.Append("$=");
        break;
      case kAttributeContain:
        builder.Append("*=");
        break;
      default:
        break;
    }
    if (Match() != kAttributeSet) {
      SerializeString(SerializingValue(), builder);
      if (AttributeMatch() == AttributeMatchType::kCaseInsensitive) {
        builder.Append(" i");
      } else if (AttributeMatch() == AttributeMatchType::kCaseSensitiveAlways) {
        DCHECK(RuntimeEnabledFeatures::CSSCaseSensitiveSelectorEnabled());
        builder.Append(" s");
      }
      builder.Append(']');
    }
  }

  if (SelectorList() && !suppress_selector_list) {
    builder.Append('(');
    SerializeSelectorList<expand_pseudo_references>(SelectorList(), builder,
                                                    scope_id);
    builder.Append(')');
  }
  return true;
}

template <bool expand_pseudo_references>
const CSSSelector* CSSSelector::SerializeCompound(StringBuilder& builder,
                                                  uintptr_t scope_id) const {
  if ((Match() == kTag || Match() == kUniversalTag) && !IsImplicit()) {
=======
const CSSSelector* CSSSelector::SerializeCompound(
    StringBuilder& builder) const {
  if (match_ == kTag && !tag_is_implicit_) {
>>>>>>> chromium
    SerializeNamespacePrefixIfNeeded(TagQName().Prefix(), g_star_atom, builder,
                                     IsAttributeSelector());
    SerializeIdentifierOrAny(TagQName().LocalName(), UniversalSelectorAtom(),
                             builder);
  }

  for (const CSSSelector* simple_selector = this; simple_selector;
<<<<<<< HEAD
       simple_selector = simple_selector->NextSimpleSelector()) {
    if (!simple_selector->SerializeSimpleSelector<expand_pseudo_references>(
            builder, scope_id)) {
      return nullptr;
    }
    if (simple_selector->Relation() != kSubSelector) {
=======
       simple_selector = simple_selector->TagHistory()) {
    if (simple_selector->match_ == kId) {
      builder.Append('#');
      SerializeIdentifier(simple_selector->SerializingValue(), builder);
    } else if (simple_selector->match_ == kClass) {
      builder.Append('.');
      SerializeIdentifier(simple_selector->SerializingValue(), builder);
    } else if (simple_selector->match_ == kPseudoClass ||
               simple_selector->match_ == kPagePseudoClass) {
      if (simple_selector->GetPseudoType() != kPseudoState) {
        builder.Append(':');
        builder.Append(simple_selector->SerializingValue());
      }

      switch (simple_selector->GetPseudoType()) {
        case kPseudoNthChild:
        case kPseudoNthLastChild:
        case kPseudoNthOfType:
        case kPseudoNthLastOfType: {
          builder.Append('(');

          // https://drafts.csswg.org/css-syntax/#serializing-anb
          int a = simple_selector->data_.rare_data_->NthAValue();
          int b = simple_selector->data_.rare_data_->NthBValue();
          if (a == 0) {
            builder.Append(String::Number(b));
          } else {
            if (a == 1)
              builder.Append('n');
            else if (a == -1)
              builder.Append("-n");
            else
              builder.AppendFormat("%dn", a);

            if (b < 0)
              builder.Append(String::Number(b));
            else if (b > 0)
              builder.AppendFormat("+%d", b);
          }

          builder.Append(')');
          break;
        }
        case kPseudoDir:
        case kPseudoLang:
          builder.Append('(');
          SerializeIdentifier(simple_selector->Argument(), builder);
          builder.Append(')');
          break;
        case kPseudoHas:
        case kPseudoNot:
          DCHECK(simple_selector->SelectorList());
          break;
        case kPseudoState:
          builder.Append(':');
          SerializeIdentifier(simple_selector->SerializingValue(), builder);
          break;
        case kPseudoHost:
        case kPseudoHostContext:
        case kPseudoAny:
        case kPseudoIs:
        case kPseudoWhere:
          break;
        default:
          break;
      }
    } else if (simple_selector->match_ == kPseudoElement) {
      builder.Append("::");
      SerializeIdentifier(simple_selector->SerializingValue(), builder);
      switch (simple_selector->GetPseudoType()) {
        case kPseudoPart: {
          char separator = '(';
          for (AtomicString part : *simple_selector->PartNames()) {
            builder.Append(separator);
            if (separator == '(')
              separator = ' ';
            SerializeIdentifier(part, builder);
          }
          builder.Append(')');
          break;
        }
        case kPseudoHighlight: {
          builder.Append('(');
          builder.Append(simple_selector->Argument());
          builder.Append(')');
          break;
        }
        default:
          break;
      }
    } else if (simple_selector->IsAttributeSelector()) {
      builder.Append('[');
      SerializeNamespacePrefixIfNeeded(simple_selector->Attribute().Prefix(),
                                       g_star_atom, builder,
                                       simple_selector->IsAttributeSelector());
      SerializeIdentifier(simple_selector->Attribute().LocalName(), builder);
      switch (simple_selector->match_) {
        case kAttributeExact:
          builder.Append('=');
          break;
        case kAttributeSet:
          // set has no operator or value, just the attrName
          builder.Append(']');
          break;
        case kAttributeList:
          builder.Append("~=");
          break;
        case kAttributeHyphen:
          builder.Append("|=");
          break;
        case kAttributeBegin:
          builder.Append("^=");
          break;
        case kAttributeEnd:
          builder.Append("$=");
          break;
        case kAttributeContain:
          builder.Append("*=");
          break;
        default:
          break;
      }
      if (simple_selector->match_ != kAttributeSet) {
        SerializeString(simple_selector->SerializingValue(), builder);
        if (simple_selector->AttributeMatch() ==
            AttributeMatchType::kCaseInsensitive) {
          builder.Append(" i");
        } else if (simple_selector->AttributeMatch() ==
                   AttributeMatchType::kCaseSensitiveAlways) {
          DCHECK(RuntimeEnabledFeatures::CSSCaseSensitiveSelectorEnabled());
          builder.Append(" s");
        }
        builder.Append(']');
      }
    }

    if (simple_selector->SelectorList()) {
      builder.Append('(');
      const CSSSelector* first_sub_selector =
          simple_selector->SelectorList()->FirstForCSSOM();
      for (const CSSSelector* sub_selector = first_sub_selector; sub_selector;
           sub_selector = CSSSelectorList::Next(*sub_selector)) {
        if (sub_selector != first_sub_selector)
          builder.Append(", ");
        builder.Append(sub_selector->SelectorText());
      }
      builder.Append(')');
    }

    if (simple_selector->Relation() != kSubSelector)
>>>>>>> chromium
      return simple_selector;
  }
  return nullptr;
}

<<<<<<< HEAD
template <bool expand_pseudo_references>
String CSSSelector::SelectorTextInternal(uintptr_t scope_id) const {
=======
String CSSSelector::SelectorText() const {
>>>>>>> chromium
  String result;
  for (const CSSSelector* compound = this; compound;
       compound = compound->TagHistory()) {
    StringBuilder builder;
<<<<<<< HEAD
    compound = compound->SerializeCompound<expand_pseudo_references>(builder,
                                                                     scope_id);
    if (!compound) {
      return builder.ReleaseString() + result;
    }

    RelationType relation = compound->Relation();
    DCHECK_NE(relation, kSubSelector);

    const CSSSelector* next_compound = compound->NextSimpleSelector();
    DCHECK(next_compound);

    // If we are combining with an implicit :scope, it is as if we
    // used a relative combinator. However, when expand_pseudo_references=true,
    // we must serialize the implicit compound anyway, since the :has() cache
    // needs this to be a part of the key.
    bool implicit = next_compound->IsImplicit() && !expand_pseudo_references;
    if (!next_compound ||
        (next_compound->Match() == kPseudoClass &&
         next_compound->GetPseudoType() == kPseudoScope && implicit)) {
      relation = ConvertRelationToRelative(relation);
    }

    switch (relation) {
=======
    compound = compound->SerializeCompound(builder);
    if (!compound)
      return builder.ToString() + result;

    DCHECK(compound->Relation() != kSubSelector);
    switch (compound->Relation()) {
>>>>>>> chromium
      case kDescendant:
        result = " " + builder.ToString() + result;
        break;
      case kChild:
        result = " > " + builder.ToString() + result;
        break;
      case kDirectAdjacent:
        result = " + " + builder.ToString() + result;
        break;
      case kIndirectAdjacent:
        result = " ~ " + builder.ToString() + result;
        break;
      case kSubSelector:
<<<<<<< HEAD
=======
        NOTREACHED();
        break;
>>>>>>> chromium
      case kShadowPart:
      case kUAShadow:
      case kShadowSlot:
        result = builder.ToString() + result;
        break;
    }
  }
  NOTREACHED();
  return String();
}

<<<<<<< HEAD
String CSSSelector::SimpleSelectorTextForDebug() const {
  StringBuilder builder;
  if ((Match() == kTag || Match() == kUniversalTag) && !IsImplicit()) {
    SerializeNamespacePrefixIfNeeded(TagQName().Prefix(), g_star_atom, builder,
                                     IsAttributeSelector());
    SerializeIdentifierOrAny(TagQName().LocalName(), UniversalSelectorAtom(),
                             builder);
  } else {
    // `scope_id` is ignored when `expand_pseudo_references` is false.
    SerializeSimpleSelector<!kExpandPseudoReferences>(builder, /*scope_id=*/0);
  }
  return builder.ToString();
=======
void CSSSelector::SetAttribute(const QualifiedName& value,
                               AttributeMatchType match_type) {
  CreateRareData();
  data_.rare_data_->attribute_ = value;
  data_.rare_data_->bits_.attribute_match_ = match_type;
>>>>>>> chromium
}

void CSSSelector::SetArgument(const AtomicString& value) {
  CreateRareData();
  data_.rare_data_->argument_ = value;
}

void CSSSelector::SetSelectorList(
    std::unique_ptr<CSSSelectorList> selector_list) {
  CreateRareData();
  data_.rare_data_->selector_list_ = std::move(selector_list);
}

static bool ValidateSubSelector(const CSSSelector* selector) {
  switch (selector->Match()) {
    case CSSSelector::kTag:
    case CSSSelector::kUniversalTag:
    case CSSSelector::kId:
    case CSSSelector::kClass:
    case CSSSelector::kAttributeExact:
    case CSSSelector::kAttributeSet:
    case CSSSelector::kAttributeList:
    case CSSSelector::kAttributeHyphen:
    case CSSSelector::kAttributeContain:
    case CSSSelector::kAttributeBegin:
    case CSSSelector::kAttributeEnd:
      return true;
    case CSSSelector::kPseudoElement:
    case CSSSelector::kUnknown:
      return false;
    case CSSSelector::kPagePseudoClass:
    case CSSSelector::kPseudoClass:
      break;
  }

  switch (selector->GetPseudoType()) {
    case CSSSelector::kPseudoEmpty:
    case CSSSelector::kPseudoLink:
    case CSSSelector::kPseudoVisited:
    case CSSSelector::kPseudoTarget:
    case CSSSelector::kPseudoEnabled:
    case CSSSelector::kPseudoDisabled:
    case CSSSelector::kPseudoChecked:
    case CSSSelector::kPseudoIndeterminate:
    case CSSSelector::kPseudoNthChild:
    case CSSSelector::kPseudoNthLastChild:
    case CSSSelector::kPseudoNthOfType:
    case CSSSelector::kPseudoNthLastOfType:
    case CSSSelector::kPseudoFirstChild:
    case CSSSelector::kPseudoLastChild:
    case CSSSelector::kPseudoFirstOfType:
    case CSSSelector::kPseudoLastOfType:
    case CSSSelector::kPseudoOnlyOfType:
    case CSSSelector::kPseudoHost:
    case CSSSelector::kPseudoHostContext:
    case CSSSelector::kPseudoNot:
    case CSSSelector::kPseudoSpatialNavigationFocus:
    case CSSSelector::kPseudoSpatialNavigationInterest:
    case CSSSelector::kPseudoHasDatalist:
    case CSSSelector::kPseudoIsHtml:
    case CSSSelector::kPseudoListBox:
<<<<<<< HEAD
    case CSSSelector::kPseudoHostHasNonAutoAppearance:
      // TODO(https://crbug.com/1346456): Many pseudos should probably be
      // added to this list.  The default: case below should also be removed
      // so that those adding new pseudos know they need to choose one path or
      // the other here.
      //
      // However, it's not clear why a pseudo should be in one list or the
      // other.  It's also entirely possible that this entire switch() should
      // be removed and all cases should return true.
=======
    case CSSSelector::kPseudoHostHasAppearance:
>>>>>>> chromium
      return true;
    default:
      return false;
  }
}

bool CSSSelector::IsCompound() const {
  if (!ValidateSubSelector(this))
    return false;

  const CSSSelector* prev_sub_selector = this;
  const CSSSelector* sub_selector = TagHistory();

  while (sub_selector) {
    if (prev_sub_selector->Relation() != kSubSelector)
      return false;
    if (!ValidateSubSelector(sub_selector))
      return false;

    prev_sub_selector = sub_selector;
    sub_selector = sub_selector->TagHistory();
  }

  return true;
}

bool CSSSelector::HasLinkOrVisited() const {
  for (const CSSSelector* current = this; current;
       current = current->TagHistory()) {
    CSSSelector::PseudoType pseudo = current->GetPseudoType();
    if (pseudo == CSSSelector::kPseudoLink ||
        pseudo == CSSSelector::kPseudoVisited) {
      return true;
    }
    if (const CSSSelectorList* list = current->SelectorList()) {
      for (const CSSSelector* sub_selector = list->First(); sub_selector;
           sub_selector = CSSSelectorList::Next(*sub_selector)) {
        if (sub_selector->HasLinkOrVisited())
          return true;
      }
    }
  }
  return false;
}

void CSSSelector::SetNth(int a, int b) {
  CreateRareData();
  data_.rare_data_->bits_.nth_.a_ = a;
  data_.rare_data_->bits_.nth_.b_ = b;
}

bool CSSSelector::MatchNth(unsigned count) const {
  DCHECK(has_rare_data_);
  return data_.rare_data_->MatchNth(count);
}

bool CSSSelector::MatchesPseudoElement() const {
  for (const CSSSelector* current = this; current;
       current = current->TagHistory()) {
    if (current->Match() == kPseudoElement)
      return true;
    if (current->Relation() != kSubSelector)
      return false;
  }
  return false;
}

bool CSSSelector::IsTreeAbidingPseudoElement() const {
  return Match() == CSSSelector::kPseudoElement &&
<<<<<<< HEAD
         (GetPseudoType() == kPseudoCheckMark ||
          GetPseudoType() == kPseudoBefore || GetPseudoType() == kPseudoAfter ||
          GetPseudoType() == kPseudoPickerIcon ||
=======
         (GetPseudoType() == kPseudoBefore || GetPseudoType() == kPseudoAfter ||
>>>>>>> chromium
          GetPseudoType() == kPseudoMarker ||
          GetPseudoType() == kPseudoPlaceholder ||
          GetPseudoType() == kPseudoFileSelectorButton);
}

bool CSSSelector::IsAllowedAfterPart() const {
  if (Match() != CSSSelector::kPseudoElement) {
    return false;
  }
  // Everything that makes sense should work following ::part. This list
  // restricts it to what has been tested.
  switch (GetPseudoType()) {
<<<<<<< HEAD
    // Pseudo-elements
    //
    // All pseudo-elements other than ::part() should be allowed after
    // ::part().
    case kPseudoCheckMark:
    case kPseudoBefore:
    case kPseudoAfter:
    case kPseudoPickerIcon:
=======
    case kPseudoBefore:
    case kPseudoAfter:
>>>>>>> chromium
    case kPseudoPlaceholder:
    case kPseudoFileSelectorButton:
    case kPseudoFirstLine:
    case kPseudoFirstLetter:
    case kPseudoSelection:
    case kPseudoTargetText:
    case kPseudoHighlight:
    case kPseudoSpellingError:
    case kPseudoGrammarError:
<<<<<<< HEAD
    case kPseudoBackdrop:
    case kPseudoCue:
    case kPseudoMarker:
    case kPseudoResizer:
    case kPseudoScrollbar:
    case kPseudoScrollbarButton:
    case kPseudoScrollbarCorner:
    case kPseudoScrollbarThumb:
    case kPseudoScrollbarTrack:
    case kPseudoScrollbarTrackPiece:
    case kPseudoScrollMarker:
    case kPseudoScrollMarkerGroup:
    case kPseudoScrollButton:
    case kPseudoColumn:
    case kPseudoWebKitCustomElement:
    case kPseudoBlinkInternalElement:
    case kPseudoDetailsContent:
    case kPseudoViewTransition:
    case kPseudoViewTransitionGroup:
    case kPseudoViewTransitionImagePair:
    case kPseudoViewTransitionNew:
    case kPseudoViewTransitionOld:
      return true;

    // It's possible that we should support ::slotted() after ::part().
    // (WebKit accepts it at parse time but it doesn't appear to work;
    // Gecko doesn't accept it.)  However, making it work isn't trivial.
    // https://github.com/w3c/csswg-drafts/issues/10807
    case kPseudoSlotted:
      return false;

    case kPseudoPart:
      return false;

    // Pseudo-classes
    //
    // All non-structural pseudo-classes should be allowed, and structural
    // pseudo-classes should be forbidden.
    case kPseudoAutofill:
    case kPseudoAutofillPreviewed:
    case kPseudoAutofillSelected:
    case kPseudoWebKitAutofill:
    case kPseudoActive:
    case kPseudoActiveViewTransition:
    case kPseudoActiveViewTransitionType:
    case kPseudoAnyLink:
    case kPseudoChecked:
    case kPseudoDefault:
    case kPseudoDialogInTopLayer:
    case kPseudoDisabled:
    case kPseudoDrag:
    case kPseudoEnabled:
    case kPseudoFocus:
    case kPseudoFocusVisible:
    case kPseudoFocusWithin:
    case kPseudoFullPageMedia:
    case kPseudoHasInterest:
    case kPseudoHasSlotted:
    case kPseudoHover:
    case kPseudoIndeterminate:
    case kPseudoInvalid:
    case kPseudoLang:
    case kPseudoLink:
    case kPseudoModal:
    case kPseudoOptional:
    case kPseudoPermissionElementInvalidStyle:
    case kPseudoPermissionElementOccluded:
    case kPseudoPermissionGranted:
    case kPseudoPlaceholderShown:
    case kPseudoReadOnly:
    case kPseudoReadWrite:
    case kPseudoRequired:
    case kPseudoSelectorFragmentAnchor:
    case kPseudoState:
    case kPseudoTarget:
    case kPseudoUserInvalid:
    case kPseudoUserValid:
    case kPseudoValid:
    case kPseudoVisited:
    case kPseudoWebkitAnyLink:
    case kPseudoWindowInactive:
    case kPseudoFullScreen:
    case kPseudoFullScreenAncestor:
    case kPseudoFullscreen:
    case kPseudoInRange:
    case kPseudoOutOfRange:
    case kPseudoPaused:
    case kPseudoPictureInPicture:
    case kPseudoPlaying:
    case kPseudoXrOverlay:
    case kPseudoDefined:
    case kPseudoDir:
    case kPseudoFutureCue:
    case kPseudoIsHtml:
    case kPseudoListBox:
    case kPseudoMultiSelectFocus:
    case kPseudoOpen:
    case kPseudoPastCue:
    case kPseudoPopoverInTopLayer:
    case kPseudoPopoverOpen:
    case kPseudoRelativeAnchor:
    case kPseudoSpatialNavigationFocus:
    case kPseudoTargetCurrent:
    case kPseudoVideoPersistent:
    case kPseudoVideoPersistentAncestor:
      return true;

    // IsSimpleSelectorValidAfterPseudoElement allows these selectors after
    // ::part() regardless of what we do here.  However, since they are in
    // fact allowed, tell the truth here.
    case kPseudoIs:
    case kPseudoNot:
    case kPseudoWhere:
      return true;

    // :-webkit-any() should in theory be allowed too like :is() and :where(),
    // but it's a legacy feature so just leave it disallowed.
    case kPseudoAny:
      return false;

    // TODO(https://crbug.com/40623497): Figure out what to do with this.
    case kPseudoParent:
      return false;

    // These are supported only after ::webkit-scrollbar, which *maybe* makes
    // them structural?  Leave them unsupported for now
    case kPseudoHorizontal:
    case kPseudoVertical:
    case kPseudoDecrement:
    case kPseudoIncrement:
    case kPseudoStart:
    case kPseudoEnd:
    case kPseudoDoubleButton:
    case kPseudoSingleButton:
    case kPseudoNoButton:
    case kPseudoCornerPresent:
    // Likewise, this matches only after ::search-text.
    case kPseudoCurrent:
      return false;

    // These are supported only on @page, so not allowed after ::part().
    case kPseudoFirstPage:
    case kPseudoLeftPage:
    case kPseudoRightPage:
      return false;

    // These are structural pseudo-classes, which should not be allowed.
    case kPseudoEmpty:
    case kPseudoFirstChild:
    case kPseudoFirstOfType:
    case kPseudoLastChild:
    case kPseudoLastOfType:
    case kPseudoNthChild:
    case kPseudoNthLastChild:
    case kPseudoNthLastOfType:
    case kPseudoNthOfType:
    case kPseudoOnlyChild:
    case kPseudoOnlyOfType:
    case kPseudoRoot:
      return false;

    // These are other pseudo-classes that match based on tree information
    // rather than local element information, which should not be allowed.
    case kPseudoHas:
    case kPseudoHasDatalist:
    case kPseudoHost:
    case kPseudoHostContext:
    case kPseudoHostHasNonAutoAppearance:
    case kPseudoScope:
      return false;

    case kPseudoUnparsed:
    case kPseudoUnknown:
=======
      return true;
    default:
>>>>>>> chromium
      return false;
  }
}

template <typename Functor>
static bool ForAnyInTagHistory(const Functor& functor,
                               const CSSSelector& selector) {
  for (const CSSSelector* current = &selector; current;
       current = current->TagHistory()) {
    if (functor(*current))
      return true;
    if (const CSSSelectorList* selector_list = current->SelectorList()) {
      for (const CSSSelector* sub_selector = selector_list->First();
           sub_selector; sub_selector = CSSSelectorList::Next(*sub_selector)) {
        if (ForAnyInTagHistory(functor, *sub_selector))
          return true;
      }
    }
  }

  return false;
}

<<<<<<< HEAD
bool CSSSelector::FollowsSlotted() const {
  const CSSSelector* previous = NextSimpleSelector();
  if (!previous) {
    return false;
  }
  return previous->GetPseudoType() == kPseudoSlotted;
}

bool CSSSelector::CrossesTreeScopes() const {
  for (const CSSSelector* s = this; s; s = s->NextSimpleSelector()) {
    switch (s->Relation()) {
      case kShadowPart:
      case kUAShadow:
      case kShadowSlot:
        return true;
      default:
        break;
    }
  }
  return false;
=======
bool CSSSelector::HasSlottedPseudo() const {
  return ForAnyInTagHistory(
      [](const CSSSelector& selector) -> bool {
        return selector.GetPseudoType() == CSSSelector::kPseudoSlotted;
      },
      *this);
}

bool CSSSelector::FollowsPart() const {
  const CSSSelector* previous = TagHistory();
  if (!previous)
    return false;
  return previous->GetPseudoType() == kPseudoPart;
>>>>>>> chromium
}

String CSSSelector::FormatPseudoTypeForDebugging(PseudoType type) {
  for (const auto& s : kPseudoTypeWithoutArgumentsMap) {
    if (s.type == type)
      return s.string;
  }
  for (const auto& s : kPseudoTypeWithArgumentsMap) {
    if (s.type == type)
      return s.string;
  }
  StringBuilder builder;
  builder.Append("pseudo-");
  builder.AppendNumber(static_cast<int>(type));
  return builder.ToString();
}

CSSSelector::RareData::RareData(const AtomicString& value)
    : matching_value_(value),
      serializing_value_(value),
      bits_(),
      attribute_(AnyQName()),
      argument_(g_null_atom) {}

CSSSelector::RareData::RareData(const RareData& other)
    : matching_value_(other.matching_value_),
      serializing_value_(other.serializing_value_),
      bits_(other.bits_),
      attribute_(other.attribute_),
      argument_(other.argument_),
      selector_list_(other.selector_list_),
      ident_list_(other.ident_list_ ? std::make_unique<Vector<AtomicString>>(
                                          *other.ident_list_)
                                    : nullptr) {}

CSSSelector::RareData::~RareData() = default;

// a helper function for checking nth-arguments
bool CSSSelector::RareData::MatchNth(unsigned unsigned_count) {
  // These very large values for aN + B or count can't ever match, so
  // give up immediately if we see them.
  int max_value = std::numeric_limits<int>::max() / 2;
  int min_value = std::numeric_limits<int>::min() / 2;
  if (UNLIKELY(unsigned_count > static_cast<unsigned>(max_value) ||
               NthAValue() > max_value || NthAValue() < min_value ||
               NthBValue() > max_value || NthBValue() < min_value))
    return false;

  int count = static_cast<int>(unsigned_count);
  if (!NthAValue())
    return count == NthBValue();
  if (NthAValue() > 0) {
    if (count < NthBValue())
      return false;
    return (count - NthBValue()) % NthAValue() == 0;
  }
  if (count > NthBValue())
    return false;
  return (NthBValue() - count) % (-NthAValue()) == 0;
}

<<<<<<< HEAD
CSSSelector::RareData* CSSSelector::RareData::Renest(StyleRule* new_parent) {
  CSSSelectorList* old_list = selector_list_.Get();
  CSSSelectorList* new_list = old_list ? old_list->Renest(new_parent) : nullptr;
  if (old_list == new_list) {
    return this;
  }
  auto* rare_data = MakeGarbageCollected<RareData>(*this);
  rare_data->selector_list_ = new_list;
  return rare_data;
}

void CSSSelector::SetIdentList(
    std::unique_ptr<Vector<AtomicString>> ident_list) {
=======
void CSSSelector::SetPartNames(
    std::unique_ptr<Vector<AtomicString>> part_names) {
>>>>>>> chromium
  CreateRareData();
  data_.rare_data_->part_names_ = std::move(part_names);
}

}  // namespace blink
