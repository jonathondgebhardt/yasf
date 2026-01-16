#pragma once

#include <chrono>

namespace yasf::time
{

/**
 * @cond yasf_dev
 */
constexpr auto seconds_to_minutes = 60;
constexpr auto seconds_to_hours = seconds_to_minutes * 60;
constexpr auto seconds_to_days = seconds_to_hours * 24;

using Microseconds = std::chrono::microseconds;
using Milliseconds = std::chrono::milliseconds;
using Seconds = std::chrono::duration<double>;
using Minutes = std::chrono::duration<double, std::ratio<seconds_to_minutes>>;
using Hours = std::chrono::duration<double, std::ratio<seconds_to_hours>>;
using Days = std::chrono::duration<double, std::ratio<seconds_to_days>>;

template<typename T, typename... U>
concept is_any_of = (std::same_as<T, U> || ...);

template<typename T>
concept TimeType = is_any_of<T,
                             yasf::time::Microseconds,
                             Milliseconds,
                             Seconds,
                             Minutes,
                             Hours,
                             Days>;

}  // namespace yasf::time
