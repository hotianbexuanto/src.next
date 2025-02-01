// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/browser/event_router.h"

#include <stddef.h>

#include <algorithm>
<<<<<<< HEAD
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

#include "base/atomic_sequence_num.h"
#include "base/check_is_test.h"
#include "base/containers/contains.h"
#include "base/debug/crash_logging.h"
#include "base/functional/bind.h"
#include "base/metrics/histogram_functions.h"
#include "base/metrics/histogram_macros.h"
#include "base/notreached.h"
#include "base/observer_list.h"
#include "base/strings/string_util.h"
=======
#include <utility>

#include "base/atomic_sequence_num.h"
#include "base/bind.h"
#include "base/metrics/histogram_functions.h"
#include "base/metrics/histogram_macros.h"
#include "base/ranges/algorithm.h"
#include "base/task/post_task.h"
#include "base/values.h"
>>>>>>> chromium
#include "components/crx_file/id_util.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/service_worker_context.h"
#include "content/public/browser/storage_partition.h"
#include "extensions/browser/api_activity_monitor.h"
#include "extensions/browser/event_router_factory.h"
#include "extensions/browser/events/lazy_event_dispatcher.h"
#include "extensions/browser/extension_host.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/browser/extension_system.h"
#include "extensions/browser/extensions_browser_client.h"
#include "extensions/browser/process_manager.h"
#include "extensions/browser/process_map.h"
#include "extensions/common/constants.h"
#include "extensions/common/extension.h"
#include "extensions/common/extension_api.h"
#include "extensions/common/extension_messages.h"
#include "extensions/common/extension_urls.h"
#include "extensions/common/features/feature.h"
#include "extensions/common/features/feature_provider.h"
#include "extensions/common/manifest_handlers/background_info.h"
#include "extensions/common/manifest_handlers/incognito_info.h"
#include "extensions/common/permissions/permissions_data.h"

using base::DictionaryValue;
using base::ListValue;
using content::BrowserContext;
using content::BrowserThread;
using content::RenderProcessHost;

namespace extensions {

namespace {

// A dictionary of event names to lists of filters that this extension has
// registered from its lazy background page.
const char kFilteredEvents[] = "filtered_events";

// Similar to |kFilteredEvents|, but applies to extension service worker events.
const char kFilteredServiceWorkerEvents[] = "filtered_service_worker_events";

// A message when mojom::EventRouter::AddListenerForMainThread() is called with
// an invalid param.
constexpr char kAddEventListenerWithInvalidParam[] =
    "Tried to add an event listener without a valid extension ID nor listener "
    "URL";

// A message when mojom::EventRouter::AddListenerForServiceWorker() is called
// with an invalid worker scope URL.
constexpr char kAddEventListenerWithInvalidWorkerScopeURL[] =
    "Tried to add an event listener for a service worker without a valid "
    "worker scope URL.";

// A message when mojom::EventRouter::AddListenerForServiceWorker() is called
// with an invalid extension ID.
constexpr char kAddEventListenerWithInvalidExtensionID[] =
    "Tried to add an event listener for a service worker without a valid "
    "extension ID.";

// A message when mojom::EventRouter::RemoveListenerForMainThread() is called
// with an invalid param.
constexpr char kRemoveEventListenerWithInvalidParam[] =
    "Tried to remove an event listener without a valid extension ID nor "
    "listener URL";

// A message when mojom::EventRouter::RemoveListenerForServiceWorker() is called
// with an invalid worker scope URL.
constexpr char kRemoveEventListenerWithInvalidWorkerScopeURL[] =
    "Tried to remove an event listener for a service worker without a valid "
    "worker scope URL.";

// A message when mojom::EventRouter::RemoveListenerForServiceWorker() is called
// with an invalid extension ID.
constexpr char kRemoveEventListenerWithInvalidExtensionID[] =
    "Tried to remove an event listener for a service worker without a valid "
    "extension ID.";

// Sends a notification about an event to the API activity monitor and the
// ExtensionHost for |extension_id| on the UI thread. Can be called from any
// thread.
void NotifyEventDispatched(content::BrowserContext* browser_context,
                           const std::string& extension_id,
                           const std::string& event_name,
                           const base::ListValue& args) {
  // Notify the ApiActivityMonitor about the event dispatch.
  activity_monitor::OnApiEventDispatched(browser_context, extension_id,
                                         event_name, args);
}

LazyContextId LazyContextIdForBrowserContext(BrowserContext* browser_context,
                                             const EventListener* listener) {
  if (listener->is_for_service_worker())
    return LazyContextId(browser_context, listener->extension_id(),
                         listener->listener_url());
  return LazyContextId(browser_context, listener->extension_id());
}

LazyContextId LazyContextIdForListener(const EventListener* listener) {
  return LazyContextIdForBrowserContext(
      listener->process()->GetBrowserContext(), listener);
}

// A global identifier used to distinguish extension events.
base::AtomicSequenceNumber g_extension_event_id;

<<<<<<< HEAD
// Returns whether an event would cross the incognito boundary. e.g.
// incognito->regular or regular->incognito. This is allowed for some extensions
// that enable spanning-mode but is always disallowed for webUI.
// |context| refers to the BrowserContext of the receiver of the event.
bool CrossesIncognito(BrowserContext* context, const Event& event) {
  return event.restrict_to_browser_context &&
         context != event.restrict_to_browser_context;
}

base::debug::CrashKeyString* GetEventNameCrashKey() {
  static auto* crash_key = base::debug::AllocateCrashKeyString(
      "ext_event_name", base::debug::CrashKeySize::Size256);
  return crash_key;
}

=======
>>>>>>> chromium
}  // namespace

namespace debug {

// Helper for adding a crash keys for dispatching an extension event over mojom.
//
// It is created each time an event is sent from the browser to the renderer
// process via the EventDispatcher::DispatchEvent interface.
//
// All keys are logged every time this class is instantiated.
class ScopedOOMCrashKey {
 public:
  explicit ScopedOOMCrashKey(const std::string& event_name)
      : event_name_crash_key_(GetEventNameCrashKey(), event_name) {}
  ~ScopedOOMCrashKey() = default;

