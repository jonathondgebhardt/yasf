#include "yasf/fixed_time_updater.hpp"

#include "yasf/clock.hpp"
#include "yasf/convert.hpp"
#include "yasf/ensure.hpp"
#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

fixed_time_updater::fixed_time_updater(time_usec delta)
    : time_updater("fixed_time_updater")
    , m_delta(delta)
{
}

fixed_time_updater::fixed_time_updater(time_sec delta)
    : fixed_time_updater(convert::sec_to_usec(delta))
{
}

auto fixed_time_updater::next_time() -> time_usec
{
    auto const* parent_clock = dynamic_cast<clock*>(parent());
    yasf::ensure(parent_clock != nullptr,
                 "failed to get parent clock to calculate next time");
    return parent_clock->time() + m_delta;
}

auto fixed_time_updater::delta() const -> time_usec
{
    return m_delta;
}

auto fixed_time_updater::delta_sec() const -> time_sec
{
    return convert::usec_to_sec(m_delta);
}

auto fixed_time_updater::set_delta(time_usec delta) -> void
{
    m_delta = delta;
}

auto fixed_time_updater::set_delta(time_sec delta) -> void
{
    m_delta = convert::sec_to_usec(delta);
}

}  // namespace yasf
