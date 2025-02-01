// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.omnibox;

import android.content.Context;
import android.content.res.ColorStateList;
import android.graphics.drawable.Drawable;
import android.os.Parcelable;
import android.util.AttributeSet;
import android.util.SparseArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.LinearLayout;

import androidx.annotation.CallSuper;
import androidx.annotation.NonNull;
import androidx.annotation.VisibleForTesting;
import androidx.core.view.MarginLayoutParamsCompat;

import org.chromium.base.ApiCompatibilityUtils;
import org.chromium.chrome.browser.lens.LensFeature;
import org.chromium.chrome.browser.omnibox.status.StatusCoordinator;
import org.chromium.chrome.browser.omnibox.status.StatusView;
import org.chromium.chrome.browser.omnibox.suggestions.AutocompleteCoordinator;
import org.chromium.components.browser_ui.widget.CompositeTouchDelegate;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents the location bar where the user types in URLs and
 * search terms.
 */
public class LocationBarLayout extends FrameLayout {
    protected ImageButton mDeleteButton;
    protected ImageButton mMicButton;
    protected ImageButton mLensButton;
    protected UrlBar mUrlBar;

    protected UrlBarCoordinator mUrlCoordinator;
    protected AutocompleteCoordinator mAutocompleteCoordinator;

    protected LocationBarDataProvider mLocationBarDataProvider;

    protected StatusCoordinator mStatusCoordinator;

    protected boolean mNativeInitialized;

    protected LinearLayout mUrlActionContainer;

    protected CompositeTouchDelegate mCompositeTouchDelegate;
    protected SearchEngineLogoUtils mSearchEngineLogoUtils;

    public LocationBarLayout(Context context, AttributeSet attrs) {
        this(context, attrs, R.layout.location_bar);

        mCompositeTouchDelegate = new CompositeTouchDelegate(this);
        setTouchDelegate(mCompositeTouchDelegate);
    }

    public LocationBarLayout(Context context, AttributeSet attrs, int layoutId) {
        super(context, attrs);

        LayoutInflater.from(context).inflate(layoutId, this, true);

        mDeleteButton = findViewById(R.id.delete_button);
        mUrlBar = findViewById(R.id.url_bar);
        mMicButton = findViewById(R.id.mic_button);
        mLensButton = LensFeature.SEARCH_BOX_START_VARIANT_LENS_CAMERA_ASSISTED_SEARCH.getValue()
                ? findViewById(R.id.lens_camera_button_start)
                : findViewById(R.id.lens_camera_button_end);
        mUrlActionContainer = (LinearLayout) findViewById(R.id.url_action_container);
    }

    /**
     * Called when activity is being destroyed.
     */
    void destroy() {
        if (mAutocompleteCoordinator != null) {
            // Don't call destroy() on mAutocompleteCoordinator since we don't own it.
            mAutocompleteCoordinator = null;
        }

        mUrlCoordinator = null;
    }

    @Override
    protected void onFinishInflate() {
        super.onFinishInflate();

        setLayoutTransition(null);

        StatusView statusView = findViewById(R.id.location_bar_status);
        statusView.setCompositeTouchDelegate(mCompositeTouchDelegate);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        updateLayoutParams();
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }

    /**
     * Initializes LocationBarLayout with dependencies that aren't immediately available at
     * construction time.
     *
     * @param autocompleteCoordinator The coordinator for interacting with the autocomplete
     *         subsystem.
     * @param urlCoordinator The coordinator for interacting with the url bar.
     * @param statusCoordinator The coordinator for interacting with the status icon.
     * @param locationBarDataProvider Provider of LocationBar data, e.g. url and title.
     * @param searchEngineLogoUtils Allows querying the state of the search engine logo feature.
     */
    @CallSuper
    public void initialize(@NonNull AutocompleteCoordinator autocompleteCoordinator,
            @NonNull UrlBarCoordinator urlCoordinator, @NonNull StatusCoordinator statusCoordinator,
            @NonNull LocationBarDataProvider locationBarDataProvider,
            @NonNull SearchEngineLogoUtils searchEngineLogoUtils) {
        mAutocompleteCoordinator = autocompleteCoordinator;
        mUrlCoordinator = urlCoordinator;
        mStatusCoordinator = statusCoordinator;
        mLocationBarDataProvider = locationBarDataProvider;
        mSearchEngineLogoUtils = searchEngineLogoUtils;
    }

