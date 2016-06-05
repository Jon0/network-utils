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


class Request : public prot::Message {
public:
    Request();
    virtual ~Request();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    std::string rstr;

};


class Response : public prot::Message {
public:
    Response();
    virtual ~Response();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    operation_t instruction;
    std::string params;

};


}
