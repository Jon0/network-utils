#include <iostream>

#include "buffer.h"

namespace unix {


Buffer::Buffer(const filedesc_t &fd)
    :
    fd(fd) {
    setg(in_buffer, in_buffer, in_buffer);
    setp(out_buffer, out_buffer + buffersize - 1);
}


Buffer::~Buffer() {
    sync();
}


int Buffer::sync() {
	if (pbase() != pptr()) {
		std::streamsize size = pptr() - pbase();
		std::streamsize done = fd.write(out_buffer, size);
		if (done > 0) {
			std::copy(pbase() + done, pptr(), pbase());
			setp(pbase(), epptr());
			pbump(size - done);
		}
		else {
			c_error("ERROR on write");
			std::cout << "fd " << fd.id() << ": write error " << done << "\n";
		}
	}
	return pptr() != epptr()? 0 : -1;
}


std::streamsize Buffer::showmanyc() {
    std::cout << "polling\n";
    return fd.poll() ? 0 : -1;
}


int Buffer::underflow() {
	if (gptr() == egptr()) {
		std::streamsize pback = std::min(gptr() - eback(), std::ptrdiff_t(diffsize));
		std::copy(egptr() - pback, egptr(), eback());
		std::streamsize done = fd.read(eback() + pback, buffersize);
		if (done < 0) {
			c_error("ERROR on read");
			std::cout << "fd " << fd.id() << ": read error " << done << "\n";
		}
		setg(eback(), eback() + pback, eback() + pback + std::max(std::streamsize(0), done));
	}
	return gptr() == egptr() ? traits_type::eof() : traits_type::to_int_type(*gptr());
}


int Buffer::overflow(int c) {
	if (!traits_type::eq_int_type(c, traits_type::eof())) {
		*pptr() = traits_type::to_char_type(c);
		pbump(1);
	}
	return sync() == -1 ? traits_type::eof() : traits_type::not_eof(c);
}


}
