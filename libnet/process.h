#pragma once

#include <vector>

#include "queue.h"

namespace net {


class Node {
public:
    using channel_t = util::Channel<util::Binary>;

    Node();
    virtual ~Node();

    void run();

    virtual void run_thread() const = 0;
    virtual void poll(Queue &q) const = 0;

private:
    std::vector<Node *> subnodes;
    std::vector<channel_t *> channels;

};


class Process {
public:
    using ptr_t = std::unique_ptr<Node>;
    using set_t = std::vector<ptr_t>;

    Process();
    virtual ~Process();

    set_t &producers();

    void run();
    void stop();

private:
    size_t thread_count;
    set_t pd;
    Queue queue;

};


}
