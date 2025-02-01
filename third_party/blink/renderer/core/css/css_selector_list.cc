/*
 * Copyright (C) 2008, 2012 Apple Inc. All rights reserved.
 * Copyright (C) 2009 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "third_party/blink/renderer/core/css/css_selector_list.h"

#include <memory>
#include "third_party/blink/renderer/core/css/parser/css_parser_selector.h"
#include "third_party/blink/renderer/platform/wtf/allocator/partitions.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"

namespace blink {

namespace {
// CSSSelector is one of the top types that consume renderer memory,
// so instead of using the |WTF_HEAP_PROFILER_TYPE_NAME| macro in the
// allocations below, pass this type name constant to allow profiling
// in official builds.
const char kCSSSelectorTypeName[] = "blink::CSSSelector";

}  // namespace

CSSSelectorList CSSSelectorList::Copy() const {
  CSSSelectorList list;

  unsigned length = ComputeLength();
  list.selector_array_ =
      reinterpret_cast<CSSSelector*>(WTF::Partitions::FastMalloc(
          WTF::Partitions::ComputeAllocationSize(length, sizeof(CSSSelector)),
          kCSSSelectorTypeName));
  for (unsigned i = 0; i < length; ++i)
    new (&list.selector_array_[i]) CSSSelector(selector_array_[i]);

  return list;
}

CSSSelectorList CSSSelectorList::AdoptSelectorVector(
    Vector<std::unique_ptr<CSSParserSelector>>& selector_vector) {
  size_t flattened_size = 0;
  for (wtf_size_t i = 0; i < selector_vector.size(); ++i) {
    for (CSSParserSelector* selector = selector_vector[i].get(); selector;
         selector = selector->TagHistory())
      ++flattened_size;
  }
  DCHECK(flattened_size);

  CSSSelectorList list;
  list.selector_array_ = reinterpret_cast<CSSSelector*>(
      WTF::Partitions::FastMalloc(WTF::Partitions::ComputeAllocationSize(
                                      flattened_size, sizeof(CSSSelector)),
                                  kCSSSelectorTypeName));
  wtf_size_t array_index = 0;
  for (wtf_size_t i = 0; i < selector_vector.size(); ++i) {
    CSSParserSelector* current = selector_vector[i].get();
    while (current) {
      // Move item from the parser selector vector into selector_array_ without
      // invoking destructor (Ugh.)
      CSSSelector* current_selector = current->ReleaseSelector().release();
      memcpy(&list.selector_array_[array_index], current_selector,
             sizeof(CSSSelector));
      WTF::Partitions::FastFree(current_selector);

      current = current->TagHistory();
      DCHECK(!list.selector_array_[array_index].IsLastInSelectorList());
      if (current)
        list.selector_array_[array_index].SetLastInTagHistory(false);
      ++array_index;
    }
    DCHECK(list.selector_array_[array_index - 1].IsLastInTagHistory());
  }
  DCHECK_EQ(flattened_size, array_index);
  list.selector_array_[array_index - 1].SetLastInSelectorList(true);
  list.selector_array_[array_index - 1].SetLastInOriginalList(true);
  selector_vector.clear();

  return list;
}

const CSSSelector* CSSSelectorList::FirstForCSSOM() const {
  const CSSSelector* s = First();
  if (!s)
    return nullptr;
  while (Next(*s))
    s = Next(*s);
  if (NextInFullList(*s))
    return NextInFullList(*s);
  return First();
}

unsigned CSSSelectorList::ComputeLength() const {
  if (!selector_array_)
    return 0;
  CSSSelector* current = selector_array_;
  while (!current->IsLastInSelectorList())
    ++current;
  return static_cast<unsigned>(current - selector_array_) + 1;
}

void CSSSelectorList::DeleteSelectors() {
  DCHECK(selector_array_);

  bool finished = false;
  for (CSSSelector* s = selector_array_; !finished; ++s) {
    finished = s->IsLastInSelectorList();
    s->~CSSSelector();
  }

  WTF::Partitions::FastFree(selector_array_);
}

<<<<<<< HEAD
bool CSSSelectorList::Renest(const CSSSelector* selector_list,
                             StyleRule* new_parent,
                             HeapVector<CSSSelector>& result) {
  bool renested_any = false;
  for (const CSSSelector* current = selector_list; current;
       current = current->IsLastInSelectorList() ? nullptr : ++current) {
    std::optional<CSSSelector> renested = current->Renest(new_parent);
    renested_any |= renested.has_value();
    result.push_back(renested.value_or(*current));
  }
  return renested_any;
}

CSSSelectorList* CSSSelectorList::Renest(StyleRule* new_parent) {
  HeapVector<CSSSelector> selectors;
  if (IsValid() && Renest(First(), new_parent, selectors)) {
    return AdoptSelectorVector(selectors);
  }
  return this;
}

String CSSSelectorList::SelectorsText(const CSSSelector* first) {
=======
String CSSSelectorList::SelectorsText() const {
>>>>>>> chromium
  StringBuilder result;

  for (const CSSSelector* s = FirstForCSSOM(); s; s = Next(*s)) {
    if (s != FirstForCSSOM())
      result.Append(", ");
    result.Append(s->SelectorText());
  }

<<<<<<< HEAD
  return result.ReleaseString();
}

bool CSSSelectorList::IsAnyAllowedInParentPseudo(
    const CSSSelector* selector_list) {
  for (const CSSSelector* s = selector_list; s; s = Next(*s)) {
    if (s->IsAllowedInParentPseudo()) {
      return true;
    }
  }
  return false;
}

void CSSSelectorList::Trace(Visitor* visitor) const {
  if (!IsValid()) {
    return;
  }

  for (int i = 0;; ++i) {
    visitor->Trace(first_selector_[i]);
    if (first_selector_[i].IsLastInSelectorList()) {
      break;
    }
  }
=======
  return result.ToString();
>>>>>>> chromium
}

}  // namespace blink
