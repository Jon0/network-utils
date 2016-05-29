#pragma once

#include <functional>
#include <initializer_list>
#include <unordered_map>

#include "libprot/protocol.h"
#include "libunix/socket.h"
#include "machine.h"

namespace net {


class Cluster {
public:
    using unit_t = Machine;
    using map_t = std::unordered_map<unit_t::key_t, unit_t>;
    using apply_t = std::function<void (unit_t &)>;

    static void insert(map_t &map, const unit_t &unit);
    static map_t list_to_map(const std::initializer_list<unit_t> &m);

    Cluster(const map_t &m);
    Cluster(const std::initializer_list<unit_t> &m);
    virtual ~Cluster();

    size_t size() const;
    Cluster operator+(const unit_t &m) const;

    void apply(const apply_t &a);

    void add_remote(const unit_t &remote);
    void add_remote(std::shared_ptr<unix::Socket> remote);

private:
    map_t ipmap;


};




}
