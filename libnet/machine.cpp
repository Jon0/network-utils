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


unix::NetAddress *Machine::addr() const {
    return socket->remote();
}


bool Machine::connected() const {
    return stream.good();
}


void Machine::log(const std::string &msg) const {
    std::cout << "[" << id() << "] " << msg << "\n";
}


std::string Machine::pop() {
    std::string buf;
    stream.read_all(buf);
    return buf;
}


void Machine::send(const std::string &msg) {
    stream.write_all(msg);
}

}
