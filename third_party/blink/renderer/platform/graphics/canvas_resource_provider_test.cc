// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/graphics/canvas_resource_provider.h"

#include "components/viz/common/resources/release_callback.h"
#include "components/viz/test/test_context_provider.h"
#include "components/viz/test/test_gles2_interface.h"
<<<<<<< HEAD
#include "components/viz/test/test_raster_interface.h"
#include "gpu/command_buffer/common/shared_image_usage.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/public/platform/scheduler/test/renderer_scheduler_test_support.h"
=======
#include "components/viz/test/test_gpu_memory_buffer_manager.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/renderer/platform/graphics/canvas_resource_dispatcher.h"
#include "third_party/blink/renderer/platform/graphics/canvas_resource_params.h"
>>>>>>> chromium
#include "third_party/blink/renderer/platform/graphics/gpu/shared_gpu_context.h"
#include "third_party/blink/renderer/platform/graphics/skia/skia_utils.h"
#include "third_party/blink/renderer/platform/graphics/static_bitmap_image.h"
#include "third_party/blink/renderer/platform/graphics/test/fake_gles2_interface.h"
#include "third_party/blink/renderer/platform/graphics/test/fake_web_graphics_context_3d_provider.h"
#include "third_party/blink/renderer/platform/graphics/test/gpu_memory_buffer_test_platform.h"
#include "third_party/blink/renderer/platform/graphics/test/gpu_test_utils.h"
#include "third_party/blink/renderer/platform/wtf/functional.h"
#include "third_party/skia/include/core/SkFilterQuality.h"
#include "ui/gfx/buffer_types.h"

using testing::_;
using testing::InSequence;
using testing::Return;
using testing::Test;

namespace blink {

namespace {

constexpr int kMaxTextureSize = 1024;

<<<<<<< HEAD
class ImageTrackingDecodeCache : public cc::StubDecodeCache {
 public:
  ImageTrackingDecodeCache() = default;
  ~ImageTrackingDecodeCache() override { EXPECT_EQ(num_locked_images_, 0); }

  cc::DecodedDrawImage GetDecodedImageForDraw(
      const cc::DrawImage& image) override {
    EXPECT_FALSE(disallow_cache_use_);

    ++num_locked_images_;
    ++max_locked_images_;
    decoded_images_.push_back(image);
    SkBitmap bitmap;
    bitmap.allocPixelsFlags(SkImageInfo::MakeN32Premul(10, 10),
                            SkBitmap::kZeroPixels_AllocFlag);
    sk_sp<SkImage> sk_image = SkImages::RasterFromBitmap(bitmap);
    return cc::DecodedDrawImage(
        sk_image, nullptr, SkSize::Make(0, 0), SkSize::Make(1, 1),
        cc::PaintFlags::FilterQuality::kLow, !budget_exceeded_);
  }

  void set_budget_exceeded(bool exceeded) { budget_exceeded_ = exceeded; }
  void set_disallow_cache_use(bool disallow) { disallow_cache_use_ = disallow; }

  void DrawWithImageFinished(
      const cc::DrawImage& image,
      const cc::DecodedDrawImage& decoded_image) override {
    EXPECT_FALSE(disallow_cache_use_);
    num_locked_images_--;
  }

  const Vector<cc::DrawImage>& decoded_images() const {
    return decoded_images_;
  }
  int num_locked_images() const { return num_locked_images_; }
  int max_locked_images() const { return max_locked_images_; }

 private:
  Vector<cc::DrawImage> decoded_images_;
  int num_locked_images_ = 0;
  int max_locked_images_ = 0;
  bool budget_exceeded_ = false;
  bool disallow_cache_use_ = false;
};
=======
class MockCanvasResourceDispatcherClient
    : public CanvasResourceDispatcherClient {
 public:
  MockCanvasResourceDispatcherClient() = default;

  MOCK_METHOD0(BeginFrame, bool());
  MOCK_METHOD1(SetFilterQualityInResource, void(SkFilterQuality));
};

}  // anonymous namespace
>>>>>>> chromium

class CanvasResourceProviderTest : public Test {
 public:
  void SetUp() override {
    test_context_provider_ = viz::TestContextProvider::Create();
    auto* test_gl = test_context_provider_->UnboundTestContextGL();
    test_gl->set_max_texture_size(kMaxTextureSize);
    test_gl->set_support_texture_storage_image(true);
    test_gl->set_supports_shared_image_swap_chain(true);
    test_gl->set_supports_gpu_memory_buffer_format(gfx::BufferFormat::RGBA_8888,
                                                   true);
    test_gl->set_supports_gpu_memory_buffer_format(gfx::BufferFormat::BGRA_8888,
                                                   true);
    test_gl->set_supports_gpu_memory_buffer_format(gfx::BufferFormat::RGBA_F16,
                                                   true);
    InitializeSharedGpuContext(test_context_provider_.get(),
                               &image_decode_cache_);
    context_provider_wrapper_ = SharedGpuContext::ContextProviderWrapper();
  }

