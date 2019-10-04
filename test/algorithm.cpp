#include <cm/algorithm.hpp>

#include <catch.hpp>

#include <array>
#include <vector>

TEST_CASE("copy", "[algorithm]") {
    std::vector<int> a(5, 0);
    std::vector<int> b{1, 2, 3, 4, 5};

    cm::copy<5>(a.data(), b.data());
    REQUIRE(a == b);

    b = {10, 11, 12, 13, 14};
    cm::copy<4>(a.data(), b.data());
    REQUIRE(a == std::vector{10, 11, 12, 13, 5});

    std::vector<float> c{-1.1f, -2.2f, -3.3f, -4.4f, -5.5f};
    cm::copy<3>(a.data(), c.data());
    REQUIRE(a == std::vector{-1, -2, -3, 13, 5});

    cm::copy<5>(c.data(), a.data());
    REQUIRE(c == std::vector{-1.f, -2.f, -3.f, 13.f, 5.f});
}

TEST_CASE("equal", "[algorithm]") {
    std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
    std::array<int, 6> b{{1, 2, 3, 4, 5, 7}};
    std::array<float, 5> c{{1.f, 2.f, 3.5f, 4.f, 5.f}};

    REQUIRE(!cm::equal<6>(a.data(), b.data()));
    REQUIRE(cm::equal<5>(a.data(), b.data()));
    REQUIRE(cm::equal<2>(a.data(), c.data()));
    REQUIRE(!cm::equal<5>(a.data(), c.data()));
}

TEST_CASE("lexicographical_compare", "[algorithm]") {
    std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
    std::array<int, 6> b{{1, 2, 3, 4, 5, 7}};
    std::array<float, 5> c{{1.f, 2.f, 3.5f, 4.f, 5.f}};

    REQUIRE(cm::lexicographical_compare<6>(a.data(), b.data()));
    REQUIRE(!cm::lexicographical_compare<6>(b.data(), a.data()));
    REQUIRE(!cm::lexicographical_compare<5>(a.data(), b.data()));
    REQUIRE(!cm::lexicographical_compare<2>(a.data(), c.data()));
    REQUIRE(cm::lexicographical_compare<5>(a.data(), c.data()));
}
