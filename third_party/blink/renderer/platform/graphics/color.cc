/*
 * Copyright (C) 2003, 2004, 2005, 2006, 2008 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
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

#include "third_party/blink/renderer/platform/graphics/color.h"

#include "build/build_config.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/decimal.h"
#include "third_party/blink/renderer/platform/wtf/dtoa.h"
#include "third_party/blink/renderer/platform/wtf/math_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"
#include "third_party/blink/renderer/platform/wtf/text/string_view.h"
#include "third_party/skia/include/core/SkColor.h"

namespace blink {

// VS 2015 and above allow these definitions and in this case require them
#if !defined(COMPILER_MSVC) || _MSC_VER >= 1900
// FIXME: Use C++11 enum classes to avoid static data member initializer
// definition problems.
const RGBA32 Color::kBlack;
const RGBA32 Color::kWhite;
const RGBA32 Color::kDarkGray;
const RGBA32 Color::kGray;
const RGBA32 Color::kLightGray;
const RGBA32 Color::kTransparent;
#endif

namespace {

const RGBA32 kLightenedBlack = 0xFF545454;
const RGBA32 kDarkenedWhite = 0xFFABABAB;
<<<<<<< HEAD
// For lch/oklch colors, the value of chroma underneath which the color is
// considered to be "achromatic", relevant for color conversions.
// https://www.w3.org/TR/css-color-4/#lab-to-lch
// This is set to be slightly higher than white's chroma value of 0.0188.
const float kAchromaticChromaThreshold = 0.02;
=======
>>>>>>> chromium

const int kCStartAlpha = 153;     // 60%
const int kCEndAlpha = 204;       // 80%;
const int kCAlphaIncrement = 17;  // Increments in between.

int BlendComponent(int c, int a) {
  // We use white.
  float alpha = a / 255.0f;
  int white_blend = 255 - a;
  c -= white_blend;
  return static_cast<int>(c / alpha);
}

double CalcHue(double temp1, double temp2, double hue_val) {
  if (hue_val < 0.0)
    hue_val += 6.0;
  else if (hue_val >= 6.0)
    hue_val -= 6.0;
  if (hue_val < 1.0)
    return temp1 + (temp2 - temp1) * hue_val;
  if (hue_val < 3.0)
    return temp2;
  if (hue_val < 4.0)
    return temp1 + (temp2 - temp1) * (4.0 - hue_val);
  return temp1;
}

int ColorFloatToRGBAByte(float f) {
  return clampTo(static_cast<int>(lroundf(255.0f * f)), 0, 255);
}

// originally moved here from the CSS parser
template <typename CharacterType>
inline bool ParseHexColorInternal(const CharacterType* name,
                                  unsigned length,
                                  RGBA32& rgb) {
  if (length != 3 && length != 4 && length != 6 && length != 8)
    return false;
  if ((length == 8 || length == 4) &&
      !RuntimeEnabledFeatures::CSSHexAlphaColorEnabled())
    return false;
  unsigned value = 0;
  for (unsigned i = 0; i < length; ++i) {
    if (!IsASCIIHexDigit(name[i]))
      return false;
    value <<= 4;
    value |= ToASCIIHexValue(name[i]);
  }
  if (length == 6) {
    rgb = 0xFF000000 | value;
    return true;
  }
  if (length == 8) {
    // We parsed the values into RGBA order, but the RGBA32 type
    // expects them to be in ARGB order, so we right rotate eight bits.
    rgb = value << 24 | value >> 8;
    return true;
  }
  if (length == 4) {
    // #abcd converts to ddaabbcc in RGBA32.
    rgb = (value & 0xF) << 28 | (value & 0xF) << 24 | (value & 0xF000) << 8 |
          (value & 0xF000) << 4 | (value & 0xF00) << 4 | (value & 0xF00) |
          (value & 0xF0) | (value & 0xF0) >> 4;
    return true;
  }
  // #abc converts to #aabbcc
  rgb = 0xFF000000 | (value & 0xF00) << 12 | (value & 0xF00) << 8 |
        (value & 0xF0) << 8 | (value & 0xF0) << 4 | (value & 0xF) << 4 |
        (value & 0xF);
  return true;
}

inline const NamedColor* FindNamedColor(const String& name) {
  char buffer[64];  // easily big enough for the longest color name
  unsigned length = name.length();
  if (length > sizeof(buffer) - 1)
    return nullptr;
  for (unsigned i = 0; i < length; ++i) {
    UChar c = name[i];
    if (!c || c > 0x7F)
      return nullptr;
    buffer[i] = ToASCIILower(static_cast<char>(c));
  }
  buffer[length] = '\0';
  return FindColor(buffer, length);
}

}  // namespace

RGBA32 MakeRGB(int r, int g, int b) {
  return 0xFF000000 | clampTo(r, 0, 255) << 16 | clampTo(g, 0, 255) << 8 |
         clampTo(b, 0, 255);
}

RGBA32 MakeRGBA(int r, int g, int b, int a) {
  return clampTo(a, 0, 255) << 24 | clampTo(r, 0, 255) << 16 |
         clampTo(g, 0, 255) << 8 | clampTo(b, 0, 255);
}

RGBA32 MakeRGBA32FromFloats(float r, float g, float b, float a) {
  return ColorFloatToRGBAByte(a) << 24 | ColorFloatToRGBAByte(r) << 16 |
         ColorFloatToRGBAByte(g) << 8 | ColorFloatToRGBAByte(b);
}

// Explanation of this algorithm can be found in the CSS Color 4 Module
// specification at https://drafts.csswg.org/css-color-4/#hsl-to-rgb with
// further explanation available at http://en.wikipedia.org/wiki/HSL_color_space

// Hue is in the range of 0 to 6.0, the remainder are in the range 0 to 1.0
RGBA32 MakeRGBAFromHSLA(double hue,
                        double saturation,
                        double lightness,
                        double alpha) {
  const double scale_factor = 255.0;

  if (!saturation) {
    int grey_value = static_cast<int>(round(lightness * scale_factor));
    return MakeRGBA(grey_value, grey_value, grey_value,
                    static_cast<int>(round(alpha * scale_factor)));
  }

  double temp2 = lightness <= 0.5
                     ? lightness * (1.0 + saturation)
                     : lightness + saturation - lightness * saturation;
  double temp1 = 2.0 * lightness - temp2;

  return MakeRGBA(
      static_cast<int>(round(CalcHue(temp1, temp2, hue + 2.0) * scale_factor)),
      static_cast<int>(round(CalcHue(temp1, temp2, hue) * scale_factor)),
      static_cast<int>(round(CalcHue(temp1, temp2, hue - 2.0) * scale_factor)),
      static_cast<int>(round(alpha * scale_factor)));
}

RGBA32 MakeRGBAFromCMYKA(float c, float m, float y, float k, float a) {
  double colors = 1 - k;
  int r = static_cast<int>(nextafter(256, 0) * (colors * (1 - c)));
  int g = static_cast<int>(nextafter(256, 0) * (colors * (1 - m)));
  int b = static_cast<int>(nextafter(256, 0) * (colors * (1 - y)));
  return MakeRGBA(r, g, b, static_cast<float>(nextafter(256, 0) * a));
}

bool Color::ParseHexColor(const LChar* name, unsigned length, RGBA32& rgb) {
  return ParseHexColorInternal(name, length, rgb);
}

bool Color::ParseHexColor(const UChar* name, unsigned length, RGBA32& rgb) {
  return ParseHexColorInternal(name, length, rgb);
}

bool Color::ParseHexColor(const StringView& name, RGBA32& rgb) {
  if (name.IsEmpty())
    return false;
<<<<<<< HEAD
  }

  if (color1.param0_is_none_ && !color2.param0_is_none_) {
    color1.param0_ = color2.param0_;
    color1.param0_is_none_ = false;
  } else if (color2.param0_is_none_ && !color1.param0_is_none_) {
    color2.param0_ = color1.param0_;
    color2.param0_is_none_ = false;
  }

  if (color1.param1_is_none_ && !color2.param1_is_none_) {
    color1.param1_ = color2.param1_;
    color1.param1_is_none_ = false;
  } else if (color2.param1_is_none_ && !color1.param1_is_none_) {
    color2.param1_ = color1.param1_;
    color2.param1_is_none_ = false;
  }

  if (color1.param2_is_none_ && !color2.param2_is_none_) {
    color1.param2_ = color2.param2_;
    color1.param2_is_none_ = false;
  } else if (color2.param2_is_none_ && !color1.param2_is_none_) {
    color2.param2_ = color1.param2_;
    color2.param2_is_none_ = false;
  }

  if (color1.alpha_is_none_ && !color2.alpha_is_none_) {
    color1.alpha_ = color2.alpha_;
    color1.alpha_is_none_ = false;
  } else if (color2.alpha_is_none_ && !color1.alpha_is_none_) {
    color2.alpha_ = color1.alpha_;
    color2.alpha_is_none_ = false;
  }

  return true;
}

// static
Color Color::InterpolateColors(Color::ColorSpace interpolation_space,
                               std::optional<HueInterpolationMethod> hue_method,
                               Color color1,
                               Color color2,
                               float percentage) {
  // https://www.w3.org/TR/css-color-4/#missing:
  // When interpolating colors, missing components do not behave as zero values
  // for color space conversions.
  const auto color1_prev_color_space = color1.GetColorSpace();
  color1.ConvertToColorSpace(interpolation_space,
                             false /* resolve_missing_components */);
  const auto color2_prev_color_space = color2.GetColorSpace();
  color2.ConvertToColorSpace(interpolation_space,
                             false /* resolve_missing_components */);

  CarryForwardAnalogousMissingComponents(color1, color1_prev_color_space);
  CarryForwardAnalogousMissingComponents(color2, color2_prev_color_space);

  if (!SubstituteMissingParameters(color1, color2)) {
    NOTREACHED();
  }

  float alpha1 = color1.PremultiplyColor();
  float alpha2 = color2.PremultiplyColor();

  if (!hue_method.has_value()) {
    // https://www.w3.org/TR/css-color-4/#hue-interpolation
    // Unless otherwise specified, if no specific hue interpolation algorithm
    // is selected by the host syntax, the default is shorter.
    hue_method = HueInterpolationMethod::kShorter;
  }

  std::optional<float> param0 =
      (color1.param0_is_none_ && color2.param0_is_none_)
          ? std::optional<float>(std::nullopt)
      : (interpolation_space == ColorSpace::kHSL ||
         interpolation_space == ColorSpace::kHWB)
          ? HueInterpolation(color1.param0_, color2.param0_, percentage,
                             hue_method.value())
          : blink::Blend(color1.param0_, color2.param0_, percentage);

  std::optional<float> param1 =
      (color1.param1_is_none_ && color2.param1_is_none_)
          ? std::optional<float>(std::nullopt)
          : blink::Blend(color1.param1_, color2.param1_, percentage);

  std::optional<float> param2 =
      (color1.param2_is_none_ && color2.param2_is_none_)
          ? std::optional<float>(std::nullopt)
      : (IsChromaSecondComponent(interpolation_space))
          ? HueInterpolation(color1.param2_, color2.param2_, percentage,
                             hue_method.value())
          : blink::Blend(color1.param2_, color2.param2_, percentage);

  std::optional<float> alpha = (color1.alpha_is_none_ && color2.alpha_is_none_)
                                   ? std::optional<float>(std::nullopt)
                                   : blink::Blend(alpha1, alpha2, percentage);

  Color result =
      FromColorSpace(interpolation_space, param0, param1, param2, alpha);

  result.UnpremultiplyColor();

  return result;
}

