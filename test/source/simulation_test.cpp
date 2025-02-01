#include <memory>

#include "yasf/simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/ensure.hpp"
#include "yasf/processor.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/types.hpp"

struct time_cache_processor : public yasf::processor
{
    void update() override
    {
        auto* const clock = get_clock();
        yasf::ensure(clock != nullptr, "failed to get clock");

        m_update_time = clock->time();
    }

    yasf::time_microseconds m_update_time{};
};

TEST_CASE("simulation: name is simulation", "[simulation]")
{
    auto const sim = yasf::simulation{std::make_unique<yasf::clock>()};
    CHECK(sim.name() == "simulation");
}

TEST_CASE("simulation: zero frame", "[simulation]")
{
    constexpr auto delta_time = yasf::time_seconds{1.0};
    auto sim =
        yasf::simulation{yasf::clock_factory::build_fixed_update(delta_time)};

    REQUIRE(sim.add_child<yasf::processor_service>());
    auto* psvc = sim.get_child<yasf::processor_service>();
    REQUIRE(psvc != nullptr);

    REQUIRE(psvc->add_child(std::make_unique<time_cache_processor>()));
    auto* const proc = psvc->get_child<time_cache_processor>();
    REQUIRE(proc != nullptr);

    REQUIRE_NOTHROW(sim.update());

    CHECK(proc->m_update_time == yasf::time_microseconds{0});
}

TEST_CASE("simulation: update advances sim time", "[simulation]")
{
    constexpr auto delta_time = yasf::time_seconds{1.0};
    auto sim =
        yasf::simulation{yasf::clock_factory::build_fixed_update(delta_time)};

    auto* const clock = sim.get_clock();
    REQUIRE(clock != nullptr);

    REQUIRE(clock->time_sec() == yasf::time_seconds{0.0});
    REQUIRE(clock->delta_sec() == yasf::time_seconds{0.0});

    REQUIRE_NOTHROW(sim.update());
    CHECK(clock->time_sec() == delta_time);
    CHECK(clock->delta_sec() == delta_time);
}
    auto* const clock = sim.get_clock();

    REQUIRE_NOTHROW(sim.update());
    CHECK(clock->time_sec() == delta_time);
    CHECK(clock->delta_sec() == delta_time);
}
