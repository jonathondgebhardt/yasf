#pragma once

#include <stdexcept>

#include "yasf/exception.hpp"
#include "yasf/logger.hpp"

namespace yasf
{

template<class... Args>
auto ensure(bool condition, std::format_string<Args...> msg, Args&&... args)
    -> void
{
    if (!condition) {
        log::critical(msg, std::forward<Args>(args)...);
        throw Exception(msg, std::forward<Args>(args)...);
    }
}

}  // namespace yasf
