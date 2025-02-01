// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'chrome://resources/cr_elements/cr_button/cr_button.m.js';
import 'chrome://resources/cr_elements/cr_icon_button/cr_icon_button.m.js';
import 'chrome://resources/cr_elements/cr_icons_css.m.js';
import 'chrome://resources/cr_elements/cr_link_row/cr_link_row.js';
import 'chrome://resources/cr_elements/cr_toggle/cr_toggle.m.js';
import 'chrome://resources/cr_elements/icons.m.js';
import 'chrome://resources/cr_elements/policy/cr_tooltip_icon.m.js';
import 'chrome://resources/cr_elements/shared_style_css.m.js';
import 'chrome://resources/cr_elements/shared_vars_css.m.js';
import 'chrome://resources/js/action_link.js';
import 'chrome://resources/cr_elements/action_link_css.m.js';
import 'chrome://resources/polymer/v3_0/iron-flex-layout/iron-flex-layout-classes.js';
import 'chrome://resources/polymer/v3_0/iron-icon/iron-icon.js';
import 'chrome://resources/polymer/v3_0/paper-spinner/paper-spinner-lite.js';
import 'chrome://resources/polymer/v3_0/paper-styles/color.js';
import './host_permissions_toggle_list.js';
import './icons.html.js';
import './runtime_host_permissions.js';
import './shared_style.js';
import './shared_vars.js';
import './strings.m.js';
import './toggle_row.js';

