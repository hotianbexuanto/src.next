// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tasks.tab_management;

<<<<<<< HEAD
import static org.chromium.chrome.browser.flags.ChromeFeatureList.DATA_SHARING;

import android.app.Activity;
=======
import static org.chromium.chrome.browser.tasks.tab_management.TabSwitcherMediator.INITIAL_SCROLL_INDEX_OFFSET_GTS;

import android.content.ComponentName;
>>>>>>> chromium
import android.content.Context;
import android.content.res.ColorStateList;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;
import androidx.appcompat.content.res.AppCompatResources;

import org.chromium.base.Callback;
import org.chromium.base.metrics.RecordUserAction;
import org.chromium.base.supplier.Supplier;
<<<<<<< HEAD
import org.chromium.base.task.PostTask;
import org.chromium.base.task.TaskTraits;
import org.chromium.chrome.browser.collaboration.CollaborationServiceFactory;
import org.chromium.chrome.browser.collaboration.messaging.MessagingBackendServiceFactory;
import org.chromium.chrome.browser.data_sharing.DataSharingServiceFactory;
import org.chromium.chrome.browser.data_sharing.DataSharingTabManager;
import org.chromium.chrome.browser.data_sharing.ui.shared_image_tiles.SharedImageTilesCoordinator;
import org.chromium.chrome.browser.feedback.HelpAndFeedbackLauncher;
import org.chromium.chrome.browser.feedback.HelpAndFeedbackLauncherFactory;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.profiles.Profile;
=======
import org.chromium.chrome.browser.share.ChromeShareExtras;
import org.chromium.chrome.browser.share.ShareDelegate;
import org.chromium.chrome.browser.share.ShareDelegate.ShareOrigin;
>>>>>>> chromium
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabCreationState;
import org.chromium.chrome.browser.tab.TabLaunchType;
import org.chromium.chrome.browser.tab.TabSelectionType;
<<<<<<< HEAD
import org.chromium.chrome.browser.tab_group_sync.TabGroupSyncServiceFactory;
import org.chromium.chrome.browser.tab_ui.RecyclerViewPosition;
import org.chromium.chrome.browser.tab_ui.TabUiThemeUtils;
import org.chromium.chrome.browser.tabmodel.TabGroupModelFilter;
import org.chromium.chrome.browser.tabmodel.TabGroupModelFilterObserver;
import org.chromium.chrome.browser.tabmodel.TabGroupTitleUtils;
import org.chromium.chrome.browser.tabmodel.TabGroupUtils;
=======
import org.chromium.chrome.browser.tab.state.CriticalPersistedTabData;
import org.chromium.chrome.browser.tabmodel.TabCreatorManager;
>>>>>>> chromium
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelFilter;
import org.chromium.chrome.browser.tabmodel.TabModelObserver;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tabmodel.TabModelSelectorObserver;
import org.chromium.chrome.browser.tasks.tab_groups.TabGroupModelFilter;
import org.chromium.chrome.browser.ui.messages.snackbar.Snackbar;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.tab_ui.R;
<<<<<<< HEAD
import org.chromium.components.browser_ui.desktop_windowing.AppHeaderState;
import org.chromium.components.browser_ui.desktop_windowing.DesktopWindowStateManager;
import org.chromium.components.browser_ui.desktop_windowing.DesktopWindowStateManager.AppHeaderObserver;
import org.chromium.components.browser_ui.styles.SemanticColorUtils;
import org.chromium.components.browser_ui.widget.gesture.BackPressHandler;
import org.chromium.components.collaboration.CollaborationService;
import org.chromium.components.collaboration.messaging.CollaborationEvent;
import org.chromium.components.collaboration.messaging.MessagingBackendService;
import org.chromium.components.collaboration.messaging.MessagingBackendService.PersistentMessageObserver;
import org.chromium.components.collaboration.messaging.PersistentMessage;
import org.chromium.components.collaboration.messaging.PersistentNotificationType;
import org.chromium.components.data_sharing.DataSharingService;
import org.chromium.components.data_sharing.GroupMember;
import org.chromium.components.data_sharing.member_role.MemberRole;
import org.chromium.components.embedder_support.util.UrlConstants;
import org.chromium.components.tab_group_sync.EitherId.EitherGroupId;
import org.chromium.components.tab_group_sync.LocalTabGroupId;
import org.chromium.components.tab_group_sync.TabGroupSyncService;
import org.chromium.components.tab_groups.TabGroupColorId;
=======
import org.chromium.components.browser_ui.share.ShareParams;
import org.chromium.components.browser_ui.widget.gesture.BackPressHandler;
import org.chromium.components.embedder_support.util.UrlConstants;
import org.chromium.content_public.browser.LoadUrlParams;
>>>>>>> chromium
import org.chromium.ui.KeyboardVisibilityDelegate;
import org.chromium.ui.modelutil.PropertyModel;

import java.util.List;

import org.chromium.chrome.browser.homepage.HomepageManager;

/**
 * A mediator for the TabGridDialog component, responsible for communicating
 * with the components' coordinator as well as managing the business logic
 * for dialog show/hide.
 */
