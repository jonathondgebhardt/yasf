#include "behavior_tree_drawable.hpp"

#include <imgui.h>

#include "yasf/composite_node.hpp"
#include "yasf/decorator_node.hpp"
#include "yasf/leaf_node.hpp"
#include "yasf/logger.hpp"

auto BehaviorTreeDrawable::draw() -> void
{
    if (m_tree == nullptr) {
        return;
    }

    if (ImGui::CollapsingHeader("behavior tree")) {
        for (auto i = 0u; i < m_tree->num_nodes(); ++i) {
            draw_node_helper(m_tree->get_node(i));
        }
    }
}

auto BehaviorTreeDrawable::draw_node_helper(
    const yasf::BehaviorTree::Node* node) -> void
{
    if (const auto* composite_node =
            dynamic_cast<const yasf::CompositeNode*>(node);
        composite_node != nullptr)
    {
        draw_composite_node(composite_node);
    } else if (const auto* decorator_node =
                   dynamic_cast<const yasf::DecoratorNode*>(node);
               decorator_node != nullptr)
    {
        draw_decorator_node(decorator_node);
    } else if (const auto* leaf_node =
                   dynamic_cast<const yasf::LeafNode*>(node);
               leaf_node != nullptr)
    {
        draw_leaf_node(leaf_node);
    } else {
        yasf::log::error("unrecognized node type: {}", node->node_type());
    }
}

auto BehaviorTreeDrawable::draw_composite_node(const yasf::CompositeNode* node)
    -> void
{
    if (node == nullptr) {
        return;
    }

    if (ImGui::TreeNode(node->node_type().data())) {
        for (auto i = 0u; i < node->num_nodes(); ++i) {
            draw_node_helper(node->get_node(i));
        }

        ImGui::TreePop();
    }
}

auto BehaviorTreeDrawable::draw_decorator_node(const yasf::DecoratorNode* node)
    -> void
{
    if (node == nullptr) {
        return;
    }

    if (ImGui::TreeNode(node->node_type().data())) {
        for (auto i = 0u; i < node->num_nodes(); ++i) {
            draw_node_helper(node->get_node(i));
        }

        ImGui::TreePop();
    }
}

auto BehaviorTreeDrawable::draw_leaf_node(const yasf::LeafNode* node) -> void
{
    if (node == nullptr) {
        return;
    }

    ImGui::TreeNode(node->node_type().data());
    ImGui::TreePop();
}

auto BehaviorTreeDrawable::node_display_name(
    const yasf::BehaviorTree::Node* node) -> const char*
{
    if (node == nullptr) {
        return "null";
    }

    // const auto type = node->node_type();
    // const auto name = node->name();
    // if (type.empty()) {
    //     return name.data();
    // }
    //
    // return std::string{name.data()} + " (" + type.data() + ")";

    return "hello";
}
