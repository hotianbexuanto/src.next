// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tabbed_mode;

<<<<<<< HEAD
import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Bitmap;
import android.os.Build.VERSION;
import android.os.Build.VERSION_CODES;
import android.os.Bundle;
import android.view.View;
=======
>>>>>>> chromium
import android.view.ViewGroup;
import android.view.ViewStub;

import androidx.annotation.ColorInt;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import org.chromium.base.ApiCompatibilityUtils;
import org.chromium.base.Callback;
import org.chromium.base.CommandLine;
import org.chromium.base.TraceEvent;
import org.chromium.base.jank_tracker.JankTracker;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.base.supplier.Supplier;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.ActivityTabProvider;
import org.chromium.chrome.browser.ActivityTabProvider.ActivityTabTabObserver;
import org.chromium.chrome.browser.ApplicationLifetime;
import org.chromium.chrome.browser.SwipeRefreshHandler;
<<<<<<< HEAD
import org.chromium.chrome.browser.accessibility.PageZoomIphController;
import org.chromium.chrome.browser.back_press.BackPressManager;
import org.chromium.chrome.browser.bookmarks.BookmarkModel;
import org.chromium.chrome.browser.bookmarks.TabBookmarker;
import org.chromium.chrome.browser.bookmarks.bar.BookmarkBarCoordinator;
import org.chromium.chrome.browser.browser_controls.BrowserControlsSizer;
import org.chromium.chrome.browser.browser_controls.BrowserControlsStateProvider.ControlsPosition;
import org.chromium.chrome.browser.collaboration.CollaborationControllerDelegateFactory;
import org.chromium.chrome.browser.collaboration.CollaborationControllerDelegateImpl;
import org.chromium.chrome.browser.collaboration.CollaborationServiceFactory;
import org.chromium.chrome.browser.collaboration.messaging.MessagingBackendServiceFactory;
=======
import org.chromium.chrome.browser.app.ChromeActivity;
import org.chromium.chrome.browser.banners.AppBannerInProductHelpController;
import org.chromium.chrome.browser.banners.AppBannerInProductHelpControllerFactory;
import org.chromium.chrome.browser.bookmarks.BookmarkBridge;
import org.chromium.chrome.browser.browser_controls.BrowserControlsSizer;
>>>>>>> chromium
import org.chromium.chrome.browser.compositor.CompositorViewHolder;
import org.chromium.chrome.browser.compositor.bottombar.ephemeraltab.EphemeralTabCoordinator;
import org.chromium.chrome.browser.compositor.layouts.LayoutManagerImpl;
<<<<<<< HEAD
import org.chromium.chrome.browser.crash.ChromePureJavaExceptionReporter;
import org.chromium.chrome.browser.customtabs.CustomTabActivity;
import org.chromium.chrome.browser.data_sharing.DataSharingNotificationManager;
import org.chromium.chrome.browser.data_sharing.DataSharingServiceFactory;
import org.chromium.chrome.browser.data_sharing.DataSharingTabGroupsDelegate;
import org.chromium.chrome.browser.data_sharing.DataSharingTabManager;
import org.chromium.chrome.browser.data_sharing.InstantMessageDelegateFactory;
import org.chromium.chrome.browser.data_sharing.InstantMessageDelegateImpl;
import org.chromium.chrome.browser.desktop_site.DesktopSiteSettingsIphController;
import org.chromium.chrome.browser.dragdrop.ChromeTabbedOnDragListener;
import org.chromium.chrome.browser.ephemeraltab.EphemeralTabCoordinator;
import org.chromium.chrome.browser.feature_engagement.TrackerFactory;
import org.chromium.chrome.browser.feed.webfeed.WebFeedBridge;
=======
import org.chromium.chrome.browser.compositor.layouts.OverviewModeBehavior;
import org.chromium.chrome.browser.contextualsearch.ContextualSearchManager;
import org.chromium.chrome.browser.continuous_search.ContinuousSearchContainerCoordinator;
import org.chromium.chrome.browser.continuous_search.ContinuousSearchContainerCoordinator.HeightObserver;
import org.chromium.chrome.browser.datareduction.DataReductionPromoScreen;
import org.chromium.chrome.browser.feed.shared.FeedFeatures;
>>>>>>> chromium
import org.chromium.chrome.browser.feed.webfeed.WebFeedFollowIntroController;
import org.chromium.chrome.browser.findinpage.FindToolbarObserver;
import org.chromium.chrome.browser.firstrun.FirstRunStatus;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.flags.ChromeSwitches;
import org.chromium.chrome.browser.fullscreen.BrowserControlsManager;
import org.chromium.chrome.browser.gesturenav.BackActionDelegate;
import org.chromium.chrome.browser.gesturenav.HistoryNavigationCoordinator;
import org.chromium.chrome.browser.gesturenav.NavigationSheet;
import org.chromium.chrome.browser.gesturenav.TabbedSheetDelegate;
import org.chromium.chrome.browser.history.HistoryManagerUtils;
import org.chromium.chrome.browser.language.AppLanguagePromoDialog;
import org.chromium.chrome.browser.language.LanguageAskPrompt;
import org.chromium.chrome.browser.layouts.LayoutStateProvider;
import org.chromium.chrome.browser.locale.LocaleManager;
import org.chromium.chrome.browser.merchant_viewer.MerchantTrustMetrics;
import org.chromium.chrome.browser.merchant_viewer.MerchantTrustSignalsCoordinator;
import org.chromium.chrome.browser.multiwindow.MultiWindowUtils;
import org.chromium.chrome.browser.ntp.NewTabPageLaunchOrigin;
import org.chromium.chrome.browser.ntp.NewTabPageUtils;
import org.chromium.chrome.browser.offlinepages.indicator.OfflineIndicatorControllerV2;
import org.chromium.chrome.browser.offlinepages.indicator.OfflineIndicatorInProductHelpController;
import org.chromium.chrome.browser.omnibox.UrlFocusChangeListener;
import org.chromium.chrome.browser.preferences.ChromePreferenceKeys;
import org.chromium.chrome.browser.preferences.SharedPreferencesManager;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.read_later.ReadLaterIPHController;
import org.chromium.chrome.browser.share.ShareDelegate;
import org.chromium.chrome.browser.signin.SyncConsentActivityLauncherImpl;
import org.chromium.chrome.browser.signin.ui.SigninPromoUtil;
import org.chromium.chrome.browser.status_indicator.StatusIndicatorCoordinator;
import org.chromium.chrome.browser.subscriptions.CommerceSubscriptionsService;
import org.chromium.chrome.browser.subscriptions.CommerceSubscriptionsServiceFactory;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabAssociatedApp;
import org.chromium.chrome.browser.tab.TabLaunchType;
<<<<<<< HEAD
import org.chromium.chrome.browser.tab_group_sync.TabGroupSyncControllerImpl;
import org.chromium.chrome.browser.tab_group_sync.TabGroupSyncFeatures;
import org.chromium.chrome.browser.tab_group_sync.TabGroupSyncServiceFactory;
import org.chromium.chrome.browser.tab_ui.TabContentManager;
import org.chromium.chrome.browser.tab_ui.TabSwitcher;
import org.chromium.chrome.browser.tabmodel.TabClosureParams;
import org.chromium.chrome.browser.tabmodel.TabCreatorManager;
import org.chromium.chrome.browser.tabmodel.TabGroupModelFilter;
=======
>>>>>>> chromium
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tasks.tab_management.PriceTrackingUtilities;
import org.chromium.chrome.browser.tasks.tab_management.TabUiFeatureUtilities;
import org.chromium.chrome.browser.toolbar.ToolbarButtonInProductHelpController;
import org.chromium.chrome.browser.toolbar.ToolbarIntentMetadata;
import org.chromium.chrome.browser.ui.RootUiCoordinator;
import org.chromium.chrome.browser.ui.TabObscuringHandler;
import org.chromium.chrome.browser.ui.appmenu.AppMenuHandler;
import org.chromium.chrome.browser.ui.default_browser_promo.DefaultBrowserPromoUtils;
import org.chromium.chrome.browser.ui.tablet.emptybackground.EmptyBackgroundViewWrapper;
import org.chromium.chrome.browser.version.ChromeVersionInfo;
import org.chromium.chrome.browser.vr.VrModuleProvider;
import org.chromium.chrome.browser.webapps.AddToHomescreenIPHController;
import org.chromium.chrome.browser.webapps.AddToHomescreenMostVisitedTileClickObserver;
import org.chromium.chrome.browser.webapps.PwaBottomSheetController;
import org.chromium.chrome.browser.webapps.PwaBottomSheetControllerFactory;
import org.chromium.chrome.features.start_surface.StartSurface;
import org.chromium.chrome.features.start_surface.StartSurfaceState;
import org.chromium.components.browser_ui.bottomsheet.EmptyBottomSheetObserver;
<<<<<<< HEAD
import org.chromium.components.browser_ui.desktop_windowing.DesktopWindowStateManager;
import org.chromium.components.browser_ui.edge_to_edge.EdgeToEdgeManager;
import org.chromium.components.browser_ui.edge_to_edge.EdgeToEdgeStateProvider;
import org.chromium.components.browser_ui.edge_to_edge.SystemBarColorHelper;
import org.chromium.components.browser_ui.widget.CoordinatorLayoutForPointer;
import org.chromium.components.browser_ui.widget.MenuOrKeyboardActionController;
import org.chromium.components.browser_ui.widget.TouchEventObserver;
import org.chromium.components.browser_ui.widget.scrim.ScrimManager;
import org.chromium.components.collaboration.CollaborationService;
import org.chromium.components.collaboration.ServiceStatus;
import org.chromium.components.feature_engagement.FeatureConstants;
import org.chromium.components.search_engines.SearchEnginesFeatures;
import org.chromium.components.tab_group_sync.TabGroupSyncController;
import org.chromium.components.tab_group_sync.TabGroupUiActionHandler;
import org.chromium.components.user_prefs.UserPrefs;
import org.chromium.components.webapps.bottomsheet.PwaBottomSheetController;
import org.chromium.components.webapps.bottomsheet.PwaBottomSheetControllerFactory;
import org.chromium.ui.InsetObserver;
import org.chromium.ui.UiUtils;
import org.chromium.ui.base.ActivityWindowAndroid;
import org.chromium.ui.base.DeviceFormFactor;
import org.chromium.ui.base.IntentRequestTracker;
import org.chromium.ui.base.LocalizationUtils;
import org.chromium.ui.dragdrop.DragDropGlobalState;
import org.chromium.ui.modaldialog.ModalDialogManager;
import org.chromium.url.GURL;
=======
import org.chromium.components.browser_ui.util.ComposedBrowserControlsVisibilityDelegate;
import org.chromium.components.browser_ui.widget.TouchEventObserver;
import org.chromium.components.browser_ui.widget.scrim.ScrimCoordinator;
import org.chromium.components.messages.MessageDispatcherProvider;
import org.chromium.ui.base.ActivityWindowAndroid;
import org.chromium.ui.base.DeviceFormFactor;
import org.chromium.ui.util.TokenHolder;
>>>>>>> chromium

