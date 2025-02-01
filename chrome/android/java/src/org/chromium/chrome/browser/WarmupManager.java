// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser;

import android.annotation.SuppressLint;
import android.content.Context;
import android.net.Uri;
import android.os.SystemClock;
import android.view.ContextThemeWrapper;
import android.view.InflateException;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewStub;
import android.widget.FrameLayout;

import androidx.annotation.IntDef;
import androidx.annotation.VisibleForTesting;

import org.chromium.base.Log;
import org.chromium.base.ThreadUtils;
import org.chromium.base.TraceEvent;
import org.chromium.base.annotations.NativeMethods;
import org.chromium.base.library_loader.LibraryLoader;
import org.chromium.base.metrics.RecordHistogram;
import org.chromium.base.task.AsyncTask;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.toolbar.ControlContainer;
import org.chromium.components.embedder_support.util.UrlConstants;
import org.chromium.content_public.browser.WebContents;
import org.chromium.content_public.browser.WebContentsObserver;
import org.chromium.ui.LayoutInflaterUtils;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * This class is a singleton that holds utilities for warming up Chrome and prerendering urls
 * without creating the Activity.
 *
 * <p>This class is not thread-safe and must only be used on the UI thread.
 */
public class WarmupManager {
    private static final String TAG = "WarmupManager";

    @VisibleForTesting
    static final String WEBCONTENTS_STATUS_HISTOGRAM = "CustomTabs.SpareWebContents.Status2";

    public static final boolean FOR_CCT = true;

    // See CustomTabs.SpareWebContentsStatus histogram. Append-only.
    @IntDef({WebContentsStatus.CREATED, WebContentsStatus.USED, WebContentsStatus.KILLED,
            WebContentsStatus.DESTROYED, WebContentsStatus.STOLEN})
    @Retention(RetentionPolicy.SOURCE)
    @interface WebContentsStatus {
        @VisibleForTesting
        int CREATED = 0;
        @VisibleForTesting
        int USED = 1;
        @VisibleForTesting
        int KILLED = 2;
        @VisibleForTesting
        int DESTROYED = 3;
        @VisibleForTesting
        int STOLEN = 4;
        int NUM_ENTRIES = 5;
    }

    /**
     * Observes spare WebContents deaths. In case of death, records stats, and cleanup the objects.
     */
    private class RenderProcessGoneObserver extends WebContentsObserver {
        @Override
        public void renderProcessGone(boolean wasOomProtected) {
            long elapsed = SystemClock.elapsedRealtime() - mWebContentsCreationTimeMs;
            RecordHistogram.recordLongTimesHistogram(
                    "CustomTabs.SpareWebContents.TimeBeforeDeath", elapsed);
            recordWebContentsStatus(WebContentsStatus.KILLED);
            destroySpareWebContentsInternal();
        }
    }

    @SuppressLint("StaticFieldLeak")
    private static WarmupManager sWarmupManager;

    private final Set<String> mDnsRequestsInFlight;
    private final Map<String, Profile> mPendingPreconnectWithProfile;

    private int mToolbarContainerId;
    private ViewGroup mMainView;
    @VisibleForTesting
    WebContents mSpareWebContents;
    private long mWebContentsCreationTimeMs;
    private RenderProcessGoneObserver mObserver;
<<<<<<< HEAD
    private boolean mIsCctPrewarmTabEnabled;

    // Stores a prebuilt tab. To load a URL, this can be used if available instead of creating one
    // from scratch.
    @VisibleForTesting Tab mSpareTab;

    /**
     * Represents various states of spareTab.
     *
     * These values are persisted to logs. Entries should not be renumbered and
     * numeric values should never be reused. See tools/metrics/histograms/enums.xml.
     */
    @IntDef({
        SpareTabFinalStatus.TAB_CREATED_BUT_NOT_USED,
        SpareTabFinalStatus.TAB_CREATION_IN_PROGRESS,
        SpareTabFinalStatus.TAB_USED,
        SpareTabFinalStatus.TAB_CRASHED,
        SpareTabFinalStatus.TAB_DESTROYED,
        SpareTabFinalStatus.NUM_ENTRIES
    })
    @Retention(RetentionPolicy.SOURCE)
    public @interface SpareTabFinalStatus {
        int TAB_CREATED_BUT_NOT_USED = 0;
        int TAB_CREATION_IN_PROGRESS = 1;
        int TAB_USED = 2;
        int TAB_CRASHED = 3;
        int TAB_DESTROYED = 4;
        int NUM_ENTRIES = 5;
    }

