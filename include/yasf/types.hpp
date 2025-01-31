#pragma once

#include <chrono>

namespace yasf
{

constexpr auto seconds_to_minutes = 60;
constexpr auto seconds_to_hours = 3600;
constexpr auto seconds_to_days = 86400;

using time_useconds = std::chrono::microseconds;
using time_milliseconds = std::chrono::milliseconds;
using time_seconds = std::chrono::duration<double>;
using time_minutes =
    std::chrono::duration<double, std::ratio<seconds_to_minutes>>;
using time_hours = std::chrono::duration<double, std::ratio<seconds_to_hours>>;
using time_days = std::chrono::duration<double, std::ratio<seconds_to_days>>;

}  // namespace yasf
