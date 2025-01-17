#include "yasf/object_factory.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("object_factory: build", "[library]")
{
    auto obj = yasf::object_factory::build();
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
}
