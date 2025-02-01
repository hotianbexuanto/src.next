// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/navigator_ua_data.h"

#include "base/compiler_specific.h"
#include "base/single_thread_task_runner.h"
#include "third_party/blink/public/common/privacy_budget/identifiability_metric_builder.h"
#include "third_party/blink/public/common/privacy_budget/identifiability_study_settings.h"
#include "third_party/blink/public/common/privacy_budget/identifiable_surface.h"
#include "third_party/blink/public/common/privacy_budget/identifiable_token.h"
#include "third_party/blink/public/common/privacy_budget/identifiable_token_builder.h"
#include "third_party/blink/public/mojom/web_feature/web_feature.mojom-blink.h"
#include "third_party/blink/renderer/bindings/core/v8/script_promise_resolver.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_ua_data_values.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/page/page.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"

namespace blink {

namespace {

// Record identifiability study metrics for a single field requested by a
// getHighEntropyValues() call if the user is in the study.
void MaybeRecordMetric(bool record_identifiability,
                       const String& hint,
                       const String& value,
                       ExecutionContext* execution_context) {
  if (LIKELY(!record_identifiability))
    return;
  auto identifiable_surface = IdentifiableSurface::FromTypeAndToken(
      IdentifiableSurface::Type::kNavigatorUAData_GetHighEntropyValues,
      IdentifiableToken(hint.Utf8()));
  IdentifiabilityMetricBuilder(execution_context->UkmSourceID())
      .Set(identifiable_surface, IdentifiableToken(value.Utf8()))
      .Record(execution_context->UkmRecorder());
}

}  // namespace

NavigatorUAData::NavigatorUAData(ExecutionContext* context)
    : ExecutionContextClient(context) {
  NavigatorUABrandVersion* dict = NavigatorUABrandVersion::Create();
  dict->setBrand("");
  dict->setVersion("");
  empty_brand_set_.push_back(dict);
}

void NavigatorUAData::AddBrandVersion(const String& brand,
                                      const String& version) {
  NavigatorUABrandVersion* dict = NavigatorUABrandVersion::Create();
  dict->setBrand(brand);
  dict->setVersion(version);
  brand_set_.push_back(dict);
}

void NavigatorUAData::SetBrandVersionList(
    const UserAgentBrandList& brand_version_list) {
  for (const auto& brand_version : brand_version_list) {
    AddBrandVersion(String::FromUTF8(brand_version.brand),
                    String::FromUTF8(brand_version.major_version));
  }
}

void NavigatorUAData::SetMobile(bool mobile) {
  is_mobile_ = mobile;
}

void NavigatorUAData::SetPlatform(const String& brand, const String& version) {
  platform_ = brand;
  platform_version_ = version;
}

void NavigatorUAData::SetArchitecture(const String& architecture) {
  architecture_ = architecture;
}

void NavigatorUAData::SetModel(const String& model) {
  model_ = model;
}

void NavigatorUAData::SetUAFullVersion(const String& ua_full_version) {
  ua_full_version_ = ua_full_version;
}

void NavigatorUAData::SetBitness(const String& bitness) {
  bitness_ = bitness;
}

bool NavigatorUAData::mobile() const {
  if (GetExecutionContext()) {
    return is_mobile_;
  }
  return false;
}

const HeapVector<Member<NavigatorUABrandVersion>>& NavigatorUAData::brands()
    const {
  if (GetExecutionContext()) {
    return brand_set_;
  }
  return empty_brand_set_;
}

const String& NavigatorUAData::platform() const {
  if (GetExecutionContext()) {
    return platform_;
  }
  return WTF::g_empty_string;
}

<<<<<<< HEAD
bool AllowedToCollectHighEntropyValues(ExecutionContext* execution_context) {
  // To determine whether a document is allowed to use the get high-entropy
  // client hints returned by navigator.userAgentData.getHighEntropyValues(),
  // check the following:

  // 1. Check if our RuntimeEnabledFeature is enabled
  // Note: We return true if not enabled because the default allowlist is "*",
  // this permissions-policy allows a document to restrict it.
  // TODO(crbug.com/388538952): remove this after it ships to stable
  if (!RuntimeEnabledFeatures::
          ClientHintUAHighEntropyValuesPermissionPolicyEnabled()) {
    return true;
  }

  // 2. If Permissions Policy is enabled, return the policy for
  // "ch-ua-high-entropy-values" feature.
  return execution_context->IsFeatureEnabled(
      network::mojom::PermissionsPolicyFeature::kClientHintUAHighEntropyValues,
      ReportOptions::kReportOnFailure,
      "Collection of high-entropy user-agent client hints is disabled for "
      "this document.");
}

ScriptPromise<UADataValues> NavigatorUAData::getHighEntropyValues(
=======
ScriptPromise NavigatorUAData::getHighEntropyValues(
>>>>>>> chromium
    ScriptState* script_state,
    Vector<String>& hints) const {
  auto* resolver = MakeGarbageCollected<ScriptPromiseResolver>(script_state);
  ScriptPromise promise = resolver->Promise();
  auto* execution_context =
      ExecutionContext::From(script_state);  // GetExecutionContext();
  DCHECK(execution_context);

  bool record_identifiability =
      IdentifiabilityStudySettings::Get()->ShouldSample(
          IdentifiableSurface::Type::kNavigatorUAData_GetHighEntropyValues);
  UADataValues* values = MakeGarbageCollected<UADataValues>();
<<<<<<< HEAD
  // TODO: It'd be faster to compare hint when turning |hints| into an
  // AtomicString vector and turning the const string literals |hint| into
  // AtomicStrings as well.

  // According to
  // https://wicg.github.io/ua-client-hints/#getHighEntropyValues, the
  // low-entropy brands, mobile and platform hints should always be included for
  // convenience.

  // Use `brands()` and not `brand_set_` directly since the former also
  // records IdentifiabilityStudy metrics.
  values->setBrands(brands());
  values->setMobile(is_mobile_);
  values->setPlatform(platform_);
  // Record IdentifiabilityStudy metrics for `mobile()` and `platform()` (the
  // `brands()` part is already recorded inside that function).
  Dactyloscoper::RecordDirectSurface(
      GetExecutionContext(), WebFeature::kNavigatorUAData_Mobile, mobile());
  Dactyloscoper::RecordDirectSurface(
      GetExecutionContext(), WebFeature::kNavigatorUAData_Platform, platform());

  // If the "ch-ua-high-entropy-values" permission policy is enabled for a
  // document, add high-entropy client hints to values (if requested)
  if (AllowedToCollectHighEntropyValues(execution_context)) {
    for (const String& hint : hints) {
      if (hint == "platformVersion") {
        values->setPlatformVersion(platform_version_);
        MaybeRecordMetric(record_identifiability, hint, platform_version_,
                          execution_context);
      } else if (hint == "architecture") {
        values->setArchitecture(architecture_);
        MaybeRecordMetric(record_identifiability, hint, architecture_,
                          execution_context);
      } else if (hint == "model") {
        values->setModel(model_);
        MaybeRecordMetric(record_identifiability, hint, model_,
                          execution_context);
      } else if (hint == "uaFullVersion") {
        values->setUaFullVersion(ua_full_version_);
        MaybeRecordMetric(record_identifiability, hint, ua_full_version_,
                          execution_context);
      } else if (hint == "bitness") {
        values->setBitness(bitness_);
        MaybeRecordMetric(record_identifiability, hint, bitness_,
                          execution_context);
      } else if (hint == "fullVersionList") {
        values->setFullVersionList(full_version_list_);
      } else if (hint == "wow64") {
        values->setWow64(is_wow64_);
        MaybeRecordMetric(record_identifiability, hint, is_wow64_ ? "?1" : "?0",
                          execution_context);
      } else if (hint == "formFactors") {
        values->setFormFactors(form_factors_);
        MaybeRecordMetric(record_identifiability, hint, form_factors_,
                          execution_context);
      }
=======
  for (const String& hint : hints) {
    values->setBrands(brand_set_);
    values->setMobile(is_mobile_);
    if (hint == "platform") {
      values->setPlatform(platform_);
      MaybeRecordMetric(record_identifiability, hint, platform_,
                        execution_context);
    } else if (hint == "platformVersion") {
      values->setPlatformVersion(platform_version_);
      MaybeRecordMetric(record_identifiability, hint, platform_version_,
                        execution_context);
    } else if (hint == "architecture") {
      values->setArchitecture(architecture_);
      MaybeRecordMetric(record_identifiability, hint, architecture_,
                        execution_context);
    } else if (hint == "model") {
      values->setModel(model_);
      MaybeRecordMetric(record_identifiability, hint, model_,
                        execution_context);
    } else if (hint == "uaFullVersion") {
      values->setUaFullVersion(ua_full_version_);
      MaybeRecordMetric(record_identifiability, hint, ua_full_version_,
                        execution_context);
    } else if (hint == "bitness") {
      values->setBitness(bitness_);
      MaybeRecordMetric(record_identifiability, hint, bitness_,
                        execution_context);
>>>>>>> chromium
    }
  }

  execution_context->GetTaskRunner(TaskType::kPermission)
      ->PostTask(
          FROM_HERE,
          WTF::Bind([](ScriptPromiseResolver* resolver,
                       UADataValues* values) { resolver->Resolve(values); },
                    WrapPersistent(resolver), WrapPersistent(values)));

  return promise;
}

ScriptObject NavigatorUAData::toJSON(ScriptState* script_state) const {
  V8ObjectBuilder builder(script_state);
<<<<<<< HEAD
  builder.AddVector<NavigatorUABrandVersion>("brands", brands());
  builder.AddBoolean("mobile", mobile());
  builder.AddString("platform", platform());

  // Record IdentifiabilityStudy metrics for `mobile()` and `platform()`
  // (the `brands()` part is already recorded inside that function).
  Dactyloscoper::RecordDirectSurface(
      GetExecutionContext(), WebFeature::kNavigatorUAData_Mobile, mobile());
  Dactyloscoper::RecordDirectSurface(
      GetExecutionContext(), WebFeature::kNavigatorUAData_Platform, platform());

  return builder.ToScriptObject();
=======
  builder.Add("brands", brands());
  builder.Add("mobile", mobile());
  return builder.GetScriptValue();
>>>>>>> chromium
}

void NavigatorUAData::Trace(Visitor* visitor) const {
  visitor->Trace(brand_set_);
  visitor->Trace(empty_brand_set_);
  ScriptWrappable::Trace(visitor);
  ExecutionContextClient::Trace(visitor);
}

}  // namespace blink
