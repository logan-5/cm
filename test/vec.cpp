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

TEST_CASE("component-wise operations") {
    constexpr vec4 a{0.f, 0.f, 0.f, 0.f};
    constexpr vec4 b{1.f, 1.f, 1.f, 1.f};
    static_assert(a + b == b);
    static_assert(b + a == b);
    static_assert(b + b == vec4{2.f, 2.f, 2.f, 2.f});
    SECTION("add assignment") {
        vec4 aCopy = a;
        aCopy += a;
        REQUIRE(aCopy == vec4{0.f, 0.f, 0.f, 0.f});
        aCopy += b;
        REQUIRE(aCopy == b);
        aCopy += b;
        REQUIRE(aCopy == (b + b));
    }

    static_assert(a - b == vec4{-1.f, -1.f, -1.f, -1.f});
    static_assert(b - a == b);
    static_assert(b - b == a);
    SECTION("sub assignment") {
        vec4 aCopy = a;
        aCopy -= a;
        REQUIRE(aCopy == vec4{0.f, 0.f, 0.f, 0.f});
        aCopy -= b;
        REQUIRE(aCopy == vec4{-1.f, -1.f, -1.f, -1.f});
        aCopy -= b;
        REQUIRE(aCopy == vec4{-2.f, -2.f, -2.f, -2.f});
    }

    constexpr ivec4 c{5, 5, 5, 5};
    constexpr ivec4 d{2, 2, 3, 6};
    static_assert(a * b == a);
    static_assert(b * a == a);
    static_assert(b * b == b);
    static_assert(b * vec4{2.f, 2.f, 2.f, 2.f} == vec4{2.f, 2.f, 2.f, 2.f});
    static_assert(c * d == ivec4{10, 10, 15, 30});
    SECTION("mul assignment") {
        vec4 aCopy = a;
        aCopy *= a;
        REQUIRE(aCopy == vec4{0.f, 0.f, 0.f, 0.f});
        aCopy *= b;
        REQUIRE(aCopy == vec4{0.f, 0.f, 0.f, 0.f});
        vec4 bCopy = b;
        bCopy *= vec4{2.f, 2.f, 2.f, 2.f};
        REQUIRE(bCopy == vec4{2.f, 2.f, 2.f, 2.f});
    }

    static_assert(a / b == a);
    static_assert(c / d == ivec4{2, 2, 1, 0});
    static_assert(d / d == ivec4{1, 1, 1, 1});
    SECTION("div assignment") {
        ivec4 cCopy = c;
        cCopy /= c;
        REQUIRE(cCopy == ivec4{1, 1, 1, 1});
        cCopy /= d;
        REQUIRE(cCopy == ivec4{0, 0, 0, 0});
    }
}

TEST_CASE("scalar operations") {
    constexpr vec4 a{0.f, 0.f, 0.f, 0.f};
    constexpr vec4 b{1.f, 1.f, 1.f, 1.f};
    constexpr ivec4 c{5, 5, 5, 5};
    constexpr ivec4 d{2, 2, 3, 6};
    static_assert(a * 1.f == a);
    static_assert(b * 1.f == b);
    static_assert(b * 2.f == vec4{2.f, 2.f, 2.f, 2.f});
    static_assert(c * 3 == ivec4{15, 15, 15, 15});
    static_assert(d * 5 == ivec4{10, 10, 15, 30});
    SECTION("mul assignment") {
        vec4 aCopy = a;
        aCopy *= 10.f;
        REQUIRE(aCopy == vec4{0.f, 0.f, 0.f, 0.f});
        vec4 bCopy = b;
        bCopy *= 10.f;
        REQUIRE(bCopy == vec4{10.f, 10.f, 10.f, 10.f});
    }

    static_assert(-b == vec4{-1.f, -1.f, -1.f, -1.f});
    static_assert(-c == ivec4{-5, -5, -5, -5});

    static_assert(a / 5.f == a);
    static_assert(c / 5 == ivec4{1, 1, 1, 1});
    static_assert(d / 5 == ivec4{0, 0, 0, 1});
    SECTION("div assignment") {
        ivec4 cCopy = c;
        cCopy /= 2;
        REQUIRE(cCopy == ivec4{2});
        cCopy /= 10;
        REQUIRE(cCopy == ivec4{0});
    }
}
