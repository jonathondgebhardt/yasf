#pragma once

#include <memory>

#include "yasf/entity.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT entity_factory
{
public:
    static auto build() -> std::unique_ptr<entity>;

private:
    // TODO: hopefully i can read an entity's definition from a file or
    // something
    auto build_impl() -> std::unique_ptr<entity>;
};

}  // namespace yasf
