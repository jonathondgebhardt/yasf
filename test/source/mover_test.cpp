#include <memory>
#include <utility>

#include "yasf/mover.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock_factory.hpp"
#include "yasf/entity_factory.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/math.hpp"
#include "yasf/position.hpp"
#include "yasf/processor_service.hpp"
#include "yasf/simulation.hpp"
#include "yasf/velocity.hpp"

struct MoverFixture
{
    MoverFixture()
    {
        auto clock = yasf::ClockFactory::build_fixed_update(m_delta_time);
        m_sim = std::make_unique<yasf::Simulation>(std::move(clock));

        // TODO: once again, this is inconvenient. i'd like something like this:
        // auto esvc = ...
        // m_sim->add_child(esvc);
        // esvc->add_child(...);
        m_sim->add_child<yasf::EntityService>();
        auto* esvc = m_sim->get_child<yasf::EntityService>();

        esvc->add_child(yasf::EntityFactory::build());
        m_entity = esvc->get_child<yasf::Entity>();

        m_sim->add_child<yasf::ProcessorService>();
        auto* psvc = m_sim->get_child<yasf::ProcessorService>();

        psvc->add_child<yasf::Mover>();
        m_mover = psvc->get_child<yasf::Mover>();
    }

    std::unique_ptr<yasf::Simulation> m_sim;
    yasf::Mover* m_mover{};
    yasf::Entity* m_entity{};
    yasf::time_seconds m_delta_time{1.0};
};

TEST_CASE_METHOD(MoverFixture, "mover: no movement", "[processor]")
{
    auto* vel = m_entity->get_component<yasf::Velocity>();
    REQUIRE(vel != nullptr);
    REQUIRE(vel->get().is_zero());

    auto* pos = m_entity->get_component<yasf::Position>();
    REQUIRE(pos != nullptr);
    const auto pos_vec = pos->get();

    m_sim->update();

    CHECK(pos->get() == pos_vec);
}

TEST_CASE_METHOD(MoverFixture, "mover: 1-d movement", "[processor]")
{
    constexpr auto x_vel = 1.0;
    auto* vel = m_entity->get_component<yasf::Velocity>();
    REQUIRE(vel != nullptr);

    vel->set(yasf::Vec3d{x_vel, 0.0, 0.0});

    auto* pos = m_entity->get_component<yasf::Position>();
    REQUIRE(pos != nullptr);

    constexpr auto iterations = 10;
    for (auto i = 0; i < iterations; ++i) {
        m_sim->update();

        auto const pos_vec = pos->get();
        CHECK(yasf::math::double_eq(pos_vec.x(), x_vel * i));
    }
}

TEST_CASE_METHOD(MoverFixture, "mover: 2-d movement", "[processor]")
{
    constexpr auto x_vel = 1.0;
    constexpr auto y_vel = 2.0;
    auto* vel = m_entity->get_component<yasf::Velocity>();
    REQUIRE(vel != nullptr);

    vel->set(yasf::Vec3d{x_vel, y_vel, 0.0});

    auto* pos = m_entity->get_component<yasf::Position>();
    REQUIRE(pos != nullptr);

    constexpr auto iterations = 10;
    for (auto i = 0; i < iterations; ++i) {
        m_sim->update();

        auto const pos_vec = pos->get();
        CHECK(yasf::math::double_eq(pos_vec.x(), x_vel * i));
        CHECK(yasf::math::double_eq(pos_vec.y(), y_vel * i));
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_CASE_METHOD(MoverFixture, "mover: 3-d movement", "[processor]")
{
    constexpr auto x_vel = 1.0;
    constexpr auto y_vel = 2.0;
    constexpr auto z_vel = 3.0;
    auto* vel = m_entity->get_component<yasf::Velocity>();
    REQUIRE(vel != nullptr);

    vel->set(yasf::Vec3d{x_vel, y_vel, z_vel});

    auto* pos = m_entity->get_component<yasf::Position>();
    REQUIRE(pos != nullptr);

    constexpr auto iterations = 10;
    for (auto i = 0; i < iterations; ++i) {
        m_sim->update();

        auto const pos_vec = pos->get();
        CHECK(yasf::math::double_eq(pos_vec.x(), x_vel * i));
        CHECK(yasf::math::double_eq(pos_vec.y(), y_vel * i));
        CHECK(yasf::math::double_eq(pos_vec.z(), z_vel * i));
    }
}

// NOLINTEND(readability-function-cognitive-complexity)
