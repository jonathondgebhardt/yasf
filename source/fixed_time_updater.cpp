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

}  // namespace yasf
