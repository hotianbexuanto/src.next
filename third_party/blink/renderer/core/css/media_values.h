// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_MEDIA_VALUES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_MEDIA_VALUES_H_

#include "third_party/blink/public/mojom/css/preferred_color_scheme.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/css/preferred_contrast.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/manifest/display_mode.mojom-shared.h"
#include "third_party/blink/public/mojom/webpreferences/web_preferences.mojom-blink-forward.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/css/css_primitive_value.h"
#include "third_party/blink/renderer/platform/heap/handle.h"
#include "ui/base/pointer/pointer_device.h"

namespace blink {

class Document;
class CSSPrimitiveValue;
class LocalFrame;
enum class CSSValueID;
enum class ColorSpaceGamut;
enum class ForcedColors;
enum class NavigationControls;
enum class ScreenSpanning { kNone, kSingleFoldHorizontal, kSingleFoldVertical };
enum class DevicePosture { kNoFold, kLaptop, kFlat, kTent, kTablet, kBook };

mojom::blink::PreferredColorScheme CSSValueIDToPreferredColorScheme(
    CSSValueID id);

class CORE_EXPORT MediaValues : public GarbageCollected<MediaValues> {
 public:
  virtual ~MediaValues() = default;
  virtual void Trace(Visitor* visitor) const {}

  static MediaValues* CreateDynamicIfFrameExists(LocalFrame*);
  virtual MediaValues* Copy() const = 0;

  static bool ComputeLengthImpl(double value,
                                CSSPrimitiveValue::UnitType,
                                unsigned default_font_size,
                                double viewport_width,
                                double viewport_height,
                                double& result);
  template <typename T>
  static bool ComputeLength(double value,
                            CSSPrimitiveValue::UnitType type,
                            unsigned default_font_size,
                            double viewport_width,
                            double viewport_height,
                            T& result) {
    double temp_result;
    if (!ComputeLengthImpl(value, type, default_font_size, viewport_width,
                           viewport_height, temp_result))
      return false;
    result = clampTo<T>(temp_result);
    return true;
  }
  virtual bool ComputeLength(double value,
                             CSSPrimitiveValue::UnitType,
                             int& result) const = 0;
  virtual bool ComputeLength(double value,
                             CSSPrimitiveValue::UnitType,
                             double& result) const = 0;

  virtual double ViewportWidth() const = 0;
  virtual double ViewportHeight() const = 0;
  virtual int DeviceWidth() const = 0;
  virtual int DeviceHeight() const = 0;
  virtual float DevicePixelRatio() const = 0;
  virtual int ColorBitsPerComponent() const = 0;
  virtual int MonochromeBitsPerComponent() const = 0;
  virtual mojom::blink::PointerType PrimaryPointerType() const = 0;
  virtual int AvailablePointerTypes() const = 0;
  virtual mojom::blink::HoverType PrimaryHoverType() const = 0;
  virtual int AvailableHoverTypes() const = 0;
  virtual bool ThreeDEnabled() const = 0;
  virtual bool InImmersiveMode() const = 0;
  virtual const String MediaType() const = 0;
  virtual blink::mojom::DisplayMode DisplayMode() const = 0;
  virtual bool StrictMode() const = 0;
  virtual Document* GetDocument() const = 0;
  virtual bool HasValues() const = 0;

