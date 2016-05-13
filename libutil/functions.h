#pragma once

#include <functional>

namespace util {

template<template<typename> typename List, typename In, typename Out>
List<Out> map(std::function<Out(In)> fn, List<In> list) {
    List<Out> result;
    for (auto &e: list) {
        result.insert(result.end(), fn(e));
    }
    return result;
}

}
