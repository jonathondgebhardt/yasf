#pragma once

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/object.hpp"
#include "yasf/simulation.hpp"

namespace yasf
{

class YASF_EXPORT Processor : public Object
{
public:
    Processor()
        : Object("processor")
    {
    }

    // TODO: add m_enabled and update_impl?
    virtual auto update() -> void = 0;

    auto get_simulation() const -> Simulation*;

    auto get_clock() const -> Clock*;

    auto get_entity_service() const -> EntityService*;

protected:
    explicit Processor(std::string name)
        : Object(std::move(name))
    {
    }
};

}  // namespace yasf
