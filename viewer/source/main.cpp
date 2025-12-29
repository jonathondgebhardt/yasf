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

        const auto seed =
            std::chrono::system_clock::now().time_since_epoch().count();

        auto eng = std::mt19937{static_cast<unsigned int>(seed)};

        auto pos_dist = std::uniform_real_distribution{10.0, 500.0};
        auto vel_dist = std::uniform_real_distribution{100.0, 300.0};
        auto vel_sign_dist = std::uniform_real_distribution{0.0, 1.0};

        for (auto i = 0u; i < num_entities; ++i) {
            auto entity = yasf::EntityFactory::build();
            const auto vel = entity->get_component<yasf::Velocity>();
            const auto [vel_x, vel_y] = [&]() -> std::pair<double, double>
            {
                auto vel_x = vel_dist(eng);
                auto vel_y = vel_x;

                if (const auto sign = vel_sign_dist(eng); sign <= 0.5) {
                    vel_x *= -1.0;
                }

                if (const auto sign = vel_sign_dist(eng); sign <= 0.5) {
                    vel_y *= -1.0;
                }

                return {vel_x, vel_y};
            }();
            vel->set(yasf::Vec3d{vel_x, vel_y, 0.0});

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
    explicit EntityDrawable(yasf::Entity* entity)
        : SceneManager::Drawable{std::make_unique<sf::CircleShape>(10.0f)}
        , entity{entity}
        , previous_velocity{*entity->get_component<yasf::Velocity>()}
    {
        const auto circle = dynamic_cast<sf::CircleShape*>(drawable.get());
        circle->setFillColor(get_random_color());
        circle->setOutlineThickness(2.f);
        circle->setOutlineColor(sf::Color::White);

        // Center the circle (origin is top-left by default)
        circle->setOrigin({10.0f, 10.0f});
    }

    auto update() -> void override
    {
        update_drawable_position();
        update_drawable_color();
    }

    auto update_drawable_position() const -> void
    {
        const auto pos_vec = entity->get_component<yasf::Position>()->get();
        const auto vec = sf::Vector2f{static_cast<float>(pos_vec.x()),
                                      static_cast<float>(pos_vec.y())};
        const auto circle = dynamic_cast<sf::CircleShape*>(drawable.get());
        circle->setPosition(vec);
    }

    auto update_drawable_color() -> void
    {
        if (velocity_changed_sign()) {
            const auto circle = dynamic_cast<sf::CircleShape*>(drawable.get());
            color_index = (color_index + 1) % 8;
            circle->setFillColor(color_from_index(color_index));
        }

        previous_velocity = *entity->get_component<yasf::Velocity>();
    }

    auto velocity_changed_sign() -> bool
    {
        auto current_velocity = *entity->get_component<yasf::Velocity>();
        return (std::signbit(previous_velocity.get().x())
                != std::signbit(current_velocity.get().x()))
            || (std::signbit(previous_velocity.get().y())
                != std::signbit(current_velocity.get().y()));
    }

    static auto get_random_color() -> sf::Color
    {
        const auto seed =
            std::chrono::system_clock::now().time_since_epoch().count();

        auto eng = std::mt19937{static_cast<unsigned int>(seed)};
        auto dist = std::uniform_int_distribution{0, 7};
        return color_from_index(dist(eng));
    }

    static auto color_from_index(int index)
    {
        switch (index) {
            case 0:
                return sf::Color::Black;
            case 1:
                return sf::Color::White;
            case 2:
                return sf::Color::Red;
            case 3:
                return sf::Color::Green;
            case 4:
                return sf::Color::Blue;
            case 5:
                return sf::Color::Yellow;
            case 6:
                return sf::Color::Magenta;
            case 7:
            default:
                return sf::Color::Cyan;
        }
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
    yasf::Velocity previous_velocity{};
    int color_index{};
};

}  // namespace

auto main() -> int
{
    auto sim = make_sim(10);

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
