#pragma once

#include <libutil/serial.h>

namespace prot {


class Message : public util::Serialisable {
public:
    Message();
    virtual ~Message();

    bool valid() const override;
    bool read(util::BinaryStream &s) override;
    bool write(util::BinaryStream &s) override;

private:
    std::string msg;

};


}
