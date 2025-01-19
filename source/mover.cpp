#include "yasf/mover.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"

namespace yasf
{

auto mover::process() -> void
{
    auto* const service = get_entity_service();
    ensure(service != nullptr, "failed to get entity_service");

    auto* const clock = get_clock();
    yasf::ensure(clock != nullptr, "failed to access clock");

    // TODO: get all entities
    // use Visitor pattern?
    auto* lentity = service->get_child<entity>();
    if (lentity == nullptr) {
        return;
    }

    auto* pos = lentity->get_component<yasf::position>();
    if (pos == nullptr) {
        return;
    }

    auto* const vel = lentity->get_component<yasf::velocity>();
    if (vel == nullptr) {
        return;
    }

    auto const delta_time = m_clock->delta_sec();

    auto pos_vec = pos->get();
    auto const vel_vec = vel->get();
    pos_vec += vel_vec * delta_time;
    pos->set(pos_vec);
}

}  // namespace yasf
