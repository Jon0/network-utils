#pragma once

#include <memory>

#include "libutil/channel.h"

namespace prot {


class Interface : public util::Channel<util::Binary> {
public:
    Interface();
    ~Interface();

    virtual void recv() = 0;
};


class Protocol {
public:
    Protocol();
    ~Protocol();

    virtual std::unique_ptr<Protocol> copy() const = 0;
};


}
