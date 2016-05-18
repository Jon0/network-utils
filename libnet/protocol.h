#pragma once

#include <iostream>

#include <libunix/stream.h>

#include "channel.h"
#include "cluster.h"

namespace net {


class GroupRequest : public Handler {
public:
    GroupRequest(unix::FileDesc *desc);
    virtual ~GroupRequest();

    void request_neighbors();

    std::string recv_msg(const std::string &msg) override;

private:
    unix::BinaryStream stream;

};


class GroupRespond : public Handler {
public:
    GroupRespond(const Cluster &c);
    virtual ~GroupRespond();

    std::string recv_msg(const std::string &msg) override;

private:
    const Cluster cluster;

};


}
