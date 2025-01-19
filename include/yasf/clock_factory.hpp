#pragma once

#include <memory>

#include "yasf/clock.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT clock_factory
{
public:
    static auto build_fixed_update(time_sec delta) -> std::unique_ptr<clock>;
    static auto build_fixed_update(time_usec delta) -> std::unique_ptr<clock>;
};

}  // namespace yasf
