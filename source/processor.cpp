#include "yasf/processor.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/simulation.hpp"

namespace yasf
{

auto Processor::get_simulation() const -> Simulation*
{
    auto* const service = dynamic_cast<ProcessorService*>(parent());
    Ensure(service != nullptr, "failed to get processor_service");
    return dynamic_cast<Simulation*>(service->parent());
}

auto Processor::get_clock() const -> Clock*
{
    auto* const service = dynamic_cast<ProcessorService*>(parent());
    Ensure(service != nullptr, "failed to get processor_service");
    return service->get_clock();
}

auto Processor::get_entity_service() const -> EntityService*
{
    auto* const sim = get_simulation();
    return sim->get_child<EntityService>();
}

}  // namespace yasf
