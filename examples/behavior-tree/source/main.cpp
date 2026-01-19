#include <imgui-SFML.h>
#include <imgui.h>

#include "graphics_window.hpp"
#include "node_drawable.hpp"
#include "scene_manager.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/external_time_updater.hpp"
#include "yasf/logger.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/simulation.hpp"

namespace
{

auto make_sim() -> yasf::Simulation
{
    auto sim = yasf::Simulation{yasf::ClockFactory::build_external_update()};

    {
        auto svc = std::make_unique<yasf::EntityService>();

        // ground
        // svc->add_child(make_ground_object());

        sim.add_child(std::move(svc));
    }

    {
        auto svc = std::make_unique<yasf::ProcessorService>();

        // auto mover = std::make_unique<EntityMover>();
        // auto mover = std::make_unique<yasf::Mover>();
        // svc->add_child(std::move(mover));
        //
        // auto ground_collision = std::make_unique<GroundCollisionProcessor>();
        // svc->add_child(std::move(ground_collision));

        sim.add_child(std::move(svc));
    }

    return sim;
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

    const auto font = sf::Font{"/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"};
    auto text_box = std::make_unique<NodeDrawable>(nullptr, font);
    manager.add_drawable(std::move(text_box));

    // GroundDrawable::build_drawables(sim, manager);

    auto* const clock = sim.get_clock();
    auto* const updater = clock->get_component<yasf::ExternalTimeUpdater>();

    // auto sim_time_drawable = std::make_unique<SimTimeDrawable>();
    // sim_time_drawable->clock = clock;
    // manager.add_drawable(std::move(sim_time_drawable));
    // manager.add_drawable(std::make_unique<MetricsDrawable>());
    // auto sim_drawable = std::make_unique<TreeDrawable>();
    // sim_drawable->sim = &sim;
    // manager.add_drawable(std::move(sim_drawable));

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
            } else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                const auto rect =
                    sf::FloatRect{{0.0f, 0.0f},
                                  {static_cast<float>(resized->size.x),
                                   static_cast<float>(resized->size.y)}};
                const auto view = sf::View{rect};
                window_handle->setView(view);
            }
        }

        const auto delta_time = delta_clock.restart();

        // todo: don't update simtime with SFML frame time
        updater->set_next_time(
            clock->time()
            + yasf::time::Microseconds{delta_time.asMicroseconds()});

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