std::tuple<float, float, float> Color::ExportAsXYZD50Floats() const {
  switch (color_space_) {
    case ColorSpace::kSRGBLegacy: {
      auto [r, g, b] = gfx::SRGBLegacyToSRGB(param0_, param1_, param2_);
      return gfx::SRGBToXYZD50(r, g, b);
    }
    case ColorSpace::kSRGB:
      return gfx::SRGBToXYZD50(param0_, param1_, param2_);
    case ColorSpace::kSRGBLinear:
      return gfx::SRGBLinearToXYZD50(param0_, param1_, param2_);
    case ColorSpace::kDisplayP3:
      return gfx::DisplayP3ToXYZD50(param0_, param1_, param2_);
    case ColorSpace::kA98RGB:
      return gfx::AdobeRGBToXYZD50(param0_, param1_, param2_);
    case ColorSpace::kProPhotoRGB:
      return gfx::ProPhotoToXYZD50(param0_, param1_, param2_);
    case ColorSpace::kRec2020:
      return gfx::Rec2020ToXYZD50(param0_, param1_, param2_);
    case ColorSpace::kXYZD50:
      return {param0_, param1_, param2_};
    case ColorSpace::kXYZD65:
      return gfx::XYZD65ToD50(param0_, param1_, param2_);
    case ColorSpace::kLab:
      return gfx::LabToXYZD50(param0_, param1_, param2_);
    case ColorSpace::kOklab: {
      auto [x, y, z] = gfx::OklabToXYZD65(param0_, param1_, param2_);
      return gfx::XYZD65ToD50(x, y, z);
    }
    case ColorSpace::kLch: {
      auto [l, a, b] = gfx::LchToLab(param0_, param1_, param2_);
      return gfx::LabToXYZD50(l, a, b);
    }
    case ColorSpace::kOklch: {
      auto [l, a, b] = gfx::LchToLab(param0_, param1_, param2_);
      auto [x, y, z] = gfx::OklabToXYZD65(l, a, b);
      return gfx::XYZD65ToD50(x, y, z);
    }
    case ColorSpace::kHSL: {
      auto [r, g, b] = gfx::HSLToSRGB(param0_, param1_, param2_);
      return gfx::SRGBToXYZD50(r, g, b);
    }
    case ColorSpace::kHWB: {
      auto [r, g, b] = gfx::HWBToSRGB(param0_, param1_, param2_);
      return gfx::SRGBToXYZD50(r, g, b);
    }
    case ColorSpace::kNone:
      NOTREACHED();
  }
}

