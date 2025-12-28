#include <memory>

#include "yasf/event_simulation.hpp"

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/event_simulation_factory.hpp"
#include "yasf/external_time_updater.hpp"

namespace yasf
{

auto EventSimulationFactory::build() -> std::unique_ptr<EventSimulation>
{
    auto sim = std::make_unique<EventSimulation>(std::make_unique<Clock>());
    auto* clock = sim->get_clock();
    clock->add_component<ExternalTimeUpdater>();

    sim->add_child<EventProcessorService>();
    sim->add_child<EntityService>();

    return sim;
}

}  // namespace yasf
