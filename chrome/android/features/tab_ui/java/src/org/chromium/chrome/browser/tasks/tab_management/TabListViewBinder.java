// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tasks.tab_management;

import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.InsetDrawable;
<<<<<<< HEAD
import android.view.LayoutInflater;
=======
import android.os.Build;
>>>>>>> chromium
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.core.content.res.ResourcesCompat;
import androidx.core.graphics.drawable.DrawableCompat;
import androidx.vectordrawable.graphics.drawable.AnimatedVectorDrawableCompat;

import org.chromium.base.ApiCompatibilityUtils;
import org.chromium.chrome.tab_ui.R;
import org.chromium.ui.modelutil.PropertyKey;
import org.chromium.ui.modelutil.PropertyModel;

/**
 * {@link org.chromium.ui.modelutil.SimpleRecyclerViewMcp.ViewBinder} for tab List.
 */
class TabListViewBinder {
    // TODO(1023557): Merge with TabGridViewBinder for shared properties.
    public static void bindListTab(
            PropertyModel model, ViewGroup view, @Nullable PropertyKey propertyKey) {
        View fastView = view;

<<<<<<< HEAD
        ((TabListView) view).setTabActionState(tabActionState);
        bindListTab(model, (ViewLookupCachingFrameLayout) view, propertyKey);
        if (tabActionState == TabActionState.CLOSABLE) {
            bindClosableListTab(model, (ViewLookupCachingFrameLayout) view, propertyKey);
        } else if (tabActionState == TabActionState.SELECTABLE) {
            bindSelectableListTab(model, (ViewLookupCachingFrameLayout) view, propertyKey);
        } else {
            assert false : "Unsupported TabActionState provided to bindTab.";
        }
    }

    /**
     * Handles any cleanup for recycled views that might be expensive to keep around in the pool.
     *
     * @param model The property model to possibly cleanup.
     * @param view The view to possibly cleanup.
     */
    public static void onViewRecycled(PropertyModel model, View view) {
        if (view instanceof TabListView tabListView) {
            ImageView faviconView = tabListView.findViewById(R.id.start_icon);
            faviconView.setImageDrawable(null);

            FrameLayout colorContainer = tabListView.findViewById(R.id.after_title_container);
            TabCardViewBinderUtils.detachTabGroupColorView(colorContainer);

            FrameLayout labelContainer =
                    tabListView.findViewById(R.id.before_description_container);
            labelContainer.removeAllViews();
        }
    }

