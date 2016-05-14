#include <iostream>

#include <libunix/socket.h>
#include <libnet/cluster.h>
#include <libnet/protocol.h>

int main() {
    int port = 2620;
    std::cout << "listen on port " << port << "\n";
    unix::TcpAcceptor a(port);
    net::Cluster c({});

    bool running = true;
    while (running) {
        if (a.poll()) {
            std::cout << "connected\n";
            net::GroupRespond r(c, a.acceptfd());
            while (r.active()) {
                r.update();
            }
            std::cout << "replied\n";
        }
    }
}
