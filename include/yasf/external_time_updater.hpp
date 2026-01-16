#pragma once

#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

// TODO: should yasf have an abstraction for pumping events?
// maybe that's a different `simulation` type altogether.

/**
 * @brief Used for event-based simulations.
 */
class YASF_EXPORT ExternalTimeUpdater : public TimeUpdater
{
public:
    ExternalTimeUpdater()
        : TimeUpdater("external_time_updater")
    {
    }

    /**
     * @brief
     * @return
     */
    auto next_time() -> Microseconds override { return m_next_time; }

    template<TimeType T>
    auto set_next_time(T next_time) -> void
    {
        m_next_time = std::chrono::duration_cast<Microseconds>(next_time);
    }

private:
    Microseconds m_next_time{};
};

}  // namespace yasf
