#include "yasf/position.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("position: default")
{
    auto pos = yasf::Position{};
    const auto vec = pos.get();
    REQUIRE(vec.is_zero());
}

TEST_CASE("position: parameterized ctor")
{
    auto pos = yasf::Position{yasf::Vec3d{1.0, 2.0, 3.0}};
    REQUIRE(pos.get() == yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
}

TEST_CASE("position: set and get")
{
    auto pos = yasf::Position{};
    pos.set(yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
    const auto vec = pos.get();
    REQUIRE(vec == yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
}

TEST_CASE("position: modify vec in place")
{
    auto pos = yasf::Position{1.0, 2.0, 3.0};
    REQUIRE(pos.get() == yasf::Vec3d{1.0, 2.0, 3.0});

    pos.get() *= -1.0;
    REQUIRE(pos.get() == yasf::Vec3d{-1.0, -2.0, -3.0});
}
