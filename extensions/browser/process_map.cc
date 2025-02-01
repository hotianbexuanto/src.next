// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/browser/process_map.h"

<<<<<<< HEAD
#include <algorithm>
#include <string>
=======
>>>>>>> chromium
#include <tuple>

#include "content/public/browser/child_process_security_policy.h"
#include "content/public/common/url_constants.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/process_map_factory.h"
#include "extensions/common/extension.h"
#include "extensions/common/features/feature.h"

namespace extensions {

// Item
struct ProcessMap::Item {
  Item(const std::string& extension_id, int process_id,
       int site_instance_id)
      : extension_id(extension_id),
        process_id(process_id),
        site_instance_id(site_instance_id) {
  }

  ~Item() {
  }

  Item(ProcessMap::Item&&) = default;
  Item& operator=(ProcessMap::Item&&) = default;

  bool operator<(const ProcessMap::Item& other) const {
    return std::tie(extension_id, process_id, site_instance_id) <
           std::tie(other.extension_id, other.process_id,
                    other.site_instance_id);
  }

  std::string extension_id;
  int process_id = 0;
  int site_instance_id = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Item);
};


// ProcessMap
ProcessMap::ProcessMap() {
}

ProcessMap::~ProcessMap() {
}

// static
ProcessMap* ProcessMap::Get(content::BrowserContext* browser_context) {
  return ProcessMapFactory::GetForBrowserContext(browser_context);
}

bool ProcessMap::Insert(const std::string& extension_id, int process_id,
                        int site_instance_id) {
  return items_.insert(Item(extension_id, process_id, site_instance_id)).second;
}

bool ProcessMap::Remove(const std::string& extension_id, int process_id,
                        int site_instance_id) {
  return items_.erase(Item(extension_id, process_id, site_instance_id)) > 0;
}

int ProcessMap::RemoveAllFromProcess(int process_id) {
  int result = 0;
  for (auto iter = items_.begin(); iter != items_.end();) {
    if (iter->process_id == process_id) {
      items_.erase(iter++);
      ++result;
    } else {
      ++iter;
    }
  }
  return result;
}

bool ProcessMap::Contains(const std::string& extension_id,
                          int process_id) const {
  for (auto iter = items_.cbegin(); iter != items_.cend(); ++iter) {
    if (iter->process_id == process_id && iter->extension_id == extension_id)
      return true;
  }
  return false;
}

bool ProcessMap::Contains(int process_id) const {
<<<<<<< HEAD
  return base::Contains(items_, process_id);
}

bool ProcessMap::ExtensionHasProcess(const ExtensionId& extension_id) const {
  return std::ranges::find_if(items_, [extension_id](const auto& entry) {
           return entry.second == extension_id;
         }) != items_.end();
}

const Extension* ProcessMap::GetEnabledExtensionByProcessID(
    int process_id) const {
  auto* extension_id = base::FindOrNull(items_, process_id);
  return extension_id ? ExtensionRegistry::Get(browser_context_)
                            ->enabled_extensions()
                            .GetByID(*extension_id)
                      : nullptr;
}

std::optional<ExtensionId> ProcessMap::GetExtensionIdForProcess(
    int process_id) const {
  return base::OptionalFromPtr(base::FindOrNull(items_, process_id));
}

bool ProcessMap::IsPrivilegedExtensionProcess(const Extension& extension,
                                              int process_id) {
  return Contains(extension.id(), process_id) &&
         // Hosted apps aren't considered privileged extension processes...
         (!extension.is_hosted_app() ||
          // ... Unless they're component hosted apps, like the webstore.
          // TODO(https://crbug/1429667): We can clean this up when we remove
          // special handling of component hosted apps.
          extension.location() == mojom::ManifestLocation::kComponent);
}

