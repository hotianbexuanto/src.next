// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.toolbar.top;

import android.content.Context;
import androidx.annotation.VisibleForTesting;
import org.chromium.base.Callback;
import org.chromium.base.CallbackController;
import org.chromium.base.supplier.BooleanSupplier;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.chrome.browser.flags.FeatureParamUtils;
import org.chromium.chrome.browser.layouts.LayoutStateProvider;
import org.chromium.chrome.browser.layouts.LayoutType;
import org.chromium.chrome.browser.tab.CurrentTabObserver;
import org.chromium.chrome.browser.tab.EmptyTabObserver;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.toolbar.R;
import org.chromium.chrome.browser.toolbar.ToolbarIntentMetadata;
import org.chromium.chrome.browser.user_education.IPHCommandBuilder;
import org.chromium.chrome.browser.user_education.UserEducationHelper;
import org.chromium.components.browser_ui.widget.highlight.ViewHighlighter.HighlightParams;
import org.chromium.components.browser_ui.widget.highlight.ViewHighlighter.HighlightShape;
import org.chromium.components.feature_engagement.FeatureConstants;
import org.chromium.url.GURL;

/**
 * Root component for the tab switcher button on the toolbar. Intended to own the
 * {@link ToggleTabStackButton}, but currently it only manages some signals around the tab switcher
 * button.
 * TODO(https://crbug.com/871806): Finish converting HomeButton to MVC and move more logic into this
 * class.
 */
public class ToggleTabStackButtonCoordinator {
    @VisibleForTesting
    static final String MAIN_INTENT_FROM_LAUNCHER_PARAM_NAME = "isMainIntentFromLauncher";
    @VisibleForTesting
    static final String INTENT_WITH_EFFECT_PARAM_NAME = "intentWithEffect";

    private final CallbackController mCallbackController = new CallbackController();
    private final Context mContext;
    private final ToggleTabStackButton mToggleTabStackButton;
    private final UserEducationHelper mUserEducationHelper;
    private final BooleanSupplier mIsIncognitoSupplier;
    private final OneshotSupplier<ToolbarIntentMetadata> mIntentMetadataOneshotSupplier;
    private final OneshotSupplier<Boolean> mPromoShownOneshotSupplier;
    private final Callback<Boolean> mSetNewTabButtonHighlightCallback;
    private final CurrentTabObserver mPageLoadObserver;

    private LayoutStateProvider mLayoutStateProvider;
    private LayoutStateProvider.LayoutStateObserver mLayoutStateObserver;
    @VisibleForTesting
    boolean mIphBeingShown;

    /**
     * @param context The Android context used for various view operations.
     * @param toggleTabStackButton The concrete {@link ToggleTabStackButton} class for this MVC
     *         component.
     * @param userEducationHelper Helper class for showing in-product help text bubbles.
     * @param isIncognitoSupplier Supplier for whether the current tab is incognito.
     * @param intentMetadataOneshotSupplier Potentially delayed information about launching intent.
     * @param promoShownOneshotSupplier Potentially delayed information about if a promo was shown.
     * @param layoutStateProviderSupplier Allows observing layout state.
     * @param setNewTabButtonHighlightCallback Delegate to highlight the new tab button.
     * @param activityTabSupplier Supplier of the activity tab.
     */
    public ToggleTabStackButtonCoordinator(Context context,
            ToggleTabStackButton toggleTabStackButton, UserEducationHelper userEducationHelper,
            BooleanSupplier isIncognitoSupplier,
            OneshotSupplier<ToolbarIntentMetadata> intentMetadataOneshotSupplier,
            OneshotSupplier<Boolean> promoShownOneshotSupplier,
            OneshotSupplier<LayoutStateProvider> layoutStateProviderSupplier,
            Callback<Boolean> setNewTabButtonHighlightCallback,
            ObservableSupplier<Tab> activityTabSupplier) {
        mContext = context;
        mToggleTabStackButton = toggleTabStackButton;
        mUserEducationHelper = userEducationHelper;
        mIsIncognitoSupplier = isIncognitoSupplier;
        mIntentMetadataOneshotSupplier = intentMetadataOneshotSupplier;
        mPromoShownOneshotSupplier = promoShownOneshotSupplier;
        mSetNewTabButtonHighlightCallback = setNewTabButtonHighlightCallback;

        layoutStateProviderSupplier.onAvailable(
                mCallbackController.makeCancelable(this::setLayoutStateProvider));
<<<<<<< HEAD

        mPageLoadObserver =
                new CurrentTabObserver(
                        activityTabSupplier,
                        new EmptyTabObserver() {
                            @Override
                            public void onPageLoadFinished(Tab tab, GURL url) {
                                handlePageLoadFinished();
                            }
                        },
                        /* swapCallback= */ null);
    }