    // TODO(crbug.com/40107066): Merge with TabGridViewBinder for shared properties.
    private static void bindListTab(
            PropertyModel model, ViewGroup view, @Nullable PropertyKey propertyKey) {
=======
>>>>>>> chromium
        if (TabProperties.TITLE == propertyKey) {
            String title = model.get(TabProperties.TITLE);
            ((TextView) fastView.findViewById(R.id.title)).setText(title);
        } else if (TabProperties.FAVICON == propertyKey) {
            Drawable favicon = model.get(TabProperties.FAVICON);
            ImageView faviconView = (ImageView) fastView.findViewById(R.id.start_icon);
            faviconView.setBackgroundResource(R.drawable.list_item_icon_modern_bg);
            faviconView.setImageDrawable(favicon);
        } else if (TabProperties.TAB_CLOSED_LISTENER == propertyKey) {
            if (model.get(TabProperties.TAB_CLOSED_LISTENER) == null) {
                fastView.findViewById(R.id.end_button).setOnClickListener(null);
            } else {
                fastView.findViewById(R.id.end_button).setOnClickListener(v -> {
                    int tabId = model.get(TabProperties.TAB_ID);
                    model.get(TabProperties.TAB_CLOSED_LISTENER).run(tabId);
                });
            }
        } else if (TabProperties.IS_SELECTED == propertyKey) {
            int selectedTabBackground =
                    model.get(TabProperties.SELECTED_TAB_BACKGROUND_DRAWABLE_ID);
            if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.LOLLIPOP_MR1) {
                if (model.get(TabProperties.IS_SELECTED)) {
                    fastView.findViewById(R.id.selected_view_below_lollipop)
                            .setBackgroundResource(selectedTabBackground);
                    fastView.findViewById(R.id.selected_view_below_lollipop)
                            .setVisibility(View.VISIBLE);
                } else {
                    fastView.findViewById(R.id.selected_view_below_lollipop)
                            .setVisibility(View.GONE);
                }
            } else {
                Resources res = view.getResources();
                Resources.Theme theme = view.getContext().getTheme();
                Drawable drawable = new InsetDrawable(
                        ResourcesCompat.getDrawable(res, selectedTabBackground, theme),
                        (int) res.getDimension(R.dimen.tab_list_selected_inset_low_end));
                view.setForeground(model.get(TabProperties.IS_SELECTED) ? drawable : null);
            }
        } else if (TabProperties.TAB_SELECTED_LISTENER == propertyKey) {
            if (model.get(TabProperties.TAB_SELECTED_LISTENER) == null) {
                view.setOnClickListener(null);
            } else {
                view.setOnClickListener(v -> {
                    int tabId = model.get(TabProperties.TAB_ID);
                    model.get(TabProperties.TAB_SELECTED_LISTENER).run(tabId);
                });
            }
        } else if (TabProperties.URL_DOMAIN == propertyKey) {
            String domain = model.get(TabProperties.URL_DOMAIN);
<<<<<<< HEAD
            ((TextView) view.findViewById(R.id.description)).setText(domain);
        } else if (TabProperties.TAB_GROUP_COLOR_VIEW_PROVIDER == propertyKey) {
            @Nullable
            TabGroupColorViewProvider provider =
                    model.get(TabProperties.TAB_GROUP_COLOR_VIEW_PROVIDER);
            FrameLayout container = view.findViewById(R.id.after_title_container);
            TabCardViewBinderUtils.updateTabGroupColorView(container, provider);
        } else if (TabProperties.TAB_ACTION_BUTTON_DATA == propertyKey) {
            @Nullable TabActionButtonData data = model.get(TabProperties.TAB_ACTION_BUTTON_DATA);
            @Nullable
            TabActionListener tabActionListener = data == null ? null : data.tabActionListener;
            ImageView actionButton = view.findViewById(R.id.end_button);
            TabGridViewBinder.setNullableClickListener(tabActionListener, actionButton, model);

            if (data == null) return;

            Resources res = view.getResources();
            if (data.type == TabActionButtonType.OVERFLOW) {
                actionButton.setImageDrawable(
                        ResourcesCompat.getDrawable(
                                res, R.drawable.ic_more_vert_24dp, view.getContext().getTheme()));
            } else if (data.type == TabActionButtonType.CLOSE) {
                int closeButtonSize = (int) res.getDimension(R.dimen.tab_grid_close_button_size);
                Bitmap bitmap = BitmapFactory.decodeResource(res, R.drawable.btn_close);
                Bitmap.createScaledBitmap(bitmap, closeButtonSize, closeButtonSize, true);
                actionButton.setImageBitmap(bitmap);
            } else if (data.type == TabActionButtonType.SELECT) {
                // Intentional no-op. Handled as part of setTabActionState.
            } else {
                assert false : "Not reached";
            }
        } else if (TabProperties.TAB_CLICK_LISTENER == propertyKey) {
            TabGridViewBinder.setNullableClickListener(
                    model.get(TabProperties.TAB_CLICK_LISTENER), view, model);
        } else if (TabProperties.TAB_LONG_CLICK_LISTENER == propertyKey) {
            TabGridViewBinder.setNullableLongClickListener(
                    model.get(TabProperties.TAB_LONG_CLICK_LISTENER), view, model);
        } else if (TabProperties.TAB_CARD_LABEL_DATA == propertyKey) {
            // Ignore this data for tab card labels in selectable mode.
            updateTabCardLabel(view, /* tabCardLabelData= */ null);
=======
            ((TextView) fastView.findViewById(R.id.description)).setText(domain);
>>>>>>> chromium
        }
    }

    /**
<<<<<<< HEAD
     * Bind a closable tab to view.
     *
     * @param model The model to bind.
     * @param view The view to bind to.
     * @param propertyKey The property that changed.
     */
    private static void bindClosableListTab(
            PropertyModel model, ViewGroup view, @Nullable PropertyKey propertyKey) {
        bindListTab(model, view, propertyKey);

        if (TabProperties.IS_SELECTED == propertyKey
                || TabProperties.TAB_ACTION_BUTTON_DATA == propertyKey) {
            ImageView closeButton = view.findViewById(R.id.end_button);
            ImageViewCompat.setImageTintList(
                    closeButton,
                    TabUiThemeProvider.getActionButtonTintList(
                            view.getContext(),
                            model.get(TabProperties.IS_INCOGNITO),
                            /* isSelected= */ false));
        } else if (TabProperties.ACTION_BUTTON_DESCRIPTION_TEXT_RESOLVER == propertyKey) {
            TextResolver actionButtonDescriptionTextResolver =
                    model.get(TabProperties.ACTION_BUTTON_DESCRIPTION_TEXT_RESOLVER);
            CharSequence actionButtonDescriptionString =
                    TabCardViewBinderUtils.resolveNullSafe(
                            actionButtonDescriptionTextResolver, view.getContext());
            view.findViewById(R.id.end_button).setContentDescription(actionButtonDescriptionString);
        } else if (TabProperties.TAB_CARD_LABEL_DATA == propertyKey) {
            updateTabCardLabel(view, model.get(TabProperties.TAB_CARD_LABEL_DATA));
        }
    }

    /**
     * Bind color updates.
     *
     * @param view The root view of the item (either Selectable/ClosableTabListView).
     * @param isIncognito Whether the model is in incognito mode.
     * @param isSelected Whether the item is selected.
     */
    private static void updateColors(ViewGroup view, boolean isIncognito) {
        // TODO(crbug.com/40272756): isSelected is ignored as the selected row is only outlined not
        // colored so it should use the unselected color. This will be addressed in a fixit.

        // Shared by both classes, from tab_list_card_item.
        View contentView = view.findViewById(R.id.content_view);
        contentView.getBackground().mutate();
        final @ColorInt int backgroundColor =
                TabUiThemeUtils.getCardViewBackgroundColor(
                        view.getContext(), isIncognito, /* isSelected= */ false);
        ViewCompat.setBackgroundTintList(contentView, ColorStateList.valueOf(backgroundColor));

        final @ColorInt int textColor =
                TabUiThemeUtils.getTitleTextColor(
                        view.getContext(), isIncognito, /* isSelected= */ false);
        TextView titleView = view.findViewById(R.id.title);
        TextView descriptionView = view.findViewById(R.id.description);
        titleView.setTextColor(textColor);
        descriptionView.setTextColor(textColor);

        ImageView faviconView = view.findViewById(R.id.start_icon);
        if (faviconView.getBackground() == null) {
            faviconView.setBackgroundResource(R.drawable.list_item_icon_modern_bg);
        }
        faviconView.getBackground().mutate();
        final @ColorInt int faviconBackgroundColor =
                TabUiThemeUtils.getMiniThumbnailPlaceholderColor(
                        view.getContext(), isIncognito, /* isSelected= */ false);
        ViewCompat.setBackgroundTintList(
                faviconView, ColorStateList.valueOf(faviconBackgroundColor));
    }

    /**
=======
>>>>>>> chromium
     * Bind a selectable tab to view.
     * @param model The model to bind.
     * @param view The view to bind to.
     * @param propertyKey The property that changed.
     */
    public static void bindSelectableListTab(
            PropertyModel model, ViewGroup view, @Nullable PropertyKey propertyKey) {
        bindListTab(model, view, propertyKey);

        final int tabId = model.get(TabProperties.TAB_ID);
        final int defaultLevel = view.getResources().getInteger(R.integer.list_item_level_default);
        final int selectedLevel =
                view.getResources().getInteger(R.integer.list_item_level_selected);
        SelectableTabGridView selectableTabListView = view.findViewById(R.id.content_view);

        if (TabProperties.SELECTABLE_TAB_CLICKED_LISTENER == propertyKey) {
            View.OnClickListener onClickListener = v -> {
                model.get(TabProperties.SELECTABLE_TAB_CLICKED_LISTENER).run(tabId);
                selectableTabListView.onClick();
            };
            View.OnLongClickListener onLongClickListener = v -> {
                model.get(TabProperties.SELECTABLE_TAB_CLICKED_LISTENER).run(tabId);
                return selectableTabListView.onLongClick(selectableTabListView);
            };
            selectableTabListView.setOnClickListener(onClickListener);
            selectableTabListView.setOnLongClickListener(onLongClickListener);

            ImageView endButton = selectableTabListView.findViewById(R.id.end_button);
            endButton.setOnClickListener(onClickListener);
            endButton.setOnLongClickListener(onLongClickListener);
        } else if (TabProperties.TAB_SELECTION_DELEGATE == propertyKey) {
            assert model.get(TabProperties.TAB_SELECTION_DELEGATE) != null;
            selectableTabListView.setSelectionDelegate(
                    model.get(TabProperties.TAB_SELECTION_DELEGATE));
            selectableTabListView.setItem(tabId);
        } else if (TabProperties.IS_SELECTED == propertyKey) {
            boolean isSelected = model.get(TabProperties.IS_SELECTED);
            ImageView actionButton = (ImageView) view.findViewById(R.id.end_button);
            actionButton.getBackground().setLevel(isSelected ? selectedLevel : defaultLevel);
            DrawableCompat.setTintList(actionButton.getBackground().mutate(),
                    isSelected ? model.get(
                            TabProperties.SELECTABLE_TAB_ACTION_BUTTON_SELECTED_BACKGROUND)
                               : model.get(TabProperties.SELECTABLE_TAB_ACTION_BUTTON_BACKGROUND));

            // The check should be invisible if not selected.
            actionButton.getDrawable().setAlpha(isSelected ? 255 : 0);
            ApiCompatibilityUtils.setImageTintList(actionButton,
                    isSelected ? model.get(TabProperties.CHECKED_DRAWABLE_STATE_LIST) : null);
            if (isSelected) ((AnimatedVectorDrawableCompat) actionButton.getDrawable()).start();
        }
    }
