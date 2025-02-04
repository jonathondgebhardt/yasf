#include <cstddef>
#include <memory>

#include "yasf/event_processor_service.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/event.hpp"
#include "yasf/event_processor.hpp"
#include "yasf/simulation.hpp"
#include "yasf/types.hpp"

TEST_CASE("event_processor_service: name is processor_service",
          "[event_processor_service]")
{
    auto const psvc = yasf::event_processor_service{};
    CHECK(psvc.name() == "event_processor_service");
}

TEST_CASE("event_processor_service: simulation getters",
          "[event_processor_service]")
{
    auto sim = yasf::simulation{std::make_unique<yasf::clock>()};

    REQUIRE(sim.add_child<yasf::event_processor_service>());
    auto* const psvc = sim.get_child<yasf::event_processor_service>();
    REQUIRE(psvc != nullptr);

    SECTION("get_simulation")
    {
        CHECK(psvc->get_simulation() != nullptr);
    }

    SECTION("get_clock")
    {
        CHECK(psvc->get_clock() != nullptr);
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_CASE("event_processor_service: update", "[event_processor_service]")
{
    struct test_processor : public yasf::event_processor
    {
        void on_event([[maybe_unused]] const yasf::event* evt) override
        {
            m_visited = true;
            ++m_visited_count;
        }

        bool m_visited{};
        std::size_t m_visited_count{};
    };

    auto sim = yasf::simulation{std::make_unique<yasf::clock>()};

    REQUIRE(sim.add_child<yasf::event_processor_service>());
    auto* const psvc = sim.get_child<yasf::event_processor_service>();
    REQUIRE(psvc != nullptr);

    REQUIRE(psvc->add_child<test_processor>());
    auto* const proc = psvc->get_child<test_processor>();
    REQUIRE(proc != nullptr);

    REQUIRE(!proc->m_visited);
    REQUIRE(proc->m_visited_count == std::size_t{0});

    auto const evt = yasf::event{yasf::time_microseconds{},
                                 yasf::event_type::simulation_start};
    REQUIRE_NOTHROW(proc->on_event(&evt));

    CHECK(proc->m_visited);
    CHECK(proc->m_visited_count == std::size_t{1});
}

// NOLINTEND(readability-function-cognitive-complexity)
