#pragma once

#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class fixed_time_updater : public time_updater
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
     * @detail Throws an exception if parent is not a clock.
     * @return The delta time plus the parent clock's time.
     */
    time_microseconds next_time() override;

    // NOLINTEND(modernize-use-trailing-return-type)

    auto delta() const -> time_microseconds;
    auto delta_sec() const -> time_seconds;

    auto set_delta(time_microseconds delta) -> void;
    auto set_delta(time_seconds delta) -> void;

private:
    YASF_SUPPRESS_C4251
    time_microseconds m_delta{};
};

}  // namespace yasf
