#include "yasf/mover.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/position.hpp"
#include "yasf/types.hpp"
#include "yasf/velocity.hpp"
#include "yasf/visitor.hpp"

namespace
{

struct MoverVisitor : public yasf::ObjectVisitor
{
    void visit(yasf::Object* obj) override
    {
        auto* ent = dynamic_cast<yasf::Entity*>(obj);
        if (ent != nullptr) {
            move_entity(ent);
        }
    }

    auto move_entity(yasf::Entity* entity) const -> void
    {
        yasf::Ensure(m_clock != nullptr, "failed to access clock");

        auto* const vel = entity->get_component<yasf::Velocity>();
        if (vel == nullptr || vel->get().is_zero()) {
            return;
        }

        auto* pos = entity->get_component<yasf::Position>();
        if (pos == nullptr) {
            return;
        }

        auto const delta_time = m_clock->delta<yasf::time_seconds>();

        auto pos_vec = pos->get();
        auto const vel_vec = vel->get();
        pos_vec += vel_vec * delta_time.count();
        pos->set(pos_vec);
    }

    yasf::Clock* m_clock{};
};

}  // namespace

namespace yasf
{

auto Mover::update() -> void
{
    auto* const esvc = get_entity_service();
    Ensure(esvc != nullptr, "failed to get entity_service");

    auto* const clock = get_clock();
    auto visitor = MoverVisitor{};

    // TODO: used designated initializer
    visitor.m_clock = clock;

    // TODO: how do i know which entities to get? should they be tagged somehow?
    esvc->accept(visitor);
}

}  // namespace yasf