  void TearDown() override { SharedGpuContext::ResetForTesting(); }

 protected:
  cc::StubDecodeCache image_decode_cache_;
  scoped_refptr<viz::TestContextProvider> test_context_provider_;
  base::WeakPtr<WebGraphicsContext3DProviderWrapper> context_provider_wrapper_;
  ScopedTestingPlatformSupport<GpuMemoryBufferTestPlatform> platform_;
};

<<<<<<< HEAD
TEST_F(CanvasResourceProviderTest,
       GetBackingClientSharedImageForExternalWrite) {
  const gpu::SharedImageUsageSet shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY_READ | gpu::SHARED_IMAGE_USAGE_SCANOUT |
      gpu::SHARED_IMAGE_USAGE_CONCURRENT_READ_WRITE;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, shared_image_usage_flags);

  auto client_si = provider->GetBackingClientSharedImageForExternalWrite(
      /*internal_access_sync_token=*/nullptr, gpu::SharedImageUsageSet());

  // When supplied required usages that the backing SI already supports, that
  // backing SI should be returned.
  auto client_si_with_no_new_usage_required =
      provider->GetBackingClientSharedImageForExternalWrite(
          /*internal_access_sync_token=*/nullptr,
          gpu::SHARED_IMAGE_USAGE_SCANOUT);
  EXPECT_EQ(client_si_with_no_new_usage_required, client_si);

  // When supplied required usages that the backing SI does not support, a new
  // backing SI should be created that supports the required usages.
  auto client_si_with_webgpu_usage_required =
      provider->GetBackingClientSharedImageForExternalWrite(
          /*internal_access_sync_token=*/nullptr,
          gpu::SHARED_IMAGE_USAGE_WEBGPU_READ);
  EXPECT_NE(client_si_with_webgpu_usage_required, client_si);
  EXPECT_TRUE(client_si_with_webgpu_usage_required->usage().HasAll(
      shared_image_usage_flags));
  EXPECT_TRUE(client_si_with_webgpu_usage_required->usage().Has(
      gpu::SHARED_IMAGE_USAGE_WEBGPU_READ));

  // That new backing SI should then be returned on subsequent calls with
  // already-supported usages.
  client_si_with_no_new_usage_required =
      provider->GetBackingClientSharedImageForExternalWrite(
          /*internal_access_sync_token=*/nullptr,
          gpu::SHARED_IMAGE_USAGE_SCANOUT);
  EXPECT_EQ(client_si_with_no_new_usage_required,
            client_si_with_webgpu_usage_required);
}

TEST_F(CanvasResourceProviderTest, CanvasResourceProviderAcceleratedOverlay) {
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());
=======
TEST_F(CanvasResourceProviderTest, CanvasResourceProviderAcceleratedOverlay) {
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
>>>>>>> chromium

  const uint32_t shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY | gpu::SHARED_IMAGE_USAGE_SCANOUT |
      gpu::SHARED_IMAGE_USAGE_CONCURRENT_READ_WRITE;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
=======
      kSize, kMedium_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      shared_image_usage_flags);

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_TRUE(provider->IsAccelerated());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  EXPECT_TRUE(provider->SupportsSingleBuffering());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  // As it is an CanvasResourceProviderSharedImage and an accelerated canvas, it
  // will internally force it to kRGBA8
  EXPECT_EQ(provider->ColorParams().GetSkColorType(), kRGBA_8888_SkColorType);
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  EXPECT_FALSE(provider->IsSingleBuffered());
  provider->TryEnableSingleBuffering();
  EXPECT_TRUE(provider->IsSingleBuffered());
}

