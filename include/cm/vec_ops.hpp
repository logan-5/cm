#ifndef CM_VEC_OPS_HPP
#define CM_VEC_OPS_HPP

#include <cm/vec_base.hpp>

#include <cmath>

namespace cm {
// operators
template <typename Rep0, typename Rep1, usize Size>
constexpr std::enable_if_t<detail::equality_comparable_v<Rep0, Rep1>, bool>
operator==(const vec_base<Rep0, Size>& a, const vec_base<Rep1, Size>& b) {
    return cm::equal<Size>(a.storage.data(), b.storage.data());
}

namespace detail {
template <typename Op, typename Rep, usize Size>
constexpr vec_base<Rep, Size>& componentwise_op(
      Op op,
      vec_base<Rep, Size>& lhs,
      const vec_base<Rep, Size>& rhs) {
    for (usize i = 0; i < Size; ++i) {
        op(lhs.storage[i], rhs.storage[i]);
    }
    return lhs;
}
}  // namespace detail

template <typename Rep, usize Size>
constexpr vec_base<Rep, Size>& operator+=(vec_base<Rep, Size>& lhs,
                                          const vec_base<Rep, Size>& rhs) {
    return detail::componentwise_op(
          [](auto& l, const auto& r) { return l += r; }, lhs, rhs);
}
template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> operator+(vec_base<Rep, Size> lhs,
                                        const vec_base<Rep, Size>& rhs) {
    lhs += rhs;
    return lhs;
}

template <typename Rep, usize Size>
constexpr vec_base<Rep, Size>& operator-=(vec_base<Rep, Size>& lhs,
                                          const vec_base<Rep, Size>& rhs) {
    return detail::componentwise_op(
          [](auto& l, const auto& r) { return l -= r; }, lhs, rhs);
}
template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> operator-(vec_base<Rep, Size> lhs,
                                        const vec_base<Rep, Size>& rhs) {
    lhs -= rhs;
    return lhs;
}

template <typename Rep, usize Size>
constexpr vec_base<Rep, Size>& operator*=(vec_base<Rep, Size>& lhs,
                                          const vec_base<Rep, Size>& rhs) {
    return detail::componentwise_op(
          [](auto& l, const auto& r) { return l *= r; }, lhs, rhs);
}
template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> operator*(vec_base<Rep, Size> lhs,
                                        const vec_base<Rep, Size>& rhs) {
    lhs *= rhs;
    return lhs;
}

template <typename Rep, usize Size>
constexpr vec_base<Rep, Size>& operator/=(vec_base<Rep, Size>& lhs,
                                          const vec_base<Rep, Size>& rhs) {
    return detail::componentwise_op(
          [](auto& l, const auto& r) { return l /= r; }, lhs, rhs);
}
template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> operator/(vec_base<Rep, Size> lhs,
                                        const vec_base<Rep, Size>& rhs) {
    lhs /= rhs;
    return lhs;
}

namespace detail {
template <typename Op, typename Rep, usize Size>
constexpr vec_base<Rep, Size>& scalar_op(vec_base<Rep, Size>& lhs, Op op) {
    for (usize i = 0; i < Size; ++i) {
        op(lhs.storage[i]);
    }
    return lhs;
}
}  // namespace detail

template <typename Rep, usize Size>
constexpr vec_base<Rep, Size>& operator*=(vec_base<Rep, Size>& lhs, Rep rhs) {
    return detail::scalar_op(lhs, [&](Rep& l) { l *= rhs; });
}
template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> operator*(vec_base<Rep, Size> lhs, Rep rhs) {
    lhs *= rhs;
    return lhs;
}
template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> operator-(vec_base<Rep, Size> lhs) {
    lhs *= Rep(-1);
    return lhs;
}

template <typename Rep, usize Size>
constexpr vec_base<Rep, Size>& operator/=(vec_base<Rep, Size>& lhs, Rep rhs) {
    return detail::scalar_op(lhs, [&](Rep& l) { l /= rhs; });
}
template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> operator/(vec_base<Rep, Size> lhs, Rep rhs) {
    lhs /= rhs;
    return lhs;
}

// functions

template <typename Rep, usize Size>
constexpr Rep dot(const vec_base<Rep, Size>& lhs,
                  const vec_base<Rep, Size>& rhs) {
    auto sum = Rep(0);
    for (usize i = 0; i < Size; ++i) {
        sum += lhs.storage[i] * rhs.storage[i];
    }
    return sum;
}

template <typename Rep, usize Size>
constexpr Rep magnitude_squared(const vec_base<Rep, Size>& v) {
    return dot(v, v);
}

// TODO constexpr sqrt
template <typename Rep, usize Size>
constexpr Rep magnitude(const vec_base<Rep, Size>& v) {
    return std::sqrt(magnitude_squared(v));
}

template <typename Rep, usize Size>
constexpr vec_base<Rep, Size> normalized(const vec_base<Rep, Size>& v) {
    return v / magnitude(v);
}

}  // namespace cm
#endif