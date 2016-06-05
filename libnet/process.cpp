#include <iostream>

#include "process.h"

namespace net {


ClusterAcceptor::ClusterAcceptor(Cluster &c, unsigned short portnum)
    :
    cl(&c),
    acceptor(portnum) {}


ClusterAcceptor::~ClusterAcceptor() {}


void ClusterAcceptor::update(prot::Context *c) {
    if (acceptor.poll()) {
        auto sock = acceptor.accept_shared();
        std::cout << "[" << sock->rstr() << "] connected\n";
        cl->add_remote(Machine(c, MachineTask(sock)));
    }
}


}
