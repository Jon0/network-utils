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


ClusterResponder::ClusterResponder(Cluster &c)
    :
    cl(&c) {}


ClusterResponder::~ClusterResponder() {}


std::string ClusterResponder::respond(const std::string &s) const {
    return s;
}


void ClusterResponder::update(prot::Context *c) {
    auto fn = [this](Cluster::unit_t &u) {
        auto recv = std::make_shared<prot::Message>();
        u.ctrlqueue()->pushr(recv, [this, &u, recv]() {
            std::cout << "recv: " << recv->str() << "\n";
            auto reply = std::make_shared<prot::Message>(cl->neighborstr());
            u.ctrlqueue()->pushw(reply, []() {
                return true;
            });
            return true;
        });
    };
    cl->apply(fn);
}


}
