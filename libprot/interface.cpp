#include "interface.h"

namespace prot {


Interface::Interface(const Protocol &p, std::shared_ptr<channel_t> c)
    :
    pr(p.copy()) {
    channels.emplace_back(c);
}


Interface::~Interface() {}


void Interface::update(Context *ct) {
    for (auto &ch : channels) {
        if (ch->readable()) {
            pr->event(ct, ch.get());
        }
    }
}

}
