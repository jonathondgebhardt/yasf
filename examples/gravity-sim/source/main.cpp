#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "graphics_window.hpp"
#include "scene_manager.hpp"
#include "yasf/acceleration.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/entity_factory.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/external_time_updater.hpp"
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
        yasf::ensure(ground != nullptr, "failed to find ground object");

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
        pos->get().x() = 400.0;
        auto* const vel = entity->get_component<yasf::Velocity>();
        vel->get().x() = 20.0;
        auto* const acc = entity->get_component<yasf::Acceleration>();
        acc->get().y() = 9.8;

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

struct EntityDrawable : yasf::viewer::SfDrawable<sf::CircleShape>
{
    explicit EntityDrawable(yasf::Entity* entity)
        : entity{entity}
        , previous_velocity{*entity->get_component<yasf::Velocity>()}
    {
        m_drawable.setRadius(10.0f);
        m_drawable.setFillColor(sf::Color::White);
        m_drawable.setOutlineThickness(2.f);
        m_drawable.setOutlineColor(sf::Color::White);

        // Center the circle (origin is top-left by default)
        m_drawable.setOrigin({10.0f, 10.0f});
    }

    auto update() -> void override
    {
        const auto pos_vec = entity->get_component<yasf::Position>()->get();
        const auto vec = sf::Vector2f{static_cast<float>(pos_vec.x()),
                                      static_cast<float>(pos_vec.y())};
        m_drawable.setPosition(vec);
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

    static void build_drawables(yasf::Simulation& sim,
                                yasf::viewer::SceneManager& manager)
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

        yasf::Object* ground;
    };

    static auto build_drawables(yasf::Simulation& sim,
                                yasf::viewer::SceneManager& manager) -> void
    {
        auto visitor = EntityVisitor{};
        sim.accept(visitor);
        yasf::ensure(visitor.ground != nullptr, "failed to find ground object");
        manager.add_drawable(std::make_unique<GroundDrawable>(visitor.ground));
        yasf::log::info("created ground object");
    }

    yasf::Object* ground{};
};

struct TreeDrawable : yasf::viewer::Drawable
{
    auto draw() -> void override
    {
        if (ImGui::CollapsingHeader("simulation tree")) {
            std::ranges::for_each(sim->get_children(), &draw_tree);
        }
    }

    static auto get_id(const yasf::Object* obj) -> std::string
    {
        return std::format("{} ({})", obj->name(), obj->uuid().tail(4));
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

struct SimTimeDrawable : yasf::viewer::Drawable
{
    auto get_sim_time() const -> std::string
    {
        const auto seconds = yasf::convert::useconds_to_seconds(clock->time());
        const auto hms = std::chrono::hh_mm_ss{seconds};
        std::ostringstream oss;
        oss << hms;
        return oss.str();
    }

    auto draw() -> void override
    {
        ImGui::Text("time: %s", get_sim_time().c_str());
    }

    yasf::Clock* clock;
};

struct MetricsDrawable : yasf::viewer::Drawable
{
    auto draw() -> void override
    {
        ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
    }
};

}  // namespace

auto main() -> int
{
    auto sim = make_sim();

    yasf::viewer::GraphicsWindow::init(
        {.window_width = 1024, .window_height = 768, .frame_limit = 60});
    auto* const window_handle = yasf::viewer::GraphicsWindow::instance();

    if (!ImGui::SFML::Init(*window_handle)) {
        yasf::log::error("failed to initialize ImGui");
        return EXIT_FAILURE;
    }

    auto manager = yasf::viewer::SceneManager{};

    EntityDrawable::build_drawables(sim, manager);
    GroundDrawable::build_drawables(sim, manager);

    auto* const clock = sim.get_clock();
    auto* const updater = clock->get_component<yasf::ExternalTimeUpdater>();

    auto sim_time_drawable = std::make_unique<SimTimeDrawable>();
    sim_time_drawable->clock = clock;
    manager.add_drawable(std::move(sim_time_drawable));
    manager.add_drawable(std::make_unique<MetricsDrawable>());
    auto sim_drawable = std::make_unique<TreeDrawable>();
    sim_drawable->sim = &sim;
    manager.add_drawable(std::move(sim_drawable));

    yasf::log::info("starting simulation visualization");

    auto simulation_paused = false;

    // run the program as long as the window is open
    sf::Clock delta_clock;
    while (window_handle->isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        while (const auto event = window_handle->pollEvent()) {
            ImGui::SFML::ProcessEvent(*window_handle, event.value());

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window_handle->close();
            }
        }

        const auto delta_time = delta_clock.restart();
        updater->set_next_time(
            clock->time()
            + yasf::time_microseconds{delta_time.asMicroseconds()});

        ImGui::SFML::Update(*window_handle, delta_time);

        window_handle->clear();

        ImGui::Begin("Simulation");

        ImGui::Checkbox("pause simulation", &simulation_paused);
        if (!simulation_paused) {
            sim.update();
        }

        manager.draw();
        ImGui::End();

        ImGui::SFML::Render(*window_handle);
        window_handle->display();
    }

    ImGui::SFML::Shutdown();

    yasf::log::info("simulation visualization ended");
}
