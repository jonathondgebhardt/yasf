#include <memory>

#include "yasf/composite_node.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/behavior_tree.hpp"
#include "yasf/leaf_node.hpp"

TEST_CASE("composite node: node_type", "[library][behavior_tree]")
{
    SECTION("sequence")
    {
        const auto node = yasf::CompositeNode{
            yasf::CompositeNode::CompositeNodeType::SEQUENCE};
        REQUIRE(node.node_type() == "composite_node: sequence");
    }

    SECTION("selector")
    {
        const auto node = yasf::CompositeNode{
            yasf::CompositeNode::CompositeNodeType::SELECTOR};
        REQUIRE(node.node_type() == "composite_node: selector");
    }
}

struct FailingLeafNode : yasf::LeafNode
{
    auto evaluate() -> yasf::BehaviorTree::NodeStatus override
    {
        return yasf::BehaviorTree::NodeStatus::FAILURE;
    }
};

TEST_CASE("composite node: evaluate SEQUENCE", "[library][behavior_tree]")
{
    auto node =
        yasf::CompositeNode{yasf::CompositeNode::CompositeNodeType::SEQUENCE};

    SECTION("no nodes")
    {
        CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::SUCCESS);
    }

    SECTION("one success node")
    {
        node.add_node(std::make_unique<yasf::LeafNode>());
        CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::SUCCESS);

        SECTION("two success nodes")
        {
            node.add_node(std::make_unique<yasf::LeafNode>());
            CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::SUCCESS);
        }

        SECTION("one success node, one failing node")
        {
            node.add_node(std::make_unique<FailingLeafNode>());
            CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::FAILURE);
        }
    }

    SECTION("one failing node")
    {
        node.add_node(std::make_unique<FailingLeafNode>());
        CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::FAILURE);

        SECTION("two failing nodes")
        {
            node.add_node(std::make_unique<FailingLeafNode>());
            CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::FAILURE);
        }
    }
}

TEST_CASE("composite node: evaluate SELECTOR", "[library][behavior_tree]")
{
    auto node =
        yasf::CompositeNode{yasf::CompositeNode::CompositeNodeType::SELECTOR};

    SECTION("no nodes")
    {
        CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::SUCCESS);
    }

    SECTION("one success node")
    {
        node.add_node(std::make_unique<yasf::LeafNode>());
        CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::SUCCESS);

        SECTION("two success nodes")
        {
            node.add_node(std::make_unique<yasf::LeafNode>());
            CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::SUCCESS);
        }

        SECTION("one success node, one failing node")
        {
            node.add_node(std::make_unique<FailingLeafNode>());
            CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::SUCCESS);
        }
    }

    SECTION("one failing node")
    {
        node.add_node(std::make_unique<FailingLeafNode>());
        CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::FAILURE);

        SECTION("two failing nodes")
        {
            node.add_node(std::make_unique<FailingLeafNode>());
            CHECK(node.evaluate() == yasf::BehaviorTree::NodeStatus::FAILURE);
        }
    }
}
