#pragma once

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/object.hpp"
#include "yasf/simulation.hpp"

namespace yasf
{

class processor : public object
{
public:
    virtual auto update() -> void = 0;

    auto get_simulation() const -> simulation*;

    auto get_clock() const -> clock*;

    auto get_entity_service() const -> entity_service*;

protected:
    explicit processor(std::string name)
        : object(std::move(name))
    {
    }
};

}  // namespace yasf
