#pragma once

#include <functional>
#include <initializer_list>
#include <unordered_map>

#include "libprot/protocol.h"
#include "libunix/socket.h"
#include "machine.h"
#include "process.h"

namespace net {


class Cluster {
public:
    using unit_t = Machine;
    using map_t = std::unordered_map<unit_t::key_t, unit_t>;

    static map_t list_to_map(const std::initializer_list<unit_t> &m);

    Cluster(const map_t &m);
    Cluster(const std::initializer_list<unit_t> &m);
    virtual ~Cluster();

    size_t size() const;
    Cluster operator+(const unit_t &m) const;

    Queue update();

private:
    map_t ipmap;

};


class NewConnection : public prot::Protocol {
public:
    NewConnection();
    std::unique_ptr<prot::Protocol> copy() const override;
    void chan(channel_t *c) const override;
    void event(channel_t *c) const override;
};


class ClusterJoin : public Event {
public:
    using modify_t = Cluster;

    bool apply(modify_t m) const;
};


}
