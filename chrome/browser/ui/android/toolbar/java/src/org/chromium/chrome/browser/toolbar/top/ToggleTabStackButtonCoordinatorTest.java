// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.toolbar.top;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.any;
import static org.mockito.Mockito.doAnswer;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.reset;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import android.content.Context;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Captor;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;

import org.chromium.base.Callback;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.supplier.OneshotSupplierImpl;
import org.chromium.base.test.BaseRobolectricTestRunner;
<<<<<<< HEAD
=======
import org.chromium.chrome.browser.flags.ChromeFeatureList;
>>>>>>> chromium
import org.chromium.chrome.browser.layouts.LayoutStateProvider;
import org.chromium.chrome.browser.layouts.LayoutType;
import org.chromium.chrome.browser.toolbar.ToolbarIntentMetadata;
import org.chromium.chrome.browser.user_education.IPHCommand;
import org.chromium.chrome.browser.user_education.UserEducationHelper;
import org.chromium.components.feature_engagement.FeatureConstants;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * Unit tests for ToggleTabStackButtonCoordinator.
 */
@RunWith(BaseRobolectricTestRunner.class)
@Config(shadows = {ToggleTabStackButtonCoordinatorTest.ShadowChromeFeatureList.class})
public class ToggleTabStackButtonCoordinatorTest {
    private static final ToolbarIntentMetadata DEFAULT_INTENT_METADATA =
            new ToolbarIntentMetadata(/*isMainIntent*/ true, /*isIntentWithEffect*/ false);

<<<<<<< HEAD
    @Mock private Context mContext;
    @Mock private LayoutStateProvider mLayoutStateProvider;
    @Mock private ToggleTabStackButton mToggleTabStackButton;
    @Mock private android.content.res.Resources mResources;
    @Mock private UserEducationHelper mUserEducationHelper;
    @Mock private OnClickListener mOnClickListener;
    @Mock private OnLongClickListener mOnLongClickListener;
    @Mock private TabModelSelector mTabModelSelector;
    @Mock private TabModel mStandardTabModel;
    @Mock private TabModel mIncognitoTabModel;
=======
    @Implements(ChromeFeatureList.class)
    static class ShadowChromeFeatureList {
        static Map<String, String> sParamMap;
        @Implementation
        public static String getFieldTrialParamByFeature(String featureName, String paramName) {
            Assert.assertEquals("Wrong feature name", FeatureConstants.TAB_SWITCHER_BUTTON_FEATURE,
                    featureName);
            if (sParamMap.containsKey(paramName)) return sParamMap.get(paramName);
            return "";
        }
    }
>>>>>>> chromium

    @Mock
    private Context mContext;
    @Mock
    private LayoutStateProvider mLayoutStateProvider;
    @Mock
    private ToggleTabStackButton mToggleTabStackButton;
    @Mock
    private android.content.res.Resources mResources;
    @Mock
    private UserEducationHelper mUserEducationHelper;
    @Mock
    private Callback<Boolean> mSetNewTabButtonHighlightCallback;

    @Captor
    private ArgumentCaptor<IPHCommand> mIPHCommandCaptor;

<<<<<<< HEAD
    private final ObservableSupplierImpl<Boolean> mNotificationDotSupplier =
            new ObservableSupplierImpl<>(false);
=======
    private boolean mIsIncognito;
    private boolean mOverviewOpen;
    private final OneshotSupplierImpl<ToolbarIntentMetadata> mIntentMetadataOneshotSupplier =
            new OneshotSupplierImpl<>();
>>>>>>> chromium
    private final OneshotSupplierImpl<Boolean> mPromoShownOneshotSupplier =
            new OneshotSupplierImpl<>();

    private boolean mIsIncognito;
    private boolean mOverviewOpen;
    private Set<LayoutStateProvider.LayoutStateObserver> mLayoutStateObserverSet;

