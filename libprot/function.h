#pragma once

namespace prot {

class Function {
public:
    using stream_t = int;

    virtual ~Function() {}
    virtual void apply(stream_t &in, stream_t &out) const = 0;

};

}
