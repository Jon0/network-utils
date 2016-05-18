#include <iostream>

#include "stream.h"

namespace unix {


BinaryStream::BinaryStream(FileDesc *fd)
    :
    fd(fd) {}


BinaryStream::~BinaryStream() {}


bool BinaryStream::good() const {
    return !fd->eof();
}


std::streamsize BinaryStream::read_all(std::string &buf) {
    if (fd->poll(POLLIN)) {
        std::streamsize done = fd->read(in_buffer, buffersize);
        if (done > 0) {
            buf += std::string(in_buffer, done);
        }
        return done;
    }
    return 0;
}


std::streamsize BinaryStream::write_all(const std::string &buf) {
    return fd->write(buf.c_str(), buf.size());
}


bool BinaryStream::matchstr(const std::string &str) {
    // TODO
    return false;
}


}
