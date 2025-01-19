#include "yasf/mover.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/object.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"

namespace yasf
{

auto mover::process() -> void
{
    if (m_root == nullptr) {
        return;
    }

    auto* pos = m_root->get_component<yasf::position>();
    if (pos == nullptr) {
        return;
    }

    auto* const vel = m_root->get_component<yasf::velocity>();
    if (vel == nullptr) {
        return;
    }

    yasf::ensure(m_clock != nullptr, "failed to access clock");
    auto const delta_time = m_clock->delta_sec();

    auto pos_vec = pos->get();
    auto const vel_vec = vel->get();
    pos_vec += vel_vec * delta_time;
    pos->set(pos_vec);
}

}  // namespace yasf
