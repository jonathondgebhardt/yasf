#pragma once

#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The root of all entities.
 */
class YASF_EXPORT entity_service : public object
{
public:
    entity_service()
        : object("entity_service")
    {
    }
};

}  // namespace yasf