    @SpareTabFinalStatus int mSpareTabFinalStatus;

    /**
     * Records the spareTab final status.
     * @param status Status to be recorded in the enumerated histogram.
     */
    private void recordSpareTabFinalStatusHistogram(@SpareTabFinalStatus int status) {
        RecordHistogram.recordEnumeratedHistogram(
                "Android.SpareTab.FinalStatus", status, SpareTabFinalStatus.NUM_ENTRIES);
    }

    /** Destroys the spare Tab if there is one and sets mSpareTab to null. */
    public void destroySpareTab() {
        try (TraceEvent e = TraceEvent.scoped("WarmupManager.destroySpareTab")) {
            ThreadUtils.assertOnUiThread();

            mSpareTabFinalStatus = SpareTabFinalStatus.TAB_DESTROYED;
            destroySpareTabInternal(null);
        }
    }

    private void destroySpareTabInternal(Tab tab) {
        // Don't do anything if the spare tab doesn't exist.
        if (mSpareTab == null) return;

        if (tab != null && tab != mSpareTab) return;

        // Record the SpareTabFinalStatus once its destroyed.
        recordSpareTabFinalStatusHistogram(mSpareTabFinalStatus);

        mSpareTab.destroy();
        mSpareTab = null;
    }

    /**
     * Creates and initializes a Regular (non-Incognito) spare Tab, to be used for a subsequent
     * navigation.
     *
     * <p>This creates a WebContents and initializes renderer if SPARE_TAB_INITIALIZE_RENDERER is
     * true. Can be called multiple times, and must be called from the UI thread.
     *
     * <p>The tab's launch type will be set when the tab is used.
     */
    public void createRegularSpareTab(Profile profile) {
        createRegularSpareTab(profile, /* webContents= */ null);
    }

    /**
     * Creates and initializes a Regular (non-Incognito) spare Tab, to be used for a subsequent
     * navigation.
     *
     * <p>This creates a WebContents and initializes renderer if SPARE_TAB_INITIALIZE_RENDERER is
     * true. Can be called multiple times, and must be called from the UI thread.
     *
     * <p>The tab's launch type will be set when the tab is used.
     *
     * <p>* @param webContents The {@link WebContents} to use in the tab. If null the default is
     * used.
     */
    public void createRegularSpareTab(Profile profile, @Nullable WebContents webContents) {
        ThreadUtils.assertOnUiThread();
        assert !profile.isOffTheRecord();
        try (TraceEvent e = TraceEvent.scoped("WarmupManager.createSpareTab")) {
            mSpareTabFinalStatus = SpareTabFinalStatus.TAB_CREATION_IN_PROGRESS;

            // Ensure native is initialized before creating spareTab.
            assert LibraryLoader.getInstance().isInitialized();

            if (mSpareTab != null) return;

            // Build a spare detached tab.
            Tab spareTab = buildDetachedSpareTab(profile, webContents);

            mSpareTab = spareTab;
            assert mSpareTab != null : "Building a spare detached tab shouldn't return null.";

            mSpareTabFinalStatus = SpareTabFinalStatus.TAB_CREATED_BUT_NOT_USED;
        }

        if (mSpareTab != null) {
            mSpareTab.addObserver(new HiddenTabObserver(mSpareTab.getWindowAndroid()));
        }
    }