TEST_F(CanvasResourceProviderTest, CanvasResourceProviderTexture) {
<<<<<<< HEAD
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
      kSize, kLow_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      0u /*shared_image_usage_flags*/);

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_TRUE(provider->IsAccelerated());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  EXPECT_FALSE(provider->SupportsSingleBuffering());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  // As it is an CanvasResourceProviderSharedImage and an accelerated canvas, it
  // will internally force it to kRGBA8
  EXPECT_EQ(provider->ColorParams().GetSkColorType(), kRGBA_8888_SkColorType);
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  EXPECT_FALSE(provider->IsSingleBuffered());
}

TEST_F(CanvasResourceProviderTest, CanvasResourceProviderUnacceleratedOverlay) {
<<<<<<< HEAD
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
>>>>>>> chromium

  const uint32_t shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY | gpu::SHARED_IMAGE_USAGE_SCANOUT;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
=======
      kSize, kLow_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kCPU, true /*is_origin_top_left*/,
      shared_image_usage_flags);

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_FALSE(provider->IsAccelerated());
  EXPECT_TRUE(provider->SupportsDirectCompositing());

  // We do not support single buffering for unaccelerated low latency canvas.
  EXPECT_FALSE(provider->SupportsSingleBuffering());

  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  EXPECT_EQ(provider->ColorParams().GetSkColorType(),
            kColorParams.GetSkColorType());
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  EXPECT_FALSE(provider->IsSingleBuffered());
}

<<<<<<< HEAD
std::unique_ptr<CanvasResourceProvider> MakeCanvasResourceProvider(
    RasterMode raster_mode,
    base::WeakPtr<WebGraphicsContext3DProviderWrapper>
        context_provider_wrapper) {
  const gpu::SharedImageUsageSet shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY_READ | gpu::SHARED_IMAGE_USAGE_SCANOUT;

  return CanvasResourceProvider::CreateSharedImageProvider(
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper, raster_mode, shared_image_usage_flags);
}

scoped_refptr<CanvasResource> UpdateResource(CanvasResourceProvider* provider) {
  provider->ProduceCanvasResource(FlushReason::kTesting);
  // Resource updated after draw.
  provider->Canvas().clear(SkColors::kWhite);
  return provider->ProduceCanvasResource(FlushReason::kTesting);
}

void EnsureResourceRecycled(CanvasResourceProvider* provider,
                            scoped_refptr<CanvasResource>&& resource) {
  viz::TransferableResource transferable_resource;
  CanvasResource::ReleaseCallback release_callback;
  auto sync_token = resource->GetSyncToken();
  CHECK(resource->PrepareTransferableResource(
      &transferable_resource, &release_callback,
      /*needs_verified_synctoken=*/false));
  std::move(release_callback).Run(std::move(resource), sync_token, false);
}

=======
>>>>>>> chromium
TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderSharedImageEndExternalWrite) {
  // Set up this test to use OOP rasterization to be able to verify
  // conditions against the test raster interface.
  SharedGpuContext::Reset();
  auto raster_context_provider = viz::TestContextProvider::CreateRaster();
  raster_context_provider->UnboundTestRasterInterface()->set_gpu_rasterization(
      true);
  InitializeSharedGpuContextRaster(raster_context_provider.get(),
                                   &image_decode_cache_,
                                   SetIsContextLost::kSetToFalse);

  const gpu::SharedImageUsageSet shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY_READ | gpu::SHARED_IMAGE_USAGE_SCANOUT;
  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      SharedGpuContext::ContextProviderWrapper(), RasterMode::kGPU,
      shared_image_usage_flags);

  auto resource = provider->ProduceCanvasResource(FlushReason::kTesting);
  auto old_compositor_read_sync_token = resource->GetSyncToken();

  // NOTE: Need to ensure that this SyncToken's release count is greater than
  // that of the last one that TestRasterInterface waited on for
  // TestRasterInterface to set this token as `last_waited_sync_token_` when it
  // waits on the token.
  gpu::SyncToken external_write_sync_token(gpu::CommandBufferNamespace::GPU_IO,
                                           gpu::CommandBufferId(), 42);

  provider->EndExternalWrite(external_write_sync_token);

  // EndExternalWrite() should have initiated a wait on
  // `external_write_sync_token` on the raster interface.
  EXPECT_EQ(raster_context_provider->GetTestRasterInterface()
                ->last_waited_sync_token(),
            external_write_sync_token);

  // In addition, it should have ensured that the resource generates a new
  // compositor read sync token on the next request for that token.
  EXPECT_NE(resource->GetSyncToken(), old_compositor_read_sync_token);
}

TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderSharedImageResourceRecycling) {
<<<<<<< HEAD
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
>>>>>>> chromium

  const uint32_t shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY | gpu::SHARED_IMAGE_USAGE_SCANOUT;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
=======
      kSize, kMedium_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      shared_image_usage_flags);

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_TRUE(provider->IsAccelerated());
  EXPECT_FALSE(provider->IsSingleBuffered());
  EXPECT_FALSE(provider->SupportsSingleBuffering());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  // As it is an CanvasResourceProviderSharedImage and an accelerated canvas, it
  // will internally force it to kRGBA8
  EXPECT_EQ(provider->ColorParams().GetSkColorType(), kRGBA_8888_SkColorType);
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  // Same resource and sync token if we query again without updating.
  auto resource = provider->ProduceCanvasResource();
  auto sync_token = resource->GetSyncToken();
  ASSERT_TRUE(resource);
  EXPECT_EQ(resource, provider->ProduceCanvasResource());
  EXPECT_EQ(sync_token, resource->GetSyncToken());

  // Resource updated after draw.
  provider->Canvas()->clear(SK_ColorWHITE);
  auto new_resource = provider->ProduceCanvasResource();
  EXPECT_NE(resource, new_resource);
  EXPECT_NE(sync_token, new_resource->GetSyncToken());

  // Resource recycled.
  viz::TransferableResource transferable_resource;
  viz::ReleaseCallback release_callback;
  ASSERT_TRUE(resource->PrepareTransferableResource(
      &transferable_resource, &release_callback, kUnverifiedSyncToken));
  auto* resource_ptr = resource.get();
  resource = nullptr;
  std::move(release_callback).Run(sync_token, false);

  provider->Canvas()->clear(SK_ColorBLACK);
  auto resource_again = provider->ProduceCanvasResource();
  EXPECT_EQ(resource_ptr, resource_again);
  EXPECT_NE(sync_token, resource_again->GetSyncToken());
}

TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderSharedImageStaticBitmapImage) {
<<<<<<< HEAD
  const gpu::SharedImageUsageSet shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY_READ | gpu::SHARED_IMAGE_USAGE_SCANOUT;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  const uint32_t shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY | gpu::SHARED_IMAGE_USAGE_SCANOUT;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
      kSize, kMedium_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      shared_image_usage_flags);

  ASSERT_TRUE(provider->IsValid());

  // Same resource returned until the canvas is updated.
  auto image = provider->Snapshot();
  ASSERT_TRUE(image);
<<<<<<< HEAD
  auto new_image = provider->Snapshot(FlushReason::kTesting);
  EXPECT_EQ(image->GetSharedImage(), new_image->GetSharedImage());
  EXPECT_EQ(provider->ProduceCanvasResource(FlushReason::kTesting)
                ->GetClientSharedImage(),
            image->GetSharedImage());

  // Resource updated after draw.
  provider->Canvas().clear(SkColors::kWhite);
  provider->FlushCanvas(FlushReason::kTesting);
  new_image = provider->Snapshot(FlushReason::kTesting);
  EXPECT_NE(new_image->GetSharedImage(), image->GetSharedImage());
=======
  auto new_image = provider->Snapshot();
  EXPECT_EQ(image->GetMailboxHolder().mailbox,
            new_image->GetMailboxHolder().mailbox);
  EXPECT_EQ(provider->ProduceCanvasResource()->GetOrCreateGpuMailbox(
                kOrderingBarrier),
            image->GetMailboxHolder().mailbox);

  // Resource updated after draw.
  provider->Canvas()->clear(SK_ColorWHITE);
  provider->FlushCanvas();
  new_image = provider->Snapshot();
  EXPECT_NE(new_image->GetMailboxHolder().mailbox,
            image->GetMailboxHolder().mailbox);
>>>>>>> chromium

  // Resource recycled.
  auto original_shared_image = image->GetSharedImage();
  image.reset();
<<<<<<< HEAD
  provider->Canvas().clear(SkColors::kBlack);
  provider->FlushCanvas(FlushReason::kTesting);
  EXPECT_EQ(original_shared_image,
            provider->Snapshot(FlushReason::kTesting)->GetSharedImage());
}

