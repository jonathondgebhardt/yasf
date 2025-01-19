#include "yasf/mover.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"

namespace yasf
{

auto mover::update() -> void
{
    auto* const service = get_entity_service();
    ensure(service != nullptr, "failed to get entity_service");

    // TODO: how do i know which entities to get? should they be tagged somehow?
    // also, how do i get them? visitor pattern?
    move_entity(service->get_child<entity>());
}

auto mover::move_entity(entity* entity) -> void
{
    auto* const clock = get_clock();
    yasf::ensure(clock != nullptr, "failed to access clock");

    auto* const vel = entity->get_component<yasf::velocity>();
    if (vel == nullptr || vel->get().is_zero()) {
        return;
    }

    auto* pos = entity->get_component<yasf::position>();
    if (pos == nullptr) {
        return;
    }

    auto const delta_time = clock->delta_sec();

    auto pos_vec = pos->get();
    auto const vel_vec = vel->get();
    pos_vec += vel_vec * delta_time;
    pos->set(pos_vec);
}

}  // namespace yasf
