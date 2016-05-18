#include <iostream>

#include <libunix/socket.h>
#include <libnet/cluster.h>
#include <libnet/protocol.h>

int main() {
    int port = 2620;
    std::cout << "listen on port " << port << "\n";
    unix::TcpAcceptor a(port);
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
