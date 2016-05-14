#include "protocol.h"

namespace net {


GroupRequest::GroupRequest(const unix::filedesc_t &desc)
    :
    fd(desc) {}


GroupRequest::~GroupRequest() {}


void GroupRequest::request_neighbors() {
    std::iostream stream(&fd);

    stream << "reqn\n";

    std::string response;
    stream >> response;

    std::cout << "response: " << response << "\n";
}


GroupRespond::GroupRespond(const Cluster &c, const unix::filedesc_t &desc)
    :
    cluster(c),
    fd(fd),
    stream(&fd) {}


GroupRespond::~GroupRespond() {}


bool GroupRespond::active() {
    return !fd.eof();
}


void GroupRespond::update() {
    std::string temp;
    stream >> temp;
    buffer += temp;
    std::cout << "buffer: " << buffer << "\n";
    stream << "response\n";
}


}
