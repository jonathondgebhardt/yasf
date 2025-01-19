#include "yasf/ensure.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("throws if false", "[ensure]")
{
    REQUIRE_THROWS(yasf::ensure(false, "failure message"));
}

TEST_CASE("does not throw if true", "[ensure]")
{
    REQUIRE_NOTHROW(yasf::ensure(true, "failure message"));
}
