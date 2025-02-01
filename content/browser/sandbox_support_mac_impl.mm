// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

<<<<<<< HEAD
#include "base/functional/bind.h"
#import "content/browser/sandbox_support_impl.h"
=======
#import "content/browser/sandbox_support_mac_impl.h"

#include "base/bind.h"
#include "base/task/post_task.h"
#include "base/task_runner_util.h"
>>>>>>> chromium
#import "content/browser/theme_helper_mac.h"
#include "content/common/mac/font_loader.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"

namespace content {

SandboxSupportImpl::SandboxSupportImpl() = default;

SandboxSupportImpl::~SandboxSupportImpl() = default;

void SandboxSupportImpl::BindReceiver(
    mojo::PendingReceiver<mojom::SandboxSupport> receiver) {
  receivers_.Add(this, std::move(receiver));
}

void SandboxSupportImpl::GetSystemColors(GetSystemColorsCallback callback) {
  auto task_runner = GetUIThreadTaskRunner({});
  base::PostTaskAndReplyWithResult(
      task_runner.get(), FROM_HERE,
      base::BindOnce(&ThemeHelperMac::DuplicateReadOnlyColorMapRegion,
                     base::Unretained(ThemeHelperMac::GetInstance())),
      std::move(callback));
}

void SandboxSupportMacImpl::LoadFont(const std::u16string& font_name,
                                     float font_point_size,
                                     LoadFontCallback callback) {
  FontLoader::LoadFont(font_name, font_point_size, std::move(callback));
}

}  // namespace content