<<<<<<< HEAD
public class TabGridDialogMediator
        implements SnackbarManager.SnackbarController,
                TabGridDialogView.VisibilityListener,
                TabGridItemTouchHelperCallback.OnLongPressTabItemEventListener,
                AppHeaderObserver {
    @VisibleForTesting static final String SHOW_SEND_FEEDBACK_PARAM = "show_send_feedback";
    @VisibleForTesting static final String SHARE_FEEDBACK_CATEGORY_SUFFIX = ".tab_group_share";

    /** Defines an interface for a {@link TabGridDialogMediator} to control dialog. */
    interface DialogController extends BackPressHandler {
=======
public class TabGridDialogMediator implements SnackbarManager.SnackbarController {
    /**
     * Defines an interface for a {@link TabGridDialogMediator} to control dialog.
     */
    interface DialogController {
>>>>>>> chromium
        /**
         * Handles a reset event originated from {@link TabGridDialogMediator} and {@link
         * TabSwitcherMediator}.
         *
         * @param tabs List of Tabs to reset.
         */
        void resetWithListOfTabs(@Nullable List<Tab> tabs);

        /**
         * Hide the TabGridDialog
         * @param showAnimation Whether to show an animation when hiding the dialog.
         */
        void hideDialog(boolean showAnimation);

        /**
         * Prepare the TabGridDialog before show.
         */
        void prepareDialog();

        /**
         * @return Whether or not the TabGridDialog consumed the event.
         */
        boolean handleBackPressed();

        /**
         * @return Whether the TabGridDialog is visible.
         */
        boolean isVisible();
    }

    /**
     * Defines an interface for a {@link TabGridDialogMediator} to get the source {@link View}
     * in order to prepare show/hide animation.
     */
    interface AnimationSourceViewProvider {
        /**
         * Provide {@link View} of the source item to setup the animation.
         *
         * @param tabId The id of the tab whose position is requested.
         * @return The source {@link View} used to setup the animation.
         */
        View getAnimationSourceViewForTab(int tabId);
    }

<<<<<<< HEAD
    private final ValueChangedCallback<TabGroupModelFilter> mOnTabGroupModelFilterChanged =
            new ValueChangedCallback<>(this::onTabGroupModelFilterChanged);
    private final Callback<String> mOnCollaborationIdChanged = this::onCollaborationIdChanged;
    private final Callback<Integer> mOnGroupSharedStateChanged = this::onGroupSharedStateChanged;
    private final Callback<List<GroupMember>> mOnGroupMembersChanged = this::onGroupMembersChanged;
    private final Activity mActivity;
    private final DialogController mDialogController;
    private final PropertyModel mModel;
    private final ObservableSupplier<TabGroupModelFilter> mCurrentTabGroupModelFilterSupplier;
    private final @Nullable TabSwitcherResetHandler mTabSwitcherResetHandler;
    private final Supplier<RecyclerViewPosition> mRecyclerViewPositionSupplier;
    private final AnimationSourceViewProvider mAnimationSourceViewProvider;
    private final DialogHandler mTabGridDialogHandler;
    private final @Nullable SnackbarManager mSnackbarManager;
    private final @Nullable SharedImageTilesCoordinator mSharedImageTilesCoordinator;
    private final DataSharingTabManager mDataSharingTabManager;
    private final String mComponentName;
    private final Runnable mShowColorPickerPopupRunnable;
    private final ActionConfirmationManager mActionConfirmationManager;
    private final ModalDialogManager mModalDialogManager;
    private final Profile mOriginalProfile;
    private final @Nullable TabGroupSyncService mTabGroupSyncService;
    private final @Nullable DataSharingService mDataSharingService;
    private final @NonNull CollaborationService mCollaborationService;
    private final @Nullable TransitiveSharedGroupObserver mTransitiveSharedGroupObserver;
    private final @Nullable MessagingBackendService mMessagingBackendService;
    private final @Nullable MessagingBackendService.PersistentMessageObserver
            mPersistentMessageObserver;
    private final TabModelObserver mTabModelObserver;
    private final TabGroupModelFilterObserver mTabGroupModelFilterObserver;
=======
    private final Context mContext;
    private final PropertyModel mModel;
    private final TabModelSelector mTabModelSelector;
    private final TabModelSelectorObserver mTabModelSelectorObserver;
    private final TabModelObserver mTabModelObserver;
    private final TabCreatorManager mTabCreatorManager;
    private final DialogController mDialogController;
    private final TabSwitcherMediator.ResetHandler mTabSwitcherResetHandler;
    private final AnimationSourceViewProvider mAnimationSourceViewProvider;
    private final DialogHandler mTabGridDialogHandler;
    private final Supplier<ShareDelegate> mShareDelegateSupplier;
>>>>>>> chromium
    private final Runnable mScrimClickRunnable;
    private final String mComponentName;

<<<<<<< HEAD
    private int mCurrentTabId = Tab.INVALID_TAB_ID;
    private TabGridDialogMenuCoordinator mTabGridDialogMenuCoordinator;
    private Supplier<TabListEditorController> mTabListEditorControllerSupplier;
    private boolean mTabListEditorSetup;
=======
    private TabGroupTitleEditor mTabGroupTitleEditor;
    private TabSelectionEditorCoordinator
            .TabSelectionEditorController mTabSelectionEditorController;
>>>>>>> chromium
    private KeyboardVisibilityDelegate.KeyboardVisibilityListener mKeyboardVisibilityListener;
    private int mCurrentTabId = Tab.INVALID_TAB_ID;
    private boolean mIsUpdatingTitle;
    private String mCurrentGroupModifiedTitle;
    private Callback<Integer> mToolbarMenuCallback;

<<<<<<< HEAD
    TabGridDialogMediator(
            Activity activity,
            DialogController dialogController,
            PropertyModel model,
            ObservableSupplier<TabGroupModelFilter> currentTabGroupModelFilterSupplier,
            @Nullable TabSwitcherResetHandler tabSwitcherResetHandler,
            Supplier<RecyclerViewPosition> recyclerViewPositionSupplier,
=======
    TabGridDialogMediator(Context context, DialogController dialogController, PropertyModel model,
            TabModelSelector tabModelSelector, TabCreatorManager tabCreatorManager,
            TabSwitcherMediator.ResetHandler tabSwitcherResetHandler,
>>>>>>> chromium
            AnimationSourceViewProvider animationSourceViewProvider,
            Supplier<ShareDelegate> shareDelegateSupplier, SnackbarManager snackbarManager,
            String componentName) {
        mContext = context;
        mModel = model;
<<<<<<< HEAD
        mCurrentTabGroupModelFilterSupplier = currentTabGroupModelFilterSupplier;
=======
        mTabModelSelector = tabModelSelector;
        mTabCreatorManager = tabCreatorManager;
        mDialogController = dialogController;
>>>>>>> chromium
        mTabSwitcherResetHandler = tabSwitcherResetHandler;
        mAnimationSourceViewProvider = animationSourceViewProvider;
        mTabGridDialogHandler = new DialogHandler();
        mShareDelegateSupplier = shareDelegateSupplier;
        mComponentName = componentName;
<<<<<<< HEAD
        mShowColorPickerPopupRunnable = showColorPickerPopupRunnable;
        mActionConfirmationManager = actionConfirmationManager;
        mModalDialogManager = modalDialogManager;
        mOriginalProfile =
                mCurrentTabGroupModelFilterSupplier
                        .get()
                        .getTabModel()
                        .getProfile()
                        .getOriginalProfile();
        mDesktopWindowStateManager = desktopWindowStateManager;
        mTabGroupSyncService = TabGroupSyncServiceFactory.getForProfile(mOriginalProfile);
        mCollaborationService = CollaborationServiceFactory.getForProfile(mOriginalProfile);
        // TODO(crbug.com/377366460): This checks only the flag and might break for join only cases.
        // Figure out what to do here.
        if (mTabGroupSyncService != null && ChromeFeatureList.isEnabled(DATA_SHARING)) {
            mDataSharingService = DataSharingServiceFactory.getForProfile(mOriginalProfile);
            mTransitiveSharedGroupObserver =
                    new TransitiveSharedGroupObserver(
                            mTabGroupSyncService, mDataSharingService, mCollaborationService);
            // This should be the first supplier set as the other suppliers depend on its value.
            mTransitiveSharedGroupObserver
                    .getCollaborationIdSupplier()
                    .addObserver(mOnCollaborationIdChanged);
            mTransitiveSharedGroupObserver
                    .getGroupSharedStateSupplier()
                    .addObserver(mOnGroupSharedStateChanged);
            mTransitiveSharedGroupObserver
                    .getGroupMembersSupplier()
                    .addObserver(mOnGroupMembersChanged);
            mMessagingBackendService =
                    MessagingBackendServiceFactory.getForProfile(mOriginalProfile);
            mPersistentMessageObserver =
                    new PersistentMessageObserver() {
                        @Override
                        public void displayPersistentMessage(PersistentMessage message) {
                            updateOnMatch(message);
                        }

                        @Override
                        public void hidePersistentMessage(PersistentMessage message) {
                            updateOnMatch(message);
                        }
                    };
            mMessagingBackendService.addPersistentMessageObserver(mPersistentMessageObserver);
        } else {
            mDataSharingService = null;
            mTransitiveSharedGroupObserver = null;
            mMessagingBackendService = null;
            mPersistentMessageObserver = null;
        }
=======

        // Register for tab model.
        mTabModelObserver = new TabModelObserver() {
            @Override
            public void didAddTab(
                    Tab tab, @TabLaunchType int type, @TabCreationState int creationState) {
                if (!mTabModelSelector.isTabStateInitialized()) {
                    return;
                }
                hideDialog(false);
            }
>>>>>>> chromium

            @Override
            public void tabClosureUndone(Tab tab) {
                updateDialog();
                updateGridTabSwitcher();
                snackbarManager.dismissSnackbars(TabGridDialogMediator.this, tab.getId());
            }

            @Override
            public void didSelectTab(Tab tab, int type, int lastId) {
                if (type == TabSelectionType.FROM_USER) {
                    // Cancel the zooming into tab grid card animation.
                    hideDialog(false);
                }
            }

<<<<<<< HEAD
                        // For tab group sync or data sharing a tab can be added without needing
                        // to close the tab grid dialog. The UI updates for this event are driven
                        // from TabListMediator's implementation.
                        if (type == TabLaunchType.FROM_SYNC_BACKGROUND
                                || type == TabLaunchType.FROM_COLLABORATION_BACKGROUND_IN_GROUP) {
                            return;
                        }
                        hideDialog(false);
                    }
=======
            @Override
            public void willCloseTab(Tab tab, boolean animate) {
                List<Tab> relatedTabs = getRelatedTabs(tab.getId());
                // If the group is empty, update the animation and hide the dialog.
                if (relatedTabs.size() == 0) {
                    hideDialog(false);
                    return;
                }
                // If current tab is closed and tab group is not empty, hand over ID of the next
                // tab in the group to mCurrentTabId.
                if (tab.getId() == mCurrentTabId) {
                    mCurrentTabId = relatedTabs.get(0).getId();
                }
                updateDialog();
                updateGridTabSwitcher();
            }
>>>>>>> chromium

            @Override
            public void tabPendingClosure(Tab tab) {
                if (!mModel.get(TabGridPanelProperties.IS_DIALOG_VISIBLE)) return;
                snackbarManager.showSnackbar(
                        Snackbar.make(tab.getTitle(), TabGridDialogMediator.this,
                                        Snackbar.TYPE_ACTION, Snackbar.UMA_TAB_CLOSE_UNDO)
                                .setTemplateText(
                                        mContext.getString(R.string.undo_bar_close_message))
                                .setAction(mContext.getString(R.string.undo), tab.getId()));
            }

            @Override
            public void tabClosureCommitted(Tab tab) {
                snackbarManager.dismissSnackbars(TabGridDialogMediator.this, tab.getId());
            }
        };

        mTabModelSelectorObserver = new TabModelSelectorObserver() {
            @Override
            public void onTabModelSelected(TabModel newModel, TabModel oldModel) {
                boolean isIncognito = newModel.isIncognito();
                int dialogBackgroundColor =
                        TabUiThemeProvider.getTabGridDialogBackgroundColor(context, isIncognito);
                ColorStateList tintList = isIncognito
                        ? AppCompatResources.getColorStateList(
                                mContext, R.color.default_icon_color_light_tint_list)
                        : AppCompatResources.getColorStateList(
                                mContext, R.color.default_icon_color_tint_list);
                int ungroupBarBackgroundColor =
                        TabUiThemeProvider.getTabGridDialogUngroupBarBackgroundColor(
                                context, isIncognito);
                int ungroupBarHoveredBackgroundColor =
                        TabUiThemeProvider.getTabGridDialogUngroupBarHoveredBackgroundColor(
                                context, isIncognito);
                int ungroupBarTextColor = TabUiThemeProvider.getTabGridDialogUngroupBarTextColor(
                        context, isIncognito);
                int ungroupBarHoveredTextColor =
                        TabUiThemeProvider.getTabGridDialogUngroupBarHoveredTextColor(
                                context, isIncognito);

                mModel.set(TabGridPanelProperties.DIALOG_BACKGROUND_COLOR, dialogBackgroundColor);
                mModel.set(TabGridPanelProperties.TINT, tintList);
                mModel.set(TabGridPanelProperties.DIALOG_UNGROUP_BAR_BACKGROUND_COLOR,
                        ungroupBarBackgroundColor);
                mModel.set(TabGridPanelProperties.DIALOG_UNGROUP_BAR_HOVERED_BACKGROUND_COLOR,
                        ungroupBarHoveredBackgroundColor);
                mModel.set(
                        TabGridPanelProperties.DIALOG_UNGROUP_BAR_TEXT_COLOR, ungroupBarTextColor);
                mModel.set(TabGridPanelProperties.DIALOG_UNGROUP_BAR_HOVERED_TEXT_COLOR,
                        ungroupBarHoveredTextColor);
            }
        };
        mTabModelSelector.addObserver(mTabModelSelectorObserver);

        // Setup ScrimView click Runnable.
        mScrimClickRunnable = () -> {
            if (!TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                mModel.set(TabGridPanelProperties.IS_KEYBOARD_VISIBLE, false);
                mModel.set(TabGridPanelProperties.IS_TITLE_TEXT_FOCUSED, false);
            }
            hideDialog(true);
            RecordUserAction.record("TabGridDialog.Exit");
        };
        mModel.set(TabGridPanelProperties.IS_DIALOG_VISIBLE, false);
    }

<<<<<<< HEAD
    public void initWithNative(
            @NonNull Supplier<TabListEditorController> tabListEditorControllerSupplier) {
        mTabListEditorControllerSupplier = tabListEditorControllerSupplier;
=======
    public void initWithNative(@Nullable TabSelectionEditorCoordinator
                                       .TabSelectionEditorController tabSelectionEditorController,
            TabGroupTitleEditor tabGroupTitleEditor) {
        mTabSelectionEditorController = tabSelectionEditorController;
        mTabGroupTitleEditor = tabGroupTitleEditor;
        mTabModelSelector.getTabModelFilterProvider().addTabModelFilterObserver(mTabModelObserver);
>>>>>>> chromium

        assert mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter()
                        instanceof TabGroupModelFilter;

        mToolbarMenuCallback = result -> {
            if (result == R.id.ungroup_tab) {
                if (!TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                    mModel.set(TabGridPanelProperties.IS_KEYBOARD_VISIBLE, false);
                }
                mModel.set(TabGridPanelProperties.IS_TITLE_TEXT_FOCUSED, false);
                List<Tab> tabs = getRelatedTabs(mCurrentTabId);
                if (mTabSelectionEditorController != null) {
                    mTabSelectionEditorController.show(tabs);
                }
            } else if (result == R.id.share_tab_group) {
                Tab tab = mTabModelSelector.getTabById(mCurrentTabId);
                ShareParams shareParams =
                        new ShareParams
                                .Builder(tab.getWindowAndroid(),
                                        mModel.get(TabGridPanelProperties.HEADER_TITLE), "")
                                .setText(getTabGroupStringForSharing())
                                .setCallback(new ShareParams.TargetChosenCallback() {
                                    @Override
                                    public void onTargetChosen(ComponentName chosenComponent) {
                                        RecordUserAction.record(
                                                "TabGridDialog.SharedGroupAsTextList");
                                    }

                                    @Override
                                    public void onCancel() {}
                                })
                                .build();
                // TODO(crbug.com/1085078): Sharing hub is suppressed for tab group sharing.
                // Re-enable it when tab group sharing is supported by sharing hub.
                ChromeShareExtras chromeShareExtras = new ChromeShareExtras.Builder()
                                                              .setSharingTabGroup(true)
                                                              .setSaveLastUsed(true)
                                                              .build();
                mShareDelegateSupplier.get().share(
                        shareParams, chromeShareExtras, ShareOrigin.TAB_GROUP);
            }

            if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                if (result == R.id.edit_group_name) {
                    mModel.set(TabGridPanelProperties.IS_TITLE_TEXT_FOCUSED, true);
                }
            }
        };

        // Setup toolbar button click listeners.
        setupToolbarClickHandlers();

        if (TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(mContext)) {
            // Setup toolbar edit text.
            setupToolbarEditText();

<<<<<<< HEAD
        mModel.set(TabGridDialogProperties.SHARE_BUTTON_CLICK_LISTENER, getShareClickListener());
        mModel.set(
                TabGridDialogProperties.SHARE_IMAGE_TILES_CLICK_LISTENER, getShareClickListener());
        mModel.set(TabGridDialogProperties.SEND_FEEDBACK_RUNNABLE, this::sendFeedback);
    }

    void hideDialog(boolean showAnimation) {
        if (!mModel.get(TabGridDialogProperties.IS_DIALOG_VISIBLE)) {
            if (!showAnimation) {
                // Forcibly finish any pending animations.
                mModel.set(TabGridDialogProperties.FORCE_ANIMATION_TO_FINISH, true);
                mModel.set(TabGridDialogProperties.FORCE_ANIMATION_TO_FINISH, false);
            }
            return;
        }

        if (mSnackbarManager != null) {
            mSnackbarManager.dismissSnackbars(TabGridDialogMediator.this);
        }

        // Save the title first so that the animation has the correct title.
        saveCurrentGroupModifiedTitle();
        mModel.set(TabGridDialogProperties.IS_TITLE_TEXT_FOCUSED, false);

=======
            // Setup dialog selection editor.
            setupDialogSelectionEditor();
            mModel.set(TabGridPanelProperties.MENU_CLICK_LISTENER, getMenuButtonClickListener());
        }
    }

    void hideDialog(boolean showAnimation) {
        if (!mModel.get(TabGridPanelProperties.IS_DIALOG_VISIBLE)) return;
>>>>>>> chromium
        if (!showAnimation) {
            mModel.set(TabGridPanelProperties.ANIMATION_SOURCE_VIEW, null);
        } else {
            if (mAnimationSourceViewProvider != null && mCurrentTabId != Tab.INVALID_TAB_ID) {
                mModel.set(TabGridPanelProperties.ANIMATION_SOURCE_VIEW,
                        mAnimationSourceViewProvider.getAnimationSourceViewForTab(mCurrentTabId));
            }
        }
        if (mTabSelectionEditorController != null) {
            mTabSelectionEditorController.hide();
        }
        saveCurrentGroupModifiedTitle();
        if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
            mModel.set(TabGridPanelProperties.IS_TITLE_TEXT_FOCUSED, false);
        }
        mDialogController.resetWithListOfTabs(null);
    }

    void onReset(@Nullable List<Tab> tabs) {
        if (tabs == null) {
            mCurrentTabId = Tab.INVALID_TAB_ID;
        } else {
            TabModelFilter filter =
                    mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter();
            mCurrentTabId = filter.getTabAt(filter.indexOf(tabs.get(0))).getId();
        }

        if (mCurrentTabId != Tab.INVALID_TAB_ID) {
            if (mAnimationSourceViewProvider != null) {
                mModel.set(TabGridPanelProperties.ANIMATION_SOURCE_VIEW,
                        mAnimationSourceViewProvider.getAnimationSourceViewForTab(mCurrentTabId));
            } else {
                mModel.set(TabGridPanelProperties.ANIMATION_SOURCE_VIEW, null);
            }
            updateDialog();
            updateDialogScrollPosition();
            mModel.set(TabGridPanelProperties.SCRIMVIEW_CLICK_RUNNABLE, mScrimClickRunnable);
            mDialogController.prepareDialog();
            mModel.set(TabGridPanelProperties.IS_DIALOG_VISIBLE, true);
        } else {
            mModel.set(TabGridPanelProperties.IS_DIALOG_VISIBLE, false);
        }
    }

    /**
     * Destroy any members that needs clean up.
     */
    public void destroy() {
<<<<<<< HEAD
        removeTabGroupModelFilterObserver(mCurrentTabGroupModelFilterSupplier.get());
        mCurrentTabGroupModelFilterSupplier.removeObserver(mOnTabGroupModelFilterChanged);
        KeyboardVisibilityDelegate.getInstance()
                .removeKeyboardVisibilityListener(mKeyboardVisibilityListener);
        if (mTransitiveSharedGroupObserver != null) {
            mTransitiveSharedGroupObserver
                    .getGroupSharedStateSupplier()
                    .removeObserver(mOnGroupSharedStateChanged);
            mTransitiveSharedGroupObserver
                    .getGroupMembersSupplier()
                    .removeObserver(mOnGroupMembersChanged);
            mTransitiveSharedGroupObserver
                    .getCollaborationIdSupplier()
                    .removeObserver(mOnCollaborationIdChanged);
            mTransitiveSharedGroupObserver.destroy();
        }
        if (mDesktopWindowStateManager != null) {
            mDesktopWindowStateManager.removeObserver(this);
        }
        if (mMessagingBackendService != null && mPersistentMessageObserver != null) {
            mMessagingBackendService.removePersistentMessageObserver(mPersistentMessageObserver);
=======
        if (mTabModelObserver != null) {
            mTabModelSelector.getTabModelFilterProvider().removeTabModelFilterObserver(
                    mTabModelObserver);
>>>>>>> chromium
        }
        mTabModelSelector.removeObserver(mTabModelSelectorObserver);
        KeyboardVisibilityDelegate.getInstance().removeKeyboardVisibilityListener(
                mKeyboardVisibilityListener);
    }

    boolean isVisible() {
        return mModel.get(TabGridPanelProperties.IS_DIALOG_VISIBLE);
    }

    private void updateGridTabSwitcher() {
        if (!isVisible() || mTabSwitcherResetHandler == null) return;
        mTabSwitcherResetHandler.resetWithTabList(
                mTabModelSelector.getTabModelFilterProvider().getCurrentTabModelFilter(), false,
                false);
    }

    private void updateDialog() {
<<<<<<< HEAD
        final int tabCount = getRelatedTabs(mCurrentTabId).size();
        if (tabCount == 0) {
            hideDialog(true);
            return;
        }

        updateUngroupBarText(tabCount);

        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        Tab currentTab = filter.getTabModel().getTabById(mCurrentTabId);
        final @TabGroupColorId int color =
                filter.getTabGroupColorWithFallback(currentTab.getRootId());
        mModel.set(TabGridDialogProperties.TAB_GROUP_COLOR_ID, color);
        updateTitle(tabCount);
    }

    private void updateTitle(int tabsCount) {
        Resources res = mActivity.getResources();

        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        Tab currentTab = filter.getTabModel().getTabById(mCurrentTabId);
        String storedTitle = filter.getTabGroupTitle(currentTab.getRootId());
        if (storedTitle != null && filter.isTabInTabGroup(currentTab)) {
            mModel.set(
                    TabGridDialogProperties.COLLAPSE_BUTTON_CONTENT_DESCRIPTION,
                    res.getQuantityString(
                            R.plurals.accessibility_dialog_back_button_with_group_name,
                            tabsCount,
                            storedTitle,
                            tabsCount));
            mModel.set(TabGridDialogProperties.HEADER_TITLE, storedTitle);
            return;
=======
        List<Tab> relatedTabs = getRelatedTabs(mCurrentTabId);
        int tabsCount = relatedTabs.size();
        if (tabsCount == 0) {
            hideDialog(true);
            return;
        }
        if (mTabGroupTitleEditor != null) {
            Tab currentTab = mTabModelSelector.getTabById(mCurrentTabId);
            String storedTitle = mTabGroupTitleEditor.getTabGroupTitle(getRootId(currentTab));
            if (storedTitle != null && relatedTabs.size() > 1) {
                if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                    mModel.set(TabGridPanelProperties.COLLAPSE_BUTTON_CONTENT_DESCRIPTION,
                            mContext.getResources().getQuantityString(
                                    R.plurals.accessibility_dialog_back_button_with_group_name,
                                    relatedTabs.size(), storedTitle, relatedTabs.size()));
                }
                mModel.set(TabGridPanelProperties.HEADER_TITLE, storedTitle);
                return;
            }
>>>>>>> chromium
        }
        if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
            mModel.set(TabGridPanelProperties.COLLAPSE_BUTTON_CONTENT_DESCRIPTION,
                    mContext.getResources().getQuantityString(
                            R.plurals.accessibility_dialog_back_button, relatedTabs.size(),
                            relatedTabs.size()));
        }
        mModel.set(TabGridPanelProperties.HEADER_TITLE,
                mContext.getResources().getQuantityString(
                        R.plurals.bottom_tab_grid_title_placeholder, tabsCount, tabsCount));
    }

    private static int getRootId(Tab tab) {
        return CriticalPersistedTabData.from(tab).getRootId();
    }

    private void updateDialogScrollPosition() {
        // If current selected tab is not within this dialog, always scroll to the top.
        if (mCurrentTabId != mTabModelSelector.getCurrentTabId()) {
            mModel.set(TabGridPanelProperties.INITIAL_SCROLL_INDEX, 0);
            return;
        }
        List<Tab> relatedTabs = getRelatedTabs(mCurrentTabId);
        Tab currentTab = mTabModelSelector.getTabById(mCurrentTabId);
        int initialPosition =
                Math.max(relatedTabs.indexOf(currentTab) - INITIAL_SCROLL_INDEX_OFFSET_GTS, 0);
        mModel.set(TabGridPanelProperties.INITIAL_SCROLL_INDEX, initialPosition);
    }

    private void setupToolbarClickHandlers() {
        mModel.set(
                TabGridPanelProperties.COLLAPSE_CLICK_LISTENER, getCollapseButtonClickListener());
        mModel.set(TabGridPanelProperties.ADD_CLICK_LISTENER, getAddButtonClickListener());
    }

    private void setupDialogSelectionEditor() {
        assert mTabSelectionEditorController != null;
        TabSelectionEditorActionProvider actionProvider =
                new TabSelectionEditorActionProvider(mTabSelectionEditorController,
                        TabSelectionEditorActionProvider.TabSelectionEditorAction.UNGROUP);

<<<<<<< HEAD
        if (mTabListEditorSetup) {
            return;
        }
        mTabListEditorSetup = true;

        List<TabListEditorAction> actions = new ArrayList<>();
        actions.add(
                TabListEditorSelectionAction.createAction(
                        mActivity, ShowMode.MENU_ONLY, ButtonType.ICON_AND_TEXT, IconPosition.END));
        actions.add(
                TabListEditorCloseAction.createAction(
                        mActivity,
                        ShowMode.MENU_ONLY,
                        ButtonType.ICON_AND_TEXT,
                        IconPosition.START));
        actions.add(
                TabListEditorUngroupAction.createAction(
                        mActivity,
                        ShowMode.MENU_ONLY,
                        ButtonType.ICON_AND_TEXT,
                        IconPosition.START));
        actions.add(
                TabListEditorBookmarkAction.createAction(
                        mActivity,
                        ShowMode.MENU_ONLY,
                        ButtonType.ICON_AND_TEXT,
                        IconPosition.START));
        if (TinkerTankDelegate.isEnabled()) {
            actions.add(
                    TabListEditorTinkerTankAction.createAction(
                            mActivity,
                            ShowMode.MENU_ONLY,
                            ButtonType.ICON_AND_TEXT,
                            IconPosition.START));
        }
        actions.add(
                TabListEditorShareAction.createAction(
                        mActivity,
                        ShowMode.MENU_ONLY,
                        ButtonType.ICON_AND_TEXT,
                        IconPosition.START));
        mTabListEditorControllerSupplier.get().configureToolbarWithMenuItems(actions);
=======
        String actionButtonText =
                mContext.getString(R.string.tab_grid_dialog_selection_mode_remove);
        mTabSelectionEditorController.configureToolbar(actionButtonText,
                R.plurals.accessibility_tab_selection_dialog_remove_button, actionProvider, 1,
                null);
>>>>>>> chromium
    }

    private void setupToolbarEditText() {
        mKeyboardVisibilityListener = isShowing -> {
            mModel.set(TabGridPanelProperties.TITLE_CURSOR_VISIBILITY, isShowing);
            if (!TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                mModel.set(TabGridPanelProperties.IS_TITLE_TEXT_FOCUSED, isShowing);
                mModel.set(TabGridPanelProperties.IS_KEYBOARD_VISIBLE, isShowing);
            } else if (TabUiFeatureUtilities.isLaunchPolishEnabled() && !isShowing) {
                mModel.set(TabGridPanelProperties.IS_TITLE_TEXT_FOCUSED, false);
            }
            if (!isShowing) {
                saveCurrentGroupModifiedTitle();
            }
        };
        KeyboardVisibilityDelegate.getInstance().addKeyboardVisibilityListener(
                mKeyboardVisibilityListener);

        TextWatcher textWatcher = new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}

            @Override
            public void afterTextChanged(Editable s) {
                if (!mIsUpdatingTitle) return;
                mCurrentGroupModifiedTitle = s.toString();
            }
        };
        mModel.set(TabGridPanelProperties.TITLE_TEXT_WATCHER, textWatcher);

        View.OnFocusChangeListener onFocusChangeListener = (v, hasFocus) -> {
            mIsUpdatingTitle = hasFocus;
            if (!TabUiFeatureUtilities.isLaunchPolishEnabled()) return;
            mModel.set(TabGridPanelProperties.IS_KEYBOARD_VISIBLE, hasFocus);
            mModel.set(TabGridPanelProperties.IS_TITLE_TEXT_FOCUSED, hasFocus);
        };
        mModel.set(TabGridPanelProperties.TITLE_TEXT_ON_FOCUS_LISTENER, onFocusChangeListener);
    }

    private View.OnClickListener getCollapseButtonClickListener() {
        return view -> {
            if (!TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                mModel.set(TabGridPanelProperties.IS_KEYBOARD_VISIBLE, false);
            }
            hideDialog(true);
            RecordUserAction.record("TabGridDialog.Exit");
        };
    }

    private View.OnClickListener getAddButtonClickListener() {
        return view -> {
            // Get the current Tab first since hideDialog causes mCurrentTabId to be
            // Tab.INVALID_TAB_ID.
<<<<<<< HEAD
            TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
            TabModel tabModel = filter.getTabModel();
            Tab currentTab = tabModel.getTabById(mCurrentTabId);
=======
            Tab currentTab = mTabModelSelector.getTabById(mCurrentTabId);
>>>>>>> chromium
            hideDialog(false);
            if (currentTab == null) {
<<<<<<< HEAD
                tabModel.getTabCreator().launchNtp();
=======
                mTabCreatorManager.getTabCreator(mTabModelSelector.isIncognitoSelected())
                        .launchNTP();
>>>>>>> chromium
                return;
            }
            List<Tab> relatedTabs = getRelatedTabs(currentTab.getId());

<<<<<<< HEAD
            TabGroupUtils.openUrlInGroup(
                    mCurrentTabGroupModelFilterSupplier.get(),
                    UrlConstants.NTP_URL,
                    currentTab.getId(),
                    TabLaunchType.FROM_TAB_GROUP_UI);
=======
            assert relatedTabs.size() > 0;

            Tab parentTabToAttach = relatedTabs.get(relatedTabs.size() - 1);
            mTabCreatorManager.getTabCreator(currentTab.isIncognito())
                    .createNewTab(new LoadUrlParams("chrome-search://local-ntp/local-ntp.html"),
                            TabLaunchType.FROM_TAB_GROUP_UI, parentTabToAttach);
>>>>>>> chromium
            RecordUserAction.record("MobileNewTabOpened." + mComponentName);
        };
    }

