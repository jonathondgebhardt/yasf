#include <memory>

#include "yasf/clock.hpp"

#include "yasf/clock_factory.hpp"
#include "yasf/fixed_time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

auto clock_factory::build_fixed_update(time_sec delta) -> std::unique_ptr<clock>
{
    auto builder = clock_factory{};
    return builder.build_fixed_update_impl(delta);
}

auto clock_factory::build_fixed_update_impl(time_sec delta)
    -> std::unique_ptr<clock>
{
    auto obj = std::make_unique<clock>(delta);
    obj->add_component<fixed_time_updater>();
    return obj;
}

}  // namespace yasf