// https://www.w3.org/TR/css-color-4/#missing:
// "[Except for interpolations] a missing component behaves as a zero value, in
// the appropriate unit for that component: 0, 0%, or 0deg. This includes
// rendering the color directly, converting it to another color space,
// performing computations on the color component values, etc."
// So we simply turn "none"s into zeros here. Note that this does not happen for
// interpolations.
void Color::ResolveMissingComponents() {
  if (param0_is_none_) {
    param0_ = 0;
    param0_is_none_ = false;
  }
  if (param1_is_none_) {
    param1_ = 0;
    param1_is_none_ = false;
  }
  if (param2_is_none_) {
    param2_ = 0;
    param2_is_none_ = false;
  }
}

void Color::ConvertToColorSpace(ColorSpace destination_color_space,
                                bool resolve_missing_components) {
  if (color_space_ == destination_color_space) {
    return;
  }

  if (resolve_missing_components) {
    ResolveMissingComponents();
  }

  switch (destination_color_space) {
    case ColorSpace::kXYZD65: {
      if (color_space_ == ColorSpace::kOklab) {
        std::tie(param0_, param1_, param2_) =
            gfx::OklabToXYZD65(param0_, param1_, param2_);
      } else {
        auto [x, y, z] = ExportAsXYZD50Floats();
        std::tie(param0_, param1_, param2_) = gfx::XYZD50ToD65(x, y, z);
      }
      color_space_ = ColorSpace::kXYZD65;
      return;
    }
    case ColorSpace::kXYZD50: {
      std::tie(param0_, param1_, param2_) = ExportAsXYZD50Floats();
      color_space_ = ColorSpace::kXYZD50;
      return;
    }
    case ColorSpace::kSRGBLinear: {
      auto [x, y, z] = ExportAsXYZD50Floats();
      std::tie(param0_, param1_, param2_) = gfx::XYZD50TosRGBLinear(x, y, z);
      color_space_ = ColorSpace::kSRGBLinear;
      return;
    }
    case ColorSpace::kDisplayP3: {
      auto [x, y, z] = ExportAsXYZD50Floats();
      std::tie(param0_, param1_, param2_) = gfx::XYZD50ToDisplayP3(x, y, z);
      color_space_ = ColorSpace::kDisplayP3;
      return;
    }
    case ColorSpace::kA98RGB: {
      auto [x, y, z] = ExportAsXYZD50Floats();
      std::tie(param0_, param1_, param2_) = gfx::XYZD50ToAdobeRGB(x, y, z);
      color_space_ = ColorSpace::kA98RGB;
      return;
    }
    case ColorSpace::kProPhotoRGB: {
      auto [x, y, z] = ExportAsXYZD50Floats();
      std::tie(param0_, param1_, param2_) = gfx::XYZD50ToProPhoto(x, y, z);
      color_space_ = ColorSpace::kProPhotoRGB;
      return;
    }
    case ColorSpace::kRec2020: {
      auto [x, y, z] = ExportAsXYZD50Floats();
      std::tie(param0_, param1_, param2_) = gfx::XYZD50ToRec2020(x, y, z);
      color_space_ = ColorSpace::kRec2020;
      return;
    }
    case ColorSpace::kLab: {
      if (color_space_ == ColorSpace::kLch) {
        std::tie(param0_, param1_, param2_) =
            gfx::LchToLab(param0_, param1_, param2_);
      } else {
        auto [x, y, z] = ExportAsXYZD50Floats();
        std::tie(param0_, param1_, param2_) = gfx::XYZD50ToLab(x, y, z);
      }
      color_space_ = ColorSpace::kLab;
      return;
    }
    case ColorSpace::kOklab:
    // As per CSS Color 4 Spec, "If the host syntax does not define what color
    // space interpolation should take place in, it defaults to OKLab".
    // (https://www.w3.org/TR/css-color-4/#interpolation-space)
    case ColorSpace::kNone: {
      if (color_space_ == ColorSpace::kOklab) {
        return;
      }
      if (color_space_ == ColorSpace::kOklch) {
        std::tie(param0_, param1_, param2_) =
            gfx::LchToLab(param0_, param1_, param2_);
        color_space_ = ColorSpace::kOklab;
        return;
      }
      // Conversion to Oklab is done through XYZD65.
      auto [xd65, yd65, zd65] = [&]() {
        if (color_space_ == ColorSpace::kXYZD65) {
          return std::make_tuple(param0_, param1_, param2_);
        } else {
          auto [xd50, yd50, zd50] = ExportAsXYZD50Floats();
          return gfx::XYZD50ToD65(xd50, yd50, zd50);
        }
      }();

      std::tie(param0_, param1_, param2_) =
          gfx::XYZD65ToOklab(xd65, yd65, zd65);
      color_space_ = ColorSpace::kOklab;
      return;
    }
    case ColorSpace::kLch: {
      // Conversion to lch is done through lab.
      // https://www.w3.org/TR/css-color-4/#lab-to-lch
      auto [l, a, b] = [&]() {
        if (color_space_ == ColorSpace::kLab) {
          return std::make_tuple(param0_, param1_, param2_);
        } else {
          auto [xd50, yd50, zd50] = ExportAsXYZD50Floats();
          return gfx::XYZD50ToLab(xd50, yd50, zd50);
        }
      }();

      std::tie(param0_, param1_, param2_) = gfx::LabToLch(l, a, b);
      param2_ = AngleToUnitCircleDegrees(param2_);

      // Hue component is powerless for fully transparent or achromatic colors.
      if (IsFullyTransparent() || param1_ <= kAchromaticChromaThreshold) {
        param2_is_none_ = true;
      }

      color_space_ = ColorSpace::kLch;
      return;
    }
    case ColorSpace::kOklch: {
      if (color_space_ == ColorSpace::kOklab) {
        std::tie(param0_, param1_, param2_) =
            gfx::LabToLch(param0_, param1_, param2_);
      } else {
        // Conversion to Oklch is done through XYZD65.
        auto [xd65, yd65, zd65] = [&]() {
          if (color_space_ == ColorSpace::kXYZD65) {
            return std::make_tuple(param0_, param1_, param2_);
          } else {
            auto [xd50, yd50, zd50] = ExportAsXYZD50Floats();
            return gfx::XYZD50ToD65(xd50, yd50, zd50);
          }
        }();

        auto [l, a, b] = gfx::XYZD65ToOklab(xd65, yd65, zd65);
        std::tie(param0_, param1_, param2_) = gfx::LabToLch(l, a, b);
        param2_ = AngleToUnitCircleDegrees(param2_);
      }

      // Hue component is powerless for fully transparent or archromatic colors.
      if (IsFullyTransparent() || param1_ <= kAchromaticChromaThreshold) {
        param2_is_none_ = true;
      }

      color_space_ = ColorSpace::kOklch;
      return;
    }
    case ColorSpace::kSRGB:
    case ColorSpace::kSRGBLegacy: {
      if (color_space_ == ColorSpace::kHSL) {
        std::tie(param0_, param1_, param2_) =
            gfx::HSLToSRGB(param0_, param1_, param2_);
      } else if (color_space_ == ColorSpace::kHWB) {
        std::tie(param0_, param1_, param2_) =
            gfx::HWBToSRGB(param0_, param1_, param2_);
      } else if (color_space_ == ColorSpace::kSRGBLegacy) {
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBLegacyToSRGB(param0_, param1_, param2_);
      } else if (color_space_ != ColorSpace::kSRGB) {
        // Don't go through the whole conversion to xyz for srgb to avoid
        // rounding issues.
        auto [x, y, z] = ExportAsXYZD50Floats();
        std::tie(param0_, param1_, param2_) = gfx::XYZD50TosRGB(x, y, z);
      }

      // All the above conversions result in non-legacy srgb.
      if (destination_color_space == ColorSpace::kSRGBLegacy) {
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBToSRGBLegacy(param0_, param1_, param2_);
      }

      color_space_ = destination_color_space;
      return;
    }
    case ColorSpace::kHSL: {
      if (color_space_ == ColorSpace::kSRGBLegacy) {
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBLegacyToSRGB(param0_, param1_, param2_);
      }
      if (color_space_ == ColorSpace::kSRGB ||
          color_space_ == ColorSpace::kSRGBLegacy) {
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBToHSL(param0_, param1_, param2_);
      } else if (color_space_ == ColorSpace::kHWB) {
        std::tie(param0_, param1_, param2_) =
            gfx::HWBToSRGB(param0_, param1_, param2_);
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBToHSL(param0_, param1_, param2_);
      } else {
        auto [x, y, z] = ExportAsXYZD50Floats();
        std::tie(param0_, param1_, param2_) = gfx::XYZD50TosRGB(x, y, z);
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBToHSL(param0_, param1_, param2_);
      }

      // Hue component is powerless for fully transparent or achromatic (s==0)
      // colors.
      if (IsFullyTransparent() || param1_ == 0) {
        param0_is_none_ = true;
      }

      color_space_ = ColorSpace::kHSL;
      return;
    }
    case ColorSpace::kHWB: {
      if (color_space_ == ColorSpace::kSRGBLegacy) {
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBLegacyToSRGB(param0_, param1_, param2_);
      }
      if (color_space_ == ColorSpace::kSRGB ||
          color_space_ == ColorSpace::kSRGBLegacy) {
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBToHWB(param0_, param1_, param2_);
      } else if (color_space_ == ColorSpace::kHSL) {
        std::tie(param0_, param1_, param2_) =
            gfx::HSLToSRGB(param0_, param1_, param2_);
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBToHWB(param0_, param1_, param2_);
      } else {
        auto [x, y, z] = ExportAsXYZD50Floats();
        std::tie(param0_, param1_, param2_) = gfx::XYZD50TosRGB(x, y, z);
        std::tie(param0_, param1_, param2_) =
            gfx::SRGBToHWB(param0_, param1_, param2_);
      }

      // Hue component is powerless for fully transparent or achromatic colors.
      if (IsFullyTransparent() || param1_ + param2_ >= 1) {
        param0_is_none_ = true;
      }

      color_space_ = ColorSpace::kHWB;
      return;
    }
  }
}

