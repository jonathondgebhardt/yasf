#include "yasf/fixed_time_updater.hpp"

#include "yasf/clock.hpp"
#include "yasf/convert.hpp"
#include "yasf/ensure.hpp"
#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

FixedTimeUpdater::FixedTimeUpdater(time_microseconds delta)
    : TimeUpdater("fixed_time_updater")
    , m_delta(delta)
{
}

FixedTimeUpdater::FixedTimeUpdater(time_seconds delta)
    : FixedTimeUpdater(convert::seconds_to_useconds(delta))
{
}

auto FixedTimeUpdater::next_time() -> time_microseconds
{
    auto const* parent_clock = dynamic_cast<Clock*>(parent());
    yasf::Ensure(parent_clock != nullptr,
                 "failed to get parent clock to calculate next time");
    return parent_clock->time() + m_delta;
}

}  // namespace yasf
