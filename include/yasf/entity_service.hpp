#pragma once

#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The root of all entities.
 */
class YASF_EXPORT EntityService : public Object
{
public:
    EntityService()
        : Object("entity_service")
    {
    }
};

}  // namespace yasf
