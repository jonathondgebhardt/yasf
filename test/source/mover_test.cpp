#include "yasf/mover.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock_factory.hpp"
#include "yasf/entity_factory.hpp"
#include "yasf/math.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_CASE("mover: process")
{
    auto entity = yasf::entity_factory::build();

    auto* pos = entity->get_component<yasf::position>();
    REQUIRE(pos != nullptr);
    REQUIRE(pos->get().is_zero());

    auto* vel = entity->get_component<yasf::velocity>();
    REQUIRE(vel != nullptr);

    auto mover = yasf::mover{};
    mover.set_root(entity.get());

    auto clock = yasf::clock_factory::build_fixed_update(1.0);

    SECTION("throws without clock")
    {
        CHECK_THROWS(mover.process());
    }

    mover.set_clock(clock.get());

    SECTION("no movement")
    {
        REQUIRE(vel->get().is_zero());

        auto const initial_pos = pos->get();
        mover.process();
        REQUIRE(pos->get() == initial_pos);
    }

    SECTION("1-d movement")
    {
        constexpr auto x_vel = 1.0;
        vel->set(yasf::vec3d{x_vel, 0.0, 0.0});

        constexpr auto iterations = 10;
        for (auto i = 1; i <= iterations; ++i) {
            clock->tick();

            mover.process();
            auto const pos_vec = pos->get();
            REQUIRE(yasf::math::double_eq(pos_vec.x(), x_vel * i));
        }
    }

    SECTION("2-d movement")
    {
        constexpr auto x_vel = 1.0;
        constexpr auto y_vel = 2.0;
        vel->set(yasf::vec3d{x_vel, y_vel, 0.0});

        constexpr auto iterations = 10;
        for (auto i = 1; i <= iterations; ++i) {
            clock->tick();

            mover.process();
            auto const pos_vec = pos->get();
            REQUIRE(yasf::math::double_eq(pos_vec.x(), x_vel * i));
            REQUIRE(yasf::math::double_eq(pos_vec.y(), y_vel * i));
        }
    }

    SECTION("3-d movement")
    {
        constexpr auto x_vel = 1.0;
        constexpr auto y_vel = 2.0;
        constexpr auto z_vel = 3.0;
        vel->set(yasf::vec3d{x_vel, y_vel, z_vel});

        constexpr auto iterations = 10;
        for (auto i = 1; i <= iterations; ++i) {
            clock->tick();

            mover.process();
            auto const pos_vec = pos->get();
            REQUIRE(yasf::math::double_eq(pos_vec.x(), x_vel * i));
            REQUIRE(yasf::math::double_eq(pos_vec.y(), y_vel * i));
            REQUIRE(yasf::math::double_eq(pos_vec.z(), z_vel * i));
        }
    }
}

// NOLINTEND(readability-function-cognitive-complexity)
