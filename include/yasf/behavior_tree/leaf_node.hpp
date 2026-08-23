#pragma once

#include "yasf/behavior_tree/behavior_tree.hpp"
#include "yasf/behavior_tree/yasf_behavior_tree_export.hpp"

namespace yasf
{

class YASF_BEHAVIOR_TREE_EXPORT LeafNode : public BehaviorTree::Node
{
public:
    auto node_type() const -> std::string_view override { return "leaf_node"; }

    auto evaluate() -> BehaviorTree::NodeStatus override;

private:
};

}  // namespace yasf
