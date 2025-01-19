#include "yasf/clock.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/fixed_time_updater.hpp"
#include "yasf/math.hpp"
#include "yasf/types.hpp"

TEST_CASE("tick: no updater", "[clock]")
{
    auto clock = yasf::clock{};
    clock.tick();
    REQUIRE(clock.time() == 0);
}

TEST_CASE("tick: one second delta fixed", "[clock]")
{
    auto clock = yasf::clock_factory::build_fixed_update(1.0);

    constexpr auto iterations = 10;
    for (auto i = 0; i < iterations; ++i) {
        clock->tick();
        REQUIRE(clock->time() == yasf::convert::sec_to_usec(i + 1));
    }
}

TEST_CASE("tick: change delta fixed", "[clock]")
{
    constexpr auto one_second_delta = yasf::time_sec{1.0};
    auto clock = yasf::clock_factory::build_fixed_update(one_second_delta);

    clock->tick();
    REQUIRE(yasf::math::double_eq(clock->time_sec(), one_second_delta));

    auto* updater = clock->get_component<yasf::fixed_time_updater>();
    REQUIRE(updater != nullptr);

    constexpr auto two_second_delta = yasf::time_sec{2.0};
    updater->set_delta(two_second_delta);

    auto const offset = clock->time_sec();

    clock->tick();
    REQUIRE(
        yasf::math::double_eq(clock->time_sec(), offset + two_second_delta));
}
