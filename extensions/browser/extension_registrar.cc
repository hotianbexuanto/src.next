// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/browser/extension_registrar.h"

#include "base/bind.h"
#include "base/callback_helpers.h"
#include "base/check_op.h"
#include "base/containers/contains.h"
<<<<<<< HEAD
#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/metrics/histogram_functions.h"
#include "base/metrics/histogram_macros.h"
#include "base/notreached.h"
#include "base/stl_util.h"
#include "build/chromeos_buildflags.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/devtools_agent_host.h"
#include "extensions/browser/blocklist_extension_prefs.h"
#include "extensions/browser/disable_reason.h"
=======
#include "base/metrics/histogram_macros.h"
#include "base/notreached.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/devtools_agent_host.h"
#include "content/public/browser/notification_service.h"
#include "extensions/browser/app_sorting.h"
>>>>>>> chromium
#include "extensions/browser/extension_host.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_system.h"
#include "extensions/browser/lazy_context_id.h"
#include "extensions/browser/lazy_context_task_queue.h"
<<<<<<< HEAD
#include "extensions/browser/management_policy.h"
=======
#include "extensions/browser/notification_types.h"
>>>>>>> chromium
#include "extensions/browser/process_manager.h"
#include "extensions/browser/renderer_startup_helper.h"
#include "extensions/browser/runtime_data.h"
#include "extensions/browser/service_worker_task_queue.h"
#include "extensions/browser/task_queue_util.h"
#include "extensions/common/manifest.h"
#include "extensions/common/manifest_handlers/background_info.h"
<<<<<<< HEAD
#include "extensions/common/manifest_handlers/shared_module_info.h"
#include "extensions/common/permissions/permissions_data.h"
#include "third_party/blink/public/common/service_worker/service_worker_status_code.h"

#if BUILDFLAG(IS_CHROMEOS)
#include "chrome/browser/ash/crosapi/browser_util.h"
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
>>>>>>> chromium

using content::DevToolsAgentHost;
using extensions::mojom::ManifestLocation;

namespace extensions {

ExtensionRegistrar::ExtensionRegistrar(content::BrowserContext* browser_context,
                                       Delegate* delegate)
    : browser_context_(browser_context),
      delegate_(delegate),
      extension_system_(ExtensionSystem::Get(browser_context)),
      extension_prefs_(ExtensionPrefs::Get(browser_context)),
      registry_(ExtensionRegistry::Get(browser_context)),
      renderer_helper_(
          RendererStartupHelperFactory::GetForBrowserContext(browser_context)) {
}

ExtensionRegistrar::~ExtensionRegistrar() = default;

void ExtensionRegistrar::AddExtension(
    scoped_refptr<const Extension> extension) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

<<<<<<< HEAD
  if (!Manifest::IsValidLocation(extension->location())) {
    // TODO(devlin): We should *never* add an extension with an invalid
    // location, but some bugs (e.g. crbug.com/692069) seem to indicate we do.
    // Track down the cases when this can happen, and remove this
    // DumpWithoutCrashing() (possibly replacing it with a CHECK).
    DEBUG_ALIAS_FOR_CSTR(extension_id_copy, extension->id().c_str(), 33);
    ManifestLocation location = extension->location();
    int creation_flags = extension->creation_flags();
    Manifest::Type type = extension->manifest()->type();
    base::debug::Alias(&location);
    base::debug::Alias(&creation_flags);
    base::debug::Alias(&type);
    NOTREACHED();
  }

  if (!delegate_->CanAddExtension(extension.get())) {
    return;
  }

=======
  bool is_extension_upgrade = false;
>>>>>>> chromium
  bool is_extension_loaded = false;
  const Extension* old = registry_->GetInstalledExtension(extension->id());
  if (old) {
    is_extension_loaded = true;
    int version_compare_result = extension->version().CompareTo(old->version());
    is_extension_upgrade = version_compare_result > 0;
    // Other than for unpacked extensions, we should not be downgrading.
    if (!Manifest::IsUnpackedLocation(extension->location()) &&
        version_compare_result < 0) {
      UMA_HISTOGRAM_ENUMERATION(
          "Extensions.AttemptedToDowngradeVersionLocation",
          extension->location());
      UMA_HISTOGRAM_ENUMERATION("Extensions.AttemptedToDowngradeVersionType",
                                extension->GetType(), Manifest::NUM_LOAD_TYPES);

      // TODO(https://crbug.com/810799): It would be awfully nice to CHECK this,
      // but that's caused problems. There are apparently times when this
      // happens that we aren't accounting for. We should track those down and
      // fix them, but it can be tricky.
      NOTREACHED() << "Attempted to downgrade extension."
                   << "\nID: " << extension->id()
                   << "\nOld Version: " << old->version()
                   << "\nNew Version: " << extension->version()
                   << "\nLocation: " << extension->location();
      return;
    }
  }

  // If the extension was disabled for a reload, we will enable it.
  bool was_reloading = reloading_extensions_.erase(extension->id()) > 0;

