#pragma once

#include <stack>
#include <string>

namespace net {


enum class ChannelType {
    requester,
    responder,
    symmetric
};


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
    virtual std::stack<int> protocol() = 0;
};


}
