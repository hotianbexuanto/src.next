// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.omnibox.suggestions;

import android.content.Context;
import android.content.res.Resources;
import android.os.Handler;
import android.os.SystemClock;
import android.text.TextUtils;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.annotation.Px;
import androidx.annotation.StringRes;
import androidx.annotation.VisibleForTesting;

import org.chromium.base.ActivityState;
import org.chromium.base.Callback;
import org.chromium.base.jank_tracker.JankScenario;
import org.chromium.base.jank_tracker.JankTracker;
import org.chromium.base.metrics.RecordUserAction;
import org.chromium.base.supplier.Supplier;
<<<<<<< HEAD
import org.chromium.build.BuildConfig;
import org.chromium.build.annotations.NullMarked;
import org.chromium.chrome.browser.lifecycle.ActivityLifecycleDispatcher;
import org.chromium.chrome.browser.lifecycle.PauseResumeWithNativeObserver;
import org.chromium.chrome.browser.lifecycle.TopResumedActivityChangedObserver;
import org.chromium.chrome.browser.omnibox.DeferredIMEWindowInsetApplicationCallback;
=======
import org.chromium.chrome.browser.flags.ChromeFeatureList;
>>>>>>> chromium
import org.chromium.chrome.browser.omnibox.LocationBarDataProvider;
import org.chromium.chrome.browser.omnibox.OmniboxSuggestionType;
import org.chromium.chrome.browser.omnibox.R;
import org.chromium.chrome.browser.omnibox.UrlBarEditingTextStateProvider;
import org.chromium.chrome.browser.omnibox.styles.OmniboxResourceProvider;
import org.chromium.chrome.browser.omnibox.styles.OmniboxTheme;
import org.chromium.chrome.browser.omnibox.suggestions.AutocompleteController.OnSuggestionsReceivedListener;
import org.chromium.chrome.browser.omnibox.suggestions.basic.BasicSuggestionProcessor.BookmarkState;
import org.chromium.chrome.browser.omnibox.suggestions.mostvisited.ExploreIconProvider;
import org.chromium.chrome.browser.omnibox.voice.VoiceRecognitionHandler;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.share.ShareDelegate;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabSelectionType;
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelUtils;
import org.chromium.chrome.browser.tabmodel.TabWindowManager;
import org.chromium.components.metrics.OmniboxEventProtos.OmniboxEventProto.PageClassification;
import org.chromium.components.omnibox.AutocompleteMatch;
import org.chromium.components.omnibox.AutocompleteResult;
import org.chromium.components.query_tiles.QueryTile;
import org.chromium.content_public.browser.WebContents;
import org.chromium.ui.base.PageTransition;
import org.chromium.ui.modaldialog.DialogDismissalCause;
import org.chromium.ui.modaldialog.ModalDialogManager;
import org.chromium.ui.modaldialog.ModalDialogProperties;
import org.chromium.ui.modelutil.MVCListAdapter.ModelList;
import org.chromium.ui.modelutil.PropertyModel;
import org.chromium.ui.mojom.WindowOpenDisposition;
import org.chromium.url.GURL;

import java.util.List;
<<<<<<< HEAD
import java.util.Optional;

