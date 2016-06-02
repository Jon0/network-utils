#include <iostream>

#include "process.h"

namespace net {


ClusterAcceptor::ClusterAcceptor(Cluster &c, unsigned short portnum)
    :
    cl(&c),
    acceptor(portnum) {}


ClusterAcceptor::~ClusterAcceptor() {}


void ClusterAcceptor::accept() {
    if (acceptor.poll()) {
        auto sock = acceptor.accept_shared();
        std::cout << "[" << sock->remote()->str() << "] connected\n";
        cl->add_remote(sock);
    }
}


void ClusterAcceptor::update(prot::Context *c) {
    accept();
}


ClusterResponder::ClusterResponder(Cluster &c)
    :
    cl(&c) {}


ClusterResponder::~ClusterResponder() {}


std::string ClusterResponder::neighbors() const {
    std::vector<unix::NetAddress *> n = cl->neighbors();
    std::string result = std::to_string(n.size());
    for (auto a : n) {
        result += ";" + a->str();
    }
    return result;
}


std::string ClusterResponder::respond(const std::string &s) const {
    return s;
}


void ClusterResponder::update(prot::Context *c) {
    auto fn = [this](Cluster::unit_t &u) {
        auto recv = u.poll();
        for (auto &m : recv) {
            std::cout << "recv: " << m.str() << "\n";
        }
        if (!recv.empty()) {
            std::cout << "send response\n";
            std::string rp = neighbors();
            std::cout << rp << "\n";
            u.send(rp);
        }
    };
    cl->apply(fn);
}


}
