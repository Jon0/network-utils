#include <functional>
#include <iostream>

#include <libunix/socket.h>
#include <libprot/context.h>
#include <libprot/interface.h>
#include <libnet/cluster.h>
#include <libnet/process.h>
#include <libnet/queue.h>


void queue_thread(int portnum) {
    prot::Context process;
    net::Cluster c({});
    process.add(std::make_shared<net::ClusterAcceptor>(c, portnum));
    process.run();
}


int main() {
    queue_thread(2620);
    return 0;
}
