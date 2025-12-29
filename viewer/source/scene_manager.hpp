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
        enum class RenderBin
        {
            BACKGROUND = 0,
            FOREGROUND,
            OVERLAY
        };

        Drawable() = default;

        explicit Drawable(std::unique_ptr<sf::Drawable> drawable, RenderBin render_bin = RenderBin::FOREGROUND,
                          std::optional<yasf::Uuid> uuid = std::nullopt)
            : uuid{std::move(uuid)}
            , drawable{std::move(drawable)}
            , render_bin{render_bin}
        {
        }

        virtual ~Drawable() = default;

        virtual auto update() -> void {}

        // The Uuid of the yasf entity.
        std::optional<yasf::Uuid> uuid;

        // The drawable.
        std::unique_ptr<sf::Drawable> drawable;

        RenderBin render_bin = RenderBin::FOREGROUND;
    };

    auto add_drawable(std::unique_ptr<Drawable> drawable) -> void;

    auto draw() -> void;

private:
    sf::RenderWindow* m_window{};
    std::vector<std::unique_ptr<Drawable>> m_background_drawables;
    std::vector<std::unique_ptr<Drawable>> m_foreground_drawables;
    std::vector<std::unique_ptr<Drawable>> m_overlay_drawables;
};