    /**
     * Post native initializations.
     *
     * @param onClickListener OnClickListener for view.
     * @param onLongClickListener OnLongClickListener for view.
     * @param tabCountSupplier Supplier for current tab count to show in view.
     * @param archivedTabCountSupplier Supplies the current archived tab count, used for displaying
     *     the associated IPH.
     * @param tabModelNotificationDotSupplier Supplies whether to show the notification dot on the
     *     tab switcher button.
     * @param archivedTabsIphShownCallback Callback for when the archived tabs iph is shown.
     * @param archivedTabsIphDismissedCallback Callback for when the archived tabs iph is dismissed.
     */
    public void initializeWithNative(
            OnClickListener onClickListener,
            OnLongClickListener onLongClickListener,
            ObservableSupplier<Integer> tabCountSupplier,
            @Nullable ObservableSupplier<Integer> archivedTabCountSupplier,
            ObservableSupplier<Boolean> tabModelNotificationDotSupplier,
            @NonNull Runnable archivedTabsIphShownCallback,
            @NonNull Runnable archivedTabsIphDismissedCallback) {
        mToggleTabStackButton.setOnClickListener(onClickListener);
        mToggleTabStackButton.setOnLongClickListener(onLongClickListener);
        mToggleTabStackButton.setSuppliers(
                tabCountSupplier, tabModelNotificationDotSupplier, mIsIncognitoSupplier);

        mArchivedTabCountSupplier = archivedTabCountSupplier;
        if (mArchivedTabCountSupplier != null) {
            mArchivedTabCountSupplier.addObserver(mArchivedTabCountObserver);
            mArchivedTabsIphShownCallback = archivedTabsIphShownCallback;
            mArchivedTabsIphDismissedCallback = archivedTabsIphDismissedCallback;
        }
=======
        mPageLoadObserver = new CurrentTabObserver(activityTabSupplier, new EmptyTabObserver() {
            @Override
            public void onPageLoadFinished(Tab tab, GURL url) {
                handlePageLoadFinished();
            }
        }, /*swapCallback=*/null);
>>>>>>> chromium
    }

    /** Cleans up callbacks and observers. */
    public void destroy() {
        mCallbackController.destroy();

        mPageLoadObserver.destroy();

        if (mLayoutStateProvider != null) {
            mLayoutStateProvider.removeObserver(mLayoutStateObserver);
            mLayoutStateProvider = null;
            mLayoutStateObserver = null;
        }
    }

    private void setLayoutStateProvider(LayoutStateProvider layoutStateProvider) {
        assert layoutStateProvider != null;
        assert mLayoutStateProvider == null : "the mLayoutStateProvider should set at most once.";

        mLayoutStateProvider = layoutStateProvider;
        mLayoutStateObserver = new LayoutStateProvider.LayoutStateObserver() {
            private boolean mHighlightedNewTabPageButton;

            @Override
            public void onStartedShowing(@LayoutType int layoutType, boolean showToolbar) {
                if (layoutType == LayoutType.TAB_SWITCHER && mIphBeingShown) {
                    mSetNewTabButtonHighlightCallback.onResult(true);
                    mHighlightedNewTabPageButton = true;
                }
            }

            @Override
            public void onStartedHiding(
                    @LayoutType int layoutType, boolean showToolbar, boolean delayAnimation) {
                if (layoutType == LayoutType.TAB_SWITCHER && mHighlightedNewTabPageButton) {
                    mSetNewTabButtonHighlightCallback.onResult(false);
                    mHighlightedNewTabPageButton = false;
                }
            }
        };
        mLayoutStateProvider.addObserver(mLayoutStateObserver);
    }

