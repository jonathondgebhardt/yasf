#include "yasf/behavior_tree.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("behavior tree: name", "[library][behavior_tree]")
{
    const auto tree = yasf::BehaviorTree{};
    REQUIRE(tree.name() == "behavior_tree");
}