  virtual void OverrideViewportDimensions(double width, double height) = 0;
  virtual ColorSpaceGamut ColorGamut() const = 0;
  virtual mojom::blink::PreferredColorScheme GetPreferredColorScheme()
      const = 0;
  virtual mojom::blink::PreferredContrast GetPreferredContrast() const = 0;
  virtual bool PrefersReducedMotion() const = 0;
  virtual bool PrefersReducedData() const = 0;
  virtual ForcedColors GetForcedColors() const = 0;
  virtual NavigationControls GetNavigationControls() const = 0;
<<<<<<< HEAD
  virtual int GetHorizontalViewportSegments() const = 0;
  virtual int GetVerticalViewportSegments() const = 0;
  virtual mojom::blink::DevicePostureType GetDevicePosture() const = 0;
  // For evaluating scroll-state(stuck: left), scroll-state(stuck: right)
  virtual ContainerStuckPhysical StuckHorizontal() const {
    return ContainerStuckPhysical::kNo;
  }
  // For evaluating scroll-state(stuck: top), scroll-state(stuck: bottom)
  virtual ContainerStuckPhysical StuckVertical() const {
    return ContainerStuckPhysical::kNo;
  }
  // For evaluating scroll-state(stuck: inline-start),
  // scroll-state(stuck: inline-end)
  virtual ContainerStuckLogical StuckInline() const {
    return ContainerStuckLogical::kNo;
  }
  // For evaluating scroll-state(stuck: block-start),
  // scroll-state(stuck: block-end)
  virtual ContainerStuckLogical StuckBlock() const {
    return ContainerStuckLogical::kNo;
  }
  // For boolean context evaluation.
  bool Stuck() const {
    return StuckHorizontal() != ContainerStuckPhysical::kNo ||
           StuckVertical() != ContainerStuckPhysical::kNo;
  }
  virtual ContainerSnappedFlags SnappedFlags() const {
    return static_cast<ContainerSnappedFlags>(ContainerSnapped::kNone);
  }
  // For evaluating scroll-state(snapped: x/y)
  bool SnappedX() const {
    return SnappedFlags() &
           static_cast<ContainerSnappedFlags>(ContainerSnapped::kX);
  }
  bool SnappedY() const {
    return SnappedFlags() &
           static_cast<ContainerSnappedFlags>(ContainerSnapped::kY);
  }
  // For evaluating scroll-state(snapped: block/inline)
  bool SnappedBlock() const;
  bool SnappedInline() const;
  // For boolean context evaluation.
  bool Snapped() const {
    return SnappedFlags() !=
           static_cast<ContainerSnappedFlags>(ContainerSnapped::kNone);
  }
  // For evaluating scroll-state(overflowing: left/right)
  virtual ContainerScrollableFlags ScrollableHorizontal() const {
    return static_cast<ContainerScrollableFlags>(ContainerScrollable::kNone);
  }
  // For evaluating scroll-state(overflowing: top/bottom)
  virtual ContainerScrollableFlags ScrollableVertical() const {
    return static_cast<ContainerScrollableFlags>(ContainerScrollable::kNone);
  }
  // For evaluating scroll-state(overflowing: inline-start/inline-end)
  virtual ContainerScrollableFlags ScrollableInline() const {
    return static_cast<ContainerScrollableFlags>(ContainerScrollable::kNone);
  }
  // For evaluating scroll-state(overflowing: block-start/block-end)
  virtual ContainerScrollableFlags ScrollableBlock() const {
    return static_cast<ContainerScrollableFlags>(ContainerScrollable::kNone);
  }
  // For boolean context evaluation
  bool Scrollable() const {
    return ScrollableHorizontal() != static_cast<ContainerScrollableFlags>(
                                         ContainerScrollable::kNone) ||
           ScrollableVertical() != static_cast<ContainerScrollableFlags>(
                                       ContainerScrollable::kNone);
  }
  // Returns the container element used to retrieve base style and parent style
  // when computing the computed value of a style() container query.
  virtual Element* ContainerElement() const { return nullptr; }

  virtual Scripting GetScripting() const = 0;

  // CSSLengthResolver override.
  void ReferenceTreeScope() const override {}
  void ReferenceAnchor() const override {}
  void ReferenceSibling() const override {}

  Element* GetElement() const override { NOTREACHED(); }
=======
  virtual ScreenSpanning GetScreenSpanning() const = 0;
  virtual DevicePosture GetDevicePosture() const = 0;
>>>>>>> chromium

 protected:
  static double CalculateViewportWidth(LocalFrame*);
  static double CalculateViewportHeight(LocalFrame*);
  static int CalculateDeviceWidth(LocalFrame*);
  static int CalculateDeviceHeight(LocalFrame*);
  static bool CalculateStrictMode(LocalFrame*);
  static float CalculateDevicePixelRatio(LocalFrame*);
  static int CalculateColorBitsPerComponent(LocalFrame*);
  static int CalculateMonochromeBitsPerComponent(LocalFrame*);
  static int CalculateDefaultFontSize(LocalFrame*);
  static const String CalculateMediaType(LocalFrame*);
  static blink::mojom::DisplayMode CalculateDisplayMode(LocalFrame*);
  static bool CalculateThreeDEnabled(LocalFrame*);
  static bool CalculateInImmersiveMode(LocalFrame*);
  static mojom::blink::PointerType CalculatePrimaryPointerType(LocalFrame*);
  static int CalculateAvailablePointerTypes(LocalFrame*);
  static mojom::blink::HoverType CalculatePrimaryHoverType(LocalFrame*);
  static int CalculateAvailableHoverTypes(LocalFrame*);
  static ColorSpaceGamut CalculateColorGamut(LocalFrame*);
  static mojom::blink::PreferredColorScheme CalculatePreferredColorScheme(
      LocalFrame*);
  static mojom::blink::PreferredContrast CalculatePreferredContrast(
      LocalFrame*);
  static bool CalculatePrefersReducedMotion(LocalFrame*);
  static bool CalculatePrefersReducedData(LocalFrame*);
  static ForcedColors CalculateForcedColors(LocalFrame*);
  static NavigationControls CalculateNavigationControls(LocalFrame*);
  static ScreenSpanning CalculateScreenSpanning(LocalFrame*);
  static DevicePosture CalculateDevicePosture(LocalFrame*);
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_MEDIA_VALUES_H_
