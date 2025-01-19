#pragma once

#include "yasf/object.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The simulation clock.
 * @detail Time is measured in microseconds.
 */
class YASF_EXPORT clock : public object
{
public:
    /**
     * @brief Sets name to 'clock'.
     */
    explicit clock();

    /**
     * @brief Updates the simulation time.
     * @detail How the time is updated depends on the `time_updater` component.
     */
    auto tick() -> void;

    /**
     * @brief Get the current simulation time.
     * @return The current simulation time in microseconds.
     */
    auto time() const -> time_usec;

    auto time_sec() const -> yasf::time_sec;

    /**
     * @brief Get the amount of elapsed simulation time since the last tick.
     * @return The amount of elapsed simulation time since the last tick in
     * microseconds.
     */
    auto delta() const -> time_usec;

    auto delta_sec() const -> yasf::time_sec;

private:
    YASF_SUPPRESS_C4251
    time_usec m_time{};
    time_usec m_delta{};
};

}  // namespace yasf
