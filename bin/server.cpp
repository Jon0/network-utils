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
    auto msg = std::make_shared<prot::Message>("reqn");
    m.ctrlqueue()->pushw(msg, [&m]() {
        auto join = std::make_shared<prot::Message>("join");
        m.ctrlqueue()->pushw(join);
        return true;
    });

    net::Cluster c({});
    process.add(std::make_shared<net::ClusterAcceptor>(c, portnum));
    process.add(std::make_shared<net::ClusterResponder>(c));
    process.run();
}


void queue_thread(int portnum) {
    prot::Context process;
    net::Cluster c({});
    process.add(std::make_shared<net::ClusterAcceptor>(c, portnum));
    process.add(std::make_shared<net::ClusterResponder>(c));
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
