/*
 * Copyright (C) 2011, 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
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

#ifdef UNSAFE_BUFFERS_BUILD
// TODO(crbug.com/390223051): Remove C-library calls to fix the errors.
#pragma allow_unsafe_libc_calls
#endif

#include "third_party/blink/renderer/core/css/css_math_expression_node.h"

#include "third_party/blink/renderer/core/css/css_numeric_literal_value.h"
#include "third_party/blink/renderer/core/css/css_primitive_value_mappings.h"
#include "third_party/blink/renderer/core/css/css_value_clamping_utils.h"
#include "third_party/blink/renderer/core/css/properties/css_parsing_utils.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/css/try_tactic_transform.h"
#include "third_party/blink/renderer/core/css_value_keywords.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/nth_index_cache.h"
#include "third_party/blink/renderer/core/frame/web_feature.h"
#include "third_party/blink/renderer/core/style/anchor_specifier_value.h"
=======
>>>>>>> chromium
#include "third_party/blink/renderer/platform/geometry/calculation_expression_node.h"
#include "third_party/blink/renderer/platform/wtf/math_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

enum ParseState { OK, TooDeep, NoMoreTokens };

namespace blink {

static CalculationCategory UnitCategory(CSSPrimitiveValue::UnitType type) {
  switch (type) {
    case CSSPrimitiveValue::UnitType::kNumber:
    case CSSPrimitiveValue::UnitType::kInteger:
      return kCalcNumber;
    case CSSPrimitiveValue::UnitType::kPercentage:
      return kCalcPercent;
    case CSSPrimitiveValue::UnitType::kEms:
    case CSSPrimitiveValue::UnitType::kExs:
    case CSSPrimitiveValue::UnitType::kPixels:
    case CSSPrimitiveValue::UnitType::kCentimeters:
    case CSSPrimitiveValue::UnitType::kMillimeters:
    case CSSPrimitiveValue::UnitType::kQuarterMillimeters:
    case CSSPrimitiveValue::UnitType::kInches:
    case CSSPrimitiveValue::UnitType::kPoints:
    case CSSPrimitiveValue::UnitType::kPicas:
    case CSSPrimitiveValue::UnitType::kUserUnits:
    case CSSPrimitiveValue::UnitType::kRems:
    case CSSPrimitiveValue::UnitType::kChs:
    case CSSPrimitiveValue::UnitType::kViewportWidth:
    case CSSPrimitiveValue::UnitType::kViewportHeight:
    case CSSPrimitiveValue::UnitType::kViewportMin:
    case CSSPrimitiveValue::UnitType::kViewportMax:
      return kCalcLength;
    case CSSPrimitiveValue::UnitType::kContainerWidth:
    case CSSPrimitiveValue::UnitType::kContainerHeight:
    case CSSPrimitiveValue::UnitType::kContainerInlineSize:
    case CSSPrimitiveValue::UnitType::kContainerBlockSize:
    case CSSPrimitiveValue::UnitType::kContainerMin:
    case CSSPrimitiveValue::UnitType::kContainerMax:
      return RuntimeEnabledFeatures::CSSContainerRelativeUnitsEnabled()
                 ? kCalcLength
                 : kCalcOther;
    case CSSPrimitiveValue::UnitType::kDegrees:
    case CSSPrimitiveValue::UnitType::kGradians:
    case CSSPrimitiveValue::UnitType::kRadians:
    case CSSPrimitiveValue::UnitType::kTurns:
      return kCalcAngle;
    case CSSPrimitiveValue::UnitType::kMilliseconds:
    case CSSPrimitiveValue::UnitType::kSeconds:
      return kCalcTime;
    case CSSPrimitiveValue::UnitType::kHertz:
    case CSSPrimitiveValue::UnitType::kKilohertz:
      return kCalcFrequency;
    default:
      return kCalcOther;
  }
}

static bool HasDoubleValue(CSSPrimitiveValue::UnitType type) {
  switch (type) {
    case CSSPrimitiveValue::UnitType::kNumber:
    case CSSPrimitiveValue::UnitType::kPercentage:
    case CSSPrimitiveValue::UnitType::kEms:
    case CSSPrimitiveValue::UnitType::kExs:
    case CSSPrimitiveValue::UnitType::kChs:
    case CSSPrimitiveValue::UnitType::kRems:
    case CSSPrimitiveValue::UnitType::kPixels:
    case CSSPrimitiveValue::UnitType::kCentimeters:
    case CSSPrimitiveValue::UnitType::kMillimeters:
    case CSSPrimitiveValue::UnitType::kQuarterMillimeters:
    case CSSPrimitiveValue::UnitType::kInches:
    case CSSPrimitiveValue::UnitType::kPoints:
    case CSSPrimitiveValue::UnitType::kPicas:
    case CSSPrimitiveValue::UnitType::kUserUnits:
    case CSSPrimitiveValue::UnitType::kDegrees:
    case CSSPrimitiveValue::UnitType::kRadians:
    case CSSPrimitiveValue::UnitType::kGradians:
    case CSSPrimitiveValue::UnitType::kTurns:
    case CSSPrimitiveValue::UnitType::kMilliseconds:
    case CSSPrimitiveValue::UnitType::kSeconds:
    case CSSPrimitiveValue::UnitType::kHertz:
    case CSSPrimitiveValue::UnitType::kKilohertz:
    case CSSPrimitiveValue::UnitType::kViewportWidth:
    case CSSPrimitiveValue::UnitType::kViewportHeight:
    case CSSPrimitiveValue::UnitType::kViewportMin:
    case CSSPrimitiveValue::UnitType::kViewportMax:
    case CSSPrimitiveValue::UnitType::kContainerWidth:
    case CSSPrimitiveValue::UnitType::kContainerHeight:
    case CSSPrimitiveValue::UnitType::kContainerInlineSize:
    case CSSPrimitiveValue::UnitType::kContainerBlockSize:
    case CSSPrimitiveValue::UnitType::kContainerMin:
    case CSSPrimitiveValue::UnitType::kContainerMax:
    case CSSPrimitiveValue::UnitType::kDotsPerPixel:
    case CSSPrimitiveValue::UnitType::kDotsPerInch:
    case CSSPrimitiveValue::UnitType::kDotsPerCentimeter:
    case CSSPrimitiveValue::UnitType::kFraction:
    case CSSPrimitiveValue::UnitType::kInteger:
      return true;
    default:
      return false;
  }
}

namespace {

const PixelsAndPercent CreateClampedSamePixelsAndPercent(float value) {
  return PixelsAndPercent(CSSValueClampingUtils::ClampLength(value),
                          CSSValueClampingUtils::ClampLength(value));
}

bool IsNaN(PixelsAndPercent value, bool allows_negative_percentage_reference) {
  if (std::isnan(value.pixels + value.percent) ||
      (allows_negative_percentage_reference && std::isinf(value.percent))) {
    return true;
  }
  return false;
}

absl::optional<PixelsAndPercent> EvaluateValueIfNaNorInfinity(
    scoped_refptr<const blink::CalculationExpressionNode> value,
    bool allows_negative_percentage_reference) {
  float evaluated_value = value->Evaluate(1);
  if (std::isnan(evaluated_value) || std::isinf(evaluated_value)) {
    return CreateClampedSamePixelsAndPercent(evaluated_value);
  }
  if (allows_negative_percentage_reference) {
    evaluated_value = value->Evaluate(-1);
    if (std::isnan(evaluated_value) || std::isinf(evaluated_value)) {
      return CreateClampedSamePixelsAndPercent(evaluated_value);
    }
  }
  return absl::nullopt;
}

}  // namespace

// ------ Start of CSSMathExpressionNumericLiteral member functions ------

// static
CSSMathExpressionNumericLiteral* CSSMathExpressionNumericLiteral::Create(
    const CSSNumericLiteralValue* value,
    bool is_integer) {
  return MakeGarbageCollected<CSSMathExpressionNumericLiteral>(value,
                                                               is_integer);
}

// static
CSSMathExpressionNumericLiteral* CSSMathExpressionNumericLiteral::Create(
    double value,
    CSSPrimitiveValue::UnitType type,
    bool is_integer) {
  if (!RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled() &&
      (std::isnan(value) || std::isinf(value)))
    return nullptr;
  return MakeGarbageCollected<CSSMathExpressionNumericLiteral>(
      CSSNumericLiteralValue::Create(value, type), is_integer);
}

CSSMathExpressionNumericLiteral::CSSMathExpressionNumericLiteral(
    const CSSNumericLiteralValue* value,
    bool is_integer)
    : CSSMathExpressionNode(UnitCategory(value->GetType()),
                            is_integer,
                            false /* has_comparisons*/),
      value_(value) {}

<<<<<<< HEAD
    value_ = value_->CreateCanonicalUnitValue();
  }
}

const CSSMathExpressionNode*
CSSMathExpressionNumericLiteral::ConvertLiteralsFromPercentageToNumber() const {
  if (category_ != kCalcPercent) {
    return this;
  }
  return CSSMathExpressionNumericLiteral::Create(
      value_->DoubleValue() / 100, CSSPrimitiveValue::UnitType::kNumber);
=======
bool CSSMathExpressionNumericLiteral::IsZero() const {
  return !value_->GetDoubleValue();
>>>>>>> chromium
}

String CSSMathExpressionNumericLiteral::CustomCSSText() const {
  return value_->CssText();
}

absl::optional<PixelsAndPercent>
CSSMathExpressionNumericLiteral::ToPixelsAndPercent(
    const CSSToLengthConversionData& conversion_data) const {
  PixelsAndPercent value(0, 0);
  switch (category_) {
    case kCalcLength:
      // When CSSCalcInfinityAndNaN is enabled, we allow infinity and NaN in
      // PixelsAndPercent. Therefore, we need to use a function that doesn't
      // internally clamp the result to the float range.
      if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled())
        value.pixels = value_->ComputeLengthPx(conversion_data);
      else
        value.pixels = value_->ComputeLength<float>(conversion_data);
      break;
    case kCalcPercent:
      DCHECK(value_->IsPercentage());
<<<<<<< HEAD
      return PixelsAndPercent(0.0f, value_->DoubleValue(),
                              /*has_explicit_pixels=*/false,
                              /*has_explicit_percent=*/true);
=======
      // When CSSCalcInfinityAndNaN is enabled, we allow infinity and NaN in
      // PixelsAndPercent. Therefore, we need to use a function that doesn't
      // internally clamp the result to the float range.
      if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled())
        value.percent = value_->GetDoubleValueWithoutClamping();
      else
        value.percent = value_->GetFloatValue();
      break;
>>>>>>> chromium
    case kCalcNumber:
      // TODO(alancutter): Stop treating numbers like pixels unconditionally
      // in calcs to be able to accomodate border-image-width
      // https://drafts.csswg.org/css-backgrounds-3/#the-border-image-width
<<<<<<< HEAD
      return PixelsAndPercent(
          ClampTo<float>(value_->ClampedDoubleValue()) * length_resolver.Zoom(),
          0.0f, /*has_explicit_pixels=*/true,
          /*has_explicit_percent=*/false);
    case kCalcAngle:
      // Treat angles as pixels to support calc() expressions on hue angles in
      // relative color syntax. This allows converting such expressions to
      // CalculationValues.
      return PixelsAndPercent(ClampTo<float>(value_->ClampedDoubleValue()),
                              0.0f,
                              /*has_explicit_pixels=*/true,
                              /*has_explicit_percent=*/false);
=======
      value.pixels = value_->GetFloatValue() * conversion_data.Zoom();
      break;
>>>>>>> chromium
    default:
      NOTREACHED();
  }
  return value;
}

scoped_refptr<const CalculationExpressionNode>
CSSMathExpressionNumericLiteral::ToCalculationExpression(
    const CSSToLengthConversionData& conversion_data) const {
  return base::MakeRefCounted<CalculationExpressionLeafNode>(
      *ToPixelsAndPercent(conversion_data));
}

