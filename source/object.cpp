#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "yasf/object.hpp"

#include "yasf/component.hpp"
#include "yasf/visitor.hpp"

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

auto object::parent() const -> object*
{
    return m_parent;
}

auto object::add_child(std::unique_ptr<object> child) -> bool
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

auto object::get_child(std::string_view name) const -> object*
{
    const auto& container = m_children;
    const auto found = std::ranges::find_if(
        container, [&](auto&& child) { return child->name() == name; });

    return found != container.end() ? found->get() : nullptr;
}

auto object::remove_child(std::string_view name) -> bool
{
    auto& container = m_children;
    const auto found = std::erase_if(
        container, [&](auto&& child) { return child->name() == name; });
    return found != std::size_t{0};
}

auto object::add_component(std::unique_ptr<component> component) -> bool
{
    if (!component) {
        return false;
    }

    if (component->parent() != nullptr) {
        return false;
    }

    component->m_parent = this;

    m_components.push_back(std::move(component));
    return true;
}

auto object::get_component(std::string_view name) const -> component*
{
    const auto& container = m_components;
    const auto found = std::ranges::find_if(
        container, [&](auto&& component) { return component->name() == name; });

    return found != container.end() ? found->get() : nullptr;
}

auto object::remove_component(std::string_view name) -> bool
{
    auto& container = m_components;
    const auto found = std::erase_if(
        container, [&](auto&& child) { return child->name() == name; });
    return found != std::size_t{0};

    return false;
}

auto object::accept(object_visitor& visitor) -> void
{
    visitor.visit(this);

    std::ranges::for_each(m_children,
                          [&](auto&& child) { child->accept(visitor); });
}

auto object::accept(component_visitor& visitor) -> void
{
    std::ranges::for_each(
        m_components, [&](auto&& component) { component->accept(visitor); });

    std::ranges::for_each(m_children,
                          [&](auto&& child) { child->accept(visitor); });
}

}  // namespace yasf