<<<<<<< HEAD

    private static void setFavicon(View view, Drawable favicon) {
        ImageView faviconView = view.findViewById(R.id.start_icon);
        faviconView.setImageDrawable(favicon);
    }

    private static ColorStateList getCheckedDrawableColorStateList(
            Context context, boolean isIncognito) {
        return ColorStateList.valueOf(
                isIncognito
                        ? context.getColor(R.color.default_icon_color_dark)
                        : SemanticColorUtils.getDefaultIconColorInverse(context));
    }

    private static ColorStateList getBackgroundColorStateList(
            Context context, boolean isSelected, boolean isIncognito) {
        if (isSelected) {
            return ColorStateList.valueOf(
                    isIncognito
                            ? context.getColor(R.color.baseline_primary_80)
                            : SemanticColorUtils.getDefaultControlColorActive(context));
        } else {
            return AppCompatResources.getColorStateList(
                    context,
                    isIncognito
                            ? R.color.default_icon_color_light
                            : R.color.default_icon_color_tint_list);
        }
    }

    private static void updateTabCardLabel(
            ViewGroup view, @Nullable TabCardLabelData tabCardLabelData) {
        TabCardLabelView labelView = getOrSetupTabCardLabelView(view);
        labelView.setData(tabCardLabelData);
    }

    private static TabCardLabelView getOrSetupTabCardLabelView(ViewGroup view) {
        FrameLayout labelContainer = view.findViewById(R.id.before_description_container);
        if (labelContainer.getChildCount() > 0) {
            return (TabCardLabelView) labelContainer.getChildAt(0);
        }
        Context context = labelContainer.getContext();
        TabCardLabelView labelView =
                (TabCardLabelView)
                        LayoutInflater.from(context)
                                .inflate(R.layout.tab_card_label_layout, labelContainer, false);
        labelContainer.addView(labelView);

        Resources res = context.getResources();
        int marginEnd = res.getDimensionPixelSize(R.dimen.tab_card_label_list_margin_end);
        FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) labelView.getLayoutParams();
        params.setMarginEnd(marginEnd);
        labelView.setLayoutParams(params);

        // TODO(crbug.com/362306803): This is technically supposed to have elevation. However,
        // propagating clipToPadding=false and clipChildren=false all the way from
        // title_and_description_layout up to tab_list_card_item to make it look right is not worth
        // the complexity/risk of impacting other list UI when this UI is likely to be deprecated in
        // 2025.
        labelView.setElevation(0);
        return labelView;
    }
=======
>>>>>>> chromium
}
