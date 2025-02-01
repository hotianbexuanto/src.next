// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/chrome_content_browser_client.h"

#include <memory>
#include <vector>

#include "base/bind.h"
#include "base/command_line.h"
<<<<<<< HEAD
#include "base/functional/bind.h"
#include "base/memory/raw_ptr.h"
#include "base/strings/strcat.h"
=======
#include "base/macros.h"
#include "base/no_destructor.h"
>>>>>>> chromium
#include "base/strings/stringprintf.h"
#include "base/strings/utf_string_conversions.h"
#include "base/test/scoped_feature_list.h"
#include "build/build_config.h"
#include "chrome/browser/browser_features.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/custom_handlers/protocol_handler_registry.h"
#include "chrome/browser/custom_handlers/protocol_handler_registry_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/search/instant_service.h"
#include "chrome/browser/search/instant_service_factory.h"
#include "chrome/browser/search/search.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/search/instant_test_base.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/common/chrome_features.h"
#include "chrome/common/chrome_switches.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/url_constants.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
<<<<<<< HEAD
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/common/features.h"
#include "components/content_settings/core/common/pref_names.h"
#include "components/custom_handlers/protocol_handler.h"
#include "components/custom_handlers/protocol_handler_registry.h"
#include "components/enterprise/buildflags/buildflags.h"
=======
>>>>>>> chromium
#include "components/network_session_configurator/common/network_switches.h"
#include "components/policy/core/common/cloud/cloud_policy_constants.h"
#include "components/prefs/pref_service.h"
#include "components/site_isolation/site_isolation_policy.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/content_client.h"
#include "content/public/common/content_features.h"
#include "content/public/common/content_switches.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "content/public/test/test_navigation_observer.h"
#include "content/public/test/url_loader_interceptor.h"
#include "net/dns/mock_host_resolver.h"
#include "net/http/http_status_code.h"
#include "net/test/embedded_test_server/embedded_test_server.h"
#include "net/test/embedded_test_server/http_request.h"
#include "net/test/embedded_test_server/http_response.h"
#include "ui/native_theme/native_theme.h"
#include "ui/native_theme/test_native_theme.h"
#include "url/gurl.h"
#include "url/origin.h"

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "extensions/common/constants.h"
#include "extensions/common/extension_urls.h"
#include "url/url_constants.h"
#endif

#if defined(OS_MAC)
#include "chrome/test/base/launchservices_utils_mac.h"
#endif

namespace {

// Use a test class with SetUpCommandLine to ensure the flag is sent to the
// first renderer process.
class ChromeContentBrowserClientBrowserTest : public InProcessBrowserTest {
 public:
  ChromeContentBrowserClientBrowserTest() = default;

  void SetUpCommandLine(base::CommandLine* command_line) override {
    content::IsolateAllSitesForTesting(command_line);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeContentBrowserClientBrowserTest);
};

// Test that a basic navigation works in --site-per-process mode.  This prevents
// regressions when that mode calls out into the ChromeContentBrowserClient,
// such as http://crbug.com/164223.
IN_PROC_BROWSER_TEST_F(ChromeContentBrowserClientBrowserTest,
                       SitePerProcessNavigation) {
  ASSERT_TRUE(embedded_test_server()->Start());
  const GURL url(embedded_test_server()->GetURL("/title1.html"));

  ui_test_utils::NavigateToURL(browser(), url);
  content::NavigationEntry* entry = browser()
                                        ->tab_strip_model()
                                        ->GetWebContentsAt(0)
                                        ->GetController()
                                        .GetLastCommittedEntry();

  ASSERT_TRUE(entry != NULL);
  EXPECT_EQ(url, entry->GetURL());
  EXPECT_EQ(url, entry->GetVirtualURL());
}

// Helper class to mark "https://ntp.com/" as an isolated origin.
class IsolatedOriginNTPBrowserTest : public InProcessBrowserTest,
                                     public InstantTestBase {
 public:
  IsolatedOriginNTPBrowserTest() = default;

  void SetUpCommandLine(base::CommandLine* command_line) override {
    ASSERT_TRUE(https_test_server().InitializeAndListen());

    // Mark ntp.com (with an appropriate port from the test server) as an
    // isolated origin.
    GURL isolated_url(https_test_server().GetURL("ntp.com", "/"));
    command_line->AppendSwitchASCII(switches::kIsolateOrigins,
                                    isolated_url.spec());
    command_line->AppendSwitch(switches::kIgnoreCertificateErrors);
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    host_resolver()->AddRule("*", "127.0.0.1");
    https_test_server().StartAcceptingConnections();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(IsolatedOriginNTPBrowserTest);
};

// Verifies that when the remote NTP URL has an origin which is also marked as
// an isolated origin (i.e., requiring a dedicated process), the NTP URL
// still loads successfully, and the resulting process is marked as an Instant
// process.  See https://crbug.com/755595.
IN_PROC_BROWSER_TEST_F(IsolatedOriginNTPBrowserTest,
                       IsolatedOriginDoesNotInterfereWithNTP) {
  GURL base_url =
      https_test_server().GetURL("ntp.com", "/instant_extended.html");
  GURL ntp_url =
      https_test_server().GetURL("ntp.com", "/instant_extended_ntp.html");
  SetupInstant(browser()->profile(), base_url, ntp_url);

  // Sanity check that a SiteInstance for a generic ntp.com URL requires a
  // dedicated process.
  content::BrowserContext* context = browser()->profile();
  GURL isolated_url(https_test_server().GetURL("ntp.com", "/title1.html"));
  scoped_refptr<content::SiteInstance> site_instance =
      content::SiteInstance::CreateForURL(context, isolated_url);
  EXPECT_TRUE(site_instance->RequiresDedicatedProcess());
  // Verify the isolated origin does not receive an NTP site URL scheme.
  EXPECT_FALSE(
      site_instance->GetSiteURL().SchemeIs(chrome::kChromeSearchScheme));

  // The site URL for the NTP URL should resolve to a chrome-search:// URL via
  // GetEffectiveURL(), even if the NTP URL matches an isolated origin.
  scoped_refptr<content::SiteInstance> ntp_site_instance =
      content::SiteInstance::CreateForURL(context, ntp_url);
  EXPECT_TRUE(
      ntp_site_instance->GetSiteURL().SchemeIs(chrome::kChromeSearchScheme));

  // Navigate to the NTP URL and verify that the resulting process is marked as
  // an Instant process.
  ui_test_utils::NavigateToURL(browser(), ntp_url);
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  InstantService* instant_service =
      InstantServiceFactory::GetForProfile(browser()->profile());
  EXPECT_TRUE(instant_service->IsInstantProcess(
<<<<<<< HEAD
      contents->GetPrimaryMainFrame()->GetProcess()->GetDeprecatedID()));
  EXPECT_EQ(contents->GetPrimaryMainFrame()->GetSiteInstance()->GetSiteURL(),
=======
      contents->GetMainFrame()->GetProcess()->GetID()));
  EXPECT_EQ(contents->GetMainFrame()->GetSiteInstance()->GetSiteURL(),
>>>>>>> chromium
            ntp_site_instance->GetSiteURL());

  // Navigating to a non-NTP URL on ntp.com should not result in an Instant
  // process.
  ui_test_utils::NavigateToURL(browser(), isolated_url);
  EXPECT_FALSE(instant_service->IsInstantProcess(
<<<<<<< HEAD
      contents->GetPrimaryMainFrame()->GetProcess()->GetDeprecatedID()));
  EXPECT_EQ(contents->GetPrimaryMainFrame()->GetSiteInstance()->GetSiteURL(),
=======
      contents->GetMainFrame()->GetProcess()->GetID()));
  EXPECT_EQ(contents->GetMainFrame()->GetSiteInstance()->GetSiteURL(),
>>>>>>> chromium
            site_instance->GetSiteURL());
}

