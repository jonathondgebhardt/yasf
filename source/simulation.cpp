#include <memory>
#include <utility>

#include "yasf/simulation.hpp"

#include "yasf/clock.hpp"
#include "yasf/object.hpp"

namespace yasf
{

simulation::simulation(std::unique_ptr<clock> clock)
    : object("simulation")
    , m_clock(std::move(clock))
{
}

}  // namespace yasf
