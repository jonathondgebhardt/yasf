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
     * @return The current simulation time in the requested representation.
     */
    template<time_type T = time_microseconds>
    auto time() const -> T
    {
        return std::chrono::duration_cast<T>(m_time);
    }

    /**
     * @brief Get the amount of elapsed simulation time since the last tick.
     * @return The amount of elapsed simulation time since the last tick in
     * the requested representation.
     */
    template<time_type T = time_microseconds>
    auto delta() const -> T
    {
        return std::chrono::duration_cast<T>(m_delta);
    }

private:
    YASF_SUPPRESS_C4251
    time_microseconds m_time{};
    time_microseconds m_delta{};
};

}  // namespace yasf
