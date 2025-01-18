#include <cstdint>

#include "yasf/mover.hpp"

#include "yasf/object.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"

namespace yasf
{

auto mover::set_root(object* root) -> void
{
    m_root = root;
}

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

    // TODO: consider time. assume 1 second intervals for now.
    // TODO: decide on time unit. assume seconds for now.
    constexpr auto delta_time = std::uint64_t{1};

    auto pos_vec = pos->get();
    auto const vel_vec = vel->get();
    pos_vec += vel_vec * delta_time;
    pos->set(pos_vec);
}

}  // namespace yasf
