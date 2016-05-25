#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "libutil/channel.h"

#include "interface.h"

namespace prot {


class Context {
public:
    using channel_t = util::Channel;
    using ptr_t = std::shared_ptr<Interface>;
    using set_t = std::vector<ptr_t>;

    Context();
    virtual ~Context();

    void run();
    void stop();
    void add(const ptr_t &i);
    void merge();

private:
    size_t thread_count;
    set_t runproc, addproc;
    std::mutex addlock;

};


}
