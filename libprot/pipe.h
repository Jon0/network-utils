#pragma once

#include <cstdint>
#include <string>

namespace prot {


class PipeDesc {
public:
    using pd_t = int64_t;

    PipeDesc(const pd_t &p);
    virtual ~PipeDesc();

private:
    const pd_t pd;
    std::string type;

};


}
