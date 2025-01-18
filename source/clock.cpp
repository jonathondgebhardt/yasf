#include "yasf/clock.hpp"

#include "yasf/time_updater.hpp"
#include "yasf/types.hpp"

namespace yasf
{

auto clock::tick() -> void
{
    auto* const updater = get_component<time_updater>();
    if (updater == nullptr) {
        return;
    }

    // TODO: although updater doesn't care what our implementation is, there's a
    // coupling here. can i make this more generic?
    m_time = updater->next_time(m_time, m_delta);
}

}  // namespace yasf
