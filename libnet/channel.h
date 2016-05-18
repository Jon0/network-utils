#pragma once

#include <string>

namespace net {


class Handler {
public:
    ~Handler() {}
    virtual std::string recv_msg(const std::string &msg) = 0;
};


class Channel {
public:
    virtual ~Channel() {}
    virtual bool active() const = 0;
    virtual void update() = 0;
};


}
