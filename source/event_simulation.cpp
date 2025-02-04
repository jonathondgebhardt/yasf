#include <memory>
#include <utility>

#include "yasf/event_simulation.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/event.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/external_time_updater.hpp"
#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/visitor.hpp"

namespace yasf
{

event_simulation::event_simulation(std::unique_ptr<clock> clock)
    : object("event_simulation")
    , m_clock(std::move(clock))
{
}

auto event_simulation::update() -> void
{
    if (!has_events()) {
        yasf::log::warn("no more events");
        return;
    }

    // Get the next event to process.
    auto* const evt = top();

    // Advance simulation time.
    auto* updater = m_clock->get_component<external_time_updater>();
    yasf::ensure(updater != nullptr, "failed to get updater");
    updater->set_next_time(evt->time());
    m_clock->tick();

    // Update the simulation.
    auto* const psvc = get_child<event_processor_service>();
    if (psvc != nullptr) {
        psvc->on_event(evt);
    } else {
        // Not sure if running an event_simulation without any processors makes
        // sense, but i'll allow it.
        yasf::log::warn("updating {} without a processor service", name());
    }

    // Move to the next event.
    pop();
}

auto event_simulation::queue(std::unique_ptr<event> evt) -> void
{
    // yasf::log::info("queueing event {}: {}", evt->type(),
    // evt->time().count());
    m_events.push(std::move(evt));
}

auto event_simulation::top() -> event*
{
    return has_events() ? m_events.top().get() : nullptr;
}

auto event_simulation::pop() -> void
{
    if (has_events()) {
        m_events.pop();
    }
}

}  // namespace yasf
