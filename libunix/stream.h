#pragma once

#include "file.h"

namespace unix {

class BinaryStream {
public:
    static constexpr size_t buffersize = 1024;

    BinaryStream(const filedesc_t &fd);
    virtual ~BinaryStream();

    bool good() const;

    std::streamsize read_all(std::string &buf);
    std::streamsize write_all(const std::string &buf);

    bool matchstr(const std::string &str);

private:
    FileDesc fd;
	char in_buffer[buffersize];
	char out_buffer[buffersize];

};


}
