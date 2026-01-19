#include "node_drawable.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "drawable.hpp"
#include "yasf/behavior_tree.hpp"

NodeDrawable::NodeDrawable(yasf::BehaviorTree::Node* node, sf::Font font)
    : Drawable{}
    , m_rectangle{{200.0f, 100.0f}}
    , m_font{std::move(font)}
    , m_text{m_font}
    , m_node{node}
{
}

auto NodeDrawable::draw() -> void
{
    update_rectangle();
    update_text();
    center_text_in_rectangle();

    auto* const window_handle = yasf::viewer::GraphicsWindow::instance();
    window_handle->draw(m_rectangle);
    window_handle->draw(m_text);
}

auto NodeDrawable::update_rectangle() -> void
{
    m_rectangle.setFillColor(sf::Color::Blue);
    m_rectangle.setPosition({300.0f, 250.0f});
}

auto NodeDrawable::update_text() -> void
{
    m_text.setString("hello world :)");
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::White);
}

auto NodeDrawable::center_text_in_rectangle() -> void
{
    const auto text_bounds = m_text.getLocalBounds();
    const auto text_bounds_left = text_bounds.position.x;
    const auto text_bounds_top = text_bounds.position.y;
    const auto text_bounds_width = text_bounds.size.x;
    const auto text_bounds_height = text_bounds.size.y;

    m_text.setOrigin({text_bounds_left + text_bounds_width / 2.0f,
                      text_bounds_top + text_bounds_height / 2.0f});

    constexpr auto padding = 1.25f;
    const auto rectangle_size = text_bounds.size * padding;
    m_rectangle.setSize(rectangle_size);

    const auto rect_center = m_rectangle.getPosition()
        + sf::Vector2f(m_rectangle.getSize().x / 2.0f,
                       m_rectangle.getSize().y / 2.0f);
    m_text.setPosition(rect_center);
}
