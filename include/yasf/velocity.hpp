#pragma once

#include "yasf/component.hpp"
#include "yasf/vec3d.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT Velocity : public Component
{
public:
    /**
     * @brief Initializes the name field to the name of the project
     */
    Velocity()
        : Component{"velocity"}
    {
    }

    explicit Velocity(Vec3d vec)
        : Component("velocity")
        , m_vec{vec}
    {
    }

    auto get() const -> Vec3d { return m_vec; }

    auto set(Vec3d vec) -> void { m_vec = vec; }

private:
    YASF_SUPPRESS_C4251
    Vec3d m_vec;
};

}  // namespace yasf
