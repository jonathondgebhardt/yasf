#include "yasf/velocity.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("velocity: default")
{
    auto vel = yasf::Velocity{};
    const auto vec = vel.get();
    REQUIRE(vec.is_zero());
}

TEST_CASE("velocity: parameterized ctor")
{
    SECTION("Vec3d")
    {
        auto vel = yasf::Velocity{yasf::Vec3d{1.0, 2.0, 3.0}};
        REQUIRE(vel.get() == yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
    }

    SECTION("double, double, double")
    {
        auto vel = yasf::Velocity{1.0, 2.0, 3.0};
        REQUIRE(vel.get() == yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
    }
}

TEST_CASE("velocity: set and get")
{
    auto vel = yasf::Velocity{};
    vel.set(yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
    const auto vec = vel.get();
    REQUIRE(vec == yasf::Vec3d{1.0, 2.0, 3.0});  // NOLINT
}

TEST_CASE("velocity: modify vec in place")
{
    auto vel = yasf::Velocity{1.0, 2.0, 3.0};
    REQUIRE(vel.get() == yasf::Vec3d{1.0, 2.0, 3.0});

    vel.get() *= -1.0;
    REQUIRE(vel.get() == yasf::Vec3d{-1.0, -2.0, -3.0});
}
