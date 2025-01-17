#include <string_view>
#include <utility>

#include "yasf/component.hpp"

namespace yasf
{

component::component()
    : m_name{"component"}
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

auto component::set_name(std::string name) -> void
{
    m_name = std::move(name);
}

}  // namespace yasf