<<<<<<< HEAD
    @VisibleForTesting
    public void onToolbarMenuItemClick(int menuId, Token tabGroupId, String collaborationId) {
        // Collaboration IDs will not change without the menu somehow being dismissed. This assert
        // should always hold.
        assert mTransitiveSharedGroupObserver == null
                || Objects.equals(
                        collaborationId,
                        mTransitiveSharedGroupObserver.getCollaborationIdSupplier().get());

        int tabId = mCurrentTabId;
        if (tabId == Tab.INVALID_TAB_ID) return;

        if (menuId == R.id.ungroup_tab || menuId == R.id.select_tabs) {
            RecordUserAction.record("TabGridDialogMenu.SelectTabs");
            mModel.set(TabGridDialogProperties.IS_TITLE_TEXT_FOCUSED, false);
            if (setupAndShowTabListEditor(tabId)) {
                TabUiMetricsHelper.recordSelectionEditorOpenMetrics(
                        TabListEditorOpenMetricGroups.OPEN_FROM_DIALOG, mActivity);
            }
        } else if (menuId == R.id.edit_group_name) {
            RecordUserAction.record("TabGridDialogMenu.Rename");
            mModel.set(TabGridDialogProperties.IS_TITLE_TEXT_FOCUSED, true);
        } else if (menuId == R.id.edit_group_color) {
            RecordUserAction.record("TabGridDialogMenu.EditColor");
            mShowColorPickerPopupRunnable.run();
            TabUiMetricsHelper.recordTabGroupColorChangeActionMetrics(
                    TabGroupColorChangeActionType.VIA_OVERFLOW_MENU);
        } else if (menuId == R.id.manage_sharing) {
            RecordUserAction.record("TabGridDialogMenu.ManageSharing");
            mDataSharingTabManager.createOrManageFlow(
                    mActivity,
                    /* syncId= */ null,
                    new LocalTabGroupId(tabGroupId),
                    /* createGroupFinishedCallback= */ null);
        } else if (menuId == R.id.recent_activity) {
            RecordUserAction.record("TabGridDialogMenu.RecentActivity");
            mDataSharingTabManager.showRecentActivity(mActivity, collaborationId);
            dismissAllDirtyTabMessagesForCurrentGroup();
        } else if (menuId == R.id.close_tab_group || menuId == R.id.delete_tab_group) {
            boolean hideTabGroups = menuId == R.id.close_tab_group;
            if (hideTabGroups) {
                RecordUserAction.record("TabGridDialogMenu.Close");
            } else {
                RecordUserAction.record("TabGridDialogMenu.Delete");
            }
            TabUiUtils.closeTabGroup(
                    mCurrentTabGroupModelFilterSupplier.get(),
                    tabId,
                    hideTabGroups,
                    /* didCloseCallback= */ null);
        } else if (menuId == R.id.delete_shared_group) {
            RecordUserAction.record("TabGridDialogMenu.DeleteShared");
            TabUiUtils.exitSharedTabGroupWithDialog(
                    mActivity,
                    mCurrentTabGroupModelFilterSupplier.get(),
                    mActionConfirmationManager,
                    mModalDialogManager,
                    tabId);
        } else if (menuId == R.id.leave_group) {
            RecordUserAction.record("TabGridDialogMenu.LeaveShared");
            TabUiUtils.exitSharedTabGroupWithDialog(
                    mActivity,
                    mCurrentTabGroupModelFilterSupplier.get(),
                    mActionConfirmationManager,
                    mModalDialogManager,
                    tabId);
        }
    }

    private View.OnClickListener getMenuButtonClickListener() {
        assert mTabListEditorControllerSupplier != null;

        if (mTabGridDialogMenuCoordinator == null) {
            Supplier<Token> tabGroupIdSupplier =
                    () -> {
                        TabModel tabModel = mCurrentTabGroupModelFilterSupplier.get().getTabModel();
                        @Nullable Tab tab = tabModel.getTabById(mCurrentTabId);
                        return tab == null ? null : tab.getTabGroupId();
                    };
            mTabGridDialogMenuCoordinator =
                    new TabGridDialogMenuCoordinator(
                            this::onToolbarMenuItemClick,
                            () -> mCurrentTabGroupModelFilterSupplier.get().getTabModel(),
                            tabGroupIdSupplier,
                            mTabGroupSyncService,
                            mCollaborationService);
        }

        return mTabGridDialogMenuCoordinator.getOnClickListener();
    }

    private View.OnClickListener getShareClickListener() {
        return unused -> handleShareClick();
    }

    private void sendFeedback() {
        HelpAndFeedbackLauncher launcher =
                HelpAndFeedbackLauncherFactory.getForProfile(mOriginalProfile);
        String tag = mActivity.getPackageName() + SHARE_FEEDBACK_CATEGORY_SUFFIX;
        launcher.showFeedback(mActivity, /* url= */ null, tag);
    }

    private void handleShareClick() {
        assert ChromeFeatureList.isEnabled(DATA_SHARING);

        saveCurrentGroupModifiedTitle();
        String tabGroupDisplayName = mModel.get(TabGridDialogProperties.HEADER_TITLE);
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();

        TabUiUtils.startShareTabGroupFlow(
                mActivity, filter, mDataSharingTabManager, mCurrentTabId, tabGroupDisplayName);
    }

    private void updateTabGroupId() {
        if (mTransitiveSharedGroupObserver == null) return;

        boolean isIncognitoBranded = mCurrentTabGroupModelFilterSupplier.get().isIncognitoBranded();
        if (!ChromeFeatureList.isEnabled(DATA_SHARING)
                || isIncognitoBranded
                || !mCollaborationService.getServiceStatus().isAllowedToJoin()
                || mCurrentTabId == Tab.INVALID_TAB_ID) {
            mTransitiveSharedGroupObserver.setTabGroupId(/* tabGroupId= */ null);
            return;
        }

        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        Tab tab = filter.getTabModel().getTabById(mCurrentTabId);
        mTransitiveSharedGroupObserver.setTabGroupId(tab.getTabGroupId());
    }

    private void onCollaborationIdChanged(@Nullable String collaborationId) {
        if (TabShareUtils.isCollaborationIdValid(collaborationId)) {
            showOrUpdateCollaborationActivityMessageCard();
        } else {
            removeCollaborationActivityMessageCard();
        }
        int tabCount = getRelatedTabs(mCurrentTabId).size();
        updateUngroupBarText(tabCount);
    }

    private boolean shouldShowShareButton() {
        return !mCurrentTabGroupModelFilterSupplier.get().isIncognitoBranded()
                && mCollaborationService.getServiceStatus().isAllowedToCreate();
    }

    private boolean shouldShowSendFeedback() {
        return ChromeFeatureList.isEnabled(DATA_SHARING)
                && ChromeFeatureList.getFieldTrialParamByFeatureAsBoolean(
                        DATA_SHARING, SHOW_SEND_FEEDBACK_PARAM, false);
    }

    private void onGroupSharedStateChanged(@Nullable @GroupSharedState Integer groupSharedState) {
        if (groupSharedState == null || groupSharedState == GroupSharedState.NOT_SHARED) {
            mModel.set(
                    TabGridDialogProperties.SHARE_BUTTON_STRING_RES,
                    R.string.tab_grid_share_button_text);
            mModel.set(TabGridDialogProperties.SHOW_SHARE_BUTTON, shouldShowShareButton());
            mModel.set(TabGridDialogProperties.SHOW_IMAGE_TILES, false);
            mModel.set(TabGridDialogProperties.SHOW_SEND_FEEDBACK, false);
        } else if (groupSharedState == GroupSharedState.COLLABORATION_ONLY) {
            mModel.set(
                    TabGridDialogProperties.SHARE_BUTTON_STRING_RES,
                    R.string.tab_grid_manage_button_text);
            mModel.set(TabGridDialogProperties.SHOW_SHARE_BUTTON, shouldShowShareButton());
            mModel.set(TabGridDialogProperties.SHOW_IMAGE_TILES, false);
            mModel.set(TabGridDialogProperties.SHOW_SEND_FEEDBACK, shouldShowSendFeedback());
        } else {
            mModel.set(TabGridDialogProperties.SHOW_SHARE_BUTTON, false);
            mModel.set(TabGridDialogProperties.SHOW_IMAGE_TILES, true);
            mModel.set(TabGridDialogProperties.SHOW_SEND_FEEDBACK, shouldShowSendFeedback());
        }
    }

    private void onGroupMembersChanged(@Nullable List<GroupMember> members) {
        if (mSharedImageTilesCoordinator == null) return;

        @Nullable
        String collaborationId = mTransitiveSharedGroupObserver.getCollaborationIdSupplier().get();
        if (members != null && TabShareUtils.isCollaborationIdValid(collaborationId)) {
            mSharedImageTilesCoordinator.onGroupMembersChanged(collaborationId, members);
        } else {
            mSharedImageTilesCoordinator.onGroupMembersChanged(
                    /* collaborationId= */ null, /* members= */ null);
        }
=======
    private View.OnClickListener getMenuButtonClickListener() {
        assert mTabSelectionEditorController != null;
        return TabGridDialogMenuCoordinator.getTabGridDialogMenuOnClickListener(
                mToolbarMenuCallback);
>>>>>>> chromium
    }

    private List<Tab> getRelatedTabs(int tabId) {
        return mTabModelSelector.getTabModelFilterProvider()
                .getCurrentTabModelFilter()
                .getRelatedTabList(tabId);
    }

    private void saveCurrentGroupModifiedTitle() {
        // When current group no longer exists, skip saving the title.
        if (getRelatedTabs(mCurrentTabId).size() < 2) {
            mCurrentGroupModifiedTitle = null;
        }

        if (mCurrentGroupModifiedTitle == null) {
            return;
        }

<<<<<<< HEAD
        int tabsCount = getRelatedTabs(mCurrentTabId).size();
        if (mCurrentGroupModifiedTitle.length() == 0
                || TabGroupTitleUtils.isDefaultTitle(
                        mActivity, mCurrentGroupModifiedTitle, tabsCount)) {
            // When dialog title is empty or was unchanged, delete previously stored title and
            // restore default title.
            filter.deleteTabGroupTitle(currentTab.getRootId());

            String originalTitle = TabGroupTitleUtils.getDefaultTitle(mActivity, tabsCount);
            mModel.set(
                    TabGridDialogProperties.COLLAPSE_BUTTON_CONTENT_DESCRIPTION,
                    mActivity
                            .getResources()
                            .getQuantityString(
                                    R.plurals.accessibility_dialog_back_button,
                                    tabsCount,
                                    tabsCount));
            mModel.set(TabGridDialogProperties.HEADER_TITLE, originalTitle);
            // Setting the tab group title to null ensures the default title isn't saved, but
            // observers downstream will update to the correct default title.
            filter.setTabGroupTitle(currentTab.getRootId(), null);
            mCurrentGroupModifiedTitle = null;
            RecordUserAction.record("TabGridDialog.ResetTabGroupName");
            return;
        }
        filter.setTabGroupTitle(currentTab.getRootId(), mCurrentGroupModifiedTitle);
        int relatedTabsCount = getRelatedTabs(mCurrentTabId).size();
        mModel.set(
                TabGridDialogProperties.COLLAPSE_BUTTON_CONTENT_DESCRIPTION,
                mActivity
                        .getResources()
                        .getQuantityString(
                                R.plurals.accessibility_dialog_back_button_with_group_name,
                                relatedTabsCount,
                                mCurrentGroupModifiedTitle,
                                relatedTabsCount));
        mModel.set(TabGridDialogProperties.HEADER_TITLE, mCurrentGroupModifiedTitle);
=======
        Tab currentTab = mTabModelSelector.getTabById(mCurrentTabId);
        if (mCurrentGroupModifiedTitle.length() == 0) {
            // When dialog title is empty, delete previously stored title and restore default title.
            mTabGroupTitleEditor.deleteTabGroupTitle(getRootId(currentTab));
            int tabsCount = getRelatedTabs(mCurrentTabId).size();
            assert tabsCount >= 2;

            String originalTitle = mContext.getResources().getQuantityString(
                    R.plurals.bottom_tab_grid_title_placeholder, tabsCount, tabsCount);
            if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
                mModel.set(TabGridPanelProperties.COLLAPSE_BUTTON_CONTENT_DESCRIPTION,
                        mContext.getResources().getQuantityString(
                                R.plurals.accessibility_dialog_back_button, tabsCount, tabsCount));
            }
            mModel.set(TabGridPanelProperties.HEADER_TITLE, originalTitle);
            mTabGroupTitleEditor.updateTabGroupTitle(currentTab, originalTitle);
            return;
        }
        mTabGroupTitleEditor.storeTabGroupTitle(getRootId(currentTab), mCurrentGroupModifiedTitle);
        mTabGroupTitleEditor.updateTabGroupTitle(currentTab, mCurrentGroupModifiedTitle);
        if (TabUiFeatureUtilities.isLaunchPolishEnabled()) {
            int relatedTabsCount = getRelatedTabs(mCurrentTabId).size();
            mModel.set(TabGridPanelProperties.COLLAPSE_BUTTON_CONTENT_DESCRIPTION,
                    mContext.getResources().getQuantityString(
                            R.plurals.accessibility_dialog_back_button_with_group_name,
                            relatedTabsCount, mCurrentGroupModifiedTitle, relatedTabsCount));
        }
        mModel.set(TabGridPanelProperties.HEADER_TITLE, mCurrentGroupModifiedTitle);
>>>>>>> chromium
        RecordUserAction.record("TabGridDialog.TabGroupNamedInDialog");
        mCurrentGroupModifiedTitle = null;
    }

    TabListMediator.TabGridDialogHandler getTabGridDialogHandler() {
        return mTabGridDialogHandler;
    }

    // SnackbarManager.SnackbarController implementation.
    @Override
    public void onAction(Object actionData) {
        int tabId = (int) actionData;
        TabModel model = mTabModelSelector.getModelForTabId(tabId);
        if (model != null) {
            model.cancelTabClosure(tabId);
        }
    }

    @Override
    public void onDismissNoAction(Object actionData) {
        int tabId = (int) actionData;
        TabModel model = mTabModelSelector.getModelForTabId(tabId);
        if (model != null) {
            model.commitTabClosure(tabId);
        }
    }

    /**
     * A handler that handles TabGridDialog related changes originated from {@link TabListMediator}
     * and {@link TabGridItemTouchHelperCallback}.
     */
    class DialogHandler implements TabListMediator.TabGridDialogHandler {
        @Override
        public void updateUngroupBarStatus(@TabGridDialogView.UngroupBarStatus int status) {
            mModel.set(TabGridPanelProperties.UNGROUP_BAR_STATUS, status);
        }

        @Override
        public void updateDialogContent(int tabId) {
            mCurrentTabId = tabId;
            updateDialog();
        }
    }

    private String getTabGroupStringForSharing() {
        StringBuilder sb = new StringBuilder();
        List<Tab> tabgroup = getRelatedTabs(mCurrentTabId);
        assert tabgroup.size() > 0;
        for (int i = 0; i < tabgroup.size(); i++) {
            sb.append(i + 1).append(". ").append(tabgroup.get(i).getUrl().getSpec()).append("\n");
        }
        return sb.toString();
    }

    @VisibleForTesting
    String getTabGroupStringForSharingForTesting() {
        return getTabGroupStringForSharing();
    }

    @VisibleForTesting
    int getCurrentTabIdForTesting() {
        return mCurrentTabId;
    }

    @VisibleForTesting
    void setCurrentTabIdForTesting(int tabId) {
        mCurrentTabId = tabId;
    }

    @VisibleForTesting
    KeyboardVisibilityDelegate.KeyboardVisibilityListener
    getKeyboardVisibilityListenerForTesting() {
        return mKeyboardVisibilityListener;
    }

    @VisibleForTesting
    boolean getIsUpdatingTitleForTesting() {
        return mIsUpdatingTitle;
    }

    @VisibleForTesting
    String getCurrentGroupModifiedTitleForTesting() {
        return mCurrentGroupModifiedTitle;
    }

    @VisibleForTesting
    Callback<Integer> getToolbarMenuCallbackForTesting() {
        return mToolbarMenuCallback;
    }

    @VisibleForTesting
    Runnable getScrimClickRunnableForTesting() {
        return mScrimClickRunnable;
    }
