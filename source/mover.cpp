#include "yasf/mover.hpp"

#include "yasf/acceleration.hpp"
#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/position.hpp"
#include "yasf/types.hpp"
#include "yasf/velocity.hpp"
#include "yasf/visitor.hpp"

namespace
{

struct MoverVisitor : yasf::ObjectVisitor
{
    void apply(yasf::Object& obj) override
    {
        if (auto* ent = dynamic_cast<yasf::Entity*>(&obj); ent != nullptr) {
            move_entity(ent);
        }

        traverse(obj);
    }

    auto move_entity(const yasf::Entity* entity) const -> void
    {
        yasf::Ensure(clock != nullptr, "failed to access clock");

        auto* const acc = entity->get_component<yasf::Acceleration>();
        if (acc == nullptr) {
            return;
        }

        auto* const vel = entity->get_component<yasf::Velocity>();
        if (vel == nullptr || (vel->get().is_zero() && acc->get().is_zero())) {
            return;
        }

        auto* pos = entity->get_component<yasf::Position>();
        if (pos == nullptr) {
            return;
        }

        auto const delta_time = clock->delta<yasf::time::Seconds>();
        vel->get() += acc->get() * delta_time.count();
        pos->get() += vel->get() * delta_time.count();
    }

    yasf::Clock* clock{};
};

}  // namespace

namespace yasf
{

auto Mover::update() -> void
{
    auto* const svc = get_entity_service();
    Ensure(svc != nullptr, "failed to get entity_service");

    auto* const clock = get_clock();
    auto visitor = MoverVisitor{};
    visitor.clock = clock;

    // TODO: how do i know which entities to get? should they be tagged somehow?
    svc->accept(visitor);
}

}  // namespace yasf
