// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/extensions/extension_apitest.h"
#include "content/public/test/browser_test.h"

namespace extensions {

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)

constexpr char kBackgroundJS_SabDisallowed[] = R"(
  chrome.test.runTests([
    function sendSharedArrayBufferToWorker() {
      try {
        let sab = new SharedArrayBuffer(16);
        chrome.test.fail('SAB construction succeeded unexpectedly')
      } catch (e) {
        chrome.test.succeed();
      }
    }
  ]);
)";

#else

constexpr char kWorkerJS[] = R"(
  function verifyData(data) {
    if (data.byteLength != 16)
      return `Improper byteLength: ${data.byteLength}`;

    const bufView = new Uint8Array(data);
    for (let i = 0; i < 16; i++) {
      if (bufView[i] != i % 2) {
        return `Data mismatch at index ${i}: Expected: ${i % 2}, got: ${
            bufView[i]}`;
      }
    }

    return 'PASS';
  }

  self.addEventListener('message', e => {
    try {
      postMessage(verifyData(e.data));
    } catch (e) {
      postMessage(e.message);
    }
  });
)";

constexpr char kBackgroundJS_SabAllowed[] = R"(
  chrome.test.runTests([
    function sendSharedArrayBufferToWorker() {
      let sab = new SharedArrayBuffer(16);
      let bufView = new Uint8Array(sab);
      for (let i = 0; i < 16; i++)
        bufView[i] = (i % 2);

      const workerUrl = chrome.runtime.getURL('worker.js');
      let worker = new Worker(workerUrl);

      worker.onmessage = e => {
        chrome.test.assertEq('PASS', e.data);
        chrome.test.succeed();
      };

      worker.postMessage(sab);
      chrome.test.assertEq(16, sab.byteLength);

      // The worker will ack on receiving the SharedArrayBuffer causing the test
      // to terminate.
    }
  ]);
)";

#endif

// Parameterized on tuple of
// <is_sab_allowed_unconditionally, is_cross_origin_isolated, is_platform_app>.
class SharedArrayBufferTest
    : public ExtensionApiTest,
      public ::testing::WithParamInterface<std::tuple<bool, bool>> {
 public:

  TestExtensionDir& test_dir() { return test_dir_; }

 private:
  TestExtensionDir test_dir_;
};

IN_PROC_BROWSER_TEST_P(SharedArrayBufferTest, TransferToWorker) {
=======
using SharedArrayBufferTest = ExtensionApiTest;

// Ensures extensions can use the SharedArrayBuffer API.
IN_PROC_BROWSER_TEST_F(SharedArrayBufferTest, TransferToWorker) {
>>>>>>> chromium
  ASSERT_TRUE(StartEmbeddedTestServer());
  ASSERT_TRUE(RunExtensionTest("shared_array_buffers")) << message_;
}

<<<<<<< HEAD
  bool is_cross_origin_isolated;
  bool is_platform_app;
  std::tie(is_cross_origin_isolated, is_platform_app) = GetParam();

  auto builder = base::Value::Dict()
                     .Set("manifest_version", 2)
                     .Set("name", "SharedArrayBuffer")
                     .Set("version", "1.1");

  if (is_cross_origin_isolated) {
    builder.Set("cross_origin_opener_policy",
                base::Value::Dict().Set("value", "same-origin"));
    builder.Set("cross_origin_embedder_policy",
                base::Value::Dict().Set("value", "require-corp"));
  }

  base::Value::Dict background_builder;
  background_builder.Set("scripts",
                         base::Value::List().Append("background.js"));

  if (is_platform_app) {
    builder.Set("app", base::Value::Dict().Set("background",
                                               std::move(background_builder)));
  } else {
    builder.Set("background", std::move(background_builder));
  }

  test_dir().WriteManifest(builder);

#if BUILDFLAG(IS_ANDROID)
  test_dir().WriteFile(FILE_PATH_LITERAL("background.js"),
                       kBackgroundJS_SabDisallowed);
#else
  test_dir().WriteFile(FILE_PATH_LITERAL("background.js"),
                       kBackgroundJS_SabAllowed);
  test_dir().WriteFile(FILE_PATH_LITERAL("worker.js"), kWorkerJS);
#endif

  ASSERT_TRUE(RunExtensionTest(test_dir().Pack(),
                               {.launch_as_platform_app = is_platform_app},
                               {} /* load_options */))
      << message_;
}

INSTANTIATE_TEST_SUITE_P(
    ,
    SharedArrayBufferTest,
    ::testing::Combine(::testing::Bool(), ::testing::Bool()),
    [](const testing::TestParamInfo<std::tuple<bool, bool>>& info) {
      bool is_cross_origin_isolated;
      bool is_platform_app;
      std::tie(is_cross_origin_isolated, is_platform_app) = info.param;
      return base::StringPrintf("%s_%s",
                                is_cross_origin_isolated ? "COI" : "NonCOI",
                                is_platform_app ? "App" : "Extension");
    });

=======
// Ensures platform apps can use the SharedArrayBuffer API.
IN_PROC_BROWSER_TEST_F(SharedArrayBufferTest, TransferToWorker_PlatformApp) {
  ASSERT_TRUE(StartEmbeddedTestServer());
  ASSERT_TRUE(RunExtensionTest("shared_array_buffers_platform_app",
                               {.launch_as_platform_app = true}))
      << message_;
}

>>>>>>> chromium
}  // namespace extensions