  // Set the upgraded bit; we consider reloads upgrades.
  extension_system_->runtime_data()->SetBeingUpgraded(
      extension->id(), is_extension_upgrade || was_reloading);

  // The extension is now loaded; remove its data from unloaded extension map.
  unloaded_extension_paths_.erase(extension->id());

  // If a terminated extension is loaded, remove it from the terminated list.
  UntrackTerminatedExtension(extension->id());

  // Notify the delegate we will add the extension.
  delegate_->PreAddExtension(extension.get(), old);

  if (was_reloading) {
    failed_to_reload_unpacked_extensions_.erase(extension->path());
    ReplaceReloadedExtension(extension);
  } else {
    if (is_extension_loaded) {
      // To upgrade an extension in place, remove the old one and then activate
      // the new one. ReloadExtension disables the extension, which is
      // sufficient.
      RemoveExtension(extension->id(), UnloadedExtensionReason::UPDATE);
    }
    AddNewExtension(extension);
  }

<<<<<<< HEAD
  if (registry_->disabled_extensions().Contains(extension->id())) {
    // Show the extension disabled error if a permissions increase or a remote
    // installation is the reason it was disabled, and no other reasons exist.
    int reasons = extension_prefs_->GetDisableReasons(extension->id());
    const int kReasonMask = disable_reason::DISABLE_PERMISSIONS_INCREASE |
                            disable_reason::DISABLE_REMOTE_INSTALL;
    if (reasons & kReasonMask && !(reasons & ~kReasonMask)) {
      delegate_->ShowExtensionDisabledError(
          extension.get(),
          extension_prefs_->HasDisableReason(
              extension->id(), disable_reason::DISABLE_REMOTE_INSTALL));
    }
  }
=======
  extension_system_->runtime_data()->SetBeingUpgraded(extension->id(), false);
>>>>>>> chromium
}

void ExtensionRegistrar::AddNewExtension(
    scoped_refptr<const Extension> extension) {
  if (extension_prefs_->IsExtensionBlocklisted(extension->id())) {
    DCHECK(!Manifest::IsComponentLocation(extension->location()));
    // Only prefs is checked for the blocklist. We rely on callers to check the
    // blocklist before calling into here, e.g. CrxInstaller checks before
    // installation then threads through the install and pending install flow
    // of this class, and ExtensionService checks when loading installed
    // extensions.
    registry_->AddBlocklisted(extension);
  } else if (delegate_->ShouldBlockExtension(extension.get())) {
    DCHECK(!Manifest::IsComponentLocation(extension->location()));
    registry_->AddBlocked(extension);
  } else if (extension_prefs_->IsExtensionDisabled(extension->id())) {
    registry_->AddDisabled(extension);
    // Notify that a disabled extension was added or updated.
    content::NotificationService::current()->Notify(
        extensions::NOTIFICATION_EXTENSION_UPDATE_DISABLED,
        content::Source<content::BrowserContext>(browser_context_),
        content::Details<const Extension>(extension.get()));
  } else {  // Extension should be enabled.
    // All apps that are displayed in the launcher are ordered by their ordinals
    // so we must ensure they have valid ordinals.
    if (extension->RequiresSortOrdinal()) {
      AppSorting* app_sorting = extension_system_->app_sorting();
      app_sorting->SetExtensionVisible(extension->id(),
                                       extension->ShouldDisplayInNewTabPage());
      app_sorting->EnsureValidOrdinals(extension->id(),
                                       syncer::StringOrdinal());
    }
    registry_->AddEnabled(extension);
    ActivateExtension(extension.get(), true);
  }
}

void ExtensionRegistrar::RemoveExtension(const ExtensionId& extension_id,
                                         UnloadedExtensionReason reason) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  int include_mask =
      ExtensionRegistry::EVERYTHING & ~ExtensionRegistry::TERMINATED;
  scoped_refptr<const Extension> extension(
      registry_->GetExtensionById(extension_id, include_mask));

  // If the extension was already removed, just notify of the new unload reason.
  // TODO: It's unclear when this needs to be called given that it may be a
  // duplicate notification. See crbug.com/708230.
  if (!extension) {
    extension_system_->UnregisterExtensionWithRequestContexts(extension_id,
                                                              reason);
    return;
  }

  // Keep information about the extension so that we can reload it later
  // even if it's not permanently installed.
  unloaded_extension_paths_[extension->id()] = extension->path();

  // Stop tracking whether the extension was meant to be enabled after a reload.
  reloading_extensions_.erase(extension->id());

  if (registry_->disabled_extensions().Contains(extension_id)) {
    // The extension is already deactivated.
    registry_->RemoveDisabled(extension->id());
    extension_system_->UnregisterExtensionWithRequestContexts(extension_id,
                                                              reason);
  } else {
    // TODO(michaelpg): The extension may be blocked or blocklisted, in which
    // case it shouldn't need to be "deactivated". Determine whether the removal
    // notifications are necessary (crbug.com/708230).
    registry_->RemoveEnabled(extension_id);
    DeactivateExtension(extension.get(), reason);
  }

  content::NotificationService::current()->Notify(
      extensions::NOTIFICATION_EXTENSION_REMOVED,
      content::Source<content::BrowserContext>(browser_context_),
      content::Details<const Extension>(extension.get()));
}

