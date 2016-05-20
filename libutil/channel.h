#pragma once

#include <string>

namespace util {


struct Binary {
    using data_t = char;
};


template<typename Encoding>
class Channel {
public:
    using encoding_t = typename Encoding::data_t;
    virtual ~Channel() {}
    virtual std::streamsize read(encoding_t *buf, std::size_t count) = 0;
    virtual std::streamsize write(const encoding_t *buf, std::size_t count) = 0;

};


template<typename Encoding>
class Buffer {
public:

private:
    Channel<Encoding> first, second;

};


}