// Helper class to test window creation from NTP.
class OpenWindowFromNTPBrowserTest : public InProcessBrowserTest,
                                     public InstantTestBase {
 public:
  OpenWindowFromNTPBrowserTest() = default;

  void SetUpCommandLine(base::CommandLine* command_line) override {
    command_line->AppendSwitch(switches::kIgnoreCertificateErrors);
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    host_resolver()->AddRule("*", "127.0.0.1");
    ASSERT_TRUE(https_test_server().InitializeAndListen());
    https_test_server().StartAcceptingConnections();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(OpenWindowFromNTPBrowserTest);
};

// Test checks that navigations from NTP tab to URLs with same host as NTP but
// different path do not reuse NTP SiteInstance. See https://crbug.com/859062
// for details.
IN_PROC_BROWSER_TEST_F(OpenWindowFromNTPBrowserTest,
                       TransferFromNTPCreateNewTab) {
  GURL search_url =
      https_test_server().GetURL("ntp.com", "/instant_extended.html");
  GURL ntp_url =
      https_test_server().GetURL("ntp.com", "/instant_extended_ntp.html");
  SetupInstant(browser()->profile(), search_url, ntp_url);

  // Navigate to the NTP URL and verify that the resulting process is marked as
  // an Instant process.
  ui_test_utils::NavigateToURL(browser(), ntp_url);
  content::WebContents* ntp_tab =
      browser()->tab_strip_model()->GetActiveWebContents();
  InstantService* instant_service =
      InstantServiceFactory::GetForProfile(browser()->profile());
  EXPECT_TRUE(instant_service->IsInstantProcess(
<<<<<<< HEAD
      ntp_tab->GetPrimaryMainFrame()->GetProcess()->GetDeprecatedID()));
=======
      ntp_tab->GetMainFrame()->GetProcess()->GetID()));
>>>>>>> chromium

  // Execute script that creates new window from ntp tab with
  // ntp.com/title1.html as target url. Host is same as remote-ntp host, yet
  // path is different.
  GURL generic_url(https_test_server().GetURL("ntp.com", "/title1.html"));
  content::TestNavigationObserver opened_tab_observer(nullptr);
  opened_tab_observer.StartWatchingNewWebContents();
  EXPECT_TRUE(
      ExecuteScript(ntp_tab, "window.open('" + generic_url.spec() + "');"));
  opened_tab_observer.Wait();
  ASSERT_EQ(2, browser()->tab_strip_model()->count());

  content::WebContents* opened_tab =
      browser()->tab_strip_model()->GetActiveWebContents();

  // Wait until newly opened tab is fully loaded.
  EXPECT_TRUE(WaitForLoadStop(opened_tab));

  EXPECT_NE(opened_tab, ntp_tab);
  EXPECT_EQ(generic_url, opened_tab->GetLastCommittedURL());
  // New created tab should not reside in an Instant process.
  EXPECT_FALSE(instant_service->IsInstantProcess(
<<<<<<< HEAD
      opened_tab->GetPrimaryMainFrame()->GetProcess()->GetDeprecatedID()));
=======
      opened_tab->GetMainFrame()->GetProcess()->GetID()));
>>>>>>> chromium
}

class PrefersColorSchemeTest : public testing::WithParamInterface<bool>,
                               public InProcessBrowserTest {
 protected:
  PrefersColorSchemeTest() : theme_client_(&test_theme_) {
    feature_list_.InitWithFeatureState(features::kWebUIDarkMode, GetParam());
  }

<<<<<<< HEAD
  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    command_line->AppendSwitchASCII(switches::kEnableBlinkFeatures,
                                    "CSSAccentColorKeyword");
  }

  void SetWebAppScope(const GURL web_app_scope) {
    browser_client_.set_web_app_scope(web_app_scope);
    original_client_ = content::SetBrowserClientForTesting(&browser_client_);
    browser()
        ->tab_strip_model()
        ->GetActiveWebContents()
        ->OnWebPreferencesChanged();
  }

  ui::TestNativeTheme test_theme_;

 private:
  class BrowserClientForAccentColorTest : public ChromeContentBrowserClient {
   public:
    explicit BrowserClientForAccentColorTest(const ui::NativeTheme* theme)
        : theme_(theme) {}

    void set_web_app_scope(const GURL& web_app_scope) {
      web_app_scope_ = web_app_scope;
    }

    void OverrideWebPreferences(
        content::WebContents* web_contents,
        content::SiteInstance& main_frame_site,
        blink::web_pref::WebPreferences* web_prefs) override {
      ChromeContentBrowserClient::OverrideWebPreferences(
          web_contents, main_frame_site, web_prefs);

      web_prefs->web_app_scope = web_app_scope_;
    }

   protected:
    const ui::NativeTheme* GetWebTheme() const override { return theme_; }

   private:
    const raw_ptr<const ui::NativeTheme> theme_;
    GURL web_app_scope_;
  };

  BrowserClientForAccentColorTest browser_client_;
  raw_ptr<content::ContentBrowserClient> original_client_ = nullptr;
};

IN_PROC_BROWSER_TEST_F(SystemAccentColorTest,
                       SystemAccentColorKeywordForInstalledWebApp) {
  GURL web_app_scope = ui_test_utils::GetTestUrl(
      base::FilePath(base::FilePath::kCurrentDirectory),
      base::FilePath(FILE_PATH_LITERAL("system-accent-color.html")));
  SetWebAppScope(web_app_scope);
  ui::NativeTheme::GetInstanceForWeb()->set_user_color(
      SkColorSetRGB(135, 115, 10));
  ui::NativeTheme::GetInstanceForWeb()->NotifyOnNativeThemeUpdated();

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), web_app_scope));
  // For installled WebApps we expect System AccentColor keyword resolve to
  // OS-defined accent-color, which are currently pumped for ChromeOS and
  // Windows.
  EXPECT_EQ("rgb(135, 115, 10)",
            EvalJs(browser()->tab_strip_model()->GetActiveWebContents(),
                   base::StringPrintf(
                       "window.getComputedStyle(document.getElementById('"
                       "header_element')).backgroundColor")));
}

