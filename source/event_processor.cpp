#include "yasf/event_processor.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/event_simulation.hpp"

namespace yasf
{

auto event_processor::get_simulation() const -> event_simulation*
{
    auto* const service = dynamic_cast<event_processor_service*>(parent());
    ensure(service != nullptr, "failed to get processor_service");
    return dynamic_cast<event_simulation*>(service->parent());
}

auto event_processor::get_clock() const -> clock*
{
    auto* const service = dynamic_cast<event_processor_service*>(parent());
    ensure(service != nullptr, "failed to get processor_service");
    return service->get_clock();
}

auto event_processor::get_entity_service() const -> entity_service*
{
    auto* const sim = get_simulation();
    return sim->get_child<entity_service>();
}
}  // namespace yasf
