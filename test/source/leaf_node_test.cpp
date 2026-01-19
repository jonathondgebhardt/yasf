#include "yasf/leaf_node.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("leaf node: name", "[library][behavior_tree]")
{
    const auto node = yasf::LeafNode{};
    REQUIRE(node.name() == "leaf_node");
}
