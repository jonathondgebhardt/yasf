#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "drawable.hpp"
#include "yasf/entity.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"

struct EntityDrawable : yasf::viewer::SfDrawable<sf::CircleShape>
{
    explicit EntityDrawable(yasf::Entity* entity)
        : ball{entity}
        , previous_velocity{*entity->get_component<yasf::Velocity>()}
    {
        m_drawable.setRadius(ball->meta_data<float>("radius").value_or(10.0f));
        m_drawable.setFillColor(sf::Color::White);
        m_drawable.setOutlineThickness(2.f);
        m_drawable.setOutlineColor(sf::Color::White);

        // Center the circle (origin is top-left by default)
        m_drawable.setOrigin({10.0f, 10.0f});
    }

    auto update() -> void override
    {
        const auto pos_vec = ball->get_component<yasf::Position>()->get();
        const auto vec = sf::Vector2f{static_cast<float>(pos_vec.x()),
                                      static_cast<float>(pos_vec.y())};
        m_drawable.setPosition(vec);
    }

    yasf::Entity* ball{};
    yasf::Velocity previous_velocity;
};
