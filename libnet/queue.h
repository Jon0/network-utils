#pragma once

#include <memory>
#include <queue>
#include <vector>

#include <libunix/socket.h>

namespace net {


enum class net_type {
    cluster,
    machine,
    channel
};


class Event {
public:
    ~Event() {}

private:
    int type;

};


class Queue {
public:
    Queue();
    ~Queue();

    Queue operator+(const Queue &q) const;

    void socket_open(const unix::Socket &s);

private:
    std::vector<std::shared_ptr<Event>> e;

};


}
