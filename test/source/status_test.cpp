#include <string>

#include "yasf/status.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("status: name", "[library]")
{
    SECTION("default")
    {
        auto const exported = yasf::status{};
        REQUIRE(exported.name() == std::string("status"));
    }

    SECTION("constructor")
    {
        auto const exported = yasf::status{"foo"};
        REQUIRE(exported.name() == std::string("foo"));
    }

    SECTION("state constructor")
    {
        auto const exported = yasf::status{yasf::status::state::startup};
        REQUIRE(exported.name() == std::string("status"));
    }
}

TEST_CASE("status: set_name", "[library]")
{
    auto obj = yasf::status{};
    obj.set_name("yasf");
    REQUIRE(obj.name() == std::string{"yasf"});
}

TEST_CASE("status: state", "[library]")
{
    SECTION("default")
    {
        auto status = yasf::status{};
        REQUIRE(status.get_state() == yasf::status::state::unknown);
    }

    SECTION("constructor")
    {
        auto status = yasf::status{yasf::status::state::startup};
        REQUIRE(status.get_state() == yasf::status::state::startup);
    }

    SECTION("set_state")
    {
        auto status = yasf::status{};
        status.set_state(yasf::status::state::startup);
        REQUIRE(status.get_state() == yasf::status::state::startup);
    }
}
