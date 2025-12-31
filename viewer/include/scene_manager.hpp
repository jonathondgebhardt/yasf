#pragma once

#include <memory>
#include <vector>

#include "yasf/uuid.hpp"
#include "yasf/viewer/yasf_viewer_export.hpp"
#include "drawable.hpp"

namespace yasf::viewer
{

/**
 * @brief Manages all drawables.
 */
class YASF_VIEWER_EXPORT SceneManager
{
public:
    auto add_drawable(std::unique_ptr<Drawable> drawable) -> void;

    auto draw() -> void;

private:
    YASF_SUPPRESS_C4251
    std::vector<std::unique_ptr<Drawable>> m_background_drawables;
    std::vector<std::unique_ptr<Drawable>> m_foreground_drawables;
    std::vector<std::unique_ptr<Drawable>> m_overlay_drawables;
};

}