#pragma once

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event.hpp"
#include "yasf/object.hpp"
#include "yasf/simulation.hpp"

namespace yasf
{

class event_processor : public object
{
public:
    event_processor()
        : object("event_processor")
    {
    }

    virtual auto on_event(event* evt) -> void;

    auto get_simulation() const -> simulation*;

    auto get_clock() const -> clock*;

    auto get_entity_service() const -> entity_service*;

protected:
    explicit event_processor(std::string name)
        : object{std::move(name)}
    {
    }

private:
};

}  // namespace yasf
