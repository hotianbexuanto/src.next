// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.tab;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Point;
import android.graphics.Rect;
import android.view.Display;

import androidx.annotation.Nullable;

import org.chromium.base.ApplicationStatus;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.content_public.browser.WebContents;
import org.chromium.ui.base.DeviceFormFactor;
import org.chromium.ui.base.WindowAndroid;
import org.chromium.ui.display.DisplayAndroidManager;

<<<<<<< HEAD
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/** Collection of utility methods that operates on Tab. */
=======
/**
 * Collection of utility methods that operates on Tab.
 */
>>>>>>> chromium
public class TabUtils {
    private static final String REQUEST_DESKTOP_SCREEN_WIDTH_PARAM = "screen_width_dp";

    // Do not instantiate this class.
    private TabUtils() {}

    /**
     * @return {@link Activity} associated with the given tab.
     */
    @Nullable
    public static Activity getActivity(Tab tab) {
        WebContents webContents = tab != null ? tab.getWebContents() : null;
        if (webContents == null || webContents.isDestroyed()) return null;
        WindowAndroid window = webContents.getTopLevelNativeWindow();
        return window != null ? window.getActivity().get() : null;
    }

    /**
     * Provides an estimate of the contents size.
     *
     * The estimate is likely to be incorrect. This is not a problem, as the aim
     * is to avoid getting a different layout and resources than needed at
     * render time.
     * @param context The application context.
     * @return The estimated prerender size in pixels.
     */
    public static Rect estimateContentSize(Context context) {
        // The size is estimated as:
        // X = screenSizeX
        // Y = screenSizeY - top bar - bottom bar - custom tabs bar
        // The bounds rectangle includes the bottom bar and the custom tabs bar as well.
        Rect screenBounds = new Rect();
        Point screenSize = new Point();
        Display display = DisplayAndroidManager.getDefaultDisplayForContext(context);
        display.getSize(screenSize);
        Resources resources = context.getResources();
        int statusBarId = resources.getIdentifier("status_bar_height", "dimen", "android");
        try {
            screenSize.y -= resources.getDimensionPixelSize(statusBarId);
        } catch (Resources.NotFoundException e) {
            // Nothing, this is just a best effort estimate.
        }
        screenBounds.set(0,
                resources.getDimensionPixelSize(R.dimen.custom_tabs_control_container_height),
                screenSize.x, screenSize.y);
        return screenBounds;
    }

    public static Tab fromWebContents(WebContents webContents) {
        return TabImplJni.get().fromWebContents(webContents);
    }

    /**
     * Call when tab need to switch user agent between desktop and mobile.
     * @param tab The tab to be switched the user agent.
     * @param switchToDesktop Whether switching the user agent to desktop.
     * @param forcedByUser Whether this was triggered by users action.
     */
    public static void switchUserAgent(Tab tab, boolean switchToDesktop, boolean forcedByUser) {
        final boolean reloadOnChange = !tab.isNativePage();
        tab.getWebContents().getNavigationController().setUseDesktopUserAgent(
                switchToDesktop, reloadOnChange);
        if (forcedByUser) ((TabImpl) tab).setUserForcedUserAgent();
    }

