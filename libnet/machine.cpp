#include <libunix/socket.h>

#include "machine.h"

namespace net {


Machine::Machine(const unix::Socket &s)
    :
    socket(s),
    stream(&socket) {}


Machine::~Machine() {}


Machine::key_t Machine::id() const {
    return socket.remote()->str();
}


bool Machine::connected() const {
    return stream.good();
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


void Machine::run_thread() const {

}


void Machine::poll(Queue &q) const {

}


}
