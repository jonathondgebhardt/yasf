#include "yasf/event_processor.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/simulation.hpp"

namespace yasf
{

auto event_processor::get_simulation() const -> simulation*
{
    auto* const service = dynamic_cast<processor_service*>(parent());
    ensure(service != nullptr, "failed to get processor_service");
    return dynamic_cast<simulation*>(service->parent());
}

auto event_processor::get_clock() const -> clock*
{
    auto* const service = dynamic_cast<processor_service*>(parent());
    ensure(service != nullptr, "failed to get processor_service");
    return service->get_clock();
}

auto event_processor::get_entity_service() const -> entity_service*
{
    auto* const sim = get_simulation();
    return sim->get_child<entity_service>();
}
}  // namespace yasf
