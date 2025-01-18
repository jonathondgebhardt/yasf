#include "yasf/convert.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/constants.hpp"
#include "yasf/math.hpp"
#include "yasf/types.hpp"

TEST_CASE("sec_to_us: zero seconds", "[convert]")
{
    REQUIRE(yasf::convert::sec_to_usec(0.0) == yasf::time_us{0});
}

TEST_CASE("sec_to_us: one second", "[convert]")
{
    REQUIRE(yasf::convert::sec_to_usec(1.0) == yasf::constants::sec_to_usec);
}

TEST_CASE("us_to_sec: zero seconds", "[convert]")
{
    REQUIRE(yasf::math::double_eq(yasf::convert::usec_to_sec(0), 0.0));
}

TEST_CASE("us_to_sec: one second", "[convert]")
{
    REQUIRE(yasf::math::double_eq(yasf::convert::usec_to_sec(1),
                                  yasf::constants::usec_to_sec));
}
