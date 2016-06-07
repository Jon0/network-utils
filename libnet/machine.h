#pragma once

#include <libprot/message.h>
#include <libprot/queue.h>
#include <libunix/socket.h>
#include <libutil/stream.h>

#include "channel.h"

namespace net {


struct host_addr {
    std::shared_ptr<unix::NetAddress> ip;

};


class MachineAttr {
public:

private:
    int users, permissions, devices;
};


/**
 * Additional sockets per task
 */
class MachineTask {
public:
    using id_t = typename prot::Context::id_t;
    using socket_t = std::shared_ptr<unix::Socket>;
    using queue_t = std::shared_ptr<prot::Queue>;
    using messages_t = std::vector<util::Stringable>;

    MachineTask(unix::NetAddress *addr, unsigned short portnum);
    MachineTask(const socket_t &s);
    virtual ~MachineTask();

    bool connected() const;
    void log(const std::string &msg) const;

    socket_t connection() const;
    queue_t handler() const;

    void enable(prot::Context *ct);

private:
    prot::Context *context;
    id_t id;
    socket_t socket;
    queue_t queue;

};


class Machine {
public:
    using context_t = prot::Context;
    using key_t = std::string;
    using task_t = MachineTask;
    using queue_t = typename task_t::queue_t;
    using tasklist_t = std::vector<task_t>;
    using serial_t = std::shared_ptr<util::Serialisable>;

    Machine(context_t *ctxt, task_t ctrl);
    virtual ~Machine();

    key_t id() const;
    bool server() const;
    unix::NetAddress *addr() const;
    queue_t ctrlqueue() const;

    void start(const MachineTask &m);

private:
    bool is_server;
    context_t *context;
    MachineAttr attributes;
    task_t control;
    tasklist_t tasks;
    std::string input;

};


}
