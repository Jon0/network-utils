#pragma once

#include <unordered_map>
#include <vector>

namespace util {


template<typename T>
class ClassId {
public:
    ClassId(const T &c, const size_t &i)
        :
        class_id(c),
        instance_id(i) {}

    const T class_id;
    const size_t instance_id;
};


template<typename T>
class ClassBlock {
public:
    ~ClassBlock() {}

    size_t object_size;

private:
    std::vector<char> buffer;

};


template<typename T>
class ClassRef {
public:
    ~ClassRef() {}

    size_t object_size;
    size_t object_state;

};


template<typename T>
class ClassSeq {
public:
    ~ClassSeq() {}

    size_t object_size;

private:
    std::vector<const T> states;

};


template<typename T>
class Pool {
public:

private:
    std::unordered_map<T, int> maps;
};


}
