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

    explicit fixed_time_updater(time_usec delta);
    explicit fixed_time_updater(time_sec delta);

    // clang-format-19 + gcc-14 doesn't like trailing return here.
    // auto next_time() override -> time_usec;
    // NOLINTBEGIN(modernize-use-trailing-return-type)

    /**
     * @brief Adds delta time to the parent clock's time.
     * @detail Throws an exception if parent is not a clock.
     * @return The delta time plus the parent clock's time.
     */
    time_usec next_time() override;

    // NOLINTEND(modernize-use-trailing-return-type)

    auto delta() const -> time_usec;
    auto delta_sec() const -> time_sec;

    auto set_delta(time_usec delta) -> void;
    auto set_delta(time_sec delta) -> void;

private:
    YASF_SUPPRESS_C4251
    time_usec m_delta{};
};

}  // namespace yasf
