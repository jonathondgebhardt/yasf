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

    explicit FixedTimeUpdater(time::Microseconds delta);
    explicit FixedTimeUpdater(time::Seconds delta);

    /**
     * @brief Adds delta time to the parent clock's time.
     * Throws an exception if parent is not a clock.
     * @return The delta time plus the parent clock's time.
     */
    auto next_time() -> time::Microseconds override;

    template<time::TimeType T = time::Microseconds>
    auto delta() const -> T
    {
        return std::chrono::duration_cast<time::Microseconds>(m_delta);
    }

    template<time::TimeType T = time::Microseconds>
    auto set_delta(T delta) -> void
    {
        m_delta = std::chrono::duration_cast<time::Microseconds>(delta);
    }

private:
    YASF_SUPPRESS_C4251
    time::Microseconds m_delta{};
};

}  // namespace yasf
