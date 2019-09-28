#ifndef CM_FWD_HPP
#define CM_FWD_HPP

#include <cstddef>
#include <cstdint>

namespace cm {
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using usize = std::size_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using f32 = float;
static_assert(sizeof(float) == 4);
using f64 = double;
static_assert(sizeof(double) == 8);

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

}  // namespace cm

#endif
