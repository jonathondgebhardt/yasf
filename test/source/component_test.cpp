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

    SECTION("constructor")
    {
        auto const exported = yasf::component{"foo"};
        REQUIRE(exported.name() == std::string("foo"));
    }
}

TEST_CASE("component: set_name", "[library]")
{
    auto obj = yasf::component{};
    obj.set_name("yasf");
    REQUIRE(obj.name() == std::string{"yasf"});
}
