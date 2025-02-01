// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/dactyloscoper.h"

#include "third_party/blink/public/common/privacy_budget/identifiability_metric_builder.h"
#include "third_party/blink/public/common/privacy_budget/identifiability_study_settings.h"
#include "third_party/blink/public/common/privacy_budget/identifiable_token_builder.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/loader/document_loader.h"
#include "third_party/blink/renderer/core/svg/svg_string_list_tear_off.h"
#include "third_party/blink/renderer/platform/privacy_budget/identifiability_digest_helpers.h"

namespace blink {

Dactyloscoper::Dactyloscoper() = default;

void Dactyloscoper::Record(WebFeature feature) {
  // TODO(mkwst): This is a stub. We'll pull in more interesting functionality
  // here over time.
}

namespace {

bool ShouldSample(WebFeature feature) {
  return IdentifiabilityStudySettings::Get()->ShouldSample(
      IdentifiableSurface::FromTypeAndToken(
          IdentifiableSurface::Type::kWebFeature, feature));
}

<<<<<<< HEAD
using CalledJsApi = perfetto::protos::pbzero::BlinkHighEntropyAPI::CalledJsApi;
using JSFunctionArgument =
    perfetto::protos::pbzero::BlinkHighEntropyAPI::JSFunctionArgument;
using ArgumentType = perfetto::protos::pbzero::BlinkHighEntropyAPI::
    JSFunctionArgument::ArgumentType;
using ChromeTrackEvent = perfetto::protos::pbzero::ChromeTrackEvent;
using HighEntropyAPI = perfetto::protos::pbzero::BlinkHighEntropyAPI;
using ExecutionContextProto = perfetto::protos::pbzero::BlinkExecutionContext;
using SourceLocationProto = perfetto::protos::pbzero::BlinkSourceLocation;
using FontLookup = perfetto::protos::pbzero::BlinkHighEntropyAPI::FontLookup;
using FontLookupType =
    perfetto::protos::pbzero::BlinkHighEntropyAPI::FontLookup::FontLookupType;

ArgumentType GetArgumentType(v8::Local<v8::Value> value) {
  if (value->IsUndefined()) {
    return ArgumentType::UNDEFINED;
  }
  if (value->IsNull()) {
    return ArgumentType::NULL_TYPE;
  }
  if (value->IsBigInt()) {
    return ArgumentType::BIGINT;
  }
  if (value->IsBoolean()) {
    return ArgumentType::BOOLEAN;
  }
  if (value->IsFunction()) {
    return ArgumentType::FUNCTION;
  }
  if (value->IsNumber()) {
    return ArgumentType::NUMBER;
  }
  if (value->IsString()) {
    return ArgumentType::STRING;
  }
  if (value->IsSymbol()) {
    return ArgumentType::SYMBOL;
  }
  if (value->IsObject()) {
    return ArgumentType::OBJECT;
  }

  return ArgumentType::UNKNOWN_TYPE;
}

// Returns the stringified object on success and an empty string on failure
String V8ValueToString(v8::Local<v8::Context> current_context,
                       v8::Isolate* isolate,
                       const v8::Local<v8::Value>& value) {
  v8::Local<v8::String> v8_string;

  if (!value->ToDetailString(current_context).ToLocal(&v8_string)) {
    return g_empty_string;
  }

  return ToBlinkString<String>(isolate, v8_string, kDoNotExternalize);
}

FontLookupType ToTypeProto(Dactyloscoper::FontLookupType lookup_type) {
  switch (lookup_type) {
    case Dactyloscoper::FontLookupType::kUniqueOrFamilyName:
      return FontLookupType::FONT_LOOKUP_UNIQUE_OR_FAMILY_NAME;
    case Dactyloscoper::FontLookupType::kUniqueNameOnly:
      return FontLookupType::FONT_LOOKUP_UNIQUE_NAME_ONLY;
  }
}

=======
>>>>>>> chromium
}  // namespace

// static
void Dactyloscoper::Record(ExecutionContext* context, WebFeature feature) {
  // TODO: Workers.
  if (!context)
    return;
  if (auto* window = DynamicTo<LocalDOMWindow>(context)) {
    if (auto* frame = window->GetFrame())
      frame->Loader().GetDocumentLoader()->GetDactyloscoper().Record(feature);
  }
}

// static
void Dactyloscoper::RecordDirectSurface(ExecutionContext* context,
                                        WebFeature feature,
                                        const IdentifiableToken& value) {
  if (!context || !ShouldSample(feature))
    return;
  auto* window = DynamicTo<LocalDOMWindow>(context);
  if (!window)
    return;
  Document* document = window->document();
  IdentifiabilityMetricBuilder(document->UkmSourceID())
      .SetWebfeature(feature, value)
      .Record(document->UkmRecorder());
}

// static
void Dactyloscoper::RecordDirectSurface(ExecutionContext* context,
                                        WebFeature feature,
                                        const String& str) {
  if (!context || !ShouldSample(feature))
    return;
  if (str.IsEmpty())
    return;
  Dactyloscoper::RecordDirectSurface(context, feature,
                                     IdentifiabilitySensitiveStringToken(str));
}

// static
void Dactyloscoper::RecordDirectSurface(ExecutionContext* context,
                                        WebFeature feature,
                                        const Vector<String>& strs) {
  if (!context || !ShouldSample(feature))
    return;
  if (strs.IsEmpty())
    return;
  IdentifiableTokenBuilder builder;
  for (const auto& str : strs) {
    builder.AddToken(IdentifiabilitySensitiveStringToken(str));
  }
  Dactyloscoper::RecordDirectSurface(context, feature, builder.GetToken());
}

// static
void Dactyloscoper::RecordDirectSurface(ExecutionContext* context,
                                        WebFeature feature,
                                        const DOMArrayBufferView* buffer) {
  if (!context || !ShouldSample(feature))
    return;
  if (!buffer || buffer->byteLength() == 0)
    return;
  IdentifiableTokenBuilder builder(base::make_span(
      static_cast<uint8_t*>(buffer->BaseAddress()), buffer->byteLength()));
  Dactyloscoper::RecordDirectSurface(context, feature, builder.GetToken());
}

// static
void Dactyloscoper::RecordDirectSurface(ExecutionContext* context,
                                        WebFeature feature,
                                        SVGStringListTearOff* strings) {
  RecordDirectSurface(context, feature, strings->Values());
}

}  // namespace blink
