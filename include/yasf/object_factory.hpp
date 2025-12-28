#pragma once

#include <memory>

#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT ObjectFactory
{
public:
    static auto build() -> std::unique_ptr<Object>;
};

}  // namespace yasf
