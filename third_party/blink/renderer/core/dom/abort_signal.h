// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_DOM_ABORT_SIGNAL_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_DOM_ABORT_SIGNAL_H_

<<<<<<< HEAD
#include "base/functional/callback_forward.h"
#include "third_party/blink/renderer/bindings/core/v8/script_value.h"
=======
#include "base/callback_forward.h"
>>>>>>> chromium
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/dom/events/event_target.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/execution_context/execution_context_lifecycle_observer.h"
#include "third_party/blink/renderer/platform/heap/collection_support/heap_linked_hash_set.h"
#include "third_party/blink/renderer/platform/heap/collection_support/heap_vector.h"
#include "third_party/blink/renderer/platform/heap/member.h"
#include "third_party/blink/renderer/platform/scheduler/public/post_cancellable_task.h"

namespace v8 {
class Isolate;
}  // namespace v8
=======
#include "third_party/blink/renderer/platform/heap/heap_allocator.h"
#include "third_party/blink/renderer/platform/heap/member.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
>>>>>>> chromium

namespace blink {

class ExecutionContext;
class ScriptState;

// Implementation of https://dom.spec.whatwg.org/#interface-AbortSignal
<<<<<<< HEAD
class CORE_EXPORT AbortSignal : public EventTarget,
                                public ExecutionContextLifecycleObserver {
=======
class CORE_EXPORT AbortSignal : public EventTargetWithInlineData {
>>>>>>> chromium
  DEFINE_WRAPPERTYPEINFO();

 public:
  explicit AbortSignal(ExecutionContext*);
  ~AbortSignal() override;

  // abort_signal.idl
  static AbortSignal* abort(ScriptState*);
<<<<<<< HEAD
  static AbortSignal* abort(ScriptState*, ScriptValue reason);
  static AbortSignal* any(ScriptState*,
                          HeapVector<Member<AbortSignal>> signals);
  static AbortSignal* timeout(ScriptState*, uint64_t milliseconds);
  ScriptValue reason(ScriptState*) const;
  bool aborted() const { return !abort_reason_.IsEmpty(); }
  void throwIfAborted(v8::Isolate*) const;
=======
  bool aborted() const { return aborted_flag_; }
>>>>>>> chromium
  DEFINE_ATTRIBUTE_EVENT_LISTENER(abort, kAbort)

  const AtomicString& InterfaceName() const override;
  ExecutionContext* GetExecutionContext() const override;

  // `ExecutionContextLifecycleObserver` overrides:
  void ContextDestroyed() override;

  // Internal API

  // The "add an algorithm" algorithm from the standard:
  // https://dom.spec.whatwg.org/#abortsignal-add for dependent features to call
  // to be notified when abort has been signalled. Callers should pass a
  // OnceClosure holding a weak pointer, unless the object needs to receive a
  // cancellation signal even after it otherwise would have been destroyed.
  void AddAlgorithm(base::OnceClosure algorithm);

  //
  // The "remove an algorithm" algorithm
  // https://dom.spec.whatwg.org/#abortsignal-remove is not yet implemented as
  // it has no users currently. See
  // https://docs.google.com/document/d/1OuoCG2uiijbAwbCw9jaS7tHEO0LBO_4gMNio1ox0qlY/edit#heading=h.m1zf7fypmlb9
  // for discussion.
  //

  // The "To signal abort" algorithm from the standard:
  // https://dom.spec.whatwg.org/#abortsignal-add. Run all algorithms that were
  // added by AddAlgorithm(), in order of addition, then fire an "abort"
  // event. Does nothing if called more than once.
  void SignalAbort();

  // The "follow" algorithm from the standard:
  // https://dom.spec.whatwg.org/#abortsignal-follow
  // |this| is the followingSignal described in the standard.
  void Follow(AbortSignal* parentSignal);

  virtual bool IsTaskSignal() const { return false; }

  void Trace(Visitor*) const override;

 private:
  void AddSignalAbortAlgorithm(AbortSignal*);

<<<<<<< HEAD
  void AbortTimeoutFired(ScriptState*);

  enum class AddRemoveType { kAdded, kRemoved };
  void OnEventListenerAddedOrRemoved(const AtomicString& event_type,
                                     AddRemoveType);

  void SetAbortReason(ScriptState* script_state, ScriptValue reason);
  void RunAbortSteps();

  // https://dom.spec.whatwg.org/#abortsignal-abort-reason
  // There is one difference from the spec. The value is empty instead of
  // undefined when this signal is not aborted. This is because
  // ScriptValue::IsUndefined requires callers to enter a V8 context whereas
  // ScriptValue::IsEmpty does not.
  ScriptValue abort_reason_;
  HeapLinkedHashSet<WeakMember<AbortSignal::AlgorithmHandle>> abort_algorithms_;
  SignalType signal_type_;

  // This is set to a DependentSignalCompositionManager for composite signals or
  // a SourceSignalCompositionManager for non-composite signals. Null if
  // AbortSignalAny isn't enabled.
  Member<AbortSignalCompositionManager> composition_manager_;

  // Handle for the delayed task associated with `SignalType::kTimeout` signals.
  TaskHandle timout_task_handle_;
=======
  bool aborted_flag_ = false;
  Vector<base::OnceClosure> abort_algorithms_;
  HeapVector<Member<AbortSignal>> dependent_signals_;
  Member<ExecutionContext> execution_context_;
>>>>>>> chromium
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_DOM_ABORT_SIGNAL_H_
