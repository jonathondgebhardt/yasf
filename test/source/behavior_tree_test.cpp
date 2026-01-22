#include <cstddef>
#include <memory>

#include "yasf/behavior_tree.hpp"

#include <catch2/catch_test_macros.hpp>

struct TestNode : yasf::BehaviorTree::Node
{
    auto evaluate() -> yasf::BehaviorTree::NodeStatus override
    {
        return yasf::BehaviorTree::NodeStatus::SUCCESS;
    }
};

TEST_CASE("behavior tree: name", "[library][behavior_tree]")
{
    const auto tree = yasf::BehaviorTree{};
    REQUIRE(tree.name() == "behavior_tree");
}

TEST_CASE("behavior tree: num_nodes", "[library][behavior_tree]")
{
    auto tree = yasf::BehaviorTree{};
    CHECK(tree.num_nodes() == std::size_t{0});

    tree.add_node(std::make_unique<TestNode>());
    CHECK(tree.num_nodes() == std::size_t{1});
}

TEST_CASE("behavior tree: get_node", "[library][behavior_tree]")
{
    auto tree = yasf::BehaviorTree{};
    CHECK(tree.get_node(std::size_t{0}) == nullptr);

    tree.add_node(std::make_unique<TestNode>());
    CHECK(tree.get_node(std::size_t{0}) != nullptr);
    CHECK(tree.get_node(std::size_t{1}) == nullptr);
}
