#pragma once

#include <iostream>

#include <libunix/file.h>

#include "cluster.h"

namespace net {


class GroupRequest {
public:
    GroupRequest(const unix::filedesc_t &desc);
    virtual ~GroupRequest();

    void request_neighbors();

private:
    unix::FileDesc fd;

};


class GroupRespond {
public:
    GroupRespond(const Cluster &c, const unix::filedesc_t &desc);
    virtual ~GroupRespond();

    bool active();
    void update();

private:
    const Cluster cluster;
    unix::FileDesc fd;
    std::iostream stream;
    std::string buffer;
};


}
