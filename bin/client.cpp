#include <iostream>

#include <libutil/strings.h>
#include <libunix/socket.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Use:\n\tnclient port\n";
    }

    auto ip = util::split<std::vector, std::string>(argv[1], ".");
    std::vector<unsigned char> v;
    for (auto &e: ip) {
        std::cout << e << ".";
        v.push_back(stoi(e));
    }
    std::cout << "\n";

    unix::IPv4 addr({v.at(0), v.at(1), v.at(2), v.at(3)});
    addr.connect(2620);

}
