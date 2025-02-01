// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tasks.tab_management;

import static org.chromium.chrome.browser.tasks.tab_management.TabManagementModuleProvider.SYNTHETIC_TRIAL_POSTFIX;

import android.app.Activity;
<<<<<<< HEAD
import android.content.res.Resources;
import android.graphics.Color;
import android.os.Build;
=======
import android.content.Context;
>>>>>>> chromium
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;

import org.chromium.base.metrics.RecordHistogram;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.base.supplier.Supplier;
import org.chromium.chrome.browser.compositor.layouts.OverviewModeBehavior;
import org.chromium.chrome.browser.compositor.layouts.content.TabContentManager;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.lifecycle.ActivityLifecycleDispatcher;
import org.chromium.chrome.browser.lifecycle.PauseResumeWithNativeObserver;
import org.chromium.chrome.browser.metrics.UmaSessionStats;
import org.chromium.chrome.browser.share.ShareDelegate;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.state.CriticalPersistedTabData;
import org.chromium.chrome.browser.tabmodel.TabCreatorManager;
<<<<<<< HEAD
=======
import org.chromium.chrome.browser.tabmodel.TabModelFilter;
import org.chromium.chrome.browser.tabmodel.TabModelFilterProvider;
import org.chromium.chrome.browser.tabmodel.TabModelObserver;
>>>>>>> chromium
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tasks.tab_groups.TabGroupModelFilter;
import org.chromium.chrome.browser.tasks.tab_groups.TabGroupUtils;
import org.chromium.chrome.browser.theme.ThemeColorProvider;
import org.chromium.chrome.browser.toolbar.bottom.BottomControlsCoordinator;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.tab_ui.R;
import org.chromium.components.browser_ui.bottomsheet.BottomSheetController;
<<<<<<< HEAD
import org.chromium.components.browser_ui.widget.scrim.ScrimManager;
import org.chromium.components.collaboration.CollaborationService;
import org.chromium.components.collaboration.ServiceStatus;
import org.chromium.components.data_sharing.DataSharingService;
import org.chromium.components.sensitive_content.SensitiveContentFeatures;
import org.chromium.ui.modaldialog.ModalDialogManager;
=======
import org.chromium.components.browser_ui.widget.scrim.ScrimCoordinator;
import org.chromium.components.feature_engagement.FeatureConstants;
>>>>>>> chromium
import org.chromium.ui.modelutil.PropertyModel;
import org.chromium.ui.modelutil.PropertyModelChangeProcessor;
import org.chromium.ui.resources.dynamics.DynamicResourceLoader;

import java.util.List;

/**
 * A coordinator for TabGroupUi component. Manages the communication with
 * {@link TabListCoordinator} as well as the life-cycle of
 * shared component objects.
 */