double CSSMathExpressionNumericLiteral::DoubleValue() const {
  if (HasDoubleValue(ResolvedUnitType()))
    return value_->GetDoubleValueWithoutClamping();
  NOTREACHED();
  return 0;
}

absl::optional<double>
CSSMathExpressionNumericLiteral::ComputeValueInCanonicalUnit() const {
  switch (category_) {
    case kCalcNumber:
    case kCalcPercent:
      return value_->DoubleValue();
    case kCalcLength:
      if (CSSPrimitiveValue::IsRelativeUnit(value_->GetType()))
        return absl::nullopt;
      U_FALLTHROUGH;
    case kCalcAngle:
    case kCalcTime:
    case kCalcFrequency:
      return value_->DoubleValue() *
             CSSPrimitiveValue::ConversionToCanonicalUnitsScaleFactor(
                 value_->GetType());
    default:
      return absl::nullopt;
  }
}

double CSSMathExpressionNumericLiteral::ComputeLengthPx(
    const CSSToLengthConversionData& conversion_data) const {
  switch (category_) {
    case kCalcLength:
      // When CSSCalcInfinityAndNaN is enabled, we allow infinity and NaN in
      // PixelsAndPercent. Therefore, we need to use a function that doesn't
      // internally clamp the result to the float range.
      if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled())
        return value_->ComputeLengthPx(conversion_data);
      return value_->ComputeLength<double>(conversion_data);
    case kCalcNumber:
    case kCalcPercent:
    case kCalcAngle:
    case kCalcFrequency:
    case kCalcPercentLength:
    case kCalcTime:
    case kCalcOther:
      NOTREACHED();
      break;
  }
  NOTREACHED();
  return 0;
}

bool CSSMathExpressionNumericLiteral::AccumulateLengthArray(
    CSSLengthArray& length_array,
    double multiplier) const {
  DCHECK_NE(Category(), kCalcNumber);
  return value_->AccumulateLengthArray(length_array, multiplier);
}

void CSSMathExpressionNumericLiteral::AccumulateLengthUnitTypes(
    CSSPrimitiveValue::LengthTypeFlags& types) const {
  value_->AccumulateLengthUnitTypes(types);
}

bool CSSMathExpressionNumericLiteral::operator==(
    const CSSMathExpressionNode& other) const {
  if (!other.IsNumericLiteral())
    return false;

  return DataEquivalent(value_,
                        To<CSSMathExpressionNumericLiteral>(other).value_);
}

CSSPrimitiveValue::UnitType CSSMathExpressionNumericLiteral::ResolvedUnitType()
    const {
  return value_->GetType();
}

bool CSSMathExpressionNumericLiteral::IsComputationallyIndependent() const {
  return value_->IsComputationallyIndependent();
}

void CSSMathExpressionNumericLiteral::Trace(Visitor* visitor) const {
  visitor->Trace(value_);
  CSSMathExpressionNode::Trace(visitor);
}

#if DCHECK_IS_ON()
bool CSSMathExpressionNumericLiteral::InvolvesPercentageComparisons() const {
  return false;
}
#endif

// ------ End of CSSMathExpressionNumericLiteral member functions

static const CalculationCategory kAddSubtractResult[kCalcOther][kCalcOther] = {
    /* CalcNumber */ {kCalcNumber, kCalcOther, kCalcOther, kCalcOther,
                      kCalcOther, kCalcOther, kCalcOther},
    /* CalcLength */
    {kCalcOther, kCalcLength, kCalcPercentLength, kCalcPercentLength,
     kCalcOther, kCalcOther, kCalcOther},
    /* CalcPercent */
    {kCalcOther, kCalcPercentLength, kCalcPercent, kCalcPercentLength,
     kCalcOther, kCalcOther, kCalcOther},
    /* CalcPercentLength */
    {kCalcOther, kCalcPercentLength, kCalcPercentLength, kCalcPercentLength,
     kCalcOther, kCalcOther, kCalcOther},
    /* CalcAngle  */
    {kCalcOther, kCalcOther, kCalcOther, kCalcOther, kCalcAngle, kCalcOther,
     kCalcOther},
    /* CalcTime */
    {kCalcOther, kCalcOther, kCalcOther, kCalcOther, kCalcOther, kCalcTime,
     kCalcOther},
    /* CalcFrequency */
    {kCalcOther, kCalcOther, kCalcOther, kCalcOther, kCalcOther, kCalcOther,
     kCalcFrequency}};

static CalculationCategory DetermineCategory(
    const CSSMathExpressionNode& left_side,
    const CSSMathExpressionNode& right_side,
    CSSMathOperator op) {
  CalculationCategory left_category = left_side.Category();
  CalculationCategory right_category = right_side.Category();

  if (left_category == kCalcOther || right_category == kCalcOther)
    return kCalcOther;

  switch (op) {
    case CSSMathOperator::kAdd:
    case CSSMathOperator::kSubtract:
      return kAddSubtractResult[left_category][right_category];
    case CSSMathOperator::kMultiply:
      if (left_category != kCalcNumber && right_category != kCalcNumber)
        return kCalcOther;
      return left_category == kCalcNumber ? right_category : left_category;
    case CSSMathOperator::kDivide:
      if (right_category != kCalcNumber || right_side.IsZero())
        return kCalcOther;
      return left_category;
    default:
      break;
  }

  NOTREACHED();
  return kCalcOther;
}

static bool IsIntegerResult(const CSSMathExpressionNode* left_side,
                            const CSSMathExpressionNode* right_side,
                            CSSMathOperator op) {
  // Not testing for actual integer values.
  // Performs W3C spec's type checking for calc integers.
  // http://www.w3.org/TR/css3-values/#calc-type-checking
  return op != CSSMathOperator::kDivide && left_side->IsInteger() &&
         right_side->IsInteger();
}

// ------ Start of CSSMathExpressionBinaryOperation member functions ------

// static
CSSMathExpressionNode* CSSMathExpressionBinaryOperation::Create(
    const CSSMathExpressionNode* left_side,
    const CSSMathExpressionNode* right_side,
    CSSMathOperator op) {
  DCHECK_NE(left_side->Category(), kCalcOther);
  DCHECK_NE(right_side->Category(), kCalcOther);

  CalculationCategory new_category =
      DetermineCategory(*left_side, *right_side, op);
  if (new_category == kCalcOther)
    return nullptr;

  return MakeGarbageCollected<CSSMathExpressionBinaryOperation>(
      left_side, right_side, op, new_category);
}

// static
<<<<<<< HEAD
CSSMathExpressionNode* CSSMathExpressionOperation::CreateCalcSizeOperation(
    const CSSMathExpressionNode* left_side,
    const CSSMathExpressionNode* right_side) {
  DCHECK_NE(left_side->Category(), kCalcOther);
  DCHECK_NE(right_side->Category(), kCalcOther);

  const CSSMathOperator op = CSSMathOperator::kCalcSize;
  CalculationResultCategory new_category =
      DetermineCalcSizeCategory(*left_side, *right_side, op);
  if (new_category == kCalcOther) {
    return nullptr;
  }

  return MakeGarbageCollected<CSSMathExpressionOperation>(left_side, right_side,
                                                          op, new_category);
}

// static
CSSMathExpressionNode* CSSMathExpressionOperation::CreateComparisonFunction(
    Operands&& operands,
    CSSMathOperator op) {
  DCHECK(op == CSSMathOperator::kMin || op == CSSMathOperator::kMax ||
         op == CSSMathOperator::kClamp);

  CalculationResultCategory category = DetermineComparisonCategory(operands);
  if (category == kCalcOther) {
    return nullptr;
  }

  return MakeGarbageCollected<CSSMathExpressionOperation>(
      category, std::move(operands), op);
}

// static
CSSMathExpressionNode*
CSSMathExpressionOperation::CreateComparisonFunctionSimplified(
    Operands&& operands,
    CSSMathOperator op) {
  DCHECK(op == CSSMathOperator::kMin || op == CSSMathOperator::kMax ||
         op == CSSMathOperator::kClamp);

  CalculationResultCategory category = DetermineComparisonCategory(operands);
  if (category == kCalcOther) {
    return nullptr;
  }

  if (CanEagerlySimplify(operands)) {
    Vector<double> canonical_values;
    canonical_values.reserve(operands.size());
    for (const CSSMathExpressionNode* operand : operands) {
      std::optional<double> canonical_value =
          operand->ComputeValueInCanonicalUnit();

      DCHECK(canonical_value.has_value());

      canonical_values.push_back(canonical_value.value());
    }

    CSSPrimitiveValue::UnitType canonical_unit =
        CSSPrimitiveValue::CanonicalUnit(operands.front()->ResolvedUnitType());

    return CSSMathExpressionNumericLiteral::Create(
        EvaluateOperator(canonical_values, op), canonical_unit);
  }

  if (operands.size() == 1) {
    return operands.front()->Copy();
  }

  return MakeGarbageCollected<CSSMathExpressionOperation>(
      category, std::move(operands), op);
}

// Helper function for parsing number value
static double ValueAsNumber(const CSSMathExpressionNode* node, bool& error) {
  if (node->Category() == kCalcNumber) {
    return node->DoubleValue();
  }
  error = true;
  return 0;
}

static bool SupportedCategoryForAtan2(
    const CalculationResultCategory category) {
  switch (category) {
    case kCalcNumber:
    case kCalcLength:
    case kCalcPercent:
    case kCalcTime:
    case kCalcFrequency:
    case kCalcAngle:
      return true;
    default:
      return false;
  }
}

static bool IsRelativeLength(CSSPrimitiveValue::UnitType type) {
  return CSSPrimitiveValue::IsRelativeUnit(type) &&
         CSSPrimitiveValue::IsLength(type);
}

static double ResolveAtan2(const CSSMathExpressionNode* y_node,
                           const CSSMathExpressionNode* x_node,
                           bool& error) {
  const CalculationResultCategory category = y_node->Category();
  if (category != x_node->Category() || !SupportedCategoryForAtan2(category)) {
    error = true;
    return 0;
  }
  CSSPrimitiveValue::UnitType y_type = y_node->ResolvedUnitType();
  CSSPrimitiveValue::UnitType x_type = x_node->ResolvedUnitType();

  // TODO(crbug.com/1392594): We ignore parameters in complex relative units
  // (e.g., 1rem + 1px) until they can be supported.
  if (y_type == CSSPrimitiveValue::UnitType::kUnknown ||
      x_type == CSSPrimitiveValue::UnitType::kUnknown) {
    error = true;
    return 0;
  }

  if (IsRelativeLength(y_type) || IsRelativeLength(x_type)) {
    // TODO(crbug.com/1392594): Relative length units are currently hard
    // to resolve. We ignore the units for now, so that
    // we can at least support the case where both operands have the same unit.
    double y = y_node->DoubleValue();
    double x = x_node->DoubleValue();
    return std::atan2(y, x);
  }
  auto y = y_node->ComputeValueInCanonicalUnit();
  auto x = x_node->ComputeValueInCanonicalUnit();
  return std::atan2(y.value(), x.value());
}

// Helper function for parsing trigonometric functions' parameter
static double ValueAsDegrees(const CSSMathExpressionNode* node, bool& error) {
  if (node->Category() == kCalcAngle) {
    return node->ComputeValueInCanonicalUnit().value();
  }
  return Rad2deg(ValueAsNumber(node, error));
}

static bool CanonicalizeRoundArguments(
    CSSMathExpressionOperation::Operands& nodes) {
  if (nodes.size() == 2) {
    return true;
  }
  // If the type of A matches <number>, then B may be omitted, and defaults to
  // 1; omitting B is otherwise invalid.
  // (https://drafts.csswg.org/css-values-4/#round-func)
  if (nodes.size() == 1 &&
      nodes[0]->Category() == CalculationResultCategory::kCalcNumber) {
    // Add B=1 to get the function on canonical form.
    nodes.push_back(CSSMathExpressionNumericLiteral::Create(
        1, CSSPrimitiveValue::UnitType::kNumber));
    return true;
  }
  return false;
}

