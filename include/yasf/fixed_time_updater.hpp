#pragma once

#include <chrono>

#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT fixed_time_updater : public time_updater
{
public:
    fixed_time_updater() = delete;

    explicit fixed_time_updater(time_microseconds delta);
    explicit fixed_time_updater(time_seconds delta);

    // clang-format-19 + gcc-14 doesn't like trailing return here.
    // auto next_time() override -> time_usec;
    // NOLINTBEGIN(modernize-use-trailing-return-type)

    /**
     * @brief Adds delta time to the parent clock's time.
     * Throws an exception if parent is not a clock.
     * @return The delta time plus the parent clock's time.
     */
    time_microseconds next_time() override;

    // NOLINTEND(modernize-use-trailing-return-type)

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
