#pragma once

#include <libunix/file.h>

namespace net {

class GroupProtocol {
public:
    GroupProtocol(const unix::filedesc_t &fd);
    virtual ~GroupProtocol();

private:
    unix::FileDesc fd;

};

}
