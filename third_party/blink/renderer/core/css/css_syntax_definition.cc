// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/css/css_syntax_definition.h"

#include <utility>
<<<<<<< HEAD

#include "third_party/blink/renderer/core/css/css_string_value.h"
=======
#include "third_party/blink/renderer/core/css/css_custom_property_declaration.h"
>>>>>>> chromium
#include "third_party/blink/renderer/core/css/css_syntax_component.h"
#include "third_party/blink/renderer/core/css/css_uri_value.h"
#include "third_party/blink/renderer/core/css/css_value_list.h"
#include "third_party/blink/renderer/core/css/css_variable_reference_value.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_idioms.h"
#include "third_party/blink/renderer/core/css/parser/css_variable_parser.h"
#include "third_party/blink/renderer/core/css/properties/css_parsing_utils.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_idioms.h"

namespace blink {
namespace {

// The 'revert' and 'default' keywords are reserved.
//
// https://drafts.csswg.org/css-cascade/#default
// https://drafts.csswg.org/css-values-4/#identifier-value
//
// TODO(crbug.com/579788): Implement 'revert'.
// TODO(crbug.com/882285): Make 'default' invalid as <custom-ident>.
bool IsReservedIdentToken(const CSSParserToken& token) {
  if (token.GetType() != kIdentToken)
    return false;
  return css_parsing_utils::IsRevertKeyword(token.Value()) ||
         css_parsing_utils::IsDefaultKeyword(token.Value());
}

bool CouldConsumeReservedKeyword(CSSParserTokenRange range) {
  range.ConsumeWhitespace();
  if (IsReservedIdentToken(range.ConsumeIncludingWhitespace()))
    return range.AtEnd();
  return false;
}

<<<<<<< HEAD
CSSSyntaxRepeat ConsumeSyntaxMultiplier(CSSParserTokenStream& stream) {
  if (stream.Peek().GetType() == kDelimiterToken &&
      stream.Peek().Delimiter() == '#') {
    stream.ConsumeIncludingWhitespace();
    return CSSSyntaxRepeat::kCommaSeparated;
  }
  if (stream.Peek().GetType() == kDelimiterToken &&
      stream.Peek().Delimiter() == '+') {
    stream.ConsumeIncludingWhitespace();
    return CSSSyntaxRepeat::kSpaceSeparated;
  }
  return CSSSyntaxRepeat::kNone;
}

std::optional<CSSSyntaxType> ConsumeTypeName(CSSParserTokenStream& stream) {
  if (stream.Peek().GetType() != kIdentToken) {
    return std::nullopt;
  }
  if (stream.Peek().Value() == "angle") {
    stream.Consume();
    return CSSSyntaxType::kAngle;
  }
  if (stream.Peek().Value() == "color") {
    stream.Consume();
    return CSSSyntaxType::kColor;
  }
  if (stream.Peek().Value() == "custom-ident") {
    stream.Consume();
    return CSSSyntaxType::kCustomIdent;
  }
  if (stream.Peek().Value() == "image") {
    stream.Consume();
    return CSSSyntaxType::kImage;
  }
  if (stream.Peek().Value() == "integer") {
    stream.Consume();
    return CSSSyntaxType::kInteger;
  }
  if (stream.Peek().Value() == "length") {
    stream.Consume();
    return CSSSyntaxType::kLength;
  }
  if (stream.Peek().Value() == "length-percentage") {
    stream.Consume();
    return CSSSyntaxType::kLengthPercentage;
  }
  if (stream.Peek().Value() == "number") {
    stream.Consume();
    return CSSSyntaxType::kNumber;
  }
  if (stream.Peek().Value() == "percentage") {
    stream.Consume();
    return CSSSyntaxType::kPercentage;
  }
  if (stream.Peek().Value() == "resolution") {
    stream.Consume();
    return CSSSyntaxType::kResolution;
  }
  if (RuntimeEnabledFeatures::CSSAtPropertyStringSyntaxEnabled() &&
      stream.Peek().Value() == "string") {
    stream.Consume();
    return CSSSyntaxType::kString;
  }
  if (stream.Peek().Value() == "time") {
    stream.Consume();
    return CSSSyntaxType::kTime;
  }
  if (stream.Peek().Value() == "url") {
    stream.Consume();
    return CSSSyntaxType::kUrl;
  }
  if (stream.Peek().Value() == "transform-function") {
    stream.Consume();
    return CSSSyntaxType::kTransformFunction;
  }
  if (stream.Peek().Value() == "transform-list") {
    stream.Consume();
    return CSSSyntaxType::kTransformList;
  }
  return std::nullopt;
}

std::optional<std::tuple<CSSSyntaxType, String>> ConsumeSyntaxSingleComponent(
    CSSParserTokenStream& stream) {
  if (stream.Peek().GetType() == kDelimiterToken &&
      stream.Peek().Delimiter() == '<') {
    CSSParserSavePoint save_point(stream);
    stream.Consume();
    std::optional<CSSSyntaxType> syntax_type = ConsumeTypeName(stream);
    if (!syntax_type.has_value()) {
      return std::nullopt;
    }
    if (stream.Peek().GetType() != kDelimiterToken ||
        stream.Peek().Delimiter() != '>') {
      return std::nullopt;
    }
    stream.Consume();
    save_point.Release();
    return std::make_tuple(*syntax_type, String());
  }
  CSSParserToken peek = stream.Peek();
  if (peek.GetType() != kIdentToken) {
    return std::nullopt;
  }
  if (css_parsing_utils::IsCSSWideKeyword(peek.Value()) ||
      css_parsing_utils::IsDefaultKeyword(peek.Value())) {
    return std::nullopt;
  }
  return std::make_tuple(CSSSyntaxType::kIdent,
                         stream.Consume().Value().ToString());
}

std::optional<CSSSyntaxComponent> ConsumeSyntaxComponent(
    CSSParserTokenStream& stream) {
  stream.EnsureLookAhead();
  CSSParserSavePoint save_point(stream);

  std::optional<std::tuple<CSSSyntaxType, String>> css_syntax_type_ident =
      ConsumeSyntaxSingleComponent(stream);
  if (!css_syntax_type_ident.has_value()) {
    return std::nullopt;
  }
  CSSSyntaxType syntax_type;
  String ident;
  std::tie(syntax_type, ident) = *css_syntax_type_ident;
  CSSSyntaxRepeat repeat = ConsumeSyntaxMultiplier(stream);
  stream.ConsumeWhitespace();
  if (syntax_type == CSSSyntaxType::kTransformList &&
      repeat != CSSSyntaxRepeat::kNone) {
    // <transform-list> may not be followed by a <syntax-multiplier>.
    // https://drafts.csswg.org/css-values-5/#css-syntax
    return std::nullopt;
  }
  save_point.Release();
  return CSSSyntaxComponent(syntax_type, ident, repeat);
}

const CSSValue* ConsumeSingleType(const CSSSyntaxComponent& syntax,
                                  CSSParserTokenStream& stream,
                                  const CSSParserContext& context,
                                  bool is_attr_tainted) {
=======
const CSSValue* ConsumeSingleType(const CSSSyntaxComponent& syntax,
                                  CSSParserTokenRange& range,
                                  const CSSParserContext& context) {
>>>>>>> chromium
  switch (syntax.GetType()) {
    case CSSSyntaxType::kIdent:
      if (range.Peek().GetType() == kIdentToken &&
          range.Peek().Value() == syntax.GetString()) {
        range.ConsumeIncludingWhitespace();
        return MakeGarbageCollected<CSSCustomIdentValue>(
            AtomicString(syntax.GetString()));
      }
      return nullptr;
    case CSSSyntaxType::kLength: {
      CSSParserContext::ParserModeOverridingScope scope(context,
                                                        kHTMLStandardMode);
      return css_parsing_utils::ConsumeLength(range, context,
                                              ValueRange::kValueRangeAll);
    }
    case CSSSyntaxType::kNumber:
      return css_parsing_utils::ConsumeNumber(range, context,
                                              ValueRange::kValueRangeAll);
    case CSSSyntaxType::kPercentage:
      return css_parsing_utils::ConsumePercent(range, context,
                                               ValueRange::kValueRangeAll);
    case CSSSyntaxType::kLengthPercentage: {
      CSSParserContext::ParserModeOverridingScope scope(context,
                                                        kHTMLStandardMode);
      return css_parsing_utils::ConsumeLengthOrPercent(
          range, context, ValueRange::kValueRangeAll);
    }
    case CSSSyntaxType::kColor: {
      CSSParserContext::ParserModeOverridingScope scope(context,
                                                        kHTMLStandardMode);
      return css_parsing_utils::ConsumeColor(range, context);
    }
    case CSSSyntaxType::kImage:
      return css_parsing_utils::ConsumeImage(range, context);
    case CSSSyntaxType::kUrl:
<<<<<<< HEAD
      if (is_attr_tainted) {
        return nullptr;
      }
      return css_parsing_utils::ConsumeUrl(stream, context);
=======
      return css_parsing_utils::ConsumeUrl(range, context);
>>>>>>> chromium
    case CSSSyntaxType::kInteger:
      return css_parsing_utils::ConsumeIntegerOrNumberCalc(range, context);
    case CSSSyntaxType::kAngle:
      return css_parsing_utils::ConsumeAngle(range, context,
                                             absl::optional<WebFeature>());
    case CSSSyntaxType::kTime:
      return css_parsing_utils::ConsumeTime(range, context,
                                            ValueRange::kValueRangeAll);
    case CSSSyntaxType::kResolution:
      return css_parsing_utils::ConsumeResolution(range);
    case CSSSyntaxType::kTransformFunction:
      return css_parsing_utils::ConsumeTransformValue(range, context);
    case CSSSyntaxType::kTransformList:
      return css_parsing_utils::ConsumeTransformList(range, context);
    case CSSSyntaxType::kCustomIdent:
      // TODO(crbug.com/579788): Implement 'revert'.
      // TODO(crbug.com/882285): Make 'default' invalid as <custom-ident>.
      if (IsReservedIdentToken(range.Peek()))
        return nullptr;
      return css_parsing_utils::ConsumeCustomIdent(range, context);
    default:
      NOTREACHED();
      return nullptr;
  }
}

const CSSValue* ConsumeSyntaxComponent(const CSSSyntaxComponent& syntax,
<<<<<<< HEAD
                                       CSSParserTokenStream& stream,
                                       const CSSParserContext& context,
                                       bool is_attr_tainted) {
  // CSS-wide keywords are already handled by the CSSPropertyParser
  if (syntax.GetRepeat() == CSSSyntaxRepeat::kSpaceSeparated) {
    CSSValueList* list = CSSValueList::CreateSpaceSeparated();
    while (!stream.AtEnd()) {
      const CSSValue* value =
          ConsumeSingleType(syntax, stream, context, is_attr_tainted);
      if (!value) {
=======
                                       CSSParserTokenRange range,
                                       const CSSParserContext& context) {
  // CSS-wide keywords are already handled by the CSSPropertyParser
  if (syntax.GetRepeat() == CSSSyntaxRepeat::kSpaceSeparated) {
    CSSValueList* list = CSSValueList::CreateSpaceSeparated();
    while (!range.AtEnd()) {
      const CSSValue* value = ConsumeSingleType(syntax, range, context);
      if (!value)
>>>>>>> chromium
        return nullptr;
      list->Append(*value);
    }
    return list->length() ? list : nullptr;
  }
  if (syntax.GetRepeat() == CSSSyntaxRepeat::kCommaSeparated) {
    CSSValueList* list = CSSValueList::CreateCommaSeparated();
    do {
<<<<<<< HEAD
      const CSSValue* value =
          ConsumeSingleType(syntax, stream, context, is_attr_tainted);
      if (!value) {
=======
      const CSSValue* value = ConsumeSingleType(syntax, range, context);
      if (!value)
>>>>>>> chromium
        return nullptr;
      list->Append(*value);
    } while (css_parsing_utils::ConsumeCommaIncludingWhitespace(range));
    return list->length() ? list : nullptr;
  }
<<<<<<< HEAD
  const CSSValue* result =
      ConsumeSingleType(syntax, stream, context, is_attr_tainted);
  if (!stream.AtEnd()) {
=======
  const CSSValue* result = ConsumeSingleType(syntax, range, context);
  if (!range.AtEnd())
>>>>>>> chromium
    return nullptr;
  return result;
}

}  // namespace

<<<<<<< HEAD
std::optional<CSSSyntaxDefinition> CSSSyntaxDefinition::Consume(
    CSSParserTokenStream& stream) {
  if (stream.Peek().GetType() == kDelimiterToken &&
      stream.Peek().Delimiter() == '*') {
    stream.ConsumeIncludingWhitespace();
    return CSSSyntaxDefinition::CreateUniversal();
  }

  Vector<CSSSyntaxComponent> syntax_components;
  CSSParserSavePoint save_point(stream);
  do {
    std::optional<CSSSyntaxComponent> syntax_component =
        ConsumeSyntaxComponent(stream);
    if (!syntax_component.has_value()) {
      return std::nullopt;
    }
    syntax_components.emplace_back(*syntax_component);
  } while (ConsumeSyntaxCombinator(stream));

  save_point.Release();
  return CSSSyntaxDefinition(std::move(syntax_components));
}

std::optional<CSSSyntaxDefinition> CSSSyntaxDefinition::ConsumeComponent(
    CSSParserTokenStream& stream) {
  if (std::optional<CSSSyntaxComponent> syntax_component =
          ConsumeSyntaxComponent(stream)) {
    Vector<CSSSyntaxComponent> syntax_components(1u, syntax_component.value());
    return CSSSyntaxDefinition(std::move(syntax_components));
  }
  return std::nullopt;
}

const CSSValue* CSSSyntaxDefinition::Parse(StringView text,
=======
const CSSValue* CSSSyntaxDefinition::Parse(CSSParserTokenRange range,
>>>>>>> chromium
                                           const CSSParserContext& context,
                                           bool is_animation_tainted,
                                           bool is_attr_tainted) const {
  if (IsUniversal()) {
    // TODO(crbug.com/579788): Implement 'revert'.
    // TODO(crbug.com/882285): Make 'default' invalid as <custom-ident>.
    if (CouldConsumeReservedKeyword(range))
      return nullptr;
    return CSSVariableParser::ParseRegisteredPropertyValue(
        range, context, false, is_animation_tainted);
  }
  range.ConsumeWhitespace();
  for (const CSSSyntaxComponent& component : syntax_components_) {
<<<<<<< HEAD
    CSSParserTokenStream stream(text);
    stream.ConsumeWhitespace();
    if (const CSSValue* result = ConsumeSyntaxComponent(
            component, stream, context, is_attr_tainted)) {
=======
    if (const CSSValue* result =
            ConsumeSyntaxComponent(component, range, context))
>>>>>>> chromium
      return result;
  }
  return CSSVariableParser::ParseRegisteredPropertyValue(range, context, true,
                                                         is_animation_tainted);
}

CSSSyntaxDefinition CSSSyntaxDefinition::IsolatedCopy() const {
  Vector<CSSSyntaxComponent> syntax_components_copy;
  syntax_components_copy.ReserveCapacity(syntax_components_.size());
  for (const auto& syntax_component : syntax_components_) {
    syntax_components_copy.push_back(CSSSyntaxComponent(
        syntax_component.GetType(), syntax_component.GetString().IsolatedCopy(),
        syntax_component.GetRepeat()));
  }
  return CSSSyntaxDefinition(std::move(syntax_components_copy));
}

CSSSyntaxDefinition::CSSSyntaxDefinition(Vector<CSSSyntaxComponent> components)
    : syntax_components_(std::move(components)) {
  DCHECK(syntax_components_.size());
}

CSSSyntaxDefinition CSSSyntaxDefinition::CreateUniversal() {
  Vector<CSSSyntaxComponent> components;
  components.push_back(CSSSyntaxComponent(
      CSSSyntaxType::kTokenStream, g_empty_string, CSSSyntaxRepeat::kNone));
  return CSSSyntaxDefinition(std::move(components));
}

}  // namespace blink
