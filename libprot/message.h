#pragma once

#include <libutil/serial.h>

namespace prot {


struct message_t {
    size_t id, size;
};


class Message : public util::Serialisable {
public:
    Message();
    Message(const std::string &init);
    virtual ~Message();

    std::string str() const;

    bool valid() const override;
    bool read(util::BinaryStream &s) override;
    bool write(util::BinaryStream &s) override;

private:
    std::string msg;

};


}
