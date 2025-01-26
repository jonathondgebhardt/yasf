#pragma once

#include "yasf/yasf_export.hpp"

// TODO:
// - make templated versions?
// - add a "deep" option?

namespace yasf
{

template<typename T>
class YASF_EXPORT visitor
{
public:
    visitor() = default;
    visitor(const visitor&) = default;
    visitor(visitor&&) noexcept = default;
    virtual ~visitor() = default;
    auto operator=(const visitor&) -> visitor& = default;
    auto operator=(visitor&&) noexcept -> visitor& = default;

    virtual auto visit(T*) -> void = 0;
};

class object;
using object_visitor = visitor<object>;

class component;
using component_visitor = visitor<component>;

}  // namespace yasf
