#include <cstddef>
#include <memory>

#include "yasf/event_simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/event.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/external_time_updater.hpp"
#include "yasf/types.hpp"

TEST_CASE("event_simulation: name is event_simulation", "[simulation]")
{
    auto const sim = yasf::EventSimulation{std::make_unique<yasf::Clock>()};
    CHECK(sim.name() == "event_simulation");
}

TEST_CASE("event_simulation: update", "[simulation]")
{
    auto sim = yasf::EventSimulation{std::make_unique<yasf::Clock>()};

    SECTION("no events")
    {
        CHECK_NOTHROW(sim.update());
    }

    sim.queue(std::make_unique<yasf::Event>(yasf::time_microseconds{1},
                                            yasf::EventType::USER));

    SECTION("no updater")
    {
        CHECK_THROWS(sim.update());
    }

    auto* clock = sim.get_clock();
    REQUIRE(clock != nullptr);
    REQUIRE(clock->add_component<yasf::ExternalTimeUpdater>());

    SECTION("updater")
    {
        CHECK_NOTHROW(sim.update());
    }

    sim.add_child<yasf::EventProcessorService>();

    SECTION("processor_service")
    {
        CHECK_NOTHROW(sim.update());
    }
}

TEST_CASE("event_simulation: get_clock", "[simulation]")
{
    auto sim = yasf::EventSimulation{std::make_unique<yasf::Clock>()};
    CHECK(sim.get_clock() != nullptr);
}

TEST_CASE("event_simulation: has_events", "[simulation]")
{
    auto sim = yasf::EventSimulation{std::make_unique<yasf::Clock>()};

    // Insert out of order.
    sim.queue(std::make_unique<yasf::Event>(yasf::time_microseconds{0},
                                            yasf::EventType::USER));

    CHECK(sim.has_events());
}

TEST_CASE("event_simulation: num_events", "[simulation]")
{
    auto sim = yasf::EventSimulation{std::make_unique<yasf::Clock>()};

    // Insert out of order.
    sim.queue(std::make_unique<yasf::Event>(yasf::time_microseconds{0},
                                            yasf::EventType::USER));

    CHECK(sim.num_events() == std::size_t{1});
}
