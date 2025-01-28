#include "yasf/convert.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/constants.hpp"
#include "yasf/math.hpp"
#include "yasf/types.hpp"

TEST_CASE("seconds_to_useconds", "[convert]")
{
    SECTION("zero seconds")
    {
        CHECK(yasf::convert::seconds_to_useconds(0.0)
              == yasf::time_useconds{0});
    }

    SECTION("one second")
    {
        CHECK(yasf::convert::seconds_to_useconds(1.0)
              == yasf::constants::seconds_to_useconds);
    }
}

TEST_CASE("useconds_to_seconds", "[convert]")
{
    SECTION("zero seconds")
    {
        CHECK(
            yasf::math::double_eq(yasf::convert::useconds_to_seconds(0), 0.0));
    }

    SECTION("one second")
    {
        CHECK(yasf::math::double_eq(yasf::convert::useconds_to_seconds(1000000),
                                    1.0));
    }
}

TEST_CASE("minutes_to_seconds", "[convert]")
{
    SECTION("one minute")
    {
        CHECK(yasf::math::double_eq(yasf::convert::minutes_to_seconds(1.0),
                                    60.0));  // NOLINT
    }

    SECTION("one and a half minutes")
    {
        CHECK(yasf::math::double_eq(
            yasf::convert::minutes_to_seconds(1.5),  // NOLINT
            90.0));  // NOLINT
    }
}

TEST_CASE("seconds_to_minutes", "[convert]")
{
    SECTION("one minute")
    {
        CHECK(yasf::math::double_eq(
            yasf::convert::seconds_to_minutes(60.0),  // NOLINT
            1.0));
    }

    SECTION("one and a half minutes")
    {
        CHECK(yasf::math::double_eq(
            yasf::convert::seconds_to_minutes(90.0),  // NOLINT
            1.5));  // NOLINT
    }
}

TEST_CASE("hours_to_minutes", "[convert]")
{
    SECTION("one hour")
    {
        CHECK(yasf::math::double_eq(yasf::convert::hours_to_minutes(1.0),
                                    60.0));  // NOLINT
    }

    SECTION("one and a half hours")
    {
        CHECK(yasf::math::double_eq(
            yasf::convert::hours_to_minutes(1.5),  // NOLINT
            90.0));  // NOLINT
    }
}

TEST_CASE("minutes_to_hours", "[convert]")
{
    SECTION("one hour")
    {
        CHECK(yasf::math::double_eq(
            yasf::convert::minutes_to_hours(60.0),  // NOLINT
            1.0));
    }

    SECTION("one and a half hours")
    {
        CHECK(yasf::math::double_eq(
            yasf::convert::minutes_to_hours(90.0),  // NOLINT
            1.5));  // NOLINT
    }
}

TEST_CASE("days_to_hours", "[convert]")
{
    SECTION("one day")
    {
        CHECK(yasf::math::double_eq(yasf::convert::days_to_hours(1.0),
                                    24.0));  // NOLINT
    }

    SECTION("one and a half days")
    {
        CHECK(
            yasf::math::double_eq(yasf::convert::days_to_hours(1.5),  // NOLINT
                                  36.0));  // NOLINT
    }
}

TEST_CASE("hours_to_days", "[convert]")
{
    SECTION("one day")
    {
        CHECK(
            yasf::math::double_eq(yasf::convert::hours_to_days(24.0),  // NOLINT
                                  1.0));  // NOLINT
    }

    SECTION("one and a half days")
    {
        CHECK(
            yasf::math::double_eq(yasf::convert::hours_to_days(36.0),  // NOLINT
                                  1.5));  // NOLINT
    }
}