IN_PROC_BROWSER_TEST_F(SystemAccentColorTest,
                       SystemAccentColorKeywordForNonWebApp) {
  GURL web_app_scope = ui_test_utils::GetTestUrl(
      base::FilePath(base::FilePath::kCurrentDirectory),
      base::FilePath(FILE_PATH_LITERAL("system-accent-color.html")));
  SetWebAppScope(GURL());
  ui::NativeTheme::GetInstanceForWeb()->set_user_color(
      SkColorSetRGB(135, 115, 10));
  ui::NativeTheme::GetInstanceForWeb()->NotifyOnNativeThemeUpdated();

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), web_app_scope));
  // System AccentColor keyword returns a hard coded value (Shade of blue) for
  // non-installed websites.
  EXPECT_EQ("rgb(0, 117, 255)",
            EvalJs(browser()->tab_strip_model()->GetActiveWebContents(),
                   base::StringPrintf(
                       "window.getComputedStyle(document.getElementById('"
                       "header_element')).backgroundColor")));
}
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_CHROMEOS)

// Test for the state of Forced Colors Mode for a given WebContents across
// various scenarios.
class ForcedColorsTest : public testing::WithParamInterface<bool>,
                         public InProcessBrowserTest {
 protected:
  ForcedColorsTest() : theme_client_(&test_theme_) {}

  ~ForcedColorsTest() override {
    CHECK_EQ(&theme_client_, SetBrowserClientForTesting(original_client_));
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    command_line->AppendSwitchASCII(switches::kEnableBlinkFeatures,
                                    "ForcedColors");
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    original_client_ = SetBrowserClientForTesting(&theme_client_);
  }

 protected:
  ui::TestNativeTheme test_theme_;

 private:
  raw_ptr<content::ContentBrowserClient> original_client_ = nullptr;

  class ChromeContentBrowserClientWithWebTheme
      : public ChromeContentBrowserClient {
   public:
    explicit ChromeContentBrowserClientWithWebTheme(
        const ui::NativeTheme* theme)
        : theme_(theme) {}

   protected:
    const ui::NativeTheme* GetWebTheme() const override { return theme_; }

   private:
    const raw_ptr<const ui::NativeTheme> theme_;
  };

  ChromeContentBrowserClientWithWebTheme theme_client_;
};

IN_PROC_BROWSER_TEST_P(ForcedColorsTest, ForcedColors) {
  test_theme_.set_forced_colors(GetParam());
  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();
  ASSERT_TRUE(ui_test_utils::NavigateToURL(
      browser(), ui_test_utils::GetTestUrl(
                     base::FilePath(base::FilePath::kCurrentDirectory),
                     base::FilePath(FILE_PATH_LITERAL("forced-colors.html")))));
  std::u16string tab_title;
  const char* expected = test_theme_.InForcedColorsMode() ? "active" : "none";
  ASSERT_TRUE(ui_test_utils::GetCurrentTabTitle(browser(), &tab_title));
  EXPECT_EQ(base::ASCIIToUTF16(expected), tab_title);
}

IN_PROC_BROWSER_TEST_P(ForcedColorsTest, ForcedColorsWithBlockList) {
  test_theme_.set_forced_colors(GetParam());

  const char* url = "https://foo.com";
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), GURL(url)));

  // Add url to the page colors block list.
  base::Value::List list;
  list.Append(url);
  Profile* profile = browser()->profile();
  profile->GetPrefs()->SetList(prefs::kPageColorsBlockList, list.Clone());
  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();

  // Forced colors should be `none` when a site is added to the block list.
  EXPECT_EQ(true, EvalJs(browser()->tab_strip_model()->GetActiveWebContents(),
                         base::StringPrintf(
                             "window.matchMedia('(forced-colors: %s)').matches",
                             "none")));

  // Remove url from the page colors block list.
  list.EraseValue(base::Value(url));
  profile->GetPrefs()->SetList(prefs::kPageColorsBlockList, list.Clone());
  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();

  // Forced colors should respect the NativeTheme when a site is removed from
  // the block list.
  const char* expected = test_theme_.InForcedColorsMode() ? "active" : "none";
  EXPECT_EQ(true, EvalJs(browser()->tab_strip_model()->GetActiveWebContents(),
                         base::StringPrintf(
                             "window.matchMedia('(forced-colors: %s)').matches",
                             expected)));
}

INSTANTIATE_TEST_SUITE_P(All, ForcedColorsTest, testing::Bool());

// Helper class to test the Page colors feature. Page colors is a feature that
// simulates Forced colors mode via a browser setting.
class PageColorsBrowserClientTest : public InProcessBrowserTest {
 public:
  PageColorsBrowserClientTest() = default;

  PageColorsBrowserClientTest(const PageColorsBrowserClientTest&) = delete;
  PageColorsBrowserClientTest& operator=(const PageColorsBrowserClientTest&) =
      delete;

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
  }
};

IN_PROC_BROWSER_TEST_F(PageColorsBrowserClientTest,
                       PageColorsAffectsWebContents) {
  browser()->profile()->GetPrefs()->SetBoolean(
      prefs::kApplyPageColorsOnlyOnIncreasedContrast, false);
  browser()->profile()->GetPrefs()->SetInteger(
      prefs::kPageColors, ui::NativeTheme::PageColors::kDusk);

  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), GURL("http://foo.com")));

  // Check that the page colors are applied when Forced Colors is enabled. For
  // the Dusk theme, the color value for Window is 0x2D3236 which corresponds to
  // rgb(45, 50, 54).
  std::string expected_bg_color = "rgb(45, 50, 54)";
  EXPECT_EQ(expected_bg_color,
            EvalJs(browser()->tab_strip_model()->GetActiveWebContents(),
                   "window.getComputedStyle(document.body).getPropertyValue('"
                   "background-color').toString()"));
}

IN_PROC_BROWSER_TEST_F(PageColorsBrowserClientTest,
                       PageColorsAffectsCssPseudoElements) {
  browser()->profile()->GetPrefs()->SetBoolean(
      prefs::kApplyPageColorsOnlyOnIncreasedContrast, false);
  browser()->profile()->GetPrefs()->SetInteger(
      prefs::kPageColors, ui::NativeTheme::PageColors::kDesert);

  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();

  ASSERT_TRUE(ui_test_utils::NavigateToURL(
      browser(), ui_test_utils::GetTestUrl(
                     base::FilePath(base::FilePath::kCurrentDirectory),
                     base::FilePath(FILE_PATH_LITERAL("system-colors.html")))));

  // Check that the right system color is applied for Pseudo elements when
  // Forced Colors is enabled. For the Desert theme, the color value for
  // WindowText is 0x3D3D3D which corresponds to rgb(61, 61, 61).
  std::string expected_element_color = "rgb(61, 61, 61)";
  EXPECT_EQ(expected_element_color,
            EvalJs(browser()->tab_strip_model()->GetActiveWebContents(),
                   "window.getComputedStyle(document.getElementById('icon'), "
                   "'::before')."
                   "getPropertyValue('color').toString()"));
}

