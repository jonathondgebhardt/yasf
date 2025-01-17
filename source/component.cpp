#include <string_view>
#include <utility>

#include "yasf/component.hpp"

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

}  // namespace yasf
