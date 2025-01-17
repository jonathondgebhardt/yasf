#include <memory>
#include <string>

#include "yasf/object.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/component.hpp"

TEST_CASE("object: name", "[library]")
{
    auto const obj = yasf::object{};
    REQUIRE(obj.name() == std::string("object"));
}

TEST_CASE("object: add_child", "[library]")
{
    auto obj = yasf::object{};

    SECTION("valid child")
    {
        // It's unfortunate that you lose access to the child once you add it to
        // the parent. It's hard for me to test whether the child's parent got
        // set.
        REQUIRE(obj.add_child(std::make_unique<yasf::object>()));
    }

    SECTION("null child")
    {
        REQUIRE_FALSE(obj.add_child(nullptr));
    }
}

TEST_CASE("object: add_component", "[library]")
{
    auto obj = yasf::object{};

    SECTION("valid component")
    {
        // It's unfortunate that you lose access to the child once you add it to
        // the parent. It's hard for me to test whether the child's parent got
        // set.
        REQUIRE(obj.add_component(std::make_unique<yasf::component>()));
    }

    SECTION("null component")
    {
        REQUIRE_FALSE(obj.add_component(nullptr));
    }
}

TEST_CASE("object: get_component", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_component(std::make_unique<yasf::component>()));

    SECTION("valid component")
    {
        REQUIRE(obj.get_component("component") != nullptr);
    }
}
