#include "yasf/event_processor.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/event_simulation.hpp"

namespace yasf
{

auto EventProcessor::get_simulation() const -> EventSimulation*
{
    auto* const service = dynamic_cast<EventProcessorService*>(parent());
    Ensure(service != nullptr, "failed to get processor_service");
    return dynamic_cast<EventSimulation*>(service->parent());
}

auto EventProcessor::get_clock() const -> Clock*
{
    auto* const service = dynamic_cast<EventProcessorService*>(parent());
    Ensure(service != nullptr, "failed to get processor_service");
    return service->get_clock();
}

auto EventProcessor::get_entity_service() const -> EntityService*
{
    auto* const sim = get_simulation();
    return sim->get_child<EntityService>();
}

}  // namespace yasf
