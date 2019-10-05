#ifndef CM_VEC_OPS_HPP
#define CM_VEC_OPS_HPP

#include <cm/generic_ops.hpp>
#include <cm/vec_base.hpp>

#include <cmath>

namespace cm {
// operators
template <typename Rep0, typename Rep1, usize Size>
constexpr std::enable_if_t<detail::equality_comparable_v<Rep0, Rep1>, bool>
operator==(const vec_base<Rep0, Size>& a, const vec_base<Rep1, Size>& b) {
    return cm::equal<Size>(a.storage.data(), b.storage.data());
}
template <typename Rep0, typename Rep1, usize Size>
constexpr std::enable_if_t<detail::equality_comparable_v<Rep0, Rep1>, bool>
operator!=(const vec_base<Rep0, Size>& a, const vec_base<Rep1, Size>& b) {
    return !(a == b);
}
template <typename Rep0, typename Rep1, usize Size>
constexpr std::enable_if_t<detail::less_than_comparable_v<Rep0, Rep1>, bool>
operator<(const vec_base<Rep0, Size>& a, const vec_base<Rep1, Size>& b) {
    return cm::lexicographical_compare<Size>(a.storage.data(),
                                             b.storage.data());
}
template <typename Rep0, typename Rep1, usize Size>
constexpr std::enable_if_t<detail::less_than_comparable_v<Rep0, Rep1>, bool>
operator>=(const vec_base<Rep0, Size>& a, const vec_base<Rep1, Size>& b) {
    return !(a < b);
}
template <typename Rep0, typename Rep1, usize Size>
constexpr std::enable_if_t<detail::less_than_comparable_v<Rep0, Rep1>, bool>
operator>(const vec_base<Rep0, Size>& a, const vec_base<Rep1, Size>& b) {
    return b < a;
}
template <typename Rep0, typename Rep1, usize Size>
constexpr std::enable_if_t<detail::less_than_comparable_v<Rep0, Rep1>, bool>
operator<=(const vec_base<Rep0, Size>& a, const vec_base<Rep1, Size>& b) {
    return !(a > b);
}

namespace detail {

struct vec_base_type_helper {
    template <typename Rep, usize Size>
    static vec_base<Rep, Size> foo(const vec_base<Rep, Size>&);
    static void foo(...);
};
template <typename T>
inline constexpr bool is_vec_v =
      !std::is_same_v<decltype(vec_base_type_helper::foo(std::declval<T>())),
                      void>;

template <typename Op, typename V, typename... Vs>
constexpr std::enable_if_t<is_vec_v<V>, V&> componentwise_op(Op op,
                                                             V& lhs,
                                                             const Vs&... rhs) {
    using base = decltype(vec_base_type_helper::foo(lhs));
    for (usize i = 0; i < V::dimension(); ++i) {
        op(static_cast<base&>(lhs).storage[i],
           static_cast<const base&>(rhs).storage[i]...);
    }
    return lhs;
}
}  // namespace detail

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V&> operator+=(V& lhs,
                                                               const V& rhs) {
    return detail::componentwise_op(
          [](typename V::rep& l, const typename V::rep& r) { return l += r; },
          lhs, rhs);
}
template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> operator+(V lhs,
                                                             const V& rhs) {
    lhs += rhs;
    return lhs;
}

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V&> operator-=(V& lhs,
                                                               const V& rhs) {
    return detail::componentwise_op(
          [](typename V::rep& l, const typename V::rep& r) { return l -= r; },
          lhs, rhs);
}
template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> operator-(V lhs,
                                                             const V& rhs) {
    lhs -= rhs;
    return lhs;
}

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V&> operator*=(V& lhs,
                                                               const V& rhs) {
    return detail::componentwise_op(
          [](typename V::rep& l, const typename V::rep& r) { return l *= r; },
          lhs, rhs);
}
template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> operator*(V lhs,
                                                             const V& rhs) {
    lhs *= rhs;
    return lhs;
}

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V&> operator/=(V& lhs,
                                                               const V& rhs) {
    return detail::componentwise_op(
          [](typename V::rep& l, const typename V::rep& r) { return l /= r; },
          lhs, rhs);
}
template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> operator/(V lhs,
                                                             const V& rhs) {
    lhs /= rhs;
    return lhs;
}

namespace detail {
template <typename Op, typename V>
constexpr std::enable_if_t<is_vec_v<V>, V&> scalar_op(V& lhs, Op op) {
    using base = decltype(vec_base_type_helper::foo(lhs));
    for (usize i = 0; i < V::dimension(); ++i) {
        op(static_cast<base&>(lhs).storage[i]);
    }
    return lhs;
}
}  // namespace detail

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V&> operator*=(
      V& lhs,
      typename V::rep rhs) {
    return detail::scalar_op(lhs, [&](typename V::rep& l) { l *= rhs; });
}
template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> operator*(
      V lhs,
      typename V::rep rhs) {
    lhs *= rhs;
    return lhs;
}
template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> operator-(V lhs) {
    lhs *= typename V::rep(-1);
    return lhs;
}

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V&> operator/=(
      V& lhs,
      typename V::rep rhs) {
    return detail::scalar_op(lhs, [&](typename V::rep& l) { l /= rhs; });
}
template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> operator/(
      V lhs,
      typename V::rep rhs) {
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

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> normalized(const V& v) {
    using Rep = typename V::rep;
    const Rep scale = Rep(1) / magnitude(v);
    return v * scale;
}

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> clamp(V v,
                                                         typename V::rep lo,
                                                         typename V::rep hi) {
    return detail::scalar_op(
          v, [&](typename V::rep& v) { v = std::clamp(v, lo, hi); });
}

template <typename V>
constexpr std::enable_if_t<detail::is_vec_v<V>, V> clamp(V v,
                                                         const V& lo,
                                                         const V& hi) {
    return detail::componentwise_op(
          [](typename V::rep& v, const typename V::rep& lo,
             const typename V::rep& hi) { v = std::clamp(v, lo, hi); },
          v, lo, hi);
}

namespace detail {
template <typename V>
inline constexpr bool is_vec2or3_v = is_vec_v<V> && ((V::dimension() == 2) ||
                                                     (V::dimension() == 3));
}

template <typename V>
constexpr std::enable_if_t<detail::is_vec2or3_v<V>, V> bounce(
      const V& in_normalized,
      const V& normal) {
    return in_normalized + normal * (cm::dot(in_normalized, normal) * -2.f);
}

template <typename V, typename ErrorMargin = default_error_margin>
static constexpr std::enable_if_t<
      detail::is_vec_v<V> && detail::is_error_margin<ErrorMargin>::value,
      bool>
fuzzy_equals(const V& a, const V& b) {
    using base = decltype(detail::vec_base_type_helper::foo(a));
    for (usize i = 0; i < V::dimension(); ++i) {
        if (!cm::fuzzy_equals<typename V::rep, ErrorMargin>(
                  static_cast<const base&>(a).storage[i],
                  static_cast<const base&>(b).storage[i]))
            return false;
    }
    return true;
}

}  // namespace cm
#endif