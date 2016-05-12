#include <fcntl.h>
#include <unistd.h>

#include "file.h"

namespace unix {


void c_error(const char *msg) {
	perror(msg);
	exit(1);
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
    fd(fd) {}


FileDesc::~FileDesc() {
    ::close(fd);
}


filedesc_t FileDesc::id() const {
    return fd;
}


}
