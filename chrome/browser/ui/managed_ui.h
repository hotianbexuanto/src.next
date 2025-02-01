// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_MANAGED_UI_H_
#define CHROME_BROWSER_UI_MANAGED_UI_H_

#include <string>

<<<<<<< HEAD
#include "build/build_config.h"
=======
#include "build/chromeos_buildflags.h"
#include "third_party/abseil-cpp/absl/types/optional.h"
>>>>>>> chromium

class Profile;

<<<<<<< HEAD
namespace gfx {
struct VectorIcon;
}

class ScopedDeviceManagerForTesting {
 public:
  explicit ScopedDeviceManagerForTesting(const char* manager);
  ~ScopedDeviceManagerForTesting();

 private:
  const char* previous_manager_ = nullptr;
};

// Returns the enterprise domain of `profile` if one was found.
// This function will try to get the hosted domain and fallback on the domain
// of the email of the signed in account.
std::optional<std::string> GetEnterpriseAccountDomain(const Profile& profile);

// Returns true if a 'Managed by <...>' message should appear in
=======
namespace chrome {

// Returns true if a 'Managed by your organization' message should appear in
>>>>>>> chromium
// Chrome's App Menu, and on the following chrome:// pages:
// - chrome://bookmarks
// - chrome://downloads
// - chrome://extensions
// - chrome://history
// - chrome://settings
//
// N.B.: This is independent of Chrome OS's system tray message for enterprise
// users.
bool ShouldDisplayManagedUi(Profile* profile);

// The label for the App Menu item for Managed UI.
std::u16string GetManagedUiMenuItemLabel(Profile* profile);

// The label for the WebUI footnote for Managed UI indicating that the browser
// is managed. These strings contain HTML for an <a> element.
std::u16string GetManagedUiWebUILabel(Profile* profile);

<<<<<<< HEAD
// The label for the string describing whether the browser is managed or not, in
// the chrome://settings/help page.
std::u16string GetDeviceManagedUiHelpLabel(Profile* profile);
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
// The label for the WebUI footnote for Managed UI indicating that the device
// is mananged. These strings contain HTML for an <a> element.
std::u16string GetDeviceManagedUiWebUILabel();
#else
std::u16string GetManagementPageSubtitle(Profile* profile);
std::u16string GetManagementBubbleTitle(Profile* profile);
#endif

// Returns trus if the profile and browser are managed and both entities are
// known and different.
bool AreProfileAndBrowserManagedBySameEntity(Profile* profile);

// Returns nullopt if the device is not managed, the UTF8-encoded string
// representation of the manager identity if available and an empty string if
// the device is managed but the manager is not known or if the policy store
// hasn't been loaded yet.
std::optional<std::string> GetDeviceManagerIdentity();
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
// The label for the WebUI footnote for Managed UI indicating that the device
// is mananged. These strings contain HTML for an <a> element.
std::u16string GetDeviceManagedUiWebUILabel();
#endif

// Returns nullopt if the device is not managed, the UTF8-encoded string
// representation of the manager identity if available and an empty string if
// the device is managed but the manager is not known.
absl::optional<std::string> GetDeviceManagerIdentity();
>>>>>>> chromium

// Returns the UTF8-encoded string representation of the the entity that manages
// `profile` or nullopt if unmanaged. For standard dasher domains, this will be
// a domain name (ie foo.com). For FlexOrgs, this will be the email address of
// the admin of the FlexOrg (ie user@foo.com). If DMServer does not provide this
// information, this function defaults to the domain of the account.
// TODO(crbug.com/1081272): Refactor localization hints for all strings that
// depend on this function.
absl::optional<std::string> GetAccountManagerIdentity(Profile* profile);

#endif  // CHROME_BROWSER_UI_MANAGED_UI_H_
