#include "yasf/processor_service.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
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
