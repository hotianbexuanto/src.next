// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/chrome_browser_interface_binders.h"

#include <utility>

#include "ash/constants/ash_features.h"
#include "build/build_config.h"
#include "build/chromeos_buildflags.h"
#include "chrome/browser/accessibility/accessibility_labels_service.h"
#include "chrome/browser/accessibility/accessibility_labels_service_factory.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/buildflags.h"
#include "chrome/browser/dom_distiller/dom_distiller_service_factory.h"
<<<<<<< HEAD
#include "chrome/browser/history_clusters/history_clusters_service_factory.h"
#include "chrome/browser/history_embeddings/history_embeddings_utils.h"
=======
#include "chrome/browser/language/translate_frame_binder.h"
#include "chrome/browser/media/history/media_history_store.mojom.h"
>>>>>>> chromium
#include "chrome/browser/media/media_engagement_score_details.mojom.h"
#include "chrome/browser/navigation_predictor/navigation_predictor.h"
#include "chrome/browser/password_manager/chrome_password_manager_client.h"
#include "chrome/browser/predictors/network_hints_handler_impl.h"
#include "chrome/browser/prefetch/no_state_prefetch/chrome_no_state_prefetch_contents_delegate.h"
#include "chrome/browser/prefetch/no_state_prefetch/chrome_no_state_prefetch_processor_impl_delegate.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/signin/identity_manager_factory.h"
#include "chrome/browser/ssl/security_state_tab_helper.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/browser/ui/web_applications/draggable_region_host_impl.h"
#include "chrome/browser/ui/webui/bluetooth_internals/bluetooth_internals.mojom.h"
#include "chrome/browser/ui/webui/bluetooth_internals/bluetooth_internals_ui.h"
<<<<<<< HEAD
#include "chrome/browser/ui/webui/browsing_topics/browsing_topics_internals_ui.h"
#include "chrome/browser/ui/webui/chrome_urls/chrome_urls_ui.h"
#include "chrome/browser/ui/webui/data_sharing_internals/data_sharing_internals_ui.h"
#include "chrome/browser/ui/webui/engagement/site_engagement_ui.h"
#include "chrome/browser/ui/webui/location_internals/location_internals.mojom.h"
#include "chrome/browser/ui/webui/location_internals/location_internals_ui.h"
=======
#include "chrome/browser/ui/webui/engagement/site_engagement_ui.h"
#include "chrome/browser/ui/webui/federated_learning/floc_internals.mojom.h"
#include "chrome/browser/ui/webui/federated_learning/floc_internals_ui.h"
#include "chrome/browser/ui/webui/internals/internals_ui.h"
>>>>>>> chromium
#include "chrome/browser/ui/webui/media/media_engagement_ui.h"
#include "chrome/browser/ui/webui/media/media_history_ui.h"
#include "chrome/browser/ui/webui/omnibox/omnibox.mojom.h"
#include "chrome/browser/ui/webui/omnibox/omnibox_ui.h"
#include "chrome/browser/ui/webui/usb_internals/usb_internals.mojom.h"
#include "chrome/browser/ui/webui/usb_internals/usb_internals_ui.h"
#include "chrome/common/chrome_features.h"
#include "chrome/common/pref_names.h"
#include "components/contextual_search/buildflags.h"
#include "components/dom_distiller/content/browser/distillability_driver.h"
#include "components/dom_distiller/content/browser/distiller_javascript_service_impl.h"
#include "components/dom_distiller/content/common/mojom/distillability_service.mojom.h"
#include "components/dom_distiller/content/common/mojom/distiller_javascript_service.mojom.h"
#include "components/dom_distiller/core/dom_distiller_service.h"
<<<<<<< HEAD
#include "components/history_clusters/core/features.h"
#include "components/history_clusters/core/history_clusters_service.h"
#include "components/history_clusters/history_clusters_internals/webui/history_clusters_internals_ui.h"
#include "components/language_detection/content/common/language_detection.mojom.h"
#include "components/lens/lens_features.h"
#include "components/live_caption/caption_util.h"
=======
#include "components/feed/buildflags.h"
>>>>>>> chromium
#include "components/live_caption/pref_names.h"
#include "components/no_state_prefetch/browser/no_state_prefetch_contents.h"
#include "components/no_state_prefetch/browser/no_state_prefetch_processor_impl.h"
#include "components/payments/content/payment_credential_factory.h"
#include "components/performance_manager/embedder/binders.h"
#include "components/performance_manager/public/performance_manager.h"
#include "components/prefs/pref_service.h"
#include "components/reading_list/features/reading_list_switches.h"
#include "components/safe_browsing/buildflags.h"
#include "components/security_state/content/content_utils.h"
#include "components/security_state/core/security_state.h"
#include "components/signin/public/identity_manager/identity_manager.h"
#include "components/site_engagement/core/mojom/site_engagement_details.mojom.h"
#include "components/translate/content/common/translate.mojom.h"
<<<<<<< HEAD
#include "components/webui/chrome_urls/features.h"
=======
>>>>>>> chromium
#include "content/public/browser/browser_context.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/common/content_features.h"
#include "content/public/common/url_constants.h"
#include "extensions/buildflags/buildflags.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "services/image_annotation/public/mojom/image_annotation.mojom.h"
#include "third_party/blink/public/mojom/credentialmanager/credential_manager.mojom.h"
#include "third_party/blink/public/mojom/loader/navigation_predictor.mojom.h"
#include "third_party/blink/public/mojom/payments/payment_request.mojom.h"
#include "third_party/blink/public/mojom/payments/secure_payment_confirmation_service.mojom.h"
#include "third_party/blink/public/mojom/prerender/prerender.mojom.h"
#include "third_party/blink/public/public_buildflags.h"
#include "ui/webui/resources/cr_components/customize_themes/customize_themes.mojom.h"

#if BUILDFLAG(ENABLE_UNHANDLED_TAP)
#include "chrome/browser/android/contextualsearch/unhandled_tap_notifier_impl.h"
#include "chrome/browser/android/contextualsearch/unhandled_tap_web_contents_observer.h"
#include "third_party/blink/public/mojom/unhandled_tap_notifier/unhandled_tap_notifier.mojom.h"
#endif  // BUILDFLAG(ENABLE_UNHANDLED_TAP)

#if BUILDFLAG(FULL_SAFE_BROWSING)
#include "chrome/browser/ui/webui/reset_password/reset_password.mojom.h"
#include "chrome/browser/ui/webui/reset_password/reset_password_ui.h"
#endif  // BUILDFLAG(FULL_SAFE_BROWSING)

