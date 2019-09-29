#ifndef CM_VEC_BASE_HPP
#define CM_VEC_BASE_HPP

#include <array>
#include <type_traits>

#include <cm/fwd.hpp>

namespace cm {

template <typename Rep, usize Dim>
struct vec_base;

namespace detail {

template <usize... Is>
struct sum : std::integral_constant<usize, (Is + ... + 0)> {};
template <usize... Is>
constexpr inline auto sum_v = sum<Is...>::value;

template <typename T, usize ASize, usize BSize>
constexpr std::array<T, ASize + BSize> array_cat_impl(
      const std::array<T, ASize>& a,
      const std::array<T, BSize>& b) {
    std::array<T, ASize + BSize> result = {};
    cm::copy<ASize>(result.data(), a.data());
    cm::copy<BSize>(result.data() + ASize, b.data());
    return result;
}

template <typename T, usize Size>
constexpr std::array<T, Size> array_cat(std::array<T, Size> a) {
    return a;
}

template <typename T, usize FirstSize, usize SecondSize, usize... Sizes>
constexpr std::array<T, FirstSize + SecondSize + sum_v<Sizes...>> array_cat(
      const std::array<T, FirstSize>& first,
      const std::array<T, SecondSize>& second,
      const std::array<T, Sizes>&... args) {
    return array_cat(array_cat_impl(first, second), args...);
}

template <typename T, typename Rep>
struct valid_vec_base_scalar_arg
    : std::bool_constant<std::is_convertible_v<T, Rep>> {};
template <typename T, typename Rep>
constexpr inline bool valid_vec_base_scalar_arg_v =
      valid_vec_base_scalar_arg<T, Rep>::value;

template <typename T, typename U, usize Size>
constexpr std::array<T, Size> converted(const std::array<U, Size>& other) {
    std::array<T, Size> result = {};
    cm::copy<Size>(result.data(), other.data());
    return result;
}

template <usize Size, typename T>
constexpr std::array<T, Size> filled(const T& val) {
    std::array<T, Size> result = {};
    for (usize i = 0; i < Size; ++i) {
        result[i] = val;
    }
    return result;
}

}  // namespace detail

template <typename Rep, usize Dim>
struct vec_base {
    constexpr vec_base() = default;
    constexpr vec_base(const vec_base&) = default;
    vec_base& operator=(const vec_base&) = default;

    template <typename... Args,
              typename = std::enable_if_t<
                    (sizeof...(Args) == Dim) &&
                    std::conjunction_v<
                          typename detail::valid_vec_base_scalar_arg<Args,
                                                                     Rep>...>>>
    constexpr vec_base(Args... vals) : storage{{static_cast<Rep>(vals)...}} {}

    template <usize D = Dim, typename = std::enable_if_t<(D > 1)>>
    constexpr vec_base(Rep arg) : storage{detail::filled<Dim>(arg)} {}

    template <usize... Dims,
              typename = std::enable_if_t<(sizeof...(Dims) > 1) &&
                                          detail::sum_v<Dims...> == Dim>>
    constexpr vec_base(const vec_base<Rep, Dims>&... args)
        : storage{detail::array_cat(args.storage...)} {}

    template <typename OtherRep,
              typename = std::enable_if_t<std::is_convertible_v<OtherRep, Rep>>>
    constexpr vec_base(const vec_base<OtherRep, Dim>& other)
        : storage{detail::converted<Rep>(other.storage)} {}

    static constexpr auto length() noexcept { return Dim; }
    static constexpr auto size() noexcept { return Dim; }

    std::array<Rep, Dim> storage;
};

template <typename Rep>
struct vec_base<Rep, 0> {
    static constexpr auto length() noexcept { return 0; }
    static constexpr auto size() noexcept { return 0; }
};

}  // namespace cm

#endif
