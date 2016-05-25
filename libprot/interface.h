#pragma once

#include "protocol.h"

namespace prot {


class Interface {
public:
    using channel_t = util::Channel;

    Interface(const Protocol &p, std::shared_ptr<channel_t> c);
    ~Interface();

    void update(Context *ct);

private:
    std::vector<std::shared_ptr<channel_t>> channels;
    std::unique_ptr<Protocol> pr;

};


}
