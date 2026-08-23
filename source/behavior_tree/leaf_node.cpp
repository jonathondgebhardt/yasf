#include "yasf/behavior_tree/leaf_node.hpp"

#include "yasf/behavior_tree/behavior_tree.hpp"

namespace yasf
{

auto LeafNode::evaluate() -> BehaviorTree::NodeStatus
{
    return BehaviorTree::NodeStatus::SUCCESS;
}

}  // namespace yasf
