// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CSS_VARIABLE_DATA_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CSS_VARIABLE_DATA_H_

#include "third_party/blink/renderer/core/css/parser/css_parser_token.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_token_range.h"
#include "third_party/blink/renderer/core/css/parser/css_tokenized_value.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/wtf/forward.h"
#include "third_party/blink/renderer/platform/wtf/text/text_encoding.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

class CSSSyntaxDefinition;
enum class SecureContextMode;

class CORE_EXPORT CSSVariableData : public RefCounted<CSSVariableData> {
  USING_FAST_MALLOC(CSSVariableData);

 public:
<<<<<<< HEAD
  CSSVariableData()
      : length_(0),
        is_animation_tainted_(false),
        is_attr_tainted_(false),
        needs_variable_resolution_(false),
        is_8bit_(true),
        has_font_units_(false),
        has_root_font_units_(false),
        has_line_height_units_(false) {}

  using PassKey = base::PassKey<CSSVariableData>;
  CSSVariableData(PassKey,
                  StringView,
                  bool is_animation_tainted,
                  bool is_attr_tainted,
                  bool needs_variable_resolution,
                  bool has_font_units,
                  bool has_root_font_units,
                  bool has_line_height_units);

  // This is the fastest (non-trivial) constructor if you've got the has_* data
  // already, e.g. because you extracted them while tokenizing (see
  // ExtractFeatures()) or got them from another CSSVariableData instance during
  // substitution.
  static CSSVariableData* Create(StringView original_text,
                                 bool is_animation_tainted,
                                 bool is_attr_tainted,
                                 bool needs_variable_resolution,
                                 bool has_font_units,
                                 bool has_root_font_units,
                                 bool has_line_height_units) {
    if (original_text.length() > kMaxVariableBytes) {
      // This should have been blocked off during variable substitution.
      NOTREACHED();
    }

    return MakeGarbageCollected<CSSVariableData>(
        AdditionalBytes(original_text.Is8Bit() ? original_text.length()
                                               : 2 * original_text.length()),
        PassKey(), original_text, is_animation_tainted, is_attr_tainted,
        needs_variable_resolution, has_font_units, has_root_font_units,
        has_line_height_units);
  }

  // This tokenizes the string to determine the has_* data.
  // (The tokens are not used apart from that; only the original string is
  // stored.)
  static CSSVariableData* Create(const String& original_text,
                                 bool is_animation_tainted,
                                 bool is_attr_tainted,
                                 bool needs_variable_resolution);

  void Trace(Visitor*) const {}

