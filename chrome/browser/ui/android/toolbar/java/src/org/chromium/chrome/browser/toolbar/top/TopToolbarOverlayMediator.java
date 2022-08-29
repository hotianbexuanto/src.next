// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.toolbar.top;

import android.content.Context;

import androidx.annotation.ColorInt;
import androidx.annotation.VisibleForTesting;

import org.chromium.base.Callback;
import org.chromium.base.supplier.ObservableSupplier;
<<<<<<< HEAD
import org.chromium.cc.input.BrowserControlsOffsetTagsInfo;
import org.chromium.cc.input.BrowserControlsState;
=======
>>>>>>> chromium
import org.chromium.chrome.browser.browser_controls.BrowserControlsStateProvider;
import org.chromium.chrome.browser.browser_controls.BrowserControlsUtils;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.layouts.LayoutStateProvider;
import org.chromium.chrome.browser.layouts.LayoutStateProvider.LayoutStateObserver;
import org.chromium.chrome.browser.layouts.LayoutType;
import org.chromium.chrome.browser.tab.CurrentTabObserver;
import org.chromium.chrome.browser.tab.EmptyTabObserver;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.theme.ThemeUtils;
import org.chromium.chrome.browser.theme.TopUiThemeColorProvider;
import org.chromium.components.browser_ui.widget.ClipDrawableProgressBar;
import org.chromium.ui.base.DeviceFormFactor;
import org.chromium.ui.modelutil.PropertyModel;

/** The business logic for controlling the top toolbar's cc texture. */
public class TopToolbarOverlayMediator {
    // Forced testing params.
    private static Boolean sIsTabletForTesting;
    private static Integer sToolbarBackgroundColorForTesting;
    private static Integer sUrlBarColorForTesting;

    /** An Android Context. */
    private final Context mContext;

    /** A handle to the layout manager for observing scene changes. */
    private final LayoutStateProvider mLayoutStateProvider;

    /** The observer of changes to the active layout. */
    private final LayoutStateObserver mSceneChangeObserver;

    /** A means of populating draw info for the progress bar. */
    private final Callback<ClipDrawableProgressBar.DrawingInfo> mProgressInfoCallback;

    /** An observer that watches for changes in the active tab. */
    private final CurrentTabObserver mTabObserver;

    /** Access to the current state of the browser controls. */
    private final BrowserControlsStateProvider mBrowserControlsStateProvider;

    /** An observer of the browser controls offsets. */
    private final BrowserControlsStateProvider.Observer mBrowserControlsObserver;

    private final TopUiThemeColorProvider mTopUiThemeColorProvider;

    /** The view state for this overlay. */
    private final PropertyModel mModel;

<<<<<<< HEAD
    private final ObservableSupplier<Integer> mBottomToolbarControlsOffsetSupplier;

=======
>>>>>>> chromium
    /** Whether visibility is controlled internally or manually by the feature. */
    private boolean mIsVisibilityManuallyControlled;

    /** Whether the android view for this overlay is visible. */
    private boolean mIsAndroidViewVisible;

    /** Whether the overlay should be visible despite other signals. */
    private boolean mManualVisibility;

    /** Whether a layout that this overlay can be displayed on is showing. */
    private boolean mIsOnValidLayout;