    @VisibleForTesting(otherwise = VisibleForTesting.PROTECTED)
    public AutocompleteCoordinator getAutocompleteCoordinator() {
        return mAutocompleteCoordinator;
    }

    /**
     *  Signals to LocationBarLayout that's it safe to call code that requires native to be loaded.
     */
    public void onFinishNativeInitialization() {
        mNativeInitialized = true;
    }

    /* package */ void setMicButtonDrawable(Drawable drawable) {
        mMicButton.setImageDrawable(drawable);
    }

    /* package */ void setMicButtonTint(ColorStateList colorStateList) {
        ApiCompatibilityUtils.setImageTintList(mMicButton, colorStateList);
    }

    /* package */ void setDeleteButtonTint(ColorStateList colorStateList) {
        ApiCompatibilityUtils.setImageTintList(mDeleteButton, colorStateList);
    }

    /* package */ void setLensButtonTint(ColorStateList colorStateList) {
        ApiCompatibilityUtils.setImageTintList(mLensButton, colorStateList);
    }

    @Override
    protected void dispatchRestoreInstanceState(SparseArray<Parcelable> container) {
        // Don't restore the state of the location bar, it can lead to all kind of bad states with
        // the popup.
        // When we restore tabs, we focus the selected tab so the URL of the page shows.
    }

    protected void onNtpStartedLoading() {}

    public View getSecurityIconView() {
        return mStatusCoordinator.getSecurityIconView();
    }

    /**
     * Specify whether location bar should present icons when focused.
     * @param showIcon True if we should show the icons when the url is focused.
     */
    protected void setShowIconsWhenUrlFocused(boolean showIcon) {}

    /**
     * @return The margin to be applied to the URL bar based on the buttons currently visible next
     *         to it, used to avoid text overlapping the buttons and vice versa.
     */
    private int getUrlContainerMarginEnd() {
        int urlContainerMarginEnd = 0;
        for (View childView : getUrlContainerViewsForMargin()) {
            ViewGroup.MarginLayoutParams childLayoutParams =
                    (ViewGroup.MarginLayoutParams) childView.getLayoutParams();
            urlContainerMarginEnd += childLayoutParams.width
                    + MarginLayoutParamsCompat.getMarginStart(childLayoutParams)
                    + MarginLayoutParamsCompat.getMarginEnd(childLayoutParams);
        }
        if (mUrlActionContainer != null && mUrlActionContainer.getVisibility() == View.VISIBLE) {
            ViewGroup.MarginLayoutParams urlActionContainerLayoutParams =
                    (ViewGroup.MarginLayoutParams) mUrlActionContainer.getLayoutParams();
            urlContainerMarginEnd +=
                    MarginLayoutParamsCompat.getMarginStart(urlActionContainerLayoutParams)
                    + MarginLayoutParamsCompat.getMarginEnd(urlActionContainerLayoutParams);
        }
        urlContainerMarginEnd += mStatusCoordinator.getAdditionalUrlContainerMarginEnd();
        return urlContainerMarginEnd;
    }

