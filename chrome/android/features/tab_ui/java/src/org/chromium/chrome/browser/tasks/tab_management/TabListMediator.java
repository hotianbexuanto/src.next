// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tasks.tab_management;

import static org.chromium.chrome.browser.tasks.tab_management.MessageCardViewProperties.MESSAGE_TYPE;
import static org.chromium.chrome.browser.tasks.tab_management.TabListModel.CardProperties.CARD_ALPHA;
import static org.chromium.chrome.browser.tasks.tab_management.TabListModel.CardProperties.CARD_TYPE;
import static org.chromium.chrome.browser.tasks.tab_management.TabListModel.CardProperties.ModelType.TAB;
<<<<<<< HEAD
import static org.chromium.chrome.browser.tasks.tab_management.TabProperties.TAB_GROUP_COLOR_VIEW_PROVIDER;
import static org.chromium.chrome.browser.tasks.tab_management.TabProperties.TAB_ID;
import static org.chromium.chrome.browser.tasks.tab_management.TabProperties.THUMBNAIL_FETCHER;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.animation.ObjectAnimator;
import android.app.Activity;
import android.content.ComponentCallbacks;
=======
import static org.chromium.chrome.browser.tasks.tab_management.TabProperties.CLOSE_BUTTON_DESCRIPTION_STRING;

import android.app.Activity;
import android.content.ComponentCallbacks;
import android.content.Context;
import android.content.res.ColorStateList;
>>>>>>> chromium
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.text.TextUtils;
import android.util.Pair;
import android.view.View;
import android.view.accessibility.AccessibilityNodeInfo;
import android.view.accessibility.AccessibilityNodeInfo.AccessibilityAction;

import androidx.annotation.IntDef;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;
import androidx.appcompat.content.res.AppCompatResources;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.ItemTouchHelper;

import org.chromium.base.Callback;
import org.chromium.base.Log;
import org.chromium.base.metrics.RecordHistogram;
import org.chromium.base.metrics.RecordUserAction;
<<<<<<< HEAD
import org.chromium.base.shared_preferences.SharedPreferencesManager;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.Supplier;
import org.chromium.chrome.browser.collaboration.CollaborationServiceFactory;
import org.chromium.chrome.browser.data_sharing.DataSharingServiceFactory;
import org.chromium.chrome.browser.data_sharing.DataSharingTabManager;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.preferences.ChromePreferenceKeys;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.price_tracking.PriceTrackingFeatures;
import org.chromium.chrome.browser.price_tracking.PriceTrackingUtilities;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.quick_delete.QuickDeleteAnimationGradientDrawable;
=======
import org.chromium.base.task.PostTask;
import org.chromium.chrome.browser.compositor.layouts.content.TabContentManager;
import org.chromium.chrome.browser.multiwindow.MultiWindowUtils;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.search_engines.TemplateUrlServiceFactory;
>>>>>>> chromium
import org.chromium.chrome.browser.tab.EmptyTabObserver;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabCreationState;
import org.chromium.chrome.browser.tab.TabLaunchType;
import org.chromium.chrome.browser.tab.TabObserver;
import org.chromium.chrome.browser.tab.TabSelectionType;
import org.chromium.chrome.browser.tab.state.ShoppingPersistedTabData;
<<<<<<< HEAD
import org.chromium.chrome.browser.tab_group_sync.TabGroupSyncFeatures;
import org.chromium.chrome.browser.tab_group_sync.TabGroupSyncServiceFactory;
import org.chromium.chrome.browser.tab_ui.TabListFaviconProvider;
import org.chromium.chrome.browser.tab_ui.TabListFaviconProvider.TabFaviconFetcher;
import org.chromium.chrome.browser.tab_ui.ThumbnailProvider;
import org.chromium.chrome.browser.tabmodel.TabClosureParams;
import org.chromium.chrome.browser.tabmodel.TabGroupColorUtils;
import org.chromium.chrome.browser.tabmodel.TabGroupModelFilter;
import org.chromium.chrome.browser.tabmodel.TabGroupModelFilterObserver;
import org.chromium.chrome.browser.tabmodel.TabGroupTitleUtils;
import org.chromium.chrome.browser.tabmodel.TabGroupUtils;
import org.chromium.chrome.browser.tabmodel.TabList;
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelActionListener;
=======
import org.chromium.chrome.browser.tab.state.StorePersistedTabData;
import org.chromium.chrome.browser.tabmodel.EmptyTabModelFilter;
import org.chromium.chrome.browser.tabmodel.TabList;
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelFilter;
>>>>>>> chromium
import org.chromium.chrome.browser.tabmodel.TabModelObserver;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tabmodel.TabModelUtils;
<<<<<<< HEAD
=======
import org.chromium.chrome.browser.tasks.pseudotab.PseudoTab;
import org.chromium.chrome.browser.tasks.pseudotab.TabAttributeCache;
import org.chromium.chrome.browser.tasks.tab_groups.EmptyTabGroupModelFilterObserver;
import org.chromium.chrome.browser.tasks.tab_groups.TabGroupModelFilter;
import org.chromium.chrome.browser.tasks.tab_groups.TabGroupUtils;
>>>>>>> chromium
import org.chromium.chrome.browser.tasks.tab_management.PriceMessageService.PriceTabData;
import org.chromium.chrome.browser.tasks.tab_management.TabListCoordinator.TabListMode;
import org.chromium.chrome.browser.tasks.tab_management.TabProperties.UiType;
import org.chromium.chrome.browser.tasks.tab_management.TabSwitcherMediator.PriceWelcomeMessageController;
import org.chromium.chrome.tab_ui.R;
import org.chromium.components.browser_ui.widget.selectable_list.SelectionDelegate;
import org.chromium.components.embedder_support.util.UrlUtilities;
<<<<<<< HEAD
import org.chromium.components.tab_group_sync.TabGroupSyncService;
import org.chromium.components.tab_groups.TabGroupColorId;
=======
import org.chromium.components.feature_engagement.FeatureConstants;
import org.chromium.components.search_engines.TemplateUrlService;
import org.chromium.content_public.browser.LoadUrlParams;
import org.chromium.content_public.browser.NavigationController;
>>>>>>> chromium
import org.chromium.content_public.browser.NavigationHandle;
import org.chromium.content_public.browser.NavigationHistory;
import org.chromium.content_public.browser.UiThreadTaskTraits;
import org.chromium.ui.base.PageTransition;
import org.chromium.ui.modelutil.ListObservable;
import org.chromium.ui.modelutil.ListObservable.ListObserver;
import org.chromium.ui.modelutil.PropertyModel;
import org.chromium.ui.modelutil.SimpleRecyclerViewAdapter;
import org.chromium.url.GURL;
import org.chromium.base.ContextUtils;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.ArrayList;
<<<<<<< HEAD
=======
import java.util.Collections;
import java.util.Comparator;
>>>>>>> chromium
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Mediator for business logic for the tab grid. This class should be initialized with a list of
 * tabs and a TabModel to observe for changes and should not have any logic around what the list
 * signifies.
 * TODO(yusufo): Move some of the logic here to a parent component to make the above true.
 */
class TabListMediator {
    // Comparator to sort Tabs in descending order of the last shown time.
    private static final Comparator<PseudoTab> LAST_SHOWN_COMPARATOR =
            (a, b) -> (Long.compare(b.getTimestampMillis(), a.getTimestampMillis()));

    private boolean mVisible;
    private boolean mShownIPH;

    /**
     * An interface to get the thumbnails to be shown inside the tab grid cards.
     */
    public interface ThumbnailProvider {
        /**
         * @see TabContentManager#getTabThumbnailWithCallback
         */
        void getTabThumbnailWithCallback(
                int tabId, Callback<Bitmap> callback, boolean forceUpdate, boolean writeToCache);
    }

    /**
     * An interface to handle requests about updating TabGridDialog.
     */
    public interface TabGridDialogHandler {
        /**
         * This method updates the status of the ungroup bar in TabGridDialog.
         *
         * @param status The status in {@link TabGridDialogView.UngroupBarStatus} that the ungroup
         *         bar should be updated to.
         */
        void updateUngroupBarStatus(@TabGridDialogView.UngroupBarStatus int status);

        /**
         * This method updates the content of the TabGridDialog.
         *
         * @param tabId The id of the {@link Tab} that is used to update TabGridDialog.
         */
        void updateDialogContent(int tabId);
    }

    /**
     * An interface to expose functionality needed to support reordering in grid layouts in
     * accessibility mode.
     */
    public interface TabGridAccessibilityHelper {
        /**
         * This method gets the possible actions for reordering a tab in grid layout.
         *
         * @param view The host view that triggers the accessibility action.
         * @return The list of possible {@link AccessibilityAction}s for host view.
         */
        List<AccessibilityAction> getPotentialActionsForView(View view);

        /**
         * This method gives the previous and target position of current reordering based on the
         * host view and current action.
         *
         * @param view   The host view that triggers the accessibility action.
         * @param action The id of the action.
         * @return {@link Pair} that contains previous and target position of this action.
         */
        Pair<Integer, Integer> getPositionsOfReorderAction(View view, int action);

        /**
         * This method returns whether the given action is a type of the reordering actions.
         *
         * @param action The accessibility action.
         * @return Whether the given action is a reordering action.
         */
        boolean isReorderAction(int action);
    }

    /**
     * Provides capability to asynchronously acquire {@link ShoppingPersistedTabData}
     */
    static class ShoppingPersistedTabDataFetcher {
        protected Tab mTab;
        protected PriceWelcomeMessageController mPriceWelcomeMessageController;

        /**
         * @param tab {@link Tab} {@link ShoppingPersistedTabData} will be acquired for.
         * @param priceWelcomeMessageController to show the price welcome message.
         */
        ShoppingPersistedTabDataFetcher(
                Tab tab, @Nullable PriceWelcomeMessageController priceWelcomeMessageController) {
            mTab = tab;
            mPriceWelcomeMessageController = priceWelcomeMessageController;
        }

        /**
         * Asynchronously acquire {@link ShoppingPersistedTabData}
         * @param callback {@link Callback} to pass {@link ShoppingPersistedTabData} back in
         */
        public void fetch(Callback<ShoppingPersistedTabData> callback) {
            ShoppingPersistedTabData.from(mTab, (res) -> {
                callback.onResult(res);
                maybeShowPriceWelcomeMessage(res);
            });
        }

        @VisibleForTesting
        void maybeShowPriceWelcomeMessage(
                @Nullable ShoppingPersistedTabData shoppingPersistedTabData) {
            // Avoid inserting message while RecyclerView is computing a layout.
            new Handler().post(() -> {
                if (!PriceTrackingUtilities.isPriceWelcomeMessageCardEnabled()
                        || (mPriceWelcomeMessageController == null)
                        || (shoppingPersistedTabData == null)
                        || (shoppingPersistedTabData.getPriceDrop() == null)) {
                    return;
                }
                mPriceWelcomeMessageController.showPriceWelcomeMessage(
                        new PriceTabData(mTab.getId(), shoppingPersistedTabData.getPriceDrop()));
            });
        }
    }

    /**
     * Provides capability to asynchronously acquire {@link StorePersistedTabData}
     */
    static class StorePersistedTabDataFetcher {
        protected Tab mTab;

        /**
         * @param tab {@link Tab} {@link StorePersistedTabData} will be acquired for.
         */
        StorePersistedTabDataFetcher(Tab tab) {
            mTab = tab;
        }

        /**
         * Asynchronously acquire {@link StorePersistedTabData}
         * @param callback {@link Callback} to pass {@link StorePersistedTabData} back in
         */
        public void fetch(Callback<StorePersistedTabData> callback) {
            StorePersistedTabData.from(mTab, (res) -> { callback.onResult(res); });
        }
    }

    /**
     * The object to set to {@link TabProperties#THUMBNAIL_FETCHER} for the TabGridViewBinder to
     * obtain the thumbnail asynchronously.
     */
    static class ThumbnailFetcher {
        static Callback<Bitmap> sBitmapCallbackForTesting;
        static int sFetchCountForTesting;
        private ThumbnailProvider mThumbnailProvider;
        private int mId;
        private boolean mForceUpdate;
        private boolean mWriteToCache;

        ThumbnailFetcher(
                ThumbnailProvider provider, int id, boolean forceUpdate, boolean writeToCache) {
            mThumbnailProvider = provider;
            mId = id;
            mForceUpdate = forceUpdate;
            mWriteToCache = writeToCache;
        }

        void fetch(Callback<Bitmap> callback) {
            Callback<Bitmap> forking = (bitmap) -> {
                if (sBitmapCallbackForTesting != null) sBitmapCallbackForTesting.onResult(bitmap);
                callback.onResult(bitmap);
            };
            sFetchCountForTesting++;
            mThumbnailProvider.getTabThumbnailWithCallback(
                    mId, forking, mForceUpdate, mWriteToCache);
        }
    }

    /**
     * An interface to show IPH for a tab.
     */
    public interface IphProvider { void showIPH(View anchor); }

    private final IphProvider mIphProvider = new IphProvider() {
        private static final int IPH_DELAY_MS = 1000;

        @Override
        public void showIPH(View anchor) {
            if (mShownIPH) return;
            mShownIPH = true;

            new Handler().postDelayed(
                    ()
                            -> TabGroupUtils.maybeShowIPH(
                                    FeatureConstants.TAB_GROUPS_YOUR_TABS_ARE_TOGETHER_FEATURE,
                                    anchor, null),
                    IPH_DELAY_MS);
        }
    };

    /**
     * An interface to get a SelectionDelegate that contains the selected items for a selectable
     * tab list.
     */
    public interface SelectionDelegateProvider { SelectionDelegate getSelectionDelegate(); }

    /**
     * An interface to get the onClickListener when clicking on a grid card.
     */
    interface GridCardOnClickListenerProvider {
        /**
         * @return {@link TabActionListener} to open Tab Grid dialog.
         * If the given {@link Tab} is not able to create group, return null;
         */
        @Nullable
        TabActionListener openTabGridDialog(@NonNull Tab tab);

        /**
         * Run additional actions on tab selection.
         * @param tabId The ID of selected {@link Tab}.
         * @param fromActionButton Whether it is called from the Action button on the card.
         */
        void onTabSelecting(int tabId, boolean fromActionButton);
    }

    @IntDef({TabClosedFrom.TAB_STRIP, TabClosedFrom.GRID_TAB_SWITCHER,
            TabClosedFrom.GRID_TAB_SWITCHER_GROUP})
    @Retention(RetentionPolicy.SOURCE)
    private @interface TabClosedFrom {
        int TAB_STRIP = 0;
        // int TAB_GRID_SHEET = 1;  // Obsolete
        int GRID_TAB_SWITCHER = 2;
        int GRID_TAB_SWITCHER_GROUP = 3;
        int NUM_ENTRIES = 4;
    }

    private static final String TAG = "TabListMediator";
    private static Map<Integer, Integer> sTabClosedFromMapTabClosedFromMap = new HashMap<>();

<<<<<<< HEAD
    private final ValueChangedCallback<TabGroupModelFilter> mOnTabGroupModelFilterChanged =
            new ValueChangedCallback<>(this::onTabGroupModelFilterChanged);
    private final TabListGroupMenuCoordinator.OnItemClickedCallback mOnMenuItemClickedCallback =
            this::onMenuItemClicked;
    private final Activity mActivity;
    private final TabListModel mModelList;
=======
    private final Context mContext;
    private final TabListModel mModel;
>>>>>>> chromium
    private final @TabListMode int mMode;
    private final TabModelSelector mTabModelSelector;
    private final TabActionListener mTabClosedListener;
    private final PseudoTab.TitleProvider mTitleProvider;
    private final SelectionDelegateProvider mSelectionDelegateProvider;
    private final GridCardOnClickListenerProvider mGridCardOnClickListenerProvider;
    private final TabGridDialogHandler mTabGridDialogHandler;
<<<<<<< HEAD
    private final Supplier<PriceWelcomeMessageController> mPriceWelcomeMessageControllerSupplier;
    private final @Nullable ActionConfirmationManager mActionConfirmationManager;
    private final @Nullable DataSharingTabManager mDataSharingTabManager;
    private final Runnable mOnTabGroupCreation;
    private final TabModelObserver mTabModelObserver;
    private final TabActionListener mTabClosedListener;
    private final TabGridItemTouchHelperCallback mTabGridItemTouchHelperCallback;
=======
    private final String mComponentName;
    private final TabListFaviconProvider mTabListFaviconProvider;
    private final PriceWelcomeMessageController mPriceWelcomeMessageController;
>>>>>>> chromium

    private ThumbnailProvider mThumbnailProvider;
    private boolean mActionsOnAllRelatedTabs;
    private ComponentCallbacks mComponentCallbacks;
    private TabGridItemTouchHelperCallback mTabGridItemTouchHelperCallback;
    private int mNextTabId = Tab.INVALID_TAB_ID;
    private @UiType int mUiType;
    private int mSearchChipIconDrawableId;
    private GridLayoutManager mGridLayoutManager;
<<<<<<< HEAD
    // Set to true after a `resetWithListOfTabs` that used a non-null list of tabs. Remains true
    // until `postHiding` is invoked or the mediator is destroyed. While true, this mediator is
    // actively tracking updates to a TabModel.
    private boolean mShowingTabs;
    private Tab mTabToAddDelayed;
    private RecyclerViewItemAnimationToggle mRecyclerViewItemAnimationToggle;
    private ListObserver<Void> mListObserver;
=======

