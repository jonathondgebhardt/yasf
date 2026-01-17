#pragma once

#include <cstdint>

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
    enum class TraversalMode : std::uint8_t
    {
        NONE,
        PARENTS,
        CHILDREN
    };

    ObjectVisitor() = default;

    explicit ObjectVisitor(TraversalMode traversal_mode)
        : m_traversal_mode{traversal_mode}
    {
    }

    ObjectVisitor(const ObjectVisitor&) = default;
    ObjectVisitor(ObjectVisitor&&) noexcept = default;
    virtual ~ObjectVisitor() = default;
    auto operator=(const ObjectVisitor&) -> ObjectVisitor& = default;
    auto operator=(ObjectVisitor&&) noexcept -> ObjectVisitor& = default;

    auto traverse(Object& obj) -> void;

    virtual auto apply(Object& obj) -> void { traverse(obj); }

private:
    TraversalMode m_traversal_mode = TraversalMode::CHILDREN;
};

}  // namespace yasf
