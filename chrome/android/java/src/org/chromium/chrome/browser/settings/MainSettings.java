// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.settings;

import android.content.Context;
import android.content.Intent;
<<<<<<< HEAD
import android.content.pm.PackageManager;
=======
>>>>>>> chromium
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;
import androidx.preference.Preference;
import androidx.preference.PreferenceFragmentCompat;

import org.chromium.base.ContextUtils;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.datareduction.settings.DataReductionPreferenceFragment;
import org.chromium.chrome.browser.homepage.HomepageManager;
import org.chromium.chrome.browser.net.spdyproxy.DataReductionProxySettings;
import org.chromium.chrome.browser.night_mode.NightModeUtils;
import org.chromium.chrome.browser.password_check.PasswordCheck;
import org.chromium.chrome.browser.password_check.PasswordCheckFactory;
import org.chromium.chrome.browser.password_manager.ManagePasswordsReferrer;
import org.chromium.chrome.browser.password_manager.PasswordManagerLauncher;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.search_engines.TemplateUrlServiceFactory;
<<<<<<< HEAD
=======
import org.chromium.chrome.browser.signin.SyncConsentActivityLauncherImpl;
>>>>>>> chromium
import org.chromium.chrome.browser.signin.services.IdentityServicesProvider;
import org.chromium.chrome.browser.signin.services.SigninManager;
import org.chromium.chrome.browser.sync.SyncService;
import org.chromium.chrome.browser.sync.settings.ManageSyncSettings;
import org.chromium.chrome.browser.sync.settings.SignInPreference;
<<<<<<< HEAD
import org.chromium.chrome.browser.sync.settings.SyncSettingsUtils;
import org.chromium.chrome.browser.tab_group_sync.TabGroupSyncFeatures;
import org.chromium.chrome.browser.toolbar.ToolbarPositionController;
import org.chromium.chrome.browser.toolbar.adaptive.AdaptiveToolbarStatePredictor;
import org.chromium.chrome.browser.tracing.settings.DeveloperSettings;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.browser.ui.settings_promo_card.SettingsPromoCardPreference;
import org.chromium.chrome.browser.ui.signin.SignOutCoordinator;
import org.chromium.components.autofill.AutofillFeatures;
=======
import org.chromium.chrome.browser.sync.settings.SyncPromoPreference;
import org.chromium.chrome.browser.sync.settings.SyncPromoPreference.State;
import org.chromium.chrome.browser.sync.settings.SyncSettingsUtils;
import org.chromium.chrome.browser.toolbar.adaptive.AdaptiveToolbarFeatures;
import org.chromium.chrome.browser.toolbar.adaptive.AdaptiveToolbarStatePredictor;
import org.chromium.chrome.browser.tracing.settings.DeveloperSettings;
>>>>>>> chromium
import org.chromium.components.browser_ui.settings.ChromeBasePreference;
import org.chromium.components.browser_ui.settings.ManagedPreferenceDelegate;
import org.chromium.components.browser_ui.settings.SettingsLauncher;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.components.search_engines.TemplateUrl;
import org.chromium.components.search_engines.TemplateUrlService;
<<<<<<< HEAD
import org.chromium.components.signin.AccountManagerFacade;
import org.chromium.components.signin.AccountManagerFacadeProvider;
import org.chromium.components.signin.identitymanager.ConsentLevel;
import org.chromium.components.sync.SyncService;
import org.chromium.components.user_prefs.UserPrefs;
import org.chromium.ui.modaldialog.ModalDialogManager;
=======
import org.chromium.components.signin.base.CoreAccountInfo;
import org.chromium.components.signin.identitymanager.ConsentLevel;
import org.chromium.components.signin.metrics.SigninAccessPoint;
>>>>>>> chromium

import java.util.HashMap;
import java.util.Map;

