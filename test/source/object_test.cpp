#include <memory>
#include <string>

#include "yasf/object.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/component.hpp"

TEST_CASE("object: name", "[library]")
{
    SECTION("default")
    {
        auto const obj = yasf::object{};
        REQUIRE(obj.name() == std::string("object"));
    }

    SECTION("constructor")
    {
        auto const obj = yasf::object{"foo"};
        REQUIRE(obj.name() == std::string("foo"));
    }
}

TEST_CASE("object: set_name", "[library]")
{
    auto obj = yasf::object{};
    obj.set_name("yasf");
    REQUIRE(obj.name() == std::string{"yasf"});
}

TEST_CASE("object: add_child", "[library]")
{
    auto obj = yasf::object{};

    SECTION("valid child")
    {
        // It's unfortunate that you lose access to the child once you add it to
        // the parent. It's hard for me to test whether the child's parent got
        // set.
        auto child = std::make_unique<yasf::object>();
        REQUIRE(obj.add_child(std::move(child)));
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
        auto component = std::make_unique<yasf::component>();
        REQUIRE(obj.add_component(std::move(component)));
    }

    SECTION("null component")
    {
        REQUIRE_FALSE(obj.add_component(nullptr));
    }
}

TEST_CASE("object: get_component", "[library]")
{
    auto obj = yasf::object{};

    {
        auto component = std::make_unique<yasf::component>();
        component->set_name("some");
        REQUIRE(obj.add_component(std::move(component)));
    }

    {
        auto component = std::make_unique<yasf::component>();
        component->set_name("other");
        REQUIRE(obj.add_component(std::move(component)));
    }

    SECTION("valid component")
    {
        auto* comp = obj.get_component("some");
        REQUIRE(comp);
        REQUIRE(comp->name() == "some");
    }
}