static bool ShouldSerializeRoundingStep(
    const CSSMathExpressionOperation::Operands& operands) {
  // Omit the step (B) operand to round(...) if the type of A is <number> and
  // the step is the literal 1.
  if (operands[0]->Category() != CalculationResultCategory::kCalcNumber) {
    return true;
  }
  auto* literal = DynamicTo<CSSMathExpressionNumericLiteral>(*operands[1]);
  if (!literal) {
    return true;
  }
  const CSSNumericLiteralValue& literal_value = literal->GetValue();
  if (!literal_value.IsNumber() || literal_value.DoubleValue() != 1) {
    return true;
  }
  return false;
}

CSSMathExpressionNode*
CSSMathExpressionOperation::CreateTrigonometricFunctionSimplified(
    Operands&& operands,
    CSSValueID function_id) {
  double value;
  auto unit_type = CSSPrimitiveValue::UnitType::kUnknown;
  bool error = false;
  switch (function_id) {
    case CSSValueID::kSin: {
      DCHECK_EQ(operands.size(), 1u);
      unit_type = CSSPrimitiveValue::UnitType::kNumber;
      value = gfx::SinCosDegrees(ValueAsDegrees(operands[0], error)).sin;
      break;
    }
    case CSSValueID::kCos: {
      DCHECK_EQ(operands.size(), 1u);
      unit_type = CSSPrimitiveValue::UnitType::kNumber;
      value = gfx::SinCosDegrees(ValueAsDegrees(operands[0], error)).cos;
      break;
    }
    case CSSValueID::kTan: {
      DCHECK_EQ(operands.size(), 1u);
      unit_type = CSSPrimitiveValue::UnitType::kNumber;
      value = TanDegrees(ValueAsDegrees(operands[0], error));
      break;
    }
    case CSSValueID::kAsin: {
      DCHECK_EQ(operands.size(), 1u);
      unit_type = CSSPrimitiveValue::UnitType::kDegrees;
      value = Rad2deg(std::asin(ValueAsNumber(operands[0], error)));
      DCHECK(value >= -90 && value <= 90 || std::isnan(value));
      break;
    }
    case CSSValueID::kAcos: {
      DCHECK_EQ(operands.size(), 1u);
      unit_type = CSSPrimitiveValue::UnitType::kDegrees;
      value = Rad2deg(std::acos(ValueAsNumber(operands[0], error)));
      DCHECK(value >= 0 && value <= 180 || std::isnan(value));
      break;
    }
    case CSSValueID::kAtan: {
      DCHECK_EQ(operands.size(), 1u);
      unit_type = CSSPrimitiveValue::UnitType::kDegrees;
      value = Rad2deg(std::atan(ValueAsNumber(operands[0], error)));
      DCHECK(value >= -90 && value <= 90 || std::isnan(value));
      break;
    }
    case CSSValueID::kAtan2: {
      DCHECK_EQ(operands.size(), 2u);
      unit_type = CSSPrimitiveValue::UnitType::kDegrees;
      value = Rad2deg(ResolveAtan2(operands[0], operands[1], error));
      DCHECK(value >= -180 && value <= 180 || std::isnan(value));
      break;
    }
    default:
      return nullptr;
  }

  if (error) {
    return nullptr;
  }

  DCHECK_NE(unit_type, CSSPrimitiveValue::UnitType::kUnknown);
  return CSSMathExpressionNumericLiteral::Create(value, unit_type);
}

CSSMathExpressionNode* CSSMathExpressionOperation::CreateSteppedValueFunction(
    Operands&& operands,
    CSSMathOperator op) {
  if (!RuntimeEnabledFeatures::CSSSteppedValueFunctionsEnabled()) {
    return nullptr;
  }
  DCHECK_EQ(operands.size(), 2u);
  if (operands[0]->Category() == kCalcOther ||
      operands[1]->Category() == kCalcOther) {
    return nullptr;
  }
  CalculationResultCategory category =
      kAddSubtractResult[operands[0]->Category()][operands[1]->Category()];
  if (category == kCalcOther) {
    return nullptr;
  }
  if (CanEagerlySimplify(operands)) {
    std::optional<double> a = operands[0]->ComputeValueInCanonicalUnit();
    std::optional<double> b = operands[1]->ComputeValueInCanonicalUnit();
    DCHECK(a.has_value());
    DCHECK(b.has_value());
    double value = EvaluateSteppedValueFunction(op, a.value(), b.value());
    return CSSMathExpressionNumericLiteral::Create(
        value,
        CSSPrimitiveValue::CanonicalUnit(operands.front()->ResolvedUnitType()));
  }
  return MakeGarbageCollected<CSSMathExpressionOperation>(
      category, std::move(operands), op);
}

// static
CSSMathExpressionNode* CSSMathExpressionOperation::CreateExponentialFunction(
    Operands&& operands,
    CSSValueID function_id) {
  if (!RuntimeEnabledFeatures::CSSExponentialFunctionsEnabled()) {
    return nullptr;
  }

  double value = 0;
  bool error = false;
  auto unit_type = CSSPrimitiveValue::UnitType::kNumber;
  switch (function_id) {
    case CSSValueID::kPow: {
      DCHECK_EQ(operands.size(), 2u);
      double a = ValueAsNumber(operands[0], error);
      double b = ValueAsNumber(operands[1], error);
      value = std::pow(a, b);
      break;
    }
    case CSSValueID::kSqrt: {
      DCHECK_EQ(operands.size(), 1u);
      double a = ValueAsNumber(operands[0], error);
      value = std::sqrt(a);
      break;
    }
    case CSSValueID::kHypot: {
      DCHECK_GE(operands.size(), 1u);
      CalculationResultCategory category =
          DetermineComparisonCategory(operands);
      if (category == kCalcOther) {
        return nullptr;
      }
      if (CanEagerlySimplify(operands)) {
        for (const CSSMathExpressionNode* operand : operands) {
          std::optional<double> a = operand->ComputeValueInCanonicalUnit();
          DCHECK(a.has_value());
          value = std::hypot(value, a.value());
        }
        unit_type = CSSPrimitiveValue::CanonicalUnit(
            operands.front()->ResolvedUnitType());
      } else {
        return MakeGarbageCollected<CSSMathExpressionOperation>(
            category, std::move(operands), CSSMathOperator::kHypot);
      }
      break;
    }
    case CSSValueID::kLog: {
      DCHECK_GE(operands.size(), 1u);
      DCHECK_LE(operands.size(), 2u);
      double a = ValueAsNumber(operands[0], error);
      if (operands.size() == 2) {
        double b = ValueAsNumber(operands[1], error);
        value = std::log2(a) / std::log2(b);
      } else {
        value = std::log(a);
      }
      break;
    }
    case CSSValueID::kExp: {
      DCHECK_EQ(operands.size(), 1u);
      double a = ValueAsNumber(operands[0], error);
      value = std::exp(a);
      break;
    }
    default:
      return nullptr;
  }
  if (error) {
    return nullptr;
  }

  DCHECK_NE(unit_type, CSSPrimitiveValue::UnitType::kUnknown);
  return CSSMathExpressionNumericLiteral::Create(value, unit_type);
}

CSSMathExpressionNode* CSSMathExpressionOperation::CreateSignRelatedFunction(
    Operands&& operands,
    CSSValueID function_id) {
  if (!RuntimeEnabledFeatures::CSSSignRelatedFunctionsEnabled()) {
    return nullptr;
  }

  const CSSMathExpressionNode* operand = operands.front();

  if (operand->Category() == kCalcIntrinsicSize) {
    return nullptr;
  }

  switch (function_id) {
    case CSSValueID::kAbs: {
      if (CanEagerlySimplify(operand)) {
        const std::optional<double> opt =
            operand->ComputeValueInCanonicalUnit();
        DCHECK(opt.has_value());
        return CSSMathExpressionNumericLiteral::Create(
            std::abs(opt.value()), operand->ResolvedUnitType());
      }
      return MakeGarbageCollected<CSSMathExpressionOperation>(
          operand->Category(), std::move(operands), CSSMathOperator::kAbs);
    }
    case CSSValueID::kSign: {
      if (CanEagerlySimplify(operand)) {
        const std::optional<double> opt =
            operand->ComputeValueInCanonicalUnit();
        DCHECK(opt.has_value());
        const double value = opt.value();
        const double signum =
            (value == 0 || std::isnan(value)) ? value : ((value > 0) ? 1 : -1);
        return CSSMathExpressionNumericLiteral::Create(
            signum, CSSPrimitiveValue::UnitType::kNumber);
      }
      return MakeGarbageCollected<CSSMathExpressionOperation>(
          kCalcNumber, std::move(operands), CSSMathOperator::kSign);
    }
    default:
      NOTREACHED();
  }
}

const CSSMathExpressionNode*
CSSMathExpressionOperation::ConvertLiteralsFromPercentageToNumber() const {
  Operands ops;
  ops.reserve(operands_.size());
  for (const CSSMathExpressionNode* op : operands_) {
    ops.push_back(op->ConvertLiteralsFromPercentageToNumber());
  }
  CalculationResultCategory category =
      category_ == kCalcPercent ? kCalcNumber : category_;
  return MakeGarbageCollected<CSSMathExpressionOperation>(
      category, std::move(ops), operator_);
}

namespace {

inline const CSSMathExpressionOperation* DynamicToCalcSize(
    const CSSMathExpressionNode* node) {
  const CSSMathExpressionOperation* operation =
      DynamicTo<CSSMathExpressionOperation>(node);
  if (!operation || !operation->IsCalcSize()) {
    return nullptr;
  }
  return operation;
}

inline bool CanArithmeticOperationBeSimplified(
    const CSSMathExpressionNode* left_side,
    const CSSMathExpressionNode* right_side) {
  return left_side->IsNumericLiteral() && right_side->IsNumericLiteral();
}

}  // namespace

