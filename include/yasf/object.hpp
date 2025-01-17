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

    explicit object(std::string name);

    /**
     * @brief Returns a non-owning pointer to the string stored in this class
     */
    auto name() const -> std::string_view;

    auto set_name(std::string name) -> void;

    auto add_child(std::unique_ptr<object>&& child) -> bool;

    auto parent() const -> object*;

    auto get_child(std::string_view name) -> object*;

    auto add_component(std::unique_ptr<component> component) -> bool;

    auto get_component(std::string_view name) const -> component*;

private:
    YASF_SUPPRESS_C4251
    object* m_parent{nullptr};
    std::vector<std::unique_ptr<object>> m_children;
    std::vector<std::unique_ptr<component>> m_components;
    std::string m_name;
};

}  // namespace yasf
