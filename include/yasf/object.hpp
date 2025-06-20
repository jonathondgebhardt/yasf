#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "yasf/component.hpp"
#include "yasf/uuid.hpp"
#include "yasf/visitor.hpp"
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

    object(const object&) = delete;
    object(object&&) noexcept = default;

    virtual ~object() = default;

    auto operator=(const object&) -> object& = delete;
    auto operator=(object&&) noexcept -> object& = default;

    /**
     * @brief Returns the name of this object.
     */
    auto name() const -> std::string_view { return m_name; }

    auto uuid() const -> uuid { return m_uuid; }

    /**
     * @brief Gets the parent of this object.
     * If this object is not a child of another object, parent will be null.
     */
    auto parent() const -> object* { return m_parent; }

    /**
     * @brief Adds the child to this object.
     * If child is null, this function returns false. If the child already has a
     * parent, this function returns null.
     * @param child The child to add.
     * @return Whether the child was added.
     */
    auto add_child(std::unique_ptr<object> child) -> bool;

    template<typename T, typename... Args>
    auto add_child(Args&&... args) -> bool
        requires std::is_base_of_v<object, T>
    {
        // TODO: make sure there's only one T?
        return add_child(std::make_unique<T>(std::forward<Args>(args)...));
    }

    auto get_child(std::string_view name) const -> object*;

    auto get_child(const yasf::uuid& uid) const -> object*;

    template<typename T>
    auto get_child() const -> T*
        requires std::is_base_of_v<object, T>
    {
        const auto& container = m_children;
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

    /**
     * @brief Adds the component to this object.
     * If component is null, this function returns false. If the component
     * already has a parent, this function returns null.
     * @param component The component to add.
     * @return Whether the component was added.
     */
    auto add_component(std::unique_ptr<component> component) -> bool;

    template<typename T, typename... Args>
    auto add_component(Args&&... args) -> bool
        requires std::is_base_of_v<component, T>
    {
        // TODO: make sure there's only one T?
        return add_component(std::make_unique<T>(std::forward<Args>(args)...));
    }

    auto get_component(std::string_view name) const -> component*;

    template<typename T>
    auto get_component() const -> T*
        requires std::is_base_of_v<component, T>
    {
        const auto& container = m_components;
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

    auto accept(object_visitor& visitor) -> void;
    auto accept(component_visitor& visitor) -> void;

protected:
    explicit object(std::string name);

private:
    YASF_SUPPRESS_C4251
    object* m_parent{nullptr};
    std::vector<std::unique_ptr<object>> m_children;
    std::vector<std::unique_ptr<component>> m_components;
    yasf::uuid m_uuid;
    std::string m_name;
};

}  // namespace yasf
