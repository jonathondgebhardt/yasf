#pragma once

#include "yasf/processor.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class clock;

class YASF_EXPORT mover : public processor
{
public:
    mover()
        : processor("mover")
    {
    }

    auto process() -> void;

private:
    clock* m_clock{};
};

}  // namespace yasf
