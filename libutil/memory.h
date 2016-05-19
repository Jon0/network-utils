#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

namespace util {


template<typename T>
class ClassRef {
public:
    ~ClassRef() {}

    size_t ref_count;
    size_t object_size;
    size_t object_state;

private:
    const T state;

};


template<typename T>
class ClassSeq {
public:
    ~ClassSeq() {}

    const size_t object_size;
    const size_t instance_id;

private:
    std::vector<std::weak_ptr<const T>> states;

};


template<typename T>
class ClassList {
public:
    ~ClassList() {}

    const size_t class_id;

private:
    std::vector<ClassSeq<T>> buffer;

};


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
class MemoryMap {
public:

private:
    std::unordered_map<T, int> maps;
};


}
