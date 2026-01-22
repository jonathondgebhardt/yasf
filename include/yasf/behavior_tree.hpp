#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "yasf/component.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

// https://www.gamedeveloper.com/programming/behavior-trees-for-ai-how-they-work
class YASF_EXPORT BehaviorTree : public Component
{
public:
    enum class NodeStatus : std::uint8_t
    {
        UNKNOWN,
        SUCCESS,
        FAILURE,
        RUNNING
    };

    class Node
    {
    public:
        Node() = default;
        Node(const Node&) = default;
        Node(Node&&) = delete;
        virtual ~Node() = default;
        auto operator=(const Node&) -> Node& = default;
        auto operator=(Node&&) -> Node& = delete;

        virtual auto evaluate() -> NodeStatus = 0;

        virtual auto node_type() const -> std::string_view { return "unknown"; }

        auto set_name(std::string name) -> void { m_name = std::move(name); }

        auto name() const -> std::string_view { return m_name; }

    private:
        std::string m_name;
    };

    BehaviorTree();

    auto add_node(std::unique_ptr<Node> node)
    {
        m_nodes.push_back(std::move(node));
    }

    auto num_nodes() const -> std::size_t { return m_nodes.size(); }

    auto get_node(std::size_t index) -> Node*;

    auto evaluate() -> void;

private:
    YASF_SUPPRESS_C4251
    std::vector<std::unique_ptr<Node>> m_nodes;
};

}  // namespace yasf
