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

    virtual ~Channel() {}

    /**
     * Eof has not been reached and channel is writable
     */
    virtual bool open() const = 0;

    /**
     * Able to read some input
     */
    virtual bool ready() const = 0;
    virtual std::streamsize read(base_t *buf, std::size_t count) = 0;
    virtual std::streamsize write(const base_t *buf, std::size_t count) = 0;
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
