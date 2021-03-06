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

    virtual std::string name() const = 0;

    /**
     * Eof has not been reached
     */
    virtual bool open() const = 0;

    /**
     * Able to read some input
     */
    virtual bool readable() const = 0;
    virtual bool writable() const = 0;
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
