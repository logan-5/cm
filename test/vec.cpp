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

// access
static_assert(vec2{1.f, 2.f}.x() == 1.f);
static_assert(vec2{1.f, 2.f}.y() == 2.f);
static_assert(vec3{1.f, 2.f, 3.f}.z() == vec3{1.f, 2.f, 3.f}.b());

TEST_CASE("accessors", "[accessors]") {
    constexpr vec4 v{1.f, 2.f, 3.f, 4.f};
    static_assert(v.x() == 1.f);
    static_assert(v.x() == v.r());
    static_assert(v.y() == 2.f);
    static_assert(v.y() == v.g());
    static_assert(v.z() == 3.f);
    static_assert(v.z() == v.b());
    static_assert(v.w() == 4.f);
    static_assert(v.w() == v.a());

    SECTION("writing through one accessor is readable through others") {
        vec4 vCopy{v};
        vCopy.x() = 10.f;
        REQUIRE(vCopy.r() == 10.f);
        vCopy.y() = 20.f;
        REQUIRE(vCopy.g() == 20.f);
        vCopy.z() = 30.f;
        REQUIRE(vCopy.b() == 30.f);
        vCopy.w() = 40.f;
        REQUIRE(vCopy.a() == 40.f);
    }
}
