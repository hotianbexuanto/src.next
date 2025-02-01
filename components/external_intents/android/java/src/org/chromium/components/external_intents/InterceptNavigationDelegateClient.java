// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.components.external_intents;

import android.app.Activity;

<<<<<<< HEAD
import org.chromium.content_public.browser.LoadUrlParams;
=======
import org.chromium.components.external_intents.ExternalNavigationHandler.OverrideUrlLoadingResult;
import org.chromium.components.navigation_interception.NavigationParams;
>>>>>>> chromium
import org.chromium.content_public.browser.WebContents;

/**
 * An interface via which the embedder provides the context information that
 * InterceptNavigationDelegateImpl needs.
 */
public interface InterceptNavigationDelegateClient {
    /* Returns the WebContents in the context of which this InterceptNavigationDelegateImpl instance
     * is operating. */
    WebContents getWebContents();

    /* Creates an ExternalNavigationHandler instance that is configured for this client. */
    ExternalNavigationHandler createExternalNavigationHandler();

    /* Gets a RedirectHandler instance that is associated with this client, creating it if
     * necessary. */
    RedirectHandler getOrCreateRedirectHandler();

    /* Creates an AuthenticatorNavigationInterceptor instance that is configured for this client.
     */
    AuthenticatorNavigationInterceptor createAuthenticatorNavigationInterceptor();

    /* Returns whether whether the tab associated with this client is incognito. */
    boolean isIncognito();

<<<<<<< HEAD
=======
    /* Returns whether whether the tab associated with this client is currently hidden. */
    boolean isHidden();

    /* Returns whether intent launching from hidden tabs is allowed for the navigation specified
     * by |params|. */
    boolean areIntentLaunchesAllowedInHiddenTabsForNavigation(NavigationParams params);

>>>>>>> chromium
    /* Returns the Activity associated with this client. */
    Activity getActivity();

    /* Returns true if the tab associated with this client was launched from an external app. */
    boolean wasTabLaunchedFromExternalApp();

    /* Returns true if the tab associated with this client was launched from a long press in the
     * background. */
    boolean wasTabLaunchedFromLongPressInBackground();

    /* Invoked when the tab associated with this client should be closed. */
    void closeTab();

<<<<<<< HEAD
    /**
     * Loads a URL as specified by |loadUrlParams| if possible. May fail in exceptional conditions
     * (e.g., if there is no valid tab).
     *
     * @param loadUrlParams parameters of the URL to be loaded
     */
    void loadUrlIfPossible(LoadUrlParams loadUrlParams);
=======
    /* Invoked when a navigation has begun in the InterceptNavigationDelegateImpl instance
     * associated with this instance. */
    void onNavigationStarted(NavigationParams params);

    /* Invoked when the InterceptNavigationDelegateImpl instance
     * associated with this instance has reached a decision for the navigation specified by
     * |params|. |overrideUrlLoadingResult| specifies the decision. */
    void onDecisionReachedForNavigation(
            NavigationParams params, OverrideUrlLoadingResult overrideUrlLoadingResult);
>>>>>>> chromium
}
