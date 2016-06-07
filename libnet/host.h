#pragma once

#include <memory>

#include <libutil/serial.h>
#include <libunix/address.h>

namespace net {

enum class host_t {
    address,
    alias,
    dns
};

class Host : public util::Stringable {
public:
    Host();
    Host(const host_t &t, const std::string &n);
    Host(unix::NetAddress *a);
    virtual ~Host();

    unix::NetAddress *resolve() const;
    unix::NetAddress *lookup_dns() const;

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    host_t type;
    std::string name;
    std::unique_ptr<unix::NetAddress> addr;

};

};
