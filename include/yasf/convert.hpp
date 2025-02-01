#pragma once

#include <chrono>

#include "yasf/types.hpp"

namespace yasf::convert
{

constexpr auto seconds_to_useconds(time_seconds seconds) -> time_microseconds
{
    return std::chrono::duration_cast<time_microseconds>(seconds);
}

constexpr auto useconds_to_seconds(time_microseconds useconds) -> time_seconds
{
    return std::chrono::duration_cast<time_seconds>(useconds);
}

constexpr auto minutes_to_seconds(time_minutes minutes) -> time_seconds
{
    return std::chrono::duration_cast<time_seconds>(minutes);
}

constexpr auto seconds_to_minutes(time_seconds seconds) -> time_minutes
{
    return std::chrono::duration_cast<time_minutes>(seconds);
}

constexpr auto hours_to_minutes(time_hours hours) -> time_minutes
{
    return std::chrono::duration_cast<time_minutes>(hours);
}

constexpr auto minutes_to_hours(time_minutes minutes) -> time_hours
{
    return std::chrono::duration_cast<time_hours>(minutes);
}

constexpr auto days_to_hours(time_days days) -> time_hours
{
    return std::chrono::duration_cast<time_hours>(days);
}

constexpr auto hours_to_days(time_hours hours) -> time_days
{
    return std::chrono::duration_cast<time_days>(hours);
}

}  // namespace yasf::convert
