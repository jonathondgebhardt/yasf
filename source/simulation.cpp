#include "yasf/simulation.hpp"

namespace yasf
{

simulation::simulation(std::unique_ptr<clock> clock)
    : object("simulation")
    , m_clock(std::move(clock))
{
}

}  // namespace yasf
