#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "scene_manager.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/entity_factory.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/mover.hpp"
#include "yasf/position.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/simulation.hpp"
#include "yasf/vec3d.hpp"
#include "yasf/velocity.hpp"

namespace
{

struct EntityMover : yasf::Mover
{
    using Bounds = std::pair<double, double>;

    struct BorderPatrol : yasf::ObjectVisitor
    {
        auto within_x_bounds(yasf::Position& pos) const -> bool
        {
            const auto vec = pos.get();
            return vec.x() >= x_bounds.first && vec.x() < x_bounds.second;
        }

        auto within_y_bounds(yasf::Position& pos) const -> bool
        {
            const auto vec = pos.get();
            return vec.y() >= y_bounds.first && vec.y() < y_bounds.second;
        }

        auto visit(yasf::Object* obj) -> void override
        {
            if (obj == nullptr) {
                return;
            }

            const auto entity = dynamic_cast<yasf::Entity*>(obj);
            if (entity == nullptr) {
                return;
            }

            const auto pos = entity->get_component<yasf::Position>();
            yasf::Ensure(pos != nullptr, "failed to get entity position");

            const auto vel = entity->get_component<yasf::Velocity>();
            yasf::Ensure(vel != nullptr, "failed to get entity velocity");

            if (!within_x_bounds(*pos)) {
                vel->get().x() *= -1.0;
            }

            if (!within_y_bounds(*pos)) {
                vel->get().y() *= -1.0;
            }
        }

        // todo: don't hardcode this
        Bounds x_bounds = {0.0, 800.0};
        Bounds y_bounds = {0.0, 600.0};
    };

    auto update() -> void override
    {
        yasf::Mover::update();

        const auto svc = get_entity_service();
        yasf::Ensure(svc != nullptr, "failed to get entity service");

        svc->accept(visitor);
    }

    BorderPatrol visitor;
};

auto make_sim(const std::size_t num_entities) -> yasf::Simulation
{
    // todo: can i use a different time updater?
    auto sim = yasf::Simulation{yasf::ClockFactory::build_fixed_update(
        yasf::time_seconds{0.01667})};  // approx 60 times a second

    {
        auto svc = std::make_unique<yasf::EntityService>();

        const unsigned int seed =
            std::chrono::system_clock::now().time_since_epoch().count();

        auto eng = std::mt19937{seed};

        auto pos_dist = std::uniform_real_distribution{10.0, 500.0};
        auto vel_dist = std::uniform_real_distribution{-300.0, 300.0};

        for (auto i = 0u; i < num_entities; ++i) {
            auto entity = yasf::EntityFactory::build();
            const auto vel = entity->get_component<yasf::Velocity>();
            const auto vel_component = vel_dist(eng);
            vel->set(yasf::Vec3d{vel_component, vel_component, 0.0});

            const auto pos = entity->get_component<yasf::Position>();
            pos->set(yasf::Vec3d{pos_dist(eng), pos_dist(eng), 0.0});

            svc->add_child(std::move(entity));
        }

        sim.add_child(std::move(svc));
    }

    {
        auto svc = std::make_unique<yasf::ProcessorService>();

        auto mover = std::make_unique<EntityMover>();
        svc->add_child(std::move(mover));

        sim.add_child(std::move(svc));
    }

    return sim;
}

struct SimulationTimeDrawable : SceneManager::Drawable
{
    explicit SimulationTimeDrawable(yasf::Clock* clock)
        : clock{clock}
    {
        auto text = std::make_unique<sf::Text>(font);
        text->setFillColor(sf::Color::Red);
        text->setPosition({400.0, 300.0});
        drawable = std::move(text);
    }

    [[nodiscard]] auto clock_time_to_time_string() const -> std::string
    {
        const auto seconds = yasf::convert::useconds_to_seconds(clock->time());
        const auto hms = std::chrono::hh_mm_ss{seconds};
        std::ostringstream oss;
        oss << hms;
        return oss.str();
    }

    auto update() -> void override
    {
        const auto text = dynamic_cast<sf::Text*>(drawable.get());
        text->setString(clock_time_to_time_string());
    }

    yasf::Clock* clock{};
    sf::Font font{"arial.ttf"};
};

struct EntityDrawable : SceneManager::Drawable
{
    EntityDrawable(yasf::Entity* entity)
        : SceneManager::Drawable{std::make_unique<sf::CircleShape>(10.0f)}
        , entity{entity}
    {
        const auto circle = dynamic_cast<sf::CircleShape*>(drawable.get());
        circle->setFillColor(sf::Color::Green);
        circle->setOutlineThickness(2.f);
        circle->setOutlineColor(sf::Color::White);

        // Center the circle (origin is top-left by default)
        circle->setOrigin({10.0f, 10.0f});
    }

    auto update() -> void override
    {
        const auto pos_vec = entity->get_component<yasf::Position>()->get();
        const auto vec = sf::Vector2f{static_cast<float>(pos_vec.x()),
                                      static_cast<float>(pos_vec.y())};
        const auto circle = dynamic_cast<sf::CircleShape*>(drawable.get());
        circle->setPosition(vec);
    }

    struct EntityVisitor : yasf::ObjectVisitor
    {
        auto visit(yasf::Object* obj) -> void override
        {
            if (obj == nullptr) {
                return;
            }

            const auto entity = dynamic_cast<yasf::Entity*>(obj);
            if (entity == nullptr) {
                return;
            }

            entities.push_back(entity);
        }

        std::vector<yasf::Entity*> entities;
    };

    static void BuildDrawables(yasf::Simulation& sim, SceneManager& manager)
    {
        auto visitor = EntityVisitor{};
        sim.accept(visitor);
        std::ranges::for_each(
            visitor.entities,
            [&](const auto entity)
            {
                manager.add_drawable(std::make_unique<EntityDrawable>(entity));
            });

        yasf::log::info("created {} entity drawables", visitor.entities.size());
    }

    yasf::Entity* entity{};
};

}  // namespace

auto main() -> int
{
    auto sim = make_sim(3);

    sf::RenderWindow window(sf::VideoMode({800, 600}), "yasf Viewer");
    auto manager = SceneManager{&window};

    window.setFramerateLimit(60);

    manager.add_drawable(
        std::make_unique<SimulationTimeDrawable>(sim.get_clock()));

    EntityDrawable::BuildDrawables(sim, manager);

    yasf::log::info("starting simulation visualization");

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        while (const auto event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sim.update();

        // todo: is there a way to know time elapsed since last frame?
        window.clear();
        manager.draw();
        window.display();
    }

    yasf::log::info("simulation visualization ended");
}