SkColor4f Color::toSkColor4f() const {
  return ToSkColor4fInternal(IsBakedGamutMappingEnabled());
}

SkColor4f
Color::ToGradientStopSkColor4f(ColorSpace interpolation_space) const {
  // Do not apply gamut mapping to gradient stops. Skia will perform
  // gamut mapping on a per-pixel basis internally.
  return ToSkColor4fInternal(/*gamut_map_oklab_oklch=*/false);
}

// static
bool Color::IsBakedGamutMappingEnabled() {
  static bool enabled =
      base::FeatureList::IsEnabled(blink::features::kBakedGamutMapping);
  return enabled;
}

SkColor4f Color::ToSkColor4fInternal(bool gamut_map_oklab_oklch) const {
  switch (color_space_) {
    case ColorSpace::kSRGB:
      return SkColor4f{param0_, param1_, param2_, alpha_};
    case ColorSpace::kSRGBLegacy: {
      auto [r, g, b] = gfx::SRGBLegacyToSRGB(param0_, param1_, param2_);
      return SkColor4f{r, g, b, alpha_};
    }
    case ColorSpace::kSRGBLinear:
      return gfx::SRGBLinearToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kDisplayP3:
      return gfx::DisplayP3ToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kA98RGB:
      return gfx::AdobeRGBToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kProPhotoRGB:
      return gfx::ProPhotoToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kRec2020:
      return gfx::Rec2020ToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kXYZD50:
      return gfx::XYZD50ToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kXYZD65:
      return gfx::XYZD65ToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kLab:
      return gfx::LabToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kOklab:
      if (gamut_map_oklab_oklch) {
        return gfx::OklabGamutMapToSkColor4f(param0_, param1_, param2_, alpha_);
      } else {
        return gfx::OklabToSkColor4f(param0_, param1_, param2_, alpha_);
      }
    case ColorSpace::kLch:
      return gfx::LchToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kOklch:
      if (gamut_map_oklab_oklch) {
        return gfx::OklchGamutMapToSkColor4f(param0_, param1_, param2_, alpha_);
      } else {
        return gfx::OklchToSkColor4f(param0_, param1_, param2_, alpha_);
      }
    case ColorSpace::kHSL:
      return gfx::HSLToSkColor4f(param0_, param1_, param2_, alpha_);
    case ColorSpace::kHWB:
      return gfx::HWBToSkColor4f(param0_, param1_, param2_, alpha_);
    default:
      NOTIMPLEMENTED();
      return SkColor4f{0.f, 0.f, 0.f, 0.f};
  }
}

