#include "yasf/fixed_time_updater.hpp"

#include "yasf/convert.hpp"
#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

fixed_time_updater::fixed_time_updater()
    : time_updater("fixed_time_updater")
{
}

auto fixed_time_updater::next_time(time_usec current_time, time_sec delta)
    -> time_usec
{
    return current_time + convert::sec_to_usec(delta);
}

}  // namespace yasf
