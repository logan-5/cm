#include <cm/vec.hpp>

#include <catch.hpp>

using namespace cm;

// construction from pieces
static_assert(scalar{0.f} == 0.f);
static_assert(scalar{1.f} == 1.f);
static_assert(vec2{0.f, 1.f} == vec2{scalar{0.f}, scalar{1.f}});
static_assert(vec3{1.f, 2.f, 3.f} ==
              vec3{scalar{1.f}, scalar{2.f}, scalar{3.f}});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{vec2{1.f, 2.f}, scalar{3.f}});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{scalar{1.f}, vec2{2.f, 3.f}});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{1, 2, 3});

// construction from scalars
static_assert(vec2{1.f} == vec2{1.f, 1.f});
static_assert(vec3{5.f} == vec3{5.f, 5.f, 5.f});
static_assert(vec3{scalar{5.f}} == vec3{5.f, 5.f, 5.f});

// conversion
static_assert(vec2{1.f, 2.f} == vec2{ivec2{1, 2}});
static_assert(ivec2{1.f, 2.f} == ivec2{vec2{1, 2}});

TEST_CASE("this is a test test") {
    REQUIRE(0 == 0);
}
