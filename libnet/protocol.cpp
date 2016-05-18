#include "protocol.h"

namespace net {


GroupRequest::GroupRequest(unix::FileDesc *desc)
    :
    stream(desc) {}


GroupRequest::~GroupRequest() {}


void GroupRequest::request_neighbors() {
    stream.write_all("reqn\n");

    std::string response;
    stream.read_all(response);

    std::cout << "response: " << response << "\n";
}


std::string GroupRequest::recv_msg(const std::string &msg) {
    return "";
}


GroupRespond::GroupRespond(const Cluster &c)
    :
    cluster(c) {}


GroupRespond::~GroupRespond() {}


std::string GroupRespond::recv_msg(const std::string &msg) {
    if (!msg.empty()) {
        std::cout << "input: " << msg << "\n";
    }
    return "response\n";
}





}
