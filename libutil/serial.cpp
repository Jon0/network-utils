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


String::String() {}
String::String(const std::string &s)
    :
    str(s) {
    init();
}


String::~String() {}


std::string String::to_string() const {
    return str;
}


void String::from_string(const std::string &s) {
    str = s;
}


StringList::StringList() {}
StringList::~StringList() {}


std::string StringList::to_string() const {
    array_t arr = to_array();
    std::string result;
    result += itobs(arr.size());
    for (auto &s : arr) {
        std::string elem = s->to_string();
        result += itobs(elem.size());
        result += elem;
    }
    return result;
}


void StringList::from_string(const std::string &s) {
    int_t length = bstoi(s);
    size_t offset = sizeof(int_t);
    for (int i = 0; i < length && offset < s.size(); ++i) {
        std::string elem = s.substr(offset);
        size_t esize = bstoi(elem);
        Stringable *st = at(i);
        if (st) {
            st->from_string(elem.substr(sizeof(int_t), esize));
            offset += sizeof(int_t) + esize;
        }
        else {
            std::cout << "Reading input failed\n";
            return;
        }
    }
}


StringList::int_t StringList::bstoi(const std::string &s) const {
    int_t result;
    std::memcpy(&result, s.c_str(), sizeof(int_t));
    return result;
}


std::string StringList::itobs(const StringList::int_t &i) const {
    char result [sizeof(int_t)];
    std::memcpy(&result, &i, sizeof(int_t));
    return std::string(result, sizeof(int_t));
}


}
