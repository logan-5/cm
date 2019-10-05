#ifndef CM_GENERIC_OPS
#define CM_GENERIC_OPS

#include "constants.hpp"
#include "fwd.hpp"

#include <algorithm>

namespace cm {

template <typename T>
constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> abs(T val) {
    return val < T(0) ? -val : val;
}

namespace detail {
template <typename T>
struct is_error_margin : std::false_type {};
template <typename Rep, typename Ratio>
struct is_error_margin<cm::error_margin<Rep, Ratio>> : std::true_type {};
}  // namespace detail

template <typename T, typename ErrorMargin = default_error_margin>
constexpr std::enable_if_t<std::is_arithmetic_v<T> &&
                                 detail::is_error_margin<ErrorMargin>::value,
                           bool>
fuzzy_equals(const T& a, const T& b) {
    return abs(a - b) < ErrorMargin::value;
}

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
constexpr U linearstep(const T& edge0, const T& edge1, const U& x) {
    return clamp((x - U(edge0)) / U(edge1 - edge0), U(0.0), U(1.0));
}

template <typename T, typename U>
constexpr U smoothstep(const T& edge0, const T& edge1, const U& x_) {
    const U x = linearstep(edge0, edge1, x_);
    return x * x * (U(3) - U(2) * x);
}

}  // namespace cm

#endif