/**
 * A {@link RootUiCoordinator} variant that controls tabbed-mode specific UI.
 */
public class TabbedRootUiCoordinator extends RootUiCoordinator {
    private static boolean sEnableStatusIndicatorForTests;

    private final ObservableSupplierImpl<EphemeralTabCoordinator> mEphemeralTabCoordinatorSupplier;
    private final RootUiTabObserver mRootUiTabObserver;
    private TabbedSystemUiCoordinator mSystemUiCoordinator;
    private @Nullable EmptyBackgroundViewWrapper mEmptyBackgroundViewWrapper;

    private StatusIndicatorCoordinator mStatusIndicatorCoordinator;
    private StatusIndicatorCoordinator.StatusIndicatorObserver mStatusIndicatorObserver;
    private OfflineIndicatorControllerV2 mOfflineIndicatorController;
    private OfflineIndicatorInProductHelpController mOfflineIndicatorInProductHelpController;
    private ReadLaterIPHController mReadLaterIPHController;
    private WebFeedFollowIntroController mWebFeedFollowIntroController;
    private UrlFocusChangeListener mUrlFocusChangeListener;
    private @Nullable ToolbarButtonInProductHelpController mToolbarButtonInProductHelpController;
    private AddToHomescreenIPHController mAddToHomescreenIPHController;
    private AddToHomescreenMostVisitedTileClickObserver mAddToHomescreenMostVisitedTileObserver;
    private AppBannerInProductHelpController mAppBannerInProductHelpController;
    private PwaBottomSheetController mPwaBottomSheetController;
    private HistoryNavigationCoordinator mHistoryNavigationCoordinator;
    private NavigationSheet mNavigationSheet;
    private ComposedBrowserControlsVisibilityDelegate mAppBrowserControlsVisibilityDelegate;
    private LayoutManagerImpl mLayoutManager;
    private ContinuousSearchContainerCoordinator mContinuousSearchContainerCoordinator;
    private HeightObserver mContinuousSearchObserver;
    private TabObscuringHandler.Observer mContinuousSearchTabObscuringHandlerObserver;
    private FindToolbarObserver mContinuousSearchFindToolbarObserver;
    private MerchantTrustSignalsCoordinator mMerchantTrustSignalsCoordinator;
    private CommerceSubscriptionsService mCommerceSubscriptionsService;

    private int mStatusIndicatorHeight;
<<<<<<< HEAD
    private final OneshotSupplier<HubManager> mHubManagerSupplier;
    private TouchEventObserver mDragDropTouchObserver;
    private ViewGroup mCoordinator;
    private final ObservableSupplier<EdgeToEdgeController> mEdgeToEdgeControllerSupplier;
    private final OneshotSupplierImpl<SystemBarColorHelper> mSystemBarColorHelperSupplier;
    private @Nullable AppHeaderCoordinator mAppHeaderCoordinator;
    private final ManualFillingComponentSupplier mManualFillingComponentSupplier;
    private final @NonNull DataSharingTabManager mDataSharingTabManager;
    private final Supplier<Boolean> mCanAnimateBrowserControls;
    private final EdgeToEdgeManager mEdgeToEdgeManager;
    protected @Nullable InstantMessageDelegateImpl mInstantMessageDelegateImpl;
    private @Nullable BookmarkBarCoordinator mBookmarkBarCoordinator;
=======
    private int mContinuousSearchHeight;
>>>>>>> chromium

    // Activity tab observer that updates the current tab used by various UI components.
    private class RootUiTabObserver extends ActivityTabTabObserver {
        private Tab mTab;

        private RootUiTabObserver(ActivityTabProvider activityTabProvider) {
            super(activityTabProvider);
        }

        @Override
        public void onObservingDifferentTab(Tab tab, boolean hint) {
            swapToTab(tab);
        }

        private void swapToTab(Tab tab) {
            if (mTab != null && !mTab.isDestroyed()) {
                SwipeRefreshHandler.from(mTab).setNavigationCoordinator(null);
            }
            mTab = tab;

            if (tab != null) {
                SwipeRefreshHandler.from(tab).setNavigationCoordinator(
                        mHistoryNavigationCoordinator);
            }
        }

        @Override
        public void destroy() {
            super.destroy();
            swapToTab(null);
        }
    }

