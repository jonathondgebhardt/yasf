#pragma once

#include "yasf/acceleration.hpp"
#include "yasf/ensure.hpp"
#include "yasf/position.hpp"
#include "yasf/processor.hpp"
#include "yasf/vec3d.hpp"
#include "yasf/velocity.hpp"

struct GroundCollisionProcessor : yasf::Processor
{
    struct FindGroundObjectVisitor : yasf::ObjectVisitor
    {
        auto visit(yasf::Object* obj) -> void override
        {
            if (obj != nullptr && obj->display_name() == "ground") {
                ground = obj;
            }
        }

        yasf::Object* ground{};
    };

    struct DetectCollisionsVisitor : yasf::ObjectVisitor
    {
        static auto overlap(const yasf::Vec3d lhs, const yasf::Vec3d rhs)
            -> bool
        {
            // return yasf::math::double_eq(lhs.x(), rhs.x())
            //     || yasf::math::double_eq(lhs.y(), rhs.y());
            return lhs.y() >= rhs.y();
        }

        auto visit(yasf::Object* obj) -> void override
        {
            if (obj == nullptr || obj == collider) {
                return;
            }

            auto* const pos_collidee = obj->get_component<yasf::Position>();
            if (pos_collidee == nullptr) {
                return;
            }

            auto* const pos_collider =
                collider->get_component<yasf::Position>();
            if (pos_collider == nullptr) {
                return;
            }

            if (overlap(pos_collidee->get(), pos_collider->get())) {
                collidees.push_back(obj);
            }
        }

        yasf::Object* collider{};
        std::vector<yasf::Object*> collidees;
    };

    auto update() -> void override
    {
        auto ground_visitor = FindGroundObjectVisitor{};
        get_simulation()->accept(ground_visitor);
        auto* const ground = ground_visitor.ground;
        yasf::Ensure(ground != nullptr, "failed to find ground object");

        auto collision_visitor = DetectCollisionsVisitor{};
        collision_visitor.collider = ground;
        get_entity_service()->accept(collision_visitor);

        std::ranges::for_each(
            collision_visitor.collidees,
            [](yasf::Object* const obj)
            {
                if (auto* vel = obj->get_component<yasf::Velocity>()) {
                    vel->get().zero();
                }
                if (auto* acc = obj->get_component<yasf::Acceleration>()) {
                    acc->get().zero();
                }
            });
    }
};