#if defined(OS_ANDROID)
#include "chrome/browser/android/contextualsearch/contextual_search_observer.h"
#include "chrome/browser/android/dom_distiller/distiller_ui_handle_android.h"
#include "chrome/browser/offline_pages/android/offline_page_auto_fetcher.h"
#include "chrome/browser/ui/webui/explore_sites_internals/explore_sites_internals.mojom.h"
#include "chrome/browser/ui/webui/explore_sites_internals/explore_sites_internals_ui.h"
#include "chrome/browser/ui/webui/feed_internals/feed_internals.mojom.h"
#include "chrome/browser/ui/webui/feed_internals/feed_internals_ui.h"
#include "chrome/common/offline_page_auto_fetcher.mojom.h"
#include "components/contextual_search/content/browser/contextual_search_js_api_service_impl.h"
#include "components/contextual_search/content/common/mojom/contextual_search_js_api_service.mojom.h"
#include "services/service_manager/public/cpp/interface_provider.h"
#include "third_party/blink/public/mojom/digital_goods/digital_goods.mojom.h"
#include "third_party/blink/public/mojom/installedapp/installed_app_provider.mojom.h"
#else
#include "chrome/browser/accessibility/live_caption_speech_recognition_host.h"
#include "chrome/browser/badging/badge_manager.h"
<<<<<<< HEAD
#include "chrome/browser/new_tab_page/modules/file_suggestion/drive_suggestion.mojom.h"
#include "chrome/browser/new_tab_page/modules/file_suggestion/microsoft_files.mojom.h"
#include "chrome/browser/new_tab_page/modules/v2/authentication/microsoft_auth.mojom.h"
#include "chrome/browser/new_tab_page/modules/v2/calendar/google_calendar.mojom.h"
#include "chrome/browser/new_tab_page/modules/v2/calendar/outlook_calendar.mojom.h"
#include "chrome/browser/new_tab_page/modules/v2/most_relevant_tab_resumption/most_relevant_tab_resumption.mojom.h"
#include "chrome/browser/new_tab_page/new_tab_page_util.h"
=======
#include "chrome/browser/cart/chrome_cart.mojom.h"
#include "chrome/browser/cart/commerce_hint_service.h"
#include "chrome/browser/new_tab_page/modules/drive/drive.mojom.h"
#include "chrome/browser/new_tab_page/modules/task_module/task_module.mojom.h"
>>>>>>> chromium
#include "chrome/browser/payments/payment_request_factory.h"
#include "chrome/browser/promo_browser_command/promo_browser_command.mojom.h"
#include "chrome/browser/speech/speech_recognition_client_browser_interface.h"
#include "chrome/browser/speech/speech_recognition_client_browser_interface_factory.h"
#include "chrome/browser/speech/speech_recognition_service.h"
#if BUILDFLAG(IS_CHROMEOS_ASH)
#include "chrome/browser/speech/cros_speech_recognition_service_factory.h"
#else
#include "chrome/browser/speech/speech_recognition_service_factory.h"
#endif
#include "chrome/browser/ui/webui/app_service_internals/app_service_internals.mojom.h"
#include "chrome/browser/ui/webui/app_service_internals/app_service_internals_ui.h"
#include "chrome/browser/ui/webui/downloads/downloads.mojom.h"
#include "chrome/browser/ui/webui/downloads/downloads_ui.h"
#include "chrome/browser/ui/webui/realbox/realbox.mojom.h"
#if !defined(OFFICIAL_BUILD)
#include "chrome/browser/ui/webui/new_tab_page/foo/foo.mojom.h"  // nogncheck crbug.com/1125897
#endif
<<<<<<< HEAD
#include "chrome/browser/ui/lens/lens_overlay_untrusted_ui.h"
#include "chrome/browser/ui/lens/lens_side_panel_untrusted_ui.h"
#include "chrome/browser/ui/views/side_panel/customize_chrome/customize_chrome_utils.h"
#include "chrome/browser/ui/webui/commerce/product_specifications_ui.h"
#include "chrome/browser/ui/webui/commerce/shopping_insights_side_panel_ui.h"
#include "chrome/browser/ui/webui/data_sharing/data_sharing.mojom.h"
#include "chrome/browser/ui/webui/data_sharing/data_sharing_ui.h"
#include "chrome/browser/ui/webui/history/history_ui.h"
#include "chrome/browser/ui/webui/new_tab_page/new_tab_page.mojom.h"
#include "chrome/browser/ui/webui/new_tab_page/new_tab_page_ui.h"
#include "chrome/browser/ui/webui/new_tab_page_third_party/new_tab_page_third_party_ui.h"
#include "chrome/browser/ui/webui/ntp_microsoft_auth/ntp_microsoft_auth_untrusted_ui.h"
#include "chrome/browser/ui/webui/omnibox_popup/omnibox_popup_ui.h"
#include "chrome/browser/ui/webui/password_manager/password_manager_ui.h"
#include "chrome/browser/ui/webui/privacy_sandbox/private_state_tokens/private_state_tokens.mojom.h"
#include "chrome/browser/ui/webui/privacy_sandbox/related_website_sets/related_website_sets.mojom.h"
#include "chrome/browser/ui/webui/search_engine_choice/search_engine_choice.mojom.h"  // nogncheck crbug.com/1125897
#include "chrome/browser/ui/webui/search_engine_choice/search_engine_choice_ui.h"
=======
#include "chrome/browser/ui/webui/download_shelf/download_shelf.mojom.h"
#include "chrome/browser/ui/webui/download_shelf/download_shelf_ui.h"
#include "chrome/browser/ui/webui/history_clusters/history_clusters.mojom.h"
#include "chrome/browser/ui/webui/history_clusters/memories_ui.h"
#include "chrome/browser/ui/webui/internals/user_education/user_education_internals.mojom.h"
#include "chrome/browser/ui/webui/new_tab_page/new_tab_page.mojom.h"
#include "chrome/browser/ui/webui/new_tab_page/new_tab_page_ui.h"
#include "chrome/browser/ui/webui/new_tab_page_third_party/new_tab_page_third_party_ui.h"
#include "chrome/browser/ui/webui/read_later/read_later.mojom.h"
#include "chrome/browser/ui/webui/read_later/read_later_ui.h"
>>>>>>> chromium
#include "chrome/browser/ui/webui/settings/settings_ui.h"
#include "chrome/browser/ui/webui/tab_search/tab_search.mojom.h"
#include "chrome/browser/ui/webui/tab_search/tab_search_ui.h"
<<<<<<< HEAD
#include "chrome/browser/ui/webui/user_education_internals/user_education_internals.mojom.h"
#include "chrome/browser/ui/webui/user_education_internals/user_education_internals_ui.h"
#include "chrome/browser/ui/webui/webui_gallery/webui_gallery_ui.h"
#include "chrome/browser/web_applications/web_install_service_impl.h"
=======
>>>>>>> chromium
#include "chrome/common/webui_url_constants.h"
#include "components/search/ntp_features.h"
#include "media/base/media_switches.h"
#include "media/mojo/mojom/speech_recognition_service.mojom.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"
#include "ui/webui/resources/cr_components/most_visited/most_visited.mojom.h"
#endif  // defined(OS_ANDROID)

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) || \
    defined(OS_CHROMEOS)
#include "chrome/browser/ui/webui/discards/discards.mojom.h"
#include "chrome/browser/ui/webui/discards/discards_ui.h"
#include "chrome/browser/ui/webui/discards/site_data.mojom.h"
#endif

#if !BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OS_ANDROID)
#include "chrome/browser/ui/webui/signin/profile_customization_ui.h"
#include "chrome/browser/ui/webui/signin/profile_picker_ui.h"
#include "ui/webui/resources/cr_components/customize_themes/customize_themes.mojom.h"
#endif  // !defined(OS_ANDROID) && !BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
#include "ash/webui/diagnostics_ui/diagnostics_ui.h"
#include "ash/webui/diagnostics_ui/mojom/input_data_provider.mojom.h"
#include "ash/webui/diagnostics_ui/mojom/network_health_provider.mojom.h"
#include "ash/webui/diagnostics_ui/mojom/system_data_provider.mojom.h"
#include "ash/webui/diagnostics_ui/mojom/system_routine_controller.mojom.h"
#include "ash/webui/file_manager/file_manager_ui.h"
#include "ash/webui/file_manager/mojom/file_manager.mojom.h"
<<<<<<< HEAD
#include "ash/webui/files_internals/files_internals_ui.h"
#include "ash/webui/files_internals/mojom/files_internals.mojom.h"
#include "ash/webui/firmware_update_ui/firmware_update_app_ui.h"
#include "ash/webui/firmware_update_ui/mojom/firmware_update.mojom.h"
#include "ash/webui/focus_mode/focus_mode_ui.h"
#include "ash/webui/focus_mode/mojom/focus_mode.mojom.h"
#include "ash/webui/graduation/graduation_ui.h"
#include "ash/webui/graduation/mojom/graduation_ui.mojom.h"
#include "ash/webui/growth_internals/growth_internals.mojom.h"
#include "ash/webui/growth_internals/growth_internals_ui.h"
#include "ash/webui/help_app_ui/help_app_ui.h"
#include "ash/webui/help_app_ui/help_app_ui.mojom.h"
#include "ash/webui/help_app_ui/help_app_untrusted_ui.h"
#include "ash/webui/help_app_ui/search/search.mojom.h"
#include "ash/webui/mall/mall_ui.h"
#include "ash/webui/mall/mall_ui.mojom.h"
#include "ash/webui/media_app_ui/media_app_guest_ui.h"
#include "ash/webui/media_app_ui/media_app_ui.h"
#include "ash/webui/media_app_ui/media_app_ui.mojom.h"
#include "ash/webui/media_app_ui/media_app_ui_untrusted.mojom.h"
#include "ash/webui/multidevice_debug/proximity_auth_ui.h"
#include "ash/webui/os_feedback_ui/mojom/os_feedback_ui.mojom.h"
#include "ash/webui/os_feedback_ui/os_feedback_ui.h"
#include "ash/webui/os_feedback_ui/os_feedback_untrusted_ui.h"
#include "ash/webui/personalization_app/mojom/personalization_app.mojom.h"
#include "ash/webui/personalization_app/personalization_app_ui.h"
#include "ash/webui/personalization_app/search/search.mojom.h"
#include "ash/webui/print_management/print_management_ui.h"
#include "ash/webui/print_preview_cros/mojom/destination_provider.mojom.h"
#include "ash/webui/print_preview_cros/print_preview_cros_ui.h"
#include "ash/webui/projector_app/mojom/untrusted_projector.mojom.h"
#include "ash/webui/projector_app/untrusted_projector_ui.h"
#include "ash/webui/recorder_app_ui/mojom/recorder_app.mojom.h"
#include "ash/webui/recorder_app_ui/recorder_app_ui.h"
#include "ash/webui/sanitize_ui/mojom/sanitize_ui.mojom.h"
#include "ash/webui/sanitize_ui/sanitize_ui.h"
#include "ash/webui/scanner_feedback_ui/mojom/scanner_feedback_ui.mojom.h"
#include "ash/webui/scanner_feedback_ui/scanner_feedback_untrusted_ui.h"
=======
>>>>>>> chromium
#include "ash/webui/scanning/mojom/scanning.mojom.h"
#include "ash/webui/scanning/scanning_ui.h"
#include "ash/webui/shimless_rma/shimless_rma.h"
#include "chrome/browser/apps/digital_goods/digital_goods_factory_impl.h"
#include "chrome/browser/nearby_sharing/common/nearby_share_features.h"
#include "chrome/browser/ui/webui/app_management/app_management.mojom.h"
#include "chrome/browser/ui/webui/chromeos/add_supervision/add_supervision.mojom.h"
#include "chrome/browser/ui/webui/chromeos/add_supervision/add_supervision_ui.h"
#include "chrome/browser/ui/webui/chromeos/crostini_installer/crostini_installer.mojom.h"
#include "chrome/browser/ui/webui/chromeos/crostini_installer/crostini_installer_ui.h"
#include "chrome/browser/ui/webui/chromeos/crostini_upgrader/crostini_upgrader.mojom.h"
#include "chrome/browser/ui/webui/chromeos/crostini_upgrader/crostini_upgrader_ui.h"
#include "chrome/browser/ui/webui/chromeos/emoji/emoji_picker.mojom.h"
#include "chrome/browser/ui/webui/chromeos/emoji/emoji_ui.h"
#include "chrome/browser/ui/webui/chromeos/in_session_password_change/lock_screen_network_ui.h"
#include "chrome/browser/ui/webui/chromeos/internet_config_dialog.h"
#include "chrome/browser/ui/webui/chromeos/internet_detail_dialog.h"
#include "chrome/browser/ui/webui/chromeos/launcher_internals/launcher_internals.mojom.h"
#include "chrome/browser/ui/webui/chromeos/launcher_internals/launcher_internals_ui.h"
#include "chrome/browser/ui/webui/chromeos/login/oobe_ui.h"
#include "chrome/browser/ui/webui/chromeos/multidevice_setup/multidevice_setup_dialog.h"
#include "chrome/browser/ui/webui/chromeos/network_ui.h"
#include "chrome/browser/ui/webui/chromeos/vm/vm.mojom.h"
#include "chrome/browser/ui/webui/chromeos/vm/vm_ui.h"
#include "chrome/browser/ui/webui/nearby_share/nearby_share.mojom.h"
#include "chrome/browser/ui/webui/nearby_share/nearby_share_dialog_ui.h"
#include "chrome/browser/ui/webui/nearby_share/public/mojom/nearby_share_settings.mojom.h"  // nogncheck crbug.com/1125897
#include "chrome/browser/ui/webui/settings/chromeos/os_settings_ui.h"
#include "chrome/browser/ui/webui/settings/chromeos/search/search.mojom.h"
#include "chrome/browser/ui/webui/settings/chromeos/search/user_action_recorder.mojom.h"
#include "chromeos/components/camera_app_ui/camera_app_helper.mojom.h"
#include "chromeos/components/camera_app_ui/camera_app_ui.h"
#include "chromeos/components/connectivity_diagnostics/connectivity_diagnostics_ui.h"
#include "chromeos/components/eche_app_ui/eche_app_ui.h"
#include "chromeos/components/eche_app_ui/mojom/eche_app.mojom.h"
#include "chromeos/components/help_app_ui/help_app_ui.h"
#include "chromeos/components/help_app_ui/help_app_ui.mojom.h"
#include "chromeos/components/help_app_ui/search/search.mojom.h"
#include "chromeos/components/local_search_service/public/mojom/index.mojom.h"
#include "chromeos/components/media_app_ui/media_app_ui.h"
#include "chromeos/components/media_app_ui/media_app_ui.mojom.h"
#include "chromeos/components/multidevice/debug_webui/proximity_auth_ui.h"
#include "chromeos/components/personalization_app/mojom/personalization_app.mojom.h"
#include "chromeos/components/personalization_app/personalization_app_ui.h"
#include "chromeos/components/print_management/mojom/printing_manager.mojom.h"
#include "chromeos/components/print_management/print_management_ui.h"
#include "chromeos/services/cellular_setup/public/mojom/cellular_setup.mojom.h"
#include "chromeos/services/cellular_setup/public/mojom/esim_manager.mojom.h"
#include "chromeos/services/multidevice_setup/multidevice_setup_service.h"
#include "chromeos/services/multidevice_setup/public/mojom/multidevice_setup.mojom.h"
#include "chromeos/services/network_config/public/mojom/cros_network_config.mojom.h"  // nogncheck
#include "chromeos/services/network_health/public/mojom/network_diagnostics.mojom.h"
#include "chromeos/services/network_health/public/mojom/network_health.mojom.h"
#include "media/capture/video/chromeos/mojom/camera_app.mojom.h"
#include "third_party/blink/public/mojom/digital_goods/digital_goods.mojom.h"
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if defined(OS_WIN) || BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC) || \
    defined(OS_ANDROID)