    /**
     * Updates the layout params for the location bar start aligned views.
     */
    @VisibleForTesting
    void updateLayoutParams() {
        int startMargin = 0;
        for (int i = 0; i < getChildCount(); i++) {
            View childView = getChildAt(i);
            if (childView.getVisibility() != GONE) {
                LayoutParams childLayoutParams = (LayoutParams) childView.getLayoutParams();
                if (MarginLayoutParamsCompat.getMarginStart(childLayoutParams) != startMargin) {
                    MarginLayoutParamsCompat.setMarginStart(childLayoutParams, startMargin);
                    childView.setLayoutParams(childLayoutParams);
                }
                if (childView == mUrlBar) break;

                int widthMeasureSpec;
                int heightMeasureSpec;
                if (childLayoutParams.width == LayoutParams.WRAP_CONTENT) {
                    widthMeasureSpec =
                            MeasureSpec.makeMeasureSpec(getMeasuredWidth(), MeasureSpec.AT_MOST);
                } else if (childLayoutParams.width == LayoutParams.MATCH_PARENT) {
                    widthMeasureSpec =
                            MeasureSpec.makeMeasureSpec(getMeasuredWidth(), MeasureSpec.EXACTLY);
                } else {
                    widthMeasureSpec = MeasureSpec.makeMeasureSpec(
                            childLayoutParams.width, MeasureSpec.EXACTLY);
                }
                if (childLayoutParams.height == LayoutParams.WRAP_CONTENT) {
                    heightMeasureSpec =
                            MeasureSpec.makeMeasureSpec(getMeasuredHeight(), MeasureSpec.AT_MOST);
                } else if (childLayoutParams.height == LayoutParams.MATCH_PARENT) {
                    heightMeasureSpec =
                            MeasureSpec.makeMeasureSpec(getMeasuredHeight(), MeasureSpec.EXACTLY);
                } else {
                    heightMeasureSpec = MeasureSpec.makeMeasureSpec(
                            childLayoutParams.height, MeasureSpec.EXACTLY);
                }
                childView.measure(widthMeasureSpec, heightMeasureSpec);
                startMargin += childView.getMeasuredWidth();
            }
        }

        int urlContainerMarginEnd = getUrlContainerMarginEnd();
        LayoutParams urlLayoutParams = (LayoutParams) mUrlBar.getLayoutParams();
        if (MarginLayoutParamsCompat.getMarginEnd(urlLayoutParams) != urlContainerMarginEnd) {
            MarginLayoutParamsCompat.setMarginEnd(urlLayoutParams, urlContainerMarginEnd);
            mUrlBar.setLayoutParams(urlLayoutParams);
        }
    }

    /**
     * Gets the list of views that need to be taken into account for adding margin to the end of the
     * URL bar.
     *
     * @return A {@link List} of the views to be taken into account for URL bar margin to avoid
     *         overlapping text and buttons.
     */
    protected List<View> getUrlContainerViewsForMargin() {
        List<View> outList = new ArrayList<View>();
        if (mUrlActionContainer == null) return outList;

        for (int i = 0; i < mUrlActionContainer.getChildCount(); i++) {
            View childView = mUrlActionContainer.getChildAt(i);
            if (childView.getVisibility() != GONE) outList.add(childView);
        }
        return outList;
    }

    /** Sets the visibility of the delete URL content button. */
    /* package */ void setDeleteButtonVisibility(boolean shouldShow) {
        mDeleteButton.setVisibility(shouldShow ? VISIBLE : GONE);
    }

    /** Sets the visibility of the mic button. */
    /* package */ void setMicButtonVisibility(boolean shouldShow) {
        mMicButton.setVisibility(shouldShow ? VISIBLE : GONE);
    }

    /** Sets the visibility of the mic button. */
    /* package */ void setLensButtonVisibility(boolean shouldShow) {
        mLensButton.setVisibility(shouldShow ? VISIBLE : GONE);
    }

    protected void setUnfocusedWidth(int unfocusedWidth) {
        mStatusCoordinator.setUnfocusedLocationBarWidth(unfocusedWidth);
    }

    @VisibleForTesting
    public StatusCoordinator getStatusCoordinatorForTesting() {
        return mStatusCoordinator;
    }

    /* package */ void setUrlActionContainerVisibility(int visibility) {
        mUrlActionContainer.setVisibility(visibility);
    }
<<<<<<< HEAD

    /** Returns the increase in StatusView end padding, when the Url bar is focused. */
    public int getEndPaddingPixelSizeOnFocusDelta() {
        return getResources()
                .getDimensionPixelSize(
                        mLocationBarDataProvider.isIncognitoBranded()
                                ? R.dimen.location_bar_icon_end_padding_focused_incognito
                                : R.dimen.location_bar_icon_end_padding_focused);
    }