    private OneshotSupplierImpl<LayoutStateProvider> mLayoutSateProviderOneshotSupplier;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);

        when(mContext.getResources()).thenReturn(mResources);
        doAnswer(invocation -> mOverviewOpen)
                .when(mLayoutStateProvider)
                .isLayoutVisible(LayoutType.TAB_SWITCHER);
        doAnswer(invocation -> {
            mLayoutStateObserverSet.add(invocation.getArgument(0));
            return null;
        })
                .when(mLayoutStateProvider)
                .addObserver(any(LayoutStateProvider.LayoutStateObserver.class));
        doAnswer(invocation -> {
            mLayoutStateObserverSet.remove(invocation.getArgument(0));
            return null;
        })
                .when(mLayoutStateProvider)
                .removeObserver(any(LayoutStateProvider.LayoutStateObserver.class));

        mLayoutStateObserverSet = new HashSet<>();
        mLayoutSateProviderOneshotSupplier = new OneshotSupplierImpl<>();
<<<<<<< HEAD
        mTabModelSelectorSupplier = new ObservableSupplierImpl<>();
        mTabModelSelectorSupplier.set(mTabModelSelector);
        when(mTabModelSelector.getCurrentModel()).thenReturn(mStandardTabModel);
        when(mTabModelSelector.getModel(true)).thenReturn(mIncognitoTabModel);
        when(mStandardTabModel.isIncognitoBranded()).thenReturn(false);
        when(mIncognitoTabModel.isIncognitoBranded()).thenReturn(true);
        when(mIncognitoTabModel.getCount()).thenReturn(0);
