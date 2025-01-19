#include "yasf/processor_service.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/simulation.hpp"

namespace yasf
{

auto processor_service::get_simulation() const -> simulation*
{
    return dynamic_cast<simulation*>(parent());
}

auto processor_service::get_clock() const -> clock*
{
    auto const* sim = get_simulation();
    ensure(sim != nullptr, "failed to get simulation");
    return sim->get_clock();
}

}  // namespace yasf
