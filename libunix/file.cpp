#include <iostream>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "file.h"

namespace unix {


void c_error(const std::string &msg) {
	std::cout << msg << ": " << std::string(::strerror(errno)) << "\n";
}


int set_nonblocking(int fd) {
    int flags = ::fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        flags = 0;
    }
    return ::fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


FilePath::FilePath(const std::string &p)
    :
    path(p) {}


bool FilePath::empty() const {
    return path.empty();
}


bool FilePath::absolute() const {
    return !relative();
}


bool FilePath::relative() const {
    return path.empty() || path.at(0) != '/';
}


FilePath FilePath::operator+(const FilePath &fp) const {
    return FilePath(path + "/" + fp.path);
}


filedesc_t FilePath::open(fileopts_t opts) const {
    return ::open(path.c_str(), opts);
}


FileDesc::FileDesc(const filedesc_t &fd)
    :
    fd(fd),
 	eofbit(false) {
	set_nonblocking(fd);
}


FileDesc::~FileDesc() {
    if (fd >= 0) {
		::close(fd);
	}
}


bool FileDesc::operator==(const FileDesc &f) const {
	return fd == f.fd;
}


filedesc_t FileDesc::id() const {
    return fd;
}


bool FileDesc::eof() const {
	return eofbit;
}


bool FileDesc::poll(short events) const {
    struct pollfd fds{fd, events, events};
    int result = ::poll(&fds, 1, 0);
	if (result == -1) {
		c_error("ERROR on poll");
	}
	return result;
}


std::string FileDesc::name() const {
	return "fd " + std::to_string(fd);
}


bool FileDesc::open() const {
	return !eof();
}


bool FileDesc::readable() const {
	return poll(POLLIN);
}


bool FileDesc::writable() const {
	return poll(POLLOUT);
}


std::streamsize FileDesc::read(char *buf, std::size_t count) {
	return checkerr(::read(fd, buf, count));
}


std::streamsize FileDesc::write(const char *buf, std::size_t count) {
	return checkerr(::write(fd, buf, count));
}


std::streamsize FileDesc::checkerr(const std::streamsize &done) {
	if (done < 0) {
		c_error("ERROR fd " + std::to_string(fd));
	}
	if (done == EPIPE || done == 0) {
	    eofbit = true;
	}
	return done;
}


}