    /**
     * Expand the left and right space besides the status view, and increase the location bar
     * vertical padding based on current animation progress percent.
     *
     * @param ntpSearchBoxScrollFraction The degree to which the omnibox has expanded to full width
     *     in NTP due to the NTP search box is being scrolled up.
     * @param urlFocusChangeFraction The degree to which the omnibox has expanded due to it is
     *     getting focused.
     * @param isUrlFocusChangeInProgress True if the url focus change is in progress.
     */
    protected void setUrlFocusChangePercent(
            float ntpSearchBoxScrollFraction,
            float urlFocusChangeFraction,
            boolean isUrlFocusChangeInProgress) {
        mIsUrlFocusChangeInProgress = isUrlFocusChangeInProgress;
        mUrlFocusPercentage = Math.max(ntpSearchBoxScrollFraction, urlFocusChangeFraction);
        setStatusViewLeftSpacePercent(
                ntpSearchBoxScrollFraction, urlFocusChangeFraction, isUrlFocusChangeInProgress);
        setStatusViewRightSpacePercent(
                ntpSearchBoxScrollFraction, urlFocusChangeFraction, isUrlFocusChangeInProgress);
    }

    /**
     * Set the "left space width" based on current animation progress percent. This can either
     * mutate the width of a Space view to the left of the status view or use translation to
     * accomplish the same thing without triggering a relayout.
     *
     * @param ntpSearchBoxScrollFraction The degree to which the omnibox has expanded to full width
     *     in NTP due to the NTP search box is being scrolled up.
     * @param urlFocusChangeFraction The degree to which the omnibox has expanded due to it is
     *     getting focused.
     * @param isUrlFocusChangeInProgress True if the url focus change is in progress.
     */
    protected void setStatusViewLeftSpacePercent(
            float ntpSearchBoxScrollFraction,
            float urlFocusChangeFraction,
            boolean isUrlFocusChangeInProgress) {
        float maxPercent = Math.max(ntpSearchBoxScrollFraction, urlFocusChangeFraction);
        boolean isOnTablet = DeviceFormFactor.isNonMultiDisplayContextOnTablet(getContext());
        // The tablet UI doesn't have status view spacer elements so must use translation.
        float translationX;
        if (!isOnTablet && isUrlFocusChangeInProgress && ntpSearchBoxScrollFraction == 1) {
            translationX =
                    OmniboxResourceProvider.getFocusedStatusViewLeftSpacing(getContext())
                            + mStatusIconAndUrlBarOffset * (1 - urlFocusChangeFraction);
        } else {
            translationX =
                    OmniboxResourceProvider.getFocusedStatusViewLeftSpacing(getContext())
                            * maxPercent;
        }
        mStatusCoordinator.setTranslationX(
                MathUtils.flipSignIf(translationX, getLayoutDirection() == LAYOUT_DIRECTION_RTL));
    }

    /**
     * Set the "right space width" based on current animation progress percent. This can either
     * mutate the width of a Space view to the right of the status view or use translation to
     * accomplish the same thing without triggering a relayout.
     *
     * @param ntpSearchBoxScrollFraction The degree to which the omnibox has expanded to full width
     *     in NTP due to the NTP search box is being scrolled up.
     * @param urlFocusChangeFraction The degree to which the omnibox has expanded due to it is
     *     getting focused.
     * @param isUrlFocusChangeInProgress True if the url focus change is in progress.
     */
    protected void setStatusViewRightSpacePercent(
            float ntpSearchBoxScrollFraction,
            float urlFocusChangeFraction,
            boolean isUrlFocusChangeInProgress) {
        // The tablet UI doesn't have status view spacer elements so must use translation.
        float translationX;
        if (mUrlBarLaidOutAtFocusedWidth) {
            translationX =
                    getUrlbarTranslationXForFocusAndScrollAnimationOnNtp(
                            ntpSearchBoxScrollFraction,
                            urlFocusChangeFraction,
                            isUrlFocusChangeInProgress,
                            DeviceFormFactor.isNonMultiDisplayContextOnTablet(getContext()));
        } else {
            // No compensation is needed at 0% because the margin is reset to normal.
            translationX = 0.0f;
        }

        mUrlBar.setTranslationX(
                MathUtils.flipSignIf(translationX, getLayoutDirection() == LAYOUT_DIRECTION_RTL));
    }