#if defined(OS_WIN) || BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC)
#include "chrome/browser/webshare/share_service_impl.h"
#endif
#include "third_party/blink/public/mojom/webshare/webshare.mojom.h"
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OFFICIAL_BUILD)
#include "chromeos/components/telemetry_extension_ui/mojom/diagnostics_service.mojom.h"  // nogncheck crbug.com/1125897
#include "chromeos/components/telemetry_extension_ui/mojom/probe_service.mojom.h"  // nogncheck crbug.com/1125897
#include "chromeos/components/telemetry_extension_ui/mojom/system_events_service.mojom.h"  // nogncheck crbug.com/1125897
#include "chromeos/components/telemetry_extension_ui/telemetry_extension_ui.h"
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "extensions/browser/api/mime_handler_private/mime_handler_private.h"
#include "extensions/browser/guest_view/mime_handler_view/mime_handler_view_guest.h"
#include "extensions/common/api/mime_handler.mojom.h"  // nogncheck
#endif

<<<<<<< HEAD
#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)
#include "chrome/browser/ui/webui/tab_strip/tab_strip.mojom.h"
#include "chrome/browser/ui/webui/tab_strip/tab_strip_ui.h"
#endif

#if BUILDFLAG(ENABLE_COMPOSE)
#include "chrome/browser/ui/webui/compose/compose_untrusted_ui.h"
#include "chrome/common/compose/compose.mojom.h"
#endif

#if BUILDFLAG(ENABLE_PRINT_PREVIEW)
#include "chrome/browser/printing/web_api/web_printing_service_binder.h"
#include "third_party/blink/public/mojom/printing/web_printing.mojom.h"
#endif

#if BUILDFLAG(IS_CHROMEOS)
#include "chrome/browser/ui/webui/ash/dlp_internals/dlp_internals.mojom.h"
#include "chrome/browser/ui/webui/ash/dlp_internals/dlp_internals_ui.h"
#endif

#if BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)
#include "chrome/browser/ui/webui/certificate_manager/certificate_manager_ui.h"
#include "ui/webui/resources/cr_components/certificate_manager/certificate_manager_v2.mojom.h"
#endif  // BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)

#if BUILDFLAG(ENABLE_DICE_SUPPORT)
#include "chrome/browser/ui/webui/signin/batch_upload/batch_upload.mojom.h"
#include "chrome/browser/ui/webui/signin/batch_upload_ui.h"
#include "chrome/browser/ui/webui/signin/signout_confirmation/signout_confirmation.mojom.h"
#include "chrome/browser/ui/webui/signin/signout_confirmation/signout_confirmation_ui.h"
#include "components/signin/public/base/signin_switches.h"
#endif  // BUILDFLAG(ENABLE_DICE_SUPPORT)

#if BUILDFLAG(ENABLE_GLIC)
#include "chrome/browser/glic/glic_enabling.h"
#include "chrome/browser/glic/glic_ui.h"
#endif

