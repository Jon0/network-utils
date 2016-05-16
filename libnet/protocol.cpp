#include "protocol.h"

namespace net {


GroupRequest::GroupRequest(const unix::filedesc_t &desc)
    :
    stream(desc) {}


GroupRequest::~GroupRequest() {}


void GroupRequest::request_neighbors() {
    stream.write_all("reqn\n");

    std::string response;
    stream.read_all(response);

    std::cout << "response: " << response << "\n";
}


GroupRespond::GroupRespond(const Cluster &c, const unix::filedesc_t &desc)
    :
    cluster(c),
    stream(desc) {}


GroupRespond::~GroupRespond() {}


bool GroupRespond::active() {
    return stream.good();
}


void GroupRespond::update() {
    std::string temp;
    stream.read_all(temp);
    if (!temp.empty()) {
        input += temp;
        parse_buffer();
    }
}


void GroupRespond::parse_buffer() {
    if (!input.empty()) {
        std::cout << "input: " << input << "\n";
        stream.write_all("response\n");
    }
}


}
