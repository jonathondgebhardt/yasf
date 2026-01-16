#pragma once

#include <chrono>

#include "yasf/types.hpp"

namespace yasf::convert
{

template<TimeType T, TimeType U>
constexpr auto time_cast(U time) -> T
{
    return std::chrono::duration_cast<T>(time);
}

constexpr auto seconds_to_useconds(Seconds seconds) -> Microseconds
{
    return std::chrono::duration_cast<Microseconds>(seconds);
}

constexpr auto useconds_to_seconds(Microseconds useconds) -> Seconds
{
    return std::chrono::duration_cast<Seconds>(useconds);
}

constexpr auto minutes_to_seconds(Minutes minutes) -> Seconds
{
    return std::chrono::duration_cast<Seconds>(minutes);
}

constexpr auto seconds_to_minutes(Seconds seconds) -> Minutes
{
    return std::chrono::duration_cast<Minutes>(seconds);
}

constexpr auto hours_to_minutes(Hours hours) -> Minutes
{
    return std::chrono::duration_cast<Minutes>(hours);
}

constexpr auto minutes_to_hours(Minutes minutes) -> Hours
{
    return std::chrono::duration_cast<Hours>(minutes);
}

constexpr auto days_to_hours(Days days) -> Hours
{
    return std::chrono::duration_cast<Hours>(days);
}

constexpr auto hours_to_days(Hours hours) -> Days
{
    return std::chrono::duration_cast<Days>(hours);
}

}  // namespace yasf::convert
