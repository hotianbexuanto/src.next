// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tabmodel;

import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabSelectionType;
import org.chromium.chrome.browser.tab.state.CriticalPersistedTabData;
import org.chromium.content_public.browser.WebContents;

import java.util.ArrayList;
import java.util.List;

/**
 * A set of convenience methods used for interacting with {@link TabList}s and {@link TabModel}s.
 */
public class TabModelUtils {
    private TabModelUtils() {}

    /**
<<<<<<< HEAD
=======
     * @param model The {@link TabModel} to act on.
     * @param index The index of the {@link Tab} to close.
     * @return      {@code true} if the {@link Tab} was found.
     */
    public static boolean closeTabByIndex(TabModel model, int index) {
        Tab tab = model.getTabAt(index);
        if (tab == null) return false;

        return model.closeTab(tab);
    }

    /**
     * @param model The {@link TabModel} to act on.
     * @param tabId The id of the {@link Tab} to close.
     * @return      {@code true} if the {@link Tab} was found.
     */
    public static boolean closeTabById(TabModel model, int tabId) {
        return closeTabById(model, tabId, false);
    }

    /**
     * @param model   The {@link TabModel} to act on.
     * @param tabId   The id of the {@link Tab} to close.
     * @param canUndo Whether or not this closure can be undone.
     * @return        {@code true} if the {@link Tab} was found.
     */
    public static boolean closeTabById(TabModel model, int tabId, boolean canUndo) {
        Tab tab = TabModelUtils.getTabById(model, tabId);
        if (tab == null) return false;

        return model.closeTab(tab, true, false, canUndo);
    }

    /**
     * @param model The {@link TabModel} to act on.
     * @return      {@code true} if the {@link Tab} was found.
     */
    public static boolean closeCurrentTab(TabModel model) {
        Tab tab = TabModelUtils.getCurrentTab(model);
        if (tab == null) return false;

        return model.closeTab(tab);
    }

    /**
>>>>>>> chromium
     * Find the index of the {@link Tab} with the specified id.
     * @param model The {@link TabModel} to act on.
     * @param tabId The id of the {@link Tab} to find.
     * @return      Specified {@link Tab} index or {@link TabList#INVALID_TAB_INDEX} if the
     *              {@link Tab} is not found
     */
    public static int getTabIndexById(TabList model, int tabId) {
        int count = model.getCount();

        for (int i = 0; i < count; i++) {
            Tab tab = model.getTabAt(i);
            if (tab.getId() == tabId) return i;
        }

        return TabModel.INVALID_TAB_INDEX;
    }

    /**
     * Find the {@link Tab} with the specified id.
     * @param model The {@link TabModel} to act on.
     * @param tabId The id of the {@link Tab} to find.
     * @return      Specified {@link Tab} or {@code null} if the {@link Tab} is not found
     */
    public static Tab getTabById(TabList model, int tabId) {
        int index = getTabIndexById(model, tabId);
        if (index == TabModel.INVALID_TAB_INDEX) return null;
        return model.getTabAt(index);
    }

    /**
     * Find the {@link Tab} index whose URL matches the specified URL.
     * @param model The {@link TabModel} to act on.
     * @param url   The URL to search for.
     * @return      Specified {@link Tab} or {@code null} if the {@link Tab} is not found
     */
    public static int getTabIndexByUrl(TabList model, String url) {
        int count = model.getCount();

        for (int i = 0; i < count; i++) {
            if (model.getTabAt(i).getUrl().getSpec().contentEquals(url)) return i;
        }

        return TabModel.INVALID_TAB_INDEX;
    }

    /**
     * Get the currently selected {@link Tab} id.
     * @param model The {@link TabModel} to act on.
     * @return      The id of the currently selected {@link Tab}.
     */
    public static int getCurrentTabId(TabList model) {
        Tab tab = getCurrentTab(model);
        if (tab == null) return Tab.INVALID_TAB_ID;

        return tab.getId();
    }

    /**
     * Get the currently selected {@link Tab}.
     * @param model The {@link TabModel} to act on.
     * @returns     The current {@link Tab} or {@code null} if no {@link Tab} is selected
     */
    public static Tab getCurrentTab(TabList model) {
        int index = model.index();
        if (index == TabModel.INVALID_TAB_INDEX) return null;

        return model.getTabAt(index);
    }