// Tests for the preferred color scheme for a given WebContents. The first param
// controls whether the web NativeTheme is light or dark the second controls
// whether the color mode on the associated color provider is light or dark.
class PrefersColorSchemeTest
    : public testing::WithParamInterface<std::tuple<bool, bool>>,
      public InProcessBrowserTest {
 protected:
  PrefersColorSchemeTest()
      : theme_client_(&test_theme_),
        color_provider_source_(GetIsDarkColorProviderColorMode()) {
    test_theme_.SetDarkMode(GetIsDarkNativeTheme());
  }
=======
>>>>>>> chromium
  ~PrefersColorSchemeTest() override {
    CHECK_EQ(&theme_client_, SetBrowserClientForTesting(original_client_));
  }

  const char* ExpectedColorScheme() const {
<<<<<<< HEAD
    const char* color_provider_color_mode =
        GetIsDarkColorProviderColorMode() ? "dark" : "light";
    const char* native_theme_color_mode =
        GetIsDarkNativeTheme() ? "dark" : "light";

    // WebUI's preferred color scheme should reflect the color mode of their
    // associated ColorProvider, and not the preferred color scheme of the web
    // NativeTheme.
    const GURL& last_committed_url = browser()
                                         ->tab_strip_model()
                                         ->GetActiveWebContents()
                                         ->GetLastCommittedURL();
    if (content::HasWebUIScheme(last_committed_url)) {
      return color_provider_color_mode;
    }

    // Pages in incognito profiles should follow the device theme.
    if (browser()->profile()->IsIncognitoProfile()) {
      return native_theme_color_mode;
    }

    // Pages in regular profiles should follow the browser theme, reflected by
    // the color mode of the associated ColorProvider, if the feature is
    // enabled.
    return base::FeatureList::IsEnabled(
               features::kContentUsesBrowserThemeColorMode)
               ? color_provider_color_mode
               : native_theme_color_mode;
=======
    return GetParam() ? "dark" : "light";
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    command_line->AppendSwitchASCII(switches::kEnableBlinkFeatures,
                                    "MediaQueryPrefersColorScheme");
>>>>>>> chromium
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    original_client_ = SetBrowserClientForTesting(&theme_client_);
  }

 protected:
  ui::TestNativeTheme test_theme_;

 private:
  content::ContentBrowserClient* original_client_ = nullptr;

  class ChromeContentBrowserClientWithWebTheme
      : public ChromeContentBrowserClient {
   public:
    explicit ChromeContentBrowserClientWithWebTheme(
        const ui::NativeTheme* theme)
        : theme_(theme) {}

   protected:
    const ui::NativeTheme* GetWebTheme() const override { return theme_; }

   private:
    const ui::NativeTheme* const theme_;
  };

  base::test::ScopedFeatureList feature_list_;
  ChromeContentBrowserClientWithWebTheme theme_client_;
};

IN_PROC_BROWSER_TEST_P(PrefersColorSchemeTest, PrefersColorScheme) {
  test_theme_.SetDarkMode(GetParam());
  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();
  ui_test_utils::NavigateToURL(
      browser(),
      ui_test_utils::GetTestUrl(
          base::FilePath(base::FilePath::kCurrentDirectory),
          base::FilePath(FILE_PATH_LITERAL("prefers-color-scheme.html"))));
  std::u16string tab_title;
  ASSERT_TRUE(ui_test_utils::GetCurrentTabTitle(browser(), &tab_title));
  EXPECT_EQ(base::ASCIIToUTF16(ExpectedColorScheme()), tab_title);
}

IN_PROC_BROWSER_TEST_P(PrefersColorSchemeTest, FeatureOverridesChromeSchemes) {
  test_theme_.SetDarkMode(true);
  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();

  ui_test_utils::NavigateToURL(browser(), GURL(chrome::kChromeUIDownloadsURL));

  bool matches;
  ASSERT_TRUE(ExecuteScriptAndExtractBool(
      browser()->tab_strip_model()->GetActiveWebContents(),
      base::StringPrintf("window.domAutomationController.send(window."
                         "matchMedia('(prefers-color-scheme: %s)').matches)",
                         ExpectedColorScheme()),
      &matches));
  EXPECT_TRUE(matches);
}

#if BUILDFLAG(ENABLE_EXTENSIONS)
IN_PROC_BROWSER_TEST_P(PrefersColorSchemeTest, FeatureOverridesPdfUI) {
  test_theme_.SetDarkMode(true);
  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();

  std::string pdf_extension_url(extensions::kExtensionScheme);
  pdf_extension_url.append(url::kStandardSchemeSeparator);
  pdf_extension_url.append(extension_misc::kPdfExtensionId);
  GURL pdf_index = GURL(pdf_extension_url).Resolve("/index.html");
  ui_test_utils::NavigateToURL(browser(), pdf_index);

  bool matches;
  ASSERT_TRUE(ExecuteScriptAndExtractBool(
      browser()->tab_strip_model()->GetActiveWebContents(),
      base::StringPrintf("window.domAutomationController.send(window."
                         "matchMedia('(prefers-color-scheme: %s)').matches)",
                         ExpectedColorScheme()),
      &matches));
  EXPECT_TRUE(matches);
}
#endif

<<<<<<< HEAD
INSTANTIATE_TEST_SUITE_P(All,
                         PrefersColorSchemeTest,
                         testing::Combine(testing::Bool(), testing::Bool()));

