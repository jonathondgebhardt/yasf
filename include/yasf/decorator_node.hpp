#pragma once

#include "yasf/behavior_tree.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

// transform the result they receive from their child node's status, to
// terminate the child, or repeat processing of the child, depending on the type
// of decorator node
class DecoratorNode : public BehaviorTree::Node
{
public:
    auto node_type() const -> std::string_view override
    {
        return "decorator_node";
    }

    auto evaluate() -> BehaviorTree::NodeStatus override;

private:
    YASF_SUPPRESS_C4251
    std::vector<BehaviorTree::Node> m_nodes;
};

}  // namespace yasf
