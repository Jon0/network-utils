#include <iostream>

#include <libunix/socket.h>

#include "machine.h"

namespace net {


MachineTask::MachineTask(unix::NetAddress *addr, unsigned short portnum)
    :
    id(0),
    socket(std::make_shared<unix::Socket>(addr, portnum)),
    queue(std::make_shared<prot::Queue>(socket.get())) {}


MachineTask::MachineTask(const MachineTask::socket_t &s)
    :
    id(0),
    socket(s),
    queue(std::make_shared<prot::Queue>(socket.get())) {}


MachineTask::~MachineTask() {
    if (id) {
        context->remove(id);
    }
}


bool MachineTask::connected() const {
    return socket->open();
}


void MachineTask::log(const std::string &msg) const {
    std::cout << "[" << socket->remote()->str() << "] " << msg << "\n";
}


MachineTask::socket_t MachineTask::connection() const {
    return socket;
}


MachineTask::queue_t MachineTask::handler() const {
    return queue;
}


void MachineTask::enable(prot::Context *ct) {
    log("enable");
    context = ct;
    id = context->add(queue);
}


Machine::Machine(Machine::context_t *ctxt, Machine::task_t ctrl)
    :
    is_server(false),
    context(ctxt),
    control(ctrl),
    hostname(control.connection()->remote()) {
    control.enable(context);
}


Machine::~Machine() {}


Host Machine::host() const {
    return hostname;
}


bool Machine::server() const {
    return is_server;
}


unix::NetAddress *Machine::addr() const {
    return control.connection()->remote();
}


Machine::queue_t Machine::ctrlqueue() const {
    return control.handler();
}


void Machine::start(const MachineTask &m) {
    tasks.push_back(m);
    tasks.back().enable(context);
}


}