/** Handles updating the model state for the currently visible omnibox suggestions. */
@NullMarked
class AutocompleteMediator
        implements OnSuggestionsReceivedListener,
                OmniboxSuggestionsDropdown.GestureObserver,
                OmniboxSuggestionsDropdownScrollListener,
                TopResumedActivityChangedObserver,
                PauseResumeWithNativeObserver,
                SuggestionHost {
=======

/**
 * Handles updating the model state for the currently visible omnibox suggestions.
 */
class AutocompleteMediator implements OnSuggestionsReceivedListener,
                                      OmniboxSuggestionsDropdown.Observer, SuggestionHost {
    private static final int SUGGESTION_NOT_FOUND = -1;
>>>>>>> chromium
    private static final int SCHEDULE_FOR_IMMEDIATE_EXECUTION = -1;

    // Delay triggering the omnibox results upon key press to allow the location bar to repaint
    // with the new characters.
    private static final long OMNIBOX_SUGGESTION_START_DELAY_MS = 30;
    private static final int OMNIBOX_HISTOGRAMS_MAX_SUGGESTIONS = 10;

<<<<<<< HEAD
    private final Context mContext;
    private final AutocompleteDelegate mDelegate;
    private final UrlBarEditingTextStateProvider mUrlBarEditingTextProvider;
    private final PropertyModel mListPropertyModel;
    private final ModelList mSuggestionModels;
    private final Handler mHandler;
    private final LocationBarDataProvider mDataProvider;
    private final Supplier<ModalDialogManager> mModalDialogManagerSupplier;
    private final DropdownItemViewInfoListBuilder mDropdownViewInfoListBuilder;
    private final DropdownItemViewInfoListManager mDropdownViewInfoListManager;
    private final Callback<Tab> mBringTabToFrontCallback;
    private final Supplier<TabWindowManager> mTabWindowManagerSupplier;
    private final OmniboxActionDelegate mOmniboxActionDelegate;
    private final ActivityLifecycleDispatcher mLifecycleDispatcher;
    private final SuggestionsListAnimationDriver mAnimationDriver;
    private final WindowAndroid mWindowAndroid;
    private final DeferredIMEWindowInsetApplicationCallback
            mDeferredIMEWindowInsetApplicationCallback;
    private final OmniboxSuggestionsDropdownEmbedder mEmbedder;
    private final AutocompleteInput mAutocompleteInput = new AutocompleteInput();

    private Optional<AutocompleteController> mAutocomplete = Optional.empty();
    private Optional<AutocompleteResult> mAutocompleteResult = Optional.empty();
    private Optional<Runnable> mCurrentAutocompleteRequest = Optional.empty();
    private Optional<Runnable> mDeferredLoadAction = Optional.empty();
    private Optional<PropertyModel> mDeleteDialogModel = Optional.empty();
=======
    private final @NonNull Context mContext;
    private final @NonNull AutocompleteDelegate mDelegate;
    private final @NonNull UrlBarEditingTextStateProvider mUrlBarEditingTextProvider;
    private final @NonNull PropertyModel mListPropertyModel;
    private final @NonNull ModelList mSuggestionModels;
    private final @NonNull Handler mHandler;
    private final @NonNull LocationBarDataProvider mDataProvider;
    private final @NonNull Supplier<ModalDialogManager> mModalDialogManagerSupplier;
    private final @NonNull DropdownItemViewInfoListBuilder mDropdownViewInfoListBuilder;
    private final @NonNull DropdownItemViewInfoListManager mDropdownViewInfoListManager;
    private final @NonNull Callback<Tab> mBringTabToFrontCallback;
    private final @NonNull Supplier<TabWindowManager> mTabWindowManagerSupplier;
    private final @NonNull JankTracker mJankTracker;

    private @NonNull AutocompleteResult mAutocompleteResult = AutocompleteResult.EMPTY_RESULT;
    private @Nullable Runnable mCurrentAutocompleteRequest;
    private @Nullable Runnable mDeferredLoadAction;
>>>>>>> chromium

    private boolean mNativeInitialized;
    private AutocompleteController mAutocomplete;
    private long mUrlFocusTime;
<<<<<<< HEAD
    // When set, indicates an active omnibox session.
    private boolean mIsActive;
    // When set, specifies the system time of the most recent suggestion list request.
    private @Nullable Long mLastSuggestionRequestTime;
    // When set, specifies the time when the suggestion list was shown the first time.
    // Suggestions are refreshed several times per keystroke.
    private @Nullable Long mFirstSuggestionListModelCreatedTime;

    private @RefineActionUsage int mRefineActionUsage = RefineActionUsage.NOT_USED;
=======
    private boolean mEnableAdaptiveSuggestionsCount;
    private boolean mShouldCacheSuggestions;

    @IntDef({SuggestionVisibilityState.DISALLOWED, SuggestionVisibilityState.PENDING_ALLOW,
            SuggestionVisibilityState.ALLOWED})
    @Retention(RetentionPolicy.SOURCE)
    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    @interface SuggestionVisibilityState {
        int DISALLOWED = 0;
        int PENDING_ALLOW = 1;
        int ALLOWED = 2;
    }
    @SuggestionVisibilityState
    private int mSuggestionVisibilityState;

    @IntDef({EditSessionState.INACTIVE, EditSessionState.ACTIVATED_BY_USER_INPUT,
            EditSessionState.ACTIVATED_BY_QUERY_TILE})
    @Retention(RetentionPolicy.SOURCE)
    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    @interface EditSessionState {
        int INACTIVE = 0; // Omnibox is not being edited.
        int ACTIVATED_BY_USER_INPUT = 1; // The edit session is triggered by user input.
        int ACTIVATED_BY_QUERY_TILE = 2; // The edit session is triggered from query tile.
    }
    @EditSessionState
    private int mEditSessionState = EditSessionState.INACTIVE;
>>>>>>> chromium

    // The timestamp (using SystemClock.elapsedRealtime()) at the point when the user started
    // modifying the omnibox with new input.
    private long mNewOmniboxEditSessionTimestamp = -1;
    // Set at the end of the Omnibox interaction to indicate whether the user selected an item
    // from the list (true) or left the Omnibox and suggestions list with no action taken (false).
    private boolean mOmniboxFocusResultedInNavigation;

    /**
     * The text shown in the URL bar (user text + inline autocomplete) after the most recent set of
     * omnibox suggestions was received. When the user presses enter in the omnibox, this value is
     * compared to the URL bar text to determine whether the first suggestion is still valid.
     */
<<<<<<< HEAD
    private @Nullable String mUrlTextAfterSuggestionsReceived;

=======
    private String mUrlTextAfterSuggestionsReceived;
>>>>>>> chromium
    private boolean mShouldPreventOmniboxAutocomplete;
    private long mLastActionUpTimestamp;
    private boolean mIgnoreOmniboxItemSelection = true;

<<<<<<< HEAD
    // The number of touch down events sent to native during an omnibox session.
    private int mNumTouchDownEventForwardedInOmniboxSession;
    // The number of prefetches that were started from touch down events during an omnibox session.
    private int mNumPrefetchesStartedInOmniboxSession;
    // The suggestion that the last prefetch was started for within the current omnibox session.
    private Optional<AutocompleteMatch> mLastPrefetchStartedSuggestion = Optional.empty();

    // Observer watching for changes to the visual state of the omnibox suggestions.
    private Optional<AutocompleteCoordinator.OmniboxSuggestionsVisualStateObserver>
            mOmniboxSuggestionsVisualStateObserver = Optional.empty();

    public AutocompleteMediator(
            Context context,
            AutocompleteDelegate delegate,
            UrlBarEditingTextStateProvider textProvider,
            PropertyModel listPropertyModel,
            Handler handler,
            Supplier<ModalDialogManager> modalDialogManagerSupplier,
            Supplier<Tab> activityTabSupplier,
            @Nullable Supplier<ShareDelegate> shareDelegateSupplier,
            LocationBarDataProvider locationBarDataProvider,
            Callback<Tab> bringTabToFrontCallback,
            Supplier<TabWindowManager> tabWindowManagerSupplier,
            BookmarkState bookmarkState,
            OmniboxActionDelegate omniboxActionDelegate,
            ActivityLifecycleDispatcher lifecycleDispatcher,
            OmniboxSuggestionsDropdownEmbedder embedder,
            WindowAndroid windowAndroid,
            DeferredIMEWindowInsetApplicationCallback deferredIMEWindowInsetApplicationCallback) {
=======
    public AutocompleteMediator(@NonNull Context context, @NonNull AutocompleteDelegate delegate,
            @NonNull UrlBarEditingTextStateProvider textProvider,
            @NonNull PropertyModel listPropertyModel, @NonNull Handler handler,
            @NonNull Supplier<ModalDialogManager> modalDialogManagerSupplier,
            @NonNull Supplier<Tab> activityTabSupplier,
            @Nullable Supplier<ShareDelegate> shareDelegateSupplier,
            @NonNull LocationBarDataProvider locationBarDataProvider,
            @NonNull Callback<Tab> bringTabToFrontCallback,
            @NonNull Supplier<TabWindowManager> tabWindowManagerSupplier,
            @NonNull BookmarkState bookmarkState, @NonNull JankTracker jankTracker,
            @NonNull ExploreIconProvider exploreIconProvider) {
>>>>>>> chromium
        mContext = context;
        mDelegate = delegate;
        mUrlBarEditingTextProvider = textProvider;
        mListPropertyModel = listPropertyModel;
        mJankTracker = jankTracker;
        mModalDialogManagerSupplier = modalDialogManagerSupplier;
        mHandler = handler;
        mDataProvider = locationBarDataProvider;
        mBringTabToFrontCallback = bringTabToFrontCallback;
        mTabWindowManagerSupplier = tabWindowManagerSupplier;
        mSuggestionModels = mListPropertyModel.get(SuggestionListProperties.SUGGESTION_MODELS);
        mDropdownViewInfoListBuilder = new DropdownItemViewInfoListBuilder(
                activityTabSupplier, bookmarkState, exploreIconProvider);
        mDropdownViewInfoListBuilder.setShareDelegateSupplier(shareDelegateSupplier);
<<<<<<< HEAD
        mDropdownViewInfoListManager =
                new DropdownItemViewInfoListManager(mSuggestionModels, context);
        OmniboxResourceProvider.invalidateDrawableCache();
        mLifecycleDispatcher = lifecycleDispatcher;
        mLifecycleDispatcher.register(this);
        mDeferredIMEWindowInsetApplicationCallback = deferredIMEWindowInsetApplicationCallback;

        var pm = context.getPackageManager();
        var dialIntent = new Intent(Intent.ACTION_DIAL);
        OmniboxActionFactoryImpl.get()
                .setDialerAvailable(!pm.queryIntentActivities(dialIntent, 0).isEmpty());

        mAnimationDriver = initializeAnimationDriver(mWindowAndroid.getWindow());
=======
        mDropdownViewInfoListManager = new DropdownItemViewInfoListManager(mSuggestionModels);
>>>>>>> chromium
    }

    /**
     * Initialize the Mediator with default set of suggestion processors.
     */
    void initDefaultProcessors(Callback<List<QueryTile>> queryTileSuggestionCallback) {
        mDropdownViewInfoListBuilder.initDefaultProcessors(
                mContext, this, mDelegate, mUrlBarEditingTextProvider, queryTileSuggestionCallback);
    }

    /**
     * @return DropdownItemViewInfoListBuilder instance used to convert OmniboxSuggestions to list
     * of ViewInfos.
     */
    DropdownItemViewInfoListBuilder getDropdownItemViewInfoListBuilderForTest() {
        return mDropdownViewInfoListBuilder;
    }

    public void destroy() {
        if (mAutocomplete != null) {
            stopAutocomplete(false);
            mAutocomplete.removeOnSuggestionsReceivedListener(this);
        }
<<<<<<< HEAD
        mHandler.removeCallbacksAndMessages(null);
=======
>>>>>>> chromium
        mDropdownViewInfoListBuilder.destroy();
    }

    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    void setSuggestionVisibilityState(@SuggestionVisibilityState int state) {
        mSuggestionVisibilityState = state;
    }

    private @SuggestionVisibilityState int getSuggestionVisibilityState() {
        return mSuggestionVisibilityState;
    }

    /** @return The ModelList for currently shown suggestions. */
    ModelList getSuggestionModelListForTest() {
        return mSuggestionModels;
    }

    /**
     * Check if the suggestion is created from clipboard.
     *
     * @param suggestion The AutocompleteMatch to check.
     * @return Whether or not the suggestion is from clipboard.
     */
    private boolean isSuggestionFromClipboard(AutocompleteMatch suggestion) {
        return suggestion.getType() == OmniboxSuggestionType.CLIPBOARD_URL
                || suggestion.getType() == OmniboxSuggestionType.CLIPBOARD_TEXT
                || suggestion.getType() == OmniboxSuggestionType.CLIPBOARD_IMAGE;
    }

    /**
     * @return The number of current autocomplete suggestions.
     */
    public int getSuggestionCount() {
        return mAutocompleteResult.getSuggestionsList().size();
    }

    /**
     * Retrieve the omnibox suggestion at the specified index.  The index represents the ordering
     * in the underlying model.  The index does not represent visibility due to the current scroll
     * position of the list.
     *
     * @param index The index of the suggestion to fetch.
     * @return The suggestion at the given index.
     */
<<<<<<< HEAD
    public @Nullable AutocompleteMatch getSuggestionAt(int matchIndex) {
        return mAutocompleteResult.map(r -> r.getSuggestionsList().get(matchIndex)).orElse(null);
=======
    public AutocompleteMatch getSuggestionAt(int index) {
        return mAutocompleteResult.getSuggestionsList().get(index);
>>>>>>> chromium
    }

    /**
     * Sets the layout direction to be used for any new suggestion views.
     * @see View#setLayoutDirection(int)
     */
    void setLayoutDirection(int layoutDirection) {
        mDropdownViewInfoListManager.setLayoutDirection(layoutDirection);
    }

    /**
     * Specifies the visual state to be used by the suggestions.
     * @param useDarkColors Whether dark colors should be used for fonts and icons.
     * @param isIncognito Whether the UI is for incognito mode or not.
     */
<<<<<<< HEAD
    void updateVisualsForState(@BrandedColorScheme int brandedColorScheme) {
        mDropdownViewInfoListManager.setBrandedColorScheme(brandedColorScheme);
        mListPropertyModel.set(SuggestionListProperties.COLOR_SCHEME, brandedColorScheme);
        mOmniboxSuggestionsVisualStateObserver.ifPresent(
                (observer) ->
                        observer.onOmniboxSuggestionsBackgroundColorChanged(
                                OmniboxResourceProvider.getSuggestionsDropdownBackgroundColor(
                                        mContext, brandedColorScheme)));
=======
    void updateVisualsForState(boolean useDarkColors, boolean isIncognito) {
        @OmniboxTheme
        int omniboxTheme = OmniboxResourceProvider.getThemeFromDarkColorsAndIncognito(
                useDarkColors, isIncognito);
        mDropdownViewInfoListManager.setOmniboxTheme(omniboxTheme);
        mListPropertyModel.set(SuggestionListProperties.IS_INCOGNITO, isIncognito);
>>>>>>> chromium
    }

    /**
     * Show cached zero suggest results.
     * Enables Autocomplete subsystem to offer most recently presented suggestions in the event
     * where Native counterpart is not yet initialized.
     *
     * Note: the only supported page context right now is the ANDROID_SEARCH_WIDGET.
     */
    void startCachedZeroSuggest() {
<<<<<<< HEAD
        maybeServeCachedResult();
        postAutocompleteRequest(this::startZeroSuggest, SCHEDULE_FOR_IMMEDIATE_EXECUTION);
    }

    /** Save AutocompleteResult to Cache for early serving. */
    private void maybeCacheResult(AutocompleteResult result) {
        if (!mAutocompleteInput.isInCacheableContext() || result.isFromCachedResult()) {
            return;
        }

        CachedZeroSuggestionsManager.saveToCache(
                mAutocompleteInput.getPageClassification(), result);
    }

    /** Serve AutocompleteResult from Cache if Autocomplete is not yet initialized. */
    private void maybeServeCachedResult() {
        if (!mAutocompleteInput.isInCacheableContext() || mAutocomplete.isPresent()) {
            return;
        }
        onSuggestionsReceived(
                CachedZeroSuggestionsManager.readFromCache(
                        mAutocompleteInput.getPageClassification()),
                true);
=======
        if (mNativeInitialized) return;
        onSuggestionsReceived(CachedZeroSuggestionsManager.readFromCache(), "");
>>>>>>> chromium
    }

    /** Notify the mediator that a item selection is pending and should be accepted. */
    void allowPendingItemSelection() {
        mIgnoreOmniboxItemSelection = false;
    }

    /**
     * Signals that native initialization has completed.
     */
    void onNativeInitialized() {
        mNativeInitialized = true;

        mEnableAdaptiveSuggestionsCount =
                ChromeFeatureList.isEnabled(ChromeFeatureList.OMNIBOX_ADAPTIVE_SUGGESTIONS_COUNT);
        mDropdownViewInfoListBuilder.onNativeInitialized();

        runPendingAutocompleteRequests();
    }

<<<<<<< HEAD
    /**
     * Take necessary action to update the autocomplete system state and record metrics when the
     * omnibox session state changes.
     *
     * @param activated Whether the autocomplete session should be activated when the omnibox
     *     session state changes, {@code true} if this will be activated, {@code false} otherwise.
     */
    void onOmniboxSessionStateChange(boolean activated) {
        if (mIsActive == activated) return;
        mIsActive = activated;

        // Propagate the information about omnibox session state change to all the processors first.
        // Processors need this for accounting purposes.
        // The change information should be passed before Processors receive first
        // batch of suggestions, that is:
        // - before any call to startZeroSuggest() (when first suggestions are populated), and
        // - before stopAutocomplete() (when current suggestions are erased).
        mDropdownViewInfoListBuilder.onOmniboxSessionStateChange(activated);

        if (mAnimationDriver.isAnimationEnabled()) {
            mAnimationDriver.onOmniboxSessionStateChange(activated);
            if (activated) {
                mDelegate.setKeyboardVisibility(true, false);
            }
        }

        if (activated) {
            mAutocompleteInput.setPageClassification(mDataProvider.getPageClassification(false));
            mDeferredIMEWindowInsetApplicationCallback.attach(mWindowAndroid);
            dismissDeleteDialog(DialogDismissalCause.DISMISSED_BY_NATIVE);
            mRefineActionUsage = RefineActionUsage.NOT_USED;
=======
    /** @see org.chromium.chrome.browser.omnibox.UrlFocusChangeListener#onUrlFocusChange(boolean) */
    void onUrlFocusChange(boolean hasFocus) {
        if (hasFocus) {
>>>>>>> chromium
            mOmniboxFocusResultedInNavigation = false;
            mUrlFocusTime = System.currentTimeMillis();
            mJankTracker.startTrackingScenario(JankScenario.OMNIBOX_FOCUS);

            setSuggestionVisibilityState(SuggestionVisibilityState.PENDING_ALLOW);

            // Ask directly for zero-suggestions related to current input, unless the user is
            // currently visiting SearchActivity and the input is populated from the launch intent.
            // For SearchActivity, in most cases the input will be empty, triggering the same
            // response (starting zero suggestions), but if the Activity was launched with a QUERY,
            // then the query might point to a different URL than the reported Page, and the
            // suggestion would take the user to the DSE home page.
            // This is tracked by MobileStartup.LaunchCause / EXTERNAL_SEARCH_ACTION_INTENT
            // metric.
<<<<<<< HEAD
            String text = mUrlBarEditingTextProvider.getTextWithoutAutocomplete();
            onTextChanged(
                    text, /* isOnFocusContext= */ OmniboxFeatures.shouldRetainOmniboxOnFocus());
=======
            if (mDataProvider.getPageClassification(false)
                    != PageClassification.ANDROID_SEARCH_WIDGET_VALUE) {
                postAutocompleteRequest(this::startZeroSuggest, SCHEDULE_FOR_IMMEDIATE_EXECUTION);
            } else {
                String text = mUrlBarEditingTextProvider.getTextWithoutAutocomplete();
                onTextChanged(text, text);
            }
>>>>>>> chromium
        } else {
            mJankTracker.finishTrackingScenario(JankScenario.OMNIBOX_FOCUS);
            cancelAutocompleteRequests();
            SuggestionsMetrics.recordOmniboxFocusResultedInNavigation(
                    mOmniboxFocusResultedInNavigation);
<<<<<<< HEAD
            OmniboxMetrics.recordRefineActionUsage(mRefineActionUsage);
            OmniboxMetrics.recordSuggestionsListScrolled(
                    mAutocompleteInput.getPageClassification(), mSuggestionsListScrolled);

            // Reset the per omnibox session state of touch down prefetch.
            OmniboxMetrics.recordNumPrefetchesStartedInOmniboxSession(
                    mNumPrefetchesStartedInOmniboxSession);
            mNumTouchDownEventForwardedInOmniboxSession = 0;
            mNumPrefetchesStartedInOmniboxSession = 0;
            mLastPrefetchStartedSuggestion = Optional.empty();

            mNewOmniboxEditSessionTimestamp = -1;
            // Prevent any upcoming omnibox suggestions from showing once a URL is loaded (and as
            // a consequence the omnibox is unfocused), unless it is for hub search.
            // TODO(crbug.com/390011136): Find a better way to create a seamless animation when
            // exiting hub search that dismisses the URL bar and suggestions list together.
            if (mDataProvider.getPageClassification(/* isPrefetch= */ false)
                    != PageClassification.ANDROID_HUB_VALUE) {
                clearSuggestions();
            }
=======
            setSuggestionVisibilityState(SuggestionVisibilityState.DISALLOWED);
            mEditSessionState = EditSessionState.INACTIVE;
            mNewOmniboxEditSessionTimestamp = -1;
            // Prevent any upcoming omnibox suggestions from showing once a URL is loaded (and as
            // a consequence the omnibox is unfocused).
            hideSuggestions();
>>>>>>> chromium
        }

        mDropdownViewInfoListBuilder.onUrlFocusChange(hasFocus);
    }

    /**
     * @see
     * org.chromium.chrome.browser.omnibox.UrlFocusChangeListener#onUrlAnimationFinished(boolean)
     */
    void onUrlAnimationFinished(boolean hasFocus) {
<<<<<<< HEAD
        // mAnimationDriver has the responsibility of calling propagateOmniboxSessionStateChange if
        // it's present and currently active.
        if (hasFocus && mAnimationDriver.isAnimationEnabled()) {
            return;
        }
        propagateOmniboxSessionStateChange(hasFocus);
=======
        setSuggestionVisibilityState(hasFocus ? SuggestionVisibilityState.ALLOWED
                                              : SuggestionVisibilityState.DISALLOWED);
        updateOmniboxSuggestionsVisibility();
>>>>>>> chromium
    }

    /**
     * Updates the profile used for generating autocomplete suggestions.
     * @param profile The profile to be used.
     */
    void setAutocompleteProfile(Profile profile) {
        if (mAutocomplete != null) {
            stopAutocomplete(true);
            mAutocomplete.removeOnSuggestionsReceivedListener(this);
        }
        mAutocomplete = AutocompleteController.getForProfile(profile);

        mAutocomplete.addOnSuggestionsReceivedListener(this);
        mDropdownViewInfoListBuilder.setProfile(profile);

        runPendingAutocompleteRequests();
    }

    /**
     * Whether omnibox autocomplete should currently be prevented from generating suggestions.
     */
    void setShouldPreventOmniboxAutocomplete(boolean prevent) {
        mShouldPreventOmniboxAutocomplete = prevent;
    }

    /**
     * @see AutocompleteController#onVoiceResults(List)
     */
    void onVoiceResults(@Nullable List<VoiceRecognitionHandler.VoiceResult> results) {
        if (!mNativeInitialized || mAutocomplete == null) return;
        mAutocomplete.onVoiceResults(results);
    }

    /**
     * @return The current native pointer to the autocomplete results.
     * TODO(crbug.com/1138587): Figure out how to remove this.
     */
    long getCurrentNativeAutocompleteResult() {
        return mAutocompleteResult.getNativeObjectRef();
    }

    private static boolean isQueryEditingEnabled() {
        return ChromeFeatureList.isEnabled(ChromeFeatureList.QUERY_TILES_ENABLE_QUERY_EDITING);
    }

    /** Called when a query tile is selected by the user. */
    void onQueryTileSelected(QueryTile queryTile) {
        // For last level tile, start a search query, unless we want to let user have a chance to
        // edit the query.
        if (queryTile.children.isEmpty() && !isQueryEditingEnabled()) {
            launchSearchUrlForQueryTileSuggestion(queryTile);
            return;
        }

        // If the tile has sub-tiles, start a new request to the backend to get the new set
        // of tiles. Also set the tile text in omnibox.
        stopAutocomplete(false);
        String refineText = TextUtils.concat(queryTile.queryText, " ").toString();
        mDelegate.setOmniboxEditingText(refineText);

        mNewOmniboxEditSessionTimestamp = SystemClock.elapsedRealtime();
        mEditSessionState = EditSessionState.ACTIVATED_BY_QUERY_TILE;

        mAutocomplete.start(mDataProvider.getCurrentUrl(),
                mDataProvider.getPageClassification(mDelegate.didFocusUrlFromFakebox()),
                mUrlBarEditingTextProvider.getTextWithoutAutocomplete(),
                mUrlBarEditingTextProvider.getSelectionStart(),
                !mUrlBarEditingTextProvider.shouldAutocomplete(), queryTile.id, true);
    }

    /**
     * Triggered when the user selects one of the omnibox suggestions to navigate to.
     * @param suggestion The AutocompleteMatch which was selected.
     * @param position Position of the suggestion in the drop down view.
     * @param url The URL associated with the suggestion.
     */
    @Override
<<<<<<< HEAD
    public void onSuggestionClicked(AutocompleteMatch suggestion, int matchIndex, GURL url) {
        // Android hub should always switch to tab if one is available.
        // TODO(crbug.com/369438026): Remove this block once switch-to-tab is the default action.
        boolean isAndroidHub =
                mDataProvider.getPageClassification(/* isPrefetch= */ false)
                        == PageClassification.ANDROID_HUB_VALUE;
        if (isAndroidHub && suggestion.hasTabMatch() && maybeSwitchToTab(suggestion)) {
            // This bypasses the execution flow that captures histograms for all other cases.
            recordMetrics(suggestion, matchIndex, WindowOpenDisposition.SWITCH_TO_TAB);
            return;
        }

        mDeferredLoadAction =
                Optional.of(
                        () ->
                                loadUrlForOmniboxMatch(
                                        matchIndex,
                                        suggestion,
                                        url,
                                        mLastActionUpTimestamp,
                                        /* openInNewTab= */ false,
                                        true));

        // Note: Action will be reset when load is initiated.
        mAutocomplete.ifPresent(a -> mDeferredLoadAction.get().run());
    }

    /**
     * Triggered when the user touches down on a search suggestion.
     *
     * @param suggestion The AutocompleteMatch which was selected.
     * @param matchIndex Position of the suggestion in the drop down view.
     */
    @Override
    public void onSuggestionTouchDown(AutocompleteMatch suggestion, int matchIndex) {
        if (mAutocomplete.isEmpty()
                || mNumTouchDownEventForwardedInOmniboxSession
                        >= OmniboxFeatures.getMaxPrefetchesPerOmniboxSession()) {
            return;
        }
        mNumTouchDownEventForwardedInOmniboxSession++;

        var tab = mDataProvider.getTab();
        WebContents webContents = tab != null ? tab.getWebContents() : null;
        boolean wasPrefetchStarted =
                mAutocomplete
                        .map(a -> a.onSuggestionTouchDown(suggestion, matchIndex, webContents))
                        .orElse(false);
        if (wasPrefetchStarted) {
            mNumPrefetchesStartedInOmniboxSession++;
            mLastPrefetchStartedSuggestion = Optional.of(suggestion);
        }
    }

    @Override
    public void onOmniboxActionClicked(OmniboxAction action, int position) {
        if (action instanceof OmniboxAnswerAction omniboxAnswerAction) {
            Optional<AutocompleteMatch> associatedSuggestion =
                    mAutocompleteResult
                            .map(AutocompleteResult::getSuggestionsList)
                            .map((list) -> list.get(position));
            if (!associatedSuggestion.isPresent()) {
                return;
            }

            // Allow the action to record execution-related metrics before we navigate away.
            action.execute(mOmniboxActionDelegate);
            // onSuggestionClicked will post a call to finishInteraction, so we don't need to call
            // it immediately.
            loadUrlForOmniboxMatch(
                    0,
                    associatedSuggestion.get(),
                    mAutocomplete
                            .map(
                                    a ->
                                            a.getAnswerActionDestinationURL(
                                                    associatedSuggestion.get(),
                                                    mLastActionUpTimestamp,
                                                    omniboxAnswerAction))
                            .orElse(associatedSuggestion.get().getUrl()),
                    getElapsedTimeSinceInputChange(),
                    false,
                    false);
        } else {
            action.execute(mOmniboxActionDelegate);
            finishInteraction();
        }
=======
    public void onSuggestionClicked(
            @NonNull AutocompleteMatch suggestion, int position, @NonNull GURL url) {
        if (mAutocompleteResult.isFromCachedResult()
                && (!mNativeInitialized || mAutocomplete == null)) {
            // clang-format off
            mDeferredLoadAction = () -> loadUrlForOmniboxMatch(
                            position, suggestion, url, mLastActionUpTimestamp, true);
            // clang-format on
            return;
        }

        loadUrlForOmniboxMatch(position, suggestion, url, mLastActionUpTimestamp, true);
>>>>>>> chromium
    }

    /**
     * Triggered when the user selects to refine one of the omnibox suggestions.
     * @param suggestion The suggestion selected.
     */
    @Override
    public void onRefineSuggestion(AutocompleteMatch suggestion) {
        stopAutocomplete(false);
        boolean isSearchSuggestion = suggestion.isSearchSuggestion();
        String refineText = suggestion.getFillIntoEdit();
        if (isSearchSuggestion) refineText = TextUtils.concat(refineText, " ").toString();

        mDelegate.setOmniboxEditingText(refineText);
<<<<<<< HEAD
        onTextChanged(
                mUrlBarEditingTextProvider.getTextWithoutAutocomplete(),
                /* isOnFocusContext= */ false);

=======
        onTextChanged(mUrlBarEditingTextProvider.getTextWithoutAutocomplete(),
                mUrlBarEditingTextProvider.getTextWithAutocomplete());
>>>>>>> chromium
        if (isSearchSuggestion) {
            RecordUserAction.record("MobileOmniboxRefineSuggestion.Search");
        } else {
            RecordUserAction.record("MobileOmniboxRefineSuggestion.Url");
        }
    }

    @Override
<<<<<<< HEAD
    public void onSwitchToTab(AutocompleteMatch match, int matchIndex) {
        if (maybeSwitchToTab(match)) {
            recordMetrics(match, matchIndex, WindowOpenDisposition.SWITCH_TO_TAB);
        } else {
            onSuggestionClicked(match, matchIndex, match.getUrl());
=======
    public void onSwitchToTab(AutocompleteMatch suggestion, int position) {
        Tab tab = mAutocomplete.findMatchingTabWithUrl(suggestion.getUrl());
        if (tab == null || !mTabWindowManagerSupplier.hasValue()) {
            onSuggestionClicked(suggestion, position, suggestion.getUrl());
            return;
>>>>>>> chromium
        }

        // When invoked directly from a browser, we want to trigger switch to tab animation.
        // If invoked from other activities, ex. searchActivity, we do not need to trigger the
        // animation since Android will show the animation for switching apps.
        if (tab.getWindowAndroid().getActivityState() != ActivityState.STOPPED
                && tab.getWindowAndroid().getActivityState() != ActivityState.DESTROYED) {
            TabModel tabModel = mTabWindowManagerSupplier.get().getTabModelForTab(tab);
            assert tabModel != null;

            int tabIndex = TabModelUtils.getTabIndexById(tabModel, tab.getId());
            tabModel.setIndex(tabIndex, TabSelectionType.FROM_OMNIBOX);
        } else {
            mBringTabToFrontCallback.onResult(tab);
        }
        recordMetrics(position, WindowOpenDisposition.SWITCH_TO_TAB, suggestion);
    }

    @Override
    public void onGesture(boolean isGestureUp, long timestamp) {
        stopAutocomplete(false);
        if (isGestureUp) {
            mLastActionUpTimestamp = timestamp;
        }
    }

    /**
     * Triggered when the user long presses the omnibox suggestion.
     * @param suggestion The suggestion selected.
     * @param position The position of the suggestion.
     *
     * TODO(crbug.com/1136107): revisit the event propagation here to make sure we do not try to
     * execute an action before native is initialize.
     */
    @Override
<<<<<<< HEAD
    public void onDeleteMatch(AutocompleteMatch suggestion, String titleText) {
        showDeleteDialog(
                suggestion,
                titleText,
                () -> mAutocomplete.ifPresent(a -> a.deleteMatch(suggestion)));
    }

    /**
     * Triggered when the user long presses the omnibox suggestion element (eg. a tile).
     *
     * @param suggestion The suggestion selected.
     * @param titleText The title to display in the delete dialog.
     * @param elementIndex The element of the suggestion to be deleted.
     */
    @Override
    public void onDeleteMatchElement(
            AutocompleteMatch suggestion, String titleText, int elementIndex) {
        showDeleteDialog(
                suggestion,
                titleText,
                () -> mAutocomplete.ifPresent(a -> a.deleteMatchElement(suggestion, elementIndex)));
    }

    /** Terminate the interaction with the Omnibox. */
    @Override
    public void finishInteraction() {
        mDelegate.clearOmniboxFocus();
    }

    public void showDeleteDialog(
            AutocompleteMatch suggestion, String titleText, Runnable deleteAction) {
=======
    public void onSuggestionLongClicked(@NonNull AutocompleteMatch suggestion, int position) {
>>>>>>> chromium
        RecordUserAction.record("MobileOmniboxDeleteGesture");
        if (!suggestion.isDeletable()) return;

        ModalDialogManager manager = mModalDialogManagerSupplier.get();
        if (manager == null) {
            assert false : "No modal dialog manager registered for this activity.";
            return;
        }

        ModalDialogProperties.Controller dialogController = new ModalDialogProperties.Controller() {
            @Override
            public void onClick(PropertyModel model, int buttonType) {
                if (buttonType == ModalDialogProperties.ButtonType.POSITIVE) {
                    RecordUserAction.record("MobileOmniboxDeleteRequested");
                    mAutocomplete.deleteSuggestion(position);
                    manager.dismissDialog(model, DialogDismissalCause.POSITIVE_BUTTON_CLICKED);
                } else if (buttonType == ModalDialogProperties.ButtonType.NEGATIVE) {
                    manager.dismissDialog(model, DialogDismissalCause.NEGATIVE_BUTTON_CLICKED);
                }
            }

            @Override
            public void onDismiss(PropertyModel model, int dismissalCause) {}
        };

        Resources resources = mContext.getResources();
        @StringRes
        int dialogMessageId = R.string.omnibox_confirm_delete;
        if (isSuggestionFromClipboard(suggestion)) {
            dialogMessageId = R.string.omnibox_confirm_delete_from_clipboard;
        }

        PropertyModel model =
                new PropertyModel.Builder(ModalDialogProperties.ALL_KEYS)
                        .with(ModalDialogProperties.CONTROLLER, dialogController)
                        .with(ModalDialogProperties.TITLE, suggestion.getDisplayText())
                        .with(ModalDialogProperties.MESSAGE, resources, dialogMessageId)
                        .with(ModalDialogProperties.POSITIVE_BUTTON_TEXT, resources, R.string.ok)
                        .with(ModalDialogProperties.NEGATIVE_BUTTON_TEXT, resources,
                                R.string.cancel)
                        .with(ModalDialogProperties.CANCEL_ON_TOUCH_OUTSIDE, true)
                        .build();

        // Prevent updates to the shown omnibox suggestions list while the dialog is open.
        stopAutocomplete(false);
        manager.showDialog(model, ModalDialogManager.ModalDialogType.APP);
    }

    /**
     * Triggered when the user navigates to one of the suggestions without clicking on it.
     * @param text The text to be displayed in the Omnibox.
     */
    @Override
    public void setOmniboxEditingText(String text) {
        if (mIgnoreOmniboxItemSelection) return;
        mIgnoreOmniboxItemSelection = true;
        mDelegate.setOmniboxEditingText(text);
    }

    /**
     * Updates the URL we will navigate to from suggestion, if needed. This will update the search
     * URL to be of the corpus type if query in the omnibox is displayed and update aqs= parameter
     * on regular web search URLs.
     *
     * @param suggestion The chosen omnibox suggestion.
     * @param selectedIndex The index of the chosen omnibox suggestion.
     * @param url The URL associated with the suggestion to navigate to.
     * @param skipCheck Whether to skip an out of bounds check.
     * @return The url to navigate to.
     */
<<<<<<< HEAD
    private GURL updateSuggestionUrlIfNeeded(AutocompleteMatch suggestion, GURL url) {
        if (mAutocomplete.isEmpty()) return url;
        // TODO(crbug.com/40279214): this should exclude TILE variants when horizontal render group
        // is
        // ready.
        if (suggestion.getType() == OmniboxSuggestionType.TILE_NAVSUGGEST) {
=======
    private GURL updateSuggestionUrlIfNeeded(@NonNull AutocompleteMatch suggestion,
            int selectedIndex, @NonNull GURL url, boolean skipCheck) {
        if (!mNativeInitialized || mAutocomplete == null) return url;
        if (suggestion.getType() == OmniboxSuggestionType.VOICE_SUGGEST
                || suggestion.getType() == OmniboxSuggestionType.TILE_SUGGESTION
                || suggestion.getType() == OmniboxSuggestionType.TILE_NAVSUGGEST) {
>>>>>>> chromium
            return url;
        }

        int verifiedIndex = SUGGESTION_NOT_FOUND;
        if (!skipCheck) {
            verifiedIndex = findSuggestionInAutocompleteResult(suggestion, selectedIndex);
        }

        // If we do not have the suggestion as part of our results, skip the URL update.
        if (verifiedIndex == SUGGESTION_NOT_FOUND) return url;

        // TODO(mariakhomenko): Ideally we want to update match destination URL with new aqs
        // for query in the omnibox and voice suggestions, but it's currently difficult to do.
        GURL updatedUrl = mAutocomplete.updateMatchDestinationUrlWithQueryFormulationTime(
                verifiedIndex, getElapsedTimeSinceInputChange());

        return updatedUrl == null ? url : updatedUrl;
    }

    /**
     * Check if the supplied suggestion is still in the current model and return its index.
     *
     * This call should be used to confirm that model has not been changed ahead of an event being
     * called by all the methods that are dispatched rather than called directly.
     *
     * @param suggestion Suggestion to look for.
     * @param index Last known position of the suggestion.
     * @return Current index of the supplied suggestion, or SUGGESTION_NOT_FOUND if it is no longer
     *         part of the model.
     */
    @SuppressWarnings("ReferenceEquality")
    private int findSuggestionInAutocompleteResult(AutocompleteMatch suggestion, int position) {
        if (getSuggestionCount() > position && getSuggestionAt(position) == suggestion) {
            return position;
        }

        // Underlying omnibox results may have changed since the selection was made,
        // find the suggestion item, if possible.
        for (int index = 0; index < getSuggestionCount(); index++) {
            if (suggestion.equals(getSuggestionAt(index))) {
                return index;
            }
        }

        return SUGGESTION_NOT_FOUND;
    }

    /**
     * Notifies the autocomplete system that the text has changed that drives autocomplete and the
     * autocomplete suggestions should be updated.
<<<<<<< HEAD
     *
     * <p>The isOnFocusContext parameter signifies that the Zero Prefix Suggestions should be
     * retrieved even if the Omnibox content is not empty. This is relevant to Desktop mode Chrome,
     * where, if both physical keyboard and pointer device is attached, the Page URL should not be
     * cleared.
     *
     * @param textWithoutAutocomplete the text that does not include autocomplete information
     * @param isOnFocusContext whether Omnibox is currently gaining focus
     */
    public void onTextChanged(String textWithoutAutocomplete, boolean isOnFocusContext) {
        if (mShouldPreventOmniboxAutocomplete) return;

        // Always re-set the list's final state when we're about to request new suggestions.
        // This avoids a problem, where the property does not get an explicit update that the list
        // is final, which, in turn, may suppress certain functionality from getting invoked if the
        // subsequent push is immediately `final`.
        mListPropertyModel.set(SuggestionListProperties.LIST_IS_FINAL, false);

        mAutocompleteInput.setUserText(textWithoutAutocomplete);
        mIgnoreOmniboxItemSelection = true;
        cancelAutocompleteRequests();

        mAutocomplete.ifPresent(a -> a.resetSession());
        mNewOmniboxEditSessionTimestamp = SystemClock.elapsedRealtime();
        stopAutocomplete(false);

        if (mAutocompleteInput.isInZeroPrefixContext() || isOnFocusContext) {
            clearSuggestions();
            startCachedZeroSuggest();
=======
     */
    public void onTextChanged(String textWithoutAutocomplete, String textWithAutocomplete) {
        if (mShouldPreventOmniboxAutocomplete) return;

        mIgnoreOmniboxItemSelection = true;
        cancelAutocompleteRequests();

        if (mEditSessionState == EditSessionState.INACTIVE && mNativeInitialized
                && mAutocomplete != null) {
            mAutocomplete.resetSession();
            mNewOmniboxEditSessionTimestamp = SystemClock.elapsedRealtime();
            mEditSessionState = EditSessionState.ACTIVATED_BY_USER_INPUT;
        }

        stopAutocomplete(false);
        if (TextUtils.isEmpty(textWithoutAutocomplete)) {
            hideSuggestions();
            postAutocompleteRequest(this::startZeroSuggest, SCHEDULE_FOR_IMMEDIATE_EXECUTION);
>>>>>>> chromium
        } else {
            // There may be no tabs when searching form omnibox in overview mode. In that case,
            // LocationBarDataProvider.getCurrentUrl() returns NTP url.
            if (mDataProvider.hasTab() || mDataProvider.isInOverviewAndShowingOmnibox()) {
                boolean preventAutocomplete = !mUrlBarEditingTextProvider.shouldAutocomplete();
                int cursorPosition = mUrlBarEditingTextProvider.getSelectionStart()
                                == mUrlBarEditingTextProvider.getSelectionEnd()
                        ? mUrlBarEditingTextProvider.getSelectionStart()
                        : -1;
                int pageClassification =
                        mDataProvider.getPageClassification(mDelegate.didFocusUrlFromFakebox());
                String currentUrl = mDataProvider.getCurrentUrl();
                boolean isQueryStartedFromTiles = mDelegate.didFocusUrlFromQueryTiles()
                        || mEditSessionState == EditSessionState.ACTIVATED_BY_QUERY_TILE;

<<<<<<< HEAD
            postAutocompleteRequest(
                    () -> {
                        startMeasuringSuggestionRequestToUiModelTime();
                        mAutocomplete.ifPresent(
                                a ->
                                        a.start(
                                                currentUrl,
                                                mAutocompleteInput.getPageClassification(),
                                                textWithoutAutocomplete,
                                                cursorPosition,
                                                preventAutocomplete));
                    },
                    OMNIBOX_SUGGESTION_START_DELAY_MS);
=======
                postAutocompleteRequest(() -> {
                    mAutocomplete.start(currentUrl, pageClassification, textWithoutAutocomplete,
                            cursorPosition, preventAutocomplete, null, isQueryStartedFromTiles);
                }, OMNIBOX_SUGGESTION_START_DELAY_MS);
            }
>>>>>>> chromium
        }

        mDelegate.onUrlTextChanged();
    }

    @Override
<<<<<<< HEAD
    public void onSuggestionsReceived(AutocompleteResult autocompleteResult, boolean isFinal) {
        // Persist AutocompleteResult in cache even if the interaction has just finished.
        // This allows us to cache most up-to-date information even after navigation was initiated.
        if (isFinal && !autocompleteResult.getSuggestionsList().isEmpty()) {
            maybeCacheResult(autocompleteResult);
=======
    public void onSuggestionsReceived(
            AutocompleteResult autocompleteResult, String inlineAutocompleteText) {
        if (mShouldPreventOmniboxAutocomplete
                || getSuggestionVisibilityState() == SuggestionVisibilityState.DISALLOWED) {
            return;
>>>>>>> chromium
        }

        if (mShouldCacheSuggestions) {
            CachedZeroSuggestionsManager.saveToCache(autocompleteResult);
        }

        final List<AutocompleteMatch> newSuggestions = autocompleteResult.getSuggestionsList();
        String userText = mUrlBarEditingTextProvider.getTextWithoutAutocomplete();
        mUrlTextAfterSuggestionsReceived = userText + inlineAutocompleteText;

        if (!mAutocompleteResult.equals(autocompleteResult)) {
            mAutocompleteResult = autocompleteResult;
            List<DropdownItemViewInfo> viewInfoList =
                    mDropdownViewInfoListBuilder.buildDropdownViewInfoList(autocompleteResult);
            mDropdownViewInfoListManager.setSourceViewInfoList(
                    viewInfoList, autocompleteResult.getGroupsDetails());
            boolean defaultMatchIsSearch = true;
            if (!TextUtils.isEmpty(mUrlBarEditingTextProvider.getTextWithoutAutocomplete())
                    && !newSuggestions.isEmpty()) {
                defaultMatchIsSearch = newSuggestions.get(0).isSearchSuggestion();
            }
            mDelegate.onSuggestionsChanged(inlineAutocompleteText, defaultMatchIsSearch);
            updateOmniboxSuggestionsVisibility();
        }
    }

    @Override
    public void setGroupCollapsedState(int groupId, boolean state) {
        mDropdownViewInfoListManager.setGroupCollapsedState(groupId, state);
    }

    /**
     * Load the url corresponding to the typed omnibox text.
     * @param eventTime The timestamp the load was triggered by the user.
     */
    void loadTypedOmniboxText(long eventTime) {
        final String urlText = mUrlBarEditingTextProvider.getTextWithAutocomplete();
        cancelAutocompleteRequests();
<<<<<<< HEAD

        if (mAutocompleteInput.getPageClassification() == PageClassification.ANDROID_HUB_VALUE) {
            RecordUserAction.record("HubSearch.KeyboardEnterPressed");

            if (!OmniboxFeatures.sAndroidHubSearchEnterPerformsSearch.getValue()) {
                // For Hub Search, searching by keyboard typed query is not allowed so do nothing.
                return;
            }
        }

        if (mAutocomplete.isPresent()) {
            findMatchAndLoadUrl(urlText, eventTime, openInNewTab);
=======
        if (mNativeInitialized && mAutocomplete != null) {
            findMatchAndLoadUrl(urlText, eventTime);
>>>>>>> chromium
        } else {
            mDeferredLoadAction = () -> findMatchAndLoadUrl(urlText, eventTime);
        }
    }

    /**
     * Search for a suggestion with the same associated URL as the supplied one.
     *
     * @param urlText The URL text to search for.
     * @param eventTime The timestamp the load was triggered by the user.
     */
<<<<<<< HEAD
    private void findMatchAndLoadUrl(String urlText, long inputStart, boolean openInNewTab) {
=======
    private void findMatchAndLoadUrl(String urlText, long inputStart) {
>>>>>>> chromium
        AutocompleteMatch suggestionMatch;
        boolean inSuggestionList = true;

        if (getSuggestionCount() > 0
                && mUrlTextAfterSuggestionsReceived != null
                && urlText.trim().equals(mUrlTextAfterSuggestionsReceived.trim())) {
            // Common case: the user typed something, received suggestions, then pressed enter.
            // This triggers the Default Match.
            suggestionMatch = getSuggestionAt(0);
        } else {
            // Less common case: there are no valid omnibox suggestions. This can happen if the
            // user tapped the URL bar to dismiss the suggestions, then pressed enter. This can
            // also happen if the user presses enter before any suggestions have been received
            // from the autocomplete controller.
            if (!mNativeInitialized || mAutocomplete == null) return;
            suggestionMatch = mAutocomplete.classify(urlText, mDelegate.didFocusUrlFromFakebox());
            // Classify matches don't propagate to java, so skip the OOB check.
            inSuggestionList = false;

            // If urlText couldn't be classified, bail.
        }

        if (suggestionMatch == null) return;
        loadUrlForOmniboxMatch(
                0, suggestionMatch, suggestionMatch.getUrl(), inputStart, inSuggestionList);
    }

    /**
     * Loads the specified omnibox suggestion.
     *
     * @param matchPosition The position of the selected omnibox suggestion.
     * @param suggestion The suggestion selected.
     * @param url The URL to load.
     * @param inputStart The timestamp the input was started.
     * @param inVisibleSuggestionList Whether the suggestion is in the visible suggestion list.
     */
<<<<<<< HEAD
    private void loadUrlForOmniboxMatch(
            int matchIndex,
            AutocompleteMatch suggestion,
            GURL url,
            long inputStart,
            boolean openInNewTab,
            boolean shouldUpdateSuggestionUrl) {
        try (TraceEvent e = TraceEvent.scoped("AutocompleteMediator.loadUrlFromOmniboxMatch")) {
            OmniboxMetrics.recordFocusToOpenTime(System.currentTimeMillis() - mUrlFocusTime);
=======
    private void loadUrlForOmniboxMatch(int matchPosition, @NonNull AutocompleteMatch suggestion,
            @NonNull GURL url, long inputStart, boolean inVisibleSuggestionList) {
        SuggestionsMetrics.recordFocusToOpenTime(System.currentTimeMillis() - mUrlFocusTime);
>>>>>>> chromium

        // Clear the deferred site load action in case it executes. Reclaims a bit of memory.
        mDeferredLoadAction = null;

        mOmniboxFocusResultedInNavigation = true;
        url = updateSuggestionUrlIfNeeded(suggestion, matchPosition, url, !inVisibleSuggestionList);

        // loadUrl modifies AutocompleteController's state clearing the native
        // AutocompleteResults needed by onSuggestionsSelected. Therefore,
        // loadUrl should should be invoked last.
        int transition = suggestion.getTransition();
        int type = suggestion.getType();

<<<<<<< HEAD
            recordMetrics(suggestion, matchIndex, WindowOpenDisposition.CURRENT_TAB);
            if (type == OmniboxSuggestionType.URL_WHAT_YOU_TYPED
                    && mUrlBarEditingTextProvider.wasLastEditPaste()) {
                // It's important to use the page transition from the suggestion or we might end
                // up saving generated URLs as typed URLs, which would then pollute the subsequent
                // omnibox results. There is one special case where the suggestion text was pasted,
                // where we want the transition type to be LINK.
=======
        recordMetrics(matchPosition, WindowOpenDisposition.CURRENT_TAB, suggestion);
        if (((transition & PageTransition.CORE_MASK) == PageTransition.TYPED)
                && TextUtils.equals(url.getSpec(), mDataProvider.getCurrentUrl())) {
            // When the user hit enter on the existing permanent URL, treat it like a
            // reload for scoring purposes.  We could detect this by just checking
            // user_input_in_progress_, but it seems better to treat "edits" that end
            // up leaving the URL unchanged (e.g. deleting the last character and then
            // retyping it) as reloads too.  We exclude non-TYPED transitions because if
            // the transition is GENERATED, the user input something that looked
            // different from the current URL, even if it wound up at the same place
            // (e.g. manually retyping the same search query), and it seems wrong to
            // treat this as a reload.
            transition = PageTransition.RELOAD;
        } else if (type == OmniboxSuggestionType.URL_WHAT_YOU_TYPED
                && mUrlBarEditingTextProvider.wasLastEditPaste()) {
            // It's important to use the page transition from the suggestion or we might end
            // up saving generated URLs as typed URLs, which would then pollute the subsequent
            // omnibox results. There is one special case where the suggestion text was pasted,
            // where we want the transition type to be LINK.
>>>>>>> chromium

            transition = PageTransition.LINK;
        }

        if (suggestion.getType() == OmniboxSuggestionType.CLIPBOARD_IMAGE) {
            mDelegate.loadUrlWithPostData(url.getSpec(), transition, inputStart,
                    suggestion.getPostContentType(), suggestion.getPostData());
            return;
        }
        mDelegate.loadUrl(url.getSpec(), transition, inputStart);
    }

    /**
     * Make a zero suggest request if:
     * - The URL bar has focus.
     * - The the tab/overview is not incognito.
     * This method should not be called directly. Schedule execution using postAutocompleteRequest.
     */
    private void startZeroSuggest() {
        // Reset "edited" state in the omnibox if zero suggest is triggered -- new edits
        // now count as a new session.
        mNewOmniboxEditSessionTimestamp = -1;
        assert mNativeInitialized
            : "startZeroSuggest should be scheduled using postAutocompleteRequest";

<<<<<<< HEAD
        if (mDelegate.isUrlBarFocused()) {
            mAutocomplete.ifPresent(
                    a -> {
                        a.startZeroSuggest(
                                mUrlBarEditingTextProvider.getTextWithAutocomplete(),
                                mDataProvider.getCurrentGurl(),
                                mAutocompleteInput.getPageClassification(),
                                mDataProvider.getTitle());
                    });
=======
        if (mDelegate.isUrlBarFocused()
                && (mDataProvider.hasTab() || mDataProvider.isInOverviewAndShowingOmnibox())) {
            int pageClassification =
                    mDataProvider.getPageClassification(mDelegate.didFocusUrlFromFakebox());
            mShouldCacheSuggestions =
                    pageClassification == PageClassification.ANDROID_SEARCH_WIDGET_VALUE;
            mAutocomplete.startZeroSuggest(mUrlBarEditingTextProvider.getTextWithAutocomplete(),
                    mDataProvider.getCurrentUrl(), pageClassification, mDataProvider.getTitle());
>>>>>>> chromium
        }
    }

    /**
     * Update whether the omnibox suggestions are visible.
     */
<<<<<<< HEAD
    @VisibleForTesting
    void propagateOmniboxSessionStateChange(boolean isActive) {
        if (isActive) {
            mListPropertyModel.set(
                    SuggestionListProperties.CONTAINER_ALWAYS_VISIBLE,
                    mAutocompleteInput.getPageClassification()
                            == PageClassification.ANDROID_HUB_VALUE);
        }

        boolean wasActive = mListPropertyModel.get(SuggestionListProperties.OMNIBOX_SESSION_ACTIVE);
        mListPropertyModel.set(SuggestionListProperties.OMNIBOX_SESSION_ACTIVE, isActive);

        if (isActive != wasActive) {
            mIgnoreOmniboxItemSelection |= isActive; // Reset to default value.
            mOmniboxSuggestionsVisualStateObserver.ifPresent(
                    (observer) -> observer.onOmniboxSessionStateChange(isActive));
=======
    private void updateOmniboxSuggestionsVisibility() {
        boolean shouldBeVisible =
                getSuggestionVisibilityState() == SuggestionVisibilityState.ALLOWED
                && getSuggestionCount() > 0;
        boolean wasVisible = mListPropertyModel.get(SuggestionListProperties.VISIBLE);
        mListPropertyModel.set(SuggestionListProperties.VISIBLE, shouldBeVisible);
        if (shouldBeVisible && !wasVisible) {
            mIgnoreOmniboxItemSelection = true; // Reset to default value.
>>>>>>> chromium
        }
    }

    /**
     * Hides the omnibox suggestion popup.
     *
     * <p>
     * Signals the autocomplete controller to stop generating omnibox suggestions.
     *
     * @see AutocompleteController#stop(boolean)
     */
    private void hideSuggestions() {
        if (!mNativeInitialized || mAutocomplete == null) return;
        stopAutocomplete(true);

        mDropdownViewInfoListManager.clear();
        mAutocompleteResult = AutocompleteResult.EMPTY_RESULT;
        updateOmniboxSuggestionsVisibility();
    }

    /**
     * Signals the autocomplete controller to stop generating omnibox suggestions and cancels the
     * queued task to start the autocomplete controller, if any.
     *
     * @param clear Whether to clear the most recent autocomplete results.
     */
<<<<<<< HEAD
    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    void stopAutocomplete(boolean clear) {
        mAutocomplete.ifPresent(a -> a.stop(clear));
        // All suggestions are now removed.
        if (clear) mAutocompleteInput.reset();
        cancelAutocompleteRequests();
    }

    /** Trigger autocomplete for the given query. */
    void startAutocompleteForQuery(String query) {
=======
    private void stopAutocomplete(boolean clear) {
        if (mNativeInitialized && mAutocomplete != null) mAutocomplete.stop(clear);
        cancelAutocompleteRequests();
    }

    /**
     * Trigger autocomplete for the given query.
     */
    void startAutocompleteForQuery(String query) {
        if (!mNativeInitialized || mAutocomplete == null) return;
>>>>>>> chromium
        stopAutocomplete(false);
        if (mDataProvider.hasTab()) {
            mAutocomplete.start(mDataProvider.getCurrentUrl(),
                    mDataProvider.getPageClassification(false), query, -1, false, null, false);
        }
    }

    /**
     * Respond to Suggestion list height change and update list of presented suggestions.
     *
     * This typically happens as a result of soft keyboard being shown or hidden.
     *
     * @param newHeightPx New height of the suggestion list in pixels.
     */
    @Override
    public void onSuggestionDropdownHeightChanged(@Px int newHeight) {
        // Report the dropdown height whenever we intend to - or do show soft keyboard. This
        // addresses cases where hardware keyboard is attached to a device, or where user explicitly
        // called the keyboard back after we hid it.
        if (mDelegate.isKeyboardActive()) {
            mDropdownViewInfoListBuilder.setDropdownHeightWithKeyboardActive(newHeight);
        }
    }

    @Override
    public void onSuggestionDropdownScroll() {
        if (mEnableAdaptiveSuggestionsCount
                && mDropdownViewInfoListBuilder.hasFullyConcealedElements()) {
            mDelegate.setKeyboardVisibility(false, false);
        }
    }

    /**
     * Called whenever a navigation happens from the omnibox to record metrics about the user's
     * interaction with the omnibox.
     *
     * @param matchPosition The index of the suggestion that was selected.
     * @param disposition The window open disposition.
     * @param suggestion The suggestion selected.
     */
<<<<<<< HEAD
    private void recordMetrics(AutocompleteMatch match, int suggestionLine, int disposition) {
        if (mAutocompleteResult.isEmpty()) return;

        boolean autocompleteResultIsFromCache =
                mAutocompleteResult.map(r -> r.isFromCachedResult()).orElse(true);

        OmniboxMetrics.recordUsedSuggestionFromCache(autocompleteResultIsFromCache);
        OmniboxMetrics.recordTouchDownPrefetchResult(match, mLastPrefetchStartedSuggestion);
=======
    private void recordMetrics(int matchPosition, int disposition, AutocompleteMatch suggestion) {
        SuggestionsMetrics.recordUsedSuggestionFromCache(mAutocompleteResult.isFromCachedResult());
>>>>>>> chromium

        // Do not attempt to record other metrics for cached suggestions if the source of the list
        // is local cache. These suggestions do not have corresponding native objects and will fail
        // validation.
        if (mAutocompleteResult.isFromCachedResult()) return;

        String currentPageUrl = mDataProvider.getCurrentUrl();
        int pageClassification =
                mDataProvider.getPageClassification(mDelegate.didFocusUrlFromFakebox());
        long elapsedTimeSinceModified = getElapsedTimeSinceInputChange();
        int autocompleteLength = mUrlBarEditingTextProvider.getTextWithAutocomplete().length()
                - mUrlBarEditingTextProvider.getTextWithoutAutocomplete().length();
        WebContents webContents =
                mDataProvider.hasTab() ? mDataProvider.getTab().getWebContents() : null;

<<<<<<< HEAD
        mAutocomplete.ifPresent(
                a ->
                        a.onSuggestionSelected(
                                match,
                                suggestionLine,
                                disposition,
                                currentPageUrl,
                                mAutocompleteInput.getPageClassification(),
                                elapsedTimeSinceModified,
                                autocompleteLength,
                                webContents));
=======
        mAutocomplete.onSuggestionSelected(matchPosition, disposition, suggestion.getType(),
                currentPageUrl, pageClassification, elapsedTimeSinceModified, autocompleteLength,
                webContents);
>>>>>>> chromium
    }

    @Override
    public void onSuggestionDropdownOverscrolledToTop() {
        if (mEnableAdaptiveSuggestionsCount) {
            mDelegate.setKeyboardVisibility(true, false);
        }
    }

    /**
     * @return elapsed time (in milliseconds) since last input or -1 if user has chosen
     *         a zero-prefix suggestion.
     */
    private long getElapsedTimeSinceInputChange() {
        return mNewOmniboxEditSessionTimestamp > 0
                ? (SystemClock.elapsedRealtime() - mNewOmniboxEditSessionTimestamp)
                : -1;
    }

<<<<<<< HEAD
=======
    /**
     * Launches the search URL for the query tile suggestion.
     * @param queryTile The query tile user selected.
     */
    @SuppressWarnings("VisibleForTests")
    private void launchSearchUrlForQueryTileSuggestion(QueryTile queryTile) {
        SuggestionsMetrics.recordFocusToOpenTime(System.currentTimeMillis() - mUrlFocusTime);
        int position = -1;
        int suggestionCount = getSuggestionCount();
        AutocompleteMatch suggestion = null;
        // Find the suggestion position and hashCode.
        for (int i = 0; i < suggestionCount; ++i) {
            suggestion = getSuggestionAt(i);
            if (suggestion.getType() == OmniboxSuggestionType.TILE_SUGGESTION) {
                position = i;
                break;
            }
        }
        if (suggestion == null) return;
        GURL updatedUrl = mAutocomplete.updateMatchDestinationUrlWithQueryFormulationTime(position,
                getElapsedTimeSinceInputChange(), queryTile.queryText, queryTile.searchParams);

        // Abort if the Autocomplete has just become invalid/profile was destroyed.
        if (updatedUrl == null) return;

        // RecordMetrics has to be called before loadUrl, or otherwise the native AutocompleteResult
        // object will be reset and the suggestion will fail validation.
        recordMetrics(position, WindowOpenDisposition.CURRENT_TAB, suggestion);
        mDelegate.loadUrl(updatedUrl.getSpec(), PageTransition.LINK, mLastActionUpTimestamp);
    }

    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    @EditSessionState
    int getEditSessionStateForTest() {
        return mEditSessionState;
    }

>>>>>>> chromium
    /**
     * Schedule Autocomplete action for execution.
     * Each Autocomplete action posted here will cancel any previously posted Autocomplete action,
     * ensuring that the actions don't compete against each other. Any action scheduled for
     * execution before Native libraries are ready will be deferred.
     *
     * This call should only be used for regular suggest flows. Do not post arbitrary tasks here.
     *
     * @param action Autocomplete action to execute.
     * @param delayMillis The number of milliseconds by which the action should be delayed.
     *         Use SCHEDULE_FOR_IMMEDIATE_EXECUTION to post action at front of the message queue.
     */
<<<<<<< HEAD
    private void postAutocompleteRequest(Runnable action, long delayMillis) {
        assert !mIsExecutingAutocompleteAction : "Can't schedule conflicting autocomplete action";
        assert ThreadUtils.runningOnUiThread() : "Detected input from a non-UI thread. Test error?";

=======
    private void postAutocompleteRequest(@NonNull Runnable action, long delayMillis) {
>>>>>>> chromium
        cancelAutocompleteRequests();
        mCurrentAutocompleteRequest = new Runnable() {
            @Override
            public void run() {
                action.run();
                // Catch any AutocompleteRequests that post subsequent AutocompleteRequest.
                // Note: we have to explicitly instantiate a Runnable class, otherwise
                // 'this' will resolve into a parent class and Runnable.this won't work.
                assert mCurrentAutocompleteRequest == this;
                // Release completed Runnable.
                mCurrentAutocompleteRequest = null;
            }
        };
        // In the event we got Native Ready signal but no Profile yet (or the other way around),
        // delay execution of the Autocomplete request.
        if (!mNativeInitialized || mAutocomplete == null) return;
        if (delayMillis == SCHEDULE_FOR_IMMEDIATE_EXECUTION) {
            // TODO(crbug.com/1174855): Replace the following with postAtFrontOfQueue() and
            // correct any tests that expect data instantly.
            mCurrentAutocompleteRequest.run();
        } else {
            mHandler.postDelayed(mCurrentAutocompleteRequest, delayMillis);
        }
    }

    /**
     * Cancel any pending autocomplete actions.
     */
    private void cancelAutocompleteRequests() {
        mShouldCacheSuggestions = false;
        if (mCurrentAutocompleteRequest != null) {
            mHandler.removeCallbacks(mCurrentAutocompleteRequest);
            mCurrentAutocompleteRequest = null;
        }
    }

    /**
     * Execute any pending Autocomplete requests, if the Autocomplete subsystem is ready.
     */
    private void runPendingAutocompleteRequests() {
        if (!mNativeInitialized || mAutocomplete == null) return;

        if (mDeferredLoadAction != null) {
            // Re-schedule the load action for execution.
            mHandler.post(mDeferredLoadAction);
            mDeferredLoadAction = null;
            cancelAutocompleteRequests();
        } else if (mCurrentAutocompleteRequest != null) {
            // Re-schedule the autocomplete action for immediate execution.
            // These requests are not executed until Native libraries are loaded.
            mHandler.postAtFrontOfQueue(mCurrentAutocompleteRequest);
        }
<<<<<<< HEAD

        if (isFinal) {
            OmniboxMetrics.recordSuggestionRequestToModelTime(
                    /* isFirst= */ false, SystemClock.uptimeMillis() - mLastSuggestionRequestTime);
            stopMeasuringSuggestionRequestToUiModelTime();
        }
    }

    /** Cancel any measurements related to the time it takes to build Suggestions UI model. */
    private void stopMeasuringSuggestionRequestToUiModelTime() {
        mLastSuggestionRequestTime = null;
        mFirstSuggestionListModelCreatedTime = null;
    }

    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    SuggestionsListAnimationDriver initializeAnimationDriver(@Nullable Window window) {
        SuggestionsListAnimationDriver driver;
        if (mDelegate.isToolbarPositionCustomizationEnabled()) {
            int addedVerticalOffset =
                    mContext.getResources()
                            .getDimensionPixelOffset(
                                    R.dimen
                                            .omnibox_suggestion_list_bottom_animation_starting_vertical_offset);
            driver =
                    new UnsyncedSuggestionsListAnimationDriver(
                            mListPropertyModel,
                            () -> propagateOmniboxSessionStateChange(true),
                            mDelegate::isToolbarBottomAnchored,
                            addedVerticalOffset);
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R
                && OmniboxFeatures.shouldAnimateSuggestionsListAppearance()
                && window != null) {
            int addedVerticalOffset =
                    mContext.getResources()
                            .getDimensionPixelOffset(
                                    R.dimen
                                            .omnibox_suggestion_list_animation_added_vertical_offset);
            InsetObserver insetObserver = mWindowAndroid.getInsetObserver();
            assert insetObserver != null;
            driver =
                    new ImeSyncedSuggestionsListAnimationDriver(
                            insetObserver,
                            mListPropertyModel,
                            mEmbedder::getVerticalTranslationForAnimation,
                            () -> propagateOmniboxSessionStateChange(true),
                            addedVerticalOffset,
                            new Handler(),
                            window);
        } else {
            driver =
                    new SuggestionsListAnimationDriver() {
                        @Override
                        public void onOmniboxSessionStateChange(boolean active) {}

                        @Override
                        public boolean isAnimationEnabled() {
                            return false;
                        }
                    };
        }
        return driver;
    }

    /** Returns the current AutocompleteInput instance. */
    AutocompleteInput getAutocompleteInputForTesting() {
        return mAutocompleteInput;
    }

    /** Returns whether Omnibox session is active (the user is interacting with the Omnibox). */
    boolean isOmniboxSessionActiveForTesting() {
        return mIsActive;
    }

    /** Returns the current Animation Driver instance. */
    SuggestionsListAnimationDriver getAnimationDriverForTesting() {
        return mAnimationDriver;
    }

    @Override
    public void onTopResumedActivityChanged(boolean isTopResumedActivity) {
        // TODO(crbug.com/329702834): Ensuring showing Suggestions when activity resumes.
        if (!isTopResumedActivity) {
            // Careful: only clear suggestions after Omnibox session state changes to inactive.
            // This has an immediate impact on suggestions caching mechanism: if suggestions get
            // cleared before session state becomes inactive, we will cache empty result.
            mDelegate.clearOmniboxFocus();
        }
    }

    @Override
    public void onResumeWithNative() {}

    @Override
    public void onPauseWithNative() {
        // IMPORTANT:
        // Test builds often mock AutocompleteController. This mock object may be defunct when we
        // this code is reached. Do not execute this code as part of integration tests as it will
        // attempt to interact with dead mocks.
        if (BuildConfig.IS_FOR_TEST) return;

        // Detect the window focus has changed. This may be due to the user entering app switcher,
        // pressing the home screen, or, in windowed/split screen mode, user interacting with a
        // different app. This gives us enough head room to retrieve and cache relevant information.
        // Note: onPause and onUserLeaveHint happen much too late.
        if (!OmniboxFeatures.isJumpStartOmniboxEnabled()) return;

        // Abort early if Autocomplete has not initialized yet.
        if (mAutocomplete.isEmpty()) return;

        // Default page context to prefetch suggestions for.
        GURL pageUrl = UrlConstants.ntpGurl();
        int pageClass = PageClassification.INSTANT_NTP_WITH_OMNIBOX_AS_STARTING_FOCUS_VALUE;

        // Preserve current page context for Jump-start Omnibox feature.
        if (OmniboxFeatures.sJumpStartOmniboxCoverRecentlyVisitedPage.getValue()) {
            pageUrl = mDataProvider.getCurrentGurl();
            pageClass = mDataProvider.getPageClassification(false);

            var currentContext = CachedZeroSuggestionsManager.readJumpStartContext();
            if (currentContext.pageClass == pageClass && currentContext.url.equals(pageUrl)) {
                return;
            }

            // The context has changed. Avoid showing stale suggestions.
            CachedZeroSuggestionsManager.saveJumpStartContext(
                    new CachedZeroSuggestionsManager.JumpStartContext(pageUrl, pageClass));
            CachedZeroSuggestionsManager.eraseCachedSuggestionsByPageClass(pageClass);
        }

        // Retrieve suggestions related to the most recently visited page.
        // This is a best-effort action and may not always work (e.g. if Chrome gets killed or
        // swiped away before we manage to retrieve and persist the information).
        mAutocomplete.get().startZeroSuggest("", pageUrl, pageClass, mDataProvider.getTitle());
=======
>>>>>>> chromium
    }
}
