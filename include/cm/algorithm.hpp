#ifndef CM_ALGORITHM_HPP
#define CM_ALGORITHM_HPP

#include <cm/fwd.hpp>

namespace cm {
template <usize Count, typename T, typename U>
constexpr std::enable_if_t<std::is_assignable_v<T&, const U>> copy(
      T* dest,
      const U* source) {
    for (usize i = 0; i < Count; ++i) {
        dest[i] = source[i];
    }
}

namespace detail {
template <typename T, typename U>
using equality_t = decltype(std::declval<T>() == std::declval<U>());
template <typename T, typename U, typename = void>
struct equality_comparable : std::false_type {};
template <typename T, typename U>
struct equality_comparable<T, U, std::void_t<equality_t<T, U>>>
    : std::bool_constant<std::is_same_v<equality_t<T, U>, bool>> {};
template <typename T, typename U>
constexpr inline bool equality_comparable_v = equality_comparable<T, U>::value;
}  // namespace detail

template <usize Count, typename T, typename U>
constexpr std::enable_if_t<detail::equality_comparable_v<T, U>, bool> equal(
      const T* a,
      const U* b) {
    for (usize i = 0; i < Count; ++i) {
        if (!(a[i] == b[i])) {
            return false;
        }
    }
    return true;
}

namespace detail {
template <typename T, typename U>
using less_than_t = decltype(std::declval<T>() < std::declval<U>());
template <typename T, typename U, typename = void>
struct less_than_comparable : std::false_type {};
template <typename T, typename U>
struct less_than_comparable<T, U, std::void_t<less_than_t<T, U>>>
    : std::bool_constant<std::is_same_v<less_than_t<T, U>, bool>> {};
template <typename T, typename U>
constexpr inline bool less_than_comparable_v =
      less_than_comparable<T, U>::value;
}  // namespace detail
template <usize Count, typename T, typename U>
constexpr std::enable_if_t<detail::less_than_comparable_v<T, U>, bool>
lexicographical_compare(const T* a, const U* b) {
    for (usize i = 0; i < Count; ++i) {
        if (a[i] < b[i]) {
            return true;
        }
        if (b[i] < a[i]) {
            return false;
        }
    }
    return false;
}
}  // namespace cm

#endif
