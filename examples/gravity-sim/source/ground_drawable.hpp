#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "drawable.hpp"
#include "scene_manager.hpp"
#include "yasf/ensure.hpp"
#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/position.hpp"
#include "yasf/simulation.hpp"

struct GroundDrawable : yasf::viewer::SfDrawable<sf::RectangleShape>
{
    explicit GroundDrawable(yasf::Object* ground)
        : ground{ground}
    {
        m_drawable.setFillColor(sf::Color::Green);
        m_drawable.setSize({2000.0, 800.0});
    }

    auto update() -> void override
    {
        const auto pos_vec = ground->get_component<yasf::Position>()->get();
        const auto vec = sf::Vector2f{static_cast<float>(pos_vec.x()),
                                      static_cast<float>(pos_vec.y())};
        m_drawable.setPosition(vec);
    }

    struct EntityVisitor : yasf::ObjectVisitor
    {
        auto visit(yasf::Object* obj) -> void override
        {
            if (obj != nullptr && obj->display_name() == "ground") {
                ground = obj;
            }
        }

        yasf::Object* ground{};
    };

    static auto build_drawables(yasf::Simulation& sim,
                                yasf::viewer::SceneManager& manager) -> void
    {
        auto visitor = EntityVisitor{};
        sim.accept(visitor);
        yasf::Ensure(visitor.ground != nullptr, "failed to find ground object");
        manager.add_drawable(std::make_unique<GroundDrawable>(visitor.ground));
        yasf::log::info("created ground object");
    }

    yasf::Object* ground{};
};
