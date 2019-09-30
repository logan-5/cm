#ifndef CM_RANDOM_HPP
#define CM_RANDOM_HPP

#include <cm/constants.hpp>
#include <cm/vec.hpp>

#include <random>

#ifndef CM_RANDOM_ENGINE
#define CM_RANDOM_ENGINE std::mt19937
#endif

namespace cm {

inline CM_RANDOM_ENGINE& random_engine() {
    static CM_RANDOM_ENGINE e{std::random_device{}()};
    return e;
}

template <typename Int>
std::enable_if_t<std::is_integral_v<Int>, Int> random_integral(
      Int minInclusive,
      Int maxInclusive) {
    return std::uniform_int_distribution<Int>{minInclusive,
                                              maxInclusive}(random_engine());
}

template <typename Float>
std::enable_if_t<std::is_floating_point_v<Float>, Float> random_real(
      Float minInclusive,
      Float maxExclusive) {
    return std::uniform_real_distribution<Float>{minInclusive,
                                                 maxExclusive}(random_engine());
}

template <typename V2 = vec2>
V2 random_on_unit_circle() {
    const float ang =
          TAU<typename V2::rep> * random_real<typename V2::rep>(0, 1);
    return V2{std::cos(ang), std::sin(ang)};
}
template <typename V2 = vec2>
V2 random_in_unit_circle() {
    return random_on_unit_circle<V2>() *
           std::sqrt(random_real<typename V2::rep>(0, 1));
}

template <typename V3 = vec3>
V3 random_on_unit_sphere() {
    using F = typename V3::rep;
    // http://mathworld.wolfram.com/SpherePointPicking.html
    const F u = random_real<F>(0, 1);
    const F v = random_real<F>(0, 1);
    const F theta = TAU<F> * u;
    const F phi = std::acos(F(2) * v - F(1));

    using std::cos;
    using std::sin;
    return V3{cos(theta) * sin(phi), sin(theta) * sin(phi), cos(phi)};
}
template <typename V3 = vec3>
V3 random_in_unit_sphere() {
    return random_on_unit_sphere<V3>() *
           std::sqrt(random_real<typename V3::rep>(0, 1));
}

}  // namespace cm

#endif
