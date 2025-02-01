// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tabmodel;

import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabCreationState;
import org.chromium.chrome.browser.tab.TabLaunchType;
import org.chromium.chrome.browser.tab.TabSelectionType;

import java.util.List;

/**
 * An interface to be notified about changes to a TabModel.
 */
public interface TabModelObserver {
    /**
     * Called when a tab is selected.
     *
     * @param tab The newly selected tab.
     * @param type The type of selection.
     * @param lastId The ID of the last selected tab, or {@link Tab#INVALID_TAB_ID} if no tab was
     * selected.
     */
    default void didSelectTab(Tab tab, @TabSelectionType int type, int lastId) {}

    /**
     * Called when a tab starts closing.
     *
     * @param tab The tab to close.
     * @param animate Whether or not to animate the closing.
     */
    default void willCloseTab(Tab tab, boolean animate) {}

    /**
     * Called right after {@code tab} has been destroyed.
     *
     * @param tabId The ID of the tab that was destroyed.
     * @param incognito True if the closed tab was incognito.
     *
     * @deprecated Use {@link #didCloseTab(Tab)} instead
     */
    @Deprecated
    default void didCloseTab(int tabId, boolean incognito) {}

    /**
     * Called right after {@code tab} has been destroyed.
     *
     * @param tab The tab that was closed.
     */
    default void didCloseTab(Tab tab) {}

    /**
     * Called before a tab will be added to the {@link TabModel}.
     *
     * @param tab The tab about to be added.
     * @param type The type of tab launch.
     */
    default void willAddTab(Tab tab, @TabLaunchType int type) {}

    /**
     * Called after a tab has been added to the {@link TabModel}.
     *
     * @param tab The newly added tab.
     * @param type The type of tab launch.
     * @param creationState How the tab was created.
     */
    default void didAddTab(Tab tab, @TabLaunchType int type, @TabCreationState int creationState) {}

    /**
     * Called after a tab has been moved from one position in the {@link TabModel} to another.
     *
     * @param tab The tab which has been moved.
     * @param newIndex The new index of the tab in the model.
     * @param curIndex The old index of the tab in the model.
     */
    default void didMoveTab(Tab tab, int newIndex, int curIndex) {}

    /**
     * Called when a tab is pending closure, i.e. the user has just closed it, but it can still be
     * undone. At this point, the Tab has been removed from the TabModel and can only be accessed
     * via {@link TabModel#getComprehensiveModel()}.
     *
     * @param tab The tab that is pending closure.
     */
    default void tabPendingClosure(Tab tab) {}

    /**
     * Called when a tab closure is undone.
     *
     * @param tab The tab that has been reopened.
     */
    default void tabClosureUndone(Tab tab) {}

    /**
     * Called when a tab closure is committed and can't be undone anymore.
     *
     * @param tab The tab that has been closed.
     */
    default void tabClosureCommitted(Tab tab) {}

    /**
     * Called when multiple tabs are pending closure.
     *
     * @param tabs The tabs that are pending closure.
     * @param isAllTabs Whether |tabs| are all the tabs.
     */
    default void multipleTabsPendingClosure(List<Tab> tabs, boolean isAllTabs) {}

    /**
<<<<<<< HEAD
     * Called when a tab closure is undone.
     *
     * @param tab The tab that has been reopened.
     */
    default void tabClosureUndone(Tab tab) {}

    /**
     * Called after all tabs closed from a close all tabs action have been successfully restored by
     * an undo action.
     */
    default void allTabsClosureUndone() {}

    /**
     * Called when a tab closure is committed and can't be undone anymore.
     *
     * @param tab The tab that has been closed.
     */
    default void tabClosureCommitted(Tab tab) {}

    /**
     * Called when an "all tabs" closure will happen. If multiple tabs are closed, @{@link
     * TabModelObserver#willCloseMultipleTabs(boolean, List)} is invoked
=======
     * Called when an "all tabs" closure will happen.
>>>>>>> chromium
     */
    default void willCloseAllTabs(boolean incognito) {}

    /**
<<<<<<< HEAD
     * Called when multiple tabs closure will happen. If "all tabs" are closed at once, @{@link
     * TabModelObserver#willCloseAllTabs(boolean)} is invoked.
     *
     * @param allowUndo If undo is allowed on the tab closure.
     * @param tabs being closed.
=======
     * Called when an "all tabs" closure has been committed and can't be undone anymore.
>>>>>>> chromium
     */
    default void allTabsClosureCommitted() {}

    /**
     * Called after a tab has been removed. At this point, the tab is no longer in the tab model.
     *
     * @param tab The tab that has been removed.
     */
    default void tabRemoved(Tab tab) {}

    /**
     * Called after all {@link org.chromium.chrome.browser.tab.TabState}s within {@link TabModel}
     * are loaded from storage.
     */
    default void restoreCompleted() {}

    //  TODO(crbug.com/381471263): The following methods are still in development and will
    //  replace the existing tab closure events in the near future. Methods being replaced are
    //  tabPendingClosure, multipleTabsPendingClosure, tabClosureUndone,
    //  allTabsClosureUndone, tabClosureCommitted, willCloseAllTabs,
    //  willCloseMultipleTabs and allTabsClosureCommitted.
    /**
     * Called right before {@code tabs} will be destroyed.
     *
     * @param tabs The list of {@link Tab}s that will be closed.
     * @param isAllTabs Whether tabs are all the tabs.
     */
    default void onTabCloseImmediate(List<Tab> tabs, boolean isAllTabs) {}

    /**
     * Called right before when tabs are pending closure, i.e. the user has just closed them, but it
     * can still be undone.
     *
     * @param tabs The list of {@link Tab}s that are pending closure.
     * @param isAllTabs Whether tabs are all the tabs.
     */
    default void onTabClosePending(List<Tab> tabs, boolean isAllTabs) {}

    /**
     * Called right before {@code tabs} closure is committed permanently and cannot be undone.
     *
     * @param tabs The list of {@link Tab}s that are closed.
     * @param isAllTabs Whether tabs are all the tabs.
     */
    default void onTabCloseCommitted(List<Tab> tabs, boolean isAllTabs) {}

    /**
     * Called just before {@code tabs} closed have been successfully restored by an undo action.
     *
     * @param tabs The list of {@link Tab}s that has been reopened.
     * @param isAllTabs Whether tabs are all the tabs.
     */
    default void onTabCloseUndone(List<Tab> tabs, boolean isAllTabs) {}
}
