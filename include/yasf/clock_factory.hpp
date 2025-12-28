#pragma once

#include <memory>

#include "yasf/clock.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT ClockFactory
{
public:
    static auto build_fixed_update(time_seconds delta)
        -> std::unique_ptr<Clock>;
    static auto build_fixed_update(time_microseconds delta)
        -> std::unique_ptr<Clock>;
};

}  // namespace yasf
