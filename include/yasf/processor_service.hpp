#pragma once

#include "yasf/clock.hpp"
#include "yasf/object.hpp"
#include "yasf/simulation.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The root of all processors.
 */
class YASF_EXPORT ProcessorService : public Object
{
public:
    ProcessorService()
        : Object("processor_service")
    {
    }

    /**
     * @brief Updates all child processors.
     */
    auto update() -> void;

    auto get_simulation() const -> Simulation*;

    auto get_clock() const -> Clock*;
};

}  // namespace yasf
