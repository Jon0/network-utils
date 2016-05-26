#include "protocol.h"

namespace net {


Message::Message(unix::FileDesc *desc)
    :
    stream(desc) {}


Message::~Message() {}


void Message::request_neighbors() {
    stream.write_all("reqn\n");

    std::string response;
    stream.read_all(response);

    std::cout << "response: " << response << "\n";
}


std::string Message::recv_msg(const std::string &msg) {
    return "";
}


bool Message::valid() const {}
void Message::read(util::Channel &c) {}
void Message::write(util::Channel &c) {}


}
