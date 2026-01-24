#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

#include "yasf/composite_node.hpp"

#include "yasf/behavior_tree.hpp"
#include "yasf/logger.hpp"

namespace yasf
{

auto CompositeNode::evaluate() -> BehaviorTree::NodeStatus
{
    switch (m_type) {
        using enum CompositeNodeType;
        case SEQUENCE:
            return evaluate_sequence();
        case SELECTOR:
            return evaluate_selector();
        case UNKNOWN:
            yasf::log::error("composite node '{}' has has type UNKNOWN",
                             name());
            break;
    }

    return BehaviorTree::NodeStatus::FAILURE;
}

auto CompositeNode::add_node(std::unique_ptr<BehaviorTree::Node> node) -> void
{
    m_nodes.push_back(std::move(node));
}

auto CompositeNode::get_node(std::size_t index) const -> Node*
{
    if (index >= m_nodes.size()) {
        return {};
    }

    return m_nodes[index].get();
}

auto CompositeNode::evaluate_sequence() -> BehaviorTree::NodeStatus
{
    if (m_nodes.empty()) {
        return BehaviorTree::NodeStatus::SUCCESS;
    }

    return std::ranges::all_of(m_nodes,
                               [](const auto& node) {
                                   return node->evaluate()
                                       == BehaviorTree::NodeStatus::SUCCESS;
                               })
        ? BehaviorTree::NodeStatus::SUCCESS
        : BehaviorTree::NodeStatus::FAILURE;
}

auto CompositeNode::evaluate_selector() -> BehaviorTree::NodeStatus
{
    if (m_nodes.empty()) {
        return BehaviorTree::NodeStatus::SUCCESS;
    }

    return std::ranges::any_of(m_nodes,
                               [](const auto& node) {
                                   return node->evaluate()
                                       == BehaviorTree::NodeStatus::SUCCESS;
                               })
        ? BehaviorTree::NodeStatus::SUCCESS
        : BehaviorTree::NodeStatus::FAILURE;
}

}  // namespace yasf
