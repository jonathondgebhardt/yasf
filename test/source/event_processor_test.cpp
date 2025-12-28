#include <memory>

#include "yasf/event_processor.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/clock.hpp"
#include "yasf/entity_service.hpp"
#include "yasf/event.hpp"
#include "yasf/event_processor_service.hpp"
#include "yasf/event_simulation.hpp"

namespace
{

struct concrete_processor : public yasf::EventProcessor
{
    void on_event([[maybe_unused]] const yasf::Event* evt) override {}
};

}  // namespace

TEST_CASE("event_processor: name is processor", "[event_processor]")
{
    auto const proc = concrete_processor{};
    CHECK(proc.name() == "event_processor");
}

TEST_CASE("event_processor: simulation getters", "[event_processor]")
{
    auto sim = yasf::EventSimulation{std::make_unique<yasf::Clock>()};

    REQUIRE(sim.add_child<yasf::EventProcessorService>());
    auto* const psvc = sim.get_child<yasf::EventProcessorService>();
    REQUIRE(psvc != nullptr);

    REQUIRE(psvc->add_child(std::make_unique<concrete_processor>()));
    auto* const proc = psvc->get_child<concrete_processor>();
    REQUIRE(proc != nullptr);

    SECTION("get_simulation")
    {
        CHECK(proc->get_simulation());
    }

    SECTION("get_clock")
    {
        CHECK(proc->get_clock());
    }

    REQUIRE(sim.add_child<yasf::EntityService>());

    SECTION("get_entity_service")
    {
        CHECK(proc->get_entity_service());
    }
}
