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

    Drawable(const Drawable&) = default;
    Drawable(Drawable&&) = delete;
    virtual ~Drawable() = default;
    auto operator=(const Drawable&) -> Drawable& = default;
    auto operator=(Drawable&&) -> Drawable& = delete;

    virtual auto update() -> void {}

    virtual auto draw() -> void {}

    auto render_bin() const -> RenderBin { return m_render_bin; }

    auto set_render_bin(RenderBin render_bin) -> void
    {
        m_render_bin = render_bin;
    }

private:
    RenderBin m_render_bin = RenderBin::FOREGROUND;
};

template<typename T>
    requires std::is_base_of_v<sf::Drawable, T>
class SfDrawable : public Drawable
{
public:
    auto draw() -> void override
    {
        auto* const window_handle =
            yasf::viewer::GraphicsWindow::instance()->handle();
        window_handle->draw(m_drawable);
    }

protected:
    T m_drawable;
};

}  // namespace yasf::viewer
