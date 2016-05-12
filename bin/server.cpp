#include <iostream>

#include <libunix/socket.h>

int main() {
    std::cout << "listen on port 2620\n";

    unix::TcpAcceptor a(2620);

    a.acceptfd();

    std::cout << "connected\n";
}
