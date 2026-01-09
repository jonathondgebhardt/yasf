#pragma once

#include <imgui.h>

#include "drawable.hpp"
#include "yasf/clock.hpp"
#include "yasf/convert.hpp"

struct SimTimeDrawable : yasf::viewer::Drawable
{
    auto get_sim_time() const -> std::string
    {
        const auto seconds = clock->time<yasf::time_seconds>();
        const auto hms = std::chrono::hh_mm_ss{seconds};
        std::ostringstream oss;
        oss << hms;
        return oss.str();
    }

    auto draw() -> void override
    {
        ImGui::Text("time: %s", get_sim_time().c_str());
    }

    yasf::Clock* clock{};
};