float Color::PremultiplyColor() {
  // By the spec (https://www.w3.org/TR/css-color-4/#interpolation) Hue values
  // are not premultiplied, and if alpha is none, the color premultiplied value
  // is the same as unpremultiplied.
  if (alpha_is_none_)
    return alpha_;
  float alpha = alpha_;
  if (color_space_ != ColorSpace::kHSL && color_space_ != ColorSpace::kHWB)
    param0_ = param0_ * alpha_;
  param1_ = param1_ * alpha_;
  if (!IsChromaSecondComponent(color_space_)) {
    param2_ = param2_ * alpha_;
  }
  alpha_ = 1.0f;
  return alpha;
}

void Color::UnpremultiplyColor() {
  // By the spec (https://www.w3.org/TR/css-color-4/#interpolation) Hue values
  // are not premultiplied, and if alpha is none, the color premultiplied value
  // is the same as unpremultiplied.
  if (alpha_is_none_ || alpha_ == 0.0f)
    return;

  if (color_space_ != ColorSpace::kHSL && color_space_ != ColorSpace::kHWB)
    param0_ = param0_ / alpha_;
  param1_ = param1_ / alpha_;
  if (!IsChromaSecondComponent(color_space_)) {
    param2_ = param2_ / alpha_;
  }
}

