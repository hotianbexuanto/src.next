// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/memory/ptr_util.h"
#include "base/path_service.h"
#include "base/threading/thread_restrictions.h"
#include "base/values.h"
#include "build/build_config.h"
#include "chrome/browser/extensions/extension_apitest.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/common/webui_url_constants.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/guest_view/browser/guest_view_manager_delegate.h"
#include "components/guest_view/browser/test_guest_view_manager.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/content_features.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "extensions/browser/api/extensions_api_client.h"
#include "extensions/browser/event_router.h"
#include "extensions/common/api/test.h"
#include "extensions/common/extension.h"
#include "extensions/test/extension_test_message_listener.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace extensions {

namespace OnMessage = api::test::OnMessage;

namespace {

#if !BUILDFLAG(IS_WIN)  // flaky http://crbug.com/530722

// Tests running extension APIs on WebUI.
class ExtensionWebUITest : public ExtensionApiTest {
 protected:
  testing::AssertionResult RunTest(const char* name,
                                   const GURL& page_url,
                                   bool expected_result) {
    std::string script;
    {
      base::ScopedAllowBlockingForTesting allow_blocking;
      // Tests are located in chrome/test/data/extensions/webui/$(name).
      base::FilePath path;
      base::PathService::Get(chrome::DIR_TEST_DATA, &path);
      path =
          path.AppendASCII("extensions").AppendASCII("webui").AppendASCII(name);

      // Read the test.
      if (!base::PathExists(path))
        return testing::AssertionFailure() << "Couldn't find " << path.value();
      base::ReadFileToString(path, &script);
      script = "(function(){'use strict';" + script + "}());";
    }

    // Run the test.
    bool actual_result = false;
    ui_test_utils::NavigateToURL(browser(), page_url);
    content::RenderFrameHost* webui =
        browser()->tab_strip_model()->GetActiveWebContents()->GetMainFrame();
    if (!webui)
      return testing::AssertionFailure() << "Failed to navigate to WebUI";
    CHECK(content::ExecuteScriptAndExtractBool(webui, script, &actual_result));
    return (expected_result == actual_result)
               ? testing::AssertionSuccess()
               : (testing::AssertionFailure() << "Check console output");
  }

  testing::AssertionResult RunTestOnExtensionsPage(const char* name) {
    return RunTest(name, GURL("chrome://extensions"), true);
  }