void ExtensionRegistrar::EnableExtension(const ExtensionId& extension_id) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  // If the extension is currently reloading, it will be enabled once the reload
  // is complete.
  if (reloading_extensions_.count(extension_id) > 0)
    return;

  // First, check that the extension can be enabled.
  if (IsExtensionEnabled(extension_id) ||
      extension_prefs_->IsExtensionBlocklisted(extension_id) ||
      registry_->blocked_extensions().Contains(extension_id)) {
    return;
  }

  const Extension* extension =
      registry_->disabled_extensions().GetByID(extension_id);
  if (extension && !delegate_->CanEnableExtension(extension))
    return;

  // Now that we know the extension can be enabled, update the prefs.
  extension_prefs_->SetExtensionEnabled(extension_id);

  // This can happen if sync enables an extension that is not installed yet.
  if (!extension)
    return;

  // Actually enable the extension.
  registry_->AddEnabled(extension);
  registry_->RemoveDisabled(extension->id());
  ActivateExtension(extension, false);
}

void ExtensionRegistrar::DisableExtension(const ExtensionId& extension_id,
                                          int disable_reasons) {
  auto passkey = ExtensionPrefs::DisableReasonRawManipulationPasskey();
  DisableExtension(passkey, extension_id, BitflagToIntegerSet(disable_reasons));
}

void ExtensionRegistrar::DisableExtension(
    ExtensionPrefs::DisableReasonRawManipulationPasskey,
    const ExtensionId& extension_id,
    base::flat_set<int> disable_reasons) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  DCHECK(!disable_reasons.empty());

  scoped_refptr<const Extension> extension =
      registry_->GetExtensionById(extension_id, ExtensionRegistry::EVERYTHING);

  bool is_controlled_extension =
      !delegate_->CanDisableExtension(extension.get());

  if (is_controlled_extension) {
    // Remove disallowed disable reasons.
    // Certain disable reasons are always allowed, since they are more internal
    // to the browser (rather than the user choosing to disable the extension).
<<<<<<< HEAD
    base::flat_set<int> internal_disable_reasons = {
        extensions::disable_reason::DISABLE_RELOAD,
        extensions::disable_reason::DISABLE_CORRUPTED,
        extensions::disable_reason::DISABLE_UPDATE_REQUIRED_BY_POLICY,
        extensions::disable_reason::
            DISABLE_PUBLISHED_IN_STORE_REQUIRED_BY_POLICY,
        extensions::disable_reason::DISABLE_BLOCKED_BY_POLICY,
        extensions::disable_reason::DISABLE_CUSTODIAN_APPROVAL_REQUIRED,
        extensions::disable_reason::DISABLE_REINSTALL,
        extensions::disable_reason::DISABLE_UNSUPPORTED_MANIFEST_VERSION,
        extensions::disable_reason::DISABLE_NOT_VERIFIED,
        extensions::disable_reason::DISABLE_UNSUPPORTED_DEVELOPER_EXTENSION,
    };

    disable_reasons = base::STLSetIntersection<base::flat_set<int>>(
        disable_reasons, internal_disable_reasons);

    if (disable_reasons.empty()) {
=======
    int internal_disable_reason_mask =
        extensions::disable_reason::DISABLE_RELOAD |
        extensions::disable_reason::DISABLE_CORRUPTED |
        extensions::disable_reason::DISABLE_UPDATE_REQUIRED_BY_POLICY |
        extensions::disable_reason::DISABLE_BLOCKED_BY_POLICY |
        extensions::disable_reason::DISABLE_CUSTODIAN_APPROVAL_REQUIRED |
        extensions::disable_reason::DISABLE_REINSTALL;
    disable_reasons &= internal_disable_reason_mask;

    if (disable_reasons == disable_reason::DISABLE_NONE)
>>>>>>> chromium
      return;
    }
  }

  auto passkey = ExtensionPrefs::DisableReasonRawManipulationPasskey();

  // The extension may have been disabled already. Just add the disable reasons.
  if (!IsExtensionEnabled(extension_id)) {
    extension_prefs_->AddDisableReasons(passkey, extension_id, disable_reasons);
    return;
  }

  extension_prefs_->SetExtensionDisabled(passkey, extension_id,
                                         disable_reasons);

  int include_mask =
      ExtensionRegistry::EVERYTHING & ~ExtensionRegistry::DISABLED;
  extension = registry_->GetExtensionById(extension_id, include_mask);
  if (!extension)
    return;

  // The extension is either enabled or terminated.
  DCHECK(registry_->enabled_extensions().Contains(extension->id()) ||
         registry_->terminated_extensions().Contains(extension->id()));

  // Move the extension to the disabled list.
  registry_->AddDisabled(extension);
  if (registry_->enabled_extensions().Contains(extension->id())) {
    registry_->RemoveEnabled(extension->id());
    DeactivateExtension(extension.get(), UnloadedExtensionReason::DISABLE);
  } else {
    // The extension must have been terminated. Don't send additional
    // notifications for it being disabled.
    bool removed = registry_->RemoveTerminated(extension->id());
    DCHECK(removed);
  }
}

