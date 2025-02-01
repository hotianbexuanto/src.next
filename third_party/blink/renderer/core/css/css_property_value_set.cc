/*
 * (C) 1999-2003 Lars Knoll (knoll@kde.org)
 * Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2012, 2013 Apple Inc.
 * All rights reserved.
 * Copyright (C) 2011 Research In Motion Limited. All rights reserved.
 * Copyright (C) 2013 Intel Corporation. All rights reserved.
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

#include "third_party/blink/renderer/core/css/css_property_value_set.h"

#include "third_party/blink/renderer/core/css/css_custom_property_declaration.h"
#include "third_party/blink/renderer/core/css/css_identifier_value.h"
#include "third_party/blink/renderer/core/css/parser/css_parser.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_context.h"
#include "third_party/blink/renderer/core/css/properties/css_property.h"
#include "third_party/blink/renderer/core/css/style_property_serializer.h"
#include "third_party/blink/renderer/core/css/style_sheet_contents.h"
#include "third_party/blink/renderer/core/style_property_shorthand.h"
#include "third_party/blink/renderer/platform/heap/heap.h"
#include "third_party/blink/renderer/platform/instrumentation/use_counter.h"
#include "third_party/blink/renderer/platform/wtf/size_assertions.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

namespace blink {

static AdditionalBytes
AdditionalBytesForImmutableCSSPropertyValueSetWithPropertyCount(
    unsigned count) {
<<<<<<< HEAD
  return AdditionalBytes(sizeof(CSSPropertyValue) * count);
=======
  return AdditionalBytes(sizeof(Member<CSSValue>) * count +
                         sizeof(CSSPropertyValueMetadata) * count);
>>>>>>> chromium
}

ImmutableCSSPropertyValueSet* ImmutableCSSPropertyValueSet::Create(
    const CSSPropertyValue* properties,
    unsigned count,
    CSSParserMode css_parser_mode) {
  DCHECK_LE(count, static_cast<unsigned>(kMaxArraySize));
  return MakeGarbageCollected<ImmutableCSSPropertyValueSet>(
      AdditionalBytesForImmutableCSSPropertyValueSetWithPropertyCount(count),
      properties, count, css_parser_mode);
}

ImmutableCSSPropertyValueSet* CSSPropertyValueSet::ImmutableCopyIfNeeded()
    const {
  auto* immutable_property_set = DynamicTo<ImmutableCSSPropertyValueSet>(
      const_cast<CSSPropertyValueSet*>(this));
  if (immutable_property_set)
    return immutable_property_set;

  const auto* mutable_this = To<MutableCSSPropertyValueSet>(this);
  return ImmutableCSSPropertyValueSet::Create(
<<<<<<< HEAD
      base::span(mutable_this->property_vector_), CssParserMode());
}

unsigned CSSPropertyValueSet::ComputeHash() const {
  unsigned hash = 3141592653;

  for (const CSSPropertyValue& property : Properties()) {
    if (property.PropertyID() == CSSPropertyID::kVariable) {
      WTF::AddIntToHash(hash, property.Name().ToAtomicString().Hash());
    } else {
      WTF::AddIntToHash(hash, static_cast<unsigned>(property.PropertyID()));
    }
    WTF::AddIntToHash(hash, property.IsImportant());
    WTF::AddIntToHash(hash, property.Value().Hash());
  }

  static_assert((WTF::HashTraits<unsigned>::EmptyValue() ^ 0x80000000) !=
                    WTF::HashTraits<unsigned>::DeletedValue(),
                "We assume below that flipping the top bit will not turn "
                "EmptyValue into DeletedValue or vice versa");
  if (hash == WTF::HashTraits<unsigned>::EmptyValue() ||
      hash == WTF::HashTraits<unsigned>::DeletedValue()) {
    hash ^= 0x80000000;
  }

  return hash;
=======
      mutable_this->property_vector_.data(),
      mutable_this->property_vector_.size(), CssParserMode());
>>>>>>> chromium
}

MutableCSSPropertyValueSet::MutableCSSPropertyValueSet(
    CSSParserMode css_parser_mode)
    : CSSPropertyValueSet(css_parser_mode) {}

MutableCSSPropertyValueSet::MutableCSSPropertyValueSet(
    const CSSPropertyValue* properties,
    unsigned length)
    : CSSPropertyValueSet(kHTMLStandardMode) {
<<<<<<< HEAD
  property_vector_.ReserveInitialCapacity(properties.size());
  for (const CSSPropertyValue& property : properties) {
    property_vector_.UncheckedAppend(property);
    may_have_logical_properties_ |=
        kLogicalGroupProperties.Has(property.PropertyID());
=======
  property_vector_.ReserveInitialCapacity(length);
  for (unsigned i = 0; i < length; ++i) {
    property_vector_.UncheckedAppend(properties[i]);
    if (!may_have_logical_properties_) {
      const CSSProperty& prop = CSSProperty::Get(properties[i].Id());
      may_have_logical_properties_ =
          prop.IsInLogicalPropertyGroup() && prop.IsSurrogate();
    }
>>>>>>> chromium
  }
}

ImmutableCSSPropertyValueSet::ImmutableCSSPropertyValueSet(
<<<<<<< HEAD
    PassKey,
    base::span<const CSSPropertyValue> properties,
    CSSParserMode css_parser_mode,
    bool contains_query_hand)
    : CSSPropertyValueSet(css_parser_mode,
                          properties.size(),
                          contains_query_hand) {
  if (array_size_ > 0) {
    // SAFETY: By funneling all allocation of ImmutableCSSPropertyValueSet
    // through Create(), we guarantee that the arrays will have storage where we
    // expect.
    UNSAFE_BUFFERS(base::span<CSSPropertyValue> array(
        const_cast<CSSPropertyValue*>(ArrayBase()), array_size_));
    for (unsigned i = 0; i < array_size_; ++i) {
      new (&array[i]) CSSPropertyValue(properties[i]);
    }
=======
    const CSSPropertyValue* properties,
    unsigned length,
    CSSParserMode css_parser_mode)
    : CSSPropertyValueSet(css_parser_mode, length) {
  CSSPropertyValueMetadata* metadata_array =
      const_cast<CSSPropertyValueMetadata*>(MetadataArray());
  Member<const CSSValue>* value_array =
      const_cast<Member<const CSSValue>*>(ValueArray());
  for (unsigned i = 0; i < array_size_; ++i) {
    metadata_array[i] = properties[i].Metadata();
    value_array[i] = properties[i].Value();
>>>>>>> chromium
  }
}

// Convert property into an uint16_t for comparison with property's ID
// to avoid the compiler converting it to an int multiple times in a loop.
static uint16_t GetConvertedCSSPropertyID(CSSPropertyID property_id) {
  return static_cast<uint16_t>(property_id);
}

static uint16_t GetConvertedCSSPropertyID(const AtomicString&) {
  return static_cast<uint16_t>(CSSPropertyID::kVariable);
}

static uint16_t GetConvertedCSSPropertyID(AtRuleDescriptorID descriptor_id) {
  return static_cast<uint16_t>(
      AtRuleDescriptorIDAsCSSPropertyID(descriptor_id));
}

<<<<<<< HEAD
static bool IsPropertyMatch(const CSSPropertyValue& property,
=======
static bool IsPropertyMatch(const CSSPropertyValueMetadata& metadata,
                            const CSSValue&,
>>>>>>> chromium
                            uint16_t id,
                            CSSPropertyID property_id) {
  DCHECK_EQ(id, static_cast<uint16_t>(property_id));
  bool result = static_cast<uint16_t>(property.PropertyID()) == id;
// Only enabled properties except kInternalFontSizeDelta should be part of the
// style.
// TODO(hjkim3323@gmail.com): Remove kInternalFontSizeDelta bypassing hack
#if DCHECK_IS_ON()
  DCHECK(!result || property_id == CSSPropertyID::kInternalFontSizeDelta ||
         CSSProperty::Get(ResolveCSSPropertyID(property_id)).IsWebExposed());
#endif
  return result;
}

<<<<<<< HEAD
static bool IsPropertyMatch(const CSSPropertyValue& property,
                            uint16_t id,
                            const AtomicString& custom_property_name) {
  DCHECK_EQ(id, static_cast<uint16_t>(CSSPropertyID::kVariable));
  return property.Name() == CSSPropertyName(custom_property_name);
}

static bool IsPropertyMatch(const CSSPropertyValue& property,
                            uint16_t id,
                            AtRuleDescriptorID descriptor_id) {
  return IsPropertyMatch(property, id,
=======
static bool IsPropertyMatch(const CSSPropertyValueMetadata& metadata,
                            const CSSValue& value,
                            uint16_t id,
                            const AtomicString& custom_property_name) {
  DCHECK_EQ(id, static_cast<uint16_t>(CSSPropertyID::kVariable));
  return static_cast<uint16_t>(metadata.PropertyID()) == id &&
         To<CSSCustomPropertyDeclaration>(value).GetName() ==
             custom_property_name;
}

static bool IsPropertyMatch(const CSSPropertyValueMetadata& metadata,
                            const CSSValue& css_value,
                            uint16_t id,
                            AtRuleDescriptorID descriptor_id) {
  return IsPropertyMatch(metadata, css_value, id,
>>>>>>> chromium
                         AtRuleDescriptorIDAsCSSPropertyID(descriptor_id));
}

template <typename T>
int ImmutableCSSPropertyValueSet::FindPropertyIndex(T property) const {
  uint16_t id = GetConvertedCSSPropertyID(property);
<<<<<<< HEAD
  const base::span<const CSSPropertyValue> properties = Properties();
  for (size_t n = array_size_; n; --n) {
    if (IsPropertyMatch(properties[n - 1], id, property)) {
      return static_cast<int>(n - 1);
    }
=======
  for (int n = array_size_ - 1; n >= 0; --n) {
    if (IsPropertyMatch(MetadataArray()[n], *ValueArray()[n], id, property))
      return n;
>>>>>>> chromium
  }

  return -1;
}
template CORE_EXPORT int ImmutableCSSPropertyValueSet::FindPropertyIndex(
    CSSPropertyID) const;
template CORE_EXPORT int ImmutableCSSPropertyValueSet::FindPropertyIndex(
    AtomicString) const;
template CORE_EXPORT int ImmutableCSSPropertyValueSet::FindPropertyIndex(
    AtRuleDescriptorID) const;

void ImmutableCSSPropertyValueSet::TraceAfterDispatch(
    blink::Visitor* visitor) const {
<<<<<<< HEAD
  for (const CSSPropertyValue& value : Properties()) {
    visitor->Trace(value);
  }
=======
  const Member<const CSSValue>* values = ValueArray();
  for (unsigned i = 0; i < array_size_; i++)
    visitor->Trace(values[i]);
>>>>>>> chromium
  CSSPropertyValueSet::TraceAfterDispatch(visitor);
}

MutableCSSPropertyValueSet::MutableCSSPropertyValueSet(
    const CSSPropertyValueSet& other)
    : CSSPropertyValueSet(other.CssParserMode()) {
  if (auto* other_mutable_property_set =
          DynamicTo<MutableCSSPropertyValueSet>(other)) {
    property_vector_ = other_mutable_property_set->property_vector_;
    may_have_logical_properties_ =
        other_mutable_property_set->may_have_logical_properties_;
  } else {
    property_vector_.ReserveInitialCapacity(other.PropertyCount());
<<<<<<< HEAD
    for (const CSSPropertyValue& property : other.Properties()) {
      property_vector_.UncheckedAppend(CSSPropertyValue(property));
      may_have_logical_properties_ |=
          kLogicalGroupProperties.Has(property.PropertyID());
=======
    for (unsigned i = 0; i < other.PropertyCount(); ++i) {
      PropertyReference property = other.PropertyAt(i);
      property_vector_.UncheckedAppend(
          CSSPropertyValue(property.PropertyMetadata(), property.Value()));
      if (!may_have_logical_properties_) {
        const CSSProperty& prop = CSSProperty::Get(property.Id());
        may_have_logical_properties_ =
            prop.IsInLogicalPropertyGroup() && prop.IsSurrogate();
      }
>>>>>>> chromium
    }
  }
}

static String SerializeShorthand(const CSSPropertyValueSet& property_set,
                                 CSSPropertyID property_id) {
  StylePropertyShorthand shorthand = shorthandForProperty(property_id);
  if (!shorthand.length())
    return String();

  return StylePropertySerializer(property_set).SerializeShorthand(property_id);
}

static String SerializeShorthand(const CSSPropertyValueSet&,
                                 const AtomicString& custom_property_name) {
  // Custom properties are never shorthands.
  return String();
}

static String SerializeShorthand(const CSSPropertyValueSet& property_set,
                                 AtRuleDescriptorID atrule_id) {
  // Descriptor shorthands aren't handled yet.
  return String();
}

template <typename T>
String CSSPropertyValueSet::GetPropertyValue(T property) const {
  String shorthand_serialization = SerializeShorthand(*this, property);
  if (!shorthand_serialization.IsNull())
    return shorthand_serialization;
  const CSSValue* value = GetPropertyCSSValue(property);
  if (value)
    return value->CssText();
  return g_empty_string;
}
template CORE_EXPORT String
    CSSPropertyValueSet::GetPropertyValue<CSSPropertyID>(CSSPropertyID) const;
template CORE_EXPORT String
    CSSPropertyValueSet::GetPropertyValue<AtRuleDescriptorID>(
        AtRuleDescriptorID) const;
template CORE_EXPORT String
    CSSPropertyValueSet::GetPropertyValue<AtomicString>(AtomicString) const;

template <typename T>
const CSSValue* CSSPropertyValueSet::GetPropertyCSSValue(T property) const {
  int found_property_index = FindPropertyIndex(property);
  if (found_property_index == -1)
    return nullptr;
  return &PropertyAt(found_property_index).Value();
}
template CORE_EXPORT const CSSValue* CSSPropertyValueSet::GetPropertyCSSValue<
    CSSPropertyID>(CSSPropertyID) const;
template CORE_EXPORT const CSSValue* CSSPropertyValueSet::GetPropertyCSSValue<
    AtRuleDescriptorID>(AtRuleDescriptorID) const;
template CORE_EXPORT const CSSValue*
    CSSPropertyValueSet::GetPropertyCSSValue<AtomicString>(AtomicString) const;

void CSSPropertyValueSet::Trace(Visitor* visitor) const {
  if (is_mutable_)
    To<MutableCSSPropertyValueSet>(this)->TraceAfterDispatch(visitor);
  else
    To<ImmutableCSSPropertyValueSet>(this)->TraceAfterDispatch(visitor);
}

void CSSPropertyValueSet::FinalizeGarbageCollectedObject() {
  if (is_mutable_)
    To<MutableCSSPropertyValueSet>(this)->~MutableCSSPropertyValueSet();
  else
    To<ImmutableCSSPropertyValueSet>(this)->~ImmutableCSSPropertyValueSet();
}

bool MutableCSSPropertyValueSet::RemoveShorthandProperty(
    CSSPropertyID property_id) {
  if (property_id == CSSPropertyID::kAll) {
    return RemovePropertiesAffectedByAll();
  }
  StylePropertyShorthand shorthand = shorthandForProperty(property_id);
  if (!shorthand.length())
    return false;

  return RemovePropertiesInSet(shorthand.properties(), shorthand.length());
}

bool MutableCSSPropertyValueSet::RemovePropertyAtIndex(int property_index,
                                                       String* return_text) {
  if (property_index == -1) {
    if (return_text)
      *return_text = "";
    return false;
  }

  if (return_text)
    *return_text = PropertyAt(property_index).Value().CssText();

  // A more efficient removal strategy would involve marking entries as empty
  // and sweeping them when the vector grows too big.
  property_vector_.EraseAt(property_index);

  return true;
}

template <typename T>
bool MutableCSSPropertyValueSet::RemoveProperty(T property,
                                                String* return_text) {
  if (RemoveShorthandProperty(property)) {
    // FIXME: Return an equivalent shorthand when possible.
    if (return_text)
      *return_text = "";
    return true;
  }

  int found_property_index = FindPropertyIndex(property);
  return RemovePropertyAtIndex(found_property_index, return_text);
}
template CORE_EXPORT bool MutableCSSPropertyValueSet::RemoveProperty(
    CSSPropertyID,
    String*);
template CORE_EXPORT bool MutableCSSPropertyValueSet::RemoveProperty(
    AtomicString,
    String*);

template <typename T>
bool CSSPropertyValueSet::PropertyIsImportant(T property) const {
  int found_property_index = FindPropertyIndex(property);
  if (found_property_index != -1)
    return PropertyAt(found_property_index).IsImportant();
  return ShorthandIsImportant(property);
}
template bool CSSPropertyValueSet::PropertyIsImportant<CSSPropertyID>(
    CSSPropertyID) const;
template bool CSSPropertyValueSet::PropertyIsImportant<AtomicString>(
    AtomicString) const;

bool CSSPropertyValueSet::ShorthandIsImportant(
    CSSPropertyID property_id) const {
  StylePropertyShorthand shorthand = shorthandForProperty(property_id);
  if (!shorthand.length())
    return false;

  for (unsigned i = 0; i < shorthand.length(); ++i) {
    if (!PropertyIsImportant(shorthand.properties()[i]->PropertyID()))
      return false;
  }
  return true;
}

bool CSSPropertyValueSet::ShorthandIsImportant(
    AtomicString custom_property_name) const {
  // Custom properties are never shorthands.
  return false;
}

CSSPropertyID CSSPropertyValueSet::GetPropertyShorthand(
    CSSPropertyID property_id) const {
  int found_property_index = FindPropertyIndex(property_id);
  if (found_property_index == -1)
    return CSSPropertyID::kInvalid;
  return PropertyAt(found_property_index).ShorthandID();
}

bool CSSPropertyValueSet::IsPropertyImplicit(CSSPropertyID property_id) const {
  int found_property_index = FindPropertyIndex(property_id);
  if (found_property_index == -1)
    return false;
  return PropertyAt(found_property_index).IsImplicit();
}

MutableCSSPropertyValueSet::SetResult MutableCSSPropertyValueSet::SetProperty(
    CSSPropertyID unresolved_property,
    const String& value,
    bool important,
    SecureContextMode secure_context_mode,
    StyleSheetContents* context_style_sheet) {
  DCHECK_GE(unresolved_property, kFirstCSSProperty);

  // Setting the value to an empty string just removes the property in both IE
  // and Gecko. Setting it to null seems to produce less consistent results, but
  // we treat it just the same.
  if (value.IsEmpty()) {
    bool did_parse = true;
    bool did_change = RemoveProperty(ResolveCSSPropertyID(unresolved_property));
    return SetResult{did_parse, did_change};
  }

  // When replacing an existing property value, this moves the property to the
  // end of the list. Firefox preserves the position, and MSIE moves the
  // property to the beginning.
  return CSSParser::ParseValue(this, unresolved_property, value, important,
                               secure_context_mode, context_style_sheet);
}

MutableCSSPropertyValueSet::SetResult MutableCSSPropertyValueSet::SetProperty(
    const AtomicString& custom_property_name,
    const String& value,
    bool important,
    SecureContextMode secure_context_mode,
    StyleSheetContents* context_style_sheet,
    bool is_animation_tainted) {
  if (value.IsEmpty()) {
    bool did_parse = true;
    bool did_change = RemoveProperty(custom_property_name);
    return MutableCSSPropertyValueSet::SetResult{did_parse, did_change};
  }
  return CSSParser::ParseValueForCustomProperty(
      this, custom_property_name, value, important, secure_context_mode,
      context_style_sheet, is_animation_tainted);
}

void MutableCSSPropertyValueSet::SetProperty(CSSPropertyID property_id,
                                             const CSSValue& value,
                                             bool important) {
  StylePropertyShorthand shorthand = shorthandForProperty(property_id);
  if (!shorthand.length()) {
    // TODO(crbug.com/1112291): Don't use this function for custom properties.
    CSSPropertyName name =
        (property_id == CSSPropertyID::kVariable)
            ? CSSPropertyName(To<CSSCustomPropertyDeclaration>(value).GetName())
            : CSSPropertyName(property_id);
    SetProperty(CSSPropertyValue(name, value, important));
    return;
  }

  RemovePropertiesInSet(shorthand.properties(), shorthand.length());

  for (unsigned i = 0; i < shorthand.length(); ++i) {
    CSSPropertyName name(shorthand.properties()[i]->PropertyID());
    property_vector_.push_back(CSSPropertyValue(name, value, important));
  }
}

bool MutableCSSPropertyValueSet::SetProperty(const CSSPropertyValue& property,
                                             CSSPropertyValue* slot) {
  CSSPropertyValue* to_replace =
<<<<<<< HEAD
      const_cast<CSSPropertyValue*>(FindPropertyPointer(property_id));
  if (to_replace == nullptr) {
    return nullptr;
  }
  if (may_have_logical_properties_) {
    const CSSProperty& prop = CSSProperty::Get(property_id);
    if (prop.IsInLogicalPropertyGroup()) {
      DCHECK(property_vector_.Contains(*to_replace));
      int to_replace_index =
          static_cast<int>(to_replace - property_vector_.data());
      for (int n = property_vector_.size() - 1; n > to_replace_index; --n) {
        if (prop.IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
                PropertyAt(n).PropertyID())) {
          RemovePropertyAtIndex(to_replace_index, nullptr);
          return nullptr;
        }
      }
    }
  }
  return to_replace;
}

MutableCSSPropertyValueSet::SetResult
MutableCSSPropertyValueSet::SetLonghandProperty(CSSPropertyValue property) {
  const CSSPropertyID id = property.PropertyID();
  DCHECK_EQ(shorthandForProperty(id).length(), 0u)
      << CSSProperty::Get(id).GetPropertyNameString() << " is a shorthand";
  CSSPropertyValue* to_replace;
  if (id == CSSPropertyID::kVariable) {
    to_replace = const_cast<CSSPropertyValue*>(
        FindPropertyPointer(property.Name().ToAtomicString()));
  } else {
    to_replace = FindInsertionPointForID(id);
  }
  if (to_replace) {
    if (*to_replace == property) {
      return kUnchanged;
=======
      slot ? slot : FindCSSPropertyWithName(property.Name());
  if (to_replace) {
    if (may_have_logical_properties_) {
      const CSSProperty& prop = CSSProperty::Get(property.Id());
      if (prop.IsInLogicalPropertyGroup()) {
        DCHECK(property_vector_.Contains(*to_replace));
        int to_replace_index = to_replace - property_vector_.begin();
        for (int n = property_vector_.size() - 1; n > to_replace_index; --n) {
          if (prop.IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
                  PropertyAt(n).Id())) {
            RemovePropertyAtIndex(to_replace_index, nullptr);
            to_replace = nullptr;
            break;
          }
        }
      }
    }
    if (to_replace) {
      if (*to_replace == property)
        return false;
      *to_replace = property;
      return true;
>>>>>>> chromium
    }
  } else if (!may_have_logical_properties_) {
    const CSSProperty& prop = CSSProperty::Get(property.Id());
    may_have_logical_properties_ =
        prop.IsInLogicalPropertyGroup() && prop.IsSurrogate();
  }
  property_vector_.push_back(property);
  return true;
}

bool MutableCSSPropertyValueSet::SetProperty(CSSPropertyID property_id,
                                             CSSValueID identifier,
                                             bool important) {
  CSSPropertyName name(property_id);
  SetProperty(CSSPropertyValue(name, *CSSIdentifierValue::Create(identifier),
                               important));
  return true;
}

void MutableCSSPropertyValueSet::ParseDeclarationList(
    const String& style_declaration,
    SecureContextMode secure_context_mode,
    StyleSheetContents* context_style_sheet) {
  property_vector_.clear();

  CSSParserContext* context;
  if (context_style_sheet) {
    context = MakeGarbageCollected<CSSParserContext>(
        context_style_sheet->ParserContext(), context_style_sheet);
    context->SetMode(CssParserMode());
  } else {
    context = MakeGarbageCollected<CSSParserContext>(CssParserMode(),
                                                     secure_context_mode);
  }

  CSSParser::ParseDeclarationList(context, this, style_declaration);
}

<<<<<<< HEAD
MutableCSSPropertyValueSet::SetResult
MutableCSSPropertyValueSet::AddParsedProperties(
    base::span<CSSPropertyValue> properties) {
  SetResult changed = kUnchanged;
  property_vector_.reserve(property_vector_.size() + properties.size());
  for (const CSSPropertyValue& property : properties) {
    changed = std::max(changed, SetLonghandProperty(property));
  }
=======
bool MutableCSSPropertyValueSet::AddParsedProperties(
    const HeapVector<CSSPropertyValue, 256>& properties) {
  bool changed = false;
  property_vector_.ReserveCapacity(property_vector_.size() + properties.size());
  for (unsigned i = 0; i < properties.size(); ++i)
    changed |= SetProperty(properties[i]);
>>>>>>> chromium
  return changed;
}

bool MutableCSSPropertyValueSet::AddRespectingCascade(
    const CSSPropertyValue& property) {
  // Only add properties that have no !important counterpart present
<<<<<<< HEAD
  if (!PropertyIsImportant(property.PropertyID()) || property.IsImportant()) {
    return SetLonghandProperty(property);
  }
=======
  if (!PropertyIsImportant(property.Id()) || property.IsImportant())
    return SetProperty(property);
>>>>>>> chromium
  return false;
}

String CSSPropertyValueSet::AsText() const {
  return StylePropertySerializer(*this).AsText();
}

void MutableCSSPropertyValueSet::MergeAndOverrideOnConflict(
    const CSSPropertyValueSet* other) {
<<<<<<< HEAD
  for (const CSSPropertyValue& property : other->Properties()) {
    SetLonghandProperty(property);
=======
  unsigned size = other->PropertyCount();
  for (unsigned n = 0; n < size; ++n) {
    PropertyReference to_merge = other->PropertyAt(n);
    CSSPropertyValue* old = FindCSSPropertyWithName(to_merge.Name());
    if (old) {
      SetProperty(
          CSSPropertyValue(to_merge.PropertyMetadata(), to_merge.Value()), old);
    } else {
      property_vector_.push_back(
          CSSPropertyValue(to_merge.PropertyMetadata(), to_merge.Value()));
    }
>>>>>>> chromium
  }
}

bool CSSPropertyValueSet::HasFailedOrCanceledSubresources() const {
<<<<<<< HEAD
  for (const CSSPropertyValue& property : Properties()) {
    if (property.Value().HasFailedOrCanceledSubresources()) {
=======
  unsigned size = PropertyCount();
  for (unsigned i = 0; i < size; ++i) {
    if (PropertyAt(i).Value().HasFailedOrCanceledSubresources())
>>>>>>> chromium
      return true;
  }
  return false;
}

void MutableCSSPropertyValueSet::Clear() {
  property_vector_.clear();
  may_have_logical_properties_ = false;
}

inline bool ContainsId(const CSSProperty* const set[],
                       unsigned length,
                       CSSPropertyID id) {
  for (unsigned i = 0; i < length; ++i) {
    if (set[i]->IDEquals(id))
      return true;
  }
  return false;
}

bool MutableCSSPropertyValueSet::RemovePropertiesInSet(
    const CSSProperty* const set[],
    unsigned length) {
  if (property_vector_.IsEmpty())
    return false;

  CSSPropertyValue* properties = property_vector_.data();
  unsigned old_size = property_vector_.size();
  unsigned new_index = 0;
  for (unsigned old_index = 0; old_index < old_size; ++old_index) {
    const CSSPropertyValue& property = properties[old_index];
<<<<<<< HEAD
    if (ContainsId(set, property.PropertyID())) {
=======
    if (ContainsId(set, length, property.Id()))
>>>>>>> chromium
      continue;
    // Modify property_vector_ in-place since this method is
    // performance-sensitive.
    properties[new_index++] = properties[old_index];
  }
  if (new_index != old_size) {
    property_vector_.Shrink(new_index);
    return true;
  }
  return false;
}

bool MutableCSSPropertyValueSet::RemovePropertiesAffectedByAll() {
  if (property_vector_.empty()) {
    return false;
  }

  base::span<CSSPropertyValue> properties(property_vector_);
  unsigned old_size = property_vector_.size();
  unsigned new_index = 0;
  for (unsigned old_index = 0; old_index < old_size; ++old_index) {
    const CSSPropertyValue& property = properties[old_index];
    if (CSSProperty::Get(property.PropertyID()).IsAffectedByAll()) {
      continue;
    }
    properties[new_index++] = properties[old_index];
  }
  if (new_index != old_size) {
    property_vector_.Shrink(new_index);
    InvalidateHashIfComputed();
    return true;
  }
  return false;
}

CSSPropertyValue* MutableCSSPropertyValueSet::FindCSSPropertyWithName(
    const CSSPropertyName& name) {
  int found_property_index = name.IsCustomProperty()
                                 ? FindPropertyIndex(name.ToAtomicString())
                                 : FindPropertyIndex(name.Id());
  if (found_property_index == -1)
    return nullptr;
  return &property_vector_.at(found_property_index);
}

bool CSSPropertyValueSet::PropertyMatches(
    CSSPropertyID property_id,
    const CSSValue& property_value) const {
  int found_property_index = FindPropertyIndex(property_id);
  if (found_property_index == -1)
    return false;
  return PropertyAt(found_property_index).Value() == property_value;
}

void MutableCSSPropertyValueSet::RemoveEquivalentProperties(
    const CSSPropertyValueSet* style) {
  Vector<CSSPropertyID> properties_to_remove;
  unsigned size = property_vector_.size();
  for (unsigned i = 0; i < size; ++i) {
<<<<<<< HEAD
    const CSSPropertyValue& property = PropertyAt(i);
    if (style->PropertyMatches(property.PropertyID(), property.Value())) {
      properties_to_remove.push_back(property.PropertyID());
    }
  }
  // FIXME: This should use mass removal.
  for (CSSPropertyID id : properties_to_remove) {
    RemoveProperty(id);
  }
=======
    PropertyReference property = PropertyAt(i);
    if (style->PropertyMatches(property.Id(), property.Value()))
      properties_to_remove.push_back(property.Id());
  }
  // FIXME: This should use mass removal.
  for (unsigned i = 0; i < properties_to_remove.size(); ++i)
    RemoveProperty(properties_to_remove[i]);
>>>>>>> chromium
}

void MutableCSSPropertyValueSet::RemoveEquivalentProperties(
    const CSSStyleDeclaration* style) {
  Vector<CSSPropertyID> properties_to_remove;
<<<<<<< HEAD
  for (const CSSPropertyValue& property : property_vector_) {
    if (style->CssPropertyMatches(property.PropertyID(), property.Value())) {
      properties_to_remove.push_back(property.PropertyID());
    }
  }
  // FIXME: This should use mass removal.
  for (CSSPropertyID id : properties_to_remove) {
    RemoveProperty(id);
  }
=======
  unsigned size = property_vector_.size();
  for (unsigned i = 0; i < size; ++i) {
    PropertyReference property = PropertyAt(i);
    if (style->CssPropertyMatches(property.Id(), property.Value()))
      properties_to_remove.push_back(property.Id());
  }
  // FIXME: This should use mass removal.
  for (unsigned i = 0; i < properties_to_remove.size(); ++i)
    RemoveProperty(properties_to_remove[i]);
>>>>>>> chromium
}

MutableCSSPropertyValueSet* CSSPropertyValueSet::MutableCopy() const {
  return MakeGarbageCollected<MutableCSSPropertyValueSet>(*this);
}

MutableCSSPropertyValueSet* CSSPropertyValueSet::CopyPropertiesInSet(
    const Vector<const CSSProperty*>& properties) const {
  HeapVector<CSSPropertyValue, 256> list;
  list.ReserveInitialCapacity(properties.size());
  for (unsigned i = 0; i < properties.size(); ++i) {
    CSSPropertyName name(properties[i]->PropertyID());
    const CSSValue* value = GetPropertyCSSValue(name.Id());
    if (value)
      list.push_back(CSSPropertyValue(name, *value, false));
  }
  return MakeGarbageCollected<MutableCSSPropertyValueSet>(list.data(),
                                                          list.size());
}

CSSStyleDeclaration* MutableCSSPropertyValueSet::EnsureCSSStyleDeclaration(
    ExecutionContext* execution_context) {
  // FIXME: get rid of this weirdness of a CSSStyleDeclaration inside of a
  // style property set.
  if (cssom_wrapper_) {
    DCHECK(
        !static_cast<CSSStyleDeclaration*>(cssom_wrapper_.Get())->parentRule());
    DCHECK(!cssom_wrapper_->ParentElement());
    return cssom_wrapper_.Get();
  }
  cssom_wrapper_ = MakeGarbageCollected<PropertySetCSSStyleDeclaration>(
      execution_context, *this);
  return cssom_wrapper_.Get();
}

template <typename T>
int MutableCSSPropertyValueSet::FindPropertyIndex(T property) const {
  const CSSPropertyValue* begin = property_vector_.data();
  const CSSPropertyValue* end = begin + property_vector_.size();

  uint16_t id = GetConvertedCSSPropertyID(property);

<<<<<<< HEAD
  auto it = std::find_if(
      property_vector_.begin(), property_vector_.end(),
      [property, id](const CSSPropertyValue& css_property) -> bool {
        return IsPropertyMatch(css_property, id, property);
=======
  const CSSPropertyValue* it = std::find_if(
      begin, end, [property, id](const CSSPropertyValue& css_property) -> bool {
        return IsPropertyMatch(css_property.Metadata(), *css_property.Value(),
                               id, property);
>>>>>>> chromium
      });

  return (it == end) ? -1 : static_cast<int>(it - begin);
}
template CORE_EXPORT int MutableCSSPropertyValueSet::FindPropertyIndex(
    CSSPropertyID) const;
template CORE_EXPORT int MutableCSSPropertyValueSet::FindPropertyIndex(
    AtomicString) const;

void MutableCSSPropertyValueSet::TraceAfterDispatch(
    blink::Visitor* visitor) const {
  visitor->Trace(cssom_wrapper_);
  visitor->Trace(property_vector_);
  CSSPropertyValueSet::TraceAfterDispatch(visitor);
}

unsigned CSSPropertyValueSet::AverageSizeInBytes() {
  // Please update this if the storage scheme changes so that this longer
  // reflects the actual size.
  return sizeof(ImmutableCSSPropertyValueSet) +
         AdditionalBytesForImmutableCSSPropertyValueSetWithPropertyCount(4)
             .value;
}

// See the function above if you need to update this.
struct SameSizeAsCSSPropertyValueSet final
    : public GarbageCollected<SameSizeAsCSSPropertyValueSet> {
  uint32_t bitfield;
};
ASSERT_SIZE(CSSPropertyValueSet, SameSizeAsCSSPropertyValueSet);

#ifndef NDEBUG
void CSSPropertyValueSet::ShowStyle() {
  fprintf(stderr, "%s\n", AsText().Ascii().c_str());
}
#endif

}  // namespace blink
