// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.toolbar.top;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.Nullable;

import org.chromium.base.TraceEvent;
import org.chromium.chrome.browser.toolbar.R;
import org.chromium.chrome.browser.toolbar.TabCountProvider;
import org.chromium.chrome.browser.toolbar.TabSwitcherDrawable;
import org.chromium.components.browser_ui.widget.highlight.PulseDrawable;
import org.chromium.components.browser_ui.widget.listmenu.ListMenuButton;
import org.chromium.ui.widget.Toast;

/**
 * A button displaying the number of open tabs. Clicking the button toggles the tab switcher view.
 * TODO(twellington): Replace with TabSwitcherButtonCoordinator so code can be shared with bottom
 *                    toolbar.
 */
<<<<<<< HEAD
public class ToggleTabStackButton extends ListMenuButton implements TabSwitcherDrawable.Observer {
    private final Callback<Integer> mTabCountSupplierObserver = this::onUpdateTabCount;
    private final Callback<Boolean> mNotificationDotObserver = this::onUpdateNotificationDot;
    private TabSwitcherDrawable mTabSwitcherButtonDrawable;
    private ObservableSupplier<Integer> mTabCountSupplier;
    private ObservableSupplier<Boolean> mNotificationDotSupplier;
    private Supplier<Boolean> mIsIncognitoSupplier;
=======
public class ToggleTabStackButton
        extends ListMenuButton implements TabCountProvider.TabCountObserver, View.OnClickListener,
                                          View.OnLongClickListener {
    private TabSwitcherDrawable mTabSwitcherButtonDrawable;
    private TabSwitcherDrawable mTabSwitcherButtonDrawableLight;
    private TabCountProvider mTabCountProvider;
    private OnClickListener mTabSwitcherListener;
    private OnLongClickListener mTabSwitcherLongClickListener;
    private PulseDrawable mHighlightDrawable;
    private Drawable mNormalBackground;
>>>>>>> chromium

    public ToggleTabStackButton(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void onFinishInflate() {
        super.onFinishInflate();

        mTabSwitcherButtonDrawable =
                TabSwitcherDrawable.createTabSwitcherDrawable(getContext(), false);
        mTabSwitcherButtonDrawableLight =
                TabSwitcherDrawable.createTabSwitcherDrawable(getContext(), true);
        setImageDrawable(mTabSwitcherButtonDrawable);
<<<<<<< HEAD
        mTabSwitcherButtonDrawable.addTabSwitcherDrawableObserver(this);
    }

    /** Called to destroy the tab stack button. */
    void destroy() {
        if (mTabCountSupplier != null) {
            mTabCountSupplier.removeObserver(mTabCountSupplierObserver);
        }
        if (mNotificationDotSupplier != null) {
            mNotificationDotSupplier.removeObserver(mNotificationDotObserver);
        }
        mTabSwitcherButtonDrawable.removeTabSwitcherDrawableObserver(this);
    }

    void setBrandedColorScheme(@BrandedColorScheme int brandedColorScheme) {
        mTabSwitcherButtonDrawable.setTint(
                ThemeUtils.getThemedToolbarIconTint(getContext(), brandedColorScheme));
        mTabSwitcherButtonDrawable.setNotificationBackground(brandedColorScheme);
        if (mIsIncognitoSupplier != null) {
            mTabSwitcherButtonDrawable.setIncognitoStatus(mIsIncognitoSupplier.get());
        }
    }

    /**
     * @param tabCountSupplier A supplier used to observe the number of tabs in the current model.
     * @param notificationDotSupplier A supplier used to observe whether to show the notification
     *     dot.
     * @param incognitoSupplier A supplier used to check for incongito state.
     */
    void setSuppliers(
            ObservableSupplier<Integer> tabCountSupplier,
            ObservableSupplier<Boolean> notificationDotSupplier,
            Supplier<Boolean> isIncognitoSupplier) {
        assert mTabCountSupplier == null : "setSuppliers should only be called once.";

        mTabCountSupplier = tabCountSupplier;
        tabCountSupplier.addObserver(mTabCountSupplierObserver);

        mNotificationDotSupplier = notificationDotSupplier;
        notificationDotSupplier.addObserver(mNotificationDotObserver);

        mIsIncognitoSupplier = isIncognitoSupplier;
=======
        setOnClickListener(this);
        setOnLongClickListener(this);
    }

    /**
     * Called to destroy the tab stack button.
     */
    void destroy() {
        if (mTabCountProvider != null) mTabCountProvider.removeObserver(this);
    }

    /**
     * Sets the OnClickListener that will be notified when the TabSwitcher button is pressed.
     * @param listener The callback that will be notified when the TabSwitcher button is pressed.
     */
    void setOnTabSwitcherClickHandler(OnClickListener listener) {
        mTabSwitcherListener = listener;
    }

    /**
     * Sets the OnLongClickListern that will be notified when the TabSwitcher button is long
     *         pressed.
     * @param listener The callback that will be notified when the TabSwitcher button is long
     *         pressed.
     */
    void setOnTabSwitcherLongClickHandler(OnLongClickListener listener) {
        mTabSwitcherLongClickListener = listener;
    }

    /**
     * Updates the contained drawable.
     * @param useLightDrawables Whether light drawables should be used.
     */
    void setUseLightDrawables(boolean useLightDrawables) {
        setImageDrawable(
                useLightDrawables ? mTabSwitcherButtonDrawableLight : mTabSwitcherButtonDrawable);
    }

    /**
     * @param provider The {@link TabCountProvider} used to observe the number of tabs in the
     *                 current model.
     */
    void setTabCountProvider(TabCountProvider provider) {
        mTabCountProvider = provider;
        mTabCountProvider.addObserverAndTrigger(this);
    }

    @Override
    public void onTabCountChanged(int numberOfTabs, boolean isIncognito) {
        setEnabled(numberOfTabs >= 1);
        setContentDescription(getResources().getQuantityString(
                R.plurals.accessibility_toolbar_btn_tabswitcher_toggle, numberOfTabs,
                numberOfTabs));
        mTabSwitcherButtonDrawableLight.updateForTabCount(numberOfTabs, isIncognito);
        mTabSwitcherButtonDrawable.updateForTabCount(numberOfTabs, isIncognito);
    }

    @Override
    public void onClick(View v) {
        if (mTabSwitcherListener != null && isClickable()) {
            mTabSwitcherListener.onClick(this);
        }
    }

    @Override
    public boolean onLongClick(View v) {
        if (mTabSwitcherLongClickListener != null && isLongClickable()) {
            return mTabSwitcherLongClickListener.onLongClick(v);
        } else {
            CharSequence description = getResources().getString(R.string.open_tabs);
            return Toast.showAnchoredToast(getContext(), v, description);
        }
>>>>>>> chromium
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        try (TraceEvent e = TraceEvent.scoped("ToggleTabStackButton.onMeasure")) {
            super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        }
    }

    @Override
    protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
        try (TraceEvent e = TraceEvent.scoped("ToggleTabStackButton.onLayout")) {
            super.onLayout(changed, left, top, right, bottom);
        }
    }
<<<<<<< HEAD

    // TabSwitcherDrawable.Observer implementation.

    @Override
    public void onDrawableStateChanged() {
        @PluralsRes
        int drawableDescRes = R.plurals.accessibility_toolbar_btn_tabswitcher_toggle_default;
        if (ChromeFeatureList.isEnabled(ChromeFeatureList.DATA_SHARING)
                && mTabSwitcherButtonDrawable.getShowIconNotificationStatus()) {
            drawableDescRes =
                    R.plurals
                            .accessibility_toolbar_btn_tabswitcher_toggle_default_with_notification;
        }

        int tabCount = mTabCountSupplier.get();
        String drawableText = getResources().getQuantityString(drawableDescRes, tabCount, tabCount);
        setContentDescription(drawableText);
        TooltipCompat.setTooltipText(this, drawableText);
    }

    /**
     * Draws the current visual state of this component for the purposes of rendering the tab
     * switcher animation, setting the alpha to fade the view by the appropriate amount.
     *
     * @param canvas Canvas to draw to.
     * @param alpha Integer (0-255) alpha level to draw at.
     */
    public void drawTabSwitcherAnimationOverlay(Canvas canvas, int alpha) {
        int backgroundWidth = mTabSwitcherButtonDrawable.getIntrinsicWidth();
        int backgroundHeight = mTabSwitcherButtonDrawable.getIntrinsicHeight();
        int backgroundLeft =
                (getWidth() - getPaddingLeft() - getPaddingRight() - backgroundWidth) / 2;
        backgroundLeft += getPaddingLeft();
        int backgroundTop =
                (getHeight() - getPaddingTop() - getPaddingBottom() - backgroundHeight) / 2;
        backgroundTop += getPaddingTop();
        canvas.translate(backgroundLeft, backgroundTop);

        int previousAlpha = mTabSwitcherButtonDrawable.getAlpha();
        mTabSwitcherButtonDrawable.setAlpha(255);
        mTabSwitcherButtonDrawable.draw(canvas);
        // restore alpha.
        getDrawable().setAlpha(previousAlpha);
    }

    public TabSwitcherDrawable getTabSwitcherDrawableForTesting() {
        return mTabSwitcherButtonDrawable;
    }

    private void onUpdateTabCount(int tabCount) {
        setEnabled(tabCount >= 1);
        mTabSwitcherButtonDrawable.updateForTabCount(tabCount, mIsIncognitoSupplier.get());
    }

    private void onUpdateNotificationDot(boolean showDot) {
        mTabSwitcherButtonDrawable.setNotificationIconStatus(showDot);
    }
=======
>>>>>>> chromium
}
