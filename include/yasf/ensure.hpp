#pragma once

#include "yasf/exception.hpp"

namespace yasf
{

template<class... Args>
auto ensure(bool condition, std::format_string<Args...> msg, Args&&... args)
    -> void
{
    if (!condition) {
        throw Exception(msg, std::forward<Args>(args)...);
    }
}

}  // namespace yasf
