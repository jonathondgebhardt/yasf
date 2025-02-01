#include <cstddef>
#include <memory>

#include "yasf/processor_service.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/processor.hpp"
#include "yasf/simulation.hpp"

TEST_CASE("processor_service: name is processor_service", "[processor_service]")
{
    auto const psvc = yasf::processor_service{};
    CHECK(psvc.name() == "processor_service");
}

TEST_CASE("processor_service: simulation getters", "[processor_service]")
{
    auto sim = yasf::simulation{std::make_unique<yasf::clock>()};

    REQUIRE(sim.add_child<yasf::processor_service>());
    auto* const psvc = sim.get_child<yasf::processor_service>();
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
TEST_CASE("processor_service: update", "[processor_service]")
{
    struct test_processor : public yasf::processor
    {
        void update() override
        {
            m_visited = true;
            ++m_visited_count;
        }

        bool m_visited{};
        std::size_t m_visited_count{};
    };

    auto sim = yasf::simulation{std::make_unique<yasf::clock>()};

    REQUIRE(sim.add_child<yasf::processor_service>());
    auto* const psvc = sim.get_child<yasf::processor_service>();
    REQUIRE(psvc != nullptr);

    REQUIRE(psvc->add_child<test_processor>());
    auto* const proc = psvc->get_child<test_processor>();
    REQUIRE(proc != nullptr);

    REQUIRE(!proc->m_visited);
    REQUIRE(proc->m_visited_count == std::size_t{0});

    REQUIRE_NOTHROW(proc->update());

    CHECK(proc->m_visited);
    CHECK(proc->m_visited_count == std::size_t{1});
}

// NOLINTEND(readability-function-cognitive-complexity)
