#include "host.h"

namespace net {


Host::Host()
    :
    addr(nullptr) {}


Host::Host(const host_t &t, const std::string &n)
    :
    type(t),
    name(n) {
    init();
}


Host::Host(unix::NetAddress *a)
    :
    Host(host_t::address, a->str()) {}


Host::~Host() {}


unix::NetAddress *Host::resolve() const {
    if (addr) {
        return addr.get();
    }
    else {
        return lookup_dns();
    }
}


unix::NetAddress *Host::lookup_dns() const {
    return nullptr;
}


std::string Host::to_string() const {
    return name;
}


void Host::from_string(const std::string &s) {
    name = s;
}


}
