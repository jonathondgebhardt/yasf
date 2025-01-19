#pragma once

#include "yasf/processor.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class clock;
class entity;

class YASF_EXPORT mover : public processor
{
public:
    mover()
        : processor("mover")
    {
    }

    auto process() -> void;

private:
    auto move_entity(entity* entity) -> void;
};

}  // namespace yasf
