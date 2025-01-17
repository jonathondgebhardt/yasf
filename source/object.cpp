#include <algorithm>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "yasf/object.hpp"

namespace yasf
{

object::object()
    : m_name{"object"}
{
}

auto object::name() const -> std::string_view
{
    return m_name;
}

auto object::set_name(std::string name) -> void
{
    m_name = std::move(name);
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

}  // namespace yasf
