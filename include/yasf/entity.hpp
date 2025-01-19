#pragma once

#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief An object that takes part in a simulation.
 */
class YASF_EXPORT entity : public object
{
public:
    entity();

private:
    YASF_SUPPRESS_C4251
};

}  // namespace yasf
