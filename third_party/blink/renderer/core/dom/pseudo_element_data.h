// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_DOM_PSEUDO_ELEMENT_DATA_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_DOM_PSEUDO_ELEMENT_DATA_H_

#include "build/build_config.h"
#include "third_party/blink/renderer/platform/heap/handle.h"

namespace blink {

class PseudoElementData final : public GarbageCollected<PseudoElementData> {
 public:
  PseudoElementData() = default;
  PseudoElementData(const PseudoElementData&) = delete;
  PseudoElementData& operator=(const PseudoElementData&) = delete;

  void SetPseudoElement(PseudoId, PseudoElement*);
  PseudoElement* GetPseudoElement(PseudoId) const;

  using PseudoElementVector = HeapVector<Member<PseudoElement>, 2>;
  PseudoElementVector GetPseudoElements() const;

<<<<<<< HEAD
  const ColumnPseudoElementsVector* GetColumnPseudoElements() const {
    return column_pseudo_elements_;
  }
  ColumnPseudoElement* GetColumnPseudoElement(wtf_size_t idx) const {
    if (!column_pseudo_elements_ || idx >= column_pseudo_elements_->size()) {
      return nullptr;
    }
    return column_pseudo_elements_->at(idx);
  }
  void AddColumnPseudoElement(ColumnPseudoElement& column_pseudo_element) {
    if (!column_pseudo_elements_) {
      column_pseudo_elements_ =
          MakeGarbageCollected<ColumnPseudoElementsVector>();
    }
    DCHECK(column_pseudo_elements_->Find(column_pseudo_element) == kNotFound);
    column_pseudo_elements_->push_back(column_pseudo_element);
  }
  void ClearColumnPseudoElements(wtf_size_t to_keep) {
    if (!column_pseudo_elements_) {
      return;
    }
    for (wtf_size_t i = to_keep; i < column_pseudo_elements_->size(); ++i) {
      column_pseudo_elements_->at(i)->Dispose();
    }
    if (to_keep) {
      column_pseudo_elements_->Shrink(to_keep);
    } else {
      column_pseudo_elements_->clear();
    }
  }

=======
>>>>>>> chromium
  bool HasPseudoElements() const;
  void ClearPseudoElements();
  void Trace(Visitor* visitor) const {
    visitor->Trace(generated_before_);
    visitor->Trace(generated_after_);
<<<<<<< HEAD
    visitor->Trace(generated_picker_icon_);
    visitor->Trace(generated_marker_);
    visitor->Trace(generated_first_letter_);
    visitor->Trace(generated_scroll_marker_group_before_);
    visitor->Trace(generated_scroll_marker_group_after_);
    visitor->Trace(generated_scroll_marker_);
    visitor->Trace(generated_scroll_button_block_start_);
    visitor->Trace(generated_scroll_button_inline_start_);
    visitor->Trace(generated_scroll_button_inline_end_);
    visitor->Trace(generated_scroll_button_block_end_);
=======
    visitor->Trace(generated_marker_);
    visitor->Trace(generated_first_letter_);
>>>>>>> chromium
    visitor->Trace(backdrop_);
  }

