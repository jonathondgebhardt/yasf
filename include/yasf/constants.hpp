#pragma once

namespace yasf::constants
{

constexpr auto seconds_to_useconds = 1000000;
constexpr auto useconds_to_seconds = 1.0 / seconds_to_useconds;

constexpr auto minutes_to_seconds = 60.0;
constexpr auto seconds_to_minutes = 1.0 / minutes_to_seconds;

constexpr auto hours_to_minutes = minutes_to_seconds;
constexpr auto minutes_to_hours = seconds_to_minutes;

constexpr auto days_to_hours = 24.0;
constexpr auto hours_to_days = 1.0 / days_to_hours;

}  // namespace yasf::constants
