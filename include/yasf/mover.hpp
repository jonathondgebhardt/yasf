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

    // clang-format-19 + gcc-14 doesn't like trailing return here.
    // auto update() override -> void;
    // NOLINTBEGIN(modernize-use-trailing-return-type)
    void update() override;
    // NOLINTEND(modernize-use-trailing-return-type)

protected:
    explicit Mover(std::string name)
        : Processor(std::move(name))
    {
    }

private:
    auto move_entity(Entity* entity) -> void;
};

}  // namespace yasf