    /**
     * Construct a new TabbedRootUiCoordinator.
     * @param activity The activity whose UI the coordinator is responsible for.
     * @param onOmniboxFocusChangedListener callback to invoke when Omnibox focus
     *         changes.
     * @param intentMetadataOneshotSupplier Supplier with information about the launching intent.
     * @param shareDelegateSupplier
     * @param tabProvider The {@link ActivityTabProvider} to get current tab of the activity.
     * @param profileSupplier Supplier of the currently applicable profile.
     * @param bookmarkBridgeSupplier Supplier of the bookmark bridge for the current profile.
     * @param overviewModeBehaviorSupplier Supplier of the overview mode manager.
     * @param contextualSearchManagerSupplier Supplier of the {@link ContextualSearchManager}.
     * @param startSurfaceSupplier Supplier of the {@link StartSurface}.
     * @param layoutStateProviderOneshotSupplier Supplier of the {@link LayoutStateProvider}.
     * @param startSurfaceParentTabSupplier Supplies the parent tab for the StartSurface.
     * @param browserControlsManager Manages the browser controls.
     * @param windowAndroid The current {@link WindowAndroid}.
<<<<<<< HEAD
     * @param activityLifecycleDispatcher Allows observation of the activity lifecycle.
     * @param layoutManagerSupplier Supplies the {@link LayoutManager}.
     * @param menuOrKeyboardActionController Controls the menu or keyboard action controller.
     * @param activityThemeColorSupplier Supplies the activity color theme.
     * @param modalDialogManagerSupplier Supplies the {@link ModalDialogManager}.
     * @param appMenuBlocker Controls the app menu blocking.
     * @param supportsAppMenuSupplier Supplies the support state for the app menu.
     * @param supportsFindInPage Supplies the support state for find in page.
     * @param tabCreatorManagerSupplier Supplies the {@link TabCreatorManager}.
     * @param fullscreenManager Manages the fullscreen state.
     * @param compositorViewHolderSupplier Supplies the {@link CompositorViewHolder}.
     * @param tabContentManagerSupplier Supplies the {@link TabContentManager}.
     * @param snackbarManagerSupplier Supplies the {@link SnackbarManager}.
     * @param edgeToEdgeSupplier Supplies the {@link EdgeToEdgeController}.
     * @param systemBarColorHelperSupplier Supplies the {@link SystemBarColorHelper} for the
     *     edge-to-edge bottom chin.
     * @param activityType The {@link ActivityType} for the activity.
     * @param isInOverviewModeSupplier Supplies whether the app is in overview mode.
     * @param appMenuDelegate The app menu delegate.
     * @param statusBarColorProvider Provides the status bar color.
     * @param ephemeralTabCoordinatorSupplier Supplies the {@link EphemeralTabCoordinator}.
     * @param intentRequestTracker Tracks intent requests.
     * @param insetObserver The {@link InsetObserver}.
     * @param backButtonShouldCloseTabFn Function which supplies whether or not the back button
     *     should close the tab.
     * @param sendToBackground Callback exiting the app and closing the tab.
     * @param initializeUiWithIncognitoColors Whether to initialize the UI with incognito colors.
     * @param backPressManager The {@link BackPressManager} handling back press.
     * @param savedInstanceState The saved bundle for the last recorded state.
     * @param multiInstanceManager Manages multi-instance mode.
     * @param overviewColorSupplier Notifies when the overview color changes.
     * @param baseChromeLayout The base view hosting Chrome that certain views (e.g. the omnibox
     *     suggestion list) will position themselves relative to. If null, the content view will be
     *     used.
     * @param manualFillingComponentSupplier Supplies the {@link ManualFillingComponent} for
     *     interacting with non-popup filling UI.
     * @param edgeToEdgeManager Manages core edge-to-edge state and logic.
     */
    public TabbedRootUiCoordinator(
            @NonNull AppCompatActivity activity,
            @Nullable Callback<Boolean> onOmniboxFocusChangedListener,
            @NonNull ObservableSupplier<ShareDelegate> shareDelegateSupplier,
            @NonNull ActivityTabProvider tabProvider,
            @NonNull ObservableSupplier<Profile> profileSupplier,
            @NonNull ObservableSupplier<BookmarkModel> bookmarkModelSupplier,
            @NonNull ObservableSupplier<TabBookmarker> tabBookmarkerSupplier,
            @NonNull ObservableSupplier<TabModelSelector> tabModelSelectorSupplier,
            @NonNull OneshotSupplier<TabSwitcher> tabSwitcherSupplier,
            @NonNull OneshotSupplier<TabSwitcher> incognitoTabSwitcherSupplier,
            @NonNull OneshotSupplier<HubManager> hubManagerSupplier,
            @NonNull OneshotSupplier<ToolbarIntentMetadata> intentMetadataOneshotSupplier,
            @NonNull OneshotSupplier<LayoutStateProvider> layoutStateProviderOneshotSupplier,
            @NonNull BrowserControlsManager browserControlsManager,
            @NonNull ActivityWindowAndroid windowAndroid,
            @NonNull ActivityLifecycleDispatcher activityLifecycleDispatcher,
            @NonNull ObservableSupplier<LayoutManagerImpl> layoutManagerSupplier,
            @NonNull MenuOrKeyboardActionController menuOrKeyboardActionController,
            @NonNull Supplier<Integer> activityThemeColorSupplier,
            @NonNull ObservableSupplier<ModalDialogManager> modalDialogManagerSupplier,
            @NonNull AppMenuBlocker appMenuBlocker,
            @NonNull BooleanSupplier supportsAppMenuSupplier,
            @NonNull BooleanSupplier supportsFindInPage,
            @NonNull Supplier<TabCreatorManager> tabCreatorManagerSupplier,
            @NonNull FullscreenManager fullscreenManager,
            @NonNull Supplier<CompositorViewHolder> compositorViewHolderSupplier,
            @NonNull Supplier<TabContentManager> tabContentManagerSupplier,
            @NonNull Supplier<SnackbarManager> snackbarManagerSupplier,
            @NonNull ObservableSupplierImpl<EdgeToEdgeController> edgeToEdgeSupplier,
            @NonNull OneshotSupplierImpl<SystemBarColorHelper> systemBarColorHelperSupplier,
            @ActivityType int activityType,
            @NonNull Supplier<Boolean> isInOverviewModeSupplier,
            @NonNull AppMenuDelegate appMenuDelegate,
            @NonNull StatusBarColorProvider statusBarColorProvider,
            @NonNull OneshotSupplierImpl<EphemeralTabCoordinator> ephemeralTabCoordinatorSupplier,
            @NonNull IntentRequestTracker intentRequestTracker,
            @NonNull InsetObserver insetObserver,
            @NonNull Function<Tab, Boolean> backButtonShouldCloseTabFn,
            @NonNull Callback<Tab> sendToBackground,
            boolean initializeUiWithIncognitoColors,
            @NonNull BackPressManager backPressManager,
            @Nullable Bundle savedInstanceState,
            @Nullable MultiInstanceManager multiInstanceManager,
            @NonNull ObservableSupplier<Integer> overviewColorSupplier,
            @Nullable View baseChromeLayout,
            @NonNull ManualFillingComponentSupplier manualFillingComponentSupplier,
            @NonNull EdgeToEdgeManager edgeToEdgeManager) {
        super(
                activity,
                onOmniboxFocusChangedListener,
                shareDelegateSupplier,
                tabProvider,
                profileSupplier,
                bookmarkModelSupplier,
                tabBookmarkerSupplier,
                tabModelSelectorSupplier,
                tabSwitcherSupplier,
                incognitoTabSwitcherSupplier,
                intentMetadataOneshotSupplier,
                layoutStateProviderOneshotSupplier,
                browserControlsManager,
                windowAndroid,
                activityLifecycleDispatcher,
                layoutManagerSupplier,
                menuOrKeyboardActionController,
                activityThemeColorSupplier,
                modalDialogManagerSupplier,
                appMenuBlocker,
                supportsAppMenuSupplier,
                supportsFindInPage,
                tabCreatorManagerSupplier,
                fullscreenManager,
                compositorViewHolderSupplier,
                tabContentManagerSupplier,
                snackbarManagerSupplier,
                edgeToEdgeSupplier,
                activityType,
                isInOverviewModeSupplier,
                appMenuDelegate,
                statusBarColorProvider,
                intentRequestTracker,
                ephemeralTabCoordinatorSupplier,
                initializeUiWithIncognitoColors,
                backPressManager,
                savedInstanceState,
                overviewColorSupplier,
                baseChromeLayout,
                edgeToEdgeManager);
        mInsetObserver = insetObserver;
        mBackButtonShouldCloseTabFn = backButtonShouldCloseTabFn;
        mSendToBackground = sendToBackground;
=======
     */
    public TabbedRootUiCoordinator(ChromeActivity activity,
            Callback<Boolean> onOmniboxFocusChangedListener,
            OneshotSupplier<ToolbarIntentMetadata> intentMetadataOneshotSupplier,
            ObservableSupplier<ShareDelegate> shareDelegateSupplier,
            ActivityTabProvider tabProvider,
            ObservableSupplierImpl<EphemeralTabCoordinator> ephemeralTabCoordinatorSupplier,
            ObservableSupplier<Profile> profileSupplier,
            ObservableSupplier<BookmarkBridge> bookmarkBridgeSupplier,
            OneshotSupplier<OverviewModeBehavior> overviewModeBehaviorSupplier,
            Supplier<ContextualSearchManager> contextualSearchManagerSupplier,
            ObservableSupplier<TabModelSelector> tabModelSelectorSupplier,
            OneshotSupplier<StartSurface> startSurfaceSupplier,
            OneshotSupplier<LayoutStateProvider> layoutStateProviderOneshotSupplier,
            Supplier<Tab> startSurfaceParentTabSupplier,
            @NonNull BrowserControlsManager browserControlsManager,
            ActivityWindowAndroid windowAndroid, JankTracker jankTracker) {
        super(activity, onOmniboxFocusChangedListener, shareDelegateSupplier, tabProvider,
                profileSupplier, bookmarkBridgeSupplier, contextualSearchManagerSupplier,
                tabModelSelectorSupplier, startSurfaceSupplier, intentMetadataOneshotSupplier,
                layoutStateProviderOneshotSupplier, startSurfaceParentTabSupplier,
                browserControlsManager, windowAndroid, jankTracker);
>>>>>>> chromium
        mEphemeralTabCoordinatorSupplier = ephemeralTabCoordinatorSupplier;
        mCanAnimateBrowserControls = () -> {
            // These null checks prevent any exceptions that may be caused by callbacks after
            // destruction.
            if (mActivity == null || mActivity.getActivityTabProvider() == null) return false;
            final Tab tab = mActivity.getActivityTabProvider().get();
            return tab != null && tab.isUserInteractable() && !tab.isNativePage();
        };

        getAppBrowserControlsVisibilityDelegate().addDelegate(
                browserControlsManager.getBrowserVisibilityDelegate());
        mRootUiTabObserver = new RootUiTabObserver(tabProvider);
<<<<<<< HEAD
        mGestureNavLayoutObserver =
                new LayoutStateProvider.LayoutStateObserver() {
                    @Override
                    public void onStartedShowing(int layoutType) {
                        if (layoutType == LayoutType.TAB_SWITCHER) {
                            mHistoryNavigationCoordinator.reset();
                        }
                    }
                };
        mMultiInstanceManager = multiInstanceManager;
        mHubManagerSupplier = hubManagerSupplier;
        mStatusBarColorController.setAllowToolbarColorOnTablets(true);
        mEdgeToEdgeControllerSupplier = edgeToEdgeSupplier;
        mSystemBarColorHelperSupplier = systemBarColorHelperSupplier;
        mManualFillingComponentSupplier = manualFillingComponentSupplier;

        DataSharingTabGroupsDelegate dataSharingTabGroupsDelegate =
                createDataSharingTabGroupsDelegate();

        CollaborationControllerDelegateFactory collaborationControllerDelegateFactory =
                (type) -> {
                    assert getDataSharingTabManager() != null;
                    return new CollaborationControllerDelegateImpl(
                            mActivity,
                            type,
                            getDataSharingTabManager(),
                            SigninAndHistorySyncActivityLauncherImpl.get());
                };

        mDataSharingTabManager =
                new DataSharingTabManager(
                        mTabModelSelectorSupplier,
                        dataSharingTabGroupsDelegate,
                        this::getBottomSheetController,
                        mShareDelegateSupplier,
                        mWindowAndroid,
                        mActivity.getResources(),
                        mTabGroupUiActionHandlerSupplier,
                        collaborationControllerDelegateFactory);

        mEdgeToEdgeManager = edgeToEdgeManager;
        initAppHeaderCoordinator(
                savedInstanceState, mEdgeToEdgeManager.getEdgeToEdgeStateProvider());
=======
>>>>>>> chromium
    }

    @Override
    public void onDestroy() {
        if (mSystemUiCoordinator != null) mSystemUiCoordinator.destroy();
        if (mEmptyBackgroundViewWrapper != null) mEmptyBackgroundViewWrapper.destroy();

        if (mOfflineIndicatorController != null) {
            mOfflineIndicatorController.destroy();
        }

        if (mToolbarManager != null) {
            mToolbarManager.getOmniboxStub().removeUrlFocusChangeListener(mUrlFocusChangeListener);
<<<<<<< HEAD
            if (mOnTabStripHeightChangedCallback != null) {
                mToolbarManager
                        .getTabStripHeightSupplier()
                        .removeObserver(mOnTabStripHeightChangedCallback);
                mOnTabStripHeightChangedCallback = null;
            }
            mToolbarManager.setBookmarkBarHeightSupplier(null);
=======
>>>>>>> chromium
        }

        if (mOfflineIndicatorInProductHelpController != null) {
            mOfflineIndicatorInProductHelpController.destroy();
        }
        if (mStatusIndicatorCoordinator != null) {
            mStatusIndicatorCoordinator.removeObserver(mStatusIndicatorObserver);
            mStatusIndicatorCoordinator.removeObserver(mActivity.getStatusBarColorController());
            mStatusIndicatorCoordinator.destroy();
        }

        if (mToolbarButtonInProductHelpController != null) {
            mToolbarButtonInProductHelpController.destroy();
        }

        if (mWebFeedFollowIntroController != null) {
            mWebFeedFollowIntroController.destroy();
        }

        if (mRootUiTabObserver != null) mRootUiTabObserver.destroy();

        if (mAppBannerInProductHelpController != null) {
            AppBannerInProductHelpControllerFactory.detach(mAppBannerInProductHelpController);
        }

        if (mPwaBottomSheetController != null) {
            PwaBottomSheetControllerFactory.detach(mPwaBottomSheetController);
        }

        if (mHistoryNavigationCoordinator != null) {
            TouchEventObserver obs = mHistoryNavigationCoordinator.getTouchEventObserver();
            CompositorViewHolder cvh = mActivity.getCompositorViewHolder();
            if (cvh != null && obs != null) cvh.removeTouchEventObserver(obs);
            mHistoryNavigationCoordinator.destroy();
            mHistoryNavigationCoordinator = null;
        }

        if (mContinuousSearchContainerCoordinator != null) {
            getTabObscuringHandler().removeObserver(mContinuousSearchTabObscuringHandlerObserver);
            mContinuousSearchContainerCoordinator.removeHeightObserver(mContinuousSearchObserver);
            if (mFindToolbarManager != null) {
                mFindToolbarManager.removeObserver(mContinuousSearchFindToolbarObserver);
            }
            mContinuousSearchContainerCoordinator.destroy();
            mContinuousSearchContainerCoordinator = null;
            mContinuousSearchObserver = null;
            mContinuousSearchTabObscuringHandlerObserver = null;
            mContinuousSearchFindToolbarObserver = null;
        }

        if (mMerchantTrustSignalsCoordinator != null) {
            mMerchantTrustSignalsCoordinator.destroy();
            mMerchantTrustSignalsCoordinator = null;
        }

        if (mCommerceSubscriptionsService != null) {
            mCommerceSubscriptionsService.destroy();
            mCommerceSubscriptionsService = null;
        }

<<<<<<< HEAD
        if (mNotificationPermissionController != null) {
            NotificationPermissionController.detach(mNotificationPermissionController);
            mNotificationPermissionController = null;
        }

        if (mDesktopSiteSettingsIphController != null) {
            mDesktopSiteSettingsIphController.destroy();
            mDesktopSiteSettingsIphController = null;
        }

        if (mRtlGestureNavIphController != null) {
            mRtlGestureNavIphController.destroy();
            mRtlGestureNavIphController = null;
        }

        if (mCoordinator != null && mDragDropTouchObserver != null) {
            ((CoordinatorLayoutForPointer) mCoordinator)
                    .removeTouchEventObserver(mDragDropTouchObserver);
            mDragDropTouchObserver = null;
        }

        if (mAppHeaderCoordinator != null && VERSION.SDK_INT >= VERSION_CODES.R) {
            mAppHeaderCoordinator.destroy();
            mAppHeaderCoordinator = null;
        }

        mDataSharingTabManager.destroy();

        if (mInstantMessageDelegateImpl != null) {
            mInstantMessageDelegateImpl.detachWindow(mWindowAndroid);
        }

        if (mBookmarkBarCoordinator != null) {
            mBookmarkBarCoordinator.destroy();
            mBookmarkBarCoordinator = null;
        }

=======
>>>>>>> chromium
        super.onDestroy();
    }

    @Override
    public void onPostInflationStartup() {
        super.onPostInflationStartup();

<<<<<<< HEAD
        mSystemUiCoordinator =
                new TabbedSystemUiCoordinator(
                        mActivity.getWindow(),
                        mTabModelSelectorSupplier.get(),
                        mLayoutManagerSupplier,
                        mFullscreenManager,
                        mEdgeToEdgeControllerSupplier,
                        mBottomControlsStacker,
                        mBrowserControlsManager,
                        mSnackbarManagerSupplier,
                        mContextualSearchManagerSupplier,
                        getBottomSheetController(),
                        mToolbarManager.getLocationBar().getOmniboxSuggestionsVisualState(),
                        mManualFillingComponentSupplier
                                .get()
                                .getAccessorySheetVisualStateProvider(),
                        mOverviewColorSupplier,
                        mInsetObserver,
                        mEdgeToEdgeManager.getEdgeToEdgeSystemBarColorHelper(),
                        getTabObscuringHandler());
=======
        mSystemUiCoordinator = new TabbedSystemUiCoordinator(mActivity.getWindow(),
                mActivity.getTabModelSelector(), mActivity.getOverviewModeBehaviorSupplier());
>>>>>>> chromium
    }

    @Override
    protected void onFindToolbarShown() {
        super.onFindToolbarShown();
        EphemeralTabCoordinator coordinator = mEphemeralTabCoordinatorSupplier.get();
        if (coordinator != null && coordinator.isOpened()) coordinator.close();
    }

    /**
     * @return The toolbar button IPH controller for the tabbed UI this coordinator controls.
     * TODO(pnoland, https://crbug.com/865801): remove this in favor of wiring it directly.
     */
    public ToolbarButtonInProductHelpController getToolbarButtonInProductHelpController() {
        return mToolbarButtonInProductHelpController;
    }

    /**
     * Show navigation history sheet.
     */
    public void showFullHistorySheet() {
        Tab tab = mActivity.getActivityTabProvider().get();
        if (tab == null || tab.getWebContents() == null || !tab.isUserInteractable()) return;
        Profile profile = Profile.fromWebContents(tab.getWebContents());
        mNavigationSheet = NavigationSheet.create(
                mActivity.getWindow().getDecorView().findViewById(android.R.id.content), mActivity,
                this::getBottomSheetController, profile);
        mNavigationSheet.setDelegate(new TabbedSheetDelegate(tab, aTab -> {
            HistoryManagerUtils.showHistoryManager(
                    mActivity, aTab, mActivity.getTabModelSelector().isIncognitoSelected());
        }, mActivity.getResources().getString(R.string.show_full_history)));
        if (!mNavigationSheet.startAndExpand(/* forward=*/false, /* animate=*/true)) {
            mNavigationSheet = null;
        } else {
            getBottomSheetController().addObserver(new EmptyBottomSheetObserver() {
                @Override
                public void onSheetClosed(int reason) {
                    getBottomSheetController().removeObserver(this);
                    mNavigationSheet = null;
                }
            });
        }
    }

    @Override
    public void onFinishNativeInitialization() {
        super.onFinishNativeInitialization();
        assert mLayoutManager != null;
        CompositorViewHolder cvh = mActivity.getCompositorViewHolder();
        ActivityTabProvider activityTabProvider = mActivity.getActivityTabProvider();

        mHistoryNavigationCoordinator = HistoryNavigationCoordinator.create(
                mActivity.getWindowAndroid(), mActivity.getLifecycleDispatcher(), cvh,
                mCallbackController.makeCancelable(
                        () -> mLayoutManager.getActiveLayout().requestUpdate()),
                activityTabProvider, mActivity.getInsetObserverView(), new BackActionDelegate() {
                    @Override
                    public @ActionType int getBackActionType(Tab tab) {
                        if (isShowingStartSurfaceHomepage()) return ActionType.EXIT_APP;
                        if (tab.canGoBack()
                                || tab.getLaunchType() == TabLaunchType.FROM_START_SURFACE) {
                            return ActionType.NAVIGATE_BACK;
                        }
                        if (TabAssociatedApp.isOpenedFromExternalApp(tab)) {
                            return ActionType.EXIT_APP;
                        }
                        return mActivity.backShouldCloseTab(tab) ? ActionType.CLOSE_TAB
                                                                 : ActionType.EXIT_APP;
                    }

<<<<<<< HEAD
                            @Override
                            public void onBackGesture(Tab tab) {
                                // Back navigation gesture performs only history navigation or
                                // closing the current tab/chrome. Other actions back button can do
                                // is not considered.
                                switch (getBackActionType(tab)) {
                                    case ActionType.NAVIGATE_BACK:
                                        tab.goBack();
                                        break;
                                    case ActionType.CLOSE_TAB:
                                        mTabModelSelectorSupplier
                                                .get()
                                                .getCurrentModel()
                                                .getTabRemover()
                                                .closeTabs(
                                                        TabClosureParams.closeTab(tab).build(),
                                                        /* allowDialog= */ false);
                                        break;
                                    case ActionType.EXIT_APP:
                                        mSendToBackground.onResult(tab);
                                        break;
                                }
                            }
=======
                    @Override
                    public void onBackGesture() {
                        // Back navigation gesture performs what the back button would do.
                        mActivity.onBackPressed();
                    }
>>>>>>> chromium

                    @Override
                    public boolean isNavigable() {
                        return isShowingStartSurfaceHomepage();
                    }
                }, cvh::addTouchEventObserver, mLayoutManager);
        mRootUiTabObserver.swapToTab(activityTabProvider.get());

        // TODO(twellington): Supply TabModelSelector as well and move initialization earlier.
        if (DeviceFormFactor.isNonMultiDisplayContextOnTablet(mActivity)) {
<<<<<<< HEAD
            ChromeTabbedOnDragListener chromeTabbedOnDragListener =
                    new ChromeTabbedOnDragListener(
                            mMultiInstanceManager,
                            mTabModelSelectorSupplier.get(),
                            mWindowAndroid,
                            mLayoutStateProviderOneShotSupplier,
                            mAppHeaderCoordinator);

            mCompositorViewHolderSupplier.get().setOnDragListener(chromeTabbedOnDragListener);

            // Disable touch event while drag is in progress.
            mDragDropTouchObserver = e -> DragDropGlobalState.hasValue();
            ((CoordinatorLayoutForPointer) mCoordinator)
                    .addTouchEventObserver(mDragDropTouchObserver);
=======
            AppMenuHandler appMenuHandler =
                    mAppMenuCoordinator == null ? null : mAppMenuCoordinator.getAppMenuHandler();
            mEmptyBackgroundViewWrapper = new EmptyBackgroundViewWrapper(
                    mActivity.getTabModelSelector(), mActivity.getTabCreator(false), mActivity,
                    appMenuHandler, mActivity.getSnackbarManager(),
                    mActivity.getOverviewModeBehaviorSupplier());
            mEmptyBackgroundViewWrapper.initialize();
>>>>>>> chromium
        }

        if (!mActivity.isTablet()
                && (TabUiFeatureUtilities.isTabGroupsAndroidEnabled(mActivity)
                        || TabUiFeatureUtilities.isConditionalTabStripEnabled())) {
            getToolbarManager().enableBottomControls();
        }

        if (EphemeralTabCoordinator.isSupported()) {
            mEphemeralTabCoordinatorSupplier.set(
                    new EphemeralTabCoordinator(mActivity, mActivity.getWindowAndroid(),
                            mActivity.getWindow().getDecorView(), activityTabProvider,
                            mActivity::getCurrentTabCreator, getBottomSheetController(), true));
        }

        mIntentMetadataOneshotSupplier.onAvailable(mCallbackController.makeCancelable(
                (metadata) -> initializeIPH(metadata.getIsIntentWithEffect())));

        // TODO(https://crbug.com/1157955): Investigate switching to per-Activity coordinator that
        // uses signals from the current Tab to decide when to show the PWA install bottom sheet
        // rather than relying on unowned user data.
        mPwaBottomSheetController =
                PwaBottomSheetControllerFactory.createPwaBottomSheetController(mActivity);
        PwaBottomSheetControllerFactory.attach(
                mActivity.getWindowAndroid(), mPwaBottomSheetController);
        initContinuousSearchCoordinator();

        initMerchantTrustSignals();
        initCommerceSubscriptionsService();
<<<<<<< HEAD
        initUndoGroupSnackbarController();
        initTabStripTransitionCoordinator();
        if (ChromeFeatureList.isEnabled(ChromeFeatureList.CHROME_SHARE_PAGE_INFO)) {
            PageInfoSharingControllerImpl.getInstance().initialize();
        }

        new OneShotCallback<>(mProfileSupplier, this::initCollaborationDelegatesOnProfile);

        if (ChromeFeatureList.sAndroidBookmarkBar.isEnabled()
                && DeviceFormFactor.isNonMultiDisplayContextOnTablet(mActivity)) {
            mBookmarkBarCoordinator =
                    new BookmarkBarCoordinator(
                            mActivity,
                            mBrowserControlsManager,
                            /* heightChangeCallback= */ (height) -> updateTopControlsHeight(),
                            mProfileSupplier,
                            /* viewStub= */ mActivity.findViewById(R.id.bookmark_bar_stub));

            if (mToolbarManager != null) {
                mToolbarManager.setBookmarkBarHeightSupplier(
                        mBookmarkBarCoordinator.getHeightSupplier());
            }
        }
    }

    @Override
    protected void initProfileDependentFeatures(Profile currentlySelectedProfile) {
        super.initProfileDependentFeatures(currentlySelectedProfile);
        Profile originalProfile = currentlySelectedProfile.getOriginalProfile();
        if (TabGroupSyncFeatures.isTabGroupSyncEnabled(originalProfile)) {
            mTabGroupSyncController =
                    new TabGroupSyncControllerImpl(
                            mTabModelSelectorSupplier.get(),
                            TabGroupSyncServiceFactory.getForProfile(originalProfile),
                            UserPrefs.get(originalProfile),
                            () -> {
                                return MultiWindowUtils.getInstanceCount() <= 1
                                        || ApplicationStatus.getLastTrackedFocusedActivity()
                                                == mActivity;
                            });
            mTabGroupUiActionHandlerSupplier.set(mTabGroupSyncController);
        }
=======
    }

    private boolean isShowingStartSurfaceHomepage() {
        return mStartSurfaceSupplier.get() != null
                && mStartSurfaceSupplier.get().getController().getStartSurfaceState()
                == StartSurfaceState.SHOWN_HOMEPAGE;
>>>>>>> chromium
    }

    private void initMerchantTrustSignals() {
        if (!ChromeFeatureList.isEnabled(ChromeFeatureList.COMMERCE_MERCHANT_VIEWER)) {
            return;
        }

        mMerchantTrustSignalsCoordinator =
                new MerchantTrustSignalsCoordinator(mActivity, mActivity.getWindowAndroid(),
                        getBottomSheetController(), mActivity.getWindow().getDecorView(),
                        MessageDispatcherProvider.from(mActivity.getWindowAndroid()),
                        mActivity.getActivityTabProvider(), mProfileSupplier,
                        new MerchantTrustMetrics(), mActivity.getIntentRequestTracker());
    }

    // Protected class methods

    @Override
    protected void onLayoutManagerAvailable(LayoutManagerImpl layoutManager) {
        super.onLayoutManagerAvailable(layoutManager);

        initStatusIndicatorCoordinator(layoutManager);
        mLayoutManager = layoutManager;
    }

    @Override
    protected boolean shouldShowMenuUpdateBadge() {
        return true;
    }

    @Override
<<<<<<< HEAD
    protected ScrimManager buildScrimWidget() {
        ScrimManager scrimManager = new ScrimManager(mActivity, mCoordinator);
        scrimManager
                .getStatusBarColorSupplier()
                .addObserver(mStatusBarColorController::setScrimColor);
        scrimManager.getNavigationBarColorSupplier().addObserver(this::onNavBarScrimColorChanged);
        return scrimManager;
    }

    @SuppressLint("NewApi")
    private void onNavBarScrimColorChanged(@ColorInt int color) {
        // When drawing edge to edge, scrim already draws over the nav bar region.
        // No need to change the nav bar color.
        var edgeToEdgeController = mEdgeToEdgeControllerSupplier.get();
        if (edgeToEdgeController != null && edgeToEdgeController.isDrawingToEdge()) {
            return;
        }

        TabbedNavigationBarColorController controller =
                mSystemUiCoordinator.getNavigationBarColorController();
        if (controller == null) {
            return;
        }
        controller.setNavigationBarScrimColor(color);
    }

    // Package Private class methods
    void recordPrivacySandboxActivityType(Profile profile) {
        // Records the current ActivityType using a PrivacySandbox Bridge
        if (ChromeFeatureList.isEnabled(ChromeFeatureList.PRIVACY_SANDBOX_ACTIVITY_TYPE_STORAGE)) {
            int privacySandboxStorageActivityType =
                    ActivityTypeMapper.toPrivacySandboxStorageActivityType(ActivityType.TABBED);

            PrivacySandboxBridge privacySandboxBridge = new PrivacySandboxBridge(profile);
            privacySandboxBridge.recordActivityType(privacySandboxStorageActivityType);
        }
    }

    boolean maybeTriggerPsDialogSuppression(Profile profile) {
        // Handles whether the PS Dialog should be suppressed, logs whether it was suppressed and
        // returns whether a promo was triggered
        Tab tab = mActivityTabProvider.get();

        boolean isTabLaunchedFromExternalApp =
                tab != null && tab.getLaunchType() == TabLaunchType.FROM_EXTERNAL_APP;
        boolean shouldSuppressPsDialogForExternalAppLaunches =
                ChromeFeatureList.getFieldTrialParamByFeatureAsBoolean(
                        ChromeFeatureList.PRIVACY_SANDBOX_SETTINGS_4,
                        "suppress-dialog-for-external-app-launches",
                        true);
        boolean shouldSuppressPsDialog =
                isTabLaunchedFromExternalApp && shouldSuppressPsDialogForExternalAppLaunches;

        String histogramName =
                "Startup.Android.PrivacySandbox.DialogNotShownDueToTabLaunchedFromExternalApp";
        RecordHistogram.recordBooleanHistogram(histogramName, shouldSuppressPsDialog);

        if (!shouldSuppressPsDialog) {
            return PrivacySandboxDialogController.maybeLaunchPrivacySandboxDialog(
                    mActivity, profile, SurfaceType.BR_APP, mWindowAndroid);
        }

        return false;
    }

    private boolean maybeTriggerPrivacySandboxPrompt(Profile profile) {
        return maybeTriggerPsDialogSuppression(profile);
=======
    protected ScrimCoordinator buildScrimWidget() {
        ViewGroup coordinator = mActivity.findViewById(R.id.coordinator);
        ScrimCoordinator.SystemUiScrimDelegate delegate =
                new ScrimCoordinator.SystemUiScrimDelegate() {
                    @Override
                    public void setStatusBarScrimFraction(float scrimFraction) {
                        mActivity.getStatusBarColorController().setStatusBarScrimFraction(
                                scrimFraction);
                    }

                    @Override
                    public void setNavigationBarScrimFraction(float scrimFraction) {
                        TabbedNavigationBarColorController controller =
                                mSystemUiCoordinator.getNavigationBarColorController();
                        if (controller == null) {
                            return;
                        }
                        controller.setNavigationBarScrimFraction(scrimFraction);
                    }
                };
        return new ScrimCoordinator(mActivity, delegate, coordinator,
                ApiCompatibilityUtils.getColor(coordinator.getResources(),
                        R.color.omnibox_focused_fading_background_color));
>>>>>>> chromium
    }

    // Private class methods

    private void initializeIPH(boolean intentWithEffect) {
        if (mActivity == null) return;
        mToolbarButtonInProductHelpController =
                new ToolbarButtonInProductHelpController(mActivity, mActivity.getWindowAndroid(),
                        mAppMenuCoordinator, mActivity.getLifecycleDispatcher(),
                        mActivity.getActivityTabProvider(), mActivity::isInOverviewMode,
                        mToolbarManager.getMenuButtonView(), mToolbarManager.getSecurityIconView());
        mReadLaterIPHController = new ReadLaterIPHController(mActivity,
                getToolbarManager().getMenuButtonView(), mAppMenuCoordinator.getAppMenuHandler());

        boolean didTriggerPromo = triggerPromo(intentWithEffect);
        if (!didTriggerPromo) {
            mToolbarButtonInProductHelpController.showColdStartIPH();
            mReadLaterIPHController.showColdStartIPH();
        }
        if (ChromeFeatureList.isEnabled(ChromeFeatureList.TOOLBAR_IPH_ANDROID)) {
            mPromoShownOneshotSupplier.set(didTriggerPromo);
        }

        if (mOfflineIndicatorController != null) {
            // Initialize the OfflineIndicatorInProductHelpController if the
            // mOfflineIndicatorController is enabled and initialized. For example, it wouldn't be
            // initialized if the OfflineIndicatorV2 feature is disabled.
            assert mOfflineIndicatorInProductHelpController == null;
            mOfflineIndicatorInProductHelpController =
                    new OfflineIndicatorInProductHelpController(mActivity, mToolbarManager,
                            mAppMenuCoordinator.getAppMenuHandler(), mStatusIndicatorCoordinator);
        }

        mAddToHomescreenIPHController = new AddToHomescreenIPHController(mActivity,
                mActivity.getWindowAndroid(), mActivity.getModalDialogManager(),
                mAppMenuCoordinator.getAppMenuHandler(), R.id.add_to_homescreen_id,
                ()
                        -> mActivity.getToolbarManager().getMenuButtonView(),
                MessageDispatcherProvider.from(mActivity.getWindowAndroid()));
        mAddToHomescreenMostVisitedTileObserver = new AddToHomescreenMostVisitedTileClickObserver(
                mActivity.getActivityTabProvider(), mAddToHomescreenIPHController);
        mAppBannerInProductHelpController =
                AppBannerInProductHelpControllerFactory.createAppBannerInProductHelpController(
                        mActivity, mAppMenuCoordinator.getAppMenuHandler(),
                        ()
                                -> mActivity.getToolbarManager().getMenuButtonView(),
                        R.id.add_to_homescreen_id);
        AppBannerInProductHelpControllerFactory.attach(
                mActivity.getWindowAndroid(), mAppBannerInProductHelpController);

        if (FeedFeatures.isWebFeedUIEnabled()) {
            mWebFeedFollowIntroController = new WebFeedFollowIntroController(mActivity,
                    mAppMenuCoordinator.getAppMenuHandler(), mActivity.getActivityTabProvider(),
                    mToolbarManager.getMenuButtonView(),
                    ()
                            -> mActivity.getTabCreator(/*incognito=*/false)
                                       .launchUrl(NewTabPageUtils.encodeNtpUrl(
                                                          NewTabPageLaunchOrigin.WEB_FEED),
                                               TabLaunchType.FROM_CHROME_UI),
                    mActivity.getModalDialogManager(), mActivity.getSnackbarManager());
        }
    }

<<<<<<< HEAD
    private void updateTopControlsHeight() {
        if (mToolbarManager == null) return;

        // TODO(crbug/331844971): Do a smooth transition head into DW mode.
        final boolean animate =
                !sDisableTopControlsAnimationForTesting
                        && !AppHeaderUtils.isAppInDesktopWindow(mAppHeaderCoordinator);
        final BrowserControlsSizer browserControlsSizer = mBrowserControlsManager;

        boolean isTablet = DeviceFormFactor.isNonMultiDisplayContextOnTablet(mActivity);
        int topControlsNewHeight;
        // This method can be called when the toolbar didn't go through a layout pass (e.g. when
        // theme switches in settings, activity recreates), so getToolbar().getHeight() returns
        // 0.
        // TODO(crbug.com/40943442): Remove the reference to toolbar_height_no_shadow.
        final int toolbarHeight =
                browserControlsSizer.getControlsPosition() == ControlsPosition.TOP
                        ? mActivity
                                .getResources()
                                .getDimensionPixelSize(R.dimen.toolbar_height_no_shadow)
                        : 0;
        final int tabStripHeight = mToolbarManager.getTabStripHeightSupplier().get();
        final int bookmarkBarHeight =
                mBookmarkBarCoordinator != null
                        ? mBookmarkBarCoordinator.getHeightSupplier().get()
                        : 0;
        topControlsNewHeight =
                bookmarkBarHeight + toolbarHeight + tabStripHeight + mStatusIndicatorHeight;
        if (tabStripHeight > 0 && !isTablet) {
            String msg =
                    "Non-zero tab strip height found on non-tablet form factor. tabStripHeight="
                            + " "
                            + tabStripHeight
                            + " toolbarHeight= "
                            + toolbarHeight
                            + " statusIndicatorHeight= "
                            + mStatusIndicatorHeight;
            ChromePureJavaExceptionReporter.reportJavaException(new Throwable(msg));
        }
=======
    private void updateTopControlsHeight(boolean animate) {
        final BrowserControlsSizer browserControlsSizer = mActivity.getBrowserControlsManager();
        final int resourceId = mActivity.getControlContainerHeightResource();
        final int topControlsNewHeight = mActivity.getResources().getDimensionPixelSize(resourceId)
                + mStatusIndicatorHeight + mContinuousSearchHeight;
>>>>>>> chromium

        browserControlsSizer.setAnimateBrowserControlsHeightChanges(animate);
        browserControlsSizer.setTopControlsHeight(topControlsNewHeight, mStatusIndicatorHeight);
        if (animate) browserControlsSizer.setAnimateBrowserControlsHeightChanges(false);
    }

    private void initCommerceSubscriptionsService() {
        if (!PriceTrackingUtilities.ENABLE_PRICE_NOTIFICATION.getValue()) {
            return;
        }

        CommerceSubscriptionsServiceFactory factory = new CommerceSubscriptionsServiceFactory();
        mCommerceSubscriptionsService = factory.getForLastUsedProfile();
        mCommerceSubscriptionsService.initDeferredStartupForActivity(
                mActivity.getTabModelSelector(), mActivity.getLifecycleDispatcher());
    }

    private void initStatusIndicatorCoordinator(LayoutManagerImpl layoutManager) {
        // TODO(crbug.com/1035584): Disable on tablets for now as we need to do one or two extra
        // things for tablets.
        if (DeviceFormFactor.isNonMultiDisplayContextOnTablet(mActivity)
                || (!ChromeFeatureList.isEnabled(ChromeFeatureList.OFFLINE_INDICATOR_V2)
                        && !sEnableStatusIndicatorForTests)) {
            return;
        }

        final BrowserControlsSizer browserControlsSizer = mActivity.getBrowserControlsManager();
        mStatusIndicatorCoordinator = new StatusIndicatorCoordinator(mActivity,
                mActivity.getCompositorViewHolder().getResourceManager(), browserControlsSizer,
                mActivity.getStatusBarColorController()::getStatusBarColorWithoutStatusIndicator,
                mCanAnimateBrowserControls, layoutManager::requestUpdate);
        layoutManager.addSceneOverlay(mStatusIndicatorCoordinator.getSceneLayer());
        mStatusIndicatorObserver = new StatusIndicatorCoordinator.StatusIndicatorObserver() {
            @Override
            public void onStatusIndicatorHeightChanged(int indicatorHeight) {
                mStatusIndicatorHeight = indicatorHeight;
                updateTopControlsHeight(/*animate=*/true);
            }
        };
        mStatusIndicatorCoordinator.addObserver(mStatusIndicatorObserver);
        mStatusIndicatorCoordinator.addObserver(mActivity.getStatusBarColorController());

        // Don't initialize the offline indicator controller if the feature is disabled.
        if (!ChromeFeatureList.isEnabled(ChromeFeatureList.OFFLINE_INDICATOR_V2)) {
            return;
        }

        ObservableSupplierImpl<Boolean> isUrlBarFocusedSupplier = new ObservableSupplierImpl<>();
        isUrlBarFocusedSupplier.set(mToolbarManager.isUrlBarFocused());
        mUrlFocusChangeListener = new UrlFocusChangeListener() {
            @Override
            public void onUrlFocusChange(boolean hasFocus) {
                // Offline indicator should assume the UrlBar is focused if it's focusing.
                if (hasFocus) {
                    isUrlBarFocusedSupplier.set(true);
                }
            }

            @Override
            public void onUrlAnimationFinished(boolean hasFocus) {
                // Wait for the animation to finish before notifying that UrlBar is unfocused.
                if (!hasFocus) {
                    isUrlBarFocusedSupplier.set(false);
                }
            }
        };
        mOfflineIndicatorController = new OfflineIndicatorControllerV2(mActivity,
                mStatusIndicatorCoordinator, isUrlBarFocusedSupplier, mCanAnimateBrowserControls);
        if (mToolbarManager.getOmniboxStub() != null) {
            mToolbarManager.getOmniboxStub().addUrlFocusChangeListener(mUrlFocusChangeListener);
        }
    }

<<<<<<< HEAD
    @Override
    protected Destroyable createEdgeToEdgeBottomChin() {
        SystemBarColorHelper bottomChinColorHelper =
                EdgeToEdgeControllerFactory.createBottomChin(
                        mActivity.findViewById(R.id.edge_to_edge_bottom_chin),
                        mWindowAndroid.getKeyboardDelegate(),
                        mLayoutManager,
                        mLayoutManager::requestUpdate,
                        mEdgeToEdgeControllerSupplier.get(),
                        mBottomControlsStacker,
                        mFullscreenManager);
        mSystemBarColorHelperSupplier.set(bottomChinColorHelper);
        return bottomChinColorHelper;
    }

    private void initTabStripTransitionCoordinator() {
        // Tab strip transition is only supported for tablets.
        if (!DeviceFormFactor.isNonMultiDisplayContextOnTablet(mActivity)) return;

        mOnTabStripHeightChangedCallback = (height) -> updateTopControlsHeight();
        mToolbarManager.getTabStripHeightSupplier().addObserver(mOnTabStripHeightChangedCallback);
    }

    @SuppressWarnings("NewApi") // OS version check is done via helper method.
    private void initAppHeaderCoordinator(
            Bundle savedInstanceState, EdgeToEdgeStateProvider edgeToEdgeStateProvider) {
        boolean isTablet = DeviceFormFactor.isNonMultiDisplayContextOnTablet(mActivity);
        if (!ToolbarFeatures.isTabStripWindowLayoutOptimizationEnabled(isTablet)) {
=======
    private void initContinuousSearchCoordinator() {
        if (!ChromeFeatureList.isEnabled(ChromeFeatureList.CONTINUOUS_SEARCH)) {
>>>>>>> chromium
            return;
        }

        Supplier<Integer> defaultTopContainerHeightSupplier = ()
                -> mActivity.getResources().getDimensionPixelSize(
                        mActivity.getControlContainerHeightResource());
        final ViewStub viewStub = mActivity.findViewById(R.id.continuous_search_container_stub);
        final BrowserControlsSizer browserControlsSizer = mActivity.getBrowserControlsManager();
        mContinuousSearchContainerCoordinator = new ContinuousSearchContainerCoordinator(viewStub,
                mLayoutManager, mActivity.getCompositorViewHolder().getResourceManager(),
                mActivity.getActivityTabProvider(), browserControlsSizer,
                mCanAnimateBrowserControls, defaultTopContainerHeightSupplier,
                getTopUiThemeColorProvider(), mActivity.getResources(),
                mToolbarManager::setForceHideShadow);
        mContinuousSearchObserver = (newHeight, animate) -> {
            mContinuousSearchHeight = newHeight;
            updateTopControlsHeight(animate);
        };
        mContinuousSearchContainerCoordinator.addHeightObserver(mContinuousSearchObserver);
        mContinuousSearchTabObscuringHandlerObserver =
                isObscured -> mContinuousSearchContainerCoordinator.updateTabObscured(isObscured);
        getTabObscuringHandler().addObserver(mContinuousSearchTabObscuringHandlerObserver);

        if (!mActivity.supportsFindInPage()) return;

        assert mFindToolbarManager != null;

        mContinuousSearchFindToolbarObserver = new FindToolbarObserver() {
            private int mToken = TokenHolder.INVALID_TOKEN;

            @Override
            public void onFindToolbarShown() {
                assert mToken == TokenHolder.INVALID_TOKEN;
                mToken = mContinuousSearchContainerCoordinator.hideContainer();
            }

            @Override
            public void onFindToolbarHidden() {
                mContinuousSearchContainerCoordinator.showContainer(mToken);
                mToken = TokenHolder.INVALID_TOKEN;
            }
        };
        mFindToolbarManager.addObserver(mContinuousSearchFindToolbarObserver);
    }

<<<<<<< HEAD
    private void initCollaborationDelegatesOnProfile(Profile profile) {
        // We must use the original non-OTR profile here.
        Profile originalProfile = profile.getOriginalProfile();

        CollaborationService collaborationService =
                CollaborationServiceFactory.getForProfile(originalProfile);
        @NonNull ServiceStatus serviceStatus = collaborationService.getServiceStatus();
        if (!serviceStatus.isAllowedToJoin()) return;

        mDataSharingTabManager.initWithProfile(
                originalProfile,
                DataSharingServiceFactory.getForProfile(originalProfile),
                MessagingBackendServiceFactory.getForProfile(originalProfile),
                collaborationService);

        TabModelUtils.onInitializedTabModelSelector(mTabModelSelectorSupplier)
                .runSyncOrOnAvailable(
                        selector -> {
                            mInstantMessageDelegateImpl =
                                    InstantMessageDelegateFactory.getForProfile(originalProfile);
                            TabGroupModelFilter tabGroupModelFilter =
                                    selector.getTabGroupModelFilterProvider()
                                            .getTabGroupModelFilter(/* isIncognito= */ false);
                            DataSharingNotificationManager dataSharingNotificationManager =
                                    new DataSharingNotificationManager(mActivity);
                            mInstantMessageDelegateImpl.attachWindow(
                                    mWindowAndroid,
                                    tabGroupModelFilter,
                                    dataSharingNotificationManager,
                                    mDataSharingTabManager);
                        });
    }

    private DataSharingTabGroupsDelegate createDataSharingTabGroupsDelegate() {
        return new DataSharingTabGroupsDelegate() {

            @Override
            public void openTabGroupWithTabId(int tabId) {
                mTabSwitcherSupplier.get().requestOpenTabGroupDialog(tabId);
            }

            @Override
            public void openLearnMoreSharedTabGroupsPage(Context context, GURL gurl) {
                CustomTabActivity.showInfoPage(context, gurl.getSpec());
            }

            @Override
            public void openUrlInChromeCustomTab(Context context, GURL gurl) {
                CustomTabActivity.showInfoPage(context, gurl.getSpec());
            }

            @Override
            public void getPreviewBitmap(
                    String collaborationId, int size, Callback<Bitmap> callback) {
                // TODO(https://crbug.com/386833405): implement this.
                callback.onResult(null);
            }
        };
    }

    @Override
    public DesktopWindowStateManager getDesktopWindowStateManager() {
        return mAppHeaderCoordinator;
    }

    /** Returns the {@link TabGroupSyncControllerImpl} if it has been created yet. */
    public TabGroupSyncController getTabGroupSyncController() {
        return mTabGroupSyncController;
    }

    @Override
    protected boolean supportsEdgeToEdge() {
        return EdgeToEdgeControllerFactory.isSupportedConfiguration(mActivity);
=======
    /**
     * @return {@link ComposedBrowserControlsVisibilityDelegate} object for tabbed activity.
     */
    public ComposedBrowserControlsVisibilityDelegate getAppBrowserControlsVisibilityDelegate() {
        if (mAppBrowserControlsVisibilityDelegate == null) {
            mAppBrowserControlsVisibilityDelegate = new ComposedBrowserControlsVisibilityDelegate();
        }
        return mAppBrowserControlsVisibilityDelegate;
>>>>>>> chromium
    }

    @VisibleForTesting
    public StatusIndicatorCoordinator getStatusIndicatorCoordinatorForTesting() {
        return mStatusIndicatorCoordinator;
    }

    @VisibleForTesting
    public static void setEnableStatusIndicatorForTests(boolean disable) {
        sEnableStatusIndicatorForTests = disable;
    }

    @VisibleForTesting
    public EphemeralTabCoordinator getEphemeralTabCoordinatorForTesting() {
        return mEphemeralTabCoordinatorSupplier.get();
    }

    @VisibleForTesting
    public HistoryNavigationCoordinator getHistoryNavigationCoordinatorForTesting() {
        return mHistoryNavigationCoordinator;
    }

    @VisibleForTesting
    public NavigationSheet getNavigationSheetForTesting() {
        return mNavigationSheet;
    }

    /** Called when a link is copied through context menu. */
    public void onContextMenuCopyLink() {
        // TODO(crbug/1150090): Find a better way of passing event for IPH.
        mReadLaterIPHController.onCopyContextMenuItemClicked();
    }

    /**
     * Triggers the display of an appropriate promo, if any, returning true if a promo is actually
     * displayed.
     */
    private boolean triggerPromo(boolean intentWithEffect) {
        try (TraceEvent e = TraceEvent.scoped("TabbedRootUiCoordinator.triggerPromo")) {
            if (CommandLine.getInstance().hasSwitch(ChromeSwitches.DISABLE_STARTUP_PROMOS)) {
                return false;
            }

            SharedPreferencesManager preferenceManager = SharedPreferencesManager.getInstance();
            // Promos can only be shown when we start with ACTION_MAIN intent and
            // after FRE is complete. Native initialization can finish before the FRE flow is
            // complete, and this will only show promos on the second opportunity. This is
            // because the FRE is shown on the first opportunity, and we don't want to show such
            // content back to back.
            //
            // TODO(https://crbug.com/865801, pnoland): Unify promo dialog logic and move into a
            // single PromoDialogCoordinator.
            boolean isShowingPromo =
                    LocaleManager.getInstance().hasShownSearchEnginePromoThisSession();
            // Promo dialogs in multiwindow mode are broken on some devices:
            // http://crbug.com/354696
            boolean isLegacyMultiWindow =
                    MultiWindowUtils.getInstance().isLegacyMultiWindow(mActivity);
            if (!isShowingPromo && !intentWithEffect && FirstRunStatus.getFirstRunFlowComplete()
                    && preferenceManager.readBoolean(
                            ChromePreferenceKeys.PROMOS_SKIPPED_ON_FIRST_START, false)
                    && !VrModuleProvider.getDelegate().isInVr()
                    // VrModuleProvider.getDelegate().isInVr may not return true at this point
                    // even though Chrome is about to enter VR, so we need to also check whether
                    // we're launching into VR.
                    && !VrModuleProvider.getIntentDelegate().isLaunchingIntoVr(
                            mActivity, mActivity.getIntent())
                    && !isLegacyMultiWindow) {
                isShowingPromo = maybeShowPromo();
            } else {
                preferenceManager.writeBoolean(
                        ChromePreferenceKeys.PROMOS_SKIPPED_ON_FIRST_START, true);
            }
            return isShowingPromo;
        }
    }

    private boolean maybeShowPromo() {
        // Only one promo can be shown in one run to avoid nagging users too much.
        if (SigninPromoUtil.launchSigninPromoIfNeeded(mActivity,
                    SyncConsentActivityLauncherImpl.get(),
                    ChromeVersionInfo.getProductMajorVersion())) {
            return true;
        }
        if (DataReductionPromoScreen.launchDataReductionPromo(
                    mActivity, mActivity.getTabModelSelector().getCurrentModel().isIncognito())) {
            return true;
        }
<<<<<<< HEAD
        if (DefaultBrowserPromoUtils.getInstance()
                .prepareLaunchPromoIfNeeded(
                        mActivity, mWindowAndroid, TrackerFactory.getTrackerForProfile(profile))) {
=======
        if (DefaultBrowserPromoUtils.prepareLaunchPromoIfNeeded(
                    mActivity, mActivity.getWindowAndroid())) {
>>>>>>> chromium
            return true;
        }
        if (AppLanguagePromoDialog.maybeShowPrompt(mActivity,
                    mActivity.getModalDialogManagerSupplier(),
                    () -> ApplicationLifetime.terminate(true))) {
            return true;
        }
        return LanguageAskPrompt.maybeShowLanguageAskPrompt(
                mActivity, mActivity.getModalDialogManagerSupplier());
    }
}
