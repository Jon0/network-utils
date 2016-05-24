#include <functional>
#include <iostream>

#include <libunix/socket.h>
#include <libprot/interface.h>
#include <libnet/cluster.h>
#include <libnet/protocol.h>
#include <libnet/queue.h>


void queue_thread(int portnum) {
    net::NewConnection c;
    prot::Interface intf(c, std::make_shared<unix::TcpAcceptor>(portnum));


    // event handlers
    net::Cluster neighbors({});
    //neighbors = neighbors + net::Machine(s);
    neighbors.update();
}


int main() {
    queue_thread(2620);
    return 0;
}
