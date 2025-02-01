// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/platform_util.h"

#include <fcntl.h>

<<<<<<< HEAD
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <vector>

#include "base/callback_list.h"
#include "base/check.h"
#include "base/check_op.h"
#include "base/containers/contains.h"
#include "base/files/file_path.h"
#include "base/functional/bind.h"
#include "base/functional/callback.h"
#include "base/logging.h"
#include "base/memory/raw_ptr.h"
#include "base/nix/xdg_util.h"
=======
#include <string>
#include <vector>

#include "base/bind.h"
#include "base/containers/contains.h"
>>>>>>> chromium
#include "base/no_destructor.h"
#include "base/posix/eintr_wrapper.h"
#include "base/process/kill.h"
#include "base/process/launch.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/task/thread_pool.h"
#include "base/threading/scoped_blocking_call.h"
<<<<<<< HEAD
#include "base/types/expected.h"
#include "chrome/browser/platform_util_internal.h"
#include "components/dbus/properties/types.h"
#include "components/dbus/thread_linux/dbus_thread_linux.h"
#include "components/dbus/utils/check_for_service_and_start.h"
#include "components/dbus/xdg/request.h"
=======
#include "chrome/browser/chrome_notification_types.h"
#include "chrome/browser/platform_util_internal.h"
// This file gets pulled in in Chromecast builds, which causes "gn check" to
// complain as Chromecast doesn't use (or depend on) //components/dbus.
// TODO(crbug.com/1215474): Eliminate //chrome being visible in the GN structure
// on Chromecast and remove the nogncheck below.
#include "components/dbus/thread_linux/dbus_thread_linux.h"  // nogncheck
>>>>>>> chromium
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/notification_service.h"
#include "dbus/bus.h"
#include "dbus/message.h"
#include "dbus/object_proxy.h"
#include "third_party/abseil-cpp/absl/types/optional.h"
#include "url/gurl.h"

using content::BrowserThread;

namespace platform_util {

namespace {

const char kMethodListActivatableNames[] = "ListActivatableNames";
const char kMethodNameHasOwner[] = "NameHasOwner";

const char kFreedesktopFileManagerName[] = "org.freedesktop.FileManager1";
const char kFreedesktopFileManagerPath[] = "/org/freedesktop/FileManager1";
const char kMethodShowItems[] = "ShowItems";

const char kFreedesktopPortalName[] = "org.freedesktop.portal.Desktop";
const char kFreedesktopPortalPath[] = "/org/freedesktop/portal/desktop";
const char kFreedesktopPortalOpenURI[] = "org.freedesktop.portal.OpenURI";
const char kMethodOpenDirectory[] = "OpenDirectory";
const char kActivationTokenKey[] = "activation_token";

class ShowItemHelper : public content::NotificationObserver {
 public:
  static ShowItemHelper& GetInstance() {
    static base::NoDestructor<ShowItemHelper> instance;
    return *instance;
  }

<<<<<<< HEAD
  ShowItemHelper() = default;
=======
  ShowItemHelper() {
    registrar_.Add(this, chrome::NOTIFICATION_APP_TERMINATING,
                   content::NotificationService::AllSources());
  }
>>>>>>> chromium

