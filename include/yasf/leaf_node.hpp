#pragma once

#include "yasf/behavior_tree.hpp"

namespace yasf
{

class LeafNode : public BehaviorTree::Node
{
public:
    LeafNode() { set_name("leaf_node"); }

    auto evaluate() -> BehaviorTree::NodeStatus override;

private:
};

}  // namespace yasf
