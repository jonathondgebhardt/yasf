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
        REQUIRE(obj.add_child(std::make_unique<yasf::object>()));
    }

    SECTION("null child")
    {
        REQUIRE_FALSE(obj.add_child(nullptr));
    }
}

TEST_CASE("object: add_child templated", "[library]")
{
    auto obj = yasf::object{};

    SECTION("valid child")
    {
        REQUIRE(obj.add_child<yasf::object>());
    }
}

TEST_CASE("object: get_child", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_child(std::make_unique<yasf::object>()));

    SECTION("valid component")
    {
        REQUIRE(obj.get_child("object") != nullptr);
    }
}

TEST_CASE("object: get_child templated", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_child<yasf::object>());

    SECTION("valid component")
    {
        REQUIRE(obj.get_child<yasf::object>() != nullptr);
    }
}

TEST_CASE("object: add_component", "[library]")
{
    auto obj = yasf::object{};

    SECTION("valid component")
    {
        REQUIRE(obj.add_component(std::make_unique<yasf::component>()));
    }

    SECTION("null component")
    {
        REQUIRE_FALSE(obj.add_component(nullptr));
    }
}

TEST_CASE("object: add_component templated", "[library]")
{
    auto obj = yasf::object{};

    SECTION("valid component")
    {
        REQUIRE(obj.add_component<yasf::component>());
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

TEST_CASE("object: get_component templated", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_component<yasf::component>());

    SECTION("valid component")
    {
        REQUIRE(obj.get_component<yasf::component>() != nullptr);
    }
}
