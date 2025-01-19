#pragma once

#include "yasf/clock.hpp"
#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief The root of the simulation.
 *
 * This class owns the simulation clock, the entity_service, and the
 * processor_service.
 */
class YASF_EXPORT simulation : public object
{
public:
    explicit simulation(std::unique_ptr<clock> clock);

    auto update() -> void;

    auto get_clock() const -> clock* { return m_clock.get(); }

private:
    YASF_SUPPRESS_C4251
    std::unique_ptr<clock> m_clock;
};

}  // namespace yasf
