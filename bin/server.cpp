#include <iostream>

#include <libunix/socket.h>
#include <libnet/cluster.h>
#include <libnet/protocol.h>
#include <libnet/queue.h>

void queue_thread() {
    net::Queue q;

}


void accept_connections(int portnum) {
    unix::TcpAcceptor a(portnum);
    net::Cluster neighbors({});

    bool running = true;
    while (running) {
        if (a.poll()) {
            unix::Socket s = a.accept();
            neighbors = neighbors + net::Machine(s);
            std::cout << "connected " << s.remote()->str() << "\n";
        }
        neighbors.update();
    }
}


int main() {
    accept_connections(2620);
    return 0;
}