 private:
  // Extension API event name.
  base::debug::ScopedCrashKeyString event_name_crash_key_;
};

}  // namespace debug

const char EventRouter::kRegisteredLazyEvents[] = "events";
const char EventRouter::kRegisteredServiceWorkerEvents[] =
    "serviceworkerevents";

// static
void EventRouter::DispatchExtensionMessage(
    IPC::Sender* ipc_sender,
    int worker_thread_id,
    content::BrowserContext* browser_context,
    const std::string& extension_id,
    int event_id,
    const std::string& event_name,
    ListValue* event_args,
    UserGestureState user_gesture,
    const EventFilteringInfo& info) {
  NotifyEventDispatched(browser_context, extension_id, event_name, *event_args);
  mojom::DispatchEventParams params;
  params.worker_thread_id = worker_thread_id;
  params.extension_id = extension_id;
  params.event_name = event_name;
  params.event_id = event_id;
  params.is_user_gesture = user_gesture == USER_GESTURE_ENABLED;
  params.filtering_info = info;

<<<<<<< HEAD
void EventRouter::RouteDispatchEvent(
    content::RenderProcessHost* rph,
    mojom::DispatchEventParamsPtr params,
    base::Value::List event_args,
    mojom::EventDispatcher::DispatchEventCallback callback) {
  CHECK(base::Contains(observed_process_set_, rph));
  int worker_thread_id = params->worker_thread_id;
  mojo::AssociatedRemote<mojom::EventDispatcher>& dispatcher =
      rph_dispatcher_map_[rph][worker_thread_id];

  if (!dispatcher.is_bound()) {
    if (worker_thread_id == kMainThreadId) {
      IPC::ChannelProxy* channel = rph->GetChannel();
      if (!channel) {
        return;
      }
      channel->GetRemoteAssociatedInterface(
          dispatcher.BindNewEndpointAndPassReceiver());
    } else {
      // EventDispatcher for worker threads should be bound at
      // `BindServiceWorkerEventDispatcher`.
      return;
    }
  }

  // The RenderProcessHost might be dead, but if the RenderProcessHost
  // is alive then the dispatcher must be connected.
  CHECK(!rph->IsInitializedAndNotDead() || dispatcher.is_connected());
  debug::ScopedOOMCrashKey oom_crash_key(params->event_name);
  dispatcher->DispatchEvent(std::move(params), std::move(event_args),
                            std::move(callback));
=======
  ipc_sender->Send(new ExtensionMsg_DispatchEvent(params, *event_args));
>>>>>>> chromium
}

// static
EventRouter* EventRouter::Get(content::BrowserContext* browser_context) {
  return EventRouterFactory::GetForBrowserContext(browser_context);
}

// static
std::string EventRouter::GetBaseEventName(const std::string& full_event_name) {
  size_t slash_sep = full_event_name.find('/');
  return full_event_name.substr(0, slash_sep);
}

// static
void EventRouter::DispatchEventToSender(
    IPC::Sender* ipc_sender,
    content::BrowserContext* browser_context,
    const std::string& extension_id,
    events::HistogramValue histogram_value,
    const std::string& event_name,
    int render_process_id,
    int worker_thread_id,
    int64_t service_worker_version_id,
    std::unique_ptr<ListValue> event_args,
    const EventFilteringInfo& info) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  int event_id = g_extension_event_id.GetNext();

  DoDispatchEventToSenderBookkeeping(
      browser_context, extension_id, event_id, render_process_id,
      service_worker_version_id, histogram_value, event_name);

<<<<<<< HEAD
  if (!extension) {
    for (TestObserver& observer : test_observers_) {
      observer.OnNonExtensionEventDispatched(event_name);
    }

    ObserveProcess(rph);
    DispatchExtensionMessage(rph, worker_thread_id, browser_context, host_id,
                             event_id, event_name, std::move(event_args),
                             UserGestureState::USER_GESTURE_UNKNOWN,
                             std::move(info), base::DoNothing());
    // In this case, we won't log the metric for dispatch_start_time. But this
    // means we aren't dispatching an event to an extension so the metric
    // wouldn't be relevant anyways (e.g. would go to a web page or webUI).
    return;
  }

  IncrementInFlightEvents(
      browser_context, rph, extension, event_id, event_name,
      // Currently `dispatch_start_time`, `lazy_background_active_on_dispatch`,
      // and `histogram_value` args are not used for metrics recording since we
      // do not include events from EventDispatchSource::kDispatchEventToSender.
      /*dispatch_start_time=*/base::TimeTicks::Now(), service_worker_version_id,
      EventDispatchSource::kDispatchEventToSender,
      // Background script is active/started at this point.
      /*lazy_background_active_on_dispatch=*/true,
      events::HistogramValue::UNKNOWN);
  ReportEvent(histogram_value, extension,
              /*did_enqueue=*/false);
  mojom::EventDispatcher::DispatchEventCallback callback;
  if (worker_thread_id != kMainThreadId) {
    callback = base::BindOnce(
        &EventRouter::DecrementInFlightEventsForServiceWorker,
        weak_factory_.GetWeakPtr(),
        WorkerId{GenerateExtensionIdFromHostId(host_id), rph->GetDeprecatedID(),
                 service_worker_version_id, worker_thread_id},
        event_id);
  } else if (BackgroundInfo::HasBackgroundPage(extension)) {
    // TODO(crbug.com/40909770): When creating dispatch time metrics for the
    // DispatchEventToSender event flow, ensure this also handles persistent
    // background pages.
    // Although it's unnecessary to decrement in-flight events for non-lazy
    // background pages, we use the logic for event tracking/metrics purposes.
    callback =
        base::BindOnce(&EventRouter::DecrementInFlightEventsForRenderFrameHost,
                       weak_factory_.GetWeakPtr(), rph->GetDeprecatedID(),
                       host_id.id, event_id);
  } else {
    callback = base::DoNothing();
  }
  ObserveProcess(rph);
  DispatchExtensionMessage(rph, worker_thread_id, browser_context, host_id,
                           event_id, event_name, std::move(event_args),
                           UserGestureState::USER_GESTURE_UNKNOWN,
                           std::move(info), std::move(callback));
=======
  DispatchExtensionMessage(ipc_sender, worker_thread_id, browser_context,
                           extension_id, event_id, event_name, event_args.get(),
                           UserGestureState::USER_GESTURE_UNKNOWN, info);
>>>>>>> chromium
}

// static.
bool EventRouter::CanDispatchEventToBrowserContext(BrowserContext* context,
                                                   const Extension* extension,
                                                   const Event& event) {
  // Is this event from a different browser context than the renderer (ie, an
  // incognito tab event sent to a normal process, or vice versa).
  bool crosses_incognito = event.restrict_to_browser_context &&
                           context != event.restrict_to_browser_context;
  if (!crosses_incognito)
    return true;
  return ExtensionsBrowserClient::Get()->CanExtensionCrossIncognito(extension,
                                                                    context);
}

// static
void EventRouter::BindForRenderer(
    int render_process_id,
    mojo::PendingAssociatedReceiver<mojom::EventRouter> receiver) {
  auto* host = RenderProcessHost::FromID(render_process_id);
  if (!host)
    return;

  EventRouter* event_router = EventRouter::Get(host->GetBrowserContext());
  event_router->receivers_.Add(event_router, std::move(receiver),
                               render_process_id);
}

void EventRouter::SwapReceiverForTesting(int render_process_id,
                                         mojom::EventRouter* new_impl) {
  CHECK_IS_TEST();
  std::map<mojo::ReceiverId, int*> receiver_contexts =
      receivers_.GetAllContexts();

  // We don't have the ReceiverId for the receiver stored anywhere, so loop
  // through existing receivers to find the ReceiverId and use it to find the
  // correct receiver to swap for testing.
  for (auto& [receiver_id, render_process_id_ptr] :
       receivers_.GetAllContexts()) {
    if (render_process_id_ptr && *render_process_id_ptr == render_process_id) {
      std::ignore =
          receivers_.SwapImplForTesting(receiver_id, new_impl);  // IN-TEST
      return;
    }
  }

  // There was no receiver to swap, maybe it was destroyed before this method
  // was called?
  NOTREACHED();
}

EventRouter::EventRouter(BrowserContext* browser_context,
                         ExtensionPrefs* extension_prefs)
    : browser_context_(browser_context),
      extension_prefs_(extension_prefs),
      lazy_event_dispatch_util_(browser_context_) {
  extension_registry_observation_.Observe(
      ExtensionRegistry::Get(browser_context_));
  process_manager_observation_.Observe(ProcessManager::Get(browser_context_));
}

EventRouter::~EventRouter() {
  for (auto* process : observed_process_set_)
    process->RemoveObserver(this);
}

void EventRouter::AddListenerForMainThread(mojom::EventListenerParamPtr param,
                                           const std::string& event_name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  if (param->is_extension_id() &&
      crx_file::id_util::IdIsValid(param->get_extension_id())) {
    AddEventListener(event_name, process, param->get_extension_id());
  } else if (param->is_listener_url() && param->get_listener_url().is_valid()) {
    AddEventListenerForURL(event_name, process, param->get_listener_url());
  } else {
    mojo::ReportBadMessage(kAddEventListenerWithInvalidParam);
  }
}

void EventRouter::AddListenerForServiceWorker(const std::string& extension_id,
                                              const GURL& worker_scope_url,
                                              const std::string& event_name,
                                              int64_t service_worker_version_id,
                                              int32_t worker_thread_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  if (crx_file::id_util::IdIsValid(extension_id)) {
    if (!worker_scope_url.is_valid()) {
      mojo::ReportBadMessage(kAddEventListenerWithInvalidWorkerScopeURL);
      return;
    }
    AddServiceWorkerEventListener(event_name, process, extension_id,
                                  worker_scope_url, service_worker_version_id,
                                  worker_thread_id);
  } else {
    mojo::ReportBadMessage(kAddEventListenerWithInvalidExtensionID);
  }
}

void EventRouter::AddLazyListenerForMainThread(const std::string& extension_id,
                                               const std::string& event_name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  AddLazyEventListener(event_name, extension_id);
}

void EventRouter::AddLazyListenerForServiceWorker(
    const std::string& extension_id,
    const GURL& worker_scope_url,
    const std::string& event_name) {
  std::unique_ptr<EventListener> listener =
      EventListener::ForExtensionServiceWorker(
          event_name, extension_id, nullptr, worker_scope_url,
          // Lazy listener, without worker version id and thread id.
          blink::mojom::kInvalidServiceWorkerVersionId, kMainThreadId, nullptr);
  AddLazyEventListenerImpl(std::move(listener),
                           RegisteredEventType::kServiceWorker);
}

void EventRouter::AddFilteredListenerForMainThread(
    const std::string& extension_id,
    const std::string& event_name,
    base::Value filter,
    bool add_lazy_listener) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  AddFilteredEventListener(event_name, process, extension_id, absl::nullopt,
                           base::Value::AsDictionaryValue(filter),
                           add_lazy_listener);
}

