#pragma once

#include <libunix/socket.h>
#include <libunix/stream.h>

#include "channel.h"

namespace net {


class Machine {
public:
    using key_t = std::string;

    Machine(const unix::Socket &s);
    virtual ~Machine();

    key_t id() const;
    bool connected() const;
    void update(Handler *hdl);

private:
    unix::Socket socket;
    unix::BinaryStream stream;
    std::string input;

};


}
