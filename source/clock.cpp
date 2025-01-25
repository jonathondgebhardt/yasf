#include "yasf/clock.hpp"

#include "yasf/convert.hpp"
#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

clock::clock()
    : object("clock")
{
}

auto clock::tick() -> void
{
    auto* const updater = get_component<time_updater>();
    if (updater == nullptr) {
        yasf::log::error("failed to get updater");
        return;
    }

    auto const next_time = updater->next_time();
    m_delta = next_time - m_time;
    m_time = next_time;
}

auto clock::time() const -> time_usec
{
    return m_time;
}

auto clock::time_sec() const -> yasf::time_sec
{
    return convert::usec_to_sec(m_time);
}

auto clock::delta() const -> time_usec
{
    return m_delta;
}

auto clock::delta_sec() const -> yasf::time_sec
{
    return convert::usec_to_sec(m_delta);
}

}  // namespace yasf
