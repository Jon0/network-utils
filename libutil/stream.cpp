#include <iostream>

#include "stream.h"

namespace util {


BinaryStream::BinaryStream(Channel *c)
    :
    c(c) {}


BinaryStream::~BinaryStream() {}


bool BinaryStream::good() const {
    return c->open();
}


size_t BinaryStream::available() {
    sync_input();
    return strbuffer.size();
}


std::string BinaryStream::peek_some(size_t len) {
    sync_input();
    ensure_available(len);
    return strbuffer.substr(0, len);
}


std::string BinaryStream::read_some(size_t len) {
    std::string result = peek_some(len);
    strbuffer = strbuffer.substr(len);
    return result;
}


void BinaryStream::read_all(std::string &buf) {
    sync_input();
    buf = strbuffer;
}


void BinaryStream::write_all(const std::string &buf) {
    while (!c->writable()) {}
    auto done = c->write(buf.c_str(), buf.size());
    if (done < buf.size()) {
        std::cout << "incomplete write\n";
    }
    else {
        std::cout << "sent: " << buf << "\n";
    }
}


bool BinaryStream::matchstr(const std::string &str) {
    // TODO
    return false;
}


void BinaryStream::ensure_available(size_t len) const {
    if (strbuffer.size() < len) {
        std::cerr << "Require " << len << " bytes (" << strbuffer.size() << " available)\n";
    }
}


void BinaryStream::sync_input() {
    while (c->readable()) {
        std::streamsize done = c->read(in_buffer, buffersize);
        if (done > 0) {
            strbuffer += std::string(in_buffer, done);
        }
    }
}


}
