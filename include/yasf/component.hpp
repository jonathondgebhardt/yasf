#pragma once

#include <string>
#include <string_view>

#include "yasf/yasf_export.hpp"

namespace yasf
{

class object;

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
    component(const component&) = default;
    component(component&&) noexcept = default;

    virtual ~component() = default;

    auto operator=(const component&) -> component& = default;
    auto operator=(component&&) noexcept -> component& = default;

    /**
     * @brief Returns a non-owning pointer to the string stored in this class
     */
    auto name() const -> std::string_view;

    auto parent() const -> object*;

protected:
    explicit component(std::string name);

private:
    YASF_SUPPRESS_C4251
    std::string m_name;
    object* m_parent{};

    // Allows object to set m_parent.
    // TODO: should i just add set_parent?
    friend class object;
};

}  // namespace yasf
