#include <memory>

#include "yasf/event_simulation.hpp"

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/event_simulation_factory.hpp"
#include "yasf/external_time_updater.hpp"

namespace yasf
{

auto event_simulation_factory::build() -> std::unique_ptr<event_simulation>
{
    auto sim = std::make_unique<event_simulation>(std::make_unique<clock>());
    auto* clock = sim->get_clock();
    clock->add_component<external_time_updater>();

    sim->add_child<event_processor_service>();
    sim->add_child<entity_service>();

    return sim;
}

}  // namespace yasf
