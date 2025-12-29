#pragma once

#include <memory>
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
        Drawable() = default;

        explicit Drawable(std::unique_ptr<sf::Drawable> drawable,
                          std::optional<yasf::Uuid> uuid = std::nullopt)
            : drawable{std::move(drawable)}
            , uuid{std::move(uuid)}
        {
        }

        virtual ~Drawable() = default;

        virtual void update() {}

        // The drawable.
        std::unique_ptr<sf::Drawable> drawable;

        // The Uuid of the yasf entity.
        std::optional<yasf::Uuid> uuid;
    };

    void add_drawable(std::unique_ptr<Drawable> drawable);

    void draw();

private:
    sf::RenderWindow* m_window{};
    std::vector<std::unique_ptr<Drawable>> m_drawables;
};
