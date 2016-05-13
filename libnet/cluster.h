#pragma once

#include <initializer_list>
#include <unordered_map>

#include "libunix/socket.h"
#include "machine.h"

namespace net {


using ip_map_t = std::unordered_map<machine_key, Machine>;


ip_map_t list_to_map(const std::initializer_list<Machine> &m);


class Cluster {
public:
    Cluster(const std::initializer_list<Machine> &m);
    virtual ~Cluster();

    Cluster operator+(const machine_key &ip) const;

private:
    const ip_map_t ipmap;

};

}