    private final TabActionListener mTabSelectedListener = new TabActionListener() {
        @Override
        public void run(int tabId) {
            if (mModel.indexFromId(tabId) == TabModel.INVALID_TAB_INDEX) return;

            mNextTabId = tabId;

            if (!mActionsOnAllRelatedTabs || TabUiFeatureUtilities.isConditionalTabStripEnabled()) {
                Tab currentTab = mTabModelSelector.getCurrentTab();
                Tab newlySelectedTab =
                        TabModelUtils.getTabById(mTabModelSelector.getCurrentModel(), tabId);

                // We filtered the tab switching related metric for components that takes actions on
                // all related tabs (e.g. GTS) because that component can switch to different
                // TabModel before switching tabs, while this class only contains information for
                // all tabs that are in the same TabModel, more specifically:
                //   * For Tabs.TabOffsetOfSwitch, we do not want to log anything if the user
                //     switched from normal to incognito or vice-versa.
                //   * For MobileTabSwitched, as compared to the VTS, we need to account for
                //     MobileTabReturnedToCurrentTab action. This action is defined as return to the
                //     same tab as before entering the component, and we don't have this information
                //     here.
                recordUserSwitchedTab(currentTab, newlySelectedTab);
            }
            if (mGridCardOnClickListenerProvider != null) {
                mGridCardOnClickListenerProvider.onTabSelecting(
                        tabId, true /* fromActiionButton */);
            } else {
                mTabModelSelector.getCurrentModel().setIndex(
                        TabModelUtils.getTabIndexById(mTabModelSelector.getCurrentModel(), tabId),
                        TabSelectionType.FROM_USER);
            }
        }

        /**
         * Records MobileTabSwitched for the component. Also, records Tabs.TabOffsetOfSwitch but
         * only when fromTab and toTab are within the same group. This method only records UMA
         * for components other than TabSwitcher.
         *
         * @param fromTab The previous selected tab.
         * @param toTab The new selected tab.
         */
        private void recordUserSwitchedTab(Tab fromTab, Tab toTab) {
            int fromFilterIndex = mTabModelSelector.getTabModelFilterProvider()
                                          .getCurrentTabModelFilter()
                                          .indexOf(fromTab);
            int toFilterIndex = mTabModelSelector.getTabModelFilterProvider()
                                        .getCurrentTabModelFilter()
                                        .indexOf(toTab);

            RecordUserAction.record("MobileTabSwitched." + mComponentName);
            if (PriceTrackingUtilities.isTrackPricesOnTabsEnabled()
                    && TabSwitcherCoordinator.COMPONENT_NAME.equals(mComponentName)) {
                RecordUserAction.record("Commerce.TabGridSwitched."
                        + (ShoppingPersistedTabData.hasPriceDrop(toTab) ? "HasPriceDrop"
                                                                        : "NoPriceDrop"));
            }
            if (TabUiFeatureUtilities.isConditionalTabStripEnabled()) {
                assert fromFilterIndex != toFilterIndex;
                RecordHistogram.recordSparseHistogram("Tabs.TabOffsetOfSwitch." + mComponentName,
                        fromFilterIndex - toFilterIndex);
                return;
            }

            if (fromFilterIndex != toFilterIndex) return;

            int fromIndex = TabModelUtils.getTabIndexById(
                    mTabModelSelector.getCurrentModel(), fromTab.getId());
            int toIndex = TabModelUtils.getTabIndexById(
                    mTabModelSelector.getCurrentModel(), toTab.getId());

            RecordHistogram.recordSparseHistogram(
                    "Tabs.TabOffsetOfSwitch." + mComponentName, fromIndex - toIndex);
        }
    };

    private final TabActionListener mSelectableTabOnClickListener = new TabActionListener() {
        @Override
        public void run(int tabId) {
            int index = mModel.indexFromId(tabId);
            if (index == TabModel.INVALID_TAB_INDEX) return;
            boolean selected = mModel.get(index).model.get(TabProperties.IS_SELECTED);
            if (selected) {
                RecordUserAction.record("TabMultiSelect.TabUnselected");
            } else {
                RecordUserAction.record("TabMultiSelect.TabSelected");
            }
            mModel.get(index).model.set(TabProperties.IS_SELECTED, !selected);
        }
    };

    private final TabObserver mTabObserver = new EmptyTabObserver() {
        @Override
        public void onDidStartNavigation(Tab tab, NavigationHandle navigationHandle) {
            if (UrlUtilities.isNTPUrl(tab.getUrl())) return;
            if (navigationHandle.isSameDocument() || !navigationHandle.isInPrimaryMainFrame()) {
                return;
            }
            if (mModel.indexFromId(tab.getId()) == TabModel.INVALID_TAB_INDEX) return;
            mModel.get(mModel.indexFromId(tab.getId()))
                    .model.set(TabProperties.FAVICON,
                            mTabListFaviconProvider.getDefaultFaviconDrawable(tab.isIncognito()));
        }

        @Override
        public void onTitleUpdated(Tab updatedTab) {
            int index = mModel.indexFromId(updatedTab.getId());
            // TODO(crbug.com/1098100) The null check for tab here should be redundant once we have
            // resolved the bug.
            if (index == TabModel.INVALID_TAB_INDEX
                    || mTabModelSelector.getTabById(updatedTab.getId()) == null) {
                return;
            }
            mModel.get(index).model.set(
                    TabProperties.TITLE, getLatestTitleForTab(PseudoTab.fromTab(updatedTab)));
        }

        @Override
        public void onFaviconUpdated(Tab updatedTab, Bitmap icon) {
            updateFaviconForTab(PseudoTab.fromTab(updatedTab), icon);
        }

        @Override
        public void onUrlUpdated(Tab tab) {
            if (!TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(mContext)) return;
            int index = mModel.indexFromId(tab.getId());

            if (index == TabModel.INVALID_TAB_INDEX && mActionsOnAllRelatedTabs) {
                Tab currentGroupSelectedTab =
                        TabGroupUtils.getSelectedTabInGroupForTab(mTabModelSelector, tab);
                if (currentGroupSelectedTab == null) return;
                index = mModel.indexFromId(currentGroupSelectedTab.getId());
            }

            if (index == TabModel.INVALID_TAB_INDEX) return;
            mModel.get(index).model.set(TabProperties.URL_DOMAIN, getDomainForTab(tab));
        }
    };

    private final TabModelObserver mTabModelObserver;

    private ListObserver<Void> mListObserver;

    private @Nullable TemplateUrlService.TemplateUrlServiceObserver mTemplateUrlObserver;

    private TabGroupTitleEditor mTabGroupTitleEditor;

    private TabGroupModelFilter.Observer mTabGroupObserver;

>>>>>>> chromium
    private View.AccessibilityDelegate mAccessibilityDelegate;

    /**
     * Interface for implementing a {@link Runnable} that takes a tabId for a generic action.
     */
    public interface TabActionListener { void run(int tabId); }

    /**
     * Construct the Mediator with the given Models and observing hooks from the given
     * ChromeActivity.
     * @param context The context used to get some configuration information.
     * @param model The Model to keep state about a list of {@link Tab}s.
     * @param mode The {@link TabListMode}
     * @param tabModelSelector {@link TabModelSelector} that will provide and receive signals about
     *                                                 the tabs concerned.
     * @param thumbnailProvider {@link ThumbnailProvider} to provide screenshot related details.
     * @param titleProvider {@link PseudoTab.TitleProvider} for a given tab's title to show.
     * @param tabListFaviconProvider Provider for all favicon related drawables.
     * @param actionOnRelatedTabs Whether tab-related actions should be operated on all related
     *                            tabs.
     * @param selectionDelegateProvider Provider for a {@link SelectionDelegate} that is used for
     *                                  a selectable list. It's null when selection is not possible.
     * @param gridCardOnClickListenerProvider Provides the onClickListener for opening dialog when
     *                                        click on a grid card.
     * @param dialogHandler A handler to handle requests about updating TabGridDialog.
     * @param priceWelcomeMessageController A controller to show PriceWelcomeMessage.
     * @param componentName This is a unique string to identify different components.
     * @param uiType The type of UI this mediator should be building.
     */
    public TabListMediator(Context context, TabListModel model, @TabListMode int mode,
            TabModelSelector tabModelSelector, @Nullable ThumbnailProvider thumbnailProvider,
            @Nullable PseudoTab.TitleProvider titleProvider,
            TabListFaviconProvider tabListFaviconProvider, boolean actionOnRelatedTabs,
            @Nullable SelectionDelegateProvider selectionDelegateProvider,
            @Nullable GridCardOnClickListenerProvider gridCardOnClickListenerProvider,
            @Nullable TabGridDialogHandler dialogHandler,
            @Nullable PriceWelcomeMessageController priceWelcomeMessageController,
            String componentName, @UiType int uiType) {
/*
        if (ContextUtils.getAppSharedPreferences().getString("active_tabswitcher", "default").equals("list"))
          mode = TabListMode.LIST;
        if (ContextUtils.getAppSharedPreferences().getString("active_tabswitcher", "default").equals("classic") || ContextUtils.getAppSharedPreferences().getString("active_tabswitcher", "default").equals("grid"))
          mode = TabListMode.GRID;
*/
        mContext = context;
        mTabModelSelector = tabModelSelector;
        mThumbnailProvider = thumbnailProvider;
        mModel = model;
        mMode = mode;
        mTabListFaviconProvider = tabListFaviconProvider;
        mComponentName = componentName;
        mTitleProvider = titleProvider;
        mSelectionDelegateProvider = selectionDelegateProvider;
        mGridCardOnClickListenerProvider = gridCardOnClickListenerProvider;
        mTabGridDialogHandler = dialogHandler;
        mActionsOnAllRelatedTabs = actionOnRelatedTabs;
        mUiType = uiType;
        mPriceWelcomeMessageController = priceWelcomeMessageController;

        mTabModelObserver = new TabModelObserver() {
            @Override
            public void didSelectTab(Tab tab, int type, int lastId) {
                mNextTabId = Tab.INVALID_TAB_ID;
                if (tab.getId() == lastId) return;
                int oldIndex = mModel.indexFromId(lastId);
                if (oldIndex != TabModel.INVALID_TAB_INDEX) {
                    mModel.get(oldIndex).model.set(TabProperties.IS_SELECTED, false);
                }
                int newIndex = mModel.indexFromId(tab.getId());
                if (newIndex == TabModel.INVALID_TAB_INDEX) return;

                mModel.get(newIndex).model.set(TabProperties.IS_SELECTED, true);
            }

            @Override
            public void tabClosureUndone(Tab tab) {
                onTabAdded(tab, !mActionsOnAllRelatedTabs);
                if (TabUiFeatureUtilities.isConditionalTabStripEnabled()) {
                    mTabModelSelector.getCurrentModel().setIndex(
                            TabModelUtils.getTabIndexById(
                                    mTabModelSelector.getCurrentModel(), tab.getId()),
                            TabSelectionType.FROM_USER);
                }
                if (sTabClosedFromMapTabClosedFromMap.containsKey(tab.getId())) {
                    @TabClosedFrom
                    int from = sTabClosedFromMapTabClosedFromMap.get(tab.getId());
                    switch (from) {
                        case TabClosedFrom.TAB_STRIP:
                            RecordUserAction.record("TabStrip.UndoCloseTab");
                            break;
                        case TabClosedFrom.GRID_TAB_SWITCHER:
                            RecordUserAction.record("GridTabSwitch.UndoCloseTab");
                            break;
                        case TabClosedFrom.GRID_TAB_SWITCHER_GROUP:
                            RecordUserAction.record("GridTabSwitcher.UndoCloseTabGroup");
                            break;
                        default:
                            assert false
                                : "tabClosureUndone for tab that closed from an unknown UI";
                    }
                    sTabClosedFromMapTabClosedFromMap.remove(tab.getId());
                }
                // TODO(yuezhanggg): clean up updateTab() calls in this class.
                if (mActionsOnAllRelatedTabs) {
                    TabModelFilter filter = mTabModelSelector.getTabModelFilterProvider()
                                                    .getCurrentTabModelFilter();
                    int filterIndex = filter.indexOf(tab);
                    if (filterIndex == TabList.INVALID_TAB_INDEX
                            || getRelatedTabsForId(tab.getId()).size() == 1
                            || filterIndex >= mModel.size()) {
                        return;
                    }
                    Tab currentGroupSelectedTab = filter.getTabAt(filterIndex);

                    int tabListModelIndex = mModel.indexOfNthTabCard(filterIndex);
                    assert mModel.indexFromId(currentGroupSelectedTab.getId()) == tabListModelIndex;

                    updateTab(tabListModelIndex, PseudoTab.fromTab(currentGroupSelectedTab),
                            mModel.get(tabListModelIndex).model.get(TabProperties.IS_SELECTED),
                            false, false);
                }
            }

            @Override
            public void didAddTab(
                    Tab tab, @TabLaunchType int type, @TabCreationState int creationState) {
                if (!mTabModelSelector.isTabStateInitialized()) return;
                onTabAdded(tab, !mActionsOnAllRelatedTabs);
                if (type == TabLaunchType.FROM_RESTORE && mActionsOnAllRelatedTabs) {
                    // When tab is restored after restoring stage (e.g. exiting multi-window mode,
                    // switching between dark/light mode in incognito), we need to update related
                    // property models.
                    TabModelFilter filter = mTabModelSelector.getTabModelFilterProvider()
                                                    .getCurrentTabModelFilter();
                    int filterIndex = filter.indexOf(tab);
                    if (filterIndex == TabList.INVALID_TAB_INDEX) return;
                    Tab currentGroupSelectedTab = filter.getTabAt(filterIndex);
                    // TabModel and TabListModel may be in the process of syncing up through
                    // restoring. Examples of this situation are switching between light/dark mode
                    // in incognito, exiting multi-window mode, etc.
                    int tabListModelIndex = mModel.indexOfNthTabCard(filterIndex);
                    if (mModel.indexFromId(currentGroupSelectedTab.getId()) != tabListModelIndex) {
                        return;
                    }
                    updateTab(tabListModelIndex, PseudoTab.fromTab(currentGroupSelectedTab),
                            mModel.get(tabListModelIndex).model.get(TabProperties.IS_SELECTED),
                            false, false);
                }
            }

            @Override
            public void willCloseTab(Tab tab, boolean animate) {
                if (mModel.indexFromId(tab.getId()) == TabModel.INVALID_TAB_INDEX) return;
                tab.removeObserver(mTabObserver);
                mModel.removeAt(mModel.indexFromId(tab.getId()));
            }

            @Override
            public void didMoveTab(Tab tab, int newIndex, int curIndex) {
                if (mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter()
                                instanceof TabGroupModelFilter) {
                    return;
                }
                onTabMoved(mModel.indexOfNthTabCard(newIndex), mModel.indexOfNthTabCard(curIndex));
            }

            @Override
            public void tabRemoved(Tab tab) {
                if (mModel.indexFromId(tab.getId()) == TabModel.INVALID_TAB_INDEX) return;
                mModel.removeAt(mModel.indexFromId(tab.getId()));
            }
        };

        // TODO(meiliang): follow up with unit tests to test the close signal is sent correctly with
        // the recommendedNextTab.
        mTabClosedListener = new TabActionListener() {
            @Override
            public void run(int tabId) {
                // TODO(crbug.com/990698): Consider disabling all touch events during animation.
                if (mModel.indexFromId(tabId) == TabModel.INVALID_TAB_INDEX) return;
                Tab closingTab =
                        TabModelUtils.getTabById(mTabModelSelector.getCurrentModel(), tabId);
                if (closingTab == null) return;

                RecordUserAction.record("MobileTabClosed." + mComponentName);

                if (mActionsOnAllRelatedTabs) {
                    List<Tab> related = getRelatedTabsForId(tabId);
                    if (related.size() > 1) {
                        onGroupClosedFrom(tabId);
                        mTabModelSelector.getCurrentModel().closeMultipleTabs(related, true);
                        return;
                    }
                }
                onTabClosedFrom(tabId, mComponentName);

                Tab currentTab = mTabModelSelector.getCurrentTab();
                Tab nextTab = currentTab == closingTab ? getNextTab(tabId) : null;

                mTabModelSelector.getCurrentModel().closeTab(
                        closingTab, nextTab, false, false, true);
            }

            private Tab getNextTab(int closingTabId) {
                int closingTabIndex = mModel.indexFromId(closingTabId);

                if (closingTabIndex == TabModel.INVALID_TAB_INDEX) {
                    assert false;
                    return null;
                }

                int nextTabId = Tab.INVALID_TAB_ID;
                if (mModel.size() > 1) {
                    int nextTabIndex = closingTabIndex == 0
                            ? mModel.getTabIndexAfter(closingTabIndex)
                            : mModel.getTabIndexBefore(closingTabIndex);
                    nextTabId = nextTabIndex == TabModel.INVALID_TAB_INDEX
                            ? Tab.INVALID_TAB_ID
                            : mModel.get(nextTabIndex).model.get(TabProperties.TAB_ID);
                }

                return TabModelUtils.getTabById(mTabModelSelector.getCurrentModel(), nextTabId);
            }
        };

        mTabGridItemTouchHelperCallback = new TabGridItemTouchHelperCallback(context, mModel,
                mTabModelSelector, mTabClosedListener, mTabGridDialogHandler, mComponentName,
                mActionsOnAllRelatedTabs, mMode);

        // Right now we need to update layout only if there is a price welcome message card in tab
        // switcher.
        if (mMode == TabListMode.GRID && mUiType != UiType.SELECTABLE
                && PriceTrackingUtilities.isPriceTrackingEnabled()) {
            mListObserver = new ListObserver<Void>() {
                @Override
                public void onItemRangeInserted(ListObservable source, int index, int count) {
                    updateLayout();
                }

                @Override
                public void onItemRangeRemoved(ListObservable source, int index, int count) {
                    updateLayout();
                }

                @Override
                public void onItemRangeChanged(
                        ListObservable<Void> source, int index, int count, @Nullable Void payload) {
                    updateLayout();
                }

<<<<<<< HEAD
                    int index = mModelList.indexFromId(updatedTab.getId());

                    @Nullable Tab tab = null;
                    @Nullable PropertyModel model = null;
                    if (index != TabModel.INVALID_TAB_INDEX) {
                        tab = updatedTab;
                        model = mModelList.get(index).model;
                    } else if (mActionsOnAllRelatedTabs) {
                        @Nullable
                        Pair<Integer, Tab> indexAndTab =
                                getIndexAndTabForRootId(updatedTab.getRootId());
                        if (indexAndTab != null) {
                            tab = indexAndTab.second;
                            model = mModelList.get(indexAndTab.first).model;
                        }
                    }
                    if (tab != null && model != null) {
                        model.set(TabProperties.URL_DOMAIN, getDomainForTab(tab));
                        // Changing URL will result in a thumbnail invalidation if the on-disk
                        // thumbnail doesn't match.
                        updateThumbnailFetcher(model, tab.getId());
                        // Changing URL should also invalidate the favicon.
                        updateFaviconForTab(model, tab, null, null);
                    }
=======
                @Override
                public void onItemMoved(ListObservable source, int curIndex, int newIndex) {
                    updateLayout();
>>>>>>> chromium
                }
            };
            mModel.addObserver(mListObserver);
        }
    }

