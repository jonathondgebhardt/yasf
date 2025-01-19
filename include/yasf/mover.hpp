#pragma once

#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class clock;

class YASF_EXPORT mover
{
public:
    auto set_root(object* root) -> void { m_root = root; }

    // TODO: should probably get clock from simulation?
    auto set_clock(clock* clock) -> void { m_clock = clock; }

    auto process() -> void;

private:
    object* m_root{};
    clock* m_clock{};
};

}  // namespace yasf