<<<<<<< HEAD
void ExtensionRegistrar::DisableExtensionWithSource(
    const Extension* source_extension,
    const std::string& extension_id,
    disable_reason::DisableReason disable_reasons) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  DCHECK(disable_reasons == disable_reason::DISABLE_USER_ACTION ||
         disable_reasons == disable_reason::DISABLE_BLOCKED_BY_POLICY);
  if (disable_reasons == disable_reason::DISABLE_BLOCKED_BY_POLICY) {
    DCHECK(Manifest::IsPolicyLocation(source_extension->location()) ||
           Manifest::IsComponentLocation(source_extension->location()));
  }

  const Extension* extension =
      registry_->GetExtensionById(extension_id, ExtensionRegistry::EVERYTHING);
  CHECK(extension_system_->management_policy()->ExtensionMayModifySettings(
      source_extension, extension, nullptr));
  DisableExtension(extension_id, disable_reasons);
}

void ExtensionRegistrar::EnabledReloadableExtensions() {
  std::vector<std::string> extensions_to_enable;
  for (const auto& e : registry_->disabled_extensions()) {
    if (extension_prefs_->GetDisableReasons(e->id()) ==
        disable_reason::DISABLE_RELOAD) {
      extensions_to_enable.push_back(e->id());
    }
  }
  for (const std::string& extension : extensions_to_enable) {
    EnableExtension(extension);
  }
}

void ExtensionRegistrar::RemoveComponentExtension(
    const std::string& extension_id) {
  scoped_refptr<const Extension> extension(
      registry_->enabled_extensions().GetByID(extension_id));
  RemoveExtension(extension_id, UnloadedExtensionReason::UNINSTALL);
  if (extension.get()) {
    registry_->TriggerOnUninstalled(extension.get(),
                                    UNINSTALL_REASON_COMPONENT_REMOVED);
  }
}

void ExtensionRegistrar::RemoveDisableReasonAndMaybeEnable(
    const std::string& extension_id,
    disable_reason::DisableReason reason_to_remove) {
  auto disable_reason = extension_prefs_->GetDisableReasons(extension_id);
  if ((disable_reason & reason_to_remove) == 0) {
    return;
  }

  extension_prefs_->RemoveDisableReason(extension_id, reason_to_remove);
  if (disable_reason == reason_to_remove) {
    EnableExtension(extension_id);
  }
}

namespace {
std::vector<scoped_refptr<DevToolsAgentHost>> GetDevToolsAgentHostsFor(
    ProcessManager* process_manager,
    const Extension* extension) {
  std::vector<scoped_refptr<DevToolsAgentHost>> result;
  if (!BackgroundInfo::IsServiceWorkerBased(extension)) {
    ExtensionHost* host =
        process_manager->GetBackgroundHostForExtension(extension->id());
    if (host) {
      content::WebContents* const wc = host->host_contents();
      if (auto tab_host = content::DevToolsAgentHost::GetForTab(wc)) {
        result.push_back(tab_host);
      }
      if (content::DevToolsAgentHost::HasFor(wc)) {
        result.push_back(content::DevToolsAgentHost::GetOrCreateFor(wc));
      }
    }
  } else {
    content::ServiceWorkerContext* context =
        util::GetServiceWorkerContextForExtensionId(
            extension->id(), process_manager->browser_context());
    std::vector<WorkerId> service_worker_ids =
        process_manager->GetServiceWorkersForExtension(extension->id());
    for (const auto& worker_id : service_worker_ids) {
      auto devtools_host =
          DevToolsAgentHost::GetForServiceWorker(context, worker_id.version_id);
      if (devtools_host)
        result.push_back(std::move(devtools_host));
    }
  }
  return result;
}
}  // namespace