// static
CSSMathExpressionNode*
CSSMathExpressionOperation::CreateArithmeticOperationSimplified(
=======
CSSMathExpressionNode* CSSMathExpressionBinaryOperation::CreateSimplified(
>>>>>>> chromium
    const CSSMathExpressionNode* left_side,
    const CSSMathExpressionNode* right_side,
    CSSMathOperator op) {
  if (left_side->IsMathFunction() || right_side->IsMathFunction())
    return Create(left_side, right_side, op);

  CalculationCategory left_category = left_side->Category();
  CalculationCategory right_category = right_side->Category();
  DCHECK_NE(left_category, kCalcOther);
  DCHECK_NE(right_category, kCalcOther);

  bool is_integer = IsIntegerResult(left_side, right_side, op);

  // Simplify numbers.
  if (left_category == kCalcNumber && right_category == kCalcNumber) {
    return CSSMathExpressionNumericLiteral::Create(
        EvaluateOperator(left_side->DoubleValue(), right_side->DoubleValue(),
                         op),
        CSSPrimitiveValue::UnitType::kNumber, is_integer);
  }

  // Simplify addition and subtraction between same types.
  if (op == CSSMathOperator::kAdd || op == CSSMathOperator::kSubtract) {
    if (left_category == right_side->Category()) {
      CSSPrimitiveValue::UnitType left_type = left_side->ResolvedUnitType();
      if (HasDoubleValue(left_type)) {
        CSSPrimitiveValue::UnitType right_type = right_side->ResolvedUnitType();
        if (left_type == right_type) {
          return CSSMathExpressionNumericLiteral::Create(
              EvaluateOperator(left_side->DoubleValue(),
                               right_side->DoubleValue(), op),
              left_type, is_integer);
        }
        CSSPrimitiveValue::UnitCategory left_unit_category =
            CSSPrimitiveValue::UnitTypeToUnitCategory(left_type);
        if (left_unit_category != CSSPrimitiveValue::kUOther &&
            left_unit_category ==
                CSSPrimitiveValue::UnitTypeToUnitCategory(right_type)) {
          CSSPrimitiveValue::UnitType canonical_type =
              CSSPrimitiveValue::CanonicalUnitTypeForCategory(
                  left_unit_category);
          if (canonical_type != CSSPrimitiveValue::UnitType::kUnknown) {
            double left_value = clampTo<double>(
                left_side->DoubleValue() *
                CSSPrimitiveValue::ConversionToCanonicalUnitsScaleFactor(
                    left_type));
            double right_value = clampTo<double>(
                right_side->DoubleValue() *
                CSSPrimitiveValue::ConversionToCanonicalUnitsScaleFactor(
                    right_type));
            return CSSMathExpressionNumericLiteral::Create(
                EvaluateOperator(left_value, right_value, op), canonical_type,
                is_integer);
          }
        }
      }
    }
  } else {
    // Simplify multiplying or dividing by a number for simplifiable types.
    DCHECK(op == CSSMathOperator::kMultiply || op == CSSMathOperator::kDivide);
    const CSSMathExpressionNode* number_side =
        GetNumberSide(left_side, right_side);
    if (!number_side)
      return Create(left_side, right_side, op);
    if (number_side == left_side && op == CSSMathOperator::kDivide)
      return nullptr;
    const CSSMathExpressionNode* other_side =
        left_side == number_side ? right_side : left_side;

    double number = number_side->DoubleValue();

    if (!RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled()) {
      if (std::isnan(number) || std::isinf(number))
        return nullptr;
      if (op == CSSMathOperator::kDivide && !number)
        return nullptr;
    }

    CSSPrimitiveValue::UnitType other_type = other_side->ResolvedUnitType();
    if (HasDoubleValue(other_type)) {
      return CSSMathExpressionNumericLiteral::Create(
          EvaluateOperator(other_side->DoubleValue(), number, op), other_type,
          is_integer);
    }
  }

  return Create(left_side, right_side, op);
}

<<<<<<< HEAD
namespace {

std::tuple<const CSSMathExpressionNode*, wtf_size_t> SubstituteForSizeKeyword(
    const CSSMathExpressionNode* source,
    const CSSMathExpressionNode* size_substitution,
    wtf_size_t count_in_substitution) {
  CHECK_GT(count_in_substitution, 0u);
  if (const auto* operation = DynamicTo<CSSMathExpressionOperation>(source)) {
    using Operands = CSSMathExpressionOperation::Operands;
    const Operands& source_operands = operation->GetOperands();
    Operands dest_operands;
    dest_operands.reserve(source_operands.size());
    wtf_size_t total_substitution_count = 0;
    for (const CSSMathExpressionNode* source_op : source_operands) {
      const CSSMathExpressionNode* dest_op;
      wtf_size_t substitution_count;
      std::tie(dest_op, substitution_count) = SubstituteForSizeKeyword(
          source_op, size_substitution, count_in_substitution);
      CHECK_EQ(dest_op == source_op, substitution_count == 0);
      total_substitution_count += substitution_count;
      if (!dest_op || total_substitution_count > (1u << 16)) {
        // hit the size limit
        return std::make_tuple(nullptr, total_substitution_count);
      }
      dest_operands.push_back(dest_op);
    }

    if (total_substitution_count == 0) {
      // return the original rather than making a new one
      return std::make_tuple(source, 0);
    }

    return std::make_tuple(MakeGarbageCollected<CSSMathExpressionOperation>(
                               operation->Category(), std::move(dest_operands),
                               operation->OperatorType()),
                           total_substitution_count);
  }

  auto* literal = DynamicTo<CSSMathExpressionKeywordLiteral>(source);
  if (literal &&
      literal->GetContext() ==
          CSSMathExpressionKeywordLiteral::Context::kCalcSize &&
      literal->GetValue() == CSSValueID::kSize) {
    return std::make_tuple(size_substitution, count_in_substitution);
  }
  return std::make_tuple(source, 0);
}

// https://drafts.csswg.org/css-values-5/#de-percentify-a-calc-size-calculation
const CSSMathExpressionNode* SubstituteForPercentages(
    const CSSMathExpressionNode* source) {
  if (const auto* operation = DynamicTo<CSSMathExpressionOperation>(source)) {
    using Operands = CSSMathExpressionOperation::Operands;
    const Operands& source_operands = operation->GetOperands();
    Operands dest_operands;
    dest_operands.reserve(source_operands.size());
    for (const CSSMathExpressionNode* source_op : source_operands) {
      const CSSMathExpressionNode* dest_op =
          SubstituteForPercentages(source_op);
      dest_operands.push_back(dest_op);
    }

    return MakeGarbageCollected<CSSMathExpressionOperation>(
        operation->Category(), std::move(dest_operands),
        operation->OperatorType());
  }

  if (const auto* numeric_literal =
          DynamicTo<CSSMathExpressionNumericLiteral>(source)) {
    const CSSNumericLiteralValue& value = numeric_literal->GetValue();
    if (value.IsPercentage()) {
      return CSSMathExpressionOperation::CreateArithmeticOperation(
          CSSMathExpressionKeywordLiteral::Create(
              CSSValueID::kSize,
              CSSMathExpressionKeywordLiteral::Context::kCalcSize),
          CSSMathExpressionNumericLiteral::Create(
              value.DoubleValue() / 100.0,
              CSSPrimitiveValue::UnitType::kNumber),
          CSSMathOperator::kMultiply);
    }
  }
  return source;
}

bool BasisIsCanonical(const CSSMathExpressionNode* basis) {
  // A basis is canonical if it is a sizing keyword, 'any', or '100%'.
  if (const auto* numeric_literal =
          DynamicTo<CSSMathExpressionNumericLiteral>(basis)) {
    const CSSNumericLiteralValue& value = numeric_literal->GetValue();
    return value.IsPercentage() && value.GetValueIfKnown() == 100.0;
  }

  if (const auto* keyword_literal =
          DynamicTo<CSSMathExpressionKeywordLiteral>(basis)) {
    return keyword_literal->GetContext() ==
           CSSMathExpressionKeywordLiteral::Context::kCalcSize;
  }

  return false;
}

// Do substitution in order to produce a calc-size() whose basis is not
// another calc-size() and is not in non-canonical form.
const CSSMathExpressionOperation* MakeBasisCanonical(
    const CSSMathExpressionOperation* calc_size_input) {
  DCHECK(calc_size_input->IsCalcSize());
  HeapVector<Member<const CSSMathExpressionNode>, 4> calculation_stack;
  const CSSMathExpressionNode* final_basis = nullptr;
  const CSSMathExpressionNode* current_result = nullptr;

  wtf_size_t substitution_count = 1;
  const CSSMathExpressionOperation* current_calc_size = calc_size_input;
  while (true) {
    // If the basis is a calc-size(), push the calculation on the stack, and
    // enter this loop again with its basis.
    const CSSMathExpressionNode* basis = current_calc_size->GetOperands()[0];
    const CSSMathExpressionNode* calculation =
        current_calc_size->GetOperands()[1];
    if (const CSSMathExpressionOperation* basis_calc_size =
            DynamicToCalcSize(basis)) {
      calculation_stack.push_back(calculation);
      current_calc_size = basis_calc_size;
      continue;
    }

    // If the basis is canonical, use it.
    if (BasisIsCanonical(basis)) {
      if (calculation_stack.empty()) {
        // No substitution is needed; return the original.
        return calc_size_input;
      }

      current_result = calculation;
      final_basis = basis;
      break;
    }

    // Otherwise, we have a <calc-sum>, and our canonical basis should be
    // '100%' if we have a percentage and 'any' if we don't.  The percentage
    // case also requires that we substitute (size * (P/100)) for P% in the
    // basis.
    if (basis->HasPercentage()) {
      basis = SubstituteForPercentages(basis);
      final_basis = CSSMathExpressionNumericLiteral::Create(
          100.0, CSSPrimitiveValue::UnitType::kPercentage);
    } else {
      final_basis = CSSMathExpressionKeywordLiteral::Create(
          CSSValueID::kAny,
          CSSMathExpressionKeywordLiteral::Context::kCalcSize);
    }
    CHECK_EQ(substitution_count, 1u);
    std::tie(current_result, substitution_count) =
        SubstituteForSizeKeyword(calculation, basis, 1u);
    break;
  }

  while (!calculation_stack.empty()) {
    std::tie(current_result, substitution_count) =
        SubstituteForSizeKeyword(calculation_stack.back(), current_result,
                                 std::max(substitution_count, 1u));
    if (!current_result) {
      // too much expansion
      return nullptr;
    }
    calculation_stack.pop_back();
  }

  return To<CSSMathExpressionOperation>(
      CSSMathExpressionOperation::CreateCalcSizeOperation(final_basis,
                                                          current_result));
}

}  // namespace

// static
CSSMathExpressionNode*
CSSMathExpressionOperation::CreateArithmeticOperationAndSimplifyCalcSize(
    const CSSMathExpressionNode* left_side,
    const CSSMathExpressionNode* right_side,
    CSSMathOperator op) {
  DCHECK(op == CSSMathOperator::kAdd || op == CSSMathOperator::kSubtract ||
         op == CSSMathOperator::kMultiply || op == CSSMathOperator::kDivide);

  // Merge calc-size() expressions to keep calc-size() always at the top level.
  const CSSMathExpressionOperation* left_calc_size =
      DynamicToCalcSize(left_side);
  const CSSMathExpressionOperation* right_calc_size =
      DynamicToCalcSize(right_side);
  if (left_calc_size) {
    if (right_calc_size) {
      if (op != CSSMathOperator::kAdd && op != CSSMathOperator::kSubtract) {
        return nullptr;
      }
      // In theory we could check for basis equality or for one basis being
      // 'any' before we canonicalize to make some cases faster (and then
      // check again after).  However, the spec doesn't have this
      // optimization, and it is observable.

      // If either value has a non-canonical basis, substitute to produce a
      // canonical basis and try again recursively (with only one level of
      // recursion possible).
      //
      // We need to interpolate between the values *following* substitution of
      // the basis in the calculation, because if we interpolate the two
      // separately we are likely to get nonlinear interpolation behavior
      // (since we would be interpolating two different things linearly and
      // then multiplying them together).
      if (!BasisIsCanonical(left_calc_size->GetOperands()[0])) {
        left_calc_size = MakeBasisCanonical(left_calc_size);
        if (!left_calc_size) {
          return nullptr;  // hit the expansion limit
        }
      }
      if (!BasisIsCanonical(right_calc_size->GetOperands()[0])) {
        right_calc_size = MakeBasisCanonical(right_calc_size);
        if (!right_calc_size) {
          return nullptr;  // hit the expansion limit
        }
      }

      const CSSMathExpressionNode* left_basis =
          left_calc_size->GetOperands()[0];
      const CSSMathExpressionNode* right_basis =
          right_calc_size->GetOperands()[0];

      CHECK(BasisIsCanonical(left_basis));
      CHECK(BasisIsCanonical(right_basis));

      const CSSMathExpressionNode* final_basis = nullptr;
      // If the bases are equal, or one of them is the
      // any keyword, then we can interpolate only the calculations.
      auto is_any_keyword = [](const CSSMathExpressionNode* node) -> bool {
        const auto* literal = DynamicTo<CSSMathExpressionKeywordLiteral>(node);
        return literal && literal->GetValue() == CSSValueID::kAny &&
               literal->GetContext() ==
                   CSSMathExpressionKeywordLiteral::Context::kCalcSize;
      };

      if (*left_basis == *right_basis) {
        final_basis = left_basis;
      } else if (is_any_keyword(left_basis)) {
        final_basis = right_basis;
      } else if (is_any_keyword(right_basis)) {
        final_basis = left_basis;
      }
      if (!final_basis) {
        return nullptr;
      }
      const CSSMathExpressionNode* left_calculation =
          left_calc_size->GetOperands()[1];
      const CSSMathExpressionNode* right_calculation =
          right_calc_size->GetOperands()[1];
      return CreateCalcSizeOperation(
          final_basis, CreateArithmeticOperationSimplified(
                           left_calculation, right_calculation, op));
    } else {
      const CSSMathExpressionNode* left_basis =
          left_calc_size->GetOperands()[0];
      const CSSMathExpressionNode* left_calculation =
          left_calc_size->GetOperands()[1];
      return CreateCalcSizeOperation(
          left_basis, CreateArithmeticOperationSimplified(left_calculation,
                                                          right_side, op));
    }
  } else if (right_calc_size) {
    const CSSMathExpressionNode* right_basis =
        right_calc_size->GetOperands()[0];
    const CSSMathExpressionNode* right_calculation =
        right_calc_size->GetOperands()[1];
    return CreateCalcSizeOperation(
        right_basis,
        CreateArithmeticOperationSimplified(left_side, right_calculation, op));
  }

  return CreateArithmeticOperationSimplified(left_side, right_side, op);
}

CSSMathExpressionOperation::CSSMathExpressionOperation(
=======
CSSMathExpressionBinaryOperation::CSSMathExpressionBinaryOperation(
>>>>>>> chromium
    const CSSMathExpressionNode* left_side,
    const CSSMathExpressionNode* right_side,
    CSSMathOperator op,
    CalculationCategory category)
    : CSSMathExpressionNode(
          category,
          IsIntegerResult(left_side, right_side, op),
          left_side->HasComparisons() || right_side->HasComparisons()),
      left_side_(left_side),
      right_side_(right_side),
      operator_(op) {}

bool CSSMathExpressionBinaryOperation::IsZero() const {
  return !DoubleValue();
}

<<<<<<< HEAD
bool CSSMathExpressionOperation::InvolvesLayout() const {
  if (Category() == kCalcPercent || Category() == kCalcLengthFunction) {
    return true;
  }
  for (const CSSMathExpressionNode* operand : operands_) {
    if (operand->InvolvesLayout()) {
      return true;
    }
  }
  return false;
}

static bool AnyOperandHasComparisons(
    CSSMathExpressionOperation::Operands& operands) {
  for (const CSSMathExpressionNode* operand : operands) {
    if (operand->HasComparisons()) {
      return true;
    }
  }
  return false;
}

static bool AnyOperandHasAnchorFunctions(
    CSSMathExpressionOperation::Operands& operands) {
  for (const CSSMathExpressionNode* operand : operands) {
    if (operand->HasAnchorFunctions()) {
      return true;
    }
  }
  return false;
}

static bool AnyOperandNeedsTreeScopePopulation(
    CSSMathExpressionOperation::Operands& operands) {
  for (const CSSMathExpressionNode* operand : operands) {
    if (!operand->IsScopedValue()) {
      return true;
    }
  }
  return false;
}

CSSMathExpressionOperation::CSSMathExpressionOperation(
    CalculationResultCategory category,
    Operands&& operands,
    CSSMathOperator op)
    : CSSMathExpressionNode(
          category,
          IsComparison(op) || AnyOperandHasComparisons(operands),
          AnyOperandHasAnchorFunctions(operands),
          AnyOperandNeedsTreeScopePopulation(operands)),
      operands_(std::move(operands)),
      operator_(op) {}

CSSMathExpressionOperation::CSSMathExpressionOperation(
    CalculationResultCategory category,
    CSSMathOperator op)
    : CSSMathExpressionNode(category,
                            IsComparison(op),
                            false /*has_anchor_functions*/,
                            false),
      operator_(op) {}

std::optional<PixelsAndPercent> CSSMathExpressionOperation::ToPixelsAndPercent(
    const CSSLengthResolver& length_resolver) const {
  std::optional<PixelsAndPercent> result;
=======
absl::optional<PixelsAndPercent>
CSSMathExpressionBinaryOperation::ToPixelsAndPercent(
    const CSSToLengthConversionData& conversion_data) const {
  absl::optional<PixelsAndPercent> result;
>>>>>>> chromium
  switch (operator_) {
    case CSSMathOperator::kAdd:
    case CSSMathOperator::kSubtract: {
      result = left_side_->ToPixelsAndPercent(conversion_data);
      if (!result)
        return absl::nullopt;

      absl::optional<PixelsAndPercent> other_side =
          right_side_->ToPixelsAndPercent(conversion_data);
      if (!other_side)
        return absl::nullopt;
      if (operator_ == CSSMathOperator::kAdd) {
        result->pixels += other_side->pixels;
        result->percent += other_side->percent;
      } else {
        result->pixels -= other_side->pixels;
        result->percent -= other_side->percent;
      }
      break;
    }
    case CSSMathOperator::kMultiply:
    case CSSMathOperator::kDivide: {
      const CSSMathExpressionNode* number_side =
          GetNumberSide(left_side_, right_side_);
      const CSSMathExpressionNode* other_side =
          left_side_ == number_side ? right_side_ : left_side_;
      result = other_side->ToPixelsAndPercent(conversion_data);
      if (!result)
        return absl::nullopt;
      float number = number_side->DoubleValue();
      if (operator_ == CSSMathOperator::kDivide)
        number = 1.0 / number;
      result->pixels *= number;
      result->percent *= number;
      break;
    }
    default:
      NOTREACHED();
  }
  return result;
}

scoped_refptr<const CalculationExpressionNode>
CSSMathExpressionBinaryOperation::ToCalculationExpression(
    const CSSToLengthConversionData& conversion_data) const {
  switch (operator_) {
    case CSSMathOperator::kAdd:
      return CalculationExpressionAdditiveNode::CreateSimplified(
          left_side_->ToCalculationExpression(conversion_data),
          right_side_->ToCalculationExpression(conversion_data),
          CalculationExpressionAdditiveNode::Type::kAdd);
    case CSSMathOperator::kSubtract:
      return CalculationExpressionAdditiveNode::CreateSimplified(
          left_side_->ToCalculationExpression(conversion_data),
          right_side_->ToCalculationExpression(conversion_data),
          CalculationExpressionAdditiveNode::Type::kSubtract);
    case CSSMathOperator::kMultiply:
      DCHECK_NE((left_side_->Category() == kCalcNumber),
                (right_side_->Category() == kCalcNumber));
      if (left_side_->Category() == kCalcNumber) {
        return CalculationExpressionMultiplicationNode::CreateSimplified(
            right_side_->ToCalculationExpression(conversion_data),
            left_side_->DoubleValue());
      }
      return CalculationExpressionMultiplicationNode::CreateSimplified(
          left_side_->ToCalculationExpression(conversion_data),
          right_side_->DoubleValue());
    case CSSMathOperator::kDivide:
      DCHECK_EQ(right_side_->Category(), kCalcNumber);
      return CalculationExpressionMultiplicationNode::CreateSimplified(
          left_side_->ToCalculationExpression(conversion_data),
          1.0 / right_side_->DoubleValue());
    default:
      NOTREACHED();
      return nullptr;
  }
}

double CSSMathExpressionBinaryOperation::DoubleValue() const {
  DCHECK(HasDoubleValue(ResolvedUnitType())) << CustomCSSText();
  return Evaluate(left_side_->DoubleValue(), right_side_->DoubleValue());
}

static bool HasCanonicalUnit(CalculationCategory category) {
  return category == kCalcNumber || category == kCalcLength ||
         category == kCalcPercent || category == kCalcAngle ||
         category == kCalcTime || category == kCalcFrequency;
}

absl::optional<double>
CSSMathExpressionBinaryOperation::ComputeValueInCanonicalUnit() const {
  if (!HasCanonicalUnit(category_))
    return absl::nullopt;

  absl::optional<double> left_value = left_side_->ComputeValueInCanonicalUnit();
  if (!left_value)
    return absl::nullopt;

  absl::optional<double> right_value =
      right_side_->ComputeValueInCanonicalUnit();
  if (!right_value)
    return absl::nullopt;

  return Evaluate(*left_value, *right_value);
}

double CSSMathExpressionBinaryOperation::ComputeLengthPx(
    const CSSToLengthConversionData& conversion_data) const {
  DCHECK_EQ(kCalcLength, Category());
  double left_value;
  if (left_side_->Category() == kCalcLength) {
    left_value = left_side_->ComputeLengthPx(conversion_data);
  } else {
    DCHECK_EQ(kCalcNumber, left_side_->Category());
    left_value = left_side_->DoubleValue();
  }
  double right_value;
  if (right_side_->Category() == kCalcLength) {
    right_value = right_side_->ComputeLengthPx(conversion_data);
  } else {
    DCHECK_EQ(kCalcNumber, right_side_->Category());
    right_value = right_side_->DoubleValue();
  }
  return Evaluate(left_value, right_value);
}

bool CSSMathExpressionBinaryOperation::AccumulateLengthArray(
    CSSLengthArray& length_array,
    double multiplier) const {
  switch (operator_) {
    case CSSMathOperator::kAdd:
      if (!left_side_->AccumulateLengthArray(length_array, multiplier))
        return false;
      if (!right_side_->AccumulateLengthArray(length_array, multiplier))
        return false;
      return true;
    case CSSMathOperator::kSubtract:
      if (!left_side_->AccumulateLengthArray(length_array, multiplier))
        return false;
      if (!right_side_->AccumulateLengthArray(length_array, -multiplier))
        return false;
      return true;
    case CSSMathOperator::kMultiply:
      DCHECK_NE((left_side_->Category() == kCalcNumber),
                (right_side_->Category() == kCalcNumber));
      if (left_side_->Category() == kCalcNumber) {
        return right_side_->AccumulateLengthArray(
            length_array, multiplier * left_side_->DoubleValue());
      } else {
        return left_side_->AccumulateLengthArray(
            length_array, multiplier * right_side_->DoubleValue());
      }
    case CSSMathOperator::kDivide:
      DCHECK_EQ(right_side_->Category(), kCalcNumber);
      return left_side_->AccumulateLengthArray(
          length_array, multiplier / right_side_->DoubleValue());
    default:
      NOTREACHED();
      return false;
  }
}

void CSSMathExpressionBinaryOperation::AccumulateLengthUnitTypes(
    CSSPrimitiveValue::LengthTypeFlags& types) const {
  left_side_->AccumulateLengthUnitTypes(types);
  right_side_->AccumulateLengthUnitTypes(types);
}

bool CSSMathExpressionBinaryOperation::IsComputationallyIndependent() const {
  if (Category() != kCalcLength && Category() != kCalcPercentLength)
    return true;
  return left_side_->IsComputationallyIndependent() &&
         right_side_->IsComputationallyIndependent();
}

String CSSMathExpressionBinaryOperation::CustomCSSText() const {
  StringBuilder result;

  const bool left_side_needs_parentheses =
      left_side_->IsBinaryOperation() && operator_ != CSSMathOperator::kAdd;
  if (left_side_needs_parentheses)
    result.Append('(');
  result.Append(left_side_->CustomCSSText());
  if (left_side_needs_parentheses)
    result.Append(')');

  result.Append(' ');
  result.Append(ToString(operator_));
  result.Append(' ');

  const bool right_side_needs_parentheses =
      right_side_->IsBinaryOperation() && operator_ != CSSMathOperator::kAdd;
  if (right_side_needs_parentheses)
    result.Append('(');
  result.Append(right_side_->CustomCSSText());
  if (right_side_needs_parentheses)
    result.Append(')');

  return result.ToString();
}

bool CSSMathExpressionBinaryOperation::operator==(
    const CSSMathExpressionNode& exp) const {
  if (!exp.IsBinaryOperation())
    return false;

  const CSSMathExpressionBinaryOperation& other =
      To<CSSMathExpressionBinaryOperation>(exp);
  return DataEquivalent(left_side_, other.left_side_) &&
         DataEquivalent(right_side_, other.right_side_) &&
         operator_ == other.operator_;
}

CSSPrimitiveValue::UnitType CSSMathExpressionBinaryOperation::ResolvedUnitType()
    const {
  switch (category_) {
    case kCalcNumber:
      DCHECK_EQ(left_side_->Category(), kCalcNumber);
      DCHECK_EQ(right_side_->Category(), kCalcNumber);
      return CSSPrimitiveValue::UnitType::kNumber;
    case kCalcLength:
    case kCalcPercent: {
      if (left_side_->Category() == kCalcNumber)
        return right_side_->ResolvedUnitType();
      if (right_side_->Category() == kCalcNumber)
        return left_side_->ResolvedUnitType();
      CSSPrimitiveValue::UnitType left_type = left_side_->ResolvedUnitType();
      if (left_type == right_side_->ResolvedUnitType())
        return left_type;
      return CSSPrimitiveValue::UnitType::kUnknown;
    }
    case kCalcAngle:
      return CSSPrimitiveValue::UnitType::kDegrees;
    case kCalcTime:
      return CSSPrimitiveValue::UnitType::kMilliseconds;
    case kCalcFrequency:
      return CSSPrimitiveValue::UnitType::kHertz;
    case kCalcPercentLength:
    case kCalcOther:
      return CSSPrimitiveValue::UnitType::kUnknown;
  }
  NOTREACHED();
  return CSSPrimitiveValue::UnitType::kUnknown;
}

void CSSMathExpressionBinaryOperation::Trace(Visitor* visitor) const {
  visitor->Trace(left_side_);
  visitor->Trace(right_side_);
  CSSMathExpressionNode::Trace(visitor);
}

// static
const CSSMathExpressionNode* CSSMathExpressionBinaryOperation::GetNumberSide(
    const CSSMathExpressionNode* left_side,
    const CSSMathExpressionNode* right_side) {
  if (left_side->Category() == kCalcNumber)
    return left_side;
  if (right_side->Category() == kCalcNumber)
    return right_side;
  return nullptr;
}

// static
double CSSMathExpressionBinaryOperation::EvaluateOperator(double left_value,
                                                          double right_value,
                                                          CSSMathOperator op) {
  // Design doc for infinity and NaN: https://bit.ly/349gXjq
  switch (op) {
    case CSSMathOperator::kAdd:
      if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled())
        return left_value + right_value;
      return clampTo<double>(left_value + right_value);
    case CSSMathOperator::kSubtract:
      if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled())
        return left_value - right_value;
      return clampTo<double>(left_value - right_value);
    case CSSMathOperator::kMultiply:
      if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled())
        return left_value * right_value;
      return clampTo<double>(left_value * right_value);
    case CSSMathOperator::kDivide:
<<<<<<< HEAD
      DCHECK(operands.size() == 1u || operands.size() == 2u);
      return operands[0] / operands[1];
    case CSSMathOperator::kMin: {
      if (operands.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      double minimum = operands[0];
      for (double operand : operands) {
        // std::min(0.0, -0.0) returns 0.0, manually check for such situation
        // and set result to -0.0.
        if (minimum == 0 && operand == 0 &&
            std::signbit(minimum) != std::signbit(operand)) {
          minimum = -0.0;
          continue;
        }
        minimum = std::min(minimum, operand);
      }
      return minimum;
    }
    case CSSMathOperator::kMax: {
      if (operands.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      double maximum = operands[0];
      for (double operand : operands) {
        // std::max(-0.0, 0.0) returns -0.0, manually check for such situation
        // and set result to 0.0.
        if (maximum == 0 && operand == 0 &&
            std::signbit(maximum) != std::signbit(operand)) {
          maximum = 0.0;
          continue;
        }
        maximum = std::max(maximum, operand);
      }
      return maximum;
    }
    case CSSMathOperator::kClamp: {
      DCHECK_EQ(operands.size(), 3u);
      double min = operands[0];
      double val = operands[1];
      double max = operands[2];
      // clamp(MIN, VAL, MAX) is identical to max(MIN, min(VAL, MAX))
      // according to the spec,
      // https://drafts.csswg.org/css-values-4/#funcdef-clamp.
      double minimum = std::min(val, max);
      // std::min(0.0, -0.0) returns 0.0, so manually check for this situation
      // to set result to -0.0.
      if (val == 0 && max == 0 && !std::signbit(val) && std::signbit(max)) {
        minimum = -0.0;
      }
      double maximum = std::max(min, minimum);
      // std::max(-0.0, 0.0) returns -0.0, so manually check for this situation
      // to set result to 0.0.
      if (min == 0 && minimum == 0 && std::signbit(min) &&
          !std::signbit(minimum)) {
        maximum = 0.0;
      }
      return maximum;
    }
    case CSSMathOperator::kRoundNearest:
    case CSSMathOperator::kRoundUp:
    case CSSMathOperator::kRoundDown:
    case CSSMathOperator::kRoundToZero:
    case CSSMathOperator::kMod:
    case CSSMathOperator::kRem: {
      DCHECK_EQ(operands.size(), 2u);
      return EvaluateSteppedValueFunction(op, operands[0], operands[1]);
    }
    case CSSMathOperator::kHypot: {
      DCHECK_GE(operands.size(), 1u);
      double value = 0;
      for (double operand : operands) {
        value = std::hypot(value, operand);
      }
      return value;
    }
    case CSSMathOperator::kAbs: {
      DCHECK_EQ(operands.size(), 1u);
      return std::abs(operands.front());
    }
    case CSSMathOperator::kSign: {
      DCHECK_EQ(operands.size(), 1u);
      const double value = operands.front();
      const double signum =
          (value == 0 || std::isnan(value)) ? value : ((value > 0) ? 1 : -1);
      return signum;
    }
    case CSSMathOperator::kProgress:
    case CSSMathOperator::kMediaProgress:
    case CSSMathOperator::kContainerProgress: {
      CHECK_EQ(operands.size(), 3u);
      return (operands[0] - operands[1]) / (operands[2] - operands[1]);
    }
    case CSSMathOperator::kCalcSize: {
      CHECK_EQ(operands.size(), 2u);
      // TODO(https://crbug.com/313072): In theory we could also
      // evaluate (a) cases where the basis (operand 0) is not a double,
      // and (b) cases where the basis (operand 0) is a double and the
      // calculation (operand 1) requires 'size' keyword substitutions.
      // But for now just handle the simplest case.
      return operands[1];
    }

    case CSSMathOperator::kInvalid:
=======
      if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled())
        return left_value / right_value;
      if (right_value)
        return clampTo<double>(left_value / right_value);
      return std::numeric_limits<double>::quiet_NaN();
    default:
>>>>>>> chromium
      NOTREACHED();
      break;
  }
  return 0;
}

#if DCHECK_IS_ON()
bool CSSMathExpressionBinaryOperation::InvolvesPercentageComparisons() const {
  return left_side_->InvolvesPercentageComparisons() ||
         right_side_->InvolvesPercentageComparisons();
}
#endif

// ------ End of CSSMathExpressionBinaryOperation member functions ------

// ------ Start of CSSMathExpressionVariadicOperation member functions ------

// static
CSSMathExpressionVariadicOperation* CSSMathExpressionVariadicOperation::Create(
    Operands&& operands,
    CSSMathOperator op) {
  DCHECK(op == CSSMathOperator::kMin || op == CSSMathOperator::kMax);
  DCHECK(operands.size());
  bool is_first = true;
  CalculationCategory category;
  bool is_integer;
  for (const auto& operand : operands) {
    if (is_first) {
      category = operand->Category();
      is_integer = operand->IsInteger();
    } else {
      category = kAddSubtractResult[category][operand->Category()];
      if (!operand->IsInteger())
        is_integer = false;
    }
    is_first = false;
    if (category == kCalcOther)
      return nullptr;
  }
  return MakeGarbageCollected<CSSMathExpressionVariadicOperation>(
      category, is_integer, std::move(operands), op);
}

CSSMathExpressionVariadicOperation::CSSMathExpressionVariadicOperation(
    CalculationCategory category,
    bool is_integer_result,
    Operands&& operands,
    CSSMathOperator op)
    : CSSMathExpressionNode(category,
                            is_integer_result,
                            true /* has_comparisons */),
      operands_(std::move(operands)),
      operator_(op) {}

void CSSMathExpressionVariadicOperation::Trace(Visitor* visitor) const {
  visitor->Trace(operands_);
  CSSMathExpressionNode::Trace(visitor);
}

bool CSSMathExpressionVariadicOperation::IsZero() const {
  absl::optional<double> maybe_value = ComputeValueInCanonicalUnit();
  return maybe_value && !*maybe_value;
}

double CSSMathExpressionVariadicOperation::EvaluateBinary(double lhs,
                                                          double rhs) const {
  if (std::isnan(lhs) || std::isnan(rhs))
    return std::numeric_limits<double>::quiet_NaN();

  switch (operator_) {
    case CSSMathOperator::kMin:
      return std::min(lhs, rhs);
    case CSSMathOperator::kMax:
      return std::max(lhs, rhs);
    default:
      NOTREACHED();
      return 0;
  }
}

absl::optional<double>
CSSMathExpressionVariadicOperation::ComputeValueInCanonicalUnit() const {
  absl::optional<double> first_value =
      operands_.front()->ComputeValueInCanonicalUnit();
  if (!first_value)
    return absl::nullopt;

  double result = *first_value;
  for (const auto& operand : SecondToLastOperands()) {
    absl::optional<double> maybe_value = operand->ComputeValueInCanonicalUnit();
    if (!maybe_value)
      return absl::nullopt;
    result = EvaluateBinary(result, *maybe_value);
  }
  return result;
}

double CSSMathExpressionVariadicOperation::DoubleValue() const {
  DCHECK(HasDoubleValue(ResolvedUnitType()));
  double result = operands_.front()->DoubleValue();
  for (const auto& operand : SecondToLastOperands())
    result = EvaluateBinary(result, operand->DoubleValue());
  return result;
}

double CSSMathExpressionVariadicOperation::ComputeLengthPx(
    const CSSToLengthConversionData& data) const {
  DCHECK_EQ(kCalcLength, Category());
  double result = operands_.front()->ComputeLengthPx(data);
  for (const auto& operand : SecondToLastOperands())
    result = EvaluateBinary(result, operand->ComputeLengthPx(data));
  return result;
}

String CSSMathExpressionVariadicOperation::CSSTextAsClamp() const {
  DCHECK(is_clamp_);
  DCHECK_EQ(CSSMathOperator::kMax, operator_);
  DCHECK_EQ(2u, operands_.size());
  DCHECK(operands_[1]->IsVariadicOperation());
  const auto& nested = To<CSSMathExpressionVariadicOperation>(*operands_[1]);
  DCHECK(!nested.is_clamp_);
  DCHECK_EQ(CSSMathOperator::kMin, nested.operator_);
  DCHECK_EQ(2u, nested.operands_.size());

  StringBuilder result;
  result.Append("clamp(");
  result.Append(operands_[0]->CustomCSSText());
  result.Append(", ");
  result.Append(nested.operands_[0]->CustomCSSText());
  result.Append(", ");
  result.Append(nested.operands_[1]->CustomCSSText());
  result.Append(")");
  return result.ToString();
}

String CSSMathExpressionVariadicOperation::CustomCSSText() const {
  if (is_clamp_)
    return CSSTextAsClamp();

  StringBuilder result;
  result.Append(ToString(operator_));
  result.Append('(');
  result.Append(operands_.front()->CustomCSSText());
  for (const auto& operand : SecondToLastOperands()) {
    result.Append(", ");
    result.Append(operand->CustomCSSText());
  }
  result.Append(')');

  return result.ToString();
}

absl::optional<PixelsAndPercent>
CSSMathExpressionVariadicOperation::ToPixelsAndPercent(
    const CSSToLengthConversionData& conversion_data) const {
  return absl::nullopt;
}

scoped_refptr<const CalculationExpressionNode>
CSSMathExpressionVariadicOperation::ToCalculationExpression(
    const CSSToLengthConversionData& data) const {
  Vector<scoped_refptr<const CalculationExpressionNode>> operands;
  operands.ReserveCapacity(operands_.size());
  for (const auto& operand : operands_)
    operands.push_back(operand->ToCalculationExpression(data));
  auto expression_type = operator_ == CSSMathOperator::kMin
                             ? CalculationExpressionComparisonNode::Type::kMin
                             : CalculationExpressionComparisonNode::Type::kMax;
  return CalculationExpressionComparisonNode::CreateSimplified(
      std::move(operands), expression_type);
}

bool CSSMathExpressionVariadicOperation::AccumulateLengthArray(CSSLengthArray&,
                                                               double) const {
  // When comparison function are involved, we can't resolve the expression into
  // a length array.
  // TODO(crbug.com/991672): We need a more general length interpolation
  // implemetation that doesn't rely on CSSLengthArray.
  return false;
}

void CSSMathExpressionVariadicOperation::AccumulateLengthUnitTypes(
    CSSPrimitiveValue::LengthTypeFlags& types) const {
  for (const auto& operand : operands_)
    operand->AccumulateLengthUnitTypes(types);
}

bool CSSMathExpressionVariadicOperation::IsComputationallyIndependent() const {
  for (const auto& operand : operands_) {
    if (!operand->IsComputationallyIndependent())
      return false;
  }
  return true;
}

bool CSSMathExpressionVariadicOperation::operator==(
    const CSSMathExpressionNode& exp) const {
  if (!exp.IsVariadicOperation())
    return false;
  const CSSMathExpressionVariadicOperation& other =
      To<CSSMathExpressionVariadicOperation>(exp);
  if (operator_ != other.operator_)
    return false;
  if (operands_.size() != other.operands_.size())
    return false;
  for (wtf_size_t i = 0; i < operands_.size(); ++i) {
    if (!DataEquivalent(operands_[i], other.operands_[i]))
      return false;
  }
  return true;
}

CSSPrimitiveValue::UnitType
CSSMathExpressionVariadicOperation::ResolvedUnitType() const {
  if (Category() == kCalcNumber)
    return CSSPrimitiveValue::UnitType::kNumber;

  CSSPrimitiveValue::UnitType result = operands_.front()->ResolvedUnitType();
  if (result == CSSPrimitiveValue::UnitType::kUnknown)
    return CSSPrimitiveValue::UnitType::kUnknown;
  for (const auto& operand : SecondToLastOperands()) {
    CSSPrimitiveValue::UnitType next = operand->ResolvedUnitType();
    if (next == CSSPrimitiveValue::UnitType::kUnknown || next != result)
      return CSSPrimitiveValue::UnitType::kUnknown;
  }
  return result;
}

#if DCHECK_IS_ON()
bool CSSMathExpressionVariadicOperation::InvolvesPercentageComparisons() const {
  if (Category() == kCalcPercent && operands_.size() > 1u)
    return true;
  for (const auto& operand : operands_) {
    if (operand->InvolvesPercentageComparisons())
      return true;
  }
  return false;
}
#endif

// ------ End of CSSMathExpressionVariadicOperation member functions

class CSSMathExpressionNodeParser {
  STACK_ALLOCATED();

 public:
  CSSMathExpressionNodeParser() {}

<<<<<<< HEAD
  // A struct containing parser state that varies within the expression tree.
  struct State {
    STACK_ALLOCATED();

   public:
    uint8_t depth;
    bool allow_size_keyword;

    static_assert(uint8_t(kMaxExpressionDepth + 1) == kMaxExpressionDepth + 1);

    State() : depth(0), allow_size_keyword(false) {}
    State(const State&) = default;
    State& operator=(const State&) = default;
  };

  CSSMathExpressionNodeParser(const CSSParserContext& context,
                              const Flags parsing_flags,
                              CSSAnchorQueryTypes allowed_anchor_queries,
                              const CSSColorChannelMap& color_channel_map)
      : context_(context),
        allowed_anchor_queries_(allowed_anchor_queries),
        parsing_flags_(parsing_flags),
        color_channel_map_(color_channel_map) {}

  bool IsSupportedMathFunction(CSSValueID function_id) {
    switch (function_id) {
      case CSSValueID::kMin:
      case CSSValueID::kMax:
      case CSSValueID::kClamp:
      case CSSValueID::kCalc:
      case CSSValueID::kWebkitCalc:
      case CSSValueID::kSin:
      case CSSValueID::kCos:
      case CSSValueID::kTan:
      case CSSValueID::kAsin:
      case CSSValueID::kAcos:
      case CSSValueID::kAtan:
      case CSSValueID::kAtan2:
      case CSSValueID::kAnchor:
      case CSSValueID::kAnchorSize:
      case CSSValueID::kCalcSize:
        return true;
      case CSSValueID::kPow:
      case CSSValueID::kSqrt:
      case CSSValueID::kHypot:
      case CSSValueID::kLog:
      case CSSValueID::kExp:
        return RuntimeEnabledFeatures::CSSExponentialFunctionsEnabled();
      case CSSValueID::kRound:
      case CSSValueID::kMod:
      case CSSValueID::kRem:
        return RuntimeEnabledFeatures::CSSSteppedValueFunctionsEnabled();
      case CSSValueID::kAbs:
      case CSSValueID::kSign:
        return RuntimeEnabledFeatures::CSSSignRelatedFunctionsEnabled();
      case CSSValueID::kProgress:
      case CSSValueID::kMediaProgress:
      case CSSValueID::kContainerProgress:
        return RuntimeEnabledFeatures::CSSProgressNotationEnabled();
      case CSSValueID::kSiblingCount:
      case CSSValueID::kSiblingIndex:
        return RuntimeEnabledFeatures::CSSSiblingFunctionsEnabled();
      // TODO(crbug.com/1284199): Support other math functions.
      default:
        return false;
    }
=======
  CSSMathExpressionNode* ParseCalc(CSSParserTokenRange tokens) {
    tokens.ConsumeWhitespace();
    CSSMathExpressionNode* result = ParseValueExpression(tokens, 0);
    if (!result || !tokens.AtEnd())
      return nullptr;
    return result;
>>>>>>> chromium
  }

  CSSMathExpressionNode* ParseMinOrMax(CSSParserTokenRange tokens,
                                       CSSMathOperator op,
                                       int depth) {
    DCHECK(op == CSSMathOperator::kMin || op == CSSMathOperator::kMax);
    if (tokens.AtEnd())
      return nullptr;

    CSSMathExpressionVariadicOperation::Operands operands;
    bool last_token_is_comma = false;
    while (!tokens.AtEnd()) {
      tokens.ConsumeWhitespace();
      CSSMathExpressionNode* operand = ParseValueExpression(tokens, depth);
      if (!operand)
        return nullptr;

      last_token_is_comma = false;
      operands.push_back(operand);

      if (!css_parsing_utils::ConsumeCommaIncludingWhitespace(tokens))
        break;
      last_token_is_comma = true;
    }

    if (operands.IsEmpty() || !tokens.AtEnd() || last_token_is_comma)
      return nullptr;

    return CSSMathExpressionVariadicOperation::Create(std::move(operands), op);
  }

  CSSMathExpressionNode* ParseClamp(CSSParserTokenRange tokens, int depth) {
    if (tokens.AtEnd())
      return nullptr;

    CSSMathExpressionNode* min_operand = ParseValueExpression(tokens, depth);
    if (!min_operand)
      return nullptr;

    if (!css_parsing_utils::ConsumeCommaIncludingWhitespace(tokens))
      return nullptr;

    CSSMathExpressionNode* val_operand = ParseValueExpression(tokens, depth);
    if (!val_operand)
      return nullptr;

<<<<<<< HEAD
    stream.ConsumeWhitespace();

    CSSMathExpressionNode* basis = nullptr;

    CSSValueID id = stream.Peek().Id();
    bool basis_is_any = id == CSSValueID::kAny;
    if (id != CSSValueID::kInvalid &&
        (id == CSSValueID::kAny ||
         (id == CSSValueID::kAuto &&
          parsing_flags_.Has(Flag::AllowAutoInCalcSize)) ||
         (id == CSSValueID::kContent &&
          parsing_flags_.Has(Flag::AllowContentInCalcSize)) ||
         css_parsing_utils::ValidWidthOrHeightKeyword(id, context_))) {
      // TODO(https://crbug.com/353538495): Right now 'flex-basis'
      // accepts fewer keywords than other width properties.  So for
      // now specifically exclude the ones that it doesn't accept,
      // based off the flag for accepting 'content'.
      if (parsing_flags_.Has(Flag::AllowContentInCalcSize) &&
          !css_parsing_utils::IdentMatches<
              CSSValueID::kAny, CSSValueID::kAuto, CSSValueID::kContent,
              CSSValueID::kMinContent, CSSValueID::kMaxContent,
              CSSValueID::kFitContent, CSSValueID::kStretch>(id)) {
        return nullptr;
      }

      // Note: We don't want to accept 'none' (for 'max-*' properties) since
      // it's not meaningful for animation, since it's equivalent to infinity.
      stream.ConsumeIncludingWhitespace();
      basis = CSSMathExpressionKeywordLiteral::Create(
          id, CSSMathExpressionKeywordLiteral::Context::kCalcSize);
    } else {
      basis = ParseValueExpression(stream, state);
      if (!basis) {
        return nullptr;
      }
    }

    if (!css_parsing_utils::ConsumeCommaIncludingWhitespace(stream)) {
=======
    if (!css_parsing_utils::ConsumeCommaIncludingWhitespace(tokens))
>>>>>>> chromium
      return nullptr;

    CSSMathExpressionNode* max_operand = ParseValueExpression(tokens, depth);
    if (!max_operand)
      return nullptr;

<<<<<<< HEAD
    return CSSMathExpressionOperation::CreateCalcSizeOperation(basis,
                                                               calculation);
  }

  CSSMathExpressionNode* ParseSiblingIndexOrCount(CSSValueID function_id,
                                                  CSSParserTokenStream& stream,
                                                  State state) {
    if (function_id != CSSValueID::kSiblingCount &&
        function_id != CSSValueID::kSiblingIndex) {
      return nullptr;
    }
    if (!stream.AtEnd()) {
      // These do not take any arguments.
      return nullptr;
    }
    return MakeGarbageCollected<CSSMathExpressionSiblingFunction>(function_id);
  }

  CSSMathExpressionNode* ParseMathFunction(CSSValueID function_id,
                                           CSSParserTokenStream& stream,
                                           State state) {
    if (!IsSupportedMathFunction(function_id)) {
      return nullptr;
    }
    if (auto* anchor_query = ParseAnchorQuery(function_id, stream)) {
      context_.Count(WebFeature::kCSSAnchorPositioning);
      return anchor_query;
    }
    if (RuntimeEnabledFeatures::CSSProgressNotationEnabled()) {
      if (CSSMathExpressionNode* progress =
              ParseProgressNotation(function_id, stream, state)) {
        return progress;
      }
    }
    if (CSSMathExpressionNode* calc_size =
            ParseCalcSize(function_id, stream, state)) {
      context_.Count(WebFeature::kCSSCalcSizeFunction);
      return calc_size;
    }
    if (RuntimeEnabledFeatures::CSSSiblingFunctionsEnabled()) {
      if (CSSMathExpressionNode* sibling_function =
              ParseSiblingIndexOrCount(function_id, stream, state)) {
        return sibling_function;
      }
    }
=======
    if (!tokens.AtEnd())
      return nullptr;
>>>>>>> chromium

    // clamp(MIN, VAL, MAX) is identical to max(MIN, min(VAL, MAX))

    auto* nested = CSSMathExpressionVariadicOperation::Create(
        {val_operand, max_operand}, CSSMathOperator::kMin);
    if (!nested)
      return nullptr;

    auto* result = CSSMathExpressionVariadicOperation::Create(
        {min_operand, nested}, CSSMathOperator::kMax);
    if (!result)
      return nullptr;

<<<<<<< HEAD
      case CSSValueID::kSiblingIndex:
      case CSSValueID::kSiblingCount:
        // Handled above.
        return nullptr;

      // TODO(crbug.com/1284199): Support other math functions.
      default:
        return nullptr;
    }
=======
    result->SetIsClamp();
    return result;
>>>>>>> chromium
  }

 private:
  CSSMathExpressionNode* ParseValue(CSSParserTokenRange& tokens) {
    CSSParserToken token = tokens.ConsumeIncludingWhitespace();
    if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled()) {
      if (token.Id() == CSSValueID::kInfinity) {
        return CSSMathExpressionNumericLiteral::Create(
            std::numeric_limits<double>::infinity(),
            CSSPrimitiveValue::UnitType::kNumber, false);
      }
      if (token.Id() == CSSValueID::kNegativeInfinity) {
        return CSSMathExpressionNumericLiteral::Create(
            -std::numeric_limits<double>::infinity(),
            CSSPrimitiveValue::UnitType::kNumber, false);
      }
      if (token.Id() == CSSValueID::kNan) {
        return CSSMathExpressionNumericLiteral::Create(
            std::numeric_limits<double>::quiet_NaN(),
            CSSPrimitiveValue::UnitType::kNumber, false);
      }
    }
    if (!(token.GetType() == kNumberToken ||
          token.GetType() == kPercentageToken ||
          token.GetType() == kDimensionToken))
      return nullptr;

    CSSPrimitiveValue::UnitType type = token.GetUnitType();
    if (UnitCategory(type) == kCalcOther)
      return nullptr;

    return CSSMathExpressionNumericLiteral::Create(
        CSSNumericLiteralValue::Create(token.NumericValue(), type),
        token.GetNumericValueType() == kIntegerValueType);
  }

  CSSMathExpressionNode* ParseValueTerm(CSSParserTokenRange& tokens,
                                        int depth) {
    if (tokens.AtEnd())
      return nullptr;

    if (tokens.Peek().GetType() == kLeftParenthesisToken ||
        tokens.Peek().FunctionId() == CSSValueID::kCalc) {
      CSSParserTokenRange inner_range = tokens.ConsumeBlock();
      tokens.ConsumeWhitespace();
      inner_range.ConsumeWhitespace();
      CSSMathExpressionNode* result = ParseValueExpression(inner_range, depth);
      if (!result)
        return nullptr;
      result->SetIsNestedCalc();
      return result;
    }

    if (tokens.Peek().GetType() == kFunctionToken) {
      CSSValueID function_id = tokens.Peek().FunctionId();
      CSSParserTokenRange inner_range = tokens.ConsumeBlock();
      tokens.ConsumeWhitespace();
      inner_range.ConsumeWhitespace();
      switch (function_id) {
        case CSSValueID::kMin:
          return ParseMinOrMax(inner_range, CSSMathOperator::kMin, depth);
        case CSSValueID::kMax:
          return ParseMinOrMax(inner_range, CSSMathOperator::kMax, depth);
        case CSSValueID::kClamp:
          return ParseClamp(inner_range, depth);
        default:
          break;
      }
    }

    return ParseValue(tokens);
  }

  CSSMathExpressionNode* ParseValueMultiplicativeExpression(
      CSSParserTokenRange& tokens,
      int depth) {
    if (tokens.AtEnd())
      return nullptr;

    CSSMathExpressionNode* result = ParseValueTerm(tokens, depth);
    if (!result)
      return nullptr;

    while (!tokens.AtEnd()) {
      CSSMathOperator math_operator = ParseCSSArithmeticOperator(tokens.Peek());
      if (math_operator != CSSMathOperator::kMultiply &&
          math_operator != CSSMathOperator::kDivide)
        break;
      tokens.ConsumeIncludingWhitespace();

      CSSMathExpressionNode* rhs = ParseValueTerm(tokens, depth);
      if (!rhs)
        return nullptr;

      result = CSSMathExpressionBinaryOperation::CreateSimplified(
          result, rhs, math_operator);

      if (!result)
        return nullptr;
    }

    return result;
  }

  CSSMathExpressionNode* ParseAdditiveValueExpression(
      CSSParserTokenRange& tokens,
      int depth) {
    if (tokens.AtEnd())
      return nullptr;

    CSSMathExpressionNode* result =
        ParseValueMultiplicativeExpression(tokens, depth);
    if (!result)
      return nullptr;

    while (!tokens.AtEnd()) {
      CSSMathOperator math_operator = ParseCSSArithmeticOperator(tokens.Peek());
      if (math_operator != CSSMathOperator::kAdd &&
          math_operator != CSSMathOperator::kSubtract)
        break;
      if ((&tokens.Peek() - 1)->GetType() != kWhitespaceToken)
        return nullptr;  // calc(1px+ 2px) is invalid
      tokens.Consume();
      if (tokens.Peek().GetType() != kWhitespaceToken)
        return nullptr;  // calc(1px +2px) is invalid
      tokens.ConsumeIncludingWhitespace();

      CSSMathExpressionNode* rhs =
          ParseValueMultiplicativeExpression(tokens, depth);
      if (!rhs)
        return nullptr;

      result = CSSMathExpressionBinaryOperation::CreateSimplified(
          result, rhs, math_operator);

      if (!result)
        return nullptr;
    }

    return result;
  }

  CSSMathExpressionNode* ParseValueExpression(CSSParserTokenRange& tokens,
                                              int depth) {
    if (++depth > kMaxExpressionDepth)
      return nullptr;
    return ParseAdditiveValueExpression(tokens, depth);
  }
};

scoped_refptr<const CalculationValue> CSSMathExpressionNode::ToCalcValue(
    const CSSToLengthConversionData& conversion_data,
    ValueRange range,
    bool allows_negative_percentage_reference) const {
  if (auto maybe_pixels_and_percent = ToPixelsAndPercent(conversion_data)) {
    // Clamping if pixels + percent could result in NaN. In special case,
    // inf px + inf % could evaluate to nan when
    // allows_negative_percentage_reference is true.
    if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled()) {
      if (IsNaN(*maybe_pixels_and_percent,
                allows_negative_percentage_reference)) {
        maybe_pixels_and_percent = CreateClampedSamePixelsAndPercent(
            std::numeric_limits<float>::quiet_NaN());
      } else {
        maybe_pixels_and_percent->pixels = CSSValueClampingUtils::ClampLength(
            maybe_pixels_and_percent->pixels);
        maybe_pixels_and_percent->percent = CSSValueClampingUtils::ClampLength(
            maybe_pixels_and_percent->percent);
      }
    }
    return CalculationValue::Create(*maybe_pixels_and_percent, range);
  }

  auto value = ToCalculationExpression(conversion_data);
  if (RuntimeEnabledFeatures::CSSCalcInfinityAndNaNEnabled()) {
    absl::optional<PixelsAndPercent> evaluated_value =
        EvaluateValueIfNaNorInfinity(value,
                                     allows_negative_percentage_reference);
    if (evaluated_value.has_value()) {
      return CalculationValue::Create(evaluated_value.value(), range);
    }
  }
  return CalculationValue::CreateSimplified(value, range);
}

