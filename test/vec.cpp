#include <cm/vec.hpp>

#include <catch.hpp>

using namespace cm;

static_assert(std::is_trivial_v<scalar>);
static_assert(std::is_trivial_v<vec2>);
static_assert(std::is_trivial_v<vec3>);
static_assert(std::is_trivial_v<vec4>);

// construction from pieces
static_assert(scalar{0.f}.get() == 0.f);
static_assert(static_cast<scalar::rep>(scalar{1.f}) == 1.f);
static_assert(vec2{0.f, 1.f} == vec2{scalar{0.f}, scalar{1.f}});
static_assert(vec3{1.f, 2.f, 3.f} ==
              vec3{scalar{1.f}, scalar{2.f}, scalar{3.f}});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{vec2{1.f, 2.f}, scalar{3.f}});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{scalar{1.f}, vec2{2.f, 3.f}});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{vec2{1.f, 2.f}, 3.f});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{1.f, vec2{2.f, 3.f}});
static_assert(vec3{1.f, 2.f, 3.f} == vec3{1, 2, 3});
static_assert(vec4{1.f, 2.f, 3.f, 4.f} == vec4{1.f, vec2{2.f, 3.f}, 4.f});

// construction from scalars
static_assert(vec2{1.f} == vec2{1.f, 1.f});
static_assert(vec3{5.f} == vec3{5.f, 5.f, 5.f});

// conversion
static_assert(vec2{1.f, 2.f} == vec2{ivec2{1, 2}});
static_assert(ivec2{1.f, 2.f} == ivec2{vec2{1, 2}});

// access
static_assert(vec2{1.f, 2.f}.x() == 1.f);
static_assert(vec2{1.f, 2.f}.y() == 2.f);
static_assert(vec3{1.f, 2.f, 3.f}.z() == vec3{1.f, 2.f, 3.f}.b());

