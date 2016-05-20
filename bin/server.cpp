#include <functional>
#include <iostream>

#include <libunix/socket.h>
#include <libnet/cluster.h>
#include <libnet/protocol.h>
#include <libnet/queue.h>


void queue_thread(int portnum) {
    net::Process ps;
    ps.producers().emplace_back(std::make_unique<net::ClusterAccept>(portnum));
    ps.run();

    // event handlers
    net::Cluster neighbors({});
    //neighbors = neighbors + net::Machine(s);
    neighbors.update();
}


int main() {
    queue_thread(2620);
    return 0;
}
