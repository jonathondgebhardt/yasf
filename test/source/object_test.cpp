#include <memory>
#include <string>

#include "yasf/object.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is object", "[library]")
{
    auto const exported = yasf::object{};
    REQUIRE(exported.name() == std::string("object"));
}

TEST_CASE("Set name is yasf", "[library]")
{
    auto obj = yasf::object{};
    obj.set_name("yasf");
    REQUIRE(obj.name() == std::string{"yasf"});
}

TEST_CASE("add_child valid child", "[library]")
{
    const auto parent = std::make_unique<yasf::object>();
    auto child = std::make_unique<yasf::object>();
    REQUIRE(parent->add_child(std::move(child)));
}

TEST_CASE("add_child null child", "[library]")
{
    const auto parent = std::make_unique<yasf::object>();
    REQUIRE_FALSE(parent->add_child(nullptr));
}
