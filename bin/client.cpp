#include <iostream>

#include <libutil/strings.h>
#include <libunix/socket.h>
#include <libnet/protocol.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Use:\n\tnclient port\n";
    }

    auto ip = util::split<std::vector, std::string>(argv[1], ".");
    std::vector<unsigned char> v;
    for (auto &e: ip) {
        v.push_back(stoi(e));
    }

    unix::IPv4 addr({v.at(0), v.at(1), v.at(2), v.at(3)});
    std::cout << "connecting to " << addr.str() << "\n";

    net::GroupRequest r(addr.connect(2620));
    r.request_neighbors();
}