// static
CSSMathExpressionNode* CSSMathExpressionNode::Create(
    const CalculationValue& calc) {
  if (calc.IsExpression())
    return Create(*calc.GetOrCreateExpression());
  return Create(calc.GetPixelsAndPercent());
}

// static
CSSMathExpressionNode* CSSMathExpressionNode::Create(PixelsAndPercent value) {
  double percent = value.percent;
  double pixels = value.pixels;
  CSSMathOperator op = CSSMathOperator::kAdd;
  if (pixels < 0) {
    pixels = -pixels;
    op = CSSMathOperator::kSubtract;
  }
  return CSSMathExpressionBinaryOperation::Create(
      CSSMathExpressionNumericLiteral::Create(
          CSSNumericLiteralValue::Create(
              percent, CSSPrimitiveValue::UnitType::kPercentage),
          percent == trunc(percent)),
      CSSMathExpressionNumericLiteral::Create(
          CSSNumericLiteralValue::Create(pixels,
                                         CSSPrimitiveValue::UnitType::kPixels),
          pixels == trunc(pixels)),
      op);
}

// static
CSSMathExpressionNode* CSSMathExpressionNode::Create(
    const CalculationExpressionNode& node) {
  if (node.IsLeaf()) {
    const auto& leaf = To<CalculationExpressionLeafNode>(node);
    return Create(leaf.GetPixelsAndPercent());
  }

  if (node.IsMultiplication()) {
    const auto& multiplication =
        To<CalculationExpressionMultiplicationNode>(node);
    double factor = multiplication.GetFactor();
    return CSSMathExpressionBinaryOperation::Create(
        Create(multiplication.GetChild()),
        CSSMathExpressionNumericLiteral::Create(
            CSSNumericLiteralValue::Create(
                factor, CSSPrimitiveValue::UnitType::kNumber),
            factor == trunc(factor)),
        CSSMathOperator::kMultiply);
  }

  if (node.IsAdditive()) {
    const auto& add_or_subtract = To<CalculationExpressionAdditiveNode>(node);
    auto* lhs = Create(add_or_subtract.GetLeftSide());
    auto* rhs = Create(add_or_subtract.GetRightSide());
    CSSMathOperator op = add_or_subtract.IsAdd() ? CSSMathOperator::kAdd
                                                 : CSSMathOperator::kSubtract;
    return CSSMathExpressionBinaryOperation::Create(lhs, rhs, op);
  }

  DCHECK(node.IsComparison());
  const auto& comparison = To<CalculationExpressionComparisonNode>(node);
  CSSMathExpressionVariadicOperation::Operands operands;
  for (const auto& operand : comparison.GetOperands())
    operands.push_back(Create(*operand));
  CSSMathOperator op =
      comparison.IsMin() ? CSSMathOperator::kMin : CSSMathOperator::kMax;
  return CSSMathExpressionVariadicOperation::Create(std::move(operands), op);
}

