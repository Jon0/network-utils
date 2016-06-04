#pragma once

#include "stream.h"

namespace util {


class Serialisable {
public:
    virtual ~Serialisable() {}
    virtual bool valid() const = 0;
    virtual bool read(BinaryStream &s) = 0;
    virtual bool write(BinaryStream &s) = 0;
};


}
