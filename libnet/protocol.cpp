#include "protocol.h"

namespace net {


GroupProtocol::GroupProtocol(const unix::filedesc_t &fd)
    :
    fd(fd) {}


GroupProtocol::~GroupProtocol() {}


}