namespace chrome::internal {

using content::RegisterWebUIControllerInterfaceBinder;
=======
namespace chrome {
namespace internal {
>>>>>>> chromium

#if BUILDFLAG(ENABLE_UNHANDLED_TAP)
void BindUnhandledTapWebContentsObserver(
    content::RenderFrameHost* const host,
    mojo::PendingReceiver<blink::mojom::UnhandledTapNotifier> receiver) {
  auto* web_contents = content::WebContents::FromRenderFrameHost(host);
  if (!web_contents)
    return;

  auto* unhandled_tap_notifier_observer =
      contextual_search::UnhandledTapWebContentsObserver::FromWebContents(
          web_contents);
  if (!unhandled_tap_notifier_observer)
    return;

  contextual_search::CreateUnhandledTapNotifierImpl(
      unhandled_tap_notifier_observer->device_scale_factor(),
      unhandled_tap_notifier_observer->unhandled_tap_callback(),
      std::move(receiver));
}
#endif  // BUILDFLAG(ENABLE_UNHANDLED_TAP)

#if BUILDFLAG(BUILD_CONTEXTUAL_SEARCH)
void BindContextualSearchObserver(
    content::RenderFrameHost* const host,
    mojo::PendingReceiver<
        contextual_search::mojom::ContextualSearchJsApiService> receiver) {
  // Early return if the RenderFrameHost's delegate is not a WebContents.
  auto* web_contents = content::WebContents::FromRenderFrameHost(host);
  if (!web_contents)
    return;

  auto* contextual_search_observer =
      contextual_search::ContextualSearchObserver::FromWebContents(
          web_contents);
  if (contextual_search_observer) {
    contextual_search::CreateContextualSearchJsApiService(
        contextual_search_observer->api_handler(), std::move(receiver));
  }
}
#endif  // BUILDFLAG(BUILD_CONTEXTUAL_SEARCH)

// Forward image Annotator requests to the profile's AccessibilityLabelsService.
void BindImageAnnotator(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<image_annotation::mojom::Annotator> receiver) {
  AccessibilityLabelsServiceFactory::GetForProfile(
      Profile::FromBrowserContext(
          frame_host->GetProcess()->GetBrowserContext()))
      ->BindImageAnnotator(std::move(receiver));
}

#if !defined(OS_ANDROID)
void BindCommerceHintObserver(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<cart::mojom::CommerceHintObserver> receiver) {
  // Cart is not available for non-signin single-profile users.
  Profile* profile = Profile::FromBrowserContext(
      frame_host->GetProcess()->GetBrowserContext());
  auto* identity_manager = IdentityManagerFactory::GetForProfile(profile);
  ProfileManager* profile_manager = g_browser_process->profile_manager();
  if (!identity_manager || !profile_manager)
    return;
  if (!identity_manager->HasPrimaryAccount(signin::ConsentLevel::kSignin) &&
      profile_manager->GetNumberOfProfiles() <= 1)
    return;
  auto* web_contents = content::WebContents::FromRenderFrameHost(frame_host);
  if (!web_contents)
    return;
  content::BrowserContext* browser_context = web_contents->GetBrowserContext();
  if (!browser_context)
    return;
  if (browser_context->IsOffTheRecord())
    return;

  cart::CommerceHintService::CreateForWebContents(web_contents);
  cart::CommerceHintService* service =
      cart::CommerceHintService::FromWebContents(web_contents);
  if (!service)
    return;
  service->BindCommerceHintObserver(frame_host, std::move(receiver));
}
#endif

void BindDistillabilityService(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<dom_distiller::mojom::DistillabilityService>
        receiver) {
  auto* web_contents = content::WebContents::FromRenderFrameHost(frame_host);
  if (!web_contents)
    return;

  dom_distiller::DistillabilityDriver* driver =
      dom_distiller::DistillabilityDriver::FromWebContents(web_contents);
  if (!driver)
    return;
  driver->SetIsSecureCallback(
      base::BindRepeating([](content::WebContents* contents) {
        // SecurityStateTabHelper uses chrome-specific
        // GetVisibleSecurityState to determine if a page is SECURE.
        return SecurityStateTabHelper::FromWebContents(contents)
                   ->GetSecurityLevel() ==
               security_state::SecurityLevel::SECURE;
      }));
  driver->CreateDistillabilityService(std::move(receiver));
}

void BindDistillerJavaScriptService(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<dom_distiller::mojom::DistillerJavaScriptService>
        receiver) {
  auto* web_contents = content::WebContents::FromRenderFrameHost(frame_host);
  if (!web_contents)
    return;

  dom_distiller::DomDistillerService* dom_distiller_service =
      dom_distiller::DomDistillerServiceFactory::GetForBrowserContext(
          web_contents->GetBrowserContext());
  auto* distiller_ui_handle = dom_distiller_service->GetDistillerUIHandle();
#if defined(OS_ANDROID)
  static_cast<dom_distiller::android::DistillerUIHandleAndroid*>(
      distiller_ui_handle)
      ->set_render_frame_host(frame_host);
#endif
  auto* distilled_page_prefs = dom_distiller_service->GetDistilledPagePrefs();
  CreateDistillerJavaScriptService(distiller_ui_handle, distilled_page_prefs,
                                   std::move(receiver));
}

void BindPrerenderCanceler(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<prerender::mojom::PrerenderCanceler> receiver) {
  auto* web_contents = content::WebContents::FromRenderFrameHost(frame_host);
  if (!web_contents)
    return;

  auto* no_state_prefetch_contents =
      prerender::ChromeNoStatePrefetchContentsDelegate::FromWebContents(
          web_contents);
  if (!no_state_prefetch_contents)
    return;
  no_state_prefetch_contents->AddPrerenderCancelerReceiver(std::move(receiver));
}

void BindNoStatePrefetchProcessor(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<blink::mojom::NoStatePrefetchProcessor> receiver) {
  prerender::NoStatePrefetchProcessorImpl::Create(
      frame_host, std::move(receiver),
      std::make_unique<
          prerender::ChromeNoStatePrefetchProcessorImplDelegate>());
}

#if defined(OS_ANDROID)
template <typename Interface>
void ForwardToJavaWebContents(content::RenderFrameHost* frame_host,
                              mojo::PendingReceiver<Interface> receiver) {
  content::WebContents* contents =
      content::WebContents::FromRenderFrameHost(frame_host);
  if (contents)
    contents->GetJavaInterfaces()->GetInterface(std::move(receiver));
}

template <typename Interface>
void ForwardToJavaFrame(content::RenderFrameHost* render_frame_host,
                        mojo::PendingReceiver<Interface> receiver) {
  render_frame_host->GetJavaInterfaces()->GetInterface(std::move(receiver));
}
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
void BindMimeHandlerService(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<extensions::mime_handler::MimeHandlerService>
        receiver) {
  auto* web_contents = content::WebContents::FromRenderFrameHost(frame_host);
  if (!web_contents)
    return;

  auto* guest_view =
      extensions::MimeHandlerViewGuest::FromWebContents(web_contents);
  if (!guest_view)
    return;
  extensions::MimeHandlerServiceImpl::Create(guest_view->GetStreamWeakPtr(),
                                             std::move(receiver));
}

void BindBeforeUnloadControl(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<extensions::mime_handler::BeforeUnloadControl>
        receiver) {
  auto* web_contents = content::WebContents::FromRenderFrameHost(frame_host);
  if (!web_contents)
    return;

  auto* guest_view =
      extensions::MimeHandlerViewGuest::FromWebContents(web_contents);
  if (!guest_view)
    return;
  guest_view->FuseBeforeUnloadControl(std::move(receiver));
}
#endif

void BindNetworkHintsHandler(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<network_hints::mojom::NetworkHintsHandler> receiver) {
  predictors::NetworkHintsHandlerImpl::Create(frame_host, std::move(receiver));
}

#if !defined(OS_ANDROID)
void BindSpeechRecognitionContextHandler(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<media::mojom::SpeechRecognitionContext> receiver) {
  Profile* profile = Profile::FromBrowserContext(
      frame_host->GetProcess()->GetBrowserContext());
  if (media::IsLiveCaptionFeatureEnabled()) {
#if BUILDFLAG(IS_CHROMEOS_ASH)
    CrosSpeechRecognitionServiceFactory::GetForProfile(profile)->Create(
        std::move(receiver));
#else
    SpeechRecognitionServiceFactory::GetForProfile(profile)->Create(
        std::move(receiver));
#endif
  }
}

void BindSpeechRecognitionClientBrowserInterfaceHandler(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<media::mojom::SpeechRecognitionClientBrowserInterface>
        receiver) {
  if (media::IsLiveCaptionFeatureEnabled()) {
    Profile* profile = Profile::FromBrowserContext(
        frame_host->GetProcess()->GetBrowserContext());

    SpeechRecognitionClientBrowserInterfaceFactory::GetForProfile(profile)
        ->BindReceiver(std::move(receiver));
  }
}

void BindSpeechRecognitionRecognizerClientHandler(
    content::RenderFrameHost* frame_host,
    mojo::PendingReceiver<media::mojom::SpeechRecognitionRecognizerClient>
        receiver) {
  Profile* profile = Profile::FromBrowserContext(
      frame_host->GetProcess()->GetBrowserContext());
  PrefService* profile_prefs = profile->GetPrefs();
  if (profile_prefs->GetBoolean(prefs::kLiveCaptionEnabled) &&
      media::IsLiveCaptionFeatureEnabled()) {
    captions::LiveCaptionSpeechRecognitionHost::Create(frame_host,
                                                       std::move(receiver));
  }
}
#endif

void PopulateChromeFrameBinders(
    mojo::BinderMapWithContext<content::RenderFrameHost*>* map,
    content::RenderFrameHost* render_frame_host) {
  map->Add<image_annotation::mojom::Annotator>(
      base::BindRepeating(&BindImageAnnotator));

#if !defined(OS_ANDROID)
  if (base::FeatureList::IsEnabled(ntp_features::kNtpChromeCartModule) &&
      !render_frame_host->GetParent()) {
    map->Add<cart::mojom::CommerceHintObserver>(
        base::BindRepeating(&BindCommerceHintObserver));
  }
#endif

  map->Add<blink::mojom::AnchorElementMetricsHost>(
      base::BindRepeating(&NavigationPredictor::Create));

  map->Add<dom_distiller::mojom::DistillabilityService>(
      base::BindRepeating(&BindDistillabilityService));

  map->Add<dom_distiller::mojom::DistillerJavaScriptService>(
      base::BindRepeating(&BindDistillerJavaScriptService));

  map->Add<prerender::mojom::PrerenderCanceler>(
      base::BindRepeating(&BindPrerenderCanceler));

  map->Add<blink::mojom::NoStatePrefetchProcessor>(
      base::BindRepeating(&BindNoStatePrefetchProcessor));

  if (performance_manager::PerformanceManager::IsAvailable()) {
    map->Add<performance_manager::mojom::DocumentCoordinationUnit>(
        base::BindRepeating(
            &performance_manager::BindDocumentCoordinationUnit));
  }

  map->Add<translate::mojom::ContentTranslateDriver>(
<<<<<<< HEAD
      base::BindRepeating(&translate::BindContentTranslateDriver));

  if (!base::FeatureList::IsEnabled(blink::features::kLanguageDetectionAPI)) {
    // When the feature is enabled, the driver is bound by
    // browser_interface_binders.cc to make it available to JS execution
    // contexts. When the feature is disabled, we bind it here for Chrome's
    // page-translation feature.
    //
    // TODO(https://crbug.com/354069716): Remove this when the flag is removed.
    map->Add<language_detection::mojom::ContentLanguageDetectionDriver>(
        base::BindRepeating(&translate::BindContentLanguageDetectionDriver));
  }
=======
      base::BindRepeating(&language::BindContentTranslateDriver));
>>>>>>> chromium

  map->Add<blink::mojom::CredentialManager>(
      base::BindRepeating(&ChromePasswordManagerClient::BindCredentialManager));

