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
    auto const sim = yasf::event_simulation{std::make_unique<yasf::clock>()};
    CHECK(sim.name() == "event_simulation");
}

TEST_CASE("event_simulation: update", "[simulation]")
{
    auto sim = yasf::event_simulation{std::make_unique<yasf::clock>()};

    SECTION("no events")
    {
        CHECK_NOTHROW(sim.update());
    }

    sim.queue(std::make_unique<yasf::event>(yasf::time_microseconds{1},
                                            yasf::event_type::user));

    SECTION("no updater")
    {
        CHECK_THROWS(sim.update());
    }

    auto* clock = sim.get_clock();
    REQUIRE(clock != nullptr);
    REQUIRE(clock->add_component<yasf::external_time_updater>());

    SECTION("updater")
    {
        CHECK_NOTHROW(sim.update());
    }

    sim.add_child<yasf::event_processor_service>();

    SECTION("processor_service")
    {
        CHECK_NOTHROW(sim.update());
    }
}

TEST_CASE("event_simulation: get_clock", "[simulation]")
{
    auto sim = yasf::event_simulation{std::make_unique<yasf::clock>()};
    CHECK(sim.get_clock() != nullptr);
}

TEST_CASE("event_simulation: queue", "[simulation]")
{
    auto sim = yasf::event_simulation{std::make_unique<yasf::clock>()};

    // Insert out of order.
    sim.queue(std::make_unique<yasf::event>(yasf::time_microseconds{0},
                                            yasf::event_type::user));
    sim.queue(std::make_unique<yasf::event>(yasf::time_microseconds{2},
                                            yasf::event_type::user));
    sim.queue(std::make_unique<yasf::event>(yasf::time_microseconds{1},
                                            yasf::event_type::user));

    // TODO: add a benchmark

    // TODO: top and pop are private. i'll have to build up the simulation tree
    // and create a concrete event processor to inspect events coming across.

    CHECK(sim.has_events());
}

TEST_CASE("event_simulation: has_events", "[simulation]")
{
    auto sim = yasf::event_simulation{std::make_unique<yasf::clock>()};

    // Insert out of order.
    sim.queue(std::make_unique<yasf::event>(yasf::time_microseconds{0},
                                            yasf::event_type::user));

    CHECK(sim.has_events());
}

TEST_CASE("event_simulation: num_events", "[simulation]")
{
    auto sim = yasf::event_simulation{std::make_unique<yasf::clock>()};

    // Insert out of order.
    sim.queue(std::make_unique<yasf::event>(yasf::time_microseconds{0},
                                            yasf::event_type::user));

    CHECK(sim.num_events() == std::size_t{1});
}