unsigned Color::GetHash() const {
  unsigned result = WTF::HashInt(static_cast<uint8_t>(color_space_));
  WTF::AddFloatToHash(result, param0_);
  WTF::AddFloatToHash(result, param1_);
  WTF::AddFloatToHash(result, param2_);
  WTF::AddFloatToHash(result, alpha_);
  WTF::AddIntToHash(result, param0_is_none_);
  WTF::AddIntToHash(result, param1_is_none_);
  WTF::AddIntToHash(result, param2_is_none_);
  WTF::AddIntToHash(result, alpha_is_none_);
  return result;
}

int Color::Red() const {
  return RedChannel(Rgb());
}
int Color::Green() const {
  return GreenChannel(Rgb());
}
int Color::Blue() const {
  return BlueChannel(Rgb());
}

RGBA32 Color::Rgb() const {
  return toSkColor4f().toSkColor();
}

bool Color::ParseHexColor(base::span<const LChar> name, Color& color) {
  return ParseHexColorInternal(name, color);
}

bool Color::ParseHexColor(base::span<const UChar> name, Color& color) {
  return ParseHexColorInternal(name, color);
}

bool Color::ParseHexColor(const StringView& name, Color& color) {
  if (name.empty())
    return false;
  return VisitCharacters(name, [&color](auto chars) {
    return ParseHexColorInternal(chars, color);
  });
=======
  if (name.Is8Bit())
    return ParseHexColor(name.Characters8(), name.length(), rgb);
  return ParseHexColor(name.Characters16(), name.length(), rgb);
>>>>>>> chromium
}

