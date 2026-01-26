#pragma once

#include "drawable.hpp"
#include "yasf/behavior_tree.hpp"
#include "yasf/composite_node.hpp"
#include "yasf/decorator_node.hpp"
#include "yasf/leaf_node.hpp"

class BehaviorTreeDrawable : public yasf::viewer::Drawable
{
public:
    explicit BehaviorTreeDrawable(yasf::BehaviorTree* tree)
        : m_tree{tree}
    {
    }

    auto draw() -> void override;

private:
    // static auto draw_node(yasf::CompositeNode* node) -> void;
    // static auto draw_node(yasf::DecoratorNode* node) -> void;
    // static auto draw_node(yasf::LeafNode* node) -> void;

    static auto draw_node_helper(const yasf::BehaviorTree::Node* node) -> void;
    static auto draw_composite_node(const yasf::CompositeNode* node) -> void;
    static auto draw_decorator_node(const yasf::DecoratorNode* node) -> void;
    static auto draw_leaf_node(const yasf::LeafNode* node) -> void;

    static auto node_display_name(const yasf::BehaviorTree::Node* node) -> const
        char*;

    yasf::BehaviorTree* m_tree{};
};