    /**
     * Get the translation for the status view based on the current animation progress percent.
     *
     * @param ntpSearchBoxScrollFraction The degree to which the omnibox has expanded to full width
     *     in NTP due to the NTP search box is being scrolled up.
     * @param urlFocusChangeFraction The degree to which the omnibox has expanded due to it is
     *     getting focused.
     * @param isUrlFocusChangeInProgress True if the url focus change is in progress.
     * @param isOnTablet True if the current page is on the tablet.
     */
    float getUrlbarTranslationXForFocusAndScrollAnimationOnNtp(
            float ntpSearchBoxScrollFraction,
            float urlFocusChangeFraction,
            boolean isUrlFocusChangeInProgress,
            boolean isOnTablet) {

        if (!isOnTablet && isUrlFocusChangeInProgress && ntpSearchBoxScrollFraction == 1) {
            // For the focus and un-focus animation when the real search box is visible
            // on NTP.
            return mStatusIconAndUrlBarOffset * (1 - urlFocusChangeFraction);
        }

        float translationX = -getFocusedStatusViewSpacingDelta();

        boolean isNtpOnPhone =
                mStatusCoordinator.isSearchEngineStatusIconVisible()
                        && UrlUtilities.isNtpUrl(mLocationBarDataProvider.getCurrentGurl())
                        && !isOnTablet;
        boolean isScrollingOnNtpOnPhone = !mUrlBar.hasFocus() && isNtpOnPhone;

        if (isScrollingOnNtpOnPhone) {
            translationX -=
                    mStatusCoordinator.getStatusIconWidth()
                            - getResources()
                                    .getDimensionPixelSize(
                                            R.dimen.location_bar_status_icon_holding_space_size);
        }

        boolean isInSingleUrlBarMode =
                isNtpOnPhone
                        && mSearchEngineUtils != null
                        && mSearchEngineUtils.doesDefaultSearchEngineHaveLogo();
        if (isInSingleUrlBarMode) {
            translationX +=
                    (getResources().getDimensionPixelSize(R.dimen.fake_search_box_start_padding)
                            - getResources()
                                    .getDimensionPixelSize(
                                            R.dimen.location_bar_status_icon_holding_space_size));
        }

        // If the url bar is laid out at its smaller, focused width, translate back towards
        // start to compensate for the increased start margin set in #updateLayoutParams. The
        // magnitude of the compensation decreases as % increases and is 0 at full focus %.
        float percent = Math.max(ntpSearchBoxScrollFraction, urlFocusChangeFraction);
        return translationX * (1.0f - percent);
    }

    /**
     * The delta between the total status view spacing (left + right) when unfocused vs focused. The
     * status view has additional spacing applied when focused to visually align it and the UrlBar
     * with omnibox suggestions. See below diagram; the additional spacing is denoted with _
     * Unfocused: [ (i) www.example.com] Focused: [ _(G)_ Search or type web address] [ 🔍 Foobar ↖
     * ] [ 🔍 Barbaz ↖ ]
     */
    @VisibleForTesting
    int getFocusedStatusViewSpacingDelta() {
        return getEndPaddingPixelSizeOnFocusDelta()
                + OmniboxResourceProvider.getFocusedStatusViewLeftSpacing(getContext());
    }

    /** Applies the new SearchEngineUtils. */
    void setSearchEngineUtils(SearchEngineUtils searchEngineUtils) {
        mSearchEngineUtils = searchEngineUtils;
    }

    /** Returns the source of Voice Recognition interactions. */
    public int getVoiceRecogintionSource() {
        return VoiceRecognitionHandler.VoiceInteractionSource.OMNIBOX;
    }

    /** Returns the entrypoint used to launch Lens. */
    public int getLensEntryPoint() {
        return LensEntryPoint.OMNIBOX;
    }

    /** Returns whether the Omnibox text should be cleared on focus. */
    public boolean shouldClearTextOnFocus() {
        return true;
    }

    /**
     * Updates the value for the end margin of the url action container in the search box.
     *
     * @param useDefaultUrlActionContainerEndMargin Whether to use the default end margin for the
     *     url action container in the search box. If not we will use the specific end margin value
     *     for NTP's un-focus state.
     */
    public void updateUrlActionContainerEndMargin(boolean useDefaultUrlActionContainerEndMargin) {
        mUrlActionContainerEndMargin =
                useDefaultUrlActionContainerEndMargin
                        ? getResources()
                                .getDimensionPixelSize(R.dimen.location_bar_url_action_offset)
                        : getResources()
                                .getDimensionPixelSize(R.dimen.location_bar_url_action_offset_ntp);
    }

    int getUrlActionContainerEndMarginForTesting() {
        return mUrlActionContainerEndMargin;
    }
=======
>>>>>>> chromium
}