int DifferenceSquared(const Color& c1, const Color& c2) {
  int d_r = c1.Red() - c2.Red();
  int d_g = c1.Green() - c2.Green();
  int d_b = c1.Blue() - c2.Blue();
  return d_r * d_r + d_g * d_g + d_b * d_b;
}

bool Color::SetFromString(const String& name) {
  if (name[0] != '#')
    return SetNamedColor(name);
<<<<<<< HEAD
  return VisitCharacters(name, [this](auto chars) {
    return ParseHexColorInternal(chars.template subspan<1>(), *this);
  });
=======
  if (name.Is8Bit())
    return ParseHexColor(name.Characters8() + 1, name.length() - 1, color_);
  return ParseHexColor(name.Characters16() + 1, name.length() - 1, color_);
>>>>>>> chromium
}

String Color::Serialized() const {
  if (!HasAlpha())
    return String::Format("#%02x%02x%02x", Red(), Green(), Blue());

  StringBuilder result;
  result.ReserveCapacity(28);

  result.Append("rgba(");
  result.AppendNumber(Red());
  result.Append(", ");
  result.AppendNumber(Green());
  result.Append(", ");
  result.AppendNumber(Blue());
  result.Append(", ");

  if (!Alpha())
    result.Append('0');
  else {
    result.Append(Decimal::FromDouble(Alpha() / 255.0).ToString());
  }

  result.Append(')');
  return result.ToString();
}

String Color::NameForLayoutTreeAsText() const {
  if (Alpha() < 0xFF)
    return String::Format("#%02X%02X%02X%02X", Red(), Green(), Blue(), Alpha());
  return String::Format("#%02X%02X%02X", Red(), Green(), Blue());
}

bool Color::SetNamedColor(const String& name) {
  const NamedColor* found_color = FindNamedColor(name);
  color_ = found_color ? found_color->argb_value : 0;
  return found_color;
}

Color::operator SkColor() const {
  return SkColorSetARGB(Alpha(), Red(), Green(), Blue());
}

Color Color::Light() const {
  // Hardcode this common case for speed.
  if (color_ == kBlack)
    return kLightenedBlack;

  const float scale_factor = nextafterf(256.0f, 0.0f);

  float r, g, b, a;
  GetRGBA(r, g, b, a);

  float v = std::max(r, std::max(g, b));

  if (v == 0.0f)
    // Lightened black with alpha.
    return Color(0x54, 0x54, 0x54, Alpha());

  float multiplier = std::min(1.0f, v + 0.33f) / v;

  return Color(static_cast<int>(multiplier * r * scale_factor),
               static_cast<int>(multiplier * g * scale_factor),
               static_cast<int>(multiplier * b * scale_factor), Alpha());
}

Color Color::Dark() const {
  // Hardcode this common case for speed.
  if (color_ == kWhite)
    return kDarkenedWhite;

  const float scale_factor = nextafterf(256.0f, 0.0f);

  float r, g, b, a;
  GetRGBA(r, g, b, a);

  float v = std::max(r, std::max(g, b));
  float multiplier = (v == 0.0f) ? 0.0f : std::max(0.0f, (v - 0.33f) / v);

  return Color(static_cast<int>(multiplier * r * scale_factor),
               static_cast<int>(multiplier * g * scale_factor),
               static_cast<int>(multiplier * b * scale_factor), Alpha());
}

Color Color::CombineWithAlpha(float other_alpha) const {
  RGBA32 rgb_only = Rgb() & 0x00FFFFFF;
  float override_alpha = (Alpha() / 255.f) * other_alpha;
  return rgb_only | ColorFloatToRGBAByte(override_alpha) << 24;
}

