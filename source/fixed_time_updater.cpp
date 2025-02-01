#include "yasf/fixed_time_updater.hpp"

#include "yasf/clock.hpp"
#include "yasf/convert.hpp"
#include "yasf/ensure.hpp"
#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

fixed_time_updater::fixed_time_updater(time_microseconds delta)
    : time_updater("fixed_time_updater")
    , m_delta(delta)
{
}

fixed_time_updater::fixed_time_updater(time_seconds delta)
    : fixed_time_updater(convert::seconds_to_useconds(delta))
{
}

auto fixed_time_updater::next_time() -> time_microseconds
{
    auto const* parent_clock = dynamic_cast<clock*>(parent());
    yasf::ensure(parent_clock != nullptr,
                 "failed to get parent clock to calculate next time");
    return parent_clock->time() + m_delta;
}

auto fixed_time_updater::delta() const -> time_microseconds
{
    return m_delta;
}

auto fixed_time_updater::delta_sec() const -> time_seconds
{
    return convert::useconds_to_seconds(m_delta);
}

auto fixed_time_updater::set_delta(time_microseconds delta) -> void
{
    m_delta = delta;
}

auto fixed_time_updater::set_delta(time_seconds delta) -> void
{
    m_delta = convert::seconds_to_useconds(delta);
}

}  // namespace yasf
