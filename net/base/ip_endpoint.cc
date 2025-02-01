// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef UNSAFE_BUFFERS_BUILD
// TODO(crbug.com/390223051): Remove C-library calls to fix the errors.
#pragma allow_unsafe_libc_calls
#endif

#include "net/base/ip_endpoint.h"

#include <ostream>

#include "build/build_config.h"

#if defined(OS_WIN)
#include <winsock2.h>
#include <ws2bth.h>
#elif defined(OS_POSIX)
#include <netinet/in.h>
#endif

#include <string.h>

#include <tuple>

#include "base/check.h"
#include "base/notreached.h"
#include "base/strings/string_number_conversions.h"
#include "base/sys_byteorder.h"
#include "net/base/ip_address.h"
#include "net/base/sys_addrinfo.h"

<<<<<<< HEAD
#if BUILDFLAG(IS_WIN)
#include <winsock2.h>
#include <winternl.h>

#include <netioapi.h>
#include <ntstatus.h>
#include <ws2bth.h>

#include "net/base/winsock_util.h"  // For kBluetoothAddressSize
#elif BUILDFLAG(IS_POSIX) || BUILDFLAG(IS_FUCHSIA)
#include <net/if.h>
=======
#if defined(OS_WIN)
#include "net/base/winsock_util.h"
>>>>>>> chromium
#endif

namespace net {

namespace {

<<<<<<< HEAD
// Value dictionary keys
constexpr std::string_view kValueAddressKey = "address";
constexpr std::string_view kValuePortKey = "port";
constexpr std::string_view kInterfaceName = "interface_name";

}  // namespace

IPEndPoint::IndexToNameFunc IPEndPoint::index_to_name_func_for_testing_ =
    nullptr;
IPEndPoint::NameToIndexFunc IPEndPoint::name_to_index_func_for_testing_ =
    nullptr;

// static
void IPEndPoint::SetNameToIndexFuncForTesting(NameToIndexFunc func) {
  name_to_index_func_for_testing_ = func;
}

void IPEndPoint::SetIndexToNameFuncForTesting(IndexToNameFunc func) {
  index_to_name_func_for_testing_ = func;
}

// static
std::optional<uint32_t> IPEndPoint::ScopeIdFromDict(
    const base::Value::Dict& dict) {
  const std::string* name = dict.FindString(kInterfaceName);
  if (!name) {
    return std::nullopt;
  }

  unsigned int index = 0;
  if (name_to_index_func_for_testing_) {
    index = name_to_index_func_for_testing_(name->c_str());
  } else {
    index = if_nametoindex(name->c_str());
  }

  return index;
}

// static
base::Value IPEndPoint::ScopeIdToValue(std::optional<uint32_t> scope_id) {
  if (!scope_id.has_value()) {
    return base::Value();
  }

  char* name = nullptr;
  char buf[IF_NAMESIZE + 1];
  memset(buf, 0, sizeof(buf));
  if (index_to_name_func_for_testing_) {
    name = index_to_name_func_for_testing_(scope_id.value(), buf);
  } else {
    name = if_indextoname(scope_id.value(), buf);
  }

  if (!name) {
    return base::Value();
  }

  return base::Value(name);
}

// static
std::optional<IPEndPoint> IPEndPoint::FromValue(const base::Value& value) {
  const base::Value::Dict* dict = value.GetIfDict();
  if (!dict)
    return std::nullopt;

  const base::Value* address_value = dict->Find(kValueAddressKey);
  if (!address_value)
    return std::nullopt;
  std::optional<IPAddress> address = IPAddress::FromValue(*address_value);
  if (!address.has_value())
    return std::nullopt;
  // Expect IPAddress to only allow deserializing valid addresses.
  DCHECK(address.value().IsValid());

  std::optional<int> port = dict->FindInt(kValuePortKey);
  if (!port.has_value() ||
      !base::IsValueInRangeForNumericType<uint16_t>(port.value())) {
    return std::nullopt;
  }

  IPEndPoint endpoint(address.value(),
                      base::checked_cast<uint16_t>(port.value()));

  std::optional<uint32_t> scope_id = ScopeIdFromDict(*dict);
  if (scope_id.has_value()) {
    if (scope_id.value() == 0 || !endpoint.IsIPv6LinkLocal() ||
        !base::IsValueInRangeForNumericType<uint32_t>(scope_id.value())) {
      return std::nullopt;
    }
    endpoint.scope_id_ = scope_id.value();
  }

  return endpoint;
}

IPEndPoint::IPEndPoint() = default;
=======
// By definition, socklen_t is large enough to hold both sizes.
const socklen_t kSockaddrInSize = sizeof(struct sockaddr_in);
const socklen_t kSockaddrIn6Size = sizeof(struct sockaddr_in6);

// Extracts the address and port portions of a sockaddr.
bool GetIPAddressFromSockAddr(const struct sockaddr* sock_addr,
                              socklen_t sock_addr_len,
                              const uint8_t** address,
                              size_t* address_len,
                              uint16_t* port) {
  if (sock_addr->sa_family == AF_INET) {
    if (sock_addr_len < static_cast<socklen_t>(sizeof(struct sockaddr_in)))
      return false;
    const struct sockaddr_in* addr =
        reinterpret_cast<const struct sockaddr_in*>(sock_addr);
    *address = reinterpret_cast<const uint8_t*>(&addr->sin_addr);
    *address_len = IPAddress::kIPv4AddressSize;
    if (port)
      *port = base::NetToHost16(addr->sin_port);
    return true;
  }

  if (sock_addr->sa_family == AF_INET6) {
    if (sock_addr_len < static_cast<socklen_t>(sizeof(struct sockaddr_in6)))
      return false;
    const struct sockaddr_in6* addr =
        reinterpret_cast<const struct sockaddr_in6*>(sock_addr);
    *address = reinterpret_cast<const uint8_t*>(&addr->sin6_addr);
    *address_len = IPAddress::kIPv6AddressSize;
    if (port)
      *port = base::NetToHost16(addr->sin6_port);
    return true;
  }

#if defined(OS_WIN)
  if (sock_addr->sa_family == AF_BTH) {
    if (sock_addr_len < static_cast<socklen_t>(sizeof(SOCKADDR_BTH)))
      return false;
    const SOCKADDR_BTH* addr = reinterpret_cast<const SOCKADDR_BTH*>(sock_addr);
    *address = reinterpret_cast<const uint8_t*>(&addr->btAddr);
    *address_len = kBluetoothAddressSize;
    if (port)
      *port = static_cast<uint16_t>(addr->port);
    return true;
  }
#endif

  return false;  // Unrecognized |sa_family|.
}

}  // namespace

