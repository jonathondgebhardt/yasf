#include "yasf/convert.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/constants.hpp"
#include "yasf/math.hpp"
#include "yasf/types.hpp"

TEST_CASE("sec_to_us: zero seconds", "[convert]")
{
    REQUIRE(yasf::convert::seconds_to_useconds(0.0) == yasf::time_useconds{0});
}

TEST_CASE("sec_to_us: one second", "[convert]")
{
    REQUIRE(yasf::convert::seconds_to_useconds(1.0)
            == yasf::constants::seconds_to_useconds);
}

TEST_CASE("us_to_sec: zero seconds", "[convert]")
{
    REQUIRE(yasf::math::double_eq(yasf::convert::useconds_to_seconds(0), 0.0));
}

TEST_CASE("us_to_sec: one second", "[convert]")
{
    REQUIRE(yasf::math::double_eq(yasf::convert::useconds_to_seconds(1000000),
                                  1.0));
}
