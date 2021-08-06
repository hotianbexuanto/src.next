// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tabbed_mode;

import android.annotation.SuppressLint;
<<<<<<< HEAD
import android.content.Context;
=======
import android.annotation.TargetApi;
import android.content.res.Resources;
>>>>>>> chromium
import android.os.Build;
import android.view.Window;

import androidx.annotation.ColorInt;
import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;

import org.chromium.base.CallbackController;
import org.chromium.base.MathUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.chrome.R;
<<<<<<< HEAD
import org.chromium.chrome.browser.browser_controls.BottomControlsStacker;
import org.chromium.chrome.browser.browser_controls.BrowserControlsStateProvider;
import org.chromium.chrome.browser.contextualsearch.ContextualSearchManager;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.fullscreen.FullscreenManager;
import org.chromium.chrome.browser.fullscreen.FullscreenOptions;
import org.chromium.chrome.browser.keyboard_accessory.AccessorySheetVisualStateProvider;
import org.chromium.chrome.browser.layouts.LayoutManager;
import org.chromium.chrome.browser.layouts.LayoutStateProvider;
import org.chromium.chrome.browser.layouts.LayoutStateProvider.LayoutStateObserver;
import org.chromium.chrome.browser.layouts.LayoutType;
import org.chromium.chrome.browser.omnibox.suggestions.OmniboxSuggestionsVisualState;
import org.chromium.chrome.browser.tab.EmptyTabObserver;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabObscuringHandler;
import org.chromium.chrome.browser.tab.TabObserver;
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tabmodel.TabModelSelectorObserver;
import org.chromium.chrome.browser.ui.edge_to_edge.EdgeToEdgeController;
import org.chromium.chrome.browser.ui.edge_to_edge.NavigationBarColorProvider;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.components.browser_ui.bottomsheet.BottomSheetController;
import org.chromium.components.browser_ui.edge_to_edge.EdgeToEdgeSupplier.ChangeObserver;
import org.chromium.components.browser_ui.edge_to_edge.EdgeToEdgeSystemBarColorHelper;
import org.chromium.components.browser_ui.styles.SemanticColorUtils;
import org.chromium.ui.InsetObserver;
import org.chromium.ui.interpolators.Interpolators;
=======
import org.chromium.chrome.browser.compositor.layouts.EmptyOverviewModeObserver;
import org.chromium.chrome.browser.compositor.layouts.OverviewModeBehavior;
import org.chromium.chrome.browser.compositor.layouts.OverviewModeBehavior.OverviewModeObserver;
import org.chromium.chrome.browser.device.DeviceClassManager;
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tabmodel.TabModelSelectorObserver;
import org.chromium.chrome.browser.tasks.tab_management.TabUiFeatureUtilities;
import org.chromium.chrome.browser.vr.VrModuleProvider;
import org.chromium.ui.UiUtils;
>>>>>>> chromium
import org.chromium.ui.util.ColorUtils;
import org.chromium.ui.vr.VrModeObserver;

<<<<<<< HEAD
import java.util.Optional;

