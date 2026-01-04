#pragma once

#include <format>
#include <stacktrace>
#include <stdexcept>
#include <string>

namespace yasf
{

// shamelessly stolen from:
// https://github.com/nathan-baggs/ufps/blob/main/src/utils/exception.h
class Exception : public std::runtime_error
{
public:
    template<class... Args>
    explicit Exception(std::format_string<Args...> msg, Args&&... args)
        : std::runtime_error{std::format(msg, std::forward<Args>(args)...)}
        , m_what{std::format("{}\n{}",
                             std::runtime_error::what(),
                             std::stacktrace::current(1))}
    {
    }

    auto to_string() const -> std::string { return m_what; }

    auto what() const noexcept -> const char* override
    {
        return m_what.c_str();
    }

private:
    std::string m_what;
};

}  // namespace yasf
