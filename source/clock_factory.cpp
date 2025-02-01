#include <memory>

#include "yasf/clock.hpp"

#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/fixed_time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

auto clock_factory::build_fixed_update(time_seconds delta)
    -> std::unique_ptr<clock>
{
    return build_fixed_update(convert::seconds_to_useconds(delta));
}

auto clock_factory::build_fixed_update(time_microseconds delta)
    -> std::unique_ptr<clock>
{
    auto obj = std::make_unique<clock>();
    obj->add_component<fixed_time_updater>(delta);
    return obj;
}

}  // namespace yasf
