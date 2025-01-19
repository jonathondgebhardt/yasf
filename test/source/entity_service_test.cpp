#include "yasf/entity_service.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("entity_service: name is entity_service", "[entity_service]")
{
    auto const esvc = yasf::entity_service{};
    CHECK(esvc.name() == "entity_service");
}
