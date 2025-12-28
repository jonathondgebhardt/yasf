#pragma once

#include <string>
#include <string_view>

#include "yasf/uuid.hpp"
#include "yasf/visitor.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class Object;

/**
 * @brief Provides behaviors or capabilities to objects.
 *
 * For example, if an object has a position component, it can move.
 */
class YASF_EXPORT Component
{
public:
    /**
     * @brief Initializes the name of this component to 'component'.
     */
    Component();
    Component(const Component&) = default;
    Component(Component&&) noexcept = default;

    virtual ~Component() = default;

    auto operator=(const Component&) -> Component& = default;
    auto operator=(Component&&) noexcept -> Component& = default;

    /**
     * @brief Returns a view to the name of this class.
     */
    auto name() const -> std::string_view { return m_name; }

    auto uuid() const -> Uuid { return m_uuid; }

    /**
     * @brief Returns the parent.
     * If this component was not add to an object, this function will return
     * null.
     * @return The parent.
     */
    auto parent() const -> Object* { return m_parent; }

    auto accept(ComponentVisitor& visitor) -> void;

protected:
    /**
     * @brief Initializes the name of this component.
     * @name The value to set on name.
     */
    explicit Component(std::string name);

private:
    YASF_SUPPRESS_C4251
    std::string m_name;
    Object* m_parent{};
    yasf::Uuid m_uuid;

    // Allows object to set m_parent.
    // TODO: should i just add set_parent?
    friend class Object;
};

}  // namespace yasf
