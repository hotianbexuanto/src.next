// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/managed_ui.h"

#include "base/strings/utf_string_conversions.h"
<<<<<<< HEAD
#include "build/build_config.h"
#include "chrome/browser/browser_features.h"
=======
#include "build/chromeos_buildflags.h"
>>>>>>> chromium
#include "chrome/browser/browser_process.h"
#include "chrome/browser/enterprise/browser_management/browser_management_service.h"
#include "chrome/browser/enterprise/util/managed_browser_utils.h"
#include "chrome/browser/policy/chrome_browser_policy_connector.h"
#include "chrome/browser/policy/profile_policy_connector.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/management/management_ui_handler.h"
#include "chrome/grit/generated_resources.h"
#include "components/policy/core/common/cloud/machine_level_user_cloud_policy_manager.h"
#include "components/policy/core/common/management/platform_management_service.h"
#include "components/policy/proto/device_management_backend.pb.h"
<<<<<<< HEAD
#include "components/prefs/pref_service.h"
#include "components/signin/public/identity_manager/account_info.h"
#include "components/signin/public/identity_manager/account_managed_status_finder.h"
#include "components/signin/public/identity_manager/signin_constants.h"
#include "components/strings/grit/components_strings.h"
#include "components/supervised_user/core/browser/supervised_user_preferences.h"
#include "components/supervised_user/core/common/supervised_user_constants.h"
#include "components/vector_icons/vector_icons.h"
=======
>>>>>>> chromium
#include "ui/base/l10n/l10n_util.h"

#if BUILDFLAG(IS_CHROMEOS)
#include "chrome/browser/ash/login/demo_mode/demo_session.h"
#include "chrome/browser/ash/policy/core/browser_policy_connector_chromeos.h"
#include "chrome/browser/ash/policy/core/user_cloud_policy_manager_chromeos.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/browser_process_platform_part.h"
#include "ui/chromeos/devicetype_utils.h"
#else
#include "components/policy/core/common/cloud/user_cloud_policy_manager.h"
#endif

