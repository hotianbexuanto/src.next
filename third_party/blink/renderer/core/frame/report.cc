// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/report.h"

namespace blink {

ScriptObject Report::toJSON(ScriptState* script_state) const {
  V8ObjectBuilder builder(script_state);
  builder.AddString("type", type());
  builder.AddString("url", url());
  V8ObjectBuilder body_builder(script_state);
  body()->BuildJSONValue(body_builder);
  builder.Add("body", body_builder);
  return builder.ToScriptObject();
}

unsigned Report::MatchId() const {
  unsigned hash = body()->MatchId();
  hash = WTF::HashInts(hash, url().IsNull() ? 0 : url().Impl()->GetHash());
  hash = WTF::HashInts(hash, type().Impl()->GetHash());
  return hash;
}

}  // namespace blink
