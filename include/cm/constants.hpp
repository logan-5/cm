#ifndef CM_CONSTANTS_HPP
#define CM_CONSTANTS_HPP

#include <cm/fwd.hpp>

#include <cmath>
#include <ratio>

namespace cm {

namespace detail {
template <typename T>
struct is_ratio : std::false_type {};
template <std::intmax_t N, std::intmax_t D>
struct is_ratio<std::ratio<N, D>> : std::true_type {};
}  // namespace detail

template <typename Rep, typename Ratio, typename = void>
struct error_margin;
template <typename Rep, typename Ratio>
struct error_margin<Rep,
                    Ratio,
                    std::void_t<decltype(detail::is_ratio<Ratio>::value)>> {
    static constexpr Rep value = Rep(Ratio::num) / Rep(Ratio::den);
};

using default_error_margin = error_margin<float, std::ratio<1, 1000>>;

template <typename Float = f32>
inline constexpr Float PI = Float(M_PI);

template <typename Float = f32>
inline constexpr Float TAU = Float(6.28318530717958647692528676655900577);

}  // namespace cm

#endif