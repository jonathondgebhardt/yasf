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
