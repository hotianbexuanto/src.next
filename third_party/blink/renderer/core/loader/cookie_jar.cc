// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/loader/cookie_jar.h"

#include "base/metrics/histogram_functions.h"
#include "base/strings/strcat.h"
#include "third_party/blink/public/common/browser_interface_broker_proxy.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
<<<<<<< HEAD
#include "third_party/blink/renderer/core/frame/web_feature.h"
#include "third_party/blink/renderer/core/probe/core_probes.h"
=======
>>>>>>> chromium
#include "third_party/blink/renderer/platform/weborigin/kurl.h"

namespace blink {
namespace {

void LogCookieHistogram(const char* prefix,
                        bool cookie_manager_requested,
                        base::TimeDelta elapsed) {
  base::UmaHistogramTimes(
      base::StrCat({prefix, cookie_manager_requested ? "ManagerRequested"
                                                     : "ManagerAvailable"}),
      elapsed);
}

}  // namespace

CookieJar::CookieJar(blink::Document* document)
    : backend_(document->GetExecutionContext()), document_(document) {}

CookieJar::~CookieJar() = default;

void CookieJar::Trace(Visitor* visitor) const {
  visitor->Trace(backend_);
  visitor->Trace(document_);
}

void CookieJar::SetCookie(const String& value) {
  KURL cookie_url = document_->CookieURL();
  if (cookie_url.IsEmpty())
    return;

  base::ElapsedTimer timer;
<<<<<<< HEAD
  RequestRestrictedCookieManagerIfNeeded();
  backend_->SetCookieFromString(
      cookie_url, document_->SiteForCookies(), document_->TopFrameOrigin(),
      document_->GetExecutionContext()->GetStorageAccessApiStatus(),
      ShouldApplyDevtoolsOverrides(), value);
  last_operation_was_set_ = true;
  base::UmaHistogramTimes("Blink.SetCookieTime", timer.Elapsed());
  if (is_first_operation_) {
    LogFirstCookieRequest(FirstCookieRequest::kFirstOperationWasSet);
  }

  // TODO(crbug.com/1276520): Remove after truncating characters are fully
  // deprecated
  if (value.Find(ContainsTruncatingChar) != kNotFound) {
    document_->CountDeprecation(WebFeature::kCookieWithTruncatingChar);
  }
}

void CookieJar::OnBackendDisconnect() {
  shared_memory_version_client_.reset();
  InvalidateCache();
=======
  bool requested = RequestRestrictedCookieManagerIfNeeded();
  backend_->SetCookieFromString(cookie_url, document_->SiteForCookies(),
                                document_->TopFrameOrigin(), value);
  LogCookieHistogram("Blink.SetCookieTime.", requested, timer.Elapsed());
>>>>>>> chromium
}

String CookieJar::Cookies() {
  KURL cookie_url = document_->CookieURL();
  if (cookie_url.IsEmpty())
    return String();

  base::ElapsedTimer timer;
<<<<<<< HEAD
  RequestRestrictedCookieManagerIfNeeded();

  String value = g_empty_string;
  base::ReadOnlySharedMemoryRegion new_mapped_region;
  const bool get_version_shared_memory =
      !shared_memory_version_client_.has_value();

  // Store the latest cookie version to update |last_version_| after attempting
  // to get the string. Will get updated once more by GetCookiesString() if an
  // ipc is required.
  uint64_t new_version = last_version_;
  bool should_apply_devtools_overrides = ShouldApplyDevtoolsOverrides();
  const bool ipc_needed = IPCNeeded(should_apply_devtools_overrides);
  base::UmaHistogramBoolean("Blink.Experimental.Cookies.IpcNeeded", ipc_needed);
  if (ipc_needed) {
    bool is_ad_tagged =
        document_->GetFrame() ? document_->GetFrame()->IsAdFrame() : false;

    if (!backend_->GetCookiesString(
            cookie_url, document_->SiteForCookies(),
            document_->TopFrameOrigin(),
            document_->GetExecutionContext()->GetStorageAccessApiStatus(),
            get_version_shared_memory, is_ad_tagged,
            should_apply_devtools_overrides,
            /*force_disable_third_party_cookies=*/false, &new_version,
            &new_mapped_region, &value)) {
      // On IPC failure invalidate cached values and return empty string since
      // there is no guarantee the client can still validly access cookies in
      // the current context. See crbug.com/1468909.
      InvalidateCache();
      return g_empty_string;
    }
    last_cookies_ = value;
  }
  if (new_mapped_region.IsValid()) {
    shared_memory_version_client_.emplace(std::move(new_mapped_region));
  }
  base::UmaHistogramTimes("Blink.CookiesTime", timer.Elapsed());
  UpdateCacheAfterGetRequest(cookie_url, value, new_version);

  last_operation_was_set_ = false;
  if (is_first_operation_) {
    LogFirstCookieRequest(FirstCookieRequest::kFirstOperationWasGet);
  }
  return last_cookies_;
=======
  bool requested = RequestRestrictedCookieManagerIfNeeded();
  String value;
  backend_->GetCookiesString(cookie_url, document_->SiteForCookies(),
                             document_->TopFrameOrigin(), &value);
  LogCookieHistogram("Blink.CookiesTime.", requested, timer.Elapsed());
  return value;
>>>>>>> chromium
}

bool CookieJar::CookiesEnabled() {
  KURL cookie_url = document_->CookieURL();
  if (cookie_url.IsEmpty())
    return false;

  base::ElapsedTimer timer;
  bool requested = RequestRestrictedCookieManagerIfNeeded();
  bool cookies_enabled = false;
<<<<<<< HEAD
  backend_->CookiesEnabledFor(
      cookie_url, document_->SiteForCookies(), document_->TopFrameOrigin(),
      document_->GetExecutionContext()->GetStorageAccessApiStatus(),
      ShouldApplyDevtoolsOverrides(), &cookies_enabled);
  base::UmaHistogramTimes("Blink.CookiesEnabledTime", timer.Elapsed());
  if (is_first_operation_) {
    LogFirstCookieRequest(FirstCookieRequest::kFirstOperationWasCookiesEnabled);
  }
  return cookies_enabled;
}

void CookieJar::SetCookieManager(
    mojo::PendingRemote<network::mojom::blink::RestrictedCookieManager>
        cookie_manager) {
  backend_.reset();
  backend_.Bind(std::move(cookie_manager),
                document_->GetTaskRunner(TaskType::kInternalDefault));
}

void CookieJar::InvalidateCache() {
  last_cookies_hash_.reset();
  last_cookies_ = String();
  last_version_ = mojo::shared_memory_version::kInvalidVersion;
}

bool CookieJar::IPCNeeded(bool should_apply_devtools_overrides) {
  // IPC needed if devtools overrides is different
  if (should_apply_devtools_overrides != last_devtools_overrides_were_applied) {
    last_devtools_overrides_were_applied = should_apply_devtools_overrides;
    return true;
  }

  // |last_cookies_| can be null when converting the raw mojo payload failed.
  // (See ConvertUTF8ToUTF16() for details.) In that case use an IPC to request
  // another string to be safe.
  if (last_cookies_.IsNull()) {
    return true;
  }

  // No shared memory communication so IPC needed.
  if (!shared_memory_version_client_.has_value()) {
    return true;
  }

  // Cookie string has changed.
  if (shared_memory_version_client_->SharedVersionIsGreaterThan(
          last_version_)) {
    return true;
  }

  // No IPC needed!
  return false;
}

void CookieJar::RequestRestrictedCookieManagerIfNeeded() {
=======
  backend_->CookiesEnabledFor(cookie_url, document_->SiteForCookies(),
                              document_->TopFrameOrigin(), &cookies_enabled);
  LogCookieHistogram("Blink.CookiesEnabledTime.", requested, timer.Elapsed());
  return cookies_enabled;
}

bool CookieJar::RequestRestrictedCookieManagerIfNeeded() {
>>>>>>> chromium
  if (!backend_.is_bound() || !backend_.is_connected()) {
    backend_.reset();
    document_->GetFrame()->GetBrowserInterfaceBroker().GetInterface(
        backend_.BindNewPipeAndPassReceiver(
            document_->GetTaskRunner(TaskType::kInternalDefault)));
    return true;
  }
  return false;
}

bool CookieJar::ShouldApplyDevtoolsOverrides() const {
  bool should_apply_devtools_overrides = false;
  probe::ShouldApplyDevtoolsCookieSettingOverrides(
      document_->GetExecutionContext(), &should_apply_devtools_overrides);

  return should_apply_devtools_overrides;
}

}  // namespace blink
