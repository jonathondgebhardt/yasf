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
class YASF_EXPORT external_time_updater : public time_updater
{
public:
    external_time_updater()
        : time_updater("external_time_updater")
    {
    }

    // clang-format-19 + gcc-14 doesn't like trailing return here.
    // auto next_time() override -> time_usec;
    // NOLINTBEGIN(modernize-use-trailing-return-type)

    /**
     * @brief
     * @return
     */
    time_microseconds next_time() override { return m_next_time; }

    // NOLINTEND(modernize-use-trailing-return-type)

    template<time_type T>
    auto set_next_time(T next_time) -> void
    {
        m_next_time = std::chrono::duration_cast<time_microseconds>(next_time);
    }

private:
    time_microseconds m_next_time{};
};

}  // namespace yasf
