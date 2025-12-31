#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "scene_manager.hpp"

#include "drawable.hpp"

namespace
{

auto update_and_draw(
    const std::vector<std::unique_ptr<yasf::viewer::Drawable>>& drawables)
    -> void
{
    std::ranges::for_each(drawables,
                          [](const auto& drawable)
                          {
                              drawable->update();
                              drawable->draw();
                          });
}

}  // namespace

namespace yasf::viewer
{

auto SceneManager::add_drawable(std::unique_ptr<Drawable> drawable) -> void
{
    if (drawable == nullptr) {
        return;
    }

    if (drawable->render_bin() == Drawable::RenderBin::BACKGROUND) {
        m_background_drawables.push_back(std::move(drawable));
    } else if (drawable->render_bin() == Drawable::RenderBin::FOREGROUND) {
        m_foreground_drawables.push_back(std::move(drawable));
    } else if (drawable->render_bin() == Drawable::RenderBin::OVERLAY) {
        m_overlay_drawables.push_back(std::move(drawable));
    }
}

auto SceneManager::draw() -> void
{
    update_and_draw(m_background_drawables);
    update_and_draw(m_foreground_drawables);
    update_and_draw(m_overlay_drawables);
}

}  // namespace yasf::viewer
