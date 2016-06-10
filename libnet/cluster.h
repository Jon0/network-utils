#pragma once

#include <functional>
#include <initializer_list>
#include <unordered_map>

#include <libutil/serial.h>
#include <libunix/socket.h>

#include "machine.h"
#include "protocol.h"

namespace net {


class Neighbors : public util::Serialisable {
public:
    using addr_t = std::unique_ptr<unix::NetAddress>;
    using list_t = std::vector<addr_t>;

    Neighbors();
    virtual ~Neighbors();

    bool valid() const override;
    bool read(util::BinaryStream &s) override;
    bool write(util::BinaryStream &s) override;

private:
    list_t addrs;

};


class Cluster {
public:
    using unit_t = Machine;
    using key_t = Host;
    using map_t = std::unordered_map<key_t, unit_t>;
    using apply_t = std::function<void (unit_t &)>;

    static key_t get_key(const unit_t &unit);
    static void insert(map_t &map, const unit_t &unit);
    static map_t list_to_map(const std::initializer_list<unit_t> &m);

    Cluster(const map_t &m);
    Cluster(const std::initializer_list<unit_t> &m);
    virtual ~Cluster();

    size_t size() const;
    std::string status() const;
    std::vector<unix::NetAddress *> neighbors() const;
    std::vector<std::string> neighbor_str() const;
    std::string neighbor_out() const;

    void apply(const apply_t &a);

    void add_remote(const unit_t &remote);
    void process_input(key_t remote);

private:
    map_t ipmap;
    map_t client, server;

};




}
