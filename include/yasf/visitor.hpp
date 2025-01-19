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
};

class component;

class YASF_EXPORT component_visitor
{
public:
    component_visitor() = default;
    component_visitor(const component_visitor&) = default;
    component_visitor(component_visitor&&) noexcept = default;
    virtual ~component_visitor() = default;
    auto operator=(const component_visitor&) -> component_visitor& = default;
    auto operator=(component_visitor&&) noexcept
        -> component_visitor& = default;

    virtual auto visit(component* comp) -> void = 0;
};

}  // namespace yasf
