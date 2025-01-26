#include <utility>

#include "yasf/component.hpp"

#include "yasf/visitor.hpp"

namespace yasf
{

component::component()
    : component("component")
{
}

component::component(std::string name)
    : m_name{std::move(name)}
{
}

auto component::accept(component_visitor& visitor) -> void
{
    visitor.visit(this);
}

}  // namespace yasf
