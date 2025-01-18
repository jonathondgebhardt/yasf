#include "yasf/clock.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/convert.hpp"
#include "yasf/fixed_time_updater.hpp"
#include "yasf/math.hpp"
#include "yasf/types.hpp"

TEST_CASE("delta", "[clock]")
{
    constexpr auto one_second_delta = yasf::time_sec{1.0};

    SECTION("ctor")
    {
        auto clock = yasf::clock{one_second_delta};
        REQUIRE(yasf::math::double_eq(clock.delta(), one_second_delta));
    }

    SECTION("setter")
    {
        auto clock = yasf::clock{0};
        REQUIRE(yasf::math::double_eq(clock.delta(), 0.0));

        clock.set_delta(one_second_delta);
        REQUIRE(yasf::math::double_eq(clock.delta(), one_second_delta));
    }
}

TEST_CASE("tick: no updater", "[clock]")
{
    constexpr auto delta = 1.0;
    auto clock = yasf::clock{delta};
    REQUIRE(yasf::math::double_eq(clock.delta(), delta));

    clock.tick();
    REQUIRE(clock.time() == 0);
}

TEST_CASE("tick: one second delta", "[clock]")
{
    constexpr auto one_second_delta = yasf::time_sec{1.0};
    auto clock = yasf::clock{one_second_delta};
    REQUIRE(clock.add_component<yasf::fixed_time_updater>());

    constexpr auto iterations = 10;
    for (auto i = 0; i < iterations; ++i) {
        clock.tick();
        REQUIRE(clock.time() == yasf::convert::sec_to_usec(i + 1));
    }
}

TEST_CASE("tick: change delta", "[clock]")
{
    constexpr auto one_second_delta = yasf::time_sec{1.0};
    auto clock = yasf::clock{one_second_delta};
    REQUIRE(clock.add_component<yasf::fixed_time_updater>());

    clock.tick();
    REQUIRE(clock.time() == yasf::convert::sec_to_usec(one_second_delta));

    constexpr auto two_second_delta = yasf::time_sec{2.0};
    clock.set_delta(two_second_delta);
    auto const offset = clock.time();

    clock.tick();
    REQUIRE(clock.time()
            == offset + yasf::convert::sec_to_usec(two_second_delta));
}