    /**
     * Creates an instance of a {@link Tab} that is fully detached from any activity.
     *
     * <p>Also performs general tab initialization as well as detached specifics.
     *
     * @param webContents The {@link WebContents} to use in the tab. If null the default is used.
     * @return The newly created and initialized spare tab.
     *     <p>TODO(crbug.com/40255340): Adapt this method to create other tabs.
     */
    private Tab buildDetachedSpareTab(Profile profile, @Nullable WebContents webContents) {
        Context context = ContextUtils.getApplicationContext();

        // These are effectively unused as they will be set when finishing reparenting.
        TabDelegateFactory delegateFactory = CustomTabDelegateFactory.createEmpty();
        WindowAndroid window = new WindowAndroid(context, /* trackOcclusion= */ false);

        // TODO(crbug.com/40174356): Set isIncognito flag here if spare tabs are allowed for
        // incognito mode.
        // Creates a tab with renderer initialized for spareTab. See https://crbug.com/1412572.
        Tab tab =
                TabBuilder.createLiveTab(profile, true)
                        .setWindow(window)
                        .setLaunchType(TabLaunchType.UNSET)
                        .setDelegateFactory(delegateFactory)
                        .setInitiallyHidden(true)
                        .setInitializeRenderer(true)
                        .setWebContents(webContents)
                        .build();

        // Resize the webContents to avoid expensive post load resize when attaching the tab.
        Rect bounds = TabUtils.estimateContentSize(context);
        int width = bounds.right - bounds.left;
        int height = bounds.bottom - bounds.top;
        tab.getWebContents().setSize(width, height);

        // Reparent the tab to detach it from the current activity.
        ReparentingTask.from(tab).detach();
        return tab;
    }

    /**
     * Returns the spare Tab. Must only be called when a spare tab is available for |profile|.
     *
     * @param profile the profile associated with the spare Tab.
     * @param type TabLaunchType of the requested tab.
     * @return the spare Tab.
     */
    public Tab takeSpareTab(Profile profile, boolean initiallyHidden, @TabLaunchType int type) {
        ThreadUtils.assertOnUiThread();
        try (TraceEvent e = TraceEvent.scoped("WarmupManager.takeSpareTab")) {
            if (mSpareTab.getProfile() != profile) {
                throw new RuntimeException("Attempted to take the tab from another profile.");
            }

            Tab spareTab = mSpareTab;
            mSpareTab = null;

            spareTab.setTabLaunchType(type);
            mSpareTabFinalStatus = SpareTabFinalStatus.TAB_USED;

            if (!initiallyHidden) {
                spareTab.getWebContents().updateWebContentsVisibility(Visibility.VISIBLE);
            }

            // Record the SpareTabFinalStatus once its used.
            recordSpareTabFinalStatusHistogram(mSpareTabFinalStatus);
            return spareTab;
        }
    }

    /**
     * @param targetsNetwork whether the activity/tab associated with this WebContents targets a
     *     network (supported only by multi-network CCT, see @{link
     *     BrowserServicesIntentDataProvider#getTargetNetwork).
     * @return Whether a spare tab is available for the given profile.
     */
    public boolean hasSpareTab(Profile profile, boolean targetsNetwork) {
        // Spare Tabs are not supported for multi-network CCT. In this case it's better to
        // always create Tabs from scratch, otherwise we might break the "WebContents
        // associated with a CCT tab targeting a network will always have
        // WebContents::GetTargetNetwork == that target network" invariant (see
        // WebContentsImpl::CreateWithOpener for more info).
        if (targetsNetwork) return false;
        if (mSpareTab == null) return false;
        return mSpareTab.getProfile() == profile;
    }

    /**
     * @param tab Tab to compare with SpareTab with.
     * @return Returns true if tab is same as spare tab.
     */
    public boolean isSpareTab(Tab tab) {
        if (mSpareTab == null) return false;

        assert mSpareTab.isHidden() : "Spare tab is not hidden";
        return mSpareTab == tab;
    }

    public static void deInitForTesting() {
        sWarmupManager = null;
    }

    /** Removes the singleton instance for the WarmupManager for testing. */
    public static void setInstanceForTesting(WarmupManager instance) {
        var oldValue = sWarmupManager;
        sWarmupManager = instance;
        ResettersForTesting.register(() -> sWarmupManager = oldValue);
    }
=======
    private boolean mWebContentsCreatedForCCT;
>>>>>>> chromium

    /**
     * @return The singleton instance for the WarmupManager, creating one if necessary.
     */
    public static WarmupManager getInstance() {
        ThreadUtils.assertOnUiThread();
        if (sWarmupManager == null) sWarmupManager = new WarmupManager();
        return sWarmupManager;
    }

    private WarmupManager() {
        mDnsRequestsInFlight = new HashSet<>();
        mPendingPreconnectWithProfile = new HashMap<>();
    }

