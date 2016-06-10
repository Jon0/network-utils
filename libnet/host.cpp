#include "host.h"

namespace net {


Host this_host() {
    return Host(host_t::alias, "hostname");
}


Host::Host()
    :
    addr(nullptr) {}


Host::Host(const Host &h)
    :
    type(h.type),
    name(h.name),
    addr(unix::nullcpy(h.addr.get())) {
    init();
}

Host::Host(const host_t &t, const std::string &n)
    :
    type(t),
    name(n),
    addr(resolve()){
    init();
}


Host::Host(unix::NetAddress *a)
    :
    Host(host_t::address, a->str()) {}


Host::~Host() {}


bool Host::operator==(const Host &h) const {
    return *address() == *h.address();
}


std::string Host::desc() const {
    return name;
}


unix::NetAddress *Host::address() const {
    return addr.get();
}


std::unique_ptr<unix::NetAddress> Host::resolve() const {
    return std::make_unique<unix::IPv4>(std::array<unsigned char, 4>({0, 0, 0, 0}));
}


std::string Host::to_string() const {
    return name;
}


void Host::from_string(const std::string &s) {
    name = s;
}


}
