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


GroupRespond::GroupRespond(const Cluster &c, const unix::filedesc_t &fd)
    :
    cluster(c),
    fd(fd) {}


GroupRespond::~GroupRespond() {}


bool GroupRespond::active() {
    return !fd.eof();
}


void GroupRespond::update() {
    std::iostream stream(&fd);
    std::string temp;
    stream >> temp;
    buffer += temp;
    std::cout << "buffer: " << buffer;
    stream << "response\n";
}


}