void EventRouter::AddFilteredListenerForServiceWorker(
    const std::string& extension_id,
    const GURL& worker_scope_url,
    const std::string& event_name,
    int64_t service_worker_version_id,
    int32_t worker_thread_id,
    base::Value filter,
    bool add_lazy_listener) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  ServiceWorkerIdentifier sw_identifier;
  sw_identifier.scope = worker_scope_url;
  sw_identifier.thread_id = worker_thread_id;
  sw_identifier.version_id = service_worker_version_id;

  AddFilteredEventListener(event_name, process, extension_id, sw_identifier,
                           base::Value::AsDictionaryValue(filter),
                           add_lazy_listener);
}

void EventRouter::RemoveListenerForMainThread(
    mojom::EventListenerParamPtr param,
    const std::string& event_name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  if (param->is_extension_id() &&
      crx_file::id_util::IdIsValid(param->get_extension_id())) {
    RemoveEventListener(event_name, process, param->get_extension_id());
  } else if (param->is_listener_url() && param->get_listener_url().is_valid()) {
    RemoveEventListenerForURL(event_name, process, param->get_listener_url());
  } else {
    mojo::ReportBadMessage(kRemoveEventListenerWithInvalidParam);
  }
}

void EventRouter::RemoveListenerForServiceWorker(
    const std::string& extension_id,
    const GURL& worker_scope_url,
    const std::string& event_name,
    int64_t service_worker_version_id,
    int worker_thread_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  if (crx_file::id_util::IdIsValid(extension_id)) {
    if (!worker_scope_url.is_valid()) {
      mojo::ReportBadMessage(kRemoveEventListenerWithInvalidWorkerScopeURL);
      return;
    }
    RemoveServiceWorkerEventListener(
        event_name, process, extension_id, worker_scope_url,
        service_worker_version_id, worker_thread_id);
  } else {
    mojo::ReportBadMessage(kRemoveEventListenerWithInvalidExtensionID);
  }
}

void EventRouter::RemoveLazyListenerForMainThread(
    const std::string& extension_id,
    const std::string& event_name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  RemoveLazyEventListener(event_name, extension_id);
}

void EventRouter::RemoveLazyListenerForServiceWorker(
    const std::string& extension_id,
    const GURL& worker_scope_url,
    const std::string& event_name) {
  std::unique_ptr<EventListener> listener =
      EventListener::ForExtensionServiceWorker(
          event_name, extension_id, nullptr, worker_scope_url,
          // Lazy listener, without worker version id and thread id.
          blink::mojom::kInvalidServiceWorkerVersionId, kMainThreadId, nullptr);
  RemoveLazyEventListenerImpl(std::move(listener),
                              RegisteredEventType::kServiceWorker);
}

void EventRouter::RemoveFilteredListenerForMainThread(
    const std::string& extension_id,
    const std::string& event_name,
    base::Value filter,
    bool remove_lazy_listener) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  RemoveFilteredEventListener(event_name, process, extension_id, absl::nullopt,
                              base::Value::AsDictionaryValue(filter),
                              remove_lazy_listener);
}

void EventRouter::RemoveFilteredListenerForServiceWorker(
    const std::string& extension_id,
    const GURL& worker_scope_url,
    const std::string& event_name,
    int64_t service_worker_version_id,
    int32_t worker_thread_id,
    base::Value filter,
    bool remove_lazy_listener) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(receivers_.current_context());
  if (!process)
    return;

  ServiceWorkerIdentifier sw_identifier;
  sw_identifier.scope = worker_scope_url;
  sw_identifier.thread_id = worker_thread_id;
  sw_identifier.version_id = service_worker_version_id;

  RemoveFilteredEventListener(event_name, process, extension_id, sw_identifier,
                              base::Value::AsDictionaryValue(filter),
                              remove_lazy_listener);
}

void EventRouter::AddEventListener(const std::string& event_name,
                                   RenderProcessHost* process,
                                   const std::string& extension_id) {
  listeners_.AddListener(
      EventListener::ForExtension(event_name, extension_id, process, nullptr));
}

void EventRouter::AddServiceWorkerEventListener(
    const std::string& event_name,
    RenderProcessHost* process,
    const ExtensionId& extension_id,
    const GURL& service_worker_scope,
    int64_t service_worker_version_id,
    int worker_thread_id) {
  listeners_.AddListener(EventListener::ForExtensionServiceWorker(
      event_name, extension_id, process, service_worker_scope,
      service_worker_version_id, worker_thread_id, nullptr));
}

