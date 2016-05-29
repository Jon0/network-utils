#pragma once

#include <iostream>

#include <libutil/serial.h>

#include "cluster.h"

namespace net {


class Message : public util::Serialisable {
public:
    Message();
    virtual ~Message();

    bool valid() const override;
    void read(util::Channel &c) override;
    void write(util::Channel &c) override;

private:
    std::string msg;

};


}
