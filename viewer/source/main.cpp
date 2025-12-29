#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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

        void visit(yasf::Object* obj) override
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

        Bounds x_bounds = {0.0, 800.0};
        Bounds y_bounds = {0.0, 600.0};
    };

    void update() override
    {
        yasf::Mover::update();

        const auto svc = get_entity_service();
        yasf::Ensure(svc != nullptr, "failed to get entity service");

        svc->accept(visitor);
    }

    BorderPatrol visitor;
};

auto make_sim() -> yasf::Simulation
{
    auto sim = yasf::Simulation{yasf::ClockFactory::build_fixed_update(
        yasf::time_seconds{0.01667})};  // approx 60 times a second

    {
        auto entity = yasf::EntityFactory::build();
        const auto vel = entity->get_component<yasf::Velocity>();
        yasf::Ensure(vel != nullptr, "failed to get entity velocity");
        vel->set(yasf::Vec3d{300.0, 300.0, 0.0});

        const auto pos = entity->get_component<yasf::Position>();
        yasf::Ensure(pos != nullptr, "failed to get entity position");
        pos->set(yasf::Vec3d{400.0, 300.0, 0.0});

        auto svc = std::make_unique<yasf::EntityService>();
        svc->add_child(std::move(entity));

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

struct EntityVisitor : yasf::ObjectVisitor
{
    void visit(yasf::Object* obj) override
    {
        if (obj == nullptr) {
            return;
        }

        const auto entity = dynamic_cast<yasf::Entity*>(obj);
        if (entity == nullptr) {
            return;
        }

        vec = entity->get_component<yasf::Position>()->get();
    }

    yasf::Vec3d vec;
};

}  // namespace

auto main() -> int
{
    auto sim = make_sim();

    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");

    auto visitor = EntityVisitor{};
    sim.accept(visitor);

    window.setFramerateLimit(60);

    const auto font = sf::Font{"arial.ttf"};
    auto text = sf::Text{font, "hello world :)"};
    text.setFillColor(sf::Color::Red);
    text.setPosition({400.0, 300.0});

    // 1. Create the circle shape
    sf::CircleShape circle{10.0f};  // Constructor takes radius

    // 2. Set its properties (optional but recommended)
    circle.setFillColor(sf::Color::Green);  // Set fill color
    circle.setOutlineThickness(2.f);  // Set outline thickness
    circle.setOutlineColor(sf::Color::White);  // Set outline color

    // Center the circle (origin is top-left by default)
    circle.setOrigin({10.0f, 10.0f});  // Move origin to the center

    const auto update_drawable_position = [&]
    {
        sim.accept(visitor);
        const auto pos = sf::Vector2f{static_cast<float>(visitor.vec.x()),
                                      static_cast<float>(visitor.vec.y())};
        circle.setPosition(pos);
    };

    const auto update_sim_time_label = [&]
    {
        const auto clock = sim.get_clock();
        yasf::Ensure(clock != nullptr, "failed to get clock");
        const auto seconds = yasf::convert::useconds_to_seconds(clock->time());
        const auto hms = std::chrono::hh_mm_ss{seconds};
        std::ostringstream oss;
        oss << hms;
        text.setString(oss.str());
    };

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sim.update();
        update_drawable_position();
        update_sim_time_label();

        window.clear();
        window.draw(circle);
        window.draw(text);
        window.display();
    }
}
