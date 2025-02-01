// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_CANVAS_RESOURCE_HOST_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_CANVAS_RESOURCE_HOST_H_

#include <memory>

#include "third_party/blink/renderer/platform/graphics/graphics_types.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_canvas.h"
#include "third_party/blink/renderer/platform/platform_export.h"

namespace cc {
class PaintCanvas;
}

namespace blink {
class CanvasResourceProvider;

class PLATFORM_EXPORT CanvasResourceHost {
 public:
<<<<<<< HEAD
  explicit CanvasResourceHost(gfx::Size size);
  ~CanvasResourceHost() override;

  // cc::TextureLayerClient implementation.
  bool PrepareTransferableResource(
      viz::TransferableResource* out_resource,
      viz::ReleaseCallback* out_release_callback) override;

=======
  virtual ~CanvasResourceHost() = default;
>>>>>>> chromium
  virtual void NotifyGpuContextLost() = 0;
  virtual void SetNeedsCompositingUpdate() = 0;
  virtual void RestoreCanvasMatrixClipStack(cc::PaintCanvas*) const = 0;
  virtual void UpdateMemoryUsage() = 0;
  virtual size_t GetMemoryUsage() const = 0;
  virtual CanvasResourceProvider* GetOrCreateCanvasResourceProvider(
      RasterModeHint hint) = 0;
  virtual CanvasResourceProvider* GetOrCreateCanvasResourceProviderImpl(
      RasterModeHint hint) = 0;
<<<<<<< HEAD
  CanvasResourceProvider*
  GetOrCreateResourceProviderWithCurrentRasterModeHint() {
    return GetOrCreateCanvasResourceProvider(preferred_2d_raster_mode());
  }

  // Initialize the indicated cc::Layer with the HTMLCanvasElement's CSS
  // properties. This is a no-op if `this` is not an HTMLCanvasElement.
  virtual void InitializeLayerWithCSSProperties(cc::Layer* layer) {}

  bool IsComposited() const;
  bool IsResourceValid();
  virtual bool HasPlacedElements() const { return false; }
  gfx::Size Size() const { return size_; }
  virtual void SetSize(gfx::Size size) { size_ = size; }

  void SetHdrMetadata(const gfx::HDRMetadata& hdr_metadata);
  const gfx::HDRMetadata& GetHDRMetadata() const { return hdr_metadata_; }
=======
>>>>>>> chromium

  virtual void SetFilterQuality(SkFilterQuality filter_quality);
  SkFilterQuality FilterQuality() const { return filter_quality_; }
  virtual bool LowLatencyEnabled() const { return false; }

  CanvasResourceProvider* ResourceProvider() const;

  std::unique_ptr<CanvasResourceProvider> ReplaceResourceProvider(
      std::unique_ptr<CanvasResourceProvider>);

  virtual void DiscardResourceProvider();

  virtual bool IsPrinting() const { return false; }

 private:
  void InitializeForRecording(cc::PaintCanvas* canvas);

  std::unique_ptr<CanvasResourceProvider> resource_provider_;
<<<<<<< HEAD
  gfx::HDRMetadata hdr_metadata_;
  RasterModeHint preferred_2d_raster_mode_ = RasterModeHint::kPreferCPU;
  gfx::Size size_;
  bool always_enable_raster_timers_for_testing_ = false;
  // TODO(380896841): Extremely confusingly, this cc::TextureLayer, which in
  // this superclass of CanvasRenderingContextHost, is only used by 2D
  // canvases.
  scoped_refptr<cc::TextureLayer> cc_layer_;
  OpacityMode opacity_mode_ = kNonOpaque;
=======
  SkFilterQuality filter_quality_ = kLow_SkFilterQuality;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_CANVAS_RESOURCE_HOST_H_
