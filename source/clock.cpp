#include "yasf/clock.hpp"

#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

clock::clock()
    : object("clock")
{
}

auto clock::tick() -> void
{
    auto* const updater = get_component<time_updater>();
    if (updater == nullptr) {
        yasf::log::error("failed to get updater");
        return;
    }

    auto const next_time = updater->next_time();

    if (next_time == m_time) {
        yasf::log::warn("time was not advanced");
    }

    if (next_time < m_time) {
        yasf::log::warn("delta time is negative");
    }

    m_delta = next_time - m_time;
    m_time = next_time;
}

}  // namespace yasf
