#pragma once

#include <memory>

#include "yasf/entity.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT EntityFactory
{
public:
    static auto build() -> std::unique_ptr<Entity>;
};

}  // namespace yasf