  testing::AssertionResult RunTestOnAboutPage(const char* name) {
    // chrome://about is an innocuous page that doesn't have any bindings.
    // Tests should fail.
    return RunTest(name, GURL("chrome://about"), false);
  }
};

<<<<<<< HEAD
// Tests running within an <extensionoptions>.
class ExtensionWebUIEmbeddedOptionsTest
    : public ExtensionWebUITest,
      public testing::WithParamInterface<bool> {
=======
// Tests running within an <extensionoptions> WebContents.
class ExtensionWebUIEmbeddedOptionsTest : public ExtensionWebUITest {
>>>>>>> chromium
 public:
  static std::string DescribeParams(
      const testing::TestParamInfo<ParamType>& info) {
    return info.param ? "MPArch" : "InnerWebContents";
  }

  ExtensionWebUIEmbeddedOptionsTest() {
    scoped_feature_list_.InitWithFeatureState(features::kGuestViewMPArch,
                                              GetParam());
  }

  void SetUpOnMainThread() override {
    ExtensionWebUITest::SetUpOnMainThread();
    guest_view::GuestViewManager::set_factory_for_testing(
        &test_guest_view_manager_factory_);
    test_guest_view_manager_ = static_cast<guest_view::TestGuestViewManager*>(
        guest_view::GuestViewManager::CreateWithDelegate(
            browser()->profile(),
            ExtensionsAPIClient::Get()->CreateGuestViewManagerDelegate(
                browser()->profile())));
  }

  void TearDownOnMainThread() override {
    test_guest_view_manager_ = nullptr;
    ExtensionWebUITest::TearDownOnMainThread();
  }

 protected:
  // Loads |extension|'s options page in an <extensionoptions> and returns the
  // <extensionoptions>'s WebContents.
  content::WebContents* OpenExtensionOptions(const Extension* extension) {
    ui_test_utils::NavigateToURL(browser(),
                                 GURL(chrome::kChromeUIExtensionsURL));
    content::WebContents* webui =
        browser()->tab_strip_model()->GetActiveWebContents();

    EXPECT_EQ(0U, test_guest_view_manager_->num_guests_created());

<<<<<<< HEAD
    EXPECT_TRUE(content::ExecJs(
        webui, content::JsReplace(
                   "(() => {"
                   "  let extensionoptions = "
                   "      document.createElement('extensionoptions');"
                   "  extensionoptions.extension = $1;"
                   "  return new Promise((resolve) => {"
                   "    extensionoptions.addEventListener('load', () => {"
                   "      resolve();"
                   "    });"
                   "    document.body.appendChild(extensionoptions);"
                   "  });"
                   "})();",
                   extension->id())));

    guest_view::GuestViewBase* guest_view =
        test_guest_view_manager_->WaitForSingleGuestViewCreated();
    EXPECT_TRUE(guest_view);
    test_guest_view_manager_->WaitUntilAttached(guest_view);
=======
    EXPECT_TRUE(content::ExecuteScript(
        webui,
        content::JsReplace(
            "let extensionoptions = document.createElement('extensionoptions');"
            "extensionoptions.extension = $1;"
            "document.body.appendChild(extensionoptions);",
            extension->id())));

    content::WebContents* guest_web_contents =
        test_guest_view_manager_->WaitForSingleGuestCreated();
    EXPECT_TRUE(guest_web_contents);
    EXPECT_TRUE(content::WaitForLoadStop(guest_web_contents));
>>>>>>> chromium

    return guest_web_contents;
  }

 private:
  guest_view::TestGuestViewManagerFactory test_guest_view_manager_factory_;
<<<<<<< HEAD
  raw_ptr<guest_view::TestGuestViewManager> test_guest_view_manager_ = nullptr;
  base::test::ScopedFeatureList scoped_feature_list_;
};

INSTANTIATE_TEST_SUITE_P(/* no prefix */,
                         ExtensionWebUIEmbeddedOptionsTest,
                         testing::Bool(),
                         ExtensionWebUIEmbeddedOptionsTest::DescribeParams);
=======
  guest_view::TestGuestViewManager* test_guest_view_manager_ = nullptr;
};

#if !defined(OS_WIN)  // flaky http://crbug.com/530722
>>>>>>> chromium

IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, SanityCheckAvailableAPIs) {
  ASSERT_TRUE(RunTestOnExtensionsPage("sanity_check_available_apis.js"));
}

IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, SanityCheckUnavailableAPIs) {
  ASSERT_TRUE(RunTestOnAboutPage("sanity_check_available_apis.js"));
}

// Tests chrome.test.sendMessage, which exercises WebUI making a
// function call and receiving a response.
IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, SendMessage) {
  ExtensionTestMessageListener ping_listener("ping", true);

  ASSERT_TRUE(RunTestOnExtensionsPage("send_message.js"));
  ASSERT_TRUE(ping_listener.WaitUntilSatisfied());

  ExtensionTestMessageListener result_listener(false);
  ping_listener.Reply("pong");

  ASSERT_TRUE(result_listener.WaitUntilSatisfied());
  EXPECT_EQ("true", result_listener.message());
}

// Tests chrome.runtime.onMessage, which exercises WebUI registering and
// receiving an event.
IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, OnMessage) {
  ASSERT_TRUE(RunTestOnExtensionsPage("on_message.js"));

  ExtensionTestMessageListener result_listener(false);

  OnMessage::Info info;
  info.data = "hi";
  info.last_message = true;
  EventRouter::Get(profile())->BroadcastEvent(base::WrapUnique(
      new Event(events::RUNTIME_ON_MESSAGE, OnMessage::kEventName,
                OnMessage::Create(info))));

  ASSERT_TRUE(result_listener.WaitUntilSatisfied());
  EXPECT_EQ("true", result_listener.message());
}

// Tests chrome.runtime.lastError, which exercises WebUI accessing a property
// on an API which it doesn't actually have access to. A bindings test really.
IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, RuntimeLastError) {
  ExtensionTestMessageListener ping_listener("ping", true);

  ASSERT_TRUE(RunTestOnExtensionsPage("runtime_last_error.js"));
  ASSERT_TRUE(ping_listener.WaitUntilSatisfied());

  ExtensionTestMessageListener result_listener(false);
  ping_listener.ReplyWithError("unknown host");
  ASSERT_TRUE(result_listener.WaitUntilSatisfied());
  EXPECT_EQ("true", result_listener.message());
}

