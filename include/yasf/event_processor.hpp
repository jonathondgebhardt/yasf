#pragma once

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event.hpp"
#include "yasf/event_simulation.hpp"
#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT EventProcessor : public Object
{
public:
    EventProcessor()
        : Object("event_processor")
    {
    }

    virtual auto on_event(const Event* evt) -> void = 0;

    auto get_simulation() const -> EventSimulation*;

    auto get_clock() const -> Clock*;

    auto get_entity_service() const -> EntityService*;
};

}  // namespace yasf
