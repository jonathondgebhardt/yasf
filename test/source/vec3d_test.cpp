#include <array>

#include "yasf/vec3d.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/math.hpp"

TEST_CASE("vec3d: constructor", "[library]")
{
    SECTION("default")
    {
        constexpr auto vec = yasf::vec3d{};
        REQUIRE(vec == std::array{0.0, 0.0, 0.0});
    }

    SECTION("parameterized: scalar")
    {
        constexpr auto vec = yasf::vec3d{1.0};
        REQUIRE(vec == std::array{1.0, 1.0, 1.0});
    }

    SECTION("parameterized: array")
    {
        constexpr auto vec = yasf::vec3d{std::array{1.0, 2.0, 3.0}};
        REQUIRE(vec == std::array{1.0, 2.0, 3.0});  // NOLINT
    }

    SECTION("parameterized: literals")
    {
        constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};
        REQUIRE(vec == std::array{1.0, 2.0, 3.0});  // NOLINT
    }
}

TEST_CASE("vec3d: equality", "[library]")
{
    SECTION("array")
    {
        constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};
        REQUIRE(vec == std::array{1.0, 2.0, 3.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto lhs = yasf::vec3d{1.0, 2.0, 3.0};
        constexpr auto rhs = yasf::vec3d{1.0, 2.0, 3.0};
        REQUIRE(lhs == rhs);  // NOLINT
    }
}

TEST_CASE("vec3d: inequality", "[library]")
{
    SECTION("array")
    {
        constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};
        REQUIRE(vec != std::array{2.0, 3.0, 4.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto lhs = yasf::vec3d{1.0, 2.0, 3.0};
        constexpr auto rhs = yasf::vec3d{2.0, 3.0, 4.0};
        REQUIRE(lhs != rhs);  // NOLINT
    }
}

TEST_CASE("vec3d: component getters")
{
    constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};
    REQUIRE(yasf::math::double_eq(vec.x(), 1.0));
    REQUIRE(yasf::math::double_eq(vec.y(), 2.0));  // NOLINT
    REQUIRE(yasf::math::double_eq(vec.z(), 3.0));  // NOLINT
}

TEST_CASE("vec3d: component setters")
{
    auto vec = yasf::vec3d{};

    vec.x() = 1.0;
    REQUIRE(yasf::math::double_eq(vec.x(), 1.0));

    vec.y() = 2.0;  // NOLINT
    REQUIRE(yasf::math::double_eq(vec.y(), 2.0));  // NOLINT

    vec.z() = 3.0;  // NOLINT
    REQUIRE(yasf::math::double_eq(vec.z(), 3.0));  // NOLINT
}

TEST_CASE("vec3d: const addition operator")
{
    constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};

    SECTION("scalar")
    {
        constexpr auto sum = vec + 1.0;
        REQUIRE(sum == yasf::vec3d{2.0, 3.0, 4.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto sum = vec + yasf::vec3d{1.0, 2.0, 3.0};
        REQUIRE(sum == yasf::vec3d{2.0, 4.0, 6.0});  // NOLINT
    }
}

TEST_CASE("vec3d: addition operator")
{
    auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT

    SECTION("scalar")
    {
        vec += 1.0;
        REQUIRE(vec == yasf::vec3d{2.0, 3.0, 4.0});  // NOLINT
    }

    SECTION("vec")
    {
        vec += yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
        REQUIRE(vec == yasf::vec3d{2.0, 4.0, 6.0});  // NOLINT
    }
}

TEST_CASE("vec3d: const subtraction operator")
{
    constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};

    SECTION("scalar")
    {
        constexpr auto sum = vec - 1.0;
        REQUIRE(sum == yasf::vec3d{0.0, 1.0, 2.0});  // NOLINT
    }

    SECTION("vec")
    {
        constexpr auto sum = vec - yasf::vec3d{1.0, 2.0, 3.0};
        REQUIRE(sum == yasf::vec3d{0.0, 0.0, 0.0});  // NOLINT
    }
}

TEST_CASE("vec3d: subtraction operator")
{
    auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT

    SECTION("scalar")
    {
        vec -= 1.0;
        REQUIRE(vec == yasf::vec3d{0.0, 1.0, 2.0});  // NOLINT
    }

    SECTION("vec")
    {
        vec -= yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
        REQUIRE(vec == yasf::vec3d{0.0, 0.0, 0.0});  // NOLINT
    }
}

TEST_CASE("vec3d: multiply const")
{
    constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};
    constexpr auto result = vec * 2.0;
    REQUIRE(result == yasf::vec3d{2.0, 4.0, 6.0});  // NOLINT
}

TEST_CASE("vec3d: multiply")
{
    auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
    vec *= 2.0;  // NOLINT
    REQUIRE(vec == yasf::vec3d{2.0, 4.0, 6.0});  // NOLINT
}

TEST_CASE("vec3d: divide const")
{
    constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};
    constexpr auto result = vec / 2.0;
    REQUIRE(result == yasf::vec3d{0.5, 1.0, 1.5});  // NOLINT
}

TEST_CASE("vec3d: divide")
{
    auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
    vec /= 2.0;  // NOLINT
    REQUIRE(vec == yasf::vec3d{0.5, 1.0, 1.5});  // NOLINT
}

TEST_CASE("vec3d: mag")
{
    constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};
    const auto mag = vec.mag();
    REQUIRE(yasf::math::double_eq(mag, 3.7416573867739413));  // NOLINT
}

TEST_CASE("vec3d: normal")
{
    constexpr auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
    const auto result = vec.normal();

    REQUIRE(result
            == yasf::vec3d{0.2672612419124244,  // NOLINT
                           0.53452248382484879,  // NOLINT
                           0.80178372573727319});  // NOLINT
}

TEST_CASE("vec3d: normalize")
{
    auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
    vec.normalize();

    REQUIRE(vec
            == yasf::vec3d{0.2672612419124244,  // NOLINT
                           0.53452248382484879,  // NOLINT
                           0.80178372573727319});  // NOLINT
}

TEST_CASE("vec3d: zero")
{
    auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
    vec.zero();
    REQUIRE(vec == yasf::vec3d{0.0});
}

TEST_CASE("vec3d: is_zero")
{
    auto vec = yasf::vec3d{1.0, 2.0, 3.0};  // NOLINT
    REQUIRE_FALSE(vec.is_zero());
    vec.zero();
    REQUIRE(vec == yasf::vec3d{0.0});
}
