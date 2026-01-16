#pragma once

#include <chrono>

#include "yasf/types.hpp"

namespace yasf::convert
{

template<yasf::time::TimeType T, yasf::time::TimeType U>
constexpr auto time_cast(U time) -> T
{
    return std::chrono::duration_cast<T>(time);
}

constexpr auto seconds_to_useconds(time::Seconds seconds) -> time::Microseconds
{
    return std::chrono::duration_cast<time::Microseconds>(seconds);
}

constexpr auto useconds_to_seconds(time::Microseconds useconds) -> time::Seconds
{
    return std::chrono::duration_cast<time::Seconds>(useconds);
}

constexpr auto minutes_to_seconds(time::Minutes minutes) -> time::Seconds
{
    return std::chrono::duration_cast<time::Seconds>(minutes);
}

constexpr auto seconds_to_minutes(yasf::time::Seconds seconds) -> time::Minutes
{
    return std::chrono::duration_cast<time::Minutes>(seconds);
}

constexpr auto hours_to_minutes(time::Hours hours) -> time::Minutes
{
    return std::chrono::duration_cast<time::Minutes>(hours);
}

constexpr auto minutes_to_hours(time::Minutes minutes) -> time::Hours
{
    return std::chrono::duration_cast<time::Hours>(minutes);
}

constexpr auto days_to_hours(time::Days days) -> time::Hours
{
    return std::chrono::duration_cast<time::Hours>(days);
}

constexpr auto hours_to_days(time::Hours hours) -> time::Days
{
    return std::chrono::duration_cast<time::Days>(hours);
}

}  // namespace yasf::convert
