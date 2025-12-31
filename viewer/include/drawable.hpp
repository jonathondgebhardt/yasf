#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include "graphics_window.hpp"

namespace yasf::viewer
{

/**
 * @brief The drawable item.
 */
class Drawable
{
public:
    /**
     * @enum RenderBin
     * @brief Indicates the draw order.
     * @detail Lower RenderBins will be drawn first.
     */
    enum class RenderBin : std::uint8_t
    {
        BACKGROUND = 0,
        FOREGROUND,
        OVERLAY
    };

    virtual ~Drawable() = default;

    virtual auto update() -> void {}

    virtual auto draw() -> void {}

    auto render_bin() const -> RenderBin { return m_render_bin; }

protected:
    RenderBin m_render_bin = RenderBin::FOREGROUND;
};

template<typename T> requires std::is_base_of_v<sf::Drawable, T>
class SfDrawable : public Drawable
{
public:
    auto draw() -> void override
    {
        const auto window_handle =
            yasf::viewer::GraphicsWindow::instance()->handle();
        window_handle->draw(m_drawable);
    }
protected:
    T m_drawable;
};

}  // namespace yasf::viewer
