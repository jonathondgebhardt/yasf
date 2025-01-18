#include "yasf/clock.hpp"

#include "yasf/convert.hpp"

namespace yasf
{

auto clock::tick() -> void
{
    m_time += convert::sec_to_usec(m_delta);
}

}  // namespace yasf
