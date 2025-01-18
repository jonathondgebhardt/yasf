#pragma once

#include "yasf/component.hpp"
#include "yasf/vec3d.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT velocity : public component
{
public:
    /**
     * @brief Initializes the name field to the name of the project
     */
    velocity()
        : component{"velocity"}
    {
    }

    explicit velocity(vec3d vec)
        : component("velocity")
        , m_vec{vec}
    {
    }

    auto get() const -> vec3d { return m_vec; }

    auto set(vec3d vec) -> void { m_vec = vec; }

private:
    YASF_SUPPRESS_C4251
    vec3d m_vec;
};

}  // namespace yasf
