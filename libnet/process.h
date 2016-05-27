#pragma once

#include <libprot/context.h>

#include "cluster.h"

namespace net {


class ClusterAcceptor : public prot::ContextItem {
public:
    ClusterAcceptor(Cluster &c, unsigned short portnum);
    virtual ~ClusterAcceptor();
    void accept();

    void update(prot::Context *c) override;

private:
    Cluster *cl;
    unix::TcpAcceptor acceptor;

};



}
