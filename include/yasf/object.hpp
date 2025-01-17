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
 * @brief Reports the name of the library
 */
class YASF_EXPORT object
{
public:
    /**
     * @brief Initializes the name field to the name of the project
     */
    object();
    object(const object&) = default;
    object(object&&) noexcept = default;

    virtual ~object() = default;

    auto operator=(const object&) -> object& = default;
    auto operator=(object&&) noexcept -> object& = default;

    /**
     * @brief Returns a non-owning pointer to the string stored in this class
     */
    auto name() const -> std::string_view;

    auto parent() const -> object*;

    auto add_child(std::unique_ptr<object> child) -> bool;

    template<typename T>
    auto add_child() -> bool
        requires std::is_base_of_v<object, T>
    {
        // TODO: make sure there's only one T?
        m_children.push_back(std::make_unique<T>());
        return true;
    }

    auto get_child(std::string_view name) -> object*;

    template<typename T>
    auto get_child() -> T*
        requires std::is_base_of_v<object, T>
    {
        const auto found = std::ranges::find_if(
            m_children,
            [](auto&& child)
            { return dynamic_cast<T*>(child.get()) != nullptr; });

        return found != m_children.end() ? dynamic_cast<T*>(found->get())
                                         : nullptr;
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
        const auto found = std::ranges::find_if(
            m_components,
            [](auto&& child)
            { return dynamic_cast<T*>(child.get()) != nullptr; });

        return found != m_components.end() ? dynamic_cast<T*>(found->get())
                                           : nullptr;
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
