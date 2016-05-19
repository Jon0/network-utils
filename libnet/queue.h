#pragma once

#include <memory>
#include <queue>
#include <vector>

#include <libutil/memory.h>

namespace net {


enum class net_type {
    cluster,
    machine,
    channel
};


class Event {
public:
    ~Event() {}
};


class Queue {
public:
    Queue();
    ~Queue();

    Queue operator+(const Queue &q) const;

private:
    std::vector<std::shared_ptr<Event>> e;

};


}
