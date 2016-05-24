#pragma once

#include <vector>

#include "queue.h"

namespace net {


class Node {
public:
    using channel_t = util::Channel;
    using ptr_t = std::unique_ptr<Node>;
    using set_t = std::vector<ptr_t>;

    Node();
    virtual ~Node();

    set_t &nodes();

    void run();
    void stop();

    virtual void update() const = 0;
    virtual void poll(Queue &q) const = 0;

private:
    size_t thread_count;
    set_t subnodes;
    std::vector<channel_t *> channels;

};


}
