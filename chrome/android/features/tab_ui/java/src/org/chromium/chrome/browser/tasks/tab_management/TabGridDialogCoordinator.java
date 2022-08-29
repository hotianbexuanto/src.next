// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tasks.tab_management;

import android.app.Activity;
import android.content.Context;
import android.graphics.Rect;
import android.view.LayoutInflater;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import org.chromium.base.SysUtils;
import org.chromium.base.TraceEvent;
import org.chromium.base.metrics.RecordUserAction;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.supplier.Supplier;
import org.chromium.chrome.browser.compositor.layouts.content.TabContentManager;
import org.chromium.chrome.browser.share.ShareDelegate;
import org.chromium.chrome.browser.tab.Tab;
<<<<<<< HEAD
import org.chromium.chrome.browser.tab_ui.RecyclerViewPosition;
import org.chromium.chrome.browser.tab_ui.TabContentManager;
import org.chromium.chrome.browser.tab_ui.TabContentManagerThumbnailProvider;
import org.chromium.chrome.browser.tabmodel.TabGroupColorUtils;
import org.chromium.chrome.browser.tabmodel.TabGroupModelFilter;
import org.chromium.chrome.browser.tasks.tab_management.ColorPickerCoordinator.ColorPickerLayoutType;
import org.chromium.chrome.browser.tasks.tab_management.MessageService.MessageType;
import org.chromium.chrome.browser.tasks.tab_management.TabGridDialogMediator.AnimationSourceViewProvider;
import org.chromium.chrome.browser.tasks.tab_management.TabListEditorCoordinator.TabListEditorController;
import org.chromium.chrome.browser.tasks.tab_management.TabListMediator.GridCardOnClickListenerProvider;
import org.chromium.chrome.browser.tasks.tab_management.TabProperties.UiType;
import org.chromium.chrome.browser.tasks.tab_management.TabUiMetricsHelper.TabGroupColorChangeActionType;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.tab_ui.R;
import org.chromium.components.browser_ui.bottomsheet.BottomSheetController;
import org.chromium.components.browser_ui.desktop_windowing.DesktopWindowStateManager;
import org.chromium.components.browser_ui.widget.scrim.ScrimManager;
import org.chromium.components.collaboration.CollaborationService;
import org.chromium.components.collaboration.ServiceStatus;
import org.chromium.components.data_sharing.DataSharingService;
import org.chromium.ui.modaldialog.ModalDialogManager;
import org.chromium.ui.modelutil.LayoutViewBuilder;
=======
import org.chromium.chrome.browser.tabmodel.TabCreatorManager;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.tab_ui.R;
import org.chromium.components.browser_ui.widget.scrim.ScrimCoordinator;
>>>>>>> chromium
import org.chromium.ui.modelutil.PropertyModel;
import org.chromium.ui.modelutil.PropertyModelChangeProcessor;

import java.util.List;

/**
 * A coordinator for TabGridDialog component. Manages the communication with
 * {@link TabListCoordinator} as well as the life-cycle of shared component
 * objects.
 */
