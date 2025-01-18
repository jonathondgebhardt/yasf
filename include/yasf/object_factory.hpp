#pragma once

#include <memory>

#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT object_factory
{
public:
    static auto build() -> std::unique_ptr<object>;

private:
    // TODO: hopefully i can read an object's definition from a file or
    // something
    auto build_impl() -> std::unique_ptr<object>;
};

}  // namespace yasf
