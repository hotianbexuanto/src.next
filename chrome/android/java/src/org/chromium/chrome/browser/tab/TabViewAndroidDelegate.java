// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tab;

import android.view.ViewGroup;

import androidx.annotation.Nullable;

import org.chromium.base.Callback;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.content_public.browser.RenderWidgetHostView;
import org.chromium.ui.base.ViewAndroidDelegate;
import org.chromium.ui.base.WindowAndroid;

/**
 * Implementation of the abstract class {@link ViewAndroidDelegate} for Chrome.
 */
public class TabViewAndroidDelegate extends ViewAndroidDelegate {
    private final TabImpl mTab;

    /**
     * The inset for the bottom of the Visual Viewport in pixels, or 0 for no insetting.
     * This is the source of truth for the application viewport inset for this embedder.
     */
    private int mApplicationViewportInsetBottomPx;

    /** The inset supplier the observer is currently attached to. */
    private ObservableSupplier<Integer> mCurrentInsetSupplier;

<<<<<<< HEAD
    private final Callback<ViewportInsets> mInsetObserver =
            (unused) -> updateVisualViewportBottomInset();

    TabViewAndroidDelegate(Tab tab, ContentView containerView) {
=======
    TabViewAndroidDelegate(Tab tab, ViewGroup containerView) {
>>>>>>> chromium
        super(containerView);
        mTab = (TabImpl) tab;

<<<<<<< HEAD
        if (ContentFeatureMap.isEnabled(ContentFeatures.TOUCH_DRAG_AND_CONTEXT_MENU)) {
            mDragAndDropBrowserDelegate =
                    new ChromeDragAndDropBrowserDelegate(
                            () -> {
                                if (mTab == null || mTab.getWindowAndroid() == null) return null;
                                return mTab.getWindowAndroid().getActivity().get();
                            });
            getDragAndDropDelegate().setDragAndDropBrowserDelegate(mDragAndDropBrowserDelegate);
        }

        mCurrentInsetSupplier = tab.getWindowAndroid().getApplicationBottomInsetSupplier();
        mCurrentInsetSupplier.addObserver(mInsetObserver);

        mTab.addObserver(
                new EmptyTabObserver() {
                    @Override
                    public void onActivityAttachmentChanged(
                            Tab tab, @Nullable WindowAndroid window) {
                        if (mCurrentInsetSupplier != null) {
                            mCurrentInsetSupplier.removeObserver(mInsetObserver);
                            mCurrentInsetSupplier = null;
                        }
                        if (window != null) {
                            mCurrentInsetSupplier =
                                    tab.getWindowAndroid().getApplicationBottomInsetSupplier();
                            mCurrentInsetSupplier.addObserver(mInsetObserver);
                        }
                        updateVisualViewportBottomInset();
                    }
=======
        Callback<Integer> insetObserver = (inset) -> updateInsetViewportBottom();
        mCurrentInsetSupplier = tab.getWindowAndroid().getApplicationBottomInsetProvider();
        mCurrentInsetSupplier.addObserver(insetObserver);

        mTab.addObserver(new EmptyTabObserver() {
            @Override
            public void onActivityAttachmentChanged(Tab tab, @Nullable WindowAndroid window) {
                if (window != null) {
                    mCurrentInsetSupplier =
                            tab.getWindowAndroid().getApplicationBottomInsetProvider();
                    mCurrentInsetSupplier.addObserver(insetObserver);
                } else {
                    mCurrentInsetSupplier.removeObserver(insetObserver);
                    mCurrentInsetSupplier = null;
                    updateInsetViewportBottom();
                }
            }
>>>>>>> chromium

            @Override
            public void onShown(Tab tab, int type) {
                updateInsetViewportBottom();
            }

            @Override
            public void onHidden(Tab tab, int reason) {
                updateInsetViewportBottom();
            }
        });
    }

    @Override
    public void onBackgroundColorChanged(int color) {
        mTab.onBackgroundColorChanged(color);
    }

    @Override
    public void onTopControlsChanged(
            int topControlsOffsetY, int contentOffsetY, int topControlsMinHeightOffsetY) {
        TabBrowserControlsOffsetHelper.get(mTab).setTopOffset(
                topControlsOffsetY, contentOffsetY, topControlsMinHeightOffsetY);
    }

    @Override
    public void onBottomControlsChanged(
            int bottomControlsOffsetY, int bottomControlsMinHeightOffsetY) {
        TabBrowserControlsOffsetHelper.get(mTab).setBottomOffset(
                bottomControlsOffsetY, bottomControlsMinHeightOffsetY);
    }

    /** Sets the Visual Viewport bottom inset. */
    private void updateInsetViewportBottom() {
        int inset =
                mTab.isHidden() || mCurrentInsetSupplier == null ? 0 : mCurrentInsetSupplier.get();

        if (inset == mApplicationViewportInsetBottomPx) return;

        mApplicationViewportInsetBottomPx = inset;

        RenderWidgetHostView renderWidgetHostView = mTab.getWebContents().getRenderWidgetHostView();
        if (renderWidgetHostView == null) return;

        renderWidgetHostView.onViewportInsetBottomChanged();
    }

    @Override
    protected int getViewportInsetBottom() {
<<<<<<< HEAD
        return mVisualViewportInsetBottomPx;
    }

    @Override
    public void updateAnchorViews(ViewGroup oldContainerView) {
        super.updateAnchorViews(oldContainerView);

        assert oldContainerView instanceof ContentView
                : "TabViewAndroidDelegate does not host container views other than ContentView.";

        // Transfer the drag state tracker to the new container view.
        ((ContentView) oldContainerView).removeOnDragListener(getDragStateTracker());
        getContentView().addOnDragListener(getDragStateTracker());
    }

    private ContentView getContentView() {
        assert getContainerView() instanceof ContentView
                : "TabViewAndroidDelegate does not host container views other than ContentView.";

        return (ContentView) getContainerView();
    }

    /* Destroy and clean up {@link DragStateTracker} to the content view. */
    @Override
    public void destroy() {
        super.destroy();
        if (getContentView() != null) {
            getContentView().removeOnDragListener(getDragStateTracker());
        }
        if (mDragAndDropBrowserDelegate != null) {
            getDragAndDropDelegate().setDragAndDropBrowserDelegate(null);
            mDragAndDropBrowserDelegate = null;
        }
        if (mCurrentInsetSupplier != null) {
            mCurrentInsetSupplier.removeObserver(mInsetObserver);
            mCurrentInsetSupplier = null;
        }
    }

    @Override
    public void onProvideAutofillVirtualStructure(ViewStructure structure, int flags) {
        mTab.onProvideAutofillVirtualStructure(structure, flags);
    }

    @Override
    public void autofill(final SparseArray<AutofillValue> values) {
        mTab.autofill(values);
    }

    @Override
    public boolean providesAutofillStructure() {
        return mTab.providesAutofillStructure();
    }

    DragAndDropBrowserDelegate getDragAndDropBrowserDelegateForTesting() {
        return mDragAndDropBrowserDelegate;
=======
        return mApplicationViewportInsetBottomPx;
>>>>>>> chromium
    }
}
