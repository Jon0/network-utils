#include "process.h"

namespace net {


Node::Node() {}
Node::~Node() {}
void Node::run() {}


Process::Process()
    :
    thread_count(1) {}


Process::~Process() {}


Process::set_t &Process::producers() {
    return pd;
}


void Process::run() {
    while (thread_count) {

    }
}


void Process::stop() {
    thread_count = 0;
}


}
