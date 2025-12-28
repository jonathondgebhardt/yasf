#include <memory>
#include <string>

#include "yasf/object.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/component.hpp"

TEST_CASE("object: name", "[library]")
{
    auto const obj = yasf::Object{};
    REQUIRE(obj.name() == std::string("object"));
}

TEST_CASE("object: uuid", "[library]")
{
    auto const obj = yasf::Object{};
    CHECK_FALSE(obj.uuid().empty());
}

TEST_CASE("object: add_child", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("name")
    {
        REQUIRE(obj.add_child(std::make_unique<yasf::Object>()));
    }

    SECTION("null child")
    {
        REQUIRE_FALSE(obj.add_child(nullptr));
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_child<yasf::Object>());
    }
}

TEST_CASE("object: get_child", "[library]")
{
    auto obj = yasf::Object{};
    REQUIRE(obj.add_child(std::make_unique<yasf::Object>()));

    SECTION("name")
    {
        auto* const child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }

    SECTION("templated")
    {
        auto* const child = obj.get_child<yasf::Object>();
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }
}

TEST_CASE("object: parent", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("take by value")
    {
        REQUIRE(obj.add_child(std::make_unique<yasf::Object>()));
        auto const* child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_child<yasf::Object>());
        auto const* child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }
}

TEST_CASE("object: remove_child", "[library]")
{
    auto obj = yasf::Object{};
    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("name")
    {
        REQUIRE(obj.remove_child("object"));
    }

    SECTION("templated")
    {
        REQUIRE(obj.remove_child<yasf::Object>());
    }
}

TEST_CASE("object: add_component", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("name")
    {
        REQUIRE(obj.add_component(std::make_unique<yasf::Component>()));
    }

    SECTION("null component")
    {
        REQUIRE_FALSE(obj.add_component(nullptr));
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_component<yasf::Component>());
    }
}

TEST_CASE("object: get_component", "[library]")
{
    auto obj = yasf::Object{};
    REQUIRE(obj.add_component(std::make_unique<yasf::Component>()));

    SECTION("name")
    {
        REQUIRE(obj.get_component("component") != nullptr);
    }

    SECTION("valid component")
    {
        REQUIRE(obj.get_component<yasf::Component>() != nullptr);
    }
}

TEST_CASE("object: remove_component", "[library]")
{
    auto obj = yasf::Object{};
    REQUIRE(obj.add_component<yasf::Component>());

    SECTION("name")
    {
        REQUIRE(obj.remove_component("component"));
    }

    SECTION("templated")
    {
        REQUIRE(obj.remove_component<yasf::Component>());
    }
}
