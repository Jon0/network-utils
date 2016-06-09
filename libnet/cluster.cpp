#include <algorithm>
#include <iostream>

#include <libutil/strings.h>

#include "cluster.h"

namespace net {


Neighbors::Neighbors() {}
Neighbors::~Neighbors() {}


bool Neighbors::valid() const {
    return true;
}


bool Neighbors::read(util::BinaryStream &s) {
    if (s.available() < sizeof(int32_t)) {
        return false;
    }
    int32_t length = s.peek_type<int32_t>();
    if (s.available() < length) {
        return false;
    }
    std::string buf = s.read_some(length);
    return true;
}


bool Neighbors::write(util::BinaryStream &s) {
    s.write_all("output\n");
    return true;
}


void Cluster::insert(map_t &map, const unit_t &unit) {
    map.insert(std::make_pair(unit.id(), unit));
}


Cluster::map_t Cluster::list_to_map(const std::initializer_list<Cluster::unit_t> &m) {
    Cluster::map_t result;
    for (auto i = m.begin(); i < m.end(); ++i) {
        result.insert(std::make_pair((*i).id(), *i));
    }
    return result;
}


Cluster::Cluster(const map_t &m)
    :
    ipmap(m) {}


Cluster::Cluster(const std::initializer_list<Cluster::unit_t> &m)
    :
    ipmap(list_to_map(m)) {}


Cluster::~Cluster() {}


size_t Cluster::size() const {
    return ipmap.size();
}


std::string Cluster::status() const {
    std::vector<std::string> ns = neighbor_str();
    std::string str = std::to_string(ns.size());
    //std::string str = util::concat(util::intersperse(std::string(", "), ns));
    return "{" + str + "}";
}


std::vector<unix::NetAddress *> Cluster::neighbors() const {
    std::vector<unix::NetAddress *> result;
    for (auto &u : ipmap) {
        if (u.second.server()) {
            result.emplace_back(u.second.addr());
        }
    }
    return result;
}


std::vector<std::string> Cluster::neighbor_str() const {
    std::vector<std::string> result;
    for (auto &n : neighbors()) {
        result.push_back(n->str());
    }
    return result;
}


std::string Cluster::neighbor_out() const {
    std::vector<unix::NetAddress *> n = neighbors();
    std::string result = std::to_string(n.size());
    for (auto a : n) {
        result += ";" + a->str();
    }
    return result;
}


Cluster Cluster::operator+(const Cluster::unit_t &m) const {
    map_t result = ipmap;
    Cluster::insert(result, m);
    return Cluster(result);
}


void Cluster::apply(const Cluster::apply_t &a) {
    for (auto &m : ipmap) {
        a(m.second);
    }
}


void Cluster::add_remote(const unit_t &remote) {
    Cluster::insert(ipmap, remote);

    // queue initial task
    process_input(remote.id());
}


void Cluster::process_input(key_t remote) {
    auto m1 = ipmap.find(remote);
    if (m1 == ipmap.end()) {
        return;
    }
    auto recv = std::make_shared<Message>();
    m1->second.ctrlqueue()->pushr(recv, [this, recv, remote]() {
        auto m2 = ipmap.find(remote);
        if (m2 == ipmap.end()) {
            return true;
        }

        auto reply = recv->op().apply(recv.get(), this);
        if (reply) {
            m2->second.ctrlqueue()->pushw(reply);
        }

        // output result
        std::cout << recv->desc() << " applied\n";
        std::cout << status() << "\n";

        // continue reading
        process_input(remote);
        return true;
    });
}


}
