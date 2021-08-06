// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.omnibox.suggestions;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.Rect;
import android.graphics.drawable.ColorDrawable;
<<<<<<< HEAD
import android.os.Handler;
import android.os.Looper;
import android.util.AttributeSet;
=======
import android.os.Build;
>>>>>>> chromium
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
<<<<<<< HEAD
import android.view.ViewOutlineProvider;
import android.view.accessibility.AccessibilityEvent;
=======
import android.view.ViewParent;
import android.view.ViewTreeObserver.OnGlobalLayoutListener;
import android.view.WindowInsets;
>>>>>>> chromium

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.Px;
import androidx.core.view.ViewCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

<<<<<<< HEAD
import org.chromium.base.Callback;
import org.chromium.base.TimeUtils;
=======
>>>>>>> chromium
import org.chromium.base.TraceEvent;
import org.chromium.base.metrics.TimingMetric;
import org.chromium.base.task.PostTask;
import org.chromium.chrome.browser.omnibox.R;
import org.chromium.chrome.browser.util.KeyNavigationUtil;
import org.chromium.components.browser_ui.styles.ChromeColors;
import org.chromium.content_public.browser.UiThreadTaskTraits;
import org.chromium.ui.base.ViewUtils;

/** A widget for showing a list of omnibox suggestions. */
public class OmniboxSuggestionsDropdown extends RecyclerView {
<<<<<<< HEAD
    /** Used to tag and cancel the Accessibility focus events. */
    private static final Object TOKEN_ACCESSIBILITY_FOCUS = new Object();

    /**
     * Used to defer the accessibility announcement for list content. This makes core difference
     * when the list is first shown up, when the interaction with the Omnibox and presence of
     * virtual keyboard may actually cause throttling of the Accessibility events.
     *
     * <p>Note that this delay aims to strike a compromise between multiple directly competing
     * components for a11y time:
     *
     * <ul>
     *   <li>UrlBar: "facebook.com",
     *   <li>Soft Keyboard: "f. foxtrot. showing us english q w e r t y", and
     *   <li>Omnibox Suggestions: "15 suggested items in list below".
     * </ul>
     *
     * The Suggestions list can be announced after a slight pause, as it's best that it's announced
     * last.
     */
    private static final long LIST_COMPOSITION_ACCESSIBILITY_ANNOUNCEMENT_DELAY_MS = 1500;

    private final SuggestionLayoutScrollListener mLayoutScrollListener;
    private final RecyclerViewSelectionController mSelectionController;
    private final Handler mHandler;
=======
    private final int mStandardBgColor;
    private final int mIncognitoBgColor;

    private final int[] mTempPosition = new int[2];
    private final Rect mTempRect = new Rect();
>>>>>>> chromium

    private final SuggestionScrollListener mScrollListener;
    private @Nullable OmniboxSuggestionsDropdownAdapter mAdapter;
    private @Nullable OmniboxSuggestionsDropdownEmbedder mEmbedder;
    private @Nullable OmniboxSuggestionsDropdown.Observer mObserver;
    private @Nullable View mAnchorView;
    private @Nullable View mAlignmentView;
    private @Nullable OnGlobalLayoutListener mAnchorViewLayoutListener;
    private @Nullable View.OnLayoutChangeListener mAlignmentViewLayoutListener;

    private int mListViewMaxHeight;
    private int mLastBroadcastedListViewMaxHeight;

    /** Interface that will receive notifications and callbacks from OmniboxSuggestionsDropdown. */
    public interface Observer {
        /**
         * Invoked whenever the height of suggestion list changes.
         * The height may change as a result of eg. soft keyboard popping up.
         *
         * @param newHeightPx New height of the suggestion list in pixels.
         */
        void onSuggestionDropdownHeightChanged(@Px int newHeightPx);

        /**
         * Invoked whenever the User scrolls the list.
         */
        void onSuggestionDropdownScroll();

        /**
         * Invoked whenever the User scrolls the list to the top.
         */
        void onSuggestionDropdownOverscrolledToTop();

        /**
         * Notify that the user is interacting with an item on the Suggestions list.
         *
         * @param isGestureUp Whether user pressed (false) or depressed (true) the element on the
         *         list.
         * @param timestamp The timestamp associated with the event.
         */
        void onGesture(boolean isGestureUp, long timestamp);
    }

