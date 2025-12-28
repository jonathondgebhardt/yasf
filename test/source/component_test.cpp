#include <memory>
#include <string>

#include "yasf/component.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/object.hpp"

TEST_CASE("component: name", "[library]")
{
    auto const component = yasf::Component{};
    REQUIRE(component.name() == std::string("component"));
}

TEST_CASE("component: uuid", "[library]")
{
    auto const component = yasf::Component{};
    CHECK_FALSE(component.uuid().empty());
}

TEST_CASE("component: parent", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("take by value")
    {
        REQUIRE(obj.add_component(std::make_unique<yasf::Component>()));
        auto const* component = obj.get_component("component");
        REQUIRE(component != nullptr);
        REQUIRE(component->parent() != nullptr);
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_component<yasf::Component>());
        auto const* component = obj.get_component("component");
        REQUIRE(component != nullptr);
        REQUIRE(component->parent() != nullptr);
    }
}
