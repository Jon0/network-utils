#include <iostream>

#include <libunix/socket.h>

#include "machine.h"

namespace net {


Machine::Machine(const Machine::socket_t &s)
    :
    socket(s),
    stream(socket.get()) {}


Machine::~Machine() {}


Machine::key_t Machine::id() const {
    return socket->remote()->str();
}


bool Machine::connected() const {
    return stream.good();
}


void Machine::log(const std::string &msg) const {
    std::cout << "[" << id() << "] " << msg << "\n";
}


Machine::socket_t Machine::connection() {
    return socket;
}


void Machine::update(Handler *hdl) {
    std::string temp;
    stream.read_all(temp);
    if (!temp.empty()) {
        input += temp;
        std::string s = hdl->recv_msg(input);
        stream.write_all(s);
    }
}


}