    /** Scroll listener that propagates scroll event notification to registered observers. */
    private class SuggestionScrollListener extends RecyclerView.OnScrollListener {
        @Override
        public void onScrolled(RecyclerView view, int dx, int dy) {}

        @Override
        public void onScrollStateChanged(RecyclerView view, int scrollState) {
            if (scrollState == SCROLL_STATE_DRAGGING && mObserver != null) {
                mObserver.onSuggestionDropdownScroll();
            }
        }

        void onOverscrollToTop() {
            mObserver.onSuggestionDropdownOverscrolledToTop();
        }
    }

    /**
     * RecyclerView pool that records performance of the view recycling mechanism.
     * @see OmniboxSuggestionsListViewListAdapter#canReuseView(View, int)
     */
    private class HistogramRecordingRecycledViewPool extends RecycledViewPool {
        HistogramRecordingRecycledViewPool() {
            // The list below should include suggestions defined in OmniboxSuggestionUiType
            // and specify the maximum anticipated volume of suggestions of each type.
            // For readability reasons, keep the order of this list same as the order of
            // the types defined in OmniboxSuggestionUiType.
            setMaxRecycledViews(OmniboxSuggestionUiType.DEFAULT, 20);
            setMaxRecycledViews(OmniboxSuggestionUiType.EDIT_URL_SUGGESTION, 1);
            setMaxRecycledViews(OmniboxSuggestionUiType.ANSWER_SUGGESTION, 1);
            setMaxRecycledViews(OmniboxSuggestionUiType.ENTITY_SUGGESTION, 5);
            setMaxRecycledViews(OmniboxSuggestionUiType.TAIL_SUGGESTION, 15);
            setMaxRecycledViews(OmniboxSuggestionUiType.CLIPBOARD_SUGGESTION, 1);
            setMaxRecycledViews(OmniboxSuggestionUiType.HEADER, 4);
            setMaxRecycledViews(OmniboxSuggestionUiType.TILE_NAVSUGGEST, 1);
            setMaxRecycledViews(OmniboxSuggestionUiType.PEDAL_SUGGESTION, 3);
        }

        @Override
        public ViewHolder getRecycledView(int viewType) {
            ViewHolder result = super.getRecycledView(viewType);
            SuggestionsMetrics.recordSuggestionViewReused(result != null);
            if (result == null) {
                SuggestionsMetrics.recordSuggestionsViewCreatedType(viewType);
            } else {
                SuggestionsMetrics.recordSuggestionsViewReusedType(viewType);
            }
            return result;
        }
    }

