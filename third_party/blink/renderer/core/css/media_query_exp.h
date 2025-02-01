/*
 * CSS Media Query
 *
 * Copyright (C) 2006 Kimmo Kinnunen <kimmo.t.kinnunen@nokia.com>.
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_MEDIA_QUERY_EXP_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_MEDIA_QUERY_EXP_H_

#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/css/css_primitive_value.h"
#include "third_party/blink/renderer/core/css/css_value.h"
#include "third_party/blink/renderer/core/css/media_feature_names.h"
#include "third_party/blink/renderer/core/css_value_keywords.h"
#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"

namespace blink {

class CSSParserContext;
class CSSParserTokenRange;
class ExecutionContext;

struct MediaQueryExpValue {
  DISALLOW_NEW();
  CSSValueID id;
  double value;
  CSSPrimitiveValue::UnitType unit;
  unsigned numerator;
  unsigned denominator;

  bool is_id;
  bool is_value;
  bool is_ratio;

<<<<<<< HEAD
  explicit MediaQueryExpValue(CSSValueID id) : type_(Type::kId), id_(id) {}
  explicit MediaQueryExpValue(const CSSValue& value)
      : type_(Type::kValue), value_(value) {}
  MediaQueryExpValue(const CSSPrimitiveValue& numerator,
                     const CSSPrimitiveValue& denominator)
      : type_(Type::kRatio),
        ratio_(MakeGarbageCollected<cssvalue::CSSRatioValue>(numerator,
                                                             denominator)) {}
  void Trace(Visitor* visitor) const {
    visitor->Trace(value_);
    visitor->Trace(ratio_);
  }

  bool IsValid() const { return type_ != Type::kInvalid; }
  bool IsId() const { return type_ == Type::kId; }
  bool IsRatio() const { return type_ == Type::kRatio; }
  bool IsValue() const { return type_ == Type::kValue; }

  bool IsPrimitiveValue() const {
    return IsValue() && value_->IsPrimitiveValue();
  }
  bool IsNumber() const {
    return IsPrimitiveValue() && To<CSSPrimitiveValue>(*value_).IsNumber();
  }
  bool IsResolution() const {
    return IsPrimitiveValue() && To<CSSPrimitiveValue>(*value_).IsResolution();
  }
  bool IsNumericLiteralValue() const {
    return IsValue() && value_->IsNumericLiteralValue();
  }
  bool IsDotsPerCentimeter() const {
    return IsNumericLiteralValue() &&
           To<CSSNumericLiteralValue>(*value_).GetType() ==
               CSSPrimitiveValue::UnitType::kDotsPerCentimeter;
  }

  CSSValueID Id() const {
    DCHECK(IsId());
    return id_;
  }

  double GetDoubleValue() const {
    DCHECK(IsNumericLiteralValue());
    return To<CSSNumericLiteralValue>(*value_).ClampedDoubleValue();
  }

  CSSPrimitiveValue::UnitType GetUnitType() const {
    DCHECK(IsNumericLiteralValue());
    return To<CSSNumericLiteralValue>(*value_).GetType();
  }

  const CSSValue& GetCSSValue() const {
    DCHECK(IsValue());
    return *value_;
  }

  const CSSValue& Numerator() const {
    DCHECK(IsRatio());
    return ratio_->First();
  }

  const CSSValue& Denominator() const {
    DCHECK(IsRatio());
    return ratio_->Second();
  }

  double Value(const CSSLengthResolver& length_resolver) const {
    DCHECK(IsValue());
    return To<CSSPrimitiveValue>(*value_).ComputeValueInCanonicalUnit(
        length_resolver);
  }

  double Numerator(const CSSLengthResolver& length_resolver) const {
    DCHECK(IsRatio());
    return ratio_->First().ComputeValueInCanonicalUnit(length_resolver);
  }

  double Denominator(const CSSLengthResolver& length_resolver) const {
    DCHECK(IsRatio());
    return ratio_->Second().ComputeValueInCanonicalUnit(length_resolver);
  }

  enum UnitFlags {
    kNone = 0,
    kFontRelative = 1 << 0,
    kRootFontRelative = 1 << 1,
    kDynamicViewport = 1 << 2,
    kStaticViewport = 1 << 3,
    kContainer = 1 << 4,
  };

  static const int kUnitFlagsBits = 5;

  unsigned GetUnitFlags() const;
=======
  MediaQueryExpValue()
      : id(CSSValueID::kInvalid),
        value(0),
        unit(CSSPrimitiveValue::UnitType::kUnknown),
        numerator(0),
        denominator(1),
        is_id(false),
        is_value(false),
        is_ratio(false) {}
>>>>>>> chromium

  bool IsValid() const { return (is_id || is_value || is_ratio); }
  String CssText() const;
  bool Equals(const MediaQueryExpValue& exp_value) const {
    if (is_id)
      return (id == exp_value.id);
    if (is_value)
      return (value == exp_value.value);
    if (is_ratio)
      return (numerator == exp_value.numerator &&
              denominator == exp_value.denominator);
    return !exp_value.IsValid();
  }
};

class CORE_EXPORT MediaQueryExp {
  DISALLOW_NEW();

 public:
  // Returns an invalid MediaQueryExp if the arguments are invalid.
  static MediaQueryExp Create(const String& media_feature,
                              CSSParserTokenRange&,
                              const CSSParserContext&,
                              const ExecutionContext*);
  static MediaQueryExp Invalid() {
    return MediaQueryExp(String(), MediaQueryExpValue());
  }

  MediaQueryExp(const MediaQueryExp& other);
  ~MediaQueryExp();

  const String& MediaFeature() const { return media_feature_; }

  MediaQueryExpValue ExpValue() const { return exp_value_; }

  bool IsValid() const { return !media_feature_.IsNull(); }

  bool operator==(const MediaQueryExp& other) const;

  bool IsViewportDependent() const;

  bool IsDeviceDependent() const;

  bool IsWidthDependent() const;

  bool IsHeightDependent() const;

  String Serialize() const;

 private:
  MediaQueryExp(const String&, const MediaQueryExpValue&);

<<<<<<< HEAD
  AtomicString media_feature_;
  MediaQueryExpBounds bounds_;
};

// MediaQueryExpNode representing a tree of MediaQueryExp objects capable of
// nested/compound expressions.
class CORE_EXPORT MediaQueryExpNode
    : public GarbageCollected<MediaQueryExpNode> {
 public:
  virtual ~MediaQueryExpNode() = default;
  virtual void Trace(Visitor*) const {}

  enum class Type { kFeature, kNested, kFunction, kNot, kAnd, kOr, kUnknown };

  enum FeatureFlag {
    kFeatureUnknown = 1 << 1,
    kFeatureWidth = 1 << 2,
    kFeatureHeight = 1 << 3,
    kFeatureInlineSize = 1 << 4,
    kFeatureBlockSize = 1 << 5,
    kFeatureStyle = 1 << 6,
    kFeatureSticky = 1 << 7,
    kFeatureSnap = 1 << 8,
    kFeatureScrollable = 1 << 9,
  };

  using FeatureFlags = unsigned;

  String Serialize() const;

  bool HasUnknown() const { return CollectFeatureFlags() & kFeatureUnknown; }

  virtual Type GetType() const = 0;
  virtual void SerializeTo(WTF::StringBuilder&) const = 0;
  virtual void CollectExpressions(HeapVector<MediaQueryExp>&) const = 0;
  virtual FeatureFlags CollectFeatureFlags() const = 0;

  // These helper functions return nullptr if any argument is nullptr.
  static const MediaQueryExpNode* Not(const MediaQueryExpNode*);
  static const MediaQueryExpNode* Nested(const MediaQueryExpNode*);
  static const MediaQueryExpNode* Function(const MediaQueryExpNode*,
                                           const AtomicString& name);
  static const MediaQueryExpNode* And(const MediaQueryExpNode*,
                                      const MediaQueryExpNode*);
  static const MediaQueryExpNode* Or(const MediaQueryExpNode*,
                                     const MediaQueryExpNode*);
};

class CORE_EXPORT MediaQueryFeatureExpNode : public MediaQueryExpNode {
 public:
  explicit MediaQueryFeatureExpNode(const MediaQueryExp& exp) : exp_(exp) {}
  void Trace(Visitor*) const override;

  const String& Name() const { return exp_.MediaFeature(); }
  const MediaQueryExpBounds& Bounds() const { return exp_.Bounds(); }

  unsigned GetUnitFlags() const;
  bool IsViewportDependent() const;
  bool IsDeviceDependent() const;
  bool IsWidthDependent() const;
  bool IsHeightDependent() const;
  bool IsInlineSizeDependent() const;
  bool IsBlockSizeDependent() const;

  Type GetType() const override { return Type::kFeature; }
  void SerializeTo(WTF::StringBuilder&) const override;
  void CollectExpressions(HeapVector<MediaQueryExp>&) const override;
  FeatureFlags CollectFeatureFlags() const override;

 private:
  MediaQueryExp exp_;
};

class CORE_EXPORT MediaQueryUnaryExpNode : public MediaQueryExpNode {
 public:
  explicit MediaQueryUnaryExpNode(const MediaQueryExpNode* operand)
      : operand_(operand) {
    DCHECK(operand_);
  }
  void Trace(Visitor*) const override;

  void CollectExpressions(HeapVector<MediaQueryExp>&) const override;
  FeatureFlags CollectFeatureFlags() const override;
  const MediaQueryExpNode& Operand() const { return *operand_; }

 private:
  Member<const MediaQueryExpNode> operand_;
};

class CORE_EXPORT MediaQueryNestedExpNode : public MediaQueryUnaryExpNode {
 public:
  explicit MediaQueryNestedExpNode(const MediaQueryExpNode* operand)
      : MediaQueryUnaryExpNode(operand) {}

  Type GetType() const override { return Type::kNested; }
  void SerializeTo(WTF::StringBuilder&) const override;
};

class CORE_EXPORT MediaQueryFunctionExpNode : public MediaQueryUnaryExpNode {
 public:
  explicit MediaQueryFunctionExpNode(const MediaQueryExpNode* operand,
                                     const AtomicString& name)
      : MediaQueryUnaryExpNode(operand), name_(name) {}

  Type GetType() const override { return Type::kFunction; }
  void SerializeTo(WTF::StringBuilder&) const override;
  FeatureFlags CollectFeatureFlags() const override;

 private:
  AtomicString name_;
};

class CORE_EXPORT MediaQueryNotExpNode : public MediaQueryUnaryExpNode {
 public:
  explicit MediaQueryNotExpNode(const MediaQueryExpNode* operand)
      : MediaQueryUnaryExpNode(operand) {}

  Type GetType() const override { return Type::kNot; }
  void SerializeTo(WTF::StringBuilder&) const override;
};

class CORE_EXPORT MediaQueryCompoundExpNode : public MediaQueryExpNode {
 public:
  MediaQueryCompoundExpNode(const MediaQueryExpNode* left,
                            const MediaQueryExpNode* right)
      : left_(left), right_(right) {
    DCHECK(left_);
    DCHECK(right_);
  }
  void Trace(Visitor*) const override;

  void CollectExpressions(HeapVector<MediaQueryExp>&) const override;
  FeatureFlags CollectFeatureFlags() const override;
  const MediaQueryExpNode& Left() const { return *left_; }
  const MediaQueryExpNode& Right() const { return *right_; }

 private:
  Member<const MediaQueryExpNode> left_;
  Member<const MediaQueryExpNode> right_;
};

class CORE_EXPORT MediaQueryAndExpNode : public MediaQueryCompoundExpNode {
 public:
  MediaQueryAndExpNode(const MediaQueryExpNode* left,
                       const MediaQueryExpNode* right)
      : MediaQueryCompoundExpNode(left, right) {}

  Type GetType() const override { return Type::kAnd; }
  void SerializeTo(WTF::StringBuilder&) const override;
};

class CORE_EXPORT MediaQueryOrExpNode : public MediaQueryCompoundExpNode {
 public:
  MediaQueryOrExpNode(const MediaQueryExpNode* left,
                      const MediaQueryExpNode* right)
      : MediaQueryCompoundExpNode(left, right) {}

  Type GetType() const override { return Type::kOr; }
  void SerializeTo(WTF::StringBuilder&) const override;
};

class CORE_EXPORT MediaQueryUnknownExpNode : public MediaQueryExpNode {
 public:
  explicit MediaQueryUnknownExpNode(String string) : string_(string) {}

  Type GetType() const override { return Type::kUnknown; }
  void SerializeTo(WTF::StringBuilder&) const override;
  void CollectExpressions(HeapVector<MediaQueryExp>&) const override;
  FeatureFlags CollectFeatureFlags() const override;

 private:
  String string_;
};

template <>
struct DowncastTraits<MediaQueryFeatureExpNode> {
  static bool AllowFrom(const MediaQueryExpNode& node) {
    return node.GetType() == MediaQueryExpNode::Type::kFeature;
  }
};

template <>
struct DowncastTraits<MediaQueryNestedExpNode> {
  static bool AllowFrom(const MediaQueryExpNode& node) {
    return node.GetType() == MediaQueryExpNode::Type::kNested;
  }
};

template <>
struct DowncastTraits<MediaQueryFunctionExpNode> {
  static bool AllowFrom(const MediaQueryExpNode& node) {
    return node.GetType() == MediaQueryExpNode::Type::kFunction;
  }
};

template <>
struct DowncastTraits<MediaQueryNotExpNode> {
  static bool AllowFrom(const MediaQueryExpNode& node) {
    return node.GetType() == MediaQueryExpNode::Type::kNot;
  }
};

template <>
struct DowncastTraits<MediaQueryAndExpNode> {
  static bool AllowFrom(const MediaQueryExpNode& node) {
    return node.GetType() == MediaQueryExpNode::Type::kAnd;
  }
};

template <>
struct DowncastTraits<MediaQueryOrExpNode> {
  static bool AllowFrom(const MediaQueryExpNode& node) {
    return node.GetType() == MediaQueryExpNode::Type::kOr;
  }
};

template <>
struct DowncastTraits<MediaQueryUnknownExpNode> {
  static bool AllowFrom(const MediaQueryExpNode& node) {
    return node.GetType() == MediaQueryExpNode::Type::kUnknown;
  }
=======
  String media_feature_;
  MediaQueryExpValue exp_value_;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_MEDIA_QUERY_EXP_H_
