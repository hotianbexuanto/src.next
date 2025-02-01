// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import './strings.m.js';

import {assertNotReached} from 'chrome://resources/js/assert.m.js';
import {loadTimeData} from 'chrome://resources/js/load_time_data.m.js';

export enum SourceType {
  WEBSTORE = 'webstore',
  POLICY = 'policy',
  SIDELOADED = 'sideloaded',
  UNPACKED = 'unpacked',
  UNKNOWN = 'unknown',
}

export enum EnableControl {
  RELOAD = 'RELOAD',
  REPAIR = 'REPAIR',
  ENABLE_TOGGLE = 'ENABLE_TOGGLE',
}

// TODO(tjudkins): This should be extracted to a shared metrics module.
/** @enum {string} */
export enum UserAction {
  ALL_TOGGLED_ON = 'Extensions.Settings.HostList.AllHostsToggledOn',
  ALL_TOGGLED_OFF = 'Extensions.Settings.HostList.AllHostsToggledOff',
  SPECIFIC_TOGGLED_ON = 'Extensions.Settings.HostList.SpecificHostToggledOn',
  SPECIFIC_TOGGLED_OFF = 'Extensions.Settings.HostList.SpecificHostToggledOff',
  LEARN_MORE = 'Extensions.Settings.HostList.LearnMoreActivated',
}

<<<<<<< HEAD
// Duration of the toast shown.
export const TOAST_DURATION_MS = 3000;

// Values for logging Extension Safety Hub metrics.
export const SAFETY_HUB_EXTENSION_KEPT_HISTOGRAM_NAME =
    'SafeBrowsing.ExtensionSafetyHub.Trigger.Kept';
export const SAFETY_HUB_EXTENSION_REMOVED_HISTOGRAM_NAME =
    'SafeBrowsing.ExtensionSafetyHub.Trigger.Removed';
export const SAFETY_HUB_EXTENSION_SHOWN_HISTOGRAM_NAME =
    `SafeBrowsing.ExtensionSafetyHub.Trigger.Shown`;
// This number should match however many entries are defined in the
// `SafetyCheckWarningReason` defined in the `enums.xml` file.
export const SAFETY_HUB_WARNING_REASON_MAX_SIZE = 7;

=======
>>>>>>> chromium
/**
 * Returns true if the extension is enabled, including terminated
 * extensions.
 */
export function isEnabled(state: chrome.developerPrivate.ExtensionState):
    boolean {
  switch (state) {
    case chrome.developerPrivate.ExtensionState.ENABLED:
    case chrome.developerPrivate.ExtensionState.TERMINATED:
      return true;
    case chrome.developerPrivate.ExtensionState.BLACKLISTED:
    case chrome.developerPrivate.ExtensionState.DISABLED:
      return false;
  }
  assertNotReached();
  return false;
}

/**
 * @return {boolean} Whether the user can change whether or not the extension is
 *     enabled.
 */
export function userCanChangeEnablement(
    item: chrome.developerPrivate.ExtensionInfo): boolean {
  // User doesn't have permission.
  if (!item.userMayModify) {
    return false;
  }
  // Item is forcefully disabled.
  if (item.disableReasons.corruptInstall ||
      item.disableReasons.suspiciousInstall ||
      item.disableReasons.updateRequired ||
<<<<<<< HEAD
      item.disableReasons.publishedInStoreRequired ||
      item.disableReasons.blockedByPolicy ||
      item.disableReasons.unsupportedDeveloperExtension) {
=======
      item.disableReasons.blockedByPolicy) {
>>>>>>> chromium
    return false;
  }
  // An item with dependent extensions can't be disabled (it would bork the
  // dependents).
  if (item.dependentExtensions.length > 0) {
    return false;
  }
  // Blacklisted can't be enabled, either.
  if (item.state === chrome.developerPrivate.ExtensionState.BLACKLISTED) {
    return false;
  }

  return true;
}

export function getItemSource(item: chrome.developerPrivate.ExtensionInfo):
    SourceType {
  if (item.controlledInfo) {
    return SourceType.POLICY;
  }

  switch (item.location) {
    case chrome.developerPrivate.Location.THIRD_PARTY:
      return SourceType.SIDELOADED;
    case chrome.developerPrivate.Location.UNPACKED:
      return SourceType.UNPACKED;
    case chrome.developerPrivate.Location.UNKNOWN:
      return SourceType.UNKNOWN;
    case chrome.developerPrivate.Location.FROM_STORE:
      return SourceType.WEBSTORE;
  }

  assertNotReached(item.location);
}

