#pragma once

#include "stream.h"

namespace util {


class Serialisable {
public:
    virtual ~Serialisable() {}
    virtual bool valid() const = 0;
    virtual bool read(BinaryStream &s) = 0;
    virtual bool write(BinaryStream &s) = 0;
};


class Stringable : public Serialisable {
public:
    using length_t = int32_t;

    Stringable();
    Stringable(const Stringable &msg) = delete;
    virtual ~Stringable() = default;

    void init();
    void init(const Stringable &msg);
    void init(const std::string &msg);

    bool valid() const override;
    bool read(util::BinaryStream &s) override;
    bool write(util::BinaryStream &s) override;

    virtual std::string to_string() const = 0;
    virtual void from_string(const std::string &s) = 0;

private:
    bool initialised;

};


}