    /**
     * Check if the tab is large enough for displaying desktop sites. This method will only check
     * for tablets, if the device is a phone, will return false regardless of tab size.
     * @param tab The tab to be checked if the size is large enough for desktop site.
     * @return Whether or not the screen size is large enough for desktop sites.
     */
    public static boolean isTabLargeEnoughForDesktopSite(Tab tab) {
        if (!DeviceFormFactor.isNonMultiDisplayContextOnTablet(tab.getContext())) {
            // The device is a phone, do not check the tab size.
            return false;
        }
        Activity activity = ((TabImpl) tab).getActivity();
        if (activity == null) {
            // It is possible that we are in custom tabs or tests, and need to access the activity
            // differently.
            activity = ApplicationStatus.getLastTrackedFocusedActivity();
            if (activity == null) return false;
        }
        int windowWidth = activity.getWindow().getDecorView().getWidth();
        int minWidthForDesktopSite = ChromeFeatureList.getFieldTrialParamByFeatureAsInt(
                ChromeFeatureList.REQUEST_DESKTOP_SITE_FOR_TABLETS,
                REQUEST_DESKTOP_SCREEN_WIDTH_PARAM,
                /* Set a very large size as default to serve as a disabled screen width. */ 4096);

<<<<<<< HEAD
    /**
     * Check if Request Desktop Site global setting is enabled.
     * @param profile The profile of the tab.
     *        Content settings have separate storage for incognito profiles.
     *        For site-specific exceptions the actual profile is needed.
     * @return Whether the desktop site should be requested.
     */
    public static boolean isDesktopSiteGlobalEnabled(Profile profile) {
        return WebsitePreferenceBridge.isCategoryEnabled(
                profile, ContentSettingsType.REQUEST_DESKTOP_SITE);
    }

    /**
     * Check if Request Desktop Site global setting is enabled.
     * @param profile The profile of the tab.
     *        Content settings have separate storage for incognito profiles.
     *        For site-specific exceptions the actual profile is needed.
     * @param url The URL for the current web content.
     * @return Whether the desktop site should be requested.
     */
    public static boolean isDesktopSiteEnabled(Profile profile, GURL url) {
        return WebsitePreferenceBridge.getContentSetting(
                        profile, ContentSettingsType.REQUEST_DESKTOP_SITE, url, url)
                == ContentSettingValues.ALLOW;
    }

    /**
     * Return aspect ratio for grid tab card based on form factor and orientation.
     * @param context - Context of the application.
     * @param browserControlsStateProvider - For getting browser controls height.
     * @return Aspect ratio for the grid tab card.
     */
    public static float getTabThumbnailAspectRatio(
            Context context, BrowserControlsStateProvider browserControlsStateProvider) {
        if (context.getResources().getConfiguration().orientation
                == Configuration.ORIENTATION_LANDSCAPE) {
            assert browserControlsStateProvider != null;
            int browserControlsHeightDp =
                    (browserControlsStateProvider == null)
                            ? 0
                            : Math.round(
                                    (float) browserControlsStateProvider.getTopControlsHeight()
                                            / context.getResources().getDisplayMetrics().density);
            int horizontalAutomotiveToolbarHeightDp =
                    AutomotiveUtils.getHorizontalAutomotiveToolbarHeightDp(context);
            int verticalAutomotiveToolbarWidthDp =
                    AutomotiveUtils.getVerticalAutomotiveToolbarWidthDp(context);
            DimensionCompat dimensionCompat = getDimensionCompat(context);
            float windowWidthDp = getWindowWidthDp(dimensionCompat, context);
            float windowHeightDp = getWindowHeightExcludingSystemBarsDp(dimensionCompat, context);
            // This should match the aspect ratio of a Tab's content area.
            return (windowWidthDp - verticalAutomotiveToolbarWidthDp)
                    / (windowHeightDp
                            - browserControlsHeightDp
                            - horizontalAutomotiveToolbarHeightDp);
        }
        // This is an experimentally determined value.
        return PORTRAIT_THUMBNAIL_ASPECT_RATIO;
    }

    private static float getWindowWidthDp(DimensionCompat compat, Context context) {
        return compat.getWindowWidth() / context.getResources().getDisplayMetrics().density;
    }

    private static float getWindowHeightExcludingSystemBarsDp(
            DimensionCompat compat, Context context) {
        return (compat.getWindowHeight() - compat.getNavbarHeight() - compat.getStatusBarHeight())
                / context.getResources().getDisplayMetrics().density;
    }

    private static DimensionCompat getDimensionCompat(Context context) {
        // (TODO: crbug.com/351854698) Pass activity context instead.
        Activity activity = ContextUtils.activityFromContext(context);
        assert activity != null : "Activity from context should not be null for this class.";
        return DimensionCompat.create(activity, null);
    }

    /**
     * Derive grid card height based on width, expected thumbnail aspect ratio and margins.
     *
     * @param cardWidthPx width of the card
     * @param context to derive view margins
     * @param browserControlsStateProvider - For getting browser controls height.
     * @return computed card height.
     */
    public static int deriveGridCardHeight(
            int cardWidthPx,
            Context context,
            BrowserControlsStateProvider browserControlsStateProvider) {
        int tabThumbnailHeight =
                (int)
                        ((cardWidthPx - getThumbnailWidthDiff(context))
                                / getTabThumbnailAspectRatio(
                                        context, browserControlsStateProvider));
        int cardHeightPx = tabThumbnailHeight + getThumbnailHeightDiff(context);
        return cardHeightPx;
    }

    /**
     * Derive thumbnail size based on parent card size.
     * @param gridCardSize size of parent card.
     * @param context to derive view margins.
     * @return computed width and height of thumbnail.
     */
    public static Size deriveThumbnailSize(@NonNull Size gridCardSize, @NonNull Context context) {
        int thumbnailWidth = gridCardSize.getWidth() - getThumbnailWidthDiff(context);
        int thumbnailHeight = gridCardSize.getHeight() - getThumbnailHeightDiff(context);
        return new Size(thumbnailWidth, thumbnailHeight);
    }

    /**
     * Update the {@link Bitmap} and @{@link Matrix} of ImageView. The drawable is scaled by a
     * matrix to be scaled to larger of the two dimensions of {@code destinationSize}, then
     * top-center aligned.
     *
     * @param view The {@link ImageView} to update.
     * @param drawable The {@link Drawable} to set in the view and scale.
     * @param destinationSize The desired {@link Size} of the drawable.
     */
    public static void setDrawableAndUpdateImageMatrix(
            ImageView view, Drawable drawable, Size destinationSize) {
        if (BuildInfo.getInstance().isAutomotive) {
            if (drawable instanceof BitmapDrawable bitmapDrawable) {
                Bitmap bitmap = bitmapDrawable.getBitmap();
                assert bitmap != null;
                bitmap.setDensity(
                        DisplayUtil.getUiDensityForAutomotive(
                                view.getContext(), bitmap.getDensity()));
            }
        }
        view.setImageDrawable(drawable);
        int newWidth = destinationSize == null ? 0 : destinationSize.getWidth();
        int newHeight = destinationSize == null ? 0 : destinationSize.getHeight();
        if (newWidth <= 0
                || newHeight <= 0
                || (newWidth == drawable.getIntrinsicWidth()
                        && newHeight == drawable.getIntrinsicHeight())) {
            view.setScaleType(ScaleType.FIT_CENTER);
            return;
        }

        final Matrix m = new Matrix();
        final float scale =
                Math.max(
                        (float) newWidth / drawable.getIntrinsicWidth(),
                        (float) newHeight / drawable.getIntrinsicHeight());
        m.setScale(scale, scale);

        /*
         * Bitmap is top-left aligned by default. We want to translate the image to be horizontally
         * center-aligned. |destination width - scaled width| is the width that is out of view
         * bounds. We need to translate the drawable (to left) by half of this distance.
         */
        final int xOffset = (int) ((newWidth - (drawable.getIntrinsicWidth() * scale)) / 2);
        m.postTranslate(xOffset, 0);

        view.setScaleType(ScaleType.MATRIX);
        view.setImageMatrix(m);
    }

    private static int getThumbnailHeightDiff(Context context) {
        final int tabGridCardMargin = (int) TabUiThemeProvider.getTabGridCardMargin(context);
        final int thumbnailMargin =
                (int) context.getResources().getDimension(R.dimen.tab_grid_card_thumbnail_margin);
        int heightMargins = (2 * tabGridCardMargin) + thumbnailMargin;
        final int titleHeight =
                (int) context.getResources().getDimension(R.dimen.tab_grid_card_header_height);
        return titleHeight + heightMargins;
    }

    private static int getThumbnailWidthDiff(Context context) {
        final int tabGridCardMargin = (int) TabUiThemeProvider.getTabGridCardMargin(context);
        final int thumbnailMargin =
                (int) context.getResources().getDimension(R.dimen.tab_grid_card_thumbnail_margin);
        return 2 * (tabGridCardMargin + thumbnailMargin);
=======
        return minWidthForDesktopSite <= windowWidth;
>>>>>>> chromium
    }
}
