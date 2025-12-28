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

EventSimulation::EventSimulation(std::unique_ptr<Clock> clock)
    : Object("event_simulation")
    , m_clock(std::move(clock))
{
}

auto EventSimulation::update() -> void
{
    // Get the next event to process.
    auto* const evt = top();

    if (evt == nullptr) {
        yasf::log::warn("no more events");
        return;
    }

    // Advance simulation time.
    auto* updater = m_clock->get_component<ExternalTimeUpdater>();
    yasf::Ensure(updater != nullptr, "failed to get updater");
    updater->set_next_time(evt->time());
    m_clock->tick();

    // Update the simulation.
    auto* const psvc = get_child<EventProcessorService>();
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

auto EventSimulation::queue(std::unique_ptr<Event> evt) -> void
{
    // yasf::log::info("queueing event {}: {}", evt->type(),
    // evt->time().count());
    m_events.push(std::move(evt));
}

auto EventSimulation::top() -> Event*
{
    return has_events() ? m_events.top().get() : nullptr;
}

auto EventSimulation::pop() -> void
{
    if (has_events()) {
        m_events.pop();
    }
}

}  // namespace yasf
