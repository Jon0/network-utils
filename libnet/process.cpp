#include <iostream>

#include "message.h"
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


std::string ClusterResponder::respond(const std::string &s) const {
    return s;
}


void ClusterResponder::update(prot::Context *c) {
    auto fn = [this](Cluster::unit_t &u) {
        std::string reply = respond(u.pop());
    };
    cl->apply(fn);
}


}
