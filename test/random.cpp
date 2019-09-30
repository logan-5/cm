#include <cm/random.hpp>

#include <catch.hpp>

static bool fuzzy_equals(float a, float b, float tolerance) {
    return std::abs(a - b) < tolerance;
}

TEST_CASE("'random_on' magnitudes", "[random]") {
    using namespace cm;

    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f, 0.0000001f));

    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f, 0.0000001f));
}