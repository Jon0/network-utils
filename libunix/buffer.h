#pragma once

#include <sstream>

#include "file.h"

namespace unix {


class Buffer : public std::streambuf {
public:
    static constexpr size_t buffersize = 1024;
    static constexpr size_t diffsize = 16 - sizeof(size_t);
    using traits_type = std::streambuf::traits_type;

    Buffer(const filedesc_t &fd);
    virtual ~Buffer();

protected:
    int sync() override;
    std::streamsize showmanyc() override;
    int underflow() override;
	int overflow(int c) override;

private:
    FileDesc fd;
	char out_buffer[buffersize];
	char in_buffer[buffersize + diffsize];

};


}