<<<<<<< HEAD
using signin::constants::kNoHostedDomainFound;
=======
namespace chrome {
>>>>>>> chromium

namespace {

std::string GetManagedBy(const policy::CloudPolicyManager* manager) {
  if (manager) {
    const enterprise_management::PolicyData* policy =
        manager->core()->store()->policy();
    if (policy && policy->has_managed_by()) {
      return policy->managed_by();
    }
  }
  return std::string();
}

const policy::CloudPolicyManager* GetUserCloudPolicyManager(Profile* profile) {
#if BUILDFLAG(IS_CHROMEOS_ASH)
  return profile->GetUserCloudPolicyManagerChromeOS();
#else
  return profile->GetUserCloudPolicyManager();
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
}

absl::optional<std::string> GetEnterpriseAccountDomain(Profile* profile) {
  const std::string domain =
      enterprise_util::GetDomainFromEmail(profile->GetProfileUserName());
  // Heuristic for most common consumer Google domains -- these are not managed.
  if (domain.empty() || domain == "gmail.com" || domain == "googlemail.com")
    return absl::nullopt;
  return domain;
}

}  // namespace

bool ShouldDisplayManagedUi(Profile* profile) {
#if BUILDFLAG(IS_CHROMEOS)
  // Don't show the UI in demo mode.
  if (ash::DemoSession::IsDeviceInDemoMode()) {
    return false;
<<<<<<< HEAD
  }

  // Don't show the UI for Family Link accounts.
  if (profile->IsChild()) {
    return false;
  }
#endif  // BUILDFLAG(IS_CHROMEOS)

  return enterprise_util::IsBrowserManaged(profile) ||
         ShouldDisplayManagedByParentUi(profile);
}

#if !BUILDFLAG(IS_ANDROID)

GURL GetManagedUiUrl(Profile* profile) {
  if (enterprise_util::IsBrowserManaged(profile)) {
    return GURL(chrome::kChromeUIManagementURL);
  }

  if (ShouldDisplayManagedByParentUi(profile)) {
    return GURL(supervised_user::kManagedByParentUiMoreInfoUrl);
  }

  return GURL();
}

const gfx::VectorIcon& GetManagedUiIcon(Profile* profile) {
  CHECK(ShouldDisplayManagedUi(profile));

  if (enterprise_util::IsBrowserManaged(profile)) {
    return vector_icons::kBusinessChromeRefreshIcon;
  }

  CHECK(ShouldDisplayManagedByParentUi(profile));
  return vector_icons::kFamilyLinkIcon;
=======

  // Don't show the UI for Unicorn accounts.
  if (profile->IsSupervised())
    return false;
#endif

  return enterprise_util::HasBrowserPoliciesApplied(profile);
>>>>>>> chromium
}

std::u16string GetManagedUiMenuItemLabel(Profile* profile) {
  absl::optional<std::string> account_manager =
      GetAccountManagerIdentity(profile);

  int string_id = IDS_MANAGED;
  std::vector<std::u16string> replacements;
  if (account_manager) {
    string_id = IDS_MANAGED_BY;
    replacements.push_back(base::UTF8ToUTF16(*account_manager));
  }

  return l10n_util::GetStringFUTF16(string_id, replacements, nullptr);
}

std::u16string GetManagedUiWebUILabel(Profile* profile) {
  absl::optional<std::string> account_manager =
      GetAccountManagerIdentity(profile);

  int string_id = IDS_MANAGED_WITH_HYPERLINK;
  std::vector<std::u16string> replacements;
  replacements.push_back(base::UTF8ToUTF16(chrome::kChromeUIManagementURL));
  if (account_manager) {
    string_id = IDS_MANAGED_BY_WITH_HYPERLINK;
    replacements.push_back(base::UTF8ToUTF16(*account_manager));
  }

  return l10n_util::GetStringFUTF16(string_id, replacements, nullptr);
}

<<<<<<< HEAD
std::u16string GetDeviceManagedUiHelpLabel(Profile* profile) {
#if BUILDFLAG(IS_CHROMEOS)
  return ManagementUI::GetManagementPageSubtitle(profile);
#else
  if (enterprise_util::IsBrowserManaged(profile)) {
    std::optional<std::string> manager = GetAccountManagerIdentity(profile);
    if (!manager &&
        base::FeatureList::IsEnabled(features::kFlexOrgManagementDisclosure)) {
      manager = GetDeviceManagerIdentity();
    }
    return manager && !manager->empty()
               ? l10n_util::GetStringFUTF16(IDS_MANAGEMENT_SUBTITLE_MANAGED_BY,
                                            base::UTF8ToUTF16(*manager))
               : l10n_util::GetStringUTF16(IDS_MANAGEMENT_SUBTITLE);
  }

  if (ShouldDisplayManagedByParentUi(profile)) {
    return l10n_util::GetStringUTF16(IDS_HELP_MANAGED_BY_YOUR_PARENT);
  }

  return l10n_util::GetStringUTF16(IDS_MANAGEMENT_NOT_MANAGED_SUBTITLE);
#endif  // BUILDFLAG(IS_CHROMEOS)
}
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
std::u16string GetDeviceManagedUiWebUILabel() {
  int string_id = IDS_DEVICE_MANAGED_WITH_HYPERLINK;
  std::vector<std::u16string> replacements;
  replacements.push_back(base::UTF8ToUTF16(chrome::kChromeUIManagementURL));
  replacements.push_back(ui::GetChromeOSDeviceName());

  const absl::optional<std::string> device_manager = GetDeviceManagerIdentity();
  if (device_manager && !device_manager->empty()) {
    string_id = IDS_DEVICE_MANAGED_BY_WITH_HYPERLINK;
    replacements.push_back(base::UTF8ToUTF16(*device_manager));
  }

  return l10n_util::GetStringFUTF16(string_id, replacements, nullptr);
}
#endif

<<<<<<< HEAD
#if !BUILDFLAG(IS_CHROMEOS)
std::u16string GetManagementBubbleTitle(Profile* profile) {
  std::optional<std::string> device_manager = GetDeviceManagerIdentity();

  switch (GetManagementStringType(profile)) {
    case BROWSER_MANAGED:
      return l10n_util::GetStringUTF16(IDS_MANAGEMENT_DIALOG_BROWSER_MANAGED);
    case BROWSER_MANAGED_BY:
    case BROWSER_PROFILE_SAME_MANAGED_BY:
      return l10n_util::GetStringFUTF16(
          IDS_MANAGEMENT_DIALOG_BROWSER_MANAGED_BY,
          base::UTF8ToUTF16(*device_manager));
    case BROWSER_PROFILE_DIFFERENT_MANAGED_BY:
    case BROWSER_MANAGED_PROFILE_MANAGED_BY:
      return l10n_util::GetStringUTF16(
          IDS_MANAGEMENT_DIALOG_BROWSER_MANAGED_BY_MULTIPLE_ORGANIZATIONS);
    case PROFILE_MANAGED_BY:
      return l10n_util::GetStringFUTF16(
          IDS_MANAGEMENT_DIALOG_PROFILE_MANAGED_BY,
          base::UTF8ToUTF16(*GetAccountManagerIdentity(profile)));
    case SUPERVISED:
    case NOT_MANAGED:
      NOTREACHED();
  }
}
#endif

bool AreProfileAndBrowserManagedBySameEntity(Profile* profile) {
  return GetManagementStringType(profile) == BROWSER_PROFILE_SAME_MANAGED_BY;
}

std::optional<std::string> GetDeviceManagerIdentity() {
  if (g_device_manager_for_testing) {
    return g_device_manager_for_testing;
  }

  if (!policy::ManagementServiceFactory::GetForPlatform()->IsManaged()) {
    return std::nullopt;
  }

#if BUILDFLAG(IS_CHROMEOS)
  policy::BrowserPolicyConnectorAsh* connector =
      g_browser_process->platform_part()->browser_policy_connector_ash();
  return connector->GetEnterpriseDomainManager();
#else
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  if (base::FeatureList::IsEnabled(
          features::kEnterpriseManagementDisclaimerUsesCustomLabel)) {
    std::string custom_management_label =
        g_browser_process->local_state()
            ? g_browser_process->local_state()->GetString(
                  prefs::kEnterpriseCustomLabelForBrowser)
            : std::string();
    if (!custom_management_label.empty()) {
      return custom_management_label;
    }
  }
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  // The device is managed as
  // `policy::ManagementServiceFactory::GetForPlatform()->IsManaged()` returned
  // true. `policy::GetManagedBy` might return `std::nullopt` if
  // `policy::CloudPolicyStore` hasn't fully initialized yet.
  return policy::GetManagedBy(g_browser_process->browser_policy_connector()
                                  ->machine_level_user_cloud_policy_manager())
      .value_or(std::string());
#endif  // BUILDFLAG(IS_CHROMEOS)
}

std::optional<std::string> GetAccountManagerIdentity(Profile* profile) {
  if (!policy::ManagementServiceFactory::GetForProfile(profile)
           ->HasManagementAuthority(
               policy::EnterpriseManagementAuthority::CLOUD)) {
    return std::nullopt;
  }

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  if (base::FeatureList::IsEnabled(
          features::kEnterpriseManagementDisclaimerUsesCustomLabel)) {
    std::string custom_management_label =
        profile->GetPrefs()->GetString(prefs::kEnterpriseCustomLabelForProfile);
    if (!custom_management_label.empty()) {
      return custom_management_label;
    }
  }
#endif

  const std::optional<std::string> managed_by =
      policy::GetManagedBy(profile->GetCloudPolicyManager());
  if (managed_by) {
    return *managed_by;
  }

  if (profile->GetProfilePolicyConnector()->IsUsingLocalTestPolicyProvider()) {
    return "Local Test Policies";
  }

  return GetEnterpriseAccountDomain(*profile);
=======
absl::optional<std::string> GetDeviceManagerIdentity() {
  if (!policy::PlatformManagementService::GetInstance().IsManaged())
    return absl::nullopt;

#if BUILDFLAG(IS_CHROMEOS_ASH)
  policy::BrowserPolicyConnectorChromeOS* connector =
      g_browser_process->platform_part()->browser_policy_connector_chromeos();
  return connector->IsActiveDirectoryManaged()
             ? connector->GetRealm()
             : connector->GetEnterpriseDomainManager();
#else
  return GetManagedBy(g_browser_process->browser_policy_connector()
                          ->machine_level_user_cloud_policy_manager());
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
}

absl::optional<std::string> GetAccountManagerIdentity(Profile* profile) {
  // TODO(crbug.com/1188594): Replace the check with
  // !policy::BrowserManagementService(profile).IsManaged() once this bug is
  // fixed (it still needs a lot of test fixture changes).
  if (!profile->GetProfilePolicyConnector()->IsManaged())
    return absl::nullopt;

  const std::string managed_by =
      GetManagedBy(GetUserCloudPolicyManager(profile));
  if (!managed_by.empty())
    return managed_by;

  return GetEnterpriseAccountDomain(profile);
>>>>>>> chromium
}
