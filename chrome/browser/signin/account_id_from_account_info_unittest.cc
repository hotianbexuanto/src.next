// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/signin/account_id_from_account_info.h"
<<<<<<< HEAD

#include "chrome/test/base/scoped_testing_local_state.h"
#include "chrome/test/base/testing_browser_process.h"
#include "google_apis/gaia/gaia_id.h"
=======
>>>>>>> chromium
#include "testing/gtest/include/gtest/gtest.h"

class AccountIdFromAccountInfoTest : public testing::Test {};

// Tests that AccountIdFromAccountInfo() passes along a canonicalized email to
// AccountId.
TEST(AccountIdFromAccountInfoTest,
     AccountIdFromAccountInfo_CanonicalizesRawEmail) {
  AccountInfo info;
  info.email = "test.email@gmail.com";
  info.gaia = GaiaId("test_id");

  EXPECT_EQ("testemail@gmail.com",
            AccountIdFromAccountInfo(info).GetUserEmail());
}
