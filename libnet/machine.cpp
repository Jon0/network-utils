#include <iostream>

#include <libunix/socket.h>

#include "machine.h"

namespace net {


Machine::Machine(unix::NetAddress *addr, unsigned short portnum)
    :
    socket(std::make_shared<unix::Socket>(addr, portnum)),
    stream(socket.get()) {}


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


Machine::messages_t Machine::poll() {
    messages_t result;
    bool parse = true;
    while (parse) {
        prot::Message msg;
        parse = msg.read(stream);
        if (parse) {
            result.emplace_back(msg);
        }
    }
    return result;
}


void Machine::send(prot::Message &msg) {
    msg.write(stream);
}


void Machine::send(const std::string &msg) {
    stream.write_all(msg);
}

}