    TopToolbarOverlayMediator(PropertyModel model, Context context,
            LayoutStateProvider layoutStateProvider,
            Callback<ClipDrawableProgressBar.DrawingInfo> progressInfoCallback,
            ObservableSupplier<Tab> tabSupplier,
            BrowserControlsStateProvider browserControlsStateProvider,
<<<<<<< HEAD
            TopUiThemeColorProvider topUiThemeColorProvider,
            ObservableSupplier<Integer> bottomToolbarControlsOffsetSupplier,
            int layoutsToShowOn,
=======
            TopUiThemeColorProvider topUiThemeColorProvider, int layoutsToShowOn,
>>>>>>> chromium
            boolean manualVisibilityControl) {
        mContext = context;
        mLayoutStateProvider = layoutStateProvider;
        mProgressInfoCallback = progressInfoCallback;
        mBrowserControlsStateProvider = browserControlsStateProvider;
        mTopUiThemeColorProvider = topUiThemeColorProvider;
        mModel = model;
<<<<<<< HEAD
        mBottomToolbarControlsOffsetSupplier = bottomToolbarControlsOffsetSupplier;
        mBottomToolbarControlsOffsetSupplier.addObserver((unused) -> updateContentOffset(false));
=======
>>>>>>> chromium
        mIsVisibilityManuallyControlled = manualVisibilityControl;

        mIsOnValidLayout = (mLayoutStateProvider.getActiveLayoutType() & layoutsToShowOn) > 0;
        updateVisibility();

        mSceneChangeObserver = new LayoutStateObserver() {
            @Override
            public void onStartedShowing(@LayoutType int layout, boolean showToolbar) {
                mIsOnValidLayout = (layout & layoutsToShowOn) > 0;
                updateVisibility();
            }
        };
        mLayoutStateProvider.addObserver(mSceneChangeObserver);

        // Keep an observer attached to the visible tab (and only the visible tab) to update
        // properties including theme color.
        Callback<Tab> activityTabCallback = (tab) -> {
            if (tab == null) return;
            updateVisibility();
            updateThemeColor(tab);
            updateProgress();
        };
        mTabObserver = new CurrentTabObserver(tabSupplier, new EmptyTabObserver() {
            @Override
            public void onDidChangeThemeColor(Tab tab, int color) {
                updateThemeColor(tab);
            }

            @Override
            public void onLoadProgressChanged(Tab tab, float progress) {
                updateProgress();
            }

            @Override
            public void onContentChanged(Tab tab) {
                updateVisibility();
                updateThemeColor(tab);
            }
        }, activityTabCallback);

        activityTabCallback.onResult(tabSupplier.get());
        mTabObserver.triggerWithCurrentTab();

<<<<<<< HEAD
        mBrowserControlsObserver =
                new BrowserControlsStateProvider.Observer() {
                    @Override
                    public void onControlsOffsetChanged(
                            int topOffset,
                            int topControlsMinHeightOffset,
                            boolean topControlsMinHeightChanged,
                            int bottomOffset,
                            int bottomControlsMinHeightOffset,
                            boolean bottomControlsMinHeightChanged,
                            boolean requestNewFrame,
                            boolean isVisibilityForced) {
                        if (!ChromeFeatureList.sBrowserControlsInViz.isEnabled()
                                || requestNewFrame
                                || isVisibilityForced
                                || topControlsMinHeightChanged) {
                            updateContentOffset(topControlsMinHeightChanged);
                        }
=======
        mBrowserControlsObserver = new BrowserControlsStateProvider.Observer() {
            @Override
            public void onControlsOffsetChanged(int topOffset, int topControlsMinHeightOffset,
                    int bottomOffset, int bottomControlsMinHeightOffset, boolean needsAnimate) {
                // The toolbar layer is positioned below the minimum height (i.e. the top of the
                // toolbar layer is set to the bottom of minimum height). Hence, the offset
                // consists of the top controls offset plus top controls minimum height.
                int yOffset = topOffset + mBrowserControlsStateProvider.getTopControlsMinHeight();
                mModel.set(TopToolbarOverlayProperties.Y_OFFSET, yOffset);
>>>>>>> chromium

                updateShadowState();
                updateVisibility();
            }

            @Override
            public void onAndroidVisibilityChanged(int visibility) {
                // TODO(crbug/1223069): Remove this workaround for default method desugaring in D8
                // causing AbstractMethodErrors in some cases once fixed upstream.
            }
        };
        mBrowserControlsStateProvider.addObserver(mBrowserControlsObserver);
    }

    /**
     * Set whether the android view corresponding with this overlay is showing.
     * @param isVisible Whether the android view is visible.
     */
    void setIsAndroidViewVisible(boolean isVisible) {
        mIsAndroidViewVisible = isVisible;
        updateShadowState();
    }

    /**
     * Compute whether the texture's shadow should be visible. The shadow is visible whenever the
     * android view is not shown.
     */
    private void updateShadowState() {
        boolean drawControlsAsTexture =
                BrowserControlsUtils.drawControlsAsTexture(mBrowserControlsStateProvider);
        boolean showShadow = drawControlsAsTexture || !mIsAndroidViewVisible
                || mIsVisibilityManuallyControlled;
        mModel.set(TopToolbarOverlayProperties.SHOW_SHADOW, showShadow);
    }

    /**
     * Update the colors of the layer based on the specified tab.
     * @param tab The tab to base the colors on.
     */
    private void updateThemeColor(Tab tab) {
        @ColorInt
        int color = getToolbarBackgroundColor(tab);
        mModel.set(TopToolbarOverlayProperties.TOOLBAR_BACKGROUND_COLOR, color);
        mModel.set(TopToolbarOverlayProperties.URL_BAR_COLOR, getUrlBarBackgroundColor(tab, color));
    }

    /**
     * @param tab The tab to get the background color for.
     * @return The background color.
     */
    @ColorInt
    private int getToolbarBackgroundColor(Tab tab) {
        if (sToolbarBackgroundColorForTesting != null) return sToolbarBackgroundColorForTesting;
        return mTopUiThemeColorProvider.getSceneLayerBackground(tab);
    }

    /**
     * @param tab The tab to get the background color for.
     * @param backgroundColor The tab's background color.
     * @return The url bar color.
     */
    @ColorInt
    private int getUrlBarBackgroundColor(Tab tab, @ColorInt int backgroundColor) {
        if (sUrlBarColorForTesting != null) return sUrlBarColorForTesting;
        return ThemeUtils.getTextBoxColorForToolbarBackground(
                mContext.getResources(), tab, backgroundColor);
    }

    /** Update the state of the composited progress bar. */
    private void updateProgress() {
        // Tablets have their own version of a progress "spinner".
        if (isTablet()) return;

        if (mModel.get(TopToolbarOverlayProperties.PROGRESS_BAR_INFO) == null) {
            mModel.set(TopToolbarOverlayProperties.PROGRESS_BAR_INFO,
                    new ClipDrawableProgressBar.DrawingInfo());
        }

        // Update and set the progress info to trigger an update; the PROGRESS_BAR_INFO
        // property skips the object equality check.
        mProgressInfoCallback.onResult(mModel.get(TopToolbarOverlayProperties.PROGRESS_BAR_INFO));
        if (!ChromeFeatureList.isEnabled(ChromeFeatureList.DISABLE_COMPOSITED_PROGRESS_BAR)) {
            mModel.set(TopToolbarOverlayProperties.PROGRESS_BAR_INFO,
                    mModel.get(TopToolbarOverlayProperties.PROGRESS_BAR_INFO));
        }
    }

    /** @return Whether this component is in tablet mode. */
    private boolean isTablet() {
        if (sIsTabletForTesting != null) return sIsTabletForTesting;
        return DeviceFormFactor.isNonMultiDisplayContextOnTablet(mContext);
    }

    /** Clean up any state and observers. */
    void destroy() {
        mTabObserver.destroy();

        mLayoutStateProvider.removeObserver(mSceneChangeObserver);
        mBrowserControlsStateProvider.removeObserver(mBrowserControlsObserver);
    }

    /** Update the visibility of the overlay. */
    private void updateVisibility() {
        if (mIsVisibilityManuallyControlled) {
            mModel.set(TopToolbarOverlayProperties.VISIBLE, mManualVisibility && mIsOnValidLayout);
        } else {
            mModel.set(TopToolbarOverlayProperties.VISIBLE,
                    !BrowserControlsUtils.areBrowserControlsOffScreen(mBrowserControlsStateProvider)
                            && mIsOnValidLayout);
        }
    }

    /** @return Whether this overlay should be attached to the tree. */
    boolean shouldBeAttachedToTree() {
        return true;
    }

    /** @param xOffset The x offset of the toolbar. */
    void setXOffset(float xOffset) {
        mModel.set(TopToolbarOverlayProperties.X_OFFSET, xOffset);
    }

    /** @param anonymize Whether the URL should be hidden when the layer is rendered. */
    void setAnonymize(boolean anonymize) {
        mModel.set(TopToolbarOverlayProperties.ANONYMIZE, anonymize);
    }

    /** @param visible Whether the overlay and shadow should be visible despite other signals. */
    void setManualVisibility(boolean visible) {
        assert mIsVisibilityManuallyControlled
                : "Manual visibility control was not set for this overlay.";
        mManualVisibility = visible;
        updateShadowState();
        updateVisibility();
    }

    @VisibleForTesting
    void setVisibilityManuallyControlledForTesting(boolean manuallyControlled) {
        mIsVisibilityManuallyControlled = manuallyControlled;
        updateShadowState();
        updateVisibility();
    }

<<<<<<< HEAD
    void setViewportHeight(float viewportHeight) {
        if (viewportHeight == mViewportHeight) return;
        mViewportHeight = viewportHeight;
        updateContentOffset(false);
    }

    private void updateContentOffset(boolean minHeightChanged) {
        // When top-anchored, the content offset is used to position the toolbar
        // layer instead of the top controls offset because the top controls can
        // have a different height than that of just the toolbar, (e.g. when status
        // indicator is visible or tab strip is hidden), and the toolbar should be
        // positioned at the bottom of the top controls regardless of the overall
        // height.
        // When the toolbar is bottom-anchored, the situation is even more ambiguous
        // because the bottom-anchored toolbar can't be assumed to sit at the top or
        // bottom of the bottom controls stack. Instead, we rely on an offset
        // provided to us indirectly via BottomControlsStacker, which controls the
        // position of bottom controls layers.
        int contentOffset = mBrowserControlsStateProvider.getContentOffset();
        if (ChromeFeatureList.sBrowserControlsInViz.isEnabled() && minHeightChanged) {
            // We only want to use the height, any scroll offsets will be applied by viz.
            contentOffset = mBrowserControlsStateProvider.getTopControlsCurrentHeight();
        }

        if (mBrowserControlsStateProvider.getControlsPosition() == ControlsPosition.BOTTOM) {
            contentOffset = (int) (mBottomToolbarControlsOffsetSupplier.get() + mViewportHeight);
        }

        mModel.set(TopToolbarOverlayProperties.CONTENT_OFFSET, contentOffset);
    }

=======
    @VisibleForTesting
>>>>>>> chromium
    static void setIsTabletForTesting(Boolean isTablet) {
        sIsTabletForTesting = isTablet;
    }

    @VisibleForTesting
    static void setToolbarBackgroundColorForTesting(@ColorInt int color) {
        sToolbarBackgroundColorForTesting = color;
    }

    @VisibleForTesting
    static void setUrlBarColorForTesting(@ColorInt int color) {
        sUrlBarColorForTesting = color;
    }
}
