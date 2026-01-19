#pragma once

#include <memory>
#include <vector>

#include "yasf/behavior_tree.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class CompositeNode : public BehaviorTree::Node
{
public:
    enum class CompositeNodeType : std::uint8_t
    {
        UNKNOWN,
        SEQUENCE,  ///< AND
        SELECTOR  ///< OR
    };

    explicit CompositeNode(CompositeNodeType type)
        : m_type{type}
    {
    }

    auto node_type() const -> std::string_view override
    {
        switch (m_type) {
            using enum CompositeNodeType;
            case SEQUENCE:
                return "composite_node: sequence";
            case SELECTOR:
                return "composite_node: selector";
            case UNKNOWN:
                return "composite_node: unknown";
        }

        return BehaviorTree::Node::node_type();
    }

    // todo: should probably return a pair of NodeStatus and Node so
    // BehaviorTree can track "RUNNING" nodes.
    // i think the idea is that a running node would continue evaluating on the
    // next tick until it returns SUCCESS or FAILURE, but how do i go back to
    // that node in the tree to resume evaluation?
    auto evaluate() -> BehaviorTree::NodeStatus override;

    auto add_node(std::unique_ptr<BehaviorTree::Node> node) -> void;

private:
    auto evaluate_sequence() -> BehaviorTree::NodeStatus;
    auto evaluate_selector() -> BehaviorTree::NodeStatus;

    YASF_SUPPRESS_C4251
    std::vector<std::unique_ptr<BehaviorTree::Node>> m_nodes;
    CompositeNodeType m_type{CompositeNodeType::UNKNOWN};
};

}  // namespace yasf
