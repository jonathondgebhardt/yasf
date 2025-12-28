#include "yasf/velocity.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("velocity: default")
{
    const auto pos = yasf::Velocity{};
    const auto vec = pos.get();
    REQUIRE(vec.is_zero());
}

TEST_CASE("velocity: parameterized ctor")
{
    const auto pos = yasf::Velocity{yasf::Vec3d{1.0, 2.0, 3.0}};
    REQUIRE(pos.get() == yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
}

TEST_CASE("velocity: set and get")
{
    auto pos = yasf::Velocity{};
    pos.set(yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
    const auto vec = pos.get();
    REQUIRE(vec == yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
}
