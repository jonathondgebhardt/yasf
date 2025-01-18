#include "yasf/clock_factory.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("clock_factory: build fixed update", "[factory]")
{
    auto obj = yasf::clock_factory::build_fixed_update(1.0);
    REQUIRE(obj != nullptr);

    SECTION("has fixed updater")
    {
        auto* comp = obj->get_component("fixed_time_updater");
        REQUIRE(comp != nullptr);
    }
}
