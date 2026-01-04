#pragma once

#include <cstdint>
#include <filesystem>
#include <format>
#include <print>
#include <source_location>

namespace yasf::log
{

// todo: shamelessly stolen from
// https://github.com/nathan-baggs/ufps/blob/main/src/utils/log.h

enum class Level : std::uint8_t
{
    DEBUG,
    INFO,
    WARN,
    ERROR,
    CRITICAL
};

template<Level L, class... Args>
struct Print
{
    explicit Print(std::format_string<Args...> msg,
                   Args&&... args,
                   std::source_location loc = std::source_location::current())
    {
        auto log_level = '?';
        if constexpr (L == Level::DEBUG) {
            log_level = 'D';
        } else if constexpr (L == Level::INFO) {
            log_level = 'I';
        } else if constexpr (L == Level::WARN) {
            log_level = 'W';
        } else if constexpr (L == Level::ERROR) {
            log_level = 'E';
        } else if constexpr (L == Level::CRITICAL) {
            log_level = '!';
        }

        const auto path = std::filesystem::path{loc.file_name()};

        auto log_line =
            std::format("[{}] {}:{} {}",
                        log_level,
                        path.filename().string(),
                        loc.line(),
                        std::format(msg, std::forward<Args>(args)...));

        std::print("{}", log_line);
    }
};

template<Level L = {}, class... Args>
Print(std::format_string<Args...>, Args&&...) -> Print<L, Args...>;

template<class... Args>
using debug = Print<Level::DEBUG, Args...>;

template<class... Args>
using info = Print<Level::INFO, Args...>;

template<class... Args>
using warn = Print<Level::WARN, Args...>;

template<class... Args>
using error = Print<Level::ERROR, Args...>;

template<class... Args>
using critical = Print<Level::CRITICAL, Args...>;

}  // namespace yasf::log
