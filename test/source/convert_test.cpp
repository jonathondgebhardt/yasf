#include "yasf/convert.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/types.hpp"

TEST_CASE("seconds_to_useconds", "[convert]")
{
    SECTION("zero seconds")
    {
        CHECK(yasf::convert::seconds_to_useconds(yasf::Seconds{0.0})
              == yasf::Microseconds{0});
    }

    SECTION("one second")
    {
        CHECK(yasf::convert::seconds_to_useconds(yasf::Seconds{1.0})
              == yasf::Microseconds{1000000});
    }

    SECTION("one and a half seconds")
    {
        CHECK(yasf::convert::seconds_to_useconds(yasf::Seconds{1.5})  // NOLINT
              == yasf::Microseconds{1500000});
    }
}

TEST_CASE("useconds_to_seconds", "[convert]")
{
    SECTION("zero seconds")
    {
        CHECK(yasf::convert::useconds_to_seconds(yasf::Microseconds{0})
              == yasf::Seconds{0.0});
    }

    SECTION("one second")
    {
        CHECK(yasf::convert::useconds_to_seconds(yasf::Microseconds{1000000})
              == yasf::Seconds{1.0});
    }
}

TEST_CASE("minutes_to_seconds", "[convert]")
{
    SECTION("one minute")
    {
        CHECK(yasf::convert::minutes_to_seconds(yasf::Minutes{1.0})
              == yasf::Seconds{60.0});  // NOLINT
    }

    SECTION("one and a half minutes")
    {
        CHECK(yasf::convert::minutes_to_seconds(yasf::Minutes{1.5})  // NOLINT
              == yasf::Seconds{90.0});  // NOLINT
    }
}

TEST_CASE("seconds_to_minutes", "[convert]")
{
    SECTION("one minute")
    {
        CHECK(yasf::convert::seconds_to_minutes(yasf::Seconds{60.0})  // NOLINT
              == yasf::Minutes{1.0});
    }

    SECTION("one and a half minutes")
    {
        CHECK(yasf::convert::seconds_to_minutes(yasf::Seconds{90.0})  // NOLINT
              == yasf::Minutes{1.5});  // NOLINT
    }
}

TEST_CASE("hours_to_minutes", "[convert]")
{
    SECTION("one hour")
    {
        CHECK(yasf::convert::hours_to_minutes(yasf::Hours{1.0})
              == yasf::Minutes{60.0});  // NOLINT
    }

    SECTION("one and a half hours")
    {
        CHECK(yasf::convert::hours_to_minutes(yasf::Hours{1.5})  // NOLINT
              == yasf::Minutes{90.0});
    }
}

TEST_CASE("minutes_to_hours", "[convert]")
{
    SECTION("one hour")
    {
        CHECK(yasf::convert::minutes_to_hours(yasf::Minutes{60.0})  // NOLINT
              == yasf::Hours{1.0});
    }

    SECTION("one and a half hours")
    {
        CHECK(yasf::convert::minutes_to_hours(yasf::Minutes{90.0})  // NOLINT
              == yasf::Hours{1.5});  // NOLINT
    }
}

TEST_CASE("days_to_hours", "[convert]")
{
    SECTION("one day")
    {
        CHECK(yasf::convert::days_to_hours(yasf::Days{1.0})
              == yasf::Hours{24.0});  // NOLINT
    }

    SECTION("one and a half days")
    {
        CHECK(yasf::convert::days_to_hours(yasf::Days{1.5})  // NOLINT
              == yasf::Hours{36.0});  // NOLINT
    }
}

TEST_CASE("hours_to_days", "[convert]")
{
    SECTION("one day")
    {
        CHECK(yasf::convert::hours_to_days(yasf::Hours{24.0})  // NOLINT
              == yasf::Days{1.0});
    }

    SECTION("one and a half days")
    {
        CHECK(yasf::convert::hours_to_days(yasf::Hours{36.0})  // NOLINT
              == yasf::Days{1.5});  // NOLINT
    }
}
