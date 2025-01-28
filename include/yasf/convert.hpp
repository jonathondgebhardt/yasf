#pragma once

#include "yasf/constants.hpp"
#include "yasf/types.hpp"

namespace yasf::convert
{

constexpr auto seconds_to_useconds(time_seconds seconds) -> time_useconds
{
    return static_cast<time_useconds>(seconds * constants::seconds_to_useconds);
}

constexpr auto useconds_to_seconds(time_useconds useconds) -> time_seconds
{
    return static_cast<time_seconds>(useconds) * constants::useconds_to_seconds;
}

constexpr auto minutes_to_seconds(time_minutes minutes) -> time_seconds
{
    return static_cast<time_seconds>(minutes * constants::minutes_to_seconds);
}

constexpr auto seconds_to_minutes(time_seconds seconds) -> time_minutes
{
    return static_cast<time_minutes>(seconds * constants::seconds_to_minutes);
}

constexpr auto hours_to_minutes(time_hours hours) -> time_minutes
{
    return static_cast<time_minutes>(hours * constants::hours_to_minutes);
}

constexpr auto minutes_to_hours(time_minutes minutes) -> time_hours
{
    return static_cast<time_hours>(minutes * constants::minutes_to_hours);
}

constexpr auto days_to_hours(time_days days) -> time_hours
{
    return static_cast<time_hours>(days * constants::days_to_hours);
}

constexpr auto hours_to_days(time_hours hours) -> time_days
{
    return static_cast<time_days>(hours * constants::hours_to_days);
}

}  // namespace yasf::convert