IPEndPoint::IPEndPoint() : port_(0) {}
>>>>>>> chromium

IPEndPoint::~IPEndPoint() = default;

IPEndPoint::IPEndPoint(const IPAddress& address,
                       uint16_t port,
                       std::optional<uint32_t> scope_id)
    : address_(address), port_(port), scope_id_(scope_id) {}

IPEndPoint::IPEndPoint(const IPEndPoint& endpoint) {
  address_ = endpoint.address_;
  port_ = endpoint.port_;
}

AddressFamily IPEndPoint::GetFamily() const {
  return GetAddressFamily(address_);
}

int IPEndPoint::GetSockAddrFamily() const {
  switch (address_.size()) {
    case IPAddress::kIPv4AddressSize:
      return AF_INET;
    case IPAddress::kIPv6AddressSize:
      return AF_INET6;
    default:
      NOTREACHED() << "Bad IP address";
      return AF_UNSPEC;
  }
}

bool IPEndPoint::ToSockAddr(struct sockaddr* address,
                            socklen_t* address_length) const {
  DCHECK(address);
  DCHECK(address_length);
  switch (address_.size()) {
    case IPAddress::kIPv4AddressSize: {
      if (*address_length < kSockaddrInSize)
        return false;
      *address_length = kSockaddrInSize;
      struct sockaddr_in* addr = reinterpret_cast<struct sockaddr_in*>(address);
      memset(addr, 0, sizeof(struct sockaddr_in));
      addr->sin_family = AF_INET;
      addr->sin_port = base::HostToNet16(port_);
      memcpy(&addr->sin_addr, address_.bytes().data(),
             IPAddress::kIPv4AddressSize);
      break;
    }
    case IPAddress::kIPv6AddressSize: {
      if (*address_length < kSockaddrIn6Size)
        return false;
      *address_length = kSockaddrIn6Size;
      struct sockaddr_in6* addr6 =
          reinterpret_cast<struct sockaddr_in6*>(address);
      memset(addr6, 0, sizeof(struct sockaddr_in6));
      addr6->sin6_family = AF_INET6;
      addr6->sin6_port = base::HostToNet16(port_);
      memcpy(&addr6->sin6_addr, address_.bytes().data(),
             IPAddress::kIPv6AddressSize);
      if (IsIPv6LinkLocal() && scope_id_) {
        addr6->sin6_scope_id = *scope_id_;
      }
      break;
    }
    default:
      return false;
  }
  return true;
}

