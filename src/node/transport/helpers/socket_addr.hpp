#pragma once
#include "tcp_sockaddr.hpp"
#include <variant>
struct Sockaddr {
    [[nodiscard]] bool is_supported();
#ifndef DISABLE_LIBUV
    Sockaddr(TCPSockaddr sa)
        : data { std::move(sa) }
    {
    }
#else
#endif
    Sockaddr(WSSockaddr sa)
        : data { std::move(sa) }
    {
    }
    auto operator<=>(const Sockaddr&) const = default;
    using variant_t = std::variant<
#ifndef DISABLE_LIBUV
        TCPSockaddr,
#endif
        WSSockaddr>;
    variant_t data;
    [[nodiscard]] IPv4 ipv4() const;
    [[nodiscard]] uint16_t port() const;
    bool operator==(const Sockaddr&) const = default;
    std::string to_string() const;
};
