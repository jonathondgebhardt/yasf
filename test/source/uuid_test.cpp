#include "yasf/uuid.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("uuid", "[library]")
{
    auto const uuid = yasf::Uuid{};

    SECTION("populated on construction")
    {
        CHECK_FALSE(uuid.empty());
    }

    SECTION("uniqueness")
    {
        auto const other = yasf::Uuid{};
        CHECK(uuid != other);
    }

    SECTION("get")
    {
        CHECK(!uuid.get().empty());
    }

    SECTION("tail")
    {
        CHECK(uuid.tail(1).size() < uuid.tail(2).size());
    }
}