    @VisibleForTesting
    void handlePageLoadFinished() {
        if (mToggleTabStackButton == null || !mToggleTabStackButton.isShown()) return;
        if (mIsIncognitoSupplier.getAsBoolean()) return;
        if (mPromoShownOneshotSupplier.get() == null || mPromoShownOneshotSupplier.get()) return;

        ToolbarIntentMetadata intentMetadata = mIntentMetadataOneshotSupplier.get();
        if (intentMetadata == null) return;
        if (FeatureParamUtils.paramExistsAndDoesNotMatch(
                    FeatureConstants.TAB_SWITCHER_BUTTON_FEATURE,
                    MAIN_INTENT_FROM_LAUNCHER_PARAM_NAME,
                    intentMetadata.getIsMainIntentFromLauncher())) {
            return;
        }
        if (FeatureParamUtils.paramExistsAndDoesNotMatch(
                    FeatureConstants.TAB_SWITCHER_BUTTON_FEATURE, INTENT_WITH_EFFECT_PARAM_NAME,
                    intentMetadata.getIsIntentWithEffect())) {
            return;
        }

        HighlightParams params = new HighlightParams(HighlightShape.CIRCLE);
        params.setBoundsRespectPadding(true);
<<<<<<< HEAD
        IphCommandBuilder builder = null;
        if (ChromeFeatureList.sTabStripIncognitoMigration.isEnabled()
                && mTabModelSelectorSupplier.hasValue()) {
            TabModelSelector selector = mTabModelSelectorSupplier.get();
            // When in Incognito, show IPH to switch out.
            if (selector.getCurrentModel().isIncognitoBranded()) {
                builder =
                        new IphCommandBuilder(
                                mContext.getResources(),
                                FeatureConstants.TAB_SWITCHER_BUTTON_SWITCH_INCOGNITO,
                                R.string.iph_tab_switcher_switch_out_of_incognito_text,
                                R.string
                                        .iph_tab_switcher_switch_out_of_incognito_accessibility_text);
            } else if (selector.getModel(true).getCount() > 0) {
                // When in standard model with incognito tabs, show IPH to switch into incognito.
                builder =
                        new IphCommandBuilder(
                                mContext.getResources(),
                                FeatureConstants.TAB_SWITCHER_BUTTON_SWITCH_INCOGNITO,
                                R.string.iph_tab_switcher_switch_into_incognito_text,
                                R.string.iph_tab_switcher_switch_into_incognito_accessibility_text);
            }
        }

        if (builder == null
                && !mIsIncognitoSupplier.get()
                && mPromoShownOneshotSupplier.hasValue()
                && !mPromoShownOneshotSupplier.get()) {
            builder =
                    new IphCommandBuilder(
                            mContext.getResources(),
                            FeatureConstants.TAB_SWITCHER_BUTTON_FEATURE,
                            R.string.iph_tab_switcher_text,
                            R.string.iph_tab_switcher_accessibility_text);
        }

        if (builder != null) {
            mUserEducationHelper.requestShowIph(
                    builder.setAnchorView(mToggleTabStackButton)
                            .setOnShowCallback(this::handleShowCallback)
                            .setOnDismissCallback(this::handleDismissCallback)
                            .setHighlightParams(params)
                            .build());
        }
    }

    /**
     * Enables or disables the tab switcher ripple depending on whether we are in or out of the tab
     * switcher mode.
     */
    private void updateTabSwitcherButtonRipple() {
        Drawable drawable = mToggleTabStackButton.getBackground();
        // drawable may not be a RippleDrawable if IPH is showing. Ignore that scenario since
        // it is rare.
        if (drawable instanceof RippleDrawable) {
            // Force the ripple to end so the transition looks correct.
            drawable.jumpToCurrentState();
        }
=======
        mUserEducationHelper.requestShowIPH(new IPHCommandBuilder(mContext.getResources(),
                FeatureConstants.TAB_SWITCHER_BUTTON_FEATURE, R.string.iph_tab_switcher_text,
                R.string.iph_tab_switcher_accessibility_text)
                                                    .setAnchorView(mToggleTabStackButton)
                                                    .setOnShowCallback(this::handleShowCallback)
                                                    .setOnDismissCallback(
                                                            this::handleDismissCallback)
                                                    .setHighlightParams(params)
                                                    .build());
>>>>>>> chromium
    }

    private void handleShowCallback() {
        assert mToggleTabStackButton != null;
        mIphBeingShown = true;
    }

    private void handleDismissCallback() {
        assert mToggleTabStackButton != null;
        mIphBeingShown = false;
    }
}
