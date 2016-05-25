#include <iostream>

#include "context.h"

namespace prot {


Context::Context()
    :
    thread_count(1) {}


Context::~Context() {}


void Context::run() {
    while (thread_count) {
        for (auto &p : runproc) {
            p->update(this);
        }
        merge();
    }
}


void Context::stop() {
    thread_count = 0;
}


void Context::add(const ptr_t &i) {
    std::lock_guard<std::mutex> lock(addlock);
    addproc.emplace_back(i);
}


void Context::merge() {
    std::lock_guard<std::mutex> lock(addlock);
    for (auto &p : addproc) {
        runproc.emplace_back(p);
    }
    addproc.clear();
}


}
