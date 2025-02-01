#include "yasf/convert.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/types.hpp"

TEST_CASE("seconds_to_useconds", "[convert]")
{
    SECTION("zero seconds")
    {
        CHECK(yasf::convert::seconds_to_useconds(yasf::time_seconds{0.0})
              == yasf::time_microseconds{0});
    }

    SECTION("one second")
    {
        CHECK(yasf::convert::seconds_to_useconds(yasf::time_seconds{1.0})
              == yasf::time_microseconds{1000000});
    }

    SECTION("one and a half seconds")
    {
        CHECK(yasf::convert::seconds_to_useconds(
                  yasf::time_seconds{1.5})  // NOLINT
              == yasf::time_microseconds{1500000});
    }
}

TEST_CASE("useconds_to_seconds", "[convert]")
{
    SECTION("zero seconds")
    {
        CHECK(yasf::convert::useconds_to_seconds(yasf::time_microseconds{0})
              == yasf::time_seconds{0.0});
    }

    SECTION("one second")
    {
        CHECK(
            yasf::convert::useconds_to_seconds(yasf::time_microseconds{1000000})
            == yasf::time_seconds{1.0});
    }
}

TEST_CASE("minutes_to_seconds", "[convert]")
{
    SECTION("one minute")
    {
        CHECK(yasf::convert::minutes_to_seconds(yasf::time_minutes{1.0})
              == yasf::time_seconds{60.0});  // NOLINT
    }

    SECTION("one and a half minutes")
    {
        CHECK(yasf::convert::minutes_to_seconds(
                  yasf::time_minutes{1.5})  // NOLINT
              == yasf::time_seconds{90.0});  // NOLINT
    }
}

TEST_CASE("seconds_to_minutes", "[convert]")
{
    SECTION("one minute")
    {
        CHECK(yasf::convert::seconds_to_minutes(
                  yasf::time_seconds{60.0})  // NOLINT
              == yasf::time_minutes{1.0});
    }

    SECTION("one and a half minutes")
    {
        CHECK(yasf::convert::seconds_to_minutes(
                  yasf::time_seconds{90.0})  // NOLINT
              == yasf::time_minutes{1.5});  // NOLINT
    }
}

TEST_CASE("hours_to_minutes", "[convert]")
{
    SECTION("one hour")
    {
        CHECK(yasf::convert::hours_to_minutes(yasf::time_hours{1.0})
              == yasf::time_minutes{60.0});  // NOLINT
    }

    SECTION("one and a half hours")
    {
        CHECK(yasf::convert::hours_to_minutes(yasf::time_hours{1.5})  // NOLINT
              == yasf::time_minutes{90.0});
    }
}

TEST_CASE("minutes_to_hours", "[convert]")
{
    SECTION("one hour")
    {
        CHECK(
            yasf::convert::minutes_to_hours(yasf::time_minutes{60.0})  // NOLINT
            == yasf::time_hours{1.0});
    }

    SECTION("one and a half hours")
    {
        CHECK(
            yasf::convert::minutes_to_hours(yasf::time_minutes{90.0})  // NOLINT
            == yasf::time_hours{1.5});  // NOLINT
    }
}

TEST_CASE("days_to_hours", "[convert]")
{
    SECTION("one day")
    {
        CHECK(yasf::convert::days_to_hours(yasf::time_days{1.0})
              == yasf::time_hours{24.0});  // NOLINT
    }

    SECTION("one and a half days")
    {
        CHECK(yasf::convert::days_to_hours(yasf::time_days{1.5})  // NOLINT
              == yasf::time_hours{36.0});  // NOLINT
    }
}

TEST_CASE("hours_to_days", "[convert]")
{
    SECTION("one day")
    {
        CHECK(yasf::convert::hours_to_days(yasf::time_hours{24.0})  // NOLINT
              == yasf::time_days{1.0});
    }

    SECTION("one and a half days")
    {
        CHECK(yasf::convert::hours_to_days(yasf::time_hours{36.0})  // NOLINT
              == yasf::time_days{1.5});  // NOLINT
    }
}
