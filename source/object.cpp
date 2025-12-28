#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "yasf/object.hpp"

#include "yasf/component.hpp"
#include "yasf/uuid.hpp"
#include "yasf/visitor.hpp"

namespace yasf
{

Object::Object()
    : Object("object")
{
}

Object::Object(std::string name)
    : m_name{std::move(name)}
{
}

auto Object::add_child(std::unique_ptr<Object> child) -> bool
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

auto Object::get_child(std::string_view name) const -> Object*
{
    const auto& container = m_children;
    const auto found = std::ranges::find_if(
        container, [&](auto&& child) { return child->name() == name; });

    return found != container.end() ? found->get() : nullptr;
}

auto Object::get_child(const yasf::Uuid& uid) const -> Object*
{
    const auto& container = m_children;
    const auto found = std::ranges::find_if(
        container, [&](auto&& child) { return child->uuid() == uid; });

    return found != container.end() ? found->get() : nullptr;
}

auto Object::remove_child(std::string_view name) -> bool
{
    auto& container = m_children;
    const auto found = std::erase_if(
        container, [&](auto&& child) { return child->name() == name; });
    return found != std::size_t{0};
}

auto Object::add_component(std::unique_ptr<Component> component) -> bool
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

auto Object::get_component(std::string_view name) const -> Component*
{
    const auto& container = m_components;
    const auto found = std::ranges::find_if(
        container, [&](auto&& component) { return component->name() == name; });

    return found != container.end() ? found->get() : nullptr;
}

auto Object::remove_component(std::string_view name) -> bool
{
    auto& container = m_components;
    const auto found = std::erase_if(
        container, [&](auto&& child) { return child->name() == name; });
    return found != std::size_t{0};
}

auto Object::accept(ObjectVisitor& visitor) -> void
{
    visitor.visit(this);

    std::ranges::for_each(m_children,
                          [&](auto&& child) { child->accept(visitor); });
}

auto Object::accept(ComponentVisitor& visitor) -> void
{
    std::ranges::for_each(
        m_components, [&](auto&& component) { component->accept(visitor); });

    std::ranges::for_each(m_children,
                          [&](auto&& child) { child->accept(visitor); });
}

}  // namespace yasf