  ShowItemHelper(const ShowItemHelper&) = delete;
  ShowItemHelper& operator=(const ShowItemHelper&) = delete;

<<<<<<< HEAD
  void ShowItemInFolder(const base::FilePath& full_path) {
    // Skip opening the folder during browser tests, to avoid leaving an open
    // file explorer window behind.
    if (!internal::AreShellOperationsAllowed()) {
      return;
    }
=======
  void Observe(int type,
               const content::NotificationSource& source,
               const content::NotificationDetails& details) override {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    DCHECK_EQ(chrome::NOTIFICATION_APP_TERMINATING, type);
    // The browser process is about to exit. Clean up while we still can.
    if (bus_)
      bus_->ShutdownOnDBusThreadAndBlock();
    bus_.reset();
    object_proxy_ = nullptr;
  }

  void ShowItemInFolder(Profile* profile, const base::FilePath& full_path) {
>>>>>>> chromium
    if (!bus_) {
      bus_ = dbus_thread_linux::GetSharedSessionBus();
    }

<<<<<<< HEAD
    if (api_type_.has_value()) {
      ShowItemInFolderOnApiTypeSet(full_path);
      return;
    }

    bool api_availability_check_in_progress = !pending_requests_.empty();
    pending_requests_.push(full_path);
    if (!api_availability_check_in_progress) {
      // Initiate check to determine if portal or the FileManager API should
      // be used. The portal API is always preferred if available.
      dbus_utils::CheckForServiceAndStart(
          bus_.get(), kFreedesktopPortalName,
          base::BindOnce(&ShowItemHelper::CheckPortalRunningResponse,
                         // Unretained is safe, the ShowItemHelper instance is
                         // never destroyed.
                         base::Unretained(this)));
=======
    if (!dbus_proxy_) {
      dbus_proxy_ = bus_->GetObjectProxy(DBUS_SERVICE_DBUS,
                                         dbus::ObjectPath(DBUS_PATH_DBUS));
    }

    if (prefer_filemanager_interface_.has_value()) {
      if (prefer_filemanager_interface_.value()) {
        VLOG(1) << "Using FileManager1 to show folder";
        ShowItemUsingFileManager(profile, full_path);
      } else {
        VLOG(1) << "Using OpenURI to show folder";
        ShowItemUsingFreedesktopPortal(profile, full_path);
      }
    } else {
      CheckFileManagerRunning(profile, full_path);
>>>>>>> chromium
    }
  }

 private:
<<<<<<< HEAD
  enum class ApiType { kNone, kPortal, kFileManager };

  void ShowItemInFolderOnApiTypeSet(const base::FilePath& full_path) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    CHECK(api_type_.has_value());
    switch (*api_type_) {
      case ApiType::kPortal:
        ShowItemUsingPortal(full_path);
        break;
      case ApiType::kFileManager:
        ShowItemUsingFileManager(full_path);
        break;
      case ApiType::kNone:
        OpenParentFolderFallback(full_path);
        break;
    }
  }

  void ProcessPendingRequests() {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    if (!bus_) {
      return;
    }

    CHECK(!pending_requests_.empty());
    while (!pending_requests_.empty()) {
      ShowItemInFolderOnApiTypeSet(pending_requests_.front());
      pending_requests_.pop();
    }
=======
  void CheckFileManagerRunning(Profile* profile,
                               const base::FilePath& full_path) {
    dbus::MethodCall method_call(DBUS_INTERFACE_DBUS, kMethodNameHasOwner);
    dbus::MessageWriter writer(&method_call);
    writer.AppendString(kFreedesktopFileManagerName);

    dbus_proxy_->CallMethod(
        &method_call, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
        base::BindOnce(&ShowItemHelper::CheckFileManagerRunningResponse,
                       weak_ptr_factory_.GetWeakPtr(), profile, full_path));
  }

  void CheckFileManagerRunningResponse(Profile* profile,
                                       const base::FilePath& full_path,
                                       dbus::Response* response) {
    if (prefer_filemanager_interface_.has_value()) {
      ShowItemInFolder(profile, full_path);
      return;
    }

    bool is_running = false;

    if (!response) {
      LOG(ERROR) << "Failed to call " << kMethodNameHasOwner;
    } else {
      dbus::MessageReader reader(response);
      bool owned = false;

      if (!reader.PopBool(&owned)) {
        LOG(ERROR) << "Failed to read " << kMethodNameHasOwner << " resposne";
      } else if (owned) {
        is_running = true;
      }
    }

    if (is_running) {
      prefer_filemanager_interface_ = true;
      ShowItemInFolder(profile, full_path);
    } else {
      CheckFileManagerActivatable(profile, full_path);
    }
  }

  void CheckFileManagerActivatable(Profile* profile,
                                   const base::FilePath& full_path) {
    dbus::MethodCall method_call(DBUS_INTERFACE_DBUS,
                                 kMethodListActivatableNames);
    dbus_proxy_->CallMethod(
        &method_call, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
        base::BindOnce(&ShowItemHelper::CheckFileManagerActivatableResponse,
                       weak_ptr_factory_.GetWeakPtr(), profile, full_path));
  }

  void CheckFileManagerActivatableResponse(Profile* profile,
                                           const base::FilePath& full_path,
                                           dbus::Response* response) {
    if (prefer_filemanager_interface_.has_value()) {
      ShowItemInFolder(profile, full_path);
      return;
    }

    bool is_activatable = false;

    if (!response) {
      LOG(ERROR) << "Failed to call " << kMethodListActivatableNames;
    } else {
      dbus::MessageReader reader(response);
      std::vector<std::string> names;
      if (!reader.PopArrayOfStrings(&names)) {
        LOG(ERROR) << "Failed to read " << kMethodListActivatableNames
                   << " response";
      } else if (base::Contains(names, kFreedesktopFileManagerName)) {
        is_activatable = true;
      }
    }

    prefer_filemanager_interface_ = is_activatable;
    ShowItemInFolder(profile, full_path);
>>>>>>> chromium
  }

  void CheckPortalRunningResponse(std::optional<bool> is_running) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    if (is_running.value_or(false)) {
      api_type_ = ApiType::kPortal;
      ProcessPendingRequests();
    } else {
      // Portal is unavailable.
      // Check if FileManager is available.
      dbus_utils::CheckForServiceAndStart(
          bus_.get(), kFreedesktopFileManagerName,
          base::BindOnce(&ShowItemHelper::CheckFileManagerRunningResponse,
                         // Unretained is safe, the ShowItemHelper instance is
                         // never destroyed.
                         base::Unretained(this)));
    }
  }

  void CheckFileManagerRunningResponse(std::optional<bool> is_running) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    if (is_running.value_or(false)) {
      api_type_ = ApiType::kFileManager;
    } else {
      // Neither portal nor FileManager is available.
      api_type_ = ApiType::kNone;
    }
    ProcessPendingRequests();
  }

