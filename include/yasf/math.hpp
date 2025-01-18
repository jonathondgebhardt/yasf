#pragma once

#include <cmath>

namespace yasf::math
{

constexpr auto double_eq(auto lhs, auto rhs) -> bool
{
    constexpr auto epsilon = 1e-9;
    return std::abs(lhs - rhs) < epsilon;
}

constexpr auto double_ne(auto lhs, auto rhs) -> bool
{
    constexpr auto epsilon = 1e-9;
    return std::abs(lhs - rhs) > epsilon;
}

}  // namespace yasf::math
