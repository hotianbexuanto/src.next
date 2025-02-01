// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'chrome://resources/cr_components/managed_footnote/managed_footnote.js';
import './item.js';
import './shared_style.js';

import {CrContainerShadowBehavior} from 'chrome://resources/cr_elements/cr_container_shadow_behavior.m.js';
import {I18nBehavior} from 'chrome://resources/js/i18n_behavior.m.js';
import {IronA11yAnnouncer} from 'chrome://resources/polymer/v3_0/iron-a11y-announcer/iron-a11y-announcer.js';
import {html, mixinBehaviors, PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import {ExtensionsItemElement, ItemDelegate} from './item.js';

type Filter = (info: chrome.developerPrivate.ExtensionInfo) => boolean;

const ExtensionsItemListElementBase =
    mixinBehaviors([CrContainerShadowBehavior, I18nBehavior], PolymerElement) as
    {new (): PolymerElement & I18nBehavior};

class ExtensionsItemListElement extends ExtensionsItemListElementBase {
  static get is() {
    return 'extensions-item-list';
  }

  static get template() {
    return html`{__html_template__}`;
  }

  static get properties() {
    return {
      apps: Array,
      extensions: Array,
      delegate: Object,

      inDevMode: {
        type: Boolean,
        value: false,
      },

      filter: {
        type: String,
      },

      computedFilter_: {
        type: String,
        computed: 'computeFilter_(filter)',
        observer: 'announceSearchResults_',
      },

      maxColumns_: {
        type: Number,
        value: 3,
      },

      shownAppsCount_: {
        type: Number,
        value: 0,
      },

      shownExtensionsCount_: {
        type: Number,
        value: 0,
      },
    };
  }

  apps: Array<chrome.developerPrivate.ExtensionInfo>;
  extensions: Array<chrome.developerPrivate.ExtensionInfo>;
  delegate: ItemDelegate;
  inDevMode: boolean;
  filter: string;
  private computedFilter_: string;
  private maxColumns_: number;
  private shownAppsCount_: number;
  private shownExtensionsCount_: number;

  getDetailsButton(id: string): HTMLElement|null {
    const item =
        this.shadowRoot!.querySelector<ExtensionsItemElement>(`#${id}`);
    return item && item.getDetailsButton();
  }

  getErrorsButton(id: string): HTMLElement|null {
    const item =
        this.shadowRoot!.querySelector<ExtensionsItemElement>(`#${id}`);
    return item && item.getErrorsButton();
  }

  /**
   * Computes the filter function to be used for determining which items
   * should be shown. A |null| value indicates that everything should be
   * shown.
   * return {?Function}
   */
  private computeFilter_(): Filter|null {
    const formattedFilter = this.filter.trim().toLowerCase();
    if (!formattedFilter) {
      return null;
    }

    return i => [i.name, i.id].some(
               s => s.toLowerCase().includes(formattedFilter));
  }

<<<<<<< HEAD
  /**
   * Computes the extensions that are affected by the manifest v2 deprecation
   * and should be visible in the MV2 deprecation panel.
   */
  private computeMv2DeprecatedExtensions_():
      chrome.developerPrivate.ExtensionInfo[] {
    return this.extensions.filter((extension) => {
      switch (this.mv2ExperimentStage_) {
        case Mv2ExperimentStage.NONE:
          return false;
        case Mv2ExperimentStage.WARNING:
          return extension.isAffectedByMV2Deprecation &&
              !extension.didAcknowledgeMV2DeprecationNotice;
        case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
          return extension.isAffectedByMV2Deprecation &&
              extension.disableReasons.unsupportedManifestVersion &&
              !extension.didAcknowledgeMV2DeprecationNotice;
        case Mv2ExperimentStage.UNSUPPORTED:
          return extension.isAffectedByMV2Deprecation &&
              extension.disableReasons.unsupportedManifestVersion;
      }
    });
  }

  /**
   * Computes the extensions that are potentially unsafe and should be visible
   * in the review panel.
   */
  private computeUnsafeExtensions_(): chrome.developerPrivate.ExtensionInfo[] {
    return this.extensions.filter(
        extension =>
            !!(extension.safetyCheckText &&
               extension.safetyCheckText.panelString));
  }

  /**
   * Returns whether the review deprecation panel should be visible.
   */
  private computeShowSafetyCheckReviewPanel_(): boolean {
    // If there are any unsafe extensions, they will be shown in the panel.
    // Store this, so we can show the completion info in the panel when there
    // are no unsafe extensions left after the user finished reviewing the
    // extensions.
    if (this.unsafeExtensions_.length !== 0) {
      this.reviewPanelShown_ = true;
    }

    // Panel is visible if there are any unsafe extensions, or the there are
    // none left after the user finished reviewing the extensions.
    return this.unsafeExtensions_.length !== 0 || this.reviewPanelShown_;
  }


  /*
   * Indicates whether the mv2 deprecation panel is shown.
   */
  protected hasSafetyCheckTriggeringExtension_(): boolean {
    for (const extension of this.extensions) {
      if (!!extension.safetyCheckText &&
          !!extension.safetyCheckText.panelString &&
          this.showSafetyCheckReviewPanel_) {
        return true;
      }
    }
    return false;
  }

  /**
   * Returns whether the manifest v2 deprecation panel should be visible.
   */
  protected shouldShowMv2DeprecationPanel_(): boolean {
    switch (this.mv2ExperimentStage_) {
      case Mv2ExperimentStage.NONE:
        return false;
      case Mv2ExperimentStage.WARNING:
      case Mv2ExperimentStage.DISABLE_WITH_REENABLE:
      case Mv2ExperimentStage.UNSUPPORTED:
        // Panel is visible when it has not been dismissed and at least one
        // extension is affected by the MV2 deprecation.
        return !this.isMv2DeprecationNoticeDismissed &&
            this.mv2DeprecatedExtensions_?.length !== 0;
    }
  }

  protected shouldShowEmptyItemsMessage_(): boolean {
=======
  private shouldShowEmptyItemsMessage_() {
    if (!this.apps || !this.extensions) {
      return;
    }

>>>>>>> chromium
    return this.apps.length === 0 && this.extensions.length === 0;
  }

  private shouldShowEmptySearchMessage_() {
    return !this.shouldShowEmptyItemsMessage_() && this.shownAppsCount_ === 0 &&
        this.shownExtensionsCount_ === 0;
  }

  private onNoExtensionsTap_(e: Event) {
    if ((e.target as HTMLElement).tagName === 'A') {
      chrome.metricsPrivate.recordUserAction('Options_GetMoreExtensions');
    }
  }

  private announceSearchResults_() {
    if (this.computedFilter_) {
      IronA11yAnnouncer.requestAvailability();
      setTimeout(() => {  // Async to allow list to update.
        const total = this.shownAppsCount_ + this.shownExtensionsCount_;
        this.dispatchEvent(new CustomEvent('iron-announce', {
          bubbles: true,
          composed: true,
          detail: {
            text: this.shouldShowEmptySearchMessage_() ?
                this.i18n('noSearchResults') :
                (total === 1 ?
                     this.i18n('searchResultsSingular', this.filter) :
                     this.i18n(
                         'searchResultsPlural', total.toString(), this.filter)),
          }
        }));
      }, 0);
    }
  }
}

declare global {
  interface HTMLElementTagNameMap {
    'extensions-item-list': ExtensionsItemListElement;
  }
}

customElements.define(ExtensionsItemListElement.is, ExtensionsItemListElement);
