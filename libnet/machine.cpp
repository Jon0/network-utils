#include <libunix/socket.h>

#include "machine.h"

namespace net {

Machine::Machine(const machine_key &ip)
    :
    ipaddr(ip),
    fd(unix::ipv4_socket()) {
    ip.connect(fd.id(), 2620);
}


Machine::~Machine() {}


machine_key Machine::id() const {
    return ipaddr;
}

}
