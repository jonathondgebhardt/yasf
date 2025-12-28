#pragma once

#include "yasf/clock.hpp"
#include "yasf/event.hpp"
#include "yasf/event_simulation.hpp"
#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The root of all processors.
 */
class YASF_EXPORT EventProcessorService : public Object
{
public:
    EventProcessorService()
        : Object("event_processor_service")
    {
    }

    /**
     * @brief Updates all child processors.
     */
    auto on_event(Event* evt) -> void;

    auto get_simulation() const -> EventSimulation*;

    auto get_clock() const -> Clock*;
};

}  // namespace yasf
