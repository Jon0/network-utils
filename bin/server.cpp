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
        net::GroupRespond r(c);
        if (a.poll()) {
            unix::FileDesc fd(a.acceptfd());
            std::cout << "connected\n";
            r.respond(fd);
        }
    }
}
