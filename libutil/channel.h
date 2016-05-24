#pragma once

#include <string>
#include <vector>

namespace util {


struct Binary {
    using data_t = char;
};


class Channel {
public:
    using base_t = char;
    using addr_t = int;

    virtual ~Channel() {}
    virtual addr_t type() const = 0;
    virtual bool ready() const = 0;
    virtual std::streamsize read(base_t *buf, std::size_t count) = 0;
    virtual std::streamsize write(const base_t *buf, std::size_t count) = 0;

    template<typename T>
    T *cast() {
        return dynamic_cast<T *>(this);
    }
};


class ChannelAttr {
    virtual const char *name() const = 0;
};


class ChannelFmt {
public:

    template<typename E>
    std::streamsize readt(typename E::data_t *buf, std::size_t count) {
        // TODO
    }

    template<typename E>
    std::streamsize writet(typename E::data_t *buf, std::size_t count) {
        // TODO
    }
};


template<typename Encoding>
class Buffer {
public:

private:
    Channel first, second;

};


}
