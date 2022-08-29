// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/about_flags.h"

#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <utility>

#include "ash/constants/ash_features.h"
#include "ash/public/cpp/app_list/app_list_features.h"
#include "ash/public/cpp/app_list/app_list_switches.h"
#include "ash/public/cpp/keyboard/keyboard_switches.h"
#include "base/base_switches.h"
#include "base/bind.h"
#include "base/callback.h"
#include "base/command_line.h"
#include "base/cxx17_backports.h"
#include "base/feature_list.h"
#include "base/i18n/base_i18n_switches.h"
#include "base/memory/singleton.h"
#include "base/metrics/histogram_functions.h"
#include "base/no_destructor.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "base/values.h"
#include "build/branding_buildflags.h"
#include "build/build_config.h"
#include "cc/base/features.h"
#include "cc/base/switches.h"
#include "chrome/browser/browser_features.h"
#include "chrome/browser/chromeos/android_sms/android_sms_switches.h"
#include "chrome/browser/commerce/commerce_feature_list.h"
#include "chrome/browser/flag_descriptions.h"
#include "chrome/browser/lite_video/lite_video_switches.h"
#include "chrome/browser/login_detection/login_detection_util.h"
#include "chrome/browser/navigation_predictor/navigation_predictor_features.h"
#include "chrome/browser/navigation_predictor/search_engine_preconnector.h"
#include "chrome/browser/net/stub_resolver_config_reader.h"
#include "chrome/browser/net/system_network_context_manager.h"
#include "chrome/browser/notifications/scheduler/public/features.h"
#include "chrome/browser/performance_hints/performance_hints_features.h"
#include "chrome/browser/performance_manager/policies/policy_features.h"
#include "chrome/browser/permissions/abusive_origin_notifications_permission_revocation_config.h"
#include "chrome/browser/permissions/quiet_notification_permission_ui_config.h"
#include "chrome/browser/predictors/loading_predictor_config.h"
#include "chrome/browser/prefetch/prefetch_proxy/prefetch_proxy_features.h"
#include "chrome/browser/prefetch/prefetch_proxy/prefetch_proxy_params.h"
#include "chrome/browser/prefetch/search_prefetch/field_trial_settings.h"
#include "chrome/browser/resource_coordinator/tab_manager_features.h"
#include "chrome/browser/sharing/features.h"
#include "chrome/browser/sharing/shared_clipboard/feature_flags.h"
#include "chrome/browser/sharing/sms/sms_flags.h"
#include "chrome/browser/sharing_hub/sharing_hub_features.h"
#include "chrome/browser/signin/signin_features.h"
#include "chrome/browser/site_isolation/about_flags.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/browser/unexpire_flags.h"
#include "chrome/browser/unexpire_flags_gen.h"
#include "chrome/browser/video_tutorials/switches.h"
#include "chrome/common/buildflags.h"
#include "chrome/common/channel_info.h"
#include "chrome/common/chrome_content_client.h"
#include "chrome/common/chrome_features.h"
#include "chrome/common/chrome_switches.h"
#include "components/assist_ranker/predictor_config_definitions.h"
<<<<<<< HEAD
#include "components/autofill/core/browser/studies/autofill_experiments.h"
=======
#include "components/autofill/core/browser/autofill_experiments.h"
>>>>>>> chromium
#include "components/autofill/core/common/autofill_features.h"
#include "components/autofill/core/common/autofill_payments_features.h"
#include "components/autofill/core/common/autofill_switches.h"
#include "components/autofill/core/common/autofill_util.h"
#include "components/autofill_assistant/browser/features.h"
#include "components/browser_sync/browser_sync_switches.h"
<<<<<<< HEAD
#include "components/collaboration/public/features.h"
#include "components/commerce/core/commerce_feature_list.h"
#include "components/commerce/core/flag_descriptions.h"
#include "components/component_updater/component_updater_command_line_config_policy.h"
#include "components/component_updater/component_updater_switches.h"
#include "components/compose/buildflags.h"
#include "components/compose/core/browser/compose_features.h"
#include "components/content_settings/core/common/features.h"
#include "components/contextual_search/core/browser/contextual_search_field_trial.h"
=======
#include "components/browsing_data/core/features.h"
#include "components/cloud_devices/common/cloud_devices_switches.h"
>>>>>>> chromium
#include "components/contextual_search/core/browser/public.h"
#include "components/data_reduction_proxy/core/common/data_reduction_proxy_features.h"
#include "components/data_reduction_proxy/core/common/data_reduction_proxy_switches.h"
#include "components/dom_distiller/core/dom_distiller_features.h"
#include "components/dom_distiller/core/dom_distiller_switches.h"
#include "components/download/public/common/download_features.h"
#include "components/enterprise/data_controls/core/browser/features.h"
#include "components/error_page/common/error_page_switches.h"
#include "components/feature_engagement/public/feature_constants.h"
#include "components/feature_engagement/public/feature_list.h"
#include "components/feed/feed_feature_list.h"
#include "components/flags_ui/feature_entry.h"
#include "components/flags_ui/feature_entry_macros.h"
#include "components/flags_ui/flags_state.h"
#include "components/flags_ui/flags_storage.h"
#include "components/flags_ui/flags_ui_metrics.h"
#include "components/flags_ui/flags_ui_switches.h"
#include "components/heavy_ad_intervention/heavy_ad_features.h"
#include "components/history_clusters/core/memories_features.h"
#include "components/invalidation/impl/invalidation_switches.h"
#include "components/language/core/common/language_experiments.h"
#include "components/lens/lens_features.h"
#include "components/lookalikes/core/features.h"
#include "components/messages/android/messages_feature.h"
#include "components/nacl/common/buildflags.h"
#include "components/nacl/common/nacl_switches.h"
#include "components/network_session_configurator/common/network_features.h"
#include "components/network_session_configurator/common/network_switches.h"
#include "components/no_state_prefetch/browser/no_state_prefetch_field_trial.h"
#include "components/ntp_tiles/features.h"
#include "components/offline_pages/core/offline_page_feature.h"
#include "components/omnibox/browser/omnibox_field_trial.h"
#include "components/omnibox/common/omnibox_feature_configs.h"
#include "components/omnibox/common/omnibox_features.h"
#include "components/optimization_guide/core/optimization_guide_features.h"
#include "components/page_info/features.h"
#include "components/paint_preview/buildflags/buildflags.h"
#include "components/paint_preview/features/features.h"
#include "components/password_manager/core/common/password_manager_features.h"
#include "components/payments/core/features.h"
#include "components/permissions/features.h"
#include "components/policy/core/common/features.h"
#include "components/query_tiles/switches.h"
#include "components/reading_list/features/reading_list_switches.h"
#include "components/safe_browsing/core/common/features.h"
#include "components/search/ntp_features.h"
#include "components/security_interstitials/content/stateful_ssl_host_state_delegate.h"
#include "components/security_interstitials/core/features.h"
#include "components/security_state/core/features.h"
#include "components/security_state/core/security_state.h"
<<<<<<< HEAD
#include "components/segmentation_platform/embedder/home_modules/constants.h"
#include "components/segmentation_platform/public/features.h"
=======
>>>>>>> chromium
#include "components/send_tab_to_self/features.h"
#include "components/services/heap_profiling/public/cpp/switches.h"
#include "components/shared_highlighting/core/common/shared_highlighting_features.h"
#include "components/signin/core/browser/dice_account_reconcilor_delegate.h"
#include "components/signin/public/base/signin_buildflags.h"
#include "components/signin/public/base/signin_switches.h"
#include "components/site_isolation/features.h"
#include "components/spellcheck/common/spellcheck_features.h"
#include "components/spellcheck/spellcheck_buildflags.h"
#include "components/sync/base/sync_base_switches.h"
#include "components/sync/driver/sync_driver_switches.h"
#include "components/tracing/common/tracing_switches.h"
#include "components/translate/core/browser/translate_manager.h"
#include "components/translate/core/browser/translate_prefs.h"
#include "components/translate/core/browser/translate_ranker_impl.h"
#include "components/translate/core/common/translate_util.h"
#include "components/ui_devtools/switches.h"
#include "components/version_info/version_info.h"
#include "components/viz/common/features.h"
#include "components/viz/common/switches.h"
<<<<<<< HEAD
#include "components/webapps/browser/features.h"
=======
#include "components/webapps/common/switches.h"
>>>>>>> chromium
#include "content/public/common/content_features.h"
#include "content/public/common/content_switches.h"
#include "device/base/features.h"
#include "device/fido/features.h"
#include "device/gamepad/public/cpp/gamepad_features.h"
#include "device/vr/buildflags/buildflags.h"
#include "extensions/buildflags/buildflags.h"
#include "gpu/config/gpu_finch_features.h"
#include "gpu/config/gpu_switches.h"
#include "media/audio/audio_features.h"
#include "media/base/media_switches.h"
#include "media/capture/capture_switches.h"
#include "media/media_buildflags.h"
#include "media/midi/midi_switches.h"
#include "media/webrtc/webrtc_switches.h"
#include "mojo/core/embedder/features.h"
#include "net/base/features.h"
#include "net/net_buildflags.h"
#include "net/nqe/effective_connection_type.h"
#include "net/nqe/network_quality_estimator_params.h"
#include "net/websockets/websocket_basic_handshake_stream.h"
#include "pdf/buildflags.h"
#include "ppapi/buildflags/buildflags.h"
#include "printing/buildflags/buildflags.h"
#include "sandbox/policy/features.h"
#include "sandbox/policy/switches.h"
#include "services/device/public/cpp/device_features.h"
#include "services/device/public/cpp/serial/serial_switches.h"
#include "services/media_session/public/cpp/features.h"
#include "services/network/public/cpp/features.h"
#include "services/network/public/cpp/network_switches.h"
#include "storage/browser/quota/quota_features.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/common/forcedark/forcedark_switches.h"
#include "third_party/blink/public/common/switches.h"
#include "ui/accessibility/accessibility_features.h"
#include "ui/accessibility/accessibility_switches.h"
#include "ui/base/ui_base_features.h"
#include "ui/base/ui_base_switches.h"
#include "ui/compositor/compositor_switches.h"
#include "ui/display/display_features.h"
#include "ui/display/display_switches.h"
#include "ui/events/blink/blink_features.h"
#include "ui/events/event_switches.h"
#include "ui/gfx/switches.h"
#include "ui/gl/buildflags.h"
#include "ui/gl/gl_features.h"
#include "ui/gl/gl_switches.h"
#include "ui/native_theme/native_theme_features.h"

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "extensions/common/extension_features.h"
#endif

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
=======
#if defined(OS_LINUX) || defined(OS_CHROMEOS)
>>>>>>> chromium
#include "base/allocator/buildflags.h"
#endif

#if defined(OS_ANDROID)
#include "chrome/browser/android/explore_sites/explore_sites_feature.h"
#include "chrome/browser/flags/android/chrome_feature_list.h"
#include "chrome/browser/notifications/chime/android/features.h"
#include "chrome/browser/webapps/android/features.h"
#include "components/browser_ui/photo_picker/android/features.h"
#include "components/browser_ui/site_settings/android/features.h"
#include "components/content_creation/notes/core/note_features.h"
#include "components/external_intents/android/external_intents_features.h"
<<<<<<< HEAD
#include "components/facilitated_payments/core/features/features.h"
#include "components/messages/android/messages_feature.h"
#include "components/payments/content/android/payment_feature_map.h"
#include "components/segmentation_platform/public/features.h"
#include "components/translate/content/android/translate_message.h"
#include "ui/android/ui_android_features.h"
#else  // BUILDFLAG(IS_ANDROID)
#include "chrome/browser/component_updater/iwa_key_distribution_component_installer.h"
#include "chrome/browser/media/router/discovery/access_code/access_code_cast_sink_service.h"
#include "chrome/browser/media/router/media_router_feature.h"
#include "chrome/browser/ui/tabs/features.h"
#include "chrome/browser/web_applications/preinstalled_app_install_features.h"
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
#include "ash/constants/ash_features.h"
#include "ash/constants/ash_switches.h"
#include "ash/public/cpp/app_list/app_list_features.h"
#include "ash/public/cpp/keyboard/keyboard_switches.h"
#include "chrome/browser/ash/app_list/search/search_features.h"
=======
#include "components/power_scheduler/power_scheduler_features.h"
#else  // OS_ANDROID
#include "chrome/browser/media/router/media_router_feature.h"
#include "chrome/browser/web_applications/components/preinstalled_app_install_features.h"
#endif  // OS_ANDROID

#if BUILDFLAG(IS_CHROMEOS_ASH)
#include "ash/constants/ash_features.h"
#include "ash/constants/ash_switches.h"
>>>>>>> chromium
#include "chrome/browser/ash/crosapi/browser_util.h"
#include "chrome/browser/nearby_sharing/common/nearby_share_features.h"
<<<<<<< HEAD
#include "chrome/common/chrome_features.h"
#include "chrome/common/webui_url_constants.h"
#include "chromeos/ash/components/assistant/buildflags.h"
#include "chromeos/ash/components/memory/swap_configuration.h"
#include "chromeos/ash/experiences/arc/arc_features.h"
#include "chromeos/ash/experiences/arc/arc_util.h"
#include "chromeos/ash/services/assistant/public/cpp/features.h"
#include "chromeos/constants/chromeos_switches.h"
#include "components/app_restore/features.h"
#include "components/cross_device/nearby/nearby_features.h"
#include "components/metrics/structured/structured_metrics_features.h"  // nogncheck
=======
#include "chromeos/services/assistant/public/cpp/features.h"
#include "components/arc/arc_features.h"
#include "components/arc/arc_util.h"
#include "components/full_restore/features.h"
#include "components/metrics/structured/structured_metrics_features.h"
>>>>>>> chromium
#include "media/capture/video/chromeos/video_capture_features_chromeos.h"
#include "third_party/cros_system_api/switches/chrome_switches.h"
#include "ui/events/ozone/features.h"
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_MAC)
#include "chrome/browser/enterprise/platform_auth/platform_auth_features.h"
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_MAC)
>>>>>>> chromium
#include "chrome/browser/ui/browser_dialogs.h"
#include "chrome/browser/ui/cocoa/screentime/screentime_features.h"
#endif  // OS_MAC

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "extensions/common/extension_features.h"
#include "extensions/common/switches.h"
#endif  // ENABLE_EXTENSIONS

#if BUILDFLAG(ENABLE_PDF)
#include "pdf/pdf_features.h"
#endif

#if BUILDFLAG(ENABLE_PRINTING)
#include "printing/printing_features.h"
#endif

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_VR)
#include "device/vr/public/cpp/features.h"
#include "device/vr/public/cpp/switches.h"
#endif

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
#include "ui/ozone/public/ozone_switches.h"
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_WIN)
#include "chrome/browser/enterprise/platform_auth/platform_auth_features.h"
#include "chrome/browser/tracing/tracing_features.h"
#include "chrome/browser/win/mica_titlebar.h"
#endif

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
#include "chrome/browser/contextual_cueing/contextual_cueing_features.h"  // nogncheck
#include "chrome/browser/enterprise/profile_management/profile_management_features.h"
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)

#if !BUILDFLAG(IS_ANDROID)
// This causes a gn error on Android builds, because gn does not understand
// buildflags.
#include "components/user_education/common/user_education_features.h"  // nogncheck
#endif

#if BUILDFLAG(IS_LINUX)
#include "chrome/browser/ui/ui_features.h"
#include "ui/base/ui_base_features.h"
#endif
=======
#if defined(USE_OZONE)
#include "ui/ozone/public/ozone_switches.h"
#endif  // USE_OZONE

#if defined(OS_WIN)
#include "base/win/windows_version.h"
#include "chrome/browser/win/titlebar_config.h"
#endif  // OS_WIN
>>>>>>> chromium

#if defined(TOOLKIT_VIEWS)
#include "ui/views/animation/installable_ink_drop.h"
#include "ui/views/views_features.h"
#include "ui/views/views_switches.h"
#endif  // defined(TOOLKIT_VIEWS)

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)
#include "components/unexportable_keys/features.h"  // nogncheck
#endif

#if BUILDFLAG(SKIA_BUILD_RUST_PNG)
#include "skia/rusty_png_feature.h"
#endif

#if !BUILDFLAG(IS_CHROMEOS)
#include "components/variations/net/variations_command_line.h"
#endif

=======
>>>>>>> chromium
using flags_ui::FeatureEntry;
using flags_ui::kDeprecated;
using flags_ui::kOsAndroid;
using flags_ui::kOsCrOS;
using flags_ui::kOsCrOSOwnerOnly;
using flags_ui::kOsLinux;
using flags_ui::kOsMac;
using flags_ui::kOsWin;

namespace about_flags {

namespace {

const unsigned kOsAll = kOsMac | kOsWin | kOsLinux | kOsCrOS | kOsAndroid;
const unsigned kOsDesktop = kOsMac | kOsWin | kOsLinux | kOsCrOS;

#if defined(USE_AURA)
const unsigned kOsAura = kOsWin | kOsLinux | kOsCrOS;
#endif  // USE_AURA

#if defined(USE_AURA)
const FeatureEntry::Choice kPullToRefreshChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flags_ui::kGenericExperimentChoiceDisabled, switches::kPullToRefresh, "0"},
    {flags_ui::kGenericExperimentChoiceEnabled, switches::kPullToRefresh, "1"},
    {flag_descriptions::kPullToRefreshEnabledTouchscreen,
     switches::kPullToRefresh, "2"}};
#endif  // USE_AURA

const FeatureEntry::Choice kOverlayStrategiesChoices[] = {
    {flag_descriptions::kOverlayStrategiesDefault, "", ""},
    {flag_descriptions::kOverlayStrategiesNone,
     switches::kEnableHardwareOverlays, ""},
    {flag_descriptions::kOverlayStrategiesUnoccludedFullscreen,
     switches::kEnableHardwareOverlays, "single-fullscreen"},
    {flag_descriptions::kOverlayStrategiesUnoccluded,
     switches::kEnableHardwareOverlays, "single-fullscreen,single-on-top"},
    {flag_descriptions::kOverlayStrategiesOccludedAndUnoccluded,
     switches::kEnableHardwareOverlays,
     "single-fullscreen,single-on-top,underlay"},
};

const FeatureEntry::Choice kTouchTextSelectionStrategyChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kTouchSelectionStrategyCharacter,
     blink::switches::kTouchTextSelectionStrategy, "character"},
    {flag_descriptions::kTouchSelectionStrategyDirection,
     blink::switches::kTouchTextSelectionStrategy, "direction"}};

const FeatureEntry::Choice kTraceUploadURL[] = {
    {flags_ui::kGenericExperimentChoiceDisabled, "", ""},
    {flag_descriptions::kTraceUploadUrlChoiceOther, switches::kTraceUploadURL,
     "https://performance-insights.appspot.com/upload?tags=flags,Other"},
    {flag_descriptions::kTraceUploadUrlChoiceEmloading,
     switches::kTraceUploadURL,
     "https://performance-insights.appspot.com/upload?tags=flags,emloading"},
    {flag_descriptions::kTraceUploadUrlChoiceQa, switches::kTraceUploadURL,
     "https://performance-insights.appspot.com/upload?tags=flags,QA"},
    {flag_descriptions::kTraceUploadUrlChoiceTesting, switches::kTraceUploadURL,
     "https://performance-insights.appspot.com/upload?tags=flags,TestingTeam"}};

const FeatureEntry::Choice kLiteVideoDefaultDownlinkBandwidthKbps[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {"100", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "100"},
    {"150", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "150"},
    {"200", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "200"},
    {"250", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "250"},
    {"300", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "300"},
    {"350", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "350"},
    {"400", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "400"},
    {"450", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "450"},
    {"500", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "500"},
    {"600", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "600"},
    {"700", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "700"},
    {"800", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "800"},
    {"900", lite_video::switches::kLiteVideoDefaultDownlinkBandwidthKbps,
     "900"}};

#if defined(OS_WIN)
const FeatureEntry::Choice kUseAngleChoices[] = {
    {flag_descriptions::kUseAngleDefault, "", ""},
    {flag_descriptions::kUseAngleGL, switches::kUseANGLE,
     gl::kANGLEImplementationOpenGLName},
    {flag_descriptions::kUseAngleD3D11, switches::kUseANGLE,
     gl::kANGLEImplementationD3D11Name},
    {flag_descriptions::kUseAngleD3D9, switches::kUseANGLE,
     gl::kANGLEImplementationD3D9Name},
    {flag_descriptions::kUseAngleD3D11on12, switches::kUseANGLE,
     gl::kANGLEImplementationD3D11on12Name}};
<<<<<<< HEAD
#elif BUILDFLAG(IS_MAC)
const FeatureEntry::Choice kUseAngleChoicesMac[] = {
    {flag_descriptions::kUseAngleDefault, "", ""},
    {flag_descriptions::kUseAngleGL, switches::kUseANGLE,
     gl::kANGLEImplementationOpenGLName},
    {flag_descriptions::kUseAngleMetal, switches::kUseANGLE,
     gl::kANGLEImplementationMetalName}};
#elif BUILDFLAG(IS_ANDROID)
const FeatureEntry::Choice kUseAngleChoicesAndroid[] = {
    {flag_descriptions::kUseAngleDefault, "", ""},
    {flag_descriptions::kUseAngleGLES, switches::kUseANGLE,
     gl::kANGLEImplementationOpenGLESName},
    {flag_descriptions::kUseAngleVulkan, switches::kUseANGLE,
     gl::kANGLEImplementationVulkanName}};
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
const FeatureEntry::Choice kExtensionsToolbarZeroStateChoices[] = {
    {flag_descriptions::kExtensionsToolbarZeroStateChoicesDisabled, "", ""},
    {flag_descriptions::kExtensionsToolbarZeroStateVistWebStore,
     switches::kExtensionsToolbarZeroStateVariation,
     switches::kExtensionsToolbarZeroStateSingleWebStoreLink},
    {flag_descriptions::kExtensionsToolbarZeroStateExploreExtensionsByCategory,
     switches::kExtensionsToolbarZeroStateVariation,
     switches::kExtensionsToolbarZeroStateExploreExtensionsByCategory},
};
#endif  // ENABLE_EXTENSIONS

#if BUILDFLAG(IS_WIN)
const FeatureEntry::FeatureParam kDXGIWaitableSwapChain1Frame = {
    "DXGIWaitableSwapChainMaxQueuedFrames", "1"};

const FeatureEntry::FeatureParam kDXGIWaitableSwapChain2Frames = {
    "DXGIWaitableSwapChainMaxQueuedFrames", "2"};

const FeatureEntry::FeatureParam kDXGIWaitableSwapChain3Frames = {
    "DXGIWaitableSwapChainMaxQueuedFrames", "3"};

const FeatureEntry::FeatureVariation kDXGIWaitableSwapChainVariations[] = {
    {"Max 1 Frame", &kDXGIWaitableSwapChain1Frame, 1, nullptr},
    {"Max 2 Frames", &kDXGIWaitableSwapChain2Frames, 1, nullptr},
    {"Max 3 Frames", &kDXGIWaitableSwapChain3Frames, 1, nullptr}};
#endif

#if BUILDFLAG(IS_LINUX)
const FeatureEntry::Choice kOzonePlatformHintRuntimeChoices[] = {
    {flag_descriptions::kOzonePlatformHintChoiceDefault, "", ""},
    {flag_descriptions::kOzonePlatformHintChoiceAuto,
     switches::kOzonePlatformHint, "auto"},
#if BUILDFLAG(IS_OZONE_X11)
    {flag_descriptions::kOzonePlatformHintChoiceX11,
     switches::kOzonePlatformHint, "x11"},
#endif
#if BUILDFLAG(IS_OZONE_WAYLAND)
    {flag_descriptions::kOzonePlatformHintChoiceWayland,
     switches::kOzonePlatformHint, "wayland"},
#endif
};
=======
>>>>>>> chromium
#endif

#if BUILDFLAG(ENABLE_VR)
const FeatureEntry::Choice kWebXrForceRuntimeChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kWebXrRuntimeChoiceNone, switches::kWebXrForceRuntime,
     switches::kWebXrRuntimeNone},

#if BUILDFLAG(ENABLE_OPENXR)
    {flag_descriptions::kWebXrRuntimeChoiceOpenXR, switches::kWebXrForceRuntime,
     switches::kWebXrRuntimeOpenXr},
#endif  // ENABLE_OPENXR
};

const FeatureEntry::Choice KWebXrHandAnonymizationChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kWebXrHandAnonymizationChoiceRuntime,
     device::switches::kWebXrHandAnonymizationStrategy,
     device::switches::kWebXrHandAnonymizationStrategyRuntime},
    {flag_descriptions::kWebXrHandAnonymizationChoiceFallback,
     device::switches::kWebXrHandAnonymizationStrategy,
     device::switches::kWebXrHandAnonymizationStrategyFallback},
    {flag_descriptions::kWebXrHandAnonymizationChoiceNone,
     device::switches::kWebXrHandAnonymizationStrategy,
     device::switches::kWebXrHandAnonymizationStrategyNone},
};
#endif  // ENABLE_VR

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kElasticOverscrollFilterType[] = {
    {features::kElasticOverscrollType, features::kElasticOverscrollTypeFilter}};
const FeatureEntry::FeatureParam kElasticOverscrollTransformType[] = {
    {features::kElasticOverscrollType,
     features::kElasticOverscrollTypeTransform}};

const FeatureEntry::FeatureVariation kElasticOverscrollVariations[] = {
    {"Pixel shader stretch", kElasticOverscrollFilterType,
     base::size(kElasticOverscrollFilterType), nullptr},
    {"Transform stretch", kElasticOverscrollTransformType,
     base::size(kElasticOverscrollTransformType), nullptr}};

const FeatureEntry::Choice kReaderModeHeuristicsChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kReaderModeHeuristicsMarkup,
     switches::kReaderModeHeuristics,
     switches::reader_mode_heuristics::kOGArticle},
    {flag_descriptions::kReaderModeHeuristicsAdaboost,
     switches::kReaderModeHeuristics,
     switches::reader_mode_heuristics::kAdaBoost},
    {flag_descriptions::kReaderModeHeuristicsAlwaysOn,
     switches::kReaderModeHeuristics,
     switches::reader_mode_heuristics::kAlwaysTrue},
    {flag_descriptions::kReaderModeHeuristicsAlwaysOff,
     switches::kReaderModeHeuristics, switches::reader_mode_heuristics::kNone},
    {flag_descriptions::kReaderModeHeuristicsAllArticles,
     switches::kReaderModeHeuristics,
     switches::reader_mode_heuristics::kAllArticles},
};

const FeatureEntry::Choice kForceUpdateMenuTypeChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kUpdateMenuTypeNone, switches::kForceUpdateMenuType,
     "none"},
    {flag_descriptions::kUpdateMenuTypeUpdateAvailable,
     switches::kForceUpdateMenuType, "update_available"},
    {flag_descriptions::kUpdateMenuTypeUnsupportedOSVersion,
     switches::kForceUpdateMenuType, "unsupported_os_version"},
    {flag_descriptions::kUpdateMenuTypeInlineUpdateSuccess,
     switches::kForceUpdateMenuType, "inline_update_success"},
    {flag_descriptions::kUpdateMenuTypeInlineUpdateDialogCanceled,
     switches::kForceUpdateMenuType, "inline_update_dialog_canceled"},
    {flag_descriptions::kUpdateMenuTypeInlineUpdateDialogFailed,
     switches::kForceUpdateMenuType, "inline_update_dialog_failed"},
    {flag_descriptions::kUpdateMenuTypeInlineUpdateDownloadFailed,
     switches::kForceUpdateMenuType, "inline_update_download_failed"},
    {flag_descriptions::kUpdateMenuTypeInlineUpdateDownloadCanceled,
     switches::kForceUpdateMenuType, "inline_update_download_canceled"},
    {flag_descriptions::kUpdateMenuTypeInlineUpdateInstallFailed,
     switches::kForceUpdateMenuType, "inline_update_install_failed"},
};
#else  // !defined(OS_ANDROID)
const FeatureEntry::FeatureParam kReaderModeOfferInSettings[] = {
    {switches::kReaderModeDiscoverabilityParamName,
     switches::kReaderModeOfferInSettings}};

const FeatureEntry::FeatureVariation kReaderModeDiscoverabilityVariations[] = {
    {"available in settings", kReaderModeOfferInSettings,
     base::size(kReaderModeOfferInSettings), nullptr}};
#endif  // OS_ANDROID

#if defined(OS_ANDROID)
const FeatureEntry::FeatureVariation kAdaptiveButtonInTopToolbarVariations[] = {
    {
        "Always None",
        (FeatureEntry::FeatureParam[]){{"mode", "always-none"}},
        1,
        nullptr,
    },
    {
        "Always New Tab",
        (FeatureEntry::FeatureParam[]){{"mode", "always-new-tab"}},
        1,
        nullptr,
    },
    {
        "Always Share",
        (FeatureEntry::FeatureParam[]){{"mode", "always-share"}},
        1,
        nullptr,
    },
    {
        "Always Voice",
        (FeatureEntry::FeatureParam[]){{"mode", "always-voice"}},
        1,
        nullptr,
    },
};

const FeatureEntry::FeatureVariation
    kAdaptiveButtonInTopToolbarCustomizationVariations[] = {
        {
            "New Tab",
            (FeatureEntry::FeatureParam[]){
                {"default_segment", "new-tab"},
                {"ignore_segmentation_results", "true"}},
            1,
            nullptr,
        },
        {
            "Share",
            (FeatureEntry::FeatureParam[]){
                {"default_segment", "share"},
                {"ignore_segmentation_results", "true"}},
            1,
            nullptr,
        },
        {
            "Voice",
            (FeatureEntry::FeatureParam[]){
                {"default_segment", "voice"},
                {"ignore_segmentation_results", "true"}},
            1,
            nullptr,
        },
};
#endif  // OS_ANDROID

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kHideDismissButton[] = {
    {"dismiss_button", "hide"}};

const FeatureEntry::FeatureParam kSuppressBottomSheet[] = {
    {"consecutive_active_dismissal_limit", "3"}};

const FeatureEntry::FeatureVariation kMobileIdentityConsistencyVariations[] = {
    {"Hide Dismiss Button", kHideDismissButton, base::size(kHideDismissButton),
     nullptr},
    {"Suppress Bottom Sheet", kSuppressBottomSheet,
     base::size(kSuppressBottomSheet), nullptr},
};
#endif  // OS_ANDROID

#if !BUILDFLAG(IS_CHROMEOS)
const FeatureEntry::FeatureParam kForceDark_SimpleHsl[] = {
    {"inversion_method", "hsl_based"},
    {"image_behavior", "none"},
    {"text_lightness_threshold", "256"},
    {"background_lightness_threshold", "0"}};

const FeatureEntry::FeatureParam kForceDark_SimpleCielab[] = {
    {"inversion_method", "cielab_based"},
    {"image_behavior", "none"},
    {"text_lightness_threshold", "256"},
    {"background_lightness_threshold", "0"}};

const FeatureEntry::FeatureParam kForceDark_SimpleRgb[] = {
    {"inversion_method", "rgb_based"},
    {"image_behavior", "none"},
    {"text_lightness_threshold", "256"},
    {"background_lightness_threshold", "0"}};

const FeatureEntry::FeatureParam kForceDark_SelectiveImageInversion[] = {
    {"inversion_method", "cielab_based"},
    {"image_behavior", "selective"},
    {"text_lightness_threshold", "256"},
    {"background_lightness_threshold", "0"}};

const FeatureEntry::FeatureParam kForceDark_SelectiveElementInversion[] = {
    {"inversion_method", "cielab_based"},
    {"image_behavior", "none"},
    {"text_lightness_threshold", "150"},
    {"background_lightness_threshold", "205"}};

const FeatureEntry::FeatureParam kForceDark_SelectiveGeneralInversion[] = {
    {"inversion_method", "cielab_based"},
    {"image_behavior", "selective"},
    {"text_lightness_threshold", "150"},
    {"background_lightness_threshold", "205"}};

const FeatureEntry::FeatureParam kForceDark_IncreaseTextContrast[] = {
    {"increase_text_contrast", "true"}};

const FeatureEntry::FeatureVariation kForceDarkVariations[] = {
    {"with simple HSL-based inversion", kForceDark_SimpleHsl,
     base::size(kForceDark_SimpleHsl), nullptr},
    {"with simple CIELAB-based inversion", kForceDark_SimpleCielab,
     base::size(kForceDark_SimpleCielab), nullptr},
    {"with simple RGB-based inversion", kForceDark_SimpleRgb,
     base::size(kForceDark_SimpleRgb), nullptr},
    {"with selective image inversion", kForceDark_SelectiveImageInversion,
     base::size(kForceDark_SelectiveImageInversion), nullptr},
    {"with selective inversion of non-image elements",
     kForceDark_SelectiveElementInversion,
     base::size(kForceDark_SelectiveElementInversion), nullptr},
    {"with selective inversion of everything",
     kForceDark_SelectiveGeneralInversion,
     base::size(kForceDark_SelectiveGeneralInversion), nullptr},
    {"with increased text contrast", kForceDark_IncreaseTextContrast,
     base::size(kForceDark_IncreaseTextContrast), nullptr}};
#endif  // !OS_CHROMEOS

const FeatureEntry::FeatureParam kMBIModeLegacy[] = {{"mode", "legacy"}};
const FeatureEntry::FeatureParam kMBIModeEnabledPerRenderProcessHost[] = {
    {"mode", "per_render_process_host"}};
const FeatureEntry::FeatureParam kMBIModeEnabledPerSiteInstance[] = {
    {"mode", "per_site_instance"}};

const FeatureEntry::FeatureVariation kMBIModeVariations[] = {
    {"legacy mode", kMBIModeLegacy, base::size(kMBIModeLegacy), nullptr},
    {"per render process host", kMBIModeEnabledPerRenderProcessHost,
     base::size(kMBIModeEnabledPerRenderProcessHost), nullptr},
    {"per site instance", kMBIModeEnabledPerSiteInstance,
     base::size(kMBIModeEnabledPerSiteInstance), nullptr}};

const FeatureEntry::FeatureParam kIntensiveWakeUpThrottlingAfter10Seconds[] = {
    {blink::features::kIntensiveWakeUpThrottling_GracePeriodSeconds_Name,
     "10"}};

const FeatureEntry::FeatureVariation kIntensiveWakeUpThrottlingVariations[] = {
    {"10 seconds after a tab is hidden (facilitates testing)",
     kIntensiveWakeUpThrottlingAfter10Seconds,
     base::size(kIntensiveWakeUpThrottlingAfter10Seconds), nullptr},
};

const FeatureEntry::FeatureParam kFencedFramesImplementationTypeShadowDOM[] = {
    {"implementation_type", "shadow_dom"}};
const FeatureEntry::FeatureParam kFencedFramesImplementationTypeMPArch[] = {
    {"implementation_type", "mparch"}};

const FeatureEntry::FeatureVariation
    kFencedFramesImplementationTypeVariations[] = {
        {"with ShadowDOM", kFencedFramesImplementationTypeShadowDOM,
         base::size(kFencedFramesImplementationTypeShadowDOM), nullptr},
        {"with multiple page architecture",
         kFencedFramesImplementationTypeMPArch,
         base::size(kFencedFramesImplementationTypeMPArch), nullptr}};

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
const FeatureEntry::FeatureParam kArcVmMemorySizeShift_200[] = {
    {"shift_mib", "-200"}};
const FeatureEntry::FeatureParam kArcVmMemorySizeShift_500[] = {
    {"shift_mib", "-500"}};
const FeatureEntry::FeatureParam kArcVmMemorySizeShift_800[] = {
    {"shift_mib", "-800"}};

const FeatureEntry::FeatureVariation kArcVmMemorySizeVariations[] = {
    {"shift -200MiB", kArcVmMemorySizeShift_200,
     std::size(kArcVmMemorySizeShift_200), nullptr},
    {"shift -500MiB", kArcVmMemorySizeShift_500,
     std::size(kArcVmMemorySizeShift_500), nullptr},
    {"shift -800MiB", kArcVmMemorySizeShift_800,
     std::size(kArcVmMemorySizeShift_800), nullptr},
};
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kCloseTabSuggestionsStale_Immediate[] = {
    {"baseline_tab_suggestions", "true"},
    {"baseline_close_tab_suggestions", "true"}};
const FeatureEntry::FeatureParam kCloseTabSuggestionsStale_4Hours[] = {
    {"close_tab_suggestions_stale_time_ms", "14400000"}};
const FeatureEntry::FeatureParam kCloseTabSuggestionsStale_8Hours[] = {
    {"close_tab_suggestions_stale_time_ms", "28800000"}};
const FeatureEntry::FeatureParam kCloseTabSuggestionsStale_7Days[] = {
    {"close_tab_suggestions_stale_time_ms", "604800000"}};
const FeatureEntry::FeatureParam kCloseTabSuggestionsTimeSiteEngagement[] = {
    {"close_tab_min_num_tabs", "5"},
    {"close_tab_features_time_last_used_enabled", "true"},
    {"close_tab_features_time_last_used_transform", "MEAN_VARIANCE"},
    {"close_tab_features_time_last_used_threshold", "0.5"},
    {"close_tab_features_site_engagement_enabled", "true"},
    {"close_tab_features_site_engagement_threshold", "90.0"},
};
const FeatureEntry::FeatureParam kGroupAndCloseTabSuggestions_Immediate[] = {
    {"baseline_tab_suggestions", "true"},
    {"baseline_group_tab_suggestions", "true"},
    {"baseline_close_tab_suggestions", "true"}};

const FeatureEntry::FeatureVariation kCloseTabSuggestionsStaleVariations[] = {
    {"Close Immediate", kCloseTabSuggestionsStale_Immediate,
     base::size(kCloseTabSuggestionsStale_Immediate), nullptr},
    {"Group+Close Immediate", kGroupAndCloseTabSuggestions_Immediate,
     base::size(kGroupAndCloseTabSuggestions_Immediate), nullptr},
    {"4 hours", kCloseTabSuggestionsStale_4Hours,
     base::size(kCloseTabSuggestionsStale_4Hours), nullptr},
    {"8 hours", kCloseTabSuggestionsStale_8Hours,
     base::size(kCloseTabSuggestionsStale_8Hours), nullptr},
    {"7 days", kCloseTabSuggestionsStale_7Days,
     base::size(kCloseTabSuggestionsStale_7Days), nullptr},
    {"Time & Site Engagement", kCloseTabSuggestionsTimeSiteEngagement,
     base::size(kCloseTabSuggestionsTimeSiteEngagement), nullptr},
};

const FeatureEntry::FeatureParam kWebNoteStylizeRandomizeParam[] = {
    {"randomize_order", "true"}};
const FeatureEntry::FeatureVariation kWebNoteStylizeVariations[] = {
    {"With Randomized Order", kWebNoteStylizeRandomizeParam,
     base::size(kWebNoteStylizeRandomizeParam), nullptr}};
#endif  // OS_ANDROID
>>>>>>> chromium

const FeatureEntry::Choice kEnableGpuRasterizationChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flags_ui::kGenericExperimentChoiceEnabled,
     switches::kEnableGpuRasterization, ""},
    {flags_ui::kGenericExperimentChoiceDisabled,
     switches::kDisableGpuRasterization, ""},
};

<<<<<<< HEAD
const FeatureEntry::FeatureParam kEnableLazyLoadImageForAllInvisiblePage[] = {
    {"enabled_page_type", "all_invisible_page"}};
const FeatureEntry::FeatureParam kEnableLazyLoadImageForPrerenderPage[] = {
    {"enabled_page_type", "prerender_page"}};

const FeatureEntry::FeatureVariation
    kSearchSuggsetionPrerenderTypeVariations[] = {
        {"for all invisible page", kEnableLazyLoadImageForAllInvisiblePage,
         std::size(kEnableLazyLoadImageForAllInvisiblePage), nullptr},
        {"for prerendering page", kEnableLazyLoadImageForPrerenderPage,
         std::size(kEnableLazyLoadImageForPrerenderPage), nullptr}};
=======
const FeatureEntry::Choice kEnableOopRasterizationChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flags_ui::kGenericExperimentChoiceEnabled,
     switches::kEnableOopRasterization, ""},
    {flags_ui::kGenericExperimentChoiceDisabled,
     switches::kDisableOopRasterization, ""},
};

const FeatureEntry::Choice kExtensionContentVerificationChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kExtensionContentVerificationBootstrap,
     switches::kExtensionContentVerification,
     switches::kExtensionContentVerificationBootstrap},
    {flag_descriptions::kExtensionContentVerificationEnforce,
     switches::kExtensionContentVerification,
     switches::kExtensionContentVerificationEnforce},
    {flag_descriptions::kExtensionContentVerificationEnforceStrict,
     switches::kExtensionContentVerification,
     switches::kExtensionContentVerificationEnforceStrict},
};
>>>>>>> chromium

const FeatureEntry::Choice kTopChromeTouchUiChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flags_ui::kGenericExperimentChoiceAutomatic, switches::kTopChromeTouchUi,
     switches::kTopChromeTouchUiAuto},
    {flags_ui::kGenericExperimentChoiceDisabled, switches::kTopChromeTouchUi,
     switches::kTopChromeTouchUiDisabled},
    {flags_ui::kGenericExperimentChoiceEnabled, switches::kTopChromeTouchUi,
     switches::kTopChromeTouchUiEnabled}};

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kCctSignInPromptAlways[] = {
    {"cadence_day", "0"},
    {"show_limit", "10000"},
    {"user_act_count", "10000"},
    {"if_allowed_by_embedder", "true"},
    {"if_enabled_by_embedder", "true"}};
const FeatureEntry::FeatureParam kCctSignInTestOnly[] = {
    {"cadence_day", "0"},
    {"show_limit", "4"},
    {"user_act_count", "2"},
    {"if_allowed_by_embedder", "true"},
    {"if_enabled_by_embedder", "true"}};

const FeatureEntry::FeatureVariation kCctSignInPromptVariations[] = {
    {"always show", kCctSignInPromptAlways, std::size(kCctSignInPromptAlways),
     nullptr},
    {"for test", kCctSignInTestOnly, std::size(kCctSignInTestOnly), nullptr}};
#endif

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kToastWith8sNonActionable4Seconds[] = {
    {"toast_timeout", "8s"},
    {"toast_without_action_timeout", "4s"},
    {"toast_demo_mode", "true"}};
const FeatureEntry::FeatureParam kToastWith8sNonActionable6Seconds[] = {
    {"toast_timeout", "8s"},
    {"toast_without_action_timeout", "6s"},
    {"toast_demo_mode", "true"}};
const FeatureEntry::FeatureParam kToastWith10sNonActionable6Seconds[] = {
    {"toast_timeout", "8s"},
    {"toast_without_action_timeout", "6s"},
    {"toast_demo_mode", "true"}};
const FeatureEntry::FeatureParam kToastWith6Seconds[] = {
    {"toast_timeout", "6s"},
    {"toast_without_action_timeout", "6s"},
    {"toast_demo_mode", "true"}};
const FeatureEntry::FeatureParam kToastWith8Seconds[] = {
    {"toast_timeout", "8s"},
    {"toast_without_action_timeout", "8s"},
    {"toast_demo_mode", "true"}};
const FeatureEntry::FeatureParam kToastWith10Seconds[] = {
    {"toast_timeout", "10s"},
    {"toast_without_action_timeout", "10s"},
    {"toast_demo_mode", "true"}};

const FeatureEntry::FeatureVariation kToastVariations[] = {
    {"with 8s (actionable) and 4s (nonactionable)",
     kToastWith8sNonActionable4Seconds,
     std::size(kToastWith8sNonActionable4Seconds), nullptr},
    {"with 8s (actionable) and 6s (nonactionable)",
     kToastWith8sNonActionable6Seconds,
     std::size(kToastWith8sNonActionable6Seconds), nullptr},
    {"with 10s (actionable) and 6s (nonactionable)",
     kToastWith10sNonActionable6Seconds,
     std::size(kToastWith10sNonActionable6Seconds), nullptr},
    {"with 6s", kToastWith6Seconds, std::size(kToastWith6Seconds), nullptr},
    {"with 8s", kToastWith8Seconds, std::size(kToastWith8Seconds), nullptr},
    {"with 10s", kToastWith10Seconds, std::size(kToastWith10Seconds), nullptr}};
#endif

#if BUILDFLAG(IS_CHROMEOS)

const FeatureEntry::FeatureParam kRoundedWindowRadius8 = {
    chromeos::features::kRoundedWindowsRadius, "8"};

const FeatureEntry::FeatureParam kRoundedWindowRadius10 = {
    chromeos::features::kRoundedWindowsRadius, "10"};

const FeatureEntry::FeatureParam kRoundedWindowRadius12 = {
    chromeos::features::kRoundedWindowsRadius, "12"};

const FeatureEntry::FeatureParam kRoundedWindowRadius14 = {
    chromeos::features::kRoundedWindowsRadius, "14"};

const FeatureEntry::FeatureParam kRoundedWindowRadius16 = {
    chromeos::features::kRoundedWindowsRadius, "16"};

const FeatureEntry::FeatureParam kRoundedWindowRadius18 = {
    chromeos::features::kRoundedWindowsRadius, "18"};

const FeatureEntry::FeatureVariation kRoundedWindowsRadiusVariation[] = {
    {"8", &kRoundedWindowRadius8, 1, nullptr},
    {"10", &kRoundedWindowRadius10, 1, nullptr},
    {"12", &kRoundedWindowRadius12, 1, nullptr},
    {"14", &kRoundedWindowRadius14, 1, nullptr},
    {"16", &kRoundedWindowRadius16, 1, nullptr},
    {"18", &kRoundedWindowRadius18, 1, nullptr},
};

const FeatureEntry::FeatureParam
    kArcRoundedWindowCompatStrategyLeftRightBottomGesture = {
        arc::kRoundedWindowCompatStrategy,
        arc::kRoundedWindowCompatStrategy_LeftRightBottomGesture};

const FeatureEntry::FeatureParam
    kArcRoundedWindowCompatStrategyBottomOnlyGesture = {
        arc::kRoundedWindowCompatStrategy,
        arc::kRoundedWindowCompatStrategy_BottomOnlyGesture};

const FeatureEntry::FeatureVariation kArcRoundedWindowCompatVariation[] = {
    {"Left-Right-Bottom Gesture Exclusion",
     &kArcRoundedWindowCompatStrategyLeftRightBottomGesture, 1, nullptr},
    {"Bottom-only Gesture Exclusion",
     &kArcRoundedWindowCompatStrategyBottomOnlyGesture, 1, nullptr},
};

const FeatureEntry::FeatureParam kZinkEnableRecommended[] = {
    {"BorealisZinkGlDriverParam", "ZinkEnableRecommended"}};
const FeatureEntry::FeatureParam kZinkEnableAll[] = {
    {"BorealisZinkGlDriverParam", "ZinkEnableAll"}};

const FeatureEntry::FeatureVariation kBorealisZinkGlDriverVariations[] = {
    {"for recommended apps", kZinkEnableRecommended,
     std::size(kZinkEnableRecommended), nullptr},
    {"for all apps", kZinkEnableAll, std::size(kZinkEnableAll), nullptr}};

const char kArcEnableVirtioBlkForDataInternalName[] =
    "arc-enable-virtio-blk-for-data";

const char kProjectorServerSideSpeechRecognition[] =
    "enable-projector-server-side-speech-recognition";

const char kArcEnableAttestationFlag[] = "arc-enable-attestation";

#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
const char kArcUseHighMemoryDalvikProfileInternalName[] =
    "arc-use-high-memory-dalvik-profile";
const char kLacrosAvailabilityIgnoreInternalName[] =
    "lacros-availability-ignore";
const char kLacrosPrimaryInternalName[] = "lacros-primary";
const char kLacrosSupportInternalName[] = "lacros-support";
const char kLacrosStabilityInternalName[] = "lacros-stability";
const char kWebAppsCrosapiInternalName[] = "web-apps-crosapi";

const FeatureEntry::Choice kLacrosStabilityChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kLacrosStabilityLeastStableDescription,
     crosapi::browser_util::kLacrosStabilitySwitch,
     crosapi::browser_util::kLacrosStabilityLeastStable},
    {flag_descriptions::kLacrosStabilityLessStableDescription,
     crosapi::browser_util::kLacrosStabilitySwitch,
     crosapi::browser_util::kLacrosStabilityLessStable},
    {flag_descriptions::kLacrosStabilityMoreStableDescription,
     crosapi::browser_util::kLacrosStabilitySwitch,
     crosapi::browser_util::kLacrosStabilityMoreStable},
};

const char kLacrosSelectionInternalName[] = "lacros-selection";

const FeatureEntry::Choice kLacrosSelectionChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kLacrosSelectionStatefulDescription,
     crosapi::browser_util::kLacrosSelectionSwitch,
     crosapi::browser_util::kLacrosSelectionStateful},
    {flag_descriptions::kLacrosSelectionRootfsDescription,
     crosapi::browser_util::kLacrosSelectionSwitch,
     crosapi::browser_util::kLacrosSelectionRootfs},
};

#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
const FeatureEntry::Choice kCrosRegionsModeChoices[] = {
    {flag_descriptions::kCrosRegionsModeDefault, "", ""},
    {flag_descriptions::kCrosRegionsModeOverride,
     chromeos::switches::kCrosRegionsMode,
     chromeos::switches::kCrosRegionsModeOverride},
    {flag_descriptions::kCrosRegionsModeHide,
     chromeos::switches::kCrosRegionsMode,
     chromeos::switches::kCrosRegionsModeHide},
};
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

const FeatureEntry::Choice kForceUIDirectionChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kForceDirectionLtr, switches::kForceUIDirection,
     switches::kForceDirectionLTR},
    {flag_descriptions::kForceDirectionRtl, switches::kForceUIDirection,
     switches::kForceDirectionRTL},
};

const FeatureEntry::Choice kForceTextDirectionChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kForceDirectionLtr, switches::kForceTextDirection,
     switches::kForceDirectionLTR},
    {flag_descriptions::kForceDirectionRtl, switches::kForceTextDirection,
     switches::kForceDirectionRTL},
};

#if BUILDFLAG(IS_CHROMEOS_ASH)
const FeatureEntry::FeatureParam
    kDesktopPWAsAttentionBadgingCrOSApiAndNotifications[] = {
        {"badge-source",
         switches::kDesktopPWAsAttentionBadgingCrOSApiAndNotifications}};
const FeatureEntry::FeatureParam
    kDesktopPWAsAttentionBadgingCrOSApiOverridesNotifications[] = {
        {"badge-source",
         switches::kDesktopPWAsAttentionBadgingCrOSApiOverridesNotifications}};
const FeatureEntry::FeatureParam kDesktopPWAsAttentionBadgingCrOSApiOnly[] = {
    {"badge-source", switches::kDesktopPWAsAttentionBadgingCrOSApiOnly}};
const FeatureEntry::FeatureParam
    kDesktopPWAsAttentionBadgingCrOSNotificationsOnly[] = {
        {"badge-source",
         switches::kDesktopPWAsAttentionBadgingCrOSNotificationsOnly}};

const FeatureEntry::FeatureVariation
    kDesktopPWAsAttentionBadgingCrOSVariations[] = {
        {flag_descriptions::kDesktopPWAsAttentionBadgingCrOSApiAndNotifications,
         kDesktopPWAsAttentionBadgingCrOSApiAndNotifications,
         base::size(kDesktopPWAsAttentionBadgingCrOSApiAndNotifications),
         nullptr},
        {flag_descriptions::
             kDesktopPWAsAttentionBadgingCrOSApiOverridesNotifications,
         kDesktopPWAsAttentionBadgingCrOSApiOverridesNotifications,
         base::size(kDesktopPWAsAttentionBadgingCrOSApiOverridesNotifications),
         nullptr},
        {flag_descriptions::kDesktopPWAsAttentionBadgingCrOSApiOnly,
         kDesktopPWAsAttentionBadgingCrOSApiOnly,
         base::size(kDesktopPWAsAttentionBadgingCrOSApiOnly), nullptr},
        {flag_descriptions::kDesktopPWAsAttentionBadgingCrOSNotificationsOnly,
         kDesktopPWAsAttentionBadgingCrOSNotificationsOnly,
         base::size(kDesktopPWAsAttentionBadgingCrOSNotificationsOnly),
         nullptr},
};

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
=======
>>>>>>> chromium
const FeatureEntry::Choice kSchedulerConfigurationChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kSchedulerConfigurationConservative,
     ash::switches::kSchedulerConfiguration,
     ash::switches::kSchedulerConfigurationConservative},
    {flag_descriptions::kSchedulerConfigurationPerformance,
     ash::switches::kSchedulerConfiguration,
     ash::switches::kSchedulerConfigurationPerformance},
};

<<<<<<< HEAD
const FeatureEntry::FeatureParam kDynamicSearchUpdateAnimationDuration_50[] = {
    {"search_result_translation_duration", "50"}};
const FeatureEntry::FeatureParam kDynamicSearchUpdateAnimationDuration_100[] = {
    {"search_result_translation_duration", "100"}};
const FeatureEntry::FeatureParam kDynamicSearchUpdateAnimationDuration_150[] = {
    {"search_result_translation_duration", "150"}};

const FeatureEntry::FeatureVariation kDynamicSearchUpdateAnimationVariations[] =
    {{"50ms", kDynamicSearchUpdateAnimationDuration_50,
      std::size(kDynamicSearchUpdateAnimationDuration_50), nullptr},
     {"100ms", kDynamicSearchUpdateAnimationDuration_100,
      std::size(kDynamicSearchUpdateAnimationDuration_100), nullptr},
     {"150ms", kDynamicSearchUpdateAnimationDuration_150,
      std::size(kDynamicSearchUpdateAnimationDuration_150), nullptr}};
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(ENABLE_NACL)
// Note: This needs to be kept in sync with parsing in
// content/common/zygote/zygote_communication_linux.cc
const FeatureEntry::Choice kVerboseLoggingInNaclChoices[] = {
    {flag_descriptions::kVerboseLoggingInNaclChoiceDefault, "", ""},
    {flag_descriptions::kVerboseLoggingInNaclChoiceLow,
     switches::kVerboseLoggingInNacl, switches::kVerboseLoggingInNaclChoiceLow},
    {flag_descriptions::kVerboseLoggingInNaclChoiceMedium,
     switches::kVerboseLoggingInNacl,
     switches::kVerboseLoggingInNaclChoiceMedium},
    {flag_descriptions::kVerboseLoggingInNaclChoiceHigh,
     switches::kVerboseLoggingInNacl,
     switches::kVerboseLoggingInNaclChoiceHigh},
    {flag_descriptions::kVerboseLoggingInNaclChoiceHighest,
     switches::kVerboseLoggingInNacl,
     switches::kVerboseLoggingInNaclChoiceHighest},
    {flag_descriptions::kVerboseLoggingInNaclChoiceDisabled,
     switches::kVerboseLoggingInNacl,
     switches::kVerboseLoggingInNaclChoiceDisabled},
=======
#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kCompactSuggestions_SemicompactVariant[] = {
    {"omnibox_compact_suggestions_variant", "semi-compact"}};

const FeatureEntry::FeatureVariation kCompactSuggestionsVariations[] = {
    {"- Semi-compact", kCompactSuggestions_SemicompactVariant,
     base::size(kCompactSuggestions_SemicompactVariant), nullptr},
};
#endif  // OS_ANDROID

const FeatureEntry::Choice kEnableUseZoomForDSFChoices[] = {
    {flag_descriptions::kEnableUseZoomForDsfChoiceDefault, "", ""},
    {flag_descriptions::kEnableUseZoomForDsfChoiceEnabled,
     switches::kEnableUseZoomForDSF, "true"},
    {flag_descriptions::kEnableUseZoomForDsfChoiceDisabled,
     switches::kEnableUseZoomForDSF, "false"},
>>>>>>> chromium
};

const FeatureEntry::Choice kSiteIsolationOptOutChoices[] = {
    {flag_descriptions::kSiteIsolationOptOutChoiceDefault, "", ""},
    {flag_descriptions::kSiteIsolationOptOutChoiceOptOut,
     switches::kDisableSiteIsolation, ""},
};

const FeatureEntry::Choice kForceColorProfileChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kForceColorProfileSRGB,
     switches::kForceDisplayColorProfile, "srgb"},
    {flag_descriptions::kForceColorProfileP3,
     switches::kForceDisplayColorProfile, "display-p3-d65"},
    {flag_descriptions::kForceColorProfileColorSpin,
     switches::kForceDisplayColorProfile, "color-spin-gamma24"},
    {flag_descriptions::kForceColorProfileSCRGBLinear,
     switches::kForceDisplayColorProfile, "scrgb-linear"},
    {flag_descriptions::kForceColorProfileHDR10,
     switches::kForceDisplayColorProfile, "hdr10"},
};

const FeatureEntry::Choice kForceEffectiveConnectionTypeChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kEffectiveConnectionTypeUnknownDescription,
     network::switches::kForceEffectiveConnectionType,
     net::kEffectiveConnectionTypeUnknown},
    {flag_descriptions::kEffectiveConnectionTypeOfflineDescription,
     network::switches::kForceEffectiveConnectionType,
     net::kEffectiveConnectionTypeOffline},
    {flag_descriptions::kEffectiveConnectionTypeSlow2GDescription,
     network::switches::kForceEffectiveConnectionType,
     net::kEffectiveConnectionTypeSlow2G},
    {flag_descriptions::kEffectiveConnectionTypeSlow2GOnCellularDescription,
     network::switches::kForceEffectiveConnectionType,
     net::kEffectiveConnectionTypeSlow2GOnCellular},
    {flag_descriptions::kEffectiveConnectionType2GDescription,
     network::switches::kForceEffectiveConnectionType,
     net::kEffectiveConnectionType2G},
    {flag_descriptions::kEffectiveConnectionType3GDescription,
     network::switches::kForceEffectiveConnectionType,
     net::kEffectiveConnectionType3G},
    {flag_descriptions::kEffectiveConnectionType4GDescription,
     network::switches::kForceEffectiveConnectionType,
     net::kEffectiveConnectionType4G},
};

// Ensure that all effective connection types returned by Network Quality
// Estimator (NQE) are also exposed via flags.
static_assert(net::EFFECTIVE_CONNECTION_TYPE_LAST + 2 ==
                  base::size(kForceEffectiveConnectionTypeChoices),
              "ECT enum value is not handled.");
static_assert(net::EFFECTIVE_CONNECTION_TYPE_UNKNOWN == 0,
              "ECT enum value is not handled.");
static_assert(net::EFFECTIVE_CONNECTION_TYPE_4G + 1 ==
                  net::EFFECTIVE_CONNECTION_TYPE_LAST,
              "ECT enum value is not handled.");

const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitNone[] = {
    {"max_srp_prefetches", "-1"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitZero[] = {
    {"max_srp_prefetches", "0"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitOne[] = {
    {"max_srp_prefetches", "1"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitTwo[] = {
    {"max_srp_prefetches", "2"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitThree[] = {
    {"max_srp_prefetches", "3"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitFour[] = {
    {"max_srp_prefetches", "4"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitFive[] = {
    {"max_srp_prefetches", "5"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitTen[] = {
    {"max_srp_prefetches", "10"}};
const FeatureEntry::FeatureParam kIsolatedPrerenderPrefetchLimitFifteen[] = {
    {"max_srp_prefetches", "15"}};

const FeatureEntry::FeatureVariation
    kIsolatedPrerenderFeatureWithPrefetchLimit[] = {
        {"Unlimited Prefetches", kIsolatedPrerenderPrefetchLimitNone,
         base::size(kIsolatedPrerenderPrefetchLimitNone), nullptr},
        {"Zero Prefetches", kIsolatedPrerenderPrefetchLimitZero,
         base::size(kIsolatedPrerenderPrefetchLimitZero), nullptr},
        {"One Prefetch", kIsolatedPrerenderPrefetchLimitOne,
         base::size(kIsolatedPrerenderPrefetchLimitOne), nullptr},
        {"Two Prefetches", kIsolatedPrerenderPrefetchLimitTwo,
         base::size(kIsolatedPrerenderPrefetchLimitTwo), nullptr},
        {"Three Prefetches", kIsolatedPrerenderPrefetchLimitThree,
         base::size(kIsolatedPrerenderPrefetchLimitThree), nullptr},
        {"Four Prefetches", kIsolatedPrerenderPrefetchLimitFour,
         base::size(kIsolatedPrerenderPrefetchLimitFour), nullptr},
        {"Five Prefetches", kIsolatedPrerenderPrefetchLimitFive,
         base::size(kIsolatedPrerenderPrefetchLimitFive), nullptr},
        {"Ten Prefetches", kIsolatedPrerenderPrefetchLimitTen,
         base::size(kIsolatedPrerenderPrefetchLimitTen), nullptr},
        {"Fifteen Prefetches", kIsolatedPrerenderPrefetchLimitFifteen,
         base::size(kIsolatedPrerenderPrefetchLimitFifteen), nullptr},
};

const FeatureEntry::Choice kMemlogModeChoices[] = {
    {flags_ui::kGenericExperimentChoiceDisabled, "", ""},
    {flag_descriptions::kMemlogModeMinimal, heap_profiling::kMemlogMode,
     heap_profiling::kMemlogModeMinimal},
    {flag_descriptions::kMemlogModeAll, heap_profiling::kMemlogMode,
     heap_profiling::kMemlogModeAll},
    {flag_descriptions::kMemlogModeBrowser, heap_profiling::kMemlogMode,
     heap_profiling::kMemlogModeBrowser},
    {flag_descriptions::kMemlogModeGpu, heap_profiling::kMemlogMode,
     heap_profiling::kMemlogModeGpu},
    {flag_descriptions::kMemlogModeAllRenderers, heap_profiling::kMemlogMode,
     heap_profiling::kMemlogModeAllRenderers},
    {flag_descriptions::kMemlogModeRendererSampling,
     heap_profiling::kMemlogMode, heap_profiling::kMemlogModeRendererSampling},
};

const FeatureEntry::Choice kMemlogStackModeChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kMemlogStackModeNative,
     heap_profiling::kMemlogStackMode, heap_profiling::kMemlogStackModeNative},
    {flag_descriptions::kMemlogStackModeNativeWithThreadNames,
     heap_profiling::kMemlogStackMode,
     heap_profiling::kMemlogStackModeNativeWithThreadNames},
};

const FeatureEntry::Choice kMemlogSamplingRateChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kMemlogSamplingRate10KB,
     heap_profiling::kMemlogSamplingRate,
     heap_profiling::kMemlogSamplingRate10KB},
    {flag_descriptions::kMemlogSamplingRate50KB,
     heap_profiling::kMemlogSamplingRate,
     heap_profiling::kMemlogSamplingRate50KB},
    {flag_descriptions::kMemlogSamplingRate100KB,
     heap_profiling::kMemlogSamplingRate,
     heap_profiling::kMemlogSamplingRate100KB},
    {flag_descriptions::kMemlogSamplingRate500KB,
     heap_profiling::kMemlogSamplingRate,
     heap_profiling::kMemlogSamplingRate500KB},
    {flag_descriptions::kMemlogSamplingRate1MB,
     heap_profiling::kMemlogSamplingRate,
     heap_profiling::kMemlogSamplingRate1MB},
    {flag_descriptions::kMemlogSamplingRate5MB,
     heap_profiling::kMemlogSamplingRate,
     heap_profiling::kMemlogSamplingRate5MB},
};

const FeatureEntry::FeatureVariation kMemoriesVariations[] = {
    {
        "Limit 1000, On-Device",
        (FeatureEntry::FeatureParam[]){{"MemoriesMaxVisitsToCluster", "1000"}},
        1,
        nullptr,
    },
    {
        "Limit 200, Remote Exp. A",
        (FeatureEntry::FeatureParam[]){
            {"MemoriesExperimentName", "A"},
            {"MemoriesMaxVisitsToCluster", "200"},
            {"MemoriesOnDeviceClusteringBackend", "false"},
        },
        3,
        nullptr,
    },
    {
        "Limit 200, Remote Exp. B",
        (FeatureEntry::FeatureParam[]){
            {"MemoriesExperimentName", "B"},
            {"MemoriesMaxVisitsToCluster", "200"},
            {"MemoriesOnDeviceClusteringBackend", "false"},
        },
        3,
        nullptr,
    },
    {
        "Limit 200, Remote Exp. C",
        (FeatureEntry::FeatureParam[]){
            {"MemoriesExperimentName", "C"},
            {"MemoriesMaxVisitsToCluster", "200"},
            {"MemoriesOnDeviceClusteringBackend", "false"},
        },
        3,
        nullptr,
    },
    {
        "Limit 10k, Remote",
        (FeatureEntry::FeatureParam[]){
            {"MemoriesMaxVisitsToCluster", "10000"},
            {"MemoriesOnDeviceClusteringBackend", "false"},
        },
        2,
        nullptr,
    },
};

#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_MAC) || \
    defined(OS_WIN)
const FeatureEntry::FeatureParam kOmniboxDocumentProviderServerScoring[] = {
    {"DocumentUseServerScore", "true"},
    {"DocumentUseClientScore", "false"},
    {"DocumentCapScorePerRank", "false"},
    {"DocumentBoostOwned", "false"},
};
const FeatureEntry::FeatureParam
    kOmniboxDocumentProviderServerScoringCappedByRank[] = {
        {"DocumentUseServerScore", "true"},
        {"DocumentUseClientScore", "false"},
        {"DocumentCapScorePerRank", "true"},
        {"DocumentBoostOwned", "true"},
};
const FeatureEntry::FeatureParam kOmniboxDocumentProviderClientScoring[] = {
    {"DocumentUseServerScore", "false"},
    {"DocumentUseClientScore", "true"},
    {"DocumentCapScorePerRank", "false"},
    {"DocumentBoostOwned", "false"},
};
const FeatureEntry::FeatureParam
    kOmniboxDocumentProviderServerAndClientScoring[] = {
        {"DocumentUseServerScore", "true"},
        {"DocumentUseClientScore", "true"},
        {"DocumentCapScorePerRank", "false"},
        {"DocumentBoostOwned", "false"},
};

const FeatureEntry::FeatureVariation kOmniboxDocumentProviderVariations[] = {
    {"server scores", kOmniboxDocumentProviderServerScoring,
     base::size(kOmniboxDocumentProviderServerScoring), nullptr},
    {"server scores capped by rank",
     kOmniboxDocumentProviderServerScoringCappedByRank,
     base::size(kOmniboxDocumentProviderServerScoringCappedByRank), nullptr},
    {"client scores", kOmniboxDocumentProviderClientScoring,
     base::size(kOmniboxDocumentProviderClientScoring), nullptr},
    {"server and client scores", kOmniboxDocumentProviderServerAndClientScoring,
     base::size(kOmniboxDocumentProviderServerAndClientScoring), nullptr}};

// 3 permutations of the 2 rich autocompletion params:
// - Title AC: Autocompletes suggestions when the input matches the title.
//   E.g. Space Sh | [ttle - Wikipedia] (en.wikipedia.org/wiki/Space_Shuttle)
// - Non-Prefix AC: Autocompletes suggestions when the input is not necessarily
//   a prefix.
//   E.g. [en.wikipe dia.org/] wiki/Spac | [e_Shuttle] (Space Shuttle -
//   Wikipedia)
const FeatureEntry::FeatureVariation kOmniboxRichAutocompletionVariations[] = {
    {
        "Title AC",
        (FeatureEntry::FeatureParam[]){
            {"RichAutocompletionAutocompleteTitles", "true"}},
        1,
        nullptr,
    },
    {
        "Non-Prefix AC",
        (FeatureEntry::FeatureParam[]){
            {"RichAutocompletionAutocompleteNonPrefixAll", "true"}},
        1,
        nullptr,
    },
    {
        "Title AC & Non-Prefix AC",
        (FeatureEntry::FeatureParam[]){
            {"RichAutocompletionAutocompleteTitles", "true"},
            {"RichAutocompletionAutocompleteNonPrefixAll", "true"}},
        2,
        nullptr,
    }};

const FeatureEntry::FeatureVariation
    kOmniboxRichAutocompletionMinCharVariations[] = {
        {
            "Title 0 / Non Prefix 0",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitlesMinChar", "0"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "0"}},
            2,
            nullptr,
        },
        {
            "Title 0 / Non Prefix 3",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitlesMinChar", "0"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "3"}},
            2,
            nullptr,
        },
        {
            "Title 0 / Non Prefix 5",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitlesMinChar", "0"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "5"}},
            2,
            nullptr,
        },
        {
            "Title 3 / Non Prefix 3",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitlesMinChar", "3"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "3"}},
            2,
            nullptr,
        },
        {
            "Title 3 / Non Prefix 5",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitlesMinChar", "3"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "5"}},
            2,
            nullptr,
        },
        {
            "Title 5 / Non Prefix 5",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitlesMinChar", "5"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "5"}},
            2,
            nullptr,
        }};

const FeatureEntry::FeatureVariation
    kOmniboxRichAutocompletionShowAdditionalTextVariations[] = {
        {
            "Show Additional Text",
            (FeatureEntry::FeatureParam[]){},
            0,
            nullptr,
        },
        {
            "Hide Additional Text",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteShowAdditionalText", "false"}},
            1,
            nullptr,
        }};

<<<<<<< HEAD
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) || \
    BUILDFLAG(IS_WIN)

// A limited number of combinations of the rich autocompletion params.
const FeatureEntry::FeatureParam
    kOmniboxRichAutocompletionConservativeModerate[] = {
        {"RichAutocompletionAutocompleteTitles", "true"},
        {"RichAutocompletionAutocompleteNonPrefixShortcutProvider", "true"},
        {"RichAutocompletionAutocompleteTitlesMinChar", "3"},
        {"RichAutocompletionAutocompleteNonPrefixMinChar", "5"}};
const FeatureEntry::FeatureParam
    kOmniboxRichAutocompletionConservativeModerate2[] = {
        {"RichAutocompletionAutocompleteTitlesShortcutProvider", "true"},
        {"RichAutocompletionAutocompleteNonPrefixShortcutProvider", "true"},
        {"RichAutocompletionAutocompleteTitlesMinChar", "3"},
        {"RichAutocompletionAutocompleteNonPrefixMinChar", "5"}};
const FeatureEntry::FeatureParam kOmniboxRichAutocompletionAggressive2[] = {
    {"RichAutocompletionAutocompleteTitlesShortcutProvider", "true"},
    {"RichAutocompletionAutocompleteTitlesMinChar", "2"},
    {"RichAutocompletionAutocompleteShortcutText", "true"},
    {"RichAutocompletionAutocompleteShortcutTextMinChar", "2"}};
const FeatureEntry::FeatureParam kOmniboxRichAutocompletionAggressive3[] = {
    {"RichAutocompletionAutocompleteTitlesShortcutProvider", "true"},
    {"RichAutocompletionAutocompleteTitlesMinChar", "3"},
    {"RichAutocompletionAutocompleteShortcutText", "true"},
    {"RichAutocompletionAutocompleteShortcutTextMinChar", "3"}};
const FeatureEntry::FeatureParam kOmniboxRichAutocompletionAggressive4[] = {
    {"RichAutocompletionAutocompleteTitlesShortcutProvider", "true"},
    {"RichAutocompletionAutocompleteTitlesMinChar", "4"},
    {"RichAutocompletionAutocompleteShortcutText", "true"},
    {"RichAutocompletionAutocompleteShortcutTextMinChar", "4"}};
=======
const FeatureEntry::FeatureVariation
    kOmniboxRichAutocompletionSplitVariations[] = {
        {
            "Titles & URLs, min char 5",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionSplitTitleCompletion", "true"},
                {"RichAutocompletionSplitUrlCompletion", "true"},
                {"RichAutocompletionSplitCompletionMinChar", "5"}},
            3,
            nullptr,
        },
        {
            "Titles & URLs, min char 3",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionSplitTitleCompletion", "true"},
                {"RichAutocompletionSplitUrlCompletion", "true"},
                {"RichAutocompletionSplitCompletionMinChar", "3"}},
            3,
            nullptr,
        },
        {
            "Titles, min char 5",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionSplitTitleCompletion", "true"},
                {"RichAutocompletionSplitCompletionMinChar", "5"}},
            2,
            nullptr,
        },
        {
            "Titles, min char 3",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionSplitTitleCompletion", "true"},
                {"RichAutocompletionSplitCompletionMinChar", "3"}},
            2,
            nullptr,
        }};

const FeatureEntry::FeatureVariation
    kOmniboxRichAutocompletionPreferUrlsOverPrefixesVariations[] = {
        {
            "Prefer prefixes",
            (FeatureEntry::FeatureParam[]){},
            0,
            nullptr,
        },
        {
            "Prefer URLs",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompletePreferUrlsOverPrefixes",
                 "true"}},
            1,
            nullptr,
        }};
>>>>>>> chromium

// A limited number of combinations of the above variations that are most
// promising.
const FeatureEntry::FeatureVariation
    kOmniboxRichAutocompletionPromisingVariations[] = {
        {
            "Aggressive - Title, Non-Prefix, min 0/0",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitles", "true"},
                {"RichAutocompletionAutocompleteNonPrefixAll", "true"}},
            2,
            nullptr,
        },
        {
            "Aggressive Moderate - Title, Non-Prefix, min 3/5",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitles", "true"},
                {"RichAutocompletionAutocompleteNonPrefixAll", "true"},
                {"RichAutocompletionAutocompleteTitlesMinChar", "3"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "5"}},
            4,
            nullptr,
        },
        {
            "Conservative Moderate - Title, Shortcut Non-Prefix, min 3/5",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitles", "true"},
                {"RichAutocompletionAutocompleteNonPrefixShortcutProvider",
                 "true"},
                {"RichAutocompletionAutocompleteTitlesMinChar", "3"},
                {"RichAutocompletionAutocompleteNonPrefixMinChar", "5"}},
            4,
            nullptr,
        },
        {
            "Conservative - Title, min 3",
            (FeatureEntry::FeatureParam[]){
                {"RichAutocompletionAutocompleteTitles", "true"},
                {"RichAutocompletionAutocompleteTitlesMinChar", "3"}},
            2,
            nullptr,
        },
};

<<<<<<< HEAD
const FeatureEntry::FeatureParam
    kOmniboxDriveSuggestionsIgnoreWhenDebouncing[] = {
        {"DocumentProviderIgnoreWhenDebouncing", "true"}};
const FeatureEntry::FeatureVariation kOmniboxDriveSuggestionsVariations[] = {
    {"ignore when debouncing", kOmniboxDriveSuggestionsIgnoreWhenDebouncing,
     std::size(kOmniboxDriveSuggestionsIgnoreWhenDebouncing), nullptr}};

const FeatureEntry::FeatureParam kOmniboxStarterPackExpansionPreProdUrl[] = {
    {"StarterPackGeminiUrlOverride", "https://gemini.google.com/corp/prompt"}};
const FeatureEntry::FeatureParam kOmniboxStarterPackExpansionStagingUrl[] = {
    {"StarterPackGeminiUrlOverride",
     "https://gemini.google.com/staging/prompt"}};
const FeatureEntry::FeatureVariation kOmniboxStarterPackExpansionVariations[] =
    {{"pre-prod url", kOmniboxStarterPackExpansionPreProdUrl,
      std::size(kOmniboxStarterPackExpansionPreProdUrl), nullptr},
     {"staging url", kOmniboxStarterPackExpansionStagingUrl,
      std::size(kOmniboxStarterPackExpansionStagingUrl), nullptr}};

#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) ||
        // BUILDFLAG(IS_WIN)

const FeatureEntry::FeatureParam kOmniboxMlUrlScoringEnabledWithFixes[] = {
    {"enable_scoring_signals_annotators_for_ml_scoring", "true"},
    {"MlUrlScoringShortcutDocumentSignals", "true"},
};
const FeatureEntry::FeatureParam kOmniboxMlUrlScoringUnlimitedNumCandidates[] =
=======
const FeatureEntry::FeatureVariation kOmniboxBookmarkPathsVariations[] = {
>>>>>>> chromium
    {
        "Default UI (Title - URL)",
        (FeatureEntry::FeatureParam[]){},
        0,
        nullptr,
    },
    {
        "Replace title (Path/Title - URL)",
        (FeatureEntry::FeatureParam[]){
            {"OmniboxBookmarkPathsUiReplaceTitle", "true"}},
        1,
        nullptr,
    },
    {
        "Replace URL (Title - Path)",
        (FeatureEntry::FeatureParam[]){
            {"OmniboxBookmarkPathsUiReplaceUrl", "true"}},
        1,
        nullptr,
    },
    {
        "Append after title (Title : Path - URL)",
        (FeatureEntry::FeatureParam[]){
            {"OmniboxBookmarkPathsUiAppendAfterTitle", "true"}},
        1,
        nullptr,
    },
    {
        "Dynamic Replace URL (Title - Path|URL)",
        (FeatureEntry::FeatureParam[]){
            {"OmniboxBookmarkPathsUiDynamicReplaceUrl", "true"}},
        1,
        nullptr,
    },
};
#endif  // defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_MAC) ||
        // defined(OS_WIN)

const FeatureEntry::FeatureVariation
    kOmniboxOnFocusSuggestionsContextualWebVariations[] = {
        {"GOC Only", {}, 0, "t3317583"},
        {"pSuggest Only", {}, 0, "t3318055"},
        {"GOC, pSuggest Fallback", {}, 0, "t3317692"},
        {"GOC, pSuggest Backfill", {}, 0, "t3317694"},
        {"GOC, Default Hidden", {}, 0, "t3317834"},
};

<<<<<<< HEAD
const FeatureEntry::FeatureParam kMlUrlSearchBlendingStable[] = {
    {"MlUrlSearchBlending_StableSearchBlending", "true"},
    {"MlUrlSearchBlending_MappedSearchBlending", "false"},
};
const FeatureEntry::FeatureParam kMlUrlSearchBlendingMappedConservativeUrls[] =
    {
        {"MlUrlSearchBlending_StableSearchBlending", "false"},
        {"MlUrlSearchBlending_MappedSearchBlending", "true"},
        {"MlUrlSearchBlending_MappedSearchBlendingMin", "0"},
        {"MlUrlSearchBlending_MappedSearchBlendingMax", "2000"},
        {"MlUrlSearchBlending_MappedSearchBlendingGroupingThreshold", "1000"},
};
const FeatureEntry::FeatureParam kMlUrlSearchBlendingMappedModerateUrls[] = {
    {"MlUrlSearchBlending_StableSearchBlending", "false"},
    {"MlUrlSearchBlending_MappedSearchBlending", "true"},
};
const FeatureEntry::FeatureParam kMlUrlSearchBlendingMappedAggressiveUrls[] = {
    {"MlUrlSearchBlending_StableSearchBlending", "false"},
    {"MlUrlSearchBlending_MappedSearchBlending", "true"},
    {"MlUrlSearchBlending_MappedSearchBlendingMin", "1000"},
    {"MlUrlSearchBlending_MappedSearchBlendingMax", "4000"},
    {"MlUrlSearchBlending_MappedSearchBlendingGroupingThreshold", "1500"},
};

const FeatureEntry::FeatureVariation kMlUrlSearchBlendingVariations[] = {
    {"Stable", kMlUrlSearchBlendingStable,
     std::size(kMlUrlSearchBlendingStable), nullptr},
    {"Mapped conservative urls", kMlUrlSearchBlendingMappedConservativeUrls,
     std::size(kMlUrlSearchBlendingMappedConservativeUrls), nullptr},
    {"Mapped moderate urls", kMlUrlSearchBlendingMappedModerateUrls,
     std::size(kMlUrlSearchBlendingMappedModerateUrls), nullptr},
    {"Mapped aggressive urls", kMlUrlSearchBlendingMappedAggressiveUrls,
     std::size(kMlUrlSearchBlendingMappedAggressiveUrls), nullptr},
};

const FeatureEntry::FeatureParam
    kMostVitedTilesNewScoring_DecayStaircaseCap10[] = {
        {history::kMvtScoringParamRecencyFactor,
         history::kMvtScoringParamRecencyFactor_DecayStaircase},
        {history::kMvtScoringParamDailyVisitCountCap, "10"},
};
const FeatureEntry::FeatureParam kMostVitedTilesNewScoring_DecayCap1[] = {
    {history::kMvtScoringParamRecencyFactor,
     history::kMvtScoringParamRecencyFactor_Decay},
    // exp(-1.0 / 11).
    {history::kMvtScoringParamDecayPerDay, "0.9131007162822623"},
    {history::kMvtScoringParamDailyVisitCountCap, "1"},
};
const FeatureEntry::FeatureVariation kMostVisitedTilesNewScoringVariations[] = {
    {"Decay Staircase, Cap 10", kMostVitedTilesNewScoring_DecayStaircaseCap10,
     std::size(kMostVitedTilesNewScoring_DecayStaircaseCap10), nullptr},
    {"Decay, Cap 1", kMostVitedTilesNewScoring_DecayCap1,
     std::size(kMostVitedTilesNewScoring_DecayCap1), nullptr},
};

const FeatureEntry::FeatureVariation kUrlScoringModelVariations[] = {
    {"Small model (desktop)", nullptr, 0, nullptr},
    {"Full model (desktop)", nullptr, 0, "3380045"},
    {"Small model (ios)", nullptr, 0, "3379590"},
    {"Full model (ios)", nullptr, 0, "3380197"},
    {"Small model (android)", nullptr, 0, "3381543"},
    {"Full model (android)", nullptr, 0, "3381544"},
};

const FeatureEntry::FeatureParam
    kOmniboxZeroSuggestPrefetchDebouncingMinimalFromLastRun[] = {
        {"ZeroSuggestPrefetchDebounceDelay", "300"},
        {"ZeroSuggestPrefetchDebounceFromLastRun", "true"},
};
const FeatureEntry::FeatureParam
    kOmniboxZeroSuggestPrefetchDebouncingMinimalFromLastRequest[] = {
        {"ZeroSuggestPrefetchDebounceDelay", "300"},
        {"ZeroSuggestPrefetchDebounceFromLastRun", "false"},
};
const FeatureEntry::FeatureParam
    kOmniboxZeroSuggestPrefetchDebouncingModerateFromLastRun[] = {
        {"ZeroSuggestPrefetchDebounceDelay", "600"},
        {"ZeroSuggestPrefetchDebounceFromLastRun", "true"},
};
const FeatureEntry::FeatureParam
    kOmniboxZeroSuggestPrefetchDebouncingModerateFromLastRequest[] = {
        {"ZeroSuggestPrefetchDebounceDelay", "600"},
        {"ZeroSuggestPrefetchDebounceFromLastRun", "false"},
};
const FeatureEntry::FeatureParam
    kOmniboxZeroSuggestPrefetchDebouncingAggressiveFromLastRun[] = {
        {"ZeroSuggestPrefetchDebounceDelay", "900"},
        {"ZeroSuggestPrefetchDebounceFromLastRun", "true"},
};
const FeatureEntry::FeatureParam
    kOmniboxZeroSuggestPrefetchDebouncingAggressiveFromLastRequest[] = {
        {"ZeroSuggestPrefetchDebounceDelay", "900"},
        {"ZeroSuggestPrefetchDebounceFromLastRun", "false"},
};

const FeatureEntry::FeatureVariation
    kOmniboxZeroSuggestPrefetchDebouncingVariations[] = {
        {"Minimal debouncing relative to last run",
         kOmniboxZeroSuggestPrefetchDebouncingMinimalFromLastRun,
         std::size(kOmniboxZeroSuggestPrefetchDebouncingMinimalFromLastRun),
         nullptr},
        {"Minimal debouncing relative to last request",
         kOmniboxZeroSuggestPrefetchDebouncingMinimalFromLastRequest,
         std::size(kOmniboxZeroSuggestPrefetchDebouncingMinimalFromLastRequest),
         nullptr},
        {"Moderate debouncing relative to last run",
         kOmniboxZeroSuggestPrefetchDebouncingModerateFromLastRun,
         std::size(kOmniboxZeroSuggestPrefetchDebouncingModerateFromLastRun),
         nullptr},
        {"Moderate debouncing relative to last request",
         kOmniboxZeroSuggestPrefetchDebouncingModerateFromLastRequest,
         std::size(
             kOmniboxZeroSuggestPrefetchDebouncingModerateFromLastRequest),
         nullptr},
        {"Aggressive debouncing relative to last run",
         kOmniboxZeroSuggestPrefetchDebouncingAggressiveFromLastRun,
         std::size(kOmniboxZeroSuggestPrefetchDebouncingAggressiveFromLastRun),
         nullptr},
        {"Aggressive debouncing relative to last request",
         kOmniboxZeroSuggestPrefetchDebouncingAggressiveFromLastRequest,
         std::size(
             kOmniboxZeroSuggestPrefetchDebouncingAggressiveFromLastRequest),
         nullptr},
};

#if BUILDFLAG(IS_ANDROID)
constexpr FeatureEntry::FeatureParam kOmniboxAnswerActionsCounterfactual[] = {
    {OmniboxFieldTrial::kAnswerActionsCounterfactual.name, "true"}};
constexpr FeatureEntry::FeatureParam kOmniboxAnswerActionsTreatment1[] = {
    {OmniboxFieldTrial::kAnswerActionsShowAboveKeyboard.name, "true"},
    {OmniboxFieldTrial::kAnswerActionsShowIfUrlsPresent.name, "false"},
    {OmniboxFieldTrial::kAnswerActionsShowRichCard.name, "false"}};

constexpr FeatureEntry::FeatureParam kOmniboxAnswerActionsTreatment2[] = {
    {OmniboxFieldTrial::kAnswerActionsShowAboveKeyboard.name, "false"},
    {OmniboxFieldTrial::kAnswerActionsShowIfUrlsPresent.name, "true"},
    {OmniboxFieldTrial::kAnswerActionsShowRichCard.name, "false"}};

constexpr FeatureEntry::FeatureParam kOmniboxAnswerActionsTreatment3[] = {
    {OmniboxFieldTrial::kAnswerActionsShowAboveKeyboard.name, "false"},
    {OmniboxFieldTrial::kAnswerActionsShowIfUrlsPresent.name, "false"},
    {OmniboxFieldTrial::kAnswerActionsShowRichCard.name, "false"}};

constexpr FeatureEntry::FeatureParam kOmniboxAnswerActionsTreatment4[] = {
    {OmniboxFieldTrial::kAnswerActionsShowAboveKeyboard.name, "true"},
    {OmniboxFieldTrial::kAnswerActionsShowIfUrlsPresent.name, "false"},
    {OmniboxFieldTrial::kAnswerActionsShowRichCard.name, "true"}};

constexpr FeatureEntry::FeatureParam kOmniboxAnswerActionsTreatment5[] = {
    {OmniboxFieldTrial::kAnswerActionsShowAboveKeyboard.name, "false"},
    {OmniboxFieldTrial::kAnswerActionsShowIfUrlsPresent.name, "false"},
    {OmniboxFieldTrial::kAnswerActionsShowRichCard.name, "true"}};

constexpr FeatureEntry::FeatureVariation kOmniboxAnswerActionsVariants[] = {
    {"Counterfactual: fetch without rendering ",
     kOmniboxAnswerActionsCounterfactual,
     std::size(kOmniboxAnswerActionsCounterfactual), "t3379046"},
    {"T1: Show chips above keyboard when there are no url matches",
     kOmniboxAnswerActionsTreatment1,
     std::size(kOmniboxAnswerActionsTreatment1), "t3379047"},
    {"T2: Show chips at position 0", kOmniboxAnswerActionsTreatment2,
     std::size(kOmniboxAnswerActionsTreatment2), "t3379048"},
    {"T3: Show chips at position 0 when there are no url matches",
     kOmniboxAnswerActionsTreatment3,
     std::size(kOmniboxAnswerActionsTreatment3), "t3379049"},
    {"T4: Show rich card above keyboard when there are no url matches",
     kOmniboxAnswerActionsTreatment4,
     std::size(kOmniboxAnswerActionsTreatment4), "t3379050"},
    {"T5: Show rich card at position 0 when there are no url matches",
     kOmniboxAnswerActionsTreatment5,
     std::size(kOmniboxAnswerActionsTreatment5), "t3379051"},
};

#endif  // BUILDFLAG(IS_ANDROID)

const FeatureEntry::FeatureParam kMaxZeroSuggestMatches5[] = {
    {"MaxZeroSuggestMatches", "5"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches6[] = {
    {"MaxZeroSuggestMatches", "6"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches7[] = {
    {"MaxZeroSuggestMatches", "7"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches8[] = {
    {"MaxZeroSuggestMatches", "8"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches9[] = {
    {"MaxZeroSuggestMatches", "9"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches10[] = {
    {"MaxZeroSuggestMatches", "10"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches11[] = {
    {"MaxZeroSuggestMatches", "11"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches12[] = {
    {"MaxZeroSuggestMatches", "12"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches13[] = {
    {"MaxZeroSuggestMatches", "13"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches14[] = {
    {"MaxZeroSuggestMatches", "14"}};
const FeatureEntry::FeatureParam kMaxZeroSuggestMatches15[] = {
    {"MaxZeroSuggestMatches", "15"}};

=======
>>>>>>> chromium
const FeatureEntry::FeatureVariation kMaxZeroSuggestMatchesVariations[] = {
    {
        "5",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "5"}},
        1,
        nullptr,
    },
    {
        "6",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "6"}},
        1,
        nullptr,
    },
    {
        "7",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "7"}},
        1,
        nullptr,
    },
    {
        "8",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "8"}},
        1,
        nullptr,
    },
    {
        "9",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "9"}},
        1,
        nullptr,
    },
    {
        "10",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "10"}},
        1,
        nullptr,
    },
    {
        "11",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "11"}},
        1,
        nullptr,
    },
    {
        "12",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "12"}},
        1,
        nullptr,
    },
    {
        "13",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "13"}},
        1,
        nullptr,
    },
    {
        "14",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "14"}},
        1,
        nullptr,
    },
    {
        "15",
        (FeatureEntry::FeatureParam[]){{"MaxZeroSuggestMatches", "15"}},
        1,
        nullptr,
    },
};

const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches3[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "3"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches4[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "4"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches5[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "5"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches6[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "6"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches7[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "7"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches8[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "8"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches9[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "9"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches10[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "10"}};
const FeatureEntry::FeatureParam kOmniboxUIMaxAutocompleteMatches12[] = {
    {OmniboxFieldTrial::kUIMaxAutocompleteMatchesParam, "12"}};

const FeatureEntry::FeatureVariation
    kOmniboxUIMaxAutocompleteMatchesVariations[] = {
        {"3 matches", kOmniboxUIMaxAutocompleteMatches3,
         base::size(kOmniboxUIMaxAutocompleteMatches3), nullptr},
        {"4 matches", kOmniboxUIMaxAutocompleteMatches4,
         base::size(kOmniboxUIMaxAutocompleteMatches4), nullptr},
        {"5 matches", kOmniboxUIMaxAutocompleteMatches5,
         base::size(kOmniboxUIMaxAutocompleteMatches5), nullptr},
        {"6 matches", kOmniboxUIMaxAutocompleteMatches6,
         base::size(kOmniboxUIMaxAutocompleteMatches6), nullptr},
        {"7 matches", kOmniboxUIMaxAutocompleteMatches7,
         base::size(kOmniboxUIMaxAutocompleteMatches7), nullptr},
        {"8 matches", kOmniboxUIMaxAutocompleteMatches8,
         base::size(kOmniboxUIMaxAutocompleteMatches8), nullptr},
        {"9 matches", kOmniboxUIMaxAutocompleteMatches9,
         base::size(kOmniboxUIMaxAutocompleteMatches9), nullptr},
        {"10 matches", kOmniboxUIMaxAutocompleteMatches10,
         base::size(kOmniboxUIMaxAutocompleteMatches10), nullptr},
        {"12 matches", kOmniboxUIMaxAutocompleteMatches12,
         base::size(kOmniboxUIMaxAutocompleteMatches12), nullptr}};

const FeatureEntry::FeatureParam
    kOmniboxDefaultTypedNavigationsToHttpsVariationsTimeout3s[] = {
        {omnibox::kDefaultTypedNavigationsToHttpsTimeoutParam, "3s"}};
const FeatureEntry::FeatureParam
    kOmniboxDefaultTypedNavigationsToHttpsVariationsTimeout10s[] = {
        {omnibox::kDefaultTypedNavigationsToHttpsTimeoutParam, "10s"}};
const FeatureEntry::FeatureVariation
    kOmniboxDefaultTypedNavigationsToHttpsVariations[] = {
        {"3 second timeout",
         kOmniboxDefaultTypedNavigationsToHttpsVariationsTimeout3s,
         base::size(kOmniboxDefaultTypedNavigationsToHttpsVariationsTimeout3s),
         nullptr},
        {"10 second timeout",
         kOmniboxDefaultTypedNavigationsToHttpsVariationsTimeout10s,
         base::size(kOmniboxDefaultTypedNavigationsToHttpsVariationsTimeout10s),
         nullptr},
};

const FeatureEntry::FeatureParam kOmniboxMaxURLMatches2[] = {
    {OmniboxFieldTrial::kOmniboxMaxURLMatchesParam, "2"}};
const FeatureEntry::FeatureParam kOmniboxMaxURLMatches3[] = {
    {OmniboxFieldTrial::kOmniboxMaxURLMatchesParam, "3"}};
const FeatureEntry::FeatureParam kOmniboxMaxURLMatches4[] = {
    {OmniboxFieldTrial::kOmniboxMaxURLMatchesParam, "4"}};
const FeatureEntry::FeatureParam kOmniboxMaxURLMatches5[] = {
    {OmniboxFieldTrial::kOmniboxMaxURLMatchesParam, "5"}};
const FeatureEntry::FeatureParam kOmniboxMaxURLMatches6[] = {
    {OmniboxFieldTrial::kOmniboxMaxURLMatchesParam, "6"}};

const FeatureEntry::FeatureVariation kOmniboxMaxURLMatchesVariations[] = {
    {"2 matches", kOmniboxMaxURLMatches2, base::size(kOmniboxMaxURLMatches2),
     nullptr},
    {"3 matches", kOmniboxMaxURLMatches3, base::size(kOmniboxMaxURLMatches3),
     nullptr},
    {"4 matches", kOmniboxMaxURLMatches4, base::size(kOmniboxMaxURLMatches4),
     nullptr},
    {"5 matches", kOmniboxMaxURLMatches5, base::size(kOmniboxMaxURLMatches5),
     nullptr},
    {"6 matches", kOmniboxMaxURLMatches6, base::size(kOmniboxMaxURLMatches6),
     nullptr}};

const FeatureEntry::FeatureVariation
    kOmniboxDynamicMaxAutocompleteVariations[] = {
        {
            "9 suggestions if 0 or less URLs",
            (FeatureEntry::FeatureParam[]){
                {"OmniboxDynamicMaxAutocompleteUrlCutoff", "0"},
                {"OmniboxDynamicMaxAutocompleteIncreasedLimit", "9"}},
            2,
            nullptr,
        },
        {
            "9 suggestions if 1 or less URLs",
            (FeatureEntry::FeatureParam[]){
                {"OmniboxDynamicMaxAutocompleteUrlCutoff", "1"},
                {"OmniboxDynamicMaxAutocompleteIncreasedLimit", "9"}},
            2,
            nullptr,
        },
        {
            "9 suggestions if 2 or less URLs",
            (FeatureEntry::FeatureParam[]){
                {"OmniboxDynamicMaxAutocompleteUrlCutoff", "2"},
                {"OmniboxDynamicMaxAutocompleteIncreasedLimit", "9"}},
            2,
            nullptr,
        },
        {
            "10 suggestions if 0 or less URLs",
            (FeatureEntry::FeatureParam[]){
                {"OmniboxDynamicMaxAutocompleteUrlCutoff", "0"},
                {"OmniboxDynamicMaxAutocompleteIncreasedLimit", "10"}},
            2,
            nullptr,
        },
        {
            "10 suggestions if 1 or less URLs",
            (FeatureEntry::FeatureParam[]){
                {"OmniboxDynamicMaxAutocompleteUrlCutoff", "1"},
                {"OmniboxDynamicMaxAutocompleteIncreasedLimit", "10"}},
            2,
            nullptr,
        },
        {
            "10 suggestions if 2 or less URLs",
            (FeatureEntry::FeatureParam[]){
                {"OmniboxDynamicMaxAutocompleteUrlCutoff", "2"},
                {"OmniboxDynamicMaxAutocompleteIncreasedLimit", "10"}},
            2,
            nullptr,
        }};

const FeatureEntry::FeatureParam kMinimumTabWidthSettingPinned[] = {
    {features::kMinimumTabWidthFeatureParameterName, "54"}};
const FeatureEntry::FeatureParam kMinimumTabWidthSettingMedium[] = {
    {features::kMinimumTabWidthFeatureParameterName, "72"}};
const FeatureEntry::FeatureParam kMinimumTabWidthSettingLarge[] = {
    {features::kMinimumTabWidthFeatureParameterName, "140"}};
const FeatureEntry::FeatureParam kMinimumTabWidthSettingFull[] = {
    {features::kMinimumTabWidthFeatureParameterName, "256"}};

const FeatureEntry::FeatureVariation kTabScrollingVariations[] = {
    {" - tabs shrink to pinned tab width", kMinimumTabWidthSettingPinned,
     base::size(kMinimumTabWidthSettingPinned), nullptr},
    {" - tabs shrink to a medium width", kMinimumTabWidthSettingMedium,
     base::size(kMinimumTabWidthSettingMedium), nullptr},
    {" - tabs shrink to a large width", kMinimumTabWidthSettingLarge,
     base::size(kMinimumTabWidthSettingLarge), nullptr},
    {" - tabs don't shrink", kMinimumTabWidthSettingFull,
     base::size(kMinimumTabWidthSettingFull), nullptr}};

const FeatureEntry::FeatureParam kTabHoverCardImagesOptimizationCaptureSpeed[] =
    {{features::kTabHoverCardImagesNotReadyDelayParameterName, "0"},
     {features::kTabHoverCardImagesLoadingDelayParameterName, "0"},
     {features::kTabHoverCardImagesLoadedDelayParameterName, "0"}};
const FeatureEntry::FeatureParam
    kTabHoverCardImagesOptimizationResourceUsage[] = {
        {features::kTabHoverCardImagesNotReadyDelayParameterName, "800"},
        {features::kTabHoverCardImagesLoadingDelayParameterName, "300"},
        {features::kTabHoverCardImagesLoadedDelayParameterName, "300"}};
const FeatureEntry::FeatureParam
    kTabHoverCardImagesImmediatePlaceholderCrossfade[] = {
        {features::kTabHoverCardImagesNotReadyDelayParameterName, "500"},
        {features::kTabHoverCardImagesLoadingDelayParameterName, "100"},
        {features::kTabHoverCardImagesLoadedDelayParameterName, "0"},
        {features::kTabHoverCardImagesCrossfadePreviewAtParameterName, "0.0"}};
const FeatureEntry::FeatureParam
    kTabHoverCardImagesEarlySlidePlaceholderCrossfade[] = {
        {features::kTabHoverCardImagesNotReadyDelayParameterName, "500"},
        {features::kTabHoverCardImagesLoadingDelayParameterName, "100"},
        {features::kTabHoverCardImagesLoadedDelayParameterName, "0"},
        {features::kTabHoverCardImagesCrossfadePreviewAtParameterName, "0.25"}};
const FeatureEntry::FeatureParam
    kTabHoverCardImagesMidSlidePlaceholderCrossfade[] = {
        {features::kTabHoverCardImagesNotReadyDelayParameterName, "500"},
        {features::kTabHoverCardImagesLoadingDelayParameterName, "100"},
        {features::kTabHoverCardImagesLoadedDelayParameterName, "0"},
        {features::kTabHoverCardImagesCrossfadePreviewAtParameterName, "0.5"}};
const FeatureEntry::FeatureParam kTabHoverCardImagesLatePlaceholderCrossfade[] =
    {{features::kTabHoverCardImagesNotReadyDelayParameterName, "500"},
     {features::kTabHoverCardImagesLoadingDelayParameterName, "100"},
     {features::kTabHoverCardImagesLoadedDelayParameterName, "0"},
     {features::kTabHoverCardImagesCrossfadePreviewAtParameterName, "1.0"}};

const FeatureEntry::FeatureVariation kTabHoverCardImagesVariations[] = {
    {" capture speed", kTabHoverCardImagesOptimizationCaptureSpeed,
     base::size(kTabHoverCardImagesOptimizationCaptureSpeed), nullptr},
    {" resource usage", kTabHoverCardImagesOptimizationResourceUsage,
     base::size(kTabHoverCardImagesOptimizationResourceUsage), nullptr},
    {" immediate placeholder crossfade",
     kTabHoverCardImagesImmediatePlaceholderCrossfade,
     base::size(kTabHoverCardImagesImmediatePlaceholderCrossfade), nullptr},
    {" early-transition placeholder crossfade",
     kTabHoverCardImagesEarlySlidePlaceholderCrossfade,
     base::size(kTabHoverCardImagesEarlySlidePlaceholderCrossfade), nullptr},
    {" mid-transition placeholder crossfade",
     kTabHoverCardImagesMidSlidePlaceholderCrossfade,
     base::size(kTabHoverCardImagesMidSlidePlaceholderCrossfade), nullptr},
    {" placeholder crossfade on land",
     kTabHoverCardImagesLatePlaceholderCrossfade,
     base::size(kTabHoverCardImagesImmediatePlaceholderCrossfade), nullptr}};

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)

const FeatureEntry::FeatureParam kTabstripComboButtonNoBackground[] = {
    {"has_background", "false"}};

const FeatureEntry::FeatureParam kTabstripComboButtonReverseButtonOrder[] = {
    {"reverse_button_order", "true"}};

const FeatureEntry::FeatureParam
    kTabstripComboButtonReverseButtonOrderNoBackground[] = {
        {"has_background", "false"},
        {"reverse_button_order", "true"}};

const FeatureEntry::FeatureVariation kTabstripComboButtonVariations[] = {
    {" - without background", kTabstripComboButtonNoBackground,
     std::size(kTabstripComboButtonNoBackground)},
    {" - reverse button order", kTabstripComboButtonReverseButtonOrder,
     std::size(kTabstripComboButtonReverseButtonOrder)},
    {" - reverse button order & without background",
     kTabstripComboButtonReverseButtonOrderNoBackground,
     std::size(kTabstripComboButtonReverseButtonOrderNoBackground)},
};

#endif

const FeatureEntry::FeatureParam kTabScrollingButtonPositionRight[] = {
    {features::kTabScrollingButtonPositionParameterName, "0"}};
const FeatureEntry::FeatureParam kTabScrollingButtonPositionLeft[] = {
    {features::kTabScrollingButtonPositionParameterName, "1"}};
const FeatureEntry::FeatureParam kTabScrollingButtonPositionSplit[] = {
    {features::kTabScrollingButtonPositionParameterName, "2"}};

const FeatureEntry::FeatureVariation kTabScrollingButtonPositionVariations[] = {
    {" - to the right of the tabstrip", kTabScrollingButtonPositionRight,
     std::size(kTabScrollingButtonPositionRight), nullptr},
    {" - to the left of the tabstrip", kTabScrollingButtonPositionLeft,
     std::size(kTabScrollingButtonPositionLeft), nullptr},
    {" - on both sides of the tabstrip", kTabScrollingButtonPositionSplit,
     std::size(kTabScrollingButtonPositionSplit), nullptr}};

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kTabScrollingWithDraggingWithConstantSpeed[] =
    {{tabs::kTabScrollingWithDraggingModeName, "1"}};
const FeatureEntry::FeatureParam kTabScrollingWithDraggingWithVariableSpeed[] =
    {{tabs::kTabScrollingWithDraggingModeName, "2"}};

const FeatureEntry::FeatureVariation kTabScrollingWithDraggingVariations[] = {
    {" - tabs scrolling with constant speed",
     kTabScrollingWithDraggingWithConstantSpeed,
     std::size(kTabScrollingWithDraggingWithConstantSpeed), nullptr},
    {" - tabs scrolling with variable speed region",
     kTabScrollingWithDraggingWithVariableSpeed,
     std::size(kTabScrollingWithDraggingWithVariableSpeed), nullptr}};

const FeatureEntry::FeatureParam kScrollableTabStripOverflowDivider[] = {
    {tabs::kScrollableTabStripOverflowModeName, "1"}};
const FeatureEntry::FeatureParam kScrollableTabStripOverflowFade[] = {
    {tabs::kScrollableTabStripOverflowModeName, "2"}};
const FeatureEntry::FeatureParam kScrollableTabStripOverflowShadow[] = {
    {tabs::kScrollableTabStripOverflowModeName, "3"}};

const FeatureEntry::FeatureVariation kScrollableTabStripOverflowVariations[] = {
    {" - Divider", kScrollableTabStripOverflowDivider,
     std::size(kScrollableTabStripOverflowDivider), nullptr},  // Divider
    {" - Fade", kScrollableTabStripOverflowFade,
     std::size(kScrollableTabStripOverflowFade), nullptr},  // Fade
    {" - Shadow", kScrollableTabStripOverflowShadow,
     std::size(kScrollableTabStripOverflowShadow), nullptr},  // Shadow
};
#endif

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kNtpCalendarModuleFakeData[] = {
    {ntp_features::kNtpCalendarModuleDataParam, "fake"}};
const FeatureEntry::FeatureVariation kNtpCalendarModuleVariations[] = {
    {"- Fake Data", kNtpCalendarModuleFakeData,
     std::size(kNtpCalendarModuleFakeData), nullptr},
};
=======
const FeatureEntry::FeatureParam kPromoBrowserCommandUnknownCommandParam[] = {
    {features::kPromoBrowserCommandIdParam, "0"}};
const FeatureEntry::FeatureParam
    kPromoBrowserCommandOpenSafetyCheckCommandParam[] = {
        {features::kPromoBrowserCommandIdParam, "1"}};
const FeatureEntry::FeatureParam
    kPromoBrowserCommandOpenSafeBrowsingSettingsEnhancedProtectionCommandParam
        [] = {{features::kPromoBrowserCommandIdParam, "2"}};
const FeatureEntry::FeatureVariation kPromoBrowserCommandsVariations[] = {
    {"- Unknown Command", kPromoBrowserCommandUnknownCommandParam,
     base::size(kPromoBrowserCommandUnknownCommandParam), nullptr},
    {"- Open Safety Check", kPromoBrowserCommandOpenSafetyCheckCommandParam,
     base::size(kPromoBrowserCommandOpenSafetyCheckCommandParam), nullptr},
    {"- Open Safe Browsing Enhanced Protection Settings",
     kPromoBrowserCommandOpenSafeBrowsingSettingsEnhancedProtectionCommandParam,
     base::size(
         kPromoBrowserCommandOpenSafeBrowsingSettingsEnhancedProtectionCommandParam),
     nullptr}};
#if !defined(OS_ANDROID)
>>>>>>> chromium

const FeatureEntry::FeatureParam kNtpChromeCartModuleFakeData[] = {
    {ntp_features::kNtpChromeCartModuleDataParam, "fake"},
    {ntp_features::kNtpChromeCartModuleAbandonedCartDiscountParam, "true"}};
const FeatureEntry::FeatureParam kNtpChromeCartModuleAbandonedCartDiscount[] = {
    {ntp_features::kNtpChromeCartModuleAbandonedCartDiscountParam, "true"},
    {"partner-merchant-pattern",
     "(electronicexpress.com|zazzle.com|wish.com|homesquare.com)"}};
const FeatureEntry::FeatureParam kNtpChromeCartModuleHeuristicsImprovement[] = {
    {ntp_features::kNtpChromeCartModuleHeuristicsImprovementParam, "true"}};
const FeatureEntry::FeatureVariation kNtpChromeCartModuleVariations[] = {
    {"- Fake Data And Discount", kNtpChromeCartModuleFakeData,
     base::size(kNtpChromeCartModuleFakeData), nullptr},
    {"- Abandoned Cart Discount", kNtpChromeCartModuleAbandonedCartDiscount,
     base::size(kNtpChromeCartModuleAbandonedCartDiscount), nullptr},
    {"- Heuristics Improvement", kNtpChromeCartModuleHeuristicsImprovement,
     base::size(kNtpChromeCartModuleHeuristicsImprovement), nullptr},
};

<<<<<<< HEAD
=======
const FeatureEntry::FeatureParam kNtpRecipeTasksModuleFakeData[] = {
    {ntp_features::kNtpRecipeTasksModuleDataParam, "fake"}};
const FeatureEntry::FeatureVariation kNtpRecipeTasksModuleVariations[] = {
    {"- Fake Data", kNtpRecipeTasksModuleFakeData,
     base::size(kNtpRecipeTasksModuleFakeData), nullptr},
};

const FeatureEntry::FeatureParam kNtpShoppingTasksModuleFakeData[] = {
    {ntp_features::kNtpShoppingTasksModuleDataParam, "fake"}};
const FeatureEntry::FeatureVariation kNtpShoppingTasksModuleVariations[] = {
    {"- Fake Data", kNtpShoppingTasksModuleFakeData,
     base::size(kNtpShoppingTasksModuleFakeData),
     "t3329139" /* variation_id */},
};

>>>>>>> chromium
const FeatureEntry::FeatureParam kNtpDriveModuleFakeData[] = {
    {ntp_features::kNtpDriveModuleDataParam, "fake"}};
const FeatureEntry::FeatureParam kNtpDriveModuleManagedUsersOnly[] = {
    {ntp_features::kNtpDriveModuleManagedUsersOnlyParam, "true"}};
const FeatureEntry::FeatureVariation kNtpDriveModuleVariations[] = {
    {"- Fake Data", kNtpDriveModuleFakeData,
     base::size(kNtpDriveModuleFakeData), nullptr},
    {"- Managed Users Only", kNtpDriveModuleManagedUsersOnly,
     base::size(kNtpDriveModuleManagedUsersOnly), nullptr},
};
#endif  // !defined(OS_ANDROID)

#if !defined(OS_ANDROID)
const FeatureEntry::FeatureParam kEnterpriseRealtimeExtensionRequestParam[] = {
    {"with_erp", "true"}};
const FeatureEntry::FeatureVariation
    kEnterpriseRealtimeExtensionRequestVariation[] = {
        {"with encrypted reporting pipeline",
         kEnterpriseRealtimeExtensionRequestParam,
         base::size(kEnterpriseRealtimeExtensionRequestParam), nullptr}};
#endif  // !defined(OS_ANDROID)

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kTranslateForceTriggerOnEnglishHeuristic[] = {
    {language::kOverrideModelKey, language::kOverrideModelHeuristicValue},
    {language::kEnforceRankerKey, "false"}};
const FeatureEntry::FeatureParam kTranslateForceTriggerOnEnglishGeo[] = {
    {language::kOverrideModelKey, language::kOverrideModelGeoValue},
    {language::kEnforceRankerKey, "false"}};
const FeatureEntry::FeatureParam kTranslateForceTriggerOnEnglishBackoff[] = {
    {language::kOverrideModelKey, language::kOverrideModelDefaultValue},
    {language::kEnforceRankerKey, "false"},
    {language::kBackoffThresholdKey, "0"}};
const FeatureEntry::FeatureVariation
    kTranslateForceTriggerOnEnglishVariations[] = {
        {"(Heuristic model without Ranker)",
         kTranslateForceTriggerOnEnglishHeuristic,
         base::size(kTranslateForceTriggerOnEnglishHeuristic), nullptr},
        {"(Geo model without Ranker)", kTranslateForceTriggerOnEnglishGeo,
         base::size(kTranslateForceTriggerOnEnglishGeo), nullptr},
        {"(Zero threshold)", kTranslateForceTriggerOnEnglishBackoff,
         base::size(kTranslateForceTriggerOnEnglishBackoff), nullptr}};
#endif  // defined(OS_ANDROID)

const FeatureEntry::FeatureParam kOverridePrefsForHrefTranslateForceAuto[] = {
    {translate::kForceAutoTranslateKey, "true"}};

const FeatureEntry::FeatureVariation
    kOverrideLanguagePrefsForHrefTranslateVariations[] = {
        {"(Force automatic translation of blocked languages for hrefTranslate)",
         kOverridePrefsForHrefTranslateForceAuto,
         base::size(kOverridePrefsForHrefTranslateForceAuto), nullptr}};

const FeatureEntry::FeatureVariation
    kOverrideSitePrefsForHrefTranslateVariations[] = {
        {"(Force automatic translation of blocked sites for hrefTranslate)",
         kOverridePrefsForHrefTranslateForceAuto,
         base::size(kOverridePrefsForHrefTranslateForceAuto), nullptr}};

const FeatureEntry::FeatureParam
    kOverrideUnsupportedPageLanguageForHrefTranslateForceAuto[] = {
        {"force-auto-translate-for-unsupported-page-language", "true"}};

const FeatureEntry::FeatureVariation
    kOverrideUnsupportedPageLanguageForHrefTranslateVariations[] = {
        {"(Force automatic translation of pages with unknown language for "
         "hrefTranslate)",
         kOverrideUnsupportedPageLanguageForHrefTranslateForceAuto,
         base::size(kOverrideUnsupportedPageLanguageForHrefTranslateForceAuto),
         nullptr}};

const FeatureEntry::FeatureParam
    kOverrideSimilarLanguagesForHrefTranslateForceAuto[] = {
        {"force-auto-translate-for-similar-languages", "true"}};

const FeatureEntry::FeatureVariation
    kOverrideSimilarLanguagesForHrefTranslateVariations[] = {
        {"(Force automatic translation of pages with the same language as the "
         "target language for hrefTranslate)",
         kOverrideSimilarLanguagesForHrefTranslateForceAuto,
         base::size(kOverrideSimilarLanguagesForHrefTranslateForceAuto),
         nullptr}};

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kExploreSitesExperimental = {
    chrome::android::explore_sites::kExploreSitesVariationParameterName,
    chrome::android::explore_sites::kExploreSitesVariationExperimental};
const FeatureEntry::FeatureParam kExploreSitesDenseTitleBottom[] = {
    {chrome::android::explore_sites::kExploreSitesDenseVariationParameterName,
     chrome::android::explore_sites::
         kExploreSitesDenseVariationDenseTitleBottom},
};
const FeatureEntry::FeatureParam kExploreSitesDenseTitleRight[] = {
    {chrome::android::explore_sites::kExploreSitesDenseVariationParameterName,
     chrome::android::explore_sites::
         kExploreSitesDenseVariationDenseTitleRight},
};
const FeatureEntry::FeatureVariation kExploreSitesVariations[] = {
    {"Experimental", &kExploreSitesExperimental, 1, nullptr},
    {"Dense Title Bottom", kExploreSitesDenseTitleBottom,
     base::size(kExploreSitesDenseTitleBottom), nullptr},
    {"Dense Title Right", kExploreSitesDenseTitleRight,
     base::size(kExploreSitesDenseTitleRight), nullptr}};
const FeatureEntry::FeatureParam kLongpressResolvePreserveTap = {
    contextual_search::kLongpressResolveParamName,
    contextual_search::kLongpressResolvePreserveTap};
const FeatureEntry::FeatureVariation kLongpressResolveVariations[] = {
    {"and preserve Tap behavior", &kLongpressResolvePreserveTap, 1, nullptr},
};

const FeatureEntry::FeatureParam kRelatedSearchesUrl = {"stamp", "1Ru"};
const FeatureEntry::FeatureParam kRelatedSearchesContent = {"stamp", "1Rc"};
const FeatureEntry::FeatureVariation kRelatedSearchesVariations[] = {
    {"from URL", &kRelatedSearchesUrl, 1, nullptr},
    {"from content", &kRelatedSearchesContent, 1, nullptr},
};
const FeatureEntry::FeatureParam kRelatedSearchesUiVerbose = {"verbosity", "v"};
const FeatureEntry::FeatureParam kRelatedSearchesUiExtreme = {"verbosity", "x"};
const FeatureEntry::FeatureVariation kRelatedSearchesUiVariations[] = {
    {"verbose", &kRelatedSearchesUiVerbose, 1, nullptr},
    {"extreme", &kRelatedSearchesUiExtreme, 1, nullptr},
};

const FeatureEntry::FeatureParam kRelatedSearchesInBarNoShowDefaultChip = {
    "default_query_chip", "false"};
const FeatureEntry::FeatureParam kRelatedSearchesInBarShowDefaultChip = {
    "default_query_chip", "true"};
const FeatureEntry::FeatureParam
    kRelatedSearchesInBarShowDefaultChipWith110SpEllipsis[] = {
        {"default_query_chip", "true"},
        {"default_query_max_width_sp", "110"}};
const FeatureEntry::FeatureParam
    kRelatedSearchesInBarShowDefaultChipWith115SpEllipsis[] = {
        {"default_query_chip", "true"},
        {"default_query_max_width_sp", "115"}};
const FeatureEntry::FeatureParam
    kRelatedSearchesInBarShowDefaultChipWith120SpEllipsis[] = {
        {"default_query_chip", "true"},
        {"default_query_max_width_sp", "120"}};
const FeatureEntry::FeatureVariation kRelatedSearchesInBarVariations[] = {
    {"without default query chip", &kRelatedSearchesInBarNoShowDefaultChip, 1,
     nullptr},
    {"with default query chip", &kRelatedSearchesInBarShowDefaultChip, 1,
     nullptr},
    {"with 110sp ellipsized default query chip",
     kRelatedSearchesInBarShowDefaultChipWith110SpEllipsis,
     base::size(kRelatedSearchesInBarShowDefaultChipWith110SpEllipsis),
     nullptr},
    {"with 115sp ellipsized default query chip",
     kRelatedSearchesInBarShowDefaultChipWith115SpEllipsis,
     base::size(kRelatedSearchesInBarShowDefaultChipWith115SpEllipsis),
     nullptr},
    {"with 120sp ellipsized default query chip",
     kRelatedSearchesInBarShowDefaultChipWith120SpEllipsis,
     base::size(kRelatedSearchesInBarShowDefaultChipWith120SpEllipsis),
     nullptr},
};

<<<<<<< HEAD
const FeatureEntry::FeatureParam kNtpSafeBrowsingModuleFastCooldown[] = {
    {ntp_features::kNtpSafeBrowsingModuleCooldownPeriodDaysParam, "0.001"},
    {ntp_features::kNtpSafeBrowsingModuleCountMaxParam, "1"}};
const FeatureEntry::FeatureVariation kNtpSafeBrowsingModuleVariations[] = {
    {"(Fast Cooldown)", kNtpSafeBrowsingModuleFastCooldown,
     std::size(kNtpSafeBrowsingModuleFastCooldown), nullptr},
};

const FeatureEntry::FeatureParam kNtpSharepointModuleTrendingInsights[] = {
    {"NtpSharepointModuleDataParam", "trending-insights"}};
const FeatureEntry::FeatureParam kNtpSharepointModuleNonInsights[] = {
    {"NtpSharepointModuleDataParam", "non-insights"}};
const FeatureEntry::FeatureParam kNtpSharepointModuleTrendingFakeData[] = {
    {"NtpSharepointModuleDataParam", "fake-trending"}};
const FeatureEntry::FeatureParam kNtpSharepointModuleNonInsightsFakeData[] = {
    {"NtpSharepointModuleDataParam", "fake-non-insights"}};

const FeatureEntry::FeatureVariation kNtpSharepointModuleVariations[] = {
    {"- Trending", kNtpSharepointModuleTrendingInsights,
     std::size(kNtpSharepointModuleTrendingInsights), nullptr},
    {"- Recently Used and Shared", kNtpSharepointModuleNonInsights,
     std::size(kNtpSharepointModuleNonInsights), nullptr},
    {"- Fake Trending Data", kNtpSharepointModuleTrendingFakeData,
     std::size(kNtpSharepointModuleTrendingFakeData), nullptr},
    {"- Fake Recently Used and Shared", kNtpSharepointModuleNonInsightsFakeData,
     std::size(kNtpSharepointModuleNonInsightsFakeData), nullptr}};

const FeatureEntry::FeatureParam kNtpMostRelevantTabResumptionModuleFakeData[] =
    {{ntp_features::kNtpMostRelevantTabResumptionModuleDataParam, "Fake Data"}};
=======
const FeatureEntry::FeatureParam kRelatedSearchesAlternateUxNoShowDefaultChip =
    {"default_query_chip", "false"};
const FeatureEntry::FeatureParam kRelatedSearchesAlternateUxShowDefaultChip = {
    "default_query_chip", "true"};
>>>>>>> chromium
const FeatureEntry::FeatureParam
    kRelatedSearchesAlternateUxShowDefaultChipWith110SpEllipsis[] = {
        {"default_query_chip", "true"},
        {"default_query_max_width_sp", "110"}};
const FeatureEntry::FeatureParam
    kRelatedSearchesAlternateUxShowDefaultChipWith115SpEllipsis[] = {
        {"default_query_chip", "true"},
        {"default_query_max_width_sp", "115"}};
const FeatureEntry::FeatureParam
    kRelatedSearchesAlternateUxShowDefaultChipWith120SpEllipsis[] = {
        {"default_query_chip", "true"},
        {"default_query_max_width_sp", "120"}};
const FeatureEntry::FeatureVariation kRelatedSearchesAlternateUxVariations[] = {
    {"without default query chip",
     &kRelatedSearchesAlternateUxNoShowDefaultChip, 1, nullptr},
    {"with default query chip", &kRelatedSearchesAlternateUxShowDefaultChip, 1,
     nullptr},
    {"with 110sp ellipsized default query chip",
     kRelatedSearchesAlternateUxShowDefaultChipWith110SpEllipsis,
     base::size(kRelatedSearchesAlternateUxShowDefaultChipWith110SpEllipsis),
     nullptr},
    {"with 115sp ellipsized default query chip",
     kRelatedSearchesAlternateUxShowDefaultChipWith115SpEllipsis,
     base::size(kRelatedSearchesAlternateUxShowDefaultChipWith115SpEllipsis),
     nullptr},
    {"with 120sp ellipsized default query chip",
     kRelatedSearchesAlternateUxShowDefaultChipWith120SpEllipsis,
     base::size(kRelatedSearchesAlternateUxShowDefaultChipWith120SpEllipsis),
     nullptr},
};

#endif  // defined(OS_ANDROID)

const FeatureEntry::FeatureParam kResamplingInputEventsLSQEnabled[] = {
    {"predictor", features::kPredictorNameLsq}};
const FeatureEntry::FeatureParam kResamplingInputEventsKalmanEnabled[] = {
    {"predictor", features::kPredictorNameKalman}};
const FeatureEntry::FeatureParam kResamplingInputEventsLinearFirstEnabled[] = {
    {"predictor", features::kPredictorNameLinearFirst}};
const FeatureEntry::FeatureParam kResamplingInputEventsLinearSecondEnabled[] = {
    {"predictor", features::kPredictorNameLinearSecond}};
const FeatureEntry::FeatureParam
<<<<<<< HEAD
    kNtpMostRelevantTabResumptionModuleRemoteTabData[] = {
        {ntp_features::kNtpMostRelevantTabResumptionModuleDataParam, "2"}};
const FeatureEntry::FeatureParam
    kNtpMostRelevantTabResumptionModuleRemoteVisitsData[] = {
        {ntp_features::kNtpMostRelevantTabResumptionModuleDataParam, "2,4"}};
const FeatureEntry::FeatureParam
    kNtpMostRelevantTabResumptionModuleAllHistoryRemoteTabData[] = {
        {ntp_features::kNtpMostRelevantTabResumptionModuleDataParam, "2,3,4"}};
const FeatureEntry::FeatureParam
    kNtpMostRelevantTabResumptionModuleVisitData[] = {
        {ntp_features::kNtpMostRelevantTabResumptionModuleDataParam,
         "1,2,3,4"}};
// Most relevant tab resumption module data params may be expressed as a comma
// separated value consisting of the integer representations of the
// `FetchOptions::URLType` enumeration, to specify what URL types should be
// provided as options to the Visited URL Ranking Service's APIs.
const FeatureEntry::FeatureVariation
    kNtpMostRelevantTabResumptionModuleVariations[] = {
        {"- Fake Data", kNtpMostRelevantTabResumptionModuleFakeData,
         std::size(kNtpMostRelevantTabResumptionModuleFakeData), nullptr},
        {"- Fake Data - Most Recent Decorator",
         kNtpMostRelevantTabResumptionModuleFakeDataMostRecent,
         std::size(kNtpMostRelevantTabResumptionModuleFakeData), nullptr},
        {"- Fake Data - Frequently Visited At Time Decorator",
         kNtpMostRelevantTabResumptionModuleFakeDataFrequentlyVisitedAtTime,
         std::size(kNtpMostRelevantTabResumptionModuleFakeData), nullptr},
        {"- Fake Data - Just Visited Decorator",
         kNtpMostRelevantTabResumptionModuleFakeDataJustVisited,
         std::size(kNtpMostRelevantTabResumptionModuleFakeData), nullptr},
        {"- Tabs Only", kNtpMostRelevantTabResumptionModuleTabData,
         std::size(kNtpMostRelevantTabResumptionModuleTabData), nullptr},
        {"- Remote Tabs Only", kNtpMostRelevantTabResumptionModuleRemoteTabData,
         std::size(kNtpMostRelevantTabResumptionModuleRemoteTabData), nullptr},
        {"- Remote Visits", kNtpMostRelevantTabResumptionModuleRemoteVisitsData,
         std::size(kNtpMostRelevantTabResumptionModuleRemoteVisitsData),
         nullptr},
        {"- All History, Remote Tabs",
         kNtpMostRelevantTabResumptionModuleAllHistoryRemoteTabData,
         std::size(kNtpMostRelevantTabResumptionModuleAllHistoryRemoteTabData),
         nullptr},
        {"- All Visits", kNtpMostRelevantTabResumptionModuleVisitData,
         std::size(kNtpMostRelevantTabResumptionModuleVisitData), nullptr},
};
#endif  // !BUILDFLAG(IS_ANDROID)

const FeatureEntry::FeatureParam
    kOnDeviceNotificationContentDetectionModelAllowlistSampleRate100[] = {
        {"OnDeviceNotificationContentDetectionModelAllowlistSamplingRate",
         "100"}};

const FeatureEntry::FeatureVariation
    kOnDeviceNotificationContentDetectionModelVariations[] = {
        {"with allowlist sample rate 100",
         kOnDeviceNotificationContentDetectionModelAllowlistSampleRate100,
         std::size(
             kOnDeviceNotificationContentDetectionModelAllowlistSampleRate100),
         nullptr},
};

#if BUILDFLAG(IS_ANDROID)

const FeatureEntry::FeatureParam kContextualSearchSuppressShortViewWith300Dp[] =
    {{"contextual_search_minimum_page_height_dp", "300"}};
const FeatureEntry::FeatureParam kContextualSearchSuppressShortViewWith400Dp[] =
    {{"contextual_search_minimum_page_height_dp", "400"}};
const FeatureEntry::FeatureParam kContextualSearchSuppressShortViewWith500Dp[] =
    {{"contextual_search_minimum_page_height_dp", "500"}};
const FeatureEntry::FeatureParam kContextualSearchSuppressShortViewWith600Dp[] =
    {{"contextual_search_minimum_page_height_dp", "600"}};
const FeatureEntry::FeatureVariation
    kContextualSearchSuppressShortViewVariations[] = {
        {"(300 dp)", kContextualSearchSuppressShortViewWith300Dp,
         std::size(kContextualSearchSuppressShortViewWith300Dp), nullptr},
        {"(400 dp)", kContextualSearchSuppressShortViewWith400Dp,
         std::size(kContextualSearchSuppressShortViewWith400Dp), nullptr},
        {"(500 dp)", kContextualSearchSuppressShortViewWith500Dp,
         std::size(kContextualSearchSuppressShortViewWith500Dp), nullptr},
        {"(600 dp)", kContextualSearchSuppressShortViewWith600Dp,
         std::size(kContextualSearchSuppressShortViewWith600Dp), nullptr},
};

const FeatureEntry::FeatureParam kRichAutocompletionFullUrl[] = {
    {"rich_autocomplete_full_url", "true"}};
const FeatureEntry::FeatureParam kRichAutocompletionNoFullUrl[] = {
    {"rich_autocomplete_full_url", "false"}};
const FeatureEntry::FeatureVariation kRichAutocompletionAndroidVariations[] = {
    {"(full url)", kRichAutocompletionFullUrl,
     std::size(kRichAutocompletionFullUrl), nullptr},
    {"(no full url)", kRichAutocompletionNoFullUrl,
     std::size(kRichAutocompletionNoFullUrl), nullptr},
};

const FeatureEntry::FeatureParam kJumpStartOmnibox1Minute[] = {
    {"jump_start_min_away_time_minutes", "1"},
    {"jump_start_cover_recently_visited_page", "true"}};
const FeatureEntry::FeatureParam kJumpStartOmnibox15Minutes[] = {
    {"jump_start_min_away_time_minutes", "15"},
    {"jump_start_cover_recently_visited_page", "true"}};
const FeatureEntry::FeatureParam kJumpStartOmnibox30Minutes[] = {
    {"jump_start_min_away_time_minutes", "30"},
    {"jump_start_cover_recently_visited_page", "true"}};
const FeatureEntry::FeatureParam kJumpStartOmnibox60Minutes[] = {
    {"jump_start_min_away_time_minutes", "60"},
    {"jump_start_cover_recently_visited_page", "true"}};

const FeatureEntry::FeatureVariation kJumpStartOmniboxVariations[] = {
    {"(after 1min)", kJumpStartOmnibox1Minute,
     std::size(kJumpStartOmnibox1Minute)},
    {"(after 15min)", kJumpStartOmnibox15Minutes,
     std::size(kJumpStartOmnibox15Minutes)},
    {"(after 30min)", kJumpStartOmnibox30Minutes,
     std::size(kJumpStartOmnibox30Minutes)},
    {"(after 60min)", kJumpStartOmnibox60Minutes,
     std::size(kJumpStartOmnibox60Minutes)}};

#endif  // BUILDFLAG(IS_ANDROID)
=======
    kResamplingInputEventsLinearResamplingEnabled[] = {
        {"predictor", features::kPredictorNameLinearResampling}};

const FeatureEntry::FeatureVariation kResamplingInputEventsFeatureVariations[] =
    {{features::kPredictorNameLsq, kResamplingInputEventsLSQEnabled,
      base::size(kResamplingInputEventsLSQEnabled), nullptr},
     {features::kPredictorNameKalman, kResamplingInputEventsKalmanEnabled,
      base::size(kResamplingInputEventsKalmanEnabled), nullptr},
     {features::kPredictorNameLinearFirst,
      kResamplingInputEventsLinearFirstEnabled,
      base::size(kResamplingInputEventsLinearFirstEnabled), nullptr},
     {features::kPredictorNameLinearSecond,
      kResamplingInputEventsLinearSecondEnabled,
      base::size(kResamplingInputEventsLinearSecondEnabled), nullptr},
     {features::kPredictorNameLinearResampling,
      kResamplingInputEventsLinearResamplingEnabled,
      base::size(kResamplingInputEventsLinearResamplingEnabled), nullptr}};
>>>>>>> chromium

const FeatureEntry::FeatureParam
    kResamplingScrollEventsPredictionTimeBasedEnabled[] = {
        {"mode", features::kPredictionTypeTimeBased},
        {"latency", features::kPredictionTypeDefaultTime}};
const FeatureEntry::FeatureParam
    kResamplingScrollEventsPredictionFramesBasedEnabled[] = {
        {"mode", features::kPredictionTypeFramesBased},
        {"latency", features::kPredictionTypeDefaultFramesRatio}};
const FeatureEntry::FeatureVariation
    kResamplingScrollEventsExperimentalPredictionVariations[] = {
        {features::kPredictionTypeTimeBased,
         kResamplingScrollEventsPredictionTimeBasedEnabled,
         base::size(kResamplingScrollEventsPredictionTimeBasedEnabled),
         nullptr},
        {features::kPredictionTypeFramesBased,
         kResamplingScrollEventsPredictionFramesBasedEnabled,
         base::size(kResamplingScrollEventsPredictionFramesBasedEnabled),
         nullptr}};

<<<<<<< HEAD
const FeatureEntry::FeatureParam
    kShowWarningsForSuspiciousNotificationsScoreThreshold70[] = {
        {"ShowWarningsForSuspiciousNotificationsScoreThreshold", "70"},
        {"ShowWarningsForSuspiciousNotificationsShouldSwapButtons", "false"}};
const FeatureEntry::FeatureParam
    kShowWarningsForSuspiciousNotificationsScoreThreshold70SwapButtons[] = {
        {"ShowWarningsForSuspiciousNotificationsScoreThreshold", "70"},
        {"ShowWarningsForSuspiciousNotificationsShouldSwapButtons", "true"}};
const FeatureEntry::FeatureVariation
    kShowWarningsForSuspiciousNotificationsVariations[] = {
        {"with suspicious score 70",
         kShowWarningsForSuspiciousNotificationsScoreThreshold70,
         std::size(kShowWarningsForSuspiciousNotificationsScoreThreshold70),
         nullptr},
        {"with suspicious score 70 and swapped buttons",
         kShowWarningsForSuspiciousNotificationsScoreThreshold70SwapButtons,
         std::size(
             kShowWarningsForSuspiciousNotificationsScoreThreshold70SwapButtons),
         nullptr},
};

#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kStartSurfaceReturnTime_Immediate[] = {
    {"start_surface_return_time_seconds", "0"},
    {"start_surface_return_time_on_tablet_seconds", "0"}};
const FeatureEntry::FeatureParam kStartSurfaceReturnTime_10Seconds[] = {
    {"start_surface_return_time_seconds", "10"},
    {"start_surface_return_time_on_tablet_seconds", "10"}};
const FeatureEntry::FeatureParam kStartSurfaceReturnTime_1Minute[] = {
    {"start_surface_return_time_seconds", "60"},
    {"start_surface_return_time_on_tablet_seconds", "60"}};
const FeatureEntry::FeatureParam kStartSurfaceReturnTime_5Minute[] = {
    {"start_surface_return_time_seconds", "300"},
    {"start_surface_return_time_on_tablet_seconds", "300"}};
const FeatureEntry::FeatureParam kStartSurfaceReturnTime_60Minute[] = {
    {"start_surface_return_time_seconds", "3600"},
    {"start_surface_return_time_on_tablet_seconds", "3600"}};
const FeatureEntry::FeatureVariation kStartSurfaceReturnTimeVariations[] = {
    {"Immediate", kStartSurfaceReturnTime_Immediate,
     std::size(kStartSurfaceReturnTime_Immediate), nullptr},
    {"10 seconds", kStartSurfaceReturnTime_10Seconds,
     std::size(kStartSurfaceReturnTime_10Seconds), nullptr},
    {"1 minute", kStartSurfaceReturnTime_1Minute,
     std::size(kStartSurfaceReturnTime_1Minute), nullptr},
    {"5 minute", kStartSurfaceReturnTime_5Minute,
     std::size(kStartSurfaceReturnTime_5Minute), nullptr},
    {"60 minute", kStartSurfaceReturnTime_60Minute,
     std::size(kStartSurfaceReturnTime_60Minute), nullptr},
=======
const FeatureEntry::FeatureParam kFilteringPredictionEmptyFilterEnabled[] = {
    {"filter", features::kFilterNameEmpty}};
const FeatureEntry::FeatureParam kFilteringPredictionOneEuroFilterEnabled[] = {
    {"filter", features::kFilterNameOneEuro}};

const FeatureEntry::FeatureVariation kFilteringPredictionFeatureVariations[] = {
    {features::kFilterNameEmpty, kFilteringPredictionEmptyFilterEnabled,
     base::size(kFilteringPredictionEmptyFilterEnabled), nullptr},
    {features::kFilterNameOneEuro, kFilteringPredictionOneEuroFilterEnabled,
     base::size(kFilteringPredictionOneEuroFilterEnabled), nullptr}};

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kTabSwitcherOnReturn_Immediate[] = {
    {"tab_switcher_on_return_time_ms", "0"}};
const FeatureEntry::FeatureParam kTabSwitcherOnReturn_1Minute[] = {
    {"tab_switcher_on_return_time_ms", "60000"}};
const FeatureEntry::FeatureParam kTabSwitcherOnReturn_30Minutes[] = {
    {"tab_switcher_on_return_time_ms", "1800000"}};
const FeatureEntry::FeatureParam kTabSwitcherOnReturn_60Minutes[] = {
    {"tab_switcher_on_return_time_ms", "3600000"}};
const FeatureEntry::FeatureVariation kTabSwitcherOnReturnVariations[] = {
    {"Immediate", kTabSwitcherOnReturn_Immediate,
     base::size(kTabSwitcherOnReturn_30Minutes), nullptr},
    {"1 minute", kTabSwitcherOnReturn_1Minute,
     base::size(kTabSwitcherOnReturn_30Minutes), nullptr},
    {"30 minutes", kTabSwitcherOnReturn_30Minutes,
     base::size(kTabSwitcherOnReturn_30Minutes), nullptr},
    {"60 minutes", kTabSwitcherOnReturn_60Minutes,
     base::size(kTabSwitcherOnReturn_60Minutes), nullptr},
>>>>>>> chromium
};
#endif  // OS_ANDROID

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kTabGridLayoutAndroid_NewTabVariation[] = {
    {"tab_grid_layout_android_new_tab", "NewTabVariation"},
    {"allow_to_refetch", "true"}};

const FeatureEntry::FeatureParam kTabGridLayoutAndroid_NewTabTile[] = {
    {"tab_grid_layout_android_new_tab_tile", "NewTabTile"}};

<<<<<<< HEAD
const FeatureEntry::FeatureParam kDefaultBrowserPromoShowArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceShowCardParam,
     segmentation_platform::kDefaultBrowserPromo},
};
const FeatureEntry::FeatureParam kDefaultBrowserPromoHideArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceHideCardParam,
     segmentation_platform::kDefaultBrowserPromo},
};
const FeatureEntry::FeatureParam kTabGroupPromoShowArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceShowCardParam,
     segmentation_platform::kTabGroupPromo},
};
const FeatureEntry::FeatureParam kTabGroupPromoHideArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceHideCardParam,
     segmentation_platform::kTabGroupPromo},
};
const FeatureEntry::FeatureParam kTabGroupSyncPromoShowArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceShowCardParam,
     segmentation_platform::kTabGroupSyncPromo},
};
const FeatureEntry::FeatureParam kTabGroupSyncPromoHideArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceHideCardParam,
     segmentation_platform::kTabGroupSyncPromo},
};
const FeatureEntry::FeatureParam kQuickDeletePromoShowArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceShowCardParam,
     segmentation_platform::kQuickDeletePromo},
};
const FeatureEntry::FeatureParam kQuickDeletePromoHideArm[] = {
    {segmentation_platform::features::kEphemeralCardRankerForceHideCardParam,
     segmentation_platform::kQuickDeletePromo},
};

const FeatureEntry::FeatureVariation kEphemeralCardRankerCardOverrideOptions[] =
    {
        {"- Force show default browser promo", kDefaultBrowserPromoShowArm,
         std::size(kDefaultBrowserPromoShowArm), nullptr},
        {"- Force hide default browser promo", kDefaultBrowserPromoHideArm,
         std::size(kDefaultBrowserPromoHideArm), nullptr},
        {"- Force show tab group promo", kTabGroupPromoShowArm,
         std::size(kTabGroupPromoShowArm), nullptr},
        {"- Force hide tab group promo", kTabGroupPromoHideArm,
         std::size(kTabGroupPromoHideArm), nullptr},
        {"- Force show tab group sync promo", kTabGroupSyncPromoShowArm,
         std::size(kTabGroupSyncPromoShowArm), nullptr},
        {"- Force hide tab group sync promo", kTabGroupSyncPromoHideArm,
         std::size(kTabGroupSyncPromoHideArm), nullptr},
        {"- Force show quick delete promo", kQuickDeletePromoShowArm,
         std::size(kQuickDeletePromoShowArm), nullptr},
        {"- Force hide quick delete promo", kQuickDeletePromoHideArm,
         std::size(kQuickDeletePromoHideArm), nullptr},
};
#endif  // BUILDFLAG(IS_ANDROID)
#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kLogoPolish_large[] = {
    {"polish_logo_size_large", "true"},
    {"polish_logo_size_medium", "false"}};

const FeatureEntry::FeatureParam kLogoPolish_medium[] = {
    {"polish_logo_size_large", "false"},
    {"polish_logo_size_medium", "true"}};

const FeatureEntry::FeatureParam kLogoPolish_small[] = {
    {"polish_logo_size_large", "false"},
    {"polish_logo_size_medium", "false"}};

const FeatureEntry::FeatureVariation kLogoPolishVariations[] = {
    {"Logo height is large", kLogoPolish_large, std::size(kLogoPolish_large),
     nullptr},
    {"Logo height is medium", kLogoPolish_medium, std::size(kLogoPolish_medium),
     nullptr},
    {"Logo height is small", kLogoPolish_small, std::size(kLogoPolish_small),
     nullptr},
=======
const FeatureEntry::FeatureParam kTabGridLayoutAndroid_TallNTV[] = {
    {"thumbnail_aspect_ratio", "0.85"},
    {"allow_to_refetch", "true"},
    {"tab_grid_layout_android_new_tab", "NewTabVariation"},
    {"enable_launch_polish", "true"},
    {"enable_launch_bug_fix", "true"}};

const FeatureEntry::FeatureParam kTabGridLayoutAndroid_SearchChip[] = {
    {"enable_search_term_chip", "true"}};

const FeatureEntry::FeatureParam kCommercePriceTracking_PriceAlerts[] = {
    {"enable_price_tracking", "true"},
    {"price_tracking_with_optimization_guide", "false"}};

const FeatureEntry::FeatureParam
    kCommercePriceTracking_PriceAlerts_WithOptimizationGuide[] = {
        {"enable_price_tracking", "true"},
        {"price_tracking_with_optimization_guide", "true"}};

const FeatureEntry::FeatureParam kTabGridLayoutAndroid_TabGroupAutoCreation[] =
    {{"enable_tab_group_auto_creation", "false"}};

const FeatureEntry::FeatureParam kCommercePriceTracking_PriceNotifications[] = {
    {"enable_price_notification", "true"}};

const FeatureEntry::FeatureVariation kTabGridLayoutAndroidVariations[] = {
    {"New Tab Variation", kTabGridLayoutAndroid_NewTabVariation,
     base::size(kTabGridLayoutAndroid_NewTabVariation), nullptr},
    {"New Tab Tile", kTabGridLayoutAndroid_NewTabTile,
     base::size(kTabGridLayoutAndroid_NewTabTile), nullptr},
    {"Tall NTV", kTabGridLayoutAndroid_TallNTV,
     base::size(kTabGridLayoutAndroid_TallNTV), nullptr},
    {"Search term chip", kTabGridLayoutAndroid_SearchChip,
     base::size(kTabGridLayoutAndroid_SearchChip), nullptr},
    {"Without auto group", kTabGridLayoutAndroid_TabGroupAutoCreation,
     base::size(kTabGridLayoutAndroid_TabGroupAutoCreation), nullptr},
};

const FeatureEntry::FeatureVariation kCommercePriceTrackingAndroidVariations[] =
    {
        {"Price alerts", kCommercePriceTracking_PriceAlerts,
         base::size(kCommercePriceTracking_PriceAlerts), nullptr},
        {"Price alerts with OptimizationGuide",
         kCommercePriceTracking_PriceAlerts_WithOptimizationGuide,
         base::size(kCommercePriceTracking_PriceAlerts_WithOptimizationGuide),
         nullptr},
        {"Price notifications", kCommercePriceTracking_PriceNotifications,
         base::size(kCommercePriceTracking_PriceNotifications), nullptr},
>>>>>>> chromium
};

const FeatureEntry::FeatureParam kStartSurfaceAndroid_SingleSurface[] = {
    {"start_surface_variation", "single"},
    {"show_tabs_in_mru_order", "false"}};

const FeatureEntry::FeatureParam kStartSurfaceAndroid_SingleSurfaceFinale[] = {
    {"start_surface_variation", "single"},
    {"omnibox_focused_on_new_tab", "true"},
    {"home_button_on_grid_tab_switcher", "true"},
    {"new_home_surface_from_home_button", "hide_tab_switcher_only"},
    {"hide_switch_when_no_incognito_tabs", "true"},
    {"show_tabs_in_mru_order", "true"},
    {"enable_tab_groups_continuation", "true"}};

const FeatureEntry::FeatureParam
    kStartSurfaceAndroid_SingleSurfaceFinale_NTPTilesOnOmnibox[] = {
        {"start_surface_variation", "single"},
        {"omnibox_focused_on_new_tab", "true"},
        {"show_ntp_tiles_on_omnibox", "true"},
        {"home_button_on_grid_tab_switcher", "true"},
        {"new_home_surface_from_home_button", "hide_mv_tiles_and_tab_switcher"},
        {"hide_switch_when_no_incognito_tabs", "true"},
        {"show_tabs_in_mru_order", "true"},
        {"enable_tab_groups_continuation", "true"}};

const FeatureEntry::FeatureParam kStartSurfaceAndroid_SingleSurface_V2[] = {
    {"start_surface_variation", "single"},
    {"show_last_active_tab_only", "true"},
    {"exclude_mv_tiles", "true"},
    {"open_ntp_instead_of_start", "true"}};

const FeatureEntry::FeatureParam kStartSurfaceAndroid_SingleSurface_V2Finale[] =
    {{"start_surface_variation", "single"},
     {"show_last_active_tab_only", "true"},
     {"omnibox_focused_on_new_tab", "true"},
     {"home_button_on_grid_tab_switcher", "true"},
     {"new_home_surface_from_home_button", "hide_tab_switcher_only"},
     {"enable_tab_groups_continuation", "true"}};

const FeatureEntry::FeatureParam
    kStartSurfaceAndroid_SingleSurface_V2Finale_NTPTilesOnOmnibox[] = {
        {"start_surface_variation", "single"},
        {"show_last_active_tab_only", "true"},
        {"omnibox_focused_on_new_tab", "true"},
        {"show_ntp_tiles_on_omnibox", "true"},
        {"home_button_on_grid_tab_switcher", "true"},
        {"new_home_surface_from_home_button", "hide_mv_tiles_and_tab_switcher"},
        {"enable_tab_groups_continuation", "true"}};

const FeatureEntry::FeatureParam kStartSurfaceAndroid_SingleSurfaceSingleTab[] =
    {{"start_surface_variation", "single"},
     {"show_last_active_tab_only", "true"},
     {"hide_switch_when_no_incognito_tabs", "true"}};

const FeatureEntry::FeatureVariation kStartSurfaceAndroidVariations[] = {
    {"Single Surface", kStartSurfaceAndroid_SingleSurface,
     base::size(kStartSurfaceAndroid_SingleSurface), nullptr},
    {"Single Surface Finale", kStartSurfaceAndroid_SingleSurfaceFinale,
     base::size(kStartSurfaceAndroid_SingleSurfaceFinale), nullptr},
    {"Single Surface Finale + NTP tiles on Omnibox",
     kStartSurfaceAndroid_SingleSurfaceFinale_NTPTilesOnOmnibox,
     base::size(kStartSurfaceAndroid_SingleSurfaceFinale_NTPTilesOnOmnibox),
     nullptr},
    {"Single Surface V2", kStartSurfaceAndroid_SingleSurface_V2,
     base::size(kStartSurfaceAndroid_SingleSurface_V2), nullptr},
    {"Single Surface V2 Finale", kStartSurfaceAndroid_SingleSurface_V2Finale,
     base::size(kStartSurfaceAndroid_SingleSurface_V2Finale), nullptr},
    {"Single Surface V2 Finale + NTP tiles on Omnibox",
     kStartSurfaceAndroid_SingleSurface_V2Finale_NTPTilesOnOmnibox,
     base::size(kStartSurfaceAndroid_SingleSurface_V2Finale_NTPTilesOnOmnibox),
     nullptr},
    {"Single Surface + Single Tab", kStartSurfaceAndroid_SingleSurfaceSingleTab,
     base::size(kStartSurfaceAndroid_SingleSurfaceSingleTab), nullptr},
};

const FeatureEntry::FeatureParam kWebFeed_accelerator[] = {
    {"recommendation_style", "accelerator"}};

const FeatureEntry::FeatureParam kWebFeed_IPH[] = {
    {"recommendation_style", "IPH"}};

const FeatureEntry::FeatureVariation kWebFeedVariations[] = {
    {"accelerator recommendations", kWebFeed_accelerator,
     base::size(kWebFeed_accelerator), nullptr},
    {"IPH recommendations", kWebFeed_IPH, base::size(kWebFeed_IPH), nullptr},
};

const FeatureEntry::FeatureParam kConditionalTabStripAndroid_Immediate[] = {
    {"conditional_tab_strip_session_time_ms", "0"}};
const FeatureEntry::FeatureParam kConditionalTabStripAndroid_60Minutes[] = {
    {"conditional_tab_strip_session_time_ms", "3600000"}};
const FeatureEntry::FeatureVariation kConditionalTabStripAndroidVariations[] = {
    {"Immediate", kConditionalTabStripAndroid_Immediate,
     base::size(kConditionalTabStripAndroid_Immediate), nullptr},
    {"60 minutes", kConditionalTabStripAndroid_60Minutes,
     base::size(kConditionalTabStripAndroid_60Minutes), nullptr},
};
#endif  // OS_ANDROID

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kAddToHomescreen_UseTextBubble[] = {
    {"use_text_bubble", "true"}};
const FeatureEntry::FeatureParam kAddToHomescreen_UseMessage[] = {
    {"use_message", "true"}};

const FeatureEntry::FeatureVariation kAddToHomescreenIPHVariations[] = {
    {"Use Text Bubble", kAddToHomescreen_UseTextBubble,
     base::size(kAddToHomescreen_UseTextBubble), nullptr},
    {"Use Message", kAddToHomescreen_UseMessage,
     base::size(kAddToHomescreen_UseMessage), nullptr}};
#endif

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam
    kAutofillUseMobileLabelDisambiguationShowAll[] = {
        {autofill::features::kAutofillUseMobileLabelDisambiguationParameterName,
         autofill::features::
             kAutofillUseMobileLabelDisambiguationParameterShowAll}};
const FeatureEntry::FeatureParam
    kAutofillUseMobileLabelDisambiguationShowOne[] = {
        {autofill::features::kAutofillUseMobileLabelDisambiguationParameterName,
         autofill::features::
             kAutofillUseMobileLabelDisambiguationParameterShowOne}};

const FeatureEntry::FeatureVariation
    kAutofillUseMobileLabelDisambiguationVariations[] = {
        {"(show all)", kAutofillUseMobileLabelDisambiguationShowAll,
         base::size(kAutofillUseMobileLabelDisambiguationShowAll), nullptr},
        {"(show one)", kAutofillUseMobileLabelDisambiguationShowOne,
         base::size(kAutofillUseMobileLabelDisambiguationShowOne), nullptr}};
#endif  // defined(OS_ANDROID)

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kHomepagePromoCardLarge[] = {
    {"promo-card-variation", "Large"}};
const FeatureEntry::FeatureParam kHomepagePromoCardCompact[] = {
    {"promo-card-variation", "Compact"}};
const FeatureEntry::FeatureParam kHomepagePromoCardSlim[] = {
    {"promo-card-variation", "Slim"}};
const FeatureEntry::FeatureParam kHomepagePromoCardSuppressing[] = {
    {"promo-card-variation", "Compact"},
    {"suppressing_sign_in_promo", "true"}};

const FeatureEntry::FeatureVariation kHomepagePromoCardVariations[] = {
    {"Large", kHomepagePromoCardLarge, base::size(kHomepagePromoCardLarge),
     nullptr},
    {"Compact", kHomepagePromoCardCompact,
     base::size(kHomepagePromoCardCompact), nullptr},
    {"Slim", kHomepagePromoCardSlim, base::size(kHomepagePromoCardSlim),
     nullptr},
    {"Compact_SuppressingSignInPromo", kHomepagePromoCardSuppressing,
     base::size(kHomepagePromoCardSuppressing), nullptr}};
#endif  // defined(OS_ANDROID)

#if defined(OS_ANDROID)
const FeatureEntry::FeatureParam kLensCameraAssistedSearchLensButtonStart[] = {
    {"searchBoxStartVariantForLensCameraAssistedSearch", "true"}};

const FeatureEntry::FeatureParam kLensCameraAssistedSearchLensButtonEnd[] = {
    {"searchBoxStartVariantForLensCameraAssistedSearch", "false"}};

const FeatureEntry::FeatureParam
    kLensCameraAssistedSkipAgsaVersionCheckEnabled[] = {
        {"skipAgsaVersionCheck", "true"}};

const FeatureEntry::FeatureParam
    kLensCameraAssistedSkipAgsaVersionCheckDisabled[] = {
        {"skipAgsaVersionCheck", "false"}};

const FeatureEntry::FeatureVariation kLensCameraAssistedSearchVariations[] = {
    {"(Lens then Mic)", kLensCameraAssistedSearchLensButtonStart,
     base::size(kLensCameraAssistedSearchLensButtonStart), nullptr},
    {"(Mic then Lens)", kLensCameraAssistedSearchLensButtonEnd,
     base::size(kLensCameraAssistedSearchLensButtonEnd), nullptr},
    {"(without AGSA version check)",
     kLensCameraAssistedSkipAgsaVersionCheckEnabled,
     base::size(kLensCameraAssistedSkipAgsaVersionCheckEnabled), nullptr},
    {"(with AGSA version check )",
     kLensCameraAssistedSkipAgsaVersionCheckDisabled,
     base::size(kLensCameraAssistedSkipAgsaVersionCheckDisabled), nullptr}};

const FeatureEntry::FeatureParam kLensContextMenuTranslateHideRemoveIcon[] = {
    {"hideChipRemoveIcon", "true"}};

const FeatureEntry::FeatureVariation kLensContextMenuTranslateVariations[] = {
    {"(Hide Remove Icon)", kLensContextMenuTranslateHideRemoveIcon,
     base::size(kLensContextMenuTranslateHideRemoveIcon), nullptr},
};

#endif  // defined(OS_ANDROID)

const FeatureEntry::FeatureParam kLazyFrameLoadingAutomatic[] = {
    {"automatic-lazy-load-frames-enabled", "true"},
    {"restrict-lazy-load-frames-to-data-saver-only", "false"},
};

const FeatureEntry::FeatureVariation kLazyFrameLoadingVariations[] = {
    {"(Automatically lazily load where safe even if not marked "
     "'loading=lazy')",
     kLazyFrameLoadingAutomatic, base::size(kLazyFrameLoadingAutomatic),
     nullptr}};

const FeatureEntry::FeatureParam kLazyImageLoadingAutomatic[] = {
    {"automatic-lazy-load-images-enabled", "true"},
    {"restrict-lazy-load-images-to-data-saver-only", "false"},
};

const FeatureEntry::FeatureVariation kLazyImageLoadingVariations[] = {
    {"(Automatically lazily load where safe even if not marked "
     "'loading=lazy')",
     kLazyImageLoadingAutomatic, base::size(kLazyImageLoadingAutomatic),
     nullptr}};

const FeatureEntry::Choice kNotificationSchedulerChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::
         kNotificationSchedulerImmediateBackgroundTaskDescription,
     notifications::switches::kNotificationSchedulerImmediateBackgroundTask,
     ""},
};

#if defined(OS_ANDROID)

const FeatureEntry::FeatureParam kIphMicToolbarGenericMessage[] = {
    {"generic_message", "true"}};
const FeatureEntry::FeatureParam kIphMicToolbarExampleQuery[] = {
    {"generic_message", "false"}};
const FeatureEntry::FeatureVariation kIphMicToolbarVariations[] = {
    {"generic message", kIphMicToolbarGenericMessage,
     base::size(kIphMicToolbarGenericMessage), nullptr},
    {"example query", kIphMicToolbarExampleQuery,
     base::size(kIphMicToolbarExampleQuery), nullptr},

<<<<<<< HEAD
const FeatureEntry::FeatureVariation
    kPhotoPickerAdoptionStudyFeatureVariations[] = {
        {"(Android Picker w/ACTION_GET_CONTENT)",
         kPhotoPickerAdoptionStudyActionGetContent,
         std::size(kPhotoPickerAdoptionStudyActionGetContent), nullptr},
        {"(Android Picker w/ACTION_PICK_IMAGES)",
         kPhotoPickerAdoptionStudyActionPickImages,
         std::size(kPhotoPickerAdoptionStudyActionPickImages), nullptr},
        {"(Android Picker w/ACTION_PICK_IMAGES Plus)",
         kPhotoPickerAdoptionStudyActionPickImagesPlus,
         std::size(kPhotoPickerAdoptionStudyActionPickImagesPlus), nullptr},
        {"(Chrome Picker without Browse)",
         kPhotoPickerAdoptionStudyChromePickerWithoutBrowse,
         std::size(kPhotoPickerAdoptionStudyChromePickerWithoutBrowse),
         nullptr}};

const FeatureEntry::FeatureParam
    kAndroidAppIntegrationWithFavicon_UseLargeFavicon[] = {
        {"use_large_favicon", "true"}};
const FeatureEntry::FeatureParam
    kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipDeviceCheck[] = {
        {"skip_device_check", "true"},
        {"use_large_favicon", "true"}};
const FeatureEntry::FeatureParam
    kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipSchemaCheck[] = {
        {"skip_schema_check", "true"},
        {"use_large_favicon", "true"}};
const FeatureEntry::FeatureParam
    kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipDeviceAndSchemaChecks
        [] = {{"skip_device_check", "true"},
              {"skip_schema_check", "true"},
              {"use_large_favicon", "true"}};
const FeatureEntry::FeatureParam
    kAndroidAppIntegrationWithFavicon_DelayTime200Ms[] = {
        {"schedule_delay_time_ms", "200"}};
const FeatureEntry::FeatureParam
    kAndroidAppIntegrationWithFavicon_DelayTime200Ms_UseLargeFavicon[] = {
        {"schedule_delay_time_ms", "200"},
        {"use_large_favicon", "true"}};

const FeatureEntry::FeatureVariation kAndroidAppIntegrationWithFaviconVariations[] =
    {{"Use large favicon (no delay)",
      kAndroidAppIntegrationWithFavicon_UseLargeFavicon,
      std::size(kAndroidAppIntegrationWithFavicon_UseLargeFavicon), nullptr},
     {"Skip device check + use large favicon (no delay)",
      kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipDeviceCheck,
      std::size(
          kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipDeviceCheck),
      nullptr},
     {"Skip schema check + use large favicon (no delay)",
      kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipSchemaCheck,
      std::size(
          kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipSchemaCheck),
      nullptr},
     {"Skip both device and schema checks + use large favicon (no delay)",
      kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipDeviceAndSchemaChecks,
      std::size(
          kAndroidAppIntegrationWithFavicon_UseLargeFavicon_SkipDeviceAndSchemaChecks),
      nullptr},
     {"200ms delay", kAndroidAppIntegrationWithFavicon_DelayTime200Ms,
      std::size(kAndroidAppIntegrationWithFavicon_DelayTime200Ms), nullptr},
     {"200ms delay with large favicon",
      kAndroidAppIntegrationWithFavicon_DelayTime200Ms_UseLargeFavicon,
      std::size(
          kAndroidAppIntegrationWithFavicon_DelayTime200Ms_UseLargeFavicon),
      nullptr}};

const FeatureEntry::FeatureParam
    kAndroidAppIntegrationModule_ForceCardShown_Pixel[] = {
        {"force_card_shown", "true"}};

const FeatureEntry::FeatureParam
    kAndroidAppIntegrationModule_ForceCardShown_NonPixel[] = {
        {"force_card_shown", "true"},
        {"show_third_party_card", "true"}};

const FeatureEntry::FeatureVariation kAndroidAppIntegrationModuleVariations[] =
    {{"Force to show Pixel's notice card",
      kAndroidAppIntegrationModule_ForceCardShown_Pixel,
      std::size(kAndroidAppIntegrationModule_ForceCardShown_Pixel), nullptr},
     {"Force to show opt in card",
      kAndroidAppIntegrationModule_ForceCardShown_NonPixel,
      std::size(kAndroidAppIntegrationModule_ForceCardShown_NonPixel),
      nullptr}};

const FeatureEntry::FeatureParam kAuxiliarySearchDonation_MaxDonation_20[] = {
    {chrome::android::kAuxiliarySearchMaxBookmarksCountParam.name, "20"},
    {chrome::android::kAuxiliarySearchMaxTabsCountParam.name, "20"}};
const FeatureEntry::FeatureParam kAuxiliarySearchDonation_MaxDonation_100[] = {
    {chrome::android::kAuxiliarySearchMaxBookmarksCountParam.name, "100"},
    {chrome::android::kAuxiliarySearchMaxTabsCountParam.name, "100"}};
const FeatureEntry::FeatureParam kAuxiliarySearchDonation_MaxDonation_200[] = {
    {chrome::android::kAuxiliarySearchMaxBookmarksCountParam.name, "200"},
    {chrome::android::kAuxiliarySearchMaxTabsCountParam.name, "200"}};
const FeatureEntry::FeatureParam kAuxiliarySearchDonation_MaxDonation_500[] = {
    {chrome::android::kAuxiliarySearchMaxBookmarksCountParam.name, "500"},
    {chrome::android::kAuxiliarySearchMaxTabsCountParam.name, "500"}};
const FeatureEntry::FeatureVariation kAuxiliarySearchDonationVariations[] = {
    {"50 counts", kAuxiliarySearchDonation_MaxDonation_20,
     std::size(kAuxiliarySearchDonation_MaxDonation_20), nullptr},
    {"100 counts", kAuxiliarySearchDonation_MaxDonation_100,
     std::size(kAuxiliarySearchDonation_MaxDonation_100), nullptr},
    {"200 counts", kAuxiliarySearchDonation_MaxDonation_200,
     std::size(kAuxiliarySearchDonation_MaxDonation_200), nullptr},
    {"500 counts", kAuxiliarySearchDonation_MaxDonation_500,
     std::size(kAuxiliarySearchDonation_MaxDonation_500), nullptr},
=======
>>>>>>> chromium
};

const FeatureEntry::FeatureParam kOmniboxAssistantVoiceSearchGreyMic[] = {
    {"min_agsa_version", "10.95"},
    {"colorful_mic", "false"}};

const FeatureEntry::FeatureParam kOmniboxAssistantVoiceSearchColorfulMic[] = {
    {"min_agsa_version", "10.95"},
    {"colorful_mic", "true"}};

const FeatureEntry::FeatureParam
    kOmniboxAssistantVoiceSearchNoMultiAccountCheck[] = {
        {"min_agsa_version", "10.95"},
        {"colorful_mic", "true"},
        {"enable_multi_account_check", "false"}};

const FeatureEntry::FeatureVariation kOmniboxAssistantVoiceSearchVariations[] =
    {
        {"(grey mic)", kOmniboxAssistantVoiceSearchGreyMic,
         base::size(kOmniboxAssistantVoiceSearchGreyMic), nullptr},
        {"(colorful mic)", kOmniboxAssistantVoiceSearchColorfulMic,
         base::size(kOmniboxAssistantVoiceSearchColorfulMic), nullptr},
        {"(no account check)", kOmniboxAssistantVoiceSearchNoMultiAccountCheck,
         base::size(kOmniboxAssistantVoiceSearchNoMultiAccountCheck), nullptr},
};

const FeatureEntry::FeatureParam
    kPhotoPickerVideoSupportEnabledWithAnimatedThumbnails[] = {
        {"animate_thumbnails", "true"}};
const FeatureEntry::FeatureVariation
    kPhotoPickerVideoSupportFeatureVariations[] = {
        {"(with animated thumbnails)",
         kPhotoPickerVideoSupportEnabledWithAnimatedThumbnails,
         base::size(kPhotoPickerVideoSupportEnabledWithAnimatedThumbnails),
         nullptr}};

// Request Desktop Site on Tablet by default variations.
const FeatureEntry::FeatureParam kRequestDesktopSiteForTablets100[] = {
    {"screen_width_dp", "100"},
    {"enabled", "true"}};
const FeatureEntry::FeatureParam kRequestDesktopSiteForTablets600[] = {
    {"screen_width_dp", "600"},
    {"enabled", "true"}};
const FeatureEntry::FeatureParam kRequestDesktopSiteForTablets768[] = {
    {"screen_width_dp", "768"},
    {"enabled", "true"}};
const FeatureEntry::FeatureParam kRequestDesktopSiteForTablets960[] = {
    {"screen_width_dp", "960"},
    {"enabled", "true"}};
const FeatureEntry::FeatureParam kRequestDesktopSiteForTablets1024[] = {
    {"screen_width_dp", "1024"},
    {"enabled", "true"}};
const FeatureEntry::FeatureParam kRequestDesktopSiteForTablets1280[] = {
    {"screen_width_dp", "1280"},
    {"enabled", "true"}};
const FeatureEntry::FeatureParam kRequestDesktopSiteForTablets1920[] = {
    {"screen_width_dp", "1920"},
    {"enabled", "true"}};
const FeatureEntry::FeatureVariation kRequestDesktopSiteForTabletsVariations[] =
    {{"for 100dp+ screens", kRequestDesktopSiteForTablets100,
      base::size(kRequestDesktopSiteForTablets100), nullptr},
     {"for 600dp+ screens", kRequestDesktopSiteForTablets600,
      base::size(kRequestDesktopSiteForTablets600), nullptr},
     {"for 768dp+ screens", kRequestDesktopSiteForTablets768,
      base::size(kRequestDesktopSiteForTablets768), nullptr},
     {"for 960dp+ screens", kRequestDesktopSiteForTablets960,
      base::size(kRequestDesktopSiteForTablets960), nullptr},
     {"for 1024dp+ screens", kRequestDesktopSiteForTablets1024,
      base::size(kRequestDesktopSiteForTablets1024), nullptr},
     {"for 1280dp+ screens", kRequestDesktopSiteForTablets1280,
      base::size(kRequestDesktopSiteForTablets1280), nullptr},
     {"for 1920dp+ screens", kRequestDesktopSiteForTablets1920,
      base::size(kRequestDesktopSiteForTablets1920), nullptr}};
#endif  // OS_ANDROID

#if defined(OS_ANDROID)
const FeatureEntry::FeatureVariation
    kOmniboxOnDeviceHeadSuggestNonIncognitoExperimentVariations[] = {
        {
            "relevance-1000",
            (FeatureEntry::FeatureParam[]){
                {OmniboxFieldTrial::kOnDeviceHeadSuggestMaxScoreForNonUrlInput,
                 "1000"},
                {OmniboxFieldTrial::kOnDeviceHeadSuggestDemoteMode,
                 "decrease-relevances"}},
            2,
            nullptr,
        },
        {
            "no-delay-relevance-1000",
            (FeatureEntry::FeatureParam[]){
                {OmniboxFieldTrial::kOnDeviceHeadSuggestDelaySuggestRequestMs,
                 "0"},
                {OmniboxFieldTrial::kOnDeviceHeadSuggestMaxScoreForNonUrlInput,
                 "1000"},
                {OmniboxFieldTrial::kOnDeviceHeadSuggestDemoteMode,
                 "decrease-relevances"}},
            3,
            nullptr,
        }};
#endif  // defined(OS_ANDROID)

const FeatureEntry::FeatureParam
    kQuietNotificationPromptsWithAdaptiveActivation[] = {
        {QuietNotificationPermissionUiConfig::kEnableAdaptiveActivation,
         "true"},
        {QuietNotificationPermissionUiConfig::kEnableAbusiveRequestBlocking,
         "true"},
        {QuietNotificationPermissionUiConfig::kEnableAbusiveRequestWarning,
         "true"},
        {QuietNotificationPermissionUiConfig::kEnableCrowdDenyTriggering,
         "true"},
        {QuietNotificationPermissionUiConfig::kCrowdDenyHoldBackChance, "0"}};

// The default "Enabled" option has the semantics of showing the quiet UI
// (animated location bar indicator on Desktop, and mini-infobars on Android),
// but only when the user directly turns it on in Settings. In addition to that,
// expose an option to also enable adaptively turning on the quiet UI after
// three consecutive denies or based on crowd deny verdicts.
const FeatureEntry::FeatureVariation kQuietNotificationPromptsVariations[] = {
    {"(with adaptive activation)",
     kQuietNotificationPromptsWithAdaptiveActivation,
     base::size(kQuietNotificationPromptsWithAdaptiveActivation), nullptr},
};

// TODO(crbug.com/991082,1015377): Remove after proper support for back-forward
// cache is implemented.
const FeatureEntry::FeatureParam kBackForwardCache_ForceCaching[] = {
    {"TimeToLiveInBackForwardCacheInSeconds", "300"},
    {"should_ignore_blocklists", "true"},
    {"enable_same_site", "true"}};

// With this, back-forward cache will be enabled on eligible pages when doing
// same-site navigations (instead of only cross-site navigations).
const FeatureEntry::FeatureParam kBackForwardCache_SameSite[] = {
    {"enable_same_site", "true"}};

const FeatureEntry::FeatureVariation kBackForwardCacheVariations[] = {
    {"same-site support (experimental)", kBackForwardCache_SameSite,
     base::size(kBackForwardCache_SameSite), nullptr},
    {"force caching all pages (experimental)", kBackForwardCache_ForceCaching,
     base::size(kBackForwardCache_ForceCaching), nullptr},
};

const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalFailure2250[] = {
        {"lcp-limit-in-ms", "2250"},
        {"intervention-mode", "failure"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalFailure2000[] = {
        {"lcp-limit-in-ms", "2000"},
        {"intervention-mode", "failure"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1750[] = {
        {"lcp-limit-in-ms", "1750"},
        {"intervention-mode", "failure"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1500[] = {
        {"lcp-limit-in-ms", "1500"},
        {"intervention-mode", "failure"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1250[] = {
        {"lcp-limit-in-ms", "1250"},
        {"intervention-mode", "failure"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1000[] = {
        {"lcp-limit-in-ms", "1000"},
        {"intervention-mode", "failure"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalSwap2250[] = {
        {"lcp-limit-in-ms", "2250"},
        {"intervention-mode", "swap"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalSwap2000[] = {
        {"lcp-limit-in-ms", "2000"},
        {"intervention-mode", "swap"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1750[] = {
        {"lcp-limit-in-ms", "1750"},
        {"intervention-mode", "swap"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1500[] = {
        {"lcp-limit-in-ms", "1500"},
        {"intervention-mode", "swap"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1250[] = {
        {"lcp-limit-in-ms", "1250"},
        {"intervention-mode", "swap"}};
const FeatureEntry::FeatureParam
    kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1000[] = {
        {"lcp-limit-in-ms", "1000"},
        {"intervention-mode", "swap"}};
const FeatureEntry::FeatureVariation
    kAlignFontDisplayAutoTimeoutWithLCPGoalVariations[] = {
        {"switch to failure after 2250ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalFailure2250,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalFailure2250),
         nullptr},
        {"switch to failure after 2000ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalFailure2000,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalFailure2000),
         nullptr},
        {"switch to failure after 1750ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1750,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1750),
         nullptr},
        {"switch to failure after 1500ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1500,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1500),
         nullptr},
        {"switch to failure after 1250ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1250,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1250),
         nullptr},
        {"switch to failure after 1000ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1000,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalFailure1000),
         nullptr},
        {"switch to swap after 2250ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalSwap2250,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalSwap2250), nullptr},
        {"switch to swap after 2000ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalSwap2000,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalSwap2000), nullptr},
        {"switch to swap after 1750ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1750,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1750), nullptr},
        {"switch to swap after 1500ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1500,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1500), nullptr},
        {"switch to swap after 1250ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1250,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1250), nullptr},
        {"switch to swap after 1000ms since navigation",
         kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1000,
         base::size(kAlignFontDisplayAutoTimeoutWithLCPGoalSwap1000), nullptr},
};

#if BUILDFLAG(IS_CHROMEOS_ASH)
const FeatureEntry::Choice kEnableCrOSActionRecorderChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {ash::switches::kCrOSActionRecorderWithHash,
     ash::switches::kEnableCrOSActionRecorder,
     ash::switches::kCrOSActionRecorderWithHash},
    {ash::switches::kCrOSActionRecorderWithoutHash,
     ash::switches::kEnableCrOSActionRecorder,
     ash::switches::kCrOSActionRecorderWithoutHash},
    {ash::switches::kCrOSActionRecorderCopyToDownloadDir,
     ash::switches::kEnableCrOSActionRecorder,
     ash::switches::kCrOSActionRecorderCopyToDownloadDir},
    {ash::switches::kCrOSActionRecorderDisabled,
     ash::switches::kEnableCrOSActionRecorder,
     ash::switches::kCrOSActionRecorderDisabled},
    {ash::switches::kCrOSActionRecorderStructuredDisabled,
     ash::switches::kEnableCrOSActionRecorder,
     ash::switches::kCrOSActionRecorderStructuredDisabled},
};
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
const FeatureEntry::Choice kWebOtpBackendChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kWebOtpBackendSmsVerification, switches::kWebOtpBackend,
     switches::kWebOtpBackendSmsVerification},
    {flag_descriptions::kWebOtpBackendUserConsent, switches::kWebOtpBackend,
     switches::kWebOtpBackendUserConsent},
    {flag_descriptions::kWebOtpBackendAuto, switches::kWebOtpBackend,
     switches::kWebOtpBackendAuto},
};

const FeatureEntry::Choice kQueryTilesCountryChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flag_descriptions::kQueryTilesCountryCodeUS,
     query_tiles::switches::kQueryTilesCountryCode, "US"},
    {flag_descriptions::kQueryTilesCountryCodeIndia,
     query_tiles::switches::kQueryTilesCountryCode, "IN"},
    {flag_descriptions::kQueryTilesCountryCodeBrazil,
     query_tiles::switches::kQueryTilesCountryCode, "BR"},
    {flag_descriptions::kQueryTilesCountryCodeNigeria,
     query_tiles::switches::kQueryTilesCountryCode, "NG"},
    {flag_descriptions::kQueryTilesCountryCodeIndonesia,
     query_tiles::switches::kQueryTilesCountryCode, "ID"},
};

#endif  // defined(OS_ANDROID)

// The choices for --enable-experimental-cookie-features. This really should
// just be a SINGLE_VALUE_TYPE, but it is misleading to have the choices be
// labeled "Disabled"/"Enabled". So instead this is made to be a
// MULTI_VALUE_TYPE with choices "Default"/"Enabled".
const FeatureEntry::Choice kEnableExperimentalCookieFeaturesChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {flags_ui::kGenericExperimentChoiceEnabled,
     switches::kEnableExperimentalCookieFeatures, ""},
};

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
const FeatureEntry::Choice kFrameThrottleFpsChoices[] = {
    {flag_descriptions::kFrameThrottleFpsDefault, "", ""},
    {flag_descriptions::kFrameThrottleFps5, ash::switches::kFrameThrottleFps,
     "5"},
    {flag_descriptions::kFrameThrottleFps10, ash::switches::kFrameThrottleFps,
     "10"},
    {flag_descriptions::kFrameThrottleFps15, ash::switches::kFrameThrottleFps,
     "15"},
    {flag_descriptions::kFrameThrottleFps20, ash::switches::kFrameThrottleFps,
     "20"},
    {flag_descriptions::kFrameThrottleFps25, ash::switches::kFrameThrottleFps,
     "25"},
    {flag_descriptions::kFrameThrottleFps30, ash::switches::kFrameThrottleFps,
     "30"}};
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

const FeatureEntry::Choice kDrawPredictedPointsChoices[] = {
    {flag_descriptions::kDrawPredictedPointsDefault, "", ""},
    {flag_descriptions::kDraw1PredictedPoint12Ms,
     switches::kDrawPredictedInkPoint, switches::kDraw1Point12Ms},
    {flag_descriptions::kDraw2PredictedPoints6Ms,
     switches::kDrawPredictedInkPoint, switches::kDraw2Points6Ms},
    {flag_descriptions::kDraw1PredictedPoint6Ms,
     switches::kDrawPredictedInkPoint, switches::kDraw1Point6Ms},
    {flag_descriptions::kDraw2PredictedPoints3Ms,
     switches::kDrawPredictedInkPoint, switches::kDraw2Points3Ms}};

#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
const FeatureEntry::Choice kForceControlFaceAeChoices[] = {
    {"Default", "", ""},
    {"Enable", media::switches::kForceControlFaceAe, "enable"},
    {"Disable", media::switches::kForceControlFaceAe, "disable"}};
#endif

#if defined(OS_ANDROID)
// The variations of --password-change-in-settings.
const FeatureEntry::FeatureParam
    kPasswordChangeInSettingsVariationWithForcedWarningForEverySite[] = {
        {password_manager::features::
             kPasswordChangeInSettingsWithForcedWarningForEverySite,
         "true"}};

<<<<<<< HEAD
const FeatureEntry::Choice kFaceRetouchOverrideChoices[] = {
    {"Default", "", ""},
    {"Enabled with relighting", media::switches::kFaceRetouchOverride,
     media::switches::kFaceRetouchForceEnabledWithRelighting},
    {"Enabled without relighting", media::switches::kFaceRetouchOverride,
     media::switches::kFaceRetouchForceEnabledWithoutRelighting},
    {"Disabled", media::switches::kFaceRetouchOverride,
     media::switches::kFaceRetouchForceDisabled}};

const FeatureEntry::Choice kCrostiniContainerChoices[] = {
    {"Default", "", ""},
    {"Buster", crostini::kCrostiniContainerFlag, "buster"},
    {"Bullseye", crostini::kCrostiniContainerFlag, "bullseye"},
    {"Bookworm", crostini::kCrostiniContainerFlag, "bookworm"},
};
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
const FeatureEntry::FeatureVariation
    kPasswordChangeInSettingsFeatureVariations[] = {
        {"Force leak warnings for every site in settings.",
         kPasswordChangeInSettingsVariationWithForcedWarningForEverySite,
         base::size(
             kPasswordChangeInSettingsVariationWithForcedWarningForEverySite),
         nullptr}};

// The variations of --password-change-support.
const FeatureEntry::FeatureParam
    kPasswordChangeVariationWithForcedDialogAfterEverySuccessfulSubmission[] = {
        {password_manager::features::
             kPasswordChangeWithForcedDialogAfterEverySuccessfulSubmission,
         "true"}};

const FeatureEntry::FeatureVariation kPasswordChangeFeatureVariations[] = {
    {"Force dialog after every successful form submission.",
     kPasswordChangeVariationWithForcedDialogAfterEverySuccessfulSubmission,
     base::size(
         kPasswordChangeVariationWithForcedDialogAfterEverySuccessfulSubmission),
     nullptr}};
#endif  // defined(OS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS_ASH)
constexpr char kAssistantBetterOnboardingInternalName[] =
    "enable-assistant-better-onboarding";
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

#if defined(OS_LINUX) || defined(OS_CHROMEOS)
const FeatureEntry::FeatureParam
    kSendWebUIJavaScriptErrorReportsVariationSendToStaging[] = {
        {features::kSendWebUIJavaScriptErrorReportsSendToProductionVariation,
         "false"}};

const FeatureEntry::FeatureVariation
    kSendWebUIJavaScriptErrorReportsVariations[] = {
        {"Send reports to staging server.",
         kSendWebUIJavaScriptErrorReportsVariationSendToStaging,
         base::size(kSendWebUIJavaScriptErrorReportsVariationSendToStaging),
         nullptr}};
#endif

#if defined(OS_ANDROID)
// The variations of --metrics-settings-android.
const FeatureEntry::FeatureParam kMetricsSettingsAndroidAlternativeOne[] = {
    {"fre", "1"}};

const FeatureEntry::FeatureParam kMetricsSettingsAndroidAlternativeTwo[] = {
    {"fre", "2"}};

const FeatureEntry::FeatureVariation kMetricsSettingsAndroidVariations[] = {
    {"Alternative FRE 1", kMetricsSettingsAndroidAlternativeOne,
     base::size(kMetricsSettingsAndroidAlternativeOne), nullptr},
    {"Alternative FRE 2", kMetricsSettingsAndroidAlternativeTwo,
     base::size(kMetricsSettingsAndroidAlternativeTwo), nullptr},
};
#endif  // defined(OS_ANDROID)

#if !defined(OS_ANDROID)
// SCT Auditing feature variations.
const FeatureEntry::FeatureParam kSCTAuditingSamplingRateNone[] = {
    {"sampling_rate", "0.0"}};
const FeatureEntry::FeatureParam kSCTAuditingSamplingRateAlternativeOne[] = {
    {"sampling_rate", "0.0001"}};
const FeatureEntry::FeatureParam kSCTAuditingSamplingRateAlternativeTwo[] = {
    {"sampling_rate", "0.001"}};

const FeatureEntry::FeatureVariation kSCTAuditingVariations[] = {
    {"Sampling rate 0%", kSCTAuditingSamplingRateNone,
     base::size(kSCTAuditingSamplingRateNone), nullptr},
    {"Sampling rate 0.01%", kSCTAuditingSamplingRateAlternativeOne,
     base::size(kSCTAuditingSamplingRateAlternativeOne), nullptr},
    {"Sampling rate 0.1%", kSCTAuditingSamplingRateAlternativeTwo,
     base::size(kSCTAuditingSamplingRateAlternativeTwo), nullptr},
};
#endif  // !defined(OS_ANDROID)

const FeatureEntry::FeatureParam kCheckOfflineCapabilityWarnOnly[] = {
    {"check_mode", "warn_only"}};
const FeatureEntry::FeatureParam kCheckOfflineCapabilityEnforce[] = {
    {"check_mode", "enforce"}};

const FeatureEntry::FeatureVariation kCheckOfflineCapabilityVariations[] = {
    {"Warn-only", kCheckOfflineCapabilityWarnOnly,
     base::size(kCheckOfflineCapabilityWarnOnly), nullptr},
    {"Enforce", kCheckOfflineCapabilityEnforce,
     base::size(kCheckOfflineCapabilityEnforce), nullptr},
};

const FeatureEntry::FeatureParam kSubresourceRedirectPublicImageHints[] = {
    {"enable_public_image_hints_based_compression", "true"},
    {"enable_subresource_server_redirect", "true"},
    {"enable_login_robots_based_compression", "false"},
};

const FeatureEntry::FeatureParam
    kSubresourceRedirectLoginRobotsBasedCompression[] = {
        {"enable_login_robots_based_compression", "true"},
        {"enable_subresource_server_redirect", "true"},
        {"enable_public_image_hints_based_compression", "false"},
};

const FeatureEntry::FeatureVariation kSubresourceRedirectVariations[] = {
    {"Public image hints based compression",
     kSubresourceRedirectPublicImageHints,
     base::size(kSubresourceRedirectPublicImageHints), nullptr},
    {"robots.txt allowed image compression in non logged-in pages",
     kSubresourceRedirectLoginRobotsBasedCompression,
     base::size(kSubresourceRedirectLoginRobotsBasedCompression), nullptr}};

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
const FeatureEntry::FeatureParam kLauncherItemSuggest_LongDelay10Mins[] = {
    {"long_delay_minutes", "10"}};
const FeatureEntry::FeatureParam kLauncherItemSuggest_LongDelay12Hours[] = {
    {"long_delay_minutes", "720"}};
const FeatureEntry::FeatureParam kLauncherItemSuggest_LongDelay24Hours[] = {
    {"long_delay_minutes", "1440"}};
const FeatureEntry::FeatureParam kLauncherItemSuggest_LongDelay36Hours[] = {
    {"long_delay_minutes", "2160"}};
const FeatureEntry::FeatureParam kLauncherItemSuggest_LongDelay48Hours[] = {
    {"long_delay_minutes", "2880"}};
const FeatureEntry::FeatureParam kLauncherItemSuggest_LongDelay60Hours[] = {
    {"long_delay_minutes", "3600"}};
const FeatureEntry::FeatureParam kLauncherItemSuggest_LongDelay72Hours[] = {
    {"long_delay_minutes", "4320"}};

const FeatureEntry::FeatureVariation kLauncherItemSuggestVariations[] = {
    {"with 10 minute long delay", kLauncherItemSuggest_LongDelay10Mins,
     std::size(kLauncherItemSuggest_LongDelay10Mins), nullptr},
    {"with 12 hour long delay", kLauncherItemSuggest_LongDelay12Hours,
     std::size(kLauncherItemSuggest_LongDelay12Hours), nullptr},
    {"with 24 hour long delay", kLauncherItemSuggest_LongDelay24Hours,
     std::size(kLauncherItemSuggest_LongDelay24Hours), nullptr},
    {"with 36 hour long delay", kLauncherItemSuggest_LongDelay36Hours,
     std::size(kLauncherItemSuggest_LongDelay36Hours), nullptr},
    {"with 48 hour long delay", kLauncherItemSuggest_LongDelay48Hours,
     std::size(kLauncherItemSuggest_LongDelay48Hours), nullptr},
    {"with 60 hour long delay", kLauncherItemSuggest_LongDelay60Hours,
     std::size(kLauncherItemSuggest_LongDelay60Hours), nullptr},
    {"with 72 hour long delay", kLauncherItemSuggest_LongDelay72Hours,
     std::size(kLauncherItemSuggest_LongDelay72Hours), nullptr}};

const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_10[] = {
    {"confidence_threshold", "10"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_20[] = {
    {"confidence_threshold", "20"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_30[] = {
    {"confidence_threshold", "30"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_40[] = {
    {"confidence_threshold", "40"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_50[] = {
    {"confidence_threshold", "50"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_60[] = {
    {"confidence_threshold", "60"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_70[] = {
    {"confidence_threshold", "70"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_80[] = {
    {"confidence_threshold", "80"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_90[] = {
    {"confidence_threshold", "90"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_100[] = {
    {"confidence_threshold", "100"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_110[] = {
    {"confidence_threshold", "110"}};
const FeatureEntry::FeatureParam kLauncherLocalImageSearchConfidence_120[] = {
    {"confidence_threshold", "120"}};

=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
const FeatureEntry::FeatureVariation
    kOmniboxRichEntitiesInLauncherVariations[] = {
        {"with linked Suggest experiment", {}, 0, "t4461027"},
};
<<<<<<< HEAD

#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_CHROMEOS)
constexpr char kWallpaperFastRefreshInternalName[] = "wallpaper-fast-refresh";
constexpr char kWallpaperGooglePhotosSharedAlbumsInternalName[] =
    "wallpaper-google-photos-shared-albums";
constexpr char kGlanceablesTimeManagementClassroomStudentViewInternalName[] =
    "glanceables-time-management-classroom-student-view";
constexpr char kGlanceablesTimeManagementTasksViewInternalName[] =
    "glanceables-time-management-tasks-view";
constexpr char kBackgroundListeningName[] = "background-listening";
constexpr char kBorealisBigGlInternalName[] = "borealis-big-gl";
constexpr char kBorealisDGPUInternalName[] = "borealis-dgpu";
constexpr char kBorealisEnableUnsupportedHardwareInternalName[] =
    "borealis-enable-unsupported-hardware";
constexpr char kBorealisForceBetaClientInternalName[] =
    "borealis-force-beta-client";
constexpr char kBorealisForceDoubleScaleInternalName[] =
    "borealis-force-double-scale";
constexpr char kBorealisLinuxModeInternalName[] = "borealis-linux-mode";
// This differs slightly from its symbol's name since "enabled" is used
// internally to refer to whether borealis is installed or not.
constexpr char kBorealisPermittedInternalName[] = "borealis-enabled";
constexpr char kBorealisProvisionInternalName[] = "borealis-provision";
constexpr char kBorealisScaleClientByDPIInternalName[] =
    "borealis-scale-client-by-dpi";
constexpr char kBorealisZinkGlDriverInternalName[] = "borealis-zink-gl-driver";
constexpr char kClipboardHistoryLongpressInternalName[] =
    "clipboard-history-longpress";
constexpr char kClipboardHistoryUrlTitlesInternalName[] =
    "clipboard-history-url-titles";
constexpr char kBluetoothUseFlossInternalName[] = "bluetooth-use-floss";
constexpr char kBluetoothUseLLPrivacyInternalName[] = "bluetooth-use-llprivacy";
constexpr char kSeaPenInternalName[] = "sea-pen";
constexpr char kAssistantIphInternalName[] = "assistant-iph";
constexpr char kGrowthCampaigns[] = "growth-campaigns";
constexpr char kGrowthCampaignsTestTag[] = "campaigns-test-tag";
constexpr char kVcTrayMicIndicatorInternalName[] = "vc-tray-mic-indicator";
constexpr char kVcTrayTitleHeaderInternalName[] = "vc-tray-title-header";
#endif  // BUILDFLAG(IS_CHROMEOS)

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kLensOverlayNoOmniboxEntryPoint[] = {
    {"omnibox-entry-point", "false"},
};
const FeatureEntry::FeatureParam kLensOverlayResponsiveOmniboxEntryPoint[] = {
    {"omnibox-entry-point", "true"},
    {"omnibox-entry-point-always-visible", "false"},
};
const FeatureEntry::FeatureParam kLensOverlayPersistentOmniboxEntryPoint[] = {
    {"omnibox-entry-point", "true"},
    {"omnibox-entry-point-always-visible", "true"},
};

const FeatureEntry::FeatureVariation kLensOverlayVariations[] = {
    {"with no omnibox entry point", kLensOverlayNoOmniboxEntryPoint,
     std::size(kLensOverlayNoOmniboxEntryPoint), nullptr},
    {"with responsive chip omnibox entry point",
     kLensOverlayResponsiveOmniboxEntryPoint,
     std::size(kLensOverlayResponsiveOmniboxEntryPoint), nullptr},
    {"with persistent icon omnibox entry point",
     kLensOverlayPersistentOmniboxEntryPoint,
     std::size(kLensOverlayPersistentOmniboxEntryPoint), nullptr},
};
#endif  // !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kContextualSearchboxWithPageContent[] = {
    {"use-pdfs-as-context", "true"},
    {"use-inner-text-as-context", "true"},
};
const FeatureEntry::FeatureParam kContextualSearchboxWithPdfPageContent[] = {
    {"use-pdfs-as-context", "true"},
};

const FeatureEntry::FeatureVariation kContextualSearchboxVariations[] = {
    {"with page content", kContextualSearchboxWithPageContent,
     std::size(kContextualSearchboxWithPageContent), nullptr},
    {"with pdf page content", kContextualSearchboxWithPdfPageContent,
     std::size(kContextualSearchboxWithPdfPageContent), nullptr},
};
#endif  // !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kLensOverlayImageContextMenuActionsCopy[] = {
    {"enable-copy-as-image", "true"},
    {"enable-save-as-image", "false"},
};

const FeatureEntry::FeatureParam kLensOverlayImageContextMenuActionsSave[] = {
    {"enable-copy-as-image", "false"},
    {"enable-save-as-image", "true"},
};

const FeatureEntry::FeatureParam
    kLensOverlayImageContextMenuActionsCopyAndSave[] = {
        {"enable-copy-as-image", "true"},
        {"enable-save-as-image", "true"},
};

const FeatureEntry::FeatureVariation
    kLensOverlayImageContextMenuActionsVariations[] = {
        {"copy as image", kLensOverlayImageContextMenuActionsCopy,
         std::size(kLensOverlayImageContextMenuActionsCopy), nullptr},
        {"save as image", kLensOverlayImageContextMenuActionsSave,
         std::size(kLensOverlayImageContextMenuActionsSave), nullptr},
        {"copy and save as image",
         kLensOverlayImageContextMenuActionsCopyAndSave,
         std::size(kLensOverlayImageContextMenuActionsCopyAndSave), nullptr},
};
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
const FeatureEntry::Choice kAlwaysEnableHdcpChoices[] = {
    {flag_descriptions::kAlwaysEnableHdcpDefault, "", ""},
    {flag_descriptions::kAlwaysEnableHdcpType0,
     ash::switches::kAlwaysEnableHdcp, "type0"},
    {flag_descriptions::kAlwaysEnableHdcpType1,
     ash::switches::kAlwaysEnableHdcp, "type1"},
};

const FeatureEntry::Choice kPrintingPpdChannelChoices[] = {
    {flags_ui::kGenericExperimentChoiceDefault, "", ""},
    {ash::switches::kPrintingPpdChannelProduction,
     ash::switches::kPrintingPpdChannel,
     ash::switches::kPrintingPpdChannelProduction},
    {ash::switches::kPrintingPpdChannelStaging,
     ash::switches::kPrintingPpdChannel,
     ash::switches::kPrintingPpdChannelStaging},
    {ash::switches::kPrintingPpdChannelDev, ash::switches::kPrintingPpdChannel,
     ash::switches::kPrintingPpdChannelDev},
    {ash::switches::kPrintingPpdChannelLocalhost,
     ash::switches::kPrintingPpdChannel,
     ash::switches::kPrintingPpdChannelLocalhost}};
#endif  // BUILDFLAG(IS_CHROMEOS)

// Feature variations for kIsolateSandboxedIframes.
#if !BUILDFLAG(IS_ANDROID)
// TODO(wjmaclean): Add FeatureParams for a per-frame grouping when support
// for it is added.
const FeatureEntry::FeatureParam kIsolateSandboxedIframesGroupingPerSite{
    "grouping", "per-site"};
const FeatureEntry::FeatureParam kIsolateSandboxedIframesGroupingPerOrigin{
    "grouping", "per-origin"};
const FeatureEntry::FeatureParam kIsolateSandboxedIframesGroupingPerDocument{
    "grouping", "per-document"};
const FeatureEntry::FeatureVariation
    kIsolateSandboxedIframesGroupingVariations[] = {
        {"with grouping by URL's site",
         &kIsolateSandboxedIframesGroupingPerSite, 1, nullptr},
        {"with grouping by URL's origin",
         &kIsolateSandboxedIframesGroupingPerOrigin, 1, nullptr},
        {"with each sandboxed frame document in its own process",
         &kIsolateSandboxedIframesGroupingPerDocument, 1, nullptr},
};
#endif  // !BUILDFLAG(IS_ANDROID)

const FeatureEntry::FeatureParam kWebRtcApmDownmixMethodAverage[] = {
    {"method", "average"}};
const FeatureEntry::FeatureParam kWebRtcApmDownmixMethodFirstChannel[] = {
    {"method", "first"}};
const FeatureEntry::FeatureVariation kWebRtcApmDownmixMethodVariations[] = {
    {"- Average all the input channels", kWebRtcApmDownmixMethodAverage,
     std::size(kWebRtcApmDownmixMethodAverage), nullptr},
    {"- Use first channel", kWebRtcApmDownmixMethodFirstChannel,
     std::size(kWebRtcApmDownmixMethodFirstChannel), nullptr}};

const FeatureEntry::FeatureParam
    kSafetyCheckUnusedSitePermissionsNoDelayParam[] = {
        {"unused-site-permissions-no-delay-for-testing", "true"}};

const FeatureEntry::FeatureParam
    kSafetyCheckUnusedSitePermissionsWithDelayParam[] = {
        {"unused-site-permissions-with-delay-for-testing", "true"}};

const FeatureEntry::FeatureVariation
    kSafetyCheckUnusedSitePermissionsVariations[] = {
        {"for testing no delay", kSafetyCheckUnusedSitePermissionsNoDelayParam,
         std::size(kSafetyCheckUnusedSitePermissionsNoDelayParam), nullptr},
        {"for testing with delay",
         kSafetyCheckUnusedSitePermissionsWithDelayParam,
         std::size(kSafetyCheckUnusedSitePermissionsWithDelayParam), nullptr},
};

const FeatureEntry::FeatureParam kSafetyHub_NoDelay[] = {
    {features::kPasswordCheckNotificationIntervalName, "0d"},
    {features::kRevokedPermissionsNotificationIntervalName, "0d"},
    {features::kNotificationPermissionsNotificationIntervalName, "0d"},
    {features::kSafeBrowsingNotificationIntervalName, "0d"}};
const FeatureEntry::FeatureParam kSafetyHub_WithDelay[] = {
    {features::kPasswordCheckNotificationIntervalName, "0d"},
    {features::kRevokedPermissionsNotificationIntervalName, "5m"},
    {features::kNotificationPermissionsNotificationIntervalName, "5m"},
    {features::kSafeBrowsingNotificationIntervalName, "5m"}};
const FeatureEntry::FeatureVariation kSafetyHubVariations[] = {
    {"for testing no delay", kSafetyHub_NoDelay, std::size(kSafetyHub_NoDelay),
     nullptr},
    {"for testing with delay", kSafetyHub_WithDelay,
     std::size(kSafetyHub_WithDelay), nullptr},
};

const FeatureEntry::FeatureParam kTPCPhaseOutFacilitatedTestingControl1[] = {
    {tpcd::experiment::kForceEligibleForTestingName, "false"},
    {tpcd::experiment::kDisable3PCookiesName, "false"},
    {features::kCookieDeprecationTestingDisableAdsAPIsName, "false"},
    {features::kCookieDeprecationLabelName, "fake_control_1.1"},
    {tpcd::experiment::kVersionName, "9990"}};
const FeatureEntry::FeatureParam kTPCPhaseOutFacilitatedTestingLabelOnly[] = {
    {tpcd::experiment::kForceEligibleForTestingName, "false"},
    {tpcd::experiment::kDisable3PCookiesName, "false"},
    {features::kCookieDeprecationTestingDisableAdsAPIsName, "false"},
    {features::kCookieDeprecationLabelName, "fake_label_only_1.1"},
    {tpcd::experiment::kVersionName, "9991"}};
const FeatureEntry::FeatureParam kTPCPhaseOutFacilitatedTestingTreatment[] = {
    {tpcd::experiment::kForceEligibleForTestingName, "false"},
    {tpcd::experiment::kDisable3PCookiesName, "true"},
    {features::kCookieDeprecationTestingDisableAdsAPIsName, "false"},
    {features::kCookieDeprecationLabelName, "fake_treatment_1.1"},
    {tpcd::experiment::kVersionName, "9992"}};
const FeatureEntry::FeatureParam kTPCPhaseOutFacilitatedTestingControl2[] = {
    {tpcd::experiment::kForceEligibleForTestingName, "false"},
    {tpcd::experiment::kDisable3PCookiesName, "true"},
    {features::kCookieDeprecationTestingDisableAdsAPIsName, "true"},
    {features::kCookieDeprecationLabelName, "fake_control_2"},
    {tpcd::experiment::kVersionName, "9993"}};
const FeatureEntry::FeatureParam kTPCPhaseOutFacilitatedTestingForceControl1[] =
    {{tpcd::experiment::kForceEligibleForTestingName, "true"},
     {tpcd::experiment::kDisable3PCookiesName, "false"},
     {features::kCookieDeprecationTestingDisableAdsAPIsName, "false"},
     {features::kCookieDeprecationLabelName, "fake_control_1.1"},
     {tpcd::experiment::kVersionName, "9994"}};
const FeatureEntry::FeatureParam
    kTPCPhaseOutFacilitatedTestingForceLabelOnly[] = {
        {tpcd::experiment::kForceEligibleForTestingName, "true"},
        {tpcd::experiment::kDisable3PCookiesName, "false"},
        {features::kCookieDeprecationTestingDisableAdsAPIsName, "false"},
        {features::kCookieDeprecationLabelName, "fake_label_only_1.1"},
        {tpcd::experiment::kVersionName, "9995"}};
const FeatureEntry::FeatureParam
    kTPCPhaseOutFacilitatedTestingForceTreatment[] = {
        {tpcd::experiment::kForceEligibleForTestingName, "true"},
        {tpcd::experiment::kDisable3PCookiesName, "true"},
        {features::kCookieDeprecationTestingDisableAdsAPIsName, "false"},
        {features::kCookieDeprecationLabelName, "fake_treatment_1.1"},
        {tpcd::experiment::kVersionName, "9996"}};
const FeatureEntry::FeatureParam kTPCPhaseOutFacilitatedTestingForceControl2[] =
    {{tpcd::experiment::kForceEligibleForTestingName, "true"},
     {tpcd::experiment::kDisable3PCookiesName, "true"},
     {features::kCookieDeprecationTestingDisableAdsAPIsName, "true"},
     {features::kCookieDeprecationLabelName, "fake_control_2"},
     {tpcd::experiment::kVersionName, "9997"}};

const FeatureEntry::FeatureVariation
    kTPCPhaseOutFacilitatedTestingVariations[] = {
        {"Control 1", kTPCPhaseOutFacilitatedTestingControl1,
         std::size(kTPCPhaseOutFacilitatedTestingControl1), nullptr},
        {"LabelOnly", kTPCPhaseOutFacilitatedTestingLabelOnly,
         std::size(kTPCPhaseOutFacilitatedTestingLabelOnly), nullptr},
        {"Treatment", kTPCPhaseOutFacilitatedTestingTreatment,
         std::size(kTPCPhaseOutFacilitatedTestingTreatment), nullptr},
        {"Control 2", kTPCPhaseOutFacilitatedTestingControl2,
         std::size(kTPCPhaseOutFacilitatedTestingControl2), nullptr},
        {"Force Control 1", kTPCPhaseOutFacilitatedTestingForceControl1,
         std::size(kTPCPhaseOutFacilitatedTestingForceControl1), nullptr},
        {"Force LabelOnly", kTPCPhaseOutFacilitatedTestingForceLabelOnly,
         std::size(kTPCPhaseOutFacilitatedTestingForceLabelOnly), nullptr},
        {"Force Treatment", kTPCPhaseOutFacilitatedTestingForceTreatment,
         std::size(kTPCPhaseOutFacilitatedTestingForceTreatment), nullptr},
        {"Force Control 2", kTPCPhaseOutFacilitatedTestingForceControl2,
         std::size(kTPCPhaseOutFacilitatedTestingForceControl2), nullptr},
};

#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kTabStateFlatBufferMigrateStaleTabs[] = {
    {"migrate_stale_tabs", "true"}};

const FeatureEntry::FeatureVariation kTabStateFlatBufferVariations[] = {
    {"Migrate Stale Tabs", kTabStateFlatBufferMigrateStaleTabs,
     std::size(kTabStateFlatBufferMigrateStaleTabs), nullptr}};
#endif

const FeatureEntry::FeatureParam
    kTpcdHeuristicsGrants_CurrentInteraction_ShortRedirect_MainFrameInitiator
        [] = {
            {content_settings::features::kTpcdReadHeuristicsGrantsName, "true"},
            {content_settings::features::
                 kTpcdWritePopupCurrentInteractionHeuristicsGrantsName,
             "30d"},
            {content_settings::features::kTpcdBackfillPopupHeuristicsGrantsName,
             "30d"},
            {content_settings::features::
                 kTpcdPopupHeuristicEnableForIframeInitiatorName,
             "none"},
            {content_settings::features::kTpcdWriteRedirectHeuristicGrantsName,
             "15m"},
            {content_settings::features::
                 kTpcdRedirectHeuristicRequireABAFlowName,
             "true"},
            {content_settings::features::
                 kTpcdRedirectHeuristicRequireCurrentInteractionName,
             "true"}};
const FeatureEntry::FeatureParam
    kTpcdHeuristicsGrants_CurrentInteraction_LongRedirect_MainFrameInitiator[] =
        {{content_settings::features::kTpcdReadHeuristicsGrantsName, "true"},
         {content_settings::features::
              kTpcdWritePopupCurrentInteractionHeuristicsGrantsName,
          "30d"},
         {content_settings::features::kTpcdBackfillPopupHeuristicsGrantsName,
          "30d"},
         {content_settings::features::
              kTpcdPopupHeuristicEnableForIframeInitiatorName,
          "none"},
         {content_settings::features::kTpcdWriteRedirectHeuristicGrantsName,
          "30d"},
         {content_settings::features::kTpcdRedirectHeuristicRequireABAFlowName,
          "true"},
         {content_settings::features::
              kTpcdRedirectHeuristicRequireCurrentInteractionName,
          "true"}};
const FeatureEntry::FeatureParam
    kTpcdHeuristicsGrants_CurrentInteraction_ShortRedirect_AllFrameInitiator[] =
        {{content_settings::features::kTpcdReadHeuristicsGrantsName, "true"},
         {content_settings::features::
              kTpcdWritePopupCurrentInteractionHeuristicsGrantsName,
          "30d"},
         {content_settings::features::kTpcdBackfillPopupHeuristicsGrantsName,
          "30d"},
         {content_settings::features::
              kTpcdPopupHeuristicEnableForIframeInitiatorName,
          "all"},
         {content_settings::features::kTpcdWriteRedirectHeuristicGrantsName,
          "15m"},
         {content_settings::features::kTpcdRedirectHeuristicRequireABAFlowName,
          "true"},
         {content_settings::features::
              kTpcdRedirectHeuristicRequireCurrentInteractionName,
          "true"}};
const FeatureEntry::FeatureParam
    kTpcdHeuristicsGrants_CurrentInteraction_LongRedirect_AllFrameInitiator[] =
        {{content_settings::features::kTpcdReadHeuristicsGrantsName, "true"},
         {content_settings::features::
              kTpcdWritePopupCurrentInteractionHeuristicsGrantsName,
          "30d"},
         {content_settings::features::kTpcdBackfillPopupHeuristicsGrantsName,
          "30d"},
         {content_settings::features::
              kTpcdPopupHeuristicEnableForIframeInitiatorName,
          "all"},
         {content_settings::features::kTpcdWriteRedirectHeuristicGrantsName,
          "30d"},
         {content_settings::features::kTpcdRedirectHeuristicRequireABAFlowName,
          "true"},
         {content_settings::features::
              kTpcdRedirectHeuristicRequireCurrentInteractionName,
          "true"}};

const FeatureEntry::FeatureVariation kTpcdHeuristicsGrantsVariations[] = {
    {"CurrentInteraction_ShortRedirect_MainFrameInitiator",
     kTpcdHeuristicsGrants_CurrentInteraction_ShortRedirect_MainFrameInitiator,
     std::size(
         kTpcdHeuristicsGrants_CurrentInteraction_ShortRedirect_MainFrameInitiator),
     nullptr},
    {"CurrentInteraction_LongRedirect_MainFrameInitiator",
     kTpcdHeuristicsGrants_CurrentInteraction_LongRedirect_MainFrameInitiator,
     std::size(
         kTpcdHeuristicsGrants_CurrentInteraction_LongRedirect_MainFrameInitiator),
     nullptr},
    {"CurrentInteraction_ShortRedirect_AllFrameInitiator",
     kTpcdHeuristicsGrants_CurrentInteraction_ShortRedirect_AllFrameInitiator,
     std::size(
         kTpcdHeuristicsGrants_CurrentInteraction_ShortRedirect_AllFrameInitiator),
     nullptr},
    {"CurrentInteraction_LongRedirect_AllFrameInitiator",
     kTpcdHeuristicsGrants_CurrentInteraction_LongRedirect_AllFrameInitiator,
     std::size(
         kTpcdHeuristicsGrants_CurrentInteraction_LongRedirect_AllFrameInitiator),
     nullptr}};

#if BUILDFLAG(IS_CHROMEOS)
const FeatureEntry::FeatureParam kVcInferenceBackendAuto[] = {
    {"inference_backend", "AUTO"},
};

const FeatureEntry::FeatureParam kVcInferenceBackendGpu[] = {
    {"inference_backend", "GPU"},
};

const FeatureEntry::FeatureParam kVcInferenceBackendNpu[] = {
    {"inference_backend", "NPU"},
};

const FeatureEntry::FeatureVariation kVcRelightingInferenceBackendVariations[] =
    {{"AUTO", kVcInferenceBackendAuto, std::size(kVcInferenceBackendAuto),
      nullptr},
     {"GPU", kVcInferenceBackendGpu, std::size(kVcInferenceBackendGpu),
      nullptr},
     {"NPU", kVcInferenceBackendNpu, std::size(kVcInferenceBackendNpu),
      nullptr}};

const FeatureEntry::FeatureVariation kVcRetouchInferenceBackendVariations[] = {
    {"AUTO", kVcInferenceBackendAuto, std::size(kVcInferenceBackendAuto),
     nullptr},
    {"GPU", kVcInferenceBackendGpu, std::size(kVcInferenceBackendGpu), nullptr},
    {"NPU", kVcInferenceBackendNpu, std::size(kVcInferenceBackendNpu),
     nullptr}};

const FeatureEntry::FeatureVariation
    kVcSegmentationInferenceBackendVariations[] = {
        {"AUTO", kVcInferenceBackendAuto, std::size(kVcInferenceBackendAuto),
         nullptr},
        {"GPU", kVcInferenceBackendGpu, std::size(kVcInferenceBackendGpu),
         nullptr},
        {"NPU", kVcInferenceBackendNpu, std::size(kVcInferenceBackendNpu),
         nullptr}};

const FeatureEntry::FeatureParam kVcSegmentationModelHighResolution[] = {
    {"segmentation_model", "high_resolution"},
};

const FeatureEntry::FeatureParam kVcSegmentationModelLowerResolution[] = {
    {"segmentation_model", "lower_resolution"},
};

const FeatureEntry::FeatureVariation kVcSegmentationModelVariations[] = {
    {"High resolution model", kVcSegmentationModelHighResolution,
     std::size(kVcSegmentationModelHighResolution), nullptr},
    {"Lower resolution model", kVcSegmentationModelLowerResolution,
     std::size(kVcSegmentationModelLowerResolution), nullptr},
};

const FeatureEntry::FeatureParam kVcLightIntensity10[] = {
    {"light_intensity", "1.0"},
};

const FeatureEntry::FeatureParam kVcLightIntensity13[] = {
    {"light_intensity", "1.3"},
};

const FeatureEntry::FeatureParam kVcLightIntensity15[] = {
    {"light_intensity", "1.5"},
};

const FeatureEntry::FeatureParam kVcLightIntensity17[] = {
    {"light_intensity", "1.7"},
};

const FeatureEntry::FeatureParam kVcLightIntensity18[] = {
    {"light_intensity", "1.8"},
};

const FeatureEntry::FeatureParam kVcLightIntensity20[] = {
    {"light_intensity", "2.0"},
};

const FeatureEntry::FeatureVariation kVcLightIntensityVariations[] = {
    {"1.0", kVcLightIntensity10, std::size(kVcLightIntensity10), nullptr},
    {"1.3", kVcLightIntensity13, std::size(kVcLightIntensity13), nullptr},
    {"1.5", kVcLightIntensity15, std::size(kVcLightIntensity15), nullptr},
    {"1.7", kVcLightIntensity17, std::size(kVcLightIntensity17), nullptr},
    {"1.8", kVcLightIntensity18, std::size(kVcLightIntensity18), nullptr},
    {"2.0", kVcLightIntensity20, std::size(kVcLightIntensity20), nullptr},
};

const FeatureEntry::FeatureParam
    kCrOSLateBootMissiveDisableStorageDegradation[] = {
        {"controlled_degradation", "false"}};
const FeatureEntry::FeatureParam
    kCrOSLateBootMissiveEnableStorageDegradation[] = {
        {"controlled_degradation", "true"}};
const FeatureEntry::FeatureParam kCrOSLateBootMissiveDisableLegacyStorage[] = {
    {"legacy_storage_enabled",
     "UNDEFINED_PRIORITY"}};  // All others are multi-generation action state.
const FeatureEntry::FeatureParam kCrOSLateBootMissiveEnableLegacyStorage[] = {
    {"legacy_storage_enabled",
     "SECURITY,"
     "IMMEDIATE,"
     "FAST_BATCH,"
     "SLOW_BATCH,"
     "BACKGROUND_BATCH,"
     "MANUAL_BATCH,"
     "MANUAL_BATCH_LACROS,"}};
const FeatureEntry::FeatureParam kCrOSLateBootMissivePartialLegacyStorage[] = {
    {"legacy_storage_enabled",
     "SECURITY,"
     "IMMEDIATE,"}};
const FeatureEntry::FeatureParam kCrOSLateBootMissiveSecurityLegacyStorage[] = {
    {"legacy_storage_enabled", "SECURITY,"}};

const FeatureEntry::FeatureVariation
    kCrOSLateBootMissiveStorageDefaultVariations[] = {
        {"Enable storage degradation",
         kCrOSLateBootMissiveEnableStorageDegradation,
         std::size(kCrOSLateBootMissiveEnableStorageDegradation), nullptr},
        {"Disable storage degradation",
         kCrOSLateBootMissiveDisableStorageDegradation,
         std::size(kCrOSLateBootMissiveDisableStorageDegradation), nullptr},
        {"Enable all queues legacy", kCrOSLateBootMissiveEnableLegacyStorage,
         std::size(kCrOSLateBootMissiveEnableLegacyStorage), nullptr},
        {"Disable all queues legacy", kCrOSLateBootMissiveDisableLegacyStorage,
         std::size(kCrOSLateBootMissiveDisableLegacyStorage), nullptr},
        {"Enable SECURITY and IMMEDIATE queues legacy only",
         kCrOSLateBootMissivePartialLegacyStorage,
         std::size(kCrOSLateBootMissivePartialLegacyStorage), nullptr},
        {"Enable SECURITY queues legacy only",
         kCrOSLateBootMissiveSecurityLegacyStorage,
         std::size(kCrOSLateBootMissiveSecurityLegacyStorage), nullptr},
};
#endif  // BUILDFLAG(IS_CHROMEOS)

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::Choice kCastMirroringTargetPlayoutDelayChoices[] = {
    {flag_descriptions::kCastMirroringTargetPlayoutDelayDefault, "", ""},
    {flag_descriptions::kCastMirroringTargetPlayoutDelay100ms,
     switches::kCastMirroringTargetPlayoutDelay, "100"},
    {flag_descriptions::kCastMirroringTargetPlayoutDelay150ms,
     switches::kCastMirroringTargetPlayoutDelay, "150"},
    {flag_descriptions::kCastMirroringTargetPlayoutDelay250ms,
     switches::kCastMirroringTargetPlayoutDelay, "250"},
    {flag_descriptions::kCastMirroringTargetPlayoutDelay300ms,
     switches::kCastMirroringTargetPlayoutDelay, "300"},
    {flag_descriptions::kCastMirroringTargetPlayoutDelay350ms,
     switches::kCastMirroringTargetPlayoutDelay, "350"},
    {flag_descriptions::kCastMirroringTargetPlayoutDelay400ms,
     switches::kCastMirroringTargetPlayoutDelay, "400"}};

#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)
const FeatureEntry::FeatureParam
    kEnableBoundSessionCredentialsWithMultiSessionSupport[] = {
        {"exclusive-registration-path", ""}};

const FeatureEntry::FeatureVariation
    kEnableBoundSessionCredentialsVariations[] = {
        {"with multi-session",
         kEnableBoundSessionCredentialsWithMultiSessionSupport,
         std::size(kEnableBoundSessionCredentialsWithMultiSessionSupport),
         nullptr}};
#endif  // BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)

#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kWebAuthnAndroidCredManGpmInCredManParam = {
    device::kWebAuthnAndroidGpmInCredMan.name, "true"};
const FeatureEntry::FeatureParam kWebAuthnAndroidCredManGpmNotInCredManParam = {
    device::kWebAuthnAndroidGpmInCredMan.name, "false"};
const FeatureEntry::FeatureVariation kWebAuthnAndroidCredManVariations[] = {
    {"for Google Password Manager and 3rd party passkeys",
     &kWebAuthnAndroidCredManGpmInCredManParam, 1, nullptr},
    {"for 3rd party passkeys", &kWebAuthnAndroidCredManGpmNotInCredManParam, 1,
     nullptr}};

const FeatureEntry::FeatureParam kEdgeToEdgeBottomChinDebugFeatureParams[] = {
    {chrome::android::kEdgeToEdgeBottomChinDebugParam.name, "true"}};
const FeatureEntry::FeatureVariation kEdgeToEdgeBottomChinVariations[] = {
    {"debug", kEdgeToEdgeBottomChinDebugFeatureParams,
     std::size(kEdgeToEdgeBottomChinDebugFeatureParams), nullptr},
};

const FeatureEntry::FeatureParam kEdgeToEdgeEverywhereDebugFeatureParams[] = {
    {"e2e_everywhere_debug", "true"}};
const FeatureEntry::FeatureVariation kEdgeToEdgeEverywhereVariations[] = {
    {"debug", kEdgeToEdgeEverywhereDebugFeatureParams,
     std::size(kEdgeToEdgeEverywhereDebugFeatureParams), nullptr},
};

const FeatureEntry::FeatureParam kBottomBrowserControlsRefactorParams[] = {
    {"disable_bottom_controls_stacker_y_offset", "false"}};
const FeatureEntry::FeatureVariation
    kBottomBrowserControlsRefactorVariations[] = {
        {"Dispatch yOffset", kBottomBrowserControlsRefactorParams,
         std::size(kBottomBrowserControlsRefactorParams), nullptr},
};

#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN) || \
    BUILDFLAG(IS_CHROMEOS)
const flags_ui::FeatureEntry::FeatureParam kPwaNavigationCapturingDefaultOn[] =
    {{"link_capturing_state", "on_by_default"}};
const flags_ui::FeatureEntry::FeatureParam kPwaNavigationCapturingDefaultOff[] =
    {{"link_capturing_state", "off_by_default"}};
const flags_ui::FeatureEntry::FeatureParam
    kPwaNavigationCapturingReimplDefaultOn[] = {
        {"link_capturing_state", "reimpl_default_on"}};
const flags_ui::FeatureEntry::FeatureParam
    kPwaNavigationCapturingReimplDefaultOff[] = {
        {"link_capturing_state", "reimpl_default_off"}};
const flags_ui::FeatureEntry::FeatureParam
    kPwaNavigationCapturingReimplOnViaClientMode[] = {
        {"link_capturing_state", "reimpl_on_via_client_mode"}};
const flags_ui::FeatureEntry::FeatureVariation
    kPwaNavigationCapturingVariations[] = {
        {"V1, On by default", kPwaNavigationCapturingDefaultOn,
         std::size(kPwaNavigationCapturingDefaultOn), nullptr},
        {"V1, Off by default", kPwaNavigationCapturingDefaultOff,
         std::size(kPwaNavigationCapturingDefaultOff), nullptr},
        {"V2, On by default", kPwaNavigationCapturingReimplDefaultOn,
         std::size(kPwaNavigationCapturingReimplDefaultOn), nullptr},
        {"V2, Off by default", kPwaNavigationCapturingReimplDefaultOff,
         std::size(kPwaNavigationCapturingReimplDefaultOff), nullptr},
        {"V2, On by app client_mode",
         kPwaNavigationCapturingReimplOnViaClientMode,
         std::size(kPwaNavigationCapturingReimplOnViaClientMode), nullptr}};
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN) ||
        // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)

// UnoPhase2FollowUp flags.
const char kFastFollowFeatures[] =
    "UnoForAuto,"
    "UnoPhase2FollowUp,"
    "UseHostedDomainForManagementCheckOnSignin";

const FeatureEntry::Choice kReplaceSyncPromosWithSignInPromosChoices[] = {
    {"Default", "", ""},
    {"Follow-ups disabled", "disable-features", kFastFollowFeatures},
    {"Follow-ups enabled", "enable-features", kFastFollowFeatures},
};
#endif  // BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kLinkPreviewTriggerTypeAltClick[] = {
    {"trigger_type", "alt_click"}};
const FeatureEntry::FeatureParam kLinkPreviewTriggerTypeAltHover[] = {
    {"trigger_type", "alt_hover"}};
const FeatureEntry::FeatureParam kLinkPreviewTriggerTypeLongPress[] = {
    {"trigger_type", "long_press"}};

const FeatureEntry::FeatureVariation kLinkPreviewTriggerTypeVariations[] = {
    {"Alt + Click", kLinkPreviewTriggerTypeAltClick,
     std::size(kLinkPreviewTriggerTypeAltClick), nullptr},
    {"Alt + Hover", kLinkPreviewTriggerTypeAltHover,
     std::size(kLinkPreviewTriggerTypeAltHover), nullptr},
    {"Long Press", kLinkPreviewTriggerTypeLongPress,
     std::size(kLinkPreviewTriggerTypeLongPress), nullptr}};
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
inline constexpr flags_ui::FeatureEntry::FeatureParam
    kAutofillVirtualViewStructureAndroidSkipCompatibilityCheck = {
        autofill::features::
            kAutofillVirtualViewStructureAndroidSkipsCompatibilityCheck.name,
        "skip_all_checks"};
inline constexpr flags_ui::FeatureEntry::FeatureParam
    kAutofillVirtualViewStructureAndroidOnlySkipAwgCheck = {
        autofill::features::
            kAutofillVirtualViewStructureAndroidSkipsCompatibilityCheck.name,
        "only_skip_awg_check"};

inline constexpr flags_ui::FeatureEntry::FeatureVariation
    kAutofillVirtualViewStructureVariation[] = {
        {" without any compatibility check",
         &kAutofillVirtualViewStructureAndroidSkipCompatibilityCheck, 1,
         nullptr},
        {" without AwG restriction",
         &kAutofillVirtualViewStructureAndroidOnlySkipAwgCheck, 1, nullptr}};

#endif  // BUILDFLAG(IS_ANDROID)

const FeatureEntry::FeatureParam
    kPrerender2WarmUpCompositorTriggerPointDidCommitLoad[] = {
        {"trigger_point", "did_commit_load"}};
const FeatureEntry::FeatureParam
    kPrerender2WarmUpCompositorTriggerPointDidDispatchDOMContentLoadedEvent[] =
        {{"trigger_point", "did_dispatch_dom_content_loaded_event"}};
const FeatureEntry::FeatureParam
    kPrerender2WarmUpCompositorTriggerPointDidFinishLoad[] = {
        {"trigger_point", "did_finish_load"}};
const FeatureEntry::FeatureVariation
    kPrerender2WarmUpCompositorTriggerPointVariations[] = {
        {"(on DidCommitLoad)",
         kPrerender2WarmUpCompositorTriggerPointDidCommitLoad,
         std::size(kPrerender2WarmUpCompositorTriggerPointDidCommitLoad),
         nullptr},
        {"(on DOMContentLoaded)",
         kPrerender2WarmUpCompositorTriggerPointDidDispatchDOMContentLoadedEvent,
         std::size(
             kPrerender2WarmUpCompositorTriggerPointDidDispatchDOMContentLoadedEvent),
         nullptr},
        {"(on DidFinishLoad)",
         kPrerender2WarmUpCompositorTriggerPointDidFinishLoad,
         std::size(kPrerender2WarmUpCompositorTriggerPointDidFinishLoad),
         nullptr},
};

#if BUILDFLAG(ENABLE_COMPOSE)
// Vatiations of the Compose proactive nudge.
const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactNoFocusDelay_10[] = {
        {"proactive_nudge_focus_delay_milliseconds", "0"},
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "10"}};

const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactNoFocusDelay_10_5[] = {
        {"proactive_nudge_focus_delay_milliseconds", "0"},
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "10"},
        {"nudge_field_change_event_max", "5"}};

const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactNoFocusDelay_10_10[] = {
        {"proactive_nudge_focus_delay_milliseconds", "0"},
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "10"},
        {"nudge_field_change_event_max", "10"}};

const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactNoFocusDelay_50[] = {
        {"proactive_nudge_focus_delay_milliseconds", "0"},
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "50"}};

const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactLongFocusDelay_10[] = {
        {"proactive_nudge_focus_delay_milliseconds", "60000"},  // one minute
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "10"}};

const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactLongFocusDelay_50[] = {
        {"proactive_nudge_focus_delay_milliseconds", "60000"},  // one minute
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "50"}};

const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactLongTextDelay_10[] = {
        {"proactive_nudge_focus_delay_milliseconds", "0"},
        {"proactive_nudge_text_settled_delay_milliseconds", "10000"},
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "10"}};

const FeatureEntry::FeatureParam
    kComposeProactiveNudge_CompactLongTextDelay_50[] = {
        {"proactive_nudge_focus_delay_milliseconds", "0"},
        {"proactive_nudge_text_settled_delay_milliseconds", "10000"},
        {"proactive_nudge_compact_ui", "true"},
        {"proactive_nudge_text_change_count", "50"}};

const FeatureEntry::FeatureParam kComposeProactiveNudge_LargeNoFocusDelay_10[] =
    {{"proactive_nudge_focus_delay_milliseconds", "0"},
     {"proactive_nudge_compact_ui", "false"},
     {"proactive_nudge_text_change_count", "10"}};

const FeatureEntry::FeatureParam kComposeProactiveNudge_LargeNoFocusDelay_50[] =
    {{"proactive_nudge_focus_delay_milliseconds", "0"},
     {"proactive_nudge_compact_ui", "false"},
     {"proactive_nudge_text_change_count", "50"}};

const FeatureEntry::FeatureVariation kComposeProactiveNudgeVariations[] = {
    {"Compact UI - No focus delay - Show (10 edits)",
     kComposeProactiveNudge_CompactNoFocusDelay_10,
     std::size(kComposeProactiveNudge_CompactNoFocusDelay_10), nullptr},
    {"Compact UI - No focus delay - Show (10 edits) - Dismiss (5 edits)",
     kComposeProactiveNudge_CompactNoFocusDelay_10_5,
     std::size(kComposeProactiveNudge_CompactNoFocusDelay_10_5), nullptr},
    {"Compact UI - No focus delay - Show (10 edits) - Dismiss (10 edits)",
     kComposeProactiveNudge_CompactNoFocusDelay_10_10,
     std::size(kComposeProactiveNudge_CompactNoFocusDelay_10_10), nullptr},
    {"Compact UI - No focus delay - Show (50 edits)",
     kComposeProactiveNudge_CompactNoFocusDelay_50,
     std::size(kComposeProactiveNudge_CompactNoFocusDelay_50), nullptr},
    {"Compact UI - Long focus delay - Show (10 edits)",
     kComposeProactiveNudge_CompactLongFocusDelay_10,
     std::size(kComposeProactiveNudge_CompactLongFocusDelay_10), nullptr},
    {"Compact UI - Long focus delay - Show (50 edits)",
     kComposeProactiveNudge_CompactLongFocusDelay_50,
     std::size(kComposeProactiveNudge_CompactLongFocusDelay_50), nullptr},

    {"Compact UI - No Focus delay - Show (10 edits) - long text delay",
     kComposeProactiveNudge_CompactLongTextDelay_10,
     std::size(kComposeProactiveNudge_CompactLongTextDelay_10), nullptr},
    {"Compact UI - No Focus delay - Show (50 edits) - long text delay",
     kComposeProactiveNudge_CompactLongTextDelay_50,
     std::size(kComposeProactiveNudge_CompactLongTextDelay_50), nullptr},
    {"Large UI - No focus delay - Show (10 edits)",
     kComposeProactiveNudge_LargeNoFocusDelay_10,
     std::size(kComposeProactiveNudge_LargeNoFocusDelay_10), nullptr},
    {"Large UI - Long focus delay - Show (50 edits)",
     kComposeProactiveNudge_LargeNoFocusDelay_50,
     std::size(kComposeProactiveNudge_LargeNoFocusDelay_50), nullptr}};

// Variations of the Compose selection nudge.
const FeatureEntry::FeatureParam kComposeSelectionNudge_1[] = {
    {"selection_nudge_length", "1"}};

const FeatureEntry::FeatureParam kComposeSelectionNudge_15[] = {
    {"selection_nudge_length", "15"}};

const FeatureEntry::FeatureParam kComposeSelectionNudge_30[] = {
    {"selection_nudge_length", "30"}};

const FeatureEntry::FeatureParam kComposeSelectionNudge_30_1s[] = {
    {"selection_nudge_length", "30"},
    {"selection_nudge_delay_milliseconds", "1000"}};

const FeatureEntry::FeatureParam kComposeSelectionNudge_30_2s[] = {
    {"selection_nudge_length", "30"},
    {"selection_nudge_delay_milliseconds", "2000"}};

const FeatureEntry::FeatureParam kComposeSelectionNudge_50[] = {
    {"selection_nudge_length", "50"}};

const FeatureEntry::FeatureParam kComposeSelectionNudge_100[] = {
    {"selection_nudge_length", "100"}};

const FeatureEntry::FeatureVariation kComposeSelectionNudgeVariations[] = {
    {"1 Char", kComposeSelectionNudge_1, std::size(kComposeSelectionNudge_1),
     nullptr},
    {"15 Char", kComposeSelectionNudge_15, std::size(kComposeSelectionNudge_15),
     nullptr},
    {"30 Char", kComposeSelectionNudge_30, std::size(kComposeSelectionNudge_30),
     nullptr},
    {"50 Char", kComposeSelectionNudge_50, std::size(kComposeSelectionNudge_50),
     nullptr},
    {"100 Char", kComposeSelectionNudge_100,
     std::size(kComposeSelectionNudge_100), nullptr},
    {"30 Char - 1sec", kComposeSelectionNudge_30_1s,
     std::size(kComposeSelectionNudge_30_1s), nullptr},
    {"30 char - 2sec", kComposeSelectionNudge_30_2s,
     std::size(kComposeSelectionNudge_30_2s), nullptr}};
#endif  // ENABLE_COMPOSE

#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
const FeatureEntry::FeatureParam kLocationProviderManagerModeNetworkOnly[] = {
    {"LocationProviderManagerMode", "NetworkOnly"}};
const FeatureEntry::FeatureParam kLocationProviderManagerModePlatformOnly[] = {
    {"LocationProviderManagerMode", "PlatformOnly"}};
const FeatureEntry::FeatureParam kLocationProviderManagerModeHybridPlatform[] =
    {{"LocationProviderManagerMode", "HybridPlatform"}};
const FeatureEntry::FeatureParam kLocationProviderManagerModeHybridPlatform2[] =
    {{"LocationProviderManagerMode", "HybridPlatform2"}};

const FeatureEntry::FeatureVariation kLocationProviderManagerVariations[] = {
    {"Network only", kLocationProviderManagerModeNetworkOnly,
     std::size(kLocationProviderManagerModeNetworkOnly), nullptr},
    {"Platform only", kLocationProviderManagerModePlatformOnly,
     std::size(kLocationProviderManagerModePlatformOnly), nullptr},
    {"Wi-Fi fallback", kLocationProviderManagerModeHybridPlatform,
     std::size(kLocationProviderManagerModeHybridPlatform), nullptr},
    {"Fallback on error", kLocationProviderManagerModeHybridPlatform2,
     std::size(kLocationProviderManagerModeHybridPlatform2), nullptr}};
#endif  // BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kWebAuthnEnclaveAuthenticatorEnabledParam = {
    device::kWebAuthnGpmPinFeatureParameterName, "true"};
const FeatureEntry::FeatureVariation kWebAuthnEnclaveAuthenticatorVariations[] =
    {{"with GPM PIN enabled", &kWebAuthnEnclaveAuthenticatorEnabledParam, 1,
      nullptr}};
#endif

const FeatureEntry::FeatureParam kVisitedURLRankingDomainDeduplicationParam[] =
    {{"url_deduplication_include_title", "false"}};

const FeatureEntry::FeatureParam
    kVisitedURLRankingDomainDeduplicationIncludeQueryParam[] = {
        {"url_deduplication_include_title", "false"},
        {"url_deduplication_fallback", "false"}};

const FeatureEntry::FeatureParam
    kVisitedURLRankingDomainDeduplicationIncludePathQueryParam[] = {
        {"url_deduplication_include_title", "false"},
        {"url_deduplication_clear_path", "false"},
        {"url_deduplication_fallback", "false"}};

const FeatureEntry::FeatureVariation
    kVisitedURLRankingDomainDeduplicationVariations[] = {
        {"- Domain Deduplication", kVisitedURLRankingDomainDeduplicationParam,
         std::size(kVisitedURLRankingDomainDeduplicationParam), nullptr},
        {"- Domain Deduplication - Include Query",
         kVisitedURLRankingDomainDeduplicationIncludeQueryParam,
         std::size(kVisitedURLRankingDomainDeduplicationIncludeQueryParam),
         nullptr},
        {"- Domain Deduplication - Include Path and Query",
         kVisitedURLRankingDomainDeduplicationIncludePathQueryParam,
         std::size(kVisitedURLRankingDomainDeduplicationIncludePathQueryParam),
         nullptr}};

const FeatureEntry::FeatureParam
    kDeferRendererTasksAfterInputMinimalTypesPolicyParam[] = {
        {blink::features::kDeferRendererTasksAfterInputPolicyParamName,
         blink::features::kDeferRendererTasksAfterInputMinimalTypesPolicyName}};
const FeatureEntry::FeatureParam
    kDeferRendererTasksAfterInputNonUserBlockingDeferrableTypesPolicyParam[] = {
        {blink::features::kDeferRendererTasksAfterInputPolicyParamName,
         blink::features::
             kDeferRendererTasksAfterInputNonUserBlockingDeferrableTypesPolicyName}};
const FeatureEntry::FeatureParam
    kDeferRendererTasksAfterInputAllDeferrableTypesPolicyParam[] = {
        {blink::features::kDeferRendererTasksAfterInputPolicyParamName,
         blink::features::
             kDeferRendererTasksAfterInputAllDeferrableTypesPolicyName}};
const FeatureEntry::FeatureParam
    kDeferRendererTasksAfterInputNonUserBlockingTypesPolicyParam[] = {
        {blink::features::kDeferRendererTasksAfterInputPolicyParamName,
         blink::features::
             kDeferRendererTasksAfterInputNonUserBlockingTypesPolicyName}};
const FeatureEntry::FeatureParam
    kDeferRendererTasksAfterInputAllTypesPolicyParam[] = {
        {blink::features::kDeferRendererTasksAfterInputPolicyParamName,
         blink::features::kDeferRendererTasksAfterInputAllTypesPolicyName}};

const FeatureEntry::FeatureVariation kDeferRendererTasksAfterInputVariations[] = {
    {"with a minimal subset of tasks types",
     kDeferRendererTasksAfterInputMinimalTypesPolicyParam,
     std::size(kDeferRendererTasksAfterInputMinimalTypesPolicyParam), nullptr},
    {"with existing non-user-blocking 'deferrable' task types",
     kDeferRendererTasksAfterInputNonUserBlockingDeferrableTypesPolicyParam,
     std::size(
         kDeferRendererTasksAfterInputNonUserBlockingDeferrableTypesPolicyParam),
     nullptr},
    {"with non-user-blocking task types",
     kDeferRendererTasksAfterInputNonUserBlockingTypesPolicyParam,
     std::size(kDeferRendererTasksAfterInputNonUserBlockingTypesPolicyParam),
     nullptr},
    {"with all existing 'deferrable' task types",
     kDeferRendererTasksAfterInputAllDeferrableTypesPolicyParam,
     std::size(kDeferRendererTasksAfterInputAllDeferrableTypesPolicyParam),
     nullptr},
    {"with all task types", kDeferRendererTasksAfterInputAllTypesPolicyParam,
     std::size(kDeferRendererTasksAfterInputAllTypesPolicyParam), nullptr}};

const FeatureEntry::FeatureParam
    kThreadedScrollPreventRenderingStarvation_66ms[] = {{"threshold_ms", "66"}};
const FeatureEntry::FeatureParam
    kThreadedScrollPreventRenderingStarvation_100ms[] = {
        {"threshold_ms", "100"}};
const FeatureEntry::FeatureParam
    kThreadedScrollPreventRenderingStarvation_200ms[] = {
        {"threshold_ms", "200"}};
const FeatureEntry::FeatureParam
    kThreadedScrollPreventRenderingStarvation_333ms[] = {
        {"threshold_ms", "333"}};
const FeatureEntry::FeatureVariation
    kThreadedScrollPreventRenderingStarvationVariations[] = {
        {"with a 66ms threshold",
         kThreadedScrollPreventRenderingStarvation_66ms,
         std::size(kThreadedScrollPreventRenderingStarvation_66ms), nullptr},
        {"with a 100ms threshold",
         kThreadedScrollPreventRenderingStarvation_100ms,
         std::size(kThreadedScrollPreventRenderingStarvation_100ms), nullptr},
        {"with a 200ms threshold",
         kThreadedScrollPreventRenderingStarvation_200ms,
         std::size(kThreadedScrollPreventRenderingStarvation_200ms), nullptr},
        {"with a 333ms threshold",
         kThreadedScrollPreventRenderingStarvation_333ms,
         std::size(kThreadedScrollPreventRenderingStarvation_333ms), nullptr}};

// LINT.IfChange(AutofillUploadCardRequestTimeouts)
const FeatureEntry::FeatureParam
    kAutofillUploadCardRequestTimeout_6Point5Seconds[] = {
        {"autofill_upload_card_request_timeout_milliseconds", "6500"}};
const FeatureEntry::FeatureParam kAutofillUploadCardRequestTimeout_7Seconds[] =
    {{"autofill_upload_card_request_timeout_milliseconds", "7000"}};
const FeatureEntry::FeatureParam kAutofillUploadCardRequestTimeout_9Seconds[] =
    {{"autofill_upload_card_request_timeout_milliseconds", "9000"}};
const FeatureEntry::FeatureVariation
    kAutofillUploadCardRequestTimeoutOptions[] = {
        {"6.5 seconds", kAutofillUploadCardRequestTimeout_6Point5Seconds,
         std::size(kAutofillUploadCardRequestTimeout_6Point5Seconds), nullptr},
        {"7 seconds", kAutofillUploadCardRequestTimeout_7Seconds,
         std::size(kAutofillUploadCardRequestTimeout_7Seconds), nullptr},
        {"9 seconds", kAutofillUploadCardRequestTimeout_9Seconds,
         std::size(kAutofillUploadCardRequestTimeout_9Seconds), nullptr}};
// LINT.ThenChange(//ios/chrome/browser/flags/about_flags.mm:AutofillUploadCardRequestTimeouts)

// LINT.IfChange(AutofillVcnEnrollRequestTimeouts)
const FeatureEntry::FeatureParam kAutofillVcnEnrollRequestTimeout_5Seconds[] = {
    {"autofill_vcn_enroll_request_timeout_milliseconds", "5000"}};
const FeatureEntry::FeatureParam
    kAutofillVcnEnrollRequestTimeout_7Point5Seconds[] = {
        {"autofill_vcn_enroll_request_timeout_milliseconds", "7500"}};
const FeatureEntry::FeatureParam kAutofillVcnEnrollRequestTimeout_10Seconds[] =
    {{"autofill_vcn_enroll_request_timeout_milliseconds", "10000"}};
const FeatureEntry::FeatureVariation kAutofillVcnEnrollRequestTimeoutOptions[] =
    {{"5 seconds", kAutofillVcnEnrollRequestTimeout_5Seconds,
      std::size(kAutofillVcnEnrollRequestTimeout_5Seconds), nullptr},
     {"7.5 seconds", kAutofillVcnEnrollRequestTimeout_7Point5Seconds,
      std::size(kAutofillVcnEnrollRequestTimeout_7Point5Seconds), nullptr},
     {"10 seconds", kAutofillVcnEnrollRequestTimeout_10Seconds,
      std::size(kAutofillVcnEnrollRequestTimeout_10Seconds), nullptr}};
// LINT.ThenChange(//ios/chrome/browser/flags/about_flags.mm:AutofillVcnEnrollRequestTimeouts)

const FeatureEntry::FeatureParam
    kAutofillImprovedLabelsWithoutMainTextChanges[] = {
        {"autofill_improved_labels_without_main_text_changes", "true"},
        {"autofill_improved_labels_with_differentiating_labels_in_front",
         "false"}};

const FeatureEntry::FeatureParam
    kAutofillImprovedLabelsWithDifferentiatingLabelsInFront[] = {
        {"autofill_improved_labels_without_main_text_changes", "false"},
        {"autofill_improved_labels_with_differentiating_labels_in_front",
         "true"}};

const FeatureEntry::FeatureVariation kAutofillImprovedLabelsVariations[] = {
    {"without main text changes", kAutofillImprovedLabelsWithoutMainTextChanges,
     std::size(kAutofillImprovedLabelsWithoutMainTextChanges), nullptr},
    {"with differentiating labels in front",
     kAutofillImprovedLabelsWithDifferentiatingLabelsInFront,
     std::size(kAutofillImprovedLabelsWithDifferentiatingLabelsInFront),
     nullptr},
};

#if BUILDFLAG(ENABLE_EXTENSIONS)
const FeatureEntry::FeatureParam
    kExtensionTelemetryEnterpriseReportingIntervalSeconds_20Seconds[] = {
        {"EnterpriseReportingIntervalSeconds", "20"}};
const FeatureEntry::FeatureParam
    kExtensionTelemetryEnterpriseReportingIntervalSeconds_60Seconds[] = {
        {"EnterpriseReportingIntervalSeconds", "60"}};
const FeatureEntry::FeatureParam
    kExtensionTelemetryEnterpriseReportingIntervalSeconds_300Seconds[] = {
        {"EnterpriseReportingIntervalSeconds", "300"}};
const FeatureEntry::FeatureVariation
    kExtensionTelemetryEnterpriseReportingIntervalSecondsVariations[] = {
        {"20 seconds",
         kExtensionTelemetryEnterpriseReportingIntervalSeconds_20Seconds,
         std::size(
             kExtensionTelemetryEnterpriseReportingIntervalSeconds_20Seconds),
         nullptr},
        {"60 seconds",
         kExtensionTelemetryEnterpriseReportingIntervalSeconds_60Seconds,
         std::size(
             kExtensionTelemetryEnterpriseReportingIntervalSeconds_60Seconds),
         nullptr},
        {"300 seconds",
         kExtensionTelemetryEnterpriseReportingIntervalSeconds_300Seconds,
         std::size(
             kExtensionTelemetryEnterpriseReportingIntervalSeconds_300Seconds),
         nullptr}};
constexpr char kExtensionAiDataInternalName[] =
    "enable-extension-ai-data-collection";
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)

const FeatureEntry::FeatureParam kDiscountOnShoppyPage[] = {
    {commerce::kDiscountOnShoppyPageParam, "true"}};

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureVariation kDiscountsVariations[] = {
    {"Discount on Shoppy page", kDiscountOnShoppyPage,
     std::size(kDiscountOnShoppyPage), nullptr}};
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kDiscountIconOnAndroidUseAlternateColor[] = {
    {commerce::kDiscountOnShoppyPageParam, "true"},
    {"action_chip_with_different_color", "true"}};
const FeatureEntry::FeatureVariation kDiscountsVariationsOnAndroid[] = {
    {"Discount on Shoppy page", kDiscountOnShoppyPage,
     std::size(kDiscountOnShoppyPage), nullptr},
    {"action chip different color", kDiscountIconOnAndroidUseAlternateColor,
     std::size(kDiscountIconOnAndroidUseAlternateColor), nullptr}};
#endif  // BUILDFLAG(IS_ANDROID)

const FeatureEntry::FeatureParam
    kSecurePaymentConfirmationNetworkAndIssuerIcons_Inline[] = {
        {"spc_network_and_issuer_icons_option", "inline"}};
const FeatureEntry::FeatureParam
    kSecurePaymentConfirmationNetworkAndIssuerIcons_Rows[] = {
        {"spc_network_and_issuer_icons_option", "rows"}};

const FeatureEntry::FeatureVariation
    kSecurePaymentConfirmationNetworkAndIssuerIconsOptions[] = {
        {"inline with title",
         kSecurePaymentConfirmationNetworkAndIssuerIcons_Inline,
         std::size(kSecurePaymentConfirmationNetworkAndIssuerIcons_Inline),
         nullptr},
        {"as table rows", kSecurePaymentConfirmationNetworkAndIssuerIcons_Rows,
         std::size(kSecurePaymentConfirmationNetworkAndIssuerIcons_Rows),
         nullptr}};

const FeatureEntry::FeatureParam kSkiaGraphite_ValidationEnabled[] = {
    {"dawn_skip_validation", "false"}};
const FeatureEntry::FeatureParam kSkiaGraphite_ValidationDisabled[] = {
    {"dawn_skip_validation", "true"}};
const FeatureEntry::FeatureParam kSkiaGraphite_DebugLabelsEnabled[] = {
    {"dawn_backend_debug_labels", "true"}};

const FeatureEntry::FeatureVariation kSkiaGraphiteVariations[] = {
    {"dawn frontend validation enabled", kSkiaGraphite_ValidationEnabled,
     std::size(kSkiaGraphite_ValidationEnabled), nullptr},
    {"dawn frontend validation disabled", kSkiaGraphite_ValidationDisabled,
     std::size(kSkiaGraphite_ValidationDisabled), nullptr},
    {"dawn debug labels enabled", kSkiaGraphite_DebugLabelsEnabled,
     std::size(kSkiaGraphite_DebugLabelsEnabled), nullptr},
};

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
const FeatureEntry::FeatureParam kTranslationAPI_SkipLanguagePackLimit[] = {
    {"TranslationAPIAcceptLanguagesCheck", "false"},
    {"TranslationAPILimitLanguagePackCount", "false"}};

const FeatureEntry::FeatureVariation kTranslationAPIVariations[] = {
    {"without language pack limit", kTranslationAPI_SkipLanguagePackLimit,
     std::size(kTranslationAPI_SkipLanguagePackLimit), nullptr}};
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)

#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kClayBlockingWithFakeBackend[] = {
    {"use_fake_backend", "true"}};
const FeatureEntry::FeatureParam kClayBlockingVerbose[] = {
    {"enable_verbose_logging", "true"}};
const FeatureEntry::FeatureVariation kClayBlockingVariations[] = {
    {"(with fake backend)", kClayBlockingWithFakeBackend,
     std::size(kClayBlockingWithFakeBackend), nullptr},
    {"(verbose)", kClayBlockingVerbose, std::size(kClayBlockingVerbose),
     nullptr}};

const FeatureEntry::FeatureParam kSensitiveContentUsePwmHeuristics[] = {
    {"sensitive_content_use_pwm_heuristics", "true"}};

const FeatureEntry::FeatureVariation kSensitiveContentVariations[] = {
    {"with password manager heuristics", kSensitiveContentUsePwmHeuristics,
     std::size(kSensitiveContentUsePwmHeuristics), nullptr},
};

const FeatureEntry::FeatureParam kAndroidHubEnableBookmarks[] = {
    {"enable_bookmark_provider", "true"}};
const FeatureEntry::FeatureParam kAndroidHubEnableHistory[] = {
    {"enable_history_provider", "true"}};
const FeatureEntry::FeatureParam kAndroidHubEnableAllExtraProviders[] = {
    {"enable_bookmark_provider", "true"},
    {"enable_history_provider", "true"}};
const FeatureEntry::FeatureParam kAndroidHubEnableEnterToSearch[] = {
    {"enable_press_enter_to_search", "true"}};
const FeatureEntry::FeatureVariation kAndroidHubSearchVariations[] = {
    {"with bookmarks", kAndroidHubEnableBookmarks,
     std::size(kAndroidHubEnableBookmarks), nullptr},
    {"with history", kAndroidHubEnableHistory,
     std::size(kAndroidHubEnableHistory), nullptr},
    {"with all extra providers", kAndroidHubEnableAllExtraProviders,
     std::size(kAndroidHubEnableAllExtraProviders), nullptr},
    {"with pressing enter to search", kAndroidHubEnableEnterToSearch,
     std::size(kAndroidHubEnableEnterToSearch), nullptr}};
#endif  // BUILDFLAG(IS_ANDROID)

// Feature variations for kSubframeProcessReuseThresholds.
const FeatureEntry::FeatureParam kSubframeProcessReuseMemoryThreshold512MB{
    "SubframeProcessReuseMemoryThreshold", "536870912"};
const FeatureEntry::FeatureParam kSubframeProcessReuseMemoryThreshold1GB{
    "SubframeProcessReuseMemoryThreshold", "1073741824"};
const FeatureEntry::FeatureParam kSubframeProcessReuseMemoryThreshold2GB{
    "SubframeProcessReuseMemoryThreshold", "2147483648"};
const FeatureEntry::FeatureParam kSubframeProcessReuseMemoryThreshold4GB{
    "SubframeProcessReuseMemoryThreshold", "4294967296"};
const FeatureEntry::FeatureVariation
    kSubframeProcessReuseThresholdsVariations[] = {
        {"with 512MB memory threshold",
         &kSubframeProcessReuseMemoryThreshold512MB, 1, nullptr},
        {"with 1GB memory threshold", &kSubframeProcessReuseMemoryThreshold1GB,
         1, nullptr},
        {"with 2GB memory threshold", &kSubframeProcessReuseMemoryThreshold2GB,
         1, nullptr},
        {"with 4GB memory threshold", &kSubframeProcessReuseMemoryThreshold4GB,
         1, nullptr},
};

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
const FeatureEntry::FeatureParam kContextualCueingEnabledNoEngagementCap[] = {
    {"BackoffTime", "0h"},
    {"BackoffMultiplierBase", "0.0"},
    {"NudgeCapTime", "0h"},
    {"MinPageCountBetweenNudges", "0"}};
const FeatureEntry::FeatureVariation kContextualCueingEnabledOptions[] = {
    {"no engagement caps", kContextualCueingEnabledNoEngagementCap,
     std::size(kContextualCueingEnabledNoEngagementCap), nullptr},
};
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)

#if PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)
const FeatureEntry::FeatureParam
    kPartitionAllocWithAdvancedChecksEnabledProcesses_BrowserOnly[] = {
        {"enabled-processes", "browser-only"}};
const FeatureEntry::FeatureParam
    kPartitionAllocWithAdvancedChecksEnabledProcesses_BrowserAndRenderer[] = {
        {"enabled-processes", "browser-and-renderer"}};
const FeatureEntry::FeatureParam
    kPartitionAllocWithAdvancedChecksEnabledProcesses_NonRenderer[] = {
        {"enabled-processes", "non-renderer"}};
const FeatureEntry::FeatureParam
    kPartitionAllocWithAdvancedChecksEnabledProcesses_AllProcesses[] = {
        {"enabled-processes", "all-processes"}};
const FeatureEntry::FeatureVariation
    kPartitionAllocWithAdvancedChecksEnabledProcessesOptions[] = {
        {"on browser process only",
         kPartitionAllocWithAdvancedChecksEnabledProcesses_BrowserOnly,
         std::size(
             kPartitionAllocWithAdvancedChecksEnabledProcesses_BrowserOnly),
         nullptr},
        {"on browser and renderer processes",
         kPartitionAllocWithAdvancedChecksEnabledProcesses_BrowserAndRenderer,
         std::size(
             kPartitionAllocWithAdvancedChecksEnabledProcesses_BrowserAndRenderer),
         nullptr},
        {"on non renderer processes",
         kPartitionAllocWithAdvancedChecksEnabledProcesses_NonRenderer,
         std::size(
             kPartitionAllocWithAdvancedChecksEnabledProcesses_NonRenderer),
         nullptr},
        {"on all processes",
         kPartitionAllocWithAdvancedChecksEnabledProcesses_AllProcesses,
         std::size(
             kPartitionAllocWithAdvancedChecksEnabledProcesses_AllProcesses),
         nullptr}};
#endif  // PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)

const FeatureEntry::FeatureParam kSendTabIOSPushNotificationsWithURLImage[] = {
    {send_tab_to_self::kSendTabIOSPushNotificationsURLImageParam, "true"}};
const FeatureEntry::FeatureVariation kSendTabIOSPushNotificationsVariations[] =
    {
        {"With URL Image", kSendTabIOSPushNotificationsWithURLImage,
         std::size(kSendTabIOSPushNotificationsWithURLImage), nullptr},
};

#if BUILDFLAG(IS_ANDROID) && PA_BUILDFLAG(HAS_MEMORY_TAGGING) && \
    PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)
// Feature variations for kPartitionAllocMemoryTagging.
const FeatureEntry::FeatureParam
    kPartitionAllocMemoryTaggingParams_AsyncBrowserOnly[] = {
        {"enabled-processes", "browser-only"},
        {"memtag-mode", "async"}};
const FeatureEntry::FeatureParam
    kPartitionAllocMemoryTaggingParams_AsyncNonRenderer[] = {
        {"enabled-processes", "non-renderer"},
        {"memtag-mode", "async"}};
const FeatureEntry::FeatureParam
    kPartitionAllocMemoryTaggingParams_AsyncAllProcesses[] = {
        {"enabled-processes", "all-processes"},
        {"memtag-mode", "async"}};
const FeatureEntry::FeatureParam
    kPartitionAllocMemoryTaggingParams_SyncBrowserOnly[] = {
        {"enabled-processes", "browser-only"},
        {"memtag-mode", "sync"}};
const FeatureEntry::FeatureParam
    kPartitionAllocMemoryTaggingParams_SyncNonRenderer[] = {
        {"enabled-processes", "non-renderer"},
        {"memtag-mode", "sync"}};
const FeatureEntry::FeatureParam
    kPartitionAllocMemoryTaggingParams_SyncAllProcesses[] = {
        {"enabled-processes", "all-processes"},
        {"memtag-mode", "sync"}};
const FeatureEntry::FeatureVariation
    kPartitionAllocMemoryTaggingEnabledProcessesOptions[] = {
        {"ASYNC mode on browser process only",
         kPartitionAllocMemoryTaggingParams_AsyncBrowserOnly,
         std::size(kPartitionAllocMemoryTaggingParams_AsyncBrowserOnly),
         nullptr},
        {"ASYNC mode on non renderer processes",
         kPartitionAllocMemoryTaggingParams_AsyncNonRenderer,
         std::size(kPartitionAllocMemoryTaggingParams_AsyncNonRenderer),
         nullptr},
        {"ASYNC mode on all processes",
         kPartitionAllocMemoryTaggingParams_AsyncAllProcesses,
         std::size(kPartitionAllocMemoryTaggingParams_AsyncAllProcesses),
         nullptr},
        {"SYNC mode on browser process only",
         kPartitionAllocMemoryTaggingParams_SyncBrowserOnly,
         std::size(kPartitionAllocMemoryTaggingParams_SyncBrowserOnly),
         nullptr},
        {"SYNC mode on non renderer processes",
         kPartitionAllocMemoryTaggingParams_SyncNonRenderer,
         std::size(kPartitionAllocMemoryTaggingParams_SyncNonRenderer),
         nullptr},
        {"SYNC mode on all processes",
         kPartitionAllocMemoryTaggingParams_SyncAllProcesses,
         std::size(kPartitionAllocMemoryTaggingParams_SyncAllProcesses),
         nullptr}};
#endif  // BUILDFLAG(IS_ANDROID) && PA_BUILDFLAG(HAS_MEMORY_TAGGING) &&
        // PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)

const FeatureEntry::FeatureParam kServiceWorkerAutoPreload_SWNotRunningOnly[] =
    {
        {"enable_only_when_service_worker_not_running", "true"},
};
const FeatureEntry::FeatureVariation kServiceWorkerAutoPreloadVariations[] = {
    {"only when SW is not running", kServiceWorkerAutoPreload_SWNotRunningOnly,
     std::size(kServiceWorkerAutoPreload_SWNotRunningOnly), nullptr},
};
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
const FeatureEntry::FeatureParam kCategoricalSearch_Unranked[] = {
    {"ranking", "none"}};

const FeatureEntry::FeatureVariation kCategoricalSearchVariations[] = {
    {"Unranked", kCategoricalSearch_Unranked,
     base::size(kCategoricalSearch_Unranked), nullptr}};
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

constexpr FeatureEntry::FeatureParam kPlatformProvidedTrustTokenIssuance[] = {
    {"PlatformProvidedTrustTokenIssuance", "true"}};

constexpr FeatureEntry::FeatureVariation
    kPlatformProvidedTrustTokensVariations[] = {
        {"with platform-provided trust token issuance",
         kPlatformProvidedTrustTokenIssuance,
         base::size(kPlatformProvidedTrustTokenIssuance), nullptr}};

#if BUILDFLAG(IS_CHROMEOS_ASH)
constexpr char kWallpaperWebUIInternalName[] = "wallpaper-webui";
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(ENABLE_PAINT_PREVIEW) && defined(OS_ANDROID)
const FeatureEntry::FeatureParam kPaintPreviewStartupWithAccessibility[] = {
    {"has_accessibility_support", "true"}};

const FeatureEntry::FeatureVariation kPaintPreviewStartupVariations[] = {
    {"with accessibility support", kPaintPreviewStartupWithAccessibility,
     base::size(kPaintPreviewStartupWithAccessibility), nullptr}};
#endif  // BUILDFLAG(ENABLE_PAINT_PREVIEW) && defined(OS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS_ASH)
constexpr char kBorealisDiskManagementInternalName[] =
    "borealis-disk-management";
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
// The variations of Continuous Search.
const FeatureEntry::FeatureParam kContinuousSearchAfterSecondSrp[] = {
    {"trigger_mode", "1"}};

const FeatureEntry::FeatureParam kContinuousSearchOnReverseScroll[] = {
    {"trigger_mode", "2"}};

const FeatureEntry::FeatureParam kContinuousSearchPermanentDismissal[] = {
    {"permanent_dismissal_threshold", "3"}};

const FeatureEntry::FeatureVariation kContinuousSearchFeatureVariations[] = {
    {"show after second SRP", kContinuousSearchAfterSecondSrp,
     base::size(kContinuousSearchAfterSecondSrp), nullptr},
    {"show on reverse scroll", kContinuousSearchOnReverseScroll,
     base::size(kContinuousSearchOnReverseScroll), nullptr},
    {"with permanent dismissal", kContinuousSearchPermanentDismissal,
     base::size(kContinuousSearchPermanentDismissal), nullptr}};
#endif  // defined(OS_ANDROID)
>>>>>>> chromium

const FeatureEntry::FeatureParam
    kEnableFingerprintingProtectionFilter_WithLogging[] = {
        {"activation_level", "enabled"},
        {"enable_console_logging", "true"}};
const FeatureEntry::FeatureParam
    kEnableFingerprintingProtectionFilter_DryRunWithLogging[] = {
        {"activation_level", "dry_run"},
        {"enable_console_logging", "true"}};
const FeatureEntry::FeatureVariation
    kEnableFingerprintingProtectionFilterVariations[] = {
        {" - with Console Logs",
         kEnableFingerprintingProtectionFilter_WithLogging,
         std::size(kEnableFingerprintingProtectionFilter_WithLogging), nullptr},
        {" - Dry Run with Console Logs",
         kEnableFingerprintingProtectionFilter_DryRunWithLogging,
         std::size(kEnableFingerprintingProtectionFilter_DryRunWithLogging),
         nullptr}};

const FeatureEntry::FeatureParam
    kEnableFingerprintingProtectionFilterInIncognito_WithLogging[] = {
        {"activation_level", "enabled"},
        {"enable_console_logging", "true"}};
const FeatureEntry::FeatureVariation
    kEnableFingerprintingProtectionFilterInIncognitoVariations[] = {
        {" - with Console Logs",
         kEnableFingerprintingProtectionFilterInIncognito_WithLogging,
         std::size(
             kEnableFingerprintingProtectionFilterInIncognito_WithLogging),
         nullptr}};

#if !BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kMerchantTrustEnabledWithSampleData[] = {
    {page_info::kMerchantTrustEnabledWithSampleDataName, "true"}};
const FeatureEntry::FeatureVariation kMerchantTrustVariations[] = {
    {"Enabled with sample data", kMerchantTrustEnabledWithSampleData,
     std::size(kMerchantTrustEnabledWithSampleData), nullptr}};

const FeatureEntry::FeatureParam kAudioDuckingAttenuation_60[] = {
    {"attenuation", "60"}};
const FeatureEntry::FeatureParam kAudioDuckingAttenuation_70[] = {
    {"attenuation", "70"}};
const FeatureEntry::FeatureParam kAudioDuckingAttenuation_80[] = {
    {"attenuation", "80"}};
const FeatureEntry::FeatureParam kAudioDuckingAttenuation_90[] = {
    {"attenuation", "90"}};
const FeatureEntry::FeatureParam kAudioDuckingAttenuation_100[] = {
    {"attenuation", "100"}};

const FeatureEntry::FeatureVariation kAudioDuckingAttenuationVariations[] = {
    {"attenuation 60", kAudioDuckingAttenuation_60,
     std::size(kAudioDuckingAttenuation_60), nullptr},
    {"attenuation 70", kAudioDuckingAttenuation_70,
     std::size(kAudioDuckingAttenuation_70), nullptr},
    {"attenuation 80", kAudioDuckingAttenuation_80,
     std::size(kAudioDuckingAttenuation_80), nullptr},
    {"attenuation 90", kAudioDuckingAttenuation_90,
     std::size(kAudioDuckingAttenuation_90), nullptr},
    {"attenuation 100", kAudioDuckingAttenuation_100,
     std::size(kAudioDuckingAttenuation_100), nullptr}};
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
const FeatureEntry::FeatureParam kTabSwitcherColorBlendAnimateVariation1[] = {
    {"animation_duration_ms", "240"},
    {"animation_interpolator", "1"}};
const FeatureEntry::FeatureParam kTabSwitcherColorBlendAnimateVariation2[] = {
    {"animation_duration_ms", "400"},
    {"animation_interpolator", "2"}};
const FeatureEntry::FeatureParam kTabSwitcherColorBlendAnimateVariation3[] = {
    {"animation_duration_ms", "200"},
    {"animation_interpolator", "3"}};
const FeatureEntry::FeatureVariation kTabSwitcherColorBlendAnimateVariations[] =
    {{"Color Blend Animation Variation 1",
      kTabSwitcherColorBlendAnimateVariation1,
      std::size(kTabSwitcherColorBlendAnimateVariation1), nullptr},
     {"Color Blend Animation Variation 2",
      kTabSwitcherColorBlendAnimateVariation2,
      std::size(kTabSwitcherColorBlendAnimateVariation2), nullptr},
     {"Color Blend Animation Variation 3",
      kTabSwitcherColorBlendAnimateVariation3,
      std::size(kTabSwitcherColorBlendAnimateVariation3), nullptr}};
#endif  // BUILDFLAG(IS_ANDROID)

// RECORDING USER METRICS FOR FLAGS:
// -----------------------------------------------------------------------------
// The first line of the entry is the internal name.
//
// To add a new entry, add to the end of kFeatureEntries. There are two
// distinct types of entries:
// . SINGLE_VALUE: entry is either on or off. Use the SINGLE_VALUE_TYPE
//   macro for this type supplying the command line to the macro.
// . MULTI_VALUE: a list of choices, the first of which should correspond to a
//   deactivated state for this lab (i.e. no command line option). To specify
//   this type of entry use the macro MULTI_VALUE_TYPE supplying it the
//   array of choices.
// See the documentation of FeatureEntry for details on the fields.
//
// Usage of about:flags is logged on startup via the "Launch.FlagsAtStartup"
// UMA histogram. This histogram shows the number of startups with a given flag
// enabled. If you'd like to see user counts instead, make sure to switch to
// "count users" view on the dashboard. When adding new entries, the enum
// "LoginCustomFlags" must be updated in histograms/enums.xml. See note in
// enums.xml and don't forget to run AboutFlagsHistogramTest unit test to
// calculate and verify checksum.
//
// When adding a new choice, add it to the end of the list.
const FeatureEntry kFeatureEntries[] = {
// Include generated flags for flag unexpiry; see //docs/flag_expiry.md and
// //tools/flags/generate_unexpire_flags.py.
#include "build/chromeos_buildflags.h"
#include "chrome/browser/unexpire_flags_gen.inc"
    {"ignore-gpu-blocklist", flag_descriptions::kIgnoreGpuBlocklistName,
     flag_descriptions::kIgnoreGpuBlocklistDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kIgnoreGpuBlocklist)},
    {"disable-accelerated-2d-canvas",
     flag_descriptions::kAccelerated2dCanvasName,
     flag_descriptions::kAccelerated2dCanvasDescription, kOsAll,
     SINGLE_DISABLE_VALUE_TYPE(switches::kDisableAccelerated2dCanvas)},
    {"overlay-strategies", flag_descriptions::kOverlayStrategiesName,
     flag_descriptions::kOverlayStrategiesDescription, kOsAll,
     MULTI_VALUE_TYPE(kOverlayStrategiesChoices)},
    {"tint-composited-content", flag_descriptions::kTintCompositedContentName,
     flag_descriptions::kTintCompositedContentDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kTintCompositedContent)},
    {"show-overdraw-feedback", flag_descriptions::kShowOverdrawFeedbackName,
     flag_descriptions::kShowOverdrawFeedbackDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kShowOverdrawFeedback)},
#if !BUILDFLAG(IS_CHROMEOS)
    {"feedback-include-variations",
     flag_descriptions::kFeedbackIncludeVariationsName,
     flag_descriptions::kFeedbackIncludeVariationsDescription,
     kOsWin | kOsLinux | kOsMac | kOsAndroid,
     FEATURE_VALUE_TYPE(variations::kFeedbackIncludeVariations)},
#endif
    {"ui-disable-partial-swap", flag_descriptions::kUiPartialSwapName,
     flag_descriptions::kUiPartialSwapDescription, kOsAll,
     SINGLE_DISABLE_VALUE_TYPE(switches::kUIDisablePartialSwap)},
    {"enable-webrtc-capture-multi-channel-audio-processing",
     flag_descriptions::kWebrtcCaptureMultiChannelApmName,
     flag_descriptions::kWebrtcCaptureMultiChannelApmDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebRtcEnableCaptureMultiChannelApm)},
    {"disable-webrtc-hw-decoding", flag_descriptions::kWebrtcHwDecodingName,
     flag_descriptions::kWebrtcHwDecodingDescription, kOsAndroid | kOsCrOS,
     SINGLE_DISABLE_VALUE_TYPE(switches::kDisableWebRtcHWDecoding)},
    {"disable-webrtc-hw-encoding", flag_descriptions::kWebrtcHwEncodingName,
     flag_descriptions::kWebrtcHwEncodingDescription, kOsAndroid | kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(features::kWebRtcHWEncoding)},
    {"enable-webrtc-allow-input-volume-adjustment",
     flag_descriptions::kWebRtcAllowInputVolumeAdjustmentName,
     flag_descriptions::kWebRtcAllowInputVolumeAdjustmentDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(features::kWebRtcAllowInputVolumeAdjustment)},
    {"enable-webrtc-apm-downmix-capture-audio-method",
     flag_descriptions::kWebRtcApmDownmixCaptureAudioMethodName,
     flag_descriptions::kWebRtcApmDownmixCaptureAudioMethodDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         features::kWebRtcApmDownmixCaptureAudioMethod,
         kWebRtcApmDownmixMethodVariations,
         "WebRtcApmDownmixCaptureAudioMethod")},
=======
     SINGLE_DISABLE_VALUE_TYPE(switches::kDisableWebRtcHWEncoding)},
#if !defined(OS_ANDROID)
    {"enable-reader-mode", flag_descriptions::kEnableReaderModeName,
     flag_descriptions::kEnableReaderModeDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(dom_distiller::kReaderMode,
                                    kReaderModeDiscoverabilityVariations,
                                    "ReaderMode")},
#endif  // !defined(OS_ANDROID)
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-aura-window-subtree-capture",
     flag_descriptions::kAuraWindowSubtreeCaptureName,
     flag_descriptions::kAuraWindowSubtreeCaptureDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAuraWindowSubtreeCapture)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if defined(WEBRTC_USE_PIPEWIRE)
    {"enable-webrtc-pipewire-capturer",
     flag_descriptions::kWebrtcPipeWireCapturerName,
     flag_descriptions::kWebrtcPipeWireCapturerDescription, kOsLinux,
     FEATURE_VALUE_TYPE(features::kWebRtcPipeWireCapturer)},
#endif  // defined(WEBRTC_USE_PIPEWIRE)
#if defined(OS_LINUX) || defined(OS_CHROMEOS)
    {"send-webui-javascript-error-reports",
     flag_descriptions::kSendWebUIJavaScriptErrorReportsName,
     flag_descriptions::kSendWebUIJavaScriptErrorReportsDescription,
     kOsLinux | kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         features::kSendWebUIJavaScriptErrorReports,
         kSendWebUIJavaScriptErrorReportsVariations,
         "SendWebUIJavaScriptErrorReportsVariations")},
#endif
#if !defined(OS_ANDROID)
    {"enable-webrtc-remote-event-log",
     flag_descriptions::kWebRtcRemoteEventLogName,
     flag_descriptions::kWebRtcRemoteEventLogDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebRtcRemoteEventLog)},
#endif
    {"enable-webrtc-srtp-aes-gcm", flag_descriptions::kWebrtcSrtpAesGcmName,
     flag_descriptions::kWebrtcSrtpAesGcmDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableWebRtcSrtpAesGcm)},
    {"enable-webrtc-hybrid-agc", flag_descriptions::kWebrtcHybridAgcName,
     flag_descriptions::kWebrtcHybridAgcDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebRtcHybridAgc)},
    {"enable-webrtc-analog-agc-clipping-control",
     flag_descriptions::kWebrtcAnalogAgcClippingControlName,
     flag_descriptions::kWebrtcAnalogAgcClippingControlDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebRtcAnalogAgcClippingControl)},
>>>>>>> chromium
    {"enable-webrtc-hide-local-ips-with-mdns",
     flag_descriptions::kWebrtcHideLocalIpsWithMdnsName,
     flag_descriptions::kWebrtcHideLocalIpsWithMdnsDecription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kWebRtcHideLocalIpsWithMdns)},
    {"enable-webrtc-use-min-max-vea-dimensions",
     flag_descriptions::kWebrtcUseMinMaxVEADimensionsName,
     flag_descriptions::kWebrtcUseMinMaxVEADimensionsDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kWebRtcUseMinMaxVEADimensions)},
#if BUILDFLAG(ENABLE_NACL)
    {"enable-nacl", flag_descriptions::kNaclName,
     flag_descriptions::kNaclDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableNaCl)},
#endif  // ENABLE_NACL
#if BUILDFLAG(ENABLE_EXTENSIONS)
    {"extensions-on-chrome-urls",
     flag_descriptions::kExtensionsOnChromeUrlsName,
     flag_descriptions::kExtensionsOnChromeUrlsDescription, kOsAll,
     SINGLE_VALUE_TYPE(extensions::switches::kExtensionsOnChromeURLs)},
#endif  // ENABLE_EXTENSIONS
    {"colr-v1-fonts", flag_descriptions::kCOLRV1FontsName,
     flag_descriptions::kCOLRV1FontsDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kCOLRV1Fonts)},
    {"enable-container-queries", flag_descriptions::kCSSContainerQueriesName,
     flag_descriptions::kCSSContainerQueriesDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kCSSContainerQueries)},
#if defined(OS_ANDROID)
    {"contextual-search-debug", flag_descriptions::kContextualSearchDebugName,
     flag_descriptions::kContextualSearchDebugDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextualSearchDebug)},
    {"contextual-search-force-caption",
     flag_descriptions::kContextualSearchForceCaptionName,
     flag_descriptions::kContextualSearchForceCaptionDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextualSearchForceCaption)},
    {"contextual-search-literal-search-tap",
     flag_descriptions::kContextualSearchLiteralSearchTapName,
     flag_descriptions::kContextualSearchLiteralSearchTapDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextualSearchLiteralSearchTap)},
    {"contextual-search-longpress-resolve",
     flag_descriptions::kContextualSearchLongpressResolveName,
     flag_descriptions::kContextualSearchLongpressResolveDescription,
     kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kContextualSearchLongpressResolve,
         kLongpressResolveVariations,
         "ContextualSearchLongpressResolve")},
    {"contextual-search-ml-tap-suppression",
     flag_descriptions::kContextualSearchMlTapSuppressionName,
     flag_descriptions::kContextualSearchMlTapSuppressionDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextualSearchMlTapSuppression)},
    {"contextual-search-ranker-query",
     flag_descriptions::kContextualSearchRankerQueryName,
     flag_descriptions::kContextualSearchRankerQueryDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(assist_ranker::kContextualSearchRankerQuery)},
    {"contextual-search-second-tap",
     flag_descriptions::kContextualSearchSecondTapName,
     flag_descriptions::kContextualSearchSecondTapDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextualSearchSecondTap)},
    {"contextual-search-twv-impl",
     flag_descriptions::kContextualSearchThinWebViewImplementationName,
     flag_descriptions::kContextualSearchThinWebViewImplementationDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kContextualSearchThinWebViewImplementation)},
    {"contextual-search-translations",
     flag_descriptions::kContextualSearchTranslationsName,
     flag_descriptions::kContextualSearchTranslationsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextualSearchTranslations)},
    {"explore-sites", flag_descriptions::kExploreSitesName,
     flag_descriptions::kExploreSitesDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kExploreSites,
                                    kExploreSitesVariations,
                                    "ExploreSites InitialCountries")},
    {"related-searches", flag_descriptions::kRelatedSearchesName,
     flag_descriptions::kRelatedSearchesDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kRelatedSearches,
                                    kRelatedSearchesVariations,
                                    "RelatedSearches")},
    {"related-searches-ui", flag_descriptions::kRelatedSearchesUiName,
     flag_descriptions::kRelatedSearchesUiDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kRelatedSearchesUi,
                                    kRelatedSearchesUiVariations,
                                    "RelatedSearchesUi")},
    {"related-searches-in-bar", flag_descriptions::kRelatedSearchesInBarName,
     flag_descriptions::kRelatedSearchesInBarDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kRelatedSearchesInBar,
                                    kRelatedSearchesInBarVariations,
                                    "RelatedSearchesInBar")},
    {"related-searches-alternate-ux",
     flag_descriptions::kRelatedSearchesAlternateUxName,
     flag_descriptions::kRelatedSearchesAlternateUxDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kRelatedSearchesAlternateUx,
         kRelatedSearchesAlternateUxVariations,
         "RelatedSearchesAlternateUx")},
    {"related-searches-simplified-ux",
     flag_descriptions::kRelatedSearchesSimplifiedUxName,
     flag_descriptions::kRelatedSearchesSimplifiedUxDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kRelatedSearchesSimplifiedUx)},
    {"single-touch-select", flag_descriptions::kSingleTouchSelectName,
     flag_descriptions::kSingleTouchSelectDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kSingleTouchSelect)},
    {"bento-offline", flag_descriptions::kBentoOfflineName,
     flag_descriptions::kBentoOfflineDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kBentoOffline)},
#endif  // OS_ANDROID
    {"show-autofill-type-predictions",
     flag_descriptions::kShowAutofillTypePredictionsName,
     flag_descriptions::kShowAutofillTypePredictionsDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillShowTypePredictions)},
    {"smooth-scrolling", flag_descriptions::kSmoothScrollingName,
     flag_descriptions::kSmoothScrollingDescription,
     // Mac has a separate implementation with its own setting to disable.
     kOsLinux | kOsCrOS | kOsWin | kOsAndroid,
     ENABLE_DISABLE_VALUE_TYPE(switches::kEnableSmoothScrolling,
                               switches::kDisableSmoothScrolling)},
    {"sms-receiver-cross-device", flag_descriptions::kWebOTPCrossDeviceName,
     flag_descriptions::kWebOTPCrossDeviceDescription, kOsAll,
     FEATURE_VALUE_TYPE(kWebOTPCrossDevice)},
    {"fractional-scroll-offsets",
     flag_descriptions::kFractionalScrollOffsetsName,
     flag_descriptions::kFractionalScrollOffsetsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kFractionalScrollOffsets)},
#if defined(USE_AURA)
    {"overlay-scrollbars", flag_descriptions::kOverlayScrollbarsName,
     flag_descriptions::kOverlayScrollbarsDescription,
     // Uses the system preference on Mac (a different implementation).
     // On Android, this is always enabled.
     kOsAura, FEATURE_VALUE_TYPE(features::kOverlayScrollbar)},
#endif  // USE_AURA
    {"enable-lazy-load-image-for-invisible-pages",
     flag_descriptions::kEnableLazyLoadImageForInvisiblePageName,
     flag_descriptions::kEnableLazyLoadImageForInvisiblePageDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         blink::features::kEnableLazyLoadImageForInvisiblePage,
         kSearchSuggsetionPrerenderTypeVariations,
         "EnableLazyLoadImageForInvisiblePage")},
    {"enable-quic", flag_descriptions::kQuicName,
     flag_descriptions::kQuicDescription, kOsAll,
     ENABLE_DISABLE_VALUE_TYPE(switches::kEnableQuic, switches::kDisableQuic)},
    {"disable-javascript-harmony-shipping",
     flag_descriptions::kJavascriptHarmonyShippingName,
     flag_descriptions::kJavascriptHarmonyShippingDescription, kOsAll,
     SINGLE_DISABLE_VALUE_TYPE(switches::kDisableJavaScriptHarmonyShipping)},
    {"enable-javascript-harmony", flag_descriptions::kJavascriptHarmonyName,
     flag_descriptions::kJavascriptHarmonyDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kJavaScriptHarmony)},
    {"enable-experimental-webassembly-features",
     flag_descriptions::kExperimentalWebAssemblyFeaturesName,
     flag_descriptions::kExperimentalWebAssemblyFeaturesDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableExperimentalWebAssemblyFeatures)},
    {"enable-webassembly-baseline", flag_descriptions::kEnableWasmBaselineName,
     flag_descriptions::kEnableWasmBaselineDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebAssemblyBaseline)},
    {"enable-webassembly-lazy-compilation",
     flag_descriptions::kEnableWasmLazyCompilationName,
     flag_descriptions::kEnableWasmLazyCompilationDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebAssemblyLazyCompilation)},
    {"enable-webassembly-simd", flag_descriptions::kEnableWasmSimdName,
     flag_descriptions::kEnableWasmSimdDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebAssemblySimd)},
    {"enable-webassembly-tiering", flag_descriptions::kEnableWasmTieringName,
     flag_descriptions::kEnableWasmTieringDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebAssemblyTiering)},
    {"enable-future-v8-vm-features", flag_descriptions::kV8VmFutureName,
     flag_descriptions::kV8VmFutureDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kV8VmFuture)},
    {"enable-gpu-rasterization", flag_descriptions::kGpuRasterizationName,
     flag_descriptions::kGpuRasterizationDescription, kOsAll,
     MULTI_VALUE_TYPE(kEnableGpuRasterizationChoices)},
    {"enable-oop-rasterization", flag_descriptions::kOopRasterizationName,
     flag_descriptions::kOopRasterizationDescription, kOsAll,
     MULTI_VALUE_TYPE(kEnableOopRasterizationChoices)},
    {"enable-oop-rasterization-ddl",
     flag_descriptions::kOopRasterizationDDLName,
     flag_descriptions::kOopRasterizationDDLDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kOopRasterizationDDL)},
    {"enable-experimental-web-platform-features",
     flag_descriptions::kExperimentalWebPlatformFeaturesName,
     flag_descriptions::kExperimentalWebPlatformFeaturesDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableExperimentalWebPlatformFeatures)},
#if BUILDFLAG(ENABLE_SPELLCHECK) && defined(OS_ANDROID)
    {"enable-android-spellchecker",
     flag_descriptions::kEnableAndroidSpellcheckerDescription,
     flag_descriptions::kEnableAndroidSpellcheckerDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(spellcheck::kAndroidSpellCheckerNonLowEnd)},
#endif  // ENABLE_SPELLCHECK && OS_ANDROID
    {"top-chrome-touch-ui", flag_descriptions::kTopChromeTouchUiName,
     flag_descriptions::kTopChromeTouchUiDescription, kOsDesktop,
     MULTI_VALUE_TYPE(kTopChromeTouchUiChoices)},
<<<<<<< HEAD

#if !BUILDFLAG(IS_ANDROID)
    {"top-chrome-toasts", flag_descriptions::kTopChromeToastsName,
     flag_descriptions::kTopChromeToastsDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(toast_features::kToastFramework,
                                    kToastVariations,
                                    "ToastFramework")},
    {"top-chrome-toast-refinements",
     flag_descriptions::kTopChromeToastRefinementsName,
     flag_descriptions::kTopChromeToastRefinementsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(toast_features::kToastRefinements)},
#endif

=======
>>>>>>> chromium
#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)
    {"webui-tab-strip", flag_descriptions::kWebUITabStripName,
     flag_descriptions::kWebUITabStripDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebUITabStrip)},
    {"webui-tab-strip-ntb-in-tab-strip",
     flag_descriptions::kWebUITabStripNTBInTabStripName,
     flag_descriptions::kWebUITabStripNTBInTabStripDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebUITabStripNewTabButtonInTabStrip)},
#endif  // BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)
<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"allow-apn-modification-policy",
     flag_descriptions::kAllowApnModificationPolicyName,
     flag_descriptions::kAllowApnModificationPolicyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAllowApnModificationPolicy)},
    {"alt-click-and-six-pack-customization",
     flag_descriptions::kAltClickAndSixPackCustomizationName,
     flag_descriptions::kAltClickAndSixPackCustomizationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAltClickAndSixPackCustomization)},
    {"apn-policies", flag_descriptions::kApnPoliciesName,
     flag_descriptions::kApnPoliciesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kApnPolicies)},
    {"apn-revamp", flag_descriptions::kApnRevampName,
     flag_descriptions::kApnRevampDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kApnRevamp)},
    {"audio-a2dp-advanced-codecs",
     flag_descriptions::kAudioA2DPAdvancedCodecsName,
     flag_descriptions::kAudioA2DPAdvancedCodecsDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootAudioA2DPAdvancedCodecs")},
    {"audio-selection-improvement",
     flag_descriptions::kAudioSelectionImprovementName,
     flag_descriptions::kAudioSelectionImprovementDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAudioSelectionImprovement)},
    {"reset-audio-selection-improvement-pref",
     flag_descriptions::kResetAudioSelectionImprovementPrefName,
     flag_descriptions::kResetAudioSelectionImprovementPrefDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kResetAudioSelectionImprovementPref)},
    {"cras-processor-wav-dump", flag_descriptions::kCrasProcessorWavDumpName,
     flag_descriptions::kCrasProcessorWavDumpDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootCrasProcessorWavDump")},
=======
#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP) && BUILDFLAG(IS_CHROMEOS_ASH)
    {
        "webui-tab-strip-tab-drag-integration",
        flag_descriptions::kWebUITabStripTabDragIntegrationName,
        flag_descriptions::kWebUITabStripTabDragIntegrationDescription,
        kOsCrOS,
        FEATURE_VALUE_TYPE(ash::features::kWebUITabStripTabDragIntegration),
    },
#endif  // BUILDFLAG(ENABLE_WEBUI_TAB_STRIP) && BUILDFLAG(IS_CHROMEOS_ASH)
#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"disable-explicit-dma-fences",
     flag_descriptions::kDisableExplicitDmaFencesName,
     flag_descriptions::kDisableExplicitDmaFencesDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(switches::kDisableExplicitDmaFences)},
    // TODO(crbug.com/1012846): Remove this flag and provision when HDR is fully
    //  supported on ChromeOS.
    {"use-hdr-transfer-function",
     flag_descriptions::kUseHDRTransferFunctionName,
     flag_descriptions::kUseHDRTransferFunctionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(display::features::kUseHDRTransferFunction)},
<<<<<<< HEAD
    {"enable-external-display-hdr10",
     flag_descriptions::kEnableExternalDisplayHdr10Name,
     flag_descriptions::kEnableExternalDisplayHdr10Description, kOsCrOS,
     FEATURE_VALUE_TYPE(display::features::kEnableExternalDisplayHDR10Mode)},
    {"ash-capture-mode-education", flag_descriptions::kCaptureModeEducationName,
     flag_descriptions::kCaptureModeEducationDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kCaptureModeEducation,
                                    kCaptureModeEducationVariations,
                                    "CaptureModeEducation")},
    {"ash-capture-mode-education-bypass-limits",
     flag_descriptions::kCaptureModeEducationBypassLimitsName,
     flag_descriptions::kCaptureModeEducationBypassLimitsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCaptureModeEducationBypassLimits)},
=======
    {"account-management-flows-v2",
     flag_descriptions::kAccountManagementFlowsV2Name,
     flag_descriptions::kAccountManagementFlowsV2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAccountManagementFlowsV2)},
    {"dark-light-mode", flag_descriptions::kDarkLightTestName,
     flag_descriptions::kDarkLightTestDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDarkLightMode)},
    {"screen-capture", flag_descriptions::kScreenCaptureTestName,
     flag_descriptions::kScreenCaptureTestDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCaptureMode)},
    {"ash-bento-bar", flag_descriptions::kBentoBarName,
     flag_descriptions::kBentoBarDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBentoBar)},
    {"ash-overview-button", flag_descriptions::kOverviewButtonName,
     flag_descriptions::kOverviewButtonDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kOverviewButton)},
    {"ash-window-follow-cursor-multi-display",
     flag_descriptions::kWindowsFollowCursorName,
     flag_descriptions::kWindowsFollowCursorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWindowsFollowCursor)},
    {"ash-limit-alt-tab-to-active-desk",
     flag_descriptions::kLimitAltTabToActiveDeskName,
     flag_descriptions::kLimitAltTabToActiveDeskDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kLimitAltTabToActiveDesk)},
>>>>>>> chromium
    {"ash-limit-shelf-items-to-active-desk",
     flag_descriptions::kLimitShelfItemsToActiveDeskName,
     flag_descriptions::kLimitShelfItemsToActiveDeskDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPerDeskShelf)},
    {"ash-enable-unified-desktop",
     flag_descriptions::kAshEnableUnifiedDesktopName,
     flag_descriptions::kAshEnableUnifiedDesktopDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(switches::kEnableUnifiedDesktop)},
<<<<<<< HEAD
    {"rounded-windows", flag_descriptions::kRoundedWindows,
     flag_descriptions::kRoundedWindowsDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chromeos::features::kRoundedWindows,
                                    kRoundedWindowsRadiusVariation,
                                    "RoundedWindows")},
    {"bluetooth-audio-le-audio-only",
     flag_descriptions::kBluetoothAudioLEAudioOnlyName,
     flag_descriptions::kBluetoothAudioLEAudioOnlyDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootBluetoothAudioLEAudioOnly")},
    {"bluetooth-btsnoop-internals",
     flag_descriptions::kBluetoothBtsnoopInternalsName,
     flag_descriptions::kBluetoothBtsnoopInternalsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::bluetooth::features::kBluetoothBtsnoopInternals)},
    {"bluetooth-floss-telephony",
     flag_descriptions::kBluetoothFlossTelephonyName,
     flag_descriptions::kBluetoothFlossTelephonyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::bluetooth::features::kBluetoothFlossTelephony)},
    {kBluetoothUseFlossInternalName, flag_descriptions::kBluetoothUseFlossName,
     flag_descriptions::kBluetoothUseFlossDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(floss::features::kFlossEnabled)},
    {kBluetoothUseLLPrivacyInternalName,
     flag_descriptions::kBluetoothUseLLPrivacyName,
     flag_descriptions::kBluetoothUseLLPrivacyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(bluez::features::kLinkLayerPrivacy)},
    {"campbell-glyph", flag_descriptions::kCampbellGlyphName,
     flag_descriptions::kCampbellGlyphDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kCampbellGlyph,
                                    kCampbellGlyphVariations,
                                    "GampbellGlyph")},
    {"campbell-key", flag_descriptions::kCampbellKeyName,
     flag_descriptions::kCampbellKeyDescription, kOsCrOS,
     STRING_VALUE_TYPE(ash::switches::kCampbellKey, "")},
    {"cellular-bypass-esim-installation-connectivity-check",
     flag_descriptions::kCellularBypassESimInstallationConnectivityCheckName,
     flag_descriptions::
         kCellularBypassESimInstallationConnectivityCheckDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kCellularBypassESimInstallationConnectivityCheck)},
    {"cellular-use-second-euicc",
     flag_descriptions::kCellularUseSecondEuiccName,
     flag_descriptions::kCellularUseSecondEuiccDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCellularUseSecondEuicc)},
    {"cros-privacy-hub-app-permissions-v2",
     flag_descriptions::kCrosPrivacyHubAppPermissionsV2Name,
     flag_descriptions::kCrosPrivacyHubAppPermissionsV2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrosPrivacyHubAppPermissionsV2)},
    {"enable-cros-privacy-hub", flag_descriptions::kCrosPrivacyHubName,
     flag_descriptions::kCrosPrivacyHubDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrosPrivacyHub)},
    {"cros-components", flag_descriptions::kCrosComponentsName,
     flag_descriptions::kCrosComponentsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrosComponents)},
    {"os-feedback-dialog", flag_descriptions::kOsFeedbackDialogName,
     flag_descriptions::kOsFeedbackDialogDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kOsFeedbackDialog)},
=======
    {"enable-compositing-based-throttling",
     flag_descriptions::kCompositingBasedThrottling,
     flag_descriptions::kCompositingBasedThrottlingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCompositingBasedThrottling)},
    {"bluetooth-aggressive-appearance-filter",
     flag_descriptions::kBluetoothAggressiveAppearanceFilterName,
     flag_descriptions::kBluetoothAggressiveAppearanceFilterDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::features::kBluetoothAggressiveAppearanceFilter)},
    {"bluetooth-fix-a2dp-packet-size",
     flag_descriptions::kBluetoothFixA2dpPacketSizeName,
     flag_descriptions::kBluetoothFixA2dpPacketSizeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kBluetoothFixA2dpPacketSize)},
    {"bluetooth-revamp", flag_descriptions::kBluetoothRevampName,
     flag_descriptions::kBluetoothRevampDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kBluetoothRevamp)},
    {"bluetooth-wbs-dogfood", flag_descriptions::kBluetoothWbsDogfoodName,
     flag_descriptions::kBluetoothWbsDogfoodDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kBluetoothWbsDogfood)},
    {"button-arc-network-diagnostics",
     flag_descriptions::kButtonARCNetworkDiagnosticsName,
     flag_descriptions::kButtonARCNetworkDiagnosticsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kButtonARCNetworkDiagnostics)},
    {"cellular-allow-per-network-roaming",
     flag_descriptions::kCellularAllowPerNetworkRoamingName,
     flag_descriptions::kCellularAllowPerNetworkRoamingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCellularAllowPerNetworkRoaming)},
    {"cellular-forbid-attach-apn",
     flag_descriptions::kCellularForbidAttachApnName,
     flag_descriptions::kCellularForbidAttachApnDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCellularForbidAttachApn)},
    {"cellular-use-attach-apn", flag_descriptions::kCellularUseAttachApnName,
     flag_descriptions::kCellularUseAttachApnDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCellularUseAttachApn)},
    {"cellular-use-external-euicc",
     flag_descriptions::kCellularUseExternalEuiccName,
     flag_descriptions::kCellularUseExternalEuiccDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCellularUseExternalEuicc)},
    {"cryptauth-v2-device-activity-status",
     flag_descriptions::kCryptAuthV2DeviceActivityStatusName,
     flag_descriptions::kCryptAuthV2DeviceActivityStatusDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCryptAuthV2DeviceActivityStatus)},
    {"cryptauth-v2-device-activity-status-use-connectivity",
     flag_descriptions::kCryptAuthV2DeviceActivityStatusUseConnectivityName,
     flag_descriptions::
         kCryptAuthV2DeviceActivityStatusUseConnectivityDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::features::kCryptAuthV2DeviceActivityStatusUseConnectivity)},
    {"cryptauth-v2-devicesync", flag_descriptions::kCryptAuthV2DeviceSyncName,
     flag_descriptions::kCryptAuthV2DeviceSyncDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCryptAuthV2DeviceSync)},
    {"cryptauth-v2-enrollment", flag_descriptions::kCryptAuthV2EnrollmentName,
     flag_descriptions::kCryptAuthV2EnrollmentDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCryptAuthV2Enrollment)},
    {"disable-cryptauth-v1-devicesync",
     flag_descriptions::kDisableCryptAuthV1DeviceSyncName,
     flag_descriptions::kDisableCryptAuthV1DeviceSyncDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kDisableCryptAuthV1DeviceSync)},
    {"disable-idle-sockets-close-on-memory-pressure",
     flag_descriptions::kDisableIdleSocketsCloseOnMemoryPressureName,
     flag_descriptions::kDisableIdleSocketsCloseOnMemoryPressureDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::features::kDisableIdleSocketsCloseOnMemoryPressure)},
    {"disable-office-editing-component-app",
     flag_descriptions::kDisableOfficeEditingComponentAppName,
     flag_descriptions::kDisableOfficeEditingComponentAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kDisableOfficeEditingComponentApp)},
    {"updated_cellular_activation_ui",
     flag_descriptions::kUpdatedCellularActivationUiName,
     flag_descriptions::kUpdatedCellularActivationUiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kUpdatedCellularActivationUi)},
    {"use_messages_staging_url", flag_descriptions::kUseMessagesStagingUrlName,
     flag_descriptions::kUseMessagesStagingUrlDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kUseMessagesStagingUrl)},
    {"use-custom-messages-domain",
     flag_descriptions::kUseCustomMessagesDomainName,
     flag_descriptions::kUseCustomMessagesDomainDescription, kOsCrOS,
     ORIGIN_LIST_VALUE_TYPE(switches::kCustomAndroidMessagesDomain, "")},
>>>>>>> chromium
    {"disable-cancel-all-touches",
     flag_descriptions::kDisableCancelAllTouchesName,
     flag_descriptions::kDisableCancelAllTouchesDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(switches::kDisableCancelAllTouches)},
    {
        "enable-background-blur",
        flag_descriptions::kEnableBackgroundBlurName,
        flag_descriptions::kEnableBackgroundBlurDescription,
        kOsCrOS,
        FEATURE_VALUE_TYPE(ash::features::kEnableBackgroundBlur),
    },
<<<<<<< HEAD
    {
        "enable-brightness-control-in-settings",
        flag_descriptions::kEnableBrightnessControlInSettingsName,
        flag_descriptions::kEnableBrightnessControlInSettingsDescription,
        kOsCrOS,
        FEATURE_VALUE_TYPE(ash::features::kEnableBrightnessControlInSettings),
    },
=======
    {"enable-notification-indicator",
     flag_descriptions::kNotificationIndicatorName,
     flag_descriptions::kNotificationIndicatorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNotificationIndicator)},
    {kLacrosSupportInternalName, flag_descriptions::kLacrosSupportName,
     flag_descriptions::kLacrosSupportDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kLacrosSupport)},
    {kLacrosStabilityInternalName, flag_descriptions::kLacrosStabilityName,
     flag_descriptions::kLacrosStabilityDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kLacrosStabilityChoices)},
    {kLacrosSelectionInternalName, flag_descriptions::kLacrosSelectionName,
     flag_descriptions::kLacrosSelectionDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kLacrosSelectionChoices)},
    {kWebAppsCrosapiInternalName, flag_descriptions::kWebAppsCrosapiName,
     flag_descriptions::kWebAppsCrosapiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kWebAppsCrosapi)},
    {kLacrosPrimaryInternalName, flag_descriptions::kLacrosPrimaryName,
     flag_descriptions::kLacrosPrimaryDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kLacrosPrimary)},
    {kLacrosAvailabilityIgnoreInternalName,
     flag_descriptions::kLacrosAvailabilityIgnoreName,
     flag_descriptions::kLacrosAvailabilityIgnoreDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(ash::switches::kLacrosAvailabilityIgnore)},
>>>>>>> chromium
    {"list-all-display-modes", flag_descriptions::kListAllDisplayModesName,
     flag_descriptions::kListAllDisplayModesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(display::features::kListAllDisplayModes)},
    {"enable-hardware_mirror-mode",
     flag_descriptions::kEnableHardwareMirrorModeName,
     flag_descriptions::kEnableHardwareMirrorModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(display::features::kEnableHardwareMirrorMode)},
    {"enable-dns-proxy", flag_descriptions::kEnableDnsProxyName,
     flag_descriptions::kEnableDnsProxyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableDnsProxy)},
    {"dns-proxy-enable-doh", flag_descriptions::kDnsProxyEnableDOHName,
     flag_descriptions::kDnsProxyEnableDOHDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(::features::kDnsProxyEnableDOH)},
    {"instant-tethering", flag_descriptions::kTetherName,
     flag_descriptions::kTetherDescription, kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::features::kInstantTethering)},
=======
     FEATURE_VALUE_TYPE(chromeos::features::kInstantTethering)},
    {
        "new-shortcut-mapping",
        flag_descriptions::kEnableNewShortcutMappingName,
        flag_descriptions::kEnableNewShortcutMappingDescription,
        kOsCrOS,
        FEATURE_VALUE_TYPE(features::kNewShortcutMapping),
    },
    {"improved-keyboard-shortcuts",
     flag_descriptions::kImprovedKeyboardShortcutsName,
     flag_descriptions::kImprovedKeyboardShortcutsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kImprovedKeyboardShortcuts)},
>>>>>>> chromium
    {"deprecate-alt-click", flag_descriptions::kDeprecateAltClickName,
     flag_descriptions::kDeprecateAltClickDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDeprecateAltClick)},
    {"deprecate-alt-based-six-pack",
     flag_descriptions::kDeprecateAltBasedSixPackName,
     flag_descriptions::kDeprecateAltBasedSixPackDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDeprecateAltBasedSixPack)},
    {"shelf-hide-buttons-in-tablet",
     flag_descriptions::kHideShelfControlsInTabletModeName,
     flag_descriptions::kHideShelfControlsInTabletModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHideShelfControlsInTabletMode)},
    {"shelf-hover-previews", flag_descriptions::kShelfHoverPreviewsName,
     flag_descriptions::kShelfHoverPreviewsDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(chromeos::switches::kShelfHoverPreviews)},
    {"show-bluetooth-debug-log-toggle",
     flag_descriptions::kShowBluetoothDebugLogToggleName,
     flag_descriptions::kShowBluetoothDebugLogToggleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kShowBluetoothDebugLogToggle)},
    {"show-taps", flag_descriptions::kShowTapsName,
     flag_descriptions::kShowTapsDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(ash::switches::kShowTaps)},
    {"show-touch-hud", flag_descriptions::kShowTouchHudName,
     flag_descriptions::kShowTouchHudDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(ash::switches::kAshTouchHud)},
    {"trim-on-memory-pressure", flag_descriptions::kTrimOnMemoryPressureName,
     flag_descriptions::kTrimOnMemoryPressureDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(performance_manager::features::kTrimOnMemoryPressure)},
    {"stylus-battery-status", flag_descriptions::kStylusBatteryStatusName,
     flag_descriptions::kStylusBatteryStatusDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kStylusBatteryStatus)},
    {"wake-on-wifi-allowed", flag_descriptions::kWakeOnWifiAllowedName,
     flag_descriptions::kWakeOnWifiAllowedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kWakeOnWifiAllowed)},
    {"microphone-mute-notifications",
     flag_descriptions::kMicrophoneMuteNotificationsName,
     flag_descriptions::kMicrophoneMuteNotificationsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kMicMuteNotifications)},
    {"microphone-mute-switch-device",
     flag_descriptions::kMicrophoneMuteSwitchDeviceName,
     flag_descriptions::kMicrophoneMuteSwitchDeviceDescription, kOsCrOS,
     SINGLE_VALUE_TYPE("enable-microphone-mute-switch-device")},
<<<<<<< HEAD
    {"wifi-connect-mac-address-randomization",
     flag_descriptions::kWifiConnectMacAddressRandomizationName,
     flag_descriptions::kWifiConnectMacAddressRandomizationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWifiConnectMacAddressRandomization)},
    {"wifi-concurrency", flag_descriptions::kWifiConcurrencyName,
     flag_descriptions::kWifiConcurrencyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWifiConcurrency)},
    {"wifi-direct", flag_descriptions::kWifiDirectName,
     flag_descriptions::kWifiDirectDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWifiDirect)},
    {"disable-dns-proxy", flag_descriptions::kDisableDnsProxyName,
     flag_descriptions::kDisableDnsProxyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDisableDnsProxy)},
    {"firmware-update-ui-v2", flag_descriptions::kFirmwareUpdateUIV2Name,
     flag_descriptions::kFirmwareUpdateUIV2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFirmwareUpdateUIV2)},
    {"multi-zone-rgb-keyboard", flag_descriptions::kMultiZoneRgbKeyboardName,
     flag_descriptions::kMultiZoneRgbKeyboardDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kMultiZoneRgbKeyboard)},
    {"enable-rfc-8925", flag_descriptions::kEnableRFC8925Name,
     flag_descriptions::kEnableRFC8925Description, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableRFC8925)},
    {"enable-root-ns-dns-proxy", flag_descriptions::kEnableRootNsDnsProxyName,
     flag_descriptions::kEnableRootNsDnsProxyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableRootNsDnsProxy)},
    {"support-f11-and-f12-shortcuts",
     flag_descriptions::kSupportF11AndF12ShortcutsName,
     flag_descriptions::kSupportF11AndF12ShortcutsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kSupportF11AndF12KeyShortcuts)},
    {"disconnect-wifi-on-ethernet-connected",
     flag_descriptions::kDisconnectWiFiOnEthernetConnectedName,
     flag_descriptions::kDisconnectWiFiOnEthernetConnectedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDisconnectWiFiOnEthernetConnected)},
    {"use-legacy-dhcpcd", flag_descriptions::kUseLegacyDHCPCDName,
     flag_descriptions::kUseLegacyDHCPCDDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kUseLegacyDHCPCD)},
    {"cros-apps-background-event-handling",
     flag_descriptions::kCrosAppsBackgroundEventHandlingName,
     flag_descriptions::kCrosAppsBackgroundEventHandlingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrosAppsBackgroundEventHandling)},
    {"disable-idle-sockets-close-on-memory-pressure",
     flag_descriptions::kDisableIdleSocketsCloseOnMemoryPressureName,
     flag_descriptions::kDisableIdleSocketsCloseOnMemoryPressureDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::features::kDisableIdleSocketsCloseOnMemoryPressure)},
    {"disable-office-editing-component-app",
     flag_descriptions::kDisableOfficeEditingComponentAppName,
     flag_descriptions::kDisableOfficeEditingComponentAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kDisableOfficeEditingComponentApp)},
    {"one-group-per-renderer", flag_descriptions::kOneGroupPerRendererName,
     flag_descriptions::kOneGroupPerRendererDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(base::kOneGroupPerRenderer)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_CHROMEOS)
    // TODO(b/180051795): remove kOsLinux when lacros-chrome switches to
    // kOsCrOS.
    {"deprecate-low-usage-codecs",
     flag_descriptions::kDeprecateLowUsageCodecsName,
     flag_descriptions::kDeprecateLowUsageCodecsDescription, kOsCrOS | kOsLinux,
     FEATURE_VALUE_TYPE(media::kDeprecateLowUsageCodecs)},
#endif  // defined(OS_CHROMEOS)

#if defined(OS_LINUX)
    {
        "enable-accelerated-video-decode",
        flag_descriptions::kAcceleratedVideoDecodeName,
        flag_descriptions::kAcceleratedVideoDecodeDescription,
        kOsLinux,
        FEATURE_VALUE_TYPE(media::kVaapiVideoDecodeLinux),
    },
#else
    // TODO(b/180051795): remove kOsLinux when lacros-chrome switches to
    // kOsCrOS.
>>>>>>> chromium
    {
        "disable-accelerated-video-decode",
        flag_descriptions::kAcceleratedVideoDecodeName,
        flag_descriptions::kAcceleratedVideoDecodeDescription,
        kOsMac | kOsWin | kOsCrOS | kOsAndroid | kOsLinux,
        SINGLE_DISABLE_VALUE_TYPE(switches::kDisableAcceleratedVideoDecode),
    },
#endif  // defined(OS_LINUX)
    {
        "disable-accelerated-video-encode",
        flag_descriptions::kAcceleratedVideoEncodeName,
        flag_descriptions::kAcceleratedVideoEncodeDescription,
        kOsMac | kOsWin | kOsCrOS | kOsAndroid,
        SINGLE_DISABLE_VALUE_TYPE(switches::kDisableAcceleratedVideoEncode),
    },
    {
        "enable-media-internals",
        flag_descriptions::kEnableMediaInternalsName,
        flag_descriptions::kEnableMediaInternalsDescription,
        kOsAll,
        FEATURE_VALUE_TYPE(media::kEnableMediaInternals),
    },
<<<<<<< HEAD
    {
        "enable-hardware-secure-decryption-experiment",
        flag_descriptions::kHardwareSecureDecryptionExperimentName,
        flag_descriptions::kHardwareSecureDecryptionExperimentDescription,
        kOsWin,
        FEATURE_VALUE_TYPE(media::kHardwareSecureDecryptionExperiment),
    },
    {
        "enable-hardware-secure-decryption-fallback",
        flag_descriptions::kHardwareSecureDecryptionFallbackName,
        flag_descriptions::kHardwareSecureDecryptionFallbackDescription,
        kOsWin,
        FEATURE_VALUE_TYPE(media::kHardwareSecureDecryptionFallback),
    },
    {
        "enable-media-foundation-clear",
        flag_descriptions::kMediaFoundationClearName,
        flag_descriptions::kMediaFoundationClearDescription,
        kOsWin,
        FEATURE_VALUE_TYPE(media::kMediaFoundationClearPlayback),
    },
    {"enable-media-foundation-clear-rendering-strategy",
     flag_descriptions::kMediaFoundationClearStrategyName,
     flag_descriptions::kMediaFoundationClearStrategyDescription, kOsWin,
     FEATURE_WITH_PARAMS_VALUE_TYPE(media::kMediaFoundationClearRendering,
                                    kMediaFoundationClearStrategyVariations,
                                    "MediaFoundationClearRendering")},
    {
        "enable-waitable-swap-chain",
        flag_descriptions::kUseWaitableSwapChainName,
        flag_descriptions::kUseWaitableSwapChainDescription,
        kOsWin,
        FEATURE_WITH_PARAMS_VALUE_TYPE(features::kDXGIWaitableSwapChain,
                                       kDXGIWaitableSwapChainVariations,
                                       "DXGIWaitableSwapChain"),
    },
#endif  // BUILDFLAG(IS_WIN)

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX)
    {
        "fluent-overlay-scrollbars",
        flag_descriptions::kFluentOverlayScrollbarsName,
        flag_descriptions::kFluentOverlayScrollbarsDescription,
        kOsWin | kOsLinux,
        FEATURE_VALUE_TYPE(features::kFluentOverlayScrollbar),
    },
    {
        "fluent-scrollbars",
        flag_descriptions::kFluentScrollbarsName,
        flag_descriptions::kFluentScrollbarsDescription,
        kOsWin | kOsLinux,
        FEATURE_VALUE_TYPE(features::kFluentScrollbar),
    },
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX)
#if BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {
        "zero-copy-video-capture",
        flag_descriptions::kZeroCopyVideoCaptureName,
        flag_descriptions::kZeroCopyVideoCaptureDescription,
        kOsCrOS,
        ENABLE_DISABLE_VALUE_TYPE_AND_VALUE(
            switches::kVideoCaptureUseGpuMemoryBuffer,
            "1",
            switches::kDisableVideoCaptureUseGpuMemoryBuffer,
            "1"),
    },
    {
        "ash-debug-shortcuts",
        flag_descriptions::kDebugShortcutsName,
        flag_descriptions::kDebugShortcutsDescription,
        kOsAll,
        SINGLE_VALUE_TYPE(ash::switches::kAshDebugShortcuts),
    },
    {"ui-slow-animations", flag_descriptions::kUiSlowAnimationsName,
     flag_descriptions::kUiSlowAnimationsDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(switches::kUISlowAnimations)},
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(IS_WIN)
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if defined(OS_WIN)
>>>>>>> chromium
    {
        "zero-copy-video-capture",
        flag_descriptions::kZeroCopyVideoCaptureName,
        flag_descriptions::kZeroCopyVideoCaptureDescription,
        kOsWin,
        FEATURE_VALUE_TYPE(media::kMediaFoundationD3D11VideoCapture),
    },
#endif  // defined(OS_WIN)
    {"debug-packed-apps", flag_descriptions::kDebugPackedAppName,
     flag_descriptions::kDebugPackedAppDescription, kOsDesktop,
     SINGLE_VALUE_TYPE(switches::kDebugPackedApps)},
    {"use-lookalikes-for-navigation-suggestions",
     flag_descriptions::kUseLookalikesForNavigationSuggestionsName,
     flag_descriptions::kUseLookalikesForNavigationSuggestionsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(net::features::kUseLookalikesForNavigationSuggestions)},
    {"username-first-flow", flag_descriptions::kUsernameFirstFlowName,
     flag_descriptions::kUsernameFirstFlowDescription, kOsAll,
     FEATURE_VALUE_TYPE(password_manager::features::kUsernameFirstFlow)},
    {"username-first-flow-filling",
     flag_descriptions::kUsernameFirstFlowFillingName,
     flag_descriptions::kUsernameFirstFlowFillingDescription, kOsAll,
     FEATURE_VALUE_TYPE(password_manager::features::kUsernameFirstFlowFilling)},
    {"enable-show-autofill-signatures",
     flag_descriptions::kShowAutofillSignaturesName,
     flag_descriptions::kShowAutofillSignaturesDescription, kOsAll,
     SINGLE_VALUE_TYPE(autofill::switches::kShowAutofillSignatures)},
    {"wallet-service-use-sandbox",
     flag_descriptions::kWalletServiceUseSandboxName,
     flag_descriptions::kWalletServiceUseSandboxDescription,
     kOsAndroid | kOsDesktop,
     ENABLE_DISABLE_VALUE_TYPE_AND_VALUE(
         autofill::switches::kWalletServiceUseSandbox,
         "1",
         autofill::switches::kWalletServiceUseSandbox,
         "0")},
    {"enable-web-bluetooth-new-permissions-backend",
     flag_descriptions::kWebBluetoothNewPermissionsBackendName,
     flag_descriptions::kWebBluetoothNewPermissionsBackendDescription,
     kOsAndroid | kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebBluetoothNewPermissionsBackend)},
#if defined(USE_AURA)
    {"overscroll-history-navigation",
     flag_descriptions::kOverscrollHistoryNavigationName,
     flag_descriptions::kOverscrollHistoryNavigationDescription, kOsAura,
     FEATURE_VALUE_TYPE(features::kOverscrollHistoryNavigation)},
    {"pull-to-refresh", flag_descriptions::kPullToRefreshName,
     flag_descriptions::kPullToRefreshDescription, kOsAura,
     MULTI_VALUE_TYPE(kPullToRefreshChoices)},
#endif  // USE_AURA
    {"enable-touch-drag-drop", flag_descriptions::kTouchDragDropName,
     flag_descriptions::kTouchDragDropDescription, kOsWin | kOsCrOS,
     ENABLE_DISABLE_VALUE_TYPE(switches::kEnableTouchDragDrop,
                               switches::kDisableTouchDragDrop)},
    {"touch-selection-strategy", flag_descriptions::kTouchSelectionStrategyName,
     flag_descriptions::kTouchSelectionStrategyDescription,
     kOsAndroid,  // TODO(mfomitchev): Add CrOS/Win/Linux support soon.
     MULTI_VALUE_TYPE(kTouchTextSelectionStrategyChoices)},
<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
=======
    {"trace-upload-url", flag_descriptions::kTraceUploadUrlName,
     flag_descriptions::kTraceUploadUrlDescription, kOsAll,
     MULTI_VALUE_TYPE(kTraceUploadURL)},
    {"enable-suggestions-with-substring-match",
     flag_descriptions::kSuggestionsWithSubStringMatchName,
     flag_descriptions::kSuggestionsWithSubStringMatchDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillTokenPrefixMatching)},
#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"enable-virtual-keyboard", flag_descriptions::kVirtualKeyboardName,
     flag_descriptions::kVirtualKeyboardDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(keyboard::switches::kEnableVirtualKeyboard)},
    {"disable-virtual-keyboard",
     flag_descriptions::kVirtualKeyboardDisabledName,
     flag_descriptions::kVirtualKeyboardDisabledDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(keyboard::switches::kDisableVirtualKeyboard)},
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if BUILDFLAG(ENABLE_SERVICE_DISCOVERY)
    {"device-discovery-notifications",
     flag_descriptions::kDeviceDiscoveryNotificationsName,
     flag_descriptions::kDeviceDiscoveryNotificationsDescription, kOsDesktop,
     SINGLE_VALUE_TYPE(switches::kEnableDeviceDiscoveryNotifications)},
#endif  // BUILDFLAG(ENABLE_SERVICE_DISCOVERY)
>>>>>>> chromium
    {"enable-webgl-developer-extensions",
     flag_descriptions::kWebglDeveloperExtensionsName,
     flag_descriptions::kWebglDeveloperExtensionsDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableWebGLDeveloperExtensions)},
    {"enable-webgl-draft-extensions",
     flag_descriptions::kWebglDraftExtensionsName,
     flag_descriptions::kWebglDraftExtensionsDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableWebGLDraftExtensions)},
    {"enable-zero-copy", flag_descriptions::kZeroCopyName,
     flag_descriptions::kZeroCopyDescription, kOsAll,
     ENABLE_DISABLE_VALUE_TYPE(blink::switches::kEnableZeroCopy,
                               blink::switches::kDisableZeroCopy)},
    {"enable-vulkan", flag_descriptions::kEnableVulkanName,
     flag_descriptions::kEnableVulkanDescription,
<<<<<<< HEAD
     kOsWin | kOsLinux | kOsAndroid | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kVulkan)},
    {"default-angle-vulkan", flag_descriptions::kDefaultAngleVulkanName,
     flag_descriptions::kDefaultAngleVulkanDescription,
     kOsLinux | kOsAndroid | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDefaultANGLEVulkan)},
    {"vulkan-from-angle", flag_descriptions::kVulkanFromAngleName,
     flag_descriptions::kVulkanFromAngleDescription,
     kOsLinux | kOsAndroid | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kVulkanFromANGLE)},

#if !BUILDFLAG(IS_CHROMEOS)
=======
     kOsWin | kOsLinux | kOsAndroid, FEATURE_VALUE_TYPE(features::kVulkan)},
#if defined(OS_MAC)
    {"disable-hosted-app-shim-creation",
     flag_descriptions::kHostedAppShimCreationName,
     flag_descriptions::kHostedAppShimCreationDescription, kOsMac,
     SINGLE_DISABLE_VALUE_TYPE(switches::kDisableHostedAppShimCreation)},
#endif  // OS_MAC
#if defined(OS_ANDROID)
    {"translate-force-trigger-on-english",
     flag_descriptions::kTranslateForceTriggerOnEnglishName,
     flag_descriptions::kTranslateForceTriggerOnEnglishDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(language::kOverrideTranslateTriggerInIndia,
                                    kTranslateForceTriggerOnEnglishVariations,
                                    "OverrideTranslateTriggerInIndia")},
    {"translate-assist-content", flag_descriptions::kTranslateAssistContentName,
     flag_descriptions::kTranslateAssistContentDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(language::kTranslateAssistContent)},
    {"translate-intent", flag_descriptions::kTranslateIntentName,
     flag_descriptions::kTranslateIntentDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(language::kTranslateIntent)},
#endif  // OS_ANDROID

    {"override-language-prefs-for-href-translate",
     flag_descriptions::kOverrideLanguagePrefsForHrefTranslateName,
     flag_descriptions::kOverrideLanguagePrefsForHrefTranslateDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         translate::kOverrideLanguagePrefsForHrefTranslate,
         kOverrideLanguagePrefsForHrefTranslateVariations,
         "OverrideLanguagePrefsForHrefTranslate")},
    {"override-site-prefs-for-href-translate",
     flag_descriptions::kOverrideSitePrefsForHrefTranslateName,
     flag_descriptions::kOverrideSitePrefsForHrefTranslateDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         translate::kOverrideSitePrefsForHrefTranslate,
         kOverrideSitePrefsForHrefTranslateVariations,
         "OverrideSitePrefsForHrefTranslate")},
    {"override-unsupported-page-language-for-href-translate",
     flag_descriptions::kOverrideUnsupportedPageLanguageForHrefTranslateName,
     flag_descriptions::
         kOverrideUnsupportedPageLanguageForHrefTranslateDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         translate::kOverrideUnsupportedPageLanguageForHrefTranslate,
         kOverrideUnsupportedPageLanguageForHrefTranslateVariations,
         "OverrideUnsupportedPageLanguageForHrefTranslate")},
    {"override-similar-languages-for-href-translate",
     flag_descriptions::kOverrideSimilarLanguagesForHrefTranslateName,
     flag_descriptions::kOverrideSimilarLanguagesForHrefTranslateDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         translate::kOverrideSimilarLanguagesForHrefTranslate,
         kOverrideSimilarLanguagesForHrefTranslateVariations,
         "OverrideSimilarLanguagesForHrefTranslate")},

#if BUILDFLAG(ENABLE_SYSTEM_NOTIFICATIONS) && !BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"enable-system-notifications",
     flag_descriptions::kNotificationsSystemFlagName,
     flag_descriptions::kNotificationsSystemFlagDescription,
     kOsMac | kOsLinux | kOsWin,
     FEATURE_VALUE_TYPE(features::kSystemNotifications)},
<<<<<<< HEAD
#endif  // !BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(IS_CHROMEOS)
    {"enable-ongoing-processes", flag_descriptions::kEnableOngoingProcessesName,
     flag_descriptions::kEnableOngoingProcessesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kOngoingProcesses)},
#endif  // BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(IS_ANDROID)
    {"adaptive-button-in-top-toolbar-page-summary",
     flag_descriptions::kAdaptiveButtonInTopToolbarPageSummaryName,
     flag_descriptions::kAdaptiveButtonInTopToolbarPageSummaryDescription,
=======
#endif  // BUILDFLAG(ENABLE_SYSTEM_NOTIFICATIONS) && !BUILDFLAG(IS_CHROMEOS_ASH)
#if defined(OS_ANDROID)
    {"adaptive-button-in-top-toolbar",
     flag_descriptions::kAdaptiveButtonInTopToolbarName,
     flag_descriptions::kAdaptiveButtonInTopToolbarDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kAdaptiveButtonInTopToolbar,
         kAdaptiveButtonInTopToolbarVariations,
         "OptionalToolbarButton")},
    {"adaptive-button-in-top-toolbar-customization",
     flag_descriptions::kAdaptiveButtonInTopToolbarCustomizationName,
     flag_descriptions::kAdaptiveButtonInTopToolbarCustomizationDescription,
>>>>>>> chromium
     kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kAdaptiveButtonInTopToolbarCustomization,
         kAdaptiveButtonInTopToolbarCustomizationVariations,
         "OptionalToolbarButtonCustomization")},
    {"reader-mode-heuristics", flag_descriptions::kReaderModeHeuristicsName,
     flag_descriptions::kReaderModeHeuristicsDescription, kOsAndroid,
     MULTI_VALUE_TYPE(kReaderModeHeuristicsChoices)},
    {"voice-button-in-top-toolbar",
     flag_descriptions::kVoiceButtonInTopToolbarName,
     flag_descriptions::kVoiceButtonInTopToolbarDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kVoiceButtonInTopToolbar)},
    {"assistant-explicit-voice-consent",
     flag_descriptions::kAssistantExplicitVoiceConsentName,
     flag_descriptions::kAssistantExplicitVoiceConsentDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAssistantExplicitVoiceConsent)},
    {"assistant-intent-page-url",
     flag_descriptions::kAssistantIntentPageUrlName,
     flag_descriptions::kAssistantIntentPageUrlDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAssistantIntentPageUrl)},
    {"assistant-intent-translate-info",
     flag_descriptions::kAssistantIntentTranslateInfoName,
     flag_descriptions::kAssistantIntentTranslateInfoDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAssistantIntentTranslateInfo)},
    {"assistant-voice-consent-taps-counter",
     flag_descriptions::kAssistantVoiceConstentTapsCounterName,
     flag_descriptions::kAssistantVoiceConstentTapsCounterDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAssistantVoiceConsentTapsCounter)},
    {"share-button-in-top-toolbar",
     flag_descriptions::kShareButtonInTopToolbarName,
     flag_descriptions::kShareButtonInTopToolbarDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kShareButtonInTopToolbar)},
    {"chrome-share-highlights-android",
     flag_descriptions::kChromeShareHighlightsAndroidName,
     flag_descriptions::kChromeShareHighlightsAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kChromeShareHighlightsAndroid)},
    {"chrome-share-long-screenshot",
     flag_descriptions::kChromeShareLongScreenshotName,
     flag_descriptions::kChromeShareLongScreenshotDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kChromeShareLongScreenshot)},
    {"chrome-share-screenshot", flag_descriptions::kChromeShareScreenshotName,
     flag_descriptions::kChromeShareScreenshotDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kChromeShareScreenshot)},
    {"chrome-sharing-hub", flag_descriptions::kChromeSharingHubName,
     flag_descriptions::kChromeSharingHubDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kChromeSharingHub)},
    {"webnotes-stylize", flag_descriptions::kWebNotesStylizeName,
     flag_descriptions::kWebNotesStylizeDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(content_creation::kWebNotesStylizeEnabled,
                                    kWebNoteStylizeVariations,
                                    "WebNotesStylize")},
    {"sharing-hub-link-toggle", flag_descriptions::kSharingHubLinkToggleName,
     flag_descriptions::kSharingHubLinkToggleDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kSharingHubLinkToggle)},
#endif  // OS_ANDROID
    {"in-product-help-demo-mode-choice",
     flag_descriptions::kInProductHelpDemoModeChoiceName,
     flag_descriptions::kInProductHelpDemoModeChoiceDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         feature_engagement::kIPHDemoMode,
         feature_engagement::kIPHDemoModeChoiceVariations,
         "IPH_DemoMode")},
<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
=======
    {"disable-threaded-scrolling", flag_descriptions::kThreadedScrollingName,
     flag_descriptions::kThreadedScrollingDescription, kOsAll,
     SINGLE_DISABLE_VALUE_TYPE(blink::switches::kDisableThreadedScrolling)},
    {"extension-content-verification",
     flag_descriptions::kExtensionContentVerificationName,
     flag_descriptions::kExtensionContentVerificationDescription, kOsDesktop,
     MULTI_VALUE_TYPE(kExtensionContentVerificationChoices)},
    {"preemptive-link-to-text-generation",
     flag_descriptions::kPreemptiveLinkToTextGenerationName,
     flag_descriptions::kPreemptiveLinkToTextGenerationDescription, kOsAll,
     FEATURE_VALUE_TYPE(shared_highlighting::kPreemptiveLinkToTextGeneration)},
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"keyboard-based-display-arrangement-in-settings",
     flag_descriptions::kKeyboardBasedDisplayArrangementInSettingsName,
     flag_descriptions::kKeyboardBasedDisplayArrangementInSettingsDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kKeyboardBasedDisplayArrangementInSettings)},
>>>>>>> chromium
    {"enable-lock-screen-notification",
     flag_descriptions::kLockScreenNotificationName,
     flag_descriptions::kLockScreenNotificationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kLockScreenNotifications)},
<<<<<<< HEAD
    {"enable-service-workers-for-chrome-untrusted",
     flag_descriptions::kEnableServiceWorkersForChromeUntrustedName,
     flag_descriptions::kEnableServiceWorkersForChromeUntrustedDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableServiceWorkersForChromeUntrusted)},
    {"enterprise-reporting-ui", flag_descriptions::kEnterpriseReportingUIName,
     flag_descriptions::kEnterpriseReportingUIDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnterpriseReportingUI)},
    {"chromebox-usb-passthrough-restrictions",
     flag_descriptions::kChromeboxUsbPassthroughRestrictionsName,
     flag_descriptions::kChromeboxUsbPassthroughRestrictionsDescription,
     kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE(
         "CrOSLateBootChromeboxUsbPassthroughRestrictions")},
    {"disable-bruschetta-install-checks",
     flag_descriptions::kDisableBruschettaInstallChecksName,
     flag_descriptions::kDisableBruschettaInstallChecksDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDisableBruschettaInstallChecks)},
    {"crostini-reset-lxd-db", flag_descriptions::kCrostiniResetLxdDbName,
     flag_descriptions::kCrostiniResetLxdDbDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrostiniResetLxdDb)},
    {"terminal-dev", flag_descriptions::kTerminalDevName,
     flag_descriptions::kTerminalDevDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kTerminalDev)},
    {"permissive-usb-passthrough",
     flag_descriptions::kPermissiveUsbPassthroughName,
     flag_descriptions::kPermissiveUsbPassthroughDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootPermissiveUsbPassthrough")},
    {"camera-angle-backend", flag_descriptions::kCameraAngleBackendName,
     flag_descriptions::kCameraAngleBackendDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootCameraAngleBackend")},
    {"crostini-containerless", flag_descriptions::kCrostiniContainerlessName,
     flag_descriptions::kCrostiniContainerlessDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrostiniContainerless)},
    {"crostini-multi-container", flag_descriptions::kCrostiniMultiContainerName,
     flag_descriptions::kCrostiniMultiContainerDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrostiniMultiContainer)},
    {"crostini-qt-ime-support", flag_descriptions::kCrostiniQtImeSupportName,
     flag_descriptions::kCrostiniQtImeSupportDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrostiniQtImeSupport)},
    {"crostini-virtual-keyboard-support",
     flag_descriptions::kCrostiniVirtualKeyboardSupportName,
     flag_descriptions::kCrostiniVirtualKeyboardSupportDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrostiniVirtualKeyboardSupport)},
    {"notifications-ignore-require-interaction",
     flag_descriptions::kNotificationsIgnoreRequireInteractionName,
     flag_descriptions::kNotificationsIgnoreRequireInteractionDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNotificationsIgnoreRequireInteraction)},
    {"sys-ui-holdback-drive-integration",
     flag_descriptions::kSysUiShouldHoldbackDriveIntegrationName,
     flag_descriptions::kSysUiShouldHoldbackDriveIntegrationDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSysUiShouldHoldbackDriveIntegration)},
    {"sys-ui-holdback-focus-mode",
     flag_descriptions::kSysUiShouldHoldbackFocusModeName,
     flag_descriptions::kSysUiShouldHoldbackFocusModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSysUiShouldHoldbackFocusMode)},
    {"sys-ui-holdback-forest",
     flag_descriptions::kSysUiShouldHoldbackForestName,
     flag_descriptions::kSysUiShouldHoldbackForestDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSysUiShouldHoldbackForest)},
    {"sys-ui-holdback-task-management",
     flag_descriptions::kSysUiShouldHoldbackTaskManagementName,
     flag_descriptions::kSysUiShouldHoldbackTaskManagementDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSysUiShouldHoldbackTaskManagement)},

#endif  // BUILDFLAG(IS_CHROMEOS)
#if (BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_LINUX) || \
     BUILDFLAG(IS_ANDROID)) &&                        \
    !BUILDFLAG(IS_NACL)
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"crostini-use-dlc", flag_descriptions::kCrostiniUseDlcName,
     flag_descriptions::kCrostiniUseDlcDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrostiniUseDlc)},
    {"pluginvm-fullscreen", flag_descriptions::kPluginVmFullscreenName,
     flag_descriptions::kPluginVmFullscreenDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kPluginVmFullscreen)},
    {"vm-status-page", flag_descriptions::kVmStatusPageName,
     flag_descriptions::kVmStatusPageDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kVmStatusPage)},
    {"crostini-reset-lxd-db", flag_descriptions::kCrostiniResetLxdDbName,
     flag_descriptions::kCrostiniResetLxdDbDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrostiniResetLxdDb)},
#if BUILDFLAG(USE_TCMALLOC)
    {"dynamic-tcmalloc-tuning", flag_descriptions::kDynamicTcmallocName,
     flag_descriptions::kDynamicTcmallocDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(performance_manager::features::kDynamicTcmallocTuning)},
#endif  // BUILDFLAG(USE_TCMALLOC)
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if (defined(OS_CHROMEOS) || defined(OS_LINUX) || defined(OS_ANDROID)) && \
    !defined(OS_NACL)
>>>>>>> chromium
    {"mojo-linux-sharedmem", flag_descriptions::kMojoLinuxChannelSharedMemName,
     flag_descriptions::kMojoLinuxChannelSharedMemDescription,
     kOsCrOS | kOsLinux | kOsAndroid,
     FEATURE_VALUE_TYPE(mojo::core::kMojoLinuxChannelSharedMem)},
#endif
#if defined(OS_ANDROID)
    {"enable-site-isolation-for-password-sites",
     flag_descriptions::kSiteIsolationForPasswordSitesName,
     flag_descriptions::kSiteIsolationForPasswordSitesDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         site_isolation::features::kSiteIsolationForPasswordSites)},
    {"enable-site-per-process", flag_descriptions::kStrictSiteIsolationName,
     flag_descriptions::kStrictSiteIsolationDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(switches::kSitePerProcess)},
    {"enable-process-sharing-with-default-site-instances",
     flag_descriptions::kProcessSharingWithDefaultSiteInstancesName,
     flag_descriptions::kProcessSharingWithDefaultSiteInstancesDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(features::kProcessSharingWithDefaultSiteInstances)},
    {"enable-process-sharing-with-strict-site-instances",
     flag_descriptions::kProcessSharingWithStrictSiteInstancesName,
     flag_descriptions::kProcessSharingWithStrictSiteInstancesDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(features::kProcessSharingWithStrictSiteInstances)},
#endif
<<<<<<< HEAD

#if !BUILDFLAG(IS_ANDROID)
    {"enable-isolated-web-apps", flag_descriptions::kEnableIsolatedWebAppsName,
     flag_descriptions::kEnableIsolatedWebAppsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kIsolatedWebApps)},
#if BUILDFLAG(IS_CHROMEOS)
    {"enable-isolated-web-app-managed-guest-session-install",
     flag_descriptions::kEnableIsolatedWebAppManagedGuestSessionInstallName,
     flag_descriptions::
         kEnableIsolatedWebAppManagedGuestSessionInstallDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kIsolatedWebAppManagedGuestSessionInstall)},
    {"enable-isolated-web-app-unmanaged-install",
     flag_descriptions::kEnableIsolatedWebAppUnmanagedInstallName,
     flag_descriptions::kEnableIsolatedWebAppUnmanagedInstallDescription,
     kOsCrOS, FEATURE_VALUE_TYPE(features::kIsolatedWebAppUnmanagedInstall)},
#endif
    {"enable-isolated-web-app-dev-mode",
     flag_descriptions::kEnableIsolatedWebAppDevModeName,
     flag_descriptions::kEnableIsolatedWebAppDevModeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kIsolatedWebAppDevMode)},
    {"enable-iwa-key-distribution-component",
     flag_descriptions::kEnableIwaKeyDistributionComponentName,
     flag_descriptions::kEnableIwaKeyDistributionComponentDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(component_updater::kIwaKeyDistributionComponent)},
    {"iwa-key-distribution-component-exp-cohort",
     flag_descriptions::kIwaKeyDistributionComponentExpCohortName,
     flag_descriptions::kIwaKeyDistributionComponentExpCohortDescription,
     kOsDesktop,
     STRING_VALUE_TYPE(component_updater::kIwaKeyDistributionComponentExpCohort,
                       "")},
#if BUILDFLAG(IS_CHROMEOS)
    {"install-isolated-web-app-from-url",
     flag_descriptions::kInstallIsolatedWebAppFromUrl,
     flag_descriptions::kInstallIsolatedWebAppFromUrlDescription, kOsAll,
     ORIGIN_LIST_VALUE_TYPE(switches::kInstallIsolatedWebAppFromUrl, "")},
#endif
#endif

#if !BUILDFLAG(IS_ANDROID)
    {"enable-controlled-frame", flag_descriptions::kEnableControlledFrameName,
     flag_descriptions::kEnableControlledFrameDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kControlledFrame)},
#endif  // !BUILDFLAG(IS_ANDROID)

=======
>>>>>>> chromium
    {"isolate-origins", flag_descriptions::kIsolateOriginsName,
     flag_descriptions::kIsolateOriginsDescription, kOsAll,
     ORIGIN_LIST_VALUE_TYPE(switches::kIsolateOrigins, "")},
    {about_flags::kSiteIsolationTrialOptOutInternalName,
     flag_descriptions::kSiteIsolationOptOutName,
     flag_descriptions::kSiteIsolationOptOutDescription, kOsAll,
     MULTI_VALUE_TYPE(kSiteIsolationOptOutChoices)},
    {"isolation-by-default", flag_descriptions::kIsolationByDefaultName,
     flag_descriptions::kIsolationByDefaultDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kIsolationByDefault)},
    {"enable-use-zoom-for-dsf", flag_descriptions::kEnableUseZoomForDsfName,
     flag_descriptions::kEnableUseZoomForDsfDescription, kOsAll,
     MULTI_VALUE_TYPE(kEnableUseZoomForDSFChoices)},
    {"enable-subresource-redirect",
     flag_descriptions::kEnableSubresourceRedirectName,
     flag_descriptions::kEnableSubresourceRedirectDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kSubresourceRedirect,
                                    kSubresourceRedirectVariations,
                                    "SubresourceRedirect")},
    {"enable-login-detection", flag_descriptions::kEnableLoginDetectionName,
     flag_descriptions::kEnableLoginDetectionDescription, kOsAll,
     FEATURE_VALUE_TYPE(login_detection::kLoginDetection)},
#if defined(OS_CHROMEOS) || defined(OS_LINUX)
    {"enable-save-data", flag_descriptions::kEnableSaveDataName,
     flag_descriptions::kEnableSaveDataDescription, kOsCrOS | kOsLinux,
     SINGLE_VALUE_TYPE(
         data_reduction_proxy::switches::kEnableDataReductionProxy)},
    {"enable-navigation-predictor",
     flag_descriptions::kEnableNavigationPredictorName,
     flag_descriptions::kEnableNavigationPredictorDescription,
     kOsCrOS | kOsLinux,
     FEATURE_VALUE_TYPE(blink::features::kNavigationPredictor)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) || OS_LINUX
    {"enable-preconnect-to-search",
     flag_descriptions::kEnablePreconnectToSearchName,
     flag_descriptions::kEnablePreconnectToSearchDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kPreconnectToSearch)},
    {"enable-google-srp-isolated-prerender-probing",
     flag_descriptions::kEnableSRPIsolatedPrerenderProbingName,
     flag_descriptions::kEnableSRPIsolatedPrerenderProbingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kIsolatePrerendersMustProbeOrigin)},
    {"enable-google-srp-isolated-prerenders",
     flag_descriptions::kEnableSRPIsolatedPrerendersName,
     flag_descriptions::kEnableSRPIsolatedPrerendersDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kIsolatePrerenders,
                                    kIsolatedPrerenderFeatureWithPrefetchLimit,
                                    "Prefetch Limit")},
    {"enable-google-srp-isolated-prerender-nsp",
     flag_descriptions::kEnableSRPIsolatedPrerendersNSPName,
     flag_descriptions::kEnableSRPIsolatedPrerendersNSPDescription, kOsAll,
     SINGLE_VALUE_TYPE(kIsolatedPrerenderEnableNSPCmdLineFlag)},
    {"allow-insecure-localhost", flag_descriptions::kAllowInsecureLocalhostName,
     flag_descriptions::kAllowInsecureLocalhostDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kAllowInsecureLocalhost)},
<<<<<<< HEAD
    {"text-based-audio-descriptions",
     flag_descriptions::kTextBasedAudioDescriptionName,
     flag_descriptions::kTextBasedAudioDescriptionDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kTextBasedAudioDescription)},
    {"enable-desktop-pwas-app-title",
     flag_descriptions::kDesktopPWAsAppTitleName,
     flag_descriptions::kDesktopPWAsAppTitleDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kWebAppEnableAppTitle)},
=======
    {"bypass-app-banner-engagement-checks",
     flag_descriptions::kBypassAppBannerEngagementChecksName,
     flag_descriptions::kBypassAppBannerEngagementChecksDescription, kOsAll,
     SINGLE_VALUE_TYPE(webapps::switches::kBypassAppBannerEngagementChecks)},
#if BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS)
    {"allow-default-web-app-migration-for-chrome-os-managed-users",
     flag_descriptions::kAllowDefaultWebAppMigrationForChromeOsManagedUsersName,
     flag_descriptions::
         kAllowDefaultWebAppMigrationForChromeOsManagedUsersDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         web_app::kAllowDefaultWebAppMigrationForChromeOsManagedUsers)},
    {"enable-default-chat-web-app", flag_descriptions::kDefaultChatWebAppName,
     flag_descriptions::kDefaultChatWebAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(web_app::kDefaultChatWebApp)},
    {"enable-default-meet-web-app", flag_descriptions::kDefaultMeetWebAppName,
     flag_descriptions::kDefaultMeetWebAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(web_app::kDefaultMeetWebApp)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS)
    // TODO(https://crbug.com/1069293): Add macOS and Linux implementations.
    {"enable-desktop-pwas-app-icon-shortcuts-menu",
     flag_descriptions::kDesktopPWAsAppIconShortcutsMenuName,
     flag_descriptions::kDesktopPWAsAppIconShortcutsMenuDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsAppIconShortcutsMenu)},
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-desktop-pwas-attention-badging-cros",
     flag_descriptions::kDesktopPWAsAttentionBadgingCrOSName,
     flag_descriptions::kDesktopPWAsAttentionBadgingCrOSDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kDesktopPWAsAttentionBadgingCrOS,
                                    kDesktopPWAsAttentionBadgingCrOSVariations,
                                    "DesktopPWAsAttentionBadgingCrOS")},
#endif
    {"enable-desktop-pwas-prefix-app-name-in-window-title",
     flag_descriptions::kDesktopPWAsPrefixAppNameInWindowTitleName,
     flag_descriptions::kDesktopPWAsPrefixAppNameInWindowTitleDescription,
     kOsDesktop, FEATURE_VALUE_TYPE(features::kPrefixWebAppWindowsWithAppName)},
    {"enable-desktop-pwas-remove-status-bar",
     flag_descriptions::kDesktopPWAsRemoveStatusBarName,
     flag_descriptions::kDesktopPWAsRemoveStatusBarDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kRemoveStatusBarInWebApps)},
>>>>>>> chromium
    {"enable-desktop-pwas-elided-extensions-menu",
     flag_descriptions::kDesktopPWAsElidedExtensionsMenuName,
     flag_descriptions::kDesktopPWAsElidedExtensionsMenuDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsElidedExtensionsMenu)},
    {"enable-desktop-pwas-flash-app-name-instead-of-origin",
     flag_descriptions::kDesktopPWAsFlashAppNameInsteadOfOriginName,
     flag_descriptions::kDesktopPWAsFlashAppNameInsteadOfOriginDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsFlashAppNameInsteadOfOrigin)},
    {"enable-desktop-pwas-notification-icon-and-title",
     flag_descriptions::kDesktopPWAsNotificationIconAndTitleName,
     flag_descriptions::kDesktopPWAsNotificationIconAndTitleDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsNotificationIconAndTitle)},
    {"enable-desktop-pwas-tab-strip",
     flag_descriptions::kDesktopPWAsTabStripName,
     flag_descriptions::kDesktopPWAsTabStripDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsTabStrip)},
    {"enable-desktop-pwas-tab-strip-link-capturing",
     flag_descriptions::kDesktopPWAsTabStripLinkCapturingName,
     flag_descriptions::kDesktopPWAsTabStripLinkCapturingDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsTabStripLinkCapturing)},
    {"enable-desktop-pwas-tab-strip-settings",
     flag_descriptions::kDesktopPWAsTabStripSettingsName,
     flag_descriptions::kDesktopPWAsTabStripSettingsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsTabStripSettings)},
    {"enable-desktop-pwas-link-capturing",
     flag_descriptions::kDesktopPWAsLinkCapturingName,
     flag_descriptions::kDesktopPWAsLinkCapturingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kWebAppEnableLinkCapturing)},
    {"enable-desktop-pwas-manifest-id",
     flag_descriptions::kDesktopPWAsManifestIdName,
     flag_descriptions::kDesktopPWAsManifestIdDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kWebAppEnableManifestId)},
    {"enable-desktop-pwas-run-on-os-login",
     flag_descriptions::kDesktopPWAsRunOnOsLoginName,
     flag_descriptions::kDesktopPWAsRunOnOsLoginDescription,
     kOsWin | kOsLinux | kOsMac,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsRunOnOsLogin)},
    {"enable-desktop-pwas-sub-apps", flag_descriptions::kDesktopPWAsSubAppsName,
     flag_descriptions::kDesktopPWAsSubAppsDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsSubApps)},
    {"enable-desktop-pwas-protocol-handling",
     flag_descriptions::kDesktopPWAsProtocolHandlingName,
     flag_descriptions::kDesktopPWAsProtocolHandlingDescription,
     kOsWin | kOsLinux | kOsMac,
     FEATURE_VALUE_TYPE(blink::features::kWebAppEnableProtocolHandlers)},
    {"enable-desktop-pwas-url-handling",
     flag_descriptions::kDesktopPWAsUrlHandlingName,
     flag_descriptions::kDesktopPWAsUrlHandlingDescription,
     kOsWin | kOsLinux | kOsMac,
     FEATURE_VALUE_TYPE(blink::features::kWebAppEnableUrlHandlers)},
    {"enable-desktop-pwas-window-controls-overlay",
     flag_descriptions::kDesktopPWAsWindowControlsOverlayName,
     flag_descriptions::kDesktopPWAsWindowControlsOverlayDescription,
     kOsWin | kOsLinux | kOsMac,
     FEATURE_VALUE_TYPE(features::kWebAppWindowControlsOverlay)},
    {"enable-desktop-pwas-web-bundles",
     flag_descriptions::kDesktopPWAsWebBundlesName,
     flag_descriptions::kDesktopPWAsWebBundlesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsWebBundles)},
    {"record-web-app-debug-info", flag_descriptions::kRecordWebAppDebugInfoName,
     flag_descriptions::kRecordWebAppDebugInfoDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kRecordWebAppDebugInfo)},
<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
    {"web-app-sync-generated-icon-background-fix",
     flag_descriptions::kWebAppSyncGeneratedIconBackgroundFixName,
     flag_descriptions::kWebAppSyncGeneratedIconBackgroundFixDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebAppSyncGeneratedIconBackgroundFix)},
    {"web-app-sync-generated-icon-retroactive-fix",
     flag_descriptions::kWebAppSyncGeneratedIconRetroactiveFixName,
     flag_descriptions::kWebAppSyncGeneratedIconRetroactiveFixDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebAppSyncGeneratedIconRetroactiveFix)},
    {"web-app-sync-generated-icon-update-fix",
     flag_descriptions::kWebAppSyncGeneratedIconUpdateFixName,
     flag_descriptions::kWebAppSyncGeneratedIconUpdateFixDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebAppSyncGeneratedIconUpdateFix)},
    {"enable-desktop-pwas-sync-changes",
     flag_descriptions::kDesktopPWAsSyncChangesName,
     flag_descriptions::kDesktopPWAsSyncChangesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebAppDontAddExistingAppsToSync)},
#endif  // !BUILDFLAG(IS_ANDROID)
#if BUILDFLAG(IS_CHROMEOS)
    {"web-app-user-display-mode-sync-browser-mitigation",
     flag_descriptions::kUserDisplayModeSyncBrowserMitigationName,
     flag_descriptions::kUserDisplayModeSyncBrowserMitigationDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(web_app::kUserDisplayModeSyncBrowserMitigation)},
    {"web-app-user-display-mode-sync-standalone-mitigation",
     flag_descriptions::kUserDisplayModeSyncStandaloneMitigationName,
     flag_descriptions::kUserDisplayModeSyncStandaloneMitigationDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(web_app::kUserDisplayModeSyncStandaloneMitigation)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
>>>>>>> chromium
    {"use-sync-sandbox", flag_descriptions::kSyncSandboxName,
     flag_descriptions::kSyncSandboxDescription, kOsAll,
     SINGLE_VALUE_TYPE_AND_VALUE(
         switches::kSyncServiceURL,
         "https://chrome-sync.sandbox.google.com/chrome-sync/alpha")},
#if !defined(OS_ANDROID)
    {"media-router-cast-allow-all-ips",
     flag_descriptions::kMediaRouterCastAllowAllIPsName,
     flag_descriptions::kMediaRouterCastAllowAllIPsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_router::kCastAllowAllIPsFeature)},
<<<<<<< HEAD
    {"media-remoting-without-fullscreen",
     flag_descriptions::kMediaRemotingWithoutFullscreenName,
     flag_descriptions::kMediaRemotingWithoutFullscreenDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kMediaRemotingWithoutFullscreen)},
    {"remote-playback-backend", flag_descriptions::kRemotePlaybackBackendName,
     flag_descriptions::kRemotePlaybackBackendDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kRemotePlaybackBackend)},
=======
    {"cast-media-route-provider",
     flag_descriptions::kCastMediaRouteProviderName,
     flag_descriptions::kCastMediaRouteProviderDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_router::kCastMediaRouteProvider)},
    {"global-media-controls-cast-start-stop",
     flag_descriptions::kGlobalMediaControlsCastStartStopName,
     flag_descriptions::kGlobalMediaControlsCastStartStopDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(media_router::kGlobalMediaControlsCastStartStop)},
>>>>>>> chromium
    {"allow-all-sites-to-initiate-mirroring",
     flag_descriptions::kAllowAllSitesToInitiateMirroringName,
     flag_descriptions::kAllowAllSitesToInitiateMirroringDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(media_router::kAllowAllSitesToInitiateMirroring)},
<<<<<<< HEAD
    {"media-route-dial-provider",
     flag_descriptions::kDialMediaRouteProviderName,
     flag_descriptions::kDialMediaRouteProviderDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_router::kDialMediaRouteProvider)},
    {"delay-media-sink-discovery",
     flag_descriptions::kDelayMediaSinkDiscoveryName,
     flag_descriptions::kDelayMediaSinkDiscoveryDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_router::kDelayMediaSinkDiscovery)},
    {"show-cast-permission-rejected-error",
     flag_descriptions::kShowCastPermissionRejectedErrorName,
     flag_descriptions::kShowCastPermissionRejectedErrorDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_router::kShowCastPermissionRejectedError)},
    {"cast-message-logging", flag_descriptions::kCastMessageLoggingName,
     flag_descriptions::kCastMessageLoggingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_router::kCastMessageLogging)},

    {"cast-streaming-hardware-h264",
     flag_descriptions::kCastStreamingHardwareH264Name,
     flag_descriptions::kCastStreamingHardwareH264Description, kOsDesktop,
     ENABLE_DISABLE_VALUE_TYPE(
         switches::kCastStreamingForceEnableHardwareH264,
         switches::kCastStreamingForceDisableHardwareH264)},

    {"cast-streaming-hardware-vp8",
     flag_descriptions::kCastStreamingHardwareVp8Name,
     flag_descriptions::kCastStreamingHardwareVp8Description, kOsDesktop,
     ENABLE_DISABLE_VALUE_TYPE(
         switches::kCastStreamingForceEnableHardwareVp8,
         switches::kCastStreamingForceDisableHardwareVp8)},

    {"cast-streaming-hardware-vp9",
     flag_descriptions::kCastStreamingHardwareVp9Name,
     flag_descriptions::kCastStreamingHardwareVp9Description, kOsDesktop,
     ENABLE_DISABLE_VALUE_TYPE(
         switches::kCastStreamingForceEnableHardwareVp9,
         switches::kCastStreamingForceDisableHardwareVp9)},

    {"cast-streaming-media-video-encoder",
     flag_descriptions::kCastStreamingMediaVideoEncoderName,
     flag_descriptions::kCastStreamingMediaVideoEncoderDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kCastStreamingMediaVideoEncoder)},

    {"cast-streaming-performance-overlay",
     flag_descriptions::kCastStreamingPerformanceOverlayName,
     flag_descriptions::kCastStreamingPerformanceOverlayDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kCastStreamingPerformanceOverlay)},

    {"enable-cast-streaming-av1", flag_descriptions::kCastStreamingAv1Name,
     flag_descriptions::kCastStreamingAv1Description, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kCastStreamingAv1)},

#if BUILDFLAG(IS_MAC)
    {"enable-cast-streaming-mac-hardware-h264",
     flag_descriptions::kCastStreamingMacHardwareH264Name,
     flag_descriptions::kCastStreamingMacHardwareH264Description, kOsMac,
     FEATURE_VALUE_TYPE(media::kCastStreamingMacHardwareH264)},
    {"use-network-framework-for-local-discovery",
     flag_descriptions::kUseNetworkFrameworkForLocalDiscoveryName,
     flag_descriptions::kUseNetworkFrameworkForLocalDiscoveryDescription,
     kOsMac,
     FEATURE_VALUE_TYPE(media_router::kUseNetworkFrameworkForLocalDiscovery)},
#endif

#if BUILDFLAG(IS_WIN)
    {"enable-cast-streaming-win-hardware-h264",
     flag_descriptions::kCastStreamingWinHardwareH264Name,
     flag_descriptions::kCastStreamingWinHardwareH264Description, kOsWin,
     FEATURE_VALUE_TYPE(media::kCastStreamingWinHardwareH264)},
#endif

    {"enable-cast-streaming-vp8", flag_descriptions::kCastStreamingVp8Name,
     flag_descriptions::kCastStreamingVp8Description, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kCastStreamingVp8)},

    {"enable-cast-streaming-vp9", flag_descriptions::kCastStreamingVp9Name,
     flag_descriptions::kCastStreamingVp9Description, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kCastStreamingVp9)},

    {"enable-cast-streaming-with-hidpi",
     flag_descriptions::kCastEnableStreamingWithHiDPIName,
     flag_descriptions::kCastEnableStreamingWithHiDPIDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(mirroring::features::kCastEnableStreamingWithHiDPI)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"clay-blocking-dialog", flag_descriptions::kClayBlockingDialogName,
     flag_descriptions::kClayBlockingDialogDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(switches::kClayBlocking,
                                    kClayBlockingVariations,
                                    "ClayBlocking")},

    {"template-url-reconciliation",
     flag_descriptions::kTemplateUrlReconciliationName,
     flag_descriptions::kTemplateUrlReconciliationDialogDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(switches::kTemplateUrlReconciliation)},

#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_MAC)
=======
    {"enable-migrate-default-chrome-app-to-web-apps-gsuite",
     flag_descriptions::kEnableMigrateDefaultChromeAppToWebAppsGSuiteName,
     flag_descriptions::
         kEnableMigrateDefaultChromeAppToWebAppsGSuiteDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(web_app::kMigrateDefaultChromeAppToWebAppsGSuite)},
    {"enable-migrate-default-chrome-app-to-web-apps-non-gsuite",
     flag_descriptions::kEnableMigrateDefaultChromeAppToWebAppsNonGSuiteName,
     flag_descriptions::
         kEnableMigrateDefaultChromeAppToWebAppsNonGSuiteDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(web_app::kMigrateDefaultChromeAppToWebAppsNonGSuite)},
#endif  // !OS_ANDROID
#if defined(OS_ANDROID)
    {"autofill-keyboard-accessory-view",
     flag_descriptions::kAutofillAccessoryViewName,
     flag_descriptions::kAutofillAccessoryViewDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillKeyboardAccessory)},
#endif  // OS_ANDROID
#if defined(OS_MAC)
>>>>>>> chromium
    {"mac-syscall-sandbox", flag_descriptions::kMacSyscallSandboxName,
     flag_descriptions::kMacSyscallSandboxDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kMacSyscallSandbox)},
#endif  // OS_MAC
#if BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_WIN) || defined(OS_MAC)
    {"web-share", flag_descriptions::kWebShareName,
     flag_descriptions::kWebShareDescription, kOsWin | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kWebShare)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) || OS_WIN || OS_MAC
#if BUILDFLAG(ENABLE_VR)
<<<<<<< HEAD
    {"webxr-hand-input", flag_descriptions::kWebXrHandInputName,
     flag_descriptions::kWebXrHandInputDescription, kOsAll,
     FEATURE_VALUE_TYPE(device::features::kWebXrHandInput)},
    {"webxr-webgpu-binding", flag_descriptions::kWebXrWebGpuBindingName,
     flag_descriptions::kWebXrWebGpuBindingDescription, kOsWin | kOsAndroid,
     FEATURE_VALUE_TYPE(device::features::kWebXrWebGpuBinding)},
=======
>>>>>>> chromium
    {"webxr-incubations", flag_descriptions::kWebXrIncubationsName,
     flag_descriptions::kWebXrIncubationsDescription, kOsAll,
     FEATURE_VALUE_TYPE(device::features::kWebXrIncubations)},
    {"webxr-runtime", flag_descriptions::kWebXrForceRuntimeName,
     flag_descriptions::kWebXrForceRuntimeDescription, kOsDesktop,
     MULTI_VALUE_TYPE(kWebXrForceRuntimeChoices)},
<<<<<<< HEAD
    {"webxr-hand-anonymization",
     flag_descriptions::kWebXrHandAnonymizationStrategyName,
     flag_descriptions::kWebXrHandAnonymizationStrategyDescription,
     kOsDesktop | kOsAndroid, MULTI_VALUE_TYPE(KWebXrHandAnonymizationChoices)},
#if BUILDFLAG(IS_ANDROID)
    {"webxr-shared-buffers", flag_descriptions::kWebXrSharedBuffersName,
     flag_descriptions::kWebXrSharedBuffersDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(device::features::kWebXrSharedBuffers)},
#if BUILDFLAG(ENABLE_OPENXR)
    {"enable-openxr-android", flag_descriptions::kOpenXRName,
     flag_descriptions::kOpenXRDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(device::features::kOpenXR)},
    {"enable-openxr-android-smooth-depth",
     flag_descriptions::kOpenXRAndroidSmoothDepthName,
     flag_descriptions::kOpenXRAndroidSmoothDepthDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(device::features::kOpenXR)},
    {"enable-openxr-extended", flag_descriptions::kOpenXRExtendedFeaturesName,
     flag_descriptions::kOpenXRExtendedFeaturesDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(device::features::kOpenXrExtendedFeatureSupport)},
#endif
#endif  // BUILDFLAG(IS_ANDROID)
=======
>>>>>>> chromium
#endif  // ENABLE_VR
#if BUILDFLAG(IS_CHROMEOS)
    {"disable-accelerated-mjpeg-decode",
     flag_descriptions::kAcceleratedMjpegDecodeName,
     flag_descriptions::kAcceleratedMjpegDecodeDescription, kOsCrOS,
     SINGLE_DISABLE_VALUE_TYPE(switches::kDisableAcceleratedMjpegDecode)},
#endif  // BUILDFLAG(IS_CHROMEOS)
    {"system-keyboard-lock", flag_descriptions::kSystemKeyboardLockName,
     flag_descriptions::kSystemKeyboardLockDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSystemKeyboardLock)},
#if defined(OS_ANDROID)
    {"add-to-homescreen-iph", flag_descriptions::kAddToHomescreenIPHName,
     flag_descriptions::kAddToHomescreenIPHDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kAddToHomescreenIPH,
                                    kAddToHomescreenIPHVariations,
                                    "AddToHomescreen")},
    {"offline-pages-live-page-sharing",
     flag_descriptions::kOfflinePagesLivePageSharingName,
     flag_descriptions::kOfflinePagesLivePageSharingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(offline_pages::kOfflinePagesLivePageSharingFeature)},
    {"offline-indicator-v2", flag_descriptions::kOfflineIndicatorV2Name,
     flag_descriptions::kOfflineIndicatorV2Description, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kOfflineIndicatorV2)},
    {"query-tiles", flag_descriptions::kQueryTilesName,
     flag_descriptions::kQueryTilesDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(query_tiles::features::kQueryTiles)},
    {"query-tiles-ntp", flag_descriptions::kQueryTilesNTPName,
     flag_descriptions::kQueryTilesNTPDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(query_tiles::features::kQueryTilesInNTP)},
    {"query-tiles-omnibox", flag_descriptions::kQueryTilesOmniboxName,
     flag_descriptions::kQueryTilesOmniboxDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(query_tiles::features::kQueryTilesInOmnibox)},
    {"query-tiles-local-ordering",
     flag_descriptions::kQueryTilesLocalOrderingName,
     flag_descriptions::kQueryTilesLocalOrderingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(query_tiles::features::kQueryTilesLocalOrdering)},
    {"query-tiles-single-tier", flag_descriptions::kQueryTilesSingleTierName,
     flag_descriptions::kQueryTilesSingleTierDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(query_tiles::switches::kQueryTilesSingleTier)},
    {"query-tiles-enable-query-editing",
     flag_descriptions::kQueryTilesEnableQueryEditingName,
     flag_descriptions::kQueryTilesEnableQueryEditingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(query_tiles::features::kQueryTilesEnableQueryEditing)},
    {"query-tiles-enable-trending",
     flag_descriptions::kQueryTilesEnableTrendingName,
     flag_descriptions::kQueryTilesEnableTrendingDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(query_tiles::switches::kQueryTilesEnableTrending)},
    {"query-tiles-country-code", flag_descriptions::kQueryTilesCountryCode,
     flag_descriptions::kQueryTilesCountryCodeDescription, kOsAndroid,
     MULTI_VALUE_TYPE(kQueryTilesCountryChoices)},
    {"query-tiles-instant-fetch",
     flag_descriptions::kQueryTilesInstantFetchName,
     flag_descriptions::kQueryTilesInstantFetchDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(
         query_tiles::switches::kQueryTilesInstantBackgroundTask)},
    {"query-tiles-more-trending",
     flag_descriptions::kQueryTilesMoreTrendingName,
     flag_descriptions::kQueryTilesMoreTrendingDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(query_tiles::switches::kQueryTilesMoreTrending)},
    {"query-tiles-rank-tiles", flag_descriptions::kQueryTilesRankTilesName,
     flag_descriptions::kQueryTilesRankTilesDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(query_tiles::switches::kQueryTilesRankTiles)},
    {"query-tiles-swap-trending",
     flag_descriptions::kQueryTilesSwapTrendingName,
     flag_descriptions::kQueryTilesSwapTrendingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         query_tiles::features::kQueryTilesRemoveTrendingTilesAfterInactivity)},
    {"video-tutorials", flag_descriptions::kVideoTutorialsName,
     flag_descriptions::kVideoTutorialsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(video_tutorials::features::kVideoTutorials)},
    {"video-tutorials-instant-fetch",
     flag_descriptions::kVideoTutorialsInstantFetchName,
     flag_descriptions::kVideoTutorialsInstantFetchDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(video_tutorials::switches::kVideoTutorialsInstantFetch)},
    {"android-picture-in-picture-api",
     flag_descriptions::kAndroidPictureInPictureAPIName,
     flag_descriptions::kAndroidPictureInPictureAPIDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(media::kPictureInPictureAPI)},
    {"reengagement-notification",
     flag_descriptions::kReengagementNotificationName,
     flag_descriptions::kReengagementNotificationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kReengagementNotification)},
<<<<<<< HEAD

    // Enterprise Data Controls
    {"enable-clipboard-data-controls-android",
     flag_descriptions::kEnableClipboardDataControlsAndroidName,
     flag_descriptions::kEnableClipboardDataControlsAndroidDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(data_controls::kEnableClipboardDataControlsAndroid)},

    {"right-edge-goes-forward-gesture-nav",
     flag_descriptions::kRightEdgeGoesForwardGestureNavName,
     flag_descriptions::kRightEdgeGoesForwardGestureNavDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kRightEdgeGoesForwardGestureNav)},

    // Android Edge to edge
    {"draw-cutout-edge-to-edge", flag_descriptions::kDrawCutoutEdgeToEdgeName,
     flag_descriptions::kDrawCutoutEdgeToEdgeDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kDrawCutoutEdgeToEdge)},
    {"draw-key-native-edge-to-edge",
     flag_descriptions::kDrawKeyNativeEdgeToEdgeName,
     flag_descriptions::kDrawKeyNativeEdgeToEdgeDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kDrawKeyNativeEdgeToEdge)},
    {"edge-to-edge-bottom-chin", flag_descriptions::kEdgeToEdgeBottomChinName,
     flag_descriptions::kEdgeToEdgeBottomChinDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kEdgeToEdgeBottomChin,
                                    kEdgeToEdgeBottomChinVariations,
                                    "EdgeToEdgeBottomChin")},
    {"edge-to-edge-everywhere", flag_descriptions::kEdgeToEdgeEverywhereName,
     flag_descriptions::kEdgeToEdgeEverywhereDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kEdgeToEdgeEverywhere,
                                    kEdgeToEdgeEverywhereVariations,
                                    "EdgeToEdgeEverywhere")},
    {"edge-to-edge-safe-area-constraint",
     flag_descriptions::kEdgeToEdgeSafeAreaConstraintName,
     flag_descriptions::kEdgeToEdgeSafeAreaConstraintDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kEdgeToEdgeSafeAreaConstraint)},
    {"edge-to-edge-web-opt-in", flag_descriptions::kEdgeToEdgeWebOptInName,
     flag_descriptions::kEdgeToEdgeWebOptInDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kEdgeToEdgeWebOptIn)},
    {"dynamic-safe-area-insets", flag_descriptions::kDynamicSafeAreaInsetsName,
     flag_descriptions::kDynamicSafeAreaInsetsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(blink::features::kDynamicSafeAreaInsets)},
    {"dynamic-safe-area-insets-on-scroll",
     flag_descriptions::kDynamicSafeAreaInsetsOnScrollName,
     flag_descriptions::kDynamicSafeAreaInsetsOnScrollDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(blink::features::kDynamicSafeAreaInsetsOnScroll)},
    {"dynamic-safe-area-insets-supported-by-cc",
     flag_descriptions::kDynamicSafeAreaInsetsSupportedByCCName,
     flag_descriptions::kDynamicSafeAreaInsetsSupportedByCCDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(features::kDynamicSafeAreaInsetsSupportedByCC)},
    {"bottom-browser-controls-refactor",
     flag_descriptions::kBottomBrowserControlsRefactorName,
     flag_descriptions::kBottomBrowserControlsRefactorDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kBottomBrowserControlsRefactor,
         kBottomBrowserControlsRefactorVariations,
         "BottomBrowserControlsRefactor")},

    // Android floating snackbar
    {"floating-snackbar", flag_descriptions::kFloatingSnackbarName,
     flag_descriptions::kFloatingSnackbarDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kFloatingSnackbar)},

    // Android nav bar color animation
    {"nav-bar-color-animation", flag_descriptions::kNavBarColorAnimationName,
     flag_descriptions::kNavBarColorAnimationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kNavBarColorAnimation)},

    // Tab closure methods refactor.
    {"tab-closure-method-refactor",
     flag_descriptions::kTabClosureMethodRefactorName,
     flag_descriptions::kTabClosureMethodRefactorDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabClosureMethodRefactor)},

#endif  // BUILDFLAG(IS_ANDROID)
=======
    {"toolbar-iph-android", flag_descriptions::kToolbarIphAndroidName,
     flag_descriptions::kToolbarIphAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kToolbarIphAndroid)},
    {"toolbar-mic-iph-android", flag_descriptions::kToolbarMicIphAndroidName,
     flag_descriptions::kToolbarMicIphAndroidDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kToolbarMicIphAndroid,
                                    kIphMicToolbarVariations,
                                    "ToolbarMicIphAndroid")},
    {"theme-refactor-android", flag_descriptions::kThemeRefactorAndroidName,
     flag_descriptions::kThemeRefactorAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kThemeRefactorAndroid)},
#endif  // OS_ANDROID
>>>>>>> chromium
    {"disallow-doc-written-script-loads",
     flag_descriptions::kDisallowDocWrittenScriptsUiName,
     flag_descriptions::kDisallowDocWrittenScriptsUiDescription, kOsAll,
     // NOTE: if we want to add additional experiment entries for other
     // features controlled by kBlinkSettings, we'll need to add logic to
     // merge the flag values.
     ENABLE_DISABLE_VALUE_TYPE_AND_VALUE(
         blink::switches::kBlinkSettings,
         "disallowFetchForDocWrittenScriptsInMainFrame=true",
         blink::switches::kBlinkSettings,
         "disallowFetchForDocWrittenScriptsInMainFrame=false")},
<<<<<<< HEAD
    {"view-transition-layered-capture",
     flag_descriptions::kViewTransitionLayeredCaptureName,
     flag_descriptions::kViewTransitionLayeredCaptureDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kViewTransitionLayeredCapture)},
    {"view-transition-on-navigation",
     flag_descriptions::kViewTransitionOnNavigationName,
     flag_descriptions::kViewTransitionOnNavigationDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kViewTransitionOnNavigation)},
    {"view-transition-on-navigation-iframe",
     flag_descriptions::kViewTransitionOnNavigationIframeName,
     flag_descriptions::kViewTransitionOnNavigationIframeDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         blink::features::kViewTransitionOnNavigationForIframes)},
    {"view-transition-overflow-rect-from-surface",
     flag_descriptions::kViewTransitionOverflowRectFromSurfaceName,
     flag_descriptions::kViewTransitionOverflowRectFromSurfaceDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         blink::features::kViewTransitionOverflowRectFromSurface)},
#if BUILDFLAG(IS_WIN)
=======
    {"document-transition", flag_descriptions::kDocumentTransitionName,
     flag_descriptions::kDocumentTransitionDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kDocumentTransition)},
#if defined(OS_WIN)
>>>>>>> chromium
    {"use-winrt-midi-api", flag_descriptions::kUseWinrtMidiApiName,
     flag_descriptions::kUseWinrtMidiApiDescription, kOsWin,
     FEATURE_VALUE_TYPE(midi::features::kMidiManagerWinrt)},
#endif  // OS_WIN
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"cros-regions-mode", flag_descriptions::kCrosRegionsModeName,
     flag_descriptions::kCrosRegionsModeDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kCrosRegionsModeChoices)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if defined(TOOLKIT_VIEWS) || defined(OS_ANDROID)
    {"enable-autofill-credit-card-upload",
     flag_descriptions::kAutofillCreditCardUploadName,
     flag_descriptions::kAutofillCreditCardUploadDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillUpstream)},
#endif  // TOOLKIT_VIEWS || OS_ANDROID
    {"force-ui-direction", flag_descriptions::kForceUiDirectionName,
     flag_descriptions::kForceUiDirectionDescription, kOsAll,
     MULTI_VALUE_TYPE(kForceUIDirectionChoices)},
    {"force-text-direction", flag_descriptions::kForceTextDirectionName,
     flag_descriptions::kForceTextDirectionDescription, kOsAll,
     MULTI_VALUE_TYPE(kForceTextDirectionChoices)},
#if defined(OS_ANDROID)
    {"force-update-menu-type", flag_descriptions::kUpdateMenuTypeName,
     flag_descriptions::kUpdateMenuTypeDescription, kOsAndroid,
     MULTI_VALUE_TYPE(kForceUpdateMenuTypeChoices)},
    {"enable-inline-update-flow", flag_descriptions::kInlineUpdateFlowName,
     flag_descriptions::kInlineUpdateFlowDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kInlineUpdateFlow)},
    {"update-menu-item-custom-summary",
     flag_descriptions::kUpdateMenuItemCustomSummaryName,
     flag_descriptions::kUpdateMenuItemCustomSummaryDescription, kOsAndroid,
     SINGLE_VALUE_TYPE_AND_VALUE(
         switches::kForceShowUpdateMenuItemCustomSummary,
         "Custom Summary")},
    {"force-show-update-menu-badge", flag_descriptions::kUpdateMenuBadgeName,
     flag_descriptions::kUpdateMenuBadgeDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(switches::kForceShowUpdateMenuBadge)},
    {"set-market-url-for-testing",
     flag_descriptions::kSetMarketUrlForTestingName,
     flag_descriptions::kSetMarketUrlForTestingDescription, kOsAndroid,
     SINGLE_VALUE_TYPE_AND_VALUE(switches::kMarketUrlForTesting,
                                 "https://play.google.com/store/apps/"
                                 "details?id=com.android.chrome")},
#endif  // OS_ANDROID
    {"enable-tls13-early-data", flag_descriptions::kEnableTLS13EarlyDataName,
     flag_descriptions::kEnableTLS13EarlyDataDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kEnableTLS13EarlyData)},
<<<<<<< HEAD
    {"enable-tls13-kyber", flag_descriptions::kEnableTLS13KyberName,
     flag_descriptions::kEnableTLS13KyberDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kPostQuantumKyber)},
    {"use-ml-kem", flag_descriptions::kUseMLKEMName,
     flag_descriptions::kUseMLKEMDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kUseMLKEM)},
#if BUILDFLAG(IS_ANDROID)
    {"feed-loading-placeholder", flag_descriptions::kFeedLoadingPlaceholderName,
     flag_descriptions::kFeedLoadingPlaceholderDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kFeedLoadingPlaceholder)},
    {"feed-signed-out-view-demotion",
     flag_descriptions::kFeedSignedOutViewDemotionName,
     flag_descriptions::kFeedSignedOutViewDemotionDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kFeedSignedOutViewDemotion)},
    {"web-feed-awareness", flag_descriptions::kWebFeedAwarenessName,
     flag_descriptions::kWebFeedAwarenessDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(feed::kWebFeedAwareness,
                                    kWebFeedAwarenessVariations,
                                    "WebFeedAwareness")},
    {"web-feed-onboarding", flag_descriptions::kWebFeedOnboardingName,
     flag_descriptions::kWebFeedOnboardingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kWebFeedOnboarding)},
    {"web-feed-sort", flag_descriptions::kWebFeedSortName,
     flag_descriptions::kWebFeedSortDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kWebFeedSort)},
    {"xsurface-metrics-reporting",
     flag_descriptions::kXsurfaceMetricsReportingName,
     flag_descriptions::kXsurfaceMetricsReportingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kXsurfaceMetricsReporting)},
    {"feed-containment", flag_descriptions::kFeedContainmentName,
     flag_descriptions::kFeedContainmentDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kFeedContainment)},
    {"feed-discofeed-endpoint", flag_descriptions::kFeedDiscoFeedEndpointName,
     flag_descriptions::kFeedDiscoFeedEndpointDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kDiscoFeedEndpoint)},
    {"feed-dynamic-colors", flag_descriptions::kFeedDynamicColorsName,
     flag_descriptions::kFeedDynamicColorsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kFeedDynamicColors)},
    {"feed-follow-ui-update", flag_descriptions::kFeedFollowUiUpdateName,
     flag_descriptions::kFeedFollowUiUpdateDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kFeedFollowUiUpdate)},
    {"refresh-feed-on-start", flag_descriptions::kRefreshFeedOnRestartName,
     flag_descriptions::kRefreshFeedOnRestartDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kRefreshFeedOnRestart)},
#endif  // BUILDFLAG(IS_ANDROID)
    {"enable-force-dark", flag_descriptions::kAutoWebContentsDarkModeName,
     flag_descriptions::kAutoWebContentsDarkModeDescription, kOsAll,
#if BUILDFLAG(IS_CHROMEOS)
     // TODO(crbug.com/40651782): Investigate crash reports and
=======
    {"post-quantum-cecpq2", flag_descriptions::kPostQuantumCECPQ2Name,
     flag_descriptions::kPostQuantumCECPQ2Description, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kPostQuantumCECPQ2)},
#if defined(OS_ANDROID)
    {"interest-feed-v2", flag_descriptions::kInterestFeedV2Name,
     flag_descriptions::kInterestFeedV2Description, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kInterestFeedV2)},
    {"feed-interactive-refresh", flag_descriptions::kFeedInteractiveRefreshName,
     flag_descriptions::kFeedInteractiveRefreshDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kFeedInteractiveRefresh)},
    {"feed-v2-hearts", flag_descriptions::kInterestFeedV2HeartsName,
     flag_descriptions::kInterestFeedV2HeartsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kInterestFeedV2Hearts)},
    {"feed-v2-autoplay", flag_descriptions::kInterestFeedV2AutoplayName,
     flag_descriptions::kInterestFeedV2AutoplayDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kInterestFeedV2Autoplay)},
    {"web-feed", flag_descriptions::kWebFeedName,
     flag_descriptions::kWebFeedDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(feed::kWebFeed,
                                    kWebFeedVariations,
                                    "WebFeed")},
    {"xsurface-metrics-reporting",
     flag_descriptions::kXsurfaceMetricsReportingName,
     flag_descriptions::kXsurfaceMetricsReportingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kWebFeed)},
    {"interest-feed-v1-clicks-and-views-cond-upload",
     flag_descriptions::kInterestFeedV1ClickAndViewActionsConditionalUploadName,
     flag_descriptions::
         kInterestFeedV1ClickAndViewActionsConditionalUploadDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kInterestFeedV1ClicksAndViewsConditionalUpload)},
    {"interest-feed-v2-clicks-and-views-cond-upload",
     flag_descriptions::kInterestFeedV2ClickAndViewActionsConditionalUploadName,
     flag_descriptions::
         kInterestFeedV2ClickAndViewActionsConditionalUploadDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(feed::kInterestFeedV2ClicksAndViewsConditionalUpload)},
#endif  // OS_ANDROID
    {"PasswordImport", flag_descriptions::kPasswordImportName,
     flag_descriptions::kPasswordImportDescription, kOsAll,
     FEATURE_VALUE_TYPE(password_manager::features::kPasswordImport)},
    {"enable-force-dark", flag_descriptions::kForceWebContentsDarkModeName,
     flag_descriptions::kForceWebContentsDarkModeDescription, kOsAll,
#if BUILDFLAG(IS_CHROMEOS_ASH)
     // TODO(https://crbug.com/1011696): Investigate crash reports and
>>>>>>> chromium
     // re-enable variations for ChromeOS.
     FEATURE_VALUE_TYPE(blink::features::kForceWebContentsDarkMode)},
#else
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kForceWebContentsDarkMode,
                                    kForceDarkVariations,
                                    "ForceDarkVariations")},
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(IS_ANDROID)
    {"enable-accessibility-deprecate-type-announce",
     flag_descriptions::kAccessibilityDeprecateTypeAnnounceName,
     flag_descriptions::kAccessibilityDeprecateTypeAnnounceDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAccessibilityDeprecateTypeAnnounce)},
    {"enable-accessibility-include-long-click-action",
     flag_descriptions::kAccessibilityIncludeLongClickActionName,
     flag_descriptions::kAccessibilityIncludeLongClickActionDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAccessibilityIncludeLongClickAction)},
    {"enable-accessibility-page-zoom-enhancements",
     flag_descriptions::kAccessibilityPageZoomEnhancementsName,
     flag_descriptions::kAccessibilityPageZoomEnhancementsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAccessibilityPageZoomEnhancements)},
    {"enable-accessibility-unified-snapshots",
     flag_descriptions::kAccessibilityUnifiedSnapshotsName,
     flag_descriptions::kAccessibilityUnifiedSnapshotsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAccessibilityUnifiedSnapshots)},
    {"enable-accessibility-manage-broadcast-recevier-on-background",
     flag_descriptions::kAccessibilityManageBroadcastReceiverOnBackgroundName,
     flag_descriptions::
         kAccessibilityManageBroadcastReceiverOnBackgroundDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         features::kAccessibilityManageBroadcastReceiverOnBackground)},
    {"enable-smart-zoom", flag_descriptions::kSmartZoomName,
     flag_descriptions::kSmartZoomDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kSmartZoom)},
#endif  // BUILDFLAG(IS_ANDROID)
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if defined(OS_ANDROID)
    {"enable-android-layout-change-tab-reparenting",
     flag_descriptions::kAndroidLayoutChangeTabReparentingName,
     flag_descriptions::kAndroidLayoutChangeTabReparentingDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAndroidLayoutChangeTabReparenting)},
#endif  // OS_ANDROID
>>>>>>> chromium
    {"enable-experimental-accessibility-language-detection",
     flag_descriptions::kExperimentalAccessibilityLanguageDetectionName,
     flag_descriptions::kExperimentalAccessibilityLanguageDetectionDescription,
     kOsAll,
     SINGLE_VALUE_TYPE(
         ::switches::kEnableExperimentalAccessibilityLanguageDetection)},
    {"enable-experimental-accessibility-language-detection-dynamic",
     flag_descriptions::kExperimentalAccessibilityLanguageDetectionDynamicName,
     flag_descriptions::
         kExperimentalAccessibilityLanguageDetectionDynamicDescription,
     kOsAll,
     SINGLE_VALUE_TYPE(
         ::switches::kEnableExperimentalAccessibilityLanguageDetectionDynamic)},
    {"enable-aria-element-reflection",
     flag_descriptions::kAriaElementReflectionName,
     flag_descriptions::kAriaElementReflectionDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kEnableAriaElementReflection)},
<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"enable-cros-autocorrect-params-tuning",
     flag_descriptions::kAutocorrectParamsTuningName,
     flag_descriptions::kAutocorrectParamsTuningDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAutocorrectParamsTuning)},
    {"enable-cros-autocorrect-by-default",
     flag_descriptions::kAutocorrectByDefaultName,
     flag_descriptions::kAutocorrectByDefaultDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAutocorrectByDefault)},
    {"enable-cros-first-party-vietnamese-input",
     flag_descriptions::kFirstPartyVietnameseInputName,
     flag_descriptions::kFirstPartyVietnameseInputDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFirstPartyVietnameseInput)},
    {"enable-cros-hindi-inscript-layout",
     flag_descriptions::kHindiInscriptLayoutName,
     flag_descriptions::kHindiInscriptLayoutDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHindiInscriptLayout)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-cros-ime-assist-autocorrect",
     flag_descriptions::kImeAssistAutocorrectName,
     flag_descriptions::kImeAssistAutocorrectDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAssistAutoCorrect)},
    {"enable-cros-ime-assist-emoji-enhanced",
     flag_descriptions::kImeAssistEmojiEnhancedName,
     flag_descriptions::kImeAssistEmojiEnhancedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAssistEmojiEnhanced)},
>>>>>>> chromium
    {"enable-cros-ime-assist-multi-word",
     flag_descriptions::kImeAssistMultiWordName,
     flag_descriptions::kImeAssistMultiWordDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAssistMultiWord)},
    {"enable-cros-ime-assist-multi-word-expanded",
     flag_descriptions::kImeAssistMultiWordExpandedName,
     flag_descriptions::kImeAssistMultiWordExpandedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAssistMultiWordExpanded)},
    {"enable-cros-ime-assist-personal-info",
     flag_descriptions::kImeAssistPersonalInfoName,
     flag_descriptions::kImeAssistPersonalInfoDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAssistPersonalInfo)},
    {"enable-cros-ime-emoji-suggest-addition",
     flag_descriptions::kImeEmojiSuggestAdditionName,
     flag_descriptions::kImeEmojiSuggestAdditionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kEmojiSuggestAddition)},
    {"enable-cros-ime-mozc-proto", flag_descriptions::kImeMozcProtoName,
     flag_descriptions::kImeMozcProtoDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kImeMozcProto)},
    {"enable-cros-ime-service-decoder",
     flag_descriptions::kImeServiceDecoderName,
     flag_descriptions::kImeServiceDecoderDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kImeMojoDecoder)},
    {"enable-cros-ime-system-emoji-picker",
     flag_descriptions::kImeSystemEmojiPickerName,
     flag_descriptions::kImeSystemEmojiPickerDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kImeSystemEmojiPicker)},
    {"enable-cros-ime-system-emoji-picker-clipboard",
     flag_descriptions::kImeSystemEmojiPickerClipboardName,
     flag_descriptions::kImeSystemEmojiPickerClipboardDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kImeSystemEmojiPickerClipboard)},
    {"enable-cros-language-settings-update-2",
     flag_descriptions::kCrosLanguageSettingsUpdate2Name,
     flag_descriptions::kCrosLanguageSettingsUpdate2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kLanguageSettingsUpdate2)},
    {"enable-cros-language-settings-ime-options-in-settings",
     flag_descriptions::kCrosLanguageSettingsImeOptionsInSettingsName,
     flag_descriptions::kCrosLanguageSettingsImeOptionsInSettingsDescription,
     kOsCrOS, FEATURE_VALUE_TYPE(chromeos::features::kImeOptionsInSettings)},
    {"enable-cros-multilingual-typing",
     flag_descriptions::kMultilingualTypingName,
     flag_descriptions::kMultilingualTypingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kMultilingualTyping)},
    {"enable-cros-on-device-grammar-check",
     flag_descriptions::kCrosOnDeviceGrammarCheckName,
     flag_descriptions::kCrosOnDeviceGrammarCheckDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kOnDeviceGrammarCheck)},
    {"enable-cros-system-latin-physical-typing",
     flag_descriptions::kSystemLatinPhysicalTypingName,
     flag_descriptions::kSystemLatinPhysicalTypingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kSystemLatinPhysicalTyping)},
    {"enable-cros-virtual-keyboard-bordered-key",
     flag_descriptions::kVirtualKeyboardBorderedKeyName,
     flag_descriptions::kVirtualKeyboardBorderedKeyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kVirtualKeyboardBorderedKey)},
    {"enable-cros-virtual-keyboard-multipaste",
     flag_descriptions::kVirtualKeyboardMultipasteName,
     flag_descriptions::kVirtualKeyboardMultipasteDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kVirtualKeyboardMultipaste)},
    {"enable-experimental-accessibility-dictation-extension",
     flag_descriptions::kExperimentalAccessibilityDictationExtensionName,
     flag_descriptions::kExperimentalAccessibilityDictationExtensionDescription,
     kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::features::kImeSystemEmojiPickerVariantGrouping)},
    {"enable-cros-ime-us-english-model-update",
     flag_descriptions::kImeUsEnglishModelUpdateName,
     flag_descriptions::kImeUsEnglishModelUpdateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kImeUsEnglishModelUpdate)},
    {"enable-cros-ime-korean-only-mode-switch-on-right-alt",
     flag_descriptions::kImeKoreanOnlyModeSwitchOnRightAltName,
     flag_descriptions::kImeKoreanOnlyModeSwitchOnRightAltDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kImeKoreanOnlyModeSwitchOnRightAlt)},
    {"enable-cros-ime-switch-check-connection-status",
     flag_descriptions::kImeSwitchCheckConnectionStatusName,
     flag_descriptions::kImeSwitchCheckConnectionStatusDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kImeSwitchCheckConnectionStatus)},
    {"enable-cros-japanese-os-settings",
     flag_descriptions::kJapaneseOSSettingsName,
     flag_descriptions::kJapaneseOSSettingsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kJapaneseOSSettings)},
    {"enable-cros-system-japanese-physical-typing",
     flag_descriptions::kSystemJapanesePhysicalTypingName,
     flag_descriptions::kSystemJapanesePhysicalTypingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSystemJapanesePhysicalTyping)},
    {"enable-cros-virtual-keyboard-global-emoji-preferences",
     flag_descriptions::kVirtualKeyboardGlobalEmojiPreferencesName,
     flag_descriptions::kVirtualKeyboardGlobalEmojiPreferencesDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVirtualKeyboardGlobalEmojiPreferences)},
    {"enable-accessibility-bounce-keys",
     flag_descriptions::kAccessibilityBounceKeysName,
     flag_descriptions::kAccessibilityBounceKeysDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityBounceKeys)},
    {"enable-accessibility-slow-keys",
     flag_descriptions::kAccessibilitySlowKeysName,
     flag_descriptions::kAccessibilitySlowKeysDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilitySlowKeys)},
    {"enable-experimental-accessibility-dictation-context-checking",
     flag_descriptions::kExperimentalAccessibilityDictationContextCheckingName,
     flag_descriptions::
         kExperimentalAccessibilityDictationContextCheckingDescription,
=======
     SINGLE_VALUE_TYPE(
         ::switches::kEnableExperimentalAccessibilityDictationExtension)},
    {"enable-experimental-accessibility-dictation-listening",
     flag_descriptions::kExperimentalAccessibilityDictationListeningName,
     flag_descriptions::kExperimentalAccessibilityDictationListeningDescription,
>>>>>>> chromium
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         features::kExperimentalAccessibilityDictationListening)},
    {"enable-experimental-accessibility-dictation-offline",
     flag_descriptions::kExperimentalAccessibilityDictationOfflineName,
     flag_descriptions::kExperimentalAccessibilityDictationOfflineDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kExperimentalAccessibilityDictationOffline)},
    {"enable-experimental-accessibility-switch-access-text",
     flag_descriptions::kExperimentalAccessibilitySwitchAccessTextName,
     flag_descriptions::kExperimentalAccessibilitySwitchAccessTextDescription,
     kOsCrOS,
     SINGLE_VALUE_TYPE(
         ::switches::kEnableExperimentalAccessibilitySwitchAccessText)},
    {"enable-switch-access-point-scanning",
     flag_descriptions::kSwitchAccessPointScanningName,
     flag_descriptions::kSwitchAccessPointScanningDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableSwitchAccessPointScanning)},
    {"enable-experimental-accessibility-switch-access-setup-guide",
     flag_descriptions::kExperimentalAccessibilitySwitchAccessSetupGuideName,
     flag_descriptions::
         kExperimentalAccessibilitySwitchAccessSetupGuideDescription,
     kOsCrOS,
     SINGLE_VALUE_TYPE(
         ::switches::kEnableExperimentalAccessibilitySwitchAccessSetupGuide)},
    {"enable-experimental-kernel-vm-support",
     flag_descriptions::kKernelnextVMsName,
     flag_descriptions::kKernelnextVMsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kKernelnextVMs)},
    {"enable-magnifier-panning-improvements",
     flag_descriptions::kMagnifierPanningImprovementsName,
     flag_descriptions::kMagnifierPanningImprovementsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kMagnifierPanningImprovements)},
    {"enable-magnifier-continuous-mouse-following-mode-setting",
     flag_descriptions::kMagnifierContinuousMouseFollowingModeSettingName,
     flag_descriptions::
         kMagnifierContinuousMouseFollowingModeSettingDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         features::kMagnifierContinuousMouseFollowingModeSetting)},
    {"enable-system-proxy-for-system-services",
     flag_descriptions::kSystemProxyForSystemServicesName,
     flag_descriptions::kSystemProxyForSystemServicesDescription, kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::features::kSystemProxyForSystemServices)},
    {"system-shortcut-behavior", flag_descriptions::kSystemShortcutBehaviorName,
     flag_descriptions::kSystemShortcutBehaviorDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kSystemShortcutBehavior,
                                    kSystemShortcutBehaviorVariations,
                                    "SystemShortcutBehavior")},
#endif  // BUILDFLAG(IS_CHROMEOS)
    {"enable-cros-touch-text-editing-redesign",
     flag_descriptions::kTouchTextEditingRedesignName,
     flag_descriptions::kTouchTextEditingRedesignDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kTouchTextEditingRedesign)},
#if BUILDFLAG(IS_MAC)
    {"enable-extensible-enterprise-sso",
     flag_descriptions::kEnableExtensibleEnterpriseSSOName,
     flag_descriptions::kEnableExtensibleEnterpriseSSODescription, kOsMac,
     FEATURE_VALUE_TYPE(enterprise_auth::kEnableExtensibleEnterpriseSSO)},
    {"enable-retry-capture-device-enumeration-on-crash",
     flag_descriptions::kRetryGetVideoCaptureDeviceInfosName,
     flag_descriptions::kRetryGetVideoCaptureDeviceInfosDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kRetryGetVideoCaptureDeviceInfos)},
=======
     FEATURE_VALUE_TYPE(chromeos::features::kSystemProxyForSystemServices)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if defined(OS_MAC)
>>>>>>> chromium
    {"enable-immersive-fullscreen-toolbar",
     flag_descriptions::kImmersiveFullscreenName,
     flag_descriptions::kImmersiveFullscreenDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kImmersiveFullscreen)},
#endif  // OS_MAC
    {"enable-web-payments-experimental-features",
     flag_descriptions::kWebPaymentsExperimentalFeaturesName,
     flag_descriptions::kWebPaymentsExperimentalFeaturesDescription, kOsAll,
     FEATURE_VALUE_TYPE(payments::features::kWebPaymentsExperimentalFeatures)},
    {"enable-web-payments-minimal-ui",
     flag_descriptions::kWebPaymentsMinimalUIName,
     flag_descriptions::kWebPaymentsMinimalUIDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebPaymentsMinimalUI)},
    {"enable-debug-for-store-billing",
     flag_descriptions::kAppStoreBillingDebugName,
     flag_descriptions::kAppStoreBillingDebugDescription, kOsAll,
     FEATURE_VALUE_TYPE(payments::features::kAppStoreBillingDebug)},
    {"enable-debug-for-secure-payment-confirmation",
     flag_descriptions::kSecurePaymentConfirmationDebugName,
     flag_descriptions::kSecurePaymentConfirmationDebugDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kSecurePaymentConfirmationDebug)},
<<<<<<< HEAD
    {"enable-network-and-issuer-icons-for-secure-payment-confirmation",
     flag_descriptions::kSecurePaymentConfirmationNetworkAndIssuerIconsName,
     flag_descriptions::
         kSecurePaymentConfirmationNetworkAndIssuerIconsDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         blink::features::kSecurePaymentConfirmationNetworkAndIssuerIcons,
         kSecurePaymentConfirmationNetworkAndIssuerIconsOptions,
         "SecurePaymentConfirmationNetworkAndIssuerIcons")},
    {"enable-secure-payment-confirmation-browser-bound-key",
     flag_descriptions::kSecurePaymentConfirmationBrowserBoundKeysName,
     flag_descriptions::kSecurePaymentConfirmationBrowserBoundKeysDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         blink::features::kSecurePaymentConfirmationBrowserBoundKeys)},
#if BUILDFLAG(IS_ANDROID)
    {"show-ready-to-pay-debug-info",
     flag_descriptions::kShowReadyToPayDebugInfoName,
     flag_descriptions::kShowReadyToPayDebugInfoDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(payments::android::kShowReadyToPayDebugInfo)},
#endif  // BUILDFLAG(IS_ANDROID)
    {"mutation-events", flag_descriptions::kMutationEventsName,
     flag_descriptions::kMutationEventsDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kMutationEvents)},
    {"keyboard-focusable-scrollers",
     flag_descriptions::kKeyboardFocusableScrollersName,
     flag_descriptions::kKeyboardFocusableScrollersDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kKeyboardFocusableScrollers)},
    {"fill-on-account-select", flag_descriptions::kFillOnAccountSelectName,
     flag_descriptions::kFillOnAccountSelectDescription, kOsAll,
     FEATURE_VALUE_TYPE(password_manager::features::kFillOnAccountSelect)},
#if BUILDFLAG(IS_CHROMEOS)
    {"arc-aaudio-mmap-low-latency",
     flag_descriptions::kArcAAudioMMAPLowLatencyName,
     flag_descriptions::kArcAAudioMMAPLowLatencyDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootArcVmAAudioMMAPLowLatency")},
=======
    {"fill-on-account-select", flag_descriptions::kFillOnAccountSelectName,
     flag_descriptions::kFillOnAccountSelectDescription, kOsAll,
     FEATURE_VALUE_TYPE(password_manager::features::kFillOnAccountSelect)},
#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"arc-custom-tabs-experiment",
     flag_descriptions::kArcCustomTabsExperimentName,
     flag_descriptions::kArcCustomTabsExperimentDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kCustomTabsExperimentFeature)},
<<<<<<< HEAD
    {kArcEnableAttestationFlag, flag_descriptions::kArcEnableAttestationName,
     flag_descriptions::kArcEnableAttestationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kEnableArcAttestation)},
    {kArcEnableVirtioBlkForDataInternalName,
     flag_descriptions::kArcEnableVirtioBlkForDataName,
     flag_descriptions::kArcEnableVirtioBlkForDataDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kEnableVirtioBlkForData)},
    {"arc-extend-intent-anr-timeout",
     flag_descriptions::kArcExtendIntentAnrTimeoutName,
     flag_descriptions::kArcExtendIntentAnrTimeoutDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kExtendIntentAnrTimeout)},
    {"arc-extend-service-anr-timeout",
     flag_descriptions::kArcExtendServiceAnrTimeoutName,
     flag_descriptions::kArcExtendServiceAnrTimeoutDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kExtendServiceAnrTimeout)},
    {"arc-external-storage-access",
     flag_descriptions::kArcExternalStorageAccessName,
     flag_descriptions::kArcExternalStorageAccessDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kExternalStorageAccess)},
    {"arc-friendlier-error-dialog",
     flag_descriptions::kArcFriendlierErrorDialogName,
     flag_descriptions::kArcFriendlierErrorDialogDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kEnableFriendlierErrorDialog)},
=======
    {"arc-documents-provider-unknown-size",
     flag_descriptions::kArcDocumentsProviderUnknownSizeName,
     flag_descriptions::kArcDocumentsProviderUnknownSizeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kDocumentsProviderUnknownSizeFeature)},
    {"arc-enable-usap", flag_descriptions::kArcEnableUsapName,
     flag_descriptions::kArcEnableUsapDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kEnableUsap)},
    {"arc-file-picker-experiment",
     flag_descriptions::kArcFilePickerExperimentName,
     flag_descriptions::kArcFilePickerExperimentDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kFilePickerExperimentFeature)},
    {"arc-image-copy-paste-compat",
     flag_descriptions::kArcImageCopyPasteCompatName,
     flag_descriptions::kArcImageCopyPasteCompatDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kImageCopyPasteCompatFeature)},
    {"arc-keyboard-shortcut-helper-integration",
     flag_descriptions::kArcKeyboardShortcutHelperIntegrationName,
     flag_descriptions::kArcKeyboardShortcutHelperIntegrationDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kKeyboardShortcutHelperIntegrationFeature)},
>>>>>>> chromium
    {"arc-native-bridge-toggle", flag_descriptions::kArcNativeBridgeToggleName,
     flag_descriptions::kArcNativeBridgeToggleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kNativeBridgeToggleFeature)},
    {"arc-native-bridge-64bit-support-experiment",
     flag_descriptions::kArcNativeBridge64BitSupportExperimentName,
     flag_descriptions::kArcNativeBridge64BitSupportExperimentDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kNativeBridge64BitSupportExperimentFeature)},
    {"arc-rt-vcpu-dual-core", flag_descriptions::kArcRtVcpuDualCoreName,
     flag_descriptions::kArcRtVcpuDualCoreDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kRtVcpuDualCore)},
    {"arc-rt-vcpu-quad-core", flag_descriptions::kArcRtVcpuQuadCoreName,
     flag_descriptions::kArcRtVcpuQuadCoreDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kRtVcpuQuadCore)},
<<<<<<< HEAD
    {"arc-switch-to-keymint-daemon",
     flag_descriptions::kArcSwitchToKeyMintDaemonName,
     flag_descriptions::kArcSwitchToKeyMintDaemonDesc, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootArcSwitchToKeyMintDaemon")},
    {"arc-switch-to-keymint-on-t",
     flag_descriptions::kArcSwitchToKeyMintOnTName,
     flag_descriptions::kArcSwitchToKeyMintOnTDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kSwitchToKeyMintOnT)},
    {"arc-switch-to-keymint-on-t-override",
     flag_descriptions::kArcSwitchToKeyMintOnTOverrideName,
     flag_descriptions::kArcSwitchToKeyMintOnTOverrideDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kSwitchToKeyMintOnTOverride)},
    {"arc-sync-install-priority",
     flag_descriptions::kArcSyncInstallPriorityName,
     flag_descriptions::kArcSyncInstallPriorityDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kSyncInstallPriority)},
    {"arc-unthrottle-on-active-audio-v2",
     flag_descriptions::kArcUnthrottleOnActiveAudioV2Name,
     flag_descriptions::kArcUnthrottleOnActiveAudioV2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kUnthrottleOnActiveAudioV2)},
    {"arc-vmm-swap-keyboard-shortcut",
     flag_descriptions::kArcVmmSwapKBShortcutName,
     flag_descriptions::kArcVmmSwapKBShortcutDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kVmmSwapKeyboardShortcut)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
    {kArcUseHighMemoryDalvikProfileInternalName,
     flag_descriptions::kArcUseHighMemoryDalvikProfileName,
     flag_descriptions::kArcUseHighMemoryDalvikProfileDesc, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kUseHighMemoryDalvikProfile)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"enable-generic-sensor-extra-classes",
     flag_descriptions::kEnableGenericSensorExtraClassesName,
     flag_descriptions::kEnableGenericSensorExtraClassesDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kGenericSensorExtraClasses)},
    {"expensive-background-timer-throttling",
     flag_descriptions::kExpensiveBackgroundTimerThrottlingName,
     flag_descriptions::kExpensiveBackgroundTimerThrottlingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kExpensiveBackgroundTimerThrottling)},

#if BUILDFLAG(IS_CHROMEOS)
    {ui_devtools::switches::kEnableUiDevTools,
     flag_descriptions::kUiDevToolsName,
     flag_descriptions::kUiDevToolsDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(ui_devtools::switches::kEnableUiDevTools)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if defined(OS_ANDROID)
    {"enable-autofill-manual-fallback",
     flag_descriptions::kAutofillManualFallbackAndroidName,
     flag_descriptions::kAutofillManualFallbackAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillManualFallbackAndroid)},

<<<<<<< HEAD
    {"suppress-autofill-via-accessibility",
     flag_descriptions::kAutofillDeprecateAccessibilityApiName,
     flag_descriptions::kAutofillDeprecateAccessibilityApiDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAndroidAutofillDeprecateAccessibilityApi)},
=======
    {"enable-autofill-refresh-style",
     flag_descriptions::kEnableAutofillRefreshStyleName,
     flag_descriptions::kEnableAutofillRefreshStyleDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillRefreshStyleAndroid)},
>>>>>>> chromium
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-touchscreen-calibration",
     flag_descriptions::kTouchscreenCalibrationName,
     flag_descriptions::kTouchscreenCalibrationDescription, kOsCrOS,
<<<<<<< HEAD
     SINGLE_VALUE_TYPE(ash::switches::kEnableTouchCalibrationSetting)},
    {"enable-touchscreen-mapping", flag_descriptions::kTouchscreenMappingName,
     flag_descriptions::kTouchscreenMappingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableTouchscreenMappingExperience)},
    {"force-control-face-ae", flag_descriptions::kForceControlFaceAeName,
     flag_descriptions::kForceControlFaceAeDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kForceControlFaceAeChoices)},
    {"auto-framing-override", flag_descriptions::kAutoFramingOverrideName,
     flag_descriptions::kAutoFramingOverrideDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kAutoFramingOverrideChoices)},
    {"face-retouch-override", flag_descriptions::kFaceRetouchOverrideName,
     flag_descriptions::kFaceRetouchOverrideDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kFaceRetouchOverrideChoices)},
    {"camera-app-pdf-ocr", flag_descriptions::kCameraAppPdfOcrName,
     flag_descriptions::kCameraAppPdfOcrDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCameraAppPdfOcr)},
    {"camera-app-preview-ocr", flag_descriptions::kCameraAppPreviewOcrName,
     flag_descriptions::kCameraAppPreviewOcrDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCameraAppPreviewOcr)},
    {"crostini-gpu-support", flag_descriptions::kCrostiniGpuSupportName,
     flag_descriptions::kCrostiniGpuSupportDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrostiniGpuSupport)},
    {"file-transfer-enterprise-connector",
     flag_descriptions::kFileTransferEnterpriseConnectorName,
     flag_descriptions::kFileTransferEnterpriseConnectorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kFileTransferEnterpriseConnector)},
    {"file-transfer-enterprise-connector-ui",
     flag_descriptions::kFileTransferEnterpriseConnectorUIName,
     flag_descriptions::kFileTransferEnterpriseConnectorUIDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kFileTransferEnterpriseConnectorUI)},
    {"files-conflict-dialog", flag_descriptions::kFilesConflictDialogName,
     flag_descriptions::kFilesConflictDialogDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFilesConflictDialog)},
    {"files-kernel-drivers", flag_descriptions::kFilesKernelDriversName,
     flag_descriptions::kFilesKernelDriversDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFilesKernelDrivers)},
    {"files-local-image-search", flag_descriptions::kFilesLocalImageSearchName,
     flag_descriptions::kFilesLocalImageSearchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFilesLocalImageSearch)},
    {"files-materialized-views", flag_descriptions::kFilesMaterializedViewsName,
     flag_descriptions::kFilesMaterializedViewsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFilesMaterializedViews)},
=======
     SINGLE_VALUE_TYPE(chromeos::switches::kEnableTouchCalibrationSetting)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"prefer-constant-frame-rate",
     flag_descriptions::kPreferConstantFrameRateName,
     flag_descriptions::kPreferConstantFrameRateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kPreferConstantFrameRate)},
    {"force-control-face-ae", flag_descriptions::kForceControlFaceAeName,
     flag_descriptions::kForceControlFaceAeDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kForceControlFaceAeChoices)},
    {"crostini-gpu-support", flag_descriptions::kCrostiniGpuSupportName,
     flag_descriptions::kCrostiniGpuSupportDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrostiniGpuSupport)},
    {"disable-camera-frame-rotation-at-source",
     flag_descriptions::kDisableCameraFrameRotationAtSourceName,
     flag_descriptions::kDisableCameraFrameRotationAtSourceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::features::kDisableCameraFrameRotationAtSource)},
    {"drive-fs-bidirectional-native-messaging",
     flag_descriptions::kDriveFsBidirectionalNativeMessagingName,
     flag_descriptions::kDriveFsBidirectionalNativeMessagingDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::features::kDriveFsBidirectionalNativeMessaging)},
    {"files-archivemount", flag_descriptions::kFilesArchivemountName,
     flag_descriptions::kFilesArchivemountDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesArchivemount)},
    {"files-banner-framework", flag_descriptions::kFilesBannerFrameworkName,
     flag_descriptions::kFilesBannerFrameworkDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesBannerFramework)},
    {"files-filters-in-recents", flag_descriptions::kFiltersInRecentsName,
     flag_descriptions::kFiltersInRecentsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFiltersInRecents)},
>>>>>>> chromium
    {"files-single-partition-format",
     flag_descriptions::kFilesSinglePartitionFormatName,
     flag_descriptions::kFilesSinglePartitionFormatDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesSinglePartitionFormat)},
    {"files-swa", flag_descriptions::kFilesSWAName,
     flag_descriptions::kFilesSWADescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesSWA)},
    {"files-trash", flag_descriptions::kFilesTrashName,
     flag_descriptions::kFilesTrashDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesTrash)},
    {"files-zip-mount", flag_descriptions::kFilesZipMountName,
     flag_descriptions::kFilesZipMountDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesZipMount)},
    {"files-zip-pack", flag_descriptions::kFilesZipPackName,
     flag_descriptions::kFilesZipPackDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesZipPack)},
    {"files-zip-unpack", flag_descriptions::kFilesZipUnpackName,
     flag_descriptions::kFilesZipUnpackDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kFilesZipUnpack)},
    {"force-spectre-v2-mitigation",
     flag_descriptions::kForceSpectreVariant2MitigationName,
     flag_descriptions::kForceSpectreVariant2MitigationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(
         sandbox::policy::features::kForceSpectreVariant2Mitigation)},
    {"spectre-v2-mitigation", flag_descriptions::kSpectreVariant2MitigationName,
     flag_descriptions::kSpectreVariant2MitigationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(sandbox::policy::features::kSpectreVariant2Mitigation)},
    {"eche-swa", flag_descriptions::kEcheSWAName,
     flag_descriptions::kEcheSWADescription, kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::features::kEcheSWA)},
    {"eche-launcher", flag_descriptions::kEcheLauncherName,
     flag_descriptions::kEcheLauncherDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheLauncher)},
    {"eche-launcher-app-icon-in-more-apps-button",
     flag_descriptions::kEcheLauncherIconsInMoreAppsButtonName,
     flag_descriptions::kEcheLauncherIconsInMoreAppsButtonDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheLauncherIconsInMoreAppsButton)},
    {"eche-launcher-list-view", flag_descriptions::kEcheLauncherListViewName,
     flag_descriptions::kEcheLauncherListViewDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheLauncherListView)},
    {"eche-swa-check-android-network-info",
     flag_descriptions::kEcheSWACheckAndroidNetworkInfoName,
     flag_descriptions::kEcheSWACheckAndroidNetworkInfoDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheSWACheckAndroidNetworkInfo)},
    {"eche-swa-process-android-accessibility-tree",
     flag_descriptions::kEcheSWAProcessAndroidAccessibilityTreeName,
     flag_descriptions::kEcheSWAProcessAndroidAccessibilityTreeDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kEcheSWAProcessAndroidAccessibilityTree)},
    {"eche-swa-debug-mode", flag_descriptions::kEcheSWADebugModeName,
     flag_descriptions::kEcheSWADebugModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheSWADebugMode)},
    {"eche-swa-disable-stun-server",
     flag_descriptions::kEcheSWADisableStunServerName,
     flag_descriptions::kEcheSWADisableStunServerDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheSWADisableStunServer)},
    {"eche-swa-measure-latency", flag_descriptions::kEcheSWAMeasureLatencyName,
     flag_descriptions::kEcheSWAMeasureLatencyDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheSWAMeasureLatency)},
    {"eche-swa-send-start-signaling",
     flag_descriptions::kEcheSWASendStartSignalingName,
     flag_descriptions::kEcheSWASendStartSignalingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEcheSWASendStartSignaling)},
    {"print-preview-cros-app", flag_descriptions::kPrintPreviewCrosAppName,
     flag_descriptions::kPrintPreviewCrosAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPrintPreviewCrosApp)},
    {kGlanceablesTimeManagementClassroomStudentViewInternalName,
     flag_descriptions::kGlanceablesTimeManagementClassroomStudentViewName,
     flag_descriptions::
         kGlanceablesTimeManagementClassroomStudentViewDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kGlanceablesTimeManagementClassroomStudentView)},
    {kGlanceablesTimeManagementTasksViewInternalName,
     flag_descriptions::kGlanceablesTimeManagementTasksViewName,
     flag_descriptions::kGlanceablesTimeManagementTasksViewDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kGlanceablesTimeManagementTasksView)},
    {"vc-dlc-ui", flag_descriptions::kVcDlcUiName,
     flag_descriptions::kVcDlcUiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVcDlcUi)},
    {"vc-studio-look", flag_descriptions::kVcStudioLookName,
     flag_descriptions::kVcStudioLookDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVcStudioLook)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
     FEATURE_VALUE_TYPE(chromeos::features::kEcheSWA)},
    {"eche-swa-resizing", flag_descriptions::kEcheSWAResizingName,
     flag_descriptions::kEcheSWAResizingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kEcheSWAResizing)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

#if defined(OS_WIN)
    {"gdi-text-printing", flag_descriptions::kGdiTextPrinting,
     flag_descriptions::kGdiTextPrintingDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kGdiTextPrinting)},
#endif  // defined(OS_WIN)

<<<<<<< HEAD
    {"android-app-integration-module",
     flag_descriptions::kAndroidAppIntegrationModuleName,
     flag_descriptions::kAndroidAppIntegrationModuleDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         segmentation_platform::features::kAndroidAppIntegrationModule,
         kAndroidAppIntegrationModuleVariations,
         "AndroidAppIntegrationModule")},

    {"android-app-integration-v2",
     flag_descriptions::kAndroidAppIntegrationV2Name,
     flag_descriptions::kAndroidAppIntegrationV2Description, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAndroidAppIntegrationV2)},

    {"new-tab-page-customization",
     flag_descriptions::kNewTabPageCustomizationName,
     flag_descriptions::kNewTabPageCustomizationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kNewTabPageCustomization)},

    {"android-app-integration-with-favicon",
     flag_descriptions::kAndroidAppIntegrationWithFaviconName,
     flag_descriptions::kAndroidAppIntegrationWithFaviconDescription,
=======
#if defined(OS_MAC)
    {"new-usb-backend", flag_descriptions::kNewUsbBackendName,
     flag_descriptions::kNewUsbBackendDescription, kOsMac,
     FEATURE_VALUE_TYPE(device::kNewUsbBackend)},
#endif  // defined(OS_MAC)

#if defined(OS_ANDROID)
    {"omnibox-adaptive-suggestions-count",
     flag_descriptions::kOmniboxAdaptiveSuggestionsCountName,
     flag_descriptions::kOmniboxAdaptiveSuggestionsCountDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kAdaptiveSuggestionsCount)},
    {"omnibox-assistant-voice-search",
     flag_descriptions::kOmniboxAssistantVoiceSearchName,
     flag_descriptions::kOmniboxAssistantVoiceSearchDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kOmniboxAssistantVoiceSearch,
                                    kOmniboxAssistantVoiceSearchVariations,
                                    "OmniboxAssistantVoiceSearch")},
    {"omnibox-compact-suggestions",
     flag_descriptions::kOmniboxCompactSuggestionsName,
     flag_descriptions::kOmniboxCompactSuggestionsDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kCompactSuggestions,
                                    kCompactSuggestionsVariations,
                                    "OmniboxCompactSuggestions")},
    {"omnibox-most-visited-tiles",
     flag_descriptions::kOmniboxMostVisitedTilesName,
     flag_descriptions::kOmniboxMostVisitedTilesDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kMostVisitedTiles)},
    {"omnibox-tab-switch-suggestions",
     flag_descriptions::kOmniboxTabSwitchSuggestionsName,
     flag_descriptions::kOmniboxTabSwitchSuggestionsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxTabSwitchSuggestions)},
    {"omnibox-clipboard-suggestions-content-hidden",
     flag_descriptions::kClipboardSuggestionContentHiddenName,
     flag_descriptions::kClipboardSuggestionContentHiddenDescription,
>>>>>>> chromium
     kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kClipboardSuggestionContentHidden)},
#endif  // defined(OS_ANDROID)

    {"omnibox-clobber-triggers-contextual-web-zero-suggest",
     flag_descriptions::kOmniboxClobberTriggersContextualWebZeroSuggestName,
     flag_descriptions::
         kOmniboxClobberTriggersContextualWebZeroSuggestDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kClobberTriggersContextualWebZeroSuggest,
         // On-clobber has the same variations and forcing IDs as on-focus.
         kOmniboxOnFocusSuggestionsContextualWebVariations,
         "OmniboxGoogleOnContent")},

    {"omnibox-on-device-head-suggestions-incognito",
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsIncognitoName,
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsIncognitoDescription,
     kOsAll, FEATURE_VALUE_TYPE(omnibox::kOnDeviceHeadProviderIncognito)},

<<<<<<< HEAD
    {"auxiliary-search-donation",
     flag_descriptions::kAuxiliarySearchDonationName,
     flag_descriptions::kAuxiliarySearchDonationDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kAuxiliarySearchDonation,
                                    kAuxiliarySearchDonationVariations,
                                    "AuxiliarySearchDonation")},

    {"disable-instance-limit", flag_descriptions::kDisableInstanceLimitName,
     flag_descriptions::kDisableInstanceLimitDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kDisableInstanceLimit)},

    {"change-unfocused-priority",
     flag_descriptions::kChangeUnfocusedPriorityName,
     flag_descriptions::kChangeUnfocusedPriorityDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kChangeUnfocusedPriority)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"most-visited-tiles-new-scoring",
     flag_descriptions::kMostVisitedTilesNewScoringName,
     flag_descriptions::kMostVisitedTilesNewScoringDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(history::kMostVisitedTilesNewScoring,
                                    kMostVisitedTilesNewScoringVariations,
                                    "MostVisitedTilesNewScoring")},

    {"omnibox-local-history-zero-suggest-beyond-ntp",
     flag_descriptions::kOmniboxLocalHistoryZeroSuggestBeyondNTPName,
     flag_descriptions::kOmniboxLocalHistoryZeroSuggestBeyondNTPDescription,
     kOsAll, FEATURE_VALUE_TYPE(omnibox::kLocalHistoryZeroSuggestBeyondNTP)},

    {"omnibox-suggestion-answer-migration",
     flag_descriptions::kOmniboxSuggestionAnswerMigrationName,
     flag_descriptions::kOmniboxSuggestionAnswerMigrationDescription, kOsAll,
     FEATURE_VALUE_TYPE(omnibox_feature_configs::SuggestionAnswerMigration::
                            kOmniboxSuggestionAnswerMigration)},

    {"omnibox-zero-suggest-prefetch-debouncing",
     flag_descriptions::kOmniboxZeroSuggestPrefetchDebouncingName,
     flag_descriptions::kOmniboxZeroSuggestPrefetchDebouncingDescription,
=======
#if defined(OS_ANDROID)
    {"omnibox-on-device-head-suggestions-non-incognito",
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsNonIncognitoName,
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsNonIncognitoDescription,
>>>>>>> chromium
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kOnDeviceHeadProviderNonIncognito,
         kOmniboxOnDeviceHeadSuggestNonIncognitoExperimentVariations,
         "OmniboxOnDeviceHeadNonIncognitoTuningMobile")},
#endif  // defined(OS_ANDROID)

    {"omnibox-on-focus-suggestions-contextual-web",
     flag_descriptions::kOmniboxOnFocusSuggestionsContextualWebName,
     flag_descriptions::kOmniboxOnFocusSuggestionsContextualWebDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kOnFocusSuggestionsContextualWeb,
         kOmniboxOnFocusSuggestionsContextualWebVariations,
         "OmniboxGoogleOnContent")},

    {"omnibox-on-focus-suggestions-contextual-web-allow-srp",
     flag_descriptions::kOmniboxOnFocusSuggestionsContextualWebAllowSRPName,
     flag_descriptions::
         kOmniboxOnFocusSuggestionsContextualWebAllowSRPDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(omnibox::kOnFocusSuggestionsContextualWebAllowSRP)},

    {"omnibox-experimental-suggest-scoring",
     flag_descriptions::kOmniboxExperimentalSuggestScoringName,
     flag_descriptions::kOmniboxExperimentalSuggestScoringDescription, kOsAll,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxExperimentalSuggestScoring)},

    {"omnibox-trending-zero-prefix-suggestions-on-ntp",
     flag_descriptions::kOmniboxTrendingZeroPrefixSuggestionsOnNTPName,
     flag_descriptions::kOmniboxTrendingZeroPrefixSuggestionsOnNTPDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxTrendingZeroPrefixSuggestionsOnNTP)},

#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_MAC) || \
    defined(OS_WIN)
    {"omnibox-experimental-keyword-mode",
     flag_descriptions::kOmniboxExperimentalKeywordModeName,
     flag_descriptions::kOmniboxExperimentalKeywordModeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kExperimentalKeywordMode)},
    {"omnibox-short-bookmark-suggestions",
     flag_descriptions::kOmniboxShortBookmarkSuggestionsName,
     flag_descriptions::kOmniboxShortBookmarkSuggestionsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kShortBookmarkSuggestions)},
    {"omnibox-tab-switch-suggestions",
     flag_descriptions::kOmniboxTabSwitchSuggestionsName,
     flag_descriptions::kOmniboxTabSwitchSuggestionsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxTabSwitchSuggestions)},
    {"omnibox-pedals-batch2", flag_descriptions::kOmniboxPedalsBatch2Name,
     flag_descriptions::kOmniboxPedalsBatch2Description, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxPedalsBatch2)},
    {"omnibox-pedals-batch2-nonenglish",
     flag_descriptions::kOmniboxPedalsBatch2NonEnglishName,
     flag_descriptions::kOmniboxPedalsBatch2NonEnglishDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxPedalsBatch2NonEnglish)},
    {"omnibox-pedals-batch3", flag_descriptions::kOmniboxPedalsBatch3Name,
     flag_descriptions::kOmniboxPedalsBatch3Description, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxPedalsBatch3)},
    {"omnibox-pedals-default-icon-colored",
     flag_descriptions::kOmniboxPedalsDefaultIconColoredName,
     flag_descriptions::kOmniboxPedalsDefaultIconColoredDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxPedalsDefaultIconColored)},
    {"omnibox-keyword-search-button",
     flag_descriptions::kOmniboxKeywordSearchButtonName,
     flag_descriptions::kOmniboxKeywordSearchButtonDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxKeywordSearchButton)},
    {"omnibox-refined-focus-state",
     flag_descriptions::kOmniboxRefinedFocusStateName,
     flag_descriptions::kOmniboxRefinedFocusStateDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxRefinedFocusState)},
    {"omnibox-drive-suggestions",
     flag_descriptions::kOmniboxDriveSuggestionsName,
<<<<<<< HEAD
     flag_descriptions::kOmniboxDriveSuggestionsDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kDocumentProvider,
                                    kOmniboxDriveSuggestionsVariations,
                                    "OmniboxDocumentProvider")},
    {"omnibox-drive-suggestions-no-sync-requirement",
     flag_descriptions::kOmniboxDriveSuggestionsNoSyncRequirementName,
     flag_descriptions::kOmniboxDriveSuggestionsNoSyncRequirementDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kDocumentProviderNoSyncRequirement)},
    {"omnibox-force-allowed-to-be-default",
     flag_descriptions::kOmniboxForceAllowedToBeDefaultName,
     flag_descriptions::kOmniboxForceAllowedToBeDefaultDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox_feature_configs::ForceAllowedToBeDefault::
                            kForceAllowedToBeDefault)},
=======
     flag_descriptions::kOmniboxDriveSuggestionsDescriptions, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kDocumentProvider,
         kOmniboxDocumentProviderVariations,
         "OmniboxDocumentProviderNonDogfoodExperiments")},
    {"omnibox-rich-autocompletion",
     flag_descriptions::kOmniboxRichAutocompletionName,
     flag_descriptions::kOmniboxRichAutocompletionDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kRichAutocompletion,
                                    kOmniboxRichAutocompletionVariations,
                                    "OmniboxBundledExperimentV1")},
    {"omnibox-rich-autocompletion-min-char",
     flag_descriptions::kOmniboxRichAutocompletionMinCharName,
     flag_descriptions::kOmniboxRichAutocompletionMinCharDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kRichAutocompletion,
                                    kOmniboxRichAutocompletionMinCharVariations,
                                    "OmniboxBundledExperimentV1")},
    {"omnibox-rich-autocompletion-show-additional-text",
     flag_descriptions::kOmniboxRichAutocompletionShowAdditionalTextName,
     flag_descriptions::kOmniboxRichAutocompletionShowAdditionalTextDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kRichAutocompletion,
         kOmniboxRichAutocompletionShowAdditionalTextVariations,
         "OmniboxBundledExperimentV1")},
    {"omnibox-rich-autocompletion-split",
     flag_descriptions::kOmniboxRichAutocompletionSplitName,
     flag_descriptions::kOmniboxRichAutocompletionSplitDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kRichAutocompletion,
                                    kOmniboxRichAutocompletionSplitVariations,
                                    "OmniboxBundledExperimentV1")},
    {"omnibox-rich-autocompletion-prefer-urls-over-prefixes",
     flag_descriptions::kOmniboxRichAutocompletionPreferUrlsOverPrefixesName,
     flag_descriptions::
         kOmniboxRichAutocompletionPreferUrlsOverPrefixesDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kRichAutocompletion,
         kOmniboxRichAutocompletionPreferUrlsOverPrefixesVariations,
         "OmniboxBundledExperimentV1")},
>>>>>>> chromium
    {"omnibox-rich-autocompletion-promising",
     flag_descriptions::kOmniboxRichAutocompletionPromisingName,
     flag_descriptions::kOmniboxRichAutocompletionPromisingDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kRichAutocompletion,
         kOmniboxRichAutocompletionPromisingVariations,
         "OmniboxBundledExperimentV1")},
<<<<<<< HEAD
    {"omnibox-starter-pack-expansion",
     flag_descriptions::kOmniboxStarterPackExpansionName,
     flag_descriptions::kOmniboxStarterPackExpansionDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kStarterPackExpansion,
                                    kOmniboxStarterPackExpansionVariations,
                                    "StarterPackExpansion")},

    {"omnibox-starter-pack-iph", flag_descriptions::kOmniboxStarterPackIPHName,
     flag_descriptions::kOmniboxStarterPackIPHDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kStarterPackIPH)},

    {"omnibox-focus-triggers-web-and-srp-zero-suggest",
     flag_descriptions::kOmniboxFocusTriggersWebAndSRPZeroSuggestName,
     flag_descriptions::kOmniboxFocusTriggersWebAndSRPZeroSuggestDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kFocusTriggersWebAndSRPZeroSuggest)},

#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) ||
        // BUILDFLAG(IS_WIN)

#if BUILDFLAG(IS_ANDROID)
    {"animate-suggestions-list-appearance",
     flag_descriptions::kAnimateSuggestionsListAppearanceName,
     flag_descriptions::kAnimateSuggestionsListAppearanceDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kAnimateSuggestionsListAppearance)},

    {"omnibox-answer-actions", flag_descriptions::kOmniboxAnswerActionsName,
     flag_descriptions::kOmniboxAnswerActionsDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kOmniboxAnswerActions,
                                    kOmniboxAnswerActionsVariants,
                                    "OmniboxBundledExperimentV1")},

    {"omnibox-asynchronous-view-inflation",
     flag_descriptions::kOmniboxAsyncViewInflationName,
     flag_descriptions::kOmniboxAsyncViewInflationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxAsyncViewInflation)},

#endif  // BUILDFLAG(IS_ANDROID)
#if BUILDFLAG(IS_WIN)
    {"omnibox-on-device-head-suggestions",
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsName,
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsDescription, kOsWin,
     FEATURE_VALUE_TYPE(omnibox::kOnDeviceHeadProviderNonIncognito)},
    {"omnibox-on-device-head-suggestions-incognito",
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsIncognitoName,
     flag_descriptions::kOmniboxOnDeviceHeadSuggestionsIncognitoDescription,
     kOsWin, FEATURE_VALUE_TYPE(omnibox::kOnDeviceHeadProviderIncognito)},
#endif  // BUILDFLAG(IS_WIN)

    {"omnibox-on-device-tail-suggestions",
     flag_descriptions::kOmniboxOnDeviceTailSuggestionsName,
     flag_descriptions::kOmniboxOnDeviceTailSuggestionsDescription, kOsAll,
     FEATURE_VALUE_TYPE(omnibox::kOnDeviceTailModel)},
=======
    {"omnibox-bookmark-paths", flag_descriptions::kOmniboxBookmarkPathsName,
     flag_descriptions::kOmniboxBookmarkPathsDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kBookmarkPaths,
                                    kOmniboxBookmarkPathsVariations,
                                    "OmniboxBundledExperimentV1")},
    {"omnibox-disable-cgi-param-matching",
     flag_descriptions::kOmniboxDisableCGIParamMatchingName,
     flag_descriptions::kOmniboxDisableCGIParamMatchingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kDisableCGIParamMatching)},
    {"omnibox-keyword-space-triggering-setting",
     flag_descriptions::kOmniboxKeywordSpaceTriggeringSettingName,
     flag_descriptions::kOmniboxKeywordSpaceTriggeringSettingDescription,
     kOsDesktop, FEATURE_VALUE_TYPE(omnibox::kKeywordSpaceTriggeringSetting)},
    {"omnibox-active-search-engines",
     flag_descriptions::kOmniboxActiveSearchEnginesName,
     flag_descriptions::kOmniboxActiveSearchEnginesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kActiveSearchEngines)},
#endif  // defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_MAC) ||
        // defined(OS_WIN)
>>>>>>> chromium

#if BUILDFLAG(IS_CHROMEOS)
    {"scheduler-configuration", flag_descriptions::kSchedulerConfigurationName,
     flag_descriptions::kSchedulerConfigurationDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kSchedulerConfigurationChoices)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if defined(OS_ANDROID)
    {"enable-command-line-on-non-rooted-devices",
     flag_descriptions::kEnableCommandLineOnNonRootedName,
     flag_descriptions::kEnableCommandLineOnNoRootedDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCommandLineOnNonRooted)},
#endif  // OS_ANDROID

#if defined(OS_ANDROID)
    {"request-desktop-site-for-tablets",
     flag_descriptions::kRequestDesktopSiteForTabletsName,
     flag_descriptions::kRequestDesktopSiteForTabletsDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kRequestDesktopSiteForTablets,
                                    kRequestDesktopSiteForTabletsVariations,
                                    "RequestDesktopSiteForTablets")},
    {"app-menu-mobile-site-option",
     flag_descriptions::kAppMenuMobileSiteOptionName,
     flag_descriptions::kAppMenuMobileSiteOptionDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAppMenuMobileSiteOption)},
#endif  // OS_ANDROID

    {"force-color-profile", flag_descriptions::kForceColorProfileName,
     flag_descriptions::kForceColorProfileDescription, kOsAll,
     MULTI_VALUE_TYPE(kForceColorProfileChoices)},

    {"force-effective-connection-type",
     flag_descriptions::kForceEffectiveConnectionTypeName,
     flag_descriptions::kForceEffectiveConnectionTypeDescription, kOsAll,
     MULTI_VALUE_TYPE(kForceEffectiveConnectionTypeChoices)},

    {"forced-colors", flag_descriptions::kForcedColorsName,
     flag_descriptions::kForcedColorsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kForcedColors)},

#if defined(OS_ANDROID)
    {"dynamic-color-gamut", flag_descriptions::kDynamicColorGamutName,
     flag_descriptions::kDynamicColorGamutDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kDynamicColorGamut)},
#endif

    {"memlog", flag_descriptions::kMemlogName,
     flag_descriptions::kMemlogDescription, kOsAll,
     MULTI_VALUE_TYPE(kMemlogModeChoices)},

    {"memlog-sampling-rate", flag_descriptions::kMemlogSamplingRateName,
     flag_descriptions::kMemlogSamplingRateDescription, kOsAll,
     MULTI_VALUE_TYPE(kMemlogSamplingRateChoices)},

    {"memlog-stack-mode", flag_descriptions::kMemlogStackModeName,
     flag_descriptions::kMemlogStackModeDescription, kOsAll,
     MULTI_VALUE_TYPE(kMemlogStackModeChoices)},

    {"omnibox-default-typed-navigations-to-https",
     flag_descriptions::kOmniboxDefaultTypedNavigationsToHttpsName,
     flag_descriptions::kOmniboxDefaultTypedNavigationsToHttpsDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kDefaultTypedNavigationsToHttps,
         kOmniboxDefaultTypedNavigationsToHttpsVariations,
         "OmniboxDefaultTypedNavigationsToHttps")},

    {"omnibox-max-zero-suggest-matches",
     flag_descriptions::kOmniboxMaxZeroSuggestMatchesName,
     flag_descriptions::kOmniboxMaxZeroSuggestMatchesDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kMaxZeroSuggestMatches,
                                    kMaxZeroSuggestMatchesVariations,
                                    "OmniboxBundledExperimentV1")},

    {"omnibox-ui-max-autocomplete-matches",
     flag_descriptions::kOmniboxUIMaxAutocompleteMatchesName,
     flag_descriptions::kOmniboxUIMaxAutocompleteMatchesDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         omnibox::kUIExperimentMaxAutocompleteMatches,
         kOmniboxUIMaxAutocompleteMatchesVariations,
         "OmniboxBundledExperimentV1")},

    {"omnibox-max-url-matches", flag_descriptions::kOmniboxMaxURLMatchesName,
     flag_descriptions::kOmniboxMaxURLMatchesDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kOmniboxMaxURLMatches,
                                    kOmniboxMaxURLMatchesVariations,
                                    "OmniboxMaxURLMatchesVariations")},

    {"omnibox-dynamic-max-autocomplete",
     flag_descriptions::kOmniboxDynamicMaxAutocompleteName,
     flag_descriptions::kOmniboxDynamicMaxAutocompleteDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kDynamicMaxAutocomplete,
                                    kOmniboxDynamicMaxAutocompleteVariations,
                                    "OmniboxBundledExperimentV1")},

    {"omnibox-webui-omnibox-popup",
     flag_descriptions::kOmniboxWebUIOmniboxPopupName,
     flag_descriptions::kOmniboxWebUIOmniboxPopupDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kWebUIOmniboxPopup)},

    {"memories", flag_descriptions::kMemoriesName,
     flag_descriptions::kMemoriesDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(history_clusters::kMemories,
                                    kMemoriesVariations,
                                    "Memories")},

    {"memories-debug", flag_descriptions::kMemoriesDebugName,
     flag_descriptions::kMemoriesDebugDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(history_clusters::kDebug)},

<<<<<<< HEAD
    {"optimization-guide-model-execution",
     flag_descriptions::kOptimizationGuideModelExecutionName,
     flag_descriptions::kOptimizationGuideModelExecutionDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(
         optimization_guide::features::kOptimizationGuideModelExecution)},

    {"optimization-guide-on-device-model",
     flag_descriptions::kOptimizationGuideOnDeviceModelName,
     flag_descriptions::kOptimizationGuideOnDeviceModelDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         optimization_guide::features::kOnDeviceModelPerformanceParams,
         kOptimizationGuideOnDeviceModelVariations,
         "OptimizationGuideOnDeviceModel")},

    {"text-safety-classifier", flag_descriptions::kTextSafetyClassifierName,
     flag_descriptions::kTextSafetyClassifierDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         optimization_guide::features::kTextSafetyClassifier,
         kTextSafetyClassifierVariations,
         "TextSafetyClassifier")},

    {"organic-repeatable-queries",
     flag_descriptions::kOrganicRepeatableQueriesName,
     flag_descriptions::kOrganicRepeatableQueriesDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(history::kOrganicRepeatableQueries,
                                    kOrganicRepeatableQueriesVariations,
                                    "OrganicRepeatableQueries")},

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) || \
    BUILDFLAG(IS_WIN)
    {"history-embeddings", flag_descriptions::kHistoryEmbeddingsName,
     flag_descriptions::kHistoryEmbeddingsDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(history_embeddings::kHistoryEmbeddings,
                                    kHistoryEmbeddingsVariations,
                                    "HistoryEmbeddings")},
    {"history-embeddings-answers",
     flag_descriptions::kHistoryEmbeddingsAnswersName,
     flag_descriptions::kHistoryEmbeddingsAnswersDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(history_embeddings::kHistoryEmbeddingsAnswers)},
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_MAC) ||
        // BUILDFLAG(IS_WIN)

    {"history-journeys", flag_descriptions::kJourneysName,
     flag_descriptions::kJourneysDescription, kOsDesktop | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(history_clusters::internal::kJourneys,
                                    kJourneysVariations,
                                    "HistoryJourneys")},

    {"extract-related-searches-from-prefetched-zps-response",
     flag_descriptions::kExtractRelatedSearchesFromPrefetchedZPSResponseName,
     flag_descriptions::
         kExtractRelatedSearchesFromPrefetchedZPSResponseDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(page_content_annotations::features::
                            kExtractRelatedSearchesFromPrefetchedZPSResponse)},

    {"page-image-service-optimization-guide-salient-images",
     flag_descriptions::kPageImageServiceOptimizationGuideSalientImagesName,
     flag_descriptions::
         kPageImageServiceOptimizationGuideSalientImagesDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         page_image_service::kImageServiceOptimizationGuideSalientImages,
         kImageServiceOptimizationGuideSalientImagesVariations,
         "PageImageService")},

    {"page-image-service-suggest-powered-images",
     flag_descriptions::kPageImageServiceSuggestPoweredImagesName,
     flag_descriptions::kPageImageServiceSuggestPoweredImagesDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(page_image_service::kImageServiceSuggestPoweredImages)},

    {"page-content-annotations", flag_descriptions::kPageContentAnnotationsName,
     flag_descriptions::kPageContentAnnotationsDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         page_content_annotations::features::kPageContentAnnotations,
         kPageContentAnnotationsVariations,
         "PageContentAnnotations")},

    {"page-content-annotations-persist-salient-image-metadata",
     flag_descriptions::kPageContentAnnotationsPersistSalientImageMetadataName,
     flag_descriptions::
         kPageContentAnnotationsPersistSalientImageMetadataDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         page_content_annotations::features::
             kPageContentAnnotationsPersistSalientImageMetadata)},

    {"page-content-annotations-remote-page-metadata",
     flag_descriptions::kPageContentAnnotationsRemotePageMetadataName,
     flag_descriptions::kPageContentAnnotationsRemotePageMetadataDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         page_content_annotations::features::kRemotePageMetadata,
         kRemotePageMetadataVariations,
         "RemotePageMetadata")},

    {"page-visibility-page-content-annotations",
     flag_descriptions::kPageVisibilityPageContentAnnotationsName,
     flag_descriptions::kPageVisibilityPageContentAnnotationsDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(page_content_annotations::features::
                            kPageVisibilityPageContentAnnotations)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-remove-stale-policy-pinned-apps-from-shelf",
     flag_descriptions::kEnableRemoveStalePolicyPinnedAppsFromShelfName,
     flag_descriptions::kEnableRemoveStalePolicyPinnedAppsFromShelfDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kRemoveStalePolicyPinnedAppsFromShelf)},
    {"language-packs-in-settings",
     flag_descriptions::kLanguagePacksInSettingsName,
     flag_descriptions::kLanguagePacksInSettingsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kLanguagePacksInSettings)},
    {"use-ml-service-for-non-longform-handwriting-on-all-boards",
     flag_descriptions::kUseMlServiceForNonLongformHandwritingOnAllBoardsName,
     flag_descriptions::
         kUseMlServiceForNonLongformHandwritingOnAllBoardsDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kUseMlServiceForNonLongformHandwritingOnAllBoards)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
    {"search-prefetch", flag_descriptions::kEnableSearchPrefetchName,
     flag_descriptions::kEnableSearchPrefetchDescription, kOsAll,
     SINGLE_VALUE_TYPE(kSearchPrefetchServiceCommandLineFlag)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"handwriting-gesture-editing",
     flag_descriptions::kHandwritingGestureEditingName,
     flag_descriptions::kHandwritingGestureEditingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kHandwritingGestureEditing)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"block-insecure-private-network-requests",
     flag_descriptions::kBlockInsecurePrivateNetworkRequestsName,
     flag_descriptions::kBlockInsecurePrivateNetworkRequestsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kBlockInsecurePrivateNetworkRequests)},

    {"cross-origin-embedder-policy-credentialless",
     flag_descriptions::kCrossOriginEmbedderPolicyCredentiallessName,
     flag_descriptions::kCrossOriginEmbedderPolicyCredentiallessDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         network::features::kCrossOriginEmbedderPolicyCredentialless)},

<<<<<<< HEAD
    {"private-network-access-preflight-short-timeout",
     flag_descriptions::kPrivateNetworkAccessPreflightShortTimeoutName,
     flag_descriptions::kPrivateNetworkAccessPreflightShortTimeoutDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         network::features::kPrivateNetworkAccessPreflightShortTimeout)},

    {"private-network-access-permission-prompt",
     flag_descriptions::kPrivateNetworkAccessPermissionPromptName,
     flag_descriptions::kPrivateNetworkAccessPermissionPromptDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         network::features::kPrivateNetworkAccessPermissionPrompt)},

    {"private-network-access-ignore-worker-errors",
     flag_descriptions::kPrivateNetworkAccessIgnoreWorkerErrorsName,
     flag_descriptions::kPrivateNetworkAccessIgnoreWorkerErrorsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kPrivateNetworkAccessForWorkersWarningOnly)},

    {"private-network-access-ignore-navigation-errors",
     flag_descriptions::kPrivateNetworkAccessIgnoreNavigationErrorsName,
     flag_descriptions::kPrivateNetworkAccessIgnoreNavigationErrorsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         features::kPrivateNetworkAccessForNavigationsWarningOnly)},
=======
    {"disable-keepalive-fetch", flag_descriptions::kDisableKeepaliveFetchName,
     flag_descriptions::kDisableKeepaliveFetchDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kDisableKeepaliveFetch)},
>>>>>>> chromium

    {"mbi-mode", flag_descriptions::kMBIModeName,
     flag_descriptions::kMBIModeDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kMBIMode,
                                    kMBIModeVariations,
                                    "MBIMode")},

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
=======
    {"intensive-wake-up-throttling",
     flag_descriptions::kIntensiveWakeUpThrottlingName,
     flag_descriptions::kIntensiveWakeUpThrottlingDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kIntensiveWakeUpThrottling,
                                    kIntensiveWakeUpThrottlingVariations,
                                    "IntensiveWakeUpThrottling")},

#if defined(OS_ANDROID)
    {"omnibox-spare-renderer", flag_descriptions::kOmniboxSpareRendererName,
     flag_descriptions::kOmniboxSpareRendererDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kOmniboxSpareRenderer)},
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"double-tap-to-zoom-in-tablet-mode",
     flag_descriptions::kDoubleTapToZoomInTabletModeName,
     flag_descriptions::kDoubleTapToZoomInTabletModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDoubleTapToZoomInTabletMode)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {flag_descriptions::kTabGroupsDeferRemoteNavigationsId,
     flag_descriptions::kTabGroupsDeferRemoteNavigationsName,
     flag_descriptions::kTabGroupsDeferRemoteNavigationsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(tab_groups::kTabGroupsDeferRemoteNavigations)},

    {flag_descriptions::kReadLaterFlagId, flag_descriptions::kReadLaterName,
     flag_descriptions::kReadLaterDescription, kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(reading_list::switches::kReadLater)},

    {"read-later-new-badge-promo",
     flag_descriptions::kReadLaterNewBadgePromoName,
     flag_descriptions::kReadLaterNewBadgePromoDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kReadLaterNewBadgePromo)},

#ifdef OS_ANDROID
    {"read-later-reminder-notification",
     flag_descriptions::kReadLaterReminderNotificationName,
     flag_descriptions::kReadLaterReminderNotificationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         reading_list::switches::kReadLaterReminderNotification)},

    {"bookmark-bottom-sheet", flag_descriptions::kBookmarkBottomSheetName,
     flag_descriptions::kBookmarkBottomSheetDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kBookmarkBottomSheet)},
#endif

    {"tab-groups-auto-create", flag_descriptions::kTabGroupsAutoCreateName,
     flag_descriptions::kTabGroupsAutoCreateDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabGroupsAutoCreate)},

    {"tab-groups-collapse-freezing",
     flag_descriptions::kTabGroupsCollapseFreezingName,
     flag_descriptions::kTabGroupsCollapseFreezingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabGroupsCollapseFreezing)},

    {"tab-groups-feedback", flag_descriptions::kTabGroupsFeedbackName,
     flag_descriptions::kTabGroupsFeedbackDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabGroupsFeedback)},

    {"tab-groups-new-badge-promo",
     flag_descriptions::kTabGroupsNewBadgePromoName,
     flag_descriptions::kTabGroupsNewBadgePromoDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabGroupsNewBadgePromo)},

    {"tab-groups-save", flag_descriptions::kTabGroupsSaveName,
     flag_descriptions::kTabGroupsSaveDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabGroupsSave)},

    {"new-tabstrip-animation", flag_descriptions::kNewTabstripAnimationName,
     flag_descriptions::kNewTabstripAnimationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kNewTabstripAnimation)},

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
=======
>>>>>>> chromium
    {flag_descriptions::kScrollableTabStripFlagId,
     flag_descriptions::kScrollableTabStripName,
     flag_descriptions::kScrollableTabStripDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kScrollableTabStrip,
                                    kTabScrollingVariations,
                                    "TabScrolling")},

    {"scrollable-tabstrip-buttons",
     flag_descriptions::kScrollableTabStripButtonsName,
     flag_descriptions::kScrollableTabStripButtonsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kScrollableTabStripButtons)},

<<<<<<< HEAD
    {flag_descriptions::kTabstripComboButtonFlagId,
     flag_descriptions::kTabstripComboButtonName,
     flag_descriptions::kTabstripComboButtonDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kTabstripComboButton,
                                    kTabstripComboButtonVariations,
                                    "TabstripComboButton")},
=======
    {flag_descriptions::kSidePanelFlagId, flag_descriptions::kSidePanelName,
     flag_descriptions::kSidePanelDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSidePanel)},

    {"tab-outlines-in-low-contrast-themes",
     flag_descriptions::kTabOutlinesInLowContrastThemesName,
     flag_descriptions::kTabOutlinesInLowContrastThemesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabOutlinesInLowContrastThemes)},
>>>>>>> chromium

    {"prominent-dark-mode-active-tab-title",
     flag_descriptions::kProminentDarkModeActiveTabTitleName,
     flag_descriptions::kProminentDarkModeActiveTabTitleDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kProminentDarkModeActiveTabTitle)},

<<<<<<< HEAD
    {"split-tabstrip", flag_descriptions::kSplitTabStripName,
     flag_descriptions::kSplitTabStripDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(tabs::kSplitTabStrip)},
#endif

#if !BUILDFLAG(IS_ANDROID)
    {flag_descriptions::kToolbarPinningFlagId,
     flag_descriptions::kToolbarPinningName,
     flag_descriptions::kToolbarPinningDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kToolbarPinning)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {flag_descriptions::kSidePanelResizingFlagId,
     flag_descriptions::kSidePanelResizingName,
     flag_descriptions::kSidePanelResizingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSidePanelResizing)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"enable-share-custom-actions-in-cct",
     flag_descriptions::kShareCustomActionsInCCTName,
     flag_descriptions::kShareCustomActionsInCCTDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kShareCustomActionsInCCT)},
#endif  // BUILDFLAG(IS_ANDROID)
=======
    {"promo-browser-commands", flag_descriptions::kPromoBrowserCommandsName,
     flag_descriptions::kPromoBrowserCommandsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kPromoBrowserCommands,
                                    kPromoBrowserCommandsVariations,
                                    "PromoBrowserCommands")},
#if defined(OS_ANDROID)
    {"enable-reader-mode-in-cct", flag_descriptions::kReaderModeInCCTName,
     flag_descriptions::kReaderModeInCCTDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kReaderModeInCCT)},
#endif  // !defined(OS_ANDROID)

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) || \
    defined(OS_CHROMEOS)
    {"webui-feedback", flag_descriptions::kWebuiFeedbackName,
     flag_descriptions::kWebuiFeedbackDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebUIFeedback)},
#endif  // defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) ||
        // defined(OS_CHROMEOS)
>>>>>>> chromium

#if !defined(OS_ANDROID)
    {"ntp-cache-one-google-bar", flag_descriptions::kNtpCacheOneGoogleBarName,
     flag_descriptions::kNtpCacheOneGoogleBarDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kCacheOneGoogleBar)},

<<<<<<< HEAD
    {"compare-confirmation-toast",
     commerce::flag_descriptions::kCompareConfirmationToastName,
     commerce::flag_descriptions::kCompareConfirmationToastDescription,
     kOsDesktop, FEATURE_VALUE_TYPE(commerce::kCompareConfirmationToast)},

    {"compare-management-interface",
     commerce::flag_descriptions::kCompareManagementInterfaceName,
     commerce::flag_descriptions::kCompareManagementInterfaceDescription,
     kOsDesktop, FEATURE_VALUE_TYPE(commerce::kCompareManagementInterface)},

    {"shopping-list", commerce::flag_descriptions::kShoppingListName,
     commerce::flag_descriptions::kShoppingListDescription,
     kOsAndroid | kOsDesktop, FEATURE_VALUE_TYPE(commerce::kShoppingList)},

    {"local-pdp-detection",
     commerce::flag_descriptions::kCommerceLocalPDPDetectionName,
     commerce::flag_descriptions::kCommerceLocalPDPDetectionDescription,
     kOsAndroid | kOsDesktop,
     FEATURE_VALUE_TYPE(commerce::kCommerceLocalPDPDetection)},

    {"price-tracking-subscription-service-locale-key",
     commerce::flag_descriptions::
         kPriceTrackingSubscriptionServiceLocaleKeyName,
     commerce::flag_descriptions::
         kPriceTrackingSubscriptionServiceLocaleKeyDescription,
     kOsAndroid | kOsDesktop,
     FEATURE_VALUE_TYPE(commerce::kPriceTrackingSubscriptionServiceLocaleKey)},

    {"price-tracking-subscription-service-product-version",
     commerce::flag_descriptions::
         kPriceTrackingSubscriptionServiceProductVersionName,
     commerce::flag_descriptions::
         kPriceTrackingSubscriptionServiceProductVersionDescription,
     kOsAndroid | kOsDesktop,
     FEATURE_VALUE_TYPE(
         commerce::kPriceTrackingSubscriptionServiceProductVersion)},

#if BUILDFLAG(IS_ANDROID)
    {"price-change-module", flag_descriptions::kPriceChangeModuleName,
     flag_descriptions::kPriceChangeModuleDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kPriceChangeModule)},

    {"track-by-default-mobile",
     commerce::flag_descriptions::kTrackByDefaultOnMobileName,
     commerce::flag_descriptions::kTrackByDefaultOnMobileDescription,
     kOsAndroid, FEATURE_VALUE_TYPE(commerce::kTrackByDefaultOnMobile)},
#endif  // BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {"enable-retail-coupons", flag_descriptions::kRetailCouponsName,
     flag_descriptions::kRetailCouponsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(commerce::kRetailCoupons)},

    {"ntp-alpha-background-collections",
     flag_descriptions::kNtpAlphaBackgroundCollectionsName,
     flag_descriptions::kNtpAlphaBackgroundCollectionsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpAlphaBackgroundCollections)},

    {"ntp-background-image-error-detection",
     flag_descriptions::kNtpBackgroundImageErrorDetectionName,
     flag_descriptions::kNtpBackgroundImageErrorDetectionDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpBackgroundImageErrorDetection)},

    {"ntp-calendar-module", flag_descriptions::kNtpCalendarModuleName,
     flag_descriptions::kNtpCalendarModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpCalendarModule,
                                    kNtpCalendarModuleVariations,
                                    "DesktopNtpModules")},

    {"ntp-chrome-cart-module", flag_descriptions::kNtpChromeCartModuleName,
     flag_descriptions::kNtpChromeCartModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpChromeCartModule,
                                    kNtpChromeCartModuleVariations,
                                    "DesktopNtpModules")},
=======
    {"ntp-repeatable-queries", flag_descriptions::kNtpRepeatableQueriesName,
     flag_descriptions::kNtpRepeatableQueriesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpRepeatableQueries)},

    {"ntp-modules", flag_descriptions::kNtpModulesName,
     flag_descriptions::kNtpModulesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kModules)},
>>>>>>> chromium

    {"ntp-drive-module", flag_descriptions::kNtpDriveModuleName,
     flag_descriptions::kNtpDriveModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpDriveModule,
                                    kNtpDriveModuleVariations,
                                    "DesktopNtpModules")},

<<<<<<< HEAD
    {"ntp-drive-module-segmentation",
     flag_descriptions::kNtpDriveModuleSegmentationName,
     flag_descriptions::kNtpDriveModuleSegmentationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpDriveModuleSegmentation)},

    {"ntp-drive-module-show-six-files",
     flag_descriptions::kNtpDriveModuleShowSixFilesName,
     flag_descriptions::kNtpDriveModuleShowSixFilesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpDriveModuleShowSixFiles)},

#if !defined(OFFICIAL_BUILD)
    {"ntp-dummy-modules", flag_descriptions::kNtpDummyModulesName,
     flag_descriptions::kNtpDummyModulesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpDummyModules)},
#endif

    {"ntp-middle-slot-promo-dismissal",
     flag_descriptions::kNtpMiddleSlotPromoDismissalName,
     flag_descriptions::kNtpMiddleSlotPromoDismissalDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpMiddleSlotPromoDismissal,
                                    kNtpMiddleSlotPromoDismissalVariations,
=======
    {"ntp-recipe-tasks-module", flag_descriptions::kNtpRecipeTasksModuleName,
     flag_descriptions::kNtpRecipeTasksModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpRecipeTasksModule,
                                    kNtpRecipeTasksModuleVariations,
>>>>>>> chromium
                                    "DesktopNtpModules")},

    {"ntp-shopping-tasks-module",
     flag_descriptions::kNtpShoppingTasksModuleName,
     flag_descriptions::kNtpShoppingTasksModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpShoppingTasksModule,
                                    kNtpShoppingTasksModuleVariations,
                                    "DesktopNtpModules")},

    {"ntp-chrome-cart-module", flag_descriptions::kNtpChromeCartModuleName,
     flag_descriptions::kNtpChromeCartModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpChromeCartModule,
                                    kNtpChromeCartModuleVariations,
                                    "DesktopNtpModules")},

    {"ntp-modules-drag-and-drop", flag_descriptions::kNtpModulesDragAndDropName,
     flag_descriptions::kNtpModulesDragAndDropDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpModulesDragAndDrop)},

<<<<<<< HEAD
    {"ntp-most-relevant-tab-resumption-module",
     flag_descriptions::kNtpMostRelevantTabResumptionModuleName,
     flag_descriptions::kNtpMostRelevantTabResumptionModuleDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         ntp_features::kNtpMostRelevantTabResumptionModule,
         kNtpMostRelevantTabResumptionModuleVariations,
         "NtpMostRelevantTabResumptionModules")},

    {"ntp-most-relevant-tab-resumption-module-device-icon",
     flag_descriptions::kNtpMostRelevantTabResumptionModuleDeviceIconName,
     flag_descriptions::
         kNtpMostRelevantTabResumptionModuleDeviceIconDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         ntp_features::kNtpMostRelevantTabResumptionModuleDeviceIcon)},

    {"ntp-ogb-async-bar-parts",
     flag_descriptions::kNtpOneGoogleBarAsyncBarPartsName,
     flag_descriptions::kNtpOneGoogleBarAsyncBarPartsName, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpOneGoogleBarAsyncBarParts)},

    {"ntp-outlook-calendar-module",
     flag_descriptions::kNtpOutlookCalendarModuleName,
     flag_descriptions::kNtpOutlookCalendarModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpOutlookCalendarModule,
                                    kNtpOutlookCalendarModuleVariations,
                                    "DesktopNtpModules")},

    {"ntp-realbox-contextual-and-trending-suggestions",
     flag_descriptions::kNtpRealboxContextualAndTrendingSuggestionsName,
     flag_descriptions::kNtpRealboxContextualAndTrendingSuggestionsDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         omnibox_feature_configs::RealboxContextualAndTrendingSuggestions::
             kRealboxContextualAndTrendingSuggestions)},

    {"ntp-realbox-cr23-theming", flag_descriptions::kNtpRealboxCr23ThemingName,
     flag_descriptions::kNtpRealboxCr23ThemingDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kRealboxCr23Theming,
                                    kNtpRealboxCr23ThemingVariations,
                                    "NtpRealboxCr23Theming")},

    {"ntp-realbox-match-searchbox-theme",
     flag_descriptions::kNtpRealboxMatchSearchboxThemeName,
     flag_descriptions::kNtpRealboxMatchSearchboxThemeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kRealboxMatchSearchboxTheme)},

    {"ntp-realbox-use-google-g-icon",
     flag_descriptions::kNtpRealboxUseGoogleGIconName,
     flag_descriptions::kNtpRealboxUseGoogleGIconDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kRealboxUseGoogleGIcon)},

    {"ntp-safe-browsing-module", flag_descriptions::kNtpSafeBrowsingModuleName,
     flag_descriptions::kNtpSafeBrowsingModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpSafeBrowsingModule,
                                    kNtpSafeBrowsingModuleVariations,
                                    "DesktopNtpModules")},

    {"ntp-sharepoint-module", flag_descriptions::kNtpSharepointModuleName,
     flag_descriptions::kNtpSharepointModuleDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ntp_features::kNtpSharepointModule,
                                    kNtpSharepointModuleVariations,
                                    "DesktopNtpModules")},

    {"ntp-wallpaper-search-button",
     flag_descriptions::kNtpWallpaperSearchButtonName,
     flag_descriptions::kNtpWallpaperSearchButtonDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpWallpaperSearchButton)},

    {"ntp-wallpaper-search-button-animation",
     flag_descriptions::kNtpWallpaperSearchButtonAnimationName,
     flag_descriptions::kNtpWallpaperSearchButtonAnimationDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpWallpaperSearchButtonAnimation)},

    {"ntp-microsoft-authentication-module",
     flag_descriptions::kNtpMicrosoftAuthenticationModuleName,
     flag_descriptions::kNtpMicrosoftAuthenticationModuleDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpMicrosoftAuthenticationModule)},

    {"shopping-page-types", commerce::flag_descriptions::kShoppingPageTypesName,
     commerce::flag_descriptions::kShoppingPageTypesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(commerce::kShoppingPageTypes)},

#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(CHROME_WIDE_ECHO_CANCELLATION)
    {"chrome-wide-echo-cancellation",
     flag_descriptions::kChromeWideEchoCancellationName,
     flag_descriptions::kChromeWideEchoCancellationDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(media::kChromeWideEchoCancellation)},
#endif  // BUILDFLAG(CHROME_WIDE_ECHO_CANCELLATION)

#if BUILDFLAG(DCHECK_IS_CONFIGURABLE)
=======
    {"ntp-modules-redesigned", flag_descriptions::kNtpModulesRedesignedName,
     flag_descriptions::kNtpModulesRedesignedDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kNtpModulesRedesigned)},

    {"ntp-realbox-suggestion-answers",
     flag_descriptions::kNtpRealboxSuggestionAnswersName,
     flag_descriptions::kNtpRealboxSuggestionAnswersDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(omnibox::kNtpRealboxSuggestionAnswers)},
#endif  // !defined(OS_ANDROID)

#if defined(DCHECK_IS_CONFIGURABLE)
>>>>>>> chromium
    {"dcheck-is-fatal", flag_descriptions::kDcheckIsFatalName,
     flag_descriptions::kDcheckIsFatalDescription, kOsWin,
     FEATURE_VALUE_TYPE(base::kDCheckIsFatalFeature)},
#endif  // defined(DCHECK_IS_CONFIGURABLE)

    {"enable-pixel-canvas-recording",
     flag_descriptions::kEnablePixelCanvasRecordingName,
     flag_descriptions::kEnablePixelCanvasRecordingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kEnablePixelCanvasRecording)},

    {"enable-parallel-downloading", flag_descriptions::kParallelDownloadingName,
     flag_descriptions::kParallelDownloadingDescription, kOsAll,
     FEATURE_VALUE_TYPE(download::features::kParallelDownloading)},

<<<<<<< HEAD
    {"download-notification-service-unified-api",
     flag_descriptions::kDownloadNotificationServiceUnifiedAPIName,
     flag_descriptions::kDownloadNotificationServiceUnifiedAPIDescription,
     kOsAndroid,
=======
    {"enable-pointer-lock-options", flag_descriptions::kPointerLockOptionsName,
     flag_descriptions::kPointerLockOptionsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kPointerLockOptions)},

#if defined(OS_ANDROID)
    {"enable-async-dns", flag_descriptions::kAsyncDnsName,
     flag_descriptions::kAsyncDnsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAsyncDns)},
#endif  // defined(OS_ANDROID)

#if defined(OS_ANDROID)
    {"download-auto-resumption-native",
     flag_descriptions::kDownloadAutoResumptionNativeName,
     flag_descriptions::kDownloadAutoResumptionNativeDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(download::features::kDownloadAutoResumptionNative)},

    {"download-later", flag_descriptions::kDownloadLaterName,
     flag_descriptions::kDownloadLaterDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(download::features::kDownloadLater)},

    {"download-later-debug-on-wifi",
     flag_descriptions::kDownloadLaterDebugOnWifiName,
     flag_descriptions::kDownloadLaterDebugOnWifiNameDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(download::switches::kDownloadLaterDebugOnWifi)},
#endif

    {"enable-new-download-backend",
     flag_descriptions::kEnableNewDownloadBackendName,
     flag_descriptions::kEnableNewDownloadBackendDescription, kOsAll,
>>>>>>> chromium
     FEATURE_VALUE_TYPE(
         download::features::kUseDownloadOfflineContentProvider)},

#if defined(OS_ANDROID)
    {"screen-capture-android", flag_descriptions::kUserMediaScreenCapturingName,
     flag_descriptions::kUserMediaScreenCapturingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kUserMediaScreenCapturing)},
#endif

#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
    {"chrome-tips-in-main-menu", flag_descriptions::kChromeTipsInMainMenuName,
     flag_descriptions::kChromeTipsInMainMenuDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kChromeTipsInMainMenu)},

    {"chrome-tips-in-main-menu-new-badge",
     flag_descriptions::kChromeTipsInMainMenuNewBadgeName,
     flag_descriptions::kChromeTipsInMainMenuNewBadgeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kChromeTipsInMainMenuNewBadge)},
#endif

    {"tab-hover-card-images", flag_descriptions::kTabHoverCardImagesName,
     flag_descriptions::kTabHoverCardImagesDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kTabHoverCardImages,
                                    kTabHoverCardImagesVariations,
                                    "TabHoverCardImages")},

    {"enable-storage-pressure-event",
     flag_descriptions::kStoragePressureEventName,
     flag_descriptions::kStoragePressureEventDescription, kOsAll,
     FEATURE_VALUE_TYPE(storage::features::kStoragePressureEvent)},

    {"installed-apps-in-cbd", flag_descriptions::kInstalledAppsInCbdName,
     flag_descriptions::kInstalledAppsInCbdDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kInstalledAppsInCbd)},

    {"enable-network-logging-to-file",
     flag_descriptions::kEnableNetworkLoggingToFileName,
     flag_descriptions::kEnableNetworkLoggingToFileDescription, kOsAll,
     SINGLE_VALUE_TYPE(network::switches::kLogNetLog)},

    {"enable-web-authentication-cable-v2-support",
     flag_descriptions::kEnableWebAuthenticationCableV2SupportName,
     flag_descriptions::kEnableWebAuthenticationCableV2SupportDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(device::kWebAuthCableSecondFactor)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-web-authentication-chromeos-authenticator",
     flag_descriptions::kEnableWebAuthenticationChromeOSAuthenticatorName,
     flag_descriptions::
         kEnableWebAuthenticationChromeOSAuthenticatorDescription,
     kOsCrOS, FEATURE_VALUE_TYPE(device::kWebAuthCrosPlatformAuthenticator)},
#endif
<<<<<<< HEAD

    {
        "zero-copy-tab-capture",
        flag_descriptions::kEnableZeroCopyTabCaptureName,
        flag_descriptions::kEnableZeroCopyTabCaptureDescription,
        kOsMac | kOsWin | kOsCrOS,
        FEATURE_VALUE_TYPE(blink::features::kZeroCopyTabCapture),
    },

=======
>>>>>>> chromium
#if BUILDFLAG(ENABLE_PDF)
    {"accessible-pdf-form", flag_descriptions::kAccessiblePDFFormName,
     flag_descriptions::kAccessiblePDFFormDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(chrome_pdf::features::kAccessiblePDFForm)},
#endif  // BUILDFLAG(ENABLE_PDF)

#if BUILDFLAG(ENABLE_PRINTING)
<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"add-printer-via-printscanmgr",
     flag_descriptions::kAddPrinterViaPrintscanmgrName,
     flag_descriptions::kAddPrinterViaPrintscanmgrDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(printing::features::kAddPrinterViaPrintscanmgr)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
=======
#if defined(OS_MAC)
>>>>>>> chromium
    {"cups-ipp-printing-backend",
     flag_descriptions::kCupsIppPrintingBackendName,
     flag_descriptions::kCupsIppPrintingBackendDescription, kOsMac,
     FEATURE_VALUE_TYPE(printing::features::kCupsIppPrintingBackend)},
#endif  // defined(OS_MAC)

#if defined(OS_WIN)
    {"print-with-reduced-rasterization",
     flag_descriptions::kPrintWithReducedRasterizationName,
     flag_descriptions::kPrintWithReducedRasterizationDescription, kOsWin,
     FEATURE_VALUE_TYPE(printing::features::kPrintWithReducedRasterization)},

    {"use-xps-for-printing", flag_descriptions::kUseXpsForPrintingName,
     flag_descriptions::kUseXpsForPrintingDescription, kOsWin,
     FEATURE_VALUE_TYPE(printing::features::kUseXpsForPrinting)},

    {"use-xps-for-printing-from-pdf",
     flag_descriptions::kUseXpsForPrintingFromPdfName,
     flag_descriptions::kUseXpsForPrintingFromPdfDescription, kOsWin,
     FEATURE_VALUE_TYPE(printing::features::kUseXpsForPrintingFromPdf)},
#endif  // defined(OS_WIN)
#endif  // BUILDFLAG(ENABLE_PRINTING)

<<<<<<< HEAD
#if BUILDFLAG(IS_WIN)
=======
    {"autofill-profile-client-validation",
     flag_descriptions::kAutofillProfileClientValidationName,
     flag_descriptions::kAutofillProfileClientValidationDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillProfileClientValidation)},

    {"autofill-profile-server-validation",
     flag_descriptions::kAutofillProfileServerValidationName,
     flag_descriptions::kAutofillProfileServerValidationDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillProfileServerValidation)},

#if defined(OS_WIN)
>>>>>>> chromium
    {"enable-windows-gaming-input-data-fetcher",
     flag_descriptions::kEnableWindowsGamingInputDataFetcherName,
     flag_descriptions::kEnableWindowsGamingInputDataFetcherDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kEnableWindowsGamingInputDataFetcher)},
<<<<<<< HEAD

    {"windows11-mica-titlebar", flag_descriptions::kWindows11MicaTitlebarName,
     flag_descriptions::kWindows11MicaTitlebarDescription, kOsWin,
     FEATURE_VALUE_TYPE(kWindows11MicaTitlebar)},
=======
>>>>>>> chromium
#endif

#if defined(OS_ANDROID)
    {"enable-start-surface", flag_descriptions::kStartSurfaceAndroidName,
     flag_descriptions::kStartSurfaceAndroidDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kStartSurfaceAndroid,
                                    kStartSurfaceAndroidVariations,
                                    "ChromeStart")},

    {"enable-instant-start", flag_descriptions::kInstantStartName,
     flag_descriptions::kInstantStartDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kInstantStart)},

<<<<<<< HEAD
    {"enable-educational-tip-module",
     flag_descriptions::kEducationalTipModuleName,
     flag_descriptions::kEducationalTipModuleDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         segmentation_platform::features::kEducationalTipModule)},

    {"enable-segmentation-platform-ephemeral_card_ranker",
     flag_descriptions::kSegmentationPlatformEphemeralCardRankerName,
     flag_descriptions::kSegmentationPlatformEphemeralCardRankerDescription,
     kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         segmentation_platform::features::
             kSegmentationPlatformEphemeralCardRanker,
         kEphemeralCardRankerCardOverrideOptions,
         "EducationalTipModule")},
=======
    {"enable-close-tab-suggestions",
     flag_descriptions::kCloseTabSuggestionsName,
     flag_descriptions::kCloseTabSuggestionsDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kCloseTabSuggestions,
                                    kCloseTabSuggestionsStaleVariations,
                                    "CloseSuggestionsTab")},

    {"enable-critical-persisted-tab-data",
     flag_descriptions::kCriticalPersistedTabDataName,
     flag_descriptions::kCriticalPersistedTabDataDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCriticalPersistedTabData)},
>>>>>>> chromium

    {"enable-store-hours", flag_descriptions::kStoreHoursAndroidName,
     flag_descriptions::kStoreHoursAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kStoreHoursAndroid)},

    {"enable-tab-grid-layout", flag_descriptions::kTabGridLayoutAndroidName,
     flag_descriptions::kTabGridLayoutAndroidDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kTabGridLayoutAndroid,
                                    kTabGridLayoutAndroidVariations,
                                    "TabGridLayoutAndroid")},

    {"enable-commerce-merchant-viewer",
     flag_descriptions::kCommerceMerchantViewerAndroidName,
     flag_descriptions::kCommerceMerchantViewerAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(commerce::kCommerceMerchantViewer)},

<<<<<<< HEAD
    {"price-insights", commerce::flag_descriptions::kPriceInsightsName,
     commerce::flag_descriptions::kPriceInsightsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(commerce::kPriceInsights)},

    {"enable-start-surface-return-time",
     flag_descriptions::kStartSurfaceReturnTimeName,
     flag_descriptions::kStartSurfaceReturnTimeDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kStartSurfaceReturnTime,
                                    kStartSurfaceReturnTimeVariations,
                                    "StartSurfaceReturnTime")},
    {"tab-drag-drop", flag_descriptions::kTabDragDropName,
     flag_descriptions::kTabDragDropDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabDragDropAndroid)},

    {"most-visited-tiles-customization",
     flag_descriptions::kMostVisitedTilesCustomizationName,
     flag_descriptions::kMostVisitedTilesCustomizationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kMostVisitedTilesCustomization)},
=======
    {"enable-commerce-price-tracking",
     flag_descriptions::kCommercePriceTrackingAndroidName,
     flag_descriptions::kCommercePriceTrackingAndroidDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(commerce::kCommercePriceTracking,
                                    kCommercePriceTrackingAndroidVariations,
                                    "CommercePriceTrackingAndroid")},

    {"enable-tab-groups", flag_descriptions::kTabGroupsAndroidName,
     flag_descriptions::kTabGroupsAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabGroupsAndroid)},

    {"enable-tab-groups-continuation",
     flag_descriptions::kTabGroupsContinuationAndroidName,
     flag_descriptions::kTabGroupsContinuationAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabGroupsContinuationAndroid)},

    {"enable-tab-groups-ui-improvements",
     flag_descriptions::kTabGroupsUiImprovementsAndroidName,
     flag_descriptions::kTabGroupsUiImprovementsAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabGroupsUiImprovementsAndroid)},

    {"enable-tab-switcher-on-return",
     flag_descriptions::kTabSwitcherOnReturnName,
     flag_descriptions::kTabSwitcherOnReturnDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kTabSwitcherOnReturn,
                                    kTabSwitcherOnReturnVariations,
                                    "ChromeStart")},

    {"enable-tab-to-gts-animation",
     flag_descriptions::kTabToGTSAnimationAndroidName,
     flag_descriptions::kTabToGTSAnimationAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabToGTSAnimation)},

    {"enable-tab-engagement-reporting",
     flag_descriptions::kTabEngagementReportingName,
     flag_descriptions::kTabEngagementReportingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabEngagementReportingAndroid)},

    {"enable-conditional-tabstrip",
     flag_descriptions::kConditionalTabStripAndroidName,
     flag_descriptions::kConditionalTabStripAndroidDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kConditionalTabStripAndroid,
         kConditionalTabStripAndroidVariations,
         "ConditioanlTabStrip")},

    {"enable-quick-action-search-widget-android",
     flag_descriptions::kQuickActionSearchWidgetAndroidName,
     flag_descriptions::kQuickActionSearchWidgetAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kQuickActionSearchWidgetAndroid)},

#endif  // OS_ANDROID

    {"enable-layout-ng", flag_descriptions::kEnableLayoutNGName,
     flag_descriptions::kEnableLayoutNGDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kLayoutNG)},

    {"enable-table-ng", flag_descriptions::kEnableLayoutNGTableName,
     flag_descriptions::kEnableLayoutNGTableDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kLayoutNGTable)},

    {"enable-lazy-image-loading",
     flag_descriptions::kEnableLazyImageLoadingName,
     flag_descriptions::kEnableLazyImageLoadingDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kLazyImageLoading,
                                    kLazyImageLoadingVariations,
                                    "LazyLoad")},
>>>>>>> chromium

    {"enable-lazy-frame-loading",
     flag_descriptions::kEnableLazyFrameLoadingName,
     flag_descriptions::kEnableLazyFrameLoadingDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kLazyFrameLoading,
                                    kLazyFrameLoadingVariations,
                                    "LazyLoad")},

<<<<<<< HEAD
    {"toolbar-phone-cleanup", flag_descriptions::kToolbarPhoneCleanupName,
     flag_descriptions::kToolbarPhoneCleanupDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kToolbarPhoneCleanup)},

    {"hide-tablet-toolbar-download-button",
     flag_descriptions::kHideTabletToolbarDownloadButtonName,
     flag_descriptions::kHideTabletToolbarDownloadButtonDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kHideTabletToolbarDownloadButton)},

    {"show-new-tab-animations", flag_descriptions::kShowNewTabAnimationsName,
     flag_descriptions::kShowNewTabAnimationsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kShowNewTabAnimations)},

    {"tab-switcher-color-blend-animate",
     flag_descriptions::kTabSwitcherColorBlendAnimateName,
     flag_descriptions::kTabSwitcherColorBlendAnimateDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kTabSwitcherColorBlendAnimate,
         kTabSwitcherColorBlendAnimateVariations,
         "TabSwitcherColorBlendAnimateVariations")},
#endif  // BUILDFLAG(IS_ANDROID)
=======
    {"autofill-enable-toolbar-status-chip",
     flag_descriptions::kAutofillEnableToolbarStatusChipName,
     flag_descriptions::kAutofillEnableToolbarStatusChipDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableToolbarStatusChip)},
>>>>>>> chromium

    {"show-warnings-for-suspicious-notifications",
     flag_descriptions::kShowWarningsForSuspiciousNotificationsName,
     flag_descriptions::kShowWarningsForSuspiciousNotificationsDescription,
     kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         safe_browsing::kShowWarningsForSuspiciousNotifications,
         kShowWarningsForSuspiciousNotificationsVariations,
         "ShowWarningsForSuspiciousNotifications")},

    {"unsafely-treat-insecure-origin-as-secure",
     flag_descriptions::kTreatInsecureOriginAsSecureName,
     flag_descriptions::kTreatInsecureOriginAsSecureDescription, kOsAll,
     ORIGIN_LIST_VALUE_TYPE(
         network::switches::kUnsafelyTreatInsecureOriginAsSecure,
         "")},

    {"treat-unsafe-downloads-as-active-content",
     flag_descriptions::kTreatUnsafeDownloadsAsActiveName,
     flag_descriptions::kTreatUnsafeDownloadsAsActiveDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kTreatUnsafeDownloadsAsActive)},

    {"detect-target-embedding-lookalikes",
     flag_descriptions::kDetectTargetEmbeddingLookalikesName,
     flag_descriptions::kDetectTargetEmbeddingLookalikesDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(
         lookalikes::features::kDetectTargetEmbeddingLookalikes)},

    {"disable-process-reuse", flag_descriptions::kDisableProcessReuse,
     flag_descriptions::kDisableProcessReuseDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kDisableProcessReuse)},

<<<<<<< HEAD
    {"subframe-process-reuse-thresholds",
     flag_descriptions::kSubframeProcessReuseThresholds,
     flag_descriptions::kSubframeProcessReuseThresholdsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         features::kSubframeProcessReuseThresholds,
         kSubframeProcessReuseThresholdsVariations,
         "SubframeProcessReuseThresholds" /* trial name */)},

#if !BUILDFLAG(IS_ANDROID)
    {"enable-live-caption-multilang",
     flag_descriptions::kEnableLiveCaptionMultilangName,
     flag_descriptions::kEnableLiveCaptionMultilangDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kLiveCaptionMultiLanguage)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-chromeos-live-translate",
     flag_descriptions::kEnableCrOSLiveTranslateName,
     flag_descriptions::kEnableCrOSLiveTranslateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kLiveTranslate)},
    {"enable-chromeos-soda-languages",
     flag_descriptions::kEnableCrOSSodaLanguagesName,
     flag_descriptions::kEnableCrOSSodaLanguagesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(speech::kCrosExpandSodaLanguages)},
    {"enable-chromeos-soda-conch",
     flag_descriptions::kEnableCrOSSodaConchLanguagesName,
     flag_descriptions::kEnableCrOSSodaLanguagesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(speech::kCrosSodaConchLanguages)},
#endif

    {"read-anything-read-aloud", flag_descriptions::kReadAnythingReadAloudName,
     flag_descriptions::kReadAnythingReadAloudDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kReadAnythingReadAloud)},

    {"read-anything-read-aloud-phrase-highlighting",
     flag_descriptions::kReadAnythingReadAloudPhraseHighlightingName,
     flag_descriptions::kReadAnythingReadAloudPhraseHighlightingDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kReadAnythingReadAloudPhraseHighlighting)},

    {"read-anything-images-via-algorithm",
     flag_descriptions::kReadAnythingImagesViaAlgorithmName,
     flag_descriptions::kReadAnythingImagesViaAlgorithmDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kReadAnythingImagesViaAlgorithm)},

    {"read-anything-docs-integration",
     flag_descriptions::kReadAnythingDocsIntegrationName,
     flag_descriptions::kReadAnythingDocsIntegrationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kReadAnythingDocsIntegration)},

    {"read-anything-docs-load-more-button",
     flag_descriptions::kReadAnythingDocsLoadMoreButtonName,
     flag_descriptions::kReadAnythingDocsLoadMoreButtonDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kReadAnythingDocsLoadMoreButton)},

    {"support-tool-screenshot", flag_descriptions::kSupportToolScreenshot,
     flag_descriptions::kSupportToolScreenshotDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSupportToolScreenshot)},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
    {"wasm-tts-component-updater-enabled",
     flag_descriptions::kWasmTtsComponentUpdaterEnabledName,
     flag_descriptions::kWasmTtsComponentUpdaterEnabledDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWasmTtsComponentUpdaterEnabled)},
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
#endif  // !BUILDFLAG(IS_ANDROID)

    {"enable-auto-disable-accessibility",
     flag_descriptions::kEnableAutoDisableAccessibilityName,
     flag_descriptions::kEnableAutoDisableAccessibilityDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kAutoDisableAccessibility)},

    {"image-descriptions-alternative-routing",
     flag_descriptions::kImageDescriptionsAlternateRoutingName,
     flag_descriptions::kImageDescriptionsAlternateRoutingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kImageDescriptionsAlternateRouting)},

#if BUILDFLAG(IS_ANDROID)
    {"app-specific-history", flag_descriptions::kAppSpecificHistoryName,
     flag_descriptions::kAppSpecificHistoryDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAppSpecificHistory)},
#endif

#if BUILDFLAG(IS_ANDROID)
    {"cct-auth-tab", flag_descriptions::kCCTAuthTabName,
     flag_descriptions::kCCTAuthTabDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTAuthTab)},
    {"cct-auth-tab-disable-all-external-intents",
     flag_descriptions::kCCTAuthTabDisableAllExternalIntentsName,
     flag_descriptions::kCCTAuthTabDisableAllExternalIntentsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTAuthTabDisableAllExternalIntents)},
    {"cct-auth-tab-enable-https-redirects",
     flag_descriptions::kCCTAuthTabEnableHttpsRedirectsName,
     flag_descriptions::kCCTAuthTabEnableHttpsRedirectsDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kCCTAuthTabEnableHttpsRedirects,
         kCCTAuthTabEnableHttpsRedirectsVariations,
         "CCTAuthTabEnableHttpsRedirectsVariations")},
#endif

#if BUILDFLAG(IS_ANDROID)
    {"cct-before-unload", flag_descriptions::kCCTBeforeUnloadName,
     flag_descriptions::kCCTBeforeUnloadDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTBeforeUnload)},
#endif

#if BUILDFLAG(IS_ANDROID)
    {"cct-ephemeral-mode", flag_descriptions::kCCTEphemeralModeName,
     flag_descriptions::kCCTEphemeralModeDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTEphemeralMode)},
    {"cct-ephemeral-media-viewer-experiment",
     flag_descriptions::kCCTEphemeralMediaViewerExperimentName,
     flag_descriptions::kCCTEphemeralMediaViewerExperimentDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTEphemeralMediaViewerExperiment)},
#endif

#if BUILDFLAG(IS_ANDROID)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-app-data-search", flag_descriptions::kEnableAppDataSearchName,
     flag_descriptions::kEnableAppDataSearchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kEnableAppDataSearch)},

    {"enable-app-grid-ghost", flag_descriptions::kEnableAppGridGhostName,
     flag_descriptions::kEnableAppGridGhostDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kEnableAppGridGhost)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if !defined(OS_ANDROID)
    {"enable-accessibility-live-caption",
     flag_descriptions::kEnableAccessibilityLiveCaptionName,
     flag_descriptions::kEnableAccessibilityLiveCaptionDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kLiveCaption)},
    {"enable-accessibility-live-caption-soda",
     flag_descriptions::kEnableAccessibilityLiveCaptionSodaName,
     flag_descriptions::kEnableAccessibilityLiveCaptionSodaDescription,
     kOsDesktop, FEATURE_VALUE_TYPE(media::kUseSodaForLiveCaption)},
#endif  // !defined(OS_ANDROID)

#if defined(OS_ANDROID)
    {"cct-incognito", flag_descriptions::kCCTIncognitoName,
     flag_descriptions::kCCTIncognitoDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTIncognito)},
#endif

#if defined(OS_ANDROID)
>>>>>>> chromium
    {"cct-incognito-available-to-third-party",
     flag_descriptions::kCCTIncognitoAvailableToThirdPartyName,
     flag_descriptions::kCCTIncognitoAvailableToThirdPartyDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTIncognitoAvailableToThirdParty)},
#endif

#if defined(OS_ANDROID)
    {"enable-use-aaudio-driver", flag_descriptions::kEnableUseAaudioDriverName,
     flag_descriptions::kEnableUseAaudioDriverDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kUseAAudioDriver)},
#endif

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
    {"cct-resizable-for-third-parties",
     flag_descriptions::kCCTResizableForThirdPartiesName,
     flag_descriptions::kCCTResizableForThirdPartiesDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kCCTResizableForThirdParties,
         kCCTResizableThirdPartiesDefaultPolicyVariations,
         "CCTResizableThirdPartiesDefaultPolicy")},
    {"cct-google-bottom-bar", flag_descriptions::kCCTGoogleBottomBarName,
     flag_descriptions::kCCTGoogleBottomBarDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kCCTGoogleBottomBar,
                                    kCCTGoogleBottomBarVariations,
                                    "CCTGoogleBottomBarVariations")},
    {"cct-google-bottom-bar-variant-layouts",
     flag_descriptions::kCCTGoogleBottomBarVariantLayoutsName,
     flag_descriptions::kCCTGoogleBottomBarVariantLayoutsDescription,
     kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kCCTGoogleBottomBarVariantLayouts,
         kCCTGoogleBottomBarVariantLayoutsVariations,
         "CCTGoogleBottomBarVariantLayoutsVariations")},
    {"cct-open-in-browser-button-if-allowed-by-embedder",
     flag_descriptions::kCCTOpenInBrowserButtonIfAllowedByEmbedderName,
     flag_descriptions::kCCTOpenInBrowserButtonIfAllowedByEmbedderDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kCCTOpenInBrowserButtonIfAllowedByEmbedder)},
    {"cct-open-in-browser-button-if-enabled-by-embedder",
     flag_descriptions::kCCTOpenInBrowserButtonIfEnabledByEmbedderName,
     flag_descriptions::kCCTOpenInBrowserButtonIfEnabledByEmbedderDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kCCTOpenInBrowserButtonIfEnabledByEmbedder)},
    {"cct-revamped-branding", flag_descriptions::kCCTRevampedBrandingName,
     flag_descriptions::kCCTRevampedBrandingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTRevampedBranding)},
    {"cct-nested-security-icon", flag_descriptions::kCCTNestedSecurityIconName,
     flag_descriptions::kCCTNestedSecurityIconDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kCCTNestedSecurityIcon)},
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"allow-dsp-based-aec", flag_descriptions::kCrOSDspBasedAecAllowedName,
     flag_descriptions::kCrOSDspBasedAecAllowedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSDspBasedAecAllowed)},
    {"allow-dsp-based-ns", flag_descriptions::kCrOSDspBasedNsAllowedName,
     flag_descriptions::kCrOSDspBasedNsAllowedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSDspBasedNsAllowed)},
    {"allow-dsp-based-agc", flag_descriptions::kCrOSDspBasedAgcAllowedName,
     flag_descriptions::kCrOSDspBasedAgcAllowedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSDspBasedAgcAllowed)},
    {"enforce-system-aec", flag_descriptions::kCrOSEnforceSystemAecName,
     flag_descriptions::kCrOSEnforceSystemAecDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSEnforceSystemAec)},
    {"enforce-system-aec-agc", flag_descriptions::kCrOSEnforceSystemAecAgcName,
     flag_descriptions::kCrOSEnforceSystemAecAgcDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSEnforceSystemAecAgc)},
    {"enforce-system-aec-ns-agc",
     flag_descriptions::kCrOSEnforceSystemAecNsAgcName,
     flag_descriptions::kCrOSEnforceSystemAecNsAgcDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSEnforceSystemAecNsAgc)},
    {"enforce-system-aec-ns", flag_descriptions::kCrOSEnforceSystemAecNsName,
     flag_descriptions::kCrOSEnforceSystemAecNsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSEnforceSystemAecNs)},
    {"system-voice-isolation-option",
     flag_descriptions::kCrOSSystemVoiceIsolationOptionName,
     flag_descriptions::kCrOSSystemVoiceIsolationOptionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kCrOSSystemVoiceIsolationOption)},
    {"ignore-ui-gains", flag_descriptions::kIgnoreUiGainsName,
     flag_descriptions::kIgnoreUiGainsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kIgnoreUiGains)},
    {"show-force-respect-ui-gains-toggle",
     flag_descriptions::kShowForceRespectUiGainsToggleName,
     flag_descriptions::kShowForceRespectUiGainsToggleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kShowForceRespectUiGainsToggle)},
    {"show-spatial-audio-toggle",
     flag_descriptions::kShowSpatialAudioToggleName,
     flag_descriptions::kShowSpatialAudioToggleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kShowSpatialAudioToggle)},
    {"single-ca-cert-verification-phase-0",
     flag_descriptions::kSingleCaCertVerificationPhase0Name,
     flag_descriptions::kSingleCaCertVerificationPhase0Description, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSingleCaCertVerificationPhase0)},
    {"single-ca-cert-verification-phase-1",
     flag_descriptions::kSingleCaCertVerificationPhase1Name,
     flag_descriptions::kSingleCaCertVerificationPhase1Description, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSingleCaCertVerificationPhase1)},
    {"single-ca-cert-verification-phase-2",
     flag_descriptions::kSingleCaCertVerificationPhase2Name,
     flag_descriptions::kSingleCaCertVerificationPhase2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSingleCaCertVerificationPhase2)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enforce-system-aec", flag_descriptions::kCrOSEnforceSystemAecName,
     flag_descriptions::kCrOSEnforceSystemAecDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kCrOSEnforceSystemAec)},
    {"enforce-system-aec-agc", flag_descriptions::kCrOSEnforceSystemAecAgcName,
     flag_descriptions::kCrOSEnforceSystemAecAgcDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kCrOSEnforceSystemAecAgc)},
    {"enforce-system-aec-ns-agc",
     flag_descriptions::kCrOSEnforceSystemAecNsAgcName,
     flag_descriptions::kCrOSEnforceSystemAecNsAgcDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kCrOSEnforceSystemAecNsAgc)},
    {"enforce-system-aec-ns", flag_descriptions::kCrOSEnforceSystemAecNsName,
     flag_descriptions::kCrOSEnforceSystemAecNsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kCrOSEnforceSystemAecNs)},
>>>>>>> chromium
#endif

    {"enable-sxg-subresource-prefetching",
     flag_descriptions::kEnableSignedExchangeSubresourcePrefetchName,
     flag_descriptions::kEnableSignedExchangeSubresourcePrefetchDescription,
     kOsAll, FEATURE_VALUE_TYPE(features::kSignedExchangeSubresourcePrefetch)},

    {"enable-sxg-prefetch-cache-for-navigations",
     flag_descriptions::kEnableSignedExchangePrefetchCacheForNavigationsName,
     flag_descriptions::
         kEnableSignedExchangePrefetchCacheForNavigationsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kSignedExchangePrefetchCacheForNavigations)},

    {"enable-autofill-account-wallet-storage",
     flag_descriptions::kEnableAutofillAccountWalletStorageName,
     flag_descriptions::kEnableAutofillAccountWalletStorageDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableAccountWalletStorage)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-zero-state-app-reinstall-suggestions",
     flag_descriptions::kEnableAppReinstallZeroStateName,
     flag_descriptions::kEnableAppReinstallZeroStateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kEnableAppReinstallZeroState)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"reduce-horizontal-fling-velocity",
     flag_descriptions::kReduceHorizontalFlingVelocityName,
     flag_descriptions::kReduceHorizontalFlingVelocityDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kReduceHorizontalFlingVelocity)},

    {"enable-resampling-input-events",
     flag_descriptions::kEnableResamplingInputEventsName,
     flag_descriptions::kEnableResamplingInputEventsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kResamplingInputEvents,
                                    kResamplingInputEventsFeatureVariations,
                                    "ResamplingInputEvents")},

    {"enable-resampling-scroll-events",
     flag_descriptions::kEnableResamplingScrollEventsName,
     flag_descriptions::kEnableResamplingScrollEventsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kResamplingScrollEvents,
                                    kResamplingInputEventsFeatureVariations,
                                    "ResamplingScrollEvents")},

    // Should only be available if kResamplingScrollEvents is on, and using
    // linear resampling.
    {"enable-resampling-scroll-events-experimental-prediction",
     flag_descriptions::kEnableResamplingScrollEventsExperimentalPredictionName,
     flag_descriptions::
         kEnableResamplingScrollEventsExperimentalPredictionDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         ::features::kResamplingScrollEventsExperimentalPrediction,
         kResamplingScrollEventsExperimentalPredictionVariations,
         "ResamplingScrollEventsExperimentalLatency")},

    {"enable-filtering-scroll-events",
     flag_descriptions::kFilteringScrollPredictionName,
     flag_descriptions::kFilteringScrollPredictionDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kFilteringScrollPrediction,
                                    kFilteringPredictionFeatureVariations,
                                    "FilteringScrollPrediction")},

    {"compositor-threaded-scrollbar-scrolling",
     flag_descriptions::kCompositorThreadedScrollbarScrollingName,
     flag_descriptions::kCompositorThreadedScrollbarScrollingDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kCompositorThreadedScrollbarScrolling)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-vaapi-jpeg-image-decode-acceleration",
     flag_descriptions::kVaapiJpegImageDecodeAccelerationName,
     flag_descriptions::kVaapiJpegImageDecodeAccelerationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kVaapiJpegImageDecodeAcceleration)},

    {"enable-vaapi-webp-image-decode-acceleration",
     flag_descriptions::kVaapiWebPImageDecodeAccelerationName,
     flag_descriptions::kVaapiWebPImageDecodeAccelerationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kVaapiWebPImageDecodeAcceleration)},
#endif

#if defined(OS_WIN)
    {"calculate-native-win-occlusion",
     flag_descriptions::kCalculateNativeWinOcclusionName,
     flag_descriptions::kCalculateNativeWinOcclusionDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kCalculateNativeWinOcclusion)},
#endif  // OS_WIN

#if !defined(OS_ANDROID)
    {"happiness-tracking-surveys-for-desktop-demo",
     flag_descriptions::kHappinessTrackingSurveysForDesktopDemoName,
     flag_descriptions::kHappinessTrackingSurveysForDesktopDemoDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kHappinessTrackingSurveysForDesktopDemo)},

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
    {"android-elegant-text-height",
     flag_descriptions::kAndroidElegantTextHeightName,
     flag_descriptions::kAndroidElegantTextHeightDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAndroidElegantTextHeight)},
=======
    {"happiness-tracking-surveys-for-desktop-privacy-sandbox",
     flag_descriptions::kHappinessTrackingSurveysForDesktopPrivacySandboxName,
     flag_descriptions::
         kHappinessTrackingSurveysForDesktopPrivacySandboxDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         features::kHappinessTrackingSurveysForDesktopPrivacySandbox)},

    {"happiness-tracking-surveys-for-desktop-settings",
     flag_descriptions::kHappinessTrackingSurveysForDesktopSettingsName,
     flag_descriptions::kHappinessTrackingSurveysForDesktopSettingsDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kHappinessTrackingSurveysForDesktopSettings)},
>>>>>>> chromium

    {"happiness-tracking-surveys-for-desktop-settings-privacy",
     flag_descriptions::kHappinessTrackingSurveysForDesktopSettingsPrivacyName,
     flag_descriptions::
         kHappinessTrackingSurveysForDesktopSettingsPrivacyDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         features::kHappinessTrackingSurveysForDesktopSettingsPrivacy)},
#endif  // !defined(OS_ANDROID)

#if BUILDFLAG(ENABLE_DICE_SUPPORT)
    {"enable-sign-in-profile-creation",
     flag_descriptions::kSignInProfileCreationName,
     flag_descriptions::kSignInProfileCreationDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(features::kSignInProfileCreation)},

    {"enable-sign-in-profile-creation-enterprise",
     flag_descriptions::kSignInProfileCreationEnterpriseName,
     flag_descriptions::kSignInProfileCreationEnterpriseDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(features::kSignInProfileCreationEnterprise)},
#endif

    {"destroy-profile-on-browser-close",
     flag_descriptions::kDestroyProfileOnBrowserCloseName,
     flag_descriptions::kDestroyProfileOnBrowserCloseDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(features::kDestroyProfileOnBrowserClose)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-arc-unified-audio-focus",
     flag_descriptions::kEnableArcUnifiedAudioFocusName,
     flag_descriptions::kEnableArcUnifiedAudioFocusDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kEnableUnifiedAudioFocusFeature)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_WIN)
    {"use-angle", flag_descriptions::kUseAngleName,
<<<<<<< HEAD
     flag_descriptions::kUseAngleDescriptionWindows, kOsWin,
     MULTI_VALUE_TYPE(kUseAngleChoicesWindows)},
#elif BUILDFLAG(IS_MAC)
    {"use-angle", flag_descriptions::kUseAngleName,
     flag_descriptions::kUseAngleDescriptionMac, kOsMac,
     MULTI_VALUE_TYPE(kUseAngleChoicesMac)},
#elif BUILDFLAG(IS_ANDROID)
        {"use-angle", flag_descriptions::kUseAngleName,
         flag_descriptions::kUseAngleDescriptionAndroid, kOsAndroid,
         MULTI_VALUE_TYPE(kUseAngleChoicesAndroid)},
=======
     flag_descriptions::kUseAngleDescription, kOsWin,
     MULTI_VALUE_TYPE(kUseAngleChoices)},
>>>>>>> chromium
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-assistant-dsp", flag_descriptions::kEnableGoogleAssistantDspName,
     flag_descriptions::kEnableGoogleAssistantDspDescription, kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::assistant::features::kEnableDspHotword)},
    {"disable-quick-answers-v2-translation",
     flag_descriptions::kDisableQuickAnswersV2TranslationName,
     flag_descriptions::kDisableQuickAnswersV2TranslationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kDisableQuickAnswersV2Translation)},
    {"quick-answers-rich-card", flag_descriptions::kQuickAnswersRichCardName,
     flag_descriptions::kQuickAnswersRichCardDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswersRichCard)},
    {"quick-answers-material-next-ui",
     flag_descriptions::kQuickAnswersMaterialNextUIName,
     flag_descriptions::kQuickAnswersMaterialNextUIDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswersMaterialNextUI)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
     FEATURE_VALUE_TYPE(chromeos::assistant::features::kEnableDspHotword)},

    {"enable-assistant-app-support",
     flag_descriptions::kEnableAssistantAppSupportName,
     flag_descriptions::kEnableAssistantAppSupportDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::assistant::features::kAssistantAppSupport)},

    {"enable-quick-answers", flag_descriptions::kEnableQuickAnswersName,
     flag_descriptions::kEnableQuickAnswersDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswers)},

    {"enable-quick-answers-on-editable-text",
     flag_descriptions::kEnableQuickAnswersOnEditableTextName,
     flag_descriptions::kEnableQuickAnswersOnEditableTextDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswersOnEditableText)},

    {"enable-quick-answers-text-annotator",
     flag_descriptions::kEnableQuickAnswersTextAnnotatorName,
     flag_descriptions::kEnableQuickAnswersTextAnnotatorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswersTextAnnotator)},

    {"enable-quick-answers-translation",
     flag_descriptions::kEnableQuickAnswersTranslationName,
     flag_descriptions::kEnableQuickAnswersTranslationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswersTranslation)},

    {"enable-quick-answers-translation-cloud-api",
     flag_descriptions::kEnableQuickAnswersTranslationCloudAPIName,
     flag_descriptions::kEnableQuickAnswersTranslationCloudAPIDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswersTranslationCloudAPI)},

    {"enable-quick-answers-v2", flag_descriptions::kEnableQuickAnswersV2Name,
     flag_descriptions::kEnableQuickAnswersV2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickAnswersV2)},

    {kAssistantBetterOnboardingInternalName,
     flag_descriptions::kEnableAssistantBetterOnboardingName,
     flag_descriptions::kEnableAssistantBetterOnboardingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::assistant::features::kAssistantBetterOnboarding)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
    {"new-window-app-menu", flag_descriptions::kNewWindowAppMenuName,
     flag_descriptions::kNewWindowAppMenuDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kNewWindowAppMenu)},
>>>>>>> chromium

    {"instance-switcher", flag_descriptions::kInstanceSwitcherName,
     flag_descriptions::kInstanceSwitcherDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kInstanceSwitcher)},
#endif  // defined(OS_ANDROID)

    {"enable-gamepad-button-axis-events",
     flag_descriptions::kEnableGamepadButtonAxisEventsName,
     flag_descriptions::kEnableGamepadButtonAxisEventsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kEnableGamepadButtonAxisEvents)},

    {"restrict-gamepad-access", flag_descriptions::kRestrictGamepadAccessName,
     flag_descriptions::kRestrictGamepadAccessDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kRestrictGamepadAccess)},

    {"shared-clipboard-ui", flag_descriptions::kSharedClipboardUIName,
     flag_descriptions::kSharedClipboardUIDescription, kOsAll,
     FEATURE_VALUE_TYPE(kSharedClipboardUI)},

    {"sharing-prefer-vapid", flag_descriptions::kSharingPreferVapidName,
     flag_descriptions::kSharingPreferVapidDescription, kOsAll,
     FEATURE_VALUE_TYPE(kSharingPreferVapid)},

    {"sharing-send-via-sync", flag_descriptions::kSharingSendViaSyncName,
     flag_descriptions::kSharingSendViaSyncDescription, kOsAll,
     FEATURE_VALUE_TYPE(kSharingSendViaSync)},

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)
    {"sharing-hub-desktop-app-menu",
     flag_descriptions::kSharingHubDesktopAppMenuName,
     flag_descriptions::kSharingHubDesktopAppMenuDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(sharing_hub::kSharingHubDesktopAppMenu)},
    {"sharing-hub-desktop-omnibox",
     flag_descriptions::kSharingHubDesktopOmniboxName,
     flag_descriptions::kSharingHubDesktopOmniboxDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(sharing_hub::kSharingHubDesktopOmnibox)},
#endif  // defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"cros-labs-enable-overview-from-wallpaper",
     flag_descriptions::kEnterOverviewFromWallpaperName,
     flag_descriptions::kEnterOverviewFromWallpaperDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnterOverviewFromWallpaper)},
    {"enable-assistant-stereo-input",
     flag_descriptions::kEnableGoogleAssistantStereoInputName,
     flag_descriptions::kEnableGoogleAssistantStereoInputDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::assistant::features::kEnableStereoAudioInput)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"ash-enable-pip-rounded-corners",
     flag_descriptions::kAshEnablePipRoundedCornersName,
     flag_descriptions::kAshEnablePipRoundedCornersDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPipRoundedCorners)},

#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-assistant-stereo-input",
     flag_descriptions::kEnableGoogleAssistantStereoInputName,
     flag_descriptions::kEnableGoogleAssistantStereoInputDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::assistant::features::kEnableStereoAudioInput)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"enable-audio-focus-enforcement",
     flag_descriptions::kEnableAudioFocusEnforcementName,
     flag_descriptions::kEnableAudioFocusEnforcementDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_session::features::kAudioFocusEnforcement)},
    {"enable-media-session-service",
     flag_descriptions::kEnableMediaSessionServiceName,
     flag_descriptions::kEnableMediaSessionServiceDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media_session::features::kMediaSessionService)},
    {"enable-gpu-service-logging",
     flag_descriptions::kEnableGpuServiceLoggingName,
     flag_descriptions::kEnableGpuServiceLoggingDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableGPUServiceLogging)},

#if !defined(OS_ANDROID)
    {"hardware-media-key-handling",
     flag_descriptions::kHardwareMediaKeyHandling,
     flag_descriptions::kHardwareMediaKeyHandlingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kHardwareMediaKeyHandling)},
#endif

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"arc-window-predictor", flag_descriptions::kArcWindowPredictorName,
     flag_descriptions::kArcWindowPredictorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(full_restore::features::kArcWindowPredictor)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"app-management-intent-settings",
     flag_descriptions::kAppManagementIntentSettingsName,
     flag_descriptions::kAppManagementIntentSettingsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAppManagementIntentSettings)},
#endif
>>>>>>> chromium

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"app-service-adaptive-icon",
     flag_descriptions::kAppServiceAdaptiveIconName,
     flag_descriptions::kAppServiceAdaptiveIconDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAppServiceAdaptiveIcon)},

    {"app-service-external-protocol",
     flag_descriptions::kAppServiceExternalProtocolName,
     flag_descriptions::kAppServiceExternalProtocolDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAppServiceExternalProtocol)},

    {"arc-ghost-window", flag_descriptions::kArcGhostWindowName,
     flag_descriptions::kArcGhostWindowDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(full_restore::features::kArcGhostWindow)},

    {"arc-resize-lock", flag_descriptions::kArcResizeLockName,
     flag_descriptions::kArcResizeLockDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kArcResizeLock)},

    {"full-restore", flag_descriptions::kFullRestoreName,
     flag_descriptions::kFullRestoreDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(full_restore::features::kFullRestore)},

    {"use-fake-device-for-media-stream",
     flag_descriptions::kUseFakeDeviceForMediaStreamName,
     flag_descriptions::kUseFakeDeviceForMediaStreamDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kUseFakeDeviceForMediaStream)},
<<<<<<< HEAD

#if BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)
    {"enable-vbr-encode-acceleration",
     flag_descriptions::kChromeOSHWVBREncodingName,
     flag_descriptions::kChromeOSHWVBREncodingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kChromeOSHWVBREncoding)},
#if defined(ARCH_CPU_ARM_FAMILY)
    {"use-gl-scaling", flag_descriptions::kUseGLForScalingName,
     flag_descriptions::kUseGLForScalingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kUseGLForScaling)},
    {"prefer-gl-image-processor",
     flag_descriptions::kPreferGLImageProcessorName,
     flag_descriptions::kPreferGLImageProcessorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kPreferGLImageProcessor)},
    {"prefer-software-mt21", flag_descriptions::kPreferSoftwareMT21Name,
     flag_descriptions::kPreferSoftwareMT21Description, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kPreferSoftwareMT21)},
    {"enable-protected-vulkan-detiling",
     flag_descriptions::kEnableProtectedVulkanDetilingName,
     flag_descriptions::kEnableProtectedVulkanDetilingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kEnableProtectedVulkanDetiling)},
    {"enable-arm-hwdrm-10bit-overlays",
     flag_descriptions::kEnableArmHwdrm10bitOverlaysName,
     flag_descriptions::kEnableArmHwdrm10bitOverlaysDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kEnableArmHwdrm10bitOverlays)},
#if BUILDFLAG(USE_CHROMEOS_PROTECTED_MEDIA)
    {"enable-arm-hwdrm", flag_descriptions::kEnableArmHwdrmName,
     flag_descriptions::kEnableArmHwdrmDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kEnableArmHwdrm)},
#endif  // BUILDFLAG(USE_CHROMEOS_PROTECTED_MEDIA)
#endif  // defined(ARCH_CPU_ARM_FAMILY)
#endif  // BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)
#endif  // BUILDFLAG(IS_CHROMEOS)
=======

    {"intent-picker-pwa-persistence",
     flag_descriptions::kIntentPickerPWAPersistenceName,
     flag_descriptions::kIntentPickerPWAPersistenceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kIntentPickerPWAPersistence)},

    {"intent-handling-sharing", flag_descriptions::kIntentHandlingSharingName,
     flag_descriptions::kIntentHandlingSharingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kIntentHandlingSharing)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_WIN)
    {"d3d11-video-decoder", flag_descriptions::kD3D11VideoDecoderName,
     flag_descriptions::kD3D11VideoDecoderDescription, kOsWin,
     FEATURE_VALUE_TYPE(media::kD3D11VideoDecoder)},
#endif

#if defined(OS_CHROMEOS) && BUILDFLAG(USE_CHROMEOS_MEDIA_ACCELERATION)
    // TODO(b/180051795): remove kOsLinux when lacros-chrome switches to
    // kOsCrOS.
    {"chromeos-direct-video-decoder",
     flag_descriptions::kChromeOSDirectVideoDecoderName,
     flag_descriptions::kChromeOSDirectVideoDecoderDescription,
     kOsCrOS | kOsLinux,
     FEATURE_VALUE_TYPE(media::kUseChromeOSDirectVideoDecoder)},
#endif
>>>>>>> chromium

#if defined(OS_ANDROID)
    {"deprecate-menagerie-api", flag_descriptions::kDeprecateMenagerieAPIName,
     flag_descriptions::kDeprecateMenagerieAPIDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(switches::kDeprecateMenagerieAPI)},
    {"wipe-data-on-child-account-signin",
     flag_descriptions::kWipeDataOnChildAccountSigninName,
     flag_descriptions::kWipeDataOnChildAccountSigninDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(switches::kWipeDataOnChildAccountSignin)},
    {"mobile-identity-consistency",
     flag_descriptions::kMobileIdentityConsistencyName,
     flag_descriptions::kMobileIdentityConsistencyDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(signin::kMobileIdentityConsistency)},
    {"mobile-identity-consistency-var",
     flag_descriptions::kMobileIdentityConsistencyVarName,
     flag_descriptions::kMobileIdentityConsistencyVarDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(signin::kMobileIdentityConsistencyVar,
                                    kMobileIdentityConsistencyVariations,
                                    "MobileIdentityConsistencyVar")},
    {"mobile-identity-consistency-fre",
     flag_descriptions::kMobileIdentityConsistencyFREName,
     flag_descriptions::kMobileIdentityConsistencyFREDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(signin::kMobileIdentityConsistencyFRE)},
    {"force-startup-signin-promo",
     flag_descriptions::kForceStartupSigninPromoName,
     flag_descriptions::kForceStartupSigninPromoDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(switches::kForceStartupSigninPromo)},
#endif  // defined(OS_ANDROID)

    {"autofill-use-improved-label-disambiguation",
     flag_descriptions::kAutofillUseImprovedLabelDisambiguationName,
     flag_descriptions::kAutofillUseImprovedLabelDisambiguationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillUseImprovedLabelDisambiguation)},

<<<<<<< HEAD
=======
    {"file-handling-api", flag_descriptions::kFileHandlingAPIName,
     flag_descriptions::kFileHandlingAPIDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kFileHandlingAPI)},

>>>>>>> chromium
    {"file-handling-icons", flag_descriptions::kFileHandlingIconsName,
     flag_descriptions::kFileHandlingIconsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kFileHandlingIcons)},

#if defined(TOOLKIT_VIEWS)
    {"installable-ink-drop", flag_descriptions::kInstallableInkDropName,
     flag_descriptions::kInstallableInkDropDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(views::kInstallableInkDropFeature)},
#endif  // defined(TOOLKIT_VIEWS)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-assistant-launcher-integration",
     flag_descriptions::kEnableAssistantLauncherIntegrationName,
     flag_descriptions::kEnableAssistantLauncherIntegrationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kEnableAssistantSearch)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(ENABLE_EXTENSIONS)
    {"strict-extension-isolation",
     flag_descriptions::kStrictExtensionIsolationName,
     flag_descriptions::kStrictExtensionIsolationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(extensions_features::kStrictExtensionIsolation)},
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)

    {"strict-origin-isolation", flag_descriptions::kStrictOriginIsolationName,
     flag_descriptions::kStrictOriginIsolationDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kStrictOriginIsolation)},

#if defined(OS_ANDROID)
    {"enable-logging-js-console-messages",
     flag_descriptions::kLogJsConsoleMessagesName,
     flag_descriptions::kLogJsConsoleMessagesDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kLogJsConsoleMessages)},
#endif  // OS_ANDROID

    {"enable-skia-renderer", flag_descriptions::kSkiaRendererName,
     flag_descriptions::kSkiaRendererDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kUseSkiaRenderer)},

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"allow-cross-device-feature-suite",
     flag_descriptions::kAllowCrossDeviceFeatureSuiteName,
     flag_descriptions::kAllowCrossDeviceFeatureSuiteDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAllowCrossDeviceFeatureSuite)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"allow-disable-mouse-acceleration",
     flag_descriptions::kAllowDisableMouseAccelerationName,
     flag_descriptions::kAllowDisableMouseAccelerationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAllowDisableMouseAcceleration)},
>>>>>>> chromium

    {"allow-repeated-updates", flag_descriptions::kAllowRepeatedUpdatesName,
     flag_descriptions::kAllowRepeatedUpdatesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAllowRepeatedUpdates)},

    {"allow-scroll-settings", flag_descriptions::kAllowScrollSettingsName,
     flag_descriptions::kAllowScrollSettingsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAllowScrollSettings)},

<<<<<<< HEAD
    {"block-telephony-device-phone-mute",
     flag_descriptions::kBlockTelephonyDevicePhoneMuteName,
     flag_descriptions::kBlockTelephonyDevicePhoneMuteDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kBlockTelephonyDevicePhoneMute)},

    {"enable-doze-mode-power-scheduler",
     flag_descriptions::kEnableDozeModePowerSchedulerName,
     flag_descriptions::kEnableDozeModePowerSchedulerDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableDozeModePowerScheduler)},

    {"enable-fast-ink-for-software-cursor",
     flag_descriptions::kEnableFastInkForSoftwareCursorName,
     flag_descriptions::kEnableFastInkForSoftwareCursorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableFastInkForSoftwareCursor)},

    {"enable-neural-palm-adaptive-hold",
     flag_descriptions::kEnableNeuralPalmAdaptiveHoldName,
     flag_descriptions::kEnableNeuralPalmAdaptiveHoldDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableNeuralPalmAdaptiveHold)},

    {"enable-heatmap-palm-detection",
     flag_descriptions::kEnableHeatmapPalmDetectionName,
     flag_descriptions::kEnableHeatmapPalmDetectionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableHeatmapPalmDetection)},
=======
    {"bluetooth-advertisement-monitoring",
     flag_descriptions::kBluetoothAdvertisementMonitoringName,
     flag_descriptions::kBluetoothAdvertisementMonitoringDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBluetoothAdvertisementMonitoring)},
>>>>>>> chromium

    {"enable-neural-stylus-palm-rejection",
     flag_descriptions::kEnableNeuralStylusPalmRejectionName,
     flag_descriptions::kEnableNeuralStylusPalmRejectionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableNeuralPalmDetectionFilter)},

    {"enable-os-feedback", flag_descriptions::kEnableOsFeedbackName,
     flag_descriptions::kEnableOsFeedbackDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kOsFeedback)},

    {"enable-palm-max-touch-major",
     flag_descriptions::kEnablePalmOnMaxTouchMajorName,
     flag_descriptions::kEnablePalmOnMaxTouchMajorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnablePalmOnMaxTouchMajor)},

    {"enable-palm-tool-type-palm",
     flag_descriptions::kEnablePalmOnToolTypePalmName,
     flag_descriptions::kEnablePalmOnToolTypePalmName, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnablePalmOnToolTypePalm)},

    {"enable-pci-guard-ui", flag_descriptions::kEnablePciguardUiName,
     flag_descriptions::kEnablePciguardUiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kEnablePciguardUi)},

    {"enable-heuristic-stylus-palm-rejection",
     flag_descriptions::kEnableHeuristicStylusPalmRejectionName,
     flag_descriptions::kEnableHeuristicStylusPalmRejectionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableHeuristicPalmDetectionFilter)},

<<<<<<< HEAD
    {"fast-pair-keyboards", flag_descriptions::kFastPairKeyboardsName,
     flag_descriptions::kFastPairKeyboardsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFastPairKeyboards)},

    {"fast-pair-pwa-companion", flag_descriptions::kFastPairPwaCompanionName,
     flag_descriptions::kFastPairPwaCompanionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFastPairPwaCompanion)},

    {"nearby-ble-v2", flag_descriptions::kEnableNearbyBleV2Name,
     flag_descriptions::kEnableNearbyBleV2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableNearbyBleV2)},

    {"nearby-ble-v2-extended-adv",
     flag_descriptions::kEnableNearbyBleV2ExtendedAdvertisingName,
     flag_descriptions::kEnableNearbyBleV2ExtendedAdvertisingDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableNearbyBleV2ExtendedAdvertising)},

    {"nearby-ble-v2-gatt-server",
     flag_descriptions::kEnableNearbyBleV2GattServerName,
     flag_descriptions::kEnableNearbyBleV2GattServerDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableNearbyBleV2GattServer)},

    {"nearby-bluetooth-classic-adv",
     flag_descriptions::kEnableNearbyBluetoothClassicAdvertisingName,
     flag_descriptions::kEnableNearbyBluetoothClassicAdvertisingDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableNearbyBluetoothClassicAdvertising)},

    {"nearby-mdns", flag_descriptions::kEnableNearbyMdnsName,
     flag_descriptions::kEnableNearbyMdnsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableNearbyMdns)},

    {"nearby-presence", flag_descriptions::kNearbyPresenceName,
     flag_descriptions::kNearbyPresenceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kNearbyPresence)},

    {"nearby-webrtc", flag_descriptions::kEnableNearbyWebRtcName,
     flag_descriptions::kEnableNearbyWebRtcDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNearbySharingWebRtc)},

    {"nearby-wifi-direct", flag_descriptions::kEnableNearbyWifiDirectName,
     flag_descriptions::kEnableNearbyWifiDirectDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNearbySharingWifiDirect)},

    {"nearby-wifi-lan", flag_descriptions::kEnableNearbyWifiLanName,
     flag_descriptions::kEnableNearbyWifiLanDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNearbySharingWifiLan)},

    {"pcie-billboard-notification",
     flag_descriptions::kPcieBillboardNotificationName,
     flag_descriptions::kPcieBillboardNotificationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPcieBillboardNotification)},
=======
    {"enable-hide-arc-media-notifications",
     flag_descriptions::kHideArcMediaNotificationsName,
     flag_descriptions::kHideArcMediaNotificationsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHideArcMediaNotifications)},

    {"reduce-display-notifications",
     flag_descriptions::kReduceDisplayNotificationsName,
     flag_descriptions::kReduceDisplayNotificationsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kReduceDisplayNotifications)},
>>>>>>> chromium

    {"use-search-click-for-right-click",
     flag_descriptions::kUseSearchClickForRightClickName,
     flag_descriptions::kUseSearchClickForRightClickDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kUseSearchClickForRightClick)},

<<<<<<< HEAD
=======
    {"show-metered-toggle", flag_descriptions::kMeteredShowToggleName,
     flag_descriptions::kMeteredShowToggleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kMeteredShowToggle)},

    {"wifi-sync-allow-deletes", flag_descriptions::kWifiSyncAllowDeletesName,
     flag_descriptions::kWifiSyncAllowDeletesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kWifiSyncAllowDeletes)},

    {"wifi-sync-android", flag_descriptions::kWifiSyncAndroidName,
     flag_descriptions::kWifiSyncAndroidDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kWifiSyncAndroid)},

    {"display-identification", flag_descriptions::kDisplayIdentificationName,
     flag_descriptions::kDisplayIdentificationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDisplayIdentification)},

>>>>>>> chromium
    {"display-alignment-assistance",
     flag_descriptions::kDisplayAlignmentAssistanceName,
     flag_descriptions::kDisplayAlignmentAssistanceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDisplayAlignAssist)},

    {"diagnostics-app", flag_descriptions::kDiagnosticsAppName,
     flag_descriptions::kDiagnosticsAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kDiagnosticsApp)},

    {"diagnostics-app-navigation",
     flag_descriptions::kDiagnosticsAppNavigationName,
     flag_descriptions::kDiagnosticsAppNavigationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kDiagnosticsAppNavigation)},

    {"enable-hostname-setting", flag_descriptions::kEnableHostnameSettingName,
     flag_descriptions::kEnableHostnameSettingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kEnableHostnameSetting)},

    {"webui-dark-mode", flag_descriptions::kWebuiDarkModeName,
     flag_descriptions::kWebuiDarkModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kWebUIDarkMode)},

    {"select-to-speak-navigation-control",
     flag_descriptions::kSelectToSpeakNavigationControlName,
     flag_descriptions::kSelectToSpeakNavigationControlDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kSelectToSpeakNavigationControl)},

    {"enable-networking-in-diagnostics-app",
     flag_descriptions::kEnableNetworkingInDiagnosticsAppName,
     flag_descriptions::kEnableNetworkingInDiagnosticsAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kEnableNetworkingInDiagnosticsApp)},

    {"enable-oauth-ipp", flag_descriptions::kEnableOAuthIppName,
     flag_descriptions::kEnableOAuthIppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableOAuthIpp)},

<<<<<<< HEAD
    {"enable-search-customizable-shortcuts-in-launcher",
     flag_descriptions::kEnableSearchCustomizableShortcutsInLauncherName,
     flag_descriptions::kEnableSearchCustomizableShortcutsInLauncherDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSearchCustomizableShortcutsInLauncher)},

    {"enable-suspend-state-machine",
     flag_descriptions::kEnableSuspendStateMachineName,
     flag_descriptions::kEnableSuspendStateMachineDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSuspendStateMachine)},

    {"enable-input-device-settings-split",
     flag_descriptions::kEnableInputDeviceSettingsSplitName,
     flag_descriptions::kEnableInputDeviceSettingsSplitDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kInputDeviceSettingsSplit)},

    {"enable-peripheral-customization",
     flag_descriptions::kEnablePeripheralCustomizationName,
     flag_descriptions::kEnablePeripheralCustomizationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPeripheralCustomization)},

    {"enable-peripherals-logging",
     flag_descriptions::kEnablePeripheralsLoggingName,
     flag_descriptions::kEnablePeripheralsLoggingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnablePeripheralsLogging)},

    {"enable-peripheral-notification",
     flag_descriptions::kEnablePeripheralNotificationName,
     flag_descriptions::kEnablePeripheralNotificationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPeripheralNotification)},

    {"enable-accessibility-accelerator",
     flag_descriptions::kAccessibilityAcceleratorName,
     flag_descriptions::kAccessibilityAcceleratorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityAccelerator)},

    {"enable-accessibility-disable-touchpad",
     flag_descriptions::kAccessibilityDisableTouchpadName,
     flag_descriptions::kAccessibilityDisableTouchpadDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityDisableTouchpad)},

    {"enable-accessibility-flash-screen-feature",
     flag_descriptions::kAccessibilityFlashScreenFeatureName,
     flag_descriptions::kAccessibilityFlashScreenFeatureDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityFlashScreenFeature)},

    {"enable-accessibility-shake-to-locate",
     flag_descriptions::kAccessibilityShakeToLocateName,
     flag_descriptions::kAccessibilityShakeToLocateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityShakeToLocate)},

    {"enable-accessibility-service",
     flag_descriptions::kAccessibilityServiceName,
     flag_descriptions::kAccessibilityServiceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityService)},

    {"enable-accessibility-reduced-animations",
     flag_descriptions::kAccessibilityReducedAnimationsName,
     flag_descriptions::kAccessibilityReducedAnimationsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityReducedAnimations)},

    {"enable-accessibility-reduced-animations-in-kiosk",
     flag_descriptions::kAccessibilityReducedAnimationsInKioskName,
     flag_descriptions::kAccessibilityReducedAnimationsInKioskDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityReducedAnimationsInKiosk)},

    {"enable-accessibility-facegaze",
     flag_descriptions::kAccessibilityFaceGazeName,
     flag_descriptions::kAccessibilityFaceGazeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityFaceGaze)},

    {"enable-accessibility-magnifier-follows-chromevox",
     flag_descriptions::kAccessibilityMagnifierFollowsChromeVoxName,
     flag_descriptions::kAccessibilityMagnifierFollowsChromeVoxDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityMagnifierFollowsChromeVox)},

    {"enable-accessibility-manifest-v3-braille-ime",
     flag_descriptions::kAccessibilityManifestV3BrailleImeName,
     flag_descriptions::kAccessibilityManifestV3BrailleImeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityManifestV3BrailleIme)},

    {"enable-accessibility-manifest-v3-enhanced-network-tts",
     flag_descriptions::kAccessibilityManifestV3EnhancedNetworkTtsName,
     flag_descriptions::kAccessibilityManifestV3EnhancedNetworkTtsDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityManifestV3EnhancedNetworkTts)},

    {"enable-accessibility-mousekeys",
     flag_descriptions::kAccessibilityMouseKeysName,
     flag_descriptions::kAccessibilityMouseKeysDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kAccessibilityMouseKeys)},

    {"enable-pip-double-tap-to-resize",
     flag_descriptions::kPipDoubleTapToResizeName,
     flag_descriptions::kPipDoubleTapToResizeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPipDoubleTapToResize)},

    {"enable-pip-tuck", flag_descriptions::kPipTuckName,
     flag_descriptions::kPipTuckDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPipTuck)},

    {"event-based-log-upload", flag_descriptions::kEventBasedLogUpload,
     flag_descriptions::kEventBasedLogUploadDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEventBasedLogUpload)},

#endif  // BUILDFLAG(IS_CHROMEOS)
=======
    {"enable-shortcut-customization-app",
     flag_descriptions::kEnableShortcutCustomizationAppName,
     flag_descriptions::kEnableShortcutCustomizationAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kShortcutCustomizationApp)},

    {"enhanced-network-voices", flag_descriptions::kEnhancedNetworkVoicesName,
     flag_descriptions::kEnhancedNetworkVoicesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnhancedNetworkVoices)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"enable-extended-sync-promos-capability",
     flag_descriptions::kEnableExtendedSyncPromosCapabilityName,
     flag_descriptions::kEnableExtendedSyncPromosCapabilityDescription,
     flags_ui::kOsAndroid, FEATURE_VALUE_TYPE(switches::kMinorModeSupport)},

    {"enable-fenced-frames", flag_descriptions::kEnableFencedFramesName,
     flag_descriptions::kEnableFencedFramesDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kFencedFrames,
                                    kFencedFramesImplementationTypeVariations,
                                    "FencedFrames")},

    {"enable-portals", flag_descriptions::kEnablePortalsName,
     flag_descriptions::kEnablePortalsDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kPortals)},
    {"enable-portals-cross-origin",
     flag_descriptions::kEnablePortalsCrossOriginName,
     flag_descriptions::kEnablePortalsCrossOriginDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kPortalsCrossOrigin)},
    {"enable-autofill-credit-card-authentication",
     flag_descriptions::kEnableAutofillCreditCardAuthenticationName,
     flag_descriptions::kEnableAutofillCreditCardAuthenticationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillCreditCardAuthentication)},

    {"storage-access-api", flag_descriptions::kStorageAccessAPIName,
     flag_descriptions::kStorageAccessAPIDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kStorageAccessAPI)},

    {"enable-removing-all-third-party-cookies",
     flag_descriptions::kEnableRemovingAllThirdPartyCookiesName,
     flag_descriptions::kEnableRemovingAllThirdPartyCookiesDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         browsing_data::features::kEnableRemovingAllThirdPartyCookies)},

#if defined(OS_MAC)
    {"enterprise-reporting-api-keychain-recreation",
     flag_descriptions::kEnterpriseReportingApiKeychainRecreationName,
     flag_descriptions::kEnterpriseReportingApiKeychainRecreationDescription,
     kOsMac,
     FEATURE_VALUE_TYPE(features::kEnterpriseReportingApiKeychainRecreation)},
#endif  // defined(OS_MAC)

#if !defined(OS_ANDROID)
    {"enterprise-realtime-extension-request",
     flag_descriptions::kEnterpriseRealtimeExtensionRequestName,
     flag_descriptions::kEnterpriseRealtimeExtensionRequestDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         features::kEnterpriseRealtimeExtensionRequest,
         kEnterpriseRealtimeExtensionRequestVariation,
         "EnterpriseRealtimeExtensionRequest")},
#endif  // !defined(OS_ANDROID)

    {"enable-unsafe-webgpu", flag_descriptions::kUnsafeWebGPUName,
     flag_descriptions::kUnsafeWebGPUDescription, kOsMac | kOsLinux | kOsWin,
     SINGLE_VALUE_TYPE(switches::kEnableUnsafeWebGPU)},
    {"enable-unsafe-webgpu-service",
     flag_descriptions::kUnsafeWebGPUServiceName,
     flag_descriptions::kUnsafeWebGPUServiceDescription,
     kOsMac | kOsLinux | kOsWin, FEATURE_VALUE_TYPE(features::kWebGPUService)},

    {"enable-unsafe-fast-js-calls", flag_descriptions::kUnsafeFastJSCallsName,
     flag_descriptions::kUnsafeFastJSCallsDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableUnsafeFastJSCalls)},

#if defined(OS_ANDROID)
    {"autofill-use-mobile-label-disambiguation",
     flag_descriptions::kAutofillUseMobileLabelDisambiguationName,
     flag_descriptions::kAutofillUseMobileLabelDisambiguationDescription,
     kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         autofill::features::kAutofillUseMobileLabelDisambiguation,
         kAutofillUseMobileLabelDisambiguationVariations,
         "AutofillUseMobileLabelDisambiguation")},
#endif  // defined(OS_ANDROID)

    {"autofill-prune-suggestions",
     flag_descriptions::kAutofillPruneSuggestionsName,
     flag_descriptions::kAutofillPruneSuggestionsDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillPruneSuggestions)},

    {"allow-sync-xhr-in-page-dismissal",
     flag_descriptions::kAllowSyncXHRInPageDismissalName,
     flag_descriptions::kAllowSyncXHRInPageDismissalDescription,
     kOsAll | kDeprecated,
     FEATURE_VALUE_TYPE(blink::features::kAllowSyncXHRInPageDismissal)},

    {"enable-sync-requires-policies-loaded",
     flag_descriptions::kEnableSyncRequiresPoliciesLoadedName,
     flag_descriptions::kEnableSyncRequiresPoliciesLoadedDescription, kOsAll,
     FEATURE_VALUE_TYPE(switches::kSyncRequiresPoliciesLoaded)},

    {"enable-policy-blocklist-throttle-requires-policies-loaded",
     flag_descriptions::
         kEnablePolicyBlocklistThrottleRequiresPoliciesLoadedName,
     flag_descriptions::
         kEnablePolicyBlocklistThrottleRequiresPoliciesLoadedDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         policy::features::kPolicyBlocklistThrottleRequiresPoliciesLoaded)},

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"game-dashboard-game-pwas", flag_descriptions::kGameDashboardGamePWAs,
     flag_descriptions::kGameDashboardGamePWAsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kGameDashboardGamePWAs)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"auto-screen-brightness", flag_descriptions::kAutoScreenBrightnessName,
     flag_descriptions::kAutoScreenBrightnessDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAutoScreenBrightness)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"privacy-sandbox-settings", flag_descriptions::kPrivacySandboxSettingsName,
     flag_descriptions::kPrivacySandboxSettingsDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kPrivacySandboxSettings)},

    {"privacy-sandbox-settings-2",
     flag_descriptions::kPrivacySandboxSettings2Name,
     flag_descriptions::kPrivacySandboxSettings2Description,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kPrivacySandboxSettings2)},

#if defined(OS_ANDROID)
    {"metrics-settings-android", flag_descriptions::kMetricsSettingsAndroidName,
     flag_descriptions::kMetricsSettingsAndroidDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kMetricsSettingsAndroid,
                                    kMetricsSettingsAndroidVariations,
                                    "MetricsSettingsAndroid")},
#endif

    {"search-history-link", flag_descriptions::kSearchHistoryLinkName,
     flag_descriptions::kSearchHistoryLinkDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kSearchHistoryLink)},

#if defined(OS_ANDROID)
    {"safe-browsing-client-side-detection-android",
     flag_descriptions::kSafeBrowsingClientSideDetectionAndroidName,
     flag_descriptions::kSafeBrowsingClientSideDetectionAndroidDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(safe_browsing::kClientSideDetectionForAndroid)},

    {"safe-browsing-enhanced-protection-promo-android",
     flag_descriptions::kEnhancedProtectionPromoAndroidName,
     flag_descriptions::kEnhancedProtectionPromoAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kEnhancedProtectionPromoCard)},

    {"safe-browsing-passwordcheck-integration-for-saved-passwords-android",
     flag_descriptions::
         kSafeBrowsingPasswordCheckIntegrationForSavedPasswordsAndroidName,
     flag_descriptions::
         kSafeBrowsingPasswordCheckIntegrationForSavedPasswordsAndroidDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         safe_browsing::
             kSafeBrowsingPasswordCheckIntegrationForSavedPasswordsAndroid)},
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"gesture-properties-dbus-service",
     flag_descriptions::kEnableGesturePropertiesDBusServiceName,
     flag_descriptions::kEnableGesturePropertiesDBusServiceDescription, kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::features::kGesturePropertiesDBusService)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
     FEATURE_VALUE_TYPE(chromeos::features::kGesturePropertiesDBusService)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"ev-details-in-page-info", flag_descriptions::kEvDetailsInPageInfoName,
     flag_descriptions::kEvDetailsInPageInfoDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kEvDetailsInPageInfo)},

    {"enable-autofill-credit-card-upload-feedback",
     flag_descriptions::kEnableAutofillCreditCardUploadFeedbackName,
     flag_descriptions::kEnableAutofillCreditCardUploadFeedbackDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillCreditCardUploadFeedback)},

    {"font-access", flag_descriptions::kFontAccessAPIName,
     flag_descriptions::kFontAccessAPIDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kFontAccess)},

    {"font-access-persistent", flag_descriptions::kFontAccessPersistentName,
     flag_descriptions::kFontAccessPersistentDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kFontAccessPersistent)},

    {"mouse-subframe-no-implicit-capture",
     flag_descriptions::kMouseSubframeNoImplicitCaptureName,
     flag_descriptions::kMouseSubframeNoImplicitCaptureDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kMouseSubframeNoImplicitCapture)},

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) || \
    defined(OS_CHROMEOS)
    {"global-media-controls", flag_descriptions::kGlobalMediaControlsName,
     flag_descriptions::kGlobalMediaControlsDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(media::kGlobalMediaControls)},

    {"global-media-controls-for-cast",
     flag_descriptions::kGlobalMediaControlsForCastName,
     flag_descriptions::kGlobalMediaControlsForCastDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(media::kGlobalMediaControlsForCast)},

    {"global-media-controls-for-chromeos",
     flag_descriptions::kGlobalMediaControlsForChromeOSName,
     flag_descriptions::kGlobalMediaControlsForChromeOSDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kGlobalMediaControlsForChromeOS)},

    {"global-media-controls-modern-ui",
     flag_descriptions::kGlobalMediaControlsModernUIName,
     flag_descriptions::kGlobalMediaControlsModernUIDescription,
     kOsWin | kOsMac | kOsLinux | kOsCrOS,
     FEATURE_VALUE_TYPE(media::kGlobalMediaControlsModernUI)},

    {"global-media-controls-picture-in-picture",
     flag_descriptions::kGlobalMediaControlsPictureInPictureName,
     flag_descriptions::kGlobalMediaControlsPictureInPictureDescription,
     kOsWin | kOsMac | kOsLinux | kOsCrOS,
     FEATURE_VALUE_TYPE(media::kGlobalMediaControlsPictureInPicture)},

    {"global-media-controls-seamless-transfer",
     flag_descriptions::kGlobalMediaControlsSeamlessTransferName,
     flag_descriptions::kGlobalMediaControlsSeamlessTransferDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(media::kGlobalMediaControlsSeamlessTransfer)},

    {"global-media-controls-overlay-controls",
     flag_descriptions::kGlobalMediaControlsOverlayControlsName,
     flag_descriptions::kGlobalMediaControlsOverlayControlsDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(media::kGlobalMediaControlsOverlayControls)},
#endif  // defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) ||
        // defined(OS_CHROMEOS)

    {"safety-tips", flag_descriptions::kSafetyTipName,
     flag_descriptions::kSafetyTipDescription, kOsAll,
     FEATURE_VALUE_TYPE(security_state::features::kSafetyTipUI)},

    {"turn-off-streaming-media-caching-on-battery",
     flag_descriptions::kTurnOffStreamingMediaCachingOnBatteryName,
     flag_descriptions::kTurnOffStreamingMediaCachingOnBatteryDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(net::features::kTurnOffStreamingMediaCachingOnBattery)},

    {"turn-off-streaming-media-caching-always",
     flag_descriptions::kTurnOffStreamingMediaCachingAlwaysName,
     flag_descriptions::kTurnOffStreamingMediaCachingAlwaysDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kTurnOffStreamingMediaCachingAlways)},

<<<<<<< HEAD
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
    {"enable-network-service-sandbox",
     flag_descriptions::kEnableNetworkServiceSandboxName,
     flag_descriptions::kEnableNetworkServiceSandboxDescription,
     kOsLinux | kOsCrOS,
     FEATURE_VALUE_TYPE(sandbox::policy::features::kNetworkServiceSandbox)},
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(ALLOW_OOP_VIDEO_DECODER)
    {"use-out-of-process-video-decoding",
     flag_descriptions::kUseOutOfProcessVideoDecodingName,
     flag_descriptions::kUseOutOfProcessVideoDecodingDescription,
     kOsLinux | kOsCrOS,
     FEATURE_VALUE_TYPE(media::kUseOutOfProcessVideoDecoding)},
#endif  // BUILDFLAG(ALLOW_OOP_VIDEO_DECODER)
=======
    {"enable-cooperative-scheduling",
     flag_descriptions::kCooperativeSchedulingName,
     flag_descriptions::kCooperativeSchedulingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kCooperativeScheduling)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-assistant-routines",
     flag_descriptions::kEnableAssistantRoutinesName,
     flag_descriptions::kEnableAssistantRoutinesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::assistant::features::kAssistantRoutines)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"notification-scheduler", flag_descriptions::kNotificationSchedulerName,
     flag_descriptions::kNotificationSchedulerDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(notifications::features::kNotificationScheduleService)},

    {"notification-scheduler-debug-options",
     flag_descriptions::kNotificationSchedulerDebugOptionName,
     flag_descriptions::kNotificationSchedulerDebugOptionDescription,
     kOsAndroid, MULTI_VALUE_TYPE(kNotificationSchedulerChoices)},

#if defined(OS_ANDROID)

    {"use-notification-compat-builder",
     flag_descriptions::kUseNotificationCompatBuilderName,
     flag_descriptions::kUseNotificationCompatBuilderDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kUseNotificationCompatBuilder)},

    {"debug-chime-notification",
     flag_descriptions::kChimeAlwaysShowNotificationName,
     flag_descriptions::kChimeAlwaysShowNotificationDescription, kOsAndroid,
     SINGLE_VALUE_TYPE(notifications::switches::kDebugChimeNotification)},

    {"use-chime-android-sdk", flag_descriptions::kChimeAndroidSdkName,
     flag_descriptions::kChimeAndroidSdkDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(notifications::features::kUseChimeAndroidSdk)},

#endif  // defined(OS_ANDROID)

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"scalable-iph-debug", flag_descriptions::kScalableIphDebugName,
     flag_descriptions::kScalableIphDebugDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kScalableIphDebug)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"lock-screen-media-controls",
     flag_descriptions::kLockScreenMediaControlsName,
     flag_descriptions::kLockScreenMediaControlsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kLockScreenMediaControls)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"contextual-nudges", flag_descriptions::kContextualNudgesName,
     flag_descriptions::kContextualNudgesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kContextualNudges)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"settings-app-notification-settings",
     flag_descriptions::kSettingsAppNotificationSettingsName,
     flag_descriptions::kSettingsAppNotificationSettingsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSettingsAppNotificationSettings)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"decode-jpeg-images-to-yuv",
     flag_descriptions::kDecodeJpeg420ImagesToYUVName,
     flag_descriptions::kDecodeJpeg420ImagesToYUVDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kDecodeJpeg420ImagesToYUV)},

    {"decode-webp-images-to-yuv",
     flag_descriptions::kDecodeLossyWebPImagesToYUVName,
     flag_descriptions::kDecodeLossyWebPImagesToYUVDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kDecodeLossyWebPImagesToYUV)},

    {"dns-httpssvc", flag_descriptions::kDnsHttpssvcName,
     flag_descriptions::kDnsHttpssvcDescription,
     kOsMac | kOsWin | kOsCrOS | kOsAndroid,
     FEATURE_VALUE_TYPE(net::features::kDnsHttpssvc)},

    {"dns-over-https", flag_descriptions::kDnsOverHttpsName,
     flag_descriptions::kDnsOverHttpsDescription,
     kOsMac | kOsWin | kOsCrOS | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kDnsOverHttps)},

    {"web-bundles", flag_descriptions::kWebBundlesName,
     flag_descriptions::kWebBundlesDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebBundles)},

#if defined(OS_ANDROID)
    {"web-otp-backend", flag_descriptions::kWebOtpBackendName,
     flag_descriptions::kWebOtpBackendDescription, kOsAndroid,
     MULTI_VALUE_TYPE(kWebOtpBackendChoices)},

    {"darken-websites-checkbox-in-themes-setting",
     flag_descriptions::kDarkenWebsitesCheckboxInThemesSettingName,
     flag_descriptions::kDarkenWebsitesCheckboxInThemesSettingDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kDarkenWebsitesCheckboxInThemesSetting)},
#endif  // defined(OS_ANDROID)

    {"enable-autofill-upi-vpa", flag_descriptions::kAutofillSaveAndFillVPAName,
     flag_descriptions::kAutofillSaveAndFillVPADescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillSaveAndFillVPA)},

    {"quiet-notification-prompts",
     flag_descriptions::kQuietNotificationPromptsName,
     flag_descriptions::kQuietNotificationPromptsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kQuietNotificationPrompts,
                                    kQuietNotificationPromptsVariations,
                                    "QuietNotificationPrompts")},
    {"abusive-notification-permission-revocation",
     flag_descriptions::kAbusiveNotificationPermissionRevocationName,
     flag_descriptions::kAbusiveNotificationPermissionRevocationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kAbusiveNotificationPermissionRevocation)},

#if defined(OS_ANDROID)
    {"context-menu-google-lens-chip",
     flag_descriptions::kContextMenuGoogleLensChipName,
     flag_descriptions::kContextMenuGoogleLensChipDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextMenuGoogleLensChip)},

    {"context-menu-search-with-google-lens",
     flag_descriptions::kContextMenuSearchWithGoogleLensName,
     flag_descriptions::kContextMenuSearchWithGoogleLensDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextMenuSearchWithGoogleLens)},

    {"context-menu-shop-with-google-lens",
     flag_descriptions::kContextMenuShopWithGoogleLensName,
     flag_descriptions::kContextMenuShopWithGoogleLensDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kContextMenuShopWithGoogleLens)},

    {"context-menu-search-and-shop-with-google-lens",
     flag_descriptions::kContextMenuSearchAndShopWithGoogleLensName,
     flag_descriptions::kContextMenuSearchAndShopWithGoogleLensDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kContextMenuSearchAndShopWithGoogleLens)},

    {"context-menu-translate-with-google-lens",
     flag_descriptions::kContextMenuTranslateWithGoogleLensName,
     flag_descriptions::kContextMenuTranslateWithGoogleLensDescription,
     kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         chrome::android::kContextMenuTranslateWithGoogleLens,
         kLensContextMenuTranslateVariations,
         "LensContextMenuTranslate")},

    {"google-lens-sdk-intent", flag_descriptions::kGoogleLensSdkIntentName,
     flag_descriptions::kGoogleLensSdkIntentDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kGoogleLensSdkIntent)},

    {"lens-camera-assisted-search",
     flag_descriptions::kLensCameraAssistedSearchName,
     flag_descriptions::kLensCameraAssistedSearchDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kLensCameraAssistedSearch,
                                    kLensCameraAssistedSearchVariations,
                                    "OmniboxAssistantVoiceSearch")},
#endif  // defined(OS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-suggested-files", flag_descriptions::kEnableSuggestedFilesName,
     flag_descriptions::kEnableSuggestedFilesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kEnableSuggestedFiles)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"autofill-always-return-cloud-tokenized-card",
     flag_descriptions::kAutofillAlwaysReturnCloudTokenizedCardName,
     flag_descriptions::kAutofillAlwaysReturnCloudTokenizedCardDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillAlwaysReturnCloudTokenizedCard)},

    {"back-forward-cache", flag_descriptions::kBackForwardCacheName,
     flag_descriptions::kBackForwardCacheDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kBackForwardCache,
                                    kBackForwardCacheVariations,
                                    "BackForwardCache")},

<<<<<<< HEAD
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_ANDROID)
=======
    {"impulse-scroll-animations",
     flag_descriptions::kImpulseScrollAnimationsName,
     flag_descriptions::kImpulseScrollAnimationsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kImpulseScrollAnimations)},

    {"percent-based-scrolling", flag_descriptions::kPercentBasedScrollingName,
     flag_descriptions::kPercentBasedScrollingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kPercentBasedScrolling)},

    {"scroll-unification", flag_descriptions::kScrollUnificationName,
     flag_descriptions::kScrollUnificationDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kScrollUnification)},

#if defined(OS_WIN)
>>>>>>> chromium
    {"elastic-overscroll", flag_descriptions::kElasticOverscrollName,
     flag_descriptions::kElasticOverscrollDescription, kOsWin | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kElasticOverscroll)},
#elif defined(OS_ANDROID)
    {"elastic-overscroll", flag_descriptions::kElasticOverscrollName,
     flag_descriptions::kElasticOverscrollDescription, kOsWin | kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kElasticOverscroll,
                                    kElasticOverscrollVariations,
                                    "ElasticOverscroll")},
#endif

<<<<<<< HEAD
#if !BUILDFLAG(IS_ANDROID)
    {"element-capture", flag_descriptions::kElementCaptureName,
     flag_descriptions::kElementCaptureDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kElementCapture)},
#endif

    {"device-posture", flag_descriptions::kDevicePostureName,
     flag_descriptions::kDevicePostureDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kDevicePosture)},

    {"viewport-segments", flag_descriptions::kViewportSegmentsName,
     flag_descriptions::kViewportSegmentsDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kViewportSegments)},

#if BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"enable-assistant-aec", flag_descriptions::kEnableGoogleAssistantAecName,
     flag_descriptions::kEnableGoogleAssistantAecDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::assistant::features::kAssistantAudioEraser)},
#endif

#if defined(OS_WIN)
    {"enable-winrt-geolocation-implementation",
     flag_descriptions::kWinrtGeolocationImplementationName,
     flag_descriptions::kWinrtGeolocationImplementationDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kWinrtGeolocationImplementation)},
#endif

#if defined(OS_MAC)
    {"enable-core-location-backend",
     flag_descriptions::kMacCoreLocationBackendName,
     flag_descriptions::kMacCoreLocationBackendDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kMacCoreLocationBackend)},
#endif

#if defined(OS_MAC)
    {"enable-core-location-implementation",
     flag_descriptions::kMacCoreLocationImplementationName,
     flag_descriptions::kMacCoreLocationImplementationDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kMacCoreLocationImplementation)},
#endif

#if !defined(OS_ANDROID)
    {"mute-notification-snooze-action",
     flag_descriptions::kMuteNotificationSnoozeActionName,
     flag_descriptions::kMuteNotificationSnoozeActionDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kMuteNotificationSnoozeAction)},
#endif  // !defined(OS_ANDROID)

#if defined(OS_MAC)
    {"enable-new-mac-notification-api",
     flag_descriptions::kNewMacNotificationAPIName,
     flag_descriptions::kNewMacNotificationAPIDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kNewMacNotificationAPI)},
    {"notifications-via-helper-app",
     flag_descriptions::kNotificationsViaHelperAppName,
     flag_descriptions::kNotificationsViaHelperAppDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kNotificationsViaHelperApp)},
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"exo-gamepad-vibration", flag_descriptions::kExoGamepadVibrationName,
     flag_descriptions::kExoGamepadVibrationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kGamepadVibration)},
    {"exo-lock-notification", flag_descriptions::kExoLockNotificationName,
     flag_descriptions::kExoLockNotificationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kExoLockNotification)},
    {"exo-ordinal-motion", flag_descriptions::kExoOrdinalMotionName,
     flag_descriptions::kExoOrdinalMotionDescription, kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::features::kExoOrdinalMotion)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
     FEATURE_VALUE_TYPE(chromeos::features::kExoOrdinalMotion)},
    {"exo-pointer-lock", flag_descriptions::kExoPointerLockName,
     flag_descriptions::kExoPointerLockDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kExoPointerLock)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

#if defined(OS_MAC)
    {"metal", flag_descriptions::kMetalName,
     flag_descriptions::kMetalDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kMetal)},
    {"screentime", flag_descriptions::kScreenTimeName,
     flag_descriptions::kScreenTimeDescription, kOsMac,
     FEATURE_VALUE_TYPE(screentime::kScreenTime)},
#endif

    {"enable-de-jelly", flag_descriptions::kEnableDeJellyName,
     flag_descriptions::kEnableDeJellyDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableDeJelly)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-cros-action-recorder",
     flag_descriptions::kEnableCrOSActionRecorderName,
     flag_descriptions::kEnableCrOSActionRecorderDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kEnableCrOSActionRecorderChoices)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"enable-heavy-ad-intervention",
     flag_descriptions::kHeavyAdInterventionName,
     flag_descriptions::kHeavyAdInterventionDescription, kOsAll,
     FEATURE_VALUE_TYPE(heavy_ad_intervention::features::kHeavyAdIntervention)},

    {"heavy-ad-privacy-mitigations",
     flag_descriptions::kHeavyAdPrivacyMitigationsName,
     flag_descriptions::kHeavyAdPrivacyMitigationsDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         heavy_ad_intervention::features::kHeavyAdPrivacyMitigations)},

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"crostini-container-install",
     flag_descriptions::kCrostiniContainerInstallName,
     flag_descriptions::kCrostiniContainerInstallDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kCrostiniContainerChoices)},
    {"help-app-app-detail-page", flag_descriptions::kHelpAppAppDetailPageName,
     flag_descriptions::kHelpAppAppDetailPageDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHelpAppAppDetailPage)},
    {"help-app-apps-list", flag_descriptions::kHelpAppAppsListName,
     flag_descriptions::kHelpAppAppsListDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHelpAppAppsList)},
    {"help-app-auto-trigger-install-dialog",
     flag_descriptions::kHelpAppAutoTriggerInstallDialogName,
     flag_descriptions::kHelpAppAutoTriggerInstallDialogDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHelpAppAutoTriggerInstallDialog)},
    {"help-app-home-page-app-articles",
     flag_descriptions::kHelpAppHomePageAppArticlesName,
     flag_descriptions::kHelpAppHomePageAppArticlesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHelpAppHomePageAppArticles)},
    {"help-app-launcher-search", flag_descriptions::kHelpAppLauncherSearchName,
     flag_descriptions::kHelpAppLauncherSearchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHelpAppLauncherSearch)},
    {"help-app-onboarding-revamp",
     flag_descriptions::kHelpAppOnboardingRevampName,
     flag_descriptions::kHelpAppOnboardingRevampDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHelpAppOnboardingRevamp)},
    {"help-app-opens-instead-of-release-notes-notification",
     flag_descriptions::kHelpAppOpensInsteadOfReleaseNotesNotificationName,
     flag_descriptions::
         kHelpAppOpensInsteadOfReleaseNotesNotificationDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kHelpAppOpensInsteadOfReleaseNotesNotification)},
    {"media-app-pdf-mahi", flag_descriptions::kMediaAppPdfMahiName,
     flag_descriptions::kMediaAppPdfMahiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kMediaAppPdfMahi)},
    {"on-device-app-controls", flag_descriptions::kOnDeviceAppControlsName,
     flag_descriptions::kOnDeviceAppControlsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kForceOnDeviceAppControlsForAllRegions)},
=======
#if !BUILDFLAG(DISABLE_FTP_SUPPORT)
    {"enable-ftp", flag_descriptions::kEnableFtpName,
     flag_descriptions::kEnableFtpDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kFtpProtocol)},
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"crosh-swa", flag_descriptions::kCroshSWAName,
     flag_descriptions::kCroshSWADescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCroshSWA)},
    {"crostini-use-buster-image",
     flag_descriptions::kCrostiniUseBusterImageName,
     flag_descriptions::kCrostiniUseBusterImageDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrostiniUseBusterImage)},
    {"crostini-disk-resizing", flag_descriptions::kCrostiniDiskResizingName,
     flag_descriptions::kCrostiniDiskResizingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrostiniDiskResizing)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
    {"homepage-promo-card", flag_descriptions::kHomepagePromoCardName,
     flag_descriptions::kHomepagePromoCardDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(chrome::android::kHomepagePromoCard,
                                    kHomepagePromoCardVariations,
                                    "HomepagePromoAndroid")},
#endif  // defined(OS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"split-settings-sync", flag_descriptions::kSplitSettingsSyncName,
     flag_descriptions::kSplitSettingsSyncDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kSplitSettingsSync)},
    {"os-settings-app-notifications-page",
     flag_descriptions::kOsSettingsAppNotificationsPageName,
     flag_descriptions::kOsSettingsAppNotificationsPageDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kOsSettingsAppNotificationsPage)},
    {"os-settings-deep-linking", flag_descriptions::kOsSettingsDeepLinkingName,
     flag_descriptions::kOsSettingsDeepLinkingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kOsSettingsDeepLinking)},
    {"help-app-background-page", flag_descriptions::kHelpAppBackgroundPageName,
     flag_descriptions::kHelpAppBackgroundPageDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kHelpAppBackgroundPage)},
    {"help-app-discover-tab", flag_descriptions::kHelpAppDiscoverTabName,
     flag_descriptions::kHelpAppDiscoverTabDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kHelpAppDiscoverTab)},
    {"help-app-launcher-search", flag_descriptions::kHelpAppLauncherSearchName,
     flag_descriptions::kHelpAppLauncherSearchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kHelpAppLauncherSearch)},
    {"help-app-search-service-integration",
     flag_descriptions::kHelpAppSearchServiceIntegrationName,
     flag_descriptions::kHelpAppSearchServiceIntegrationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kHelpAppSearchServiceIntegration)},
    {"media-app-annotation", flag_descriptions::kMediaAppAnnotationName,
     flag_descriptions::kMediaAppAnnotationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kMediaAppAnnotation)},
    {"media-app-display-exif", flag_descriptions::kMediaAppDisplayExifName,
     flag_descriptions::kMediaAppDisplayExifDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kMediaAppAnnotation)},
    {"media-app-handles-pdf", flag_descriptions::kMediaAppHandlesPdfName,
     flag_descriptions::kMediaAppHandlesPdfDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kMediaAppHandlesPdf)},
    {"release-notes-notification",
     flag_descriptions::kReleaseNotesNotificationName,
     flag_descriptions::kReleaseNotesNotificationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kReleaseNotesNotification)},
>>>>>>> chromium
    {"release-notes-notification-all-channels",
     flag_descriptions::kReleaseNotesNotificationAllChannelsName,
     flag_descriptions::kReleaseNotesNotificationAllChannelsDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::features::kReleaseNotesNotificationAllChannels)},
    {"use-stork-smds-server-address",
     flag_descriptions::kUseStorkSmdsServerAddressName,
     flag_descriptions::kUseStorkSmdsServerAddressDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kUseStorkSmdsServerAddress)},
    {"use-wallpaper-staging-url",
     flag_descriptions::kUseWallpaperStagingUrlName,
     flag_descriptions::kUseWallpaperStagingUrlDescription, kOsCrOS,
<<<<<<< HEAD
     FEATURE_VALUE_TYPE(ash::features::kUseWallpaperStagingUrl)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
     FEATURE_VALUE_TYPE(chromeos::features::kUseWallpaperStagingUrl)},
    {"semantic-colors-debug-override",
     flag_descriptions::kSemanticColorsDebugOverrideName,
     flag_descriptions::kSemanticColorsDebugOverrideDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kSemanticColorsDebugOverride)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"autofill-enable-virtual-card",
     flag_descriptions::kAutofillEnableVirtualCardName,
     flag_descriptions::kAutofillEnableVirtualCardDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableVirtualCard)},

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_PAINT_PREVIEW) && BUILDFLAG(IS_ANDROID)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"account-id-migration", flag_descriptions::kAccountIdMigrationName,
     flag_descriptions::kAccountIdMigrationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(switches::kAccountIdMigration)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    // TODO(https://crbug.com/1032161): Implement and enable for ChromeOS.
    {"raw-clipboard", flag_descriptions::kRawClipboardName,
     flag_descriptions::kRawClipboardDescription, kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(blink::features::kRawClipboard)},

#if BUILDFLAG(ENABLE_PAINT_PREVIEW) && defined(OS_ANDROID)
>>>>>>> chromium
    {"paint-preview-demo", flag_descriptions::kPaintPreviewDemoName,
     flag_descriptions::kPaintPreviewDemoDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(paint_preview::kPaintPreviewDemo)},
    {"paint-preview-startup", flag_descriptions::kPaintPreviewStartupName,
     flag_descriptions::kPaintPreviewStartupDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(paint_preview::kPaintPreviewShowOnStartup,
                                    kPaintPreviewStartupVariations,
                                    "PaintPreviewShowOnStartup")},
#endif  // ENABLE_PAINT_PREVIEW && defined(OS_ANDROID)

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"panel-self-refresh-2", flag_descriptions::kPanelSelfRefresh2Name,
     flag_descriptions::kPanelSelfRefresh2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(display::features::kPanelSelfRefresh2)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if defined(OS_ANDROID)
    {"block-external-form-redirects-no-gesture",
     flag_descriptions::kIntentBlockExternalFormRedirectsNoGestureName,
     flag_descriptions::kIntentBlockExternalFormRedirectsNoGestureDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         external_intents::kIntentBlockExternalFormRedirectsNoGesture)},
    {"recover-from-never-save-android",
     flag_descriptions::kRecoverFromNeverSaveAndroidName,
     flag_descriptions::kRecoverFromNeverSaveAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         password_manager::features::kRecoverFromNeverSaveAndroid)},
    {"photo-picker-video-support",
     flag_descriptions::kPhotoPickerVideoSupportName,
     flag_descriptions::kPhotoPickerVideoSupportDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         photo_picker::features::kPhotoPickerVideoSupport,
         kPhotoPickerVideoSupportFeatureVariations,
         "PhotoPickerVideoSupportFeatureVariations")},
#endif  // defined(OS_ANDROID)
>>>>>>> chromium

    {"reduce-user-agent", flag_descriptions::kReduceUserAgentName,
     flag_descriptions::kReduceUserAgentDescription, kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(blink::features::kReduceUserAgent)},

<<<<<<< HEAD
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_CHROMEOS)
=======
#if !defined(OS_ANDROID) && !BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-user-data-snapshot", flag_descriptions::kUserDataSnapshotName,
     flag_descriptions::kUserDataSnapshotDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(features::kUserDataSnapshot)},
#endif

#if defined(OS_WIN)
>>>>>>> chromium
    {"run-video-capture-service-in-browser",
     flag_descriptions::kRunVideoCaptureServiceInBrowserProcessName,
     flag_descriptions::kRunVideoCaptureServiceInBrowserProcessDescription,
     kOsWin,
     FEATURE_VALUE_TYPE(features::kRunVideoCaptureServiceInBrowserProcess)},
<<<<<<< HEAD
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_CHROMEOS)
=======
#endif  // defined(OS_WIN)

    {"legacy-tls-enforced", flag_descriptions::kLegacyTLSEnforcedName,
     flag_descriptions::kLegacyTLSEnforcedDescription, kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(net::features::kLegacyTLSEnforced)},

>>>>>>> chromium
    {"double-buffer-compositing",
     flag_descriptions::kDoubleBufferCompositingName,
     flag_descriptions::kDoubleBufferCompositingDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(switches::kDoubleBufferCompositing)},

#if defined(OS_ANDROID)
    {"password-change-in-settings",
     flag_descriptions::kPasswordChangeInSettingsName,
     flag_descriptions::kPasswordChangeInSettingsDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         password_manager::features::kPasswordChangeInSettings,
         kPasswordChangeInSettingsFeatureVariations,
         "PasswordChangeAndroid")},
    {"password-scripts-fetching",
     flag_descriptions::kPasswordScriptsFetchingName,
     flag_descriptions::kPasswordScriptsFetchingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(password_manager::features::kPasswordScriptsFetching)},
    {"password-change-support", flag_descriptions::kPasswordChangeName,
     flag_descriptions::kPasswordChangeDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(password_manager::features::kPasswordChange,
                                    kPasswordChangeFeatureVariations,
                                    "PasswordChangeFeatureVariations")},

    {"context-menu-performance-info-and-remote-hints-fetching",
     flag_descriptions::kContextMenuPerformanceInfoAndRemoteHintFetchingName,
     flag_descriptions::
         kContextMenuPerformanceInfoAndRemoteHintFetchingDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(optimization_guide::features::
                            kContextMenuPerformanceInfoAndRemoteHintFetching)},
#endif  // !defined(OS_ANDROID)

#if defined(OS_ANDROID)
    {"page-info-discoverability",
     flag_descriptions::kPageInfoDiscoverabilityName,
     flag_descriptions::kPageInfoDiscoverabilityDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(page_info::kPageInfoDiscoverability)},
    {"page-info-history", flag_descriptions::kPageInfoHistoryName,
     flag_descriptions::kPageInfoHistoryDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(page_info::kPageInfoHistory)},
#endif  // !defined(OS_ANDROID)

#if !defined(OS_ANDROID)
    {"page-info-version-2-desktop", flag_descriptions::kPageInfoV2DesktopName,
     flag_descriptions::kPageInfoV2DesktopDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(page_info::kPageInfoV2Desktop)},
#endif  // !defined(OS_ANDROID)

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {kClipboardHistoryLongpressInternalName,
     flag_descriptions::kClipboardHistoryLongpressName,
     flag_descriptions::kClipboardHistoryLongpressDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kClipboardHistoryLongpress)},
    {kClipboardHistoryUrlTitlesInternalName,
     flag_descriptions::kClipboardHistoryUrlTitlesName,
     flag_descriptions::kClipboardHistoryUrlTitlesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kClipboardHistoryUrlTitles)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enhanced_clipboard", flag_descriptions::kEnhancedClipboardName,
     flag_descriptions::kEnhancedClipboardDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kClipboardHistory)},
    {"enhanced_clipboard_nudge_session_reset",
     flag_descriptions::kEnhancedClipboardNudgeSessionResetName,
     flag_descriptions::kEnhancedClipboardNudgeSessionResetDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(
         chromeos::features::kClipboardHistoryNudgeSessionReset)},
    {"enhanced_clipboard_screenshot_nudge",
     flag_descriptions::kEnhancedClipboardScreenshotNudgeName,
     flag_descriptions::kEnhancedClipboardScreenshotNudgeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kClipboardHistoryScreenshotNudge)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

#if defined(OS_WIN)
    {"enable-media-foundation-video-capture",
     flag_descriptions::kEnableMediaFoundationVideoCaptureName,
     flag_descriptions::kEnableMediaFoundationVideoCaptureDescription, kOsWin,
     FEATURE_VALUE_TYPE(media::kMediaFoundationVideoCapture)},
#endif  // defined(OS_WIN)

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"reset-shortcut-customizations",
     flag_descriptions::kResetShortcutCustomizationsName,
     flag_descriptions::kResetShortcutCustomizationsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kResetShortcutCustomizations)},
    {"shimless-rma-apro-update-rootfs",
     flag_descriptions::kShimlessRMAAproUpdateRootfsName,
     flag_descriptions::kShimlessRMAAproUpdateRootfsDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootShimlessRMAAproUpdateRootfs")},
    {"shimless-rma-os-update", flag_descriptions::kShimlessRMAOsUpdateName,
     flag_descriptions::kShimlessRMAOsUpdateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kShimlessRMAOsUpdate)},
    {"quick-share-v2", flag_descriptions::kQuickShareV2Name,
     flag_descriptions::kQuickShareV2Description, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kQuickShareV2)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"scan-app-media-link", flag_descriptions::kScanAppMediaLinkName,
     flag_descriptions::kScanAppMediaLinkDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kScanAppMediaLink)},
    {"scan-app-multi-page-scan", flag_descriptions::kScanAppMultiPageScanName,
     flag_descriptions::kScanAppMultiPageScanDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kScanAppMultiPageScan)},
    {"scan-app-searchable-pdf", flag_descriptions::kScanAppSearchablePdfName,
     flag_descriptions::kScanAppSearchablePdfDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kScanAppSearchablePdf)},
    {"scan-app-sticky-settings", flag_descriptions::kScanAppStickySettingsName,
     flag_descriptions::kScanAppStickySettingsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kScanAppStickySettings)},
    {"avatar-toolbar-button", flag_descriptions::kAvatarToolbarButtonName,
     flag_descriptions::kAvatarToolbarButtonDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAvatarToolbarButton)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"color-provider-redirection",
     flag_descriptions::kColorProviderRedirectionName,
     flag_descriptions::kColorProviderRedirectionDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kColorProviderRedirection)},

    {"trust-tokens", flag_descriptions::kTrustTokensName,
     flag_descriptions::kTrustTokensDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(network::features::kTrustTokens,
                                    kPlatformProvidedTrustTokensVariations,
                                    "TrustTokenOriginTrial")},

#if defined(OS_ANDROID)
    {"android-partner-customization-phenotype",
     flag_descriptions::kAndroidPartnerCustomizationPhenotypeName,
     flag_descriptions::kAndroidPartnerCustomizationPhenotypeDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kAndroidPartnerCustomizationPhenotype)},
#endif  // defined(OS_ANDROID)

    {"media-history", flag_descriptions::kMediaHistoryName,
     flag_descriptions::kMediaHistoryDescription, kOsAll,
     FEATURE_VALUE_TYPE(media::kUseMediaHistoryStore)},

#if !defined(OS_ANDROID)
    {"copy-link-to-text", flag_descriptions::kCopyLinkToTextName,
     flag_descriptions::kCopyLinkToTextDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kCopyLinkToText)},
#endif  // !defined(OS_ANDROID)

    {"shared-highlighting-use-blocklist",
     flag_descriptions::kSharedHighlightingUseBlocklistName,
     flag_descriptions::kSharedHighlightingUseBlocklistDescription, kOsAll,
     FEATURE_VALUE_TYPE(shared_highlighting::kSharedHighlightingUseBlocklist)},
    {"shared-highlighting-v2", flag_descriptions::kSharedHighlightingV2Name,
     flag_descriptions::kSharedHighlightingV2Description, kOsAll,
     FEATURE_VALUE_TYPE(shared_highlighting::kSharedHighlightingV2)},
    {"shared-highlighting-amp", flag_descriptions::kSharedHighlightingAmpName,
     flag_descriptions::kSharedHighlightingAmpDescription, kOsAll,
     FEATURE_VALUE_TYPE(shared_highlighting::kSharedHighlightingAmp)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"shimless-rma-flow", flag_descriptions::kShimlessRMAFlowName,
     flag_descriptions::kShimlessRMAFlowDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kShimlessRMAFlow)},
    {"nearby-keep-alive-fix", flag_descriptions::kNearbyKeepAliveFixName,
     flag_descriptions::kNearbyKeepAliveFixDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kNearbyKeepAliveFix)},
    {"nearby-sharing", flag_descriptions::kNearbySharingName,
     flag_descriptions::kNearbySharingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNearbySharing)},
    {"nearby-sharing-background-scanning",
     flag_descriptions::kNearbySharingBackgroundScanningName,
     flag_descriptions::kNearbySharingBackgroundScanningDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNearbySharingBackgroundScanning)},
    {"nearby-sharing-device-contacts",
     flag_descriptions::kNearbySharingDeviceContactsName,
     flag_descriptions::kNearbySharingDeviceContactsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNearbySharingDeviceContacts)},
    {"nearby-sharing-webrtc", flag_descriptions::kNearbySharingWebRtcName,
     flag_descriptions::kNearbySharingWebRtcDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kNearbySharingWebRtc)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"app-cache", flag_descriptions::kAppCacheName,
     flag_descriptions::kAppCacheDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kAppCache)},

    {"align-font-display-auto-lcp",
     flag_descriptions::kAlignFontDisplayAutoTimeoutWithLCPGoalName,
     flag_descriptions::kAlignFontDisplayAutoTimeoutWithLCPGoalDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         blink::features::kAlignFontDisplayAutoTimeoutWithLCPGoal,
         kAlignFontDisplayAutoTimeoutWithLCPGoalVariations,
         "AlignFontDisplayAutoTimeoutWithLCPGoal")},

#if BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium
    {"enable-palm-suppression", flag_descriptions::kEnablePalmSuppressionName,
     flag_descriptions::kEnablePalmSuppressionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnablePalmSuppression)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"enable-experimental-cookie-features",
     flag_descriptions::kEnableExperimentalCookieFeaturesName,
     flag_descriptions::kEnableExperimentalCookieFeaturesDescription, kOsAll,
     MULTI_VALUE_TYPE(kEnableExperimentalCookieFeaturesChoices)},

    {"autofill-enable-google-issued-card",
     flag_descriptions::kAutofillEnableGoogleIssuedCardName,
     flag_descriptions::kAutofillEnableGoogleIssuedCardDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableGoogleIssuedCard)},

    {"permission-chip", flag_descriptions::kPermissionChipName,
     flag_descriptions::kPermissionChipDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(permissions::features::kPermissionChip)},
    {"permission-chip-gesture",
     flag_descriptions::kPermissionChipGestureSensitiveName,
     flag_descriptions::kPermissionChipGestureSensitiveDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(
         permissions::features::kPermissionChipGestureSensitive)},
    {"permission-chip-request-type",
     flag_descriptions::kPermissionChipRequestTypeSensitiveName,
     flag_descriptions::kPermissionChipRequestTypeSensitiveDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         permissions::features::kPermissionChipRequestTypeSensitive)},
    {"permission-quiet-chip", flag_descriptions::kPermissionQuietChipName,
     flag_descriptions::kPermissionQuietChipDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(permissions::features::kPermissionQuietChip)},

    {"canvas-2d-layers", flag_descriptions::kCanvas2DLayersName,
     flag_descriptions::kCanvas2DLayersDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableCanvas2DLayers)},

    {"new-canvas-2d-api", flag_descriptions::kNewCanvas2DAPIName,
     flag_descriptions::kNewCanvas2DAPIDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kEnableNewCanvas2DAPI)},

    {"enable-translate-sub-frames",
     flag_descriptions::kEnableTranslateSubFramesName,
     flag_descriptions::kEnableTranslateSubFramesDescription, kOsAll,
     FEATURE_VALUE_TYPE(translate::kTranslateSubFrames)},

    {"service-worker-subresource-filter",
     flag_descriptions::kServiceWorkerSubresourceFilterName,
     flag_descriptions::kServiceWorkerSubresourceFilterDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kServiceWorkerSubresourceFilter)},

    {"conversion-measurement-api",
     flag_descriptions::kConversionMeasurementApiName,
     flag_descriptions::kConversionMeasurementApiDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kConversionMeasurement)},
    {"conversion-measurement-debug-mode",
     flag_descriptions::kConversionMeasurementDebugModeName,
     flag_descriptions::kConversionMeasurementDebugModeDescription, kOsAll,
     SINGLE_VALUE_TYPE(switches::kConversionsDebugMode)},

    {"client-storage-access-context-auditing",
     flag_descriptions::kClientStorageAccessContextAuditingName,
     flag_descriptions::kClientStorageAccessContextAuditingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kClientStorageAccessContextAuditing)},

#if defined(OS_WIN)
    {"safety-check-chrome-cleaner-child",
     flag_descriptions::kSafetyCheckChromeCleanerChildName,
     flag_descriptions::kSafetyCheckChromeCleanerChildDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kSafetyCheckChromeCleanerChild)},
#endif  // !defined(OS_WIN)

#if defined(OS_WIN)
    {"chrome-cleanup-scan-completed-notification",
     flag_descriptions::kChromeCleanupScanCompletedNotificationName,
     flag_descriptions::kChromeCleanupScanCompletedNotificationDescription,
     kOsWin,
     FEATURE_VALUE_TYPE(features::kChromeCleanupScanCompletedNotification)},
#endif  // !defined(OS_WIN)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"productivity-launcher", flag_descriptions::kAppListBubbleName,
     flag_descriptions::kAppListBubbleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kAppListBubble)},
    {"enable-launcher-app-paging",
     flag_descriptions::kNewDragSpecInLauncherName,
     flag_descriptions::kNewDragSpecInLauncherDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kNewDragSpecInLauncher)},
    {"cdm-factory-daemon", flag_descriptions::kCdmFactoryDaemonName,
     flag_descriptions::kCdmFactoryDaemonDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCdmFactoryDaemon)},
    {"shelf-drag-to-pin", flag_descriptions::kShelfDragToPinName,
     flag_descriptions::kShelfDragToPinDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDragUnpinnedAppToPin)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"categorical-search", flag_descriptions::kCategoricalSearchName,
     flag_descriptions::kCategoricalSearchName, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(app_list_features::kCategoricalSearch,
                                    kCategoricalSearchVariations,
                                    "LauncherCategoricalSearch")},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"autofill-enable-offers-in-downstream",
     flag_descriptions::kAutofillEnableOffersInDownstreamName,
     flag_descriptions::kAutofillEnableOffersInDownstreamDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableOffersInDownstream)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-sharesheet", flag_descriptions::kSharesheetName,
     flag_descriptions::kSharesheetDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kSharesheet)},

    {"enable-sharesheet-content-previews",
     flag_descriptions::kSharesheetContentPreviewsName,
     flag_descriptions::kSharesheetContentPreviewsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kSharesheetContentPreviews)},

    {"chromeos-sharing-hub", flag_descriptions::kChromeOSSharingHubName,
     flag_descriptions::kChromeOSSharingHubDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kChromeOSSharingHub)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"schemeful-same-site", flag_descriptions::kSchemefulSameSiteName,
     flag_descriptions::kSchemefulSameSiteDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kSchemefulSameSite)},

    {"enable-bluetooth-spp-in-serial-api",
     flag_descriptions::kEnableBluetoothSerialPortProfileInSerialApiName,
     flag_descriptions::kEnableBluetoothSerialPortProfileInSerialApiDescription,
     kOsMac,
     SINGLE_VALUE_TYPE(switches::kEnableBluetoothSerialPortProfileInSerialApi)},

    {"enable-lite-video", flag_descriptions::kLiteVideoName,
     flag_descriptions::kLiteVideoDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kLiteVideo)},

    {"lite-video-default-downlink-bandwidth-kbps",
     flag_descriptions::kLiteVideoDownlinkBandwidthKbpsName,
     flag_descriptions::kLiteVideoDownlinkBandwidthKbpsDescription, kOsAll,
     MULTI_VALUE_TYPE(kLiteVideoDefaultDownlinkBandwidthKbps)},

    {"lite-video-force-override-decision",
     flag_descriptions::kLiteVideoForceOverrideDecisionName,
     flag_descriptions::kLiteVideoForceOverrideDecisionDescription, kOsAll,
     SINGLE_VALUE_TYPE(lite_video::switches::kLiteVideoForceOverrideDecision)},

    {"edit-passwords-in-settings",
     flag_descriptions::kEditPasswordsInSettingsName,
     flag_descriptions::kEditPasswordsInSettingsDescription, kOsAll,
     FEATURE_VALUE_TYPE(password_manager::features::kEditPasswordsInSettings)},

    {"mixed-forms-disable-autofill",
     flag_descriptions::kMixedFormsDisableAutofillName,
     flag_descriptions::kMixedFormsDisableAutofillDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillPreventMixedFormsFilling)},

    {"mixed-forms-interstitial", flag_descriptions::kMixedFormsInterstitialName,
     flag_descriptions::kMixedFormsInterstitialDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         security_interstitials::kInsecureFormSubmissionInterstitial)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"frame-throttle-fps", flag_descriptions::kFrameThrottleFpsName,
     flag_descriptions::kFrameThrottleFpsDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kFrameThrottleFpsChoices)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
    {"filling-passwords-from-any-origin",
     flag_descriptions::kFillingPasswordsFromAnyOriginName,
     flag_descriptions::kFillingPasswordsFromAnyOriginDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         password_manager::features::kFillingPasswordsFromAnyOrigin)},
#endif  // OS_ANDROID

#if defined(OS_WIN)
    {"enable-incognito-shortcut-on-desktop",
     flag_descriptions::kEnableIncognitoShortcutOnDesktopName,
     flag_descriptions::kEnableIncognitoShortcutOnDesktopDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kEnableIncognitoShortcutOnDesktop)},
#endif  // defined(OS_WIN)

<<<<<<< HEAD
    {"permission-element",
     flag_descriptions::kPageEmbeddedPermissionControlName,
     flag_descriptions::kPageEmbeddedPermissionControlDescription,
     kOsMac | kOsWin | kOsCrOS | kOsAndroid | kOsLinux,
     FEATURE_VALUE_TYPE(blink::features::kPermissionElement)},

    {"left-hand-side-activity-indicators",
     flag_descriptions::kLeftHandSideActivityIndicatorsName,
     flag_descriptions::kLeftHandSideActivityIndicatorsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(
         content_settings::features::kLeftHandSideActivityIndicators)},

#if !BUILDFLAG(IS_ANDROID)
    {"merchant-trust", flag_descriptions::kMerchantTrustName,
     flag_descriptions::kMerchantTrustDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(page_info::kMerchantTrust,
                                    kMerchantTrustVariations,
                                    "MerchantTrust")},
#endif  // !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {"privacy-policy-insights", flag_descriptions::kPrivacyPolicyInsightsName,
     flag_descriptions::kPrivacyPolicyInsightsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(page_info::kPrivacyPolicyInsights)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-block-warnings",
     flag_descriptions::kCrosSystemLevelPermissionBlockedWarningsName,
     flag_descriptions::kCrosSystemLevelPermissionBlockedWarningsDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(content_settings::features::
                            kCrosSystemLevelPermissionBlockedWarnings)},
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"launcher-continue-section-with-recents",
     flag_descriptions::kLauncherContinueSectionWithRecentsName,
     flag_descriptions::kLauncherContinueSectionWithRecentsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kLauncherContinueSectionWithRecents)},
    {"launcher-item-suggest", flag_descriptions::kLauncherItemSuggestName,
     flag_descriptions::kLauncherItemSuggestDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::kLauncherItemSuggest,
                                    kLauncherItemSuggestVariations,
                                    "LauncherItemSuggest")},
    {"eol-incentive", flag_descriptions::kEolIncentiveName,
     flag_descriptions::kEolIncentiveDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kEolIncentive,
                                    kEolIncentiveVariations,
                                    "EolIncentive")},
    {"productivity-launcher-image-search",
     flag_descriptions::kProductivityLauncherImageSearchName,
     flag_descriptions::kProductivityLauncherImageSearchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kProductivityLauncherImageSearch)},
    {kSeaPenInternalName, flag_descriptions::kSeaPenName,
     flag_descriptions::kSeaPenDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSeaPen)},
    {"shelf-auto-hide-separation",
     flag_descriptions::kShelfAutoHideSeparationName,
     flag_descriptions::kShelfAutoHideSeparationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kShelfAutoHideSeparation)},
    {"launcher-keyword-extraction-scoring",
     flag_descriptions::kLauncherKeywordExtractionScoring,
     flag_descriptions::kLauncherKeywordExtractionScoringDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(search_features::kLauncherKeywordExtractionScoring)},
    {"launcher-search-control", flag_descriptions::kLauncherSearchControlName,
     flag_descriptions::kLauncherSearchControlDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kLauncherSearchControl)},
    {"launcher-nudge-session-reset",
     flag_descriptions::kLauncherNudgeSessionResetName,
     flag_descriptions::kLauncherNudgeSessionResetDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kLauncherNudgeSessionReset)},
    {"launcher-system-info-answer-cards",
     flag_descriptions::kLauncherSystemInfoAnswerCardsName,
     flag_descriptions::kLauncherSystemInfoAnswerCardsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(search_features::kLauncherSystemInfoAnswerCards)},
    {"text-in-shelf", flag_descriptions::kTextInShelfName,
     flag_descriptions::kTextInShelfDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHomeButtonWithText)},
    {"launcher-local-image-search",
     flag_descriptions::kLauncherLocalImageSearchName,
     flag_descriptions::kLauncherLocalImageSearchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(search_features::kLauncherImageSearch)},
    {"launcher-local-image-search-confidence",
     flag_descriptions::kLauncherLocalImageSearchConfidenceName,
     flag_descriptions::kLauncherLocalImageSearchConfidenceDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         search_features::kLauncherLocalImageSearchConfidence,
         kLauncherLocalImageSearchConfidenceVariations,
         "LauncherLocalImageSearchConfidence")},
    {"launcher-local-image-search-relevance",
     flag_descriptions::kLauncherLocalImageSearchRelevanceName,
     flag_descriptions::kLauncherLocalImageSearchRelevanceDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         search_features::kLauncherLocalImageSearchRelevance,
         kLauncherLocalImageSearchRelevanceVariations,
         "LauncherLocalImageSearchRelevance")},
    {"launcher-local-image-search-ocr",
     flag_descriptions::kLauncherLocalImageSearchOcrName,
     flag_descriptions::kLauncherLocalImageSearchOcrDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(search_features::kLauncherImageSearchOcr)},
    {"launcher-local-image-search-ica",
     flag_descriptions::kLauncherLocalImageSearchIcaName,
     flag_descriptions::kLauncherLocalImageSearchIcaDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(search_features::kLauncherImageSearchIca)},
    {"launcher-key-shortcut-in-best-match",
     flag_descriptions::kLauncherKeyShortcutInBestMatchName,
     flag_descriptions::kLauncherKeyShortcutInBestMatchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(search_features::kLauncherKeyShortcutInBestMatch)},
    {"quick-app-access-test-ui", flag_descriptions::kQuickAppAccessTestUIName,
     flag_descriptions::kQuickAppAccessTestUIDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kQuickAppAccessTestUI)},

    {"mac-address-randomization",
     flag_descriptions::kMacAddressRandomizationName,
     flag_descriptions::kMacAddressRandomizationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kMacAddressRandomization)},
=======
#if defined(OS_ANDROID)
    {"incognito-brand-consistency-for-android",
     flag_descriptions::kIncognitoBrandConsistencyForAndroidName,
     flag_descriptions::kIncognitoBrandConsistencyForAndroidDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(features::kIncognitoBrandConsistencyForAndroid)},
#endif

#if defined(OS_MAC) || defined(OS_WIN) || defined(OS_LINUX) || \
    defined(OS_CHROMEOS)
    {"incognito-brand-consistency-for-desktop",
     flag_descriptions::kIncognitoBrandConsistencyForDesktopName,
     flag_descriptions::kIncognitoBrandConsistencyForDesktopDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kIncognitoBrandConsistencyForDesktop)},

    {"incognito-clear-browsing-data-dialog-for-desktop",
     flag_descriptions::kIncognitoClearBrowsingDataDialogForDesktopName,
     flag_descriptions::kIncognitoClearBrowsingDataDialogForDesktopDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kIncognitoClearBrowsingDataDialogForDesktop)},

    {"inherit-native-theme-from-parent-widget",
     flag_descriptions::kInheritNativeThemeFromParentWidgetName,
     flag_descriptions::kInheritNativeThemeFromParentWidgetDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(views::features::kInheritNativeThemeFromParentWidget)},
#endif
>>>>>>> chromium

    {"content-settings-redesign",
     flag_descriptions::kContentSettingsRedesignName,
     flag_descriptions::kContentSettingsRedesignDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kContentSettingsRedesign)},

<<<<<<< HEAD
    {"dynamic-search-update-animation",
     flag_descriptions::kDynamicSearchUpdateAnimationName,
     flag_descriptions::kDynamicSearchUpdateAnimationDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         app_list_features::kDynamicSearchUpdateAnimation,
         kDynamicSearchUpdateAnimationVariations,
         "LauncherDynamicAnimations")},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if defined(OS_ANDROID)
    {"cpu-affinity-restrict-to-little-cores",
     flag_descriptions::kCpuAffinityRestrictToLittleCoresName,
     flag_descriptions::kCpuAffinityRestrictToLittleCoresDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         power_scheduler::features::kCpuAffinityRestrictToLittleCores)},
>>>>>>> chromium

    {"enable-surface-control", flag_descriptions::kAndroidSurfaceControlName,
     flag_descriptions::kAndroidSurfaceControlDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAndroidSurfaceControl)},

    {"enable-image-reader", flag_descriptions::kAImageReaderName,
     flag_descriptions::kAImageReaderDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAImageReader)},
#endif  // OS_ANDROID

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-auto-select", flag_descriptions::kEnableAutoSelectName,
     flag_descriptions::kEnableAutoSelectDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(blink::features::kCrOSAutoSelect)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
    {"smart-suggestion-for-large-downloads",
     flag_descriptions::kSmartSuggestionForLargeDownloadsName,
     flag_descriptions::kSmartSuggestionForLargeDownloadsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(download::features::kSmartSuggestionForLargeDownloads)},
<<<<<<< HEAD
=======
#endif  // defined(OS_ANDROID)

#if BUILDFLAG(ENABLE_JXL_DECODER)
    {"enable-jxl", flag_descriptions::kEnableJXLName,
     flag_descriptions::kEnableJXLDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kJXL)},
#endif  // BUILDFLAG(ENABLE_JXL_DECODER)
>>>>>>> chromium

    {"window-naming", flag_descriptions::kWindowNamingName,
     flag_descriptions::kWindowNamingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWindowNaming)},

<<<<<<< HEAD
    {"pwa-update-dialog-for-icon",
     flag_descriptions::kPwaUpdateDialogForAppIconName,
     flag_descriptions::kPwaUpdateDialogForAppIconDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kPwaUpdateDialogForIcon)},

#if !BUILDFLAG(IS_ANDROID)
    {"keyboard-lock-prompt", flag_descriptions::kKeyboardLockPromptName,
     flag_descriptions::kKeyboardLockPromptDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(permissions::features::kKeyboardLockPrompt)},

    {"press-and-hold-esc-to-exit-browser-fullscreen",
     flag_descriptions::kPressAndHoldEscToExitBrowserFullscreenName,
     flag_descriptions::kPressAndHoldEscToExitBrowserFullscreenDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kPressAndHoldEscToExitBrowserFullscreen)},
#endif

#if BUILDFLAG(ENABLE_OOP_PRINTING)
=======
#if defined(OS_ANDROID)
    {"messages-for-android-infrastructure",
     flag_descriptions::kMessagesForAndroidInfrastructureName,
     flag_descriptions::kMessagesForAndroidInfrastructureDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(messages::kMessagesForAndroidInfrastructure)},
    {"messages-for-android-passwords",
     flag_descriptions::kMessagesForAndroidPasswordsName,
     flag_descriptions::kMessagesForAndroidPasswordsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(messages::kMessagesForAndroidPasswords)},
    {"messages-for-android-popup-blocked",
     flag_descriptions::kMessagesForAndroidPopupBlockedName,
     flag_descriptions::kMessagesForAndroidPopupBlockedDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(messages::kMessagesForAndroidPopupBlocked)},
    {"messages-for-android-reader-mode",
     flag_descriptions::kMessagesForAndroidReaderModeName,
     flag_descriptions::kMessagesForAndroidReaderModeDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(messages::kMessagesForAndroidReaderMode)},
    {"messages-for-android-safety-tip",
     flag_descriptions::kMessagesForAndroidSafetyTipName,
     flag_descriptions::kMessagesForAndroidSafetyTipDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(messages::kMessagesForAndroidSafetyTip)},
    {"messages-for-android-save-card",
     flag_descriptions::kMessagesForAndroidSaveCardName,
     flag_descriptions::kMessagesForAndroidSaveCardDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(messages::kMessagesForAndroidSaveCard)},
    {"messages-for-android-update-password",
     flag_descriptions::kMessagesForAndroidUpdatePasswordName,
     flag_descriptions::kMessagesForAndroidUpdatePasswordDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(messages::kMessagesForAndroidUpdatePassword)},
#endif

#if defined(OS_ANDROID)
    {"android-detailed-language-settings",
     flag_descriptions::kAndroidDetailedLanguageSettingsName,
     flag_descriptions::kAndroidDetailedLanguageSettingsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(language::kDetailedLanguageSettings)},
    {"android-force-app-language-prompt",
     flag_descriptions::kAndroidForceAppLanguagePromptName,
     flag_descriptions::kAndroidForceAppLanguagePromptDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(language::kForceAppLanguagePrompt)},
#endif

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)
    {"commander", flag_descriptions::kCommanderName,
     flag_descriptions::kCommanderDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kCommander)},

    {"desktop-restructured-language-settings",
     flag_descriptions::kDesktopRestructuredLanguageSettingsName,
     flag_descriptions::kDesktopRestructuredLanguageSettingsDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(language::kDesktopRestructuredLanguageSettings)},

    {"desktop-detailed-language-settings",
     flag_descriptions::kDesktopDetailedLanguageSettingsName,
     flag_descriptions::kDesktopDetailedLanguageSettingsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(language::kDesktopDetailedLanguageSettings)},
#endif

    {"pwa-update-dialog-for-name-and-icon",
     flag_descriptions::kPwaUpdateDialogForNameAndIconName,
     flag_descriptions::kPwaUpdateDialogForNameAndIconDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kPwaUpdateDialogForNameAndIcon)},

    {"sync-autofill-wallet-offer-data",
     flag_descriptions::kSyncAutofillWalletOfferDataName,
     flag_descriptions::kSyncAutofillWalletOfferDataDescription, kOsAll,
     FEATURE_VALUE_TYPE(switches::kSyncAutofillWalletOfferData)},

#if (defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) || \
     defined(OS_CHROMEOS)) &&                                   \
    BUILDFLAG(ENABLE_PRINTING)
>>>>>>> chromium
    {"enable-oop-print-drivers", flag_descriptions::kEnableOopPrintDriversName,
     flag_descriptions::kEnableOopPrintDriversDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(printing::features::kEnableOopPrintDrivers)},
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"omnibox-rich-entities-in-launcher",
     flag_descriptions::kOmniboxRichEntitiesInLauncherName,
     flag_descriptions::kOmniboxRichEntitiesInLauncherDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         app_list_features::kEnableOmniboxRichEntities,
         kOmniboxRichEntitiesInLauncherVariations,
         "OmniboxRichEntitiesInLauncher")},
#endif

#if defined(OS_ANDROID)
    {"decouple-sync-from-android-auto-sync",
     flag_descriptions::kDecoupleSyncFromAndroidAutoSyncName,
     flag_descriptions::kDecoupleSyncFromAndroidAutoSyncDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(switches::kDecoupleSyncFromAndroidMasterSync)},
#endif  // defined(OS_ANDROID)

    {"enable-browsing-data-lifetime-manager",
     flag_descriptions::kEnableBrowsingDataLifetimeManagerName,
     flag_descriptions::kEnableBrowsingDataLifetimeManagerDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         browsing_data::features::kEnableBrowsingDataLifetimeManager)},

#if defined(OS_ANDROID)
    {"wallet-requires-first-sync-setup",
     flag_descriptions::kWalletRequiresFirstSyncSetupCompleteName,
     flag_descriptions::kWalletRequiresFirstSyncSetupCompleteDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kWalletRequiresFirstSyncSetupComplete)},
#endif  // defined(OS_ANDROID)

    {"privacy-advisor", flag_descriptions::kPrivacyAdvisorName,
     flag_descriptions::kPrivacyAdvisorDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kPrivacyAdvisor)},

#if defined(TOOLKIT_VIEWS)
    {"desktop-in-product-help-snooze",
     flag_descriptions::kDesktopInProductHelpSnoozeName,
     flag_descriptions::kDesktopInProductHelpSnoozeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(feature_engagement::kIPHDesktopSnoozeFeature)},
#endif  // defined(TOOLKIT_VIEWS)

<<<<<<< HEAD
    {"align-surface-layer-impl-to-pixel-grid",
     flag_descriptions::kAlignSurfaceLayerImplToPixelGridName,
     flag_descriptions::kAlignSurfaceLayerImplToPixelGridDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kAlignSurfaceLayerImplToPixelGrid)},

#if !BUILDFLAG(IS_ANDROID)
=======
    {"animated-image-resume", flag_descriptions::kAnimatedImageResumeName,
     flag_descriptions::kAnimatedImageResumeDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kAnimatedImageResume)},

#if !defined(OS_ANDROID)
>>>>>>> chromium
    {"sct-auditing", flag_descriptions::kSCTAuditingName,
     flag_descriptions::kSCTAuditingDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kSCTAuditing,
                                    kSCTAuditingVariations,
                                    "SCTAuditingVariations")},
#endif  // !defined(OS_ANDROID)

#if defined(OS_ANDROID)
    {"enable-autofill-password-account-indicator-footer",
     flag_descriptions::
         kEnableAutofillPasswordInfoBarAccountIndicationFooterName,
     flag_descriptions::
         kEnableAutofillPasswordInfoBarAccountIndicationFooterDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::
             kAutofillEnablePasswordInfoBarAccountIndicationFooter)},

    {"incognito-screenshot", flag_descriptions::kIncognitoScreenshotName,
     flag_descriptions::kIncognitoScreenshotDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kIncognitoScreenshot)},
#endif
    {"use-first-party-set", flag_descriptions::kUseFirstPartySetName,
     flag_descriptions::kUseFirstPartySetDescription, kOsAll,
     ORIGIN_LIST_VALUE_TYPE(network::switches::kUseFirstPartySet, "")},

    {"check-offline-capability", flag_descriptions::kCheckOfflineCapabilityName,
     flag_descriptions::kCheckOfflineCapabilityDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kCheckOfflineCapability,
                                    kCheckOfflineCapabilityVariations,
                                    "CheckOfflineCapability")},
#if defined(OS_ANDROID)
    {"enable-autofill-save-card-info-bar-account-indication-footer",
     flag_descriptions::
         kEnableAutofillSaveCardInfoBarAccountIndicationFooterName,
     flag_descriptions::
         kEnableAutofillSaveCardInfoBarAccountIndicationFooterDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::
             kAutofillEnableSaveCardInfoBarAccountIndicationFooter)},
#endif
    {"detect-form-submission-on-form-clear",
     flag_descriptions::kDetectFormSubmissionOnFormClearName,
     flag_descriptions::kDetectFormSubmissionOnFormClearDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         password_manager::features::kDetectFormSubmissionOnFormClear)},

#if defined(OS_ANDROID)
    {"enable-autofill-infobar-account-indication-footer-for-single-account-"
     "users",
     flag_descriptions::
         kEnableAutofillInfoBarAccountIndicationFooterForSingleAccountUsersName,
     flag_descriptions::
         kEnableAutofillInfoBarAccountIndicationFooterForSingleAccountUsersDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::
             kAutofillEnableInfoBarAccountIndicationFooterForSingleAccountUsers)},
    {"enable-autofill-infobar-account-indication-footer-for-sync-users",
     flag_descriptions::
         kEnableAutofillInfoBarAccountIndicationFooterForSyncUsersName,
     flag_descriptions::
         kEnableAutofillInfoBarAccountIndicationFooterForSyncUsersDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::
             kAutofillEnableInfoBarAccountIndicationFooterForSyncUsers)},
#endif

    {"permission-predictions", flag_descriptions::kPermissionPredictionsName,
     flag_descriptions::kPermissionPredictionsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kPermissionPredictions)},

    {"show-performance-metrics-hud",
     flag_descriptions::kShowPerformanceMetricsHudName,
     flag_descriptions::kShowPerformanceMetricsHudDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kHudDisplayForPerformanceMetrics)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"disable-buffer-bw-compression",
     flag_descriptions::kDisableBufferBWCompressionName,
     flag_descriptions::kDisableBufferBWCompressionDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(switches::kDisableBufferBWCompression)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"enable-prerender2", flag_descriptions::kPrerender2Name,
     flag_descriptions::kPrerender2Description, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kPrerender2)},

#if defined(OS_ANDROID)
    {"enable-swipe-to-move-cursor", flag_descriptions::kSwipeToMoveCursorName,
     flag_descriptions::kSwipeToMoveCursorDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kSwipeToMoveCursor)},
#endif  // defined(OS_ANDROID)

    {"safety-check-weak-passwords",
     flag_descriptions::kSafetyCheckWeakPasswordsName,
     flag_descriptions::kSafetyCheckWeakPasswordsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSafetyCheckWeakPasswords)},

#if !defined(OS_ANDROID)
    {"settings-landing-page-redesign",
     flag_descriptions::kSettingsLandingPageRedesignName,
     flag_descriptions::kSettingsLandingPageRedesignDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSettingsLandingPageRedesign)},

    {"webui-branding-update", flag_descriptions::kWebUIBrandingUpdateName,
     flag_descriptions::kWebUIBrandingUpdateDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebUIBrandingUpdate)},
#endif  // !defined(OS_ANDROID)

#if defined(OS_ANDROID)
    {"continuous-search", flag_descriptions::kContinuousSearchName,
     flag_descriptions::kContinuousSearchDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kContinuousSearch,
                                    kContinuousSearchFeatureVariations,
                                    "ContinuousSearchVariations")},

    {"enable-experimental-accessibility-labels",
     flag_descriptions::kExperimentalAccessibilityLabelsName,
     flag_descriptions::kExperimentalAccessibilityLabelsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kExperimentalAccessibilityLabels)},
#endif  // defined(OS_ANDROID)

    {"chrome-labs", flag_descriptions::kChromeLabsName,
     flag_descriptions::kChromeLabsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kChromeLabs)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"launcher-search-normalization",
     flag_descriptions::kEnableLauncherSearchNormalizationName,
     flag_descriptions::kEnableLauncherSearchNormalizationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kEnableLauncherSearchNormalization)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"enable-first-party-sets", flag_descriptions::kEnableFirstPartySetsName,
     flag_descriptions::kEnableFirstPartySetsDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kFirstPartySets)},

#if defined(OS_ANDROID)
    {"autofill-enable-offers-in-clank-keyboard-accessory",
     flag_descriptions::kAutofillEnableOffersInClankKeyboardAccessoryName,
     flag_descriptions::
         kAutofillEnableOffersInClankKeyboardAccessoryDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableOffersInClankKeyboardAccessory)},
#endif

#if BUILDFLAG(ENABLE_PDF)
    {"pdf-unseasoned", flag_descriptions::kPdfUnseasonedName,
     flag_descriptions::kPdfUnseasonedDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(chrome_pdf::features::kPdfUnseasoned)},
    {"pdf-xfa-forms", flag_descriptions::kPdfXfaFormsName,
     flag_descriptions::kPdfXfaFormsDescription, kOsAll,
     FEATURE_VALUE_TYPE(chrome_pdf::features::kPdfXfaSupport)},
#endif  // BUILDFLAG(ENABLE_PDF)

#if defined(OS_ANDROID)
    {"actionable-content-settings",
     flag_descriptions::kActionableContentSettingsName,
     flag_descriptions::kActionableContentSettingsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(browser_ui::kActionableContentSettings)},
#endif

    {"send-tab-to-self-when-signed-in",
     flag_descriptions::kSendTabToSelfWhenSignedInName,
     flag_descriptions::kSendTabToSelfWhenSignedInDescription, kOsAll,
     FEATURE_VALUE_TYPE(send_tab_to_self::kSendTabToSelfWhenSignedIn)},

    {"send-tab-to-self-v2", flag_descriptions::kSendTabToSelfV2Name,
     flag_descriptions::kSendTabToSelfV2Description, kOsAll,
     FEATURE_VALUE_TYPE(send_tab_to_self::kSendTabToSelfV2)},

#if defined(OS_ANDROID)
    {"mobile-pwa-install-use-bottom-sheet",
     flag_descriptions::kMobilePwaInstallUseBottomSheetName,
     flag_descriptions::kMobilePwaInstallUseBottomSheetDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(webapps::features::kPwaInstallUseBottomSheet)},
#endif

    {"text-fragment-color-change",
     flag_descriptions::kTextFragmentColorChangeName,
     flag_descriptions::kTextFragmentColorChangeDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kTextFragmentColorChange)},

#if defined(OS_WIN)
    {"raw-audio-capture", flag_descriptions::kRawAudioCaptureName,
     flag_descriptions::kRawAudioCaptureDescription, kOsWin,
     FEATURE_VALUE_TYPE(media::kWasapiRawAudioCapture)},
#endif  // defined(OS_MAC)

    {"enable-managed-configuration-web-api",
     flag_descriptions::kEnableManagedConfigurationWebApiName,
     flag_descriptions::kEnableManagedConfigurationWebApiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(blink::features::kManagedConfiguration)},

    {"enable-restricted-web-apis",
     flag_descriptions::kEnableRestrictedWebApisName,
     flag_descriptions::kEnableRestrictedWebApisDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableRestrictedWebApis)},

    {"clear-cross-site-cross-browsing-context-group-window-name",
     flag_descriptions::kClearCrossSiteCrossBrowsingContextGroupWindowNameName,
     flag_descriptions::
         kClearCrossSiteCrossBrowsingContextGroupWindowNameDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         features::kClearCrossSiteCrossBrowsingContextGroupWindowName)},

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {kWallpaperFastRefreshInternalName,
     flag_descriptions::kWallpaperFastRefreshName,
     flag_descriptions::kWallpaperFastRefreshDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWallpaperFastRefresh)},
    {kWallpaperGooglePhotosSharedAlbumsInternalName,
     flag_descriptions::kWallpaperGooglePhotosSharedAlbumsName,
     flag_descriptions::kWallpaperGooglePhotosSharedAlbumsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWallpaperGooglePhotosSharedAlbums)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_LINUX)
    {"enable-get-all-screens-media", flag_descriptions::kGetAllScreensMediaName,
     flag_descriptions::kGetAllScreensMediaDescription, kOsCrOS | kOsLinux,
     FEATURE_VALUE_TYPE(blink::features::kGetAllScreensMedia)},
#endif  // BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_LINUX)

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-run-on-os-login", flag_descriptions::kRunOnOsLoginName,
     flag_descriptions::kRunOnOsLoginDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsRunOnOsLogin)},
    {"enable-prevent-close", flag_descriptions::kPreventCloseName,
     flag_descriptions::kPreventCloseDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsPreventClose)},

    {"enable-cloud-identifiers",
     flag_descriptions::kFileSystemAccessGetCloudIdentifiersName,
     flag_descriptions::kFileSystemAccessGetCloudIdentifiersDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(blink::features::kFileSystemAccessGetCloudIdentifiers)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"enable-global-vaapi-lock", flag_descriptions::kGlobalVaapiLockName,
     flag_descriptions::kGlobalVaapiLockDescription, kOsCrOS | kOsLinux,
     FEATURE_VALUE_TYPE(media::kGlobalVaapiLock)},

#if BUILDFLAG(IS_WIN) ||                                      \
    (BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)) || \
    BUILDFLAG(IS_MAC)
=======
    {"autofill-enable-offer-notification",
     flag_descriptions::kAutofillEnableOfferNotificationName,
     flag_descriptions::kAutofillEnableOfferNotificationDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableOfferNotification)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {kWallpaperWebUIInternalName, flag_descriptions::kWallpaperWebUIName,
     flag_descriptions::kWallpaperWebUIDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWallpaperWebUI)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_CHROMEOS)
    // TODO(b/180051795): remove kOsLinux when lacros-chrome switches to
    // kOsCrOS.
    {"enable-vaapi-av1-decode-acceleration",
     flag_descriptions::kVaapiAV1DecoderName,
     flag_descriptions::kVaapiAV1DecoderDescription, kOsCrOS | kOsLinux,
     FEATURE_VALUE_TYPE(media::kVaapiAV1Decoder)},
#endif  // defined(OS_CHROMEOS)

#if defined(ARCH_CPU_X86_FAMILY) && BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-vaapi-vp9-kSVC-encode-acceleration",
     flag_descriptions::kVaapiVP9kSVCEncoderName,
     flag_descriptions::kVaapiVP9kSVCEncoderDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kVaapiVp9kSVCHWEncoding)},
#endif  // defined(ARCH_CPU_X86_FAMILY) && BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_WIN) || (defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)) || \
    defined(OS_MAC)
>>>>>>> chromium
    {
        "ui-debug-tools",
        flag_descriptions::kUIDebugToolsName,
        flag_descriptions::kUIDebugToolsDescription,
        kOsWin | kOsLinux | kOsMac,
        FEATURE_VALUE_TYPE(features::kUIDebugTools),
    },
#endif
    {"http-cache-partitioning",
     flag_descriptions::kSplitCacheByNetworkIsolationKeyName,
     flag_descriptions::kSplitCacheByNetworkIsolationKeyDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS | kOsAndroid,
     FEATURE_VALUE_TYPE(net::features::kSplitCacheByNetworkIsolationKey)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-show-date-in-tray", flag_descriptions::kShowDateInTrayName,
     flag_descriptions::kShowDateInTrayDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kShowDateInTrayButton)},
#endif

    {"autofill-address-save-prompt",
     flag_descriptions::kEnableAutofillAddressSavePromptName,
     flag_descriptions::kEnableAutofillAddressSavePromptDescription,
     kOsWin | kOsMac | kOsLinux | kOsCrOS | kOsAndroid,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillAddressProfileSavePrompt)},

    {"detected-source-language-option",
     flag_descriptions::kDetectedSourceLanguageOptionName,
     flag_descriptions::kDetectedSourceLanguageOptionDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(language::kDetectedSourceLanguageOption)},

#if defined(OS_ANDROID)
    {"content-languages-in-language-picker",
     flag_descriptions::kContentLanguagesInLanguagePickerName,
     flag_descriptions::kContentLanguagesInLanguagePickerName, kOsAndroid,
     FEATURE_VALUE_TYPE(language::kContentLanguagesInLanguagePicker)},
#endif

    {"filling-across-affiliated-websites",
     flag_descriptions::kFillingAcrossAffiliatedWebsitesName,
     flag_descriptions::kFillingAcrossAffiliatedWebsitesDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         password_manager::features::kFillingAcrossAffiliatedWebsites)},

    {"draw-predicted-ink-point", flag_descriptions::kDrawPredictedPointsName,
     flag_descriptions::kDrawPredictedPointsDescription, kOsAll,
     MULTI_VALUE_TYPE(kDrawPredictedPointsChoices)},

    {"enable-tflite-language-detection",
     flag_descriptions::kTFLiteLanguageDetectionName,
     flag_descriptions::kTFLiteLanguageDetectionDescription, kOsAll,
     FEATURE_VALUE_TYPE(translate::kTFLiteLanguageDetectionEnabled)},

    {"optimization-guide-model-downloading",
     flag_descriptions::kOptimizationGuideModelDownloadingName,
     flag_descriptions::kOptimizationGuideModelDownloadingDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         optimization_guide::features::kOptimizationGuideModelDownloading)},

#if defined(OS_ANDROID)
    {"optimization-guide-push-notifications",
     flag_descriptions::kOptimizationGuideModelPushNotificationName,
     flag_descriptions::kOptimizationGuideModelPushNotificationDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(optimization_guide::features::kPushNotifications)},
#endif

    {"media-session-webrtc", flag_descriptions::kMediaSessionWebRTCName,
     flag_descriptions::kMediaSessionWebRTCDescription, kOsAll,
     FEATURE_VALUE_TYPE(media::kMediaSessionWebRTC)},

    {"webid", flag_descriptions::kWebIdName,
     flag_descriptions::kWebIdDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kWebID)},

<<<<<<< HEAD
    {"fedcm-delegation", flag_descriptions::kFedCmDelegationName,
     flag_descriptions::kFedCmDelegationDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kFedCmDelegation)},

    {"fedcm-idp-registration", flag_descriptions::kFedCmIdPRegistrationName,
     flag_descriptions::kFedCmIdPRegistrationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kFedCmIdPRegistration)},

    {"fedcm-lightweight-mode", flag_descriptions::kFedCmLightweightModeName,
     flag_descriptions::kFedCmLightweightModeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kFedCmLightweightMode)},

    {"fedcm-metrics-endpoint", flag_descriptions::kFedCmMetricsEndpointName,
     flag_descriptions::kFedCmMetricsEndpointDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kFedCmMetricsEndpoint)},

    {"fedcm-multi-idp", flag_descriptions::kFedCmMultiIdpName,
     flag_descriptions::kFedCmMultiIdpDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kFedCmMultipleIdentityProviders)},
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"bluetooth-sessionized-metrics",
     flag_descriptions::kBluetoothSessionizedMetricsName,
     flag_descriptions::kBluetoothSessionizedMetricsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(metrics::structured::kBluetoothSessionizedMetrics)},
#endif

#if defined(OS_LINUX) && defined(USE_OZONE)
    {"use-ozone-platform", flag_descriptions::kUseOzonePlatformName,
     flag_descriptions::kUseOzonePlatformDescription, kOsLinux,
     FEATURE_VALUE_TYPE(features::kUseOzonePlatform)},
#endif

    {"subframe-shutdown-delay", flag_descriptions::kSubframeShutdownDelayName,
     flag_descriptions::kSubframeShutdownDelayDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSubframeShutdownDelay)},
>>>>>>> chromium

    {"composite-after-paint", flag_descriptions::kCompositeAfterPaintName,
     flag_descriptions::kCompositeAfterPaintDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kCompositeAfterPaint)},
    {"autofill-parse-merchant-promo-code-fields",
     flag_descriptions::kAutofillParseMerchantPromoCodeFieldsName,
     flag_descriptions::kAutofillParseMerchantPromoCodeFieldsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillParseMerchantPromoCodeFields)},

<<<<<<< HEAD
    {"fedcm-show-filtered-accounts",
     flag_descriptions::kFedCmShowFilteredAccountsName,
     flag_descriptions::kFedCmShowFilteredAccountsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kFedCmShowFilteredAccounts)},

    {"fedcm-use-other-account", flag_descriptions::kFedCmUseOtherAccountName,
     flag_descriptions::kFedCmUseOtherAccountDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kFedCmUseOtherAccount)},
=======
    {"autofill-enable-offer-notification-cross-tab-tracking",
     flag_descriptions::kAutofillEnableOfferNotificationCrossTabTrackingName,
     flag_descriptions::
         kAutofillEnableOfferNotificationCrossTabTrackingDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableOfferNotificationCrossTabTracking)},
>>>>>>> chromium

    {"autofill-fix-offer-in-incognito",
     flag_descriptions::kAutofillFixOfferInIncognitoName,
     flag_descriptions::kAutofillFixOfferInIncognitoDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillFixOfferInIncognito)},

    {"web-identity-digital-credentials-creation",
     flag_descriptions::kWebIdentityDigitalCredentialsCreationName,
     flag_descriptions::kWebIdentityDigitalCredentialsCreationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kWebIdentityDigitalCredentialsCreation)},

    {"sanitizer-api", flag_descriptions::kSanitizerApiName,
     flag_descriptions::kSanitizerApiDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kSanitizerAPI)},

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"productivity-reorder-apps", flag_descriptions::kLauncherAppSortName,
     flag_descriptions::kLauncherAppSortDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kLauncherAppSort)},
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-desktop-pwas-app-icon-shortcuts-menu-ui",
     flag_descriptions::kDesktopPWAsAppIconShortcutsMenuUIName,
     flag_descriptions::kDesktopPWAsAppIconShortcutsMenuUIDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kDesktopPWAsAppIconShortcutsMenuUI)},

>>>>>>> chromium
    {"enable-input-event-logging",
     flag_descriptions::kEnableInputEventLoggingName,
     flag_descriptions::kEnableInputEventLoggingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableInputEventLogging)},
#endif

<<<<<<< HEAD
    {flag_descriptions::kEnableLensStandaloneFlagId,
     flag_descriptions::kEnableLensStandaloneName,
     flag_descriptions::kEnableLensStandaloneDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(lens::features::kLensStandalone)},
=======
    {"muting-compromised-credentials",
     flag_descriptions::kMutingCompromisedCredentialsName,
     flag_descriptions::kMutingCompromisedCredentialsDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         password_manager::features::kMutingCompromisedCredentials)},

    {"autofill-enable-merchant-bound-virtual-cards",
     flag_descriptions::kAutofillEnableMerchantBoundVirtualCardsName,
     flag_descriptions::kAutofillEnableMerchantBoundVirtualCardsDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableMerchantBoundVirtualCards)},
>>>>>>> chromium

    {"autofill-enable-sticky-manual-fallback-for-cards",
     flag_descriptions::kAutofillEnableStickyManualFallbackForCardsName,
     flag_descriptions::kAutofillEnableStickyManualFallbackForCardsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableStickyManualFallbackForCards)},

<<<<<<< HEAD
#if BUILDFLAG(IS_ANDROID)
=======
    {"autofill-auto-trigger-manual-fallback-for-cards",
     flag_descriptions::kAutofillAutoTriggerManualFallbackForCardsName,
     flag_descriptions::kAutofillAutoTriggerManualFallbackForCardsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillAutoTriggerManualFallbackForCards)},

    {"autofill-suggest-virtual-cards-on-incomplete-form",
     flag_descriptions::kAutofillSuggestVirtualCardsOnIncompleteFormName,
     flag_descriptions::kAutofillSuggestVirtualCardsOnIncompleteFormDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillSuggestVirtualCardsOnIncompleteForm)},

    {flag_descriptions::kEnableLensRegionSearchFlagId,
     flag_descriptions::kEnableLensRegionSearchName,
     flag_descriptions::kEnableLensRegionSearchDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(lens::features::kLensRegionSearch)},

    {"enable-penetrating-image-selection",
     flag_descriptions::kEnablePenetratingImageSelectionName,
     flag_descriptions::kEnablePenetratingImageSelectionDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kEnablePenetratingImageSelection)},

#if defined(OS_ANDROID)
>>>>>>> chromium
    {"biometric-reauth-password-filling",
     flag_descriptions::kBiometricReauthForPasswordFillingName,
     flag_descriptions::kBiometricReauthForPasswordFillingDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(password_manager::features::kBiometricTouchToFill)},
#endif

<<<<<<< HEAD
    {"bind-cookies-to-port", flag_descriptions::kBindCookiesToPortName,
     flag_descriptions::kBindCookiesToPortDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kEnablePortBoundCookies)},

    {"bind-cookies-to-scheme", flag_descriptions::kBindCookiesToSchemeName,
     flag_descriptions::kBindCookiesToSchemeDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kEnableSchemeBoundCookies)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-keyboard-backlight-control-in-settings",
     flag_descriptions::kEnableKeyboardBacklightControlInSettingsName,
     flag_descriptions::kEnableKeyboardBacklightControlInSettingsDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kEnableKeyboardBacklightControlInSettings)},
    {"enable-keyboard-rewriter-fix",
     flag_descriptions::kEnableKeyboardRewriterFixName,
     flag_descriptions::kEnableKeyboardRewriterFixDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableKeyboardRewriterFix)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"launcher-query-highlighting",
     flag_descriptions::kLauncherQueryHighlightingName,
     flag_descriptions::kLauncherQueryHighlightingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(app_list_features::kLauncherQueryHighlighting)},

    {"enable-input-noise-cancellation-ui",
     flag_descriptions::kEnableInputNoiseCancellationUiName,
     flag_descriptions::kEnableInputNoiseCancellationUiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kEnableInputNoiseCancellationUi)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"update-history-entry-points-in-incognito",
     flag_descriptions::kUpdateHistoryEntryPointsInIncognitoName,
     flag_descriptions::kUpdateHistoryEntryPointsInIncognitoDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kUpdateHistoryEntryPointsInIncognito)},

    {"enable-throttle-display-none-and-visibility-hidden-cross-origin-iframes",
     flag_descriptions::
         kThrottleDisplayNoneAndVisibilityHiddenCrossOriginIframesName,
     flag_descriptions::
         kThrottleDisplayNoneAndVisibilityHiddenCrossOriginIframesDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(
         blink::features::
             kThrottleDisplayNoneAndVisibilityHiddenCrossOriginIframes)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-input-in-diagnostics-app",
     flag_descriptions::kEnableInputInDiagnosticsAppName,
     flag_descriptions::kEnableInputInDiagnosticsAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kEnableInputInDiagnosticsApp)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
    {"link-doctor-deprecation-android",
     flag_descriptions::kLinkDoctorDeprecationAndroidName,
     flag_descriptions::kLinkDoctorDeprecationAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kLinkDoctorDeprecationAndroid)},
#endif

#if defined(TOOLKIT_VIEWS)
    {"download-shelf-webui", flag_descriptions::kDownloadShelfWebUI,
     flag_descriptions::kDownloadShelfWebUIDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kWebUIDownloadShelf)},
#endif  // defined(TOOLKIT_VIEWS)

    {"playback-speed-button", flag_descriptions::kPlaybackSpeedButtonName,
     flag_descriptions::kPlaybackSpeedButtonDescription, kOsAll,
     FEATURE_VALUE_TYPE(media::kPlaybackSpeedButton)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-generated-webapks", flag_descriptions::kEnableGeneratedWebApksName,
     flag_descriptions::kEnableGeneratedWebApksDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWebApkGenerator)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"use-passthrough-command-decoder",
     flag_descriptions::kUsePassthroughCommandDecoderName,
     flag_descriptions::kUsePassthroughCommandDecoderDescription,
     kOsMac | kOsLinux | kOsCrOS | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kDefaultPassthroughCommandDecoder)},

#if BUILDFLAG(IS_CHROMEOS)
    {"focus-follows-cursor", flag_descriptions::kFocusFollowsCursorName,
     flag_descriptions::kFocusFollowsCursorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(::features::kFocusFollowsCursor)},
<<<<<<< HEAD
    {"print-preview-cros-primary",
     flag_descriptions::kPrintPreviewCrosPrimaryName,
     flag_descriptions::kPrintPreviewCrosPrimaryDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kPrintPreviewCrosPrimary)},
#endif

    {"prerender2", flag_descriptions::kPrerender2Name,
     flag_descriptions::kPrerender2Description, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kPrerender2)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-phone-hub-call-notification",
     flag_descriptions::kPhoneHubCallNotificationName,
     flag_descriptions::kPhoneHubCallNotificationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPhoneHubCallNotification)},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

    {"clipboard-custom-formats", flag_descriptions::kClipboardCustomFormatsName,
     flag_descriptions::kClipboardCustomFormatsDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kClipboardCustomFormats)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"performant-split-view-resizing",
     flag_descriptions::kPerformantSplitViewResizing,
     flag_descriptions::kPerformantSplitViewResizingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPerformantSplitViewResizing)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"privacy-review", flag_descriptions::kPrivacyReviewName,
     flag_descriptions::kPrivacyReviewDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kPrivacyReview)},

#if defined(OS_ANDROID)
    {"google-mobile-services-passwords",
     flag_descriptions::kUnifiedPasswordManagerAndroidName,
     flag_descriptions::kUnifiedPasswordManagerAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         password_manager::features::kUnifiedPasswordManagerAndroid)},
#endif

<<<<<<< HEAD
    {"tpcd-heuristics-grants", flag_descriptions::kTpcdHeuristicsGrantsName,
     flag_descriptions::kTpcdHeuristicsGrantsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         content_settings::features::kTpcdHeuristicsGrants,
         kTpcdHeuristicsGrantsVariations,
         "TpcdHeuristicsGrants")},

    {"tpcd-metadata-grants", flag_descriptions::kTpcdMetadataGrantsName,
     flag_descriptions::kTpcdMetadataGrantsDescription, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kTpcdMetadataGrants)},

#if BUILDFLAG(IS_CHROMEOS)
    {kBackgroundListeningName, flag_descriptions::kBackgroundListeningName,
     flag_descriptions::kBackgroundListeningDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media::kBackgroundListening)},
    {kBorealisBigGlInternalName, flag_descriptions::kBorealisBigGlName,
     flag_descriptions::kBorealisBigGlDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisBigGl)},
    {kBorealisDGPUInternalName, flag_descriptions::kBorealisDGPUName,
     flag_descriptions::kBorealisDGPUDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisDGPU)},
    {kBorealisEnableUnsupportedHardwareInternalName,
     flag_descriptions::kBorealisEnableUnsupportedHardwareName,
     flag_descriptions::kBorealisEnableUnsupportedHardwareDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisEnableUnsupportedHardware)},
    {kBorealisForceBetaClientInternalName,
     flag_descriptions::kBorealisForceBetaClientName,
     flag_descriptions::kBorealisForceBetaClientDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisForceBetaClient)},
    {kBorealisForceDoubleScaleInternalName,
     flag_descriptions::kBorealisForceDoubleScaleName,
     flag_descriptions::kBorealisForceDoubleScaleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisForceDoubleScale)},
    {kBorealisLinuxModeInternalName, flag_descriptions::kBorealisLinuxModeName,
     flag_descriptions::kBorealisLinuxModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisLinuxMode)},
    {kBorealisPermittedInternalName, flag_descriptions::kBorealisPermittedName,
     flag_descriptions::kBorealisPermittedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisPermitted)},
    {kBorealisProvisionInternalName, flag_descriptions::kBorealisProvisionName,
     flag_descriptions::kBorealisProvisionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisProvision)},
    {kBorealisScaleClientByDPIInternalName,
     flag_descriptions::kBorealisScaleClientByDPIName,
     flag_descriptions::kBorealisScaleClientByDPIDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisScaleClientByDPI)},
    {kBorealisZinkGlDriverInternalName,
     flag_descriptions::kBorealisZinkGlDriverName,
     flag_descriptions::kBorealisZinkGlDriverDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kBorealisZinkGlDriver,
                                    kBorealisZinkGlDriverVariations,
                                    "BorealisZinkGlDriver")},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
    {"extension-workflow-justification",
     flag_descriptions::kExtensionWorkflowJustificationName,
     flag_descriptions::kExtensionWorkflowJustificationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kExtensionWorkflowJustification)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"arc-web-app-share", flag_descriptions::kArcWebAppShareName,
     flag_descriptions::kArcWebAppShareDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kEnableWebAppShareFeature)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"tab-restore-sub-menus", flag_descriptions::kTabRestoreSubMenusName,
     flag_descriptions::kTabRestoreSubMenusDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabRestoreSubMenus)},

    {"chrome-whats-new-ui", flag_descriptions::kChromeWhatsNewUIName,
     flag_descriptions::kChromeWhatsNewUIDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kChromeWhatsNewUI)},

<<<<<<< HEAD
    {"https-first-mode-interstitial-august2024-refresh",
     flag_descriptions::kHttpsFirstModeInterstitialAugust2024RefreshName,
     flag_descriptions::kHttpsFirstModeInterstitialAugust2024RefreshDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(
         features::kHttpsFirstModeInterstitialAugust2024Refresh)},

    {"https-first-mode-v2-for-engaged-sites",
     flag_descriptions::kHttpsFirstModeV2ForEngagedSitesName,
     flag_descriptions::kHttpsFirstModeV2ForEngagedSitesDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kHttpsFirstModeV2ForEngagedSites)},

    {"https-upgrades", flag_descriptions::kHttpsUpgradesName,
     flag_descriptions::kHttpsUpgradesDescription, kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kHttpsUpgrades)},

    {"https-first-mode-incognito",
     flag_descriptions::kHttpsFirstModeIncognitoName,
     flag_descriptions::kHttpsFirstModeIncognitoDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kHttpsFirstModeIncognito)},

    {"https-first-mode-incognito-new-settings",
     flag_descriptions::kHttpsFirstModeIncognitoNewSettingsName,
     flag_descriptions::kHttpsFirstModeIncognitoNewSettingsDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kHttpsFirstModeIncognitoNewSettings)},

    {"https-first-mode-for-typically-secure-users",
     flag_descriptions::kHttpsFirstModeForTypicallySecureUsersName,
     flag_descriptions::kHttpsFirstModeForTypicallySecureUsersDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kHttpsFirstModeV2ForTypicallySecureUsers)},

    {"enable-drdc", flag_descriptions::kEnableDrDcName,
     flag_descriptions::kEnableDrDcDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kEnableDrDc)},

#if BUILDFLAG(IS_CHROMEOS)
    {"traffic-counters", flag_descriptions::kTrafficCountersEnabledName,
     flag_descriptions::kTrafficCountersEnabledDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kTrafficCountersEnabled)},

    {"traffic-counters-for-wifi-testing",
     flag_descriptions::kTrafficCountersForWiFiTestingName,
     flag_descriptions::kTrafficCountersForWiFiTestingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kTrafficCountersForWiFiTesting)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(ENABLE_EXTENSIONS)
    {"experimental-omnibox-labs",
     flag_descriptions::kExperimentalOmniboxLabsName,
     flag_descriptions::kExperimentalOmniboxLabsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(extensions_features::kExperimentalOmniboxLabs)},

    {kExtensionAiDataInternalName,
     flag_descriptions::kExtensionAiDataCollectionName,
     flag_descriptions::kExtensionAiDataCollectionDescription, kOsDesktop,
     SINGLE_VALUE_TYPE(switches::kExtensionAiDataCollection)},

    {"extensions-menu-access-control",
     flag_descriptions::kExtensionsMenuAccessControlName,
     flag_descriptions::kExtensionsMenuAccessControlDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(extensions_features::kExtensionsMenuAccessControl)},

    {"extensions-toolbar-zero-state-variation",
     flag_descriptions::kExtensionsToolbarZeroStateName,
     flag_descriptions::kExtensionsToolbarZeroStateDescription, kOsDesktop,
     MULTI_VALUE_TYPE(kExtensionsToolbarZeroStateChoices)},

    {"iph-extensions-menu-feature",
     flag_descriptions::kIPHExtensionsMenuFeatureName,
     flag_descriptions::kIPHExtensionsMenuFeatureDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(feature_engagement::kIPHExtensionsMenuFeature)},

    {"iph-extensions-request-access-button-feature",
     flag_descriptions::kIPHExtensionsRequestAccessButtonFeatureName,
     flag_descriptions::kIPHExtensionsRequestAccessButtonFeatureDescription,
=======
#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
    {"chrome-whats-new-in-main-menu-new-badge",
     flag_descriptions::kChromeWhatsNewInMainMenuNewBadgeName,
     flag_descriptions::kChromeWhatsNewInMainMenuNewBadgeDescription,
>>>>>>> chromium
     kOsDesktop,
     FEATURE_VALUE_TYPE(features::kChromeWhatsNewInMainMenuNewBadge)},
#endif  // BUILDFLAG(GOOGLE_CHROME_BRANDING)

    {"sync-trusted-vault-passphrase-promo",
     flag_descriptions::kSyncTrustedVaultPassphrasePromoName,
     flag_descriptions::kSyncTrustedVaultPassphrasePromoDescription, kOsAll,
     FEATURE_VALUE_TYPE(::switches::kSyncTrustedVaultPassphrasePromo)},

    {"sync-trusted-vault-passphrase-recovery",
     flag_descriptions::kSyncTrustedVaultPassphraseRecoveryName,
     flag_descriptions::kSyncTrustedVaultPassphraseRecoveryDescription, kOsAll,
     FEATURE_VALUE_TYPE(::switches::kSyncTrustedVaultPassphraseRecovery)},

<<<<<<< HEAD
    {"extension-manifest-v2-deprecation-unsupported",
     flag_descriptions::kExtensionManifestV2DeprecationUnsupportedName,
     flag_descriptions::kExtensionManifestV2DeprecationUnsupportedDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(extensions_features::kExtensionManifestV2Unsupported)},

#if BUILDFLAG(IS_CHROMEOS)
    {"extension-web-file-handlers",
     flag_descriptions::kExtensionWebFileHandlersName,
     flag_descriptions::kExtensionWebFileHandlersDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(extensions_features::kExtensionWebFileHandlers)},
#endif  // IS_CHROMEOS
#if BUILDFLAG(IS_WIN)
    {"launch-windows-native-hosts-directly",
     flag_descriptions::kLaunchWindowsNativeHostsDirectlyName,
     flag_descriptions::kLaunchWindowsNativeHostsDirectlyDescription, kOsWin,
     FEATURE_VALUE_TYPE(
         extensions_features::kLaunchWindowsNativeHostsDirectly)},
#endif  // IS_WIN
#endif  // ENABLE_EXTENSIONS

#if !BUILDFLAG(IS_ANDROID)
    {"canvas-oop-rasterization", flag_descriptions::kCanvasOopRasterizationName,
     flag_descriptions::kCanvasOopRasterizationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kCanvasOopRasterization)},
#endif

#if !BUILDFLAG(IS_ANDROID)
    {"captured-surface-control", flag_descriptions::kCapturedSurfaceControlName,
     flag_descriptions::kCapturedSurfaceControlDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kCapturedSurfaceControl)},
#endif

    {"skia-graphite", flag_descriptions::kSkiaGraphiteName,
     flag_descriptions::kSkiaGraphiteDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kSkiaGraphite,
                                    kSkiaGraphiteVariations,
                                    "SkiaGraphite")},

    {"skia-graphite-precompilation",
     flag_descriptions::kSkiaGraphitePrecompilationName,
     flag_descriptions::kSkiaGraphitePrecompilationDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kSkiaGraphitePrecompilation)},

    {"enable-tab-audio-muting", flag_descriptions::kTabAudioMutingName,
     flag_descriptions::kTabAudioMutingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(media::kEnableTabMuting)},

#if !BUILDFLAG(IS_ANDROID)
    {"customize-chrome-side-panel-extensions-card",
     flag_descriptions::kCustomizeChromeSidePanelExtensionsCardName,
     flag_descriptions::kCustomizeChromeSidePanelExtensionsCardDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kCustomizeChromeSidePanelExtensionsCard)},

    {"customize-chrome-wallpaper-search",
     flag_descriptions::kCustomizeChromeWallpaperSearchName,
     flag_descriptions::kCustomizeChromeWallpaperSearchDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kCustomizeChromeWallpaperSearch)},

    {"customize-chrome-wallpaper-search-button",
     flag_descriptions::kCustomizeChromeWallpaperSearchButtonName,
     flag_descriptions::kCustomizeChromeWallpaperSearchButtonDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(ntp_features::kCustomizeChromeWallpaperSearchButton)},

    {"customize-chrome-wallpaper-search-inspiration-card",
     flag_descriptions::kCustomizeChromeWallpaperSearchInspirationCardName,
     flag_descriptions::
         kCustomizeChromeWallpaperSearchInspirationCardDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         ntp_features::kCustomizeChromeWallpaperSearchInspirationCard)},

    {"wallpaper-search-settings-visibility",
     flag_descriptions::kWallpaperSearchSettingsVisibilityName,
     flag_descriptions::kWallpaperSearchSettingsVisibilityDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(optimization_guide::features::internal::
                            kWallpaperSearchSettingsVisibility)},
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-component-updater-test-request",
     flag_descriptions::kComponentUpdaterTestRequestName,
     flag_descriptions::kComponentUpdaterTestRequestDescription, kOsCrOS,
     SINGLE_VALUE_TYPE_AND_VALUE(switches::kComponentUpdater,
                                 component_updater::kSwitchTestRequestParam)},

    {kGrowthCampaignsTestTag,
     flag_descriptions::kCampaignsComponentUpdaterTestTagName,
     flag_descriptions::kCampaignsComponentUpdaterTestTagDescription, kOsCrOS,
     STRING_VALUE_TYPE(switches::kCampaignsTestTag, "")},

    {kGrowthCampaigns, flag_descriptions::kCampaignsOverrideName,
     flag_descriptions::kCampaignsOverrideDescription, kOsCrOS,
     STRING_VALUE_TYPE(ash::switches::kGrowthCampaigns, "")},

    {"demo-mode-test-tag",
     flag_descriptions::kDemoModeComponentUpdaterTestTagName,
     flag_descriptions::kDemoModeComponentUpdaterTestTagDescription, kOsCrOS,
     STRING_VALUE_TYPE(switches::kDemoModeTestTag, "")},
#endif

#if BUILDFLAG(IS_CHROMEOS_LACROS) || BUILDFLAG(IS_WIN)
    {"enable-delegated-compositing",
     flag_descriptions::kEnableDelegatedCompositingName,
     flag_descriptions::kEnableDelegatedCompositingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kDelegatedCompositing)},
#endif

    {"enable-render-pass-drawn-rect",
     flag_descriptions::kEnableRenderPassDrawnRectName,
     flag_descriptions::kEnableRenderPassDrawnRectDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kRenderPassDrawnRect)},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || \
    BUILDFLAG(IS_CHROMEOS)
    {"media-session-enter-picture-in-picture",
     flag_descriptions::kMediaSessionEnterPictureInPictureName,
     flag_descriptions::kMediaSessionEnterPictureInPictureDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kMediaSessionEnterPictureInPicture)},

    {"auto-picture-in-picture-video-heuristics",
     flag_descriptions::kAutoPictureInPictureVideoHeuristicsName,
     flag_descriptions::kAutoPictureInPictureVideoHeuristicsDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kAutoPictureInPictureVideoHeuristics)},

    {"auto-picture-in-picture-for-video-playback",
     flag_descriptions::kAutoPictureInPictureForVideoPlaybackName,
     flag_descriptions::kAutoPictureInPictureForVideoPlaybackDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(media::kAutoPictureInPictureForVideoPlayback)},

    {"video-picture-in-picture-controls-update-2024",
     flag_descriptions::kVideoPictureInPictureControlsUpdate2024Name,
     flag_descriptions::kVideoPictureInPictureControlsUpdate2024Description,
     kOsDesktop,
     FEATURE_VALUE_TYPE(media::kVideoPictureInPictureControlsUpdate2024)},

    {"document-picture-in-picture-animate-resize",
     flag_descriptions::kDocumentPictureInPictureAnimateResizeName,
     flag_descriptions::kDocumentPictureInPictureAnimateResizeDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(media::kDocumentPictureInPictureAnimateResize)},

#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) ||
        // BUILDFLAG(IS_CHROMEOS)

#if !BUILDFLAG(IS_ANDROID)
    {"audio-ducking", flag_descriptions::kAudioDuckingName,
     flag_descriptions::kAudioDuckingDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(media::kAudioDucking,
                                    kAudioDuckingAttenuationVariations,
                                    "AudioDucking")},
#endif  // !BUILDFLAG(IS_ANDROID)

    {"enable-commerce-developer", flag_descriptions::kCommerceDeveloperName,
     flag_descriptions::kCommerceDeveloperDescription, kOsAll,
     FEATURE_VALUE_TYPE(commerce::kCommerceDeveloper)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-libinput-to-handle-touchpad",
     flag_descriptions::kEnableLibinputToHandleTouchpadName,
     flag_descriptions::kEnableLibinputToHandleTouchpadDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kLibinputHandleTouchpad)},

    {"enable-desks-templates", flag_descriptions::kDesksTemplatesName,
     flag_descriptions::kDesksTemplatesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDesksTemplates)},

    {"vc-background-replace", flag_descriptions::kVcBackgroundReplaceName,
     flag_descriptions::kVcBackgroundReplaceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVcBackgroundReplace)},

    {"vc-relighting-inference-backend",
     flag_descriptions::kVcRelightingInferenceBackendName,
     flag_descriptions::kVcRelightingInferenceBackendDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         ash::features::kVcRelightingInferenceBackend,
         kVcRelightingInferenceBackendVariations,
         "VcRelightingInferenceBackend")},
    {"vc-retouch-inference-backend",
     flag_descriptions::kVcRetouchInferenceBackendName,
     flag_descriptions::kVcRetouchInferenceBackendDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kVcRetouchInferenceBackend,
                                    kVcRetouchInferenceBackendVariations,
                                    "VcRetouchInferenceBackend")},
    {"vc-segmentation-model", flag_descriptions::kVcSegmentationModelName,
     flag_descriptions::kVcSegmentationModelDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kVcSegmentationModel,
                                    kVcSegmentationModelVariations,
                                    "VCSegmentationModel")},
    {"vc-segmentation-inference-backend",
     flag_descriptions::kVcSegmentationInferenceBackendName,
     flag_descriptions::kVcSegmentationInferenceBackendDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         ash::features::kVcSegmentationInferenceBackend,
         kVcSegmentationInferenceBackendVariations,
         "VcSegmentationInferenceBackend")},
    {"vc-light-intensity", flag_descriptions::kVcLightIntensityName,
     flag_descriptions::kVcLightIntensityDescription, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(ash::features::kVcLightIntensity,
                                    kVcLightIntensityVariations,
                                    "VCLightIntensity")},
    {"vc-web-api", flag_descriptions::kVcWebApiName,
     flag_descriptions::kVcWebApiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVcWebApi)},
    {kVcTrayMicIndicatorInternalName,
     flag_descriptions::kVcTrayMicIndicatorName,
     flag_descriptions::kVcTrayMicIndicatorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVcTrayMicIndicator)},
    {kVcTrayTitleHeaderInternalName, flag_descriptions::kVcTrayTitleHeaderName,
     flag_descriptions::kVcTrayTitleHeaderDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVcTrayTitleHeader)},
#endif

#if BUILDFLAG(IS_ANDROID)
    {"animated-image-drag-shadow",
     flag_descriptions::kAnimatedImageDragShadowName,
     flag_descriptions::kAnimatedImageDragShadowDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAnimatedImageDragShadow)},
#endif  // BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {"main-node-annotations", flag_descriptions::kMainNodeAnnotationsName,
     flag_descriptions::kMainNodeAnnotationsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kMainNodeAnnotations)},
#endif

    {"origin-agent-cluster-default",
     flag_descriptions::kOriginAgentClusterDefaultName,
     flag_descriptions::kOriginAgentClusterDefaultDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kOriginAgentClusterDefaultEnabled)},

    {"origin-keyed-processes-by-default",
     flag_descriptions::kOriginKeyedProcessesByDefaultName,
     flag_descriptions::kOriginKeyedProcessesByDefaultDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kOriginKeyedProcessesByDefault)},

    {"collaboration-messaging", flag_descriptions::kCollaborationMessagingName,
     flag_descriptions::kCollaborationMessagingDescription, kOsAll,
     FEATURE_VALUE_TYPE(collaboration::features::kCollaborationMessaging)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-fake-keyboard-heuristic",
     flag_descriptions::kEnableFakeKeyboardHeuristicName,
     flag_descriptions::kEnableFakeKeyboardHeuristicDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableFakeKeyboardHeuristic)},
    {"enable-fake-mouse-heuristic",
     flag_descriptions::kEnableFakeMouseHeuristicName,
     flag_descriptions::kEnableFakeMouseHeuristicDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableFakeMouseHeuristic)},
#endif  // BUILDFLAG(IS_CHROMEOS)
#if !BUILDFLAG(IS_ANDROID)
    {"enable-isolated-sandboxed-iframes",
     flag_descriptions::kIsolatedSandboxedIframesName,
     flag_descriptions::kIsolatedSandboxedIframesDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         blink::features::kIsolateSandboxedIframes,
         kIsolateSandboxedIframesGroupingVariations,
         "IsolateSandboxedIframes" /* trial name */)},
#endif

    {"download-warning-improvements",
     flag_descriptions::kDownloadWarningImprovementsName,
     flag_descriptions::kDownloadWarningImprovementsDescription,
     kOsLinux | kOsMac | kOsWin | kOsCrOS,
     MULTI_VALUE_TYPE(kDownloadWarningImprovementsChoices)},

    {"reduce-accept-language", flag_descriptions::kReduceAcceptLanguageName,
     flag_descriptions::kReduceAcceptLanguageDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kReduceAcceptLanguage)},

    {"reduce-transfer-size-updated-ipc",
     flag_descriptions::kReduceTransferSizeUpdatedIPCName,
     flag_descriptions::kReduceTransferSizeUpdatedIPCDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kReduceTransferSizeUpdatedIPC)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-variable-refresh-rate",
     flag_descriptions::kEnableVariableRefreshRateName,
     flag_descriptions::kEnableVariableRefreshRateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableVariableRefreshRate)},

    {"enable-projector-app-debug", flag_descriptions::kProjectorAppDebugName,
     flag_descriptions::kProjectorAppDebugDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kProjectorAppDebug)},

    {kProjectorServerSideSpeechRecognition,
     flag_descriptions::kProjectorServerSideSpeechRecognitionName,
     flag_descriptions::kProjectorServerSideSpeechRecognitionDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kInternalServerSideSpeechRecognition)},

    {"enable-projector-server-side-usm",
     flag_descriptions::kProjectorServerSideUsmName,
     flag_descriptions::kProjectorServerSideUsmDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kProjectorUseUSMForS3)},

    {"enable-projector-gm3", flag_descriptions::kProjectorGm3Name,
     flag_descriptions::kProjectorGm3Description, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kProjectorGm3)},

    {"projector-use-dvs-playback-endpoint",
     flag_descriptions::kProjectorUseDVSPlaybackEndpointName,
     flag_descriptions::kProjectorUseDVSPlaybackEndpointDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kProjectorUseDVSPlaybackEndpoint)},

    {"enable-annotator-mode", flag_descriptions::kAnnotatorModeName,
     flag_descriptions::kAnnotatorModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAnnotatorMode)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"omit-cors-client-cert", flag_descriptions::kOmitCorsClientCertName,
     flag_descriptions::kOmitCorsClientCertDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kOmitCorsClientCert)},

    {"use-idna2008-non-transitional",
     flag_descriptions::kUseIDNA2008NonTransitionalName,
     flag_descriptions::kUseIDNA2008NonTransitionalDescription, kOsAll,
     FEATURE_VALUE_TYPE(url::kUseIDNA2008NonTransitional)},

#if BUILDFLAG(IS_CHROMEOS)
    {"always-enable-hdcp", flag_descriptions::kAlwaysEnableHdcpName,
     flag_descriptions::kAlwaysEnableHdcpDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kAlwaysEnableHdcpChoices)},
    {"enable-touchpads-in-diagnostics-app",
     flag_descriptions::kEnableTouchpadsInDiagnosticsAppName,
     flag_descriptions::kEnableTouchpadsInDiagnosticsAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableTouchpadsInDiagnosticsApp)},
    {"enable-touchscreens-in-diagnostics-app",
     flag_descriptions::kEnableTouchscreensInDiagnosticsAppName,
     flag_descriptions::kEnableTouchscreensInDiagnosticsAppDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableTouchscreensInDiagnosticsApp)},
    {"enable-external-keyboards-in-diagnostics-app",
     flag_descriptions::kEnableExternalKeyboardsInDiagnosticsAppName,
     flag_descriptions::kEnableExternalKeyboardsInDiagnosticsAppDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableExternalKeyboardsInDiagnostics)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"autofill-enable-virtual-card-metadata",
     flag_descriptions::kAutofillEnableVirtualCardMetadataName,
     flag_descriptions::kAutofillEnableVirtualCardMetadataDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableVirtualCardMetadata)},

#if BUILDFLAG(IS_ANDROID)
    {"password-suggestion-bottom-sheet-v2",
     flag_descriptions::kPasswordSuggestionBottomSheetV2Name,
     flag_descriptions::kPasswordSuggestionBottomSheetV2Description, kOsAndroid,
     FEATURE_VALUE_TYPE(
         password_manager::features::kPasswordSuggestionBottomSheetV2)},

    {"pwa-restore-backend", flag_descriptions::kPwaRestoreBackendName,
     flag_descriptions::kPwaRestoreBackendDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(syncer::kWebApkBackupAndRestoreBackend)},

    {"pwa-restore-ui", flag_descriptions::kPwaRestoreUiName,
     flag_descriptions::kPwaRestoreUiDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kPwaRestoreUi)},

    {"pwa-restore-ui-at-startup", flag_descriptions::kPwaRestoreUiAtStartupName,
     flag_descriptions::kPwaRestoreUiAtStartupDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kPwaRestoreUiAtStartup)},
#endif  // BUILDFLAG(IS_ANDROID)
    {"autofill-enable-ranking-formula-address-profiles",
     flag_descriptions::kAutofillEnableRankingFormulaAddressProfilesName,
     flag_descriptions::kAutofillEnableRankingFormulaAddressProfilesDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableRankingFormulaAddressProfiles)},

    {"autofill-enable-ranking-formula-credit-cards",
     flag_descriptions::kAutofillEnableRankingFormulaCreditCardsName,
     flag_descriptions::kAutofillEnableRankingFormulaCreditCardsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableRankingFormulaCreditCards)},

    {"safe-browsing-local-lists-use-sbv5",
     flag_descriptions::kSafeBrowsingLocalListsUseSBv5Name,
     flag_descriptions::kSafeBrowsingLocalListsUseSBv5Description, kOsAll,
     FEATURE_VALUE_TYPE(safe_browsing::kLocalListsUseSBv5)},

    {"safety-check-unused-site-permissions",
     flag_descriptions::kSafetyCheckUnusedSitePermissionsName,
     flag_descriptions::kSafetyCheckUnusedSitePermissionsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         content_settings::features::kSafetyCheckUnusedSitePermissions,
         kSafetyCheckUnusedSitePermissionsVariations,
         "SafetyCheckUnusedSitePermissions")},

    {"safety-hub", flag_descriptions::kSafetyHubName,
     flag_descriptions::kSafetyHubDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kSafetyHub,
                                    kSafetyHubVariations,
                                    "SafetyHub")},
    {"plus-address-full-form-fill",
     flag_descriptions::kPlusAddressFullFormFillName,
     flag_descriptions::kPlusAddressFullFormFillDescription, kOsAll,
     FEATURE_VALUE_TYPE(plus_addresses::features::kPlusAddressFullFormFill)},

    {"permission-site-settings-radio-button",
     flag_descriptions::kPermissionSiteSettingsRadioButtonName,
     flag_descriptions::kPermissionSiteSettingsRadioButtonDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         permissions::features::kPermissionSiteSettingsRadioButton)},

#if BUILDFLAG(IS_ANDROID)
    {"safety-hub-magic-stack", flag_descriptions::kSafetyHubMagicStackName,
     flag_descriptions::kSafetyHubMagicStackDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kSafetyHubMagicStack)},

    {"safety-hub-followup", flag_descriptions::kSafetyHubFollowupName,
     flag_descriptions::kSafetyHubFollowupDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kSafetyHubFollowup)},

    {"safety-hub-android-survey",
     flag_descriptions::kSafetyHubAndroidSurveyName,
     flag_descriptions::kSafetyHubAndroidSurveyDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kSafetyHubAndroidSurvey)},

    {"safety-hub-android-survey-v2",
     flag_descriptions::kSafetyHubAndroidSurveyV2Name,
     flag_descriptions::kSafetyHubAndroidSurveyV2Description, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kSafetyHubAndroidSurveyV2)},

    {"safety-hub-weak-reused-passwords",
     flag_descriptions::kSafetyHubWeakAndReusedPasswordsName,
     flag_descriptions::kSafetyHubWeakAndReusedPasswordsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kSafetyHubWeakAndReusedPasswords)},
#else
    {"safety-hub-one-off-survey",
     flag_descriptions::kSafetyHubHaTSOneOffSurveyName,
     flag_descriptions::kSafetyHubHaTSOneOffSurveyDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSafetyHubHaTSOneOffSurvey)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"on-device-notification-content-detection-model",
     flag_descriptions::kOnDeviceNotificationContentDetectionModelName,
     flag_descriptions::kOnDeviceNotificationContentDetectionModelDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         safe_browsing::kOnDeviceNotificationContentDetectionModel,
         kOnDeviceNotificationContentDetectionModelVariations,
         "OnDeviceNotificationContentDetectionModel")},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX)
    {"enable-web-bluetooth-confirm-pairing-support",
     flag_descriptions::kWebBluetoothConfirmPairingSupportName,
     flag_descriptions::kWebBluetoothConfirmPairingSupportDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(device::features::kWebBluetoothConfirmPairingSupport)},
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX)

    {"enable-perfetto-system-tracing",
     flag_descriptions::kEnablePerfettoSystemTracingName,
     flag_descriptions::kEnablePerfettoSystemTracingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kEnablePerfettoSystemTracing)},

#if BUILDFLAG(IS_ANDROID)
    {"browsing-data-model-clank", flag_descriptions::kBrowsingDataModelName,
     flag_descriptions::kBrowsingDataModelDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(browsing_data::features::kBrowsingDataModel)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-seamless-refresh-rate-switching",
     flag_descriptions::kEnableSeamlessRefreshRateSwitchingName,
     flag_descriptions::kEnableSeamlessRefreshRateSwitchingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSeamlessRefreshRateSwitching)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"click-to-call", flag_descriptions::kClickToCallName,
     flag_descriptions::kClickToCallDescription, kOsAll,
     FEATURE_VALUE_TYPE(kClickToCall)},

    {"css-gamut-mapping", flag_descriptions::kCssGamutMappingName,
     flag_descriptions::kCssGamutMappingDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kBakedGamutMapping)},

    {"clipboard-maximum-age", flag_descriptions::kClipboardMaximumAgeName,
     flag_descriptions::kClipboardMaximumAgeDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(kClipboardMaximumAge,
                                    kClipboardMaximumAgeVariations,
                                    "ClipboardMaximumAge")},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-media-dynamic-cgroup", flag_descriptions::kMediaDynamicCgroupName,
     flag_descriptions::kMediaDynamicCgroupDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootMediaDynamicCgroup")},
#endif  // BUILDFLAG(IS_CHROMEOS)
=======
    {"debug-history-intervention-no-user-activation",
     flag_descriptions::kDebugHistoryInterventionNoUserActivationName,
     flag_descriptions::kDebugHistoryInterventionNoUserActivationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kDebugHistoryInterventionNoUserActivation)},

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"smart-lock-ui-revamp", flag_descriptions::kSmartLockUIRevampName,
     flag_descriptions::kSmartLockUIRevampDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSmartLockUIRevamp)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-phone-hub-camera-roll", flag_descriptions::kPhoneHubCameraRollName,
     flag_descriptions::kPhoneHubCameraRollDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPhoneHubCameraRoll)},

    {"enable-phone-hub-recent-apps", flag_descriptions::kPhoneHubRecentAppsName,
     flag_descriptions::kPhoneHubRecentAppsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPhoneHubRecentApps)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
>>>>>>> chromium

    {"sameparty-cookies-considered-first-party",
     flag_descriptions::kSamePartyCookiesConsideredFirstPartyName,
     flag_descriptions::kSamePartyCookiesConsideredFirstPartyDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(net::features::kSamePartyCookiesConsideredFirstParty)},

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"arc-vm-memory-size", flag_descriptions::kArcVmMemorySizeName,
     flag_descriptions::kArcVmMemorySizeDesc, kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(arc::kVmMemorySize,
                                    kArcVmMemorySizeVariations,
                                    "VmMemorySize")},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
    {"tab-group-creation-dialog-android",
     flag_descriptions::kTabGroupCreationDialogAndroidName,
     flag_descriptions::kTabGroupCreationDialogAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabGroupCreationDialogAndroid)},

    {"tab-group-pane-android", flag_descriptions::kTabGroupPaneAndroidName,
     flag_descriptions::kTabGroupPaneAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(tab_groups::kTabGroupPaneAndroid)},

    {"tab-strip-group-collapse-android",
     flag_descriptions::kTabStripGroupCollapseAndroidName,
     flag_descriptions::kTabStripGroupCollapseAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabStripGroupCollapseAndroid)},

    {"tab-strip-group-drag-drop-android",
     flag_descriptions::kTabStripGroupDragDropAndroidName,
     flag_descriptions::kTabStripGroupDragDropAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabStripGroupDragDropAndroid)},

    {"tab-strip-group-reorder-android",
     flag_descriptions::kTabStripGroupReorderAndroidName,
     flag_descriptions::kTabStripGroupReorderAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabStripGroupReorderAndroid)},

    {"tab-strip-incognito-migration",
     flag_descriptions::kTabStripIncognitoMigrationName,
     flag_descriptions::kTabStripIncognitoMigrationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabStripIncognitoMigration)},

    {"tab-strip-layout-optimization",
     flag_descriptions::kTabStripLayoutOptimizationName,
     flag_descriptions::kTabStripLayoutOptimizationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabStripLayoutOptimization)},

    {"tab-strip-transition-in-desktop-window",
     flag_descriptions::kTabStripTransitionInDesktopWindowName,
     flag_descriptions::kTabStripTransitionInDesktopWindowDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabStripTransitionInDesktopWindow)},
#endif

    {"use-dmsaa-for-tiles", flag_descriptions::kUseDMSAAForTilesName,
     flag_descriptions::kUseDMSAAForTilesDescription, kOsAll,
     FEATURE_VALUE_TYPE(::features::kUseDMSAAForTiles)},

#if BUILDFLAG(IS_CHROMEOS)
    {"app-launch-shortcut", flag_descriptions::kAppLaunchShortcut,
     flag_descriptions::kAppLaunchShortcutDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kAppLaunchShortcut)},
    {"enable-holding-space-suggestions",
     flag_descriptions::kHoldingSpaceSuggestionsName,
     flag_descriptions::kHoldingSpaceSuggestionsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kHoldingSpaceSuggestions)},
    {"enable-welcome-experience", flag_descriptions::kWelcomeExperienceName,
     flag_descriptions::kWelcomeExperienceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWelcomeExperience)},
    {"enable-welcome-experience-test-unsupported-devices",
     flag_descriptions::kWelcomeExperienceTestUnsupportedDevicesName,
     flag_descriptions::kWelcomeExperienceTestUnsupportedDevicesDescription,
=======
#if BUILDFLAG(IS_CHROMEOS_ASH)
    {kBorealisDiskManagementInternalName,
     flag_descriptions::kBorealisDiskManagementName,
     flag_descriptions::kBorealisDiskManagementDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBorealisDiskManagement)},
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_ANDROID)
    {"dynamic-color-android", flag_descriptions::kDynamicColorAndroidName,
     flag_descriptions::kDynamicColorAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kDynamicColorAndroid)},
#endif  //   defined(OS_ANDROID)

#if defined(OS_WIN)
    {"win-10-tab-search-caption-button",
     flag_descriptions::kWin10TabSearchCaptionButtonName,
     flag_descriptions::kWin10TabSearchCaptionButtonDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kWin10TabSearchCaptionButton)},
#endif  // defined(OS_WIN)

#if BUILDFLAG(IS_CHROMEOS_ASH)
    {"enable-holding-space-in-progress-downloads-integration",
     flag_descriptions::kHoldingSpaceInProgressDownloadsIntegrationName,
     flag_descriptions::kHoldingSpaceInProgressDownloadsIntegrationDescription,
>>>>>>> chromium
     kOsCrOS,
     FEATURE_VALUE_TYPE(
         ash::features::kHoldingSpaceInProgressDownloadsIntegration)},
#endif

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
    {"google-one-offer-files-banner",
     flag_descriptions::kGoogleOneOfferFilesBannerName,
     flag_descriptions::kGoogleOneOfferFilesBannerDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kGoogleOneOfferFilesBanner)},
#endif

    {"sync-autofill-wallet-credential-data",
     flag_descriptions::kSyncAutofillWalletCredentialDataName,
     flag_descriptions::kSyncAutofillWalletCredentialDataDescription, kOsAll,
     FEATURE_VALUE_TYPE(syncer::kSyncAutofillWalletCredentialData)},

    {"sync-autofill-wallet-usage-data",
     flag_descriptions::kSyncAutofillWalletUsageDataName,
     flag_descriptions::kSyncAutofillWalletUsageDataDescription, kOsAll,
     FEATURE_VALUE_TYPE(syncer::kSyncAutofillWalletUsageData)},

#if !BUILDFLAG(IS_ANDROID)
    {"ui-enable-shared-image-cache-for-gpu",
     flag_descriptions::kUIEnableSharedImageCacheForGpuName,
     flag_descriptions::kUIEnableSharedImageCacheForGpuDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(::features::kUIEnableSharedImageCacheForGpu)},
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-labs-window-cycle-shortcut",
     flag_descriptions::kSameAppWindowCycleName,
     flag_descriptions::kSameAppWindowCycleDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSameAppWindowCycle)},
    {"promise-icons", flag_descriptions::kPromiseIconsName,
     flag_descriptions::kPromiseIconsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPromiseIcons)},
    {"printing-ppd-channel", flag_descriptions::kPrintingPpdChannelName,
     flag_descriptions::kPrintingPpdChannelDescription, kOsCrOS,
     MULTI_VALUE_TYPE(kPrintingPpdChannelChoices)},
    {"arc-idle-manager", flag_descriptions::kArcIdleManagerName,
     flag_descriptions::kArcIdleManagerDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(arc::kEnableArcIdleManager)},
#endif

    {"autofill-enable-new-card-art-and-network-images",
     flag_descriptions::kAutofillEnableNewCardArtAndNetworkImagesName,
     flag_descriptions::kAutofillEnableNewCardArtAndNetworkImagesDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableNewCardArtAndNetworkImages)},

    {"power-bookmark-backend", flag_descriptions::kPowerBookmarkBackendName,
     flag_descriptions::kPowerBookmarkBackendDescription, kOsAll,
     FEATURE_VALUE_TYPE(power_bookmarks::kPowerBookmarkBackend)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-eol-notification-reset-dismissed-prefs",
     flag_descriptions::kEolResetDismissedPrefsName,
     flag_descriptions::kEolResetDismissedPrefsDescription, kOsCrOS,
     SINGLE_VALUE_TYPE(ash::switches::kEolResetDismissedPrefs)},
#endif

#if !BUILDFLAG(IS_ANDROID)
    {"enable-preferences-account-storage",
     flag_descriptions::kEnablePreferencesAccountStorageName,
     flag_descriptions::kEnablePreferencesAccountStorageDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(syncer::kEnablePreferencesAccountStorage)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-desk-button", flag_descriptions::kDeskButtonName,
     flag_descriptions::kDeskButtonDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDeskButton)},
    {"cros-focus-mode", flag_descriptions::kFocusModeName,
     flag_descriptions::kFocusModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFocusMode)},
    {"cros-focus-mode-ytm", flag_descriptions::kFocusModeYTMName,
     flag_descriptions::kFocusModeYTMDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFocusModeYTM)},
    {"render-arc-notifications-by-chrome",
     flag_descriptions::kRenderArcNotificationsByChromeName,
     flag_descriptions::kRenderArcNotificationsByChromeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kRenderArcNotificationsByChrome)},
#endif

#if !BUILDFLAG(IS_ANDROID)
    {"ios-promo-refreshed-password-bubble",
     flag_descriptions::kIOSPromoRefreshedPasswordBubbleName,
     flag_descriptions::kIOSPromoRefreshedPasswordBubbleDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kIOSPromoRefreshedPasswordBubble)},

    {"ios-promo-address-bubble", flag_descriptions::kIOSPromoAddressBubbleName,
     flag_descriptions::kIOSPromoAddressBubbleDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kIOSPromoAddressBubble)},

    {"ios-promo-payment-bubble", flag_descriptions::kIOSPromoPaymentBubbleName,
     flag_descriptions::kIOSPromoPaymentBubbleDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kIOSPromoPaymentBubble)},
#endif  // !BUILDFLAG(IS_ANDROID)

    {"enable-compression-dictionary-transport",
     flag_descriptions::kCompressionDictionaryTransportName,
     flag_descriptions::kCompressionDictionaryTransportDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kCompressionDictionaryTransport)},

    {"enable-compression-dictionary-transport-backend",
     flag_descriptions::kCompressionDictionaryTransportBackendName,
     flag_descriptions::kCompressionDictionaryTransportBackendDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         network::features::kCompressionDictionaryTransportBackend)},

    {"enable-compression-dictionary-transport-allow-http1",
     flag_descriptions::kCompressionDictionaryTransportOverHttp1Name,
     flag_descriptions::kCompressionDictionaryTransportOverHttp1Description,
     kOsAll,
     FEATURE_VALUE_TYPE(
         net::features::kCompressionDictionaryTransportOverHttp1)},

    {"enable-compression-dictionary-transport-allow-http2",
     flag_descriptions::kCompressionDictionaryTransportOverHttp2Name,
     flag_descriptions::kCompressionDictionaryTransportOverHttp2Description,
     kOsAll,
     FEATURE_VALUE_TYPE(
         net::features::kCompressionDictionaryTransportOverHttp2)},

    {"enable-compression-dictionary-transport-require-known-root-cert",
     flag_descriptions::kCompressionDictionaryTransportRequireKnownRootCertName,
     flag_descriptions::
         kCompressionDictionaryTransportRequireKnownRootCertDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         net::features::kCompressionDictionaryTransportRequireKnownRootCert)},

    {"enable-compute-pressure-rate-obfuscation-mitigation",
     flag_descriptions::kComputePressureRateObfuscationMitigationName,
     flag_descriptions::kComputePressureRateObfuscationMitigationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         blink::features::kComputePressureRateObfuscationMitigation)},

    {"enable-container-type-no-layout-containment",
     flag_descriptions::kContainerTypeNoLayoutContainmentName,
     flag_descriptions::kContainerTypeNoLayoutContainmentDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kContainerTypeNoLayoutContainment)},

    {"enable-compute-pressure-break-calibration-mitigation",
     flag_descriptions::kComputePressureBreakCalibrationMitigationName,
     flag_descriptions::kComputePressureBreakCalibrationMitigationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kComputePressureBreakCalibrationMitigation)},

    {"enable-shared-zstd", flag_descriptions::kSharedZstdName,
     flag_descriptions::kSharedZstdDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kSharedZstd)},

#if BUILDFLAG(IS_ANDROID)
    {"web-authentication-android-credential-management",
     flag_descriptions::kWebAuthnAndroidCredManName,
     flag_descriptions::kWebAuthnAndroidCredManDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(device::kWebAuthnAndroidCredMan,
                                    kWebAuthnAndroidCredManVariations,
                                    "WebAuthenticationAndroidCredMan")},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"android-extended-keyboard-shortcuts",
     flag_descriptions::kAndroidExtendedKeyboardShortcutsName,
     flag_descriptions::kAndroidExtendedKeyboardShortcutsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(blink::features::kAndroidExtendedKeyboardShortcuts)},
    {"convert-trackpad-events-to-mouse",
     flag_descriptions::kConvertTrackpadEventsToMouseName,
     flag_descriptions::kConvertTrackpadEventsToMouseDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(ui::kConvertTrackpadEventsToMouse)},
    {"deprecated-external-picker-function",
     flag_descriptions::kDeprecatedExternalPickerFunctionName,
     flag_descriptions::kDeprecatedExternalPickerFunctionDescription,
     kOsAndroid, FEATURE_VALUE_TYPE(ui::kDeprecatedExternalPickerFunction)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-missive-storage-config", flag_descriptions::kMissiveStorageName,
     flag_descriptions::kMissiveStorageDescription, kOsCrOS,
     PLATFORM_FEATURE_WITH_PARAMS_VALUE_TYPE(
         "CrOSLateBootMissiveStorage",
         kCrOSLateBootMissiveStorageDefaultVariations,
         "CrOSLateBootMissiveStorage")},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if !BUILDFLAG(IS_ANDROID)
    {"cast-mirroring-target-playout-delay",
     flag_descriptions::kCastMirroringTargetPlayoutDelayName,
     flag_descriptions::kCastMirroringTargetPlayoutDelayDescription, kOsDesktop,
     MULTI_VALUE_TYPE(kCastMirroringTargetPlayoutDelayChoices)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"separate-web-app-shortcut-badge-icon",
     flag_descriptions::kSeparateWebAppShortcutBadgeIconName,
     flag_descriptions::kSeparateWebAppShortcutBadgeIconDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSeparateWebAppShortcutBadgeIcon)},
    {"enable-audio-focus-enforcement",
     flag_descriptions::kEnableAudioFocusEnforcementName,
     flag_descriptions::kEnableAudioFocusEnforcementDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(media_session::features::kAudioFocusEnforcement)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"enable-process-per-site-up-to-main-frame-threshold",
     flag_descriptions::kEnableProcessPerSiteUpToMainFrameThresholdName,
     flag_descriptions::kEnableProcessPerSiteUpToMainFrameThresholdDescription,
=======
#if defined(OS_WIN) || (defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)) || \
    defined(OS_MAC) || (defined(OS_ANDROID))
    {"omnibox-updated-connection-security-indicators",
     flag_descriptions::kOmniboxUpdatedConnectionSecurityIndicatorsName,
     flag_descriptions::kOmniboxUpdatedConnectionSecurityIndicatorsDescription,
>>>>>>> chromium
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kUpdatedConnectionSecurityIndicators)},
#endif

#if defined(OS_ANDROID)
    {"share-usage-ranking", flag_descriptions::kShareUsageRankingName,
     flag_descriptions::kShareUsageRankingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kShareUsageRanking)},
#endif

<<<<<<< HEAD
    {"site-instance-groups-for-data-urls",
     flag_descriptions::kSiteInstanceGroupsForDataUrlsName,
     flag_descriptions::kSiteInstanceGroupsForDataUrlsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kSiteInstanceGroupsForDataUrls)},

    {"default-site-instance-groups",
     flag_descriptions::kDefaultSiteInstanceGroupsName,
     flag_descriptions::kDefaultSiteInstanceGroupsDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kDefaultSiteInstanceGroups)},

#if BUILDFLAG(ENABLE_EXTENSIONS)
    {"cws-info-fast-check", flag_descriptions::kCWSInfoFastCheckName,
     flag_descriptions::kCWSInfoFastCheckDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(extensions::kCWSInfoFastCheck)},

    {"extension-disable-unsupported-developer-mode-extensions",
     flag_descriptions::kExtensionDisableUnsupportedDeveloperName,
     flag_descriptions::kExtensionDisableUnsupportedDeveloperDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         extensions_features::kExtensionDisableUnsupportedDeveloper)},

    {"extension-telemetry-for-enterprise",
     flag_descriptions::kExtensionTelemetryForEnterpriseName,
     flag_descriptions::kExtensionTelemetryForEnterpriseDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         safe_browsing::kExtensionTelemetryForEnterprise,
         kExtensionTelemetryEnterpriseReportingIntervalSecondsVariations,
         "EnterpriseReportingIntervalSeconds")},
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)

    {"autofill-enable-cvc-storage-and-filling",
     flag_descriptions::kAutofillEnableCvcStorageAndFillingName,
     flag_descriptions::kAutofillEnableCvcStorageAndFillingDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableCvcStorageAndFilling)},

#if BUILDFLAG(IS_CHROMEOS)
    {"drive-fs-show-cse-files", flag_descriptions::kDriveFsShowCSEFilesName,
     flag_descriptions::kDriveFsShowCSEFilesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDriveFsShowCSEFiles)},
    {"drive-fs-mirroring", flag_descriptions::kDriveFsMirroringName,
     flag_descriptions::kDriveFsShowCSEFilesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDriveFsMirroring)},
    {"cros-labs-continuous-overview-animation",
     flag_descriptions::kContinuousOverviewScrollAnimationName,
     flag_descriptions::kContinuousOverviewScrollAnimationDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kContinuousOverviewScrollAnimation)},
    {"cros-labs-window-splitting", flag_descriptions::kWindowSplittingName,
     flag_descriptions::kWindowSplittingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kWindowSplitting)},
    {"cros-labs-tiling-window-resize",
     flag_descriptions::kTilingWindowResizeName,
     flag_descriptions::kTilingWindowResizeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kTilingWindowResize)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"privacy-sandbox-enrollment-overrides",
     flag_descriptions::kPrivacySandboxEnrollmentOverridesName,
     flag_descriptions::kPrivacySandboxEnrollmentOverridesDescription, kOsAll,
     ORIGIN_LIST_VALUE_TYPE(privacy_sandbox::kPrivacySandboxEnrollmentOverrides,
                            "")},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-smart-card-web-api", flag_descriptions::kSmartCardWebApiName,
     flag_descriptions::kSmartCardWebApiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(blink::features::kSmartCard)},
    {"enable-web-printing-api", flag_descriptions::kWebPrintingApiName,
     flag_descriptions::kWebPrintingApiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(blink::features::kWebPrinting)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"autofill-enable-prefetching-risk-data-for-retrieval",
     flag_descriptions::kAutofillEnablePrefetchingRiskDataForRetrievalName,
     flag_descriptions::
         kAutofillEnablePrefetchingRiskDataForRetrievalDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnablePrefetchingRiskDataForRetrieval)},

#if BUILDFLAG(IS_ANDROID)
    {"read-aloud", flag_descriptions::kReadAloudName,
     flag_descriptions::kReadAloudDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kReadAloud)},

    {"read-aloud-background-playback",
     flag_descriptions::kReadAloudBackgroundPlaybackName,
     flag_descriptions::kReadAloudBackgroundPlaybackDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kReadAloudBackgroundPlayback)},

    {"read-aloud-in-cct", flag_descriptions::kReadAloudInCCTName,
     flag_descriptions::kReadAloudInCCTDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kReadAloudInOverflowMenuInCCT)},

    {"read-aloud-tap-to-seek", flag_descriptions::kReadAloudTapToSeekName,
     flag_descriptions::kReadAloudTapToSeekDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kReadAloudTapToSeek)},
#endif

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
    {"third-party-profile-management",
     flag_descriptions::kThirdPartyProfileManagementName,
     flag_descriptions::kThirdPartyProfileManagementDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(
         profile_management::features::kThirdPartyProfileManagement)},

    {"oidc-auth-profile-management",
     flag_descriptions::kOidcAuthProfileManagementName,
     flag_descriptions::kOidcAuthProfileManagementDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(
         profile_management::features::kOidcAuthProfileManagement)},

    {"explicit-browser-signin-ui-on-desktop",
     flag_descriptions::kExplicitBrowserSigninUIOnDesktopName,
     flag_descriptions::kExplicitBrowserSigninUIOnDesktopDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(switches::kExplicitBrowserSigninUIOnDesktop)},

    {"enable-generic-oidc-auth-profile-management",
     flag_descriptions::kEnableGenericOidcAuthProfileManagementName,
     flag_descriptions::kEnableGenericOidcAuthProfileManagementDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(profile_management::features::
                            kEnableGenericOidcAuthProfileManagement)},
    {"enable-user-link-capturing-scope-extensions-pwa",
     flag_descriptions::kDesktopPWAsUserLinkCapturingScopeExtensionsName,
     flag_descriptions::kDesktopPWAsUserLinkCapturingScopeExtensionsDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(features::kPwaNavigationCapturingWithScopeExtensions)},
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN) || \
    BUILDFLAG(IS_CHROMEOS)
    {"enable-user-navigation-capturing-pwa",
     flag_descriptions::kPwaNavigationCapturingName,
     flag_descriptions::kPwaNavigationCapturingDescription,
     kOsLinux | kOsMac | kOsWin | kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kPwaNavigationCapturing,
                                    kPwaNavigationCapturingVariations,
                                    "PwaNavigationCapturing")},
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN) ||
        // BUILDFLAG(IS_CHROMEOS)

    {"ip-protection-proxy-opt-out",
     flag_descriptions::kIpProtectionProxyOptOutName,
     flag_descriptions::kIpProtectionProxyOptOutDescription, kOsAll,
     MULTI_VALUE_TYPE(kIpProtectionProxyOptOutChoices)},

    {"protected-audience-debug-token",
     flag_descriptions::kProtectedAudiencesConsentedDebugTokenName,
     flag_descriptions::kProtectedAudiencesConsentedDebugTokenDescription,
     kOsAll,
     STRING_VALUE_TYPE(switches::kProtectedAudiencesConsentedDebugToken, "")},

    {"deprecate-unload", flag_descriptions::kDeprecateUnloadName,
     flag_descriptions::kDeprecateUnloadDescription, kOsAll | kDeprecated,
     FEATURE_VALUE_TYPE(blink::features::kDeprecateUnload)},

    {"autofill-enable-fpan-risk-based-authentication",
     flag_descriptions::kAutofillEnableFpanRiskBasedAuthenticationName,
     flag_descriptions::kAutofillEnableFpanRiskBasedAuthenticationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableFpanRiskBasedAuthentication)},

    {"draw-immediately-when-interactive",
     flag_descriptions::kDrawImmediatelyWhenInteractiveName,
     flag_descriptions::kDrawImmediatelyWhenInteractiveDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kDrawImmediatelyWhenInteractive)},

    {"ack-on-surface-activation-when-interactive",
     flag_descriptions::kAckOnSurfaceActivationWhenInteractiveName,
     flag_descriptions::kAckOnSurfaceActivationWhenInteractiveDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(features::kAckOnSurfaceActivationWhenInteractive)},

#if BUILDFLAG(IS_MAC)
    {"enable-mac-pwas-notification-attribution",
     flag_descriptions::kMacPWAsNotificationAttributionName,
     flag_descriptions::kMacPWAsNotificationAttributionDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kAppShimNotificationAttribution)},

    {"use-adhoc-signing-for-web-app-shims",
     flag_descriptions::kUseAdHocSigningForWebAppShimsName,
     flag_descriptions::kUseAdHocSigningForWebAppShimsDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kUseAdHocSigningForWebAppShims)},
#endif  // BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_CHROMEOS)
    {"seal-key", flag_descriptions::kSealKeyName,
     flag_descriptions::kSealKeyDescription, kOsCrOS,
     STRING_VALUE_TYPE(ash::switches::kSealKey, "")},
#endif

    {"enable-manta-service", flag_descriptions::kEnableMantaServiceName,
     flag_descriptions::kEnableMantaServiceDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(manta::features::kMantaService)},

#if !BUILDFLAG(IS_ANDROID) && BUILDFLAG(GOOGLE_CHROME_BRANDING)
    {"esb-download-row-promo",
     flag_descriptions::kEsbDownloadRowPromoFeatureName,
     flag_descriptions::kEsbDownloadRowPromoFeatureDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(feature_engagement::kEsbDownloadRowPromoFeature)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_HLS_DEMUXER)
    {"enable-builtin-hls", flag_descriptions::kEnableBuiltinHlsName,
     flag_descriptions::kEnableBuiltinHlsDescription, kOsAll,
     FEATURE_VALUE_TYPE(media::kBuiltInHlsPlayer)},
#endif

#if !BUILDFLAG(IS_CHROMEOS)
    {"profiles-reordering", flag_descriptions::kProfilesReorderingName,
     flag_descriptions::kProfilesReorderingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(kProfilesReordering)},
#endif

    {"profile-picker-glic-testing",
     flag_descriptions::kProfilePickerGlicTesting,
     flag_descriptions::kProfilePickerGlicTestingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(switches::kProfilePickerGlicTesting)},

#if BUILDFLAG(ENABLE_DICE_SUPPORT)
    {"batch-upload-desktop", flag_descriptions::kBatchUploadDesktopName,
     flag_descriptions::kBatchUploadDesktopDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(switches::kBatchUploadDesktop)},
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"flex-firmware-update", flag_descriptions::kFlexFirmwareUpdateName,
     flag_descriptions::kFlexFirmwareUpdateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kFlexFirmwareUpdate)},

    {"enable-vpn-apps-on-flex", flag_descriptions::kVpnAppsOnFlexName,
     flag_descriptions::kVpnAppsOnFlexDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kVpnAppsOnFlex)},

    {"ipp-first-setup-for-usb-printers",
     flag_descriptions::kIppFirstSetupForUsbPrintersName,
     flag_descriptions::kIppFirstSetupForUsbPrintersDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kIppFirstSetupForUsbPrinters)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)
    {"enable-bound-session-credentials",
     flag_descriptions::kEnableBoundSessionCredentialsName,
     flag_descriptions::kEnableBoundSessionCredentialsDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_WITH_PARAMS_VALUE_TYPE(switches::kEnableBoundSessionCredentials,
                                    kEnableBoundSessionCredentialsVariations,
                                    "EnableBoundSessionCredentials")},
    {"enable-bound-session-credentials-software-keys-for-manual-testing",
     flag_descriptions::
         kEnableBoundSessionCredentialsSoftwareKeysForManualTestingName,
     flag_descriptions::
         kEnableBoundSessionCredentialsSoftwareKeysForManualTestingDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(
         unexportable_keys::
             kEnableBoundSessionCredentialsSoftwareKeysForManualTesting)},
#endif  // BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-soul", flag_descriptions::kCrosSoulName,
     flag_descriptions::kCrosSoulDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootCrOSSOUL")},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"observable-api", flag_descriptions::kObservableAPIName,
     flag_descriptions::kObservableAPIDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kObservableAPI)},

    {"atomic-move", flag_descriptions::kAtomicMoveAPIName,
     flag_descriptions::kAtomicMoveAPIDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kAtomicMoveAPI)},

#if BUILDFLAG(IS_ANDROID)
    {"android-hub-search", flag_descriptions::kAndroidHubSearchName,
     flag_descriptions::kAndroidHubSearchDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kAndroidHubSearch,
                                    kAndroidHubSearchVariations,
                                    "AndroidHubSearch")},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)
    {"enable-web-app-system-media-controls",
     flag_descriptions::kWebAppSystemMediaControlsName,
     flag_descriptions::kWebAppSystemMediaControlsDescription, kOsWin | kOsMac,
     FEATURE_VALUE_TYPE(features::kWebAppSystemMediaControls)},
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)

#if BUILDFLAG(ENABLE_COMPOSE)
    {flag_descriptions::kComposeId, flag_descriptions::kComposeName,
     flag_descriptions::kComposeDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_VALUE_TYPE(compose::features::kEnableCompose)},

    {"compose-proactive-nudge", flag_descriptions::kComposeProactiveNudgeName,
     flag_descriptions::kComposeProactiveNudgeDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         compose::features::kEnableComposeProactiveNudge,
         kComposeProactiveNudgeVariations,
         "ComposeProactiveNudge")},

    {"compose-nudge-display-at-cursor",
     flag_descriptions::kComposeNudgeAtCursorName,
     flag_descriptions::kComposeNudgeAtCursorDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_VALUE_TYPE(compose::features::kEnableComposeNudgeAtCursor)},

    {"compose-polite-nudge", flag_descriptions::kComposePoliteNudgeName,
     flag_descriptions::kComposePoliteNudgeDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_VALUE_TYPE(autofill::features::kComposePopupAnnouncePolitely)},

    {"compose-segmentation-promotion",
     flag_descriptions::kComposeSegmentationPromotionName,
     flag_descriptions::kComposeSegmentationPromotionDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_VALUE_TYPE(segmentation_platform::features::
                            kSegmentationPlatformComposePromotion)},

    {"compose-selection-nudge", flag_descriptions::kComposeSelectionNudgeName,
     flag_descriptions::kComposeSelectionNudgeDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         compose::features::kEnableComposeSelectionNudge,
         kComposeSelectionNudgeVariations,
         "ComposeSelectionNudge")},

    {"compose-upfront-input-modes",
     flag_descriptions::kComposeUpfrontInputModesName,
     flag_descriptions::kComposeUpfrontInputModesDescription,
     kOsWin | kOsLinux | kOsMac | kOsCrOS,
     FEATURE_VALUE_TYPE(compose::features::kComposeUpfrontInputModes)},
#endif

    {"related-website-sets-permission-grants",
     flag_descriptions::kShowRelatedWebsiteSetsPermissionGrantsName,
     flag_descriptions::kShowRelatedWebsiteSetsPermissionGrantsDescription,
     kOsDesktop | kOsAndroid,
     FEATURE_VALUE_TYPE(
         permissions::features::kShowRelatedWebsiteSetsPermissionGrants)},

#if BUILDFLAG(IS_CHROMEOS)
    {"coral-feature-key", flag_descriptions::kCoralFeatureKeyName,
     flag_descriptions::kCoralFeatureKeyDescription, kOsCrOS,
     STRING_VALUE_TYPE(ash::switches::kCoralFeatureKey, "")},

    {"cros-switcher", flag_descriptions::kCrosSwitcherName,
     flag_descriptions::kCrosSwitcherDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kCrosSwitcher)},
    {"platform-keys-changes-wave-1",
     flag_descriptions::kPlatformKeysChangesWave1Name,
     flag_descriptions::kPlatformKeysChangesWave1Description, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kPlatformKeysChangesWave1)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"autofill-enable-save-card-loading-and-confirmation",
     flag_descriptions::kAutofillEnableSaveCardLoadingAndConfirmationName,
     flag_descriptions::
         kAutofillEnableSaveCardLoadingAndConfirmationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableSaveCardLoadingAndConfirmation)},

    {"autofill-enable-vcn-enroll-loading-and-confirmation",
     flag_descriptions::kAutofillEnableVcnEnrollLoadingAndConfirmationName,
     flag_descriptions::
         kAutofillEnableVcnEnrollLoadingAndConfirmationDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableVcnEnrollLoadingAndConfirmation)},

#if BUILDFLAG(IS_ANDROID)
    {"boarding-pass-detector", flag_descriptions::kBoardingPassDetectorName,
     flag_descriptions::kBoardingPassDetectorDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kBoardingPassDetector,
                                    kBoardingPassDetectorVariations,
                                    "Allowed Urls")},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"cloud-gaming-device", flag_descriptions::kCloudGamingDeviceName,
     flag_descriptions::kCloudGamingDeviceDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCloudGamingDevice)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"content-settings-partitioning",
     flag_descriptions::kContentSettingsPartitioningName,
     flag_descriptions::kContentSettingsPartitioningDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         content_settings::features::kContentSettingsPartitioning)},

#if BUILDFLAG(IS_ANDROID)
    {"use-fullscreen-insets-api",
     flag_descriptions::kFullscreenInsetsApiMigrationName,
     flag_descriptions::kFullscreenInsetsApiMigrationDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kFullscreenInsetsApiMigration)},

    {"use-fullscreen-insets-api-on-automotive",
     flag_descriptions::kFullscreenInsetsApiMigrationOnAutomotiveName,
     flag_descriptions::kFullscreenInsetsApiMigrationOnAutomotiveDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kFullscreenInsetsApiMigrationOnAutomotive)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_MAC)
    {"enable-mac-ime-live-conversion-fix",
     flag_descriptions::kMacImeLiveConversionFixName,
     flag_descriptions::kMacImeLiveConversionFixDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kMacImeLiveConversionFix)},
#endif

    {"tear-off-web-app-tab-opens-web-app-window",
     flag_descriptions::kTearOffWebAppAppTabOpensWebAppWindowName,
     flag_descriptions::kTearOffWebAppAppTabOpensWebAppWindowDescription,
     kOsAll, FEATURE_VALUE_TYPE(features::kTearOffWebAppTabOpensWebAppWindow)},

#if BUILDFLAG(IS_ANDROID)
    {"offline-auto-fetch", flag_descriptions::kOfflineAutoFetchName,
     flag_descriptions::kOfflineAutoFetchDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kOfflineAutoFetch)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {kAssistantIphInternalName, flag_descriptions::kAssistantIphName,
     flag_descriptions::kAssistantIphDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(feature_engagement::kIPHLauncherSearchHelpUiFeature)},

    {"battery-badge-icon", flag_descriptions::kBatteryBadgeIconName,
     flag_descriptions::kBatteryBadgeIconDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kBatteryBadgeIcon)},

    {"bluetooth-wifi-qs-pod-refresh",
     flag_descriptions::kBluetoothWifiQSPodRefreshName,
     flag_descriptions::kBluetoothWifiQSPodRefreshDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kBluetoothWifiQSPodRefresh)},

    {"mahi", flag_descriptions::kMahiName, flag_descriptions::kMahiDescription,
     kOsCrOS, FEATURE_VALUE_TYPE(chromeos::features::kMahi)},

    {"mahi-debugging", flag_descriptions::kMahiDebuggingName,
     flag_descriptions::kMahiDebuggingDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kMahiDebugging)},

    {"mahi-panel-resizable", flag_descriptions::kMahiPanelResizableName,
     flag_descriptions::kMahiPanelResizableDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kMahiPanelResizable)},

    {"notification-width-increase",
     flag_descriptions::kNotificationWidthIncreaseName,
     flag_descriptions::kNotificationWidthIncreaseDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kNotificationWidthIncrease)},

    {"pompano", flag_descriptions::kPompanoName,
     flag_descriptions::kPompanoDescritpion, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kPompano)},

    {"mahi-summarize-selected", flag_descriptions::kMahiSummarizeSelectedName,
     flag_descriptions::kMahiSummarizeSelectedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kMahiSummarizeSelected)},

    {"ash-picker-gifs", flag_descriptions::kAshPickerGifsName,
     flag_descriptions::kAshPickerGifsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kPickerGifs)},

    {"ash-modifier-split", flag_descriptions::kAshModifierSplitName,
     flag_descriptions::kAshModifierSplitDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kModifierSplit)},

    {"ash-split-keyboard-refactor",
     flag_descriptions::kAshSplitKeyboardRefactorName,
     flag_descriptions::kAshSplitKeyboardRefactorDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kSplitKeyboardRefactor)},

    {"enable-toggle-camera-shortcut",
     flag_descriptions::kEnableToggleCameraShortcutName,
     flag_descriptions::kEnableToggleCameraShortcutDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kEnableToggleCameraShortcut)},

    {"ash-null-top-row-fix", flag_descriptions::kAshNullTopRowFixName,
     flag_descriptions::kAshNullTopRowFixDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kNullTopRowFix)},

#endif  // BUILDFLAG(IS_CHROMEOS)

#if !BUILDFLAG(IS_ANDROID)
    {"password-manual-fallback-available",
     flag_descriptions::kPasswordManualFallbackAvailableName,
     flag_descriptions::kPasswordManualFallbackAvailableDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(
         password_manager::features::kPasswordManualFallbackAvailable)},
#endif  // !BUILDFLAG(IS_ANDROID)

    {"enable-unrestricted-usb", flag_descriptions::kEnableUnrestrictedUsbName,
     flag_descriptions::kEnableUnrestrictedUsbDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kUnrestrictedUsb)},

    {"autofill-enable-vcn-3ds-authentication",
     flag_descriptions::kAutofillEnableVcn3dsAuthenticationName,
     flag_descriptions::kAutofillEnableVcn3dsAuthenticationDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableVcn3dsAuthentication)},

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-locked-mode", flag_descriptions::kLockedModeName,
     flag_descriptions::kLockedModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(blink::features::kLockedMode)},
#endif  // BUILDFLAG_(IS_CHROMEOS)

#if !BUILDFLAG(IS_ANDROID)
    {"link-preview", flag_descriptions::kLinkPreviewName,
     flag_descriptions::kLinkPreviewDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kLinkPreview,
                                    kLinkPreviewTriggerTypeVariations,
                                    "LinkPreview")},
#endif  // !BUILDFLAG_(IS_ANDROID)

    {"send-tab-ios-push-notifications",
     flag_descriptions::kSendTabToSelfIOSPushNotificationsName,
     flag_descriptions::kSendTabToSelfIOSPushNotificationsDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         send_tab_to_self::kSendTabToSelfIOSPushNotifications,
         kSendTabIOSPushNotificationsVariations,
         "SendTabToSelfIOSPushNotifications")},

#if BUILDFLAG(IS_CHROMEOS)
    {"desk-profiles", flag_descriptions::kDeskProfilesName,
     flag_descriptions::kDeskProfilesDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kDeskProfiles)},
    {"enable-display-performance-mode",
     flag_descriptions::kEnableDisplayPerformanceModeName,
     flag_descriptions::kEnableDisplayPerformanceModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kDisplayPerformanceMode)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
    {"android-tab-declutter", flag_descriptions::kAndroidTabDeclutterName,
     flag_descriptions::kAndroidTabDeclutterDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAndroidTabDeclutter)},

    {"android-tab-declutter-archive-all-but-active-tab",
     flag_descriptions::kAndroidTabDeclutterArchiveAllButActiveTabName,
     flag_descriptions::kAndroidTabDeclutterArchiveAllButActiveTabDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kAndroidTabDeclutterArchiveAllButActiveTab)},

    {"android-tab-declutter-archive-duplicate-tabs",
     flag_descriptions::kAndroidTabDeclutterArchiveDuplicateTabsName,
     flag_descriptions::kAndroidTabDeclutterArchiveDuplicateTabsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kAndroidTabDeclutterArchiveDuplicateTabs)},

    {"force-list-tab-switcher", flag_descriptions::kForceListTabSwitcherName,
     flag_descriptions::kForceListTabSwitcherDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kForceListTabSwitcher)},

    {"tab-switcher-full-new-tab-button",
     flag_descriptions::kTabSwitcherFullNewTabButtonName,
     flag_descriptions::kTabSwitcherFullNewTabButtonDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kTabSwitcherFullNewTabButton)},

    {"tab-group-sync-android", flag_descriptions::kTabGroupSyncAndroidName,
     flag_descriptions::kTabGroupSyncAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(tab_groups::kTabGroupSyncAndroid)},

    {"tab-group-sync-disable-network-layer",
     flag_descriptions::kTabGroupSyncDisableNetworkLayerName,
     flag_descriptions::kTabGroupSyncDisableNetworkLayerDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(tab_groups::kTabGroupSyncDisableNetworkLayer)},

    {"history-pane-android", flag_descriptions::kHistoryPaneAndroidName,
     flag_descriptions::kHistoryPaneAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kHistoryPaneAndroid)},

    {"bookmark-pane-android", flag_descriptions::kBookmarkPaneAndroidName,
     flag_descriptions::kBookmarkPaneAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kBookmarkPaneAndroid)},

#endif  // BUILDFLAG(IS_ANDROID)

    {"autofill-shared-storage-server-card-data",
     flag_descriptions::kAutofillSharedStorageServerCardDataName,
     flag_descriptions::kAutofillSharedStorageServerCardDataDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillSharedStorageServerCardData)},

#if BUILDFLAG(IS_ANDROID)
    {"android-open-pdf-inline", flag_descriptions::kAndroidOpenPdfInlineName,
     flag_descriptions::kAndroidOpenPdfInlineDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAndroidOpenPdfInline)},

    {"android-open-pdf-inline-backport",
     flag_descriptions::kAndroidOpenPdfInlineBackportName,
     flag_descriptions::kAndroidOpenPdfInlineBackportDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAndroidOpenPdfInlineBackport)},

    {"android-pdf-assist-content",
     flag_descriptions::kAndroidPdfAssistContentName,
     flag_descriptions::kAndroidPdfAssistContentDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAndroidPdfAssistContent)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"page-info-sharing", flag_descriptions::kChromePageInfoSharingName,
     flag_descriptions::kChromePageInfoSharingDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kChromeSharePageInfo)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"multi-calendar-in-quick-settings",
     flag_descriptions::kMultiCalendarSupportName,
     flag_descriptions::kMultiCalendarSupportDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kMultiCalendarSupport)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
    {"autofill-enable-syncing-of-pix-bank-accounts",
     flag_descriptions::kAutofillEnableSyncingOfPixBankAccountsName,
     flag_descriptions::kAutofillEnableSyncingOfPixBankAccountsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableSyncingOfPixBankAccounts)},

    {"enable-pix-payments", flag_descriptions::kEnablePixPaymentsName,
     flag_descriptions::kEnablePixPaymentsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(payments::facilitated::kEnablePixPayments)},

    {"enable-pix-payments-in-landscape-mode",
     flag_descriptions::kEnablePixPaymentsInLandscapeModeName,
     flag_descriptions::kEnablePixPaymentsInLandscapeModeDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         payments::facilitated::kEnablePixPaymentsInLandscapeMode)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"autofill-enable-card-benefits-for-american-express",
     flag_descriptions::kAutofillEnableCardBenefitsForAmericanExpressName,
     flag_descriptions::
         kAutofillEnableCardBenefitsForAmericanExpressDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableCardBenefitsForAmericanExpress)},

    {"autofill-enable-card-benefits-sync",
     flag_descriptions::kAutofillEnableCardBenefitsSyncName,
     flag_descriptions::kAutofillEnableCardBenefitsSyncDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableCardBenefitsSync)},

    {"linked-services-setting", flag_descriptions::kLinkedServicesSettingName,
     flag_descriptions::kLinkedServicesSettingDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kLinkedServicesSetting)},

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-mall", flag_descriptions::kCrosMallName,
     flag_descriptions::kCrosMallDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrosMall)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"autofill-enable-vcn-gray-out-for-merchant-opt-out",
     flag_descriptions::kAutofillEnableVcnGrayOutForMerchantOptOutName,
     flag_descriptions::kAutofillEnableVcnGrayOutForMerchantOptOutDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableVcnGrayOutForMerchantOptOut)},

#if BUILDFLAG(IS_MAC)
    {"reduce-ip-address-change-notification",
     flag_descriptions::kReduceIPAddressChangeNotificationName,
     flag_descriptions::kReduceIPAddressChangeNotificationDescription, kOsMac,
     FEATURE_VALUE_TYPE(net::features::kReduceIPAddressChangeNotification)},
#endif  // BUILDFLAG(IS_MAC)

    {"autofill-enable-save-card-local-save-fallback",
     flag_descriptions::kAutofillEnableSaveCardLocalSaveFallbackName,
     flag_descriptions::kAutofillEnableSaveCardLocalSaveFallbackDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableSaveCardLocalSaveFallback)},

    {"enable-fingerprinting-protection-blocklist",
     flag_descriptions::kEnableFingerprintingProtectionBlocklistName,
     flag_descriptions::kEnableFingerprintingProtectionBlocklistDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         fingerprinting_protection_filter::features::
             kEnableFingerprintingProtectionFilter,
         kEnableFingerprintingProtectionFilterVariations,
         "EnableFingerprintingProtectionFilter")},

    {"enable-fingerprinting-protection-blocklist-incognito",
     flag_descriptions::kEnableFingerprintingProtectionBlocklistInIncognitoName,
     flag_descriptions::
         kEnableFingerprintingProtectionBlocklistInIncognitoDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         fingerprinting_protection_filter::features::
             kEnableFingerprintingProtectionFilterInIncognito,
         kEnableFingerprintingProtectionFilterInIncognitoVariations,
         "EnableFingerprintingProtectionFilterInIncognito")},

#if BUILDFLAG(IS_CHROMEOS)
    {"ash-forest-feature", flag_descriptions::kForestFeatureName,
     flag_descriptions::kForestFeatureDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kForestFeature)},
    {"birch-weather", flag_descriptions::kBirchWeatherName,
     flag_descriptions::kBirchWeatherDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kBirchWeather)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"enable-standard-device-bound-session-credentials",
     flag_descriptions::kEnableStandardBoundSessionCredentialsName,
     flag_descriptions::kEnableStandardBoundSessionCredentialsDescription,
     kOsWin, FEATURE_VALUE_TYPE(net::features::kDeviceBoundSessions)},
    {"enable-standard-device-bound-session-persistence",
     flag_descriptions::kEnableStandardBoundSessionPersistenceName,
     flag_descriptions::kEnableStandardBoundSessionPersistenceDescription,
     kOsWin, FEATURE_VALUE_TYPE(net::features::kPersistDeviceBoundSessions)},

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-soul-gd", flag_descriptions::kCrosSoulGravediggerName,
     flag_descriptions::kCrosSoulGravediggerDescription, kOsCrOS,
     PLATFORM_FEATURE_NAME_TYPE("CrOSLateBootGravedigger")},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"clear-undecryptable-passwords",
     flag_descriptions::kClearUndecryptablePasswordsName,
     flag_descriptions::kClearUndecryptablePasswordsDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         password_manager::features::kClearUndecryptablePasswords)},

#if BUILDFLAG(IS_ANDROID)
    {"replace-sync-promos-with-sign-in-promos",
     flag_descriptions::kReplaceSyncPromosWithSignInPromosName,
     flag_descriptions::kReplaceSyncPromosWithSignInPromosDescription,
     kOsAndroid, MULTI_VALUE_TYPE(kReplaceSyncPromosWithSignInPromosChoices)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"autofill-enable-verve-card-support",
     flag_descriptions::kAutofillEnableVerveCardSupportName,
     flag_descriptions::kAutofillEnableVerveCardSupportDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableVerveCardSupport)},

#if BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)
    {"cert-management-v2-ui", flag_descriptions::kEnableCertManagementV2UIName,
     flag_descriptions::kEnableCertManagementV2UIDescription,
     kOsLinux | kOsMac | kOsWin | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableCertManagementUIV2)},
    {"cert-management-v2-ui-write",
     flag_descriptions::kEnableCertManagementV2UIWriteName,
     flag_descriptions::kEnableCertManagementV2UIWriteDescription,
     kOsLinux | kOsMac | kOsWin | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableCertManagementUIV2Write)},
    {"cert-management-v2-ui-edit-certs",
     flag_descriptions::kEnableCertManagementV2UIEditCertsName,
     flag_descriptions::kEnableCertManagementV2UIEditCertsDescription,
     kOsLinux | kOsMac | kOsWin | kOsCrOS,
     FEATURE_VALUE_TYPE(features::kEnableCertManagementUIV2EditCerts)},
#endif  // BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)

    {"password-leak-toggle-move",
     flag_descriptions::kPasswordLeakToggleMoveName,
     flag_descriptions::kPasswordLeakToggleMoveDescription, kOsAll,
     FEATURE_VALUE_TYPE(safe_browsing::kPasswordLeakToggleMove)},

    {"pwm-show-suggestions-on-autofocus",
     flag_descriptions::kPasswordManagerShowSuggestionsOnAutofocusName,
     flag_descriptions::kPasswordManagerShowSuggestionsOnAutofocusDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         password_manager::features::kShowSuggestionsOnAutofocus)},

#if BUILDFLAG(IS_ANDROID)
    {"fetch-gaia-hash-on-sign-in",
     flag_descriptions::kFetchGaiaHashOnSignInName,
     flag_descriptions::kFetchGaiaHashOnSignInDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(password_manager::features::kFetchGaiaHashOnSignIn)},

    {"android-browser-controls-in-viz",
     flag_descriptions::kAndroidBrowserControlsInVizName,
     flag_descriptions::kAndroidBrowserControlsInVizDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAndroidBrowserControlsInViz)},

    {"android-browser-controls-in-viz-bottom-controls",
     flag_descriptions::kAndroidBcivBottomControlsName,
     flag_descriptions::kAndroidBcivBottomControlsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kAndroidBcivBottomControls)},
#endif

    {"optimization-guide-enable-dogfood-logging",
     flag_descriptions::kOptimizationGuideEnableDogfoodLoggingName,
     flag_descriptions::kOptimizationGuideEnableDogfoodLoggingDescription,
     kOsAll,
     SINGLE_VALUE_TYPE(
         optimization_guide::switches::kEnableModelQualityDogfoodLogging)},

#if !BUILDFLAG(IS_ANDROID)
    {"hybrid-passkeys-in-context-menu",
     flag_descriptions::kWebAuthnUsePasskeyFromAnotherDeviceInContextMenuName,
     flag_descriptions::
         kWebAuthnUsePasskeyFromAnotherDeviceInContextMenuDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(password_manager::features::
                            kWebAuthnUsePasskeyFromAnotherDeviceInContextMenu)},
    {"web-authentication-enclave-authenticator",
     flag_descriptions::kWebAuthnEnclaveAuthenticatorName,
     flag_descriptions::kWebAuthnEnclaveAuthenticatorDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(device::kWebAuthnEnclaveAuthenticator,
                                    kWebAuthnEnclaveAuthenticatorVariations,
                                    "WebAuthenticationEnclaveAuthenticator")},
    {"web-authentication-passkey-upgrade",
     flag_descriptions::kWebAuthnPasskeyUpgradeName,
     flag_descriptions::kWebAuthnPasskeyUpgradeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(device::kWebAuthnPasskeyUpgrade)},
#endif

#if BUILDFLAG(IS_CHROMEOS)
    {"conch", flag_descriptions::kConchName,
     flag_descriptions::kConchDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kConch)},

    {"conch-system-audio-from-mic",
     flag_descriptions::kConchSystemAudioFromMicName,
     flag_descriptions::kConchSystemAudioFromMicDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kConchSystemAudioFromMic)},

    {"conch-expand-transcription-language",
     flag_descriptions::kConchExpandTranscriptionLanguageName,
     flag_descriptions::kConchExpandTranscriptionLanguageDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kConchExpandTranscriptionLanguage)},

    {"conch-gen-ai", flag_descriptions::kConchGenAiName,
     flag_descriptions::kConchGenAiDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kConchGenAi)},

    {"conch-large-model", flag_descriptions::kConchLargeModelName,
     flag_descriptions::kConchLargeModelDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ash::features::kConchLargeModel)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
    {"autofill-sync-ewallet-accounts",
     flag_descriptions::kAutofillSyncEwalletAccountsName,
     flag_descriptions::kAutofillSyncEwalletAccountsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillSyncEwalletAccounts)},

    {"ewallet-payments", flag_descriptions::kEwalletPaymentsName,
     flag_descriptions::kEwalletPaymentsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(payments::facilitated::kEwalletPayments)},

    {"payment-link-detection", flag_descriptions::kPaymentLinkDetectionName,
     flag_descriptions::kPaymentLinkDetectionDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(blink::features::kPaymentLinkDetection)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"screenlock-reauth", flag_descriptions::kScreenlockReauthCardName,
     flag_descriptions::kScreenlockReauthCardDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(password_manager::features::kBiometricsAuthForPwdFill)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"ruby-short-heuristics", flag_descriptions::kRubyShortHeuristicsName,
     flag_descriptions::kRubyShortHeuristicsDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kRubyShortHeuristics)},

#if BUILDFLAG(IS_ANDROID)
    {"pwm-access-loss-warning",
     flag_descriptions::
         kUnifiedPasswordManagerLocalPasswordsAndroidAccessLossWarningName,
     flag_descriptions::
         kUnifiedPasswordManagerLocalPasswordsAndroidAccessLossWarningDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         password_manager::features::
             kUnifiedPasswordManagerLocalPasswordsAndroidAccessLossWarning)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"prompt-api-for-gemini-nano",
     flag_descriptions::kPromptAPIForGeminiNanoName,
     flag_descriptions::kPromptAPIForGeminiNanoDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kAIPromptAPIForWebPlatform),
     flag_descriptions::kAIAPIsForGeminiNanoLinks},

    {"prompt-api-for-gemini-nano-multimodal-input",
     flag_descriptions::kPromptAPIForGeminiNanoMultimodalInputName,
     flag_descriptions::kPromptAPIForGeminiNanoMultimodalInputDescription,
     kOsAll, FEATURE_VALUE_TYPE(blink::features::kAIPromptAPIMultimodalInput),
     flag_descriptions::kAIAPIsForGeminiNanoLinks},

    {"summarization-api-for-gemini-nano",
     flag_descriptions::kSummarizationAPIForGeminiNanoName,
     flag_descriptions::kSummarizationAPIForGeminiNanoDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kAISummarizationAPI),
     flag_descriptions::kAIAPIsForGeminiNanoLinks},

    {"writer-api-for-gemini-nano",
     flag_descriptions::kWriterAPIForGeminiNanoName,
     flag_descriptions::kWriterAPIForGeminiNanoDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kAIWriterAPI),
     flag_descriptions::kAIAPIsForGeminiNanoLinks},

    {"rewriter-api-for-gemini-nano",
     flag_descriptions::kRewriterAPIForGeminiNanoName,
     flag_descriptions::kRewriterAPIForGeminiNanoDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kAIRewriterAPI),
     flag_descriptions::kAIAPIsForGeminiNanoLinks},

    {"text-box-trim", flag_descriptions::kCssTextBoxTrimName,
     flag_descriptions::kCssTextBoxTrimDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kCSSTextBoxTrim)},

    {"storage-access-headers", flag_descriptions::kStorageAccessHeadersName,
     flag_descriptions::kStorageAccessHeadersDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kStorageAccessHeaders)},

    {"storage-access-api-follows-same-origin-policy",
     flag_descriptions::kStorageAccessApiFollowsSameOriginPolicyName,
     flag_descriptions::kStorageAccessApiFollowsSameOriginPolicyDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         net::features::kStorageAccessApiFollowsSameOriginPolicy)},

    {"canvas-2d-hibernation", flag_descriptions::kCanvasHibernationName,
     flag_descriptions::kCanvasHibernationDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kCanvas2DHibernation)},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
    {"sync-enable-bookmarks-in-transport-mode",
     flag_descriptions::kSyncEnableBookmarksInTransportModeName,
     flag_descriptions::kSyncEnableBookmarksInTransportModeDescription,
     kOsWin | kOsMac | kOsLinux,
     FEATURE_VALUE_TYPE(syncer::kSyncEnableBookmarksInTransportMode)},
#endif

    {"visited-url-ranking-service-domain-deduplication",
     flag_descriptions::kVisitedURLRankingServiceDeduplicationName,
     flag_descriptions::kVisitedURLRankingServiceDeduplicationDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         visited_url_ranking::features::kVisitedURLRankingDeduplication,
         kVisitedURLRankingDomainDeduplicationVariations,
         "visited-url-ranking-service-domain-deduplication")},

    {"visited-url-ranking-service-history-visibility-score-filter",
     flag_descriptions::
         kVisitedURLRankingServiceHistoryVisibilityScoreFilterName,
     flag_descriptions::
         kVisitedURLRankingServiceHistoryVisibilityScoreFilterDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(visited_url_ranking::features::
                            kVisitedURLRankingHistoryVisibilityScoreFilter)},

    {"defer-renderer-tasks-after-input",
     flag_descriptions::kDeferRendererTasksAfterInputName,
     flag_descriptions::kDeferRendererTasksAfterInputDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         blink::features::kDeferRendererTasksAfterInput,
         kDeferRendererTasksAfterInputVariations,
         "DeferRendererTasksAfterInput")},

    {"threaded-scroll-prevent-rendering-starvation",
     flag_descriptions::kThreadedScrollPreventRenderingStarvationName,
     flag_descriptions::kThreadedScrollPreventRenderingStarvationDescription,
     kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         blink::features::kThreadedScrollPreventRenderingStarvation,
         kThreadedScrollPreventRenderingStarvationVariations,
         "ThreadedScrollPreventRenderingStarvation")},

    {"autofill-upload-card-request-timeout",
     flag_descriptions::kAutofillUploadCardRequestTimeoutName,
     flag_descriptions::kAutofillUploadCardRequestTimeoutDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         autofill::features::kAutofillUploadCardRequestTimeout,
         kAutofillUploadCardRequestTimeoutOptions,
         "AutofillUploadCardRequestTimeout")},

    {"autofill-vcn-enroll-request-timeout",
     flag_descriptions::kAutofillVcnEnrollRequestTimeoutName,
     flag_descriptions::kAutofillVcnEnrollRequestTimeoutDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         autofill::features::kAutofillVcnEnrollRequestTimeout,
         kAutofillVcnEnrollRequestTimeoutOptions,
         "AutofillVcnEnrollRequestTimeout")},

    {"autofill-unmask-card-request-timeout",
     flag_descriptions::kAutofillUnmaskCardRequestTimeoutName,
     flag_descriptions::kAutofillUnmaskCardRequestTimeoutDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillUnmaskCardRequestTimeout)},

#if !BUILDFLAG(IS_ANDROID)
    {"freezing-on-energy-saver", flag_descriptions::kFreezingOnEnergySaverName,
     flag_descriptions::kFreezingOnEnergySaverDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(
         performance_manager::features::kFreezingOnBatterySaver)},

    {"freezing-on-energy-saver-testing",
     flag_descriptions::kFreezingOnEnergySaverTestingName,
     flag_descriptions::kFreezingOnEnergySaverTestingDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(
         performance_manager::features::kFreezingOnBatterySaverForTesting)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_WIN)
    {"hid-get-feature-report-fix",
     flag_descriptions::kHidGetFeatureReportFixName,
     flag_descriptions::kHidGetFeatureReportFixDescription, kOsWin,
     FEATURE_VALUE_TYPE(features::kHidGetFeatureReportFix)},
#endif  // BUILDFLAG(IS_WIN)

#if !BUILDFLAG(IS_ANDROID)
    {"translate-open-settings", flag_descriptions::kTranslateOpenSettingsName,
     flag_descriptions::kTranslateOpenSettingsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(language::kTranslateOpenSettings)},
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
    {"tab-organization", flag_descriptions::kTabOrganizationName,
     flag_descriptions::kTabOrganizationDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabOrganization)},

    {"tab-organization-settings-visibility",
     flag_descriptions::kTabOrganizationSettingsVisibilityName,
     flag_descriptions::kTabOrganizationSettingsVisibilityDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(optimization_guide::features::internal::
                            kTabOrganizationSettingsVisibility)},

    {"tabstrip-declutter", flag_descriptions::kTabstripDeclutterName,
     flag_descriptions::kTabstripDeclutterDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kTabstripDeclutter,
                                    kTabstripDeclutterVariations,
                                    "TabstripDeclutter")},
    {"tabstrip-dedupe", flag_descriptions::kTabstripDedupeName,
     flag_descriptions::kTabstripDedupeDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTabstripDedupe)},
#endif

#if !BUILDFLAG(IS_ANDROID)
    {"autofill-remove-payments-butter-dropdown",
     flag_descriptions::kAutofillRemovePaymentsButterDropdownName,
     flag_descriptions::kAutofillRemovePaymentsButterDropdownDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillRemovePaymentsButterDropdown)},
#endif  // !BUILDFLAG(IS_ANDROID)

    {"language-detection-api", flag_descriptions::kLanguageDetectionAPIName,
     flag_descriptions::kLanguageDetectionAPIDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kLanguageDetectionAPI)},

#if BUILDFLAG(IS_ANDROID)
    {"history-opt-in-entry-points",
     flag_descriptions::kHistoryOptInEntryPointsName,
     flag_descriptions::kHistoryOptInEntryPointsDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(switches::kHistoryOptInEntryPoints)},

    {"supervised-force-signin-with-capabilities",
     flag_descriptions::kSupervisedUserForceSigninWithCapabilitiesName,
     flag_descriptions::kSupervisedUserForceSigninWithCapabilitiesDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(switches::kForceSupervisedSigninWithCapabilities)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_WIN)
    {"supervised-profile-safe-search",
     flag_descriptions::kSupervisedProfileSafeSearchName,
     flag_descriptions::kSupervisedProfileSafeSearchDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(
         supervised_user::kForceSafeSearchForUnauthenticatedSupervisedUsers)},

    {"supervised-profile-youtube-reauth",
     flag_descriptions::kSupervisedProfileReauthForYouTubeName,
     flag_descriptions::kSupervisedProfileReauthForYouTubeDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(
         supervised_user::kForceSupervisedUserReauthenticationForYouTube)},

    {"supervised-profile-filtering-fallback",
     flag_descriptions::kSupervisedProfileFilteringFallbackName,
     flag_descriptions::kSupervisedProfileFilteringFallbackDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(
         supervised_user::kUncredentialedFilteringFallbackForSupervisedUsers)},

    {"supervised-profile-custom-strings",
     flag_descriptions::kSupervisedProfileCustomStringsName,
     flag_descriptions::kSupervisedProfileCustomStringsDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(
         supervised_user::kCustomProfileStringsForSupervisedUsers)},

    {"supervised-profile-sign-in-iph",
     flag_descriptions::kSupervisedProfileSignInIphName,
     flag_descriptions::kSupervisedProfileSignInIphDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(
         feature_engagement::kIPHSupervisedUserProfileSigninFeature)},

    {"supervised-profile-kite-badging",
     flag_descriptions::kSupervisedProfileShowKiteBadgeName,
     flag_descriptions::kSupervisedProfileShowKiteBadgeDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(supervised_user::kShowKiteForSupervisedUsers)},

    {"supervised-user-local-web-approvals",
     flag_descriptions::kSupervisedUserLocalWebApprovalsName,
     flag_descriptions::kSupervisedUserLocalWebApprovalsDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_VALUE_TYPE(supervised_user::kLocalWebApprovals)},

#endif

    {"use-frame-interval-decider",
     flag_descriptions::kUseFrameIntervalDeciderName,
     flag_descriptions::kUseFrameIntervalDeciderDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kUseFrameIntervalDecider)},

#if BUILDFLAG(IS_ANDROID)
    {"sensitive-content", flag_descriptions::kSensitiveContentName,
     flag_descriptions::kSensitiveContentDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         sensitive_content::features::kSensitiveContent,
         kSensitiveContentVariations,
         "SensitiveContent")},

    {"sensitive-content-while-switching-tabs",
     flag_descriptions::kSensitiveContentWhileSwitchingTabsName,
     flag_descriptions::kSensitiveContentWhileSwitchingTabsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         sensitive_content::features::kSensitiveContentWhileSwitchingTabs)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"data-sharing", flag_descriptions::kDataSharingName,
     flag_descriptions::kDataSharingDescription, kOsAll,
     FEATURE_VALUE_TYPE(data_sharing::features::kDataSharingFeature)},

    {"data-sharing-join-only", flag_descriptions::kDataSharingJoinOnlyName,
     flag_descriptions::kDataSharingJoinOnlyDescription, kOsAll,
     FEATURE_VALUE_TYPE(data_sharing::features::kDataSharingJoinOnly)},

    {"history-sync-alternative-illustration",
     flag_descriptions::kHistorySyncAlternativeIllustrationName,
     flag_descriptions::kHistorySyncAlternativeIllustrationDescription, kOsAll,
     FEATURE_VALUE_TYPE(tab_groups::kUseAlternateHistorySyncIllustration)},

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-content-adjusted-refresh-rate",
     flag_descriptions::kCrosContentAdjustedRefreshRateName,
     flag_descriptions::kCrosContentAdjustedRefreshRateDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kCrosContentAdjustedRefreshRate)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"autofill-enable-cvc-storage-and-filling-enhancement",
     flag_descriptions::kAutofillEnableCvcStorageAndFillingEnhancementName,
     flag_descriptions::
         kAutofillEnableCvcStorageAndFillingEnhancementDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableCvcStorageAndFillingEnhancement)},

    {"improved-signin-ui-on-desktop",
     flag_descriptions::kImprovedSigninUIOnDesktopName,
     flag_descriptions::kImprovedSigninUIOnDesktopDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(switches::kImprovedSigninUIOnDesktop)},

    {"outline-silhouette-icon", flag_descriptions::kOutlineSilhouetteIconName,
     flag_descriptions::kOutlineSilhouetteIconDescription,
     kOsMac | kOsWin | kOsLinux, FEATURE_VALUE_TYPE(kOutlineSilhouetteIcon)},

    {"improved-settings-ui-on-desktop",
     flag_descriptions::kImprovedSettingsUIOnDesktopName,
     flag_descriptions::kImprovedSettingsUIOnDesktopDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(switches::kImprovedSettingsUIOnDesktop)},

#if BUILDFLAG(IS_ANDROID)
    {"discount-on-navigation",
     commerce::flag_descriptions::kDiscountOnNavigationName,
     commerce::flag_descriptions::kDiscountOnNavigationDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(commerce::kEnableDiscountInfoApi,
                                    kDiscountsVariationsOnAndroid,
                                    "DisocuntOnNavigation")},
#endif  // BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {"discount-on-navigation",
     commerce::flag_descriptions::kDiscountOnNavigationName,
     commerce::flag_descriptions::kDiscountOnNavigationDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(commerce::kEnableDiscountInfoApi,
                                    kDiscountsVariations,
                                    "DisocuntOnNavigation")},
#endif  //! BUILDFLAG(IS_ANDROID)

    {"devtools-privacy-ui", flag_descriptions::kDevToolsPrivacyUIName,
     flag_descriptions::kDevToolsPrivacyUIDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kDevToolsPrivacyUI)},

    {"permissions-ai-v1", flag_descriptions::kPermissionsAIv1Name,
     flag_descriptions::kPermissionsAIv1Description, kOsDesktop,
     FEATURE_VALUE_TYPE(permissions::features::kPermissionsAIv1)},

#if BUILDFLAG(IS_CHROMEOS)
    {"exclude-display-in-mirror-mode",
     flag_descriptions::kExcludeDisplayInMirrorModeName,
     flag_descriptions::kExcludeDisplayInMirrorModeDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(display::features::kExcludeDisplayInMirrorMode)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
    {"enable-task-manager-clank", flag_descriptions::kTaskManagerClankName,
     flag_descriptions::kTaskManagerClankDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(features::kTaskManagerClank)},
#else
    {"enable-task-manager-desktop-refresh",
     flag_descriptions::kTaskManagerDesktopRefreshName,
     flag_descriptions::kTaskManagerDesktopRefreshDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kTaskManagerDesktopRefresh)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"autofill-enable-payment-settings-card-promo-and-scan-card",
     flag_descriptions::kAutofillEnablePaymentSettingsCardPromoAndScanCardName,
     flag_descriptions::
         kAutofillEnablePaymentSettingsCardPromoAndScanCardDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::
             kAutofillEnablePaymentSettingsCardPromoAndScanCard)},

    {"autofill-enable-payment-settings-server-card-save",
     flag_descriptions::kAutofillEnablePaymentSettingsServerCardSaveName,
     flag_descriptions::kAutofillEnablePaymentSettingsServerCardSaveDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnablePaymentSettingsServerCardSave)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"cert-verification-network-time",
     flag_descriptions::kCertVerificationNetworkTimeName,
     flag_descriptions::kCertVerificationNetworkTimeDescription,
     kOsMac | kOsWin | kOsLinux | kOsAndroid,
     FEATURE_VALUE_TYPE(features::kCertVerificationNetworkTime)},

#if !BUILDFLAG(IS_ANDROID)
    {"enable-lens-overlay-translate-button",
     flag_descriptions::kLensOverlayTranslateButtonName,
     flag_descriptions::kLensOverlayTranslateButtonDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(lens::features::kLensOverlayTranslateButton)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {"enable-lens-overlay-contextual-search-box",
     flag_descriptions::kLensOverlayContextualSearchboxName,
     flag_descriptions::kLensOverlayContextualSearchboxDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         lens::features::kLensOverlayContextualSearchbox,
         kContextualSearchboxVariations,
         "LensOverlayContextualSearchbox")},
#endif  // !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {"enable-lens-overlay-latency-optimizations",
     flag_descriptions::kLensOverlayLatencyOptimizationsName,
     flag_descriptions::kLensOverlayLatencyOptimizationsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(lens::features::kLensOverlayLatencyOptimizations)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
    {"enable-lens-overlay-image-context-menu-actions",
     flag_descriptions::kLensOverlayImageContextMenuActionsName,
     flag_descriptions::kLensOverlayImageContextMenuActionsDescription,
     kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         lens::features::kLensOverlayImageContextMenuActions,
         kLensOverlayImageContextMenuActionsVariations,
         "LensOverlayImageContextMenuActions")},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"jump-start-omnibox", flag_descriptions::kJumpStartOmniboxName,
     flag_descriptions::kJumpStartOmniboxDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(omnibox::kJumpStartOmnibox,
                                    kJumpStartOmniboxVariations,
                                    "JumpStartOmnibox")},
    {"retain-omnibox-on-focus", flag_descriptions::kRetainOmniboxOnFocusName,
     flag_descriptions::kRetainOmniboxOnFocusDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(omnibox::kRetainOmniboxOnFocus)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"autofill-enable-log-form-events-to-all-parsed-form-types",
     flag_descriptions::kAutofillEnableLogFormEventsToAllParsedFormTypesName,
     flag_descriptions::
         kAutofillEnableLogFormEventsToAllParsedFormTypesDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableLogFormEventsToAllParsedFormTypes)},

    {"enable-segmentation-internals-survey",
     flag_descriptions::kSegmentationSurveyPageName,
     flag_descriptions::kSegmentationSurveyPageDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         segmentation_platform::features::kSegmentationSurveyPage)},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
    {"autofill-enable-buy-now-pay-later-for-affirm",
     flag_descriptions::kAutofillEnableBuyNowPayLaterForAffirmName,
     flag_descriptions::kAutofillEnableBuyNowPayLaterForAffirmDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableBuyNowPayLaterForAffirm)},

    {"autofill-enable-buy-now-pay-later-for-zip",
     flag_descriptions::kAutofillEnableBuyNowPayLaterForZipName,
     flag_descriptions::kAutofillEnableBuyNowPayLaterForZipDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableBuyNowPayLaterForZip)},

    {"autofill-enable-buy-now-pay-later-syncing",
     flag_descriptions::kAutofillEnableBuyNowPayLaterSyncingName,
     flag_descriptions::kAutofillEnableBuyNowPayLaterSyncingDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableBuyNowPayLaterSyncing)},
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) ||
        // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
    {"biometric-auth-identity-check",
     flag_descriptions::kBiometricAuthIdentityCheckName,
     flag_descriptions::kBiometricAuthIdentityCheckDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         password_manager::features::kBiometricAuthIdentityCheck)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"autofill-enable-cvc-storage-and-filling-standalone-form-enhancement",
     flag_descriptions::
         kAutofillEnableCvcStorageAndFillingStandaloneFormEnhancementName,
     flag_descriptions::
         kAutofillEnableCvcStorageAndFillingStandaloneFormEnhancementDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::
             kAutofillEnableCvcStorageAndFillingStandaloneFormEnhancement)},
#if BUILDFLAG(IS_ANDROID)
    {"cct-sign-in-prompt", flag_descriptions::kCCTSignInPromptName,
     flag_descriptions::kCCTSignInPromptDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(switches::kCctSignInPrompt,
                                    kCctSignInPromptVariations,
                                    "CctSignInPrompt")},
#endif

    {"enable-bookmarks-selected-type-on-signin-for-testing",
     flag_descriptions::kEnableBookmarksSelectedTypeOnSigninForTestingName,
     flag_descriptions::
         kEnableBookmarksSelectedTypeOnSigninForTestingDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         syncer::kEnableBookmarksSelectedTypeOnSigninForTesting)},

#if !BUILDFLAG(IS_ANDROID)
    {"separate-local-and-account-themes",
     flag_descriptions::kSeparateLocalAndAccountThemesName,
     flag_descriptions::kSeparateLocalAndAccountThemesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(syncer::kSeparateLocalAndAccountThemes)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"clank-default-browser-promo-role-manager",
     flag_descriptions::kClankDefaultBrowserPromoRoleManagerName,
     flag_descriptions::kClankDefaultBrowserPromoRoleManagerDescription,
     kOsAndroid,
     SINGLE_DISABLE_VALUE_TYPE(switches::kDisableDefaultBrowserPromo)},

    {"clank-default-browser-promo2",
     flag_descriptions::kClankDefaultBrowserPromoName,
     flag_descriptions::kClankDefaultBrowserPromoDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kDefaultBrowserPromoAndroid2)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-mall-url", flag_descriptions::kCrosMallUrlName,
     flag_descriptions::kCrosMallUrlDescription, kOsCrOS,
     STRING_VALUE_TYPE(ash::switches::kMallUrl, "")},

    {"overlay-scrollbars-os-settings",
     flag_descriptions::kOverlayScrollbarsOSSettingsName,
     flag_descriptions::kOverlayScrollbarsOSSettingsDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(features::kOverlayScrollbarsOSSetting)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"autofill-enable-card-benefits-iph",
     flag_descriptions::kAutofillEnableCardBenefitsIphName,
     flag_descriptions::kAutofillEnableCardBenefitsIphDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableCardBenefitsIph)},

#if BUILDFLAG(IS_ANDROID)
    {"enable-automotive-fullscreen-toolbar-improvements",
     flag_descriptions::kAutomotiveFullscreenToolbarImprovementsName,
     flag_descriptions::kAutomotiveFullscreenToolbarImprovementsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         chrome::android::kAutomotiveFullscreenToolbarImprovements)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"privacy-sandbox-privacy-policy",
     flag_descriptions::kPrivacySandboxPrivacyPolicyName,
     flag_descriptions::kPrivacySandboxPrivacyPolicyDescription, kOsAll,
     FEATURE_VALUE_TYPE(privacy_sandbox::kPrivacySandboxPrivacyPolicy)},

#if BUILDFLAG(IS_ANDROID)
    {"support-multiple-server-requests-for-pix-payments",
     flag_descriptions::kSupportMultipleServerRequestsForPixPaymentsName,
     flag_descriptions::kSupportMultipleServerRequestsForPixPaymentsDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         payments::facilitated::kSupportMultipleServerRequestsForPixPayments)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(SKIA_BUILD_RUST_PNG)
    {"rusty-png", flag_descriptions::kRustyPngName,
     flag_descriptions::kRustyPngDescription, kOsAll,
     FEATURE_VALUE_TYPE(skia::kRustyPngFeature)},
#endif

    {"autofill-enable-card-info-runtime-retrieval",
     flag_descriptions::kAutofillEnableCardInfoRuntimeRetrievalName,
     flag_descriptions::kAutofillEnableCardInfoRuntimeRetrievalDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillEnableCardInfoRuntimeRetrieval)},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
    {"translation-api", flag_descriptions::kTranslationAPIName,
     flag_descriptions::kTranslationAPIDescription, kOsMac | kOsWin | kOsLinux,
     FEATURE_WITH_PARAMS_VALUE_TYPE(blink::features::kTranslationAPI,
                                    kTranslationAPIVariations,
                                    "TranslationAPI")},
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)

    {"password-form-grouped-affiliations",
     flag_descriptions::kPasswordFormGroupedAffiliationsName,
     flag_descriptions::kPasswordFormGroupedAffiliationsDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         password_manager::features::kPasswordFormGroupedAffiliations)},

#if !BUILDFLAG(IS_ANDROID)
    {"ai-settings-page-refresh", flag_descriptions::kAiSettingsPageRefreshName,
     flag_descriptions::kAiSettingsPageRefreshDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(optimization_guide::features::kAiSettingsPageRefresh)},
    {"privacy-guide-ai-settings",
     flag_descriptions::kPrivacyGuideAiSettingsName,
     flag_descriptions::kPrivacyGuideAiSettingsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(optimization_guide::features::kPrivacyGuideAiSettings)},
    {"ai-settings-enterprise-disabled-ui",
     flag_descriptions::kAiSettingsPageEnterpriseDisabledName,
     flag_descriptions::kAiSettingsPageEnterpriseDisabledDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         optimization_guide::features::kAiSettingsPageEnterpriseDisabledUi)},

#endif  // !BUILDFLAG(IS_ANDROID)

    {"password-form-clientside-classifier",
     flag_descriptions::kPasswordFormClientsideClassifierName,
     flag_descriptions::kPasswordFormClientsideClassifierDescription, kOsAll,
     FEATURE_VALUE_TYPE(
         password_manager::features::kPasswordFormClientsideClassifier)},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
    {"contextual-cueing", flag_descriptions::kContextualCueingName,
     flag_descriptions::kContextualCueingDescription,
     kOsLinux | kOsMac | kOsWin,
     FEATURE_WITH_PARAMS_VALUE_TYPE(contextual_cueing::kContextualCueing,
                                    kContextualCueingEnabledOptions,
                                    "ContextualCueingEnabledOptions")},
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)

    {"partitioned-popins", flag_descriptions::kPartitionedPopinsName,
     flag_descriptions::kPartitionedPopinsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(blink::features::kPartitionedPopins)},

#if !BUILDFLAG(IS_ANDROID)
    {"separate-local-and-account-search-engines",
     flag_descriptions::kSeparateLocalAndAccountSearchEnginesName,
     flag_descriptions::kSeparateLocalAndAccountSearchEnginesDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(syncer::kSeparateLocalAndAccountSearchEngines)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)
    {"partition-alloc-with-advanced-checks",
     flag_descriptions::kPartitionAllocWithAdvancedChecksName,
     flag_descriptions::kPartitionAllocWithAdvancedChecksDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         base::features::kPartitionAllocWithAdvancedChecks,
         kPartitionAllocWithAdvancedChecksEnabledProcessesOptions,
         "PartitionAllocWithAdvancedChecks")},
#endif  //  PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)

    {"partition-visited-link-database",
     flag_descriptions::kPartitionVisitedLinkDatabaseName,
     flag_descriptions::kPartitionVisitedLinkDatabaseDescription, kOsAll,
     FEATURE_VALUE_TYPE(blink::features::kPartitionVisitedLinkDatabase)},

    {"partition-visited-link-database-with-self-links",
     flag_descriptions::kPartitionVisitedLinkDatabaseWithSelfLinksName,
     flag_descriptions::kPartitionVisitedLinkDatabaseWithSelfLinksDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         blink::features::kPartitionVisitedLinkDatabaseWithSelfLinks)},

    {"autofill-disable-local-card-migration",
     flag_descriptions::kAutofillDisableLocalCardMigrationName,
     flag_descriptions::kAutofillDisableLocalCardMigrationDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillDisableLocalCardMigration)},
    {"predictable-reported-quota",
     flag_descriptions::kPredictableReportedQuotaName,
     flag_descriptions::kPredictableReportedQuotaDescription, kOsAll,
     FEATURE_VALUE_TYPE(storage::features::kStaticStorageQuota)},

#if BUILDFLAG(IS_ANDROID)
    {"use-ahardwarebuffer-usage-flags-from-vulkan",
     flag_descriptions::kUseHardwareBufferUsageFlagsFromVulkanName,
     flag_descriptions::kUseHardwareBufferUsageFlagsFromVulkanDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(::features::kUseHardwareBufferUsageFlagsFromVulkan)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID) && PA_BUILDFLAG(HAS_MEMORY_TAGGING) && \
    PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)
    {"partition-alloc-memory-tagging",
     flag_descriptions::kPartitionAllocMemoryTaggingName,
     flag_descriptions::kPartitionAllocMemoryTaggingDescription, kOsAndroid,
     FEATURE_WITH_PARAMS_VALUE_TYPE(
         base::features::kPartitionAllocMemoryTagging,
         kPartitionAllocMemoryTaggingEnabledProcessesOptions,
         "PartitionAllocMemoryTagging")},
#endif  // BUILDFLAG(IS_ANDROID) && PA_BUILDFLAG(HAS_MEMORY_TAGGING) &&
        // PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)

#if BUILDFLAG(IS_MAC)
    {"enable-mac-a11y-api-migration",
     flag_descriptions::kMacAccessibilityAPIMigrationName,
     flag_descriptions::kMacAccessibilityAPIMigrationDescription, kOsMac,
     FEATURE_VALUE_TYPE(features::kMacAccessibilityAPIMigration)},
#endif  // BUILDFLAG(IS_MAC)

#if BUILDFLAG(ENABLE_EXTENSIONS)
    {"allow-legacy-mv2-extensions",
     flag_descriptions::kAllowLegacyMV2ExtensionsName,
     flag_descriptions::kAllowLegacyMV2ExtensionsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(extensions_features::kAllowLegacyMV2Extensions)},
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)

#if !BUILDFLAG(IS_ANDROID)
    {"enable-lens-overlay-translate-languages",
     flag_descriptions::kLensOverlayTranslateLanguagesName,
     flag_descriptions::kLensOverlayTranslateLanguagesDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(lens::features::kLensOverlayTranslateLanguages)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_ANDROID)
    {"login-db-deprecation-android",
     flag_descriptions::kLoginDbDeprecationAndroidName,
     flag_descriptions::kLoginDbDeprecationAndroidDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(
         password_manager::features::kLoginDbDeprecationAndroid)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_GLIC)
    {"glic", flag_descriptions::kGlicName, flag_descriptions::kGlicDescription,
     kOsMac | kOsWin | kOsLinux, FEATURE_VALUE_TYPE(features::kGlic)},
#endif  // BUILDFLAG(ENABLE_GLIC)

#if BUILDFLAG(IS_ANDROID)
    {"enterprise-real-time-url-check-on-android",
     flag_descriptions::kEnterpriseRealTimeUrlCheckOnAndroidName,
     flag_descriptions::kEnterpriseRealTimeUrlCheckOnAndroidDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(safe_browsing::kEnterpriseRealTimeUrlCheckOnAndroid)},
#endif  // BUILDFLAG(IS_ANDROID)

    {"service-worker-auto-preload",
     flag_descriptions::kServiceWorkerAutoPreloadName,
     flag_descriptions::kServiceWorkerAutoPreloadDescription, kOsAll,
     FEATURE_WITH_PARAMS_VALUE_TYPE(features::kServiceWorkerAutoPreload,
                                    kServiceWorkerAutoPreloadVariations,
                                    "ServiceWorkerAutoPreload")},

    {"autofill-enable-save-and-fill",
     flag_descriptions::kAutofillEnableSaveAndFillName,
     flag_descriptions::kAutofillEnableSaveAndFillDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableSaveAndFill)},

    {"autofill-improved-labels", flag_descriptions::kAutofillImprovedLabelsName,
     flag_descriptions::kAutofillImprovedLabelsDescription, kOsDesktop,
     FEATURE_WITH_PARAMS_VALUE_TYPE(autofill::features::kAutofillImprovedLabels,
                                    kAutofillImprovedLabelsVariations,
                                    "AutofillImprovedLabels")},

#if BUILDFLAG(IS_ANDROID)
    {"android-bookmark-bar", flag_descriptions::kAndroidBookmarkBarName,
     flag_descriptions::kAndroidBookmarkBarDescription, kOsAndroid,
     FEATURE_VALUE_TYPE(chrome::android::kAndroidBookmarkBar)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"cros-mall-managed", flag_descriptions::kCrosMallManagedName,
     flag_descriptions::kCrosMallManagedDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(chromeos::features::kCrosMallManaged)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"happy-eyeballs-v3", flag_descriptions::kHappyEyeballsV3Name,
     flag_descriptions::kHappyEyeballsV3Description, kOsAll,
     FEATURE_VALUE_TYPE(net::features::kHappyEyeballsV3)},

#if BUILDFLAG(IS_CHROMEOS)
    {"mantis-feature-key", flag_descriptions::kMantisFeatureKeyName,
     flag_descriptions::kMantisFeatureKeyDescription, kOsCrOS,
     STRING_VALUE_TYPE(ash::switches::kMantisFeatureKey, "")},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"signature-based-sri", flag_descriptions::kSignatureBasedSriName,
     flag_descriptions::kSignatureBasedSriDescription, kOsAll,
     FEATURE_VALUE_TYPE(network::features::kSRIMessageSignatureEnforcement)},

#if !BUILDFLAG(IS_ANDROID)
    {"policy-promotion-banner-flag",
     flag_descriptions::kEnablePolicyPromotionBannerName,
     flag_descriptions::kEnablePolicyPromotionBannerDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kEnablePolicyPromotionBanner)},
#endif

    {"privacy-sandbox-ads-api-ux-enhancements",
     flag_descriptions::kPrivacySandboxAdsApiUxEnhancementsName,
     flag_descriptions::kPrivacySandboxAdsApiUxEnhancementsDescription, kOsAll,
     FEATURE_VALUE_TYPE(privacy_sandbox::kPrivacySandboxAdsApiUxEnhancements)},

#if !BUILDFLAG(IS_ANDROID)
    {"safety-hub-services-on-start-up",
     flag_descriptions::kSafetyHubServicesOnStartUpName,
     flag_descriptions::kSafetyHubServicesOnStartUpDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kSafetyHubServicesOnStartUp)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)
    {"enable-chrome-refresh-token-binding",
     flag_descriptions::kEnableChromeRefreshTokenBindingName,
     flag_descriptions::kEnableChromeRefreshTokenBindingDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(switches::kEnableChromeRefreshTokenBinding)},
#endif  // BUILDFLAG(ENABLE_BOUND_SESSION_CREDENTIALS)

#if BUILDFLAG(IS_CHROMEOS)
    {"use-managed-print-job-options-in-print-preview",
     flag_descriptions::kUseManagedPrintJobOptionsInPrintPreviewName,
     flag_descriptions::kUseManagedPrintJobOptionsInPrintPreviewDescription,
     kOsCrOS,
     FEATURE_VALUE_TYPE(features::kUseManagedPrintJobOptionsInPrintPreview)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if BUILDFLAG(IS_ANDROID)
    {"autofill-third-party-mode-content-provider",
     flag_descriptions::kAutofillThirdPartyModeContentProviderName,
     flag_descriptions::kAutofillThirdPartyModeContentProviderDescription,
     kOsAndroid,
     FEATURE_VALUE_TYPE(
         autofill::features::kAutofillThirdPartyModeContentProvider)},
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_MAC)
    {"block-root-window-accessible-name-change-event",
     flag_descriptions::kBlockRootWindowAccessibleNameChangeEventName,
     flag_descriptions::kBlockRootWindowAccessibleNameChangeEventDescription,
     kOsMac,
     FEATURE_VALUE_TYPE(::features::kBlockRootWindowAccessibleNameChangeEvent)},
#endif  // BUILDFLAG(IS_MAC)

    {"throttle-main-thread-to-60hz", flag_descriptions::kThrottleMainTo60HzName,
     flag_descriptions::kThrottleMainTo60HzDescription, kOsAll,
     FEATURE_VALUE_TYPE(features::kThrottleMainFrameTo60Hz)},

    {"client-side-detection-brand-and-page-intent",
     flag_descriptions::kClientSideDetectionBrandAndIntentForScamDetectionName,
     flag_descriptions::
         kClientSideDetectionBrandAndIntentForScamDetectionDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(
         safe_browsing::kClientSideDetectionBrandAndIntentForScamDetection)},

#if BUILDFLAG(IS_CHROMEOS)
    {"enable-keyboard-used-palm-suppression",
     flag_descriptions::kEnableKeyboardUsedPalmSuppressionName,
     flag_descriptions::kEnableKeyboardUsedPalmSuppressionDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(ui::kEnableKeyboardUsedPalmSuppression)},
#endif  // BUILDFLAG(IS_CHROMEOS)

    {"autofill-enable-card-benefits-for-bmo",
     flag_descriptions::kAutofillEnableCardBenefitsForBmoName,
     flag_descriptions::kAutofillEnableCardBenefitsForBmoDescription, kOsAll,
     FEATURE_VALUE_TYPE(autofill::features::kAutofillEnableCardBenefitsForBmo)},

#if BUILDFLAG(IS_WIN)
    {"windows-system-tracing", flag_descriptions::kWindowsSystemTracingName,
     flag_descriptions::kWindowsSystemTracingDescription, kOsWin,
     FEATURE_VALUE_TYPE(kWindowsSystemTracing)},
#endif  // BUILDFLAG(IS_WIN)

    {"privacy-sandbox-equalized-prompt-buttons",
     flag_descriptions::kPrivacySandboxEqualizedPromptButtonsName,
     flag_descriptions::kPrivacySandboxEqualizedPromptButtonsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         privacy_sandbox::kPrivacySandboxEqualizedPromptButtons)},

#if !BUILDFLAG(IS_ANDROID)
    {"move-theme-prefs-to-specifics",
     flag_descriptions::kMoveThemePrefsToSpecificsName,
     flag_descriptions::kMoveThemePrefsToSpecificsDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(syncer::kMoveThemePrefsToSpecifics)},
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS)
    {"fast-drm-master-drop", flag_descriptions::kFastDrmMasterDropName,
     flag_descriptions::kFastDrmMasterDropDescription, kOsCrOS,
     FEATURE_VALUE_TYPE(display::features::kFastDrmMasterDrop)},
#endif  // BUILDFLAG(IS_CHROMEOS)

#if !BUILDFLAG(IS_ANDROID)
    {"bookmarks-tree-view", flag_descriptions::kBookmarksTreeViewName,
     flag_descriptions::kBookmarksTreeViewDescription, kOsDesktop,
     FEATURE_VALUE_TYPE(features::kBookmarksTreeView)},
#endif

    {"is-secure-payment-confirmation-available-api",
     flag_descriptions::kIsSecurePaymentConfirmationAvailableAPIName,
     flag_descriptions::kIsSecurePaymentConfirmationAvailableAPIDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         blink::features::kIsSecurePaymentConfirmationAvailableAPI)},

    {"copy-image-filename-to-clipboard",
     flag_descriptions::kCopyImageFilenameToClipboardName,
     flag_descriptions::kCopyImageFilenameToClipboardDescription, kOsAll,
     FEATURE_VALUE_TYPE(download::features::kCopyImageFilenameToClipboard)},

    {"autofill-enable-allowlist-for-bmo-card-category-benefits",
     flag_descriptions::kAutofillEnableAllowlistForBmoCardCategoryBenefitsName,
     flag_descriptions::
         kAutofillEnableAllowlistForBmoCardCategoryBenefitsDescription,
     kOsAll,
     FEATURE_VALUE_TYPE(
         autofill::features::
             kAutofillEnableAllowlistForBmoCardCategoryBenefits)},
    {"enable-snackbar-in-settings",
     flag_descriptions::kEnableSnackbarInSettingsName,
     flag_descriptions::kEnableSnackbarInSettingsDescription,
     kOsMac | kOsWin | kOsLinux,
     FEATURE_VALUE_TYPE(switches::kEnableSnackbarInSettings)},

#if BUILDFLAG(IS_ANDROID) || BUILDFLAG(IS_LINUX)
    {"automatic-usb-detach", flag_descriptions::kAutomaticUsbDetachName,
     flag_descriptions::kAutomaticUsbDetachDescription, kOsAndroid | kOsLinux,
     FEATURE_VALUE_TYPE(features::kAutomaticUsbDetach)},
#endif  // BUILDFLAG(IS_ANDROID) || BUILDFLAG(IS_LINUX)

#if !BUILDFLAG(IS_ANDROID)
    {"enable-lens-overlay-side-panel-open-in-new-tab",
     flag_descriptions::kLensOverlaySidePanelOpenInNewTabName,
     flag_descriptions::kLensOverlaySidePanelOpenInNewTabDescription,
     kOsDesktop,
     FEATURE_VALUE_TYPE(lens::features::kLensOverlaySidePanelOpenInNewTab)},
#endif  // !BUILDFLAG(IS_ANDROID)

=======
>>>>>>> chromium
    // NOTE: Adding a new flag requires adding a corresponding entry to enum
    // "LoginCustomFlags" in tools/metrics/histograms/enums.xml. See "Flag
    // Histograms" in tools/metrics/histograms/README.md (run the
    // AboutFlagsHistogramTest unit test to verify this process).
};

class FlagsStateSingleton : public flags_ui::FlagsState::Delegate {
 public:
  FlagsStateSingleton()
      : flags_state_(
            std::make_unique<flags_ui::FlagsState>(kFeatureEntries, this)) {}
  FlagsStateSingleton(const FlagsStateSingleton&) = delete;
  FlagsStateSingleton& operator=(const FlagsStateSingleton&) = delete;
  ~FlagsStateSingleton() override = default;

  static FlagsStateSingleton* GetInstance() {
    return base::Singleton<FlagsStateSingleton>::get();
  }

  static flags_ui::FlagsState* GetFlagsState() {
    return GetInstance()->flags_state_.get();
  }

  void RebuildState(const std::vector<flags_ui::FeatureEntry>& entries) {
    flags_state_ = std::make_unique<flags_ui::FlagsState>(entries, this);
  }

  void RestoreDefaultState() {
    flags_state_ =
        std::make_unique<flags_ui::FlagsState>(kFeatureEntries, this);
  }

 private:
  // flags_ui::FlagsState::Delegate:
  bool ShouldExcludeFlag(const flags_ui::FlagsStorage* storage,
                         const FeatureEntry& entry) override {
    return flags::IsFlagExpired(storage, entry.internal_name);
  }

  std::unique_ptr<flags_ui::FlagsState> flags_state_;
};

bool ShouldSkipNonDeprecatedFeatureEntry(const FeatureEntry& entry) {
  return ~entry.supported_platforms & kDeprecated;
}

}  // namespace

<<<<<<< HEAD
#if BUILDFLAG(IS_CHROMEOS)
// This method may be invoked both synchronously or asynchronously. Based on
// whether the current user is the owner of the device, generates the
// appropriate flag storage.
void GetStorageAsync(Profile* profile,
                     GetStorageCallback callback,
                     bool current_user_is_owner) {
  // On ChromeOS the owner can set system wide flags and other users can only
  // set flags for their own session.
  if (current_user_is_owner) {
    ash::OwnerSettingsServiceAsh* service =
        ash::OwnerSettingsServiceAshFactory::GetForBrowserContext(profile);
    std::move(callback).Run(
        std::make_unique<ash::about_flags::OwnerFlagsStorage>(
            profile->GetPrefs(), service),
        flags_ui::kOwnerAccessToFlags);
  } else {
    std::move(callback).Run(std::make_unique<flags_ui::PrefServiceFlagsStorage>(
                                profile->GetPrefs()),
                            flags_ui::kGeneralAccessFlagsOnly);
  }
}
#endif

// ash-chrome uses different storage flag storage logic from other desktop
// platforms.
void GetStorage(Profile* profile, GetStorageCallback callback) {
#if BUILDFLAG(IS_CHROMEOS)
  // Bypass possible incognito profile.
  // On ChromeOS the owner can set system wide flags and other users can only
  // set flags for their own session.
  Profile* original_profile = profile->GetOriginalProfile();
  if (base::SysInfo::IsRunningOnChromeOS() &&
      ash::OwnerSettingsServiceAshFactory::GetForBrowserContext(
          original_profile)) {
    ash::OwnerSettingsServiceAsh* service =
        ash::OwnerSettingsServiceAshFactory::GetForBrowserContext(
            original_profile);
    service->IsOwnerAsync(base::BindOnce(&GetStorageAsync, original_profile,
                                         std::move(callback)));
  } else {
    GetStorageAsync(original_profile, std::move(callback),
                    /*current_user_is_owner=*/false);
  }
#else
  std::move(callback).Run(std::make_unique<flags_ui::PrefServiceFlagsStorage>(
                              g_browser_process->local_state()),
                          flags_ui::kOwnerAccessToFlags);
#endif
}

bool ShouldSkipConditionalFeatureEntry(const flags_ui::FlagsStorage* storage,
                                       const FeatureEntry& entry) {
#if BUILDFLAG(IS_CHROMEOS)
=======
bool ShouldSkipConditionalFeatureEntry(const flags_ui::FlagsStorage* storage,
                                       const FeatureEntry& entry) {
>>>>>>> chromium
  version_info::Channel channel = chrome::GetChannel();
#if BUILDFLAG(IS_CHROMEOS_ASH)
  // enable-ui-devtools is only available on for non Stable channels.
  if (!strcmp(ui_devtools::switches::kEnableUiDevTools, entry.internal_name) &&
      channel == version_info::Channel::STABLE) {
    return true;
  }

<<<<<<< HEAD
  // Skip arc-enable-attestation if it is enabled by ash switch.
  if (!strcmp(kArcEnableAttestationFlag, entry.internal_name)) {
    return base::CommandLine::ForCurrentProcess()->HasSwitch(
        ash::switches::kArcEnableAttestation);
=======
  if (!strcmp(kLacrosSupportInternalName, entry.internal_name)) {
    return !crosapi::browser_util::IsLacrosSupportFlagAllowed(channel);
  }

  if (!strcmp(kLacrosStabilityInternalName, entry.internal_name)) {
    return !crosapi::browser_util::IsLacrosAllowedToBeEnabled(channel);
>>>>>>> chromium
  }

  if (!strcmp(kLacrosPrimaryInternalName, entry.internal_name)) {
    return !crosapi::browser_util::IsLacrosPrimaryFlagAllowed(channel);
  }

  if (!strcmp(kWebAppsCrosapiInternalName, entry.internal_name)) {
    return !crosapi::browser_util::IsLacrosAllowedToBeEnabled(channel);
  }

  // The following flags are only available to teamfooders.
  if (!strcmp(kAssistantBetterOnboardingInternalName, entry.internal_name)) {
    return !base::FeatureList::IsEnabled(features::kTeamfoodFlags);
  }

  // wallpaper-webui is only available for Unknown/Canary/Dev channels.
  if (!strcmp(kWallpaperWebUIInternalName, entry.internal_name) &&
      channel != version_info::Channel::DEV &&
      channel != version_info::Channel::CANARY &&
      channel != version_info::Channel::UNKNOWN) {
    return true;
  }

  // Leave the feature only for ARCVM.
  if (!strcmp(kArcUseHighMemoryDalvikProfileInternalName,
              entry.internal_name)) {
    return !arc::IsArcVmEnabled();
  }

  // Only show Borealis flags on enabled devices.
  if (!strcmp(kBorealisDiskManagementInternalName, entry.internal_name)) {
    return !base::FeatureList::IsEnabled(features::kBorealis);
  }

<<<<<<< HEAD
  // Only show wallpaper fast refresh flag if channel is one of
  // Dev/Canary/Unknown.
  if (!strcmp(kWallpaperFastRefreshInternalName, entry.internal_name)) {
    return (channel != version_info::Channel::DEV &&
            channel != version_info::Channel::CANARY &&
            channel != version_info::Channel::UNKNOWN);
  }

  // Only show clipboard history longpress flag if channel is one of
  // Beta/Dev/Canary/Unknown.
  if (!strcmp(kClipboardHistoryLongpressInternalName, entry.internal_name)) {
    return channel != version_info::Channel::BETA &&
           channel != version_info::Channel::DEV &&
           channel != version_info::Channel::CANARY &&
           channel != version_info::Channel::UNKNOWN;
  }

  // Disable and prevent users from enabling LL privacy on boards that were
  // explicitly built without floss or hardware does not support LL privacy.
  if (!strcmp(kBluetoothUseLLPrivacyInternalName, entry.internal_name)) {
    return (
        base::FeatureList::GetInstance()->IsFeatureOverriddenFromCommandLine(
            floss::features::kLLPrivacyIsAvailable.name,
            base::FeatureList::OVERRIDE_DISABLE_FEATURE));
  }

  // Only show sea-pen flag if channel is one of Dev/Canary/Unknown.
  if (!strcmp(kSeaPenInternalName, entry.internal_name)) {
    return channel != version_info::Channel::DEV &&
           channel != version_info::Channel::CANARY &&
           channel != version_info::Channel::UNKNOWN;
  }

  // Only show Assistant Launcher search IPH flag if channel is one of
  // Beta/Dev/Canary/Unknown.
  if (!strcmp(kAssistantIphInternalName, entry.internal_name)) {
    return channel != version_info::Channel::BETA &&
           channel != version_info::Channel::DEV &&
           channel != version_info::Channel::CANARY &&
           channel != version_info::Channel::UNKNOWN;
  }

  // Only show Growth campaigns flag if channel is one of Beta/Dev/Canary/
  // Unknown.
  if (!strcmp(kGrowthCampaigns, entry.internal_name)) {
    return channel != version_info::Channel::BETA &&
           channel != version_info::Channel::DEV &&
           channel != version_info::Channel::CANARY &&
           channel != version_info::Channel::UNKNOWN;
  }

  // Only show Growth campaigns test tag flag if channel is one of
  // Beta/Dev/Canary/ Unknown.
  if (!strcmp(kGrowthCampaignsTestTag, entry.internal_name)) {
    return channel != version_info::Channel::BETA &&
           channel != version_info::Channel::DEV &&
           channel != version_info::Channel::CANARY &&
           channel != version_info::Channel::UNKNOWN;
  }
#endif  // BUILDFLAG(IS_CHROMEOS)
#if BUILDFLAG(ENABLE_EXTENSIONS)
  version_info::Channel chrome_channel = chrome::GetChannel();
  // Only show extension AI data flag in non-stable channels.
  if (!strcmp(kExtensionAiDataInternalName, entry.internal_name)) {
    return chrome_channel != version_info::Channel::BETA &&
           chrome_channel != version_info::Channel::DEV &&
           chrome_channel != version_info::Channel::CANARY &&
           chrome_channel != version_info::Channel::UNKNOWN;
  }
#endif
  if (flags::IsFlagExpired(storage, entry.internal_name)) {
=======
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

  // data-reduction-proxy-lo-fi and enable-data-reduction-proxy-lite-page
  // are only available for Chromium builds and the Canary/Dev/Beta channels.
  if ((!strcmp("data-reduction-proxy-lo-fi", entry.internal_name) ||
       !strcmp("enable-data-reduction-proxy-lite-page", entry.internal_name)) &&
      channel != version_info::Channel::BETA &&
      channel != version_info::Channel::DEV &&
      channel != version_info::Channel::CANARY &&
      channel != version_info::Channel::UNKNOWN) {
>>>>>>> chromium
    return true;
  }

  // enable-unsafe-webgpu is only available on Dev/Canary channels.
  if (!strcmp("enable-unsafe-webgpu", entry.internal_name) &&
      channel != version_info::Channel::DEV &&
      channel != version_info::Channel::CANARY &&
      channel != version_info::Channel::UNKNOWN) {
    return true;
  }

#if defined(OS_WIN)
  // HDR mode works, but displays everything horribly wrong prior to windows 10.
  if (!strcmp("enable-hdr", entry.internal_name) &&
      base::win::GetVersion() < base::win::Version::WIN10) {
    return true;
  }
#endif  // OS_WIN

  if (!strcmp("dns-over-https", entry.internal_name) &&
      SystemNetworkContextManager::GetInstance() &&
      (SystemNetworkContextManager::GetStubResolverConfigReader()
           ->ShouldDisableDohForManaged() ||
       features::kDnsOverHttpsShowUiParam.Get())) {
    return true;
  }

#if defined(OS_ANDROID)
  if (!strcmp("password-change-support", entry.internal_name)) {
    return !base::FeatureList::IsEnabled(features::kTeamfoodFlags);
  }
#endif  // OS_ANDROID

  if (flags::IsFlagExpired(storage, entry.internal_name))
    return true;

  return false;
}

void ConvertFlagsToSwitches(flags_ui::FlagsStorage* flags_storage,
                            base::CommandLine* command_line,
                            flags_ui::SentinelsMode sentinels) {
  if (command_line->HasSwitch(switches::kNoExperiments))
    return;

  FlagsStateSingleton::GetFlagsState()->ConvertFlagsToSwitches(
      flags_storage, command_line, sentinels, switches::kEnableFeatures,
      switches::kDisableFeatures);
}

std::vector<std::string> RegisterAllFeatureVariationParameters(
    flags_ui::FlagsStorage* flags_storage,
    base::FeatureList* feature_list) {
  return FlagsStateSingleton::GetFlagsState()
      ->RegisterAllFeatureVariationParameters(flags_storage, feature_list);
}

void GetFlagFeatureEntries(flags_ui::FlagsStorage* flags_storage,
                           flags_ui::FlagAccess access,
                           base::Value::ListStorage& supported_entries,
                           base::Value::ListStorage& unsupported_entries) {
  FlagsStateSingleton::GetFlagsState()->GetFlagFeatureEntries(
      flags_storage, access, supported_entries, unsupported_entries,
      base::BindRepeating(&ShouldSkipConditionalFeatureEntry,
                          // Unretained: this callback doesn't outlive this
                          // stack frame.
                          base::Unretained(flags_storage)));
}

void GetFlagFeatureEntriesForDeprecatedPage(
    flags_ui::FlagsStorage* flags_storage,
    flags_ui::FlagAccess access,
    base::Value::ListStorage& supported_entries,
    base::Value::ListStorage& unsupported_entries) {
  FlagsStateSingleton::GetFlagsState()->GetFlagFeatureEntries(
      flags_storage, access, supported_entries, unsupported_entries,
      base::BindRepeating(&ShouldSkipNonDeprecatedFeatureEntry));
}

flags_ui::FlagsState* GetCurrentFlagsState() {
  return FlagsStateSingleton::GetFlagsState();
}

bool IsRestartNeededToCommitChanges() {
  return FlagsStateSingleton::GetFlagsState()->IsRestartNeededToCommitChanges();
}

void SetFeatureEntryEnabled(flags_ui::FlagsStorage* flags_storage,
                            const std::string& internal_name,
                            bool enable) {
  FlagsStateSingleton::GetFlagsState()->SetFeatureEntryEnabled(
      flags_storage, internal_name, enable);
}

void SetOriginListFlag(const std::string& internal_name,
                       const std::string& value,
                       flags_ui::FlagsStorage* flags_storage) {
  FlagsStateSingleton::GetFlagsState()->SetOriginListFlag(internal_name, value,
                                                          flags_storage);
}

void RemoveFlagsSwitches(base::CommandLine::SwitchMap* switch_list) {
  FlagsStateSingleton::GetFlagsState()->RemoveFlagsSwitches(switch_list);
}

void ResetAllFlags(flags_ui::FlagsStorage* flags_storage) {
  FlagsStateSingleton::GetFlagsState()->ResetAllFlags(flags_storage);
}

void RecordUMAStatistics(flags_ui::FlagsStorage* flags_storage,
                         const std::string& histogram_name) {
  std::set<std::string> switches;
  std::set<std::string> features;
  FlagsStateSingleton::GetFlagsState()->GetSwitchesAndFeaturesFromFlags(
      flags_storage, &switches, &features);
  flags_ui::ReportAboutFlagsHistogram(histogram_name, switches, features);
}

namespace testing {

std::vector<FeatureEntry>* GetEntriesForTesting() {
  static base::NoDestructor<std::vector<FeatureEntry>> entries;
  return entries.get();
}

void SetFeatureEntries(const std::vector<FeatureEntry>& entries) {
<<<<<<< HEAD
  auto* entries_for_testing = GetEntriesForTesting();  // IN-TEST
  CHECK(entries_for_testing->empty());
  for (const auto& entry : entries) {
    entries_for_testing->push_back(entry);
  }
  FlagsStateSingleton::GetInstance()->RebuildState(*entries_for_testing);
=======
  CHECK(GetEntriesForTesting()->empty());  // IN-TEST
  for (const auto& entry : entries)
    GetEntriesForTesting()->push_back(entry);  // IN-TEST
  FlagsStateSingleton::GetInstance()->RebuildState(
      *GetEntriesForTesting());  // IN-TEST
>>>>>>> chromium
}

ScopedFeatureEntries::ScopedFeatureEntries(
    const std::vector<flags_ui::FeatureEntry>& entries) {
  SetFeatureEntries(entries);
}

ScopedFeatureEntries::~ScopedFeatureEntries() {
  GetEntriesForTesting()->clear();  // IN-TEST
  // Restore the flag state to the production flags.
  FlagsStateSingleton::GetInstance()->RestoreDefaultState();
}

<<<<<<< HEAD
base::span<const FeatureEntry> GetFeatureEntries() {
  if (const auto* entries_for_testing = GetEntriesForTesting();
      !entries_for_testing->empty()) {
    return *entries_for_testing;
  }
=======
const FeatureEntry* GetFeatureEntries(size_t* count) {
  if (!GetEntriesForTesting()->empty()) {
    *count = GetEntriesForTesting()->size();
    return GetEntriesForTesting()->data();
  }
  *count = base::size(kFeatureEntries);
>>>>>>> chromium
  return kFeatureEntries;
}

}  // namespace testing

}  // namespace about_flags
