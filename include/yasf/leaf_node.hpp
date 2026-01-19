#pragma once

#include "yasf/behavior_tree.hpp"

namespace yasf
{

class LeafNode : public BehaviorTree::Node
{
public:
    auto node_type() const -> std::string_view override { return "leaf_node"; }

    auto evaluate() -> BehaviorTree::NodeStatus override;

private:
};

}  // namespace yasf
