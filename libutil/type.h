#pragma once

#include <functional>

namespace util {


template<typename... T>
class Any {

};


template<typename T>
class Maybe {
public:
    using any_t = Any<void, T>;
    using justfn_t = std::function<bool(const T &)>;

    bool just(const justfn_t &fn) const {
        return false;
    }

private:
    any_t state;

};


template<typename X, typename Y>
class Either {
    using any_t = Any<X, Y>;
    using leftfn_t = std::function<bool(const X &)>;
    using rightfn_t = std::function<bool(const Y &)>;

    bool left(const leftfn_t &fn) const {
        false;
    }

    bool right(const rightfn_t &fn) const {
        false;
    }

private:
    any_t state;

};


}