=======
>>>>>>> chromium
void ExtensionRegistrar::ReloadExtension(
    const ExtensionId extension_id,  // Passed by value because reloading can
                                     // invalidate a reference to the ID.
    LoadErrorBehavior load_error_behavior) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  base::FilePath path;

  const Extension* disabled_extension =
      registry_->disabled_extensions().GetByID(extension_id);

  if (disabled_extension) {
    path = disabled_extension->path();
  }

  // If the extension is already reloading, don't reload again.
  if (extension_prefs_->HasDisableReason(extension_id,
                                         disable_reason::DISABLE_RELOAD)) {
    DCHECK(disabled_extension);
    // If an unpacked extension previously failed to reload, it will still be
    // marked as disabled, but we can try to reload it again - the developer
    // may have fixed the issue.
    if (failed_to_reload_unpacked_extensions_.count(path) == 0)
      return;
    failed_to_reload_unpacked_extensions_.erase(path);
  }
  // Ignore attempts to reload a blocklisted or blocked extension. Sometimes
  // this can happen in a convoluted reload sequence triggered by the
  // termination of a blocklisted or blocked extension and a naive attempt to
  // reload it. For an example see http://crbug.com/373842.
  if (registry_->blocklisted_extensions().Contains(extension_id) ||
      registry_->blocked_extensions().Contains(extension_id)) {
    return;
  }

  const Extension* enabled_extension =
      registry_->enabled_extensions().GetByID(extension_id);

  // Disable the extension if it's loaded. It might not be loaded if it crashed.
  if (enabled_extension) {
    // If the extension has an inspector open for its background page, detach
    // the inspector and hang onto a cookie for it, so that we can reattach
    // later.
    // TODO(yoz): this is not incognito-safe!
    ProcessManager* manager = ProcessManager::Get(browser_context_);
    ExtensionHost* host = manager->GetBackgroundHostForExtension(extension_id);
    if (host && content::DevToolsAgentHost::HasFor(host->host_contents())) {
      // Look for an open inspector for the background page.
      scoped_refptr<content::DevToolsAgentHost> agent_host =
          content::DevToolsAgentHost::GetOrCreateFor(host->host_contents());
      agent_host->DisconnectWebContents();
      orphaned_dev_tools_[extension_id] = agent_host;
    }

    path = enabled_extension->path();
    // BeingUpgraded is set back to false when the extension is added.
    extension_system_->runtime_data()->SetBeingUpgraded(enabled_extension->id(),
                                                        true);
    DisableExtension(extension_id, disable_reason::DISABLE_RELOAD);
    DCHECK(registry_->disabled_extensions().Contains(extension_id));
    reloading_extensions_.insert(extension_id);
  } else if (!disabled_extension) {
    std::map<ExtensionId, base::FilePath>::const_iterator iter =
        unloaded_extension_paths_.find(extension_id);
    if (iter == unloaded_extension_paths_.end()) {
      return;
    }
    path = unloaded_extension_paths_[extension_id];
  }

  delegate_->LoadExtensionForReload(extension_id, path, load_error_behavior);
}

bool ExtensionRegistrar::UninstallExtension(
    // "transient" because the process of uninstalling may cause the reference
    // to become invalid. Instead, use |extension->id()|.
    const std::string& transient_extension_id,
    UninstallReason reason,
    std::u16string* error,
    base::OnceClosure done_callback) {
  CHECK(content::BrowserThread::CurrentlyOn(content::BrowserThread::UI));

  scoped_refptr<const Extension> extension =
      registry_->GetInstalledExtension(transient_extension_id);

  // Callers should not send us nonexistent extensions.
  CHECK(extension.get());

  ManagementPolicy* by_policy = extension_system_->management_policy();
  // Policy change which triggers an uninstall will always set
  // |external_uninstall| to true so this is the only way to uninstall
  // managed extensions.
  // Shared modules being uninstalled will also set |external_uninstall| to true
  // so that we can guarantee users don't uninstall a shared module.
  // (crbug.com/273300)
  // TODO(rdevlin.cronin): This is probably not right. We should do something
  // else, like include an enum IS_INTERNAL_UNINSTALL or IS_USER_UNINSTALL so
  // we don't do this.
  bool external_uninstall =
      (reason == UNINSTALL_REASON_INTERNAL_MANAGEMENT) ||
      (reason == UNINSTALL_REASON_COMPONENT_REMOVED) ||
      (reason == UNINSTALL_REASON_MIGRATED) ||
      (reason == UNINSTALL_REASON_REINSTALL) ||
      (reason == UNINSTALL_REASON_ORPHANED_EXTERNAL_EXTENSION) ||
      (reason == UNINSTALL_REASON_ORPHANED_SHARED_MODULE);
  if (!external_uninstall &&
      (!by_policy->UserMayModifySettings(extension.get(), error) ||
       by_policy->MustRemainInstalled(extension.get(), error))) {
    registry_->TriggerOnUninstallationDenied(extension.get());
    return false;
  }

  // Prepare to uninstall the extension.
  delegate_->PreUninstallExtension(extension.get());

  UMA_HISTOGRAM_ENUMERATION("Extensions.UninstallType", extension->GetType(),
                            100);

  // Unload before doing more cleanup to ensure that nothing is hanging on to
  // any of these resources.
  RemoveExtension(extension->id(), UnloadedExtensionReason::UNINSTALL);

  // `UnloadExtension` ignores extensions that are `BLOCKLISTED` or `BLOCKED`
  if (registry_->blocklisted_extensions().Contains(extension->id())) {
    registry_->RemoveBlocklisted(extension->id());
  }
  if (registry_->blocked_extensions().Contains(extension->id())) {
    registry_->RemoveBlocked(extension->id());
  }

  // Perform the necessary clean up after the extension is un-registered.
  delegate_->PostUninstallExtension(extension, std::move(done_callback));

  UntrackTerminatedExtension(extension->id());

  // Notify interested parties that we've uninstalled this extension.
  registry_->TriggerOnUninstalled(extension.get(), reason);

  // Perform the necessary clean up work after extension un-installation event
  // has been notified to all observers.
  delegate_->PostNotifyUninstallExtension(extension.get());

  extension_prefs_->OnExtensionUninstalled(
      extension->id(), extension->location(), external_uninstall);

  return true;
}

