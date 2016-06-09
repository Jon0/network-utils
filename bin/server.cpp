#include <functional>
#include <iostream>

#include <libunix/socket.h>
#include <libprot/context.h>
#include <libprot/interface.h>
#include <libnet/cluster.h>
#include <libnet/process.h>


void join_thread(const std::string &host, int portnum) {
    prot::Context process;
    unix::IPv4 ip = unix::parse_ipv4(host);
    net::Machine m(&process, net::MachineTask(&ip, portnum));

    net::MessageSrc msrc;
    auto msg = msrc.create(net::ClusterOp(net::op_t::neighbor_req, ""));
    m.ctrlqueue()->pushw(msg);

    // read response
    auto rsp = std::make_shared<net::Message>();
    m.ctrlqueue()->pushr(rsp, [&m, &msrc, rsp]() {
        std::cout << rsp->desc() << "\n";
        auto join = msrc.create(net::ClusterOp(net::op_t::join_req, ""));
        m.ctrlqueue()->pushw(join);
        return true;
    });

    net::Cluster c({});
    process.add(std::make_shared<net::ClusterAcceptor>(c, portnum));
    process.run();
}


void queue_thread(int portnum) {
    prot::Context process;
    net::Cluster c({});
    process.add(std::make_shared<net::ClusterAcceptor>(c, portnum));
    process.run();
}


int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::string host = argv[1];
        std::cout << "connecting " << host << "\n";
        join_thread(host, 2620);
    }
    else {
        queue_thread(2620);
    }
    return 0;
}
