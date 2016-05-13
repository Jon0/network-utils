#pragma once

#include "libunix/socket.h"

namespace net {

class Machine {
public:
    using machine_key = unix::IPv4;

    Machine(const machine_key &id);
    virtual ~Machine();

private:
    const machine_key id;
    const unix::FileDesc fd;

};

}
