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

    // clang-format-19 + gcc-14 doesn't like trailing return here.
    // auto update() override -> void;
    // NOLINTBEGIN(modernize-use-trailing-return-type)
    void update() override;
    // NOLINTEND(modernize-use-trailing-return-type)

private:
    auto move_entity(entity* entity) -> void;
};

}  // namespace yasf
