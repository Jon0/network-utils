#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libutil/channel.h"

namespace prot {

class Context;

class Protocol {
public:
    using channel_t = util::Channel;

    ~Protocol() {}
    virtual std::unique_ptr<Protocol> copy() const = 0;
    virtual void chan(channel_t *c) const = 0;
    virtual void event(Context *ct, channel_t *ch) const = 0;
};


class Translator {
public:

private:
    std::unique_ptr<Protocol> a, b;
};


}