public class TabGroupUiCoordinator implements TabGroupUiMediator.ResetHandler, TabGroupUi,
                                              PauseResumeWithNativeObserver,
                                              TabGroupUiMediator.TabGroupUiController {
    static final String COMPONENT_NAME = "TabStrip";
    private final Activity mActivity;
<<<<<<< HEAD
    private final BrowserControlsStateProvider mBrowserControlsStateProvider;
=======
    private final Context mContext;
>>>>>>> chromium
    private final PropertyModel mModel;
    private final ThemeColorProvider mThemeColorProvider;
    private final TabGroupUiToolbarView mToolbarView;
    private final ViewGroup mTabListContainerView;
    private final ScrimManager mScrimManager;
    private final ObservableSupplier<Boolean> mOmniboxFocusStateSupplier;
    private final BottomSheetController mBottomSheetController;
    private final ActivityLifecycleDispatcher mActivityLifecycleDispatcher;
    private final Supplier<Boolean> mIsWarmOnResumeSupplier;
    private final ViewGroup mRootView;
    private final TabModelSelector mTabModelSelector;
    private final OneshotSupplier<OverviewModeBehavior> mOverviewModeBehaviorSupplier;
    private final SnackbarManager mSnackbarManager;
    private final Supplier<ShareDelegate> mShareDelegateSupplier;
    private final TabCreatorManager mTabCreatorManager;
    private final Supplier<DynamicResourceLoader> mDynamicResourceLoaderSupplier;
    private final TabContentManager mTabContentManager;
<<<<<<< HEAD
    private final ModalDialogManager mModalDialogManager;
    private final ObservableSupplierImpl<Token> mCurrentTabGroupId = new ObservableSupplierImpl<>();
    private final ThemeColorProvider mThemeColorProvider;
    private final ObservableSupplierImpl<Integer> mBackgroundColorSupplier =
            new ObservableSupplierImpl<>(Color.TRANSPARENT);

=======
>>>>>>> chromium
    private PropertyModelChangeProcessor mModelChangeProcessor;
    private TabGridDialogCoordinator mTabGridDialogCoordinator;
    private TabListCoordinator mTabStripCoordinator;
    private TabGroupUiMediator mMediator;

<<<<<<< HEAD
    /** Creates a new {@link TabGroupUiCoordinator} */
    public TabGroupUiCoordinator(
            @NonNull Activity activity,
            @NonNull ViewGroup parentView,
            @NonNull BrowserControlsStateProvider browserControlsStateProvider,
            @NonNull ScrimManager scrimManager,
=======
    /**
     * Creates a new {@link TabGroupUiCoordinator}
     */
    public TabGroupUiCoordinator(@NonNull Activity activity, @NonNull ViewGroup parentView,
            @NonNull ThemeColorProvider themeColorProvider,
            @NonNull ScrimCoordinator scrimCoordinator,
>>>>>>> chromium
            @NonNull ObservableSupplier<Boolean> omniboxFocusStateSupplier,
            @NonNull BottomSheetController bottomSheetController,
            @NonNull ActivityLifecycleDispatcher activityLifecycleDispatcher,
            @NonNull Supplier<Boolean> isWarmOnResumeSupplier,
            @NonNull TabModelSelector tabModelSelector,
            @NonNull TabContentManager tabContentManager, @NonNull ViewGroup rootView,
            @NonNull Supplier<DynamicResourceLoader> dynamicResourceLoaderSupplier,
            @NonNull TabCreatorManager tabCreatorManager,
<<<<<<< HEAD
            @NonNull OneshotSupplier<LayoutStateProvider> layoutStateProviderSupplier,
            @NonNull ModalDialogManager modalDialogManager,
            @NonNull ThemeColorProvider themeColorProvider) {
        try (TraceEvent e = TraceEvent.scoped("TabGroupUiCoordinator.constructor")) {
            mActivity = activity;
            mBrowserControlsStateProvider = browserControlsStateProvider;
            mScrimManager = scrimManager;
            mOmniboxFocusStateSupplier = omniboxFocusStateSupplier;
            mModel = new PropertyModel(TabGroupUiProperties.ALL_KEYS);

            @LayoutRes
            int layoutId =
                    ChromeFeatureList.isEnabled(ChromeFeatureList.DATA_SHARING)
                            ? R.layout.dynamic_bottom_tab_strip_toolbar
                            : R.layout.bottom_tab_strip_toolbar;
            mToolbarView =
                    (TabGroupUiToolbarView)
                            LayoutInflater.from(activity).inflate(layoutId, parentView, false);
            mTabListContainerView = mToolbarView.getViewContainer();
            mBottomSheetController = bottomSheetController;
            mDataSharingTabManager = dataSharingTabManager;
            mTabModelSelector = tabModelSelector;
            mActionConfirmationSupplier =
                    LazyOneshotSupplier.fromSupplier(this::createActionConfirmationManager);
            mLayoutStateProviderSupplier = layoutStateProviderSupplier;
            mTabCreatorManager = tabCreatorManager;
            mTabContentManager = tabContentManager;
            mModalDialogManager = modalDialogManager;
            mThemeColorProvider = themeColorProvider;
            parentView.addView(mToolbarView);
        }
    }

    private ActionConfirmationManager createActionConfirmationManager() {
        Profile profile = mTabModelSelector.getModel(false).getProfile();
        return new ActionConfirmationManager(profile, mActivity, mModalDialogManager);
    }

    private TabGridDialogMediator.DialogController initTabGridDialogCoordinator() {
        assert mTabGridDialogControllerSupplier != null;
        if (mTabGridDialogCoordinator != null) return mTabGridDialogCoordinator;

        var currentTabGroupModelFilterSupplier =
                mTabModelSelector
                        .getTabGroupModelFilterProvider()
                        .getCurrentTabGroupModelFilterSupplier();
        mTabGridDialogCoordinator =
                new TabGridDialogCoordinator(
                        mActivity,
                        mBrowserControlsStateProvider,
                        mBottomSheetController,
                        mDataSharingTabManager,
                        currentTabGroupModelFilterSupplier,
                        mTabContentManager,
                        mActivity.findViewById(R.id.coordinator),
                        null,
                        null,
                        null,
                        mScrimManager,
                        mActionConfirmationSupplier.get(),
                        mModalDialogManager,
                        /* desktopWindowStateManager= */ null);
        return mTabGridDialogCoordinator;
    }

    /** Handle any initialization that occurs once native has been loaded. */
    @Override
    public void initializeWithNative(
            Activity activity,
            BottomControlsCoordinator.BottomControlsVisibilityController visibilityController,
            Callback<Object> onModelTokenChange) {
        var currentTabGroupModelFilterSupplier =
                mTabModelSelector
                        .getTabGroupModelFilterProvider()
                        .getCurrentTabGroupModelFilterSupplier();
        try (TraceEvent e = TraceEvent.scoped("TabGroupUiCoordinator.initializeWithNative")) {
            mTabStripCoordinator =
                    new TabListCoordinator(
                            TabListCoordinator.TabListMode.STRIP,
                            mActivity,
                            mBrowserControlsStateProvider,
                            mModalDialogManager,
                            currentTabGroupModelFilterSupplier,
                            /* thumbnailProvider= */ null,
                            /* actionOnRelatedTabs= */ false,
                            mActionConfirmationSupplier.get(),
                            mDataSharingTabManager,
                            /* gridCardOnClickListenerProvider= */ null,
                            /* dialogHandler= */ null,
                            TabProperties.TabActionState.UNSET,
                            /* selectionDelegateProvider= */ null,
                            /* priceWelcomeMessageControllerSupplier= */ null,
                            mTabListContainerView,
                            /* attachToParent= */ true,
                            COMPONENT_NAME,
                            onModelTokenChange,
                            /* hasEmptyView= */ false,
                            /* emptyImageResId= */ Resources.ID_NULL,
                            /* emptyHeadingStringResId= */ Resources.ID_NULL,
                            /* emptySubheadingStringResId= */ Resources.ID_NULL,
                            /* onTabGroupCreation= */ null,
                            mBackgroundColorSupplier,
                            /* allowDragAndDrop= */ false);
            mTabStripCoordinator.initWithNative(mTabModelSelector.getModel(false).getProfile());

            mModelChangeProcessor =
                    PropertyModelChangeProcessor.create(
                            mModel,
                            new TabGroupUiViewBinder.ViewHolder(
                                    mToolbarView, mTabStripCoordinator.getContainerView()),
                            TabGroupUiViewBinder::bind);

            // TODO(crbug.com/40631286): find a way to enable interactions between grid tab switcher
            //  and the dialog here.
            if (mScrimManager != null) {
                mTabGridDialogControllerSupplier =
                        LazyOneshotSupplier.fromSupplier(this::initTabGridDialogCoordinator);
            } else {
                mTabGridDialogControllerSupplier = null;
            }

            @Nullable SharedImageTilesCoordinator sharedImageTilesCoordinator = null;
            if (ChromeFeatureList.isEnabled(ChromeFeatureList.DATA_SHARING)) {
                DataSharingService dataSharingService =
                        DataSharingServiceFactory.getForProfile(
                                mTabModelSelector.getModel(/* incognito= */ false).getProfile());
                sharedImageTilesCoordinator =
                        new SharedImageTilesCoordinator(
                                activity,
                                SharedImageTilesType.DEFAULT,
                                new SharedImageTilesColor(SharedImageTilesColor.Style.DYNAMIC),
                                dataSharingService);
                FrameLayout container =
                        mToolbarView.findViewById(R.id.toolbar_image_tiles_container);
                TabUiUtils.attachSharedImageTilesCoordinatorToFrameLayout(
                        sharedImageTilesCoordinator, container);
            }

            mMediator =
                    new TabGroupUiMediator(
                            mActivity,
                            visibilityController,
                            mHandleBackPressChangedSupplier,
                            this,
                            mModel,
                            mTabModelSelector,
                            mTabContentManager,
                            mTabCreatorManager,
                            mLayoutStateProviderSupplier,
                            mTabGridDialogControllerSupplier,
                            mOmniboxFocusStateSupplier,
                            sharedImageTilesCoordinator,
                            mThemeColorProvider,
                            mBackgroundColorSupplier);

            Profile profile = mTabModelSelector.getModel(false).getProfile();
            CollaborationService collaborationService =
                    CollaborationServiceFactory.getForProfile(profile);
            @NonNull ServiceStatus serviceStatus = collaborationService.getServiceStatus();
            if (serviceStatus.isAllowedToJoin()) {
                mTabBubbler =
                        new TabBubbler(
                                profile,
                                mTabStripCoordinator.getTabListNotificationHandler(),
                                mCurrentTabGroupId);
            }
=======
            @NonNull Supplier<ShareDelegate> shareDelegateSupplier,
            @NonNull OneshotSupplier<OverviewModeBehavior> overviewModeBehaviorSupplier,
            @NonNull SnackbarManager snackbarManager) {
        mActivity = activity;
        mContext = parentView.getContext();
        mThemeColorProvider = themeColorProvider;
        mScrimCoordinator = scrimCoordinator;
        mOmniboxFocusStateSupplier = omniboxFocusStateSupplier;
        mModel = new PropertyModel(TabGroupUiProperties.ALL_KEYS);
        mToolbarView = (TabGroupUiToolbarView) LayoutInflater.from(mContext).inflate(
                R.layout.bottom_tab_strip_toolbar, parentView, false);
        mTabListContainerView = mToolbarView.getViewContainer();
        mBottomSheetController = bottomSheetController;
        mActivityLifecycleDispatcher = activityLifecycleDispatcher;
        mActivityLifecycleDispatcher.register(this);
        mIsWarmOnResumeSupplier = isWarmOnResumeSupplier;
        mTabModelSelector = tabModelSelector;
        mOverviewModeBehaviorSupplier = overviewModeBehaviorSupplier;
        mRootView = rootView;
        mSnackbarManager = snackbarManager;
        mShareDelegateSupplier = shareDelegateSupplier;
        mTabCreatorManager = tabCreatorManager;
        mDynamicResourceLoaderSupplier = dynamicResourceLoaderSupplier;
        mTabContentManager = tabContentManager;
        parentView.addView(mToolbarView);
    }

    /**
     * Handle any initialization that occurs once native has been loaded.
     */
    @Override
    public void initializeWithNative(Activity activity,
            BottomControlsCoordinator.BottomControlsVisibilityController visibilityController) {
        if (UmaSessionStats.isMetricsServiceAvailable()) {
            UmaSessionStats.registerSyntheticFieldTrial(
                    ChromeFeatureList.TAB_GROUPS_ANDROID + SYNTHETIC_TRIAL_POSTFIX,
                    "Downloaded_Enabled");
>>>>>>> chromium
        }

        boolean actionOnAllRelatedTabs = TabUiFeatureUtilities.isConditionalTabStripEnabled();
        mTabStripCoordinator = new TabListCoordinator(TabListCoordinator.TabListMode.STRIP,
                mContext, mTabModelSelector, null, null, actionOnAllRelatedTabs, null, null,
                TabProperties.UiType.STRIP, null, null, mTabListContainerView, true, COMPONENT_NAME,
                mRootView);
        mTabStripCoordinator.initWithNative(mDynamicResourceLoaderSupplier.get());

        mModelChangeProcessor = PropertyModelChangeProcessor.create(mModel,
                new TabGroupUiViewBinder.ViewHolder(
                        mToolbarView, mTabStripCoordinator.getContainerView()),
                TabGroupUiViewBinder::bind);

        // TODO(crbug.com/972217): find a way to enable interactions between grid tab switcher
        //  and the dialog here.
        TabGridDialogMediator.DialogController dialogController = null;
        if (TabUiFeatureUtilities.isTabGroupsAndroidEnabled(activity)
                && mScrimCoordinator != null) {
            mTabGridDialogCoordinator =
                    new TabGridDialogCoordinator(mActivity, mTabModelSelector, mTabContentManager,
                            mTabCreatorManager, mActivity.findViewById(R.id.coordinator), null,
                            null, null, mShareDelegateSupplier, mScrimCoordinator, mRootView);
            mTabGridDialogCoordinator.initWithNative(mContext, mTabModelSelector,
                    mTabContentManager, mTabStripCoordinator.getTabGroupTitleEditor());
            dialogController = mTabGridDialogCoordinator.getDialogController();
        }

        mMediator = new TabGroupUiMediator(mActivity, visibilityController, this, mModel,
                mTabModelSelector, mTabCreatorManager, mOverviewModeBehaviorSupplier,
                mThemeColorProvider, dialogController, mActivityLifecycleDispatcher,
                mSnackbarManager, mOmniboxFocusStateSupplier);

        TabGroupUtils.startObservingForCreationIPH();

        if (TabUiFeatureUtilities.isConditionalTabStripEnabled()) return;

        // TODO(meiliang): Potential leak if the observer is added after restoreCompleted. Fix it.
        // Record the group count after all tabs are being restored. This only happen once per life
        // cycle, therefore remove the observer after recording. We only focus on normal tab model
        // because we don't restore tabs in incognito tab model.
        mTabModelSelector.getModel(false).addObserver(new TabModelObserver() {
            @Override
            public void restoreCompleted() {
                recordTabGroupCount();
                recordSessionCount();
                mTabModelSelector.getModel(false).removeObserver(this);
            }
        });
    }

    /**
     * @return {@link Supplier} that provides dialog visibility.
     */
    @Override
    public Supplier<Boolean> getTabGridDialogVisibilitySupplier() {
        return mTabGridDialogCoordinator::isVisible;
    }

    /**
     * Handles a reset event originated from {@link TabGroupUiMediator} to reset the tab strip.
     *
     * @param tabs List of Tabs to reset.
     */
    @Override
    public void resetStripWithListOfTabs(List<Tab> tabs) {
        if (tabs != null && tabs.size() > 1
                && mBottomSheetController.getSheetState()
                        == BottomSheetController.SheetState.HIDDEN) {
            TabGroupUtils.maybeShowIPH(FeatureConstants.TAB_GROUPS_TAP_TO_SEE_ANOTHER_TAB_FEATURE,
                    mTabStripCoordinator.getContainerView(),
                    TabUiFeatureUtilities.isLaunchBugFixEnabled() ? mBottomSheetController : null);
        }
        mTabStripCoordinator.resetWithListOfTabs(tabs);
    }

    /**
     * Handles a reset event originated from {@link TabGroupUiMediator}
     * when the bottom sheet is expanded or the dialog is shown.
     *
     * @param tabs List of Tabs to reset.
     */
    @Override
    public void resetGridWithListOfTabs(List<Tab> tabs) {
<<<<<<< HEAD
        if (mTabGridDialogControllerSupplier != null) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.VANILLA_ICE_CREAM
                    && ChromeFeatureList.isEnabled(SensitiveContentFeatures.SENSITIVE_CONTENT)
                    && ChromeFeatureList.isEnabled(
                            SensitiveContentFeatures.SENSITIVE_CONTENT_WHILE_SWITCHING_TABS)) {
                TabUiUtils.updateViewContentSensitivityForTabs(
                        tabs,
                        mTabGridDialogControllerSupplier.get()::setGridContentSensitivity,
                        "SensitiveContent.TabSwitching.BottomTabStripGroupUI.Sensitivity");
            }
            mTabGridDialogControllerSupplier.get().resetWithListOfTabs(tabs);
=======
        if (mTabGridDialogCoordinator != null) {
            mTabGridDialogCoordinator.resetWithListOfTabs(tabs);
>>>>>>> chromium
        }
    }

    /**
     * TabGroupUi implementation.
     */
    @Override
    public boolean onBackPressed() {
        return mMediator.onBackPressed();
    }

    /**
     * Destroy any members that needs clean up.
     */
    @Override
    public void destroy() {
        // TODO(crbug.com/1208462): Add tests for destroy conditions.
        // Early return if the component hasn't initialized yet.
        if (mActivity == null) return;

        mTabStripCoordinator.onDestroy();
        if (mTabGridDialogCoordinator != null) {
            mTabGridDialogCoordinator.destroy();
        }
        mModelChangeProcessor.destroy();
        mMediator.destroy();
        if (mActivityLifecycleDispatcher != null) {
            mActivityLifecycleDispatcher.unregister(this);
        }
    }

    // PauseResumeWithNativeObserver implementation.
    @Override
    public void onResumeWithNative() {
        // Since we use AsyncTask for restoring tabs, this method can be called before or after
        // restoring all tabs. Therefore, we skip recording the count here during cold start and
        // record that elsewhere when TabModel emits the restoreCompleted signal.
        if (!mIsWarmOnResumeSupplier.get()) return;

        recordTabGroupCount();
        recordSessionCount();
    }

    private void recordTabGroupCount() {
        if (mTabModelSelector == null) return;
        TabModelFilterProvider provider = mTabModelSelector.getTabModelFilterProvider();

        if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
            TabModelFilter normalTabModelFilter = provider.getTabModelFilter(false);

            if (!(normalTabModelFilter instanceof TabGroupModelFilter)) {
                String actualType = normalTabModelFilter == null
                        ? "null"
                        : normalTabModelFilter.getClass().getName();
                assert false
                    : "Please file bug, this is unexpected. Expected TabGroupModelFilter, but was "
                      + actualType;

                return;
            }
        }

        TabGroupModelFilter normalFilter = (TabGroupModelFilter) provider.getTabModelFilter(false);
        TabGroupModelFilter incognitoFilter =
                (TabGroupModelFilter) provider.getTabModelFilter(true);
        int groupCount = normalFilter.getTabGroupCount() + incognitoFilter.getTabGroupCount();
        RecordHistogram.recordCountHistogram("TabGroups.UserGroupCount", groupCount);
        if (TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(mContext)) {
            int namedGroupCount = 0;
            for (int i = 0; i < normalFilter.getTabGroupCount(); i++) {
                int rootId = CriticalPersistedTabData.from(normalFilter.getTabAt(i)).getRootId();
                if (TabGroupUtils.getTabGroupTitle(rootId) != null) {
                    namedGroupCount += 1;
                }
            }
            for (int i = 0; i < incognitoFilter.getTabGroupCount(); i++) {
                int rootId = CriticalPersistedTabData.from(incognitoFilter.getTabAt(i)).getRootId();
                if (TabGroupUtils.getTabGroupTitle(rootId) != null) {
                    namedGroupCount += 1;
                }
            }
            RecordHistogram.recordCountHistogram("TabGroups.UserNamedGroupCount", namedGroupCount);
        }
    }

    private void recordSessionCount() {
        if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
            TabModelFilter normalTabModelFilter =
                    mTabModelSelector.getTabModelFilterProvider().getTabModelFilter(false);

            if (!(normalTabModelFilter instanceof TabGroupModelFilter)) {
                String actualType = normalTabModelFilter == null
                        ? "null"
                        : normalTabModelFilter.getClass().getName();
                assert false
                    : "Please file bug, this is unexpected. Expected TabGroupModelFilter, but was "
                      + actualType;

                return;
            }
        }

        OverviewModeBehavior overviewModeBehavior = mOverviewModeBehaviorSupplier.get();
        if (overviewModeBehavior != null && overviewModeBehavior.overviewVisible()) {
            return;
        }

        Tab currentTab = mTabModelSelector.getCurrentTab();
        if (currentTab == null) return;
        TabModelFilterProvider provider = mTabModelSelector.getTabModelFilterProvider();
        ((TabGroupModelFilter) provider.getCurrentTabModelFilter()).recordSessionsCount(currentTab);
    }

    @Override
    public void onPauseWithNative() {}

    // TabGroupUiController implementation.
    @Override
    public void setupLeftButtonDrawable(int drawableId) {
        mMediator.setupLeftButtonDrawable(drawableId);
    }

    @Override
    public void setupLeftButtonOnClickListener(View.OnClickListener listener) {
        mMediator.setupLeftButtonOnClickListener(listener);
    }
}
