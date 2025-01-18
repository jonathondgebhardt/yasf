#include "yasf/position.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("position: default")
{
    const auto pos = yasf::position{};
    const auto vec = pos.get();
    REQUIRE(vec.is_zero());
}

TEST_CASE("position: set and get")
{
    auto pos = yasf::position{};
    pos.set(yasf::vec3d{1.0, 2.0, 3.0});  // NOLINT
    const auto vec = pos.get();
    REQUIRE(vec == yasf::vec3d{1.0, 2.0, 3.0});  // NOLINT
}
