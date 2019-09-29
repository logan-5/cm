#ifndef CM_VEC_HPP
#define CM_VEC_HPP

#include <cm/vec_base.hpp>

namespace cm {

namespace detail {
#define CM_VEC_ACCESSOR(NAME, IDX)                              \
    constexpr Rep& NAME() noexcept {                            \
        return static_cast<VecBase*>(this)->storage[IDX];       \
    }                                                           \
    constexpr const Rep& NAME() const noexcept {                \
        return static_cast<const VecBase*>(this)->storage[IDX]; \
    }
template <typename Rep, typename VecBase>
struct vec_with_access_1D : VecBase {
    using VecBase::VecBase;
    CM_VEC_ACCESSOR(x, 0)
    CM_VEC_ACCESSOR(r, 0)
};
template <typename Rep, typename VecBase>
struct vec_with_access_2D : vec_with_access_1D<Rep, VecBase> {
    using vec_with_access_1D<Rep, VecBase>::vec_with_access_1D;
    CM_VEC_ACCESSOR(y, 1)
    CM_VEC_ACCESSOR(g, 1)
};
template <typename Rep, typename VecBase>
struct vec_with_access_3D : vec_with_access_2D<Rep, VecBase> {
    using vec_with_access_2D<Rep, VecBase>::vec_with_access_2D;
    CM_VEC_ACCESSOR(z, 2)
    CM_VEC_ACCESSOR(b, 2)
};
template <typename Rep, typename VecBase>
struct vec_with_access_4D : vec_with_access_3D<Rep, VecBase> {
    using vec_with_access_3D<Rep, VecBase>::vec_with_access_3D;
    CM_VEC_ACCESSOR(w, 3)
    CM_VEC_ACCESSOR(a, 3)
};
#undef CM_VEC_ACCESSOR
}  // namespace detail

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
struct vec2_ : detail::vec_with_access_2D<Rep, vec_base<Rep, 2>> {
   protected:
    using base = detail::vec_with_access_2D<Rep, vec_base<Rep, 2>>;

   public:
    using base::base;

   protected:
    using base::storage;
};
using vec2 = vec2_<f32>;
using ivec2 = vec2_<i32>;

template <typename Rep>
struct vec3_ : detail::vec_with_access_3D<Rep, vec_base<Rep, 3>> {
   protected:
    using base = detail::vec_with_access_3D<Rep, vec_base<Rep, 3>>;

   public:
    using base::base;

   protected:
    using base::storage;
};
using vec3 = vec3_<f32>;
using ivec3 = vec3_<i32>;

template <typename Rep>
struct vec4_ : detail::vec_with_access_4D<Rep, vec_base<Rep, 4>> {
   protected:
    using base = detail::vec_with_access_4D<Rep, vec_base<Rep, 4>>;

   public:
    using base::base;

   protected:
    using base::storage;
};
using vec4 = vec4_<f32>;
using ivec4 = vec4_<i32>;
}  // namespace cm

#endif
