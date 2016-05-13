#pragma once

#include <array>
#include <functional>

namespace std {

template<typename T, size_t N>
struct hash<array<T, N>> {
    using array_t = array<T, N>;

    size_t operator()(const array_t &arr) const {
        hash<T> hash;
        size_t result = 1;
        for (size_t i = 0; i < N; ++i) {
            result = result * hash(arr[i]) - 1;
        }
        return result;
    }
};

}