void EventRouter::RemoveEventListener(const std::string& event_name,
                                      RenderProcessHost* process,
                                      const std::string& extension_id) {
  std::unique_ptr<EventListener> listener =
      EventListener::ForExtension(event_name, extension_id, process, nullptr);
  listeners_.RemoveListener(listener.get());
}

void EventRouter::RemoveServiceWorkerEventListener(
    const std::string& event_name,
    RenderProcessHost* process,
    const ExtensionId& extension_id,
    const GURL& service_worker_scope,
    int64_t service_worker_version_id,
    int worker_thread_id) {
  std::unique_ptr<EventListener> listener =
      EventListener::ForExtensionServiceWorker(
          event_name, extension_id, process, service_worker_scope,
          service_worker_version_id, worker_thread_id, nullptr);
  listeners_.RemoveListener(listener.get());
}

void EventRouter::AddEventListenerForURL(const std::string& event_name,
                                         RenderProcessHost* process,
                                         const GURL& listener_url) {
  listeners_.AddListener(
      EventListener::ForURL(event_name, listener_url, process, nullptr));
}

void EventRouter::RemoveEventListenerForURL(const std::string& event_name,
                                            RenderProcessHost* process,
                                            const GURL& listener_url) {
  std::unique_ptr<EventListener> listener =
      EventListener::ForURL(event_name, listener_url, process, nullptr);
  listeners_.RemoveListener(listener.get());
}

void EventRouter::RegisterObserver(Observer* observer,
                                   const std::string& event_name) {
  // Observing sub-event names like "foo.onBar/123" is not allowed.
  DCHECK(event_name.find('/') == std::string::npos);
  auto& observers = observer_map_[event_name];
  if (!observers) {
    observers = std::make_unique<Observers>();
  }

  observers->AddObserver(observer);
}

void EventRouter::UnregisterObserver(Observer* observer) {
  for (auto& it : observer_map_) {
    it.second->RemoveObserver(observer);
  }
}

void EventRouter::AddObserverForTesting(TestObserver* observer) {
  test_observers_.AddObserver(observer);
}

void EventRouter::RemoveObserverForTesting(TestObserver* observer) {
  test_observers_.RemoveObserver(observer);
}

void EventRouter::OnListenerAdded(const EventListener* listener) {
  const EventListenerInfo details(
      listener->event_name(), listener->extension_id(),
      listener->listener_url(), listener->GetBrowserContext(),
      listener->worker_thread_id(), listener->service_worker_version_id());
  std::string base_event_name = GetBaseEventName(listener->event_name());
  auto it = observer_map_.find(base_event_name);
  if (it != observer_map_.end()) {
    for (auto& observer : *it->second) {
      observer.OnListenerAdded(details);
    }
  }

  RenderProcessHost* process = listener->process();
  if (process) {
    bool inserted = observed_process_set_.insert(process).second;
    if (inserted)
      process->AddObserver(this);
  }
}

void EventRouter::OnListenerRemoved(const EventListener* listener) {
  const EventListenerInfo details(
      listener->event_name(), listener->extension_id(),
      listener->listener_url(), listener->GetBrowserContext(),
      listener->worker_thread_id(), listener->service_worker_version_id());
  std::string base_event_name = GetBaseEventName(listener->event_name());
  auto it = observer_map_.find(base_event_name);
  if (it != observer_map_.end()) {
    for (auto& observer : *it->second) {
      observer.OnListenerRemoved(details);
    }
  }
}

void EventRouter::RenderProcessExited(
    RenderProcessHost* host,
    const content::ChildProcessTerminationInfo& info) {
  listeners_.RemoveListenersForProcess(host);
<<<<<<< HEAD
  event_ack_data_.ClearUnackedEventsForRenderProcess(host->GetDeprecatedID());
=======
>>>>>>> chromium
  observed_process_set_.erase(host);
  host->RemoveObserver(this);
}

void EventRouter::RenderProcessHostDestroyed(RenderProcessHost* host) {
  listeners_.RemoveListenersForProcess(host);
<<<<<<< HEAD
  event_ack_data_.ClearUnackedEventsForRenderProcess(host->GetDeprecatedID());
=======
>>>>>>> chromium
  observed_process_set_.erase(host);
  host->RemoveObserver(this);
}

void EventRouter::AddLazyEventListener(const std::string& event_name,
                                       const ExtensionId& extension_id) {
  AddLazyEventListenerImpl(
      EventListener::ForExtension(event_name, extension_id, nullptr, nullptr),
      RegisteredEventType::kLazy);
}

void EventRouter::RemoveLazyEventListener(const std::string& event_name,
                                          const ExtensionId& extension_id) {
  RemoveLazyEventListenerImpl(
      EventListener::ForExtension(event_name, extension_id, nullptr, nullptr),
      RegisteredEventType::kLazy);
}

void EventRouter::AddFilteredEventListener(
    const std::string& event_name,
    RenderProcessHost* process,
    const std::string& extension_id,
    absl::optional<ServiceWorkerIdentifier> sw_identifier,
    const base::DictionaryValue& filter,
    bool add_lazy_listener) {
  const bool is_for_service_worker = sw_identifier.has_value();
  listeners_.AddListener(
      is_for_service_worker
          ? EventListener::ForExtensionServiceWorker(
                event_name, extension_id, process, sw_identifier->scope,
                sw_identifier->version_id, sw_identifier->thread_id,
                filter.CreateDeepCopy())
          : EventListener::ForExtension(event_name, extension_id, process,
                                        filter.CreateDeepCopy()));

  if (!add_lazy_listener)
    return;

  bool added = listeners_.AddListener(
      is_for_service_worker
          ? EventListener::ForExtensionServiceWorker(
                event_name, extension_id, nullptr, sw_identifier->scope,
                // Lazy listener, without worker version id and thread id.
                blink::mojom::kInvalidServiceWorkerVersionId, kMainThreadId,
                filter.CreateDeepCopy())
          : EventListener::ForExtension(event_name, extension_id,
                                        nullptr,  // Lazy, without process.
                                        filter.CreateDeepCopy()));
  if (added)
    AddFilterToEvent(event_name, extension_id, is_for_service_worker, &filter);
}

void EventRouter::RemoveFilteredEventListener(
    const std::string& event_name,
    RenderProcessHost* process,
    const std::string& extension_id,
    absl::optional<ServiceWorkerIdentifier> sw_identifier,
    const base::DictionaryValue& filter,
    bool remove_lazy_listener) {
  const bool is_for_service_worker = sw_identifier.has_value();
  std::unique_ptr<EventListener> listener =
      is_for_service_worker
          ? EventListener::ForExtensionServiceWorker(
                event_name, extension_id, process, sw_identifier->scope,
                sw_identifier->version_id, sw_identifier->thread_id,
                filter.CreateDeepCopy())
          : EventListener::ForExtension(event_name, extension_id, process,
                                        filter.CreateDeepCopy());

  listeners_.RemoveListener(listener.get());

  if (remove_lazy_listener) {
    listener->MakeLazy();
    bool removed = listeners_.RemoveListener(listener.get());

    if (removed) {
      RemoveFilterFromEvent(event_name, extension_id, is_for_service_worker,
                            &filter);
    }
  }
}

