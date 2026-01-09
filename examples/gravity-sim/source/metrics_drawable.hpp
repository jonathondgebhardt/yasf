#pragma once

#include <imgui.h>

#include "drawable.hpp"

struct MetricsDrawable : yasf::viewer::Drawable
{
    auto draw() -> void override
    {
        ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
    }
};
