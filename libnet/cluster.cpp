#include <algorithm>

#include "cluster.h"
#include "protocol.h"

namespace net {


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
    result.insert(std::make_pair(m.id(), m));
    return Cluster(result);
}


Queue Cluster::update() {
    GroupRespond r(ipmap);
    for (auto &i : ipmap) {
        Machine &m = i.second;
        if (m.connected()) {
            m.update(&r);
        }
    }
    return Queue();
}


}
