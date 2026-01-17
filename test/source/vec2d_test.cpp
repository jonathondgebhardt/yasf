#include <array>

#include "yasf/vec2d.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/math.hpp"

TEST_CASE("vec2d: constructor", "[library]")
{
    SECTION("default")
    {
        constexpr auto vec = yasf::Vec2d{};
        REQUIRE(vec == std::array{0.0, 0.0});
    }

    SECTION("parameterized: scalar")
    {
        constexpr auto vec = yasf::Vec2d{1.0};
        REQUIRE(vec == std::array{1.0, 1.0});
    }

    SECTION("parameterized: array")
    {
        constexpr auto vec = yasf::Vec2d{std::array{1.0, 2.0}};
        REQUIRE(vec == std::array{1.0, 2.0});  // NOLINT
    }

    SECTION("parameterized: literals")
    {
        constexpr auto vec = yasf::Vec2d{1.0, 2.0};
        REQUIRE(vec == std::array{1.0, 2.0});  // NOLINT
    }
}

TEST_CASE("vec2d: equality", "[library]")
{
    SECTION("array")
    {
        constexpr auto vec = yasf::Vec2d{1.0, 2.0};
        REQUIRE(vec == std::array{1.0, 2.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto lhs = yasf::Vec2d{1.0, 2.0};
        constexpr auto rhs = yasf::Vec2d{1.0, 2.0};
        REQUIRE(lhs == rhs);  // NOLINT
    }
}

TEST_CASE("vec2d: inequality", "[library]")
{
    SECTION("array")
    {
        constexpr auto vec = yasf::Vec2d{1.0, 2.0};
        REQUIRE(vec != std::array{2.0, 3.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto lhs = yasf::Vec2d{1.0, 2.0};
        constexpr auto rhs = yasf::Vec2d{2.0, 3.0};
        REQUIRE(lhs != rhs);  // NOLINT
    }
}

TEST_CASE("vec2d: component getters")
{
    constexpr auto vec = yasf::Vec2d{1.0, 2.0};
    REQUIRE(yasf::math::double_eq(vec.x(), 1.0));
    REQUIRE(yasf::math::double_eq(vec.y(), 2.0));  // NOLINT
}

TEST_CASE("vec2d: component setters")
{
    auto vec = yasf::Vec2d{};

    vec.x() = 1.0;
    REQUIRE(yasf::math::double_eq(vec.x(), 1.0));

    vec.y() = 2.0;  // NOLINT
    REQUIRE(yasf::math::double_eq(vec.y(), 2.0));  // NOLINT
}

TEST_CASE("vec2d: const addition operator")
{
    constexpr auto vec = yasf::Vec2d{1.0, 2.0};

    SECTION("scalar")
    {
        constexpr auto sum = vec + 1.0;
        REQUIRE(sum == yasf::Vec2d{2.0, 3.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto sum = vec + yasf::Vec2d{1.0, 2.0};
        REQUIRE(sum == yasf::Vec2d{2.0, 4.0});  // NOLINT
    }
}

TEST_CASE("vec2d: addition operator")
{
    auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT

    SECTION("scalar")
    {
        vec += 1.0;
        REQUIRE(vec == yasf::Vec2d{2.0, 3.0});  // NOLINT
    }

    SECTION("vec")
    {
        vec += yasf::Vec2d{1.0, 2.0};  // NOLINT
        REQUIRE(vec == yasf::Vec2d{2.0, 4.0});  // NOLINT
    }
}

TEST_CASE("vec2d: const subtraction operator")
{
    constexpr auto vec = yasf::Vec2d{1.0, 2.0};

    SECTION("scalar")
    {
        constexpr auto sum = vec - 1.0;
        REQUIRE(sum == yasf::Vec2d{0.0, 1.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto sum = vec - yasf::Vec2d{1.0, 2.0};
        REQUIRE(sum == yasf::Vec2d{0.0, 0.0});  // NOLINT
    }
}

TEST_CASE("vec2d: subtraction operator")
{
    auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT

    SECTION("scalar")
    {
        vec -= 1.0;
        REQUIRE(vec == yasf::Vec2d{0.0, 1.0});  // NOLINT
    }

    SECTION("vec")
    {
        vec -= yasf::Vec2d{1.0, 2.0};  // NOLINT
        REQUIRE(vec == yasf::Vec2d{0.0, 0.0});  // NOLINT
    }
}

TEST_CASE("vec2d: multiply const")
{
    constexpr auto vec = yasf::Vec2d{1.0, 2.0};
    constexpr auto result = vec * 2.0;
    REQUIRE(result == yasf::Vec2d{2.0, 4.0});  // NOLINT
}

TEST_CASE("vec2d: multiply")
{
    auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT
    vec *= 2.0;  // NOLINT
    REQUIRE(vec == yasf::Vec2d{2.0, 4.0});  // NOLINT
}

TEST_CASE("vec2d: divide const")
{
    constexpr auto vec = yasf::Vec2d{1.0, 2.0};
    constexpr auto result = vec / 2.0;
    REQUIRE(result == yasf::Vec2d{0.5, 1.0});  // NOLINT
}

TEST_CASE("vec2d: divide")
{
    auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT
    vec /= 2.0;  // NOLINT
    REQUIRE(vec == yasf::Vec2d{0.5, 1.0});  // NOLINT
}

TEST_CASE("vec2d: mag")
{
    constexpr auto vec = yasf::Vec2d{1.0, 2.0};
    const auto mag = vec.mag();
    REQUIRE(yasf::math::double_eq(mag, 2.2360679774997898));  // NOLINT
}

TEST_CASE("vec2d: normal")
{
    constexpr auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT
    const auto result = vec.normal();

    REQUIRE(result
            == yasf::Vec2d{0.44721359549995793,  // NOLINT
                           0.89442719099991586});  // NOLINT
}

TEST_CASE("vec2d: normalize")
{
    auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT
    vec.normalize();

    REQUIRE(vec
            == yasf::Vec2d{0.44721359549995793,  // NOLINT
                           0.89442719099991586});  // NOLINT
}

TEST_CASE("vec2d: zero")
{
    auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT
    vec.zero();
    REQUIRE(vec == yasf::Vec2d{});
}

TEST_CASE("vec2d: is_zero")
{
    auto vec = yasf::Vec2d{1.0, 2.0};  // NOLINT
    REQUIRE_FALSE(vec.is_zero());
    vec.zero();
    REQUIRE(vec == yasf::Vec2d{});
}