    /**
     * Inflates and constructs the view hierarchy that the app will use.
     * @param baseContext The base context to use for creating the ContextWrapper.
     * @param toolbarContainerId Id of the toolbar container.
     * @param toolbarId The toolbar's layout ID.
     */
    public void initializeViewHierarchy(Context baseContext, int toolbarContainerId,
            int toolbarId) {
        ThreadUtils.assertOnUiThread();
        if (mMainView != null && mToolbarContainerId == toolbarContainerId) return;
        mMainView = inflateViewHierarchy(baseContext, toolbarContainerId, toolbarId);
        mToolbarContainerId = toolbarContainerId;
    }

<<<<<<< HEAD
    @VisibleForTesting
    static Context applyContextOverrides(Context baseContext) {
        // Scale up the UI for the base Context on automotive
        if (BuildInfo.getInstance().isAutomotive) {
            Configuration config = new Configuration();
            DisplayUtil.scaleUpConfigurationForAutomotive(baseContext, config);
            return baseContext.createConfigurationContext(config);
        }

        return baseContext;
    }

    static void applyThemeOverlays(Context context) {
        // TODO(twellington): Look at improving code sharing with ChromeBaseAppCompatActivity
        // if the number of these overlays grows. The two below are experimental / are planned to be
        // removed by mid 2025 or sooner.
        // TODO(https://crbug.com/392634251): Explore setting elegantTextHeight to 'true' on older
        // OS versions.
        if (ChromeFeatureList.sAndroidElegantTextHeight.isEnabled()
                && Build.VERSION.SDK_INT >= VERSION_CODES.TIRAMISU) {
            int elegantTextHeightOverlay = R.style.ThemeOverlay_BrowserUI_ElegantTextHeight;
            context.getTheme().applyStyle(elegantTextHeightOverlay, true);
        }

        if (Build.VERSION.SDK_INT >= VERSION_CODES.TIRAMISU) {
            context.getTheme()
                    .applyStyle(R.style.ThemeOverlay_BrowserUI_DefaultFontFamilyThemeOverlay, true);
        }
    }

=======
>>>>>>> chromium
    /**
     * Inflates and constructs the view hierarchy that the app will use.
     * Calls to this are not restricted to the UI thread.
     * @param baseContext The base context to use for creating the ContextWrapper.
     * @param toolbarContainerId Id of the toolbar container.
     * @param toolbarId The toolbar's layout ID.
     */
    public static ViewGroup inflateViewHierarchy(
            Context baseContext, int toolbarContainerId, int toolbarId) {
        try (TraceEvent e = TraceEvent.scoped("WarmupManager.inflateViewHierarchy")) {
            ContextThemeWrapper context =
                    new ContextThemeWrapper(baseContext, ActivityUtils.getThemeId());
            FrameLayout contentHolder = new FrameLayout(context);
            ViewGroup mainView =
                    (ViewGroup) LayoutInflaterUtils.inflate(context, R.layout.main, contentHolder);
            if (toolbarContainerId != ActivityUtils.NO_RESOURCE_ID) {
                ViewStub stub = (ViewStub) mainView.findViewById(R.id.control_container_stub);
                stub.setLayoutResource(toolbarContainerId);
                stub.inflate();
            }
            // It cannot be assumed that the result of toolbarContainerStub.inflate() will be
            // the control container since it may be wrapped in another view.
            ControlContainer controlContainer =
                    (ControlContainer) mainView.findViewById(R.id.control_container);

            if (toolbarId != ActivityUtils.NO_RESOURCE_ID && controlContainer != null) {
                controlContainer.initWithToolbar(toolbarId);
            }
            return mainView;
        } catch (InflateException e) {
            // See https://crbug.com/606715.
            Log.e(TAG, "Inflation exception.", e);
            return null;
        }
    }

    /**
     * Transfers all the children in the local view hierarchy {@link #mMainView} to the given
     * ViewGroup {@param contentView} as child.
     * @param contentView The parent ViewGroup to use for the transfer.
     */
    public void transferViewHierarchyTo(ViewGroup contentView) {
        ThreadUtils.assertOnUiThread();
        ViewGroup viewHierarchy = mMainView;
        mMainView = null;
        if (viewHierarchy == null) return;
        transferViewHeirarchy(viewHierarchy, contentView);
    }

