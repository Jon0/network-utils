#include <iostream>

#include "stream.h"

namespace unix {


BinaryStream::BinaryStream(const filedesc_t &fd)
    :
    fd(fd) {}


BinaryStream::~BinaryStream() {}


bool BinaryStream::good() const {
    return !fd.eof();
}


std::streamsize BinaryStream::read_all(std::string &buf) {
    std::streamsize done = fd.read(in_buffer, buffersize);
    if (done > 0) {
        buf += std::string(in_buffer, done);
    }
    return done;
}


std::streamsize BinaryStream::write_all(const std::string &buf) {
    return fd.write(buf.c_str(), buf.size());
}


bool BinaryStream::matchstr(const std::string &str) {
    // TODO
    return false;
}


}
