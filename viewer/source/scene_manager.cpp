#include <ranges>

#include "scene_manager.hpp"

namespace
{

auto update_and_draw(
    const std::vector<std::unique_ptr<SceneManager::Drawable>>& drawables,
    sf::RenderWindow* window) -> void
{
    for (auto* const drawable :
         drawables
             | std::views::filter(
                 [](const std::unique_ptr<SceneManager::Drawable>& drawable)
                 { return drawable->drawable != nullptr; })
             | std::views::transform(
                 [](const std::unique_ptr<SceneManager::Drawable>& drawable)
                 { return drawable.get(); }))
    {
        drawable->update();
        window->draw(*drawable->drawable);
    }
}

}  // namespace

auto SceneManager::add_drawable(std::unique_ptr<Drawable> drawable) -> void
{
    if (drawable == nullptr) {
        return;
    }

    if (drawable->render_bin == Drawable::RenderBin::BACKGROUND) {
        m_background_drawables.push_back(std::move(drawable));
    } else if (drawable->render_bin == Drawable::RenderBin::FOREGROUND) {
        m_foreground_drawables.push_back(std::move(drawable));
    } else if (drawable->render_bin == Drawable::RenderBin::OVERLAY) {
        m_overlay_drawables.push_back(std::move(drawable));
    }
}

auto SceneManager::draw() -> void
{
    update_and_draw(m_background_drawables, m_window);
    update_and_draw(m_foreground_drawables, m_window);
    update_and_draw(m_overlay_drawables, m_window);
}
