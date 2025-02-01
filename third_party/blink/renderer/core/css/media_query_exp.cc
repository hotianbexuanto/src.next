/*
 * CSS Media Query
 *
 * Copyright (C) 2006 Kimmo Kinnunen <kimmo.t.kinnunen@nokia.com>.
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (C) 2013 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "third_party/blink/renderer/core/css/media_query_exp.h"

#include "third_party/blink/renderer/core/css/css_math_expression_node.h"
#include "third_party/blink/renderer/core/css/css_math_function_value.h"
#include "third_party/blink/renderer/core/css/css_numeric_literal_value.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_context.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_token_range.h"
#include "third_party/blink/renderer/core/css/properties/css_parsing_utils.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_idioms.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/decimal.h"
#include "third_party/blink/renderer/platform/wtf/text/string_buffer.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

namespace blink {

using media_feature_names::kMaxDeviceAspectRatioMediaFeature;
using media_feature_names::kMaxDevicePixelRatioMediaFeature;
using media_feature_names::kMinDeviceAspectRatioMediaFeature;

static inline bool FeatureWithValidIdent(const String& media_feature,
                                         CSSValueID ident) {
  if (media_feature == media_feature_names::kDisplayModeMediaFeature) {
    return ident == CSSValueID::kFullscreen ||
           ident == CSSValueID::kStandalone ||
           ident == CSSValueID::kMinimalUi || ident == CSSValueID::kBrowser;
  }

  if (media_feature == media_feature_names::kOrientationMediaFeature)
    return ident == CSSValueID::kPortrait || ident == CSSValueID::kLandscape;

  if (media_feature == media_feature_names::kPointerMediaFeature ||
      media_feature == media_feature_names::kAnyPointerMediaFeature) {
    return ident == CSSValueID::kNone || ident == CSSValueID::kCoarse ||
           ident == CSSValueID::kFine;
  }

  if (media_feature == media_feature_names::kHoverMediaFeature ||
      media_feature == media_feature_names::kAnyHoverMediaFeature)
    return ident == CSSValueID::kNone || ident == CSSValueID::kHover;

  if (media_feature == media_feature_names::kScanMediaFeature)
    return ident == CSSValueID::kInterlace || ident == CSSValueID::kProgressive;

  if (media_feature == media_feature_names::kColorGamutMediaFeature) {
    return ident == CSSValueID::kSRGB || ident == CSSValueID::kP3 ||
           ident == CSSValueID::kRec2020;
  }

  if (media_feature == media_feature_names::kPrefersColorSchemeMediaFeature)
    return ident == CSSValueID::kDark || ident == CSSValueID::kLight;

  if (RuntimeEnabledFeatures::PrefersContrastEnabled()) {
    if (media_feature == media_feature_names::kPrefersContrastMediaFeature) {
      return ident == CSSValueID::kNoPreference || ident == CSSValueID::kMore ||
             ident == CSSValueID::kLess || ident == CSSValueID::kForced;
    }
  }

  if (media_feature == media_feature_names::kPrefersReducedMotionMediaFeature)
    return ident == CSSValueID::kNoPreference || ident == CSSValueID::kReduce;

  if (RuntimeEnabledFeatures::PrefersReducedDataEnabled() &&
      media_feature == media_feature_names::kPrefersReducedDataMediaFeature) {
    return ident == CSSValueID::kNoPreference || ident == CSSValueID::kReduce;
  }

  if (RuntimeEnabledFeatures::ForcedColorsEnabled()) {
    if (media_feature == media_feature_names::kForcedColorsMediaFeature) {
      return ident == CSSValueID::kNone || ident == CSSValueID::kActive;
    }
  }

  if (RuntimeEnabledFeatures::MediaQueryNavigationControlsEnabled()) {
    if (media_feature == media_feature_names::kNavigationControlsMediaFeature) {
      return ident == CSSValueID::kNone || ident == CSSValueID::kBackButton;
    }
  }

  if (RuntimeEnabledFeatures::CSSFoldablesEnabled()) {
    if (media_feature == media_feature_names::kScreenSpanningMediaFeature) {
      return ident == CSSValueID::kNone ||
             ident == CSSValueID::kSingleFoldVertical ||
             ident == CSSValueID::kSingleFoldHorizontal;
    }
  }

  if (RuntimeEnabledFeatures::DevicePostureEnabled()) {
    if (media_feature == media_feature_names::kDevicePostureMediaFeature) {
<<<<<<< HEAD
      return ident == CSSValueID::kContinuous || ident == CSSValueID::kFolded;
    }
  }

  if (media_feature == media_feature_names::kOverflowInlineMediaFeature) {
    return ident == CSSValueID::kNone || ident == CSSValueID::kScroll;
  }

  if (media_feature == media_feature_names::kOverflowBlockMediaFeature) {
    return ident == CSSValueID::kNone || ident == CSSValueID::kScroll ||
           ident == CSSValueID::kPaged;
  }

  if (media_feature == media_feature_names::kUpdateMediaFeature) {
    return ident == CSSValueID::kNone || ident == CSSValueID::kFast ||
           ident == CSSValueID::kSlow;
  }

  if (RuntimeEnabledFeatures::CSSStickyContainerQueriesEnabled()) {
    if (media_feature == media_feature_names::kStuckMediaFeature) {
      switch (ident) {
        case CSSValueID::kNone:
        case CSSValueID::kTop:
        case CSSValueID::kLeft:
        case CSSValueID::kBottom:
        case CSSValueID::kRight:
        case CSSValueID::kBlockStart:
        case CSSValueID::kBlockEnd:
        case CSSValueID::kInlineStart:
        case CSSValueID::kInlineEnd:
          return true;
        default:
          return false;
      }
    }
  }

  if (media_feature == media_feature_names::kScriptingMediaFeature) {
    return ident == CSSValueID::kEnabled || ident == CSSValueID::kInitialOnly ||
           ident == CSSValueID::kNone;
  }

  if (RuntimeEnabledFeatures::CSSSnapContainerQueriesEnabled()) {
    if (media_feature == media_feature_names::kSnappedMediaFeature) {
      switch (ident) {
        case CSSValueID::kNone:
        case CSSValueID::kBlock:
        case CSSValueID::kInline:
        case CSSValueID::kX:
        case CSSValueID::kY:
        case CSSValueID::kBoth:
          return true;
        default:
          return false;
      }
    }
  }

  if (RuntimeEnabledFeatures::CSSScrollableContainerQueriesEnabled()) {
    if (media_feature == media_feature_names::kScrollableMediaFeature) {
      switch (ident) {
        case CSSValueID::kNone:
        case CSSValueID::kTop:
        case CSSValueID::kLeft:
        case CSSValueID::kBottom:
        case CSSValueID::kRight:
        case CSSValueID::kBlockStart:
        case CSSValueID::kBlockEnd:
        case CSSValueID::kInlineStart:
        case CSSValueID::kInlineEnd:
        case CSSValueID::kBlock:
        case CSSValueID::kInline:
        case CSSValueID::kX:
        case CSSValueID::kY:
          return true;
        default:
          return false;
      }
=======
      return ident == CSSValueID::kNoFold || ident == CSSValueID::kLaptop ||
             ident == CSSValueID::kFlat || ident == CSSValueID::kTent ||
             ident == CSSValueID::kTablet || ident == CSSValueID::kBook;
>>>>>>> chromium
    }
  }

  return false;
}

static inline bool FeatureWithValidPositiveLength(
    const String& media_feature,
    const CSSPrimitiveValue* value) {
  if (!(value->IsLength() ||
<<<<<<< HEAD
        (value->IsNumber() && value->GetValueIfKnown() == 0.0))) {
=======
        (value->IsNumber() && value->GetDoubleValue() == 0)))
>>>>>>> chromium
    return false;

  return media_feature == media_feature_names::kHeightMediaFeature ||
         media_feature == media_feature_names::kMaxHeightMediaFeature ||
         media_feature == media_feature_names::kMinHeightMediaFeature ||
         media_feature == media_feature_names::kWidthMediaFeature ||
         media_feature == media_feature_names::kMaxWidthMediaFeature ||
         media_feature == media_feature_names::kMinWidthMediaFeature ||
         media_feature == media_feature_names::kDeviceHeightMediaFeature ||
         media_feature == media_feature_names::kMaxDeviceHeightMediaFeature ||
         media_feature == media_feature_names::kMinDeviceHeightMediaFeature ||
         media_feature == media_feature_names::kDeviceWidthMediaFeature ||
         media_feature == media_feature_names::kMinDeviceWidthMediaFeature ||
         media_feature == media_feature_names::kMaxDeviceWidthMediaFeature;
}

static inline bool FeatureWithValidDensity(const String& media_feature,
                                           const CSSPrimitiveValue* value) {
<<<<<<< HEAD
  // NOTE: The allowed range of <resolution> values always excludes negative
  // values, in addition to any explicit ranges that might be specified.
  // https://drafts.csswg.org/css-values/#resolution
  if (!value->IsResolution() || (value->GetValueIfKnown().has_value() &&
                                 *value->GetValueIfKnown() < 0.0)) {
=======
  if (!value->IsResolution() || value->GetDoubleValue() <= 0)
>>>>>>> chromium
    return false;

  return media_feature == media_feature_names::kResolutionMediaFeature ||
         media_feature == media_feature_names::kMinResolutionMediaFeature ||
         media_feature == media_feature_names::kMaxResolutionMediaFeature;
}

static inline bool FeatureExpectingPositiveInteger(
    const String& media_feature) {
  return media_feature == media_feature_names::kColorMediaFeature ||
         media_feature == media_feature_names::kMaxColorMediaFeature ||
         media_feature == media_feature_names::kMinColorMediaFeature ||
         media_feature == media_feature_names::kColorIndexMediaFeature ||
         media_feature == media_feature_names::kMaxColorIndexMediaFeature ||
         media_feature == media_feature_names::kMinColorIndexMediaFeature ||
         media_feature == media_feature_names::kMonochromeMediaFeature ||
         media_feature == media_feature_names::kMaxMonochromeMediaFeature ||
         media_feature == media_feature_names::kMinMonochromeMediaFeature ||
         media_feature == media_feature_names::kImmersiveMediaFeature;
}

static inline bool FeatureWithPositiveInteger(const String& media_feature,
                                              const CSSPrimitiveValue* value) {
  if (!value->IsInteger())
    return false;
  return FeatureExpectingPositiveInteger(media_feature);
}

static inline bool FeatureWithPositiveNumber(const String& media_feature,
                                             const CSSPrimitiveValue* value) {
  if (!value->IsNumber())
    return false;

  return media_feature == media_feature_names::kTransform3dMediaFeature ||
         media_feature == media_feature_names::kDevicePixelRatioMediaFeature ||
         media_feature == kMaxDevicePixelRatioMediaFeature ||
         media_feature == media_feature_names::kMinDevicePixelRatioMediaFeature;
}

static inline bool FeatureWithZeroOrOne(const String& media_feature,
                                        const CSSPrimitiveValue* value) {
  if (!value->IsInteger() ||
<<<<<<< HEAD
      (value->GetValueIfKnown().has_value() &&
       *value->GetValueIfKnown() != 1.0 && *value->GetValueIfKnown() != 0.0)) {
=======
      !(value->GetDoubleValue() == 1 || !value->GetDoubleValue()))
>>>>>>> chromium
    return false;

  return media_feature == media_feature_names::kGridMediaFeature;
}

static inline bool FeatureWithAspectRatio(const String& media_feature) {
  return media_feature == media_feature_names::kAspectRatioMediaFeature ||
         media_feature == media_feature_names::kDeviceAspectRatioMediaFeature ||
         media_feature == media_feature_names::kMinAspectRatioMediaFeature ||
         media_feature == media_feature_names::kMaxAspectRatioMediaFeature ||
         media_feature == kMinDeviceAspectRatioMediaFeature ||
         media_feature == kMaxDeviceAspectRatioMediaFeature;
}

static inline bool FeatureWithoutValue(
    const String& media_feature,
    const ExecutionContext* execution_context) {
  // Media features that are prefixed by min/max cannot be used without a value.
  return media_feature == media_feature_names::kMonochromeMediaFeature ||
         media_feature == media_feature_names::kColorMediaFeature ||
         media_feature == media_feature_names::kColorIndexMediaFeature ||
         media_feature == media_feature_names::kGridMediaFeature ||
         media_feature == media_feature_names::kHeightMediaFeature ||
         media_feature == media_feature_names::kWidthMediaFeature ||
         media_feature == media_feature_names::kDeviceHeightMediaFeature ||
         media_feature == media_feature_names::kDeviceWidthMediaFeature ||
         media_feature == media_feature_names::kOrientationMediaFeature ||
         media_feature == media_feature_names::kAspectRatioMediaFeature ||
         media_feature == media_feature_names::kDeviceAspectRatioMediaFeature ||
         media_feature == media_feature_names::kHoverMediaFeature ||
         media_feature == media_feature_names::kAnyHoverMediaFeature ||
         media_feature == media_feature_names::kTransform3dMediaFeature ||
         media_feature == media_feature_names::kPointerMediaFeature ||
         media_feature == media_feature_names::kAnyPointerMediaFeature ||
         media_feature == media_feature_names::kDevicePixelRatioMediaFeature ||
         media_feature == media_feature_names::kResolutionMediaFeature ||
         media_feature == media_feature_names::kDisplayModeMediaFeature ||
         media_feature == media_feature_names::kScanMediaFeature ||
         media_feature == media_feature_names::kColorGamutMediaFeature ||
         media_feature == media_feature_names::kImmersiveMediaFeature ||
         media_feature ==
             media_feature_names::kPrefersColorSchemeMediaFeature ||
         (media_feature == media_feature_names::kPrefersContrastMediaFeature &&
          RuntimeEnabledFeatures::PrefersContrastEnabled()) ||
         media_feature ==
             media_feature_names::kPrefersReducedMotionMediaFeature ||
         (media_feature ==
              media_feature_names::kPrefersReducedDataMediaFeature &&
          RuntimeEnabledFeatures::PrefersReducedDataEnabled()) ||
         (media_feature == media_feature_names::kForcedColorsMediaFeature &&
          RuntimeEnabledFeatures::ForcedColorsEnabled()) ||
         (media_feature ==
              media_feature_names::kNavigationControlsMediaFeature &&
          RuntimeEnabledFeatures::MediaQueryNavigationControlsEnabled()) ||
         (media_feature == media_feature_names::kOriginTrialTestMediaFeature &&
          RuntimeEnabledFeatures::OriginTrialsSampleAPIEnabled(
              execution_context)) ||
         (media_feature == media_feature_names::kScreenSpanningMediaFeature &&
          RuntimeEnabledFeatures::CSSFoldablesEnabled()) ||
         (media_feature == media_feature_names::kDevicePostureMediaFeature &&
          RuntimeEnabledFeatures::DevicePostureEnabled());
}

bool MediaQueryExp::IsViewportDependent() const {
  return media_feature_ == media_feature_names::kWidthMediaFeature ||
         media_feature_ == media_feature_names::kHeightMediaFeature ||
         media_feature_ == media_feature_names::kMinWidthMediaFeature ||
         media_feature_ == media_feature_names::kMinHeightMediaFeature ||
         media_feature_ == media_feature_names::kMaxWidthMediaFeature ||
         media_feature_ == media_feature_names::kMaxHeightMediaFeature ||
         media_feature_ == media_feature_names::kOrientationMediaFeature ||
         media_feature_ == media_feature_names::kAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kMinAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kDevicePixelRatioMediaFeature ||
         media_feature_ == media_feature_names::kResolutionMediaFeature ||
         media_feature_ == media_feature_names::kMaxAspectRatioMediaFeature ||
         media_feature_ == kMaxDevicePixelRatioMediaFeature ||
         media_feature_ ==
             media_feature_names::kMinDevicePixelRatioMediaFeature;
}

bool MediaQueryExp::IsDeviceDependent() const {
  return media_feature_ ==
             media_feature_names::kDeviceAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kDeviceWidthMediaFeature ||
         media_feature_ == media_feature_names::kDeviceHeightMediaFeature ||
         media_feature_ == kMinDeviceAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kMinDeviceWidthMediaFeature ||
         media_feature_ == media_feature_names::kMinDeviceHeightMediaFeature ||
         media_feature_ == kMaxDeviceAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kMaxDeviceWidthMediaFeature ||
         media_feature_ == media_feature_names::kMaxDeviceHeightMediaFeature;
}

bool MediaQueryExp::IsWidthDependent() const {
  return media_feature_ == media_feature_names::kWidthMediaFeature ||
         media_feature_ == media_feature_names::kMinWidthMediaFeature ||
         media_feature_ == media_feature_names::kMaxWidthMediaFeature ||
         media_feature_ == media_feature_names::kAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kMinAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kMaxAspectRatioMediaFeature;
}

bool MediaQueryExp::IsHeightDependent() const {
  return media_feature_ == media_feature_names::kHeightMediaFeature ||
         media_feature_ == media_feature_names::kMinHeightMediaFeature ||
         media_feature_ == media_feature_names::kMaxHeightMediaFeature ||
         media_feature_ == media_feature_names::kAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kMinAspectRatioMediaFeature ||
         media_feature_ == media_feature_names::kMaxAspectRatioMediaFeature;
}

MediaQueryExp::MediaQueryExp(const MediaQueryExp& other)
    : media_feature_(other.MediaFeature()), exp_value_(other.ExpValue()) {}

MediaQueryExp::MediaQueryExp(const String& media_feature,
                             const MediaQueryExpValue& exp_value)
    : media_feature_(media_feature), exp_value_(exp_value) {}

MediaQueryExp MediaQueryExp::Create(const String& media_feature,
                                    CSSParserTokenRange& range,
                                    const CSSParserContext& context,
                                    const ExecutionContext* execution_context) {
  DCHECK(!media_feature.IsNull());

  MediaQueryExpValue exp_value;
  String lower_media_feature =
      AttemptStaticStringCreation(media_feature.LowerASCII());

  CSSParserContext::ParserModeOverridingScope scope(context, kHTMLStandardMode);

  CSSPrimitiveValue* value =
      css_parsing_utils::ConsumeInteger(range, context, 0);
  if (!value && !FeatureExpectingPositiveInteger(lower_media_feature) &&
      !FeatureWithAspectRatio(lower_media_feature)) {
    value = css_parsing_utils::ConsumeNumber(range, context,
                                             kValueRangeNonNegative);
  }
  if (!value) {
    value = css_parsing_utils::ConsumeLength(range, context,
                                             kValueRangeNonNegative);
  }
  if (!value)
    value = css_parsing_utils::ConsumeResolution(range);

  if (!value) {
    if (CSSIdentifierValue* ident = css_parsing_utils::ConsumeIdent(range)) {
      CSSValueID ident_id = ident->GetValueID();
      if (!FeatureWithValidIdent(lower_media_feature, ident_id))
        return Invalid();
      exp_value.id = ident_id;
      exp_value.is_id = true;
      return MediaQueryExp(lower_media_feature, exp_value);
    }
    if (FeatureWithoutValue(lower_media_feature, execution_context)) {
      // Valid, creates a MediaQueryExp with an 'invalid' MediaQueryExpValue
      return MediaQueryExp(lower_media_feature, exp_value);
    }
    return Invalid();
  }

  // Now we have |value| as a number, length or resolution
  // Create value for media query expression that must have 1 or more values.
<<<<<<< HEAD
  if (FeatureWithAspectRatio(media_feature)) {
    if (value->GetValueIfKnown().has_value() &&
        *value->GetValueIfKnown() < 0.0) {
      return std::nullopt;
    }
    if (!css_parsing_utils::ConsumeSlashIncludingWhitespace(stream)) {
      return MediaQueryExpValue(*value,
                                *CSSNumericLiteralValue::Create(
                                    1, CSSPrimitiveValue::UnitType::kNumber));
    }
    CSSPrimitiveValue* denominator = css_parsing_utils::ConsumeNumber(
        stream, context, CSSPrimitiveValue::ValueRange::kNonNegative);
    if (!denominator) {
      return std::nullopt;
    }
    if (value->GetValueIfKnown() == 0.0 &&
        denominator->GetValueIfKnown() == 0.0) {
      return MediaQueryExpValue(*CSSNumericLiteralValue::Create(
                                    1, CSSPrimitiveValue::UnitType::kNumber),
                                *CSSNumericLiteralValue::Create(
                                    0, CSSPrimitiveValue::UnitType::kNumber));
    }
    return MediaQueryExpValue(*value, *denominator);
=======
  if (FeatureWithAspectRatio(lower_media_feature)) {
    if (!value->IsInteger() || value->GetDoubleValue() == 0)
      return Invalid();
    if (!css_parsing_utils::ConsumeSlashIncludingWhitespace(range))
      return Invalid();
    CSSPrimitiveValue* denominator =
        css_parsing_utils::ConsumePositiveInteger(range, context);
    if (!denominator)
      return Invalid();

    exp_value.numerator = clampTo<unsigned>(value->GetDoubleValue());
    exp_value.denominator = clampTo<unsigned>(denominator->GetDoubleValue());
    exp_value.is_ratio = true;
    return MediaQueryExp(lower_media_feature, exp_value);
>>>>>>> chromium
  }

  if (FeatureWithValidDensity(lower_media_feature, value)) {
    // TODO(crbug.com/983613): Support resolution in math functions.
    DCHECK(value->IsNumericLiteralValue());
    const auto* numeric_literal = To<CSSNumericLiteralValue>(value);
    exp_value.value = numeric_literal->DoubleValue();
    exp_value.unit = numeric_literal->GetType();
    exp_value.is_value = true;
    return MediaQueryExp(lower_media_feature, exp_value);
  }

  if (FeatureWithPositiveInteger(lower_media_feature, value) ||
      FeatureWithPositiveNumber(lower_media_feature, value) ||
      FeatureWithZeroOrOne(lower_media_feature, value)) {
    exp_value.value = value->GetDoubleValue();
    exp_value.unit = CSSPrimitiveValue::UnitType::kNumber;
    exp_value.is_value = true;
    return MediaQueryExp(lower_media_feature, exp_value);
  }

  if (FeatureWithValidPositiveLength(lower_media_feature, value)) {
    if (value->IsNumber()) {
      exp_value.value = value->GetDoubleValue();
      exp_value.unit = CSSPrimitiveValue::UnitType::kNumber;
      exp_value.is_value = true;
      return MediaQueryExp(lower_media_feature, exp_value);
    }

    DCHECK(value->IsLength());
    if (const auto* numeric_literal =
            DynamicTo<CSSNumericLiteralValue>(value)) {
      exp_value.value = numeric_literal->GetDoubleValue();
      exp_value.unit = numeric_literal->GetType();
      exp_value.is_value = true;
      return MediaQueryExp(lower_media_feature, exp_value);
    }

    const auto* math_value = To<CSSMathFunctionValue>(value);
    CSSPrimitiveValue::UnitType expression_unit =
        math_value->ExpressionNode()->ResolvedUnitType();
    if (expression_unit == CSSPrimitiveValue::UnitType::kUnknown) {
      // TODO(crbug.com/982542): Support math expressions involving type
      // conversions properly. For example, calc(10px + 1em).
      return Invalid();
    }
    exp_value.value = math_value->DoubleValue();
    exp_value.unit = expression_unit;
    exp_value.is_value = true;
    return MediaQueryExp(lower_media_feature, exp_value);
  }

  return Invalid();
}

MediaQueryExp::~MediaQueryExp() = default;

bool MediaQueryExp::operator==(const MediaQueryExp& other) const {
  return (other.media_feature_ == media_feature_) &&
         ((!other.exp_value_.IsValid() && !exp_value_.IsValid()) ||
          (other.exp_value_.IsValid() && exp_value_.IsValid() &&
           other.exp_value_.Equals(exp_value_)));
}

String MediaQueryExp::Serialize() const {
  StringBuilder result;
  result.Append('(');
  result.Append(media_feature_.LowerASCII());
  if (exp_value_.IsValid()) {
    result.Append(": ");
    result.Append(exp_value_.CssText());
  }
  result.Append(')');

  return result.ToString();
}

static inline String PrintNumber(double number) {
  return Decimal::FromDouble(number).ToString();
}

String MediaQueryExpValue::CssText() const {
  StringBuilder output;
  if (is_value) {
    output.Append(PrintNumber(value));
    output.Append(CSSPrimitiveValue::UnitTypeToString(unit));
  } else if (is_ratio) {
    output.Append(PrintNumber(numerator));
    output.Append(" / ");
    output.Append(PrintNumber(denominator));
  } else if (is_id) {
    output.Append(getValueName(id));
  }

<<<<<<< HEAD
  return output.ReleaseString();
}

unsigned MediaQueryExpValue::GetUnitFlags() const {
  CSSPrimitiveValue::LengthTypeFlags length_type_flags;

  if (IsValue()) {
    if (auto* primitive = DynamicTo<CSSPrimitiveValue>(GetCSSValue())) {
      primitive->AccumulateLengthUnitTypes(length_type_flags);
    }
  }

  unsigned unit_flags = 0;

  if (length_type_flags.test(CSSPrimitiveValue::kUnitTypeFontSize) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeFontXSize) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeZeroCharacterWidth) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeFontCapitalHeight) ||
      length_type_flags.test(
          CSSPrimitiveValue::kUnitTypeIdeographicFullWidth) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeLineHeight)) {
    unit_flags |= UnitFlags::kFontRelative;
  }

  if (length_type_flags.test(CSSPrimitiveValue::kUnitTypeRootFontSize) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeRootFontXSize) ||
      length_type_flags.test(
          CSSPrimitiveValue::kUnitTypeRootFontCapitalHeight) ||
      length_type_flags.test(
          CSSPrimitiveValue::kUnitTypeRootFontZeroCharacterWidth) ||
      length_type_flags.test(
          CSSPrimitiveValue::kUnitTypeRootFontIdeographicFullWidth) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeRootLineHeight)) {
    unit_flags |= UnitFlags::kRootFontRelative;
  }

  if (CSSPrimitiveValue::HasDynamicViewportUnits(length_type_flags)) {
    unit_flags |= UnitFlags::kDynamicViewport;
  }

  if (CSSPrimitiveValue::HasStaticViewportUnits(length_type_flags)) {
    unit_flags |= UnitFlags::kStaticViewport;
  }

  if (length_type_flags.test(CSSPrimitiveValue::kUnitTypeContainerWidth) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeContainerHeight) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeContainerInlineSize) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeContainerBlockSize) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeContainerMin) ||
      length_type_flags.test(CSSPrimitiveValue::kUnitTypeContainerMax)) {
    unit_flags |= UnitFlags::kContainer;
  }

  return unit_flags;
}

String MediaQueryExpNode::Serialize() const {
  StringBuilder builder;
  SerializeTo(builder);
  return builder.ReleaseString();
}

const MediaQueryExpNode* MediaQueryExpNode::Not(
    const MediaQueryExpNode* operand) {
  if (!operand) {
    return nullptr;
  }
  return MakeGarbageCollected<MediaQueryNotExpNode>(operand);
}

const MediaQueryExpNode* MediaQueryExpNode::Nested(
    const MediaQueryExpNode* operand) {
  if (!operand) {
    return nullptr;
  }
  return MakeGarbageCollected<MediaQueryNestedExpNode>(operand);
}

const MediaQueryExpNode* MediaQueryExpNode::Function(
    const MediaQueryExpNode* operand,
    const AtomicString& name) {
  if (!operand) {
    return nullptr;
  }
  return MakeGarbageCollected<MediaQueryFunctionExpNode>(operand, name);
}

const MediaQueryExpNode* MediaQueryExpNode::And(
    const MediaQueryExpNode* left,
    const MediaQueryExpNode* right) {
  if (!left || !right) {
    return nullptr;
  }
  return MakeGarbageCollected<MediaQueryAndExpNode>(left, right);
}

const MediaQueryExpNode* MediaQueryExpNode::Or(const MediaQueryExpNode* left,
                                               const MediaQueryExpNode* right) {
  if (!left || !right) {
    return nullptr;
  }
  return MakeGarbageCollected<MediaQueryOrExpNode>(left, right);
}

bool MediaQueryFeatureExpNode::IsViewportDependent() const {
  return exp_.IsViewportDependent();
}

bool MediaQueryFeatureExpNode::IsDeviceDependent() const {
  return exp_.IsDeviceDependent();
}

unsigned MediaQueryFeatureExpNode::GetUnitFlags() const {
  return exp_.GetUnitFlags();
}

bool MediaQueryFeatureExpNode::IsWidthDependent() const {
  return exp_.IsWidthDependent();
}

bool MediaQueryFeatureExpNode::IsHeightDependent() const {
  return exp_.IsHeightDependent();
}

bool MediaQueryFeatureExpNode::IsInlineSizeDependent() const {
  return exp_.IsInlineSizeDependent();
}

bool MediaQueryFeatureExpNode::IsBlockSizeDependent() const {
  return exp_.IsBlockSizeDependent();
}

void MediaQueryFeatureExpNode::SerializeTo(StringBuilder& builder) const {
  builder.Append(exp_.Serialize());
}

void MediaQueryFeatureExpNode::CollectExpressions(
    HeapVector<MediaQueryExp>& result) const {
  result.push_back(exp_);
}

MediaQueryExpNode::FeatureFlags MediaQueryFeatureExpNode::CollectFeatureFlags()
    const {
  if (exp_.MediaFeature() == media_feature_names::kStuckMediaFeature) {
    return kFeatureSticky;
  } else if (exp_.MediaFeature() == media_feature_names::kSnappedMediaFeature) {
    return kFeatureSnap;
  } else if (exp_.MediaFeature() ==
             media_feature_names::kScrollableMediaFeature) {
    return kFeatureScrollable;
  } else if (exp_.IsInlineSizeDependent()) {
    return kFeatureInlineSize;
  } else if (exp_.IsBlockSizeDependent()) {
    return kFeatureBlockSize;
  } else {
    FeatureFlags flags = 0;
    if (exp_.IsWidthDependent()) {
      flags |= kFeatureWidth;
    }
    if (exp_.IsHeightDependent()) {
      flags |= kFeatureHeight;
    }
    return flags;
  }
}

void MediaQueryFeatureExpNode::Trace(Visitor* visitor) const {
  visitor->Trace(exp_);
  MediaQueryExpNode::Trace(visitor);
}

void MediaQueryUnaryExpNode::Trace(Visitor* visitor) const {
  visitor->Trace(operand_);
  MediaQueryExpNode::Trace(visitor);
}

void MediaQueryUnaryExpNode::CollectExpressions(
    HeapVector<MediaQueryExp>& result) const {
  operand_->CollectExpressions(result);
}

MediaQueryExpNode::FeatureFlags MediaQueryUnaryExpNode::CollectFeatureFlags()
    const {
  return operand_->CollectFeatureFlags();
}

void MediaQueryNestedExpNode::SerializeTo(StringBuilder& builder) const {
  builder.Append("(");
  Operand().SerializeTo(builder);
  builder.Append(")");
}

void MediaQueryFunctionExpNode::SerializeTo(StringBuilder& builder) const {
  builder.Append(name_);
  builder.Append("(");
  Operand().SerializeTo(builder);
  builder.Append(")");
}

MediaQueryExpNode::FeatureFlags MediaQueryFunctionExpNode::CollectFeatureFlags()
    const {
  FeatureFlags flags = MediaQueryUnaryExpNode::CollectFeatureFlags();
  if (name_ == AtomicString("style")) {
    flags |= kFeatureStyle;
  }
  return flags;
}

void MediaQueryNotExpNode::SerializeTo(StringBuilder& builder) const {
  builder.Append("not ");
  Operand().SerializeTo(builder);
}

void MediaQueryCompoundExpNode::Trace(Visitor* visitor) const {
  visitor->Trace(left_);
  visitor->Trace(right_);
  MediaQueryExpNode::Trace(visitor);
}

void MediaQueryCompoundExpNode::CollectExpressions(
    HeapVector<MediaQueryExp>& result) const {
  left_->CollectExpressions(result);
  right_->CollectExpressions(result);
}

MediaQueryExpNode::FeatureFlags MediaQueryCompoundExpNode::CollectFeatureFlags()
    const {
  return left_->CollectFeatureFlags() | right_->CollectFeatureFlags();
}

void MediaQueryAndExpNode::SerializeTo(StringBuilder& builder) const {
  Left().SerializeTo(builder);
  builder.Append(" and ");
  Right().SerializeTo(builder);
}

void MediaQueryOrExpNode::SerializeTo(StringBuilder& builder) const {
  Left().SerializeTo(builder);
  builder.Append(" or ");
  Right().SerializeTo(builder);
}

void MediaQueryUnknownExpNode::SerializeTo(StringBuilder& builder) const {
  builder.Append(string_);
}

void MediaQueryUnknownExpNode::CollectExpressions(
    HeapVector<MediaQueryExp>&) const {}

MediaQueryExpNode::FeatureFlags MediaQueryUnknownExpNode::CollectFeatureFlags()
    const {
  return kFeatureUnknown;
=======
  return output.ToString();
>>>>>>> chromium
}

}  // namespace blink