void ExtensionRegistrar::UninstallMigratedExtensions(
    base::span<const char* const> migrated_ids) {
  const ExtensionSet installed_extensions =
      registry_->GenerateInstalledExtensionsSet();
  for (const auto* extension_id : migrated_ids) {
    auto* extension = installed_extensions.GetByID(extension_id);
    if (extension) {
      UninstallExtension(extension_id, UNINSTALL_REASON_COMPONENT_REMOVED,
                         nullptr);
      extension_prefs_->MarkObsoleteComponentExtensionAsRemoved(
          extension->id(), extension->location());
    }
  }
}

void ExtensionRegistrar::FinishInstallation(const Extension* extension) {
  const Extension* existing_extension =
      registry_->GetInstalledExtension(extension->id());
  bool is_update = false;
  std::string old_name;
  if (existing_extension) {
    is_update = true;
    old_name = existing_extension->name();
  }
  registry_->TriggerOnWillBeInstalled(extension, is_update, old_name);

  // Unpacked extensions default to allowing file access, but if that has been
  // overridden, don't reset the value.
  if (Manifest::ShouldAlwaysAllowFileAccess(extension->location()) &&
      !extension_prefs_->HasAllowFileAccessSetting(extension->id())) {
    extension_prefs_->SetAllowFileAccess(extension->id(), true);
  }

  AddExtension(extension);

  // Notify observers that need to know when an installation is complete.
  registry_->TriggerOnInstalled(extension, is_update);

  // Check extensions that may have been delayed only because this shared module
  // was not available.
  if (SharedModuleInfo::IsSharedModule(extension)) {
    delegate_->FinishDelayedInstallationsIfAny();
  }
}

bool ExtensionRegistrar::CanBlockExtension(const Extension* extension) const {
  DCHECK(extension);
  return extension->location() != ManifestLocation::kComponent &&
         extension->location() != ManifestLocation::kExternalComponent &&
         !extension_system_->management_policy()->MustRemainEnabled(extension,
                                                                    nullptr);
}

// Extensions that are not locked, components or forced by policy should be
// locked. Extensions are no longer considered enabled or disabled. Blocklisted
// extensions are now considered both blocklisted and locked.
void ExtensionRegistrar::BlockAllExtensions() {
  // Blocklisted extensions are already unloaded, need not be blocked.
  const ExtensionSet extensions = registry_->GenerateInstalledExtensionsSet(
      ExtensionRegistry::ENABLED | ExtensionRegistry::DISABLED |
      ExtensionRegistry::TERMINATED);

  for (const auto& extension : extensions) {
    const std::string& id = extension->id();

    if (!CanBlockExtension(extension.get())) {
      continue;
    }

    registry_->AddBlocked(extension.get());
    RemoveExtension(id, UnloadedExtensionReason::LOCK_ALL);
  }
}

void ExtensionRegistrar::UnblockAllExtensions() {
  const ExtensionSet to_unblock =
      registry_->GenerateInstalledExtensionsSet(ExtensionRegistry::BLOCKED);

  for (const auto& extension : to_unblock) {
    registry_->RemoveBlocked(extension->id());
    AddExtension(extension.get());
  }
}

void ExtensionRegistrar::OnBlocklistStateRemoved(
    const std::string& extension_id) {
  if (blocklist_prefs::IsExtensionBlocklisted(extension_id, extension_prefs_)) {
    return;
  }

  // Clear acknowledged state.
  blocklist_prefs::RemoveAcknowledgedBlocklistState(
      extension_id, BitMapBlocklistState::BLOCKLISTED_MALWARE,
      extension_prefs_);

  scoped_refptr<const Extension> extension =
      registry_->blocklisted_extensions().GetByID(extension_id);
  DCHECK(extension);
  registry_->RemoveBlocklisted(extension_id);
  AddExtension(extension.get());
}

void ExtensionRegistrar::OnBlocklistStateAdded(
    const std::string& extension_id) {
  DCHECK(
      blocklist_prefs::IsExtensionBlocklisted(extension_id, extension_prefs_));
  // The extension was already acknowledged by the user, it should already be in
  // the unloaded state.
  if (blocklist_prefs::HasAcknowledgedBlocklistState(
          extension_id, BitMapBlocklistState::BLOCKLISTED_MALWARE,
          extension_prefs_)) {
    DCHECK(base::Contains(registry_->blocklisted_extensions().GetIDs(),
                          extension_id));
    return;
  }

  scoped_refptr<const Extension> extension =
      registry_->GetInstalledExtension(extension_id);
  registry_->AddBlocklisted(extension);
  RemoveExtension(extension_id, UnloadedExtensionReason::BLOCKLIST);
}

