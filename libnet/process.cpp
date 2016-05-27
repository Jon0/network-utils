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
        std::cout << "connected " << sock->remote()->str() << "\n";
        cl->add_remote(sock);
    }
}


void ClusterAcceptor::update(prot::Context *c) {
    accept();
}


}
