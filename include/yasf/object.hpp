#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "yasf/component.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The basic building block of a simulation.
 *
 * An object can have child objects and components.
 */
class YASF_EXPORT object
{
public:
    /**
     * @brief Sets name.
     */
    object();

    object(const object&) = default;
    object(object&&) noexcept = default;

    virtual ~object() = default;

    auto operator=(const object&) -> object& = default;
    auto operator=(object&&) noexcept -> object& = default;

    /**
     * @brief Returns the name of this object.
     */
    auto name() const -> std::string_view;

    /**
     * @brief Gets the parent of this object.
     * @detail If this object is not a child of another object, parent will be
     * null.
     */
    auto parent() const -> object*;

    /**
     * @brief Adds the child to this object.
     * @detail If child is null, this function returns false.
     * @detail If the child already has a parent, this function returns null.
     * @param child The child to add.
     * @return Whether the child was added.
     */
    auto add_child(std::unique_ptr<object> child) -> bool;

    template<typename T>
    auto add_child() -> bool
        requires std::is_base_of_v<object, T>
    {
        // TODO: make sure there's only one T?
        return add_child(std::make_unique<T>());
    }

    auto get_child(std::string_view name) -> object*;

    template<typename T>
    auto get_child() -> T*
        requires std::is_base_of_v<object, T>
    {
        auto& container = m_children;
        const auto found = std::ranges::find_if(
            container,
            [](auto&& child)
            { return dynamic_cast<T*>(child.get()) != nullptr; });

        return found != container.end() ? dynamic_cast<T*>(found->get())
                                        : nullptr;
    }

    auto remove_child(std::string_view name) -> bool;

    template<typename T>
    auto remove_child() -> bool
        requires std::is_base_of_v<object, T>
    {
        auto& container = m_children;
        const auto found =
            std::erase_if(container,
                          [](auto&& child)
                          { return dynamic_cast<T*>(child.get()) != nullptr; });
        return found != std::size_t{0};
    }

    auto add_component(std::unique_ptr<component> component) -> bool;

    template<typename T>
    auto add_component() -> bool
        requires std::is_base_of_v<component, T>
    {
        // TODO: make sure there's only one T?
        m_components.push_back(std::make_unique<T>());
        return true;
    }

    auto get_component(std::string_view name) const -> component*;

    template<typename T>
    auto get_component() -> T*
        requires std::is_base_of_v<component, T>
    {
        auto& container = m_components;
        const auto found = std::ranges::find_if(
            container,
            [](auto&& child)
            { return dynamic_cast<T*>(child.get()) != nullptr; });

        return found != container.end() ? dynamic_cast<T*>(found->get())
                                        : nullptr;
    }

    auto remove_component(std::string_view name) -> bool;

    template<typename T>
    auto remove_component() -> bool
        requires std::is_base_of_v<component, T>
    {
        auto& container = m_components;
        const auto found =
            std::erase_if(container,
                          [](auto&& child)
                          { return dynamic_cast<T*>(child.get()) != nullptr; });
        return found != std::size_t{0};
    }

protected:
    explicit object(std::string name);

private:
    YASF_SUPPRESS_C4251
    object* m_parent{nullptr};
    std::vector<std::unique_ptr<object>> m_children;
    std::vector<std::unique_ptr<component>> m_components;
    std::string m_name;
};

}  // namespace yasf
