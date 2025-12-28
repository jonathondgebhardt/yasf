#pragma once

#include "yasf/yasf_export.hpp"

// TODO:
// - make templated versions?
// - add a "deep" option?

namespace yasf
{

class Object;

class YASF_EXPORT ObjectVisitor
{
public:
    ObjectVisitor() = default;
    ObjectVisitor(const ObjectVisitor&) = default;
    ObjectVisitor(ObjectVisitor&&) noexcept = default;
    virtual ~ObjectVisitor() = default;
    auto operator=(const ObjectVisitor&) -> ObjectVisitor& = default;
    auto operator=(ObjectVisitor&&) noexcept -> ObjectVisitor& = default;

    virtual auto visit(Object*) -> void = 0;
};

class Component;

class YASF_EXPORT ComponentVisitor
{
public:
    ComponentVisitor() = default;
    ComponentVisitor(const ComponentVisitor&) = default;
    ComponentVisitor(ComponentVisitor&&) noexcept = default;
    virtual ~ComponentVisitor() = default;
    auto operator=(const ComponentVisitor&) -> ComponentVisitor& = default;
    auto operator=(ComponentVisitor&&) noexcept -> ComponentVisitor& = default;

    virtual auto visit(Component*) -> void = 0;
};

}  // namespace yasf
