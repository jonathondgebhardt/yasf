#pragma once

#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT clock
{
public:
    explicit clock(time_sec delta)
        : m_delta{delta}
    {
    }

    auto tick() -> void;

    auto time() const -> time_us { return m_time; }

    auto set_delta(time_sec delta) { m_delta = delta; }

    auto delta() const -> time_sec { return m_delta; }

private:
    YASF_SUPPRESS_C4251
    time_us m_time{};
    time_sec m_delta{};
};

}  // namespace yasf
