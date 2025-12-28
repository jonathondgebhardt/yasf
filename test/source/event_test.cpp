#include "yasf/event.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/types.hpp"

TEST_CASE("event: getters", "[event]")
{
    constexpr auto time = yasf::time_microseconds{1};
    constexpr auto type = yasf::EventType::SIMULATION_START;

    auto const evt = yasf::Event{time, type};
    CHECK(evt.time() == time);
    CHECK(evt.type() == type);

    SECTION("type")
    {
        constexpr auto other_time = time + time;
        auto const other =
            yasf::Event{other_time, yasf::EventType::SIMULATION_START};
        CHECK(evt < other);
        CHECK(other > evt);
    }
}
