#include <utility>

#include "yasf/status.hpp"

#include "yasf/component.hpp"

namespace yasf
{

status::status()
    : status("status", state::unknown)
{
}

status::status(std::string name, state start_state)
    : component(std::move(name))
    , m_state(start_state)
{
}

status::status(std::string name)
    : status(std::move(name), state::unknown)
{
}

status::status(state start_state)
    : status("status", start_state)
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
