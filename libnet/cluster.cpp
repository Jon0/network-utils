#include "cluster.h"

namespace net {


ip_map_t list_to_map(const std::initializer_list<Machine> &m) {
    ip_map_t result;
    for (auto i = m.begin(); i < m.end(); ++i) {
        result.insert(std::make_pair((*i).id(), *i));
    }
}


Cluster::Cluster(const std::initializer_list<Machine> &m)
    :
    ipmap(list_to_map(m)) {}


Cluster::~Cluster() {}


Cluster Cluster::operator+(const machine_key &ip) const {
    return *this;
}


}