bool ProcessMap::CanProcessHostContextType(
    const Extension* extension,
    const content::RenderProcessHost& process,
    mojom::ContextType context_type) {
  const int process_id = process.GetDeprecatedID();
  switch (context_type) {
    case mojom::ContextType::kUnspecified:
      // We never consider unspecified contexts valid. Even though they would be
      // permissionless, they should never be able to make a request to the
      // browser.
      return false;
    case mojom::ContextType::kOffscreenExtension:
    case mojom::ContextType::kPrivilegedExtension:
      // Offscreen documents run in the main extension process, so both of these
      // require a privileged extension process.
      return extension && IsPrivilegedExtensionProcess(*extension, process_id);
    case mojom::ContextType::kUnprivilegedExtension:
      return extension &&
             IsWebViewProcessForExtension(process_id, extension->id());
    case mojom::ContextType::kContentScript:
      // Currently, we assume any process can host a content script.
      // TODO(crbug.com/40055126): This could be better by looking at
      // ScriptInjectionTracker, as we do for user scripts below.
      return !!extension;
    case mojom::ContextType::kUserScript:
      return extension &&
             ScriptInjectionTracker::DidProcessRunUserScriptFromExtension(
                 process, extension->id());
    case mojom::ContextType::kPrivilegedWebPage:
      // A privileged web page is a (non-component) hosted app process.
      return extension && extension->is_hosted_app() &&
             extension->location() != mojom::ManifestLocation::kComponent &&
             Contains(extension->id(), process_id);
    case mojom::ContextType::kUntrustedWebUi:
      // Unfortunately, we have no way of checking if a *process* can host
      // untrusted webui contexts. Callers should look at (ideally, the
      // browser-verified) origin.
      [[fallthrough]];
    case mojom::ContextType::kWebPage:
      // Any context not associated with an extension, not running in an
      // extension process, and without webui bindings can be considered a
      // web page process.
      return !extension && !Contains(process_id) &&
             !ProcessHasWebUIBindings(process_id);
    case mojom::ContextType::kWebUi:
      // Don't consider extensions in webui (like content scripts) to be
      // webui.
      return !extension && ProcessHasWebUIBindings(process_id);
=======
  for (auto iter = items_.cbegin(); iter != items_.cend(); ++iter) {
    if (iter->process_id == process_id)
      return true;
>>>>>>> chromium
  }
  return false;
}

std::set<std::string> ProcessMap::GetExtensionsInProcess(int process_id) const {
  std::set<std::string> result;
  for (auto iter = items_.cbegin(); iter != items_.cend(); ++iter) {
    if (iter->process_id == process_id)
      result.insert(iter->extension_id);
  }
  return result;
}

Feature::Context ProcessMap::GetMostLikelyContextType(
    const Extension* extension,
    int process_id,
    const GURL* url) const {
  // WARNING: This logic must match ScriptContextSet::ClassifyJavaScriptContext,
  // as much as possible.

  // TODO(crbug.com/1055168): Move this into the !extension if statement below
  // or document why we want to return WEBUI_CONTEXT for content scripts in
  // WebUIs.
  // TODO(crbug.com/1055656): HasWebUIBindings does not always return true for
  // WebUIs. This should be changed to use something else.
  if (content::ChildProcessSecurityPolicy::GetInstance()->HasWebUIBindings(
          process_id)) {
    return Feature::WEBUI_CONTEXT;
  }

  if (!extension) {
    // Note that blob/filesystem schemes associated with an inner URL of
    // chrome-untrusted will be considered regular pages.
    if (url && url->SchemeIs(content::kChromeUIUntrustedScheme))
      return Feature::WEBUI_UNTRUSTED_CONTEXT;

    return Feature::WEB_PAGE_CONTEXT;
  }

  if (!Contains(extension->id(), process_id)) {
    // This could equally be UNBLESSED_EXTENSION_CONTEXT, but we don't record
    // which processes have extension frames in them.
    // TODO(kalman): Investigate this.
    return Feature::CONTENT_SCRIPT_CONTEXT;
  }

  if (extension->is_hosted_app() &&
      extension->location() != mojom::ManifestLocation::kComponent) {
    return Feature::BLESSED_WEB_PAGE_CONTEXT;
  }

<<<<<<< HEAD
  // TODO(crbug.com/40849649): Currently, offscreen document contexts
  // are misclassified as kPrivilegedExtension contexts. This is not ideal
  // because there is a mismatch between the browser and the renderer), but it's
  // not a security issue because, while offscreen documents have fewer
  // capabilities, this is an API distinction, and not a security enforcement.
  // Offscreen documents run in the same process as the rest of the extension
  // and can message the extension, so could easily - though indirectly -
  // access all the same features.
  // Even so, we should fix this to properly classify offscreen documents (and
  // this would be a problem if offscreen documents ever have access to APIs
  // that kPrivilegedExtension contexts don't).

  return mojom::ContextType::kPrivilegedExtension;
=======
  return is_lock_screen_context_ ? Feature::LOCK_SCREEN_EXTENSION_CONTEXT
                                 : Feature::BLESSED_EXTENSION_CONTEXT;
>>>>>>> chromium
}

}  // namespace extensions
