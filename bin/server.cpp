#include <functional>
#include <iostream>

#include <libunix/socket.h>
#include <libprot/context.h>
#include <libprot/interface.h>
#include <libnet/cluster.h>
#include <libnet/protocol.h>
#include <libnet/queue.h>


void queue_thread(int portnum) {
    net::Cluster c({});
    net::ClusterAcceptor a(portnum);
    while (true) {
        a.accept(c);
    }
}


int main() {
    queue_thread(2620);
    return 0;
}