import {CrContainerShadowBehavior} from 'chrome://resources/cr_elements/cr_container_shadow_behavior.m.js';
import {CrToggleElement} from 'chrome://resources/cr_elements/cr_toggle/cr_toggle.m.js';
import {focusWithoutInk} from 'chrome://resources/js/cr/ui/focus_without_ink.m.js';
import {loadTimeData} from 'chrome://resources/js/load_time_data.m.js';
import {afterNextRender, html, mixinBehaviors, PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import {ItemDelegate} from './item.js';
import {ItemMixin} from './item_mixin.js';
import {computeInspectableViewLabel, EnableControl, getEnableControl, getItemSource, getItemSourceString, isEnabled, userCanChangeEnablement} from './item_util.js';
import {navigation, Page} from './navigation_helper.js';
import {ExtensionsToggleRowElement} from './toggle_row.js';

export interface ExtensionsDetailViewElement {
  $: {
    closeButton: HTMLElement,
    enableToggle: CrToggleElement,
    extensionsActivityLogLink: HTMLElement,
  };
}

/** Event interface for dom-repeat. */
interface RepeaterEvent extends CustomEvent {
  model: {
    item: chrome.developerPrivate.ExtensionView,
  };
}

const ExtensionsDetailViewElementBase =
    mixinBehaviors([CrContainerShadowBehavior], ItemMixin(PolymerElement)) as
    {new (): PolymerElement};

export class ExtensionsDetailViewElement extends
    ExtensionsDetailViewElementBase {
  static get is() {
    return 'extensions-detail-view';
  }

  static get template() {
    return html`{__html_template__}`;
  }

  static get properties() {
    return {
      /**
       * The underlying ExtensionInfo for the details being displayed.
       */
      data: Object,

      size_: String,

      delegate: Object,

      /** Whether the user has enabled the UI's developer mode. */
      inDevMode: Boolean,

      /** Whether "allow in incognito" option should be shown. */
      incognitoAvailable: Boolean,

      /** Whether "View Activity Log" link should be shown. */
      showActivityLog: Boolean,

      /** Whether the user navigated to this page from the activity log page. */
      fromActivityLog: Boolean,
    };
  }

  static get observers() {
    return ['onItemIdChanged_(data.id, delegate)'];
  }

  data: chrome.developerPrivate.ExtensionInfo;
  delegate: ItemDelegate;
  inDevMode: boolean;
  incognitoAvailable: boolean;
  showActivityLog: boolean;
  fromActivityLog: boolean;
  private size_: string;

  ready() {
    super.ready();
    this.addEventListener('view-enter-start', this.onViewEnterStart_);
  }

  /**
   * Focuses the extensions options button. This should be used after the
   * dialog closes.
   */
  focusOptionsButton() {
    this.shadowRoot!.querySelector<HTMLElement>('#extensions-options')!.focus();
  }

  /**
   * Focuses the back button when page is loaded.
   */
  private onViewEnterStart_() {
    const elementToFocus = this.fromActivityLog ?
        this.$.extensionsActivityLogLink :
        this.$.closeButton;

    afterNextRender(this, () => focusWithoutInk(elementToFocus));
  }

  private onItemIdChanged_() {
    // Clear the size, since this view is reused, such that no obsolete size
    // is displayed.:
    this.size_ = '';
    this.delegate.getExtensionSize(this.data.id).then(size => {
      this.size_ = size;
    });
  }

  private onActivityLogTap_() {
    navigation.navigateTo({page: Page.ACTIVITY_LOG, extensionId: this.data.id});
  }

  private getDescription_(description: string, fallback: string): string {
    return description || fallback;
  }

  private onCloseButtonTap_() {
    navigation.navigateTo({page: Page.LIST});
  }

  private isEnabled_(): boolean {
    return isEnabled(this.data.state);
  }

  private isEnableToggleEnabled_(): boolean {
    return userCanChangeEnablement(this.data);
  }

  private hasDependentExtensions_(): boolean {
    return this.data.dependentExtensions.length > 0;
  }

  private hasSevereWarnings_(): boolean {
    return this.data.disableReasons.corruptInstall ||
        this.data.disableReasons.suspiciousInstall ||
<<<<<<< HEAD
        this.data.disableReasons.publishedInStoreRequired ||
        this.data.disableReasons.unsupportedDeveloperExtension ||
        this.data.disableReasons.updateRequired || !!this.data.blocklistText ||
        this.data.runtimeWarnings.length > 0;
  }

  protected showAccountUploadButton_(): boolean {
    return this.data.canUploadAsAccountExtension;
  }

  protected showDevReloadButton_(): boolean {
    return this.canReloadItem();
  }

  protected computeEnabledStyle_(): string {
=======
        this.data.disableReasons.updateRequired || !!this.data.blacklistText ||
        this.data.runtimeWarnings.length > 0;
  }

  private computeEnabledStyle_(): string {
>>>>>>> chromium
    return this.isEnabled_() ? 'enabled-text' : '';
  }

  private computeEnabledText_(
      state: chrome.developerPrivate.ExtensionState, onText: string,
      offText: string): string {
    // TODO(devlin): Get the full spectrum of these strings from bettes.
    return isEnabled(state) ? onText : offText;
  }

  private computeInspectLabel_(view: chrome.developerPrivate.ExtensionView):
      string {
    return computeInspectableViewLabel(view);
  }

  private shouldShowOptionsLink_(): boolean {
    return !!this.data.optionsPage;
  }

  private shouldShowOptionsSection_(): boolean {
    return this.data.incognitoAccess.isEnabled ||
        this.data.fileAccess.isEnabled || this.data.errorCollection.isEnabled;
  }

  private shouldShowIncognitoOption_(): boolean {
    return this.data.incognitoAccess.isEnabled && this.incognitoAvailable;
  }

  private onEnableToggleChange_() {
    this.delegate.setItemEnabled(this.data.id, this.$.enableToggle.checked);
    this.$.enableToggle.checked = this.isEnabled_();
  }

  private onInspectTap_(e: RepeaterEvent) {
    this.delegate.inspectItemView(this.data.id, e.model.item);
  }

  private onExtensionOptionsTap_() {
    this.delegate.showItemOptionsPage(this.data);
  }

  private onReloadTap_() {
    this.delegate.reloadItem(this.data.id).catch(loadError => {
      this.dispatchEvent(new CustomEvent(
          'load-error', {bubbles: true, composed: true, detail: loadError}));
    });
  }

<<<<<<< HEAD
  protected onUploadClick_() {
    this.delegate.uploadItemToAccount(this.data.id);
  }

  protected onRemoveClick_() {
    if (this.showSafetyCheck_) {
      chrome.metricsPrivate.recordUserAction('SafetyCheck.DetailRemoveClicked');
      chrome.metricsPrivate.recordEnumerationValue(
          SAFETY_HUB_EXTENSION_REMOVED_HISTOGRAM_NAME,
          convertSafetyCheckReason(this.data.safetyCheckWarningReason),
          SAFETY_HUB_WARNING_REASON_MAX_SIZE);
    }
=======
  private onRemoveTap_() {
>>>>>>> chromium
    this.delegate.deleteItem(this.data.id);
  }

  private onRepairTap_() {
    this.delegate.repairItem(this.data.id);
  }

  private onLoadPathTap_() {
    this.delegate.showInFolder(this.data.id);
  }

  private onAllowIncognitoChange_() {
    this.delegate.setItemAllowedIncognito(
        this.data.id,
        this.shadowRoot!
            .querySelector<ExtensionsToggleRowElement>(
                '#allow-incognito')!.checked);
  }

  private onAllowOnFileUrlsChange_() {
    this.delegate.setItemAllowedOnFileUrls(
        this.data.id,
        this.shadowRoot!
            .querySelector<ExtensionsToggleRowElement>(
                '#allow-on-file-urls')!.checked);
  }

  private onCollectErrorsChange_() {
    this.delegate.setItemCollectsErrors(
        this.data.id,
        this.shadowRoot!
            .querySelector<ExtensionsToggleRowElement>(
                '#collect-errors')!.checked);
  }

  private onExtensionWebSiteTap_() {
    this.delegate.openUrl(this.data.manifestHomePageUrl);
  }

  private onViewInStoreTap_() {
    this.delegate.openUrl(this.data.webStoreUrl);
  }

  private computeDependentEntry_(
      item: chrome.developerPrivate.DependentExtension): string {
    return loadTimeData.getStringF('itemDependentEntry', item.name, item.id);
  }

  private computeSourceString_(): string {
    return this.data.locationText ||
        getItemSourceString(getItemSource(this.data));
  }

  private hasPermissions_(): boolean {
    return this.data.permissions.simplePermissions.length > 0 ||
        this.hasRuntimeHostPermissions_();
  }

  private hasRuntimeHostPermissions_(): boolean {
    return !!this.data.permissions.runtimeHostPermissions;
  }

  private showSiteAccessContent_(): boolean {
    return this.showFreeformRuntimeHostPermissions_() ||
        this.showHostPermissionsToggleList_();
  }

  private showFreeformRuntimeHostPermissions_(): boolean {
    return this.hasRuntimeHostPermissions_() &&
        this.data.permissions.runtimeHostPermissions!.hasAllHosts;
  }

  private showHostPermissionsToggleList_(): boolean {
    return this.hasRuntimeHostPermissions_() &&
        !this.data.permissions.runtimeHostPermissions!.hasAllHosts;
  }

  private showReloadButton_(): boolean {
    return getEnableControl(this.data) === EnableControl.RELOAD;
  }

<<<<<<< HEAD
  private computeShowSafetyCheck_(): boolean {
    const ExtensionType = chrome.developerPrivate.ExtensionType;
    // Check to make sure this is an extension and not a Chrome app.
    if (!(this.data.type === ExtensionType.EXTENSION ||
          this.data.type === ExtensionType.SHARED_MODULE)) {
      return false;
    }
    return !!(
        this.data.safetyCheckText && this.data.safetyCheckText.detailString);
  }

  /**
   * Returns whether the mv2 deprecation message should be displayed.
   */
  protected shouldShowMv2DeprecationMessage_(): boolean {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
        return false;
      case Mv2ExperimentStage.WARNING:
        return this.data.isAffectedByMV2Deprecation;
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
        return this.data.isAffectedByMV2Deprecation &&
            this.data.disableReasons.unsupportedManifestVersion &&
            !this.data.didAcknowledgeMV2DeprecationNotice;
      case Mv2ExperimentStage.UNSUPPORTED:
        return this.data.isAffectedByMV2Deprecation &&
          this.data.disableReasons.unsupportedManifestVersion;
      default:
        assertNotReached();
    }
  }

  /**
   * Returns whether the find alternative button in the mv2 deprecation message
   * should be displayed.
   */
  protected shouldShowMv2DeprecationFindAlternativeButton_(): boolean {
    return this.mv2ExperimentStage_ === Mv2ExperimentStage.WARNING &&
        !!this.data.recommendationsUrl;
  }

  /**
   * Returns whether the remove button in the mv2 deprecation message should be
   * displayed.
   */
  protected shouldShowMv2DeprecationRemoveButton_(): boolean {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
      case Mv2ExperimentStage.WARNING:
        return false;
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
      case Mv2ExperimentStage.UNSUPPORTED:
        return !this.data.mustRemainInstalled;
    }
  }

  /**
   * Returns whether the action menu button in the mv2 deprecation message
   * should be displayed.
   */
  protected shouldShowMv2DeprecationActionMenu_(): boolean {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
      case Mv2ExperimentStage.WARNING:
        return false;
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
        return true;
      case Mv2ExperimentStage.UNSUPPORTED:
        // 'Find alternative' is the only action for this stage. Thus, we only
        // show the menu if the action should be visible. For UNSUPPORTED, this
        // is when the recommendationsUrl is non-empty.
        return !!this.data.recommendationsUrl;
    }
  }

  /**
   * Returns whether the find alternative button in mv2 deprecation message
   * action menu should be displayed.
   */
  protected shouldShowMv2DeprecationFindAlternativeAction_(): boolean {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
      case Mv2ExperimentStage.WARNING:
        return false;
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
      case Mv2ExperimentStage.UNSUPPORTED:
        return !!this.data.recommendationsUrl;
    }
  }

  /**
   * Returns whether the keep button in mv2 deprecation message action menu
   * should be displayed.
   */
  protected shouldShowMv2DeprecationKeepAction_(): boolean {
    return this.mv2ExperimentStage_ ===
        Mv2ExperimentStage.DISABLE_WITH_REENABLE;
  }

  protected shouldShowBlocklistText_(): boolean {
    return !this.showSafetyCheck_ && !!this.data.blocklistText;
  }

  /**
   * Shows only one text if both unsupported developer extension and safety
   * check texts are present. Safety check text takes precedence.
   */
  protected shouldShowUnsupportedDeveloperExtensionText_(): boolean {
    return !this.showSafetyCheck_ &&
        this.data.disableReasons.unsupportedDeveloperExtension;
  }

  protected showRepairButton_(): boolean {
=======
  private showRepairButton_(): boolean {
>>>>>>> chromium
    return getEnableControl(this.data) === EnableControl.REPAIR;
  }

  private showEnableToggle_(): boolean {
    const enableControl = getEnableControl(this.data);
    // We still show the toggle even if we also show the repair button in the
    // detail view, because the repair button appears just beneath it.
    return enableControl === EnableControl.ENABLE_TOGGLE ||
        enableControl === EnableControl.REPAIR;
  }

  private showAllowlistWarning_(): boolean {
    // Only show the allowlist warning if there is no blocklist warning. It
    // would be redundant since all blocklisted items are necessarily not
    // included in the Safe Browsing allowlist.
    return this.data.showSafeBrowsingAllowlistWarning &&
<<<<<<< HEAD
        !this.data.blocklistText;
  }

  /** Opens the action menu for the extension. */
  protected onActionMenuButtonClick_(event: MouseEvent): void {
    this.$.actionMenu.showAt(
        event.target as HTMLElement,
        {anchorAlignmentY: AnchorAlignment.AFTER_END});
  }

  /**
   * Opens a URL in the Web Store with extensions recommendations for the
   * extension.
   */
  protected onFindAlternativeActionClick_(): void {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
      case Mv2ExperimentStage.WARNING:
        assertNotReached();
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
        chrome.metricsPrivate.recordUserAction(
            'Extensions.Mv2Deprecation.Disabled.FindAlternativeForExtension.DetailPage');
        break;
      case Mv2ExperimentStage.UNSUPPORTED:
        chrome.metricsPrivate.recordUserAction(
            'Extensions.Mv2Deprecation.Unsupported.FindAlternativeForExtension.DetailPage');
        break;
    }

    this.$.actionMenu.close();

    const recommendationsUrl: string|undefined = this.data.recommendationsUrl;
    assert(!!recommendationsUrl);
    this.delegate.openUrl(recommendationsUrl);
  }

  /**
   * Dismisses the notice for a given extension in the disable experiment stage.
   * It will not be shown again during this stage.
   */
  protected onKeepActionClick_(): void {
    assert(
        this.mv2ExperimentStage_ === Mv2ExperimentStage.DISABLE_WITH_REENABLE);
    chrome.metricsPrivate.recordUserAction(
        'Extensions.Mv2Deprecation.Disabled.DismissedForExtension.DetailPage');
    this.$.actionMenu.close();
    this.delegate.dismissMv2DeprecationNoticeForExtension(this.data.id);
  }

  /**
   * Returns the Manifest V2 deprecation message header.
   */
  protected getMv2DeprecationMessageHeader_(): string {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
        return '';
      case Mv2ExperimentStage.WARNING:
        return this.i18n('mv2DeprecationMessageWarningHeader');
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
      case Mv2ExperimentStage.UNSUPPORTED:
        return this.i18n('mv2DeprecationMessageDisabledHeader');
      default:
        assertNotReached();
    }
  }

  /**
   * Returns the HTML representation of the Manifest V2 deprecation message
   * subtitle string. We need the HTML representation instead of the string
   * since the string holds substitutions.
   */
  protected getMv2DeprecationMessageSubtitle_(): TrustedHTML {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
        return window.trustedTypes!.emptyHTML;
      case Mv2ExperimentStage.WARNING:
        return this.i18nAdvanced('mv2DeprecationMessageWarningSubtitle', {
          substitutions: [
            'https://chromewebstore.google.com/category/extensions',
            this.i18n('opensInNewTab'),
          ],
          attrs: ['aria-description'],
        });
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
      case Mv2ExperimentStage.UNSUPPORTED:
        return this.i18nAdvanced('mv2DeprecationMessageDisabledSubtitle', {
          substitutions: [
            'https://support.google.com/chrome_webstore' +
                '?p=unsupported_extensions',
            this.i18n('opensInNewTab'),
          ],
          attrs: ['aria-description'],
        });
      default:
        assertNotReached();
    }
  }

  /**
   * Returns the Manifest V2 deprecation message icon.
   */
  protected getMv2DeprecationMessageIcon_(): string {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
      case Mv2ExperimentStage.WARNING:
        return 'extensions-icons:my_extensions';
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
      case Mv2ExperimentStage.UNSUPPORTED:
        return 'extensions-icons:extension_off';
      default:
        assertNotReached();
    }
  }

  /** Returns the accessible label for the action menu button */
  protected getActionMenuButtonLabel_(): string {
    return this.i18n(
        'mv2DeprecationPanelExtensionActionMenuLabel', this.data.name);
=======
        !this.data.blacklistText;
>>>>>>> chromium
  }
}

declare global {
  interface HTMLElementTagNameMap {
    'extensions-detail-view': ExtensionsDetailViewElement;
  }
}

customElements.define(
    ExtensionsDetailViewElement.is, ExtensionsDetailViewElement);
