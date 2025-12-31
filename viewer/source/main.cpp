#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "scene_manager.hpp"
#include "yasf/acceleration.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/entity_factory.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/external_time_updater.hpp"
#include "yasf/math.hpp"
#include "yasf/mover.hpp"
#include "yasf/object.hpp"
#include "yasf/position.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/simulation.hpp"
#include "yasf/vec3d.hpp"
#include "yasf/velocity.hpp"

namespace
{

struct GroundCollisionProcessor : yasf::Processor
{
    struct FindGroundObjectVisitor : yasf::ObjectVisitor
    {
        auto visit(yasf::Object* obj) -> void override
        {
            if (obj != nullptr && obj->display_name() == "ground") {
                ground = obj;
            }
        }

        yasf::Object* ground{};
    };

    struct DetectCollisionsVisitor : yasf::ObjectVisitor
    {
        static auto overlap(const yasf::Vec3d lhs, const yasf::Vec3d rhs)
            -> bool
        {
            // return yasf::math::double_eq(lhs.x(), rhs.x())
            //     || yasf::math::double_eq(lhs.y(), rhs.y());
            return lhs.y() >= rhs.y();
        }

        auto visit(yasf::Object* obj) -> void override
        {
            if (obj == nullptr || obj == collider) {
                return;
            }

            auto* const pos_collidee = obj->get_component<yasf::Position>();
            if (pos_collidee == nullptr) {
                return;
            }

            auto* const pos_collider =
                collider->get_component<yasf::Position>();
            if (pos_collider == nullptr) {
                return;
            }

            if (overlap(pos_collidee->get(), pos_collider->get())) {
                collidees.push_back(obj);
            }
        }

        yasf::Object* collider{};
        std::vector<yasf::Object*> collidees;
    };

    auto update() -> void override
    {
        auto ground_visitor = FindGroundObjectVisitor{};
        get_simulation()->accept(ground_visitor);
        auto* const ground = ground_visitor.ground;
        yasf::Ensure(ground != nullptr, "failed to find ground object");

        auto collision_visitor = DetectCollisionsVisitor{};
        collision_visitor.collider = ground;
        get_entity_service()->accept(collision_visitor);

        std::ranges::for_each(
            collision_visitor.collidees,
            [](yasf::Object* const obj)
            {
                if (auto* vel = obj->get_component<yasf::Velocity>()) {
                    vel->get().zero();
                }
                if (auto* acc = obj->get_component<yasf::Acceleration>()) {
                    acc->get().zero();
                }
            });
    }
};

auto make_ground_object() -> std::unique_ptr<yasf::Object>
{
    auto obj = std::make_unique<yasf::Object>();
    obj->add_component<yasf::Position>(0.0, 500.0, 0.0);
    obj->set_display_name("ground");

    return obj;
}

auto make_sim() -> yasf::Simulation
{
    auto sim = yasf::Simulation{yasf::ClockFactory::build_external_update()};

    {
        auto svc = std::make_unique<yasf::EntityService>();

        // ball
        auto entity = yasf::EntityFactory::build();
        auto* const pos = entity->get_component<yasf::Position>();
        pos->set(yasf::Vec3d{400.0, 0.0, 0.0});
        auto* const acc = entity->get_component<yasf::Acceleration>();
        acc->set(yasf::Vec3d{0.0, 9.8, 0.0});

        svc->add_child(std::move(entity));

        // ground
        svc->add_child(make_ground_object());

        sim.add_child(std::move(svc));
    }

    {
        auto svc = std::make_unique<yasf::ProcessorService>();

        // auto mover = std::make_unique<EntityMover>();
        auto mover = std::make_unique<yasf::Mover>();
        svc->add_child(std::move(mover));

        auto ground_collision = std::make_unique<GroundCollisionProcessor>();
        svc->add_child(std::move(ground_collision));

        sim.add_child(std::move(svc));
    }

    return sim;
}

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
        circle->setFillColor(sf::Color::White);
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

struct GroundDrawable : SceneManager::Drawable
{
    explicit GroundDrawable(yasf::Object* ground)
        : SceneManager::Drawable{std::make_unique<sf::RectangleShape>()}
        , ground{ground}
    {
        const auto rect = dynamic_cast<sf::RectangleShape*>(drawable.get());
        rect->setFillColor(sf::Color::Green);
        rect->setSize({2000.0, 800.0});
    }

    auto update() -> void override { update_drawable_position(); }

    auto update_drawable_position() const -> void
    {
        const auto pos_vec = ground->get_component<yasf::Position>()->get();
        const auto vec = sf::Vector2f{static_cast<float>(pos_vec.x()),
                                      static_cast<float>(pos_vec.y())};
        const auto rect = dynamic_cast<sf::RectangleShape*>(drawable.get());
        rect->setPosition(vec);
    }

    struct EntityVisitor : yasf::ObjectVisitor
    {
        auto visit(yasf::Object* obj) -> void override
        {
            if (obj != nullptr && obj->display_name() == "ground") {
                ground = obj;
            }
        }

        yasf::Object* ground;
    };

    static void BuildDrawables(yasf::Simulation& sim, SceneManager& manager)
    {
        auto visitor = EntityVisitor{};
        sim.accept(visitor);
        yasf::Ensure(visitor.ground != nullptr, "failed to find ground object");
        manager.add_drawable(std::make_unique<GroundDrawable>(visitor.ground));
        yasf::log::info("created ground object");
    }

    yasf::Object* ground{};
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
        if (auto* const pos = obj->get_component<yasf::Position>()) {
            const auto vec = pos->get();
            ImGui::Text("position: %.2f %.2f", vec.x(), vec.y());
        }

        if (auto* const vel = obj->get_component<yasf::Velocity>()) {
            const auto vec = vel->get();
            ImGui::Text("velocity: %.2f %.2f", vec.x(), vec.y());
        }

        if (auto* const acc = obj->get_component<yasf::Acceleration>()) {
            const auto vec = acc->get();
            ImGui::Text("acceleration: %.2f %.2f", vec.x(), vec.y());
        }
    }

    yasf::Simulation* sim{};
};

}  // namespace

auto main() -> int
{
    auto sim = make_sim();

    sf::RenderWindow window(sf::VideoMode({1024, 768}), "yasf Viewer");
    if (!ImGui::SFML::Init(window)) {
        yasf::log::error("failed to initialize ImGui");
        return EXIT_FAILURE;
    }

    auto manager = SceneManager{&window};

    window.setFramerateLimit(60);

    EntityDrawable::BuildDrawables(sim, manager);
    GroundDrawable::BuildDrawables(sim, manager);
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
