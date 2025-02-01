// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_SOCKADDR_STORAGE_H_
#define NET_BASE_SOCKADDR_STORAGE_H_

#include "build/build_config.h"
#include "net/base/net_export.h"

#if defined(OS_WIN)
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
#include <sys/socket.h>
#include <sys/types.h>
#endif

namespace net {

// Convenience struct for when you need a |struct sockaddr|.
struct NET_EXPORT SockaddrStorage {
  SockaddrStorage();
  SockaddrStorage(const SockaddrStorage& other);
  SockaddrStorage& operator=(const SockaddrStorage& other);

<<<<<<< HEAD
  const sockaddr* addr() const {
    return reinterpret_cast<const sockaddr*>(&addr_storage);
  }
  sockaddr* addr() { return reinterpret_cast<sockaddr*>(&addr_storage); }

  sockaddr_storage addr_storage;
  socklen_t addr_len = sizeof(addr_storage);
=======
  struct sockaddr_storage addr_storage;
  socklen_t addr_len;
  struct sockaddr* const addr;
>>>>>>> chromium
};

}  // namespace net

#endif  // NET_BASE_SOCKADDR_STORAGE_H_