class PreferredRootScrollbarColorSchemeChromeClientTest
    : public testing::WithParamInterface<std::tuple<bool, bool, bool>>,
      public InProcessBrowserTest {
 protected:
  PreferredRootScrollbarColorSchemeChromeClientTest()
      : dark_mode_(std::get<0>(GetParam())),
        uses_custom_theme_(std::get<1>(GetParam())),
        theme_client_(&test_theme_) {
    test_theme_.SetDarkMode(dark_mode_);
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    original_client_ = SetBrowserClientForTesting(&theme_client_);
    test_theme_.SetDarkMode(dark_mode_);
    ui::NativeTheme::GetInstanceForNativeUi()->set_use_dark_colors(dark_mode_);
    ThemeService* theme_service =
        ThemeServiceFactory::GetForProfile(browser()->profile());
    theme_service->UseDeviceTheme(std::get<2>(GetParam()));
    if (uses_custom_theme_) {
      theme_service->BuildAutogeneratedThemeFromColor(SK_ColorRED);
    } else {
      theme_service->UseDefaultTheme();
    }
  }

  ~PreferredRootScrollbarColorSchemeChromeClientTest() override {
    CHECK_EQ(&theme_client_, SetBrowserClientForTesting(original_client_));
  }

  blink::mojom::PreferredColorScheme ExpectedColorScheme() const {
    return dark_mode_ && !uses_custom_theme_ && !UsesDeviceTheme()
               ? blink::mojom::PreferredColorScheme::kDark
               : blink::mojom::PreferredColorScheme::kLight;
  }

 private:
  bool UsesDeviceTheme() const {
    ThemeService* theme_service =
        ThemeServiceFactory::GetForProfile(browser()->profile());
    return theme_service->UsingDeviceTheme();
  }

  class ChromeContentBrowserClientWithWebTheme
      : public ChromeContentBrowserClient {
   public:
    explicit ChromeContentBrowserClientWithWebTheme(
        const ui::NativeTheme* theme)
        : theme_(theme) {}

   protected:
    const ui::NativeTheme* GetWebTheme() const override { return theme_; }

   private:
    const raw_ptr<const ui::NativeTheme> theme_;
  };

  const bool dark_mode_ = false;
  const bool uses_custom_theme_ = false;
  raw_ptr<content::ContentBrowserClient> original_client_ = nullptr;
  ui::TestNativeTheme test_theme_;
  ChromeContentBrowserClientWithWebTheme theme_client_;
};

// This test verifies that the preferred color scheme for root scrollbars is set
// appropriately following the web content's color scheme and the presence of
// a custom theme.
IN_PROC_BROWSER_TEST_P(PreferredRootScrollbarColorSchemeChromeClientTest,
                       ScrollbarFollowsPreferredColorScheme) {
  EXPECT_EQ(browser()
                ->tab_strip_model()
                ->GetActiveWebContents()
                ->GetOrCreateWebPreferences()
                .preferred_root_scrollbar_color_scheme,
            ExpectedColorScheme());
}

INSTANTIATE_TEST_SUITE_P(All,
                         PreferredRootScrollbarColorSchemeChromeClientTest,
                         testing::Combine(testing::Bool(),
                                          testing::Bool(),
                                          testing::Bool()));
=======
INSTANTIATE_TEST_SUITE_P(All, PrefersColorSchemeTest, testing::Bool());
>>>>>>> chromium

class PrefersContrastTest
    : public testing::WithParamInterface<ui::NativeTheme::PreferredContrast>,
      public InProcessBrowserTest {
 protected:
  PrefersContrastTest() : theme_client_(&test_theme_) {}

  ~PrefersContrastTest() override {
    CHECK_EQ(&theme_client_, SetBrowserClientForTesting(original_client_));
  }

  const char* ExpectedPrefersContrast() const {
    switch (GetParam()) {
      case ui::NativeTheme::PreferredContrast::kNoPreference:
        return "no-preference";
      case ui::NativeTheme::PreferredContrast::kMore:
        return "more";
      case ui::NativeTheme::PreferredContrast::kLess:
        return "less";
    }
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    command_line->AppendSwitchASCII(switches::kEnableBlinkFeatures,
                                    "PrefersContrast");
    command_line->AppendSwitchASCII(switches::kEnableBlinkFeatures,
                                    "ForcedColors");
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    original_client_ = SetBrowserClientForTesting(&theme_client_);
  }

 protected:
  ui::TestNativeTheme test_theme_;

 private:
  content::ContentBrowserClient* original_client_ = nullptr;

  class ChromeContentBrowserClientWithWebTheme
      : public ChromeContentBrowserClient {
   public:
    explicit ChromeContentBrowserClientWithWebTheme(
        const ui::NativeTheme* theme)
        : theme_(theme) {}

   protected:
    const ui::NativeTheme* GetWebTheme() const override { return theme_; }

   private:
    const ui::NativeTheme* const theme_;
  };

  ChromeContentBrowserClientWithWebTheme theme_client_;
};

IN_PROC_BROWSER_TEST_P(PrefersContrastTest, PrefersContrast) {
  test_theme_.set_preferred_contrast(GetParam());
  browser()
      ->tab_strip_model()
      ->GetActiveWebContents()
      ->OnWebPreferencesChanged();
  ui_test_utils::NavigateToURL(
      browser(),
      ui_test_utils::GetTestUrl(
          base::FilePath(base::FilePath::kCurrentDirectory),
          base::FilePath(FILE_PATH_LITERAL("prefers-contrast.html"))));
  std::u16string tab_title;
  ASSERT_TRUE(ui_test_utils::GetCurrentTabTitle(browser(), &tab_title));
  EXPECT_EQ(base::ASCIIToUTF16(ExpectedPrefersContrast()), tab_title);
}

INSTANTIATE_TEST_SUITE_P(
    All,
    PrefersContrastTest,
    testing::Values(ui::NativeTheme::PreferredContrast::kNoPreference,
                    ui::NativeTheme::PreferredContrast::kMore,
                    ui::NativeTheme::PreferredContrast::kLess));

class ProtocolHandlerTest : public InProcessBrowserTest {
 public:
  ProtocolHandlerTest() = default;

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    host_resolver()->AddRule("*", "127.0.0.1");
    ASSERT_TRUE(embedded_test_server()->Start());
  }

 protected:
  void AddProtocolHandler(const std::string& scheme,
                          const std::string& redirect_template) {
    protocol_handler_registry()->OnAcceptRegisterProtocolHandler(
        ProtocolHandler::CreateProtocolHandler(scheme,
                                               GURL(redirect_template)));
  }

  ProtocolHandlerRegistry* protocol_handler_registry() {
    return ProtocolHandlerRegistryFactory::GetInstance()->GetForBrowserContext(
        browser()->profile());
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(ProtocolHandlerTest);
};

IN_PROC_BROWSER_TEST_F(ProtocolHandlerTest, CustomHandler) {
#if defined(OS_MAC)
  ASSERT_TRUE(test::RegisterAppWithLaunchServices());
#endif
  AddProtocolHandler("news", "https://abc.xyz/?url=%s");

  ui_test_utils::NavigateToURL(browser(), GURL("news:something"));

  std::u16string expected_title = u"abc.xyz";
  content::TitleWatcher title_watcher(
      browser()->tab_strip_model()->GetActiveWebContents(), expected_title);
  EXPECT_EQ(expected_title, title_watcher.WaitAndGetTitle());
}

