#include <memory>
#include <utility>

#include "yasf/simulation.hpp"

#include "yasf/clock.hpp"
#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/visitor.hpp"

namespace yasf
{

Simulation::Simulation(std::unique_ptr<Clock> clock)
    : Object("simulation")
    , m_clock(std::move(clock))
{
}

auto Simulation::update() -> void
{
    // Update the clock after updating the processors. This enables a
    // "zero-frame", where processors have a chance to do something before time
    // has advanced.
    auto* const psvc = get_child<ProcessorService>();
    if (psvc != nullptr) {
        psvc->update();
    } else {
        // Not sure if running a simulation without any processors makes sense,
        // but i'll allow it.
        yasf::log::warn("updating simulation without a processor service");
    }

    m_clock->tick();
}

}  // namespace yasf
