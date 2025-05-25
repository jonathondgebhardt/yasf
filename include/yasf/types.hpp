#pragma once

#include <chrono>

namespace yasf
{

/**
 * @cond yasf_dev
 */
constexpr auto seconds_to_minutes = 60;
constexpr auto seconds_to_hours = 3600;
constexpr auto seconds_to_days = 86400;

using time_microseconds = std::chrono::microseconds;
using time_milliseconds = std::chrono::milliseconds;
using time_seconds = std::chrono::duration<double>;
using time_minutes =
    std::chrono::duration<double, std::ratio<seconds_to_minutes>>;
using time_hours = std::chrono::duration<double, std::ratio<seconds_to_hours>>;
using time_days = std::chrono::duration<double, std::ratio<seconds_to_days>>;

template<typename T, typename... U>
concept is_any_of = (std::same_as<T, U> || ...);

template<typename T>
concept time_type = is_any_of<T,
                              time_microseconds,
                              time_milliseconds,
                              time_seconds,
                              time_seconds,
                              time_minutes,
                              time_hours,
                              time_days>;

}  // namespace yasf
