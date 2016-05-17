#pragma once

#include "libunix/address.h"

namespace net {


using machine_key = unix::IPv4;


class Machine {
public:
    Machine(const machine_key &ip);
    virtual ~Machine();

    machine_key id() const;

private:
    const machine_key ipaddr;
    const unix::FileDesc fd;

};


}
