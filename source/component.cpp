#include <string_view>
#include <utility>

#include "yasf/component.hpp"

#include "yasf/object.hpp"
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

auto component::name() const -> std::string_view
{
    return m_name;
}

auto component::parent() const -> object*
{
    return m_parent;
}

auto component::accept(component_visitor& visitor) -> void
{
    visitor.visit(this);
}

}  // namespace yasf
