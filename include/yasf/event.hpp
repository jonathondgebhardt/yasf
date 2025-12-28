#pragma once

#include <cstdint>
#include <limits>

#include "yasf/types.hpp"

namespace yasf
{

enum class event_type : std::uint16_t
{
    unknown = 0,
    simulation_start = 1,
    simulation_stop = 2,
    user = 1000,
    user_end = std::numeric_limits<std::uint16_t>::max()
};

class Event
{
public:
    Event(yasf::time_microseconds time, event_type type)
        : m_time{time}
        , m_type{type}
    {
    }

    Event(const Event&) = default;
    Event(Event&&) = delete;

    virtual ~Event() = default;

    auto operator=(const Event&) -> Event& = default;
    auto operator=(Event&&) -> Event& = delete;

    auto type() const -> event_type { return m_type; }

    auto time() const -> time_microseconds { return m_time; }

    auto operator<(const Event& other) const -> bool
    {
        return m_time < other.m_time;
    }

    auto operator>(const Event& other) const -> bool
    {
        return m_time > other.m_time;
    }

private:
    yasf::time_microseconds m_time;
    event_type m_type{};
};

}  // namespace yasf
