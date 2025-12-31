#pragma once

#include <chrono>

#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT FixedTimeUpdater : public TimeUpdater
{
public:
    FixedTimeUpdater() = delete;

    explicit FixedTimeUpdater(time_microseconds delta);
    explicit FixedTimeUpdater(time_seconds delta);

    /**
     * @brief Adds delta time to the parent clock's time.
     * Throws an exception if parent is not a clock.
     * @return The delta time plus the parent clock's time.
     */
    auto next_time() -> time_microseconds override;

    template<time_type T = time_microseconds>
    auto delta() const -> T
    {
        return std::chrono::duration_cast<time_microseconds>(m_delta);
    }

    template<time_type T = time_microseconds>
    auto set_delta(T delta) -> void
    {
        m_delta = std::chrono::duration_cast<time_microseconds>(delta);
    }

private:
    YASF_SUPPRESS_C4251
    time_microseconds m_delta{};
};

}  // namespace yasf
