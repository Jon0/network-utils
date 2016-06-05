#include <iostream>

#include "message.h"

namespace prot {


Message::Message()
    :
    id_value(0),
    initialised(false) {}


Message::id_t Message::id() const {
    return id_value;
}

void Message::init(const Message &msg) {
    init(msg.id_value, msg.to_string());
}


void Message::init(int32_t newid, const std::string &msg) {
    id_value = newid;
    from_string(msg);
    initialised = true;
}


bool Message::valid() const {
    return true;
}


bool Message::read(util::BinaryStream &s) {
    constexpr size_t headersize = sizeof(id_t) + sizeof(length_t);
    if (s.available() < headersize) {
        return false;
    }
    id_t newid = s.peek_type<id_t>();
    length_t length = s.peek_type<length_t>(sizeof(id_t));
    if (s.available() < length + headersize) {
        return false;
    }
    s.read_some(headersize);
    init(newid, s.read_some(length));
    return true;
}


bool Message::write(util::BinaryStream &s) {
    if (!initialised) {
        std::cout << "Writing uninitialised message\n";
    }
    std::string msg = to_string();
    length_t size = msg.size();
    s.write_type(id_value);
    s.write_type(size);
    s.write_all(msg);
    return true;
}


}
