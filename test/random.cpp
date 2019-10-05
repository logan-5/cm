#include <cm/generic_ops.hpp>
#include <cm/random.hpp>

#include <catch.hpp>

TEST_CASE("'random_on' magnitudes", "[random]") {
    using namespace cm;

    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_circle()), 1.f));

    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
    REQUIRE(fuzzy_equals(magnitude(random_on_unit_sphere()), 1.f));
}