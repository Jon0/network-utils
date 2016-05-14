#pragma once

#include <string>
#include <sstream>

namespace unix {

using filedesc_t = int;
using fileopts_t = int;


void c_error(const char *msg);


int set_nonblocking(int fd);


class FilePath {
public:
    FilePath(const std::string &p);

    bool empty() const;
    bool absolute() const;
    bool relative() const;

    FilePath operator+(const FilePath &fp) const;

    filedesc_t open(fileopts_t opts) const;

private:
    const std::string path;

};


class FileDesc : public std::streambuf {
public:
    using traits_type = std::streambuf::traits_type;
    static constexpr size_t buffersize = 1024;

    FileDesc(const filedesc_t &fd);
    ~FileDesc();

    bool operator==(const FileDesc &f) const;

    filedesc_t id() const;

    bool poll() const;

protected:
	int overflow(int c);
	int underflow();
	int sync();

private:
    const filedesc_t fd;
	char out_buffer[buffersize];
	char in_buffer[buffersize + 16 - sizeof(size_t)];

};


}
