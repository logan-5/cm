#ifndef CM_VEC_HPP
#define CM_VEC_HPP

#include <cm/vec_base.hpp>

namespace cm {
template <typename Rep>
struct scalar_ : vec_base<Rep, 1> {
   protected:
    using base = vec_base<Rep, 1>;

   public:
    using base::base;

    constexpr operator Rep&() noexcept { return storage[0]; }
    constexpr operator const Rep&() const noexcept { return storage[0]; }

   protected:
    using base::storage;
};
using scalar = scalar_<f32>;
using iscalar = scalar_<i32>;

template <typename Rep>
struct vec2_ : vec_base<Rep, 2> {
   protected:
    using base = vec_base<Rep, 2>;

   public:
    using base::base;

   protected:
    using base::storage;
};
using vec2 = vec2_<f32>;
using ivec2 = vec2_<i32>;

template <typename Rep>
struct vec3_ : vec_base<Rep, 3> {
   protected:
    using base = vec_base<Rep, 3>;

   public:
    using base::base;

   protected:
    using base::storage;
};
using vec3 = vec3_<f32>;
using ivec3 = vec3_<i32>;
}  // namespace cm

#endif
