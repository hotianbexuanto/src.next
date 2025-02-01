// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser;

<<<<<<< HEAD
import static android.app.Activity.OVERRIDE_TRANSITION_CLOSE;
import static android.app.Activity.OVERRIDE_TRANSITION_OPEN;
import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;
=======
import static org.chromium.chrome.browser.base.SplitCompatUtils.CHROME_SPLIT_NAME;
>>>>>>> chromium

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Configuration;
<<<<<<< HEAD
import android.os.Build;
import android.os.Build.VERSION;
import android.os.Build.VERSION_CODES;
=======
>>>>>>> chromium
import android.os.Bundle;

import androidx.annotation.CallSuper;
<<<<<<< HEAD
import androidx.annotation.ColorInt;
import androidx.annotation.IntDef;
import androidx.annotation.LayoutRes;
=======
>>>>>>> chromium
import androidx.annotation.Nullable;
import androidx.annotation.StyleRes;
import androidx.appcompat.app.AppCompatActivity;

import org.chromium.base.BuildInfo;
import org.chromium.base.ContextUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.base.supplier.OneshotSupplierImpl;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.base.SplitChromeApplication;
import org.chromium.chrome.browser.base.SplitCompatUtils;
import org.chromium.chrome.browser.flags.CachedFeatureFlags;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.flags.ChromeSwitches;
import org.chromium.chrome.browser.language.GlobalAppLocaleController;
import org.chromium.chrome.browser.night_mode.GlobalNightModeStateProviderHolder;
import org.chromium.chrome.browser.night_mode.NightModeStateProvider;
import org.chromium.chrome.browser.night_mode.NightModeUtils;
<<<<<<< HEAD
import org.chromium.chrome.browser.ui.edge_to_edge.EdgeToEdgeUtils;
import org.chromium.components.browser_ui.edge_to_edge.EdgeToEdgeManager;
import org.chromium.components.browser_ui.edge_to_edge.EdgeToEdgeStateProvider;
import org.chromium.components.browser_ui.edge_to_edge.EdgeToEdgeSystemBarColorHelper;
import org.chromium.components.browser_ui.edge_to_edge.SystemBarColorHelper;
import org.chromium.components.browser_ui.edge_to_edge.layout.EdgeToEdgeLayoutCoordinator;
import org.chromium.components.browser_ui.styles.SemanticColorUtils;
import org.chromium.components.browser_ui.util.AutomotiveUtils;
import org.chromium.ui.InsetObserver;
import org.chromium.ui.base.ImmutableWeakReference;
import org.chromium.ui.display.DisplaySwitches;
import org.chromium.ui.display.DisplayUtil;
=======
import org.chromium.chrome.browser.ui.theme.ColorDelegateImpl;
>>>>>>> chromium
import org.chromium.ui.modaldialog.ModalDialogManager;
import org.chromium.ui.modaldialog.ModalDialogManagerHolder;
import org.chromium.ui.util.AttrUtils;
import org.chromium.ui.util.XrUtils;

/**
 * A subclass of {@link AppCompatActivity} that maintains states and objects applied to all
 * activities in {@link ChromeApplication} (e.g. night mode).
 */
