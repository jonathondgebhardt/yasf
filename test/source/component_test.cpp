#include <string>

#include "yasf/component.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("component: name", "[library]")
{
    SECTION("default")
    {
        auto const exported = yasf::component{};
        REQUIRE(exported.name() == std::string("component"));
    }
}
