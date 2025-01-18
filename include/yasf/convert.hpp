#pragma once

#include "yasf/constants.hpp"
#include "yasf/types.hpp"

namespace yasf::convert
{

constexpr auto sec_to_usec(time_sec sec) -> time_us
{
    return static_cast<time_us>(sec * constants::sec_to_usec);
}

constexpr auto usec_to_sec(time_us usec) -> time_sec
{
    return static_cast<time_sec>(usec) * constants::usec_to_sec;
}

}  // namespace yasf::convert
