#include "process.h"

namespace net {


Node::Node()
    :
    thread_count(1) {}


Node::~Node() {}


Node::set_t &Node::nodes() {
    return subnodes;
}


void Node::run() {
    while (thread_count) {
        for (auto &p : subnodes) {
            p->update();
        }
    }
}


void Node::stop() {
    thread_count = 0;
}


}
