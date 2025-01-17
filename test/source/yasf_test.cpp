#include <string>

#include "yasf/yasf.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is yasf", "[library]")
{
  auto const exported = exported_class {};
  REQUIRE(std::string("yasf") == exported.name());
}