// This is a regression test for crbug.com/969177.
IN_PROC_BROWSER_TEST_F(ProtocolHandlerTest, HandlersIgnoredWhenDisabled) {
  AddProtocolHandler("bitcoin", "https://abc.xyz/?url=%s");
  protocol_handler_registry()->Disable();

  ui_test_utils::NavigateToURL(browser(), GURL("bitcoin:something"));

  std::u16string tab_title;
  ASSERT_TRUE(ui_test_utils::GetCurrentTabTitle(browser(), &tab_title));
  EXPECT_EQ(u"about:blank", tab_title);
}

#if BUILDFLAG(IS_CHROMEOS)
// Tests that if a protocol handler is registered for a scheme, an external
// program (another Chrome tab in this case) is not launched to handle the
// navigation. This is a regression test for crbug.com/963133.
IN_PROC_BROWSER_TEST_F(ProtocolHandlerTest, ExternalProgramNotLaunched) {
  ui_test_utils::NavigateToURL(browser(), GURL("mailto:bob@example.com"));

  // If an external program (Chrome) was launched, it will result in a second
  // tab being opened.
  EXPECT_EQ(1, browser()->tab_strip_model()->count());
  // Make sure the protocol handler redirected the navigation.
  std::u16string expected_title = u"mail.google.com";
  content::TitleWatcher title_watcher(
      browser()->tab_strip_model()->GetActiveWebContents(), expected_title);
  EXPECT_EQ(expected_title, title_watcher.WaitAndGetTitle());
}
<<<<<<< HEAD

namespace {
class FakeExternalProtocolHandlerWorker
    : public shell_integration::DefaultSchemeClientWorker {
 public:
  FakeExternalProtocolHandlerWorker(
      const GURL& url,
      shell_integration::DefaultWebClientState os_state,
      const std::u16string& program_name)
      : shell_integration::DefaultSchemeClientWorker(url),
        os_state_(os_state),
        program_name_(program_name) {}

 private:
  ~FakeExternalProtocolHandlerWorker() override = default;

  shell_integration::DefaultWebClientState CheckIsDefaultImpl() override {
    return os_state_;
  }

  std::u16string GetDefaultClientNameImpl() override { return program_name_; }

  void SetAsDefaultImpl(base::OnceClosure on_finished_callback) override {
    std::move(on_finished_callback).Run();
  }

  shell_integration::DefaultWebClientState os_state_;
  std::u16string program_name_;
};

class ScopedFakeExternalProtocolHandlerDelegate
    : public ExternalProtocolHandler::Delegate {
 public:
  ScopedFakeExternalProtocolHandlerDelegate() {
    ExternalProtocolHandler::SetDelegateForTesting(this);
  }
  ~ScopedFakeExternalProtocolHandlerDelegate() override {
    ExternalProtocolHandler::SetDelegateForTesting(nullptr);
  }
  scoped_refptr<shell_integration::DefaultSchemeClientWorker> CreateShellWorker(
      const GURL& url) override {
    return new FakeExternalProtocolHandlerWorker(
        url, shell_integration::UNKNOWN_DEFAULT, program_name_);
  }

  ExternalProtocolHandler::BlockState GetBlockState(const std::string& scheme,
                                                    Profile* profile) override {
    return ExternalProtocolHandler::UNKNOWN;
  }

  void BlockRequest() override {
    FAIL() << "Unexpected BlockRequest call received";
  }

  void RunExternalProtocolDialog(
      const GURL& url,
      content::WebContents* web_contents,
      ui::PageTransition page_transition,
      bool has_user_gesture,
      const std::optional<url::Origin>& initiating_origin,
      const std::u16string& program_name) override {
    EXPECT_EQ(program_name_, program_name);
    external_protocol_dialog_called_ = true;
    launched_url_with_security_check_ = url.spec();
  }

  void LaunchUrlWithoutSecurityCheck(
      const GURL& url,
      content::WebContents* web_contents) override {
    launched_url_without_security_check_ = url.spec();
    launch_url_run_loop_.Quit();
  }

  void FinishedProcessingCheck() override { launch_url_run_loop_.Quit(); }

  void WaitExternalUrlLaunchCompleted() { launch_url_run_loop_.Run(); }

  bool external_protocol_dialog_called() {
    return external_protocol_dialog_called_;
  }
  std::string launched_url_without_security_check() {
    return launched_url_without_security_check_;
  }
  std::string launched_url_with_security_check() {
    return launched_url_with_security_check_;
  }

 private:
  base::RunLoop launch_url_run_loop_;
  const std::u16string program_name_ = u"custom";
  bool external_protocol_dialog_called_ = false;
  std::string launched_url_without_security_check_;
  std::string launched_url_with_security_check_;
};

}  // namespace

// URLs which are explicitly allowlisted by policy can bypass security checks.
IN_PROC_BROWSER_TEST_F(ProtocolHandlerTest,
                       SecurityCheckExceptionForAllowlistedUrls) {
  ProtocolHandlerRegistryFactory::GetInstance()
      ->GetForBrowserContext(browser()->profile())
      ->OnAcceptRegisterProtocolHandler(
          custom_handlers::ProtocolHandler::CreateProtocolHandler(
              "map", GURL("geo://%s")));

  ScopedFakeExternalProtocolHandlerDelegate delegate;

  base::Value::List allowlist;
  allowlist.Append("geo://*");
  browser()->profile()->GetPrefs()->SetList(policy::policy_prefs::kUrlAllowlist,
                                            std::move(allowlist));
  // The call to update the internal allowlist value is async.
  base::RunLoop().RunUntilIdle();

  const char kGeoUrl[] = "geo:48.2082,16.3738";

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), GURL(kGeoUrl)));
  delegate.WaitExternalUrlLaunchCompleted();

  EXPECT_FALSE(delegate.external_protocol_dialog_called());
  EXPECT_EQ(delegate.launched_url_without_security_check(), kGeoUrl);
  EXPECT_EQ(delegate.launched_url_with_security_check(), "");
}

// Regardless of the value of the UrlAllowlist policy, intent:// URLs should
// always be deferred to the external protocol dialog (which currently defers
// the call to ARC).
IN_PROC_BROWSER_TEST_F(ProtocolHandlerTest,
                       IntentSchemeBypassSecurityExceptions) {
  ProtocolHandlerRegistryFactory::GetInstance()
      ->GetForBrowserContext(browser()->profile())
      ->OnAcceptRegisterProtocolHandler(
          custom_handlers::ProtocolHandler::CreateProtocolHandler(
              "search", GURL("intent://%s")));

  ScopedFakeExternalProtocolHandlerDelegate delegate;

  base::Value::List allowlist;
  allowlist.Append("intent://*");
  browser()->profile()->GetPrefs()->SetList(policy::policy_prefs::kUrlAllowlist,
                                            std::move(allowlist));
  // The call to update the internal allowlist value is async.
  base::RunLoop().RunUntilIdle();

  const char kIntentUrl[] =
      "intent://www.google.com/"
      "#Intent;scheme=http;package=com.android.chrome;end";

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), GURL(kIntentUrl)));
  delegate.WaitExternalUrlLaunchCompleted();

  EXPECT_TRUE(delegate.external_protocol_dialog_called());
  // intent:// URLs should not skip security checks.
  EXPECT_EQ(delegate.launched_url_without_security_check(), "");
  EXPECT_EQ(delegate.launched_url_with_security_check(), kIntentUrl);
}
=======
>>>>>>> chromium
#endif

