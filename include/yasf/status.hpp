#pragma once

#include <cstdint>

#include "yasf/component.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

// TODO: should probably delete this class.
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

    explicit status(state start_state);

    auto get_state() const -> state;

    auto set_state(state new_state) -> void;

private:
    YASF_SUPPRESS_C4251
    state m_state{};
};

}  // namespace yasf
