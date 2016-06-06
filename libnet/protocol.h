#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libprot/message.h"

namespace net {


enum class op_t {
    neighbors,
    join
};


class Request : public prot::Message {
public:
    Request();
    Request(const op_t &op);
    virtual ~Request();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    op_t type;
    std::string rstr;

};


class Response : public prot::Message {
public:
    Response();
    virtual ~Response();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    op_t type;
    std::string params;

};


}
