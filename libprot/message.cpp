#include <iostream>

#include "message.h"

namespace prot {


Message::Message() {}


Message::Message(const std::string &init)
    :
    msg(init) {}


Message::~Message() {}


std::string Message::str() const {
    return msg;
}


bool Message::valid() const {
    return true;
}


bool Message::read(util::BinaryStream &s) {
    if (s.available() < sizeof(int32_t)) {
        return false;
    }
    int32_t length = s.peek_type<int32_t>();
    std::cout << "Length is " << length << "\n";
    if (s.available() < length + sizeof(int32_t)) {
        return false;
    }
    s.read_some(sizeof(int32_t));
    msg = s.read_some(length);
    return true;
}


bool Message::write(util::BinaryStream &s) {
    int32_t size = msg.size();
    s.write_type(size);
    s.write_all(msg);
    return true;
}


}
