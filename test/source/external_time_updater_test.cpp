#include <memory>
#include <utility>

#include "yasf/external_time_updater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/simulation.hpp"

TEST_CASE("external_time_updater: name is external_time_updater",
          "[time_updater]")
{
    auto const updater = yasf::external_time_updater{};
    CHECK(updater.name() == "external_time_updater");
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_CASE("external_time_updater: next_time", "[time_updater]")
{
    // TODO: really dislike this
    auto sim = []()
    {
        auto clock = std::make_unique<yasf::clock>();
        REQUIRE(clock->add_component<yasf::external_time_updater>());
        return yasf::simulation{std::move(clock)};
    }();

    auto* const clock = sim.get_clock();
    REQUIRE(clock != nullptr);

    auto* updater = clock->get_component<yasf::external_time_updater>();
    REQUIRE(updater != nullptr);

    REQUIRE_NOTHROW(sim.update());

    // Simulation time should have advanced with a fixed_time_updater.
    CHECK(clock->time() == 0);

    updater->set_next_time(1);
    REQUIRE_NOTHROW(sim.update());
    CHECK(clock->time() == 1);
    CHECK(clock->delta() == 1);

    // Go backwards in time.
    updater->set_next_time(0);
    REQUIRE_NOTHROW(sim.update());
    CHECK(clock->time() == 0);
}

// NOLINTEND(readability-function-cognitive-complexity)
