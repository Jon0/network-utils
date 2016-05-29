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


ClusterResponder::ClusterResponder(Cluster &c) {}
ClusterResponder::~ClusterResponder() {}


void ClusterResponder::update(prot::Context *c) {
    auto fn = [](Cluster::unit_t &u) {
        Message m;
        m.read(*u.connection());
    };
    cl->apply(fn);
}


}
