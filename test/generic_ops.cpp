#include <cm/generic_ops.hpp>

#include <cm/vec.hpp>

#include <catch.hpp>

TEST_CASE("lerp", "[generic ops]") {
    using cm::lerp;
    static_assert(lerp(0.f, 1.f, 0.5f) == 0.5f);
    static_assert(lerp(17.f, 23.f, 0.5f) == 20.f);
    static_assert(lerp(0, 10, 0.667) == 6);
    static_assert(lerp(10, -10, 0.8) == -6);
    static_assert(lerp(0.f, 2.f, 2.f) == 4.f);

    REQUIRE(lerp(0.f, 1.f, 0.5f) == 0.5f);
    REQUIRE(lerp(17.f, 23.f, 0.5f) == 20.f);
    REQUIRE(lerp(0, 10, 0.667) == 6);
    REQUIRE(lerp(10, -10, 0.8) == -6);
    REQUIRE(lerp(0.f, 2.f, 2.f) == 4.f);

    using cm::scalar;
    using cm::vec2;
    using cm::vec3;
    REQUIRE(lerp(vec2{0.f, 1.f}, vec2{1.f, 0.f}, 0.5f) == vec2{0.5f});
    REQUIRE(lerp(vec3{0.f, 1.f, 0.f}, vec3{1.f, 0.f, 0.f}, 0.5f) ==
            vec3{vec2{0.5f}, scalar{0.f}});
}