TEST_F(CanvasResourceProviderTest, NoRecycleIfLastRefCallback) {
  const gpu::SharedImageUsageSet shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY_READ | gpu::SHARED_IMAGE_USAGE_SCANOUT;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, shared_image_usage_flags);

  ASSERT_TRUE(provider->IsValid());

  scoped_refptr<StaticBitmapImage> snapshot1 =
      provider->Snapshot(FlushReason::kTesting);
  ASSERT_TRUE(snapshot1);

  // Set up a LastUnrefCallback that recycles the resource asynchronously,
  // similarly to what OffscreenCanvasPlaceholder would do.
  provider->ProduceCanvasResource(FlushReason::kTesting)
      ->SetLastUnrefCallback(
          base::BindOnce([](scoped_refptr<CanvasResource> resource) {}));

  // Resource updated after draw.
  provider->Canvas().clear(SkColors::kWhite);
  provider->FlushCanvas(FlushReason::kTesting);
  scoped_refptr<StaticBitmapImage> snapshot2 =
      provider->Snapshot(FlushReason::kTesting);
  EXPECT_NE(snapshot2->GetSharedImage(), snapshot1->GetSharedImage());

  auto snapshot1_shared_image = snapshot1->GetSharedImage();
  snapshot1.reset();  // resource not recycled due to LastUnrefCallback
  provider->Canvas().clear(SkColors::kBlack);
  provider->FlushCanvas(FlushReason::kTesting);
  scoped_refptr<StaticBitmapImage> snapshot3 =
      provider->Snapshot(FlushReason::kTesting);
  // confirm resource is not recycled.
  EXPECT_NE(snapshot3->GetSharedImage(), snapshot1_shared_image);
=======
  provider->Canvas()->clear(SK_ColorBLACK);
  provider->FlushCanvas();
  EXPECT_EQ(original_mailbox, provider->Snapshot()->GetMailboxHolder().mailbox);
>>>>>>> chromium
}

TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderSharedImageCopyOnWriteDisabled) {
  auto& fake_context = static_cast<FakeWebGraphicsContext3DProvider&>(
      context_provider_wrapper_->ContextProvider());
  auto caps = fake_context.GetCapabilities();
  caps.disable_2d_canvas_copy_on_write = true;
<<<<<<< HEAD
  fake_context.SetCapabilities(caps);
=======
  fake_context->SetCapabilities(caps);

  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
>>>>>>> chromium

  const uint32_t shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY | gpu::SHARED_IMAGE_USAGE_SCANOUT;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
=======
      kSize, kMedium_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU,
      true /* is_origin_top_left */, shared_image_usage_flags);

  ASSERT_TRUE(provider->IsValid());

  // Disabling copy-on-write forces a copy each time the resource is queried.
  auto resource = provider->ProduceCanvasResource();
  EXPECT_NE(resource->GetOrCreateGpuMailbox(kOrderingBarrier),
            provider->ProduceCanvasResource()->GetOrCreateGpuMailbox(
                kOrderingBarrier));
}

TEST_F(CanvasResourceProviderTest, CanvasResourceProviderBitmap) {
<<<<<<< HEAD
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());

  auto provider = CanvasResourceProvider::CreateBitmapProvider(
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  auto provider = CanvasResourceProvider::CreateBitmapProvider(
      kSize, kLow_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear);

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_FALSE(provider->IsAccelerated());
  EXPECT_FALSE(provider->SupportsDirectCompositing());
  EXPECT_FALSE(provider->SupportsSingleBuffering());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  EXPECT_EQ(provider->ColorParams().GetSkColorType(),
            kColorParams.GetSkColorType());
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  EXPECT_FALSE(provider->IsSingleBuffered());
}

<<<<<<< HEAD
TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderSharedBitmap_GPUCompositing) {
  std::unique_ptr<WebGraphicsSharedImageInterfaceProvider>
      test_web_shared_image_interface_provider =
          TestWebGraphicsSharedImageInterfaceProvider::Create();

  EXPECT_FALSE(CanvasResourceProvider::CreateSharedBitmapProvider(
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      test_web_shared_image_interface_provider.get()));
}

TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderSharedBitmap_SWCompositing) {
  platform_->SetGpuCompositingDisabled(true);

  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());
  std::unique_ptr<WebGraphicsSharedImageInterfaceProvider>
      test_web_shared_image_interface_provider =
          TestWebGraphicsSharedImageInterfaceProvider::Create();

  auto provider = CanvasResourceProvider::CreateSharedBitmapProvider(
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      test_web_shared_image_interface_provider.get());
=======
TEST_F(CanvasResourceProviderTest, CanvasResourceProviderSharedBitmap) {
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  MockCanvasResourceDispatcherClient client;
  CanvasResourceDispatcher resource_dispatcher(
      &client, 1 /* client_id */, 1 /* sink_id */,
      1 /* placeholder_canvas_id */, kSize);

  auto provider = CanvasResourceProvider::CreateSharedBitmapProvider(
      kSize, kLow_SkFilterQuality, kColorParams,
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      resource_dispatcher.GetWeakPtr());
>>>>>>> chromium

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_FALSE(provider->IsAccelerated());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  EXPECT_FALSE(provider->SupportsSingleBuffering());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  EXPECT_EQ(provider->ColorParams().GetSkColorType(),
            kColorParams.GetSkColorType());
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  EXPECT_FALSE(provider->IsSingleBuffered());
  provider->TryEnableSingleBuffering();
  EXPECT_FALSE(provider->IsSingleBuffered());
}

TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderDirect2DGpuMemoryBuffer) {
<<<<<<< HEAD
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
>>>>>>> chromium

  const uint32_t shared_image_usage_flags =
      gpu::SHARED_IMAGE_USAGE_DISPLAY | gpu::SHARED_IMAGE_USAGE_SCANOUT |
      gpu::SHARED_IMAGE_USAGE_CONCURRENT_READ_WRITE;

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
=======
      kSize, kMedium_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      shared_image_usage_flags);

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_TRUE(provider->IsAccelerated());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  EXPECT_TRUE(provider->SupportsSingleBuffering());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  // As it is an CanvasResourceProviderSharedImage and an accelerated canvas, it
  // will internally force it to kRGBA8
  EXPECT_EQ(provider->ColorParams().GetSkColorType(), kRGBA_8888_SkColorType);
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  EXPECT_FALSE(provider->IsSingleBuffered());
  provider->TryEnableSingleBuffering();
  EXPECT_TRUE(provider->IsSingleBuffered());
}

TEST_F(CanvasResourceProviderTest,
       CanvasResourceProviderDirect3DGpuMemoryBuffer) {
<<<<<<< HEAD
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());

  auto provider = CanvasResourceProvider::CreatePassThroughProvider(
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(), context_provider_wrapper_);
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  auto provider = CanvasResourceProvider::CreatePassThroughProvider(
      kSize, kLow_SkFilterQuality, kColorParams, context_provider_wrapper_,
      nullptr /*resource_dispatcher */, true /*is_origin_top_left*/);
>>>>>>> chromium

  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_TRUE(provider->IsAccelerated());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  EXPECT_TRUE(provider->SupportsSingleBuffering());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  EXPECT_EQ(provider->ColorParams().GetSkColorType(),
            kColorParams.GetSkColorType());
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());

  EXPECT_FALSE(provider->IsSingleBuffered());
  provider->TryEnableSingleBuffering();
  EXPECT_TRUE(provider->IsSingleBuffered());

  gpu::Mailbox mailbox = gpu::Mailbox::Generate();
  scoped_refptr<ExternalCanvasResource> resource =
      ExternalCanvasResource::Create(
<<<<<<< HEAD
          client_si, tr.sync_token(), tr.resource_source, tr.hdr_metadata,
          viz::ReleaseCallback(), SharedGpuContext::ContextProviderWrapper(),
          provider->CreateWeakPtr());
=======
          mailbox, viz::ReleaseCallback(), gpu::SyncToken(), kSize,
          GL_TEXTURE_2D, kColorParams,
          SharedGpuContext::ContextProviderWrapper(), provider->CreateWeakPtr(),
          kMedium_SkFilterQuality, true /*is_origin_top_left*/,
          true /*is_overlay_candidate*/);
>>>>>>> chromium

  // NewOrRecycledResource() would return nullptr before an ImportResource().
  EXPECT_TRUE(provider->ImportResource(resource));
  EXPECT_EQ(provider->NewOrRecycledResource(), resource);
  // NewOrRecycledResource() will always return the same |resource|.
  EXPECT_EQ(provider->NewOrRecycledResource(), resource);
}