    /**
     * Transfers all the children in one view hierarchy {@param from} to another {@param to}.
     * @param from The parent ViewGroup to transfer children from.
     * @param to The parent ViewGroup to transfer children to.
     */
    public static void transferViewHeirarchy(ViewGroup from, ViewGroup to) {
        while (from.getChildCount() > 0) {
            View currentChild = from.getChildAt(0);
            from.removeView(currentChild);
            to.addView(currentChild);
        }
    }

    /**
     * @return Whether a pre-built view hierarchy exists for the given toolbarContainerId.
     */
    public boolean hasViewHierarchyWithToolbar(int toolbarContainerId) {
        ThreadUtils.assertOnUiThread();
        return mMainView != null && mToolbarContainerId == toolbarContainerId;
    }

    /**
     * Clears the inflated view hierarchy.
     */
    public void clearViewHierarchy() {
        ThreadUtils.assertOnUiThread();
        mMainView = null;
    }

    /**
     * Launches a background DNS query for a given URL.
     *
     * @param url URL from which the domain to query is extracted.
     */
    private void prefetchDnsForUrlInBackground(final String url) {
        mDnsRequestsInFlight.add(url);
        new AsyncTask<Void>() {
            @Override
            protected Void doInBackground() {
                try (TraceEvent e =
                                TraceEvent.scoped("WarmupManager.prefetchDnsForUrlInBackground")) {
                    InetAddress.getByName(new URL(url).getHost());
                } catch (MalformedURLException e) {
                    // We don't do anything with the result of the request, it
                    // is only here to warm up the cache, thus ignoring the
                    // exception is fine.
                } catch (UnknownHostException e) {
                    // As above.
                }
                return null;
            }

            @Override
            protected void onPostExecute(Void result) {
                mDnsRequestsInFlight.remove(url);
                if (mPendingPreconnectWithProfile.containsKey(url)) {
                    Profile profile = mPendingPreconnectWithProfile.get(url);
                    mPendingPreconnectWithProfile.remove(url);
                    maybePreconnectUrlAndSubResources(profile, url);
                }
            }
        }
                .executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
    }

    /** Launches a background DNS query for a given URL.
     *
     * @param context The Application context.
     * @param url URL from which the domain to query is extracted.
     */
    public void maybePrefetchDnsForUrlInBackground(Context context, String url) {
        ThreadUtils.assertOnUiThread();
            prefetchDnsForUrlInBackground(url);
    }

    /**
     * Starts asynchronous initialization of the preconnect predictor.
     *
     * Without this call, |maybePreconnectUrlAndSubresources()| will not use a database of origins
     * to connect to, unless the predictor has already been initialized in another way.
     *
     * @param profile The profile to use for the predictor.
     */
    public static void startPreconnectPredictorInitialization(Profile profile) {
        ThreadUtils.assertOnUiThread();
        WarmupManagerJni.get().startPreconnectPredictorInitialization(profile);
    }

    /** Asynchronously preconnects to a given URL if the data reduction proxy is not in use.
     *
     * @param profile The profile to use for the preconnection.
     * @param url The URL we want to preconnect to.
     */
    public void maybePreconnectUrlAndSubResources(Profile profile, String url) {
        ThreadUtils.assertOnUiThread();

        Uri uri = Uri.parse(url);
        if (uri == null) return;
        String scheme = uri.normalizeScheme().getScheme();
        if (!UrlConstants.HTTP_SCHEME.equals(scheme) && !UrlConstants.HTTPS_SCHEME.equals(scheme)) {
            return;
        }

        // If there is already a DNS request in flight for this URL, then the preconnection will
        // start by issuing a DNS request for the same domain, as the result is not cached. However,
        // such a DNS request has already been sent from this class, so it is better to wait for the
        // answer to come back before preconnecting. Otherwise, the preconnection logic will wait
        // for the result of the second DNS request, which should arrive after the result of the
        // first one. Note that we however need to wait for the main thread to be available in this
        // case, since the preconnection will be sent from AsyncTask.onPostExecute(), which may
        // delay it.
        if (mDnsRequestsInFlight.contains(url)) {
            // Note that if two requests come for the same URL with two different profiles, the last
            // one will win.
            mPendingPreconnectWithProfile.put(url, profile);
        } else {
            WarmupManagerJni.get().preconnectUrlAndSubresources(profile, url);
        }
    }

