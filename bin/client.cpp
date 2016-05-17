#include <iostream>

#include <libutil/strings.h>
#include <libunix/address.h>
#include <libnet/protocol.h>


void test_connect(const std::string &addr) {
    unix::IPv4 ip = unix::parse_ipv4(addr);
    std::cout << "connecting to " << ip.str() << "\n";

    net::GroupRequest r(ip.connect(2620));
    r.request_neighbors();
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Use:\n\tnclient address\n";
        return 0;
    }
    test_connect(argv[1]);
    return 0;
}
