#pragma once

#include "yasf/yasf_export.hpp"

// TODO:
// - make templated versions?
// - add a "deep" option?

namespace yasf
{

class object;

class YASF_EXPORT object_visitor
{
public:
    object_visitor() = default;
    object_visitor(const object_visitor&) = default;
    object_visitor(object_visitor&&) noexcept = default;
    virtual ~object_visitor() = default;
    auto operator=(const object_visitor&) -> object_visitor& = default;
    auto operator=(object_visitor&&) noexcept -> object_visitor& = default;

    virtual auto visit(object* obj) -> void = 0;

private:
    YASF_SUPPRESS_C4251
};

}  // namespace yasf
