#pragma once

#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class fixed_time_updater : public time_updater
{
public:
    fixed_time_updater();

    // clang-format-19 + gcc-14 doesn't like trailing return here.
    // auto next_time(time_usec current_time, time_sec delta) override
    //     -> time_usec;
    // NOLINTBEGIN(modernize-use-trailing-return-type)
    time_usec next_time(time_usec current_time, time_sec delta) override;
    // NOLINTEND(modernize-use-trailing-return-type)

private:
    YASF_SUPPRESS_C4251
};

}  // namespace yasf
