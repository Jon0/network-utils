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


template<typename T>
std::string struncast(const T &t) {
    char result [sizeof(T)];
    std::memcpy(result, &t, sizeof(T));
    return std::string(result, sizeof(T));
}


class BinaryStream {
public:
    static constexpr size_t buffersize = 1024;

    BinaryStream(Channel *c);
    virtual ~BinaryStream();

    std::string name() const;
    bool good() const;

    /**
     * Buffered bytes available to read
     */
    size_t available();

    std::string peek_some(size_t len, size_t offset = 0);
    std::string read_some(size_t len);

    void read_all(std::string &buf);
    void write_all(const std::string &buf);

    bool matchstr(const std::string &str);

    template<typename T>
    T peek_type(size_t offset = 0) {
        return strcast<T>(peek_some(sizeof(T), offset));
    }

    template<typename T>
    T read_type() {
        return strcast<T>(read_some(sizeof(T)));
    }

    template<typename T>
    void write_type(const T &t) {
        return write_all(struncast<T>(t));
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
