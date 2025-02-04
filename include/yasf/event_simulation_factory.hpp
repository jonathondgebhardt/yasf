#pragma once

#include <memory>

#include "yasf/event_simulation.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT event_simulation_factory
{
public:
    static auto build() -> std::unique_ptr<event_simulation>;
};

}  // namespace yasf
