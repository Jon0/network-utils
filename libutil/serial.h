#pragma once

#include "channel.h"

namespace util {


class Serialisable {
public:
    virtual bool valid() const = 0;
    virtual void read(Channel &c) = 0;
    virtual void write(Channel &c) = 0;
};


}
