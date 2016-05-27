#pragma once

#include <iostream>

#include <libutil/serial.h>

#include "cluster.h"

namespace net {


class Message : public util::Serialisable {
public:
    Message(unix::FileDesc *desc);
    virtual ~Message();

    void request_neighbors();

    std::string recv_msg(const std::string &msg);

    bool valid() const override;
    void read(util::Channel &c) override;
    void write(util::Channel &c) override;

private:
    unix::BinaryStream stream;

};


}
