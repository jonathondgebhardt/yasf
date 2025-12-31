#pragma once

#include "yasf/processor.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class Clock;
class Entity;

class YASF_EXPORT Mover : public Processor
{
public:
    Mover()
        : Processor("mover")
    {
    }

    auto update() -> void override;

protected:
    explicit Mover(std::string name)
        : Processor(std::move(name))
    {
    }

private:
    auto move_entity(Entity* entity) -> void;
};

}  // namespace yasf
