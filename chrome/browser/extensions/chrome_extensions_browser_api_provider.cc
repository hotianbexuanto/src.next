// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/extensions/chrome_extensions_browser_api_provider.h"

#include "chrome/browser/extensions/api/generated_api_registration.h"
#include "chrome/browser/extensions/api/preference/preference_api.h"
#include "extensions/browser/extension_function_registry.h"
#include "extensions/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "chrome/browser/extensions/api/commands/commands.h"
#endif

namespace extensions {

ChromeExtensionsBrowserAPIProvider::ChromeExtensionsBrowserAPIProvider() =
    default;
ChromeExtensionsBrowserAPIProvider::~ChromeExtensionsBrowserAPIProvider() =
    default;

void ChromeExtensionsBrowserAPIProvider::RegisterExtensionFunctions(
    ExtensionFunctionRegistry* registry) {
<<<<<<< HEAD
#if BUILDFLAG(ENABLE_EXTENSIONS)
  // Commands
  registry->RegisterFunction<GetAllCommandsFunction>();
#endif
=======
  // Preferences.
  registry->RegisterFunction<GetPreferenceFunction>();
  registry->RegisterFunction<SetPreferenceFunction>();
  registry->RegisterFunction<ClearPreferenceFunction>();
>>>>>>> chromium

  // Generated APIs from Chrome.
  api::ChromeGeneratedFunctionRegistry::RegisterAll(registry);
}

}  // namespace extensions