#if !defined(OS_ANDROID)
class KeepaliveDurationOnShutdownTest : public InProcessBrowserTest,
                                        public InstantTestBase {
 public:
  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    client_ = static_cast<ChromeContentBrowserClient*>(
        content::SetBrowserClientForTesting(nullptr));
    content::SetBrowserClientForTesting(client_);
  }
  void TearDownOnMainThread() override {
    client_ = nullptr;
    InProcessBrowserTest::TearDownOnMainThread();
  }

  ChromeContentBrowserClient* client_ = nullptr;
};

IN_PROC_BROWSER_TEST_F(KeepaliveDurationOnShutdownTest, DefaultValue) {
  Profile* profile =
      g_browser_process->profile_manager()->GetPrimaryUserProfile();
  EXPECT_EQ(client_->GetKeepaliveTimerTimeout(profile), base::TimeDelta());
}

IN_PROC_BROWSER_TEST_F(KeepaliveDurationOnShutdownTest, PolicySettings) {
  Profile* profile =
      g_browser_process->profile_manager()->GetPrimaryUserProfile();
  profile->GetPrefs()->SetInteger(prefs::kFetchKeepaliveDurationOnShutdown, 2);

  EXPECT_EQ(client_->GetKeepaliveTimerTimeout(profile),
            base::TimeDelta::FromSeconds(2));
}

IN_PROC_BROWSER_TEST_F(KeepaliveDurationOnShutdownTest, DynamicUpdate) {
  Profile* profile =
      g_browser_process->profile_manager()->GetPrimaryUserProfile();
  profile->GetPrefs()->SetInteger(prefs::kFetchKeepaliveDurationOnShutdown, 2);

  EXPECT_EQ(client_->GetKeepaliveTimerTimeout(profile),
            base::TimeDelta::FromSeconds(2));

  profile->GetPrefs()->SetInteger(prefs::kFetchKeepaliveDurationOnShutdown, 3);

  EXPECT_EQ(client_->GetKeepaliveTimerTimeout(profile),
            base::TimeDelta::FromSeconds(3));
}

#endif  // !defined(OS_ANDROID)

class ThirdPartyStoragePartitioningOriginTrialTest
    : public InProcessBrowserTest,
      public ::testing::WithParamInterface<bool> {
 public:
  ThirdPartyStoragePartitioningOriginTrialTest()
      : https_server_(net::EmbeddedTestServer::TYPE_HTTPS) {
    // The 3PCD tracking protection feature must be disabled so that we can
    // disable third-party cookies by changing the prefs::kCookieControlsMode
    // pref.
    feature_.InitAndDisableFeature(
        content_settings::features::kTrackingProtection3pcd);
  }

  // The URL that will be used to load third-party scripts.
  static constexpr char kThirdPartyScriptUrl[] = "https://127.0.0.1:44445";
  // A cross-site URL used for Origin Trials.
  static constexpr char kCrossSiteOriginTrialUrl[] = "https://a.com";

  bool BlockThirdPartyCookies() const { return GetParam(); }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    command_line->AppendSwitchASCII(
        "origin-trial-public-key",
        "dRCs+TocuKkocNKa0AtZ4awrt9XKH2SQCI6o4FY6BNA=");
  }

  void SetUpOnMainThread() override {
    // Set up the framework that allows us to intercept and inspect any Origin
    // Trial header requests.
    url_loader_interceptor_ =
        std::make_unique<content::URLLoaderInterceptor>(base::BindRepeating(
            &ThirdPartyStoragePartitioningOriginTrialTest::InterceptURLRequest,
            base::Unretained(this)));
    ASSERT_TRUE(https_server()->Start());
  }

  void TearDownOnMainThread() override {
    url_loader_interceptor_.reset();
    InProcessBrowserTest::TearDownOnMainThread();
  }

 protected:
  void SetOriginTrialToken(const std::string& token) {
    origin_trial_token_ = token;
  }

  GURL cross_site_script_meta_tag_origin_trial_url() const {
    return GURL(base::StrCat({kCrossSiteOriginTrialUrl, "/meta_script.html"}));
  }

  GURL meta_tag_injecting_javascript_url() const {
    return GURL(base::StrCat({kThirdPartyScriptUrl, "/meta.js"}));
  }

  GURL empty_frame_meta_origin_trial_url() const {
    return GURL(base::StrCat({kThirdPartyScriptUrl, "/empty.html"}));
  }

  net::EmbeddedTestServer* https_server() { return &https_server_; }

 private:
  bool RespondForEmptyUrl(
      content::URLLoaderInterceptor::RequestParams* params) {
    std::string headers = "HTTP/1.1 200 OK\nContent-Type: text/html\n";
    std::string body = "<html>This page has no title.</html>";
    content::URLLoaderInterceptor::WriteResponse(headers, body,
                                                 params->client.get());
    return true;
  }

  bool RespondForScriptMetaTagOriginTrialUrl(
      content::URLLoaderInterceptor::RequestParams* params) {
    // Construct the origin trial response.
    std::string headers = "HTTP/1.1 200 OK\nContent-Type: text/html\n";
    std::string body = base::StrCat(
        {"<html><head><script src=\"",
         meta_tag_injecting_javascript_url().spec(),
         "\"></script></head><body>This page has no title.</body></html>"});
    content::URLLoaderInterceptor::WriteResponse(headers, body,
                                                 params->client.get());
    return true;
  }

  bool RespondForMetaTagInjectingScriptUrl(
      content::URLLoaderInterceptor::RequestParams* params) {
    CHECK(!origin_trial_token_.empty());
    // Construct the origin trial response.
    std::string headers =
        "HTTP/1.1 200 OK\nContent-Type: application/javascript\n";
    std::string body =
        base::StrCat({"const otMeta = document.createElement('meta'); "
                      "otMeta.httpEquiv = 'origin-trial'; "
                      "otMeta.content = '",
                      origin_trial_token_,
                      "'; "
                      "document.head.append(otMeta); ",
                      "const iframe = document.createElement('iframe'); ",
                      "document.head.appendChild(iframe); "});
    content::URLLoaderInterceptor::WriteResponse(headers, body,
                                                 params->client.get());
    return true;
  }

  // Create the framework to intercept origin trial requests.
  bool InterceptURLRequest(
      content::URLLoaderInterceptor::RequestParams* params) {
    if (params->url_request.url ==
        cross_site_script_meta_tag_origin_trial_url()) {
      return RespondForScriptMetaTagOriginTrialUrl(params);
    }
    if (params->url_request.url == meta_tag_injecting_javascript_url()) {
      return RespondForMetaTagInjectingScriptUrl(params);
    }
    if (params->url_request.url == empty_frame_meta_origin_trial_url()) {
      return RespondForEmptyUrl(params);
    }
    return false;
  }

  base::test::ScopedFeatureList feature_;
  net::EmbeddedTestServer https_server_;
  std::string origin_trial_token_;
  std::unique_ptr<content::URLLoaderInterceptor> url_loader_interceptor_;
};