  StringView OriginalText() const {
    // SAFETY: See AdditionalBytes() in Create().
    if (is_8bit_) {
      return StringView(UNSAFE_BUFFERS(
          base::span(reinterpret_cast<const LChar*>(this + 1), length_)));
    } else {
      return StringView(UNSAFE_BUFFERS(
          base::span(reinterpret_cast<const UChar*>(this + 1), length_)));
    }
=======
  static scoped_refptr<CSSVariableData> Create() {
    return base::AdoptRef(new CSSVariableData());
  }
  static scoped_refptr<CSSVariableData> Create(
      const CSSTokenizedValue& tokenized_value,
      bool is_animation_tainted,
      bool needs_variable_resolution,
      const KURL& base_url,
      const WTF::TextEncoding& charset) {
    return base::AdoptRef(
        new CSSVariableData(tokenized_value, is_animation_tainted,
                            needs_variable_resolution, base_url, charset));
  }

  static scoped_refptr<CSSVariableData> CreateResolved(
      Vector<CSSParserToken> resolved_tokens,
      Vector<String> backing_strings,
      bool is_animation_tainted,
      bool has_font_units,
      bool has_root_font_units,
      const String& base_url,
      const WTF::TextEncoding& charset) {
    return base::AdoptRef(new CSSVariableData(
        std::move(resolved_tokens), std::move(backing_strings),
        is_animation_tainted, has_font_units, has_root_font_units, base_url,
        charset));
>>>>>>> chromium
  }

  CSSParserTokenRange TokenRange() const { return tokens_; }

  const Vector<CSSParserToken>& Tokens() const { return tokens_; }
  const Vector<String>& BackingStrings() const { return backing_strings_; }
  String Serialize() const;

  bool EqualsIgnoringAttrTainting(const CSSVariableData& other) const;

  bool operator==(const CSSVariableData& other) const;

  bool IsAnimationTainted() const { return is_animation_tainted_; }

  bool IsAttrTainted() const { return is_attr_tainted_; }

  bool NeedsVariableResolution() const { return needs_variable_resolution_; }

  // True if the CSSVariableData has tokens with units that are relative to the
  // font-size of the current element, e.g. 'em'.
  bool HasFontUnits() const { return has_font_units_; }

  // True if the CSSVariableData has tokens with units that are relative to the
  // font-size of the root element, e.g. 'rem'.
  bool HasRootFontUnits() const { return has_root_font_units_; }

  const String& BaseURL() const { return base_url_; }

  const WTF::TextEncoding& Charset() const { return charset_; }

  const CSSValue* ParseForSyntax(const CSSSyntaxDefinition&,
                                 SecureContextMode) const;

 private:
  CSSVariableData() = default;

  CSSVariableData(const CSSTokenizedValue&,
                  bool is_animation_tainted,
                  bool needs_variable_resolution,
                  const KURL& base_url,
                  const WTF::TextEncoding& charset);

  CSSVariableData(Vector<CSSParserToken> resolved_tokens,
                  Vector<String> backing_strings,
                  bool is_animation_tainted,
                  bool has_font_units,
                  bool has_root_font_units,
                  const String& base_url,
                  const WTF::TextEncoding& charset)
      : backing_strings_(std::move(backing_strings)),
        tokens_(std::move(resolved_tokens)),
        is_animation_tainted_(is_animation_tainted),
        has_font_units_(has_font_units),
        has_root_font_units_(has_root_font_units),
        base_url_(base_url),
        charset_(charset) {}
  CSSVariableData(const CSSVariableData&) = delete;
  CSSVariableData& operator=(const CSSVariableData&) = delete;

  void ConsumeAndUpdateTokens(const CSSParserTokenRange&);

<<<<<<< HEAD
  // The maximum number of bytes for a CSS variable (including text
  // that comes from var() substitution). This matches Firefox.
  //
  // If you change this, length_ below may need updates.
  //
  // https://drafts.csswg.org/css-variables/#long-variables
  static const size_t kMaxVariableBytes = 2097152;

 private:
  // We'd like to use bool for the booleans, but this causes the struct to
  // balloon in size on Windows:
  // https://randomascii.wordpress.com/2010/06/06/bit-field-packing-with-visual-c/

  // Enough for storing up to 2MB (and then some), cf. kMaxSubstitutionBytes.
  // The remaining 3 bits are kept in reserve for future use.
  const unsigned length_ : 22;
  const unsigned is_animation_tainted_ : 1;       // bool.
  const unsigned is_attr_tainted_ : 1;            // bool.
  const unsigned needs_variable_resolution_ : 1;  // bool.
  const unsigned is_8bit_ : 1;                    // bool.
  unsigned has_font_units_ : 1;                   // bool.
  unsigned has_root_font_units_ : 1;              // bool.
  unsigned has_line_height_units_ : 1;            // bool.
  unsigned /* unused_ */ : 3;

  // The actual character data is stored after this.
=======
  // tokens_ may have raw pointers to string data, we store the String objects
  // owning that data in backing_strings_ to keep it alive alongside the
  // tokens_.
  Vector<String> backing_strings_;
  Vector<CSSParserToken> tokens_;
  String original_text_;
  const bool is_animation_tainted_ = false;
  const bool needs_variable_resolution_ = false;
  bool has_font_units_ = false;
  bool has_root_font_units_ = false;
  String base_url_;
  WTF::TextEncoding charset_;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_CSS_VARIABLE_DATA_H_
