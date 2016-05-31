#pragma once

#include <string>

#include <poll.h>

#include <libutil/channel.h>

namespace unix {

using filedesc_t = int;
using fileopts_t = int;


void c_error(const std::string &msg);


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


class FileDesc : public util::Channel {
public:
    FileDesc(const filedesc_t &fd);
    virtual ~FileDesc();

    bool operator==(const FileDesc &f) const;

    filedesc_t id() const;
    bool eof() const;
    bool poll(short events = POLLIN) const;

    virtual bool open() const override;
    bool ready() const override;
    std::streamsize read(char *buf, std::size_t count) override;
    std::streamsize write(const char *buf, std::size_t count) override;

private:
    std::streamsize checkerr(const std::streamsize &done);

    const filedesc_t fd;
    bool eofbit;

};


}