 private:
  Member<PseudoElement> generated_before_;
  Member<PseudoElement> generated_after_;
<<<<<<< HEAD
  Member<PseudoElement> generated_picker_icon_;
  Member<PseudoElement> generated_marker_;
  Member<PseudoElement> generated_first_letter_;
  Member<PseudoElement> generated_scroll_marker_group_before_;
  Member<PseudoElement> generated_scroll_marker_group_after_;
  Member<PseudoElement> generated_scroll_marker_;
  Member<PseudoElement> generated_scroll_button_block_start_;
  Member<PseudoElement> generated_scroll_button_inline_start_;
  Member<PseudoElement> generated_scroll_button_inline_end_;
  Member<PseudoElement> generated_scroll_button_block_end_;
=======
  Member<PseudoElement> generated_marker_;
  Member<PseudoElement> generated_first_letter_;
>>>>>>> chromium
  Member<PseudoElement> backdrop_;
};

inline bool PseudoElementData::HasPseudoElements() const {
<<<<<<< HEAD
  return generated_check_ || generated_before_ || generated_after_ ||
         generated_picker_icon_ || generated_marker_ || backdrop_ ||
         generated_first_letter_ || transition_data_ ||
         generated_scroll_marker_group_before_ ||
         generated_scroll_marker_group_after_ || generated_scroll_marker_ ||
         generated_scroll_button_block_start_ ||
         generated_scroll_button_inline_start_ ||
         generated_scroll_button_inline_end_ ||
         generated_scroll_button_block_end_ ||
         (column_pseudo_elements_ && !column_pseudo_elements_->empty());
}

inline void PseudoElementData::ClearPseudoElements() {
  SetPseudoElement(kPseudoIdCheckMark, nullptr);
  SetPseudoElement(kPseudoIdBefore, nullptr);
  SetPseudoElement(kPseudoIdAfter, nullptr);
  SetPseudoElement(kPseudoIdPickerIcon, nullptr);
  SetPseudoElement(kPseudoIdMarker, nullptr);
  SetPseudoElement(kPseudoIdBackdrop, nullptr);
  SetPseudoElement(kPseudoIdFirstLetter, nullptr);
  SetPseudoElement(kPseudoIdScrollMarkerGroupBefore, nullptr);
  SetPseudoElement(kPseudoIdScrollMarkerGroupAfter, nullptr);
  SetPseudoElement(kPseudoIdScrollMarker, nullptr);
  SetPseudoElement(kPseudoIdScrollButtonBlockStart, nullptr);
  SetPseudoElement(kPseudoIdScrollButtonInlineStart, nullptr);
  SetPseudoElement(kPseudoIdScrollButtonInlineEnd, nullptr);
  SetPseudoElement(kPseudoIdScrollButtonBlockEnd, nullptr);
  if (column_pseudo_elements_) {
    for (ColumnPseudoElement* column_pseudo_element : *column_pseudo_elements_) {
      column_pseudo_element->Dispose();
    }
    column_pseudo_elements_->clear();
  }
  if (transition_data_) {
    transition_data_->ClearPseudoElements();
    transition_data_ = nullptr;
  }
=======
  return generated_before_ || generated_after_ || generated_marker_ ||
         backdrop_ || generated_first_letter_;
}

inline void PseudoElementData::ClearPseudoElements() {
  SetPseudoElement(kPseudoIdBefore, nullptr);
  SetPseudoElement(kPseudoIdAfter, nullptr);
  SetPseudoElement(kPseudoIdMarker, nullptr);
  SetPseudoElement(kPseudoIdBackdrop, nullptr);
  SetPseudoElement(kPseudoIdFirstLetter, nullptr);
>>>>>>> chromium
}

inline void PseudoElementData::SetPseudoElement(PseudoId pseudo_id,
                                                PseudoElement* element) {
  PseudoElement* previous_element = nullptr;
  switch (pseudo_id) {
<<<<<<< HEAD
    case kPseudoIdCheckMark:
      previous_element = generated_check_;
      generated_check_ = element;
      break;
=======
>>>>>>> chromium
    case kPseudoIdBefore:
      previous_element = generated_before_;
      generated_before_ = element;
      break;
    case kPseudoIdAfter:
      previous_element = generated_after_;
      generated_after_ = element;
      break;
<<<<<<< HEAD
    case kPseudoIdPickerIcon:
      previous_element = generated_picker_icon_;
      generated_picker_icon_ = element;
      break;
=======
>>>>>>> chromium
    case kPseudoIdMarker:
      previous_element = generated_marker_;
      generated_marker_ = element;
      break;
<<<<<<< HEAD
    case kPseudoIdScrollMarkerGroupBefore:
      previous_element = generated_scroll_marker_group_before_;
      generated_scroll_marker_group_before_ = element;
      break;
    case kPseudoIdScrollMarkerGroupAfter:
      previous_element = generated_scroll_marker_group_after_;
      generated_scroll_marker_group_after_ = element;
      break;
    case kPseudoIdScrollMarker:
      previous_element = generated_scroll_marker_;
      generated_scroll_marker_ = element;
      break;
    case kPseudoIdScrollButtonBlockStart:
      previous_element = generated_scroll_button_block_start_;
      generated_scroll_button_block_start_ = element;
      break;
    case kPseudoIdScrollButtonInlineStart:
      previous_element = generated_scroll_button_inline_start_;
      generated_scroll_button_inline_start_ = element;
      break;
    case kPseudoIdScrollButtonInlineEnd:
      previous_element = generated_scroll_button_inline_end_;
      generated_scroll_button_inline_end_ = element;
      break;
    case kPseudoIdScrollButtonBlockEnd:
      previous_element = generated_scroll_button_block_end_;
      generated_scroll_button_block_end_ = element;
      break;
=======
>>>>>>> chromium
    case kPseudoIdBackdrop:
      previous_element = backdrop_;
      backdrop_ = element;
      break;
    case kPseudoIdFirstLetter:
      previous_element = generated_first_letter_;
      generated_first_letter_ = element;
      break;
    default:
      NOTREACHED();
  }

  if (previous_element)
    previous_element->Dispose();
}

inline PseudoElement* PseudoElementData::GetPseudoElement(
<<<<<<< HEAD
    PseudoId pseudo_id,
    const AtomicString& view_transition_name) const {
  if (kPseudoIdCheckMark == pseudo_id) {
    return generated_check_.Get();
  }
=======
    PseudoId pseudo_id) const {
>>>>>>> chromium
  if (kPseudoIdBefore == pseudo_id)
    return generated_before_;
  if (kPseudoIdAfter == pseudo_id)
<<<<<<< HEAD
    return generated_after_.Get();
  if (kPseudoIdPickerIcon == pseudo_id) {
    return generated_picker_icon_.Get();
  }
  if (kPseudoIdMarker == pseudo_id)
    return generated_marker_.Get();
  if (kPseudoIdScrollMarkerGroupBefore == pseudo_id) {
    return generated_scroll_marker_group_before_.Get();
  }
  if (kPseudoIdScrollMarkerGroupAfter == pseudo_id) {
    return generated_scroll_marker_group_after_.Get();
  }
  if (kPseudoIdScrollMarker == pseudo_id) {
    return generated_scroll_marker_.Get();
  }
  if (kPseudoIdScrollButtonBlockStart == pseudo_id) {
    return generated_scroll_button_block_start_.Get();
  }
  if (kPseudoIdScrollButtonInlineStart == pseudo_id) {
    return generated_scroll_button_inline_start_.Get();
  }
  if (kPseudoIdScrollButtonInlineEnd == pseudo_id) {
    return generated_scroll_button_inline_end_.Get();
  }
  if (kPseudoIdScrollButtonBlockEnd == pseudo_id) {
    return generated_scroll_button_block_end_.Get();
  }
=======
    return generated_after_;
  if (kPseudoIdMarker == pseudo_id)
    return generated_marker_;
>>>>>>> chromium
// Workaround for CPU bug. This avoids compiler optimizing
// this group of if conditions into switch. See http://crbug.com/855390.
#if defined(ARCH_CPU_ARMEL)
  __asm__ volatile("");
#endif
  if (kPseudoIdBackdrop == pseudo_id)
    return backdrop_;
  if (kPseudoIdFirstLetter == pseudo_id)
    return generated_first_letter_;
  return nullptr;
}

inline PseudoElementData::PseudoElementVector
PseudoElementData::GetPseudoElements() const {
  PseudoElementData::PseudoElementVector result;
  if (generated_before_)
    result.push_back(generated_before_);
  if (generated_after_)
    result.push_back(generated_after_);
<<<<<<< HEAD
  if (generated_picker_icon_) {
    result.push_back(generated_picker_icon_);
  }
=======
>>>>>>> chromium
  if (generated_marker_)
    result.push_back(generated_marker_);
  if (generated_first_letter_)
    result.push_back(generated_first_letter_);
  if (backdrop_)
    result.push_back(backdrop_);
<<<<<<< HEAD
  if (transition_data_)
    transition_data_->AddPseudoElements(&result);
  if (generated_scroll_marker_group_before_) {
    result.push_back(generated_scroll_marker_group_before_);
  }
  if (generated_scroll_marker_group_after_) {
    result.push_back(generated_scroll_marker_group_after_);
  }
  if (generated_scroll_marker_) {
    result.push_back(generated_scroll_marker_);
  }
  if (generated_scroll_button_block_start_) {
    result.push_back(generated_scroll_button_block_start_);
  }
  if (generated_scroll_button_inline_start_) {
    result.push_back(generated_scroll_button_inline_start_);
  }
  if (generated_scroll_button_inline_end_) {
    result.push_back(generated_scroll_button_inline_end_);
  }
  if (generated_scroll_button_block_end_) {
    result.push_back(generated_scroll_button_block_end_);
  }
  if (column_pseudo_elements_) {
    result.AppendVector(*column_pseudo_elements_);
  }
=======
>>>>>>> chromium
  return result;
}

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_DOM_PSEUDO_ELEMENT_DATA_H_