    /**
     * Creates and initializes a spare WebContents, to be used in a subsequent navigation.
     *
     * This creates a renderer that is suitable for any navigation. It can be picked up by any tab.
     * Can be called multiple times, and must be called from the UI thread.
     *
     * @param forCCT Whether this WebContents is being created for CCT.
     */
    public void createSpareWebContents(boolean forCCT) {
        ThreadUtils.assertOnUiThread();
        if (!LibraryLoader.getInstance().isInitialized() || mSpareWebContents != null) return;

<<<<<<< HEAD
            mSpareWebContents =
                    WebContentsFactory.createWebContentsWithWarmRenderer(
                            profile,
                            /* initiallyHidden= */ true,
                            /* targetNetwork= */ NetId.INVALID);
            mObserver = new RenderProcessGoneObserver();
            mObserver.observe(mSpareWebContents);
        }
=======
        mWebContentsCreatedForCCT = forCCT;
        mSpareWebContents = new WebContentsFactory().createWebContentsWithWarmRenderer(
                Profile.getLastUsedRegularProfile(), true /* initiallyHidden */);
        mObserver = new RenderProcessGoneObserver();
        mSpareWebContents.addObserver(mObserver);
        mWebContentsCreationTimeMs = SystemClock.elapsedRealtime();
        recordWebContentsStatus(WebContentsStatus.CREATED);
>>>>>>> chromium
    }

    /**
     * Destroys the spare WebContents if there is one.
     */
    public void destroySpareWebContents() {
        ThreadUtils.assertOnUiThread();
        if (mSpareWebContents == null) return;
        recordWebContentsStatus(WebContentsStatus.DESTROYED);
        destroySpareWebContentsInternal();
    }

    /**
     * Returns a spare WebContents or null, depending on the availability of one.
     *
     * The parameters are the same as for {@link WebContentsFactory#createWebContents()}.
     * @param forCCT Whether this WebContents is being taken by CCT.
     *
     * @return a WebContents, or null.
     */
    public WebContents takeSpareWebContents(
<<<<<<< HEAD
            boolean incognito, boolean initiallyHidden, boolean targetsNetwork) {
        try (TraceEvent e = TraceEvent.scoped("WarmupManager.takeSpareWebContents")) {
            ThreadUtils.assertOnUiThread();
            if (incognito) return null;
            // Spare WebContents are not supported for multi-network CCT. In this case it's better
            // to always create WebContents from scratch, otherwise we might break the "WebContents
            // associated with a CCT tab targeting a network will always have
            // WebContents::GetTargetNetwork == that target network" invariant (see
            // WebContentsImpl::CreateWithOpener for more info).
            if (targetsNetwork) return null;
            WebContents result = mSpareWebContents;
            if (result == null) return null;
            mSpareWebContents = null;
            mObserver.observe(null);
            mObserver = null;
            if (!initiallyHidden) result.updateWebContentsVisibility(Visibility.VISIBLE);
            return result;
        }
=======
            boolean incognito, boolean initiallyHidden, boolean forCCT) {
        ThreadUtils.assertOnUiThread();
        if (incognito) return null;
        WebContents result = mSpareWebContents;
        if (result == null) return null;
        mSpareWebContents = null;
        result.removeObserver(mObserver);
        mObserver = null;
        if (!initiallyHidden) result.onShow();
        recordWebContentsStatus(mWebContentsCreatedForCCT == forCCT ? WebContentsStatus.USED
                                                                    : WebContentsStatus.STOLEN);
        return result;
>>>>>>> chromium
    }

    /**
     * @return Whether a spare renderer is available.
     */
    public boolean hasSpareWebContents() {
        return mSpareWebContents != null;
    }

    private void destroySpareWebContentsInternal() {
        mObserver.observe(null);
        mSpareWebContents.destroy();
        mSpareWebContents = null;
        mObserver = null;
    }

    private void recordWebContentsStatus(@WebContentsStatus int status) {
        if (!mWebContentsCreatedForCCT) return;
        RecordHistogram.recordEnumeratedHistogram(
                WEBCONTENTS_STATUS_HISTOGRAM, status, WebContentsStatus.NUM_ENTRIES);
    }

    @NativeMethods
    interface Natives {
        void startPreconnectPredictorInitialization(Profile profile);
        void preconnectUrlAndSubresources(Profile profile, String url);
    }
}
