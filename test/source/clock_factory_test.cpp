#include "yasf/clock_factory.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("clock_factory: build fixed update", "[library][factory]")
{
    auto obj = yasf::ClockFactory::build_fixed_update(yasf::time::Seconds{1.0});
    REQUIRE(obj != nullptr);

    SECTION("has fixed updater")
    {
        REQUIRE(obj->get_component("fixed_time_updater") != nullptr);
    }
}

TEST_CASE("clock_factory: build external update", "[library][factory]")
{
    auto obj = yasf::ClockFactory::build_external_update();
    REQUIRE(obj != nullptr);

    SECTION("has external updater")
    {
        REQUIRE(obj->get_component("external_time_updater") != nullptr);
    }
}
