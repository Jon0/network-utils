#include <iostream>

#include "serial.h"

namespace util {


Stringable::Stringable()
    :
    initialised(false) {}


void Stringable::init() {
    initialised = true;
}


void Stringable::init(const Stringable &msg) {
    init(msg.to_string());
}


void Stringable::init(const std::string &msg) {
    from_string(msg);
    init();
}


bool Stringable::valid() const {
    return initialised;
}


bool Stringable::read(util::BinaryStream &s) {
    constexpr size_t headersize = sizeof(length_t);
    if (s.available() < headersize) {
        return false;
    }
    length_t length = s.peek_type<length_t>();
    if (s.available() < length + headersize) {
        return false;
    }
    s.read_some(headersize);
    init(s.read_some(length));
    return true;
}


bool Stringable::write(util::BinaryStream &s) {
    if (!initialised) {
        std::cout << "Writing uninitialised message\n";
    }
    std::string msg = to_string();
    length_t size = msg.size();
    s.write_type(size);
    s.write_all(msg);
    return true;
}


}
