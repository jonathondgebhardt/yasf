#include "yasf/processor.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/processor_service.hpp"

namespace yasf
{

auto processor::get_simulation() const -> simulation*
{
    auto* const service = dynamic_cast<processor_service*>(parent());
    ensure(service != nullptr, "failed to get processor_service");
    return dynamic_cast<simulation*>(service->parent());
}

auto processor::get_clock() const -> clock*
{
    auto* const service = dynamic_cast<processor_service*>(parent());
    ensure(service != nullptr, "failed to get processor_service");
    return service->get_clock();
}

auto processor::get_entity_service() const -> entity_service*
{
    auto* const sim = get_simulation();
    return sim->get_child<entity_service>();
}

}  // namespace yasf
