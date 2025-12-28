#include <utility>

#include "yasf/component.hpp"

#include "yasf/visitor.hpp"

namespace yasf
{

Component::Component()
    : Component("component")
{
}

Component::Component(std::string name)
    : m_name{std::move(name)}
{
}

auto Component::accept(ComponentVisitor& visitor) -> void
{
    visitor.visit(this);
}

}  // namespace yasf
