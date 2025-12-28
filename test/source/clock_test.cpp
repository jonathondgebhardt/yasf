#include "yasf/clock.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock_factory.hpp"
#include "yasf/convert.hpp"
#include "yasf/fixed_time_updater.hpp"
#include "yasf/types.hpp"

TEST_CASE("tick: no updater", "[clock]")
{
    auto clock = yasf::Clock{};
    clock.tick();
    CHECK(clock.time().count() == 0);
}

TEST_CASE("tick: one second delta fixed", "[clock]")
{
    auto clock =
        yasf::ClockFactory::build_fixed_update(yasf::time_seconds{1.0});

    constexpr auto iterations = 10;
    for (auto i = 0; i < iterations; ++i) {
        clock->tick();
        CHECK(clock->time()
              == yasf::convert::seconds_to_useconds(yasf::time_seconds{i + 1}));
    }
}

TEST_CASE("tick: change delta fixed", "[clock]")
{
    constexpr auto one_second_delta = yasf::time_seconds{1.5};
    auto clock = yasf::ClockFactory::build_fixed_update(one_second_delta);

    clock->tick();
    CHECK(clock->time() == one_second_delta);

    auto* updater = clock->get_component<yasf::FixedTimeUpdater>();
    CHECK(updater != nullptr);

    constexpr auto two_second_delta = yasf::time_seconds{2.0};
    updater->set_delta(two_second_delta);

    auto const offset = clock->time();

    clock->tick();
    CHECK(clock->time() == offset + two_second_delta);
}
