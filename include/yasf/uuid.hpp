#pragma once

#include <string>
#include <string_view>

#include "yasf/component.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT uuid : public component
{
public:
    /**
     * @brief Initializes the name field to the name of the project
     */
    uuid();

    auto get() const -> std::string_view;

private:
    YASF_SUPPRESS_C4251
    std::string m_uuid;
};

}  // namespace yasf
