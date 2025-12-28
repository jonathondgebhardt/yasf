#pragma once

#include <cstdint>
#include <limits>

#include "yasf/types.hpp"

namespace yasf
{

enum class EventType : std::uint16_t
{
    UNKNOWN = 0,
    SIMULATION_START = 1,
    SIMULATION_STOP = 2,
    USER = 1000,
    USER_END = std::numeric_limits<std::uint16_t>::max()
};

class Event
{
public:
    Event(yasf::time_microseconds time, EventType type)
        : m_time{time}
        , m_type{type}
    {
    }

    Event(const Event&) = default;
    Event(Event&&) = delete;

    virtual ~Event() = default;

    auto operator=(const Event&) -> Event& = default;
    auto operator=(Event&&) -> Event& = delete;

    auto type() const -> EventType { return m_type; }

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
    EventType m_type{};
};

}  // namespace yasf