  void ShowItemUsingPortal(const base::FilePath& full_path) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    CHECK(api_type_.has_value());
    CHECK_EQ(*api_type_, ApiType::kPortal);
    base::ThreadPool::PostTaskAndReplyWithResult(
        FROM_HERE, {base::MayBlock()},
        base::BindOnce(
            [](const base::FilePath& full_path) {
              base::ScopedFD fd(HANDLE_EINTR(
                  open(full_path.value().c_str(), O_RDONLY | O_CLOEXEC)));
              return fd;
            },
            full_path),
        base::BindOnce(&ShowItemHelper::ShowItemUsingPortalFdOpened,
                       // Unretained is safe, the ShowItemHelper instance is
                       // never destroyed.
                       base::Unretained(this), full_path));
  }

  void ShowItemUsingPortalFdOpened(const base::FilePath& full_path,
                                   base::ScopedFD fd) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    if (!bus_) {
      return;
    }
    if (!fd.is_valid()) {
      // At least open the parent folder, as long as we're not in the unit
      // tests.
      OpenParentFolderFallback(full_path);
      return;
    }
    base::nix::CreateXdgActivationToken(base::BindOnce(
        &ShowItemHelper::ShowItemUsingPortalWithToken,
        // Unretained is safe, the ShowItemHelper instance is never destroyed.
        base::Unretained(this), full_path, std::move(fd)));
  }

  void ShowItemUsingPortalWithToken(const base::FilePath& full_path,
                                    base::ScopedFD fd,
                                    std::string activation_token) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    if (!bus_) {
      return;
    }

    if (!portal_object_proxy_) {
      portal_object_proxy_ = bus_->GetObjectProxy(
          kFreedesktopPortalName, dbus::ObjectPath(kFreedesktopPortalPath));
    }

    DbusDictionary options;
    options.PutAs(kActivationTokenKey, DbusString(activation_token));
    // In the rare occasion that another request comes in before the response is
    // received, we will end up overwriting this request object with the new one
    // and the response from the first request will not be handled in that case.
    // This should be acceptable as it means the two requests were received too
    // close to each other from the user and the first one was handled on a best
    // effort basis.
    portal_open_directory_request_ = std::make_unique<dbus_xdg::Request>(
        bus_, portal_object_proxy_, kFreedesktopPortalOpenURI,
        kMethodOpenDirectory,
        MakeDbusParameters(DbusString(""), DbusUnixFd(std::move(fd))),
        std::move(options),
        base::BindOnce(&ShowItemHelper::ShowItemUsingPortalResponse,
                       // Unretained is safe, the ShowItemHelper instance is
                       // never destroyed.
                       base::Unretained(this), full_path));
  }

  void ShowItemUsingPortalResponse(
      const base::FilePath& full_path,
      base::expected<DbusDictionary, dbus_xdg::ResponseError> results) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    portal_open_directory_request_.reset();
    if (!results.has_value()) {
      OpenParentFolderFallback(full_path);
    }
  }

  void ShowItemUsingFileManager(const base::FilePath& full_path) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    if (!bus_) {
      return;
    }
    CHECK(api_type_.has_value());
    CHECK_EQ(*api_type_, ApiType::kFileManager);
    if (!file_manager_object_proxy_) {
      file_manager_object_proxy_ =
          bus_->GetObjectProxy(kFreedesktopFileManagerName,
                               dbus::ObjectPath(kFreedesktopFileManagerPath));
    }

    dbus::MethodCall show_items_call(kFreedesktopFileManagerName,
                                     kMethodShowItems);
    dbus::MessageWriter writer(&show_items_call);

    writer.AppendArrayOfStrings(
        {"file://" + full_path.value()});  // List of file(s) to highlight.
    writer.AppendString({});               // startup-id

    file_manager_object_proxy_->CallMethod(
        &show_items_call, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
        base::BindOnce(&ShowItemHelper::ShowItemUsingFileManagerResponse,
                       // Unretained is safe, the ShowItemHelper instance is
                       // never destroyed.
                       base::Unretained(this), full_path));
  }

  void ShowItemUsingFileManagerResponse(const base::FilePath& full_path,
                                        dbus::Response* response) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    if (!response) {
      // If the bus call fails, at least open the parent folder.
      OpenParentFolderFallback(full_path);
    }
  }

  void OpenParentFolderFallback(const base::FilePath& full_path) {
    OpenItem(
        // profile is not used in linux
        /*profile=*/nullptr, full_path.DirName(), OPEN_FOLDER,
        OpenOperationCallback());
  }

  content::NotificationRegistrar registrar_;

  scoped_refptr<dbus::Bus> bus_;
  dbus::ObjectProxy* dbus_proxy_ = nullptr;
  dbus::ObjectProxy* object_proxy_ = nullptr;

