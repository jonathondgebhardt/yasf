#pragma once

#include "yasf/clock.hpp"
#include "yasf/event.hpp"
#include "yasf/object.hpp"
#include "yasf/simulation.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The root of all processors.
 */
class YASF_EXPORT event_processor_service : public object
{
public:
    event_processor_service()
        : object("event_processor_service")
    {
    }

    /**
     * @brief Updates all child processors.
     */
    auto on_event(event* evt) -> void;

    auto get_simulation() const -> simulation*;

    auto get_clock() const -> clock*;
};

}  // namespace yasf