  map->Add<payments::mojom::PaymentCredential>(
      base::BindRepeating(&payments::CreatePaymentCredential));

#if defined(OS_ANDROID)
  map->Add<blink::mojom::InstalledAppProvider>(base::BindRepeating(
      &ForwardToJavaFrame<blink::mojom::InstalledAppProvider>));
  map->Add<payments::mojom::DigitalGoodsFactory>(base::BindRepeating(
      &ForwardToJavaFrame<payments::mojom::DigitalGoodsFactory>));
#if defined(BROWSER_MEDIA_CONTROLS_MENU)
  map->Add<blink::mojom::MediaControlsMenuHost>(base::BindRepeating(
      &ForwardToJavaFrame<blink::mojom::MediaControlsMenuHost>));
#endif
  map->Add<chrome::mojom::OfflinePageAutoFetcher>(
      base::BindRepeating(&offline_pages::OfflinePageAutoFetcher::Create));
  if (base::FeatureList::IsEnabled(features::kWebPayments)) {
    map->Add<payments::mojom::PaymentRequest>(base::BindRepeating(
        &ForwardToJavaFrame<payments::mojom::PaymentRequest>));
  }
  map->Add<blink::mojom::ShareService>(base::BindRepeating(
      &ForwardToJavaWebContents<blink::mojom::ShareService>));

#if BUILDFLAG(BUILD_CONTEXTUAL_SEARCH)
  map->Add<contextual_search::mojom::ContextualSearchJsApiService>(
      base::BindRepeating(&BindContextualSearchObserver));

#if BUILDFLAG(ENABLE_UNHANDLED_TAP)
  map->Add<blink::mojom::UnhandledTapNotifier>(
      base::BindRepeating(&BindUnhandledTapWebContentsObserver));
#endif  // BUILDFLAG(ENABLE_UNHANDLED_TAP)
#endif  // BUILDFLAG(BUILD_CONTEXTUAL_SEARCH)

#else
  map->Add<blink::mojom::BadgeService>(
      base::BindRepeating(&badging::BadgeManager::BindFrameReceiver));
  if (base::FeatureList::IsEnabled(features::kWebPayments)) {
    map->Add<payments::mojom::PaymentRequest>(
        base::BindRepeating(&payments::CreatePaymentRequest));
  }
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
  map->Add<payments::mojom::DigitalGoodsFactory>(base::BindRepeating(
      &apps::DigitalGoodsFactoryImpl::BindDigitalGoodsFactory));
#endif

#if defined(OS_WIN) || BUILDFLAG(IS_CHROMEOS_ASH) || defined(OS_MAC)
  if (base::FeatureList::IsEnabled(features::kWebShare)) {
    map->Add<blink::mojom::ShareService>(
        base::BindRepeating(&ShareServiceImpl::Create));
  }
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
  map->Add<extensions::mime_handler::MimeHandlerService>(
      base::BindRepeating(&BindMimeHandlerService));
  map->Add<extensions::mime_handler::BeforeUnloadControl>(
      base::BindRepeating(&BindBeforeUnloadControl));
#endif

  map->Add<network_hints::mojom::NetworkHintsHandler>(
      base::BindRepeating(&BindNetworkHintsHandler));

#if !defined(OS_ANDROID)
  map->Add<media::mojom::SpeechRecognitionContext>(
      base::BindRepeating(&BindSpeechRecognitionContextHandler));
  map->Add<media::mojom::SpeechRecognitionClientBrowserInterface>(
      base::BindRepeating(&BindSpeechRecognitionClientBrowserInterfaceHandler));
  map->Add<media::mojom::SpeechRecognitionRecognizerClient>(
      base::BindRepeating(&BindSpeechRecognitionRecognizerClientHandler));
<<<<<<< HEAD
#if BUILDFLAG(IS_WIN)
  map->Add<media::mojom::MediaFoundationRendererNotifier>(
      base::BindRepeating(&BindMediaFoundationRendererNotifierHandler));
#endif
#endif  // BUILDFLAG(ENABLE_SPEECH_SERVICE)

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS)
  if (base::FeatureList::IsEnabled(blink::features::kDesktopPWAsSubApps) &&
      !render_frame_host->GetParentOrOuterDocument()) {
    // The service binder will reject non-primary main frames, but we still need
    // to register it for them because a non-primary main frame could become a
    // primary main frame at a later time (eg. a prerendered page).
    map->Add<blink::mojom::SubAppsService>(
        base::BindRepeating(&web_app::SubAppsServiceImpl::CreateIfAllowed));
  }

  map->Add<screen_ai::mojom::ScreenAIAnnotator>(
      base::BindRepeating(&BindScreenAIAnnotator));

  map->Add<screen_ai::mojom::Screen2xMainContentExtractor>(
      base::BindRepeating(&BindScreen2xMainContentExtractor));
#endif

#if BUILDFLAG(IS_WIN)
  map->Add<media::mojom::MediaFoundationPreferences>(
      base::BindRepeating(&BindMediaFoundationPreferences));
#endif

#if BUILDFLAG(ENABLE_PRINT_PREVIEW)
  map->Add<blink::mojom::WebPrintingService>(
      base::BindRepeating(&printing::CreateWebPrintingServiceForFrame));
#endif

#if BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(blink::features::kPaymentLinkDetection)) {
    map->Add<payments::facilitated::mojom::PaymentLinkHandler>(
        base::BindRepeating(&BindPaymentLinkHandler));
=======
#endif

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX)
  if (!render_frame_host->GetParent()) {
    map->Add<chrome::mojom::DraggableRegions>(
        base::BindRepeating(&DraggableRegionsHostImpl::CreateIfAllowed));
>>>>>>> chromium
  }
#endif
}

