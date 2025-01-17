#pragma once

#include <string>
#include <string_view>

#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT component
{
public:
    /**
     * @brief Initializes the name field to the name of the project
     */
    component();

    explicit component(std::string name);

    /**
     * @brief Returns a non-owning pointer to the string stored in this class
     */
    auto name() const -> std::string_view;

    auto set_name(std::string name) -> void;

private:
    YASF_SUPPRESS_C4251
    std::string m_name;
};

}  // namespace yasf
