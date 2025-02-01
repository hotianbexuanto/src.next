// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/browser/test_event_router_observer.h"

namespace extensions {

TestEventRouterObserver::TestEventRouterObserver(EventRouter* event_router) {
  observation_.Observe(event_router);
}

TestEventRouterObserver::~TestEventRouterObserver() = default;

void TestEventRouterObserver::ClearEvents() {
  events_.clear();
  dispatched_events_.clear();
}

void TestEventRouterObserver::OnWillDispatchEvent(const Event& event) {
  DCHECK(!event.event_name.empty());
  events_[event.event_name] = event.DeepCopy();
}

void TestEventRouterObserver::OnDidDispatchEventToProcess(const Event& event) {
  DCHECK(!event.event_name.empty());
  dispatched_events_[event.event_name] = event.DeepCopy();
}

}  // namespace extensions
