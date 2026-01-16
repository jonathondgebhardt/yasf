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

    explicit FixedTimeUpdater(Microseconds delta);
    explicit FixedTimeUpdater(Seconds delta);

    /**
     * @brief Adds delta time to the parent clock's time.
     * Throws an exception if parent is not a clock.
     * @return The delta time plus the parent clock's time.
     */
    auto next_time() -> Microseconds override;

    template<TimeType T = Microseconds>
    auto delta() const -> T
    {
        return std::chrono::duration_cast<Microseconds>(m_delta);
    }

    template<TimeType T = Microseconds>
    auto set_delta(T delta) -> void
    {
        m_delta = std::chrono::duration_cast<Microseconds>(delta);
    }

private:
    YASF_SUPPRESS_C4251
    Microseconds m_delta{};
};

}  // namespace yasf
