#pragma once

#include <memory>

#include "yasf/event_simulation.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT EventSimulationFactory
{
public:
    static auto build() -> std::unique_ptr<EventSimulation>;
};

}  // namespace yasf
