// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/extensions/tab_helper.h"

#include "base/run_loop.h"
#include "chrome/browser/extensions/extension_service.h"
#include "chrome/browser/extensions/extension_service_test_with_install.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/test/web_contents_tester.h"

namespace extensions {

<<<<<<< HEAD
class TabHelperUnitTest : public ExtensionServiceTestWithInstall {
 public:
  void SetUp() override {
    ExtensionServiceTestWithInstall::SetUp();
    InitializeEmptyExtensionService();

    std::unique_ptr<content::WebContents> web_contents(
        content::WebContentsTester::CreateTestWebContents(profile(), nullptr));
    web_contents_tester_ = content::WebContentsTester::For(web_contents.get());
    TabHelper::CreateForWebContents(web_contents.get());
    tab_helper_ = TabHelper::FromWebContents(web_contents.get());
    browser()->tab_strip_model()->AppendWebContents(std::move(web_contents),
                                                    true);

    permissions_manager_ = PermissionsManager::Get(profile());
  }

  void TearDown() override {
    tab_helper_ = nullptr;
    web_contents_tester_ = nullptr;
    // Remove any tabs in the tab strip to avoid test crashes.
    if (browser_) {
      while (!browser_->tab_strip_model()->empty()) {
        browser_->tab_strip_model()->DetachAndDeleteWebContentsAt(0);
      }
    }
    ExtensionServiceTestBase::TearDown();
  }

  Browser* browser() {
    if (!browser_) {
      Browser::CreateParams params(profile(), true);
      browser_window_ = std::make_unique<TestBrowserWindow>();
      params.window = browser_window_.get();
      browser_.reset(Browser::Create(params));
    }
    return browser_.get();
  }

  content::WebContentsTester* web_contents_tester() {
    return web_contents_tester_;
  }

  TabHelper* tab_helper() { return tab_helper_; }

  PermissionsManager* permissions_manager() { return permissions_manager_; }

 private:
  // The browser and accompaying window.
  std::unique_ptr<Browser> browser_;
  std::unique_ptr<TestBrowserWindow> browser_window_;

  raw_ptr<content::WebContentsTester> web_contents_tester_;
  raw_ptr<TabHelper> tab_helper_;
  raw_ptr<PermissionsManager> permissions_manager_;
};

TEST_F(TabHelperUnitTest, ClearsExtensionOnUnload) {
=======
TEST_F(ExtensionServiceTestWithInstall, TabHelperClearsExtensionOnUnload) {
  InitializeEmptyExtensionService();
>>>>>>> chromium
  const Extension* extension =
      PackAndInstallCRX(data_dir().AppendASCII("hosted_app"), INSTALL_NEW);
  ASSERT_TRUE(extension);
  std::unique_ptr<content::WebContents> web_contents(
      content::WebContentsTester::CreateTestWebContents(profile(), nullptr));
  TabHelper::CreateForWebContents(web_contents.get());
  TabHelper* tab_helper = TabHelper::FromWebContents(web_contents.get());
  tab_helper->SetExtensionApp(extension);
  EXPECT_EQ(extension->id(), tab_helper->GetExtensionAppId());
  EXPECT_TRUE(tab_helper->is_app());
  service()->UnloadExtension(extension->id(),
                             UnloadedExtensionReason::TERMINATE);
  base::RunLoop().RunUntilIdle();
  EXPECT_EQ(ExtensionId(), tab_helper->GetExtensionAppId());
}

}  // namespace extensions
