#include <memory>

#include "yasf/clock.hpp"

#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/external_time_updater.hpp"
#include "yasf/fixed_time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

auto ClockFactory::build_fixed_update(time_seconds delta)
    -> std::unique_ptr<Clock>
{
    return build_fixed_update(convert::seconds_to_useconds(delta));
}

auto ClockFactory::build_fixed_update(time_microseconds delta)
    -> std::unique_ptr<Clock>
{
    auto obj = std::make_unique<Clock>();
    obj->add_component<FixedTimeUpdater>(delta);
    return obj;
}

auto ClockFactory::build_external_update() -> std::unique_ptr<Clock>
{
    auto obj = std::make_unique<Clock>();
    obj->add_component<ExternalTimeUpdater>();
    return obj;
}

}  // namespace yasf
