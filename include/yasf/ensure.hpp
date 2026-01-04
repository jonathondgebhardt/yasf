#pragma once

#include <stdexcept>

#include "yasf/logger.hpp"

namespace yasf
{

template<class... Args>
auto ensure(bool condition, std::format_string<Args...> msg, Args&&... args)
    -> void
{
    if (!condition) {
        yasf::log::critical(msg, std::forward<Args>(args)...);
        // throw std::runtime_error(msg, std::forward<Args>(args)...);
    }
}

}  // namespace yasf