TEST_F(CanvasResourceProviderTest, DimensionsExceedMaxTextureSize_Bitmap) {
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  auto provider = CanvasResourceProvider::CreateBitmapProvider(
<<<<<<< HEAD
      gfx::Size(kMaxTextureSize - 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear);
  EXPECT_FALSE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateBitmapProvider(
      gfx::Size(kMaxTextureSize, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear);
  EXPECT_FALSE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateBitmapProvider(
      gfx::Size(kMaxTextureSize + 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear);
=======
      IntSize(kMaxTextureSize - 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear);
  EXPECT_FALSE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateBitmapProvider(
      IntSize(kMaxTextureSize, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear);
  EXPECT_FALSE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateBitmapProvider(
      IntSize(kMaxTextureSize + 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear);
>>>>>>> chromium
  EXPECT_FALSE(provider->SupportsDirectCompositing());
}

TEST_F(CanvasResourceProviderTest, DimensionsExceedMaxTextureSize_SharedImage) {
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  auto provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      gfx::Size(kMaxTextureSize - 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, gpu::SharedImageUsageSet());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSharedImageProvider(
      gfx::Size(kMaxTextureSize, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, gpu::SharedImageUsageSet());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSharedImageProvider(
      gfx::Size(kMaxTextureSize + 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, gpu::SharedImageUsageSet());
=======
      IntSize(kMaxTextureSize - 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      0u /*shared_image_usage_flags*/);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSharedImageProvider(
      IntSize(kMaxTextureSize, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      0u /*shared_image_usage_flags*/);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSharedImageProvider(
      IntSize(kMaxTextureSize + 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      0u /*shared_image_usage_flags*/);
>>>>>>> chromium
  // The CanvasResourceProvider for SharedImage should not be created or valid
  // if the texture size is greater than the maximum value
  EXPECT_TRUE(!provider || !provider->IsValid());
}

TEST_F(CanvasResourceProviderTest, DimensionsExceedMaxTextureSize_SwapChain) {
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
  auto provider = CanvasResourceProvider::CreateSwapChainProvider(
<<<<<<< HEAD
      gfx::Size(kMaxTextureSize - 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSwapChainProvider(
      gfx::Size(kMaxTextureSize, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSwapChainProvider(
      gfx::Size(kMaxTextureSize + 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_);
=======
      IntSize(kMaxTextureSize - 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, nullptr /* resource_dispatcher */,
      true /*is_origin_top_left*/);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSwapChainProvider(
      IntSize(kMaxTextureSize, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, nullptr /* resource_dispatcher */,
      true /*is_origin_top_left*/);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreateSwapChainProvider(
      IntSize(kMaxTextureSize + 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, nullptr /* resource_dispatcher */,
      true /*is_origin_top_left*/);
>>>>>>> chromium

  // The CanvasResourceProvider for SwapChain should not be created or valid
  // if the texture size is greater than the maximum value
  EXPECT_TRUE(!provider || !provider->IsValid());
}

TEST_F(CanvasResourceProviderTest, DimensionsExceedMaxTextureSize_PassThrough) {
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
  auto provider = CanvasResourceProvider::CreatePassThroughProvider(
<<<<<<< HEAD
      gfx::Size(kMaxTextureSize - 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      context_provider_wrapper_);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreatePassThroughProvider(
      gfx::Size(kMaxTextureSize, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      context_provider_wrapper_);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreatePassThroughProvider(
      gfx::Size(kMaxTextureSize + 1, kMaxTextureSize), GetN32FormatForCanvas(),
      kPremul_SkAlphaType, gfx::ColorSpace::CreateSRGB(),
      context_provider_wrapper_);
=======
      IntSize(kMaxTextureSize - 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, context_provider_wrapper_,
      nullptr /* resource_dispatcher */, true /*is_origin_top_left*/);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreatePassThroughProvider(
      IntSize(kMaxTextureSize, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, context_provider_wrapper_,
      nullptr /* resource_dispatcher */, true /*is_origin_top_left*/);
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  provider = CanvasResourceProvider::CreatePassThroughProvider(
      IntSize(kMaxTextureSize + 1, kMaxTextureSize), kLow_SkFilterQuality,
      kColorParams, context_provider_wrapper_,
      nullptr /* resource_dispatcher */, true /*is_origin_top_left*/);
>>>>>>> chromium
  // The CanvasResourceProvider for PassThrough should not be created or valid
  // if the texture size is greater than the maximum value
  EXPECT_TRUE(!provider || !provider->IsValid());
}

TEST_F(CanvasResourceProviderTest, CanvasResourceProviderDirect2DSwapChain) {
<<<<<<< HEAD
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo =
      SkImageInfo::MakeN32Premul(10, 10, SkColorSpace::MakeSRGB());

  auto provider = CanvasResourceProvider::CreateSwapChainProvider(
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGB(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_);
=======
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);

  auto provider = CanvasResourceProvider::CreateSwapChainProvider(
      kSize, kLow_SkFilterQuality, kColorParams,
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, nullptr /* resource_dispatcher */,
      true /*is_origin_top_left*/);
>>>>>>> chromium

  ASSERT_TRUE(provider);
  EXPECT_EQ(provider->Size(), kSize);
  EXPECT_TRUE(provider->IsValid());
  EXPECT_TRUE(provider->IsAccelerated());
  EXPECT_TRUE(provider->SupportsDirectCompositing());
  EXPECT_TRUE(provider->SupportsSingleBuffering());
  EXPECT_TRUE(provider->IsSingleBuffered());
  EXPECT_EQ(provider->ColorParams().ColorSpace(), kColorParams.ColorSpace());
  EXPECT_EQ(provider->ColorParams().GetSkColorType(),
            kColorParams.GetSkColorType());
  EXPECT_EQ(provider->ColorParams().GetSkAlphaType(),
            kColorParams.GetSkAlphaType());
}

<<<<<<< HEAD
TEST_F(
    CanvasResourceProviderTest,
    CanvasResourceProviderSwapChain_NonDefaultColorSpaceIsPropagatedToResource) {
  const gfx::Size kSize(10, 10);
  const SkImageInfo kInfo = SkImageInfo::MakeN32(
      10, 10, kPremul_SkAlphaType, SkColorSpace::MakeSRGBLinear());
=======
TEST_F(CanvasResourceProviderTest, FlushForImage) {
  const IntSize kSize(10, 10);
  const CanvasResourceParams kColorParams(
      CanvasColorSpace::kSRGB, kN32_SkColorType, kPremul_SkAlphaType);
>>>>>>> chromium

  auto provider = CanvasResourceProvider::CreateSwapChainProvider(
      kSize, GetN32FormatForCanvas(), kInfo.alphaType(),
      gfx::ColorSpace::CreateSRGBLinear(),
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_);

  ASSERT_TRUE(provider);
  ASSERT_EQ(provider->GetSkImageInfo(), kInfo);

  auto resource = provider->ProduceCanvasResource(FlushReason::kTesting);
  EXPECT_EQ(resource->CreateSkImageInfo(), kInfo);
}

TEST_F(CanvasResourceProviderTest, FlushForImage) {
  auto src_provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
=======
      kSize, kMedium_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      0u /*shared_image_usage_flags*/);

  auto dst_provider = CanvasResourceProvider::CreateSharedImageProvider(
<<<<<<< HEAD
      gfx::Size(10, 10), GetN32FormatForCanvas(), kPremul_SkAlphaType,
      gfx::ColorSpace::CreateSRGB(),
=======
      kSize, kMedium_SkFilterQuality, kColorParams,
>>>>>>> chromium
      CanvasResourceProvider::ShouldInitialize::kCallClear,
      context_provider_wrapper_, RasterMode::kGPU, true /*is_origin_top_left*/,
      0u /*shared_image_usage_flags*/);

  MemoryManagedPaintCanvas* dst_canvas =
      static_cast<MemoryManagedPaintCanvas*>(dst_provider->Canvas());

  PaintImage paint_image =
      src_provider->Snapshot()->PaintImageForCurrentFrame();
  PaintImage::ContentId src_content_id = paint_image.GetContentIdForFrame(0u);

  EXPECT_FALSE(dst_canvas->IsCachingImage(src_content_id));

  dst_canvas->drawImage(paint_image, 0, 0, SkSamplingOptions(), nullptr);

  EXPECT_TRUE(dst_canvas->IsCachingImage(src_content_id));

  src_provider->Canvas()->clear(
      SK_ColorWHITE);  // Modify the canvas to trigger OnFlushForImage
  src_provider
      ->ProduceCanvasResource();  // So that all the cached draws are executed

  // The paint canvas may have moved
  dst_canvas = static_cast<MemoryManagedPaintCanvas*>(dst_provider->Canvas());

  // TODO(aaronhk): The resource on the src_provider should be the same before
  // and after the draw. Something about the program flow within
  // this testing framework (but not in layout tests) makes a reference to
  // the src_resource stick around throughout the FlushForImage call so the
  // src_resource changes in this test. Things work as expected for actual
  // browser code like canvas_to_canvas_draw.html.

  // OnFlushForImage should detect the modification of the source resource and
  // clear the cache of the destination canvas to avoid a copy-on-write.
  EXPECT_FALSE(dst_canvas->IsCachingImage(src_content_id));
}

}  // namespace blink