/** Controls the bottom system navigation bar color for the provided {@link Window}. */
@RequiresApi(Build.VERSION_CODES.O_MR1)
class TabbedNavigationBarColorController
        implements BottomAttachedUiObserver.Observer, NavigationBarColorProvider {
    /** The amount of time transitioning from one color to another should take in ms. */
    public static final long NAVBAR_COLOR_TRANSITION_DURATION_MS = 250;

    private final Context mContext;
    private final FullscreenManager mFullScreenManager;
=======
/**
 * Controls the bottom system navigation bar color for the provided {@link Window}.
 */
@RequiresApi(Build.VERSION_CODES.O_MR1)
class TabbedNavigationBarColorController implements VrModeObserver {
    private final Window mWindow;
    private final ViewGroup mRootView;
    private final Resources mResources;
    private final @ColorInt int mDefaultScrimColor;
>>>>>>> chromium

    // May be null if we return from the constructor early. Otherwise will be set.
    private final @Nullable TabModelSelector mTabModelSelector;
    private final @Nullable TabModelSelectorObserver mTabModelSelectorObserver;
<<<<<<< HEAD
    private final Callback<TabModel> mCurrentTabModelObserver;
    private final @Nullable FullscreenManager.Observer mFullscreenObserver;
    private final ObservableSupplier<EdgeToEdgeController> mEdgeToEdgeControllerSupplier;
    private final @NonNull ObservableSupplier<Integer> mOverviewColorSupplier;
    private final @NonNull Callback<Integer> mOnOverviewColorChanged =
            color -> updateNavigationBarColor();
    private final Callback<EdgeToEdgeController> mEdgeToEdgeRegisterChangeObserverCallback;
    private final EdgeToEdgeSystemBarColorHelper mEdgeToEdgeSystemBarColorHelper;
    private final @Nullable BottomAttachedUiObserver mBottomAttachedUiObserver;
    private final TabObserver mTabObserver;
    private final ObserverList<Observer> mObservers = new ObserverList<>();

    private @Nullable LayoutStateProvider mLayoutManager;
    private @Nullable LayoutStateObserver mLayoutStateObserver;
    private CallbackController mCallbackController = new CallbackController();

    /**
     * The color intended for the navigation bar, as well as any similar UI (such as the bottom chin
     * in edge-to-edge). This may differ from the window navigation bar color when that color is
     * transparent (as in edge-to-edge mode).
     */
    private @ColorInt int mNavigationBarColor;

    /**
     * The target color for the {@link Window}'s navigation bar. This will have a value set during
     * animations, and will be null otherwise.
     */
    private @Nullable @ColorInt Integer mTargetNavigationBarColor;

    private boolean mForceDarkNavigationBarColor;
    private boolean mIsInFullscreen;
    private @ColorInt int mCurrentScrimColor;
    private EdgeToEdgeController mEdgeToEdgeController;
    private @Nullable ChangeObserver mEdgeToEdgeChangeObserver;
    private @Nullable Tab mActiveTab;
    private @Nullable @ColorInt Integer mBottomAttachedUiColor;
    private boolean mForceShowDivider;
    private boolean mOverviewMode;
    private ValueAnimator mNavbarColorTransitionAnimation;

    /**
     * Creates a new {@link TabbedNavigationBarColorController} instance.
     *
     * @param context Used to load resources.
     * @param tabModelSelector The {@link TabModelSelector} used to determine which tab model is
     *     selected.
     * @param layoutManagerSupplier An {@link ObservableSupplier} for the {@link LayoutManager}
     *     associated with the containing activity.
     * @param fullscreenManager The {@link FullscreenManager} used to determine if fullscreen is
     *     enabled.
     * @param edgeToEdgeControllerSupplier Supplies an {@link EdgeToEdgeController} to detect when
     *     the UI is being drawn edge to edge so the navigation bar color can be changed
     *     appropriately.
     * @param bottomControlsStacker The {@link BottomControlsStacker} for interacting with and
     *     checking the state of the bottom browser controls.
     * @param browserControlsStateProvider A {@link BrowserControlsStateProvider} to watch for
     *     changes to the browser controls.
     * @param snackbarManagerSupplier Supplies a {@link SnackbarManager} to watch for snackbars
     *     being shown.
     * @param contextualSearchManagerSupplier Supplies a {@link ContextualSearchManager} to watch
     *     for changes to contextual search and the overlay panel.
     * @param bottomSheetController A {@link BottomSheetController} to interact with and watch for
     *     changes to the bottom sheet.
     * @param omniboxSuggestionsVisualState An optional {@link OmniboxSuggestionsVisualState} for
     *     access to the visual state of the omnibox suggestions.
     * @param accessorySheetVisualStateSupplier Supplies an {@link
     *     AccessorySheetVisualStateProvider} to watch for visual changes to the keyboard accessory
     *     sheet.
     * @param overviewColorSupplier Notifies when the overview color changes.
     * @param insetObserver An {@link InsetObserver} to listen for changes to the window insets.
     * @param edgeToEdgeSystemBarColorHelper Helps setting nav bar colors when in edge-to-edge.
     * @param tabObscuringHandler A {@link TabObscuringHandler} to listen to the tab-obscuring state
     *     change.
     */
    TabbedNavigationBarColorController(
            Context context,
            TabModelSelector tabModelSelector,
            ObservableSupplier<LayoutManager> layoutManagerSupplier,
            FullscreenManager fullscreenManager,
            ObservableSupplier<EdgeToEdgeController> edgeToEdgeControllerSupplier,
            @NonNull BottomControlsStacker bottomControlsStacker,
            @NonNull BrowserControlsStateProvider browserControlsStateProvider,
            @NonNull Supplier<SnackbarManager> snackbarManagerSupplier,
            @NonNull ObservableSupplier<ContextualSearchManager> contextualSearchManagerSupplier,
            @NonNull BottomSheetController bottomSheetController,
            Optional<OmniboxSuggestionsVisualState> omniboxSuggestionsVisualState,
            @NonNull
                    ObservableSupplier<AccessorySheetVisualStateProvider>
                            accessorySheetVisualStateSupplier,
            @NonNull ObservableSupplier<Integer> overviewColorSupplier,
            InsetObserver insetObserver,
            @NonNull EdgeToEdgeSystemBarColorHelper edgeToEdgeSystemBarColorHelper,
            @NonNull TabObscuringHandler tabObscuringHandler) {
        this(
                context,
                tabModelSelector,
                layoutManagerSupplier,
                fullscreenManager,
                edgeToEdgeControllerSupplier,
                overviewColorSupplier,
                edgeToEdgeSystemBarColorHelper,
                ChromeFeatureList.sNavBarColorMatchesTabBackground.isEnabled()
                        ? new BottomAttachedUiObserver(
                                context,
                                bottomControlsStacker,
                                browserControlsStateProvider,
                                snackbarManagerSupplier.get(),
                                contextualSearchManagerSupplier,
                                bottomSheetController,
                                omniboxSuggestionsVisualState,
                                accessorySheetVisualStateSupplier,
                                insetObserver,
                                tabObscuringHandler)
                        : null);
    }

    @VisibleForTesting
    TabbedNavigationBarColorController(
            Context context,
            TabModelSelector tabModelSelector,
            ObservableSupplier<LayoutManager> layoutManagerSupplier,
            FullscreenManager fullscreenManager,
            ObservableSupplier<EdgeToEdgeController> edgeToEdgeControllerSupplier,
            @NonNull ObservableSupplier<Integer> overviewColorSupplier,
            @NonNull EdgeToEdgeSystemBarColorHelper edgeToEdgeSystemBarColorHelper,
            @Nullable BottomAttachedUiObserver bottomAttachedUiObserver) {
        assert Build.VERSION.SDK_INT >= Build.VERSION_CODES.O_MR1;

        mContext = context;
        mFullScreenManager = fullscreenManager;
        mEdgeToEdgeSystemBarColorHelper = edgeToEdgeSystemBarColorHelper;
=======
    private @Nullable OverviewModeBehavior mOverviewModeBehavior;
    private @Nullable OverviewModeObserver mOverviewModeObserver;
    private CallbackController mCallbackController = new CallbackController();

    private @ColorInt int mNavigationBarColor;
    private boolean mForceDarkNavigationBarColor;
    private boolean mOverviewModeHiding;
    private float mNavigationBarScrimFraction;

    /**
     * Creates a new {@link TabbedNavigationBarColorController} instance.
     * @param window The {@link Window} this controller should operate on.
     * @param tabModelSelector The {@link TabModelSelector} used to determine which tab model is
     *                         selected.
     * @param overviewModeBehaviorSupplier An {@link ObservableSupplier} for the
     *         {@link OverviewModeBehavior} associated with the containing activity.
     */
    TabbedNavigationBarColorController(Window window, TabModelSelector tabModelSelector,
            OneshotSupplier<OverviewModeBehavior> overviewModeBehaviorSupplier) {
        assert Build.VERSION.SDK_INT >= Build.VERSION_CODES.O_MR1;

        mWindow = window;
        mRootView = (ViewGroup) mWindow.getDecorView().getRootView();
        mResources = mRootView.getResources();
        mDefaultScrimColor =
                ApiCompatibilityUtils.getColor(mResources, R.color.default_scrim_color);
>>>>>>> chromium

        // If we're not using a light navigation bar, it will always be the same dark color so
        // there's no need to register observers and manipulate coloring.
        if (!mResources.getBoolean(R.bool.window_light_navigation_bar)) {
            mTabModelSelector = null;
            mTabModelSelectorObserver = null;
            return;
        }

        mTabModelSelector = tabModelSelector;
        mTabModelSelectorObserver = new TabModelSelectorObserver() {
            @Override
            public void onTabModelSelected(TabModel newModel, TabModel oldModel) {
                updateNavigationBarColor();
            }
        };
        mTabModelSelector.addObserver(mTabModelSelectorObserver);

        overviewModeBehaviorSupplier.onAvailable(
                mCallbackController.makeCancelable(this::setOverviewModeBehavior));

<<<<<<< HEAD
        mEdgeToEdgeControllerSupplier = edgeToEdgeControllerSupplier;
        mEdgeToEdgeRegisterChangeObserverCallback =
                (controller) -> {
                    if (mEdgeToEdgeController != null) {
                        mEdgeToEdgeController.unregisterObserver(mEdgeToEdgeChangeObserver);
                    }
                    mEdgeToEdgeController = controller;
                    mEdgeToEdgeChangeObserver =
                            (bottomInset, isDrawingToEdge, isPageOptInToEdge) -> {
                                updateNavigationBarColor(
                                        /* forceShowDivider= */ false,
                                        /* disableAnimation= */ false);
                            };
                    mEdgeToEdgeController.registerObserver(mEdgeToEdgeChangeObserver);
                };
        mEdgeToEdgeControllerSupplier.addObserver(mEdgeToEdgeRegisterChangeObserverCallback);

        mOverviewColorSupplier = overviewColorSupplier;
        mOverviewColorSupplier.addObserver(mOnOverviewColorChanged);
        mOverviewMode = false;

        // TODO(crbug.com/40560014): Observe tab loads to restrict black bottom nav to
=======
        // TODO(https://crbug.com/806054): Observe tab loads to restrict black bottom nav to
>>>>>>> chromium
        // incognito NTP.

        updateNavigationBarColor();

        VrModuleProvider.registerVrModeObserver(this);
    }

    /**
     * Destroy this {@link TabbedNavigationBarColorController} instance.
     */
    public void destroy() {
<<<<<<< HEAD
        if (mTabModelSelector != null) {
            mTabModelSelector.removeObserver(mTabModelSelectorObserver);
            mTabModelSelector.getCurrentTabModelSupplier().removeObserver(mCurrentTabModelObserver);
        }
        if (mActiveTab != null) mActiveTab.removeObserver(mTabObserver);
        if (mLayoutManager != null) {
            mLayoutManager.removeObserver(mLayoutStateObserver);
            mOverviewColorSupplier.removeObserver(mOnOverviewColorChanged);
=======
        if (mTabModelSelector != null) mTabModelSelector.removeObserver(mTabModelSelectorObserver);
        if (mOverviewModeBehavior != null) {
            mOverviewModeBehavior.removeOverviewModeObserver(mOverviewModeObserver);
>>>>>>> chromium
        }
        if (mCallbackController != null) {
            mCallbackController.destroy();
            mCallbackController = null;
        }
        VrModuleProvider.unregisterVrModeObserver(this);
    }

    @Override
    public void onScrimOverlapChanged(@ColorInt int scrimColor) {
        setNavigationBarScrimColor(scrimColor);
    }

    /**
     * @param layoutManager The {@link LayoutStateProvider} used to determine whether
     *                             overview mode is showing.
     */
    private void setLayoutManager(LayoutManager layoutManager) {
        if (mLayoutManager != null) {
            mLayoutManager.removeObserver(mLayoutStateObserver);
        }

<<<<<<< HEAD
        mLayoutManager = layoutManager;
        mLayoutStateObserver =
                new LayoutStateObserver() {
                    @Override
                    public void onStartedShowing(@LayoutType int layoutType) {
                        if (layoutType != LayoutType.TAB_SWITCHER) return;
                        updateNavigationBarColor();
                        enableOverviewMode();
                    }

                    @Override
                    public void onStartedHiding(@LayoutType int layoutType) {
                        if (layoutType != LayoutType.TAB_SWITCHER) return;
                        updateNavigationBarColor();
                        disableOverviewMode();
                    }
=======
        mOverviewModeBehavior = overviewModeBehavior;
        mOverviewModeObserver = new EmptyOverviewModeObserver() {
            @Override
            public void onOverviewModeStartedShowing(boolean showToolbar) {
                mOverviewModeHiding = false;
                updateNavigationBarColor();
            }

            @Override
            public void onOverviewModeStartedHiding(boolean showToolbar, boolean delayAnimation) {
                mOverviewModeHiding = true;
                updateNavigationBarColor();
            }
>>>>>>> chromium

                    @Override
                    public void onFinishedHiding(int layoutType) {
                        mOverviewModeHiding = false;
                    }
                });
        mLayoutManager.addObserver(mLayoutStateObserver);
        updateNavigationBarColor();
    }

    @Override
    public void onExitVr() {
        // The platform ignores the light navigation bar system UI flag when launching an Activity
        // in VR mode, so we need to restore it when VR is exited.
        UiUtils.setNavigationBarIconColor(
                mRootView, !mForceDarkNavigationBarColor && mLightNavigationBar);
    }

<<<<<<< HEAD
    @SuppressLint("NewApi")
    private void updateNavigationBarColor(boolean forceShowDivider, boolean disableAnimation) {
        mForceDarkNavigationBarColor = mTabModelSelector.isIncognitoSelected() || mIsInFullscreen;

        final @ColorInt int newNavigationBarColor =
                applyCurrentScrimToColor(getNavigationBarColor(mForceDarkNavigationBarColor));
        if (!disableAnimation
                && mTargetNavigationBarColor != null
                && mTargetNavigationBarColor.equals(newNavigationBarColor)
                && mForceShowDivider == forceShowDivider) {
            return;
        }

        final @ColorInt int currentNavigationBarColor = mNavigationBarColor;
        final @ColorInt int newNavigationBarDividerColor =
                applyCurrentScrimToColor(
                        getNavigationBarDividerColor(
                                mForceDarkNavigationBarColor, forceShowDivider));

        mNavigationBarColor = newNavigationBarColor;
        mForceShowDivider = forceShowDivider;

        endNavigationBarColorAnimationIfRunning();
        if (areNavBarColorAnimationsEnabled() && !disableAnimation) {
            animateNavigationBarColor(currentNavigationBarColor, newNavigationBarColor);
        } else {
            mEdgeToEdgeSystemBarColorHelper.setNavigationBarColor(newNavigationBarColor);
            mEdgeToEdgeSystemBarColorHelper.setNavigationBarDividerColor(
                    newNavigationBarDividerColor);
        }
    }

    private void endNavigationBarColorAnimationIfRunning() {
        if (mNavbarColorTransitionAnimation != null
                && mNavbarColorTransitionAnimation.isRunning()) {
            mNavbarColorTransitionAnimation.end();
        }
    }

    private void animateNavigationBarColor(
            @ColorInt int currentNavigationBarColor, @ColorInt int newNavigationBarColor) {
        mNavbarColorTransitionAnimation =
                ValueAnimator.ofFloat(0, 1).setDuration(NAVBAR_COLOR_TRANSITION_DURATION_MS);
        mNavbarColorTransitionAnimation.setInterpolator(Interpolators.LINEAR_INTERPOLATOR);
        mTargetNavigationBarColor = newNavigationBarColor;

        mNavbarColorTransitionAnimation.addListener(
                new AnimatorListenerAdapter() {
                    @Override
                    public void onAnimationCancel(Animator animation) {
                        mTargetNavigationBarColor = null;
                    }

                    @Override
                    public void onAnimationEnd(Animator animation) {
                        mTargetNavigationBarColor = null;
                    }
                });
        mNavbarColorTransitionAnimation.addUpdateListener(
                (ValueAnimator animation) -> {
                    assert mTargetNavigationBarColor != null;

                    float fraction = animation.getAnimatedFraction();
                    int blendedColor =
                            ColorUtils.blendColorsMultiply(
                                    currentNavigationBarColor, mTargetNavigationBarColor, fraction);
                    int dividerColor =
                            mForceShowDivider
                                    ? getNavigationBarDividerColor(
                                            mForceDarkNavigationBarColor, mForceShowDivider)
                                    : blendedColor;
                    mEdgeToEdgeSystemBarColorHelper.setNavigationBarColor(blendedColor);
                    mEdgeToEdgeSystemBarColorHelper.setNavigationBarDividerColor(dividerColor);
                });
        mNavbarColorTransitionAnimation.start();
    }
=======
    @Override
    public void onEnterVr() {}
>>>>>>> chromium

    @SuppressLint("NewApi")
    private void updateNavigationBarColor() {
        boolean overviewVisible = mOverviewModeBehavior != null
                && mOverviewModeBehavior.overviewVisible() && !mOverviewModeHiding;

        boolean forceDarkNavigation;
        if (DeviceClassManager.enableAccessibilityLayout()
                || TabUiFeatureUtilities.isGridTabSwitcherEnabled(mRootView.getContext())) {
            forceDarkNavigation = mTabModelSelector.isIncognitoSelected();
        } else {
            forceDarkNavigation = mTabModelSelector.isIncognitoSelected() && !overviewVisible;
        }

        forceDarkNavigation &= !UiUtils.isSystemUiThemingDisabled();

        mForceDarkNavigationBarColor = forceDarkNavigation;
        final @ColorInt int navigationBarColor =
                getNavigationBarColor(mForceDarkNavigationBarColor);

        if (navigationBarColor == mNavigationBarColor) return;

        mNavigationBarColor = navigationBarColor;

        mWindow.setNavigationBarColor(mNavigationBarColor);
        setNavigationBarDividerColor();
        UiUtils.setNavigationBarIconColor(
                mRootView, !mForceDarkNavigationBarColor && mLightNavigationBar);
    }

<<<<<<< HEAD
    /**
     * Update the scrim color on the navigation bar.
     *
     * @param scrimColor The scrim color currently affecting the nav bar, including alpha.
     */
    public void setNavigationBarScrimColor(@ColorInt int scrimColor) {
        mCurrentScrimColor = scrimColor;
        @ColorInt
        int scrimNavigationBarColor =
                applyCurrentScrimToColor(getNavigationBarColor(mForceDarkNavigationBarColor));
        mEdgeToEdgeSystemBarColorHelper.setNavigationBarColor(scrimNavigationBarColor);
        mEdgeToEdgeSystemBarColorHelper.setNavigationBarDividerColor(
                applyCurrentScrimToColor(
                        getNavigationBarDividerColor(mForceDarkNavigationBarColor, false)));
    }

    @ColorInt
    private int getNavigationBarColor(boolean forceDarkNavigationBar) {
        if (mOverviewMode && mOverviewColorSupplier.get() != null) {
            return mOverviewColorSupplier.get();
        } else if (useBottomAttachedUiColor()) {
            return mBottomAttachedUiColor;
        } else if (useActiveTabColor()) {
            return mActiveTab.getBackgroundColor();
        } else {
            return forceDarkNavigationBar
                    ? mContext.getColor(R.color.toolbar_background_primary_dark)
                    : SemanticColorUtils.getBottomSystemNavColor(mContext);
        }
    }

    @VisibleForTesting
    @ColorInt
    int getNavigationBarDividerColor(boolean forceDarkNavigationBar, boolean forceShowDivider) {
        if (mOverviewMode && mOverviewColorSupplier.get() != null) {
            return mOverviewColorSupplier.get();
        } else if (!forceShowDivider && useBottomAttachedUiColor()) {
            return mBottomAttachedUiColor;
        } else if (!forceShowDivider && useActiveTabColor()) {
            return mActiveTab.getBackgroundColor();
        } else {
            return forceDarkNavigationBar
                    ? mContext.getColor(R.color.bottom_system_nav_divider_color_light)
                    : SemanticColorUtils.getBottomSystemNavDividerColor(mContext);
        }
    }

    private @ColorInt int applyCurrentScrimToColor(@ColorInt int color) {
        return ColorUtils.overlayColor(color, mCurrentScrimColor);
    }

    @VisibleForTesting
    void enableOverviewMode() {
        mOverviewMode = true;
    }

    @VisibleForTesting
    void disableOverviewMode() {
        mOverviewMode = false;
    }

    private boolean useBottomAttachedUiColor() {
        return ChromeFeatureList.sNavBarColorMatchesTabBackground.isEnabled()
                && mBottomAttachedUiColor != null;
    }

    private boolean useActiveTabColor() {
        return ChromeFeatureList.sNavBarColorMatchesTabBackground.isEnabled()
                && mLayoutManager != null
                && mLayoutManager.getActiveLayoutType() == LayoutType.BROWSING
                && mActiveTab != null;
    }

    void updateActiveTabForTesting() {
        updateActiveTab();
    }

    boolean getUseActiveTabColorForTesting() {
        return useActiveTabColor();
    }

    boolean getUseBottomAttachedUiColorForTesting() {
        return useBottomAttachedUiColor();
    }

    private static boolean areNavBarColorAnimationsEnabled() {
        return ChromeFeatureList.sNavBarColorMatchesTabBackground.isEnabled()
                && !isNavBarColorAnimationDisabled();
    }

    private static boolean isNavBarColorAnimationDisabled() {
        return ChromeFeatureList.sNavBarColorMatchesTabBackgroundColorAnimationDisabled.getValue();
    }

    @Override
    public int getNavigationBarColor() {
        return mNavigationBarColor;
    }

    @Override
    public void addObserver(Observer observer) {
        mObservers.addObserver(observer);
        observer.onNavigationBarColorChanged(mNavigationBarColor);
        observer.onNavigationBarDividerChanged(mNavigationBarColor);
    }

    @Override
    public void removeObserver(Observer observer) {
        mObservers.removeObserver(observer);
=======
    @SuppressLint("NewApi")
    private void setNavigationBarDividerColor() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            mWindow.setNavigationBarDividerColor(
                    getNavigationBarDividerColor(mForceDarkNavigationBarColor));
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P && (ContextUtils.getAppSharedPreferences().getBoolean("darken_websites_enabled", false) || ContextUtils.getAppSharedPreferences().getInt("ui_theme_setting", 0) == 2))
            mWindow.setNavigationBarDividerColor(Color.parseColor("#FF000000"));
    }

    /**
     * Update the scrim amount on the navigation bar.
     * @param fraction The scrim fraction in range [0, 1].
     */
    public void setNavigationBarScrimFraction(float fraction) {
        mNavigationBarScrimFraction = fraction;
        // https://forums.oneplus.com/threads/cannot-set-navigation-bar-color-to-pure-black-ff000000-via-values-xml.908719/
        // navigation bar cannot be set to pure black to protect the display
        if (ContextUtils.getAppSharedPreferences().getBoolean("darken_websites_enabled", false) || ContextUtils.getAppSharedPreferences().getInt("ui_theme_setting", 0) == 2)
        mWindow.setNavigationBarColor(Color.parseColor("#FF000000"));
        else
        mWindow.setNavigationBarColor(
                applyCurrentScrimToColor(getNavigationBarColor(mForceDarkNavigationBarColor)));
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            mWindow.setNavigationBarDividerColor(applyCurrentScrimToColor(
                    getNavigationBarDividerColor(mForceDarkNavigationBarColor)));
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P && (ContextUtils.getAppSharedPreferences().getBoolean("darken_websites_enabled", false) || ContextUtils.getAppSharedPreferences().getInt("ui_theme_setting", 0) == 2))
            mWindow.setNavigationBarDividerColor(Color.parseColor("#FF000000"));

        // Adjust the color of navigation bar icons based on color state of the navigation bar.
        if (MathUtils.areFloatsEqual(1f, fraction)) {
            UiUtils.setNavigationBarIconColor(mRootView, false);
        } else if (MathUtils.areFloatsEqual(0f, fraction)) {
            UiUtils.setNavigationBarIconColor(mRootView, true);
        }
    }

    private @ColorInt int getNavigationBarColor(boolean forceDarkNavigationBar) {
        return forceDarkNavigationBar
                ? mContext.getColor(R.color.toolbar_background_primary_dark)
                : SemanticColorUtils.getBottomSystemNavColor(mWindow.getContext());
    }

    private @ColorInt int getNavigationBarDividerColor(boolean forceDarkNavigationBar) {
        return ApiCompatibilityUtils.getColor(mResources,
                forceDarkNavigationBar ? R.color.bottom_system_nav_divider_color_light
                                       : R.color.bottom_system_nav_divider_color);
    }

    private @ColorInt int applyCurrentScrimToColor(@ColorInt int color) {
        // Apply a color overlay.
        float scrimColorAlpha = (mDefaultScrimColor >>> 24) / 255f;
        int scrimColorOpaque = mDefaultScrimColor & 0xFF000000;
        return ColorUtils.getColorWithOverlay(
                color, scrimColorOpaque, mNavigationBarScrimFraction * scrimColorAlpha, true);
>>>>>>> chromium
    }
}