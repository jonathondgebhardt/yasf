#include "yasf/object_factory.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("object_factory: build", "[library]")
{
    auto obj = yasf::ObjectFactory::build();
    REQUIRE(obj != nullptr);
}
