#pragma once

#include <unordered_map>

#include "libunix/socket.h"
#include "machine.h"

namespace net {

class Cluster {
public:
    Cluster();

    void connect_machine(const Machine::machine_key &ip);

private:
    std::unordered_map<Machine::machine_key, Machine> ipmap;

};

}
