#include <chrono>
#include <iostream>
#include <thread>

#include "context.h"

namespace prot {


Context::Context()
    :
    thread_count(1),
    next_id(0) {}


Context::~Context() {}


void Context::run() {
    while (thread_count) {
        for (auto &p : runproc) {
            p.second->update(this);
        }
        merge();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void Context::stop() {
    thread_count = 0;
}


Context::id_t Context::add(const ptr_t &i) {
    std::lock_guard<std::mutex> lock(addlock);
    id_t new_id = next_id++;
    addproc.insert(std::make_pair(new_id, i));
    return new_id;
}


void Context::remove(const id_t &i) {
    std::lock_guard<std::mutex> lock(addlock);
    if (runproc.count(i) > 0) {
        rmproc.insert(std::make_pair(i, runproc.at(i)));
    }
}


void Context::merge() {
    std::lock_guard<std::mutex> lock(addlock);
    for (auto &p : addproc) {
        runproc.insert(p);
    }
    addproc.clear();
}


}
