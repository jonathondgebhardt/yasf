#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "drawable.hpp"
#include "yasf/behavior_tree.hpp"

class NodeDrawable : public yasf::viewer::Drawable
{
public:
    NodeDrawable(yasf::BehaviorTree::Node* node, sf::Font font);

    auto draw() -> void override;

private:
    auto update_rectangle() -> void;
    auto update_text() -> void;
    auto center_text_in_rectangle() -> void;

    sf::RectangleShape m_rectangle;
    sf::Font m_font;
    sf::Text m_text;

    yasf::BehaviorTree::Node* m_node{};
};
