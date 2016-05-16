#pragma once

#include <iostream>

#include <libunix/stream.h>

#include "cluster.h"

namespace net {


class GroupRequest {
public:
    GroupRequest(const unix::filedesc_t &desc);
    virtual ~GroupRequest();

    void request_neighbors();

private:
    unix::BinaryStream stream;

};


class GroupRespond {
public:
    GroupRespond(const Cluster &c, const unix::filedesc_t &desc);
    virtual ~GroupRespond();

    bool active();
    void update();

private:
    const Cluster cluster;
    unix::BinaryStream stream;
    std::string input;

    void parse_buffer();
};


}
