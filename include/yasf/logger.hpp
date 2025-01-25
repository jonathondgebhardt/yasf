#pragma once

#include <spdlog/spdlog.h>

// TODO: I don't think this is a proper encapsulation, but it works for now.
namespace yasf::log
{

template<typename... Args>
inline void info(fmt::format_string<Args...> fmt, Args&&... args)
{
    spdlog::info(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void warn(fmt::format_string<Args...> fmt, Args&&... args)
{
    spdlog::warn(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void error(fmt::format_string<Args...> fmt, Args&&... args)
{
    spdlog::error(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void critical(fmt::format_string<Args...> fmt, Args&&... args)
{
    spdlog::critical(fmt, std::forward<Args>(args)...);
}

}  // namespace yasf::log
