#include <string>

#include "yasf/status.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/object.hpp"

TEST_CASE("status: name", "[library]")
{
    SECTION("default")
    {
        auto const exported = yasf::status{};
        REQUIRE(exported.name() == std::string("status"));
    }
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

TEST_CASE("status: object component", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_component<yasf::status>());

    SECTION("get_component")
    {
        auto* const child = obj.get_component<yasf::status>();
        REQUIRE(child != nullptr);
    }
}
