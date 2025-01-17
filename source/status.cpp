#include "yasf/status.hpp"

#include "yasf/component.hpp"

namespace yasf
{

status::status()
    : status(state::unknown)
{
}

status::status(state start_state)
    : component("status")
    , m_state{start_state}
{
}

auto status::get_state() const -> state
{
    return m_state;
}

auto status::set_state(state new_state) -> void
{
    m_state = new_state;
}

}  // namespace yasf
