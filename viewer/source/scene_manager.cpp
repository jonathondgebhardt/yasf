#include <ranges>

#include "scene_manager.hpp"

void SceneManager::add_drawable(std::unique_ptr<Drawable> drawable)
{
    m_drawables.push_back(std::move(drawable));
}

void SceneManager::draw()
{
    for (const auto drawable : m_drawables
             | std::views::filter([](const std::unique_ptr<Drawable>& drawable)
                                  { return drawable->drawable != nullptr; })
             | std::views::transform(
                                   [](const std::unique_ptr<Drawable>& drawable)
                                   { return drawable.get(); }))
    {
        drawable->update();
        m_window->draw(*drawable->drawable);
    }
}
