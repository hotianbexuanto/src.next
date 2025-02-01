// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tab;

import org.chromium.base.UserData;
import org.chromium.components.external_intents.InterceptNavigationDelegateImpl;

/**
 * Class that glues InterceptNavigationDelegateImpl objects to Tabs.
 */
public class InterceptNavigationDelegateTabHelper implements UserData {
    private static final Class<InterceptNavigationDelegateTabHelper> USER_DATA_KEY =
            InterceptNavigationDelegateTabHelper.class;

    private final InterceptNavigationDelegateImpl mInterceptNavigationDelegate;
    private final InterceptNavigationDelegateClientImpl mInterceptNavigationDelegateClient;

    public static void createForTab(Tab tab) {
<<<<<<< HEAD
        tab.getUserDataHost()
                .setUserData(USER_DATA_KEY, new InterceptNavigationDelegateTabHelper(tab));
=======
        assert get(tab) == null;
        tab.getUserDataHost().setUserData(
                USER_DATA_KEY, new InterceptNavigationDelegateTabHelper(tab));
>>>>>>> chromium
    }

    InterceptNavigationDelegateTabHelper(Tab tab) {
        mInterceptNavigationDelegateClient = new InterceptNavigationDelegateClientImpl(tab);
        mInterceptNavigationDelegate =
                new InterceptNavigationDelegateImpl(mInterceptNavigationDelegateClient);
        mInterceptNavigationDelegateClient.initializeWithDelegate(mInterceptNavigationDelegate);
    }

    @Override
    public void destroy() {
        mInterceptNavigationDelegateClient.destroy();
    }
}
