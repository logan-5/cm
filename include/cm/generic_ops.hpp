#ifndef CM_GENERIC_OPS
#define CM_GENERIC_OPS

#include "fwd.hpp"

namespace cm {

template <typename T, typename Alpha>
constexpr T lerp(const T& a, const T& b, const Alpha f) {
    return (b - a) * f + a;
}

}  // namespace cm

#endif