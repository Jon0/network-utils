#pragma once

#include <string>
#include <vector>

namespace util {


template<typename Seq>
Seq take(const Seq &str, size_t count) {
    if (str.size() < count) {
        return str;
    }
    else {
        return Seq(str.begin(), str.begin() + count);
    }
}


template<typename Seq>
Seq drop(const Seq &str, size_t count) {
    if (str.size() < count) {
        return Seq();
    }
    else {
        return Seq(str.begin() + count, str.end());
    }
}


template<typename Seq>
std::pair<Seq, Seq> breakseq(const Seq &str, const Seq &delim) {
    for (auto i = str.begin(); i < (str.end() - delim.size()); ++i) {
        bool match = true;
        for (auto d = 0; d < delim.size(); ++d) {
            if (delim.at(d) != i[d]) {
                match = false;
            }
        }
        if (match) {
            return std::pair<Seq, Seq>(Seq(str.begin(), i), Seq(i, str.end()));
        }
    }
    return std::pair<Seq, Seq>(str, Seq());
}


template<template<typename, typename> typename List, typename Seq, typename Alloc = std::allocator<Seq>>
List<Seq, Alloc> split(const Seq &str, const Seq &delim) {
    List<Seq, Alloc> result;
    Seq remaining = str;
    while (!remaining.empty()) {
        auto p = breakseq(remaining, delim);
        result.insert(result.end(), p.first);
        remaining = drop(p.second, delim.size());
    }
    return result;
}


template<template<typename, typename> typename List, typename T, typename Alloc = std::allocator<T>>
List<T, Alloc> intersperse(const T &elem, List<T, Alloc> list) {
    List<T, Alloc> result;
    for (auto i = list.begin(); i < list.end() - 1; ++i) {
        result.insert(result.end(), *i);
        result.insert(result.end(), elem);
    }
    if (!list.empty()) {
        result.insert(result.end(), list.back());
    }
    return result;
}


template<template<typename, typename> typename List, typename T, typename Alloc = std::allocator<T>>
T concat(List<T, Alloc> list) {
    T result;
    for (auto &e: list) {
        result += e;
    }
    return result;
}


}
