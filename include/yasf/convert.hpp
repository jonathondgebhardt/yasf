#pragma once

#include "yasf/constants.hpp"
#include "yasf/types.hpp"

namespace yasf::convert
{

constexpr auto seconds_to_useconds(time_seconds sec) -> time_useconds
{
    return static_cast<time_useconds>(sec * constants::seconds_to_useconds);
}

constexpr auto useconds_to_seconds(time_useconds usec) -> time_seconds
{
    return static_cast<time_seconds>(usec) * constants::useconds_to_seconds;
}

}  // namespace yasf::convert