void ExtensionRegistrar::OnGreylistStateRemoved(
    const std::string& extension_id) {
  bool is_on_sb_list = (blocklist_prefs::GetSafeBrowsingExtensionBlocklistState(
                            extension_id, extension_prefs_) !=
                        BitMapBlocklistState::NOT_BLOCKLISTED);
  bool is_on_omaha_list =
      blocklist_prefs::HasAnyOmahaGreylistState(extension_id, extension_prefs_);
  if (is_on_sb_list || is_on_omaha_list) {
    return;
  }
  // Clear all acknowledged states so the extension will still get disabled if
  // it is added to the greylist again.
  blocklist_prefs::ClearAcknowledgedGreylistStates(extension_id,
                                                   extension_prefs_);
  RemoveDisableReasonAndMaybeEnable(extension_id,
                                    disable_reason::DISABLE_GREYLIST);
}

void ExtensionRegistrar::OnGreylistStateAdded(const std::string& extension_id,
                                              BitMapBlocklistState new_state) {
#if DCHECK_IS_ON()
  bool has_new_state_on_sb_list =
      (blocklist_prefs::GetSafeBrowsingExtensionBlocklistState(
           extension_id, extension_prefs_) == new_state);
  bool has_new_state_on_omaha_list = blocklist_prefs::HasOmahaBlocklistState(
      extension_id, new_state, extension_prefs_);
  DCHECK(has_new_state_on_sb_list || has_new_state_on_omaha_list);
#endif
  if (blocklist_prefs::HasAcknowledgedBlocklistState(extension_id, new_state,
                                                     extension_prefs_)) {
    // If the extension is already acknowledged, don't disable it again
    // because it can be already re-enabled by the user. This could happen if
    // the extension is added to the SafeBrowsing blocklist, and then
    // subsequently marked by Omaha. In this case, we don't want to disable the
    // extension twice.
    return;
  }

  // Set the current greylist states to acknowledge immediately because the
  // extension is disabled silently. Clear the other acknowledged state because
  // when the state changes to another greylist state in the future, we'd like
  // to disable the extension again.
  blocklist_prefs::UpdateCurrentGreylistStatesAsAcknowledged(extension_id,
                                                             extension_prefs_);
  DisableExtension(extension_id, disable_reason::DISABLE_GREYLIST);
}

void ExtensionRegistrar::BlocklistExtensionForTest(
    const std::string& extension_id) {
  blocklist_prefs::SetSafeBrowsingExtensionBlocklistState(
      extension_id, BitMapBlocklistState::BLOCKLISTED_MALWARE,
      extension_prefs_);
  OnBlocklistStateAdded(extension_id);
}

void ExtensionRegistrar::GreylistExtensionForTest(
    const std::string& extension_id,
    const BitMapBlocklistState& state) {
  blocklist_prefs::SetSafeBrowsingExtensionBlocklistState(extension_id, state,
                                                          extension_prefs_);
  OnGreylistStateAdded(extension_id, state);
}

void ExtensionRegistrar::OnUnpackedExtensionReloadFailed(
    const base::FilePath& path) {
  failed_to_reload_unpacked_extensions_.insert(path);
}

void ExtensionRegistrar::TerminateExtension(const ExtensionId& extension_id) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  scoped_refptr<const Extension> extension =
      registry_->enabled_extensions().GetByID(extension_id);
  if (!extension)
    return;

  // Keep information about the extension so that we can reload it later
  // even if it's not permanently installed.
  unloaded_extension_paths_[extension->id()] = extension->path();

  DCHECK(!base::Contains(reloading_extensions_, extension->id()))
      << "Enabled extension shouldn't be marked for reloading";

  registry_->AddTerminated(extension);
  registry_->RemoveEnabled(extension_id);
  DeactivateExtension(extension.get(), UnloadedExtensionReason::TERMINATE);
}

void ExtensionRegistrar::UntrackTerminatedExtension(
    const ExtensionId& extension_id) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  scoped_refptr<const Extension> extension =
      registry_->terminated_extensions().GetByID(extension_id);
  if (!extension)
    return;

  registry_->RemoveTerminated(extension_id);

  // TODO(michaelpg): This notification was already sent when the extension was
  // unloaded as part of being terminated. But we send it again as observers
  // may be tracking the terminated extension. See crbug.com/708230.
  content::NotificationService::current()->Notify(
      extensions::NOTIFICATION_EXTENSION_REMOVED,
      content::Source<content::BrowserContext>(browser_context_),
      content::Details<const Extension>(extension.get()));
}

bool ExtensionRegistrar::IsExtensionEnabled(
    const ExtensionId& extension_id) const {
  if (registry_->enabled_extensions().Contains(extension_id) ||
      registry_->terminated_extensions().Contains(extension_id)) {
    return true;
  }

  if (registry_->disabled_extensions().Contains(extension_id) ||
      registry_->blocklisted_extensions().Contains(extension_id) ||
      registry_->blocked_extensions().Contains(extension_id)) {
    return false;
  }

  if (delegate_->ShouldBlockExtension(nullptr))
    return false;

  // If the extension hasn't been loaded yet, check the prefs for it. Assume
  // enabled unless otherwise noted.
  return !extension_prefs_->IsExtensionDisabled(extension_id) &&
         !extension_prefs_->IsExtensionBlocklisted(extension_id) &&
         !extension_prefs_->IsExternalExtensionUninstalled(extension_id);
}

