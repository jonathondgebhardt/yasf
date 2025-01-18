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

    SECTION("name")
    {
        REQUIRE(obj.add_child(std::make_unique<yasf::object>()));
    }

    SECTION("null child")
    {
        REQUIRE_FALSE(obj.add_child(nullptr));
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_child<yasf::object>());
    }
}

TEST_CASE("object: get_child", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_child(std::make_unique<yasf::object>()));

    SECTION("name")
    {
        auto* const child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }

    SECTION("templated")
    {
        auto* const child = obj.get_child<yasf::object>();
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }
}

TEST_CASE("object: parent", "[library]")
{
    auto obj = yasf::object{};

    SECTION("take by value")
    {
        REQUIRE(obj.add_child(std::make_unique<yasf::object>()));
        auto const* child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_child<yasf::object>());
        auto const* child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }
}

TEST_CASE("object: remove_child", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_child<yasf::object>());

    SECTION("name")
    {
        REQUIRE(obj.remove_child("object"));
    }

    SECTION("templated")
    {
        REQUIRE(obj.remove_child<yasf::object>());
    }
}

TEST_CASE("object: add_component", "[library]")
{
    auto obj = yasf::object{};

    SECTION("name")
    {
        REQUIRE(obj.add_component(std::make_unique<yasf::component>()));
    }

    SECTION("null component")
    {
        REQUIRE_FALSE(obj.add_component(nullptr));
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_component<yasf::component>());
    }
}

TEST_CASE("object: get_component", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_component(std::make_unique<yasf::component>()));

    SECTION("name")
    {
        REQUIRE(obj.get_component("component") != nullptr);
    }

    SECTION("valid component")
    {
        REQUIRE(obj.get_component<yasf::component>() != nullptr);
    }
}

TEST_CASE("object: remove_component", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_component<yasf::component>());

    SECTION("name")
    {
        REQUIRE(obj.remove_component("component"));
    }

    SECTION("templated")
    {
        REQUIRE(obj.remove_component<yasf::component>());
    }
}