    /**
     * @param model The {@link TabModel} to act on.
     * @return      The currently active {@link WebContents}, or {@code null} if no {@link Tab}
     *              is selected or the selected {@link Tab} has no current {@link WebContents}.
     */
    public static WebContents getCurrentWebContents(TabList model) {
        Tab tab = getCurrentTab(model);
        if (tab == null) return null;

        return tab.getWebContents();
    }

    /**
     * A helper method that automatically passes {@link TabSelectionType#FROM_USER} as the selection
     * type to {@link TabModel#setIndex(int, TabSelectionType)}.
     * @param model The {@link TabModel} to act on.
     * @param index The index of the {@link Tab} to select.
     */
    public static void setIndex(TabModel model, int index) {
        model.setIndex(index, TabSelectionType.FROM_USER);
    }
<<<<<<< HEAD

    /**
     * Returns the most recently visited Tab in the specified TabList that is not {@code tabId}.
     *
     * @param model The {@link TabModel} to act on.
     * @param tabIdToSkip The ID of the {@link Tab} to skip or {@link Tab.INVALID_TAB_ID}.
     * @return the most recently visited Tab or null if none can be found.
     */
    public static Tab getMostRecentTab(TabList model, int tabIdToSkip) {
        @Nullable Tab mostRecentTab = null;
        long mostRecentTabTime = 0;
        for (int i = 0; i < model.getCount(); i++) {
            final Tab tab = model.getTabAt(i);
            if (tab.getId() == tabIdToSkip || tab.isClosing()) continue;

            final long timestamp = tab.getTimestampMillis();
            if (timestamp != Tab.INVALID_TIMESTAMP && mostRecentTabTime < timestamp) {
                mostRecentTabTime = timestamp;
                mostRecentTab = tab;
=======

    /**
     * Returns all the Tabs in the specified TabList that were opened from the Tab with the
     * specified ID. The returned Tabs are in the same order as in the TabList.
     * @param model The {@link TabModel} to act on.
     * @param tabId The ID of the Tab whose children should be returned.
     */
    public static List<Tab> getChildTabs(TabList model, int tabId) {
        Tab tab = model.getTabAt(tabId);

        ArrayList<Tab> childTabs = new ArrayList<Tab>();
        for (int i = 0; i < model.getCount(); i++) {
            if (CriticalPersistedTabData.from(model.getTabAt(i)).getParentId() == tabId) {
                childTabs.add(model.getTabAt(i));
>>>>>>> chromium
            }
        }

<<<<<<< HEAD
    /**
     * Executes an {@link Callback} when {@link TabModelSelector#isTabStateInitialized()} becomes
     * true. This will happen immediately and synchronously if the tab state is already initialized.
     *
     * @param tabModelSelector The {@link TabModelSelector} to act on.
     * @param callback The callback to be run once tab state is initialized, receiving a
     *     tabModelSelector.
     */
    public static void runOnTabStateInitialized(
            @NonNull TabModelSelector tabModelSelector,
            @NonNull Callback<TabModelSelector> callback) {
        if (tabModelSelector.isTabStateInitialized()) {
            callback.onResult(tabModelSelector);
        } else {
            TabModelSelectorObserver observer =
                    new TabModelSelectorObserver() {
                        @Override
                        public void onTabStateInitialized() {
                            tabModelSelector.removeObserver(this);
                            callback.onResult(tabModelSelector);
                        }

                        @Override
                        public void onDestroyed() {
                            tabModelSelector.removeObserver(this);
                        }
                    };

            tabModelSelector.addObserver(observer);
        }
    }

    /**
     * Similar to the above function, but waits for all provided {@link TabModelSelector}s to
     * initialize (in series).
     */
    public static void runOnTabStateInitialized(
            Runnable callback, @NonNull TabModelSelector... tabModelSelectors) {
        runOnTabStateInitializedImpl(callback, /* currentIndex= */ 0, tabModelSelectors);
    }

    private static void runOnTabStateInitializedImpl(
            Runnable callback, int currentIndex, @NonNull TabModelSelector... tabModelSelectors) {
        if (currentIndex >= tabModelSelectors.length) {
            callback.run();
            return;
        }
        runOnTabStateInitialized(
                tabModelSelectors[currentIndex],
                (selector) -> {
                    runOnTabStateInitializedImpl(callback, currentIndex + 1, tabModelSelectors);
                });
    }

    /**
     * Similar to {@link #runOnTabStateInitialized(TabModelSelector, Callback)} but instead of
     * taking a callback, it exposes a {@link OneshotSupplier}. This can be convenient for callers
     * that want to combine multiple suppliers with something like {@link
     * SupplierUtils#waitForAll(Runnable, Supplier[])}.
     *
     * <p>Note that, unlike {@link #runOnTabStateInitialized(TabModelSelector, Callback)}, this
     * approach does not take care to ensure synchronous execution even when things are already
     * satisfied. Depending on the input supplier type, this approach is likely to get stuck on the
     * resulting post from adding the {@link OneShotCallback} observer.
     *
     * @param tabModelSelectorSupplier A supplier of a maybe initialized tab model selector.
     * @return A oneshot supplier that will only be set when initialization is done.
     */
    public static OneshotSupplier<TabModelSelector> onInitializedTabModelSelector(
            ObservableSupplier<TabModelSelector> tabModelSelectorSupplier) {
        OneshotSupplierImpl<TabModelSelector> delegate = new OneshotSupplierImpl<>();
        new OneShotCallback<>(
                tabModelSelectorSupplier,
                (tabModelSelector) -> {
                    if (tabModelSelector.isTabStateInitialized()) {
                        delegate.set(tabModelSelector);
                    } else {
                        tabModelSelector.addObserver(
                                new TabModelSelectorObserver() {
                                    @Override
                                    public void onTabStateInitialized() {
                                        tabModelSelector.removeObserver(this);
                                        delegate.set(tabModelSelector);
                                    }
                                });
                    }
                });
        return delegate;
    }

    /**
     * @param tab The {@link Tab} to find the {@link TabGroupModelFilter} for.
     * @return the associated {@link TabGroupModelFilter} if found or null.
     */
    public static TabGroupModelFilter getTabGroupModelFilterByTab(@NonNull Tab tab) {
        final WindowAndroid windowAndroid = tab.getWindowAndroid();
        if (windowAndroid == null) return null;

        // Support archived tab model querying
        final TabModelSelector archivedTabModelSelector =
                ArchivedTabModelSelectorHolder.getInstance(tab.getProfile());
        if (archivedTabModelSelector != null
                && archivedTabModelSelector.getTabById(tab.getId()) != null) {
            return archivedTabModelSelector
                    .getTabGroupModelFilterProvider()
                    .getTabGroupModelFilter(/* isIncognito= */ false);
        }

        final ObservableSupplier<TabModelSelector> supplier =
                TabModelSelectorSupplier.from(windowAndroid);
        if (supplier == null) return null;

        final TabModelSelector selector = supplier.get();
        if (selector == null) return null;

        return selector.getTabGroupModelFilterProvider().getTabGroupModelFilter(tab.isIncognito());
    }

    /** Converts a {@link TabList} to a {@link List<Tab>}. */
    public static @NonNull List<Tab> convertTabListToListOfTabs(@Nullable TabList tabList) {
        ArrayList<Tab> list = new ArrayList<>();
        if (tabList == null) return list;

        for (int i = 0; i < tabList.getCount(); i++) {
            list.add(tabList.getTabAt(i));
        }
        return list;
    }

    /** Returns the list of Tabs for the given Tab IDs. */
    public static List<Tab> getTabsById(
            Collection<Integer> tabIds, TabModel tabModel, boolean allowClosing) {
        return getTabsById(tabIds, tabModel, allowClosing, null);
    }

    /**
     * Returns the list of Tabs for the given Tab IDs. Invalid IDs are ignored.
     *
     * @param tabIds Tabs IDs to retrieve.
     * @param tabModel Tab model to get them from.
     * @param allowClosing Whether to include tabs when tab.isClosing() == true.
     * @param predicate An additional condition to filter by.
     */
    public static List<Tab> getTabsById(
            Collection<Integer> tabIds,
            TabModel tabModel,
            boolean allowClosing,
            @Nullable Predicate<Tab> predicate) {
        List<Tab> ret = new ArrayList<>(tabIds.size());
        for (Integer tabId : tabIds) {
            Tab tab = tabModel.getTabById(tabId);
            if (tab != null
                    && (allowClosing || !tab.isClosing())
                    && (predicate == null || predicate.test(tab))) {
                ret.add(tab);
            }
        }
        return ret;
=======
        return childTabs;
>>>>>>> chromium
    }

    /** Returns the list of Tab IDs for the given Tabs. */
    public static List<Integer> getTabIds(Collection<Tab> tabs) {
        List<Integer> ret = new ArrayList<>(tabs.size());
        for (Tab tab : tabs) {
            ret.add(tab.getId());
        }
        return ret;
    }
}
