#pragma once

#include <imgui.h>

#include "drawable.hpp"
#include "yasf/acceleration.hpp"
#include "yasf/object.hpp"
#include "yasf/position.hpp"
#include "yasf/simulation.hpp"
#include "yasf/velocity.hpp"

struct TreeDrawable : yasf::viewer::Drawable
{
    auto draw() -> void override
    {
        if (ImGui::CollapsingHeader("simulation tree")) {
            std::ranges::for_each(sim->get_children(), &draw_tree);
        }
    }

    static auto get_id(const yasf::Object* obj) -> std::string
    {
        return std::format("{} ({})", obj->name(), obj->uuid().tail(4));
    }

    static auto draw_tree(const yasf::Object* obj) -> void
    {
        if (ImGui::TreeNode(get_id(obj).c_str())) {
            std::ranges::for_each(obj->get_children(),
                                  [](const auto child) { draw_tree(child); });

            draw_entity_components(obj);

            ImGui::TreePop();
        }
    }

    static auto draw_entity_components(const yasf::Object* obj) -> void
    {
        if (auto* const pos = obj->get_component<yasf::Position>()) {
            const auto vec = pos->get();
            ImGui::Text("position: %.2f %.2f", vec.x(), vec.y());
        }

        if (auto* const vel = obj->get_component<yasf::Velocity>()) {
            const auto vec = vel->get();
            ImGui::Text("velocity: %.2f %.2f", vec.x(), vec.y());
        }

        if (auto* const acc = obj->get_component<yasf::Acceleration>()) {
            const auto vec = acc->get();
            ImGui::Text("acceleration: %.2f %.2f", vec.x(), vec.y());
        }
    }

    yasf::Simulation* sim{};
};