<<<<<<< HEAD
/** The main settings screen, shown when the user first opens Settings. */
public class MainSettings extends ChromeBaseSettingsFragment
        implements TemplateUrlService.LoadListener,
                SyncService.SyncStateChangedListener,
                SigninManager.SignInStateObserver {
    public static final String PREF_SETTINGS_PROMO_CARD = "settings_promo_card";
=======
/**
 * The main settings screen, shown when the user first opens Settings.
 */
public class MainSettings extends PreferenceFragmentCompat
        implements TemplateUrlService.LoadListener, SyncService.SyncStateChangedListener,
                   SigninManager.SignInStateObserver {
    public static final String PREF_SYNC_PROMO = "sync_promo";
>>>>>>> chromium
    public static final String PREF_ACCOUNT_AND_GOOGLE_SERVICES_SECTION =
            "account_and_google_services_section";
    public static final String PREF_SIGN_IN = "sign_in";
    public static final String PREF_MANAGE_SYNC = "manage_sync";
    public static final String PREF_GOOGLE_SERVICES = "google_services";
    public static final String PREF_SEARCH_ENGINE = "search_engine";
    public static final String PREF_PASSWORDS = "passwords";
    public static final String PREF_HOMEPAGE = "homepage";
    public static final String PREF_TOOLBAR_SHORTCUT = "toolbar_shortcut";
    public static final String PREF_UI_THEME = "ui_theme";
    public static final String PREF_PRIVACY = "privacy";
    public static final String PREF_SAFETY_CHECK = "safety_check";
    public static final String PREF_DATA_REDUCTION = "data_reduction";
    public static final String PREF_NOTIFICATIONS = "notifications";
    public static final String PREF_DOWNLOADS = "downloads";
    public static final String PREF_DEVELOPER = "developer";

    // Used for elevating the privacy section behind the flag (see crbug.com/1099233).
    public static final int PRIVACY_ORDER_DEFAULT = 18;
    public static final int PRIVACY_ORDER_ELEVATED = 12;

    private final ManagedPreferenceDelegate mManagedPreferenceDelegate;
    private final Map<String, Preference> mAllPreferences = new HashMap<>();
    private SyncPromoPreference mSyncPromoPreference;
    private SignInPreference mSignInPreference;
    private ChromeBasePreference mManageSync;
    private @Nullable PasswordCheck mPasswordCheck;

    public MainSettings() {
        setHasOptionsMenu(true);
        mManagedPreferenceDelegate = createManagedPreferenceDelegate();
    }

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        createPreferences();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActivity().setTitle(R.string.settings);
        mPasswordCheck = PasswordCheckFactory.getOrCreate(new SettingsLauncherImpl());
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        // Disable animations of preference changes.
        getListView().setItemAnimator(null);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        mSyncPromoPreference.onPreferenceFragmentDestroyed();
        // The component should only be destroyed when the activity has been closed by the user
        // (e.g. by pressing on the back button) and not when the activity is temporarily destroyed
        // by the system.
        if (getActivity().isFinishing() && mPasswordCheck != null) PasswordCheckFactory.destroy();
    }

    @Override
    public void onStart() {
        super.onStart();
        SigninManager signinManager = IdentityServicesProvider.get().getSigninManager(
                Profile.getLastUsedRegularProfile());
        if (signinManager.isSigninSupported()) {
            signinManager.addSignInStateObserver(this);
        }
        SyncService syncService = SyncService.get();
        if (syncService != null) {
            syncService.addSyncStateChangedListener(this);
        }
    }

    @Override
    public void onStop() {
        super.onStop();
        SigninManager signinManager = IdentityServicesProvider.get().getSigninManager(
                Profile.getLastUsedRegularProfile());
        if (signinManager.isSigninSupported()) {
            signinManager.removeSignInStateObserver(this);
        }
        SyncService syncService = SyncService.get();
        if (syncService != null) {
            syncService.removeSyncStateChangedListener(this);
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        updatePreferences();
    }

    private void createPreferences() {
        SettingsUtils.addPreferencesFromResource(this, R.xml.main_preferences);

<<<<<<< HEAD
        SettingsUtils.addPreferencesFromResource(
                this,
                useLegacySettingsOrder() ? R.xml.main_preferences_legacy : R.xml.main_preferences);

        ProfileDataCache profileDataCache =
                ProfileDataCache.createWithDefaultImageSizeAndNoBadge(getContext());
        AccountManagerFacade accountManagerFacade = AccountManagerFacadeProvider.getInstance();

        if (ChromeFeatureList.isEnabled(ChromeFeatureList.DEFAULT_BROWSER_PROMO_ANDROID2)) {
            // TODO(crbug.com/364906215): Define SettingsPromoCardPreference in the xml once
            // SyncPromoPreference is removed.
            SettingsPromoCardPreference settingsPromoCardPreference =
                    new SettingsPromoCardPreference(
                            getContext(), null, TrackerFactory.getTrackerForProfile(getProfile()));
            settingsPromoCardPreference.setKey(PREF_SETTINGS_PROMO_CARD);
            settingsPromoCardPreference.setOrder(0);
            getPreferenceScreen().addPreference(settingsPromoCardPreference);
        }

        SignInPreference signInPreference = findPreference(PREF_SIGN_IN);
        signInPreference.initialize(getProfile(), profileDataCache, accountManagerFacade);

        ChromeBasePreference googleServicePreference = findPreference(PREF_GOOGLE_SERVICES);
        googleServicePreference.setViewId(R.id.account_management_google_services_row);

=======
>>>>>>> chromium
        cachePreferences();

        mSyncPromoPreference.setOnStateChangedCallback(this::onSyncPromoPreferenceStateChanged);

        updatePasswordsPreference();

        setManagedPreferenceDelegateForPreference(PREF_SEARCH_ENGINE);
        setManagedPreferenceDelegateForPreference(PREF_DATA_REDUCTION);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            // If we are on Android O+ the Notifications preference should lead to the Android
            // Settings notifications page.
            Preference notifications = findPreference(PREF_NOTIFICATIONS);
            notifications.setOnPreferenceClickListener(preference -> {
                Intent intent = new Intent();
                intent.setAction(Settings.ACTION_APP_NOTIFICATION_SETTINGS);
                intent.putExtra(Settings.EXTRA_APP_PACKAGE,
                        ContextUtils.getApplicationContext().getPackageName());
                startActivity(intent);
                // We handle the click so the default action isn't triggered.
                return true;
            });
        } else {
            // The per-website notification settings page can be accessed from Site
            // Settings, so we don't need to show this here.
            getPreferenceScreen().removePreference(findPreference(PREF_NOTIFICATIONS));
        }

        if (!TemplateUrlServiceFactory.get().isLoaded()) {
            TemplateUrlServiceFactory.get().registerLoadListener(this);
            TemplateUrlServiceFactory.get().load();
        }

        new AdaptiveToolbarStatePredictor().recomputeUiState(uiState -> {
            // We don't show the toolbar shortcut settings page if disabled from finch.
            // Note, we can still have the old data collection experiment running for which
            // |canShowUi| might be true. In that case, just hide the settings page.
            if (uiState.canShowUi && !AdaptiveToolbarFeatures.isSingleVariantModeEnabled()) return;
            getPreferenceScreen().removePreference(findPreference(PREF_TOOLBAR_SHORTCUT));
        });
    }

    /**
     * Stores all preferences in memory so that, if they needed to be added/removed from the
     * PreferenceScreen, there would be no need to reload them from 'main_preferences.xml'.
     */
    private void cachePreferences() {
        int preferenceCount = getPreferenceScreen().getPreferenceCount();
        for (int index = 0; index < preferenceCount; index++) {
            Preference preference = getPreferenceScreen().getPreference(index);
            mAllPreferences.put(preference.getKey(), preference);
        }
        mSyncPromoPreference = (SyncPromoPreference) mAllPreferences.get(PREF_SYNC_PROMO);
        mSignInPreference = (SignInPreference) mAllPreferences.get(PREF_SIGN_IN);
        mManageSync = (ChromeBasePreference) findPreference(PREF_MANAGE_SYNC);
    }

    private void setManagedPreferenceDelegateForPreference(String key) {
        ChromeBasePreference chromeBasePreference = (ChromeBasePreference) mAllPreferences.get(key);
        chromeBasePreference.setManagedPreferenceDelegate(mManagedPreferenceDelegate);
    }

    private void updatePreferences() {
<<<<<<< HEAD
        if (ChromeFeatureList.isEnabled(ChromeFeatureList.DEFAULT_BROWSER_PROMO_ANDROID2)) {
            SettingsPromoCardPreference promoCardPreference =
                    (SettingsPromoCardPreference) addPreferenceIfAbsent(PREF_SETTINGS_PROMO_CARD);
            promoCardPreference.updatePreferences();
        }

=======
>>>>>>> chromium
        if (IdentityServicesProvider.get()
                        .getSigninManager(Profile.getLastUsedRegularProfile())
                        .isSigninSupported()) {
            addPreferenceIfAbsent(PREF_SIGN_IN);
        } else {
            removePreferenceIfPresent(PREF_SIGN_IN);
        }

        updateManageSyncPreference();
        updateSearchEnginePreference();
<<<<<<< HEAD
        updateAutofillPreferences();
        updatePlusAddressesPreference();
        updateAddressBarPreference();

        boolean isTabGroupSyncAutoOpenConfigurable =
                TabGroupSyncFeatures.isTabGroupSyncEnabled(getProfile())
                        && ChromeFeatureList.isEnabled(
                                ChromeFeatureList.TAB_GROUP_SYNC_AUTO_OPEN_KILL_SWITCH);
        if (isTabGroupSyncAutoOpenConfigurable
                || ChromeFeatureList.isEnabled(ChromeFeatureList.ANDROID_TAB_DECLUTTER)) {
            addPreferenceIfAbsent(PREF_TABS);
        } else {
            removePreferenceIfPresent(PREF_TABS);
        }
=======
>>>>>>> chromium

        Preference homepagePref = addPreferenceIfAbsent(PREF_HOMEPAGE);
        setOnOffSummary(homepagePref, HomepageManager.isHomepageEnabled());

        if (NightModeUtils.isNightModeSupported()) {
            addPreferenceIfAbsent(PREF_UI_THEME);
        } else {
            removePreferenceIfPresent(PREF_UI_THEME);
        }

        if (DeveloperSettings.shouldShowDeveloperSettings()) {
            addPreferenceIfAbsent(PREF_DEVELOPER);
        } else {
            removePreferenceIfPresent(PREF_DEVELOPER);
        }

        ChromeBasePreference dataReduction =
                (ChromeBasePreference) findPreference(PREF_DATA_REDUCTION);
        dataReduction.setSummary(DataReductionPreferenceFragment.generateSummary(getResources()));
    }

    private Preference addPreferenceIfAbsent(String key) {
        Preference preference = getPreferenceScreen().findPreference(key);
        if (preference == null) getPreferenceScreen().addPreference(mAllPreferences.get(key));
        return mAllPreferences.get(key);
    }

    private void removePreferenceIfPresent(String key) {
        Preference preference = getPreferenceScreen().findPreference(key);
        if (preference != null) getPreferenceScreen().removePreference(preference);
    }

    private void updateManageSyncPreference() {
<<<<<<< HEAD
        // TODO(crbug.com/40067770): Remove usage of ConsentLevel.SYNC after kSync users are
        // migrated to kSignin in phase 3. See ConsentLevel::kSync documentation for details.
        boolean isSyncConsentAvailable =
                IdentityServicesProvider.get()
                                .getIdentityManager(getProfile())
                                .getPrimaryAccountInfo(ConsentLevel.SYNC)
                        != null;
        mManageSync.setVisible(isSyncConsentAvailable);
        if (!isSyncConsentAvailable) return;

        mManageSync.setIcon(SyncSettingsUtils.getSyncStatusIcon(getActivity(), getProfile()));
        mManageSync.setSummary(SyncSettingsUtils.getSyncStatusSummary(getActivity(), getProfile()));

        mManageSync.setOnPreferenceClickListener(
                pref -> {
                    Context context = getContext();
                    if (SyncServiceFactory.getForProfile(getProfile())
                            .isSyncDisabledByEnterprisePolicy()) {
                        SyncSettingsUtils.showSyncDisabledByAdministratorToast(context);
                    } else {
                        SettingsNavigation settingsNavigation =
                                SettingsNavigationFactory.createSettingsNavigation();
                        settingsNavigation.startSettings(context, ManageSyncSettings.class);
                    }
                    return true;
                });
=======
        String primaryAccountName = CoreAccountInfo.getEmailFrom(
                IdentityServicesProvider.get()
                        .getIdentityManager(Profile.getLastUsedRegularProfile())
                        .getPrimaryAccountInfo(ConsentLevel.SIGNIN));
        boolean showManageSync = primaryAccountName != null;
        mManageSync.setVisible(showManageSync);
        if (!showManageSync) return;

        boolean isSyncConsentAvailable =
                IdentityServicesProvider.get()
                        .getIdentityManager(Profile.getLastUsedRegularProfile())
                        .getPrimaryAccountInfo(ConsentLevel.SYNC)
                != null;
        mManageSync.setIcon(SyncSettingsUtils.getSyncStatusIcon(getActivity()));
        mManageSync.setSummary(SyncSettingsUtils.getSyncStatusSummary(getActivity()));
        mManageSync.setOnPreferenceClickListener(pref -> {
            Context context = getContext();
            if (SyncService.get().isSyncDisabledByEnterprisePolicy()) {
                SyncSettingsUtils.showSyncDisabledByAdministratorToast(context);
            } else if (isSyncConsentAvailable) {
                SettingsLauncher settingsLauncher = new SettingsLauncherImpl();
                settingsLauncher.launchSettingsActivity(context, ManageSyncSettings.class);
            } else {
                SyncConsentActivityLauncherImpl.get().launchActivityForPromoDefaultFlow(
                        context, SigninAccessPoint.SETTINGS, primaryAccountName);
            }
            return true;
        });
>>>>>>> chromium
    }

    private void updateSearchEnginePreference() {
        if (!TemplateUrlServiceFactory.get().isLoaded()) {
            ChromeBasePreference searchEnginePref =
                    (ChromeBasePreference) findPreference(PREF_SEARCH_ENGINE);
            searchEnginePref.setEnabled(false);
            return;
        }

        String defaultSearchEngineName = null;
        TemplateUrl dseTemplateUrl =
                TemplateUrlServiceFactory.get().getDefaultSearchEngineTemplateUrl();
        if (dseTemplateUrl != null) defaultSearchEngineName = dseTemplateUrl.getShortName();

        Preference searchEnginePreference = findPreference(PREF_SEARCH_ENGINE);
        searchEnginePreference.setEnabled(true);
        searchEnginePreference.setSummary(defaultSearchEngineName);
    }

    private void updatePasswordsPreference() {
        Preference passwordsPreference = findPreference(PREF_PASSWORDS);
        passwordsPreference.setOnPreferenceClickListener(preference -> {
            PasswordManagerLauncher.showPasswordSettings(
                    getActivity(), ManagePasswordsReferrer.CHROME_SETTINGS);
            return true;
        });
    }

    private void setOnOffSummary(Preference pref, boolean isOn) {
        pref.setSummary(isOn ? R.string.text_on : R.string.text_off);
    }

    // SigninManager.SignInStateObserver implementation.
    @Override
    public void onSignedIn() {
        // After signing in or out of a managed account, preferences may change or become enabled
        // or disabled.
        new Handler().post(() -> updatePreferences());
    }

    @Override
    public void onSignedOut() {
<<<<<<< HEAD
        // TODO(crbug.com/343933167): The snackbar should be shown from
        // SignOutCoordinator.startSignOutFlow(), in other words SignOutCoordinator.showSnackbar()
        // should be private method.
        if (IdentityServicesProvider.get()
                        .getIdentityManager(getProfile())
                        .getPrimaryAccountInfo(ConsentLevel.SIGNIN)
                == null) {
            // Show the signout snackbar, or wait until `onStart()` if the fragment is not in the
            // `STARTED` state.
            if (getLifecycle().getCurrentState().isAtLeast(Lifecycle.State.STARTED)) {
                showSignoutSnackbar();
            } else {
                mShouldShowSnackbar = true;
            }
        }

=======
>>>>>>> chromium
        updatePreferences();
    }

    private void onSyncPromoPreferenceStateChanged() {
        // Remove "Account" section header if the personalized sign-in promo is shown.
        boolean isShowingPersonalizedSigninPromo =
                mSyncPromoPreference.getState() == State.PERSONALIZED_SIGNIN_PROMO;
        findPreference(PREF_ACCOUNT_AND_GOOGLE_SERVICES_SECTION)
                .setVisible(!isShowingPersonalizedSigninPromo);
        mSignInPreference.setVisible(!isShowingPersonalizedSigninPromo);
    }

    // TemplateUrlService.LoadListener implementation.
    @Override
    public void onTemplateUrlServiceLoaded() {
        TemplateUrlServiceFactory.get().unregisterLoadListener(this);
        updateSearchEnginePreference();
    }

    @Override
    public void syncStateChanged() {
        updateManageSyncPreference();
    }

    @VisibleForTesting
    public ManagedPreferenceDelegate getManagedPreferenceDelegateForTest() {
        return mManagedPreferenceDelegate;
    }

    private ManagedPreferenceDelegate createManagedPreferenceDelegate() {
        return new ChromeManagedPreferenceDelegate() {
            @Override
            public boolean isPreferenceControlledByPolicy(Preference preference) {
                if (PREF_DATA_REDUCTION.equals(preference.getKey())) {
                    return DataReductionProxySettings.getInstance().isDataReductionProxyManaged();
                }
                if (PREF_SEARCH_ENGINE.equals(preference.getKey())) {
                    return TemplateUrlServiceFactory.get().isDefaultSearchManaged();
                }
                return false;
            }

            @Override
            public boolean isPreferenceClickDisabledByPolicy(Preference preference) {
                if (PREF_DATA_REDUCTION.equals(preference.getKey())) {
                    DataReductionProxySettings settings = DataReductionProxySettings.getInstance();
                    return settings.isDataReductionProxyManaged()
                            && !settings.isDataReductionProxyEnabled();
                }
                if (PREF_SEARCH_ENGINE.equals(preference.getKey())) {
                    return TemplateUrlServiceFactory.get().isDefaultSearchManaged();
                }
                return isPreferenceControlledByPolicy(preference)
                        || isPreferenceControlledByCustodian(preference);
            }
        };
    }
}