bool EventRouter::HasEventListener(const std::string& event_name) const {
  return listeners_.HasListenerForEvent(event_name);
}

bool EventRouter::ExtensionHasEventListener(
    const std::string& extension_id,
    const std::string& event_name) const {
  return listeners_.HasListenerForExtension(extension_id, event_name);
}

std::set<std::string> EventRouter::GetRegisteredEvents(
    const std::string& extension_id,
    RegisteredEventType type) const {
  std::set<std::string> events;
  const ListValue* events_value = NULL;

  const char* pref_key = type == RegisteredEventType::kLazy
                             ? kRegisteredLazyEvents
                             : kRegisteredServiceWorkerEvents;
  if (!extension_prefs_ || !extension_prefs_->ReadPrefAsList(
                               extension_id, pref_key, &events_value)) {
    return events;
  }

  for (size_t i = 0; i < events_value->GetSize(); ++i) {
    std::string event;
    if (events_value->GetString(i, &event))
      events.insert(event);
  }
  return events;
}

void EventRouter::ClearRegisteredEventsForTest(
    const ExtensionId& extension_id) {
  SetRegisteredEvents(extension_id, std::set<std::string>(),
                      RegisteredEventType::kLazy);
  SetRegisteredEvents(extension_id, std::set<std::string>(),
                      RegisteredEventType::kServiceWorker);
}

bool EventRouter::HasLazyEventListenerForTesting(
    const std::string& event_name) {
  const EventListenerMap::ListenerList& listeners =
      listeners_.GetEventListenersByName(event_name);
<<<<<<< HEAD
  return std::ranges::any_of(
      listeners, [](const std::unique_ptr<EventListener>& listener) {
        return listener->IsLazy();
      });
=======
  return std::any_of(listeners.begin(), listeners.end(),
                     [](const std::unique_ptr<EventListener>& listener) {
                       return listener->IsLazy();
                     });
>>>>>>> chromium
}

bool EventRouter::HasNonLazyEventListenerForTesting(
    const std::string& event_name) {
  const EventListenerMap::ListenerList& listeners =
      listeners_.GetEventListenersByName(event_name);
<<<<<<< HEAD
  return std::ranges::any_of(
      listeners, [](const std::unique_ptr<EventListener>& listener) {
        return !listener->IsLazy();
      });
=======
  return std::any_of(listeners.begin(), listeners.end(),
                     [](const std::unique_ptr<EventListener>& listener) {
                       return !listener->IsLazy();
                     });
>>>>>>> chromium
}

void EventRouter::RemoveFilterFromEvent(const std::string& event_name,
                                        const std::string& extension_id,
                                        bool is_for_service_worker,
                                        const DictionaryValue* filter) {
  ExtensionPrefs::ScopedDictionaryUpdate update(
      extension_prefs_, extension_id,
      is_for_service_worker ? kFilteredServiceWorkerEvents : kFilteredEvents);
  auto filtered_events = update.Create();
  ListValue* filter_list = NULL;
  if (!filtered_events ||
      !filtered_events->GetListWithoutPathExpansion(event_name, &filter_list)) {
    return;
  }
<<<<<<< HEAD
  const base::Value::Dict& (base::Value::*get_dict)() const =
      &base::Value::GetDict;
  filter_list->erase(std::ranges::find(*filter_list, filter, get_dict));
=======
  filter_list->EraseListIter(
      base::ranges::find(filter_list->GetList(), *filter));
>>>>>>> chromium
}

const DictionaryValue* EventRouter::GetFilteredEvents(
    const std::string& extension_id,
    RegisteredEventType type) {
  const DictionaryValue* events = nullptr;
  const char* pref_key = type == RegisteredEventType::kLazy
                             ? kFilteredEvents
                             : kFilteredServiceWorkerEvents;
  extension_prefs_->ReadPrefAsDictionary(extension_id, pref_key, &events);
  return events;
}

void EventRouter::BroadcastEvent(std::unique_ptr<Event> event) {
  DispatchEventImpl(std::string(), std::move(event));
}

void EventRouter::DispatchEventToExtension(const std::string& extension_id,
                                           std::unique_ptr<Event> event) {
  DCHECK(!extension_id.empty());
  DispatchEventImpl(extension_id, std::move(event));
}

void EventRouter::DispatchEventWithLazyListener(const std::string& extension_id,
                                                std::unique_ptr<Event> event) {
  DCHECK(!extension_id.empty());
  const Extension* extension = ExtensionRegistry::Get(browser_context_)
                                   ->enabled_extensions()
                                   .GetByID(extension_id);
  if (!extension)
    return;
  const bool is_service_worker_based_background =
      BackgroundInfo::IsServiceWorkerBased(extension);

  std::string event_name = event->event_name;
  const bool has_listener = ExtensionHasEventListener(extension_id, event_name);
  if (!has_listener) {
    if (is_service_worker_based_background) {
      AddLazyListenerForServiceWorker(
          extension_id, Extension::GetBaseURLFromExtensionId(extension_id),
          event_name);
    } else {
      AddLazyEventListener(event_name, extension_id);
    }
  }

  DispatchEventToExtension(extension_id, std::move(event));

  if (!has_listener) {
    if (is_service_worker_based_background) {
      RemoveLazyListenerForServiceWorker(
          extension_id, Extension::GetBaseURLFromExtensionId(extension_id),
          event_name);
    } else {
      RemoveLazyEventListener(event_name, extension_id);
    }
  }
}

void EventRouter::DispatchEventImpl(const std::string& restrict_to_extension_id,
                                    std::unique_ptr<Event> event) {
  // We don't expect to get events from a completely different browser context.
  DCHECK(!event->restrict_to_browser_context ||
         ExtensionsBrowserClient::Get()->IsSameContext(
             browser_context_, event->restrict_to_browser_context));

  for (TestObserver& observer : test_observers_)
    observer.OnWillDispatchEvent(*event);

  std::set<const EventListener*> listeners(
      listeners_.GetEventListeners(*event));

  LazyEventDispatcher lazy_event_dispatcher(
      browser_context_, base::BindRepeating(&EventRouter::DispatchPendingEvent,
                                            weak_factory_.GetWeakPtr()));

  // We dispatch events for lazy background pages first because attempting to do
  // so will cause those that are being suspended to cancel that suspension.
  // As canceling a suspension entails sending an event to the affected
  // background page, and as that event needs to be delivered before we dispatch
  // the event we are dispatching here, we dispatch to the lazy listeners here
  // first.
  for (const EventListener* listener : listeners) {
    if (!restrict_to_extension_id.empty() &&
        restrict_to_extension_id != listener->extension_id()) {
      continue;
    }
    if (!listener->IsLazy())
      continue;

    lazy_event_dispatcher.Dispatch(
        *event, LazyContextIdForBrowserContext(browser_context_, listener),
        listener->filter());
  }

  for (const EventListener* listener : listeners) {
    if (!restrict_to_extension_id.empty() &&
        restrict_to_extension_id != listener->extension_id()) {
      continue;
    }
    if (listener->IsLazy())
      continue;
    if (lazy_event_dispatcher.HasAlreadyDispatched(
            LazyContextIdForListener(listener))) {
      continue;
    }

    DispatchEventToProcess(
        listener->extension_id(), listener->listener_url(), listener->process(),
        listener->service_worker_version_id(), listener->worker_thread_id(),
        event.get(), listener->filter(), false /* did_enqueue */);
  }
}

