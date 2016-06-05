#include "protocol.h"

namespace net {

Request::Request() {}
Request::~Request() {}


std::string Request::to_string() const {
    return rstr;
}


void Request::from_string(const std::string &s) {
    rstr = s;
}


Response::Response() {}
Response::~Response() {}


std::string Response::to_string() const {
    return params;
}


void Response::from_string(const std::string &s) {
    params = s;
}


}
