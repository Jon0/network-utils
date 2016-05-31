#pragma once

#include <libunix/socket.h>
#include <libutil/stream.h>

#include "channel.h"

namespace net {


class MachineAttr {
public:

private:
    int users, permissions, devices;
};


/**
 * Additional sockets per task
 */
class MachineTask {
public:
    using socket_t = std::shared_ptr<unix::Socket>;

private:
    socket_t socket;
    util::BinaryStream stream;

};

class Machine {
public:
    using key_t = std::string;
    using socket_t = std::shared_ptr<unix::Socket>;

    Machine(const socket_t &s);
    virtual ~Machine();

    key_t id() const;
    unix::NetAddress *addr() const;
    bool connected() const;
    void log(const std::string &msg) const;

    std::string pop();
    void send(const std::string &msg);

private:
    MachineAttr attributes;
    socket_t socket;
    util::BinaryStream stream;
    std::string input;

};


}
