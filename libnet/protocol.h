#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libprot/message.h"

#include "host.h"

namespace net {


enum class op_t {
    neighbors,
    join
};


class Message : public util::Stringable {
public:
    using element_t = util::Stringable *;
    using elements_t = std::vector<element_t>;

    Message();
    virtual ~Message();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

    virtual void get(elements_t *e) = 0;
    virtual void set(elements_t *e) = 0;

private:
    Host h;
    int64_t id;
    elements_t elems;

};


class Request : public util::Stringable {
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


class Response : public util::Stringable {
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