void PopulateChromeWebUIFrameBinders(
    mojo::BinderMapWithContext<content::RenderFrameHost*>* map) {
  RegisterWebUIControllerInterfaceBinder<::mojom::BluetoothInternalsHandler,
                                         BluetoothInternalsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      media::mojom::MediaEngagementScoreDetailsProvider, MediaEngagementUI>(
      map);

  RegisterWebUIControllerInterfaceBinder<
      media_history::mojom::MediaHistoryStore, MediaHistoryUI>(map);

  RegisterWebUIControllerInterfaceBinder<::mojom::OmniboxPageHandler,
                                         OmniboxUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      site_engagement::mojom::SiteEngagementDetailsProvider, SiteEngagementUI>(
      map);

  RegisterWebUIControllerInterfaceBinder<::mojom::UsbInternalsPageHandler,
                                         UsbInternalsUI>(map);

  RegisterWebUIControllerInterfaceBinder<federated_learning::mojom::PageHandler,
                                         FlocInternalsUI>(map);

#if defined(OS_ANDROID)
  RegisterWebUIControllerInterfaceBinder<
<<<<<<< HEAD
      history_clusters_internals::mojom::PageHandlerFactory,
      HistoryClustersInternalsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      optimization_guide_internals::mojom::PageHandlerFactory,
      OptimizationGuideInternalsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      segmentation_internals::mojom::PageHandlerFactory,
      SegmentationInternalsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      commerce::mojom::CommerceInternalsHandlerFactory,
      commerce::CommerceInternalsUI>(map);

  if (base::FeatureList::IsEnabled(chrome_urls::kInternalOnlyUisPref)) {
    RegisterWebUIControllerInterfaceBinder<
        chrome_urls::mojom::PageHandlerFactory, chrome_urls::ChromeUrlsUI>(map);
  }

  RegisterWebUIControllerInterfaceBinder<
      data_sharing_internals::mojom::PageHandlerFactory,
      DataSharingInternalsUI>(map);

#if BUILDFLAG(ENABLE_GLIC)
  if (GlicEnabling::IsProfileEligible(Profile::FromBrowserContext(
          render_frame_host->GetProcess()->GetBrowserContext()))) {
    // Register the binder for all eligible profiles but the WebUI page will
    // check whether Glic is policy-enabled and restrict access if needed.
    RegisterWebUIControllerInterfaceBinder<glic::mojom::PageHandlerFactory,
                                           glic::GlicUI>(map);
  }
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
    BUILDFLAG(IS_CHROMEOS_ASH)
  RegisterWebUIControllerInterfaceBinder<
      connectors_internals::mojom::PageHandler,
      enterprise_connectors::ConnectorsInternalsUI>(map);
#endif

#if BUILDFLAG(IS_CHROMEOS)
  RegisterWebUIControllerInterfaceBinder<dlp_internals::mojom::PageHandler,
                                         policy::DlpInternalsUI>(map);
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  RegisterWebUIControllerInterfaceBinder<
      app_management::mojom::PageHandlerFactory, WebAppSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      on_device_translation_internals::mojom::PageHandlerFactory,
      OnDeviceTranslationInternalsUI>(map);
#endif

#if !BUILDFLAG(IS_ANDROID)
  RegisterWebUIControllerInterfaceBinder<
      search_engine_choice::mojom::PageHandlerFactory, SearchEngineChoiceUI>(
      map);

=======
      explore_sites_internals::mojom::PageHandler,
      explore_sites::ExploreSitesInternalsUI>(map);
#else
>>>>>>> chromium
  RegisterWebUIControllerInterfaceBinder<downloads::mojom::PageHandlerFactory,
                                         DownloadsUI>(map);
#endif

  RegisterWebUIControllerInterfaceBinder<
      new_tab_page_third_party::mojom::PageHandlerFactory,
      NewTabPageThirdPartyUI>(map);

<<<<<<< HEAD
  if (lens::features::IsLensOverlayEnabled()) {
    RegisterWebUIControllerInterfaceBinder<
        lens::mojom::LensSidePanelPageHandlerFactory,
        lens::LensSidePanelUntrustedUI>(map);
    RegisterWebUIControllerInterfaceBinder<lens::mojom::LensPageHandlerFactory,
                                           lens::LensOverlayUntrustedUI>(map);
  }

  RegisterWebUIControllerInterfaceBinder<
      color_change_listener::mojom::PageHandler,
#if BUILDFLAG(ENABLE_WEBUI_TAB_STRIP)
      TabStripUI,
#endif
#if BUILDFLAG(IS_CHROMEOS_ASH)
      ash::OobeUI, ash::personalization_app::PersonalizationAppUI,
      ash::vc_background_ui::VcBackgroundUI, ash::settings::OSSettingsUI,
      ash::DiagnosticsDialogUI, ash::FirmwareUpdateAppUI, ash::ScanningUI,
      ash::OSFeedbackUI, ash::ShortcutCustomizationAppUI,
      ash::printing::printing_manager::PrintManagementUI,
      ash::InternetConfigDialogUI, ash::InternetDetailDialogUI, ash::SetTimeUI,
      ash::BluetoothPairingDialogUI, nearby_share::NearbyShareDialogUI,
      ash::cloud_upload::CloudUploadUI, ash::office_fallback::OfficeFallbackUI,
      ash::multidevice_setup::MultiDeviceSetupDialogUI, ash::ParentAccessUI,
      ash::EmojiUI, ash::RemoteMaintenanceCurtainUI,
      ash::app_install::AppInstallDialogUI, ash::SanitizeDialogUI,
      ash::printing::print_preview::PrintPreviewCrosUI,
      ash::extended_updates::ExtendedUpdatesUI, ash::graduation::GraduationUI,
      policy::local_user_files::LocalFilesMigrationUI,
#endif
      NewTabPageUI, OmniboxPopupUI, BookmarksSidePanelUI, CustomizeChromeUI,
      UserEducationInternalsUI, ReadingListUI, TabSearchUI, WebuiGalleryUI,
      HistoryClustersSidePanelUI, ShoppingInsightsSidePanelUI,
      media_router::AccessCodeCastUI, commerce::ProductSpecificationsUI>(map);

=======
>>>>>>> chromium
  RegisterWebUIControllerInterfaceBinder<
      new_tab_page::mojom::PageHandlerFactory, NewTabPageUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      most_visited::mojom::MostVisitedPageHandlerFactory, NewTabPageUI,
      NewTabPageThirdPartyUI>(map);

<<<<<<< HEAD
  auto* history_clusters_service =
      HistoryClustersServiceFactory::GetForBrowserContext(
          render_frame_host->GetProcess()->GetBrowserContext());
  if (history_clusters_service &&
      history_clusters_service->is_journeys_feature_flag_enabled()) {
    RegisterWebUIControllerInterfaceBinder<history_clusters::mojom::PageHandler,
                                           HistoryUI,
                                           HistoryClustersSidePanelUI>(map);
  }
  if (history_embeddings::IsHistoryEmbeddingsFeatureEnabled()) {
    if (history_clusters_service &&
        history_clusters_service->is_journeys_feature_flag_enabled()) {
      RegisterWebUIControllerInterfaceBinder<
          history_embeddings::mojom::PageHandler, HistoryUI,
          HistoryClustersSidePanelUI>(map);
    } else {
      RegisterWebUIControllerInterfaceBinder<
          history_embeddings::mojom::PageHandler, HistoryUI>(map);
    }
  }
=======
  RegisterWebUIControllerInterfaceBinder<history_clusters::mojom::PageHandler,
                                         MemoriesUI>(map);
>>>>>>> chromium

  RegisterWebUIControllerInterfaceBinder<
      promo_browser_command::mojom::CommandHandler, NewTabPageUI>(map);

  RegisterWebUIControllerInterfaceBinder<realbox::mojom::PageHandler,
                                         NewTabPageUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      customize_themes::mojom::CustomizeThemesHandlerFactory, NewTabPageUI
#if !BUILDFLAG(IS_CHROMEOS_ASH)
      ,
      ProfileCustomizationUI, ProfilePickerUI, settings::SettingsUI
#endif  // !BUILDFLAG(IS_CHROMEOS_ASH)
      >(map);

<<<<<<< HEAD
#if BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)
  RegisterWebUIControllerInterfaceBinder<
      certificate_manager_v2::mojom::CertificateManagerPageHandlerFactory,
      CertificateManagerUI>(map);
#endif  // BUILDFLAG(CHROME_ROOT_STORE_CERT_MANAGEMENT_UI)

  RegisterWebUIControllerInterfaceBinder<
      help_bubble::mojom::HelpBubbleHandlerFactory, UserEducationInternalsUI,
      settings::SettingsUI, ReadingListUI, NewTabPageUI, CustomizeChromeUI,
      PasswordManagerUI, HistoryUI, lens::LensOverlayUntrustedUI,
      lens::LensSidePanelUntrustedUI
#if !BUILDFLAG(IS_CHROMEOS_ASH) && !BUILDFLAG(IS_ANDROID)
      ,
      ProfilePickerUI
#endif  //! BUILDFLAG(IS_CHROMEOS_ASH) && !BUILDFLAG(IS_ANDROID)
      >(map);

=======
>>>>>>> chromium
#if !defined(OFFICIAL_BUILD)
  RegisterWebUIControllerInterfaceBinder<foo::mojom::FooHandler, NewTabPageUI>(
      map);
#endif  // !defined(OFFICIAL_BUILD)

  if (base::FeatureList::IsEnabled(ntp_features::kNtpChromeCartModule)) {
    RegisterWebUIControllerInterfaceBinder<chrome_cart::mojom::CartHandler,
                                           NewTabPageUI>(map);
  }

  if (base::FeatureList::IsEnabled(ntp_features::kNtpDriveModule)) {
    RegisterWebUIControllerInterfaceBinder<drive::mojom::DriveHandler,
                                           NewTabPageUI>(map);
  }

  if (base::FeatureList::IsEnabled(ntp_features::kNtpRecipeTasksModule) ||
      base::FeatureList::IsEnabled(ntp_features::kNtpShoppingTasksModule)) {
    RegisterWebUIControllerInterfaceBinder<
        task_module::mojom::TaskModuleHandler, NewTabPageUI>(map);
  }

<<<<<<< HEAD
  if (IsOutlookCalendarModuleEnabledForProfile(Profile::FromBrowserContext(
          render_frame_host->GetBrowserContext()))) {
=======
  if (reading_list::switches::IsReadingListEnabled()) {
>>>>>>> chromium
    RegisterWebUIControllerInterfaceBinder<
        read_later::mojom::PageHandlerFactory, ReadLaterUI>(map);
  }

<<<<<<< HEAD
  if (IsMicrosoftModuleEnabledForProfile(Profile::FromBrowserContext(
          render_frame_host->GetBrowserContext()))) {
    RegisterWebUIControllerInterfaceBinder<
        ntp::authentication::mojom::MicrosoftAuthPageHandler, NewTabPageUI>(
        map);
  }

  if (IsMicrosoftFilesModuleEnabledForProfile(Profile::FromBrowserContext(
          render_frame_host->GetBrowserContext()))) {
    RegisterWebUIControllerInterfaceBinder<
        file_suggestion::mojom::MicrosoftFilesPageHandler, NewTabPageUI>(map);
  }

#if BUILDFLAG(IS_CHROMEOS_ASH)
  RegisterWebUIControllerInterfaceBinder<
      ash::mojom::HidPreservingBluetoothStateController,
      ash::settings::OSSettingsUI>(map);
#endif  // defined(IS_CHROMEOS_ASH)

  RegisterWebUIControllerInterfaceBinder<
      reading_list::mojom::PageHandlerFactory, ReadingListUI>(map);
  RegisterWebUIControllerInterfaceBinder<
      side_panel::mojom::BookmarksPageHandlerFactory, BookmarksSidePanelUI>(
      map);

  RegisterWebUIControllerInterfaceBinder<
      shopping_service::mojom::ShoppingServiceHandlerFactory,
      BookmarksSidePanelUI, commerce::ProductSpecificationsUI,
      ShoppingInsightsSidePanelUI, HistoryUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      commerce::product_specifications::mojom::
          ProductSpecificationsHandlerFactory,
      commerce::ProductSpecificationsUI, HistoryUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      commerce::price_tracking::mojom::PriceTrackingHandlerFactory,
      ShoppingInsightsSidePanelUI, BookmarksSidePanelUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      commerce::price_insights::mojom::PriceInsightsHandlerFactory,
      ShoppingInsightsSidePanelUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      side_panel::mojom::CustomizeChromePageHandlerFactory, CustomizeChromeUI>(
      map);

  if (base::FeatureList::IsEnabled(
          ntp_features::kCustomizeChromeWallpaperSearch) &&
      base::FeatureList::IsEnabled(
          optimization_guide::features::kOptimizationGuideModelExecution)) {
    RegisterWebUIControllerInterfaceBinder<
        side_panel::customize_chrome::mojom::WallpaperSearchHandlerFactory,
        CustomizeChromeUI>(map);
  }

  if (features::IsToolbarPinningEnabled()) {
    RegisterWebUIControllerInterfaceBinder<
        side_panel::customize_chrome::mojom::CustomizeToolbarHandlerFactory,
        CustomizeChromeUI>(map);
  }

  RegisterWebUIControllerInterfaceBinder<
      read_anything::mojom::UntrustedPageHandlerFactory,
      ReadAnythingUntrustedUI>(map);
=======
  if (base::FeatureList::IsEnabled(features::kSidePanel)) {
    RegisterWebUIControllerInterfaceBinder<
        side_panel::mojom::BookmarksPageHandlerFactory, ReadLaterUI>(map);
  }
>>>>>>> chromium

  RegisterWebUIControllerInterfaceBinder<tab_search::mojom::PageHandlerFactory,
                                         TabSearchUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      download_shelf::mojom::PageHandlerFactory, DownloadShelfUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ::mojom::user_education_internals::UserEducationInternalsPageHandler,
      UserEducationInternalsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ::mojom::app_service_internals::AppServiceInternalsPageHandler,
      AppServiceInternalsUI>(map);
#endif  // defined(OS_ANDROID)

#if BUILDFLAG(IS_CHROMEOS_ASH)
  RegisterWebUIControllerInterfaceBinder<
      ash::file_manager::mojom::PageHandlerFactory,
      ash::file_manager::FileManagerUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      add_supervision::mojom::AddSupervisionHandler,
      chromeos::AddSupervisionUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      app_management::mojom::PageHandlerFactory,
      chromeos::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::settings::mojom::UserActionRecorder,
      chromeos::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::settings::mojom::SearchHandler,
      chromeos::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::cellular_setup::mojom::CellularSetup,
      chromeos::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::cellular_setup::mojom::ESimManager,
      chromeos::settings::OSSettingsUI, chromeos::NetworkUI, chromeos::OobeUI>(
      map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::crostini_installer::mojom::PageHandlerFactory,
      chromeos::CrostiniInstallerUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::crostini_upgrader::mojom::PageHandlerFactory,
      chromeos::CrostiniUpgraderUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::multidevice_setup::mojom::MultiDeviceSetup, chromeos::OobeUI,
      chromeos::multidevice::ProximityAuthUI,
      chromeos::multidevice_setup::MultiDeviceSetupDialogUI>(map);

  RegisterWebUIControllerInterfaceBinder<
<<<<<<< HEAD
      ash::settings::app_notification::mojom::AppNotificationsHandler,
      ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::settings::app_permission::mojom::AppPermissionsHandler,
      ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::settings::app_parental_controls::mojom::AppParentalControlsHandler,
      ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::settings::mojom::InputDeviceSettingsProvider,
      ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::settings::mojom::DisplaySettingsProvider,
      ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<ash::common::mojom::AcceleratorFetcher,
                                         ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::common::mojom::ShortcutInputProvider, ash::settings::OSSettingsUI,
      ash::ShortcutCustomizationAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::settings::graduation::mojom::GraduationHandler,
      ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::cellular_setup::mojom::CellularSetup, ash::settings::OSSettingsUI>(
      map);

  RegisterWebUIControllerInterfaceBinder<chromeos::auth::mojom::InSessionAuth,
                                         ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<ash::auth::mojom::AuthFactorConfig,
                                         ash::settings::OSSettingsUI,
                                         ash::OobeUI>(map);

  RegisterWebUIControllerInterfaceBinder<ash::auth::mojom::RecoveryFactorEditor,
                                         ash::settings::OSSettingsUI>(map);

  RegisterWebUIControllerInterfaceBinder<ash::auth::mojom::PinFactorEditor,
                                         ash::settings::OSSettingsUI,
                                         ash::OobeUI>(map);

  RegisterWebUIControllerInterfaceBinder<ash::auth::mojom::PasswordFactorEditor,
                                         ash::settings::OSSettingsUI,
                                         ash::OobeUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::cellular_setup::mojom::ESimManager, ash::settings::OSSettingsUI,
      ash::NetworkUI, ash::OobeUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::borealis_installer::mojom::PageHandlerFactory,
      ash::BorealisInstallerUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::crostini_installer::mojom::PageHandlerFactory,
      ash::CrostiniInstallerUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::crostini_upgrader::mojom::PageHandlerFactory,
      ash::CrostiniUpgraderUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::multidevice_setup::mojom::MultiDeviceSetup, ash::OobeUI,
      ash::multidevice::ProximityAuthUI,
      ash::multidevice_setup::MultiDeviceSetupDialogUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      parent_access_ui::mojom::ParentAccessUiHandler, ash::ParentAccessUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::multidevice_setup::mojom::PrivilegedHostDeviceSetter, ash::OobeUI>(
      map);
=======
      chromeos::multidevice_setup::mojom::PrivilegedHostDeviceSetter,
      chromeos::OobeUI>(map);
>>>>>>> chromium

  RegisterWebUIControllerInterfaceBinder<
      chromeos::network_config::mojom::CrosNetworkConfig,
      chromeos::InternetConfigDialogUI, chromeos::InternetDetailDialogUI,
      chromeos::NetworkUI, chromeos::OobeUI, chromeos::settings::OSSettingsUI,
      chromeos::LockScreenNetworkUI, ash::ShimlessRMADialogUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::printing::printing_manager::mojom::PrintingMetadataProvider,
      chromeos::printing::printing_manager::PrintManagementUI>(map);

  RegisterWebUIControllerInterfaceBinder<cros::mojom::CameraAppDeviceProvider,
                                         chromeos::CameraAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos_camera::mojom::CameraAppHelper, chromeos::CameraAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<help_app_ui::mojom::PageHandlerFactory,
                                         chromeos::HelpAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::local_search_service::mojom::Index, chromeos::HelpAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::help_app::mojom::SearchHandler, chromeos::HelpAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::eche_app::mojom::SignalingMessageExchanger,
      chromeos::eche_app::EcheAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::eche_app::mojom::SystemInfoProvider,
      chromeos::eche_app::EcheAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::eche_app::mojom::UidGenerator, chromeos::eche_app::EcheAppUI>(
      map);

  RegisterWebUIControllerInterfaceBinder<
      media_app_ui::mojom::PageHandlerFactory, chromeos::MediaAppUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::network_health::mojom::NetworkHealthService,
      chromeos::NetworkUI, chromeos::ConnectivityDiagnosticsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::network_diagnostics::mojom::NetworkDiagnosticsRoutines,
      chromeos::NetworkUI, chromeos::ConnectivityDiagnosticsUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      ash::diagnostics::mojom::InputDataProvider, ash::DiagnosticsDialogUI>(
      map);

  if (chromeos::features::IsNetworkingInDiagnosticsAppEnabled()) {
    RegisterWebUIControllerInterfaceBinder<
        ash::diagnostics::mojom::NetworkHealthProvider,
        ash::DiagnosticsDialogUI>(map);
  }

  RegisterWebUIControllerInterfaceBinder<
      ash::diagnostics::mojom::SystemDataProvider, ash::DiagnosticsDialogUI>(
      map);

  RegisterWebUIControllerInterfaceBinder<
      ash::diagnostics::mojom::SystemRoutineController,
      ash::DiagnosticsDialogUI>(map);

  RegisterWebUIControllerInterfaceBinder<
      chromeos::vm::mojom::VmDiagnosticsProvider, chromeos::VmUI>(map);

  RegisterWebUIControllerInterfaceBinder<ash::scanning::mojom::ScanService,
                                         ash::ScanningUI>(map);

  // TODO(crbug.com/1218492): When boot RMA state is available disable this when
  // not in RMA.
  if (ash::features::IsShimlessRMAFlowEnabled()) {
    RegisterWebUIControllerInterfaceBinder<
        ash::shimless_rma::mojom::ShimlessRmaService, ash::ShimlessRMADialogUI>(
        map);
  }

  if (base::FeatureList::IsEnabled(chromeos::features::kImeSystemEmojiPicker)) {
    RegisterWebUIControllerInterfaceBinder<
        emoji_picker::mojom::PageHandlerFactory, chromeos::EmojiUI>(map);
  }

  if (chromeos::features::IsWallpaperWebUIEnabled()) {
    RegisterWebUIControllerInterfaceBinder<
        chromeos::personalization_app::mojom::WallpaperProvider,
        chromeos::PersonalizationAppUI>(map);
  }

  RegisterWebUIControllerInterfaceBinder<
      launcher_internals::mojom::PageHandlerFactory,
      chromeos::LauncherInternalsUI>(map);
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OFFICIAL_BUILD)
  if (base::FeatureList::IsEnabled(chromeos::features::kTelemetryExtension)) {
    RegisterWebUIControllerInterfaceBinder<
        chromeos::health::mojom::DiagnosticsService,
        chromeos::TelemetryExtensionUI>(map);
    RegisterWebUIControllerInterfaceBinder<
        chromeos::health::mojom::ProbeService, chromeos::TelemetryExtensionUI>(
        map);
    RegisterWebUIControllerInterfaceBinder<
        chromeos::health::mojom::SystemEventsService,
        chromeos::TelemetryExtensionUI>(map);
  }
#endif

#if defined(OS_WIN) || defined(OS_MAC) || defined(OS_LINUX) || \
    defined(OS_CHROMEOS)
  RegisterWebUIControllerInterfaceBinder<discards::mojom::DetailsProvider,
                                         DiscardsUI>(map);

  RegisterWebUIControllerInterfaceBinder<discards::mojom::GraphDump,
                                         DiscardsUI>(map);

  RegisterWebUIControllerInterfaceBinder<discards::mojom::SiteDataProvider,
                                         DiscardsUI>(map);
#endif

#if BUILDFLAG(ENABLE_FEED_V2)
  RegisterWebUIControllerInterfaceBinder<feed_internals::mojom::PageHandler,
                                         FeedInternalsUI>(map);
#endif

#if BUILDFLAG(FULL_SAFE_BROWSING)
  RegisterWebUIControllerInterfaceBinder<::mojom::ResetPasswordHandler,
                                         ResetPasswordUI>(map);
#endif

#if BUILDFLAG(IS_CHROMEOS_ASH)
  // Because Nearby Share is only currently supported for the primary profile,
  // we should only register binders in that scenario. However, we don't want to
  // plumb the profile through to this function, so we 1) ensure that
  // NearbyShareDialogUI will not be created for non-primary profiles, and 2)
  // rely on the BindInterface implementation of OSSettingsUI to ensure that no
  // Nearby Share receivers are bound.
<<<<<<< HEAD
  RegisterWebUIControllerInterfaceBinder<
      nearby_share::mojom::NearbyShareSettings, ash::settings::OSSettingsUI,
      nearby_share::NearbyShareDialogUI>(map);
  RegisterWebUIControllerInterfaceBinder<nearby_share::mojom::ContactManager,
                                         ash::settings::OSSettingsUI,
                                         nearby_share::NearbyShareDialogUI>(
      map);
  RegisterWebUIControllerInterfaceBinder<nearby_share::mojom::DiscoveryManager,
                                         nearby_share::NearbyShareDialogUI>(
      map);
  RegisterWebUIControllerInterfaceBinder<nearby_share::mojom::ReceiveManager,
                                         ash::settings::OSSettingsUI>(map);
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_ANDROID)
  RegisterWebUIControllerInterfaceBinder<::app_home::mojom::PageHandlerFactory,
                                         webapps::AppHomeUI>(map);
#endif  // !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
  RegisterWebUIControllerInterfaceBinder<::mojom::WebAppInternalsHandler,
                                         WebAppInternalsUI>(map);
#endif

  RegisterWebUIControllerInterfaceBinder<::mojom::LocationInternalsHandler,
                                         LocationInternalsUI>(map);

#if !BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(
          optimization_guide::features::kOptimizationGuideOnDeviceModel)) {
    RegisterWebUIControllerInterfaceBinder<
        ::mojom::OnDeviceInternalsPageHandlerFactory, OnDeviceInternalsUI>(map);
  }
