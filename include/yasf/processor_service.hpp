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
class YASF_EXPORT processor_service : public object
{
public:
    processor_service()
        : object("processor_service")
    {
    }

    auto get_simulation() const -> simulation*;

    auto get_clock() const -> clock*;
};

}  // namespace yasf