export function getItemSourceString(source: SourceType): string {
  switch (source) {
    case SourceType.POLICY:
      return loadTimeData.getString('itemSourcePolicy');
    case SourceType.SIDELOADED:
      return loadTimeData.getString('itemSourceSideloaded');
    case SourceType.UNPACKED:
      return loadTimeData.getString('itemSourceUnpacked');
    case SourceType.WEBSTORE:
      return loadTimeData.getString('itemSourceWebstore');
    case SourceType.UNKNOWN:
      // Nothing to return. Calling code should use
      // chrome.developerPrivate.ExtensionInfo's |locationText| instead.
      return '';
  }
  assertNotReached();
  return '';
}

/**
 * Computes the human-facing label for the given inspectable view.
 */
export function computeInspectableViewLabel(
    view: chrome.developerPrivate.ExtensionView): string {
  // Trim the "chrome-extension://<id>/".
  const url = new URL(view.url);
  let label = view.url;
  if (url.protocol === 'chrome-extension:') {
    label = url.pathname.substring(1);
  }
  if (label === '_generated_background_page.html') {
    label = loadTimeData.getString('viewBackgroundPage');
  }
  if (view.type === 'EXTENSION_SERVICE_WORKER_BACKGROUND') {
    label = loadTimeData.getString('viewServiceWorker');
  }
  // Add any qualifiers.
  if (view.incognito) {
    label += ' ' + loadTimeData.getString('viewIncognito');
  }
  if (view.renderProcessId === -1) {
    label += ' ' + loadTimeData.getString('viewInactive');
  }
  if (view.isIframe) {
    label += ' ' + loadTimeData.getString('viewIframe');
  }

  return label;
}

/**
 * @return Whether the extension is in the terminated state.
 */
function isTerminated_(state: chrome.developerPrivate.ExtensionState): boolean {
  return state === chrome.developerPrivate.ExtensionState.TERMINATED;
}

/**
 * Determines which enable control to display for a given extension.
 */
export function getEnableControl(data: chrome.developerPrivate.ExtensionInfo):
    EnableControl {
  if (isTerminated_(data.state)) {
    return EnableControl.RELOAD;
  }
  if (data.disableReasons.corruptInstall && data.userMayModify) {
    return EnableControl.REPAIR;
  }
  return EnableControl.ENABLE_TOGGLE;
}
<<<<<<< HEAD

/**
 * @return The tooltip to show for an extension's enable toggle.
 */
export function getEnableToggleTooltipText(
    data: chrome.developerPrivate.ExtensionInfo): string {
  if (!isEnabled(data.state)) {
    return loadTimeData.getString('enableToggleTooltipDisabled');
  }

  return loadTimeData.getString(
      data.permissions.canAccessSiteData ?
          'enableToggleTooltipEnabledWithSiteAccess' :
          'enableToggleTooltipEnabled');
}

export function createDummyExtensionInfo():
    chrome.developerPrivate.ExtensionInfo {
  return {
    commands: [],
    isCommandRegistrationHandledExternally: false,
    dependentExtensions: [],
    description: '',
    disableReasons: {
      suspiciousInstall: false,
      corruptInstall: false,
      updateRequired: false,
      publishedInStoreRequired: false,
      blockedByPolicy: false,
      reloading: false,
      custodianApprovalRequired: false,
      parentDisabledPermissions: false,
      unsupportedManifestVersion: false,
      unsupportedDeveloperExtension: false,
    },
    errorCollection: {isEnabled: false, isActive: false},
    fileAccess: {isEnabled: false, isActive: false},
    homePage: {url: '', specified: false},
    iconUrl: '',
    id: '',
    incognitoAccess: {isEnabled: false, isActive: false},
    installWarnings: [],
    location: chrome.developerPrivate.Location.UNKNOWN,
    manifestErrors: [],
    manifestHomePageUrl: '',
    mustRemainInstalled: false,
    name: '',
    offlineEnabled: false,
    permissions: {simplePermissions: [], canAccessSiteData: false},
    runtimeErrors: [],
    runtimeWarnings: [],
    state: chrome.developerPrivate.ExtensionState.ENABLED,
    type: chrome.developerPrivate.ExtensionType.EXTENSION,
    updateUrl: '',
    userMayModify: false,
    version: '2.0',
    views: [],
    webStoreUrl: '',
    showSafeBrowsingAllowlistWarning: false,
    showAccessRequestsInToolbar: false,
    safetyCheckWarningReason:
        chrome.developerPrivate.SafetyCheckWarningReason.UNPUBLISHED,
    isAffectedByMV2Deprecation: false,
    didAcknowledgeMV2DeprecationNotice: false,
    canUploadAsAccountExtension: false,
  };
}
=======
>>>>>>> chromium
