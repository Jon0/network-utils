#include <algorithm>

#include "cluster.h"

namespace net {


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
}


void Cluster::add_remote(std::shared_ptr<unix::Socket> remote) {
    add_remote(Machine(remote));
}


}