public class TabGridDialogCoordinator implements TabGridDialogMediator.DialogController {
    private final String mComponentName;
    private final TabListCoordinator mTabListCoordinator;
    private final TabGridDialogMediator mMediator;
    private final PropertyModel mModel;
    private final PropertyModelChangeProcessor mModelChangeProcessor;
    private final ViewGroup mRootView;
    private final ObservableSupplierImpl<Boolean> mBackPressChangedSupplier =
            new ObservableSupplierImpl<>();
    private TabSelectionEditorCoordinator mTabSelectionEditorCoordinator;
    private TabGridDialogView mDialogView;

<<<<<<< HEAD
    TabGridDialogCoordinator(
            Activity activity,
            BrowserControlsStateProvider browserControlsStateProvider,
            @NonNull BottomSheetController bottomSheetController,
            @NonNull DataSharingTabManager dataSharingTabManager,
            @NonNull ObservableSupplier<TabGroupModelFilter> currentTabGroupModelFilterSupplier,
            TabContentManager tabContentManager,
            ViewGroup containerView,
            @Nullable TabSwitcherResetHandler resetHandler,
            @Nullable GridCardOnClickListenerProvider gridCardOnClickListenerProvider,
            @Nullable AnimationSourceViewProvider animationSourceViewProvider,
            ScrimManager scrimManager,
            @Nullable ActionConfirmationManager actionConfirmationManager,
            @NonNull ModalDialogManager modalDialogManager,
            @Nullable DesktopWindowStateManager desktopWindowStateManager) {
        try (TraceEvent e = TraceEvent.scoped("TabGridDialogCoordinator.constructor")) {
            boolean isDataSharingAndroidEnabled =
                    ChromeFeatureList.isEnabled(ChromeFeatureList.DATA_SHARING);
=======
    TabGridDialogCoordinator(Activity activity, TabModelSelector tabModelSelector,
            TabContentManager tabContentManager, TabCreatorManager tabCreatorManager,
            ViewGroup containerView, TabSwitcherMediator.ResetHandler resetHandler,
            TabListMediator.GridCardOnClickListenerProvider gridCardOnClickListenerProvider,
            TabGridDialogMediator.AnimationSourceViewProvider animationSourceViewProvider,
            Supplier<ShareDelegate> shareDelegateSupplier, ScrimCoordinator scrimCoordinator,
            ViewGroup rootView) {
        mComponentName = animationSourceViewProvider == null ? "TabGridDialogFromStrip"
                                                             : "TabGridDialogInSwitcher";
>>>>>>> chromium

            mModel = new PropertyModel(TabGridPanelProperties.ALL_KEYS);
            mRootView = rootView;

            mDialogView = containerView.findViewById(R.id.dialog_parent_view);
<<<<<<< HEAD
            if (mDialogView == null) {
                ViewStub dialogStub = containerView.findViewById(R.id.tab_grid_dialog_stub);
                assert dialogStub != null;

                dialogStub.setLayoutResource(R.layout.tab_grid_dialog_layout);
                dialogStub.inflate();

                mDialogView = containerView.findViewById(R.id.dialog_parent_view);
                mDialogView.setupScrimManager(scrimManager);
            }

            if (!activity.isDestroyed() && !activity.isFinishing()) {
                mSnackbarManager =
                        new SnackbarManager(activity, mDialogView.getSnackBarContainer(), null);
            } else {
                mSnackbarManager = null;
            }
            mBottomSheetController = bottomSheetController;

            Profile originalProfile =
                    mCurrentTabGroupModelFilterSupplier
                            .get()
                            .getTabModel()
                            .getProfile()
                            .getOriginalProfile();
            if (isDataSharingAndroidEnabled) {
                DataSharingService dataSharingService =
                        DataSharingServiceFactory.getForProfile(originalProfile);
                mSharedImageTilesCoordinator =
                        new SharedImageTilesCoordinator(
                                activity,
                                SharedImageTilesType.DEFAULT,
                                new SharedImageTilesColor(SharedImageTilesColor.Style.DYNAMIC),
                                dataSharingService);
            }

            Runnable showColorPickerPopupRunnable =
                    () -> {
                        showColorPickerPopup(mDialogView.findViewById(R.id.tab_group_color_icon));
                    };

            mMediator =
                    new TabGridDialogMediator(
                            activity,
                            this,
                            mModel,
                            currentTabGroupModelFilterSupplier,
                            resetHandler,
                            this::getRecyclerViewPosition,
                            animationSourceViewProvider,
                            mSnackbarManager,
                            mSharedImageTilesCoordinator,
                            dataSharingTabManager,
                            mComponentName,
                            showColorPickerPopupRunnable,
                            actionConfirmationManager,
                            modalDialogManager,
                            desktopWindowStateManager);

            // TODO(crbug.com/40662311) : Remove the inline mode logic here, make the constructor to
            // take in a mode parameter instead.
            mTabListCoordinator =
                    new TabListCoordinator(
                            TabUiFeatureUtilities.shouldUseListMode()
                                    ? TabListCoordinator.TabListMode.LIST
                                    : TabListCoordinator.TabListMode.GRID,
                            activity,
                            mBrowserControlsStateProvider,
                            mModalDialogManager,
                            currentTabGroupModelFilterSupplier,
                            new TabContentManagerThumbnailProvider(tabContentManager),
                            /* actionOnRelatedTabs= */ false,
                            actionConfirmationManager,
                            dataSharingTabManager,
                            gridCardOnClickListenerProvider,
                            mMediator.getTabGridDialogHandler(),
                            TabProperties.TabActionState.CLOSABLE,
                            /* selectionDelegateProvider= */ null,
                            /* priceWelcomeMessageControllerSupplier= */ null,
                            containerView,
                            /* attachToParent= */ false,
                            mComponentName,
                            /* onModelTokenChange= */ null,
                            /* hasEmptyView= */ false,
                            /* emptyImageResId= */ Resources.ID_NULL,
                            /* emptyHeadingStringResId= */ Resources.ID_NULL,
                            /* emptySubheadingStringResId= */ Resources.ID_NULL,
                            /* onTabGroupCreation= */ null,
                            /* backgroundColorSupplier= */ null,
                            /* allowDragAndDrop= */ true);
            mTabListCoordinator.setOnLongPressTabItemEventListener(mMediator);
            mTabListCoordinator.registerItemType(
                    UiType.MESSAGE,
                    new LayoutViewBuilder(R.layout.tab_grid_message_card_item),
                    MessageCardViewBinder::bind);

            mTabListOnScrollListener
                    .getYOffsetNonZeroSupplier()
                    .addObserver(
                            (showHairline) ->
                                    mModel.set(
                                            TabGridDialogProperties.HAIRLINE_VISIBILITY,
                                            showHairline));
            TabListRecyclerView recyclerView = mTabListCoordinator.getContainerView();
            recyclerView.addOnScrollListener(mTabListOnScrollListener);

            @LayoutRes
            int toolbar_res_id =
                    isDataSharingAndroidEnabled
                            ? R.layout.tab_grid_dialog_toolbar_two_row
                            : R.layout.tab_grid_dialog_toolbar;
            TabGridDialogToolbarView toolbarView =
                    (TabGridDialogToolbarView)
                            LayoutInflater.from(activity)
                                    .inflate(toolbar_res_id, recyclerView, false);
            if (isDataSharingAndroidEnabled) {
                FrameLayout imageTilesContainer =
                        toolbarView.findViewById(R.id.image_tiles_container);
                TabUiUtils.attachSharedImageTilesCoordinatorToFrameLayout(
                        mSharedImageTilesCoordinator, imageTilesContainer);
            }

            mModelChangeProcessor =
                    PropertyModelChangeProcessor.create(
                            mModel,
                            new TabGridDialogViewBinder.ViewHolder(
                                    toolbarView, recyclerView, mDialogView),
                            TabGridDialogViewBinder::bind);
            mBackPressChangedSupplier.set(isVisible());
            mModel.addObserver((source, key) -> mBackPressChangedSupplier.set(isVisible()));

            // This is always created post-native so calling these immediately is safe.
            // TODO(crbug.com/40894893): Consider inlining these behaviors in their respective
            // constructors if possible.
            mMediator.initWithNative(this::getTabListEditorController);
            mTabListCoordinator.initWithNative(originalProfile);

            CollaborationService collaborationService =
                    CollaborationServiceFactory.getForProfile(originalProfile);
            @NonNull ServiceStatus serviceStatus = collaborationService.getServiceStatus();
            if (serviceStatus.isAllowedToJoin()) {
                mTabLabeller =
                        new TabLabeller(
                                originalProfile,
                                mTabListCoordinator.getTabListNotificationHandler(),
                                mCurrentTabGroupId);
            } else {
                mTabLabeller = null;
            }
=======
            mDialogView.setupScrimCoordinator(scrimCoordinator);
>>>>>>> chromium
        }
    }

    public void initWithNative(Context context, TabModelSelector tabModelSelector,
            TabContentManager tabContentManager, TabGroupTitleEditor tabGroupTitleEditor) {
        try (TraceEvent e = TraceEvent.scoped("TabGridDialogCoordinator.initWithNative")) {
            TabSelectionEditorCoordinator.TabSelectionEditorController controller = null;
            if (TabUiFeatureUtilities.isTabGroupsAndroidContinuationEnabled(context)) {
                @TabListCoordinator.TabListMode
                int mode = SysUtils.isLowEndDevice() ? TabListCoordinator.TabListMode.LIST
                                                     : TabListCoordinator.TabListMode.GRID;
                mTabSelectionEditorCoordinator = new TabSelectionEditorCoordinator(context,
                        mDialogView.findViewById(R.id.dialog_container_view), tabModelSelector,
                        tabContentManager, mode, mRootView);

                controller = mTabSelectionEditorCoordinator.getController();
            } else {
                mTabSelectionEditorCoordinator = null;
            }

            mMediator.initWithNative(controller, tabGroupTitleEditor);
            mTabListCoordinator.initWithNative(null);
        }
    }
<<<<<<< HEAD

    private View.OnClickListener getColorIconClickListener() {
        return (view) -> {
            showColorPickerPopup(view);
            TabUiMetricsHelper.recordTabGroupColorChangeActionMetrics(
                    TabGroupColorChangeActionType.VIA_COLOR_ICON);
        };
    }

    private void showColorPickerPopup(View anchorView) {
        PopupWindow.OnDismissListener onDismissListener =
                new PopupWindow.OnDismissListener() {
                    @Override
                    public void onDismiss() {
                        mMediator.setSelectedTabGroupColor(
                                mColorPickerCoordinator.getSelectedColorSupplier().get());

                        // Only require a refresh of the tab list if accessed from the GTS,
                        // skip if this is reached from the tab strip as the color will
                        // refresh upon re-entering the tab switcher.
                        if (mTabSwitcherResetHandler != null) {
                            // Refresh the TabSwitcher's tab list to reflect the last
                            // selected color in the color picker when it is dismissed. This
                            // call will be invoked for both Grid and List modes on the GTS.
                            mTabSwitcherResetHandler.resetWithTabList(
                                    mCurrentTabGroupModelFilterSupplier.get(), false);
                        }
                    }
                };

        List<Integer> colors = TabGroupColorUtils.getTabGroupColorIdList();
        mColorPickerCoordinator =
                new ColorPickerCoordinator(
                        mActivity,
                        colors,
                        LayoutInflater.from(mActivity)
                                .inflate(R.layout.tab_group_color_picker_container, null),
                        ColorPickerType.TAB_GROUP,
                        mModel.get(TabGridDialogProperties.IS_INCOGNITO),
                        ColorPickerLayoutType.DOUBLE_ROW,
                        () -> {
                            mColorIconPopupWindow.dismiss();
                            mColorIconPopupWindow = null;
                            onDismissListener.onDismiss();
                        });
        mColorPickerCoordinator.setSelectedColorItem(
                mModel.get(TabGridDialogProperties.TAB_GROUP_COLOR_ID));

        int popupMargin =
                mActivity
                        .getResources()
                        .getDimensionPixelSize(R.dimen.tab_group_color_picker_popup_padding);

        View contentView = mColorPickerCoordinator.getContainerView();
        contentView.setPadding(popupMargin, popupMargin, popupMargin, popupMargin);
        View decorView = ((Activity) contentView.getContext()).getWindow().getDecorView();

        // If the filter is in incognito mode, apply the incognito background drawable.
        @DrawableRes
        int bgDrawableId =
                mModel.get(TabGridDialogProperties.IS_INCOGNITO)
                        ? R.drawable.menu_bg_tinted_on_dark_bg
                        : R.drawable.menu_bg_tinted;

        mColorIconPopupWindow =
                new AnchoredPopupWindow(
                        mActivity,
                        decorView,
                        AppCompatResources.getDrawable(mActivity, bgDrawableId),
                        contentView,
                        new ViewRectProvider(anchorView));
        mColorIconPopupWindow.addOnDismissListener(onDismissListener);
        mColorIconPopupWindow.setFocusable(true);
        mColorIconPopupWindow.setHorizontalOverlapAnchor(true);
        mColorIconPopupWindow.setVerticalOverlapAnchor(true);
        mColorIconPopupWindow.show();
    }

    /** Destroy any members that needs clean up. */
=======
    /**
     * Destroy any members that needs clean up.
     */
>>>>>>> chromium
    public void destroy() {
        mTabListCoordinator.onDestroy();
        mMediator.destroy();
        mModelChangeProcessor.destroy();
        if (mTabSelectionEditorCoordinator != null) {
            mTabSelectionEditorCoordinator.destroy();
        }
    }

    @Override
    public boolean isVisible() {
        return mMediator.isVisible();
    }

    @NonNull
    Rect getGlobalLocationOfCurrentThumbnail() {
        mTabListCoordinator.updateThumbnailLocation();
        Rect thumbnail = mTabListCoordinator.getThumbnailLocationOfCurrentTab();
        Rect recyclerViewLocation = mTabListCoordinator.getRecyclerViewLocation();
        thumbnail.offset(recyclerViewLocation.left, recyclerViewLocation.top);
        return thumbnail;
    }

    TabGridDialogMediator.DialogController getDialogController() {
        return this;
    }

    @Override
    public void resetWithListOfTabs(@Nullable List<Tab> tabs) {
        mTabListCoordinator.resetWithListOfTabs(tabs);
        mMediator.onReset(tabs);
    }

    @Override
    public void hideDialog(boolean showAnimation) {
        mMediator.hideDialog(showAnimation);
        mTabListCoordinator.postHiding();
    }

    @Override
    public void prepareDialog() {
        mTabListCoordinator.prepareTabGridDialogView();
    }

    @Override
    public boolean handleBackPressed() {
        if (!isVisible()) return false;
        handleBackPress();
        return true;
    }

    @Override
    public void handleBackPress() {
        mMediator.hideDialog(true);
        RecordUserAction.record("TabGridDialog.Exit");
    }

    @Override
    public ObservableSupplier<Boolean> getHandleBackPressChangedSupplier() {
        return mBackPressChangedSupplier;
    }
}
