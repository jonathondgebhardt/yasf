#include "yasf/uuid.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("uuid", "[library]")
{
    auto const uuid = yasf::uuid{};

    SECTION("populated on construction")
    {
        CHECK_FALSE(uuid.empty());
    }

    SECTION("uniqueness")
    {
        auto const other = yasf::uuid{};
        CHECK(uuid != other);
    }
}