=======
>>>>>>> chromium

        // Defaults most test cases expect, can be overridden by each test though.
        when(mToggleTabStackButton.isShown()).thenReturn(true);
        ShadowChromeFeatureList.sParamMap = new HashMap<>();
        mIsIncognito = false;
    }

    private ToggleTabStackButtonCoordinator newToggleTabStackButtonCoordinator(
            ToggleTabStackButton toggleTabStackButton) {
<<<<<<< HEAD
        ToggleTabStackButtonCoordinator coordinator =
                new ToggleTabStackButtonCoordinator(
                        mContext,
                        toggleTabStackButton,
                        mUserEducationHelper,
                        () -> mIsIncognito,
                        mPromoShownOneshotSupplier,
                        mLayoutSateProviderOneshotSupplier,
                        new ObservableSupplierImpl<>(),
                        mTabModelSelectorSupplier);
        coordinator.initializeWithNative(
                mOnClickListener,
                mOnLongClickListener,
                mTabCountSupplier,
                mArchivedTabCountSupplier,
                mNotificationDotSupplier,
                () -> {},
                () -> {});
        return coordinator;
=======
        // clang-format off
        return new ToggleTabStackButtonCoordinator(mContext, toggleTabStackButton,
                mUserEducationHelper, () -> mIsIncognito, mIntentMetadataOneshotSupplier,
                mPromoShownOneshotSupplier, mLayoutSateProviderOneshotSupplier,
                mSetNewTabButtonHighlightCallback, new ObservableSupplierImpl<>());
        // clang-format on
>>>>>>> chromium
    }

    private void showOverviewMode() {
        mOverviewOpen = true;
        for (LayoutStateProvider.LayoutStateObserver observer : mLayoutStateObserverSet) {
<<<<<<< HEAD
            observer.onStartedShowing(/* layoutType= */ LayoutType.TAB_SWITCHER);
=======
            observer.onStartedShowing(LayoutType.TAB_SWITCHER, /*showToolbar*/ false);
>>>>>>> chromium
        }
        for (LayoutStateProvider.LayoutStateObserver observer : mLayoutStateObserverSet) {
            observer.onFinishedShowing(LayoutType.TAB_SWITCHER);
        }
    }

    private void hideOverviewMode() {
        mOverviewOpen = false;
        for (LayoutStateProvider.LayoutStateObserver observer : mLayoutStateObserverSet) {
            observer.onStartedHiding(
                    LayoutType.TAB_SWITCHER, /*showToolbar*/ false, /*delayAnimation*/ false);
        }
        for (LayoutStateProvider.LayoutStateObserver observer : mLayoutStateObserverSet) {
            observer.onFinishedHiding(LayoutType.TAB_SWITCHER);
        }
    }

    private IPHCommand verifyIphShown() {
        verify(mUserEducationHelper).requestShowIPH(mIPHCommandCaptor.capture());
        reset(mUserEducationHelper);
        return mIPHCommandCaptor.getValue();
    }

    private void verifyIphNotShown() {
        verify(mUserEducationHelper, never()).requestShowIPH(any());
        reset(mUserEducationHelper);
    }



    private void verifyNtpButtonHighlightChanged(boolean expectedHighlight) {
        verify(mSetNewTabButtonHighlightCallback).onResult(expectedHighlight);
        reset(mSetNewTabButtonHighlightCallback);
    }

    private void verifyNtpButtonHighlightNotChanged() {
        verify(mSetNewTabButtonHighlightCallback, never()).onResult(any());
        reset(mSetNewTabButtonHighlightCallback);
    }

    @Test
    public void testOverviewBehaviorAvailableDuringConstruction() {
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        Assert.assertEquals("Should have 1 overview observer", 1, mLayoutStateObserverSet.size());

        toggleTabStackButtonCoordinator.destroy();
        Assert.assertTrue("Should have no overview observers", mLayoutStateObserverSet.isEmpty());
    }

    @Test
    public void testOverviewBehaviorAvailableAfterDestroy() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        toggleTabStackButtonCoordinator.destroy();

        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        Assert.assertTrue("Should have no overview observers", mLayoutStateObserverSet.isEmpty());
    }

    @Test
    public void testDestroyDuringIph() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        IPHCommand iphCommand = verifyIphShown();

        iphCommand.onShowCallback.run();
        Assert.assertEquals("Should have 1 overview observer", 1, mLayoutStateObserverSet.size());

        toggleTabStackButtonCoordinator.destroy();
        Assert.assertTrue("Should have no overview observers", mLayoutStateObserverSet.isEmpty());
    }

    @Test
    public void testIphAndOverviewHighlight() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        IPHCommand iphCommand = verifyIphShown();

        iphCommand.onShowCallback.run();
        assertEquals(true, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        showOverviewMode();
        assertEquals(true, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightChanged(true);

        iphCommand.onDismissCallback.run();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();
        hideOverviewMode();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightChanged(false);
    }

    @Test
    public void testDismissIphBeforeOverview() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        IPHCommand iphCommand = verifyIphShown();

        iphCommand.onShowCallback.run();
        assertEquals(true, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        iphCommand.onDismissCallback.run();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        showOverviewMode();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        hideOverviewMode();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();
    }

    @Test
    public void testOverviewModeEventsWithoutIph() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        showOverviewMode();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        hideOverviewMode();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();
    }

    @Test
    public void testIphWithNoPageLoad() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        verifyIphNotShown();
    }

    @Test
    public void testIphWithNoViewButton() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ null);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();
    }

    @Test
    public void testIphWithNoOverviewModeBehavior() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        IPHCommand iphCommand = verifyIphShown();

        iphCommand.onShowCallback.run();
        assertEquals(true, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        showOverviewMode();
        assertEquals(true, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        iphCommand.onDismissCallback.run();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();

        hideOverviewMode();
        assertEquals(false, toggleTabStackButtonCoordinator.mIphBeingShown);
        verifyNtpButtonHighlightNotChanged();
    }

    @Test
    public void testIphIncognito() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        mIsIncognito = true;
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();

        mIsIncognito = false;
<<<<<<< HEAD
        mCoordinator.handlePageLoadFinished();
        IphCommand iphCommand = verifyIphShown();
        assertEquals(
                "IPH feature is not as expected.",
                FeatureConstants.TAB_SWITCHER_BUTTON_FEATURE,
                iphCommand.featureName);
        assertEquals(
                "IPH string is not as expected.",
                R.string.iph_tab_switcher_text,
                iphCommand.stringId);
        assertEquals(
                "IPH string is not as expected.",
                R.string.iph_tab_switcher_accessibility_text,
                iphCommand.accessibilityStringId);
    }

    @Test
    public void testSwitchToIncognitoIphIsShown() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(
                        /* toggleTabStackButton= */ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mPromoShownOneshotSupplier.set(false);

        when(mIncognitoTabModel.getCount()).thenReturn(1);

        // Standard model with incognito tabs - show switch into incognito IPH.
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        IphCommand iphCommand = verifyIphShown();
        assertEquals(
                "IPH feature is not as expected.",
                FeatureConstants.TAB_SWITCHER_BUTTON_SWITCH_INCOGNITO,
                iphCommand.featureName);
        assertEquals(
                "IPH string is not as expected.",
                R.string.iph_tab_switcher_switch_into_incognito_text,
                iphCommand.stringId);
        assertEquals(
                "IPH string is not as expected.",
                R.string.iph_tab_switcher_switch_into_incognito_accessibility_text,
                iphCommand.accessibilityStringId);

        // Incognito model - show switch out of incognito IPH.
        when(mTabModelSelector.getCurrentModel()).thenReturn(mIncognitoTabModel);
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        iphCommand = verifyIphShown();
        assertEquals(
                "IPH feature is not as expected.",
                FeatureConstants.TAB_SWITCHER_BUTTON_SWITCH_INCOGNITO,
                iphCommand.featureName);
        assertEquals(
                "IPH string is not as expected.",
                R.string.iph_tab_switcher_switch_out_of_incognito_text,
                iphCommand.stringId);
        assertEquals(
                "IPH string is not as expected.",
                R.string.iph_tab_switcher_switch_out_of_incognito_accessibility_text,
                iphCommand.accessibilityStringId);
=======
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();
>>>>>>> chromium
    }

    @Test
    public void testIphIsShown() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(false);

        when(mToggleTabStackButton.isShown()).thenReturn(false);
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();

        when(mToggleTabStackButton.isShown()).thenReturn(true);
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();
    }

    @Test
    public void testIphMainIntentFalse() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(
                new ToolbarIntentMetadata(/*isMainIntent*/ false, /*isIntentWithEffect*/ false));
        mPromoShownOneshotSupplier.set(false);

        ShadowChromeFeatureList.sParamMap.put(
                HomeButtonCoordinator.MAIN_INTENT_FROM_LAUNCHER_PARAM_NAME, "");
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();

        ShadowChromeFeatureList.sParamMap.put(
                HomeButtonCoordinator.MAIN_INTENT_FROM_LAUNCHER_PARAM_NAME, "false");
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();

        ShadowChromeFeatureList.sParamMap.put(
                HomeButtonCoordinator.MAIN_INTENT_FROM_LAUNCHER_PARAM_NAME, "true");
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();
    }

    @Test
    public void testIphIntentWithEffectTrue() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(
                new ToolbarIntentMetadata(/*isMainIntent*/ true, /*isIntentWithEffect*/ true));
        mPromoShownOneshotSupplier.set(false);

        ShadowChromeFeatureList.sParamMap.put(
                HomeButtonCoordinator.INTENT_WITH_EFFECT_PARAM_NAME, "");
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();

        ShadowChromeFeatureList.sParamMap.put(
                HomeButtonCoordinator.INTENT_WITH_EFFECT_PARAM_NAME, "false");
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();

        ShadowChromeFeatureList.sParamMap.put(
                HomeButtonCoordinator.INTENT_WITH_EFFECT_PARAM_NAME, "true");
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();
    }

    @Test
    public void testIphShowedPromo() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        mPromoShownOneshotSupplier.set(true);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();
    }

    @Test
    public void testIphDelayedIntentMetadata() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mPromoShownOneshotSupplier.set(false);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();

        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();
    }

    @Test
    public void testIphDelayedPromoShown() {
        ToggleTabStackButtonCoordinator toggleTabStackButtonCoordinator =
                newToggleTabStackButtonCoordinator(/*view*/ mToggleTabStackButton);
        mLayoutSateProviderOneshotSupplier.set(mLayoutStateProvider);
        mIntentMetadataOneshotSupplier.set(DEFAULT_INTENT_METADATA);

        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphNotShown();

        mPromoShownOneshotSupplier.set(false);
        toggleTabStackButtonCoordinator.handlePageLoadFinished();
        verifyIphShown();
    }
}