void ExtensionRegistrar::DidCreateMainFrameForBackgroundPage(
    ExtensionHost* host) {
  auto iter = orphaned_dev_tools_.find(host->extension_id());
  if (iter == orphaned_dev_tools_.end())
    return;
  // Keepalive count is reset on extension reload. This re-establishes the
  // keepalive that was added when the DevTools agent was initially attached.
  ProcessManager::Get(browser_context_)
      ->IncrementLazyKeepaliveCount(host->extension(), Activity::DEV_TOOLS,
                                    std::string());
  iter->second->ConnectWebContents(host->host_contents());
  orphaned_dev_tools_.erase(iter);
}

void ExtensionRegistrar::ActivateExtension(const Extension* extension,
                                           bool is_newly_added) {
  // The URLRequestContexts need to be first to know that the extension
  // was loaded. Otherwise a race can arise where a renderer that is created
  // for the extension may try to load an extension URL with an extension id
  // that the request context doesn't yet know about. The BrowserContext should
  // ensure its URLRequestContexts appropriately discover the loaded extension.
  extension_system_->RegisterExtensionWithRequestContexts(
      extension,
      base::BindOnce(
          &ExtensionRegistrar::OnExtensionRegisteredWithRequestContexts,
          weak_factory_.GetWeakPtr(), WrapRefCounted(extension)));

  // Activate the extension before calling
  // RendererStartupHelper::OnExtensionLoaded() below, so that we have
  // activation information ready while we send ExtensionMsg_Load IPC.
  //
  // TODO(lazyboy): We should move all logic that is required to start up an
  // extension to a separate class, instead of calling adhoc methods like
  // service worker ones below.
  ActivateTaskQueueForExtension(browser_context_, extension);

  renderer_helper_->OnExtensionLoaded(*extension);

  // Tell subsystems that use the ExtensionRegistryObserver::OnExtensionLoaded
  // about the new extension.
  //
  // NOTE: It is important that this happen after notifying the renderers about
  // the new extensions so that if we navigate to an extension URL in
  // ExtensionRegistryObserver::OnExtensionLoaded the renderer is guaranteed to
  // know about it.
  registry_->TriggerOnLoaded(extension);

  delegate_->PostActivateExtension(extension);

  // When an existing extension is re-enabled, it may be necessary to spin up
  // its lazy background page.
  if (!is_newly_added)
    MaybeSpinUpLazyBackgroundPage(extension);
}

void ExtensionRegistrar::DeactivateExtension(const Extension* extension,
                                             UnloadedExtensionReason reason) {
  registry_->TriggerOnUnloaded(extension, reason);
  renderer_helper_->OnExtensionUnloaded(*extension);
  extension_system_->UnregisterExtensionWithRequestContexts(extension->id(),
                                                            reason);
  DeactivateTaskQueueForExtension(browser_context_, extension);

  delegate_->PostDeactivateExtension(extension);
}

bool ExtensionRegistrar::ReplaceReloadedExtension(
    scoped_refptr<const Extension> extension) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  // The extension must already be disabled, and the original extension has
  // been unloaded.
  CHECK(registry_->disabled_extensions().Contains(extension->id()));
  if (!delegate_->CanEnableExtension(extension.get()))
    return false;

  // TODO(michaelpg): Other disable reasons might have been added after the
  // reload started. We may want to keep the extension disabled and just remove
  // the DISABLE_RELOAD reason in that case.
  extension_prefs_->SetExtensionEnabled(extension->id());

  // Move it over to the enabled list.
  CHECK(registry_->RemoveDisabled(extension->id()));
  CHECK(registry_->AddEnabled(extension));

  ActivateExtension(extension.get(), false);

  return true;
}

void ExtensionRegistrar::OnExtensionRegisteredWithRequestContexts(
    scoped_refptr<const Extension> extension) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  registry_->AddReady(extension);
  if (registry_->enabled_extensions().Contains(extension->id()))
    registry_->TriggerOnReady(extension.get());
}

void ExtensionRegistrar::MaybeSpinUpLazyBackgroundPage(
    const Extension* extension) {
  if (!BackgroundInfo::HasLazyBackgroundPage(extension))
    return;

  // For orphaned devtools, we will reconnect devtools to it later in
  // DidCreateMainFrameForBackgroundPage().
  bool has_orphaned_dev_tools =
      base::Contains(orphaned_dev_tools_, extension->id());

  // Reloading component extension does not trigger install, so RuntimeAPI won't
  // be able to detect its loading. Therefore, we need to spin up its lazy
  // background page.
  bool is_component_extension =
      Manifest::IsComponentLocation(extension->location());

  if (!has_orphaned_dev_tools && !is_component_extension)
    return;

  // Wake up the event page by posting a dummy task.
  const LazyContextId context_id(browser_context_, extension->id());
  context_id.GetTaskQueue()->AddPendingTask(context_id, base::DoNothing());
}

}  // namespace extensions
