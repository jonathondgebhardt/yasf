#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include "yasf/decorator_node.hpp"

#include "yasf/behavior_tree.hpp"

namespace yasf
{

auto DecoratorNode::evaluate() -> BehaviorTree::NodeStatus
{
    return BehaviorTree::NodeStatus::SUCCESS;
}

auto DecoratorNode::add_node(std::unique_ptr<BehaviorTree::Node> node) -> void
{
    m_nodes.push_back(std::move(node));
}

auto DecoratorNode::get_node(std::size_t index) -> Node*
{
    if (index >= m_nodes.size()) {
        return {};
    }

    return m_nodes[index].get();
}

}  // namespace yasf
