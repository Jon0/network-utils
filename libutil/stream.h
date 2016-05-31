#pragma once

#include <cstring>

#include "channel.h"

namespace util {


template<typename T>
T strcast(const std::string &str) {
    T result;
    std::memcpy(&result, str.c_str(), sizeof(T));
    return result;
}


class BinaryStream {
public:
    static constexpr size_t buffersize = 1024;

    BinaryStream(Channel *c);
    virtual ~BinaryStream();

    bool good() const;

    /**
     * Buffered bytes available to read
     */
    size_t available();

    std::string peek_some(size_t len);
    std::string read_some(size_t len);

    void read_all(std::string &buf);
    void write_all(const std::string &buf);

    bool matchstr(const std::string &str);

    template<typename T>
    T peek_type() {
        return strcast<T>(peek_some(sizeof(T)));
    }

    template<typename T>
    T read_type() {
        return strcast<T>(read_some(sizeof(T)));
    }

private:
    void ensure_available(size_t len) const;
    void sync_input();

    Channel *c;
	char in_buffer[buffersize];
	char out_buffer[buffersize];
    std::string strbuffer;
};


}
