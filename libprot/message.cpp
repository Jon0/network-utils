#include <iostream>

#include "message.h"

namespace prot {


Message::Message() {}
Message::~Message() {}


bool Message::valid() const {
    return true;
}


bool Message::read(util::BinaryStream &s) {
    if (s.available() < 4) {
        return false;
    }
    int32_t length = s.peek_type<int32_t>();
    if (s.available() < length) {
        return false;
    }
    std::string buf;
    s.read_all(buf);
    std::cout << "recv: " << buf << "\n";
    return true;
}


bool Message::write(util::BinaryStream &s) {
    s.write_all("output\n");
    return true;
}


}
