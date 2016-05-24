#include "interface.h"

namespace prot {


Interface::Interface(const Protocol &p, std::shared_ptr<channel_t> c)
    :
    pr(p.copy()) {
    channels.emplace_back(c);
}


Interface::~Interface() {}


void Interface::update() {
    for (auto &c : channels) {
        if (c->ready()) {
            pr->event(c.get());
        }
    }
}

}
