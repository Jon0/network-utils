#pragma once

#include "queue.h"

namespace net {


class Producer {
public:
    virtual ~Producer() {}
    virtual void poll(Queue &q);
};


}
