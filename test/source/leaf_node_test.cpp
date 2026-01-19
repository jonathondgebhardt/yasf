#include "yasf/leaf_node.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("leaf node: node_type", "[library][behavior_tree]")
{
    const auto node = yasf::LeafNode{};
    REQUIRE(node.node_type() == "leaf_node");
}
