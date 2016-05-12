#pragma once

#include <string>

namespace unix {

using filedesc_t = int;
using fileopts_t = int;


void c_error(const char *msg);


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


class FileDesc {
public:
    FileDesc(const filedesc_t &fd);
    ~FileDesc();

    filedesc_t id() const;

private:
    const filedesc_t fd;

};

}
