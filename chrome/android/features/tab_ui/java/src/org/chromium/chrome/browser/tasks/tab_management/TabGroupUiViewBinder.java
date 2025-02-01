// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tasks.tab_management;

import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.INITIAL_SCROLL_INDEX;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.IS_MAIN_CONTENT_VISIBLE;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.LEFT_BUTTON_CONTENT_DESCRIPTION;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.LEFT_BUTTON_DRAWABLE_ID;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.LEFT_BUTTON_ON_CLICK_LISTENER;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.PRIMARY_COLOR;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.RIGHT_BUTTON_CONTENT_DESCRIPTION;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.RIGHT_BUTTON_ON_CLICK_LISTENER;
import static org.chromium.chrome.browser.tasks.tab_management.TabGroupUiProperties.TINT;

import android.view.View;

import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import org.chromium.ui.modelutil.PropertyKey;
import org.chromium.ui.modelutil.PropertyModel;

/**
 * ViewBinder for TabGroupUi component.
 */
class TabGroupUiViewBinder {
    /**
     * ViewHolder class to get access to all {@link View}s inside the TabGroupUi.
     */
    public static class ViewHolder {
        public final TabGroupUiToolbarView toolbarView;
        public final RecyclerView contentView;

        ViewHolder(TabGroupUiToolbarView toolbarView, RecyclerView contentView) {
            this.toolbarView = toolbarView;
            this.contentView = contentView;
        }
    }
    /**
     * Binds the given model to the given view, updating the payload in propertyKey.
     *
     * @param model             The model to use.
     * @param viewHolder        The {@link ViewHolder} to use.
     * @param propertyKey       The key for the property to update for.
     */
    public static void bind(PropertyModel model, ViewHolder viewHolder, PropertyKey propertyKey) {
        if (LEFT_BUTTON_ON_CLICK_LISTENER == propertyKey) {
            viewHolder.toolbarView.setLeftButtonOnClickListener(
                    model.get(LEFT_BUTTON_ON_CLICK_LISTENER));
        } else if (RIGHT_BUTTON_ON_CLICK_LISTENER == propertyKey) {
            viewHolder.toolbarView.setRightButtonOnClickListener(
                    model.get(RIGHT_BUTTON_ON_CLICK_LISTENER));
        } else if (IS_MAIN_CONTENT_VISIBLE == propertyKey) {
            viewHolder.toolbarView.setMainContentVisibility(model.get(IS_MAIN_CONTENT_VISIBLE));
        } else if (PRIMARY_COLOR == propertyKey) {
            viewHolder.toolbarView.setPrimaryColor(model.get(PRIMARY_COLOR));
        } else if (TINT == propertyKey) {
            viewHolder.toolbarView.setTint(model.get(TINT));
        } else if (LEFT_BUTTON_DRAWABLE_ID == propertyKey) {
            viewHolder.toolbarView.setLeftButtonDrawableId(model.get(LEFT_BUTTON_DRAWABLE_ID));
        } else if (INITIAL_SCROLL_INDEX == propertyKey) {
<<<<<<< HEAD
            scrollToIndex(viewHolder, model);
        } else if (TINT == propertyKey) {
            viewHolder.toolbarView.setTint(model.get(TINT));
=======
            int index = (Integer) model.get(INITIAL_SCROLL_INDEX);
            LinearLayoutManager manager =
                    (LinearLayoutManager) viewHolder.contentView.getLayoutManager();
            int showingItemsCount =
                    manager.findLastVisibleItemPosition() - manager.findFirstVisibleItemPosition();
            // Try to scroll to a state where the selected tab is in the middle of the strip.
            manager.scrollToPositionWithOffset(index - showingItemsCount / 2, 0);
        } else if (LEFT_BUTTON_CONTENT_DESCRIPTION == propertyKey) {
            viewHolder.toolbarView.setLeftButtonContentDescription(
                    model.get(LEFT_BUTTON_CONTENT_DESCRIPTION));
        } else if (RIGHT_BUTTON_CONTENT_DESCRIPTION == propertyKey) {
            viewHolder.toolbarView.setRightButtonContentDescription(
                    model.get(RIGHT_BUTTON_CONTENT_DESCRIPTION));
>>>>>>> chromium
        }
    }

    private static void scrollToIndex(ViewHolder viewHolder, PropertyModel model) {
        // This is a speculative fix for https://crbug.com/40948489. A crash is happening due to a
        // temporarily detached view to TabListRecyclerView not being removed from the RecyclerView
        // before it is recycled. This typically happens when an animating view gets recycled. While
        // this is arguably a bug with the recycler view itself, a common cause of this issue is a
        // programmatic scroll happening when the the RecyclerView is animating. The structure of
        // the runnable below should avoid this happening by skipping the scroll logic until after
        // the the view is done animating and is laid out.
        RecyclerView contentView = viewHolder.contentView;
        Runnable scrollRunnable =
                new Runnable() {
                    @Override
                    public void run() {
                        // Retry if animating or layout is incomplete.
                        if (contentView.isAnimating()
                                || contentView.getWidth() == 0
                                || contentView.getHeight() == 0) {
                            contentView.post(this);
                            return;
                        }
                        int index = model.get(INITIAL_SCROLL_INDEX);
                        LinearLayoutManager manager =
                                (LinearLayoutManager) contentView.getLayoutManager();
                        int showingItemsCount =
                                manager.findLastVisibleItemPosition()
                                        - manager.findFirstVisibleItemPosition();
                        // Try to scroll to a state where the selected tab is in the middle of the
                        // strip.
                        manager.scrollToPositionWithOffset(index - showingItemsCount / 2, 0);
                    }
                };
        scrollRunnable.run();
    }
}
