#include <iostream>

#include "protocol.h"

namespace net {


GroupRequest::GroupRequest(const unix::filedesc_t &fd)
    :
    fd(fd) {}


GroupRequest::~GroupRequest() {}


void GroupRequest::request_neighbors() {
    std::iostream stream(&fd);

    stream << "reqn\n";

    std::string response;
    stream >> response;

    std::cout << "response: " << response << "\n";
}


GroupRespond::GroupRespond(const Cluster &c)
    :
    cluster(c) {}


GroupRespond::~GroupRespond() {}


void GroupRespond::respond(unix::FileDesc &fd) {
    std::iostream stream(&fd);

    std::string buf;
    stream >> buf;
    std::cout << buf;
    stream << "response\n";
}


}