    /**
     * Constructs a new list designed for containing omnibox suggestions.
     * @param context Context used for contained views.
     */
<<<<<<< HEAD
    public OmniboxSuggestionsDropdown(@NonNull Context context, AttributeSet attrs) {
        super(context, attrs, android.R.attr.dropDownListViewStyle);

        mHandler = new Handler(Looper.getMainLooper());

=======
    public OmniboxSuggestionsDropdown(@NonNull Context context) {
        super(context, null, android.R.attr.dropDownListViewStyle);
>>>>>>> chromium
        setFocusable(true);
        setFocusableInTouchMode(true);
        setRecycledViewPool(new HistogramRecordingRecycledViewPool());

        // By default RecyclerViews come with item animators.
        setItemAnimator(null);

        mScrollListener = new SuggestionScrollListener();
        setOnScrollListener(mScrollListener);
        setLayoutManager(new LinearLayoutManager(context) {
            @Override
            public int scrollVerticallyBy(
                    int deltaY, RecyclerView.Recycler recycler, RecyclerView.State state) {
                int scrollY = super.scrollVerticallyBy(deltaY, recycler, state);
                if (scrollY == 0 && deltaY < 0) {
                    mScrollListener.onOverscrollToTop();
                }
                return scrollY;
            }
        });

        final Resources resources = context.getResources();
        int paddingBottom =
                resources.getDimensionPixelOffset(R.dimen.omnibox_suggestion_list_padding_bottom);
        ViewCompat.setPaddingRelative(this, 0, 0, 0, paddingBottom);

        mStandardBgColor = ChromeColors.getDefaultThemeColor(resources, false);
        mIncognitoBgColor = ChromeColors.getDefaultThemeColor(resources, true);
    }

    /** Get the Android View implementing suggestion list. */
    public @NonNull ViewGroup getViewGroup() {
        return this;
    }

    /**
     * Sets the observer of suggestion list.
     * @param observer an observer of this list.
     */
    public void setObserver(@NonNull OmniboxSuggestionsDropdown.Observer observer) {
        mObserver = observer;
    }

    /** Resets selection typically in response to changes to the list. */
    public void resetSelection() {
        if (mAdapter == null) return;
        mAdapter.resetSelection();
    }

    /** @return The number of items in the list. */
    public int getDropdownItemViewCountForTest() {
        if (mAdapter == null) return 0;
        return mAdapter.getItemCount();
    }

    /** @return The Suggestion view at specific index. */
    public @Nullable View getDropdownItemViewForTest(int index) {
        final LayoutManager manager = getLayoutManager();
        manager.scrollToPosition(index);
        return manager.findViewByPosition(index);
    }

<<<<<<< HEAD
    /**
     * Update the suggestion popup background to reflect the current state.
     *
     * @param brandedColorScheme The {@link @BrandedColorScheme}.
     */
    public void refreshPopupBackground(@BrandedColorScheme int brandedColorScheme) {
        int color =
                OmniboxResourceProvider.getSuggestionsDropdownBackgroundColor(
                        getContext(), brandedColorScheme);
=======
    /** Show (and properly size) the suggestions list. */
    public void show() {
        if (getVisibility() == VISIBLE) return;
>>>>>>> chromium

        setVisibility(VISIBLE);
        if (mAdapter != null && mAdapter.getSelectedViewIndex() != 0) {
            mAdapter.resetSelection();
        }
    }

    /** Hide the suggestions list and release any cached resources. */
    public void hide() {
        if (getVisibility() != VISIBLE) return;
        setVisibility(GONE);
        getRecycledViewPool().clear();
    }

    /** Update the suggestion popup background to reflect the current state. */
    public void refreshPopupBackground(boolean isIncognito) {
        int color = isIncognito ? mIncognitoBgColor : mStandardBgColor;
        if (!isHardwareAccelerated()) {
            // When HW acceleration is disabled, changing mSuggestionList' items somehow erases
            // mOmniboxResultsContainer' background from the area not covered by
            // mSuggestionList. To make sure mOmniboxResultsContainer is always redrawn, we make
            // list background color slightly transparent. This makes mSuggestionList.isOpaque()
            // to return false, and forces redraw of the parent view (mOmniboxResultsContainer).
            if (Color.alpha(color) == 255) {
                color = Color.argb(254, Color.red(color), Color.green(color), Color.blue(color));
            }
        }
        setBackground(new ColorDrawable(color));
    }

    @Override
    public void setAdapter(@NonNull Adapter adapter) {
        mAdapter = (OmniboxSuggestionsDropdownAdapter) adapter;
        super.setAdapter(mAdapter);
    }

    @Override
    public void onAttachedToWindow() {
        super.onAttachedToWindow();
        mAnchorView.getViewTreeObserver().addOnGlobalLayoutListener(mAnchorViewLayoutListener);
        if (mAlignmentView != null) {
            adjustSidePadding();
            mAlignmentView.addOnLayoutChangeListener(mAlignmentViewLayoutListener);
        }
    }

    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        getRecycledViewPool().clear();
        mAnchorView.getViewTreeObserver().removeOnGlobalLayoutListener(mAnchorViewLayoutListener);
        if (mAlignmentView != null) {
            mAlignmentView.removeOnLayoutChangeListener(mAlignmentViewLayoutListener);
        }
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        try (TraceEvent tracing = TraceEvent.scoped("OmniboxSuggestionsList.Measure");
                TimingMetric metric = SuggestionsMetrics.recordSuggestionListMeasureTime()) {
            int anchorBottomRelativeToContent = calculateAnchorBottomRelativeToContent();
            if (ContextUtils.getAppSharedPreferences().getBoolean("enable_bottom_toolbar", false))
              anchorBottomRelativeToContent = 0;
            maybeUpdateLayoutParams(anchorBottomRelativeToContent);

            int availableViewportHeight =
                    calculateAvailableViewportHeight(anchorBottomRelativeToContent);
            notifyObserversIfViewportHeightChanged(availableViewportHeight);

            int newWidthMeasureSpec = MeasureSpec.makeMeasureSpec(
                    mAnchorView.getMeasuredWidth(), MeasureSpec.EXACTLY);
            int newHeightMeasureSpec = MeasureSpec.makeMeasureSpec(availableViewportHeight,
                    mEmbedder.isTablet() ? MeasureSpec.AT_MOST : MeasureSpec.EXACTLY);
            super.onMeasure(newWidthMeasureSpec, newHeightMeasureSpec);
        }
    }

    private int calculateAnchorBottomRelativeToContent() {
        View contentView =
                mEmbedder.getAnchorView().getRootView().findViewById(android.R.id.content);
        ViewUtils.getRelativeLayoutPosition(contentView, mAnchorView, mTempPosition);
        int anchorY = mTempPosition[1];
        return anchorY + mAnchorView.getMeasuredHeight();
    }

    private void maybeUpdateLayoutParams(int topMargin) {
        // Update the layout params to ensure the parent correctly positions the suggestions
        // under the anchor view.
        ViewGroup.LayoutParams layoutParams = getLayoutParams();
        if (layoutParams != null && layoutParams instanceof ViewGroup.MarginLayoutParams) {
            ((ViewGroup.MarginLayoutParams) layoutParams).topMargin = topMargin;
        }
    }

    private int calculateAvailableViewportHeight(int anchorBottomRelativeToContent) {
        mEmbedder.getWindowDelegate().getWindowVisibleDisplayFrame(mTempRect);
        return mTempRect.height() - anchorBottomRelativeToContent;
    }

    private void notifyObserversIfViewportHeightChanged(int availableViewportHeight) {
        if (availableViewportHeight == mListViewMaxHeight) return;

        mListViewMaxHeight = availableViewportHeight;
        if (mObserver != null) {
            PostTask.postTask(UiThreadTaskTraits.DEFAULT, () -> {
                // Detect if there was another change since this task posted.
                // This indicates a subsequent task being posted too.
                if (mListViewMaxHeight != availableViewportHeight) return;
                // Detect if the new height is the same as previously broadcasted.
                // The two checks (one above and one below) allow us to detect quick
                // A->B->A transitions and suppress the broadcasts.
                if (mLastBroadcastedListViewMaxHeight == availableViewportHeight) return;
                if (mObserver == null) return;

                mObserver.onSuggestionDropdownHeightChanged(availableViewportHeight);
                mLastBroadcastedListViewMaxHeight = availableViewportHeight;
            });
        }
    }

    @Override
    protected void onLayout(boolean changed, int l, int t, int r, int b) {
        try (TraceEvent tracing = TraceEvent.scoped("OmniboxSuggestionsList.Layout");
                TimingMetric metric = SuggestionsMetrics.recordSuggestionListLayoutTime()) {
            super.onLayout(changed, l, t, r, b);
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (!isShown()) return false;

        View selectedView = mAdapter.getSelectedView();
        if (selectedView != null && selectedView.onKeyDown(keyCode, event)) {
            return true;
        }

        int selectedPosition = mAdapter.getSelectedViewIndex();
        if (KeyNavigationUtil.isGoDown(event)) {
            return mAdapter.setSelectedViewIndex(selectedPosition + 1);
        } else if (KeyNavigationUtil.isGoUp(event)) {
            return mAdapter.setSelectedViewIndex(selectedPosition - 1);
        } else if (KeyNavigationUtil.isEnter(event)) {
            if (selectedView != null) return selectedView.performClick();
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onGenericMotionEvent(MotionEvent event) {
        // Consume mouse events to ensure clicks do not bleed through to sibling views that
        // are obscured by the list.  crbug.com/968414
        int action = event.getActionMasked();
        boolean shouldIgnoreGenericMotionEvent =
                (event.getSource() & InputDevice.SOURCE_CLASS_POINTER) != 0
                && event.getToolType(0) == MotionEvent.TOOL_TYPE_MOUSE
                && (action == MotionEvent.ACTION_BUTTON_PRESS
                        || action == MotionEvent.ACTION_BUTTON_RELEASE);
        return shouldIgnoreGenericMotionEvent || super.onGenericMotionEvent(event);
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        final int eventType = ev.getActionMasked();
        if ((eventType == MotionEvent.ACTION_UP || eventType == MotionEvent.ACTION_DOWN)
                && mObserver != null) {
            mObserver.onGesture(eventType == MotionEvent.ACTION_UP, ev.getEventTime());
        }
        return super.dispatchTouchEvent(ev);
    }

    /**
     * Sets the embedder for the list view.
     * @param embedder the embedder of this list.
     */
    public void setEmbedder(@NonNull OmniboxSuggestionsDropdownEmbedder embedder) {
        assert mEmbedder == null;
        mEmbedder = embedder;
        mAnchorView = mEmbedder.getAnchorView();
        // Prior to Android M, the contextual actions associated with the omnibox were anchored
        // to the top of the screen and not a floating copy/paste menu like on newer versions.
        // As a result of this, the toolbar is pushed down in these Android versions and we need
        // to montior those changes to update the positioning of the list.
        mAnchorViewLayoutListener = new OnGlobalLayoutListener() {
            private int mOffsetInWindow;
            private WindowInsets mWindowInsets;
            private final Rect mWindowRect = new Rect();

            @Override
            public void onGlobalLayout() {
                if (offsetInWindowChanged() || insetsHaveChanged()) {
                    requestLayout();
                }
            }

            private boolean offsetInWindowChanged() {
                int offsetInWindow = 0;
                View currentView = mAnchorView;
                while (true) {
                    offsetInWindow += currentView.getTop();
                    ViewParent parent = currentView.getParent();
                    if (parent == null || !(parent instanceof View)) break;
                    currentView = (View) parent;
                }
                boolean result = mOffsetInWindow != offsetInWindow;
                mOffsetInWindow = offsetInWindow;
                return result;
            }

            private boolean insetsHaveChanged() {
                boolean result = false;
                WindowInsets currentInsets = null;
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                    currentInsets = mAnchorView.getRootWindowInsets();
                    result = !currentInsets.equals(mWindowInsets);
                    mWindowInsets = currentInsets;
                } else {
                    mEmbedder.getWindowDelegate().getWindowVisibleDisplayFrame(mTempRect);
                    result = !mTempRect.equals(mWindowRect);
                    mWindowRect.set(mTempRect);
                }
                return result;
            }
        };

        mAlignmentView = mEmbedder.getAlignmentView();
        if (mAlignmentView != null) {
            mAlignmentViewLayoutListener = new View.OnLayoutChangeListener() {
                @Override
                public void onLayoutChange(View v, int left, int top, int right, int bottom,
                        int oldLeft, int oldTop, int oldRight, int oldBottom) {
                    adjustSidePadding();
                }
            };
        } else {
<<<<<<< HEAD
            cancelWindowContentChangedAnnouncement();
            removeAlignmentObserver();
=======
            mAlignmentViewLayoutListener = null;
>>>>>>> chromium
        }
    }

    public void emitWindowContentChanged() {
        PostTask.postDelayedTask(UiThreadTaskTraits.DEFAULT, () -> {
            announceForAccessibility(getContext().getString(
                    R.string.accessibility_omnibox_suggested_items, mAdapter.getItemCount()));
        }, LIST_COMPOSITION_ACCESSIBILITY_ANNOUNCEMENT_DELAY_MS);
    }

    private void adjustSidePadding() {
        if (mAlignmentView == null) return;

        ViewUtils.getRelativeLayoutPosition(mAnchorView, mAlignmentView, mTempPosition);
        setPadding(mTempPosition[0], getPaddingTop(),
                mAnchorView.getWidth() - mAlignmentView.getWidth() - mTempPosition[0],
                getPaddingBottom());
    }

<<<<<<< HEAD
    private void removeAlignmentObserver() {
        mEmbedder.ifPresent(
                e -> {
                    e.onDetachedFromWindow();
                    e.removeAlignmentObserver(mOmniboxAlignmentObserver);
                });

        if (!OmniboxFeatures.shouldPreWarmRecyclerViewPool()) {
            getRecycledViewPool().clear();
        }
    }

    private void onOmniboxAlignmentChanged(@NonNull OmniboxAlignment omniboxAlignment) {
        boolean isOnlyHorizontalDifference =
                omniboxAlignment.isOnlyHorizontalDifference(mOmniboxAlignment);
        boolean isWidthDifference = omniboxAlignment.doesWidthDiffer(mOmniboxAlignment);
        mOmniboxAlignment = omniboxAlignment;
        this.setPaddingRelative(
                getPaddingStart(),
                getPaddingTop(),
                getPaddingEnd(),
                mBaseBottomPadding + mOmniboxAlignment.paddingBottom);

        if (isOnlyHorizontalDifference) {
            adjustHorizontalPosition();
            return;
        } else if (isWidthDifference) {
            // If our width has changed, we may have views in our pool that are now the wrong width.
            // Recycle them by calling swapAdapter() to avoid showing views of the wrong size.
            swapAdapter(mAdapter, true);
            Configuration configuration = getContext().getResources().getConfiguration();
            setClipToOutline(
                    configuration.screenWidthDp >= DeviceFormFactor.MINIMUM_TABLET_WIDTH_DP);
            BaseSuggestionViewBinder.resetCachedResources();
        }
        if (isInLayout()) {
            // requestLayout doesn't behave predictably in the middle of a layout pass. Even if it
            // does trigger a second layout pass, measurement caches aren't properly reset,
            // resulting in stale sizing. Absent a way to abort the current pass and start over the
            // simplest solution is to wait until the current pass is over to request relayout.
            PostTask.postTask(
                    TaskTraits.UI_USER_VISIBLE,
                    () -> {
                        ViewUtils.requestLayout(
                                OmniboxSuggestionsDropdown.this,
                                "OmniboxSuggestionsDropdown.onOmniboxAlignmentChanged");
                    });
        } else {
            ViewUtils.requestLayout(
                    (View) OmniboxSuggestionsDropdown.this,
                    "OmniboxSuggestionsDropdown.onOmniboxAlignmentChanged");
        }
    }

    private void adjustHorizontalPosition() {
        // Set our left edge using translation x. This avoids needing to relayout (like setting
        // a left margin would) and is less risky than calling View#setLeft(), which is intended
        // for use by the layout system.
        setTranslationX(mOmniboxAlignment.left);
    }

    private void setRoundBottomCorners(boolean roundBottomCorners) {
        ViewOutlineProvider outlineProvider = getOutlineProvider();
        if (!(outlineProvider instanceof RoundedCornerOutlineProvider)) return;

        RoundedCornerOutlineProvider roundedCornerOutlineProvider =
                (RoundedCornerOutlineProvider) outlineProvider;
        roundedCornerOutlineProvider.setRoundingEdges(true, true, true, roundBottomCorners);
    }

    public void emitWindowContentChangedAnnouncement() {
        cancelWindowContentChangedAnnouncement();
        // Note: can't use postDelayed until minSdk is 28.
        mHandler.postAtTime(
                () -> {
                    setAccessibilityLiveRegion(ACCESSIBILITY_LIVE_REGION_POLITE);
                    setContentDescription(
                            getContext()
                                    .getString(
                                            R.string.accessibility_omnibox_suggested_items,
                                            mAdapter.getItemCount()));
                    sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUSED);
                    setAccessibilityLiveRegion(ACCESSIBILITY_LIVE_REGION_NONE);
                },
                TOKEN_ACCESSIBILITY_FOCUS,
                TimeUtils.uptimeMillis() + LIST_COMPOSITION_ACCESSIBILITY_ANNOUNCEMENT_DELAY_MS);
    }

    private void cancelWindowContentChangedAnnouncement() {
        mHandler.removeCallbacksAndMessages(TOKEN_ACCESSIBILITY_FOCUS);
    }

    @VisibleForTesting
    SuggestionLayoutScrollListener getLayoutScrollListener() {
        return mLayoutScrollListener;
=======
    /** Return whether Adaptive Suggestions Count feature is enabled. */
    private boolean isAdaptiveSuggestionsCountEnabled() {
        return ChromeFeatureList.isInitialized()
                && ChromeFeatureList.isEnabled(
                        ChromeFeatureList.OMNIBOX_ADAPTIVE_SUGGESTIONS_COUNT);
>>>>>>> chromium
    }
}
