#include "yasf/fixed_time_updater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/convert.hpp"
#include "yasf/math.hpp"
#include "yasf/types.hpp"

TEST_CASE("fixed_time_updater: delta", "[time_updater]")
{
    constexpr auto delta_time_sec = yasf::time_sec{1.0};
    constexpr auto delta_time_usec = yasf::convert::sec_to_usec(delta_time_sec);

    SECTION("delta: ctor seconds")
    {
        auto const updater = yasf::fixed_time_updater{delta_time_sec};
        CHECK(updater.delta() == delta_time_usec);
        CHECK(yasf::math::double_eq(updater.delta_sec(), delta_time_sec));
    }

    SECTION("delta: ctor micro seconds")
    {
        auto const updater = yasf::fixed_time_updater{delta_time_usec};
        CHECK(updater.delta() == delta_time_usec);
        CHECK(yasf::math::double_eq(updater.delta_sec(), delta_time_sec));
    }

    SECTION("delta: setter seconds")
    {
        auto updater = yasf::fixed_time_updater{0.0};
        updater.set_delta(delta_time_sec);
        CHECK(updater.delta() == delta_time_usec);
        CHECK(yasf::math::double_eq(updater.delta_sec(), delta_time_sec));
    }

    SECTION("delta: setter seconds")
    {
        auto updater = yasf::fixed_time_updater{0.0};
        updater.set_delta(delta_time_usec);
        CHECK(updater.delta() == delta_time_usec);
        CHECK(yasf::math::double_eq(updater.delta_sec(), delta_time_sec));
    }
}

TEST_CASE("fixed_time_updater: next_time", "[time_updater]")
{
    auto updater = yasf::fixed_time_updater{1.0};
    CHECK_THROWS(updater.next_time());
}
