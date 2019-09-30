#ifndef CM_GENERIC_OPS
#define CM_GENERIC_OPS

#include "fwd.hpp"

#include <algorithm>

namespace cm {

template <typename T, typename Alpha>
constexpr T lerp(const T& a, const T& b, const Alpha f) {
    return (b - a) * f + a;
}

template <typename T>
constexpr std::enable_if_t<std::is_arithmetic_v<T>, const T&>
clamp(const T& t, const T& lo, const T& hi) {
    return std::clamp(t, lo, hi);
}

template <typename T, typename U>
constexpr T linearstep(const T& edge0, const T& edge1, const U& x) {
    return clamp((T(x) - edge0) / (edge1 - edge0), T(0.0), T(1.0));
}

template <typename T, typename U>
constexpr float smoothstep(const T& edge0, const T& edge1, const U& x) {
    const T t = linearstep(edge0, edge1, x);
    return t * t * (T(3) - T(2) * t);
}

}  // namespace cm

#endif