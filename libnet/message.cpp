#include "message.h"

namespace net {


Message::Message() {}
Message::~Message() {}


bool Message::valid() const {
    return true;
}


void Message::read(util::Channel &c) {
    char buf [1024];
    while (c.ready()) {
        auto done = c.read(buf, 1024);
        msg += std::string(buf, done);
    }
}


void Message::write(util::Channel &c) {
    c.write(msg.c_str(), msg.size());
    msg = "";
}


}
