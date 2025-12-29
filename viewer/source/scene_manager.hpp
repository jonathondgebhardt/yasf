#pragma once

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "yasf/uuid.hpp"

/**
 * @brief Manages all drawables.
 */
class SceneManager
{
public:
    explicit SceneManager(sf::RenderWindow* window)
        : m_window{window}
    {
    }

    /**
     * @brief The drawable item.
     */
    struct Drawable
    {
        // The drawable.
        sf::Drawable* drawable;

        // The Uuid of the yasf entity.
        yasf::Uuid uuid;
    };

    void add_drawable(Drawable drawable);

    void draw();

private:
    sf::RenderWindow* m_window{};
    std::vector<Drawable> m_drawables;
};
