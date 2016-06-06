#pragma once

#include <libutil/serial.h>

namespace prot {


class Message : public util::Serialisable {
public:
    using id_t = int32_t;
    using length_t = int32_t;

    Message();
    Message(const Message &msg) = delete;
    virtual ~Message() = default;

    id_t id() const;
    void init();
    void init(const Message &msg);
    void init(int32_t newid, const std::string &msg);

    bool valid() const override;
    bool read(util::BinaryStream &s) override;
    bool write(util::BinaryStream &s) override;

    virtual std::string to_string() const = 0;
    virtual void from_string(const std::string &s) = 0;

private:
    id_t id_value;
    bool initialised;

};


}