    public void initWithNative(Profile profile) {
        mTabListFaviconProvider.initWithNative(profile);
        mTabModelSelector.getTabModelFilterProvider().addTabModelFilterObserver(mTabModelObserver);

        if (mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter()
                        instanceof TabGroupModelFilter) {
            mTabGroupObserver = new EmptyTabGroupModelFilterObserver() {
                @Override
                public void didMoveWithinGroup(
                        Tab movedTab, int tabModelOldIndex, int tabModelNewIndex) {
                    if (tabModelNewIndex == tabModelOldIndex) return;

                    int curPosition = mModel.indexFromId(movedTab.getId());
                    TabModel tabModel = mTabModelSelector.getCurrentModel();

                    if (!isValidMovePosition(curPosition)) return;

                    Tab destinationTab = tabModel.getTabAt(tabModelNewIndex > tabModelOldIndex
                                    ? tabModelNewIndex - 1
                                    : tabModelNewIndex + 1);

                    int newPosition = mModel.indexFromId(destinationTab.getId());
                    if (!isValidMovePosition(newPosition)) return;
                    mModel.move(curPosition, newPosition);
                }

                @Override
                public void didMoveTabOutOfGroup(Tab movedTab, int prevFilterIndex) {
                    assert !(mActionsOnAllRelatedTabs && mTabGridDialogHandler != null);
                    TabGroupModelFilter filter =
                            (TabGroupModelFilter) mTabModelSelector.getTabModelFilterProvider()
                                    .getCurrentTabModelFilter();
                    Tab groupTab = filter.getTabAt(prevFilterIndex);
                    boolean isUngroupingLastTabInGroup = groupTab.getId() == movedTab.getId();
                    if (mActionsOnAllRelatedTabs) {
                        if (isUngroupingLastTabInGroup) {
                            return;
                        }
                        Tab currentSelectedTab = mTabModelSelector.getCurrentTab();
                        if (isShowingTabsInMRUOrder()) {
                            int groupTabIndex = mModel.indexFromId(groupTab.getId());
                            if (groupTabIndex == TabModel.INVALID_TAB_INDEX) {
                                // It is possible that the movedTab is the Tab for its group in the
                                // model.
                                groupTabIndex = mModel.indexFromId(movedTab.getId());
                            }
                            assert groupTabIndex != TabModel.INVALID_TAB_INDEX;
                            boolean isSelected =
                                    mTabModelSelector.getCurrentTabId() == groupTab.getId();
                            // We may need to adjust the group's index after removing the movedTab
                            // from the group.
                            int newGroupTabIndexMRU =
                                    mModel.getNewPositionInMruOrderList(groupTab.getId());

                            updateTab(groupTabIndex, PseudoTab.fromTab(groupTab), isSelected, true,
                                    false);
                            if (groupTabIndex != newGroupTabIndexMRU) {
                                // The move API will first remove the item at groupTabIndex. Thus,
                                // we need to decrease newGroupTabIndexMRU if an item has been
                                // removed before it.
                                mModel.move(groupTabIndex,
                                        groupTabIndex < newGroupTabIndexMRU
                                                ? newGroupTabIndexMRU - 1
                                                : newGroupTabIndexMRU);
                            }

                            int modelIndex = mModel.getNewPositionInMruOrderList(movedTab.getId());
                            addTabInfoToModel(PseudoTab.fromTab(movedTab), modelIndex,
                                    currentSelectedTab.getId() == movedTab.getId());
                        } else {
                            int filterIndex = TabModelUtils.getTabIndexById(
                                    mTabModelSelector.getTabModelFilterProvider()
                                            .getCurrentTabModelFilter(),
                                    movedTab.getId());
                            addTabInfoToModel(PseudoTab.fromTab(movedTab),
                                    mModel.indexOfNthTabCard(filterIndex),
                                    currentSelectedTab.getId() == movedTab.getId());
                            boolean isSelected = mTabModelSelector.getCurrentTabId()
                                    == filter.getTabAt(prevFilterIndex).getId();
                            updateTab(mModel.indexOfNthTabCard(prevFilterIndex),
                                    PseudoTab.fromTab(filter.getTabAt(prevFilterIndex)), isSelected,
                                    true, false);
                        }
                    } else {
                        int curTabListModelIndex = mModel.indexFromId(movedTab.getId());
                        if (!isValidMovePosition(curTabListModelIndex)) return;
                        mModel.removeAt(curTabListModelIndex);
                        if (mTabGridDialogHandler != null) {
                            mTabGridDialogHandler.updateDialogContent(isUngroupingLastTabInGroup
                                            ? Tab.INVALID_TAB_ID
                                            : filter.getTabAt(prevFilterIndex).getId());
                        }
                    }
                }

                @Override
<<<<<<< HEAD
                public void didMergeTabToGroup(Tab movedTab) {
                    assert mShowingTabs;
=======
                public void didMergeTabToGroup(Tab movedTab, int selectedTabIdInGroup) {
                    if (!mActionsOnAllRelatedTabs) return;
>>>>>>> chromium

                    // When merging Tab 1 to Tab 2 as a new group, or merging Tab 1 to an existing
                    // group 1, we can always find the current indexes of 1) Tab 1 and 2) Tab 2 or
                    // group 1 in the model. The method getIndexesForMergeToGroup() returns these
                    // two ids by using Tab 1's related Tabs, which have been updated in TabModel.
                    Pair<Integer, Integer> positions =
                            mModel.getIndexesForMergeToGroup(mTabModelSelector.getCurrentModel(),
                                    getRelatedTabsForId(movedTab.getId()));
                    int srcIndex = positions.second;
                    int desIndex = positions.first;

                    if (!isValidMovePosition(srcIndex) || !isValidMovePosition(desIndex)) return;
                    Tab newSelectedTabInMergedGroup = null;
                    boolean isMRU = isShowingTabsInMRUOrder();
                    if (isMRU) {
                        // We need to choose the Tab that represents the new group. It should be the
                        // last selected tab for the new formed group.
                        Tab oldSelectedTabInMergedGroup = mTabModelSelector.getTabById(
                                mModel.get(desIndex).model.get(TabProperties.TAB_ID));
                        int mergedGroupIndex = mTabModelSelector.getTabModelFilterProvider()
                                                       .getCurrentTabModelFilter()
                                                       .indexOf(oldSelectedTabInMergedGroup);
                        newSelectedTabInMergedGroup = mTabModelSelector.getTabModelFilterProvider()
                                                              .getCurrentTabModelFilter()
                                                              .getTabAt(mergedGroupIndex);
                    }
                    mModel.removeAt(srcIndex);
                    if (getRelatedTabsForId(movedTab.getId()).size() == 2) {
                        // When users use drop-to-merge to create a group.
                        RecordUserAction.record("TabGroup.Created.DropToMerge");
                    } else {
<<<<<<< HEAD
                        // If no tab is present we can't check if the added tab is part of the
                        // current group. Assume it isn't since a group state with 0 tab should be
                        // impossible.
                        @Nullable PropertyModel model = mModelList.getFirstTabPropertyModel();
                        if (model == null) return;

                        // If the added tab is part of the group add it and update the dialog.
                        int firstTabId = model.get(TabProperties.TAB_ID);
                        Tab firstTab = tabModel.getTabById(firstTabId);
                        if (firstTab == null || firstTab.getRootId() != movedTab.getRootId()) {
                            return;
                        }

                        movedTab.addObserver(mTabObserver);
                        onTabAdded(movedTab, /* onlyShowRelatedTabs= */ true);
                        if (mTabGridDialogHandler != null) {
                            mTabGridDialogHandler.updateDialogContent(
                                    filter.getGroupLastShownTabId(firstTab.getRootId()));
                        }
=======
                        RecordUserAction.record("TabGrid.Drag.DropToMerge");
                    }
                    desIndex = srcIndex > desIndex ? desIndex : mModel.getTabIndexBefore(desIndex);
                    if (!isMRU) {
                        newSelectedTabInMergedGroup =
                                mTabModelSelector.getTabModelFilterProvider()
                                        .getCurrentTabModelFilter()
                                        .getTabAt(mModel.getTabCardCountsBefore(desIndex));
                    }

                    boolean isSelected =
                            mTabModelSelector.getCurrentTab() == newSelectedTabInMergedGroup;
                    updateTab(desIndex, PseudoTab.fromTab(newSelectedTabInMergedGroup), isSelected,
                            true, false);
                    if (isSelected && isMRU) {
                        // In MRU order, always moves the new group which contains the current
                        // selected Tab to the position 0.
                        mModel.move(desIndex, 0);
>>>>>>> chromium
                    }
                }

                @Override
                public void didMoveTabGroup(
                        Tab movedTab, int tabModelOldIndex, int tabModelNewIndex) {
                    if (!mActionsOnAllRelatedTabs || tabModelNewIndex == tabModelOldIndex) return;
                    TabGroupModelFilter filter =
                            (TabGroupModelFilter) mTabModelSelector.getTabModelFilterProvider()
                                    .getCurrentTabModelFilter();
                    List<Tab> relatedTabs = getRelatedTabsForId(movedTab.getId());
                    Tab currentGroupSelectedTab =
                            TabGroupUtils.getSelectedTabInGroupForTab(mTabModelSelector, movedTab);
                    TabModel tabModel = mTabModelSelector.getCurrentModel();
                    int curPosition = mModel.indexFromId(currentGroupSelectedTab.getId());
                    if (curPosition == TabModel.INVALID_TAB_INDEX) {
                        // Sync TabListModel with updated TabGroupModelFilter.
                        int indexToUpdate = mModel.indexOfNthTabCard(
                                filter.indexOf(tabModel.getTabAt(tabModelOldIndex)));
                        mModel.updateTabListModelIdForGroup(currentGroupSelectedTab, indexToUpdate);
                        curPosition = mModel.indexFromId(currentGroupSelectedTab.getId());
                    }
                    if (!isValidMovePosition(curPosition)) return;

                    // Find the tab which was in the destination index before this move. Use that
                    // tab to figure out the new position.
                    int destinationTabIndex = tabModelNewIndex > tabModelOldIndex
                            ? tabModelNewIndex - relatedTabs.size()
                            : tabModelNewIndex + 1;
                    Tab destinationTab = tabModel.getTabAt(destinationTabIndex);
                    Tab destinationGroupSelectedTab = TabGroupUtils.getSelectedTabInGroupForTab(
                            mTabModelSelector, destinationTab);
                    int newPosition = mModel.indexFromId(destinationGroupSelectedTab.getId());
                    if (newPosition == TabModel.INVALID_TAB_INDEX) {
                        int indexToUpdate = mModel.indexOfNthTabCard(filter.indexOf(destinationTab)
                                + (tabModelNewIndex > tabModelOldIndex ? 1 : -1));
                        mModel.updateTabListModelIdForGroup(
                                destinationGroupSelectedTab, indexToUpdate);
                        newPosition = mModel.indexFromId(destinationGroupSelectedTab.getId());
                    }
                    if (!isValidMovePosition(newPosition)) return;

                    mModel.move(curPosition, newPosition);
                }

                @Override
                public void didCreateGroup(
                        List<Tab> tabs, List<Integer> tabOriginalIndex, boolean isSameGroup) {}
            };

<<<<<<< HEAD
    /**
     * Construct the Mediator with the given Models and observing hooks from the given
     * ChromeActivity.
     *
     * @param activity The activity used to get some configuration information.
     * @param modelList The {@link TabListModel} to keep state about a list of {@link Tab}s.
     * @param mode The {@link TabListMode}
     * @param modalDialogManager The {@link ModalDialogManager} for managing dialog lifecycles.
     * @param tabGroupModelFilterSupplier Used to fetch the filter that provides tab group
     *     information.
     * @param thumbnailProvider {@link ThumbnailProvider} to provide screenshot related details.
     * @param tabListFaviconProvider Provider for all favicon related drawables.
     * @param actionOnRelatedTabs Whether tab-related actions should be operated on all related
     *     tabs.
     * @param selectionDelegateProvider Provider for a {@link SelectionDelegate} that is used for a
     *     selectable list. It's null when selection is not possible.
     * @param gridCardOnClickListenerProvider Provides the onClickListener for opening dialog when
     *     click on a grid card.
     * @param dialogHandler A handler to handle requests about updating TabGridDialog.
     * @param priceWelcomeMessageControllerSupplier A supplier of a controller to show
     *     PriceWelcomeMessage.
     * @param componentName This is a unique string to identify different components.
     * @param initialTabActionState The initial {@link TabActionState} to use for the shown tabs.
     *     Must always be CLOSABLE for TabListMode.STRIP.
     * @param actionConfirmationManager Used for showing confirmation dialogs.
     * @param dataSharingTabManager The service used to initiate data sharing.
     * @param onTabGroupCreation Should be run when the UI is used to create a tab group.
     */
    public TabListMediator(
            Activity activity,
            TabListModel modelList,
            @TabListMode int mode,
            @Nullable ModalDialogManager modalDialogManager,
            @NonNull ObservableSupplier<TabGroupModelFilter> tabGroupModelFilterSupplier,
            @Nullable ThumbnailProvider thumbnailProvider,
            TabListFaviconProvider tabListFaviconProvider,
            boolean actionOnRelatedTabs,
            @Nullable SelectionDelegateProvider selectionDelegateProvider,
            @Nullable GridCardOnClickListenerProvider gridCardOnClickListenerProvider,
            @Nullable TabGridDialogHandler dialogHandler,
            @NonNull Supplier<PriceWelcomeMessageController> priceWelcomeMessageControllerSupplier,
            String componentName,
            @TabActionState int initialTabActionState,
            @Nullable ActionConfirmationManager actionConfirmationManager,
            @Nullable DataSharingTabManager dataSharingTabManager,
            @Nullable Runnable onTabGroupCreation) {
        mActivity = activity;
        mModelList = modelList;
        mMode = mode;
        mModalDialogManager = modalDialogManager;
        mCurrentTabGroupModelFilterSupplier = tabGroupModelFilterSupplier;
        mThumbnailProvider = thumbnailProvider;
        mTabListFaviconProvider = tabListFaviconProvider;
        mActionsOnAllRelatedTabs = actionOnRelatedTabs;
        mSelectionDelegateProvider = selectionDelegateProvider;
        mGridCardOnClickListenerProvider = gridCardOnClickListenerProvider;
        mTabGridDialogHandler = dialogHandler;
        mPriceWelcomeMessageControllerSupplier = priceWelcomeMessageControllerSupplier;
        mComponentName = componentName;
        mTabActionState = initialTabActionState;
        mActionConfirmationManager = actionConfirmationManager;
        mDataSharingTabManager = dataSharingTabManager;
        mOnTabGroupCreation = onTabGroupCreation;

        mTabModelObserver =
                new TabModelObserver() {
                    @Override
                    public void didSelectTab(Tab tab, int type, int lastId) {
                        assert mShowingTabs;

                        mNextTabId = Tab.INVALID_TAB_ID;
                        if (tab.getId() == lastId) return;

                        int oldIndex = mModelList.indexFromId(lastId);
                        if (oldIndex == TabModel.INVALID_TAB_INDEX && mActionsOnAllRelatedTabs) {
                            oldIndex = getIndexForTabIdWithRelatedTabs(lastId);
                        }
                        int newIndex = mModelList.indexFromId(tab.getId());
                        if (newIndex == TabModel.INVALID_TAB_INDEX && mActionsOnAllRelatedTabs) {
                            // If a tab in tab group does not exist in model and needs to be
                            // selected, identify the related tab ids and determine newIndex
                            // based on if any of the related ids are present in model.
                            newIndex = getIndexForTabWithRelatedTabs(tab);
                            // For UNDO ensure we update the representative tab in the model.
                            if (type == TabSelectionType.FROM_UNDO
                                    && newIndex != Tab.INVALID_TAB_ID) {
                                modelList.updateTabListModelIdForGroup(tab, newIndex);
                            }
                        }

                        mLastSelectedTabListModelIndex = oldIndex;
                        if (mTabToAddDelayed != null && mTabToAddDelayed == tab) {
                            // If tab is being added later, it will be selected later.
                            return;
                        }
                        selectTab(oldIndex, newIndex);
                    }

                    @Override
                    public void tabClosureCommitted(Tab tab) {
                        sTabClosedFromMapTabClosedFromMap.remove(tab.getId());
                    }

                    @Override
                    public void tabClosureUndone(Tab tab) {
                        assert mShowingTabs;

                        tab.addObserver(mTabObserver);
                        onTabAdded(tab, !mActionsOnAllRelatedTabs);

                        if (sTabClosedFromMapTabClosedFromMap.containsKey(tab.getId())) {
                            @TabClosedFrom
                            int from = sTabClosedFromMapTabClosedFromMap.get(tab.getId());
                            switch (from) {
                                case TabClosedFrom.TAB_STRIP:
                                    RecordUserAction.record("TabStrip.UndoCloseTab");
                                    break;
                                case TabClosedFrom.GRID_TAB_SWITCHER:
                                    RecordUserAction.record("GridTabSwitch.UndoCloseTab");
                                    break;
                                case TabClosedFrom.GRID_TAB_SWITCHER_GROUP:
                                    RecordUserAction.record("GridTabSwitcher.UndoCloseTabGroup");
                                    break;
                                default:
                                    assert false
                                            : "tabClosureUndone for tab that closed from an unknown"
                                                    + " UI";
                            }
                            sTabClosedFromMapTabClosedFromMap.remove(tab.getId());
                        }
                        // TODO(yuezhanggg): clean up updateTab() calls in this class.
                        if (mActionsOnAllRelatedTabs) {
                            TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
                            int filterIndex = filter.indexOf(tab);
                            if (filterIndex == TabList.INVALID_TAB_INDEX
                                    || !filter.isTabInTabGroup(tab)
                                    || filterIndex >= mModelList.size()) {
                                return;
                            }
                            Tab currentGroupSelectedTab = filter.getTabAt(filterIndex);

                            int tabListModelIndex = mModelList.indexOfNthTabCard(filterIndex);
                            assert mModelList.indexFromId(currentGroupSelectedTab.getId())
                                    == tabListModelIndex;

                            updateTab(tabListModelIndex, currentGroupSelectedTab, false, false);
                        }
                    }

                    @Override
                    public void didAddTab(
                            Tab tab,
                            @TabLaunchType int type,
                            @TabCreationState int creationState,
                            boolean markedForSelection) {
                        assert mShowingTabs;

                        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
                        if (filter == null || !filter.isTabModelRestored()) {
                            return;
                        }

                        tab.addObserver(mTabObserver);

                        // Check if we need to delay tab addition to model.
                        boolean delayAdd =
                                (type == TabLaunchType.FROM_TAB_SWITCHER_UI)
                                        && markedForSelection
                                        && TabSwitcherPaneCoordinator.COMPONENT_NAME.equals(
                                                mComponentName);
                        if (delayAdd) {
                            mTabToAddDelayed = tab;
                            return;
                        }

                        onTabAdded(tab, !mActionsOnAllRelatedTabs);
                        if (type == TabLaunchType.FROM_RESTORE && mActionsOnAllRelatedTabs) {
                            // When tab is restored after restoring stage (e.g. exiting multi-window
                            // mode, switching between dark/light mode in incognito), we need to
                            // update related property models.
                            int filterIndex = filter.indexOf(tab);
                            if (filterIndex == TabList.INVALID_TAB_INDEX) return;
                            Tab currentGroupSelectedTab = filter.getTabAt(filterIndex);
                            // TabModel and TabListModel may be in the process of syncing up through
                            // restoring. Examples of this situation are switching between
                            // light/dark mode in incognito, exiting multi-window mode, etc.
                            int tabListModelIndex = mModelList.indexOfNthTabCard(filterIndex);
                            if (mModelList.indexFromId(currentGroupSelectedTab.getId())
                                    != tabListModelIndex) {
                                return;
                            }
                            updateTab(tabListModelIndex, currentGroupSelectedTab, false, false);
                        }
                    }

                    @Override
                    public void willCloseTab(Tab tab, boolean didCloseAlone) {
                        assert mShowingTabs;

                        tab.removeObserver(mTabObserver);

                        // If the tab closed was part of a tab group and the closure was triggered
                        // from the tab switcher, update the group to reflect the closure instead of
                        // closing the tab.
                        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
                        if (mActionsOnAllRelatedTabs
                                && filter != null
                                && filter.tabGroupExistsForRootId(tab.getRootId())) {
                            int groupIndex = filter.indexOf(tab);
                            Tab groupTab = filter.getTabAt(groupIndex);
                            if (!groupTab.isClosing()) {
                                updateTab(
                                        mModelList.indexOfNthTabCard(groupIndex),
                                        groupTab,
                                        true,
                                        false);

                                return;
                            }
                        }

                        if (mModelList.indexFromId(tab.getId()) == TabModel.INVALID_TAB_INDEX) {
                            return;
                        }
                        removeAt(mModelList.indexFromId(tab.getId()));
                    }

                    @Override
                    public void tabRemoved(Tab tab) {
                        assert mShowingTabs;

                        tab.removeObserver(mTabObserver);

                        if (mModelList.indexFromId(tab.getId()) == TabModel.INVALID_TAB_INDEX) {
                            return;
                        }
                        removeAt(mModelList.indexFromId(tab.getId()));
                    }
                };

        mTabClosedListener =
                new TabActionListener() {
                    @Override
                    public void run(View view, int tabId) {
                        // TODO(crbug.com/40638921): Consider disabling all touch events during
                        // animation.
                        if (mModelList.indexFromId(tabId) == TabModel.INVALID_TAB_INDEX) return;

                        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
                        TabModel tabModel = filter.getTabModel();
                        Tab closingTab = tabModel.getTabById(tabId);
                        if (closingTab == null) return;

                        setUseShrinkCloseAnimation(tabId, /* useShrinkCloseAnimation= */ true);
                        if (mActionsOnAllRelatedTabs && filter.isTabInTabGroup(closingTab)) {
                            onGroupClosedFrom(tabId);
                            TabUiUtils.closeTabGroup(
                                    mCurrentTabGroupModelFilterSupplier.get(),
                                    tabId,
                                    /* hideTabGroups= */ true,
                                    getOnMaybeTabClosedCallback(tabId));
                            return;
                        }

                        onTabClosedFrom(tabId, mComponentName);
                        Tab currentTab = TabModelUtils.getCurrentTab(tabModel);
                        Tab nextTab = currentTab == closingTab ? getNextTab(tabId) : null;
                        TabClosureParams closureParams =
                                TabClosureParams.closeTab(closingTab)
                                        .recommendedNextTab(nextTab)
                                        .allowUndo(true)
                                        .build();

                        @Nullable
                        TabModelActionListener listener =
                                TabUiUtils.buildMaybeDidCloseTabListener(
                                        getOnMaybeTabClosedCallback(tabId));
                        tabModel.getTabRemover()
                                .closeTabs(closureParams, /* allowDialog= */ true, listener);
                    }

                    private Tab getNextTab(int closingTabId) {
                        int closingTabIndex = mModelList.indexFromId(closingTabId);

                        if (closingTabIndex == TabModel.INVALID_TAB_INDEX) {
                            assert false;
                            return null;
                        }

                        int nextTabId = Tab.INVALID_TAB_ID;
                        if (mModelList.size() > 1) {
                            int nextTabIndex =
                                    closingTabIndex == 0
                                            ? mModelList.getTabIndexAfter(closingTabIndex)
                                            : mModelList.getTabIndexBefore(closingTabIndex);
                            nextTabId =
                                    nextTabIndex == TabModel.INVALID_TAB_INDEX
                                            ? Tab.INVALID_TAB_ID
                                            : mModelList
                                                    .get(nextTabIndex)
                                                    .model
                                                    .get(TabProperties.TAB_ID);
                        }

                        return mCurrentTabGroupModelFilterSupplier
                                .get()
                                .getTabModel()
                                .getTabById(nextTabId);
                    }
                };

        TabActionListener swipeSafeTabActionListener =
                (view, tabId) -> {
                    // The DefaultItemAnimator is prone to crashing in combination with the swipe
                    // animation when closing the last tab.
                    // Avoid this issue by disabling the default item animation for the duration of
                    // the removal of the last tab. This is a framework issue. For more details see
                    // crbug/1319859.
                    boolean shouldDisableItemAnimations =
                            mCurrentTabGroupModelFilterSupplier.hasValue()
                                    && mCurrentTabGroupModelFilterSupplier.get().getTotalTabCount()
                                            <= 1;
                    if (shouldDisableItemAnimations) {
                        mRecyclerViewItemAnimationToggle.setDisableItemAnimations(true);
                    }

                    mTabClosedListener.run(view, tabId);

                    // It is necessary to post the restoration as otherwise any animation triggered
                    // by removing the tab will still use the animator as they are also posted to
                    // the UI thread.
                    if (shouldDisableItemAnimations) {
                        new Handler()
                                .post(
                                        () -> {
                                            mRecyclerViewItemAnimationToggle
                                                    .setDisableItemAnimations(false);
                                        });
                    }
                };

        var tabGroupCreationDialogManager =
                new TabGroupCreationDialogManager(
                        activity, modalDialogManager, mOnTabGroupCreation);
        mTabGridItemTouchHelperCallback =
                new TabGridItemTouchHelperCallback(
                        activity,
                        tabGroupCreationDialogManager,
                        mModelList,
                        mCurrentTabGroupModelFilterSupplier,
                        swipeSafeTabActionListener,
                        mTabGridDialogHandler,
                        mComponentName,
                        mActionsOnAllRelatedTabs,
                        mMode);
    }

    /**
     * @param onLongPressTabItemEventListener to handle long press events on tabs.
     */
    public void setOnLongPressTabItemEventListener(
            @Nullable
                    TabGridItemTouchHelperCallback.OnLongPressTabItemEventListener
                            onLongPressTabItemEventListener) {
        mTabGridItemTouchHelperCallback.setOnLongPressTabItemEventListener(
                onLongPressTabItemEventListener);
    }

    void setRecyclerViewItemAnimationToggle(
            RecyclerViewItemAnimationToggle recyclerViewItemAnimationToggle) {
        mRecyclerViewItemAnimationToggle = recyclerViewItemAnimationToggle;
    }

    /**
     * @param size The default size to use for any new Tab cards.
     */
    void setDefaultGridCardSize(Size size) {
        mDefaultGridCardSize = size;
    }

    /**
     * @return The default size to use for any tab cards.
     */
    Size getDefaultGridCardSize() {
        return mDefaultGridCardSize;
    }

    private void selectTab(int oldIndex, int newIndex) {
        // TODO(crbug.com/347886633): Change the bounds check to an assert.
        if (oldIndex != TabModel.INVALID_TAB_INDEX && oldIndex < mModelList.size()) {
            PropertyModel oldModel = mModelList.get(oldIndex).model;
            int lastId = oldModel.get(TAB_ID);
            oldModel.set(TabProperties.IS_SELECTED, false);
            if (mActionsOnAllRelatedTabs && mThumbnailProvider != null && mShowingTabs) {
                updateThumbnailFetcher(oldModel, lastId);
            }
=======
            ((TabGroupModelFilter) mTabModelSelector.getTabModelFilterProvider().getTabModelFilter(
                     false))
                    .addTabGroupObserver(mTabGroupObserver);
            ((TabGroupModelFilter) mTabModelSelector.getTabModelFilterProvider().getTabModelFilter(
                     true))
                    .addTabGroupObserver(mTabGroupObserver);
>>>>>>> chromium
        }

        if (TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(mContext)) {
            mTabGroupTitleEditor = new TabGroupTitleEditor(mTabModelSelector) {
                @Override
                protected void updateTabGroupTitle(Tab tab, String title) {
                    // Only update title in PropertyModel for tab switcher.
                    if (!mActionsOnAllRelatedTabs) return;
                    Tab currentGroupSelectedTab =
                            TabGroupUtils.getSelectedTabInGroupForTab(mTabModelSelector, tab);
                    int index = mModel.indexFromId(currentGroupSelectedTab.getId());
                    if (index == TabModel.INVALID_TAB_INDEX) return;
                    mModel.get(index).model.set(TabProperties.TITLE, title);
                    updateDescriptionString(PseudoTab.fromTab(tab), mModel.get(index).model);
                    if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                        updateCloseButtonDescriptionString(
                                PseudoTab.fromTab(tab), mModel.get(index).model);
                    }
                }

                @Override
                protected void deleteTabGroupTitle(int tabRootId) {
                    TabGroupUtils.deleteTabGroupTitle(tabRootId);
                }

                @Override
                protected String getTabGroupTitle(int tabRootId) {
                    return TabGroupUtils.getTabGroupTitle(tabRootId);
                }

                @Override
                protected void storeTabGroupTitle(int tabRootId, String title) {
                    TabGroupUtils.storeTabGroupTitle(tabRootId, title);
                }
            };
        }

<<<<<<< HEAD
    public void initWithNative(Profile originalProfile) {
        assert !originalProfile.isOffTheRecord() : "Expecting a non-incognito profile.";
        mOriginalProfile = originalProfile;
        mTabListFaviconProvider.initWithNative(originalProfile);

        mOnTabGroupModelFilterChanged.onResult(
                mCurrentTabGroupModelFilterSupplier.addObserver(mOnTabGroupModelFilterChanged));

        mTabGroupSyncService = TabGroupSyncServiceFactory.getForProfile(originalProfile);
        if (mTabGroupSyncService != null) {
            mDataSharingService = DataSharingServiceFactory.getForProfile(originalProfile);
        }
        mCollaborationService = CollaborationServiceFactory.getForProfile(originalProfile);

        // Right now we need to update layout only if there is a price welcome message card in tab
        // switcher.
        if (mMode == TabListMode.GRID
                && mTabActionState != TabActionState.SELECTABLE
                && PriceTrackingFeatures.isPriceAnnotationsEnabled(originalProfile)) {
            mListObserver =
                    new ListObserver<Void>() {
                        @Override
                        public void onItemRangeInserted(
                                ListObservable source, int index, int count) {
                            updateLayout();
                        }

                        @Override
                        public void onItemRangeRemoved(
                                ListObservable source, int index, int count) {
                            updateLayout();
                        }

                        @Override
                        public void onItemRangeChanged(
                                ListObservable<Void> source,
                                int index,
                                int count,
                                @Nullable Void payload) {
                            updateLayout();
                        }

                        @Override
                        public void onItemMoved(ListObservable source, int curIndex, int newIndex) {
                            updateLayout();
                        }
                    };
            mModelList.addObserver(mListObserver);
=======
        if (TabUiFeatureUtilities.ENABLE_SEARCH_CHIP.getValue()) {
            mSearchChipIconDrawableId = getSearchChipIconDrawableId();
            mTemplateUrlObserver = () -> {
                mSearchChipIconDrawableId = getSearchChipIconDrawableId();
                for (int i = 0; i < mModel.size(); i++) {
                    if (mModel.get(i).model.get(CARD_TYPE) != TAB) continue;
                    mModel.get(i).model.set(
                            TabProperties.PAGE_INFO_ICON_DRAWABLE_ID, mSearchChipIconDrawableId);
                }
            };
            TemplateUrlServiceFactory.get().addObserver(mTemplateUrlObserver);
>>>>>>> chromium
        }
    }

    private void onTabClosedFrom(int tabId, String fromComponent) {
        @TabClosedFrom
        int from;
        if (fromComponent.equals(TabGroupUiCoordinator.COMPONENT_NAME)) {
            from = TabClosedFrom.TAB_STRIP;
        } else if (fromComponent.equals(TabSwitcherCoordinator.COMPONENT_NAME)) {
            from = TabClosedFrom.GRID_TAB_SWITCHER;
        } else {
            Log.w(TAG, "Attempting to close tab from Unknown UI");
            return;
        }
        sTabClosedFromMapTabClosedFromMap.put(tabId, from);
    }

    private void onGroupClosedFrom(int tabId) {
        sTabClosedFromMapTabClosedFromMap.put(tabId, TabClosedFrom.GRID_TAB_SWITCHER_GROUP);
    }

    @VisibleForTesting
    void setActionOnAllRelatedTabsForTesting(boolean actionOnAllRelatedTabs) {
        mActionsOnAllRelatedTabs = actionOnAllRelatedTabs;
    }

    private List<Tab> getRelatedTabsForId(int id) {
        TabModelFilter filter =
                mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter();
        return filter == null ? new ArrayList<>() : filter.getRelatedTabList(id);
    }

<<<<<<< HEAD
    private List<Integer> getRelatedTabsIds(int id) {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        return filter == null ? new ArrayList<>() : filter.getRelatedTabIds(id);
    }

    private int getInsertionIndexOfTab(Tab tab, boolean onlyShowRelatedTabs) {
        if (tab == null) return TabList.INVALID_TAB_INDEX;

        int tabIndex = TabList.INVALID_TAB_INDEX;
        if (onlyShowRelatedTabs) {
            // Compute the index of the tab within the tab's group.
            @Nullable PropertyModel model = mModelList.getFirstTabPropertyModel();
            if (model == null) return TabList.INVALID_TAB_INDEX;

            List<Tab> related = getRelatedTabsForId(model.get(TabProperties.TAB_ID));
            tabIndex = related.indexOf(tab);
        } else {
            // Compute the index of the tab out of all tabs.
            tabIndex =
                    TabModelUtils.getTabIndexById(
                            mCurrentTabGroupModelFilterSupplier.get(), tab.getId());
=======
    private int getIndexOfTab(Tab tab, boolean onlyShowRelatedTabs) {
        int index;
        if (onlyShowRelatedTabs) {
            if (mModel.size() == 0) return TabList.INVALID_TAB_INDEX;
            List<Tab> related = getRelatedTabsForId(mModel.get(0).model.get(TabProperties.TAB_ID));
            index = related.indexOf(tab);
            if (index == -1) return TabList.INVALID_TAB_INDEX;
        } else {
            index = mModel.indexOfNthTabCard(TabModelUtils.getTabIndexById(
                    mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter(),
                    tab.getId()));
            // TODO(wychen): the title (tab count in the group) is wrong when it's not the last
            //  tab added in the group.
>>>>>>> chromium
        }
        // Get the position of the nth tab card ignoring any other CARD_TYPE entries present in the
        // model list.
        return mModelList.indexOfNthTabCard(tabIndex);
    }

    private void onTabAdded(Tab tab, boolean onlyShowRelatedTabs) {
        int index = getIndexOfTab(tab, onlyShowRelatedTabs);
        if (index == TabList.INVALID_TAB_INDEX) return;

        addTabInfoToModel(PseudoTab.fromTab(tab), index, mTabModelSelector.getCurrentTab() == tab);
    }

    private void onTabMoved(int newIndex, int curIndex) {
        // Handle move without groups enabled.
        if (mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter()
                        instanceof EmptyTabModelFilter) {
            if (!isValidMovePosition(curIndex) || !isValidMovePosition(newIndex)) return;
            mModel.move(curIndex, newIndex);
        }
    }

    private boolean isValidMovePosition(int position) {
        return position != TabModel.INVALID_TAB_INDEX && position < mModel.size();
    }

    /**
     * Hide the blue border for selected tab for the Tab-to-Grid resizing stage.
     * The selected border should re-appear in the final fading-in stage.
     */
    void prepareOverview() {
        if (!TabUiFeatureUtilities.isTabToGtsAnimationEnabled()
                || !mTabModelSelector.isTabStateInitialized()) {
            return;
        }

        assert mVisible;
        int selectedTabCount = 0;
        int tabsCount = 0;
        for (int i = 0; i < mModel.size(); i++) {
            if (mModel.get(i).model.get(CARD_TYPE) != TAB) continue;

            if (mModel.get(i).model.get(TabProperties.IS_SELECTED)) selectedTabCount++;
            mModel.get(i).model.set(TabProperties.IS_SELECTED, false);
            tabsCount += 1;
        }
        assert (selectedTabCount == 1 || tabsCount == 0)
            : "There should be exactly one selected tab or no tabs at all when calling "
              + "TabListMediator.prepareOverview()";
    }

    private boolean areTabsUnchanged(@Nullable List<PseudoTab> tabs) {
        int tabsCount = 0;
        for (int i = 0; i < mModel.size(); i++) {
            if (mModel.get(i).model.get(CARD_TYPE) == TAB) {
                tabsCount += 1;
            }
        }
        if (tabs == null) {
            return tabsCount == 0;
        }
        if (tabs.size() != tabsCount) return false;
        int tabsIndex = 0;
        for (int i = 0; i < mModel.size(); i++) {
            if (mModel.get(i).model.get(CARD_TYPE) == TAB
                    && mModel.get(i).model.get(TabProperties.TAB_ID)
                            != tabs.get(tabsIndex++).getId()) {
                return false;
            }
        }
        return true;
    }

    /**
     * Initialize the component with a list of tabs to show in a grid.
     * @param tabs The list of tabs to be shown.
     * @param quickMode Whether to skip capturing the selected live tab for the thumbnail.
     * @param mruMode Whether to sort the Tabs in MRU order.
     * @return Whether the {@link TabListRecyclerView} can be shown quickly.
     */
    boolean resetWithListOfTabs(
            @Nullable List<PseudoTab> tabs, boolean quickMode, boolean mruMode) {
        List<PseudoTab> tabsList = tabs;
        if (tabs != null && mruMode) {
            // Make a copy to sort since the input may be unmodifiable.
            tabsList = new ArrayList<>(tabs);
            Collections.sort(tabsList, LAST_SHOWN_COMPARATOR);
        }
        mVisible = tabsList != null;
        if (areTabsUnchanged(tabsList)) {
            if (tabsList == null) return true;
            for (int i = 0; i < tabsList.size(); i++) {
                PseudoTab tab = tabsList.get(i);
                boolean isSelected = mTabModelSelector.getCurrentTabId() == tab.getId();
                updateTab(mModel.indexOfNthTabCard(i), tab, isSelected, false, quickMode);
            }
            return true;
        }
        mModel.set(new ArrayList<>());
        if (tabsList == null) {
            return true;
        }
        int currentTabId = mTabModelSelector.getCurrentTabId();

        for (int i = 0; i < tabsList.size(); i++) {
            PseudoTab tab = tabsList.get(i);
            addTabInfoToModel(tab, i, isSelectedTab(tab, currentTabId));
        }

        return false;
    }

    void postHiding() {
<<<<<<< HEAD
        removeObservers(mCurrentTabGroupModelFilterSupplier.get());
        mShowingTabs = false;
        // if tab was marked for add later, add to model and mark as selected.
        if (mTabToAddDelayed != null) {
            int index = onTabAdded(mTabToAddDelayed, !mActionsOnAllRelatedTabs);
            selectTab(mLastSelectedTabListModelIndex, index);
            mTabToAddDelayed = null;
        }
=======
        mVisible = false;
>>>>>>> chromium
    }

    private boolean isSelectedTab(PseudoTab tab, int tabModelSelectedTabId) {
        SelectionDelegate<Integer> selectionDelegate = getTabSelectionDelegate();
        if (selectionDelegate == null) {
            return tab.getId() == tabModelSelectedTabId;
        } else {
            return selectionDelegate.isItemSelected(tab.getId());
        }
    }

    /**
     * @see TabSwitcherMediator.ResetHandler#softCleanup
     */
    void softCleanup() {
        assert !mVisible;
        for (int i = 0; i < mModel.size(); i++) {
            if (mModel.get(i).model.get(CARD_TYPE) == TAB) {
                mModel.get(i).model.set(TabProperties.THUMBNAIL_FETCHER, null);
            }
        }
    }

<<<<<<< HEAD
    private void updateTab(int index, Tab tab, boolean isUpdatingId, boolean quickMode) {
        if (index < 0 || index >= mModelList.size()) return;

        PropertyModel model = mModelList.get(index).model;
=======
    private void updateTab(int index, PseudoTab pseudoTab, boolean isSelected, boolean isUpdatingId,
            boolean quickMode) {
        if (index < 0 || index >= mModel.size()) return;
>>>>>>> chromium
        if (isUpdatingId) {
            mModel.get(index).model.set(TabProperties.TAB_ID, pseudoTab.getId());
        } else {
            assert mModel.get(index).model.get(TabProperties.TAB_ID) == pseudoTab.getId();
        }

        // TODO(wychen): refactor this.
        boolean isRealTab = pseudoTab.hasRealTab();
        TabActionListener tabSelectedListener;
        if (!isRealTab) {
            tabSelectedListener = null;
        } else if (mGridCardOnClickListenerProvider == null
                || getRelatedTabsForId(pseudoTab.getId()).size() == 1
                || !mActionsOnAllRelatedTabs) {
            tabSelectedListener = mTabSelectedListener;
        } else {
            tabSelectedListener =
                    mGridCardOnClickListenerProvider.openTabGridDialog(pseudoTab.getTab());

            if (tabSelectedListener == null) {
                tabSelectedListener = mTabSelectedListener;
            }
        }
        mModel.get(index).model.set(TabProperties.TAB_SELECTED_LISTENER, tabSelectedListener);
        mModel.get(index).model.set(TabProperties.IS_SELECTED, isSelected);
        mModel.get(index).model.set(TabProperties.SHOULD_SHOW_PRICE_DROP_TOOLTIP, false);
        mModel.get(index).model.set(TabProperties.TITLE, getLatestTitleForTab(pseudoTab));
        mModel.get(index).model.set(
                TabProperties.TAB_CLOSED_LISTENER, isRealTab ? mTabClosedListener : null);
        updateDescriptionString(pseudoTab, mModel.get(index).model);
        if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
            updateCloseButtonDescriptionString(pseudoTab, mModel.get(index).model);
        }
        if (isRealTab) {
            mModel.get(index).model.set(
                    TabProperties.URL_DOMAIN, getDomainForTab(pseudoTab.getTab()));
        }
        if (TabUiFeatureUtilities.ENABLE_SEARCH_CHIP.getValue() && mUiType == UiType.CLOSABLE
                && isRealTab) {
            mModel.get(index).model.set(
                    TabProperties.SEARCH_QUERY, getLastSearchTerm(pseudoTab.getTab()));
            mModel.get(index).model.set(TabProperties.PAGE_INFO_LISTENER,
                    SearchTermChipUtils.getSearchQueryListener(
                            pseudoTab.getTab(), mTabSelectedListener));
            mModel.get(index).model.set(
                    TabProperties.PAGE_INFO_ICON_DRAWABLE_ID, mSearchChipIconDrawableId);
        }

        if (mMode == TabListMode.GRID && pseudoTab.hasRealTab() && !pseudoTab.isIncognito()) {
            if (PriceTrackingUtilities.isTrackPricesOnTabsEnabled()
                    && isUngroupedTab(pseudoTab.getId())) {
                mModel.get(index).model.set(TabProperties.SHOPPING_PERSISTED_TAB_DATA_FETCHER,
                        new ShoppingPersistedTabDataFetcher(
                                pseudoTab.getTab(), mPriceWelcomeMessageController));
            } else {
                mModel.get(index).model.set(
                        TabProperties.SHOPPING_PERSISTED_TAB_DATA_FETCHER, null);
            }
            if (StoreTrackingUtilities.isStoreHoursOnTabsEnabled()) {
                mModel.get(index).model.set(TabProperties.STORE_PERSISTED_TAB_DATA_FETCHER,
                        new StorePersistedTabDataFetcher(pseudoTab.getTab()));
            }
        } else {
            mModel.get(index).model.set(TabProperties.SHOPPING_PERSISTED_TAB_DATA_FETCHER, null);
            mModel.get(index).model.set(TabProperties.STORE_PERSISTED_TAB_DATA_FETCHER, null);
        }

        updateFaviconForTab(pseudoTab, null);
        boolean forceUpdate = isSelected && !quickMode;
        if (mThumbnailProvider != null && mVisible
                && (mModel.get(index).model.get(TabProperties.THUMBNAIL_FETCHER) == null
                        || forceUpdate || isUpdatingId)) {
            ThumbnailFetcher callback =
                    new ThumbnailFetcher(mThumbnailProvider, pseudoTab.getId(), forceUpdate,
                            forceUpdate && !TabUiFeatureUtilities.isTabToGtsAnimationEnabled());
            mModel.get(index).model.set(TabProperties.THUMBNAIL_FETCHER, callback);
        }
    }

    @VisibleForTesting
<<<<<<< HEAD
    public boolean isTabInTabGroup(@NonNull Tab tab) {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        assert filter.isTabModelRestored();

        return filter.isTabInTabGroup(tab);
=======
    public boolean isUngroupedTab(int tabId) {
        return getRelatedTabsForId(tabId).size() == 1;
>>>>>>> chromium
    }

    /**
     * @return The callback that hosts the logic for swipe and drag related actions.
     */
    ItemTouchHelper.SimpleCallback getItemTouchHelperCallback(final float swipeToDismissThreshold,
            final float mergeThreshold, final float ungroupThreshold, final Profile profile) {
        mTabGridItemTouchHelperCallback.setupCallback(
                swipeToDismissThreshold, mergeThreshold, ungroupThreshold, profile);
        return mTabGridItemTouchHelperCallback;
    }

    void registerOrientationListener(GridLayoutManager manager) {
        // TODO(yuezhanggg): Try to dynamically determine span counts based on screen width,
        // minimum card width and padding.
        mComponentCallbacks = new ComponentCallbacks() {
            @Override
            public void onConfigurationChanged(Configuration newConfig) {
                updateSpanCountForOrientation(manager, newConfig.orientation);
                if (mMode == TabListMode.GRID && mUiType != UiType.SELECTABLE) updateLayout();
            }

<<<<<<< HEAD
                    @Override
                    public void onLowMemory() {}
                };
        mActivity.registerComponentCallbacks(mComponentCallbacks);
=======
            @Override
            public void onLowMemory() {}
        };
        mContext.registerComponentCallbacks(mComponentCallbacks);
>>>>>>> chromium
        mGridLayoutManager = manager;
    }

    /**
     * Update the grid layout span count and span size lookup base on orientation.
     * @param manager     The {@link GridLayoutManager} used to update the span count.
     * @param orientation The orientation base on which we update the span count.
     */
    void updateSpanCountForOrientation(GridLayoutManager manager, int orientation) {
        // When in multi-window mode, the span count is fixed to 2 to keep tab card size reasonable.
        int spanCount = orientation == Configuration.ORIENTATION_PORTRAIT
                        || MultiWindowUtils.getInstance().isInMultiWindowMode((Activity) mContext)
                ? TabListCoordinator.GRID_LAYOUT_SPAN_COUNT_PORTRAIT
                : TabListCoordinator.GRID_LAYOUT_SPAN_COUNT_LANDSCAPE;
        manager.setSpanCount(spanCount);
        manager.setSpanSizeLookup(new GridLayoutManager.SpanSizeLookup() {
            @Override
            public int getSpanSize(int position) {
                int itemType = mModel.get(position).type;

<<<<<<< HEAD
                        if (itemType == TabProperties.UiType.MESSAGE
                                || itemType == TabProperties.UiType.LARGE_MESSAGE
                                || itemType == TabProperties.UiType.CUSTOM_MESSAGE) {
                            return manager.getSpanCount();
                        }
                        return 1;
                    }
                });
        mCurrentSpanCount = newSpanCount;
        return oldSpanCount != newSpanCount;
    }

    int getCurrentSpanCount() {
        return mCurrentSpanCount;
    }

    /**
     * Span count is computed based on screen width for tablets and orientation for phones. When in
     * multi-window mode on phone, the span count is fixed to 2 to keep tab card size reasonable.
     */
    private int getSpanCount(int screenWidthDp) {
        if (DeviceFormFactor.isNonMultiDisplayContextOnTablet(mActivity)) {
            return screenWidthDp < TabListCoordinator.MAX_SCREEN_WIDTH_COMPACT_DP
                    ? TabListCoordinator.GRID_LAYOUT_SPAN_COUNT_COMPACT
                    : screenWidthDp < TabListCoordinator.MAX_SCREEN_WIDTH_MEDIUM_DP
                            ? TabListCoordinator.GRID_LAYOUT_SPAN_COUNT_MEDIUM
                            : TabListCoordinator.GRID_LAYOUT_SPAN_COUNT_LARGE;
        }
        return screenWidthDp < TabListCoordinator.MAX_SCREEN_WIDTH_COMPACT_DP
                ? TabListCoordinator.GRID_LAYOUT_SPAN_COUNT_COMPACT
                : TabListCoordinator.GRID_LAYOUT_SPAN_COUNT_MEDIUM;
=======
                if (itemType == TabProperties.UiType.MESSAGE
                        || itemType == TabProperties.UiType.LARGE_MESSAGE) {
                    return manager.getSpanCount();
                }
                return 1;
            }
        });
>>>>>>> chromium
    }

    /**
     * Setup the {@link View.AccessibilityDelegate} for grid layout.
     * @param helper The {@link TabGridAccessibilityHelper} used to setup accessibility support.
     */
    void setupAccessibilityDelegate(TabGridAccessibilityHelper helper) {
        if (!TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(mContext)) {
            return;
        }
        mAccessibilityDelegate = new View.AccessibilityDelegate() {
            @Override
            public void onInitializeAccessibilityNodeInfo(View host, AccessibilityNodeInfo info) {
                super.onInitializeAccessibilityNodeInfo(host, info);
                for (AccessibilityAction action : helper.getPotentialActionsForView(host)) {
                    info.addAction(action);
                }
            }

            @Override
            public boolean performAccessibilityAction(View host, int action, Bundle args) {
                if (!helper.isReorderAction(action)) {
                    return super.performAccessibilityAction(host, action, args);
                }

                Pair<Integer, Integer> positions = helper.getPositionsOfReorderAction(host, action);
                int currentPosition = positions.first;
                int targetPosition = positions.second;
                if (!isValidMovePosition(currentPosition) || !isValidMovePosition(targetPosition)) {
                    return false;
                }
                mModel.move(currentPosition, targetPosition);
                RecordUserAction.record("TabGrid.AccessibilityDelegate.Reordered");
                return true;
            }
        };
    }

<<<<<<< HEAD
    /** Destroy any members that needs clean up. */
=======
    /**
     * Exposes a {@link TabGroupTitleEditor} to modify the title of a tab group.
     * @return The {@link TabGroupTitleEditor} used to modify the title of a tab group.
     */
    @Nullable
    TabGroupTitleEditor getTabGroupTitleEditor() {
        return mTabGroupTitleEditor;
    }

    /**
     * Destroy any members that needs clean up.
     */
>>>>>>> chromium
    public void destroy() {
        if (mListObserver != null) {
            mModel.removeObserver(mListObserver);
        }
        TabModel tabModel = mTabModelSelector.getCurrentModel();
        if (tabModel != null) {
            for (int i = 0; i < tabModel.getCount(); i++) {
                tabModel.getTabAt(i).removeObserver(mTabObserver);
            }
        }
        if (mTabModelObserver != null) {
            mTabModelSelector.getTabModelFilterProvider().removeTabModelFilterObserver(
                    mTabModelObserver);
        }
        if (mTabGroupObserver != null) {
            ((TabGroupModelFilter) mTabModelSelector.getTabModelFilterProvider().getTabModelFilter(
                     false))
                    .removeTabGroupObserver(mTabGroupObserver);
            ((TabGroupModelFilter) mTabModelSelector.getTabModelFilterProvider().getTabModelFilter(
                     true))
                    .removeTabGroupObserver(mTabGroupObserver);
        }
        if (mComponentCallbacks != null) {
            mActivity.unregisterComponentCallbacks(mComponentCallbacks);
        }
<<<<<<< HEAD
    }

    void setTabActionState(@TabActionState int tabActionState) {
        if (mTabActionState == tabActionState) return;
        mTabActionState = tabActionState;
        getTabSelectionDelegate().clearSelection();

        for (int i = 0; i < mModelList.size(); i++) {
            ListItem item = mModelList.get(i);
            if (item.type != UiType.TAB) continue;
            Tab tab = getTabForIndex(i);
            // Unbind the current TabActionState properties.
            PropertyModel model = item.model;
            unbindTabActionStateProperties(model);

            model.set(TabProperties.TAB_ACTION_STATE, mTabActionState);
            bindTabActionStateProperties(tabActionState, tab, model);
        }
    }

    private void unbindTabActionStateProperties(PropertyModel model) {
        model.set(TabProperties.IS_SELECTED, false);
        for (WritableObjectPropertyKey propertyKey : TabProperties.TAB_ACTION_STATE_OBJECT_KEYS) {
            model.set(propertyKey, null);
        }
    }

    private TabActionButtonData getTabActionButtonData(
            Tab tab, @TabActionState int tabActionState) {
        if (tabActionState == TabActionState.SELECTABLE) {
            return new TabActionButtonData(
                    TabActionButtonData.TabActionButtonType.SELECT, mSelectableTabOnClickListener);
        }
        // A tab is deemed a tab group card representation if it is part of a tab group and
        // based in the tab switcher.
        boolean isTabGroup = isTabInTabGroup(tab) && mActionsOnAllRelatedTabs;
        if (ChromeFeatureList.sTabGroupPaneAndroid.isEnabled() && isTabGroup) {
            return new TabActionButtonData(
                    TabActionButtonData.TabActionButtonType.OVERFLOW,
                    getTabGroupOverflowMenuClickListener());
        }
        return new TabActionButtonData(
                TabActionButtonData.TabActionButtonType.CLOSE, mTabClosedListener);
    }

    private TabListMediator.TabActionListener getTabGroupOverflowMenuClickListener() {
        if (mTabListGroupMenuCoordinator == null) {
            TabModel tabModel = mCurrentTabGroupModelFilterSupplier.get().getTabModel();
            boolean isIncognito = tabModel.isIncognitoBranded();
            TabGroupSyncService tabGroupSyncService = isIncognito ? null : mTabGroupSyncService;
            assert mCollaborationService != null;
            CollaborationService collaborationService =
                    isIncognito
                            ? CollaborationServiceFactory.getForProfile(tabModel.getProfile())
                            : mCollaborationService;
            mTabListGroupMenuCoordinator =
                    new TabListGroupMenuCoordinator(
                            mOnMenuItemClickedCallback,
                            () -> mCurrentTabGroupModelFilterSupplier.get().getTabModel(),
                            tabGroupSyncService,
                            collaborationService);
        }
        return mTabListGroupMenuCoordinator.getTabActionListener();
    }

    private TabListMediator.TabActionListener getTabClickListener(
            Tab tab, @TabActionState int tabActionState) {
        if (tabActionState == TabActionState.SELECTABLE) {
            return mSelectableTabOnClickListener;
        } else {
            if (isTabInTabGroup(tab)
                    && mActionsOnAllRelatedTabs
                    && mGridCardOnClickListenerProvider != null) {
                return mGridCardOnClickListenerProvider.openTabGridDialog(tab);
            } else {
                return mTabSelectedListener;
=======
        if (mTabGroupTitleEditor != null) {
            mTabGroupTitleEditor.destroy();
        }
        if (mTemplateUrlObserver != null) {
            TemplateUrlServiceFactory.get().removeObserver(mTemplateUrlObserver);
        }
    }

    private void addTabInfoToModel(final PseudoTab pseudoTab, int index, boolean isSelected) {
        assert index != TabModel.INVALID_TAB_INDEX;
        // If the new tab is already in the target position of TabListModel, skip redundant
        // addition. The only exception is when we undo a group-tabs operation. In that case, it is
        // possible that the tab being added back has the same id as the PropertyModel of the
        // group.
        if (index < mModel.size()) {
            int type = mModel.get(index).type;
            PropertyModel model = mModel.get(index).model;
            if ((type == UiType.CLOSABLE || type == UiType.SELECTABLE || type == UiType.STRIP)
                    && model.get(TabProperties.TAB_ID) == pseudoTab.getId()
                    && !TabUiFeatureUtilities.isTabGroupsAndroidEnabled(mContext)) {
                return;
>>>>>>> chromium
            }
        }
        boolean showIPH = false;
        boolean isRealTab = pseudoTab.hasRealTab();
        if (mActionsOnAllRelatedTabs && !mShownIPH && isRealTab) {
            showIPH = getRelatedTabsForId(pseudoTab.getId()).size() > 1;
        }
        TabActionListener tabSelectedListener;
        if (!isRealTab) {
            tabSelectedListener = null;
        } else if (mGridCardOnClickListenerProvider == null
                || getRelatedTabsForId(pseudoTab.getId()).size() == 1
                || !mActionsOnAllRelatedTabs) {
            tabSelectedListener = mTabSelectedListener;
        } else {
            tabSelectedListener =
                    mGridCardOnClickListenerProvider.openTabGridDialog(pseudoTab.getTab());
            if (tabSelectedListener == null) {
                tabSelectedListener = mTabSelectedListener;
            }
        }

        int selectedTabBackgroundDrawableId = pseudoTab.isIncognito()
                ? R.drawable.selected_tab_background_incognito
                : R.drawable.selected_tab_background;

        int tabstripFaviconBackgroundDrawableId = pseudoTab.isIncognito()
                ? R.color.favicon_background_color_incognito
                : R.color.favicon_background_color;
        PropertyModel tabInfo =
                new PropertyModel.Builder(TabProperties.ALL_KEYS_TAB_GRID)
                        .with(TabProperties.TAB_ID, pseudoTab.getId())
                        .with(TabProperties.TITLE, getLatestTitleForTab(pseudoTab))
                        .with(TabProperties.URL_DOMAIN,
                                isRealTab ? getDomainForTab(pseudoTab.getTab()) : null)
                        .with(TabProperties.FAVICON,
                                mTabListFaviconProvider.getDefaultFaviconDrawable(
                                        pseudoTab.isIncognito()))
                        .with(TabProperties.IS_SELECTED, isSelected)
                        .with(TabProperties.IPH_PROVIDER, showIPH ? mIphProvider : null)
                        .with(CARD_ALPHA, 1f)
                        .with(TabProperties.CARD_ANIMATION_STATUS,
                                ClosableTabGridView.AnimationStatus.CARD_RESTORE)
                        .with(TabProperties.TAB_SELECTION_DELEGATE,
                                isRealTab ? getTabSelectionDelegate() : null)
                        .with(TabProperties.IS_INCOGNITO, pseudoTab.isIncognito())
                        .with(TabProperties.SELECTED_TAB_BACKGROUND_DRAWABLE_ID,
                                selectedTabBackgroundDrawableId)
                        .with(TabProperties.TABSTRIP_FAVICON_BACKGROUND_COLOR_ID,
                                tabstripFaviconBackgroundDrawableId)
                        .with(TabProperties.ACCESSIBILITY_DELEGATE, mAccessibilityDelegate)
                        .with(TabProperties.SHOULD_SHOW_PRICE_DROP_TOOLTIP, false)
                        .with(CARD_TYPE, TAB)
                        .build();

        if (TabUiFeatureUtilities.ENABLE_SEARCH_CHIP.getValue() && mUiType == UiType.CLOSABLE
                && isRealTab) {
            tabInfo.set(TabProperties.SEARCH_QUERY, getLastSearchTerm(pseudoTab.getTab()));
            tabInfo.set(TabProperties.PAGE_INFO_LISTENER,
                    SearchTermChipUtils.getSearchQueryListener(
                            pseudoTab.getTab(), mTabSelectedListener));
            tabInfo.set(TabProperties.PAGE_INFO_ICON_DRAWABLE_ID, mSearchChipIconDrawableId);
        }

        if (mUiType == UiType.SELECTABLE) {
            // Incognito in both light/dark theme is the same as non-incognito mode in dark theme.
            // Non-incognito mode and incognito in both light/dark themes in dark theme all look
            // dark.
            ColorStateList checkedDrawableColorList = AppCompatResources.getColorStateList(mContext,
                    pseudoTab.isIncognito() ? R.color.default_icon_color_dark
                                            : R.color.default_icon_color_inverse);
            ColorStateList actionButtonBackgroundColorList =
                    AppCompatResources.getColorStateList(mContext,
                            pseudoTab.isIncognito() ? R.color.default_icon_color_light
                                                    : R.color.default_icon_color);
            // TODO(995876): Update color modern_blue_300 to active_color_dark when the associated
            // bug is landed.
            ColorStateList actionbuttonSelectedBackgroundColorList =
                    AppCompatResources.getColorStateList(mContext,
                            pseudoTab.isIncognito() ? R.color.modern_blue_300
                                                    : R.color.default_control_color_active);

            tabInfo.set(TabProperties.CHECKED_DRAWABLE_STATE_LIST, checkedDrawableColorList);
            tabInfo.set(TabProperties.SELECTABLE_TAB_ACTION_BUTTON_BACKGROUND,
                    actionButtonBackgroundColorList);
            tabInfo.set(TabProperties.SELECTABLE_TAB_ACTION_BUTTON_SELECTED_BACKGROUND,
                    actionbuttonSelectedBackgroundColorList);
            tabInfo.set(
                    TabProperties.SELECTABLE_TAB_CLICKED_LISTENER, mSelectableTabOnClickListener);
        } else {
            tabInfo.set(TabProperties.TAB_SELECTED_LISTENER, tabSelectedListener);
            tabInfo.set(TabProperties.TAB_CLOSED_LISTENER, isRealTab ? mTabClosedListener : null);
            updateDescriptionString(pseudoTab, tabInfo);
            if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                updateCloseButtonDescriptionString(pseudoTab, tabInfo);
            }
        }

        if (index >= mModel.size()) {
            mModel.add(new SimpleRecyclerViewAdapter.ListItem(mUiType, tabInfo));
        } else {
            mModel.add(index, new SimpleRecyclerViewAdapter.ListItem(mUiType, tabInfo));
        }

        updateFaviconForTab(pseudoTab, null);

        if (mThumbnailProvider != null && mVisible) {
            ThumbnailFetcher callback = new ThumbnailFetcher(mThumbnailProvider, pseudoTab.getId(),
                    isSelected, isSelected && !TabUiFeatureUtilities.isTabToGtsAnimationEnabled());
            tabInfo.set(TabProperties.THUMBNAIL_FETCHER, callback);
        }
        if (pseudoTab.getTab() != null) pseudoTab.getTab().addObserver(mTabObserver);
    }

    // TODO(wychen): make this work with PseudoTab.
    private String getLastSearchTerm(Tab tab) {
        assert TabUiFeatureUtilities.ENABLE_SEARCH_CHIP.getValue();
        if (mActionsOnAllRelatedTabs && TabUiFeatureUtilities.isTabGroupsAndroidEnabled(mContext)
                && getRelatedTabsForId(tab.getId()).size() > 1) {
            return null;
        }
        return TabAttributeCache.getLastSearchTerm(tab.getId());
    }

    private int getSearchChipIconDrawableId() {
        int iconDrawableId;
        if (TabUiFeatureUtilities.ENABLE_SEARCH_CHIP_ADAPTIVE.getValue()) {
            iconDrawableId = TemplateUrlServiceFactory.get().isDefaultSearchEngineGoogle()
                    ? R.drawable.ic_logo_googleg_24dp
                    : R.drawable.ic_search;
        } else {
            iconDrawableId = R.drawable.ic_search;
        }
        return iconDrawableId;
    }

    // TODO(wychen): make this work with PseudoTab.
    private String getDomainForTab(Tab tab) {
        if (!TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(mContext)) return "";
        if (!mActionsOnAllRelatedTabs) return getDomain(tab);

        List<Tab> relatedTabs = getRelatedTabsForId(tab.getId());

        List<String> domainNames = new ArrayList<>();

        for (int i = 0; i < relatedTabs.size(); i++) {
            String domain = getDomain(relatedTabs.get(i));
            domainNames.add(domain);
        }
        // TODO(1024925): Address i18n issue for the list delimiter.
        return TextUtils.join(", ", domainNames);
    }

    private void updateDescriptionString(PseudoTab pseudoTab, PropertyModel model) {
        if (!mActionsOnAllRelatedTabs) return;
<<<<<<< HEAD
        boolean isInTabGroup = isTabInTabGroup(tab);
        int numOfRelatedTabs = getRelatedTabsForId(tab.getId()).size();
        TextResolver contentDescriptionResolver =
                (context) -> {
                    String contentDescriptionString;
                    if (isInTabGroup) {
                        String title = getLatestTitleForTab(tab, /* useDefault= */ false);
                        Resources res = context.getResources();
                        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
                        @TabGroupColorId
                        int colorId = filter.getTabGroupColorWithFallback(tab.getRootId());
                        final @StringRes int colorDescRes =
                                ColorPickerUtils.getTabGroupColorPickerItemColorAccessibilityString(
                                        colorId);
                        String colorDesc = res.getString(colorDescRes);
                        if (ChromeFeatureList.isEnabled(ChromeFeatureList.DATA_SHARING)
                                && hasCollaboration(tab)) {
                            contentDescriptionString =
                                    title.isEmpty()
                                            ? res.getQuantityString(
                                                    R.plurals
                                                            .accessibility_expand_shared_tab_group_with_color,
                                                    numOfRelatedTabs,
                                                    numOfRelatedTabs,
                                                    colorDesc)
                                            : res.getQuantityString(
                                                    R.plurals
                                                            .accessibility_expand_shared_tab_group_with_group_name_with_color,
                                                    numOfRelatedTabs,
                                                    title,
                                                    numOfRelatedTabs,
                                                    colorDesc);
                        } else {
                            contentDescriptionString =
                                    title.isEmpty()
                                            ? res.getQuantityString(
                                                    R.plurals
                                                            .accessibility_expand_tab_group_with_color,
                                                    numOfRelatedTabs,
                                                    numOfRelatedTabs,
                                                    colorDesc)
                                            : res.getQuantityString(
                                                    R.plurals
                                                            .accessibility_expand_tab_group_with_group_name_with_color,
                                                    numOfRelatedTabs,
                                                    title,
                                                    numOfRelatedTabs,
                                                    colorDesc);
                        }
                    } else {
                        contentDescriptionString = null;
                    }
                    return contentDescriptionString;
                };
        model.set(TabProperties.CONTENT_DESCRIPTION_TEXT_RESOLVER, contentDescriptionResolver);
    }

    private void updateActionButtonDescriptionString(Tab tab, PropertyModel model) {
        TextResolver descriptionTextResolver;
=======
        int numOfRelatedTabs = getRelatedTabsForId(pseudoTab.getId()).size();
        if (numOfRelatedTabs > 1) {
            String title = getLatestTitleForTab(pseudoTab);
            title = title.equals(pseudoTab.getTitle(mContext, mTitleProvider)) ? "" : title;
            model.set(TabProperties.CONTENT_DESCRIPTION_STRING,
                    title.isEmpty() ? mContext.getString(R.string.accessibility_expand_tab_group,
                            String.valueOf(numOfRelatedTabs))
                                    : mContext.getString(
                                            R.string.accessibility_expand_tab_group_with_group_name,
                                            title, String.valueOf(numOfRelatedTabs)));
        } else {
            model.set(TabProperties.CONTENT_DESCRIPTION_STRING, null);
        }
    }

    private void updateCloseButtonDescriptionString(PseudoTab pseudoTab, PropertyModel model) {
        if (!TabUiFeatureUtilities.isLaunchPolishEnabled()) return;
>>>>>>> chromium
        if (mActionsOnAllRelatedTabs) {
            int numOfRelatedTabs = getRelatedTabsForId(pseudoTab.getId()).size();
            if (numOfRelatedTabs > 1) {
                String title = getLatestTitleForTab(pseudoTab);
                title = title.equals(pseudoTab.getTitle(mContext, mTitleProvider)) ? "" : title;

<<<<<<< HEAD
                descriptionTextResolver =
                        getActionButtonDescriptionTextResolver(numOfRelatedTabs, title, tab);
                model.set(
                        TabProperties.ACTION_BUTTON_DESCRIPTION_TEXT_RESOLVER,
                        descriptionTextResolver);
=======
                if (title.isEmpty()) {
                    model.set(TabProperties.CLOSE_BUTTON_DESCRIPTION_STRING,
                            mContext.getString(R.string.accessibility_close_tab_group_button,
                                    String.valueOf(numOfRelatedTabs)));
                } else {
                    model.set(TabProperties.CLOSE_BUTTON_DESCRIPTION_STRING,
                            mContext.getString(
                                    R.string.accessibility_close_tab_group_button_with_group_name,
                                    title, String.valueOf(numOfRelatedTabs)));
                }
>>>>>>> chromium
                return;
            }
        }

<<<<<<< HEAD
        descriptionTextResolver =
                (context) -> {
                    return context.getString(
                            R.string.accessibility_tabstrip_btn_close_tab, tab.getTitle());
                };
        model.set(TabProperties.ACTION_BUTTON_DESCRIPTION_TEXT_RESOLVER, descriptionTextResolver);
=======
        model.set(CLOSE_BUTTON_DESCRIPTION_STRING,
                mContext.getString(
                        R.string.accessibility_tabstrip_btn_close_tab, pseudoTab.getTitle()));
>>>>>>> chromium
    }

    @VisibleForTesting
    protected static String getDomain(Tab tab) {
        // TODO(crbug.com/1116613) Investigate how uninitialized Tabs are appearing
        // here.
        assert tab.isInitialized();
        if (!tab.isInitialized()) {
            return "";
        }
        // TODO(crbug/783819): convert UrlUtilities to GURL
        String domain = UrlUtilities.getDomainAndRegistry(tab.getUrl().getSpec(), false);

        if (domain.isEmpty()) return tab.getUrl().getSpec();
        return domain;
    }

    @Nullable
    private SelectionDelegate<Integer> getTabSelectionDelegate() {
        return mSelectionDelegateProvider == null
                ? null
                : mSelectionDelegateProvider.getSelectionDelegate();
    }

    @VisibleForTesting
<<<<<<< HEAD
    String getLatestTitleForTab(Tab tab, boolean useDefault) {
        String originalTitle = tab.getTitle();
        if (!mActionsOnAllRelatedTabs || !isTabInTabGroup(tab)) {
            return originalTitle;
        }

        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        String storedTitle = filter.getTabGroupTitle(tab.getRootId());
        if (TextUtils.isEmpty(storedTitle)) {
            if (useDefault) {
                return TabGroupTitleUtils.getDefaultTitle(
                        mActivity, filter.getRelatedTabCountForRootId(tab.getRootId()));
            } else {
                return "";
            }
        }
        return storedTitle;
=======
    String getLatestTitleForTab(PseudoTab pseudoTab) {
        String originalTitle = pseudoTab.getTitle(mContext, mTitleProvider);
        if (!mActionsOnAllRelatedTabs || mTabGroupTitleEditor == null) return originalTitle;
        // If the group degrades to a single tab, delete the stored title.
        if (getRelatedTabsForId(pseudoTab.getId()).size() <= 1) {
            return originalTitle;
        }
        String storedTitle = mTabGroupTitleEditor.getTabGroupTitle(pseudoTab.getRootId());
        return storedTitle == null ? originalTitle : storedTitle;
>>>>>>> chromium
    }

    int selectedTabId() {
        if (mNextTabId != Tab.INVALID_TAB_ID) {
            return mNextTabId;
        }

        return mTabModelSelector.getCurrentTabId();
    }

    /**
     * Find the index of the given tab in the {@link TabListRecyclerView}.
     * Note that Tabs may have different index in {@link TabListRecyclerView} and {@link
     * TabModelSelector}, like when {@link resetWithListOfTabs} above is called with MRU mode
     * enabled.
     * @param tabId The given Tab id.
     * @return The index of the Tab in the {@link TabListRecyclerView}.
     */
    int indexOfTab(int tabId) {
        return mModel.indexFromId(tabId);
    }

    @VisibleForTesting
    void updateFaviconForTab(PseudoTab pseudoTab, @Nullable Bitmap icon) {
        int modelIndex = mModel.indexFromId(pseudoTab.getId());
        if (modelIndex == Tab.INVALID_TAB_ID) return;
        List<Tab> relatedTabList = getRelatedTabsForId(pseudoTab.getId());

        Callback<Drawable> faviconCallback = drawable -> {
            assert drawable != null;
            // Need to re-get the index because the original index can be stale when callback is
            // triggered.
            int index = mModel.indexFromId(pseudoTab.getId());
            if (index != TabModel.INVALID_TAB_INDEX && drawable != null) {
                mModel.get(index).model.set(TabProperties.FAVICON, drawable);
            }
        };

        if (mActionsOnAllRelatedTabs && relatedTabList.size() > 1) {
            if (!TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(mContext)) {
                // For tab group card in grid tab switcher, the favicon is set to be null.
                mModel.get(modelIndex).model.set(TabProperties.FAVICON, null);
                return;
            }

            // The order of the url list matches the multi-thumbnail.
            List<GURL> urls = new ArrayList<>();
            urls.add(pseudoTab.getUrl());
            for (int i = 0; urls.size() < 4 && i < relatedTabList.size(); i++) {
                if (pseudoTab.getId() == relatedTabList.get(i).getId()) continue;
                urls.add(relatedTabList.get(i).getUrl());
            }

            // For tab group card in grid tab switcher, the favicon is the composed favicon.
            mTabListFaviconProvider.getComposedFaviconImageAsync(
                    urls, pseudoTab.isIncognito(), faviconCallback);

            return;
        }
        if (!mTabListFaviconProvider.isInitialized()) {
            return;
        }

        // If there is an available icon, we fetch favicon synchronously; otherwise asynchronously.
        if (icon != null) {
            Drawable drawable = mTabListFaviconProvider.getFaviconForUrlSync(icon);
            mModel.get(modelIndex).model.set(TabProperties.FAVICON, drawable);
            return;
        }

<<<<<<< HEAD
        TabFaviconFetcher fetcher = mTabListFaviconProvider.getFaviconForTabFetcher(tab);
        model.set(TabProperties.FAVICON_FETCHER, fetcher);
=======
        mTabListFaviconProvider.getFaviconForUrlAsync(
                pseudoTab.getUrl(), pseudoTab.isIncognito(), faviconCallback);
>>>>>>> chromium
    }

    /**
     * Inserts a special {@link org.chromium.ui.modelutil.MVCListAdapter.ListItem} at given index of
     * the current {@link TabListModel}.
     *
     * @param index The index of the {@link org.chromium.ui.modelutil.MVCListAdapter.ListItem} to be
     *              inserted.
     * @param uiType The view type the model will bind to.
     * @param model The model that will be bound to a view.
     */
    void addSpecialItemToModel(int index, @UiType int uiType, PropertyModel model) {
        mModel.add(index, new SimpleRecyclerViewAdapter.ListItem(uiType, model));
    }

    /**
     * Removes a special {@link @link org.chromium.ui.modelutil.MVCListAdapter.ListItem} that
     * has the given {@code uiType} and/or its {@link PropertyModel} has the given
     * {@code itemIdentifier} from the current {@link TabListModel}.
     *
     * @param uiType The uiType to match.
     * @param itemIdentifier The itemIdentifier to match. This can be obsoleted if the {@link @link
     *         org.chromium.ui.modelutil.MVCListAdapter.ListItem} does not need additional
     *         identifier.
     */
    void removeSpecialItemFromModel(@UiType int uiType, int itemIdentifier) {
        int index = TabModel.INVALID_TAB_INDEX;
        if (uiType == UiType.MESSAGE || uiType == UiType.LARGE_MESSAGE) {
            if (itemIdentifier == MessageService.MessageType.ALL) {
                while (mModel.lastIndexForMessageItem() != TabModel.INVALID_TAB_INDEX) {
                    index = mModel.lastIndexForMessageItem();
                    mModel.removeAt(index);
                }
                return;
            }
            index = mModel.lastIndexForMessageItemFromType(itemIdentifier);
        } else if (uiType == UiType.NEW_TAB_TILE) {
            index = mModel.getIndexForNewTabTile();
        }

        if (index == TabModel.INVALID_TAB_INDEX) return;

        assert validateItemAt(index, uiType, itemIdentifier);
        mModel.removeAt(index);
    }

    private boolean validateItemAt(int index, @UiType int uiType, int itemIdentifier) {
        if (uiType == UiType.MESSAGE || uiType == UiType.LARGE_MESSAGE) {
            return mModel.get(index).type == uiType
                    && mModel.get(index).model.get(MESSAGE_TYPE) == itemIdentifier;
        } else if (uiType == UiType.NEW_TAB_TILE) {
            return mModel.get(index).type == uiType;
        }

        return false;
    }

    /**
     * The PriceWelcomeMessage should be in view when user enters the tab switcher, so we put it
     * exactly below the currently selected tab.
     *
     * @return Where the PriceWelcomeMessage should be inserted in the {@link TabListModel} when
     *         user enters the tab switcher.
     */
    int getPriceWelcomeMessageInsertionIndex() {
        assert mGridLayoutManager != null;
        int spanCount = mGridLayoutManager.getSpanCount();
        int selectedTabIndex = mModel.indexOfNthTabCard(
                mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter().index());
        int indexBelowSelectedTab = (selectedTabIndex / spanCount + 1) * spanCount;
        int indexAfterLastTab = mModel.getTabIndexBefore(mModel.size()) + 1;
        return Math.min(indexBelowSelectedTab, indexAfterLastTab);
    }

    /**
     * Update the layout of tab switcher to make it compact. Because now we have messages within the
     * tabs like PriceMessage and these messages take up the entire row, some operations like
     * closing a tab above the message card will leave a blank grid, so we need to update the
     * layout.
     */
    @VisibleForTesting
    void updateLayout() {
        // Right now we need to update layout only if there is a price welcome message card in tab
        // switcher.
        if (!PriceTrackingUtilities.isPriceWelcomeMessageCardEnabled()) return;
        assert mGridLayoutManager != null;
        int spanCount = mGridLayoutManager.getSpanCount();
        GridLayoutManager.SpanSizeLookup spanSizeLookup = mGridLayoutManager.getSpanSizeLookup();
        int spanSizeSumForCurrentRow = 0;
        int index = 0;
        for (; index < mModel.size(); index++) {
            spanSizeSumForCurrentRow += spanSizeLookup.getSpanSize(index);
            if (spanSizeSumForCurrentRow == spanCount) {
                // This row is compact, we clear and recount the spanSize for next row.
                spanSizeSumForCurrentRow = 0;
            } else if (spanSizeSumForCurrentRow > spanCount) {
                // Find a blank grid and break.
                if (mModel.get(index).type == TabProperties.UiType.LARGE_MESSAGE) break;
                spanSizeSumForCurrentRow = 0;
            }
        }
        if (spanSizeSumForCurrentRow <= spanCount) return;
        int blankSize = spanCount - (spanSizeSumForCurrentRow - spanSizeLookup.getSpanSize(index));
        for (int i = index + 1; i < mModel.size(); i++) {
            if (spanSizeLookup.getSpanSize(i) > blankSize) continue;
            mModel.move(i, index);
            // We should return after one move because once item moved, updateLayout() will be
            // called again.
            return;
        }
    }

    @VisibleForTesting
    View.AccessibilityDelegate getAccessibilityDelegateForTesting() {
        return mAccessibilityDelegate;
    }

<<<<<<< HEAD
    @VisibleForTesting
    void recordPriceAnnotationsEnabledMetrics() {
        if (mMode != TabListMode.GRID
                || mCurrentTabGroupModelFilterSupplier.get().isIncognitoBranded()
                || !mActionsOnAllRelatedTabs
                || mOriginalProfile == null
                || !PriceTrackingFeatures.isPriceAnnotationsEligible(mOriginalProfile)) {
            return;
        }
        SharedPreferencesManager preferencesManager = ChromeSharedPreferences.getInstance();
        if (System.currentTimeMillis()
                        - preferencesManager.readLong(
                                ChromePreferenceKeys
                                        .PRICE_TRACKING_ANNOTATIONS_ENABLED_METRICS_TIMESTAMP,
                                -1)
                >= PriceTrackingFeatures.getAnnotationsEnabledMetricsWindowDurationMilliSeconds()) {
            RecordHistogram.recordBooleanHistogram(
                    "Commerce.PriceDrop.AnnotationsEnabled",
                    PriceTrackingUtilities.isTrackPricesOnTabsEnabled(mOriginalProfile));
            preferencesManager.writeLong(
                    ChromePreferenceKeys.PRICE_TRACKING_ANNOTATIONS_ENABLED_METRICS_TIMESTAMP,
                    System.currentTimeMillis());
        }
    }

    /** Returns the index of the nth tab card in the model or TabList.INVALID_TAB_INDEX. */
    int getIndexOfNthTabCard(int n) {
        return mModelList.indexOfNthTabCardOrInvalid(n);
    }

    /** Returns the filter index of a tab from its view index or TabList.INVALID_TAB_INDEX. */
    int indexOfTabCardsOrInvalid(int viewIndex) {
        return mModelList.indexOfTabCardsOrInvalid(viewIndex);
    }

    /**
     * @param tab the {@link Tab} to find the group index of.
     * @return the index for the tab group within {@link mModelList}
     */
    int getIndexForTabWithRelatedTabs(Tab tab) {
        return getIndexForTabIdWithRelatedTabs(tab.getId());
    }

    /**
     * @param tabId the {@link Tab} to find the group index of.
     * @return the index for the tab group within {@link mModelList}
     */
    int getIndexForTabIdWithRelatedTabs(int tabId) {
        List<Integer> relatedTabIds = getRelatedTabsIds(tabId);
        if (!relatedTabIds.isEmpty()) {
            for (int i = 0; i < mModelList.size(); i++) {
                PropertyModel model = mModelList.get(i).model;
                if (model.get(CARD_TYPE) != TAB) continue;

                int modelTabId = model.get(TAB_ID);
                if (relatedTabIds.contains(modelTabId)) {
                    return i;
                }
            }
        }
        return TabModel.INVALID_TAB_INDEX;
    }

    /** Provides the tab ID for the most recently swiped tab. */
    @NonNull
    ObservableSupplier<Integer> getRecentlySwipedTabSupplier() {
        return mTabGridItemTouchHelperCallback.getRecentlySwipedTabIdSupplier();
    }

    /**
     * Returns the index in {@link mModelList} of the group with {@code rootId} and the {@link Tab}
     * representing the group. Will be null if the entry is not present, the tab cannot be found, or
     * the tab is not part of a tab group.
     */
    private @Nullable Pair<Integer, Tab> getIndexAndTabForRootId(int rootId) {
        int index = getIndexForTabIdWithRelatedTabs(rootId);
        if (index == TabModel.INVALID_TAB_INDEX) return null;

        Tab tab = getTabForIndex(index);
        // If the found tab has a different root ID from the rootId set in the args then the update
        // is likely for a group that no longer exists so we should drop the update.
        if (tab == null
                || tab.getRootId() != rootId
                || !mCurrentTabGroupModelFilterSupplier.get().isTabInTabGroup(tab)) {
            return null;
        }
        return Pair.create(index, tab);
    }

    private @Nullable Tab getTabForIndex(int index) {
        return mCurrentTabGroupModelFilterSupplier
                .get()
                .getTabModel()
                .getTabById(mModelList.get(index).model.get(TabProperties.TAB_ID));
    }

    Tab getTabToAddDelayedForTesting() {
        return mTabToAddDelayed;
    }

    void setComponentNameForTesting(String name) {
        var oldValue = mComponentName;
        mComponentName = name;
        ResettersForTesting.register(() -> mComponentName = oldValue);
    }

    private void onTabGroupModelFilterChanged(
            @Nullable TabGroupModelFilter newFilter, @Nullable TabGroupModelFilter oldFilter) {
        removeObservers(oldFilter);

        // The observers will be bound to the newFilter's when the model is reset for with tabs for
        // that filter for the first time. Doing this on the first reset after changing models
        // makes sense as otherwise we will be observing updates when the mModelList contains tabs
        // for
        // the oldFilter which can result in invalid updates.
    }

    private void addObservers(TabGroupModelFilter filter, @NonNull List<Tab> tabs) {
        assert filter != null;

        if (mActionsOnAllRelatedTabs) {
            for (Tab rootTab : tabs) {
                for (Tab tab : filter.getRelatedTabList(rootTab.getId())) {
                    tab.addObserver(mTabObserver);
                }
            }
        } else {
            for (Tab tab : tabs) {
                tab.addObserver(mTabObserver);
            }
        }

        filter.addObserver(mTabModelObserver);
        filter.addTabGroupObserver(mTabGroupObserver);
    }

    private void removeObservers(@Nullable TabGroupModelFilter filter) {
        if (filter == null) return;

        TabModel tabModel = filter.getTabModel();
        if (tabModel != null) {
            // Observers are added when tabs are shown via addTabInfoToModel(). When switching
            // filters the TabObservers should be removed from all the tabs in the previous model.
            // If no observer was added this will no-op. Previously this was only done in
            // destroy(), but that left observers behind on the inactive model.
            for (int i = 0; i < tabModel.getCount(); i++) {
                tabModel.getTabAt(i).removeObserver(mTabObserver);
            }
        }
        filter.removeObserver(mTabModelObserver);
        filter.removeTabGroupObserver(mTabGroupObserver);
    }

    /**
     * @param itemIdentifier The itemIdentifier to match.
     * @return whether a special {@link org.chromium.ui.modelutil.MVCListAdapter.ListItem} with the
     *     given {@code itemIdentifier} for its {@link PropertyModel} exists in the current {@link
     *     TabListModel}.
     */
    boolean specialItemExistsInModel(@MessageService.MessageType int itemIdentifier) {
        if (itemIdentifier == MessageService.MessageType.ALL) {
            return mModelList.lastIndexForMessageItem() != TabModel.INVALID_TAB_INDEX;
        }
        return mModelList.lastIndexForMessageItemFromType(itemIdentifier)
                != TabModel.INVALID_TAB_INDEX;
    }

    boolean isLastItemMessage() {
        if (mModelList.size() == 0) return false;
        int index = mModelList.lastIndexForMessageItem();
        if (index == TabModel.INVALID_TAB_INDEX) return false;
        return index == mModelList.size() - 1;
    }

    /**
     * Prepare and run the Quick Delete animation on the tab list.
     *
     * @param onAnimationEnd Runnable that is invoked when the animation is completed.
     * @param tabs The tabs to fade with the animation. These tabs will get closed after the
     *     animation is complete.
     * @param recyclerView The {@link TabListRecyclerView} that is showing the tab list UI.
     */
    public void showQuickDeleteAnimation(
            @NonNull Runnable onAnimationEnd,
            @NonNull List<Tab> tabs,
            @NonNull TabListRecyclerView recyclerView) {
        recyclerView.setBlockTouchInput(true);
        Drawable originalForeground = recyclerView.getForeground();

        // Prepare the tabs that will be hidden by the animation.
        TreeMap<Integer, List<Integer>> bottomValuesToTabIndexes = new TreeMap<>();
        getOrderOfTabsForQuickDeleteAnimation(recyclerView, tabs, bottomValuesToTabIndexes);

        setQuickDeleteAnimationStatusForTabIndexes(
                CollectionUtil.flatten(bottomValuesToTabIndexes.values()),
                QuickDeleteAnimationStatus.TAB_PREPARE);

        // Create the gradient drawable and prepare the animator.
        int tabGridHeight = recyclerView.getHeight();
        int intersectionHeight =
                QuickDeleteAnimationGradientDrawable.getAnimationsIntersectionHeight(tabGridHeight);
        QuickDeleteAnimationGradientDrawable gradientDrawable =
                QuickDeleteAnimationGradientDrawable.createQuickDeleteWipeAnimationDrawable(
                        mActivity,
                        tabGridHeight,
                        mCurrentTabGroupModelFilterSupplier.get().isIncognitoBranded());

        ObjectAnimator wipeAnimation = gradientDrawable.createWipeAnimator(tabGridHeight);

        wipeAnimation.addUpdateListener(
                valueAnimator -> {
                    if (bottomValuesToTabIndexes.isEmpty()) return;

                    float value = (float) valueAnimator.getAnimatedValue();
                    int bottomVal = bottomValuesToTabIndexes.lastKey();
                    if (bottomVal >= Math.round(value) + intersectionHeight) {
                        setQuickDeleteAnimationStatusForTabIndexes(
                                bottomValuesToTabIndexes.get(bottomVal),
                                QuickDeleteAnimationStatus.TAB_HIDE);
                        bottomValuesToTabIndexes.remove(bottomVal);
                    }
                });

        wipeAnimation.addListener(
                new AnimatorListenerAdapter() {
                    @Override
                    public void onAnimationEnd(Animator animation) {
                        recyclerView.setBlockTouchInput(false);
                        recyclerView.setForeground(originalForeground);
                        onAnimationEnd.run();
                    }
                });

        recyclerView.setForeground(gradientDrawable);
        wipeAnimation.start();
    }

    // TabListNotificationHandler implementation.
    @Override
    public void updateTabStripNotificationBubble(
            Set<Integer> tabIdsToBeUpdated, boolean hasUpdate) {
        assert mMode == TabListMode.STRIP;

        Callback<PropertyModel> updateTabStripItemCallback =
                (model) -> {
                    model.set(TabProperties.HAS_NOTIFICATION_BUBBLE, hasUpdate);
                };

        forAllTabListItems(tabIdsToBeUpdated, updateTabStripItemCallback);
    }

    @Override
    public void updateTabCardLabels(Map<Integer, TabCardLabelData> labelData) {
        assert mMode == TabListMode.GRID;

        Callback<PropertyModel> updateTabCardLabel =
                (model) -> {
                    int tabId = model.get(TabProperties.TAB_ID);
                    model.set(TabProperties.TAB_CARD_LABEL_DATA, labelData.get(tabId));
                };
        forAllTabListItems(labelData.keySet(), updateTabCardLabel);
    }

    private void forAllTabListItems(
            Set<Integer> tabIdsToBeUpdated, Callback<PropertyModel> updateCallback) {
        for (int i = 0; i < mModelList.size(); i++) {
            PropertyModel model = mModelList.get(i).model;
            if (model.get(CARD_TYPE) != TAB) continue;

            int tabId = model.get(TabProperties.TAB_ID);
            if (tabIdsToBeUpdated.contains(tabId)) {
                updateCallback.onResult(model);
            }
        }
    }

    /**
     * Gets the order of tabs to be hidden with the animation starting from the bottom up.
     *
     * @param recyclerView to get the position of tabs within the {@link TabListRecyclerView}.
     * @param tabs The tabs to fade with the animation.
     * @param bottomValuesToTabIndexes the {@link TreeMap} to map a list of sorted bottom values to
     *     tabs that have these bottom values.
=======
    /**
     * These functions are wrapped in an inner class here for the formal equivalence checker, and
     * it has to be at the end of the file. Otherwise the lambda and interface orders would be
     * changed, resulting in differences.
>>>>>>> chromium
     */
    @VisibleForTesting
    static class SearchTermChipUtils {
        static @VisibleForTesting Boolean sIsSearchChipAdaptiveIconEnabledForTesting;

        private static TabObserver sLazyNavigateToLastSearchQuery = new EmptyTabObserver() {
            @Override
            public void onPageLoadStarted(Tab tab, GURL url) {
                assert tab.getWebContents() != null;
                if (tab.getWebContents() == null) return;

<<<<<<< HEAD
            // Ignore tabs that are outside the screen view.
            if (tabRect == null) continue;

            int bottom = tabRect.bottom;

            if (bottomValuesToTabIndexes.containsKey(bottom)) {
                bottomValuesToTabIndexes.get(bottom).add(index);
            } else {
                bottomValuesToTabIndexes.put(bottom, new ArrayList<>(List.of(index)));
            }
        }
    }

    /**
     * @param tabs The full list of tabs that will be closed with Quick Delete.
     * @return a filtered list of unique tabs that the animation should run on. This will ignore
     *     tabs with other related tabs unless all of it's related tabs are included in the list of
     *     tabs to be closed.
     */
    private Set<Tab> filterQuickDeleteTabsForAnimation(List<Tab> tabs) {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        assert filter != null;

        Set<Tab> unfilteredTabs = new HashSet<>(tabs);
        Set<Tab> filteredTabs = new HashSet<>();
        Set<Integer> checkedRootIds = new HashSet<>();

        for (Tab tab : unfilteredTabs) {
            if (!filter.isTabInTabGroup(tab)) {
                filteredTabs.add(tab);
                continue;
            }

            if (checkedRootIds.contains(tab.getRootId())) continue;
            checkedRootIds.add(tab.getRootId());

            List<Tab> relatedTabs = filter.getRelatedTabList(tab.getId());
            if (unfilteredTabs.containsAll(relatedTabs)) {
                int groupIndex = filter.indexOf(tab);
                Tab groupTab = filter.getTabAt(groupIndex);
                filteredTabs.add(groupTab);
            }
        }

        return filteredTabs;
    }

    private void setQuickDeleteAnimationStatusForTabIndexes(
            List<Integer> indexes, @QuickDeleteAnimationStatus int animationStatus) {
        for (int index : indexes) {
            mModelList
                    .get(index)
                    .model
                    .set(TabProperties.QUICK_DELETE_ANIMATION_STATUS, animationStatus);
        }
    }

    @VisibleForTesting
    void onMenuItemClicked(@IdRes int menuId, Token tabGroupId, @Nullable String collaborationId) {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        int tabId = filter.getGroupLastShownTabId(tabGroupId);
        if (tabId == Tab.INVALID_TAB_ID) return;

        if (menuId == R.id.close_tab_group || menuId == R.id.delete_tab_group) {
            boolean hideTabGroups = menuId == R.id.close_tab_group;
            if (hideTabGroups) {
                RecordUserAction.record("TabGroupItemMenu.Close");
            } else {
                RecordUserAction.record("TabGroupItemMenu.Delete");
            }
            setUseShrinkCloseAnimation(tabId, /* useShrinkCloseAnimation= */ true);
            onGroupClosedFrom(tabId);
            TabUiUtils.closeTabGroup(
                    filter, tabId, hideTabGroups, getOnMaybeTabClosedCallback(tabId));
        } else if (menuId == R.id.edit_group_name) {
            RecordUserAction.record("TabGroupItemMenu.Rename");
            renameTabGroup(tabId);
        } else if (menuId == R.id.ungroup_tab) {
            RecordUserAction.record("TabGroupItemMenu.Ungroup");
            TabUiUtils.ungroupTabGroup(filter, tabId);
        } else if (menuId == R.id.delete_shared_group) {
            RecordUserAction.record("TabGroupItemMenu.DeleteShared");
            TabUiUtils.exitSharedTabGroupWithDialog(
                    mActivity, filter, mActionConfirmationManager, mModalDialogManager, tabId);
        } else if (menuId == R.id.leave_group) {
            RecordUserAction.record("TabGroupItemMenu.LeaveShared");
            TabUiUtils.exitSharedTabGroupWithDialog(
                    mActivity, filter, mActionConfirmationManager, mModalDialogManager, tabId);
        } else if (menuId == R.id.share_group) {
            assert mDataSharingTabManager != null;
            RecordUserAction.record("TabGroupItemMenu.ShareGroup");
            int index = mModelList.indexFromId(tabId);
            PropertyModel model = mModelList.get(index).model;
            TabUiUtils.startShareTabGroupFlow(
                    mActivity,
                    filter,
                    mDataSharingTabManager,
                    tabId,
                    model.get(TabProperties.TITLE));
        }
    }

    private void renameTabGroup(int tabId) {
        TabModel tabModel = mCurrentTabGroupModelFilterSupplier.get().getTabModel();
        int rootId = tabModel.getTabById(tabId).getRootId();
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();

        var tabGroupVisualDataDialogManager =
                new TabGroupVisualDataDialogManager(
                        mActivity,
                        mModalDialogManager,
                        TabGroupVisualDataDialogManager.DialogType.TAB_GROUP_EDIT,
                        R.string.tab_group_rename_dialog_title);

        ModalDialogProperties.Controller dialogController =
                new ModalDialogProperties.Controller() {
                    @Override
                    public void onClick(PropertyModel model, int buttonType) {
                        if (buttonType == ModalDialogProperties.ButtonType.POSITIVE
                                && !tabGroupVisualDataDialogManager.validateCurrentGroupTitle()) {
                            tabGroupVisualDataDialogManager.focusCurrentGroupTitle();
                            return;
                        }

                        final @DialogDismissalCause int cause;
                        if (buttonType == ModalDialogProperties.ButtonType.POSITIVE) {
                            cause = DialogDismissalCause.POSITIVE_BUTTON_CLICKED;
                        } else {
                            cause = DialogDismissalCause.NEGATIVE_BUTTON_CLICKED;
                        }

                        mModalDialogManager.dismissDialog(model, cause);
                    }

                    @Override
                    public void onDismiss(PropertyModel model, int dismissalCause) {
                        if (dismissalCause == DialogDismissalCause.POSITIVE_BUTTON_CLICKED) {
                            @TabGroupColorId
                            int oldColorId = filter.getTabGroupColorWithFallback(rootId);
                            @TabGroupColorId
                            int currentColorId =
                                    tabGroupVisualDataDialogManager.getCurrentColorId();
                            boolean didChangeColor = oldColorId != currentColorId;
                            if (didChangeColor) {
                                filter.setTabGroupColor(rootId, currentColorId);
                                RecordUserAction.record("TabGroup.RenameDialog.ColorChanged");
                            }

                            String defaultGroupTitle =
                                    tabGroupVisualDataDialogManager.getDefaultGroupTitle();
                            String inputGroupTitle =
                                    tabGroupVisualDataDialogManager.getCurrentGroupTitle();
                            boolean didChangeTitle =
                                    !Objects.equals(defaultGroupTitle, inputGroupTitle);
                            // This check must be included in case the user has a null title
                            // which is displayed as a tab count and chooses not to change it.
                            if (didChangeTitle) {
                                filter.setTabGroupTitle(rootId, inputGroupTitle);
                                RecordUserAction.record("TabGroup.RenameDialog.TitleChanged");
                            }
                        }

                        tabGroupVisualDataDialogManager.hideDialog();
                    }
                };

        tabGroupVisualDataDialogManager.showDialog(rootId, filter, dialogController);
    }

    private TextResolver getActionButtonDescriptionTextResolver(
            int numOfRelatedTabs, String title, Tab tab) {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        @TabGroupColorId int colorId = filter.getTabGroupColorWithFallback(tab.getRootId());
        final @StringRes int colorDescRes =
                ColorPickerUtils.getTabGroupColorPickerItemColorAccessibilityString(colorId);
        String colorDesc = mActivity.getResources().getString(colorDescRes);
        return (context) -> {
            Resources res = context.getResources();
            if (ChromeFeatureList.sTabGroupPaneAndroid.isEnabled()) {
                String descriptionTitle = title;
                if (TextUtils.isEmpty(descriptionTitle)) {
                    descriptionTitle =
                            TabGroupTitleUtils.getDefaultTitle(mActivity, numOfRelatedTabs);
                }
                if (!ChromeFeatureList.isEnabled(ChromeFeatureList.DATA_SHARING)
                        || !hasCollaboration(tab)) {
                    return res.getString(
                            R.string
                                    .accessibility_open_tab_group_overflow_menu_with_group_name_with_color,
                            descriptionTitle,
                            colorDesc);
                } else {
                    return res.getString(
                            R.string
                                    .accessibility_open_shared_tab_group_overflow_menu_with_group_name_with_color,
                            descriptionTitle,
                            colorDesc);
                }
            } else {
                if (TextUtils.isEmpty(title)) {
                    return res.getQuantityString(
                            R.plurals.accessibility_close_tab_group_button_with_color,
                            numOfRelatedTabs,
                            numOfRelatedTabs,
                            colorDesc);
                } else {
                    return res.getQuantityString(
                            R.plurals
                                    .accessibility_close_tab_group_button_with_group_name_with_color,
                            numOfRelatedTabs,
                            title,
                            numOfRelatedTabs,
                            colorDesc);
                }
            }
        };
    }

    /** Check if the current tab group's tab representation is being shared. */
    private boolean hasCollaboration(Tab tab) {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        TabModel tabModel = filter.getTabModel();
        if (tabModel.isIncognitoBranded()) return false;

        @Nullable TabGroupSyncService tabGroupSyncService = null;
        if (TabGroupSyncFeatures.isTabGroupSyncEnabled(tab.getProfile())) {
            tabGroupSyncService = TabGroupSyncServiceFactory.getForProfile(mOriginalProfile);
        }
        @Nullable
        String collaborationId =
                TabShareUtils.getCollaborationIdOrNull(tab.getId(), tabModel, tabGroupSyncService);
        return TabShareUtils.isCollaborationIdValid(collaborationId);
    }

    private void setUseShrinkCloseAnimation(int tabId, boolean useShrinkCloseAnimation) {
        if (mMode != TabListMode.GRID) return;

        @Nullable PropertyModel model = getModelFromId(tabId);
        if (model != null) {
            model.set(TabProperties.USE_SHRINK_CLOSE_ANIMATION, useShrinkCloseAnimation);
        }
    }

    @VisibleForTesting
    @Nullable
    Callback<Boolean> getOnMaybeTabClosedCallback(int tabId) {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();

        Tab tab = filter.getTabModel().getTabById(tabId);
        if (tab == null) return null;

        return (didClose) -> {
            if (!didClose) {
                sTabClosedFromMapTabClosedFromMap.remove(tabId);
                setUseShrinkCloseAnimation(tabId, /* useShrinkCloseAnimation= */ false);
                int modelIndex = mModelList.indexFromId(tabId);
                if (modelIndex != TabModel.INVALID_TAB_INDEX) {
                    resetSwipe(modelIndex);
                }
                return;
            }

            RecordUserAction.record("MobileTabClosed." + mComponentName);

            // Special case in defense of a group not being completely closed. We need to find the
            // group and reset it.
            @Nullable
            Pair<Integer, PropertyModel> indexAndModel =
                    getIndexAndPropertyModelForGroup(filter, tab.getTabGroupId());
            if (indexAndModel != null) {
                if (mMode == TabListMode.GRID) {
                    indexAndModel.second.set(TabProperties.USE_SHRINK_CLOSE_ANIMATION, false);
                }
                resetSwipe(indexAndModel.first);
=======
                // Directly calling navigateToLastSearchQuery() would lead to unsafe re-entrant
                // calls to NavigateToPendingEntry.
                PostTask.postTask(
                        UiThreadTaskTraits.USER_BLOCKING, () -> navigateToLastSearchQuery(tab));
                tab.removeObserver(sLazyNavigateToLastSearchQuery);
>>>>>>> chromium
            }
        };

<<<<<<< HEAD
    private void resetSwipe(int index) {
        if (index < 0 || index >= mModelList.size()) return;
        // The view element has been removed. We need to bring that back. This is done by just
        // triggering a model update for that index.
        mModelList.update(index, mModelList.get(index));
    }

    private @Nullable Pair<Integer, PropertyModel> getIndexAndPropertyModelForGroup(
            TabGroupModelFilter filter, @Nullable Token tabGroupId) {
        if (tabGroupId == null) return null;

        int rootId = filter.getRootIdFromStableId(tabGroupId);
        if (rootId == Tab.INVALID_TAB_ID) return null;

        List<Integer> ids = filter.getRelatedTabIds(rootId);
        for (int id : ids) {
            int index = mModelList.indexFromId(id);
            if (index == TabModel.INVALID_TAB_INDEX) continue;

            @Nullable PropertyModel model = mModelList.get(index).model;
            if (model != null) {
                return Pair.create(index, model);
            }
        }
        return null;
    }

    private PropertyModel getModelFromId(int tabId) {
        int modelIndex = mModelList.indexFromId(tabId);
        if (modelIndex == TabModel.INVALID_TAB_INDEX) return null;
        return mModelList.get(modelIndex).model;
    }
=======
        @VisibleForTesting
        static void navigateToLastSearchQuery(Tab tab) {
            if (tab.getWebContents() == null) {
                tab.addObserver(sLazyNavigateToLastSearchQuery);
                return;
            }
            NavigationController controller = tab.getWebContents().getNavigationController();
            NavigationHistory history = controller.getNavigationHistory();
            for (int i = history.getCurrentEntryIndex() - 1; i >= 0; i--) {
                int offset = i - history.getCurrentEntryIndex();
                if (!controller.canGoToOffset(offset)) continue;
>>>>>>> chromium

                GURL url = history.getEntryAtIndex(i).getOriginalUrl();
                String query = TemplateUrlServiceFactory.get().getSearchQueryForUrl(url);
                if (TextUtils.isEmpty(query)) continue;

                tab.loadUrl(new LoadUrlParams(url.getSpec(), PageTransition.KEYWORD_GENERATED));
                return;
            }
        }

<<<<<<< HEAD
        assert colorId != TabGroupColorUtils.INVALID_COLOR_ID
                : "Tab in tab group should always have valid colors.";
        assert mMode != TabListMode.STRIP : "Tab group colors are not applicable to strip mode.";

        if (provider == null) {
            provider =
                    new TabGroupColorViewProvider(
                            mActivity,
                            tabGroupId,
                            tab.isIncognitoBranded(),
                            colorId,
                            mTabGroupSyncService,
                            mDataSharingService,
                            mCollaborationService);
            model.set(TAB_GROUP_COLOR_VIEW_PROVIDER, provider);
        } else {
            provider.setTabGroupId(tabGroupId);
            provider.setTabGroupColorId(colorId);
=======
        private static TabActionListener getSearchQueryListener(
                Tab originalTab, TabActionListener select) {
            return (tabId) -> {
                if (originalTab == null) return;
                assert tabId == originalTab.getId();
                RecordUserAction.record("TabGrid.TabSearchChipTapped");
                select.run(tabId);
                navigateToLastSearchQuery(originalTab);
            };
>>>>>>> chromium
        }
    }

    private boolean isShowingTabsInMRUOrder() {
        return TabSwitcherCoordinator.isShowingTabsInMRUOrder(mMode);
    }
}
