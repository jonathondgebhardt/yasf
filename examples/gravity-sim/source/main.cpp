#include <cstdlib>
#include <memory>
#include <utility>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "ball_factory.hpp"
#include "entity_drawable.hpp"
#include "graphics_window.hpp"
#include "ground_collision_processor.hpp"
#include "ground_drawable.hpp"
#include "metrics_drawable.hpp"
#include "scene_manager.hpp"
#include "sim_time_drawable.hpp"
#include "tree_drawable.hpp"
#include "yasf/acceleration.hpp"
#include "yasf/clock.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/external_time_updater.hpp"
#include "yasf/logger.hpp"
#include "yasf/mover.hpp"
#include "yasf/object.hpp"
#include "yasf/position.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/simulation.hpp"
#include "yasf/vec3d.hpp"

namespace
{

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

auto add_ball(yasf::Simulation& sim, yasf::Vec3d vec) -> yasf::Entity*
{
    auto* svc = sim.get_child<yasf::EntityService>();
    yasf::Ensure(svc != nullptr, "failed to get entity service");

    auto ball = build_ball();
    const auto uuid = ball->uuid();
    auto* pos = ball->get_component<yasf::Position>();
    pos->set(vec);
    auto* const acc = ball->get_component<yasf::Acceleration>();
    acc->get().y() = 9.8;

    svc->add_child(std::move(ball));
    yasf::log::info("ball added at x={} y={}", vec.x(), vec.y());

    // todo: not a huge fan of this
    return dynamic_cast<yasf::Entity*>(svc->get_child(uuid));
}

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

        std::optional<yasf::Vec3d> mouse_click_pos;
        while (const auto event = window_handle->pollEvent()) {
            ImGui::SFML::ProcessEvent(*window_handle, event.value());

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window_handle->close();
            } else if (const auto* mouse_clicked =
                           event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse_clicked->button == sf::Mouse::Button::Left) {
                    mouse_click_pos = yasf::Vec3d{
                        static_cast<double>(mouse_clicked->position.x),
                        static_cast<double>(mouse_clicked->position.y),
                        {}};
                }
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

        if (mouse_click_pos.has_value() && !ImGui::IsWindowHovered()) {
            auto* entity = add_ball(sim, mouse_click_pos.value());
            manager.add_drawable(std::make_unique<EntityDrawable>(entity));
        }

        manager.draw();
        ImGui::End();

        ImGui::SFML::Render(*window_handle);
        window_handle->display();
    }

    ImGui::SFML::Shutdown();

    yasf::log::info("simulation visualization ended");
}