// static
CSSMathExpressionNode* CSSMathExpressionNode::ParseCalc(
    const CSSParserTokenRange& tokens) {
  CSSMathExpressionNodeParser parser;
  return parser.ParseCalc(tokens);
}

// static
CSSMathExpressionNode* CSSMathExpressionNode::ParseMin(
    const CSSParserTokenRange& tokens) {
  CSSMathExpressionNodeParser parser;
  return parser.ParseMinOrMax(tokens, CSSMathOperator::kMin, 0);
}

// static
CSSMathExpressionNode* CSSMathExpressionNode::ParseMax(
    const CSSParserTokenRange& tokens) {
  CSSMathExpressionNodeParser parser;
  return parser.ParseMinOrMax(tokens, CSSMathOperator::kMax, 0);
}

// static
CSSMathExpressionNode* CSSMathExpressionNode::ParseClamp(
    const CSSParserTokenRange& tokens) {
  CSSMathExpressionNodeParser parser;
  return parser.ParseClamp(tokens, 0);
}

String CSSMathExpressionSiblingFunction::CustomCSSText() const {
  return function_id_ == CSSValueID::kSiblingIndex ? "sibling-index()"
                                                   : "sibling-count()";
}

scoped_refptr<const CalculationExpressionNode>
CSSMathExpressionSiblingFunction::ToCalculationExpression(
    const CSSLengthResolver& length_resolver) const {
  return base::MakeRefCounted<CalculationExpressionNumberNode>(
      ComputeDouble(length_resolver));
}

