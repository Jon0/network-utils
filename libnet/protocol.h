#pragma once

#include <libunix/file.h>

#include "cluster.h"

namespace net {


class GroupRequest {
public:
    GroupRequest(const unix::filedesc_t &fd);
    virtual ~GroupRequest();

    void request_neighbors();

private:
    unix::FileDesc fd;

};


class GroupRespond {
public:
    GroupRespond(const Cluster &c, const unix::filedesc_t &fd);
    virtual ~GroupRespond();

    bool active();
    void update();

private:
    const Cluster cluster;
    unix::FileDesc fd;
    std::string buffer;
};


}
