#include <algorithm>
#include <iostream>

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
    std::cout << "Length is " << length << "\n";
    if (s.available() < length) {
        return false;
    }
    std::string buf = s.read_some(length);
    std::cout << "recv: " << buf << "\n";
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


std::vector<unix::NetAddress *> Cluster::neighbors() const {
    std::vector<unix::NetAddress *> result;
    for (auto &u : ipmap) {
        if (u.second.server()) {
            result.emplace_back(u.second.addr());
        }
    }
    return result;
}


std::string Cluster::neighborstr() const {
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
    auto recv = std::make_shared<Request>();
    m1->second.ctrlqueue()->pushr(recv, [this, recv, remote]() {
        std::cout << "recv: " << recv->to_string() << "\n";

        auto m2 = ipmap.find(remote);
        if (m2 == ipmap.end()) {
            return true;
        }

        auto reply = std::make_shared<Response>();
        reply->init(recv->id(), neighborstr());

        m2->second.ctrlqueue()->pushw(reply);
        std::cout << "recv: " << recv->to_string() << "\n";
        process_input(remote);
        return true;
    });
}


}
