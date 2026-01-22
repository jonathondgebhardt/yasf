#include <algorithm>
#include <cstddef>

#include "yasf/behavior_tree.hpp"

#include "yasf/component.hpp"

namespace yasf
{

BehaviorTree::BehaviorTree()
    : Component{"behavior_tree"}
{
}

auto BehaviorTree::get_node(std::size_t index) -> Node*
{
    if (index >= m_nodes.size()) {
        return {};
    }

    return m_nodes[index].get();
}

auto BehaviorTree::evaluate() -> void
{
    std::ranges::for_each(m_nodes, [&](auto&& node) { node->evaluate(); });
}

}  // namespace yasf
