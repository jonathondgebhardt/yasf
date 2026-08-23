#include "yasf/behavior_tree/decorator_node.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("decorator node: node_type", "[library][behavior_tree]")
{
    const auto node = yasf::DecoratorNode{};
    REQUIRE(node.node_type() == "decorator_node");
}
