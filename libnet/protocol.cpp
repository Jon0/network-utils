#include "protocol.h"

namespace net {


Protocol::Protocol() {}
Protocol::~Protocol() {}


std::string Protocol::to_string() const {
    return params;
}


void Protocol::from_string(const std::string &s) {
    params = s;
}


}
