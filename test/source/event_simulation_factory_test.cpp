#include <cstddef>
#include <memory>

#include "yasf/event_simulation_factory.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event.hpp"
#include "yasf/event_processor.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/event_simulation.hpp"
#include "yasf/external_time_updater.hpp"
#include "yasf/types.hpp"

TEST_CASE("simulation_event_factory: build")
{
    auto const sim = yasf::event_simulation_factory::build();
    REQUIRE(sim != nullptr);

    SECTION("has clock")
    {
        CHECK(sim->get_clock() != nullptr);
    }

    SECTION("clock has external_time_updater")
    {
        auto* const clock = sim->get_clock();
        REQUIRE(clock != nullptr);
        CHECK(clock->get_component<yasf::external_time_updater>());
    }

    SECTION("has event_processor_service")
    {
        CHECK(sim->get_child<yasf::event_processor_service>() != nullptr);
    }

    SECTION("has entity_service")
    {
        CHECK(sim->get_child<yasf::entity_service>() != nullptr);
    }
}

// NOLINTBEGIN (readability-function-cognitive-complexity)
TEST_CASE("event_simulation: queue", "[simulation]")
{
    struct concrete_processor : public yasf::event_processor
    {
        void on_event(const yasf::event* evt) override
        {
            m_event_time = evt->time();
            m_clock_time = get_clock()->time();
        }

        yasf::time_microseconds m_event_time{};
        yasf::time_microseconds m_clock_time{};
    };

    auto sim = yasf::event_simulation_factory::build();
    REQUIRE(sim != nullptr);

    // Add a concrete processor so we can monitor simulation time.
    auto* psvc = sim->get_child<yasf::event_processor_service>();
    REQUIRE(psvc != nullptr);
    REQUIRE(psvc->add_child<concrete_processor>());
    auto* const processor = psvc->get_child<concrete_processor>();

    // Insert out of order.
    sim->queue(std::make_unique<yasf::event>(yasf::time_microseconds{0},
                                             yasf::event_type::user));
    sim->queue(std::make_unique<yasf::event>(yasf::time_microseconds{2},
                                             yasf::event_type::user));
    sim->queue(std::make_unique<yasf::event>(yasf::time_microseconds{1},
                                             yasf::event_type::user));

    REQUIRE(sim->num_events() == std::size_t{3});

    // TODO: add a benchmark

    REQUIRE_NOTHROW(sim->update());
    CHECK(processor->m_event_time == yasf::time_microseconds{0});
    CHECK(processor->m_clock_time == yasf::time_microseconds{0});
    CHECK(sim->num_events() == std::size_t{2});

    REQUIRE_NOTHROW(sim->update());
    CHECK(processor->m_event_time == yasf::time_microseconds{1});
    CHECK(processor->m_clock_time == yasf::time_microseconds{1});
    CHECK(sim->num_events() == std::size_t{1});

    REQUIRE_NOTHROW(sim->update());
    CHECK(processor->m_event_time == yasf::time_microseconds{2});
    CHECK(processor->m_clock_time == yasf::time_microseconds{2});
    CHECK(!sim->has_events());
}

// NOLINTEND (readability-function-cognitive-complexity)
