#pragma once

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event.hpp"
#include "yasf/event_simulation.hpp"
#include "yasf/object.hpp"

namespace yasf
{

class YASF_EXPORT event_processor : public object
{
public:
    event_processor()
        : object("event_processor")
    {
    }

    virtual auto on_event(const event* evt) -> void = 0;

    auto get_simulation() const -> event_simulation*;

    auto get_clock() const -> clock*;

    auto get_entity_service() const -> entity_service*;
};

}  // namespace yasf