bool CSSMathExpressionSiblingFunction::operator==(
    const CSSMathExpressionNode& other) const {
  return other.IsSiblingFunction() &&
         function_id_ ==
             To<CSSMathExpressionSiblingFunction>(other).function_id_;
}

double CSSMathExpressionSiblingFunction::ComputeDouble(
    const CSSLengthResolver& length_resolver) const {
  length_resolver.ReferenceSibling();
  const Element* element = length_resolver.GetElement();
  NthIndexCache* nth_index_cache = element->ownerDocument()->GetNthIndexCache();
  // TODO(crbug.com/40282719): Use flat tree siblings?
  if (function_id_ == CSSValueID::kSiblingIndex) {
    return nth_index_cache->NthChildIndex(const_cast<Element&>(*element),
                                          /*filter=*/nullptr,
                                          /*selector_checker=*/nullptr,
                                          /*context=*/nullptr);
  } else {
    return nth_index_cache->NthChildIndex(const_cast<Element&>(*element),
                                          /*filter=*/nullptr,
                                          /*selector_checker=*/nullptr,
                                          /*context=*/nullptr) +
           nth_index_cache->NthLastChildIndex(const_cast<Element&>(*element),
                                              /*filter=*/nullptr,
                                              /*selector_checker=*/nullptr,
                                              /*context=*/nullptr) -
           1;
  }
}

}  // namespace blink