// Test that the 3PSP deprecation trial only enables third-party storage when
// the user has explicitly opted into third-party cooking blocking (instead of
// enabling first-party storage). This test is derived from
// RenderFrameHostImplWithTokensBrowserTest.ReusedChildFrameNavigatedFromDeprecationTrialIsPartitioned.
IN_PROC_BROWSER_TEST_P(ThirdPartyStoragePartitioningOriginTrialTest,
                       ThirdPartyCookieSettingOverridesDeprecationTrial) {
  // Generated with:
  // tools/origin_trials/generate_token.py https://127.0.0.1:44445
  // DisableThirdPartyStoragePartitioning3 --expire-timestamp=2000000000
  // --is-third-party
  const char kValidThirdPartyToken[] =
      "A7BpVOcOsvw3FiZnc4wIJ9pfGSrhUqMyV8GmGkZrm6emdOW5hBe9YN8XKoFa+"
      "YQkVUxdNR22quD3oCJvuIX2cAoAAACFeyJvcmlnaW4iOiAiaHR0cHM6Ly8xMjcuMC4wLjE6N"
      "DQ0NDUiLCAiZmVhdHVyZSI6ICJEaXNhYmxlVGhpcmRQYXJ0eVN0b3JhZ2VQYXJ0aXRpb25pb"
      "mczIiwgImV4cGlyeSI6IDIwMDAwMDAwMDAsICJpc1RoaXJkUGFydHkiOiB0cnVlfQ==";

  SetOriginTrialToken(kValidThirdPartyToken);

  browser()->profile()->GetPrefs()->SetInteger(
      prefs::kCookieControlsMode,
      BlockThirdPartyCookies()
          ? static_cast<int>(
                content_settings::CookieControlsMode::kBlockThirdParty)
          : static_cast<int>(content_settings::CookieControlsMode::kOff));

  // Navigate to "a.test" and load a script from a third-party. In that script,
  // the deprecation trial token above is added via <meta> tag. Then, the script
  // adds an iframe.
  EXPECT_TRUE(ui_test_utils::NavigateToURL(
      browser(), cross_site_script_meta_tag_origin_trial_url()));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  ASSERT_NE(contents, nullptr);

  content::RenderFrameHost* child_frame =
      ChildFrameAt(contents->GetPrimaryMainFrame(), 0);
  ASSERT_TRUE(child_frame);
  // Navigate the currently empty iframe to a URL that is same-site with the
  // third-party script.
  EXPECT_TRUE(NavigateToURLFromRenderer(child_frame,
                                        empty_frame_meta_origin_trial_url()));
  // Execute a dummy roundtrip to ensure the <meta> tag trial token has time to
  // parse and be applied to the iframe.
  EXPECT_TRUE(content::ExecJs(contents, ";"));

  // Re-obtain the iframe after confirming the navigation is complete.
  child_frame = ChildFrameAt(contents->GetPrimaryMainFrame(), 0);

  if (BlockThirdPartyCookies()) {
    EXPECT_TRUE(child_frame->GetStorageKey().IsThirdPartyContext());
  } else {
    EXPECT_TRUE(child_frame->GetStorageKey().IsFirstPartyContext());
  }
}

class BundledCodeCacheChromeContentBrowserClientTest
    : public InProcessBrowserTest,
      public testing::WithParamInterface<bool> {
 public:
  BundledCodeCacheChromeContentBrowserClientTest() {
    feature_list_.InitWithFeatureState(features::kWebUIBundledCodeCache,
                                       IsBundledCodeCacheEnabled());
  }

  bool IsBundledCodeCacheEnabled() const { return GetParam(); }

 private:
  base::test::ScopedFeatureList feature_list_;
};

// Assert top-chrome webui renderers disallow v8 feature flag overrides only
// when the bundled webui code cache is enabled.
IN_PROC_BROWSER_TEST_P(BundledCodeCacheChromeContentBrowserClientTest,
                       ConfiguresRendererForDisallowV8FeatureOverrides) {
  ASSERT_TRUE(embedded_test_server()->Start());
  const GURL top_chrome_url1(chrome::kChromeUITabSearchURL);
  const GURL top_chrome_url2(chrome::kChromeUIReadLaterURL);
  const GURL non_top_chrome_url1(chrome::kChromeUINewTabPageURL);
  const GURL non_top_chrome_url2(
      embedded_test_server()->GetURL("/title1.html"));
  EXPECT_TRUE(top_chrome_url1.DomainIs(chrome::kChromeUITopChromeDomain));
  EXPECT_TRUE(top_chrome_url2.DomainIs(chrome::kChromeUITopChromeDomain));
  EXPECT_FALSE(non_top_chrome_url1.DomainIs(chrome::kChromeUITopChromeDomain));
  EXPECT_FALSE(non_top_chrome_url1.DomainIs(chrome::kChromeUITopChromeDomain));

  // Disallow V8 feature flag overrides should only apply to top-chrome URLs
  // when bundled code caching is enabled.
  auto navigate_and_expect_policy_result = [this](const GURL& url,
                                                  bool expectation) {
    content::RenderFrameHost* rfh =
        ui_test_utils::NavigateToURL(browser(), url);
    EXPECT_EQ(expectation, rfh->GetProcess()->DisallowV8FeatureFlagOverrides());
  };
  navigate_and_expect_policy_result(top_chrome_url1,
                                    IsBundledCodeCacheEnabled());
  navigate_and_expect_policy_result(top_chrome_url2,
                                    IsBundledCodeCacheEnabled());
  navigate_and_expect_policy_result(non_top_chrome_url1, false);
  navigate_and_expect_policy_result(non_top_chrome_url1, false);
}

INSTANTIATE_TEST_SUITE_P(All,
                         ThirdPartyStoragePartitioningOriginTrialTest,
                         ::testing::Bool());

INSTANTIATE_TEST_SUITE_P(
    ,
    BundledCodeCacheChromeContentBrowserClientTest,
    ::testing::Bool(),
    [](const ::testing::TestParamInfo<
        BundledCodeCacheChromeContentBrowserClientTest::ParamType>& info) {
      return info.param ? "BundledCodeCache_Enabled"
                        : "BundledCodeCache_Disabled";
    });

}  // namespace