<<<<<<< HEAD
  std::optional<ApiType> api_type_;
  // The proxy objects are owned by `bus_`.
  raw_ptr<dbus::ObjectProxy> portal_object_proxy_ = nullptr;
  raw_ptr<dbus::ObjectProxy> file_manager_object_proxy_ = nullptr;
  std::unique_ptr<dbus_xdg::Request> portal_open_directory_request_;

  // Requests that are queued until the API availability is determined.
  std::queue<base::FilePath> pending_requests_;
=======
  absl::optional<bool> prefer_filemanager_interface_;

  base::WeakPtrFactory<ShowItemHelper> weak_ptr_factory_{this};
>>>>>>> chromium
};

void RunCommand(const std::string& command,
                const base::FilePath& working_directory,
                const std::string& arg) {
  std::vector<std::string> argv;
  argv.push_back(command);
  argv.push_back(arg);

  base::LaunchOptions options;
  options.current_directory = working_directory;
  options.allow_new_privs = true;
  // xdg-open can fall back on mailcap which eventually might plumb through
  // to a command that needs a terminal.  Set the environment variable telling
  // it that we definitely don't have a terminal available and that it should
  // bring up a new terminal if necessary.  See "man mailcap".
  options.environment["MM_NOTTTY"] = "1";

  // In Google Chrome, we do not let GNOME's bug-buddy intercept our crashes.
  // However, we do not want this environment variable to propagate to external
  // applications. See http://crbug.com/24120
  char* disable_gnome_bug_buddy = getenv("GNOME_DISABLE_CRASH_DIALOG");
  if (disable_gnome_bug_buddy &&
      disable_gnome_bug_buddy == std::string("SET_BY_GOOGLE_CHROME")) {
    options.environment["GNOME_DISABLE_CRASH_DIALOG"] = std::string();
  }

  base::Process process = base::LaunchProcess(argv, options);
  if (process.IsValid()) {
    base::EnsureProcessGetsReaped(std::move(process));
  }
}

void XDGOpen(const base::FilePath& working_directory, const std::string& path) {
  RunCommand("xdg-open", working_directory, path);
}

void XDGEmail(const std::string& email) {
  RunCommand("xdg-email", base::FilePath(), email);
}

}  // namespace

namespace internal {

void PlatformOpenVerifiedItem(const base::FilePath& path, OpenItemType type) {
  // May result in an interactive dialog.
  base::ScopedBlockingCall scoped_blocking_call(FROM_HERE,
                                                base::BlockingType::MAY_BLOCK);
  switch (type) {
    case OPEN_FILE:
      XDGOpen(path.DirName(), path.value());
      break;
    case OPEN_FOLDER:
      // The utility process checks the working directory prior to the
      // invocation of xdg-open by changing the current directory into it. This
      // operation only succeeds if |path| is a directory. Opening "." from
      // there ensures that the target of the operation is a directory.  Note
      // that there remains a TOCTOU race where the directory could be unlinked
      // between the time the utility process changes into the directory and the
      // time the application invoked by xdg-open inspects the path by name.
      XDGOpen(path, ".");
      break;
  }
}

}  // namespace internal

void ShowItemInFolder(Profile*, const base::FilePath& full_path) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  ShowItemHelper::GetInstance().ShowItemInFolder(full_path);
}

void OpenExternal(Profile* profile, const GURL& url) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  if (url.SchemeIs("mailto")) {
    XDGEmail(url.spec());
  } else {
    XDGOpen(base::FilePath(), url.spec());
  }
}

}  // namespace platform_util
