#include <iostream>

#include "queue.h"

namespace prot {


Handler::Handler(serial_mode_t mode, serial_t srl)
    :
    mode(mode),
    object(srl) {}


Handler::Handler(serial_mode_t mode, serial_t srl, callback_t fn)
    :
    mode(mode),
    object(srl),
    callback(fn) {}


Handler::~Handler() {}


bool Handler::do_callback() const {
    if (callback) {
        return callback();
    }
    else {
        return true;
    }
}


bool Handler::apply(util::BinaryStream &stream) {
    if (mode == serial_mode_t::read && object->read(stream)) {
        return do_callback();
    }
    else if (mode == serial_mode_t::write && object->write(stream)) {
        return do_callback();
    }
    return false;
}


Queue::Queue(util::Channel *c)
    :
    stream(c) {
    log("open");
}


Queue::~Queue() {
    log("close");
}


void Queue::log(const std::string &msg) const {
    std::cout << "[" << stream.name() << "] " << msg << "\n";
}


void Queue::clear() {
    queue = std::queue<Handler>();
}

void Queue::pushr(serial_t srl) {
    add(Handler(serial_mode_t::read, srl));
}


void Queue::pushr(serial_t srl, callback_t fn) {
    add(Handler(serial_mode_t::read, srl, fn));
}


void Queue::pushw(serial_t srl) {
    add(Handler(serial_mode_t::write, srl));
}


void Queue::pushw(serial_t srl, callback_t fn) {
    add(Handler(serial_mode_t::write, srl, fn));
}


void Queue::update(Context *ct) {
    bool loop = true;
    while (!queue.empty() && loop) {
        Handler &hdl = queue.front();
        if (hdl.apply(stream)) {
            queue.pop();
        }
        else {
            loop = false;
        }
    }
}


void Queue::add(const Handler &hdl) {
    queue.push(hdl);
}


}
