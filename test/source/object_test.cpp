#include <memory>
#include <string>

#include "yasf/object.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("object: name", "[library]")
{
    auto const obj = yasf::object{};
    REQUIRE(obj.name() == std::string("object"));
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
