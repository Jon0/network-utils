#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libprot/message.h"

namespace net {


enum class operation_t {
    neighbors,
    join
};

class Protocol : public prot::Message {
public:
    Protocol();
    virtual ~Protocol();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    operation_t instruction;
    std::string params;

};


}
