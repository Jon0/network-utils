#include "machine.h"

namespace net {

Machine::Machine(const machine_key &ip)
    :
    ipaddr(ip),
    fd(ip.connect(2620)) {}


Machine::~Machine() {}


machine_key Machine::id() const {
    return ipaddr;
}

}
