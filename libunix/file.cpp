#include <iostream>

#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#include "file.h"

namespace unix {


void c_error(const char *msg) {
	std::cout << std::string(::strerror(errno)) << "\n";
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
    fd(fd) {
	set_nonblocking(fd);
	this->setg(in_buffer, in_buffer, in_buffer);
	this->setp(out_buffer, out_buffer + buffersize - 1);
}


FileDesc::~FileDesc() {
    if (fd >= 0) {
		sync();
		::close(fd);
	}
}


bool FileDesc::operator==(const FileDesc &f) const {
	return fd == f.fd;
}


filedesc_t FileDesc::id() const {
    return fd;
}


bool FileDesc::poll() const {
    struct pollfd fds{fd, POLLIN, POLLIN};
    int result = ::poll(&fds, 1, 0);
	if (result == -1) {
		c_error("ERROR on poll");
	}
	return result;
}


int FileDesc::overflow(int c) {
	if (!traits_type::eq_int_type(c, traits_type::eof())) {
		*pptr() = traits_type::to_char_type(c);
		pbump(1);
	}
	return sync() == -1
		? traits_type::eof()
		: traits_type::not_eof(c);
}


int FileDesc::sync() {
	if (pbase() != pptr()) {
		std::streamsize size(pptr() - pbase());
		std::streamsize done(::write(fd, out_buffer, size));

		// The code below assumes that it is success if the stream made
		// some progress. Depending on the needs it may be more
		// reasonable to consider it a success only if it managed to
		// write the entire buffer and, e.g., loop a couple of times
		// to try achieving this success.
		if (done > 0) {
			std::copy(this->pbase() + done, this->pptr(), this->pbase());
			this->setp(this->pbase(), this->epptr());
			this->pbump(size - done);
		}
		else {
			std::cout << "fd " << fd << ": write error " << done << "\n";
			return -1;
		}
	}
	return this->pptr() != this->epptr()? 0: -1;
}


int FileDesc::underflow() {
	if (this->gptr() == this->egptr()) {
		std::streamsize pback(std::min(gptr() - eback(), std::ptrdiff_t(16 - sizeof(size_t))));
		std::copy(this->egptr() - pback, this->egptr(), this->eback());
		int done(::read(fd, eback() + pback, buffersize));
		if (done < 0) {
			std::cout << "fd " << fd << ": read error " << done << "\n";
		}
		this->setg(this->eback(),
				   this->eback() + pback,
				   this->eback() + pback + std::max(0, done));
	}
	return this->gptr() == this->egptr()
		? traits_type::eof()
		: traits_type::to_int_type(*this->gptr());
}

}
