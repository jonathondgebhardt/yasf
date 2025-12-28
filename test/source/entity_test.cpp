#include "yasf/entity.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("entity: name")
{
    const auto entity = yasf::Entity{};
    REQUIRE(entity.name() == "entity");
}