void EventRouter::DispatchEventToProcess(
    const std::string& extension_id,
    const GURL& listener_url,
    RenderProcessHost* process,
    int64_t service_worker_version_id,
    int worker_thread_id,
    Event* event,
    const base::DictionaryValue* listener_filter,
    bool did_enqueue) {
  BrowserContext* listener_context = process->GetBrowserContext();
  ProcessMap* process_map = ProcessMap::Get(listener_context);

  // NOTE: |extension| being NULL does not necessarily imply that this event
  // shouldn't be dispatched. Events can be dispatched to WebUI and webviews as
  // well.  It all depends on what GetMostLikelyContextType returns.
  const Extension* extension =
      ExtensionRegistry::Get(browser_context_)->enabled_extensions().GetByID(
          extension_id);

  if (!extension && !extension_id.empty()) {
    // Trying to dispatch an event to an extension that doesn't exist. The
    // extension could have been removed, but we do not unregister it until the
    // extension process is unloaded.
    return;
  }

  if (extension) {
    // Extension-specific checks.
    // Firstly, if the event is for a URL, the Extension must have permission
    // to access that URL.
    if (!event->event_url.is_empty() &&
        event->event_url.host() != extension->id() &&  // event for self is ok
        !extension->permissions_data()
             ->active_permissions()
             .HasEffectiveAccessToURL(event->event_url)) {
      return;
    }
    // Secondly, if the event is for incognito mode, the Extension must be
    // enabled in incognito mode.
    if (!CanDispatchEventToBrowserContext(listener_context, extension,
                                          *event)) {
      return;
    }
  }

  // TODO(ortuno): |listener_url| is passed in from the renderer so it can't
  // fully be trusted. We should retrieve the URL from the browser process.
  const GURL* url =
      service_worker_version_id == blink::mojom::kInvalidServiceWorkerVersionId
          ? &listener_url
          : nullptr;
<<<<<<< HEAD
  mojom::ContextType target_context = process_map->GetMostLikelyContextType(
      extension, process->GetDeprecatedID(), url);
=======
  Feature::Context target_context =
      process_map->GetMostLikelyContextType(extension, process->GetID(), url);
>>>>>>> chromium

  // We shouldn't be dispatching an event to a webpage, since all such events
  // (e.g.  messaging) don't go through EventRouter.
  DCHECK_NE(Feature::WEB_PAGE_CONTEXT, target_context)
      << "Trying to dispatch event " << event->event_name << " to a webpage,"
      << " but this shouldn't be possible";

  Feature::Availability availability =
      ExtensionAPI::GetSharedInstance()->IsAvailable(
          event->event_name, extension, target_context, listener_url,
          CheckAliasStatus::ALLOWED);
  if (!availability.is_available()) {
    // It shouldn't be possible to reach here, because access is checked on
    // registration. However, for paranoia, check on dispatch as well.
    NOTREACHED() << "Trying to dispatch event " << event->event_name
                 << " which the target does not have access to: "
                 << availability.message();
    return;
  }

  if (!event->will_dispatch_callback.is_null() &&
      !event->will_dispatch_callback.Run(listener_context, target_context,
                                         extension, event, listener_filter)) {
    return;
  }

  int event_id = g_extension_event_id.GetNext();
<<<<<<< HEAD
  mojom::EventDispatcher::DispatchEventCallback callback;
  // This mirrors the IncrementInFlightEvents below.
  if (!extension) {
    callback = base::DoNothing();
  } else if (worker_thread_id != kMainThreadId) {
    callback =
        base::BindOnce(&EventRouter::DecrementInFlightEventsForServiceWorker,
                       weak_factory_.GetWeakPtr(),
                       WorkerId{extension_id, process->GetDeprecatedID(),
                                service_worker_version_id, worker_thread_id},
                       event_id);
  } else if (BackgroundInfo::HasBackgroundPage(extension)) {
    // Although it's unnecessary to decrement in-flight events for non-lazy
    // background pages, we use the logic for event tracking/metrics purposes.
    callback =
        base::BindOnce(&EventRouter::DecrementInFlightEventsForRenderFrameHost,
                       weak_factory_.GetWeakPtr(), process->GetDeprecatedID(),
                       extension_id, event_id);
  } else {
    callback = base::DoNothing();
  }

=======
>>>>>>> chromium
  DispatchExtensionMessage(process, worker_thread_id, listener_context,
                           extension_id, event_id, event->event_name,
                           event->event_args.get(), event->user_gesture,
                           event->filter_info);

<<<<<<< HEAD
  if (!event.did_dispatch_callback.is_null()) {
    event.did_dispatch_callback.Run(
        EventTarget{extension_id, process->GetDeprecatedID(),
                    service_worker_version_id, worker_thread_id});
  }

  for (TestObserver& observer : test_observers_) {
    observer.OnDidDispatchEventToProcess(event, process->GetDeprecatedID());
  }
=======
  for (TestObserver& observer : test_observers_)
    observer.OnDidDispatchEventToProcess(*event);
>>>>>>> chromium

  // TODO(lazyboy): This is wrong for extensions SW events. We need to:
  // 1. Increment worker ref count
  // 2. Add EventAck IPC to decrement that ref count.
  if (extension) {
    ReportEvent(event->histogram_value, extension, did_enqueue);

    IncrementInFlightEvents(listener_context, process, extension, event_id,
                            event->event_name, service_worker_version_id);
  }
}

// static
void EventRouter::DoDispatchEventToSenderBookkeeping(
    content::BrowserContext* browser_context,
    const std::string& extension_id,
    int event_id,
<<<<<<< HEAD
    bool event_will_run_in_lazy_background_page_script) {
  auto* process = RenderProcessHost::FromID(worker_id.render_process_id);
  // Check to make sure the rendered process hasn't gone away by the time
  // we've gotten here. (It's possible it has crashed, etc.) If that's
  // happened, we don't want to track the expected ACK, since we'll never
  // get it.
  if (!process) {
    return;
  }

  if (event_will_run_in_lazy_background_page_script) {
    bad_message::ReceivedBadMessage(
        process, bad_message::ER_SW_INVALID_LAZY_BACKGROUND_PARAM);
  }

  const bool worker_stopped = !ProcessManager::Get(process->GetBrowserContext())
                                   ->HasServiceWorker(worker_id);
  content::ServiceWorkerContext* service_worker_context =
      process->GetStoragePartition()->GetServiceWorkerContext();
  event_ack_data_.DecrementInflightEvent(
      service_worker_context, process->GetDeprecatedID(), worker_id.version_id,
      event_id, worker_stopped,
      base::BindOnce(
          [](RenderProcessHost* process) {
            bad_message::ReceivedBadMessage(process,
                                            bad_message::ESWMF_BAD_EVENT_ACK);
          },
          base::Unretained(process)));
}