<<<<<<< HEAD

    private void removeCollaborationActivityMessageCard() {
        mDialogController.removeMessageCardItem(MessageType.COLLABORATION_ACTIVITY);
        mCollaborationActivityPropertyModel = null;
    }

    private @Nullable Token getCurrentTabGroupId() {
        TabGroupModelFilter filter = mCurrentTabGroupModelFilterSupplier.get();
        Tab tab = filter.getTabModel().getTabById(mCurrentTabId);
        return tab == null ? null : tab.getTabGroupId();
    }

    private void updateOnMatch(PersistentMessage message) {
        if (message.attribution.tabGroupMetadata == null
                || message.attribution.tabGroupMetadata.localTabGroupId == null) return;
        @Nullable Token token = getCurrentTabGroupId();
        if (Objects.equals(
                token, message.attribution.tabGroupMetadata.localTabGroupId.tabGroupId)) {
            showOrUpdateCollaborationActivityMessageCard();
        }
    }

    private void dismissAllDirtyTabMessagesForCurrentGroup() {
        @Nullable Token tabGroupId = getCurrentTabGroupId();
        @Nullable
        String collaborationId =
                TabShareUtils.getCollaborationIdOrNull(tabGroupId, mTabGroupSyncService);
        if (mMessagingBackendService != null && collaborationId != null) {
            mMessagingBackendService.clearDirtyTabMessagesForGroup(collaborationId);
        }
    }

    private void showOrUpdateCollaborationActivityMessageCard() {
        @Nullable Token currentTabGroupId = getCurrentTabGroupId();
        if (currentTabGroupId == null) {
            assert mCollaborationActivityPropertyModel == null;
            return;
        }

        EitherGroupId eitherGroupId =
                EitherGroupId.createLocalId(new LocalTabGroupId(currentTabGroupId));
        List<PersistentMessage> messages =
                mMessagingBackendService.getMessagesForGroup(
                        eitherGroupId,
                        /* type= */ Optional.of(PersistentNotificationType.DIRTY_TAB));
        Map<Integer, Integer> collaborationEventCounts = new HashMap<>();
        for (PersistentMessage message : messages) {
            collaborationEventCounts.merge(message.collaborationEvent, 1, Integer::sum);
        }
        int tabsAdded = collaborationEventCounts.getOrDefault(CollaborationEvent.TAB_ADDED, 0);
        int tabsChanged = collaborationEventCounts.getOrDefault(CollaborationEvent.TAB_UPDATED, 0);
        int tabsClosed = collaborationEventCounts.getOrDefault(CollaborationEvent.TAB_REMOVED, 0);
        if (tabsAdded == 0 && tabsChanged == 0 && tabsClosed == 0) {
            removeCollaborationActivityMessageCard();
            return;
        }

        if (mCollaborationActivityPropertyModel == null) {
            mCollaborationActivityPropertyModel =
                    new CollaborationActivityMessageCardViewModel(
                            mActivity,
                            this::showRecentActivityOrDismissActivityMessageCard,
                            (unused) -> {
                                // TODO(crbug.com/391946087): this shouldn't be required once
                                // clearDirtyTabMessagesForCurrentGroup is fixed.
                                removeCollaborationActivityMessageCard();

                                dismissAllDirtyTabMessagesForCurrentGroup();
                            });
        }
        mCollaborationActivityPropertyModel.updateDescriptionText(
                mActivity, tabsAdded, tabsChanged, tabsClosed);

        if (!mDialogController.messageCardExists(MessageType.COLLABORATION_ACTIVITY)) {
            mDialogController.addMessageCardItem(
                    /* position= */ 0, mCollaborationActivityPropertyModel.getPropertyModel());
        }
    }

    private void showRecentActivityOrDismissActivityMessageCard() {
        assert mTransitiveSharedGroupObserver != null;
        @Nullable
        String collaborationId = mTransitiveSharedGroupObserver.getCollaborationIdSupplier().get();
        if (TabShareUtils.isCollaborationIdValid(collaborationId)) {
            mDataSharingTabManager.showRecentActivity(mActivity, collaborationId);
        } else {
            // TODO(crbug.com/391946087): this shouldn't be required once
            // clearDirtyTabMessagesForCurrentGroup is fixed.
            removeCollaborationActivityMessageCard();
        }
        dismissAllDirtyTabMessagesForCurrentGroup();
    }

    private void updateUngroupBarText(int tabCount) {
        @StringRes int ungroupBarTextId = R.string.tab_grid_dialog_remove_from_group;
        if (tabCount == 1) {
            boolean isMember = MemberRole.MEMBER == getMemberRole();
            ungroupBarTextId =
                    isMember
                            ? R.string.remove_last_tab_action_member
                            : R.string.remove_last_tab_action;
        }

        Resources res = mActivity.getResources();
        mModel.set(
                TabGridDialogProperties.DIALOG_UNGROUP_BAR_TEXT, res.getString(ungroupBarTextId));
    }

    private @MemberRole int getMemberRole() {
        if (!mCollaborationService.getServiceStatus().isAllowedToJoin()) return MemberRole.UNKNOWN;

        @Nullable
        String collaborationId = mTransitiveSharedGroupObserver.getCollaborationIdSupplier().get();
        if (!TabShareUtils.isCollaborationIdValid(collaborationId)) return MemberRole.UNKNOWN;

        return mCollaborationService.getCurrentUserRoleForGroup(collaborationId);
    }

    /** AppHeaderObserver implementation */
    @Override
    public void onAppHeaderStateChanged(AppHeaderState state) {
        mModel.set(TabGridDialogProperties.APP_HEADER_HEIGHT, state.getAppHeaderHeight());
    }
=======
>>>>>>> chromium
}
