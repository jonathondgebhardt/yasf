#include <memory>

#include "yasf/simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/clock_factory.hpp"
#include "yasf/ensure.hpp"
#include "yasf/math.hpp"
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

    yasf::time_useconds m_update_time{};
};

TEST_CASE("simulation: name is simulation", "[simulation]")
{
    auto const sim = yasf::simulation{std::make_unique<yasf::clock>()};
    CHECK(sim.name() == "simulation");
}

TEST_CASE("simulation: zero frame", "[simulation]")
{
    constexpr auto delta_time = 1.0;
    auto sim =
        yasf::simulation{yasf::clock_factory::build_fixed_update(delta_time)};

    REQUIRE(sim.add_child<yasf::processor_service>());
    auto* psvc = sim.get_child<yasf::processor_service>();
    REQUIRE(psvc != nullptr);

    REQUIRE(psvc->add_child(std::make_unique<time_cache_processor>()));
    auto* const proc = psvc->get_child<time_cache_processor>();
    REQUIRE(proc != nullptr);

    REQUIRE_NOTHROW(sim.update());

    CHECK(proc->m_update_time == yasf::time_useconds{0});
}

TEST_CASE("simulation: update advances sim time", "[simulation]")
{
    constexpr auto delta_time = 1.0;
    auto sim =
        yasf::simulation{yasf::clock_factory::build_fixed_update(delta_time)};
    auto* const clock = sim.get_clock();

    REQUIRE_NOTHROW(sim.update());
    CHECK(yasf::math::double_eq(clock->time_sec(), delta_time));
    CHECK(yasf::math::double_eq(clock->delta_sec(), delta_time));
}
