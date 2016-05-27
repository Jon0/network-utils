#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "libutil/channel.h"

namespace prot {


class Context;


class ContextItem {
public:
    virtual void update(Context *ct) = 0;
};


class Context {
public:
    using id_t = int;
    using channel_t = util::Channel;
    using ptr_t = std::shared_ptr<ContextItem>;
    using set_t = std::unordered_map<id_t, ptr_t>;

    Context();
    virtual ~Context();

    void run();
    void stop();
    void add(const ptr_t &i);
    void merge();

private:
    size_t thread_count;
    set_t runproc, addproc;
    id_t next_id;
    std::mutex addlock;

};


}
