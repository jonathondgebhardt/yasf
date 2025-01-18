#include "yasf/entity_factory.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("entity_factory: build", "[library]")
{
    auto obj = yasf::entity_factory::build();
    REQUIRE(obj != nullptr);

    SECTION("has status")
    {
        auto* status = obj->get_component("status");
        REQUIRE(status != nullptr);
    }

    SECTION("has uuid")
    {
        auto* uuid = obj->get_component("uuid");
        REQUIRE(uuid != nullptr);
    }

    SECTION("has position")
    {
        auto* position = obj->get_component("position");
        REQUIRE(position != nullptr);
    }
}
