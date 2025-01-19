#include <memory>
#include <utility>

#include "yasf/simulation.hpp"

#include "yasf/clock.hpp"
#include "yasf/object.hpp"
#include "yasf/processor.hpp"
#include "yasf/processor_service.hpp"

namespace yasf
{

simulation::simulation(std::unique_ptr<clock> clock)
    : object("simulation")
    , m_clock(std::move(clock))
{
}

auto simulation::update() -> void
{
    // Update the clock after updating the processors. This enables a
    // "zero-frame", where processors have a chance to do something before time
    // has advanced.
    auto* const psvc = get_child<processor_service>();
    if (psvc != nullptr) {
        // TODO: not sure if running a simulation without any processors makes
        // sense, but i'll allow it.

        // TODO: decide how to get all processors. i want to avoid allocating.
        // use visitor pattern?
        auto* proc = psvc->get_child<processor>();
        proc->update();
    }

    m_clock->tick();
}

}  // namespace yasf
