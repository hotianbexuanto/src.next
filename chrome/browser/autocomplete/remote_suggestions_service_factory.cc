// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/autocomplete/remote_suggestions_service_factory.h"

<<<<<<< HEAD
#include "base/no_destructor.h"
#include "chrome/browser/autocomplete/document_suggestions_service_factory.h"
#include "chrome/browser/autocomplete/enterprise_search_aggregator_suggestions_service_factory.h"
=======
#include "base/memory/singleton.h"
>>>>>>> chromium
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/omnibox/browser/remote_suggestions_service.h"
#include "content/public/browser/storage_partition.h"

// static
RemoteSuggestionsService* RemoteSuggestionsServiceFactory::GetForProfile(
    Profile* profile,
    bool create_if_necessary) {
  return static_cast<RemoteSuggestionsService*>(
      GetInstance()->GetServiceForBrowserContext(profile, create_if_necessary));
}

// static
RemoteSuggestionsServiceFactory*
RemoteSuggestionsServiceFactory::GetInstance() {
  return base::Singleton<RemoteSuggestionsServiceFactory>::get();
}

KeyedService* RemoteSuggestionsServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  Profile* profile = Profile::FromBrowserContext(context);
<<<<<<< HEAD
  return std::make_unique<RemoteSuggestionsService>(
      DocumentSuggestionsServiceFactory::GetForProfile(
          profile, /*create_if_necessary=*/true),
      EnterpriseSearchAggregatorSuggestionsServiceFactory::GetForProfile(
          profile, /*create_if_necessary=*/true),
=======
  return new RemoteSuggestionsService(
>>>>>>> chromium
      profile->GetDefaultStoragePartition()
          ->GetURLLoaderFactoryForBrowserProcess());
}

RemoteSuggestionsServiceFactory::RemoteSuggestionsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "RemoteSuggestionsService",
<<<<<<< HEAD
          ProfileSelections::Builder()
              // Service is needed in OTR profiles (Incognito and Guest).
              .WithRegular(ProfileSelection::kOwnInstance)
              .WithGuest(ProfileSelection::kOwnInstance)
              // TODO(crbug.com/41488885): Check if this service is needed for
              // Ash Internals.
              .WithAshInternals(ProfileSelection::kOriginalOnly)
              .Build()) {
  DependsOn(DocumentSuggestionsServiceFactory::GetInstance());
  DependsOn(EnterpriseSearchAggregatorSuggestionsServiceFactory::GetInstance());
=======
          BrowserContextDependencyManager::GetInstance()) {
>>>>>>> chromium
}

RemoteSuggestionsServiceFactory::~RemoteSuggestionsServiceFactory() {}
