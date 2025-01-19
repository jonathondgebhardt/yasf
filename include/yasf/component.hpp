#pragma once

#include <string>
#include <string_view>

#include "yasf/uuid.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class object;
class component_visitor;

/**
 * @brief Provides behaviors or capabilities to `object`s.
 *
 * For example, if an `object` has a `position` `component`, it can move.
 */
class YASF_EXPORT component
{
public:
    /**
     * @brief Initializes the name of this component to 'component'.
     */
    component();
    component(const component&) = default;
    component(component&&) noexcept = default;

    virtual ~component() = default;

    auto operator=(const component&) -> component& = default;
    auto operator=(component&&) noexcept -> component& = default;

    /**
     * @brief Returns a view to the name of this class.
     */
    auto name() const -> std::string_view { return m_name; }

    auto uuid() const -> uuid { return m_uuid; }

    /**
     * @brief Returns the parent.
     * @detail If this `component` was not add to an `object`, this function
     * will return null.
     * @return The parent.
     */
    auto parent() const -> object* { return m_parent; }

    auto accept(component_visitor& visitor) -> void;

protected:
    /**
     * @brief Initializes the name of this component.
     * @name The value to set on name.
     */
    explicit component(std::string name);

private:
    YASF_SUPPRESS_C4251
    std::string m_name;
    object* m_parent{};
    yasf::uuid m_uuid;

    // Allows object to set m_parent.
    // TODO: should i just add set_parent?
    friend class object;
};

}  // namespace yasf
