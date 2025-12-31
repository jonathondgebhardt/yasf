#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "scene_manager.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/entity_factory.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/external_time_updater.hpp"
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

    EntityMover()
        : yasf::Mover("entity mover")
    {
    }

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
    auto sim = yasf::Simulation{yasf::ClockFactory::build_external_update()};

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
        drawable = std::move(text);

        render_bin = RenderBin::OVERLAY;
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

    static auto get_random_color() -> sf::Color
    {
        const auto seed =
            std::chrono::system_clock::now().time_since_epoch().count();

        auto eng = std::mt19937{static_cast<unsigned int>(seed)};
        auto dist = std::uniform_int_distribution{0, 7};
        return color_from_index(dist(eng));
    }

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

struct ImGuiVisitor
{
    explicit ImGuiVisitor(yasf::Simulation* sim)
        : sim{sim}
    {
    }

    static auto get_id(const yasf::Object* obj) -> std::string
    {
        return std::format("{} ({})", obj->name(), obj->uuid().tail(4));
    }

    auto draw() const -> void
    {
        if (ImGui::CollapsingHeader("simulation tree")) {
            std::ranges::for_each(sim->get_children(), &draw_tree);
        }
    }

    static auto draw_tree(const yasf::Object* obj) -> void
    {
        if (ImGui::TreeNode(get_id(obj).c_str())) {
            std::ranges::for_each(obj->get_children(),
                                  [](const auto child) { draw_tree(child); });

            draw_entity_components(obj);

            ImGui::TreePop();
        }
    }

    static auto draw_entity_components(const yasf::Object* obj) -> void
    {
        // todo: handle components
        if (const auto pos = obj->get_component<yasf::Position>()) {
            const auto vec = pos->get();
            ImGui::Text("position: %.2f %.2f", vec.x(), vec.y());
        }

        if (const auto vel = obj->get_component<yasf::Velocity>()) {
            const auto vec = vel->get();
            ImGui::Text("velocity: %.2f %.2f", vec.x(), vec.y());
        }
    }

    yasf::Simulation* sim{};
};

}  // namespace

auto main() -> int
{
    auto sim = make_sim(10);

    sf::RenderWindow window(sf::VideoMode({1024, 768}), "yasf Viewer");
    if (!ImGui::SFML::Init(window)) {
        yasf::log::error("failed to initialize ImGui");
        return EXIT_FAILURE;
    }

    auto manager = SceneManager{&window};

    window.setFramerateLimit(60);

    EntityDrawable::BuildDrawables(sim, manager);
    auto visitor = ImGuiVisitor{&sim};

    const auto clock = sim.get_clock();
    const auto updater = clock->get_component<yasf::ExternalTimeUpdater>();

    yasf::log::info("starting simulation visualization");

    auto simulation_paused = false;

    // run the program as long as the window is open
    sf::Clock delta_clock;
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, event.value());

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        const auto delta_time = delta_clock.restart();
        updater->set_next_time(
            clock->time()
            + yasf::time_microseconds{delta_time.asMicroseconds()});

        ImGui::SFML::Update(window, delta_time);

        ImGui::ShowDemoWindow();

        ImGui::Begin("Simulation");
        const auto seconds = yasf::convert::useconds_to_seconds(clock->time());
        const auto hms = std::chrono::hh_mm_ss{seconds};
        std::ostringstream oss;
        oss << hms;
        ImGui::Text("time: %s", oss.str().c_str());
        ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);

        ImGui::Checkbox("pause simulation", &simulation_paused);
        if (!simulation_paused) {
            sim.update();
        }

        visitor.draw();

        ImGui::End();

        window.clear();
        manager.draw();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    yasf::log::info("simulation visualization ended");
}
