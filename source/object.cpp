#include <algorithm>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "yasf/object.hpp"

#include "yasf/component.hpp"

namespace yasf
{

object::object()
    : object("object")
{
}

object::object(std::string name)
    : m_name{std::move(name)}
{
}

auto object::name() const -> std::string_view
{
    return m_name;
}

auto object::add_child(std::unique_ptr<object>&& child) -> bool
{
    if (!child) {
        return false;
    }

    if (child->m_parent != nullptr) {
        return false;
    }

    child->m_parent = this;
    m_children.push_back(std::move(child));

    return true;
}

auto object::parent() const -> object*
{
    return m_parent;
}

auto object::get_child(std::string_view name) -> object*
{
    const auto found = std::ranges::find_if(
        m_children, [&](auto&& child) { return child->name() == name; });

    return found != m_children.end() ? found->get() : nullptr;
}

auto object::add_component(std::unique_ptr<component> component) -> bool
{
    if (!component) {
        return false;
    }

    m_components.push_back(std::move(component));
    return true;
}

auto object::get_component(std::string_view name) const -> component*
{
    const auto found = std::ranges::find_if(
        m_components,
        [&](auto&& component) { return component->name() == name; });

    return found != m_components.end() ? found->get() : nullptr;
}

}  // namespace yasf
