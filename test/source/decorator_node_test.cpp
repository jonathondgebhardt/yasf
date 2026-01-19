#include "yasf/decorator_node.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("decorator node: name", "[library][behavior_tree]")
{
    const auto node = yasf::DecoratorNode{};
    REQUIRE(node.name() == "decorator_node");
}
