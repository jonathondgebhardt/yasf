#include <string_view>
#include <utility>

#include "yasf/component.hpp"

#include "yasf/object.hpp"

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

}  // namespace yasf