bool IPEndPoint::FromSockAddr(const struct sockaddr* sock_addr,
                              socklen_t sock_addr_len) {
  DCHECK(sock_addr);
<<<<<<< HEAD
  switch (sock_addr->sa_family) {
    case AF_INET: {
      if (sock_addr_len < static_cast<socklen_t>(sizeof(struct sockaddr_in)))
        return false;
      const struct sockaddr_in* addr =
          reinterpret_cast<const struct sockaddr_in*>(sock_addr);
      *this = IPEndPoint(
          // `s_addr` is a `uint32_t`, but it is already in network byte order.
          IPAddress(base::as_bytes(base::span_from_ref(addr->sin_addr.s_addr))),
          base::NetToHost16(addr->sin_port));
      return true;
    }
    case AF_INET6: {
      if (sock_addr_len < static_cast<socklen_t>(sizeof(struct sockaddr_in6)))
        return false;
      const struct sockaddr_in6* addr =
          reinterpret_cast<const struct sockaddr_in6*>(sock_addr);
      *this = IPEndPoint(IPAddress(addr->sin6_addr.s6_addr),
                         base::NetToHost16(addr->sin6_port));
      if (IsIPv6LinkLocal() && addr->sin6_scope_id != 0) {
        scope_id_ = addr->sin6_scope_id;
      }
      return true;
    }
#if BUILDFLAG(IS_WIN)
    case AF_BTH: {
      if (sock_addr_len < static_cast<socklen_t>(sizeof(SOCKADDR_BTH)))
        return false;
      const SOCKADDR_BTH* addr =
          reinterpret_cast<const SOCKADDR_BTH*>(sock_addr);
      *this = IPEndPoint();
      // A bluetooth address is 6 bytes, but btAddr is a ULONGLONG, so we take a
      // prefix of it.
      address_ = IPAddress(base::as_bytes(base::span_from_ref(addr->btAddr))
                               .first(kBluetoothAddressSize));
      // Intentionally ignoring Bluetooth port. It is a ULONG, but
      // `IPEndPoint::port_` is a uint16_t. See https://crbug.com/1231273.
      return true;
    }
#endif
=======

  const uint8_t* address;
  size_t address_len;
  uint16_t port;
  if (!GetIPAddressFromSockAddr(sock_addr, sock_addr_len, &address,
                                &address_len, &port)) {
    return false;
>>>>>>> chromium
  }

  address_ = net::IPAddress(address, address_len);
  port_ = port;
  return true;
}

std::string IPEndPoint::ToString() const {
  return IPAddressToStringWithPort(address_, port_);
}

std::string IPEndPoint::ToStringWithoutPort() const {
  return address_.ToString();
}

bool IPEndPoint::operator<(const IPEndPoint& other) const {
  // Sort IPv4 before IPv6.
  if (address_.size() != other.address_.size()) {
    return address_.size() < other.address_.size();
  }
  return std::tie(address_, port_, scope_id_) <
         std::tie(other.address_, other.port_, other.scope_id_);
}

bool IPEndPoint::operator==(const IPEndPoint& other) const {
  return address_ == other.address_ && port_ == other.port_ &&
         scope_id_ == other.scope_id_;
}

bool IPEndPoint::operator!=(const IPEndPoint& that) const {
  return !(*this == that);
}

<<<<<<< HEAD
base::Value IPEndPoint::ToValue() const {
  base::Value::Dict dict;

  DCHECK(address_.IsValid());
  dict.Set(kValueAddressKey, address_.ToValue());
  dict.Set(kValuePortKey, port_);

  base::Value interface_name = ScopeIdToValue(scope_id_);
  if (!interface_name.is_none()) {
    DCHECK(IsIPv6LinkLocal());
    dict.Set(kInterfaceName, std::move(interface_name));
  }

  return base::Value(std::move(dict));
}

bool IPEndPoint::IsIPv6LinkLocal() const {
  return address_.IsValid() && address_.IsIPv6() &&
         !address_.IsIPv4MappedIPv6() && address_.IsLinkLocal();
}

std::ostream& operator<<(std::ostream& os, const IPEndPoint& ip_endpoint) {
  return os << ip_endpoint.ToString();
}

=======
>>>>>>> chromium
}  // namespace net
