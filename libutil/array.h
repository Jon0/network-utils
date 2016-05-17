#pragma once

#include <array>
#include <cstring>

namespace util {


template<typename T, size_t count>
std::array<T, count> to_array(const T arr[count]) {
    std::array<T, count> result;
    std::memcpy(&result.at(0), arr, count * sizeof(T));
    return result;
}


}