#endif

  if (base::FeatureList::IsEnabled(
          privacy_sandbox::kPrivacySandboxInternalsDevUI)) {
    RegisterWebUIControllerInterfaceBinder<
        privacy_sandbox_internals::mojom::PageHandler,
        privacy_sandbox_internals::PrivacySandboxInternalsUI>(map);
  }

#if !BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(privacy_sandbox::kRelatedWebsiteSetsDevUI)) {
    RegisterWebUIControllerInterfaceBinder<
        related_website_sets::mojom::RelatedWebsiteSetsPageHandler,
        privacy_sandbox_internals::PrivacySandboxInternalsUI>(map);
  }

  if (base::FeatureList::IsEnabled(privacy_sandbox::kPrivateStateTokensDevUI)) {
    RegisterWebUIControllerInterfaceBinder<
        private_state_tokens::mojom::PrivateStateTokensPageHandler,
        privacy_sandbox_internals::PrivacySandboxInternalsUI>(map);
  }
#endif

#if BUILDFLAG(ENABLE_DICE_SUPPORT)
  if (base::FeatureList::IsEnabled(switches::kBatchUploadDesktop)) {
    RegisterWebUIControllerInterfaceBinder<
        batch_upload::mojom::PageHandlerFactory, BatchUploadUI>(map);
  }

  RegisterWebUIControllerInterfaceBinder<
      signout_confirmation::mojom::PageHandlerFactory, SignoutConfirmationUI>(
      map);
