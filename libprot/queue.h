#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <vector>

#include <libutil/serial.h>
#include <libutil/stream.h>

#include "context.h"

namespace prot {


enum class serial_mode_t {
    read,
    write
};


class Handler {
public:
    using serial_t = std::shared_ptr<util::Serialisable>;
    using callback_t = std::function<bool()>;

    Handler(serial_mode_t mode, serial_t srl);
    Handler(serial_mode_t mode, serial_t srl, callback_t fn);
    virtual ~Handler();

    bool do_callback() const;
    bool apply(util::BinaryStream &stream);

    serial_mode_t mode;
    serial_t object;
    callback_t callback;
};


class Queue : public ContextItem {
public:
    using serial_t = typename Handler::serial_t;
    using callback_t = typename Handler::callback_t;

    Queue(util::Channel *c);
    ~Queue();

    void pushr(serial_t srl);
    void pushr(serial_t srl, callback_t fn);
    void pushw(serial_t srl);
    void pushw(serial_t srl, callback_t fn);

    void update(Context *ct) override;

private:
    void add(const Handler &hdl);

    util::BinaryStream stream;
    std::queue<Handler> queue;

};


}
