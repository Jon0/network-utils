#pragma once

#include <initializer_list>
#include <unordered_map>

#include "libunix/socket.h"
#include "machine.h"

namespace net {


class Cluster {
public:
    using unit_t = Machine;
    using map_t = std::unordered_map<unit_t::key_t, unit_t>;

    static map_t list_to_map(const std::initializer_list<unit_t> &m);

    Cluster(const map_t &m);
    Cluster(const std::initializer_list<unit_t> &m);
    virtual ~Cluster();

    Cluster operator+(const unit_t &m) const;

    void update();

private:
    map_t ipmap;

};


}
