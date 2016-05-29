#pragma once

#include <libunix/socket.h>
#include <libunix/stream.h>

#include "channel.h"

namespace net {


class MachineAttr {
public:

private:
    int users, permissions, devices;
};


class Machine {
public:
    using key_t = std::string;
    using socket_t = std::shared_ptr<unix::Socket>;

    Machine(const socket_t &s);
    virtual ~Machine();

    key_t id() const;
    bool connected() const;
    void log(const std::string &msg) const;
    socket_t connection();
    void update(Handler *hdl);

private:
    MachineAttr attributes;
    socket_t socket;
    unix::BinaryStream stream;
    std::string input;

};


}
