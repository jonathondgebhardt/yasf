#include <string>

#include "yasf/uuid.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/object.hpp"

TEST_CASE("uuid: name", "[library]")
{
    auto const uuid = yasf::uuid{};
    REQUIRE(uuid.name() == std::string("uuid"));
}

TEST_CASE("uuid: uuid", "[library]")
{
    auto const uuid = yasf::uuid{};
    REQUIRE_FALSE(uuid.get().empty());
}

TEST_CASE("uuid: object component", "[library]")
{
    auto obj = yasf::object{};
    REQUIRE(obj.add_component<yasf::uuid>());

    SECTION("get_component")
    {
        auto* const child = obj.get_component<yasf::uuid>();
        REQUIRE(child != nullptr);
    }
}
