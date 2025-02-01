// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

<<<<<<< HEAD
import type {CrLitElement} from '//resources/lit/v3_0/lit.rollup.js';
import {getToastManager} from 'chrome://resources/cr_elements/cr_toast/cr_toast_manager.js';
import {assert, assertNotReached} from 'chrome://resources/js/assert.js';
import {loadTimeData} from 'chrome://resources/js/load_time_data.js';

import type {ItemDelegate} from './item.js';
import {TOAST_DURATION_MS} from './item_util.js';
=======
import {assertNotReached} from 'chrome://resources/js/assert.m.js';
import {loadTimeData} from 'chrome://resources/js/load_time_data.m.js';
import {dedupingMixin, PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
>>>>>>> chromium

type Constructor<T> = new (...args: any[]) => T;

export const ItemMixin = dedupingMixin(
    <T extends Constructor<PolymerElement>>(superClass: T): T&
    Constructor<ItemMixinInterface> => {
      class ItemMixin extends superClass {
        /**
         * @return The app or extension label depending on |type|.
         */
        appOrExtension(
            type: chrome.developerPrivate.ExtensionType, appLabel: string,
            extensionLabel: string): string {
          const ExtensionType = chrome.developerPrivate.ExtensionType;
          switch (type) {
            case ExtensionType.HOSTED_APP:
            case ExtensionType.LEGACY_PACKAGED_APP:
            case ExtensionType.PLATFORM_APP:
              return appLabel;
            case ExtensionType.EXTENSION:
            case ExtensionType.SHARED_MODULE:
              return extensionLabel;
          }
          assertNotReached('Item type is not App or Extension.');
          // Unreachable return to satisfy TS compiler.
          return ExtensionType.EXTENSION;
        }

        /**
         * @return The a11y association descriptor, e.g. "Related to <ext>".
         */
        a11yAssociation(name: string): string {
          // Don't use I18nBehavior.i18n because of additional checks it
          // performs. Polymer ensures that this string is not stamped into
          // arbitrary HTML. `name` can contain any data including html tags,
          // e.g. "My <video> download extension!"
          return loadTimeData.getStringF('extensionA11yAssociation', name);
        }
      }

      return ItemMixin;
    });

<<<<<<< HEAD
    /**
     * Reloads the item.
     */
    async reloadItem() {
      // Don't reload if in the middle of an update.
      if (this.isReloading_) {
        return;
      }

      this.isReloading_ = true;

      const toastManager = getToastManager();
      // Keep the toast open indefinitely.
      toastManager.duration = 0;
      toastManager.show(loadTimeData.getString('itemReloading'));

      assert(this.delegate);
      assert(this.data);
      try {
        await this.delegate.reloadItem(this.data.id);
        toastManager.hide();
        toastManager.duration = TOAST_DURATION_MS;
        toastManager.show(loadTimeData.getString('itemReloaded'));
      } catch (loadError) {
        toastManager.hide();
        throw loadError;
      } finally {
        this.isReloading_ = false;
      }
    }
  }

  return ItemMixin;
};

export interface ItemMixinInterface {
=======
interface ItemMixinInterface {
>>>>>>> chromium
  appOrExtension(
      type: chrome.developerPrivate.ExtensionType, appLabel: string,
      extensionLabel: string): string;
  a11yAssociation(name: string): string;
}