<<<<<<< HEAD
IN_PROC_BROWSER_TEST_P(ExtensionWebUIEmbeddedOptionsTest,
                       CanEmbedExtensionOptions) {
  ExtensionTestMessageListener ready_listener("ready",
                                              ReplyBehavior::kWillReply);
=======
IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, CanEmbedExtensionOptions) {
  ExtensionTestMessageListener ready_listener("ready", true);
>>>>>>> chromium

  const Extension* extension =
      LoadExtension(test_data_dir_.AppendASCII("extension_options")
                        .AppendASCII("extension_with_options_page"));
  ASSERT_TRUE(extension);

  ASSERT_TRUE(RunTestOnExtensionsPage("can_embed_extension_options.js"));
  ASSERT_TRUE(ready_listener.WaitUntilSatisfied());

  ExtensionTestMessageListener load_listener("load", false);
  ready_listener.Reply(extension->id());
  ASSERT_TRUE(load_listener.WaitUntilSatisfied());
}

<<<<<<< HEAD
// Tests that an <extensionoptions> guest view can access appropriate APIs,
// including chrome.storage (semi-privileged; exposed to trusted contexts and
// contexts like content scripts and embedded resources in platform apps) and
// chrome.tabs (privileged; only exposed to trusted contexts).
IN_PROC_BROWSER_TEST_P(ExtensionWebUIEmbeddedOptionsTest,
                       ExtensionOptionsCanAccessAppropriateAPIs) {
=======
// Tests that an <extensionoptions> guest view can access the chrome.storage
// API, a privileged extension API.
IN_PROC_BROWSER_TEST_F(ExtensionWebUIEmbeddedOptionsTest,
                       ExtensionOptionsCanAccessStorage) {
>>>>>>> chromium
  const Extension* extension =
      LoadExtension(test_data_dir_.AppendASCII("extension_options")
                        .AppendASCII("extension_with_options_page"));
  ASSERT_TRUE(extension);

  content::WebContents* guest_web_contents = OpenExtensionOptions(extension);

  const std::string storage_key = "test";
  const int storage_value = 42;

  EXPECT_TRUE(content::ExecuteScript(
      guest_web_contents,
      content::JsReplace("var onChangedPromise = new Promise((resolve) => {"
                         "  chrome.storage.onChanged.addListener((change) => {"
                         "    resolve(change[$1].newValue);"
                         "  });"
                         "});",
                         storage_key)));

  std::string set_result;
  EXPECT_TRUE(content::ExecuteScriptAndExtractString(
      guest_web_contents,
      content::JsReplace(
          "try {"
          "  chrome.storage.local.set({$1: $2}, () => {"
          "    domAutomationController.send("
          "        chrome.runtime.lastError ?"
          "            chrome.runtime.lastError.message : 'success');"
          "  });"
          "} catch (e) {"
          "  domAutomationController.send(e.name + ': ' + e.message);"
          "}",
          storage_key, storage_value),
      &set_result));
  ASSERT_EQ("success", set_result);

  int actual_value = 0;
  EXPECT_TRUE(content::ExecuteScriptAndExtractInt(
      guest_web_contents,
      content::JsReplace("chrome.storage.local.get((storage) => {"
                         "  domAutomationController.send(storage[$1]);"
                         "});",
                         storage_key),
      &actual_value));
  EXPECT_EQ(storage_value, actual_value);

  EXPECT_TRUE(content::ExecuteScriptAndExtractInt(
      guest_web_contents,
      "onChangedPromise.then((newValue) => {"
      "  domAutomationController.send(newValue);"
      "});",
      &actual_value));
  EXPECT_EQ(storage_value, actual_value);
}

IN_PROC_BROWSER_TEST_P(ExtensionWebUIEmbeddedOptionsTest,
                       ExtensionOptionsExternalLinksOpenInNewTab) {
  // TODO(crbug.com/40202416): Implement new window creation under MPArch.
  if (base::FeatureList::IsEnabled(features::kGuestViewMPArch)) {
    GTEST_SKIP() << "MPArch implementation skipped. https://crbug.com/40202416";
  }

  const Extension* extension =
      LoadExtension(test_data_dir_.AppendASCII("extension_options")
                        .AppendASCII("extension_with_options_page"));
  ASSERT_TRUE(extension);

  content::WebContents* guest_web_contents = OpenExtensionOptions(extension);

  content::WebContentsAddedObserver new_contents_observer;
  EXPECT_TRUE(content::ExecuteScript(
      guest_web_contents, "document.getElementById('link').click();"));
  content::WebContents* new_contents = new_contents_observer.GetWebContents();
  EXPECT_NE(TabStripModel::kNoTab,
            browser()->tab_strip_model()->GetIndexOfWebContents(new_contents));
}

<<<<<<< HEAD
IN_PROC_BROWSER_TEST_P(ExtensionWebUIEmbeddedOptionsTest,
                       ReceivesExtensionOptionsOnClose) {
  ExtensionTestMessageListener ready_listener("ready",
                                              ReplyBehavior::kWillReply);
=======
IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, ReceivesExtensionOptionsOnClose) {
  ExtensionTestMessageListener ready_listener("ready", true);
>>>>>>> chromium

  const Extension* extension =
      InstallExtension(test_data_dir_.AppendASCII("extension_options")
          .AppendASCII("close_self"), 1);
  ASSERT_TRUE(extension);

  ASSERT_TRUE(
      RunTestOnExtensionsPage("receives_extension_options_on_close.js"));
  ASSERT_TRUE(ready_listener.WaitUntilSatisfied());

  ExtensionTestMessageListener onclose_listener("onclose received", false);
  ready_listener.Reply(extension->id());
  ASSERT_TRUE(onclose_listener.WaitUntilSatisfied());
}

// Regression test for crbug.com/414526.
//
// Same setup as CanEmbedExtensionOptions but disable the extension before
// embedding.
<<<<<<< HEAD
IN_PROC_BROWSER_TEST_P(ExtensionWebUIEmbeddedOptionsTest,
                       EmbedDisabledExtension) {
  ExtensionTestMessageListener ready_listener("ready",
                                              ReplyBehavior::kWillReply);
=======
IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, EmbedDisabledExtension) {
  ExtensionTestMessageListener ready_listener("ready", true);
>>>>>>> chromium

  std::string extension_id;
  {
    const Extension* extension =
        LoadExtension(test_data_dir_.AppendASCII("extension_options")
                          .AppendASCII("extension_with_options_page"));
    ASSERT_TRUE(extension);
    extension_id = extension->id();
    DisableExtension(extension_id);
  }

  ASSERT_TRUE(RunTestOnExtensionsPage("can_embed_extension_options.js"));
  ASSERT_TRUE(ready_listener.WaitUntilSatisfied());

  ExtensionTestMessageListener create_failed_listener("createfailed", false);
  ready_listener.Reply(extension_id);
  ASSERT_TRUE(create_failed_listener.WaitUntilSatisfied());
}

IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, EmbedInvalidExtension) {
  ExtensionTestMessageListener ready_listener("ready", true);

  const std::string extension_id = "thisisprobablynotrealextensionid";

  ASSERT_TRUE(RunTestOnExtensionsPage("can_embed_extension_options.js"));
  ASSERT_TRUE(ready_listener.WaitUntilSatisfied());

  ExtensionTestMessageListener create_failed_listener("createfailed", false);
  ready_listener.Reply(extension_id);
  ASSERT_TRUE(create_failed_listener.WaitUntilSatisfied());
}

IN_PROC_BROWSER_TEST_F(ExtensionWebUITest, EmbedExtensionWithoutOptionsPage) {
  ExtensionTestMessageListener ready_listener("ready", true);

  const Extension* extension =
      LoadExtension(test_data_dir_.AppendASCII("extension_options")
                        .AppendASCII("extension_without_options_page"));
  ASSERT_TRUE(extension);

  ASSERT_TRUE(RunTestOnExtensionsPage("can_embed_extension_options.js"));
  ASSERT_TRUE(ready_listener.WaitUntilSatisfied());

  ExtensionTestMessageListener create_failed_listener("createfailed", false);
  ready_listener.Reply(extension->id());
  ASSERT_TRUE(create_failed_listener.WaitUntilSatisfied());
}

#endif

}  // namespace

}  // namespace extensions