public class ChromeBaseAppCompatActivity extends AppCompatActivity
        implements NightModeStateProvider.Observer, ModalDialogManagerHolder {
    private final ObservableSupplierImpl<ModalDialogManager> mModalDialogManagerSupplier =
            new ObservableSupplierImpl<>();
    protected final OneshotSupplierImpl<SystemBarColorHelper> mSystemBarColorHelperSupplier =
            new OneshotSupplierImpl<>();

    private NightModeStateProvider mNightModeStateProvider;
<<<<<<< HEAD
    private LinkedHashSet<Integer> mThemeResIds = new LinkedHashSet<>();
    private ServiceTracingProxyProvider mServiceTracingProxyProvider;
    private InsetObserver mInsetObserver;
    private EdgeToEdgeStateProvider mEdgeToEdgeStateProvider;
    private EdgeToEdgeManager mEdgeToEdgeManager;
    private EdgeToEdgeLayoutCoordinator mEdgeToEdgeLayoutCoordinator;
=======
    private @StyleRes int mThemeResId;
>>>>>>> chromium

    @Override
    protected void attachBaseContext(Context newBase) {
        super.attachBaseContext(newBase);

        // Make sure the "chrome" split is loaded before checking if ClassLoaders are equal.
        SplitChromeApplication.finishPreload(CHROME_SPLIT_NAME);
        if (!ChromeBaseAppCompatActivity.class.getClassLoader().equals(
                    ContextUtils.getApplicationContext().getClassLoader())) {
            // This should only happen on Android O. See crbug.com/1146745 for more info.
            throw new IllegalStateException("ClassLoader mismatch detected.");
        }

        mNightModeStateProvider = createNightModeStateProvider();

        Configuration config = new Configuration();
        // Pre-Android O, fontScale gets initialized to 1 in the constructor. Set it to 0 so
        // that applyOverrideConfiguration() does not interpret it as an overridden value.
        // https://crbug.com/834191
        config.fontScale = 0;
        // NightMode and other applyOverrides must be done before onCreate in attachBaseContext.
        // https://crbug.com/1139760
        if (applyOverrides(newBase, config)) applyOverrideConfiguration(config);
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
<<<<<<< HEAD
        BundleUtils.restoreLoadedSplits(savedInstanceState);

        mEdgeToEdgeStateProvider = new EdgeToEdgeStateProvider(getWindow());

=======
        getSupportFragmentManager().setFragmentFactory(SplitCompatUtils.createFragmentFactory());
>>>>>>> chromium
        mModalDialogManagerSupplier.set(createModalDialogManager());

        initializeNightModeStateProvider();
        mNightModeStateProvider.addObserver(this);
        super.onCreate(savedInstanceState);
        applyThemeOverlays();

        // Activity level locale overrides must be done in onCreate.
        GlobalAppLocaleController.getInstance().maybeOverrideContextConfig(this);
<<<<<<< HEAD

        setDefaultTaskDescription();

        mInsetObserver = createInsetObserver();
        if (EdgeToEdgeUtils.isEdgeToEdgeEverywhereEnabled()) {
            mEdgeToEdgeLayoutCoordinator = ensureEdgeToEdgeLayoutCoordinator();
        }
        // TODO(crbug.com/393195226): Cleanup EdgeToEdgeManager and EdgeToEdgeSystemBarColorHelper
        //  when edge to edge supports status bar coloring in tabbed mode.
        mEdgeToEdgeManager =
                new EdgeToEdgeManager(
                        this,
                        mEdgeToEdgeStateProvider,
                        createSystemBarColorHelperSupplier(),
                        shouldDrawEdgeToEdgeOnCreate(),
                        EdgeToEdgeUtils.isEdgeToEdgeEverywhereEnabled());

        if (EdgeToEdgeUtils.isEdgeToEdgeEverywhereEnabled()) {
            initializeSystemBarColors();
        }

        if (VERSION.SDK_INT >= VERSION_CODES.UPSIDE_DOWN_CAKE
                && ChromeFeatureList.sEnableXAxisActivityTransition.isEnabled()) {
            overrideActivityTransition(
                    OVERRIDE_TRANSITION_OPEN,
                    R.anim.shared_x_axis_open_enter,
                    R.anim.shared_x_axis_open_exit,
                    SemanticColorUtils.getDefaultBgColor(this));

            overrideActivityTransition(
                    OVERRIDE_TRANSITION_CLOSE,
                    R.anim.shared_x_axis_close_enter,
                    R.anim.shared_x_axis_close_exit,
                    SemanticColorUtils.getDefaultBgColor(this));
        }
    }

    /**
     * Returns a one-shot supplier for the {@link SystemBarColorHelper} that's appropriate for the
     * activity.
     */
    protected OneshotSupplier<SystemBarColorHelper> createSystemBarColorHelperSupplier() {
        if (mEdgeToEdgeLayoutCoordinator != null) {
            mSystemBarColorHelperSupplier.set(mEdgeToEdgeLayoutCoordinator);
        }
        return mSystemBarColorHelperSupplier;
    }

    /** Set the default colors of the system bars for this activity. */
    protected void initializeSystemBarColors() {
        // TODO(crbug.com/379174458): Set color from Theme.
        final @ColorInt int defaultBgColor = SemanticColorUtils.getDefaultBgColor(this);
        @ColorInt
        int defaultStatusBarColor =
                AttrUtils.resolveColor(getTheme(), android.R.attr.statusBarColor);
        @ColorInt
        int defaultNavigationBarColor =
                AttrUtils.resolveColor(getTheme(), android.R.attr.navigationBarColor);
        // Check if defaultStatusBarColor is transparent
        defaultStatusBarColor =
                (defaultStatusBarColor != 0) ? defaultStatusBarColor : defaultBgColor;
        defaultNavigationBarColor =
                (defaultNavigationBarColor != 0) ? defaultNavigationBarColor : defaultBgColor;

        EdgeToEdgeSystemBarColorHelper edgeToEdgeSystemBarColorHelper =
                mEdgeToEdgeManager.getEdgeToEdgeSystemBarColorHelper();
        edgeToEdgeSystemBarColorHelper.setStatusBarColor(defaultStatusBarColor);
        edgeToEdgeSystemBarColorHelper.setNavigationBarColor(defaultNavigationBarColor);
=======
>>>>>>> chromium
    }

    @Override
    protected void onDestroy() {
        mNightModeStateProvider.removeObserver(this);
        if (mModalDialogManagerSupplier.get() != null) {
            mModalDialogManagerSupplier.get().destroy();
            mModalDialogManagerSupplier.set(null);
        }
<<<<<<< HEAD
        if (mEdgeToEdgeLayoutCoordinator != null) {
            mEdgeToEdgeLayoutCoordinator.destroy();
            mEdgeToEdgeLayoutCoordinator = null;
        }
        mEdgeToEdgeManager.destroy();
=======
>>>>>>> chromium
        super.onDestroy();
    }

    @Override
    public void setTheme(@StyleRes int resid) {
        super.setTheme(resid);
        mThemeResId = resid;
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        NightModeUtils.updateConfigurationForNightMode(
                this, mNightModeStateProvider.isInNightMode(), newConfig, mThemeResId);
    }

    // Implementation of ModalDialogManagerHolder
    /**
     * @return The {@link ModalDialogManager} that manages the display of modal dialogs (e.g.
     *         JavaScript dialogs).
     */
    @Override
    public ModalDialogManager getModalDialogManager() {
        // TODO(jinsukkim): Remove this method in favor of getModalDialogManagerSupplier().
        return getModalDialogManagerSupplier().get();
    }

    /**
     * Returns the supplier of {@link ModalDialogManager} that manages the display of modal dialogs.
     */
    public ObservableSupplier<ModalDialogManager> getModalDialogManagerSupplier() {
        return mModalDialogManagerSupplier;
    }

    /**
     * Creates a {@link ModalDialogManager} for this class. Subclasses that need one should override
     * this method.
     */
    @Nullable
    protected ModalDialogManager createModalDialogManager() {
        return null;
    }

<<<<<<< HEAD
    @VisibleForTesting
    public EdgeToEdgeLayoutCoordinator ensureEdgeToEdgeLayoutCoordinator() {
        if (mEdgeToEdgeLayoutCoordinator == null) {
            mEdgeToEdgeLayoutCoordinator = new EdgeToEdgeLayoutCoordinator(this, mInsetObserver);
            mEdgeToEdgeLayoutCoordinator.setIsDebugging(
                    EdgeToEdgeUtils.isEdgeToEdgeEverywhereDebugging());
        }
        return mEdgeToEdgeLayoutCoordinator;
    }

    /** Returns whether this activity should draw its content edge-to-edge by default. */
    protected boolean shouldDrawEdgeToEdgeOnCreate() {
        return EdgeToEdgeUtils.isEdgeToEdgeEverywhereEnabled();
    }

    /**
     * Returns true if this activity should wrap its content within an edge-to-edge layout, allowing
     * it to draw edge-to-edge while still automatically fitting its content within the system
     * window insets.
     */
    protected boolean wrapContentWithEdgeToEdgeLayout() {
        return EdgeToEdgeUtils.isEdgeToEdgeEverywhereEnabled();
    }

=======
>>>>>>> chromium
    /**
     * Called during {@link #attachBaseContext(Context)} to allow configuration overrides to be
     * applied. If this methods return true, the overrides will be applied using
     * {@link #applyOverrideConfiguration(Configuration)}.
     * @param baseContext The base {@link Context} attached to this class.
     * @param overrideConfig The {@link Configuration} that will be passed to
     *                       @link #applyOverrideConfiguration(Configuration)} if necessary.
     * @return True if any configuration overrides were applied, and false otherwise.
     */
    @CallSuper
    protected boolean applyOverrides(Context baseContext, Configuration overrideConfig) {
<<<<<<< HEAD
        applyOverridesForAutomotive(baseContext, overrideConfig);
        applyOverridesForXr(baseContext, overrideConfig);
=======
>>>>>>> chromium
        return NightModeUtils.applyOverridesForNightMode(
                getNightModeStateProvider(), overrideConfig);
    }

<<<<<<< HEAD
    @VisibleForTesting
    static void applyOverridesForAutomotive(Context baseContext, Configuration overrideConfig) {
        if (BuildInfo.getInstance().isAutomotive) {
            DisplayUtil.scaleUpConfigurationForAutomotive(baseContext, overrideConfig);

            // Enable web ui scaling for automotive devices.
            CommandLine.getInstance()
                    .appendSwitch(DisplaySwitches.AUTOMOTIVE_WEB_UI_SCALE_UP_ENABLED);
        }
    }

    @VisibleForTesting
    static void applyOverridesForXr(Context baseContext, Configuration overrideConfig) {
        if (XrUtils.isXrDevice()) {
            DisplayUtil.scaleUpConfigurationForXr(baseContext, overrideConfig);

            // Enable web ui scaling for immersive devices.
            CommandLine.getInstance().appendSwitch(DisplaySwitches.XR_WEB_UI_SCALE_UP_ENABLED);
        }
    }

=======
>>>>>>> chromium
    /**
     * @return The {@link NightModeStateProvider} that provides the state of night mode.
     */
    protected final NightModeStateProvider getNightModeStateProvider() {
        return mNightModeStateProvider;
    }

    /**
     * @return The {@link NightModeStateProvider} that provides the state of night mode in the scope
     *         of this class.
     */
    protected NightModeStateProvider createNightModeStateProvider() {
        return GlobalNightModeStateProviderHolder.getInstance();
    }

    /**
     * Initializes the initial night mode state. This will be called at the beginning of
     * {@link #onCreate(Bundle)} so that the correct theme can be applied for the initial night mode
     * state.
     */
    protected void initializeNightModeStateProvider() {}

    /**
     * Apply theme overlay to this activity class.
     */
    @CallSuper
    protected void applyThemeOverlays() {
        setTheme(R.style.ColorOverlay_ChromiumAndroid);

<<<<<<< HEAD
        DeferredStartupHandler.getInstance()
                .addDeferredTask(
                        () -> {
                            // #registerSyntheticFieldTrial requires native.
                            boolean isDynamicColorAvailable =
                                    DynamicColors.isDynamicColorAvailable();
                            RecordHistogram.recordBooleanHistogram(
                                    "Android.DynamicColors.IsAvailable", isDynamicColorAvailable);
                            UmaSessionStats.registerSyntheticFieldTrial(
                                    "IsDynamicColorAvailable",
                                    isDynamicColorAvailable ? "Enabled" : "Disabled");
                        });

        // TODO(https://crbug.com/392634251): Explore setting elegantTextHeight to 'true' on older
        // OS versions.
        if (ChromeFeatureList.sAndroidElegantTextHeight.isEnabled()
                && Build.VERSION.SDK_INT >= VERSION_CODES.TIRAMISU) {
            int elegantTextHeightOverlay = R.style.ThemeOverlay_BrowserUI_ElegantTextHeight;
            getTheme().applyStyle(elegantTextHeightOverlay, true);
            mThemeResIds.add(elegantTextHeightOverlay);
=======
        if (CachedFeatureFlags.isEnabled(ChromeFeatureList.DYNAMIC_COLOR_ANDROID)) {
            new ColorDelegateImpl().applyDynamicColorsIfAvailable(this);
>>>>>>> chromium
        }
        // Try to enable browser overscroll when content overscroll is enabled for consistency. This
        // needs to be in a cached feature because activity startup happens before native is
        // initialized. Unfortunately content overscroll is read in renderer threads, and these two
        // are not synchronized. Typically the first time overscroll is enabled, the following will
        // use the old value and then content will pick up the enabled value, causing one execution
        // of inconsistency.
        if (BuildInfo.isAtLeastS()
                && !CachedFeatureFlags.isEnabled(ChromeFeatureList.ELASTIC_OVERSCROLL)) {
            setTheme(R.style.ThemeOverlay_DisableOverscroll);
        }

        if (EdgeToEdgeUtils.isEdgeToEdgeEverywhereEnabled()
                || CommandLine.getInstance()
                        .hasSwitch(ChromeSwitches.DISABLE_OPT_OUT_EDGE_TO_EDGE)) {
            int optOutEdgeToEdge = R.style.ThemeOverlay_BrowserUI_OptOutEdgeToEdge;
            getTheme().applyStyle(optOutEdgeToEdge, true);
            mThemeResIds.add(optOutEdgeToEdge);
        }
    }

    // NightModeStateProvider.Observer implementation.
    @Override
    public void onNightModeStateChanged() {
        if (!isFinishing()) recreate();
    }

    /**
     * Required to make preference fragments use InMemorySharedPreferences in tests.
     */
    @Override
    public SharedPreferences getSharedPreferences(String name, int mode) {
        return ContextUtils.getApplicationContext().getSharedPreferences(name, mode);
    }
<<<<<<< HEAD

    // Note that we do not need to (and can't) override getSystemService(Class<T>) as internally
    // that just gets the name of the Service and calls getSystemService(String) for backwards
    // compatibility with overrides like this one.
    @Override
    public Object getSystemService(String name) {
        Object service = super.getSystemService(name);
        if (mServiceTracingProxyProvider != null) {
            mServiceTracingProxyProvider.traceSystemServices();
        }
        return service;
    }

    /**
     * Set the back button in the automotive toolbar to perform an Android system level back.
     *
     * This toolbar will be used to do things like exit fullscreen YouTube videos because AAOS/cars
     * don't have a built in back button
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            getOnBackPressedDispatcher().onBackPressed();
            return true;
        }
        return false;
    }

    @Override
    public void setContentView(@LayoutRes int layoutResID) {
        if (BuildInfo.getInstance().isAutomotive
                && getAutomotiveToolbarImplementation()
                        == AutomotiveToolbarImplementation.WITH_TOOLBAR_VIEW) {
            super.setContentView(AutomotiveUtils.getAutomotiveLayoutWithBackButtonToolbar(this));
            setAutomotiveToolbarBackButtonAction();
            ViewStub stub = findViewById(R.id.original_layout);
            stub.setLayoutResource(layoutResID);
            stub.inflate();
        } else if (wrapContentWithEdgeToEdgeLayout()) {
            FrameLayout baseLayout = new FrameLayout(this);
            super.setContentView(ensureEdgeToEdgeLayoutCoordinator().wrapContentView(baseLayout));
            getLayoutInflater().inflate(layoutResID, baseLayout, /* attachToRoot= */ true);
        } else {
            super.setContentView(layoutResID);
        }
    }

    @Override
    public void setContentView(View view) {
        if (BuildInfo.getInstance().isAutomotive
                && getAutomotiveToolbarImplementation()
                        == AutomotiveToolbarImplementation.WITH_TOOLBAR_VIEW) {
            super.setContentView(AutomotiveUtils.getAutomotiveLayoutWithBackButtonToolbar(this));
            setAutomotiveToolbarBackButtonAction();
            LinearLayout linearLayout = findViewById(R.id.automotive_base_linear_layout);
            linearLayout.addView(view, LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
        } else if (wrapContentWithEdgeToEdgeLayout()) {
            super.setContentView(ensureEdgeToEdgeLayoutCoordinator().wrapContentView(view));
        } else {
            super.setContentView(view);
        }
    }

    @Override
    public void setContentView(View view, ViewGroup.LayoutParams params) {
        if (BuildInfo.getInstance().isAutomotive
                && getAutomotiveToolbarImplementation()
                        == AutomotiveToolbarImplementation.WITH_TOOLBAR_VIEW) {
            super.setContentView(AutomotiveUtils.getAutomotiveLayoutWithBackButtonToolbar(this));
            setAutomotiveToolbarBackButtonAction();
            LinearLayout linearLayout = findViewById(R.id.automotive_base_linear_layout);
            linearLayout.setLayoutParams(params);
            linearLayout.addView(view, LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
        } else if (wrapContentWithEdgeToEdgeLayout()) {
            super.setContentView(ensureEdgeToEdgeLayoutCoordinator().wrapContentView(view, params));
        } else {
            super.setContentView(view, params);
        }
    }

    @Override
    public void addContentView(View view, ViewGroup.LayoutParams params) {
        if (BuildInfo.getInstance().isAutomotive
                && params.width == MATCH_PARENT
                && params.height == MATCH_PARENT) {
            ViewGroup automotiveLayout =
                    (ViewGroup)
                            getLayoutInflater()
                                    .inflate(
                                            AutomotiveUtils
                                                    .getAutomotiveLayoutWithBackButtonToolbar(this),
                                            null);
            super.addContentView(
                    automotiveLayout, new LinearLayout.LayoutParams(MATCH_PARENT, MATCH_PARENT));
            setAutomotiveToolbarBackButtonAction();
            automotiveLayout.addView(view, params);
        } else if (wrapContentWithEdgeToEdgeLayout()) {
            super.setContentView(ensureEdgeToEdgeLayoutCoordinator().wrapContentView(view, params));
        } else {
            super.addContentView(view, params);
        }
    }

    protected int getAutomotiveToolbarImplementation() {
        int activityStyle = -1;
        try {
            activityStyle =
                    getPackageManager().getActivityInfo(getComponentName(), 0).getThemeResource();
        } catch (Exception e) {
            e.printStackTrace();
        }
        if (activityStyle == R.style.Theme_Chromium_DialogWhenLarge) {
            return AutomotiveToolbarImplementation.NONE;
        } else {
            return AutomotiveToolbarImplementation.WITH_TOOLBAR_VIEW;
        }
    }

    /**
     * Returns the {@link EdgeToEdgeStateProvider} for checking and requesting changes to the
     * edge-to-edge state.
     */
    protected EdgeToEdgeStateProvider getEdgeToEdgeStateProvider() {
        return mEdgeToEdgeStateProvider;
    }

    /** Returns the {@link EdgeToEdgeManager} for access to core edge-to-edge logic. */
    @VisibleForTesting
    public EdgeToEdgeManager getEdgeToEdgeManager() {
        return mEdgeToEdgeManager;
    }

    /** Returns the {@link InsetObserver} for observing changes to the system insets. */
    protected InsetObserver getInsetObserver() {
        assert mInsetObserver != null
                : "The inset observer should not be accessed before being initialized.";
        return mInsetObserver;
    }

    private InsetObserver createInsetObserver() {
        return new InsetObserver(
                new ImmutableWeakReference<>(getWindow().getDecorView().getRootView()));
    }

    private void setAutomotiveToolbarBackButtonAction() {
        Toolbar backButtonToolbarForAutomotive = findViewById(R.id.back_button_toolbar);
        if (backButtonToolbarForAutomotive != null) {
            backButtonToolbarForAutomotive.setNavigationOnClickListener(
                    backButtonClick -> {
                        getOnBackPressedDispatcher().onBackPressed();
                    });
        }
    }
=======
>>>>>>> chromium
}
