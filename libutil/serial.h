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


class String : public Stringable {
public:
    String();
    String(const std::string &s);
    virtual ~String();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    std::string str;

};


template<typename T>
class Block : public Stringable {
public:
    Block() {}
    Block(const T &s)
        :
        i(s) {
        init();
    }

    virtual ~Block() {}

    T get() const {
        return i;
    }

    std::string to_string() const override {
        char result [sizeof(T)];
        std::memcpy(&result, &i, sizeof(T));
        return std::string(result, sizeof(T));
    }

    void from_string(const std::string &s) override {
        std::memcpy(&i, s.c_str(), sizeof(T));
    }

private:
    T i;

};


class StringList : public Stringable {
public:
    using int_t = int32_t;
    using array_t = std::vector<const Stringable *>;

    StringList();
    virtual ~StringList();

    std::string to_string() const override;
    void from_string(const std::string &s) override;

    virtual array_t to_array() const = 0;
    virtual Stringable *at(size_t e) = 0;

private:
    int_t bstoi(const std::string &s) const;
    std::string itobs(const int_t &i) const;

};


}
