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
    Host(const Host &h);
    Host(const host_t &t, const std::string &n);
    Host(unix::NetAddress *a);
    virtual ~Host();

    bool operator==(const Host &h) const;
    std::string desc() const;
    unix::NetAddress *address() const;
    std::unique_ptr<unix::NetAddress> resolve() const;

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    host_t type;
    std::string name;
    std::unique_ptr<unix::NetAddress> addr;

};


Host this_host();


};


namespace std {


template<>
struct hash<net::Host> {
    size_t operator()(const net::Host &h) const {
        hash<unix::NetAddress> hash;
        return hash(*h.address());
    }
};


}
