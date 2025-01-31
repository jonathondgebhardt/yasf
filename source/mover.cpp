#include "yasf/mover.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/entity.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"
#include "yasf/visitor.hpp"

namespace yasf
{

struct mover_visitor : public object_visitor
{
    void visit(object* obj) override
    {
        auto* ent = dynamic_cast<entity*>(obj);
        if (ent != nullptr) {
            move_entity(ent);
        }
    }

    auto move_entity(entity* entity) const -> void
    {
        yasf::ensure(m_clock != nullptr, "failed to access clock");

        auto* const vel = entity->get_component<yasf::velocity>();
        if (vel == nullptr || vel->get().is_zero()) {
            return;
        }

        auto* pos = entity->get_component<yasf::position>();
        if (pos == nullptr) {
            return;
        }

        auto const delta_time = m_clock->delta_sec();

        auto pos_vec = pos->get();
        auto const vel_vec = vel->get();
        pos_vec += vel_vec * delta_time.count();
        pos->set(pos_vec);
    }

    clock* m_clock{};
};

auto mover::update() -> void
{
    auto* const esvc = get_entity_service();
    ensure(esvc != nullptr, "failed to get entity_service");

    auto* const clock = get_clock();
    auto visitor = mover_visitor{};

    // TODO: used designated initializer
    visitor.m_clock = clock;

    // TODO: how do i know which entities to get? should they be tagged somehow?
    esvc->accept(visitor);
}

}  // namespace yasf
