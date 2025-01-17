#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include "yasf/component.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT status : public component
{
public:
    enum class state : uint8_t
    {
        unknown = 0,
        startup,
        shutdown
    };

    /**
     * @brief Initializes the name field to the name of the project
     */
    status();

    status(std::string name, state start_state);

    explicit status(std::string name);

    explicit status(state start_state);

    auto get_state() const -> state;

    auto set_state(state new_state) -> void;

private:
    YASF_SUPPRESS_C4251
    state m_state{};
};

}  // namespace yasf
