#pragma once

#include <memory>
#include <queue>

#include "yasf/clock.hpp"
#include "yasf/event.hpp"
#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The root of the simulation.
 *
 * This class owns the simulation clock, the entity_service, and the
 * processor_service.
 */
class YASF_EXPORT EventSimulation : public Object
{
public:
    explicit EventSimulation(std::unique_ptr<Clock> clock);

    auto update() -> void;

    auto get_clock() const -> Clock* { return m_clock.get(); }

    auto queue(std::unique_ptr<Event> evt) -> void;

    auto has_events() const -> bool { return !m_events.empty(); }

    auto num_events() const -> std::size_t { return m_events.size(); }

private:
    // NOTE: Potential use after move here. Top gets you a pointer to the first
    // element and pop removes the first element. If top is called before pop,
    // you'll have a dangling pointer.
    auto top() -> Event*;

    auto pop() -> void;

    YASF_SUPPRESS_C4251
    std::unique_ptr<Clock> m_clock;

    struct EventComparator
    {
        auto operator()(const std::unique_ptr<Event>& lhs,
                        const std::unique_ptr<Event>& rhs) const -> bool
        {
            return lhs->time() > rhs->time();
        }
    };

    std::priority_queue<std::unique_ptr<Event>,
                        std::vector<std::unique_ptr<Event>>,
                        EventComparator>
        m_events;
};

}  // namespace yasf
