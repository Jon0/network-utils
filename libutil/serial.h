#pragma once

#include "channel.h"

namespace util {


class Serialisable {
public:
    virtual bool valid() const = 0;
    virtual read(Channel &c) = 0;
    virtual write(Channel &c) = 0;
};


}
