#include "yasf/event.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/types.hpp"

TEST_CASE("event: getters", "[event]")
{
    constexpr auto time = yasf::time_microseconds{1};
    constexpr auto type = yasf::event_type::simulation_start;

    auto const evt = yasf::event{time, type};
    CHECK(evt.time() == time);
    CHECK(evt.type() == type);
}