#endif  // BUILDFLAG(ENABLE_DICE_SUPPORT)

#if BUILDFLAG(IS_CHROMEOS_ASH)
  if (ash::features::IsFocusModeEnabled()) {
    RegisterWebUIControllerInterfaceBinder<
        ash::focus_mode::mojom::TrackProvider, ash::FocusModeUI>(map);
  }
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
  RegisterWebUIControllerInterfaceBinder<
      ash::sanitize_ui::mojom::SettingsResetter, ash::SanitizeDialogUI>(map);
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
  if (ash::features::IsGraduationEnabled()) {
    RegisterWebUIControllerInterfaceBinder<
        ash::graduation_ui::mojom::GraduationUiHandler,
        ash::graduation::GraduationUI>(map);
=======
  if (base::FeatureList::IsEnabled(features::kNearbySharing)) {
    RegisterWebUIControllerInterfaceBinder<
        nearby_share::mojom::NearbyShareSettings,
        chromeos::settings::OSSettingsUI, nearby_share::NearbyShareDialogUI>(
        map);
    RegisterWebUIControllerInterfaceBinder<nearby_share::mojom::ContactManager,
                                           chromeos::settings::OSSettingsUI,
                                           nearby_share::NearbyShareDialogUI>(
        map);
    RegisterWebUIControllerInterfaceBinder<
        nearby_share::mojom::DiscoveryManager,
        nearby_share::NearbyShareDialogUI>(map);
    RegisterWebUIControllerInterfaceBinder<nearby_share::mojom::ReceiveManager,
                                           chromeos::settings::OSSettingsUI>(
        map);
>>>>>>> chromium
  }
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)
}

<<<<<<< HEAD
void PopulateChromeWebUIFrameInterfaceBrokers(
    content::WebUIBrowserInterfaceBrokerRegistry& registry) {
  // This function is broken up into sections based on WebUI types.

  // --- Section 1: chrome:// WebUIs:

#if BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OFFICIAL_BUILD)
  registry.ForWebUI<ash::SampleSystemWebAppUI>()
      .Add<ash::mojom::sample_swa::PageHandlerFactory>()
      .Add<color_change_listener::mojom::PageHandler>();

  registry.ForWebUI<ash::StatusAreaInternalsUI>()
      .Add<ash::mojom::status_area_internals::PageHandler>();
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OFFICIAL_BUILD)

#if BUILDFLAG(IS_CHROMEOS_ASH)
  registry.ForWebUI<ash::RecorderAppUI>()
      .Add<ash::recorder_app::mojom::PageHandler>()
      .Add<color_change_listener::mojom::PageHandler>()
      .Add<crosapi::mojom::StructuredMetricsService>();
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH)
  registry.ForWebUI<ash::CameraAppUI>()
      .Add<color_change_listener::mojom::PageHandler>()
      .Add<cros::mojom::CameraAppDeviceProvider>()
      .Add<ash::camera_app::mojom::CameraAppHelper>();
  registry.ForWebUI<ash::ColorInternalsUI>()
      .Add<color_change_listener::mojom::PageHandler>()
      .Add<ash::color_internals::mojom::WallpaperColorsHandler>();
  registry.ForWebUI<ash::FilesInternalsUI>()
      .Add<ash::mojom::files_internals::PageHandler>();
  registry.ForWebUI<ash::file_manager::FileManagerUI>()
      .Add<color_change_listener::mojom::PageHandler>();
  registry.ForWebUI<ash::smb_dialog::SmbShareDialogUI>()
      .Add<color_change_listener::mojom::PageHandler>();
  registry.ForWebUI<ash::smb_dialog::SmbCredentialsDialogUI>()
      .Add<color_change_listener::mojom::PageHandler>();
  registry.ForWebUI<FeedbackUI>()
      .Add<color_change_listener::mojom::PageHandler>();
  registry.ForWebUI<ash::MallUI>().Add<ash::mall::mojom::PageHandler>();
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

  // --- Section 2: chrome-untrusted:// WebUIs:
#if BUILDFLAG(IS_CHROMEOS_ASH)
  registry.ForWebUI<ash::boca::BocaUI>()
      .Add<ash::boca::mojom::BocaPageHandlerFactory>()
      .Add<color_change_listener::mojom::PageHandler>();

  if (chromeos::features::IsOrcaEnabled() ||
      ash::features::IsLobsterEnabled()) {
    registry.ForWebUI<ash::MakoUntrustedUI>()
        .Add<ash::orca::mojom::EditorClient>()
        .Add<lobster::mojom::UntrustedLobsterPageHandler>();
  }

  registry.ForWebUI<ash::DemoModeAppUntrustedUI>()
      .Add<ash::mojom::demo_mode::UntrustedPageHandlerFactory>();

  registry.ForWebUI<ash::UntrustedAnnotatorUI>()
      .Add<ash::annotator::mojom::UntrustedAnnotatorPageHandlerFactory>();

  registry.ForWebUI<ash::UntrustedProjectorUI>()
      .Add<color_change_listener::mojom::PageHandler>()
      .Add<ash::projector::mojom::UntrustedProjectorPageHandlerFactory>();

  registry.ForWebUI<ash::feedback::OsFeedbackUntrustedUI>()
      .Add<color_change_listener::mojom::PageHandler>();

  registry.ForWebUI<ash::MediaAppGuestUI>()
      .Add<color_change_listener::mojom::PageHandler>()
      .Add<ash::media_app_ui::mojom::UntrustedServiceFactory>();

  registry.ForWebUI<ash::HelpAppUntrustedUI>()
      .Add<color_change_listener::mojom::PageHandler>();

  registry.ForWebUI<ash::ScannerFeedbackUntrustedUI>()
      .Add<color_change_listener::mojom::PageHandler>()
      .Add<ash::mojom::scanner_feedback_ui::PageHandler>();
#endif  // BUILDFLAG(IS_CHROMEOS_ASH)

#if BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OFFICIAL_BUILD)
  registry.ForWebUI<ash::SampleSystemWebAppUntrustedUI>()
      .Add<ash::mojom::sample_swa::UntrustedPageInterfacesFactory>();
#endif  // BUILDFLAG(IS_CHROMEOS_ASH) && !defined(OFFICIAL_BUILD)

#if BUILDFLAG(ENABLE_COMPOSE)
  registry.ForWebUI<ComposeUntrustedUI>()
      .Add<color_change_listener::mojom::PageHandler>()
      .Add<compose::mojom::ComposeSessionUntrustedPageHandlerFactory>();
#endif  // BUILDFLAG(ENABLE_COMPOSE)
#if !BUILDFLAG(IS_ANDROID)
  if (lens::features::IsLensOverlayEnabled()) {
    registry.ForWebUI<lens::LensSidePanelUntrustedUI>()
        .Add<lens::mojom::LensSidePanelPageHandlerFactory>()
        .Add<lens::mojom::LensGhostLoaderPageHandlerFactory>()
        .Add<searchbox::mojom::PageHandler>()
        .Add<help_bubble::mojom::HelpBubbleHandlerFactory>()
        .Add<color_change_listener::mojom::PageHandler>();
  }
  if (lens::features::IsLensOverlayEnabled()) {
    registry.ForWebUI<lens::LensOverlayUntrustedUI>()
        .Add<lens::mojom::LensPageHandlerFactory>()
        .Add<lens::mojom::LensGhostLoaderPageHandlerFactory>()
        .Add<color_change_listener::mojom::PageHandler>()
        .Add<help_bubble::mojom::HelpBubbleHandlerFactory>()
        .Add<searchbox::mojom::PageHandler>();
  }
  registry.ForWebUI<ReadAnythingUntrustedUI>()
      .Add<color_change_listener::mojom::PageHandler>();

  if (base::FeatureList::IsEnabled(
          data_sharing::features::kDataSharingFeature)) {
    registry.ForWebUI<DataSharingUI>()
        .Add<data_sharing::mojom::PageHandlerFactory>()
        .Add<color_change_listener::mojom::PageHandler>();
  }

  registry.ForWebUI<NtpMicrosoftAuthUntrustedUI>()
      .Add<new_tab_page::mojom::
               MicrosoftAuthUntrustedDocumentInterfacesFactory>();

#endif  // !BUILDFLAG(IS_ANDROID)
}

}  // namespace chrome::internal
=======
}  // namespace internal
}  // namespace chrome
>>>>>>> chromium
