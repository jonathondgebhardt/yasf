#include <ranges>

#include "scene_manager.hpp"

void SceneManager::add_drawable(Drawable drawable)
{
    m_drawables.push_back(std::move(drawable));
}

void SceneManager::draw()
{
    for (const auto drawable : m_drawables
             | std::views::filter([](const Drawable& drawable)
                                  { return drawable.drawable != nullptr; })
             | std::views::transform([](const Drawable& drawable)
                                     { return drawable.drawable; }))
    {
        m_window->draw(*drawable);
    }
}
