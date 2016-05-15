#include <iostream>

#include <libutil/strings.h>
#include <libunix/socket.h>
#include <libnet/protocol.h>


void test_connect(const std::string &addr) {
    auto parts = util::split<std::vector, std::string>(addr, ".");
    std::vector<unsigned char> v;
    for (auto &e: parts) {
        v.push_back(stoi(e));
    }

    unix::IPv4 ip({v.at(0), v.at(1), v.at(2), v.at(3)});
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