Color Color::Blend(const Color& source) const {
  if (!Alpha() || !source.HasAlpha())
    return source;

  if (!source.Alpha())
    return *this;

<<<<<<< HEAD
  const SkRGBA4f<kPremul_SkAlphaType> pm_src = source.toSkColor4f().premul();
  auto pm_result = this->toSkColor4f().premul() * (1.0f - pm_src.fA);
  pm_result.fA += pm_src.fA;
  pm_result.fR += pm_src.fR;
  pm_result.fG += pm_src.fG;
  pm_result.fB += pm_src.fB;
  return Color(pm_result.unpremul());
=======
  int d = 255 * (Alpha() + source.Alpha()) - Alpha() * source.Alpha();
  int a = d / 255;
  int r = (Red() * Alpha() * (255 - source.Alpha()) +
           255 * source.Alpha() * source.Red()) /
          d;
  int g = (Green() * Alpha() * (255 - source.Alpha()) +
           255 * source.Alpha() * source.Green()) /
          d;
  int b = (Blue() * Alpha() * (255 - source.Alpha()) +
           255 * source.Alpha() * source.Blue()) /
          d;
  return Color(r, g, b, a);
>>>>>>> chromium
}

Color Color::BlendWithWhite() const {
  // If the color contains alpha already, we leave it alone.
  if (HasAlpha())
    return *this;

  Color new_color;
  for (int alpha = kCStartAlpha; alpha <= kCEndAlpha;
       alpha += kCAlphaIncrement) {
    // We have a solid color.  Convert to an equivalent color that looks the
    // same when blended with white at the current alpha.  Try using less
    // transparency if the numbers end up being negative.
    int r = BlendComponent(Red(), alpha);
    int g = BlendComponent(Green(), alpha);
    int b = BlendComponent(Blue(), alpha);

    new_color = Color(r, g, b, alpha);

    if (r >= 0 && g >= 0 && b >= 0)
      break;
  }
  return new_color;
}

void Color::GetRGBA(float& r, float& g, float& b, float& a) const {
  r = Red() / 255.0f;
  g = Green() / 255.0f;
  b = Blue() / 255.0f;
  a = Alpha() / 255.0f;
}

void Color::GetRGBA(double& r, double& g, double& b, double& a) const {
  r = Red() / 255.0;
  g = Green() / 255.0;
  b = Blue() / 255.0;
  a = Alpha() / 255.0;
}

void Color::GetHSL(double& hue, double& saturation, double& lightness) const {
  // http://en.wikipedia.org/wiki/HSL_color_space. This is a direct copy of
  // the algorithm therein, although it's 360^o based and we end up wanting
  // [0...1) based. It's clearer if we stick to 360^o until the end.
  double r = static_cast<double>(Red()) / 255.0;
  double g = static_cast<double>(Green()) / 255.0;
  double b = static_cast<double>(Blue()) / 255.0;
  double max = std::max(std::max(r, g), b);
  double min = std::min(std::min(r, g), b);

  if (max == min)
    hue = 0.0;
  else if (max == r)
    hue = (60.0 * ((g - b) / (max - min))) + 360.0;
  else if (max == g)
    hue = (60.0 * ((b - r) / (max - min))) + 120.0;
  else
    hue = (60.0 * ((r - g) / (max - min))) + 240.0;

  if (hue >= 360.0)
    hue -= 360.0;

  // makeRGBAFromHSLA assumes that hue is in [0...1).
  hue /= 360.0;

  lightness = 0.5 * (max + min);
  if (max == min)
    saturation = 0.0;
  else if (lightness <= 0.5)
    saturation = ((max - min) / (max + min));
  else
    saturation = ((max - min) / (2.0 - (max + min)));
}

Color ColorFromPremultipliedARGB(RGBA32 pixel_color) {
  int alpha = AlphaChannel(pixel_color);
  if (alpha && alpha < 255) {
    return Color::CreateUnchecked(RedChannel(pixel_color) * 255 / alpha,
                                  GreenChannel(pixel_color) * 255 / alpha,
                                  BlueChannel(pixel_color) * 255 / alpha,
                                  alpha);
  } else
    return Color(pixel_color);
}

RGBA32 PremultipliedARGBFromColor(const Color& color) {
  unsigned pixel_color;

  unsigned alpha = color.Alpha();
  if (alpha < 255) {
    pixel_color =
        Color::CreateUnchecked((color.Red() * alpha + 254) / 255,
                               (color.Green() * alpha + 254) / 255,
                               (color.Blue() * alpha + 254) / 255, alpha)
            .Rgb();
  } else
    pixel_color = color.Rgb();

  return pixel_color;
}

}  // namespace blink