void EventRouter::DecrementInFlightEventsForRenderFrameHost(
    int render_process_host,
    const ExtensionId& extension_id,
    int event_id,
    bool event_will_run_in_background_page_script) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  auto* process = RenderProcessHost::FromID(render_process_host);
  if (!process) {
    return;
  }

  ProcessManager* pm = ProcessManager::Get(process->GetBrowserContext());
  ExtensionHost* host = pm->GetBackgroundHostForExtension(extension_id);
  if (host) {
    host->OnEventAck(event_id, event_will_run_in_background_page_script);
  }
}

void EventRouter::IncrementInFlightEvents(
    BrowserContext* context,
    RenderProcessHost* process,
    const Extension* extension,
    int event_id,
    const std::string& event_name,
    base::TimeTicks dispatch_start_time,
=======
    int render_process_id,
>>>>>>> chromium
    int64_t service_worker_version_id,
    events::HistogramValue histogram_value,
    const std::string& event_name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  if (!ExtensionsBrowserClient::Get()->IsValidContext(browser_context))
    return;

  auto* registry = ExtensionRegistry::Get(browser_context);
  DCHECK(registry);
  const Extension* extension =
      registry->enabled_extensions().GetByID(extension_id);
  if (!extension)
    return;

  EventRouter* event_router = EventRouter::Get(browser_context);
  DCHECK(event_router);
  event_router->IncrementInFlightEvents(
      browser_context, RenderProcessHost::FromID(render_process_id), extension,
      event_id, event_name, service_worker_version_id);
  event_router->ReportEvent(histogram_value, extension, /*did_enqueue=*/false);
}

void EventRouter::IncrementInFlightEvents(BrowserContext* context,
                                          RenderProcessHost* process,
                                          const Extension* extension,
                                          int event_id,
                                          const std::string& event_name,
                                          int64_t service_worker_version_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  // Only increment in-flight events if the lazy background page is active,
  // because that's the only time we'll get an ACK.
  if (BackgroundInfo::HasLazyBackgroundPage(extension)) {
    ProcessManager* pm = ProcessManager::Get(context);
    ExtensionHost* host = pm->GetBackgroundHostForExtension(extension->id());
    if (host) {
      pm->IncrementLazyKeepaliveCount(extension, Activity::EVENT, event_name);
      host->OnBackgroundEventDispatched(event_name, event_id);
    }
  } else if (service_worker_version_id !=
             blink::mojom::kInvalidServiceWorkerVersionId) {
    // Check to make sure the rendered process hasn't gone away by the time
    // we've gotten here. (It's possible it has crashed, etc.) If that's
    // happened, we don't want to track the expected ACK, since we'll never
    // get it.
    if (process) {
      content::ServiceWorkerContext* service_worker_context =
          process->GetStoragePartition()->GetServiceWorkerContext();
      event_ack_data_.IncrementInflightEvent(
<<<<<<< HEAD
          service_worker_context, process->GetDeprecatedID(),
          service_worker_version_id, event_id, dispatch_start_time,
          dispatch_source, lazy_background_active_on_dispatch, histogram_value);
=======
          service_worker_context, process->GetID(), service_worker_version_id,
          event_id);
>>>>>>> chromium
    }
  }
}

void EventRouter::OnEventAck(BrowserContext* context,
                             const std::string& extension_id,
                             const std::string& event_name) {
  ProcessManager* pm = ProcessManager::Get(context);
  ExtensionHost* host = pm->GetBackgroundHostForExtension(extension_id);
  // The event ACK is routed to the background host, so this should never be
  // NULL.
  CHECK(host);
  // TODO(mpcomplete): We should never get this message unless
  // HasLazyBackgroundPage is true. Find out why we're getting it anyway.
  if (host->extension() &&
      BackgroundInfo::HasLazyBackgroundPage(host->extension()))
    pm->DecrementLazyKeepaliveCount(host->extension(), Activity::EVENT,
                                    event_name);
}

bool EventRouter::HasRegisteredEvents(const ExtensionId& extension_id) const {
  return !GetRegisteredEvents(extension_id, RegisteredEventType::kLazy)
              .empty() ||
         !GetRegisteredEvents(extension_id, RegisteredEventType::kServiceWorker)
              .empty();
}

void EventRouter::ReportEvent(events::HistogramValue histogram_value,
                              const Extension* extension,
                              bool did_enqueue) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  // Record every event fired.
  UMA_HISTOGRAM_ENUMERATION("Extensions.Events.Dispatch", histogram_value,
                            events::ENUM_BOUNDARY);

  bool is_component = Manifest::IsComponentLocation(extension->location());

  // Record events for component extensions. These should be kept to a minimum,
  // especially if they wake its event page. Component extensions should use
  // declarative APIs as much as possible.
  if (is_component) {
    UMA_HISTOGRAM_ENUMERATION("Extensions.Events.DispatchToComponent",
                              histogram_value, events::ENUM_BOUNDARY);
  }

  // Record events for background pages, if any. The most important statistic
  // is DispatchWithSuspendedEventPage. Events reported there woke an event
  // page. Implementing either filtered or declarative versions of these events
  // should be prioritised.
  //
  // Note: all we know is that the extension *has* a persistent or event page,
  // not that the event is being dispatched *to* such a page. However, this is
  // academic, since extensions with any background page have that background
  // page running (or in the case of suspended event pages, must be started)
  // regardless of where the event is being dispatched. Events are dispatched
  // to a *process* not a *frame*.
  if (BackgroundInfo::HasPersistentBackgroundPage(extension)) {
    UMA_HISTOGRAM_ENUMERATION(
        "Extensions.Events.DispatchWithPersistentBackgroundPage",
        histogram_value, events::ENUM_BOUNDARY);
  } else if (BackgroundInfo::HasLazyBackgroundPage(extension)) {
    if (did_enqueue) {
      UMA_HISTOGRAM_ENUMERATION(
          "Extensions.Events.DispatchWithSuspendedEventPage", histogram_value,
          events::ENUM_BOUNDARY);
    } else {
      UMA_HISTOGRAM_ENUMERATION(
          "Extensions.Events.DispatchWithRunningEventPage", histogram_value,
          events::ENUM_BOUNDARY);
    }
  } else if (BackgroundInfo::IsServiceWorkerBased(extension)) {
    base::UmaHistogramEnumeration(
        "Extensions.Events.DispatchWithServiceWorkerBackground",
        histogram_value, events::ENUM_BOUNDARY);
  }
}

void EventRouter::DispatchPendingEvent(
    std::unique_ptr<Event> event,
    std::unique_ptr<LazyContextTaskQueue::ContextInfo> params) {
  if (!params)
    return;

  if (listeners_.HasProcessListener(params->render_process_host,
                                    params->worker_thread_id,
                                    params->extension_id)) {
    DispatchEventToProcess(
        params->extension_id, params->url, params->render_process_host,
        params->service_worker_version_id, params->worker_thread_id,
        event.get(), nullptr, true /* did_enqueue */);
  }
}