TEST_CASE("accessors", "[vec]") {
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

TEST_CASE("component-wise operations", "[vec]") {
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

TEST_CASE("scalar operations", "[vec]") {
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

static_assert(dot(ivec2{-6, 8}, ivec2{5, 12}) == 66);
static_assert(dot(ivec3{1, 3, -5}, ivec3{4, -2, -1}) == 3);
static_assert(dot(vec3{9.f, 2.f, 7.f}, vec3{4.f, 8.f, 10.f}) == 122.f);

static_assert(magnitude_squared(ivec2{1, 0}) == 1);
static_assert(magnitude_squared(ivec2{0, 1}) == 1);
static_assert(magnitude_squared(ivec2{1, 1}) == 2);
static_assert(magnitude_squared(vec3{5.f, 5.f, 5.f}) == 75.f);

TEST_CASE("magnitude", "[vec]") {
    REQUIRE(magnitude(ivec2{1, 0}) == 1);
    REQUIRE(magnitude(ivec2{0, 1}) == 1);
    REQUIRE(magnitude(ivec2{1, 1}) == 1);
    REQUIRE(fuzzy_equals(magnitude(vec2{1, 1}), float(M_SQRT2)));
    using Margin = error_margin<vec3::rep, std::ratio<5, 1000>>;
    REQUIRE(fuzzy_equals<vec3, Margin>(magnitude(vec3{2.f, 3.f, 5.f}), 6.16f));
}

TEST_CASE("normalized", "[vec]") {
    REQUIRE(normalized(ivec2{1, 0}) == ivec2{1, 0});
    REQUIRE(normalized(ivec2{0, 1}) == ivec2{0, 1});
    REQUIRE(normalized(ivec2{1, 1}) == ivec2{1, 1});
    REQUIRE(magnitude(normalized(vec4{5.f, 50.f, 85.f, 9.f})) == 1.f);
}

TEST_CASE("copying", "[vec]") {
    vec4 a{1, 2, 3, 4};
    vec4 b = a;

    vec4 c = a + b;
    c = a - b;
    c = a * b;
    c = a / b;

    c = a * 2.f;
    c = -a;
    c = a / 2.f;

    c = normalized(a);

    REQUIRE("if this all compiled, then we're good");
}

TEST_CASE("clamp_componentwise", "[vec]") {
    static_assert(cm::clamp(vec2{0.5f}, 0.f, 1.f) == vec2{0.5f});
    static_assert(cm::clamp(vec2{10.5f, 2.5f}, 2.f, 3.f) == vec2{3.f, 2.5f});
    static_assert(cm::clamp(vec4{-100.5f, 0.f, -2.f, 3.f}, -9.f, 1.f) ==
                  vec4{-9.f, 0.f, -2.f, 1.f});

    REQUIRE(cm::clamp(vec2{0.5f}, 0.f, 1.f) == vec2{0.5f});
    REQUIRE(cm::clamp(vec2{10.5f, 2.5f}, 2.f, 3.f) == vec2{3.f, 2.5f});
    REQUIRE(cm::clamp(vec4{-100.5f, 0.f, -2.f, 3.f}, -9.f, 1.f) ==
            vec4{-9.f, 0.f, -2.f, 1.f});

    static_assert(cm::clamp(vec2{10.f}, vec2{0.f}, vec2{20.f}) == vec2{10.f});
    static_assert(cm::clamp(vec2{10.f}, vec2{0.f}, vec2{20.f, 5.f}) ==
                  vec2{10.f, 5.f});
    static_assert(cm::clamp(vec4{-100.5f, 0.f, -2.f, 3.f}, vec4{-9.f},
                            vec4{1.f}) == vec4{-9.f, 0.f, -2.f, 1.f});

    REQUIRE(cm::clamp(vec2{10.f}, vec2{0.f}, vec2{20.f}) == vec2{10.f});
    REQUIRE(cm::clamp(vec2{10.f}, vec2{0.f}, vec2{20.f, 5.f}) ==
            vec2{10.f, 5.f});
    REQUIRE(cm::clamp(vec4{-100.5f, 0.f, -2.f, 3.f}, vec4{-9.f}, vec4{1.f}) ==
            vec4{-9.f, 0.f, -2.f, 1.f});
}

#include <cm/generic_ops.hpp>

TEST_CASE("linearstep_componentwise", "[vec]") {
    static_assert(cm::linearstep(vec2{0.5f}, vec2{0.f}, vec2{0.5f}) ==
                  vec2{0.f});
    static_assert(cm::linearstep(vec2{0.5f}, vec2{0.f}, vec2{0.f}) ==
                  vec2{1.f});
    static_assert(cm::linearstep(vec2{0.5f}, vec2{0.f}, vec2{0.f, 1.f}) ==
                  vec2{1.f, 0.f});

    REQUIRE(cm::linearstep(vec2{0.5f}, vec2{0.f}, vec2{0.5f}) == vec2{0.f});
    REQUIRE(cm::linearstep(vec2{0.5f}, vec2{0.f}, vec2{0.f}) == vec2{1.f});
    REQUIRE(cm::linearstep(vec2{0.5f}, vec2{0.f}, vec2{0.f, 1.f}) ==
            vec2{1.f, 0.f});

    static_assert(cm::linearstep(-1.f, 1.f, vec3{2.f, -10.f, 0.5f}) ==
                  vec3{1.f, 0.f, 0.75f});
}

TEST_CASE("bounce", "[vec]") {
    SECTION("2D") {
        REQUIRE(fuzzy_equals(cm::bounce(cm::normalized(cm::vec2{1.f, -1.f}),
                                        cm::normalized(cm::vec2{0.f, 1.f})),
                             cm::normalized(cm::vec2{1.f, 1.f})));
        REQUIRE(fuzzy_equals(cm::bounce(cm::normalized(cm::vec2{-1.f, 1.f}),
                                        cm::normalized(cm::vec2{1.f, 0.f})),
                             cm::normalized(cm::vec2{1.f, 1.f})));
        REQUIRE(fuzzy_equals(cm::bounce(cm::normalized(cm::vec2{1.f, -1.f}),
                                        cm::normalized(cm::vec2{-1.f, 1.f})),
                             cm::normalized(cm::vec2{-1.f, 1.f})));
    }
    SECTION("3D") {
        REQUIRE(
              fuzzy_equals(cm::bounce(cm::normalized(cm::vec3{1.f, -1.f, 0.f}),
                                      cm::normalized(cm::vec3{0.f, 1.f, 0.f})),
                           cm::normalized(cm::vec3{1.f, 1.f, 0.f})));
        REQUIRE(
              fuzzy_equals(cm::bounce(cm::normalized(cm::vec3{-1.f, 1.f, 0.f}),
                                      cm::normalized(cm::vec3{1.f, 0.f, 0.f})),
                           cm::normalized(cm::vec3{1.f, 1.f, 0.f})));
        REQUIRE(
              fuzzy_equals(cm::bounce(cm::normalized(cm::vec3{1.f, -1.f, 0.f}),
                                      cm::normalized(cm::vec3{-1.f, 1.f, 0.f})),
                           cm::normalized(cm::vec3{-1.f, 1.f, 0.f})));
    }
}

TEST_CASE("relational ops", "[vec]") {
    constexpr vec4 a{1.f, 2.f, 3.f, 4.f};
    constexpr vec4 b{4.f, 3.f, 2.f, 1.f};

    static_assert(a != b);
    static_assert(a < b);
    static_assert(a <= b);
    static_assert(b > a);
    static_assert(b >= a);
    REQUIRE(a != b);
    REQUIRE(a < b);
    REQUIRE(a <= b);
    REQUIRE(b > a);
    REQUIRE(b >= a);

    constexpr ivec4 c{1, 1, 1, 1};
    constexpr ivec4 d{1, 1, 1, 1};

    static_assert(c == d);
    static_assert(c <= d);
    static_assert(d <= c);
    static_assert(c >= d);
    static_assert(d >= c);
    REQUIRE(c == d);
    REQUIRE(c <= d);
    REQUIRE(d <= c);
    REQUIRE(c >= d);
    REQUIRE(d >= c);
}
