#include "yasf/decorator_node.hpp"

#include "yasf/behavior_tree.hpp"

namespace yasf
{

auto DecoratorNode::evaluate() -> BehaviorTree::NodeStatus
{
    return BehaviorTree::NodeStatus::SUCCESS;
}

}  // namespace yasf