void EventRouter::SetRegisteredEvents(const std::string& extension_id,
                                      const std::set<std::string>& events,
                                      RegisteredEventType type) {
  auto events_value = std::make_unique<base::ListValue>();
  for (auto iter = events.cbegin(); iter != events.cend(); ++iter) {
    events_value->AppendString(*iter);
  }
  const char* pref_key = type == RegisteredEventType::kLazy
                             ? kRegisteredLazyEvents
                             : kRegisteredServiceWorkerEvents;
  extension_prefs_->UpdateExtensionPref(extension_id, pref_key,
                                        std::move(events_value));
}

void EventRouter::AddFilterToEvent(const std::string& event_name,
                                   const std::string& extension_id,
                                   bool is_for_service_worker,
                                   const DictionaryValue* filter) {
  ExtensionPrefs::ScopedDictionaryUpdate update(
      extension_prefs_, extension_id,
      is_for_service_worker ? kFilteredServiceWorkerEvents : kFilteredEvents);
  auto filtered_events = update.Create();

  ListValue* filter_list = nullptr;
  if (!filtered_events->GetListWithoutPathExpansion(event_name, &filter_list)) {
    filtered_events->SetWithoutPathExpansion(
        event_name, std::make_unique<base::ListValue>());
    filtered_events->GetListWithoutPathExpansion(event_name, &filter_list);
  }

  filter_list->Append(filter->CreateDeepCopy());
}

void EventRouter::OnExtensionLoaded(content::BrowserContext* browser_context,
                                    const Extension* extension) {
  // Add all registered lazy listeners to our cache.
  std::set<std::string> registered_events =
      GetRegisteredEvents(extension->id(), RegisteredEventType::kLazy);
  listeners_.LoadUnfilteredLazyListeners(extension->id(), registered_events);

  std::set<std::string> registered_worker_events =
      GetRegisteredEvents(extension->id(), RegisteredEventType::kServiceWorker);
  listeners_.LoadUnfilteredWorkerListeners(extension->id(),
                                           registered_worker_events);

  const DictionaryValue* filtered_events =
      GetFilteredEvents(extension->id(), RegisteredEventType::kLazy);
  if (filtered_events)
    listeners_.LoadFilteredLazyListeners(
        extension->id(), false /* is_for_service_worker */, *filtered_events);

  const DictionaryValue* filtered_worker_events =
      GetFilteredEvents(extension->id(), RegisteredEventType::kServiceWorker);
  if (filtered_worker_events)
    listeners_.LoadFilteredLazyListeners(extension->id(),
                                         true /* is_for_service_worker */,
                                         *filtered_worker_events);
}

void EventRouter::OnExtensionUnloaded(content::BrowserContext* browser_context,
                                      const Extension* extension,
                                      UnloadedExtensionReason reason) {
  // Remove all registered listeners from our cache.
  listeners_.RemoveListenersForExtension(extension->id());
}

void EventRouter::OnStoppedTrackingServiceWorkerInstance(
    const WorkerId& worker_id) {
  // Remove any active listeners since they are no longer guaranteed to be ready
  // to receive events.
  listeners_.RemoveActiveServiceWorkerListenersForExtension(
      worker_id.extension_id);
}

void EventRouter::AddLazyEventListenerImpl(
    std::unique_ptr<EventListener> listener,
    RegisteredEventType type) {
  const ExtensionId extension_id = listener->extension_id();
  const std::string event_name = listener->event_name();
  bool is_new = listeners_.AddListener(std::move(listener));
  if (is_new) {
    std::set<std::string> events = GetRegisteredEvents(extension_id, type);
    bool prefs_is_new = events.insert(event_name).second;
    if (prefs_is_new)
      SetRegisteredEvents(extension_id, events, type);
  }
}

void EventRouter::RemoveLazyEventListenerImpl(
    std::unique_ptr<EventListener> listener,
    RegisteredEventType type) {
  const ExtensionId extension_id = listener->extension_id();
  const std::string event_name = listener->event_name();
  bool did_exist = listeners_.RemoveListener(listener.get());
  if (did_exist) {
    std::set<std::string> events = GetRegisteredEvents(extension_id, type);
    bool prefs_did_exist = events.erase(event_name) > 0;
    DCHECK(prefs_did_exist);
    SetRegisteredEvents(extension_id, events, type);
  }
}

Event::Event(events::HistogramValue histogram_value,
             const std::string& event_name,
             std::vector<base::Value> event_args)
    : Event(histogram_value, event_name, std::move(event_args), nullptr) {}

Event::Event(events::HistogramValue histogram_value,
             const std::string& event_name,
             std::vector<base::Value> event_args,
             content::BrowserContext* restrict_to_browser_context)
    : Event(histogram_value,
            event_name,
            std::move(event_args),
            restrict_to_browser_context,
            GURL(),
            EventRouter::USER_GESTURE_UNKNOWN,
            EventFilteringInfo()) {}

Event::Event(events::HistogramValue histogram_value,
             const std::string& event_name,
             std::vector<base::Value> event_args_tmp,
             content::BrowserContext* restrict_to_browser_context,
             const GURL& event_url,
             EventRouter::UserGestureState user_gesture,
             const EventFilteringInfo& info)
    : histogram_value(histogram_value),
      event_name(event_name),
      event_args(std::make_unique<base::ListValue>(std::move(event_args_tmp))),
      restrict_to_browser_context(restrict_to_browser_context),
      event_url(event_url),
      user_gesture(user_gesture),
      filter_info(info) {
  DCHECK(event_args);
  DCHECK_NE(events::UNKNOWN, histogram_value)
      << "events::UNKNOWN cannot be used as a histogram value.\n"
      << "If this is a test, use events::FOR_TEST.\n"
      << "If this is production code, it is important that you use a realistic "
      << "value so that we can accurately track event usage. "
      << "See extension_event_histogram_value.h for inspiration.";
}

Event::~Event() = default;

std::unique_ptr<Event> Event::DeepCopy() const {
  auto copy = std::make_unique<Event>(
      histogram_value, event_name, event_args->Clone().TakeList(),
      restrict_to_browser_context, event_url, user_gesture, filter_info);
  copy->will_dispatch_callback = will_dispatch_callback;
  return copy;
}

EventListenerInfo::EventListenerInfo(const std::string& event_name,
                                     const std::string& extension_id,
                                     const GURL& listener_url,
                                     content::BrowserContext* browser_context)
    : event_name(event_name),
      extension_id(extension_id),
      listener_url(listener_url),
      browser_context(browser_context),
      worker_thread_id(kMainThreadId),
      service_worker_version_id(blink::mojom::kInvalidServiceWorkerVersionId) {}

EventListenerInfo::EventListenerInfo(const std::string& event_name,
                                     const std::string& extension_id,
                                     const GURL& listener_url,
                                     content::BrowserContext* browser_context,
                                     int worker_thread_id,
                                     int64_t service_worker_version_id)
    : event_name(event_name),
      extension_id(extension_id),
      listener_url(listener_url),
      browser_context(browser_context),
      worker_thread_id(worker_thread_id),
      service_worker_version_id(service_worker_version_id) {}

}  // namespace extensions
